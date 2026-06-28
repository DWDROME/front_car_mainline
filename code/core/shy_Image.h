/* =====================================================================
 *  图像处理主框架接口（shy_Image）
 *
 *  核心处理流程（image_handle）：
 *    种子点搜索 → 沿线追踪 → 透视变换 → 滤波 → 采样 → 角度计算 → 中线跟踪
 *
 *  角点检测（find_corners）：
 *    在等距采样后的边线上找 Y 角点和 L 角点
 * ===================================================================== */
#ifndef _SHY_IMAGE_h
#define _SHY_IMAGE_h

#include <stdint.h>

/* ================= 图像处理主入口 ================= */

void image_handle(void);

/* 角点检测：找 Y 角点和 L 角点 */
void find_corners(void);

/* 透视变换 */
void rot_img_process(void);

/* 坐标变换 */
float Cal_rot_x(float x, float y);     /* 原图 → 俯视角 x */
float Cal_rot_y(float x, float y);     /* 原图 → 俯视角 y */
float Cal_inv_rot_x(float x, float y); /* 俯视角 → 原图 x */
float Cal_inv_rot_y(float x, float y); /* 俯视角 → 原图 y */

/* ================= 全局状态 ================= */

/* IPM 变换矩阵 */
extern float rot[3][3];
extern float inv_rot[3][3];

/* 透视变换偏移 */
extern int16_t delta_y, delta_x;

/* 角点置信度（调试用） */
extern float conf1, conf2, conf1_max, conf2_max;

/* 种子点搜索结果 */
extern int atg_seed0_found, atg_seed1_found;
extern int atg_seed0_x, atg_seed0_y, atg_seed1_x, atg_seed1_y;

/* 角点检测结果（调试用） */
extern int atg_lpt0_best_i, atg_lpt1_best_i;
extern int atg_lpt0_best_im1, atg_lpt0_best_ip1;
extern int atg_lpt1_best_im1, atg_lpt1_best_ip1;
extern int atg_lpt0_pass_nms, atg_lpt0_pass_low, atg_lpt0_pass_high, atg_lpt0_pass_near, atg_lpt0_pass_dir;
extern int atg_lpt1_pass_nms, atg_lpt1_pass_low, atg_lpt1_pass_high, atg_lpt1_pass_near, atg_lpt1_pass_dir;
extern int atg_lpt0_accept_i, atg_lpt1_accept_i;
extern float atg_lpt0_best_conf, atg_lpt1_best_conf;
extern float atg_lpt0_best_x, atg_lpt0_best_y, atg_lpt1_best_x, atg_lpt1_best_y;
extern float atg_lpt0_best_inv_x, atg_lpt0_best_inv_y, atg_lpt1_best_inv_x, atg_lpt1_best_inv_y;

#endif /* _SHY_IMAGE_h */
