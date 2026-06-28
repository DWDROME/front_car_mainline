/* =====================================================================
 *  补线工具函数
 *
 *  提供直线生成、线段拼接等基础操作，用于十字/圆环等元素的补线。
 *
 *  主要功能：
 *    point_Cal_Line  — 两点定线，按 x 顺序生成点（正向）
 *    point_Cal_Line_2 — 两点定线，按 x 逆序生成点（反向）
 * ===================================================================== */
#include "Patching_Line.h"

/* --- 右侧补线数据 --- */
float rightline[MT9V03X_H][2];                         /* 右侧补线点 */
int rightline_num;
float Splicing_rightline_s0s[MT9V03X_H][2];           /* 等距采样后的拼接右线 */
int Splicing_rightline_s0s_num;
float Splicing_rightline_center[MT9V03X_H][2];        /* 拼接右线的中线 */
int Splicing_rightline_center_num;

/* --- 左侧补线数据 --- */
float leftline[MT9V03X_H][2];                          /* 左侧补线点 */
float Splicing_leftline_s1s[MT9V03X_H][2];            /* 等距采样后的拼接左线 */
int  Splicing_leftline_s1s_num;
int  leftline_num;
float Splicing_leftline_center[MT9V03X_H][2];         /* 拼接左线的中线 */
int Splicing_leftline_center_num;

/* 两点定线，按 x 顺序生成点（正向） */
void point_Cal_Line(float x1,float y1,float x2,float y2,float outline[][2],int *num)
{
int delta= (int)(x2-x1);
if(delta==0)delta=1;
float k=(y2-y1)/(delta*1.0f);
float b=y1-k*x1;
float min_x=(x1 < x2) ? x1 : x2;
float max_x=(x1 > x2) ? x1 : x2;
for(int j=(int)min_x;j<(int)max_x;j++)
{
    int i;
    int zhi;
    zhi=k*j+b;

    if(zhi>MT9V03X_H)
    zhi=MT9V03X_H;
    else if(zhi<0)
    zhi=0;
    i=j-min_x;
    outline[i][0]=j;
    outline[i][1]=zhi;
}
*num=(int)max_x-(int)min_x;
}

/* 两点定线，按 x 逆序生成点（反向） */
void point_Cal_Line_2(float x1,float y1,float x2,float y2,float outline[][2],int *num)
{
    int delta= (int)(x2-x1);
    if(delta==0)delta=1;
    float k=(y2-y1)/(delta*1.0f);
    float b=y1-k*x1;
    float min_x=(x1 < x2) ? x1 : x2;
    float max_x=(x1 > x2) ? x1 : x2;
    for(int j=(int)min_x;j<(int)max_x;j++)
    {
        int i;
        int zhi;
        zhi=k*j+b;

        if(zhi>MT9V03X_H)
        zhi=MT9V03X_H;
        else if(zhi<0)
        zhi=0;
        i=(int)max_x - 1 - j;
        outline[i][0]=j;
        outline[i][1]=zhi;
    }
    *num=(int)max_x-(int)min_x;
}
