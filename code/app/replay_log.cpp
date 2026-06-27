#include "app/replay_log.hpp"

#include "app/report.hpp"
#include "tracking/atg_reference_mainline.hpp"

#include <cmath>
#include <cstdio>

void print_replay_frame(int frame, const runtime_t *rt)
{
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = atg_lookahead_dist_px();
    const atg_replay_snapshot_t atg = atg_replay_snapshot();
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
                track_line_found(rt),
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
