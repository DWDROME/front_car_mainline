#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
REPO_ROOT="$(cd "${ROOT}/.." && pwd)"
AUTOCAL_DIR="${REPO_ROOT}/ipm_autocal"
OUT_DIR="${AUTOCAL_DIR}/.agentdocs/runtime/ipm_capture_only"
OUT_FILE="${OUT_DIR}/ipm_raw.png"

REMOTE_IP="${REMOTE_IP:-192.168.0.102}"
REMOTE_USER="${REMOTE_USER:-root}"
REMOTE_RAW="${REMOTE_RAW:-/tmp/ipm_raw_capture.png}"
REMOTE_CAPTURE_LOG="${REMOTE_CAPTURE_LOG:-/tmp/ipm_raw_capture.log}"

SSH_OPTS=(
  -o StrictHostKeyChecking=no
)

mkdir -p "${OUT_DIR}"

ssh "${SSH_OPTS[@]}" "${REMOTE_USER}@${REMOTE_IP}" \
  "killall -9 front_car_mainline 2>/dev/null || true; \
   rm -f '${REMOTE_RAW}' '${REMOTE_CAPTURE_LOG}'; \
   env SMARTCAR_ASSISTANT=0 FRONT_CAR_DISPLAY=0 SMARTCAR_UVC_WIDTH=160 SMARTCAR_UVC_HEIGHT=120 SMARTCAR_UVC_FPS=30 \
   /root/front_car_mainline --capture-frame '${REMOTE_RAW}' >'${REMOTE_CAPTURE_LOG}' 2>&1; \
   ls -l '${REMOTE_RAW}'"

scp "${SSH_OPTS[@]}" "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_RAW}" "${OUT_FILE}"

ssh "${SSH_OPTS[@]}" "${REMOTE_USER}@${REMOTE_IP}" \
  "env SMARTCAR_ASSISTANT=1 SMARTCAR_ASSISTANT_IP=192.168.0.101 SMARTCAR_ASSISTANT_PORT=8086 SMARTCAR_ASSISTANT_CONNECT_MS=30 SMARTCAR_ASSISTANT_RECONNECT_DIV=30 SMARTCAR_ASSISTANT_DIV=12 FRONT_CAR_DISPLAY=0 FRONT_CAR_PROCESS_FPS=120 FRONT_CAR_PRINT_DIV=30 FRONT_CAR_ENABLE_DRIVE=0 /root/front_car_mainline >/tmp/front_car_mainline.log 2>&1 &"

echo "Captured raw image -> ${OUT_FILE}"
