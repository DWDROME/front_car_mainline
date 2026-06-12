#pragma once

#include "types.hpp"

//----------------------------------------------------------------------------------------------------------------------
//  @brief      仅根据薄视觉输入计算一帧控制输出
//  @param      input 当前帧控制输入；由 ATG/runner 提供 line_found、guide_error、元素状态和停车线
//  @param      ctrl  输出 target_yaw_rate、左右 duty、stop_request 等控制结果
//  @note       该入口不读取编码器和 IMU，主要用于无反馈路径或离线检查。
//----------------------------------------------------------------------------------------------------------------------
void solve_control_input(const control_input_t *input, control_state_t *ctrl);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      带编码器和 IMU yaw-rate 反馈的一帧实车闭环控制
//  @param      input 当前帧控制输入；控制层不再直接依赖 runtime_t.track/cross/ring
//  @param      fb    drive_output_read_feedback() 输出的编码器/陀螺反馈
//  @param      ctrl  输出左右 duty，后续交给 drive_output_apply()
//  @note       主链语义：guide_error -> target_yaw -> yaw_cmd -> target_l/r -> duty。
//----------------------------------------------------------------------------------------------------------------------
void solve_control_input_with_feedback(const control_input_t *input,
                                       const control_feedback_t *fb,
                                       control_state_t *ctrl);
