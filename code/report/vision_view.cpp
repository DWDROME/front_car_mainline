#include "report/vision_view.hpp"

#include "core/config.hpp"

#include "vision_step.h"

extern "C" {
#include "headfile.h"
}

namespace
{
constexpr float kRadToDeg = 180.0F / 3.14159265358979323846F;
} // namespace

int vision_lookahead_dist_px(void)
{
    return control_lookahead_dist_px(pixel_per_meter);
}

void vision_raw_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y)
{
    raw_to_ipm(raw_x, raw_y, ipm_x, ipm_y);
}

void vision_ipm_to_raw(float ipm_x, float ipm_y, float *raw_x, float *raw_y)
{
    if(raw_x != nullptr)
    {
        *raw_x = Cal_inv_rot_x(ipm_x, ipm_y);
    }
    if(raw_y != nullptr)
    {
        *raw_y = Cal_inv_rot_y(ipm_x, ipm_y);
    }
}

vision_snapshot_t vision_snapshot(void)
{
    vision_snapshot_t s = {};
    s.track_type = track_type;
    s.cross_type = cross_type;
    switch(cross_type)
    {
    case CROSS_NONE:
        s.cross_type_name = "CROSS_NONE";
        break;
    case CROSS_BEGIN:
        s.cross_type_name = "CROSS_BEGIN";
        break;
    case CROSS_IN:
        s.cross_type_name = "CROSS_IN";
        break;
    case CROSS_HALF:
        s.cross_type_name = "CROSS_HALF";
        break;
    default:
        s.cross_type_name = "CROSS_UNKNOWN";
        break;
    }
    s.circle_type = circle_type;
    switch(circle_type)
    {
    case CIRCLE_NONE:
        s.circle_type_name = "CIRCLE_NONE";
        break;
    case CIRCLE_LEFT_BEGIN:
        s.circle_type_name = "CIRCLE_LEFT_BEGIN";
        break;
    case CIRCLE_RIGHT_BEGIN:
        s.circle_type_name = "CIRCLE_RIGHT_BEGIN";
        break;
    case CIRCLE_LEFT_RUNNING:
        s.circle_type_name = "CIRCLE_LEFT_RUNNING";
        break;
    case CIRCLE_RIGHT_RUNNING:
        s.circle_type_name = "CIRCLE_RIGHT_RUNNING";
        break;
    case CIRCLE_LEFT_OUT:
        s.circle_type_name = "CIRCLE_LEFT_OUT";
        break;
    case CIRCLE_RIGHT_OUT:
        s.circle_type_name = "CIRCLE_RIGHT_OUT";
        break;
    default:
        s.circle_type_name = "CIRCLE_UNKNOWN";
        break;
    }
    s.round_type = round_type;
    s.yroad_type = yroad_type;
    s.ramp_type = ramp_type;
    s.road_type = road_type;
    s.speed_type = speed_type;
    s.garage_type = garage_type;
    s.circle_ref_mode = circle_ref_mode;
    s.circle_none = circle_type == CIRCLE_NONE ? 1 : 0;
    s.circle_left_begin = circle_type == CIRCLE_LEFT_BEGIN ? 1 : 0;
    s.circle_right_begin = circle_type == CIRCLE_RIGHT_BEGIN ? 1 : 0;
    s.circle_left_out = circle_type == CIRCLE_LEFT_OUT ? 1 : 0;
    s.circle_right_out = circle_type == CIRCLE_RIGHT_OUT ? 1 : 0;
    s.circle_ref_in_c = circle_ref_mode == CIRCLE_REF_IN_C ? 1 : 0;
    s.cross_or_circle_active =
        (cross_type != CROSS_NONE || circle_type != CIRCLE_NONE) ? 1 : 0;
    s.cross_half = cross_type == CROSS_HALF ? 1 : 0;
    s.not_have_line = not_have_line;
    s.total_distence = total_distence;
    s.ramp_total_distence = Ramp_total_distence;
    s.circle_begin_dist = begin_dist;
    s.circle_begin_last_dist = last_begin_dist;

    s.ipts0_num = ipts0_num;
    s.ipts1_num = ipts1_num;
    s.rpts0_num = rpts0_num;
    s.rpts1_num = rpts1_num;
    s.rpts0s_num = rpts0s_num;
    s.rpts1s_num = rpts1s_num;
    s.rptsc0_num = rptsc0_num;
    s.rptsc1_num = rptsc1_num;
    s.rpts_num = rpts_num;
    s.rptsn_num = rptsn_num;
    s.far_ipts0_num = far_ipts0_num;
    s.far_ipts1_num = far_ipts1_num;
    s.far_rpts0s_num = far_rpts0s_num;
    s.far_rpts1s_num = far_rpts1s_num;
    s.line_src_id = src_id;
    s.line_src_name = src;

    s.lpt0_found = Lpt0_found ? 1 : 0;
    s.lpt0_id = Lpt0_found ? Lpt0_rpts0s_id : -1;
    s.lpt1_found = Lpt1_found ? 1 : 0;
    s.lpt1_id = Lpt1_found ? Lpt1_rpts1s_id : -1;
    s.ypt0_found = Ypt0_found ? 1 : 0;
    s.ypt0_id = Ypt0_found ? Ypt0_rpts0s_id : -1;
    s.ypt1_found = Ypt1_found ? 1 : 0;
    s.ypt1_id = Ypt1_found ? Ypt1_rpts1s_id : -1;
    s.far_lpt0_found = far_Lpt0_found ? 1 : 0;
    s.far_lpt0_id = far_Lpt0_found ? far_Lpt0_rpts0s_id : -1;
    s.far_lpt1_found = far_Lpt1_found ? 1 : 0;
    s.far_lpt1_id = far_Lpt1_found ? far_Lpt1_rpts1s_id : -1;
    s.lpt0_found_flag = Lpt0_found_flag;
    s.lpt1_found_flag = Lpt1_found_flag;
    s.if_lost_left_line = if_lost_left_line;
    s.if_lost_right_line = if_lost_right_line;

    s.is_straight0 = is_straight0 ? 1 : 0;
    s.is_straight1 = is_straight1 ? 1 : 0;
    s.is_straight_far_0 = is_straight_far_0 ? 1 : 0;
    s.is_straight_far_1 = is_straight_far_1 ? 1 : 0;
    s.conf1_rad = conf1_max;
    s.conf2_rad = conf2_max;
    s.conf3_rad = conf3_max;
    s.conf4_rad = conf4_max;
    s.conf1_deg = conf1_max * kRadToDeg;
    s.conf2_deg = conf2_max * kRadToDeg;
    s.conf3_deg = conf3_max * kRadToDeg;
    s.conf4_deg = conf4_max * kRadToDeg;

    s.seed0_found = atg_seed0_found;
    s.seed0_x = atg_seed0_x;
    s.seed0_y = atg_seed0_y;
    s.seed1_found = atg_seed1_found;
    s.seed1_x = atg_seed1_x;
    s.seed1_y = atg_seed1_y;
    s.lpt0_debug = {
        atg_lpt0_best_i,
        atg_lpt0_best_im1,
        atg_lpt0_best_ip1,
        atg_lpt0_pass_nms,
        atg_lpt0_pass_low,
        atg_lpt0_pass_high,
        atg_lpt0_pass_near,
        atg_lpt0_pass_dir,
        atg_lpt0_accept_i,
        atg_lpt0_best_conf,
        atg_lpt0_best_conf * kRadToDeg,
        atg_lpt0_best_x,
        atg_lpt0_best_y,
        atg_lpt0_best_inv_x,
        atg_lpt0_best_inv_y,
    };
    s.lpt1_debug = {
        atg_lpt1_best_i,
        atg_lpt1_best_im1,
        atg_lpt1_best_ip1,
        atg_lpt1_pass_nms,
        atg_lpt1_pass_low,
        atg_lpt1_pass_high,
        atg_lpt1_pass_near,
        atg_lpt1_pass_dir,
        atg_lpt1_accept_i,
        atg_lpt1_best_conf,
        atg_lpt1_best_conf * kRadToDeg,
        atg_lpt1_best_x,
        atg_lpt1_best_y,
        atg_lpt1_best_inv_x,
        atg_lpt1_best_inv_y,
    };

    s.inv_lpt0 = {inv_Lpt0_found[0], inv_Lpt0_found[1]};
    s.inv_lpt1 = {inv_Lpt1_found[0], inv_Lpt1_found[1]};
    s.inv_far_lpt0 = {inv_far_Lpt0_found[0], inv_far_Lpt0_found[1]};
    s.inv_far_lpt1 = {inv_far_Lpt1_found[0], inv_far_Lpt1_found[1]};
    s.far_x11 = far_x11;
    s.far_y1 = far_y1;

    s.none_left_line = none_left_line;
    s.none_right_line = none_right_line;
    s.have_left_line = have_left_line;
    s.have_right_line = have_right_line;
    s.circle_a = {circle_A_point.found, circle_A_point.id, circle_A_point.raw_x, circle_A_point.raw_y};
    s.circle_b = {circle_B_point.found, circle_B_point.id, circle_B_point.raw_x, circle_B_point.raw_y};
    s.circle_c = {circle_C_point.found, circle_C_point.id, circle_C_point.raw_x, circle_C_point.raw_y};

    s.begin_x = begin_x;
    s.begin_y = begin_y;
    s.block_size = block_size;
    s.clip_value = clip_value;
    s.line_blur_kernel = line_blur_kernel;
    s.sample_dist = sample_dist;
    s.pixel_per_meter = pixel_per_meter;
    s.angle_dist = angle_dist;
    s.road_width = ROAD_WIDTH;
    s.aim_distance = aim_distance;
    s.aim_distance_far = aim_distance_far;
    s.round_aim_distance = round_aim_distance;
    s.aim_idx = aim_idx;
    s.aim_idx_up = aim_idx_up;
    s.aim_idx_up_up = aim_idx_up_up;

    s.cx = cx;
    s.cy = cy;
    s.guide = Guide;
    s.guide_up = Guide_up;
    s.guide_up_up = Guide_up_up;
    s.pure_angle = pure_angle;
    s.pure_angle_up = pure_angle_up;
    s.vehicle_raw_ref_x = car_raw_x;
    return s;
}

vision_line_view_t vision_line(vision_line_id id)
{
    switch(id)
    {
    case vision_line_id::near_left_smooth:
        return {rpts0s, rpts0s_num};
    case vision_line_id::near_right_smooth:
        return {rpts1s, rpts1s_num};
    case vision_line_id::center_left:
        return {rptsc0, rptsc0_num};
    case vision_line_id::center_right:
        return {rptsc1, rptsc1_num};
    case vision_line_id::selected:
        return {rptsn, rptsn_num};
    case vision_line_id::selected_raw:
        return {inv_rptsn, rptsn_num};
    case vision_line_id::far_left_smooth:
        return {far_rpts0s, far_rpts0s_num};
    case vision_line_id::far_right_smooth:
        return {far_rpts1s, far_rpts1s_num};
    case vision_line_id::splicing_leftline_center:
        return {Splicing_leftline_center, Splicing_leftline_center_num};
    case vision_line_id::splicing_rightline_center:
        return {Splicing_rightline_center, Splicing_rightline_center_num};
    case vision_line_id::leftline:
        return {leftline, leftline_num};
    case vision_line_id::rightline:
        return {rightline, rightline_num};
    }
    return {nullptr, 0};
}

vision_raw_view_t vision_raw_line(vision_raw_id id)
{
    switch(id)
    {
    case vision_raw_id::left:
        return {ipts0, ipts0_num};
    case vision_raw_id::right:
        return {ipts1, ipts1_num};
    }
    return {nullptr, 0};
}

int vision_circle_entry_seed(int *seed_x, int *seed_y)
{
    if(seed_x == nullptr || seed_y == nullptr)
    {
        return 0;
    }

    const int left_entry_side =
        circle_type == CIRCLE_LEFT_BEGIN ||
        (circle_type == CIRCLE_NONE && Lpt0_found && !Lpt1_found);
    const int right_entry_side =
        circle_type == CIRCLE_RIGHT_BEGIN ||
        (circle_type == CIRCLE_NONE && !Lpt0_found && Lpt1_found);

    int side = -1;
    if(left_entry_side)
    {
        side = 0;
    }
    else if(right_entry_side)
    {
        side = 1;
    }
    else
    {
        return 0;
    }

    float seed_raw_x = 0.0F;
    float seed_raw_y = 0.0F;
    return circle_entry_inner_seed(side, seed_x, seed_y, &seed_raw_x, &seed_raw_y);
}
