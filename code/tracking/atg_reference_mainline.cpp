#include "tracking/atg_reference_mainline.hpp"

#include "clip.hpp"
#include "atg_reference_step.h"

extern "C" {
#include "headfile.h"
}

#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{

int clip_track_type()
{
    return track_type == TRACK_LEFT ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;
}

int map_atg_cross_state()
{
    if(cross_type == CROSS_BEGIN)
    {
        return CROSS_STATE_BEGIN;
    }
    if(cross_type == CROSS_IN || cross_type == CROSS_HALF)
    {
        return CROSS_STATE_IN;
    }
    return CROSS_STATE_NONE;
}

int map_atg_ring_kind()
{
    if(round_type == ROUND_LEFT_BEGIN ||
       round_type == ROUND_LEFT_IN ||
       round_type == ROUND_LEFT_END)
    {
        return RING_KIND_LEFT;
    }
    if(round_type == ROUND_RIGHT_BEGIN ||
       round_type == ROUND_RIGHT_IN ||
       round_type == ROUND_RIGHT_END)
    {
        return RING_KIND_RIGHT;
    }
    switch(circle_type)
    {
    case CIRCLE_LEFT_BEGIN:
    case CIRCLE_LEFT_IN:
    case CIRCLE_LEFT_RUNNING:
    case CIRCLE_LEFT_OUT:
    case CIRCLE_LEFT_END:
        return RING_KIND_LEFT;
    case CIRCLE_RIGHT_BEGIN:
    case CIRCLE_RIGHT_IN:
    case CIRCLE_RIGHT_RUNNING:
    case CIRCLE_RIGHT_OUT:
    case CIRCLE_RIGHT_END:
        return RING_KIND_RIGHT;
    default:
        return RING_KIND_NONE;
    }
}

int map_atg_ring_state()
{
    switch(round_type)
    {
    case ROUND_LEFT_BEGIN:
    case ROUND_RIGHT_BEGIN:
        return RING_STATE_BEGIN;
    case ROUND_LEFT_IN:
    case ROUND_RIGHT_IN:
        return RING_STATE_IN;
    case ROUND_LEFT_END:
    case ROUND_RIGHT_END:
        return RING_STATE_END;
    default:
        break;
    }
    switch(circle_type)
    {
    case CIRCLE_LEFT_BEGIN:
    case CIRCLE_RIGHT_BEGIN:
        return RING_STATE_BEGIN;
    case CIRCLE_LEFT_IN:
    case CIRCLE_RIGHT_IN:
        return RING_STATE_IN;
    case CIRCLE_LEFT_RUNNING:
    case CIRCLE_RIGHT_RUNNING:
        return RING_STATE_RUN;
    case CIRCLE_LEFT_OUT:
    case CIRCLE_RIGHT_OUT:
        return RING_STATE_OUT;
    case CIRCLE_LEFT_END:
    case CIRCLE_RIGHT_END:
        return RING_STATE_END;
    default:
        return RING_STATE_BEGIN;
    }
}

void clear_track_result(runtime_t *rt)
{
    std::memset(&rt->track, 0, sizeof(rt->track));
    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.track_type = TRACK_TYPE_NONE;
    rt->track.center_x = -1;
    rt->track.control_ref = {-1, -1};
    rt->track.candidate_crop_side = TRACK_TYPE_NONE;
    rt->track.candidate_crop_index = -1;
    rt->track.ring_opp_left = -1;
    rt->track.ring_opp_l_index = -1;
    rt->track.search_update_kind = TRACK_SEARCH_UPDATE_NONE;
    rt->track.seed_left_find = {-1, -1};
    rt->track.seed_right_find = {-1, -1};
}

point_t atg_control_ref(const runtime_t *rt)
{
    point_t ref = {CONTROL_CENTER_X, START_HIGH};
    if(rt != nullptr)
    {
        ref.x = clip_i(rt->control_center_x, 0, RAW_W - 1);
    }
    return ref;
}

void copy_atg_midline(runtime_t *rt, point_t ref)
{
    midline_t *mid = &rt->track.mid;
    mid->step = std::min(rptsn_num, static_cast<int>(POINT_MAX));
    int last_x = ref.x;
    int last_y = ref.y;
    int dist = 0;
    for(int i = 0; i < mid->step; ++i)
    {
        const int x = clip_i(static_cast<int>(std::lround(rptsn[i][0])), 0, IPM_W - 1);
        const int y = clip_i(static_cast<int>(std::lround(rptsn[i][1])), 0, IPM_H - 1);
        mid->pts[i] = {x, y};
        if(i == 0)
        {
            mid->dist[i] = 0;
        }
        else
        {
            const double dx = static_cast<double>(x - last_x);
            const double dy = static_cast<double>(y - last_y);
            dist += static_cast<int>(std::lround(std::hypot(dx, dy)));
            mid->dist[i] = dist;
        }
        last_x = x;
        last_y = y;
    }
}

void copy_atg_boundary(boundary_t *bd,
                       const int raw_pts[][2],
                       int raw_num,
                       float work_pts[][2],
                       int work_num,
                       int l_found,
                       int l_index)
{
    if(bd == nullptr)
    {
        return;
    }
    std::memset(bd, 0, sizeof(*bd));

    bd->original_step = std::min(raw_num, static_cast<int>(POINT_MAX));
    for(int i = 0; i < bd->original_step; ++i)
    {
        bd->original_pts[i] = {raw_pts[i][0], raw_pts[i][1]};
    }

    bd->now_step = std::min(work_num, static_cast<int>(POINT_MAX));
    bd->work_step = bd->now_step;
    for(int i = 0; i < bd->now_step; ++i)
    {
        bd->work_pts[i][0] = work_pts[i][0];
        bd->work_pts[i][1] = work_pts[i][1];
        bd->now_pts[i] = {
            clip_i(static_cast<int>(std::lround(work_pts[i][0])), 0, IPM_W - 1),
            clip_i(static_cast<int>(std::lround(work_pts[i][1])), 0, IPM_H - 1),
        };
    }

    bd->l_found = l_found ? 1 : 0;
    bd->l_ok = bd->l_found;
    bd->l_now_index = l_found ? clip_i(l_index, 0, std::max(0, bd->now_step - 1)) : 0;
    bd->l_original_index = l_found ? clip_i(l_index, 0, std::max(0, bd->original_step - 1)) : 0;
}

double atg_lookahead_error(const midline_t *mid, point_t ref)
{
    if(mid == nullptr || mid->step <= 0)
    {
        return 0.0;
    }
    int best = 0;
    int best_err = 1 << 30;
    for(int i = 0; i < mid->step; ++i)
    {
        if(mid->dist[i] <= 0)
        {
            continue;
        }
        const int err = std::abs(mid->dist[i] - LOOKAHEAD_DIST);
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }
    const double dx = static_cast<double>(mid->pts[best].x - ref.x);
    const double dy = static_cast<double>(ref.y - mid->pts[best].y) + ROAD_HALF_WIDTH * 8.0 / 9.0;
    return -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
}

void copy_far_points(double out[][2], int *out_num, const float in[][2], int in_num)
{
    if(out == nullptr || out_num == nullptr)
    {
        return;
    }
    *out_num = std::min(in_num, static_cast<int>(POINT_MAX));
    for(int i = 0; i < *out_num; ++i)
    {
        out[i][0] = in[i][0];
        out[i][1] = in[i][1];
    }
}

void map_atg_element_state(runtime_t *rt)
{
    rt->cross.state = map_atg_cross_state();
    rt->cross.not_have_line = not_have_line;
    rt->cross.track_type = clip_track_type();
    rt->cross.left_far_found = far_Lpt0_found ? 1 : 0;
    rt->cross.right_far_found = far_Lpt1_found ? 1 : 0;
    rt->cross.left_l = far_Lpt0_found ? far_Lpt0_rpts0s_id : -1;
    rt->cross.right_l = far_Lpt1_found ? far_Lpt1_rpts1s_id : -1;
    rt->cross.left_near_step = rpts0s_num;
    rt->cross.right_near_step = rpts1s_num;
    rt->cross.both_near_lost = (rpts0s_num < 5 && rpts1s_num < 5) ? 1 : 0;
    rt->cross.both_near_recover = (rpts0s_num > 20 && rpts1s_num > 20) ? 1 : 0;
    rt->cross.left_far_ok = far_Lpt0_found && far_rpts0s_num > 0 ? 1 : 0;
    rt->cross.right_far_ok = far_Lpt1_found && far_rpts1s_num > 0 ? 1 : 0;
    rt->cross.exit_ready = (not_have_line > 2 && rpts0s_num > 20 && rpts1s_num > 20) ? 1 : 0;
    rt->cross.left_far_fail = far_rpts0s_num > 0 ? CROSS_FAR_FAIL_NONE : CROSS_FAR_FAIL_TRACE;
    rt->cross.right_far_fail = far_rpts1s_num > 0 ? CROSS_FAR_FAIL_NONE : CROSS_FAR_FAIL_TRACE;
    rt->cross.left_far_seed = {far_x11, far_y1};
    rt->cross.right_far_seed = {far_x11, far_y2};
    rt->cross.left_far_trace = far_ipts0_num;
    rt->cross.right_far_trace = far_ipts1_num;
    rt->cross.left_far_ipm = far_rpts0_num;
    rt->cross.right_far_ipm = far_rpts1_num;
    rt->cross.left_far_blur = far_rpts0b_num;
    rt->cross.right_far_blur = far_rpts1b_num;
    rt->cross.left_far_resample = far_rpts0s_num;
    rt->cross.right_far_resample = far_rpts1s_num;
    rt->cross.left_far_l_source = far_Lpt0_found ? CROSS_FAR_L_NEW : CROSS_FAR_L_NONE;
    rt->cross.right_far_l_source = far_Lpt1_found ? CROSS_FAR_L_NEW : CROSS_FAR_L_NONE;
    copy_far_points(rt->cross.left_pts, &rt->cross.left_num, far_rpts0s, far_rpts0s_num);
    copy_far_points(rt->cross.right_pts, &rt->cross.right_num, far_rpts1s, far_rpts1s_num);

    rt->ring.kind = map_atg_ring_kind();
    rt->ring.state = map_atg_ring_state();
    if(rt->ring.kind == RING_KIND_LEFT)
    {
        rt->ring.lost_count = none_left_line;
        rt->ring.have_count = have_left_line;
        rt->track.ring_opp_left = 1;
        rt->track.ring_cur_step = rpts0s_num;
        rt->track.ring_opp_step = rpts1s_num;
        rt->track.ring_opp_l_ok = Lpt1_found ? 1 : 0;
        rt->track.ring_opp_l_index = Lpt1_found ? Lpt1_rpts1s_id : -1;
        rt->track.ring_opp_build_result = Splicing_rightline_center_num;
    }
    else if(rt->ring.kind == RING_KIND_RIGHT)
    {
        rt->ring.lost_count = none_right_line;
        rt->ring.have_count = have_right_line;
        rt->track.ring_opp_left = 0;
        rt->track.ring_cur_step = rpts1s_num;
        rt->track.ring_opp_step = rpts0s_num;
        rt->track.ring_opp_l_ok = Lpt0_found ? 1 : 0;
        rt->track.ring_opp_l_index = Lpt0_found ? Lpt0_rpts0s_id : -1;
        rt->track.ring_opp_build_result = Splicing_leftline_center_num;
    }
    else
    {
        rt->ring.lost_count = 0;
        rt->ring.have_count = 0;
    }
}

} // namespace

int track_line_found(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }
    return rt->track.track_type != TRACK_TYPE_NONE &&
           rt->track.reject_reason == TRACK_REJECT_NONE &&
           rt->track.mid.step > 0;
}

int seed_pair_accepted(const seed_pair_t *sd, int state)
{
    if(sd == nullptr)
    {
        return 0;
    }
    if((state & 0x3) != 0x3)
    {
        return 0;
    }
    if(sd->left.y != sd->right.y)
    {
        return 0;
    }
    const int span = sd->right.x - sd->left.x;
    return span >= 10 && span <= RAW_W - ROAD_HALF_WIDTH;
}

int midline_has_forward_lookahead(const midline_t *midline, int aim_distance, int ref_y)
{
    if(midline == nullptr || midline->step <= 0)
    {
        return 0;
    }

    int best = -1;
    for(int i = 0; i < midline->step; ++i)
    {
        if(midline->dist[i] < aim_distance)
        {
            continue;
        }
        if(best < 0 || midline->dist[i] < midline->dist[best])
        {
            best = i;
        }
    }
    if(best < 0)
    {
        return 0;
    }
    return midline->pts[best].y < ref_y;
}

void tracking_reset(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }
    std::memset(rt, 0, sizeof(*rt));
    rt->control_center_x = CONTROL_CENTER_X;
    rt->mid_position = MID_X;
    rt->width_base = ROAD_HALF_WIDTH * 2;
    clear_track_result(rt);
    atg_reference_reset();
}

int tracking_process_frame(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }
    clear_track_result(rt);
    if(!rt->gray_valid)
    {
        rt->track.reject_reason = TRACK_REJECT_NO_SEED;
        return 0;
    }

    const int ok = atg_reference_process_frame(rt->gray, rt->encoder_total);
    map_atg_element_state(rt);
    copy_atg_boundary(&rt->track.left,
                      ipts0,
                      ipts0_num,
                      rpts0s,
                      rpts0s_num,
                      Lpt0_found ? 1 : 0,
                      Lpt0_rpts0s_id);
    copy_atg_boundary(&rt->track.right,
                      ipts1,
                      ipts1_num,
                      rpts1s,
                      rpts1s_num,
                      Lpt1_found ? 1 : 0,
                      Lpt1_rpts1s_id);
    rt->track.control_ref = atg_control_ref(rt);
    rt->track.track_type = clip_track_type();
    rt->track.action_cross_state0 = rt->cross.state;
    rt->track.action_ring_kind0 = rt->ring.kind;
    rt->track.action_ring_state0 = rt->ring.state;
    rt->track.mode_work_track_type = rt->track.track_type;
    rt->track.selected_mid_ok = ok ? rptsn_num : 0;
    rt->track.center_x = rt->track.control_ref.x;

    if(!ok)
    {
        rt->track.track_type = TRACK_TYPE_NONE;
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        return 0;
    }

    copy_atg_midline(rt, rt->track.control_ref);
    rt->track.guide_error = atg_lookahead_error(&rt->track.mid, rt->track.control_ref);
    return track_line_found(rt);
}
