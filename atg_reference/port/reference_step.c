#include "atg_reference_step.h"

#include <string.h>

#include "headfile.h"
#include "shy_Image.h"
#include "round.h"

extern int64_t g_atg_reference_encoder_total;

static void configure_atg_params(void)
{
    begin_x = BEGIN_X;
    begin_y = BEGIN_Y;
    block_size = 5;
    clip_value = 8;
    line_blur_kernel = 7;
    ROAD_WIDTH = 0.45f;
    pixel_per_meter = 116;
    sample_dist = 0.03f;
    angle_dist = 0.2f;
    aim_distance_far = 0.58f;
    aim_distance = aim_distance_far;
}

static void clear_frame_outputs(void)
{
    ipts0_num = ipts1_num = 0;
    rpts0_num = rpts1_num = 0;
    rpts0b_num = rpts1b_num = 0;
    rpts0s_num = rpts1s_num = 0;
    rpts0a_num = rpts1a_num = 0;
    rpts0an_num = rpts1an_num = 0;
    rptsc0_num = rptsc1_num = 0;
    rptsn_num = 0;
    rpts = NULL;
    rpts_num = 0;
}

void atg_reference_reset(void)
{
    configure_atg_params();
    g_atg_reference_encoder_total = 0;
    track_type = TRACK_RIGHT;
    round_type = ROUND_NONE;
    clear_frame_outputs();
}

int atg_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total)
{
    if(gray == NULL)
    {
        return 0;
    }

    configure_atg_params();
    g_atg_reference_encoder_total = encoder_total;
    img_raw.data = (uint8 *)gray;
    clear_frame_outputs();

    image_handle();
    find_corners();

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

    if(rpts_num <= 0)
    {
        return 0;
    }

    rptsn_num = rpts_num;
    if(rptsn_num > MT9V03X_HH)
    {
        rptsn_num = MT9V03X_HH;
    }
    memcpy(rptsn, rpts, (size_t)rptsn_num * sizeof(rptsn[0]));
    return rptsn_num > 0;
}

int atg_reference_track_line_found(void)
{
    return rptsn_num > 0;
}
