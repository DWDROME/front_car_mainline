# All-Stage Refactor Plan

Updated: 2026-06-06 11:59:42 +0800.

Scope: brainstorm only. No source implementation in this task.

## Goal

Plan every major "knife" before the first source edit, because the first midline pipeline cut defines the data contract for cross, ring, zebra, assistant display, and control.

## Target Architecture In One Line

```text
seed/trace -> rpts0s/rpts1s -> rptsc0/rptsc1 -> element side/crop action -> selected rpts/rpts_num -> build_rptsn() -> rt->track.mid -> guide_error/control/display
```

Exception: `CROSS_IN` does not select from ordinary `rptsc0/rptsc1`. It selects a farline tail from `rt->cross.left_pts/right_pts`, builds a far candidate with `track_leftline/rightline`, then calls `build_rptsn(force_begin_id0=1)`.

This aligns with RT1064:

```text
process_image()
  -> rpts0s/rpts1s
  -> rptsc0/rptsc1
run_cross/run_circle()
  -> track_type and point-count crop
main loop
  -> select rpts/rpts_num
  -> begin_id/cx/cy
  -> rptsn
  -> aim/error
```

## Stage 0: Freeze Current Contracts

Purpose: prevent accidental deletion of known fixes.

No source edits. Use as checklist before Stage 1.

Must preserve:

```text
find_seeds() missing-side upward search
trace_edges() clears failed side before update_search_center()
update_search_center() after trace success
width_base normal-frame update only
element short-midline gate
ring current-frame side/crop snapshot
assistant red line = rt->track.mid projected to raw
```

Abort Stage 1 if the planned diff touches seed acquisition, ring state transitions, PID/control, assistant protocol, or cross farline detection.

## Stage 1: Vertical Slice For Line-Output Contract

Files:

```text
code/tracking/imgproc.hpp
code/tracking/imgproc.cpp
code/tracking/mainline.cpp
```

Change:

```text
track_leftline/rightline:
  before: side boundary -> offset -> nearest begin -> cx/cy overwrite -> resample -> midline_t
  after : side boundary -> offset -> rptsc candidate only

build_rptsn:
  selected candidate -> begin_id -> cx/cy overwrite -> resample -> midline_t
```

This stage must be a vertical slice, not a detached function-signature edit.

It must introduce and consume the full line-output contract in one compiled change:

```text
rpts0s/rpts1s -> rptsc0/rptsc1 -> selected rpts/rpts_num -> build_rptsn() -> rt->track.mid
```

Reason: if `track_leftline/rightline` are split without wiring selected `rpts/rptsn` in `mainline.cpp`, the project temporarily has no clear owner for normalization, cross force-begin behavior, ring crop, and zebra scan.

Required implementation shape:

```cpp
int track_leftline(const double pts_in[POINT_MAX][2],
                   int num,
                   double pts_out[POINT_MAX][2],
                   int approx_num,
                   double dist);

int track_rightline(const double pts_in[POINT_MAX][2],
                    int num,
                    double pts_out[POINT_MAX][2],
                    int approx_num,
                    double dist);

int build_rptsn(const double rpts[POINT_MAX][2],
                int rpts_num,
                int cx,
                int cy,
                int force_begin_id0,
                midline_t *midline);
```

Recommended local arrays in `mainline.cpp`:

```text
rptsc0/rptsc1/rptsn
rptsc0_num/rptsc1_num/rptsn_num
const double (*rpts)[2]
int rpts_num
```

Path handling:

```text
ordinary:
  rpts0s/rpts1s -> rptsc0/rptsc1 -> select -> build_rptsn(force=0)

cross BEGIN / same-frame BEGIN->IN:
  build rptsc0/rptsc1 before element_process
  after element_process, crop rptsc0_num/rptsc1_num by rt->track.left/right.now_step
  do not rely on cropped rpts0s_num/rpts1s_num after rptsc has already been built
  select ordinary_track_type0
  build_rptsn(force=0)

cross IN:
  use existing farline points after far L index
  track_leftline/rightline into a far candidate
  build_rptsn(force=1)

ring:
  use frame-start action side/crop
  build rptsc0/rptsc1 before element_process
  for RUN crop, crop rptsc0_num/rptsc1_num by the frame-start ring crop index
  do not leave the old rpts0s_num/rpts1s_num crop as the effective control crop
  build_rptsn(force=0)

zebra scan:
  rebuild local candidate from opposite side
  build_rptsn(force=0) into local zebra_mid
```

Important details:

```text
Do not use candidate centerline directly for guide_error.
guide_error must read normalized rt->track.mid.
rt->track.mid.pts[0] must remain cx/cy.
rt->track.mid.dist[] must remain cumulative distance from pts[0].
CROSS_IN must preserve force begin_id=0.
track_leftline/rightline candidate output must be 1:1 with input sampled side points.
Resampling into the final control line belongs only to build_rptsn().
Because candidates are built before element_process, cross-near and ring-RUN crop must change candidate counts: rptsc0_num/rptsc1_num.
```

Decision:

If Stage 1 fully migrates `solve_cross_mid()` to `build_rptsn(force=1)`, delete `track_leftline_from_start/rightline_from_start` in the same diff. If not fully migrated, keep them temporarily. Do not leave both paths long term.

Validation:

```text
git diff --check -- code/tracking/imgproc.hpp code/tracking/imgproc.cpp code/tracking/mainline.cpp
bash code/test.sh --host
manual review: all track_leftline/rightline call sites migrated
manual review: no changes in seed/ring/cross detection/control/assistant
```

## Stage 2: Make Mainline Flow More Readable

Files:

```text
code/tracking/mainline.cpp
```

Purpose: after Stage 1 compiles and behavior is still equivalent, simplify `tracking_process_frame()` into named phases.

Target local flow:

```text
find_frame_seeds
trace_frame_edges
build_frame_boundaries
build_candidate_centerlines
snapshot_element_action
element_process
apply_element_crop
select_rpts
build_rptsn
apply_final_gate
calc_aim_error
zebra_process
```

This is not necessarily new functions for every line. The key is the visible sequence.

Allowed naming cleanup:

```text
lookahead_error -> calc_aim_error (optional)
ring_track_type0/ring_run_crop_* -> local frame action struct or flat variables
```

Not allowed:

```text
changing seed thresholds
changing ring transition conditions
changing control output
moving update_search_center before trace filtering
```

Validation:

```text
bash code/test.sh --host
line-level review of frame order
compare final source order against RT1064 main.c:302-430
```

## Stage 3: Cross IN Review

Files:

```text
code/tracking/mainline.cpp
possibly code/tracking/imgproc.hpp/.cpp only if Stage 1 left wrappers
```

Purpose: verify cross farline path is not a separate final-midline generator.

Target:

```text
cross.cpp still owns farline detection and far L index
mainline.cpp selects farline tail after L index
track_leftline/rightline builds far candidate
build_rptsn(force_begin_id0=1) normalizes final midline
```

Stage 1 should already complete this if feasible. If Stage 1 could not safely delete the wrappers, Stage 3 becomes the forced cleanup point.

Not allowed:

```text
rewriting build_cross_farline()
changing far L angle thresholds
changing CROSS_IN exit rules
```

Validation:

```text
rg "track_leftline_from_start|track_rightline_from_start" code
bash code/test.sh --host
manual sequence review for same-frame BEGIN->IN: nearline still used until next frame
```

## Stage 4: Ring And Zebra Owner Decision

Files:

```text
code/tracking/ring.cpp
code/tracking/mainline.cpp
```

This is the first stage that may change ring/zebra behavior. Do not combine behavior changes with Stage 1.

Problem:

Current ring has `build_opp()` and edits `boundary_t`; RT1064 circle only sets `track_type` and crops `rpts*s_num/rptsc*_num`.

Current zebra scan also has ownership debt: `build_zebra_mid()` in `mainline.cpp` currently rebuilds a scan midline from side boundaries. Once Stage 1 introduces `rptsc0/rptsc1`, zebra should be reviewed to avoid a temporary duplicate centerline route becoming permanent.

Decision options:

```text
A. Keep build_opp as project-specific ring-IN aid.
   Then make its ownership explicit: ring edits boundary, mainline rebuilds rpts/rptsc from that boundary before selecting control line.

B. Remove build_opp and align ring to RT1064:
   ring only sets side/crop; no synthetic opposite boundary.

C. Hybrid:
   build_opp only for detection/corner continuity, not control selected line.
```

Current recommendation before real ring-frame evidence:

```text
Stage 4 starts as review, not immediate code.
Ring review target: C, `build_opp()` may be detection/corner continuity only, not necessarily selected control line.
Zebra review target: scan from the appropriate candidate/normalized line without duplicating centerline ownership.
```

Reason:

The user's symptom "recognized ring but did not move" can be caused by selected side, state timing, candidate count, or final gate. Stage 1/2 make these visible. Removing `build_opp()` before that may hide the actual issue.

Validation:

```text
assistant red control line during ring
report fields or temporary debug: ring.kind/state, selected track_type, rpts_num, rptsn_num, mid_ok, reject_reason
real ring sequence review
```

## Stage 5: `cx/cy` Control Start Alignment And Error Formula

Files:

```text
code/tracking/mainline.cpp
code/tracking/perspective.cpp/.hpp if helper needed
possibly code/tuning.hpp
```

Current:

```text
point_t ref = {rt->control_center_x, START_HIGH}
```

RT1064:

```text
cx = mapx[(int)(MT9V03X_CSI_H * 0.78f)][MT9V03X_CSI_W / 2]
cy = mapy[(int)(MT9V03X_CSI_H * 0.78f)][MT9V03X_CSI_W / 2]
```

Decision:

Do not change `cx/cy` in Stage 1. However, Stage 1 must name the variables `cx/cy` and keep the current value source explicit:

```text
cx = rt->control_center_x
cy = START_HIGH
```

This keeps the data contract compatible with RT1064 while avoiding a same-commit geometry change.

Changing the value source changes geometry and control origin, so it must be its own measured stage.

Stage 5 options:

```text
A. keep current control_center_x + START_HIGH
B. compute cx/cy by projecting a raw wheel reference point through current perspective lookup
C. keep x calibrated but choose a better y independent from seed START_HIGH
```

Current recommendation:

```text
Use B only after Stage 1/2 make red control line trustworthy.
```

Validation:

```text
straight road red line starts at expected wheel/control point
guide_error sign and magnitude checked on straight and curve
bash code/test.sh --host
```

## Stage 6: Optional Naming And File Cleanup

Files:

```text
code/tracking/mainline.cpp
code/tracking/imgproc.cpp
headers if needed
```

Allowed after behavior is stable:

```text
lookahead_error -> calc_aim_error
private trace_left/right -> closer reference names if still desired
comments around `process_image` equivalent stages
```

Still not recommended:

```text
rename tracking_process_frame -> process_image
rename ring -> circle
split boundary.cpp to corner.cpp
move rptsc/rptsn into runtime_t
```

## Final Recommended Order

```text
0. Freeze current contracts.
1. Vertical slice: track_leftline/rightline candidate output + selected rpts/rptsn + build_rptsn.
2. Make mainline sequence more readable after Stage 1 compiles.
3. Review cross IN wrappers; delete if Stage 1 did not already.
4. Decide ring/build_opp and zebra scan ownership using visible selected rpts/rptsn evidence.
5. Decide cx/cy origin alignment and error formula.
6. Optional naming cleanup only after behavior stabilizes.
```

## User Decisions Before Implementation Goal

These are the decisions that should be locked before starting the next goal:

1. Use `build_rptsn()` as the new normalization function name.
2. Use exact internal names `rptsc0/rptsc1/rpts/rpts_num/rptsn/rptsn_num/begin_id/cx/cy`.
3. Keep first implementation file scope to `imgproc.hpp`, `imgproc.cpp`, `mainline.cpp`.
4. Keep `tracking_process_frame()` name.
5. Keep `ring` naming; do not rename to `circle`.
6. Preserve current `cx/cy = {control_center_x, START_HIGH}` in Stage 1.
7. Preserve `find_seeds()` and `update_search_center()` behavior exactly.
8. Preserve element short-line gate exactly.
9. Preserve ring frame-start action semantics exactly.
10. If `build_rptsn(force_begin_id0)` fully replaces cross IN wrappers, delete `track_leftline_from_start/rightline_from_start`; otherwise keep temporarily and schedule deletion in Stage 3.
11. Do not add report fields in Stage 1 unless the user wants a debug commit.
12. Commit Stage 1 as one focused algorithm-structure commit after build passes.
