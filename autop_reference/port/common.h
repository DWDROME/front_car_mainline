#ifndef AUTOP_REFERENCE_PORT_COMMON_H
#define AUTOP_REFERENCE_PORT_COMMON_H

#include "headfile.h"

static inline int autop_reference_project_points_until_invalid(
    const int pts_in[][2],
    int pts_num,
    float pts_out[][2],
    float raw_to_ipm_x[MT9V03X_CSI_H][MT9V03X_CSI_W],
    float raw_to_ipm_y[MT9V03X_CSI_H][MT9V03X_CSI_W])
{
    int out_num = 0;
    for(int i = 0; i < pts_num; i++)
    {
        const int x = pts_in[i][0];
        const int y = pts_in[i][1];
        if(x < 0 || x >= MT9V03X_CSI_W || y < 0 || y >= MT9V03X_CSI_H)
        {
            break;
        }

        const float ipm_x = raw_to_ipm_x[y][x];
        const float ipm_y = raw_to_ipm_y[y][x];
        if(ipm_x < 0.0f || ipm_y < 0.0f)
        {
            break;
        }

        pts_out[out_num][0] = ipm_x;
        pts_out[out_num][1] = ipm_y;
        out_num++;
    }
    return out_num;
}

#endif
