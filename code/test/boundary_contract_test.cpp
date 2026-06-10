#include <cmath>
#include <cstdio>
#include <cstring>

#include "tracking/boundary.hpp"

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

void expect_range_d(const char *name, double actual, double low, double high, int *failed)
{
    if(actual < low || actual > high)
    {
        std::fprintf(stderr, "FAIL: %s actual=%.3f range=[%.3f, %.3f]\n", name, actual, low, high);
        *failed = 1;
    }
}

void reset_boundary(boundary_t *bd)
{
    if(bd == nullptr)
    {
        return;
    }
    std::memset(bd, 0, sizeof(*bd));
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

void refresh_for_test(boundary_t *left,
                      boundary_t *right,
                      const double left_pts[POINT_MAX][2],
                      int left_num,
                      const double right_pts[POINT_MAX][2],
                      int right_num)
{
    reset_boundary(left);
    reset_boundary(right);
    copy_original(left, left_pts, left_num);
    copy_original(right, right_pts, right_num);

    const double matrix[9] = {};
    refresh_boundary_corners(left,
                             right,
                             left_pts,
                             left_num,
                             right_pts,
                             right_num,
                             matrix,
                             0);
}

int run_single_l_and_straight_contract()
{
    int failed = 0;
    double left_pts[POINT_MAX][2] = {};
    double right_pts[POINT_MAX][2] = {};
    int left_num = 0;
    int right_num = 0;

    fill_l_corner(left_pts, &left_num, 60, -1);
    fill_straight(right_pts, &right_num, 105);

    boundary_t left = {};
    boundary_t right = {};
    refresh_for_test(&left, &right, left_pts, left_num, right_pts, right_num);

    expect_eq("single left L found", left.l_found, 1, &failed);
    expect_eq("single left L ok", left.l_ok, 1, &failed);
    expect_eq("single right L absent", right.l_ok, 0, &failed);
    expect_eq("single left pair absent", left.l_pair_ok, 0, &failed);
    expect_eq("single right pair absent", right.l_pair_ok, 0, &failed);
    expect_eq("opposite straight", boundary_is_straight(&right), 1, &failed);
    expect_eq("L side not straight", boundary_is_straight(&left), 0, &failed);
    expect_range_d("single left L angle", left.l_angle_deg, 70.0, 140.0, &failed);
    return failed;
}

int run_strict_double_l_contract()
{
    int failed = 0;
    double left_pts[POINT_MAX][2] = {};
    double right_pts[POINT_MAX][2] = {};
    int left_num = 0;
    int right_num = 0;

    fill_l_corner(left_pts, &left_num, 60, -1);
    fill_l_corner(right_pts, &right_num, 105, 1);

    boundary_t left = {};
    boundary_t right = {};
    refresh_for_test(&left, &right, left_pts, left_num, right_pts, right_num);

    expect_eq("double left L ok", left.l_ok, 1, &failed);
    expect_eq("double right L ok", right.l_ok, 1, &failed);
    expect_eq("double left pair ok", left.l_pair_ok, 1, &failed);
    expect_eq("double right pair ok", right.l_pair_ok, 1, &failed);
    expect_range_d("double pair width0", left.l_pair_width0, 44.0, 46.0, &failed);
    expect_range_d("double pair width1", left.l_pair_width1, 70.0, 120.0, &failed);
    expect_eq("double left not straight", boundary_is_straight(&left), 0, &failed);
    expect_eq("double right not straight", boundary_is_straight(&right), 0, &failed);
    return failed;
}

int run_plain_straight_contract()
{
    int failed = 0;
    double left_pts[POINT_MAX][2] = {};
    double right_pts[POINT_MAX][2] = {};
    int left_num = 0;
    int right_num = 0;

    fill_straight(left_pts, &left_num, 60);
    fill_straight(right_pts, &right_num, 105);

    boundary_t left = {};
    boundary_t right = {};
    refresh_for_test(&left, &right, left_pts, left_num, right_pts, right_num);

    expect_eq("straight left no L", left.l_found, 0, &failed);
    expect_eq("straight right no L", right.l_found, 0, &failed);
    expect_eq("straight left", boundary_is_straight(&left), 1, &failed);
    expect_eq("straight right", boundary_is_straight(&right), 1, &failed);
    return failed;
}
}

int main()
{
    int failed = 0;
    failed |= run_plain_straight_contract();
    failed |= run_single_l_and_straight_contract();
    failed |= run_strict_double_l_contract();
    if(failed)
    {
        return 1;
    }

    std::puts("boundary_contract_test: ok");
    return 0;
}
