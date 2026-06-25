# 圆环陀螺仪 heading 积分辅助

## Goal

在 ATG 圆环状态机（`circle.c`）中引入 IMU yaw-rate 积分得到的 heading 角度，作为各阶段切换的 **OR 辅助条件**（不替代、不删除原视觉/里程条件），缓解纯视觉阶段判断不稳导致的入环偏左。功能代码已实现（未提交 diff，已过审）；本任务负责按审阅结论做最小化清理后提交。

## Context / 现状

- 功能已实现，改动 4 文件：`circle.c`（heading 变量 + 积分 + OR 条件）、`circle.h`（函数声明）、`reference_step.c`（3 处 reset）、`runners.cpp`（live 调用积分）。
- 已过审：方向正确，无第二状态机、无伪造线、offline 行为可证明与原版一致。审阅发现的问题集中在 **reset 散布（8 处）** 与 **跨文件改动冗余**，已得出改动 A/B 清理方案，用户接纳。

## 已定型的设计决策（实现已落地）

1. **OR 增项，不替代**：保留每阶段原视觉/里程条件，新增 `circle_heading_abs_ge(阈值)` 作 OR，任一满足即切换。（对应 prompt 约束 #2；修正 prompt 中"替代 total_distence"的旧表述）
2. **积分只在 live() 进行**：`update_circle_heading()` 仅在 `runners.cpp` live 主循环、`drive_output_read_feedback()` 之后调用一次。**这是关键决策**——offline/replay 不调用它 → `circle_heading_rad ≡ 0` → 所有 heading OR 项恒 false → offline 行为与原版逐位一致。（修正 prompt 要求 #5"在 reference_step.c process_frame 每帧积分"——那样 offline 会误积分；改为 live-only 才正确）
3. **ABS heading + 左右共用阈值**：几何转角左右对称，`fabsf()` 后比较。
4. **入环清零**：进入 BEGIN 时 heading=0，积分窗口从入环开始；BEGIN 触发当帧不积分（合理）。
5. **死区 0.065 rad/s**：消除静止零漂积分。yaw-rate 源 `actual_yaw_rate_mrad_s`（`drive_output_read_feedback()`），本项目 IMU。
6. **4 个阈值（0.1° 单位）**：60°/200°/250°/355°（600/2000/2500/3550），抄自 Enterprise_E gyro 圆环逻辑，作摄像头车可调起点、待上车标定。出处与可参考范围见 memory `atg-circle-heading-thresholds-provenance`。

## 本任务要做的清理（改动 A/B，审阅结论，已接纳）

**改动 A — reset 收敛 + 消除跨文件改动 + 收窄公开面**
- reset 从 8 处收敛到单一真相：保留 `update_circle_heading()` NONE 守卫里的清零，删除其余 7 处（`circle.c` 2×BEGIN + 2×END；`reference_step.c` 3 处）。
  - 等价替代（option b）：保留 2×BEGIN reset、NONE 守卫改纯 `return`、删 END+reference_step。二选一，**默认 option a**（与审阅一致）。
- `reference_step.c` 回退到零改动（跨文件改动消失）。
- `reset_circle_heading()` 改 `static`，从 `circle.h` 删除声明；`circle.h` 只保留 `update_circle_heading()`。

**改动 B — 常量命名去歧义**
- `CIRCLE_HEADING_BEGIN_TO_IN_DEG10` → `CIRCLE_HEADING_ENTER_DEG10`。该 60° 阈值同时用于 BEGIN→IN 与 IN→RUNNING；research 已确认 ittuann 的 IN→RUNNING 也是 `heading>=60°` 持续，复用忠实于参考，故只重命名、不新增第 5 个常量。

## Requirements

- [ ] 实现改动 A（reset 单点化 + reference_step.c 回退 + static + 头文件收窄）
- [ ] 实现改动 B（常量重命名）
- [ ] 保持 offline/replay 行为与原版一致（heading=0 时所有 OR 项 false）
- [ ] host 编译通过，既有 parsing 测试绿

## Acceptance Criteria

- [ ] `cmake --build code/build-host` 通过（允许既有 ATG C 文件 warning）
- [ ] `config_parsing_test` / `options_parsing_test` 通过
- [ ] `git diff -- atg_reference/port/reference_step.c` 为空（改动 A 后零改动）
- [ ] `circle.h` 相对原版仅新增 `update_circle_heading` 一个声明
- [ ] 收尾看 diff：无第二真相源、无隐藏 fallback、reset 单点
- [ ] （硬件侧）上车标定 4 个 heading 阈值，确认不过早切阶段

## Definition of Done

- 改动 A/B 落地，host build + 既有测试绿
- diff 自审通过（reset 单点、reference_step.c 零改动、circle.h 只多一个声明）
- 代码侧 DoD 到 build+测试为止；4 阈值上车标定在硬件上做

## Out of Scope

- 不实现 ittuann 的 350°(3500) 偏转 flag、100–225° 环内平均打角记录（保持最小）
- 不引入卡尔曼/互补滤波
- 不修改 `control.cpp` 的 yaw-rate 内环
- 不新增 yaml/env 配置（4 阈值与死区硬编码）
- 不新增测试文件（offline 无真实 yaw-rate，单测无法覆盖 heading 积分；用 host build + 既有测试 + 上车验证）
- 不用 Enterprise_E 佐证 ATG 视觉链（cross 远线 / IPM 搜线 / 外扩规则）——其摄像头部分未开源

## 上车验证风险点（审阅 Part 4）

- **IN→RUNNING** 的 heading OR 绕过 `total_distence>2000` 距离闸，可能里程不足就进 RUNNING
- **RUNNING→OUT(200°)、OUT→END(250°)** 是无视觉 AND 的纯 heading 强推，开环陀螺标定误差可能强切阶段
- **LEFT_END**：里程门 7500 vs heading 355°，若 heading 先到可能缩短防重复触发直道
- IMU 整圈 `valid==0` 时 heading 停 0，自动退化为原版纯视觉/里程（可接受的降级）

## Decision (ADR-lite)

**Context**: heading=0 的不变量当前被 8 处 reset 强制，过度工程化。
**Decision**: 收敛到单一真相（默认 option a：`update_circle_heading` 的 NONE 守卫），`reference_step.c` 回退，`reset_circle_heading` 改 static。
**Consequences**: reset 集中可审；option a 依赖"update 每 live 帧在 run_circle 前调用"（主循环本就是此序，`runners.cpp:632→657`）；若偏好显式入环清零可选 option b，等价。

## Technical Notes

- 实现文件：`circle.c` / `circle.h` / `runners.cpp`（改动 A 后 `reference_step.c` 零改动）
- 阈值出处与可参考范围：memory `atg-circle-heading-thresholds-provenance`
- 逐阶段对比：`research/circle-stage-comparison.md`（已更正 ittuann 入环误读）

## Research References

* [`research/circle-stage-comparison.md`](research/circle-stage-comparison.md) — ATG 各阶段 vs ittuann heading 阈值逐阶段对应；Enterprise_E 为摄像头主 + gyro 圆环 + 电磁辅助（摄像头未开源），入环机制不可证为电磁
