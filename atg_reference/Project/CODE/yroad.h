/* =====================================================================
 *  Y 路检测模块接口（yroad）
 *
 *  状态机：NONE → FOUND → NEAR → LEFT/RIGHT_RUN → LEFT/RIGHT_OUT → NONE
 *
 *  检测依据：Ypt0/Ypt1_found（Y 形角点）
 *  当前状态：废弃（ATG_ENABLE_YROAD=0），代码保留供参考
 * ===================================================================== */
#ifndef YROAD_H
#define YROAD_H
#include "headfile.h"

/* Y 路状态枚举 */
enum yroad_type_e {
    YROAD_NONE = 0,                     /* 无 Y 路 */
    YROAD_FOUND,                        /* 找到 Y 角点 */
    YROAD_NEAR,                         /* 接近 Y 路，Y 角点靠近 */
    YROAD_LEFT_RUN, YROAD_RIGHT_RUN,    /* Y 路内部行驶 */
    YROAD_LEFT_OUT, YROAD_RIGHT_OUT,    /* Y 路出口（再次看到 Y 角点） */
    YROAD_NUM,
};

#define ENCODER_PER_METER   (5800)      /* 每米编码器 counts 数 */

/* 当前 Y 路状态 */
extern enum yroad_type_e yroad_type;

/* 状态名称表（用于日志） */
extern const char *yroad_type_name[YROAD_NUM];

/* Y 路经过计数（用于交替选择左右分支） */
extern int8 yroad_cnt;

/* ================= 接口函数 ================= */

/* Y 路检测入口 */
void check_yroad();

/* Y 路主流程 */
void run_yroad();

/* Y 路行驶速度 */
extern int16 yroad_speed;

#endif /* YROAD_H */
