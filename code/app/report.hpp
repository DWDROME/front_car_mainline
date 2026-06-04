#pragma once

#include <cstdint>

#include "types.hpp"

// 打印单帧详情，只读 runtime_t，不改变 tracking/control 状态。
void print_detail(const runtime_t *rt);

// 打印 live 单行摘要；mid 字段是控制中线坐标，不是 assistant 原图红线。
void print_live(uint32_t frame_id, const runtime_t *rt);

// 写离线 key=value 报告，不参与实车控制链。
int write_report(const runtime_t *rt, const char *report_path);
