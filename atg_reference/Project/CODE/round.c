#include "round.h"
#define PI               3.14159265358979f
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)
enum round_type_e  round_type = ROUND_NONE;
float round_aim_distance;
int16 round_speed;
int16 left_round_cnt,right_round_cnt;
void check_round()
{

        if(round_type == ROUND_NONE && Lpt0_found  && is_straight1&&Lpt0_rpts0s_id<30) check_round_L(); //当一侧找到90°拐点，另一侧为长直道、且90°的拐点足够近的时候（通过Lpt0_rpts0s_id判别拐点在远端还是近端）开始判断回环的条件
        if(round_type == ROUND_NONE && Lpt1_found  && is_straight0&&Lpt1_rpts1s_id<30) check_round_R();


}

void run_round()
{

    if(round_type==ROUND_RIGHT_BEGIN) {
//        cross_farline_R();
        track_type = TRACK_LEFT;
        circle_type = CIRCLE_NONE;
        cross_type = CROSS_NONE;

        if (rpts1s_num < 0.2 / sample_dist) { none_right_line++; }
        if (rpts1s_num > (1.0 / sample_dist-40 )&& none_right_line > 2) {
            have_right_line++;
            if (have_right_line > 1) {
                round_type = ROUND_RIGHT_IN;
                none_right_line = 0;
                have_right_line = 0;
            }
        }


    }
    else if(round_type==ROUND_RIGHT_IN)
    {

        track_type = TRACK_LEFT;
        if(Lpt0_found&&Lpt0_rpts0s_id<rpts0s_num*0.8)
        {
            round_type=ROUND_RIGHT_END;
            if_clean_pid = 1;
            aim_distance = AIM_DISTENCE;
        }



    }
    else if(round_type==ROUND_RIGHT_END)
    {
        //begin_y=MT9V03X_H*0.7;
        aim_distance = round_aim_distance;
        track_type = TRACK_LEFT;
        Count_dis_Flag=1;
        if(Lpt0_found){
                rpts0s_num = clip(Lpt0_rpts0s_id+8,0,rpts0s_num);
                rptsc0_num = clip(Lpt0_rpts0s_id+8,0,rpts0s_num);
        }
        if (rpts1s_num < 0.2 / sample_dist)     { none_right_line++; }
        if(total_distence>=3000&&none_right_line>2&&rpts1s_num>65){
            track_type = TRACK_RIGHT;
            Count_dis_Flag=0;
            round_type= ROUND_NONE;
            circle_type = CIRCLE_NONE;
            //circle_type = CIRCLE_LEFT_BEGIN;
            cross_type = CROSS_NONE;
            yroad_type=YROAD_NONE;
            garage_type = GARAGE_NONE;
            ramp_type=RAMP_NONE;
            begin_y=BEGIN_Y;
            aim_distance = AIM_DISTENCE;
            //yroad_cnt++;
            broadcast_flag=1;
            none_left_line= 0 ;
            if_lost_right_line =0;
            if_lost_left_line = 0;
            none_right_line = 0;
            have_right_line = 0;
            none_left_line = 0;
            have_left_line = 0;
            right_round_cnt++;
        }

    }
    else if(round_type==ROUND_LEFT_BEGIN)
    {

        track_type = TRACK_RIGHT;
        circle_type = CIRCLE_NONE;
        cross_type = CROSS_NONE;

        if (rpts0s_num < 0.2 / sample_dist) { none_left_line++; }
        if (rpts0s_num > (1.0 / sample_dist-40 )&& none_left_line > 2) {
            have_left_line++;
            if (have_left_line > 1) {
                round_type = ROUND_LEFT_IN;
                none_left_line = 0;
                have_left_line = 0;
            }
        }
    }
    else if(round_type==ROUND_LEFT_IN)
    {
        track_type = TRACK_RIGHT;
        if(Lpt1_found&&Lpt1_rpts1s_id<rpts1s_num*0.8)
        {
            round_type=ROUND_LEFT_END;
            if_clean_pid = 1;
            aim_distance = AIM_DISTENCE;
        }
    }
    else if(round_type==ROUND_LEFT_END)
    {
        aim_distance = round_aim_distance;
        //begin_y=MT9V03X_H*0.75;
        track_type = TRACK_RIGHT;
        Count_dis_Flag=1;
        if (rpts0s_num < 0.2 / sample_dist)     { none_left_line++; }
        if(Lpt1_found){
                rpts1s_num = clip(Lpt1_rpts1s_id+8,0,rpts1s_num);
                rptsc1_num = clip(Lpt1_rpts1s_id+8,0,rpts1s_num);
        }
        if(total_distence>=3000&&none_left_line>2&&rpts0s_num>65){
            track_type = TRACK_LEFT;
            Count_dis_Flag=0;
            round_type= ROUND_NONE;
            circle_type = CIRCLE_NONE;
            cross_type = CROSS_NONE;
            yroad_type=YROAD_NONE;
            garage_type = GARAGE_NONE;
            ramp_type=RAMP_NONE;
            begin_y=BEGIN_Y;
            aim_distance = AIM_DISTENCE;
            yroad_cnt++;
            broadcast_flag=1;
            none_left_line= 0 ;
            if_lost_right_line =0;
            if_lost_left_line = 0;
            left_round_cnt++;
        }

    }


    //lcd_showstr(1,1,"round_right");
}

void check_round_L()
{
/*
 * cross_farline_L，和cross_farline_L是后续元素操作中找远处边线非常有效的函数
 * 当进入check_round_L时，说明已经找到了拐点和长直道，这个时候开启cross_farline_L去寻找拐点所在边线上方远端的线
 *若找到far_Lpt0_found则说明一侧同时存在上下两个90°拐点，再加上另外一侧边线的长直道的判别条件就满足了车库的边线判断条件（车库在经过时的摄像头里是不是一边是长直道，另一侧是上下两个90°拐点的样子？）
 * 由于取消了回环元素，则出现上述角点和边线的情况下必然是车库的判断条件，则直接跳入GARAGE_FOUND_LEFT或GARAGE_FOUND_RIGHT
 * 通过经过车库的计数以及发车的方向来决定入库的时间，循环赛道的话没有三岔路口第二次看到车库就该GARAGE_IN_LEFT或者GARAGE_IN_RIGHT
 * 和round_type相关的就可以不用看了，没有这个元素了
 * check_round_R同理
 * */
    cross_farline_L();
    if(far_Lpt0_found) {
        Count_Garage_num++;
        if(Count_Garage_num%2 ==0){
            if(Count_Garage_num==4){
                garage_type = GARAGE_IN_LEFT;
                if_clean_pid = 1;
            }
            else if(Count_Garage_num==2){
                garage_type = GARAGE_FOUND_LEFT;
                if_lost_left_line = 0;
            }
            //round_type = ROUND_LEFT_BEGIN;
        }
        else {
            round_type = ROUND_LEFT_BEGIN;
            if_lost_left_line = 0;
            if_clean_pid = 1;
        }

    }

}

void check_round_R()
{
    cross_farline_R();

    if(far_Lpt1_found) {
        Count_Garage_num++;
        if(Count_Garage_num%2 ==0){
            if(Count_Garage_num==4){
                garage_type = GARAGE_IN_RIGHT;
                if_clean_pid = 1;
            }
            else if(Count_Garage_num==2)garage_type = GARAGE_FOUND_RIGHT;
            if_lost_right_line = 0;
            //round_type = ROUND_RIGHT_BEGIN;
        }
        else {
            round_type = ROUND_RIGHT_BEGIN;
            if_lost_right_line = 0;
            if_clean_pid = 1;
        }




    }


}
