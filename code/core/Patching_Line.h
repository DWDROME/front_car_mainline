#ifndef PATCHING_LINE_H
#define PATCHING_LINE_H

#include "headfile.h"

/* 两点连线生成边线（左线版本） */
void point_Cal_Line(float x1, float y1, float x2, float y2, float outline[][2], int *num);

/* 两点连线生成边线（右线版本） */
void point_Cal_Line_2(float x1, float y1, float x2, float y2, float outline[][2], int *num);

/* 补线原始边线 */
extern float rightline[MT9V03X_H][2];
extern int rightline_num;
extern float leftline[MT9V03X_H][2];
extern int leftline_num;

/* 补线等距采样 */
extern float Splicing_rightline_s0s[MT9V03X_H][2];
extern float Splicing_leftline_s1s[MT9V03X_H][2];
extern int Splicing_rightline_s0s_num;
extern int Splicing_leftline_s1s_num;

/* 补线中心线 */
extern float Splicing_rightline_center[MT9V03X_H][2];
extern int Splicing_rightline_center_num;
extern float Splicing_leftline_center[MT9V03X_H][2];
extern int Splicing_leftline_center_num;

#endif /* PATCHING_LINE_H */
