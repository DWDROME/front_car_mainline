#include "yroad.h"
#include "motor.h"
#include "headfile.h"

int16 yroad_speed;
enum yroad_type_e yroad_type = YROAD_NONE;


const char *yroad_type_name[YROAD_NUM] = {
        "YROAD_NONE",
        "YROAD_FOUND", "YROAD_NEAR",
        "YROAD_LEFT_RUN", "YROAD_RIGHT_RUN",
        "YROAD_LEFT_OUT", "YROAD_RIGHT_OUT",
};

extern enum yroad_type_e yroad_type;

// 编码器，防止重复触发等情况
int64_t yroad_encoder = -10000;

// 记录第一圈的转向方向
bool first_right;

// 记录第几个三岔
int8 yroad_cnt = 0;


void check_yroad() {
    bool Yfound = Ypt0_found || Ypt1_found;
    // 状态切换
    //两个Y角点进三叉
    if (yroad_type == YROAD_NONE && Yfound ) {
        yroad_type = YROAD_FOUND;
        Count_dis_Flag=1;
        //yroad_encoder = get_total_encoder();
    }
}

void run_yroad() {
    bool Yfound = Ypt0_found || Ypt1_found;
    // 状态切换
    if (yroad_type == YROAD_FOUND || yroad_type == YROAD_NEAR) {
        // wait for openart

        aim_distance = AIM_DISTENCE;
        if (Yfound && (Ypt0_rpts0s_id < 0.6 / sample_dist || Ypt1_rpts1s_id < 0.6 / sample_dist)) {
            yroad_type = YROAD_NEAR;
        }

        if(if_check_ramp){
            if (yroad_cnt % 2 == 0)track_type = TRACK_LEFT;
            else  track_type = TRACK_LEFT;
        }
        else{
            if (yroad_cnt % 2 == 0)track_type = TRACK_RIGHT;
            else  track_type = TRACK_LEFT;
        }




        if(total_distence>=6500&&!Yfound){
            Count_dis_Flag=0;
            if(if_check_ramp){
                if (yroad_cnt % 2 == 0)yroad_type = YROAD_LEFT_RUN;
                else  yroad_type = YROAD_LEFT_RUN;
            }
            else{
                if (yroad_cnt % 2 == 0)yroad_type = YROAD_RIGHT_RUN;
                else  yroad_type = YROAD_LEFT_RUN;
            }

            yroad_cnt++;
        }

    } else if (yroad_type == YROAD_LEFT_RUN && Yfound ) {
        yroad_type = YROAD_LEFT_OUT;//begin_y=MT9V03X_H*0.85;
        Count_dis_Flag=1;
    } else if (yroad_type == YROAD_RIGHT_RUN && Yfound ) {
        yroad_type = YROAD_RIGHT_OUT;//begin_y=MT9V03X_H*0.85;
        Count_dis_Flag=1;
    } else if (yroad_type == YROAD_LEFT_OUT && !Yfound&&total_distence>=4000) {
        yroad_type = YROAD_NONE;begin_y=BEGIN_Y;
        Count_dis_Flag=0;
    } else if (yroad_type == YROAD_RIGHT_OUT && !Yfound&&total_distence>=4000) {
        yroad_type = YROAD_NONE;begin_y=BEGIN_Y;
        Count_dis_Flag=0;
    }

    if (yroad_type == YROAD_LEFT_RUN || yroad_type == YROAD_LEFT_OUT) {
        track_type = TRACK_LEFT;
    } else if (yroad_type == YROAD_RIGHT_RUN || yroad_type == YROAD_RIGHT_OUT) {
        track_type = TRACK_RIGHT;
    }
}


