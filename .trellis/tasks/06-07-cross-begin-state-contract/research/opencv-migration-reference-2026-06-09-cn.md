# OpenCV 迁移参考与当前搜线层清晰化结论

日期：2026-06-09

## 来源

用户提供了另一个 agent 对视频 `34850997340-1-192.mp4` 的整理产物：

- `/home/ds_ev/video_analysis_34850997340/migration_notes.md`
- `/home/ds_ev/video_analysis_34850997340/reconstructed/opencv_port_reference.cc`
- `/home/ds_ev/video_analysis_34850997340/reconstructed/migration_demo.cc`
- `/home/ds_ev/video_analysis_34850997340/reconstructed/smoke_test.cc`

主会话已复跑：

```bash
/home/ds_ev/video_analysis_34850997340/reconstructed/build/smoke_test
```

输出：

```text
left_num=200 right_num=200
```

## 核心结论

这批产物确认的视频内容不是另一套复杂模型，而是把 RT1064 的
`findline_lefthand_adaptive()` / `findline_righthand_adaptive()` 迁移到
OpenCV/PC 工程。重点不变量是：

- 坐标系：`x` 向右，`y` 向下。
- 点集：`pts[i][0]` 是 `x`，`pts[i][1]` 是 `y`。
- `*num`：调用前是容量，返回后是实际点数。
- 图像访问：RT `AT(img,x,y)` 迁移到 OpenCV 时等价为 `img.ptr<uint8_t>(y)[x]`。
- 方向表必须是 RT1064 原版的上、右、下、左顺时针顺序；否则 `(dir + 1) % 4` 与 `(dir + 3) % 4` 的左右转语义会反。
- `find_leftbase()` 的最终视频语义已补齐：在二值图里从 `*x` 向左扫，遇到
  `ptr[w] == 255 && ptr[w - 1] == 0` 就把 `*x = w` 作为左边界 seed。
  它不是额外模型，而是“先找边界 seed，再交给左手追线”的起点函数。

## 和当前项目的关系

当前 `code/tracking/imgproc.cpp` 已经满足关键方向表合同：

- `DX/DY` 顺序是上、右、下、左。
- `LDX/LDY` 与 RT1064 `dir_frontleft` 一致。
- `RDX/RDY` 与 RT1064 `dir_frontright` 一致。
- `trace_left()` / `trace_right()` 仍按当前点局部阈值判断 `front` 与 `front-left/right`。
- `find_left_edge()` 等价承接视频 `find_leftbase()` 的边界 seed 语义：
  当前点仍在白区、左邻进入黑区；区别是本项目用局部阈值而不是固定二值
  `255/0`。`find_right_edge()` 是同一语义的右侧对称版。

因此本轮不建议引入一套新的 OpenCV 搜线实现，也不建议用视频简化版固定阈值 `125`
替换当前局部阈值。更合理的方向是把现有主链清晰化为三层：

| 层 | 只回答的问题 | 当前关键证据 |
| --- | --- | --- |
| 识线层 | `START_HIGH` 有没有找到 seed；trace 是否向前爬；左右身份是否反序 | `seed_state_find`、`seed_left_find/right_find`、`trace_*_raw_step`、`trace_*_raw_gain`、`trace_identity_reject` |
| 几何层 | 当前帧能否发布中线；预瞄是否完整且在前方 | `selected_mid_ok`、`mid_step`、`mid_max_dist`、`mid_forward_lookahead`、`reject_reason` |
| 元素层 | cross/ring/zebra 是否消费了稳定几何证据 | `action_*0`、`mode_*`、`candidate_crop_*`、`cross/ring` 状态 |

## 清晰化建议

后续开发以“小清理”为主：

1. 不改变 `trace_left/right` 的方向表和转向公式。
2. 不把视频教学版固定阈值迁入主链。
3. 保留当前 seed 行与左右 seed 方框显示，用它判断起搜行是否合理。
4. 把日志/报告解释围绕三层组织，减少把 seed、trace、midline、element 混在一起讨论。
5. 如果需要增加代码，只优先加 host-only 白盒测试，锁住方向表、`*num` 语义和左右手追线基本行为。

## 已落清晰化小改动

本轮只做表达和验证清晰化，不改变搜线算法：

- `find_seeds()` 形参从 `mid` / `mid_position` 表达清理为 `search_center`，强调它是 seed 搜索中心，不是当前控制中线。
- `find_left_edge()` / `find_right_edge()` 注释补齐与视频 `find_leftbase()` 的迁移映射：
  先按起线行找白->黑边界 seed，再进入左右手追线。
- `code/tracking/imgproc.cpp` 方向表注释明确绑定 RT1064 的上、右、下、左顺时针顺序，防止后续把方向表和 `(dir + 1)/(dir + 3)` 转向公式拆开改。
- `tracking_process_frame()` 顶部注释按三层重写：识线层、几何层、元素层。
- `print_detail()` 输出把 `SeedSt` 改为 `SeedState`，把 `Learn` 改为 `SearchPrior`。
- `write_report()` 保留旧 `mid_position` 字段，同时新增同义诊断键：
  `seed_search_center` 和 `seed_width_prior`。
- `write_report()` 额外输出 before/after 同义键：
  `seed_search_center_before/after`、`seed_width_prior_before/after`，便于把下一帧
  seed 搜索先验的实际变化和当前控制中线分开看。
- `update_search_center()` 内部局部变量改为 `next_center`；`search_update_kind`
  解释为本帧进入的学习提交路径，不等价于 before/after 一定发生变化。普通单侧
  guard 拒绝学习时，kind 仍可记录 ordinary 路径，但 after 会等于 before。
- 新增 host-only `line_trace_contract_test`：
  - 用黑底白色矩形验证 `find_seeds()` 能先在起线行找出左右 base seed；
  - 再把 seed 交给 `trace_single()`，验证左手/右手 trace 的首段都沿边界向上爬且点都留在白区。
  这条测试对应视频的 `find_leftbase() -> findline_lefthand_adaptive()` 教学链路。

固定理由：

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `imgproc.c` 左/右手巡线方向表固定为上、右、下、左，`*num` 是输入容量/输出点数。 | 当前代码算法已基本等价，但命名里 `mid_position` 容易被误读成当前控制中线，日志 `Learn` 也没有说明它只是下一帧 seed 搜索先验。 | 只改注释、参数名、诊断标签和 host-only 测试；不改 `trace_left/right` 分支和阈值。 | 让现场调试按“识线 -> 几何发布 -> 元素消费”定位失败点，避免把 search prior 当控制输出。 | 没有复用旧中线、没有合成对侧线、没有新增 fallback 路径。新增测试只验证现有 trace 方向合同，验证失败会暴露方向表/转向公式被改坏。 |

## 不是兜底的证据

这份参考只用于确认低层搜线不变量，不改变当前帧控制输出，不复用旧中线，不合成对侧线，也不把 OpenCV 行扫描/固定阈值作为隐藏备用路径。

## 本轮验证

命令：

```bash
git diff --check
bash code/test.sh --host
bash code/test.sh
code/build-host/front_car_mainline --analyze .diag/synth/straight_cross_like.png --report /tmp/front_car_report_style_smoke.txt
rg -n "^(seed_search_center|seed_width_prior)" /tmp/front_car_report_style_smoke.txt
```

结果：

- `git diff --check` 通过。
- `bash code/test.sh --host` 通过：
  `cross_farline_reuse_test`、`line_trace_contract_test`、`midline_lookahead_test`、
  `search_center_learning_test` 均输出 `ok`。其中 `line_trace_contract_test`
  已包含 `find_seeds() -> trace_single()` 的 seed-to-trace 合同。
- `bash code/test.sh` 通过。
- analyze smoke 中 `SeedState` / `SearchPrior` 新标签可见，report 中输出：
  `seed_search_center_before=80`、`seed_search_center_after=-1`、
  `seed_width_prior_before=52`、`seed_width_prior_after=-1`、
  `seed_search_center=80`、`seed_width_prior=52`。
