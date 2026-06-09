#include <cstdio>
#include <cstring>

#include "types.hpp"
#include "tracking/imgproc.hpp"

namespace
{
void fail(const char *name, int actual, int expected, int *failed)
{
    std::fprintf(stderr, "FAIL: %s actual=%d expected=%d\n", name, actual, expected);
    *failed = 1;
}

void expect_eq(const char *name, int actual, int expected, int *failed)
{
    if(actual != expected)
    {
        fail(name, actual, expected, failed);
    }
}

void fill_white_lane(uint8_t gray[RAW_H][RAW_W], int x0, int y0, int x1, int y1)
{
    std::memset(gray, 0, RAW_H * RAW_W);
    for(int y = y0; y <= y1; ++y)
    {
        for(int x = x0; x <= x1; ++x)
        {
            gray[y][x] = 255;
        }
    }
}

int trace_stays_on_white(const uint8_t gray[RAW_H][RAW_W], const trace_t *trace)
{
    if(trace == nullptr || trace->step <= 0)
    {
        return 0;
    }
    for(int i = 0; i < trace->step; ++i)
    {
        const point_t p = trace->pts[i];
        if(p.x < 0 || p.x >= RAW_W || p.y < 0 || p.y >= RAW_H)
        {
            return 0;
        }
        if(gray[p.y][p.x] == 0)
        {
            return 0;
        }
    }
    return 1;
}

int trace_first_run_goes_up_near_x(const trace_t *trace, int expected_x, int tolerance)
{
    if(trace == nullptr || trace->step < 20)
    {
        return 0;
    }
    const int limit = trace->step < 30 ? trace->step : 30;
    for(int i = 0; i < limit; ++i)
    {
        const int dx = trace->pts[i].x - expected_x;
        if(dx < -tolerance || dx > tolerance)
        {
            return 0;
        }
    }
    return trace->pts[limit - 1].y < trace->pts[0].y;
}

int run_trace_direction_contract()
{
    int failed = 0;
    uint8_t gray[RAW_H][RAW_W] = {};
    fill_white_lane(gray, 40, 10, 120, 110);

    trace_t left = {};
    expect_eq("left trace publish",
              trace_single(gray, {40, 90}, 1, &left),
              1,
              &failed);
    expect_eq("left trace side", left.left_side, 1, &failed);
    expect_eq("left trace first run",
              trace_first_run_goes_up_near_x(&left, 40, 1),
              1,
              &failed);
    expect_eq("left trace white",
              trace_stays_on_white(gray, &left),
              1,
              &failed);

    trace_t right = {};
    expect_eq("right trace publish",
              trace_single(gray, {120, 90}, 0, &right),
              1,
              &failed);
    expect_eq("right trace side", right.left_side, 0, &failed);
    expect_eq("right trace first run",
              trace_first_run_goes_up_near_x(&right, 120, 1),
              1,
              &failed);
    expect_eq("right trace white",
              trace_stays_on_white(gray, &right),
              1,
              &failed);
    return failed;
}

int run_seed_to_trace_contract()
{
    int failed = 0;
    uint8_t gray[RAW_H][RAW_W] = {};
    fill_white_lane(gray, 40, 10, 120, 110);

    int search_center = 80;
    int state = 0;
    seed_pair_t seeds = {};
    expect_eq("seed base publish",
              find_seeds(gray, 90, &search_center, &state, &seeds),
              1,
              &failed);
    expect_eq("seed base state", state, 3, &failed);
    expect_eq("seed base left x", seeds.left.x, 40, &failed);
    expect_eq("seed base left y", seeds.left.y, 90, &failed);
    expect_eq("seed base right x", seeds.right.x, 120, &failed);
    expect_eq("seed base right y", seeds.right.y, 90, &failed);
    expect_eq("seed pair accepted", seed_pair_accepted(&seeds, state), 1, &failed);

    trace_t left = {};
    trace_t right = {};
    expect_eq("seed left trace",
              trace_single(gray, seeds.left, 1, &left),
              1,
              &failed);
    expect_eq("seed right trace",
              trace_single(gray, seeds.right, 0, &right),
              1,
              &failed);
    expect_eq("seed left trace white", trace_stays_on_white(gray, &left), 1, &failed);
    expect_eq("seed right trace white", trace_stays_on_white(gray, &right), 1, &failed);
    return failed;
}
}

int main()
{
    int failed = 0;
    failed |= run_seed_to_trace_contract();
    failed |= run_trace_direction_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("line_trace_contract_test: ok");
    return 0;
}
