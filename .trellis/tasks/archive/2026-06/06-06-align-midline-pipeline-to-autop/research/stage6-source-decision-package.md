# Stage 6 Source Decision Package

Updated: 2026-06-06 14:33:56 +0800.

Scope: design only. This file turns Stage 6 into concrete source choices.

## Non-Negotiable Boundary

Stage 6 is about human readability:

```text
names
file responsibilities
flow visibility
comments that explain ownership
```

Stage 6 is not allowed to change:

```text
seed behavior
trace behavior
ring/cross/zebra state transitions
control origin
guide_error formula
control/PID
assistant protocol
report data meaning
```

## Current Evidence

Current code has no source diff at this point:

```text
git diff --quiet -- code -> CODE_DIFF_EXIT=0
```

Important symbol locations:

```text
code/tracking/mainline.cpp
  rpts0s/rpts1s/rptsc0/rptsc1 globals: lines 54-66
  build candidates: lines 108-141
  frame action/mode: lines 78-95, 144-239
  crop/select/publish: lines 242-314
  main entry: lines 734-813

code/tracking/imgproc.hpp
  track_leftline/rightline declarations: lines 125-144
  build_rptsn declaration: lines 157-162
  track_dualline declaration: lines 177-184

code/types.hpp
  boundary_t coordinate names: lines 33-60
  midline_t and guide_error comments: lines 62-70, 135-147
  control_center_x/mid_position: lines 196-206
```

## File Decision Matrix

| File | Stage 6A Option A | Stage 6B Option B | Defer |
| --- | --- | --- | --- |
| `code/tracking/mainline.cpp` | Add a short flow block and glossary near file-static arrays. Keep `rpts*` names. | Rename private arrays/counts to plain role names and add same flow block. | Physical split into `line_output.cpp` / `frame_flow.cpp`. |
| `code/tracking/imgproc.hpp/.cpp` | Add clearer comment for `build_rptsn()` as final normalizer. Keep function names. | Same as A. Do not rename `build_rptsn()` yet. | Rename `build_rptsn()` or split seed/trace/midline into files. |
| `code/types.hpp` | Clarify comments for `original_pts/now_pts/work_pts` and the three center fields. | Same as A. No field rename. | Rename public fields after behavior is stable. |
| `code/tracking/boundary.cpp/.hpp` | No behavior or API change. Optional comment only. | Same as A. | Split `corner.cpp`. |
| `code/tracking/element.cpp/.hpp` | No source change. | No source change. | Split check/run element phases. |
| `code/tracking/cross.cpp/.hpp` | No source change. | No source change. | Rename/split cross state machine. |
| `code/tracking/ring.cpp/.hpp` | No source change. | No source change. | Rename `build_opp()` only after ring behavior is stable. |
| `code/tracking/zebra.cpp/.hpp` | No source change. | No source change. | Move scan-mid owner. |
| `code/app/assistant.cpp/.hpp` | No source change. | No source change. | Split overlay/transport. |
| `code/app/report.cpp/.hpp` | No source change. | No source change. | Add long human-readable telemetry mode. |
| `code/core/control.cpp/.hpp` | No source change. | No source change. | Control-origin/error formula work belongs to Patch 5A/5B. |

## Option A Implementation Package

Use this if the user values RT1064 comparison most.

Source files:

```text
code/tracking/mainline.cpp
code/tracking/imgproc.hpp
code/types.hpp
```

Allowed changes:

1. Add a compact file-local glossary near `rpts0/rpts1/.../rptsc0/rptsc1`.
2. Add one comment before `tracking_process_frame()` that shows the real
   current flow.
3. Strengthen `build_rptsn()` public comment:

```text
selected candidate -> fixed control start -> resample -> midline_t
```

4. Strengthen `types.hpp` comments:

```text
original_pts = raw overlay boundary
now_pts      = element/corner integer work coordinate
work_pts     = floating sampled work coordinate
control_center_x = control reference fallback x
mid_position     = next-frame seed search center x
track.center_x   = published midline start x
```

Not allowed:

```text
No symbol rename.
No API change.
No function move.
No report/assistant/control changes.
```

Expected diff shape:

```text
comments only
```

Verification:

```bash
git diff --check -- code/tracking/mainline.cpp code/tracking/imgproc.hpp code/types.hpp
bash code/test.sh --host
git diff --word-diff -- code/tracking/mainline.cpp code/tracking/imgproc.hpp code/types.hpp
```

## Option B Implementation Package

Use this if the user values immediate mainline readability most.

Source files:

```text
code/tracking/mainline.cpp
code/tracking/imgproc.hpp
code/types.hpp
```

Allowed symbol renames inside `mainline.cpp` only:

```text
rpts0       -> left_work_pts
rpts1       -> right_work_pts
rpts0b      -> left_blur_pts
rpts1b      -> right_blur_pts
rpts0s      -> left_sampled_boundary
rpts1s      -> right_sampled_boundary
rptsc0      -> left_mid_candidate
rptsc1      -> right_mid_candidate

rpts0_num   -> left_work_num
rpts1_num   -> right_work_num
rpts0b_num  -> left_blur_num
rpts1b_num  -> right_blur_num
rpts0s_num  -> left_sampled_boundary_num
rpts1s_num  -> right_sampled_boundary_num
rptsc0_num  -> left_mid_candidate_num
rptsc1_num  -> right_mid_candidate_num
```

Allowed comment changes:

```text
same as Option A
```

Not allowed:

```text
Do not rename track_leftline().
Do not rename track_rightline().
Do not rename build_rptsn().
Do not rename boundary_t fields.
Do not rename runtime_t / track_result_t fields.
Do not touch CMakeLists.txt.
```

Expected diff shape:

```text
mainline.cpp local rename + comments
imgproc.hpp comment
types.hpp comment
```

Verification:

```bash
git diff --check -- code/tracking/mainline.cpp code/tracking/imgproc.hpp code/types.hpp
bash code/test.sh --host
rg -n "rpts0s|rpts1s|rptsc0|rptsc1|rpts0b|rpts1b" code/tracking/mainline.cpp
```

For Option B, the final `rg` result should only show comments if the user
chooses to keep reference-name glossary comments. It should not show live code
using both old and new array names.

## Explicitly Rejected First-Pass Changes

Do not do these in the first Stage 6 source pass:

```text
build_rptsn() -> build_control_midline()
tracking_process_frame() -> process_image()
ring -> circle
boundary.cpp -> corner.cpp
imgproc.cpp split
mainline.cpp split
runtime_t field renames
track_result_t field renames
report live key expansion
assistant protocol or point-buffer rename
track_dualline deletion
```

Reasons:

- They create broad churn.
- They hurt RT1064 comparison or log comparison.
- They can hide later behavior regressions in rename noise.

## Human Choice Required

Choose exactly one:

```text
A: Keep RT1064-style names, improve comments only.
B: Rename private mainline arrays to plain role names, keep APIs stable.
```

Recommended if the next priority is ring/control debugging:

```text
A
```

Recommended if the next priority is letting humans hand-edit `mainline.cpp`:

```text
B
```

Either path is acceptable. What is not acceptable is mixing A/B with behavior
changes.
