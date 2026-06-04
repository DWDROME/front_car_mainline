#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="${ROOT}/code/build-host"
BIN="${BUILD}/front_car_mainline"
OUT="${ROOT}/.diag/straight_audit"
REPORT_KEYS='^(line_found|track_reject_reason|track_type|ring_kind|ring_state|cross_state|zebra_detected|zebra_stop_line|mid_position|control_center_x|left_seed|right_seed|seed_row|seed_width|left_trace_step|right_trace_step|center_x|guide_error)='

mkdir -p "${OUT}"

if [[ ! -f "${BUILD}/Makefile" ]]; then
    bash "${ROOT}/scripts/test.sh" --host --reconfigure
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
