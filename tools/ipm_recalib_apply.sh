#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
REPO_ROOT="$(cd "${ROOT}/.." && pwd)"
AUTOCAL_DIR="${REPO_ROOT}/ipm_autocal"

MATRIX_FILE="${1:-${AUTOCAL_DIR}/.agentdocs/runtime/ipm_manual_pick/ipm_matrix.txt}"
REMOTE_IP="${REMOTE_IP:-192.168.0.102}"
REMOTE_USER="${REMOTE_USER:-root}"
REMOTE_MATRIX="${REMOTE_MATRIX:-/root/ipm_matrix.txt}"

SSH_OPTS=(
  -o StrictHostKeyChecking=no
)

if [[ ! -f "${MATRIX_FILE}" ]]; then
  echo "ERROR: matrix file not found: ${MATRIX_FILE}" >&2
  exit 1
fi

scp "${SSH_OPTS[@]}" "${MATRIX_FILE}" "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_MATRIX}.new"
ssh "${SSH_OPTS[@]}" "${REMOTE_USER}@${REMOTE_IP}" \
  "install -m 644 '${REMOTE_MATRIX}.new' '${REMOTE_MATRIX}' && rm -f '${REMOTE_MATRIX}.new' && cat '${REMOTE_MATRIX}'"

echo "Applied matrix -> ${REMOTE_USER}@${REMOTE_IP}:${REMOTE_MATRIX}"
