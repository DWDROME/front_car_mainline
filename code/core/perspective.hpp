#pragma once

#include <cstdint>

#include <opencv2/core.hpp>

#include "types.hpp"

//----------------------------------------------------------------------------------------------------------------------
//  @brief      从静态反查表读取 IPM -> raw 整数坐标
//  @param      ix  IPM x
//  @param      iy  IPM y
//  @param      x   输出 raw x
//  @param      y   输出 raw y
//  @return     int 1 查表有效 / 0 输入越界或该点无效
//----------------------------------------------------------------------------------------------------------------------
int perspective_lookup_ipm_to_raw(int ix, int iy, int *x, int *y);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      根据 raw 图和 ATG inv_rot 生成 IPM 灰度预览图
//  @param      gray     输入 raw 灰度图
//  @param      preview  输出 IPM 预览图
//  @note       采用 IPM -> raw 反向采样，避免正向投影留下空洞；仅用于显示和调试。
//----------------------------------------------------------------------------------------------------------------------
void perspective_preview(const uint8_t gray[RAW_H][RAW_W], cv::Mat *preview);
