#ifndef AUTOP_REF_CAMERA_PARAM_H
#define AUTOP_REF_CAMERA_PARAM_H

#include <stdbool.h>

#include "tuning.hpp"

extern float K[3][3];
extern float D[4];
extern float H[3][3];
extern float H_inv[3][3];
extern float mapx[RAW_H][RAW_W];
extern float mapy[RAW_H][RAW_W];
extern int invx[IPM_H][IPM_W];
extern int invy[IPM_H][IPM_W];

bool map_inv(float pt0[2], int pt1[2]);

#endif
