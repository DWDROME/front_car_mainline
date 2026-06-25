#!/bin/bash
set -euo pipefail

TASK_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "${TASK_DIR}/../../.." && pwd)"

BOARD_HOST="${BOARD_HOST:-192.168.0.101}"
BOARD_USER="${BOARD_USER:-root}"
BOARD_BIN="${BOARD_BIN:-/root/front_car_mainline}"
LOCAL_BIN="${LOCAL_BIN:-code/build/front_car_mainline}"
LOG_DIR="${LOG_DIR:-logs/live-circle}"
RUN_DIR="${RUN_DIR:-${TASK_DIR}/runs}"
DURATION="${DURATION:-6}"
MAKE_JOBS="${MAKE_JOBS:-$(nproc)}"
FRONT_CAR_DISPLAY="${FRONT_CAR_DISPLAY:-0}"
SMARTCAR_ASSISTANT="${SMARTCAR_ASSISTANT:-1}"
SMARTCAR_VIEWER="${SMARTCAR_VIEWER:-1}"
SMARTCAR_ASSISTANT_IP="${SMARTCAR_ASSISTANT_IP:-192.168.0.100}"
SMARTCAR_ASSISTANT_PORT="${SMARTCAR_ASSISTANT_PORT:-8086}"
SMARTCAR_ASSISTANT_DIV="${SMARTCAR_ASSISTANT_DIV:-20}"

usage() {
    cat <<EOF
用法:
  $0 verify-build
  $0 upload
  $0 run <drive_id> [duration_seconds]
  $0 review <drive_id|log_path>
  $0 all <drive_id> [duration_seconds]

环境变量:
  BOARD_HOST=${BOARD_HOST}
  BOARD_USER=${BOARD_USER}
  BOARD_BIN=${BOARD_BIN}
  LOCAL_BIN=${LOCAL_BIN}
  LOG_DIR=${LOG_DIR}
  DURATION=${DURATION}
  FRONT_CAR_DISPLAY=${FRONT_CAR_DISPLAY}
  SMARTCAR_ASSISTANT=${SMARTCAR_ASSISTANT}
  SMARTCAR_VIEWER=${SMARTCAR_VIEWER}
  SMARTCAR_ASSISTANT_IP=${SMARTCAR_ASSISTANT_IP}
  SMARTCAR_ASSISTANT_PORT=${SMARTCAR_ASSISTANT_PORT}
  SMARTCAR_ASSISTANT_DIV=${SMARTCAR_ASSISTANT_DIV}

说明:
  verify-build 只做本地构建和 host parser 测试。
  upload 只上传当前交叉编译产物到板端，不启动跑车。
  run 会杀旧进程、启动 FRONT_CAR_ENABLE_DRIVE=1、等待固定窗口、停进程并拉回日志。
  review 只复盘已有日志，不改代码、不连接板子。
EOF
}

require_run_id() {
    if [[ $# -lt 1 || -z "${1:-}" ]]; then
        echo "[ERROR] missing drive_id, example: drive15" >&2
        exit 1
    fi
}

commit_short() {
    git -C "${ROOT}" rev-parse --short HEAD
}

log_path_for_run() {
    local run_id="$1"
    printf "%s/20260621-%s-front_car_circle_%s.log" "${LOG_DIR}" "${run_id}" "${run_id}"
}

remote_log_for_run() {
    local run_id="$1"
    printf "/tmp/front_car_circle_%s.log" "${run_id}"
}

summary_path_for_run() {
    local run_id="$1"
    printf "%s/%s.summary.md" "${RUN_DIR}" "${run_id}"
}

enter_root() {
    cd "${ROOT}"
}

verify_build() {
    enter_root
    mkdir -p "${LOG_DIR}" "${RUN_DIR}"
    git status --short --branch
    git rev-parse --short HEAD
    git diff --check
    cmake --build code/build-host -j"${MAKE_JOBS}"
    cmake --build code/build -j"${MAKE_JOBS}"
    (
        cd code/build-host
        ./config_parsing_test
        ./options_parsing_test
    )
}

upload_binary() {
    enter_root
    if [[ ! -x "${LOCAL_BIN}" ]]; then
        echo "[ERROR] missing local binary: ${LOCAL_BIN}" >&2
        echo "Run: $0 verify-build" >&2
        exit 1
    fi

    scp -O "${LOCAL_BIN}" "${BOARD_USER}@${BOARD_HOST}:/tmp/front_car_mainline.new"
    ssh -o BatchMode=yes -o ConnectTimeout=3 "${BOARD_USER}@${BOARD_HOST}" \
        "mv -f /tmp/front_car_mainline.new '${BOARD_BIN}' && chmod +x '${BOARD_BIN}' && ls -l '${BOARD_BIN}'"
}

run_live() {
    require_run_id "$@"
    local run_id="$1"
    local duration="${2:-${DURATION}}"
    local remote_log
    local local_log
    local summary
    remote_log="$(remote_log_for_run "${run_id}")"
    local_log="$(log_path_for_run "${run_id}")"
    summary="$(summary_path_for_run "${run_id}")"

    enter_root
    mkdir -p "${LOG_DIR}" "${RUN_DIR}"

    {
        echo "# ${run_id}"
        echo
        echo "- commit: $(commit_short)"
        echo "- board: ${BOARD_USER}@${BOARD_HOST}"
        echo "- binary: ${BOARD_BIN}"
        echo "- duration_seconds: ${duration}"
        echo "- local_log: ${local_log}"
        echo "- remote_log: ${remote_log}"
        echo "- started_at: $(date -Iseconds)"
        echo
        echo "## Commands"
        echo
        echo '```bash'
        echo "$0 run ${run_id} ${duration}"
        echo '```'
        echo
    } >"${summary}"

    ssh -o BatchMode=yes -o ConnectTimeout=3 "${BOARD_USER}@${BOARD_HOST}" \
        "killall -9 front_car_mainline 2>/dev/null || true; \
         cd /root; \
         env FRONT_CAR_ENABLE_DRIVE=1 \
             FRONT_CAR_CIRCLE_CAL_LOG=1 \
             FRONT_CAR_DISPLAY='${FRONT_CAR_DISPLAY}' \
             SMARTCAR_ASSISTANT='${SMARTCAR_ASSISTANT}' \
             SMARTCAR_VIEWER='${SMARTCAR_VIEWER}' \
             SMARTCAR_ASSISTANT_IP='${SMARTCAR_ASSISTANT_IP}' \
             SMARTCAR_ASSISTANT_PORT='${SMARTCAR_ASSISTANT_PORT}' \
             SMARTCAR_ASSISTANT_DIV='${SMARTCAR_ASSISTANT_DIV}' \
             FRONT_CAR_PROCESS_FPS=120 \
             FRONT_CAR_PRINT_DIV=1 \
             '${BOARD_BIN}' >'${remote_log}' 2>&1 & \
         echo \$! >/tmp/front_car_circle_${run_id}.pid; \
         cat /tmp/front_car_circle_${run_id}.pid"

    sleep "${duration}"

    ssh -o BatchMode=yes -o ConnectTimeout=3 "${BOARD_USER}@${BOARD_HOST}" \
        "killall -9 front_car_mainline 2>/dev/null || true; \
         wc -l '${remote_log}'; \
         tail -80 '${remote_log}'" | tee -a "${summary}"

    scp -O "${BOARD_USER}@${BOARD_HOST}:${remote_log}" "${local_log}"
    {
        echo
        echo "- stopped_at: $(date -Iseconds)"
        echo
        echo "## Review"
        echo
        echo '```bash'
        echo "$0 review ${run_id}"
        echo '```'
    } >>"${summary}"
}

resolve_log_path() {
    local input="$1"
    if [[ -f "${input}" ]]; then
        printf "%s" "${input}"
        return 0
    fi
    local candidate
    candidate="$(log_path_for_run "${input}")"
    if [[ -f "${candidate}" ]]; then
        printf "%s" "${candidate}"
        return 0
    fi
    echo "[ERROR] log not found: ${input}" >&2
    echo "Tried: ${candidate}" >&2
    exit 1
}

review_log() {
    require_run_id "$@"
    local input="$1"
    local log
    log="$(resolve_log_path "${input}")"

    echo "## Log"
    echo "${log}"
    echo

    echo "## Circle diagnostic events"
    rg -n "ATGCircleCal|ATGCircleReset|ATGCircleStall|ATGCircleSuppress|ATGCircleEndRelease|ATGCircleFarline|ATGCircleLptWindow|ATGCircleOutEvidence|ATGCircleSelectEvidence" "${log}" | sed -n '1,260p' || true
    echo

    echo "## Circle state frames"
    rg -n "circle=[1-9]\\(" "${log}" | sed -n '1,220p' || true
    echo

    echo "## Key circle states"
    rg -n "circle=1\\(|circle=3\\(|circle=5\\(|circle=7\\(|circle=9\\(" "${log}" | sed -n '1,160p' || true
    echo

    echo "## Entry candidate statistics"
    python3 - "${log}" <<'PY'
from pathlib import Path
import re
import sys

log = Path(sys.argv[1])
left = []
right = []

for line in log.open(errors="ignore"):
    if not line.startswith("frame="):
        continue
    toks = {}
    for part in line.split():
        if "=" in part:
            k, v = part.split("=", 1)
            toks[k] = v

    m = re.match(r"(\d+)@(-?\d+)/(\d+)@(-?\d+)", toks.get("l", ""))
    if not m:
        continue
    lf, lid, rf, rid = map(int, m.groups())

    try:
        s0, s1 = map(int, toks.get("straight", "").split("/")[:2])
    except Exception:
        continue

    row = (
        toks.get("frame"),
        toks.get("near"),
        toks.get("raw"),
        toks.get("l"),
        toks.get("straight"),
        toks.get("conf"),
        toks.get("guide"),
        toks.get("yaw"),
        toks.get("road"),
    )

    if lf and not rf and s1 and lid < 25:
        left.append(row)
    if (not lf) and rf and s0 and rid < 25:
        right.append(row)

print("left_entry_candidates:", len(left))
for row in left[:20]:
    print(row)

print("right_entry_candidates:", len(right))
for row in right[:20]:
    print(row)
PY
}

run_all() {
    require_run_id "$@"
    verify_build
    upload_binary
    run_live "$@"
    review_log "$1"
}

cmd="${1:-}"
case "${cmd}" in
    verify-build)
        shift
        verify_build "$@"
        ;;
    upload)
        shift
        upload_binary "$@"
        ;;
    run)
        shift
        run_live "$@"
        ;;
    review)
        shift
        review_log "$@"
        ;;
    all)
        shift
        run_all "$@"
        ;;
    -h|--help|help)
        usage
        ;;
    *)
        usage >&2
        exit 1
        ;;
esac
