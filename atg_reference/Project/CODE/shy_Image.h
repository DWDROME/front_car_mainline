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
#include "headfile.h"

/* ================= 阈值化 ================= */

/* 固定阈值二值化（输出 0/1） */
void thres_hold(uint8 *img_data, uint8 *output_data, int width, int height, int thres);

/* 固定阈值二值化（输出 0/255） */
void thres_hold_255(uint8 *img_data, uint8 *output_data, int width, int height, int thres);

/* 自适应阈值二值化 */
void adaptiveThreshold(uint8 *img_data, uint8 *output_data, int width, int height, int block, uint8 clip_value);

/* ================= 图像处理主入口 ================= */

void process_image(void);
void image_handle(void);

/* 左侧区域自适应二值化（车库检测用） */
void find_Left_line(uint8 *img_data, uint8 *output, int block_size, int clip_value, int x, int y);

/* 角点检测：找 Y 角点和 L 角点 */
void find_corners(void);

/* 透视变换 */
void rot_img_process(void);

/* ================= 工具函数 ================= */

float rot_max(float a, float b, float c, float d);
float rot_min(float a, float b, float c, float d);

/* 坐标变换 */
float Cal_rot_x(float x, float y);     /* 原图 → 俯视角 x */
float Cal_rot_y(float x, float y);     /* 原图 → 俯视角 y */
float Cal_inv_rot_x(float x, float y); /* 俯视角 → 原图 x */
float Cal_inv_rot_y(float x, float y); /* 俯视角 → 原图 y */

/* LCD 显示逆透视边线 */
void lcd_Show_inv_Line(int num, float matrix[][2], float inv_matrix[][2], uint16 color);

/* 图像下采样 */
void Cut_Image(void);

/* 坡道检测辅助 */
void Check_Ramp();

/* ================= 全局状态 ================= */

/* IPM 变换矩阵 */
extern float rot[3][3];
extern float inv_rot[3][3];

/* 透视变换后图片大小 */
extern int16 rot_height, rot_width;

/* 透视变换偏移 */
extern int16 delta_y, delta_x;

/* 坡道检测 */
extern float dw_max, dw_top;

/* 车库搜索边界 */
extern int16 right_bound_x, left_bound_x;

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
