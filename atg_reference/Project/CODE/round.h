#ifndef ROUND_H
#define ROUND_H
#include "headfile.h"

enum round_type_e{
    ROUND_NONE = 0,
    ROUND_LEFT_BEGIN ,ROUND_RIGHT_BEGIN,
    ROUND_LEFT_IN    ,ROUND_RIGHT_IN,
    ROUND_LEFT_END   ,ROUND_RIGHT_END
};
void check_round();

void check_round_L();

void check_round_R();

void run_round();

extern enum round_type_e  round_type;

extern int16 round_speed;

extern float round_aim_distance;

extern int16 left_round_cnt,right_round_cnt;

#endif
