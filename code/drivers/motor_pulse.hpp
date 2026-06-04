#pragma once

// 板端开环诊断入口，不作为正式闭环控制输出。
// p0/p1 = 左/右轮占空(%)，ms = 驱动时长；详见 motor_pulse.cpp 的时序说明。
int run_motor_pulse(int p0, int p1, int ms);
