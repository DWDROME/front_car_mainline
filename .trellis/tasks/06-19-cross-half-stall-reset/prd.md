# 半十字无线短时低速直行

## Goal

实车进入 `CROSS_HALF` 后，如果当前帧远线无法生成选线，差速车会因 `line_found=0` 停车，图像不再推进，导致远线没有机会重新进入视野。本任务将参考车“失败帧仍会继续往前滚”的物理前提显式移植为半十字无线短时低速直行：只在 `CROSS_HALF` 无线时给一个有上限的直行窗口，帮助图像继续推进。

## Requirements

* 仅处理 `CROSS_HALF` 当前帧无线，不改远线搜索算法。
* `CROSS_HALF` 无线时短时低速直行，模拟参考舵机车失败帧仍继续运动的物理行为。
* 短时直行必须有明确时间/帧数上限；超过上限仍无线则回到正常无线停车行为。
* 直行期间不生成中线、不复用旧帧、不新增近线 fallback。
* 正常有当前帧选线或离开 `CROSS_HALF` 时必须清零 relay/creep 状态。
* 触发和超时必须显式打印诊断日志，便于实车确认。

## Acceptance Criteria

* [ ] `CROSS_HALF` 无线时，在限定窗口内控制输入保持低速直行。
* [ ] 窗口内 `guide_error` 为 0，不沿用旧误差。
* [ ] 超过窗口仍无线时控制层停车。
* [ ] 有选线或未处于 `CROSS_HALF` 时 relay/creep 状态清零。
* [ ] 实现不增加旧帧复用或伪造线逻辑。
* [ ] 通过最小相关编译/测试或说明未运行原因。

## Definition of Done

* 代码改动小而集中。
* 运行 `git diff --check`。
* 尽量运行项目最小测试链。
* 更新 `PORTING.md` 记录移植边界和原因。

## Technical Approach

在 runner/control 输入边界新增 `CROSS_HALF` 无线短时直行窗口。tracking 仍如实返回无线；runner 在 `cross_type == CROSS_HALF && line_found == 0` 且窗口未超时时，将控制输入设为 `line_found=1`、`element_active=1`、`guide_error=0`，使控制层按元素速度低速直行。窗口超时后不再覆盖 `line_found`，恢复正常停车。

## Decision

Context: ATG 参考车是舵机车，远线失败帧仍会继续滚动，图像会变化；当前差速车在 `line_found=0` 时停车，图像冻结，`CROSS_HALF` 远线依赖会变成死锁。

Decision: 采用 bounded relay/creep：半十字无线时短时低速直行，不复位十字状态，不做近线 fallback，也不调整远线搜索阈值。

Consequences: 更接近参考车“继续往前滚”的物理前提；风险是无当前帧中线时会短时开环前进，因此必须有低速、零转向、短窗口和显式日志。

## Out of Scope

* 不调整 `cross_farline_L/R` 的阈值、锚点或 IPM 逻辑。
* 不在 `CROSS_HALF` 内新增近线 fallback。
* 不复位 `cross_type` 或清理半十字 flags。
* 不解决半十字偏左根因。

## Technical Notes

* `reference_step.c::select_work_line()` 在 `CROSS_HALF` 使用 `far_rpts0s/far_rpts1s` 生成工作线。
* `cross.c::run_cross()` 中 `CROSS_HALF` 正常退出依赖 `not_have_line > 2` 后近线重新出现。
* `control.cpp` 在 `line_found=0` 时清状态并停车；本任务的 relay/creep 应放在 runner 生成控制输入的位置。
