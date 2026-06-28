/* =====================================================================
 *  vision_step: 一帧视觉主线
 *
 *  单帧处理流程：
 *    image_handle → find_corners → 元素处理 → choose_line → norm_line
 *
 *  元素优先级：圆环 > 十字 > 坡道 > 环岛 > Y路 > 车库
 * ===================================================================== */
#ifndef VISION_STEP_H
#define VISION_STEP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ================= 主接口 ================= */

/* 清空视觉状态，恢复默认参数 */
void vision_reset(void);

/* 跑一帧视觉，返回 1 表示有有效导引线 */
int vision_step(uint8_t gray[120][160], int64_t encoder_total);

/* 设置车辆参考点 x 坐标（原图坐标） */
void vision_set_car_x(float x);

/* 原图坐标 → 俯视角坐标（IPM 变换） */
void raw_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y);

/* 圆环 heading 输入 */
void vision_update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid);

/* ================= 视觉输出 ================= */
extern const char *src;
extern int src_id;
extern int64_t begin_dist;
extern int64_t last_begin_dist;
extern float car_raw_x;

#ifdef __cplusplus
}
#endif

#endif /* VISION_STEP_H */
