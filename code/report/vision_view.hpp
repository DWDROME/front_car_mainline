#pragma once

#include <cstdint>

#include "types.hpp"

struct vision_anchor_point_t
{
    int found;
    int id;
    int raw_x;
    int raw_y;
};

struct vision_point2f_t
{
    float x;
    float y;
};

struct vision_lpt_debug_t
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

struct vision_snapshot_t
{
    int track_type;
    int cross_type;
    const char *cross_type_name;
    int circle_type;
    const char *circle_type_name;
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
    const char *line_src_name;

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

    int seed0_found;
    int seed0_x;
    int seed0_y;
    int seed1_found;
    int seed1_x;
    int seed1_y;
    vision_lpt_debug_t lpt0_debug;
    vision_lpt_debug_t lpt1_debug;

    vision_point2f_t inv_lpt0;
    vision_point2f_t inv_lpt1;
    vision_point2f_t inv_far_lpt0;
    vision_point2f_t inv_far_lpt1;
    int far_x11;
    int far_y1;

    int none_left_line;
    int none_right_line;
    int have_left_line;
    int have_right_line;
    vision_anchor_point_t circle_a;
    vision_anchor_point_t circle_b;
    vision_anchor_point_t circle_c;

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
    float vehicle_raw_ref_x;
};

enum class vision_line_id
{
    near_left_smooth,
    near_right_smooth,
    center_left,
    center_right,
    selected,
    selected_raw,
    far_left_smooth,
    far_right_smooth,
    splicing_leftline_center,
    splicing_rightline_center,
    leftline,
    rightline,
};

struct vision_line_view_t
{
    const float (*pts)[2];
    int count;
};

enum class vision_raw_id
{
    left,
    right,
};

struct vision_raw_view_t
{
    const int (*pts)[2];
    int count;
};

int vision_lookahead_dist_px(void);
void vision_raw_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y);
void vision_ipm_to_raw(float ipm_x, float ipm_y, float *raw_x, float *raw_y);
vision_snapshot_t vision_snapshot(void);
vision_line_view_t vision_line(vision_line_id id);
vision_raw_view_t vision_raw_line(vision_raw_id id);
int vision_circle_entry_seed(int *seed_x, int *seed_y);
