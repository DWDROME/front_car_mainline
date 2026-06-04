#include "cross.hpp"

#include "clip.hpp"
#include "imgproc.hpp"
#include "perspective.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{
// 十字判定沿用 AuTop 的双 L 点入口；
// BEGIN 截近线，IN 用远线选边，但退出十字仍看近线是否一起丢失/恢复。
const int k_cross_min_front_step = 8; // 远线 trace / IPM 后至少保留 8 个点，太短就不当有效远线。
const int k_cross_far_left_x = RAW_W * 86 / 376; // 左远线固定列 seed，按参考版 376 宽缩到当前 RAW_W。
const int k_cross_far_right_x = RAW_W * 280 / 376; // 右远线固定列 seed，按参考版 376 宽缩到当前 RAW_W。
// 对齐参考版 0.1m 近角门；当前 3px 重采样下等效约 4~5 点，这里配合 <= 判断取 4。
const int k_cross_begin_near_step = 4; // BEGIN 阶段 L 点靠近门，任一侧 L 角进入前约 0.1m 就切 IN。
// CROSS_IN 退出门槛仍按当前近线长度算；这里不是 farline 阈值。
const int k_cross_near_lost_step = 5; // CROSS_IN 内两侧近线都短于 5 点，记一次“近线已丢”。
const int k_cross_near_recover_step = 20; // CROSS_IN 内两侧近线都恢复到 20 点以上，才允许退出十字。
const int k_cross_far_resample_dist = 3; // 十字远线重采样步长，和主线当前 3px 步长保持一致。
const int k_cross_far_l_window = 4; // 远 L 局部角计算窗口，前后各取 4 点构造转角。
const int k_cross_far_nms_window = k_cross_far_l_window * 2 + 1; // 远 L 峰值 NMS 窗口，当前等于 9 点。
const int k_cross_far_l_angle_min = 70; // 远 L 角置信度下限，小于这个更像普通弯折。
const int k_cross_far_l_angle_max = 110; // 远 L 角置信度上限，大于这个更像噪声尖峰或异常折角。
const int k_cross_far_edge_width = 4; // 固定列贴近边缘时，允许把 4 像素边带视作有效起扫边界。

// 离开十字后清空状态，下一帧重新按双 L 点判断是否进入。
void cross_leave(cross_state_t *cross)
{
    if(cross == nullptr)
    {
        return;
    }
    std::memset(cross, 0, sizeof(*cross));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      在远线重采样点列上找 L 点：先算局部角度，再做 NMS，最后按角度区间筛选
//  @return     int          远线 L 点索引；没找到返回 -1
//  @note       角度单位是 degree，只扫描前 80 个重采样点，避免远端噪声抢峰。
//-------------------------------------------------------------------------------------------------------------------
int far_l_index(const double pts[POINT_MAX][2], int num)
{
    if(num < k_cross_far_l_window * 2 + 1)
    {
        return -1;
    }

    double a[POINT_MAX] = {};
    uint8_t an[POINT_MAX] = {};
    const int stop = std::min(num, 80);
    for(int i = k_cross_far_l_window; i < stop - k_cross_far_l_window; ++i)
    {
        const double x0 = pts[i - k_cross_far_l_window][0];
        const double y0 = pts[i - k_cross_far_l_window][1];
        const double x1 = pts[i][0];
        const double y1 = pts[i][1];
        const double x2 = pts[i + k_cross_far_l_window][0];
        const double y2 = pts[i + k_cross_far_l_window][1];
        if(x0 < 0.0 || y0 < 0.0 ||
           x1 < 0.0 || y1 < 0.0 ||
           x2 < 0.0 || y2 < 0.0)
        {
            continue;
        }
        const double ax = x1 - x0;
        const double ay = y1 - y0;
        const double bx = x2 - x1;
        const double by = y2 - y1;
        const double an = std::hypot(ax, ay);
        const double bn = std::hypot(bx, by);
        if(an < 1e-9 || bn < 1e-9)
        {
            continue;
        }
        a[i] = std::atan2(std::fabs(ax * by - ay * bx), ax * bx + ay * by) * 180.0 /
               3.14159265358979323846;
    }

    const int half = k_cross_far_nms_window / 2;
    for(int i = 0; i < stop; ++i)
    {
        const double peak = a[i];
        if(peak <= 0.0)
        {
            continue;
        }

        int keep = 1;
        const int lo = std::max(0, i - half);
        const int hi = std::min(stop - 1, i + half);
        for(int j = lo; j <= hi; ++j)
        {
            if(j != i && a[j] > peak)
            {
                keep = 0;
                break;
            }
        }
        if(keep)
        {
            an[i] = 1;
        }
    }

    for(int i = 0; i < stop; ++i)
    {
        if(!an[i])
        {
            continue;
        }

        const int i0 = clip_i(i - k_cross_far_l_window, 0, num - 1);
        const int i1 = clip_i(i + k_cross_far_l_window, 0, num - 1);
        const double conf = a[i] - (a[i0] + a[i1]) * 0.5;
        int angle_ok = 0;
        if(conf >= k_cross_far_l_angle_min)
        {
            if(conf <= k_cross_far_l_angle_max)
            {
                angle_ok = 1;
            }
        }
        if(angle_ok)
        {
            return i;
        }
    }
    return -1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      按参考 cross_farline 的固定列扫描远线 seed：先看到白，再遇黑时返回上一行白点
//  @return     int          1 找到 seed / 0 未找到
//  @note       left_side=1 扫左远线固定列；left_side=0 扫右远线固定列。
//-------------------------------------------------------------------------------------------------------------------
int find_far_seed(runtime_t *rt, int left_side, point_t *seed)
{
    if(rt == nullptr || seed == nullptr)
    {
        return 0;
    }

    int x0 = k_cross_far_right_x;
    if(left_side)
    {
        x0 = k_cross_far_left_x;
    }
    const int x = clip_i(x0, 1, RAW_W - 2);
    int y = START_HIGH;
    if(rt->seeds.row > 0)
    {
        y = rt->seeds.row;
    }
    y = clip_i(y, 1, RAW_H - 2);

    int white = 0;
    for(; y > 0; --y)
    {
        const int th = calc_th(rt->gray, x, y);
        if(rt->gray[y][x] >= th)
        {
            white = 1;
        }
        int edge_col = 0;
        if(x <= k_cross_far_edge_width)
        {
            edge_col = 1;
        }
        if(x >= RAW_W - 1 - k_cross_far_edge_width)
        {
            edge_col = 1;
        }

        int black_after_white = 0;
        if(rt->gray[y][x] < th)
        {
            if(white || edge_col)
            {
                black_after_white = 1;
            }
        }

        if(black_after_white)
        {
            const int y1 = clip_i(y + 1, 1, RAW_H - 2);
            const int th1 = calc_th(rt->gray, x, y1);
            if(rt->gray[y1][x] >= th1)
            {
                *seed = {x, y1};
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      构建一侧十字远线：固定列 seed -> trace -> IPM/pass-through -> 平滑 -> 重采样 -> 找远 L
//  @return     int          1 远线点列构建完成 / 0 seed、trace 或点数不足
//  @note       远线和普通边界共用 perspective_points()，保持 IPM 出界截断语义一致。
//-------------------------------------------------------------------------------------------------------------------
int build_cross_farline(runtime_t *rt, int left_side)
{
    if(rt == nullptr)
    {
        return 0;
    }

    int has_matrix = rt->has_matrix;

    double (*far_pts)[2] = rt->cross.right_pts;
    int *far_num = &rt->cross.right_num;
    int *far_l = &rt->cross.right_l;
    if(left_side)
    {
        far_pts = rt->cross.left_pts;
        far_num = &rt->cross.left_num;
        far_l = &rt->cross.left_l;
    }

    *far_num = 0;
    *far_l = -1;
    std::memset(far_pts, 0, sizeof(double[POINT_MAX][2]));
    point_t seed = {-1, -1};
    if(!find_far_seed(rt, left_side, &seed))
    {
        return 0;
    }

    trace_t tr0 = {};
    int trace_ok = trace_single(rt->gray, seed, left_side, &tr0);
    if(!trace_ok)
    {
        return 0;
    }
    if(tr0.step < k_cross_min_front_step)
    {
        return 0;
    }

    double ipm0[POINT_MAX][2] = {};
    double ipm1[POINT_MAX][2] = {};
    double ipm2[POINT_MAX][2] = {};
    int num0 = perspective_points(tr0.pts, tr0.step, rt->matrix, has_matrix, ipm0);
    if(num0 < k_cross_min_front_step)
    {
        return 0;
    }

    int num1 = 0;
    int num2 = 0;
    blur_points(ipm0, num0, ipm1, &num1);
    resample_points(ipm1, num1, ipm2, &num2, k_cross_far_resample_dist);
    *far_num = 0;
    for(int i = 0; i < num2 && *far_num < POINT_MAX; ++i)
    {
        far_pts[*far_num][0] = ipm2[i][0];
        far_pts[*far_num][1] = ipm2[i][1];
        ++(*far_num);
    }
    if(*far_num < k_cross_min_front_step)
    {
        return 0;
    }
    *far_l = far_l_index(far_pts, *far_num);
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      十字 BEGIN 阶段：截断近线，等待双 L 点靠前后切到 IN
//  @return     void
//  @note       BEGIN 不提前搜远线；否则十字上方黑痕可能把 front seed 吸走。
//-------------------------------------------------------------------------------------------------------------------
void cross_begin(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }

    boundary_t *left = &rt->track.left;
    boundary_t *right = &rt->track.right;
    const int left_l = left->l_ok;
    const int right_l = right->l_ok;
    int both_l = 0;
    if(left_l && right_l)
    {
        both_l = 1;
    }

    int left_near = 0;
    if(left_l && left->now_step > 0)
    {
        const int id = clip_i(left->l_now_index, 0, left->now_step - 1);
        if(id <= k_cross_begin_near_step)
        {
            left_near = 1;
        }
    }

    int right_near = 0;
    if(right_l && right->now_step > 0)
    {
        const int id = clip_i(right->l_now_index, 0, right->now_step - 1);
        if(id <= k_cross_begin_near_step)
        {
            right_near = 1;
        }
    }

    // 截断左线
    if(left_l && left->original_step > 0 && left->now_step > 0)
    {
        left->original_step = clip_i(left->l_original_index, 0, left->original_step);
        left->now_step = clip_i(left->l_now_index, 0, left->now_step);
    }
    // 截断右线
    if(right_l && right->original_step > 0 && right->now_step > 0)
    {
        right->original_step = clip_i(right->l_original_index, 0, right->original_step);
        right->now_step = clip_i(right->l_now_index, 0, right->now_step);
    }

    int near_ok = 0;
    if(left_near || right_near)
    {
        near_ok = 1;
    }
    if(both_l && near_ok)
    {
        rt->cross.state = CROSS_STATE_IN;
        rt->cross.not_have_line = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      十字 IN 阶段：优先用远线 L 点选边，远 L 不稳时按近线丢失侧选边
//  @return     void
//  @note       退出十字仍看近线：两侧近线先一起丢，再一起恢复。
//-------------------------------------------------------------------------------------------------------------------
void cross_evolve(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }

    // 清空十字步线跟踪相关数据
    rt->cross.track_type = TRACK_TYPE_NONE;
    rt->cross.left_far_found = 0;
    rt->cross.right_far_found = 0;
    rt->cross.left_l = -1;
    rt->cross.right_l = -1;
    rt->cross.left_num = 0;
    rt->cross.right_num = 0;
    std::memset(rt->cross.left_pts, 0, sizeof(rt->cross.left_pts));
    std::memset(rt->cross.right_pts, 0, sizeof(rt->cross.right_pts));

    // 构建左右十字"远线"（通常为前方远 L 点串），存状态标志到 left_far_found/right_far_found
    rt->cross.left_far_found = build_cross_farline(rt, 1);
    rt->cross.right_far_found = build_cross_farline(rt, 0);

    // 获取当前最近侧左右线可用点数
    const int left_near_step = rt->track.left.now_step;
    const int right_near_step = rt->track.right.now_step;

    // 检查两侧近线是否都短于丢失阈值
    int both_near_lost = 0;
    if(left_near_step < k_cross_near_lost_step)
    {
        if(right_near_step < k_cross_near_lost_step)
        {
            both_near_lost = 1;
        }
    }
    if(both_near_lost)
    {
        rt->cross.not_have_line++;
    }

    // 优先看有没有稳定且数量足够的远线
    int left_ok = 0;
    if(rt->cross.left_far_found)
    {
        if(rt->cross.left_num >= k_cross_min_front_step && rt->cross.left_l >= 0)
        {
            left_ok = 1;
        }
    }

    int right_ok = 0;
    if(rt->cross.right_far_found)
    {
        if(rt->cross.right_num >= k_cross_min_front_step && rt->cross.right_l >= 0)
        {
            right_ok = 1;
        }
    }

    // 选边顺序对齐参考版：右远 L 优先、左远 L 次之、最后按近线丢失侧定侧。
    if(right_ok)
    {
        rt->cross.track_type = TRACK_TYPE_RIGHT;
    }
    else if(left_ok)
    {
        rt->cross.track_type = TRACK_TYPE_LEFT;
    }
    else if(rt->cross.not_have_line > 0)
    {
        if(right_near_step < k_cross_near_lost_step)
        {
            rt->cross.track_type = TRACK_TYPE_RIGHT;
        }
        else if(left_near_step < k_cross_near_lost_step)
        {
            rt->cross.track_type = TRACK_TYPE_LEFT;
        }
    }

    // 检查两侧近线是否都恢复到指定长度，用来判断是否退出十字
    int both_near_recover = 0;
    if(left_near_step > k_cross_near_recover_step)
    {
        if(right_near_step > k_cross_near_recover_step)
        {
            both_near_recover = 1;
        }
    }
    // 如果 not_have_line 连续大于2，且两侧近线都恢复，退出十字
    if(rt->cross.not_have_line > 2 && both_near_recover)
    {
        cross_leave(&rt->cross);
    }
}

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      十字状态机入口：NONE 判双 L；BEGIN 截近线；IN 走远线并等待近线丢失后恢复
//  @return     void
//  @note       ring 已活动时由 element_process() 保证互斥；本函数只维护 cross 自身状态。
//-------------------------------------------------------------------------------------------------------------------
void cross_process(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }

    if(rt->cross.state == CROSS_STATE_NONE)
    {
        boundary_t *left = &rt->track.left;
        boundary_t *right = &rt->track.right;
        int both_l = 0;
        if(left->l_ok && right->l_ok)
        {
            both_l = 1;
        }

        if(both_l)
        {
            rt->cross.state = CROSS_STATE_BEGIN;
            rt->cross.not_have_line = 0;
            cross_begin(rt);
            if(rt->cross.state == CROSS_STATE_IN)
            {
                cross_evolve(rt);
            }
        }
        return;
    }

    if(rt->cross.state == CROSS_STATE_BEGIN)
    {
        cross_begin(rt);
        if(rt->cross.state == CROSS_STATE_IN)
        {
            cross_evolve(rt);
        }
    }
    else if(rt->cross.state == CROSS_STATE_IN)
    {
        cross_evolve(rt);
    }
    else
    {
        cross_leave(&rt->cross);
    }
}
