#include "mainline.hpp"

#include "cross.hpp"
#include "clip.hpp"
#include "element.hpp"
#include "imgproc.hpp"
#include "perspective.hpp"
#include "boundary.hpp"
#include "zebra.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

// 当前帧是否有可用于控制的中线。
int track_line_found(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }
    if(rt->track.track_type == TRACK_TYPE_NONE)
    {
        return 0;
    }
    if(rt->track.reject_reason != TRACK_REJECT_NONE)
    {
        return 0;
    }
    if(rt->track.mid.step <= 0)
    {
        return 0;
    }
    return 1;
}

namespace
{
const int k_mid_resample_dist = 3;     // 中线重采样步长，单位 工作坐标像素
const int k_min_border_step = 6;       // 生成有效中线所需的最小点数
const int k_dual_min_step = 12;        // 左右都达到此点数才算"两边都够长"
const double k_lookahead_min = 15.0;   // 预瞄距离下限，单位 累计弧长像素
const double k_lookahead_max = 80.0;   // 预瞄距离上限，单位 累计弧长像素
// 主入口直接写清每帧顺序，短函数只保留真实算法段。

double rpts0[POINT_MAX][2] = {};
double rpts1[POINT_MAX][2] = {};
double rpts0b[POINT_MAX][2] = {};
double rpts1b[POINT_MAX][2] = {};
double rpts0s[POINT_MAX][2] = {};
double rpts1s[POINT_MAX][2] = {};

int rpts0_num = 0;
int rpts1_num = 0;
int rpts0b_num = 0;
int rpts1b_num = 0;
int rpts0s_num = 0;
int rpts1s_num = 0;

int track_type_keep = TRACK_TYPE_RIGHT;

double lookahead_error(midline_t *mid, int look, point_t ref);

// 左右种子分别爬线；失败的一侧清掉，避免后面继续拿旧点算边界。
int trace_edges(runtime_t *rt, int *use_matrix)
{
    if(rt == nullptr || use_matrix == nullptr)
    {
        return 0;
    }

    int pair_ok = seed_pair_accepted(&rt->seeds, rt->seed_state);
    *use_matrix = 0;
    if(rt->has_matrix)
    {
        *use_matrix = 1;
    }

    int has_left_seed = 0;
    if(rt->seed_state & 1)
    {
        if(rt->seeds.left.x >= 0 && rt->seeds.left.x < RAW_W &&
           rt->seeds.left.y >= 0 && rt->seeds.left.y < RAW_H)
        {
            has_left_seed = 1;
        }
    }

    int has_right_seed = 0;
    if(rt->seed_state & 2)
    {
        if(rt->seeds.right.x >= 0 && rt->seeds.right.x < RAW_W &&
           rt->seeds.right.y >= 0 && rt->seeds.right.y < RAW_H)
        {
            has_right_seed = 1;
        }
    }

    std::memset(&rt->left_trace, 0, sizeof(rt->left_trace));
    std::memset(&rt->right_trace, 0, sizeof(rt->right_trace));
    rt->left_trace.left_side = 1;

    int left_ok = 0;
    if(has_left_seed)
    {
        left_ok = trace_single(rt->gray, rt->seeds.left, 1, &rt->left_trace);
    }

    int right_ok = 0;
    if(has_right_seed)
    {
        right_ok = trace_single(rt->gray, rt->seeds.right, 0, &rt->right_trace);
    }

    if(!left_ok)
    {
        std::memset(&rt->left_trace, 0, sizeof(rt->left_trace));
        rt->left_trace.left_side = 1;
        rt->seed_state &= ~1;
        rt->seeds.left = {-1, -1};
    }
    if(!right_ok)
    {
        std::memset(&rt->right_trace, 0, sizeof(rt->right_trace));
        rt->seed_state &= ~2;
        rt->seeds.right = {-1, -1};
    }
    pair_ok = seed_pair_accepted(&rt->seeds, rt->seed_state);
    if(!pair_ok)
    {
        rt->seeds.width = 0;
    }

    if(rt->left_trace.step <= 0 && rt->right_trace.step <= 0)
    {
        rt->track.reject_reason = TRACK_REJECT_TRACE_FILTERED;
        return 0;
    }
    return 1;
}

// 清零本文件内用于中线计算的点列长度。
void clear_rpts()
{
    rpts0_num = 0;
    rpts1_num = 0;
    rpts0b_num = 0;
    rpts1b_num = 0;
    rpts0s_num = 0;
    rpts1s_num = 0;
}

// 十字 IN 阶段求控制中线：
// 输入：cross_evolve() 写入的 track_type、远线点列、远线 L 点，以及本帧近线 rpts0s/rpts1s。
// 输出：rt->track.mid，坐标语义是 IPM/控制坐标，不是原图显示坐标。
// 规则：只用远线 L 点后面的远线单边外扩；远线 L 点不可用时直接失败，不回近线兜底。
int solve_cross_mid(runtime_t *rt, point_t ref)
{
    if(rt == nullptr)
    {
        return 0;
    }
    if(rt->cross.state != CROSS_STATE_IN)
    {
        return 0;
    }

    const int t = rt->cross.track_type;
    if(t == TRACK_TYPE_LEFT)
    {
        int far_ok = 0;
        if(rt->cross.left_far_found)
        {
            if(rt->cross.left_num >= k_min_border_step && rt->cross.left_l >= 0)
            {
                far_ok = 1;
            }
        }

        if(far_ok)
        {
            int start = rt->cross.left_l;
            if(start < 0)
            {
                start = 0;
            }
            if(start < rt->cross.left_num)
            {
                const int num = clip_i(rt->cross.left_num - start, 0, POINT_MAX);
                if(num >= k_min_border_step)
                {
                    return track_leftline_from_start(rt->cross.left_pts + start,
                                                     num,
                                                     ROAD_HALF_WIDTH,
                                                     ref.x,
                                                     ref.y,
                                                     &rt->track.mid);
                }
            }
        }
        return 0;
    }
    if(t == TRACK_TYPE_RIGHT)
    {
        int far_ok = 0;
        if(rt->cross.right_far_found)
        {
            if(rt->cross.right_num >= k_min_border_step && rt->cross.right_l >= 0)
            {
                far_ok = 1;
            }
        }

        if(far_ok)
        {
            int start = rt->cross.right_l;
            if(start < 0)
            {
                start = 0;
            }
            if(start < rt->cross.right_num)
            {
                const int num = clip_i(rt->cross.right_num - start, 0, POINT_MAX);
                if(num >= k_min_border_step)
                {
                    return track_rightline_from_start(rt->cross.right_pts + start,
                                                      num,
                                                      ROAD_HALF_WIDTH,
                                                      ref.x,
                                                      ref.y,
                                                      &rt->track.mid);
                }
            }
        }
        return 0;
    }
    return 0;
}

// 斑马线按参考 garage 语义选扫描中线：
// 只有单侧 L 点时才查；左 L 用右边线外扩中线，右 L 用左边线外扩中线。
int build_zebra_mid(runtime_t *rt, point_t ref, midline_t *mid)
{
    if(rt == nullptr || mid == nullptr)
    {
        return 0;
    }

    std::memset(mid, 0, sizeof(*mid));
    if(rt->track.left.l_ok && !rt->track.right.l_ok)
    {
        return track_rightline(rpts1s,
                               rpts1s_num,
                               ROAD_HALF_WIDTH,
                               ref.x,
                               ref.y,
                               mid);
    }
    if(!rt->track.left.l_ok && rt->track.right.l_ok)
    {
        return track_leftline(rpts0s,
                              rpts0s_num,
                              ROAD_HALF_WIDTH,
                              ref.x,
                              ref.y,
                              mid);
    }
    return 0;
}

// 左边线工作点列：原图点 -> IPM/pass-through -> 平滑 -> 等距重采样。
void build_rpts0(const point_t *pts, int num, const double matrix[9], int use_matrix)
{
    if(pts == nullptr || num <= 0)
    {
        return;
    }

    rpts0_num = perspective_points(pts, num, matrix, use_matrix, rpts0);
    if(rpts0_num <= 0)
    {
        return;
    }
    blur_points(rpts0, rpts0_num, rpts0b, &rpts0b_num);
    resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, k_mid_resample_dist);
}

// 右边线工作点列：原图点 -> IPM/pass-through -> 平滑 -> 等距重采样。
void build_rpts1(const point_t *pts, int num, const double matrix[9], int use_matrix)
{
    if(pts == nullptr || num <= 0)
    {
        return;
    }

    rpts1_num = perspective_points(pts, num, matrix, use_matrix, rpts1);
    if(rpts1_num <= 0)
    {
        return;
    }
    blur_points(rpts1, rpts1_num, rpts1b, &rpts1b_num);
    resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, k_mid_resample_dist);
}

// 普通巡线选边：
// 输入：左右边线经过 IPM、平滑、重采样后的 rpts0s/rpts1s 点数。
// 输出：TRACK_TYPE_LEFT/RIGHT/NONE。参考主线只有左右单边两种 track_type，双边都够长时沿用上一帧单边。
// 注意：普通巡线不主动切 TRACK_TYPE_DUAL；track_dualline() 只保留为明确实验入口。
int pick_track_type()
{
    // 一侧点数不到另一侧一半、且绝对值也短(< 60 点)：判该侧明显丢线，跟长的一侧。
    int left_short = 0;
    if(rpts0s_num < rpts1s_num / 2)
    {
        if(rpts0s_num < 60)
        {
            left_short = 1;
        }
    }

    int right_short = 0;
    if(rpts1s_num < rpts0s_num / 2)
    {
        if(rpts1s_num < 60)
        {
            right_short = 1;
        }
    }

    if(left_short)
    {
        return TRACK_TYPE_RIGHT;
    }
    if(right_short)
    {
        return TRACK_TYPE_LEFT;
    }

    // 一侧极短(< 20 点)且比另一侧还短：同样判该侧不可靠，跟另一侧。
    int left_less = 0;
    if(rpts0s_num < 20)
    {
        if(rpts1s_num > rpts0s_num)
        {
            left_less = 1;
        }
    }

    int right_less = 0;
    if(rpts1s_num < 20)
    {
        if(rpts0s_num > rpts1s_num)
        {
            right_less = 1;
        }
    }

    if(left_less)
    {
        return TRACK_TYPE_RIGHT;
    }
    if(right_less)
    {
        return TRACK_TYPE_LEFT;
    }

    // 两侧都够长(>= k_dual_min_step)：不主动切双边，沿用上一帧单边选择(track_type_keep)。
    int left_enough = rpts0s_num >= k_dual_min_step;
    int right_enough = rpts1s_num >= k_dual_min_step;
    if(left_enough && right_enough)
    {
        if(track_type_keep == TRACK_TYPE_LEFT)
        {
            return TRACK_TYPE_LEFT;
        }
        return TRACK_TYPE_RIGHT;
    }
    // 只有一侧达到最小点数：跟那一侧；两侧都不够则本帧无可用单边线。
    if(rpts0s_num >= k_min_border_step)
    {
        return TRACK_TYPE_LEFT;
    }
    if(rpts1s_num >= k_min_border_step)
    {
        return TRACK_TYPE_RIGHT;
    }
    return TRACK_TYPE_NONE;
}

// 在控制中线上取最接近 look 的点，输出相对参考点的角度误差，单位 degree。
double lookahead_error(midline_t *mid, int look, point_t ref)
{
    if(mid == nullptr || mid->step <= 0)
    {
        return 0.0;
    }

    int best_i = 0;
    int best_d = 1 << 30;
    look = clip_i(look, (int)k_lookahead_min, (int)k_lookahead_max);
    for(int i = 0; i < mid->step; ++i)
    {
        if(mid->dist[i] <= 0)
        {
            continue;
        }
        int d = std::abs(mid->dist[i] - look);
        if(d < best_d)
        {
            best_d = d;
            best_i = i;
        }
    }

    double dx = mid->pts[best_i].x - ref.x;
    double dy = ref.y - mid->pts[best_i].y;
    double err = std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
    return err;
}

// 搜索中心跟随的路宽基准限幅，对齐 imgproc 的 kSeedMinWidth/kSeedMaxWidth 语义。
const int k_width_base_min = 10;
const int k_width_base_max = RAW_W - ROAD_HALF_WIDTH;
const int k_center_margin = 1;  // mid_position 写回留白，落在 find_seeds 读取校验 [0,RAW_W) 内

// 用本帧 seed 结果更新下一帧起搜中心(mid_position)：
//  - 全失：直接返回，保持上一帧中心(Front_Car 语义，勿学 TC264 重置回中点)。
//  - 双边(两侧 bit 都置位)：中心取左右中点，即使宽度超出成对区间(如十字开口处
//    左右远边相距过宽)也优于单边外推；width_base 仅在常态且合法成对时低通标定。
//  - 单边：用 width_base 把已知侧外推出虚拟中心，让中心随外圈平移。
void update_search_center(runtime_t *rt, int seed_ok)
{
    if(rt == nullptr || !seed_ok)
    {
        return;
    }
    int mid = rt->mid_position;
    if((rt->seed_state & 3) == 3)
    {
        mid = (rt->seeds.left.x + rt->seeds.right.x) / 2;
        if(rt->ring.kind == RING_KIND_NONE && rt->cross.state == CROSS_STATE_NONE &&
           seed_pair_accepted(&rt->seeds, rt->seed_state))
        {
            const int wb = clip_i(rt->seeds.width, k_width_base_min, k_width_base_max);
            rt->width_base = (rt->width_base * 3 + wb) / 4;
        }
    }
    else if(rt->seed_state & 1)
    {
        mid = rt->seeds.left.x + rt->width_base / 2;
    }
    else if(rt->seed_state & 2)
    {
        mid = rt->seeds.right.x - rt->width_base / 2;
    }
    rt->mid_position = clip_i(mid, k_center_margin, RAW_W - 1 - k_center_margin);
}

} // namespace

// 清空巡线状态，恢复默认控制中心和几何中心。
void tracking_reset(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }
    std::memset(rt, 0, sizeof(*rt));
    rt->has_matrix = 0;
    rt->control_center_x = CONTROL_CENTER_X;
    rt->mid_position = MID_X;
    rt->width_base = ROAD_HALF_WIDTH * 2;
    track_type_keep = TRACK_TYPE_RIGHT;
}

// 当前帧主巡线流程：seed -> trace -> boundary/element -> midline -> guide_error。
int tracking_process_frame(runtime_t *rt)
{
    if(rt == nullptr || !rt->gray_valid)
    {
        return 0;
    }

    std::memset(&rt->track, 0, sizeof(rt->track));
    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.track_type = TRACK_TYPE_NONE;
    rt->track.center_x = -1;
    std::memset(&rt->seeds, 0, sizeof(rt->seeds));
    std::memset(&rt->left_trace, 0, sizeof(rt->left_trace));
    std::memset(&rt->right_trace, 0, sizeof(rt->right_trace));

    int normal_ok = 0;
    // 本帧开始前已在 IN，才允许本帧直接走远线；刚从 BEGIN 切 IN 的帧仍走截短近线。
    int cross_in0 = 0;
    if(rt->cross.state == CROSS_STATE_IN)
    {
        cross_in0 = 1;
    }
    int seed_ok = find_seeds(rt->gray,
                             START_HIGH,
                             &rt->mid_position,
                             &rt->seed_state,
                             &rt->seeds);
    // 搜索中心跟随：用本帧 seed 结果更新下一帧起搜中心(全失则保持上一帧)。
    update_search_center(rt, seed_ok);
    if(!seed_ok)
    {
        if(rt->cross.state != CROSS_STATE_IN)
        {
            rt->track.reject_reason = TRACK_REJECT_NO_SEED;
            return 0;
        }
        // CROSS_IN 按参考版继续寻远线；这不是普通巡线 fallback。
        clear_rpts();
        cross_process(rt);
    }
    else
    {
        int use_matrix = 0;
        if(!trace_edges(rt, &use_matrix))
        {
            if(rt->cross.state != CROSS_STATE_IN)
            {
                return 0;
            }
            // 近线 trace 全断时，CROSS_IN 仍要继续 cross_farline。
            clear_rpts();
            cross_process(rt);
        }
        else
        {
            build_boundary_from_trace(&rt->left_trace, rt->matrix, use_matrix, &rt->track.left);
            build_boundary_from_trace(&rt->right_trace, rt->matrix, use_matrix, &rt->track.right);
            clear_rpts();
            build_rpts0(rt->track.left.original_pts,
                        clip_i(rt->track.left.original_step, 0, POINT_MAX),
                        rt->matrix,
                        use_matrix);
            build_rpts1(rt->track.right.original_pts,
                        clip_i(rt->track.right.original_step, 0, POINT_MAX),
                        rt->matrix,
                        use_matrix);
            refresh_boundary_corners(&rt->track.left,
                                     &rt->track.right,
                                     rpts0s,
                                     rpts0s_num,
                                     rpts1s,
                                     rpts1s_num,
                                     rt->matrix,
                                     use_matrix);
            const int cross_state0 = rt->cross.state;
            element_process(rt);
            // 对齐参考 run_cross()：BEGIN 先截 rpts0s/rpts1s，随后才可能切进 CROSS_IN。
            if(rt->cross.state != CROSS_STATE_NONE)
            {
                if(cross_state0 == CROSS_STATE_NONE || cross_state0 == CROSS_STATE_BEGIN)
                {
                    rpts0s_num = clip_i(rt->track.left.now_step, 0, rpts0s_num);
                    rpts1s_num = clip_i(rt->track.right.now_step, 0, rpts1s_num);
                }
            }
            normal_ok = 1;
        }

    }

    point_t ref = {rt->control_center_x, START_HIGH};
    // 十字态对齐 RT1064：不为中线过短停车，夹取可用点列即可（BEGIN 截短近线也放行）。
    const int in_cross = (rt->cross.state != CROSS_STATE_NONE);
    if(cross_in0 && rt->cross.state == CROSS_STATE_IN)
    {
        const int track_type = rt->cross.track_type;
        if(track_type == TRACK_TYPE_NONE)
        {
            rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
            return 0;
        }
        const int mid_ok = solve_cross_mid(rt, ref);
        // 十字态对齐 RT1064：放宽最小点数门，不为中线过短停车。
        if(mid_ok < (in_cross ? 3 : k_min_border_step))
        {
            rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
            return 0;
        }
        // 十字态对齐 RT1064：跳过前瞻硬停，直接用现有点列算 guide_error（lookahead_error 内部已 clip）。
        if(!in_cross && !midline_has_lookahead(&rt->track.mid, LOOKAHEAD_DIST))
        {
            rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
            return 0;
        }
        rt->track.reject_reason = TRACK_REJECT_NONE;
        rt->track.track_type = track_type;
        rt->track.center_x = rt->track.mid.pts[0].x;
        rt->track.guide_error = lookahead_error(&rt->track.mid, LOOKAHEAD_DIST, ref);
        zebra_process(rt, nullptr);
        return 1;
    }
    if(!normal_ok)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }

    int track_type = TRACK_TYPE_NONE;
    if(rt->ring.kind != RING_KIND_NONE)
    {
        int left_ring = 0;
        if(rt->ring.kind == RING_KIND_LEFT)
        {
            left_ring = 1;
        }

        // 对齐参考版 circle.c：BEGIN/RUN/END 跟外圈，IN/OUT 跟内圈。
        // 左环：右(外) -> 左(内) -> 右(外) -> 左(内) -> 右(外)
        // 右环：左(外) -> 右(内) -> 左(外) -> 右(内) -> 左(外)
        if(rt->ring.state == RING_STATE_BEGIN ||
           rt->ring.state == RING_STATE_RUN ||
           rt->ring.state == RING_STATE_END)
        {
            if(left_ring)
            {
                track_type = TRACK_TYPE_RIGHT;
            }
            else
            {
                track_type = TRACK_TYPE_LEFT;
            }
        }
        else if(rt->ring.state == RING_STATE_IN ||
                rt->ring.state == RING_STATE_OUT)
        {
            if(left_ring)
            {
                track_type = TRACK_TYPE_LEFT;
            }
            else
            {
                track_type = TRACK_TYPE_RIGHT;
            }
        }
    }
    else
    {
        track_type = pick_track_type();
    }
    if(track_type == TRACK_TYPE_NONE)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }

    int mid_ok = 0;
    if(track_type == TRACK_TYPE_LEFT)
    {
        mid_ok = track_leftline(rpts0s,
                                rpts0s_num,
                                ROAD_HALF_WIDTH,
                                ref.x,
                                ref.y,
                                &rt->track.mid);
    }
    else if(track_type == TRACK_TYPE_RIGHT)
    {
        mid_ok = track_rightline(rpts1s,
                                 rpts1s_num,
                                 ROAD_HALF_WIDTH,
                                 ref.x,
                                 ref.y,
                                 &rt->track.mid);
    }
    if(mid_ok < (in_cross ? 3 : k_min_border_step))
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }
    // 十字态对齐 RT1064：BEGIN 截短近线产出的中线也放行，不为前瞻不足停车。
    if(!in_cross && !midline_has_lookahead(&rt->track.mid, LOOKAHEAD_DIST))
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }
    rt->track.track_type = track_type;
    if(track_type == TRACK_TYPE_LEFT || track_type == TRACK_TYPE_RIGHT)
    {
        track_type_keep = track_type;
    }
    rt->track.center_x = rt->track.mid.pts[0].x;
    rt->track.guide_error = lookahead_error(&rt->track.mid, LOOKAHEAD_DIST, ref);
    midline_t zebra_mid = {};
    const midline_t *zebra_scan = nullptr;
    if(build_zebra_mid(rt, ref, &zebra_mid) >= k_min_border_step)
    {
        zebra_scan = &zebra_mid;
    }
    zebra_process(rt, zebra_scan);
    return 1;
}
