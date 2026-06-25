# Stage 6 Option A Closeout

Updated: 2026-06-06 14:39:48 +0800.

User choice:

```text
A
```

Meaning:

```text
Keep RT1064-style names.
Do not rename rpts0s/rpts1s/rptsc0/rptsc1/build_rptsn().
Add human-readable glossary and flow comments only.
```

## Source Changes

Touched files:

```text
code/tracking/mainline.cpp
code/tracking/imgproc.hpp
code/types.hpp
```

Changes:

1. `mainline.cpp`
   - Added RT1064 point-list glossary near file-static arrays.
   - Added explicit current-frame pipeline comment before
     `tracking_process_frame()`.
   - No symbol rename.
   - No control-flow change.

2. `imgproc.hpp`
   - Clarified that `build_rptsn()` consumes candidates from `rptsc0/rptsc1`
     or CROSS_IN farline expansion.
   - Clarified that its only job is `begin_id -> cx/cy -> resample ->
     midline_t`.
   - No API change.

3. `types.hpp`
   - Clarified `original_pts`, `now_pts`, and `work_pts` coordinate roles.
   - Clarified `track.center_x`, `control_center_x`, and `mid_position` are
     different concepts.
   - No field rename.

## Explicit Non-Changes

```text
No seed behavior change.
No trace behavior change.
No ring/cross/zebra state-machine change.
No control origin change.
No guide_error formula change.
No control/PID change.
No assistant protocol change.
No report data change.
No file split.
No public field rename.
No build_rptsn() rename.
```

## Validation

Passed:

```bash
git diff --check -- code/tracking/mainline.cpp code/tracking/imgproc.hpp code/types.hpp
bash code/test.sh --host
```

Build result:

```text
[100%] Built target front_car_mainline
```

## Deferred Work

Option B is deferred:

```text
Rename private mainline arrays to plain role names after ring/control behavior is
stable, if readability still wins over RT1064 comparison.
```

Option C is deferred:

```text
Rename build_rptsn() only after Stage 5 control-origin and guide_error decisions
are settled.
```
