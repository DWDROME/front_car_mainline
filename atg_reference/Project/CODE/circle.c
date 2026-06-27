/* =====================================================================
 *  圆环检测与状态机
 *
 *  整体流程：
 *
 *    ┌─────────────────────────────────────────────────────────────────┐
 *    │  NONE ──(投票)──► ENTRY ──(B稳定)──► BEGIN ──(陀螺仪)──► RUNNING │
 *    │    ▲                                                      │    │
 *    │    │                                                      ▼    │
 *    │    └──────(直道确认)────── OUT ◄──────(出环条件)────────────┘    │
 *    └─────────────────────────────────────────────────────────────────┘
 *
 *  各阶段任务：
 *
 *  ENTRY — 找到入口参考点
 *    1. 投票确认：本侧有 L 点、对侧是直道，连续 2 帧命中才进 ENTRY
 *    2. 锁定 A（入口近端拐点），从 A 出发沿弯道边界找 B（外侧极值点）
 *    3. B 的 y 坐标超过 B_READY_Y 且连续稳定 → 进入 BEGIN
 *    4. 如果 A 太近但一直没见过 B → 撤回（假入口）
 *
 *  BEGIN — 建立入环参考，等待进环
 *    1. 在 B 附近 ±8px 窄窗跟踪 B 漂移
 *    2. 从 B 往上找 C（弯道最深处角点），用局部角度 NMS 检测
 *    3. C 稳定 → 切换到 C 参考（更深的入环基准）；否则用 B 兜底
 *    4. 陀螺仪累计转角 ≥ 60° → 进入 RUNNING
 *    5. 口部丢失过晚（行驶距离 > 4000）→ 撤回（假入口）
 *
 *  RUNNING — 环内行驶
 *    不再找 A/B/C，只靠陀螺仪和对侧 L 点判断出环：
 *    - 对侧 L 点 id < 55 且陀螺仪 ≥ 150° → 出环（视觉+陀螺仪联合）
 *    - 陀螺仪 ≥ 200° → 强制出环
 *
 *  OUT — 出环恢复
 *    切到对侧巡线，连续 2 帧检测到直道 → 回到 NONE
 *    退出后抑制 150 帧，防止立刻重新误触发
 *
 *  A/B/C 锚点说明：
 *    A — 入口近端拐点，由 L 点（局部极值点）锁定
 *    B — 圆环外侧远端极值点，在 A 的上方且向内侧偏移
 *    C — 弯道最深处角点，由局部角度 NMS 检测
 *
 *  坐标系：raw_x/raw_y 是逆旋转后的图像坐标（raw 图空间）。
 *  左环 = CIRCLE_SIDE_LEFT，右环 = CIRCLE_SIDE_RIGHT。
 * ===================================================================== */
#include "circle.h"
#include "atg_reference_step.h"
#include "motor.h"
#include "headfile.h"
#include "imgproc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= 左右方向工具 ================= */

/* side 参数统一编码：0 = RIGHT，1 = LEFT。
 * 所有 side_* 函数都通过 side_index() 做归一化，避免调用方记错编码。
 *
 * 关键映射：
 *   side_lpt_found/id  →  Lpt0/1_found, Lpt0/1_rpts0/1s_id（本侧 L 点）
 *   side_rpts_num      →  rpts0/1s_num（本侧线点数）
 *   side_opposite_*    →  对侧 L 点和直道状态
 *   side_begin_track   →  左环跟右线，右环跟左线（跟内侧）
 *   side_out_track     →  切到对侧巡线 */
enum circle_side_e
{
    CIRCLE_SIDE_RIGHT = 0,
    CIRCLE_SIDE_LEFT = 1,
};

typedef struct circle_point_s
{
    int x;
    int y;
} circle_point_t;

/* ================= 圆环状态门：真正决定流程 ================= */

/* 这些常量是状态机的核心，改一个值就能改变整个行为。
 * 连续帧门槛防止噪声误触发；陀螺仪门槛控制进/出环时机。 */
enum
{
    /* --- 连续帧门槛：投票 / B 稳定 / C 稳定都需要连续 N 帧达标才放行 --- */
    ENTRY_OK_FRAMES = 2,        /* 入环投票连续 2 帧命中才进 ENTRY */
    B_OK_FRAMES = 2,            /* B 点连续 2 帧 ready 才从 ENTRY 进 BEGIN */
    C_OK_FRAMES = 2,            /* C 点连续 2 帧稳定才启用 C 参考 */

    /* --- 陀螺仪转角门槛（单位 0.1°）---
     * 这些值决定了状态切换的时机，需要上车标定：
     * - 太小：还没进环就切状态，参考点丢失
     * - 太大：已经在环里了还没切状态，巡线偏移 */
    GYRO_IN_DEG10 = 600,        /* BEGIN→RUNNING：累计转 60° 认为已进环 */
    GYRO_OUT_DEG10 = 1500,      /* RUNNING→OUT：视觉+陀螺仪联合，转 150° 且看到出口 */
    GYRO_FORCE_OUT_DEG10 = 2000, /* RUNNING→OUT：强制出环，转 200° 不管视觉 */

    /* --- 其他门控 --- */
    B_READY_Y = 58,             /* B 点 y 坐标超过此值才算"够远"，可以推进状态 */
    OUT_LPT_NEAR_ID = 55,       /* 出环时对侧 L 点 id 小于此值才认为"看到出口" */
    OUT_STRAIGHT_FRAMES = 2,    /* OUT 阶段连续 2 帧检测到直道就退出圆环 */
    REENTRY_SUPPRESS_FRAMES = 150, /* 退出后抑制 150 帧，防止立刻重新误触发 */
};

/* B/C 搜索结果码，用于日志和调试 */
enum
{
    CIRCLE_POINT_SEARCH_OK = 0,         /* 找到可信点 */
    CIRCLE_POINT_SEARCH_NO_A,           /* 没有锁定 A */
    CIRCLE_POINT_SEARCH_NO_B,           /* trace 里没有候选点 */
    CIRCLE_POINT_SEARCH_NO_EXTREME,     /* 有候选但不满足极值条件 */
    CIRCLE_POINT_SEARCH_NO_V,           /* C 搜索：trace 里没有角点 */
    CIRCLE_POINT_SEARCH_PHASE_GATE,     /* B 还没 ready，C 搜索被门控 */
    CIRCLE_POINT_SEARCH_NO_SEED,        /* 找不到预测 seed */
    CIRCLE_POINT_SEARCH_NO_TRACE,       /* trace 太短或断掉 */
    CIRCLE_POINT_SEARCH_NO_SLOPE,       /* 对面线太短，无法算预测斜率 */
    CIRCLE_POINT_SEARCH_JOIN_BAD,       /* C 点与 B 点的连接关系不合格 */
};

static const float CIRCLE_GYRO_DEADZONE_RAD_S = 0.065f; /* 陀螺仪死区，低于此值不积分 */
static const float CIRCLE_RAD_TO_DEG10 = 1800.0f / 3.14159265358979f; /* rad → 0.1° 换算系数 */

/* ================= 圆环全局状态 ================= */

/* 这些变量是状态机的"记忆"，在状态切换时被重置。
 * circle_type 是核心：决定 run_circle() 每帧执行哪个分支。 */
int circle_count;                                    /* 累计完成的圆环次数 */
enum circle_type_e circle_type = CIRCLE_NONE;        /* 当前状态机阶段 */
enum circle_ref_mode_e circle_ref_mode = CIRCLE_REF_NONE; /* 当前使用的参考点模式 */

/* A/B/C 三个锚点，随状态推进逐步建立：
 *   ENTRY: 建立 A，尝试找 B
 *   BEGIN: 建立 B，尝试找 C
 *   RUNNING: 不再使用，全部清除 */
circle_anchor_point_t circle_A_point;                /* A — 入口近端拐点 */
circle_anchor_point_t circle_B_point;                /* B — 圆环外侧远端极值点 */
circle_anchor_point_t circle_C_point;                /* C — 弯道最深处角点 */

int none_left_line = 0, none_right_line = 0;         /* BEGIN 阶段本侧线丢失计数 */
int have_left_line = 0, have_right_line = 0;         /* 已废弃，保留兼容 */

const char *circle_type_name[CIRCLE_NUM] = {
    "CIRCLE_NONE",
    "CIRCLE_LEFT_ENTRY", "CIRCLE_RIGHT_ENTRY",
    "CIRCLE_LEFT_BEGIN", "CIRCLE_RIGHT_BEGIN",
    "CIRCLE_LEFT_RUNNING", "CIRCLE_RIGHT_RUNNING",
    "CIRCLE_LEFT_OUT", "CIRCLE_RIGHT_OUT",
};

/* --- 入环投票与抑制 --- */
static int circle_entry_votes[2];                    /* 左右两侧连续命中帧数 */
static circle_anchor_point_t circle_entry_pending_A[2]; /* 投票期间暂存的 A 点 */
static int circle_entry_ever_valid_B[2];             /* ENTRY 阶段是否曾经见过有效 B */
static int circle_entry_suppress_frames;             /* 剩余抑制帧数，>0 时跳过入环检测 */

/* --- 陀螺仪积分 --- */
static float circle_heading_rad;                     /* 圆环内累计转角（rad） */

/* --- BEGIN 阶段丢失跟踪 --- */
static int circle_begin_lost_streak[2];              /* 本侧线连续丢失帧数 */
static int64_t circle_loss_start_begin_dist[2] = {-1, -1}; /* 丢失开始时的 begin_dist */

/* --- OUT 阶段直道检测 --- */
static int circle_out_straight_streak[2];            /* 出环后连续直道帧数 */

/* --- B/C 稳定计数 --- */
static int circle_B_streak;                          /* B 连续 ready 帧数 */
static int circle_C_streak;                          /* C 连续稳定帧数 */
static int circle_C_join_ok;                         /* C 与 B 的连接关系是否合格 */
static int circle_B_follow_fail_streak[2];           /* B_follow 连续失败帧数 */

/* --- seed_line：B/C 搜索的预测基准点 ---
 * seed_line 是预测搜索的起点：
 *   ENTRY 阶段：用 A 的坐标
 *   BEGIN 阶段：用 B 的坐标（向内偏移 8px）
 * 搜索时从 seed_line 出发，沿对面线斜率方向扫描暗点。
 * 如果 seed_line 无效，整个 B/C 搜索链都会失败。 */
static int circle_seed_line_x[2];                    /* seed 原始 x（raw 图坐标） */
static int circle_seed_line_y[2];                    /* seed 原始 y */
static int circle_seed_line_valid[2];                /* seed 是否有效 */

/* --- B 搜索调试状态（供日志输出） --- */
static int circle_B_search_reason;
static int circle_B_search_num;
static const char *circle_B_search_detail;
static int circle_B_search_best_x;
static int circle_B_search_best_y;
static int circle_B_search_sharp_far;                /* 远端 L 点与 B 太近，疑似假入口 */
static int circle_B_search_seed_x;
static int circle_B_search_seed_y;
static int circle_B_search_ready;                    /* B 的 y 坐标是否达到 B_READY_Y */
static float circle_B_search_slope;

/* --- B 搜索临时工作区 --- */
static int B_trace_pts[MT9V03X_H][2];               /* trace 点序列 */
static int B_trace_num;
static int B_seed_x;
static int B_seed_y;
static float B_slope;                                /* 预测斜率 dx/dy */
static int B_y_min;                                  /* 搜索窗口上界 */
static int B_y_max;                                  /* 搜索窗口下界 */
static int B_best_x;                                 /* 当前最佳 B 候选 */
static int B_best_y;
static int B_best_i;
static int B_candidate_hits;                         /* trace 中落在窗口内的点数 */
static int B_valid_hits;                             /* 满足所有阈值的候选点数 */

/* --- C 搜索调试状态 --- */
static int circle_C_search_reason;
static int circle_C_search_num;
static const char *circle_C_search_detail;
static int circle_C_search_seed_x;
static int circle_C_search_seed_y;
static int circle_C_search_best_i;
static float circle_C_search_slope;
static float circle_C_search_angle;

/* --- C 搜索临时工作区 --- */
static int C_trace_pts[MT9V03X_H][2];
static float C_trace_f[MT9V03X_H][2];               /* trace 转 float，供角度计算 */
static float C_angles[MT9V03X_H];                    /* 局部角度序列 */
static float C_angles_nms[MT9V03X_H];                /* NMS 抑制后的角度 */
static int C_trace_num;
static int C_seed_x;
static int C_seed_y;
static float C_slope;
static int C_best_i;                                 /* 角度最大的点索引 */
static float C_best_abs_angle;

/* side 参数统一编码：0 = RIGHT，1 = LEFT。
 * 所有 side_* 函数通过 side_index() 归一化，调用方只需传入 CIRCLE_SIDE_LEFT/RIGHT。
 * side_lpt / side_rpts 等映射到 imgproc 模块的全局变量。 */
/* side 参数归一化：0 = RIGHT，1 = LEFT，其他值也安全映射 */
static int side_index(int side) { return side ? CIRCLE_SIDE_LEFT : CIRCLE_SIDE_RIGHT; }
/* side 转字符，用于日志输出 */
static char side_char(int side) { return side ? 'L' : 'R'; }
/* side 是否为左环 */
static int side_is_left(int side) { return side_index(side) == CIRCLE_SIDE_LEFT; }
/* 本侧 L 点是否找到（Lpt0 对应左线，Lpt1 对应右线） */
static int side_lpt_found(int side) { return side_is_left(side) ? (Lpt0_found ? 1 : 0) : (Lpt1_found ? 1 : 0); }

/* 本侧 L 点在 rptss 数组中的索引 */
static int side_lpt_id(int side) { return side_is_left(side) ? Lpt0_rpts0s_id : Lpt1_rpts1s_id; }

/* 本侧边线点数（点数少说明是内侧，被圆环遮挡） */
static int side_rpts_num(int side) { return side_is_left(side) ? rpts0s_num : rpts1s_num; }

/* 对侧 L 点是否找到（圆环入口特征：本侧有 L 点，对侧没有） */
static int side_opposite_lpt_found(int side) { return side_is_left(side) ? (Lpt1_found ? 1 : 0) : (Lpt0_found ? 1 : 0); }

/* 对侧 L 点索引 */
static int side_opposite_lpt_id(int side) { return side_is_left(side) ? Lpt1_rpts1s_id : Lpt0_rpts0s_id; }
/* 对侧是否为直道（圆环入口的典型特征：本侧有拐点，对侧是直道） */
static int side_opposite_straight(int side) { return side_is_left(side) ? is_straight1 : is_straight0; }

/* OUT 阶段判断对侧是否为直道（出环确认条件） */
static int side_out_straight(int side) { return side_is_left(side) ? is_straight1 : is_straight0; }
/* 状态枚举映射：根据 side 返回对应的左右状态 */
static int side_entry_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_ENTRY : CIRCLE_RIGHT_ENTRY; }
static int side_begin_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_BEGIN : CIRCLE_RIGHT_BEGIN; }
static int side_running_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_RUNNING : CIRCLE_RIGHT_RUNNING; }
static int side_out_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_OUT : CIRCLE_RIGHT_OUT; }
/* BEGIN 阶段跟的是圆环内侧，所以左环跟右线，右环跟左线 */
static int side_begin_track(int side) { return side_is_left(side) ? TRACK_RIGHT : TRACK_LEFT; }
/* OUT 阶段切到对侧巡线 */
static int side_out_track(int side) { return side_is_left(side) ? TRACK_LEFT : TRACK_RIGHT; }

/* ================= 日志与调参输出 ================= */

/* 参考模式名称（用于日志输出）。
 * CIRCLE_REF_NONE: 还没找到可用参考
 * CIRCLE_REF_BEGIN_AB: 用 B 做参考（兜底）
 * CIRCLE_REF_IN_C: 用 C 做参考（更稳定） */
static const char *circle_ref_mode_name(enum circle_ref_mode_e mode)
{
    switch(mode)
    {
    case CIRCLE_REF_NONE: return "none";
    case CIRCLE_REF_BEGIN_AB: return "begin_outer_fallback";
    case CIRCLE_REF_IN_C: return "in_c";
    default: return "unknown";
    }
}

/* B/C 搜索结果名称（用于日志输出）。
 * 每个结果码对应一种失败原因，方便调参时定位问题。 */
static const char *point_search_reason_name(int reason)
{
    switch(reason)
    {
    case CIRCLE_POINT_SEARCH_OK: return "ok";                    /* 找到可信点 */
    case CIRCLE_POINT_SEARCH_NO_A: return "no_a";                /* 没有锁定 A */
    case CIRCLE_POINT_SEARCH_NO_B: return "no_b";                /* trace 里没有候选点 */
    case CIRCLE_POINT_SEARCH_NO_EXTREME: return "no_extreme";    /* 有候选但不满足极值条件 */
    case CIRCLE_POINT_SEARCH_NO_V: return "no_v";                /* C 搜索：trace 里没有角点 */
    case CIRCLE_POINT_SEARCH_PHASE_GATE: return "phase_gate";    /* B 还没 ready，C 搜索被门控 */
    case CIRCLE_POINT_SEARCH_NO_SEED: return "no_seed";          /* 找不到预测 seed */
    case CIRCLE_POINT_SEARCH_NO_TRACE: return "no_trace";        /* trace 太短或断掉 */
    case CIRCLE_POINT_SEARCH_NO_SLOPE: return "no_slope";        /* 对面线太短，无法算预测斜率 */
    case CIRCLE_POINT_SEARCH_JOIN_BAD: return "join_bad";        /* C 点与 B 点的连接关系不合格 */
    default: return "unknown";
    }
}

/* 圆环调试日志是否启用。
 * 通过环境变量 FRONT_CAR_CIRCLE_CAL_LOG 控制：
 *   "1" 或 "true" → 启用
 *   "0" 或 "false" 或未设置 → 禁用
 * 启用后会输出详细的 A/B/C 搜索过程、状态切换、陀螺仪转角等信息。 */
int circle_cal_log_enabled(void)
{
    const char *val = getenv("FRONT_CAR_CIRCLE_CAL_LOG");
    static int warned_invalid;
    if(val == NULL || val[0] == '\0' || strcmp(val, "0") == 0 || strcmp(val, "false") == 0) return 0;
    if(strcmp(val, "1") == 0 || strcmp(val, "true") == 0) return 1;
    if(!warned_invalid)
    {
        printf("EnvWarn: invalid flag for FRONT_CAR_CIRCLE_CAL_LOG='%s'\n", val);
        warned_invalid = 1;
    }
    return 0;
}

/* 获取当前累计转角（单位 0.1°） */
static int circle_heading_deg10(void)
{
    return (int)(fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10);
}

/* 判断累计转角是否达到指定门槛（单位 0.1°）。
 * 用于 BEGIN→RUNNING（GYRO_IN_DEG10=600，即 60°）和 RUNNING→OUT（GYRO_OUT_DEG10=1500，即 150°）。 */
static int circle_heading_abs_ge(int tenth_deg)
{
    return fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10 >= (float)tenth_deg;
}

/* 记录状态切换日志（仅 circle_cal_log_enabled 时输出）。
 * 包含：from/to 状态、切换原因、当前转角、累计距离、BEGIN 距离。
 * 用于调参时分析状态切换时机是否正确。 */
static void log_circle_state(enum circle_type_e from, enum circle_type_e to, const char *reason)
{
    if(circle_cal_log_enabled())
    {
        printf("ATGCircleState: from=%s to=%s reason=%s heading_deg10=%d dist=%d begin_dist=%lld begin_last=%lld\n",
               circle_type_name[from],
               circle_type_name[to],
               reason,
               circle_heading_deg10(),
               total_distence,
               (long long)atg_reference_circle_begin_dist(),
               (long long)atg_reference_circle_begin_last_dist());
    }
}

/* 清除锚点：标记为未找到，坐标置 -1。
 * 在状态切换时调用，防止旧状态的锚点干扰新状态。 */
static void clear_anchor(circle_anchor_point_t *p)
{
    p->found = 0;
    p->id = -1;
    p->raw_x = -1;
    p->raw_y = -1;
}

/* 存储锚点：把搜索到的点存入 anchor 结构体。
 * found=1 表示有效，id 是在 rptss 数组中的索引，raw_x/raw_y 是原图坐标。 */
static void store_anchor(circle_anchor_point_t *p, int id, const circle_point_t *raw)
{
    p->found = 1;
    p->id = id;
    p->raw_x = raw->x;
    p->raw_y = raw->y;
}

/* 清除 seed_line：标记为无效，坐标置 -1。
 * seed_line 无效时，整个 B/C 搜索链都会失败。 */
static void clear_seed_line(int side)
{
    circle_seed_line_valid[side] = 0;
    circle_seed_line_x[side] = -1;
    circle_seed_line_y[side] = -1;
}

/* 从 A 点设置 seed_line：ENTRY 阶段用 A 的坐标做预测基准。
 * seed_line 是 B/C 搜索的起点，从这里出发沿对面线斜率方向扫描暗点。 */
static void set_seed_line_from_A(int side, const circle_anchor_point_t *A)
{
    if(A == NULL || !A->found) return;
    circle_seed_line_valid[side] = 1;
    circle_seed_line_x[side] = A->raw_x;
    circle_seed_line_y[side] = A->raw_y;
}

/* B 的 seed 有一个小偏移（±8px），让预测线从 B 稍微偏向圆环内侧。
 * 为什么需要偏移？
 *   B 在圆环外侧边缘，直接从 B 出发搜索可能会搜到外侧的噪声。
 *   向内偏移 8px 后，搜索起点更靠近圆环内侧的边界，更容易找到 C 点。 */
static int signed_B_seed_offset(int side)
{
    enum { seed_dx = 8 };                              /* 向内侧偏移 8 像素 */
    return side_is_left(side) ? -seed_dx : seed_dx;
}

/* 从 B 点设置 seed_line：BEGIN 阶段用 B 的坐标做预测基准。
 * 与 set_seed_line_from_A 不同，这里有一个 ±8px 的内侧偏移。 */
static void set_seed_line_from_B(int side, const circle_anchor_point_t *B)
{
    if(B == NULL || !B->found) return;
    circle_seed_line_valid[side] = 1;
    circle_seed_line_x[side] = B->raw_x + signed_B_seed_offset(side);
    circle_seed_line_y[side] = B->raw_y;
}

/* ================= 状态复位与退出收口 ================= */

/* 清空入环投票计数和暂存的 A 点 */
/* 清空入环投票计数和暂存的 A 点。
 * 调用时机：投票通过后、投票失败时、抑制期间。 */
void reset_circle_entry_votes(void)
{
    circle_entry_votes[CIRCLE_SIDE_RIGHT] = 0;
    circle_entry_votes[CIRCLE_SIDE_LEFT] = 0;
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_RIGHT]);
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_LEFT]);
}

/* 抑制入环检测指定帧数。
 * 如果当前抑制帧数更多，则保留更大的值（取 max）。
 * 同时清空投票，防止抑制期间积累无效投票。 */
void suppress_circle_entry_frames(int frames)
{
    if(frames > circle_entry_suppress_frames)
    {
        circle_entry_suppress_frames = frames;
    }
    reset_circle_entry_votes();
}

/* 出环后抑制重新进入：防止刚出圆环就立刻重新误触发。
 * REENTRY_SUPPRESS_FRAMES=150 帧（约 1.5 秒），足够车驶离圆环入口区域。 */
void suppress_circle_reentry_after_exit(void)
{
    suppress_circle_entry_frames(REENTRY_SUPPRESS_FRAMES);
}

/* 清除入环抑制（用于手动复位等场景） */
void clear_circle_entry_suppression(void)
{
    circle_entry_suppress_frames = 0;
}

/* 检查入环检测是否被抑制。
 * 抑制期间每帧递减计数器，并清空投票（防止抑制期间积累无效投票）。
 * 返回 1 表示被抑制（跳过检测），0 表示可以正常检测。 */
static int circle_entry_suppressed(void)
{
    if(circle_entry_suppress_frames <= 0) return 0;
    circle_entry_suppress_frames--;
    reset_circle_entry_votes();
    return 1;
}

/* 重置 BEGIN 阶段的丢线计数。
 * 在状态切换时调用，防止旧状态的丢线计数干扰新状态。 */
void reset_circle_begin_flags(void)
{
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    circle_begin_lost_streak[CIRCLE_SIDE_RIGHT] = 0;
    circle_begin_lost_streak[CIRCLE_SIDE_LEFT] = 0;
}

/* 重置圆环几何状态：清除所有锚点、seed_line、搜索状态等。
 * 在状态切换时调用，确保新状态从干净的状态开始。 */
void reset_circle_geometry_state(void)
{
    circle_ref_mode = CIRCLE_REF_NONE;
    clear_anchor(&circle_A_point);
    clear_anchor(&circle_B_point);
    clear_anchor(&circle_C_point);
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_RIGHT]);
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_LEFT]);
    circle_entry_ever_valid_B[CIRCLE_SIDE_RIGHT] = 0;
    circle_entry_ever_valid_B[CIRCLE_SIDE_LEFT] = 0;
    clear_seed_line(CIRCLE_SIDE_RIGHT);
    clear_seed_line(CIRCLE_SIDE_LEFT);
    circle_out_straight_streak[CIRCLE_SIDE_RIGHT] = 0;
    circle_out_straight_streak[CIRCLE_SIDE_LEFT] = 0;
    circle_B_streak = 0;
    circle_C_streak = 0;
    circle_C_join_ok = 0;
    circle_B_follow_fail_streak[CIRCLE_SIDE_RIGHT] = 0;
    circle_B_follow_fail_streak[CIRCLE_SIDE_LEFT] = 0;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_detail = "reset";
    circle_B_search_num = 0;
    circle_B_search_best_x = -1;
    circle_B_search_best_y = -1;
    circle_B_search_seed_x = -1;
    circle_B_search_seed_y = -1;
    circle_B_search_ready = 0;
    circle_B_search_slope = 0.0f;
    circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_C_search_num = 0;
    circle_C_search_detail = "reset";
    circle_C_search_seed_x = -1;
    circle_C_search_seed_y = -1;
    circle_C_search_best_i = -1;
    circle_C_search_slope = 0.0f;
    circle_C_search_angle = 0.0f;
}

/* 重置陀螺仪累计转角。
 * 调用时机：进入 RUNNING 时（BEGIN→RUNNING 的转角从 0 开始重新计算）。 */
static void reset_circle_heading(void)
{
    circle_heading_rad = 0.0f;
}

/* 陀螺仪积分：每个控制周期调用一次，累计圆环内转角。
 *
 * 死区过滤：角速度低于 0.065 rad/s 时不积分，避免静止时漂移累积。
 * 这个死区值需要根据实际陀螺仪的噪声水平标定。
 *
 * 调用时机：由控制模块在每个 PIT 中断中调用。
 * 重置时机：进入 RUNNING 时重置（BEGIN→RUNNING 的转角从 0 开始重新计算）。 */
void update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid)
{
    if(circle_type == CIRCLE_NONE)
    {
        reset_circle_heading();
        return;
    }
    if(!valid || period_ms <= 0 || fabsf(yaw_rate_rad_s) <= CIRCLE_GYRO_DEADZONE_RAD_S) return;
    circle_heading_rad += yaw_rate_rad_s * ((float)period_ms / 1000.0f);
}

/* 陀螺仪角度是否达到进环门槛（GYRO_IN_DEG10=600，即 60°）。
 * 用于 BEGIN→RUNNING 的状态转换判断。
 * 被 reference_step.c 的 revoke_idle_circle_begin() 调用。 */
int circle_heading_enter_ready(void)
{
    return circle_heading_abs_ge(GYRO_IN_DEG10);
}

/* 正常出环收口：恢复巡线参数，计数 +1，抑制重入。
 * 与 reference_step.c 的 reset_circle_to_none() 保持一致。
 * 调用时机：OUT 阶段连续检测到直道后。 */
static void finish_circle_exit(const char *reason)
{
    log_circle_state(circle_type, CIRCLE_NONE, reason);
    circle_type = CIRCLE_NONE;
    road_type = ROAD_NORMAL;
    begin_y = BEGIN_Y;
    Count_dis_Flag = 0;
    aim_distance = AIM_DISTENCE;
    if_lost_right_line = 0;
    if_lost_left_line = 0;
    circle_count++;
    reset_circle_begin_flags();
    reset_circle_geometry_state();
    suppress_circle_reentry_after_exit();
}

/* BEGIN 阶段异常撤回（假入口、口部丢失过晚等），不计 circle_count。
 * 与 finish_circle_exit 的区别：不增加 circle_count，因为这不是真正的圆环。
 * 调用时机：口部丢失过晚、远端 L 点与 B 太近等。 */
static void abort_circle_begin(const char *reason)
{
    log_circle_state(circle_type, CIRCLE_NONE, reason);
    circle_type = CIRCLE_NONE;
    Count_dis_Flag = 0;
    reset_circle_begin_flags();
    reset_circle_geometry_state();
    reset_circle_entry_votes();
    circle_loss_start_begin_dist[CIRCLE_SIDE_RIGHT] = -1;
    circle_loss_start_begin_dist[CIRCLE_SIDE_LEFT] = -1;
    suppress_circle_reentry_after_exit();
}

/* ================= 入环检测：确认 A 点 ================= */

/* 从本侧 rpts 序列取第 id 个点，逆旋转到 raw 图坐标。
 * rpts 是俯视角坐标，需要逆旋转回原图坐标才能在 raw 图上做暗点检测和追线。
 * 返回 1 表示成功，0 表示 id 越界或 p 为 NULL。 */
static int circle_get_raw_point(int side, int id, circle_point_t *p)
{
    const int num = side_rpts_num(side);
    float (*pts)[2] = side_is_left(side) ? rpts0s : rpts1s;
    if(p == NULL || id < 0 || id >= num) return 0;
    p->x = (int)Cal_inv_rot_x(pts[id][0], pts[id][1]);
    p->y = (int)Cal_inv_rot_y(pts[id][0], pts[id][1]);
    return 1;
}

/* 获取本侧 A 点（L 角点）的 raw 图坐标。
 * A 是入口近端拐点，由 imgproc 的角点检测模块锁定。
 * 返回 1 表示成功，0 表示本侧没有 L 点。 */
static int circle_get_A(int side, circle_point_t *A)
{
    const int id = side_lpt_id(side);
    if(!side_lpt_found(side) || !circle_get_raw_point(side, id, A)) return 0;
    return 1;
}

/* 局部自适应暗点检测：block×block 窗口内均值 - clip_value 作为阈值。
 * 与 image_handle() 中的种子点搜索用同样的自适应逻辑。
 * threshold 可以为 NULL，不关心具体阈值时只判断是否为暗点。 */
static int raw_dark(int x, int y, int *threshold)
{
    int lt = 0;
    if(x < block_size / 2 || x >= MT9V03X_W - block_size / 2 ||
       y < block_size / 2 || y >= MT9V03X_H - block_size / 2) return 0;
    for(int dy = -block_size / 2; dy <= block_size / 2; dy++)
    {
        for(int dx = -block_size / 2; dx <= block_size / 2; dx++)
        {
            lt += AT_IMAGE(&img_raw, x + dx, y + dy);
        }
    }
    lt = lt / (block_size * block_size) - clip_value;
    if(threshold != NULL)
    {
        *threshold = lt;
    }
    return AT_IMAGE(&img_raw, x, y) < lt;
}

/* 水平镜像：对面线的 x 坐标需要翻转才能和本侧在同一坐标系下比较。
 * 原因：左线和右线的 x 坐标方向相反，镜像后才能用同一个斜率公式预测。 */
static int mirrored_raw_x(int x)
{
    return MT9V03X_W - 1 - x;
}

/* 用对面线的斜率预测弯道走向。
 *
 * 问题：入环时本侧线在拐点处断开或变形，无法用于预测。
 * 方案：对面线在视野内仍保持连续，其延伸方向近似弯道弧线的切线方向。
 *
 * 算法：
 *   1. 取对面线的前 30 个点（靠近画面底部）
 *   2. 用首尾两点算 dx/dy 斜率
 *   3. 要求 dy ≥ 8 像素，避免水平线导致斜率爆炸
 *
 * 返回 dx/dy 斜率，调用方用 prediction_x_at_y() 投射到指定行。 */
static int circle_prediction_slope(int side, float *dx_per_dy)
{
    float (*pts)[2] = side_is_left(side) ? rpts1s : rpts0s;
    const int num = side_is_left(side) ? rpts1s_num : rpts0s_num;
    if(dx_per_dy == NULL || num < 4) return 0;

    const int ref0 = 0;
    const int ref_max = clip(num - 1, 1, 30);
    const int x0 = mirrored_raw_x((int)Cal_inv_rot_x(pts[ref0][0], pts[ref0][1]));
    const int y0 = (int)Cal_inv_rot_y(pts[ref0][0], pts[ref0][1]);
    for(int i = ref_max; i > ref0; i--)
    {
        const int x1 = mirrored_raw_x((int)Cal_inv_rot_x(pts[i][0], pts[i][1]));
        const int y1 = (int)Cal_inv_rot_y(pts[i][0], pts[i][1]);
        const int dy = y1 - y0;
        if(abs(dy) < 8) continue;
        *dx_per_dy = (float)(x1 - x0) / (float)dy;
        return isfinite(*dx_per_dy) ? 1 : 0;
    }
    return 0;
}

/* 根据预测斜率，在指定行 y 上计算预测的 x 坐标。
 * 公式：x = seed_x + slope * (y - seed_y)
 * 结果钳位到图像范围内。 */
static int prediction_x_at_y(int side, int y, float slope)
{
    const int x = circle_seed_line_x[side] +
                  (int)lroundf(slope * (float)(y - circle_seed_line_y[side]));
    return clip(x, block_size / 2, MT9V03X_W - block_size / 2 - 1);
}

/* 在预测点附近 ±r 像素范围内找暗点。
 * 从中心向外扩展搜索，找到第一个暗点就返回。
 * 这样即使预测不精确，也能在小范围内找到真正的边界。 */
static int dark_near_prediction(int x_center, int y, int *seed_x)
{
    enum { r = 8 };  /* 搜索半径（像素） */

    for(int delta = 0; delta <= r; delta++)
    {
        const int xs[2] = {x_center + delta, x_center - delta};
        const int n = delta == 0 ? 1 : 2;
        for(int i = 0; i < n; i++)
        {
            const int x = xs[i];
            if(x < block_size / 2 || x >= MT9V03X_W - block_size / 2) continue;
            if(raw_dark(x, y, NULL))
            {
                *seed_x = x;
                return 1;
            }
        }
    }
    return 0;
}

/* 沿预测斜率方向扫描，找到第一个暗点作为 trace 起点。
 * 从 y_start 向 y_stop 逐行扫描，用 prediction_x_at_y() 计算预测 x，
 * 再在 ±8 像素范围内找暗点。
 * 这样即使本侧线在拐点处断裂，也能靠对面线的斜率"跨过去"找到弯道内侧边界。 */
static int circle_find_prediction_seed(int side, int y_start, int y_stop,
                                       int *seed_x, int *seed_y, const float *slope)
{
    if(!circle_seed_line_valid[side]) return 0;
    if(slope == NULL || !isfinite(*slope)) return 0;

    y_start = clip(y_start, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    y_stop = clip(y_stop, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    if(y_start < y_stop)
    {
        const int t = y_start;
        y_start = y_stop;
        y_stop = t;
    }

    for(int y = y_start; y >= y_stop; y--)
    {
        const int x_center = prediction_x_at_y(side, y, *slope);
        int x = -1;
        if(dark_near_prediction(x_center, y, &x))
        {
            *seed_x = x;
            *seed_y = y;
            return 1;
        }
    }
    return 0;
}

/* 从 seed 点开始沿边界搜线。
 * 左环用 lefthand（逆时针），右环用 righthand（顺时针），
 * 保证 trace 方向始终从入口向外侧延伸。 */
static int circle_trace_from_seed(int side, int seed_x, int seed_y, int trace[][2], int *trace_num)
{
    enum { min_trace = 6 };

    *trace_num = MT9V03X_H;
    if(side_is_left(side))
    {
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, seed_x, seed_y, trace, trace_num);
    }
    else
    {
        findline_righthand_adaptive(&img_raw, block_size, clip_value, seed_x, seed_y, trace, trace_num);
    }
    return *trace_num >= min_trace;
}

/* 把 int 类型的 trace 转成 float 类型，供角度计算函数使用。
 * local_angle_points() 需要 float 输入。 */
static void raw_trace_to_float(int trace[][2], int trace_num, float out[][2])
{
    for(int i = 0; i < trace_num; i++)
    {
        out[i][0] = (float)trace[i][0];
        out[i][1] = (float)trace[i][1];
    }
}

/* 从 L 点偏移得到内侧暗点搜索起点（仅日志/调试用）。
 * 偏移量：左环 (+2, -5)，右环 (+5, -5)。
 * 这个偏移是为了让搜索起点更靠近圆环内侧的边界。 */
int circle_entry_inner_seed(int left_side, int *seed_x, int *seed_y,
                            float *seed_raw_x, float *seed_raw_y)
{
    const int side = side_index(left_side);
    const int found_lpt = side_lpt_found(side);
    const int lpt_num = side_rpts_num(side);
    int id = 0;

    if(!found_lpt || lpt_num <= 0) return 0;
    id = clip(side_lpt_id(side), 0, lpt_num - 1);
    if(side_is_left(side))
    {
        *seed_raw_x = Cal_inv_rot_x(rpts0s[id][0], rpts0s[id][1]) + 2.0f;
        *seed_raw_y = Cal_inv_rot_y(rpts0s[id][0], rpts0s[id][1]) - 5.0f;
    }
    else
    {
        *seed_raw_x = Cal_inv_rot_x(rpts1s[id][0], rpts1s[id][1]) + 5.0f;
        *seed_raw_y = Cal_inv_rot_y(rpts1s[id][0], rpts1s[id][1]) - 5.0f;
    }
    *seed_x = clip((int)*seed_raw_x, block_size / 2, MT9V03X_W - block_size / 2 - 1);
    *seed_y = clip((int)*seed_raw_y, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    return 1;
}

/* 从 L 点向内侧射线扫描暗点（仅日志用，不影响逻辑）。
 * 沿 3 个方向（水平、斜上 1、斜上 2）各扫描 45 像素。
 * 找到暗点说明 L 点附近确实有弯道边界，辅助判断入环条件。 */
static int circle_inner_hit(int side, const circle_point_t *A)
{
    (void)A;
    const int inner_dx = side_is_left(side) ? -1 : 1;
    const int ray_dy[3] = {0, -1, -2};
    float seed_raw_x = 0.0f, seed_raw_y = 0.0f;
    int seed_x = -1, seed_y = -1;
    int hit_x = -1, hit_y = -1, hit_dx = 0, hit_dy = 0, hit_th = 0;

    if(!circle_entry_inner_seed(side, &seed_x, &seed_y, &seed_raw_x, &seed_raw_y))
    {
        if(circle_cal_log_enabled())
        {
            printf("ATGCircleEntryInnerHit: side=%c near=0@-1 seed=-1,-1 hit=0@-1,-1 ray=0,0 raw=0.0,0.0 th=0\n",
                   side_char(side));
        }
        return 0;
    }
    for(int ray = 0; ray < 3 && hit_y < 0; ray++)
    {
        for(int step = 1; step <= 45; step++)
        {
            const int x = seed_x + inner_dx * step;
            const int y = seed_y + ray_dy[ray] * step;
            if(x < block_size / 2 || x >= MT9V03X_W - block_size / 2 ||
               y < block_size / 2 + 1 || y >= MT9V03X_H - block_size / 2) break;
            if(raw_dark(x, y, &hit_th))
            {
                hit_x = x;
                hit_y = y;
                hit_dx = inner_dx;
                hit_dy = ray_dy[ray];
                break;
            }
        }
    }
    if(circle_cal_log_enabled())
    {
        printf("ATGCircleEntryInnerHit: side=%c near=%d@%d seed=%d,%d hit=%d@%d,%d ray=%d,%d raw=%.1f,%.1f th=%d\n",
               side_char(side), side_lpt_found(side), side_lpt_found(side) ? side_lpt_id(side) : -1,
               seed_x, seed_y, hit_y >= 0, hit_x, hit_y, hit_dx, hit_dy, seed_raw_x, seed_raw_y, hit_th);
    }
    return hit_y >= 0;
}

/* 记录 ENTRY 阶段 B 搜索的详细日志（仅 circle_cal_log_enabled 时输出）。
 * 包含 A 点状态、B 搜索结果、seed 坐标、斜率、最佳候选等。
 * 用于调参时分析为什么 B 搜索失败。 */
static void log_entry_probe(int side, int b_ret)
{
    if(!circle_cal_log_enabled()) return;
    printf("ATGCircleEntryProbe: side=%c A=1@%d(raw=%d,%d) B=0 ret=%d reason=%s detail=%s "
           "trace=%d seed=%d,%d seed_line=%d,%d slope=%.3f best=%d,%d ready=%d sharp_far=%d\n",
           side_char(side),
           circle_A_point.found ? circle_A_point.id : side_lpt_id(side),
           circle_A_point.raw_x, circle_A_point.raw_y, b_ret,
           point_search_reason_name(circle_B_search_reason),
           circle_B_search_detail ? circle_B_search_detail : "unknown",
           circle_B_search_num, circle_B_search_seed_x, circle_B_search_seed_y,
           circle_seed_line_x[side], circle_seed_line_y[side], circle_B_search_slope,
           circle_B_search_best_x, circle_B_search_best_y, circle_B_search_ready,
           circle_B_search_sharp_far);
}

/* 远端 L 点与 B 候选的距离检查：太近说明是尖锐弯道而非圆环。
 * 圆环的 B 点应该远离远端 L 点（圆环外侧是弧线，不是尖角）。
 * 如果远端 L 点与 B 距离 < 20 像素，说明是尖锐弯道的假入口。 */
static int far_lpt_near_B(int side, int b_x, int b_y)
{
    enum { near_r = 20 };                              /* 距离阈值（像素） */
    int far_x = 0, far_y = 0;
    if(side_is_left(side))
    {
        if(!far_Lpt0_found) return 0;
        far_x = (int)inv_far_Lpt0_found[0];
        far_y = (int)inv_far_Lpt0_found[1];
    }
    else
    {
        if(!far_Lpt1_found) return 0;
        far_x = (int)inv_far_Lpt1_found[0];
        far_y = (int)inv_far_Lpt1_found[1];
    }
    const int dx = far_x - b_x;
    const int dy = far_y - b_y;
    return dx * dx + dy * dy < near_r * near_r;
}

/* ================= B_entry：ENTRY 阶段从 A 找 B ================= */

/* 重置 B 搜索状态：清空所有临时变量和调试状态。
 * 每次 find_B_entry() 调用前都要重置，确保搜索从干净状态开始。 */
static void B_entry_reset(void)
{
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_detail = "start";
    circle_B_search_num = 0;
    circle_B_search_best_x = -1;
    circle_B_search_best_y = -1;
    circle_B_search_sharp_far = 0;
    circle_B_search_seed_x = -1;
    circle_B_search_seed_y = -1;
    circle_B_search_ready = 0;
    circle_B_search_slope = 0.0f;
    clear_anchor(&circle_B_point);
    B_trace_num = 0;
    B_seed_x = -1;
    B_seed_y = -1;
    B_slope = 0.0f;
    B_y_min = 0;
    B_y_max = 0;
    B_best_x = -1;
    B_best_y = -1;
    B_best_i = -1;
    B_candidate_hits = 0;
    B_valid_hits = 0;
}

/* 检查 A 点是否已锁定，并计算 B 搜索窗口。
 * B 应该在 A 的上方 15~50 像素范围内（up_min=15, up_max=50）。
 * 为什么是 15~50？
 *   太近（<15）：B 和 A 重叠，没有意义
 *   太远（>50）：超出圆环入口的典型范围，可能是噪声
 * B_best_x 初始化：左环取 -1（找最大），右环取 9999（找最小） */
static int B_entry_has_A(int side)
{
    enum { up_min = 15, up_max = 50 };

    if(!circle_A_point.found)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_A;
        circle_B_search_detail = "no_locked_a";
        return 0;
    }

    B_y_min = clip(circle_A_point.raw_y - up_max, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    B_y_max = clip(circle_A_point.raw_y - up_min, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    B_best_x = side_is_left(side) ? -1 : 9999;
    B_best_y = -1;
    return 1;
}

/* B 搜索的 seed 阶段：
 * 1. 检查 seed_line 是否有效（A 点已锁定）
 * 2. 计算对面线的预测斜率
 * 3. 沿预测方向在搜索窗口内找暗点作为 trace 起点
 *
 * 为什么用对面线的斜率？
 *   入环时本侧线在拐点处断开或变形，无法用于预测。
 *   对面线在视野内仍保持连续，其延伸方向近似弯道弧线的切线方向。 */
static int B_entry_seed(int side)
{
    if(!circle_seed_line_valid[side])
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_B_search_detail = "seed_line_invalid";
        return 0;
    }
    if(!circle_prediction_slope(side, &B_slope))
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SLOPE;
        circle_B_search_detail = "no_opposite_slope";
        return 0;
    }
    if(!circle_find_prediction_seed(side, B_y_max, B_y_min, &B_seed_x, &B_seed_y, &B_slope))
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_B_search_detail = "no_pred_seed";
        circle_B_search_slope = B_slope;
        return 0;
    }

    circle_B_search_seed_x = B_seed_x;
    circle_B_search_seed_y = B_seed_y;
    circle_B_search_slope = B_slope;
    return 1;
}

/* B 搜索的 trace 阶段：从 seed 点开始沿边界追线。
 * 左环用 lefthand（逆时针），右环用 righthand（顺时针）。
 * trace 太短（<6 点）则认为失败。 */
static int B_entry_trace(int side)
{
    if(!circle_trace_from_seed(side, B_seed_x, B_seed_y, B_trace_pts, &B_trace_num))
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_TRACE;
        circle_B_search_detail = "short_trace";
        circle_B_search_num = B_trace_num;
        return 0;
    }

    circle_B_search_num = B_trace_num;
    return 1;
}

/* 从 B_trace 中挑 B：
 * B 必须在 A 的上方，并且向圆环内侧偏移足够多。
 * min_dist / min_dy / min_inner_dx 不是状态门，只是排除太近、太平、太像噪声的候选点。 */
static int B_entry_pick(int side)
{
    enum
    {
        min_dy = 8,          /* B 至少要比 A 高 8 像素 */
        min_inner_dx = 6,    /* B 要向圆环内侧偏移至少 6 像素 */
        min_dist = 23,       /* A/B 距离太近不可信 */
        max_step = 18,       /* trace 横向突跳超过此值，认为断线 */
        min_hits = 1,        /* 至少需要 1 个合法候选 */
        up_min = 15,         /* B 在 A 上方的最小距离 */
        up_max = 50,         /* B 在 A 上方的最大距离，太远可能是噪声 */
    };

    int last_x = -1;

    for(int i = 0; i < B_trace_num; i++)
    {
        const int x = B_trace_pts[i][0];
        const int y = B_trace_pts[i][1];
        const int dx = x - circle_A_point.raw_x;
        const int dy = circle_A_point.raw_y - y;
        const int inner_dx = side_is_left(side) ? dx : -dx;
        const int dist2 = dx * dx + dy * dy;

        if(y < B_y_min || y > B_y_max) continue;
        B_candidate_hits++;

        if(last_x >= 0 && abs(x - last_x) > max_step)
        {
            circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
            circle_B_search_detail = "jump_bad";
            return -1;
        }
        last_x = x;
        if(dy < min_dy ||
           inner_dx < min_inner_dx ||
           dist2 < min_dist * min_dist ||
           dy < up_min || dy > up_max)
        {
            continue;
        }

        B_valid_hits++;
        if(side_is_left(side) ? x > B_best_x : x < B_best_x)
        {
            B_best_x = x;
            B_best_y = y;
            B_best_i = i;
        }
    }

    circle_B_search_best_x = B_best_x;
    circle_B_search_best_y = B_best_y;
    if(B_best_y < 0 || B_valid_hits < min_hits)
    {
        circle_B_search_reason = B_candidate_hits > 0 ? CIRCLE_POINT_SEARCH_NO_EXTREME :
                                                        CIRCLE_POINT_SEARCH_NO_B;
        circle_B_search_detail = B_candidate_hits > 0 ? "no_legal_extreme" : "no_trace_candidate";
        return 0;
    }

    return 1;
}

/* 远端 L 点与 B 候选太近 → 大概率是尖锐弯道而非圆环，标记为假入口 */
/* 检查 B 候选是否为假入口（远端 L 点与 B 太近）。
 * 圆环的 B 点应该远离远端 L 点（圆环外侧是弧线，不是尖角）。
 * 如果远端 L 点与 B 距离 < 20 像素，说明是尖锐弯道的假入口。 */
static int B_entry_fake(int side)
{
    if(!far_lpt_near_B(side, B_best_x, B_best_y)) return 0;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
    circle_B_search_detail = "sharp_far";
    circle_B_search_sharp_far = 1;
    return 1;
}

/* 锁定 B 点：把搜索到的最佳候选存入 circle_B_point。
 * 同时检查 B 的 y 坐标是否达到 B_READY_Y（够远）。
 * B_READY_Y=58 表示 B 点在画面上方 58 行以上才算"够远"。 */
static void B_entry_lock(void)
{
    circle_B_point.found = 1;
    circle_B_point.id = circle_A_point.id;
    circle_B_point.raw_x = B_best_x;
    circle_B_point.raw_y = B_best_y;
    circle_B_search_ready = circle_B_point.raw_y >= B_READY_Y;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_detail = "ok";
}

/* 记录 B 搜索的详细日志（仅 circle_cal_log_enabled 时输出）。
 * 包含：A 点位置、seed 坐标、斜率、B 候选坐标、dx/dy/dist2、trace 长度等。
 * 用于调参时分析 B 搜索的过程和结果。 */
static void B_entry_log(int side)
{
    if(!circle_cal_log_enabled()) return;
    const int dx = B_best_x - circle_A_point.raw_x;
    const int dy = circle_A_point.raw_y - B_best_y;
    const int inner_dx = side_is_left(side) ? dx : -dx;
    const int dist2 = dx * dx + dy * dy;
    printf("ATGCircleEntryB: side=%c A@%d seed=%d,%d seed_line=%d,%d slope=%.3f "
           "B_raw=%d,%d#%d dx=%d inner_dx=%d dy=%d dist2=%d trace=%d cand=%d hits=%d ready=%d sharp_far=%d\n",
           side_char(side), circle_A_point.id,
           circle_B_search_seed_x, circle_B_search_seed_y,
           circle_seed_line_x[side], circle_seed_line_y[side], circle_B_search_slope,
           circle_B_point.raw_x, circle_B_point.raw_y, B_best_i, dx, inner_dx, dy, dist2,
           B_trace_num, B_candidate_hits, B_valid_hits,
           circle_B_search_ready, circle_B_search_sharp_far);
}

/* ENTRY 阶段找 B：
 * A 是入口近端拐点，B 是圆环外侧远端极值点。
 * 找到 B 后不立刻进 BEGIN，而是靠 B_OK_FRAMES 做稳定确认。
 *
 * 返回：
 *   1  找到可信 B
 *   0  本帧没找到
 *  -1  找到疑似假 B（远端 L 点太近），需要撤回 ENTRY
 */
static int find_B_entry(int side)
{
    int pick_ret;

    B_entry_reset();

    if(!B_entry_has_A(side)) return 0;      /* 没有锁定 A，没法从 A 推 B */
    if(!B_entry_seed(side)) return 0;       /* 找不到预测 seed，不追线 */
    if(!B_entry_trace(side)) return 0;      /* trace 太短或断掉 */

    pick_ret = B_entry_pick(side);          /* 从 trace 里挑最像 B 的点 */
    if(pick_ret <= 0) return pick_ret;

    if(B_entry_fake(side)) return -1;       /* 远端 L 点太近，可能是假入口 */

    B_entry_lock();
    B_entry_log(side);
    return 1;
}

/* ================= B_follow：BEGIN 阶段跟踪 B ================= */

/* 重置 B 跟踪状态：清空所有临时变量和调试状态。
 * 每次 follow_B_begin() 调用前都要重置。 */
static void B_follow_reset(void)
{
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_detail = "follow_start";
    circle_B_search_num = 0;
    circle_B_search_best_x = -1;
    circle_B_search_best_y = -1;
    circle_B_search_sharp_far = 0;
    circle_B_search_seed_x = -1;
    circle_B_search_seed_y = -1;
    circle_B_search_ready = 0;
    circle_B_search_slope = 0.0f;
    B_trace_num = 0;
    B_seed_x = -1;
    B_seed_y = -1;
    B_slope = 0.0f;
    B_y_min = 0;
    B_y_max = 0;
    B_best_x = -1;
    B_best_y = -1;
    B_best_i = -1;
    B_candidate_hits = 0;
    B_valid_hits = 0;
}

/* B_follow 检查前置条件并设置搜索窗口：
 *   1. B 点必须已锁定（circle_B_point.found）
 *   2. seed_line 必须有效
 *   3. 搜索窗口：B 的 y 坐标 ±8px（y_r=8）
 *
 * 返回：1 前置条件满足，0 失败（设置失败原因） */
static int B_follow_check(int side)
{
    enum { y_r = 8 };                              /* 跟踪窗口半径（像素），B 只在 ±8px 内移动 */

    if(!circle_B_point.found)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_B;
        circle_B_search_detail = "follow_no_b";
        return 0;
    }
    if(!circle_seed_line_valid[side])
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_B_search_detail = "follow_seed_line_invalid";
        return 0;
    }

    B_y_min = clip(circle_B_point.raw_y - y_r, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    B_y_max = clip(circle_B_point.raw_y + y_r, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    B_best_x = side_is_left(side) ? -1 : 9999;
    B_best_y = -1;
    return 1;
}

/* B_follow 获取 seed：
 *   1. 计算对面线的预测斜率
 *   2. 沿预测方向在 B 附近窗口内找暗点作为 trace 起点
 *
 * 与 B_entry_seed 的区别：搜索窗口更窄（B ±8px），因为 B 已经大致确定。 */
static int B_follow_get_seed(int side)
{
    if(!circle_prediction_slope(side, &B_slope))
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SLOPE;
        circle_B_search_detail = "follow_no_slope";
        return 0;
    }
    if(!circle_find_prediction_seed(side, B_y_max, B_y_min, &B_seed_x, &B_seed_y, &B_slope))
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_B_search_detail = "follow_no_pred_seed";
        circle_B_search_slope = B_slope;
        return 0;
    }
    circle_B_search_seed_x = B_seed_x;
    circle_B_search_seed_y = B_seed_y;
    circle_B_search_slope = B_slope;
    return 1;
}

/* B_follow 搜 trace：从 seed 点开始沿边界追线。
 * trace 太短（<6 点）则认为失败。 */
static int B_follow_trace(int side)
{
    if(!circle_trace_from_seed(side, B_seed_x, B_seed_y, B_trace_pts, &B_trace_num))
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_TRACE;
        circle_B_search_detail = "follow_short_trace";
        circle_B_search_num = B_trace_num;
        return 0;
    }
    circle_B_search_num = B_trace_num;
    return 1;
}

/* 从 trace 中找 B 的新位置：在 ±8px 窗口内找最靠内侧的点。
 * 左环找 x 最大的点（最靠右），右环找 x 最小的点（最靠左）。
 *
 * 返回：1 找到候选点，0 窗口内没有点 */
static int B_pick_follow(int side)
{
    for(int i = 0; i < B_trace_num; i++)
    {
        const int x = B_trace_pts[i][0];
        const int y = B_trace_pts[i][1];

        if(y < B_y_min || y > B_y_max) continue;
        if(side_is_left(side) ? x > B_best_x : x < B_best_x)
        {
            B_best_x = x;
            B_best_y = y;
        }
    }

    if(B_best_y >= 0) return 1;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
    circle_B_search_detail = "follow_no_window_point";
    return 0;
}

/* 跟踪模式锁定 B：更新 circle_B_point 的坐标。
 * 与 B_entry_lock 不同，这里不重置 found 状态，只更新坐标。
 * 同时更新 seed_line 到 B 的新坐标（向内偏移 8px），供后续 C 搜索使用。 */
static void B_lock_follow(int side)
{
    circle_B_point.raw_x = B_best_x;
    circle_B_point.raw_y = B_best_y;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_detail = "follow_ok";
    circle_B_search_best_x = B_best_x;
    circle_B_search_best_y = B_best_y;
    circle_B_search_ready = B_best_y >= B_READY_Y;
    set_seed_line_from_B(side, &circle_B_point);
}

/* 记录 B 跟踪日志（仅 circle_cal_log_enabled 时输出） */
static void B_log_follow(int side)
{
    if(!circle_cal_log_enabled()) return;
    printf("ATGCircleBeginBFollow: side=%c seed=%d,%d B=%d,%d seed_line=%d,%d slope=%.3f trace=%d\n",
           side_char(side), B_seed_x, B_seed_y,
           circle_B_point.raw_x, circle_B_point.raw_y,
           circle_seed_line_x[side], circle_seed_line_y[side], B_slope, B_trace_num);
}

/* BEGIN 阶段跟踪 B 的主函数：
 *   1. 检查前置条件（B 已锁定、seed_line 有效）
 *   2. 计算预测斜率，在 B 附近找 seed
 *   3. 从 seed 追线，从 trace 中挑 B 的新位置
 *   4. 更新 circle_B_point 和 seed_line
 *
 * 返回：1 跟踪成功，0 跟踪失败（B 不动或丢失） */
static int follow_B_begin(int side)
{
    B_follow_reset();
    if(!B_follow_check(side)) return 0;
    if(!B_follow_get_seed(side)) return 0;
    if(!B_follow_trace(side)) return 0;
    if(!B_pick_follow(side)) return 0;
    B_lock_follow(side);
    B_log_follow(side);
    return 1;
}

/* 记录 B 跟踪失败日志（仅 circle_cal_log_enabled 时输出） */
static void log_B_follow_miss(int side)
{
    if(!circle_cal_log_enabled()) return;
    printf("ATGCircleBeginBFollow: side=%c miss_streak=%d B=%d@%d,%d seed_line=%d@%d,%d\n",
           side_char(side),
           circle_B_follow_fail_streak[side],
           circle_B_point.found,
           circle_B_point.raw_x,
           circle_B_point.raw_y,
           circle_seed_line_valid[side],
           circle_seed_line_x[side],
           circle_seed_line_y[side]);
}

/* ================= C_begin：BEGIN 阶段从 B 找 C =================
 *
 * C 是弯道最深处的角点，由局部角度 NMS 检测。
 * C 比 B 更深、更稳定，找到 C 后可以作为更好的入环参考。
 * 如果 C 不稳定，用 B 兜底。 */

/* 重置 C 搜索状态 */
static void C_reset(void)
{
    clear_anchor(&circle_C_point);
    circle_C_search_num = 0;
    circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_C_search_detail = "start";
    circle_C_search_seed_x = -1;
    circle_C_search_seed_y = -1;
    circle_C_search_best_i = -1;
    circle_C_search_slope = 0.0f;
    circle_C_search_angle = 0.0f;
    circle_C_join_ok = 0;
    C_trace_num = 0;
    C_seed_x = -1;
    C_seed_y = -1;
    C_slope = 0.0f;
    C_best_i = -1;
    C_best_abs_angle = 0.0f;
}

/* C 搜索前置条件：B 必须已锁定 */
static int C_has_B(void)
{
    if(!circle_B_point.found)
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_B;
        circle_C_search_detail = "no_locked_b";
        return 0;
    }
    return 1;
}

/* C 搜索的 seed 阶段：
 *   1. 检查 seed_line 是否有效
 *   2. 计算对面线的预测斜率
 *   3. 从 B 点上方 6px 开始向上搜索暗点（C 应该在 B 的上方）
 *
 * 搜索范围：B.y - 6 到画面上方（block_size/2 + 5） */
static int C_seed(int side)
{
    if(!circle_seed_line_valid[side])
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_C_search_detail = "seed_line_invalid";
        return 0;
    }
    if(!circle_prediction_slope(side, &C_slope))
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_SLOPE;
        circle_C_search_detail = "no_opposite_slope";
        return 0;
    }
    /* 从 B 点上方一点开始找 C */
    if(!circle_find_prediction_seed(side,
                                    circle_B_point.raw_y - 6,
                                    block_size / 2 + 5,
                                    &C_seed_x, &C_seed_y, &C_slope))
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_C_search_detail = "no_pred_seed";
        circle_C_search_slope = C_slope;
        return 0;
    }
    circle_C_search_seed_x = C_seed_x;
    circle_C_search_seed_y = C_seed_y;
    circle_C_search_slope = C_slope;
    return 1;
}

/* C 搜索的 trace 阶段：
 *   1. 从 seed 追线得到 trace
 *   2. 把 trace 转成 float（供角度计算函数使用）
 *   3. 计算局部角度序列（前后 3 点的角度差）
 *   4. 用 NMS（非极大值抑制）抑制噪声峰值
 *
 * angle_dist=3：角度计算的前后跨度
 * nms=7：NMS 抑制窗口大小 */
static int C_trace(int side)
{
    enum { angle_dist = 3, nms = 7 };

    if(!circle_trace_from_seed(side, C_seed_x, C_seed_y, C_trace_pts, &C_trace_num))
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_TRACE;
        circle_C_search_detail = "short_trace";
        circle_C_search_num = C_trace_num;
        return 0;
    }
    circle_C_search_num = C_trace_num;
    raw_trace_to_float(C_trace_pts, C_trace_num, C_trace_f);
    local_angle_points(C_trace_f, C_trace_num, C_angles, angle_dist);
    nms_angle(C_angles, C_trace_num, C_angles_nms, nms);
    return 1;
}

/* 从 trace 中找角度最大的点作为 C：
 *   - C 必须在 B 上方 >6px（up_min）
 *   - 局部角度 ≥ 350 mrad（≈20°）才算角点（min_angle_mrad）
 *   - trace 长度 ≥ 6 点才算有效（min_trace）
 *
 * 还要检查 C 与 B 的连接关系（join_ok）：
 *   trace 够长、C 索引合法、C 确实在 B 上方 */
static int C_pick(void)
{
    enum
    {
        up_min = 6,            /* C 至少要比 B 高 6 像素 */
        min_angle_mrad = 350,  /* 局部角度至少 350 mrad（≈20°）才算角点 */
        min_trace = 6,         /* trace 长度至少 6 点才算有效 */
    };

    for(int i = 0; i < C_trace_num; i++)
    {
        const int y = C_trace_pts[i][1];
        const float abs_angle = fabsf(C_angles_nms[i]);
        const int dy = circle_B_point.raw_y - y;
        if(dy <= up_min) continue;
        if((int)(abs_angle * 1000.0f) < min_angle_mrad) continue;
        if(abs_angle > C_best_abs_angle)
        {
            C_best_abs_angle = abs_angle;
            C_best_i = i;
        }
    }

    if(C_best_i < 0)
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_V;
        circle_C_search_detail = "no_corner";
        return 0;
    }

    circle_C_join_ok = C_trace_num >= min_trace &&
                       C_best_i >= 0 &&
                       C_best_i < C_trace_num &&
                       circle_B_point.raw_y - C_trace_pts[C_best_i][1] > up_min;
    if(!circle_C_join_ok)
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_JOIN_BAD;
        circle_C_search_detail = "join_bad";
        clear_anchor(&circle_C_point);
        return 0;
    }
    return 1;
}

/* 锁定 C 点：把最佳候选存入 circle_C_point */
static void C_lock(void)
{
    circle_C_point.found = 1;
    circle_C_point.id = C_best_i;
    circle_C_point.raw_x = C_trace_pts[C_best_i][0];
    circle_C_point.raw_y = C_trace_pts[C_best_i][1];
    circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_C_search_detail = "ok";
    circle_C_search_best_i = C_best_i;
    circle_C_search_angle = C_angles_nms[C_best_i];
}

/* 记录 C 搜索日志（仅 circle_cal_log_enabled 时输出） */
static void C_log(int side)
{
    if(circle_cal_log_enabled())
    {
        printf("ATGCircleBeginC: side=%c B=%d,%d seed=%d,%d seed_line=%d,%d slope=%.3f "
               "C=%d,%d#%d angle=%.3f trace=%d join=%d\n",
               side_char(side), circle_B_point.raw_x, circle_B_point.raw_y,
               circle_C_search_seed_x, circle_C_search_seed_y,
               circle_seed_line_x[side], circle_seed_line_y[side], C_slope,
               circle_C_point.raw_x, circle_C_point.raw_y, C_best_i,
               circle_C_search_angle, C_trace_num, circle_C_join_ok);
    }
}

/* BEGIN 阶段找 C：
 * 从 B 点上方开始，沿预测方向搜线，用局部角度 NMS 找弯道最深处的角点。
 * C 稳定后可作为比 B 更深的入环参考。
 *
 * 返回：1 找到，0 没找到
 */
static int find_C_begin(int side)
{
    C_reset();
    if(!C_has_B()) return 0;
    if(!C_seed(side)) return 0;
    if(!C_trace(side)) return 0;
    if(!C_pick()) return 0;
    C_lock();
    C_log(side);
    return 1;
}

/* B 连续稳定且 y 坐标足够远，才允许开始找 C。
 * 这是一个门控条件：B 还不稳定时，C 搜索没有意义（参考点会漂移）。
 * B_OK_FRAMES=2 表示 B 连续 2 帧 ready 才放行。 */
static int circle_C_phase_ready(void)
{
    return circle_B_streak >= B_OK_FRAMES &&
           circle_B_point.found &&
           circle_B_point.raw_y >= B_READY_Y;
}

static int circle_update_C(int side)
{
    if(!circle_C_phase_ready())
    {
        clear_anchor(&circle_C_point);
        circle_C_search_num = 0;
        circle_C_search_reason = CIRCLE_POINT_SEARCH_PHASE_GATE;
        circle_C_search_detail = "b_not_ready";
        circle_C_search_seed_x = -1;
        circle_C_search_seed_y = -1;
        circle_C_search_best_i = -1;
        circle_C_search_slope = 0.0f;
        circle_C_search_angle = 0.0f;
        circle_C_join_ok = 0;
        return 0;
    }
    return find_C_begin(side);
}

/* 记录 A/B/C 三锚点的完整状态（仅 circle_cal_log_enabled 时输出）。
 * 这是最详细的日志，包含所有锚点、搜索状态、streak、参考模式等信息。
 * 用于调参时分析状态机的整体行为。 */
static void log_circle_abc(int side, const char *phase, int mouth_ready)
{
    if(!circle_cal_log_enabled() || circle_type == CIRCLE_NONE) return;
    printf("ATGCircleABC: side=%c phase=%s ref=%d(%s) rpts=%d/%d lpt=%d@%d/%d@%d "
           "seed_line=%d@%d,%d B_offset=%d "
           "A=%d@%d,%d#%d B=%d@%d,%d#%d B_streak=%d B_ready=%d B_ready_y=%d "
           "B_search=%s/%s trace=%d seed=%d,%d best=%d,%d slope=%.3f "
           "C=%d@%d,%d#%d C_streak=%d C_ready=%d C_join=%d C_search=%s/%s trace=%d seed=%d,%d best_i=%d angle=%.3f slope=%.3f "
           "mouth_ready=%d heading=%d begin_dist=%lld\n",
           side_char(side), phase, (int)circle_ref_mode, circle_ref_mode_name(circle_ref_mode),
           rpts0s_num, rpts1s_num,
           Lpt0_found ? 1 : 0, Lpt0_found ? Lpt0_rpts0s_id : -1,
           Lpt1_found ? 1 : 0, Lpt1_found ? Lpt1_rpts1s_id : -1,
           circle_seed_line_valid[side], circle_seed_line_x[side], circle_seed_line_y[side],
           signed_B_seed_offset(side),
           circle_A_point.found, circle_A_point.raw_x, circle_A_point.raw_y, circle_A_point.id,
           circle_B_point.found, circle_B_point.raw_x, circle_B_point.raw_y, circle_B_point.id,
           circle_B_streak, circle_B_search_ready, B_READY_Y,
           point_search_reason_name(circle_B_search_reason),
           circle_B_search_detail ? circle_B_search_detail : "unknown",
           circle_B_search_num, circle_B_search_seed_x, circle_B_search_seed_y,
           circle_B_search_best_x, circle_B_search_best_y, circle_B_search_slope,
           circle_C_point.found, circle_C_point.raw_x, circle_C_point.raw_y, circle_C_point.id,
           circle_C_streak, circle_C_streak >= C_OK_FRAMES, circle_C_join_ok,
           point_search_reason_name(circle_C_search_reason),
           circle_C_search_detail ? circle_C_search_detail : "unknown",
           circle_C_search_num, circle_C_search_seed_x, circle_C_search_seed_y,
           circle_C_search_best_i, circle_C_search_angle, circle_C_search_slope,
           mouth_ready, circle_heading_deg10(), (long long)atg_reference_circle_begin_dist());
}

/* 入环候选检测（投票阶段用）。
 *
 * 判断逻辑（全部满足才认为"可能是圆环入口"）：
 *   1. 本侧有 L 点 → 说明本侧有拐点
 *   2. L 点 id < 35 → 太远的 L 点不可信（id 越小越靠近画面底部，越近）
 *   3. L 点 y < 100 → 太靠下的 L 点不像入口（入口应在画面上半部分）
 *   4. 对侧没有 L 点 → 对侧是直道（圆环入口的典型特征）
 *   5. 对侧是直道 → 进一步确认不是普通弯道
 *
 * 为什么需要连续 2 帧？
 *   单帧可能因为噪声误判，连续 2 帧命中可以过滤掉大部分噪声。
 *   ENTRY_OK_FRAMES=2 是经验值，太大会延迟入环检测。
 *
 * 为什么对侧必须是直道？
 *   圆环入口的几何特征：本侧是弯道（有 L 点），对侧是直道（没有 L 点）。
 *   普通弯道两侧都有 L 点，所以可以通过"对侧无 L 点"区分。 */
static int circle_entry_detect(int side, circle_point_t *A)
{
    enum { max_id = 35 };                              /* L 点 id 太大说明太远，不可信 */

    if(!circle_get_A(side, A)) return 0;               /* 本侧没有 L 点 */
    if(side_lpt_id(side) < 0 || side_lpt_id(side) >= max_id) return 0; /* L 点太远 */
    if(A->y > 100) return 0;                           /* A 在画面太下方，不像入口 */
    if(side_opposite_lpt_found(side) || !side_opposite_straight(side)) return 0; /* 对侧不是直道 */
    if(circle_cal_log_enabled()) (void)circle_inner_hit(side, A); /* 仅日志用，不影响逻辑 */
    return 1;
}

/* 更新 ENTRY 阶段的 A 点。
 * 每帧调用，如果本侧 L 点存在且 id < 35，就更新 circle_A_point。
 * 同时更新 seed_line 到 A 的坐标（后续 B 搜索从 A 出发）。 */
static int circle_update_entry_A(int side)
{
    enum { max_id = 35 };

    circle_point_t A = {0, 0};
    if(!circle_get_A(side, &A)) return 0;
    if(side_lpt_id(side) < 0 || side_lpt_id(side) >= max_id) return 0;
    store_anchor(&circle_A_point, side_lpt_id(side), &A);
    set_seed_line_from_A(side, &circle_A_point);
    return 1;
}

/* 投票通过后进入 ENTRY 状态：
 * 1. 重置所有几何状态（A/B/C 点、seed_line 等）
 * 2. 从暂存的 A 点恢复到正式的 circle_A_point
 * 3. 重置投票计数
 * 4. 开启距离计数（用于后续判断口部丢失时机） */
static void enter_circle_entry(int side)
{
    const circle_anchor_point_t pending_A = circle_entry_pending_A[side];
    log_circle_state(circle_type, (enum circle_type_e)side_entry_state(side), "entry_vote");
    circle_type = (enum circle_type_e)side_entry_state(side);
    reset_circle_begin_flags();
    reset_circle_geometry_state();
    if(pending_A.found)
    {
        circle_A_point = pending_A;
        set_seed_line_from_A(side, &circle_A_point);
    }
    circle_entry_ever_valid_B[side] = 0;
    Count_dis_Flag = 0;
    reset_circle_entry_votes();
}

/* ENTRY 阶段撤回（假入口、远端 L 点与 B 太近等）：
 * 与 abort_circle_begin 类似，但不重置 loss_start_begin_dist。
 * 调用时机：b_ret == -1（假 B）、A 太近且从未见过 B。 */
static void abort_circle_entry(int side, const char *reason)
{
    log_circle_state(circle_type, CIRCLE_NONE, reason);
    circle_type = CIRCLE_NONE;
    circle_ref_mode = CIRCLE_REF_NONE;
    Count_dis_Flag = 0;
    reset_circle_begin_flags();
    reset_circle_geometry_state();
    reset_circle_entry_votes();
    suppress_circle_reentry_after_exit();
    (void)side;
}

/* ENTRY → BEGIN 状态转换：
 * 1. 保留 B 点，清除 A 点（B 已经比 A 更准确）
 * 2. 切换 seed_line 到 B 的坐标（后续 C 搜索从 B 出发）
 * 3. 重置 C 稳定计数和 B 连续计数
 * 4. 参考模式设为 BEGIN_AB（用 B 做参考，等 C 稳定后切换到 IN_C） */
static void promote_entry_to_begin(int side)
{
    const circle_anchor_point_t B = circle_B_point;
    log_circle_state(circle_type, (enum circle_type_e)side_begin_state(side), "b_ready");
    circle_type = (enum circle_type_e)side_begin_state(side);
    clear_anchor(&circle_A_point);
    circle_B_point = B;
    set_seed_line_from_B(side, &circle_B_point);
    circle_C_streak = 0;
    circle_ref_mode = CIRCLE_REF_BEGIN_AB;
    circle_entry_ever_valid_B[side] = 0;
    circle_B_streak = 0;
    reset_circle_begin_flags();
    Count_dis_Flag = 0;
}

/* ================= ENTRY 状态：找 A/B，确认进入 BEGIN =================
 *
 * ENTRY 的任务：
 * 1. 更新或沿用锁定 A；
 * 2. 从 A 出发找 B；
 * 3. B 连续稳定后进入 BEGIN；
 * 4. 如果 A 已经太近但一直没见过 B，撤回圆环。
 *
 * 状态转换：
 *   成功：B 连续 ready B_OK_FRAMES 帧 → promote_entry_to_begin()
 *   失败：b_ret == -1（假 B）→ abort
 *         A 太近且从未见过 B → abort
 */
static void run_circle_entry(int side)
{
    enum { near_id = 8 };                              /* A 的 id ≤ 8 认为"太近" */

    const int a_visible = circle_update_entry_A(side);
    const int a_near = a_visible && side_lpt_id(side) <= near_id;

    /* ENTRY 锁定后，A 可能在后续帧消失（L 点丢失）。
     * 此时继续使用 circle_A_point 里保存的最后一个 A 去找 B。 */
    const int b_ret = find_B_entry(side);

    track_type = side_begin_track(side);
    circle_ref_mode = CIRCLE_REF_NONE;

    /* b_ret < 0：远端 L 点与 B 太近，假入口，立刻撤回 */
    if(b_ret < 0)
    {
        log_entry_probe(side, b_ret);
        abort_circle_entry(side, side_is_left(side) ? "LEFT_ENTRY false_b" : "RIGHT_ENTRY false_b");
        return;
    }

    if(b_ret == 1)
    {
        /* 只要见过一次有效 B，后续 A 消失就不能撤回 ENTRY。
         * 这是为了防止 A 短暂丢失导致误撤回。 */
        circle_entry_ever_valid_B[side] = 1;
        if(circle_B_search_ready) circle_B_streak++;
        else circle_B_streak = 0;
    }
    else
    {
        log_entry_probe(side, b_ret);
        circle_B_streak = 0;
    }

    log_circle_abc(side, "ENTRY", 0);

    /* B 连续稳定 → 进入 BEGIN */
    if(circle_B_streak >= B_OK_FRAMES &&
       circle_B_point.found &&
       circle_B_search_ready)
    {
        promote_entry_to_begin(side);
        return;
    }

    /* A 太近且从未见过 B → 撤回（假入口） */
    if(!circle_entry_ever_valid_B[side] && (!a_visible || a_near))
    {
        abort_circle_entry(side, side_is_left(side) ? "LEFT_ENTRY no_b_window" : "RIGHT_ENTRY no_b_window");
    }
}

/* 入环投票入口：每帧调用，只在 CIRCLE_NONE 状态下工作。
 *
 * 投票机制：
 *   1. 左右两侧独立投票，互不干扰
 *   2. 每帧检测 circle_entry_detect()，命中则 votes[side]++，否则清零
 *   3. 连续 ENTRY_OK_FRAMES(2) 帧命中 → 进入 ENTRY
 *   4. 投票期间暂存 A 点，投票通过后恢复到正式的 circle_A_point
 *
 * 为什么用投票？
 *   单帧检测可能因为噪声误判，连续 2 帧命中可以过滤掉大部分噪声。
 *   左右独立投票可以同时检测两个方向的圆环（虽然同一时刻只有一个活跃）。 */
void check_circle(void)
{
    if(circle_type != CIRCLE_NONE)
    {
        reset_circle_entry_votes();
        return;
    }
    if(circle_entry_suppressed()) return;

    for(int side = CIRCLE_SIDE_RIGHT; side <= CIRCLE_SIDE_LEFT; side++)
    {
        circle_point_t A = {0, 0};
        if(circle_entry_detect(side, &A))
        {
            if(circle_entry_votes[side] == 0)
            {
                store_anchor(&circle_entry_pending_A[side], side_lpt_id(side), &A);
            }
            circle_entry_votes[side]++;
        }
        else
        {
            circle_entry_votes[side] = 0;
            clear_anchor(&circle_entry_pending_A[side]);
        }
    }

    for(int side = CIRCLE_SIDE_RIGHT; side <= CIRCLE_SIDE_LEFT; side++)
    {
        if(circle_entry_votes[side] >= ENTRY_OK_FRAMES)
        {
            enter_circle_entry(side);
            return;
        }
    }
}

/* BEGIN 阶段跟踪本侧线是否丢失，用于判断假入口撤回。
 *
 * 为什么需要跟踪丢失？
 *   真圆环：进入 BEGIN 后，本侧线会在口部附近丢失（被圆环遮挡），这是正常现象。
 *   假入口：如果 BEGIN 后行驶了很长距离（>4000 counts）才丢线，说明不是真正的圆环入口。
 *
 * 判断逻辑：
 *   rpts 数量 < 2 且无 L 点 → 认为丢失
 *   丢失开始时记录 begin_dist，用于后续判断是否"过晚"
 *
 * rpts_max=2：本侧边线点数少于 2 个且无 L 点，认为边线丢失。
 * 丢失时开启距离计数（Count_dis_Flag=1），用于后续判断丢失时机。 */
static void update_begin_loss(int side)
{
    enum { rpts_max = 2 };

    const int lost = side_rpts_num(side) < rpts_max && !side_lpt_found(side);
    if(lost)
    {
        Count_dis_Flag = 1;
        if(side_is_left(side))
        {
            none_left_line++;
            have_left_line = 0;
        }
        else
        {
            none_right_line++;
            have_right_line = 0;
        }
        if(circle_begin_lost_streak[side] == 0)
        {
            circle_loss_start_begin_dist[side] = atg_reference_circle_begin_dist();
        }
        circle_begin_lost_streak[side]++;
    }
    else
    {
        circle_begin_lost_streak[side] = 0;
        circle_loss_start_begin_dist[side] = -1;
    }
}

/* ================= BEGIN 状态：跟 B、找 C，等待陀螺仪进环 =================
 *
 * BEGIN 的任务：
 * 1. 在 B 附近跟踪 B，防止入口参考点漂移；
 * 2. 从 B 往上找 C，作为更深的入环参考；
 * 3. C 稳定则使用 C，否则用 B 兜底；
 * 4. 陀螺仪角度达到门槛后进入 RUNNING。
 *
 * 参考点切换：
 *   CIRCLE_REF_NONE    → 还没找到可用参考（异常）
 *   CIRCLE_REF_BEGIN_AB → 用 B 做参考（兜底）
 *   CIRCLE_REF_IN_C    → 用 C 做参考（更稳定）
 *
 * 状态转换：
 *   成功：陀螺仪 ≥ 60° → RUNNING
 *   失败：口部丢失过晚（距离 > 4000）→ 撤回
 */
static void run_circle_begin(int side)
{
    enum
    {
        lost_frames = 2,       /* 连续丢失 2 帧才触发撤回判断 */
        max_dist = 4000,       /* 行驶超过此距离后口部丢失视为假入口 */
    };

    track_type = side_begin_track(side);

    /* 1. 跟踪本侧线丢失情况（用于假入口判断） */
    update_begin_loss(side);

    /* 2. 跟踪 B 漂移 */
    if(follow_B_begin(side)) circle_B_follow_fail_streak[side] = 0;
    else
    {
        circle_B_follow_fail_streak[side]++;
        log_B_follow_miss(side);
    }

    /* 3. 尝试找 C */
    if(circle_update_C(side) && circle_C_join_ok) circle_C_streak++;
    else circle_C_streak = 0;

    /* 4. 决定参考点模式 */
    circle_ref_mode = (circle_C_streak >= C_OK_FRAMES && circle_C_join_ok) ? CIRCLE_REF_IN_C :
                      circle_B_point.found ? CIRCLE_REF_BEGIN_AB : CIRCLE_REF_NONE;
    log_circle_abc(side, "BEGIN", 0);

    /* 5. 陀螺仪达标 → 进入 RUNNING */
    if(circle_heading_abs_ge(GYRO_IN_DEG10))
    {
        log_circle_state(circle_type, (enum circle_type_e)side_running_state(side),
                         circle_C_streak >= C_OK_FRAMES ? "gyro_c" : "gyro");
        circle_type = (enum circle_type_e)side_running_state(side);
        circle_ref_mode = CIRCLE_REF_NONE;
        reset_circle_heading();
        if(side_is_left(side)) if_lost_right_line = 0;
        else if_lost_left_line = 0;
        reset_circle_begin_flags();
        clear_anchor(&circle_C_point);
        circle_C_streak = 0;
        Count_dis_Flag = 0;
        return;
    }

    /* 6. 口部丢失过晚 → 撤回（假入口）。
     * 真圆环在 BEGIN 后很快就会丢线（口部遮挡），如果行驶了 4000 counts（约 0.7m）才丢线，
     * 说明是直道上的假 L 点误触发，需要撤回。 */
    const int abort_late_mouth_loss =
        circle_begin_lost_streak[side] >= lost_frames &&
        circle_loss_start_begin_dist[side] > max_dist;
    if(abort_late_mouth_loss)
    {
        abort_circle_begin(side_is_left(side) ? "LEFT_BEGIN mouth_loss too late" :
                                                "RIGHT_BEGIN mouth_loss too late");
    }
}

/* ================= RUNNING 状态：环内行驶，等待出环条件 =================
 *
 * RUNNING 不再找 A/B/C，只靠陀螺仪和对侧 L 点判断是否准备出环。
 *
 * 出环条件（满足其一）：
 *   1. 视觉+陀螺仪联合：对侧 L 点 id < OUT_LPT_NEAR_ID(55) 且陀螺仪 ≥ GYRO_OUT_DEG10(150°)
 *      这表示"看到出口了，而且转够了"。
 *   2. 强制出环：陀螺仪 ≥ GYRO_FORCE_OUT_DEG10(200°)
 *      即使视觉没看到出口，转了 200° 也该出环了（防止视觉丢失时卡在环里）。
 *
 * 为什么用对侧 L 点？
 *   出口在对侧，所以对侧会出现 L 点（出口的拐点）。
 *   本侧 L 点是入口的拐点，出环时已经看不见了。 */
static void run_circle_running(int side)
{
    track_type = side_begin_track(side);
    Count_dis_Flag = 1;
    if(side_opposite_lpt_found(side) &&
       side_opposite_lpt_id(side) < OUT_LPT_NEAR_ID &&
       circle_heading_abs_ge(GYRO_OUT_DEG10))
    {
        log_circle_state(circle_type, (enum circle_type_e)side_out_state(side), "vision_lpt");
        circle_type = (enum circle_type_e)side_out_state(side);
        circle_out_straight_streak[side] = 0;
        Count_dis_Flag = 0;
        if(side_is_left(side)) if_lost_right_line = 0;
        else if_lost_left_line = 0;
    }
    else if(circle_heading_abs_ge(GYRO_FORCE_OUT_DEG10))
    {
        log_circle_state(circle_type, (enum circle_type_e)side_out_state(side), "gyro");
        circle_type = (enum circle_type_e)side_out_state(side);
        circle_out_straight_streak[side] = 0;
        Count_dis_Flag = 0;
        if(side_is_left(side)) if_lost_right_line = 0;
        else if_lost_left_line = 0;
    }
}

/* ================= OUT 状态：出环后恢复正常巡线 =================
 *
 * 出环后切到对侧巡线，等连续直道检测确认后回到 NONE。
 *
 * 出环策略：
 *   1. 切到对侧巡线（左环切右线，右环切左线）
 *   2. 等连续 OUT_STRAIGHT_FRAMES(2) 帧检测到对侧是直道 → 确认已出环，回到 NONE
 *   3. 退出后抑制 REENTRY_SUPPRESS_FRAMES(150) 帧，防止立刻重新误触发
 *
 * 为什么切到对侧？
 *   出环时车在圆环外侧，对侧线更接近赛道中心。 */
static void run_circle_out(int side)
{
    track_type = side_out_track(side);
    Count_dis_Flag = 1;

    if(side_out_straight(side)) circle_out_straight_streak[side]++;
    else circle_out_straight_streak[side] = 0;

    if(circle_out_straight_streak[side] >= OUT_STRAIGHT_FRAMES)
    {
        finish_circle_exit("straight_exit");
    }
}


/* ================= 圆环主流程 ================= */

/* 圆环主流程：根据当前状态分发到对应的状态处理函数。
 * 这是状态机的核心调度，每帧调用一次。
 * circle_type 在状态切换时被修改，下一帧就会进入新的分支。 */
void run_circle(void)
{
    switch(circle_type)
    {
    case CIRCLE_LEFT_ENTRY: run_circle_entry(CIRCLE_SIDE_LEFT); break;
    case CIRCLE_RIGHT_ENTRY: run_circle_entry(CIRCLE_SIDE_RIGHT); break;
    case CIRCLE_LEFT_BEGIN: run_circle_begin(CIRCLE_SIDE_LEFT); break;
    case CIRCLE_RIGHT_BEGIN: run_circle_begin(CIRCLE_SIDE_RIGHT); break;
    case CIRCLE_LEFT_RUNNING: run_circle_running(CIRCLE_SIDE_LEFT); break;
    case CIRCLE_RIGHT_RUNNING: run_circle_running(CIRCLE_SIDE_RIGHT); break;
    case CIRCLE_LEFT_OUT: run_circle_out(CIRCLE_SIDE_LEFT); break;
    case CIRCLE_RIGHT_OUT: run_circle_out(CIRCLE_SIDE_RIGHT); break;
    default: break;
    }
}
