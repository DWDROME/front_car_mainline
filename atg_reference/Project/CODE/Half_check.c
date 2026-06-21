#include "Half_check.h"
//*´«Í³µÄÊı°ßÂíÏßÌø±äµã¼ì²â³µ¿âÓÃµ½µÄ±äÁ¿*//
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
    if(Lpt0_found&&rpts0s_num>rpts1s_num) check_Half_left();                //Ò»²àÕÒµ½90¡ã¹Õµã¾Í¿ªÆô
    if(Lpt1_found&&rpts1s_num>rpts0s_num) check_Half_right();

}
void check_Half_left()
{
    //Ô¶¶Ë±ßÏßÌáÈ¡
        cross_farline_L();
    // Lµã¶ş´Î¼ì²é
        if (far_Lpt0_found && Lpt0_found)
        {
            float dx = far_rpts0s[far_Lpt0_rpts0s_id][0] - rpts0s[Lpt0_rpts0s_id][0];
            float dy = far_rpts0s[far_Lpt0_rpts0s_id][1] - rpts0s[Lpt0_rpts0s_id][1];
            float dn = sqrtf(dx * dx + dy * dy);
            if (fabs(dn - 0.35 * pixel_per_meter) > 0.35 * pixel_per_meter)    far_Lpt0_found = false;
        }
        is_straight_far_0 = far_rpts0s_num> (0.55 / sample_dist);
    //»Ø»·±êÖ¾¶ş´ÎÅĞ¶¨£¨²»ÓÃ¿´£©
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
            //Èç¹ûÕÒµ½ÁËÍ¬Ò»²àµÄ90¡ã¹Õµãµ«ÊÇÃ»ÓĞËÑµ½³¤Ö±µÀµÄÌõ¼ş£¬ÔòÌø×ªÖÁÊ®×Ö´¦Àí
            cross_type = CROSS_HALF;
            garage_type = GARAGE_NONE;
            //±êÖ¾ÕÒµ½ÁË×óÊ®×Ö»¹ÊÇÓÒÊ®×Ö
            Lpt0_found_flag = 1;
        }
        //if(Lpt0_rpts0s_id<10&&!far_Lpt0_found&&cross_type == CROSS_NONE&&round_type ==ROUND_NONE) circle_type = CIRCLE_LEFT_BEGIN;
        if(Lpt0_rpts0s_id<5&&!far_Lpt0_found&&is_straight1&&cross_type == CROSS_NONE&&round_type ==ROUND_NONE) {
            // is_straight1 æ˜¯ LS2K ç§»æ¤è¡¥å……çš„å¯¹ä¾§é•¿ç›´é“è¯æ®ï¼Œä¸ check_circle() å·¦ç¯æ­£é—¨ä¸€è‡´ï¼›
            // åŸä½œè€…æ­¤æ·å¾„ä¾èµ–å…¶èµ›é“å…ˆéªŒ(å•è¿‘L+æ— è¿œLåªå¯èƒ½æ˜¯ç¯å²›)ï¼Œå½“å‰èµ›é“æ–œè½¦èº«ä¸¢å³çº¿çš„åå­—ä¼šè¯¯å…¥å·¦ç¯ã€‚
            //Ê×ÏÈ£¬³µ¿â¼ì²éµÄÓÅÏÈ¼¶×î¸ßµ«²¢Ã»ÓĞËÑµ½³µ¿âµÄ±êÖ¾Î»£¬Ôò½øĞĞµ½°ë±ß¼ì²âµÄº¯ÊıÖĞ£¬Æä´ÎÈç¹ûÔÚ°ë±ß¼ì²âÖĞ²»ÊÇÊ®×Ö£¬ÄÇÓĞ¹ÕµãµÄÔªËØÖ»ÄÜÊÇÔ²»·£¨18½ìµÄ¶ÏÂ·ºÍÕÏ°­ÎïĞèÒªÁíÍâµÄ¼ì²â£¡£©
            //ÔÚÎÒ17½ìµ÷³µµÄ¹ı³ÌÖĞ£¬ÓÃÕâÖÖ·½Ê½»ù±¾ÉÏÔªËØÅĞ¶ÏÊÇ²»»á³ö´íµÄ
            circle_type = CIRCLE_LEFT_BEGIN;
            reset_circle_begin_flags();
            reset_circle_entry_votes();
            Count_dis_Flag=0;
        }


}
void check_Half_right()//×óÓÒÍ¬Àí
{
     cross_farline_R();
     // Lµã¶ş´Î¼ì²é
     if (far_Lpt1_found && Lpt1_found)
     {
         float dx = far_rpts1s[far_Lpt1_rpts1s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
         float dy = far_rpts1s[far_Lpt1_rpts1s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
         float dn = sqrtf(dx * dx + dy * dy);
         if (fabs(dn - 0.35 * pixel_per_meter) > 0.30 * pixel_per_meter)    far_Lpt1_found = false;
     }
     is_straight_far_1 = far_rpts1s_num> (0.45 / sample_dist);
 //»Ø»·±êÖ¾¶ş´ÎÅĞ¶¨
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
         //±êÖ¾ÕÒµ½ÁË×óÊ®×Ö»¹ÊÇÓÒÊ®×Ö
         Lpt1_found_flag = 1;
     }
     if(Lpt1_rpts1s_id<5&&!far_Lpt1_found&&is_straight0&&cross_type == CROSS_NONE&&round_type ==ROUND_NONE) {
         // is_straight0 åŒä¸Šï¼šå¯¹ä¾§é•¿ç›´é“è¯æ®ï¼Œä¸ check_circle() å³ç¯æ­£é—¨ä¸€è‡´ã€‚
         circle_type = CIRCLE_RIGHT_BEGIN;
         reset_circle_begin_flags();
         reset_circle_entry_votes();
         Count_dis_Flag=0;
     }
}
