#include "circle.h"
#include "atg_reference_step.h"
#include "motor.h"
#include "headfile.h"
#include "imgproc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
enum
{
    CIRCLE_ENTRY_CONFIRM_FRAMES = 2,
    CIRCLE_B_CONFIRM_FRAMES = 2,
    CIRCLE_C_CONFIRM_FRAMES = 2,

    CIRCLE_HEADING_ENTER_DEG10 = 600,
    CIRCLE_HEADING_OUT_GATE_DEG10 = 1500,
    CIRCLE_HEADING_START_OUT_DEG10 = 2000,
    CIRCLE_HEADING_READY_OUT_TO_END_DEG10 = 2660,
    CIRCLE_HEADING_FINISH_SOFT_DEG10 = 3300,

    CIRCLE_OUT_LPT_NEAR_ID = 55,
    CIRCLE_REENTRY_SUPPRESS_FRAMES = 150,
};

/* ================= 入口 A/B/C 几何：B/C 搜索器内部参数 =================
   正常调车不动，只在 B/C 点定位偏差时才调整。
   circle_find_B() / circle_find_C() 的具体约束，非状态推进门槛。 */
enum
{
    CIRCLE_ENTRY_A_ID_MAX = 35,
    CIRCLE_ENTRY_A_NEAR_ID = 8,
    CIRCLE_B_READY_RAW_Y_MIN = 58,

    CIRCLE_ENTRY_AB_DIST_MIN = 23,
    CIRCLE_ENTRY_AB_Y_MIN = 8,
    CIRCLE_ENTRY_AB_X_MIN = 6,

    CIRCLE_ENTRY_B_MIN_HITS = 1,
    CIRCLE_ENTRY_B_MAX_STEP_X = 18,

    CIRCLE_B_UP_MIN = 15,
    CIRCLE_B_UP_MAX = 50,
    CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST = 20,

    CIRCLE_PREDICT_SEED_RADIUS = 8,
    CIRCLE_PREDICT_TRACE_MIN_POINTS = 6,
    CIRCLE_SEED_LINE_B_OFFSET_X = 8,
    CIRCLE_B_FOLLOW_Y_RADIUS = 8,
    CIRCLE_C_UP_MIN = 6,
    CIRCLE_C_ANGLE_DIST = 3,
    CIRCLE_C_ANGLE_NMS_KERNEL = 7,
    CIRCLE_C_ANGLE_MIN_MRAD = 350,
};

/* ================= BEGIN 异常撤回：保险丝，非主流程 =================
   abort_late_mouth_loss 的触发条件。只在假入口（直道伪 L）卡住时起效。
   不是正常推进路径，不要依赖它调环。 */
enum
{
    CIRCLE_BEGIN_LOST_CONFIRM_FRAMES = 2,
    CIRCLE_BEGIN_LOST_RPTS_MAX = 2,
    CIRCLE_BEGIN_MOUTH_MIN_DIST = 600,
    CIRCLE_BEGIN_LOSS_MAX_DIST = 4000,
};

enum
{
    CIRCLE_POINT_SEARCH_OK = 0,
    CIRCLE_POINT_SEARCH_NO_A,
    CIRCLE_POINT_SEARCH_NO_B,
    CIRCLE_POINT_SEARCH_NO_EXTREME,
    CIRCLE_POINT_SEARCH_NO_V,
    CIRCLE_POINT_SEARCH_PHASE_GATE,
    CIRCLE_POINT_SEARCH_NO_SEED,
    CIRCLE_POINT_SEARCH_NO_TRACE,
    CIRCLE_POINT_SEARCH_NO_SLOPE,
};

static const float CIRCLE_GYRO_DEADZONE_RAD_S = 0.065f;
static const float CIRCLE_RAD_TO_DEG10 = 1800.0f / 3.14159265358979f;

int circle_count;
enum circle_type_e circle_type = CIRCLE_NONE;
enum circle_ref_mode_e circle_ref_mode = CIRCLE_REF_NONE;
circle_anchor_point_t circle_A_point;
circle_anchor_point_t circle_B_point;
circle_anchor_point_t circle_C_point;
int none_left_line = 0, none_right_line = 0;
int have_left_line = 0, have_right_line = 0; // DEPRECATED: not used for state progression

const char *circle_type_name[CIRCLE_NUM] = {
    "CIRCLE_NONE",
    "CIRCLE_LEFT_ENTRY", "CIRCLE_RIGHT_ENTRY",
    "CIRCLE_LEFT_BEGIN", "CIRCLE_RIGHT_BEGIN",
    "CIRCLE_LEFT_RUNNING", "CIRCLE_RIGHT_RUNNING",
    "CIRCLE_LEFT_OUT", "CIRCLE_RIGHT_OUT",
};

static int circle_entry_votes[2];
static circle_anchor_point_t circle_entry_pending_A[2];
static int circle_entry_seen_B[2];
static int circle_entry_suppress_frames;
static float circle_heading_rad;
static int circle_begin_lost_streak[2];
static int64_t circle_loss_start_begin_dist[2] = {-1, -1};
static int circle_out_straight_streak[2];
static int circle_B_streak;
static int circle_C_streak;
static int circle_B_follow_fail_streak[2];
static int circle_seed_line_x[2];
static int circle_seed_line_y[2];
static int circle_seed_line_valid[2];

static int circle_B_search_reason;
static int circle_B_search_num;
static const char *circle_B_search_detail;
static int circle_B_search_best_x;
static int circle_B_search_best_y;
static int circle_B_search_sharp_far;
static int circle_B_search_seed_x;
static int circle_B_search_seed_y;
static int circle_B_search_ready;
static float circle_B_search_slope;

static int circle_C_search_reason;
static int circle_C_search_num;
static const char *circle_C_search_detail;
static int circle_C_search_seed_x;
static int circle_C_search_seed_y;
static int circle_C_search_best_i;
static float circle_C_search_slope;
static float circle_C_search_angle;

static int side_index(int side) { return side ? CIRCLE_SIDE_LEFT : CIRCLE_SIDE_RIGHT; }
static char side_char(int side) { return side ? 'L' : 'R'; }
static int side_is_left(int side) { return side_index(side) == CIRCLE_SIDE_LEFT; }
static int side_lpt_found(int side) { return side_is_left(side) ? (Lpt0_found ? 1 : 0) : (Lpt1_found ? 1 : 0); }
static int side_lpt_id(int side) { return side_is_left(side) ? Lpt0_rpts0s_id : Lpt1_rpts1s_id; }
static int side_rpts_num(int side) { return side_is_left(side) ? rpts0s_num : rpts1s_num; }
static int side_opposite_lpt_found(int side) { return side_is_left(side) ? (Lpt1_found ? 1 : 0) : (Lpt0_found ? 1 : 0); }
static int side_opposite_lpt_id(int side) { return side_is_left(side) ? Lpt1_rpts1s_id : Lpt0_rpts0s_id; }
static int side_opposite_straight(int side) { return side_is_left(side) ? is_straight1 : is_straight0; }
static int side_out_straight(int side) { return side_is_left(side) ? is_straight1 : is_straight0; }
static int side_entry_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_ENTRY : CIRCLE_RIGHT_ENTRY; }
static int side_begin_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_BEGIN : CIRCLE_RIGHT_BEGIN; }
static int side_running_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_RUNNING : CIRCLE_RIGHT_RUNNING; }
static int side_out_state(int side) { return side_is_left(side) ? CIRCLE_LEFT_OUT : CIRCLE_RIGHT_OUT; }
static int side_begin_track(int side) { return side_is_left(side) ? TRACK_RIGHT : TRACK_LEFT; }
static int side_out_track(int side) { return side_is_left(side) ? TRACK_LEFT : TRACK_RIGHT; }

static const char *circle_ref_mode_name(enum circle_ref_mode_e mode)
{
    switch(mode)
    {
    case CIRCLE_REF_NONE: return "none";
    case CIRCLE_REF_BEGIN_AB: return "begin_ab";
    case CIRCLE_REF_IN_C: return "in_c";
    default: return "unknown";
    }
}

static const char *point_search_reason_name(int reason)
{
    switch(reason)
    {
    case CIRCLE_POINT_SEARCH_OK: return "ok";
    case CIRCLE_POINT_SEARCH_NO_A: return "no_a";
    case CIRCLE_POINT_SEARCH_NO_B: return "no_b";
    case CIRCLE_POINT_SEARCH_NO_EXTREME: return "no_extreme";
    case CIRCLE_POINT_SEARCH_NO_V: return "no_v";
    case CIRCLE_POINT_SEARCH_PHASE_GATE: return "phase_gate";
    case CIRCLE_POINT_SEARCH_NO_SEED: return "no_seed";
    case CIRCLE_POINT_SEARCH_NO_TRACE: return "no_trace";
    case CIRCLE_POINT_SEARCH_NO_SLOPE: return "no_slope";
    default: return "unknown";
    }
}
// 
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

static int circle_heading_deg10(void)
{
    return (int)(fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10);
}

static int circle_heading_abs_ge(int tenth_deg)
{
    return fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10 >= (float)tenth_deg;
}

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

static void clear_anchor(circle_anchor_point_t *p)
{
    p->found = 0;
    p->id = -1;
    p->raw_x = -1;
    p->raw_y = -1;
}

static void store_anchor(circle_anchor_point_t *p, int id, const circle_point_t *raw)
{
    p->found = 1;
    p->id = id;
    p->raw_x = raw->x;
    p->raw_y = raw->y;
}

static void clear_seed_line(int side)
{
    circle_seed_line_valid[side] = 0;
    circle_seed_line_x[side] = -1;
    circle_seed_line_y[side] = -1;
}

static void set_seed_line_from_A(int side, const circle_anchor_point_t *A)
{
    if(A == NULL || !A->found) return;
    circle_seed_line_valid[side] = 1;
    circle_seed_line_x[side] = A->raw_x;
    circle_seed_line_y[side] = A->raw_y;
}

static int signed_B_seed_offset(int side)
{
    return side_is_left(side) ? -CIRCLE_SEED_LINE_B_OFFSET_X : CIRCLE_SEED_LINE_B_OFFSET_X;
}

static void set_seed_line_from_B(int side, const circle_anchor_point_t *B)
{
    if(B == NULL || !B->found) return;
    circle_seed_line_valid[side] = 1;
    circle_seed_line_x[side] = B->raw_x + signed_B_seed_offset(side);
    circle_seed_line_y[side] = B->raw_y;
}

void reset_circle_entry_votes(void)
{
    circle_entry_votes[CIRCLE_SIDE_RIGHT] = 0;
    circle_entry_votes[CIRCLE_SIDE_LEFT] = 0;
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_RIGHT]);
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_LEFT]);
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
    if(circle_entry_suppress_frames <= 0) return 0;
    circle_entry_suppress_frames--;
    reset_circle_entry_votes();
    return 1;
}

void reset_circle_begin_flags(void)
{
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    circle_begin_lost_streak[CIRCLE_SIDE_RIGHT] = 0;
    circle_begin_lost_streak[CIRCLE_SIDE_LEFT] = 0;
}

void reset_circle_geometry_state(void)
{
    circle_ref_mode = CIRCLE_REF_NONE;
    clear_anchor(&circle_A_point);
    clear_anchor(&circle_B_point);
    clear_anchor(&circle_C_point);
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_RIGHT]);
    clear_anchor(&circle_entry_pending_A[CIRCLE_SIDE_LEFT]);
    circle_entry_seen_B[CIRCLE_SIDE_RIGHT] = 0;
    circle_entry_seen_B[CIRCLE_SIDE_LEFT] = 0;
    clear_seed_line(CIRCLE_SIDE_RIGHT);
    clear_seed_line(CIRCLE_SIDE_LEFT);
    circle_out_straight_streak[CIRCLE_SIDE_RIGHT] = 0;
    circle_out_straight_streak[CIRCLE_SIDE_LEFT] = 0;
    circle_B_streak = 0;
    circle_C_streak = 0;
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
    if(!valid || period_ms <= 0 || fabsf(yaw_rate_rad_s) <= CIRCLE_GYRO_DEADZONE_RAD_S) return;
    circle_heading_rad += yaw_rate_rad_s * ((float)period_ms / 1000.0f);
}

int circle_heading_enter_ready(void)
{
    return circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10);
}

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

static int circle_get_raw_point(int side, int id, circle_point_t *p)
{
    const int num = side_rpts_num(side);
    float (*pts)[2] = side_is_left(side) ? rpts0s : rpts1s;
    if(p == NULL || id < 0 || id >= num) return 0;
    p->x = (int)Cal_inv_rot_x(pts[id][0], pts[id][1]);
    p->y = (int)Cal_inv_rot_y(pts[id][0], pts[id][1]);
    return 1;
}

static int circle_get_A(int side, circle_point_t *A)
{
    const int id = side_lpt_id(side);
    if(!side_lpt_found(side) || !circle_get_raw_point(side, id, A)) return 0;
    return 1;
}

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

static int mirrored_raw_x(int x)
{
    return MT9V03X_W - 1 - x;
}

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

static int prediction_x_at_y(int side, int y, float slope)
{
    const int x = circle_seed_line_x[side] +
                  (int)lroundf(slope * (float)(y - circle_seed_line_y[side]));
    return clip(x, block_size / 2, MT9V03X_W - block_size / 2 - 1);
}

static int dark_near_prediction(int x_center, int y, int *seed_x)
{
    for(int delta = 0; delta <= CIRCLE_PREDICT_SEED_RADIUS; delta++)
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

static int circle_find_prediction_seed(int side, int y_start, int y_stop,
                                       int *seed_x, int *seed_y, float *slope_out)
{
    float slope = 0.0f;
    if(!circle_seed_line_valid[side]) return 0;
    if(!circle_prediction_slope(side, &slope)) return 0;

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
        const int x_center = prediction_x_at_y(side, y, slope);
        int x = -1;
        if(dark_near_prediction(x_center, y, &x))
        {
            *seed_x = x;
            *seed_y = y;
            if(slope_out != NULL) *slope_out = slope;
            return 1;
        }
    }
    if(slope_out != NULL) *slope_out = slope;
    return 0;
}

static int circle_trace_from_seed(int side, int seed_x, int seed_y, int trace[][2], int *trace_num)
{
    *trace_num = MT9V03X_H;
    if(side_is_left(side))
    {
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, seed_x, seed_y, trace, trace_num);
    }
    else
    {
        findline_righthand_adaptive(&img_raw, block_size, clip_value, seed_x, seed_y, trace, trace_num);
    }
    return *trace_num >= CIRCLE_PREDICT_TRACE_MIN_POINTS;
}

static void raw_trace_to_float(int trace[][2], int trace_num, float out[][2])
{
    for(int i = 0; i < trace_num; i++)
    {
        out[i][0] = (float)trace[i][0];
        out[i][1] = (float)trace[i][1];
    }
}

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

static void log_entry_probe(int side, const circle_point_t *A, int b_ret)
{
    if(!circle_cal_log_enabled()) return;
    printf("ATGCircleEntryProbe: side=%c A=1@%d(raw=%d,%d) B=0 ret=%d reason=%s detail=%s "
           "trace=%d seed=%d,%d seed_line=%d,%d slope=%.3f best=%d,%d ready=%d sharp_far=%d\n",
           side_char(side),
           side_lpt_id(side), A->x, A->y, b_ret,
           point_search_reason_name(circle_B_search_reason),
           circle_B_search_detail ? circle_B_search_detail : "unknown",
           circle_B_search_num, circle_B_search_seed_x, circle_B_search_seed_y,
           circle_seed_line_x[side], circle_seed_line_y[side], circle_B_search_slope,
           circle_B_search_best_x, circle_B_search_best_y, circle_B_search_ready,
           circle_B_search_sharp_far);
}

static int far_lpt_near_B(int side, const circle_point_t *B)
{
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
    const int dx = far_x - B->x;
    const int dy = far_y - B->y;
    return dx * dx + dy * dy <
           CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST * CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST;
}

static int circle_find_B(int side, const circle_point_t *ref, int follow_mode, circle_point_t *B_out)
{
    int trace[MT9V03X_H][2];
    int trace_num = 0;
    int seed_x = -1;
    int seed_y = -1;
    float slope = 0.0f;
    int best_x, best_y;
    int y_min, y_max;

    if(follow_mode == 0)  /* ENTRY mode: full A-B geometry search */
    {
        if(B_out != NULL) memset(B_out, 0, sizeof(*B_out));
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

        if(ref == NULL || !circle_A_point.found)
        {
            circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_A;
            circle_B_search_detail = "no_locked_a";
            return 0;
        }

        y_min = clip(ref->y - CIRCLE_B_UP_MAX, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
        y_max = clip(ref->y - CIRCLE_B_UP_MIN, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
        best_x = side_is_left(side) ? -1 : 9999;
        best_y = -1;
    }
    else  /* follow_mode == 1: BEGIN follow mode, narrow window around current B */
    {
        if(!circle_B_point.found || !circle_seed_line_valid[side]) return 0;
        y_min = clip(ref->y - CIRCLE_B_FOLLOW_Y_RADIUS, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
        y_max = clip(ref->y + CIRCLE_B_FOLLOW_Y_RADIUS, block_size / 2 + 1, MT9V03X_H - block_size / 2 - 1);
        best_x = side_is_left(side) ? -1 : 9999;
        best_y = -1;
    }

    if(!circle_seed_line_valid[side])
    {
        if(follow_mode == 0)
        {
            circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
            circle_B_search_detail = "seed_line_invalid";
        }
        return 0;
    }
    if(!circle_prediction_slope(side, &slope))
    {
        if(follow_mode == 0)
        {
            circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SLOPE;
            circle_B_search_detail = "no_opposite_slope";
        }
        return 0;
    }
    if(!circle_find_prediction_seed(side, y_max, y_min, &seed_x, &seed_y, &slope))
    {
        if(follow_mode == 0)
        {
            circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
            circle_B_search_detail = "no_pred_seed";
            circle_B_search_slope = slope;
        }
        return 0;
    }

    if(follow_mode == 0)
    {
        circle_B_search_seed_x = seed_x;
        circle_B_search_seed_y = seed_y;
        circle_B_search_slope = slope;
    }

    if(!circle_trace_from_seed(side, seed_x, seed_y, trace, &trace_num))
    {
        if(follow_mode == 0)
        {
            circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_TRACE;
            circle_B_search_detail = "short_trace";
            circle_B_search_num = trace_num;
        }
        return 0;
    }

    if(follow_mode == 0)
    {
        circle_B_search_num = trace_num;
    }

    {
        int valid_hits = 0;
        int candidate_hits = 0;
        int last_x = -1;
        int best_i = -1;

        for(int i = 0; i < trace_num; i++)
        {
            const int x = trace[i][0];
            const int y = trace[i][1];

            if(y < y_min || y > y_max) continue;
            candidate_hits++;

            if(follow_mode == 0)
            {
                const int dx = x - ref->x;
                const int dy = ref->y - y;
                const int inner_dx = side_is_left(side) ? dx : -dx;
                const int dist2 = dx * dx + dy * dy;

                if(last_x >= 0 && abs(x - last_x) > CIRCLE_ENTRY_B_MAX_STEP_X)
                {
                    circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
                    circle_B_search_detail = "jump_bad";
                    return -1;
                }
                last_x = x;
                if(dy < CIRCLE_ENTRY_AB_Y_MIN ||
                   inner_dx < CIRCLE_ENTRY_AB_X_MIN ||
                   dist2 < CIRCLE_ENTRY_AB_DIST_MIN * CIRCLE_ENTRY_AB_DIST_MIN ||
                   dy < CIRCLE_B_UP_MIN || dy > CIRCLE_B_UP_MAX)
                {
                    continue;
                }
            }

            valid_hits++;
            if(side_is_left(side) ? x > best_x : x < best_x)
            {
                best_x = x;
                best_y = y;
                best_i = i;
            }
        }

        if(follow_mode == 0)
        {
            circle_B_search_best_x = best_x;
            circle_B_search_best_y = best_y;
            if(best_y < 0 || valid_hits < CIRCLE_ENTRY_B_MIN_HITS)
            {
                circle_B_search_reason = candidate_hits > 0 ? CIRCLE_POINT_SEARCH_NO_EXTREME :
                                                               CIRCLE_POINT_SEARCH_NO_B;
                circle_B_search_detail = candidate_hits > 0 ? "no_legal_extreme" : "no_trace_candidate";
                return 0;
            }

            {
                const int dx = best_x - ref->x;
                const int dy = ref->y - best_y;
                const int inner_dx = side_is_left(side) ? dx : -dx;
                const int dist2 = dx * dx + dy * dy;

                B_out->x = best_x;
                B_out->y = best_y;
                if(far_lpt_near_B(side, B_out))
                {
                    circle_B_search_reason = CIRCLE_POINT_SEARCH_NO_EXTREME;
                    circle_B_search_detail = "sharp_far";
                    circle_B_search_sharp_far = 1;
                    return -1;
                }

                circle_B_point.found = 1;
                circle_B_point.id = circle_A_point.id;
                circle_B_point.raw_x = B_out->x;
                circle_B_point.raw_y = B_out->y;
                circle_B_search_ready = B_out->y >= CIRCLE_B_READY_RAW_Y_MIN;
                circle_B_search_reason = CIRCLE_POINT_SEARCH_OK;
                circle_B_search_detail = "ok";
                if(circle_cal_log_enabled())
                {
                    printf("ATGCircleEntryB: side=%c A@%d seed=%d,%d seed_line=%d,%d slope=%.3f "
                           "B_raw=%d,%d#%d dx=%d inner_dx=%d dy=%d dist2=%d trace=%d cand=%d hits=%d ready=%d sharp_far=%d\n",
                           side_char(side), circle_A_point.id,
                           circle_B_search_seed_x, circle_B_search_seed_y,
                           circle_seed_line_x[side], circle_seed_line_y[side], circle_B_search_slope,
                           B_out->x, B_out->y, best_i, dx, inner_dx, dy, dist2, trace_num, candidate_hits, valid_hits,
                           circle_B_search_ready, circle_B_search_sharp_far);
                }
                return 1;
            }
        }
        else  /* follow_mode == 1: BEGIN follow mode result */
        {
            if(best_y < 0) return 0;

            circle_B_point.raw_x = best_x;
            circle_B_point.raw_y = best_y;
            set_seed_line_from_B(side, &circle_B_point);
            if(circle_cal_log_enabled())
            {
                printf("ATGCircleBeginBFollow: side=%c seed=%d,%d B=%d,%d seed_line=%d,%d slope=%.3f trace=%d\n",
                       side_char(side), seed_x, seed_y,
                       circle_B_point.raw_x, circle_B_point.raw_y,
                       circle_seed_line_x[side], circle_seed_line_y[side], slope, trace_num);
            }
            return 1;
        }
    }
}

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

static int circle_find_C(int side, const circle_point_t *B, circle_point_t *C)
{
    int trace[MT9V03X_H][2];
    float trace_f[MT9V03X_H][2];
    float angles[MT9V03X_H];
    float angles_nms[MT9V03X_H];
    int trace_num = 0;
    int seed_x = -1;
    int seed_y = -1;
    float slope = 0.0f;
    int best_i = -1;
    float best_abs_angle = 0.0f;

    clear_anchor(&circle_C_point);
    circle_C_search_num = 0;
    circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_C_search_detail = "start";
    circle_C_search_seed_x = -1;
    circle_C_search_seed_y = -1;
    circle_C_search_best_i = -1;
    circle_C_search_slope = 0.0f;
    circle_C_search_angle = 0.0f;
    if(!circle_B_point.found)
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_B;
        circle_C_search_detail = "no_locked_b";
        return 0;
    }

    if(!circle_seed_line_valid[side])
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_C_search_detail = "seed_line_invalid";
        return 0;
    }
    if(!circle_prediction_slope(side, &slope))
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_SLOPE;
        circle_C_search_detail = "no_opposite_slope";
        return 0;
    }
    if(!circle_find_prediction_seed(side,
                                    B->y - CIRCLE_C_UP_MIN,
                                    block_size / 2 + 5,
                                    &seed_x, &seed_y, &slope))
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_SEED;
        circle_C_search_detail = "no_pred_seed";
        circle_C_search_slope = slope;
        return 0;
    }
    circle_C_search_seed_x = seed_x;
    circle_C_search_seed_y = seed_y;
    circle_C_search_slope = slope;

    if(!circle_trace_from_seed(side, seed_x, seed_y, trace, &trace_num))
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_TRACE;
        circle_C_search_detail = "short_trace";
        circle_C_search_num = trace_num;
        return 0;
    }
    circle_C_search_num = trace_num;
    raw_trace_to_float(trace, trace_num, trace_f);
    local_angle_points(trace_f, trace_num, angles, CIRCLE_C_ANGLE_DIST);
    nms_angle(angles, trace_num, angles_nms, CIRCLE_C_ANGLE_NMS_KERNEL);

    for(int i = 0; i < trace_num; i++)
    {
        const int y = trace[i][1];
        const float abs_angle = fabsf(angles_nms[i]);
        if(y >= B->y - CIRCLE_C_UP_MIN) continue;
        if((int)(abs_angle * 1000.0f) < CIRCLE_C_ANGLE_MIN_MRAD) continue;
        if(abs_angle > best_abs_angle)
        {
            best_abs_angle = abs_angle;
            best_i = i;
        }
    }

    if(best_i < 0)
    {
        circle_C_search_reason = CIRCLE_POINT_SEARCH_NO_V;
        circle_C_search_detail = "no_corner";
        return 0;
    }

    C->x = trace[best_i][0];
    C->y = trace[best_i][1];
    circle_C_point.found = 1;
    circle_C_point.id = best_i;
    circle_C_point.raw_x = C->x;
    circle_C_point.raw_y = C->y;
    circle_C_search_reason = CIRCLE_POINT_SEARCH_OK;
    circle_C_search_detail = "ok";
    circle_C_search_best_i = best_i;
    circle_C_search_angle = angles_nms[best_i];
    if(circle_cal_log_enabled())
    {
        printf("ATGCircleBeginC: side=%c B=%d,%d seed=%d,%d seed_line=%d,%d slope=%.3f "
               "C=%d,%d#%d angle=%.3f trace=%d\n",
               side_char(side), B->x, B->y,
               circle_C_search_seed_x, circle_C_search_seed_y,
               circle_seed_line_x[side], circle_seed_line_y[side], slope,
               C->x, C->y, best_i, circle_C_search_angle, trace_num);
    }
    return 1;
}

static int circle_C_phase_ready(void)
{
    return circle_B_streak >= CIRCLE_B_CONFIRM_FRAMES &&
           circle_B_point.found &&
           circle_B_point.raw_y >= CIRCLE_B_READY_RAW_Y_MIN;
}

static int circle_update_C(int side, circle_point_t *C)
{
    circle_point_t B = {circle_B_point.raw_x, circle_B_point.raw_y};
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
        return 0;
    }
    return circle_find_C(side, &B, C);
}

static void log_circle_abc(int side, const char *phase, int mouth_ready)
{
    if(!circle_cal_log_enabled() || circle_type == CIRCLE_NONE) return;
    printf("ATGCircleABC: side=%c phase=%s ref=%d(%s) rpts=%d/%d lpt=%d@%d/%d@%d "
           "seed_line=%d@%d,%d B_offset=%d "
           "A=%d@%d,%d#%d B=%d@%d,%d#%d B_streak=%d B_ready=%d B_ready_y=%d "
           "B_search=%s/%s trace=%d seed=%d,%d best=%d,%d slope=%.3f "
           "C=%d@%d,%d#%d C_streak=%d C_ready=%d C_search=%s/%s trace=%d seed=%d,%d best_i=%d angle=%.3f slope=%.3f "
           "mouth_ready=%d heading=%d begin_dist=%lld\n",
           side_char(side), phase, (int)circle_ref_mode, circle_ref_mode_name(circle_ref_mode),
           rpts0s_num, rpts1s_num,
           Lpt0_found ? 1 : 0, Lpt0_found ? Lpt0_rpts0s_id : -1,
           Lpt1_found ? 1 : 0, Lpt1_found ? Lpt1_rpts1s_id : -1,
           circle_seed_line_valid[side], circle_seed_line_x[side], circle_seed_line_y[side],
           signed_B_seed_offset(side),
           circle_A_point.found, circle_A_point.raw_x, circle_A_point.raw_y, circle_A_point.id,
           circle_B_point.found, circle_B_point.raw_x, circle_B_point.raw_y, circle_B_point.id,
           circle_B_streak, circle_B_search_ready, CIRCLE_B_READY_RAW_Y_MIN,
           point_search_reason_name(circle_B_search_reason),
           circle_B_search_detail ? circle_B_search_detail : "unknown",
           circle_B_search_num, circle_B_search_seed_x, circle_B_search_seed_y,
           circle_B_search_best_x, circle_B_search_best_y, circle_B_search_slope,
           circle_C_point.found, circle_C_point.raw_x, circle_C_point.raw_y, circle_C_point.id,
           circle_C_streak, circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES,
           point_search_reason_name(circle_C_search_reason),
           circle_C_search_detail ? circle_C_search_detail : "unknown",
           circle_C_search_num, circle_C_search_seed_x, circle_C_search_seed_y,
           circle_C_search_best_i, circle_C_search_angle, circle_C_search_slope,
           mouth_ready, circle_heading_deg10(), (long long)atg_reference_circle_begin_dist());
}

static int circle_entry_detect(int side, circle_point_t *A)
{
    if(!circle_get_A(side, A)) return 0;
    if(side_lpt_id(side) < 0 || side_lpt_id(side) >= CIRCLE_ENTRY_A_ID_MAX) return 0;
    if(A->y > 100) return 0;
    if(side_opposite_lpt_found(side) || !side_opposite_straight(side)) return 0;
    if(circle_cal_log_enabled()) (void)circle_inner_hit(side, A);
    return 1;
}

static int circle_update_entry_A(int side)
{
    circle_point_t A = {0, 0};
    if(!circle_get_A(side, &A)) return 0;
    if(side_lpt_id(side) < 0 || side_lpt_id(side) >= CIRCLE_ENTRY_A_ID_MAX) return 0;
    store_anchor(&circle_A_point, side_lpt_id(side), &A);
    set_seed_line_from_A(side, &circle_A_point);
    return 1;
}

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
    Count_dis_Flag = 0;
    reset_circle_entry_votes();
}

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
    reset_circle_begin_flags();
    Count_dis_Flag = 0;
}

static void run_circle_entry(int side)
{
    circle_point_t A = {circle_A_point.raw_x, circle_A_point.raw_y};
    circle_point_t B = {0, 0};
    const int a_visible = circle_update_entry_A(side);
    const int a_near = a_visible && side_lpt_id(side) <= CIRCLE_ENTRY_A_NEAR_ID;
    A.x = circle_A_point.raw_x;
    A.y = circle_A_point.raw_y;
    const int b_ret = circle_find_B(side, &A, 0, &B);

    track_type = side_begin_track(side);
    circle_ref_mode = CIRCLE_REF_NONE;
    if(b_ret < 0)
    {
        log_entry_probe(side, &A, b_ret);
        abort_circle_entry(side, side_is_left(side) ? "LEFT_ENTRY false_b" : "RIGHT_ENTRY false_b");
        return;
    }
    if(b_ret == 1 && circle_B_search_ready)
    {
        circle_entry_seen_B[side] = 1;
        circle_B_streak++;
    }
    else if(b_ret == 1)
    {
        circle_entry_seen_B[side] = 0;
        circle_B_streak = 0;
    }
    else
    {
        log_entry_probe(side, &A, b_ret);
        circle_entry_seen_B[side] = 0;
        circle_B_streak = 0;
    }

    log_circle_abc(side, "ENTRY", 0);

    if(circle_B_streak >= CIRCLE_B_CONFIRM_FRAMES &&
       circle_B_point.found &&
       circle_B_search_ready)
    {
        promote_entry_to_begin(side);
        return;
    }

    if(!circle_entry_seen_B[side] && (!a_visible || a_near))
    {
        abort_circle_entry(side, side_is_left(side) ? "LEFT_ENTRY no_b_window" : "RIGHT_ENTRY no_b_window");
    }
}

int circle_entry_candidate_pending(void)
{
    return circle_entry_votes[CIRCLE_SIDE_LEFT] > 0 || circle_entry_votes[CIRCLE_SIDE_RIGHT] > 0;
}

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
        if(circle_entry_votes[side] >= CIRCLE_ENTRY_CONFIRM_FRAMES)
        {
            enter_circle_entry(side);
            return;
        }
    }
}

static void update_begin_loss(int side)
{
    const int lost = side_rpts_num(side) < CIRCLE_BEGIN_LOST_RPTS_MAX && !side_lpt_found(side);
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

// begin
static void run_circle_begin(int side)
{
    circle_point_t C = {0, 0};
    track_type = side_begin_track(side);
    update_begin_loss(side);
    {
        circle_point_t B_ref = {circle_B_point.raw_x, circle_B_point.raw_y};
        if(circle_find_B(side, &B_ref, 1, NULL)) circle_B_follow_fail_streak[side] = 0;
        else
        {
            circle_B_follow_fail_streak[side]++;
            log_B_follow_miss(side);
        }
    }
    if(circle_update_C(side, &C)) circle_C_streak++;
    else circle_C_streak = 0;

    circle_ref_mode = circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES ? CIRCLE_REF_IN_C :
                      circle_B_point.found ? CIRCLE_REF_BEGIN_AB : CIRCLE_REF_NONE;
    log_circle_abc(side, "BEGIN", 0);

    if(circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10))
    {
        log_circle_state(circle_type, (enum circle_type_e)side_running_state(side),
                         circle_C_streak >= CIRCLE_C_CONFIRM_FRAMES ? "gyro_c" : "gyro");
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

    /* not a normal progression condition — abort on late mouth loss (false entry) */
    const int abort_late_mouth_loss =
        circle_begin_lost_streak[side] >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
        circle_loss_start_begin_dist[side] >= CIRCLE_BEGIN_MOUTH_MIN_DIST &&
        circle_loss_start_begin_dist[side] > CIRCLE_BEGIN_LOSS_MAX_DIST;
    if(abort_late_mouth_loss)
    {
        abort_circle_begin(side_is_left(side) ? "LEFT_BEGIN mouth_loss too late" :
                                                "RIGHT_BEGIN mouth_loss too late");
    }
}

// running
static void run_circle_running(int side)
{
    track_type = side_begin_track(side);
    Count_dis_Flag = 1;
    if(side_opposite_lpt_found(side) &&
       side_opposite_lpt_id(side) < CIRCLE_OUT_LPT_NEAR_ID &&
       circle_heading_abs_ge(CIRCLE_HEADING_OUT_GATE_DEG10))
    {
        log_circle_state(circle_type, (enum circle_type_e)side_out_state(side), "vision_lpt");
        circle_type = (enum circle_type_e)side_out_state(side);
        circle_out_straight_streak[side] = 0;
        Count_dis_Flag = 0;
        if(side_is_left(side)) if_lost_right_line = 0;
        else if_lost_left_line = 0;
    }
    else if(circle_heading_abs_ge(CIRCLE_HEADING_START_OUT_DEG10))
    {
        log_circle_state(circle_type, (enum circle_type_e)side_out_state(side), "gyro");
        circle_type = (enum circle_type_e)side_out_state(side);
        circle_out_straight_streak[side] = 0;
        Count_dis_Flag = 0;
        if(side_is_left(side)) if_lost_right_line = 0;
        else if_lost_left_line = 0;
    }
}

// out
static void run_circle_out(int side)
{
    track_type = side_out_track(side);
    Count_dis_Flag = 1;
    if(side_out_straight(side)) circle_out_straight_streak[side]++;
    else circle_out_straight_streak[side] = 0;

    if((circle_heading_abs_ge(CIRCLE_HEADING_READY_OUT_TO_END_DEG10) &&
        circle_out_straight_streak[side] >= 2) ||
       circle_heading_abs_ge(CIRCLE_HEADING_FINISH_SOFT_DEG10))
    {
        finish_circle_exit("straight_exit");
    }
}


// 主流程
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
