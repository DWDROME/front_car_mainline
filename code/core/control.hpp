#pragma once

#include "types.hpp"

//----------------------------------------------------------------------------------------------------------------------
//  @brief      根据视觉控制输入和可选反馈求解一帧控制输出
//  @param      input 当前帧控制输入；控制层不再直接依赖 runtime_t.track/cross/ring
//  @param      fb    drive_output_read_feedback() 输出的编码器/陀螺反馈；离线路径可传 nullptr
//  @param      ctrl  输出左右 duty，后续交给 drive_output_apply()
//  @note       主链语义：guide_error -> target_yaw -> yaw_cmd -> target_l/r -> duty。
//----------------------------------------------------------------------------------------------------------------------
void solve_control_input(const control_input_t *input,
                         const control_feedback_t *fb,
                         control_state_t *ctrl);
