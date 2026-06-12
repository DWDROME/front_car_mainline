#include "atg_reference_step.h"

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
    sample_dist = 0.03f;
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
        total_distence = (int16)(total_distence + (int16)delta);
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
    if(circle_type == CIRCLE_RIGHT_IN)
    {
        if(far_Lpt1_found)
        {
            point_Cal_Line(Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                           Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                           far_rpts1s[far_Lpt1_rpts1s_id][0],
                           far_rpts1s[far_Lpt1_rpts1s_id][1],
                           leftline,
                           &leftline_num);
            Splicing_array(leftline,
                           leftline_num,
                           far_rpts1s,
                           far_Lpt1_rpts1s_id,
                           Splicing_leftline,
                           &Splicing_leftline_num,
                           1);
            Splicing_leftline_s1s_num = MT9V03X_H;
            resample_points(Splicing_leftline,
                            Splicing_leftline_num,
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
        else if(far_rpts1s_num > 10 && far_rpts1s[1][1] > 20)
        {
            point_Cal_Line(Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                           Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                           far_rpts1s[1][0],
                           far_rpts1s[1][1],
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
        if(far_Lpt0_found)
        {
            point_Cal_Line_2(Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                             Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                             far_rpts0s[far_Lpt0_rpts0s_id][0],
                             far_rpts0s[far_Lpt0_rpts0s_id][1],
                             rightline,
                             &rightline_num);
            Splicing_array(rightline,
                           rightline_num,
                           far_rpts0s,
                           far_Lpt0_rpts0s_id,
                           Splicing_rightline,
                           &Splicing_rightline_num,
                           1);
            Splicing_rightline_s0s_num = MT9V03X_H;
            resample_points(Splicing_rightline,
                            Splicing_rightline_num,
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
        else if(far_rpts0s_num > 10 && far_rpts0s[1][1] > 20)
        {
            point_Cal_Line_2(Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                             Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                             far_rpts0s[1][0],
                             far_rpts0s[1][1],
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
        if(circle_type == CIRCLE_RIGHT_OUT || circle_type == CIRCLE_RIGHT_IN)
        {
            rpts = Splicing_leftline_center;
            rpts_num = Splicing_leftline_center_num;
        }
        else if(circle_type == CIRCLE_LEFT_OUT || circle_type == CIRCLE_LEFT_IN)
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
    const float half_width = MT9V03X_W / 2.0f;
    cx = (rot[1][0] * MT9V03X_H * h_zoom + rot[1][1] * half_width + rot[1][2]) /
         (rot[2][0] * MT9V03X_H * h_zoom + rot[2][1] * half_width + rot[2][2]);
    cy = (rot[0][0] * MT9V03X_H * h_zoom + rot[0][1] * half_width + rot[0][2]) /
         (rot[2][0] * MT9V03X_H * h_zoom + rot[2][1] * half_width + rot[2][2]);

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
    track_type = TRACK_RIGHT;
    reset_element_state();
    clear_frame_outputs();
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
    select_work_line();

    const int ok = normalize_selected_line();
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
