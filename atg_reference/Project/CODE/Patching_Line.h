#include "headfile.h"
float Get_Line_Slope(int16 X_end,int16 Y_end,int16 X_start,int16 Y_start);

void Patching_Line(float pts_in[][2],int16 X_end,int16 Y_end,int16 X_start,int16 Y_start ,float slope,uint8 *step);

void point_Cal_Line(float x1,float y1,float x2,float y2,float outline[][2],int *num);

void Splicing_array(float pts_in1[][2], int num1, float pts_in2[][2], int num2,float pts_out[][2], int *num3,int dir);

void point_Cal_Line_2(float x1,float y1,float x2,float y2,float outline[][2],int *num);

extern uint8 if_Patching_Line ;

extern float rightline[MT9V03X_H][2];

extern float rightline2[MT9V03X_H][2];

extern float  leftline[MT9V03X_H][2];

extern float leftline2[MT9V03X_H][2];

extern int   rightline_num, leftline_num;

extern float inv_rightline[MT9V03X_H][2];

extern float inv_leftline[MT9V03X_H][2];

extern float Splicing_rightline[MT9V03X_H][2];

extern float Splicing_leftline[MT9V03X_H][2];

extern float inv_Splicing_rightline[MT9V03X_H][2];

extern float Splicing_rightline_center[MT9V03X_H][2];

extern int   Splicing_rightline_center_num;

extern float inv_Splicing_leftline[MT9V03X_H][2];

extern float Splicing_leftline_s1s[MT9V03X_H][2];

extern float Splicing_rightline_s0s[MT9V03X_H][2];

extern int   Splicing_rightline_num, Splicing_leftline_num;

extern int   Splicing_rightline_s0s_num;

extern int   Splicing_leftline_s1s_num;

extern float Splicing_leftline_center[MT9V03X_H][2];

extern int Splicing_leftline_center_num;

extern float mix_rightline[MT9V03X_H][2];
extern float mix_leftline[MT9V03X_H][2];

extern int mix_rightline_num;
extern int mix_leftline_num;

extern float inv_mix_rightline[MT9V03X_H][2];
extern float inv_mix_leftline[MT9V03X_H][2];
