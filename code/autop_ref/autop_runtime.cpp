#include "autop_runtime.hpp"

extern "C" {
#include "camera_param.h"
#include "circle.h"
#include "cross.h"
#include "imgproc.h"
#include "main.h"
}

#include "clip.hpp"
#include "tracking/ipm_table_generated.hpp"
#include "tracking/perspective.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{

constexpr int k_scaled_far_left_x = RAW_W * 86 / 376;
constexpr int k_scaled_far_right_x = RAW_W * 280 / 376;
constexpr int k_mid_resample_dist = 3;
constexpr int k_track_approx_num = 5;
constexpr int k_lookahead_min = 15;
constexpr int k_lookahead_max = 80;
constexpr float k_pair_width_tolerance = 15.0F;
constexpr float k_pair_open_width = 70.0F;
constexpr double k_error_forward_bias = ROAD_HALF_WIDTH * 8.0 / 9.0;

int angle_window_points()
{
    return std::max(1, static_cast<int>(std::round(angle_dist / sample_dist)));
}

float road_width_pixels()
{
    return static_cast<float>(ROAD_HALF_WIDTH * 2);
}

} // namespace

extern "C" {

extern int far_x1;
extern int far_x2;
extern int not_have_line;

image_t img_raw = DEF_IMAGE(nullptr, RAW_W, RAW_H);
uint8_t img_thres_data[RAW_H][RAW_W];
image_t img_thres = DEF_IMAGE(reinterpret_cast<uint8_t *>(img_thres_data), RAW_W, RAW_H);
uint8_t img_line_data[RAW_H][RAW_W];
image_t img_line = DEF_IMAGE(reinterpret_cast<uint8_t *>(img_line_data), RAW_W, RAW_H);

bool line_show_sample = true;
bool line_show_blur = false;
bool track_left = false;
float angle = 0.0F;

float thres = 140.0F;
float block_size = 7.0F;
float clip_value = 2.0F;
float begin_x = 14.0F;
float begin_y = 84.0F;
float line_blur_kernel = 7.0F;
float pixel_per_meter = static_cast<float>(ROAD_HALF_WIDTH * 2) / ROAD_WIDTH;
float sample_dist = 0.03F;
float point_sample_dist = 3.0F;
float angle_dist = 0.20F;
float aim_distance = 0.58F;
float far_rate = 0.8F;
bool adc_cross = false;

float K[3][3] = {};
float D[4] = {};
float H[3][3] = {};
float H_inv[3][3] = {};
float mapx[RAW_H][RAW_W];
float mapy[RAW_H][RAW_W];
int invx[IPM_H][IPM_W];
int invy[IPM_H][IPM_W];

int ipts0[POINTS_MAX_LEN][2];
int ipts1[POINTS_MAX_LEN][2];
int ipts0_num, ipts1_num;
float rpts0[POINTS_MAX_LEN][2];
float rpts1[POINTS_MAX_LEN][2];
int rpts0_num, rpts1_num;
float rpts0b[POINTS_MAX_LEN][2];
float rpts1b[POINTS_MAX_LEN][2];
int rpts0b_num, rpts1b_num;
float rpts0s[POINTS_MAX_LEN][2];
float rpts1s[POINTS_MAX_LEN][2];
int rpts0s_num, rpts1s_num;
float rpts0a[POINTS_MAX_LEN];
float rpts1a[POINTS_MAX_LEN];
int rpts0a_num, rpts1a_num;
float rpts0an[POINTS_MAX_LEN];
float rpts1an[POINTS_MAX_LEN];
int rpts0an_num, rpts1an_num;
float rptsc0[POINTS_MAX_LEN][2];
float rptsc1[POINTS_MAX_LEN][2];
int rptsc0_num, rptsc1_num;
float (*rpts)[2] = nullptr;
int rpts_num;
float rptsn[POINTS_MAX_LEN][2];
int rptsn_num;

int Ypt0_rpts0s_id, Ypt1_rpts1s_id;
bool Ypt0_found, Ypt1_found;
int Lpt0_rpts0s_id, Lpt1_rpts1s_id;
bool Lpt0_found, Lpt1_found;
bool is_straight0, is_straight1;
enum track_type_e track_type = TRACK_RIGHT;

int64_t g_autop_encoder_total = 0;

int64_t get_total_encoder(void)
{
    return g_autop_encoder_total;
}

void flash_param_init(void) {}
bool flash_param_check(void) { return false; }
void flash_param_load(void) {}
void flash_param_write(void) {}

bool map_inv(float pt0[2], int pt1[2])
{
    if(pt0 == nullptr || pt1 == nullptr)
    {
        return false;
    }
    return perspective_lookup_ipm_to_raw(static_cast<int>(std::lround(pt0[0])),
                                         static_cast<int>(std::lround(pt0[1])),
                                         &pt1[0],
                                         &pt1[1]) != 0;
}

void process_image(void)
{
    int x1 = img_raw.width / 2 - static_cast<int>(begin_x);
    int y1 = static_cast<int>(begin_y);
    ipts0_num = sizeof(ipts0) / sizeof(ipts0[0]);
    for(; x1 > 0; --x1)
    {
        if(AT_IMAGE(&img_raw, x1 - 1, y1) < thres)
        {
            break;
        }
    }
    if(AT_IMAGE(&img_raw, x1, y1) >= thres)
    {
        findline_lefthand_adaptive(&img_raw,
                                   static_cast<int>(block_size),
                                   static_cast<int>(clip_value),
                                   x1,
                                   y1,
                                   ipts0,
                                   &ipts0_num);
    }
    else
    {
        ipts0_num = 0;
    }

    int x2 = img_raw.width / 2 + static_cast<int>(begin_x);
    int y2 = static_cast<int>(begin_y);
    ipts1_num = sizeof(ipts1) / sizeof(ipts1[0]);
    for(; x2 < static_cast<int>(img_raw.width) - 1; ++x2)
    {
        if(AT_IMAGE(&img_raw, x2 + 1, y2) < thres)
        {
            break;
        }
    }
    if(AT_IMAGE(&img_raw, x2, y2) >= thres)
    {
        findline_righthand_adaptive(&img_raw,
                                    static_cast<int>(block_size),
                                    static_cast<int>(clip_value),
                                    x2,
                                    y2,
                                    ipts1,
                                    &ipts1_num);
    }
    else
    {
        ipts1_num = 0;
    }

    for(int i = 0; i < ipts0_num; ++i)
    {
        rpts0[i][0] = mapx[ipts0[i][1]][ipts0[i][0]];
        rpts0[i][1] = mapy[ipts0[i][1]][ipts0[i][0]];
    }
    rpts0_num = ipts0_num;
    for(int i = 0; i < ipts1_num; ++i)
    {
        rpts1[i][0] = mapx[ipts1[i][1]][ipts1[i][0]];
        rpts1[i][1] = mapy[ipts1[i][1]][ipts1[i][0]];
    }
    rpts1_num = ipts1_num;

    blur_points(rpts0, rpts0_num, rpts0b, static_cast<int>(std::round(line_blur_kernel)));
    rpts0b_num = rpts0_num;
    blur_points(rpts1, rpts1_num, rpts1b, static_cast<int>(std::round(line_blur_kernel)));
    rpts1b_num = rpts1_num;

    rpts0s_num = sizeof(rpts0s) / sizeof(rpts0s[0]);
    resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, point_sample_dist);
    rpts1s_num = sizeof(rpts1s) / sizeof(rpts1s[0]);
    resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, point_sample_dist);

    const int angle_window = angle_window_points();
    local_angle_points(rpts0s, rpts0s_num, rpts0a, angle_window);
    rpts0a_num = rpts0s_num;
    local_angle_points(rpts1s, rpts1s_num, rpts1a, angle_window);
    rpts1a_num = rpts1s_num;

    nms_angle(rpts0a, rpts0a_num, rpts0an, angle_window * 2 + 1);
    rpts0an_num = rpts0a_num;
    nms_angle(rpts1a, rpts1a_num, rpts1an, angle_window * 2 + 1);
    rpts1an_num = rpts1a_num;

    track_leftline(rpts0s, rpts0s_num, rptsc0, k_track_approx_num, ROAD_HALF_WIDTH);
    rptsc0_num = rpts0s_num;
    track_rightline(rpts1s, rpts1s_num, rptsc1, k_track_approx_num, ROAD_HALF_WIDTH);
    rptsc1_num = rpts1s_num;
}

void find_corners(void)
{
    Ypt0_found = false;
    Ypt1_found = false;
    Lpt0_found = false;
    Lpt1_found = false;
    is_straight0 = rpts0s_num > 1.0F / sample_dist;
    is_straight1 = rpts1s_num > 1.0F / sample_dist;

    const int angle_window = angle_window_points();
    for(int i = 0; i < rpts0s_num; ++i)
    {
        if(rpts0an[i] == 0)
        {
            continue;
        }
        const int im1 = clip(i - angle_window, 0, rpts0s_num - 1);
        const int ip1 = clip(i + angle_window, 0, rpts0s_num - 1);
        const float conf = std::fabs(rpts0a[i]) - (std::fabs(rpts0a[im1]) + std::fabs(rpts0a[ip1])) / 2.0F;

        if(!Ypt0_found && 30.0F / 180.0F * PI < conf && conf < 65.0F / 180.0F * PI &&
           i < 0.8F / sample_dist)
        {
            Ypt0_rpts0s_id = i;
            Ypt0_found = true;
        }
        if(!Lpt0_found && 70.0F / 180.0F * PI < conf && conf < 140.0F / 180.0F * PI &&
           i < 0.8F / sample_dist)
        {
            Lpt0_rpts0s_id = i;
            Lpt0_found = true;
        }
        if(conf > 5.0F / 180.0F * PI && i < 1.0F / sample_dist)
        {
            is_straight0 = false;
        }
        if(Ypt0_found && Lpt0_found && !is_straight0)
        {
            break;
        }
    }

    for(int i = 0; i < rpts1s_num; ++i)
    {
        if(rpts1an[i] == 0)
        {
            continue;
        }
        const int im1 = clip(i - angle_window, 0, rpts1s_num - 1);
        const int ip1 = clip(i + angle_window, 0, rpts1s_num - 1);
        const float conf = std::fabs(rpts1a[i]) - (std::fabs(rpts1a[im1]) + std::fabs(rpts1a[ip1])) / 2.0F;

        if(!Ypt1_found && 30.0F / 180.0F * PI < conf && conf < 65.0F / 180.0F * PI &&
           i < 0.8F / sample_dist)
        {
            Ypt1_rpts1s_id = i;
            Ypt1_found = true;
        }
        if(!Lpt1_found && 70.0F / 180.0F * PI < conf && conf < 140.0F / 180.0F * PI &&
           i < 0.8F / sample_dist)
        {
            Lpt1_rpts1s_id = i;
            Lpt1_found = true;
        }
        if(conf > 5.0F / 180.0F * PI && i < 1.0F / sample_dist)
        {
            is_straight1 = false;
        }
        if(Ypt1_found && Lpt1_found && !is_straight1)
        {
            break;
        }
    }

    if(Ypt0_found && Ypt1_found)
    {
        const float dx = rpts0s[Ypt0_rpts0s_id][0] - rpts1s[Ypt1_rpts1s_id][0];
        const float dy = rpts0s[Ypt0_rpts0s_id][1] - rpts1s[Ypt1_rpts1s_id][1];
        const float dn = std::sqrt(dx * dx + dy * dy);
        if(std::fabs(dn - road_width_pixels()) < k_pair_width_tolerance)
        {
            const int id0 = clip(Ypt0_rpts0s_id + 50, 0, rpts0s_num - 1);
            const int id1 = clip(Ypt1_rpts1s_id + 50, 0, rpts1s_num - 1);
            const float dwx = rpts0s[id0][0] - rpts1s[id1][0];
            const float dwy = rpts0s[id0][1] - rpts1s[id1][1];
            const float dwn = std::sqrt(dwx * dwx + dwy * dwy);
            if(!(dwn > k_pair_open_width &&
                 rpts0s[id0][0] < rpts0s[Ypt0_rpts0s_id][0] &&
                 rpts1s[id1][0] > rpts1s[Ypt1_rpts1s_id][0]))
            {
                Ypt0_found = false;
                Ypt1_found = false;
            }
        }
        else
        {
            Ypt0_found = false;
            Ypt1_found = false;
        }
    }

    if(Lpt0_found && Lpt1_found)
    {
        const float dx = rpts0s[Lpt0_rpts0s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
        const float dy = rpts0s[Lpt0_rpts0s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
        const float dn = std::sqrt(dx * dx + dy * dy);
        if(std::fabs(dn - road_width_pixels()) < k_pair_width_tolerance)
        {
            const int id0 = clip(Lpt0_rpts0s_id + 50, 0, rpts0s_num - 1);
            const int id1 = clip(Lpt1_rpts1s_id + 50, 0, rpts1s_num - 1);
            const float dwx = rpts0s[id0][0] - rpts1s[id1][0];
            const float dwy = rpts0s[id0][1] - rpts1s[id1][1];
            const float dwn = std::sqrt(dwx * dwx + dwy * dwy);
            if(!(dwn > k_pair_open_width &&
                 rpts0s[id0][0] < rpts0s[Lpt0_rpts0s_id][0] &&
                 rpts1s[id1][0] > rpts1s[Lpt1_rpts1s_id][0]))
            {
                Lpt0_found = false;
                Lpt1_found = false;
            }
        }
        else
        {
            Lpt0_found = false;
            Lpt1_found = false;
        }
    }
}

} // extern "C"

namespace
{

void init_camera_tables_once()
{
    static int initialized = 0;
    if(initialized)
    {
        return;
    }
    initialized = 1;

    for(int y = 0; y < RAW_H; ++y)
    {
        for(int x = 0; x < RAW_W; ++x)
        {
            mapx[y][x] = g_raw_to_ipm_x[y][x];
            mapy[y][x] = g_raw_to_ipm_y[y][x];
        }
    }
    for(int y = 0; y < IPM_H; ++y)
    {
        for(int x = 0; x < IPM_W; ++x)
        {
            invx[y][x] = g_ipm_to_raw_x[y][x];
            invy[y][x] = g_ipm_to_raw_y[y][x];
        }
    }
}

void reset_frame_outputs(runtime_t *rt)
{
    rt->track = {};
    rt->seeds = {};
    rt->seed_state = 0;
    rt->left_trace = {};
    rt->right_trace = {};
    rt->zebra = {};
    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.track_type = TRACK_TYPE_NONE;
    rt->track.center_x = -1;
    rt->track.control_ref = {-1, -1};
    rt->track.candidate_crop_side = 0;
    rt->track.candidate_crop_index = -1;
}

void copy_raw_points(const int src[][2], int num, boundary_t *out)
{
    if(out == nullptr)
    {
        return;
    }
    const int n = std::clamp(num, 0, static_cast<int>(POINT_MAX));
    out->original_step = n;
    out->now_step = n;
    out->work_step = n;
    for(int i = 0; i < n; ++i)
    {
        out->original_pts[i] = {src[i][0], src[i][1]};
        out->now_pts[i] = {src[i][0], src[i][1]};
        out->work_pts[i][0] = src[i][0];
        out->work_pts[i][1] = src[i][1];
    }
}

void copy_l_diag(boundary_t *left, boundary_t *right)
{
    if(left != nullptr)
    {
        left->l_found = Lpt0_found ? 1 : 0;
        left->l_ok = Lpt0_found ? 1 : 0;
        left->l_now_index = Lpt0_found ? Lpt0_rpts0s_id : -1;
        left->l_original_index = left->l_now_index;
        left->l_pair_ok = (Lpt0_found && Lpt1_found) ? 1 : 0;
    }
    if(right != nullptr)
    {
        right->l_found = Lpt1_found ? 1 : 0;
        right->l_ok = Lpt1_found ? 1 : 0;
        right->l_now_index = Lpt1_found ? Lpt1_rpts1s_id : -1;
        right->l_original_index = right->l_now_index;
        right->l_pair_ok = (Lpt0_found && Lpt1_found) ? 1 : 0;
    }
}

point_t control_ref_point(const runtime_t *rt)
{
    point_t ref = {rt != nullptr ? rt->control_center_x : CONTROL_CENTER_X, START_HIGH};
    const int raw_x = RAW_W / 2;
    const int raw_y = static_cast<int>(RAW_H * 0.78F);
    double ix = 0.0;
    double iy = 0.0;
    if(rt != nullptr && rt->has_matrix &&
       perspective_lookup_raw_to_ipm(raw_x, raw_y, &ix, &iy))
    {
        ref.x = clip_i(round_i(ix), 0, IPM_W - 1);
        ref.y = clip_i(round_i(iy), 0, IPM_H - 1);
    }
    return ref;
}

void copy_midline(runtime_t *rt)
{
    midline_t &mid = rt->track.mid;
    mid = {};
    const int n = std::clamp(rptsn_num, 0, static_cast<int>(POINT_MAX));
    int last_x = 0;
    int last_y = 0;
    int total = 0;
    for(int i = 0; i < n; ++i)
    {
        const int x = round_i(rptsn[i][0]);
        const int y = round_i(rptsn[i][1]);
        mid.pts[i] = {x, y};
        if(i > 0)
        {
            total += round_i(std::hypot(static_cast<double>(x - last_x),
                                        static_cast<double>(y - last_y)));
        }
        mid.dist[i] = total;
        last_x = x;
        last_y = y;
    }
    mid.step = n;
}

double guide_error_from_mid(const midline_t &mid, point_t ref)
{
    if(mid.step <= 0)
    {
        return 0.0;
    }

    int best = 0;
    int best_err = 1 << 30;
    for(int i = 0; i < mid.step; ++i)
    {
        const int look = clip_i(LOOKAHEAD_DIST, k_lookahead_min, k_lookahead_max);
        const int err = std::abs(mid.dist[i] - look);
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }

    const double dx = static_cast<double>(mid.pts[best].x - ref.x);
    const double dy = static_cast<double>(ref.y - mid.pts[best].y) + k_error_forward_bias;
    return -std::atan2(dx, dy) * 180.0 / 3.14159265358979323846;
}

int nearest_begin_id(float pts[][2], int num, point_t ref)
{
    int begin_id = -1;
    float min_dist = 1e10F;
    for(int i = 0; i < num; ++i)
    {
        const float dx = pts[i][0] - static_cast<float>(ref.x);
        const float dy = pts[i][1] - static_cast<float>(ref.y);
        const float dist = std::sqrt(dx * dx + dy * dy);
        if(dist < min_dist)
        {
            min_dist = dist;
            begin_id = i;
        }
    }
    return begin_id;
}

int build_selected_midline(runtime_t *rt, point_t ref)
{
    if(cross_type != CROSS_IN)
    {
        if(track_type == TRACK_LEFT)
        {
            rpts = rptsc0;
            rpts_num = rptsc0_num;
        }
        else
        {
            rpts = rptsc1;
            rpts_num = rptsc1_num;
        }
    }
    else
    {
        if(track_type == TRACK_LEFT && far_Lpt0_found)
        {
            rpts = rptsc0;
            track_leftline(far_rpts0s + far_Lpt0_rpts0s_id,
                           far_rpts0s_num - far_Lpt0_rpts0s_id,
                           rpts,
                           k_track_approx_num,
                           ROAD_HALF_WIDTH);
            rpts_num = far_rpts0s_num - far_Lpt0_rpts0s_id;
        }
        else if(track_type == TRACK_RIGHT && far_Lpt1_found)
        {
            rpts = rptsc1;
            track_rightline(far_rpts1s + far_Lpt1_rpts1s_id,
                            far_rpts1s_num - far_Lpt1_rpts1s_id,
                            rpts,
                            k_track_approx_num,
                            ROAD_HALF_WIDTH);
            rpts_num = far_rpts1s_num - far_Lpt1_rpts1s_id;
        }
        else
        {
            rpts_num = 0;
        }
    }

    if(rpts == nullptr || rpts_num <= 0)
    {
        return 0;
    }

    int begin_id = nearest_begin_id(rpts, rpts_num, ref);
    if(cross_type == CROSS_IN)
    {
        begin_id = 0;
    }
    if(begin_id < 0 || rpts_num - begin_id < 3)
    {
        return 0;
    }

    rpts[begin_id][0] = static_cast<float>(ref.x);
    rpts[begin_id][1] = static_cast<float>(ref.y);
    rptsn_num = POINTS_MAX_LEN;
    resample_points(rpts + begin_id,
                    rpts_num - begin_id,
                    rptsn,
                    &rptsn_num,
                    k_mid_resample_dist);
    copy_midline(rt);
    return rt->track.mid.step >= 3;
}

void map_element_state(runtime_t *rt)
{
    rt->cross.state = CROSS_STATE_NONE;
    if(cross_type == CROSS_BEGIN)
    {
        rt->cross.state = CROSS_STATE_BEGIN;
    }
    else if(cross_type == CROSS_IN)
    {
        rt->cross.state = CROSS_STATE_IN;
    }
    rt->cross.not_have_line = not_have_line;
    rt->cross.track_type = track_type == TRACK_LEFT ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;
    rt->cross.left_far_found = far_Lpt0_found ? 1 : 0;
    rt->cross.right_far_found = far_Lpt1_found ? 1 : 0;
    rt->cross.left_l = far_Lpt0_found ? far_Lpt0_rpts0s_id : -1;
    rt->cross.right_l = far_Lpt1_found ? far_Lpt1_rpts1s_id : -1;
    rt->cross.left_num = far_rpts0s_num;
    rt->cross.right_num = far_rpts1s_num;
    rt->cross.left_far_l_source = far_Lpt0_found ? CROSS_FAR_L_NEW : CROSS_FAR_L_NONE;
    rt->cross.right_far_l_source = far_Lpt1_found ? CROSS_FAR_L_NEW : CROSS_FAR_L_NONE;
    for(int i = 0; i < std::min(far_rpts0s_num, static_cast<int>(POINT_MAX)); ++i)
    {
        rt->cross.left_pts[i][0] = far_rpts0s[i][0];
        rt->cross.left_pts[i][1] = far_rpts0s[i][1];
    }
    for(int i = 0; i < std::min(far_rpts1s_num, static_cast<int>(POINT_MAX)); ++i)
    {
        rt->cross.right_pts[i][0] = far_rpts1s[i][0];
        rt->cross.right_pts[i][1] = far_rpts1s[i][1];
    }

    rt->ring.kind = RING_KIND_NONE;
    rt->ring.state = RING_STATE_BEGIN;
    if(circle_type >= CIRCLE_LEFT_BEGIN && circle_type <= CIRCLE_LEFT_END &&
       (circle_type & 1) == 1)
    {
        rt->ring.kind = RING_KIND_LEFT;
    }
    else if(circle_type >= CIRCLE_RIGHT_BEGIN && circle_type <= CIRCLE_RIGHT_END &&
             (circle_type & 1) == 0)
    {
        rt->ring.kind = RING_KIND_RIGHT;
    }

    switch(circle_type)
    {
    case CIRCLE_LEFT_IN:
    case CIRCLE_RIGHT_IN:
        rt->ring.state = RING_STATE_IN;
        break;
    case CIRCLE_LEFT_RUNNING:
    case CIRCLE_RIGHT_RUNNING:
        rt->ring.state = RING_STATE_RUN;
        break;
    case CIRCLE_LEFT_OUT:
    case CIRCLE_RIGHT_OUT:
        rt->ring.state = RING_STATE_OUT;
        break;
    case CIRCLE_LEFT_END:
    case CIRCLE_RIGHT_END:
        rt->ring.state = RING_STATE_END;
        break;
    default:
        rt->ring.state = RING_STATE_BEGIN;
        break;
    }
}

void update_seed_diag(runtime_t *rt)
{
    rt->seed_state = 0;
    rt->seeds.row = static_cast<int>(begin_y);
    if(ipts0_num > 0)
    {
        rt->seed_state |= 1;
        rt->seeds.left = {ipts0[0][0], ipts0[0][1]};
        rt->track.seed_left_find = rt->seeds.left;
    }
    else
    {
        rt->seeds.left = {-1, -1};
        rt->track.seed_left_find = {-1, -1};
    }
    if(ipts1_num > 0)
    {
        rt->seed_state |= 2;
        rt->seeds.right = {ipts1[0][0], ipts1[0][1]};
        rt->track.seed_right_find = rt->seeds.right;
    }
    else
    {
        rt->seeds.right = {-1, -1};
        rt->track.seed_right_find = {-1, -1};
    }
    rt->track.seed_state_find = rt->seed_state;
}

} // namespace

void autop_ref_set_encoder_total(int64_t encoder_total)
{
    g_autop_encoder_total = encoder_total;
}

void tracking_reset(runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }
    *rt = {};
    rt->gray_valid = 0;
    rt->control_center_x = CONTROL_CENTER_X;
    rt->mid_position = MID_X;
    rt->width_base = ROAD_HALF_WIDTH * 2;
    rt->has_matrix = 1;
    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.track_type = TRACK_TYPE_NONE;
    rt->track.center_x = -1;

    cross_type = CROSS_NONE;
    circle_type = CIRCLE_NONE;
    track_type = TRACK_RIGHT;
    not_have_line = 0;
    far_Lpt0_found = false;
    far_Lpt1_found = false;
    far_Lpt0_rpts0s_id = -1;
    far_Lpt1_rpts1s_id = -1;
    far_x1 = k_scaled_far_left_x;
    far_x2 = k_scaled_far_right_x;
}

int tracking_process_frame(runtime_t *rt)
{
    if(rt == nullptr || !rt->gray_valid)
    {
        return 0;
    }

    init_camera_tables_once();
    reset_frame_outputs(rt);
    autop_ref_set_encoder_total(rt->encoder_total);
    img_raw.data = &rt->gray[0][0];
    far_x1 = k_scaled_far_left_x;
    far_x2 = k_scaled_far_right_x;
    aim_distance = 0.58F;

    process_image();
    find_corners();

    if(rpts0s_num < rpts1s_num / 2 && rpts0s_num < 60)
    {
        track_type = TRACK_RIGHT;
    }
    else if(rpts1s_num < rpts0s_num / 2 && rpts1s_num < 60)
    {
        track_type = TRACK_LEFT;
    }
    else if(rpts0s_num < 20 && rpts1s_num > rpts0s_num)
    {
        track_type = TRACK_RIGHT;
    }
    else if(rpts1s_num < 20 && rpts0s_num > rpts1s_num)
    {
        track_type = TRACK_LEFT;
    }

    check_cross();
    if(cross_type == CROSS_NONE)
    {
        check_circle();
    }
    if(cross_type != CROSS_NONE)
    {
        circle_type = CIRCLE_NONE;
    }
    if(cross_type != CROSS_NONE)
    {
        run_cross();
    }
    if(circle_type != CIRCLE_NONE)
    {
        run_circle();
    }

    copy_raw_points(ipts0, ipts0_num, &rt->track.left);
    copy_raw_points(ipts1, ipts1_num, &rt->track.right);
    copy_l_diag(&rt->track.left, &rt->track.right);
    update_seed_diag(rt);
    map_element_state(rt);

    const point_t ref = control_ref_point(rt);
    rt->track.control_ref = ref;
    rt->track.action_cross_state0 = rt->cross.state;
    rt->track.action_ring_kind0 = rt->ring.kind;
    rt->track.action_ring_state0 = rt->ring.state;
    rt->track.action_base_ready = 1;
    rt->track.mode_cross_far = cross_type == CROSS_IN ? 1 : 0;
    rt->track.mode_cross_near = cross_type == CROSS_BEGIN ? 1 : 0;
    rt->track.mode_ring_active = circle_type != CIRCLE_NONE ? 1 : 0;
    rt->track.mode_work_track_type = track_type == TRACK_LEFT ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;

    if(!build_selected_midline(rt, ref))
    {
        rt->track.reject_reason = TRACK_REJECT_NO_MIDLINE;
        rt->track.track_type = TRACK_TYPE_NONE;
        rt->track.selected_mid_ok = 0;
        return 0;
    }

    rt->track.reject_reason = TRACK_REJECT_NONE;
    rt->track.track_type = track_type == TRACK_LEFT ? TRACK_TYPE_LEFT : TRACK_TYPE_RIGHT;
    rt->track.center_x = rt->track.mid.pts[0].x;
    rt->track.guide_error = guide_error_from_mid(rt->track.mid, ref);
    rt->track.selected_mid_ok = 1;
    return 1;
}

int autop_ref_track_line_found(const runtime_t *rt)
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
    return rt->track.mid.step >= 3;
}

int track_line_found(const runtime_t *rt)
{
    return autop_ref_track_line_found(rt);
}
