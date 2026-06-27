#pragma once

#include <cstdint>

#include "types.hpp"

struct atg_replay_snapshot_t
{
    int track_type;
    int cross_type;
    int circle_type;
    int round_type;
    int yroad_type;
    int ramp_type;
    int road_type;
    int speed_type;
    int rpts0s_num;
    int rpts1s_num;
    int ipts0_num;
    int ipts1_num;
    int rpts0_num;
    int rpts1_num;
    int rptsc0_num;
    int rptsc1_num;
    int rpts_num;
    int rptsn_num;
    int line_src_id;
    int lpt0_found;
    int lpt0_id;
    int lpt1_found;
    int lpt1_id;
    int ypt0_found;
    int ypt0_id;
    int ypt1_found;
    int ypt1_id;
    int far_lpt0_found;
    int far_lpt0_id;
    int far_lpt1_found;
    int far_lpt1_id;
    int far_rpts0s_num;
    int far_rpts1s_num;
    int is_straight0;
    int is_straight1;
    int is_straight_far_0;
    int is_straight_far_1;
    float conf1_deg;
    float conf2_deg;
    float conf3_deg;
    float conf4_deg;
    int total_distence;
    std::int64_t circle_begin_dist;
    std::int64_t circle_begin_last_dist;
    int ramp_total_distence;
    float cx;
    float cy;
    float guide;
    float guide_up;
    float guide_up_up;
};

struct atg_anchor_point_t
{
    int found;
    int id;
    int raw_x;
    int raw_y;
};

struct atg_point2f_t
{
    float x;
    float y;
};

struct atg_lpt_debug_t
{
    int best_i;
    int best_im1;
    int best_ip1;
    int pass_nms;
    int pass_low;
    int pass_high;
    int pass_near;
    int pass_dir;
    int accept_i;
    float best_conf_rad;
    float best_conf_deg;
    float best_x;
    float best_y;
    float best_inv_x;
    float best_inv_y;
};

struct atg_report_snapshot_t
{
    int track_type;
    int cross_type;
    int circle_type;
    int round_type;
    int yroad_type;
    int ramp_type;
    int road_type;
    int speed_type;
    int garage_type;
    int circle_ref_mode;
    int circle_none;
    int circle_left_begin;
    int circle_right_begin;
    int circle_left_out;
    int circle_right_out;
    int circle_ref_in_c;
    int cross_or_circle_active;
    int cross_half;
    int not_have_line;
    int total_distence;
    int ramp_total_distence;
    std::int64_t circle_begin_dist;
    std::int64_t circle_begin_last_dist;

    int ipts0_num;
    int ipts1_num;
    int rpts0_num;
    int rpts1_num;
    int rpts0s_num;
    int rpts1s_num;
    int rptsc0_num;
    int rptsc1_num;
    int rpts_num;
    int rptsn_num;
    int far_ipts0_num;
    int far_ipts1_num;
    int far_rpts0s_num;
    int far_rpts1s_num;
    int line_src_id;

    int lpt0_found;
    int lpt0_id;
    int lpt1_found;
    int lpt1_id;
    int ypt0_found;
    int ypt0_id;
    int ypt1_found;
    int ypt1_id;
    int far_lpt0_found;
    int far_lpt0_id;
    int far_lpt1_found;
    int far_lpt1_id;
    int lpt0_found_flag;
    int lpt1_found_flag;
    int if_lost_left_line;
    int if_lost_right_line;

    int is_straight0;
    int is_straight1;
    int is_straight_far_0;
    int is_straight_far_1;
    float conf1_rad;
    float conf2_rad;
    float conf3_rad;
    float conf4_rad;
    float conf1_deg;
    float conf2_deg;
    float conf3_deg;
    float conf4_deg;

    int atg_seed0_found;
    int atg_seed0_x;
    int atg_seed0_y;
    int atg_seed1_found;
    int atg_seed1_x;
    int atg_seed1_y;
    atg_lpt_debug_t lpt0_debug;
    atg_lpt_debug_t lpt1_debug;

    atg_point2f_t inv_lpt0;
    atg_point2f_t inv_lpt1;
    atg_point2f_t inv_far_lpt0;
    atg_point2f_t inv_far_lpt1;
    int far_x11;
    int far_y1;

    int none_left_line;
    int none_right_line;
    int have_left_line;
    int have_right_line;
    atg_anchor_point_t circle_a;
    atg_anchor_point_t circle_b;
    atg_anchor_point_t circle_c;

    int begin_x;
    int begin_y;
    int block_size;
    int clip_value;
    int line_blur_kernel;
    float sample_dist;
    int pixel_per_meter;
    float angle_dist;
    float road_width;
    float aim_distance;
    float aim_distance_far;
    float round_aim_distance;
    int aim_idx;
    int aim_idx_up;
    int aim_idx_up_up;

    float cx;
    float cy;
    float guide;
    float guide_up;
    float guide_up_up;
    float pure_angle;
    float pure_angle_up;
};

enum class atg_line_points_id
{
    near_left_smooth,
    near_right_smooth,
    center_left,
    center_right,
    selected,
    selected_raw,
    far_left_smooth,
    far_right_smooth,
    splicing_leftline,
    splicing_leftline_center,
    splicing_rightline,
    splicing_rightline_center,
    leftline,
    rightline,
};

struct atg_line_points_view_t
{
    const float (*pts)[2];
    int count;
};

enum class atg_raw_points_id
{
    left,
    right,
};

struct atg_raw_points_view_t
{
    const int (*pts)[2];
    int count;
};

void tracking_reset(runtime_t *rt);
int tracking_process_frame(runtime_t *rt);
int track_line_found(const runtime_t *rt);

int atg_lookahead_dist_px();
int midline_has_forward_lookahead(const midline_t *midline, int aim_distance, int ref_y);

int atg_cross_type_value();
int atg_cross_half_active();
int atg_element_active();
const char *atg_selected_line_source_name();
int atg_selected_line_source_id();
std::int64_t atg_circle_begin_dist();
std::int64_t atg_circle_begin_last_dist();
float atg_vehicle_raw_ref_x();
void atg_raw_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y);
void atg_ipm_to_raw(float ipm_x, float ipm_y, float *raw_x, float *raw_y);
void atg_set_vehicle_raw_ref_x(float x);
void atg_update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid);
atg_replay_snapshot_t atg_replay_snapshot();
atg_report_snapshot_t atg_report_snapshot();
atg_line_points_view_t atg_line_points(atg_line_points_id id);
atg_raw_points_view_t atg_raw_points(atg_raw_points_id id);
const char *atg_circle_type_name(int value);
const char *atg_cross_type_name(int value);
int atg_circle_entry_scan_seed_raw(int *seed_x, int *seed_y);
