#include "report/report.hpp"

#include "report/options.hpp"
#include "report/vision_view.hpp"

#include <array>
#include <cstddef>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <tuple>
#include <unistd.h>

namespace
{
constexpr const char *k_live_beep_path = "/dev/zf_gpio_beep";
constexpr int k_live_beep_ms = 35;
constexpr float k_rad_to_deg = 180.0f / 3.14159265358979323846f;

using live_state_signature_t = std::array<int, 64>;

template <typename... Values>
live_state_signature_t live_state_signature(Values... values)
{
    static_assert(sizeof...(values) == std::tuple_size<live_state_signature_t>::value,
                  "live_state_signature_t size must match the live-state field list");
    return {{static_cast<int>(values)...}};
}

uint64_t report_monotonic_us()
{
    using clock = std::chrono::steady_clock;
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(clock::now().time_since_epoch()).count());
}

int live_beep_fd()
{
    static int fd = -2;
    if(fd != -2)
    {
        return fd;
    }

    if(!read_env_flag("FRONT_CAR_STATE_BEEP", 1))
    {
        fd = -1;
        return fd;
    }

    const char *path = read_env_text("FRONT_CAR_BEEP_PATH", k_live_beep_path);
    fd = open(path, O_WRONLY | O_CLOEXEC);
    return fd;
}

uint64_t &live_beep_off_at_us()
{
    static uint64_t value = 0;
    return value;
}

int write_live_beep_level(int level)
{
    const int fd = live_beep_fd();
    if(fd < 0)
    {
        return 0;
    }

    char c = level ? '1' : '0';
    if(lseek(fd, 0, SEEK_SET) < 0)
    {
        return 0;
    }
    const ssize_t written = write(fd, &c, 1);
    return written == 1 ? 1 : 0;
}

void live_beep_tick()
{
    uint64_t &off_at_us = live_beep_off_at_us();
    if(off_at_us == 0)
    {
        return;
    }

    if(report_monotonic_us() >= off_at_us)
    {
        write_live_beep_level(0);
        off_at_us = 0;
    }
}

void live_beep_once()
{
    if(live_beep_fd() < 0)
    {
        return;
    }

    if(!write_live_beep_level(1))
    {
        return;
    }
    live_beep_off_at_us() = report_monotonic_us() + static_cast<uint64_t>(k_live_beep_ms) * 1000U;
}

int positive_bucket(int value)
{
    return value > 0 ? 1 : 0;
}

int count_bucket(int value)
{
    if(value <= 0)
    {
        return 0;
    }
    if(value < 10)
    {
        return 1;
    }
    if(value < 40)
    {
        return 2;
    }
    return 3;
}

int angle_bucket(float rad)
{
    return static_cast<int>(std::lround(rad * k_rad_to_deg / 5.0f));
}

int flag(bool value)
{
    return value ? 1 : 0;
}

int line_found_for_report(const runtime_t *rt)
{
    return rt != nullptr && rt->vision.line_found && rt->vision.mid.step > 0;
}

int clamp_index_for_report(int index, int count)
{
    if(count <= 0)
    {
        return -1;
    }
    if(index < 0)
    {
        return 0;
    }
    if(index >= count)
    {
        return count - 1;
    }
    return index;
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

struct atg_point_diag_t
{
    int found;
    int id;
    float ipm_x;
    float ipm_y;
    float raw_x;
    float raw_y;
};

atg_point_diag_t near_point_diag(bool found, int id, const float pts[][2], int count)
{
    atg_point_diag_t out = {};
    out.found = flag(found);
    out.id = found ? id : -1;
    out.ipm_x = -1.0F;
    out.ipm_y = -1.0F;
    out.raw_x = -1.0F;
    out.raw_y = -1.0F;

    if(!found)
    {
        return out;
    }
    const int idx = clamp_index_for_report(id, count);
    if(idx < 0)
    {
        return out;
    }
    out.ipm_x = pts[idx][0];
    out.ipm_y = pts[idx][1];
    vision_ipm_to_raw(out.ipm_x, out.ipm_y, &out.raw_x, &out.raw_y);
    return out;
}

atg_point_diag_t near_point_diag(bool found, int id, vision_line_view_t pts)
{
    return near_point_diag(found, id, pts.pts, pts.count);
}

atg_point_diag_t far_point_diag(bool found,
                                int id,
                                vision_line_view_t pts,
                                vision_point2f_t inv_pt)
{
    atg_point_diag_t out = {};
    out.found = flag(found);
    out.id = found ? id : -1;
    out.ipm_x = -1.0F;
    out.ipm_y = -1.0F;
    out.raw_x = -1.0F;
    out.raw_y = -1.0F;

    if(!found)
    {
        return out;
    }
    const int idx = clamp_index_for_report(id, pts.count);
    if(idx < 0)
    {
        return out;
    }
    out.ipm_x = pts.pts[idx][0];
    out.ipm_y = pts.pts[idx][1];
    out.raw_x = inv_pt.x;
    out.raw_y = inv_pt.y;
    return out;
}

const char *left_farline_seed_source(const vision_snapshot_t &atg)
{
    if(atg.lpt0_found && atg.rpts0s_num >= 3 && !atg.if_lost_left_line)
    {
        return "lpt";
    }
    if(atg.circle_right_out)
    {
        return "circle";
    }
    if(atg.rpts0s_num < 2)
    {
        return "lost";
    }
    return "none";
}

const char *right_farline_seed_source(const vision_snapshot_t &atg)
{
    if(atg.lpt1_found && atg.lpt1_id > 2 && !atg.if_lost_right_line)
    {
        return "lpt";
    }
    if(atg.circle_left_out && !atg.garage_type)
    {
        return "circle";
    }
    if(atg.rpts1s_num < 2)
    {
        return "lost";
    }
    return "none";
}

live_state_signature_t make_live_state_signature(const runtime_t *rt)
{
    const vision_snapshot_t atg = vision_snapshot();
    return live_state_signature(
        line_found_for_report(rt),
        atg.track_type,
        atg.cross_type,
        atg.circle_type,
        atg.round_type,
        atg.yroad_type,
        atg.ramp_type,
        atg.road_type,
        atg.speed_type,
        count_bucket(atg.ipts0_num),
        count_bucket(atg.ipts1_num),
        count_bucket(atg.rpts0s_num),
        count_bucket(atg.rpts1s_num),
        count_bucket(atg.rptsn_num),
        atg.line_src_id,
        count_bucket(atg.far_rpts0s_num),
        count_bucket(atg.far_rpts1s_num),
        flag(atg.lpt0_found),
        flag(atg.lpt1_found),
        atg.lpt0_found ? atg.lpt0_id / 4 : -1,
        atg.lpt1_found ? atg.lpt1_id / 4 : -1,
        flag(atg.ypt0_found),
        flag(atg.ypt1_found),
        flag(atg.far_lpt0_found),
        flag(atg.far_lpt1_found),
        atg.far_lpt0_found ? atg.far_lpt0_id / 4 : -1,
        atg.far_lpt1_found ? atg.far_lpt1_id / 4 : -1,
        flag(atg.is_straight0),
        flag(atg.is_straight1),
        flag(atg.is_straight_far_0),
        flag(atg.is_straight_far_1),
        angle_bucket(atg.conf1_rad),
        angle_bucket(atg.conf2_rad),
        angle_bucket(atg.conf3_rad),
        angle_bucket(atg.conf4_rad),
        atg.seed0_found,
        atg.seed1_found,
        atg.seed0_y / 4,
        atg.seed1_y / 4,
        atg.lpt0_debug.best_i / 2,
        atg.lpt1_debug.best_i / 2,
        angle_bucket(atg.lpt0_debug.best_conf_rad),
        angle_bucket(atg.lpt1_debug.best_conf_rad),
        positive_bucket(atg.not_have_line),
        count_bucket(atg.total_distence),
        count_bucket(atg.ramp_total_distence),
        atg.circle_ref_mode,
        flag(atg.circle_a.found),
        atg.circle_a.id / 4,
        atg.circle_a.raw_x / 4,
        atg.circle_a.raw_y / 4,
        flag(atg.circle_b.found),
        atg.circle_b.id / 4,
        atg.circle_b.raw_x / 4,
        atg.circle_b.raw_y / 4,
        flag(atg.circle_c.found),
        atg.circle_c.id / 4,
        atg.circle_c.raw_x / 4,
        atg.circle_c.raw_y / 4,
        positive_bucket(rt != nullptr ? rt->vision.mid.step : 0),
        static_cast<int>(std::lround(rt != nullptr ? rt->vision.guide_error : 0.0)),
        rt != nullptr ? rt->control.input_valid : 0,
        rt != nullptr ? rt->control.stop_request : 0,
        rt != nullptr ? (rt->control.left_duty - rt->control.right_duty) / 20 : 0
    );
}

int live_state_changed(const live_state_signature_t &sig)
{
    static int initialized = 0;
    static live_state_signature_t last = {};
    if(!initialized)
    {
        last = sig;
        initialized = 1;
        return 1;
    }

    if(sig == last)
    {
        return 0;
    }

    last = sig;
    return 1;
}

void print_atg_counts(const vision_snapshot_t &atg)
{
    std::printf("ATGCounts: raw=%d/%d ipm=%d/%d smooth=%d/%d center=%d/%d sel=%d norm=%d "
                "far_raw=%d/%d far_ipm=%d/%d\n",
                atg.ipts0_num,
                atg.ipts1_num,
                atg.rpts0_num,
                atg.rpts1_num,
                atg.rpts0s_num,
                atg.rpts1s_num,
                atg.rptsc0_num,
                atg.rptsc1_num,
                atg.rpts_num,
                atg.rptsn_num,
                atg.far_ipts0_num,
                atg.far_ipts1_num,
                atg.far_rpts0s_num,
                atg.far_rpts1s_num);
}

void print_atg_elements(const vision_snapshot_t &atg)
{
    std::printf("ATGElem: track=%d cross=%d circle=%d(%s) round=%d yroad=%d ramp=%d road=%d speed=%d "
                "not_have_line=%d dist=%d begin_dist=%lld begin_last=%lld ramp_dist=%d\n",
                atg.track_type,
                atg.cross_type,
                atg.circle_type,
                atg.circle_type_name,
                atg.round_type,
                atg.yroad_type,
                atg.ramp_type,
                atg.road_type,
                atg.speed_type,
                atg.not_have_line,
                atg.total_distence,
                (long long)atg.circle_begin_dist,
                (long long)atg.circle_begin_last_dist,
                atg.ramp_total_distence);
}

void print_atg_corners(const vision_snapshot_t &atg)
{
    const vision_line_view_t left = vision_line(vision_line_id::near_left_smooth);
    const vision_line_view_t right = vision_line(vision_line_id::near_right_smooth);
    const vision_line_view_t far_left = vision_line(vision_line_id::far_left_smooth);
    const vision_line_view_t far_right = vision_line(vision_line_id::far_right_smooth);
    const atg_point_diag_t l0 = near_point_diag(atg.lpt0_found, atg.lpt0_id, left);
    const atg_point_diag_t l1 = near_point_diag(atg.lpt1_found, atg.lpt1_id, right);
    const atg_point_diag_t y0 = near_point_diag(atg.ypt0_found, atg.ypt0_id, left);
    const atg_point_diag_t y1 = near_point_diag(atg.ypt1_found, atg.ypt1_id, right);
    const atg_point_diag_t fl0 = far_point_diag(atg.far_lpt0_found,
                                                atg.far_lpt0_id,
                                                far_left,
                                                atg.inv_far_lpt0);
    const atg_point_diag_t fl1 = far_point_diag(atg.far_lpt1_found,
                                                atg.far_lpt1_id,
                                                far_right,
                                                atg.inv_far_lpt1);

    std::printf("ATGCorner: L=%d@%d/%d@%d Y=%d@%d/%d@%d farL=%d@%d/%d@%d "
                "Lxy=%.1f,%.1f:%.1f,%.1f/%.1f,%.1f:%.1f,%.1f "
                "Yxy=%.1f,%.1f:%.1f,%.1f/%.1f,%.1f:%.1f,%.1f "
                "farLxy=%.1f,%.1f:%.1f,%.1f/%.1f,%.1f:%.1f,%.1f "
                "best=%d:%.1f,%.1f:%.1f,%.1f:%.1f:%d%d%d%d%d/%d:%.1f,%.1f:%.1f,%.1f:%.1f:%d%d%d%d%d "
                "seed_src=%s/%s seed=%.1f,%.1f/%.1f,%.1f far_start=%d,%d far_raw=%d/%d far_num=%d/%d "
                "straight=%d/%d far_straight=%d/%d conf_deg=%.1f/%.1f/%.1f/%.1f\n",
                l0.found,
                l0.id,
                l1.found,
                l1.id,
                y0.found,
                y0.id,
                y1.found,
                y1.id,
                fl0.found,
                fl0.id,
                fl1.found,
                fl1.id,
                l0.ipm_x,
                l0.ipm_y,
                l0.raw_x,
                l0.raw_y,
                l1.ipm_x,
                l1.ipm_y,
                l1.raw_x,
                l1.raw_y,
                y0.ipm_x,
                y0.ipm_y,
                y0.raw_x,
                y0.raw_y,
                y1.ipm_x,
                y1.ipm_y,
                y1.raw_x,
                y1.raw_y,
                fl0.ipm_x,
                fl0.ipm_y,
                fl0.raw_x,
                fl0.raw_y,
                fl1.ipm_x,
                fl1.ipm_y,
                fl1.raw_x,
                fl1.raw_y,
                atg.lpt0_debug.best_i,
                atg.lpt0_debug.best_x,
                atg.lpt0_debug.best_y,
                atg.lpt0_debug.best_inv_x,
                atg.lpt0_debug.best_inv_y,
                atg.lpt0_debug.best_conf_deg,
                atg.lpt0_debug.pass_nms,
                atg.lpt0_debug.pass_low,
                atg.lpt0_debug.pass_high,
                atg.lpt0_debug.pass_near,
                atg.lpt0_debug.pass_dir,
                atg.lpt1_debug.best_i,
                atg.lpt1_debug.best_x,
                atg.lpt1_debug.best_y,
                atg.lpt1_debug.best_inv_x,
                atg.lpt1_debug.best_inv_y,
                atg.lpt1_debug.best_conf_deg,
                atg.lpt1_debug.pass_nms,
                atg.lpt1_debug.pass_low,
                atg.lpt1_debug.pass_high,
                atg.lpt1_debug.pass_near,
                atg.lpt1_debug.pass_dir,
                left_farline_seed_source(atg),
                right_farline_seed_source(atg),
                atg.inv_lpt0.x,
                atg.inv_lpt0.y,
                atg.inv_lpt1.x,
                atg.inv_lpt1.y,
                atg.far_x11,
                atg.far_y1,
                atg.far_ipts0_num,
                atg.far_ipts1_num,
                atg.far_rpts0s_num,
                atg.far_rpts1s_num,
                flag(atg.is_straight0),
                flag(atg.is_straight1),
                flag(atg.is_straight_far_0),
                flag(atg.is_straight_far_1),
                atg.conf1_deg,
                atg.conf2_deg,
                atg.conf3_deg,
                atg.conf4_deg);
}

struct line_error_diag_t
{
    int ok;
    int begin;
    int idx;
    int x;
    int y;
    int dist;
    int max_dist;
    double err_deg;
    double dx;
};

struct raw_ref_diag_t
{
    double x;
    double y;
};

line_error_diag_t line_error_diag(vision_line_view_t points,
                                  int aim_distance,
                                  const vision_snapshot_t &atg)
{
    line_error_diag_t out = {};
    out.begin = -1;
    out.idx = -1;
    out.x = -1;
    out.y = -1;
    out.dist = -1;
    out.max_dist = -1;
    if(points.pts == nullptr || points.count <= 0)
    {
        return out;
    }

    double best_start = 1.0e30;
    int begin = -1;
    for(int i = 0; i < points.count; ++i)
    {
        const double dx = static_cast<double>(points.pts[i][0]) - static_cast<double>(atg.cx);
        const double dy = static_cast<double>(points.pts[i][1]) - static_cast<double>(atg.cy);
        const double d = dx * dx + dy * dy;
        if(d < best_start)
        {
            best_start = d;
            begin = i;
        }
    }
    if(begin < 0 || points.count - begin < 2)
    {
        return out;
    }

    int best = begin;
    int best_err = 1 << 30;
    int dist = 0;
    double last_x = static_cast<double>(atg.cx);
    double last_y = static_cast<double>(atg.cy);
    for(int i = begin; i < points.count; ++i)
    {
        const double x = static_cast<double>(points.pts[i][0]);
        const double y = static_cast<double>(points.pts[i][1]);
        if(i != begin)
        {
            dist += static_cast<int>(std::lround(std::hypot(x - last_x, y - last_y)));
        }
        if(dist > out.max_dist)
        {
            out.max_dist = dist;
        }
        const int err = std::abs(dist - aim_distance);
        if(err < best_err)
        {
            best_err = err;
            best = i;
            out.dist = dist;
        }
        last_x = x;
        last_y = y;
    }

    const double x = static_cast<double>(points.pts[best][0]);
    const double y = static_cast<double>(points.pts[best][1]);
    const double dx = x - static_cast<double>(atg.cx);
    const double dy = static_cast<double>(atg.cy) - y + 0.2 * static_cast<double>(atg.pixel_per_meter);
    out.ok = 1;
    out.begin = begin;
    out.idx = best;
    out.x = static_cast<int>(std::lround(x));
    out.y = static_cast<int>(std::lround(y));
    out.dx = dx;
    out.err_deg = -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
    return out;
}

void print_line_error_diag(const vision_snapshot_t &atg)
{
    const int aim_distance = vision_lookahead_dist_px();
    const line_error_diag_t left =
        line_error_diag(vision_line(vision_line_id::center_left), aim_distance, atg);
    const line_error_diag_t right =
        line_error_diag(vision_line(vision_line_id::center_right), aim_distance, atg);
    const line_error_diag_t selected =
        line_error_diag(vision_line(vision_line_id::selected), aim_distance, atg);
    const line_error_diag_t edge_left =
        line_error_diag(vision_line(vision_line_id::near_left_smooth), aim_distance, atg);
    const line_error_diag_t edge_right =
        line_error_diag(vision_line(vision_line_id::near_right_smooth), aim_distance, atg);
    int edge_mid_ok = 0;
    double edge_mid_x = -1.0;
    double edge_mid_y = -1.0;
    double edge_mid_dx = 0.0;
    double edge_mid_err = 0.0;
    double edge_width = 0.0;
    if(edge_left.ok && edge_right.ok)
    {
        edge_mid_ok = 1;
        edge_mid_x = (static_cast<double>(edge_left.x) + static_cast<double>(edge_right.x)) * 0.5;
        edge_mid_y = (static_cast<double>(edge_left.y) + static_cast<double>(edge_right.y)) * 0.5;
        edge_mid_dx = edge_mid_x - static_cast<double>(atg.cx);
        const double edge_mid_dy =
            static_cast<double>(atg.cy) - edge_mid_y + 0.2 * static_cast<double>(atg.pixel_per_meter);
        edge_mid_err = -std::atan2(edge_mid_dx, edge_mid_dy) * 180.0 / 3.14159265358979323846;
        edge_width = std::hypot(static_cast<double>(edge_right.x - edge_left.x),
                                static_cast<double>(edge_right.y - edge_left.y));
    }

    std::printf("LineErr: aim=%d cxcy=%.1f,%.1f "
                "left=%d:%.2f@%d,%d dx=%.1f idx=%d/%d dist=%d/%d "
                "right=%d:%.2f@%d,%d dx=%.1f idx=%d/%d dist=%d/%d "
                "sel=%d:%.2f@%d,%d dx=%.1f idx=%d/%d dist=%d/%d "
                "edge=%d:%.2f@%.1f,%.1f dx=%.1f width=%.1f l=%d,%d r=%d,%d\n",
                aim_distance,
                atg.cx,
                atg.cy,
                left.ok,
                left.err_deg,
                left.x,
                left.y,
                left.dx,
                left.begin,
                left.idx,
                left.dist,
                left.max_dist,
                right.ok,
                right.err_deg,
                right.x,
                right.y,
                right.dx,
                right.begin,
                right.idx,
                right.dist,
                right.max_dist,
                selected.ok,
                selected.err_deg,
                selected.x,
                selected.y,
                selected.dx,
                selected.begin,
                selected.idx,
                selected.dist,
                selected.max_dist,
                edge_mid_ok,
                edge_mid_err,
                edge_mid_x,
                edge_mid_y,
                edge_mid_dx,
                edge_width,
                edge_left.x,
                edge_left.y,
                edge_right.x,
                edge_right.y);
    if(edge_mid_ok)
    {
        int best_raw_x = -1;
        double best_abs_err = 1.0e30;
        double best_err = 0.0;
        raw_ref_diag_t best_ref = {};
        char scan[512];
        int used = 0;
        scan[0] = '\0';
        const double raw_y = static_cast<double>(RAW_H) * 0.98;
        for(int raw_x = 0; raw_x <= 140; raw_x += 5)
        {
            raw_ref_diag_t ref = {};
            float ipm_x = 0.0F;
            float ipm_y = 0.0F;
            vision_raw_to_ipm(static_cast<float>(raw_x),
                              static_cast<float>(raw_y),
                              &ipm_x,
                              &ipm_y);
            ref.x = static_cast<double>(ipm_x);
            ref.y = static_cast<double>(ipm_y);
            const double dx = edge_mid_x - ref.x;
            const double dy = ref.y - edge_mid_y + 0.2 * static_cast<double>(atg.pixel_per_meter);
            const double err = -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
            const double abs_err = std::fabs(err);
            if(abs_err < best_abs_err)
            {
                best_abs_err = abs_err;
                best_err = err;
                best_raw_x = raw_x;
                best_ref = ref;
            }
            if(raw_x % 10 == 0)
            {
                const int n = std::snprintf(scan + used,
                                            sizeof(scan) - static_cast<size_t>(used),
                                            "%s%d:%.1f",
                                            used == 0 ? "" : ",",
                                            raw_x,
                                            err);
                if(n > 0)
                {
                    used += n;
                    if(used >= static_cast<int>(sizeof(scan)))
                    {
                        used = static_cast<int>(sizeof(scan)) - 1;
                    }
                }
            }
        }
        std::printf("CxScan: raw_ref=%.1f edge=%.1f,%.1f best_raw_x=%d best_err=%.2f best_cxcy=%.1f,%.1f scan=%s\n",
                    atg.vehicle_raw_ref_x,
                    edge_mid_x,
                    edge_mid_y,
                    best_raw_x,
                    best_err,
                    best_ref.x,
                    best_ref.y,
                    scan);
    }
}

void print_cross_diag(const vision_snapshot_t &atg)
{
    const int half_left = atg.cross_half && atg.lpt0_found_flag;
    const int half_right = atg.cross_half && atg.lpt1_found_flag;
    std::printf("CrossDiag: type=%s track=%d half_lr=%d/%d "
                "nearL=%d@%d/%d@%d nearNum=%d/%d centerNum=%d/%d "
                "farL=%d@%d/%d@%d farNum=%d/%d farRaw=%d/%d "
                "lost=%d/%d not_have=%d final=%d/%d flags=%d/%d\n",
                atg.cross_type_name,
                atg.track_type,
                half_left,
                half_right,
                flag(atg.lpt0_found),
                atg.lpt0_found ? atg.lpt0_id : -1,
                flag(atg.lpt1_found),
                atg.lpt1_found ? atg.lpt1_id : -1,
                atg.rpts0s_num,
                atg.rpts1s_num,
                atg.rptsc0_num,
                atg.rptsc1_num,
                flag(atg.far_lpt0_found),
                atg.far_lpt0_found ? atg.far_lpt0_id : -1,
                flag(atg.far_lpt1_found),
                atg.far_lpt1_found ? atg.far_lpt1_id : -1,
                atg.far_rpts0s_num,
                atg.far_rpts1s_num,
                atg.far_ipts0_num,
                atg.far_ipts1_num,
                atg.if_lost_left_line,
                atg.if_lost_right_line,
                atg.not_have_line,
                atg.rpts_num,
                atg.rptsn_num,
                atg.lpt0_found_flag,
                atg.lpt1_found_flag);
}

void print_atg_vision_diag(const vision_snapshot_t &atg)
{
    std::printf("ATGSeedDiag: seed=%d@%d,%d/%d@%d,%d begin=%d,%d block=%d clip=%d\n",
                atg.seed0_found,
                atg.seed0_x,
                atg.seed0_y,
                atg.seed1_found,
                atg.seed1_x,
                atg.seed1_y,
                atg.begin_x,
                atg.begin_y,
                atg.block_size,
                atg.clip_value);
    std::printf("ATGLptDiag: best=%d(%.1f) imip=%d/%d pass=%d%d%d%d%d acc=%d ipm=%.1f,%.1f inv=%.1f,%.1f "
                "| %d(%.1f) imip=%d/%d pass=%d%d%d%d%d acc=%d ipm=%.1f,%.1f inv=%.1f,%.1f\n",
                atg.lpt0_debug.best_i,
                atg.lpt0_debug.best_conf_deg,
                atg.lpt0_debug.best_im1,
                atg.lpt0_debug.best_ip1,
                atg.lpt0_debug.pass_nms,
                atg.lpt0_debug.pass_low,
                atg.lpt0_debug.pass_high,
                atg.lpt0_debug.pass_near,
                atg.lpt0_debug.pass_dir,
                atg.lpt0_debug.accept_i,
                atg.lpt0_debug.best_x,
                atg.lpt0_debug.best_y,
                atg.lpt0_debug.best_inv_x,
                atg.lpt0_debug.best_inv_y,
                atg.lpt1_debug.best_i,
                atg.lpt1_debug.best_conf_deg,
                atg.lpt1_debug.best_im1,
                atg.lpt1_debug.best_ip1,
                atg.lpt1_debug.pass_nms,
                atg.lpt1_debug.pass_low,
                atg.lpt1_debug.pass_high,
                atg.lpt1_debug.pass_near,
                atg.lpt1_debug.pass_dir,
                atg.lpt1_debug.accept_i,
                atg.lpt1_debug.best_x,
                atg.lpt1_debug.best_y,
                atg.lpt1_debug.best_inv_x,
                atg.lpt1_debug.best_inv_y);
}

void write_mid_report(std::ofstream &out, const runtime_t *rt)
{
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = vision_lookahead_dist_px();
    mid_points_for_report(rt->vision.mid,
                          rt->vision.control_ref.y,
                          aim_distance,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);

    out << "mid_step=" << rt->vision.mid.step << "\n";
    out << "mid0=" << m0.x << "," << m0.y << "\n";
    out << "mid_look=" << ml.x << "," << ml.y << "\n";
    out << "mid_look_dist=" << ml_dist << "\n";
    out << "mid_max_dist=" << max_dist << "\n";
    out << "mid_forward_lookahead=" << ml_forward << "\n";
    out << "control_ref=" << rt->vision.control_ref.x << "," << rt->vision.control_ref.y << "\n";
    out << "control_center_x=" << rt->control_center_x << "\n";
    out << "guide_error=" << rt->vision.guide_error << "\n";
}
} // namespace

// 取中线起点和预瞄附近点，供单行日志和报告输出。
void mid_points_for_report(const midline_t &mid,
                           int ref_y,
                           int aim_distance,
                           point_t *m0,
                           point_t *ml,
                           int *ml_dist,
                           int *max_dist,
                           int *forward_ok)
{
    if(m0 == nullptr || ml == nullptr || ml_dist == nullptr ||
       max_dist == nullptr || forward_ok == nullptr)
    {
        return;
    }

    *m0 = {-1, -1};
    *ml = {-1, -1};
    *ml_dist = -1;
    *max_dist = -1;
    *forward_ok = 0;
    if(mid.step <= 0)
    {
        return;
    }

    *m0 = mid.pts[0];
    int best = 0;
    int best_err = 1 << 30;
    for(int i = 0; i < mid.step; ++i)
    {
        if(mid.dist[i] <= 0)
        {
            continue;
        }
        if(mid.dist[i] > *max_dist)
        {
            *max_dist = mid.dist[i];
        }
        const int err = std::abs(mid.dist[i] - aim_distance);
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }
    *ml = mid.pts[best];
    *ml_dist = mid.dist[best];
    *forward_ok = midline_has_forward_lookahead(&mid, aim_distance, ref_y);
}

void print_replay_frame(int frame, const runtime_t *rt)
{
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = vision_lookahead_dist_px();
    const vision_snapshot_t atg = vision_snapshot();
    mid_points_for_report(rt->vision.mid,
                          rt->vision.control_ref.y,
                          aim_distance,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);

    std::printf("replay frame=%d line=%d track=%d cross=%d circle=%d round=%d yroad=%d ramp=%d road=%d speed=%d "
                "near=%d/%d raw=%d/%d ipm=%d/%d center=%d/%d sel=%d/%d src=%d "
                "l=%d@%d/%d@%d y=%d@%d/%d@%d far_l=%d@%d/%d@%d far_num=%d/%d "
                "straight=%d/%d far_straight=%d/%d conf=%.1f/%.1f/%.1f/%.1f "
                "dist=%d begin=%lld/%lld ramp_dist=%d m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d "
                "cxcy=%.1f,%.1f guide=%.2f atg_guide=%.1f/%.1f/%.1f "
                "duty=%d/%d pwm=PWM2:%d/PWM1:%d motor=2:%d/1:%d\n",
                frame,
                line_found_for_report(rt),
                atg.track_type,
                atg.cross_type,
                atg.circle_type,
                atg.round_type,
                atg.yroad_type,
                atg.ramp_type,
                atg.road_type,
                atg.speed_type,
                atg.rpts0s_num,
                atg.rpts1s_num,
                atg.ipts0_num,
                atg.ipts1_num,
                atg.rpts0_num,
                atg.rpts1_num,
                atg.rptsc0_num,
                atg.rptsc1_num,
                atg.rpts_num,
                atg.rptsn_num,
                atg.line_src_id,
                atg.lpt0_found,
                atg.lpt0_id,
                atg.lpt1_found,
                atg.lpt1_id,
                atg.ypt0_found,
                atg.ypt0_id,
                atg.ypt1_found,
                atg.ypt1_id,
                atg.far_lpt0_found,
                atg.far_lpt0_id,
                atg.far_lpt1_found,
                atg.far_lpt1_id,
                atg.far_rpts0s_num,
                atg.far_rpts1s_num,
                atg.is_straight0,
                atg.is_straight1,
                atg.is_straight_far_0,
                atg.is_straight_far_1,
                atg.conf1_deg,
                atg.conf2_deg,
                atg.conf3_deg,
                atg.conf4_deg,
                atg.total_distence,
                (long long)atg.circle_begin_dist,
                (long long)atg.circle_begin_last_dist,
                atg.ramp_total_distence,
                m0.x,
                m0.y,
                ml.x,
                ml.y,
                ml_dist,
                ml_forward,
                max_dist,
                atg.cx,
                atg.cy,
                rt->vision.guide_error,
                atg.guide,
                atg.guide_up,
                atg.guide_up_up,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty);
}

void print_detail(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }
    const vision_snapshot_t atg = vision_snapshot();

    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = vision_lookahead_dist_px();
    mid_points_for_report(rt->vision.mid,
                          rt->vision.control_ref.y,
                          aim_distance,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);

    print_atg_elements(atg);
    print_atg_counts(atg);
    print_atg_corners(atg);
    print_atg_vision_diag(atg);
    std::printf("ATGMid: line=%d step=%d ref=(%d,%d) m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d "
                "cxcy=%.1f,%.1f guide=%.2f atg_guide=%.1f/%.1f/%.1f\n",
                line_found_for_report(rt),
                rt->vision.mid.step,
                rt->vision.control_ref.x,
                rt->vision.control_ref.y,
                m0.x,
                m0.y,
                ml.x,
                ml.y,
                ml_dist,
                ml_forward,
                max_dist,
                atg.cx,
                atg.cy,
                rt->vision.guide_error,
                atg.guide,
                atg.guide_up,
                atg.guide_up_up);
    std::printf("ATGParam: begin=%d,%d block=%d clip=%d blur=%d sample=%.3f ppm=%d angle=%.3f road=%.3f "
                "aim=%.3f/%.3f/%.3f idx=%d/%d/%d ipm_source=atg_rot_inv_rot\n",
                atg.begin_x,
                atg.begin_y,
                atg.block_size,
                atg.clip_value,
                atg.line_blur_kernel,
                atg.sample_dist,
                atg.pixel_per_meter,
                atg.angle_dist,
                atg.road_width,
                static_cast<double>(aim_distance),
                atg.aim_distance_far,
                atg.round_aim_distance,
                atg.aim_idx,
                atg.aim_idx_up,
                atg.aim_idx_up_up);
    std::printf("Loop: valid=%d stop=%d signed=%d target_yaw=%d yaw_cmd=%d actual_yaw=%d target_rps=%d/%d actual_rps=%d/%d "
                "duty=%d/%d pwm=PWM2:%d/PWM1:%d motor=2:%d/1:%d\n",
                rt->control.input_valid,
                rt->control.stop_request,
                rt->control.signed_output,
                rt->control.target_yaw_rate_mrad_s,
                rt->control.yaw_cmd_mrad_s,
                rt->control.actual_yaw_rate_mrad_s,
                rt->control.left_target_rps_milli,
                rt->control.right_target_rps_milli,
                rt->control.left_actual_rps_milli,
                rt->control.right_actual_rps_milli,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty);
}

void print_live(uint32_t frame_id, const runtime_t *rt, int div)
{
    live_beep_tick();
    if(rt == nullptr)
    {
        return;
    }
    const vision_snapshot_t atg = vision_snapshot();
    const int force_log = read_env_flag("FRONT_CAR_FORCE_LIVE_LOG", 0);
    const int element_log = atg.cross_or_circle_active;
    if(!force_log && !element_log && div > 1 && frame_id % static_cast<uint32_t>(div) != 0U)
    {
        return;
    }

    const live_state_signature_t sig = make_live_state_signature(rt);
    if(!force_log && !live_state_changed(sig))
    {
        return;
    }
    if(!force_log && frame_id != 0U)
    {
        live_beep_once();
    }

    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = vision_lookahead_dist_px();
    mid_points_for_report(rt->vision.mid,
                          rt->vision.control_ref.y,
                          aim_distance,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);

    std::printf("frame=%u line=%d track=%d cross=%d circle=%d(%s) round=%d yroad=%d ramp=%d road=%d speed=%d "
                "near=%d/%d raw=%d/%d sel=%d/%d src=%d far=%d/%d far_raw=%d/%d "
                "l=%d@%d/%d@%d far_l=%d@%d/%d@%d straight=%d/%d far_straight=%d/%d "
                "circle_cnt=%d/%d/%d/%d lost=%d/%d ref=%d A=%d@%d,%d#%d B=%d@%d,%d#%d C=%d@%d,%d#%d "
                "conf=%.1f/%.1f/%.1f/%.1f dist=%d begin=%lld/%lld "
                "m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d cxcy=%.1f,%.1f guide=%.2f "
                "atg=%.1f/%.1f/%.1f pure=%.2f/%.2f yaw=%d cmd=%d actual=%d signed=%d rps=%d/%d:%d/%d "
                "duty=%d/%d pwm=PWM2:%d/PWM1:%d motor=2:%d/1:%d\n",
                frame_id,
                line_found_for_report(rt),
                atg.track_type,
                atg.cross_type,
                atg.circle_type,
                atg.circle_type_name,
                atg.round_type,
                atg.yroad_type,
                atg.ramp_type,
                atg.road_type,
                atg.speed_type,
                atg.rpts0s_num,
                atg.rpts1s_num,
                atg.ipts0_num,
                atg.ipts1_num,
                atg.rpts_num,
                atg.rptsn_num,
                atg.line_src_id,
                atg.far_rpts0s_num,
                atg.far_rpts1s_num,
                atg.far_ipts0_num,
                atg.far_ipts1_num,
                flag(atg.lpt0_found),
                atg.lpt0_found ? atg.lpt0_id : -1,
                flag(atg.lpt1_found),
                atg.lpt1_found ? atg.lpt1_id : -1,
                flag(atg.far_lpt0_found),
                atg.far_lpt0_found ? atg.far_lpt0_id : -1,
                flag(atg.far_lpt1_found),
                atg.far_lpt1_found ? atg.far_lpt1_id : -1,
                flag(atg.is_straight0),
                flag(atg.is_straight1),
                flag(atg.is_straight_far_0),
                flag(atg.is_straight_far_1),
                atg.none_left_line,
                atg.none_right_line,
                atg.have_left_line,
                atg.have_right_line,
                flag(atg.if_lost_left_line),
                flag(atg.if_lost_right_line),
                atg.circle_ref_mode,
                flag(atg.circle_a.found),
                atg.circle_a.found ? atg.circle_a.raw_x : -1,
                atg.circle_a.found ? atg.circle_a.raw_y : -1,
                atg.circle_a.id,
                flag(atg.circle_b.found),
                atg.circle_b.found ? atg.circle_b.raw_x : -1,
                atg.circle_b.found ? atg.circle_b.raw_y : -1,
                atg.circle_b.id,
                flag(atg.circle_c.found),
                atg.circle_c.found ? atg.circle_c.raw_x : -1,
                atg.circle_c.found ? atg.circle_c.raw_y : -1,
                atg.circle_c.id,
                atg.conf1_deg,
                atg.conf2_deg,
                atg.conf3_deg,
                atg.conf4_deg,
                atg.total_distence,
                (long long)atg.circle_begin_dist,
                (long long)atg.circle_begin_last_dist,
                m0.x,
                m0.y,
                ml.x,
                ml.y,
                ml_dist,
                ml_forward,
                max_dist,
                atg.cx,
                atg.cy,
                rt->vision.guide_error,
                atg.guide,
                atg.guide_up,
                atg.guide_up_up,
                atg.pure_angle,
                atg.pure_angle_up,
                rt->control.target_yaw_rate_mrad_s,
                rt->control.yaw_cmd_mrad_s,
                rt->control.actual_yaw_rate_mrad_s,
                rt->control.signed_output,
                rt->control.left_target_rps_milli,
                rt->control.right_target_rps_milli,
                rt->control.left_actual_rps_milli,
                rt->control.right_actual_rps_milli,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty);
    if(force_log || element_log)
    {
        print_atg_corners(atg);
    }
    print_cross_diag(atg);
    print_line_error_diag(atg);
    print_atg_vision_diag(atg);
    std::fflush(stdout);
}

int write_report(const runtime_t *rt, const char *report_path)
{
    if(rt == nullptr || report_path == nullptr || report_path[0] == '\0')
    {
        return 0;
    }

    std::ofstream out(report_path);
    if(!out.is_open())
    {
        return 0;
    }
    const vision_snapshot_t atg = vision_snapshot();

    out << "line_found=" << line_found_for_report(rt) << "\n";
    out << "ipm_source=atg_rot_inv_rot\n";
    out << "atg_track_type=" << atg.track_type << "\n";
    out << "atg_cross_type=" << atg.cross_type << "\n";
    out << "atg_circle_type=" << atg.circle_type << "\n";
    out << "atg_circle_ref_mode=" << atg.circle_ref_mode << "\n";
    out << "atg_circle_A=" << flag(atg.circle_a.found) << ","
        << atg.circle_a.id << ","
        << (atg.circle_a.found ? atg.circle_a.raw_x : -1) << ","
        << (atg.circle_a.found ? atg.circle_a.raw_y : -1) << "\n";
    out << "atg_circle_B=" << flag(atg.circle_b.found) << ","
        << atg.circle_b.id << ","
        << (atg.circle_b.found ? atg.circle_b.raw_x : -1) << ","
        << (atg.circle_b.found ? atg.circle_b.raw_y : -1) << "\n";
    out << "atg_circle_C=" << flag(atg.circle_c.found) << ","
        << atg.circle_c.id << ","
        << (atg.circle_c.found ? atg.circle_c.raw_x : -1) << ","
        << (atg.circle_c.found ? atg.circle_c.raw_y : -1) << "\n";
    out << "atg_round_type=" << atg.round_type << "\n";
    out << "atg_yroad_type=" << atg.yroad_type << "\n";
    out << "atg_ramp_type=" << atg.ramp_type << "\n";
    out << "atg_road_type=" << atg.road_type << "\n";
    out << "atg_speed_type=" << atg.speed_type << "\n";
    out << "atg_not_have_line=" << atg.not_have_line << "\n";
    out << "atg_total_distence=" << atg.total_distence << "\n";
    out << "atg_circle_begin_dist=" << atg.circle_begin_dist << "\n";
    out << "atg_circle_begin_last_dist=" << atg.circle_begin_last_dist << "\n";
    out << "atg_ramp_total_distence=" << atg.ramp_total_distence << "\n";

    out << "atg_ipts0_num=" << atg.ipts0_num << "\n";
    out << "atg_ipts1_num=" << atg.ipts1_num << "\n";
    out << "atg_rpts0_num=" << atg.rpts0_num << "\n";
    out << "atg_rpts1_num=" << atg.rpts1_num << "\n";
    out << "atg_rpts0s_num=" << atg.rpts0s_num << "\n";
    out << "atg_rpts1s_num=" << atg.rpts1s_num << "\n";
    out << "atg_rptsc0_num=" << atg.rptsc0_num << "\n";
    out << "atg_rptsc1_num=" << atg.rptsc1_num << "\n";
    out << "atg_rpts_num=" << atg.rpts_num << "\n";
    out << "atg_rptsn_num=" << atg.rptsn_num << "\n";
    out << "atg_selected_line_source=" << atg.line_src_name << "\n";
    out << "atg_selected_line_source_id=" << atg.line_src_id << "\n";
    out << "atg_far_ipts0_num=" << atg.far_ipts0_num << "\n";
    out << "atg_far_ipts1_num=" << atg.far_ipts1_num << "\n";
    out << "atg_far_rpts0s_num=" << atg.far_rpts0s_num << "\n";
    out << "atg_far_rpts1s_num=" << atg.far_rpts1s_num << "\n";

    out << "atg_is_straight0=" << flag(atg.is_straight0) << "\n";
    out << "atg_is_straight1=" << flag(atg.is_straight1) << "\n";
    out << "atg_is_straight_far_0=" << flag(atg.is_straight_far_0) << "\n";
    out << "atg_is_straight_far_1=" << flag(atg.is_straight_far_1) << "\n";
    out << "atg_lpt0_found=" << flag(atg.lpt0_found) << "\n";
    out << "atg_lpt1_found=" << flag(atg.lpt1_found) << "\n";
    out << "atg_lpt0_id=" << (atg.lpt0_found ? atg.lpt0_id : -1) << "\n";
    out << "atg_lpt1_id=" << (atg.lpt1_found ? atg.lpt1_id : -1) << "\n";
    out << "atg_ypt0_found=" << flag(atg.ypt0_found) << "\n";
    out << "atg_ypt1_found=" << flag(atg.ypt1_found) << "\n";
    out << "atg_ypt0_id=" << (atg.ypt0_found ? atg.ypt0_id : -1) << "\n";
    out << "atg_ypt1_id=" << (atg.ypt1_found ? atg.ypt1_id : -1) << "\n";
    out << "atg_far_lpt0_found=" << flag(atg.far_lpt0_found) << "\n";
    out << "atg_far_lpt1_found=" << flag(atg.far_lpt1_found) << "\n";
    out << "atg_far_lpt0_id=" << (atg.far_lpt0_found ? atg.far_lpt0_id : -1) << "\n";
    out << "atg_far_lpt1_id=" << (atg.far_lpt1_found ? atg.far_lpt1_id : -1) << "\n";
    out << "atg_conf1_max_deg=" << atg.conf1_deg << "\n";
    out << "atg_conf2_max_deg=" << atg.conf2_deg << "\n";
    out << "atg_conf3_max_deg=" << atg.conf3_deg << "\n";
    out << "atg_conf4_max_deg=" << atg.conf4_deg << "\n";
    out << "atg_seed0_found=" << atg.seed0_found << "\n";
    out << "atg_seed1_found=" << atg.seed1_found << "\n";
    out << "atg_seed0_xy=" << atg.seed0_x << "," << atg.seed0_y << "\n";
    out << "atg_seed1_xy=" << atg.seed1_x << "," << atg.seed1_y << "\n";
    out << "atg_lpt0_best=" << atg.lpt0_debug.best_i << "," << atg.lpt0_debug.best_conf_deg << "\n";
    out << "atg_lpt1_best=" << atg.lpt1_debug.best_i << "," << atg.lpt1_debug.best_conf_deg << "\n";
    out << "atg_lpt0_best_imip=" << atg.lpt0_debug.best_im1 << "," << atg.lpt0_debug.best_ip1 << "\n";
    out << "atg_lpt1_best_imip=" << atg.lpt1_debug.best_im1 << "," << atg.lpt1_debug.best_ip1 << "\n";
    out << "atg_lpt0_pass=" << atg.lpt0_debug.pass_nms << "," << atg.lpt0_debug.pass_low << ","
        << atg.lpt0_debug.pass_high << ","
        << atg.lpt0_debug.pass_near << "," << atg.lpt0_debug.pass_dir << "\n";
    out << "atg_lpt1_pass=" << atg.lpt1_debug.pass_nms << "," << atg.lpt1_debug.pass_low << ","
        << atg.lpt1_debug.pass_high << ","
        << atg.lpt1_debug.pass_near << "," << atg.lpt1_debug.pass_dir << "\n";
    out << "atg_lpt0_accept_i=" << atg.lpt0_debug.accept_i << "\n";
    out << "atg_lpt1_accept_i=" << atg.lpt1_debug.accept_i << "\n";
    out << "atg_lpt0_best_ipm=" << atg.lpt0_debug.best_x << "," << atg.lpt0_debug.best_y << "\n";
    out << "atg_lpt1_best_ipm=" << atg.lpt1_debug.best_x << "," << atg.lpt1_debug.best_y << "\n";
    out << "atg_lpt0_best_inv=" << atg.lpt0_debug.best_inv_x << "," << atg.lpt0_debug.best_inv_y << "\n";
    out << "atg_lpt1_best_inv=" << atg.lpt1_debug.best_inv_x << "," << atg.lpt1_debug.best_inv_y << "\n";

    out << "atg_begin_x=" << atg.begin_x << "\n";
    out << "atg_begin_y=" << atg.begin_y << "\n";
    out << "atg_block_size=" << atg.block_size << "\n";
    out << "atg_clip_value=" << atg.clip_value << "\n";
    out << "atg_line_blur_kernel=" << atg.line_blur_kernel << "\n";
    out << "atg_sample_dist=" << atg.sample_dist << "\n";
    out << "atg_pixel_per_meter=" << atg.pixel_per_meter << "\n";
    out << "atg_angle_dist=" << atg.angle_dist << "\n";
    out << "atg_road_width=" << atg.road_width << "\n";
    out << "atg_aim_distance=" << atg.aim_distance << "\n";
    out << "atg_aim_distance_far=" << atg.aim_distance_far << "\n";
    out << "atg_round_aim_distance=" << atg.round_aim_distance << "\n";
    out << "atg_aim_idx=" << atg.aim_idx << "\n";
    out << "atg_aim_idx_up=" << atg.aim_idx_up << "\n";
    out << "atg_aim_idx_up_up=" << atg.aim_idx_up_up << "\n";
    out << "atg_cx=" << atg.cx << "\n";
    out << "atg_cy=" << atg.cy << "\n";
    out << "atg_guide=" << atg.guide << "\n";
    out << "atg_guide_up=" << atg.guide_up << "\n";
    out << "atg_guide_up_up=" << atg.guide_up_up << "\n";

    write_mid_report(out, rt);
    out << "control_input_valid=" << rt->control.input_valid << "\n";
    out << "control_stop_request=" << rt->control.stop_request << "\n";
    out << "control_target_yaw_rate_mrad_s=" << rt->control.target_yaw_rate_mrad_s << "\n";
    out << "control_yaw_cmd_mrad_s=" << rt->control.yaw_cmd_mrad_s << "\n";
    out << "control_actual_yaw_rate_mrad_s=" << rt->control.actual_yaw_rate_mrad_s << "\n";
    out << "control_signed_output=" << rt->control.signed_output << "\n";
    out << "control_left_target_rps_milli=" << rt->control.left_target_rps_milli << "\n";
    out << "control_right_target_rps_milli=" << rt->control.right_target_rps_milli << "\n";
    out << "control_left_actual_rps_milli=" << rt->control.left_actual_rps_milli << "\n";
    out << "control_right_actual_rps_milli=" << rt->control.right_actual_rps_milli << "\n";
    out << "control_left_duty=" << rt->control.left_duty << "\n";
    out << "control_right_duty=" << rt->control.right_duty << "\n";
    out << "control_duty_mapping=left_duty->PWM2/motor2,right_duty->PWM1/motor1\n";
    out << "control_pwm2_duty=" << rt->control.left_duty << "\n";
    out << "control_pwm1_duty=" << rt->control.right_duty << "\n";
    out << "control_motor2_duty=" << rt->control.left_duty << "\n";
    out << "control_motor1_duty=" << rt->control.right_duty << "\n";
    return 1;
}
