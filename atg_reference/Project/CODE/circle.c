#include "circle.h"
#include "motor.h"
#include "headfile.h"
#define ENCODER_PER_METER   (5800)
int is_large_circle,is_small_circle,circle_count;  //记录赛道有几个圆环及其大小，配合离线调参可以提前预判大小圆环从而进行加减速操作
int circle_in_length=60,circle_in_distance=2000;   //入环时内侧边线长度，入环时编码器记录长度
enum circle_type_e circle_type = CIRCLE_NONE;


const char *circle_type_name[CIRCLE_NUM] = {
        "CIRCLE_NONE",
        "CIRCLE_LEFT_BEGIN", "CIRCLE_RIGHT_BEGIN",
        "CIRCLE_LEFT_IN", "CIRCLE_RIGHT_IN",
        "CIRCLE_LEFT_RUNNING", "CIRCLE_RIGHT_RUNNING",
        "CIRCLE_LEFT_OUT", "CIRCLE_RIGHT_OUT",
        "CIRCLE_LEFT_END", "CIRCLE_RIGHT_END",
};


int64_t circle_encoder;                                     // 编码器，用于防止一些重复触发等。

int none_left_line = 0, none_right_line = 0;                //丢线标志位
int have_left_line = 0, have_right_line = 0;                //重找到线的线标志位

enum
{
    CIRCLE_ENTRY_CONFIRM_FRAMES = 2,
    CIRCLE_IN_DISTANCE_CONFIRM = 2000,
};

static int circle_left_entry_votes;
static int circle_right_entry_votes;

void reset_circle_entry_votes()
{
    circle_left_entry_votes = 0;
    circle_right_entry_votes = 0;
}

void check_circle() {
    if (circle_type != CIRCLE_NONE) {
        reset_circle_entry_votes();
        return;
    }

    // 非圆环模式下，单边L角点, 单边长直道，且当比较靠近近处时才开启判别，防止远端图像畸变产生的误判（凡是id<一个数的都是为了靠近时再识别，在远处识别会有误判）
    const int left_entry = Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 25;
    const int right_entry = !Lpt0_found && Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 25;

    circle_left_entry_votes = left_entry ? circle_left_entry_votes + 1 : 0;
    circle_right_entry_votes = right_entry ? circle_right_entry_votes + 1 : 0;

    if (circle_left_entry_votes >= CIRCLE_ENTRY_CONFIRM_FRAMES) {
        circle_type = CIRCLE_LEFT_BEGIN;
        none_left_line = 0;
        have_left_line = 0;
        Count_dis_Flag=0;
        reset_circle_entry_votes();
    }

    if (circle_right_entry_votes >= CIRCLE_ENTRY_CONFIRM_FRAMES) {
        circle_type = CIRCLE_RIGHT_BEGIN;
        none_right_line = 0;
        have_right_line = 0;
        Count_dis_Flag=0;
        reset_circle_entry_votes();
    }
}

void run_circle() {
    int64_t current_encoder = 1;

    // 左环开始，寻外直道右线
    if (circle_type == CIRCLE_LEFT_BEGIN) {
        track_type = TRACK_RIGHT;
        //先丢左线后有线
        if (rpts0s_num  <2&&!Lpt0_found) { Count_dis_Flag=1;none_left_line++; have_left_line = 0;}  //丢线标志位开启，开始记录编码器距离
        if (rpts0s_num >30&&none_left_line )  have_left_line ++;                                    //经历了一个先丢先再有线的过程，再次出现边线标志位标志位开启
        if (rpts0s_num  <  circle_in_length &&total_distence>circle_in_distance&&have_left_line) {
            //当搜到内环&&内环边线长度小于某个长度（小于的意思是虽然之前我可能搜到了内环，过早切换到内环会非常切内，单轮出界
            //但是这时我仍可以巡外侧长直道行进，但边线长度会随着车往前跑而逐渐变短，当短到一定地步时入环时机合适）&&编码累积了一定的行进距离
            //这些条件可多可少，最好根据自身车速和摄像头视野灵活修改
                circle_type = CIRCLE_LEFT_IN;if_lost_right_line =0;
                none_left_line = 0;
                none_right_line = 0;
                have_left_line = 0;
                have_right_line = 0;
                if_clean_pid = 1;//变积分PID开启标志位
                Count_dis_Flag=0;
                //还原一些边线标志位，并跳转到CIRCLE_LEFT_IN状态
        }
    }
    //入环，寻内圆左线
    else if (circle_type == CIRCLE_LEFT_IN) {
        cross_farline_L();                                           //开启搜索远线
        track_type = TRACK_LEFT;
        if(rpts0s_num>70){                                           //通过内环判断大小圆环，用于速度决策
            is_large_circle = 1;
            is_small_circle= 0;
        }
        else
            is_small_circle = 1;

        if(rpts0s_num<35)Count_dis_Flag=1;
        if(rpts1s_num < 0.2 / sample_dist)none_right_line++;         //右侧长直道丢失
        if((rpts1s_num >25&&none_right_line>1) ||
           (total_distence>CIRCLE_IN_DISTANCE_CONFIRM&&rpts0s_num<circle_in_length&&rpts1s_num>25)){ //低速下右线可能一直可见；需先在 IN 阶段行驶一段距离
            circle_type = CIRCLE_LEFT_RUNNING;
            Count_dis_Flag=0;
            none_right_line = 0;
        }
    }
    //正常巡线，寻外圆右线
    else if (circle_type == CIRCLE_LEFT_RUNNING) {
        track_type = TRACK_RIGHT;
        if (Lpt1_found) {
            //接近出环时,拐点截断处理
            rpts1s_num = Lpt1_rpts1s_id-2;
            rptsc1_num = Lpt1_rpts1s_id-2;
        }
        //满足拐点足够靠近近点时切换到内环循迹
        if ( Lpt1_found&&((Lpt1_rpts1s_id < 0.7/ sample_dist))) {
            circle_type = CIRCLE_LEFT_OUT;
            Count_dis_Flag=0;
            if_lost_right_line =0;
            if_clean_pid = 1;
        }
    }
    //出环，寻内圆
    else if (circle_type == CIRCLE_LEFT_OUT) {
        //小圆容易看不到内侧的环，因此使用cross_farline_R去找赛道对侧的长直道，即可进行补线操作
        cross_farline_R();
        track_type = TRACK_LEFT;
        Count_dis_Flag=1;
        if(rpts1s_num < 5)           none_right_line++;                                          //右侧经历拐点消失后丢线标志位启动
        if((rpts1s_num>30&&!Lpt1_found&&none_right_line>1)||total_distence>4500)                  //右侧重新出现长直道边线或者编码器累计一定的长度强制跳出
        {
            circle_type = CIRCLE_LEFT_END;
            none_right_line= 0;
            Count_dis_Flag=0;
        }
    }
        //走过圆环，寻右线
    else if (circle_type == CIRCLE_LEFT_END) {
        track_type = TRACK_RIGHT;
        broadcast_flag=1;
        Count_dis_Flag=1;
        if (total_distence>=7500) {//此时的条件非常简单，寻外环长直道记录一定的长度防止再次触发圆环标志位，清理还原标志位
        circle_type = CIRCLE_NONE;
        road_type = ROAD_NORMAL;
        begin_y=BEGIN_Y;
        Count_dis_Flag=0;
        aim_distance = AIM_DISTENCE;
        is_large_circle = is_small_circle = 0;
        if_lost_right_line =0;
        if_lost_left_line = 0;
        circle_count++;
        none_right_line = 0;
        have_right_line = 0;
        none_left_line = 0;
        have_left_line = 0;
        }
    }
        //右圆环同理
    else if (circle_type == CIRCLE_RIGHT_BEGIN) {
        track_type = TRACK_LEFT;
        if (rpts1s_num < 10&&!Lpt1_found) { Count_dis_Flag=1;none_right_line++; have_right_line = 0;}
        if (rpts1s_num>30&&none_right_line)have_right_line++;
        if ( rpts1s_num  < circle_in_length &&total_distence>circle_in_distance&&have_right_line)//(0.2 / sample_dist )<rpts1s_num&&rpts1s_num < (0.4 / sample_dist )&&
        {
            circle_type = CIRCLE_RIGHT_IN;
            if_lost_left_line = 0;
            none_right_line = 0;
            none_left_line = 0;
            have_right_line = 0;
            have_left_line = 0;
            circle_encoder = current_encoder;
            Count_dis_Flag=0;
            if_clean_pid = 1;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_IN) {
        cross_farline_R();
        track_type = TRACK_RIGHT;
        if(rpts1s_num>70){
            is_large_circle = 1;
            is_small_circle = 0;
        }
        else             is_small_circle = 1;
        if(rpts1s_num<35)Count_dis_Flag=1;
        if(rpts0s_num < 5)none_left_line++;
        if((rpts0s_num >25&&none_left_line>1) ||
           (total_distence>CIRCLE_IN_DISTANCE_CONFIRM&&rpts1s_num<circle_in_length&&rpts0s_num>25)){
            circle_type = CIRCLE_RIGHT_RUNNING; Count_dis_Flag=0;
            begin_y=BEGIN_Y;
            none_left_line = 0;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_RUNNING) {
        track_type = TRACK_LEFT;
        if (Lpt0_found) {
            rpts0s_num = Lpt0_rpts0s_id-2;
            rptsc0_num = Lpt0_rpts0s_id-2;
        }
        if (Lpt0_found && ((Lpt0_rpts0s_id < 0.7 / sample_dist))) {//||rpts1s_num>=5
            circle_type = CIRCLE_RIGHT_OUT;
            if_lost_left_line = 0;
            if_clean_pid = 1;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_OUT) {
        cross_farline_L();
        track_type = TRACK_RIGHT;
        broadcast_flag=1;
        if(rpts0s_num < 5){
            none_left_line++;
            Count_dis_Flag=1;
        }
        if((rpts0s_num>30&&!Lpt0_found&&none_left_line>=1)||total_distence>4500)
        {
            circle_type = CIRCLE_RIGHT_END;
            none_left_line= 0;
            Count_dis_Flag=0;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_END) {
        track_type = TRACK_LEFT;
        Count_dis_Flag=1;
        if (rpts1s_num < 0.2 / sample_dist) { none_right_line++;Count_dis_Flag=1; }
        if (total_distence>=4000) {
            circle_type = CIRCLE_NONE;
            circle_type= CIRCLE_NONE;
            road_type = ROAD_NORMAL;

            begin_y=BEGIN_Y;
            Count_dis_Flag=0;
            aim_distance = AIM_DISTENCE;
            is_large_circle = is_small_circle = 0;
            if_lost_right_line =0;
            if_lost_left_line = 0;
            circle_count++;
            none_right_line = 0;
            have_right_line = 0;
            none_left_line = 0;
            have_left_line = 0;
        }
    }
}
