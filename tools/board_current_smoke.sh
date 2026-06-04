#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="${ROOT}/code/build-host"
BIN="${BUILD}/front_car_mainline"
OUT="${ROOT}/.diag/board_current"
REMOTE_IP="${REMOTE_IP:-ls2k0300}"
REMOTE_USER="${REMOTE_USER:-root}"
REMOTE_BIN="${REMOTE_BIN:-/root/front_car_mainline}"
REMOTE_IMG="/tmp/front_car_current_capture.png"
REMOTE_RPT="/tmp/front_car_current_capture_report.txt"
REMOTE_LOG="/tmp/front_car_current_capture_analyze.log"
REMOTE_MATRIX="${REMOTE_MATRIX:-/root/ipm_matrix.txt}"
REPORT_KEYS='^(line_found|track_type|track_reject_reason|matrix_loaded|ipm_geometry_reject_reason|ring_kind|ring_state|cross_state|zebra_detected|zebra_stop_line|seed_row|seed_width|left_trace_step|right_trace_step|center_x|guide_error)='

mkdir -p "${OUT}"

if [[ ! -f "${BUILD}/Makefile" ]]; then
    bash "${ROOT}/scripts/test.sh" --host --reconfigure
fi
cmake --build "${BUILD}" --target front_car_mainline -j"${MAKE_JOBS:-$(nproc)}"

ssh -o BatchMode=yes -o ConnectTimeout=3 "${REMOTE_USER}@${REMOTE_IP}" \
    "FRONT_CAR_DISPLAY=0 SMARTCAR_ASSISTANT=0 ${REMOTE_BIN} --capture-frame ${REMOTE_IMG}"

ssh -o BatchMode=yes -o ConnectTimeout=3 "${REMOTE_USER}@${REMOTE_IP}" \
    "FRONT_CAR_DISPLAY=0 SMARTCAR_ASSISTANT=0 ${REMOTE_BIN} --analyze ${REMOTE_IMG} --report ${REMOTE_RPT} >${REMOTE_LOG} 2>&1"

scp -O "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_IMG}" "${OUT}/capture.png"
scp -O "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_RPT}" "${OUT}/report.txt"
scp -O "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_MATRIX}" "${OUT}/ipm_matrix.txt" >/dev/null 2>&1 || true

FRONT_CAR_MATRIX="${OUT}/ipm_matrix.txt" "${BIN}" \
    --analyze "${OUT}/capture.png" \
    --ipm "${OUT}/ipm.png" \
    --report "${OUT}/host_report.txt" >/tmp/front_car_board_current_host.log 2>&1

echo "----BOARD REPORT----"
grep -E "${REPORT_KEYS}" "${OUT}/report.txt" || true

echo "----HOST REPORT----"
grep -E "${REPORT_KEYS}" "${OUT}/host_report.txt" || true
