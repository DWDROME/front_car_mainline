#pragma once

#include <cstdint>

#include "tuning.hpp"

struct point_t
{
    // 坐标统一按当前运行时图像解释：x 向右，y 向下。
    int x;
    int y;
};

struct midline_t
{
    // 控制中线点列，语义是 ATG IPM/控制坐标；不是 assistant 原图红线。
    point_t pts[POINT_MAX];

    // dist[i] 是从 pts[0] 到 pts[i] 的累计近似弧长，lookahead_error 按它选预瞄点。
    int dist[POINT_MAX];
    int step;
};

struct vision_state_t
{
    // 只保留控制层和外围输出真正需要的 ATG 当前帧薄结果。
    int line_found;
    point_t control_ref;
    midline_t mid;
    double guide_error;
};

struct control_state_t
{
    // 控制输出状态。yaw-rate 单位为 mrad/s，duty 单位按 drive_output 的 PWM 占空比解释。
    int input_valid;
    int stop_request;
    int target_yaw_rate_mrad_s;
    int yaw_cmd_mrad_s;
    int actual_yaw_rate_mrad_s;
    int left_target_rps_milli;
    int right_target_rps_milli;
    int left_actual_rps_milli;
    int right_actual_rps_milli;
    int signed_output;
    int left_duty;
    int right_duty;
};

struct control_input_t
{
    // 控制层需要的当前帧视觉输入，由 runner 从当前 ATG step 结果生成。
    int line_found;
    int stop_line;
    int element_active;
    int fixed_yaw_rate_valid;
    int fixed_yaw_rate_mrad_s;
    int spin_mode;
    double guide_error;
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
    // 输入图像与 ATG 距离状态。ATG 算法状态由 atg_reference 自己的全局变量维护。
    uint8_t gray[RAW_H][RAW_W];
    int gray_valid;
    int64_t encoder_total;

    // 控制参考中心来自本车标定；不是 ATG 算法内的 seed 搜索中心。
    int control_center_x;

    vision_state_t vision;
    control_state_t control;
};
