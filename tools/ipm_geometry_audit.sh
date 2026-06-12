#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="${ROOT}/code/build-host"
BIN="${BUILD}/front_car_mainline"
OUT="${ROOT}/.diag/ipm_geometry_audit"
REPORT_KEYS='^(line_found|track_reject_reason|track_type|ipm_source|seed_ipm_pair_diag|ring_kind|ring_state|cross_state|zebra_detected|zebra_stop_line|left_seed|right_seed|seed_width|left_trace_step|right_trace_step|mid_step|center_x|guide_error)='

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
        --disable-cross \
        --ipm "${ipm}" \
        --report "${rpt}" >"${log}" 2>&1
    cat "${log}"
    echo "----REPORT----"
    grep -E "${REPORT_KEYS}" "${rpt}" || true
done
exit "${status}"
