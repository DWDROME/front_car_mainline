#ifndef CAMERA_PARAM_H
#define CAMERA_PARAM_H

#include <stdbool.h>

#include "headfile.h"

extern float K[3][3];
extern float D[4];
extern float H[3][3];
extern float H_inv[3][3];
extern float mapx[MT9V03X_CSI_H][MT9V03X_CSI_W];
extern float mapy[MT9V03X_CSI_H][MT9V03X_CSI_W];
extern int invx[MT9V03X_CSI_H][MT9V03X_CSI_W];
extern int invy[MT9V03X_CSI_H][MT9V03X_CSI_W];

bool map_inv(float pt0[2], int pt1[2]);

#endif // CAMERA_PARAM_H
