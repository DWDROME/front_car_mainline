/* =====================================================================
 *  ATG 参考线处理主框架接口（atg_reference_step）
 *
 *  单帧处理流程：
 *    image_handle → find_corners → run_atg_elements → select_work_line → normalize
 *
 *  元素优先级：圆环 > 十字 > 坡道 > 环岛 > Y路 > 车库
 * ===================================================================== */
#ifndef ATG_REFERENCE_STEP_H
#define ATG_REFERENCE_STEP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ================= 主接口 ================= */

/* 全局复位：清空所有状态，恢复默认参数 */
void atg_reference_reset(void);

/* 单帧处理主入口：输入灰度图和编码器值，返回 1 表示有有效导引线 */
int atg_reference_process_frame(uint8_t gray[120][160], int64_t encoder_total);

/* ================= 查询接口 ================= */

/* 是否有有效导引线（rptsn_num > 0） */
int atg_reference_track_line_found(void);

/* 设置车辆参考点 x 坐标（原图坐标） */
void atg_reference_set_vehicle_raw_ref_x(float raw_x);

/* 获取车辆参考点 x 坐标 */
float atg_reference_vehicle_raw_ref_x(void);

/* 原图坐标 → 俯视角坐标（IPM 变换） */
void atg_reference_raw_ref_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y);

/* 获取圆环 BEGIN 阶段累计行驶距离 */
int64_t atg_reference_circle_begin_dist(void);

/* 获取上一次圆环 BEGIN 阶段累计行驶距离 */
int64_t atg_reference_circle_begin_last_dist(void);

/* 获取选线来源名称（用于日志） */
const char *atg_reference_selected_line_source(void);

/* 获取选线来源数字 id（用于数据记录） */
int atg_reference_selected_line_source_id(void);

#ifdef __cplusplus
}
#endif

#endif /* ATG_REFERENCE_STEP_H */
