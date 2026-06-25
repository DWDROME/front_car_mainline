# PRD: Align Midline Pipeline To AuTop Reference

Status: historical PRD plus implementation record. The current source state is
summarized in `research/current-stage-summary.md`; early "current code"
sections below are retained as historical evidence and may describe pre-refactor
code paths that no longer exist.

## User Intent

The current `front_car_mainline` midline pipeline was considered structurally poor compared with the RT1064 AuTop reference. The user wanted a deep algorithm refactor plan before implementation.

Primary direction:

- Prefer AuTop reference naming and variable flow where practical.
- Restore clear algorithm layering instead of hidden mixed responsibilities.
- Avoid patch-style fallback and avoid clever C++ structure that makes the algorithm harder to compare.
- Produce file-level function flowcharts before deciding implementation.
- Use three agents for independent research and criticism before final user decision.

## Current High-Level Finding

The biggest confirmed mismatch is not only math behavior. It is ownership location.

AuTop reference keeps `track_leftline()` / `track_rightline()` simple:

```text
left/right sampled boundary -> offset center candidate rptsc0/rptsc1
```

Then the main loop performs one shared control-midline stage:

```text
select rpts by track_type
-> compute fixed start cx/cy
-> find nearest begin_id
-> special force begin_id = 0 when needed
-> set rpts[begin_id] = cx/cy
-> resample into rptsn
-> select aim_idx and compute control error
```

Historical mismatch: the old code mixed offset, nearest-start search,
reference-point overwrite, resampling, and `midline_t` output inside
`track_leftline()` / `track_rightline()`. Current source now uses
`rpts0s/rpts1s -> rptsc0/rptsc1 -> build_rptsn() -> rt->track.mid`; see
`research/current-stage-summary.md`.

## Reference Evidence

### RT1064 files

- `Project/USER/inc/main.h`
- `Project/USER/src/main.c`
- `Project/CODE/imgproc.h`
- `Project/CODE/imgproc.c`
- Element files that modify `track_type` / point counts:
  - `Project/CODE/cross.c`
  - `Project/CODE/circle.c`
  - possibly `garage.c`, `yroad.c`, `apriltag.c` if included in a broader future pass

### RT1064 main data names

From `Project/USER/inc/main.h`:

```text
ipts0 / ipts1      raw left/right boundaries
rpts0 / rpts1      mapped left/right boundaries
rpts0b / rpts1b    blurred boundaries
rpts0s / rpts1s    resampled boundaries
rptsc0 / rptsc1    left/right candidate centerlines
rpts               selected centerline pointer
rpts_num           selected centerline count
rptsn              normalized centerline
rptsn_num          normalized centerline count
```

### RT1064 function flowcharts

#### `Project/USER/src/main.c` frame loop

```text
process_image()
-> find_corners()
-> ordinary track_type selection from rpts0s_num/rpts1s_num
-> check_garage/check_apriltag/check_cross/check_yroad/check_circle
-> run_yroad/run_cross/run_circle/run_garage
-> select rpts/rpts_num:
   if cross_type != CROSS_IN:
       track_type LEFT  -> rpts = rptsc0; rpts_num = rptsc0_num
       track_type RIGHT -> rpts = rptsc1; rpts_num = rptsc1_num
   else:
       build farline center into rpts directly
-> cx/cy = wheel reference point via mapx/mapy
-> begin_id = nearest point in selected rpts to cx/cy
-> force begin_id = 0 for garage in / CROSS_IN
-> rpts[begin_id] = cx/cy
-> resample_points(rpts + begin_id, ..., rptsn, &rptsn_num, sample_dist * pixel_per_meter)
-> aim_idx = clip(round(aim_distance / sample_dist), 0, rptsn_num - 1)
-> compute pure pursuit / PID angle
```

Line anchors:

- `main.c:302-303`: process image and corners.
- `main.c:308-317`: ordinary track_type selection.
- `main.c:344-348`: run element state machines.
- `main.c:353-373`: select candidate centerline or build cross farline center.
- `main.c:375-401`: fixed-start normalization.
- `main.c:403-430`: aim point and control error.

#### `Project/USER/src/main.c::process_image()`

```text
raw seed search on begin_y
-> findline_lefthand_adaptive / findline_righthand_adaptive into ipts0/ipts1
-> map raw ipts through mapx/mapy into rpts0/rpts1
-> blur_points into rpts0b/rpts1b
-> resample_points into rpts0s/rpts1s
-> local_angle_points + nms_angle for corners
-> track_leftline(rpts0s, ..., rptsc0)
-> track_rightline(rpts1s, ..., rptsc1)
```

Line anchors:

- `main.c:532-545`: raw start points and trace.
- `main.c:547-557`: mapx/mapy.
- `main.c:559-569`: blur and resample.
- `main.c:571-581`: local angle and NMS.
- `main.c:583-587`: candidate centerline generation.

#### `Project/CODE/imgproc.c::track_leftline()`

```text
for each sampled left boundary point i:
    dx/dy = tangent from i-approx_num to i+approx_num
    normalize tangent
    pts_out[i] = pts_in[i] + left normal * dist
```

Line anchors:

- `imgproc.c:611-621`.

#### `Project/CODE/imgproc.c::track_rightline()`

```text
for each sampled right boundary point i:
    dx/dy = tangent from i-approx_num to i+approx_num
    normalize tangent
    pts_out[i] = pts_in[i] + right normal * dist
```

Line anchors:

- `imgproc.c:624-635`.

## Current Code Evidence

### Current files involved

- `code/tracking/mainline.cpp`
- `code/tracking/imgproc.hpp`
- `code/tracking/imgproc.cpp`
- `code/types.hpp`
- `code/tuning.hpp`
- `code/tracking/cross.cpp` / `cross.hpp`
- `code/tracking/ring.cpp` / `ring.hpp`
- `code/tracking/zebra.cpp` / `zebra.hpp`
- `code/app/report.cpp`
- `code/app/assistant.cpp` / `assistant.hpp`
- `code/core/control.cpp`

### Current function flowcharts

#### `code/tracking/mainline.cpp::tracking_process_frame()`

```text
reset rt->track/seeds/traces
-> find_seeds(gray, START_HIGH, &mid_position, &seed_state, &seeds)
-> trace_edges()
-> update_search_center()
-> build_boundary_from_trace(left/right)
-> build_rpts0/build_rpts1
-> refresh_boundary_corners
-> ordinary_track_type0 = pick_track_type()
-> precompute ring_track_type0/ring_run_crop
-> element_process(rt)
-> ref = {rt->control_center_x, START_HIGH}
-> classify cross_far_frame/cross_near_frame/ring_active_frame
-> work_track_type selection
-> optional ring RUN crop
-> generate rt->track.mid directly:
   cross_far_frame -> solve_cross_mid(rt, ref)
   LEFT            -> track_leftline(..., ref, &rt->track.mid)
   RIGHT           -> track_rightline(..., ref, &rt->track.mid)
-> reject gate: min_mid_step and lookahead
-> set reject_reason/track_type/center_x/guide_error
-> zebra_process(rt, zebra_scan)
```

Line anchors:

- `mainline.cpp:480-733`.
- `mainline.cpp:593`: current `ref`.
- `mainline.cpp:678-700`: direct midline generation.
- `mainline.cpp:701-724`: reject and guide error.

#### `code/tracking/mainline.cpp::solve_cross_mid()`

```text
if cross.state != IN -> fail
-> use cross.track_type
-> validate selected farline found + L index
-> start = cross.left_l/right_l
-> call track_leftline_from_start / track_rightline_from_start
-> output rt->track.mid
```

Line anchors:

- `mainline.cpp:160-240`.

#### `code/tracking/imgproc.cpp::track_leftline()` current

```text
for each left boundary point:
    validate IPM point triple
    compute tangent
    offset into local mids[i]
    compute distance mids[i] to ref
    choose nearest begin
-> clamp ref
-> midline->pts[0] = ref
-> mids[begin] = ref
-> resample_points(mids + begin, ..., mids_sample)
-> push_mid into midline, generating dist[]
-> return midline->step
```

Line anchors:

- `imgproc.cpp:806-875`.

#### `code/tracking/imgproc.cpp::track_rightline()` current

Same as left, but right-side normal offset.

Line anchors:

- `imgproc.cpp:944-1014`.

#### `code/tracking/imgproc.cpp::*_from_start()` current

```text
for each selected farline point:
    compute offset center mids[i]
-> force mids[0] = ref
-> resample from mids[0]
-> push_mid into midline
```

Line anchors:

- `track_leftline_from_start`: `imgproc.cpp:883-937`.
- `track_rightline_from_start`: `imgproc.cpp:1021-1075`.

### Current mismatch summary

Current `track_leftline()` / `track_rightline()` are not equivalent to AuTop functions with the same names. They own four responsibilities:

1. boundary offset to centerline;
2. nearest begin search;
3. fixed reference start overwrite;
4. midline resampling and `dist[]` construction.

In AuTop, only item 1 belongs to `track_leftline()` / `track_rightline()`. Items 2-4 belong to the main control-midline stage.

## Proposed Refactor Direction

The desired target is to make function and variable ownership easier to compare with the reference.

### Naming target

Prefer these names or close equivalents:

```text
rpts0/rpts1       mapped left/right boundaries
rpts0b/rpts1b     blurred left/right boundaries
rpts0s/rpts1s     resampled left/right boundaries
rptsc0/rptsc1     candidate centerlines from left/right side
rpts/rpts_num     selected candidate centerline
rptsn/rptsn_num   normalized control centerline
begin_id          selected normalization start index
cx/cy             fixed control start point in IPM/control coordinates
aim_idx           lookahead index
```

### Candidate target file flowcharts

#### `code/tracking/imgproc.cpp` target

```text
track_leftline(pts_in, num, pts_out, approx_num, dist)
-> only offset left boundary into candidate centerline
-> no ref
-> no begin_id
-> no resample to midline_t
-> no dist[]

track_rightline(pts_in, num, pts_out, approx_num, dist)
-> only offset right boundary into candidate centerline

normalize_midline_start(rpts, rpts_num, cx, cy, force_begin_id0, midline)
-> begin_id = nearest(rpts, cx/cy) or 0 if force
-> require rpts_num - begin_id >= min step
-> rpts[begin_id] = cx/cy
-> resample_points(rpts + begin_id, ..., rptsn)
-> fill midline_t pts/dist/step
```

#### `code/tracking/mainline.cpp` target

```text
build_rpts0/build_rpts1
-> build candidate centerlines rptsc0/rptsc1 once after rpts0s/rpts1s exist
-> element_process may adjust track_type or point counts
-> select rpts/rpts_num based on work_track_type or cross farline
-> force_begin_id0 = cross_far_frame or other selected special modes
-> normalize_midline_start(rpts, rpts_num, cx, cy, force_begin_id0, &rt->track.mid)
-> common reject gate
-> common guide_error/aim_idx calculation
```

#### `code/types.hpp` target

Keep `midline_t` as runtime/control output unless deliberately renaming to reference-like `rptsn` is chosen. Avoid adding runtime fields for `rptsc0/rptsc1/rpts/rptsn` if file-static arrays in `mainline.cpp` are enough.

#### `code/app/assistant.cpp` target

No algorithm ownership. Continue displaying `rt->track.mid` projected back to raw. If `midline_t` remains the normalized control line, assistant remains correct.

#### `code/app/report.cpp` target

Report `mid_step`, `m0`, `ml`, and guide fields after normalization. If new debug fields are needed, prefer explicit `begin_id`, `aim_idx`, `rptsc0_num/rptsc1_num`, but only after user approval.

## Open Decisions For User

1. Should we keep C++ names `midline_t`, `track_result_t`, etc., while using AuTop variable names only inside `mainline.cpp`, or rename more broadly?
2. Should `track_leftline()` / `track_rightline()` signatures be made nearly identical to AuTop (`pts_in, num, pts_out, approx_num, dist`) even if that requires broad call-site edits?
3. Should we introduce file-static arrays `rptsc0/rptsc1/rptsn` in `mainline.cpp`, matching reference, or keep local stack arrays to reduce persistent state?
4. Should `rpts` be represented as a pointer like the reference, or as explicit selected pointer/count local variables?
5. Should `cx/cy` be computed from `CONTROL_CENTER_X, START_HIGH`, or should we introduce a closer reference-style fixed point derived from raw `0.78H` through IPM lookup?
6. Should `begin_id = 0` be forced only for `CROSS_IN`, or also for future garage-like modes if they exist?
7. Should ring states ever force `begin_id = 0`, or should ring always use nearest-start normalization?
8. Should the current `track_dualline()` be kept, removed, or moved out as experimental dead code?
9. Should `LOOKAHEAD_DIST` remain a pixel-distance constant, or should names move toward `aim_distance` + `sample_dist` semantics?
10. Should `guide_error` continue using angle error, or should the pure-pursuit formula be moved closer to reference in a later task?
11. Should this refactor preserve exact current numeric outputs where possible, or prioritize reference-equivalent stage ownership even if outputs shift slightly?
12. Should we add temporary report fields for `begin_id`, `aim_idx`, `rptsc0_num`, `rptsc1_num`, `rptsn_num` during migration, or avoid observability changes?
13. Should cross farline use the same `track_leftline()` + `normalize_midline_start(force_begin_id0=1)` route, removing `track_leftline_from_start()` / `track_rightline_from_start()`?
14. Should zebra scanning consume the normalized `rptsn` or its own separately selected/normalized line?
15. Should we split implementation into “rename/shape only” then “behavior correction,” or do one direct algorithm restructure commit?

## Non-Goals For This Brainstorm Task

- No source changes.
- No board upload.
- No new logging framework.
- No protocol expansion.
- No fallback line generator.
- No attempt to fix ring state machine until midline ownership is settled.

## Brainstorm Update: Preserve Local Fixes While Aligning Names

Updated: 2026-06-06 11:59:42 +0800.

User direction:

- The first cut is acceptable in principle, but it affects every later cut.
- Before implementation, all major stages must be planned.
- Recent pushed changes that are not present in RT1064 must be explicitly preserved or delayed.
- Reference names are welcome where they clarify comparison, but false renames are not acceptable.

New research records:

- `research/claude-review-flowchart.md`
- `research/claude-review-resolution.md`
- `research/non-reference-retention-plan.md`
- `research/naming-and-file-boundary-plan.md`
- `research/all-stage-refactor-plan.md`

Reviewer summary:

1. Naming and file boundary:
   - Do not add new files in the first cut.
   - Do not rename `tracking_process_frame()` to `process_image()`.
   - Do not rename `ring` to `circle` in the first cut.
   - Keep `boundary.cpp` as the current `find_corners()` equivalent owner.
   - Keep `track_leftline/rightline` names, but change their semantics to RT1064-style candidate centerline generation.

2. Local non-reference fixes:
   - Preserve missing-side upward seed search.
   - Preserve trace-validated `update_search_center()` and `width_base`.
   - Preserve element short-midline gate.
   - Preserve ring current-frame side/crop snapshot.
   - Preserve assistant red line as final control midline projection.

3. Stage plan:
   - Stage 1: implement a vertical line-output contract slice: `rpts0s/rpts1s -> rptsc0/rptsc1 -> selected rpts/rpts_num -> build_rptsn() -> rt->track.mid`.
   - Stage 2: make `mainline.cpp` order more readable after Stage 1 compiles.
   - Stage 3: review/delete cross `*_from_start` wrappers if Stage 1 does not already remove them.
   - Stage 4: decide ring owner / historical `build_opp()` now named `build_ring_opp_for_detection()` and zebra scan ownership after selected `rpts/rptsn` visibility exists.
   - Stage 5: decide `cx/cy` control origin alignment and error formula.
   - Stage 6: human-readable naming and file-boundary design.

Current recommendation:

The next implementation goal should only execute Stage 1 as a vertical slice. It must not change seed acquisition, search-center update, ring transitions, cross farline detection, control PID, assistant protocol, or file names.

## Claude Review Resolution: Candidate-First Crop Contract

Updated: 2026-06-06.

Claude review result:

- Stage 1 is conditionally accepted.
- Blocking issue B1: the previous plan conflicted on whether crop happens before candidate building or after candidate building.

User decision:

- Use the RT1064-like candidate-first flow.
- Build `rptsc0/rptsc1` once before `element_process()`.
- After `element_process()`, cross-near and ring-RUN crop must target `rptsc0_num/rptsc1_num`.
- Do not rely on the old `rpts0s_num/rpts1s_num` crop as the effective control crop after candidates have already been built.

Implication for Stage 1:

```text
ordinary:
  rpts0s/rpts1s -> rptsc0/rptsc1 -> select -> build_rptsn

cross BEGIN / same-frame BEGIN->IN:
  rptsc0/rptsc1 already built
  crop rptsc0_num/rptsc1_num by rt->track.left/right.now_step
  select ordinary_track_type0
  build_rptsn(force=0)

ring RUN:
  rptsc0/rptsc1 already built
  crop the selected candidate count by frame-start ring crop index
  build_rptsn(force=0)

CROSS_IN:
  exception: farline tail -> far candidate -> build_rptsn(force=1)
```

## Stage 2 / Stage 3 Closeout

Updated: 2026-06-06.

Completed source commits:

```text
07bec91 fix bug：对齐参考版中线生成流程
2394b60 fix bug：拆分主巡线阶段流程
```

Stage 2 result:

- `tracking_process_frame()` is now split into frame action, frame mode,
  element crop, selected midline build, final publication gate, and zebra scan.
- This was a readability / phase-boundary change in `code/tracking/mainline.cpp`.
- It did not intentionally change seed acquisition, trace logic, ring state
  transitions, cross farline detection, control/PID, assistant protocol, or file
  names.

Stage 3 review result:

- Cross farline review is closed.
- `track_leftline_from_start` and `track_rightline_from_start` no longer exist
  under `code/`.
- `CROSS_IN` farline now uses:

```text
rt->cross.left_pts / rt->cross.right_pts tail
-> track_leftline() / track_rightline()
-> far candidate
-> build_rptsn(force_begin_id0 = 1)
-> rt->track.mid
```

No source change is required for Stage 3.

Current next stage:

```text
Stage 4: ring owner / historical build_opp() now named build_ring_opp_for_detection() / zebra ownership decision.
```

Do not do naming/file-boundary source cleanup before Stage 4; source cleanup remains Stage 6
unless Stage 4 requires a targeted local cleanup.

## Stage 4 Closeout: Ring And Zebra Owner

Updated: 2026-06-06.

Stage 4 result:

```text
Closed as decision/review-only.
No source change is required.
```

Resume note:

```text
This section is a historical Stage 4 closeout.
Current source names after later cleanup:
  snapshot_ring_frame_start_action()
  apply_frame_start_element_crop()
  frame_action_t::base_candidates_ready
  build_zebra_scan_midline()
  build_ring_opp_for_detection()
```

Decision:

```text
Use option C.
Keep ring.cpp::build_ring_opp_for_detection() as ring detection / state-continuity internals only.
Do not make ring-edited boundary_t a current-frame control-midline input.
Do not delete the ring opposite-boundary detection helper in this stage.
```

Current code evidence:

- `code/tracking/mainline.cpp` builds `rptsc0/rptsc1` before
  `element_process()`.
- `snapshot_ring_frame_start_action()` captures frame-start ring side/crop before
  `element_process()`.
- `apply_frame_start_element_crop()` only clips `rptsc0_num/rptsc1_num`.
- `build_selected_midline()` consumes `rptsc0/rptsc1` or cross farline; it does
  not consume ring-edited `boundary_t`.
- `ring.cpp::build_ring_opp_for_detection()` can edit `boundary_t` during
  `RING_STATE_IN`, but that happens after current-frame candidates already exist.

Reference alignment:

- RT1064 `circle.c` does not synthesize an opposite boundary.
- RT1064 circle stages set `track_type`, update state counters, and in RUN crop
  `rpts*s_num/rptsc*_num`.
- RT1064 final main loop selects `rptsc0/rptsc1` by `track_type`.

Zebra decision:

- Current `build_zebra_scan_midline()` already selects from existing `rptsc0/rptsc1`
  candidates and calls `build_rptsn()`.
- `zebra_process()` only reads `midline_t` points and scans raw pixels.
- No zebra source change is needed in Stage 4.

Next stage:

```text
Stage 5: control origin / error formula review.
```

Before any future ring behavior change, collect real ring-sequence telemetry:

```text
ring.kind
ring.state
selected track_type
rptsc0_num / rptsc1_num
mid.step
reject_reason
guide_error
```

## Stage 5 Closeout: Control Origin And Error Formula

Updated: 2026-06-06.

Stage 5 result:

```text
Patch 5A was later implemented because the original user question required
RT1064-style fixed midline start normalization.
Patch 5B is now implemented because the original user question also required
RT1064-style guide_error calculation, not only candidate ownership.
```

Previous code:

```text
ref = {rt->control_center_x, START_HIGH}
default ref = {86,116}
guide_error = atan2(mid[look].x - ref.x, ref.y - mid[look].y)
```

RT1064 reference:

```text
cx = mapx[(int)(H * 0.78f)][W / 2]
cy = mapy[(int)(H * 0.78f)][W / 2]
error = -atan2f(dx, cy - y + 0.2 * pixel_per_meter)
```

Measured current-table probe:

```text
raw=(80,93) -> ipm=(88.52225,108.59464)
current ref=(86,116)
```

Decision:

```text
Patch 5A implements control origin as a separate concept.
Do not change START_HIGH; it is still seed/search row and zebra bottom scan row.
Do not combine control-origin change with guide_error formula change.
```

Recommended future split:

```text
Patch 5A implemented:
  control origin only
  compute RT-style projected raw wheel point via perspective_lookup_raw_to_ipm()
  fallback to {control_center_x, START_HIGH}

Patch 5B implemented:
  guide_error formula only
  use RT-style negative atan2 sign
  add forward bias equivalent to 0.2 * pixel_per_meter
  keep LOOKAHEAD_DIST unchanged
  validate target_yaw sign after outer_sign on car
```

Patch 5A current behavior:

```text
if rt->has_matrix:
  ref = perspective_lookup_raw_to_ipm(RAW_W / 2, int(RAW_H * 0.78))
else:
  ref = {rt->control_center_x, START_HIGH}
```

Current table probe:

```text
raw=(80,93) -> ipm=(88.52225,108.59464) -> rounded ref=(89,109)
```

Patch 5B current behavior:

```text
dx = mid[look].x - ref.x
dy = ref.y - mid[look].y + k_error_forward_bias
guide_error = -atan2(dx, dy)

k_error_forward_bias = ROAD_HALF_WIDTH * 8 / 9
```

Reason for `8 / 9`:

```text
RT1064 uses 0.2 * pixel_per_meter.
Current ROAD_HALF_WIDTH is the measured half road width, about 0.225m.
0.2 / 0.225 = 8 / 9.
```

Remaining non-code validation:

```text
Check real-car steering direction and magnitude after the sign change.
If the car steers away from the line, adjust front_car_mainline.yaml outer_sign.
If it steers too aggressively, tune outer_kp / LOOKAHEAD_DIST; do not reopen
the midline ownership contract first.
```

Validation:

```text
bash code/test.sh --host -> [100%] Built target front_car_mainline
```

Next formal stage:

```text
Stage 6: human-readable naming / file-boundary design.
```

## Stage 6 Reframe: Human-Readable Architecture

Updated: 2026-06-06 14:27:11 +0800.

Stage 6 is no longer treated as optional cleanup.

It is the most human-facing stage of this refactor: it decides the vocabulary,
file boundaries, and readable flow contract that later ring/cross/control work
will rely on.

New research entry:

```text
research/stage6-human-readable-architecture-plan.md
research/stage6-source-decision-package.md
```

Why this matters:

- Stage 1 and Stage 2 made the midline ownership more reference-aligned.
- The code now works through `rpts0s/rpts1s -> rptsc0/rptsc1 ->
  build_rptsn() -> rt->track.mid`.
- That chain is good for RT1064 comparison, but not automatically easy for a
  new human maintainer.
- A sloppy Stage 6 source cleanup would make later ring/control debugging worse
  by mixing behavior, naming, and file movement in one diff.

Three-agent review produced a real decision point:

```text
Naming review:
  plain role names improve human readability.

Risk review:
  RT1064-style names preserve reference comparison and reduce churn.

File-boundary review:
  keep files physically stable until vocabulary and behavior are stable.
```

Current Stage 6 decision options:

```text
Option A:
  keep RT1064-style names:
    rpts0s / rpts1s / rptsc0 / rptsc1 / build_rptsn()
  add stronger glossary and flow comments.

Option B:
  rename private mainline arrays to plain role names:
    left_sampled_boundary / right_sampled_boundary
    left_mid_candidate / right_mid_candidate
  keep low-level primitive names:
    track_leftline()
    track_rightline()
    build_rptsn()

Option C:
  also rename build_rptsn() to a plain final-builder name.
  Not recommended now because Stage 5 control-origin/error formula is not
  settled.
```

Stage 6 source gate:

```text
Do not change source until Option A/B/C is chosen.
Do not combine naming/file work with seed, ring, cross, control-origin,
guide_error, PID, assistant protocol, or report behavior changes.
Do not physically split mainline.cpp or imgproc.cpp in the first Stage 6 source
pass unless the user explicitly selects that larger churn.
```

Immediate recommendation:

```text
Use Stage 6 as a design-decision task first.
Ask the user to choose Option A or B.
Only after that, open a separate implementation goal for the selected source
cleanup.
```

Concrete implementation packages are now defined:

```text
Option A:
  comment/glossary only
  touch only mainline.cpp, imgproc.hpp, types.hpp

Option B:
  rename private mainline arrays/counts to plain role names
  keep public APIs and RT1064 primitive names stable
  touch only mainline.cpp, imgproc.hpp, types.hpp
```

Both packages explicitly reject behavior changes, file splits, public runtime
field renames, assistant protocol changes, report data changes, and control
changes.

## Stage 6 Closeout: Option A

Updated: 2026-06-06 14:39:48 +0800.

User selected:

```text
A
```

Implemented source cleanup:

```text
Keep RT1064-style names.
Add human-readable glossary and flow comments only.
```

Touched source files:

```text
code/tracking/mainline.cpp
code/tracking/imgproc.hpp
code/types.hpp
```

What changed:

- `mainline.cpp`: added RT1064 point-list glossary and an explicit
  `tracking_process_frame()` pipeline comment.
- `imgproc.hpp`: clarified `build_rptsn()` as the selected-candidate normalizer
  from `rptsc0/rptsc1` or CROSS_IN farline candidate into `midline_t`.
- `types.hpp`: clarified coordinate and center ownership for
  `original_pts/now_pts/work_pts`, `track.center_x`, `control_center_x`, and
  `mid_position`.

What did not change:

```text
No symbol rename.
No API change.
No file split.
No seed/trace behavior change.
No ring/cross/zebra state change.
No control-origin or guide_error change.
No assistant/report/control behavior change.
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
Option B private mainline array rename.
Option C build_rptsn() rename.
Physical file split.
Public runtime/result field rename.
```

## Stage 7 Brainstorm: All Tracking File Contract Straightening

Updated: 2026-06-06 15:56:45 +0800.

User correction:

```text
Stages 1-6 only touched several files and solved the midline owner chain.
That does not mean the whole tracking package is successful.
All related files must be straightened under one contract.
```

Stage 7 scope:

```text
code/tracking/mainline.cpp
code/tracking/imgproc.cpp / imgproc.hpp
code/tracking/boundary.cpp / boundary.hpp
code/tracking/cross.cpp / cross.hpp
code/tracking/ring.cpp / ring.hpp
code/tracking/element.cpp / element.hpp
code/tracking/zebra.cpp / zebra.hpp
code/app/assistant.cpp / assistant.hpp
code/app/report.cpp
code/app/runners.cpp
code/core/control.cpp / control.hpp
code/types.hpp
code/tuning.hpp
```

Accepted global contract:

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

New research entry:

```text
research/stage7-all-tracking-file-contract-plan.md
```

Stage 7 patch order:

```text
Patch 7A: Seed / Trace / Report Semantics
Patch 7B: Cross Entry State Machine
Patch 7C: Ring Ownership And State Contract
Patch 7D: Boundary Corner Semantics
Patch 7E: Observability Cleanup
```

Recommended next implementation:

```text
Patch 7A first.
```

Reason:

```text
Patch 7A is the lowest-risk cleanup:
- removes misleading `seed_pair_t::width`
- makes seed explicitly mean trace start point
- stops report from presenting seed pair width as central geometry truth
- preserves seed search, trace, cross, ring, zebra, assistant protocol, and control
```

Explicit non-goals for Patch 7A:

```text
Do not change seed search algorithm.
Do not change trace border margin.
Do not change cross/ring state machines.
Do not change assistant binary protocol.
Do not change control/PID.
Do not commit Trellis or local AI workflow files.
```

## Stage 7 Brainstorm Reset: Do Not Rush Algorithm Behavior

Updated: 2026-06-06 16:44:14 +0800.

User correction:

```text
This is an intelligent-car competition codebase. Every variable assignment can
change behavior qualitatively. Token budget is not a reason to rush or add
fallbacks. The goal is precise, repeated, mechanism-level convergence:
make the code easier for humans to read, closer to the AuTop reference, more
direct, more correct, and with fewer ad-hoc fallbacks or noisy helper layers.
```

Current source state:

```text
The current working tree contains an experimental Stage 7 implementation diff.
It must not be treated as accepted or ready to commit.
```

Important review result:

```text
Patch 7A seed/report cleanup is low-risk and aligns with the plan.

Patch 7B weak cross entry is behavior-changing and is not RT1064's original
strict double-L contract. Even after tightening, it remains a platform-specific
behavior patch. It must pass a separate decision gate before implementation.
```

Stage 7 implementation gate is now:

1. Patch 7A may proceed as the first real implementation because it removes a
   misleading state field and does not change seed search / trace / elements /
   control.
2. Patch 7B must not be bundled with 7A.
3. Patch 7B requires replay or real-frame evidence before being accepted:
   - the failure frame is a turning cross entry,
   - strict double-L fails before `CROSS_IN`,
   - farline has a real far L, not only a visible line,
   - the proposed rule does not steal ring frames,
   - state does not get stuck in `CROSS_STATE_BEGIN` or `CROSS_STATE_IN`.
4. Patch 7C/7D/7E can be planned, but any behavior changes must be separated
   from observability-only changes.

Revised open decision:

```text
Q7B-reset-1: Should the next source implementation be reset to pure Patch 7A
only, leaving all cross/ring/boundary behavior changes for replay-backed
separate tasks?

Recommended: yes. This matches the user's principle: no bundled fallback, no
behavior patch without mechanism-level evidence, and easier human review.
```

Suggested next goal prompt:

```text
Goal: Implement Patch 7A from
.trellis/tasks/06-06-align-midline-pipeline-to-autop/research/stage7-all-tracking-file-contract-plan.md.

Only change seed/report semantics:
- remove seed_pair_t::width
- recompute same-row seed span inside seed_pair_accepted() / report as needed
- remove trace_edges() mutation of rt->seeds.width
- rename or clarify report-only seed IPM geometry diagnostics
- keep seed search, trace, cross, ring, zebra, assistant protocol, and control unchanged

Validate with:
- rg -n "seed_width|\\.width|seeds.width|seed_pair_t" code
- git diff --check -- code/types.hpp code/tracking/imgproc.cpp code/tracking/imgproc.hpp code/tracking/mainline.cpp code/app/report.cpp
- bash code/test.sh --host

Do not commit Trellis or local AI workflow files.
```
