#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_DIR="${ROOT}/.diag/ipm_recalib"
OUT_RAW="${OUT_DIR}/ipm_raw_160x120.png"
OUT_INPUT="${OUT_DIR}/ipm_raw_640x360.png"

REMOTE_IP="${REMOTE_IP:-ls2k0300}"
REMOTE_USER="${REMOTE_USER:-root}"
ASSISTANT_IP="${ASSISTANT_IP:-192.168.0.100}"
REMOTE_RAW="${REMOTE_RAW:-/tmp/ipm_raw_capture.png}"
REMOTE_CAPTURE_LOG="${REMOTE_CAPTURE_LOG:-/tmp/ipm_raw_capture.log}"

SSH_OPTS=(
  -o StrictHostKeyChecking=no
)

mkdir -p "${OUT_DIR}"

if ! command -v ffmpeg >/dev/null 2>&1; then
  echo "ERROR: ffmpeg is required to create ${OUT_INPUT}" >&2
  exit 1
fi

ssh "${SSH_OPTS[@]}" "${REMOTE_USER}@${REMOTE_IP}" \
  "killall -9 front_car_mainline 2>/dev/null || true; \
   rm -f '${REMOTE_RAW}' '${REMOTE_CAPTURE_LOG}'; \
   env SMARTCAR_ASSISTANT=0 FRONT_CAR_DISPLAY=0 SMARTCAR_UVC_WIDTH=160 SMARTCAR_UVC_HEIGHT=120 SMARTCAR_UVC_FPS=30 \
   /root/front_car_mainline --capture-frame '${REMOTE_RAW}' >'${REMOTE_CAPTURE_LOG}' 2>&1; \
   ls -l '${REMOTE_RAW}'"

scp "${SSH_OPTS[@]}" "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_RAW}" "${OUT_RAW}"
ffmpeg -hide_banner -loglevel error -y \
  -i "${OUT_RAW}" \
  -vf "scale=640:360:flags=neighbor,format=gray" \
  "${OUT_INPUT}"

ssh "${SSH_OPTS[@]}" "${REMOTE_USER}@${REMOTE_IP}" \
  "env SMARTCAR_ASSISTANT=1 SMARTCAR_ASSISTANT_IP='${ASSISTANT_IP}' SMARTCAR_ASSISTANT_PORT=8086 SMARTCAR_ASSISTANT_CONNECT_MS=30 SMARTCAR_ASSISTANT_RECONNECT_DIV=30 SMARTCAR_ASSISTANT_DIV=12 FRONT_CAR_DISPLAY=0 FRONT_CAR_PROCESS_FPS=120 FRONT_CAR_PRINT_DIV=30 FRONT_CAR_ENABLE_DRIVE=0 /root/front_car_mainline >/tmp/front_car_mainline.log 2>&1 &"

echo "Captured raw image -> ${OUT_RAW}"
echo "Calibration input -> ${OUT_INPUT}"
echo "Board SSH target -> ${REMOTE_USER}@${REMOTE_IP}"
echo "Assistant target -> ${ASSISTANT_IP}:8086"
