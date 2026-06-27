/* =====================================================================
 *  环岛检测模块接口（round）
 *
 *  状态机：NONE → BEGIN → IN → END → NONE
 *
 *  检测依据：check_round_L/R 用奇偶计数法区分环岛与车库
 *  当前状态：废弃（ATG_ENABLE_ROUND=0），代码保留供参考
 * ===================================================================== */
#ifndef ROUND_H
#define ROUND_H
#include "headfile.h"

/* 环岛状态枚举 */
enum round_type_e {
    ROUND_NONE = 0,         /* 无环岛 */
    ROUND_LEFT_BEGIN,       /* 左环岛入口检测 */
    ROUND_RIGHT_BEGIN,      /* 右环岛入口检测 */
    ROUND_LEFT_IN,          /* 左环岛内部 */
    ROUND_RIGHT_IN,         /* 右环岛内部 */
    ROUND_LEFT_END,         /* 左环岛出口 */
    ROUND_RIGHT_END         /* 右环岛出口 */
};

/* ================= 接口函数 ================= */

/* 环岛检测入口 */
void check_round();

/* 左环岛检测（奇偶计数法） */
void check_round_L();

/* 右环岛检测（奇偶计数法） */
void check_round_R();

/* 环岛主流程 */
void run_round();

/* ================= 全局状态 ================= */

/* 当前环岛状态 */
extern enum round_type_e round_type;

/* 环岛行驶速度 */
extern int16 round_speed;

/* 环岛瞄准距离 */
extern float round_aim_distance;

/* 左右环岛经过计数 */
extern int16 left_round_cnt, right_round_cnt;

#endif /* ROUND_H */
