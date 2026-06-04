#include "device.hpp"

#include "zf_device_uvc.hpp"

#include <cstdio>
#include <cstring>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace
{
zf_device_uvc g_uvc;
int g_opened = 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      打开 UVC 摄像头并按库默认参数初始化；重复调用直接返回成功
//  @return     int          1 成功 / 0 设备初始化失败
//  @note       当前逐飞库版本只支持 init(path)，width/height/fps 在这里不生效，实际尺寸由采集阶段校验。
//-------------------------------------------------------------------------------------------------------------------
int device_open_camera(const char *path, int width, int height, int fps)
{
    if(g_opened)
    {
        return 1;
    }

    (void)width;
    (void)height;
    (void)fps;

    if(g_uvc.init(path) < 0)
    {
        return 0;
    }
    g_opened = 1;
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从摄像头采集一帧并转换为 RAW_W×RAW_H 的灰度位图，尺寸不符则拒绝
//  @return     int          1 成功 / 0 未初始化、刷新失败或尺寸不匹配
//  @note       不做隐式 resize，避免 raw/IPM 矩阵和角点坐标基准被偷偷改掉。
//-------------------------------------------------------------------------------------------------------------------
int device_capture_gray(uint8_t gray[RAW_H][RAW_W])
{
    if(!g_opened)
    {
        return 0;
    }
    if(g_uvc.wait_image_refresh() < 0)
    {
        return 0;
    }

    cv::Mat img = g_uvc.get_frame_mjpg();
    if(img.empty())
    {
        return 0;
    }

    cv::Mat g;
    if(img.channels() == 3)
    {
        cv::cvtColor(img, g, cv::COLOR_BGR2GRAY);
    }
    else
    {
        g = img;
    }

    if(g.cols != RAW_W || g.rows != RAW_H)
    {
        std::fprintf(stderr,
                     "ERROR: camera frame size %dx%d, expected %dx%d\n",
                     g.cols,
                     g.rows,
                     RAW_W,
                     RAW_H);
        return 0;
    }

    std::memcpy(gray[0], g.data, RAW_W * RAW_H);
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从文件读取灰度图并校验尺寸为 RAW_W×RAW_H 后拷入目标缓冲区
//  @return     int          1 成功 / 0 读取失败或尺寸不匹配
//  @note       离线图片和摄像头采集使用同一尺寸规则。
//-------------------------------------------------------------------------------------------------------------------
int device_load_gray(const char *path, uint8_t gray[RAW_H][RAW_W])
{
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        return 0;
    }

    if(img.cols != RAW_W || img.rows != RAW_H)
    {
        std::fprintf(stderr,
                     "ERROR: image size %dx%d, expected %dx%d: %s\n",
                     img.cols,
                     img.rows,
                     RAW_W,
                     RAW_H,
                     path);
        return 0;
    }

    std::memcpy(gray[0], img.data, RAW_W * RAW_H);
    return 1;
}
