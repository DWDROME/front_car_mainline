# 当前完成度审计

本文用于防止把“分析收敛”误报为“问题完全解决”。当前任务仍是
`in_progress`，没有理由标记完成。

## 1. 用户核心要求拆解

| 要求 | 当前证据状态 | 结论 |
| --- | --- | --- |
| 对照参考版，不要自造方案 | 已完成多轮 RT1064 / 当前代码 / git 回归 / Trellis 复核；双假设已拒绝。 | 静态分析达标。 |
| 不加兜底 | 已明确禁止旧中线、旧 `guide_error`、旧 duty、双假设、宽度/漂移硬门、单侧硬拒绝。 | 本轮实现只延后普通帧学习，不引入兜底。 |
| 简单直白代码 | 已把候选落实为小范围时序移动 + `allow_width_base` 显式参数。 | 代码达标。 |
| 参考版 + 历史提交共同校验 | 已记录 RT1064 无 `mid_position/width_base`，Front_Car 历史解释动态中心，`ce65c9d/e1069df/d2ccaf0` 解释学习时序演进。 | 静态证据达标。 |
| 解决直道爬到对侧 / 扭动 | 双侧 raw/IPM 身份问题已有运行代码覆盖；普通帧 learning-order guard 已收紧到 publish 成功后学习。单侧错误身份但完整前方预瞄也成立、以及控制 yaw/duty 扭动仍需真实帧区分。 | 部分完成，仍不能声称全解决。 |
| 不能随便删特殊逻辑 | `old_l`、`mid_position/width_base`、frame-start element contract、ring RT1064 direct entry 都已保留并解释。 | 当前审计达标。 |
| 多 agent 协同记录 | 四角色复核结论已写入研究记录，并加入短版中文交接。 | 达标。 |
| Trellis 本地协调 | PRD、研究记录、spec、guide、implement/check context 均已更新。 | 达标。 |
| 测试验证 | 本轮已运行 `git diff --check`、`bash code/test.sh --host`、`bash code/test.sh` 和 4 个 host analyze smoke。 | 符合当前约束。 |

## 2. 已证明完成的点

| 点 | 证据 |
| --- | --- |
| 双假设不是参考版路径 | RT1064 左右 trace 分别生成 `rptsc0/rptsc1`，没有同线双身份；当前代码已同构。 |
| IPM 反序不会再污染 `mid_position` | 当前 HEAD `d2ccaf0` 已把 `update_search_center()` 放到 IPM 反序拒绝之后。 |
| frame-start element contract 存在 | `classify_frame_mode()` 依赖 `action.cross_state0` / `action.ring_kind0`，新进入元素不抢当前帧模式。 |
| `mid_position/width_base` 是 acquisition state | 代码消费者审计显示它只喂 `find_seeds()` 和报告，控制链消费 `guide_error`。 |
| 最新候选边界清楚 | `Formal Learning-Order Contract`、`Truth Table`、中文 brief、spec/guide 已记录。 |

## 3. 未完成或不能证明完成的点

| 点 | 为什么未完成 |
| --- | --- |
| 单侧错误身份但完整前方预瞄也成立的情况 | learning-order guard 已实现并收紧到 publish 成功后学习，但这种更强坏例仍可能通过，需要真实帧或更强诊断字段。 |
| 真实相机 CROSS_IN replay | 当前没有 checked-in 序列证明真实相机进入并通过 `CROSS_STATE_IN`。 |
| 真实环岛全流程 replay | 当前没有真实序列证明 BEGIN -> IN -> RUN -> OUT -> END。 |
| 直道扭动到底是视觉还是控制 | 需要日志区分 `guide_error` 是否跳变；若 `guide_error` 稳定，问题可能在 yaw/轮速控制。 |
| 真实序列回归 | 本轮只覆盖 host build、交叉编译、现有单帧 smoke；没有真实连续序列 replay。 |

## 4. 本轮已实现的代码边界

已实现 learning-order guard：

1. 给 `update_search_center()` 增加显式 `allow_width_base` 参数。
2. 帧首记录 `ordinary_frame0`。
3. 帧首非普通帧不再早期学习；只有原本会早期学习的 accepted nearline
   路径在发布成功后 `update_search_center(rt, 0)`。
4. 帧首普通帧跳过早期学习。
5. `publish_track_result()` 成功后，如果 `ordinary_frame0`，再学习。
6. 不改 `publish_track_result()` 内部语义，不改
   `midline_has_forward_lookahead()`。
7. 不加单侧硬拒绝，不加双假设，不加宽度/漂移阈值。

## 5. 如果下一步只允许继续分析

继续方向应该是：

- 设计诊断字段，而不是行为 patch；
- 证明单侧帧是否真的在 `mid_ok < k_min_border_step` 或
  `work_track_type == NONE` 情况下污染 `mid_position`；
- 区分“视觉 `guide_error` 跳”与“控制 yaw/duty 抖”。

## 6. 当前结论

当前状态是：

> 分析主线已经收敛，最小 learning-order guard 已实现并通过本轮检查。  
> 但真实帧证据仍缺，不能把“直道爬到对侧 / 扭动”声明为彻底解决。
