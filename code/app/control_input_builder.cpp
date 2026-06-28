#include "app/control_input_builder.hpp"

#include "report/options.hpp"
#include "core/config.hpp"

extern "C" {
#include "vision_step.h"
#include "headfile.h"
}

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>

namespace
{
constexpr int kCrossHalfRelayDefaultMs = 500;
constexpr int kCrossHalfRelayMaxMs = 3000;

int g_cross_half_relay_frames;
int g_cross_half_relay_timeout_reported;

}

static void apply_cross_half_relay(control_input_t *input, int line_found)
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

    const int period_ms = std::clamp(control_config().control_period_ms, 1, 100);
    const int relay_ms = read_env_int_clamped("FRONT_CAR_CROSS_HALF_RELAY_MS",
                                             kCrossHalfRelayDefaultMs,
                                             0,
                                             kCrossHalfRelayMaxMs);
    if(relay_ms <= 0)
    {
        return;
    }
    const int limit_frames = (relay_ms + period_ms - 1) / period_ms;
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
                        cross_type);
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
