#pragma once

#include "types.hpp"

// analyze 模式的输入和输出路径。
struct analyze_paths_t
{
    const char *image_path;
    const char *ipm_path;
    const char *report_path;
};

// 单帧分析：视觉 + 无反馈控制 + 可选 IPM 预览和报告，不下发电机。
int analyze(runtime_t *rt, const analyze_paths_t *p);

// 同一 runtime 内重复处理离线帧，用于观察 cross/ring 这类跨帧状态推进。
int replay(runtime_t *rt, const char *image_path, int count, const char *report_path);

// 离线单图：视觉 + 无反馈控制 + 详细打印。
int offline(runtime_t *rt, const char *image_path);

// 实时相机循环：采集 -> 反馈 -> 视觉 -> 控制 -> 下发。
int live(runtime_t *rt);

// 抓帧保存：只采集并写图，不跑视觉/control。
int capture_frame(runtime_t *rt, const char *capture_path);
