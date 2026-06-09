#include "app/report.hpp"

#include "tracking/boundary.hpp"
#include "tracking/imgproc.hpp"
#include "tracking/mainline.hpp"
#include "tracking/perspective.hpp"

#include <cmath>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>

namespace
{
constexpr const char *k_live_beep_path = "/dev/zf_gpio_beep";
constexpr int k_live_beep_ms = 35;
constexpr int k_report_near_lost_step = 5;
constexpr int k_report_near_recover_step = 20;

using live_state_signature_t = std::array<int, 67>;

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

    const char *enabled = std::getenv("FRONT_CAR_STATE_BEEP");
    if(enabled != nullptr && enabled[0] == '0')
    {
        fd = -1;
        return fd;
    }

    const char *path = std::getenv("FRONT_CAR_BEEP_PATH");
    if(path == nullptr || path[0] == '\0')
    {
        path = k_live_beep_path;
    }
    fd = open(path, O_WRONLY | O_CLOEXEC);
    return fd;
}

uint64_t &live_beep_off_at_us()
{
    static uint64_t value = 0;
    return value;
}

void write_live_beep_level(int level)
{
    const int fd = live_beep_fd();
    if(fd < 0)
    {
        return;
    }

    char c = level ? '1' : '0';
    lseek(fd, 0, SEEK_SET);
    const ssize_t written = write(fd, &c, 1);
    (void)written;
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

    write_live_beep_level(1);
    uint64_t &off_at_us = live_beep_off_at_us();
    off_at_us = report_monotonic_us() + static_cast<uint64_t>(k_live_beep_ms) * 1000U;
}

int near_step_bucket(int step)
{
    if(step < k_report_near_lost_step)
    {
        return 0;
    }
    if(step > k_report_near_recover_step)
    {
        return 2;
    }
    return 1;
}

int positive_bucket(int value)
{
    return value > 0 ? 1 : 0;
}

int bucket8(int value)
{
    if(value < 0)
    {
        return -1;
    }
    return value / 8;
}

live_state_signature_t make_live_state_signature(const runtime_t *rt)
{
    const auto &tr = rt->track;
    const auto &cz = rt->cross;
    return {
        track_line_found(rt),
        rt->ring.kind,
        rt->ring.state,
        cz.state,
        cz.track_type,
        positive_bucket(cz.not_have_line),
        rt->zebra.detected,
        rt->zebra.stop_line,
        tr.reject_reason,
        tr.track_type,
        positive_bucket(tr.mid.step),
        tr.action_cross_state0,
        tr.action_base_ready,
        tr.mode_cross_far,
        tr.mode_cross_near,
        tr.mode_ring_active,
        tr.mode_work_track_type,
        near_step_bucket(cz.left_near_step),
        near_step_bucket(cz.right_near_step),
        cz.both_near_lost,
        cz.both_near_recover,
        cz.exit_ready,
        cz.left_far_found,
        cz.right_far_found,
        cz.left_far_ok,
        cz.right_far_ok,
        cz.left_far_fail,
        cz.right_far_fail,
        positive_bucket(cz.left_num),
        positive_bucket(cz.right_num),
        cz.left_l >= 0 ? 1 : 0,
        cz.right_l >= 0 ? 1 : 0,
        cz.left_far_l_source,
        cz.right_far_l_source,
        tr.cross_mid_side,
        tr.cross_mid_fail,
        positive_bucket(tr.cross_mid_out),
        tr.left.l_found,
        tr.left.l_ok,
        tr.left.l_pair_ok,
        tr.left.l_pair_state,
        tr.right.l_found,
        tr.right.l_ok,
        tr.right.l_pair_ok,
        tr.right.l_pair_state,
        tr.action_ring_kind0,
        tr.action_ring_state0,
        tr.seed_state_find,
        positive_bucket(tr.trace_left_raw_step),
        positive_bucket(tr.trace_right_raw_step),
        positive_bucket(tr.trace_left_raw_gain),
        positive_bucket(tr.trace_right_raw_gain),
        positive_bucket(tr.trace_left_pass_right_gain),
        positive_bucket(tr.trace_right_pass_left_gain),
        tr.trace_identity_reject,
        tr.candidate_crop_side,
        positive_bucket(tr.candidate_crop_index + 1),
        positive_bucket(tr.candidate_left_before_crop),
        positive_bucket(tr.candidate_right_before_crop),
        positive_bucket(tr.candidate_left_after_crop),
        positive_bucket(tr.candidate_right_after_crop),
        positive_bucket(tr.selected_mid_ok),
        tr.search_update_kind,
        bucket8(tr.search_mid_before),
        bucket8(tr.search_mid_after),
        bucket8(tr.width_base_before),
        bucket8(tr.width_base_after)
    };
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

// 计算两点之间的欧式距离，用于报告里的 seed IPM 诊断。
double point_distance(point_t a, point_t b)
{
    return std::hypot((double)a.x - b.x, (double)a.y - b.y);
}

int report_seed_pair_span(const runtime_t *rt)
{
    if(rt == nullptr || !seed_pair_accepted(&rt->seeds, rt->seed_state))
    {
        return -1;
    }
    return rt->seeds.right.x - rt->seeds.left.x;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      诊断同排 seed pair 映射到 IPM 后的跨度是否异常
//  @return     int          SEED_IPM_DIAG_xxx 枚举之一
//  @note       这里只做报告输出；seed 仍只是 trace 起点，不是 tracking 成败门。
//-------------------------------------------------------------------------------------------------------------------
int report_seed_ipm_pair_diag(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return SEED_IPM_DIAG_NO_PAIR;
    }
    if(!seed_pair_accepted(&rt->seeds, rt->seed_state))
    {
        return SEED_IPM_DIAG_NO_PAIR;
    }
    if(!rt->has_matrix)
    {
        return SEED_IPM_DIAG_NO_MATRIX;
    }

    point_t p0 = {-1, -1};
    point_t p1 = {-1, -1};
    int ok0 = 0;
    int ok1 = 0;
    perspective_point(rt->matrix, &rt->seeds.left, &p0, &ok0);
    perspective_point(rt->matrix, &rt->seeds.right, &p1, &ok1);
    if(!ok0 || !ok1)
    {
        return SEED_IPM_DIAG_MAP_FAILED;
    }

    const double w = point_distance(p0, p1);
    if(w < ROAD_HALF_WIDTH)
    {
        return SEED_IPM_DIAG_SPAN_TOO_SMALL;
    }
    if(w > RAW_W - 2)
    {
        return SEED_IPM_DIAG_SPAN_TOO_LARGE;
    }
    return SEED_IPM_DIAG_OK;
}

}

// 取中线起点和预瞄附近点，供单行日志和报告输出。
void mid_points_for_report(const midline_t &mid,
                           int ref_y,
                           point_t *m0,
                           point_t *ml,
                           int *ml_dist,
                           int *max_dist,
                           int *forward_ok)
{
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
        const int err = std::abs(mid.dist[i] - LOOKAHEAD_DIST);
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }
    *ml = mid.pts[best];
    *ml_dist = mid.dist[best];
    *forward_ok = midline_has_forward_lookahead(&mid, LOOKAHEAD_DIST, ref_y);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      打印当前帧的详细调试信息（种子、控制基准、IPM、左右轨迹、中线、控制环、元素状态）
//  @return     void
//  @note       只读 runtime_t，不修改 tracking/control 状态。
//-------------------------------------------------------------------------------------------------------------------
void print_detail(const runtime_t *rt)
{
    const auto &sd = rt->seeds;
    const auto &tr = rt->track;
    const auto &tr0 = rt->left_trace;
    const auto &tr1 = rt->right_trace;
    const auto &rg = rt->ring;
    const auto &cz = rt->cross;
    const auto &zb = rt->zebra;
    const int use_matrix = rt->has_matrix;
    const int seed_span = report_seed_pair_span(rt);
    const int ipm_reason = report_seed_ipm_pair_diag(rt);

    std::printf("Seed: left=(%d,%d) right=(%d,%d) row=%d pair_span=%d "
                "pre=%d:(%d,%d)-(%d,%d)\n",
                sd.left.x,
                sd.left.y,
                sd.right.x,
                sd.right.y,
                sd.row,
                seed_span,
                tr.seed_state_find,
                tr.seed_left_find.x,
                tr.seed_left_find.y,
                tr.seed_right_find.x,
                tr.seed_right_find.y);
    std::printf("SeedState: filtered=%d search_center=%d track=%d\n",
                rt->seed_state,
                rt->mid_position,
                tr.track_type);
    std::printf("CtlX: x=%d\n", rt->control_center_x);
    std::printf("IPM: loaded=%d frame=%d reason=%d\n",
                rt->has_matrix,
                use_matrix,
                ipm_reason);
    std::printf("Trace: left=%d right=%d raw=%d/%d gain=%d/%d pass=%d/%d idrej=%d\n",
                tr0.step,
                tr1.step,
                tr.trace_left_raw_step,
                tr.trace_right_raw_step,
                tr.trace_left_raw_gain,
                tr.trace_right_raw_gain,
                tr.trace_left_pass_right_gain,
                tr.trace_right_pass_left_gain,
                tr.trace_identity_reject);
    std::printf("CornerL: left=%d/%d@%d/%.1f pair=%d state=%d w=%.1f/%.1f "
                "right=%d/%d@%d/%.1f pair=%d state=%d w=%.1f/%.1f\n",
                tr.left.l_found,
                tr.left.l_ok,
                tr.left.l_now_index,
                tr.left.l_angle_deg,
                tr.left.l_pair_ok,
                tr.left.l_pair_state,
                tr.left.l_pair_width0,
                tr.left.l_pair_width1,
                tr.right.l_found,
                tr.right.l_ok,
                tr.right.l_now_index,
                tr.right.l_angle_deg,
                tr.right.l_pair_ok,
                tr.right.l_pair_state,
                tr.right.l_pair_width0,
                tr.right.l_pair_width1);
    std::printf("Mid: step=%d center=%d guide=%.2f rej=%d\n",
                tr.mid.step,
                tr.center_x,
                tr.guide_error,
                tr.reject_reason);
    std::printf("Cand: crop=%d/%d before=%d/%d after=%d/%d mid_ok=%d\n",
                tr.candidate_crop_side,
                tr.candidate_crop_index,
                tr.candidate_left_before_crop,
                tr.candidate_right_before_crop,
                tr.candidate_left_after_crop,
                tr.candidate_right_after_crop,
                tr.selected_mid_ok);
    std::printf("SearchPrior: kind=%d center=%d/%d width=%d/%d\n",
                tr.search_update_kind,
                tr.search_mid_before,
                tr.search_mid_after,
                tr.width_base_before,
                tr.width_base_after);
    std::printf("CrossDbg: mode=%d/%d/%d/%d/%d ring0=%d/%d ref=(%d,%d) "
                "near=%d/%d lost=%d rec=%d exit=%d far_ok=%d/%d "
                "far_fail=%d/%d far_seed=(%d,%d)/(%d,%d) "
                "far_n=%d/%d/%d/%d @ %d/%d/%d/%d lsrc=%d/%d reuse=%d/%d "
                "mid=%d/%d/%d/%d/%d/%d\n",
                tr.action_cross_state0,
                tr.action_base_ready,
                tr.mode_cross_far,
                tr.mode_cross_near,
                tr.mode_work_track_type,
                tr.action_ring_kind0,
                tr.action_ring_state0,
                tr.control_ref.x,
                tr.control_ref.y,
                cz.left_near_step,
                cz.right_near_step,
                cz.both_near_lost,
                cz.both_near_recover,
                cz.exit_ready,
                cz.left_far_ok,
                cz.right_far_ok,
                cz.left_far_fail,
                cz.right_far_fail,
                cz.left_far_seed.x,
                cz.left_far_seed.y,
                cz.right_far_seed.x,
                cz.right_far_seed.y,
                cz.left_far_trace,
                cz.left_far_ipm,
                cz.left_far_blur,
                cz.left_far_resample,
                cz.right_far_trace,
                cz.right_far_ipm,
                cz.right_far_blur,
                cz.right_far_resample,
                cz.left_far_l_source,
                cz.right_far_l_source,
                cz.left_far_l_reuse_count,
                cz.right_far_l_reuse_count,
                tr.cross_mid_side,
                tr.cross_mid_fail,
                tr.cross_mid_start,
                tr.cross_mid_tail,
                tr.cross_mid_cand,
                tr.cross_mid_out);
    std::printf("Loop: valid=%d stop=%d target_yaw=%d actual_yaw=%d duty=%d/%d\n",
                rt->control.input_valid,
                rt->control.stop_request,
                rt->control.target_yaw_rate_mrad_s,
                rt->control.actual_yaw_rate_mrad_s,
                rt->control.left_duty,
                rt->control.right_duty);
    std::printf("Elem: ring=%d/%d "
                "cross=%d nf=%d far=%d/%d num=%d/%d l=%d/%d "
                "zebra=%d stop=%d\n",
                rg.kind,
                rg.state,
                cz.state,
                cz.not_have_line,
                cz.left_far_found,
                cz.right_far_found,
                cz.left_num,
                cz.right_num,
                cz.left_l,
                cz.right_l,
                zb.detected,
                zb.stop_line);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      打印实时模式下的单行帧摘要（按分频在 publish 同步点调用）
//  @return     void
//  @note       line 字段使用 track_line_found()；mid 点是控制中线坐标，不是 assistant 原图红线。
//-------------------------------------------------------------------------------------------------------------------
void print_live(uint32_t frame_id, const runtime_t *rt)
{
    live_beep_tick();
    if(rt == nullptr)
    {
        return;
    }

    const live_state_signature_t sig = make_live_state_signature(rt);
    const int changed = live_state_changed(sig);
    if(!changed)
    {
        return;
    }
    if(frame_id != 0U)
    {
        live_beep_once();
    }

    const auto &sd = rt->seeds;
    const auto &tr = rt->track;
    const auto &tr0 = rt->left_trace;
    const auto &tr1 = rt->right_trace;
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    mid_points_for_report(tr.mid, tr.control_ref.y, &m0, &ml, &ml_dist, &max_dist, &ml_forward);

    // 字段缩写：cf=左/右远线found，cn=左/右远线点数，cl=左/右远 L 索引，cs=远 L 来源，cr=连续复用帧数；
    //   l=左 found/ok/now_index @ 右 found/ok/now_index；pair=左/右 strict double-L 复核结果；
    //   ps=左/右 pair_state；pw=双 L 基准/张开宽度；
    //   pre=find_seeds后state/seed和trace过滤前步数；tg=trace过滤前纵向爬升量；tp=trace越过对侧seed时的爬升量；
    //   xst=帧首cross/base/cross_far/cross_near/ring_active/work_track/ref；
    //   xcrop=ring裁剪side/index + rptsc0/rptsc1裁剪前/后 + selected mid_ok；
    //   xlearn=seed 搜索先验学习 kind/search_center_before/search_center_after/width_before/width_after；
    //   xfar=近线步数/lost/recover/exit/far_ok/far_fail/far_trace/ipm/blur/resample；
    //   xmid=远线中线 side/fail/start/tail/cand/out；m0=中线起点，ml=预瞄点，md=预瞄距离/前方门/最大距离；
    //   yaw=target_yaw(mrad/s)，duty=左/右占空。
    std::printf("frame=%u ring=%d/%d r0=%d/%d cross=%d cf=%d/%d cn=%d/%d cl=%d/%d cs=%d/%d cr=%d/%d "
                "zebra=%d line=%d rej=%d track=%d mid=%d "
                "seed=(%d,%d)-(%d,%d) trace=%d/%d pre=%d:(%d,%d)-(%d,%d)/%d/%d tg=%d/%d tp=%d/%d idrej=%d "
                "l=%d/%d@%d/%d/%d@%d pair=%d/%d ps=%d/%d pw=%.1f/%.1f "
                "xst=%d/%d/%d/%d/%d/%d@%d,%d "
                "xcrop=%d/%d/%d/%d/%d/%d/%d "
                "xlearn=%d/%d/%d/%d/%d "
                "xfar=%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d/%d "
                "xmid=%d/%d/%d/%d/%d/%d "
                "center=%d m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d guide=%.2f "
                "loop=%d stop=%d yaw=%d duty=%d/%d\n",
                frame_id,
                rt->ring.kind,
                rt->ring.state,
                tr.action_ring_kind0,
                tr.action_ring_state0,
                rt->cross.state,
                rt->cross.left_far_found,
                rt->cross.right_far_found,
                rt->cross.left_num,
                rt->cross.right_num,
                rt->cross.left_l,
                rt->cross.right_l,
                rt->cross.left_far_l_source,
                rt->cross.right_far_l_source,
                rt->cross.left_far_l_reuse_count,
                rt->cross.right_far_l_reuse_count,
                rt->zebra.detected,
                track_line_found(rt),
                tr.reject_reason,
                tr.track_type,
                tr.mid.step,
                sd.left.x,
                sd.left.y,
                sd.right.x,
                sd.right.y,
                tr0.step,
                tr1.step,
                tr.seed_state_find,
                tr.seed_left_find.x,
                tr.seed_left_find.y,
                tr.seed_right_find.x,
                tr.seed_right_find.y,
                tr.trace_left_raw_step,
                tr.trace_right_raw_step,
                tr.trace_left_raw_gain,
                tr.trace_right_raw_gain,
                tr.trace_left_pass_right_gain,
                tr.trace_right_pass_left_gain,
                tr.trace_identity_reject,
                tr.left.l_found,
                tr.left.l_ok,
                tr.left.l_now_index,
                tr.right.l_found,
                tr.right.l_ok,
                tr.right.l_now_index,
                tr.left.l_pair_ok,
                tr.right.l_pair_ok,
                tr.left.l_pair_state,
                tr.right.l_pair_state,
                tr.left.l_pair_width0,
                tr.left.l_pair_width1,
                tr.action_cross_state0,
                tr.action_base_ready,
                tr.mode_cross_far,
                tr.mode_cross_near,
                tr.mode_ring_active,
                tr.mode_work_track_type,
                tr.control_ref.x,
                tr.control_ref.y,
                tr.candidate_crop_side,
                tr.candidate_crop_index,
                tr.candidate_left_before_crop,
                tr.candidate_right_before_crop,
                tr.candidate_left_after_crop,
                tr.candidate_right_after_crop,
                tr.selected_mid_ok,
                tr.search_update_kind,
                tr.search_mid_before,
                tr.search_mid_after,
                tr.width_base_before,
                tr.width_base_after,
                rt->cross.left_near_step,
                rt->cross.right_near_step,
                rt->cross.both_near_lost,
                rt->cross.both_near_recover,
                rt->cross.exit_ready,
                rt->cross.left_far_ok,
                rt->cross.right_far_ok,
                rt->cross.left_far_fail,
                rt->cross.right_far_fail,
                rt->cross.left_far_trace,
                rt->cross.right_far_trace,
                rt->cross.left_far_ipm,
                rt->cross.right_far_ipm,
                rt->cross.left_far_blur,
                rt->cross.right_far_blur,
                rt->cross.left_far_resample,
                rt->cross.right_far_resample,
                tr.cross_mid_side,
                tr.cross_mid_fail,
                tr.cross_mid_start,
                tr.cross_mid_tail,
                tr.cross_mid_cand,
                tr.cross_mid_out,
                tr.center_x,
                m0.x,
                m0.y,
                ml.x,
                ml.y,
                ml_dist,
                ml_forward,
                max_dist,
                tr.guide_error,
                rt->control.input_valid,
                rt->control.stop_request,
                rt->control.target_yaw_rate_mrad_s,
                rt->control.left_duty,
                rt->control.right_duty);
    std::fflush(stdout);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      将当前 runtime 的关键状态以 key=value 形式写入报告文件
//  @return     int          1 写入成功 / 0 失败（参数无效或文件无法打开）
//  @note       报告用于离线排查，不参与实车控制链。
//-------------------------------------------------------------------------------------------------------------------
int write_report(const runtime_t *rt, const char *report_path)
{
    if(rt == nullptr || report_path == nullptr)
    {
        return 0;
    }

    std::ofstream out(report_path);
    if(!out.is_open())
    {
        return 0;
    }

    out << "line_found=" << track_line_found(rt) << "\n";
    out << "track_reject_reason=" << rt->track.reject_reason << "\n";
    out << "track_type=" << rt->track.track_type << "\n";
    out << "action_ring_kind0=" << rt->track.action_ring_kind0 << "\n";
    out << "action_ring_state0=" << rt->track.action_ring_state0 << "\n";
    out << "candidate_crop_side=" << rt->track.candidate_crop_side << "\n";
    out << "candidate_crop_index=" << rt->track.candidate_crop_index << "\n";
    out << "candidate_left_before_crop=" << rt->track.candidate_left_before_crop << "\n";
    out << "candidate_right_before_crop=" << rt->track.candidate_right_before_crop << "\n";
    out << "candidate_left_after_crop=" << rt->track.candidate_left_after_crop << "\n";
    out << "candidate_right_after_crop=" << rt->track.candidate_right_after_crop << "\n";
    out << "selected_mid_ok=" << rt->track.selected_mid_ok << "\n";
    out << "search_update_kind=" << rt->track.search_update_kind << "\n";
    out << "search_mid_before=" << rt->track.search_mid_before << "\n";
    out << "search_mid_after=" << rt->track.search_mid_after << "\n";
    out << "width_base_before=" << rt->track.width_base_before << "\n";
    out << "width_base_after=" << rt->track.width_base_after << "\n";
    out << "seed_search_center_before=" << rt->track.search_mid_before << "\n";
    out << "seed_search_center_after=" << rt->track.search_mid_after << "\n";
    out << "seed_width_prior_before=" << rt->track.width_base_before << "\n";
    out << "seed_width_prior_after=" << rt->track.width_base_after << "\n";

    const int ipm_reason = report_seed_ipm_pair_diag(rt);
    out << "matrix_loaded=" << rt->has_matrix << "\n";
    out << "seed_ipm_pair_diag=" << ipm_reason << "\n";

    out << "ring_kind=" << rt->ring.kind << "\n";
    out << "ring_state=" << rt->ring.state << "\n";
    out << "cross_state=" << rt->cross.state << "\n";
    out << "cross_not_have_line=" << rt->cross.not_have_line << "\n";
    out << "cross_left_far_found=" << rt->cross.left_far_found << "\n";
    out << "cross_right_far_found=" << rt->cross.right_far_found << "\n";
    out << "cross_left_num=" << rt->cross.left_num << "\n";
    out << "cross_right_num=" << rt->cross.right_num << "\n";
    out << "cross_left_l=" << rt->cross.left_l << "\n";
    out << "cross_right_l=" << rt->cross.right_l << "\n";
    out << "cross_left_l_source=" << rt->cross.left_far_l_source << "\n";
    out << "cross_right_l_source=" << rt->cross.right_far_l_source << "\n";
    out << "cross_left_l_reuse_count=" << rt->cross.left_far_l_reuse_count << "\n";
    out << "cross_right_l_reuse_count=" << rt->cross.right_far_l_reuse_count << "\n";
    out << "zebra_detected=" << rt->zebra.detected << "\n";
    out << "zebra_stop_line=" << rt->zebra.stop_line << "\n";

    out << "mid_position=" << rt->mid_position << "\n";
    out << "seed_search_center=" << rt->mid_position << "\n";
    out << "seed_width_prior=" << rt->width_base << "\n";
    out << "control_center_x=" << rt->control_center_x << "\n";
    out << "left_seed=" << rt->seeds.left.x << "," << rt->seeds.left.y << "\n";
    out << "right_seed=" << rt->seeds.right.x << "," << rt->seeds.right.y << "\n";
    out << "seed_row=" << rt->seeds.row << "\n";
    out << "seed_pair_span=" << report_seed_pair_span(rt) << "\n";
    out << "seed_state_find=" << rt->track.seed_state_find << "\n";
    out << "left_seed_find=" << rt->track.seed_left_find.x << "," << rt->track.seed_left_find.y << "\n";
    out << "right_seed_find=" << rt->track.seed_right_find.x << "," << rt->track.seed_right_find.y << "\n";

    out << "left_trace_step=" << rt->left_trace.step << "\n";
    out << "right_trace_step=" << rt->right_trace.step << "\n";
    out << "left_trace_raw_step=" << rt->track.trace_left_raw_step << "\n";
    out << "right_trace_raw_step=" << rt->track.trace_right_raw_step << "\n";
    out << "left_trace_raw_gain=" << rt->track.trace_left_raw_gain << "\n";
    out << "right_trace_raw_gain=" << rt->track.trace_right_raw_gain << "\n";
    out << "left_trace_pass_right_gain=" << rt->track.trace_left_pass_right_gain << "\n";
    out << "right_trace_pass_left_gain=" << rt->track.trace_right_pass_left_gain << "\n";
    out << "trace_identity_reject=" << rt->track.trace_identity_reject << "\n";
    out << "left_l_found=" << rt->track.left.l_found << "\n";
    out << "left_l_ok=" << rt->track.left.l_ok << "\n";
    out << "left_l_now_index=" << rt->track.left.l_now_index << "\n";
    out << "left_l_original_index=" << rt->track.left.l_original_index << "\n";
    out << "left_l_angle_deg=" << rt->track.left.l_angle_deg << "\n";
    out << "left_l_pair_ok=" << rt->track.left.l_pair_ok << "\n";
    out << "left_l_pair_state=" << rt->track.left.l_pair_state << "\n";
    out << "left_l_pair_width0=" << rt->track.left.l_pair_width0 << "\n";
    out << "left_l_pair_width1=" << rt->track.left.l_pair_width1 << "\n";
    out << "right_l_found=" << rt->track.right.l_found << "\n";
    out << "right_l_ok=" << rt->track.right.l_ok << "\n";
    out << "right_l_now_index=" << rt->track.right.l_now_index << "\n";
    out << "right_l_original_index=" << rt->track.right.l_original_index << "\n";
    out << "right_l_angle_deg=" << rt->track.right.l_angle_deg << "\n";
    out << "right_l_pair_ok=" << rt->track.right.l_pair_ok << "\n";
    out << "right_l_pair_state=" << rt->track.right.l_pair_state << "\n";
    out << "right_l_pair_width0=" << rt->track.right.l_pair_width0 << "\n";
    out << "right_l_pair_width1=" << rt->track.right.l_pair_width1 << "\n";
    out << "mid_step=" << rt->track.mid.step << "\n";
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    mid_points_for_report(rt->track.mid,
                          rt->track.control_ref.y,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);
    out << "mid0=" << m0.x << "," << m0.y << "\n";
    out << "mid_look=" << ml.x << "," << ml.y << "\n";
    out << "mid_look_dist=" << ml_dist << "\n";
    out << "mid_max_dist=" << max_dist << "\n";
    out << "mid_forward_lookahead=" << ml_forward << "\n";
    out << "center_x=" << rt->track.center_x << "\n";
    out << "guide_error=" << rt->track.guide_error << "\n";
    return 1;
}
