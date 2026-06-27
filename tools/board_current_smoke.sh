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
REPORT_KEYS='^(line_found|ipm_source|atg_track_type|atg_cross_type|atg_circle_type|atg_round_type|atg_yroad_type|atg_ramp_type|atg_rpts0s_num|atg_rpts1s_num|atg_rptsn_num|atg_lpt0_found|atg_lpt1_found|atg_is_straight0|atg_is_straight1|mid_step|control_ref|guide_error)='

mkdir -p "${OUT}"

if [[ ! -f "${BUILD}/Makefile" ]]; then
    bash "${ROOT}/test.sh" --host --reconfigure
fi
cmake --build "${BUILD}" --target front_car_mainline -j"${MAKE_JOBS:-$(nproc)}"

ssh -o BatchMode=yes -o ConnectTimeout=3 "${REMOTE_USER}@${REMOTE_IP}" \
    "FRONT_CAR_DISPLAY=0 SMARTCAR_ASSISTANT=0 ${REMOTE_BIN} --capture-frame ${REMOTE_IMG}"

ssh -o BatchMode=yes -o ConnectTimeout=3 "${REMOTE_USER}@${REMOTE_IP}" \
    "FRONT_CAR_DISPLAY=0 SMARTCAR_ASSISTANT=0 ${REMOTE_BIN} --analyze ${REMOTE_IMG} --report ${REMOTE_RPT} >${REMOTE_LOG} 2>&1"

scp -O "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_IMG}" "${OUT}/capture.png"
scp -O "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_RPT}" "${OUT}/report.txt"

"${BIN}" \
    --analyze "${OUT}/capture.png" \
    --ipm "${OUT}/ipm.png" \
    --report "${OUT}/host_report.txt" >/tmp/front_car_board_current_host.log 2>&1

echo "----BOARD REPORT----"
grep -E "${REPORT_KEYS}" "${OUT}/report.txt" || true

echo "----HOST REPORT----"
grep -E "${REPORT_KEYS}" "${OUT}/host_report.txt" || true
