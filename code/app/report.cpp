#include "app/report.hpp"

#include "tracking/boundary.hpp"
#include "tracking/imgproc.hpp"
#include "tracking/mainline.hpp"
#include "tracking/perspective.hpp"

#include <cstdint>
#include <cstdio>
#include <fstream>

namespace
{
// 计算两点之间的欧式距离，用于报告里的 IPM seed 几何检查。
double point_distance(point_t a, point_t b)
{
    return std::hypot((double)a.x - b.x, (double)a.y - b.y);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      校验 IPM 种子映射几何是否合法（种子有效、矩阵已加载、映射成功、左右间距合理）
//  @return     int          IPM_GEOMETRY_xxx 枚举之一
//  @note       这里只做诊断输出，不影响 tracking_process_frame() 的真实中线生成。
//-------------------------------------------------------------------------------------------------------------------
int inspect_ipm_seed_geometry(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return IPM_GEOMETRY_NO_SEED;
    }
    if(!seed_pair_accepted(&rt->seeds, rt->seed_state))
    {
        return IPM_GEOMETRY_NO_SEED;
    }
    if(!rt->has_matrix)
    {
        return IPM_GEOMETRY_NO_MATRIX;
    }

    point_t p0 = {-1, -1};
    point_t p1 = {-1, -1};
    int ok0 = 0;
    int ok1 = 0;
    perspective_point(rt->matrix, &rt->seeds.left, &p0, &ok0);
    perspective_point(rt->matrix, &rt->seeds.right, &p1, &ok1);
    if(!ok0 || !ok1)
    {
        return IPM_GEOMETRY_MAP_FAILED;
    }

    const double w = point_distance(p0, p1);
    if(w < ROAD_HALF_WIDTH)
    {
        return IPM_GEOMETRY_WIDTH_TOO_SMALL;
    }
    if(w > RAW_W - 2)
    {
        return IPM_GEOMETRY_WIDTH_TOO_LARGE;
    }
    return IPM_GEOMETRY_OK;
}

// 取中线起点和预瞄附近点，供单行日志和报告输出。
void mid_points_for_report(const midline_t &mid, point_t *m0, point_t *ml)
{
    *m0 = {-1, -1};
    *ml = {-1, -1};
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
        const int err = std::abs(mid.dist[i] - LOOKAHEAD_DIST);
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }
    *ml = mid.pts[best];
}

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
    const int ipm_reason = inspect_ipm_seed_geometry(rt);

    std::printf("Seed: left=(%d,%d) right=(%d,%d) row=%d width=%d\n",
                sd.left.x,
                sd.left.y,
                sd.right.x,
                sd.right.y,
                sd.row,
                sd.width);
    std::printf("SeedSt: state=%d mid=%d track=%d\n",
                rt->seed_state,
                rt->mid_position,
                tr.track_type);
    std::printf("CtlX: x=%d\n", rt->control_center_x);
    std::printf("IPM: loaded=%d frame=%d reason=%d\n",
                rt->has_matrix,
                use_matrix,
                ipm_reason);
    std::printf("Trace: left=%d right=%d\n", tr0.step, tr1.step);
    std::printf("CornerL: left=%d/%d@%d/%.1f pair=%d w=%.1f/%.1f "
                "base=(%d,%d) open=(%d,%d) "
                "right=%d/%d@%d/%.1f pair=%d w=%.1f/%.1f "
                "base=(%d,%d) open=(%d,%d)\n",
                tr.left.l_found,
                tr.left.l_ok,
                tr.left.l_now_index,
                tr.left.l_angle_deg,
                tr.left.l_pair_state,
                tr.left.l_pair_width0,
                tr.left.l_pair_width1,
                tr.left.l_pair_base_pt.x,
                tr.left.l_pair_base_pt.y,
                tr.left.l_pair_open_pt.x,
                tr.left.l_pair_open_pt.y,
                tr.right.l_found,
                tr.right.l_ok,
                tr.right.l_now_index,
                tr.right.l_angle_deg,
                tr.right.l_pair_state,
                tr.right.l_pair_width0,
                tr.right.l_pair_width1,
                tr.right.l_pair_base_pt.x,
                tr.right.l_pair_base_pt.y,
                tr.right.l_pair_open_pt.x,
                tr.right.l_pair_open_pt.y);
    std::printf("Mid: step=%d center=%d guide=%.2f rej=%d\n",
                tr.mid.step,
                tr.center_x,
                tr.guide_error,
                tr.reject_reason);
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
    const auto &sd = rt->seeds;
    const auto &tr = rt->track;
    const auto &tr0 = rt->left_trace;
    const auto &tr1 = rt->right_trace;
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    mid_points_for_report(tr.mid, &m0, &ml);

    // 字段缩写：cf=左/右远线found，cn=左/右远线点数，cl=左/右远 L 索引；
    //   l=左 found/ok/now_index @ 右 found/ok/now_index；lp/rp=左/右双 L 复核状态；
    //   lb/la=左边界 pair 基点/张开点，rb/ra=右边界同；m0=中线起点，ml=预瞄点（均控制坐标）；
    //   yaw=target_yaw(mrad/s)，duty=左/右占空。
    std::printf("frame=%u ring=%d/%d cross=%d cf=%d/%d cn=%d/%d cl=%d/%d "
                "zebra=%d line=%d rej=%d track=%d mid=%d "
                "seed=(%d,%d)-(%d,%d) trace=%d/%d "
                "l=%d/%d@%d/%d/%d@%d lp=%d rp=%d "
                "lb=(%d,%d) la=(%d,%d) rb=(%d,%d) ra=(%d,%d) "
                "center=%d m0=(%d,%d) ml=(%d,%d) guide=%.2f "
                "loop=%d stop=%d yaw=%d duty=%d/%d\n",
                frame_id,
                rt->ring.kind,
                rt->ring.state,
                rt->cross.state,
                rt->cross.left_far_found,
                rt->cross.right_far_found,
                rt->cross.left_num,
                rt->cross.right_num,
                rt->cross.left_l,
                rt->cross.right_l,
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
                tr.left.l_found,
                tr.left.l_ok,
                tr.left.l_now_index,
                tr.right.l_found,
                tr.right.l_ok,
                tr.right.l_now_index,
                tr.left.l_pair_state,
                tr.right.l_pair_state,
                tr.left.l_pair_base_pt.x,
                tr.left.l_pair_base_pt.y,
                tr.left.l_pair_open_pt.x,
                tr.left.l_pair_open_pt.y,
                tr.right.l_pair_base_pt.x,
                tr.right.l_pair_base_pt.y,
                tr.right.l_pair_open_pt.x,
                tr.right.l_pair_open_pt.y,
                tr.center_x,
                m0.x,
                m0.y,
                ml.x,
                ml.y,
                tr.guide_error,
                rt->control.input_valid,
                rt->control.stop_request,
                rt->control.target_yaw_rate_mrad_s,
                rt->control.left_duty,
                rt->control.right_duty);
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

    const int ipm_reason = inspect_ipm_seed_geometry(rt);
    out << "matrix_loaded=" << rt->has_matrix << "\n";
    out << "ipm_geometry_reject_reason=" << ipm_reason << "\n";

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
    out << "zebra_detected=" << rt->zebra.detected << "\n";
    out << "zebra_stop_line=" << rt->zebra.stop_line << "\n";

    out << "mid_position=" << rt->mid_position << "\n";
    out << "control_center_x=" << rt->control_center_x << "\n";
    out << "left_seed=" << rt->seeds.left.x << "," << rt->seeds.left.y << "\n";
    out << "right_seed=" << rt->seeds.right.x << "," << rt->seeds.right.y << "\n";
    out << "seed_row=" << rt->seeds.row << "\n";
    out << "seed_width=" << rt->seeds.width << "\n";

    out << "left_trace_step=" << rt->left_trace.step << "\n";
    out << "right_trace_step=" << rt->right_trace.step << "\n";
    out << "left_l_found=" << rt->track.left.l_found << "\n";
    out << "left_l_ok=" << rt->track.left.l_ok << "\n";
    out << "left_l_now_index=" << rt->track.left.l_now_index << "\n";
    out << "left_l_original_index=" << rt->track.left.l_original_index << "\n";
    out << "left_l_angle_deg=" << rt->track.left.l_angle_deg << "\n";
    out << "left_l_pair_state=" << rt->track.left.l_pair_state << "\n";
    out << "left_l_pair_width0=" << rt->track.left.l_pair_width0 << "\n";
    out << "left_l_pair_width1=" << rt->track.left.l_pair_width1 << "\n";
    out << "left_l_pair_base=" << rt->track.left.l_pair_base_pt.x << "," << rt->track.left.l_pair_base_pt.y << "\n";
    out << "left_l_pair_open=" << rt->track.left.l_pair_open_pt.x << "," << rt->track.left.l_pair_open_pt.y << "\n";
    out << "right_l_found=" << rt->track.right.l_found << "\n";
    out << "right_l_ok=" << rt->track.right.l_ok << "\n";
    out << "right_l_now_index=" << rt->track.right.l_now_index << "\n";
    out << "right_l_original_index=" << rt->track.right.l_original_index << "\n";
    out << "right_l_angle_deg=" << rt->track.right.l_angle_deg << "\n";
    out << "right_l_pair_state=" << rt->track.right.l_pair_state << "\n";
    out << "right_l_pair_width0=" << rt->track.right.l_pair_width0 << "\n";
    out << "right_l_pair_width1=" << rt->track.right.l_pair_width1 << "\n";
    out << "right_l_pair_base=" << rt->track.right.l_pair_base_pt.x << "," << rt->track.right.l_pair_base_pt.y << "\n";
    out << "right_l_pair_open=" << rt->track.right.l_pair_open_pt.x << "," << rt->track.right.l_pair_open_pt.y << "\n";
    out << "mid_step=" << rt->track.mid.step << "\n";
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    mid_points_for_report(rt->track.mid, &m0, &ml);
    out << "mid0=" << m0.x << "," << m0.y << "\n";
    out << "mid_look=" << ml.x << "," << ml.y << "\n";
    out << "center_x=" << rt->track.center_x << "\n";
    out << "guide_error=" << rt->track.guide_error << "\n";
    return 1;
}
