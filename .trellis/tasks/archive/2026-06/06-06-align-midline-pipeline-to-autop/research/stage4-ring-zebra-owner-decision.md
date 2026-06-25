# Stage 4 Ring And Zebra Owner Decision

Updated: 2026-06-06.

Scope: decision/review only. No source edit is required by this stage.

Resume note: this is a historical Stage 4 decision record. Current source names
after later cleanup are `snapshot_ring_frame_start_action()`,
`apply_frame_start_element_crop()`, `frame_action_t::base_candidates_ready`,
`build_zebra_scan_midline()`, and `build_ring_opp_for_detection()`. Older text
that says `build_opp()` refers to the same ring opposite-boundary detection
helper before the later naming cleanup.

## Decision

Use option C:

```text
Keep build_ring_opp_for_detection() as ring detection / state-continuity internals only.
Do not make ring-edited boundary_t a current-frame control-midline input.
Do not remove the ring opposite-boundary detection helper in this stage.
```

Current control owner remains:

```text
mainline.cpp
  -> build_frame_boundaries_and_candidates() builds rptsc0 / rptsc1 before element_process()
  -> snapshot_ring_frame_start_action() decides frame-start ring side/crop
  -> apply_frame_start_element_crop() only clips rptsc*_num
  -> build_selected_midline() / build_rptsn() produces rt->track.mid
```

Zebra owner is already settled:

```text
mainline.cpp::build_zebra_scan_midline() chooses a scan midline from existing rptsc0/rptsc1 candidates
-> build_rptsn()
-> zebra_process() only reads midline_t pts/step and scans raw image
```

No zebra source change is needed in Stage 4.

## Why This Decision

RT1064 circle behavior is simple:

```text
check_circle()
  -> detect single-side L + opposite straight

run_circle()
  -> set track_type
  -> update circle state counters
  -> in RUN, crop rpts*s_num and rptsc*_num at the outer L point

main loop
  -> select rptsc0/rptsc1 by track_type
  -> normalize selected line
```

It does not synthesize an opposite boundary.

The current project still has `ring.cpp::build_ring_opp_for_detection()`
(historically called `build_opp()` in this decision record), but after Stage 1/2
it is not a current-frame control-midline owner. It edits `boundary_t` after
`rptsc0/rptsc1` have already been built. That means it can help ring state and
corner continuity, but it does not directly steer the current frame.

This is safer than deleting `build_ring_opp_for_detection()` immediately because
current `RING_STATE_IN/RUN` still depend on `opp->l_ok`, refreshed corners, and
straightness checks. It is also safer than rebuilding `rptsc0/rptsc1` after
`ring_process()`, because that would intentionally route a non-reference
synthesized boundary into control.

## Current Code Evidence

### Candidate-first mainline

`code/tracking/mainline.cpp:119-152`:

```text
build_frame_boundaries_and_candidates()
  -> build_boundary_from_trace()
  -> build_rpts0/build_rpts1
  -> refresh_boundary_corners()
  -> rptsc0_num = track_leftline(rpts0s, ...)
  -> rptsc1_num = track_rightline(rpts1s, ...)
```

`code/tracking/mainline.cpp:814-819`:

```text
update_search_center()
-> build_frame_boundaries_and_candidates()
-> snapshot_ring_frame_start_action()
-> element_process()
-> action.base_candidates_ready = 1
```

So `rptsc0/rptsc1` are built before `element_process()` can call
`ring_process()`.

### Ring current-frame action

`code/tracking/mainline.cpp:155-188`:

```text
snapshot_ring_frame_start_action()
  BEGIN/RUN/END -> outer side
  IN/OUT        -> inner side
  RUN           -> save frame-start crop side/index
```

`code/tracking/mainline.cpp:253-272`:

```text
apply_frame_start_element_crop()
  cross_near -> crop rptsc0_num/rptsc1_num
  ring RUN   -> crop selected rptsc*_num from frame-start crop index
```

It does not rebuild candidates from ring-edited `boundary_t`.

### Ring edits boundary_t, not current-frame candidates

`code/tracking/ring.cpp:78` defines `build_ring_opp_for_detection()`.

`code/tracking/ring.cpp:356-359`:

```text
RING_STATE_IN:
  build_ring_opp_for_detection(...)
  refresh_ring_corners(...)
```

`code/tracking/ring.cpp:363-385`:

```text
RING_STATE_RUN:
  if opp->l_ok:
    crop opp->original_step
    build_boundary_from_trace(..., opp)
    refresh_ring_corners(...)
    maybe state -> OUT
```

Those edits happen inside `element_process()` after current-frame candidates
already exist.

### Final selected midline

`code/tracking/mainline.cpp:274-288`:

```text
cross_far -> solve_cross_mid()
LEFT      -> build_rptsn(rptsc0, rptsc0_num, ...)
RIGHT     -> build_rptsn(rptsc1, rptsc1_num, ...)
```

Therefore current-frame steering reads `rptsc0/rptsc1`, not ring-edited
`boundary_t`.

### Zebra uses normalized scan midline

`code/tracking/mainline.cpp:514-529`:

```text
left L only  -> build_rptsn(rptsc1, ...)
right L only -> build_rptsn(rptsc0, ...)
```

`code/tracking/zebra.cpp:110-153`:

```text
zebra_process(rt, scan_mid)
  -> read scan_mid->step
  -> read scan_mid->pts[i]
  -> map to raw
  -> scan raw pixels
```

`zebra.cpp` does not own candidate generation.

## Reference Evidence

`RT1064 Project/CODE/circle.c:23-31`:

```text
check_circle()
  single-side L + opposite straight -> CIRCLE_*_BEGIN
```

`RT1064 Project/CODE/circle.c:37-145`:

```text
BEGIN / IN / RUN / OUT / END:
  set track_type
  update state counters
  RUN may crop rpts*s_num and rptsc*_num at outer L
```

There is no opposite-boundary synthesis helper equivalent.

`RT1064 Project/USER/src/main.c:353-360`:

```text
if track_type == TRACK_LEFT:
  rpts = rptsc0
else:
  rpts = rptsc1
```

`RT1064 Project/CODE/garage.c:55-75`:

```text
single-side L chooses opposite rptsc* directly for zebra/garage scan
```

This matches the current post-Stage-1/2 zebra ownership.

## Agent Review Summary

Fixed agents used:

```text
Fermat
Huygens
Euclid
```

Consensus:

```text
1. build_ring_opp_for_detection() does not affect the current-frame control midline after Stage 1/2.
2. RT1064 circle does not synthesize the opposite boundary.
3. The safest Stage 4 decision is C:
   keep build_ring_opp_for_detection() as ring detection/state continuity only,
   do not wire it into current-frame control,
   do not delete it without real ring-sequence evidence.
4. Zebra owner is already correct enough:
   mainline builds a normalized scan midline from rptsc0/rptsc1,
   zebra_process only scans raw image from midline_t.
```

## What Not To Do Now

Do not:

```text
rebuild rptsc0/rptsc1 after ring_process()
make mainline consume ring-edited boundary_t for current-frame control
delete build_ring_opp_for_detection()
rewrite ring state transitions
change zebra_process()
add source cleanup before Stage 5
```

## Next Stage

Stage 5 is:

```text
control origin / error formula review
```

Recommended before any ring behavior code change:

```text
collect real ring-sequence telemetry:
  ring.kind
  ring.state
  selected track_type
  rptsc0_num / rptsc1_num
  mid.step
  reject_reason
  guide_error
```

If a future real-sequence review proves that ring recognition succeeds but
selected side/candidate count is wrong, open a targeted ring behavior task.
Do not mix that with the owner decision already closed here.
