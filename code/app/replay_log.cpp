#include "app/replay_log.hpp"

#include "app/report.hpp"
#include "tracking/atg_reference_mainline.hpp"

#include <cmath>
#include <cstdio>

extern "C" {
#include "atg_reference_step.h"
#include "headfile.h"
}

void print_replay_frame(int frame, const runtime_t *rt)
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

    std::printf("replay frame=%d line=%d track=%d cross=%d circle=%d round=%d yroad=%d ramp=%d road=%d speed=%d "
                "near=%d/%d raw=%d/%d ipm=%d/%d center=%d/%d sel=%d/%d src=%d "
                "l=%d@%d/%d@%d y=%d@%d/%d@%d far_l=%d@%d/%d@%d far_num=%d/%d "
                "straight=%d/%d far_straight=%d/%d conf=%.1f/%.1f/%.1f/%.1f "
                "dist=%d begin=%lld/%lld ramp_dist=%d m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d "
                "cxcy=%.1f,%.1f guide=%.2f atg_guide=%.1f/%.1f/%.1f "
                "duty=%d/%d pwm=PWM2:%d/PWM1:%d motor=2:%d/1:%d\n",
                frame,
                track_line_found(rt),
                track_type,
                cross_type,
                circle_type,
                round_type,
                yroad_type,
                ramp_type,
                road_type,
                speed_type,
                rpts0s_num,
                rpts1s_num,
                ipts0_num,
                ipts1_num,
                rpts0_num,
                rpts1_num,
                rptsc0_num,
                rptsc1_num,
                rpts_num,
                rptsn_num,
                atg_reference_selected_line_source_id(),
                Lpt0_found ? 1 : 0,
                Lpt0_found ? Lpt0_rpts0s_id : -1,
                Lpt1_found ? 1 : 0,
                Lpt1_found ? Lpt1_rpts1s_id : -1,
                Ypt0_found ? 1 : 0,
                Ypt0_found ? Ypt0_rpts0s_id : -1,
                Ypt1_found ? 1 : 0,
                Ypt1_found ? Ypt1_rpts1s_id : -1,
                far_Lpt0_found ? 1 : 0,
                far_Lpt0_found ? far_Lpt0_rpts0s_id : -1,
                far_Lpt1_found ? 1 : 0,
                far_Lpt1_found ? far_Lpt1_rpts1s_id : -1,
                far_rpts0s_num,
                far_rpts1s_num,
                is_straight0 ? 1 : 0,
                is_straight1 ? 1 : 0,
                is_straight_far_0 ? 1 : 0,
                is_straight_far_1 ? 1 : 0,
                conf1_max * 180.0f / 3.14159265358979323846f,
                conf2_max * 180.0f / 3.14159265358979323846f,
                conf3_max * 180.0f / 3.14159265358979323846f,
                conf4_max * 180.0f / 3.14159265358979323846f,
                total_distence,
                (long long)atg_reference_circle_begin_dist(),
                (long long)atg_reference_circle_begin_last_dist(),
                Ramp_total_distence,
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
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty);
}
