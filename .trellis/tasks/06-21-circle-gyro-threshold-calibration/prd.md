# 圆环陀螺与距离阈值测算 PRD

## Goal

建立一套可上车执行的圆环阶段阈值测算流程，用当前代码里的陀螺积分和编码器距离口径，校准 `600 / 2000 / 2500 / 3550 / 16000` 这些阈值是否适合当前车、当前摄像头/IPM、当前速度与圆环固定动作。

本任务先产出测算方案和最小采数要求。除非后续明确进入实现阶段，否则不改圆环状态机策略。

## What I Already Know

* 当前圆环状态机在 `atg_reference/Project/CODE/circle.c`。
* 当前圆环陀螺积分变量是 `static float circle_heading_rad`，只在 `circle.c` 内部可见。
* 当前 live 主链在 `code/app/runners.cpp` 中调用：
  * `drive_output_read_feedback(&fb, control_period_ms)`
  * `rt->encoder_total += atg_distance_counts_from_encoder_delta(fb)`
  * `update_circle_heading(fb.actual_yaw_rate_mrad_s / 1000.0F, fb.period_ms, fb.actual_yaw_rate_valid)`
* `drive_output_read_feedback()` 使用实际经过时间 `fb.period_ms`；时钟异常才回退到标称 `control_period_ms`。
* `update_circle_heading()` 的积分口径：
  * `circle_type == CIRCLE_NONE` 时清零并返回。
  * `valid == 0` 或 `period_ms <= 0` 时不积分。
  * `fabs(yaw_rate_rad_s) <= 0.065 rad/s` 时不积分。
  * 否则 `circle_heading_rad += yaw_rate_rad_s * period_ms / 1000`。
* 阈值单位是 `0.1 deg`：
  * `600` = `60.0 deg`
  * `2000` = `200.0 deg`
  * `2500` = `250.0 deg`
  * `3550` = `355.0 deg`
* `16000` 不是陀螺阈值。它是 `RUNNING -> OUT` 的编码器距离保护值。
* `ENCODER_PER_METER = 5800`，所以：
  * `2000` counts = `0.345 m`
  * `4500` counts = `0.776 m`
  * `7500` counts = `1.293 m`
  * `4000` counts = `0.690 m`
  * `16000` counts = `2.759 m`
* replay/offline/analyze 路径不能完整验证 gyro/distance 阶段推进。完整测算必须上 live 或提供等价 IMU/encoder 注入。

## Problem

当前 `600 / 2000 / 2500 / 3550` 来自参考思路，但它们是否匹配当前车，需要按本车的实际陀螺比例、实际速度、实际圆环固定动作位置来验证。

如果不测：

* `IN -> RUNNING` 可能太早，固定动作不足，车还没进稳就切到环内走线。
* `RUNNING -> OUT` 可能太早或太晚，导致提前外飘或错过出环。
* `OUT -> END` 可能提前结束出环补线，或者拖太久。
* `END -> NONE` 可能回普通赛道太早/太晚。
* `16000` 如果太小，会替代 gyro 正常触发；如果太大，只能很晚救出 `RUNNING`。

## Requirements

* 使用现有陀螺积分口径测算，不引入第二套角度算法。
* 使用现有编码器 `total_distence` 口径测算距离，不引入第二套里程算法。
* 测算入口使用现有 `front_car_mainline` live 程序，不新建第二个可执行程序。
* 标定输出用一个明确的临时环境变量打开，默认关闭。
* 区分两类阈值：
  * 陀螺阈值：`600 / 2000 / 2500 / 3550`，单位 `0.1 deg`。
  * 距离阈值：`16000`，单位 encoder counts。
* 测算必须记录每次状态转换发生时的：
  * 转换前状态
  * 转换后状态
  * 触发原因：gyro / distance / entry evidence
  * `circle_heading_deg10`
  * `total_distence`
  * `actual_yaw_rate_valid`
  * `actual_yaw_rate_mrad_s`
  * `period_ms`
* 允许增加最小临时标定输出，但不得增加候选层、诊断状态机、YAML 参数层或控制层圆环特判。
* 若新增临时输出，输出必须能被注释/移除，不改变状态机行为。
* 测算结果必须形成一张阈值表，说明每个阈值是否保留、增大、减小，以及依据。

## Calculation Contract

### Gyro Integration

当前代码等价公式：

```text
yaw_rate_rad_s = actual_yaw_rate_mrad_s / 1000
dt_s           = period_ms / 1000
heading_rad   += yaw_rate_rad_s * dt_s
heading_deg10 = abs(heading_rad) * 1800 / pi
```

每帧增量：

```text
delta_deg10 = actual_yaw_rate_mrad_s * period_ms * 1800 / (pi * 1000000)
            ~= actual_yaw_rate_mrad_s * period_ms * 0.00057296
```

示例：

```text
actual_yaw_rate_mrad_s = 1000
period_ms = 10
delta_deg10 ~= 5.73
delta_deg ~= 0.573 deg
```

### Distance Conversion

当前距离口径：

```text
meters = total_distence / 5800.0
counts = meters * 5800.0
```

`16000` 当前等价：

```text
16000 / 5800 = 2.759 m
```

它只能从实车 `RUNNING` 阶段的正常里程分布估算，不能从陀螺角直接推导。

## Program Entry

本测算不需要单独程序。使用现有主程序：

```text
code/build/front_car_mainline
```

入口规则来自 `code/app/main.cpp`：

* 不带参数：进入 live 模式，能读摄像头、编码器、IMU，并调用 `update_circle_heading()`。
* `--input` / `--analyze` / `--replay`：只能验证图像链路，不能完整验证 gyro/distance 圆环阶段推进。

因此本任务的有效测算入口只有 live：

```bash
./front_car_mainline
```

建议新增一个临时环境变量：

```bash
FRONT_CAR_CIRCLE_CAL_LOG=1
```

语义：

* 默认 `0`：不输出圆环标定行。
* `1`：只在圆环状态转换点输出 `ATGCircleCal:` 行。

不建议新增 CLI 参数，因为当前 `parse_options()` 对未知参数显式失败；live 调试开关已经主要走环境变量。

## Measurement Plan

### Stage 0: Static IMU Sanity Check

目的：确认陀螺不飘到影响圆环阈值。

步骤：

1. 车静止，保持 `5-10s`。
2. 观察 `actual_yaw_rate_valid` 是否稳定为 `1`。
3. 观察 `actual_yaw_rate_mrad_s` 是否围绕 0，小幅噪声应被 `0.065 rad/s` deadzone 吃掉。

通过标准：

* 静止时积分不应快速增长。
* 若静止积分明显增长，先处理陀螺零偏/比例，不调圆环阈值。

### Stage 1: Manual Angle Scale Check

目的：确认 `gyro_raw_to_rad_s` 与 yaw 轴方向/比例大致正确。

步骤：

1. 不跑圆环，低风险方式让车原地或手动转过约 `90 deg`。
2. 用同一积分口径计算 `heading_deg10`。
3. 目标值约为 `900 deg10`。

判定：

* `900 +/- 15%`：比例可先用于圆环测算。
* 明显偏小：`gyro_raw_to_rad_s` 或轴选择可能偏小。
* 明显偏大：`gyro_raw_to_rad_s` 或单位转换可能偏大。
* 符号不作为第一问题，因为圆环状态机使用 `fabsf()`。

推荐命令：

```bash
killall -9 front_car_mainline 2>/dev/null || true
FRONT_CAR_ENABLE_DRIVE=0 \
FRONT_CAR_FORCE_LIVE_LOG=1 \
FRONT_CAR_PRINT_DIV=1 \
FRONT_CAR_RUN_MS=10000 \
FRONT_CAR_CIRCLE_CAL_LOG=1 \
./front_car_mainline
```

说明：

* `FRONT_CAR_ENABLE_DRIVE=0`：不下发电机，只看 IMU/视觉/live 日志。
* `FRONT_CAR_FORCE_LIVE_LOG=1`：现有 live 日志每帧输出，便于看 `actual` yaw。
* `FRONT_CAR_CIRCLE_CAL_LOG=1`：待实现的圆环标定行开关。
* `FRONT_CAR_RUN_MS=10000`：10 秒自动退出，避免无界 live 进程。

### Stage 2: One-Lap Circle Calibration Run

目的：记录一圈圆环内每个状态转换点的角度和距离。

每次状态转换记录一行：

```text
ATGCircleCal: from=CIRCLE_LEFT_IN to=CIRCLE_LEFT_RUNNING reason=gyro heading_deg10=612 dist=1840 yaw_valid=1 yaw_mrad_s=980 period_ms=10
```

左环和右环分别至少采：

* 慢速 2 圈
* 目标比赛速度 2 圈
* 如果左右圆环行为明显不同，则左右分别保留阈值建议。

推荐命令：

```bash
killall -9 front_car_mainline 2>/dev/null || true
FRONT_CAR_ENABLE_DRIVE=1 \
FRONT_CAR_PRINT_DIV=1 \
FRONT_CAR_RUN_MS=15000 \
FRONT_CAR_CIRCLE_CAL_LOG=1 \
./front_car_mainline | tee /tmp/front_car_circle_cal.log
```

如果只想降低普通 live 日志噪声：

```bash
killall -9 front_car_mainline 2>/dev/null || true
FRONT_CAR_ENABLE_DRIVE=1 \
FRONT_CAR_PRINT_DIV=20 \
FRONT_CAR_RUN_MS=15000 \
FRONT_CAR_CIRCLE_CAL_LOG=1 \
./front_car_mainline | tee /tmp/front_car_circle_cal.log
```

采数后先看：

```bash
rg "ATGCircleCal" /tmp/front_car_circle_cal.log
```

### Stage 3: Threshold Fit

对每个阶段做表：

| Transition | Current Threshold | Observed Good Range | Trigger Used | Decision |
| --- | ---: | ---: | --- | --- |
| `IN -> RUNNING` | `600` | TBD | gyro/distance | keep/up/down |
| `RUNNING -> OUT` | `2000` | TBD | gyro/distance | keep/up/down |
| `OUT -> END` | `2500` | TBD | gyro/distance | keep/up/down |
| `END -> NONE` | `3550` | TBD | gyro/distance | keep/up/down |
| `RUNNING` distance guard | `16000` | TBD | distance | keep/up/down |

调参原则：

* 如果某阶段总是由 distance 触发，而 gyro 没到阈值：该 gyro 阈值可能过大，或陀螺积分偏小/valid 掉线。
* 如果某阶段 gyro 触发后车明显太早进入下一阶段：对应 gyro 阈值偏小。
* 如果某阶段 gyro 触发后车明显太晚：对应 gyro 阈值偏大。
* `16000` 应高于正常 `RUNNING` 里程，低于“明显错过出环还不切”的危险里程。
* `16000` 建议初始拟合：

```text
RUNNING_FORCE_OUT = normal_running_dist_counts * 1.3 ~ 1.5
```

但最终必须以实车安全边界为准。

## Minimal Instrumentation Approach

推荐做法：只在圆环状态转换点输出标定行。

不推荐每帧输出全部数据，因为会污染 live 日志并影响阅读。每帧原始 yaw 只有在发现 `heading_deg10` 计算异常时再临时打开。

最小实现形态：

* 在 `circle.c` 内增加一个只读计算函数：

```c
static int circle_heading_deg10(void)
{
    return (int)(fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10);
}
```

* 在每个 `circle_type = ...` 转换前后打印：

```c
printf("ATGCircleCal: from=%s to=%s reason=%s heading_deg10=%d dist=%d\n",
       circle_type_name[from],
       circle_type_name[to],
       reason,
       circle_heading_deg10(),
       total_distence);
```

限制：

* `circle.c` 当前不知道 `actual_yaw_rate_valid / actual_yaw_rate_mrad_s / period_ms`。
* 如果必须把 yaw 原始值也打在同一行，需要从 `runners.cpp` 暴露最近一次 feedback，或在已有 live 日志中同步查同一帧。
* 第一版优先只打 `state + reason + heading_deg10 + total_distence`，因为这是调阈值的核心证据。

## Implementation Contract

如果进入实现阶段，第一版只做下面这些，不扩大：

1. 在 `circle.c` 内新增 `circle_heading_deg10()`。
2. 在 `circle.c` 内新增一个极小打印函数或局部 `printf`。
3. 打印函数由 `FRONT_CAR_CIRCLE_CAL_LOG=1` 控制。
4. 每个圆环状态转换点打印一行。
5. 不改转换条件、不改阈值、不改控制层、不改 report schema。

第一版输出字段：

```text
ATGCircleCal: from=<state> to=<state> reason=<gyro|distance|entry> heading_deg10=<n> dist=<n>
```

第二版才考虑接入最近一次 IMU feedback：

```text
yaw_valid=<0|1> yaw_mrad_s=<n> period_ms=<n>
```

第二版需要在 `runners.cpp` 和 `circle.c` 之间传递最近 feedback，属于更大接口面；没有必要一开始做。

建议触发原因命名：

| Transition | reason |
| --- | --- |
| `BEGIN -> IN` by `none_*_line > 0` and distance | `entry_distance` |
| `BEGIN -> IN` by `none_*_line > 0` and gyro | `entry_gyro` |
| `IN -> RUNNING` by gyro | `gyro` |
| `IN -> RUNNING` by distance | `distance` |
| `RUNNING -> OUT` by gyro | `gyro` |
| `RUNNING -> OUT` by distance | `distance` |
| `OUT -> END` by gyro | `gyro` |
| `OUT -> END` by distance | `distance` |
| `END -> NONE` by gyro | `gyro` |
| `END -> NONE` by distance | `distance` |

## Acceptance Criteria

* [ ] PRD 记录当前积分公式、距离换算公式、阈值单位。
* [ ] PRD 明确测算程序入口：`front_car_mainline` live 模式。
* [ ] PRD 明确临时开关：`FRONT_CAR_CIRCLE_CAL_LOG=1`。
* [ ] PRD 给出静止/手动角度/实车圆环测试命令。
* [ ] 明确区分 gyro 阈值和 distance 阈值。
* [ ] 定义上车采数步骤：静止、90 度比例、左环/右环 live 圈。
* [ ] 定义每次状态转换必须记录的字段。
* [ ] 定义阈值调整规则，尤其是 `16000` 的 counts/meter 关系。
* [ ] 若进入实现阶段，临时输出不改变状态机行为，且通过 host/cross build。
* [ ] 测完后形成实际阈值表，能说明每个阈值保留或修改的原因。

## Definition of Done

Planning done:

* `prd.md` 已建立。
* 方案能直接指导上车采数。
* 没有把测算任务混入圆环状态机策略改动。

Implementation done, if later approved:

* 最小标定输出已实现。
* host build 通过。
* cross build 通过。
* `FRONT_CAR_CIRCLE_CAL_LOG=0` 时没有新增标定输出。
* `FRONT_CAR_CIRCLE_CAL_LOG=1` 时状态转换输出 `ATGCircleCal:`。
* 至少一组 live 圆环日志被采集并转成阈值表。

## Out of Scope

* 不在本任务重写 `check_circle()` / `Half_check.c`。
* 不在本任务改固定动作几何。
* 不在本任务调巡线控制器。
* 不引入 YAML/CLI 参数化圆环阈值。
* 不新增候选层、诊断状态机或 replay IMU 注入框架。
* 不用 replay/offline 证明 gyro/distance 阶段推进正确。

## Technical Notes

Relevant files:

* `atg_reference/Project/CODE/circle.c`
  * `CIRCLE_HEADING_*`
  * `CIRCLE_RUNNING_FORCE_OUT_COUNTS`
  * `update_circle_heading()`
  * `circle_heading_abs_ge()`
  * `run_circle()`
* `code/app/runners.cpp`
  * `drive_output_read_feedback()`
  * `atg_distance_counts_from_encoder_delta()`
  * `update_circle_heading()` call order
* `code/drivers/drive_output.cpp`
  * actual `period_ms`
  * `actual_yaw_rate_mrad_s`
  * `actual_yaw_rate_valid`
* `atg_reference/port/reference_step.c`
  * `update_distance_counters()`
  * `total_distence`
  * `Count_dis_Flag`

Open question for implementation phase:

* 标定输出是否只打 `state + reason + heading_deg10 + dist`，还是需要把 `yaw_valid / yaw_mrad_s / period_ms` 也接到同一行。
