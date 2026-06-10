#ifndef _ROAD_H_
#define _ROAD_H_
#include "headfile.h"
enum road_type_e {
    ROAD_NORMAL= 0,
    CURVE_NONE,
    CURVE_NEAR ,
    CURVE_IN,
    CURVE_OUT,
    CURVE_CURVE,
    CURVE_S_CURVE,
    LONG_STRAIGHT,
    SHORT_STRAIGHT,
    Large_Circle,
    Small_Cirlce,
};

enum speed_type_e{
    speed_normal,
    speed_shortfast,
    speed_longfast,
    speed_largecircle,
    speed_smallcircle,
    speed_curve_near,
    speed_curve_in,
    speed_curve_out,
};

extern enum road_type_e road_type;

extern enum speed_type_e speed_type;

void check_road(void);

#endif
