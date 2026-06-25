# Stage 2 Mainline Flow Plan

Updated: 2026-06-06.

Scope: brainstorm / design before source edits.

Stage 1 is implemented and pushed as:

```text
07bec91 fix bug：对齐参考版中线生成流程
```

Current working tree at Step 2 entry is clean.

## Purpose

Step 2 is not an algorithm change. It is a `mainline.cpp` readability and
phase-boundary pass after Stage 1 made the selected-midline contract explicit.

Target from `all-stage-refactor-plan.md`:

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

## Current Pain Point

`tracking_process_frame()` now contains all of these concerns inline:

```text
seed acquisition
trace filtering
CROSS_IN no-seed/no-trace continuation
search-center update
boundary/rpts/rptsc construction
ring frame-start side/crop snapshot
element_process()
cross/ring/ordinary frame classification
candidate crop
work_track_type selection
build_rptsn or cross farline build
short-midline gate
track result publication
zebra scan
```

The behavior is already correct enough to compile after Stage 1, but the order
is hard to audit because frame-start action variables and post-element frame
classification are mixed as loose locals.

## Non-Negotiable Invariants

Do not change:

```text
find_seeds() arguments or thresholds
trace_edges() behavior
update_search_center() position: after trace success, before boundary build
cross_process() behavior and cross farline detection
ring state transition logic in ring.cpp
element_process() timing
candidate-first crop target: rptsc0_num/rptsc1_num
element short-midline gate
control/PID
assistant/report protocol
file names
```

Do not move `update_search_center()` before trace filtering.

Do not make same-frame BEGIN->IN use farline. Only a frame that started in
`CROSS_STATE_IN` may use CROSS_IN farline:

```cpp
cross_far_frame = (cross_state0 == CROSS_STATE_IN &&
                   rt->cross.state == CROSS_STATE_IN);
```

## Recommended Step 2 Cut

Only edit:

```text
code/tracking/mainline.cpp
```

Introduce small file-local structs, not runtime fields:

```cpp
struct frame_action_t
{
    int cross_state0;
    int ordinary_track_type;
    int ring_track_type;
    int ring_run_crop_side;
    int ring_run_crop_index;
    int normal_ok;
};

struct frame_mode_t
{
    int cross_far;
    int cross_near;
    int ring_active;
    int element_action;
    int work_track_type;
};
```

These are local readability tools. They must not be stored in `runtime_t`.

## Candidate Helper Functions

### `reset_frame_tracking_state(runtime_t *rt)`

Move only the existing reset block:

```text
memset track/seeds/traces
reject_reason = NONE
track_type = NONE
center_x = -1
```

No behavior change.

### `build_frame_boundaries_and_candidates(runtime_t *rt, int use_matrix)`

Move the trace-success block after `update_search_center()`:

```text
build_boundary_from_trace(left/right)
clear_rpts()
build_rpts0/build_rpts1
refresh_boundary_corners
ordinary_track_type = pick_track_type()
rptsc0_num = track_leftline(...)
rptsc1_num = track_rightline(...)
```

Return `ordinary_track_type`.

This helper must not call `element_process()`.

### `snapshot_ring_action(runtime_t *rt, frame_action_t *action)`

Move the current ring frame-start side/crop computation exactly.

Important: this must run before `element_process()`.

### `classify_frame_mode(runtime_t *rt, const frame_action_t *action)`

Move the current post-`element_process()` classification:

```text
cross_far
cross_near
ring_active
work_track_type
element_action
```

Keep the same same-frame BEGIN->IN rule.

### `apply_element_crop(runtime_t *rt, const frame_mode_t *mode, const frame_action_t *action)`

Move only the two crop blocks:

```text
cross_near -> crop rptsc0_num/rptsc1_num by now_step
ring RUN   -> crop selected rptsc*_num by frame-start crop index
```

Never crop `rpts0s_num/rpts1s_num` here.

### `build_selected_midline(runtime_t *rt, const frame_mode_t *mode, point_t ref)`

Move:

```text
cross_far -> solve_cross_mid()
LEFT      -> build_rptsn(rptsc0...)
RIGHT     -> build_rptsn(rptsc1...)
```

No gate logic inside.

### `publish_track_result(runtime_t *rt, const frame_mode_t *mode, int mid_ok, point_t ref)`

Move final gate and publication:

```text
min_mid_step
midline_has_lookahead
reject_reason
track_type
track_type_keep
center_x
guide_error
```

Return 1/0.

## Expected Final `tracking_process_frame()` Shape

```cpp
int tracking_process_frame(runtime_t *rt)
{
    if(rt == nullptr || !rt->gray_valid)
        return 0;

    reset_frame_tracking_state(rt);

    frame_action_t action = {};
    action.cross_state0 = rt->cross.state;

    if(!find_frame_seeds_or_cross_in(rt))
        return 0;

    if(seed path)
    {
        if(!trace_frame_edges_or_cross_in(rt, &use_matrix))
            return 0;

        action.normal_ok = 1;
        update_search_center(rt);
        action.ordinary_track_type = build_frame_boundaries_and_candidates(rt, use_matrix);
        snapshot_ring_action(rt, &action);
        element_process(rt);
    }

    point_t ref = {rt->control_center_x, START_HIGH};
    frame_mode_t mode = classify_frame_mode(rt, &action);

    if(!action.normal_ok && !mode.cross_far)
        reject NO_MIDLINE;

    apply_element_crop(rt, &mode, &action);

    const int mid_ok = build_selected_midline(rt, &mode, ref);
    if(!publish_track_result(rt, &mode, mid_ok, ref))
        return 0;

    run_zebra_scan(rt, ref, mode.cross_far);
    return 1;
}
```

The actual implementation can avoid over-splitting seed/CROSS_IN into helpers if
that makes the diff safer. The important Step 2 improvement is to make action,
mode, crop, selected midline, and final gate visually separate.

## Risk Points For Implementation Review

1. `element_process(rt)` must remain after ring frame-start action snapshot.
2. `normal_ok` must only become true after successful seed + trace + boundary/candidate construction.
3. no-seed / trace-failed `CROSS_IN` must still call `clear_rpts(); cross_process(rt);`
4. `cross_near` crop must happen before `build_zebra_mid()` because zebra consumes `rptsc*`.
5. `work_track_type == TRACK_TYPE_NONE` must still reject before final midline build.
6. `track_type_keep` must only update after final gate succeeds.
7. `lookahead_error()` may be renamed later, but Step 2 should not mix naming cleanup unless the diff remains obviously mechanical.

## Validation

Run:

```bash
git diff --check -- code/tracking/mainline.cpp
bash code/test.sh --host
```

Manual review:

```text
git diff -- code/tracking/mainline.cpp
```

Confirm the diff is mostly extraction/reordering inside `mainline.cpp`, and no
condition changed for:

```text
cross_far_frame
cross_near_frame
ring_active_frame
ring RUN crop
final element gate
```
