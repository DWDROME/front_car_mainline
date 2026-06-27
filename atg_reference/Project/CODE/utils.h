/* =====================================================================
 *  通用工具函数接口（utils）
 * ===================================================================== */
#ifndef UTILS_H
#define UTILS_H
#include "utils.h"

/* 钳位整数到 [low, up] 范围 */
int clip(int x, int low, int up);

/* 钳位浮点数到 [low, up] 范围 */
float fclip(float x, float low, float up);

#endif /* UTILS_H */
