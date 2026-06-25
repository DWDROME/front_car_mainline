# Three-Agent Review Summary

## Agent A: RT1064 Reference Mainline

Core finding:

```text
process_image()
  -> generates rptsc0/rptsc1 candidate centerlines
run_cross/run_circle
  -> modify track_type or crop point counts
main loop final stage
  -> select rpts/rpts_num
  -> normalize begin_id to cx/cy
  -> resample into rptsn
  -> compute aim_idx and error
```

Reference names recommended for direct alignment:

```text
process_image
track_leftline
track_rightline
rpts0s/rpts1s
rptsc0/rptsc1
rpts/rpts_num
rptsn/rptsn_num
begin_id
cx/cy
aim_idx/aim_idx_near
track_type
TRACK_LEFT/TRACK_RIGHT
```

Agent A's key conclusion:

`track_leftline()` / `track_rightline()` in RT1064 are pure geometric offset functions. They do not own `begin_id`, fixed start normalization, `rptsn`, or control aim-point logic.

## Agent B: Current Code Mainline

Core finding:

```text
tracking_process_frame()
  -> seed/trace/boundary/element/track selection
  -> calls current track_leftline()/track_rightline()

current track_leftline()/track_rightline()
  -> offset boundary to local mids[]
  -> find nearest begin to ref
  -> overwrite mids[begin] with ref
  -> resample
  -> push into midline_t with dist[]
```

Current responsibilities are mixed in two places:

- `mainline.cpp` owns too many orchestration details but must remain the main pipeline owner for now.
- `imgproc.cpp::track_leftline/rightline` own both candidate centerline generation and final normalized control midline generation.

Agent B's recommended first cut:

```text
imgproc.hpp/cpp:
  make track_leftline/rightline match RT1064: pts_in -> rptsc0/rptsc1 only

mainline.cpp:
  explicitly maintain rptsc0/rptsc1
  select rpts/rpts_num
  normalize into rt->track.mid
  then run existing gate + guide_error
```

Do not first-cut refactor `runtime_t`, assistant, report, control, seed, or ring state machine.

## Agent C: Risk Critic

Critical preserved contracts:

- `rt->track.mid` remains final control midline in IPM/control coordinates.
- `midline->pts[0]` remains the fixed control start point.
- `midline->dist[]` remains valid because `lookahead_error()` and `midline_has_lookahead()` depend on it.
- `guide_error` must be computed from normalized midline, not raw candidate centerline.
- `CROSS_IN` must preserve `begin_id = 0` semantics.
- Current element-frame short-midline gate must not be changed incidentally.

Affected paths:

```text
ordinary line
cross BEGIN
cross IN
ring states
zebra scan midline
assistant red line
report/live fields
control input validity and guide error
```

Agent C's first-cut restriction:

Only split candidate centerline offset from fixed-start normalization. Do not touch seed, ring state machine, control PID, assistant protocol, or cross farline detection in the first implementation task.

## Combined Consensus

All three agents agree:

1. The reference structure is better and should guide the refactor.
2. The first implementation task should not be a broad algorithm rewrite.
3. The core first cut is structural:
   ```text
   track_leftline/rightline: only offset boundary -> candidate centerline
   mainline final stage: select candidate -> normalize -> rt->track.mid -> guide
   ```
4. Naming should move toward RT1064 names where it improves comparison.
5. `rt->track.mid` can stay as the public runtime output, but internally it should be treated as reference `rptsn`.
