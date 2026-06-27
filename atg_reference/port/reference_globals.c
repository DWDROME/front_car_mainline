/* =====================================================================
 *  ATG 参考线处理全局变量定义（reference_globals）
 *
 *  所有模块共享的全局变量统一定义在此处，避免重复定义。
 *  包括：图像缓冲区、边线数组、搜线参数、角点状态、控制输出等。
 * ===================================================================== */
#include "headfile.h"
#include "round.h"

/* ================= 图像缓冲区 ================= */
uint8 global_Img[MT9V03X_H][MT9V03X_W];
uint8 global_Img2[Cut_height][Cut_Width];
uint8 global_Img3[50][80];
uint8 global_Img4[MT9V03X_H][MT9V03X_W];
uint8 Bin_Image[MT9V03X_H / 2][MT9V03X_W / 2];

image_t img_raw = DEF_IMAGE(NULL, MT9V03X_W, MT9V03X_H);

/* ================= 边线数组 =================
 *
 * 命名规则：
 *   ipts  = 原图像素坐标边线（int）
 *   rpts  = 俯视角坐标边线（float）
 *   rptsb = 滤波后的边线
 *   rptss = 等距采样后的边线
 *   rptsa = 局部转角
 *   rptsan = NMS 后的转角（只保留角点）
 *   rptsc = 中心线（边线偏移半赛宽）
 *   rptsn = 归一化后的控制用线
 *   0 = 左线，1 = 右线
 */
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

/* ================= 搜线参数 ================= */

int16 begin_x = BEGIN_X;    /* 种子点搜索起始 x 偏移 */
int16 begin_y = BEGIN_Y;    /* 种子点搜索起始 y 行 */
int16 thres = 140;          /* 固定阈值（备用） */
int16 thres_temp, thres_up;
int16 block_size = 5;       /* 自适应阈值窗口大小 */
int16 clip_value = 8;       /* 自适应阈值偏移量 */
int16 line_blur_kernel = 7; /* 边线滤波核大小 */
float sample_dist = 0.02f;  /* 等距采样间距（m） */
int16 pixel_per_meter = 116;/* 每米对应像素数 */
float angle_dist = 0.2f;    /* 角度计算前后距离（m） */
float far_rate = 0.5f;
float ROAD_WIDTH = 0.45f;   /* 赛道宽度（m） */
float aim_distance = 0.58f; /* 瞄准距离（m） */
float aim_distance_temp, aim_distance_far = 0.58f, adaptive_aim_distance;
int aim_idx, aim_idx_up, aim_idx_up_up;
int16 Up_Error;

/* ================= 角点状态 ================= */

int Lpt0_rpts0s_id, Lpt1_rpts1s_id;    /* L 角点在 rptss 数组中的索引 */
int Ypt0_rpts0s_id, Ypt1_rpts1s_id;    /* Y 角点在 rptss 数组中的索引 */
int inv_Lpt0_rpts0s_id, inv_Lpt1_rpts1s_id;
bool is_straight0, is_straight1;        /* 左右线是否为长直道 */
bool is_straight_far_0, is_straight_far_1; /* 左右远端线是否为直道 */
bool Ypt0_found, Ypt1_found;           /* Y 角点是否找到 */
bool Lpt0_found, Lpt1_found;           /* L 角点是否找到 */
bool is_turn0, is_turn1;

/* ================= 元素与控制状态 ================= */

enum track_type_e track_type = TRACK_RIGHT; /* 跟踪方向：左线或右线 */

uint16 OSTU_thres;
int16 DisPlay_Flag;
int16 total_distence, Ramp_total_distence;  /* 累计行驶距离（counts） */
uint8 Count_dis_Flag;                       /* 距离计数使能 */
uint8 Count_Garage_num;
int garage_type = GARAGE_NONE;
int16 LAimSpeed, RAimSpeed, SetSpeed, AimSpeed;
uint16 Clean_Time_count, Clean_Time_count_flag;
int TFmini_Plus_Dis, TFmini_Plus_Strong;   /* 激光测距 */
float angle, angle_up, pure_angle, pure_angle_up, pure_angle_up_up;
float Guide, Guide_up, Guide_up_up;        /* 横向偏差引导值 */
float cx, cy;                               /* 车辆参考点 IPM 坐标 */
float inv_aim_idx[2], inv_aim_idx_up[2], inv_aim_idx_up_up[2];
float inv_rptsn[MT9V03X_HH][2];
uint8 if_check_ramp;

/* ================= 工具函数 ================= */

/* 钳位整数到 [low, up] 范围 */
int range_limit(int x, int low, int up)
{
    return x > up ? up : x < low ? low : x;
}

/* 清除距离计数器 */
void atg_reference_clear_distance_counter(void)
{
    total_distence = 0;
    Ramp_total_distence = 0;
    Count_dis_Flag = 0;
}
