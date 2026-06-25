# circle.c 1->7 深挖结论

本文件是 `atg_reference/CIRCLE_DEEPDIVE.md` 的任务内摘要。依据为当前工作树真实文件:

- `atg_reference/Project/CODE/circle.c`
- `atg_reference/port/reference_step.c`
- `atg_reference/Project/CODE/cross.c`
- `code/tracking/atg_reference_mainline.cpp`
- `code/core/control.cpp`
- `code/app/runners.cpp`

## 1. 距离阈值语义

`total_distence` 只在 `Count_dis_Flag==1` 时累加,否则清零。且一帧顺序是:

```text
run_atg_elements/run_circle -> update_distance_counters -> revoke/select/normalize
```

所以 `run_circle()` 当前帧看到的是上一帧累计到的距离,本帧写 `Count_dis_Flag` 后要到本帧末尾才影响距离。

结论:

- BEGIN 的 `total_distence` 是首次内侧丢线后的 `lost_dist`。
- IN/RUNNING/OUT/END 的距离门是各自状态内重新起算的 state distance。
- `g_circle_begin_dist` 才是 BEGIN 后全段距离,用于 idle revoke。

## 2. 副作用标志消费链

当前实车主控制链只有:

```text
circle_type -> select_work_line/src -> rptsn -> atg_lookahead_error() -> guide_error
circle_type != NONE -> element_active -> element_target_rps / element_reverse_brake
```

`if_clean_pid`、`broadcast_flag`、`is_large_circle/is_small_circle` 不是当前差速控制主链。它们主要是历史标志、reset/report 或旧参考遗留。

`if_lost_left/right_line` 仍有真实作用:影响 `cross_farline_L/R` 的 seed 分支,并进入诊断输出。

## 3. cross_farline_L/R 作用

`circle.c` 只在 `LEFT_IN` 调 `cross_farline_L()`,在 `RIGHT_IN` 调 `cross_farline_R()`。

当前 port 的 `reference_step.c::build_circle_spliced_lines()` 已经把 IN/OUT/RUNNING 主要补线改成固定 raw 几何,不再要求 `far_Lpt*` 成功才生成 `src=2/3/5/6/14`。

因此:

- `far=0/0` 不等于固定补线没打出来;必须看 `src` 和 `sel`。
- `cross_farline` 主要保留远线缓存、截断、`if_lost_*` latch 和诊断价值。
- `circle.c` 入口 inner-hit 和 `cross.c` farline seed 是两套逻辑,不能混用偏移含义。

## 4. heading 阈值物理阶段

heading 从进入 `*_IN` 清零后累计:

- `600` = 60 deg: BEGIN/IN 到下一阶段的早期切入确认。
- `1500` = 150 deg: RUNNING 视觉出 OUT 的陀螺门,防假 Lpt。
- `2000` = 200 deg: RUNNING 纯 gyro 出 OUT 兜底。
- `2660` = 266 deg: OUT 到 END 的交棒时机。用户要求保持不动。
- `3550` = 355 deg: 左 END 视觉退出硬门,防 `src=14` 过早撤掉。

`CIRCLE_HEADING_FORCE_OUT_DEG10=2500` 当前未引用。

## 5. inner-hit 几何

当前入口不是完整双断点。它是:

```text
单侧 Lpt + 对侧 straight + Lpt 内侧 raw 黑点 hit + 连续 2 帧 vote
```

`ATGCircleEntryBreakpoints` 日志名不准确。函数里有两处同名输出,第一步清理若改名必须两处一起改。

## 6. 异常路径

圆环有三类退出/复位:

- 自然 END 退出: `circle_count++`,恢复普通参数,抑制重入。
- BEGIN idle revoke: BEGIN 超 6000 counts 且无内侧丢线,reset NONE,不计数。
- stall revoke: 圆环态连续 30 帧无 selected line,reset NONE,不计数。

这些是兜底/撤销路径,不是入口或推进主判据。

## 7. 大小环消费

`is_large_circle/is_small_circle` 仍在 `*_IN` 被写,但当前 port:

- `road.c` 相关分支已注释;
- `control.cpp` 不读取大小环;
- `atg_reference_mainline.cpp` 只看 `circle_type` 做 guide scale;
- 速度控制只看 `element_active` 和配置中的元素速度/反刹。

所以大小环目前是历史/诊断标志,不是当前控制主线。

## 第一阶段清理边界

允许:

- 改入口日志名,两处同步。
- 删未引用 `CIRCLE_HEADING_FORCE_OUT_DEG10`。
- 清理或标明 `circle_encoder` 残留。
- 把 `4500/7500/4000` 提成 enum 常量,数值不变。
- 补诊断日志,不改变判断。

禁止:

- 改 `CIRCLE_HEADING_READY_OUT_TO_END_DEG10=2660`。
- 改 guide 控制链。
- 把 `pure_angle` 接进当前控制。
- 重新加入 early revoke、anti-flicker、Joshua AND 门、BEGIN 恢复清零。
- 在语义清理阶段改状态推进条件、阈值数值或判断顺序。
