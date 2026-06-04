#pragma once

#include "types.hpp"

//----------------------------------------------------------------------------------------------------------------------
//  @brief      仅根据当前视觉结果计算一帧控制输出
//  @param      rt    运行时状态；读取 rt->track.guide_error、元素状态和停车线状态
//  @param      ctrl  输出 target_yaw_rate、左右 duty、stop_request 等控制结果
//  @note       该入口不读取编码器和 IMU，主要用于无反馈路径或离线检查；实车闭环优先用 solve_runtime_with_feedback()。
//----------------------------------------------------------------------------------------------------------------------
void solve_runtime(const runtime_t *rt, control_state_t *ctrl);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      带编码器和 IMU yaw-rate 反馈的一帧实车闭环控制
//  @param      rt    运行时状态；视觉输入来自 rt->track.guide_error
//  @param      fb    drive_output_read_feedback() 输出的编码器/陀螺反馈
//  @param      ctrl  输出左右 duty，后续交给 drive_output_apply()
//  @note       主链语义：guide_error -> target_yaw -> yaw_cmd -> target_l/r -> duty。
//              本函数只计算控制量，不直接访问 PWM 硬件。
//----------------------------------------------------------------------------------------------------------------------
void solve_runtime_with_feedback(const runtime_t *rt, const control_feedback_t *fb, control_state_t *ctrl);
