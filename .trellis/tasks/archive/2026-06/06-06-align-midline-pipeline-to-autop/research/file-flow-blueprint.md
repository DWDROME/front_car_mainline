# File-Level Function Flow Blueprint

## Reference: `Project/USER/inc/main.h`

```text
main.h
-> declares ipts0/ipts1
-> declares rpts0/rpts1
-> declares rpts0b/rpts1b
-> declares rpts0s/rpts1s
-> declares rpts0a/rpts1a
-> declares rpts0an/rpts1an
-> declares rptsc0/rptsc1
-> declares rpts/rpts_num
-> declares rptsn/rptsn_num
-> declares track_type and element states
```

## Reference: `Project/USER/src/main.c`

```text
frame loop
-> process_image()
-> find_corners()
-> ordinary track_type from rpts0s_num/rpts1s_num
-> check element states
-> run element states
-> choose selected centerline:
   normal/circle/cross-BEGIN: rpts = rptsc0 or rptsc1
   cross-IN: build farline center into rpts
-> cx/cy fixed control start
-> begin_id nearest selected centerline point
-> force begin_id = 0 for special modes
-> set rpts[begin_id] = cx/cy
-> resample selected tail into rptsn
-> choose aim_idx / aim_idx_near
-> compute steering error
```

## Reference: `Project/CODE/imgproc.c`

```text
findline_*_adaptive()
-> raw edge trace

blur_points()
-> filtered line

resample_points()
-> equal-distance line

local_angle_points()
-> local corner angle

nms_angle()
-> suppress non-corner points

track_leftline()
-> left boundary sampled line -> left candidate centerline rptsc0

track_rightline()
-> right boundary sampled line -> right candidate centerline rptsc1
```

## Current: `code/tracking/mainline.cpp`

```text
track_line_found()
-> validates rt->track.{track_type,reject_reason,mid.step}

trace_edges()
-> trace left/right side from seeds
-> mutate seed state after trace failure

clear_rpts()
-> clears file-static rpts0/rpts1/rpts0b/rpts1b/rpts0s/rpts1s counts

solve_cross_mid()
-> select farline after L point
-> current calls track_*_from_start()
-> writes rt->track.mid

build_zebra_mid()
-> selects opposite-side scan midline
-> current calls track_leftline/rightline()

build_rpts0()/build_rpts1()
-> raw original boundary -> perspective -> blur -> resample

pick_track_type()
-> select TRACK_TYPE_LEFT/RIGHT/NONE from rpts0s_num/rpts1s_num and track_type_keep

lookahead_error()
-> choose midline point by dist[] and compute angle error

update_search_center()
-> update next frame seed-search center from seeds and width_base

tracking_process_frame()
-> orchestrates all stages
```

## Target: `code/tracking/mainline.cpp`

```text
tracking_process_frame()
-> seed / trace / boundary / rpts0s/rpts1s stays mostly unchanged
-> build candidate centerlines:
   track_leftline(rpts0s, rpts0s_num, rptsc0, approx_num, ROAD_HALF_WIDTH)
   track_rightline(rpts1s, rpts1s_num, rptsc1, approx_num, ROAD_HALF_WIDTH)
-> element process may request near-line/ring crop
-> because candidates are already built, apply effective control crop to rptsc0_num/rptsc1_num
-> do not rely on old rpts0s_num/rpts1s_num crop as the effective selected-line crop
-> select rpts/rpts_num:
   ordinary/ring/cross-BEGIN -> rptsc0/rptsc1
   cross-IN -> farline candidate centerline
-> normalize selected centerline:
   build_rptsn(rpts, rpts_num, cx, cy, force_begin_id0, &rt->track.mid)
-> run existing min-mid and lookahead gates
-> compute guide_error from normalized rt->track.mid
```

## Current: `code/tracking/imgproc.hpp/cpp`

```text
track_leftline/current
-> input sampled side boundary
-> offset into mids[]
-> find nearest begin
-> overwrite begin with ref
-> resample
-> push into midline_t

track_rightline/current
-> same shape

track_*_from_start/current
-> duplicate offset code
-> force first candidate to ref
-> resample
-> push into midline_t
```

## Target: `code/tracking/imgproc.hpp/cpp`

```text
track_leftline(target)
-> input sampled left boundary
-> output candidate centerline points
-> no ref
-> no midline_t
-> no begin_id
-> no resample-to-rptsn

track_rightline(target)
-> input sampled right boundary
-> output candidate centerline points

build_rptsn or normalize_midline_start(target)
-> input selected candidate centerline rpts/rpts_num
-> input cx/cy
-> input force_begin_id0
-> output rt->track.mid / midline_t
-> computes dist[]
```

## Current: `code/types.hpp`

```text
runtime_t
-> owns input image, seed/trace, element states, tracking result, control state

track_result_t
-> reject_reason
-> track_type
-> center_x
-> guide_error
-> left/right boundary_t
-> midline_t mid

midline_t
-> pts/dist/step
```

Target decision:

- Keep public `rt->track.mid` as final normalized output.
- Avoid adding `rptsc0/rptsc1/rptsn` to `runtime_t` in first cut.
- Use file-static or local arrays in `mainline.cpp` unless user chooses full reference-style globals.

## Current: `code/tuning.hpp`

```text
RAW_W/H, IPM_W/H
MID_X
CONTROL_CENTER_X
START_HIGH
ROAD_HALF_WIDTH
LOOKAHEAD_DIST
```

Target decision:

- `START_HIGH` currently doubles as seed row and control ref y.
- Reference has `begin_y` for seed and `cx/cy` from mapped wheel point.
- User must decide whether first cut keeps `{CONTROL_CENTER_X, START_HIGH}` or introduces closer `cx/cy` semantics.

## Current: `code/app/assistant.cpp`

```text
config_points()
-> x0/y0 raw left boundary
-> x1/y1 control_mid_pts(rt->track.mid projected to raw)
-> x2/y2 raw right boundary
```

Target:

- No first-cut algorithm changes.
- It remains correct if `rt->track.mid` remains final normalized control line.

## Current: `code/app/report.cpp`

```text
print_live()/write_report()
-> report track_line_found, reject, track_type, mid_step, m0, ml, guide
```

Target decision:

- Optional migration diagnostics: `begin_id`, `force_begin`, `selected_rpts_num`, `rptsc0_num`, `rptsc1_num`, `rptsn_num`.
- Do not add unless user approves.
