#include "zf_driver_delay.hpp"
#include "zf_driver_encoder.hpp"
#include "zf_driver_gpio.hpp"
#include "zf_driver_pwm.hpp"

#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>

namespace
{
// 当前硬件合同与 drive_output.cpp 保持一致：
//   encoder: QUAD1 = left, QUAD2 = right
//   motor:   left  -> PWM2, right -> PWM1
//   forward: direction level = 0
constexpr int k_max_pulse_percent = 35;
constexpr int k_max_pulse_duration_ms = 10000;
constexpr int k_motor_forward_level = 0;
constexpr int k_encoder_left_sign = -1;
constexpr int k_encoder_right_sign = 1;

struct motor_pulse_args_t
{
    int left_percent;
    int right_percent;
    int duration_ms;
};

bool parse_int_arg(const char *text, int *out)
{
    if(text == nullptr || text[0] == '\0' || out == nullptr)
    {
        return false;
    }

    errno = 0;
    char *end = nullptr;
    const long parsed = std::strtol(text, &end, 10);
    if(end == text || *end != '\0' || errno != 0 || parsed < INT_MIN || parsed > INT_MAX)
    {
        return false;
    }

    *out = static_cast<int>(parsed);
    return true;
}

void print_usage(const char *name)
{
    std::printf("Usage: %s <left_percent> <right_percent> <duration_ms>\n", name);
    std::printf("  left/right percent are clamped to [0, %d]\n", k_max_pulse_percent);
    std::printf("  duration_ms is clamped to [0, %d]\n", k_max_pulse_duration_ms);
}

bool parse_args(int argc, char **argv, motor_pulse_args_t *args)
{
    if(args == nullptr)
    {
        return false;
    }

    if(argc == 2 && (std::strcmp(argv[1], "--help") == 0 || std::strcmp(argv[1], "-h") == 0))
    {
        print_usage(argv[0]);
        return false;
    }

    if(argc != 4 ||
       !parse_int_arg(argv[1], &args->left_percent) ||
       !parse_int_arg(argv[2], &args->right_percent) ||
       !parse_int_arg(argv[3], &args->duration_ms))
    {
        print_usage(argv[0]);
        return false;
    }

    return true;
}

uint16_t percent_to_duty(zf_driver_pwm &pwm, int percent)
{
    percent = std::clamp(percent, 0, k_max_pulse_percent);
    pwm_info info = {};
    pwm.get_dev_info(&info);
    return static_cast<uint16_t>(static_cast<uint32_t>(info.duty_max) *
                                 static_cast<uint32_t>(percent) / 100U);
}

int run_motor_pulse(const motor_pulse_args_t &args)
{
    const int left_percent = std::clamp(args.left_percent, 0, k_max_pulse_percent);
    const int right_percent = std::clamp(args.right_percent, 0, k_max_pulse_percent);
    const int duration_ms = std::clamp(args.duration_ms, 0, k_max_pulse_duration_ms);

    zf_driver_gpio motor_dir_1(ZF_GPIO_MOTOR_1, O_RDWR);
    zf_driver_gpio motor_dir_2(ZF_GPIO_MOTOR_2, O_RDWR);
    zf_driver_pwm motor_pwm_1(ZF_PWM_MOTOR_1);
    zf_driver_pwm motor_pwm_2(ZF_PWM_MOTOR_2);
    zf_driver_encoder encoder_left(ZF_ENCODER_QUAD_1);
    zf_driver_encoder encoder_right(ZF_ENCODER_QUAD_2);

    std::printf("MotorPulse: left=%d right=%d duration_ms=%d max_percent=%d\n",
                left_percent,
                right_percent,
                duration_ms,
                k_max_pulse_percent);

    encoder_left.clear_count();
    encoder_right.clear_count();
    motor_dir_1.set_level(k_motor_forward_level);
    motor_dir_2.set_level(k_motor_forward_level);
    motor_pwm_2.set_duty(percent_to_duty(motor_pwm_2, left_percent));
    motor_pwm_1.set_duty(percent_to_duty(motor_pwm_1, right_percent));

    system_delay_ms(duration_ms);
    motor_pwm_1.set_duty(0);
    motor_pwm_2.set_duty(0);
    system_delay_ms(50);

    const int raw_left = static_cast<int>(encoder_left.get_count());
    const int raw_right = static_cast<int>(encoder_right.get_count());
    std::printf("EncoderPulse: raw_left=%d raw_right=%d norm_left=%d norm_right=%d\n",
                raw_left,
                raw_right,
                raw_left * k_encoder_left_sign,
                raw_right * k_encoder_right_sign);
    return 0;
}
}

int main(int argc, char **argv)
{
    motor_pulse_args_t args = {};
    if(!parse_args(argc, argv, &args))
    {
        return argc == 2 ? 0 : 2;
    }

    return run_motor_pulse(args);
}
