# 主链分层重构:拆 runners + 日志分域 + seed 去重

## Goal

降低主链工程复杂度,让圆环/十字调试更直白。手段是硬化"主循环层 / tracking 桥 / control / log+assistant"四层边界,把复杂度从算法判断里搬到模块分层、日志分域、调试工具里。**不改任何算法逻辑、不改任何已标定的控制/视觉数值。**

## What I already know(已核实)

* `code/app/runners.cpp` = 729 行,混了 9 类职责:`live_profile_t` / `camera_options_t` 两个 struct、encoder 距离换算(`atg_distance_counts_from_encoder_delta`)、`apply_cross_half_relay`、`control_input_from_current_frame`、profile 计时(`profile_add`/`profile_report_and_reset`)、`print_replay_frame`、`publish_completed_live_frame`、5 个 mode runner(live/replay/analyze/offline/capture)。
* `log.hpp/log.cpp` 当前**不存在**,日志全是散落 `printf`。
* 四层边界成立,与现有代码注释一致。
* guide 缩放在 tracking 桥 `atg_reference_mainline.cpp:18-20`(`kCircleInGuideScale=0.75` / `kCircleRightOutGuideScale=0.75` / `kCircleRunningGuideScale=0.81`,`:230` clamp ±35)。**这是上车标定值(drive42/43),不可动**;搬迁可以,改值不行。
* seed **已同源**:`circle.c:536-543 circle_entry_inner_seed()` 与 `assistant.cpp:547-562 circle_entry_scan_seed_raw()` 公式逐字一致(左 +2/-5,右 +5/-5)。当前无偏差,但是**两份重复拷贝**(第二真相源)→ P2 去重,非紧急 bug。
* `print_circle_abc_diag`(`circle.c:424`)无条件打印是**刻意设计**(注释 `:426`),非疏漏。

## Assumptions(待确认)

* 本次为纯行为保持重构,验收靠 replay 同一份 drive 日志 → 重构前后输出逐字节一致。
* 日志分域引入新设施,但**不改动现有日志输出字符串格式**(因为标定分析依赖解析既有日志)。

## Open Questions

* (见下方 Q&A,逐个确认)

## Requirements(LOCKED — MVP = A + B + 日志门控方案1)

* **A. 拆 `runners.cpp`**:运行层只保留 5 个 mode 调度(live/replay/analyze/offline/capture);析出
  frame_pipeline / control_input_builder / live_profile / camera_options / replay_log。纯搬代码,零行为变更。
* **日志门控(方案1)**:引入 `log.hpp/log.cpp`,提供 level + domain 门控
  (CIRCLE/CROSS/LINE/CONTROL/CAMERA/ASSISTANT)。**只加开关,不改任何现有输出字符串格式。**
  目标=解决"无效日志太多":默认静默最吵的域(典型 `print_circle_abc_diag` 进圆环每帧无条件打印),
  调试时用 `FRONT_CAR_LOG_<DOMAIN>=1` 按需打开。
* **B. seed 单一来源**:circle.c 导出种子函数(基于 `circle_entry_inner_seed` 公式),
  assistant 的 `circle_entry_scan_seed_raw` 改为复用,消除两份重复公式拷贝。数值同源不变。

## Acceptance Criteria

* [ ] 重构后 `runners.cpp` 只含 5 个 mode 调度
* [ ] replay 同一 drive 日志,重构前后控制输出/中线**逐字节一致**
* [ ] 日志默认输出体积下降(吵闹域默认关),且保留的日志字符串格式不变
* [ ] seed 只剩一份公式来源,circle.c 与 assistant 数值仍一致
* [ ] WSL 下 build 通过
* [ ] diff 可证:无算法逻辑改动、无 guide/阈值等标定值数值改动

## Definition of Done

* WSL build green
* replay 行为一致性验证通过
* 收尾看 diff:无算法改动、无标定值改动、无吞错误、无第二真相源残留

## Out of Scope(explicit)

* 日志事件格式重设计(FrameSummary/CircleState 等)——会改输出字符串,打断 drive43 标定分析,标定结束后再单独做
* C. camera 尺寸错首次停机(continue→停机,轻微行为变更)——用户明确不做
* D. control_config sanitize(clamp 非法值,改边界行为)
* E. control.cpp solve() 拆 stage 函数(量大,单独任务)
* F. guide scale 从桥层搬迁(涉标定,需上车回归)
* G. 元素仲裁层去投票(动元素时序,碰算法)
* 圆环/十字状态机算法改动(B 搜索方向等)

## Technical Notes

* 构建/git 环境:WSL(Git Bash 缺 make,.git 指向 /mnt/e)。
* 标定基线:drive43 重复性测试中(`docs/in-075-running-081-baseline.md`),日志格式变更会破坏既有分析脚本解析。
