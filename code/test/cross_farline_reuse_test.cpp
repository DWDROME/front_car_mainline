#include <cstdint>
#include <cstdio>
#include <cstring>

#include "types.hpp"

int cross_farline_test_trace_single(const uint8_t gray[RAW_H][RAW_W],
                                    point_t seed,
                                    int left_side,
                                    trace_t *trace);

// Whitebox test: include the owner file so the anonymous build_cross_farline()
// branch is tested directly without exposing a production-only test hook.
#define trace_single cross_farline_test_trace_single
#include "tracking/cross.cpp"
#undef trace_single

namespace
{
enum
{
    TRACE_SHAPE_L = 0,
    TRACE_SHAPE_STRAIGHT = 1,
    TRACE_SHAPE_FAIL = 2,
};

int g_trace_shape = TRACE_SHAPE_L;

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

void expect_ge(const char *name, int actual, int expected, int *failed)
{
    if(actual < expected)
    {
        std::fprintf(stderr, "FAIL: %s actual=%d expected>=%d\n", name, actual, expected);
        *failed = 1;
    }
}

void fill_far_seed_column(runtime_t *rt)
{
    std::memset(rt->gray, 0, sizeof(rt->gray));
    const int x = k_cross_far_left_x;
    for(int y = 70; y <= k_cross_far_begin_y; ++y)
    {
        rt->gray[y][x] = 255;
    }
}

void push_trace_point(trace_t *trace, int x, int y)
{
    if(trace->step >= POINT_MAX)
    {
        return;
    }
    trace->pts[trace->step] = {x, y};
    trace->stop_point = trace->pts[trace->step];
    ++trace->step;
}

void fill_l_trace(trace_t *trace, point_t seed)
{
    for(int i = 0; i < 18; ++i)
    {
        push_trace_point(trace, seed.x, seed.y - i);
    }
    for(int i = 1; i < 24; ++i)
    {
        push_trace_point(trace, seed.x + i, seed.y - 17);
    }
}

void fill_straight_trace(trace_t *trace, point_t seed)
{
    for(int i = 0; i < 48; ++i)
    {
        push_trace_point(trace, seed.x, seed.y - i);
    }
}

int run_reuse_contract()
{
    int failed = 0;
    runtime_t rt = {};
    fill_far_seed_column(&rt);

    g_trace_shape = TRACE_SHAPE_L;
    expect_eq("first build ok", build_cross_farline(&rt, 1), 1, &failed);
    expect_eq("first source", rt.cross.left_far_l_source, CROSS_FAR_L_NEW, &failed);
    expect_eq("first reuse count", rt.cross.left_far_l_reuse_count, 0, &failed);
    expect_ge("first l", rt.cross.left_l, 0, &failed);
    expect_ge("first num", rt.cross.left_num, k_cross_min_front_step, &failed);

    const int old_l = rt.cross.left_l;
    g_trace_shape = TRACE_SHAPE_STRAIGHT;
    expect_eq("reuse build ok", build_cross_farline(&rt, 1), 1, &failed);
    expect_eq("reuse l", rt.cross.left_l, old_l, &failed);
    expect_eq("reuse source", rt.cross.left_far_l_source, CROSS_FAR_L_REUSED, &failed);
    expect_eq("reuse count", rt.cross.left_far_l_reuse_count, 1, &failed);
    expect_ge("reuse tail", rt.cross.left_num - rt.cross.left_l, k_cross_min_front_step, &failed);

    expect_eq("reuse expires build ok", build_cross_farline(&rt, 1), 1, &failed);
    expect_eq("reuse expires l", rt.cross.left_l, -1, &failed);
    expect_eq("reuse expires source", rt.cross.left_far_l_source, CROSS_FAR_L_NONE, &failed);
    expect_eq("reuse expires count", rt.cross.left_far_l_reuse_count, 0, &failed);

    g_trace_shape = TRACE_SHAPE_FAIL;
    expect_eq("fail build", build_cross_farline(&rt, 1), 0, &failed);
    expect_eq("fail l", rt.cross.left_l, -1, &failed);
    expect_eq("fail source", rt.cross.left_far_l_source, CROSS_FAR_L_NONE, &failed);
    expect_eq("fail reuse count", rt.cross.left_far_l_reuse_count, 0, &failed);

    return failed;
}

int run_reset_zero_guard()
{
    int failed = 0;
    runtime_t rt = {};
    fill_far_seed_column(&rt);
    rt.cross.left_l = 0;
    rt.cross.left_far_l_source = CROSS_FAR_L_NONE;

    g_trace_shape = TRACE_SHAPE_STRAIGHT;
    expect_eq("guard build ok", build_cross_farline(&rt, 1), 1, &failed);
    expect_eq("guard l", rt.cross.left_l, -1, &failed);
    expect_eq("guard source", rt.cross.left_far_l_source, CROSS_FAR_L_NONE, &failed);
    expect_eq("guard reuse count", rt.cross.left_far_l_reuse_count, 0, &failed);

    return failed;
}
}

int cross_farline_test_trace_single(const uint8_t gray[RAW_H][RAW_W],
                                    point_t seed,
                                    int left_side,
                                    trace_t *trace)
{
    (void)gray;
    if(trace == nullptr || g_trace_shape == TRACE_SHAPE_FAIL)
    {
        return 0;
    }

    std::memset(trace, 0, sizeof(*trace));
    trace->left_side = left_side ? 1 : 0;
    trace->seed = seed;
    trace->stop_point = seed;

    if(g_trace_shape == TRACE_SHAPE_L)
    {
        fill_l_trace(trace, seed);
    }
    else
    {
        fill_straight_trace(trace, seed);
    }

    return trace->step >= TRACE_MIN_STEP;
}

int main()
{
    int failed = 0;
    failed |= run_reuse_contract();
    failed |= run_reset_zero_guard();
    if(failed)
    {
        return 1;
    }

    std::puts("cross_farline_reuse_test: ok");
    return 0;
}
