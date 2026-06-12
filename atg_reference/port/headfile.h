#ifndef ATG_REFERENCE_PORT_HEADFILE_H
#define ATG_REFERENCE_PORT_HEADFILE_H

#include "common.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "imgproc.h"

#define ABS(x) (((x) > 0) ? (x) : (-(x)))
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define MT9V03X_W 160
#define MT9V03X_H 120
#define MT9V03X_HH (MT9V03X_H + 50)

#define BEGIN_X 7
#define BEGIN_Y ((int16)(MT9V03X_H * 0.9f))
#define AIM_DISTENCE aim_distance_far
#define AIM_DISTANCE_UP (aim_distance + 0.4f)
#define AIM_DISTANCE_UP_UP (aim_distance + 0.54f)

#define X_zoom 1.86f
#define Y_zoom 1.875f
#define Cut_height 119
#define Cut_Width 187

#define RED 0
#define GREEN 0
#define BLUE 0
#define YELLOW 0

#define lcd_drawpoint(x, y, color) ((void)0)
#define lcd_showint8(x, y, value) ((void)0)
#define lcd_showint16(x, y, value) ((void)0)
#define lcd_showfloat(x, y, value, len, precision) ((void)0)

enum track_type_e
{
    TRACK_LEFT,
    TRACK_RIGHT,
};

enum atg_port_garage_type_e
{
    GARAGE_NONE = 0,
    GARAGE_IN_LEFT,
    GARAGE_IN_RIGHT,
    GARAGE_FOUND_LEFT,
    GARAGE_FOUND_RIGHT,
    GARAGE_OUT_LEFT,
    GARAGE_OUT_RIGHT,
};

#include "round.h"
#include "cross.h"
#include "circle.h"
#include "Half_check.h"
#include "Patching_Line.h"
#include "Ramp.h"
#include "yroad.h"
#include "road.h"

extern uint8 global_Img[MT9V03X_H][MT9V03X_W];
extern uint8 global_Img2[Cut_height][Cut_Width];
extern uint8 global_Img3[50][80];
extern uint8 global_Img4[MT9V03X_H][MT9V03X_W];
extern uint8 Bin_Image[MT9V03X_H / 2][MT9V03X_W / 2];

extern image_t img_raw;

extern int ipts0[MT9V03X_HH][2], ipts1[MT9V03X_HH][2];
extern float rpts0[MT9V03X_HH][2], rpts1[MT9V03X_HH][2];
extern float rpts0b[MT9V03X_HH][2], rpts1b[MT9V03X_HH][2];
extern float rpts0s[MT9V03X_HH][2], rpts1s[MT9V03X_HH][2];
extern float rpts0a[MT9V03X_HH], rpts1a[MT9V03X_HH];
extern float rpts0an[MT9V03X_HH], rpts1an[MT9V03X_HH];
extern float rptsc0[MT9V03X_HH][2], rptsc1[MT9V03X_HH][2];
extern float rptsn[MT9V03X_HH][2], (*rpts)[2];
extern int ipts0_num, ipts1_num;
extern int rpts0_num, rpts1_num;
extern int rpts0b_num, rpts1b_num;
extern int rpts0s_num, rpts1s_num;
extern int rpts0a_num, rpts1a_num;
extern int rpts0an_num, rpts1an_num;
extern int rptsc0_num, rptsc1_num;
extern int rpts_num, rptsn_num;

extern int16 begin_x, begin_y;
extern int16 thres, thres_temp, thres_up;
extern int16 block_size, clip_value, line_blur_kernel;
extern float sample_dist;
extern int16 pixel_per_meter;
extern float angle_dist, far_rate, ROAD_WIDTH;
extern float aim_distance, aim_distance_temp, aim_distance_far, adaptive_aim_distance;
extern int aim_idx, aim_idx_up, aim_idx_up_up;
extern int16 Up_Error;

extern int Lpt0_rpts0s_id, Lpt1_rpts1s_id, Ypt0_rpts0s_id, Ypt1_rpts1s_id;
extern int inv_Lpt0_rpts0s_id, inv_Lpt1_rpts1s_id;
extern bool is_straight0, is_straight1, is_straight_far_0, is_straight_far_1;
extern bool Ypt0_found, Ypt1_found, Lpt0_found, Lpt1_found;
extern bool is_turn0, is_turn1;

extern enum track_type_e track_type;

extern uint16 OSTU_thres;
extern int16 DisPlay_Flag;
extern int16 total_distence, Ramp_total_distence;
extern uint8 Count_dis_Flag;
extern uint8 Count_Garage_num;
extern int garage_type;
extern enum ramp_type_e ramp_type;
extern enum yroad_type_e yroad_type;
extern enum road_type_e road_type;
extern enum speed_type_e speed_type;
extern int16 LAimSpeed, RAimSpeed, SetSpeed, AimSpeed;
extern uint16 Clean_Time_count, Clean_Time_count_flag;
extern int TFmini_Plus_Dis, TFmini_Plus_Strong;
extern float angle, angle_up, pure_angle, pure_angle_up, pure_angle_up_up;
extern float Guide, Guide_up, Guide_up_up;
extern float cx, cy;
extern float inv_aim_idx[2], inv_aim_idx_up[2], inv_aim_idx_up_up[2];
extern float inv_rptsn[MT9V03X_HH][2];
extern int broadcast_flag;
extern uint8 if_check_ramp, if_clean_pid;
extern int not_have_line;

int range_limit(int x, int low, int up);

#include "shy_Image.h"

#endif
