# Patch 5B Guide Error Closeout

Updated: 2026-06-06 14:59:08 +0800.

Reason:

```text
The original user question was not only about candidate-midline ownership.
RT1064 also normalizes the control start point and computes the aim error with
a negative atan2 sign plus a forward bias.
```

## Reference

RT1064 computes the far aim error as:

```text
dx = rptsn[aim_idx][0] - cx
dy = cy - rptsn[aim_idx][1] + 0.2 * pixel_per_meter
error = -atan2f(dx, dy) * 180 / PI
```

## Previous Current Code

Before Patch 5B:

```text
dx = mid[look].x - ref.x
dy = ref.y - mid[look].y
guide_error = atan2(dx, dy)
```

This missed both RT1064 details:

```text
1. negative sign
2. forward bias
```

## Patch 5B Change

Changed:

```text
code/tracking/mainline.cpp
```

New behavior:

```text
dx = mid[look].x - ref.x
dy = ref.y - mid[look].y + k_error_forward_bias
guide_error = -atan2(dx, dy)
```

`k_error_forward_bias` is derived from the current measured road-width
constant:

```text
RT1064: 0.2 * pixel_per_meter
Current ROAD_HALF_WIDTH: measured half road width, about 0.225m
0.2 / 0.225 = 8 / 9
k_error_forward_bias = ROAD_HALF_WIDTH * 8 / 9
```

## Explicit Non-Changes

```text
LOOKAHEAD_DIST unchanged.
outer_sign unchanged.
outer_kp unchanged.
No seed/trace/ring/cross/zebra/control/PID/assistant/report code changed.
```

## Remaining Real-Car Validation

This patch changes steering sign and magnitude before `outer_sign`.

```text
If the car steers away from the target line:
  tune front_car_mainline.yaml outer_sign

If the car steers correctly but too hard/too weak:
  tune outer_kp and, if necessary, LOOKAHEAD_DIST
```

Do not reopen the midline ownership contract first unless telemetry shows the
published `rt->track.mid` itself is wrong.

## Validation

Passed:

```bash
git diff --check -- code/tracking/mainline.cpp code/types.hpp code/tracking/imgproc.hpp
bash code/test.sh --host
```

Build result:

```text
[100%] Built target front_car_mainline
```
