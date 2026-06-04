# diagnose cross ring pause and lower L loss stop

## Goal

Diagnose why the car pauses when entering or passing cross intersections and roundabouts, and why losing one lower L / one-side boundary appears to stop the car. The first deliverable is a code-evidence-backed explanation and a minimal fix direction, not an immediate broad rewrite.

## What I already know

* User report: teammates observed a pause around cross and ring elements.
* User report: if one lower L is lost, the car seems to stop.
* User report from video: normal straight and continuous bends are smooth, but the car stops after entering a cross; no farline appears, and near L corners are also absent in the stopped frame.
* User report from video: when a visible line enters from the left image border rather than the bottom edge, the left boundary is visually clear but is not acquired by the current pipeline.
* User report from video: roundabout currently has no successful pass; the first corner disappearing is followed by a stop, and manually placing the car mid-roundabout can produce a reasonable midline only in some phases.
* User report from teammate: "double L" cross detection is too strict under yaw/offset, but their last change that allowed single-side L to trigger/enter cross caused broader failures.
* Team local tuning note: changing `code/tuning.hpp` `CONTROL_CENTER_X` from `60` to `85`, then to `80`, improved behavior; current source still has `CONTROL_CENTER_X = 60`.
* The active project for this image/vision/line-tracking issue is `front_car_mainline`.
* The reference implementation path is `/mnt/e/longxin/RT1064_Code_ref`.
* The concrete RT1064 reference checkout is `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code`.
* `fast_context_search` located RT1064 reference files earlier, but fast-context is currently unavailable. Current evidence gathering uses bounded local commands only: `rg --files`, `rg -n`, `nl -ba ... | sed -n`.
* Current control layer stops only on `zebra.stop_line`, `ctrl == nullptr`, `stop_request`, or `input_valid == 0`.
* `control.cpp` marks input invalid when `track.track_type == TRACK_TYPE_NONE` or `track.reject_reason != TRACK_REJECT_NONE`.
* `drive_output.cpp` calls `drive_output_stop()` when `ctrl->stop_request` or `!ctrl->input_valid`.
* `element_target_rps` is lower than normal `target_rps` by default (`3.0` vs `4.0` rps), so element detection itself intentionally slows the car but should not hard-stop it.
* In `CROSS_IN`, `tracking_process_frame()` requires a valid `cross.track_type`, `solve_cross_mid()` result, and lookahead-capable midline. Failure becomes `TRACK_REJECT_NO_MIDLINE`, which disables control output.
* Ring state forces a side choice by ring state. If the selected side has too few points or cannot produce lookahead, `TRACK_REJECT_NO_MIDLINE` also disables control output.
* Ordinary line selection already supports single-side tracking through `pick_track_type()`, so the likely stop is not simply "only one side exists", but "the selected/required side after element logic cannot build a valid midline".
* RT1064 reference `track_type` has only `TRACK_LEFT` and `TRACK_RIGHT`; it never has a `TRACK_NONE` invalid-output state.
* RT1064 `run_cross()` only updates `track_type` when far L is found, or after near-line loss. If far L is temporarily missing before near-line loss, previous `track_type` remains in force instead of stopping.
* Current `cross_evolve()` clears `rt->cross.track_type` to `TRACK_TYPE_NONE` every frame before rebuilding far lines, so a transient far-L miss can become a hard invalid-control frame.
* RT1064 `run_circle()` also forces `track_type` by circle state, and the main loop consumes the chosen side directly. The current ring port matches the state-based side choice, but adds explicit `NO_MIDLINE` rejection when the selected side cannot build a lookahead midline.
* Current ordinary `find_seeds()` only searches one fixed bottom row (`START_HIGH = 116`) from `mid_position ± ROAD_HALF_WIDTH`; it does not search for a boundary whose first visible point enters from the left/right image edge.
* RT1064 ordinary `process_image()` also starts from fixed `begin_y` and scans horizontally on that row, so border-entry recovery is not a direct copied feature from the reference. RT1064 cross farline, however, separately scans upward on fixed far columns before tracing.

## Assumptions

* The observed "pause" is either intentional lower `element_target_rps` or one/few frames of `input_valid=0`, not a separate motor-driver delay.
* The observed "lower L loss stop" is likely caused by an element-state midline rejection path, not by `l_ok` alone.
* The next comparison should anchor on RT1064 cross/circle semantics before deciding whether current gates are too strict.
* The highest-probability cross fix is to preserve the last valid cross side or provide a near-line fallback before returning `TRACK_REJECT_NO_MIDLINE`.
* The ring pause needs runtime confirmation: it may be intentional `element_target_rps`, or selected-side midline rejection when the forced inner/outer side is too short.
* Because this is safety-critical vehicle code, no field-level behavior change should happen until its writer/reader/control-output impact is explicitly listed.

## Open Questions

* Need distinguish using existing report/replay/video evidence only, without adding a new logging system: are pause frames `input_valid=0` / `reject_reason=4`, or merely reduced `center_rps` from element speed?

## Requirements

* Map the exact code path from visual element state to control output stop.
* Compare current cross/ring failure gates against the RT1064 reference implementation.
* Identify the smallest safe code change if the current gates are stricter than the reference or unsafe for one-side loss.
* Preserve single-side tracking behavior outside elements.
* Before editing any field, document:
  * every writer of the field
  * every reader that changes control behavior
  * whether the field is per-frame or cross-frame state
  * how invalid values propagate to `input_valid`, `stop_request`, duty output, report, and telemetry

## Safety Constraints

* Do not directly change `rt->track.track_type`, `rt->track.reject_reason`, `rt->cross.state`, `rt->ring.kind`, or `rt->ring.state` semantics as a first fix.
* Do not weaken `drive_output_apply()` stop behavior for `!input_valid`; that is the final safety gate.
* Do not make `TRACK_REJECT_NO_MIDLINE` globally non-fatal; normal no-line frames must still stop.
* Do not add a generic fallback from cross/ring back to ordinary `pick_track_type()` without proving it cannot steer on the wrong side inside an element.
* Do not introduce a new logging system, new test framework, or debug-oriented runtime layer into the vehicle path.
* Do not add observability-only source patches unless explicitly requested later.
* If behavior changes are needed, prefer the smallest local change in the element-side decision contract, not the control or motor-driver layer.
* Prefer mechanism-level reasoning against the RT1064 reference code over instrumentation-first changes.
* Every future source-line change is critical. Before changing any source line, record the exact file/line, current behavior, proposed behavior, RT1064 alignment basis, downstream control impact, and rollback path.
* Do not batch unrelated source edits. A source patch must be a single coherent mechanism change, not a mixture of cross, ring, seed, and control tuning.

## Field Impact Notes

* `rt->cross.track_type`
  * Writers: `cross_evolve()` clears it to `TRACK_TYPE_NONE` and rewrites it from far L or near-line-lost side.
  * Readers: `solve_cross_mid()` and `tracking_process_frame()` consume it in `CROSS_IN`; `report`/`replay` expose only the final `rt->track.track_type`.
  * State shape: stored in `cross_state_t`, so it can be cross-frame state, but current writer clears it every `cross_evolve()` frame.
  * Risk: preserving the previous value may smooth transient far-L misses, but can also keep following a stale side if the car has genuinely moved to a different cross phase.
* `rt->track.track_type`
  * Writers: `tracking_process_frame()` clears it every frame and writes it only after a valid midline is built.
  * Readers: `track_line_found()`, `control.cpp::line_ok()`, report/live output.
  * Risk: changing this field directly can make control trust a frame with no valid midline.
* `rt->track.reject_reason`
  * Writers: seed/trace/midline failure branches in `tracking_process_frame()`.
  * Readers: `track_line_found()`, `control.cpp::line_ok()`, report/live output.
  * Risk: suppressing reject globally would bypass the intended no-line safety stop.
* `rt->ring.kind/state`
  * Writers: `ring_process()` and `element.cpp` reset ring when cross is active.
  * Readers: `mainline.cpp` selects forced side by ring state; `control.cpp` switches to `element_target_rps`.
  * Risk: changing ring state semantics affects both side choice and speed target.
* `rt->cross.state`
  * Writers: `cross_process()` / `cross_begin()` / `cross_leave()`.
  * Readers: `element.cpp`, `tracking_process_frame()`, `control.cpp`, assistant/report.
  * Risk: changing this field affects element mutual exclusion, cross farline routing, and element speed.

## Mechanism Alignment With RT1064 Reference

### Core Difference: Continuous Side State vs Invalid Side State

RT1064 reference uses a persistent global `track_type` with only two legal values:

```text
TRACK_LEFT / TRACK_RIGHT
```

There is no `TRACK_NONE` state in the reference side-selection contract. The main loop first updates `track_type` from ordinary line imbalance, then element state machines may overwrite it. Centerline generation consumes whichever side is currently selected.

Current `front_car_mainline` splits this into two fields:

```text
cross.track_type  // element-local side decision, can be TRACK_TYPE_NONE
track.track_type  // final control side, cleared every frame and written only after midline succeeds
```

That split is safer in ordinary no-line frames, but it creates a new discontinuity inside `CROSS_IN`: if `cross_evolve()` cannot select a side in the current frame, `tracking_process_frame()` rejects the frame, then `control.cpp` clears state and the motor output stops.

This is not present as the same discrete state in RT1064.

### Cross Mechanism

RT1064 `run_cross()` in `CROSS_IN`:

```text
cross_farline()
if both near lines lost: not_have_line++
if far right L found: track_type = TRACK_RIGHT
else if far left L found: track_type = TRACK_LEFT
else if not_have_line > 0 and right near short: track_type = TRACK_RIGHT
else if not_have_line > 0 and left near short: track_type = TRACK_LEFT
else: keep previous track_type
```

Current `cross_evolve()`:

```text
cross.track_type = TRACK_TYPE_NONE
clear farline/L fields
build farline
if far right L valid: cross.track_type = TRACK_TYPE_RIGHT
else if far left L valid: cross.track_type = TRACK_TYPE_LEFT
else if not_have_line > 0 and near side short: choose side
else: remain TRACK_TYPE_NONE
```

Then `tracking_process_frame()` treats `TRACK_TYPE_NONE` as `TRACK_REJECT_NO_MIDLINE`, and `control.cpp` treats that as invalid input.

Mechanically, the pause can be explained as:

```text
CROSS_IN frame
-> far L not detected this frame
-> not_have_line has not yet become useful, or near-side short rule does not select
-> cross.track_type remains NONE
-> reject_reason = NO_MIDLINE
-> input_valid = 0
-> drive_output_stop()
```

The key semantic mismatch is not “missing L should be ignored”; it is that RT1064 keeps the previous side through an uncertain frame, while the current port converts uncertainty into an explicit invalid side.

### Ring Mechanism

RT1064 circle logic forces `track_type` directly by state:

```text
left ring:  BEGIN/RUN/END use right side, IN/OUT use left side
right ring: BEGIN/RUN/END use left side,  IN/OUT use right side
```

Current ring side selection matches this state table in `mainline.cpp`. The extra discontinuity is again after the side is selected: current code requires the selected side to build a valid midline and lookahead, otherwise `TRACK_REJECT_NO_MIDLINE` stops control.

So ring has two possible mechanisms:

* If the car only feels slower while `line` stays valid, it is probably intentional `element_target_rps`.
* If it truly hard-stops, the likely cause is selected-side midline failure after ring has forced inner/outer side.

Because ring forced-side fallback can make the car follow the wrong arc, it is more dangerous than cross side persistence. Ring should not be changed before the cross semantic mismatch is settled.

## Modification Candidate Table

### C0: Do not change control-layer safety gate

* Type: forbidden behavior change.
* Examples:
  * Make `TRACK_REJECT_NO_MIDLINE` non-fatal globally.
  * Let `drive_output_apply()` keep last duty when `!input_valid`.
  * Force `rt->track.track_type` nonzero without a valid midline.
* Risk:
  * Can drive the car on frames with no trustworthy line.
* Recommendation: reject.

### C1: Preserve only `cross.track_type`

* Type: small cross-local behavior change.
* Idea:
  * Stop clearing `rt->cross.track_type` to `TRACK_TYPE_NONE` at the top of every `cross_evolve()` frame.
  * Only overwrite it when fresh far-L or near-line-loss evidence selects a side.
* Benefit:
  * Moves closer to RT1064's persistent `track_type` behavior.
* Limitation:
  * Not sufficient by itself if `left_l/right_l` is still reset to `-1`; `solve_cross_mid()` will still reject when the selected side has no fresh far L.
* Risk:
  * Can preserve a stale side after the actual cross geometry changes.
* Recommendation:
  * Mechanically closer to RT1064, but not sufficient if far L indices are still required fresh every frame.
  * Do not apply as a blind one-line fix.

### C2: Bounded cross far-L latch

* Type: cross-local behavior change with explicit risk bounds.
* Idea:
  * If a valid far-L side was found recently, allow one or two transient frames to reuse the last valid side and L index when the current farline is still built and the saved index is still in range.
  * Continue to require `solve_cross_mid()` and `midline_has_lookahead()` to pass before writing `rt->track.track_type`.
  * Reset the latch on `cross_leave()` and when entering a new cross.
* Benefit:
  * Targets the likely RT1064 semantic difference without weakening the final control safety gate.
  * Handles one-frame far-L dropout instead of turning it into `input_valid=0`.
* Risk:
  * Reusing a stale L index can steer from a slightly wrong farline segment.
  * Adding latch counters/fields changes `cross_state_t`; that field impact must be reviewed before implementation.
* Recommendation:
  * Best mechanism-aligned candidate if we decide to edit code.
  * It should be framed as preserving RT1064's "uncertain frame keeps previous side" behavior, with explicit reset on cross exit, not as a generic fallback.

### C3: CROSS_IN near-line fallback

* Type: behavior change in `tracking_process_frame()`.
* Idea:
  * If `solve_cross_mid()` fails, fall back to the current frame's near-line output.
* Benefit:
  * Can reduce hard-stop frames when farline is bad.
* Risk:
  * High: inside a cross, near lines may be intentionally truncated or geometrically misleading.
  * Violates the current contract that `CROSS_IN` does not silently return to ordinary `pick_track_type()`.
* Recommendation:
  * Not recommended unless replay proves farline is unusable but near-line is consistently safe.

### R0: Ring diagnosis before ring behavior changes

* Type: mechanism-first analysis.
* Current evidence:
  * Ring state table is already aligned with RT1064.
  * Current code adds a stricter midline/lookahead validity gate after forced side selection.
* Interpretation:
  * Ring is less likely to be fixed by changing the state table.
  * Ring hard-stop, if real, is likely selected-side midline failure; ring “pause” may simply be `element_target_rps`.
* Recommendation:
  * Do not change ring until cross is understood; do not add opposite-side fallback now.

### R1: Ring forced-side fallback

* Type: ring/mainline behavior change.
* Idea:
  * If the side forced by ring state cannot build a midline, try the opposite side.
* Risk:
  * High: ring state deliberately switches between inner and outer side. Opposite-side fallback can make the car cut the wrong arc.
* Recommendation:
  * Reject for now. Only revisit with frame-by-frame replay evidence.

## Recommended Sequence

1. Treat RT1064 `track_type` persistence as the reference semantic to compare against.
2. For cross, focus on the new invalid-side discontinuity introduced by `TRACK_TYPE_NONE`.
3. Decide whether to emulate the reference by keeping a bounded previous-side/far-L decision inside `CROSS_IN`.
4. For ring, keep the state table unchanged and do not introduce opposite-side fallback.
5. Do not touch C0, C3, or R1 without a separate, explicit decision.

## Method Notes

* `fast_context_search` successfully located current and RT1064 reference files earlier in the task.
* Later fast-context retries failed with network errors, so the current mechanism notes are based on already-located files plus direct file reads.
* User explicitly rejected adding logging systems, tests, or debug-oriented patches for this critical vehicle code. The task now prioritizes mechanism-level reasoning and RT1064 semantic alignment.

## Acceptance Criteria

* [ ] Evidence identifies whether the issue is speed reduction, invalid tracking output, zebra stop, or motor-driver behavior.
* [ ] Cross behavior is compared with the RT1064 reference.
* [ ] Ring behavior is compared with the RT1064 reference.
* [ ] A minimal fix direction is proposed before source edits.
* [ ] If code is changed later, `bash "project/user/test.sh"` passes or any failure is explained.

## Definition of Done

* Root cause or strongest supported hypothesis is documented.
* Any code change is minimal and local to the visual/control choke point.
* Validation uses the project build script and, if possible, replay/report fields.

## Out of Scope

* PID retuning, unless evidence shows the pause is only `element_target_rps`.
* Rewriting the cross/ring state machines from scratch.
* Moving this work to `front_car_control_calib`.
* Introducing a new logging system, test framework, or observability-only source patch.

## Technical Notes

* `code/core/control.cpp`: `line_ok()` rejects `TRACK_TYPE_NONE` and nonzero `reject_reason`; element states select `element_target_rps`.
* `code/drivers/drive_output.cpp`: `drive_output_apply()` stops motor when control input is invalid.
* `code/tracking/mainline.cpp`: cross/ring midline rejection paths write `TRACK_REJECT_NO_MIDLINE`.
* `code/tracking/cross.cpp`: `CROSS_IN` chooses far-line-based side and exits only after near-line lost/recovered.
* `code/tracking/ring.cpp`: ring state machine forces inner/outer side selection by state.
* `code/types.hpp`: reject reason `TRACK_REJECT_NO_MIDLINE = 4`.
* RT1064 `Project/CODE/cross.c`: `run_cross()` sets `track_type` from far L when present; otherwise falls back to near-line-lost side after `not_have_line > 0`.
* RT1064 `Project/CODE/circle.c`: each circle state writes `track_type` directly.
* RT1064 `Project/USER/src/main.c`: main loop consumes `track_type` directly for centerline generation; no explicit `track_type none -> stop` gate exists there.
* `docs/流程图.md` appears stale for element scheduling order: current `element.cpp` gives cross priority, while that doc says idle state tries ring before cross. Current code must be treated as source of truth.

## Direct Evidence Index

### Current `front_car_mainline`

* `code/tuning.hpp:20-33`: `MID_X = RAW_W / 2`, `CONTROL_CENTER_X = 60`, `START_HIGH = 116`.
* `code/tracking/imgproc.cpp:214-290`: `find_seeds()` searches one fixed row from `center ± kSeedStartOffset`; it can return a single-side seed, but only if that row contains the edge.
* `code/tracking/imgproc.cpp:312-341`: `find_column_seed()` can scan upward on one column, but current ordinary seed search does not use it; ring opposite-side fill and cross farline do.
* `code/tracking/boundary.cpp:430-510`: L corners are cleared every refresh, found only in the front segment, and when both sides are found they must pass `corner_pair_ok()` or both `l_ok` flags are cleared.
* `code/tracking/cross.cpp:279-339`: `CROSS_BEGIN` truncates near lines and requires `both_l && near_ok` to enter `CROSS_IN`; `near_ok` itself is single-side, but `both_l` is still required.
* `code/tracking/cross.cpp:346-440`: `CROSS_IN` clears `cross.track_type`, farline flags, far L indices, and farline point arrays every frame before rebuilding them.
* `code/tracking/cross.cpp:405-424`: side choice in `CROSS_IN` is right far L, then left far L, then near-line-lost side. If none matches, side remains `TRACK_TYPE_NONE`.
* `code/tracking/mainline.cpp:526-551`: an already-active `CROSS_IN` frame rejects immediately when `cross.track_type == TRACK_TYPE_NONE`, `solve_cross_mid()` is too short, or the midline lacks lookahead.
* `code/tracking/mainline.cpp:559-635`: ring forces side by state, then still requires `track_leftline/track_rightline` and `midline_has_lookahead()`.
* `code/core/control.cpp:95-150`: `line_ok()` rejects `TRACK_TYPE_NONE` and any nonzero reject reason; invalid line clears controller state.
* `code/drivers/drive_output.cpp:134-144`: invalid control input calls `drive_output_stop()`.
* `code/tracking/ring.cpp:259-304`: ring entry is single-side L plus opposite straight, aligned with RT1064 `check_circle()`.
* `code/tracking/ring.cpp:324-420`: ring state transitions depend on selected-side point length, L corner, straightness, lost/have counters, and encoder distance.

### RT1064 Reference

* `Project/CODE/flash_param.c:22-23`: reference defaults `begin_x = 32`, `begin_y = 167` on a 376x240 image.
* `Project/USER/src/main.c:308-317`: ordinary side selection supports single-side loss by choosing the longer side.
* `Project/USER/src/main.c:326-347`: element priority is cross, yroad, circle; then `run_cross()` and `run_circle()` may overwrite `track_type`.
* `Project/USER/src/main.c:353-372`: normal mode consumes near-line centerline; `CROSS_IN` consumes farline from the far L index onward.
* `Project/USER/src/main.c:392-401`: in `CROSS_IN`, reference forces `begin_id = 0` before resampling centerline.
* `Project/USER/src/main.c:532-545`: reference ordinary `process_image()` starts from fixed `begin_y` and scans horizontally at that row.
* `Project/CODE/cross.c:50-54`: cross entry is double L.
* `Project/CODE/cross.c:56-92`: in `CROSS_IN`, missing far L does not clear `track_type`; the previous global side can persist.
* `Project/CODE/cross.c:128-251`: farline scans upward on fixed far columns, traces from the detected white point, resamples, then finds far L.
* `Project/CODE/circle.c:23-31`: circle entry is single-side L plus opposite straight.
* `Project/CODE/circle.c:33-145`: each circle state directly writes `track_type` according to inner/outer side.

## Teammate Patch Comparison

| Item | Teammate idea / observed effect | Current code | RT1064 alignment | Mechanism judgment | Risk | MVP recommendation |
|---|---|---|---|---|---|---|
| `CONTROL_CENTER_X` 60 -> 85 -> 80 | 85 made the car move from stuck to movable; 80 reportedly better | `tuning.hpp` still sets `CONTROL_CENTER_X = 60`; runtime can also read `SMARTCAR_CONTROL_CENTER_X` in `runners.cpp` | Reference uses geometric center plus mapping parameters, not this exact split | This changes the control reference point, not seed center. It can improve steering bias, but does not explain missing left seed or farline by itself | Medium: changing control reference affects all straight/curve/element steering | Keep as calibration note; do not mix into cross/ring state fix unless a separate calibration pass confirms it |
| Control: delay clearing integrators for 3 bad element frames | Avoid one-frame invalid line causing a visible brake/pause | Current `control.cpp` clears state immediately on `!line_ok()` | RT1064 has no equivalent explicit `input_valid` stop gate, but also does not provide this exact controller latch | It masks downstream invalid-line frames rather than fixing line generation. It may reduce pause but can keep old control through a genuinely blind frame | High in vehicle path | Do not include as first MVP; only consider after vision-side cause is narrowed and with explicit fail-safe bounds |
| `mainline.cpp` BEGIN->IN does not truncate `rpts` | Intended to keep near-line points when entering cross | Current code truncates near lines for cross BEGIN, then only uses farline when already in `CROSS_IN` at frame start | Reference truncates near lines in `CROSS_BEGIN`; in `CROSS_IN` it uses farline | Not clearly aligned. The stop described happens with no farline/L, so keeping near-line points may not address the core farline side decision | Medium-high: near-line in cross may be geometrically misleading | Not MVP unless exact failing frame is the transition frame rather than sustained `CROSS_IN` |
| `cross.cpp` farline failure fallback side | Avoid `TRACK_TYPE_NONE` when far L is missing | Current `cross_evolve()` clears side every frame, so missing far L can become `NO_MIDLINE` | Strongly aligned at the side-decision level: RT1064 preserves previous `track_type` when no new far L/near-loss evidence appears | This is the cleanest RT1064 semantic mismatch. But preserving only side is insufficient if `solve_cross_mid()` still needs fresh far L index | Medium: stale far L/side can steer wrong if unbounded | Best candidate, but implement as bounded cross-local farline/side persistence, not as generic fallback |
| `ring.cpp` 3-frame confirmation + RUN timeout | Reduce ring false state changes and avoid being trapped in RUN | Current ring has lost/have counters for BEGIN and END, encoder timeout only in IN; no explicit RUN timeout | RT1064 uses lost/have counters and encoder in IN; no identical RUN timeout visible in `circle.c` | Confirmation is plausible for robustness; RUN timeout is a separate state-machine escape, not a direct fix for first-corner stop | Medium: timeout can skip required ring phase and choose wrong side | Keep as secondary ring stabilization after cross/seed chain; not first MVP |
| Trace failure does not clear all data; retain short boundary through sharp bend | Intended to prevent single bad trace frame from deleting usable near-line/L context | Current `tracking_process_frame()` clears `rt->track`, seeds, traces each frame; `trace_edges()` clears failed side seed/trace | Reference arrays are recomputed each frame, but global `track_type` persists and centerline update is suppressed if too few points | This is a broad temporal memory change. It may help border/short-line dropout, but it can also reuse stale geometry | High unless narrowly scoped | Do not implement globally. If needed, use a bounded, element-local latch for cross farline only |
| Single-side L triggers cross and single-side L near enters IN | Teammate says double L is too strict; their last version caused broader failures | Current `cross_process()` requires both `l_ok`; `cross_begin()` also requires `both_l && (left_near || right_near)` | RT1064 cross entry is double L. RT1064 circle entry is single L + opposite straight | The complaint is real, but the proposed fix mixes cross with circle/acute bend semantics. A single L alone is not enough to classify cross | High; observed to break other cases | Reject as stated. If revisited, require extra constraints such as opposite-side geometry, width/open checks, state hysteresis, and no active ring |

## Mechanism Table From Field Symptoms

| Field symptom | Most likely current choke point | Why it fits the code | RT1064 comparison | Suggested handling |
|---|---|---|---|---|
| Left boundary visibly enters from left image edge but is not found | `find_seeds()` fixed bottom-row search | Ordinary trace cannot start if row `START_HIGH` lacks the edge; corner detection then has no point list to analyze | Reference ordinary `process_image()` is also fixed-row, so this is not a direct reference mismatch | Treat as seed/acquisition weakness, separate from cross-side persistence |
| Enter cross, no farline points appear | `find_far_seed()` / `build_cross_farline()` fixed-column upward scan plus `trace_single()` / far L filter | `build_cross_farline()` returns 0 on seed, trace, IPM, point-count, or far-L failure; then side can become NONE | RT1064 farline also can fail, but side state is not cleared to NONE | First fix should address current invalid-side discontinuity, not weaken final midline validity |
| Lower L disappears and car stops | `cross_evolve()`/`ring_process()` element side required but no valid midline | L loss itself does not directly stop; it changes state/side/farline availability, which can lead to `NO_MIDLINE` | RT1064 keeps side state and directly consumes selected side | Do not globally keep stale L; preserve only bounded element-side decision if needed |
| Roundabout first corner disappears, then stop | Ring forced side cannot generate enough midline/lookahead after state transition | `mainline.cpp` forces side by ring state; failure after side choice becomes `NO_MIDLINE` | Reference also forces side, but lacks explicit invalid-output stop gate | Do not add opposite-side fallback first; inspect ring IN/RUN selected-side point counts in existing report/replay if available |
| Roundabout mid-stage manually placed car has good midline but does not enter inner circle | State timing or steering reference/calibration may be late/weak | `CONTROL_CENTER_X`, `LOOKAHEAD_DIST`, ring side, and control yaw loop all affect entry arc | Reference has different geometry, `pixel_per_meter`, `aim_distance`, and servo/motor system | Keep as second phase after hard-stop cause; do not mix tuning with detection fix |

## Converged MVP Direction

The safest narrow MVP is not "single L cross" and not "ignore no-midline." It is:

1. Keep the control-layer stop gate unchanged.
2. Keep RT1064's double-L cross entry for now.
3. For cross only, study a bounded version of RT1064's persistent side behavior inside `CROSS_IN`: uncertainty in one frame should not automatically become `TRACK_TYPE_NONE`, but the final midline and lookahead checks must still pass.
4. Treat border-entry seed acquisition as a separate acquisition problem. It explains missing visible left lines, but it is not directly solved by changing cross entry from double L to single L.
5. Treat ring as second phase. Its entry rule is already RT1064-like; the likely issue is selected-side midline generation or calibration, not the high-level state table.

Concrete first code surface if implementation is approved later:

* `code/tracking/cross.cpp`: `cross_evolve()` side/farline persistence semantics.
* `code/tracking/mainline.cpp`: `solve_cross_mid()` dependency on fresh `left_l/right_l`.
* `code/types.hpp`: only if a bounded latch requires new cross fields; avoid this if the same behavior can be encoded without expanding shared state.

Concrete surfaces to avoid in the first patch:

* `code/core/control.cpp`
* `code/drivers/drive_output.cpp`
* global `TRACK_REJECT_NO_MIDLINE` semantics
* ring opposite-side fallback
* single-L cross entry without additional constraints

## Source Change Discipline

No source edit should happen until the proposed line-level patch is reviewed against this checklist:

1. Exact position: `file:line` from the current checkout.
2. Current behavior: what the existing line does in the frame/state machine.
3. Proposed behavior: the smallest semantic change, preferably one local mechanism.
4. RT1064 basis: the exact reference file/line or explicit note that the change is not copied from RT1064.
5. Downstream impact: how the value reaches `solve_cross_mid()`, `track.track_type`, `track.reject_reason`, `control.input_valid`, and `drive_output_stop()`.
6. Failure mode: what can go wrong if the assumption is false.
7. Rollback: which exact line(s) restore previous behavior.

## Candidate Code Position Map

| Priority | Current position | Current behavior | Why this is a choke point | RT1064 reference | Change caution |
|---|---|---|---|---|---|
| P0 | `code/tracking/cross.cpp:353-362` | Clears `cross.track_type`, farline flags, far L indices, and farline arrays every `CROSS_IN` evolve frame | Converts a transient farline/L miss into `TRACK_TYPE_NONE` before side selection | `Project/CODE/cross.c:56-92` keeps global `track_type` unless new evidence overwrites it | Do not simply delete all clearing; farline point arrays still need fresh-frame ownership unless a bounded latch is explicitly designed |
| P0 | `code/tracking/cross.cpp:405-424` | Selects right far L, then left far L, then near-line-lost side; otherwise leaves side as `TRACK_TYPE_NONE` | This is the direct source of `NONE -> NO_MIDLINE -> input_valid=0` in cross | `Project/CODE/cross.c:87-90` has the same overwrite order, but no final clear-to-none | Any fallback must be cross-local and bounded, not a global ordinary-line fallback |
| P0 | `code/tracking/mainline.cpp:526-551` | In already-active `CROSS_IN`, rejects if side is none, farline midline is too short, or lookahead is missing | This is the hard stop conversion point from cross side/farline uncertainty to tracking reject | `Project/USER/src/main.c:353-372` consumes farline by `track_type`; no explicit `TRACK_NONE` gate exists | Do not weaken final midline/lookahead checks unless separately justified |
| P0 | `code/tracking/mainline.cpp:153-237` | `solve_cross_mid()` requires fresh farline found, fresh far L index, enough points after L, then expands from that side | Preserving only `cross.track_type` will not help if fresh `left_l/right_l` is still required every frame | `Project/USER/src/main.c:364-371` starts from `far_Lpt*_id` in `CROSS_IN` | If a latch is added, this function must define whether it can consume a saved L index or only fresh indices |
| P1 | `code/tracking/imgproc.cpp:214-290` | Ordinary seed search scans only one bottom row from center offsets | Explains visible border-entry line not being traced, because no seed means no boundary and no L | `Project/USER/src/main.c:532-545` also uses fixed `begin_y`, so this is not a direct RT1064 mismatch | Treat as a separate acquisition patch, not part of the first cross semantic patch |
| P1 | `code/tracking/boundary.cpp:430-510` | L corners are per-frame and double-L pair failure clears both `l_ok` flags | Explains why yaw/offset can lose both usable L flags even when one corner is visible | `Project/CODE/cross.c:50-54` uses double L for cross; `Project/CODE/circle.c:23-31` uses single L plus opposite straight for circle | Do not change cross to single L directly; it already broke broader behavior in teammate test |
| P1 | `code/tracking/ring.cpp:259-304` | Ring entry is single-side L plus opposite straight | This part is already RT1064-like; not the first suspected mismatch | `Project/CODE/circle.c:23-31` | Avoid changing ring entry before cross/seed cause is isolated |
| P1 | `code/tracking/mainline.cpp:559-635` | Ring state forces side, then midline/lookahead failure rejects frame | Likely hard-stop path inside ring after state has selected an inner/outer side | `Project/CODE/circle.c:33-145` forces `track_type` by state | Do not add opposite-side fallback; it can steer the wrong arc |
| Avoid | `code/core/control.cpp:95-150` | Invalid line clears controller state and outputs no valid control | It is the final safety conversion, not the visual root cause | RT1064 has a different control architecture; no direct safe copy | Do not patch first |
| Avoid | `code/drivers/drive_output.cpp:134-144` | `!input_valid` calls `drive_output_stop()` | Final motor safety gate | No applicable RT1064 line for this architecture | Do not patch |
| Calibration only | `code/tuning.hpp:20-33` | `CONTROL_CENTER_X = 60`, `MID_X = 80`, `START_HIGH = 116` | Control reference and seed geometry interact, but this is not the cross farline clearing mismatch | RT1064 uses `begin_x=32`, `begin_y=167` in `Project/CODE/flash_param.c:22-23` | Do not mix calibration with state-machine patch |

## Patch Draft V1: Cross Far-L Index Hold (Not Applied)

This is the current preferred P0 patch shape if source editing is approved. It intentionally does not reuse old farline point arrays. It only reuses the last valid far-L index when the current frame still has a usable farline point array for the same side.

Why not a one-line patch:

* Deleting `code/tracking/cross.cpp:354` is insufficient. `code/tracking/mainline.cpp:153-237` still requires `left_l/right_l >= 0`, enough farline points after that L, and a valid midline.
* Keeping old farline arrays wholesale is higher risk. It can steer from stale geometry when the car has already moved inside the cross.

Line-level draft:

| Step | Position | Draft change | Current behavior | Proposed behavior | RT1064 basis | Downstream impact | Rollback |
|---|---|---|---|---|---|---|---|
| 1 | `code/types.hpp:85-97` | Add three fields after `track_type`: `far_hold_count`, `last_far_track_type`, `last_far_l` | `cross_state_t` only stores current-frame side and current-frame farline/L | Store a very short cross-local memory of the last valid far-L side/index | `Project/CODE/cross.c:56-92` keeps global `track_type`; `far_Lpt*_id` is not cleared when `far_Lpt*_found` is false | Adds state only inside `rt->cross`; zeroed by existing `memset` in init/leave | Delete the three fields |
| 2 | `code/tracking/cross.cpp:28-29` | Add `const int k_cross_far_hold_frames = 2;` | No bounded far-L memory exists | Allow at most two uncertain frames to reuse a last valid far-L index | Reference keeps side continuously; this port bounds it to avoid stale control | Limits fallback duration before `TRACK_REJECT_NO_MIDLINE` returns | Delete the constant |
| 3 | `code/tracking/cross.cpp` before `far_l_index()` | Add small helpers: save last valid far L; try reuse last L only when current same-side farline exists, point count is enough, and saved index is in range | Fresh far L is required every frame | Current farline may use last valid L index for the same side | Reference uses farline from `far_Lpt*_id`; missing-found flag does not necessarily erase the previous id | If helper fails, normal reject path remains | Delete helpers and restore direct selection block |
| 4 | `code/tracking/cross.cpp:353-362` | Keep current clearing of current-frame `track_type`, farline flags, L indices, and arrays | Current-frame data is owned by the current frame | No change to current-frame ownership; hold fields are separate and not cleared here | Safer than preserving whole old arrays | Avoids stale farline arrays reaching `solve_cross_mid()` | No rollback needed |
| 5 | `code/tracking/cross.cpp:405-424` | Replace direct side assignment with: fresh right/left save hold; else near-line side can try held L; else uncertain frame can try previous side; otherwise remain NONE | Missing fresh far L often leaves `track_type` NONE or leaves side without usable L | If current farline exists but L flickers, set current `left_l/right_l` from held index and keep final midline checks | `Project/CODE/cross.c:87-90` overwrites side only on evidence; otherwise old side survives | Can turn one/two far-L-index dropout frames into valid `solve_cross_mid()` output, but still stops if no current farline or no lookahead | Restore old `if(right_ok) ... else if(left_ok) ... else if(not_have_line > 0) ...` block |
| 6 | `code/tracking/mainline.cpp:153-237` | No code change | Requires current `left_l/right_l` and farline points | Continue requiring a valid farline-derived midline | Keeps final geometry gate stricter than RT1064 | `track.track_type` is written only after `solve_cross_mid()` and lookahead pass | No rollback needed |
| 7 | `code/core/control.cpp:95-150` and `code/drivers/drive_output.cpp:134-144` | No code change | Invalid tracking still clears control and stops output | Safety gate stays intact | No direct RT1064 copy due different architecture | No invalid line is allowed to drive motors | No rollback needed |

Expected behavior if the hypothesis is correct:

* A single far-L-index dropout inside `CROSS_IN` no longer immediately becomes `NO_MIDLINE` when the same-side farline still exists.
* If farline seed/trace fails completely, the car still stops through the existing `NO_MIDLINE -> input_valid=0 -> drive_output_stop()` path.
* Ring behavior is unchanged.
* `CONTROL_CENTER_X` is unchanged.

## Patch Draft V2: Reference-Style Minimal Hold (Not Applied)

User preference: this approach is favored because it is closer to the RT1064 reference and has less added state than V1. It still needs careful thought because current code clears `left_l/right_l` in two places:

* `code/tracking/cross.cpp:357-358` clears both before farline rebuild.
* `code/tracking/cross.cpp:226-227` clears the selected side again inside `build_cross_farline()`.

Therefore, a true reference-style simplification is not just "do not clear in `cross_evolve()`"; it must also decide how `build_cross_farline()` treats a previous L index when the current farline exists but current L detection fails.

Reference behavior being matched:

* `Project/CODE/cross.c:227` clears only `far_Lpt0_found/far_Lpt1_found`.
* `Project/CODE/cross.c:233-247` overwrites `far_Lpt*_rpts*s_id` only when a new far L is found.
* `Project/CODE/cross.c:87-90` overwrites `track_type` only when new far L or near-line-loss evidence exists.

Minimal current-code equivalent:

| Step | Position | Draft change | Current behavior | Proposed behavior | Risk control |
|---|---|---|---|---|---|
| 1 | `code/tracking/cross.cpp:354` | Stop clearing `rt->cross.track_type` every `cross_evolve()` frame | Missing current evidence becomes `TRACK_TYPE_NONE` | Preserve previous side unless new evidence overwrites it | Still rejected later if midline cannot be generated |
| 2 | `code/tracking/cross.cpp:357-358` | Do not clear `left_l/right_l` in `cross_evolve()` | Previous L index is destroyed before farline rebuild | Let previous L index survive until current side proves it invalid or overwrites it | Must validate against current farline length before use |
| 3 | `code/tracking/cross.cpp:226-227` | Change `build_cross_farline()` so it does not blindly set `*far_l = -1` before trying to find a new far L | Previous side-specific L index is destroyed inside the builder | Preserve old side-specific L while rebuilding current side farline; overwrite if `far_l_index()` finds a new one | If seed/trace/IPM fails completely, clear the side's `far_num/far_found`; `solve_cross_mid()` will reject |
| 4 | after `code/tracking/cross.cpp:270` | After `*far_l = far_l_index(...)`, only overwrite with new index if the result is `>= 0`; otherwise keep old index only if it is valid for the current `*far_num` and leaves enough points | Current code always stores `-1` on L miss | Current farline can use previous L index if it remains in range | Prevents stale out-of-range index |
| 5 | `code/tracking/cross.cpp:386-424` | Compute `left_ok/right_ok` from current farline plus validated `left_l/right_l`; side selection stays in current order | Current `left_ok/right_ok` fail immediately on L miss | If current farline exists and old L index is still usable, side remains valid | No control-layer bypass |
| 6 | `code/tracking/mainline.cpp:153-237` | No change | Requires current farline, L index, enough points, midline output | Continues to be the final geometry gate | Keeps safety stricter than RT1064 |

Important edge cases:

* If current farline point count is shorter than the old L index, clear that side's L to `-1`.
* If `current_num - old_l < k_cross_min_front_step`, clear that side's L to `-1`.
* If current farline seed/trace fails and `left_far_found/right_far_found` is false, do not use the old L index.
* Do not preserve old farline point arrays.

Trade-off vs V1:

* V2 is closer to the reference and avoids adding `hold_count/last_far_*` fields.
* V2 can preserve an L index for longer than 1-2 frames as long as current farline length keeps making it look valid. That is closer to RT1064 but less explicitly bounded.
* V1 is more bounded but adds more state and looks less like the reference.

## Proposed Solution: V2 Minimal Current-Farline L Reuse

Decision candidate: use V2 as the MVP. The goal is to match the useful RT1064 behavior without copying its fully implicit global-variable risk.

Core rule:

```text
current frame has a newly detected far L
    -> use the new L index
current frame has a farline but no far L
    -> reuse the previous L index only if it still fits the current farline
current frame has no farline
    -> do not reuse the previous L index
```

This means `left_l/right_l` become "current usable farline start index", not strictly "this frame's freshly detected L index".

Source-level shape:

1. `code/tracking/cross.cpp:354`
   * Do not clear `rt->cross.track_type` at the beginning of every `cross_evolve()` frame.
   * Reason: RT1064 `track_type` persists unless new evidence changes it.

2. `code/tracking/cross.cpp:357-358`
   * Do not clear `rt->cross.left_l/right_l` in `cross_evolve()`.
   * Reason: previous L index must survive long enough for `build_cross_farline()` to decide whether it still fits the current farline.

3. `code/tracking/cross.cpp:226-228`
   * In `build_cross_farline()`, save the old side-specific L index before clearing point count/point array:
     ```text
     old_l = *far_l
     *far_num = 0
     clear far_pts
     ```
   * Do not immediately set `*far_l = -1`.

4. Failure inside `build_cross_farline()`
   * If seed/trace/IPM/current farline point generation fails, set `*far_l = -1` before returning `0`.
   * Reason: old L index cannot be used without a current farline point array.

5. Success inside `build_cross_farline()`
   * After current farline points are built:
     ```text
     new_l = far_l_index(current_far_pts, current_far_num)
     if new_l >= 0:
         *far_l = new_l
     else if old_l fits current farline:
         *far_l = old_l
     else:
         *far_l = -1
     ```
   * "Fits current farline" means:
     ```text
     old_l >= 0
     old_l < *far_num
     *far_num - old_l >= k_cross_min_front_step
     ```

6. `code/tracking/cross.cpp:386-424`
   * Keep the side-selection order unchanged:
     ```text
     right far L/farline valid first
     left far L/farline valid second
     near-line-lost side last
     otherwise preserve previous side because track_type was not cleared
     ```

7. `code/tracking/mainline.cpp:153-237` and `code/tracking/mainline.cpp:526-545`
   * No change.
   * `solve_cross_mid()` and `midline_has_lookahead()` remain the final geometry gates.

8. `code/core/control.cpp` and `code/drivers/drive_output.cpp`
   * No change.
   * `NO_MIDLINE -> input_valid=0 -> drive_output_stop()` remains intact.

Why this is the best current solution:

* It fixes the exact failure chain: preserved side alone is not enough; the usable L start index must also survive a one-frame L detection miss.
* It does not keep stale farline point arrays; the old L index is only applied to the current frame's newly rebuilt farline.
* It is closer to RT1064 than V1 because it avoids adding new `hold_count/last_far_*` fields.
* It is safer than raw RT1064 behavior because old index reuse is rejected when it is out of range or leaves too few points.

Out of this MVP:

* Single-L cross entry.
* Ring state changes.
* Seed acquisition changes for border-entry lines.
* `CONTROL_CENTER_X` tuning.
* Control-layer tolerance or delayed stop.
