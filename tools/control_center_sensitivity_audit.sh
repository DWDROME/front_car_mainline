#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="${ROOT}/code/build-host"
BIN="${BUILD}/front_car_mainline"
OUT="${ROOT}/.diag/control_center_sensitivity"
CENTERS="${SMARTCAR_CENTER_SWEEP:-60 80}"
REPORT_KEYS='^(line_found|track_reject_reason|track_type|mid_position|control_center_x|left_seed|right_seed|seed_row|seed_width|left_trace_step|right_trace_step|center_x|guide_error)='

mkdir -p "${OUT}"

if [[ ! -f "${BUILD}/Makefile" ]]; then
    bash "${ROOT}/scripts/test.sh" --host --reconfigure
fi
cmake --build "${BUILD}" --target front_car_mainline -j"${MAKE_JOBS:-$(nproc)}"

if [[ $# -eq 0 ]]; then
    set -- \
        ".diag/front_car_capture_live_current.png" \
        ".diag/control_loop_center/capture.png" \
        ".diag/control_loop_left/capture.png" \
        ".diag/control_loop_left2/capture.png"
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
    for x in ${CENTERS}; do
        rpt="${OUT}/${stem}.center_${x}.report.txt"
        log="${OUT}/${stem}.center_${x}.log.txt"

        echo "====${img} center=${x}===="
        SMARTCAR_CONTROL_CENTER_X="${x}" \
            "${BIN}" --analyze "${ROOT}/${img}" --report "${rpt}" >"${log}" 2>&1
        cat "${log}"
        echo "----REPORT----"
        grep -E "${REPORT_KEYS}" "${rpt}" || true
    done
done
exit "${status}"
