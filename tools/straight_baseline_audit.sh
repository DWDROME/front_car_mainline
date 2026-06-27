#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="${ROOT}/code/build-host"
BIN="${BUILD}/front_car_mainline"
OUT="${ROOT}/.diag/straight_audit"
REPORT_KEYS='^(line_found|ipm_source|atg_track_type|atg_cross_type|atg_circle_type|atg_round_type|atg_yroad_type|atg_ramp_type|atg_road_type|atg_speed_type|atg_ipts0_num|atg_ipts1_num|atg_rpts0s_num|atg_rpts1s_num|atg_rptsn_num|atg_lpt0_found|atg_lpt1_found|atg_is_straight0|atg_is_straight1|mid_step|control_ref|control_center_x|guide_error)='

mkdir -p "${OUT}"

if [[ ! -f "${BUILD}/Makefile" ]]; then
    bash "${ROOT}/test.sh" --host --reconfigure
fi
cmake --build "${BUILD}" --target front_car_mainline -j"${MAKE_JOBS:-$(nproc)}"

if [[ $# -eq 0 ]]; then
    set -- \
        ".diag/front_car_capture_live_current.png" \
        ".diag/front_car_capture_live_baseline.png"
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

    echo "====${img}===="
    "${BIN}" --analyze "${ROOT}/${img}" --report "${rpt}" >"${log}" 2>&1
    cat "${log}"
    echo "----REPORT----"
    grep -E "${REPORT_KEYS}" "${rpt}" || true
done
exit "${status}"
