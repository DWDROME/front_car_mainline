#pragma once

#include "types.hpp"

// 初始化逐飞 assistant 上位机连接；失败只影响显示，不改变 tracking/control 主链。
void assistant_init();

// 发送当前帧上位机数据。
// 黄/绿线使用 raw original_pts；红线使用 raw 左右边界行中点，不直接发送 rt->track.mid。
void assistant_tick(const runtime_t *rt, unsigned frame_id);
