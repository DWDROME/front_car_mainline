/* =====================================================================
 *  补线工具函数
 *
 *  提供直线生成、线段拼接等基础操作，用于十字/圆环等元素的补线。
 *
 *  主要功能：
 *    Patching_Line   — 从起点到终点按斜率生成补线点序列
 *    point_Cal_Line  — 两点定线，按 x 顺序生成点（正向）
 *    point_Cal_Line_2 — 两点定线，按 x 逆序生成点（反向）
 *    Splicing_array  — 拼接两条线段
 * ===================================================================== */
#include "Patching_Line.h"

uint8 if_Patching_Line = 0;                            /* 是否启用补线 */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* --- 右侧补线数据 --- */
float rightline[MT9V03X_H][2];                         /* 右侧补线点 */
float rightline2[MT9V03X_H][2];                        /* 右侧补线点2 */
int rightline_num;
float Splicing_rightline[MT9V03X_H][2];               /* 拼接后的右线 */
int Splicing_rightline_num;
float inv_Splicing_rightline[MT9V03X_H][2];           /* 逆旋转后的拼接右线 */
float Splicing_rightline_s0s[MT9V03X_H][2];           /* 等距采样后的拼接右线 */
int Splicing_rightline_s0s_num;
float inv_rightline[MT9V03X_H][2];                    /* 逆旋转后的右线 */
float Splicing_rightline_center[MT9V03X_H][2];        /* 拼接右线的中线 */
int Splicing_rightline_center_num;

/* --- 左侧补线数据 --- */
float leftline[MT9V03X_H][2];                          /* 左侧补线点 */
float leftline2[MT9V03X_H][2];                         /* 左侧补线点2 */
float Splicing_leftline[MT9V03X_H][2];                /* 拼接后的左线 */
float Splicing_leftline_s1s[MT9V03X_H][2];            /* 等距采样后的拼接左线 */
int  Splicing_leftline_s1s_num;
float inv_Splicing_leftline[MT9V03X_H][2];            /* 逆旋转后的拼接左线 */
int  leftline_num;
int  Splicing_leftline_num;
float inv_leftline [MT9V03X_H][2];                     /* 逆旋转后的左线 */
float Splicing_leftline_center[MT9V03X_H][2];         /* 拼接左线的中线 */
int Splicing_leftline_center_num;

/* --- 混合线数据 --- */
float inv_mix_rightline[MT9V03X_H][2];
float inv_mix_leftline[MT9V03X_H][2];
float mix_rightline[MT9V03X_H][2];
float mix_leftline[MT9V03X_H][2];
int mix_rightline_num;
int mix_leftline_num;

/* 工具函数 */
float my_min(float a ,float b)
{
    if (a<b) return a;
    else return b;
}

float my_max(float a,float b)
{
    if(a>b) return a;
    else return b;
}

/* 计算两点连线的斜率 */
float Get_Line_Slope(int16 X_end,int16 Y_end,int16 X_start,int16 Y_start)
{
    return (X_end - X_start)/(Y_end - Y_start);
}

/* 从起点到终点按斜率生成补线点序列。
 * 斜率 > 0：向右上；斜率 < 0：向左上。
 * step 输出生成的点数。 */
void Patching_Line(float pts_in[][2],int16 X_end,int16 Y_end,int16 X_start,int16 Y_start ,float slope,uint8 *step){

    pts_in[0][0]= X_start  ;
    pts_in[0][1]= Y_start  ;
    if(Y_start>Y_end){
        int cnt = 1;
        for(int i=1;pts_in[i-1][1]>=Y_end;i++){
            pts_in[i][0]= X_start  - slope*cnt;
            pts_in[i][1]= Y_start  - cnt;
            cnt++;
        }
        step = cnt;
    }
    else if(Y_start<=Y_end){
        int cnt = -1;
        for(int i=1;pts_in[i-1][1]>=Y_end;i++){
            pts_in[i][0]= X_start  - slope*cnt;
            if((Y_end-Y_start)>1){
                pts_in[i][1]= Y_start  - cnt;
                cnt--;
            }
            else pts_in[i][1]= Y_start;

        }
        step = -cnt;
    }
}

/* 两点定线，按 x 顺序生成点（正向） */
void point_Cal_Line(float x1,float y1,float x2,float y2,float outline[][2],int *num)
{
int delta= (int)(x2-x1);
if(delta==0)delta=1;
float k=(y2-y1)/(delta*1.0f);
float b=y1-k*x1;
float min_x=my_min(x1,x2);
float max_x=my_max(x1,x2);
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
    float min_x=my_min(x1,x2);
    float max_x=my_max(x1,x2);
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

/* 拼接两条线段。
 * dir=0：正向拼接（pts_in2 保持原序）
 * dir=1：反向拼接（pts_in2 逆序） */
void Splicing_array(float pts_in1[][2], int num1, float pts_in2[][2], int num2,float pts_out[][2], int *num3,int dir)
{
    int inv_num2 = num2-1;

    for(int i=0;i<num1;i++){
        pts_out[i][0] = pts_in1[i][0];
        pts_out[i][1] = pts_in1[i][1];
    }
    if(dir==0)
    {
        for(int i=num1;i<num1+num2;i++){
            pts_out[i][0] = pts_in2[i][0];
            pts_out[i][1] = pts_in2[i][1];
        }
    }
    else{

        for(int i=num1;i<num1+num2;i++){
            pts_out[i][0] = pts_in2[inv_num2][0];
            pts_out[i][1] = pts_in2[inv_num2][1];
            inv_num2--;
            if(inv_num2<=0)
                break;
        }
    }
    *num3 = (num1+num2);
}


