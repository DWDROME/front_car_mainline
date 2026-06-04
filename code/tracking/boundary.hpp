#pragma once

#include <cstdint>

#include "types.hpp"

//----------------------------------------------------------------------------------------------------------------------
//  @brief      由 trace 生成主边界
//  @param      tr          输入 raw trace 点列
//  @param      matrix      raw -> ipm 单应矩阵
//  @param      has_matrix  1 使用 IPM / 0 保持 raw pass-through
//  @param      bd          输出边界状态
//  @note       original_pts 保留原图边界；work_pts/now_pts 和 mainline 一样走 perspective_points -> blur_points -> resample_points。
//----------------------------------------------------------------------------------------------------------------------
void build_boundary_from_trace(const trace_t *tr, const double matrix[9], int has_matrix, boundary_t *bd);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      刷新左右边界的 L 角和双 L 配对信息
//  @param      left        左边界状态
//  @param      right       右边界状态
//  @param      left_pts    左边界工作点列，通常是 IPM/pass-through 后的浮点点列
//  @param      left_num    左边界工作点数
//  @param      right_pts   右边界工作点列
//  @param      right_num   右边界工作点数
//  @param      matrix      raw -> ipm 单应矩阵
//  @param      has_matrix  1 使用 IPM / 0 保持 raw pass-through
//  @note       L 角过远会被清掉；左右都找到 L 后再做双 L 宽度复核。
//----------------------------------------------------------------------------------------------------------------------
void refresh_boundary_corners(boundary_t *left,
                              boundary_t *right,
                              const double left_pts[POINT_MAX][2],
                              int left_num,
                              const double right_pts[POINT_MAX][2],
                              int right_num,
                              const double matrix[9],
                              int has_matrix);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      判断边界是否近似直线
//  @param      bd   输入边界状态
//  @return     int  1 近似直线 / 0 弯曲、过短或已有 L 角
//  @note       几何判定按需现算，不常驻在 boundary_t 里；ring 用它判断对侧边界是否恢复直线。
//----------------------------------------------------------------------------------------------------------------------
int boundary_is_straight(const boundary_t *bd);
