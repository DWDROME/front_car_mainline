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
| Round, Y-road, ramp, garage | Source is kept and still built where needed, but the current competition profile keeps these states idle from the port step. |
| Road classification | Still computed after a valid selected line for report/debug evidence. |

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

The active port step follows the relevant `Cpu0_Main.c` order, narrowed to the
current competition profile:

1. `image_handle()`
2. `find_corners()`
3. near-line `track_type` switching
4. `check_Half()` for cross/half-cross entry
5. `check_circle()` for circle entry
6. `run_cross()` / `run_circle()`
7. keep `round/ramp/yroad/garage` states idle
8. circle splicing from `Patching_Line.c`
9. selected-line normalization into `rptsn`
10. `check_road()` after ATG preview variables are computed

`code/tracking/atg_reference_mainline.cpp` is now a thin bridge: it calls the
ATG step, copies only the selected `rptsn` midline and `guide_error` into
`rt->vision`, and leaves element evidence in ATG's native globals for
report/assistant to read directly. It does not import ATG servo PID or motor
output; current control remains `guide_error -> yaw_cmd -> differential motor
duty`.

TC264 garage action, motor/servo PID, UART broadcast, TFT display, flash, key,
and sensor drivers are still outside the build. Round, ramp, Y-road, and garage
logic stays in the copied ATG source for later reuse, but `reference_step.c`
does not activate those states in the current competition profile.

## Change Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `Project/USER/Cpu0_Main.c` runs `image_handle()`, `find_corners()`, element checks, element runners, then selected-line normalization. | Previous ATG branch only ran base line-search and copied `rptsc0/rptsc1`; copied element files were not compiled or called. | `atg_reference/port/reference_step.c` now calls the ATG cross/half/circle sequence and selected-line logic. | The algorithm mainline must follow ATG's state-machine owner instead of the old local runtime. | Missing geometry still returns no `rptsn`; no old-frame midline is reused. |
| ATG `cross.c` owns `CROSS_IN/CROSS_HALF` far-line control. | The bridge no longer mirrors cross state into a local `runtime_t.cross` structure. | `report.cpp`/`assistant.cpp` read `cross_type`, `far_rpts*`, and `far_Lpt*` directly from ATG globals. | Upper monitor and logs should show ATG's real state, not a translated old-mainline field. | The data is current-frame ATG evidence only; control still consumes the published current `rptsn`. |
| ATG `circle.c` plus `Patching_Line.c` builds spliced center lines for circle in/out phases. | Circle state is no longer translated to local ring diagnostics. | `reference_step.c` builds spliced lines for ATG circle IN/OUT states; report/assistant read `circle_type` and `Splicing_*` evidence directly. | Circle selected-line behavior is part of the purchased ATG improvement path. | No synthetic fallback line is created; splicing only runs when ATG state and far-line evidence make that branch active. |
| ATG `Cpu0_Main.c` also has round, ramp, Y-road, and garage-related branches. | The current race does not need those elements, and some triggers depend on sensors or scene contracts not validated on this car. | Keep the copied source, but gate the active port step with `ATG_ENABLE_*`: only cross/half-cross and circle are enabled; round/ramp/Y-road/garage are held at `NONE`. | This keeps ATG code available without letting unused elements steal the state machine. | Disabled states are explicitly reset each frame in `reference_step.c`; no old-frame line or fake element state is introduced. |
| ATG ISR accumulates `total_distence` only while `Count_dis_Flag` is set. | LS2K has no TC264 ISR/motor module. | Port layer updates `total_distence` from frame-to-frame `encoder_total` delta. | Circle state transitions depend on this ATG distance contract. | The counter resets exactly when ATG state clears `Count_dis_Flag`; it does not mask missing vision evidence. |
| ATG `Cpu0_Main.c` feeds the frame result straight into its own control path (`pure_angle -> servo`); there is no runtime adapter between algorithm and control. | The LS2K control entry used to be `solve_runtime*(runtime_t)`, so the control layer consumed the whole `runtime_t.track` snapshot instead of the current ATG frame result. | Public control entries are now `solve_control_input(_with_feedback)(control_input_t)`; `runners.cpp` builds `control_input_t` (`line_found` from the `tracking_process_frame()` return, plus `guide_error`/`element_active`/`stop_line`) right after the ATG step, and `runtime_t` only keeps `gray/encoder_total/control_center_x/vision/control`. | The ATG algorithm is unchanged, so the control chain can produce its final input in one step; keeping a public runtime adapter layer would only preserve old-mainline semantics. | `line_found` comes from the current-frame ATG step result; on no-line or stop-line the control layer clears state and outputs stop instead of holding any previous midline or duty. |
| ATG2022's migrated mainline has no zebra stop-line detector; its race-end handling is the TC264 garage path, which is gated off. | The old local mainline had a zebra scan that set `stop_line` and drove `stop_request`. | `control_input_t.stop_line` is constantly 0 with an explicit comment in `runners.cpp`; the old zebra scan was removed with the old tracking tree. | Faking a stop-line from non-ATG evidence would reintroduce old-mainline semantics; stopping must come from a real detector when one is ported. | This is a documented capability gap, not a silent fallback: the car has no automatic stop until an ATG-native or new stop detector is added. |
| ATG circle exits via vision (`rpts1s_num>30...`) or the forced `total_distence>4500` gate, both of which assume the servo car keeps rolling when the selected line is empty. | This differential car stops on `line_found=0`, so a falsely-entered circle state can never satisfy either exit: the image freezes and the encoder stops counting — a deadlock observed live as `circle=7 (CIRCLE_LEFT_OUT)` with the car frozen mid-curve. | `reference_step.c` adds a port-layer stall exit: after 30 consecutive frames of "circle active but no selected line", reset the circle state (same restore set as `CIRCLE_*_END`) with an explicit `ATGCircleStall` log. Also `build_circle_spliced_lines()` now clears `Splicing_*_center_num` each frame. | The stall exit is the differential-car translation of ATG's own forced-distance exit; the splice clear enforces the no-previous-frame-midline rule (the reference car tolerates stale splices only because it keeps moving). | No line is fabricated and no old frame is reused: the car stays stopped until real current-frame evidence produces a line; the reset only releases a state whose physical preconditions are gone, and it logs loudly instead of failing silently. |
| `Half_check.c` enters `CIRCLE_*_BEGIN` from a bare "near L (<5) + no far L" shortcut; the author's comment says on his track such a corner could only be a circle. `check_circle()`'s own entry additionally requires the opposite-side long-straight flag (`is_straight1/0`). | On this track, approaching a cross with the body not yet straightened loses the entire opposite boundary; the shortcut then classified a cross as `CIRCLE_LEFT_BEGIN` (live log frame=1920: `l=1@4/0@-1`, right seed lost, car stopped). | Add the same opposite-side evidence (`is_straight1` for the left shortcut, `is_straight0` for the right) to the two `Half_check.c` circle shortcuts, aligning them with `check_circle()`'s front-door condition. `check_cross()` stays disabled exactly as the reference author left it. | The shortcut encoded a track-specific prior, not geometry; a real circle entry always has an opposite long straight, so the unified evidence requirement separates the two scenes. | Evidence is tightened, not loosened: no state or line is fabricated, the no-evidence frame stays ordinary single-side tracking, and a real circle still triggers via either entry because its opposite straight makes the flag true. |
