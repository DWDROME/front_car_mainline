#include <cmath>
#include <cstdio>
#include <cstring>

#include "tracking/boundary.hpp"
#include "tracking/cross.hpp"
#include "tracking/ring.hpp"

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

void reset_runtime(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }
    std::memset(rt, 0, sizeof(*rt));
}

void copy_original(boundary_t *bd, const double pts[POINT_MAX][2], int num)
{
    if(bd == nullptr)
    {
        return;
    }

    bd->original_step = num;
    for(int i = 0; i < num; ++i)
    {
        bd->original_pts[i].x = (int)std::lround(pts[i][0]);
        bd->original_pts[i].y = (int)std::lround(pts[i][1]);
    }
}

// ==== 直线合同点列 ====
void fill_straight(double pts[POINT_MAX][2], int *num, int x)
{
    const int n = 60;
    for(int i = 0; i < n; ++i)
    {
        pts[i][0] = (double)x;
        pts[i][1] = 112.0 - (double)i;
    }
    *num = n;
}

// ==== L角合同点列 ====
void fill_l_corner(double pts[POINT_MAX][2], int *num, int x, int outward_dir)
{
    const int n = 60;
    const int corner_i = 12;
    const double corner_y = 112.0 - (double)corner_i;
    for(int i = 0; i < n; ++i)
    {
        if(i <= corner_i)
        {
            pts[i][0] = (double)x;
            pts[i][1] = 112.0 - (double)i;
        }
        else
        {
            pts[i][0] = (double)(x + outward_dir * (i - corner_i));
            pts[i][1] = corner_y;
        }
    }
    *num = n;
}

void load_boundaries(runtime_t *rt,
                     const double left_pts[POINT_MAX][2],
                     int left_num,
                     const double right_pts[POINT_MAX][2],
                     int right_num)
{
    copy_original(&rt->track.left, left_pts, left_num);
    copy_original(&rt->track.right, right_pts, right_num);

    const double matrix[9] = {};
    refresh_boundary_corners(&rt->track.left,
                             &rt->track.right,
                             left_pts,
                             left_num,
                             right_pts,
                             right_num,
                             matrix,
                             0);
}

int run_cross_requires_strict_pair_contract()
{
    int failed = 0;
    double left_pts[POINT_MAX][2] = {};
    double right_pts[POINT_MAX][2] = {};
    int left_num = 0;
    int right_num = 0;

    runtime_t rt = {};
    reset_runtime(&rt);
    fill_l_corner(left_pts, &left_num, 60, -1);
    fill_straight(right_pts, &right_num, 105);
    load_boundaries(&rt, left_pts, left_num, right_pts, right_num);
    cross_process(&rt);
    expect_eq("cross rejects single L", rt.cross.state, CROSS_STATE_NONE, &failed);

    reset_runtime(&rt);
    fill_l_corner(left_pts, &left_num, 60, -1);
    fill_l_corner(right_pts, &right_num, 105, 1);
    load_boundaries(&rt, left_pts, left_num, right_pts, right_num);
    cross_process(&rt);
    expect_eq("cross accepts strict double L", rt.cross.state, CROSS_STATE_BEGIN, &failed);
    return failed;
}

int run_ring_requires_single_l_and_opposite_straight_contract()
{
    int failed = 0;
    double left_pts[POINT_MAX][2] = {};
    double right_pts[POINT_MAX][2] = {};
    int left_num = 0;
    int right_num = 0;

    runtime_t rt = {};
    reset_runtime(&rt);
    fill_l_corner(left_pts, &left_num, 60, -1);
    fill_straight(right_pts, &right_num, 105);
    load_boundaries(&rt, left_pts, left_num, right_pts, right_num);
    ring_process(&rt);
    expect_eq("ring accepts left single L", rt.ring.kind, RING_KIND_LEFT, &failed);
    expect_eq("ring left starts BEGIN", rt.ring.state, RING_STATE_BEGIN, &failed);

    reset_runtime(&rt);
    fill_straight(left_pts, &left_num, 60);
    fill_l_corner(right_pts, &right_num, 105, 1);
    load_boundaries(&rt, left_pts, left_num, right_pts, right_num);
    ring_process(&rt);
    expect_eq("ring accepts right single L", rt.ring.kind, RING_KIND_RIGHT, &failed);
    expect_eq("ring right starts BEGIN", rt.ring.state, RING_STATE_BEGIN, &failed);

    reset_runtime(&rt);
    fill_l_corner(left_pts, &left_num, 60, -1);
    fill_l_corner(right_pts, &right_num, 105, 1);
    load_boundaries(&rt, left_pts, left_num, right_pts, right_num);
    ring_process(&rt);
    expect_eq("ring rejects double L", rt.ring.kind, RING_KIND_NONE, &failed);

    reset_runtime(&rt);
    fill_straight(left_pts, &left_num, 60);
    fill_straight(right_pts, &right_num, 105);
    load_boundaries(&rt, left_pts, left_num, right_pts, right_num);
    ring_process(&rt);
    expect_eq("ring rejects straight pair", rt.ring.kind, RING_KIND_NONE, &failed);
    return failed;
}

int run_ring_run_far_l_crops_without_out_contract()
{
    int failed = 0;
    runtime_t rt = {};
    reset_runtime(&rt);

    rt.ring.kind = RING_KIND_LEFT;
    rt.ring.state = RING_STATE_RUN;
    rt.track.left.now_step = 40;
    rt.track.right.l_found = 1;
    rt.track.right.l_ok = 0;
    rt.track.right.l_now_index = 31;
    rt.track.right.l_original_index = 18;
    rt.track.right.original_step = 40;
    for(int i = 0; i < rt.track.right.original_step; ++i)
    {
        rt.track.right.original_pts[i] = {100, START_HIGH - i};
    }

    ring_process(&rt);

    expect_eq("far L keeps run", rt.ring.state, RING_STATE_RUN, &failed);
    expect_eq("far L crops original", rt.track.right.original_step, 19, &failed);
    return failed;
}
}

int main()
{
    int failed = 0;
    failed |= run_cross_requires_strict_pair_contract();
    failed |= run_ring_requires_single_l_and_opposite_straight_contract();
    failed |= run_ring_run_far_l_crops_without_out_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("element_entry_contract_test: ok");
    return 0;
}
