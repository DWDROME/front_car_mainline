#!/bin/bash
set -euo pipefail

export PATH=/opt/ls_2k0300_env/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.6/bin:$PATH

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TARGET="front_car_mainline"
KEY_BIN="key_supervisor"
BUILD="${ROOT}/build"
BUILD_HOST="${ROOT}/build-host"
REMOTE_IP="${REMOTE_IP:-ls2k0300}"
REMOTE_USER="${REMOTE_USER:-root}"
REMOTE_PATH="${REMOTE_PATH:-/root/}"
MAKE_JOBS="${MAKE_JOBS:-$(nproc)}"

CLEAN=0
RECONF=0
UPLOAD=0
HOST=0

usage() {
    cat <<EOF
用法:
  ./test.sh
  ./test.sh --host
  ./test.sh --reconfigure
  ./test.sh --clean
  ./test.sh --upload        # 只上传交叉编译产物，不能和 --host 同用
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --host)
            HOST=1
            ;;
        --clean)
            CLEAN=1
            RECONF=1
            ;;
        --reconfigure)
            RECONF=1
            ;;
        --upload)
            UPLOAD=1
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "[ERROR] 未知参数: $1" >&2
            exit 1
            ;;
    esac
    shift
done

if [[ ${HOST} -eq 1 ]]; then
    OUT="${BUILD_HOST}"
    CMAKE_OPT="-DSMARTCAR_CROSS_COMPILE=OFF"
else
    OUT="${BUILD}"
    CMAKE_OPT="-DSMARTCAR_CROSS_COMPILE=ON"
fi

# ==== 上传模式边界 ====
if [[ ${HOST} -eq 1 && ${UPLOAD} -eq 1 ]]; then
    echo "[ERROR] --upload 只能上传交叉编译产物，不能和 --host 同时使用" >&2
    exit 1
fi

mkdir -p "${OUT}"
cd "${OUT}"

if [[ ${CLEAN} -eq 1 ]]; then
    find . -mindepth 1 -maxdepth 1 -exec rm -rf {} +
fi

if [[ ${RECONF} -eq 1 || ! -f "Makefile" ]]; then
    cmake ${CMAKE_OPT} "${ROOT}"
fi

make -j"${MAKE_JOBS}"

if [[ ${HOST} -eq 1 ]]; then
    "${OUT}/cross_farline_reuse_test"
    "${OUT}/line_trace_contract_test"
    "${OUT}/boundary_contract_test"
    "${OUT}/element_entry_contract_test"
    "${OUT}/midline_lookahead_test"
    "${OUT}/search_center_learning_test"
    "${OUT}/element_deferred_mode_test"
    "${OUT}/ring_opp_diag_test"
    "${OUT}/config_parsing_test"
    "${OUT}/options_parsing_test"
fi

if [[ ${UPLOAD} -eq 1 ]]; then
    TMP="/tmp"
    ssh "${REMOTE_USER}@${REMOTE_IP}" "mkdir -p ${REMOTE_PATH}"
    scp -O "${TARGET}" "${REMOTE_USER}@${REMOTE_IP}:${TMP}/${TARGET}.new"
    ssh "${REMOTE_USER}@${REMOTE_IP}" "mv -f ${TMP}/${TARGET}.new ${REMOTE_PATH}/${TARGET}"
    scp -O "${KEY_BIN}" "${REMOTE_USER}@${REMOTE_IP}:${TMP}/${KEY_BIN}.new"
    ssh "${REMOTE_USER}@${REMOTE_IP}" "mv -f ${TMP}/${KEY_BIN}.new ${REMOTE_PATH}/${KEY_BIN}"
fi
