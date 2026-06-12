# ATG2022 Porting Boundary

Goal: make ATG2022 the new algorithm mainline while keeping the current LS2K
peripheral, control, and upper-monitor layers.

## Layer Contract

| Layer | Directory | Rule |
| --- | --- | --- |
| ATG algorithm core | `atg_reference/Project/CODE/` | Keep close to copied source. Do not hide port logic here. |
| ATG loop evidence | `atg_reference/Project/USER/` | Read-only reference for ordering, selected-line choice, and element sequence. |
| Port layer | `atg_reference/port/` | Provide TC264 type aliases, globals, encoder hooks, image input, and LS2K bridge functions. |
| Current bridge | `code/tracking/` | Expose the existing `tracking_process_frame()` contract to app/core/report. |
| LS2K app/core/drivers | `code/app/`, `code/core/`, `code/drivers/` | Keep current UVC capture, differential control, encoder accumulation, and upper-monitor output. |

## What Migrates

| Area | Decision |
| --- | --- |
| Line search and resampling | Migrate to ATG `shy_Image.c` path. |
| Corner detection | Migrate to ATG thresholds and direction checks. |
| Cross and half-cross | Migrate to ATG `cross.c` + `Half_check.c`. |
| Circle and patching | Migrate to ATG `circle.c` + `Patching_Line.c`, preserving ATG enum order inside the ATG layer. |
| Y-road, ramp, road classification | Compile and call ATG source from the port step; sensor-dependent trigger quality still needs real-car validation. |

## What Does Not Migrate

| Area | Reason |
| --- | --- |
| TC264 motor, servo, ADRC, PID, key, TFT, flash, UART, and sensor drivers | Hardware and control loop differ from LS2K. |
| TC264 direct actuator output | Current car uses LS2K differential `guide_error -> yaw_cmd -> motor duty`. |
| A second production IPM truth source | Current production IPM is ATG `shy_Image.c::rot/inv_rot`; do not reintroduce the old `camera_param.c` table path as a parallel runtime source. |

## Current Migration Order

1. Preserve the pushed RT1064/autop branch history as the old baseline.
2. Build this branch as `port/atg2022-reference-control`.
3. Copy ATG source into `atg_reference/`.
4. Create a minimal ATG port layer that compiles host-side without TC264 drivers.
5. Keep only the ATG tracking bridge in `code/tracking`; the old `autop_reference/` tree and bridge are removed from this branch.
6. Validate with `git diff --check`, `bash code/test.sh --host`, and targeted offline/analyze frames.

## Current Stage

The branch currently builds the copied ATG `Project/CODE` tracking and element
mainline:

| Active in build | Status |
| --- | --- |
| `atg_reference/Project/CODE/shy_Image.c` | active |
| `atg_reference/Project/CODE/imgproc.c` | active |
| `atg_reference/Project/CODE/utils.c` | active |
| `atg_reference/Project/CODE/cross.c` | active |
| `atg_reference/Project/CODE/Half_check.c` | active |
| `atg_reference/Project/CODE/circle.c` | active |
| `atg_reference/Project/CODE/Patching_Line.c` | active |
| `atg_reference/Project/CODE/round.c` | active |
| `atg_reference/Project/CODE/yroad.c` | active |
| `atg_reference/Project/CODE/Ramp.c` | active |
| `atg_reference/Project/CODE/road.c` | active |
| `atg_reference/port/reference_step.c` | active |
| `code/tracking/atg_reference_mainline.cpp` | active bridge |

The active port step follows the relevant `Cpu0_Main.c` order for:

1. `image_handle()`
2. `find_corners()`
3. near-line `track_type` switching
4. `check_round()`
5. `check_Half()`
6. `Check_ramp()`
7. `check_circle()`
8. `check_yroad()`
9. `run_round()` / `Run_Ramp()` / `run_cross()` / `run_circle()` / `run_yroad()`
10. circle splicing from `Patching_Line.c`
11. selected-line normalization into `rptsn`
12. `check_road()` after ATG preview variables are computed

`code/tracking/atg_reference_mainline.cpp` maps ATG `cross_type`,
`circle_type`, `round_type`, far-line points, and spliced-line diagnostics into
the existing LS2K `runtime_t` report/control contract. It does not import ATG
servo PID or motor output; current control remains
`guide_error -> yaw_cmd -> differential motor duty`.

TC264 garage action, motor/servo PID, UART broadcast, TFT display, flash, key,
and sensor drivers are still outside the build. The ATG ramp state machine is
compiled and called, but its distance-sensor inputs currently come from the
port-layer globals and default to zero unless an LS2K sensor adapter is added.

## Change Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `Project/USER/Cpu0_Main.c` runs `image_handle()`, `find_corners()`, element checks, element runners, then selected-line normalization. | Previous ATG branch only ran base line-search and copied `rptsc0/rptsc1`; copied element files were not compiled or called. | `atg_reference/port/reference_step.c` now calls the ATG cross/half/circle sequence and selected-line logic. | The algorithm mainline must follow ATG's state-machine owner instead of the old local runtime. | Missing geometry still returns no `rptsn`; no old-frame midline is reused. |
| ATG `cross.c` owns `CROSS_IN/CROSS_HALF` far-line control. | The bridge previously cleared cross state as unported. | `code/tracking/atg_reference_mainline.cpp` maps `cross_type` and `far_rpts*` to `runtime_t.cross`. | Upper monitor needs to see the active ATG state now that it participates in selection. | Mapping is diagnostic/current-frame data only; control still consumes the published current `rptsn`. |
| ATG `circle.c` plus `Patching_Line.c` builds spliced center lines for circle in/out phases. | Circle state was previously hidden from runtime and spliced lines were not selected. | `reference_step.c` builds spliced lines for ATG circle IN/OUT states; bridge maps `circle_type` to ring diagnostics. | Circle selected-line behavior is part of the purchased ATG improvement path. | No synthetic fallback line is created; splicing only runs when ATG state and far-line evidence make that branch active. |
| ATG `Cpu0_Main.c` checks round, ramp, y-road, and road classification in addition to cross/circle. | These copied files were present but not built or called. | `code/CMakeLists.txt` compiles `round.c`, `yroad.c`, `Ramp.c`, and `road.c`; `reference_step.c` calls them in the ATG order. | The branch goal is full ATG algorithm-mainline migration, not only base line search. | TC264 actuator/sensor side effects remain outside the build; missing current geometry still fails instead of holding output. |
| ATG ISR accumulates `total_distence` only while `Count_dis_Flag` is set. | LS2K has no TC264 ISR/motor module. | Port layer updates `total_distence` from frame-to-frame `encoder_total` delta. | Circle state transitions depend on this ATG distance contract. | The counter resets exactly when ATG state clears `Count_dis_Flag`; it does not mask missing vision evidence. |
| ATG `Cpu0_Main.c` feeds the frame result straight into its own control path (`pure_angle -> servo`); there is no runtime adapter between algorithm and control. | The LS2K control entry used to be `solve_runtime*(runtime_t)`, so the control layer consumed the whole `runtime_t.track` snapshot instead of the current ATG frame result. | Public control entries are now `solve_control_input(_with_feedback)(control_input_t)`; `runners.cpp` builds `control_input_t` (`line_found` from the `tracking_process_frame()` return, plus `guide_error`/`element_active`/`stop_line`) right after the ATG step, and `runtime_t` stays only as a report/assistant snapshot. | The ATG algorithm is unchanged, so the control chain can produce its final input in one step; keeping a public runtime adapter layer would only preserve old-mainline semantics. | `line_found` comes from the current-frame ATG step result; on no-line or stop-line the control layer clears state and outputs stop instead of holding any previous midline or duty. |
