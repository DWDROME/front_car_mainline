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
const int k_track_approx_num = 5;      // 单边外扩时用前后各 5 个点估计切向

// 元素帧(十字/环岛)允许短中线继续输出；普通帧仍按 k_min_border_step + 前瞻硬停。
const int k_element_min_mid_step = 3;  // 元素态允许的最短有效中线点数
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
double rptsc0[POINT_MAX][2] = {};
double rptsc1[POINT_MAX][2] = {};

int rpts0_num = 0;
int rpts1_num = 0;
int rpts0b_num = 0;
int rpts1b_num = 0;
int rpts0s_num = 0;
int rpts1s_num = 0;
int rptsc0_num = 0;
int rptsc1_num = 0;

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
    rptsc0_num = 0;
    rptsc1_num = 0;
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
                if(num >= k_element_min_mid_step)
                {
                    double far_cand[POINT_MAX][2] = {};
                    const int cand_num = track_leftline(rt->cross.left_pts + start,
                                                        num,
                                                        far_cand,
                                                        k_track_approx_num,
                                                        ROAD_HALF_WIDTH);
                    return build_rptsn(far_cand,
                                       cand_num,
                                       ref.x,
                                       ref.y,
                                       1,
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
                if(num >= k_element_min_mid_step)
                {
                    double far_cand[POINT_MAX][2] = {};
                    const int cand_num = track_rightline(rt->cross.right_pts + start,
                                                         num,
                                                         far_cand,
                                                         k_track_approx_num,
                                                         ROAD_HALF_WIDTH);
                    return build_rptsn(far_cand,
                                       cand_num,
                                       ref.x,
                                       ref.y,
                                       1,
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
        return build_rptsn(rptsc1, rptsc1_num, ref.x, ref.y, 0, mid);
    }
    if(!rt->track.left.l_ok && rt->track.right.l_ok)
    {
        return build_rptsn(rptsc0, rptsc0_num, ref.x, ref.y, 0, mid);
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

// 用本帧追线成功后保留下来的 seed 结果更新下一帧起搜中心(mid_position)：
//  - 全失：直接返回，保持上一帧中心(Front_Car 语义，勿学 TC264 重置回中点)。
//  - 双边(两侧 bit 都置位)：中心取左右中点，即使宽度超出成对区间(如十字开口处
//    左右远边相距过宽)也优于单边外推；width_base 仅在常态且合法成对时低通标定。
//  - 单边：用 width_base 把已知侧外推出虚拟中心，让中心随外圈平移。
void update_search_center(runtime_t *rt)
{
    if(rt == nullptr)
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

    // 动作所有者：本帧动作只依据帧首已成立的元素状态计算；element_process 推进状态机后，
    // 新阶段留到下一帧才生效，避免"同帧改状态又用新状态"造成的时序错位。
    const int cross_state0 = rt->cross.state;
    int normal_ok = 0;
    int ordinary_track_type0 = TRACK_TYPE_NONE;
    int ring_track_type0 = TRACK_TYPE_NONE;
    int ring_run_crop_side0 = TRACK_TYPE_NONE;
    int ring_run_crop_index0 = -1;

    int seed_ok = find_seeds(rt->gray,
                             START_HIGH,
                             &rt->mid_position,
                             &rt->seed_state,
                             &rt->seeds);
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
            // 搜索中心跟随：只用本帧追线成功后保留下来的 seed 结果更新下一帧起搜中心。
            update_search_center(rt);
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
            ordinary_track_type0 = pick_track_type();
            rptsc0_num = track_leftline(rpts0s,
                                        rpts0s_num,
                                        rptsc0,
                                        k_track_approx_num,
                                        ROAD_HALF_WIDTH);
            rptsc1_num = track_rightline(rpts1s,
                                         rpts1s_num,
                                         rptsc1,
                                         k_track_approx_num,
                                         ROAD_HALF_WIDTH);
            // ring_process() 会推进状态；这里先把本帧要走的 side/crop 算成动作值。
            if(rt->ring.kind != RING_KIND_NONE)
            {
                const int left_ring = (rt->ring.kind == RING_KIND_LEFT);
                if(rt->ring.state == RING_STATE_BEGIN ||
                   rt->ring.state == RING_STATE_RUN ||
                   rt->ring.state == RING_STATE_END)
                {
                    ring_track_type0 = left_ring ? TRACK_TYPE_RIGHT : TRACK_TYPE_LEFT;
                }
                else if(rt->ring.state == RING_STATE_IN ||
                        rt->ring.state == RING_STATE_OUT)
                {
                    ring_track_type0 = left_ring ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;
                }

                if(rt->ring.state == RING_STATE_RUN)
                {
                    if(rt->ring.kind == RING_KIND_LEFT && rt->track.right.l_ok)
                    {
                        ring_run_crop_side0 = TRACK_TYPE_RIGHT;
                        ring_run_crop_index0 = rt->track.right.l_now_index;
                    }
                    else if(rt->ring.kind == RING_KIND_RIGHT && rt->track.left.l_ok)
                    {
                        ring_run_crop_side0 = TRACK_TYPE_LEFT;
                        ring_run_crop_index0 = rt->track.left.l_now_index;
                    }
                }
            }
            element_process(rt);
            normal_ok = 1;
        }

    }

    point_t ref = {rt->control_center_x, START_HIGH};
    // 把本帧归为三类元素动作帧，决定中线来源与 reject 门：
    //   cross_far  : 帧首已在 CROSS_IN，本帧走远线 farline；
    //   cross_near : 十字 BEGIN，或同帧刚 BEGIN->IN，本帧仍走截短近线；
    //   ring       : 环岛态，按状态选内/外圈（下方用帧首算好的动作值选边）。
    const int cross_far_frame =
        (cross_state0 == CROSS_STATE_IN && rt->cross.state == CROSS_STATE_IN);
    const int cross_near_frame =
        (normal_ok && !cross_far_frame && rt->cross.state != CROSS_STATE_NONE);

    // 同帧 BEGIN -> IN 仍走截短近线；只有帧开始已是 CROSS_IN 才走远线。
    if(cross_near_frame)
    {
        rptsc0_num = clip_i(rt->track.left.now_step, 0, rptsc0_num);
        rptsc1_num = clip_i(rt->track.right.now_step, 0, rptsc1_num);
    }

    const int ring_active_frame =
        (normal_ok &&
         !cross_far_frame &&
         !cross_near_frame &&
         (ring_track_type0 != TRACK_TYPE_NONE || rt->ring.kind != RING_KIND_NONE));

    if(!normal_ok && !cross_far_frame)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }

    int work_track_type = TRACK_TYPE_NONE;

    if(cross_far_frame)
    {
        work_track_type = rt->cross.track_type;
    }
    else if(cross_near_frame)
    {
        work_track_type = ordinary_track_type0;
    }
    else if(ring_active_frame)
    {
        if(ring_track_type0 != TRACK_TYPE_NONE)
        {
            work_track_type = ring_track_type0;
        }
        else if(rt->ring.kind != RING_KIND_NONE)
        {
            // 本帧才新进入 ring（帧首未算 ring_track_type0）时，用推进后的 ring 状态补选边。
            const int left_ring = (rt->ring.kind == RING_KIND_LEFT);
            if(rt->ring.state == RING_STATE_BEGIN ||
               rt->ring.state == RING_STATE_RUN ||
               rt->ring.state == RING_STATE_END)
            {
                work_track_type = left_ring ? TRACK_TYPE_RIGHT : TRACK_TYPE_LEFT;
            }
            else if(rt->ring.state == RING_STATE_IN ||
                    rt->ring.state == RING_STATE_OUT)
            {
                work_track_type = left_ring ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;
            }
        }
    }
    else
    {
        work_track_type = ordinary_track_type0;
    }

    if(ring_active_frame && ring_run_crop_index0 >= 0)
    {
        if(ring_run_crop_side0 == TRACK_TYPE_LEFT)
        {
            rptsc0_num = clip_i(ring_run_crop_index0, 0, rptsc0_num);
        }
        else if(ring_run_crop_side0 == TRACK_TYPE_RIGHT)
        {
            rptsc1_num = clip_i(ring_run_crop_index0, 0, rptsc1_num);
        }
    }

    if(work_track_type == TRACK_TYPE_NONE)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }

    int mid_ok = 0;
    if(cross_far_frame)
    {
        mid_ok = solve_cross_mid(rt, ref);
    }
    else if(work_track_type == TRACK_TYPE_LEFT)
    {
        mid_ok = build_rptsn(rptsc0, rptsc0_num, ref.x, ref.y, 0, &rt->track.mid);
    }
    else if(work_track_type == TRACK_TYPE_RIGHT)
    {
        mid_ok = build_rptsn(rptsc1, rptsc1_num, ref.x, ref.y, 0, &rt->track.mid);
    }
    // 共同元素合同(对齐 RT1064)：十字/环岛元素态只要中线 >= k_element_min_mid_step 即放行，
    // 并跳过前瞻硬停（lookahead_error 内部已按可用弧长 clip）；普通道路仍需 >= k_min_border_step
    // 且满足前瞻，确保真正无线时照常停车。
    const int element_action_frame = cross_far_frame || cross_near_frame || ring_active_frame;
    const int min_mid_step = element_action_frame ? k_element_min_mid_step : k_min_border_step;
    const int require_lookahead = !element_action_frame;
    if(mid_ok < min_mid_step)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }
    if(require_lookahead && !midline_has_lookahead(&rt->track.mid, LOOKAHEAD_DIST))
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }
    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.track_type = work_track_type;
    if(work_track_type == TRACK_TYPE_LEFT || work_track_type == TRACK_TYPE_RIGHT)
    {
        track_type_keep = work_track_type;
    }
    rt->track.center_x = rt->track.mid.pts[0].x;
    rt->track.guide_error = lookahead_error(&rt->track.mid, LOOKAHEAD_DIST, ref);
    midline_t zebra_mid = {};
    const midline_t *zebra_scan = nullptr;
    if(!cross_far_frame && build_zebra_mid(rt, ref, &zebra_mid) >= k_min_border_step)
    {
        zebra_scan = &zebra_mid;
    }
    zebra_process(rt, zebra_scan);
    return 1;
}
