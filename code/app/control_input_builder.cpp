#include "app/control_input_builder.hpp"

#include "app/options.hpp"
#include "clip.hpp"
#include "core/config.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>

extern "C" {
#include "atg_reference_step.h"
#include "headfile.h"
}

namespace
{
constexpr double kEncoderCountsPerRev = 1024.0 * 4.0;
constexpr double kAtgEncoderCountsPerMeter = 5800.0;
constexpr int kCrossHalfRelayDefaultMs = 500;
constexpr int kCrossHalfRelayMaxMs = 3000;

int g_cross_half_relay_frames;
int g_cross_half_relay_timeout_reported;
}

int64_t atg_distance_counts_from_encoder_delta(const control_feedback_t &fb)
{
    const int64_t wheel_delta = (static_cast<int64_t>(fb.left_speed_count) +
                                 static_cast<int64_t>(fb.right_speed_count)) / 2;
    if(wheel_delta == 0)
    {
        return 0;
    }

    const control_config_t &c = control_config();
    const double wheel_m = static_cast<double>(wheel_delta) / kEncoderCountsPerRev *
                           3.14159265358979323846 *
                           static_cast<double>(c.encoder_gear_diameter_m);
    return static_cast<int64_t>(std::llround(wheel_m * kAtgEncoderCountsPerMeter));
}

int cross_half_relay_limit_frames(int period_ms)
{
    const int relay_ms = read_env_int_clamped("FRONT_CAR_CROSS_HALF_RELAY_MS",
                                             kCrossHalfRelayDefaultMs,
                                             0,
                                             kCrossHalfRelayMaxMs);
    if(relay_ms <= 0)
    {
        return 0;
    }
    return (relay_ms + period_ms - 1) / period_ms;
}

void apply_cross_half_relay(control_input_t *input, int line_found)
{
    if(input == nullptr)
    {
        return;
    }
    if(cross_type != CROSS_HALF || line_found)
    {
        g_cross_half_relay_frames = 0;
        g_cross_half_relay_timeout_reported = 0;
        return;
    }

    const int period_ms = clip_i(control_config().control_period_ms, 1, 100);
    const int limit_frames = cross_half_relay_limit_frames(period_ms);
    if(limit_frames <= 0)
    {
        return;
    }

    if(g_cross_half_relay_frames == 0 && !g_cross_half_relay_timeout_reported)
    {
        std::printf("ATGCrossHalfRelay: start limit_frames=%d period_ms=%d\n",
                    limit_frames,
                    period_ms);
    }

    if(g_cross_half_relay_frames >= limit_frames)
    {
        if(!g_cross_half_relay_timeout_reported)
        {
            std::printf("ATGCrossHalfRelay: timeout frames=%d cross_type=%d, stop on no-line\n",
                        g_cross_half_relay_frames,
                        (int)cross_type);
            g_cross_half_relay_timeout_reported = 1;
        }
        return;
    }

    g_cross_half_relay_frames++;
    input->line_found = 1;
    input->stop_line = 0;
    input->element_active = 1;
    input->fixed_yaw_rate_valid = 0;
    input->fixed_yaw_rate_mrad_s = 0;
    input->spin_mode = 0;
    input->guide_error = 0.0;
}

control_input_t control_input_from_current_frame(const runtime_t *rt, int line_found)
{
    control_input_t input = {};
    if(rt == nullptr)
    {
        return input;
    }

    input.line_found = line_found ? 1 : 0;
    input.guide_error = rt->vision.guide_error;
    input.element_active =
        (cross_type != CROSS_NONE ||
         circle_type != CIRCLE_NONE ||
         round_type != ROUND_NONE ||
         yroad_type != YROAD_NONE ||
         ramp_type != RAMP_NONE ||
         garage_type != GARAGE_NONE) ? 1 : 0;
    input.stop_line = 0;

    apply_cross_half_relay(&input, line_found);

    if(read_env_flag("FRONT_CAR_FORCE_LINE", 0))
    {
        input.line_found = 1;
        input.stop_line = 0;
        input.element_active = 0;
        input.guide_error = 0.0;
    }

    const int fixed_yaw_mrad_s = read_env_int("FRONT_CAR_FIXED_YAW_MRAD_S", 0);
    if(fixed_yaw_mrad_s != 0)
    {
        input.line_found = 1;
        input.stop_line = 0;
        input.element_active = 0;
        input.fixed_yaw_rate_valid = 1;
        input.fixed_yaw_rate_mrad_s = fixed_yaw_mrad_s;
        input.guide_error = 0.0;
    }

    const int spin_yaw_mrad_s = read_env_int("FRONT_CAR_SPIN_YAW_MRAD_S", 0);
    if(spin_yaw_mrad_s != 0)
    {
        input.line_found = 1;
        input.stop_line = 0;
        input.element_active = 0;
        input.fixed_yaw_rate_valid = 1;
        input.fixed_yaw_rate_mrad_s = spin_yaw_mrad_s;
        input.spin_mode = 1;
        input.guide_error = 0.0;
    }
    return input;
}
