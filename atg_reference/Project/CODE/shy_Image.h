#ifndef _SHY_IMAGE_h
#define _SHY_IMAGE_h
#include "headfile.h"
void thres_hold(uint8 *img_data, uint8 *output_data, int width, int height, int thres);//普通二值化算法
void thres_hold_255(uint8 *img_data, uint8 *output_data, int width, int height, int thres);//普通二值化算法
void adaptiveThreshold(uint8* img_data, uint8* output_data, int width, int height, int block, uint8 clip_value);//自适应二值化
void process_image(void);
void image_handle(void);
void find_Left_line(uint8 *img_data, uint8 *output ,int block_size, int clip_value, int x, int y);
void find_corners(void);
void rot_img_process(void);
float rot_max(float a,float b,float c,float d);
float rot_min(float a,float b,float c,float d);

float Cal_rot_x(float x,float y);
float Cal_rot_y(float x,float y);
float Cal_inv_rot_x(float x,float y);
float Cal_inv_rot_y(float x,float y);
void lcd_Show_inv_Line(int num,float matrix[][2],float inv_matrix[][2],uint16 color);

void Cut_Image(void);
void Check_Ramp();
extern float rot[3][3];
extern float inv_rot[3][3];
extern int16 rot_height,rot_width;//透视变换之后图片的大小
extern int16 delta_y, delta_x;
extern float dw_max,dw_top;
extern int16 right_bound_x,left_bound_x;
extern float conf1,conf2,conf1_max,conf2_max;
//void Porcess_Image(void);


#endif
