#!/bin/bash
set -euo pipefail

TASK_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "${TASK_DIR}/../../.." && pwd)"

BOARD_HOST="${BOARD_HOST:-192.168.0.101}"
BOARD_USER="${BOARD_USER:-root}"
BOARD_BIN="${BOARD_BIN:-/root/front_car_mainline}"
LOCAL_BIN="${LOCAL_BIN:-code/build/front_car_mainline}"
LOG_DIR="${LOG_DIR:-logs/live-cross}"
RUN_DIR="${RUN_DIR:-${TASK_DIR}/runs}"
DURATION="${DURATION:-8}"
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
EOF
}

require_run_id() {
    if [[ $# -lt 1 || -z "${1:-}" ]]; then
        echo "[ERROR] missing drive_id, example: drive01" >&2
        exit 1
    fi
}

commit_short() {
    git -C "${ROOT}" rev-parse --short HEAD
}

log_path_for_run() {
    local run_id="$1"
    printf "%s/20260622-%s-front_car_cross_%s.log" "${LOG_DIR}" "${run_id}" "${run_id}"
}

remote_log_for_run() {
    local run_id="$1"
    printf "/tmp/front_car_cross_%s.log" "${run_id}"
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
             FRONT_CAR_DISPLAY='${FRONT_CAR_DISPLAY}' \
             SMARTCAR_ASSISTANT='${SMARTCAR_ASSISTANT}' \
             SMARTCAR_VIEWER='${SMARTCAR_VIEWER}' \
             SMARTCAR_ASSISTANT_IP='${SMARTCAR_ASSISTANT_IP}' \
             SMARTCAR_ASSISTANT_PORT='${SMARTCAR_ASSISTANT_PORT}' \
             SMARTCAR_ASSISTANT_DIV='${SMARTCAR_ASSISTANT_DIV}' \
             FRONT_CAR_PROCESS_FPS=120 \
             FRONT_CAR_PRINT_DIV=1 \
             '${BOARD_BIN}' >'${remote_log}' 2>&1 & \
         echo \$! >/tmp/front_car_cross_${run_id}.pid; \
         cat /tmp/front_car_cross_${run_id}.pid"

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

    echo "## Cross diagnostic events"
    rg -n "cross=|CrossDiag|truncate_cross|CROSS_HALF|CROSS_BEGIN|CROSS_IN|cross_type=" "${log}" | sed -n '1,260p' || true
    echo

    echo "## Cross state frames (cross != 0)"
    rg -n "cross=[1-9]" "${log}" | sed -n '1,220p' || true
    echo

    echo "## Cross entry candidate frames (cross=0, far_l found)"
    python3 - "${log}" <<'PY'
import re
import sys

log_path = sys.argv[1]
frames = []
with open(log_path, errors="ignore") as f:
    for line in f:
        if not line.startswith("frame="):
            continue
        toks = {}
        for part in line.split():
            if "=" in part:
                k, v = part.split("=", 1)
                toks[k] = v

        frame = int(toks.get("frame", -1))
        cross = int(toks.get("cross", "0"))
        near = toks.get("near", "0/0")
        center = toks.get("center", "0/0")
        sel = toks.get("sel", "0/0")
        l = toks.get("l", "0@-1/0@-1")
        far_l = toks.get("far_l", "0@-1/0@-1")
        far_raw = toks.get("far_raw", "0/0")
        far_num = toks.get("far", "0/0")
        guide = toks.get("guide", "0")
        yaw = toks.get("yaw", "0")
        ml = toks.get("ml", "(-1,-1)")
        road = toks.get("road", "0")
        source = toks.get("source", "")

        # 十字候选帧：cross=0 但有 far_L 证据
        m = re.match(r"(\d+)@(-?\d+)/(\d+)@(-?\d+)", far_l)
        far_l0_f, far_l0_id, far_l1_f, far_l1_id = (0, -1, 0, -1)
        if m:
            far_l0_f, far_l0_id, far_l1_f, far_l1_id = map(int, m.groups())

        # 十字活跃帧
        if cross != 0:
            frames.append((frame, cross, near, center, sel, far_l, guide, yaw, ml, road, source))

    print(f"cross_active_frames: {len(frames)}")
    print()
    print("frame cross near center sel far_l guide yaw ml road source")
    for row in frames[:80]:
        print(f"  {row[0]:>5}  cross={row[1]}  near={row[2]}  center={row[3]}  sel={row[4]}  far_l={row[5]}  guide={row[6]:>6}  yaw={row[7]:>6}  ml={row[8]}  road={row[9]}  {row[10]}")
PY
    echo

    echo "## Entry truncation analysis"
    python3 - "${log}" <<'PY'
import re
import sys

log_path = sys.argv[1]
candidates = []
with open(log_path, errors="ignore") as f:
    for line in f:
        if not line.startswith("frame="):
            continue
        toks = {}
        for part in line.split():
            if "=" in part:
                k, v = part.split("=", 1)
                toks[k] = v

        frame = int(toks.get("frame", -1))
        cross = int(toks.get("cross", "0"))
        near = toks.get("near", "0/0")
        center = toks.get("center", "0/0")
        l = toks.get("l", "0@-1/0@-1")
        far_l = toks.get("far_l", "0@-1/0@-1")
        far_num = toks.get("far", "0/0")
        guide = toks.get("guide", "0")
        yaw = toks.get("yaw", "0")
        road = toks.get("road", "0")

        if cross != 0:
            continue

        m = re.match(r"(\d+)@(-?\d+)/(\d+)@(-?\d+)", l)
        l0_f, l0_id, l1_f, l1_id = (0, -1, 0, -1)
        if m:
            l0_f, l0_id, l1_f, l1_id = map(int, m.groups())

        m = re.match(r"(\d+)@(-?\d+)/(\d+)@(-?\d+)", far_l)
        far_l0_f, far_l0_id, far_l1_f, far_l1_id = (0, -1, 0, -1)
        if m:
            far_l0_f, far_l0_id, far_l1_f, far_l1_id = map(int, m.groups())

        # 左候选：近L + 远L + id<25  → 截断应生效
        left_candidate = l0_f and far_l0_f and l0_id < 25
        right_candidate = l1_f and far_l1_f and l1_id < 25

        if left_candidate or right_candidate:
            near_n0, near_n1 = map(int, near.split("/")[:2])
            center_n0, center_n1 = map(int, center.split("/")[:2])
            candidates.append((frame, "L" if left_candidate else "R",
                              l0_f, l0_id, l1_f, l1_id,
                              far_l0_f, far_l0_id, far_l1_f, far_l1_id,
                              near_n0, near_n1,
                              center_n0, center_n1,
                              far_num, guide, yaw, road))

    if not candidates:
        print("No cross entry candidates detected (no frame with near_L + far_L + id<25)")
        print("This may mean the car never approached a cross, or the threshold is too strict.")
        sys.exit(0)

    print(f"Cross entry candidates (cross=0, near_L+far_L, id<25): {len(candidates)} frames")
    print()
    print("frame side l0@id l1@id far_l0@id far_l1@id near0/1 center0/1 far_num guide  yaw  road")
    for row in candidates[:60]:
        frm, side, l0f, l0id, l1f, l1id, fl0f, fl0id, fl1f, fl1id, n0, n1, c0, c1, fn, g, y, r = row
        print(f"{frm:>5}  {side}  {l0f}@{l0id} {l1f}@{l1id}  {fl0f}@{fl0id} {fl1f}@{fl1id}  {n0:>2}/{n1:<2}  {c0:>2}/{c1:<2}  {fn:>4}  {g:>6}  {y:>6}  {r}")
        # 超过20个不再重复输出
    for row in candidates[60:]:
        print(f"  ... {len(candidates)-60} more frames ...")
        break
PY
    echo

    echo "## CrossDiag lines (last 60)"
    rg -n "CrossDiag:" "${log}" | tail -60 || true
    echo
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
