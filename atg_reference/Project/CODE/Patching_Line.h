/* =====================================================================
 *  补线工具模块接口（Patching_Line）
 *
 *  提供补线相关的工具函数：
 *    - 斜率计算
 *    - 两点连线生成边线
 *    - 边线拼接
 *    - 补线数据存储
 * ===================================================================== */
#include "headfile.h"

/* ================= 接口函数 ================= */

/* 计算两点之间的斜率 */
float Get_Line_Slope(int16 X_end, int16 Y_end, int16 X_start, int16 Y_start);

/* 补线：从 (X_start,Y_start) 到 (X_end,Y_end)，按 slope 偏移生成边线 */
void Patching_Line(float pts_in[][2], int16 X_end, int16 Y_end, int16 X_start, int16 Y_start, float slope, uint8 *step);

/* 两点连线生成边线（左线版本） */
void point_Cal_Line(float x1, float y1, float x2, float y2, float outline[][2], int *num);

/* 两点连线生成边线（右线版本） */
void point_Cal_Line_2(float x1, float y1, float x2, float y2, float outline[][2], int *num);

/* 边线拼接：dir=0 左线拼接，dir=1 右线拼接 */
void Splicing_array(float pts_in1[][2], int num1, float pts_in2[][2], int num2, float pts_out[][2], int *num3, int dir);

/* ================= 补线数据 ================= */

extern uint8 if_Patching_Line;

/* 右线数据 */
extern float rightline[MT9V03X_H][2];
extern float rightline2[MT9V03X_H][2];
extern int rightline_num;

/* 左线数据 */
extern float leftline[MT9V03X_H][2];
extern float leftline2[MT9V03X_H][2];
extern int leftline_num;

/* 逆透视后的线 */
extern float inv_rightline[MT9V03X_H][2];
extern float inv_leftline[MT9V03X_H][2];

/* 拼接后的线 */
extern float Splicing_rightline[MT9V03X_H][2];
extern float Splicing_leftline[MT9V03X_H][2];
extern int Splicing_rightline_num, Splicing_leftline_num;

/* 拼接后等距采样 */
extern float Splicing_rightline_s0s[MT9V03X_H][2];
extern float Splicing_leftline_s1s[MT9V03X_H][2];
extern int Splicing_rightline_s0s_num;
extern int Splicing_leftline_s1s_num;

/* 拼接后中心线（偏移半赛宽） */
extern float Splicing_rightline_center[MT9V03X_H][2];
extern int Splicing_rightline_center_num;
extern float Splicing_leftline_center[MT9V03X_H][2];
extern int Splicing_leftline_center_num;

/* 逆透视后的拼接线 */
extern float inv_Splicing_rightline[MT9V03X_H][2];
extern float inv_Splicing_leftline[MT9V03X_H][2];

/* 混合线 */
extern float mix_rightline[MT9V03X_H][2];
extern float mix_leftline[MT9V03X_H][2];
extern int mix_rightline_num;
extern int mix_leftline_num;
extern float inv_mix_rightline[MT9V03X_H][2];
extern float inv_mix_leftline[MT9V03X_H][2];

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
