/* =====================================================================
 *  环岛检测模块接口（round）
 *
 *  状态机：NONE → BEGIN → IN → END → NONE
 *
 *  检测依据：check_round_L/R 用奇偶计数法区分环岛与车库
 *  当前状态：默认关闭（ATG_ENABLE_ROUND=0），需要时由 vision_step.c 统一启用
 * ===================================================================== */
#ifndef ROUND_H
#define ROUND_H

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
void check_round(void);

/* 环岛主流程 */
void run_round(void);

/* ================= 全局状态 ================= */

/* 当前环岛状态 */
extern enum round_type_e round_type;

/* 环岛瞄准距离 */
extern float round_aim_distance;

#endif /* ROUND_H */
