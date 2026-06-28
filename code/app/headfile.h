/* =====================================================================
 *  视觉全局出口（headfile）
 *
 *  定义 ATG 视觉主线仍在共用的常量、类型别名和全局状态。
 *  新代码优先 include 自己需要的窄头；只有直接读这些全局状态时再 include 本文件。
 * ===================================================================== */
#ifndef APP_HEADFILE_H
#define APP_HEADFILE_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "imgproc.h"

/* ================= ATG 类型别名 ================= */

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

/* ================= 通用宏 ================= */

#define ABS(x) (((x) > 0) ? (x) : (-(x)))
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/* ================= 图像与搜线参数 ================= */

#define MT9V03X_W 160                           /* 图像宽度 */
#define MT9V03X_H 120                           /* 图像高度 */
#define MT9V03X_HH (MT9V03X_H + 50)            /* 边线数组最大点数（留余量） */

#define BEGIN_X 7                               /* 种子点搜索起始 x 偏移 */
#define BEGIN_Y ((int16)(MT9V03X_H * 0.9f))     /* 种子点搜索起始 y 行 */
#define AIM_DISTENCE aim_distance_far           /* 主瞄准距离 */
#define AIM_DISTANCE_UP (aim_distance + 0.4f)   /* 辅助瞄准距离（更远） */
#define AIM_DISTANCE_UP_UP (aim_distance + 0.54f) /* 辅助瞄准距离（最远） */

/* ================= 跟踪方向枚举 ================= */

enum track_type_e
{
    TRACK_LEFT,     /* 跟左线 */
    TRACK_RIGHT,    /* 跟右线 */
};

/* ================= 车库状态枚举 ================= */

enum atg_port_garage_type_e
{
    GARAGE_NONE = 0,        /* 无车库 */
    GARAGE_IN_LEFT,         /* 左入库 */
    GARAGE_IN_RIGHT,        /* 右入库 */
    GARAGE_FOUND_LEFT,      /* 左车库发现 */
    GARAGE_FOUND_RIGHT,     /* 右车库发现 */
    GARAGE_OUT_LEFT,        /* 左出库 */
    GARAGE_OUT_RIGHT,       /* 右出库 */
};

/* ================= 元素状态头 ================= */

#include "round.h"
#include "cross.h"
#include "circle.h"
#include "Half_check.h"
#include "Patching_Line.h"
#include "Ramp.h"
#include "yroad.h"
#include "road.h"

/* ================= 全局变量声明 ================= */

/* 原始图像 */
extern image_t img_raw;

/* 边线数组声明（详见 app/vision_globals.c） */
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

/* 搜线参数 */
extern int16 begin_x, begin_y;
extern int16 thres;
extern int16 block_size, clip_value, line_blur_kernel;
extern float sample_dist;
extern int16 pixel_per_meter;
extern float angle_dist, ROAD_WIDTH;
extern float aim_distance, aim_distance_far;
extern int aim_idx, aim_idx_up, aim_idx_up_up;
extern int16 Up_Error;

/* 角点状态 */
extern int Lpt0_rpts0s_id, Lpt1_rpts1s_id, Ypt0_rpts0s_id, Ypt1_rpts1s_id;
extern bool is_straight0, is_straight1, is_straight_far_0, is_straight_far_1;
extern bool Ypt0_found, Ypt1_found, Lpt0_found, Lpt1_found;

/* 元素与控制状态 */
extern enum track_type_e track_type;

extern uint16 OSTU_thres;
extern int16 total_distence, Ramp_total_distence;
extern uint8 Count_dis_Flag;
extern uint8 Count_Garage_num;
extern int garage_type;
extern enum ramp_type_e ramp_type;
extern enum yroad_type_e yroad_type;
extern enum road_type_e road_type;
extern enum speed_type_e speed_type;
extern uint16 Clean_Time_count, Clean_Time_count_flag;
extern int TFmini_Plus_Dis, TFmini_Plus_Strong;
extern float pure_angle, pure_angle_up, pure_angle_up_up;
extern float Guide, Guide_up, Guide_up_up;
extern float cx, cy;
extern float inv_aim_idx[2];
extern float inv_rptsn[MT9V03X_HH][2];
extern uint8 if_check_ramp;
extern int not_have_line;

#include "shy_Image.h"

#endif /* APP_HEADFILE_H */
