#pragma once

#include <cstdint>

struct live_profile_t
{
    int enabled;
    int divider;
    uint32_t frames;
    uint64_t total_us;
    uint64_t capture_us;
    uint64_t pts_us;
    uint64_t feedback_us;
    uint64_t control_us;
    uint64_t drive_us;
    uint64_t print_us;
};

uint64_t monotonic_us();
void profile_add(uint64_t *bucket, uint64_t t0, uint64_t t1);
double avg_ms(uint64_t us, uint32_t frames);
int frame_period_us_from_fps(int fps);
void sleep_remaining_frame_time(uint64_t t0, int period_us);
int live_control_period_ms();
void profile_report_and_reset(live_profile_t *prof);
