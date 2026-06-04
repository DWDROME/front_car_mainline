#include "perspective.hpp"

#include "clip.hpp"
#include "ipm_table_generated.hpp"

// 静态查表对齐参考版 mapx/mapy 用法：raw 点先查表，再进入点列平滑/重采样。

// raw -> IPM：查 float 表 g_raw_to_ipm_x/y；表值 <0 表示该 raw 像素落在 IPM 视野外，返回 0。
int perspective_lookup_raw_to_ipm(int x, int y, double *ix, double *iy)
{
    if(ix == nullptr || iy == nullptr)
    {
        return 0;
    }
    if(x < 0 || x >= RAW_W || y < 0 || y >= RAW_H)
    {
        return 0;
    }

    const float x0 = g_raw_to_ipm_x[y][x];
    const float y0 = g_raw_to_ipm_y[y][x];
    if(x0 < 0.0F || y0 < 0.0F)
    {
        return 0;
    }

    *ix = x0;
    *iy = y0;
    return 1;
}

// IPM -> raw 反查：查 int16 表 g_ipm_to_raw_x/y；表值 <0 表示该 IPM 像素无原图对应，返回 0。
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

    const int x0 = g_ipm_to_raw_x[iy][ix];
    const int y0 = g_ipm_to_raw_y[iy][ix];
    if(x0 < 0 || y0 < 0)
    {
        return 0;
    }

    *x = x0;
    *y = y0;
    return 1;
}

// 投影一个 point_t 到 IPM；失败或越界时 dst 置为 (-1,-1)，ok 写 0。
void perspective_point(const double matrix[9], const point_t *src, point_t *dst, int *ok)
{
    (void)matrix;

    double x = 0.0;
    double y = 0.0;
    int valid = 0;

    if(src != nullptr && dst != nullptr)
    {
        valid = perspective_lookup_raw_to_ipm(src->x, src->y, &x, &y);
        if(valid)
        {
            dst->x = round_i(x);
            dst->y = round_i(y);
        }
        else
        {
            dst->x = -1;
            dst->y = -1;
        }
    }

    if(ok != nullptr)
    {
        *ok = valid;
    }
}

// 俯视预览采用反向采样，避免正向投影留下空洞。
// 对每个 IPM 像素反向采样原图灰度；反算失败或越界处保持白色。
void perspective_preview(const uint8_t gray[RAW_H][RAW_W], const double matrix[9], cv::Mat *preview)
{
    (void)matrix;

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
