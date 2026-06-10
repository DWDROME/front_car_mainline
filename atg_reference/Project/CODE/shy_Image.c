#include "shy_Image.h"
#include <common.h>
#include "stdlib.h"
#include "math.h"
#define PI               3.14159265358979f
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
float pix[2];
float rot[3][3]={
        //透视变换矩阵，由matlab仿真程序生成
        6.8631  ,0  , -5.8559,
        4.4931 , 1.0072  ,-4.4931,
        0.0494,  0 , 0.9579
};
float inv_rot[3][3]={
        //逆透视变换矩阵，由matlab仿真程序生成
        0.1396  ,0 ,  0.8532,
        -0.6547 ,0.9928 , 0.6547,
        -0.0072 ,0 ,  1
};
float pix1[2],pix2[2],pix3[2],pix4[2];
float dw_max,dw_top;
int16 rot_height=116;
int16 rot_width =187;//透视变换之后图片的大小
int16 delta_y= 0;
int16 delta_x= 0;
int16 right_bound_x,left_bound_x;
int8  Image_thres=7;
float conf1,conf2,conf1_max,conf2_max;//用于记录当前边线计算中的最大角点，方便调试阈值

void thres_hold(uint8 *img_data, uint8 *output_data, int width, int height, int thres)
{
  for(int y=0; y<height; y++){
    for(int x=0; x<width; x++){
      output_data[x+y*width] = img_data[x+y*width]>thres ? 1 : 0;
    }
  }
}
void thres_hold_255(uint8 *img_data, uint8 *output_data, int width, int height, int thres)
{
  for(int y=0; y<height; y++){
    for(int x=0; x<width; x++){
      output_data[x+y*width] = img_data[x+y*width]>thres ? 255 : 0;
    }
  }
}

void adaptiveThreshold(uint8* img_data, uint8* output_data, int width, int height, int block, uint8 clip_value)
{
    //assert(block % 2 == 1); // block必须为奇数
  int half_block = block / 2;
  for(int y=half_block; y<height-half_block; y++){
    for(int x=half_block; x<width-half_block; x++){
        // 计算局部阈值
      int thres = 0;
      for(int dy=-half_block; dy<=half_block; dy++){
        for(int dx=-half_block; dx<=half_block; dx++){
          thres += img_data[(x+dx)+(y+dy)*width];
        }
      }
      thres = thres / (block * block) - clip_value;
      // 进行二值化
      output_data[x+y*width] = img_data[x+y*width]>thres ? 255 : 0;
    }
  }
}

float rot_max(float a,float b,float c,float d)
{
    float temp[5];
    temp[0]=a;  temp[1]=b; temp[2]=c; temp[3]=d; temp[4]=a;
    for(int i=0;i<4;i++)  if(temp[i]>=temp[4])   temp[4]=temp[i];
    return temp[4];

}

float rot_min(float a,float b,float c,float d)
{
    float temp[5];
    temp[0]=a;  temp[1]=b; temp[2]=c; temp[3]=d; temp[4]=a;
    for(int i=0;i<4;i++)  if(temp[i]<=temp[4])   temp[4]=temp[i];
    return temp[4];

}

void rot_img_process(void)
{

    //a[3][3]是根据透视变换公式求出的透视变换矩阵
    //变换之后的坐标：rot_x = (a11*x+a12*y+a13)/(a31*x+a32*y+1)
    //变换之后的坐标：rot_y = (a21*x+a22*y+a23)/(a31*x+a32*y+1)
//    pix1[0]=((rot[0][0]*1+rot[0][1]*1+rot[0][2])/(rot[2][0]*1+rot[2][1]*1+1.0));
//    pix1[1]=(rot[1][0]*1+rot[1][1]*1+rot[1][2])/(rot[2][0]*1+rot[2][1]*1+1.0);
//
//    pix2[0]=(rot[0][0]*100+rot[0][1]*1+rot[0][2])/(rot[2][0]*100+rot[2][1]*1+1.0);
//    pix2[1]=(rot[1][0]*100+rot[1][1]*1+rot[1][2])/(rot[2][0]*100+rot[2][1]*1+1.0);
//
//    pix3[0]=(rot[0][0]*1+rot[0][1]*160+rot[0][2])/(rot[2][0]*1+rot[2][1]*160+1.0);
//    pix3[1]=(rot[1][0]*1+rot[1][1]*160+rot[1][2])/(rot[2][0]*1+rot[2][1]*160+1.0);
//
//    pix4[0]=(rot[0][0]*100+rot[0][1]*160+rot[0][2])/(rot[2][0]*100+rot[2][1]*160+1.0);
//    pix4[1]=(rot[1][0]*100+rot[1][1]*160+rot[1][2])/(rot[2][0]*100+rot[2][1]*160+1.0);

//    rot_height = round(rot_max(pix1[0],pix2[0],pix3[0],pix4[0])-rot_min(pix1[0],pix2[0],pix3[0],pix4[0]));
//    rot_width  = round(rot_max(pix1[1],pix2[1],pix3[1],pix4[1])-rot_min(pix1[1],pix2[1],pix3[1],pix4[1]));
//    delta_y = round(abs(rot_min(pix1[0],pix2[0],pix3[0],pix4[0])));
//    delta_x = round(abs(rot_min(pix1[1],pix2[1],pix3[1],pix4[1])));
    for(int i=0;i<ipts0_num;i++)
    {
        rpts0[i][0] = (rot[1][0]*ipts0[i][1]+rot[1][1]*ipts0[i][0]+rot[1][2])/(rot[2][0]*ipts0[i][1]+rot[2][1]*ipts0[i][0]+rot[2][2])+delta_x;
        rpts0[i][1] = (rot[0][0]*ipts0[i][1]+rot[0][1]*ipts0[i][0]+rot[0][2])/(rot[2][0]*ipts0[i][1]+rot[2][1]*ipts0[i][0]+rot[2][2])+delta_y;
    }
    for(int i=0;i<ipts1_num;i++)
    {
        rpts1[i][0] = (rot[1][0]*ipts1[i][1]+rot[1][1]*ipts1[i][0]+rot[1][2])/(rot[2][0]*ipts1[i][1]+rot[2][1]*ipts1[i][0]+rot[2][2])+delta_x;
        rpts1[i][1] = (rot[0][0]*ipts1[i][1]+rot[0][1]*ipts1[i][0]+rot[0][2])/(rot[2][0]*ipts1[i][1]+rot[2][1]*ipts1[i][0]+rot[2][2])+delta_y;
    }
    rpts0_num = ipts0_num;
    rpts1_num = ipts1_num;

}
void image_handle(void)
{
    //搜索边线起始点的方式是给一个固定的搜索起始点横纵坐标，然后向左右在这一行上去找赛道边线的横坐标x1、x2，并利用这个坐标去做边线跟踪
    //为了达到一个类似于阳光算法的效果（不需要调整阈值之类的），我在这一横向找赛道边界坐标的时候利用自适应二值化的方法
    //以找左边线起始点坐标为例，横坐标每向左移动一次，就计算当前这个点的自适应阈值
    //并且为了防止噪点的误判，向左去计算这个点连续三个左点的阈值，这样的话基本上上场调一下自适应算法的两个参数，就可以实现一个类似于阳光算法的效果
    //在后续实验的过程中我发现这个自适应计算的方法可以用sobel+大津法或canny边缘检测算子代替（本质上都是为了在灰度图的基础上保留边线特征，便于搜边线），但由于临近比赛我不太想再去改动程序了

    //再提供一个可以动态扫描边线的例子,实测是可以用的，便于15cm限制高度的摄像头获取赛道边线信息有限的情况下自动去找边线的起始点，但是要给一定的限制使用条件
    /*
    for(;y1>0;y1--){
        for(x1= img_raw.width / 2 - begin_x;x1>3;x1--){
            if (AT_IMAGE(&img_raw, x1 - 1, y1) < OSTU_thres){
                x1_flag = 1;
            }
        }
    }
    if(x1_flag==1) break;
     */
    int x1= img_raw.width / 2 - begin_x, y1 = begin_y;
    ipts0_num = sizeof(ipts0) / sizeof(ipts0[0]);
    int local_thres_left = 0,local_thres_left_num=0;
    for (; x1 > block_size/2; x1--){
        //从给定的起始点开始向左去找左线
        for(int i=1;i<=4;i++){
            //判断连续的四个点，防止噪点误判
            for (int dy = -block_size/2; dy <= block_size/2; dy++) {
                for (int dx = -block_size/2; dx <= block_size/2; dx++) {
                    local_thres_left += AT_IMAGE(&img_raw, x1 - i + dx, y1 + dy);
                }
            }
            local_thres_left /= block_size * block_size;
            local_thres_left -= clip_value;
            if(AT_IMAGE(&img_raw, x1 - i, y1) < local_thres_left)local_thres_left_num++;

        }
        if(local_thres_left_num>=4) {
            local_thres_left_num = 0;
            left_bound_x = x1;                              //用于限制传统车库搜索函数的坐标范围
            break;
        }
        else local_thres_left_num = 0;


    }
    if (AT_IMAGE(&img_raw, x1 -1, y1) < local_thres_left){
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, x1, y1, ipts0, &ipts0_num);
    }
    else ipts0_num = 0;
    int x2 = img_raw.width / 2 + begin_x, y2 = begin_y;
    ipts1_num = sizeof(ipts1) / sizeof(ipts1[0]);
    int local_thres_right = 0,local_thres_right_num=0;

    for(; x2 < img_raw.width - block_size/2; x2++)
    {
        for(int i=1;i<=4;i++){
            for (int dy = -block_size/2; dy <= block_size/2; dy++) {
                for (int dx = -block_size/2; dx <= block_size/2; dx++) {
                    local_thres_right += AT_IMAGE(&img_raw, x2 + i + dx, y2 + dy);
                }
            }
            local_thres_right /= block_size * block_size;
            local_thres_right -= clip_value;
            if(AT_IMAGE(&img_raw, x2 + i, y2) < local_thres_right)local_thres_right_num++;

        }
        if(local_thres_right_num>=4) {
            local_thres_right_num = 0;
            right_bound_x = x2;                               //用于限制传统车库搜索函数的坐标范围
            break;
        }
        else local_thres_right_num = 0;
    }
    if (AT_IMAGE(&img_raw, x2+1, y2) < local_thres_right){
        findline_righthand_adaptive(&img_raw, block_size, clip_value, x2, y2, ipts1, &ipts1_num);
    }

    else ipts1_num = 0;

    // 透视变换
    rot_img_process();

    // 边线滤波
    blur_points(rpts0, rpts0_num, rpts0b, (int) round(line_blur_kernel));
    rpts0b_num = rpts0_num;
    blur_points(rpts1, rpts1_num, rpts1b, (int) round(line_blur_kernel));
    rpts1b_num = rpts1_num;


    // 边线等距采样
    rpts0s_num = sizeof(rpts0s) / sizeof(rpts0s[0]);
    resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, sample_dist * pixel_per_meter);
    rpts1s_num = sizeof(rpts1s) / sizeof(rpts1s[0]);
    resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, sample_dist * pixel_per_meter);
    // 边线局部角度变化率，采用我们的算法可以得到稳定且等距的边线前提下，直接取每个点前后20cm构成一个三点，
         //利用向量的角度计算公式算实际角度即可。为方便判断，
    local_angle_points(rpts0s, rpts0s_num, rpts0a, (int) round(angle_dist / sample_dist));
    rpts0a_num = rpts0s_num;
    local_angle_points(rpts1s, rpts1s_num, rpts1a, (int) round(angle_dist / sample_dist));//angle_dist / sample_dist
    rpts1a_num = rpts1s_num;
    // 角度变化率非极大抑制
        //我们又进行了角度的非极大抑制，保证只留下角度最大的点，即角点。这样算出来的角度很稳定，跟实际也很接近。（前提是透视变换做的正确）
    nms_angle(rpts0a, rpts0a_num, rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);//angle_dist / sample_dist
    rpts0an_num = rpts0a_num;
    nms_angle(rpts1a, rpts1a_num, rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);//angle_dist / sample_dist
    rpts1an_num = rpts1a_num;

    // 左右中线跟踪
    track_leftline(rpts0s, rpts0s_num, rptsc0, (int) round(10.0), pixel_per_meter * ROAD_WIDTH / 2);//
    rptsc0_num = rpts0s_num;
    track_rightline(rpts1s, rpts1s_num, rptsc1, (int) round(10.0), pixel_per_meter * ROAD_WIDTH / 2);//
    rptsc1_num = rpts1s_num;

}
void find_Left_line(uint8 *img_data, uint8 *output ,int block_size, int clip_value, int x, int y)
{
    int half = block_size / 2;
    int step = 0, dir = 0, turn = 0;
    int local_thres = 0;
    for(int y1=half; y1<MT9V03X_H-half; y1++)
     {
            for(int x1=half; x1<x+half; x1++)
            {
                for (int dy = -half; dy <= half; dy++)
                {
                    for (int dx = -half; dx <= half; dx++)
                    {
                        local_thres += img_data[(x1+dx)+(y1+dy)*MT9V03X_W];
                    }
                }
                local_thres /= block_size * block_size;
                local_thres -= clip_value;
                output[x1+y1*MT9V03X_W] = img_data[x1+y1*MT9V03X_W]>local_thres ? 255 : 0;
            }
     }

}

void find_corners() {
    // 识别Y,L拐点
    Ypt0_found = Ypt1_found = Lpt0_found = Lpt1_found = false;
    is_straight0 = rpts0s_num > (1.5 / sample_dist);    //长直道判断初始化
    is_straight1 = rpts1s_num > (1.5 / sample_dist);    //长直道判断初始化
    conf1_max =conf2_max = 0;
    for (int i = 0; i < MIN(rpts0s_num,80); i++) {
        if (rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, rpts0s_num - 1);
        conf1 = 0;
        conf1  = fabs(rpts0a[i]) - (fabs(rpts0a[im1]) + fabs(rpts0a[ip1])) / 2;
        //Y角点阈值
        if (Ypt0_found == false && 40. / 180. * PI < conf1 && conf1 < 66. / 180. * PI && i < 0.7 / sample_dist) {
            Ypt0_rpts0s_id = i;
            Ypt0_found = true;
        }
        //L角点阈值，判断的时候建议用id的值控制车在比较靠近元素时在判断，并对角点及前后两点，这三个点组成的拐点方向进行判定，防止误判，也可用这个方式判别角点的方向
        if(round_type){
            //回环阶段的单独阈值
            if (Lpt0_found == false && 50. / 180. * PI < conf1 && conf1 < 120. / 180. * PI && i<45
                    &&(rpts0s[im1][0]>rpts0s[ip1][0]&&rpts0s[im1][1]>rpts0s[ip1][1])) {
                Lpt0_rpts0s_id = i;
                Lpt0_found = true;
            }
        }
        else{
            //一般情况下的阈值
            if (Lpt0_found == false && 73. / 180. * PI < conf1 && conf1 < 120. / 180. * PI && i<45
                    &&(rpts0s[im1][0]>rpts0s[ip1][0]&&rpts0s[im1][1]>rpts0s[ip1][1]))
            {
                Lpt0_rpts0s_id = i;
                Lpt0_found = true;
            }
        }


        //长直道阈值
        if (conf1 > 15. / 180. * PI && i < 1.5 / sample_dist) is_straight0 = false;
        if (Ypt0_found == true && Lpt0_found == true && is_straight0 == false) break;
        if(conf1>conf1_max)conf1_max = conf1;
    }


    for (int i = 0; i < MIN(rpts1s_num,80); i++) {
        if (rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, rpts1s_num - 1);
        conf2 =0;
        conf2 = fabs(rpts1a[i]) - (fabs(rpts1a[im1]) + fabs(rpts1a[ip1])) / 2;
        if (Ypt1_found == false && 40. / 180. * PI < conf2 && conf2 < 66. / 180. * PI && i < 0.7 / sample_dist) {
            Ypt1_rpts1s_id = i;
            Ypt1_found = true;
        }
        if(round_type){
            if (Lpt1_found == false && 50. / 180. * PI < conf2 && conf2 < 120. / 180. * PI&& i < 45 ) {
                Lpt1_rpts1s_id = i;
                Lpt1_found = true;
            }
        }
        else{
            if (Lpt1_found == false && 73. / 180. * PI < conf2 && conf2 < 120. / 180. * PI&& i < 45 ) {
                Lpt1_rpts1s_id = i;
                Lpt1_found = true;
            }
        }
        if (conf2 > 15. / 180. * PI && i < 1.5 / sample_dist) is_straight1 = false;
        if (Ypt1_found == true && Lpt1_found == true && is_straight1 == false) break;
        if(conf2>conf2_max)conf2_max = conf2;
    }

    // Y点二次检查,依据两角点距离及角点后张开特性
    //但对于无法处理较大尺寸或视野受限的情况下，是无法满足二次检查的要求（因为他要同时看到两个拐点，所以在后续操作中基本用不到二次判断，不用这个个人感觉问题不大）
    if (Ypt0_found && Ypt1_found) {
        float dx = rpts0s[Ypt0_rpts0s_id][0] - rpts1s[Ypt1_rpts1s_id][0];
        float dy = rpts0s[Ypt0_rpts0s_id][1] - rpts1s[Ypt1_rpts1s_id][1];
        float dn = sqrtf(dx * dx + dy * dy);
        if (fabs(dn - 0.45 * pixel_per_meter) < 0.15 * pixel_per_meter) {
            float dwx = rpts0s[clip(Ypt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] -
                        rpts1s[clip(Ypt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0];
            float dwy = rpts0s[clip(Ypt0_rpts0s_id + 50, 0, rpts0s_num - 1)][1] -
                        rpts1s[clip(Ypt1_rpts1s_id + 50, 0, rpts1s_num - 1)][1];
            float dwn = sqrtf(dwx * dwx + dwy * dwy);
            if (!(dwn > 0.7 * pixel_per_meter &&
                  rpts0s[clip(Ypt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] < rpts0s[Ypt0_rpts0s_id][0] &&
                  rpts1s[clip(Ypt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0] > rpts1s[Ypt1_rpts1s_id][0])) {
                Ypt0_found = Ypt1_found = false;
            }
        } else {
            Ypt0_found = Ypt1_found = false;
        }
    }
    if(Ypt0_found&&!Ypt1_found&&rpts1s_num>30)Ypt0_found = false;
    if(Ypt1_found&&!Ypt0_found&&rpts0s_num>30)Ypt1_found = false;


}
void Check_Ramp()
{
    float dx ,dy ,dw;
    for(int i=0;i<30;i++)
    {
        dx = rpts0s[i][0] - rpts1s[i][0];
        dy = rpts0s[i][1] - rpts1s[i][1];
        dw_top = sqrtf(dx * dx + dy * dy);

    }
    if(dw_top>dw_max) dw_max = dw_top;


}
void Cut_Image(void)
{
    for(int i = 1;i<MT9V03X_H;i++)
        for(int j = 1;j<MT9V03X_W;j++)
            if(i%2 == 0&&j%2==0) Bin_Image[i/2][j/2]=global_Img[i][j];


}

float Cal_rot_x(float x,float y){
    //透视变换横坐标变换
    float rot_x;
    rot_x = (rot[1][0]*y+rot[1][1]*x+rot[1][2])/(rot[2][0]*y+rot[2][1]*x+rot[2][2]);
    return rot_x;
}
float Cal_rot_y(float x,float y){
    //透视变换纵坐标变换
    float rot_y;
    rot_y = (rot[0][0]*y+rot[0][1]*x+rot[0][2])/(rot[2][0]*y+rot[2][1]*x+rot[2][2]);
    return rot_y;
}
float Cal_inv_rot_x(float x,float y){
    //逆透视变换横坐标变换
    float inv_rot_x;
    inv_rot_x = (inv_rot[1][0]*y + inv_rot[1][1]*x + inv_rot[1][2])/(inv_rot[2][0]*y+inv_rot[2][1]*x+1);
    return inv_rot_x;


}
float Cal_inv_rot_y(float x,float y){
    //逆透视变换纵坐标变换
    float inv_rot_y;
    inv_rot_y = (inv_rot[0][0]*y + inv_rot[0][1]*x + inv_rot[0][2])/(inv_rot[2][0]*y+inv_rot[2][1]*x+1);
    return inv_rot_y;
}

void lcd_Show_inv_Line(int num,float matrix[][2],float inv_matrix[][2],uint16 color)
{
    //输入一条俯视角下的边线数组，输出逆透视原图视角下的边线数组
    for(int i=0;i<num;i++)
    {
        inv_matrix[i][0] = Cal_inv_rot_x(matrix[i][0],matrix[i][1]);
        inv_matrix[i][1] = Cal_inv_rot_y(matrix[i][0],matrix[i][1]);
    }
        for(int i=0;i<num;i++)
            for(int y=0;y<3;y++)
                if(1<((inv_matrix[i][0]+y)/X_zoom)&&((inv_matrix[i][0]+y)/X_zoom)<101&&1<(inv_matrix[i][1]/Y_zoom)&&(inv_matrix[i][1]/Y_zoom)<64)
                    lcd_drawpoint((inv_matrix[i][0]+y)/X_zoom,inv_matrix[i][1]/Y_zoom,color);
}


