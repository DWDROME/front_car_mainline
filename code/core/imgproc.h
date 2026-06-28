/* =====================================================================
 *  视觉主链图像基础接口（imgproc）
 *
 *  保留当前主链使用的沿线追踪和点列处理 primitive。
 * ===================================================================== */
#ifndef IMGPROC_H
#define IMGPROC_H

#include <stdint.h>
#include "utils.h"

/* 图像结构体：data 为像素数据，width/height 为尺寸，step 为行步长 */
typedef struct image {
    uint8_t *data;
    uint32_t width;
    uint32_t height;
    uint32_t step;
} image_t;

#define AT_IMAGE(img, x, y)          ((img)->data[(y)*(img)->step+(x)])

#define DEF_IMAGE(ptr, w, h)         {.data=ptr, .width=w, .height=h, .step=w}

void findline_lefthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);

void findline_righthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);

void blur_points(float pts_in[][2], int num, float pts_out[][2], int kernel);

void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist);

void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist);

void nms_angle(float angle_in[], int num, float angle_out[], int kernel);

void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);

void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);

#endif // IMGPROC_H
