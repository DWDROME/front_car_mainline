#pragma once

// 控制层默认参数；启动时会尝试读取 /root/front_car_mainline.yaml 覆盖这些默认值。

struct control_config_t
{
    // 控制周期必须 >0。实车 live 入口通常限制到 1~100ms。
    int   control_period_ms        = 10;

    // 基础速度目标，单位 rps。元素内用 element_target_rps。
    float target_rps               = 4.0F;
    float element_target_rps       = 3.0F;
    float speed_target_rps         = 4.0F;

    // 左右轮 FF+PI 参数。base 是前馈占空，kp/ki 是轮速闭环。
    float left_speed_base_percent  = 9.0F;
    float right_speed_base_percent = 9.7F;
    float left_speed_kp            = 1.25F;
    float right_speed_kp           = 1.25F;
    float left_speed_ki            = 0.35F;
    float right_speed_ki           = 0.35F;

    // 差速运动学参数。轮距/轮径不准会直接影响左右轮目标转速差。
    float wheel_track_m            = 0.155F;
    float encoder_gear_diameter_m  = 0.018F;

    // IMU yaw-rate 反馈。未验证 IMU 方向和比例前，imu_yaw_feedback_enabled 可以关为 0。
    float gyro_raw_to_rad_s        = 0.001277562F;
    int   imu_yaw_feedback_enabled = 1;

    // 视觉外环 PD。outer_kd 默认允许为 0，图像误差抖动时不要轻易打开。
    float outer_kp                 = 0.03F;
    float outer_kd                 = 0.0F;
    float outer_sign               = 1.0F;
    float straight_error_threshold = 12.0F;
    float straight_turn_scale      = 0.6F;
    float max_target_yaw_rate      = 1.5F;

    // yaw-rate 内环 PI，只修正 target_yaw，不直接改 guide_error。
    float yaw_kp                   = 1.0F;
    float yaw_ki                   = 0.0F;
    float max_yaw_rate_correction  = 0.12F;

    // 反馈滤波。rps_filter_alpha 应在 0~1，yaw_rate_filter_window 应为正数。
    float rps_filter_alpha         = 0.5F;
    int   yaw_rate_filter_window   = 7;

    // 控制层 duty 输出上限；drive_output.cpp 里仍有 35% 硬件安全上限。
    int   max_duty_percent         = 35;
};

// 启动时调用一次；找不到文件时打印警告并保留默认值。
bool load_control_config(const char *path);

// 控制环读全局参数；load 之前调用返回默认值。
const control_config_t &control_config();
