/* =====================================================================
 *  ATG 参考线处理主框架
 *
 *  单帧处理流程：
 *
 *    image_handle()     — 基础搜线，产出 rpts0s/rpts1s（左右边线）
 *    find_corners()     — 角点检测，产出 Lpt0/1_found、is_straight0/1
 *    run_atg_elements() — 元素状态机（圆环/十字/坡道/环岛/Y路/车库）
 *    select_work_line() — 选择控制用线（远线/圆环补线/普通线）
 *    normalize_selected_line() — 归一化成 rptsn 给控制
 *    check_road()       — 道路类型检测（直道/弯道）
 *
 *  元素优先级：圆环 > 十字 > 坡道 > 环岛 > Y路 > 车库
 *  同一时刻只有一个元素活跃，其他被抑制。
 *
 *  选线来源（优先级从高到低）：
 *    1. 十字远线（cross_far_line）
 *    2. 圆环补线（circle_spliced_lines）
 *    3. 普通线（rptsc0/rptsc1）
 * ===================================================================== */
#include "atg_reference_step.h"

#include <stdio.h>
#include <string.h>

#include "headfile.h"
#include "shy_Image.h"
#include "round.h"
#include "cross.h"
#include "Half_check.h"
#include "circle.h"
#include "Patching_Line.h"

/* ================= 全局状态与开关 ================= */

extern int64_t g_atg_reference_encoder_total;

static int64_t last_encoder_total;
static float g_vehicle_raw_ref_x = MT9V03X_W / 2.0f;
static const char *g_selected_line_source = "none";
static int g_selected_line_begin_id;

/* 环岛状态停滞出口：本车 line_found=0 即停车，状态机无法继续靠视觉/陀螺推进。
 * 连续 ATG_CIRCLE_STALL_FRAMES 帧"环岛状态活跃但无任何选线"时复位环岛状态，
 * 显式打日志；不伪造线、不复用旧帧，复位后若环岛证据真实存在会重新自然触发。 */
enum
{
    ATG_CIRCLE_STALL_FRAMES = 30,
};
static int g_circle_stall_frames;

/* CIRCLE_*_BEGIN 误入撤销：真环 BEGIN 后短距离内必然出现入环口"丢线"事件
 * (none_left/right_line>0) 才能推进到 IN；直道伪 L 误入时该事件永不发生，
 * 状态会滞留并把 track_type 锁在对侧边线上（本次实测表现为稳定贴左直行）。
 * 进入 BEGIN 后累计行驶超过 ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS（约 1.0m）仍无丢线
 * 事件即判定证据消失，撤回 NONE 并显式打日志。用距离不用帧数，与车速解耦。
 * ENCODER_PER_METER=5800，6000 counts 约 1.03m，能在误入 BEGIN 时及时撤销。 */
enum
{
    ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS = 6000,
};
static int64_t g_circle_begin_dist;
static int64_t g_circle_begin_last_dist;

/* ================= 元素使能开关 =================
 * 编译时开关：1=启用，0=禁用。禁用的元素每帧被 keep_disabled_elements_idle() 强制清零。 */

/* 十字（启用） */
#ifndef ATG_ENABLE_CROSS
#define ATG_ENABLE_CROSS 1
#endif

/* 圆环（启用） */
#ifndef ATG_ENABLE_CIRCLE
#define ATG_ENABLE_CIRCLE 1
#endif

/* 坡道（禁用） */
#ifndef ATG_ENABLE_RAMP
#define ATG_ENABLE_RAMP 0
#endif

/* 环岛（废弃） */
#ifndef ATG_ENABLE_ROUND
#define ATG_ENABLE_ROUND 0
#endif

/* Y 路（废弃） */
#ifndef ATG_ENABLE_YROAD
#define ATG_ENABLE_YROAD 0
#endif

/* 倒车入库（废弃） */
#ifndef ATG_ENABLE_GARAGE
#define ATG_ENABLE_GARAGE 0
#endif

/* ================= 固定几何锚点与阈值 =================
 *
 * 圆环补线用的 raw 坐标锚点：
 *   左/右锚点在画面最底部边缘，作为补线起点；
 *   目标点在画面上方固定位置，作为补线终点。
 *   左右 OFFSET 对称（均为 35），保证左右环补线镜像一致。
 *
 * CROSS_HALF_CANDIDATE_LPT_ID_MAX：
 *   近端 L + 远端 L 同时出现是半十字证据。
 *   如果没有任何元素认领这个证据，截断近线防止泄漏到普通选线。
 *   25 表示只看 rpts0s/rpts1s 的前 25 个点内的角点。
 */
enum
{
    RAW_LEFT_ANCHOR_X = 5,                                          /* 补线起点：画面左下角 */
    RAW_RIGHT_ANCHOR_X = MT9V03X_W - 6,                             /* 补线起点：画面右下角 */
    RAW_BOTTOM_ANCHOR_Y = MT9V03X_H - 2,                            /* 补线起点 y：画面最底部 */
    CIRCLE_FIXED_IN_TARGET_RAW_Y = 70,                              /* 补线终点 y：画面上方 */
    CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X_OFFSET = 35,                  /* 左环补线终点相对中线的偏移 */
    CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X_OFFSET = 35,                 /* 右环补线终点相对中线的偏移（与左环对称） */
    CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X = MT9V03X_W / 2 - CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X_OFFSET,
    CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X = MT9V03X_W / 2 + CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X_OFFSET,
    CIRCLE_RUNNING_NATURAL_MIN_POINTS = 20,                         /* 自然线最少点数，不够则用固定补线兜底 */
    CROSS_HALF_CANDIDATE_LPT_ID_MAX = 25,                           /* 半十字角点最大 id，超过则不认为是候选 */
};

/* ================= 本帧准备与状态复位 =================
 *
 * 每帧开始前或复位时，把所有参数恢复到默认值。
 * 这些参数是图像处理的核心参数，圆环/十字等元素会临时修改它们。 */

/* 重置图像处理参数到默认值：搜线起点、二值化参数、IPM 参数、瞄准距离等。
 * 元素处理过程中会临时修改这些参数，每帧开始前需要恢复。 */
static void reset_atg_params(void)
{
    begin_x = BEGIN_X;
    begin_y = BEGIN_Y;
    block_size = 5;
    clip_value = 8;
    line_blur_kernel = 7;
    ROAD_WIDTH = 0.45f;
    pixel_per_meter = 116;
    sample_dist = 0.02f;
    angle_dist = 0.2f;
    aim_distance_far = 0.58f;
    aim_distance = aim_distance_far;
    round_aim_distance = aim_distance_far;
}

/* 钳位点数到 [0, MT9V03X_H]：防止越界访问图像缓冲区 */
static int clipped_count(int n)
{
    return range_limit(n, 0, MT9V03X_H);
}

/* 清空本帧所有搜线输出，每帧开头调用 */
static void clear_frame_outputs(void)
{
    ipts0_num = ipts1_num = 0;
    rpts0_num = rpts1_num = 0;
    rpts0b_num = rpts1b_num = 0;
    rpts0s_num = rpts1s_num = 0;
    rpts0a_num = rpts1a_num = 0;
    rpts0an_num = rpts1an_num = 0;
    rptsc0_num = rptsc1_num = 0;
    rptsn_num = 0;
    rpts = NULL;
    rpts_num = 0;
    clear_cross_farline_outputs();
}

/* 重置所有元素状态机到初始状态 */
static void reset_element_state(void)
{
    cross_type = CROSS_NONE;
    circle_type = CIRCLE_NONE;
    reset_circle_geometry_state();
    reset_circle_entry_votes();
    clear_circle_entry_suppression();
    round_type = ROUND_NONE;
    ramp_type = RAMP_NONE;
    yroad_type = YROAD_NONE;
    road_type = ROAD_NORMAL;
    speed_type = speed_normal;
    garage_type = GARAGE_NONE;
    not_have_line = 0;
    if_lost_left_line = 0;
    if_lost_right_line = 0;
    Lpt0_found_flag = 0;
    Lpt1_found_flag = 0;
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    circle_count = 0;
    Count_dis_Flag = 0;
    total_distence = 0;
    g_circle_begin_dist = 0;
    g_circle_begin_last_dist = 0;
    Ramp_total_distence = 0;
    Clean_Time_count = 0;
    Clean_Time_count_flag = 0;
}

/* 更新所有距离计数器：total_distence、Ramp_total_distence、g_circle_begin_dist。
 *
 * total_distence 是 int16，元素内门限沿用 ATG counts 量级。
 * 饱和而不回绕：误入元素状态长期滞留时 int16 累计会绕成负数，破坏所有距离门限。
 * 所以超过 32767 就钳位，不回绕。
 *
 * g_circle_begin_dist 单独追踪 BEGIN 阶段的行驶距离，
 * 用于 revoke_idle_circle_begin() 的超时判断。 */
static void update_distance_counters(int64_t encoder_total)
{
    int64_t delta = encoder_total - last_encoder_total;
    if(delta < 0)
    {
        delta = -delta;
    }
    if(delta > 32767)
    {
        delta = 32767;
    }

    if(Count_dis_Flag)
    {
        /* 饱和而不回绕：误入元素状态长期滞留时 int16 累计会绕成负数，破坏所有距离门限。 */
        int32 next = (int32)total_distence + (int32)delta;
        if(next > 32767)
        {
            next = 32767;
        }
        total_distence = (int16)next;
    }
    else
    {
        total_distence = 0;
    }

    if(Clean_Time_count_flag)
    {
        Clean_Time_count = (uint16)(Clean_Time_count + 1);
        Ramp_total_distence = (int16)(Ramp_total_distence + (int16)delta);
    }
    else
    {
        Clean_Time_count = 0;
        Ramp_total_distence = 0;
    }

    last_encoder_total = encoder_total;

    if(circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_RIGHT_BEGIN)
    {
        g_circle_begin_dist += delta;
    }
    else
    {
        if(g_circle_begin_dist > 0)
        {
            g_circle_begin_last_dist = g_circle_begin_dist;
        }
        g_circle_begin_dist = 0;
    }
}

int64_t atg_reference_circle_begin_dist(void)
{
    return g_circle_begin_dist;
}

int64_t atg_reference_circle_begin_last_dist(void)
{
    return g_circle_begin_last_dist;
}

/* 根据左右线点数选择跟踪哪条线：线少的一侧说明是内侧（被圆环/十字遮挡），跟对侧。
 * 判断逻辑：
 *   - 一侧点数不到另一侧一半且 < 25 → 跟对侧
 *   - 一侧点数 < 10 且另一侧更多 → 跟对侧
 * 这是粗略判断，圆环/十字等元素会覆盖 track_type。 */
static void choose_track_type_from_near_lines(void)
{
    if(rpts0s_num < rpts1s_num / 2 && rpts0s_num < 25)
    {
        track_type = TRACK_RIGHT;
    }
    else if(rpts1s_num < rpts0s_num / 2 && rpts1s_num < 25)
    {
        track_type = TRACK_LEFT;
    }
    else if(rpts0s_num < 10 && rpts1s_num > rpts0s_num)
    {
        track_type = TRACK_RIGHT;
    }
    else if(rpts1s_num < 10 && rpts0s_num > rpts1s_num)
    {
        track_type = TRACK_LEFT;
    }
}

/* 截断十字半候选近线：防止未被元素认领的十字候选泄漏到普通选线。
 *
 * 当近端 L 角点（Lpt0/Lpt1）和远端 L 角点同时出现，但没有任何元素认领时，
 * 说明可能是十字/半十字的前兆，但还没被正式检测到。
 * 此时截断近线到 L 角点之前，防止弯曲的近线段被当作普通线使用。
 * 仅检查当前帧证据，不依赖历史状态。 */
static void truncate_cross_half_candidate_near_lines(void)
{
    if(cross_type != CROSS_NONE ||
       circle_type != CIRCLE_NONE ||
       round_type != ROUND_NONE ||
       yroad_type != YROAD_NONE ||
       ramp_type != RAMP_NONE ||
       garage_type != GARAGE_NONE)
    {
        return;
    }

    /* 仅检查当前帧证据：check_Half()/check_circle() 已经有机会认领元素。
     * 这里只是防止未认领的十字半候选泄漏到普通选线。 */
    if(Lpt0_found && far_Lpt0_found && Lpt0_rpts0s_id < CROSS_HALF_CANDIDATE_LPT_ID_MAX)
    {
        const int n = range_limit(Lpt0_rpts0s_id - 1, 0, rpts0s_num);
        rpts0s_num = n;
        rptsc0_num = n;
    }
    if(Lpt1_found && far_Lpt1_found && Lpt1_rpts1s_id < CROSS_HALF_CANDIDATE_LPT_ID_MAX)
    {
        const int n = range_limit(Lpt1_rpts1s_id - 1, 0, rpts1s_num);
        rpts1s_num = n;
        rptsc1_num = n;
    }
}

/* 强制禁用的元素保持空闲：编译时关闭的元素（ATG_ENABLE_*=0），
 * 每帧强制清零其状态，防止残留状态干扰其他元素。
 * 这样即使检测函数意外修改了这些状态，也会被立即还原。 */
static void keep_disabled_elements_idle(void)
{
#if !ATG_ENABLE_ROUND
    round_type = ROUND_NONE;
    round_aim_distance = aim_distance_far;
#endif
#if !ATG_ENABLE_RAMP
    ramp_type = RAMP_NONE;
    Ramp_total_distence = 0;
    Clean_Time_count = 0;
    Clean_Time_count_flag = 0;
#endif
#if !ATG_ENABLE_YROAD
    yroad_type = YROAD_NONE;
    begin_y = BEGIN_Y;
#endif
#if !ATG_ENABLE_GARAGE
    garage_type = GARAGE_NONE;
    Count_Garage_num = 0;
#endif
}

/* ================= 元素状态机调度 =================
 *
 * 元素优先级：圆环 > 十字 > 坡道 > 环岛 > Y路 > 车库
 * 同一时刻只有一个元素活跃，其他被抑制。
 *
 * 调度流程：
 *   1. run_active_element()  — 已有活跃元素继续运行
 *   2. check_new_element()   — 没有活跃元素时按优先级检测新元素
 *   3. run_new_element()     — 运行新检测到的元素
 *
 * 圆环优先级最高：一旦圆环活跃，强制清除十字角点标记，防止十字干扰圆环。
 */

/* 运行当前活跃的元素：按优先级尝试，找到一个就返回 */
static int run_active_element(void)
{
#if ATG_ENABLE_CIRCLE
    if(circle_type != CIRCLE_NONE)
    {
        cross_type = CROSS_NONE;  /* 圆环优先：强制清除十字，防止干扰 */
        Lpt0_found_flag = 0;
        Lpt1_found_flag = 0;
        run_circle();
        return 1;
    }
#endif
#if ATG_ENABLE_CROSS
    if(cross_type != CROSS_NONE && !yroad_type && round_type == ROUND_NONE && !garage_type)
    {
        run_cross();
        return 1;
    }
#endif
#if ATG_ENABLE_RAMP
    if(ramp_type != RAMP_NONE && !yroad_type && round_type == ROUND_NONE && !garage_type)
    {
        Run_Ramp();
        return 1;
    }
#endif
#if ATG_ENABLE_YROAD
    if(yroad_type != YROAD_NONE && round_type == ROUND_NONE && !garage_type)
    {
        run_yroad();
        return 1;
    }
#endif

    return 0;
}

/* 检测新元素：按优先级依次检测，发现一个就停止。
 * 圆环最先检测，因为它优先级最高；
 * 环岛比较特殊，允许在圆环 BEGIN 阶段同时检测（环岛可能嵌套在圆环入口附近）。 */
static void check_new_element(void)
{
#if ATG_ENABLE_CIRCLE
    if(!cross_type && !yroad_type && !round_type && !ramp_type && !garage_type)
    {
        check_circle();
        if(circle_type != CIRCLE_NONE)
        {
            return;
        }
    }
#endif
#if ATG_ENABLE_CROSS
    if(!yroad_type && !ramp_type && !circle_type && !cross_type && !round_type && !garage_type)
    {
        check_Half();
        if(cross_type != CROSS_NONE)
        {
            return;
        }
    }
#endif
#if ATG_ENABLE_ROUND
    if(!garage_type && !yroad_type && !ramp_type &&
       (circle_type == CIRCLE_RIGHT_BEGIN || circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_NONE))
    {
        check_round();
    }
#endif
#if ATG_ENABLE_RAMP
    if(!circle_type && !yroad_type && !garage_type && !ramp_type)
    {
        Check_ramp();
    }
#endif
#if ATG_ENABLE_YROAD
    if(!circle_type && !ramp_type && !garage_type)
    {
        check_yroad();
    }
#endif
}

/* 运行新检测到的元素：与 run_active_element 不同的是，
 * 这里环岛和坡道排在十字前面（因为它们是新检测到的，需要优先处理）。
 * 返回 1 表示有元素在运行，0 表示没有。 */
static int run_new_element(void)
{
#if ATG_ENABLE_ROUND
    if(yroad_type == YROAD_NONE && round_type != ROUND_NONE && ramp_type == RAMP_NONE && !garage_type)
    {
        run_round();
        return 1;
    }
#endif
#if ATG_ENABLE_RAMP
    if(ramp_type != RAMP_NONE && !circle_type && !yroad_type && !round_type && !garage_type)
    {
        Run_Ramp();
        return 1;
    }
#endif
#if ATG_ENABLE_CROSS
    if(cross_type != CROSS_NONE && !circle_type && !yroad_type && round_type == ROUND_NONE && !garage_type)
    {
        run_cross();
        return 1;
    }
#endif
#if ATG_ENABLE_CIRCLE
    if(circle_type != CIRCLE_NONE && !cross_type && !yroad_type && round_type == ROUND_NONE && !garage_type)
    {
        run_circle();
        return 1;
    }
#endif
#if ATG_ENABLE_YROAD
    if(!circle_type && !cross_type && yroad_type != YROAD_NONE && round_type == ROUND_NONE && !garage_type)
    {
        run_yroad();
        return 1;
    }
#endif

    return 0;
}

/* 元素调度主入口：
 * 1. 先运行已有活跃元素
 * 2. 没有活跃元素时检测新元素
 * 3. 运行新检测到的元素 */
static void run_atg_elements(void)
{
    keep_disabled_elements_idle();

    if(run_active_element())
    {
        keep_disabled_elements_idle();
        return;
    }

    check_new_element();

    if(run_new_element())
    {
        keep_disabled_elements_idle();
        return;
    }

    keep_disabled_elements_idle();
}

/* ================= 圆环补线构造 =================
 *
 * 圆环各阶段的补线策略（每帧从固定 raw 几何重建，不复用旧帧）：
 *   BEGIN(IN_C)  — 从底部锚点到 C 点连线，偏移半赛宽成中心线
 *   RUNNING      — 自然线足够时用自然线，否则用固定补线兜底
 *   OUT          — 用固定补线（从底部锚点到画面中上方目标点）
 *
 * 补线中心是环岛 BEGIN(IN_C)/OUT/RUNNING 桥接的控制选线来源。
 * 左环用右侧自然线（rpts1s），右环用左侧自然线（rpts0s）——
 * 因为圆环内侧的线被遮挡，外侧自然线更完整。 */

/* 左环 RUNNING 时，右侧自然线是否足够长？
 * 足够长则直接用自然线，否则需要固定补线兜底。 */
static int circle_left_running_natural_right_ready(void)
{
    return rpts1s_num >= CIRCLE_RUNNING_NATURAL_MIN_POINTS &&
           rptsc1_num >= CIRCLE_RUNNING_NATURAL_MIN_POINTS;
}

static int circle_right_running_natural_left_ready(void)
{
    return rpts0s_num >= CIRCLE_RUNNING_NATURAL_MIN_POINTS &&
           rptsc0_num >= CIRCLE_RUNNING_NATURAL_MIN_POINTS;
}

/* 构建左环固定补线：从左下角锚点到右上方目标点，右偏半赛宽成中心线。
 * 用于右环 RUNNING（自然线不足时）和右环 OUT 阶段。 */
static void build_fixed_left_center_for_circle(void)
{
    point_Cal_Line(Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                   Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                   Cal_rot_x(CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X,
                             CIRCLE_FIXED_IN_TARGET_RAW_Y),
                   Cal_rot_y(CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X,
                             CIRCLE_FIXED_IN_TARGET_RAW_Y),
                   leftline,
                   &leftline_num);
    Splicing_leftline_s1s_num = MT9V03X_H;
    resample_points(leftline,
                    leftline_num,
                    Splicing_leftline_s1s,
                    &Splicing_leftline_s1s_num,
                    sample_dist * pixel_per_meter);
    track_leftline(Splicing_leftline_s1s,
                   Splicing_leftline_s1s_num,
                   Splicing_leftline_center,
                   (int)round(2.0),
                   pixel_per_meter * ROAD_WIDTH / 2);
    Splicing_leftline_center_num = Splicing_leftline_s1s_num;
}

/* 构建右环固定补线：从右下角锚点到左上方目标点，左偏半赛宽成中心线。
 * 用于左环 RUNNING（自然线不足时）和左环 OUT 阶段。 */
static void build_fixed_right_center_for_circle(void)
{
    point_Cal_Line_2(Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                     Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                     Cal_rot_x(CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X,
                               CIRCLE_FIXED_IN_TARGET_RAW_Y),
                     Cal_rot_y(CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X,
                               CIRCLE_FIXED_IN_TARGET_RAW_Y),
                     rightline,
                     &rightline_num);
    Splicing_rightline_s0s_num = MT9V03X_H;
    resample_points(rightline,
                    rightline_num,
                    Splicing_rightline_s0s,
                    &Splicing_rightline_s0s_num,
                    sample_dist * pixel_per_meter);
    track_rightline(Splicing_rightline_s0s,
                    Splicing_rightline_s0s_num,
                    Splicing_rightline_center,
                    (int)round(2.0),
                    pixel_per_meter * ROAD_WIDTH / 2);
    Splicing_rightline_center_num = Splicing_rightline_s0s_num;
}

/* 构建左环 IN_C 补线：从左下角锚点到 C 点，右偏半赛宽成中心线。
 * C 点是圆环最深处的拐点，比固定目标点更准确地描述圆环内侧轮廓。
 * 仅在 circle_C_point.found 时有效。 */
static void build_circle_left_in_center_by_c(void)
{
    if(!circle_C_point.found)
    {
        return;
    }
    /* 当前 C 补线是同侧底部 raw anchor -> C，再右偏半赛宽成中心线；
     * 不是 C -> 外侧直道的双边融合线。 */
    point_Cal_Line(Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                   Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                   Cal_rot_x(circle_C_point.raw_x, circle_C_point.raw_y),
                   Cal_rot_y(circle_C_point.raw_x, circle_C_point.raw_y),
                   leftline,
                   &leftline_num);
    if(leftline_num <= 1)
    {
        return;
    }
    Splicing_leftline_s1s_num = MT9V03X_H;
    resample_points(leftline,
                    leftline_num,
                    Splicing_leftline_s1s,
                    &Splicing_leftline_s1s_num,
                    sample_dist * pixel_per_meter);
    if(Splicing_leftline_s1s_num <= 1)
    {
        return;
    }
    track_leftline(Splicing_leftline_s1s,
                   Splicing_leftline_s1s_num,
                   Splicing_leftline_center,
                   (int)round(2.0),
                   pixel_per_meter * ROAD_WIDTH / 2);
    Splicing_leftline_center_num = Splicing_leftline_s1s_num;
    if(circle_cal_log_enabled())
    {
        printf("ATGCircleSpliceDiag: side=L mode=C anchor_raw=%d,%d C_raw=%d,%d edge_num=%d sample_num=%d center_num=%d outer_num=%d half_width=%.1f\n",
               RAW_LEFT_ANCHOR_X,
               RAW_BOTTOM_ANCHOR_Y,
               circle_C_point.raw_x,
               circle_C_point.raw_y,
               leftline_num,
               Splicing_leftline_s1s_num,
               Splicing_leftline_center_num,
               rpts1s_num,
               pixel_per_meter * ROAD_WIDTH / 2);
    }
}

/* 构建右环 IN_C 补线：从右下角锚点到 C 点，左偏半赛宽成中心线。
 * 与左环版本镜像对称。 */
static void build_circle_right_in_center_by_c(void)
{
    if(!circle_C_point.found)
    {
        return;
    }
    /* 当前 C 补线是同侧底部 raw anchor -> C，再左偏半赛宽成中心线；
     * 不是 C -> 外侧直道的双边融合线。 */
    point_Cal_Line_2(Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                     Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                     Cal_rot_x(circle_C_point.raw_x, circle_C_point.raw_y),
                     Cal_rot_y(circle_C_point.raw_x, circle_C_point.raw_y),
                     rightline,
                     &rightline_num);
    if(rightline_num <= 1)
    {
        return;
    }
    Splicing_rightline_s0s_num = MT9V03X_H;
    resample_points(rightline,
                    rightline_num,
                    Splicing_rightline_s0s,
                    &Splicing_rightline_s0s_num,
                    sample_dist * pixel_per_meter);
    if(Splicing_rightline_s0s_num <= 1)
    {
        return;
    }
    track_rightline(Splicing_rightline_s0s,
                    Splicing_rightline_s0s_num,
                    Splicing_rightline_center,
                    (int)round(2.0),
                    pixel_per_meter * ROAD_WIDTH / 2);
    Splicing_rightline_center_num = Splicing_rightline_s0s_num;
    if(circle_cal_log_enabled())
    {
        printf("ATGCircleSpliceDiag: side=R mode=C anchor_raw=%d,%d C_raw=%d,%d edge_num=%d sample_num=%d center_num=%d outer_num=%d half_width=%.1f\n",
               RAW_RIGHT_ANCHOR_X,
               RAW_BOTTOM_ANCHOR_Y,
               circle_C_point.raw_x,
               circle_C_point.raw_y,
               rightline_num,
               Splicing_rightline_s0s_num,
               Splicing_rightline_center_num,
               rpts0s_num,
               pixel_per_meter * ROAD_WIDTH / 2);
    }
}

/* 构建圆环补线：根据圆环状态和参考模式，选择合适的补线策略 */
static void build_circle_spliced_lines(void)
{
    /* 补线中心是环岛 BEGIN(IN_C)/OUT/RUNNING 桥接的控制选线来源。
     * 每帧从固定 raw 几何重建，不复用旧帧中线或旧 guide。 */
    Splicing_leftline_center_num = 0;
    Splicing_rightline_center_num = 0;

    if(circle_type == CIRCLE_RIGHT_BEGIN && circle_ref_mode == CIRCLE_REF_IN_C)
    {
        build_circle_right_in_center_by_c();
    }
    else if(circle_type == CIRCLE_RIGHT_RUNNING &&
            !circle_right_running_natural_left_ready())
    {
        build_fixed_left_center_for_circle();
    }
    else if(circle_type == CIRCLE_RIGHT_OUT)
    {
        build_fixed_left_center_for_circle();
    }
    else if(circle_type == CIRCLE_LEFT_BEGIN && circle_ref_mode == CIRCLE_REF_IN_C)
    {
        build_circle_left_in_center_by_c();
    }
    else if(circle_type == CIRCLE_LEFT_RUNNING &&
            !circle_left_running_natural_right_ready())
    {
        build_fixed_right_center_for_circle();
    }
    else if(circle_type == CIRCLE_LEFT_OUT)
    {
        build_fixed_right_center_for_circle();
    }
}

/* ================= 控制线选择 =================
 *
 * 选线优先级（从高到低）：
 *   1. 十字远线（cross_far_line）— 十字/半十字时使用，从远端 L 角点开始
 *   2. 圆环补线（circle_spliced_lines）— 圆环各阶段使用
 *   3. 普通线（rptsc0/rptsc1）— 正常巡线
 *
 * 选线结果记录在 g_selected_line_source，用于日志和调试。
 */

/* 选择十字远线：从远端 L 角点开始，沿边线偏移半赛宽生成中心线。
 * 仅在 CROSS_IN/CROSS_HALF/GARAGE_FOUND 时生效。
 * 返回 1 表示选线成功，0 表示不适用。 */
static int select_cross_far_line(void)
{
    if(cross_type != CROSS_IN &&
       cross_type != CROSS_HALF &&
       garage_type != GARAGE_FOUND_LEFT &&
       garage_type != GARAGE_FOUND_RIGHT)
    {
        return 0;
    }

    if(track_type == TRACK_LEFT)
    {
        const int start = range_limit(far_Lpt0_rpts0s_id, 0, far_rpts0s_num);
        const int count = clipped_count(far_rpts0s_num - start - 1);
        rpts = rptsc0;
        track_leftline(far_rpts0s + start,
                       count,
                       rpts,
                       (int)round(angle_dist / sample_dist),
                       pixel_per_meter * ROAD_WIDTH / 2);
        rpts_num = clipped_count(far_rpts0s_num - start);
        g_selected_line_source = "far_left";
        return 1;
    }

    const int start = range_limit(far_Lpt1_rpts1s_id, 0, far_rpts1s_num);
    const int count = clipped_count(far_rpts1s_num - start);
    rpts = rptsc1;
    track_rightline(far_rpts1s + start,
                    count,
                    rpts,
                    (int)round(angle_dist / sample_dist),
                    pixel_per_meter * ROAD_WIDTH / 2);
    rpts_num = count;
    g_selected_line_source = "far_right";
    return 1;
}

/* 选择圆环线：根据圆环状态和参考模式，选择合适的补线。
 *   BEGIN + IN_C → 用 C 点补线（更准确的入环参考）
 *   RUNNING       → 用固定补线（自然线不足时）或跳过（自然线足够时由 select_normal_line 处理）
 *   OUT           → 用固定补线（出环过渡）
 *   兜底          → OUT 阶段如果补线都没有，强制用 rptsc1 避免崩塌到空线
 * 返回 1 表示选线成功，0 表示不适用。 */
static int select_circle_line(void)
{
    if(circle_type == CIRCLE_LEFT_BEGIN &&
       circle_ref_mode == CIRCLE_REF_IN_C &&
       Splicing_leftline_center_num > 0)
    {
        rpts = Splicing_leftline_center;
        rpts_num = Splicing_leftline_center_num;
        g_selected_line_source = "circle_in_c_left";
        return 1;
    }
    if(circle_type == CIRCLE_RIGHT_BEGIN &&
       circle_ref_mode == CIRCLE_REF_IN_C &&
       Splicing_rightline_center_num > 0)
    {
        rpts = Splicing_rightline_center;
        rpts_num = Splicing_rightline_center_num;
        g_selected_line_source = "circle_in_c_right";
        return 1;
    }
    if((circle_type == CIRCLE_RIGHT_OUT ||
        circle_type == CIRCLE_RIGHT_RUNNING) &&
       Splicing_leftline_center_num > 0)
    {
        rpts = Splicing_leftline_center;
        rpts_num = Splicing_leftline_center_num;
        g_selected_line_source =
            circle_type == CIRCLE_RIGHT_RUNNING ? "circle_running_fixed_left" :
            "circle_out_fixed_left";
        return 1;
    }
    if((circle_type == CIRCLE_LEFT_OUT ||
        circle_type == CIRCLE_LEFT_RUNNING) &&
       Splicing_rightline_center_num > 0)
    {
        rpts = Splicing_rightline_center;
        rpts_num = Splicing_rightline_center_num;
        g_selected_line_source =
            circle_type == CIRCLE_LEFT_RUNNING ? "circle_running_fixed_right" :
            "circle_out_fixed_right";
        return 1;
    }
    if(circle_type == CIRCLE_LEFT_OUT && rptsc1_num > 0)
    {
        /* OUT 无出环中心线时，track_type=TRACK_LEFT 会选到空 rptsc0。
         * 强制用原始右线 rptsc1，避免立即崩塌到 sel=0/0。 */
        rpts = rptsc1;
        rpts_num = rptsc1_num;
        g_selected_line_source = "out_rptsc1";
        return 1;
    }

    return 0;
}

/* 选择普通线：根据 track_type 选择 rptsc0（左线）或 rptsc1（右线）。
 * track_type 在 choose_track_type_from_near_lines() 中根据点数决定。 */
static void select_normal_line(void)
{
    if(track_type == TRACK_LEFT)
    {
        rpts = rptsc0;
        rpts_num = rptsc0_num;
        g_selected_line_source = "rptsc0";
        return;
    }

    rpts = rptsc1;
    rpts_num = rptsc1_num;
    g_selected_line_source = "rptsc1";
}

/* 记录选线日志：圆环活跃时输出详细的选线来源、A/B/C 点状态、各线点数。
 * 仅在 circle_cal_log_enabled() 时输出，避免正常行驶时刷屏。 */
static void log_selected_line(void)
{
    if(circle_cal_log_enabled() && circle_type != CIRCLE_NONE)
    {
        printf("ATGCircleRefDiag: circle=%d ref=%d src=%s(%d) track=%d rpts=%d norm_pre=%d "
               "spL=%d spR=%d near=%d/%d center=%d/%d far=%d/%d A=%d@%d,%d#%d B=%d@%d,%d#%d C=%d@%d,%d#%d\n",
               (int)circle_type,
               (int)circle_ref_mode,
               atg_reference_selected_line_source(),
               atg_reference_selected_line_source_id(),
               track_type,
               rpts_num,
               rptsn_num,
               Splicing_leftline_center_num,
               Splicing_rightline_center_num,
               rpts0s_num,
               rpts1s_num,
               rptsc0_num,
               rptsc1_num,
               far_rpts0s_num,
               far_rpts1s_num,
               circle_A_point.found,
               circle_A_point.found ? circle_A_point.raw_x : -1,
               circle_A_point.found ? circle_A_point.raw_y : -1,
               circle_A_point.id,
               circle_B_point.found,
               circle_B_point.found ? circle_B_point.raw_x : -1,
               circle_B_point.found ? circle_B_point.raw_y : -1,
               circle_B_point.id,
               circle_C_point.found,
               circle_C_point.found ? circle_C_point.raw_x : -1,
               circle_C_point.found ? circle_C_point.raw_y : -1,
               circle_C_point.id);
    }
}

/* 选择控制用线：按优先级尝试十字远线 → 圆环补线 → 普通线 */
static void select_work_line(void)
{
    g_selected_line_source = "none";

    if(select_cross_far_line())
    {
        log_selected_line();
        return;
    }

    build_circle_spliced_lines();

    if(select_circle_line())
    {
        log_selected_line();
        return;
    }

    select_normal_line();
    log_selected_line();
}

/* ================= 控制线归一化 =================
 *
 * 无论选线来源如何（十字远线/圆环补线/普通线），统一归一化成 rptsn 给控制模块。
 * rptsn 是等间距重采样后的参考线，控制模块只需要 rptsn + aim_idx 就能计算转向。
 *
 * 归一化流程：
 *   1. selected_line_ok()        — 检查选线是否有效
 *   2. update_vehicle_ref_ipm()  — 车辆参考点从原图坐标转 IPM 坐标
 *   3. find_selected_line_begin()— 在选线上找离车辆最近的点作为起点
 *   4. resample_selected_line()  — 从起点开始等间距重采样
 *   5. update_aim_points()       — 根据 aim_distance 计算瞄准点
 *   6. calc_guides()             — 计算 pure_angle（角度偏差）和 Guide（横向偏差）
 */

/* 检查选线是否有效：rpts 非空且点数 > 0 */
static int selected_line_ok(void)
{
    if(rpts == NULL || rpts_num <= 0)
    {
        rptsn_num = 0;
        return 0;
    }

    return 1;
}

/* 车辆参考点 IPM 变换：把原图坐标 (g_vehicle_raw_ref_x, H*0.98) 转成俯视角坐标 (cx, cy)。
 * h_zoom=0.98 避免取到画面最底部的畸变像素。 */
static void update_vehicle_ref_ipm(void)
{
    const float h_zoom = 0.98f;
    atg_reference_raw_ref_to_ipm(g_vehicle_raw_ref_x, MT9V03X_H * h_zoom, &cx, &cy);
}

/* 在选线上找离车辆最近的点作为重采样起点。
 * 遍历 rpts 找欧氏距离最小的点，记录为 g_selected_line_begin_id。
 * 如果起点太靠尾部（剩余点 < 2），认为线太短，放弃。 */
static int find_selected_line_begin(void)
{
    float min_dist = 10000.0f;
    g_selected_line_begin_id = 0;
    for(int i = 0; i < rpts_num; i++)
    {
        float dx = rpts[i][0] - cx;
        float dy = rpts[i][1] - cy;
        float dist = sqrtf(dx * dx + dy * dy);
        if(dist < min_dist)
        {
            min_dist = dist;
            g_selected_line_begin_id = i;
        }
    }

    if(g_selected_line_begin_id < 0 || rpts_num - g_selected_line_begin_id < 2)
    {
        rptsn_num = 0;
        return 0;
    }

    return 1;
}

/* 重采样选线：从最近点开始，按 sample_dist*pixel_per_meter 间距等间距重采样。
 * 重采样后存入 rptsn，控制模块直接用 rptsn 计算转向。
 * 先把起点强制对齐到 (cx, cy)，保证重采样从车辆位置开始。 */
static int resample_selected_line(void)
{
    rpts[g_selected_line_begin_id][0] = cx;
    rpts[g_selected_line_begin_id][1] = cy;
    rptsn_num = MT9V03X_HH;
    resample_points(rpts + g_selected_line_begin_id,
                    rpts_num - g_selected_line_begin_id,
                    rptsn,
                    &rptsn_num,
                    sample_dist * pixel_per_meter);
    if(rptsn_num <= 0)
    {
        return 0;
    }

    return 1;
}

/* 计算瞄准点：根据 aim_distance 找到 rptsn 上的对应点。
 * aim_idx 是主瞄准点（用于纯角度计算），aim_idx_up/aim_idx_up_up 是更远的辅助瞄准点。
 * 同时计算 inv_rptsn（IPM 坐标反投影回原图坐标），供外部模块查询。 */
static void update_aim_points(void)
{
    aim_idx = (int)clip(round(aim_distance / sample_dist), 0, rptsn_num - 1);
    aim_idx_up = (int)clip(round(AIM_DISTANCE_UP / sample_dist), 0, rptsn_num - 1);
    aim_idx_up_up = (int)clip(round(AIM_DISTANCE_UP_UP / sample_dist), 0, rptsn_num - 1);
    inv_aim_idx[0] = Cal_inv_rot_x(rptsn[aim_idx][0], rptsn[aim_idx][1]);
    inv_aim_idx[1] = Cal_inv_rot_y(rptsn[aim_idx][0], rptsn[aim_idx][1]);
    for(int i = 0; i < rptsn_num; i++)
    {
        inv_rptsn[i][0] = Cal_inv_rot_x(rptsn[i][0], rptsn[i][1]);
        inv_rptsn[i][1] = Cal_inv_rot_y(rptsn[i][0], rptsn[i][1]);
    }
}

/* 计算引导线：pure_angle（角度偏差）和 Guide（横向偏差）。
 * pure_angle 基于瞄准点相对车辆的横向偏移 dx 和距离 dn，用反正切算出角度偏差。
 * Guide 是横向偏差，结合了横向偏移和角度偏差，用于控制模块的转向决策。
 * Guide_up/Guide_up_up 是更远距离的辅助引导值，用于前瞻控制。 */
static void calc_guides(void)
{
    float dx = rptsn[aim_idx][0] - cx;
    float dy = cy - rptsn[aim_idx][1] + 0.2f * pixel_per_meter;
    float dn = sqrtf(dx * dx + dy * dy);
    float dx_up = rptsn[aim_idx_up][0] - cx;
    float dy_up = cy - rptsn[aim_idx_up][1] + 0.2f * pixel_per_meter;
    float dn_up = sqrtf(dx_up * dx_up + dy_up * dy_up);
    float dx_up_up = rptsn[aim_idx_up_up][0] - cx;
    float dy_up_up = cy - rptsn[aim_idx_up_up][1] + 0.2f * pixel_per_meter;
    float dn_up_up = sqrtf(dx_up_up * dx_up_up + dy_up_up * dy_up_up);
    if(dn > 0.0f)
    {
        pure_angle = -atanf(pixel_per_meter * 2.0f * 0.2f * dx / dn / dn) / 3.14159265358979f * 180.0f / 2.4f;
    }
    if(dn_up > 0.0f)
    {
        pure_angle_up = -atanf(pixel_per_meter * 2.0f * 0.2f * dx_up / dn_up / dn_up) / 3.14159265358979f * 180.0f / 2.4f;
    }
    if(dn_up_up > 0.0f)
    {
        pure_angle_up_up = -atanf(pixel_per_meter * 2.0f * 0.2f * dx_up_up / dn_up_up / dn_up_up) / 3.14159265358979f * 180.0f / 2.4f;
    }
    Guide = (float)clip(round((rptsn[clip(aim_idx, 0, rptsn_num - 1)][0] - cx)) * fabsf(pure_angle), -60, 60);
    Guide_up = (float)clip(round((rptsn[clip(aim_idx_up, 0, rptsn_num - 1)][0] - cx)) * fabsf(pure_angle_up) / 2.5f, -60, 60);
    Guide_up_up = (float)clip(round((rptsn[clip(aim_idx_up_up, 0, rptsn_num - 1)][0] - cx)) * fabsf(pure_angle_up_up) / 2.5f, -60, 60);
}

/* 归一化选中的线：从选线到 rptsn 的完整流程 */
static int normalize_selected_line(void)
{
    if(!selected_line_ok())
    {
        return 0;
    }

    update_vehicle_ref_ipm();

    if(!find_selected_line_begin())
    {
        return 0;
    }

    if(!resample_selected_line())
    {
        return 0;
    }

    update_aim_points();
    calc_guides();

    return 1;
}

/* ================= 复位与异常收尾 =================
 *
 * 圆环异常恢复机制：
 *   - stall：环岛状态活跃但无任何选线，连续 ATG_CIRCLE_STALL_FRAMES 帧后复位到 NONE。
 *     这种情况通常是车卡住或视觉丢失，状态机无法推进，需要强制复位。
 *   - timeout：BEGIN 阶段行驶距离超过 ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS 但陀螺仪角度
 *     仍未达到进环门槛，说明是误入（直道伪 L 触发），需要撤回 NONE。
 *     用距离不用帧数，与车速解耦。
 */

/* 全局复位：清空所有状态，恢复默认参数。
 * 调用时机：系统启动、出错恢复、或手动复位。 */
void atg_reference_reset(void)
{
    reset_atg_params();
    g_atg_reference_encoder_total = 0;
    last_encoder_total = 0;
    g_circle_stall_frames = 0;
    track_type = TRACK_RIGHT;
    reset_element_state();
    clear_frame_outputs();
}

/* 圆环强制复位到 NONE：与 circle.c 的 OUT->NONE 退出逻辑保持一致。
 * 复位所有圆环相关状态（几何、抑制、距离计数），并打印复位原因供调试。
 * 复位后调用 suppress_circle_reentry_after_exit() 防止立即重新误触发圆环。 */
static void reset_circle_to_none(const char *reason)
{
    printf("ATGCircleReset: %s circle_type=%d -> NONE\n", reason, (int)circle_type);
    circle_type = CIRCLE_NONE;
    suppress_circle_reentry_after_exit();
    road_type = ROAD_NORMAL;
    begin_y = BEGIN_Y;
    Count_dis_Flag = 0;
    aim_distance = aim_distance_far;
    if_lost_left_line = 0;
    if_lost_right_line = 0;
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    reset_circle_geometry_state();
    g_circle_stall_frames = 0;
    g_circle_begin_dist = 0;
    g_circle_begin_last_dist = 0;
}

/* BEGIN 阶段超时撤销：行驶距离超过 6000 counts（约 1.0m）但陀螺仪角度
 * 仍未达到进环门槛，说明是误入（直道伪 L 触发的假圆环），撤回 NONE。
 * 用距离不用帧数，与车速解耦。 */
static void revoke_idle_circle_begin(void)
{
    if(circle_type == CIRCLE_LEFT_BEGIN &&
       g_circle_begin_dist > ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS &&
       !circle_heading_enter_ready())
    {
        reset_circle_to_none("LEFT_BEGIN timeout before heading enter,");
    }
    else if(circle_type == CIRCLE_RIGHT_BEGIN &&
            g_circle_begin_dist > ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS &&
            !circle_heading_enter_ready())
    {
        reset_circle_to_none("RIGHT_BEGIN timeout before heading enter,");
    }
}

/* 圆环停滞检测：圆环活跃但连续 ATG_CIRCLE_STALL_FRAMES 帧无有效选线时强制复位。
 * line_ok 表示本帧是否有有效导引线（rptsn_num > 0）。
 * 有线则重置停滞计数，无线则累加；达到阈值后打印日志并复位到 NONE。 */
static void exit_circle_after_stall(int line_ok)
{
    if(circle_type == CIRCLE_NONE || line_ok)
    {
        g_circle_stall_frames = 0;
        return;
    }

    g_circle_stall_frames++;
    if(g_circle_stall_frames < ATG_CIRCLE_STALL_FRAMES)
    {
        return;
    }

    printf("ATGCircleStall: circle_type=%d stalled %d frames without selected line, reset to NONE\n",
           (int)circle_type,
           g_circle_stall_frames);
    reset_circle_to_none("stall without selected line,");
}

/* ================= 单帧处理主入口 =================
 *
 * 单帧图像处理主入口，完整处理流程：
 *
 *   1. clear_frame_outputs()              — 清空上一帧的所有搜线输出
 *   2. image_handle()                     — 基础搜线，从 raw 图左右 seed 开始，
 *                                          产出 rpts0s/rpts1s（左右边线）
 *   3. find_corners()                     — 角点检测，产出 Lpt0/1_found、is_straight0/1
 *   4. choose_track_type_from_near_lines()— 根据左右线点数选择跟踪哪条线
 *   5. run_atg_elements()                 — 元素状态机（圆环/十字/坡道/环岛/Y路/车库）
 *   6. truncate_cross_half_candidate_...  — 截断未认领的十字半候选近线
 *   7. choose_track_type_from_near_lines()— 元素处理后重新选择跟踪线
 *   8. update_distance_counters()         — 更新所有距离计数器
 *   9. select_work_line()                 — 选择控制用线（远线/圆环补线/普通线）
 *  10. normalize_selected_line()          — 归一化成 rptsn 给控制
 *  11. exit_circle_after_stall()          — 圆环停滞检测
 *  12. check_road()                       — 道路类型检测（直道/弯道）
 *
 * 返回 1 表示本帧有有效导引线（rptsn_num > 0），0 表示丢失。 */
int atg_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total)
{
    if(gray == NULL)
    {
        return 0;
    }

    g_atg_reference_encoder_total = encoder_total;
    img_raw.data = (uint8 *)gray;
    clear_frame_outputs();                    /* 清空上一帧输出 */

    image_handle();                           /* 基础搜线：raw 图 → rpts0s/rpts1s */
    find_corners();                           /* 角点检测：Lpt0/1_found、is_straight0/1 */
    choose_track_type_from_near_lines();      /* 根据点数粗选跟踪线 */
    run_atg_elements();                       /* 元素状态机调度 */
    truncate_cross_half_candidate_near_lines(); /* 截断未认领的十字半候选 */
    choose_track_type_from_near_lines();      /* 元素处理后重新选择跟踪线 */
    update_distance_counters(encoder_total);  /* 更新距离计数器 */
    // revoke_idle_circle_begin();            /* BEGIN 超时撤销（暂时禁用） */
    select_work_line();                       /* 选择控制用线 */

    const int ok = normalize_selected_line(); /* 归一化成 rptsn */
    if(circle_cal_log_enabled() && circle_type != CIRCLE_NONE)
    {
        printf("ATGCircleNormDiag: circle=%d ref=%d src=%s(%d) ok=%d rpts=%d rptsn=%d aim=%d inv_aim=%.1f,%.1f cxcy=%.1f,%.1f Guide=%.1f/%.1f/%.1f pure=%.2f/%.2f/%.2f\n",
               (int)circle_type,
               (int)circle_ref_mode,
               atg_reference_selected_line_source(),
               atg_reference_selected_line_source_id(),
               ok,
               rpts_num,
               rptsn_num,
               aim_idx,
               inv_aim_idx[0],
               inv_aim_idx[1],
               cx,
               cy,
               Guide,
               Guide_up,
               Guide_up_up,
               pure_angle,
               pure_angle_up,
               pure_angle_up_up);
    }
    exit_circle_after_stall(ok);
    if(ok)
    {
        check_road();
    }
    return ok;
}

/* ================= 外部查询与坐标辅助 =================
 *
 * 提供给外部模块的查询接口：
 *   - atg_reference_track_line_found()      — 是否有有效导引线
 *   - atg_reference_selected_line_source()   — 选线来源名称（用于日志）
 *   - atg_reference_selected_line_source_id()— 选线来源数字 id（用于数据记录）
 *   - atg_reference_vehicle_raw_ref_x()      — 车辆参考点 x 坐标
 *   - atg_reference_set_vehicle_raw_ref_x()  — 设置车辆参考点 x 坐标
 *   - atg_reference_raw_ref_to_ipm()         — 原图坐标 → 俯视角坐标（IPM 变换）
 */

int atg_reference_track_line_found(void)
{
    return rptsn_num > 0;
}

const char *atg_reference_selected_line_source(void)
{
    return g_selected_line_source != NULL ? g_selected_line_source : "none";
}

/* 选线来源数字 id：用于数据记录和分析。
 * 1-6 是圆环固定补线，9 是 OUT 兜底，10-11 是普通线，12-13 是十字远线，15-16 是 C 点补线。
 * 未知来源返回 0。 */
int atg_reference_selected_line_source_id(void)
{
    const char *source = atg_reference_selected_line_source();
    if(strcmp(source, "circle_running_fixed_left") == 0) return 1;
    if(strcmp(source, "circle_in_fixed_left") == 0) return 2;
    if(strcmp(source, "circle_out_fixed_left") == 0) return 3;
    if(strcmp(source, "circle_running_fixed_right") == 0) return 4;
    if(strcmp(source, "circle_in_fixed_right") == 0) return 5;
    if(strcmp(source, "circle_out_fixed_right") == 0) return 6;
    if(strcmp(source, "circle_in_c_left") == 0) return 15;
    if(strcmp(source, "circle_in_c_right") == 0) return 16;
    if(strcmp(source, "out_rptsc1") == 0) return 9;
    if(strcmp(source, "rptsc0") == 0) return 10;
    if(strcmp(source, "rptsc1") == 0) return 11;
    if(strcmp(source, "far_left") == 0) return 12;
    if(strcmp(source, "far_right") == 0) return 13;
    return 0;
}

/* 设置车辆参考点 x 坐标（原图坐标），用于控制线归一化。
 * 控制模块可以通过这个接口动态调整车辆在画面中的参考位置。
 * 钳位到 [0, MT9V03X_W-1] 防止越界。 */
void atg_reference_set_vehicle_raw_ref_x(float raw_x)
{
    if(raw_x < 0.0f)
    {
        raw_x = 0.0f;
    }
    if(raw_x > (float)(MT9V03X_W - 1))
    {
        raw_x = (float)(MT9V03X_W - 1);
    }
    g_vehicle_raw_ref_x = raw_x;
}

float atg_reference_vehicle_raw_ref_x(void)
{
    return g_vehicle_raw_ref_x;
}

/* 原图坐标 → 俯视角坐标（IPM 逆透视变换）。
 * 用 rot 矩阵把原图像素坐标 (raw_x, raw_y) 映射到俯视角坐标 (ipm_x, ipm_y)。
 * den=0 表示投影退化（点在无穷远），返回 (0,0)。 */
void atg_reference_raw_ref_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y)
{
    const float den = rot[2][0] * raw_y + rot[2][1] * raw_x + rot[2][2];
    if(den == 0.0f)
    {
        if(ipm_x != NULL)
        {
            *ipm_x = 0.0f;
        }
        if(ipm_y != NULL)
        {
            *ipm_y = 0.0f;
        }
        return;
    }
    if(ipm_x != NULL)
    {
        *ipm_x = (rot[1][0] * raw_y + rot[1][1] * raw_x + rot[1][2]) / den;
    }
    if(ipm_y != NULL)
    {
        *ipm_y = (rot[0][0] * raw_y + rot[0][1] * raw_x + rot[0][2]) / den;
    }
}
