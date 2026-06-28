/* =====================================================================
 *  Y 路检测模块接口（yroad）
 *
 *  状态机：NONE → FOUND → NEAR → LEFT/RIGHT_RUN → LEFT/RIGHT_OUT → NONE
 *
 *  检测依据：Ypt0/Ypt1_found（Y 形角点）
 *  当前状态：默认关闭（ATG_ENABLE_YROAD=0），需要时由 vision_step.c 统一启用
 * ===================================================================== */
#ifndef YROAD_H
#define YROAD_H

#include <stdint.h>

/* Y 路状态枚举 */
enum yroad_type_e {
    YROAD_NONE = 0,                     /* 无 Y 路 */
    YROAD_FOUND,                        /* 找到 Y 角点 */
    YROAD_NEAR,                         /* 接近 Y 路，Y 角点靠近 */
    YROAD_LEFT_RUN, YROAD_RIGHT_RUN,    /* Y 路内部行驶 */
    YROAD_LEFT_OUT, YROAD_RIGHT_OUT,    /* Y 路出口（再次看到 Y 角点） */
    YROAD_NUM,
};

/* 当前 Y 路状态 */
extern enum yroad_type_e yroad_type;

/* Y 路经过计数（用于交替选择左右分支） */
extern int8_t yroad_cnt;

/* ================= 接口函数 ================= */

/* Y 路检测入口 */
void check_yroad(void);

/* Y 路主流程 */
void run_yroad(void);

#endif /* YROAD_H */
