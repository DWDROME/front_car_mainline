#include "Half_check.h"
//*传统的数斑马线跳变点检测车库用到的变量*//
float Far_rLine_endpoint_x,Far_rLine_endpoint_y;
float near_rLine_endpoint_x,near_rLine_endpoint_y;
float inv_Slope_point_R[2],inv_Slope_point_L[2];
int find_garage_left_x,find_garage_left_y;
int find_garage_white=1,find_garage_black;
int find_garage_num,find_garage_change_num;
int find_garage;
///
#define PI               3.14159265358979f
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)
void check_Half()
{
    if(Lpt0_found&&rpts0s_num>rpts1s_num) check_Half_left();                //一侧找到90°拐点就开启
    if(Lpt1_found&&rpts1s_num>rpts0s_num) check_Half_right();

}
void check_Half_left()
{
    //远端边线提取
        cross_farline_L();
    // L点二次检查
        if (far_Lpt0_found && Lpt0_found)
        {
            float dx = far_rpts0s[far_Lpt0_rpts0s_id][0] - rpts0s[Lpt0_rpts0s_id][0];
            float dy = far_rpts0s[far_Lpt0_rpts0s_id][1] - rpts0s[Lpt0_rpts0s_id][1];
            float dn = sqrtf(dx * dx + dy * dy);
            if (fabs(dn - 0.35 * pixel_per_meter) > 0.35 * pixel_per_meter)    far_Lpt0_found = false;
        }
        is_straight_far_0 = far_rpts0s_num> (0.55 / sample_dist);
    //回环标志二次判定（不用看）
        if(far_ipts0[far_ipts0_num-5][0]<130||far_ipts0[5][0]>50||far_ipts0[far_ipts0_num-2][1]>far_ipts0[0][1])is_straight_far_0 = false;//||far_ipts0[5][0]>50
        if (far_rpts0s_num>15)
        {
            float dx = far_ipts0[5][0] - far_ipts0[far_ipts0_num-5][0];
            float dy = far_ipts0[5][1] - far_ipts0[far_ipts0_num-5][1];
            float dn = sqrtf(dx * dx + dy * dy);
            if (fabs(dn - 0.35 * pixel_per_meter) < 0.10 * pixel_per_meter) {
                is_straight_far_0 = false;
            }
        }
        if(far_Lpt0_found&&circle_type==CIRCLE_NONE&&!is_straight1&&Lpt0_rpts0s_id<10){
            //如果找到了同一侧的90°拐点但是没有搜到长直道的条件，则跳转至十字处理
            cross_type = CROSS_HALF;
            garage_type = GARAGE_NONE;
            //标志找到了左十字还是右十字
            Lpt0_found_flag = 1;
        }
        //if(Lpt0_rpts0s_id<10&&!far_Lpt0_found&&cross_type == CROSS_NONE&&round_type ==ROUND_NONE) circle_type = CIRCLE_LEFT_BEGIN;
        if(Lpt0_rpts0s_id<5&&!far_Lpt0_found&&cross_type == CROSS_NONE&&round_type ==ROUND_NONE) {
            //首先，车库检查的优先级最高但并没有搜到车库的标志位，则进行到半边检测的函数中，其次如果在半边检测中不是十字，那有拐点的元素只能是圆环（18届的断路和障碍物需要另外的检测！）
            //在我17届调车的过程中，用这种方式基本上元素判断是不会出错的
            circle_type = CIRCLE_LEFT_BEGIN;
            Count_dis_Flag=0;
        }


}
void check_Half_right()//左右同理
{
     cross_farline_R();
     // L点二次检查
     if (far_Lpt1_found && Lpt1_found)
     {
         float dx = far_rpts1s[far_Lpt1_rpts1s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
         float dy = far_rpts1s[far_Lpt1_rpts1s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
         float dn = sqrtf(dx * dx + dy * dy);
         if (fabs(dn - 0.35 * pixel_per_meter) > 0.30 * pixel_per_meter)    far_Lpt1_found = false;
     }
     is_straight_far_1 = far_rpts1s_num> (0.45 / sample_dist);
 //回环标志二次判定
     if(far_ipts1[far_ipts1_num-3][0]>10||far_ipts1[5][0]<50||(far_ipts1[far_ipts1_num-1][1]<far_ipts1[0][1]))is_straight_far_1 = false;
     if (far_rpts1s_num>15)
     {
         float dx = far_ipts1[5][0] - far_ipts1[far_ipts1_num-5][0];
         float dy = far_ipts1[5][1] - far_ipts1[far_ipts1_num-5][1];
         float dn = sqrtf(dx * dx + dy * dy);
         if (fabs(dn - 0.20 * pixel_per_meter) < 0.10 * pixel_per_meter) {
             is_straight_far_1 = false;
         }
     }

     if(far_Lpt1_found&&circle_type==CIRCLE_NONE&&!is_straight0&&Lpt1_rpts1s_id<10){//
         cross_type = CROSS_HALF;
         garage_type = GARAGE_NONE;
         //标志找到了左十字还是右十字
         Lpt1_found_flag = 1;
     }
     if(Lpt1_rpts1s_id<5&&!far_Lpt1_found&&cross_type == CROSS_NONE&&round_type ==ROUND_NONE) {
         circle_type = CIRCLE_RIGHT_BEGIN;
         Count_dis_Flag=0;
     }
}
