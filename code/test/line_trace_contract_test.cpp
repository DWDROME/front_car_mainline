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

void draw_white_segment(uint8_t gray[RAW_H][RAW_W], point_t a, point_t b)
{
    const int dx = b.x - a.x;
    const int dy = b.y - a.y;
    int n = dx < 0 ? -dx : dx;
    if(dy < 0 && -dy > n)
    {
        n = -dy;
    }
    else if(dy > 0 && dy > n)
    {
        n = dy;
    }
    if(n <= 0)
    {
        if(a.x >= 0 && a.x < RAW_W && a.y >= 0 && a.y < RAW_H)
        {
            gray[a.y][a.x] = 255;
        }
        return;
    }

    for(int i = 0; i <= n; ++i)
    {
        const int x = a.x + dx * i / n;
        const int y = a.y + dy * i / n;
        if(x >= 0 && x < RAW_W && y >= 0 && y < RAW_H)
        {
            gray[y][x] = 255;
        }
    }
}

void fill_left_down_bend(uint8_t gray[RAW_H][RAW_W])
{
    std::memset(gray, 0, RAW_H * RAW_W);
    draw_white_segment(gray, {40, 100}, {40, 50});
    draw_white_segment(gray, {40, 50}, {80, 50});
    draw_white_segment(gray, {80, 50}, {80, 86});
}

void fill_right_down_bend(uint8_t gray[RAW_H][RAW_W])
{
    std::memset(gray, 0, RAW_H * RAW_W);
    draw_white_segment(gray, {120, 100}, {120, 50});
    draw_white_segment(gray, {120, 50}, {80, 50});
    draw_white_segment(gray, {80, 50}, {80, 86});
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

int trace_turns_down_after_up(const trace_t *trace, int min_down_gain)
{
    if(trace == nullptr || trace->step < 30)
    {
        return 0;
    }

    int min_y = RAW_H;
    int min_i = -1;
    for(int i = 0; i < trace->step; ++i)
    {
        if(trace->pts[i].y < min_y)
        {
            min_y = trace->pts[i].y;
            min_i = i;
        }
    }
    if(min_i < 0)
    {
        return 0;
    }

    for(int i = min_i + 1; i < trace->step; ++i)
    {
        if(trace->pts[i].y >= min_y + min_down_gain)
        {
            return 1;
        }
    }
    return 0;
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

int run_down_bend_contract()
{
    int failed = 0;
    uint8_t gray[RAW_H][RAW_W] = {};

    fill_left_down_bend(gray);
    trace_t left = {};
    expect_eq("left down bend publish",
              trace_single(gray, {40, 100}, 1, &left),
              1,
              &failed);
    expect_eq("left down bend white", trace_stays_on_white(gray, &left), 1, &failed);
    expect_eq("left down bend after up",
              trace_turns_down_after_up(&left, 20),
              1,
              &failed);

    fill_right_down_bend(gray);
    trace_t right = {};
    expect_eq("right down bend publish",
              trace_single(gray, {120, 100}, 0, &right),
              1,
              &failed);
    expect_eq("right down bend white", trace_stays_on_white(gray, &right), 1, &failed);
    expect_eq("right down bend after up",
              trace_turns_down_after_up(&right, 20),
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

int run_region_otsu_contract()
{
    int failed = 0;
    uint8_t gray[RAW_H][RAW_W] = {};
    std::memset(gray, 240, RAW_H * RAW_W);

    // Calvariaa/RT1064-Code PR #6 把 OTSU 改成区域接口；外部亮区不能污染目标区域。
    for(int y = 20; y <= 29; ++y)
    {
        for(int x = 10; x <= 19; ++x)
        {
            gray[y][x] = 40;
        }
    }
    expect_eq("region otsu constant rect", region_otsu(gray, 10, 19, 20, 29), 40, &failed);
    expect_eq("region otsu swapped rect", region_otsu(gray, 19, 10, 29, 20), 40, &failed);

    for(int y = 40; y <= 49; ++y)
    {
        for(int x = 30; x <= 34; ++x)
        {
            gray[y][x] = 30;
        }
        for(int x = 35; x <= 39; ++x)
        {
            gray[y][x] = 220;
        }
    }
    expect_eq("region otsu bimodal rect", region_otsu(gray, 30, 39, 40, 49), 30, &failed);
    return failed;
}
}

int main()
{
    int failed = 0;
    failed |= run_region_otsu_contract();
    failed |= run_seed_to_trace_contract();
    failed |= run_trace_direction_contract();
    failed |= run_down_bend_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("line_trace_contract_test: ok");
    return 0;
}
