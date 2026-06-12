#include "tracking/atg_reference_mainline.hpp"

#include "atg_reference_step.h"
#include "clip.hpp"

extern "C" {
#include "headfile.h"
}

#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{
point_t atg_control_ref(const runtime_t *rt)
{
    point_t ref = {CONTROL_CENTER_X, START_HIGH};
    if(rt != nullptr)
    {
        ref.x = clip_i(rt->control_center_x, 0, RAW_W - 1);
    }
    return ref;
}

void clear_vision_state(runtime_t *rt)
{
    std::memset(&rt->vision, 0, sizeof(rt->vision));
    rt->vision.track_type = static_cast<int>(TRACK_RIGHT);
    rt->vision.control_center_x = rt->control_center_x;
    rt->vision.control_ref = atg_control_ref(rt);
}

void copy_atg_midline(runtime_t *rt)
{
    midline_t *mid = &rt->vision.mid;
    const point_t ref = rt->vision.control_ref;
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
} // namespace

int track_line_found(const runtime_t *rt)
{
    return rt != nullptr && rt->vision.line_found && rt->vision.mid.step > 0;
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
    clear_vision_state(rt);
    atg_reference_reset();
}

int tracking_process_frame(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }

    clear_vision_state(rt);
    if(!rt->gray_valid)
    {
        return 0;
    }

    const int ok = atg_reference_process_frame(rt->gray, rt->encoder_total);
    rt->vision.track_type = static_cast<int>(track_type);
    rt->vision.line_found = ok && atg_reference_track_line_found() ? 1 : 0;
    if(!rt->vision.line_found)
    {
        return 0;
    }

    copy_atg_midline(rt);
    rt->vision.guide_error = atg_lookahead_error(&rt->vision.mid, rt->vision.control_ref);
    return track_line_found(rt);
}
