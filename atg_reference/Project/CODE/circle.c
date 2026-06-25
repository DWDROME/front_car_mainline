#include "circle.h"
#include "atg_reference_step.h"
#include "motor.h"
#include "headfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENCODER_PER_METER   (5800)
int circle_count;
enum circle_type_e circle_type = CIRCLE_NONE;
enum circle_ref_mode_e circle_ref_mode = CIRCLE_REF_NONE;
circle_anchor_point_t circle_A_point;
circle_anchor_point_t circle_B_point;
circle_anchor_point_t circle_C_point;


const char *circle_type_name[CIRCLE_NUM] = {
        "CIRCLE_NONE",
        "CIRCLE_LEFT_BEGIN", "CIRCLE_RIGHT_BEGIN",
        "CIRCLE_LEFT_RUNNING", "CIRCLE_RIGHT_RUNNING",
        "CIRCLE_LEFT_OUT", "CIRCLE_RIGHT_OUT",
};


int none_left_line = 0, none_right_line = 0;                //丢线标志位
int have_left_line = 0, have_right_line = 0;                //重找到线的线标志位

enum
{
    CIRCLE_ENTRY_CONFIRM_FRAMES = 2,
    CIRCLE_BEGIN_LOST_CONFIRM_FRAMES = 2,
    CIRCLE_BEGIN_LOST_RPTS_MAX = 2,
    CIRCLE_B_CONFIRM_FRAMES = 2,
    CIRCLE_C_CONFIRM_FRAMES = 2,
    // CIRCLE_B_ENTER_ROW: y=0 在图像顶部, y=120 在底部
    // raw_y >= 58 表示 B 靠近车身(下方),用于判断是否进入圆环
    // 当前只用于改 ref_mode，不做状态切换
    CIRCLE_B_ENTER_ROW = 58,
    // 旧 mouth_loss 方案的诊断门限。现在只打印 mouth_ready, 不再推进 BEGIN->IN。
    CIRCLE_BEGIN_MOUTH_MIN_DIST = 600,
    // 真双断点 A+B 约束: A 不能太远, A/B 必须分离(不是同一个断点)。
    CIRCLE_ENTRY_A_ID_MAX = 35,
    CIRCLE_ENTRY_AB_DIST_MIN = 23,     // IPM 欧氏距离,≈ 0.20m * 116px/m
    CIRCLE_ENTRY_AB_Y_MIN = 8,        // 纵向分离像素(圆弧B近,满足此值即可)
    CIRCLE_ENTRY_AB_X_MIN = 6,        // B 必须向对侧弧面展开,不能只是 A 同列上方黑边
    CIRCLE_ENTRY_B_SKIP_EDGE_X = 20,  // 跳过近端线边缘假目标,再找对侧弧面 B
    CIRCLE_ENTRY_B_SCAN_SPAN_X = 60,  // B 只在口门横向窗口内找,避免扫到远侧普通边线
    CIRCLE_ENTRY_B_MIN_HITS = 1,  // 远点内圆边界仅1-2行可见,降低门槛(AB约束(dy/dist/dx)已防噪)
    // B 必须在 A 上方高度窗口中:A_raw_y - B_raw_y ∈ [UP_MIN, UP_MAX]
    // 坐标系:y=0 在图像顶部(远处), y=120 在底部(车身)。A_y≈80(近), B_y≈41(远弧顶)。窗口靠实测定。
    CIRCLE_B_UP_MIN = 15,
    CIRCLE_B_UP_MAX = 50,
    CIRCLE_ENTRY_B_MIN_RISE_HITS = 1,  // 远端弧面可见点少,AB 几何继续防噪
    CIRCLE_ENTRY_B_MAX_STEP_X = 18,
    CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST = 20,
    // BEGIN→IN mouth_loss 相位窗:丢线只能在合理 begin_dist 窗口内触发。
    // mouth_loss_too_late 保护车已拖到中间圆才丢线(实测喉口丢线 begin_dist~1200~1700)。
    CIRCLE_BEGIN_LOSS_MAX_DIST = 4000, // 超出此距离的丢线=拖太晚,撤回
    // 线方差判据:B 点在弧面上弯度自然大;只做诊断,不做硬门。
    // (原在 A 点区域算方差无意义——A 还在直道段,var 天然≈0.3)。
    CIRCLE_ENTRY_ANGLE_VAR_WINDOW = 10,
    CIRCLE_ENTRY_MIN_ANGLE_VAR = 1,       // B 点弧面弯度足够大,诊断用
    // 参考陀螺积分圆环：阈值单位是 0.1 度，进 IN 后单次清零，后续累计比较。
    CIRCLE_HEADING_ENTER_DEG10 = 600,
    CIRCLE_HEADING_START_OUT_DEG10 = 2000,
    // 阶段2(视觉驱动+陀螺门限): RUNNING->OUT 改为"对侧出口角点出现 + 陀螺过门限"为主, 陀螺 START_OUT 兜底。两值待 live 标定。
    CIRCLE_HEADING_OUT_GATE_DEG10 = 1500,   // 视觉出环的陀螺门限(< START_OUT 2000), 防光干扰/假角点早触发; live 调
    CIRCLE_OUT_LPT_NEAR_ID = 55,            // 对侧出口角点足够近的 rpts id 阈值, 确认车已到出环口; live 调 (drive02 左环对侧 Lpt 出现在 id=51, 原 25 偏严)
    // drive24: 260度可出环, END内guide穿零后交棒; drive25: 250度退环太早, guide仍为负会回起点。
    CIRCLE_HEADING_READY_OUT_TO_END_DEG10 = 2660,
    // END 安全释放:主出口仍是视觉近角点;编码器释放只防止 END 固定补线死锁。
    CIRCLE_HEADING_FINISH_SOFT_DEG10 = 3300,
    CIRCLE_REENTRY_SUPPRESS_FRAMES = 150,
};
static const float CIRCLE_GYRO_DEADZONE_RAD_S = 0.065f;
static const float CIRCLE_RAD_TO_DEG10 = 1800.0f / 3.14159265358979f;

static int circle_left_entry_votes;
static int circle_right_entry_votes;
static int circle_entry_suppress_frames;
static float circle_heading_rad;
// BEGIN 内连续丢线计数(恢复即清零),用于喉口相位锚定。区别于 latch 的 none_*_line。
static int circle_left_begin_lost_streak;
static int circle_right_begin_lost_streak;
// 丢线起点 begin_dist(用于正确判断"第一次丢线窗口是否太早")。
static int64_t circle_left_loss_start_begin_dist = -1;
static int64_t circle_right_loss_start_begin_dist = -1;
static int circle_left_out_straight_streak;  // OUT→NONE 对侧直线连续帧
static int circle_right_out_straight_streak;
static int circle_B_streak;
static int circle_C_streak;
static int circle_B_search_reason;
static int circle_B_search_num;
static int circle_B_search_a_found;
static int circle_B_search_a_id;
static int circle_B_search_start;
static int circle_B_search_end;
static const char *circle_B_search_detail;
static int circle_B_search_scan_x;
static int circle_B_search_scan_end_x;
static int circle_B_search_best_x;
static int circle_B_search_best_y;
static int circle_B_search_rise_hits;
static int circle_B_search_dx;
static int circle_B_search_inner_dx;
static int circle_B_search_dy;
static int circle_B_search_up_dy;
static int circle_B_search_dist2;
static int circle_B_search_jump_bad;
static int circle_B_search_sharp_far;
static int circle_C_search_reason;
static int circle_C_search_num;
static int circle_C_search_b_found;
static int circle_C_search_b_id;
static int circle_C_search_start;
static int circle_C_search_end;

enum
{
    CIRCLE_POINT_SEARCH_OK = 0,
    CIRCLE_POINT_SEARCH_NO_A = 1,
    CIRCLE_POINT_SEARCH_SHORT_LINE = 2,
    CIRCLE_POINT_SEARCH_NO_B = 3,
    CIRCLE_POINT_SEARCH_NO_EXTREME = 4,
    CIRCLE_POINT_SEARCH_NO_V = 5,
};

static const char *circle_ref_mode_name(enum circle_ref_mode_e mode)
{
    switch(mode)
    {
    case CIRCLE_REF_NONE:
        return "none";
    case CIRCLE_REF_BEGIN_AB:
        return "begin_ab";
    case CIRCLE_REF_IN_C:
        return "in_c";
    default:
        return "unknown";
    }
}

static const char *circle_point_search_reason_name(int reason)
{
    switch(reason)
    {
    case CIRCLE_POINT_SEARCH_OK:
        return "ok";
    case CIRCLE_POINT_SEARCH_NO_A:
        return "no_a";
    case CIRCLE_POINT_SEARCH_SHORT_LINE:
        return "short_line";
    case CIRCLE_POINT_SEARCH_NO_B:
        return "no_b";
    case CIRCLE_POINT_SEARCH_NO_EXTREME:
        return "no_extreme";
    case CIRCLE_POINT_SEARCH_NO_V:
        return "no_v";
    default:
        return "unknown";
    }
}

int circle_cal_log_enabled(void)
{
    const char *val = getenv("FRONT_CAR_CIRCLE_CAL_LOG");
    static int warned_invalid;
    if(val == NULL || val[0] == '\0' || strcmp(val, "0") == 0 || strcmp(val, "false") == 0)
    {
        return 0;
    }
    if(strcmp(val, "1") == 0 || strcmp(val, "true") == 0)
    {
        return 1;
    }
    if(!warned_invalid)
    {
        printf("EnvWarn: invalid flag for FRONT_CAR_CIRCLE_CAL_LOG='%s'\n", val);
        warned_invalid = 1;
    }
    return 0;
}

static void print_circle_entry_probe_diag(int left_side,
                                          int a_id,
                                          int a_rx,
                                          int a_ry,
                                          int b_ret)
{
    if(!circle_cal_log_enabled())
    {
        return;
    }
    printf("ATGCircleEntryProbe: side=%c A=1@%d(raw=%d,%d) B=0 ret=%d reason=%s detail=%s "
           "hits=%d rise=%d range=%d..%d scan_x=%d..%d best=%d,%d dx=%d inner_dx=%d "
           "dy=%d up_dy=%d dist2=%d jump=%d sharp_far=%d\n",
           left_side ? 'L' : 'R',
           a_id,
           a_rx,
           a_ry,
           b_ret,
           circle_point_search_reason_name(circle_B_search_reason),
           circle_B_search_detail ? circle_B_search_detail : "unknown",
           circle_B_search_num,
           circle_B_search_rise_hits,
           circle_B_search_start,
           circle_B_search_end,
           circle_B_search_scan_x,
           circle_B_search_scan_end_x,
           circle_B_search_best_x,
           circle_B_search_best_y,
           circle_B_search_dx,
           circle_B_search_inner_dx,
           circle_B_search_dy,
           circle_B_search_up_dy,
           circle_B_search_dist2,
           circle_B_search_jump_bad,
           circle_B_search_sharp_far);
}

static int circle_heading_deg10(void)
{
    return (int)(fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10);
}

static void print_circle_transition(enum circle_type_e from,
                                    enum circle_type_e to,
                                    const char *reason)
{
    if(!circle_cal_log_enabled())
    {
        return;
    }
    printf("ATGCircleCal: from=%s to=%s reason=%s heading_deg10=%d dist=%d begin_dist=%lld begin_last=%lld\n",
           circle_type_name[from],
           circle_type_name[to],
           reason,
           circle_heading_deg10(),
           total_distence,
           (long long)atg_reference_circle_begin_dist(),
           (long long)atg_reference_circle_begin_last_dist());
}

void reset_circle_entry_votes()
{
    circle_left_entry_votes = 0;
    circle_right_entry_votes = 0;
}

void suppress_circle_entry_frames(int frames)
{
    if(frames > circle_entry_suppress_frames)
    {
        circle_entry_suppress_frames = frames;
    }
    reset_circle_entry_votes();
}

void suppress_circle_reentry_after_exit(void)
{
    suppress_circle_entry_frames(CIRCLE_REENTRY_SUPPRESS_FRAMES);
}

void clear_circle_entry_suppression(void)
{
    circle_entry_suppress_frames = 0;
}

static int circle_entry_suppressed(void)
{
    if(circle_entry_suppress_frames <= 0)
    {
        return 0;
    }
    circle_entry_suppress_frames--;
    reset_circle_entry_votes();
    return 1;
}

void reset_circle_begin_flags()
{
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    circle_left_begin_lost_streak = 0;
    circle_right_begin_lost_streak = 0;
}

void reset_circle_geometry_state(void)
{
    circle_ref_mode = CIRCLE_REF_NONE;
    memset(&circle_A_point, 0, sizeof(circle_A_point));
    memset(&circle_B_point, 0, sizeof(circle_B_point));
    memset(&circle_C_point, 0, sizeof(circle_C_point));
    circle_left_out_straight_streak = 0;
    circle_right_out_straight_streak = 0;
    circle_B_streak = 0;
    circle_C_streak = 0;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_num = 0;
    circle_B_search_a_found = 0;
    circle_B_search_a_id = -1;
    circle_B_search_start = -1;
    circle_B_search_end = -1;
    circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_C_search_num = 0;
    circle_C_search_b_found = 0;
    circle_C_search_b_id = -1;
    circle_C_search_start = -1;
    circle_C_search_end = -1;
}

static void reset_circle_heading(void)
{
    circle_heading_rad = 0.0f;
}

void update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid)
{
    if(circle_type == CIRCLE_NONE)
    {
        reset_circle_heading();
        return;
    }
    if(!valid || period_ms <= 0)
    {
        return;
    }

    if(fabsf(yaw_rate_rad_s) <= CIRCLE_GYRO_DEADZONE_RAD_S)
    {
        return;
    }
    circle_heading_rad += yaw_rate_rad_s * ((float)period_ms / 1000.0f);
}

static int circle_heading_abs_ge(int tenth_deg)
{
    return fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10 >= (float)tenth_deg;
}

int circle_heading_enter_ready(void)
{
    return circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10);
}

static void finish_circle_exit(const char *reason)
{
    print_circle_transition(circle_type, CIRCLE_NONE, reason);
    circle_type = CIRCLE_NONE;
    road_type = ROAD_NORMAL;
    begin_y = BEGIN_Y;
    Count_dis_Flag = 0;
    aim_distance = AIM_DISTENCE;
    if_lost_right_line = 0;
    if_lost_left_line = 0;
    circle_count++;
    none_right_line = 0;
    have_right_line = 0;
    none_left_line = 0;
    have_left_line = 0;
    reset_circle_geometry_state();
    suppress_circle_reentry_after_exit();
}

// BEGIN abort:mouth_loss 太晚丢线,直接撤回 NONE,不等 reference_step idle revoke。
static void abort_circle_begin(const char *reason)
{
    print_circle_transition(circle_type, CIRCLE_NONE, reason);
    circle_type = CIRCLE_NONE;
    Count_dis_Flag = 0;
    reset_circle_begin_flags();
    reset_circle_geometry_state();
    reset_circle_entry_votes();
    circle_ref_mode = CIRCLE_REF_NONE;
    circle_left_begin_lost_streak = 0;
    circle_right_begin_lost_streak = 0;
    circle_left_loss_start_begin_dist = -1;
    circle_right_loss_start_begin_dist = -1;
    suppress_circle_reentry_after_exit();
}

static int circle_get_raw_point(int left_side, int id, int *raw_x, int *raw_y)
{
    const int num = left_side ? rpts0s_num : rpts1s_num;
    float (*pts)[2] = left_side ? rpts0s : rpts1s;
    if(id < 0 || id >= num)
    {
        return 0;
    }
    *raw_x = (int)Cal_inv_rot_x(pts[id][0], pts[id][1]);
    *raw_y = (int)Cal_inv_rot_y(pts[id][0], pts[id][1]);
    return 1;
}

static void latch_circle_A(int left_circle)
{
    const int found = left_circle ? (Lpt0_found ? 1 : 0) : (Lpt1_found ? 1 : 0);
    const int id = left_circle ? Lpt0_rpts0s_id : Lpt1_rpts1s_id;
    int raw_x = 0;
    int raw_y = 0;
    circle_A_point.found = 0;
    circle_A_point.id = -1;
    if(found && circle_get_raw_point(left_circle, id, &raw_x, &raw_y))
    {
        circle_A_point.found = 1;
        circle_A_point.id = id;
        circle_A_point.raw_x = raw_x;
        circle_A_point.raw_y = raw_y;
    }
}

// 从 B 沿竖线往上继续扫,找 C 点(更上方的尖锐角点)。
// 圆环的 A-B-C 三个点沿同一条竖线: A=近断点, B=弧顶(非尖锐), C=最高处的角点(尖锐).
// C 找到 → 可拉线 A→B→C 进圆。
static int find_circle_C(int left_circle)
{
    circle_C_search_num = 0;
    circle_C_search_b_found = circle_B_point.found;
    circle_C_search_b_id = circle_B_point.id;
    circle_C_search_start = -1;
    circle_C_search_end = -1;
    circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_C_point.found = 0;
    circle_C_point.id = -1;

    if(!circle_B_point.found)
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_B;
        return 0;
    }

    const int inner_dir = left_circle ? -1 : 1;
    const int x_limit = left_circle ? block_size / 2 : MT9V03X_W - block_size / 2 - 1;

    // 从 B 的位置,沿 B 的 x 列往上扫,每行往内侧扫到底找黑点
    // y 坐标减小 = 往图像顶部/远处走
    for(int y = circle_B_point.raw_y - 1; y > block_size / 2 + 5; y--)
    {
        int hit_x = -1;
        for(int x = circle_B_point.raw_x; left_circle ? (x >= x_limit) : (x <= x_limit); x += inner_dir)
        {
            if(x < block_size / 2 || x >= MT9V03X_W - block_size / 2) continue;
            int lt = 0;
            for(int dy = -block_size / 2; dy <= block_size / 2; dy++)
                for(int dx = -block_size / 2; dx <= block_size / 2; dx++)
                    lt += AT_IMAGE(&img_raw, x + dx, y + dy);
            lt = lt / (block_size * block_size) - clip_value;
            if(AT_IMAGE(&img_raw, x, y) < lt && y > 10) { hit_x = x; break; }
        }
        if(hit_x < 0) continue;

        // C 是尖锐角点:和最内侧方向一致(左环往左,右环往右),x 出现跳变→拐角
        // 简单判据:当前行能找到黑点,且 x 明显缩回或跳变(弧顶已过后的拐角)。
        // 实际用:当前行 hit_x 和 B 的 x 差距超过阈值,即认为找到了 C(上方另一个结构)。
        const int dx_from_b = left_circle ? (circle_B_point.raw_x - hit_x) : (hit_x - circle_B_point.raw_x);
        if(dx_from_b > 15 || dx_from_b < -5)
        {
            // C 找到:位置明显不同于 B(尖锐拐角或更外侧)
            circle_C_point.found = 1;
            circle_C_point.id = -1;
            circle_C_point.raw_x = hit_x;
            circle_C_point.raw_y = y;
            circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
            circle_C_search_start = -1;
            circle_C_search_end = y;
            return 1;
        }
    }

    circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_V;
    return 0;
}

static void print_circle_abc_diag(char side, const char *phase, int mouth_ready)
{
    if(circle_type == CIRCLE_NONE)
    {
        return;
    }
    if(!circle_cal_log_enabled())
    {
        return;
    }
    printf("ATGCircleABCDiag: side=%c phase=%s ref=%d(%s) rpts=%d/%d lpt=%d@%d/%d@%d "
           "A=%d@%d,%d#%d "
           "B=%d@%d,%d#%d B_streak=%d B_row_ready=%d B_enter_row=%d "
           "B_search=%s num=%d Acur=%d@%d range=%d..%d "
           "C=%d@%d,%d#%d C_streak=%d C_ready=%d "
           "C_search=%s num=%d Bcur=%d@%d range=%d..%d "
           "mouth_ready=%d heading=%d begin_dist=%lld\n",
           side,
           phase,
           (int)circle_ref_mode,
           circle_ref_mode_name(circle_ref_mode),
           rpts0s_num,
           rpts1s_num,
           Lpt0_found ? 1 : 0,
           Lpt0_found ? Lpt0_rpts0s_id : -1,
           Lpt1_found ? 1 : 0,
           Lpt1_found ? Lpt1_rpts1s_id : -1,
           circle_A_point.found,
           circle_A_point.found ? circle_A_point.raw_x : -1,
           circle_A_point.found ? circle_A_point.raw_y : -1,
           circle_A_point.id,
           circle_B_point.found,
           circle_B_point.found ? circle_B_point.raw_x : -1,
           circle_B_point.found ? circle_B_point.raw_y : -1,
           circle_B_point.id,
           circle_B_streak,
           (circle_B_streak >= CIRCLE_B_CONFIRM_FRAMES &&
            circle_B_point.found &&
            circle_B_point.raw_y >= CIRCLE_B_ENTER_ROW) ? 1 : 0,
           CIRCLE_B_ENTER_ROW,
           circle_point_search_reason_name(circle_B_search_reason),
           circle_B_search_num,
           circle_B_search_a_found,
           circle_B_search_a_id,
           circle_B_search_start,
           circle_B_search_end,
           circle_C_point.found,
           circle_C_point.found ? circle_C_point.raw_x : -1,
           circle_C_point.found ? circle_C_point.raw_y : -1,
           circle_C_point.id,
           circle_C_streak,
           circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES ? 1 : 0,
           circle_point_search_reason_name(circle_C_search_reason),
           circle_C_search_num,
           circle_C_search_b_found,
           circle_C_search_b_id,
           circle_C_search_start,
           circle_C_search_end,
           mouth_ready,
           circle_heading_deg10(),
           (long long)atg_reference_circle_begin_dist());
}

static void print_left_begin_diag(const char *reason)
{
    if(!circle_cal_log_enabled())
    {
        return;
    }
    printf("ATGCircleBeginDiag: side=L reason=%s rpts0=%d Lpt0=%d none_left=%d lost_streak=%d dist=%d begin_dist=%lld mouth_ready=%d\n",
           reason,
           rpts0s_num,
           Lpt0_found ? 1 : 0,
           none_left_line,
           circle_left_begin_lost_streak,
           total_distence,
           (long long)atg_reference_circle_begin_dist(),
           (circle_left_begin_lost_streak >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
            atg_reference_circle_begin_dist() >= CIRCLE_BEGIN_MOUTH_MIN_DIST) ? 1 : 0);
}

static void print_right_begin_diag(const char *reason)
{
    if(!circle_cal_log_enabled())
    {
        return;
    }
    printf("ATGCircleBeginDiag: side=R reason=%s rpts1=%d Lpt1=%d none_right=%d lost_streak=%d dist=%d begin_dist=%lld mouth_ready=%d\n",
           reason,
           rpts1s_num,
           Lpt1_found ? 1 : 0,
           none_right_line,
           circle_right_begin_lost_streak,
           total_distence,
           (long long)atg_reference_circle_begin_dist(),
           (circle_right_begin_lost_streak >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
            atg_reference_circle_begin_dist() >= CIRCLE_BEGIN_MOUTH_MIN_DIST) ? 1 : 0);
}

// 圆环入口 inner-hit 种子的唯一来源。circle.c 自身扫描与 assistant 显示线必须同源,
// 公式(左 +2/-5、右 +5/-5)只此一份,assistant.cpp::circle_entry_scan_seed_raw 复用本函数。
int circle_entry_inner_seed(int left_side, int *seed_x, int *seed_y,
                            float *seed_raw_x, float *seed_raw_y)
{
    const int lpt_id = left_side ? Lpt0_rpts0s_id : Lpt1_rpts1s_id;
    const int lpt_num = left_side ? rpts0s_num : rpts1s_num;
    const int found_lpt = left_side ? (Lpt0_found ? 1 : 0) : (Lpt1_found ? 1 : 0);

    if(!found_lpt || lpt_num <= 0)
    {
        return 0;
    }

    if(left_side)
    {
        const int id = clip(lpt_id, 0, lpt_num - 1);
        *seed_raw_x = Cal_inv_rot_x(rpts0s[id][0], rpts0s[id][1]) + 2.0f;   // 从角点右侧出发,向左扫内圆黑块有足够空间
        *seed_raw_y = Cal_inv_rot_y(rpts0s[id][0], rpts0s[id][1]) - 5.0f;  // -17→-5:远点入口raw_y太靠上,-17会推出图像顶
    }
    else
    {
        const int id = clip(lpt_id, 0, lpt_num - 1);
        *seed_raw_x = Cal_inv_rot_x(rpts1s[id][0], rpts1s[id][1]) + 5.0f;
        *seed_raw_y = Cal_inv_rot_y(rpts1s[id][0], rpts1s[id][1]) - 5.0f;  // 同上
    }

    *seed_x = clip((int)*seed_raw_x, block_size / 2, MT9V03X_W - block_size / 2 - 1);
    *seed_y = clip((int)*seed_raw_y, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    return 1;
}

static int circle_entry_find_inner_hit_ray(int left_side, int seed_x, int seed_y,
                                           int *hit_x, int *hit_y, int *hit_dx,
                                           int *hit_dy, int *hit_thres)
{
    const int inner_dx = left_side ? -1 : 1;
    const int ray_dx[3] = {inner_dx, inner_dx, inner_dx};
    const int ray_dy[3] = {0, -1, -2};
    const int max_steps = 45;

    *hit_x = -1;
    *hit_y = -1;
    *hit_dx = 0;
    *hit_dy = 0;
    *hit_thres = 0;

    for(int ray = 0; ray < 3 && *hit_y < 0; ray++)
    {
        for(int step = 1; step <= max_steps; step++)
        {
            const int x = seed_x + ray_dx[ray] * step;
            const int y = seed_y + ray_dy[ray] * step;
            int local_thres = 0;

            if(x < block_size / 2 || x >= MT9V03X_W - block_size / 2 ||
               y < block_size / 2 + 1 || y >= MT9V03X_H - block_size / 2)
            {
                break;
            }

            for(int dy = -block_size / 2; dy <= block_size / 2; dy++)
            {
                for(int dx = -block_size / 2; dx <= block_size / 2; dx++)
                {
                    local_thres += AT_IMAGE(&img_raw, x + dx, y + dy);
                }
            }
            local_thres /= block_size * block_size;
            local_thres -= clip_value;

            if(AT_IMAGE(&img_raw, x, y) < local_thres)
            {
                *hit_x = x;
                *hit_y = y;
                *hit_dx = ray_dx[ray];
                *hit_dy = ray_dy[ray];
                *hit_thres = local_thres;
                break;
            }
        }
    }

    return *hit_y >= 0;
}

static int circle_entry_find_inner_hit_on_seed_line(int left_side)
{
    const int lpt_id = left_side ? Lpt0_rpts0s_id : Lpt1_rpts1s_id;
    const int found_lpt = left_side ? (Lpt0_found ? 1 : 0) : (Lpt1_found ? 1 : 0);
    float seed_raw_x = 0.0f;
    float seed_raw_y = 0.0f;
    int seed_x = -1;
    int seed_y = -1;
    int hit_x = -1;
    int hit_y = -1;
    int hit_dx = 0;
    int hit_dy = 0;
    int hit_thres = 0;

    if(!circle_entry_inner_seed(left_side, &seed_x, &seed_y, &seed_raw_x, &seed_raw_y))
    {
        if(circle_cal_log_enabled())
        {
            printf("ATGCircleEntryInnerHit: side=%c near=%d@%d seed=-1,-1 hit=0@-1,-1 ray=0,0 sharp=0\n",
                   left_side ? 'L' : 'R', found_lpt, -1);
        }
        return 0;
    }

    circle_entry_find_inner_hit_ray(left_side, seed_x, seed_y, &hit_x, &hit_y,
                                    &hit_dx, &hit_dy, &hit_thres);

    if(circle_cal_log_enabled())
    {
        printf("ATGCircleEntryInnerHit: side=%c near=%d@%d seed=%d,%d hit=%d@%d,%d ray=%d,%d sharp=0 raw=%.1f,%.1f th=%d\n",
               left_side ? 'L' : 'R',
               found_lpt,
               found_lpt ? lpt_id : -1,
               seed_x,
               seed_y,
               hit_y >= 0 ? 1 : 0,
               hit_x,
               hit_y,
               hit_dx,
               hit_dy,
               seed_raw_x,
               seed_raw_y,
               hit_thres);
    }

    return hit_y >= 0;
}

// 线方差判据:圆环入口前同侧边线从直道变成圆弧,角度方差应显著增大。
// 普通弯道/假开口的边线弯度变化平缓,方差低。
static int circle_entry_check_angle_variance(int left_side, int a_id, float *out_var)
{
    extern float rpts0a[MT9V03X_HH], rpts1a[MT9V03X_HH];
    extern int rpts0a_num, rpts1a_num;
    const float *ang = left_side ? rpts0a : rpts1a;
    const int a_num = left_side ? rpts0a_num : rpts1a_num;

    const int w = CIRCLE_ENTRY_ANGLE_VAR_WINDOW;
    const int start = clip(a_id - w, 0, a_num - 1);
    const int end = clip(a_id + w, 0, a_num - 1);
    const int n = end - start + 1;
    if(n < 5) { *out_var = 0; return 0; }

    float sum = 0;
    for(int i = start; i <= end; i++) sum += ang[i];
    const float mean = sum / (float)n;

    float var = 0;
    for(int i = start; i <= end; i++) { float d = ang[i] - mean; var += d * d; }
    var /= (float)n;
    *out_var = var;

    return var >= (float)CIRCLE_ENTRY_MIN_ANGLE_VAR;
}

// 对侧扫 B:从角点 A 的 raw 坐标往上取窗口,先跳过近端线边缘,再扫到对侧弧面黑边界。
// 左环向右取最大 x,右环向左取最小 x。
// 若存在尖锐远角点(far_Lpt)→那是十字,不是圆环;返回区分。
// 返回值:1=找到 B 且是非尖锐(圆环),-1=找到尖锐 B(十字),0=没找到。
static int find_circle_B_vertical(int left_side)
{
    const int a_id = left_side ? Lpt0_rpts0s_id : Lpt1_rpts1s_id;
    const int a_found = left_side ? (Lpt0_found ? 1 : 0) : (Lpt1_found ? 1 : 0);
    circle_B_point.found = 0;
    circle_B_point.id = -1;
    circle_B_point.raw_x = -1;
    circle_B_point.raw_y = -1;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_num = 0;
    circle_B_search_a_found = a_found;
    circle_B_search_a_id = a_id;
    circle_B_search_start = -1;
    circle_B_search_end = -1;
    circle_B_search_detail = "start";
    circle_B_search_scan_x = -1;
    circle_B_search_scan_end_x = -1;
    circle_B_search_best_x = -1;
    circle_B_search_best_y = -1;
    circle_B_search_rise_hits = 0;
    circle_B_search_dx = 0;
    circle_B_search_inner_dx = 0;
    circle_B_search_dy = 0;
    circle_B_search_up_dy = 0;
    circle_B_search_dist2 = 0;
    circle_B_search_jump_bad = 0;
    circle_B_search_sharp_far = 0;
    if(!a_found || a_id < 0)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_A;
        circle_B_search_detail = "no_a";
        return 0;
    }
    if(a_id >= CIRCLE_ENTRY_A_ID_MAX)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_A;
        circle_B_search_detail = "a_too_far";
        return 0;
    }

    int seed_raw_x = 0, seed_raw_y = 0;
    if(!circle_get_raw_point(left_side, a_id, &seed_raw_x, &seed_raw_y))
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_A;
        circle_B_search_detail = "raw_a_failed";
        return 0;
    }

    int best_x = left_side ? -1 : 9999, best_y = -1;
    int valid_hits = 0;
    int rise_hits = 0;
    int jump_bad = 0;
    int last_candidate_x = -1;
    // 从 A 的 raw 坐标向上逐行扫描,先跳过近端线边缘假目标,找对侧弧面黑边界。
    // 左环向右扫,右环向左扫。
    const int y_min = clip(seed_raw_y - CIRCLE_B_UP_MAX, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    const int y_max = clip(seed_raw_y - CIRCLE_B_UP_MIN, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
    const int scan_start_x = clip(left_side ? (seed_raw_x + CIRCLE_ENTRY_B_SKIP_EDGE_X) :
                                               (seed_raw_x - CIRCLE_ENTRY_B_SKIP_EDGE_X),
                                  block_size / 2,
                                  MT9V03X_W - block_size / 2 - 1);
    const int scan_end_x = clip(left_side ? (seed_raw_x + CIRCLE_ENTRY_B_SCAN_SPAN_X) :
                                             (seed_raw_x - CIRCLE_ENTRY_B_SCAN_SPAN_X),
                                block_size / 2,
                                MT9V03X_W - block_size / 2 - 1);
    circle_B_search_scan_x = scan_start_x;
    circle_B_search_scan_end_x = scan_end_x;
    circle_B_search_start = y_max;
    circle_B_search_end = -1;

    for(int y = y_max; y >= y_min; y--)
    {
        int hit = 0;
        for(int x = scan_start_x; left_side ? (x <= scan_end_x) : (x >= scan_end_x);
            left_side ? x++ : x--)
        {
            if(x < block_size / 2 || x >= MT9V03X_W - block_size / 2) continue;
            int lt = 0;
            for(int dy2 = -block_size / 2; dy2 <= block_size / 2; dy2++)
                for(int dx2 = -block_size / 2; dx2 <= block_size / 2; dx2++)
                    lt += AT_IMAGE(&img_raw, x + dx2, y + dy2);
            lt = lt / (block_size * block_size) - clip_value;
            if(AT_IMAGE(&img_raw, x, y) < lt)
            {
                const int inner_dx = left_side ? (x - seed_raw_x) : (seed_raw_x - x);
                if(inner_dx <= 0) continue;

                valid_hits++;
                circle_B_search_num = valid_hits;
                circle_B_search_end = y;
                if(last_candidate_x >= 0 && abs(x - last_candidate_x) > CIRCLE_ENTRY_B_MAX_STEP_X)
                    jump_bad = 1;
                if(inner_dx >= CIRCLE_ENTRY_AB_X_MIN)
                    rise_hits++;
                last_candidate_x = x;

                if(left_side ? (x > best_x) : (x < best_x))
                {
                    best_x = x;
                    best_y = y;
                }
                hit = 1;
                break;
            }
        }
        if(!hit) continue;
    }
    circle_B_search_best_x = best_x;
    circle_B_search_best_y = best_y;
    circle_B_search_rise_hits = rise_hits;
    circle_B_search_jump_bad = jump_bad;

    if(best_y < 0)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_B;
        circle_B_search_detail = "no_best_y";
        // printf("ATGCircleBDiag: side=%c seed=%d,%d y=%d..%d hits=%d best_y=-1 reason=no_best_y\n",
        //        left_side ? 'L' : 'R', seed_raw_x, seed_raw_y, y_min, y_max, valid_hits);
        return 0;
    }
    if(valid_hits < CIRCLE_ENTRY_B_MIN_HITS || rise_hits < CIRCLE_ENTRY_B_MIN_RISE_HITS)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_B;
        circle_B_search_detail = "not_enough_hits";
        // printf("ATGCircleBDiag: side=%c seed=%d,%d best=%d,%d hits=%d/%d reason=not_enough_hits\n",
        //        left_side ? 'L' : 'R', seed_raw_x, seed_raw_y, best_x, best_y,
        //        valid_hits, rise_hits);
        return 0;
    }
    // AB 约束:A 不能太远,B 必须离 A 够远(纵向分离+空间距离),否则不是真双断点。
    // y 坐标减小 = 往上，所以 dy_ab = seed_raw_y - best_y
    const int dy_ab = seed_raw_y - best_y;
    const int dx_ab = best_x - seed_raw_x;
    const int inner_dx_ab = left_side ? dx_ab : -dx_ab;
    const int dist2_ab = dx_ab * dx_ab + dy_ab * dy_ab;
    const int up_dy = seed_raw_y - best_y;
    circle_B_search_dx = dx_ab;
    circle_B_search_inner_dx = inner_dx_ab;
    circle_B_search_dy = dy_ab;
    circle_B_search_up_dy = up_dy;
    circle_B_search_dist2 = dist2_ab;

    // printf("ATGCircleBDiag: side=%c seed=%d,%d best=%d,%d dy=%d dx=%d inner_dx=%d dist2=%d up_dy=%d hits=%d/%d reason=",
    //        left_side ? 'L' : 'R', seed_raw_x, seed_raw_y, best_x, best_y,
    //        dy_ab, dx_ab, inner_dx_ab, dist2_ab, up_dy, valid_hits, rise_hits);

    if(jump_bad)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
        circle_B_search_detail = "jump_bad";
        return 0;
    }
    if(dy_ab < CIRCLE_ENTRY_AB_Y_MIN)
    {
        // printf("dy_too_small\n");
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
        circle_B_search_detail = "dy_too_small";
        return 0;
    }
    if(inner_dx_ab < CIRCLE_ENTRY_AB_X_MIN)
    {
        // printf("inner_dx_too_small\n");
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
        circle_B_search_detail = "inner_dx_too_small";
        return 0;
    }
    if(dist2_ab < CIRCLE_ENTRY_AB_DIST_MIN * CIRCLE_ENTRY_AB_DIST_MIN)
    {
        // printf("dist2_too_small\n");
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
        circle_B_search_detail = "dist2_too_small";
        return 0;
    }

    // B 高度窗口:A_raw_y - B_raw_y ∈ [UP_MIN, UP_MAX]。
    // B 太近 A 只是近端边线,太远可能是噪声;窗口确保 B 是上方弧顶。
    if(up_dy < CIRCLE_B_UP_MIN || up_dy > CIRCLE_B_UP_MAX)
    {
        // printf("up_dy_out_of_range\n");
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
        circle_B_search_detail = "up_dy_out_of_range";
        return 0;
    }
    // printf("ok\n");

    // 尖锐判别:从 raw 序列判断(圆环=平滑弧顶,十字=跳变/少点)。
    // far_Lpt 只在和当前 B raw 坐标接近时辅助 veto,避免吃其他元素或上一帧远角点。
    int sharp_far_lpt = 0;
    if(left_side && far_Lpt0_found)
    {
        const int far_x = (int)inv_far_Lpt0_found[0];
        const int far_y = (int)inv_far_Lpt0_found[1];
        const int far_dx = far_x - best_x;
        const int far_dy = far_y - best_y;
        sharp_far_lpt =
            (far_dx * far_dx + far_dy * far_dy <
             CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST * CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST) ? 1 : 0;
    }
    else if(!left_side && far_Lpt1_found)
    {
        const int far_x = (int)inv_far_Lpt1_found[0];
        const int far_y = (int)inv_far_Lpt1_found[1];
        const int far_dx = far_x - best_x;
        const int far_dy = far_y - best_y;
        sharp_far_lpt =
            (far_dx * far_dx + far_dy * far_dy <
             CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST * CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST) ? 1 : 0;
    }
    if(sharp_far_lpt)
    {
        circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
        circle_B_search_detail = "sharp_far";
        circle_B_search_sharp_far = sharp_far_lpt;
        return -1;
    }

    circle_B_point.found = 1;
    circle_B_point.id = a_id;
    circle_B_point.raw_x = best_x;
    circle_B_point.raw_y = best_y;
    circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_B_search_detail = "ok";
    circle_B_search_sharp_far = sharp_far_lpt;

    if(circle_cal_log_enabled())
    {
        printf("ATGCircleEntryB: side=%c A@%d B_raw=%d,%d dx=%d inner_dx=%d dy=%d up_dy=%d "
               "dist2=%d hits=%d rise=%d sharp_far=%d\n",
               left_side ? 'L' : 'R', a_id, best_x, best_y, dx_ab, inner_dx_ab, dy_ab,
               dy_ab, dist2_ab, valid_hits, rise_hits, sharp_far_lpt);
    }

    return 1;
}

// 真双断点:左环 A=Lpt0,跳过近端线边缘后扫到对侧弧面 B(非尖锐=圆环);尖锐 B 是十字,不放行。
static int circle_entry_find_double_breakpoint(int left_side)
{
    // 先满足圆环基本条件:对侧直道+对侧无近 Lpt+内侧黑块
    const int basic = left_side ?
        (!Lpt1_found && is_straight1 && circle_entry_find_inner_hit_on_seed_line(1)) :
        (!Lpt0_found && is_straight0 && circle_entry_find_inner_hit_on_seed_line(0));
    if(!basic) return 0;

    // A 点高度门:raw_y 应在合理范围(底部太近=false,顶部太远=false)
    // 对应 viewer y≈80(车在圆环入口前合适距离)。
    const int a_id = left_side ? Lpt0_rpts0s_id : Lpt1_rpts1s_id;
    int a_rx = 0, a_ry = 0;
    if(!circle_get_raw_point(left_side, a_id, &a_rx, &a_ry) || a_ry > 100)
    {
        return 0;
    }

    const int b_ret = find_circle_B_vertical(left_side);
    if(b_ret <= 0)
    {
        print_circle_entry_probe_diag(left_side, a_id, a_rx, a_ry, b_ret);
        return 0;  // 0=没找到 B, -1=尖锐B(十字)→都不算圆环
    }

    // A=B 确认,圆环入口
    if(circle_cal_log_enabled())
    {
        printf("ATGCircleEntryAB: side=%c A=1@%d(raw=%d,%d) B=1@%d,%d OK\n",
               left_side ? 'L' : 'R', a_id, a_rx, a_ry,
               circle_B_point.raw_x, circle_B_point.raw_y);
    }
    return 1;
}

int circle_entry_candidate_pending(void)
{
    return circle_left_entry_votes > 0 || circle_right_entry_votes > 0;
}

void check_circle() {
    if (circle_type != CIRCLE_NONE) {
        reset_circle_entry_votes();
        return;
    }

    if (circle_entry_suppressed()) {
        return;
    }

    // 入口:先判断是圆环(对侧直道+对侧无近Lpt+内侧黑块+竖线扫到弧顶B非尖锐)。
    // circle_entry_find_double_breakpoint 内部已含 basic 条件检查 + B 搜索 + 尖锐判别。
    const int left_entry = circle_entry_find_double_breakpoint(1);
    const int right_entry = circle_entry_find_double_breakpoint(0);

    // 线方差只打诊断(弧面弯度观测用)
    float left_angle_var = 0, right_angle_var = 0;
    if(Lpt0_found) circle_entry_check_angle_variance(1, Lpt0_rpts0s_id, &left_angle_var);
    if(Lpt1_found) circle_entry_check_angle_variance(0, Lpt1_rpts1s_id, &right_angle_var);

    circle_left_entry_votes = left_entry ? circle_left_entry_votes + 1 : 0;
    circle_right_entry_votes = right_entry ? circle_right_entry_votes + 1 : 0;

    if (circle_left_entry_votes >= CIRCLE_ENTRY_CONFIRM_FRAMES) {
        print_circle_transition(circle_type, CIRCLE_LEFT_BEGIN, "entry_vote");
        circle_type = CIRCLE_LEFT_BEGIN;
        reset_circle_begin_flags();
        reset_circle_geometry_state();
        Count_dis_Flag=0;
        reset_circle_entry_votes();
    }

    if (circle_right_entry_votes >= CIRCLE_ENTRY_CONFIRM_FRAMES) {
        print_circle_transition(circle_type, CIRCLE_RIGHT_BEGIN, "entry_vote");
        circle_type = CIRCLE_RIGHT_BEGIN;
        reset_circle_begin_flags();
        reset_circle_geometry_state();
        Count_dis_Flag=0;
        reset_circle_entry_votes();
    }
}

void run_circle() {
    // ===================== 左环 =====================
    if (circle_type == CIRCLE_LEFT_BEGIN) {
        track_type = TRACK_RIGHT;

        // 入环口内侧(左)线丢失:none_left_line 累计(idle-revoke 用),lost_streak 连续计数(恢复即清零)。
        // 记录丢线起点 begin_dist;mouth_loss 只认起点在合理窗口的丢线,挡早开口一直拖到 600。
        if (rpts0s_num < CIRCLE_BEGIN_LOST_RPTS_MAX && !Lpt0_found) {
            Count_dis_Flag = 1;
            none_left_line++;
            have_left_line = 0;
            if(circle_left_begin_lost_streak == 0) {
                circle_left_loss_start_begin_dist = atg_reference_circle_begin_dist();
            }
            circle_left_begin_lost_streak++;
        }
        else {
            circle_left_begin_lost_streak = 0;
            circle_left_loss_start_begin_dist = -1;
        }

        print_left_begin_diag("state");

        latch_circle_A(1);
        // BEGIN 内持续找 B(非尖锐弧顶) 和 C(上方尖角)
        const int b_ok = find_circle_B_vertical(1) == 1;
        if(b_ok) { circle_B_streak++; }
        else { circle_B_streak = 0; }

        const int c_ok = find_circle_C(1);
        if(c_ok) { circle_C_streak++; }
        else { circle_C_streak = 0; }
        circle_ref_mode = (circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES) ? CIRCLE_REF_IN_C :
                          (circle_B_streak >= CIRCLE_B_CONFIRM_FRAMES) ? CIRCLE_REF_BEGIN_AB : CIRCLE_REF_NONE;

        print_circle_abc_diag('L', "BEGIN", 0);

        // BEGIN 内:C 找到→ref_mode=IN_C 触发 C 补线(停在 BEGIN 拉线)。
        // B_row/mouth_loss 只切 ref_mode,不做状态切换。
        // 唯一进 RUNNING 的路径:陀螺到 ENTER(完成切入)。
        if (circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_LEFT_RUNNING,
                circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES ? "gyro_c" : "gyro");
            circle_type = CIRCLE_LEFT_RUNNING;
            circle_ref_mode = CIRCLE_REF_NONE;
            reset_circle_heading();
            if_lost_right_line = 0;
            reset_circle_begin_flags();
            circle_C_point.found = 0;
            circle_C_streak = 0;
            Count_dis_Flag = 0;
        }
        // B_row/mouth_loss 不直接 RUNNING——只在 BEGIN 内改 ref_mode 启用补线
        else if (circle_B_streak >= CIRCLE_B_CONFIRM_FRAMES &&
                 circle_B_point.found &&
                 circle_B_point.raw_y >= CIRCLE_B_ENTER_ROW) {
            circle_ref_mode = CIRCLE_REF_IN_C;  // B 到了,启用 C 补线模式但不离开 BEGIN
        }
        else {
        const int mouth_lost_too_late =
            circle_left_begin_lost_streak >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
            circle_left_loss_start_begin_dist >= CIRCLE_BEGIN_MOUTH_MIN_DIST &&
            circle_left_loss_start_begin_dist > CIRCLE_BEGIN_LOSS_MAX_DIST;

        if (mouth_lost_too_late) {
            abort_circle_begin("LEFT_BEGIN mouth_loss too late");
        }
        }
    }
    else if (circle_type == CIRCLE_LEFT_RUNNING) {
        track_type = TRACK_RIGHT;
        Count_dis_Flag = 1;

        // 阶段2(视觉为主+陀螺门限): 对侧出口角点出现且陀螺已过门限;视觉失效时只留陀螺主触发。
        if (Lpt1_found && Lpt1_rpts1s_id < CIRCLE_OUT_LPT_NEAR_ID &&
            circle_heading_abs_ge(CIRCLE_HEADING_OUT_GATE_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_LEFT_OUT, "vision_lpt");
            circle_type = CIRCLE_LEFT_OUT;
            circle_left_out_straight_streak = 0;
            Count_dis_Flag = 0;
            if_lost_right_line = 0;
        }
        else if (circle_heading_abs_ge(CIRCLE_HEADING_START_OUT_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_LEFT_OUT, "gyro");
            circle_type = CIRCLE_LEFT_OUT;
            circle_left_out_straight_streak = 0;
            Count_dis_Flag = 0;
            if_lost_right_line = 0;
        }
    }
    else if (circle_type == CIRCLE_LEFT_OUT) {
        track_type = TRACK_LEFT;
        Count_dis_Flag = 1;

        // OUT→NONE:陀螺到+对侧直线连续2帧→交棒;或陀螺超大兜底
        if(is_straight1) circle_left_out_straight_streak++;
        else circle_left_out_straight_streak = 0;
        if ((circle_heading_abs_ge(CIRCLE_HEADING_READY_OUT_TO_END_DEG10) &&
             circle_left_out_straight_streak >= 2) ||
            circle_heading_abs_ge(CIRCLE_HEADING_FINISH_SOFT_DEG10)) {
            finish_circle_exit("straight_exit");
        }
    }

    // ===================== 右环 =====================
    else if (circle_type == CIRCLE_RIGHT_BEGIN) {
        track_type = TRACK_LEFT;

        // 内侧(右)线丢失:记录丢线起点 begin_dist;mouth_loss 只认起点在合理窗口的丢线。
        if (rpts1s_num < CIRCLE_BEGIN_LOST_RPTS_MAX && !Lpt1_found) {
            Count_dis_Flag = 1;
            none_right_line++;
            have_right_line = 0;
            if(circle_right_begin_lost_streak == 0) {
                circle_right_loss_start_begin_dist = atg_reference_circle_begin_dist();
            }
            circle_right_begin_lost_streak++;
        }
        else {
            circle_right_begin_lost_streak = 0;
            circle_right_loss_start_begin_dist = -1;
        }

        print_right_begin_diag("state");

        // BEGIN 内持续找 B(非尖锐弧顶) 和 C(上方尖角)——对称左环
        const int b_ok_r = find_circle_B_vertical(0) == 1;
        if(b_ok_r) { circle_B_streak++; }
        else { circle_B_streak = 0; }

        const int c_ok_r = find_circle_C(0);
        if(c_ok_r) { circle_C_streak++; }
        else { circle_C_streak = 0; }
        circle_ref_mode = (circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES) ? CIRCLE_REF_IN_C :
                          (circle_B_streak >= CIRCLE_B_CONFIRM_FRAMES) ? CIRCLE_REF_BEGIN_AB : CIRCLE_REF_NONE;

        // BEGIN→RUNNING:陀螺到→RUNNING(C 找到时 ref_mode=IN_C,BEGIN 内已拉线)
        if (circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_RUNNING,
                circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES ? "gyro_c" : "gyro");
            circle_type = CIRCLE_RIGHT_RUNNING;
            circle_ref_mode = CIRCLE_REF_NONE;
            reset_circle_heading();
            if_lost_left_line = 0;
            reset_circle_begin_flags();
            circle_C_point.found = 0;
            circle_C_streak = 0;
            Count_dis_Flag = 0;
        }
        // B_row/mouth_loss 不直接 RUNNING——只在 BEGIN 内改 ref_mode 启用补线
        else if (circle_B_streak >= CIRCLE_B_CONFIRM_FRAMES &&
                 circle_B_point.found &&
                 circle_B_point.raw_y >= CIRCLE_B_ENTER_ROW) {
            circle_ref_mode = CIRCLE_REF_IN_C;
        }
        else {
        const int mouth_lost_too_late_r =
            circle_right_begin_lost_streak >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
            circle_right_loss_start_begin_dist >= CIRCLE_BEGIN_MOUTH_MIN_DIST &&
            circle_right_loss_start_begin_dist > CIRCLE_BEGIN_LOSS_MAX_DIST;

        if (mouth_lost_too_late_r) {
            abort_circle_begin("RIGHT_BEGIN mouth_loss too late");
        }
        }
    }
    else if (circle_type == CIRCLE_RIGHT_RUNNING) {
        track_type = TRACK_LEFT;
        Count_dis_Flag = 1;

        // 阶段2(视觉为主+陀螺门限): 对称右环, 对侧(左)Lpt0 出环触发 + 陀螺门限。
        if (Lpt0_found && Lpt0_rpts0s_id < CIRCLE_OUT_LPT_NEAR_ID &&
            circle_heading_abs_ge(CIRCLE_HEADING_OUT_GATE_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_OUT, "vision_lpt");
            circle_type = CIRCLE_RIGHT_OUT;
            circle_right_out_straight_streak = 0;
            Count_dis_Flag = 0;
            if_lost_left_line = 0;
        }
        else if (circle_heading_abs_ge(CIRCLE_HEADING_START_OUT_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_OUT, "gyro");
            circle_type = CIRCLE_RIGHT_OUT;
            circle_right_out_straight_streak = 0;
            Count_dis_Flag = 0;
            if_lost_left_line = 0;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_OUT) {
        track_type = TRACK_RIGHT;
        Count_dis_Flag = 1;

        // OUT→NONE:陀螺到+对侧直线连续2帧→交棒;或陀螺超大兜底
        if(is_straight0) circle_right_out_straight_streak++;
        else circle_right_out_straight_streak = 0;
        if ((circle_heading_abs_ge(CIRCLE_HEADING_READY_OUT_TO_END_DEG10) &&
             circle_right_out_straight_streak >= 2) ||
            circle_heading_abs_ge(CIRCLE_HEADING_FINISH_SOFT_DEG10)) {
            finish_circle_exit("straight_exit");
        }
    }
}
