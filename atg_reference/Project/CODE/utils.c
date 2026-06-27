/* =====================================================================
 *  通用工具函数（utils）
 * ===================================================================== */
#include "utils.h"

/* 钳位整数到 [low, up] 范围 */
int clip(int x, int low, int up) {
    return x > up ? up : x < low ? low : x;
}

/* 钳位浮点数到 [low, up] 范围 */
float fclip(float x, float low, float up) {
    return x > up ? up : x < low ? low : x;
}
