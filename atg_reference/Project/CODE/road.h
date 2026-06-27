/* =====================================================================
 *  道路类型检测模块接口（road）
 *
 *  根据边线曲率和角度变化率判断当前道路类型：
 *    直道、弯道、S 弯、大圆、小圆等
 *  用于自适应速度控制
 * ===================================================================== */
#ifndef _ROAD_H_
#define _ROAD_H_
#include "headfile.h"

/* 道路类型枚举 */
enum road_type_e {
    ROAD_NORMAL = 0,    /* 普通道路 */
    CURVE_NONE,         /* 无弯道 */
    CURVE_NEAR,         /* 接近弯道 */
    CURVE_IN,           /* 进入弯道 */
    CURVE_OUT,          /* 出弯道 */
    CURVE_CURVE,        /* 弯道中 */
    CURVE_S_CURVE,      /* S 弯 */
    LONG_STRAIGHT,      /* 长直道 */
    SHORT_STRAIGHT,     /* 短直道 */
    Large_Circle,       /* 大圆弯 */
    Small_Cirlce,       /* 小圆弯 */
};

/* 速度类型枚举：与道路类型对应的速度策略 */
enum speed_type_e {
    speed_normal,       /* 普通速度 */
    speed_shortfast,    /* 短直道快速 */
    speed_longfast,     /* 长直道快速 */
    speed_largecircle,  /* 大圆弯速度 */
    speed_smallcircle,  /* 小圆弯速度 */
    speed_curve_near,   /* 接近弯道减速 */
    speed_curve_in,     /* 弯道中速度 */
    speed_curve_out,    /* 出弯加速 */
};

/* 当前道路类型 */
extern enum road_type_e road_type;

/* 当前速度类型 */
extern enum speed_type_e speed_type;

/* 道路类型检测入口 */
void check_road(void);

#endif /* _ROAD_H_ */
