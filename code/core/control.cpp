#include "control.hpp"

#include "config.hpp"
#include "clip.hpp"

#include <cmath>

// 控制主链按实车闭环顺序展开：
//
// 1. 安全入口：停车线、无有效线时清状态并禁止输出。
// 2. 目标速度：普通巡线用 target_rps，十字/环岛内用 element_target_rps。
// 3. 反馈预处理：编码器 count -> 左右轮 rps；IMU yaw-rate -> yaw_now。
// 4. 视觉外环：control_input_t.guide_error -> target_yaw。
// 5. yaw-rate 内环：target_yaw + yaw_now -> yaw_cmd。
// 6. 差速运动学：center_rps + yaw_cmd -> target_l / target_r。
// 7. 轮速环：target_l/r + encoder rps -> left/right duty。
//
// 本文件不是单一 PID。视觉外环、yaw-rate 内环、左右轮速度环分别解释和调参。
// 参数来自 /root/front_car_mainline.yaml；缺文件时使用 config.hpp 默认值。

namespace
{
const float k_counts_per_rev = 1024.0F * 4.0F; // 每转编码器计数：1024 线 x 4 倍频
const float k_pi = 3.14159265358979323846F;
const float k_speed_i_max = 20.0F;             // 轮速 PI 积分项限幅，抗饱和
const float k_yaw_i_max = 2.0F;                // yaw-rate PI 积分项限幅，抗饱和
const int k_yaw_window_max = 32;               // yaw-rate 滑动平均窗口的硬上限（缓冲长度）

// 控制环跨帧状态。无线、停车线、无有效线时统一清零，避免旧积分继续影响下一段。
float g_left_i = 0.0F;
float g_right_i = 0.0F;
float g_yaw_i = 0.0F;
float g_last_target_yaw = 0.0F;
float g_last_err = 0.0F;
int g_has_err = 0;
float g_left_rps = 0.0F;
float g_right_rps = 0.0F;
int g_rps_ready = 0;
float g_yaw_buf[k_yaw_window_max] = {};
int g_yaw_num = 0;
int g_yaw_pos = 0;

// 清掉左右轮积分、yaw 积分、上一帧视觉误差、轮速低通和 yaw-rate 平均窗口。
// 主链失效、停车线触发时调用，避免旧积分继续影响下一段赛道。
void clear_state()
{
    g_left_i = 0.0F;
    g_right_i = 0.0F;
    g_yaw_i = 0.0F;
    g_last_target_yaw = 0.0F;
    g_last_err = 0.0F;
    g_has_err = 0;
    g_left_rps = 0.0F;
    g_right_rps = 0.0F;
    g_rps_ready = 0;
    g_yaw_num = 0;
    g_yaw_pos = 0;
    for(int i = 0; i < k_yaw_window_max; ++i)
    {
        g_yaw_buf[i] = 0.0F;
    }
}

// 浮点四舍五入到最近整数，用于把 rps/yaw 等浮点量转成上报和 duty 用的整型。
int round_i32(float v)
{
    return static_cast<int>(std::lround(v));
}

// 只做浮点限幅，不负责参数合法性检查。
float clip_f(float v, float minv, float maxv)
{
    if(v < minv)
    {
        return minv;
    }
    if(v > maxv)
    {
        return maxv;
    }
    return v;
}

// 将一个控制周期内的编码器增量换算为轮速 rps。
// 编码器方向已在 drive_output.cpp 修正；这里只做单位换算，不做滤波。
float count_to_rps(int cnt, int ms)
{
    if(ms <= 0)
    {
        ms = 10;
    }
    return static_cast<float>(cnt) / k_counts_per_rev * 1000.0F / static_cast<float>(ms);
}

float abs_f(float v)
{
    return v < 0.0F ? -v : v;
}

int sign_f(float v)
{
    return v < 0.0F ? -1 : 1;
}

// 对 IMU yaw-rate 做滑动平均；单位 rad/s。g_yaw_buf 是环形缓冲，g_yaw_pos 写满 window 后回绕。
float yaw_avg(float yaw, int window)
{
    window = clip_i(window, 1, k_yaw_window_max);
    g_yaw_buf[g_yaw_pos] = yaw;
    g_yaw_pos++;
    if(g_yaw_pos >= window)
    {
        g_yaw_pos = 0;
    }
    if(g_yaw_num < window)
    {
        g_yaw_num++;
    }

    float sum = 0.0F;
    for(int i = 0; i < g_yaw_num; ++i)
    {
        sum += g_yaw_buf[i];
    }
    return sum / static_cast<float>(g_yaw_num);
}

void solve(const control_input_t *input, const control_feedback_t *fb, control_state_t *out)
{
    *out = {};
    if(fb != nullptr)
    {
        out->actual_yaw_rate_mrad_s = fb->actual_yaw_rate_mrad_s;
    }

    if(input == nullptr)
    {
        clear_state();
        return;
    }
    if(input->stop_line)
    {
        clear_state();
        out->stop_request = 1;
        return;
    }
    if(!input->line_found)
    {
        clear_state();
        return;
    }

    out->input_valid = 1;

    const control_config_t &c = control_config();
    // control_period_ms 必须 >0。实车入口通常由 runners.cpp 限制到 1~100ms；
    // 若 yaml 写成非法值，这里不做兜底修正，只保留当前代码路径，风险在最终摘要中说明。
    int ms = c.control_period_ms;
    if(fb != nullptr && fb->period_ms > 0)
    {
        ms = fb->period_ms;
    }
    const float dt = static_cast<float>(ms) / 1000.0F;

    // 元素内降速：
    // 输入：input->element_active。
    // 输出：center_rps。
    // 控制类型：速度目标切换，不是 PID。
    // 主要参数：target_rps 普通巡线速度；element_target_rps 十字/环岛速度。
    // 调参风险：element_target_rps 太高会导致元素内来不及转向，太低会影响通过连续性。
    float center_rps = c.target_rps;
    if(input->element_active)
    {
        center_rps = c.element_target_rps;
    }
    if(input->spin_mode)
    {
        center_rps = 0.0F;
    }

    // 1. 编码器反馈：count -> rps -> 低通
    //
    // 输入：fb->left_speed_count / fb->right_speed_count。
    // 输出：g_left_rps / g_right_rps。
    // 控制类型：反馈预处理，不是 PID。
    // 主要参数：rps_filter_alpha，范围应为 0~1；越大越跟手，越小越平滑。
    // 调参风险：超出 0~1 会放大或反向反馈；滤波太重会让轮速 PI 反应慢。
    // 注意：编码器左右和方向已在 drive_output.cpp 修正，本阶段不再处理硬件映射。
    int cnt_l = 0;
    int cnt_r = 0;
    if(fb != nullptr)
    {
        cnt_l = fb->left_speed_count;
        cnt_r = fb->right_speed_count;
    }

    const float raw_l = count_to_rps(cnt_l, ms);
    const float raw_r = count_to_rps(cnt_r, ms);
    if(!g_rps_ready)
    {
        g_left_rps = raw_l;
        g_right_rps = raw_r;
        g_rps_ready = 1;
    }
    else
    {
        g_left_rps = c.rps_filter_alpha * raw_l + (1.0F - c.rps_filter_alpha) * g_left_rps;
        g_right_rps = c.rps_filter_alpha * raw_r + (1.0F - c.rps_filter_alpha) * g_right_rps;
    }

    // 2. IMU yaw rate 反馈
    //
    // 输入：fb->actual_yaw_rate_mrad_s / fb->actual_yaw_rate_valid。
    // 输出：yaw_now。
    // 控制类型：yaw-rate 反馈预处理，不是 PID。
    // 主要参数：yaw_rate_filter_window；窗口越大越稳，反馈越慢。
    // 调参风险：IMU 方向或比例未验证时，后面的 yaw-rate 内环可能把车拖偏。
    // 注意：actual_yaw_rate_mrad_s 是 rad/s * 1000。
    float raw_yaw = 0.0F;
    if(fb != nullptr)
    {
        raw_yaw = static_cast<float>(fb->actual_yaw_rate_mrad_s) / 1000.0F;
    }
    const float yaw_now = yaw_avg(raw_yaw, c.yaw_rate_filter_window);

    // 3. 视觉外环：guide_error -> target_yaw
    //
    // 输入：control_input_t.guide_error，中线预瞄误差。
    // 输出：target_yaw，视觉外环给出的目标 yaw-rate。
    // 控制类型：PD；outer_kp 管转向强度，outer_kd 管误差变化率。
    // 主要参数：
    //   outer_kp 转向强度；
    //   outer_kd 默认可为 0，图像误差抖动时不要轻易打开；
    //   outer_sign 修正图像误差和车体 yaw 方向；
    //   straight_error_threshold / straight_turn_scale 抑制直道小摆动；
    //   max_target_yaw_rate 限制视觉外环最大目标角速度。
    // 调参风险：outer_kp 太大容易蛇形；outer_sign 反了会越修越偏；outer_kd 会放大视觉抖动。
    float target_yaw = 0.0F;
    if(input->fixed_yaw_rate_valid)
    {
        target_yaw = static_cast<float>(input->fixed_yaw_rate_mrad_s) / 1000.0F;
        g_last_err = 0.0F;
        g_has_err = 0;
    }
    else
    {
        const float err = static_cast<float>(input->guide_error);
        float derr = 0.0F;
        if(g_has_err && dt > 0.0F)
        {
            derr = (err - g_last_err) / dt;
        }
        g_last_err = err;
        g_has_err = 1;

        target_yaw = c.outer_kp * err + c.outer_kd * derr;
        target_yaw *= c.outer_sign;
        if(!input->element_active && std::fabs(err) < c.straight_error_threshold)
        {
            target_yaw *= c.straight_turn_scale;
        }
    }
    target_yaw = clip_f(target_yaw, -c.max_target_yaw_rate, c.max_target_yaw_rate);

    // 弯道按转向幅度连续降速：直道(|target_yaw|≈0)≈满速，弯越急越慢，预瞄可提前刹。
    // 仅普通巡线生效：element_active 时 center_rps 已是元素速度；fixed_yaw_rate_valid 时
    // target_yaw 是指定值(含 spin)，都不缩。curve_speed_slowdown=0 时行为与原版一致。
    if(!input->element_active && !input->fixed_yaw_rate_valid &&
       c.curve_speed_slowdown > 0.0F && c.max_target_yaw_rate > 0.0F)
    {
        const float curve_ratio = clip_f(abs_f(target_yaw) / c.max_target_yaw_rate, 0.0F, 1.0F);
        center_rps *= 1.0F - c.curve_speed_slowdown * curve_ratio;
    }

    // 4. yaw-rate 内环修正：target_yaw -> yaw_cmd
    //
    // 输入：target_yaw 和 yaw_now。
    // 输出：yaw_cmd，给差速运动学使用的实际转向命令。
    // 控制类型：yaw-rate PI；只修正角速度，不直接改 guide_error。
    // 主要参数：
    //   imu_yaw_feedback_enabled 未验证 IMU 方向/比例前可以关为 0；
    //   yaw_kp 管角速度误差；
    //   yaw_ki 管长期 yaw-rate 偏差；
    //   max_yaw_rate_correction 限制 IMU 内环最多能补多少。
    // 调参风险：IMU 方向、比例或延迟不对时，内环会和视觉外环打架；先小 correction 再放大。
    int yaw_fb_ok = 0;
    if(fb != nullptr && fb->actual_yaw_rate_valid)
    {
        yaw_fb_ok = 1;
    }

    float yaw_cmd = target_yaw;
    if(!yaw_fb_ok || !c.imu_yaw_feedback_enabled || c.max_yaw_rate_correction <= 0.0F)
    {
        g_yaw_i = 0.0F;
        g_last_target_yaw = target_yaw;
    }
    else
    {
        if(target_yaw == 0.0F || g_last_target_yaw * target_yaw < 0.0F)
        {
            g_yaw_i = 0.0F;
        }
        g_last_target_yaw = target_yaw;

        const float yaw_err = target_yaw - yaw_now;
        const float yaw_i1 = clip_f(g_yaw_i + yaw_err * dt, -k_yaw_i_max, k_yaw_i_max);
        const float yaw_u1 = c.yaw_kp * yaw_err + c.yaw_ki * yaw_i1;

        int hold_i = 0;
        if(yaw_u1 > c.max_yaw_rate_correction && yaw_err > 0.0F)
        {
            hold_i = 1;
        }
        if(yaw_u1 < -c.max_yaw_rate_correction && yaw_err < 0.0F)
        {
            hold_i = 1;
        }
        if(!hold_i)
        {
            g_yaw_i = yaw_i1;
        }

        float corr = c.yaw_kp * yaw_err + c.yaw_ki * g_yaw_i;
        corr = clip_f(corr, -c.max_yaw_rate_correction, c.max_yaw_rate_correction);
        yaw_cmd = clip_f(target_yaw + corr, -c.max_target_yaw_rate, c.max_target_yaw_rate);
    }

    // 5. 差速运动学：yaw_cmd -> left/right target rps
    //
    // 输入：center_rps 和 yaw_cmd。
    // 输出：target_l / target_r，左右轮目标转速。
    // 控制类型：运动学换算，不是 PID。
    // 主要参数：wheel_track_m 左右轮距；encoder_gear_diameter_m 编码轮直径。
    // 调参风险：轮距或轮径不准，会导致同样 yaw_cmd 下左右轮差速比例不准。
    // 注意：yaw_cmd > 0 时右轮目标更高、左轮目标更低；具体 PWM 映射在 drive_output.cpp。
    const float circ = k_pi * c.encoder_gear_diameter_m;
    const float center_mps = center_rps * circ;
    const float diff_mps = yaw_cmd * c.wheel_track_m * 0.5F;
    float target_l = (center_mps - diff_mps) / circ;
    float target_r = (center_mps + diff_mps) / circ;
    const int element_reverse_brake = clip_i(c.element_reverse_brake_percent, 0, c.max_duty_percent);
    if(input->spin_mode || (input->element_active && element_reverse_brake > 0))
    {
        target_l = clip_f(target_l, -45.0F, 45.0F);
        target_r = clip_f(target_r, -45.0F, 45.0F);
    }
    else
    {
        // 巡线模式不倒车，目标轮速钳到 [0, 45] rps。
        target_l = clip_f(target_l, 0.0F, 45.0F);
        target_r = clip_f(target_r, 0.0F, 45.0F);
    }

    // 6. 左轮 FF+PI：target_l + left encoder rps -> duty_l
    //
    // 输入：target_l 和 g_left_rps。
    // 输出：duty_l。
    // 控制类型：前馈 FF + 速度 PI。
    // 主要参数：
    //   left_speed_base_percent 是前馈基准占空；
    //   left_speed_kp 管当前轮速误差；
    //   left_speed_ki 管长期轮速偏差；
    //   speed_target_rps 是前馈缩放参考；
    //   max_duty_percent 是输出上限。
    // 调参风险：base 太低车起不来，kp 太大轮速抖，ki 太大会慢慢顶到饱和。
    float ff_ref = c.speed_target_rps;
    if(ff_ref <= 1.0F)
    {
        ff_ref = 1.0F;
    }

    float duty_l = 0.0F;
    const float abs_target_l = abs_f(target_l);
    const float signed_actual_l = static_cast<float>(sign_f(target_l)) * g_left_rps;
    if(abs_target_l <= 0.0F)
    {
        g_left_i = 0.0F;
    }
    else
    {
        const float kp = c.left_speed_kp;
        const float ki = c.left_speed_ki;
        const float ff = c.left_speed_base_percent * abs_target_l / ff_ref;
        const float e = abs_target_l - signed_actual_l;
        const float i1 = clip_f(g_left_i + e * dt, -k_speed_i_max, k_speed_i_max);
        const float u1 = ff + kp * e + ki * i1;

        int hold_i = 0;
        if(u1 > static_cast<float>(c.max_duty_percent) && e > 0.0F)
        {
            hold_i = 1;
        }
        if(u1 < 0.0F && e < 0.0F)
        {
            hold_i = 1;
        }
        if(!hold_i)
        {
            g_left_i = i1;
        }
        duty_l = clip_f(ff + kp * e + ki * g_left_i, 0.0F, static_cast<float>(c.max_duty_percent));
        if((input->spin_mode || (input->element_active && element_reverse_brake > 0)) && target_l < 0.0F)
        {
            duty_l = -duty_l;
        }
    }

    // 7. 右轮 FF+PI：target_r + right encoder rps -> duty_r
    //
    // 输入：target_r 和 g_right_rps。
    // 输出：duty_r。
    // 控制类型：前馈 FF + 速度 PI。
    // 主要参数：
    //   right_speed_base_percent 是前馈基准占空；
    //   right_speed_kp 管当前轮速误差；
    //   right_speed_ki 管长期轮速偏差；
    //   speed_target_rps 是前馈缩放参考；
    //   max_duty_percent 是输出上限。
    // 调参风险：右轮参数不要默认照抄左轮；左右机械差异会体现在 base_percent 和 PI 上。
    // 注意：右轮单独一段，不和左轮抽成通用函数，方便现场对比左右参数和日志。
    float duty_r = 0.0F;
    const float abs_target_r = abs_f(target_r);
    const float signed_actual_r = static_cast<float>(sign_f(target_r)) * g_right_rps;
    if(abs_target_r <= 0.0F)
    {
        g_right_i = 0.0F;
    }
    else
    {
        const float kp = c.right_speed_kp;
        const float ki = c.right_speed_ki;
        const float ff = c.right_speed_base_percent * abs_target_r / ff_ref;
        const float e = abs_target_r - signed_actual_r;
        const float i1 = clip_f(g_right_i + e * dt, -k_speed_i_max, k_speed_i_max);
        const float u1 = ff + kp * e + ki * i1;

        int hold_i = 0;
        if(u1 > static_cast<float>(c.max_duty_percent) && e > 0.0F)
        {
            hold_i = 1;
        }
        if(u1 < 0.0F && e < 0.0F)
        {
            hold_i = 1;
        }
        if(!hold_i)
        {
            g_right_i = i1;
        }
        duty_r = clip_f(ff + kp * e + ki * g_right_i, 0.0F, static_cast<float>(c.max_duty_percent));
        if((input->spin_mode || (input->element_active && element_reverse_brake > 0)) && target_r < 0.0F)
        {
            duty_r = -duty_r;
        }
    }

    // 输出给 report / drive_output：
    //   target_yaw_rate_mrad_s 记录视觉外环 target_yaw
    //   actual_yaw_rate_mrad_s 记录滤波后的陀螺反馈
    //   left_duty/right_duty   交给 drive_output.cpp 做 PWM 硬件映射
    out->target_yaw_rate_mrad_s = round_i32(target_yaw * 1000.0F);
    out->yaw_cmd_mrad_s = round_i32(yaw_cmd * 1000.0F);
    out->actual_yaw_rate_mrad_s = round_i32(yaw_now * 1000.0F);
    out->left_target_rps_milli = round_i32(target_l * 1000.0F);
    out->right_target_rps_milli = round_i32(target_r * 1000.0F);
    out->left_actual_rps_milli = round_i32(g_left_rps * 1000.0F);
    out->right_actual_rps_milli = round_i32(g_right_rps * 1000.0F);
    out->signed_output = (input->spin_mode || (input->element_active && element_reverse_brake > 0)) ? 1 : 0;
    if(out->signed_output)
    {
        const int reverse_limit = input->spin_mode ? c.max_duty_percent : element_reverse_brake;
        out->left_duty = clip_i(round_i32(duty_l), -reverse_limit, c.max_duty_percent);
        out->right_duty = clip_i(round_i32(duty_r), -reverse_limit, c.max_duty_percent);
    }
    else
    {
        out->left_duty = clip_i(round_i32(duty_l), 0, c.max_duty_percent);
        out->right_duty = clip_i(round_i32(duty_r), 0, c.max_duty_percent);
    }
}

} // namespace

void solve_control_input(const control_input_t *input, control_state_t *ctrl)
{
    if(input == nullptr || ctrl == nullptr)
    {
        return;
    }

    control_feedback_t fb = {};
    fb.period_ms = control_config().control_period_ms;
    solve(input, &fb, ctrl);
}

void solve_control_input_with_feedback(const control_input_t *input,
                                       const control_feedback_t *fb,
                                       control_state_t *ctrl)
{
    if(input == nullptr || ctrl == nullptr)
    {
        return;
    }
    solve(input, fb, ctrl);
}
