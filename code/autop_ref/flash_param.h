#ifndef AUTOP_REF_FLASH_PARAM_H
#define AUTOP_REF_FLASH_PARAM_H

#include <stdbool.h>

extern float thres;
extern float block_size;
extern float clip_value;
extern float begin_x;
extern float begin_y;
extern float line_blur_kernel;
extern float pixel_per_meter;
extern float sample_dist;
extern float point_sample_dist;
extern float angle_dist;
extern float aim_distance;
extern float far_rate;
extern bool adc_cross;

void flash_param_init(void);
bool flash_param_check(void);
void flash_param_load(void);
void flash_param_write(void);

#endif
