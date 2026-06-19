#include "app/report.hpp"

#include "app/options.hpp"
#include "tracking/atg_reference_mainline.hpp"

#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fcntl.h>
#include <fstream>
#include <tuple>
#include <unistd.h>

extern "C" {
#include "atg_reference_step.h"
#include "headfile.h"
}

namespace
{
constexpr const char *k_live_beep_path = "/dev/zf_gpio_beep";
constexpr int k_live_beep_ms = 35;
constexpr float k_rad_to_deg = 180.0f / 3.14159265358979323846f;

using live_state_signature_t = std::array<int, 50>;

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

const char *circle_enum_name(int value)
{
    switch(value)
    {
    case CIRCLE_NONE:
        return "CIRCLE_NONE";
    case CIRCLE_LEFT_BEGIN:
        return "CIRCLE_LEFT_BEGIN";
    case CIRCLE_RIGHT_BEGIN:
        return "CIRCLE_RIGHT_BEGIN";
    case CIRCLE_LEFT_IN:
        return "CIRCLE_LEFT_IN";
    case CIRCLE_RIGHT_IN:
        return "CIRCLE_RIGHT_IN";
    case CIRCLE_LEFT_RUNNING:
        return "CIRCLE_LEFT_RUNNING";
    case CIRCLE_RIGHT_RUNNING:
        return "CIRCLE_RIGHT_RUNNING";
    case CIRCLE_LEFT_OUT:
        return "CIRCLE_LEFT_OUT";
    case CIRCLE_RIGHT_OUT:
        return "CIRCLE_RIGHT_OUT";
    case CIRCLE_LEFT_END:
        return "CIRCLE_LEFT_END";
    case CIRCLE_RIGHT_END:
        return "CIRCLE_RIGHT_END";
    default:
        return "CIRCLE_UNKNOWN";
    }
}

const char *cross_enum_name(int value)
{
    switch(value)
    {
    case CROSS_NONE:
        return "CROSS_NONE";
    case CROSS_BEGIN:
        return "CROSS_BEGIN";
    case CROSS_IN:
        return "CROSS_IN";
    case CROSS_HALF:
        return "CROSS_HALF";
    case CROSS_HALF_BEGIN:
        return "CROSS_HALF_BEGIN";
    case CROSS_HALF_RIGHT:
        return "CROSS_HALF_RIGHT";
    case CROSS_HALF_LEFT:
        return "CROSS_HALF_LEFT";
    default:
        return "CROSS_UNKNOWN";
    }
}

live_state_signature_t make_live_state_signature(const runtime_t *rt)
{
    return live_state_signature(
        track_line_found(rt),
        track_type,
        cross_type,
        circle_type,
        round_type,
        yroad_type,
        ramp_type,
        road_type,
        speed_type,
        count_bucket(ipts0_num),
        count_bucket(ipts1_num),
        count_bucket(rpts0s_num),
        count_bucket(rpts1s_num),
        count_bucket(rptsn_num),
        count_bucket(far_rpts0s_num),
        count_bucket(far_rpts1s_num),
        flag(Lpt0_found),
        flag(Lpt1_found),
        Lpt0_found ? Lpt0_rpts0s_id / 4 : -1,
        Lpt1_found ? Lpt1_rpts1s_id / 4 : -1,
        flag(Ypt0_found),
        flag(Ypt1_found),
        flag(far_Lpt0_found),
        flag(far_Lpt1_found),
        far_Lpt0_found ? far_Lpt0_rpts0s_id / 4 : -1,
        far_Lpt1_found ? far_Lpt1_rpts1s_id / 4 : -1,
        flag(is_straight0),
        flag(is_straight1),
        flag(is_straight_far_0),
        flag(is_straight_far_1),
        angle_bucket(conf1_max),
        angle_bucket(conf2_max),
        angle_bucket(conf3_max),
        angle_bucket(conf4_max),
        atg_seed0_found,
        atg_seed1_found,
        atg_seed0_y / 4,
        atg_seed1_y / 4,
        atg_lpt0_best_i / 2,
        atg_lpt1_best_i / 2,
        angle_bucket(atg_lpt0_best_conf),
        angle_bucket(atg_lpt1_best_conf),
        positive_bucket(not_have_line),
        count_bucket(total_distence),
        count_bucket(Ramp_total_distence),
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

void print_atg_counts()
{
    std::printf("ATGCounts: raw=%d/%d ipm=%d/%d smooth=%d/%d center=%d/%d sel=%d norm=%d "
                "far_raw=%d/%d far_ipm=%d/%d\n",
                ipts0_num,
                ipts1_num,
                rpts0_num,
                rpts1_num,
                rpts0s_num,
                rpts1s_num,
                rptsc0_num,
                rptsc1_num,
                rpts_num,
                rptsn_num,
                far_ipts0_num,
                far_ipts1_num,
                far_rpts0s_num,
                far_rpts1s_num);
}

void print_atg_elements()
{
    std::printf("ATGElem: track=%d cross=%d circle=%d(%s) round=%d yroad=%d ramp=%d road=%d speed=%d "
                "not_have_line=%d dist=%d ramp_dist=%d\n",
                track_type,
                cross_type,
                circle_type,
                circle_enum_name(circle_type),
                round_type,
                yroad_type,
                ramp_type,
                road_type,
                speed_type,
                not_have_line,
                total_distence,
                Ramp_total_distence);
}

void print_atg_corners()
{
    std::printf("ATGCorner: L=%d@%d/%d@%d Y=%d@%d/%d@%d farL=%d@%d/%d@%d "
                "straight=%d/%d far_straight=%d/%d conf_deg=%.1f/%.1f/%.1f/%.1f\n",
                flag(Lpt0_found),
                Lpt0_found ? Lpt0_rpts0s_id : -1,
                flag(Lpt1_found),
                Lpt1_found ? Lpt1_rpts1s_id : -1,
                flag(Ypt0_found),
                Ypt0_found ? Ypt0_rpts0s_id : -1,
                flag(Ypt1_found),
                Ypt1_found ? Ypt1_rpts1s_id : -1,
                flag(far_Lpt0_found),
                far_Lpt0_found ? far_Lpt0_rpts0s_id : -1,
                flag(far_Lpt1_found),
                far_Lpt1_found ? far_Lpt1_rpts1s_id : -1,
                flag(is_straight0),
                flag(is_straight1),
                flag(is_straight_far_0),
                flag(is_straight_far_1),
                conf1_max * k_rad_to_deg,
                conf2_max * k_rad_to_deg,
                conf3_max * k_rad_to_deg,
                conf4_max * k_rad_to_deg);
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

raw_ref_diag_t raw_ref_to_ipm(double raw_x)
{
    const double raw_y = static_cast<double>(MT9V03X_H) * 0.98;
    raw_ref_diag_t out = {};
    float ipm_x = 0.0F;
    float ipm_y = 0.0F;
    atg_reference_raw_ref_to_ipm(static_cast<float>(raw_x),
                                 static_cast<float>(raw_y),
                                 &ipm_x,
                                 &ipm_y);
    out.x = static_cast<double>(ipm_x);
    out.y = static_cast<double>(ipm_y);
    return out;
}

line_error_diag_t line_error_diag(const float pts[][2], int num, int aim_distance)
{
    line_error_diag_t out = {};
    out.begin = -1;
    out.idx = -1;
    out.x = -1;
    out.y = -1;
    out.dist = -1;
    out.max_dist = -1;
    if(pts == nullptr || num <= 0)
    {
        return out;
    }

    double best_start = 1.0e30;
    int begin = -1;
    for(int i = 0; i < num; ++i)
    {
        const double dx = static_cast<double>(pts[i][0]) - static_cast<double>(cx);
        const double dy = static_cast<double>(pts[i][1]) - static_cast<double>(cy);
        const double d = dx * dx + dy * dy;
        if(d < best_start)
        {
            best_start = d;
            begin = i;
        }
    }
    if(begin < 0 || num - begin < 2)
    {
        return out;
    }

    int best = begin;
    int best_err = 1 << 30;
    int dist = 0;
    double last_x = static_cast<double>(cx);
    double last_y = static_cast<double>(cy);
    for(int i = begin; i < num; ++i)
    {
        const double x = static_cast<double>(pts[i][0]);
        const double y = static_cast<double>(pts[i][1]);
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

    const double x = static_cast<double>(pts[best][0]);
    const double y = static_cast<double>(pts[best][1]);
    const double dx = x - static_cast<double>(cx);
    const double dy = static_cast<double>(cy) - y + 0.2 * static_cast<double>(pixel_per_meter);
    out.ok = 1;
    out.begin = begin;
    out.idx = best;
    out.x = static_cast<int>(std::lround(x));
    out.y = static_cast<int>(std::lround(y));
    out.dx = dx;
    out.err_deg = -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
    return out;
}

void print_line_error_diag()
{
    const int aim_distance = atg_lookahead_dist_px();
    const line_error_diag_t left = line_error_diag(rptsc0, rptsc0_num, aim_distance);
    const line_error_diag_t right = line_error_diag(rptsc1, rptsc1_num, aim_distance);
    const line_error_diag_t selected = line_error_diag(rptsn, rptsn_num, aim_distance);
    const line_error_diag_t edge_left = line_error_diag(rpts0s, rpts0s_num, aim_distance);
    const line_error_diag_t edge_right = line_error_diag(rpts1s, rpts1s_num, aim_distance);
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
        edge_mid_dx = edge_mid_x - static_cast<double>(cx);
        const double edge_mid_dy =
            static_cast<double>(cy) - edge_mid_y + 0.2 * static_cast<double>(pixel_per_meter);
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
                cx,
                cy,
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
        for(int raw_x = 0; raw_x <= 140; raw_x += 5)
        {
            const raw_ref_diag_t ref = raw_ref_to_ipm(static_cast<double>(raw_x));
            const double dx = edge_mid_x - ref.x;
            const double dy = ref.y - edge_mid_y + 0.2 * static_cast<double>(pixel_per_meter);
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
                    atg_reference_vehicle_raw_ref_x(),
                    edge_mid_x,
                    edge_mid_y,
                    best_raw_x,
                    best_err,
                    best_ref.x,
                    best_ref.y,
                    scan);
    }
}

void print_cross_diag()
{
    const int half_left = cross_type == CROSS_HALF && Lpt0_found_flag;
    const int half_right = cross_type == CROSS_HALF && Lpt1_found_flag;
    std::printf("CrossDiag: type=%s track=%d half_lr=%d/%d "
                "nearL=%d@%d/%d@%d nearNum=%d/%d centerNum=%d/%d "
                "farL=%d@%d/%d@%d farNum=%d/%d farRaw=%d/%d "
                "lost=%d/%d not_have=%d final=%d/%d flags=%d/%d\n",
                cross_enum_name(cross_type),
                track_type,
                half_left,
                half_right,
                flag(Lpt0_found),
                Lpt0_found ? Lpt0_rpts0s_id : -1,
                flag(Lpt1_found),
                Lpt1_found ? Lpt1_rpts1s_id : -1,
                rpts0s_num,
                rpts1s_num,
                rptsc0_num,
                rptsc1_num,
                flag(far_Lpt0_found),
                far_Lpt0_found ? far_Lpt0_rpts0s_id : -1,
                flag(far_Lpt1_found),
                far_Lpt1_found ? far_Lpt1_rpts1s_id : -1,
                far_rpts0s_num,
                far_rpts1s_num,
                far_ipts0_num,
                far_ipts1_num,
                if_lost_left_line,
                if_lost_right_line,
                not_have_line,
                rpts_num,
                rptsn_num,
                Lpt0_found_flag,
                Lpt1_found_flag);
}

void print_atg_vision_diag()
{
    std::printf("ATGSeedDiag: seed=%d@%d,%d/%d@%d,%d begin=%d,%d block=%d clip=%d\n",
                atg_seed0_found,
                atg_seed0_x,
                atg_seed0_y,
                atg_seed1_found,
                atg_seed1_x,
                atg_seed1_y,
                begin_x,
                begin_y,
                block_size,
                clip_value);
    std::printf("ATGLptDiag: best=%d(%.1f) imip=%d/%d pass=%d%d%d%d%d acc=%d ipm=%.1f,%.1f inv=%.1f,%.1f "
                "| %d(%.1f) imip=%d/%d pass=%d%d%d%d%d acc=%d ipm=%.1f,%.1f inv=%.1f,%.1f\n",
                atg_lpt0_best_i,
                atg_lpt0_best_conf * k_rad_to_deg,
                atg_lpt0_best_im1,
                atg_lpt0_best_ip1,
                atg_lpt0_pass_nms,
                atg_lpt0_pass_low,
                atg_lpt0_pass_high,
                atg_lpt0_pass_near,
                atg_lpt0_pass_dir,
                atg_lpt0_accept_i,
                atg_lpt0_best_x,
                atg_lpt0_best_y,
                atg_lpt0_best_inv_x,
                atg_lpt0_best_inv_y,
                atg_lpt1_best_i,
                atg_lpt1_best_conf * k_rad_to_deg,
                atg_lpt1_best_im1,
                atg_lpt1_best_ip1,
                atg_lpt1_pass_nms,
                atg_lpt1_pass_low,
                atg_lpt1_pass_high,
                atg_lpt1_pass_near,
                atg_lpt1_pass_dir,
                atg_lpt1_accept_i,
                atg_lpt1_best_x,
                atg_lpt1_best_y,
                atg_lpt1_best_inv_x,
                atg_lpt1_best_inv_y);
}

void write_mid_report(std::ofstream &out, const runtime_t *rt)
{
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = atg_lookahead_dist_px();
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

void print_detail(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }

    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = atg_lookahead_dist_px();
    mid_points_for_report(rt->vision.mid,
                          rt->vision.control_ref.y,
                          aim_distance,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);

    print_atg_elements();
    print_atg_counts();
    print_atg_corners();
    print_atg_vision_diag();
    std::printf("ATGMid: line=%d step=%d ref=(%d,%d) m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d "
                "cxcy=%.1f,%.1f guide=%.2f atg_guide=%.1f/%.1f/%.1f\n",
                track_line_found(rt),
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
                cx,
                cy,
                rt->vision.guide_error,
                Guide,
                Guide_up,
                Guide_up_up);
    std::printf("ATGParam: begin=%d,%d block=%d clip=%d blur=%d sample=%.3f ppm=%d angle=%.3f road=%.3f "
                "aim=%.3f/%.3f/%.3f idx=%d/%d/%d ipm_source=atg_rot_inv_rot\n",
                begin_x,
                begin_y,
                block_size,
                clip_value,
                line_blur_kernel,
                sample_dist,
                pixel_per_meter,
                angle_dist,
                ROAD_WIDTH,
                static_cast<double>(aim_distance),
                aim_distance_far,
                round_aim_distance,
                aim_idx,
                aim_idx_up,
                aim_idx_up_up);
    std::printf("Loop: valid=%d stop=%d signed=%d target_yaw=%d yaw_cmd=%d actual_yaw=%d target_rps=%d/%d actual_rps=%d/%d duty=%d/%d\n",
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
                rt->control.right_duty);
}

void print_live(uint32_t frame_id, const runtime_t *rt, int div)
{
    live_beep_tick();
    if(rt == nullptr)
    {
        return;
    }
    const int force_log = read_env_flag("FRONT_CAR_FORCE_LIVE_LOG", 0);
    const int element_log = cross_type != CROSS_NONE || circle_type != CIRCLE_NONE;
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
    const int aim_distance = atg_lookahead_dist_px();
    mid_points_for_report(rt->vision.mid,
                          rt->vision.control_ref.y,
                          aim_distance,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);

    std::printf("frame=%u line=%d track=%d cross=%d circle=%d(%s) round=%d yroad=%d ramp=%d road=%d speed=%d "
                "near=%d/%d raw=%d/%d sel=%d/%d far=%d/%d far_raw=%d/%d "
                "l=%d@%d/%d@%d far_l=%d@%d/%d@%d straight=%d/%d far_straight=%d/%d "
                "circle_cnt=%d/%d/%d/%d lost=%d/%d conf=%.1f/%.1f/%.1f/%.1f dist=%d "
                "m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d cxcy=%.1f,%.1f guide=%.2f "
                "atg=%.1f/%.1f/%.1f pure=%.2f/%.2f yaw=%d cmd=%d actual=%d signed=%d rps=%d/%d:%d/%d duty=%d/%d\n",
                frame_id,
                track_line_found(rt),
                track_type,
                cross_type,
                circle_type,
                circle_enum_name(circle_type),
                round_type,
                yroad_type,
                ramp_type,
                road_type,
                speed_type,
                rpts0s_num,
                rpts1s_num,
                ipts0_num,
                ipts1_num,
                rpts_num,
                rptsn_num,
                far_rpts0s_num,
                far_rpts1s_num,
                far_ipts0_num,
                far_ipts1_num,
                flag(Lpt0_found),
                Lpt0_found ? Lpt0_rpts0s_id : -1,
                flag(Lpt1_found),
                Lpt1_found ? Lpt1_rpts1s_id : -1,
                flag(far_Lpt0_found),
                far_Lpt0_found ? far_Lpt0_rpts0s_id : -1,
                flag(far_Lpt1_found),
                far_Lpt1_found ? far_Lpt1_rpts1s_id : -1,
                flag(is_straight0),
                flag(is_straight1),
                flag(is_straight_far_0),
                flag(is_straight_far_1),
                none_left_line,
                none_right_line,
                have_left_line,
                have_right_line,
                flag(if_lost_left_line),
                flag(if_lost_right_line),
                conf1_max * k_rad_to_deg,
                conf2_max * k_rad_to_deg,
                conf3_max * k_rad_to_deg,
                conf4_max * k_rad_to_deg,
                total_distence,
                m0.x,
                m0.y,
                ml.x,
                ml.y,
                ml_dist,
                ml_forward,
                max_dist,
                cx,
                cy,
                rt->vision.guide_error,
                Guide,
                Guide_up,
                Guide_up_up,
                pure_angle,
                pure_angle_up,
                rt->control.target_yaw_rate_mrad_s,
                rt->control.yaw_cmd_mrad_s,
                rt->control.actual_yaw_rate_mrad_s,
                rt->control.signed_output,
                rt->control.left_target_rps_milli,
                rt->control.right_target_rps_milli,
                rt->control.left_actual_rps_milli,
                rt->control.right_actual_rps_milli,
                rt->control.left_duty,
                rt->control.right_duty);
    print_cross_diag();
    print_line_error_diag();
    print_atg_vision_diag();
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

    out << "line_found=" << track_line_found(rt) << "\n";
    out << "ipm_source=atg_rot_inv_rot\n";
    out << "atg_track_type=" << track_type << "\n";
    out << "atg_cross_type=" << cross_type << "\n";
    out << "atg_circle_type=" << circle_type << "\n";
    out << "atg_round_type=" << round_type << "\n";
    out << "atg_yroad_type=" << yroad_type << "\n";
    out << "atg_ramp_type=" << ramp_type << "\n";
    out << "atg_road_type=" << road_type << "\n";
    out << "atg_speed_type=" << speed_type << "\n";
    out << "atg_not_have_line=" << not_have_line << "\n";
    out << "atg_total_distence=" << total_distence << "\n";
    out << "atg_ramp_total_distence=" << Ramp_total_distence << "\n";

    out << "atg_ipts0_num=" << ipts0_num << "\n";
    out << "atg_ipts1_num=" << ipts1_num << "\n";
    out << "atg_rpts0_num=" << rpts0_num << "\n";
    out << "atg_rpts1_num=" << rpts1_num << "\n";
    out << "atg_rpts0s_num=" << rpts0s_num << "\n";
    out << "atg_rpts1s_num=" << rpts1s_num << "\n";
    out << "atg_rptsc0_num=" << rptsc0_num << "\n";
    out << "atg_rptsc1_num=" << rptsc1_num << "\n";
    out << "atg_rpts_num=" << rpts_num << "\n";
    out << "atg_rptsn_num=" << rptsn_num << "\n";
    out << "atg_far_ipts0_num=" << far_ipts0_num << "\n";
    out << "atg_far_ipts1_num=" << far_ipts1_num << "\n";
    out << "atg_far_rpts0s_num=" << far_rpts0s_num << "\n";
    out << "atg_far_rpts1s_num=" << far_rpts1s_num << "\n";

    out << "atg_is_straight0=" << flag(is_straight0) << "\n";
    out << "atg_is_straight1=" << flag(is_straight1) << "\n";
    out << "atg_is_straight_far_0=" << flag(is_straight_far_0) << "\n";
    out << "atg_is_straight_far_1=" << flag(is_straight_far_1) << "\n";
    out << "atg_lpt0_found=" << flag(Lpt0_found) << "\n";
    out << "atg_lpt1_found=" << flag(Lpt1_found) << "\n";
    out << "atg_lpt0_id=" << (Lpt0_found ? Lpt0_rpts0s_id : -1) << "\n";
    out << "atg_lpt1_id=" << (Lpt1_found ? Lpt1_rpts1s_id : -1) << "\n";
    out << "atg_ypt0_found=" << flag(Ypt0_found) << "\n";
    out << "atg_ypt1_found=" << flag(Ypt1_found) << "\n";
    out << "atg_ypt0_id=" << (Ypt0_found ? Ypt0_rpts0s_id : -1) << "\n";
    out << "atg_ypt1_id=" << (Ypt1_found ? Ypt1_rpts1s_id : -1) << "\n";
    out << "atg_far_lpt0_found=" << flag(far_Lpt0_found) << "\n";
    out << "atg_far_lpt1_found=" << flag(far_Lpt1_found) << "\n";
    out << "atg_far_lpt0_id=" << (far_Lpt0_found ? far_Lpt0_rpts0s_id : -1) << "\n";
    out << "atg_far_lpt1_id=" << (far_Lpt1_found ? far_Lpt1_rpts1s_id : -1) << "\n";
    out << "atg_conf1_max_deg=" << conf1_max * k_rad_to_deg << "\n";
    out << "atg_conf2_max_deg=" << conf2_max * k_rad_to_deg << "\n";
    out << "atg_conf3_max_deg=" << conf3_max * k_rad_to_deg << "\n";
    out << "atg_conf4_max_deg=" << conf4_max * k_rad_to_deg << "\n";
    out << "atg_seed0_found=" << atg_seed0_found << "\n";
    out << "atg_seed1_found=" << atg_seed1_found << "\n";
    out << "atg_seed0_xy=" << atg_seed0_x << "," << atg_seed0_y << "\n";
    out << "atg_seed1_xy=" << atg_seed1_x << "," << atg_seed1_y << "\n";
    out << "atg_lpt0_best=" << atg_lpt0_best_i << "," << atg_lpt0_best_conf * k_rad_to_deg << "\n";
    out << "atg_lpt1_best=" << atg_lpt1_best_i << "," << atg_lpt1_best_conf * k_rad_to_deg << "\n";
    out << "atg_lpt0_best_imip=" << atg_lpt0_best_im1 << "," << atg_lpt0_best_ip1 << "\n";
    out << "atg_lpt1_best_imip=" << atg_lpt1_best_im1 << "," << atg_lpt1_best_ip1 << "\n";
    out << "atg_lpt0_pass=" << atg_lpt0_pass_nms << "," << atg_lpt0_pass_low << "," << atg_lpt0_pass_high << ","
        << atg_lpt0_pass_near << "," << atg_lpt0_pass_dir << "\n";
    out << "atg_lpt1_pass=" << atg_lpt1_pass_nms << "," << atg_lpt1_pass_low << "," << atg_lpt1_pass_high << ","
        << atg_lpt1_pass_near << "," << atg_lpt1_pass_dir << "\n";
    out << "atg_lpt0_accept_i=" << atg_lpt0_accept_i << "\n";
    out << "atg_lpt1_accept_i=" << atg_lpt1_accept_i << "\n";
    out << "atg_lpt0_best_ipm=" << atg_lpt0_best_x << "," << atg_lpt0_best_y << "\n";
    out << "atg_lpt1_best_ipm=" << atg_lpt1_best_x << "," << atg_lpt1_best_y << "\n";
    out << "atg_lpt0_best_inv=" << atg_lpt0_best_inv_x << "," << atg_lpt0_best_inv_y << "\n";
    out << "atg_lpt1_best_inv=" << atg_lpt1_best_inv_x << "," << atg_lpt1_best_inv_y << "\n";

    out << "atg_begin_x=" << begin_x << "\n";
    out << "atg_begin_y=" << begin_y << "\n";
    out << "atg_block_size=" << block_size << "\n";
    out << "atg_clip_value=" << clip_value << "\n";
    out << "atg_line_blur_kernel=" << line_blur_kernel << "\n";
    out << "atg_sample_dist=" << sample_dist << "\n";
    out << "atg_pixel_per_meter=" << pixel_per_meter << "\n";
    out << "atg_angle_dist=" << angle_dist << "\n";
    out << "atg_road_width=" << ROAD_WIDTH << "\n";
    out << "atg_aim_distance=" << aim_distance << "\n";
    out << "atg_aim_distance_far=" << aim_distance_far << "\n";
    out << "atg_round_aim_distance=" << round_aim_distance << "\n";
    out << "atg_aim_idx=" << aim_idx << "\n";
    out << "atg_aim_idx_up=" << aim_idx_up << "\n";
    out << "atg_aim_idx_up_up=" << aim_idx_up_up << "\n";
    out << "atg_cx=" << cx << "\n";
    out << "atg_cy=" << cy << "\n";
    out << "atg_guide=" << Guide << "\n";
    out << "atg_guide_up=" << Guide_up << "\n";
    out << "atg_guide_up_up=" << Guide_up_up << "\n";

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
    return 1;
}
