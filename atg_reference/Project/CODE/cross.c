#include "cross.h"
#include "motor.h"
#include "headfile.h"

#define PI               3.14159265358979f
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)
enum cross_type_e cross_type = CROSS_NONE;

const char *cross_type_name[CROSS_NUM] = {
        "CROSS_NONE",
        "CROSS_BEGIN", "CROSS_IN",
        "CROSS_HALF"
};

// 编码器值，用于防止一些重复触发等。
int64_t cross_encoder;

float conf3,conf4,conf3_max,conf4_max;  //记录边线角度值及其最大值

uint8 if_lost_left_line = 0,if_lost_right_line = 0;


// 以下定义为十字寻远线设定
bool far_Lpt0_found, far_Lpt1_found;
int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;
int8 Lpt0_found_flag,Lpt1_found_flag;
int8 far_Lpt0_found_flag,far_Lpt1_found_flag;
int far_ipts0[MT9V03X_H][2];
int far_ipts1[MT9V03X_H][2];
int far_ipts0_num, far_ipts1_num;

float far_rpts0[MT9V03X_H][2];
float far_rpts1[MT9V03X_H][2];
int far_rpts0_num, far_rpts1_num;

float far_rpts0b[MT9V03X_H][2];
float far_rpts1b[MT9V03X_H][2];
int far_rpts0b_num, far_rpts1b_num;

float far_rpts0s[MT9V03X_H][2];
float far_rpts1s[MT9V03X_H][2];
int far_rpts0s_num, far_rpts1s_num;

float far_rpts0a[MT9V03X_H];
float far_rpts1a[MT9V03X_H];
int far_rpts0a_num, far_rpts1a_num;

float far_rpts0an[MT9V03X_H];
float far_rpts1an[MT9V03X_H];
int far_rpts0an_num, far_rpts1an_num;

int not_have_line = 0;

int far_x1 = 32, far_x2 = 118, far_y1, far_y2;
int far_x11=70 , far_x22= 100;
float inv_Lpt0_found[2],inv_Lpt1_found[2];
float inv_far_Lpt0_found[2],inv_far_Lpt1_found[2];
//双L角点,切十字模式
void check_cross() {
    bool Xfound = Lpt0_found && Lpt1_found;
    if (cross_type == CROSS_NONE && Xfound) cross_type = CROSS_BEGIN;
}
void Double_check_cross_R()
{
    cross_farline_R();
}
void Double_check_cross_L()
{
    //当转弯接十字有一侧全部丢线时的补救方法
    cross_farline_L();

}
void run_cross()
{
    bool Xfound = Lpt0_found && Lpt1_found;
    int64_t current_encoder = 1;
    float Lpt0y = rpts0s[Lpt0_rpts0s_id][1];
    float Lpt1y = rpts1s[Lpt1_rpts1s_id][1];
    //检测到十字，先按照近线走
    // 十字截断
    if (cross_type == CROSS_BEGIN) {
        if (Lpt0_found) {
            rptsc0_num = rpts0s_num = Lpt0_rpts0s_id;
        }
        if (Lpt1_found) {
            rptsc1_num = rpts1s_num = Lpt1_rpts1s_id;
        }

        //aim_distance = AIM_DISTENCE;
        aim_distance = 0.4; // 参考的
        //近角点过少，进入远线控制
        if ((Xfound && (Lpt0_rpts0s_id < 0.1 / sample_dist || Lpt1_rpts1s_id < 0.1 / sample_dist))/* || (rpts1_num <30 && rpts0_num<30)*/) {
            cross_type = CROSS_IN;
            cross_encoder = current_encoder;
        }
    }
        //远线控制进十字,begin_y渐变靠近防丢线
    else if (cross_type == CROSS_IN) {
        //寻远线,算法与近线相同
        cross_farline();

        if (rpts1s_num < 5 && rpts0s_num < 5) { not_have_line++; }
        if (not_have_line > 2 && rpts1s_num > 20 && rpts0s_num > 20) {
            cross_type = CROSS_NONE;
            ramp_type=RAMP_NONE;
            broadcast_flag=1;
            Clean_Time_count_flag = 0;
            not_have_line = 0;
        }
        if (far_Lpt1_found) { track_type = TRACK_RIGHT; }
        else if (far_Lpt0_found) { track_type = TRACK_LEFT; }
        else if (not_have_line > 0 && rpts1s_num < 5) { track_type = TRACK_RIGHT; }
        else if (not_have_line > 0 && rpts0s_num < 5) { track_type = TRACK_LEFT; }

    }
    else if(cross_type == CROSS_HALF){
        //最终所有的十字执行都在这个部分，可以实现在仅看到一侧视野的情况下通过十字（另一侧全丢都没问题）
        //Lpt0_found_flag和Lpt1_found_flag判断看到的是哪一侧
        if(Lpt0_found_flag)
        {
            //若找到了左近处90°拐点，开始搜左远线，后续操作在中线跟踪部分
            cross_farline_L();
            aim_distance = 0.25;
            track_type = TRACK_LEFT;
            if (rpts0s_num < 5) { not_have_line++; }
            if (not_have_line > 2 && rpts1s_num > 20 && rpts0s_num > 20) {
                //经历过一个先丢先再有线的过程说明可以刷掉十字了
                cross_type = CROSS_NONE;
                if_lost_left_line = 0;
                Clean_Time_count_flag = 0;
                ramp_type=RAMP_NONE;
                broadcast_flag=1;
                aim_distance = AIM_DISTENCE;
                not_have_line = 0;
                Lpt0_found_flag=0;
                Lpt1_found_flag=0;
            }
        }
        if(Lpt1_found_flag)
        {
            cross_farline_R();
            aim_distance = 0.75;
            track_type = TRACK_RIGHT;
            if (rpts1s_num < 5) { not_have_line++; }
            if (not_have_line > 2 && rpts0s_num > 20 && rpts1s_num > 20) {
                cross_type = CROSS_NONE;
                if_lost_right_line= 0;
                ramp_type=RAMP_NONE;
                Clean_Time_count_flag = 0;
                broadcast_flag=1;
                aim_distance = AIM_DISTENCE;
                not_have_line = 0;
                Lpt1_found_flag=0;
                Lpt0_found_flag=0;
            }
        }

    }
}
void cross_farline_L()
{

    if (Lpt0_found&&rpts0s_num>=3&&!if_lost_left_line) {
        /*
         * if_lost_left_line表示边线是否曾经丢失过
                        若if_lost_left_line的条件不满足，则说明边线经过了一个先有线后丢线的过程，有可能是某个元素行进到了下一个阶段
                        比如圆环从CIRCLE_LEFT_BEGIN跳到了CIRCLE_LEFT_IN，从十字路口中间驶离十字元素等情况都会经过这个过程
                        第一步，当找到左侧拐点，且左侧的拐点边线还在没丢的情况下，将俯视角下的拐点坐标映射回原图坐标
                        利用此坐标作为起始点，可以向上去找同侧远端边线
                        假设*表示边线，&为近处的拐点，#表示远处的拐点，则在这个近处拐点&的坐标基础上进行一定的偏移，用￥表示远端边线搜索的起始点坐标
                        偏移的目的是保证这个点，在车身无论多歪的情况下能够始终在近端边线的上方，从而能够向上搜到远处的边线

                                 *
                                 *
                                 *
                                 *
                                 *
                                 *
          ***********************#




                                                  ￥

          ***********************&
                                 *
                                 *
                                 *
                                 *
                                 *
                                 *
                                 *
                                 *


         */
        inv_Lpt0_found[0] = Cal_inv_rot_x(rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][0],rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][1])-5;
        inv_Lpt0_found[1] = Cal_inv_rot_y(rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][0],rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][1])-17;//-5和-17都是在拐点坐标的基础上进行相对偏移
        rptsc0_num = rpts0s_num = Lpt0_rpts0s_id-1 ;            //截断处理，防止顺着一侧边线划出去
    }
    else if(circle_type== CIRCLE_LEFT_IN||circle_type== CIRCLE_RIGHT_OUT||circle_type== CIRCLE_RIGHT_END){

        //在这个if条件中主要用于圆环各阶段近处丢线情况下，寻找合适的起始点，从而从远端的边线信息中提取角点，从而进行补线的操作
        if(circle_type== CIRCLE_LEFT_IN)
        {
            //圆环CIRCLE_LEFT_IN阶段原本是利用搜到的内圆边线作为中线，但在R50且车速很快的情况下，会有丢失内侧边线的可能性
            if(ipts0_num>12&&!if_lost_left_line){
                //当内侧边线还能搜索到、没丢过线、满足一定的长度时，根据内侧边线末端的一个点的坐标作为基准，向赛道中见方向平移一定的距离作为远端边线搜索的起始点
                inv_Lpt0_found[0] = ipts0[ipts0_num-3][0]+15;
                inv_Lpt0_found[1] = ipts0[ipts0_num-3][1]-5;
            }else{
                //若丢失时则表明车身此时已经接近圆环的入环口，内侧丢失边线的情况下则可以手动给定一个固定的起始点作为远端边线搜索的起始点
                //固定点的坐标需要根据你图像的尺寸和摄像头高度修改
                if_lost_left_line = 1;
                inv_Lpt0_found[0] = 40;
                inv_Lpt0_found[1] = begin_y*0.85;
            }
        }
        else {
            //这是出环阶段的情况下，原本的CIRCLE_RIGHT_OUT是利用内侧边线划出去，但是R50这种小圆也是极容易丢失边线的
            //因此我选了一个比较靠近图像正中下方的一个点，这样他既不会在向上搜边线的时候碰到外环边线，而且能搜到赛道对侧的长直道，用于出环补线
            inv_Lpt0_found[0] = 80;
            inv_Lpt0_found[1] = begin_y*0.85;

        }


    }
    else if(rpts0s_num<2){
        //在非圆环且边线几乎丢失的情况下，说明近端空白，可以用一个固定的点位去向上搜索，固定点的坐标需要根据你图像的尺寸和摄像头高度修改
        if_lost_left_line = 1;
        inv_Lpt0_found[0] = 20;
        inv_Lpt0_found[1] = begin_y-5;
    }

    if (Lpt1_found) {//拐点截断处理，拐点之后的点都不要了
        rptsc1_num = rpts1s_num = Lpt1_rpts1s_id -2;
    }


    int cross_width = 4;
    far_y1 = 0, far_y2 = 0;
    int y1 = clip((int)inv_Lpt0_found[1], block_size/2 + 1, MT9V03X_H - block_size/2 - 1);
    far_x11 = clip((int)inv_Lpt0_found[0], block_size/2, MT9V03X_W - block_size/2 - 1);
    bool white_found = false;
    far_ipts0_num = sizeof(far_ipts0) / sizeof(far_ipts0[0]);

    int local_thres_left_up = 0;
    for (; y1 > block_size/2; y1--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x11, y1-1) < OSTU_thres) {
            break;
        }
    }


    for (; y1 > block_size/2; y1--) {
        local_thres_left_up = 0;
        for (int dy = -block_size/2; dy <= block_size/2; dy++) {
            for (int dx = -block_size/2; dx <= block_size/2; dx++) {
                local_thres_left_up += AT_IMAGE(&img_raw, far_x11 + dx, y1 + dy);
            }
        }
        local_thres_left_up /= block_size * block_size;
        local_thres_left_up -= clip_value;

        if (AT_IMAGE(&img_raw, far_x11 , y1 - 1 ) < local_thres_left_up
                ){
            far_y1 = y1;
            break;
        }

    }//利用自适应二值化的方式向上寻找边线

    //从far_y1，far_x11位置开始寻找远端边线
    if (far_y1 > block_size/2 && AT_IMAGE(&img_raw, far_x11, far_y1 -1) < local_thres_left_up)
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, far_x11, far_y1 , far_ipts0, &far_ipts0_num);
    else far_ipts0_num = 0;

    // 去畸变+透视变换
    for(int i=0;i<far_ipts0_num;i++)
    {
        far_rpts0[i][0] = (rot[1][0]*far_ipts0[i][1]+rot[1][1]*far_ipts0[i][0]+rot[1][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_x;
        far_rpts0[i][1] = (rot[0][0]*far_ipts0[i][1]+rot[0][1]*far_ipts0[i][0]+rot[0][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_y;

    }

    far_rpts0_num = far_ipts0_num;
    // 边线滤波
    blur_points(far_rpts0, far_rpts0_num, far_rpts0b, (int) round(line_blur_kernel));
    far_rpts0b_num = far_rpts0_num;

    // 边线等距采样
    far_rpts0s_num = sizeof(far_rpts0s) / sizeof(far_rpts0s[0]);
    resample_points(far_rpts0b, far_rpts0b_num, far_rpts0s, &far_rpts0s_num, sample_dist * pixel_per_meter);
    //far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);


    // 边线局部角度变化率
    local_angle_points(far_rpts0s, far_rpts0s_num, far_rpts0a, (int) round(angle_dist / sample_dist));
    far_rpts0a_num = far_rpts0s_num;

    // 角度变化率非极大抑制
    nms_angle(far_rpts0a, far_rpts0a_num, far_rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts0an_num = far_rpts0a_num;

    // 找远线上的L角点
    far_Lpt0_found = far_Lpt1_found = false;
    for (int i = 0; i < MIN(far_rpts0s_num, 70); i++) {
        if (far_rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
//        float conf = fabs(far_rpts0a[i]) - (fabs(far_rpts0a[im1]) + fabs(far_rpts0a[ip1])) / 2;
        conf3 = fabs(far_rpts0a[i]) - (fabs(far_rpts0a[im1]) + fabs(far_rpts0a[ip1])) / 2;
        if (50. / 180. * PI < conf3 && conf3 < 140. / 180. * PI && i < 40&&far_rpts0s[i][0]<=far_rpts0s[ip1][0]&&i>1&&far_rpts0s[i][1]>far_rpts0s[ip1][1]&&far_rpts0s[im1][0]<far_rpts0s[ip1][0]) {//为防止误判，远端的拐点角度定义域可以放的大一点，再加上拐点和前后两点的相对位置关系可以有效解决误判
            far_Lpt0_rpts0s_id = i;
            far_Lpt0_found = true;
            inv_far_Lpt0_found[0] = Cal_inv_rot_x(far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][0],far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][1]);
            inv_far_Lpt0_found[1] = Cal_inv_rot_y(far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][0],far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][1]);//逆透视计算，将俯视角下的远端拐点坐标映射回原图
            break;
        }
        if(conf3>conf3_max)conf3_max = conf3;//每次计算保存下当前计算周期中的边线最大角度值，在屏幕上显示出来准确的数据方便调整拐点的定义域
    }





}


void cross_farline_R()//左右同理
{
    if (Lpt0_found) {
        rptsc0_num = rpts0s_num = Lpt0_rpts0s_id -2;
    }

    if (Lpt1_found&&Lpt1_rpts1s_id>2&&!if_lost_right_line) {
        inv_Lpt1_found[0] = Cal_inv_rot_x(rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][0],rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][1])+5;
        inv_Lpt1_found[1] = Cal_inv_rot_y(rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][0],rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][1])-17;
        rptsc1_num = rpts1s_num = Lpt1_rpts1s_id ;
    }
    else if((circle_type== CIRCLE_RIGHT_IN||circle_type== CIRCLE_LEFT_OUT||circle_type== CIRCLE_LEFT_END)&&!garage_type){
        if(circle_type== CIRCLE_RIGHT_IN)
        {
            if(ipts1_num>12&&!if_lost_right_line){
                inv_Lpt1_found[0] = ipts1[ipts1_num-3][0]-15;
                inv_Lpt1_found[1] = ipts1[ipts1_num-3][1]-8;
            }else{
                if_lost_right_line =1;
                inv_Lpt1_found[0] = 140;
                inv_Lpt1_found[1] = begin_y*0.85;
            }
        }
        else {
            if(rpts1s_num>10){
                inv_Lpt1_found[0] = 80;
                inv_Lpt1_found[1] = 105;
            }
            else{
                inv_Lpt1_found[0] = 110;
                inv_Lpt1_found[1] = 105;
            }


        }


    }
    else if(rpts1s_num<2){
        if_lost_right_line = 1;
        inv_Lpt1_found[0] = 160;
        inv_Lpt1_found[1] = begin_y-5;
    }
    if(DisPlay_Flag&&!thres)
        {
            if(3<(inv_Lpt1_found[0]/X_zoom)&&(inv_Lpt1_found[0]/X_zoom)<101&&3<(inv_Lpt1_found[1]/Y_zoom)&&(inv_Lpt1_found[1]/Y_zoom)<64) for(int i=-2;i<3;i++)for(int j=-2;j<3;j++)lcd_drawpoint((int)(inv_Lpt1_found[0]+i)/X_zoom,(int)(inv_Lpt1_found[1]+j)/Y_zoom,RED);
        }
 int cross_width = 4;
    far_y1 = 0, far_y2 = 0;
    int y1 = clip((int)inv_Lpt1_found[1], block_size/2 + 1, MT9V03X_H - block_size/2 - 1);
    far_x11 = clip((int)inv_Lpt1_found[0], block_size/2, MT9V03X_W - block_size/2 - 1);
    bool white_found = false;
    far_ipts1_num = sizeof(far_ipts1) / sizeof(far_ipts1[0]);

    int local_thres_right_up = 0;
    for (; y1 > block_size/2; y1--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x11, y1-1) < OSTU_thres) {
            break;
        }
    }
         for (; y1 > block_size/2; y1--) {


             local_thres_right_up = 0;
             for (int dy = -block_size/2; dy <= block_size/2; dy++) {
                 for (int dx = -block_size/2; dx <= block_size/2; dx++) {
                     local_thres_right_up += AT_IMAGE(&img_raw, far_x11 + dx, y1 + dy);
                 }
             }
             local_thres_right_up /= block_size * block_size;
             local_thres_right_up -= clip_value;

             if (AT_IMAGE(&img_raw, far_x11 , y1 - 1 ) < local_thres_right_up)
             {
                 far_y1 = y1;
                 break;
             }
         }
         //从找到角点位置开始寻找
         if (far_y1 > block_size/2 && AT_IMAGE(&img_raw, far_x11, far_y1 -1) < local_thres_right_up)
        findline_righthand_adaptive(&img_raw, block_size, clip_value, far_x11, far_y1 , far_ipts1, &far_ipts1_num);
         else far_ipts1_num = 0;

    // 去畸变+透视变换
    for(int i=0;i<far_ipts1_num;i++)
    {
        far_rpts1[i][0] = (rot[1][0]*far_ipts1[i][1]+rot[1][1]*far_ipts1[i][0]+rot[1][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_x;
        far_rpts1[i][1] = (rot[0][0]*far_ipts1[i][1]+rot[0][1]*far_ipts1[i][0]+rot[0][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_y;

    }

    far_rpts1_num = far_ipts1_num;
    // 边线滤波
    blur_points(far_rpts1, far_rpts1_num, far_rpts1b, (int) round(line_blur_kernel));
    far_rpts1b_num = far_rpts1_num;

    // 边线等距采样
    far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);
    resample_points(far_rpts1b, far_rpts1b_num, far_rpts1s, &far_rpts1s_num, sample_dist * pixel_per_meter);
    //far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);


    // 边线局部角度变化率
    local_angle_points(far_rpts1s, far_rpts1s_num, far_rpts1a, (int) round(angle_dist / sample_dist));
    far_rpts1a_num = far_rpts1s_num;

    // 角度变化率非极大抑制
    nms_angle(far_rpts1a, far_rpts1a_num, far_rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts1an_num = far_rpts1a_num;

    // 找远线上的L角点


    far_Lpt1_found = far_Lpt0_found = false;
    for (int i = 0; i < MIN(far_rpts1s_num, 70); i++) {
        if (far_rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        conf4 = fabs(far_rpts1a[i]) - (fabs(far_rpts1a[im1]) + fabs(far_rpts1a[ip1])) / 2;
        if (50. / 180. * PI < conf4 && conf4 < 140. / 180. * PI&&i<40 &&far_rpts1s[i][0]>=far_rpts1s[ip1][0]&&i>1&&far_rpts1s[i][1]>=far_rpts1s[ip1][1]&&far_rpts1s[im1][0]>=far_rpts1s[ip1][0]) {
            far_Lpt1_rpts1s_id = i;
            far_Lpt1_found = true;
            inv_far_Lpt1_found[0] = Cal_inv_rot_x(far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][0],far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][1]);
            inv_far_Lpt1_found[1] = Cal_inv_rot_y(far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][0],far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][1]);
            break;
        }
        if(conf4>conf4_max)conf4_max = conf4;
    }


}



void cross_farline() {
    int cross_width = 4;
//    far_x1 = cross_width, far_x2 = img_raw.width -cross_width;
    far_y1 = 0, far_y2 = 0;
//    int x1 = img_raw.width / 2 - begin_x
    int y1 = begin_y;
    bool white_found = false;
    far_ipts0_num = sizeof(far_ipts0) / sizeof(far_ipts0[0]);

    //在begin_y向两边找黑线
//    for(;x1>cross_width*2; x1--)
//    {
//      if(AT_IMAGE(&img_raw, x1-1, y1) < low_thres) {
//        far_x1 = x1 - cross_width;
//        break;
//      }
//    }
    //全白  far_x1 = 0,从边界找
    for (; y1 > 0; y1--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x1, y1) >= thres) { white_found = true; }
        if (AT_IMAGE(&img_raw, far_x1, y1) < thres && (white_found || far_x1 == cross_width)) {
            far_y1 = y1;
            break;
        }
    }

    //从找到角点位置开始寻找
    if (AT_IMAGE(&img_raw, far_x1, far_y1 + 1) >= thres)
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, far_x1, far_y1 + 1, far_ipts0, &far_ipts0_num);
    else far_ipts0_num = 0;

    //int x2 = img_raw.width / 2 + begin_x,
    int y2 = begin_y;
    white_found = false;
    far_ipts1_num = sizeof(far_ipts1) / sizeof(far_ipts1[0]);

    //在begin_y向两边找黑线
//    for(;x2<img_raw.width-cross_width*2; x2++)
//    {
//      if(AT_IMAGE(&img_raw, x2+1, y2) < low_thres) {
//        far_x2 = x2 + cross_width;
//        break;
//      }
//    }
    //全白  far_x2 = 0,从边界找
    for (; y2 > 0; y2--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x2, y2) >= thres) { white_found = true; }
        if (AT_IMAGE(&img_raw, far_x2, y2) < thres && (white_found || far_x2 == img_raw.width - cross_width)) {
            far_y2 = y2;
            break;
        }
    }

    //从找到角点位置开始寻找
    if (AT_IMAGE(&img_raw, far_x2, far_y2 + 1) >= thres)
        findline_righthand_adaptive(&img_raw, block_size, clip_value, far_x2, far_y2 + 1, far_ipts1, &far_ipts1_num);

    else far_ipts1_num = 0;

    // 去畸变+透视变换
    for(int i=0;i<far_ipts0_num;i++)
    {
        far_rpts0[i][0] = (rot[1][0]*far_ipts0[i][1]+rot[1][1]*far_ipts0[i][0]+rot[1][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_x;
        far_rpts0[i][1] = (rot[0][0]*far_ipts0[i][1]+rot[0][1]*far_ipts0[i][0]+rot[0][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_y;

    }
    for(int i=0;i<far_ipts1_num;i++)
    {
        far_rpts1[i][0] = (rot[1][0]*far_ipts1[i][1]+rot[1][1]*far_ipts1[i][0]+rot[1][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_x;
        far_rpts1[i][1] = (rot[0][0]*far_ipts1[i][1]+rot[0][1]*far_ipts1[i][0]+rot[0][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_y;

    }
    far_rpts0_num = far_ipts0_num;
    far_rpts1_num = far_ipts1_num;

    // 边线滤波
    blur_points(far_rpts0, far_rpts0_num, far_rpts0b, (int) round(line_blur_kernel));
    far_rpts0b_num = far_rpts0_num;
    blur_points(far_rpts1, far_rpts1_num, far_rpts1b, (int) round(line_blur_kernel));
    far_rpts1b_num = far_rpts1_num;

    // 边线等距采样
    far_rpts0s_num = sizeof(far_rpts0s) / sizeof(far_rpts0s[0]);
    resample_points(far_rpts0b, far_rpts0b_num, far_rpts0s, &far_rpts0s_num, sample_dist * pixel_per_meter);
    far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);
    resample_points(far_rpts1b, far_rpts1b_num, far_rpts1s, &far_rpts1s_num, sample_dist * pixel_per_meter);


    // 边线局部角度变化率
    local_angle_points(far_rpts0s, far_rpts0s_num, far_rpts0a, (int) round(angle_dist / sample_dist));
    far_rpts0a_num = far_rpts0s_num;
    local_angle_points(far_rpts1s, far_rpts1s_num, far_rpts1a, (int) round(angle_dist / sample_dist));
    far_rpts1a_num = far_rpts1s_num;

    // 角度变化率非极大抑制
    nms_angle(far_rpts0a, far_rpts0a_num, far_rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts0an_num = far_rpts0a_num;
    nms_angle(far_rpts1a, far_rpts1a_num, far_rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts1an_num = far_rpts1a_num;

    // 找远线上的L角点

    far_Lpt0_found = far_Lpt1_found = false;
    for (int i = 0; i < MIN(far_rpts0s_num, 40); i++) {
        if (far_rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        float conf = fabs(far_rpts0a[i]) - (fabs(far_rpts0a[im1]) + fabs(far_rpts0a[ip1])) / 2;
        if (70. / 180. * PI < conf && conf < 110. / 180. * PI && i < 100) {
            far_Lpt0_rpts0s_id = i;
            far_Lpt0_found = true;
            break;
        }
    }
    for (int i = 0; i < MIN(far_rpts1s_num, 70); i++) {
        if (far_rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        float conf = fabs(far_rpts1a[i]) - (fabs(far_rpts1a[im1]) + fabs(far_rpts1a[ip1])) / 2;

        if (70. / 180. * PI < conf && conf < 140. / 180. * PI && i < 100) {
            far_Lpt1_rpts1s_id = i;
            far_Lpt1_found = true;
            break;
        }
    }

#if If_DisPlay
    lcd_showint8(70 ,6,far_Lpt0_found);
    lcd_showint8(105,6,far_Lpt1_found);
#endif
}


void cross_farline_half()
{
    int cross_width = 4;
//    far_x1 = cross_width, far_x2 = img_raw.width -cross_width;
    far_y1 = 0, far_y2 = 0;
//    int x1 = img_raw.width / 2 - begin_x
    int y1 = begin_y;
    bool white_found = false;
    far_ipts0_num = sizeof(far_ipts0) / sizeof(far_ipts0[0]);

    //在begin_y向两边找黑线
//    for(;x1>cross_width*2; x1--)
//    {
//      if(AT_IMAGE(&img_raw, x1-1, y1) < low_thres) {
//        far_x1 = x1 - cross_width;
//        break;
//      }
//    }
    //全白  far_x1 = 0,从边界找
    for (; y1 > 0; y1--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x1, y1) >= thres) { white_found = true; }
        if (AT_IMAGE(&img_raw, far_x1, y1) < thres && (white_found || far_x1 == cross_width)) {
            far_y1 = y1;
            break;
        }
    }

    //从找到角点位置开始寻找
    if (AT_IMAGE(&img_raw, far_x1, far_y1 + 1) >= thres)
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, far_x1, far_y1 + 1, far_ipts0, &far_ipts0_num);
    else far_ipts0_num = 0;

    //int x2 = img_raw.width / 2 + begin_x,
    int y2 = begin_y;
    white_found = false;
    far_ipts1_num = sizeof(far_ipts1) / sizeof(far_ipts1[0]);

    //在begin_y向两边找黑线
//    for(;x2<img_raw.width-cross_width*2; x2++)
//    {
//      if(AT_IMAGE(&img_raw, x2+1, y2) < low_thres) {
//        far_x2 = x2 + cross_width;
//        break;
//      }
//    }
    //全白  far_x2 = 0,从边界找
    for (; y2 > 0; y2--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x2, y2) >= thres) { white_found = true; }
        if (AT_IMAGE(&img_raw, far_x2, y2) < thres && (white_found || far_x2 == img_raw.width - cross_width)) {
            far_y2 = y2;
            break;
        }
    }

    //从找到角点位置开始寻找
    if (AT_IMAGE(&img_raw, far_x2, far_y2 + 1) >= thres)
        findline_righthand_adaptive(&img_raw, block_size, clip_value, far_x2, far_y2 + 1, far_ipts1, &far_ipts1_num);

    else far_ipts1_num = 0;

    // 去畸变+透视变换
    for(int i=0;i<far_ipts0_num;i++)
    {
        far_rpts0[i][0] = (rot[1][0]*far_ipts0[i][1]+rot[1][1]*far_ipts0[i][0]+rot[1][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_x;
        far_rpts0[i][1] = (rot[0][0]*far_ipts0[i][1]+rot[0][1]*far_ipts0[i][0]+rot[0][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_y;

    }
    for(int i=0;i<far_ipts1_num;i++)
    {
        far_rpts1[i][0] = (rot[1][0]*far_ipts1[i][1]+rot[1][1]*far_ipts1[i][0]+rot[1][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_x;
        far_rpts1[i][1] = (rot[0][0]*far_ipts1[i][1]+rot[0][1]*far_ipts1[i][0]+rot[0][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_y;

    }
    far_rpts0_num = far_ipts0_num;
    far_rpts1_num = far_ipts1_num;

    // 边线滤波
    blur_points(far_rpts0, far_rpts0_num, far_rpts0b, (int) round(line_blur_kernel));
    far_rpts0b_num = far_rpts0_num;
    blur_points(far_rpts1, far_rpts1_num, far_rpts1b, (int) round(line_blur_kernel));
    far_rpts1b_num = far_rpts1_num;

    // 边线等距采样
    far_rpts0s_num = sizeof(far_rpts0s) / sizeof(far_rpts0s[0]);
    resample_points(far_rpts0b, far_rpts0b_num, far_rpts0s, &far_rpts0s_num, sample_dist * pixel_per_meter);
    far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);
    resample_points(far_rpts1b, far_rpts1b_num, far_rpts1s, &far_rpts1s_num, sample_dist * pixel_per_meter);


    // 边线局部角度变化率
    local_angle_points(far_rpts0s, far_rpts0s_num, far_rpts0a, (int) round(angle_dist / sample_dist));
    far_rpts0a_num = far_rpts0s_num;
    local_angle_points(far_rpts1s, far_rpts1s_num, far_rpts1a, (int) round(angle_dist / sample_dist));
    far_rpts1a_num = far_rpts1s_num;

    // 角度变化率非极大抑制
    nms_angle(far_rpts0a, far_rpts0a_num, far_rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts0an_num = far_rpts0a_num;
    nms_angle(far_rpts1a, far_rpts1a_num, far_rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts1an_num = far_rpts1a_num;

    // 找远线上的L角点
    far_Lpt0_found = far_Lpt1_found = false;
    for (int i = 0; i < MIN(far_rpts0s_num, 40); i++) {
        if (far_rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        float conf = fabs(far_rpts0a[i]) - (fabs(far_rpts0a[im1]) + fabs(far_rpts0a[ip1])) / 2;
        if (70. / 180. * PI < conf && conf < 110. / 180. * PI && i < 100) {
            far_Lpt0_rpts0s_id = i;
            far_Lpt0_found = true;
            break;
        }
    }
    for (int i = 0; i < MIN(far_rpts1s_num, 40); i++) {
        if (far_rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        float conf = fabs(far_rpts1a[i]) - (fabs(far_rpts1a[im1]) + fabs(far_rpts1a[ip1])) / 2;

        if (70. / 180. * PI < conf && conf < 140. / 180. * PI && i < 100) {
            far_Lpt1_rpts1s_id = i;
            far_Lpt1_found = true;
            break;
        }
    }
#if If_DisPlay
    lcd_showint8(70 ,6,far_Lpt0_found);
    lcd_showint8(105,6,far_Lpt1_found);
#endif
}

