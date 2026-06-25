#include "headfile.h"

#include "round.h"

uint8 global_Img[MT9V03X_H][MT9V03X_W];
uint8 global_Img2[Cut_height][Cut_Width];
uint8 global_Img3[50][80];
uint8 global_Img4[MT9V03X_H][MT9V03X_W];
uint8 Bin_Image[MT9V03X_H / 2][MT9V03X_W / 2];

image_t img_raw = DEF_IMAGE(NULL, MT9V03X_W, MT9V03X_H);

int ipts0[MT9V03X_HH][2], ipts1[MT9V03X_HH][2];
float rpts0[MT9V03X_HH][2], rpts1[MT9V03X_HH][2];
float rpts0b[MT9V03X_HH][2], rpts1b[MT9V03X_HH][2];
float rpts0s[MT9V03X_HH][2], rpts1s[MT9V03X_HH][2];
float rpts0a[MT9V03X_HH], rpts1a[MT9V03X_HH];
float rpts0an[MT9V03X_HH], rpts1an[MT9V03X_HH];
float rptsc0[MT9V03X_HH][2], rptsc1[MT9V03X_HH][2];
float rptsn[MT9V03X_HH][2], (*rpts)[2];
int ipts0_num, ipts1_num;
int rpts0_num, rpts1_num;
int rpts0b_num, rpts1b_num;
int rpts0s_num, rpts1s_num;
int rpts0a_num, rpts1a_num;
int rpts0an_num, rpts1an_num;
int rptsc0_num, rptsc1_num;
int rpts_num, rptsn_num;

int16 begin_x = BEGIN_X;
int16 begin_y = BEGIN_Y;
int16 thres = 140;
int16 thres_temp, thres_up;
int16 block_size = 5;
int16 clip_value = 8;
int16 line_blur_kernel = 7;
float sample_dist = 0.02f;
int16 pixel_per_meter = 116;
float angle_dist = 0.2f;
float far_rate = 0.5f;
float ROAD_WIDTH = 0.45f;
float aim_distance = 0.58f;
float aim_distance_temp, aim_distance_far = 0.58f, adaptive_aim_distance;
int aim_idx, aim_idx_up, aim_idx_up_up;
int16 Up_Error;

int Lpt0_rpts0s_id, Lpt1_rpts1s_id, Ypt0_rpts0s_id, Ypt1_rpts1s_id;
int inv_Lpt0_rpts0s_id, inv_Lpt1_rpts1s_id;
bool is_straight0, is_straight1, is_straight_far_0, is_straight_far_1;
bool Ypt0_found, Ypt1_found, Lpt0_found, Lpt1_found;
bool is_turn0, is_turn1;

enum track_type_e track_type = TRACK_RIGHT;

uint16 OSTU_thres;
int16 DisPlay_Flag;
int16 total_distence, Ramp_total_distence;
uint8 Count_dis_Flag;
uint8 Count_Garage_num;
int garage_type = GARAGE_NONE;
int16 LAimSpeed, RAimSpeed, SetSpeed, AimSpeed;
uint16 Clean_Time_count, Clean_Time_count_flag;
int TFmini_Plus_Dis, TFmini_Plus_Strong;
float angle, angle_up, pure_angle, pure_angle_up, pure_angle_up_up;
float Guide, Guide_up, Guide_up_up;
float cx, cy;
float inv_aim_idx[2], inv_aim_idx_up[2], inv_aim_idx_up_up[2];
float inv_rptsn[MT9V03X_HH][2];
uint8 if_check_ramp;

int64_t g_atg_reference_encoder_total;

int range_limit(int x, int low, int up)
{
    return x > up ? up : x < low ? low : x;
}

int64_t get_total_encoder(void)
{
    return g_atg_reference_encoder_total;
}

void atg_reference_clear_distance_counter(void)
{
    total_distence = 0;
    Ramp_total_distence = 0;
    Count_dis_Flag = 0;
}
