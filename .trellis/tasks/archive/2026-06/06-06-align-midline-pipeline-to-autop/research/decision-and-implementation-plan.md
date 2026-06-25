# Decision And Implementation Plan

## Recommended Decision

Proceed with a structural refactor, but constrain first implementation to the midline pipeline only.

Recommended first implementation scope:

```text
code/tracking/imgproc.hpp
code/tracking/imgproc.cpp
code/tracking/mainline.cpp
```

Potentially touched only if compile requires declaration/report sync:

```text
code/types.hpp      no first-cut field additions recommended
code/app/report.cpp optional diagnostics only, not recommended first cut
code/app/assistant.cpp no change expected
```

## Recommended Target Shape

### 1. Make candidate centerline generation pure

Change `track_leftline()` / `track_rightline()` to reference-like semantics:

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
```

Behavior:

```text
input sampled side boundary
-> compute tangent using approx_num
-> normalize tangent
-> offset by dist
-> output candidate centerline
-> return candidate count
```

No `ref_x/ref_y`.
No `midline_t`.
No begin search.
No fixed-start overwrite.
No `dist[]`.

### 2. Add one unified normalization stage

Use either name below; final name requires user decision:

```text
build_rptsn()              closer to reference variable name
normalize_midline_start()  clearer C++ descriptive name
```

Recommended signature:

```cpp
int build_rptsn(const double rpts[POINT_MAX][2],
                int rpts_num,
                int cx,
                int cy,
                int force_begin_id0,
                midline_t *midline);
```

Behavior:

```text
if force_begin_id0:
    begin_id = 0
else:
    begin_id = nearest point in rpts to cx/cy
if begin_id invalid or rpts_num - begin_id < min step:
    return 0
copy or temporarily rewrite selected begin as cx/cy
resample_points(rpts + begin_id, ..., rptsn, sample distance)
fill midline->pts
fill midline->dist
fill midline->step
return midline->step
```

### 3. Make `mainline.cpp` flow more reference-like

Add file-static arrays or local arrays:

```cpp
double rptsc0[POINT_MAX][2];
double rptsc1[POINT_MAX][2];
int rptsc0_num;
int rptsc1_num;

const double (*rpts)[2];
int rpts_num;
```

Target flow:

```text
build_rpts0/build_rpts1
-> track_leftline(rpts0s, rpts0s_num, rptsc0, approx_num, ROAD_HALF_WIDTH)
-> track_rightline(rpts1s, rpts1s_num, rptsc1, approx_num, ROAD_HALF_WIDTH)
-> element_process and crop must keep candidate counts aligned
-> choose rpts/rpts_num by work_track_type
-> cross_far_frame can build candidate from farline then force_begin_id0
-> build_rptsn(rpts, rpts_num, cx, cy, force_begin_id0, &rt->track.mid)
-> existing gate and guide_error
```

## Proposed Per-Path Handling

### Ordinary

```text
rpts0s/rpts1s
-> rptsc0/rptsc1
-> pick_track_type
-> select rpts/rpts_num
-> build_rptsn(force=0)
```

### Cross BEGIN

```text
cross_begin clips boundary point counts
-> mainline clips rpts0s/rpts1s and must also keep rptsc0/rptsc1 aligned
-> select ordinary_track_type0
-> build_rptsn(force=0)
```

### Cross IN

```text
cross_farline builds far_rpts0s/far_rpts1s
-> build candidate centerline from far_rpts starting at far_Lpt id
-> build_rptsn(force=1)
```

This removes the need for `track_leftline_from_start()` / `track_rightline_from_start()`.

### Ring

```text
keep current ring state machine and side table
-> ring selects work_track_type
-> ring RUN crop must crop candidate centerline count consistently
-> build_rptsn(force=0)
```

No `ring.cpp` rewrite in first cut.

### Zebra

Current `build_zebra_mid()` must be adjusted because it currently calls old `track_leftline/rightline()` directly.

Target:

```text
select scan candidate side
-> use candidate centerline or rebuild candidate centerline
-> build_rptsn(force=0) into local midline_t zebra_mid
-> zebra_process(rt, &zebra_mid)
```

## Explicit Non-Goals

- Do not change seed acquisition.
- Do not change ring state transitions.
- Do not change cross farline detection.
- Do not change control PID or drive output.
- Do not change assistant protocol.
- Do not add fallback midlines.
- Do not add broad logging framework.
- Do not split `runtime_t` in first cut.

## User Decisions Needed Before Implementation

1. Function naming: use `build_rptsn()` or `normalize_midline_start()`?
2. Candidate arrays: use exact `rptsc0/rptsc1/rptsn` names in `mainline.cpp`, or more C++ names with reference comments?
3. `track_leftline/rightline` signatures: make them close to RT1064 exactly, or keep C++ type style but same semantics?
4. `cx/cy`: keep current `{control_center_x, START_HIGH}` for first cut, or implement reference-style mapped wheel point now?
5. `force_begin_id0`: apply only for `CROSS_IN` first cut?
6. Generate both candidate centerlines every valid frame like reference, or only selected one for lower cost?
7. Delete `track_leftline_from_start/rightline_from_start` in same implementation, or leave wrappers temporarily calling new primitives?
8. Keep `track_dualline()` untouched, delete it, or move it behind an explicit experimental comment?
9. Do we add temporary report fields for `begin_id/aim_idx/rptsn_num` to verify behavior?
10. Should `LOOKAHEAD_DIST` naming be kept for now, or start moving toward `aim_distance`?
11. Should zebra use the same selected candidate centerline if available, or rebuild its own opposite-side candidate?
12. Should implementation be one commit or split into two commits: `imgproc` semantic split, then `mainline` wiring?

## Recommended Answers Unless User Overrides

1. Use `build_rptsn()` internally because it aligns with reference; add a clear comment that it normalizes selected centerline.
2. Use exact `rptsc0/rptsc1/rptsn` file-static names in `mainline.cpp`.
3. Make `track_leftline/rightline` close to RT1064 signatures.
4. Keep current `{control_center_x, START_HIGH}` in first cut to avoid changing camera geometry and control origin at the same time.
5. Force begin only for `CROSS_IN` first cut.
6. Generate both candidate centerlines every valid frame, like reference.
7. Delete `*_from_start` in same implementation if all call sites are migrated.
8. Keep `track_dualline()` untouched but do not wire it into the new path.
9. Do not add report fields in first cut unless user wants extra verification visibility.
10. Keep `LOOKAHEAD_DIST` for now.
11. Rebuild zebra local candidate and pass through `build_rptsn()` to avoid hidden dependency.
12. Prefer one focused commit for the midline pipeline refactor after approval.

## Calibration Facts To Preserve

User supplied teammate calibration:

```cpp
// CONTROL_CENTER_X = 87,  // previous value, measured IPM road center around 86
CONTROL_CENTER_X = 86,     // 2026-06 adjusted from IPM_DBG measurement

// ROAD_HALF_WIDTH = 20,    // old value, measured IPM road width around 52 px
ROAD_HALF_WIDTH = 26,      // 2026-06 adjusted from IPM_DBG measurement
```

Current source still shows older constants in `code/tuning.hpp`:

```text
CONTROL_CENTER_X = 80
ROAD_HALF_WIDTH = 20
```

Stage 1 implementation must not accidentally preserve the old geometry when
rewiring the midline pipeline. The selected contract remains:

```text
cx = rt->control_center_x
cy = START_HIGH
dist = ROAD_HALF_WIDTH
```

But the intended calibrated defaults are:

```text
CONTROL_CENTER_X = 86
ROAD_HALF_WIDTH = 26
```

This is not a separate algorithm change. It is a measured geometry correction
that `build_rptsn()` and `track_leftline/rightline()` must inherit.
