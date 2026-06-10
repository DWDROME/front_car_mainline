#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CAMERA_PARAM_DST="${ROOT}/autop_reference/Project/CODE/camera_param.c"

CAMERA_PARAM_SRC="${1:-${ROOT}/.diag/ipm_recalib/camera_param.c}"

if [[ ! -f "${CAMERA_PARAM_SRC}" ]]; then
  echo "ERROR: camera_param.c not found: ${CAMERA_PARAM_SRC}" >&2
  exit 1
fi

for symbol in \
  "float K\\[3\\]\\[3\\]" \
  "float D\\[4\\]" \
  "float H\\[3\\]\\[3\\]" \
  "float H_inv\\[3\\]\\[3\\]" \
  "float mapx\\[MT9V03X_CSI_H\\]\\[MT9V03X_CSI_W\\]" \
  "float mapy\\[MT9V03X_CSI_H\\]\\[MT9V03X_CSI_W\\]" \
  "int invx\\[MT9V03X_CSI_H\\]\\[MT9V03X_CSI_W\\]" \
  "int invy\\[MT9V03X_CSI_H\\]\\[MT9V03X_CSI_W\\]" \
  "bool map_inv"; do
  if ! grep -q "${symbol}" "${CAMERA_PARAM_SRC}"; then
    echo "ERROR: generated camera_param.c missing symbol pattern: ${symbol}" >&2
    exit 1
  fi
done

install -m 644 "${CAMERA_PARAM_SRC}" "${CAMERA_PARAM_DST}"
echo "Applied camera_param.c -> ${CAMERA_PARAM_DST}"
