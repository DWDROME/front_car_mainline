# Current Stage Summary

Updated: 2026-06-06 17:37:30 +0800.

Purpose: compressed entry point for the midline-pipeline refactor task. The
original research files remain as evidence and detail. This file only records
the current state, next review target, and cleanup boundary.

## Current Source State

Completed and pushed:

```text
07bec91 fix bug：对齐参考版中线生成流程
2394b60 fix bug：拆分主巡线阶段流程
```

The current code-level contract is:

```text
seed / trace
-> rpts0s / rpts1s
-> rptsc0 / rptsc1
-> element side and crop action
-> selected candidate
-> build_rptsn()
-> rt->track.mid
-> guide_error / control / assistant red line
```

Special path:

```text
CROSS_IN
-> rt->cross.left_pts / rt->cross.right_pts farline tail
-> track_leftline() / track_rightline() far candidate
-> build_rptsn(force_begin_id0 = 1)
-> rt->track.mid
```

## Stage Status

| Stage | Status | Code state |
| --- | --- | --- |
| Stage 0: freeze contracts | Done | Known non-reference fixes preserved by later diffs. |
| Stage 1: line-output contract | Done | `track_leftline/rightline` build 1:1 candidates; `build_rptsn()` owns final normalized control midline. |
| Stage 2: readable mainline flow | Done | `tracking_process_frame()` is split into frame action, mode classification, crop, selected midline, final gate, and zebra scan helpers. |
| Stage 3: Cross IN review | Done | Review passed; old `*_from_start` wrappers are gone, and CROSS_IN farline now goes through candidate generation plus `build_rptsn(force_begin_id0 = 1)`. |
| Stage 4: ring / zebra owner decision | Done | Decision C: keep opposite-boundary synthesis as ring detection/state-continuity internals only; current source name is `build_ring_opp_for_detection()`; do not wire ring-edited `boundary_t` into current-frame control; zebra owner is settled. |
| Stage 5: control origin / error formula | Done | Patch 5A projects the RT1064-style raw wheel point into IPM for the control origin when `has_matrix` is true. Patch 5B changes `guide_error` to RT1064-style `-atan2(dx, dy + forward_bias)`. |
| Stage 6: human-readable naming / file-boundary design | Done | User chose Option A. RT1064-style names are kept; source cleanup is limited to glossary / flow / coordinate comments in `mainline.cpp`, `imgproc.hpp`, and `types.hpp`. |
| Stage 7: all tracking file contract straightening | Implemented / evidence-gated | Seed/report, boundary L semantics, strict cross entry, ring detection-only ownership, and report/replay observability are now explicit. Weak cross entry and ring behavior changes remain blocked on replay / real-car evidence. |

## Step 3 Result

Step 3 is closed as review-only.

Confirmed:

```text
1. CROSS_IN still continues when ordinary seed or trace fails.
2. CROSS_IN farline path builds candidate points through track_leftline/rightline.
3. CROSS_IN calls build_rptsn(..., force_begin_id0 = 1, ...).
4. Old track_leftline_from_start / track_rightline_from_start declarations and definitions are gone.
5. No old wrapper call remains in code.
```

No source change is needed for Step 3.

## Step 3 Scope Record

Step 3 should be a confirmation review, not a broad rewrite.

Check only:

```text
1. CROSS_IN still continues when ordinary seed or trace fails.
2. CROSS_IN farline path builds candidate points through track_leftline/rightline.
3. CROSS_IN calls build_rptsn(..., force_begin_id0 = 1, ...).
4. Old track_leftline_from_start / track_rightline_from_start declarations and definitions are gone.
5. No old wrapper call remains in code.
```

Do not change during Step 3 unless the review finds a concrete defect:

```text
seed acquisition
trace logic
update_search_center() placement
ring state transitions
cross farline detection in cross.cpp
control / PID
assistant protocol
file names
```

## Cleanup Decision

Do a light documentation cleanup now:

```text
current-stage-summary.md is the new entry point.
Keep the original research files as detailed evidence.
Do not delete or rewrite them during Step 3.
```

Do not do source cleanup before Step 3:

```text
helper placement
function naming
file splitting
optional variable renames
comment polishing
```

Reason: Stage 4 may still change ring/zebra ownership. Cleaning source before
that decision risks creating churn that must be edited again.

## Step 4 Result

Step 4 is closed as decision/review-only.

Confirmed:

```text
1. Current rptsc0/rptsc1 candidates are built before element_process().
2. ring_process() may edit boundary_t via the internal opposite-boundary helper,
   currently named `build_ring_opp_for_detection()`, but mainline does not
   rebuild rptsc0/rptsc1 after that edit.
3. Current-frame control consumes the pre-element rptsc0/rptsc1 plus frame-start
   ring side/crop action.
4. RT1064 circle.c does not synthesize an opposite boundary; it sets track_type
   and crops rpts*s_num/rptsc*_num.
5. Current zebra path already consumes rptsc0/rptsc1 through build_rptsn(), and
   zebra_process() only reads a normalized scan midline.
```

Decision:

```text
Keep opposite-boundary synthesis for ring detection/state continuity only.
Do not wire `build_ring_opp_for_detection()` into current-frame control.
Do not delete it without real ring-sequence evidence.
No source change is needed for Step 4.
```

Next:

```text
Stage 5: control origin / error formula review.
```

## Step 5 Result

Step 5 is now implemented.

Confirmed:

```text
1. Previous control origin was ref = {rt->control_center_x, START_HIGH}.
2. Default previous ref was {86,116}.
3. RT1064-style raw wheel point raw=(80,93) maps through current IPM table to
   about {88.52,108.59}.
4. Previous guide_error used atan2(dx, dy) without RT1064 negative sign or
   forward bias.
5. Control consumes guide_error through outer_sign/outer_kp, so formula changes
   are control behavior changes.
```

Decision:

```text
Patch 5A is implemented:
  if rt->has_matrix:
    ref = perspective_lookup_raw_to_ipm(RAW_W / 2, int(RAW_H * 0.78))
  else:
    ref = {rt->control_center_x, START_HIGH}

Patch 5B is implemented:
  dx = mid[look].x - ref.x
  dy = ref.y - mid[look].y + ROAD_HALF_WIDTH * 8 / 9
  guide_error = -atan2(dx, dy)

Do not change START_HIGH.
Do not change LOOKAHEAD_DIST in this patch.
Real-car sign/magnitude validation remains required through outer_sign/outer_kp.
```

Validation:

```text
raw=(80,93) -> ipm=(88.52225,108.59464) -> rounded ref=(89,109)
bash code/test.sh --host -> [100%] Built target front_car_mainline
```

Next action is not another midline-owner change. It is real-car validation:
if steering direction is inverted, change `front_car_mainline.yaml:outer_sign`;
if magnitude is wrong, tune `outer_kp` / `LOOKAHEAD_DIST`.

## Step 6 Reframing

Step 6 is not optional source cleanup.

It is the stage that decides how humans will read and maintain the tracking
pipeline after Stage 1/2. The main decision is not "rename a few things"; it is
which vocabulary should be stable for future work:

```text
RT1064-style names:
  rpts0s / rpts1s / rptsc0 / rptsc1 / rptsn / build_rptsn()

Plain role names:
  left_sampled_boundary / right_sampled_boundary
  left_mid_candidate / right_mid_candidate
  build_control_midline()
```

Three-agent review found a real disagreement:

```text
Naming review:
  plain role names are easier for new maintainers.

Risk review:
  reference-style names preserve direct RT1064 comparison and avoid churn.

File-boundary review:
  do not physically split files before vocabulary and behavior are stable.
```

Current recommended Stage 6 action:

```text
Read research/stage6-human-readable-architecture-plan.md.
Choose Option A or B before any source cleanup:

Option A:
  keep RT1064-style names and add stronger glossary / flow comments.

Option B:
  rename private mainline arrays to plain role names, but keep low-level
  RT1064 primitive names.
```

Not recommended as immediate Stage 6 source work:

```text
rename build_rptsn()
split mainline.cpp
split imgproc.cpp
rename runtime_t / track_result_t fields
change ring/cross/control behavior
```

## Step 6 Result

Step 6 is closed with Option A.

Confirmed:

```text
1. RT1064-style names remain:
   rpts0s / rpts1s / rptsc0 / rptsc1 / build_rptsn()
2. Source cleanup is comments only.
3. No symbol rename, API change, file split, or behavior change was made.
4. `mainline.cpp` now has a point-list glossary and explicit current-frame
   pipeline comment.
5. `imgproc.hpp` now documents `build_rptsn()` as the selected-candidate
   normalizer.
6. `types.hpp` now separates raw/display boundary points, element/work points,
   published control midline start, control fallback x, and next-frame seed
   search center.
```

Validation:

```bash
git diff --check -- code/tracking/mainline.cpp code/tracking/imgproc.hpp code/types.hpp
bash code/test.sh --host
```

Result:

```text
[100%] Built target front_car_mainline
```

Deferred:

```text
Option B private mainline renames
Option C build_rptsn() rename
physical file split
public runtime_t / track_result_t field rename
```

## Useful Evidence Files

Use these when deeper context is needed:

```text
research/all-stage-refactor-plan.md
research/claude-review-resolution.md
research/stage2-mainline-flow-plan.md
research/stage6-human-readable-architecture-plan.md
research/stage6-source-decision-package.md
research/stage6-option-a-closeout.md
research/patch5a-control-origin-closeout.md
research/file-flow-blueprint.md
research/non-reference-retention-plan.md
```

Use the current source as authority for implementation facts:

```text
code/tracking/mainline.cpp
code/tracking/imgproc.cpp
code/tracking/imgproc.hpp
code/tracking/boundary.cpp
code/tracking/cross.cpp
code/tracking/ring.cpp
code/app/report.cpp
code/app/runners.cpp
```

## Step 7 Result

Step 7 contract cleanup is implemented, with behavior changes still gated by
replay / real-car evidence.

The accepted global contract is:

```text
imgproc     owns seed, trace, point-list primitives, and low-level geometry helpers.
boundary    owns boundary point interpretation and corner/straight geometry.
cross       owns cross state, farline points, and cross track_type; it does not own final midline.
ring        owns ring state and detection/state-continuity boundary edits; it does not own final midline.
element     owns element priority and state-machine dispatch only.
mainline    owns frame-start element action snapshots, selected candidate -> rt->track.mid, and guide_error.
zebra       consumes a scan midline and raw image; it does not define control midline.
assistant   displays already-published runtime state.
report      diagnoses already-published runtime state; it does not define algorithm gates.
control     consumes guide_error and element stop states; it does not reinterpret vision geometry.
```

Current Stage 7 plan file:

```text
research/stage7-all-tracking-file-contract-plan.md
```

Implemented source contract:

```text
1. `seed_pair_t::width` is removed.
2. `seed_pair_accepted()` recomputes same-row seed span on demand.
3. Reports use `seed_pair_span` and `seed_ipm_pair_diag`; seed remains a trace
   start, not a tracking validity gate.
4. `boundary_t::l_found` / `l_ok` / `l_pair_ok` now have separate meanings:
   - l_found: boundary geometry scan saw a single-side L candidate.
   - l_ok: accepted front-segment single-side L for ring/zebra/crop consumers.
   - l_pair_ok: strict double-L pair passed; cross entry consumes this.
5. `cross.cpp` keeps strict double-L as the only implemented entry path;
   `strict_double_l_ok()` consumes only `l_pair_ok`.
6. The ring opposite-boundary helper is named `build_ring_opp_for_detection()` and
   remains an internal detection/state-continuity helper.
7. Mainline now uses explicit frame-action names:
   `base_candidates_ready`, `snapshot_ring_frame_start_action()`, and
   `ring_frame_start_crop_*`; ring edits do not rebuild current-frame candidates.
8. `zebra_process()` still only consumes a scan midline; mainline owns scan
   midline construction via `build_zebra_scan_midline()` from current
   rptsc0/rptsc1 candidates.
9. `report.cpp` and `runners.cpp` now expose only validation-relevant fields:
   single-side L, strict pair_ok/state/width, cross farline, ring/cross/zebra
   state, midline step, guide_error, reject_reason.
```

Validation:

Resume note: the grep needles below use the current post-Stage-7 names where a
current symbol exists. Historical names such as `build_opp()` are only searched
as stale-code detectors, not as functions to resume from.

```text
rg -n "normal_ok|ring_run_crop|snapshot_ring_action|apply_element_crop|build_zebra_mid|pair_check_inputs_ready|left->l_ok && right->l_ok|left\\.l_ok && right\\.l_ok|build_opp\\(" code
  -> no matches

rg -n "l_pair_base_pt|l_pair_open_pt|seed_width|seeds\\.width|IPM_GEOMETRY|build_opp\\(" code
  -> no matches

rg -n "l_pair_base_pt|l_pair_open_pt|build_opp|seed_width|seeds\\.width|IPM_GEOMETRY|left->l_ok && right->l_ok|left\\.l_ok && right\\.l_ok" code
  -> no stale code matches except boundary.cpp doing pair validation before writing l_pair_ok.

rg -n "build_ring_opp_for_detection|snapshot_ring_frame_start_action|apply_frame_start_element_crop|base_candidates_ready|build_zebra_scan_midline" code/tracking
  -> current source anchors present

git diff --check -- changed source files
  -> passed

bash code/test.sh --host
  -> [100%] Built target front_car_mainline
```

Replay evidence:

```text
No valid local replay evidence was produced in this pass. The repository only
contains documentation screenshots at 1270x684 and 1085x390, while
device_load_gray() requires exact RAW_W x RAW_H input.
```

Remaining evidence-gated work:

```text
Do not add weak cross entry until cross-entry replay / real-car logs show why
strict double-L fails with the new pair telemetry.

Do not change ring thresholds or remove the detection helper until ring replay /
real-car logs show whether the failure is state stuck, wrong side/crop,
too-short selected candidate, or final midline reject.

Reconfirm zebra only after future cross/ring crop semantics change.
```
