#include "motor_pulse.hpp"

#include "clip.hpp"
#include "zf_common_typedef.hpp"
#include "zf_driver_delay.hpp"
#include "zf_driver_encoder.hpp"
#include "zf_driver_gpio.hpp"
#include "zf_driver_pwm.hpp"

#include <cstdio>
#include <fcntl.h>

namespace
{
// 当前硬件合同与 drive_output.cpp 保持一致：
//   encoder: QUAD1 = left, QUAD2 = right
//   motor:   left  -> PWM2, right -> PWM1
//   forward: direction level = 0
constexpr int k_max_pulse_percent = 35;        // 诊断占空硬上限(%)，与 drive_output 的 35% 安全上限一致
constexpr int k_max_pulse_duration_ms = 10000; // 单次脉冲最长时长(ms)，防止误触发后电机长时间狂转
constexpr int k_motor_forward_level = 0;       // 方向 GPIO 的前进电平
constexpr int k_encoder_left_sign = -1;        // 左编码器方向修正符号（与 drive_output 保持一致）
constexpr int k_encoder_right_sign = 1;        // 右编码器方向修正符号

zf_driver_gpio g_motor_dir_1(ZF_GPIO_MOTOR_1, O_RDWR);
zf_driver_gpio g_motor_dir_2(ZF_GPIO_MOTOR_2, O_RDWR);
zf_driver_pwm g_motor_pwm_1(ZF_PWM_MOTOR_1);
zf_driver_pwm g_motor_pwm_2(ZF_PWM_MOTOR_2);
zf_driver_encoder g_encoder_left(ZF_ENCODER_QUAD_1);
zf_driver_encoder g_encoder_right(ZF_ENCODER_QUAD_2);

// 百分比 -> PWM 原始 duty，钳到 35% 硬上限。这里和 drive_output.cpp 同名函数是有意复制：
// 诊断工具独立编译、不与控制主链共用实现；两处硬件合同需同步维护。
uint16_t percent_to_duty(zf_driver_pwm &pwm, int percent)
{
    percent = clip_i(percent, 0, k_max_pulse_percent);
    pwm_info info = {};
    pwm.get_dev_info(&info);
    return static_cast<uint16_t>(static_cast<uint32_t>(info.duty_max) *
                                 static_cast<uint32_t>(percent) / 100U);
}

// 两路 PWM 置 0，停转。
void motor_stop()
{
    g_motor_pwm_1.set_duty(0);
    g_motor_pwm_2.set_duty(0);
}

// 两路方向 GPIO 置前进电平。
void motor_forward()
{
    g_motor_dir_1.set_level(k_motor_forward_level);
    g_motor_dir_2.set_level(k_motor_forward_level);
}

// 清零左右编码器计数。
void encoder_clear()
{
    g_encoder_left.clear_count();
    g_encoder_right.clear_count();
}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      开环诊断：按给定左右占空驱动电机一段时间，再打印编码器原始/归一化计数
//  @param      left_percent   左轮占空(%)，会被钳到 [0, 35]
//  @param      right_percent  右轮占空(%)，会被钳到 [0, 35]
//  @param      duration_ms    驱动时长(ms)，会被钳到 [0, 10000]
//  @return     int            固定返回 0
//  @note       时序：清码 -> 置前进方向 -> 下发占空 -> 延时 -> 停车 -> 等 50ms 稳定 -> 读码打印。
//              仅用于验证硬件合同和左右方向，不参与闭环控制。
//-------------------------------------------------------------------------------------------------------------------
int run_motor_pulse(int left_percent, int right_percent, int duration_ms)
{
    int p0 = clip_i(left_percent, 0, k_max_pulse_percent);
    int p1 = clip_i(right_percent, 0, k_max_pulse_percent);
    int ms = clip_i(duration_ms, 0, k_max_pulse_duration_ms);

    std::printf("MotorPulse: left=%d right=%d duration_ms=%d max_percent=%d\n",
                p0,
                p1,
                ms,
                k_max_pulse_percent);
    encoder_clear();
    motor_forward();
    g_motor_pwm_2.set_duty(percent_to_duty(g_motor_pwm_2, p0));
    g_motor_pwm_1.set_duty(percent_to_duty(g_motor_pwm_1, p1));

    system_delay_ms(ms);
    motor_stop();
    system_delay_ms(50);

    const int cnt0 = static_cast<int>(g_encoder_left.get_count());
    const int cnt1 = static_cast<int>(g_encoder_right.get_count());
    std::printf("EncoderPulse: raw_left=%d raw_right=%d norm_left=%d norm_right=%d\n",
                cnt0,
                cnt1,
                cnt0 * k_encoder_left_sign,
                cnt1 * k_encoder_right_sign);
    return 0;
}
