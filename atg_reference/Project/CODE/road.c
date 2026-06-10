#include "road.h"
enum road_type_e  road_type;
enum speed_type_e speed_type;
void check_road(void)
{
    if(!circle_type&&!ramp_type)
    {
        if(ABS(pure_angle_up_up)<0.75&&ABS(pure_angle_up)<0.75&&(road_type == ROAD_NORMAL||road_type == CURVE_S_CURVE))
        {
            road_type = LONG_STRAIGHT;
        }
//        else if(ABS(pure_angle_up)<3.0&&(road_type == LONG_STRAIGHT||road_type == ROAD_NORMAL)){
//            road_type = SHORT_STRAIGHT;
//        }
        else if(ABS(pure_angle)<2.0&&ABS(Guide_up_up)>15&&(road_type ==LONG_STRAIGHT||road_type == SHORT_STRAIGHT))
        {
            road_type = ROAD_NORMAL;
        }
        else if(2.0<ABS(pure_angle)&&ABS(pure_angle)<5.5&&!ramp_type&&!circle_type&&!cross_type&&!round_type&&!garage_type&&(road_type ==CURVE_NONE||road_type == ROAD_NORMAL))
        {
            if(rpts0s_num<40||rpts1s_num<40)road_type =CURVE_NEAR;
            else road_type = CURVE_S_CURVE;
        }
        else if(ABS(pure_angle)>=5.5&&(road_type == CURVE_NEAR||road_type == CURVE_CURVE))
        {
            road_type = CURVE_IN;
        }
        else if(2.0<ABS(pure_angle)&&ABS(pure_angle)<5.5&&road_type == CURVE_IN)
        {
            if(ABS(pure_angle)<2.2){
                if(pure_angle_up_up>4.2||ABS(Guide_up_up)>45)road_type = CURVE_CURVE;
                else                    road_type = CURVE_OUT;
            }
            //if(pure_angle_up_up>4.2&&ABS(pure_angle)<2.2)road_type = CURVE_CURVE;

        }
        else if(ABS(pure_angle)<1.0&&road_type == CURVE_OUT)
        {
            road_type = ROAD_NORMAL;
        }
        else if(road_type == CURVE_S_CURVE&&rpts0s_num<55&&rpts1s_num<55&&ABS(Guide_up_up)>45){
            road_type = CURVE_IN;
        }

    }
//    else
//    {
//        if(is_large_circle){
//            road_type = Large_Circle;
//        }
//        else road_type = Small_Cirlce;
//    }
}
