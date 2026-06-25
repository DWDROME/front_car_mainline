#include "app/live_profile.hpp"

#include "core/config.hpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <unistd.h>

uint64_t monotonic_us()
{
    using clock = std::chrono::steady_clock;
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(clock::now().time_since_epoch()).count());
}

void profile_add(uint64_t *bucket, uint64_t t0, uint64_t t1)
{
    if(bucket != nullptr && t1 >= t0)
    {
        *bucket += t1 - t0;
    }
}

double avg_ms(uint64_t us, uint32_t frames)
{
    if(frames == 0U)
    {
        return 0.0;
    }
    return static_cast<double>(us) / static_cast<double>(frames) / 1000.0;
}

int frame_period_us_from_fps(int fps)
{
    if(fps <= 0)
    {
        return 0;
    }
    return 1000000 / fps;
}

void sleep_remaining_frame_time(uint64_t t0, int period_us)
{
    if(period_us <= 0)
    {
        return;
    }

    const uint64_t now = monotonic_us();
    const uint64_t used = now >= t0 ? now - t0 : 0;
    if(used < static_cast<uint64_t>(period_us))
    {
        usleep(static_cast<useconds_t>(period_us - used));
    }
}

int live_control_period_ms()
{
    const int ms = control_config().control_period_ms;
    if(ms < 1)
    {
        std::printf("ConfigWarn: control_period_ms=%d below live range, using 1\n", ms);
        return 1;
    }
    if(ms > 100)
    {
        std::printf("ConfigWarn: control_period_ms=%d above live range, using 100\n", ms);
        return 100;
    }
    return ms;
}

void profile_report_and_reset(live_profile_t *prof)
{
    if(prof == nullptr || !prof->enabled || prof->frames < static_cast<uint32_t>(prof->divider))
    {
        return;
    }

    const uint32_t num = prof->frames;
    std::printf("profile frames=%u avg_ms total=%.2f capture=%.2f pts=%.2f feedback=%.2f "
                "control=%.2f drive=%.2f print=%.2f\n",
                num,
                avg_ms(prof->total_us, num),
                avg_ms(prof->capture_us, num),
                avg_ms(prof->pts_us, num),
                avg_ms(prof->feedback_us, num),
                avg_ms(prof->control_us, num),
                avg_ms(prof->drive_us, num),
                avg_ms(prof->print_us, num));
    std::fflush(stdout);

    prof->frames = 0;
    prof->total_us = 0;
    prof->capture_us = 0;
    prof->pts_us = 0;
    prof->feedback_us = 0;
    prof->control_us = 0;
    prof->drive_us = 0;
    prof->print_us = 0;
}
