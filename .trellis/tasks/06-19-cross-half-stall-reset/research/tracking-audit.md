# 半十字无线短时低速直行审计

## Symptom

实车进入十字后偏左，在十字中间停顿；如果某帧重新识别到远线可以继续走，否则停在原地。该现象符合 `CROSS_HALF` 远线选线失败后 `line_found=0`、差速车停车、图像冻结的死锁链路。

## Four Audit Roles

### Reference Contract

`atg_reference/Project/USER/Cpu0_Main.c` 的选线主链在 `cross_type == CROSS_IN || cross_type == CROSS_HALF` 时进入远线分支；普通近线分支只在非十字/车库远线场景使用。`atg_reference/Project/CODE/cross.c` 中 `CROSS_HALF` 退出依赖 `not_have_line > 2` 后左右近线重新出现。

### Current Implementation

`atg_reference/port/reference_step.c::select_work_line()` 保留该远线分支：`CROSS_HALF` 时按 `track_type` 从 `far_rpts0s/far_rpts1s` 生成 `rpts`。若远线为空，`normalize_selected_line()` 返回失败，`tracking_process_frame()` 发布 `line_found=0`，控制层停车。当前只有 `exit_circle_after_stall()` 管环岛连续无选线，没有十字等价保护。

### Git Regression

`exit_circle_after_stall()` 由 `f15b77b fix(atg-ref): 收敛实车元素入环控制诊断` 引入，用于解决差速车在环岛状态中无选线停车后的状态死锁。`CROSS_HALF` 主链来自 `3ee8047`/`fad5e28` 的 ATG 元素接入，未补充对应移植层行为。

### Trellis / Check Gate

本任务只实现 `CROSS_HALF` 无线短时低速直行，不调整远线阈值、IPM、近线 fallback 或偏左根因。验证目标为 diff 检查和项目最小测试。

## Change Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `Cpu0_Main.c` 在 `CROSS_IN/CROSS_HALF` 使用远线选线；参考车失败帧仍会继续运动，图像会变化。 | 当前差速车 `line_found=0` 立即停车，图像冻结；`CROSS_HALF` 远线失败后没有新视角。 | 在 runner/control 输入边界增加 bounded relay/creep：`CROSS_HALF` 无线时短时按元素低速、零 guide 前进。 | 显式翻译参考车“失败帧仍会向前滚”的物理前提，给远线重新进入视野的机会。 | 不生成中线、不复用旧帧、不新增近线 fallback；tracking 仍报告无线，控制输入只在限定窗口内开环低速直行，超时恢复停车。 |

## Out Of Scope

* 不修改 `cross_farline_L/R` 远线搜索阈值。
* 不新增 `CROSS_HALF` 内近线 fallback。
* 不复位 `cross_type` 或清理半十字 flags。
* 不解决偏左根因。
