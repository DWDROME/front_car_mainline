#pragma once

#include <cstdint>

#include "types.hpp"

// 对齐参考版 camera_param.h：这里只声明静态查表，数组定义放在 ipm_table_generated.cpp。
// 当前表由 3x3 单应矩阵离线生成；后续若补齐 K/D 畸变数据，应重新生成本表，调用侧不再改。
extern const float g_raw_to_ipm_x[RAW_H][RAW_W];
extern const float g_raw_to_ipm_y[RAW_H][RAW_W];
extern const int16_t g_ipm_to_raw_x[IPM_H][IPM_W];
extern const int16_t g_ipm_to_raw_y[IPM_H][IPM_W];
