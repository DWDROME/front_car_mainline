/* =====================================================================
 *  环岛检测与通过
 *
 *  环岛结构：
 *
 *         直道
 *           │
 *     ┌─────┴─────╥─────────┐
 *     │           ║         │
 *  直道入口    环岛圆弧    出口直道
 *     │         ═══         │
 *     └─────────╨───────────┘
 *           │
 *         直道
 *
 *  从直道进入，绕环岛圆弧行驶，选一条直道出去。
 *
 *  状态机：
 *    NONE ──(L角点+对侧直道)──► BEGIN ──(线先丢后有)──► IN ──(L角点)──► END ──(距离+线恢复)──► NONE
 *
 *  检测逻辑：
 *    本侧有 L 角点 + 对侧是直道 → 可能是环岛
 *    调用 cross_farline_L/R 寻找远端 L 角点：
 *      - 找到远端 L → 环岛（奇数次）或 车库（偶数次）
 *      - 没找到 → 不是环岛
 * ===================================================================== */
#include "round.h"
#include "headfile.h"

enum round_type_e  round_type = ROUND_NONE;           /* 当前环岛状态 */
float round_aim_distance;                              /* 环岛内前瞻距离 */

static void check_round_L(void);
static void check_round_R(void);

/* 环岛入口检测：本侧有 L 角点 + 对侧是直道 */
void check_round(void)
{
        /* 左侧 L 角点 + 右侧直道 → 检查是否是左环岛 */
        if(round_type == ROUND_NONE && Lpt0_found  && is_straight1&&Lpt0_rpts0s_id<30) check_round_L();
        /* 右侧 L 角点 + 左侧直道 → 检查是否是右环岛 */
        if(round_type == ROUND_NONE && Lpt1_found  && is_straight0&&Lpt1_rpts1s_id<30) check_round_R();

}

/* 环岛状态机主流程 */
void run_round(void)
{
    /* --- 右环岛 BEGIN：进入环岛入口 ---
     * 跟左线（内侧），等右线先丢后有 → 进入 IN */
    if(round_type==ROUND_RIGHT_BEGIN) {
        track_type = TRACK_LEFT;
        circle_type = CIRCLE_NONE;
        cross_type = CROSS_NONE;

        /* 右线丢失计数 */
        if (rpts1s_num < 0.2 / sample_dist) { none_right_line++; }
        /* 右线恢复且之前丢过 → 进入 IN */
        if (rpts1s_num > (1.0 / sample_dist-40 )&& none_right_line > 2) {
            have_right_line++;
            if (have_right_line > 1) {
                round_type = ROUND_RIGHT_IN;
                none_right_line = 0;
                have_right_line = 0;
            }
        }

    }
    /* --- 右环岛 IN：环岛内部 ---
     * 跟左线，等左侧出现 L 角点（出口位置）→ 进入 END */
    else if(round_type==ROUND_RIGHT_IN)
    {
        track_type = TRACK_LEFT;
        if(Lpt0_found&&Lpt0_rpts0s_id<rpts0s_num*0.8)
        {
            round_type=ROUND_RIGHT_END;
            aim_distance = AIM_DISTENCE;
        }

    }
    /* --- 右环岛 END：驶出环岛 ---
     * 跟左线，截断到 L 角点位置，等距离+线恢复 → 退出 */
    else if(round_type==ROUND_RIGHT_END)
    {
        aim_distance = round_aim_distance;
        track_type = TRACK_LEFT;
        Count_dis_Flag=1;
        /* 截断到 L 角点位置 */
        if(Lpt0_found){
                rpts0s_num = clip(Lpt0_rpts0s_id+8,0,rpts0s_num);
                rptsc0_num = clip(Lpt0_rpts0s_id+8,0,rpts0s_num);
        }
        /* 右线丢失计数 */
        if (rpts1s_num < 0.2 / sample_dist)     { none_right_line++; }
        /* 距离够 + 右线恢复 → 退出环岛 */
        if(total_distence>=3000&&none_right_line>2&&rpts1s_num>65){
            track_type = TRACK_RIGHT;
            Count_dis_Flag=0;
            round_type= ROUND_NONE;
            circle_type = CIRCLE_NONE;
            cross_type = CROSS_NONE;
            yroad_type=YROAD_NONE;
            garage_type = GARAGE_NONE;
            ramp_type=RAMP_NONE;
            begin_y=BEGIN_Y;
            aim_distance = AIM_DISTENCE;
            none_left_line= 0 ;
            if_lost_right_line =0;
            if_lost_left_line = 0;
            none_right_line = 0;
            have_right_line = 0;
            none_left_line = 0;
            have_left_line = 0;
        }

    }
    /* --- 左环岛 BEGIN：与右环岛对称 --- */
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
    /* --- 左环岛 IN --- */
    else if(round_type==ROUND_LEFT_IN)
    {
        track_type = TRACK_RIGHT;
        if(Lpt1_found&&Lpt1_rpts1s_id<rpts1s_num*0.8)
        {
            round_type=ROUND_LEFT_END;
            aim_distance = AIM_DISTENCE;
        }
    }
    /* --- 左环岛 END --- */
    else if(round_type==ROUND_LEFT_END)
    {
        aim_distance = round_aim_distance;
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
            none_left_line= 0 ;
            if_lost_right_line =0;
            if_lost_left_line = 0;
        }

    }
}

/* 左环岛/车库联合检测：
 * 调用 cross_farline_L 寻找远端 L 角点。
 * 奇数次 → 环岛，偶数次 → 车库。 */
static void check_round_L(void)
{
    cross_farline_L();
    if(far_Lpt0_found) {
        Count_Garage_num++;
        if(Count_Garage_num%2 ==0){
            if(Count_Garage_num==4){
                garage_type = GARAGE_IN_LEFT;
            }
            else if(Count_Garage_num==2){
                garage_type = GARAGE_FOUND_LEFT;
                if_lost_left_line = 0;
            }
        }
        else {
            round_type = ROUND_LEFT_BEGIN;
            if_lost_left_line = 0;
        }

    }

}

static void check_round_R(void)
{
    cross_farline_R();

    if(far_Lpt1_found) {
        Count_Garage_num++;
        if(Count_Garage_num%2 ==0){
            if(Count_Garage_num==4){
                garage_type = GARAGE_IN_RIGHT;
            }
            else if(Count_Garage_num==2)garage_type = GARAGE_FOUND_RIGHT;
            if_lost_right_line = 0;
        }
        else {
            round_type = ROUND_RIGHT_BEGIN;
            if_lost_right_line = 0;
        }




    }


}
