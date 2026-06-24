#include "Half_check.h"
//*��ͳ����������������⳵���õ��ı���*//
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
    if(Lpt0_found&&rpts0s_num>rpts1s_num) check_Half_left();                //һ���ҵ�90��յ�Ϳ���
    if(Lpt1_found&&rpts1s_num>rpts0s_num) check_Half_right();

}
void check_Half_left()
{
    //Զ�˱�����ȡ
        cross_farline_L();
    // L����μ��
        if (far_Lpt0_found && Lpt0_found)
        {
            float dx = far_rpts0s[far_Lpt0_rpts0s_id][0] - rpts0s[Lpt0_rpts0s_id][0];
            float dy = far_rpts0s[far_Lpt0_rpts0s_id][1] - rpts0s[Lpt0_rpts0s_id][1];
            float dn = sqrtf(dx * dx + dy * dy);
            if (fabs(dn - 0.35 * pixel_per_meter) > 0.35 * pixel_per_meter)    far_Lpt0_found = false;
        }
        is_straight_far_0 = far_rpts0s_num> (0.55 / sample_dist);
    //�ػ���־�����ж������ÿ���
        if(far_ipts0_num < 6 || far_ipts0[far_ipts0_num-5][0]<130||far_ipts0[5][0]>50||far_ipts0[far_ipts0_num-2][1]>far_ipts0[0][1])is_straight_far_0 = false;//||far_ipts0[5][0]>50
        if (far_rpts0s_num>15 && far_ipts0_num >= 6)
        {
            float dx = far_ipts0[5][0] - far_ipts0[far_ipts0_num-5][0];
            float dy = far_ipts0[5][1] - far_ipts0[far_ipts0_num-5][1];
            float dn = sqrtf(dx * dx + dy * dy);
            if (fabs(dn - 0.35 * pixel_per_meter) < 0.10 * pixel_per_meter) {
                is_straight_far_0 = false;
            }
        }
        if(far_Lpt0_found&&circle_type==CIRCLE_NONE&&!is_straight1&&Lpt0_rpts0s_id<10){
            //����ҵ���ͬһ���90��յ㵫��û���ѵ���ֱ��������������ת��ʮ�ִ���
            cross_type = CROSS_HALF;
            garage_type = GARAGE_NONE;
            //��־�ҵ�����ʮ�ֻ�����ʮ��
            Lpt0_found_flag = 1;
        }
        // Circle entry is owned by check_circle(); Half_check only claims CROSS_HALF.


}
void check_Half_right()//����ͬ��
{
     cross_farline_R();
     // L����μ��
     if (far_Lpt1_found && Lpt1_found)
     {
         float dx = far_rpts1s[far_Lpt1_rpts1s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
         float dy = far_rpts1s[far_Lpt1_rpts1s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
         float dn = sqrtf(dx * dx + dy * dy);
         if (fabs(dn - 0.35 * pixel_per_meter) > 0.30 * pixel_per_meter)    far_Lpt1_found = false;
     }
     is_straight_far_1 = far_rpts1s_num> (0.45 / sample_dist);
 //�ػ���־�����ж�
     if(far_ipts1_num < 6 || far_ipts1[far_ipts1_num-3][0]>10||far_ipts1[5][0]<50||(far_ipts1[far_ipts1_num-1][1]<far_ipts1[0][1]))is_straight_far_1 = false;
     if (far_rpts1s_num>15 && far_ipts1_num >= 6)
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
         //��־�ҵ�����ʮ�ֻ�����ʮ��
         Lpt1_found_flag = 1;
     }
     // Circle entry is owned by check_circle(); Half_check only claims CROSS_HALF.
}
