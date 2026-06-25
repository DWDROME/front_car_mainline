# Claude Review Resolution

Updated: 2026-06-06.

Scope: brainstorm only. No source implementation in this task.

## Review Result

Claude's Stage 1 architecture review result:

```text
Conditionally approved.
One blocker must be resolved before implementation.
```

The blocker was B1: the previous docs conflicted on crop order.

```text
Flowchart:
  build rptsc0/rptsc1 first -> element_process -> crop

Old all-stage text:
  crop rpts0s/rpts1s first -> rebuild or crop rptsc
```

If implemented literally, cross BEGIN and ring RUN crop could silently become a no-op, because candidates would already have been built from full-length `rpts0s/rpts1s`.

## User Decision

Use the RT1064-like candidate-first flow.

```text
1. Build rptsc0/rptsc1 once before element_process().
2. After element_process(), apply effective control crop to rptsc0_num/rptsc1_num.
3. Do not rely on old rpts0s_num/rpts1s_num crop after candidates have already been built.
```

## Locked Stage 1 Contract

```text
ordinary:
  rpts0s/rpts1s
  -> rptsc0/rptsc1
  -> select candidate
  -> build_rptsn(force=0)

cross BEGIN / same-frame BEGIN->IN:
  rpts0s/rpts1s
  -> rptsc0/rptsc1
  -> element_process()
  -> crop rptsc0_num/rptsc1_num by rt->track.left/right.now_step
  -> select ordinary_track_type0
  -> build_rptsn(force=0)

ring RUN:
  rpts0s/rpts1s
  -> rptsc0/rptsc1
  -> element_process()
  -> crop selected rptsc*_num by frame-start ring crop index
  -> build_rptsn(force=0)

CROSS_IN:
  farline tail from rt->cross.left_pts/right_pts
  -> far candidate via track_leftline/rightline
  -> build_rptsn(force=1)
```

## Remaining Implementation Notes

M1. Resampling ownership:

```text
track_leftline/rightline must output 1:1 candidate points.
They must not resample.
Only build_rptsn() resamples into final control midline.
```

M2. Zebra scan:

```text
zebra_process() only requires scan_mid->pts/step in IPM/control coordinates that can be projected back to raw.
build_zebra_mid() must not keep calling old final-midline track_leftline/rightline semantics.
Use candidate generation + build_rptsn().
```

Hard constraint after candidate-first crop:

```text
build_zebra_mid() must consume the already-cropped candidate arrays
rptsc0/rptsc1 and rptsc0_num/rptsc1_num.

It must not rebuild from rpts0s/rpts1s after element crop.
```

Reason:

```text
After Stage 1, cross-near and ring-RUN control crop targets rptsc*_num.
rpts0s_num/rpts1s_num remain full-length for corner/ordinary selection evidence.

If build_zebra_mid() rebuilds from rpts0s/rpts1s, zebra scanning silently ignores
the cross-near crop and can regress in CROSS_BEGIN / same-frame BEGIN->IN frames.
```

M3. `imgproc.cpp` edit discipline:

```text
find_seeds(), trace_single(), trace_left(), trace_right(), seed thresholds, and trace border rules are out of scope.
Stage 1 edits in imgproc.cpp must be limited to track_leftline/rightline, from_start removal if fully migrated, and build_rptsn support.
```

## Cleanups Now Allowed In Stage 1

Because `track_leftline_from_start/rightline_from_start` only feed `solve_cross_mid()`, Stage 1 may lock the deterministic delete path:

```text
Migrate solve_cross_mid() to far candidate + build_rptsn(force=1).
Then delete track_leftline_from_start/rightline_from_start declarations and definitions in the same diff.
```

## Final Implementation Correction

The original Stage 1 write scope listed only:

```text
code/tracking/imgproc.hpp
code/tracking/imgproc.cpp
code/tracking/mainline.cpp
```

User supplied measured geometry corrections:

```text
CONTROL_CENTER_X = 86
ROAD_HALF_WIDTH = 26
```

Current source still contains older defaults in `code/tuning.hpp`:

```text
CONTROL_CENTER_X = 80
ROAD_HALF_WIDTH = 20
```

Therefore the implementation scope must include `code/tuning.hpp`, or the
Stage 1 refactor will preserve old geometry while claiming to inherit measured
IPM calibration.
