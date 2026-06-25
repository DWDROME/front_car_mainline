# Stage 5 Control Origin And Error Formula Review

Updated: 2026-06-06.

Scope: decision/review only. No source edit is required by this stage.

## Decision

Do not change source in Stage 5.

Close Stage 5 as a calibration and validation decision:

```text
1. Current control origin is not RT1064-equivalent.
2. Current guide_error formula is not RT1064-equivalent.
3. Both differences are real behavior changes, not cleanup.
4. Do not change control origin and error formula in the same patch.
5. Future source change must be split and verified on replay / real car.
```

Recommended future order:

```text
A. First split control origin from seed row:
   current: ref = {control_center_x, START_HIGH}
   future : ref = projected raw wheel point, with fallback

B. Then separately review guide_error formula:
   current: atan2(dx, dy)
   RT-style: -atan2(dx, dy + forward_bias)

C. Only after sign/magnitude validation, retune outer_sign / outer_kp /
   LOOKAHEAD_DIST if needed.
```

## Current Code Contract

Current constants:

```text
CONTROL_CENTER_X = 86
START_HIGH = 116
LOOKAHEAD_DIST = 35
ROAD_HALF_WIDTH = 26
```

Current reference point:

```text
point_t ref = {rt->control_center_x, START_HIGH}
```

Current normalized midline:

```text
build_rptsn(rpts, rpts_num, ref.x, ref.y, force_begin_id0, &rt->track.mid)
```

Current error:

```text
dx = mid[look].x - ref.x
dy = ref.y - mid[look].y
guide_error = atan2(dx, dy) * 180 / pi
```

Current control consumer:

```text
target_yaw = (outer_kp * guide_error + outer_kd * d_error) * outer_sign
```

Therefore `guide_error` is already part of a tuned control contract.

## RT1064 Reference Contract

RT1064 control origin:

```text
cx = mapx[(int)(H * 0.78f)][W / 2]
cy = mapy[(int)(H * 0.78f)][W / 2]
```

RT1064 normalized midline:

```text
rpts[begin_id][0] = cx
rpts[begin_id][1] = cy
resample_points(rpts + begin_id, ..., rptsn, ...)
```

RT1064 angle formula:

```text
dx = rptsn[aim_idx][0] - cx
dy = cy - rptsn[aim_idx][1] + 0.2 * pixel_per_meter
error = -atan2f(dx, dy) * 180 / PI
```

Important caveat:

```text
RT1064 computes error/error_near, but the observed reference segment later uses
pure_angle in the active steering call. Do not assume the error variable alone
is the final steering command without reviewing the exact active build path.
```

## Measured Current-Table Delta

Probe command compiled a temporary program against the current generated IPM
table, without editing source files.

Reference-style raw point for 160x120:

```text
raw x = RAW_W / 2 = 80
raw y = int(RAW_H * 0.78f) = 93
```

Current generated table maps it to:

```text
raw=(80,93) -> ipm=(88.52225,108.59464)
```

Current control origin is:

```text
ref=(86,116)
```

Delta:

```text
dx ~= +2.52 px
dy ~= -7.41 px
```

This is large enough to affect:

```text
begin_id
normalized midline start point
resampled point spacing
lookahead selected point
guide_error magnitude
target_yaw after outer_sign/outer_kp
```

It is not safe to change as a silent cleanup.

## Evidence

### Current origin and error

`code/tuning.hpp`:

```text
CONTROL_CENTER_X = 86
START_HIGH = 116
LOOKAHEAD_DIST = 35
```

`code/tracking/mainline.cpp:789`:

```cpp
point_t ref = {rt->control_center_x, START_HIGH};
```

`code/tracking/imgproc.cpp:890-974`:

```text
build_rptsn()
  -> find nearest begin to cx/cy unless force_begin_id0
  -> overwrite work[0] with cx/cy
  -> resample
  -> write midline->pts/dist/step
```

`code/tracking/mainline.cpp:647-675`:

```text
lookahead_error()
  -> select point by mid.dist nearest LOOKAHEAD_DIST
  -> atan2(dx, dy)
```

`code/core/control.cpp:231-258`:

```text
guide_error -> outer_kp/outer_kd -> outer_sign -> target_yaw
```

### Current perspective support

`code/tracking/perspective.hpp:17`:

```cpp
int perspective_lookup_raw_to_ipm(int x, int y, double *ix, double *iy);
```

`code/tracking/perspective.cpp:55-75`:

```text
raw -> IPM table lookup already exists
```

Future origin change does not need a new perspective subsystem.

### Current runtime override

`code/app/runners.cpp:124-130`:

```text
SMARTCAR_CONTROL_CENTER_X can override control_center_x each frame.
```

This only overrides x. It cannot represent RT-style projected `cy`.

### RT1064 origin and formula

`RT1064 Project/USER/src/main.c:375-401`:

```text
cx/cy from mapx/mapy raw wheel point
nearest begin_id
overwrite rpts[begin_id]
resample to rptsn
```

`RT1064 Project/USER/src/main.c:408-420`:

```text
error = -atan2f(dx, cy - y + 0.2 * pixel_per_meter)
error_near uses same shape
```

## Agent Review Summary

Fixed agents used:

```text
Fermat
Huygens
Euclid
```

Consensus:

```text
1. Stage 5 should not edit source immediately.
2. START_HIGH is still the seed/search row and zebra bottom scan row; do not
   change it to become a control-origin y.
3. Control origin should become its own concept if changed.
4. guide_error formula change affects sign and magnitude and is coupled to
   outer_sign / outer_kp / LOOKAHEAD_DIST.
5. Future implementation is feasible and mostly local to mainline.cpp, but
   must be split into separately validated patches.
```

## Future Patch Scope If User Chooses To Change It

### Patch 5A: control origin only

Files:

```text
code/tracking/mainline.cpp
possibly code/tuning.hpp
```

Shape:

```text
control_ref_point(rt)
  raw_x = RAW_W / 2
  raw_y = round_or_int(RAW_H * 0.78)
  if perspective_lookup_raw_to_ipm(raw_x, raw_y, &cx, &cy):
      return rounded IPM point
  else:
      return {rt->control_center_x, START_HIGH}
```

Do not change:

```text
START_HIGH
find_seeds()
zebra bottom scan
lookahead_error formula
control.cpp
assistant protocol
```

Validation:

```text
straight road red control line starts at expected wheel/control point
mid.pts[0] equals new origin when tracking is valid
guide_error sign on straight/left/right remains expected
bash code/test.sh --host
```

### Patch 5B: guide_error formula only

Files:

```text
code/tracking/mainline.cpp
possibly code/tuning.hpp
possibly front_car_mainline.yaml if outer_sign/outer_kp must retune
```

Open decisions:

```text
1. Add RT-style forward bias? If yes, what pixel value?
2. Flip formula sign, or keep sign and adjust outer_sign?
3. Keep LOOKAHEAD_DIST=35 or move toward aim_distance/sample_dist semantics?
```

Validation:

```text
log current guide_error and candidate RT-style error on same frames
verify straight, left curve, right curve, left-offset, right-offset cases
verify target_yaw sign after outer_sign
retune outer_kp only after sign is correct
```

## Stage 5 Closeout

Stage 5 is closed as review-only.

Next formal stage:

```text
Stage 6: optional naming / file cleanup
```

However, if the user wants actual control-origin work before cleanup, open a
new targeted implementation task for Patch 5A first. Do not combine Patch 5A
with Patch 5B.
