#include "tracking/atg_reference_mainline.hpp"

#include "core/config.hpp"

#include "atg_reference_step.h"
#include "clip.hpp"

extern "C" {
#include "headfile.h"
}

#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{
constexpr double kCircleInGuideScale = 0.75;
constexpr double kCircleRightOutGuideScale = 0.75;
constexpr double kCircleRunningGuideScale = 0.81;
constexpr float kRadToDeg = 180.0F / 3.14159265358979323846F;

point_t atg_control_ref(const runtime_t *rt)
{
    point_t ref = {CONTROL_CENTER_X, START_HIGH};
    if(rt != nullptr)
    {
        ref.x = clip_i(rt->control_center_x, 0, RAW_W - 1);
    }
    return ref;
}

void clear_vision_state(runtime_t *rt)
{
    std::memset(&rt->vision, 0, sizeof(rt->vision));
    rt->vision.control_ref = atg_control_ref(rt);
}

void copy_atg_midline(runtime_t *rt)
{
    midline_t *mid = &rt->vision.mid;
    const point_t ref = rt->vision.control_ref;
    mid->step = std::min(rptsn_num, static_cast<int>(POINT_MAX));

    int last_x = ref.x;
    int last_y = ref.y;
    int dist = 0;
    for(int i = 0; i < mid->step; ++i)
    {
        const int x = clip_i(static_cast<int>(std::lround(rptsn[i][0])), 0, IPM_W - 1);
        const int y = clip_i(static_cast<int>(std::lround(rptsn[i][1])), 0, IPM_H - 1);
        mid->pts[i] = {x, y};
        if(i == 0)
        {
            mid->dist[i] = 0;
        }
        else
        {
            const double dx = static_cast<double>(x - last_x);
            const double dy = static_cast<double>(y - last_y);
            dist += static_cast<int>(std::lround(std::hypot(dx, dy)));
            mid->dist[i] = dist;
        }
        last_x = x;
        last_y = y;
    }
}

// 普通巡线用本车标定过的短预瞄误差，保证直道居中不被 ATG 原生 Guide 的远点权重带偏。
double atg_lookahead_error(const midline_t *mid)
{
    if(mid == nullptr || mid->step <= 0)
    {
        return 0.0;
    }

    const int lookahead = atg_lookahead_dist_px();
    const int window = std::max(4, lookahead / 5);
    const double ref_x = static_cast<double>(cx);
    const double ref_y = static_cast<double>(cy);

    double sum_x = 0.0;
    double sum_y = 0.0;
    int count = 0;
    for(int i = 0; i < mid->step; ++i)
    {
        if(mid->dist[i] < lookahead - window ||
           mid->dist[i] > lookahead + window)
        {
            continue;
        }
        sum_x += mid->pts[i].x;
        sum_y += mid->pts[i].y;
        count++;
    }
    if(count > 0)
    {
        const double dx = sum_x / static_cast<double>(count) - ref_x;
        const double dy = ref_y - sum_y / static_cast<double>(count) + ROAD_HALF_WIDTH * 8.0 / 9.0;
        return -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
    }

    int best = 0;
    int best_err = 1 << 30;
    for(int i = 0; i < mid->step; ++i)
    {
        if(mid->dist[i] <= 0)
        {
            continue;
        }
        const int err = std::abs(mid->dist[i] - lookahead);
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }

    const double dx = static_cast<double>(mid->pts[best].x) - ref_x;
    const double dy = ref_y - static_cast<double>(mid->pts[best].y) + ROAD_HALF_WIDTH * 8.0 / 9.0;
    return -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
}
} // namespace

int atg_lookahead_dist_px()
{
    const control_config_t &c = control_config();
    const double circ = 3.14159265358979323846 * static_cast<double>(c.encoder_gear_diameter_m);
    const double v_mps = static_cast<double>(c.target_rps) * circ;
    double dist_m = static_cast<double>(c.lookahead_time_s) * v_mps;
    if(dist_m < 0.20)
    {
        dist_m = 0.20;
    }
    if(dist_m > 0.58)
    {
        dist_m = 0.58;
    }
    return static_cast<int>(std::lround(dist_m * static_cast<double>(pixel_per_meter)));
}

int track_line_found(const runtime_t *rt)
{
    return rt != nullptr && rt->vision.line_found && rt->vision.mid.step > 0;
}

int midline_has_forward_lookahead(const midline_t *midline, int aim_distance, int ref_y)
{
    if(midline == nullptr || midline->step <= 0)
    {
        return 0;
    }

    int best = -1;
    for(int i = 0; i < midline->step; ++i)
    {
        if(midline->dist[i] < aim_distance)
        {
            continue;
        }
        if(best < 0 || midline->dist[i] < midline->dist[best])
        {
            best = i;
        }
    }
    if(best < 0)
    {
        return 0;
    }
    return midline->pts[best].y < ref_y;
}

int atg_cross_type_value()
{
    return cross_type;
}

int atg_cross_half_active()
{
    return cross_type == CROSS_HALF;
}

int atg_element_active()
{
    return cross_type != CROSS_NONE ||
           circle_type != CIRCLE_NONE ||
           round_type != ROUND_NONE ||
           yroad_type != YROAD_NONE ||
           ramp_type != RAMP_NONE ||
           garage_type != GARAGE_NONE;
}

const char *atg_selected_line_source_name()
{
    return line_src();
}

int atg_selected_line_source_id()
{
    return line_src_id();
}

std::int64_t atg_circle_begin_dist()
{
    return atg_reference_circle_begin_dist();
}

std::int64_t atg_circle_begin_last_dist()
{
    return atg_reference_circle_begin_last_dist();
}

float atg_vehicle_raw_ref_x()
{
    return car_x();
}

void atg_raw_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y)
{
    raw_to_ipm(raw_x, raw_y, ipm_x, ipm_y);
}

void atg_ipm_to_raw(float ipm_x, float ipm_y, float *raw_x, float *raw_y)
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

void atg_set_vehicle_raw_ref_x(float x)
{
    set_car_x(x);
}

void atg_update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid)
{
    update_circle_heading(yaw_rate_rad_s, period_ms, valid);
}

atg_replay_snapshot_t atg_replay_snapshot()
{
    atg_replay_snapshot_t s = {};
    s.track_type = track_type;
    s.cross_type = cross_type;
    s.circle_type = circle_type;
    s.round_type = round_type;
    s.yroad_type = yroad_type;
    s.ramp_type = ramp_type;
    s.road_type = road_type;
    s.speed_type = speed_type;
    s.rpts0s_num = rpts0s_num;
    s.rpts1s_num = rpts1s_num;
    s.ipts0_num = ipts0_num;
    s.ipts1_num = ipts1_num;
    s.rpts0_num = rpts0_num;
    s.rpts1_num = rpts1_num;
    s.rptsc0_num = rptsc0_num;
    s.rptsc1_num = rptsc1_num;
    s.rpts_num = rpts_num;
    s.rptsn_num = rptsn_num;
    s.line_src_id = atg_selected_line_source_id();
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
    s.far_rpts0s_num = far_rpts0s_num;
    s.far_rpts1s_num = far_rpts1s_num;
    s.is_straight0 = is_straight0 ? 1 : 0;
    s.is_straight1 = is_straight1 ? 1 : 0;
    s.is_straight_far_0 = is_straight_far_0 ? 1 : 0;
    s.is_straight_far_1 = is_straight_far_1 ? 1 : 0;
    s.conf1_deg = conf1_max * 180.0F / 3.14159265358979323846F;
    s.conf2_deg = conf2_max * 180.0F / 3.14159265358979323846F;
    s.conf3_deg = conf3_max * 180.0F / 3.14159265358979323846F;
    s.conf4_deg = conf4_max * 180.0F / 3.14159265358979323846F;
    s.total_distence = total_distence;
    s.circle_begin_dist = atg_circle_begin_dist();
    s.circle_begin_last_dist = atg_circle_begin_last_dist();
    s.ramp_total_distence = Ramp_total_distence;
    s.cx = cx;
    s.cy = cy;
    s.guide = Guide;
    s.guide_up = Guide_up;
    s.guide_up_up = Guide_up_up;
    return s;
}

atg_report_snapshot_t atg_report_snapshot()
{
    atg_report_snapshot_t s = {};
    s.track_type = track_type;
    s.cross_type = cross_type;
    s.circle_type = circle_type;
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
    s.circle_begin_dist = atg_circle_begin_dist();
    s.circle_begin_last_dist = atg_circle_begin_last_dist();

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
    s.line_src_id = atg_selected_line_source_id();

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

    s.atg_seed0_found = atg_seed0_found;
    s.atg_seed0_x = atg_seed0_x;
    s.atg_seed0_y = atg_seed0_y;
    s.atg_seed1_found = atg_seed1_found;
    s.atg_seed1_x = atg_seed1_x;
    s.atg_seed1_y = atg_seed1_y;
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
    return s;
}

atg_line_points_view_t atg_line_points(atg_line_points_id id)
{
    switch(id)
    {
    case atg_line_points_id::near_left_smooth:
        return {rpts0s, rpts0s_num};
    case atg_line_points_id::near_right_smooth:
        return {rpts1s, rpts1s_num};
    case atg_line_points_id::center_left:
        return {rptsc0, rptsc0_num};
    case atg_line_points_id::center_right:
        return {rptsc1, rptsc1_num};
    case atg_line_points_id::selected:
        return {rptsn, rptsn_num};
    case atg_line_points_id::selected_raw:
        return {inv_rptsn, rptsn_num};
    case atg_line_points_id::far_left_smooth:
        return {far_rpts0s, far_rpts0s_num};
    case atg_line_points_id::far_right_smooth:
        return {far_rpts1s, far_rpts1s_num};
    case atg_line_points_id::splicing_leftline:
        return {Splicing_leftline, Splicing_leftline_num};
    case atg_line_points_id::splicing_leftline_center:
        return {Splicing_leftline_center, Splicing_leftline_center_num};
    case atg_line_points_id::splicing_rightline:
        return {Splicing_rightline, Splicing_rightline_num};
    case atg_line_points_id::splicing_rightline_center:
        return {Splicing_rightline_center, Splicing_rightline_center_num};
    case atg_line_points_id::leftline:
        return {leftline, leftline_num};
    case atg_line_points_id::rightline:
        return {rightline, rightline_num};
    }
    return {nullptr, 0};
}

atg_raw_points_view_t atg_raw_points(atg_raw_points_id id)
{
    switch(id)
    {
    case atg_raw_points_id::left:
        return {ipts0, ipts0_num};
    case atg_raw_points_id::right:
        return {ipts1, ipts1_num};
    }
    return {nullptr, 0};
}

const char *atg_circle_type_name(int value)
{
    switch(value)
    {
    case CIRCLE_NONE:
        return "CIRCLE_NONE";
    case CIRCLE_LEFT_BEGIN:
        return "CIRCLE_LEFT_BEGIN";
    case CIRCLE_RIGHT_BEGIN:
        return "CIRCLE_RIGHT_BEGIN";
    case CIRCLE_LEFT_RUNNING:
        return "CIRCLE_LEFT_RUNNING";
    case CIRCLE_RIGHT_RUNNING:
        return "CIRCLE_RIGHT_RUNNING";
    case CIRCLE_LEFT_OUT:
        return "CIRCLE_LEFT_OUT";
    case CIRCLE_RIGHT_OUT:
        return "CIRCLE_RIGHT_OUT";
    default:
        return "CIRCLE_UNKNOWN";
    }
}

const char *atg_cross_type_name(int value)
{
    switch(value)
    {
    case CROSS_NONE:
        return "CROSS_NONE";
    case CROSS_BEGIN:
        return "CROSS_BEGIN";
    case CROSS_IN:
        return "CROSS_IN";
    case CROSS_HALF:
        return "CROSS_HALF";
    default:
        return "CROSS_UNKNOWN";
    }
}

int atg_circle_entry_scan_seed_raw(int *seed_x, int *seed_y)
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

void tracking_reset(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }

    std::memset(rt, 0, sizeof(*rt));
    rt->control_center_x = CONTROL_CENTER_X;
    clear_vision_state(rt);
    atg_reference_reset();
}

// ATG wrapper：把 runtime 灰度图/encoder 送进参考算法，
// 再把 ATG 的 rptsn 转成 rt->vision.mid 和 guide_error。
int tracking_process_frame(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }

    clear_vision_state(rt);
    if(!rt->gray_valid)
    {
        return 0;
    }

    const int ok = atg_reference_process_frame(rt->gray, rt->encoder_total);
    rt->vision.line_found = ok && line_found() ? 1 : 0;
    if(!rt->vision.line_found)
    {
        return 0;
    }

    copy_atg_midline(rt);
    // ATG pure_angle feeds a steering-servo PID in the reference car. This
    // differential car publishes a heading-style error from the selected
    // current-frame rptsn line; element_active is consumed later as speed/brake
    // context, not as a reason to change the guide_error unit.
    rt->vision.guide_error =
        atg_lookahead_error(&rt->vision.mid) -
        static_cast<double>(control_config().guide_error_bias_deg);
    if(road_type == CURVE_NEAR && control_config().curve_entry_bias_deg != 0.0F)
    {
        const double curve_sign = (pure_angle < 0) ? 1.0 : ((pure_angle > 0) ? -1.0 : 0.0);
        rt->vision.guide_error += curve_sign * static_cast<double>(control_config().curve_entry_bias_deg);
    }
    if((circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_RIGHT_BEGIN) &&
       circle_ref_mode == CIRCLE_REF_IN_C)
    {
        rt->vision.guide_error *= kCircleInGuideScale;
    }
    else if(circle_type == CIRCLE_RIGHT_OUT)
    {
        rt->vision.guide_error *= kCircleRightOutGuideScale;
    }
    else if(circle_type == CIRCLE_LEFT_RUNNING || circle_type == CIRCLE_RIGHT_RUNNING)
    {
        rt->vision.guide_error *= kCircleRunningGuideScale;
        rt->vision.guide_error = std::clamp(rt->vision.guide_error, -35.0, 35.0);
    }
    return track_line_found(rt);
}
