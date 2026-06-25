# Patch 5A Control Origin Closeout

Updated: 2026-06-06 14:51:14 +0800.

Reason:

```text
The original user question included RT1064-style midline start normalization.
Stage 5 had identified the mismatch but left it deferred. That was incomplete.
```

## Reference

RT1064 uses the mapped raw wheel point as the fixed control start:

```text
cx = mapx[(int)(H * 0.78f)][W / 2]
cy = mapy[(int)(H * 0.78f)][W / 2]
```

Then it finds `begin_id`, overwrites the selected candidate point with
`cx/cy`, and resamples into `rptsn`.

## Previous Current Code

Before Patch 5A:

```text
ref = {rt->control_center_x, START_HIGH}
default ref = {86,116}
```

This reused the seed/search row as the control-midline normalization y. That was
not RT1064-equivalent.

## Patch 5A Change

Changed:

```text
code/tracking/mainline.cpp
```

New behavior:

```text
if rt->has_matrix:
  raw_x = RAW_W / 2
  raw_y = int(RAW_H * 0.78)
  ref = perspective_lookup_raw_to_ipm(raw_x, raw_y)
else:
  ref = {rt->control_center_x, START_HIGH}
```

Fallback also applies if the lookup fails.

Current table probe:

```text
raw=(80,93) -> ipm=(88.52225,108.59464) -> rounded ref=(89,109)
```

## Explicit Non-Changes

```text
LOOKAHEAD_DIST unchanged.
START_HIGH still used for seed search and bottom scan.
control_center_x remains as fallback x and env-calibrated debug value.
No seed/trace/ring/cross/zebra/control/PID/assistant/report behavior changed.
```

This document records Patch 5A only. Patch 5B was later completed in:

```text
research/patch5b-guide-error-closeout.md
```

After Patch 5B, `guide_error` uses the RT1064-style negative atan2 sign and
forward bias. It still requires real-car steering sign and magnitude validation.

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
