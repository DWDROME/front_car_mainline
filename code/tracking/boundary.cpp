#include "boundary.hpp"

#include "clip.hpp"
#include "imgproc.hpp"
#include "perspective.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{
// 这里负责的是边界解释层：
// 原图/ IPM 投影、角点判定、前边界修补。
// 不接管元素状态机，也不向控制层回写。
const int k_curvature_threshold = 3; // 曲线程度阈值，单位 1/pixel
const int k_angle_threshold = 8; // 局部角度阈值，单位 degree
const int k_l_angle_low = 70; // L 角角度阈值，单位 degree
const int k_l_angle_high = 140;  // L 角角度阈值，单位 degree

const double k_pi = 3.14159265358979323846;

// 对齐 AuTop 里常用的 10 点窗口，弯道上的碎峰会少很多。
const int k_window_size = 10; // 窗口大小，单位 点

const int k_boundary_blur_kernel = 3; // 边界模糊核大小，单位 点
const int k_boundary_resample_dist = 3;  // 边界重采样距离，单位 点

const int k_corner_open_step = 34;  // 双 L 角张开步长，单位 点
const double k_corner_pair_width_ref = 45.0; // 双 L 角宽度参考值，单位 pixel
const double k_corner_pair_tol = 15.0; // 双 L 角宽度误差阈值，单位 pixel
const double k_corner_pair_open_ref = 70.0; // 双 L 角张开参考值，单位 pixel
const int k_corner_scan_step = 28; // 角点扫描步长，单位 点

const int k_straight_scan_step = 34; // 直道扫描步长，单位 点
const int k_corner_front_step = 28; // 角点前段步长，单位 点
const int k_straight_min_step = 34; // 直道最小步长，单位 点

const int k_pair_none = 0; // 双 L 角状态：无
const int k_pair_width0_bad = 1; // 双 L 角状态：宽度不合格
const int k_pair_open_bad = 2; // 双 L 角状态：张开不合格
const int k_pair_dir_bad = 3; // 双 L 角状态：方向不合格

// 用前后各 dist 个点构造两条向量，返回 index 处局部转角；单位 rad，带左右转方向。
double local_angle_d(const double pts[POINT_MAX][2], int step, int index, int dist)
{
    if(step <= 0)
    {
        return 0.0;
    }

    int c = clip_i(index, 0, step - 1);
    int p = clip_i(c - dist, 0, step - 1);
    int n = clip_i(c + dist, 0, step - 1);

    double dx1 = pts[c][0] - pts[p][0];
    double dy1 = pts[c][1] - pts[p][1];
    double dx2 = pts[n][0] - pts[c][0];
    double dy2 = pts[n][1] - pts[c][1];
    if(pts[c][0] < 0.0 || pts[c][1] < 0.0 ||
       pts[p][0] < 0.0 || pts[p][1] < 0.0 ||
       pts[n][0] < 0.0 || pts[n][1] < 0.0)
    {
        return 0.0;
    }
    double dn1 = std::hypot(dx1, dy1);
    double dn2 = std::hypot(dx2, dy2);
    if(dn1 < 1e-9 || dn2 < 1e-9)
    {
        return 0.0;
    }

    double cross = dx1 * dy2 - dy1 * dx2;
    double dot = dx1 * dx2 + dy1 * dy2;
    return std::atan2(cross, dot);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      生成参考版风格的 angle + nms 两组固定数组
//  @return     void
//  @note       a 存局部角，单位 rad；an 标记局部峰值，后续 scan_corner() 再按角度范围筛。
//-------------------------------------------------------------------------------------------------------------------
void build_ang_pts(const double pts[POINT_MAX][2], int step, int win, double a[POINT_MAX], uint8_t an[POINT_MAX])
{
    std::memset(a, 0, sizeof(double) * POINT_MAX);
    std::memset(an, 0, sizeof(uint8_t) * POINT_MAX);
    if(pts == nullptr || step <= 0 || win <= 0)
    {
        return;
    }

    step = std::min(step, (int)POINT_MAX);
    for(int i = 0; i < step; ++i)
    {
        a[i] = local_angle_d(pts, step, i, win);
    }

    for(int i = 0; i < step; ++i)
    {
        const double peak = std::fabs(a[i]);
        if(peak <= 1e-9)
        {
            continue;
        }

        int ok = 1;
        const int lo = clip_i(i - win, 0, step - 1);
        const int hi = clip_i(i + win, 0, step - 1);
        for(int j = lo; j <= hi; ++j)
        {
            if(j == i)
            {
                continue;
            }
            if(std::fabs(a[j]) > peak)
            {
                ok = 0;
                break;
            }
        }
        an[i] = ok ? 1 : 0;
    }
}

// 角点置信度：当前峰值减去前后同窗口峰值均值；单位仍是 rad。
double angle_conf(const double a[POINT_MAX], int step, int i, int win)
{
    if(a == nullptr || step <= 0 || i < 0 || i >= step || win <= 0)
    {
        return 0.0;
    }

    const double ai = std::fabs(a[i]);
    if(ai <= 1e-9)
    {
        return 0.0;
    }

    const int im1 = clip_i(i - win, 0, step - 1);
    const int ip1 = clip_i(i + win, 0, step - 1);
    return ai - 0.5 * (std::fabs(a[im1]) + std::fabs(a[ip1]));
}

// 把 IPM/当前点列里的角点索引映回原图边界点，供 cross/ring 截 raw 点。
int find_raw_corner(const boundary_t *bd, int i, const double matrix[9], int has_matrix)
{
    if(bd == nullptr || bd->work_step <= 0 || bd->original_step <= 0)
    {
        return -1;
    }

    const int id = clip_i(i, 0, bd->work_step - 1);
    const double now_x = bd->work_pts[id][0];
    const double now_y = bd->work_pts[id][1];
    int best_i = -1;
    int best_d = 1 << 30;
    for(int j = 0; j < bd->original_step; ++j)
    {
        point_t p = bd->original_pts[j];
        if(has_matrix)
        {
            int ok = 0;
            perspective_point(matrix, &bd->original_pts[j], &p, &ok);
            if(!ok)
            {
                continue;
            }
        }

        const int d = round_i(std::fabs((double)p.x - now_x) + std::fabs((double)p.y - now_y));
        if(d < best_d)
        {
            best_d = d;
            best_i = j;
        }
    }
    return best_i;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      只在边界前段找第一个有效角点：先看 nms，再用 conf 角度范围筛
//  @return     int          当前边界点列索引；没找到返回 -1
//  @note       raw 输出原图边界索引，deg 输出角点置信度角度，单位 degree。
//-------------------------------------------------------------------------------------------------------------------
int scan_corner(const boundary_t *bd,
                const double a[POINT_MAX],
                const uint8_t an[POINT_MAX],
                int win,
                int low_deg,
                int high_deg,
                const double matrix[9],
                int has_matrix,
                int *raw,
                double *deg)
{
    if(bd == nullptr || a == nullptr || an == nullptr || bd->now_step <= 0)
    {
        return -1;
    }

    const int step = std::min(bd->now_step, (int)POINT_MAX);
    const int stop = std::min(step, k_corner_scan_step);
    for(int i = 0; i < stop; ++i)
    {
        if(!an[i])
        {
            continue;
        }

        const double conf = angle_conf(a, step, i, win) * 180.0 / k_pi;
        if(conf <= low_deg || conf >= high_deg)
        {
            continue;
        }

        if(raw != nullptr)
        {
            const int raw_i = find_raw_corner(bd, i, matrix, has_matrix);
            if(raw_i < 0)
            {
                continue;
            }
            *raw = raw_i;
        }
        if(deg != nullptr)
        {
            *deg = conf;
        }
        return i;
    }
    return -1;
}

// 三点外接圆估算曲率 k=1/R；共线或退化时返回 0，单位 1/pixel。
double curvature(point_t p0, point_t p1, point_t p2)
{
    double cross = (double)(p1.x - p0.x) * (p2.y - p0.y) - (double)(p2.x - p0.x) * (p1.y - p0.y);
    double area = 0.5 * std::fabs(cross);
    if(area < 1e-8)
    {
        return 0.0;
    }

    double a = std::hypot((double)(p2.x - p1.x), (double)(p2.y - p1.y));
    double b = std::hypot((double)(p2.x - p0.x), (double)(p2.y - p0.y));
    double c = std::hypot((double)(p1.x - p0.x), (double)(p1.y - p0.y));
    double r = (a * b * c) / (4.0 * area);
    return r > 1e-9 ? 1.0 / r : 0.0;
}

// 清空一个边界上的单侧 L 角和双 L 复核结果。
void clear_corner(boundary_t *bd)
{
    if(bd == nullptr)
    {
        return;
    }
    bd->l_found = 0;
    bd->l_ok = 0;
    bd->l_now_index = 0;
    bd->l_original_index = 0;
    bd->l_angle_deg = 0.0;
    bd->l_pair_ok = 0;
    bd->l_pair_state = k_pair_none;
    bd->l_pair_width0 = 0.0;
    bd->l_pair_width1 = 0.0;
}

int strict_pair_inputs_ready(const boundary_t *left, const boundary_t *right)
{
    if(left == nullptr || right == nullptr)
    {
        return 0;
    }
    if(!left->l_ok || !right->l_ok)
    {
        return 0;
    }
    return left->now_step > 0 && right->now_step > 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      双 L 角二次检查：记录宽度/张开状态，并判断左右 L 点是否组成参考版 strict 入口
//  @return     int          1 双 L 复核通过 / 0 宽度、张开或方向不合格
//  @note       只写 l_pair_ok/l_pair_*；不覆盖单侧 l_ok，避免 cross/ring/zebra 语义耦合。
//-------------------------------------------------------------------------------------------------------------------
int corner_pair_ok(boundary_t *left, boundary_t *right)
{
    if(!strict_pair_inputs_ready(left, right))
    {
        return 0;
    }

    const int li = clip_i(left->l_now_index, 0, left->now_step - 1);
    const int ri = clip_i(right->l_now_index, 0, right->now_step - 1);
    const point_t lp = left->now_pts[li];
    const point_t rp = right->now_pts[ri];
    const int dx = lp.x - rp.x;
    const int dy = lp.y - rp.y;
    const double w0 = std::hypot((double)dx, (double)dy);
    const double w_ref = k_corner_pair_width_ref;
    left->l_pair_width0 = w0;
    right->l_pair_width0 = w0;
    if(std::fabs(w0 - w_ref) > k_corner_pair_tol)
    {
        left->l_pair_state = k_pair_width0_bad;
        right->l_pair_state = k_pair_width0_bad;
        return 0;
    }

    const int li1 = clip_i(li + k_corner_open_step, 0, left->now_step - 1);
    const int ri1 = clip_i(ri + k_corner_open_step, 0, right->now_step - 1);
    const point_t lp1 = left->now_pts[li1];
    const point_t rp1 = right->now_pts[ri1];
    const int dx1 = lp1.x - rp1.x;
    const int dy1 = lp1.y - rp1.y;
    const double w1 = std::hypot((double)dx1, (double)dy1);
    left->l_pair_width1 = w1;
    right->l_pair_width1 = w1;
    if(w1 <= k_corner_pair_open_ref)
    {
        left->l_pair_state = k_pair_open_bad;
        right->l_pair_state = k_pair_open_bad;
        return 0;
    }
    if(lp1.x >= lp.x || rp1.x <= rp.x)
    {
        left->l_pair_state = k_pair_dir_bad;
        right->l_pair_state = k_pair_dir_bad;
        return 0;
    }
    left->l_pair_ok = 1;
    right->l_pair_ok = 1;
    left->l_pair_state = k_pair_none;
    right->l_pair_state = k_pair_none;
    return 1;
}

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      由 trace 生成 boundary_t：保留原图序列，并复用主线 float 点列链生成当前边界
//  @return     void
//  @note       original_pts 是原图边界；work_pts/now_pts 和 mainline 一样走 perspective_points -> blur_points -> resample_points。
//-------------------------------------------------------------------------------------------------------------------
void build_boundary_from_trace(const trace_t *trace, const double matrix[9], int has_matrix, boundary_t *boundary)
{
    if(trace == nullptr || boundary == nullptr)
    {
        return;
    }

    std::memset(boundary, 0, sizeof(*boundary));
    boundary->original_step = clip_i(trace->step, 0, POINT_MAX);
    for(int i = 0; i < boundary->original_step; ++i)
    {
        boundary->original_pts[i] = trace->pts[i];
    }

    double rpts[POINT_MAX][2] = {};
    double blur[POINT_MAX][2] = {};
    int raw_num = perspective_points(boundary->original_pts,
                                     boundary->original_step,
                                     matrix,
                                     has_matrix,
                                     rpts);
    int blur_num = 0;
    blur_points(rpts, raw_num, blur, &blur_num);
    resample_points(blur,
                    blur_num,
                    boundary->work_pts,
                    &boundary->work_step,
                    k_boundary_resample_dist);

    boundary->now_step = boundary->work_step;
    if(boundary->work_step <= 0)
    {
        return;
    }

    const int x_max = has_matrix ? (IPM_W - 1) : (RAW_W - 1);
    const int y_max = has_matrix ? (IPM_H - 1) : (RAW_H - 1);
    for(int i = 0; i < boundary->work_step; ++i)
    {
        boundary->now_pts[i].x = clip_i(round_i(boundary->work_pts[i][0]), 0, x_max);
        boundary->now_pts[i].y = clip_i(round_i(boundary->work_pts[i][1]), 0, y_max);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      判断当前边界是否近似直线：曲率小、前段局部转角小、且未识别到 L 角
//  @return     int          1 近似直线 / 0 弯曲、过短或已有 L 角
//  @note       ring 用它判断对侧边界是否恢复直线，阈值不要和主线中线逻辑混用。
//-------------------------------------------------------------------------------------------------------------------
int boundary_is_straight(const boundary_t *bd)
{
    if(bd == nullptr || bd->now_step <= k_straight_min_step || bd->l_found)
    {
        return 0;
    }

    const double curv = curvature(bd->now_pts[0],
                                  bd->now_pts[bd->now_step / 2],
                                  bd->now_pts[bd->now_step - 1]);
    if(curv * 1000.0 >= k_curvature_threshold)
    {
        return 0;
    }

    const int step = bd->now_step;
    const int win = std::max(1, std::min(k_window_size, (step - 1) / 2));
    double a[POINT_MAX];
    uint8_t an[POINT_MAX];
    build_ang_pts(bd->work_pts, step, win, a, an);

    const int stop = std::min(step, k_straight_scan_step);
    for(int i = 0; i < stop; ++i)
    {
        if(!an[i])
        {
            continue;
        }

        const double ang = angle_conf(a, step, i, win) * 180.0 / k_pi;
        if(ang > k_angle_threshold)
        {
            return 0;
        }
    }
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      在左右边界前段搜索单侧 L 角，并独立刷新双 L 复核结果
//  @return     void
//  @note       l_ok 是单侧 L 语义；l_pair_ok 是 strict double-L 入口语义，二者不能混用。
//-------------------------------------------------------------------------------------------------------------------
void refresh_boundary_corners(boundary_t *left,
                              boundary_t *right,
                              const double left_pts[POINT_MAX][2],
                              int left_num,
                              const double right_pts[POINT_MAX][2],
                              int right_num,
                              const double matrix[9],
                              int has_matrix)
{
    if(left == nullptr || right == nullptr)
    {
        return;
    }

    boundary_t *bd_tab[2] = {left, right};
    const double (*work_tab[2])[2] = {left_pts, right_pts};
    const int num_tab[2] = {left_num, right_num};
    for(int side = 0; side < 2; ++side)
    {
        boundary_t *bd = bd_tab[side];
        clear_corner(bd);
        if(num_tab[side] < 3)
        {
            continue;
        }

        point_t work_pts[POINT_MAX];
        const int step = clip_i(num_tab[side], 0, POINT_MAX);
        bd->work_step = step;
        for(int i = 0; i < step; ++i)
        {
            bd->work_pts[i][0] = work_tab[side][i][0];
            bd->work_pts[i][1] = work_tab[side][i][1];
            work_pts[i].x = clip_i(round_i(work_tab[side][i][0]), 0, IPM_W - 1);
            work_pts[i].y = clip_i(round_i(work_tab[side][i][1]), 0, IPM_H - 1);
        }
        if(step < 3)
        {
            continue;
        }
        bd->now_step = step;
        for(int i = 0; i < step; ++i)
        {
            bd->now_pts[i] = work_pts[i];
        }

        const int win = std::max(1, std::min(k_window_size, (step - 1) / 2));
        double a[POINT_MAX];
        uint8_t an[POINT_MAX];
        build_ang_pts(bd->work_pts, step, win, a, an);

        int raw = 0;
        double deg = 0.0;
        const int li = scan_corner(bd, a, an, win, k_l_angle_low, k_l_angle_high, matrix, has_matrix, &raw, &deg);
        if(li >= 0)
        {
            bd->l_found = 1;
            bd->l_now_index = li;
            bd->l_original_index = raw;
            bd->l_angle_deg = deg;
            if(li < k_corner_front_step)
            {
                bd->l_ok = 1;
            }
        }
    }

    if(strict_pair_inputs_ready(left, right))
    {
        corner_pair_ok(left, right);
    }
}
