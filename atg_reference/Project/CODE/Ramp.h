#ifndef _RAMP_H_
#define _RAMP_H_
#include "headfile.h"
enum ramp_type_e{
    RAMP_NONE,
    RAMP_NEAR,
    RAMP_UP,
    RAMP_DOWN,
    RAMP_END
};
void Check_ramp();

void Run_Ramp();

extern int16 Ramp_speed;
extern int16 Ramp_Count;
extern enum ramp_type_e  ramp_type;
extern int ramp_numb;
#endif
