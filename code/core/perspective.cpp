#include "perspective.hpp"

extern "C" {
float Cal_rot_x(float x, float y);
float Cal_rot_y(float x, float y);
float Cal_inv_rot_x(float x, float y);
float Cal_inv_rot_y(float x, float y);
}

#include <algorithm>
#include <cmath>

// ATG 分支使用 ATG2022 rot/inv_rot 投影函数；算法层本身也走同一套函数。

int perspective_lookup_ipm_to_raw(int ix, int iy, int *x, int *y)
{
    if(x == nullptr || y == nullptr)
    {
        return 0;
    }
    if(ix < 0 || ix >= IPM_W || iy < 0 || iy >= IPM_H)
    {
        return 0;
    }

    const float x0 = Cal_inv_rot_x(static_cast<float>(ix), static_cast<float>(iy));
    const float y0 = Cal_inv_rot_y(static_cast<float>(ix), static_cast<float>(iy));
    if(x0 < 0.0F || y0 < 0.0F || x0 >= RAW_W || y0 >= RAW_H)
    {
        return 0;
    }

    *x = std::clamp(static_cast<int>(std::lround(x0)), 0, RAW_W - 1);
    *y = std::clamp(static_cast<int>(std::lround(y0)), 0, RAW_H - 1);
    return 1;
}

// 俯视预览采用反向采样，避免正向投影留下空洞。
// 对每个 IPM 像素反向采样原图灰度；反算失败或越界处保持白色。
void perspective_preview(const uint8_t gray[RAW_H][RAW_W], cv::Mat *preview)
{
    if(preview == nullptr)
    {
        return;
    }
    *preview = cv::Mat(IPM_H, IPM_W, CV_8UC1, cv::Scalar(255));
    for(int y = 0; y < IPM_H; ++y)
    {
        uint8_t *row = preview->ptr<uint8_t>(y);
        for(int x = 0; x < IPM_W; ++x)
        {
            int x0 = -1;
            int y0 = -1;
            if(!perspective_lookup_ipm_to_raw(x, y, &x0, &y0))
            {
                continue;
            }
            row[x] = gray[y0][x0];
        }
    }
}
