# 完整前方预瞄采样间隔审计与四角色回包

日期：2026-06-09

## 结论

第七刀可落地：普通帧完整前方预瞄门应检查“是否存在当前帧前方点覆盖
`LOOKAHEAD_DIST`”，不能先选离 `LOOKAHEAD_DIST` 最近的点再要求该点
`dist >= LOOKAHEAD_DIST`。

原实现会误拒 `34/37` 这种采样间隔：最近点是 `34`，但下一点已经覆盖完整
预瞄。修正后只选择最小的 `dist >= LOOKAHEAD_DIST` 点，再检查
`target.y < ref.y`。

这不是把短线放行：`.diag/video_crop_input/t16.png` 和 `t36.png` 的
`mid_max_dist=28/29` 仍失败，`search_update_kind=0`。

## 四角色回包摘要

| 角色 | 结论 |
| --- | --- |
| Reference contract | RT1064 没有本项目的完整前方预瞄发布门；它用 `aim_idx` 在 `rptsn_num` 内取点。因此当前门是本地 fail-closed 合同，不能声称是 RT1064 逐行合同。参考审计指出旧 helper 存在 `34/37` 采样间隔误拒风险。 |
| Current implementation | 未发现 stale midline、旧 `guide_error`、旧边界或 duty hold fallback。`xlearn/xcrop` 是诊断字段，不是第二真相源。保留风险：元素短线发布成功后仍会学习 `mid_position`，但这不是失败帧学习，且不更新 `width_base`。 |
| Git regression | 当前 diff 未回退 `d101ad7` 普通帧发布后学习、`d2ccaf0` IPM reject 前不学习、`aafcea8` RT1064 ring 主链、`086844b` 十字远 L 来源保护。 |
| Trellis/check gate | 需要把最新综合 research、视频证据索引、learning-order 计划和本文件加入 `check.jsonl`；当前大 diff 最终提交时应拆成行为、诊断、assistant 显示边界，或明确说明为什么合并。 |

## 第七刀算法理由表

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `main.c` 没有完整前方预瞄拒绝门；`aim_idx` 在已生成 `rptsn` 内裁剪取点。当前项目额外添加普通帧完整前方预瞄门，是为了防止短/后向普通中线强控。 | 旧 `midline_has_forward_lookahead()` 先找离 `LOOKAHEAD_DIST` 最近的点，再要求该点 `dist >= LOOKAHEAD_DIST`；当采样为 `34/37` 时，已有完整预瞄却被 34px 最近点挡掉。 | `code/tracking/imgproc.cpp::midline_has_forward_lookahead()` 改为寻找最小的 `dist >= aim_distance` 点，再要求该点 `y < ref_y`。 | 完整预瞄门的语义是“覆盖到目标距离”，不是“最近采样点刚好不小于目标距离”。这修正采样间隔造成的误拒，同时保留前方性约束。 | 不复用旧中线/旧 guide/旧 duty，不降低 `LOOKAHEAD_DIST`，不允许 `max_dist < LOOKAHEAD_DIST` 的短线通过。`t16/t36` 仍失败且不学习；`t60` 因 `mid_max_dist=139` 且前方门成立才发布。 |

## 新增诊断

- `report` key-value 增加：
  - `mid_look_dist`
  - `mid_max_dist`
  - `mid_forward_lookahead`
- live/replay 单行 `md=look_dist/forward_ok/max_dist`。

解释：

- `mid_look_dist` 是当前 `lookahead_error()` 会取的最近预瞄点距离。
- `mid_forward_lookahead` 是普通帧发布门结果。
- `mid_max_dist` 用于区分“总长度不够”和“有更远点但前方性不成立”。

## 本地证据

命令：

```bash
git diff --check
bash code/test.sh --host
bash code/test.sh
./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t60.png --report .diag/video_crop_input/t60.current_report.txt
./code/build-host/front_car_mainline --replay .diag/video_crop_input/t60.png 2 --report .diag/video_crop_input/t60.replay_report.txt
```

结果：

- `git diff --check` 通过。
- `bash code/test.sh --host` 通过，包含：
  - `cross_farline_reuse_test`
  - `midline_lookahead_test`
  - `search_center_learning_test`
- `bash code/test.sh` 通过。
- `t16`：`line_found=0 mid_look_dist=28 mid_max_dist=28 mid_forward_lookahead=0 search_update_kind=0`。
- `t36`：`line_found=0 mid_look_dist=29 mid_max_dist=29 mid_forward_lookahead=0 search_update_kind=0`。
- `t60`：`line_found=1 mid_look_dist=34 mid_max_dist=139 mid_forward_lookahead=1 search_update_kind=1 guide_error=12.8786`。

## 保留风险

- 当前仍没有真实 already-in-ring/cross 成功发布长序列，不能声称 V03/V05 或
  `frame=3570` 根因已解决。
- 元素短线发布成功后学习 `mid_position` 是保留合同，不是本刀修改；若后续现场日志
  显示元素短线成功发布但污染后续 seed，需要另开独立证据链处理。
- live changed-state 对部分数值做 bucket，现场若要追每帧小幅漂移，应使用 replay/report
  或临时提高 live 输出密度。
