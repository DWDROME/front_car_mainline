#pragma once

#include "types.hpp"

// 初始化逐飞 assistant 上位机连接；失败只影响显示，不改变 tracking/control 主链。
void assistant_init(void);

// 发送当前帧上位机数据。
// 上位机线和角点通过 vision_view 读取；runtime_t 只提供灰度底图。
void assistant_tick(const runtime_t *rt, unsigned frame_id);
