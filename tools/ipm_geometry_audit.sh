#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="${ROOT}/code/build-host"
BIN="${BUILD}/front_car_mainline"
OUT="${ROOT}/.diag/ipm_geometry_audit"
REPORT_KEYS='^(line_found|ipm_source|atg_track_type|atg_cross_type|atg_circle_type|atg_rpts0s_num|atg_rpts1s_num|atg_rptsn_num|atg_lpt0_found|atg_lpt1_found|atg_is_straight0|atg_is_straight1|atg_conf1_max_deg|atg_conf2_max_deg|mid_step|control_ref|guide_error)='

mkdir -p "${OUT}"

if [[ ! -f "${BUILD}/Makefile" ]]; then
    bash "${ROOT}/scripts/test.sh" --host --reconfigure
fi
cmake --build "${BUILD}" --target front_car_mainline -j"${MAKE_JOBS:-$(nproc)}"

if [[ $# -eq 0 ]]; then
    set -- \
        ".diag/live_border_midline_report/front_car_capture_border_midline_report_1.png" \
        ".diag/live_border_midline_report/front_car_capture_border_midline_report_2.png" \
        ".diag/live_border_midline_report/front_car_capture_border_midline_report_3.png" \
        ".diag/front_car_capture_live_current.png"
fi

status=0
for img in "$@"; do
    if [[ ! -f "${ROOT}/${img}" ]]; then
        echo "====SKIP ${img}===="
        echo "missing file"
        status=1
        continue
    fi

    name="$(basename "${img}")"
    stem="${name%.*}"
    rpt="${OUT}/${stem}.report.txt"
    log="${OUT}/${stem}.log.txt"
    ipm="${OUT}/${stem}.ipm.png"

    echo "====${img}===="
    "${BIN}" \
        --analyze "${ROOT}/${img}" \
        --ipm "${ipm}" \
        --report "${rpt}" >"${log}" 2>&1
    cat "${log}"
    echo "----REPORT----"
    grep -E "${REPORT_KEYS}" "${rpt}" || true
done
exit "${status}"
