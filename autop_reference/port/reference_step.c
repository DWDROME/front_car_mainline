#include "autop_reference_step.h"

#include <math.h>
#include <string.h>

#include "camera_param.h"
#include "circle.h"
#include "cross.h"
#include "flash_param.h"
#include "imgproc.h"
#include "main.h"
#include "encoder_port.h"

extern int64_t g_autop_reference_encoder_total;
extern int far_x1;
extern int far_x2;

static int g_ipm_ready = 0;

static void fill_reference_ipm_tables(void)
{
    if(g_ipm_ready)
    {
        return;
    }
    autop_reference_fill_ipm_tables(mapx, mapy);
    memset(invx, -1, sizeof(invx));
    memset(invy, -1, sizeof(invy));
    g_ipm_ready = 1;
}

static void reset_frame_outputs(void)
{
    rptsn_num = 0;
    rpts = NULL;
    rpts_num = 0;
}

void autop_reference_reset(void)
{
    circle_type = CIRCLE_NONE;
    cross_type = CROSS_NONE;
    track_type = TRACK_RIGHT;
    g_autop_reference_encoder_total = 0;
    reset_frame_outputs();
}

static void configure_reference_params(void)
{
    thres = 140.0f;
    block_size = 7.0f;
    clip_value = 2.0f;
    begin_x = 14.0f;
    begin_y = 84.0f;
    line_blur_kernel = 7.0f;
    pixel_per_meter = 26.0f * 2.0f / (float)ROAD_WIDTH;
    sample_dist = 0.03f;
    angle_dist = 0.2f;
    aim_distance = 0.58f;
    far_rate = 0.5f;
    adc_cross = false;
    far_x1 = MT9V03X_CSI_W * 86 / 376;
    far_x2 = MT9V03X_CSI_W * 280 / 376;
}

void autop_reference_process_image(void)
{
    int x1 = img_raw.width / 2 - begin_x, y1 = begin_y;
    ipts0_num = sizeof(ipts0) / sizeof(ipts0[0]);
    for(; x1 > 0; x1--)
    {
        if(AT_IMAGE(&img_raw, x1 - 1, y1) < thres)
        {
            break;
        }
    }
    if(AT_IMAGE(&img_raw, x1, y1) >= thres)
    {
        findline_lefthand_adaptive(&img_raw, (int)block_size, (int)clip_value, x1, y1, ipts0, &ipts0_num);
    }
    else
    {
        ipts0_num = 0;
    }

    int x2 = img_raw.width / 2 + begin_x, y2 = begin_y;
    ipts1_num = sizeof(ipts1) / sizeof(ipts1[0]);
    for(; x2 < (int)img_raw.width - 1; x2++)
    {
        if(AT_IMAGE(&img_raw, x2 + 1, y2) < thres)
        {
            break;
        }
    }
    if(AT_IMAGE(&img_raw, x2, y2) >= thres)
    {
        findline_righthand_adaptive(&img_raw, (int)block_size, (int)clip_value, x2, y2, ipts1, &ipts1_num);
    }
    else
    {
        ipts1_num = 0;
    }

    for(int i = 0; i < ipts0_num; i++)
    {
        rpts0[i][0] = mapx[ipts0[i][1]][ipts0[i][0]];
        rpts0[i][1] = mapy[ipts0[i][1]][ipts0[i][0]];
    }
    rpts0_num = ipts0_num;
    for(int i = 0; i < ipts1_num; i++)
    {
        rpts1[i][0] = mapx[ipts1[i][1]][ipts1[i][0]];
        rpts1[i][1] = mapy[ipts1[i][1]][ipts1[i][0]];
    }
    rpts1_num = ipts1_num;

    blur_points(rpts0, rpts0_num, rpts0b, (int)roundf(line_blur_kernel));
    rpts0b_num = rpts0_num;
    blur_points(rpts1, rpts1_num, rpts1b, (int)roundf(line_blur_kernel));
    rpts1b_num = rpts1_num;

    rpts0s_num = sizeof(rpts0s) / sizeof(rpts0s[0]);
    resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, sample_dist * pixel_per_meter);
    rpts1s_num = sizeof(rpts1s) / sizeof(rpts1s[0]);
    resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, sample_dist * pixel_per_meter);

    local_angle_points(rpts0s, rpts0s_num, rpts0a, (int)roundf(angle_dist / sample_dist));
    rpts0a_num = rpts0s_num;
    local_angle_points(rpts1s, rpts1s_num, rpts1a, (int)roundf(angle_dist / sample_dist));
    rpts1a_num = rpts1s_num;

    nms_angle(rpts0a, rpts0a_num, rpts0an, (int)roundf(angle_dist / sample_dist) * 2 + 1);
    rpts0an_num = rpts0a_num;
    nms_angle(rpts1a, rpts1a_num, rpts1an, (int)roundf(angle_dist / sample_dist) * 2 + 1);
    rpts1an_num = rpts1a_num;

    track_leftline(rpts0s, rpts0s_num, rptsc0, (int)roundf(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    rptsc0_num = rpts0s_num;
    track_rightline(rpts1s, rpts1s_num, rptsc1, (int)roundf(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
    rptsc1_num = rpts1s_num;
}

void autop_reference_find_corners(void)
{
    Ypt0_found = Ypt1_found = Lpt0_found = Lpt1_found = false;
    is_straight0 = rpts0s_num > 1.0f / sample_dist;
    is_straight1 = rpts1s_num > 1.0f / sample_dist;
    for(int i = 0; i < rpts0s_num; i++)
    {
        if(rpts0an[i] == 0)
        {
            continue;
        }
        int im1 = clip(i - (int)roundf(angle_dist / sample_dist), 0, rpts0s_num - 1);
        int ip1 = clip(i + (int)roundf(angle_dist / sample_dist), 0, rpts0s_num - 1);
        float conf = fabsf(rpts0a[i]) - (fabsf(rpts0a[im1]) + fabsf(rpts0a[ip1])) / 2.0f;
        if(!Ypt0_found && 30.0f / 180.0f * PI < conf && conf < 65.0f / 180.0f * PI && i < 0.8f / sample_dist)
        {
            Ypt0_rpts0s_id = i;
            Ypt0_found = true;
        }
        if(!Lpt0_found && 70.0f / 180.0f * PI < conf && conf < 140.0f / 180.0f * PI && i < 0.8f / sample_dist)
        {
            Lpt0_rpts0s_id = i;
            Lpt0_found = true;
        }
        if(conf > 5.0f / 180.0f * PI && i < 1.0f / sample_dist)
        {
            is_straight0 = false;
        }
        if(Ypt0_found && Lpt0_found && !is_straight0)
        {
            break;
        }
    }
    for(int i = 0; i < rpts1s_num; i++)
    {
        if(rpts1an[i] == 0)
        {
            continue;
        }
        int im1 = clip(i - (int)roundf(angle_dist / sample_dist), 0, rpts1s_num - 1);
        int ip1 = clip(i + (int)roundf(angle_dist / sample_dist), 0, rpts1s_num - 1);
        float conf = fabsf(rpts1a[i]) - (fabsf(rpts1a[im1]) + fabsf(rpts1a[ip1])) / 2.0f;
        if(!Ypt1_found && 30.0f / 180.0f * PI < conf && conf < 65.0f / 180.0f * PI && i < 0.8f / sample_dist)
        {
            Ypt1_rpts1s_id = i;
            Ypt1_found = true;
        }
        if(!Lpt1_found && 70.0f / 180.0f * PI < conf && conf < 140.0f / 180.0f * PI && i < 0.8f / sample_dist)
        {
            Lpt1_rpts1s_id = i;
            Lpt1_found = true;
        }
        if(conf > 5.0f / 180.0f * PI && i < 1.0f / sample_dist)
        {
            is_straight1 = false;
        }
        if(Ypt1_found && Lpt1_found && !is_straight1)
        {
            break;
        }
    }
    if(Lpt0_found && Lpt1_found)
    {
        float dx = rpts0s[Lpt0_rpts0s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
        float dy = rpts0s[Lpt0_rpts0s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
        float dn = sqrtf(dx * dx + dy * dy);
        if(fabsf(dn - 0.45f * pixel_per_meter) < 0.15f * pixel_per_meter)
        {
            float dwx = rpts0s[clip(Lpt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] -
                        rpts1s[clip(Lpt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0];
            float dwy = rpts0s[clip(Lpt0_rpts0s_id + 50, 0, rpts0s_num - 1)][1] -
                        rpts1s[clip(Lpt1_rpts1s_id + 50, 0, rpts1s_num - 1)][1];
            float dwn = sqrtf(dwx * dwx + dwy * dwy);
            if(!(dwn > 0.7f * pixel_per_meter &&
                 rpts0s[clip(Lpt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] < rpts0s[Lpt0_rpts0s_id][0] &&
                 rpts1s[clip(Lpt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0] > rpts1s[Lpt1_rpts1s_id][0]))
            {
                Lpt0_found = Lpt1_found = false;
            }
        }
        else
        {
            Lpt0_found = Lpt1_found = false;
        }
    }
}

static int build_reference_selected_midline(void)
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
                           (int)roundf(angle_dist / sample_dist),
                           pixel_per_meter * ROAD_WIDTH / 2);
            rpts_num = far_rpts0s_num - far_Lpt0_rpts0s_id;
        }
        else if(track_type == TRACK_RIGHT && far_Lpt1_found)
        {
            rpts = rptsc1;
            track_rightline(far_rpts1s + far_Lpt1_rpts1s_id,
                            far_rpts1s_num - far_Lpt1_rpts1s_id,
                            rpts,
                            (int)roundf(angle_dist / sample_dist),
                            pixel_per_meter * ROAD_WIDTH / 2);
            rpts_num = far_rpts1s_num - far_Lpt1_rpts1s_id;
        }
        else
        {
            rpts_num = 0;
        }
    }

    float cx = mapx[(int)(MT9V03X_CSI_H * 0.78f)][MT9V03X_CSI_W / 2];
    float cy = mapy[(int)(MT9V03X_CSI_H * 0.78f)][MT9V03X_CSI_W / 2];
    if(cx < 0.0f || cy < 0.0f)
    {
        cx = 86.0f;
        cy = 116.0f;
    }

    float min_dist = 1e10f;
    int begin_id = -1;
    for(int i = 0; i < rpts_num; i++)
    {
        float dx = rpts[i][0] - cx;
        float dy = rpts[i][1] - cy;
        float dist = sqrtf(dx * dx + dy * dy);
        if(dist < min_dist)
        {
            min_dist = dist;
            begin_id = i;
        }
    }

    if(cross_type == CROSS_IN)
    {
        begin_id = 0;
    }

    if(begin_id >= 0 && rpts_num - begin_id >= 3)
    {
        rpts[begin_id][0] = cx;
        rpts[begin_id][1] = cy;
        rptsn_num = sizeof(rptsn) / sizeof(rptsn[0]);
        resample_points(rpts + begin_id, rpts_num - begin_id, rptsn, &rptsn_num, sample_dist * pixel_per_meter);
    }
    else
    {
        rptsn_num = 0;
    }
    return rptsn_num > 0;
}

int autop_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total)
{
    if(gray == NULL)
    {
        return 0;
    }

    fill_reference_ipm_tables();
    configure_reference_params();
    g_autop_reference_encoder_total = encoder_total;
    img_raw.data = (uint8_t *)gray;
    reset_frame_outputs();

    autop_reference_process_image();
    autop_reference_find_corners();

    aim_distance = 0.58f;
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

    return build_reference_selected_midline();
}

int autop_reference_track_line_found(void)
{
    return rptsn_num > 0;
}
