#pragma once

#include <cstdint>

#include "tuning.hpp"

struct point_t
{
    // 坐标统一按当前运行时图像解释：x 向右，y 向下。
    int x;
    int y;
};

struct seed_pair_t
{
    // 原图 seed。state 里 bit0 表示 left 有效，bit1 表示 right 有效。
    point_t left;
    point_t right;
    int row;
};

struct trace_t
{
    // left_side=1 表示左手追线；0 表示右手追线。pts[] 保留 raw trace 点。
    int left_side;
    point_t seed;
    int step;
    point_t stop_point;
    point_t pts[POINT_MAX];
};

struct boundary_t
{
    // original_pts 是 raw 原图边界，assistant 黄/绿线也使用这组点；不参与控制中线归一化。
    int original_step;
    point_t original_pts[POINT_MAX];

    // now_pts 是元素识别用的整数边界：有 IPM 时为 IPM，无矩阵时为 raw pass-through。
    int now_step;
    point_t now_pts[POINT_MAX];

    // work_pts 是角点/中线前的浮点工作点列，通常来自透视、平滑和重采样。
    int work_step;
    double work_pts[POINT_MAX][2];

    // 单侧 L 角结果。*_now_index 对应 now_pts，*_original_index 对应 original_pts。
    // l_found 只表示 boundary 几何扫描见到单侧 L 候选，用于诊断/直线判定。
    // l_ok 表示该单侧 L 候选落在可消费前段，可供 ring、zebra 扫描选线和环岛裁剪使用。
    // l_found/l_ok 都不是 cross 入口信号。
    int l_found;
    int l_ok;
    int l_now_index;
    int l_original_index;
    double l_angle_deg;

    // 双 L 复核信息。l_pair_ok 只表示左右 L 组成参考版 strict double-L 入口；
    // cross 只消费 l_pair_ok；它不覆盖单侧 l_ok，也不直接参与控制中线生成。
    int l_pair_ok;
    int l_pair_state;
    double l_pair_width0;
    double l_pair_width1;
};

struct midline_t
{
    // 控制中线点列，语义是 IPM/控制坐标；不是 assistant 原图红线。
    point_t pts[POINT_MAX];

    // dist[i] 是从 pts[0] 到 pts[i] 的累计近似弧长，lookahead_error 按它选预瞄点。
    int dist[POINT_MAX];
    int step;
};

enum
{
    CROSS_STATE_NONE = 0,
    CROSS_STATE_BEGIN = 1,
    CROSS_STATE_IN = 2,
};

struct cross_state_t
{
    // state: NONE 未进十字，BEGIN 截近线，IN 使用远线过十字。
    int state;
    int not_have_line;

    // 十字内部选择的中线来源：TRACK_TYPE_LEFT 或 TRACK_TYPE_RIGHT。
    int track_type;

    // 远线构建结果。left/right_pts 是 IPM/控制工作点列，不是 raw overlay 点。
    int left_far_found;
    int right_far_found;
    int left_l;
    int right_l;
    int left_num;
    int right_num;
    double left_pts[POINT_MAX][2];
    double right_pts[POINT_MAX][2];

    // CROSS_IN 状态机诊断：near_* 是本帧近线门判定，far_ok 是远线是否可用于选边。
    int left_near_step;
    int right_near_step;
    int both_near_lost;
    int both_near_recover;
    int left_far_ok;
    int right_far_ok;
    int exit_ready;

    // 远线构建诊断：seed/trace/ipm/blur/resample/L 点阶段，左右各一份。
    int left_far_fail;
    int right_far_fail;
    point_t left_far_seed;
    point_t right_far_seed;
    int left_far_trace;
    int right_far_trace;
    int left_far_ipm;
    int right_far_ipm;
    int left_far_blur;
    int right_far_blur;
    int left_far_resample;
    int right_far_resample;
};

enum
{
    CROSS_FAR_FAIL_NONE = 0,
    CROSS_FAR_FAIL_NO_SEED = 1,
    CROSS_FAR_FAIL_TRACE = 2,
    CROSS_FAR_FAIL_TRACE_SHORT = 3,
    CROSS_FAR_FAIL_IPM_SHORT = 4,
    CROSS_FAR_FAIL_RESAMPLE_SHORT = 5,
};

enum
{
    RING_KIND_NONE = 0,
    RING_KIND_LEFT = 1,
    RING_KIND_RIGHT = 2,
};

enum
{
    RING_STATE_BEGIN = 0,
    RING_STATE_IN = 1,
    RING_STATE_RUN = 2,
    RING_STATE_OUT = 3,
    RING_STATE_END = 4,
};

struct ring_state_t
{
    // kind 表示左/右环；state 按 BEGIN -> IN -> RUN -> OUT -> END 推进。
    int kind;
    int state;

    // 参考版 ring_times=1/2 的入口确认阶段；pending 期间 kind 仍为 NONE。
    int pending_kind;
    int pending_stage;
    int64_t pending_encoder0;

    // 连续丢线/有线计数，配合编码器累计值推进环岛阶段。
    int lost_count;
    int have_count;
    int64_t encoder0;
};

struct zebra_state_t
{
    // detected 是中线两侧黑白段检测结果；stop_line 是底部黑线多帧确认结果。
    int detected;
    int stop_line;
    int stop_count;
};

struct track_result_t
{
    // reject_reason 只表示 tracking 失败原因，不负责停车或安全输出。
    int reject_reason;
    int track_type;

    // center_x 是已发布控制中线的起点 x；guide_error 是给控制外环使用的预瞄误差。
    int center_x;
    double guide_error;
    boundary_t left;
    boundary_t right;
    midline_t mid;

    // CROSS_IN 远线中线诊断：side 为本帧尝试侧，fail 标记失败阶段；
    // start/tail/cand/out 分别是 L 后起点、剩余远线点、外扩候选点和最终中线点。
    int cross_mid_side;
    int cross_mid_fail;
    int cross_mid_start;
    int cross_mid_tail;
    int cross_mid_cand;
    int cross_mid_out;

    // 主线帧分类诊断：记录本帧动作来源、mode 和控制参考点。
    int action_cross_state0;
    int action_base_ready;
    int mode_cross_far;
    int mode_cross_near;
    int mode_ring_active;
    int mode_work_track_type;
    point_t control_ref;

    // trace 左右身份拒绝位：只记录当前帧证据，不复用上一帧中线。
    int trace_identity_reject;
};

enum
{
    CROSS_MID_FAIL_NONE = 0,
    CROSS_MID_FAIL_NOT_IN = 1,
    CROSS_MID_FAIL_NO_SIDE = 2,
    CROSS_MID_FAIL_NO_FAR = 3,
    CROSS_MID_FAIL_BAD_START = 4,
    CROSS_MID_FAIL_SHORT_TAIL = 5,
    CROSS_MID_FAIL_OFFSET = 6,
    CROSS_MID_FAIL_BUILD = 7,
};

enum
{
    TRACK_TYPE_NONE = 0,
    TRACK_TYPE_LEFT = 1,
    TRACK_TYPE_RIGHT = 2,
    TRACK_TYPE_DUAL = 3,
};

enum
{
    TRACK_REJECT_NONE = 0,
    TRACK_REJECT_NO_SEED = 1,
    TRACK_REJECT_TRACE_FILTERED = 3,
    TRACK_REJECT_NO_MIDLINE = 4,
};

enum
{
    TRACE_IDENTITY_REJECT_NONE = 0,
    TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED = 1,
    TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED = 2,
    TRACE_IDENTITY_REJECT_ROW_CROSS = 4,
};

enum
{
    SEED_IPM_DIAG_OK = 0,
    SEED_IPM_DIAG_NO_MATRIX = 1,
    SEED_IPM_DIAG_NO_PAIR = 2,
    SEED_IPM_DIAG_MAP_FAILED = 3,
    SEED_IPM_DIAG_SPAN_TOO_SMALL = 4,
    SEED_IPM_DIAG_SPAN_TOO_LARGE = 5,
};

struct control_state_t
{
    // 控制输出状态。yaw-rate 单位为 mrad/s，duty 单位按 drive_output 的 PWM 占空比解释。
    int input_valid;
    int stop_request;
    int target_yaw_rate_mrad_s;
    int actual_yaw_rate_mrad_s;
    int left_duty;
    int right_duty;
};

struct control_feedback_t
{
    // 一个控制周期内的编码器增量和 IMU yaw-rate 反馈。
    int left_speed_count;
    int right_speed_count;
    int actual_yaw_rate_mrad_s;
    int actual_yaw_rate_valid;
    int period_ms;
};

struct runtime_t
{
    // 输入图像与几何基准。
    uint8_t gray[RAW_H][RAW_W];
    int gray_valid;
    int64_t encoder_total;
    // control_center_x 是控制参考点查表失败时的 fallback x，不等同于下一帧 seed 搜索中心。
    int control_center_x;
    int seed_state;
    // mid_position 是下一帧 seed 搜索中心 x，和控制中线起点不是同一个概念。
    int mid_position;
    // 搜索中心跟随的路宽基准(像素)：常态双边帧低通标定，单边帧据此外推起搜中心。
    int width_base;
    double matrix[9];
    int has_matrix;

    // 当前帧 seed/trace/元素/巡线/控制共享状态。
    seed_pair_t seeds;
    trace_t left_trace;
    trace_t right_trace;
    cross_state_t cross;
    ring_state_t ring;
    zebra_state_t zebra;
    track_result_t track;
    control_state_t control;
};
