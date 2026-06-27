/* =====================================================================
 *  图像处理工具库接口（imgproc）
 *
 *  提供基础图像操作：阈值化、滤波、形态学、沿线追踪、线段逼近、
 *  点集处理（重采样/角度/NMS/偏移）、大津法、绘图工具
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

typedef struct fimage {
    float *data;
    uint32_t width;
    uint32_t height;
    uint32_t step;
} fimage_t;

#define AT_IMAGE(img, x, y)          ((img)->data[(y)*(img)->step+(x)])
#define AT_IMAGE_CLIP(img, x, y)     AT_IMAGE(img, clip(x, 0, (img)->width-1), clip(y, 0, (img)->height-1))

#define DEF_IMAGE(ptr, w, h)         {.data=ptr, .width=w, .height=h, .step=w}
#define ROI_IMAGE(img, x1, y1, w, h) {.data=&AT_IMAGE(img, x1, y1), .width=w, .height=h, .step=img.width}


void clone_image(image_t *img0, image_t *img1);


void clear_image(image_t *img);


void threshold(image_t *img0, image_t *img1, uint8_t thres, uint8_t low_value, uint8_t high_value);


void adaptive_threshold(image_t *img0, image_t *img1, int block_size, int down_value, uint8_t low_value, uint8_t high_value);


void image_and(image_t *img0, image_t *img1, image_t *img2);


void image_or(image_t *img0, image_t *img1, image_t *img2);


void minpool2(image_t *img0, image_t *img1);


void blur3(image_t *img0, image_t *img1);


void sobel3(image_t *img0, image_t *img1);


void erode3(image_t *img0, image_t *img1);


void dilate3(image_t *img0, image_t *img1);


void remap(image_t *img0, image_t *img1, fimage_t *mapx, fimage_t *mapy);


void findline_lefthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);


void findline_righthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num);


uint16_t getOSTUThreshold(image_t *img, uint8_t MinThreshold, uint8_t MaxThreshold);

void Ostu_Robert(unsigned char *org_in, unsigned char *ostu_out, unsigned char th_ostu, unsigned int th_edge, unsigned int start_rows, unsigned int end_rows) ;

void blur_points(float pts_in[][2], int num, float pts_out[][2], int kernel);

uint8_t Threshold_deal(uint8_t *image, uint16_t col, uint16_t row,uint32_t pixel_threshold);

void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist);


void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist);


void nms_angle(float angle_in[], int num, float angle_out[], int kernel);

void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);


void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist);


void draw_x(image_t *img, int x, int y, int len, uint8_t value);


void draw_o(image_t *img, int x, int y, int radius, uint8_t value);

uint8_t otsuThreshold(uint8_t *image, uint16_t width, uint16_t height);

#endif // IMGPROC_H
