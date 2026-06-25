# 单侧/no-opposite-anchor 诊断证明设计

本文只设计诊断字段，不批准或实现运行代码。目标是证明剩余问题到底是：

1. 单侧错误身份直接发布了错误 `guide_error`；
2. 单侧弱几何没有发布控制，但提前污染了 `mid_position/width_base`；
3. 视觉输出稳定，问题实际在 yaw/轮速控制。

## 1. 需要证明的最小事实

| 问题 | 必要字段 |
| --- | --- |
| 本帧是不是单侧/no-opposite-anchor | `seed_state` after find，`seed_state` after trace，左右 trace step，左右 trace x range |
| 是否有双侧关系证据 | `trace_identity_reject`，`rpts0s/rpts1s` count，IPM paired order reject bit |
| 是否有 selected side | `mode_work_track_type`，`rptsc0/rptsc1` count |
| selected midline 是否几何成立 | `selected_mid_ok`，`mid.step`，`midline_has_lookahead` result |
| 是否发生 learning | `search_mid_before/after`，`width_base_before/after`，`search_center_updated` |
| learning 是否发生在 publish 前 | `selected_mid_ok` 与 `reject_reason` 同帧对比 |
| 当前控制是否受影响 | `guide_error`，`target_yaw_rate_mrad_s`，`left_duty/right_duty` |

## 2. 建议字段

放在 `track_result_t` 或相邻 debug struct，全部是事实字段。

| 字段 | 含义 | 默认值 |
| --- | --- | --- |
| `seed_state_found` | `find_seeds()` 刚返回后的 seed bit | `0` |
| `seed_state_traced` | `trace_edges()` 过滤后的 seed bit | `0` |
| `search_mid_before` | `update_search_center()` 前 `rt->mid_position` | `-1` |
| `search_mid_after` | `update_search_center()` 后 `rt->mid_position` | `-1` |
| `width_base_before` | `update_search_center()` 前 `rt->width_base` | `-1` |
| `width_base_after` | `update_search_center()` 后 `rt->width_base` | `-1` |
| `search_center_updated` | 本帧是否实际调用并写回 search center | `0` |
| `search_center_allow_width` | 本帧是否允许 `width_base` 低通 | `0` |
| `left_trace_min_x/max_x` | 左 raw trace x 范围 | `-1/-1` |
| `right_trace_min_x/max_x` | 右 raw trace x 范围 | `-1/-1` |
| `rpts0s_num_dbg` | 左工作重采样点数 | `-1` |
| `rpts1s_num_dbg` | 右工作重采样点数 | `-1` |
| `rptsc0_num_dbg` | 左边界外扩候选中线点数 | `-1` |
| `rptsc1_num_dbg` | 右边界外扩候选中线点数 | `-1` |
| `selected_mid_ok` | `build_selected_midline()` 返回值 | `-1` |
| `selected_has_lookahead` | `midline_has_lookahead()` 结果，仅记录 | `-1` |

可选字段，如果要证明 `build_rptsn()` attach 问题：

| 字段 | 含义 |
| --- | --- |
| `rptsn_begin_id` | 归一化时选中的 begin index |
| `rptsn_attach_dist2` | 覆盖 `work[0]=cx/cy` 前，候选点到控制参考点的距离平方 |
| `rptsn_work_num` | begin 后剩余输入点数 |

这三个最好由 `build_rptsn()` owner 记录，避免调用方重复猜 begin 逻辑。

## 3. 最小文件范围

第一阶段只做离线/detail/report，不改 live changed-state。

| 文件 | 作用 |
| --- | --- |
| `code/types.hpp` | 给 `track_result_t` 增加 debug 字段，或增加一个小 debug struct |
| `code/tracking/mainline.cpp` | 在 `find_seeds()`、`trace_edges()`、`build_frame_boundaries_and_candidates()`、`update_search_center()`、`build_selected_midline()` 处记录事实 |
| `code/app/report.cpp` | 在 `print_detail()` 和 `write_report()` 输出字段 |
| `code/tracking/imgproc.hpp/.cpp` | 可选：如果要记录 `build_rptsn()` begin/attach，则加 debug 指针参数 |

第二阶段如果真实 live 需要证明 quiet drift：

| 文件 | 作用 |
| --- | --- |
| `code/app/report.cpp` | 在 `make_live_state_signature()` 加 coarse proof bucket，或新增显式诊断模式 |

默认不要让 live 每次数值抖动都 beep。

## 4. 不允许顺手改的东西

诊断 patch 不允许改变：

- `track_type`
- `guide_error`
- `mid_position`
- `width_base`
- `rpts/rptsc` 候选点
- `publish_track_result()` gate
- `midline_has_lookahead()` gate
- duty / yaw / PID 参数
- ring/cross 状态机

如果任何行为分支要改，必须拆成单独 behavior patch。

## 5. 诊断后如何读结论

| 观察 | 结论 |
| --- | --- |
| 单侧、无 opposite anchor、`selected_mid_ok < k_min_border_step`，但 `search_center_updated=1` | learning-order 污染成立，优先实现 learning-order guard |
| 单侧、无 opposite anchor、`selected_mid_ok >= k_min_border_step`，`guide_error` 明显跳 | 当前-frame visual control 风险，learning-order guard 不够 |
| `guide_error` 稳定，yaw/duty 大幅摆 | 视觉不是主因，转控制/IMU/轮速审计 |
| IPM 反序 bit 触发且 `search_center_updated=0` | `d2ccaf0` 工作正常 |
| 双侧 trace 同行反序或过 seed 被拒绝 | raw identity gate 工作正常 |

## 6. 推荐实施顺序

1. 先只加 detail/report 字段，不碰 live beep。
2. 用真实单侧/直道问题帧或连续帧看 `search_center_updated` 与
   `selected_mid_ok/reject_reason/guide_error`。
3. 如果证明 learning-order 污染，再实施 learning-order guard。
4. 如果证明 visual control 风险但 learning-order guard 不够，才讨论新的
   single-side identity predicate。

