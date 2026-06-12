#!/bin/bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GEN_DIR="${ROOT}/tools/ipm_generator"
BUILD_DIR="${GEN_DIR}/build"
INPUT="${1:-${ROOT}/.diag/ipm_recalib/ipm_raw_640x360.png}"
OUT_DIR="${2:-${ROOT}/.diag/ipm_recalib}"
shift $(( $# > 0 ? 1 : 0 ))
shift $(( $# > 0 ? 1 : 0 ))

cmake -S "${GEN_DIR}" -B "${BUILD_DIR}"
cmake --build "${BUILD_DIR}"
"${BUILD_DIR}/ipm_generator" --input "${INPUT}" --out "${OUT_DIR}" "$@"

echo "Generated IPM matrix -> ${OUT_DIR}/ipm_matrix_tuned.txt"
echo "Generated compatibility camera_param.c -> ${OUT_DIR}/camera_param.c"
