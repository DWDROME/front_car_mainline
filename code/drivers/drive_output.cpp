#include "drive_output.hpp"

#include "clip.hpp"
#include "config.hpp"
#include "imu_feedback.hpp"
#include "zf_driver_encoder.hpp"
#include "zf_driver_gpio.hpp"
#include "zf_driver_pwm.hpp"

#include <cstdint>
#include <ctime>
#include <fcntl.h>
#include <cmath>

namespace
{
// 当前硬件合同：
//   encoder: QUAD1 = left, QUAD2 = right
//   motor:   left  -> PWM2, right -> PWM1
//   forward: direction level = 0
// 驱动层硬上限。yaml 里的 max_duty_percent 只限制控制输出，不能放开这里的硬件安全边界。
constexpr int kHardwareDutyLimitPercent = 35;
constexpr int kMotorForwardLevel = 0;
constexpr int kEncoderLeftSign = -1;
constexpr int kEncoderRightSign = 1;

zf_driver_gpio g_motor_dir_1(ZF_GPIO_MOTOR_1, O_RDWR);
zf_driver_gpio g_motor_dir_2(ZF_GPIO_MOTOR_2, O_RDWR);
zf_driver_pwm g_motor_pwm_1(ZF_PWM_MOTOR_1);
zf_driver_pwm g_motor_pwm_2(ZF_PWM_MOTOR_2);
zf_driver_encoder g_encoder_left(ZF_ENCODER_QUAD_1);
zf_driver_encoder g_encoder_right(ZF_ENCODER_QUAD_2);

int g_drive_enabled = 0;
int g_imu_ready = 0;
int64_t g_last_feedback_ms = 0;

// 取单调时钟毫秒，用于估算两次读反馈之间的真实控制周期。
int64_t monotonic_ms()
{
    timespec ts = {};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<int64_t>(ts.tv_sec) * 1000LL + static_cast<int64_t>(ts.tv_nsec) / 1000000LL;
}

// 百分比占空 -> PWM 原始 duty 值。先强制钳到 kHardwareDutyLimitPercent(35%) 硬件安全上限：
// 这是独立于 yaml max_duty_percent 的最后一道闸，任何上层算出的占空都不能突破它。
uint16_t percent_to_duty(zf_driver_pwm &pwm, int percent)
{
    percent = clip_i(percent, 0, kHardwareDutyLimitPercent);
    pwm_info info = {};
    pwm.get_dev_info(&info);
    return static_cast<uint16_t>(static_cast<uint32_t>(info.duty_max) *
                                 static_cast<uint32_t>(percent) / 100U);
}

// 两路方向 GPIO 置前进电平(0)；本工程只跑前进，不做倒车。
void set_forward_direction()
{
    g_motor_dir_1.set_level(kMotorForwardLevel);
    g_motor_dir_2.set_level(kMotorForwardLevel);
}

// 清零左右编码器计数，配合"每周期读增量再清零"的用法。
void clear_encoders()
{
    g_encoder_left.clear_count();
    g_encoder_right.clear_count();
}
}

int drive_output_init(int enabled)
{
    g_drive_enabled = enabled ? 1 : 0;
    g_imu_ready = imu_feedback_init(control_config().gyro_raw_to_rad_s) ? 1 : 0;
    g_last_feedback_ms = monotonic_ms();
    set_forward_direction();
    drive_output_stop();
    clear_encoders();
    return g_drive_enabled;
}

void drive_output_stop()
{
    g_motor_pwm_1.set_duty(0);
    g_motor_pwm_2.set_duty(0);
}

void drive_output_read_feedback(control_feedback_t *fb, int period_ms)
{
    if(fb == nullptr)
    {
        return;
    }

    // 用实际经过的毫秒数作控制周期；时钟异常(<=0 或 >1000ms)时回退到传入的标称 period_ms。
    const int64_t now_ms = monotonic_ms();
    int ms = static_cast<int>(now_ms - g_last_feedback_ms);
    if(ms <= 0 || ms > 1000)
    {
        ms = period_ms;
    }
    g_last_feedback_ms = now_ms;

    fb->actual_yaw_rate_mrad_s = 0;
    fb->actual_yaw_rate_valid = 0;
    fb->period_ms = ms;
    if(g_imu_ready)
    {
        gyro_sample_t gy = {};
        if(imu_feedback_read(&gy))
        {
            fb->actual_yaw_rate_mrad_s =
                static_cast<int>(std::lround(gy.rad_s * 1000.0));
            fb->actual_yaw_rate_valid = 1;
        }
    }
    if(!g_drive_enabled)
    {
        fb->left_speed_count = 0;
        fb->right_speed_count = 0;
        return;
    }

    const int cnt0 = static_cast<int>(g_encoder_left.get_count());
    const int cnt1 = static_cast<int>(g_encoder_right.get_count());

    // 编码器方向在此统一修正（左轮取反）；控制层拿到的就是"前进为正"，不要再改符号。
    fb->left_speed_count = cnt0 * kEncoderLeftSign;
    fb->right_speed_count = cnt1 * kEncoderRightSign;
    clear_encoders();
}

void drive_output_apply(const control_state_t *ctrl)
{
    if(!g_drive_enabled)
    {
        return;
    }
    if(ctrl == nullptr || ctrl->stop_request || !ctrl->input_valid)
    {
        drive_output_stop();
        return;
    }

    set_forward_direction();
    // 硬件映射：左轮 -> PWM2，右轮 -> PWM1（与文件头硬件合同一致，勿写反）。
    g_motor_pwm_2.set_duty(percent_to_duty(g_motor_pwm_2, ctrl->left_duty));
    g_motor_pwm_1.set_duty(percent_to_duty(g_motor_pwm_1, ctrl->right_duty));
}
