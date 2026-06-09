#pragma once

#include <cstdint>

#include "types.hpp"

// 打印单帧详情，只读 runtime_t，不改变 tracking/control 状态。
void print_detail(const runtime_t *rt);

// 打印 live 单行摘要；mid 字段是控制中线坐标，不是 assistant 原图红线。
void print_live(uint32_t frame_id, const runtime_t *rt);

// 取报告用中线起点、预瞄点、预瞄距离和完整前方预瞄门结果。
void mid_points_for_report(const midline_t &mid,
                           int ref_y,
                           point_t *m0,
                           point_t *ml,
                           int *ml_dist,
                           int *max_dist,
                           int *forward_ok);

// 写离线 key=value 报告，不参与实车控制链。
int write_report(const runtime_t *rt, const char *report_path);
