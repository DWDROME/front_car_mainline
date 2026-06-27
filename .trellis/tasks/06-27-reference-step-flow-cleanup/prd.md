# 整理 reference_step.c 状态机主流程

## Goal

把 `atg_reference/port/reference_step.c` 从中央大杂烩整理成清楚的状态机调度流程。目标是提高可读性和审查性，不改变元素优先级、状态切换条件、阈值或算法结果。

## Requirements

* 重点拆分 `run_atg_elements()`、`select_work_line()`、`normalize_selected_line()` 三个函数。
* `run_atg_elements()` 保持现有优先级和 return 行为，整理为：
  * `keep_disabled_elements_idle()`
  * `run_active_element()`
  * `check_new_element()`
  * `run_new_element()`
  * 末尾和早退前继续调用 `keep_disabled_elements_idle()`
* `run_active_element()` 只处理已经激活的元素继续执行。
* `check_new_element()` 只负责在无活跃元素时按原优先级检测新元素。
* `run_new_element()` 只负责 check 后刚激活的元素执行。
* `select_work_line()` 整理为：
  * `g_selected_line_source = "none";`
  * `select_cross_far_line()`
  * `build_circle_spliced_lines()`
  * `select_circle_line()`
  * `select_normal_line()`
  * `log_selected_line()`
* `select_cross_far_line()` 处理 `CROSS_IN` / `CROSS_HALF` 的 `far_left` / `far_right`，并保留原有 `GARAGE_FOUND_*` 远线旁路。
* `select_circle_line()` 只处理 `circle_in_c`、`circle_running_fixed`、`circle_out_fixed`、`out_rptsc1`。
* `select_normal_line()` 只按 `track_type` 选择 `rptsc0` / `rptsc1`。
* `log_selected_line()` 从 `select_work_line()` 拆出，避免日志污染选线主流程。
* `normalize_selected_line()` 整理为：
  * `selected_line_ok()`
  * `update_vehicle_ref_ipm()`
  * `find_selected_line_begin()`
  * `resample_selected_line()`
  * `update_aim_points()`
  * `calc_guides()`
* 允许继续使用现有全局变量、短函数名、短局部变量名、左右逻辑复制和 `===` 中文注释分区。
* 可适当缩短顶部内部常量名，例如 `RAW_LEFT_ANCHOR_X` → `L_ANCHOR_X`、`CIRCLE_RUNNING_NATURAL_MIN_POINTS` → `CIRCLE_NATURAL_MIN`，但不得改数值。

## Acceptance Criteria

* [ ] `atg_reference_process_frame()` 主流程读起来是：准备本帧、基础搜线、找角点、运行元素状态机、选控制线、归一化控制线、收尾检查。
* [ ] `run_atg_elements()` 的结构符合用户给定目标形态。
* [ ] `select_work_line()` 的结构符合用户给定目标形态。
* [ ] `normalize_selected_line()` 的结构符合用户给定目标形态。
* [ ] 不新增 `ElementOps`、`ElementScheduler`、`Context`、`Config`、`Pipeline` 或类似通用框架结构体。
* [ ] 不把圆环、十字、坡道、Y 路抽象成统一 Element 对象。
* [ ] 不引入大量函数参数；新 helper 优先使用现有全局变量。
* [ ] 不改元素优先级、状态切换条件、阈值和算法结果。
* [ ] 保留 `build_fixed_left_center_for_circle()` / `build_fixed_right_center_for_circle()` 的左右复制。
* [ ] 保留 `build_circle_left_in_center_by_c()` / `build_circle_right_in_center_by_c()` 的左右复制。

## Definition of Done

* 代码 diff 小而可审查，属于行为保持重构。
* 运行最小相关验证；至少执行 `git diff --check`，并尝试项目可用的构建/测试命令。
* 收尾前检查 diff，确认没有隐藏 fallback、第二真相源、无关算法改动或敏感信息。

## Technical Approach

采用局部函数提取，不引入工程化框架。拆分粒度以三条主流程为边界：

* 元素状态机：活跃元素继续执行、无活跃元素检测新元素、刚激活元素执行。
* 控制线选择：十字远线优先、圆环补线其次、普通中心线兜底。
* 控制线归一化：输入检查、车辆参考点 IPM、起点查找、重采样、目标点更新、导引量计算。

## Decision (ADR-lite)

**Context**: `reference_step.c` 是 ATG 参考算法到当前车控制输入之间的移植层，当前主要问题是调度流程集中在大函数里，阅读时难以区分状态机阶段、选线策略和归一化步骤。

**Decision**: 只做函数提取和章节整理，不设计通用元素框架，不改变已有状态机条件和阈值。

**Consequences**: 可读性提升，行为风险较低；仍保留全局变量和左右复制，以便嵌入式调试时逐行对照现有逻辑。

## Out of Scope

* 不修正或调整圆环、十字、坡道、Y 路算法行为。
* 不修改元素优先级。
* 不恢复、删除或新增状态机条件。
* 不新增配置系统、调度框架、元素对象模型或 pipeline。
* 不合并左右补线函数。

## Technical Notes

* 目标文件：`atg_reference/port/reference_step.c`。
* 当前已有未提交 WIP 改动，尤其 `run_atg_elements()` 已有阶段注释和部分重排；本任务在现状上继续整理，不回滚用户改动。
* 已读规范：
  * `.trellis/spec/quality/embedded-tracking-guidelines.md`
  * `.trellis/spec/quality/refactoring-and-diagnostic-discipline.md`
  * `.trellis/spec/tracking/critical-audit-guide.md`
* 本任务预期为行为保持重构；若实现中发现必须改行为，应停止并回到需求确认。
