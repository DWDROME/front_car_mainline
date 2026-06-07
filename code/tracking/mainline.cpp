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
const int k_pair_max_y_diff = 8;        // 左右工作点配对时允许的 y 近邻误差
const int k_pair_min_count = 10;        // 最小可判定配对数；不足则不拒绝
const double k_lookahead_min = 15.0;   // 预瞄距离下限，单位 累计弧长像素
const double k_lookahead_max = 80.0;   // 预瞄距离上限，单位 累计弧长像素
// RT1064 误差计算使用 0.2m 前向偏置。当前 ROAD_HALF_WIDTH 约对应 0.225m，
// 因此 0.2m 近似为 ROAD_HALF_WIDTH * 8/9。
const double k_error_forward_bias = ROAD_HALF_WIDTH * 8.0 / 9.0;
// 主入口直接写清每帧顺序，短函数只保留真实算法段。
//
// RT1064 点列命名对照：
//   rpts0/rpts1     raw 边界经过 IPM/pass-through 后的左右工作点列
//   rpts0b/rpts1b   左右工作点列的平滑结果
//   rpts0s/rpts1s   左右平滑点列的等距重采样结果，也是角点/选边输入
//   rptsc0/rptsc1   由左/右边界单边外扩得到的候选控制中线
// 最终只发布 rt->track.mid；上述数组是本文件内的当前帧中间点列。

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

void clear_rpts();
void build_rpts0(const point_t *pts, int num, const double matrix[9], int use_matrix);
void build_rpts1(const point_t *pts, int num, const double matrix[9], int use_matrix);
int pick_track_type();
int work_pair_order_ok(const double left[POINT_MAX][2],
                       int left_num,
                       const double right[POINT_MAX][2],
                       int right_num);
int solve_cross_mid(runtime_t *rt, point_t ref);
int build_zebra_scan_midline(runtime_t *rt, point_t ref, midline_t *mid);
double lookahead_error(midline_t *mid, int look, point_t ref);
point_t control_ref_point(const runtime_t *rt);

struct frame_action_t
{
    int cross_state0 = CROSS_STATE_NONE;
    int ring_kind0 = RING_KIND_NONE;
    int ordinary_track_type = TRACK_TYPE_NONE;
    int ring_track_type = TRACK_TYPE_NONE;
    int ring_frame_start_crop_side = TRACK_TYPE_NONE;
    int ring_frame_start_crop_index = -1;
    int base_candidates_ready = 0;
};

struct frame_mode_t
{
    int cross_far = 0;
    int cross_near = 0;
    int ring_active = 0;
    int element_action = 0;
    int work_track_type = TRACK_TYPE_NONE;
};

void reset_frame_tracking_state(runtime_t *rt)
{
    std::memset(&rt->track, 0, sizeof(rt->track));
    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.track_type = TRACK_TYPE_NONE;
    rt->track.center_x = -1;
    std::memset(&rt->seeds, 0, sizeof(rt->seeds));
    std::memset(&rt->left_trace, 0, sizeof(rt->left_trace));
    std::memset(&rt->right_trace, 0, sizeof(rt->right_trace));
}

int build_frame_boundaries_and_candidates(runtime_t *rt, int use_matrix)
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
    if(!work_pair_order_ok(rpts0s, rpts0s_num, rpts1s, rpts1s_num))
    {
        rt->track.trace_identity_reject |= TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS;
        rt->track.reject_reason = TRACK_REJECT_TRACE_FILTERED;
        std::memset(&rt->track.left, 0, sizeof(rt->track.left));
        std::memset(&rt->track.right, 0, sizeof(rt->track.right));
        clear_rpts();
        return TRACK_TYPE_NONE;
    }
    refresh_boundary_corners(&rt->track.left,
                             &rt->track.right,
                             rpts0s,
                             rpts0s_num,
                             rpts1s,
                             rpts1s_num,
                             rt->matrix,
                             use_matrix);

    const int ordinary_track_type = pick_track_type();
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
    return ordinary_track_type;
}

void snapshot_ring_frame_start_action(runtime_t *rt, frame_action_t *action)
{
    if(action == nullptr || rt->ring.kind == RING_KIND_NONE)
    {
        return;
    }

    const int left_ring = (rt->ring.kind == RING_KIND_LEFT);
    if(rt->ring.state == RING_STATE_BEGIN ||
       rt->ring.state == RING_STATE_RUN ||
       rt->ring.state == RING_STATE_END)
    {
        action->ring_track_type = left_ring ? TRACK_TYPE_RIGHT : TRACK_TYPE_LEFT;
    }
    else if(rt->ring.state == RING_STATE_IN ||
            rt->ring.state == RING_STATE_OUT)
    {
        action->ring_track_type = left_ring ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;
    }

    if(rt->ring.state == RING_STATE_RUN)
    {
        if(rt->ring.kind == RING_KIND_LEFT && rt->track.right.l_ok)
        {
            action->ring_frame_start_crop_side = TRACK_TYPE_RIGHT;
            action->ring_frame_start_crop_index = rt->track.right.l_now_index;
        }
        else if(rt->ring.kind == RING_KIND_RIGHT && rt->track.left.l_ok)
        {
            action->ring_frame_start_crop_side = TRACK_TYPE_LEFT;
            action->ring_frame_start_crop_index = rt->track.left.l_now_index;
        }
    }
}

int ring_track_type_from_current_state(const runtime_t *rt)
{
    if(rt == nullptr || rt->ring.kind == RING_KIND_NONE)
    {
        return TRACK_TYPE_NONE;
    }

    const int left_ring = (rt->ring.kind == RING_KIND_LEFT);
    if(rt->ring.state == RING_STATE_BEGIN ||
       rt->ring.state == RING_STATE_RUN ||
       rt->ring.state == RING_STATE_END)
    {
        return left_ring ? TRACK_TYPE_RIGHT : TRACK_TYPE_LEFT;
    }
    if(rt->ring.state == RING_STATE_IN ||
       rt->ring.state == RING_STATE_OUT)
    {
        return left_ring ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;
    }
    return TRACK_TYPE_NONE;
}

frame_mode_t classify_frame_mode(runtime_t *rt, const frame_action_t *action)
{
    frame_mode_t mode = {};
    mode.cross_far =
        (action->cross_state0 == CROSS_STATE_IN && rt->cross.state == CROSS_STATE_IN);
    mode.cross_near =
        (action->base_candidates_ready &&
         !mode.cross_far &&
         action->cross_state0 != CROSS_STATE_NONE &&
         rt->cross.state != CROSS_STATE_NONE);
    mode.ring_active =
        (action->base_candidates_ready &&
         !mode.cross_far &&
         !mode.cross_near &&
         action->ring_kind0 != RING_KIND_NONE &&
         rt->ring.kind != RING_KIND_NONE);

    if(mode.cross_far)
    {
        mode.work_track_type = rt->cross.track_type;
    }
    else if(mode.cross_near)
    {
        mode.work_track_type = action->ordinary_track_type;
    }
    else if(mode.ring_active)
    {
        if(action->ring_track_type != TRACK_TYPE_NONE)
        {
            mode.work_track_type = action->ring_track_type;
        }
        else
        {
            mode.work_track_type = ring_track_type_from_current_state(rt);
        }
    }
    else
    {
        mode.work_track_type = action->ordinary_track_type;
    }

    mode.element_action = mode.cross_far || mode.cross_near || mode.ring_active;
    return mode;
}

void apply_frame_start_element_crop(runtime_t *rt, const frame_mode_t *mode, const frame_action_t *action)
{
    if(mode->cross_near)
    {
        rptsc0_num = clip_i(rt->track.left.now_step, 0, rptsc0_num);
        rptsc1_num = clip_i(rt->track.right.now_step, 0, rptsc1_num);
    }

    if(mode->ring_active && action->ring_frame_start_crop_index >= 0)
    {
        if(action->ring_frame_start_crop_side == TRACK_TYPE_LEFT)
        {
            rptsc0_num = clip_i(action->ring_frame_start_crop_index, 0, rptsc0_num);
        }
        else if(action->ring_frame_start_crop_side == TRACK_TYPE_RIGHT)
        {
            rptsc1_num = clip_i(action->ring_frame_start_crop_index, 0, rptsc1_num);
        }
    }
}

int build_selected_midline(runtime_t *rt, const frame_mode_t *mode, point_t ref)
{
    if(mode->cross_far)
    {
        return solve_cross_mid(rt, ref);
    }
    if(mode->work_track_type == TRACK_TYPE_LEFT)
    {
        return build_rptsn(rptsc0, rptsc0_num, ref.x, ref.y, 0, &rt->track.mid);
    }
    if(mode->work_track_type == TRACK_TYPE_RIGHT)
    {
        return build_rptsn(rptsc1, rptsc1_num, ref.x, ref.y, 0, &rt->track.mid);
    }
    return 0;
}

void trace_x_range(const trace_t *trace, int *min_x, int *max_x)
{
    if(min_x == nullptr || max_x == nullptr)
    {
        return;
    }
    *min_x = RAW_W;
    *max_x = -1;
    if(trace == nullptr)
    {
        return;
    }
    for(int i = 0; i < trace->step; ++i)
    {
        *min_x = std::min(*min_x, trace->pts[i].x);
        *max_x = std::max(*max_x, trace->pts[i].x);
    }
    if(trace->step <= 0)
    {
        *min_x = -1;
        *max_x = -1;
    }
}

int traces_cross_on_same_row(const trace_t *left, const trace_t *right)
{
    if(left == nullptr || right == nullptr || left->step <= 0 || right->step <= 0)
    {
        return 0;
    }

    int left_x[RAW_H];
    int right_x[RAW_H];
    for(int y = 0; y < RAW_H; ++y)
    {
        left_x[y] = -1;
        right_x[y] = RAW_W;
    }
    for(int i = 0; i < left->step; ++i)
    {
        const int y = left->pts[i].y;
        if(y >= 0 && y < RAW_H)
        {
            left_x[y] = std::max(left_x[y], left->pts[i].x);
        }
    }
    for(int i = 0; i < right->step; ++i)
    {
        const int y = right->pts[i].y;
        if(y >= 0 && y < RAW_H)
        {
            right_x[y] = std::min(right_x[y], right->pts[i].x);
        }
    }
    for(int y = 0; y < RAW_H; ++y)
    {
        if(left_x[y] >= 0 && right_x[y] < RAW_W && left_x[y] >= right_x[y])
        {
            return 1;
        }
    }
    return 0;
}

int trace_identity_reject_bits(const runtime_t *rt, int left_ok, int right_ok)
{
    if(rt == nullptr)
    {
        return TRACE_IDENTITY_REJECT_NONE;
    }

    int reject = TRACE_IDENTITY_REJECT_NONE;
    int left_min = -1;
    int left_max = -1;
    int right_min = -1;
    int right_max = -1;
    trace_x_range(&rt->left_trace, &left_min, &left_max);
    trace_x_range(&rt->right_trace, &right_min, &right_max);

    if(left_ok && (rt->seed_state & 2) && rt->seeds.right.x >= 0 && left_max >= rt->seeds.right.x)
    {
        reject |= TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED;
    }
    if(right_ok && (rt->seed_state & 1) && rt->seeds.left.x >= 0 && right_min <= rt->seeds.left.x)
    {
        reject |= TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED;
    }
    if(left_ok && right_ok && traces_cross_on_same_row(&rt->left_trace, &rt->right_trace))
    {
        reject |= TRACE_IDENTITY_REJECT_ROW_CROSS;
    }
    return reject;
}

int publish_track_result(runtime_t *rt, const frame_mode_t *mode, int mid_ok, point_t ref)
{
    const int min_mid_step = mode->element_action ? k_element_min_mid_step : k_min_border_step;
    const int require_lookahead = !mode->element_action;
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
    rt->track.track_type = mode->work_track_type;
    if(mode->work_track_type == TRACK_TYPE_LEFT || mode->work_track_type == TRACK_TYPE_RIGHT)
    {
        track_type_keep = mode->work_track_type;
    }
    rt->track.center_x = rt->track.mid.pts[0].x;
    rt->track.guide_error = lookahead_error(&rt->track.mid, LOOKAHEAD_DIST, ref);
    return 1;
}

void run_zebra_scan(runtime_t *rt, point_t ref, int cross_far_frame)
{
    midline_t zebra_mid = {};
    const midline_t *zebra_scan = nullptr;
    if(!cross_far_frame && build_zebra_scan_midline(rt, ref, &zebra_mid) >= k_min_border_step)
    {
        zebra_scan = &zebra_mid;
    }
    zebra_process(rt, zebra_scan);
}

// 左右种子分别爬线；失败的一侧清掉，避免后面继续拿旧点算边界。
int trace_edges(runtime_t *rt, int *use_matrix)
{
    if(rt == nullptr || use_matrix == nullptr)
    {
        return 0;
    }

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

    const int identity_reject = trace_identity_reject_bits(rt, left_ok, right_ok);
    rt->track.trace_identity_reject = identity_reject;
    if(identity_reject & TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED)
    {
        left_ok = 0;
    }
    if(identity_reject & TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED)
    {
        right_ok = 0;
    }
    if(identity_reject & TRACE_IDENTITY_REJECT_ROW_CROSS)
    {
        left_ok = 0;
        right_ok = 0;
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

    rt->track.cross_mid_side = rt->cross.track_type;
    rt->track.cross_mid_fail = CROSS_MID_FAIL_NONE;
    rt->track.cross_mid_start = -1;
    rt->track.cross_mid_tail = 0;
    rt->track.cross_mid_cand = 0;
    rt->track.cross_mid_out = 0;

    if(rt->cross.state != CROSS_STATE_IN)
    {
        rt->track.cross_mid_fail = CROSS_MID_FAIL_NOT_IN;
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
            rt->track.cross_mid_start = start;
            if(start < rt->cross.left_num)
            {
                const int num = clip_i(rt->cross.left_num - start, 0, POINT_MAX);
                rt->track.cross_mid_tail = num;
                if(num >= k_element_min_mid_step)
                {
                    double far_cand[POINT_MAX][2] = {};
                    const int cand_num = track_leftline(rt->cross.left_pts + start,
                                                        num,
                                                        far_cand,
                                                        k_track_approx_num,
                                                        ROAD_HALF_WIDTH);
                    rt->track.cross_mid_cand = cand_num;
                    if(cand_num <= 0)
                    {
                        rt->track.cross_mid_fail = CROSS_MID_FAIL_OFFSET;
                        return 0;
                    }
                    const int out = build_rptsn(far_cand,
                                                cand_num,
                                                ref.x,
                                                ref.y,
                                                1,
                                                &rt->track.mid);
                    rt->track.cross_mid_out = out;
                    if(out <= 0)
                    {
                        rt->track.cross_mid_fail = CROSS_MID_FAIL_BUILD;
                    }
                    return out;
                }
                rt->track.cross_mid_fail = CROSS_MID_FAIL_SHORT_TAIL;
                return 0;
            }
            rt->track.cross_mid_fail = CROSS_MID_FAIL_BAD_START;
            return 0;
        }
        rt->track.cross_mid_fail = CROSS_MID_FAIL_NO_FAR;
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
            rt->track.cross_mid_start = start;
            if(start < rt->cross.right_num)
            {
                const int num = clip_i(rt->cross.right_num - start, 0, POINT_MAX);
                rt->track.cross_mid_tail = num;
                if(num >= k_element_min_mid_step)
                {
                    double far_cand[POINT_MAX][2] = {};
                    const int cand_num = track_rightline(rt->cross.right_pts + start,
                                                         num,
                                                         far_cand,
                                                         k_track_approx_num,
                                                         ROAD_HALF_WIDTH);
                    rt->track.cross_mid_cand = cand_num;
                    if(cand_num <= 0)
                    {
                        rt->track.cross_mid_fail = CROSS_MID_FAIL_OFFSET;
                        return 0;
                    }
                    const int out = build_rptsn(far_cand,
                                                cand_num,
                                                ref.x,
                                                ref.y,
                                                1,
                                                &rt->track.mid);
                    rt->track.cross_mid_out = out;
                    if(out <= 0)
                    {
                        rt->track.cross_mid_fail = CROSS_MID_FAIL_BUILD;
                    }
                    return out;
                }
                rt->track.cross_mid_fail = CROSS_MID_FAIL_SHORT_TAIL;
                return 0;
            }
            rt->track.cross_mid_fail = CROSS_MID_FAIL_BAD_START;
            return 0;
        }
        rt->track.cross_mid_fail = CROSS_MID_FAIL_NO_FAR;
        return 0;
    }
    rt->track.cross_mid_fail = CROSS_MID_FAIL_NO_SIDE;
    return 0;
}

// 斑马线按参考 garage 语义选扫描中线：
// 只有单侧 L 点时才查；左 L 用右边线外扩中线，右 L 用左边线外扩中线。
int build_zebra_scan_midline(runtime_t *rt, point_t ref, midline_t *mid)
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

// 双侧工作点顺序复核：只在当前帧配对点足够时查左右反序，不查宽度、不补线。
int work_pair_order_ok(const double left[POINT_MAX][2],
                       int left_num,
                       const double right[POINT_MAX][2],
                       int right_num)
{
    if(left == nullptr || right == nullptr)
    {
        return 1;
    }
    if(left_num < k_dual_min_step || right_num < k_dual_min_step)
    {
        return 1;
    }

    int pair_count = 0;
    int bad_order = 0;
    for(int i = 0; i < left_num; ++i)
    {
        if(left[i][0] < 0.0 || left[i][1] < 0.0)
        {
            continue;
        }

        int best = -1;
        double best_dy = k_pair_max_y_diff + 1.0;
        for(int j = 0; j < right_num; ++j)
        {
            if(right[j][0] < 0.0 || right[j][1] < 0.0)
            {
                continue;
            }
            const double dy = std::fabs(left[i][1] - right[j][1]);
            if(dy < best_dy)
            {
                best_dy = dy;
                best = j;
            }
        }
        if(best < 0 || best_dy > k_pair_max_y_diff)
        {
            continue;
        }

        if(left[i][0] >= right[best][0])
        {
            bad_order = 1;
        }
        ++pair_count;
    }

    if(pair_count < k_pair_min_count)
    {
        return 1;
    }
    return !bad_order;
}

// 在控制中线上取最接近 look 的点，按 RT1064 的纯跟踪误差形式输出角度误差，单位 degree。
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
    double dy = ref.y - mid->pts[best_i].y + k_error_forward_bias;
    double err = -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
    return err;
}

// 对齐 RT1064：有 IPM 时，控制中线归一化起点来自 raw 车轮点映射后的 IPM 点，
// 而不是 seed 起线行。查表失败或 raw pass-through 模式下才回退到当前硬件标定值。
point_t control_ref_point(const runtime_t *rt)
{
    point_t ref = {CONTROL_CENTER_X, START_HIGH};
    if(rt != nullptr)
    {
        ref.x = rt->control_center_x;
    }

    const int raw_x = RAW_W / 2;
    const int raw_y = static_cast<int>(RAW_H * 0.78F);
    double ix = 0.0;
    double iy = 0.0;
    if(rt != nullptr && rt->has_matrix &&
       perspective_lookup_raw_to_ipm(raw_x, raw_y, &ix, &iy))
    {
        ref.x = clip_i(static_cast<int>(std::lround(ix)), 0, IPM_W - 1);
        ref.y = clip_i(static_cast<int>(std::lround(iy)), 0, IPM_H - 1);
    }
    return ref;
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
            const int span = rt->seeds.right.x - rt->seeds.left.x;
            const int wb = clip_i(span, k_width_base_min, k_width_base_max);
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

// 当前帧主巡线流程：
//   seed -> trace -> rpts0s/rpts1s -> rptsc0/rptsc1
//   -> element_process() 更新元素状态
//   -> 帧首 action 选择/裁剪候选中线
//   -> build_rptsn() 归一化为 rt->track.mid
//   -> guide_error / zebra scan
// 注意：元素状态机只决定选边、裁剪或 CROSS_IN 远线；最终控制中线只从这里发布。
int tracking_process_frame(runtime_t *rt)
{
    if(rt == nullptr || !rt->gray_valid)
    {
        return 0;
    }

    reset_frame_tracking_state(rt);

    // 动作所有者：本帧动作只依据帧首已成立的元素状态计算；element_process 推进状态机后，
    // 新阶段留到下一帧才生效，避免"同帧改状态又用新状态"造成的时序错位。
    frame_action_t action = {};
    action.cross_state0 = rt->cross.state;
    action.ring_kind0 = rt->ring.kind;

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
            action.ordinary_track_type = build_frame_boundaries_and_candidates(rt, use_matrix);
            if(rt->track.trace_identity_reject & TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS)
            {
                if(rt->cross.state != CROSS_STATE_IN)
                {
                    return 0;
                }
                // 反序近线已被清掉；CROSS_IN 只允许十字远线流程继续。
                clear_rpts();
                cross_process(rt);
            }
            else
            {
                snapshot_ring_frame_start_action(rt, &action);
                element_process(rt);
                action.base_candidates_ready = 1;
            }
        }

    }

    point_t ref = control_ref_point(rt);
    const frame_mode_t mode = classify_frame_mode(rt, &action);
    rt->track.action_cross_state0 = action.cross_state0;
    rt->track.action_base_ready = action.base_candidates_ready;
    rt->track.mode_cross_far = mode.cross_far;
    rt->track.mode_cross_near = mode.cross_near;
    rt->track.mode_ring_active = mode.ring_active;
    rt->track.mode_work_track_type = mode.work_track_type;
    rt->track.control_ref = ref;

    if(!action.base_candidates_ready && !mode.cross_far)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }

    apply_frame_start_element_crop(rt, &mode, &action);

    if(mode.work_track_type == TRACK_TYPE_NONE)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }

    const int mid_ok = build_selected_midline(rt, &mode, ref);
    if(!publish_track_result(rt, &mode, mid_ok, ref))
    {
        return 0;
    }

    run_zebra_scan(rt, ref, mode.cross_far);
    return 1;
}
