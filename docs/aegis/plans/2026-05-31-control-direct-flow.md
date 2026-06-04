# Goal

把 `code/core/control.cpp` 从“闭环控制库写法”收成 `front_car_mainline` 当前约定的现场过程式风格。第一刀以行为保持为边界：保留现有输入输出、参数、yaw 反馈、轮速 PI 和 `guide_error -> target_yaw -> duty -> drive_output_apply` 主链，只改变代码形态，让现场队员能顺着一帧控制流程读下去。

# Architecture

控制主链仍由 `code/app/runners.cpp` 调度：

```text
tracking_process_frame(rt)
-> drive_output_read_feedback(&fb, control_period_ms)
-> solve_runtime_with_feedback(rt, &fb, &rt->control)
-> drive_output_apply(&rt->control)
```

本计划只改 `control.cpp` 内部组织方式，不新增 owner 文件，不新增 wrapper，不把控制逻辑搬到驱动层。

# Tech Stack

- C++17
- 固定数组和文件内全局变量
- 逐飞 LS2K0300 用户态工程
- 验证入口：`bash "code/test.sh" --host`

# Baseline/Authority Refs

- `AGENTS.md`
- `code/core/control.cpp`
- `code/core/control.hpp`
- `utils/types.hpp`
- `code/drivers/drive_output.cpp`
- 正例风格：`code/drivers/device.cpp`、`code/tracking/cross.cpp`、`code/tracking/mainline.cpp`

# Compatibility Boundary

必须保持：

- `solve_runtime(const runtime_t *rt, control_state_t *ctrl)` 签名不变。
- `solve_runtime_with_feedback(const runtime_t *rt, const control_feedback_t *fb, control_state_t *ctrl)` 签名不变。
- `control_state_t` 和 `control_feedback_t` 不变。
- `front_car_mainline.yaml` 字段不增不删。
- `drive_output.cpp` 的硬件映射不变：`left -> PWM2`、`right -> PWM1`、`QUAD1=left`、`QUAD2=right`。
- 不新增 fallback，不新增旧新双路线，不新增 mock 成功。

# Verification

基础验证：

```bash
bash "code/test.sh" --host
```

静态风格闸：

```bash
python3 - <<'PY'
from pathlib import Path
s = Path("code/core/control.cpp").read_text()
bad = [
    "struct loop_t",
    "outer_pd(",
    "inner_pi(",
    "wheel_pi(",
    " ? ",
    " : ",
]
hit = [x for x in bad if x in s]
if hit:
    print("style gate failed:", ", ".join(hit))
    raise SystemExit(1)
print("style gate passed: direct control flow")
PY
```

板端验证在用户确认板子在线时执行：

```bash
REMOTE_IP=192.168.0.102 MAKE_JOBS=4 bash "code/test.sh" --upload
```

# Plan Basis

## Facts

- `control.cpp` 当前 201 行，集中包含反馈滤波、视觉外环、yaw 内环、差速运动学、左右轮 PI。
- `drive_output.cpp` 已负责真实硬件映射和下发，`control.cpp` 不应知道 PWM1/PWM2 细节。
- `AGENTS.md` 已要求 `control.cpp` 后续收成现场可读直流程。

## Assumptions

- 当前控制行为虽然难读，但最近仍作为可运行基线使用。
- 第一刀不改变控制律，能降低实车风险。
- 是否删除 yaw 内环或轮速 PI 属于行为变化，需要实车日志和用户确认后单独做。

## Unknowns

- 当前 yaw 反馈和轮速 PI 在实车上是否确实收益大于复杂度。
- 板端 `/root/front_car_mainline.yaml` 是否与本地文件一致。

## Ripple Signal Triage

- 影响直接消费者：`code/app/runners.cpp`、`code/drivers/drive_output.cpp`、`utils/types.hpp`。
- 不影响 tracking 中线生成。
- 不影响 assistant 图传显示。
- 不影响 K3 拍照。

# Files

## Modify

- `code/core/control.cpp`

## Read Only

- `AGENTS.md`
- `code/core/control.hpp`
- `utils/types.hpp`
- `code/app/runners.cpp`
- `code/drivers/drive_output.cpp`
- `code/core/config.hpp`

## Do Not Modify

- `code/drivers/drive_output.cpp`
- `front_car_mainline.yaml`
- `front_car_control_calib`
- 外部 RT1064 参考工程

# Compatibility

本计划是行为保持式重写。允许变化的是代码形态：

- `loop_t g` 改成文件内全局变量。
- `outer_pd`、`inner_pi`、`wheel_pi` 的逻辑内联到 `solve()` 的阶段块。
- 三元表达式改成 `if/else`。
- 压缩表达式拆成固定局部变量。

不允许变化的是运行语义：

- `zebra.stop_line` 仍然触发停车请求。
- 无线或被拒绝时仍然清控制状态并输出无效。
- `target_yaw_rate_mrad_s` 仍记录视觉外环输出，不改成修正后的 `yaw_cmd`。
- `left_duty/right_duty` 仍由左右轮 PI 计算。

# Plan Pressure Test

- Owner / contract / retirement: `control.cpp` 是控制计算 owner；旧 helper 和 `loop_t` 在本计划中退休。
- Verification scope: 静态风格闸 + host 编译；板端上传和实车行为由用户现场确认。
- Task executability: 单文件替换，公开接口不动，命令明确。
- Pressure result: proceed。

# Plan-Time Complexity Check

- Target files: `code/core/control.cpp`
- Existing size / shape signals: 201 行，单文件可控，但存在控制库式 helper、状态 struct、三元表达式、紧凑表达式。
- Owner fit: 控制计算仍属于 `control.cpp`。
- Add-in-place risk: 新增 helper 或新文件会和 AGENTS 的少工程化方向冲突。
- Better file boundary: 不拆文件，直接在当前 owner 内收直。
- Recommendation: edit-in-place。

# Tasks

## Task 1: 用静态闸固定“必须收直”的目标

Files:

- Modify: none
- Test command only: `code/core/control.cpp`

Why:

先把当前坏味道变成可重复检查的失败信号，防止重写后又回到 `outer_pd/inner_pi/wheel_pi/loop_t` 这种库式形态。

Impact/Compatibility:

- 不改源码。
- 不影响板端。

Verification:

```bash
python3 - <<'PY'
from pathlib import Path
s = Path("code/core/control.cpp").read_text()
bad = [
    "struct loop_t",
    "outer_pd(",
    "inner_pi(",
    "wheel_pi(",
    " ? ",
    " : ",
]
hit = [x for x in bad if x in s]
if hit:
    print("style gate failed:", ", ".join(hit))
    raise SystemExit(1)
print("style gate passed: direct control flow")
PY
```

Expected before Task 2:

```text
style gate failed: struct loop_t, outer_pd(, inner_pi(, wheel_pi(
```

Steps:

- [ ] Write test: run the Python style gate above from project root.
- [ ] Verify RED: confirm it exits with code `1` and prints `style gate failed`.
- [ ] Minimal code: no source change in this task; keep the failing command as the acceptance gate for Task 2.
- [ ] Verify GREEN: not applicable to this task because the current baseline is intentionally red.
- [ ] Commit: do not commit this task separately.

## Task 2: Replace `control.cpp` with direct staged flow

Files:

- Modify: `code/core/control.cpp`

Why:

把一帧控制计算写成现场能顺着读的阶段流：停车/无线门控、反馈换算、视觉外环、yaw 修正、左右目标、左右 duty。保留现有控制行为，去掉库式 helper 形态。

Impact/Compatibility:

- Public API unchanged.
- Control output fields unchanged.
- No new fallback.
- No new config.

Repair Track:

- Root cause: 控制逻辑以通用闭环库方式组织，现场读代码时需要在多个 helper 和状态 struct 之间跳转。
- Canonical owner: `code/core/control.cpp`
- Stable repair: 单文件直流程重写，不拆 owner，不新增 wrapper。
- Compatibility: 保持 `control_state_t`、`control_feedback_t`、yaml 字段和驱动映射不变。
- Verification: style gate + host build。

Retirement Track:

- Retire immediately: `struct loop_t`、`outer_pd()`、`inner_pi()`、`wheel_pi()`。
- Keep: 必要的 `clip_f()`、`count_to_rps()`、`yaw_avg()` 这种短数学段。
- Delete trigger: Task 2 replacement completed and host build passes。

Minimal code:

Replace the full contents of `code/core/control.cpp` with:

```cpp
#include "control.hpp"

#include "config.hpp"
#include "clip.hpp"

#include <cmath>

// 控制主链：
//   guide_error -> target_yaw -> yaw_cmd -> left/right duty
// 这里保留现有 yaw 反馈和左右轮 PI 行为，但按现场调车顺序直接展开。

namespace
{
const float k_counts_per_rev = 1024.0F * 4.0F;
const float k_pi = 3.14159265358979323846F;
const float k_speed_i_max = 20.0F;
const float k_yaw_i_max = 2.0F;
const int k_yaw_window_max = 32;

float g_left_i = 0.0F;
float g_right_i = 0.0F;
float g_yaw_i = 0.0F;
float g_last_target_yaw = 0.0F;
float g_last_err = 0.0F;
int g_has_err = 0;
float g_left_rps = 0.0F;
float g_right_rps = 0.0F;
int g_rps_ready = 0;
float g_yaw_buf[k_yaw_window_max] = {};
int g_yaw_num = 0;
int g_yaw_pos = 0;

void clear_state()
{
    g_left_i = 0.0F;
    g_right_i = 0.0F;
    g_yaw_i = 0.0F;
    g_last_target_yaw = 0.0F;
    g_last_err = 0.0F;
    g_has_err = 0;
    g_left_rps = 0.0F;
    g_right_rps = 0.0F;
    g_rps_ready = 0;
    g_yaw_num = 0;
    g_yaw_pos = 0;
    for(int i = 0; i < k_yaw_window_max; ++i)
    {
        g_yaw_buf[i] = 0.0F;
    }
}

int round_i32(float v)
{
    return static_cast<int>(std::lround(v));
}

float clip_f(float v, float minv, float maxv)
{
    if(v < minv)
    {
        return minv;
    }
    if(v > maxv)
    {
        return maxv;
    }
    return v;
}

float count_to_rps(int cnt, int ms)
{
    if(ms <= 0)
    {
        ms = 10;
    }
    return static_cast<float>(cnt) / k_counts_per_rev * 1000.0F / static_cast<float>(ms);
}

int line_ok(const runtime_t *rt)
{
    if(rt->track.track_type == TRACK_TYPE_NONE)
    {
        return 0;
    }
    if(rt->track.reject_reason != TRACK_REJECT_NONE)
    {
        return 0;
    }
    return 1;
}

float yaw_avg(float yaw, int window)
{
    window = clip_i(window, 1, k_yaw_window_max);
    g_yaw_buf[g_yaw_pos] = yaw;
    g_yaw_pos++;
    if(g_yaw_pos >= window)
    {
        g_yaw_pos = 0;
    }
    if(g_yaw_num < window)
    {
        g_yaw_num++;
    }

    float sum = 0.0F;
    for(int i = 0; i < g_yaw_num; ++i)
    {
        sum += g_yaw_buf[i];
    }
    return sum / static_cast<float>(g_yaw_num);
}

void solve(const runtime_t *rt, const control_feedback_t *fb, control_state_t *out)
{
    *out = {};
    if(fb != nullptr)
    {
        out->actual_yaw_rate_mrad_s = fb->actual_yaw_rate_mrad_s;
    }

    if(rt->zebra.stop_line)
    {
        clear_state();
        out->stop_request = 1;
        return;
    }
    if(!line_ok(rt))
    {
        clear_state();
        return;
    }

    out->input_valid = 1;

    const control_config_t &c = control_config();
    int ms = c.control_period_ms;
    if(fb != nullptr && fb->period_ms > 0)
    {
        ms = fb->period_ms;
    }
    const float dt = static_cast<float>(ms) / 1000.0F;

    int element = 0;
    if(rt->ring.kind != RING_KIND_NONE)
    {
        element = 1;
    }
    if(rt->cross.state != CROSS_STATE_NONE)
    {
        element = 1;
    }

    float center_rps = c.target_rps;
    if(element)
    {
        center_rps = c.element_target_rps;
    }

    // 1. 编码器反馈：count -> rps -> 低通
    int cnt_l = 0;
    int cnt_r = 0;
    if(fb != nullptr)
    {
        cnt_l = fb->left_speed_count;
        cnt_r = fb->right_speed_count;
    }

    const float raw_l = count_to_rps(cnt_l, ms);
    const float raw_r = count_to_rps(cnt_r, ms);
    if(!g_rps_ready)
    {
        g_left_rps = raw_l;
        g_right_rps = raw_r;
        g_rps_ready = 1;
    }
    else
    {
        g_left_rps = c.rps_filter_alpha * raw_l + (1.0F - c.rps_filter_alpha) * g_left_rps;
        g_right_rps = c.rps_filter_alpha * raw_r + (1.0F - c.rps_filter_alpha) * g_right_rps;
    }

    // 2. IMU yaw rate 反馈
    float raw_yaw = 0.0F;
    if(fb != nullptr)
    {
        raw_yaw = static_cast<float>(fb->actual_yaw_rate_mrad_s) / 1000.0F;
    }
    const float yaw_now = yaw_avg(raw_yaw, c.yaw_rate_filter_window);

    // 3. 视觉外环：guide_error -> target_yaw
    const float err = static_cast<float>(rt->track.guide_error);
    float derr = 0.0F;
    if(g_has_err && dt > 0.0F)
    {
        derr = (err - g_last_err) / dt;
    }
    g_last_err = err;
    g_has_err = 1;

    float target_yaw = c.outer_kp * err + c.outer_kd * derr;
    target_yaw *= c.outer_sign;
    if(std::fabs(err) < c.straight_error_threshold)
    {
        target_yaw *= c.straight_turn_scale;
    }
    target_yaw = clip_f(target_yaw, -c.max_target_yaw_rate, c.max_target_yaw_rate);

    // 4. yaw rate 内环修正：target_yaw -> yaw_cmd
    int yaw_fb_ok = 0;
    if(fb != nullptr && fb->actual_yaw_rate_valid)
    {
        yaw_fb_ok = 1;
    }

    float yaw_cmd = target_yaw;
    if(!yaw_fb_ok || !c.imu_yaw_feedback_enabled || c.max_yaw_rate_correction <= 0.0F)
    {
        g_yaw_i = 0.0F;
        g_last_target_yaw = target_yaw;
    }
    else
    {
        if(target_yaw == 0.0F || g_last_target_yaw * target_yaw < 0.0F)
        {
            g_yaw_i = 0.0F;
        }
        g_last_target_yaw = target_yaw;

        const float yaw_err = target_yaw - yaw_now;
        const float yaw_i1 = clip_f(g_yaw_i + yaw_err * dt, -k_yaw_i_max, k_yaw_i_max);
        const float yaw_u1 = c.yaw_kp * yaw_err + c.yaw_ki * yaw_i1;

        int hold_i = 0;
        if(yaw_u1 > c.max_yaw_rate_correction && yaw_err > 0.0F)
        {
            hold_i = 1;
        }
        if(yaw_u1 < -c.max_yaw_rate_correction && yaw_err < 0.0F)
        {
            hold_i = 1;
        }
        if(!hold_i)
        {
            g_yaw_i = yaw_i1;
        }

        float corr = c.yaw_kp * yaw_err + c.yaw_ki * g_yaw_i;
        corr = clip_f(corr, -c.max_yaw_rate_correction, c.max_yaw_rate_correction);
        yaw_cmd = clip_f(target_yaw + corr, -c.max_target_yaw_rate, c.max_target_yaw_rate);
    }

    // 5. 差速运动学：yaw_cmd -> left/right target rps
    const float circ = k_pi * c.encoder_gear_diameter_m;
    const float center_mps = center_rps * circ;
    const float diff_mps = yaw_cmd * c.wheel_track_m * 0.5F;
    float target_l = (center_mps - diff_mps) / circ;
    float target_r = (center_mps + diff_mps) / circ;
    target_l = clip_f(target_l, 0.0F, 45.0F);
    target_r = clip_f(target_r, 0.0F, 45.0F);

    // 6. 左轮 PI：target_l -> duty_l
    float ff_ref = c.speed_target_rps;
    if(ff_ref <= 1.0F)
    {
        ff_ref = 1.0F;
    }

    float duty_l = 0.0F;
    if(target_l <= 0.0F)
    {
        g_left_i = 0.0F;
    }
    else
    {
        const float kp = c.left_speed_kp;
        const float ki = c.left_speed_ki;
        const float ff = c.left_speed_base_percent * target_l / ff_ref;
        const float e = target_l - g_left_rps;
        const float i1 = clip_f(g_left_i + e * dt, -k_speed_i_max, k_speed_i_max);
        const float u1 = ff + kp * e + ki * i1;

        int hold_i = 0;
        if(u1 > static_cast<float>(c.max_duty_percent) && e > 0.0F)
        {
            hold_i = 1;
        }
        if(u1 < 0.0F && e < 0.0F)
        {
            hold_i = 1;
        }
        if(!hold_i)
        {
            g_left_i = i1;
        }
        duty_l = ff + kp * e + ki * g_left_i;
        duty_l = clip_f(duty_l, 0.0F, static_cast<float>(c.max_duty_percent));
    }

    // 7. 右轮 PI：target_r -> duty_r
    float duty_r = 0.0F;
    if(target_r <= 0.0F)
    {
        g_right_i = 0.0F;
    }
    else
    {
        const float kp = c.right_speed_kp;
        const float ki = c.right_speed_ki;
        const float ff = c.right_speed_base_percent * target_r / ff_ref;
        const float e = target_r - g_right_rps;
        const float i1 = clip_f(g_right_i + e * dt, -k_speed_i_max, k_speed_i_max);
        const float u1 = ff + kp * e + ki * i1;

        int hold_i = 0;
        if(u1 > static_cast<float>(c.max_duty_percent) && e > 0.0F)
        {
            hold_i = 1;
        }
        if(u1 < 0.0F && e < 0.0F)
        {
            hold_i = 1;
        }
        if(!hold_i)
        {
            g_right_i = i1;
        }
        duty_r = ff + kp * e + ki * g_right_i;
        duty_r = clip_f(duty_r, 0.0F, static_cast<float>(c.max_duty_percent));
    }

    out->target_yaw_rate_mrad_s = round_i32(target_yaw * 1000.0F);
    out->actual_yaw_rate_mrad_s = round_i32(yaw_now * 1000.0F);
    out->left_duty = clip_i(round_i32(duty_l), 0, c.max_duty_percent);
    out->right_duty = clip_i(round_i32(duty_r), 0, c.max_duty_percent);
}

} // namespace

void solve_runtime(const runtime_t *rt, control_state_t *ctrl)
{
    if(rt == nullptr || ctrl == nullptr)
    {
        return;
    }

    control_feedback_t fb = {};
    fb.period_ms = control_config().control_period_ms;
    solve(rt, &fb, ctrl);
}

void solve_runtime_with_feedback(const runtime_t *rt, const control_feedback_t *fb, control_state_t *ctrl)
{
    if(rt == nullptr || ctrl == nullptr)
    {
        return;
    }
    solve(rt, fb, ctrl);
}
```

Steps:

- [ ] Write test: run the Task 1 style gate and confirm it currently fails before editing.
- [ ] Verify RED: expected output contains `style gate failed`.
- [ ] Minimal code: replace `code/core/control.cpp` with the complete code block above.
- [ ] Verify GREEN: run the style gate again and expect `style gate passed: direct control flow`, then run `bash "code/test.sh" --host`.
- [ ] Commit: only after user confirms committing, run:

```bash
git add "code/core/control.cpp"
git commit -m "refactor(control): straighten mainline control flow"
```

## Task 3: Board-side smoke after compile

Files:

- Modify: none
- Runtime target: `/root/front_car_mainline`

Why:

`control.cpp` touches real duty output. Host compile is necessary but not sufficient. Board smoke confirms upload and startup still work before real driving.

Impact/Compatibility:

- No software behavior change beyond Task 2.
- Does not force motor enable by itself; use the existing user-controlled run command.

Verification:

```bash
REMOTE_IP=192.168.0.102 MAKE_JOBS=4 bash "code/test.sh" --upload
```

If upload succeeds, start with drive disabled for first smoke:

```bash
ssh root@192.168.0.102 'for p in $(ps | awk "/front_car_mainline/ && !/awk/ {print \$1}"); do kill $p 2>/dev/null; done; sleep 1; SMARTCAR_ASSISTANT=1 SMARTCAR_ASSISTANT_IP=192.168.0.101 SMARTCAR_ASSISTANT_PORT=8086 SMARTCAR_ASSISTANT_CONNECT_MS=30 SMARTCAR_ASSISTANT_RECONNECT_DIV=30 SMARTCAR_ASSISTANT_DIV=12 FRONT_CAR_DISPLAY=0 FRONT_CAR_PROCESS_FPS=120 FRONT_CAR_PRINT_DIV=15 FRONT_CAR_ENABLE_DRIVE=0 /root/front_car_mainline >/tmp/front_car_mainline.log 2>&1 & echo started'
```

Read logs:

```bash
ssh root@192.168.0.102 'head -n 14 /tmp/front_car_mainline.log; tail -n 20 /tmp/front_car_mainline.log'
```

Expected signals:

```text
front_car_mainline: assistant 192.168.0.101:8086 connected
line=...
track=...
guide_error=...
```

Steps:

- [ ] Write test: prepare the exact upload/start/log commands above.
- [ ] Verify RED: if SSH hangs or upload fails, stop and report the exact failed command.
- [ ] Minimal code: no source change in this task; this is runtime smoke for Task 2.
- [ ] Verify GREEN: log shows startup, assistant connection or explicit connect failure, and frame fields without crash.
- [ ] Commit: no additional commit for this task.

# Risks

- Behavior-preserving intent can still change behavior if the staged rewrite accidentally changes update order.
- The static style gate is intentionally narrow; it catches current bad shapes, not every possible future abstraction.
- Host compile cannot prove real motor response.
- If `/root/front_car_mainline.yaml` differs from local config, board behavior may differ even when code is correct.

# Retirement

Retired by this plan:

- `struct loop_t`
- `outer_pd()`
- `inner_pi()`
- `wheel_pi()`
- compressed ternary control expressions

Not retired in this plan:

- yaw feedback loop
- wheel PI
- yaml control parameters

Deletion of yaw feedback or wheel PI requires a separate behavior-change plan with real log evidence.

# Self-Review

- Spec coverage: plan targets the named file `code/core/control.cpp` and the stated complexity/style problem.
- Placeholder scan: no placeholder tasks or vague file names.
- Type consistency: public signatures and structs are unchanged.
- Compatibility: yaml schema, driver mapping, runtime chain, assistant display, and tracking are unchanged.
- Minimality: single owner file edit, no wrapper, no adapter, no new fallback.
- Verification: style gate, host build, and board smoke commands are exact.
- Dual-track: repair retires old helper owner shape; behavior-changing retirement is explicitly deferred behind evidence.

