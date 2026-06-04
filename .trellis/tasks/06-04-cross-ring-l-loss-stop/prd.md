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
* Team local tuning note: changing `code/tuning.hpp` `CONTROL_CENTER_X` from `60` to `85`, then to `80`, improved behavior; user has now changed current source to `CONTROL_CENTER_X = 80`.
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
* RT1064 cross farline uses `far_x1 = 86`, `far_x2 = 280`, and starts vertical scanning from `begin_y`.
* RT1064 default `begin_y = 167` on a 240-high image, so the height-normalized start row is `167 / 240 = 0.696`.
* Current `front_car_mainline` uses `START_HIGH = 116` on a 120-high image, so the height-normalized start row is `116 / 120 = 0.967`.
* Current cross farline therefore reuses a much lower near-line row; a reference-scaled cross farline start row would be about `167 * 120 / 240 = 83.5`.

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

### C-FY: Separate cross farline begin row from ordinary near-line start row

* Type: small cross-local parameter alignment.
* Evidence:
  * RT1064 reference `flash_param.c` sets `begin_y = 167`.
  * RT1064 reference `cross.c::cross_farline()` starts fixed-column vertical scan from `begin_y`.
  * Current `code/tracking/cross.cpp::find_far_seed()` starts from `START_HIGH` or `rt->seeds.row`, typically `116` on a 120-high image.
* Idea:
  * Add a cross-local constant for farline vertical scan start, derived from RT1064 `begin_y` by image-height scaling.
  * Use that constant only in `find_far_seed()`.
  * Do not change ordinary `START_HIGH`, ordinary `find_seeds()`, control reference point, ring fixed-column start, or zebra bottom scan.
* Candidate values:
  * `84`: strict rounded scale from `167 / 240 * 120 = 83.5`.
  * `83`: floor-ish scale from the same ratio.
  * `82`: slightly more aggressive upward start, close to the scaled reference but not the strict rounded value.
* Recommendation:
  * Prefer `84` as the first patch because it is directly explainable from the reference ratio and easy to roll back.
  * Use `82` only if field evidence shows `84` still starts too low for the visible farline.
* Rollback:
  * Revert the one cross-local constant or switch `find_far_seed()` back to `START_HIGH`.

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

* `code/tuning.hpp:20-33`: `MID_X = RAW_W / 2`, `CONTROL_CENTER_X = 80`, `START_HIGH = 116`.
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
| `CONTROL_CENTER_X` 60 -> 85 -> 80 | 85 made the car move from stuck to movable; 80 reportedly better | User has changed `tuning.hpp` to `CONTROL_CENTER_X = 80`; runtime can also read `SMARTCAR_CONTROL_CENTER_X` in `runners.cpp` | Reference uses geometric center plus mapping parameters, not this exact split | This changes the control reference point, not seed center. It can improve steering bias, but does not explain missing left seed or farline by itself | Medium: changing control reference affects all straight/curve/element steering | Treat as guidance from the baseline-version patch. Do not assume it is required for the cross/ring mechanism fix unless field validation confirms it. |
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
| Calibration only | `code/tuning.hpp:20-33` | `CONTROL_CENTER_X = 80`, `MID_X = 80`, `START_HIGH = 116` | Control reference and seed geometry interact, but this is not the cross farline clearing mismatch | RT1064 uses `begin_x=32`, `begin_y=167` in `Project/CODE/flash_param.c:22-23` | Keep separate from the state-machine patch. It is a field-tuning candidate, not proof of the root cause. |

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
* Further `CONTROL_CENTER_X` tuning beyond the current user-applied `80`.
* Control-layer tolerance or delayed stop.

## Implementation Record

Decision implemented: V2 Minimal Current-Farline L Reuse.

Changed source:

* `code/tracking/cross.cpp`

Actual behavior after implementation:

* `cross_evolve()` still clears the current-frame farline found flags, point counts, and point arrays.
* `cross_evolve()` no longer clears `rt->cross.track_type`, `rt->cross.left_l`, or `rt->cross.right_l` at the start of every `CROSS_IN` frame.
* `build_cross_farline()` saves the previous side-specific L index before rebuilding the current farline.
* If current farline generation fails at seed, trace, IPM, or point-count stages, the side-specific L index is cleared to `-1`.
* If current farline generation succeeds and a fresh far L is found, the fresh index is used.
* If current farline generation succeeds but no fresh far L is found, the previous L index is reused only when:
  * `old_l >= 0`
  * `old_l < current_far_num`
  * `current_far_num - old_l >= k_cross_min_front_step`
* If those checks fail, the side-specific L index is cleared to `-1`.

Unchanged safety gates:

* `code/tracking/mainline.cpp` still rejects `CROSS_IN` when `cross.track_type == TRACK_TYPE_NONE`, `solve_cross_mid()` is too short, or the midline lacks lookahead.
* `code/core/control.cpp` still treats `TRACK_TYPE_NONE` or nonzero `reject_reason` as invalid input.
* `code/drivers/drive_output.cpp` still stops output when control input is invalid.

Validation:

* `make CMakeFiles/front_car_mainline.dir/tracking/cross.cpp.o -j1` in `code/build` passed.
* Full `./test.sh` was attempted. It compiled through `tracking/cross.cpp.o`, then failed in the existing assistant dependency path: `libraries/zf_components/seekfree_assistant/seekfree_assistant.cpp:37:10: fatal error: vision2_core.hpp: No such file or directory`.
* The full-build failure is outside this patch surface and is not caused by the `cross.cpp` change.

## Current Progress Reassessment

User assessment: the bug fix is only about 10% complete.

Interpretation:

* The implemented V2 cross farline reuse fixes one narrow failure chain: current farline exists, fresh far L detection flickers, and old L index still fits the current farline.
* It does not fix frames where the farline seed/trace itself fails.
* It does not fix the visible border-entry ordinary seed acquisition weakness.
* It does not fix ring selected-side midline failure.
* It does not prove that control-layer pauses are only caused by visual invalid frames.
* It does not change cross entry from double L to single L, by design.

The teammate baseline-version patch table is guidance only, not an implementation checklist for the current codebase:

* Do not automatically copy the five baseline-version changes into the current branch.
* `CONTROL_CENTER_X = 80` is a field-tuning observation, not proof of the root cause.

## Deep Reference Note: Two Searches in Cross

There are two different searches that must not be merged conceptually:

### Search A: Ordinary near-line seed search

Current code:

* `code/tracking/imgproc.cpp:214-290` searches one fixed row (`START_HIGH`) from `mid_position +/- kSeedStartOffset`.
* It can return a single-side seed, but it cannot start a line that first enters from the left/right image border if that boundary is not visible on the fixed bottom row.
* This explains the user's video observation that a visually clear side-border line may not be acquired.
* Image evidence from user: in the cross-entry screenshots, the left boundary is visually clear and enters from the left image border, but the overlay does not acquire/trace it. This strongly supports Search A being incomplete rather than a pure cross-farline L-index problem.

RT1064 reference:

* `Project/USER/src/main.c:532-545` also uses fixed `begin_y` and horizontal scanning for ordinary line acquisition.
* Therefore side-border acquisition is a real weakness, but not the most direct RT1064 mismatch.

Best interpretation:

* Search A affects whether near boundaries and near L points exist.
* It can prevent cross entry or leave the system without useful near-line evidence.
* It does not by itself explain why the car stops after already entering `CROSS_IN`.
* However, if Search A starves near-line acquisition before or during cross entry, Search B can also be starved indirectly because cross state and fallback decisions depend on near-line/L context.

### Search B: Cross farline seed and far-L search

Current code:

* `code/tracking/cross.cpp:157-217` scans upward on a fixed far column, looking for white first and then black, and returns the previous white point as the farline seed.
* `code/tracking/cross.cpp:224-306` traces the current farline from that seed, transforms/smooths/resamples it, and finds a far L index.
* `code/tracking/mainline.cpp:153-237` builds the control midline only from the selected farline segment starting at that L index.

RT1064 reference:

* `Project/CODE/cross.c:128-251` performs the same farline pattern: fixed far column upward scan -> trace -> transform -> smooth/resample -> find far L.
* `Project/USER/src/main.c:353-372` uses `track_type` to choose the farline and starts centerline generation from `far_Lpt*_rpts*s_id`.

Best interpretation:

* Search B is the direct path for `CROSS_IN` control.
* In current code, if this path cannot provide a usable side plus usable far-L index, `mainline.cpp` rejects with `TRACK_REJECT_NO_MIDLINE`, which then disables control output.
* The best reference alignment is not to invent a direct "far midline search"; the reference does not do that. It searches far side boundaries, finds far L, then expands side boundary into the control midline.

### Best Reference Priority

For the next cross fix, use RT1064 `cross.c` / `main.c` as the primary reference, but only for the cross-local visual contract:

1. Farline is side-boundary based, not direct-midline based.
2. `track_type` persists across uncertain frames unless new evidence overwrites it.
3. Farline point arrays should still be rebuilt from the current frame.
4. Final control safety should remain stricter than RT1064 in this port: no valid midline and no lookahead still means invalid tracking output.

Do not use `TC264-Peripheral-perspective` as the primary cross behavior reference. It is useful evidence for seed mechanics (`Seek_Pts_Seed` row search and `seek_up` column search), but it does not define the RT1064-style `CROSS_IN` farline control contract.

Do not use `Front_Car` current `image_processing.c` as proof because it is a stub. Its `.bak` confirms similar row/column seed mechanics only.
* Control-layer bad-frame tolerance remains high risk unless the visual failure mode is bounded first.
* Global trace-data retention remains high risk unless narrowed to a specific element state.

## Next Brainstorm Branches

### Branch A: Cross Farline Acquisition

Question: when entering cross, is failure now mostly "current farline does not exist" rather than "farline exists but L index is missing"?

Likely code surfaces:

* `code/tracking/cross.cpp::find_far_seed()`
* `code/tracking/cross.cpp::build_cross_farline()`
* `code/tracking/imgproc.cpp::trace_single()`

Why this matters:

* V2 cannot help if `left_far_found/right_far_found` are false.
* The video observation "no farline appears" points here.

### Branch B: Ordinary Border-Entry Seed Acquisition

Question: should ordinary seed search handle a clear boundary entering from the left/right image border instead of the bottom row?

Likely code surfaces:

* `code/tracking/imgproc.cpp::find_seeds()`
* `code/tracking/imgproc.cpp::find_column_seed()`
* `code/tracking/mainline.cpp::trace_edges()`

Why this matters:

* If no ordinary boundary is acquired, L corners cannot be detected, cross/ring state can be starved, and the car can reach an element with no usable near-line context.

Correction after user review:

* The screenshots prove Search A is incomplete, but they do not yet prove that the right implementation is a new side-border seed path.
* Before designing a side-border seed, distinguish four mechanisms:
  * the boundary exists on `START_HIGH`, but is rejected because it is too close to `kSeedBorderMargin`;
  * the boundary exists above `START_HIGH`, but not on the fixed seed row;
  * the row scan sees the boundary but local threshold / white-black transition logic rejects it;
  * the boundary truly only has a side-entry geometry and needs a different seed source.
* A side-border seed is only justified by the fourth mechanism. The first three should be solved by smaller changes to current row-search parameters or row-search policy.

### Branch B Reference Comparison: Multi-row Horizontal Seed Scan

Local source comparison:

* `TC264-Peripheral-perspective/code/image_processing.c:225-277`
  * `Seek_Pts_Seed(High, mini_high)` first scans one fixed row:
    ```text
    found_left_x = find_edge_canny_row(High, mid_position, 0)
    found_right_x = find_edge_canny_row(High, mid_position, 1)
    ```
  * If only one side is found, it scans rows above `High` down to `mini_high`, still using horizontal row search from `mid_position`, to find the missing opposite side.
  * It does not scan the image side border directly.
  * It does not run a broad multi-row search when both sides are missing.

* `Front_Car/code/image_processing.c.bak:288-350`
  * Backup implementation has the same row-first and missing-opposite-side fallback pattern.
  * It additionally updates `mid_position` from `width_base` when only one seed exists:
    ```text
    left only  -> mid_position = Seed_left[0] + width_base / 2
    right only -> mid_position = Seed_right[0] - width_base / 2
    ```
  * This is important because it keeps the next frame's center seed closer to the road after a one-side frame.
  * Current `Front_Car/code/image_processing.c` is a stub and must not be used as behavior evidence.

* `RT1064_Code_ref/.../Project/USER/src/main.c:532-545`
  * RT1064 ordinary acquisition uses one fixed `begin_y` row:
    ```text
    x1 = center - begin_x, y1 = begin_y
    scan x1 left on that row
    trace left from (x1, y1)
    ```
  * It does not include the TC264-style multi-row missing-side fallback in ordinary `process_image()`.
  * RT1064's robustness around cross is more about state/side continuity and separate farline search than ordinary seed multi-row fallback.

* Current `front_car_mainline/code/tracking/imgproc.cpp:214-290`
  * Current `find_seeds()` is stricter than TC264/Front_Car backup in one key way: it does not scan nearby rows to recover a missing side.
  * It can return a single-side seed, but if the missing side appears only a few rows above `START_HIGH`, current code will not find it in this frame.

External-source comparison:

* Cytron's camera line-following tutorial describes multiple fixed horizontal scanlines and explicitly says multi-scanline sampling improves robustness against noise, uneven illumination, and partial occlusion. This supports multi-row/scanline ideas in general vision line following, but it uses centroid/scanline averaging rather than our seed + maze trace contract.
  * Source: https://sg.cytron.io/tutorial/differential-line-following-algorithm
* Pixy2 line tracking documentation emphasizes tracking the currently followed line/vector across frames rather than switching to every new line that appears. This supports preserving continuity and avoiding broad side-border pickup, but it is not direct code guidance for our seed search.
  * Source: https://docs.pixycam.com/wiki/doku.php?id=wiki%3Av2%3Aline_tracking
* Existing Branch B smart-search research also found Chinese smart-car sources describing scan-start/search-start as a separate stage before boundary following, and distinguishing center scan, edge scan, and element-specific starts.
  * Local note: `research/branch-b-border-seed-acquisition.md`

Mechanism conclusion:

* Multi-row horizontal补搜 is a conservative candidate because it keeps the same seed semantics: find a white/black boundary on a row, then let `trace_single()` validate.
* It is less invasive than side-border seed because it does not create a new seed topology.
* It is not a full fix for a true side-border entrant if no useful row near `START_HIGH` intersects the boundary.
* It is also not a direct RT1064 ordinary-line copy; it is closer to TC264/Front_Car backup.

If this branch becomes a code patch later, it should start as a missing-side recovery, not a broad search:

```text
try current START_HIGH row
if one side exists and the opposite side is missing:
    scan a limited number of rows above START_HIGH for the missing side only
    keep the found seed only if trace_single() accepts it
if both sides are missing:
    do not perform a broad multi-row rescue in the first patch
```

Open design detail:

* If left and right seeds come from different rows, current `seed_pair_accepted()` rejects the pair because it requires equal `y` and uses one `seeds->row`. A multi-row missing-side patch must either keep such a frame as single-side for trace/midline, or deliberately relax pair acceptance. Relaxing pair acceptance is broader and should not be first.

### Reassessment: Seed Width Is Not the Reference Width Contract

User correction:

* Treating current `seed_pair_t.width = right.x - left.x` as the main width source is misleading when aligning to the RT1064 reference.
* RT1064 ordinary `process_image()` does not preserve a seed-pair width field. It uses fixed-row seeds only to start `findline_lefthand_adaptive()` / `findline_righthand_adaptive()`.

RT1064 layer split:

1. Seed layer:
   * `Project/USER/src/main.c:532-545`
   * Find one raw start point per side on `begin_y`.
   * Purpose: start boundary tracing, not validate road width.

2. Boundary point layer:
   * `Project/USER/src/main.c:547-569`
   * Raw traced points are mapped through `mapx/mapy`, blurred, and resampled into `rpts0s/rpts1s`.
   * Downstream logic works on these point sequences, not seed-pair width.

3. Width / pair checks:
   * `Project/USER/src/main.c:655-672`
   * L-pair checks use distances between selected points in `rpts0s/rpts1s`, e.g. `hypot(dx, dy)` against `0.45 * pixel_per_meter`.
   * The pairing is by semantic point index such as L/Y point id, not by raw seed row.

4. Centerline generation:
   * `Project/CODE/imgproc.c:612-635`
   * `track_leftline()` and `track_rightline()` generate the centerline by offsetting a selected side boundary by `pixel_per_meter * ROAD_WIDTH / 2`.
   * Normal and element states choose which side to offset through `track_type`.

Current code mapping:

* `code/tracking/imgproc.cpp:257-263` stores `seeds->width` only when both fixed-row seeds are accepted on the same row.
* `code/tracking/imgproc.cpp:293-309` rejects seed pairs when left/right seed y differ.
* `code/tracking/mainline.cpp:305-388` already follows the RT1064 idea of choosing a single side based on resampled point counts and prior `track_type_keep`.
* `code/tracking/imgproc.cpp:769-977` already follows the RT1064 single-side outward offset idea with `ROAD_HALF_WIDTH`.
* `code/tracking/boundary.cpp:275-325` already performs L-pair width checks on traced/transformed point sequences, not raw seed row width.

Implication:

* A future multi-row seed patch should not be judged by whether it can produce a trustworthy `seeds->width`.
* Its main job is to start valid boundary traces.
* If left/right seed rows differ, that does not invalidate the traces by itself.
* The current `seed_pair_accepted()` contract may remain as a conservative report/pair-width contract, but it must not prevent valid single-side trace acquisition.

This is now a broader design branch, not a tiny implementation patch. Source changes are paused until the seed/trace/width/centerline contract is explicitly chosen.

### Candidate Architecture Directions After Reassessment

**A. Keep seed width as a conservative same-row report field, but decouple trace acquisition from pair acceptance** (recommended direction for a minimal future patch)

* Seed layer may find left/right seeds on different nearby rows.
* `trace_edges()` can trace each valid side independently.
* `seed_pair_accepted()` continues to mean "same-row pair with trustworthy seed width"; it does not decide whether a side may trace.
* Control still uses resampled boundary point counts and single-side outward offset.

**B. Remove or downgrade `seed_pair_t.width` from algorithmic decisions**

* Treat `seeds->width` as debug/report only.
* Ensure downstream algorithmic checks use point sequences (`rpts*`, L-pair width, midline lookahead) instead.
* Larger cleanup; not a first patch unless a direct dependency on seed width causes failure.

**C. Rebuild seed acquisition around row-indexed boundary arrays**

* Introduce per-row left/right boundary arrays and compute width by matching rows.
* This would answer the "corresponding width by row" idea directly.
* Very large rewrite and not aligned with the existing RT1064 point-sequence pipeline; reject for this task unless the whole tracking architecture is intentionally replaced.

### Branch C: Ring Selected-Side Midline Failure

Question: after ring state forces inner/outer side, which state first produces `TRACK_REJECT_NO_MIDLINE`?

Likely code surfaces:

* `code/tracking/ring.cpp`
* `code/tracking/mainline.cpp:559-635`

Why this matters:

* Ring entry is already close to RT1064, but current code has a stricter midline/lookahead reject gate after forced side choice.
* Opposite-side fallback is still risky because it can steer the wrong ring arc.

### Branch D: Control-Layer Bad-Frame Tolerance

Question: should control tolerate a tiny number of invalid element frames, and under what exact conditions?

Likely code surfaces:

* `code/core/control.cpp`
* `code/drivers/drive_output.cpp`

Why this matters:

* This can hide a visible pause, but it can also keep driving on a genuinely blind frame.
* It should not be the next patch unless the visual-side bad frame is proven brief, bounded, and element-local.

Recommended next branch: Branch A first, then Branch B, then Branch C. Branch D should remain deferred.

## Branch Selection Update

User selected Branch B first: Ordinary Border-Entry Seed Acquisition.

Reasoning:

* The cross farline failure in Branch A may be downstream of Branch B. If a clear border-entering line is not acquired as an ordinary boundary, then near-line point lists and L corners can disappear before cross farline logic has enough stable context.
* The observed cross failure may also involve state-machine timing or direct pause behavior that is not fully aligned with the RT1064 reference; therefore Branch A should not be treated as the only root cause.
* The baseline-version patch table is guidance only and should not be copied wholesale into the current branch.

Branch B current evidence:

* `code/tracking/imgproc.cpp::find_seeds()` searches one fixed row `START_HIGH` from `mid_position ± ROAD_HALF_WIDTH`.
* A boundary whose first visible point enters from the image left/right border can be visually clear while not crossing that fixed seed row at the expected x-range.
* `code/tracking/imgproc.cpp::find_column_seed()` already implements vertical fixed-column seed search, but current ordinary seed acquisition does not use it.
* `code/tracking/imgproc.cpp::trace_single()` rejects seeds too close to image border via `kTraceBorderMargin`, so a naive "seed exactly on border" fix can still fail downstream.

Branch B design constraints:

* Do not globally retain stale trace/boundary arrays as a first fix.
* Do not weaken final `TRACK_REJECT_NO_MIDLINE -> input_valid=0 -> drive_output_stop()` safety chain.
* Do not change cross entry to single-L as part of this branch.
* Any border-entry recovery must produce a current-frame seed and trace, not reuse old geometry blindly.

## Branch B Smart Search Result

Detailed research note: `research/branch-b-border-seed-acquisition.md`.

Smart-search conclusion:

* External smart-car sources support the same layered mechanism: seed acquisition first, boundary trace second, line repair/midline third.
* A visually clear side-border boundary can still fail if the seed acquisition stage only checks one bottom row and one expected center-offset window.
* General boundary tracing sources also support the same algorithmic dependency: tracing starts after locating an initial boundary pixel.
* RT1064 ordinary `process_image()` is also fixed-row, so ordinary side-border recovery is not a direct copied reference feature.
* RT1064 cross farline does provide a reference-aligned mechanism for vertical fixed-column current-frame seed acquisition.

Branch B current best direction:

* Prefer a small current-frame side-column seed supplement after the existing fixed-row seed search misses a side.
* Do not seed exactly on the image edge, because `trace_single()` rejects seeds within `kTraceBorderMargin`.
* Keep `trace_single()`, midline validity, control `line_ok()`, and motor stop gates unchanged.
* Before editing source, decide whether the supplement is always available for missing sides, only element-suspect, or only active cross/ring.

## Cross Farline Begin-Y Patch

User decision: use the reference-scaled cross farline start row `84`.

Implementation:

* `code/tracking/cross.cpp` now defines `k_cross_far_begin_y = (RAW_H * 167 + 120) / 240`.
* `find_far_seed()` now starts cross farline vertical scanning from `k_cross_far_begin_y`.
* Ordinary `START_HIGH = 116` remains unchanged for normal seed search, zebra bottom scan, ring start geometry, and control reference usage.
* `rt->seeds.row` no longer overrides the cross farline scan start row; this keeps cross farline aligned to the RT1064 `begin_y` ratio instead of binding it to the near-line seed row.

Reference basis:

* RT1064 `Project/CODE/flash_param.c` default `begin_y = 167`.
* RT1064 image height is `240`; current `RAW_H = 120`.
* Scaled row: `167 * 120 / 240 = 83.5`, rounded to `84`.

Validation:

* `git diff --check -- code/tracking/cross.cpp .trellis/tasks/06-04-cross-ring-l-loss-stop/prd.md` passed.
* `cmake --build code/build --target CMakeFiles/front_car_mainline.dir/tracking/cross.cpp.o -j1` passed.
* `./code/test.sh --host` compiled through `tracking/cross.cpp.o`, then failed in existing dependency path: `seekfree_assistant.cpp:37:10: fatal error: vision2_core.hpp: No such file or directory`.
* `./code/test.sh` compiled through `tracking/cross.cpp.o`, then failed at the same existing `vision2_core.hpp` missing include.

Rollback:

* Revert the one `k_cross_far_begin_y` constant and `find_far_seed()` start-row change, or switch `find_far_seed()` back to `START_HIGH`.

## Evidence Correction: Current Seed Width vs RT1064

Updated: 2026-06-05 02:39:55 +0800.

User correction:

* Do not describe the current code as having a literal `width = right.x - left.x` assignment.
* The exact source must be matched using the real field names and local variables.
* For this comparison stage, only compare the current project and the RT1064 reference. Other libraries are guidance only and should not drive the next conclusion.

Current project exact code facts:

* `code/types.hpp:14-20` defines `seed_pair_t` with `point_t left`, `point_t right`, `int row`, and `int width`.
* `code/tracking/imgproc.cpp:244-245` finds same-row seed candidates into local variables `x0` and `x1`.
* `code/tracking/imgproc.cpp:257` computes the candidate same-row raw seed span as `const int w = x1 - x0`.
* `code/tracking/imgproc.cpp:258-263` writes `seeds->width = w` only when both seeds are found on that fixed row and `w` is within `kSeedMinWidth..kSeedMaxWidth`.
* `code/tracking/imgproc.cpp:292-308` `seed_pair_accepted()` requires both seed bits, equal `left.y/right.y`, `seeds->row == left.y`, and `seeds->width` within range.
* `code/tracking/mainline.cpp:64-136` `trace_edges()` traces each side independently from valid seed coordinates. It calls `seed_pair_accepted()` before and after trace, but the observed source use of failed pair acceptance is clearing `rt->seeds.width = 0`; it does not block single-side `trace_single()` by itself.
* `code/app/report.cpp:20-42`, `111-117`, and `296-303` use seed-pair acceptance / seed width for diagnostic/report output, not direct control midline generation.

RT1064 exact code facts:

* `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/USER/inc/main.h:26-41` declares point arrays and point counts such as `ipts0/ipts1`, `rpts0/rpts1`, `rpts0s/rpts1s`; there is no ordinary seed-pair struct or ordinary seed-width field in this header.
* `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/USER/src/main.c:532-545` ordinary line acquisition uses local `x1/y1` and `x2/y2`, scans one fixed row outward, then directly calls `findline_lefthand_adaptive()` / `findline_righthand_adaptive()`. No seed-pair width is persisted.
* `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/USER/src/main.c:583-587` builds single-side candidate centerlines from traced/resampled point arrays using `track_leftline()` / `track_rightline()`.
* `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/USER/src/main.c:308-317` ordinary side selection uses `rpts0s_num/rpts1s_num`, not a raw seed width.
* `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/USER/src/main.c:653-672` L-pair geometry checks use distances between `rpts0s[...]` and `rpts1s[...]` points after tracing, mapping, filtering, and resampling.

Corrected interpretation:

* Current `seed_pair_t::width` is a same-fixed-row raw seed span, not a row-indexed boundary-array width.
* RT1064 does not have an equivalent ordinary seed-pair width contract.
* Therefore, when aligning with RT1064, the stable geometry contract should be traced/resampled point sequences and their counts/distances, not the raw fixed-row seed span.
* Because current `trace_edges()` already allows left and right seeds to trace independently, the key question is not "how to compute width when seed rows differ"; it is whether `seed_pair_t::width` should remain only a same-row report/diagnostic field while trace acquisition accepts any valid current-frame side seed.

## Candidate Decision: Remove `seed_pair_t::width`

User inclination:

* Prefer deleting the stored `seed_pair_t::width` field.
* Reason: RT1064 has no ordinary seed-width state, and TC264 / Front_Car style multi-row missing-side search can work from seed coordinates plus `Seed_State`.
* Front_Car's `width_base` is a separate concept: it is used to estimate `mid_position` when only one side seed exists, not to validate a current-frame same-row seed pair.

Current impact surface if removing the field:

* `code/types.hpp:14-20`: remove `int width` from `seed_pair_t`.
* `code/tracking/imgproc.cpp:257-263`: keep local `w = x1 - x0` only for same-row pair acceptance, but stop storing it in `seeds`.
* `code/tracking/imgproc.cpp:293-308`: make `seed_pair_accepted()` recompute same-row span from `seeds->right.x - seeds->left.x`, after verifying both seeds are on the same row.
* `code/tracking/mainline.cpp:128-132`: remove the `rt->seeds.width = 0` cleanup, because failed pair acceptance should not mutate seed coordinates or a removed field.
* `code/app/report.cpp:111-117` and `296-303`: remove or replace `seed_width` report output. If a report value is still wanted, compute a local same-row span only when `seed_pair_accepted()` is true.

Reference alignment:

* RT1064 ordinary seed coordinates are transient local start points (`x1/y1`, `x2/y2`) for trace.
* RT1064 side selection and element geometry checks are based on traced/resampled point counts and distances, not a persisted raw seed width.
* Deleting `seed_pair_t::width` moves the current project closer to this layer split without changing trace, midline, control, cross, or ring behavior by itself.

Important distinction:

* Removing `seed_pair_t::width` does not mean immediately adding `width_base`.
* `width_base` would be a cross-frame `mid_position` recovery aid for one-side seed frames. That is a separate behavior change and needs its own field ownership, update rule, stale reset rule, and rollback plan.

## Central Reframe: Four-Layer Reference Contract

User correction:

* The central issue is not `width_base`, not just deleting `seed_pair_t::width`, and not choosing ring before seed.
* The central issue is the reference-style layer contract:
  1. seed only starts boundary tracing;
  2. traced/IPM/resampled point sequences carry geometry;
  3. ordinary or element state chooses which side to follow;
  4. selected side is converted to control midline by fixed half-road-width normal offset.

Reference contract from RT1064:

* Seed layer:
  * `Project/USER/src/main.c:532-545`
  * Uses `x1/y1` and `x2/y2` only to start `findline_lefthand_adaptive()` / `findline_righthand_adaptive()`.
  * No persisted ordinary seed-pair width.
* Point-sequence geometry:
  * `Project/USER/src/main.c:547-582`
  * Raw trace points become `rpts0s/rpts1s` after map, blur, resample, angle, and NMS.
* Width / distance checks:
  * `Project/USER/src/main.c:653-672`
  * L-pair distance is computed between selected IPM/resampled points, not between raw seed row points.
* Side selection:
  * `Project/USER/src/main.c:308-317`
  * Ordinary mode updates `track_type` from `rpts0s_num/rpts1s_num`.
  * Cross/circle state machines may overwrite `track_type`.
* Centerline generation:
  * `Project/CODE/imgproc.c:612-635`
  * `track_leftline()` / `track_rightline()` offset the selected side boundary by `pixel_per_meter * ROAD_WIDTH / 2`.

Current project mapping:

* Seed layer:
  * `code/tracking/imgproc.cpp:214-290`
  * Currently has extra same-row seed-pair state `seed_pair_t::width`.
* Trace layer:
  * `code/tracking/mainline.cpp:64-136`
  * Already traces valid left/right seeds independently.
* Point-sequence geometry:
  * `code/tracking/mainline.cpp:271-303`
  * Builds `rpts0s/rpts1s` from trace points by perspective, blur, and resample.
* Width / distance checks:
  * `code/tracking/boundary.cpp:275-328`
  * L-pair checks use transformed/resampled boundary points.
* Side selection:
  * `code/tracking/mainline.cpp:305-388`
  * Ordinary mode chooses side from `rpts0s_num/rpts1s_num` and `track_type_keep`.
  * `code/tracking/mainline.cpp:527-551` cross IN requires farline side and farline midline.
  * `code/tracking/mainline.cpp:559-596` ring active state forces side.
* Centerline generation:
  * `code/tracking/imgproc.cpp:769-1030`
  * Single-side midline is generated by fixed `ROAD_HALF_WIDTH` normal offset.

Design implication:

* A future seed patch must be judged by whether it starts valid current-frame traces, not by whether it can produce same-row seed width.
* If seed rows differ after a multi-row missing-side search, that is not inherently invalid for trace.
* Raw seed-pair width must not become the core geometry contract.
* The first real behavior patch should be a layer-specific change, not a mixed patch touching seed, ring, cross, and control together.

Current brainstorm position:

* `width_base`: out of current MVP; keep only as reference context.
* `seed_pair_t::width` deletion: valid cleanup branch, but not by itself the cross/ring stop fix.
* Branch to converge next: seed-layer acquisition contract, because it is the earliest layer that can make clear visible boundaries never reach the trace/IPM geometry layer.

## Current Focus Correction: Basic Search Alignment

User correction:

* The current task is to solve the mismatch with the reference-style acquisition pipeline and the broken basic search.
* Observed video symptom: a visually clear left boundary enters from the left image side, not from the bottom fixed seed row; current code does not acquire it.
* After lower L points disappear, the car pauses and the farline points are also absent. This is a stable failure.
* Therefore the next branch is not `width_base`, not ring selected-side fallback, and not control-layer tolerance. It is the seed/acquisition layer that decides whether a clear boundary reaches trace.

Current project evidence:

* `code/tracking/imgproc.cpp:214-290` `find_seeds()` only searches one fixed row from `mid_position ± ROAD_HALF_WIDTH`.
* `code/tracking/imgproc.cpp:82-121` `find_left_edge()` / `find_right_edge()` are horizontal row searches. If the visible line starts above that row or only enters from the side, the fixed row may miss it.
* `code/tracking/mainline.cpp:460-489` if ordinary seed or trace fails outside `CROSS_IN`, the frame rejects before boundary/IPM geometry exists.
* `code/tracking/imgproc.cpp:475-512` `trace_single()` rejects seeds too close to the image border or too dark. A direct seed exactly on the left border is not acceptable.

Reference / comparison evidence:

* RT1064 ordinary `process_image()` (`Project/USER/src/main.c:532-545`) also uses fixed-row seeds only to start tracing; it does not persist seed width.
* RT1064 cross farline (`Project/CODE/cross.c:128-186`) shows a separate reference-aligned mechanism for current-frame fixed-column vertical seed acquisition when a line is not available from the ordinary row.
* TC264 / Front_Car `Seek_Pts_Seed()` show a lower-risk ordinary-line supplement: after fixed-row search finds only one side, scan rows above (`High - 1` down to `mini_high`) for the missing opposite side using the same horizontal row-search primitive.

Design implication for the first real behavior patch:

* Patch scope should be seed/acquisition only.
* The patch should produce current-frame seed coordinates that `trace_single()` can validate and trace.
* Do not seed exactly on the image edge; keep `trace_single()` border and brightness checks intact.
* Do not change `track_leftline()` / `track_rightline()` external offset behavior.
* Do not change cross/ring state machines or control stop gates in this patch.
* Do not introduce `width_base` in this patch.
* `seed_pair_t::width` removal can be paired only if it is needed to keep seed-layer semantics clean; it is not the behavioral fix by itself.

## Seed vs Pair Contract

Core correction:

* A seed is a current-frame start point for `trace_single()`.
* A pair is an optional same-row relationship between two seeds.
* If two seeds are not on the same row, they may fail the pair contract but can still be valid trace start points.
* Therefore "not a pair" must not be treated as "not a valid seed".

Current source support:

* `code/tracking/mainline.cpp:79-113` checks `seed_state` and valid coordinates, then calls `trace_single()` separately for left and right.
* `code/tracking/mainline.cpp:128-132` uses `seed_pair_accepted()` only to clear `rt->seeds.width`; it does not block single-side trace.
* This means the future multi-row补搜 can set `seed_state` for a missing side even if its `y` differs from the other seed, as long as `trace_single()` can validate the seed.

Design rule for multi-row補搜:

* Same-row fixed search success may still be considered a pair.
* Multi-row补搜 success should be considered "side seed found", not "same-row pair found".
* Width / pair diagnostics may be absent or invalid for mixed-row seeds.
* Downstream geometry must rely on traced/IPM/resampled point sequences.

## Candidate Patch Contract: Multi-row Missing-side Seed Search

Updated: 2026-06-05 02:59:43 +0800.

Goal:

* Fix the basic acquisition failure where a clear boundary enters from the side or starts above the fixed bottom seed row, so the current fixed-row search misses it before trace can run.
* Keep the RT1064-style layering: seed starts trace, point sequences carry geometry, side selection and midline generation stay downstream.

Scope:

* Modify only `code/tracking/imgproc.cpp::find_seeds()` and tightly related seed helpers if needed.
* Do not modify `trace_single()`, `trace_edges()`, `track_leftline()`, `track_rightline()`, `cross.cpp`, `ring.cpp`, `control.cpp`, or `drive_output.cpp` in this patch.
* Do not add `width_base`.
* Do not add logs/tests/runtime observability systems.

Mechanism:

1. Run the existing fixed-row search exactly as today on `start_row`.
2. If both sides are found on that row and same-row width is legal, keep the current same-row pair behavior.
3. If only the left side is found, scan rows upward from `start_row - 1` down to `MINI_HIGH` for the missing right side using the existing horizontal right-edge search primitive.
4. If only the right side is found, scan rows upward from `start_row - 1` down to `MINI_HIGH` for the missing left side using the existing horizontal left-edge search primitive.
5. When the missing side is found on a different row, set that side's seed coordinate and side bit in `seed_state`.
6. Do not compute or store a mixed-row seed width.
7. Let `trace_single()` decide whether the found seed is usable by checking image bounds, border margin, brightness, and vertical trace gain.

Open detail to settle before implementation:

* If both sides are missing on the fixed row, should the first patch do no补搜, or should it scan upward for both sides?

Recommendation:

* First patch should only补搜 the missing side when exactly one fixed-row side is already found.
* Reason: this matches TC264 / Front_Car most closely, keeps the search anchored to a known current-frame side, and avoids turning a fully lost bottom row into speculative two-side acquisition.

Decision:

* Accepted. First patch only补搜 the missing side when exactly one fixed-row side is already found.
* If the fixed row finds neither side, keep current failure behavior.
* This keeps the patch focused on the observed failure: one visually clear side starts above/sideward while the other side still anchors the current frame.

Expected behavior:

* A side boundary that is clear but starts above the bottom seed row can enter trace through a current-frame seed.
* Mixed-row seeds may produce no valid `seed_pair_accepted()` result, but that is acceptable because trace is side-based.
* If the补搜 seed is bad, too close to the border, too dark, or cannot climb enough vertically, `trace_single()` still rejects it and existing safety gates remain intact.

Implementation:

* `code/tracking/imgproc.cpp::find_seeds()` now keeps the existing fixed-row search first.
* If the fixed row finds only left, it scans upward from `start_row - 1` to `MINI_HIGH` for a right seed using `find_right_edge()`.
* If the fixed row finds only right, it scans upward from `start_row - 1` to `MINI_HIGH` for a left seed using `find_left_edge()`.
* Found seed coordinates keep their real `y` in `seeds->left.y` / `seeds->right.y`.
* `seeds->row` is set only when both seed `y` values match; otherwise it is `-1`, so mixed-row seeds are not treated as a same-row pair.
* No `width_base`, cross/ring/control, or midline-generation code was changed.

Validation:

* `git diff --check -- code/tracking/imgproc.cpp .trellis/tasks/06-04-cross-ring-l-loss-stop/prd.md` passed.
* `cmake --build code/build --target CMakeFiles/front_car_mainline.dir/tracking/imgproc.cpp.o -j1` passed.
* `bash code/test.sh` compiled through `tracking/imgproc.cpp.o`, `tracking/mainline.cpp.o`, and `tracking/cross.cpp.o`, then failed at the existing dependency issue: `seekfree_assistant.cpp:37:10: fatal error: vision2_core.hpp: No such file or directory`.
* `bash code/test.sh --host` failed at the same existing `vision2_core.hpp` include.

Rollback:

* Remove the upward补搜 block in `find_seeds()` and restore single-side seed row assignment to the original fixed-row `y`.
