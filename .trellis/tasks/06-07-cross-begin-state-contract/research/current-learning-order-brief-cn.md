# 当前结论交接：普通追线单侧问题与搜索中心学习

本文是给后续 agent / 现场队员看的短版结论。完整证据在
`tracking-reference-audit-checklist.md`。

## 1. 当前最重要结论

现在不要再走“同一条线同时按左边界/右边界试一遍”的双假设方案。

原因：

- RT1064 参考版不是这样做的；
- 当前代码已经按参考版形状生成候选：
  - 左 trace -> `track_leftline()` -> `rptsc0`
  - 右 trace -> `track_rightline()` -> `rptsc1`
  - `pick_track_type()` / `build_selected_midline()` 只选一边
- 双假设最后仍然要靠中心、宽度、历史、贴合距离等条件选一个，本质上会引入隐藏兜底。

## 2. 真正剩下的问题

剩下的问题不是“候选中线生成错了”，而是：

> 单侧可见、没有对侧 seed/trace/IPM paired points 时，当前帧无法静态证明这条线到底是不是正确的左/右边界。

当前代码已经能处理有关系证据的坏身份：

| 证据 | 当前处理 |
| --- | --- |
| 左 trace 经过右 seed | 拒绝左 trace |
| 右 trace 经过左 seed | 拒绝右 trace |
| 左右 trace 同行反序 | 两侧都拒绝 |
| IPM/work paired points 反序 | `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS`，并且 `d2ccaf0` 已阻止它学习 `mid_position` |

但只有单侧时，没有对侧关系可比，所以不能直接加“单侧硬拒绝”。

## 3. 为什么不能删 `mid_position/width_base`

`mid_position/width_base` 不是随便加的。历史提交说明：

- `ce65c9d`：固定 `mid_position=80` 会让弯道/十字/环岛偏置时一侧先出画，然后边线、L 点、元素都饿死；
- `e1069df`：把搜索中心学习从 seed 后挪到 trace 成功后，避免 seed 毛刺污染下一帧；
- `d2ccaf0`：把搜索中心学习挪到 IPM 身份复核之后，避免已证明反序的近线污染下一帧。

所以历史趋势是：

> 不删除动态搜索中心，而是让它越来越晚、越来越靠近当前帧可靠证据之后再学习。

## 4. 当前已落的 learning-order 合同

这个补丁只叫 learning-order guard，不叫单侧身份修复。

当前最小合同：

1. 帧首记录：
   `ordinary_frame0 = cross_state0 == NONE && ring_kind0 == NONE`
2. 帧首已经在 cross/ring 的 accepted nearline 路径，第一版之后已收紧为：
   只记录 `defer_element_search_center_update`，等 `publish_track_result()`
   成功后再 `update_search_center(rt, 0)`；farline-only / IPM 拒绝路径不新增学习。
3. 帧首普通帧，不在当前早期位置学习。
4. 先按现有顺序跑：
   `snapshot_ring_frame_start_action()` ->
   `element_process()` ->
   `classify_frame_mode()` ->
   `apply_frame_start_element_crop()` ->
   `build_selected_midline()`
5. 先过 `publish_track_result()`。
6. 如果 `ordinary_frame0` 且发布成功，再学习 `mid_position/width_base`。
7. `width_base` 是否低通，必须由帧首普通标志决定，不能用
   `element_process()` 后的 `rt->cross.state/rt->ring.kind`。

2026-06-09 收紧原因：

- 第一刀新增了普通帧完整前方预瞄门；
- 如果普通帧被该门拒绝，却已经提前写入 `mid_position/width_base`，
  就会让“短中线/后方预瞄”不发控制但仍教下一帧 acquisition；
- 因此当前合同改为：普通帧只有最终可发布，才允许写入下一帧搜索中心。

## 5. 这个候选会改变什么

只改变这些普通帧：

| 帧类型 | 当前行为 | 候选行为 |
| --- | --- | --- |
| `work_track_type == NONE` | 可能已经学习 `mid_position` | 不学习 |
| selected side 存在但 `mid_ok < k_min_border_step` | 可能已经学习 `mid_position` | 不学习 |
| `mid_ok >= k_min_border_step` 但 forward-lookahead 发布门失败 | 以前可能学习 | 不学习 |

这些帧不改变：

| 帧类型 | 行为 |
| --- | --- |
| seed 失败 | 不学习 |
| trace 失败 | 不学习 |
| IPM 反序拒绝 | 不学习 |
| CROSS_IN farline | 保持当前路径 |
| 帧首已在 cross/ring，且 nearline seed/trace/IPM 通过 | 发布成功后学习，`width_base` 不更新 |
| CROSS_IN farline-only 或 IPM 反序后远线 | 不新增学习 |
| 普通帧 `publish_track_result()` 成功 | 学习，且允许普通双 seed 更新 `width_base` |

## 6. 这不是兜底的原因

它不做这些事：

- 不合成对侧线；
- 不复用旧中线；
- 不 hold 旧 `guide_error`;
- 不 hold duty；
- 不加宽度/漂移阈值；
- 不双假设；
- 不禁止单侧追线。

它只做一件事：

> 普通帧只有在 selected midline 几何与完整前方预瞄发布门都成立后，才允许把这个当前帧教给下一帧 seed 搜索中心。

## 7. 它仍然解决不了什么

如果一条错误身份的单侧线也能通过完整前方预瞄发布门，这个候选仍然挡不住。

这种情况需要真实帧证据或诊断字段，例如：

- `seed_state`
- seed 坐标
- trace x 范围
- `rpts0s/rpts1s`、`rptsc0/rptsc1` 数量
- `mid_ok`
- `mid_position/width_base` before/after
- 最终 `guide_error`

在这些证据之前，不要加 center-column、attach-distance、temporal prior、
width/drift 之类的硬门。

## 8. 当前执行状态

- 运行代码已实现 learning-order guard，并在 2026-06-09 收紧为普通帧 publish 成功后学习。
- 当前远端 HEAD 已有 `d2ccaf0`：IPM 反序帧不会再学习 `mid_position`。
- `.trellis/` 是本地协作记录，不提交到 Git。
- 当前任务仍处于 `in_progress`；这不证明 `rej=3/ring` 无线或控制扭动已经解决。
