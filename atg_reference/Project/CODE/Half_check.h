/* =====================================================================
 *  半十字检测模块接口（Half_check）
 *
 *  半十字：只有单侧出现 L 角点 + 远端边线的情况
 *  与全十字的区别：全十字两侧都有 L 角点，半十字只有一侧
 * ===================================================================== */
#ifndef _HALF_CHECK_H_
#define _HALF_CHECK_H_
#include "headfile.h"

/* ================= 接口函数 ================= */

/* 半十字检测入口：根据 Lpt0/Lpt1_found 选择左右检测 */
void check_Half();

/* 左侧半十字检测：返回 1 表示检测到，0 表示未检测到 */
int check_Half_left();

/* 右侧半十字检测：返回 1 表示检测到，0 表示未检测到 */
int check_Half_right();

/* ================= 全局状态 ================= */

/* 远端右线端点坐标 */
extern float Far_rLine_endpoint_x, Far_rLine_endpoint_y;

/* 近端右线端点坐标 */
extern float near_rLine_endpoint_x, near_rLine_endpoint_y;

/* 车库检测相关变量 */
extern int find_garage_left_x, find_garage_left_y;
extern int find_garage_white, find_garage_black;
extern int find_garage_num, find_garage_change_num;
extern int find_garage;

#endif /* _HALF_CHECK_H_ */
