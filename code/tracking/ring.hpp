#pragma once

#include "types.hpp"

// ==== 环岛状态机入口 ====
// 读取单侧 L、直线判断、编码器累计值，更新 rt->ring 和检测用边界。
// ring 内部边界补线/截线只服务检测和状态连续，不发布当前帧控制中线。
// cross 已活动时不进入新环岛，元素互斥顺序由 element_process() 统一控制。
void ring_process(runtime_t *rt);
