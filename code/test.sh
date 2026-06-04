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
  ./test.sh --upload
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

mkdir -p "${OUT}"
cd "${OUT}"

if [[ ${CLEAN} -eq 1 ]]; then
    find . -mindepth 1 -maxdepth 1 -exec rm -rf {} +
fi

if [[ ${RECONF} -eq 1 || ! -f "Makefile" ]]; then
    cmake ${CMAKE_OPT} "${ROOT}"
fi

make -j"${MAKE_JOBS}"

if [[ ${UPLOAD} -eq 1 ]]; then
    TMP="/tmp"
    ssh "${REMOTE_USER}@${REMOTE_IP}" "mkdir -p ${REMOTE_PATH}"
    scp -O "${TARGET}" "${REMOTE_USER}@${REMOTE_IP}:${TMP}/${TARGET}.new"
    ssh "${REMOTE_USER}@${REMOTE_IP}" "mv -f ${TMP}/${TARGET}.new ${REMOTE_PATH}/${TARGET}"
    scp -O "${KEY_BIN}" "${REMOTE_USER}@${REMOTE_IP}:${TMP}/${KEY_BIN}.new"
    ssh "${REMOTE_USER}@${REMOTE_IP}" "mv -f ${TMP}/${KEY_BIN}.new ${REMOTE_PATH}/${KEY_BIN}"
fi
