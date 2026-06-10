/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#include "Cpu0_Main.h"
#include <Bsp.h>
#include <common.h>
#include <Motor.h>
#include <Platform_Types.h>
#include <SEEKFREE_18TFT.h>
#include <SEEKFREE_IIC.h>
#include <SEEKFREE_MPU6050.h>
#include <SEEKFREE_MT9V03X.h>
#include <zf_gpio.h>
#include <zf_stm_systick.h>
#pragma section all "cpu0_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

int pit_time_2ms,pit_time_5ms,pit_time_10ms;                        //串级控制周期控制，周期分别为2ms,5ms,10ms,对应角速度环，角度环，速度环
int pit_Ang_Velocity_Cal=0,pit_Angle_Cal=0,pit_Speed_Cal=0;         //串级控制周期控制开启标志位
int32 PWM_Ang_Velocity_Cal,PWM_Angle_Cal,PWM_Speed_Cal;             //串级控制计算量
int32 PWM_Ang_Velocity_Cal_R,PWM_Angle_Cal_R,PWM_Speed_Cal_R;       //串级控制计算量（右轮）
float Angle_X,Angle_Y,Angle_Z;                                      //DMP角度采集变量
int broadcast_flag=1;
uint8 if_check_ramp = 0;                                            //是否检测三叉内坡道（为线上赛专写的）
uint8 Rot_Img[87][187];                                             //储存透视变换后的图像
uint8 Count_Garage_num = 0;                                         //记录经过的车库次数
int8 show_page,key_pos;
uint16 OSTU_thres;                                                  //大津法阈值
uint8 if_debug_mode = 0 ;                                           //是否开启语音播报
int16 Servo_Mid  ;                                                  //舵机中值
uint8 if_stop_flag =0;                                              //停车标志位
int16 Up_Error;
uint16 Clean_Time_count,Clean_Time_count_flag;                      //坡道检测误判
int16 DisPlay_Flag;                                                 //屏显标志位
int16 total_distence,Ramp_total_distence;                           //编码器累计长度
uint8 Count_dis_Flag=0;                                             //开启：开始累计编码器，关闭：编码器计数清零，用于防止一些重复触发等
uint8 global_Img[MT9V03X_H][MT9V03X_W];                             //备用图像数组，可用于测试二值化，边缘检测算子，透视变换时使用
image_t img_raw = DEF_IMAGE(NULL, MT9V03X_W, MT9V03X_H);            //图像结构体
#define PI               3.14159265358979f
int16 begin_x           =BEGIN_X;                                   //搜索左右边线起始点坐标
int16 begin_y           =BEGIN_Y;                                   //搜索左右边线起始点坐标
int16 thres             =100;
int16 thres_temp          ;                                         //flash中保存的可更改的二值化阈值，用于在上赛场前测试一下灯光强度
int16 block_size        =9;
int16 clip_value        =2;
int16 line_blur_kernel  =7;
float sample_dist       =0.02;
int16 pixel_per_meter   =41;//
float angle_dist        =0.2;
float far_rate          =0.5;
float ROAD_WIDTH        =0.45;
float aim_distance      ;
float aim_distance_temp,aim_distance_far;

//补线
int Make_up0[MT9V03X_HH][2];
int Make_up1[MT9V03X_HH][2];
float Slope_L,Slope_R;
//原图左右边线横坐标
uint8 ipts0_x[MT9V03X_HH];
uint8 ipts1_x[MT9V03X_HH];
//原图左右边线纵坐标
uint8 ipts0_y[MT9V03X_HH];
uint8 ipts1_y[MT9V03X_HH];
//原图左右边线
int ipts0[MT9V03X_HH][2];
int ipts1[MT9V03X_HH][2];
int ipts0_num, ipts1_num;
//变换后左右边线
float rpts0[MT9V03X_HH][2];
float rpts1[MT9V03X_HH][2];
float rpts0_makeup[MT9V03X_HH][2];
float rpts1_makeup[MT9V03X_HH][2];
int rpts0_num, rpts1_num;
// 变换后左右边线+滤波
float rpts0b[MT9V03X_HH][2];
float rpts1b[MT9V03X_HH][2];
float rpts0b_makeup[MT9V03X_HH][2];
float rpts1b_makeup[MT9V03X_HH][2];
int rpts0b_num, rpts1b_num;
// 变换后左右边线+等距采样
float rpts0s[MT9V03X_HH][2];
float rpts1s[MT9V03X_HH][2];
float rpts0s_makeup[MT9V03X_HH][2];
float rpts1s_makeup[MT9V03X_HH][2];
int rpts0s_num, rpts1s_num;
// 左右边线局部角度变化率
float rpts0a[MT9V03X_HH];
float rpts1a[MT9V03X_HH];
int rpts0a_num, rpts1a_num;
// 左右边线局部角度变化率+非极大抑制
float rpts0an[MT9V03X_HH];
float rpts1an[MT9V03X_HH];
int rpts0an_num, rpts1an_num;
// 左/右中线
float rptsc0[MT9V03X_HH][2];
float rptsc1[MT9V03X_HH][2];
int rptsc0_num, rptsc1_num;
// 中线
float (*rpts)[2];
int rpts_num;



// 中线横纵坐标

uint8 rpts_x[MT9V03X_HH];
uint8 rpts_y[MT9V03X_HH];
//变换前中线位置
float inv_rptsn[MT9V03X_HH][2];
// 归一化中线
float rptsn[MT9V03X_HH][2];
int rptsn_num;

// Y角点
int Ypt0_rpts0s_id, Ypt1_rpts1s_id;
bool Ypt0_found, Ypt1_found;

// L角点
int Lpt0_rpts0s_id, Lpt1_rpts1s_id;
int inv_Lpt0_rpts0s_id,inv_Lpt1_rpts1s_id;
bool Lpt0_found, Lpt1_found;

// 长直道
bool is_straight0, is_straight1,is_straight_far_0,is_straight_far_1;



// 弯道
bool is_turn0, is_turn1;

// 当前巡线模式
enum track_type_e track_type = TRACK_RIGHT;

float cx ;//车轮对应点(纯跟踪起始点)//(rot[1][0]*MT9V03X_H*0.78f+rot[1][1]*MT9V03X_W/2+rot[1][2])/(rot[2][0]*MT9V03X_H*0.78f+rot[2][1]*MT9V03X_W/2+1.0)+delta_x;//(float)(MT9V03X_W/2)
float cy ;//车轮对应点(纯跟踪起始点)//(rot[0][0]*MT9V03X_H*0.78f+rot[0][1]*MT9V03X_W/2+rot[0][2])/(rot[2][0]*MT9V03X_H*0.78f+rot[2][1]*MT9V03X_W/2+1.0)+delta_y;//(float)(MT9V03X_H*0.78f)
//舵机控制偏差
float angle, angle_up,pure_angle,pure_angle_up,pure_angle_up_up;
#define SMOTOR_RATE     (2.4)

int16 FPS_Count;                //计算帧率
int16 Encoder_speed;            //编码器
int16 Encoder_speed2;           //编码器

//计算error值的横坐标差值
int aim_idx,aim_idx_up,aim_idx_up_up;
float inv_aim_idx[2],inv_aim_idx_up[2],inv_aim_idx_up_up[2];
int test_flag=1;
//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因为需要我们自己手动调用enableInterrupts();来开启中断的响应。

int range_limit(int x, int low, int up);
int range_limit(int x, int low, int up){
    return x > up ? up : x < low ? low : x;
}

//工程导入到软件之后，应该选中工程然后点击refresh刷新一下                   之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化
//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。
int core0_main(void)
{
	get_clk();//获取时钟频率  务必保留
    lcd_init();                                 //屏幕初始化
    W25QXX_Init();                              //flash初始化
    gpio_init(P33_10,GPO,0,NO_PULL);            //蜂鸣器初始化
    //simiic_init();mpu6050_init();             //陀螺仪初始化，V1.2版本中加入了DMP角度结算这个就可注释掉了，请使用下方IIC_Init，和DMP_Init进行陀螺仪初始化
    //Current_int();                            //电流环初始化
    Key_Init();                                 //五向按键初始化
    seekfree_wireless_init();                   //逐飞无线串口初始化
    mt9v03x_init();                             //摄像头初始化
    ADRC_Init(&ADRC_LMotor,&ADRC_RMotor);       //ADRC结构体初始化
    //Parameter_Init();                         //离线调参初始化（首次向flash内写入数据时使用）
    Parameter_Read();                           //读取flash内保存的参数
    Change_Parameter();                         //按键调参
    Motor_Init();                               //电机初始化
    pit_interrupt_ms(CCU6_0, PIT_CH0, 1);       //1ms中断
    TFmini_Plus_Init();                         //TOF测距模块初始化
    garage_type = (int)GARAGE_OUT_RIGHT;        //选择出库方向
    //等待所有核心初始化完毕
    IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();
	//注：IIC_Init和DMP_Init这两个函数需要放在“等待所有核心初始化完毕”功能函数后才能正常初始化，本工程测试时使用的是MPU6050，如果自己选择其他的传感器记得修改对应内容。
    IIC_Init();
    DMP_Init();//mpu6050DMP初始化
    while (TRUE)
    {
//        adaptiveThreshold(mt9v03x_image[0],global_Img[0],MT9V03X_W,MT9V03X_H,block_size,clip_value);  //全图自适应二值化计算，可在调参时全局显示，不建议在图像处理中使用全局的自适应，计算量过大，有优化算法
        OSTU_thres = otsuThreshold(mt9v03x_image,MT9V03X_W,MT9V03X_H);                                  //计算大津法
        Get_Control();                                                                                  //遥控器

        if(if_stop_flag) {                                                                              //停车标志位，检测到已经入库时将舵机按照进库方向打死，并break停止图像处理
            if(garage_type == GARAGE_IN_LEFT)     pwm_duty(ATOM1_CH1_P33_9,Servo_Middle+60);
            else if(garage_type ==GARAGE_IN_RIGHT)pwm_duty(ATOM1_CH1_P33_9,Servo_Middle-60);
            break;
        }

        if(mt9v03x_finish_flag)
         {

            FPS_Count++;

 #if 1
                 img_raw.data = mt9v03x_image[0];
                 image_handle();                                                                        //边线提取、滤波、透视变换、等距采样、中线跟踪
                 find_corners();                                                                        //角点提取&筛选
                 //aim_distance = 0.58;                                                                 //aim_distance是赛道当前偏差率的计算点，aim_distance越大表示越用远处的点计算偏差，越小用越近的点计算偏差，通过控制这个参数可以实现调节切内的程度
                 // 单侧线少，切换巡线方向  切外向圆
                 if (rpts0s_num < rpts1s_num / 2 && rpts0s_num < 25) {
                     track_type = TRACK_RIGHT;
                 } else if (rpts1s_num < rpts0s_num / 2 && rpts1s_num < 25) {
                     track_type = TRACK_LEFT;
                 } else if (rpts0s_num < 10 && rpts1s_num > rpts0s_num) {
                     track_type = TRACK_RIGHT;
                 } else if (rpts1s_num < 10 && rpts0s_num > rpts1s_num) {
                     track_type = TRACK_LEFT;
                 }

                 /*元素判断*/
                 //if(!garage_type&&!yroad_type&&!ramp_type)                                                      check_garage(); //这是传统数斑马线跳跃的方式判别车库，是可以用的，判别准确度还是可以的，但在round_type中我使用了一种更为简洁的不需要数斑马线跳变的方式实现车库判别
                 if(!garage_type&&!yroad_type&&!ramp_type&&(circle_type==CIRCLE_RIGHT_BEGIN||circle_type==CIRCLE_LEFT_BEGIN||circle_type==CIRCLE_LEFT_IN||circle_type==CIRCLE_RIGHT_IN
                         ||circle_type==CIRCLE_NONE))
                     check_round();                                                                                               //今年已没有回环的判别，因此这部分只需要看一下这里面用来判别车库的条件就ok
                 if(!yroad_type&&!ramp_type&&!circle_type&&!cross_type&&!round_type&&!garage_type)                check_Half();   //半边检测，用于在丢边的情况下检测十字，圆环等元素
                 if(!circle_type&&!yroad_type&&!garage_type&&!ramp_type)                                          Check_ramp();   //坡道检测
                 //if(!circle_type&&!yroad_type&&!round_type&&!ramp_type)                                         check_cross();  //由于半边检测非常好用，我在后期已经不需要单独判断十字因此注释掉了
                 if(!cross_type &&!yroad_type&&!round_type&&!ramp_type&&!garage_type)                             check_circle(); //检查圆环
                 if(!circle_type&&!ramp_type&&!garage_type)                                                       check_yroad();  //检测三叉
                 /*元素对应执行操作*/
                 if(garage_type&&!yroad_type&&!ramp_type) run_garage();                                                           //执行车库相应操作
                 if(yroad_type == YROAD_NONE&&round_type!=ROUND_NONE&&ramp_type==RAMP_NONE&&!garage_type)         run_round();    //执行回环相应操作（今年没这元素）
                 if(ramp_type!=RAMP_NONE&&!circle_type&&!yroad_type&&!round_type&&!garage_type)                   Run_Ramp();     //执行坡道相应操作
                 if (cross_type != CROSS_NONE&&!circle_type&&!yroad_type&&round_type==ROUND_NONE&&!garage_type)   run_cross();    //执行十字相应操作
                 if (circle_type != CIRCLE_NONE&&!cross_type&&!yroad_type&&round_type==ROUND_NONE&&!garage_type ) run_circle();   //执行圆环相应操作
                 if (!circle_type&&!cross_type&&yroad_type != YROAD_NONE&&round_type==ROUND_NONE&&!garage_type)   run_yroad();    //执行三叉相应操作（今年没这元素）

                 //if(circle_type==CIRCLE_LEFT_OUT||circle_type==CIRCLE_LEFT_END) Beep_on; else  Beep_off; //蜂鸣器检测
                 /********语音播报，需要配合语音播报模块实现*********/
                 if(!if_debug_mode){
                     if(broadcast_flag&&circle_type==CIRCLE_RIGHT_IN){
                         //uart_putstr(UART_2,"<G>右 圆 环");
                         uart_putstr(UART_0,"2");
                         broadcast_flag=0;
                     }
                     if(broadcast_flag&&circle_type==CIRCLE_LEFT_IN){
                         //uart_putstr(UART_2,"<G>左 圆 环");
                         uart_putstr(UART_0,"1");
                         broadcast_flag=0;
                     }
                     if(broadcast_flag&&cross_type){
                         //uart_putstr(UART_2,"<G>十  字");
                         uart_putstr(UART_0,"3");
                         broadcast_flag=0;
                     }
                     if(broadcast_flag&&yroad_type==YROAD_NEAR){
                         //uart_putstr(UART_2,"<G>三 叉 路");
                         uart_putstr(UART_0,"4");
                         broadcast_flag=0;
                     }
                     if(broadcast_flag&&(round_type==ROUND_LEFT_BEGIN||round_type==ROUND_LEFT_END)){
                         //uart_putstr(UART_2,"<G>断 头 左");
                         uart_putstr(UART_0,"5");
                         broadcast_flag=0;
                     }
                     if(broadcast_flag&&(round_type==ROUND_RIGHT_BEGIN||round_type==ROUND_RIGHT_END)){
                         //uart_putstr(UART_2,"<G>断 头 右");
                         uart_putstr(UART_0,"6");
                         broadcast_flag=0;
                     }
                     if(broadcast_flag&&ramp_type){
                         uart_putstr(UART_0,"7");
                         broadcast_flag=0;
                     }
                     if(broadcast_flag&&garage_type){
                         uart_putstr(UART_0,"8");
                         broadcast_flag=0;
                     }
                 }




                 /********圆环补线*********/
                 //效果可详见视频中的边线显示：https://www.bilibili.com/video/BV19B4y1V7aV/?spm_id_from=333.999.0.0
                     if(circle_type==CIRCLE_RIGHT_IN)
                     {
                        //在CIRCLE_RIGHT_IN的这个时候开启了cross_farline_R
                         if(far_Lpt1_found) {
                             //右上拐点找到的情况下，从左下角顶点拉一条线到右上拐点形成补线
                             point_Cal_Line(Cal_rot_x(5,118),Cal_rot_y(5,118),far_rpts1s[far_Lpt1_rpts1s_id][0],far_rpts1s[far_Lpt1_rpts1s_id][1],leftline,&leftline_num);
                             //数组拼接，将补线和右上拐点右侧的部分边线重构
                             Splicing_array(leftline,leftline_num, far_rpts1s, far_Lpt1_rpts1s_id,Splicing_leftline, &Splicing_leftline_num,1);
                             //由于是在俯视角下的变换，因此只需要再做一个等距采样就可以平移了
                             Splicing_leftline_s1s_num = sizeof(Splicing_leftline_s1s) / sizeof(Splicing_leftline_s1s[0]);
                             resample_points(Splicing_leftline, Splicing_leftline_num, Splicing_leftline_s1s, &Splicing_leftline_s1s_num, sample_dist * pixel_per_meter);
                             //中线平移
                             track_leftline(Splicing_leftline_s1s, Splicing_leftline_s1s_num, Splicing_leftline_center, (int) round(2.0), pixel_per_meter * ROAD_WIDTH / 2);//
                             Splicing_leftline_center_num = Splicing_leftline_s1s_num;
                       }
                         else{
                             //在CIRCLE_RIGHT_IN的这个时候开启了cross_farline_R，从右内环向上去找圆环远处的边线，可能在某个角度下会产生误判无法找到拐点，这个时候就直接将右上边线的某个点视作拐点，和左下顶点连线补线
                             if(far_rpts1s_num>10&&far_rpts1s[1][1]>20){
                                 point_Cal_Line(Cal_rot_x(5,118),Cal_rot_y(5,118),far_rpts1s[1][0],far_rpts1s[1][1],leftline,&leftline_num);
                                 //由于是在俯视角下的变换，因此只需要再做一个等距采样就可以平移了
                                 Splicing_leftline_s1s_num = sizeof(Splicing_leftline_s1s) / sizeof(Splicing_leftline_s1s[0]);
                                 resample_points(leftline, leftline_num, Splicing_leftline_s1s, &Splicing_leftline_s1s_num, sample_dist * pixel_per_meter);
                                 //中线平移
                                 track_leftline(Splicing_leftline_s1s, Splicing_leftline_s1s_num, Splicing_leftline_center, (int) round(2.0), pixel_per_meter * ROAD_WIDTH / 2);//
                                 Splicing_leftline_center_num = Splicing_leftline_s1s_num;
                             }

                         }
                     }
                     else if(circle_type==CIRCLE_RIGHT_OUT)
                     {
                         //出环阶段原本是按内环划出去，但为了防止没有线可以寻，在CIRCLE_RIGHT_OUT阶段开启了cross_farline_L，搜到了对侧边线时，将其右端顶点处的某个点和左下角连线补线作为中线
                         point_Cal_Line(far_rpts0s[(int)(far_rpts0s_num-1)][0],far_rpts0s[(int)(far_rpts0s_num-1)][1],Cal_rot_x(5,118),Cal_rot_y(5,118),leftline,&leftline_num);
                         //由于是在俯视角下的变换，因此只需要再做一个等距采样就可以平移了
                         Splicing_leftline_s1s_num = sizeof(Splicing_leftline_s1s) / sizeof(Splicing_leftline_s1s[0]);
                         resample_points(leftline, leftline_num, Splicing_leftline_s1s, &Splicing_leftline_s1s_num, sample_dist * pixel_per_meter);
                         //中线平移
                         track_leftline(Splicing_leftline_s1s, Splicing_leftline_s1s_num, Splicing_leftline_center, (int) round(2.0), pixel_per_meter * ROAD_WIDTH / 2);//
                         Splicing_leftline_center_num = Splicing_leftline_s1s_num;
                     }
                     //右圆环补线同理
                     else if (circle_type==CIRCLE_LEFT_IN)
                     {
                         if(far_Lpt0_found) {
                             point_Cal_Line_2(Cal_rot_x(185,118),Cal_rot_y(185,118),far_rpts0s[far_Lpt0_rpts0s_id][0],far_rpts0s[far_Lpt0_rpts0s_id][1],rightline,&rightline_num);
                             Splicing_array(rightline,rightline_num, far_rpts0s, far_Lpt0_rpts0s_id,Splicing_rightline, &Splicing_rightline_num,1);
                             Splicing_rightline_s0s_num = sizeof(Splicing_rightline_s0s) / sizeof(Splicing_rightline_s0s[0]);
                             resample_points(Splicing_rightline, Splicing_rightline_num, Splicing_rightline_s0s, &Splicing_rightline_s0s_num, sample_dist * pixel_per_meter);
                             track_rightline(Splicing_rightline_s0s, Splicing_rightline_s0s_num, Splicing_rightline_center, (int) round(2.0), pixel_per_meter * ROAD_WIDTH / 2);//
                             Splicing_rightline_center_num = Splicing_rightline_s0s_num;
                         }
                         else{
                             if(far_rpts0s_num>10&&far_rpts0s[1][1]>20){
                                 point_Cal_Line_2(Cal_rot_x(185,118),Cal_rot_y(185,118),far_rpts0s[1][0],far_rpts0s[1][1],rightline,&rightline_num);
                                 Splicing_rightline_s0s_num = sizeof(Splicing_rightline_s0s) / sizeof(Splicing_rightline_s0s[0]);
                                 resample_points(rightline, rightline_num, Splicing_rightline_s0s, &Splicing_rightline_s0s_num, sample_dist * pixel_per_meter);
                                 track_rightline(Splicing_rightline_s0s, Splicing_rightline_s0s_num, Splicing_rightline_center, (int) round(2.0), pixel_per_meter * ROAD_WIDTH / 2);//
                                 Splicing_rightline_center_num = Splicing_rightline_s0s_num;
                             }

                         }
                     }
                     else if(circle_type==CIRCLE_LEFT_OUT)
                     {
                         point_Cal_Line(far_rpts1s[(int)(far_rpts1s_num-1)][0],far_rpts1s[(int)(far_rpts1s_num-1)][1],Cal_rot_x(180,118),Cal_rot_y(180,118),rightline,&rightline_num);
                         Splicing_rightline_s0s_num = sizeof(Splicing_rightline_s0s) / sizeof(Splicing_rightline_s0s[0]);
                         resample_points(rightline, rightline_num, Splicing_rightline_s0s, &Splicing_rightline_s0s_num, sample_dist * pixel_per_meter);
                         track_rightline(Splicing_rightline_s0s, Splicing_rightline_s0s_num, Splicing_rightline_center, (int) round(5.0), pixel_per_meter * ROAD_WIDTH / 2);//
                         Splicing_rightline_center_num = Splicing_rightline_s0s_num;
                     }
                     ////
                     ///



                 // 中线跟踪
                     //十字的CROSS_IN和CROSS_HALF和车库的GARAGE_FOUND_LEFT和GARAGE_FOUND_RIGHT都是使用远线控制通过，这样的方法可以使得十字不需要补线，车库不需要对斑马线进行任何操作就能通过
                 if (cross_type != CROSS_IN&&cross_type != CROSS_HALF&&garage_type !=  GARAGE_FOUND_LEFT&&garage_type !=GARAGE_FOUND_RIGHT) {//
                     //当不满足上述情况时分为两种情况：1、需要补线进入的圆环的几个阶段CIRCLE_RIGHT_IN、和CIRCLE_LEFT_IN、CIRCLE_RIGHT_OUT、CIRCLE_LEFT_OUT这几个在run_circle函数中已经扫描到了远端的边线，并且在前面操作中对补线数组完成了拼接、等距采样、左右线平移等操作
                     //由于当年比赛中全部是r50的小圆，所以在这边进环阶段我都是默认开启了补线，但对于r60以上的大环可能边线状况会好很多，可以在这里加一个判断是否需要补线才能循迹。
                     if(circle_type==CIRCLE_RIGHT_OUT||circle_type==CIRCLE_RIGHT_IN){
                             rpts = Splicing_leftline_center;
                             rpts_num = Splicing_leftline_center_num;

                     }
                     else if(circle_type==CIRCLE_LEFT_OUT||circle_type==CIRCLE_LEFT_IN){
                         rpts = Splicing_rightline_center;
                         rpts_num = Splicing_rightline_center_num;
                     }
                     else{
                         //一般情况下的左右线切换到中线
                         if (track_type == TRACK_LEFT) {
                             rpts = rptsc0;
                             rpts_num = rptsc0_num;
                         } else {
                             rpts = rptsc1;
                             rpts_num = rptsc1_num;
                         }
                     }

                 }
                 else {
                     //十字和车库根据远线控制
                     if (track_type == TRACK_LEFT) {
                         //对拐点id之前的点做截断处理舍弃掉
                         track_leftline(far_rpts0s + far_Lpt0_rpts0s_id, range_limit(far_rpts0s_num - far_Lpt0_rpts0s_id -1,0,far_rpts0s_num), rpts,
                                        (int) round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
                         rpts_num = range_limit(far_rpts0s_num - far_Lpt0_rpts0s_id,0,far_rpts0s_num);
                     }

                     if(track_type == TRACK_RIGHT){
                         track_rightline(far_rpts1s + far_Lpt1_rpts1s_id, far_rpts1s_num - far_Lpt1_rpts1s_id, rpts,
                                         (int) round(angle_dist / sample_dist), pixel_per_meter * ROAD_WIDTH / 2);
                         rpts_num = far_rpts1s_num - far_Lpt1_rpts1s_id;
                     }
                 }
                 float H_zoom = 0.98f;
                 float Half_width = MT9V03X_W/2;
                 // 车轮对应点(纯跟踪起始点)cx,cy
                 cx = (rot[1][0]*MT9V03X_H*H_zoom+rot[1][1]*Half_width+rot[1][2])/(rot[2][0]*MT9V03X_H*H_zoom+rot[2][1]*Half_width+rot[2][2]);
                 cy = (rot[0][0]*MT9V03X_H*H_zoom+rot[0][1]*Half_width+rot[0][2])/(rot[2][0]*MT9V03X_H*H_zoom+rot[2][1]*Half_width+rot[2][2]);
                 // 找最近点(起始点中线归一化)
                 float min_dist = 10000;
                 int begin_id = 0;
                 for (int i = 0; i < rpts_num; i++) {

                     float dx = rpts[i][0] - cx;
                     float dy = rpts[i][1] - cy;
                     float dist = sqrt(dx * dx + dy * dy);
                     if (dist < min_dist) {
                         min_dist = dist;
                         begin_id = i;

                     }
                 }
                 // 中线有点，同时最近点不是最后几个点
                 if (begin_id >= 0 && rpts_num - begin_id >= 2) {
                     // 归一化中线
                     rpts[begin_id][0] = cx;
                     rpts[begin_id][1] = cy;
                     rptsn_num = sizeof(rptsn) / sizeof(rptsn[0]);
                     resample_points(rpts + begin_id, rpts_num - begin_id, rptsn, &rptsn_num, sample_dist * pixel_per_meter);
                     // 预锚点位置
                     aim_idx = (int)clip(round(aim_distance / sample_dist), 0, rptsn_num - 1);
                     aim_idx_up = (int)clip(round(AIM_DISTANCE_UP / sample_dist), 0, rptsn_num - 1);
                     aim_idx_up_up = (int)clip(round(AIM_DISTANCE_UP_UP / sample_dist), 0, rptsn_num - 1);
                     // 预锚点在原图中的坐标位置
                     inv_aim_idx[0] = Cal_inv_rot_x(rptsn[aim_idx][0],rptsn[aim_idx][1]);
                     inv_aim_idx[1] = Cal_inv_rot_y(rptsn[aim_idx][0],rptsn[aim_idx][1]);
                     for(int i=0;i<rptsn_num;i++)
                     {
                         //变换前中线位置，用于在原图中显示中线
                         inv_rptsn[i][0] = Cal_inv_rot_x(rptsn[i][0],rptsn[i][1]);
                         inv_rptsn[i][1] = Cal_inv_rot_y(rptsn[i][0],rptsn[i][1]);
                     }

                     //由于是固定视角的透视变换，因此单线平移对于坡道来说就会出现畸变，因此我采用了预瞄点位置上的左右边线加权和的方式提取坐标误差用于坡道控制
                     //更建议多取预瞄点位置附近几行算一下左右边线平均误差，或使用电磁循迹
                     Up_Error = (ipts0[aim_idx][0]+ipts1[aim_idx][0])/2-MT9V03X_W/2;
                     Up_Error = -Up_Error/2;
                     Up_Error = clip(Up_Error,-60,60);



                     // 计算远锚点偏差值
                     float dx    = rptsn[aim_idx][0] - cx;
                     float dy    = cy - rptsn[aim_idx][1] + 0.2 * pixel_per_meter;
                     float dn    = sqrt(dx * dx + dy * dy);
                     // 计算远远锚点偏差值
                     float dx_up = rptsn[aim_idx_up][0] - cx;
                     float dy_up = cy - rptsn[aim_idx_up][1] + 0.2 * pixel_per_meter;
                     float dn_up    = sqrt(dx_up * dx_up + dy_up * dy_up);
                     // 计算远远远锚点偏差值
                     float dx_up_up = rptsn[aim_idx_up_up][0] - cx;
                     float dy_up_up = cy - rptsn[aim_idx_up_up][1] + 0.2 * pixel_per_meter;

                     // 纯跟踪算法
                     pure_angle = -atanf(pixel_per_meter * 2 * 0.2 * dx / dn / dn) / PI * 180 / SMOTOR_RATE;
                     pure_angle_up = -atanf(pixel_per_meter * 2 * 0.2 * dx_up / dn_up / dn_up) / PI * 180 / SMOTOR_RATE;
                     //用于后轮差速的偏差值
                     Guide = round((rptsn[clip(aim_idx,0,rptsn_num-1)][0]- cx))*fabs(pure_angle);
                     Guide = clip(Guide,-60,60);
                     //一个用于速度决策的前瞻，位置位于预瞄点的前方
                     Guide_up = round((rptsn[clip(aim_idx_up,0,rptsn_num-1)][0]- cx))*fabs(pure_angle_up)/2.5;
                     Guide_up = clip(Guide_up,-60,60);


                     #if 1
                     //分段PID，针对不同元素给不同的值
                     if(circle_type == CIRCLE_LEFT_RUNNING||circle_type ==CIRCLE_RIGHT_RUNNING|| circle_type==CIRCLE_LEFT_END||circle_type==CIRCLE_RIGHT_END)
                     {
                         //后期因为想要追r50小圆的极限速度将圆环pid细分为了几个阶段，但我在3.15速度一下给一个pid就能跑完
                         angle    = PID_Realize_float(&Angle_PID, Angle,pure_angle,0);
                     }
                     else if(circle_type ==CIRCLE_LEFT_OUT||circle_type ==CIRCLE_RIGHT_OUT){
                         //后期因为想要追r50小圆的极限速度将圆环pid细分为了几个阶段，但我在3.15速度一下给一个pid就能跑完
                         angle    = PID_Realize_float(&Angle_PID, circle_end_pid,pure_angle,0);

                     }
                     else if(circle_type ==CIRCLE_RIGHT_IN||circle_type ==CIRCLE_LEFT_IN){
                         //后期因为想要追r50小圆的极限速度将圆环pid细分为了几个阶段，但我在3.15速度以下给一个pid就能跑完，不是追速度没必要细分的这么多
                         angle    = PID_Realize_float(&Angle_PID, circle_in_pid,pure_angle,0);
                     }
                     else if(ramp_type!=RAMP_NONE)
                     {
                         //坡道控制，建议电磁
                            angle = PID_Realize_float(&Angle_PID, Ramp_pid,Up_Error,0);//Guide

                     }
                     else if(garage_type == GARAGE_OUT_LEFT||garage_type == GARAGE_OUT_RIGHT)
                     {
                         //出库
                         angle    = PID_Realize_float(&Angle_PID, Direct,pure_angle,0);
                     }
                     else if(round_type){
                         //回环的出环阶段非常容易碰边界，因此这个阶段给一个单独的值
                         if(round_type==ROUND_LEFT_END||round_type==ROUND_RIGHT_END) angle = PID_Realize_float(&PID_Round, Round_PID,pure_angle,0);
                         else    angle = PID_Realize_float(&PID_Round, Round_IN_PID,pure_angle,0);
                     }
                     else if(yroad_type){
                         //三叉和普通弯道上一个值，这里使用模糊pid
                         angle    = fuzzy_PID_Realize(&Angle_PID, pure_angle   ,0,1);
                     }
                     else{
                         //普通弯道上使用模糊pid，模糊pid需自行研究
                         angle    = fuzzy_PID_Realize(&Angle_PID, pure_angle   ,0,1);
                     }
#endif
                     //舵机输出
                     pwm_duty(ATOM1_CH1_P33_9,Servo_Middle-clip(angle,-59,59));


                 }
                 else {

                     // 中线点过少(出现问题)，则不控制舵机
                     rptsn_num = 0;

                 }
                 if(DisPlay_Flag)
                     {
                     if(!thres){
                         //*图显边线*//

                         //圆环补线
                         if(circle_type==CIRCLE_RIGHT_IN)
                         {
                             if(far_Lpt1_found) {
                                 lcd_Show_inv_Line(Splicing_leftline_num,Splicing_leftline,inv_Splicing_leftline,RED);
                                 lcd_Show_inv_Line(Splicing_leftline_center_num,Splicing_leftline_center,inv_Splicing_leftline,RED);
                             }
                         }
                         else if(circle_type==CIRCLE_RIGHT_OUT||circle_type==CIRCLE_RIGHT_END)
                         {
                             if(Lpt0_found&&far_rpts0s_num>0) {
                                 lcd_Show_inv_Line(leftline_num,leftline,inv_leftline,GREEN);
                                 lcd_Show_inv_Line(Splicing_leftline_center_num,Splicing_leftline_center,inv_Splicing_leftline,RED);
                             }
                             else{
                                 if (rpts0s_num < 0.6 / sample_dist){
                                     lcd_Show_inv_Line(leftline_num,leftline,inv_leftline,GREEN);
                                     lcd_Show_inv_Line(Splicing_leftline_center_num,Splicing_leftline_center,inv_Splicing_leftline,RED);
                                 }
                             }
                         }
                         else if (circle_type==CIRCLE_LEFT_IN)
                         {
                             if(far_Lpt0_found) {
                                 lcd_Show_inv_Line(Splicing_rightline_center_num,Splicing_rightline_center,inv_Splicing_rightline,RED);
                                 lcd_Show_inv_Line(Splicing_rightline_num,(int)Splicing_rightline,inv_Splicing_rightline,GREEN);
                             }
                         }
                         else if(circle_type==CIRCLE_LEFT_OUT||circle_type==CIRCLE_LEFT_END)
                         {
                             if(Lpt1_found) {
                                 lcd_Show_inv_Line(Splicing_rightline_center_num,Splicing_rightline_center,inv_Splicing_rightline,RED);
                                 lcd_Show_inv_Line(rightline_num,rightline,inv_rightline,RED);
                             }
                             else{
                                 if (rpts1s_num < 0.6 / sample_dist){
                                     lcd_Show_inv_Line(Splicing_rightline_center_num,Splicing_rightline_center,inv_Splicing_rightline,RED);
                                     lcd_Show_inv_Line(rightline_num,rightline,inv_rightline,RED);
                                 }

                             }
                         }

                             //起始点
                             lcd_drawpoint(  (int)((img_raw.width / 2 - begin_x)/X_zoom) , (int)(begin_y/Y_zoom) , RED   );
                             lcd_drawpoint(  (int)((img_raw.width / 2 + begin_x)/X_zoom) , (int)(begin_y/Y_zoom) , RED   );
                             lcd_drawpoint(  (int)(12/X_zoom) ,(int)((begin_y-18)/Y_zoom),GREEN);
                             lcd_drawpoint(  (int)(148/X_zoom),(int)((begin_y-18)/Y_zoom),GREEN);
                             //原图像边线
                             if(DisPlay_Flag)for(int i=0;i<ipts0_num;i++)for(int y=0;y<3;y++)if(1<(ipts0[i][0]+y)/X_zoom&&(ipts0[i][0]+y)/X_zoom<101&&1<ipts0[i][1]/Y_zoom&&ipts0[i][1]/Y_zoom<64)lcd_drawpoint((int)(ipts0[i][0]+y)/X_zoom,(int)ipts0[i][1]/Y_zoom,RED);
                             if(DisPlay_Flag)for(int i=0;i<ipts1_num;i++)for(int y=0;y<3;y++)if(1<((ipts1[i][0]-y)/X_zoom)&&((ipts1[i][0]-y)/X_zoom)<101&&1<(ipts1[i][1]/Y_zoom)&&(ipts1[i][1]/Y_zoom)<64)lcd_drawpoint((int)((ipts1[i][0]-y)/X_zoom),(int)(ipts1[i][1]/Y_zoom),GREEN);
                             //中线归一化起始点
                             for(int i=-2;i<3;i++) lcd_drawpoint((int)(MT9V03X_W/2+i)/X_zoom,(int)MT9V03X_H*H_zoom/Y_zoom,BLUE);
                             //中线
                             for(int i=0;i<rptsn_num;i++)
                             {
                                 if(1<(inv_rptsn[i][0]/X_zoom)&&(inv_rptsn[i][0]/X_zoom)<101&&1<(inv_rptsn[i][1]/Y_zoom)&&(inv_rptsn[i][1]/Y_zoom)<64) lcd_drawpoint((int)inv_rptsn[i][0]/X_zoom,(int)(inv_rptsn[i][1]/Y_zoom),BLUE);
                             }
                             //预瞄点
                             for(int i=-8;i<8;i++)if(3<(inv_aim_idx[0]/X_zoom+i)&&(inv_aim_idx[0]/X_zoom+i)<99&&3<inv_aim_idx[1]/Y_zoom&&inv_aim_idx[1]/Y_zoom<60)lcd_drawpoint((int)(inv_aim_idx[0]/X_zoom+i),(int)(inv_aim_idx[1]/Y_zoom),RED);
                             //车库跳变点
                             if(garage_type==GARAGE_IN_LEFT ||garage_type==GARAGE_FOUND_LEFT) for(int i=1;i<(int)MT9V03X_W/X_zoom;i++)lcd_drawpoint(i,find_garage_right_y/Y_zoom,RED);
                             if(garage_type==GARAGE_IN_RIGHT||garage_type==GARAGE_FOUND_RIGHT) for(int i=1;i<(int)MT9V03X_W/X_zoom;i++)lcd_drawpoint(i,find_garage_left_y/Y_zoom,YELLOW);

                     }

                         //**屏显参数**//
                         key_pos = Key_Scan();
                         if(key_pos==KEY_UP) {
                             show_page++;
                             lcd_clear(WHITE);
                         }
                         else if(key_pos==KEY_DOWN) {
                             show_page--;
                             lcd_clear(WHITE);
                         }
                         if(show_page>1) {
                             show_page = 0;

                         }
                         else if(show_page<0){
                             show_page = 1;

                         }

                         if(show_page==0){
                             if(TFmini_Plus_Dis>0&&TFmini_Plus_Strong>120)lcd_showint16(105,0,TFmini_Plus_Dis);
                             lcd_showint16(105,1,circle_type);
                             lcd_showint16(105,2,cross_type);
                             lcd_showfloat(105,3,pure_angle,2,2);
                             lcd_showint8(1 ,4,is_straight_far_1);
                             lcd_showint8(35,4,yroad_cnt);
                             lcd_showint8(70,4,yroad_type);//
                             lcd_showfloat(105,4,pure_angle_up,2,2);
                             lcd_showint8(1,5,round_type);
                             lcd_showint8(35,5,ramp_type);
                             lcd_showint8(70,5,road_type);
                             lcd_showint16(105,5,garage_type);
                             lcd_showuint8(1,6,rpts0s_num);
                             lcd_showuint8(35,6,rpts1s_num);//
                             lcd_showfloat(70 ,6,conf3_max*180/PI,3,0);
                             lcd_showfloat(105,6,conf4_max*180/PI,3,0);
                             lcd_showint8(1,7,is_straight0);
                             lcd_showint8(35,7,is_straight1);
                             lcd_showfloat(70,7,conf1_max*180/PI,3,0);
                             lcd_showfloat(105,7,conf2_max*180/PI,3,0);
                         }
                         else if(show_page==1){
                             //
                             lcd_showint16(105,0,Guide);
                             lcd_showuint8(105,1,Splicing_leftline_num);
                             lcd_showint16(105,2,rightline_num);//
                             lcd_showint16(105,3,leftline_num);//
                             lcd_showint16(105,4,Splicing_leftline_s1s_num);
                             lcd_showint16(105,5,TFmini_Plus_Strong);
                             lcd_showint16(105,6,TFmini_Plus_Dis);

                         }


                     }
                 if(DisPlay_Flag==2) {
                     //显示全局自适应二值化
                     adaptiveThreshold(mt9v03x_image[0],global_Img[0],MT9V03X_W,MT9V03X_H,block_size,clip_value);
                     lcd_displayimage032_zoom(global_Img[0],MT9V03X_W,MT9V03X_H,101,64);
                 }
                 else if(DisPlay_Flag==1&&!thres){
                     //显示灰度图
                     lcd_displayimage032_zoom(mt9v03x_image[0],MT9V03X_W,MT9V03X_H,101,64);
                 }
                 else if(DisPlay_Flag==3){
                     //显示固定阈值二值化，阈值可调
                     thres_hold_255(mt9v03x_image[0],global_Img[0],MT9V03X_W,MT9V03X_H,thres);
                     lcd_displayimage032_zoom(global_Img[0],MT9V03X_W,MT9V03X_H,101,64);
                 }
                 else if(DisPlay_Flag == 4){
                     //大津法二值化
                     OSTU_thres = otsuThreshold(mt9v03x_image,MT9V03X_W,MT9V03X_H);
                     thres_hold_255(mt9v03x_image,global_Img,MT9V03X_W,MT9V03X_H,OSTU_thres);//thres
                     lcd_displayimage032_zoom(global_Img[0],MT9V03X_W,MT9V03X_H,101,64);
                 }
                 else if(DisPlay_Flag==5){
                     //从网上找的改进版大津法二值化，但似乎没什么效果
                     int OSTU_thres2;
                     OSTU_thres = otsuThreshold(mt9v03x_image,MT9V03X_W,MT9V03X_H);
                     OSTU_thres2 = Threshold_deal(mt9v03x_image,MT9V03X_W,MT9V03X_H,OSTU_thres);
                     Ostu_Robert(mt9v03x_image,global_Img,OSTU_thres2,31,10,MT9V03X_H);
                     lcd_displayimage032_zoom(global_Img[0],MT9V03X_W,MT9V03X_H,101,64);
                 }
                 if(thres==1){
                     //上位机图传
                     sendimg_binary_CHK(mt9v03x_image[0],MT9V03X_W,MT9V03X_H,OSTU_thres,11);

                 }
                 else if(thres==2){
                     for(int i=0;i<MT9V03X_H;i++){
                         for(int j=0;j<MT9V03X_W;j++){
                             //透视变换中的打标变换方式，可以提高运算速度
                             Rot_Img[y_data[i]][x_data[j+MT9V03X_W*i] ] = mt9v03x_image[i][j];
                         }
                     }

                     lcd_displayimage032_zoom(Rot_Img[0],187,87,101,64);
                 }
                 else if(thres==3){
                     //透视变换之后的图像

                     for(int i=0;i<MT9V03X_W;i++){
                         for(int j = 0;j<MT9V03X_H;j++){
                             int X,Y;
                             X = Cal_rot_x(i,j);
                             Y = Cal_rot_y(i,j);
                             if(0<=Y&&Y<=Cut_height&&0<=X&&X<=Cut_Width) global_Img2[Y][X] = mt9v03x_image[j][i];
                         }
                     }
                     lcd_displayimage032_zoom(global_Img2[0],Cut_Width,Cut_height,140,80);//

                 }
                 else if(thres==4){
                     float pix1[2];
                     for(int i = 0;i<rot_height;i++)
                     {
                         for(int j = 0;j<rot_width;j++)
                         {
                             pix1[0] = Cal_inv_rot_x(j,i);
                             pix1[1] = Cal_inv_rot_y(j,i);
                             if(pix1[0]>=0.5&&pix1[1]>=0.5&&pix1[0]<=MT9V03X_W&&pix1[1]<=MT9V03X_H)
                             {
                                 //逆透视变换实现插值
                                 global_Img2[i][j]=mt9v03x_image[(int)pix1[1]][(int)pix1[0]];//82.126


                             }

                         }
                     }
                     lcd_displayimage032_zoom(global_Img2[0],Cut_Width,Cut_height,101,64);//
                 }


 #endif
                 /**无线图传**/
//                    sendline_clear(0,rot_width/2,rot_height/2);
//                    for(int i=0;i<rpts0s_num;i++) {
//                        ipts0_x[i] = rpts0s[i][0]/2;
//                        ipts0_y[i] = rpts0s[i][1]/2;
//                    }
//                    for(int i=0;i<rpts1s_num;i++) {
//                        ipts1_x[i] = rpts1s[i][0]/2;
//                        ipts1_y[i] = rpts1s[i][1]/2;
//                    }
//                    sendline2(1,ipts0_x,ipts0_y,rpts0s_num);
//                    sendline2(1,ipts1_x,ipts1_y,rpts1s_num);
                 mt9v03x_finish_flag = 0;//在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像

         }

    }
}

#pragma section all restore


