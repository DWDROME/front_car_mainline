# 元素帧搜索中心学习顺序审计

## 结论

第六刀允许落地，但不是无风险整理；它是新的 ring/cross acquisition 学习行为变更。

最终合同：

- 普通帧：`publish_track_result()` 成功后 `update_search_center(rt, 1)`。
- 帧首已在 cross/ring，且走到原本早期学习所在的 accepted nearline 分支：
  先置 `defer_element_search_center_update=1`，发布成功后
  `update_search_center(rt, 0)`。
- `CROSS_IN` farline-only、trace 失败、IPM 反序后远线继续等原本没有学习的路径，
  不新增 search-center 学习。
- `width_base` 只允许帧首普通帧更新。

## 四审计摘要

| 角色 | 结论 |
| --- | --- |
| Reference contract | RT1064 没有动态 `mid_position/width_base`；参考原则是 ring/cross 最终中线点数足够才控制，点不足不控制，也没有失败帧教下一帧 search center。 |
| Current implementation | 早期 `update_search_center(rt, 0)` 只写 `mid_position`，不影响本帧 `ring/cross/zebra/guide_error`；移动时必须用 deferred flag 保持原触发域。 |
| Git regression | `ce65c9d -> e1069df -> d2ccaf0` 的方向是越来越晚、越来越接近可靠当前帧证据后再学习；但 `d101ad7` 曾明确把元素帧作为第一版保留边界。 |
| Trellis/spec/check gate | 条件允许；必须更新反向 spec/research，记录 reference/log evidence，验证 `git diff --check`、`bash code/test.sh --host`、`bash code/test.sh`，并尽量做 targeted analyze/replay。 |

## 为什么不是 ring 裁剪修复

这刀不改变：

- `ring_process()` 状态机；
- `snapshot_ring_frame_start_action()` 的选边；
- `apply_frame_start_element_crop()` 的裁剪条件；
- `publish_track_result()` 的发布门；
- `midline_has_forward_lookahead()`；
- `guide_error -> control` 链。

它只改变跨帧 acquisition prior：发布失败的元素帧不再写下一帧 `mid_position`。

## 固定理由表

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 没有动态 search center；ring/cross 可选边、裁剪或用远线，但最终只有选中的候选能生成足够 `rptsn` 时才控制，点不足则 `rptsn_num=0`。 | 当前项目有 `mid_position` 跨帧学习；元素帧旧代码在最终发布前学习，后续即使 `rej=4` 也已经教下一帧 seed search。 | 只把原本会早期学习的 accepted nearline 元素帧改为发布成功后学习；普通帧发布成功后学习保持；farline-only/IPM reject 路径不新增学习。 | V03/V05/Image #7 类元素阶段 `rej=4` 问题已进入候选裁剪/selected midline/publish owner，发布失败元素帧不应污染下一帧 acquisition。 | 不复用旧中线/旧边界/旧 `guide_error`/旧 duty，不合成对侧线，不改状态机，不加单侧硬拒或宽度/漂移/attach-distance gate。失败帧仍失败且不学习。 |

## 验证要求

已要求的基础验证：

- `rg -n "update_search_center\\(|defer_element_search_center_update|ordinary_frame0|publish_track_result\\(|TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS" code/tracking/mainline.cpp`
- `git diff --check`
- `bash code/test.sh --host`
- `bash code/test.sh`

Smoke 验证：

- `.diag/video_crop_input/t16.png`
- `.diag/video_crop_input/t36.png`
- `.diag/video_crop_input/t60.png`
- `.diag/synth/straight_cross_like.png`

当前不足：

- 还没有真实可回放的 already-in-ring/cross 多帧输入来证明第六刀在元素长序列上的动态收益。
- 因此不能声称 `frame=3570`、V03、V05 根因已解决；只能说代码已 fail-closed，并新增 `xlearn` 字段让下一轮现场日志能验证。

2026-06-09 本地 smoke 结果：

- `git diff --check` 通过。
- `bash code/test.sh --host` 通过。
- `bash code/test.sh` 通过。
- 新增 `code/test/search_center_learning_test.cpp` 白盒锁定学习合同：
  - 普通帧完整前方预瞄发布成功后，`kind=1`，`mid_position` 学习且
    `width_base` 允许低通更新。
  - 普通帧短前方中线被 `publish_track_result()` 拒绝时，不写
    `mid_position/width_base`，`kind=0`。
  - 普通帧后方完整长度中线被 `publish_track_result()` 拒绝时，不写
    `mid_position/width_base`，`kind=0`。
  - 元素帧短中线发布成功后，`kind=2`，允许 `mid_position` 学习，
    但 `width_base` 保持不变。
  - 元素帧单 seed 发布成功后按现有 `width_base` 外推 `mid_position`，
    不新增身份兜底。
- `.diag/video_crop_input/t04..t60.png` 与 `.diag/synth/straight_cross_like.png`
  当前均为 `line_found=0`，`search_update_kind=0`。这证明这些失败帧没有学习
  `mid_position`，但不能证明成功发布帧或真实环岛长序列安全。
- `.diag/video_console/*.png`、`.diag/video_frames/*.png`、`.diag/video_full/t04.png`
  不是当前 analyze 可用的 `RAW_W x RAW_H` 输入，本轮未形成有效报告。

## 下一轮日志判读

`xlearn=kind/mid_before/mid_after/width_before/width_after`：

- `kind=0`：本帧没有 search-center 学习。
- `kind=1`：普通帧发布成功后学习，允许 `width_base` 更新。
- `kind=2`：帧首已在元素态的 accepted nearline 分支发布成功后学习，`width_base` 不应变化。

若 `rej!=0` 且 `xlearn.kind!=0`，这是回归，说明失败帧仍在学习。
