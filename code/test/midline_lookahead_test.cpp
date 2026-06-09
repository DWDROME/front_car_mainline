#include <cstdio>
#include <cstring>

#include "types.hpp"
#include "tracking/imgproc.cpp"

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

void expect_ge(const char *name, int actual, int expected, int *failed)
{
    if(actual < expected)
    {
        std::fprintf(stderr, "FAIL: %s actual=%d expected>=%d\n", name, actual, expected);
        *failed = 1;
    }
}

void push_mid_point(midline_t *mid, int idx, int x, int y, int dist)
{
    mid->pts[idx] = {x, y};
    mid->dist[idx] = dist;
    if(mid->step <= idx)
    {
        mid->step = idx + 1;
    }
}

int run_forward_contract()
{
    int failed = 0;
    midline_t mid = {};
    push_mid_point(&mid, 0, 89, 109, 0);
    push_mid_point(&mid, 1, 87, 100, 12);
    push_mid_point(&mid, 2, 84, 90, 24);
    push_mid_point(&mid, 3, 82, 74, 36);

    expect_eq("forward length", midline_has_lookahead(&mid, 35), 1, &failed);
    expect_eq("forward target", midline_has_forward_lookahead(&mid, 35, 109), 1, &failed);
    return failed;
}

int run_backward_reject_contract()
{
    int failed = 0;
    midline_t mid = {};
    push_mid_point(&mid, 0, 89, 109, 0);
    push_mid_point(&mid, 1, 88, 112, 12);
    push_mid_point(&mid, 2, 86, 115, 24);
    push_mid_point(&mid, 3, 84, 117, 36);

    expect_eq("backward length still covered", midline_has_lookahead(&mid, 35), 1, &failed);
    expect_eq("backward target rejected", midline_has_forward_lookahead(&mid, 35, 109), 0, &failed);
    return failed;
}

int run_short_forward_reject_contract()
{
    int failed = 0;
    midline_t mid = {};
    push_mid_point(&mid, 0, 89, 109, 0);
    push_mid_point(&mid, 1, 87, 101, 8);
    push_mid_point(&mid, 2, 84, 94, 16);
    push_mid_point(&mid, 3, 82, 87, 24);

    expect_eq("short length old gate still covered", midline_has_lookahead(&mid, 35), 1, &failed);
    expect_eq("short forward rejected", midline_has_forward_lookahead(&mid, 35, 109), 0, &failed);
    return failed;
}

int run_sample_gap_coverage_contract()
{
    int failed = 0;
    midline_t mid = {};
    push_mid_point(&mid, 0, 89, 109, 0);
    push_mid_point(&mid, 1, 87, 96, 18);
    push_mid_point(&mid, 2, 84, 83, 34);
    push_mid_point(&mid, 3, 82, 72, 37);

    expect_eq("sample gap covered", midline_has_forward_lookahead(&mid, 35, 109), 1, &failed);
    return failed;
}

int run_build_rptsn_valid_run_contract()
{
    int failed = 0;
    double rpts[POINT_MAX][2] = {};
    rpts[0][0] = -1.0;
    rpts[0][1] = -1.0;
    rpts[1][0] = 89.0;
    rpts[1][1] = 109.0;
    rpts[2][0] = 87.0;
    rpts[2][1] = 98.0;
    rpts[3][0] = 84.0;
    rpts[3][1] = 86.0;
    rpts[4][0] = 82.0;
    rpts[4][1] = 74.0;

    midline_t mid = {};
    expect_ge("ordinary trims invalid prefix", build_rptsn(rpts, 5, 89, 109, 0, &mid), 2, &failed);

    mid = {};
    expect_eq("forced begin keeps strict invalid reject", build_rptsn(rpts, 5, 89, 109, 1, &mid), 0, &failed);
    return failed;
}
}

int main()
{
    int failed = 0;
    failed |= run_forward_contract();
    failed |= run_backward_reject_contract();
    failed |= run_short_forward_reject_contract();
    failed |= run_sample_gap_coverage_contract();
    failed |= run_build_rptsn_valid_run_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("midline_lookahead_test: ok");
    return 0;
}
