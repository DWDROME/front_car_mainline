#include "imgproc.h"
#include "headfile.h"
#include "common.h"
#include "math.h"
#define PI               3.14159265358979f
#define AT                  AT_IMAGE
#define AT_CLIP(img, x, y)  AT_IMAGE((img), clip((x), 0, (img)->width-1), clip((y), 0, (img)->height-1));

extern int clip(int x, int low, int up);


void clone_image(image_t *img0, image_t *img1) {
    if (img0->width == img0->step && img1->width == img1->step) {
        memcpy(img1->data, img0->data, img0->width * img0->height);
    } else {
        for (int y = 0; y < img0->height; y++) {
            memcpy(&AT(img1, 0, y), &AT(img0, 0, y), img0->width);
        }
    }
}

void clear_image(image_t *img) {
    if (img->width == img->step) {
        memset(img->data, 0, img->width * img->height);
    } else {
        for (int y = 0; y < img->height; y++) {
            memset(&AT(img, 0, y), 0, img->width);
        }
    }
}


void threshold(image_t *img0, image_t *img1, uint8_t thres, uint8_t low_value, uint8_t high_value) {
    for (int y = 0; y < img0->height; y++) {
        for (int x = 0; x < img0->width; x++) {
                    AT(img1, x, y) = AT(img0, x, y) < thres ? low_value : high_value;
        }
    }
}


void adaptive_threshold(image_t *img0, image_t *img1, int block_size, int down_value, uint8_t low_value, uint8_t high_value) {
    int half = block_size / 2;
    for (int y = 0; y < img0->height; y++) {
        for (int x = 0; x < img0->width; x++) {
            int thres_value = 0;
            for (int dy = -half; dy <= half; dy++) {
                for (int dx = -half; dx <= half; dx++) {
                    thres_value += AT_CLIP(img0, x + dx, y + dy);
                }
            }
            thres_value /= block_size * block_size;
            thres_value -= down_value;
                    AT(img1, x, y) = AT(img0, x, y) < thres_value ? low_value : high_value;
        }
    }
}


void image_and(image_t *img0, image_t *img1, image_t *img2) {
    for (int y = 0; y < img0->height; y++) {
        for (int x = 0; x < img0->width; x++) {
                    AT(img2, x, y) = (AT(img0, x, y) == 0 || AT(img1, x, y) == 0) ? 0 : 255;
        }
    }
}


void image_or(image_t *img0, image_t *img1, image_t *img2){
    for (int y = 0; y < img0->height; y++) {
        for (int x = 0; x < img0->width; x++) {
                    AT(img2, x, y) = (AT(img0, x, y) == 0 && AT(img1, x, y) == 0) ? 0 : 255;
        }
    }
}


void minpool2(image_t *img0, image_t *img1){
    uint8_t min_value;

    for (int y = 1; y < img0->height; y += 2) {
        for (int x = 1; x < img0->width; x += 2) {
            min_value = 255;
            if (AT(img0, x, y) < min_value) min_value = AT(img0, x, y);
            if (AT(img0, x - 1, y) < min_value) min_value = AT(img0, x - 1, y);
            if (AT(img0, x, y - 1) < min_value) min_value = AT(img0, x, y - 1);
            if (AT(img0, x - 1, y - 1) < min_value) min_value = AT(img0, x - 1, y - 1);
                    AT(img1, x / 2, y / 2) = min_value;
        }
    }
}


void blur(image_t *img0, image_t *img1, uint32_t kernel){

    for (int y = 1; y < img0->height - 1; y++) {
        for (int x = 1; x < img0->width - 1; x++) {
                    AT(img1, x, y) = (1 * AT(img0, x - 1, y - 1) + 2 * AT(img0, x, y - 1) + 1 * AT(img0, x + 1, y - 1) +
                                      2 * AT(img0, x - 1, y) + 4 * AT(img0, x, y) + 2 * AT(img0, x + 1, y) +
                                      1 * AT(img0, x - 1, y + 1) + 2 * AT(img0, x, y + 1) + 1 * AT(img0, x + 1, y + 1)) / 16;
        }
    }
}


void sobel3(image_t *img0, image_t *img1){
    int gx, gy;
    for (int y = 1; y < img0->height - 1; y++) {
        for (int x = 1; x < img0->width - 1; x++) {
            gx = (-1 * AT(img0, x - 1, y - 1) + 1 * AT(img0, x + 1, y - 1) +
                  -2 * AT(img0, x - 1, y) + 2 * AT(img0, x + 1, y) +
                  -1 * AT(img0, x - 1, y + 1) + 1 * AT(img0, x + 1, y + 1)) / 4;
            gy = (1 * AT(img0, x - 1, y - 1) + 2 * AT(img0, x, y - 1) + 1 * AT(img0, x + 1, y - 1) +
                  -1 * AT(img0, x - 1, y + 1) - 2 * AT(img0, x, y + 1) - 1 * AT(img0, x + 1, y + 1)) / 4;
                    AT(img1, x, y) = (fabs(gx) + fabs(gy)) / 2;
        }
    }
}


void erode3(image_t *img0, image_t *img1) {
    int min_value;
    for (int y = 1; y < img0->height - 1; y++) {
        for (int x = 1; x < img0->width - 1; x++) {
            min_value = 255;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (AT(img0, x + dx, y + dy) < min_value) min_value = AT(img0, x + dx, y + dy);
                }
            }
                    AT(img1, x, y) = min_value;
        }
    }
}


void dilate3(image_t *img0, image_t *img1) {
    int max_value;
    for (int y = 1; y < img0->height - 1; y++) {
        for (int x = 1; x < img0->width - 1; x++) {
            max_value = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (AT(img0, x + dx, y + dy) > max_value) max_value = AT(img0, x + dx, y + dy);
                }
            }
                    AT(img1, x, y) = max_value;
        }
    }
}

//
void remap(image_t *img0, image_t *img1, fimage_t *mapx, fimage_t *mapy) {
    for (int y = 1; y < img0->height - 1; y++) {
        for (int x = 1; x < img0->width - 1; x++) {
                    AT(img1, x, y) = AT(img0, (int) (AT(mapx, x, y) + 0.5), (int) (AT(mapy, x, y) + 0.5));
        }
    }
}


const int dir_front[4][2] = {{0,  -1},
                                                            {1,  0},
                                                            {0,  1},
                                                            {-1, 0}};
const int dir_frontleft[4][2] = {{-1, -1},
                                                                {1,  -1},
                                                                {1,  1},
                                                                {-1, 1}};
const int dir_frontright[4][2] = {{1,  -1},
                                                                 {1,  1},
                                                                 {-1, 1},
                                                                 {-1, -1}};


void findline_lefthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num) {
    int half = block_size / 2;
    int step = 0, dir = 0, turn = 0;
    while (step < *num && half < x && x < img->width - half - 1 && 0 < y && y < img->height - half - 1 && turn < 4) {
        int local_thres = 0;
        for (int dy = -half; dy <= half; dy++) {
            for (int dx = -half; dx <= half; dx++) {
                local_thres += AT(img, x + dx, y + dy);
            }
        }
        local_thres /= block_size * block_size;
        local_thres -= clip_value;

        int current_value = AT(img, x, y);
        int front_value = AT(img, x + dir_front[dir][0], y + dir_front[dir][1]);
        int frontleft_value = AT(img, x + dir_frontleft[dir][0], y + dir_frontleft[dir][1]);
        if (front_value < local_thres) {
            dir = (dir + 1) % 4;
            turn++;
        } else if (frontleft_value < local_thres) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            //for(int i=0;i<3;i++)lcd_drawpoint(x+i,y,RED);
            step++;
            turn = 0;
        } else {
            x += dir_frontleft[dir][0];
            y += dir_frontleft[dir][1];
            dir = (dir + 3) % 4;
            pts[step][0] = x;
            pts[step][1] = y;
            //for(int i=0;i<3;i++)lcd_drawpoint(x+i,y,RED);
            step++;
            turn = 0;
        }
    }
    *num = step;
}


void findline_righthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num) {
    int half = block_size / 2;
    int step = 0, dir = 0, turn = 0;
    while (step < *num && 0 < x && x < img->width -half- 1 && 0 < y && y < img->height - 1 && turn < 4) {
        int local_thres = 0;
        for (int dy = -half; dy <= half; dy++) {
            for (int dx = -half; dx <= half; dx++) {
                local_thres += AT(img, x + dx, y + dy);
            }
        }
        local_thres /= block_size * block_size;
        local_thres -= clip_value;

        int current_value = AT(img, x, y);
        int front_value = AT(img, x + dir_front[dir][0], y + dir_front[dir][1]);
        int frontright_value = AT(img, x + dir_frontright[dir][0], y + dir_frontright[dir][1]);
        if (front_value < local_thres) {
            dir = (dir + 3) % 4;
            turn++;
        } else if (frontright_value < local_thres) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            //for(int i=0;i<3;i++)lcd_drawpoint(x-i,y,GREEN);
            step++;
            turn = 0;
        } else {
            x += dir_frontright[dir][0];
            y += dir_frontright[dir][1];
            dir = (dir + 1) % 4;
            pts[step][0] = x;
            pts[step][1] = y;
            //for(int i=0;i<3;i++)lcd_drawpoint(x-i,y,GREEN);
            step++;
            turn = 0;
        }
    }

    *num = step;
}


void approx_lines(int pts[][2], int pts_num, float epsilon, int lines[][2], int *lines_num){
    int dx = pts[pts_num - 1][0] - pts[0][0];
    int dy = pts[pts_num - 1][1] - pts[0][1];
    float nx = -dy / sqrtf(dx * dx + dy * dy);
    float ny = dx / sqrtf(dx * dx + dy * dy);
    float max_dist = 0, dist;
    int idx = -1;
    for (int i = 1; i < pts_num - 1; i++) {
        dist = fabs((pts[i][0] - pts[0][0]) * nx + (pts[i][1] - pts[0][1]) * ny);
        if (dist > max_dist) {
            max_dist = dist;
            idx = i;
        }
    }
    if (max_dist >= epsilon) {
        int num1 = *lines_num;
        approx_lines(pts, idx + 1, epsilon, lines, &num1);
        int num2 = *lines_num - num1 - 1;
        approx_lines(pts + idx, pts_num - idx, epsilon, lines + num1 - 1, &num2);
        *lines_num = num1 + num2 - 1;
    } else {
        lines[0][0] = pts[0][0];
        lines[0][1] = pts[0][1];
        lines[1][0] = pts[pts_num - 1][0];
        lines[1][1] = pts[pts_num - 1][1];
        *lines_num = 2;
    }
}


void approx_lines_f(float pts[][2], int pts_num, float epsilon, float lines[][2], int *lines_num) {
    int dx = pts[pts_num - 1][0] - pts[0][0];
    int dy = pts[pts_num - 1][1] - pts[0][1];
    float nx = -dy / sqrtf(dx * dx + dy * dy);
    float ny = dx / sqrtf(dx * dx + dy * dy);
    float max_dist = 0, dist;
    int idx = -1;
    for (int i = 1; i < pts_num - 1; i++) {
        dist = fabs((pts[i][0] - pts[0][0]) * nx + (pts[i][1] - pts[0][1]) * ny);
        if (dist > max_dist) {
            max_dist = dist;
            idx = i;
        }
    }
    if (max_dist >= epsilon && *lines_num > 2) {
        int num1 = *lines_num;
        approx_lines_f(pts, idx + 1, epsilon, lines, &num1);
        int num2 = *lines_num - num1 - 1;
        approx_lines_f(pts + idx, pts_num - idx, epsilon, lines + num1 - 1, &num2);
        *lines_num = num1 + num2 - 1;
    } else {
        lines[0][0] = pts[0][0];
        lines[0][1] = pts[0][1];
        lines[1][0] = pts[pts_num - 1][0];
        lines[1][1] = pts[pts_num - 1][1];
        *lines_num = 2;
    }
}

void draw_line(image_t *img, int pt0[2], int pt1[2], uint8_t value) {
    int dx = pt1[0] - pt0[0];
    int dy = pt1[1] - pt0[1];
    if (fabs(dx) > fabs(dy)) {
        for (int x = pt0[0]; x != pt1[0]; x += (dx > 0 ? 1 : -1)) {
            int y = pt0[1] + (x - pt0[0]) * dy / dx;
                    AT(img, clip(x, 0, img->width - 1), clip(y, 0, img->height - 1)) = value;
        }
    } else {
        for (int y = pt0[1]; y != pt1[1]; y += (dy > 0 ? 1 : -1)) {
            int x = pt0[0] + (y - pt0[1]) * dx / dy;
                    AT(img, clip(x, 0, img->width - 1), clip(y, 0, img->height - 1)) = value;
        }
    }
}







uint8 otsuThreshold(uint8 *image, uint16 width, uint16 height)
{
    #define GrayScale 256
    int pixelCount[GrayScale] = {0};//每个灰度值所占像素个数
    float pixelPro[GrayScale] = {0};//每个灰度值所占总像素比例
    int i,j;
    int Sumpix = width * height;   //总像素点
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针


    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
          //   pixelCount[(int)image[i][j]]++;    若不用指针用这个
        }
    }
    float u = 0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / Sumpix;   //计算每个像素在整幅图像中的比例
        u += i * pixelPro[i];  //总平均灰度
    }


    float maxVariance=0.0;  //最大类间方差
    float w0 = 0, avgValue  = 0;  //w0 前景比例 ，avgValue 前景平均灰度
    for(int i = 0; i < 256; i++)     //每一次循环都是一次完整类间方差计算 (两个for叠加为1个)
    {
        w0 += pixelPro[i];  //假设当前灰度i为阈值, 0~i 灰度像素所占整幅图像的比例即前景比例
        avgValue  += i * pixelPro[i];

        float variance = pow((avgValue/w0 - u), 2) * w0 /(1 - w0);    //类间方差
        if(variance > maxVariance)
        {
            maxVariance = variance;
            threshold = i;
        }
    }


    return threshold;

}











uint16_t getOSTUThreshold(image_t *img, uint8_t MinThreshold, uint8_t MaxThreshold) {
    uint8_t Histogram[256];
    uint16_t OUSTThreshold = 0;
    uint32_t PixelAmount = 0, Value_Sum = 0;
    uint64_t sigma = 0, maxSigma = 0;
    float w1 = 0, w2 = 0;
    int32_t u1 = 0, u2 = 0;
    uint8_t MinValue = 0, MaxValue = 255;
    uint8_t *ptr = img->data;
    uint8_t *ptrEnd = img->data + img->width * img->height;
    while (ptr != ptrEnd) {
        ++Histogram[*ptr++];
    }

    for (uint8_t m = 0; m < 100; m++) {

        Histogram[m] = 0;
    }

    for (MinValue = 0; Histogram[MinValue] == 0 && MinValue < 255; ++MinValue);
    for (MaxValue = 255; Histogram[MaxValue] == 0 && MaxValue > 0; --MaxValue);

    if (MaxValue == MinValue) return MaxValue;         // 闁告瑯浜濆﹢浣圭▔閿熻姤绋夐鍫澒闁肩櫢鎷�
    if (MinValue + 1 == MaxValue) return MinValue;        // 闁告瑯浜濆﹢浣圭鐏炲ジ鍤嬪Λ鐗堢矎婢癸拷

    if (MinValue < MinThreshold) {
        MinValue = MinThreshold;
    }
    if (MaxValue > MaxThreshold) {
        MaxValue = MaxThreshold;
    }

    uint32_t Pixel_Integral[256] = {0};
    uint32_t Value_Integral[256] = {0};
    for (uint8_t i = MinValue; i <= MaxValue; ++i) {
        PixelAmount += Histogram[i];
        Value_Sum += Histogram[i] * i;
        Pixel_Integral[i] = PixelAmount;
        Value_Integral[i] = Value_Sum;
    }
    for (uint8_t i = MinValue; i < MaxValue + 1; ++i) {
        w1 = (float) Pixel_Integral[i] / PixelAmount;
        w2 = 1 - w1;
        u1 = (int32_t) (Value_Integral[i] / w1);
        u2 = (int32_t) ((Value_Sum - Value_Integral[i]) / w2);
        sigma = (uint64_t) (w1 * w2 * (u1 - u2) * (u1 - u2));
        if (sigma >= maxSigma) {
            maxSigma = sigma;
            OUSTThreshold = i;
        } else {
            break;
        }
    }
    return OUSTThreshold;
}


uint8_t Threshold_deal(uint8_t *image, uint16_t col, uint16_t row,uint32_t pixel_threshold)
{
  #define GrayScale 256
  uint16_t width = col;
  uint16_t height = row;
  int pixelCount[GrayScale];
  float pixelPro[GrayScale];
  int i, j, pixelSum = width * height;
  uint8_t threshold = 0;
  uint8_t* data = image;  //指向像素数据的指针
  for (i = 0; i < GrayScale; i++)
  {
    pixelCount[i] = 0;
    pixelPro[i] = 0;
  }
  uint32_t gray_sum=0;
  //统计灰度级中每个像素在整幅图像中的个数
  for (i = 0; i < height; i+=1)
  {
    for (j = 0; j < width; j+=1)
    {
      //if((sun_mode&&data[i*width+j]<pixel_threshold)||(!sun_mode))
      //{
        pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
        gray_sum+=(int)data[i * width + j];       //灰度值总和
      //}
    }
  }
  //计算每个像素值的点在整幅图像中的比例
  for (i = 0; i < GrayScale; i++)
  {
    pixelPro[i] = (float)pixelCount[i] / pixelSum;
  }
  //遍历灰度级[0,255]
  float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;



  w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
  for (j = 0; j < pixel_threshold; j++)
  {

    w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
    u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

    w1=1-w0;
    u1tmp=gray_sum/pixelSum-u0tmp;

    u0 = u0tmp / w0;              //背景平均灰度
    u1 = u1tmp / w1;              //前景平均灰度
    u = u0tmp + u1tmp;            //全局平均灰度
    deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
    if (deltaTmp > deltaMax)
    {
      deltaMax = deltaTmp;
      threshold = j;
    }
    if (deltaTmp < deltaMax)
    {
      break;
    }
  }
  return threshold;
}

/*
    函数功能：在对OSTU二值化的图像进行Robert算子边缘增强
    参数说明：
        org_in：输入原图，一维数组
        ostu_out：输出图像，经大津法二值化并进行边缘增强后的图像
          th_ostu: 大津法阈值
        th_edge：边缘增强阈值，建议在11左右调试
        start_rows: 边缘强化起始行，从0开始计数
        end_row：边缘强化结束行，包括改行
*/
#define MAX_COLS 160 /*图像水平分辨率*/
#define MAX_ROWS 100 /*图像竖直分辨率*/
//#define TH_EDGE 30     /*该阈值是前个版本的两倍*/
void Ostu_Robert(unsigned char *org_in, unsigned char *ostu_out, unsigned char th_ostu, unsigned int th_edge, unsigned int start_rows, unsigned int end_rows) //阳光算法2
{
  unsigned int i, col, h, v;
  unsigned int start_pixel, end_pixel;
  unsigned int pix0, pix1, pix2, pix3;

  col = 0;
  start_pixel = start_rows * MAX_COLS;
  end_pixel = (end_rows + 1) * MAX_COLS;

  for (i = start_pixel; i < end_pixel - MAX_COLS; i++)
  {
    col++;

    if (org_in[i] >= th_ostu) /*等号是否需要根据小车情况进行处理*/
    {
      ostu_out[i - start_pixel] = 255; /*置白*/
    }
    else
    {
      ostu_out[i - start_pixel] = 0; /*置黑*/
    }

    if (col == MAX_COLS) //右边界像素无法用Robert算子，不增强，仅更新列索引
    {
      col = 0;
    }
    else //Robert算子边缘增强
    {
      pix0 = (unsigned int)org_in[i] & 0xff;
      pix1 = (unsigned int)org_in[i + 1] & 0xff;
      pix2 = (unsigned int)org_in[i + MAX_COLS] & 0xff;
      pix3 = (unsigned int)org_in[i + 1 + MAX_COLS] & 0xff;

      if (pix0 > pix3)
      {
        h = pix0 - pix3;
      }
      else
      {
        h = pix3 - pix0;
      }

      if (pix1 > pix2)
      {
        v = pix1 - pix2;
      }
      else
      {
        v = pix2 - pix1;
      }

      h = h + v;

      if (h >= th_edge)
      {
        ostu_out[i - start_pixel] = 0; // 强制置黑
      }
    }
  }
}
void blur_points(float pts_in[][2], int num, float pts_out[][2], int kernel){
    int half = kernel / 2;
    for (int i = 0; i < num; i++) {
        pts_out[i][0] = pts_out[i][1] = 0;
        for (int j = -half; j <= half; j++) {
            pts_out[i][0] += pts_in[clip(i + j, 0, num - 1)][0] * (half + 1 - fabs(j));
            pts_out[i][1] += pts_in[clip(i + j, 0, num - 1)][1] * (half + 1 - fabs(j));
        }
        pts_out[i][0] /= (2 * half + 2) * (half + 1) / 2;
        pts_out[i][1] /= (2 * half + 2) * (half + 1) / 2;
    }
}


void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist){
    if (num1 < 0) {
        *num2 = 0;
        return;
    }
    pts_out[0][0] = pts_in[0][0];
    pts_out[0][1] = pts_in[0][1];
    int len = 1;
    for (int i = 0; i < num1 - 1 && len < *num2; i++) {
        float x0 = pts_in[i][0];
        float y0 = pts_in[i][1];
        float x1 = pts_in[i + 1][0];
        float y1 = pts_in[i + 1][1];

        do {
            float x = pts_out[len - 1][0];
            float y = pts_out[len - 1][1];

            float dx0 = x0 - x;
            float dy0 = y0 - y;
            float dx1 = x1 - x;
            float dy1 = y1 - y;

            float dist0 = sqrt(dx0 * dx0 + dy0 * dy0);
            float dist1 = sqrt(dx1 * dx1 + dy1 * dy1);

            float r0 = (dist1 - dist) / (dist1 - dist0);
            float r1 = 1 - r0;

            if (r0 < 0 || r1 < 0) break;
            x0 = x0 * r0 + x1 * r1;
            y0 = y0 * r0 + y1 * r1;
            pts_out[len][0] = x0;
            pts_out[len][1] = y0;
            len++;
        } while (len < *num2);

    }
    *num2 = len;
}

void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist){
    for (int i = 0; i < num; i++) {
        if (i <= 0 || i >= num - 1) {
            angle_out[i] = 0;
            continue;
        }
        float dx1 = pts_in[i][0] - pts_in[clip(i - dist, 0, num - 1)][0];
        float dy1 = pts_in[i][1] - pts_in[clip(i - dist, 0, num - 1)][1];
        float dn1 = sqrtf(dx1 * dx1 + dy1 * dy1);
        float dx2 = pts_in[clip(i + dist, 0, num - 1)][0] - pts_in[i][0];
        float dy2 = pts_in[clip(i + dist, 0, num - 1)][1] - pts_in[i][1];
        float dn2 = sqrtf(dx2 * dx2 + dy2 * dy2);
        float c1 = dx1 / dn1;
        float s1 = dy1 / dn1;
        float c2 = dx2 / dn2;
        float s2 = dy2 / dn2;
        angle_out[i] = atan2f(c1 * s2 - c2 * s1, c2 * c1 + s2 * s1);
    }
}


void nms_angle(float angle_in[], int num, float angle_out[], int kernel){
    int half = kernel / 2;
    for (int i = 0; i < num; i++) {
        angle_out[i] = angle_in[i];
        for (int j = -half; j <= half; j++) {
            if (fabs(angle_in[clip(i + j, 0, num - 1)]) > fabs(angle_out[i])) {
                angle_out[i] = 0;
                break;
            }
        }
    }
}

void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist) {
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] - dy * dist;
        pts_out[i][1] = pts_in[i][1] + dx * dist;


    }
}


void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist){
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] + dy * dist;
        pts_out[i][1] = pts_in[i][1] - dx * dist;
    }
}

void draw_x(image_t *img, int x, int y, int len, uint8_t value) {
    for (int i = -len; i <= len; i++) {
                AT(img, clip(x + i, 0, img->width - 1), clip(y + i, 0, img->height - 1)) = value;
                AT(img, clip(x - i, 0, img->width - 1), clip(y + i, 0, img->height - 1)) = value;
    }
}

void draw_o(image_t *img, int x, int y, int radius, uint8_t value) {
    for (float i = -PI; i <= PI; i += PI / 10) {
                AT(img, clip(x + radius * cosf(i), 0, img->width - 1), clip(y + radius * sinf(i), 0, img->height - 1)) = value;
    }
}
