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

extern int64_t g_atg_reference_encoder_total;

static int64_t last_encoder_total;
static float g_vehicle_raw_ref_x = MT9V03X_W / 2.0f;

// 环岛状态停滞出口：ATG 原工程是舵机车，选线失败帧车仍按旧速度滚动，
// 状态机靠"继续行驶"满足视觉出口或 total_distence 强制出口（circle.c 的 >4500）。
// 本车 line_found=0 即停车，编码器不再增长，两类出口都永远无法触发，
// 误入的环岛状态会把车锁死在原地。连续 ATG_CIRCLE_STALL_FRAMES 帧
// "环岛状态活跃但无任何选线"时复位环岛状态，显式打日志；
// 不伪造线、不复用旧帧，复位后若环岛证据真实存在会重新自然触发。
enum
{
    ATG_CIRCLE_STALL_FRAMES = 30,
};
static int g_circle_stall_frames;

// CIRCLE_*_BEGIN 误入撤销：真环 BEGIN 后短距离内必然出现入环口"丢线"事件
// (none_left/right_line>0) 才能推进到 IN；直道伪 L 误入时该事件永不发生，
// 状态会滞留并把 track_type 锁在对侧边线上(本次实测表现为稳定贴左直行)。
// 进入 BEGIN 后累计行驶超过 ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS(约0.8m)仍无丢线
// 事件即判定证据消失，撤回 NONE 并显式打日志。用距离不用帧数，与车速解耦。
// 本 port 的 total_distence 是 int16，元素内门限沿用 ATG counts 量级；
// 0.8m 对应约 24000，低于 int16 饱和值，能在误入 BEGIN 时实际触发撤销。
enum
{
    ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS = 24000,
};
static int64_t g_circle_begin_dist;

#ifndef ATG_ENABLE_CROSS
#define ATG_ENABLE_CROSS 1
#endif
#ifndef ATG_ENABLE_CIRCLE
#define ATG_ENABLE_CIRCLE 1
#endif
#ifndef ATG_ENABLE_ROUND
#define ATG_ENABLE_ROUND 0
#endif
#ifndef ATG_ENABLE_RAMP
#define ATG_ENABLE_RAMP 0
#endif
#ifndef ATG_ENABLE_YROAD
#define ATG_ENABLE_YROAD 0
#endif
#ifndef ATG_ENABLE_GARAGE
#define ATG_ENABLE_GARAGE 0
#endif

enum
{
    RAW_LEFT_ANCHOR_X = 5,
    RAW_RIGHT_ANCHOR_X = MT9V03X_W - 6,
    RAW_BOTTOM_ANCHOR_Y = MT9V03X_H - 2,
    CIRCLE_FIXED_IN_TARGET_RAW_Y = 70,
    CIRCLE_FIXED_IN_TARGET_RAW_X_OFFSET = 35,
    CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X = MT9V03X_W / 2 - CIRCLE_FIXED_IN_TARGET_RAW_X_OFFSET,
    CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X = MT9V03X_W / 2 + CIRCLE_FIXED_IN_TARGET_RAW_X_OFFSET,
};

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

static int clipped_count(int n)
{
    return range_limit(n, 0, MT9V03X_H);
}

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
}

static void reset_element_state(void)
{
    cross_type = CROSS_NONE;
    circle_type = CIRCLE_NONE;
    reset_circle_entry_votes();
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
    far_Lpt0_found_flag = 0;
    far_Lpt1_found_flag = 0;
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    is_large_circle = 0;
    is_small_circle = 0;
    circle_count = 0;
    Count_dis_Flag = 0;
    total_distence = 0;
    g_circle_begin_dist = 0;
    Ramp_total_distence = 0;
    Clean_Time_count = 0;
    Clean_Time_count_flag = 0;
    broadcast_flag = 1;
    if_clean_pid = 0;
}

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
        // 饱和而不回绕：误入元素状态长期滞留时 int16 累计会绕成负数，破坏所有距离门限。
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
        g_circle_begin_dist = 0;
    }
}

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

static void run_atg_elements(void)
{
    keep_disabled_elements_idle();

#if ATG_ENABLE_ROUND
    if(!garage_type &&
       !yroad_type &&
       !ramp_type &&
       (circle_type == CIRCLE_RIGHT_BEGIN ||
        circle_type == CIRCLE_LEFT_BEGIN ||
        circle_type == CIRCLE_LEFT_IN ||
        circle_type == CIRCLE_RIGHT_IN ||
        circle_type == CIRCLE_NONE))
    {
        check_round();
    }
#endif
#if ATG_ENABLE_CROSS
    if(!yroad_type && !ramp_type && !circle_type && !cross_type && !round_type && !garage_type)
    {
        check_Half();
    }
#endif
#if ATG_ENABLE_RAMP
    if(!circle_type && !yroad_type && !garage_type && !ramp_type)
    {
        Check_ramp();
    }
#endif
#if ATG_ENABLE_CIRCLE
    if(!cross_type && !yroad_type && !round_type && !ramp_type && !garage_type)
    {
        check_circle();
    }
#endif
#if ATG_ENABLE_YROAD
    if(!circle_type && !ramp_type && !garage_type)
    {
        check_yroad();
    }
#endif

    keep_disabled_elements_idle();

#if ATG_ENABLE_ROUND
    if(yroad_type == YROAD_NONE && round_type != ROUND_NONE && ramp_type == RAMP_NONE && !garage_type)
    {
        run_round();
    }
#endif
#if ATG_ENABLE_RAMP
    if(ramp_type != RAMP_NONE && !circle_type && !yroad_type && !round_type && !garage_type)
    {
        Run_Ramp();
    }
#endif
#if ATG_ENABLE_CROSS
    if(cross_type != CROSS_NONE && !circle_type && !yroad_type && round_type == ROUND_NONE && !garage_type)
    {
        run_cross();
    }
#endif
#if ATG_ENABLE_CIRCLE
    if(circle_type != CIRCLE_NONE && !cross_type && !yroad_type && round_type == ROUND_NONE && !garage_type)
    {
        run_circle();
    }
#endif
#if ATG_ENABLE_YROAD
    if(!circle_type && !cross_type && yroad_type != YROAD_NONE && round_type == ROUND_NONE && !garage_type)
    {
        run_yroad();
    }
#endif

    keep_disabled_elements_idle();
}

static void build_circle_spliced_lines(void)
{
    // 补线中心是环岛 IN/OUT 的控制选线来源。
    // IN 是明确的元素固定动作，使用当帧固定 raw 锚点重建；OUT 仍依赖当帧远线证据。
    // 不复用旧帧中线，当前状态不能建线时就让选线显式为空。
    Splicing_leftline_center_num = 0;
    Splicing_rightline_center_num = 0;

    if(circle_type == CIRCLE_RIGHT_IN)
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

        /*
         * legacy far-line splice for CIRCLE_RIGHT_IN:
         * if(far_Lpt1_found)
         * {
         *     point_Cal_Line(Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                    Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                    far_rpts1s[far_Lpt1_rpts1s_id][0],
         *                    far_rpts1s[far_Lpt1_rpts1s_id][1],
         *                    leftline,
         *                    &leftline_num);
         *     Splicing_array(leftline,
         *                    leftline_num,
         *                    far_rpts1s,
         *                    far_Lpt1_rpts1s_id,
         *                    Splicing_leftline,
         *                    &Splicing_leftline_num,
         *                    1);
         *     Splicing_leftline_s1s_num = MT9V03X_H;
         *     resample_points(Splicing_leftline,
         *                     Splicing_leftline_num,
         *                     Splicing_leftline_s1s,
         *                     &Splicing_leftline_s1s_num,
         *                     sample_dist * pixel_per_meter);
         *     track_leftline(Splicing_leftline_s1s,
         *                    Splicing_leftline_s1s_num,
         *                    Splicing_leftline_center,
         *                    (int)round(2.0),
         *                    pixel_per_meter * ROAD_WIDTH / 2);
         *     Splicing_leftline_center_num = Splicing_leftline_s1s_num;
         * }
         * else if(far_rpts1s_num > 10 && far_rpts1s[1][1] > 20)
         * {
         *     point_Cal_Line(Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                    Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                    far_rpts1s[1][0],
         *                    far_rpts1s[1][1],
         *                    leftline,
         *                    &leftline_num);
         *     Splicing_leftline_s1s_num = MT9V03X_H;
         *     resample_points(leftline,
         *                     leftline_num,
         *                     Splicing_leftline_s1s,
         *                     &Splicing_leftline_s1s_num,
         *                     sample_dist * pixel_per_meter);
         *     track_leftline(Splicing_leftline_s1s,
         *                    Splicing_leftline_s1s_num,
         *                    Splicing_leftline_center,
         *                    (int)round(2.0),
         *                    pixel_per_meter * ROAD_WIDTH / 2);
         *     Splicing_leftline_center_num = Splicing_leftline_s1s_num;
         * }
         */
    }
    else if(circle_type == CIRCLE_RIGHT_OUT && far_rpts0s_num > 0)
    {
        point_Cal_Line(far_rpts0s[far_rpts0s_num - 1][0],
                       far_rpts0s[far_rpts0s_num - 1][1],
                       Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                       Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
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
    else if(circle_type == CIRCLE_LEFT_IN)
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

        /*
         * legacy far-line splice for CIRCLE_LEFT_IN:
         * if(far_Lpt0_found)
         * {
         *     point_Cal_Line_2(Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                      Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                      far_rpts0s[far_Lpt0_rpts0s_id][0],
         *                      far_rpts0s[far_Lpt0_rpts0s_id][1],
         *                      rightline,
         *                      &rightline_num);
         *     Splicing_array(rightline,
         *                    rightline_num,
         *                    far_rpts0s,
         *                    far_Lpt0_rpts0s_id,
         *                    Splicing_rightline,
         *                    &Splicing_rightline_num,
         *                    1);
         *     Splicing_rightline_s0s_num = MT9V03X_H;
         *     resample_points(Splicing_rightline,
         *                     Splicing_rightline_num,
         *                     Splicing_rightline_s0s,
         *                     &Splicing_rightline_s0s_num,
         *                     sample_dist * pixel_per_meter);
         *     track_rightline(Splicing_rightline_s0s,
         *                     Splicing_rightline_s0s_num,
         *                     Splicing_rightline_center,
         *                     (int)round(2.0),
         *                     pixel_per_meter * ROAD_WIDTH / 2);
         *     Splicing_rightline_center_num = Splicing_rightline_s0s_num;
         * }
         * else if(far_rpts0s_num > 10 && far_rpts0s[1][1] > 20)
         * {
         *     point_Cal_Line_2(Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                      Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
         *                      far_rpts0s[1][0],
         *                      far_rpts0s[1][1],
         *                      rightline,
         *                      &rightline_num);
         *     Splicing_rightline_s0s_num = MT9V03X_H;
         *     resample_points(rightline,
         *                     rightline_num,
         *                     Splicing_rightline_s0s,
         *                     &Splicing_rightline_s0s_num,
         *                     sample_dist * pixel_per_meter);
         *     track_rightline(Splicing_rightline_s0s,
         *                     Splicing_rightline_s0s_num,
         *                     Splicing_rightline_center,
         *                     (int)round(2.0),
         *                     pixel_per_meter * ROAD_WIDTH / 2);
         *     Splicing_rightline_center_num = Splicing_rightline_s0s_num;
         * }
         */
    }
    else if(circle_type == CIRCLE_LEFT_OUT && far_rpts1s_num > 0)
    {
        point_Cal_Line(far_rpts1s[far_rpts1s_num - 1][0],
                       far_rpts1s[far_rpts1s_num - 1][1],
                       Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                       Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
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
                        (int)round(5.0),
                        pixel_per_meter * ROAD_WIDTH / 2);
        Splicing_rightline_center_num = Splicing_rightline_s0s_num;
    }
}

static void select_work_line(void)
{
    if(cross_type != CROSS_IN &&
       cross_type != CROSS_HALF &&
       garage_type != GARAGE_FOUND_LEFT &&
       garage_type != GARAGE_FOUND_RIGHT)
    {
        build_circle_spliced_lines();
        if((circle_type == CIRCLE_RIGHT_OUT || circle_type == CIRCLE_RIGHT_IN) &&
           Splicing_leftline_center_num > 0)
        {
            rpts = Splicing_leftline_center;
            rpts_num = Splicing_leftline_center_num;
        }
        else if((circle_type == CIRCLE_LEFT_OUT || circle_type == CIRCLE_LEFT_IN) &&
                Splicing_rightline_center_num > 0)
        {
            rpts = Splicing_rightline_center;
            rpts_num = Splicing_rightline_center_num;
        }
        else if(track_type == TRACK_LEFT)
        {
            rpts = rptsc0;
            rpts_num = rptsc0_num;
        }
        else
        {
            rpts = rptsc1;
            rpts_num = rptsc1_num;
        }
    }
    else if(track_type == TRACK_LEFT)
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
    }
    else
    {
        const int start = range_limit(far_Lpt1_rpts1s_id, 0, far_rpts1s_num);
        const int count = clipped_count(far_rpts1s_num - start);
        rpts = rptsc1;
        track_rightline(far_rpts1s + start,
                        count,
                        rpts,
                        (int)round(angle_dist / sample_dist),
                        pixel_per_meter * ROAD_WIDTH / 2);
        rpts_num = count;
    }
}

static int normalize_selected_line(void)
{
    if(rpts == NULL || rpts_num <= 0)
    {
        rptsn_num = 0;
        return 0;
    }

    const float h_zoom = 0.98f;
    atg_reference_raw_ref_to_ipm(g_vehicle_raw_ref_x, MT9V03X_H * h_zoom, &cx, &cy);

    float min_dist = 10000.0f;
    int begin_id = 0;
    for(int i = 0; i < rpts_num; i++)
    {
        float dx = rpts[i][0] - cx;
        float dy = rpts[i][1] - cy;
        float dist = sqrtf(dx * dx + dy * dy);
        if(dist < min_dist)
        {
            min_dist = dist;
            begin_id = i;
        }
    }

    if(begin_id < 0 || rpts_num - begin_id < 2)
    {
        rptsn_num = 0;
        return 0;
    }

    rpts[begin_id][0] = cx;
    rpts[begin_id][1] = cy;
    rptsn_num = MT9V03X_HH;
    resample_points(rpts + begin_id,
                    rpts_num - begin_id,
                    rptsn,
                    &rptsn_num,
                    sample_dist * pixel_per_meter);
    if(rptsn_num <= 0)
    {
        return 0;
    }

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
    return rptsn_num > 0;
}

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

// 复位集对照 circle.c CIRCLE_LEFT_END/RIGHT_END 自然退出时的还原变量。
static void reset_circle_to_none(const char *reason)
{
    printf("ATGCircleReset: %s circle_type=%d -> NONE\n", reason, (int)circle_type);
        circle_type = CIRCLE_NONE;
        reset_circle_entry_votes();
    road_type = ROAD_NORMAL;
    begin_y = BEGIN_Y;
    Count_dis_Flag = 0;
    aim_distance = aim_distance_far;
    is_large_circle = 0;
    is_small_circle = 0;
    if_lost_left_line = 0;
    if_lost_right_line = 0;
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    if_clean_pid = 0;
    g_circle_stall_frames = 0;
    g_circle_begin_dist = 0;
}

static void revoke_idle_circle_begin(void)
{
    if(circle_type == CIRCLE_LEFT_BEGIN && none_left_line == 0 &&
       g_circle_begin_dist > ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS)
    {
        reset_circle_to_none("LEFT_BEGIN idle beyond 0.8m without lost-line evidence,");
    }
    else if(circle_type == CIRCLE_RIGHT_BEGIN && none_right_line == 0 &&
            g_circle_begin_dist > ATG_CIRCLE_BEGIN_MAX_DIST_COUNTS)
    {
        reset_circle_to_none("RIGHT_BEGIN idle beyond 0.8m without lost-line evidence,");
    }
}

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
    circle_type = CIRCLE_NONE;
    reset_circle_entry_votes();
    road_type = ROAD_NORMAL;
    begin_y = BEGIN_Y;
    Count_dis_Flag = 0;
    aim_distance = aim_distance_far;
    is_large_circle = 0;
    is_small_circle = 0;
    if_lost_left_line = 0;
    if_lost_right_line = 0;
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
    if_clean_pid = 0;
    g_circle_stall_frames = 0;
}

int atg_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total)
{
    if(gray == NULL)
    {
        return 0;
    }

    g_atg_reference_encoder_total = encoder_total;
    img_raw.data = (uint8 *)gray;
    clear_frame_outputs();

    image_handle();
    find_corners();
    choose_track_type_from_near_lines();
    run_atg_elements();
    update_distance_counters(encoder_total);
    revoke_idle_circle_begin();
    select_work_line();

    const int ok = normalize_selected_line();
    exit_circle_after_stall(ok);
    if(ok)
    {
        check_road();
    }
    return ok;
}

int atg_reference_track_line_found(void)
{
    return rptsn_num > 0;
}

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
