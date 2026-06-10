#include "Ramp.h"
enum ramp_type_e  ramp_type;
int16 Ramp_Count;
int ramp_numb;
int16 Ramp_speed;

void Check_ramp()
//我的想法是，检测两侧边线的偏差都控制在一定范围内，编码器累计距离防止误判，以及测距的条件来判定是否接近坡道，但18届中还存在障碍物，和坡道是否会发生误判是一个值得探讨的问题：）
{
    if((TFmini_Plus_Dis<=200&&TFmini_Plus_Dis>0&&TFmini_Plus_Strong>120&&is_straight1&&is_straight0&&ramp_type==RAMP_NONE&&Up_Error>-25&&Up_Error<25&&rpts0s_num>50&&rpts1s_num>40&&conf1<18&&conf1>-18&&conf2>-18&&conf2<18)||(TFmini_Plus_Dis<=50&&TFmini_Plus_Dis>0&&TFmini_Plus_Strong>100))//&&rpts0s_num>50&&rpts1s_num>50
    {

        Clean_Time_count_flag=1;
        if(Ramp_total_distence>900||(TFmini_Plus_Dis<=50&&TFmini_Plus_Dis>0&&TFmini_Plus_Strong>100))//
        {
            Clean_Time_count_flag = 0;
            ramp_type=RAMP_NEAR;
            Ramp_Count=0;
        }

    }
    if(Clean_Time_count>3500&&ramp_type==RAMP_NONE||TFmini_Plus_Dis>450)//若误判则清除标志位
    {
        Clean_Time_count_flag = 0;

    }

}
void Run_Ramp()
{
    //强烈建议18届在坡道阶段使用图像和测距判别但用电磁导航！
    if(ramp_type==RAMP_NEAR)
    {
        //第一个阶段在接近坡道，刚刚上坡时，测距突然变远，或者测距信号强度非常弱，则说明看到天花板或者超出测距范围了，再加上编码器累计，可以跳转到上坡阶段
        Count_dis_Flag = 1;
        LAimSpeed = Ramp_speed;
        RAimSpeed = Ramp_speed;
        aim_distance = 0.35;
        if(TFmini_Plus_Dis>=800||(TFmini_Plus_Dis==0&&TFmini_Plus_Strong<250)||total_distence>3500){
            Ramp_Count++;
            if(Ramp_Count>=3)
            {
                Ramp_Count = 0;
                ramp_type=RAMP_UP;
                Count_dis_Flag = 0;
            }

        }
    }
    else if(ramp_type==RAMP_UP)
    {
        Count_dis_Flag  = 1;
        LAimSpeed = Ramp_speed-40;//0
        RAimSpeed = Ramp_speed-40;//
        aim_distance = 0.35;
        if(TFmini_Plus_Dis<180&&TFmini_Plus_Strong>150||total_distence>=3000)
        {
            //上坡转下坡，测距距离小于一定距离，编码器记录长度，或编码器足够长强制跳转标志位
            LAimSpeed = 175;
            RAimSpeed = 175;
            Ramp_Count++;
            if(Ramp_Count>=4)
            {
                Ramp_Count = 0;
                ramp_type=RAMP_DOWN;
                Count_dis_Flag=0;
            }

        }
    }
    else if(ramp_type==RAMP_DOWN)
    {
        //begin_y=MT9V03X_H-15;
        //LAimSpeed = AimSpeed-20;
        //RAimSpeed = AimSpeed-20;
        aim_distance = 0.35;
        Count_dis_Flag=1;
        if(TFmini_Plus_Dis>210)//||(TFmini_Plus_Dis==0&&TFmini_Plus_Strong<150)
        {
            SetSpeed = AimSpeed;
            Ramp_Count++;

        }
        if(Ramp_Count>=6||total_distence>=1500)//&&total_distence>=500
            {
            //长度大于一定距离，或编码器强制清除离开坡道
                Ramp_Count = 0;
                begin_y=BEGIN_Y;
                road_type = ROAD_NORMAL;
                cross_type = CROSS_NONE;
                circle_type= CIRCLE_NONE;
                yroad_type=YROAD_NONE;
                round_type=ROUND_NONE;
                garage_type = GARAGE_NONE;
                aim_distance = AIM_DISTENCE;
                Count_dis_Flag=0;
                ramp_type=RAMP_NONE;
                broadcast_flag=1;
                ramp_numb ++;
            }

    }

}
