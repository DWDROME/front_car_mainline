#ifndef CORSS_H
#define CORSS_H
#include "headfile.h"
#include "stdio.h"
enum cross_type_e {
    CROSS_NONE = 0,     // 非十字模式
    CROSS_BEGIN,        // 找到左右两个L角点
    CROSS_IN,           // 两个L角点很近，即进入十字内部(此时切换远线控制)
    CROSS_HALF,
    CROSS_HALF_BEGIN,
    CROSS_HALF_RIGHT,
    CROSS_HALF_LEFT,
    CROSS_NUM
};

extern enum cross_type_e cross_type;

extern const char *cross_type_name[CROSS_NUM];

void check_cross();

void Double_check_cross_L();

void Double_check_cross_R();

void run_cross();

void cross_farline();

void cross_farline_L();

void cross_farline_R();

void cross_farline_half();

extern _Bool far_Lpt0_found, far_Lpt1_found;

extern int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;

extern uint8    if_lost_left_line ,if_lost_right_line ;

extern float conf3,conf4,conf3_max,conf4_max;

extern int8 Lpt0_found_flag,Lpt1_found_flag;

extern int8 far_Lpt0_found_flag,far_Lpt1_found_flag;

extern int far_ipts0[MT9V03X_H][2];
extern int far_ipts1[MT9V03X_H][2];
extern int far_ipts0_num, far_ipts1_num;

extern float far_rpts0[MT9V03X_H][2];
extern float far_rpts1[MT9V03X_H][2];
extern int far_rpts0_num, far_rpts1_num;

extern float far_rpts0b[MT9V03X_H][2];
extern float far_rpts1b[MT9V03X_H][2];
extern int far_rpts0b_num, far_rpts1b_num;

extern float far_rpts0s[MT9V03X_H][2];
extern float far_rpts1s[MT9V03X_H][2];
extern int far_rpts0s_num, far_rpts1s_num;

extern float far_rpts0a[MT9V03X_H];
extern float far_rpts1a[MT9V03X_H];
extern int far_rpts0a_num, far_rpts1a_num;

extern float far_rpts0an[MT9V03X_H];
extern float far_rpts1an[MT9V03X_H];
extern int far_rpts0an_num, far_rpts1an_num;

extern float  inv_Lpt0_found[2],inv_Lpt1_found[2];
extern float  inv_far_Lpt0_found[2],inv_far_Lpt1_found[2];

extern int far_x11,far_y1,far_y2;
#endif // CORSS_H
