/* =====================================================================
 *  坡道检测模块接口（Ramp）
 *
 *  状态机：NONE → NEAR → UP → DOWN → END → NONE
 *
 *  检测依据：激光测距 + 边线状态
 *  当前状态：禁用（ATG_ENABLE_RAMP=0）
 * ===================================================================== */
#ifndef _RAMP_H_
#define _RAMP_H_
#include "headfile.h"

/* 坡道状态枚举 */
enum ramp_type_e {
    RAMP_NONE,      /* 无坡道 */
    RAMP_NEAR,      /* 接近坡道 */
    RAMP_UP,        /* 上坡 */
    RAMP_DOWN,      /* 下坡 */
    RAMP_END        /* 坡道结束 */
};

/* ================= 接口函数 ================= */

/* 坡道检测入口 */
void Check_ramp();

/* 坡道主流程 */
void Run_Ramp();

/* ================= 全局状态 ================= */

extern int16 Ramp_speed;            /* 坡道行驶速度 */
extern int16 Ramp_Count;            /* 坡道计数 */
extern enum ramp_type_e ramp_type;  /* 当前坡道状态 */
extern int ramp_numb;

#endif /* _RAMP_H_ */
