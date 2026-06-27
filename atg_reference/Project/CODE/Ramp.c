/* =====================================================================
 *  坡道检测与通过
 *
 *  整体流程：
 *    NONE ──(激光+距离)──► NEAR ──(激光远)──► UP ──(激光近)──► DOWN ──(激光远)──► NONE
 *
 *  检测依据：
 *    - 激光测距仪（TFmini_Plus）：距离和信号强度
 *    - 边线状态：is_straight0/1（两侧都是直道）
 *    - 偏移量：Up_Error 在合理范围内
 *    - 角度：conf1/conf2 在合理范围内
 *    - 累计距离：Ramp_total_distence > 900 确认进入
 *
 *  各阶段任务：
 *    NEAR：接近坡道，减速，等待激光信号变化确认
 *    UP：上坡，降低速度，等待激光检测到坡顶
 *    DOWN：下坡，等待激光检测到坡底，恢复状态
 * ===================================================================== */
#include "Ramp.h"

enum ramp_type_e  ramp_type;                           /* 当前坡道状态 */
int16 Ramp_Count;                                      /* 状态稳定计数 */
int ramp_numb;                                         /* 累计通过的坡道数 */
int16 Ramp_speed;                                      /* 坡道行驶速度 */

/* 坡道检测：每帧调用，激光+边线状态联合判断 */
void Check_ramp()
{
    /* 检测条件：
     *   激光距离 200mm 内 + 信号强 + 两侧直道 + 偏移小 + 角度小
     *   或者激光距离 50mm 内（极近距离，强制进入） */
    if((TFmini_Plus_Dis<=200&&TFmini_Plus_Dis>0&&TFmini_Plus_Strong>120&&is_straight1&&is_straight0&&ramp_type==RAMP_NONE&&Up_Error>-25&&Up_Error<25&&rpts0s_num>50&&rpts1s_num>40&&conf1<18&&conf1>-18&&conf2>-18&&conf2<18)||(TFmini_Plus_Dis<=50&&TFmini_Plus_Dis>0&&TFmini_Plus_Strong>100))
    {
        Clean_Time_count_flag=1;
        /* 累计距离 > 900 或极近距离 → 确认进入坡道 */
        if(Ramp_total_distence>900||(TFmini_Plus_Dis<=50&&TFmini_Plus_Dis>0&&TFmini_Plus_Strong>100))
        {
            Clean_Time_count_flag = 0;
            ramp_type=RAMP_NEAR;
            Ramp_Count=0;
        }

    }
    /* 超时或激光太远 → 重置检测标志 */
    if(Clean_Time_count>3500&&ramp_type==RAMP_NONE||TFmini_Plus_Dis>450)
    {
        Clean_Time_count_flag = 0;
    }

}

/* 坡道通过状态机 */
void Run_Ramp()
{
    /* --- NEAR：接近坡道 ---
     * 减速，等激光信号变化确认：
     *   激光突然变远（≥800）或信号弱 → 上坡了
     *   累计距离 > 3500 → 也认为上坡 */
    if(ramp_type==RAMP_NEAR)
    {
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
    /* --- UP：上坡 ---
     * 降低速度，等激光检测到坡顶（距离变近+信号强） */
    else if(ramp_type==RAMP_UP)
    {
        Count_dis_Flag  = 1;
        LAimSpeed = Ramp_speed-40;
        RAimSpeed = Ramp_speed-40;
        aim_distance = 0.35;
        if(TFmini_Plus_Dis<180&&TFmini_Plus_Strong>150||total_distence>=3000)
        {
            /* 检测到坡顶，准备下坡 */
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
    /* --- DOWN：下坡 ---
     * 等激光检测到坡底（距离变远），恢复状态 */
    else if(ramp_type==RAMP_DOWN)
    {
        aim_distance = 0.35;
        Count_dis_Flag=1;
        if(TFmini_Plus_Dis>210)
        {
            SetSpeed = AimSpeed;
            Ramp_Count++;

        }
        /* 稳定计数足够或距离够 → 退出坡道 */
        if(Ramp_Count>=6||total_distence>=1500)
            {
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
                ramp_numb ++;
            }

    }

}
