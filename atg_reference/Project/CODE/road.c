/* =====================================================================
 *  道路类型检测
 *
 *  根据边线角度和引导线偏移判断当前道路类型，用于速度控制和路径规划。
 *  只在非圆环、非坡道时工作。
 *
 *  道路类型状态机：
 *
 *    ROAD_NORMAL ──(角度小)──► LONG_STRAIGHT
 *         │                        │
 *         │                        ▼
 *         │                   ROAD_NORMAL ◄──(角度小)
 *         │                        │
 *         ▼                        ▼
 *    CURVE_S_CURVE ──(线短)──► CURVE_NEAR ──(角度大)──► CURVE_IN
 *         │                                                │
 *         │                                                ▼
 *         │                              CURVE_CURVE ◄──(角度中+历史)
 *         │                                   │
 *         │                                   ▼
 *         └─────────────────────────────► CURVE_OUT ──(角度小)──► ROAD_NORMAL
 *
 *  判断依据：
 *    pure_angle      — 当前边线角度（弧度）
 *    pure_angle_up   — 上一帧边线角度
 *    pure_angle_up_up — 上上帧边线角度
 *    Guide_up_up      — 上上帧引导线偏移
 *    rpts0/1s_num     — 左/右线点数
 * ===================================================================== */
#include "road.h"

enum road_type_e  road_type;                           /* 当前道路类型 */
enum speed_type_e speed_type;                          /* 当前速度模式 */

/* 道路类型检测：每帧调用，根据角度和偏移判断道路类型 */
void check_road(void)
{
    /* 只在非圆环、非坡道时工作 */
    if(!circle_type&&!ramp_type)
    {
        /* 长直道：连续两帧角度都很小 */
        if(ABS(pure_angle_up_up)<0.75&&ABS(pure_angle_up)<0.75&&(road_type == ROAD_NORMAL||road_type == CURVE_S_CURVE))
        {
            road_type = LONG_STRAIGHT;
        }
        /* 从长直道回到正常：角度变大或偏移明显 */
        else if(ABS(pure_angle)<2.0&&ABS(Guide_up_up)>15&&(road_type ==LONG_STRAIGHT||road_type == SHORT_STRAIGHT))
        {
            road_type = ROAD_NORMAL;
        }
        /* 进入弯道：角度中等，无其他元素干扰 */
        else if(2.0<ABS(pure_angle)&&ABS(pure_angle)<5.5&&!ramp_type&&!circle_type&&!cross_type&&!round_type&&!garage_type&&(road_type ==CURVE_NONE||road_type == ROAD_NORMAL))
        {
            if(rpts0s_num<40||rpts1s_num<40)road_type =CURVE_NEAR;  /* 线短 → 近弯 */
            else road_type = CURVE_S_CURVE;                          /* 线长 → S弯 */
        }
        /* 进入急弯：角度大 */
        else if(ABS(pure_angle)>=5.5&&(road_type == CURVE_NEAR||road_type == CURVE_CURVE))
        {
            road_type = CURVE_IN;
        }
        /* 急弯内部：角度变小时判断是继续弯还是出弯 */
        else if(2.0<ABS(pure_angle)&&ABS(pure_angle)<5.5&&road_type == CURVE_IN)
        {
            if(ABS(pure_angle)<2.2){
                /* 历史角度大或偏移大 → 还在弯里 */
                if(pure_angle_up_up>4.2||ABS(Guide_up_up)>45)road_type = CURVE_CURVE;
                else                    road_type = CURVE_OUT;       /* 否则 → 出弯 */
            }
        }
        /* 出弯完成：角度很小 → 回到正常 */
        else if(ABS(pure_angle)<1.0&&road_type == CURVE_OUT)
        {
            road_type = ROAD_NORMAL;
        }
        /* S弯转急弯：线变短且偏移大 */
        else if(road_type == CURVE_S_CURVE&&rpts0s_num<55&&rpts1s_num<55&&ABS(Guide_up_up)>45){
            road_type = CURVE_IN;
        }

    }
}
