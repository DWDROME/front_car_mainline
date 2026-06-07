#include "ring.hpp"

#include "clip.hpp"
#include "imgproc.hpp"
#include "boundary.hpp"
#include "perspective.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{
const int k_lost_step = 7; // 丢失步长阈值，单位 点
const int k_have_step = 34; // 有步长阈值，单位 点
const int k_seed_dx = 5; // 种子点横移距离，单位 点
const int k_seed_dy = 3; // 种子点纵移距离，单位 点
const int k_in_lost_step = 4; // 入环丢失步长阈值，单位 点
const int k_run_corner_step = 14; // 环岛运行阶段角点步长阈值，单位 点
const int k_lost_confirm_n = 2; // 丢失确认次数阈值
const int k_have_confirm_n = 1; // 有确认次数阈值
const int k_end_left_exit_lost_n = 3; // 左环退出丢失次数阈值
const int k_end_right_exit_lost_n = 2; // 右环退出丢失次数阈值
const int k_encoder_per_meter = 5800; // 编码器每米步长，单位 步/米
const int k_in_encoder_step = k_encoder_per_meter * 314 / 200; // 入环走行阈值：约半圈弧长(314/200≈1.57m=π/2)对应的编码器步数
const int k_ring_find_line_len = 5; // 参考版 find_line_lenth
const int k_ring_forward_line = 62; // 参考版 ring_forward_line
const int k_ring_first_find_pos_num = 23; // 参考版 ring_find_pos=0.23
const int k_ring_first_find_pos_den = 100;
const int k_ring_second_find_pos_num = 345; // 参考版 ring_find_pos *= 1.5
const int k_ring_second_find_pos_den = 1000;
const int k_ring_first_cf_max = 30;
const int k_ring_second_cf_max = 20;
const double k_ring_first_mid_min = 0.1;
const double k_ring_first_side_min = 0.95;
const double k_ring_second_side_min = 0.3;
const double k_ring_first_line_degree = 0.995;
const double k_ring_second_line_degree = 0.999;
const int k_ring_degree_min_rows = 12;
const int k_ring_degree_first_start_y = RAW_H - 10;
const int k_ring_degree_second_start_y = RAW_H - 20;
const int k_ring_degree_end_y = 70;
const int64_t k_ring_first_confirm_encoder = k_encoder_per_meter * 8 / 10; // 参考版 set_ED(0.8f)
const int64_t k_ring_second_confirm_encoder = k_encoder_per_meter * 15 / 10; // 参考版 set_ED(1.5f)
const int64_t k_ring_false_exit_encoder = k_encoder_per_meter * 13 / 10; // 参考版非圆环路径 set_ED(1.3f)
const int k_ring_pending_first = 1;
const int k_ring_pending_second = 2;
const int k_ring_pending_false_wait_first = 3;
const int k_ring_pending_false_wait_exit = 4;

struct ring_scan_t
{
    double proportion;
    int x;
    int y;
    int total;
    int white;
};

int ring_pixel_is_white(const uint8_t gray[RAW_H][RAW_W], int x, int y)
{
    if(gray == nullptr || x < 0 || x >= RAW_W || y < 0 || y >= RAW_H)
    {
        return 0;
    }
    const int th = calc_th(gray, x, y);
    return gray[y][x] > th;
}

ring_scan_t ring_scan_line_blank(const uint8_t gray[RAW_H][RAW_W], int x0, int y0, int x1, int y1)
{
    ring_scan_t out = {0.0, -1, -1, 0, 0};
    if(gray == nullptr)
    {
        return out;
    }

    const int dx = std::abs(x1 - x0);
    const int dy = std::abs(y1 - y0);
    const int sx = (x0 < x1) ? 1 : -1;
    const int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int sum_x = 0;
    int sum_y = 0;

    while(1)
    {
        if(x0 >= 0 && x0 < RAW_W && y0 >= 0 && y0 < RAW_H)
        {
            out.total++;
            if(ring_pixel_is_white(gray, x0, y0))
            {
                out.white++;
                sum_x += x0;
                sum_y += y0;
            }
        }

        if(x0 == x1 && y0 == y1)
        {
            break;
        }

        const int e2 = 2 * err;
        if(e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if(e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }

    if(out.total > 0)
    {
        out.proportion = (double)out.white / (double)out.total;
    }
    if(out.white > 0)
    {
        out.x = sum_x / out.white;
        out.y = sum_y / out.white;
    }
    return out;
}

int ring_monitor_y(int second_check)
{
    if(second_check)
    {
        return ((RAW_H - 1) * (k_ring_second_find_pos_den - k_ring_second_find_pos_num)) /
               k_ring_second_find_pos_den;
    }
    return ((RAW_H - 1) * (k_ring_first_find_pos_den - k_ring_first_find_pos_num)) /
           k_ring_first_find_pos_den;
}

double boundary_line_degree_like_reference(const boundary_t *bd, int left_boundary, int start_y, int end_y)
{
    (void)left_boundary;
    int line[RAW_H];
    int valid[RAW_H];
    for(int i = 0; i < RAW_H; ++i)
    {
        line[i] = 0;
        valid[i] = 0;
    }

    if(bd != nullptr)
    {
        for(int i = 0; i < bd->original_step; ++i)
        {
            const point_t p = bd->original_pts[i];
            if(p.y >= 0 && p.y < RAW_H && p.x >= 0 && p.x < RAW_W)
            {
                line[p.y] = p.x;
                valid[p.y] = 1;
            }
        }
    }

    start_y = clip_i(start_y, 0, RAW_H - 1);
    end_y = clip_i(end_y, 0, RAW_H - 1);
    if(start_y <= end_y)
    {
        return 0.0;
    }

    double sum_y = 0.0;
    double sum_x = 0.0;
    double sum_y2 = 0.0;
    double sum_x2 = 0.0;
    double sum_yx = 0.0;
    int count = 0;
    for(int y = start_y; y > end_y; --y)
    {
        if(!valid[y])
        {
            continue;
        }
        const double yy = (double)y;
        const double xx = (double)line[y];
        sum_y += yy;
        sum_x += xx;
        sum_y2 += yy * yy;
        sum_x2 += xx * xx;
        sum_yx += yy * xx;
        count++;
    }

    if(count < k_ring_degree_min_rows)
    {
        return 0.0;
    }

    const double n = (double)count;
    const double numerator = n * sum_yx - sum_y * sum_x;
    const double denom_y = n * sum_y2 - sum_y * sum_y;
    const double denom_x = n * sum_x2 - sum_x * sum_x;
    const double denom = std::sqrt(denom_y * denom_x);
    if(denom <= 1e-9)
    {
        return 0.0;
    }
    return numerator / denom;
}

int boundary_degree_ok_like_reference(const boundary_t *bd,
                                      int left_boundary,
                                      int start_y,
                                      double threshold)
{
    const double degree = boundary_line_degree_like_reference(bd,
                                                             left_boundary,
                                                             start_y,
                                                             k_ring_degree_end_y);
    return std::fabs(degree) > threshold;
}

int check_ring_like_reference(const runtime_t *rt, int mode)
{
    if(rt == nullptr)
    {
        return RING_KIND_NONE;
    }

    const int second_check = (mode == RING_KIND_LEFT || mode == RING_KIND_RIGHT);
    const int monitor_y = ring_monitor_y(second_check);
    const int draw_close = second_check ? 1 : 0;
    const int right_x = RAW_W - 2 - draw_close;
    const int left_x = 1;
    const ring_scan_t rcr = ring_scan_line_blank(rt->gray,
                                                 right_x,
                                                 monitor_y - k_ring_find_line_len,
                                                 right_x,
                                                 monitor_y);
    const ring_scan_t lcr = ring_scan_line_blank(rt->gray,
                                                 left_x,
                                                 monitor_y - k_ring_find_line_len,
                                                 left_x,
                                                 monitor_y);
    const ring_scan_t middle = ring_scan_line_blank(rt->gray,
                                                   0,
                                                   k_ring_forward_line,
                                                   RAW_W - 1,
                                                   k_ring_forward_line);
    const int cf = MID_X - middle.x;

    if(!second_check)
    {
        if(std::abs(cf) >= k_ring_first_cf_max ||
           middle.x <= 0 ||
           middle.proportion <= k_ring_first_mid_min)
        {
            return RING_KIND_NONE;
        }

        if(rcr.proportion > k_ring_first_side_min &&
           lcr.proportion == 0.0 &&
           boundary_degree_ok_like_reference(&rt->track.left,
                                             1,
                                             k_ring_degree_first_start_y,
                                             k_ring_first_line_degree))
        {
            return RING_KIND_RIGHT;
        }
        if(lcr.proportion > k_ring_first_side_min &&
           rcr.proportion == 0.0 &&
           boundary_degree_ok_like_reference(&rt->track.right,
                                             0,
                                             k_ring_degree_first_start_y,
                                             k_ring_first_line_degree))
        {
            return RING_KIND_LEFT;
        }
        return RING_KIND_NONE;
    }

    if(std::abs(cf) >= k_ring_second_cf_max || middle.x == -1)
    {
        return RING_KIND_NONE;
    }

    if(mode == RING_KIND_RIGHT &&
       rcr.proportion > k_ring_second_side_min &&
       lcr.proportion == 0.0 &&
       boundary_degree_ok_like_reference(&rt->track.left,
                                         1,
                                         k_ring_degree_second_start_y,
                                         k_ring_second_line_degree))
    {
        return RING_KIND_RIGHT;
    }
    if(mode == RING_KIND_LEFT &&
       lcr.proportion > k_ring_second_side_min &&
       rcr.proportion == 0.0 &&
       boundary_degree_ok_like_reference(&rt->track.right,
                                         0,
                                         k_ring_degree_second_start_y,
                                         k_ring_second_line_degree))
    {
        return RING_KIND_LEFT;
    }
    return RING_KIND_NONE;
}

void clear_ring_pending(ring_state_t &ring)
{
    ring.pending_kind = RING_KIND_NONE;
    ring.pending_stage = 0;
    ring.pending_encoder0 = 0;
}

void enter_confirmed_ring(ring_state_t &ring, int kind)
{
    ring.kind = kind;
    ring.state = RING_STATE_BEGIN;
    clear_ring_pending(ring);
    ring.lost_count = 0;
    ring.have_count = 0;
    ring.encoder0 = 0;
}

void enter_false_ring_suppression(ring_state_t &ring)
{
    ring.pending_kind = RING_KIND_NONE;
    ring.pending_stage = k_ring_pending_false_wait_first;
}

int ring_pending_straight_ok(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }
    if(rt->ring.pending_kind == RING_KIND_LEFT)
    {
        return boundary_degree_ok_like_reference(&rt->track.right,
                                                 0,
                                                 k_ring_degree_first_start_y,
                                                 k_ring_first_line_degree);
    }
    if(rt->ring.pending_kind == RING_KIND_RIGHT)
    {
        return boundary_degree_ok_like_reference(&rt->track.left,
                                                 1,
                                                 k_ring_degree_first_start_y,
                                                 k_ring_first_line_degree);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      环岛过程中重算左右边界角点：raw 边界 -> IPM/pass-through -> 平滑 -> 重采样 -> 角点刷新
//  @return     void
//  @note       用于环岛内部补边或截断边界后，刷新检测/状态连续所需角点；不发布当前帧控制中线。
//-------------------------------------------------------------------------------------------------------------------
void refresh_ring_corners(runtime_t *rt, int has_matrix)
{
    if(rt == nullptr)
    {
        return;
    }

    double left_rpts[POINT_MAX][2] = {};
    double right_rpts[POINT_MAX][2] = {};
    double left_blur[POINT_MAX][2] = {};
    double right_blur[POINT_MAX][2] = {};
    double left_sample[POINT_MAX][2] = {};
    double right_sample[POINT_MAX][2] = {};
    int left_num = perspective_points(rt->track.left.original_pts,
                                      rt->track.left.original_step,
                                      rt->matrix,
                                      has_matrix,
                                      left_rpts);
    int right_num = perspective_points(rt->track.right.original_pts,
                                       rt->track.right.original_step,
                                       rt->matrix,
                                       has_matrix,
                                       right_rpts);
    int left_blur_num = 0;
    int right_blur_num = 0;
    int left_sample_num = 0;
    int right_sample_num = 0;
    blur_points(left_rpts, left_num, left_blur, &left_blur_num);
    blur_points(right_rpts, right_num, right_blur, &right_blur_num);
    resample_points(left_blur, left_blur_num, left_sample, &left_sample_num, 3);
    resample_points(right_blur, right_blur_num, right_sample, &right_sample_num, 3);
    refresh_boundary_corners(&rt->track.left,
                             &rt->track.right,
                             left_sample,
                             left_sample_num,
                             right_sample,
                             right_sample_num,
                             rt->matrix,
                             has_matrix);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      入环阶段为检测/状态连续补对侧边界：清空 opp，再找种子、跟踪、直线补点、拼接尾段
//  @return     int          1 成功补出对侧边界 / 0 seed、trace 或点数不足
//  @note       只供 ring_process() 内部更新 boundary_t 与角点状态；mainline 不用这条补线生成当前帧控制中线。
//-------------------------------------------------------------------------------------------------------------------
int build_ring_opp_for_detection(runtime_t &rt,
                                 const boundary_t &cur,
                                 boundary_t &opp,
                                 int left,
                                 int has_matrix)
{
    std::memset(&opp, 0, sizeof(opp));

    trace_t tr = {};
    int opp_left = 1;
    if(left)
    {
        opp_left = 0;
    }
    int best_i = 0;
    int best_v = -1;
    point_t seed = {10, START_HIGH};
    if(!opp_left)
    {
        seed.x = RAW_W - 11;
    }

    if(cur.original_step > 0)
    {
        best_i = 0;
        best_v = -1;
        // 在当前边界点里挑补线种子：评分 v = dx*dy，取最靠对侧外缘(dx)且最靠车头底部(dy)的点。
        // dx 左环用 x、右环用 RAW_W-x，含义都是"离对侧那条边的水平距离"。
        for(int i = 0; i < cur.original_step; ++i)
        {
            const int x = cur.original_pts[i].x;
            const int y = cur.original_pts[i].y;
            int dx = RAW_W - x;
            if(left)
            {
                dx = x;
            }
            const int dy = RAW_H - y;
            const int v = dx * dy;
            if(v > best_v)
            {
                best_v = v;
                best_i = i;
            }
        }
        seed = cur.original_pts[best_i];
        if(left)
        {
            seed.x = clip_i(seed.x + k_seed_dx, 1, RAW_W - 2);
        }
        else
        {
            seed.x = clip_i(seed.x - k_seed_dx, 1, RAW_W - 2);
        }
        seed.y = clip_i(seed.y - k_seed_dy, 1, RAW_H - 2);
    }

    point_t p0 = {-1, -1};
    if(!find_column_seed(rt.gray, seed, &p0))
    {
        return 0;
    }
    if(!trace_single(rt.gray, p0, opp_left, &tr))
    {
        return 0;
    }
    if(tr.step <= 3)
    {
        return 0;
    }

    const int step = tr.step;
    best_i = step - 1;
    best_v = -1;
    // 在补线 trace 上挑拼接点：评分 v = dx*dy*dy，dy 取平方放大"靠上方/远处"的权重，
    // 让拼接点偏向远端，避免补线在近处就接死。dx 含义同上（到对侧的水平距离）。
    for(int i = 0; i < step; ++i)
    {
        const int x = tr.pts[i].x;
        const int y = tr.pts[i].y;
        int dx = RAW_W - x;
        if(left)
        {
            dx = x;
        }
        const int dy = y;
        const int v = dx * dy * dy;
        if(v > best_v)
        {
            best_v = v;
            best_i = i;
        }
    }

    const int w = ROAD_HALF_WIDTH * 2;
    // 无边界点时的补点起点用稳定几何中心 MID_X(而非跟随的 mid_position)，避免动态中心污染环岛对称补点：左环补右边，右环补左边。
    int x0 = clip_i(MID_X - w / 2, 3, RAW_W - 4);
    if(left)
    {
        x0 = clip_i(MID_X + w / 2, 3, RAW_W - 4);
    }
    int y0 = START_HIGH;
    if(cur.original_step > 0)
    {
        if(left)
        {
            x0 = clip_i(cur.original_pts[0].x + w, 3, RAW_W - 4);
        }
        else
        {
            x0 = clip_i(cur.original_pts[0].x - w, 3, RAW_W - 4);
        }
    }

    const int x1 = tr.pts[best_i].x;
    const int y1 = tr.pts[best_i].y;

    point_t pts[POINT_MAX];
    int num = 0;
    const int dx = x1 - x0;
    const int dy = y1 - y0;
    const int n = clip_i(std::max(std::abs(dx), std::abs(dy)), 1, POINT_MAX);
    for(int i = 0; i <= n && num < POINT_MAX; ++i)
    {
        const double t = (double)i / n;
        const double x = x0 + dx * t;
        const double y = y0 + dy * t;
        const int px = clip_i(round_i(x), 0, RAW_W - 1);
        const int py = clip_i(round_i(y), 0, RAW_H - 1);
        if(num > 0 && pts[num - 1].x == px && pts[num - 1].y == py)
        {
            continue;
        }
        pts[num].x = px;
        pts[num].y = py;
        num++;
    }
    if(num > 0 && best_i < step &&
       pts[num - 1].x == tr.pts[best_i].x &&
       pts[num - 1].y == tr.pts[best_i].y)
    {
        best_i++;
    }
    for(int i = best_i; i < step && num < POINT_MAX; ++i)
    {
        pts[num] = tr.pts[i];
        num++;
    }

    opp.original_step = num;
    std::memcpy(opp.original_pts, pts, num * sizeof(point_t));
    trace_t opp_tr = {};
    opp_tr.step = clip_i(opp.original_step, 0, POINT_MAX);
    for(int i = 0; i < opp_tr.step; ++i)
    {
        opp_tr.pts[i] = opp.original_pts[i];
    }
    build_boundary_from_trace(&opp_tr, rt.matrix, has_matrix, &opp);
    return opp.original_step > 0;
}

// 复位环岛状态机。
void ring_reset(ring_state_t &ring)
{
    std::memset(&ring, 0, sizeof(ring));
}

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      环岛状态机入口：NONE(pending 二次确认) -> BEGIN -> IN -> RUN -> OUT -> END
//  @return     void
//  @note       kind 为 NONE 时只做参考版入口确认，不发布环岛动作；IN 阶段补对侧边界；RUN/OUT/END 按角点、直线和近线长度退出。
//-------------------------------------------------------------------------------------------------------------------
void ring_process(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }

    if(rt->ring.kind == RING_KIND_NONE)
    {
        if(rt->cross.state != CROSS_STATE_NONE)
        {
            clear_ring_pending(rt->ring);
            return;
        }

        if(rt->ring.pending_stage == k_ring_pending_false_wait_first)
        {
            if(rt->encoder_total - rt->ring.pending_encoder0 >= k_ring_first_confirm_encoder)
            {
                rt->ring.pending_stage = k_ring_pending_false_wait_exit;
                rt->ring.pending_encoder0 = rt->encoder_total;
            }
            return;
        }

        if(rt->ring.pending_stage == k_ring_pending_false_wait_exit)
        {
            if(rt->encoder_total - rt->ring.pending_encoder0 >= k_ring_false_exit_encoder)
            {
                clear_ring_pending(rt->ring);
            }
            return;
        }

        if(rt->ring.pending_stage == k_ring_pending_first)
        {
            if(rt->encoder_total - rt->ring.pending_encoder0 < k_ring_first_confirm_encoder)
            {
                if(!ring_pending_straight_ok(rt))
                {
                    enter_false_ring_suppression(rt->ring);
                }
                return;
            }
            rt->ring.pending_stage = k_ring_pending_second;
            rt->ring.pending_encoder0 = rt->encoder_total;
            return;
        }

        if(rt->ring.pending_stage == k_ring_pending_second)
        {
            if(rt->encoder_total - rt->ring.pending_encoder0 >= k_ring_second_confirm_encoder)
            {
                clear_ring_pending(rt->ring);
                return;
            }

            const int confirmed = check_ring_like_reference(rt, rt->ring.pending_kind);
            if(confirmed == rt->ring.pending_kind)
            {
                enter_confirmed_ring(rt->ring, confirmed);
            }
            return;
        }

        const int first = check_ring_like_reference(rt, RING_KIND_NONE);
        if(first == RING_KIND_LEFT || first == RING_KIND_RIGHT)
        {
            rt->ring.pending_kind = first;
            rt->ring.pending_stage = k_ring_pending_first;
            rt->ring.pending_encoder0 = rt->encoder_total;
        }
        return;
    }

    int left = 0;
    if(rt->ring.kind == RING_KIND_LEFT)
    {
        left = 1;
    }

    // cur = 当前贴住的边界，opp = 需要补出来的对侧边界：左环贴左补右，右环贴右补左。
    boundary_t *cur = &rt->track.right;
    boundary_t *opp = &rt->track.left;
    if(left)
    {
        cur = &rt->track.left;
        opp = &rt->track.right;
    }

    const int has_matrix = rt->has_matrix;
    const int64_t enc = rt->encoder_total;
    if(rt->ring.state == RING_STATE_BEGIN)
    {
        const int step = cur->now_step;
        if(step < k_lost_step)
        {
            rt->ring.lost_count++;
        }
        if(step > k_have_step && rt->ring.lost_count > k_lost_confirm_n)
        {
            rt->ring.have_count++;
            if(rt->ring.have_count > k_have_confirm_n)
            {
                rt->ring.lost_count = 0;
                rt->ring.have_count = 0;
                rt->ring.encoder0 = enc;
                rt->ring.state = RING_STATE_IN;
            }
        }
        return;
    }

    if(rt->ring.state == RING_STATE_IN)
    {
        const int step = cur->now_step;
        const int64_t denc = enc - rt->ring.encoder0;
        if(step < k_in_lost_step || denc >= k_in_encoder_step)
        {
            rt->ring.state = RING_STATE_RUN;
            rt->ring.lost_count = 0;
            rt->ring.have_count = 0;
            return;
        }
        if(build_ring_opp_for_detection(*rt, *cur, *opp, left, has_matrix))
        {
            refresh_ring_corners(rt, has_matrix);
        }
        return;
    }

    if(rt->ring.state == RING_STATE_RUN)
    {
        if(opp->l_ok)
        {
            const int i0 = opp->l_now_index;
            const int raw_i = opp->l_original_index;
            opp->original_step = clip_i(raw_i + 1, 1, opp->original_step);
            trace_t opp_tr = {};
            opp_tr.step = clip_i(opp->original_step, 0, POINT_MAX);
            for(int i = 0; i < opp_tr.step; ++i)
            {
                opp_tr.pts[i] = opp->original_pts[i];
            }
            build_boundary_from_trace(&opp_tr, rt->matrix, has_matrix, opp);
            refresh_ring_corners(rt, has_matrix);
            if(i0 >= 0 && i0 < k_run_corner_step)
            {
                rt->ring.state = RING_STATE_OUT;
                rt->ring.lost_count = 0;
                rt->ring.have_count = 0;
            }
        }
        return;
    }

    if(rt->ring.state == RING_STATE_OUT)
    {
        if(boundary_is_straight(opp))
        {
            rt->ring.state = RING_STATE_END;
            rt->ring.lost_count = 0;
            rt->ring.have_count = 0;
            return;
        }
        rt->ring.lost_count = 0;
        rt->ring.have_count = 0;
        return;
    }

    if(rt->ring.state == RING_STATE_END)
    {
        const int step = cur->now_step;
        int lost_n = k_end_right_exit_lost_n;
        if(left)
        {
            lost_n = k_end_left_exit_lost_n;
        }
        if(step < k_lost_step)
        {
            rt->ring.lost_count++;
        }
        if(step > k_have_step && rt->ring.lost_count > lost_n)
        {
            ring_reset(rt->ring);
            return;
        }
        return;
    }
    ring_reset(rt->ring);
}
