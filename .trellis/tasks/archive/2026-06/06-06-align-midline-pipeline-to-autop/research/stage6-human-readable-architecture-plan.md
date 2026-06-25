# Stage 6 Human-Readable Architecture Plan

Updated: 2026-06-06 14:27:11 +0800.

Scope: design only. No source edit in this review.

## Position

Stage 6 is not optional cleanup.

It is the human-maintenance stage for this tracking refactor. The goal is to
make the algorithm easy to read, compare with RT1064, and modify later without
re-learning the whole pipeline each time.

This stage must decide naming, file boundaries, and file-level flow before any
large source cleanup. It must not mix behavior changes such as ring transitions,
control origin, `guide_error`, seed acquisition, or PID tuning.

## Why This Stage Is Heavy

The current source already has a clearer midline contract after Stage 1 and
Stage 2:

```text
seed / trace
-> rpts0s / rpts1s
-> rptsc0 / rptsc1
-> element side and crop action
-> selected candidate
-> build_rptsn()
-> rt->track.mid
-> guide_error / control / assistant red line
```

However, readability still depends on knowing both the local code and the
RT1064 reference names. That is fragile for human review.

The main tension:

```text
RT1064-style names help reference comparison:
  rpts0s / rpts1s / rptsc0 / rptsc1 / rptsn / build_rptsn()

Plain role names help new maintainers:
  left_sampled_boundary / right_sampled_boundary
  left_mid_candidate / right_mid_candidate
  build_control_midline()
```

Both goals are valid. Stage 6 must choose a direction explicitly.

## Three-Agent Review Summary

### Naming Review

Finding:

- `rpts0/rpts1/rpts0b/rpts1b/rpts0s/rpts1s/rptsc0/rptsc1` are the hardest
  names for new readers.
- `build_rptsn()` hides an important responsibility: it chooses a start point,
  overwrites it with the control reference, resamples, fills `dist[]`, and
  writes final `midline_t`.
- `original_pts / now_pts / work_pts` are easy to misuse because they mix raw
  coordinates, element coordinates, and floating work coordinates.
- `center_x / control_center_x / mid_position` are three different "centers";
  this should be made more explicit before control-origin work.

Recommendation from this review:

```text
Prefer plain role names where they cross file boundaries or drive human
decision-making.
```

### File Boundary Review

Finding:

- `mainline.cpp` should remain the frame-level orchestrator for now.
- `imgproc.cpp` is large, but currently acts as the RT1064-like low-level image
  processing kernel. Splitting it now would create include/CMake churn.
- `boundary.cpp`, `element.cpp`, `cross.cpp`, `ring.cpp`, and `zebra.cpp` have
  acceptable file ownership.
- `assistant.cpp` and `report.cpp` are observation layers and must not become
  algorithm owners.

Recommendation from this review:

```text
Do not physically split files in the first Stage 6 source pass.
First fix vocabulary and flow visibility.
```

### Risk Review

Finding:

- Renaming `rptsc0/rptsc1/rptsn/build_rptsn()` can break direct RT1064
  comparison.
- Splitting `mainline.cpp` or `imgproc.cpp` now would create a large diff while
  ring/control behavior is still being validated.
- Renaming `runtime_t`, `track_result_t`, `guide_error`, or public enum fields
  has high churn and low immediate benefit.

Recommendation from this review:

```text
Keep reference-style algorithm names for now, but document them more directly.
Do only source comments / local helper naming if the user approves.
```

## Synthesis

The reviews disagree on whether `rptsc/build_rptsn` should be renamed. That is
the real Stage 6 decision.

Recommended synthesis:

```text
Stage 6A: Decide vocabulary.
Stage 6B: Add a visible flow map and improve comments.
Stage 6C: Optionally rename only private helpers after vocabulary is chosen.
Stage 6D: Defer physical file splitting until ring/control behavior is stable.
```

This is direct, but not reckless: it treats readability as important without
turning a naming stage into a behavior-changing refactor.

## File-Level Flow Contract

### `code/tracking/mainline.cpp`

```text
Input:
  runtime_t gray / matrix / seed state / element state

Method:
  frame orchestration
  seed -> trace -> boundary -> candidate centerline
  element state update
  element crop
  selected midline build
  final reject gate
  zebra scan dispatch

Output:
  rt->track.mid
  rt->track.track_type
  rt->track.guide_error
  rt->track.reject_reason

Downstream:
  code/core/control.cpp
  code/app/report.cpp
  code/app/assistant.cpp
```

Do not make it own low-level tracing or control/PID.

### `code/tracking/imgproc.cpp`

```text
Input:
  raw gray
  seed points
  raw trace points
  work point arrays

Method:
  threshold
  seed search
  trace
  perspective point mapping
  blur / resample
  single-side candidate centerline
  normalized control midline build

Output:
  seed_pair_t
  trace_t
  work point arrays
  candidate centerline arrays
  midline_t

Downstream:
  mainline.cpp
  boundary.cpp
  cross.cpp
  ring.cpp
  zebra.cpp
```

Do not make it own frame decisions, element states, or control output.

### `code/tracking/boundary.cpp`

```text
Input:
  trace_t
  matrix / has_matrix
  sampled left/right work points

Method:
  build boundary_t
  refresh L corners
  check double-L pair geometry
  check straight boundary

Output:
  boundary_t left/right corner and straight state

Downstream:
  mainline.cpp
  cross.cpp
  ring.cpp
  assistant.cpp
  report.cpp
```

Do not make it build the final control midline.

### `code/tracking/element.cpp`

```text
Input:
  rt->track.left/right
  rt->cross
  rt->ring

Method:
  cross first
  ring only when cross is inactive
  element mutual exclusion

Output:
  rt->cross
  rt->ring

Downstream:
  mainline.cpp frame mode classification
```

Do not place zebra here. Zebra scans a selected line after midline selection.

### `code/tracking/cross.cpp`

```text
Input:
  boundary L-corners
  raw gray
  matrix
  trace helpers

Method:
  NONE -> BEGIN -> IN
  BEGIN crops near line
  IN builds farline points

Output:
  rt->cross.state
  rt->cross.track_type
  rt->cross.left_pts / right_pts
  rt->cross.left_l / right_l

Downstream:
  mainline.cpp::solve_cross_mid()
```

Do not write `rt->track.mid` here.

### `code/tracking/ring.cpp`

```text
Input:
  boundary L-corners
  straight-boundary checks
  encoder_total

Method:
  NONE -> BEGIN -> IN -> RUN -> OUT -> END
  may use build_opp() for detection/state continuity

Output:
  rt->ring.kind
  rt->ring.state
  optional boundary edits for ring continuity

Downstream:
  mainline.cpp frame-start ring action and crop
```

Do not rebuild current-frame control candidates from ring-edited `boundary_t`
unless a later behavior task explicitly changes the owner contract.

### `code/tracking/zebra.cpp`

```text
Input:
  raw gray
  selected scan midline

Method:
  convert midline points back to raw
  scan both sides for black/white segments
  scan bottom row for stop line

Output:
  rt->zebra.detected
  rt->zebra.stop_line

Downstream:
  report / control stop logic
```

Do not choose the scan midline here. `mainline.cpp` chooses it.

### `code/app/assistant.cpp`

```text
Input:
  runtime_t
  raw left/right boundary
  rt->track.mid
  cross farline state

Method:
  project control midline back to raw
  draw raw boundaries, real control red line, farline, L corners
  send upper-computer frame

Output:
  display only

Downstream:
  human visual debugging
```

Do not use assistant red line as algorithm input.

### `code/app/report.cpp`

```text
Input:
  runtime_t

Method:
  print live frame summary
  write detail report

Output:
  text diagnostics only

Downstream:
  human debugging
```

Do not make report fields drive behavior.

### `code/core/control.cpp`

```text
Input:
  rt->track.guide_error
  track_line_found(rt)
  feedback
  config

Method:
  guide_error -> target_yaw
  optional yaw-rate PI feedback
  differential duty output

Output:
  rt->control

Downstream:
  drive output
```

Do not change it in Stage 6.

## Vocabulary Decision Options

### Option A: Keep Reference Names, Add Human Glossary

Keep these names:

```text
rpts0s / rpts1s
rptsc0 / rptsc1
build_rptsn()
track_leftline()
track_rightline()
```

Add explicit comments and documentation:

```text
rpts0s/rpts1s = sampled left/right boundary
rptsc0/rptsc1 = left/right candidate control centerline
rptsn = normalized selected control midline
build_rptsn() = selected candidate -> rt->track.mid
```

Pros:

- Best RT1064 comparison.
- Smallest source churn.
- Keeps Stage 1/2 diffs easy to audit.

Cons:

- New reader must learn reference shorthand.
- Human readability depends on comments.

### Option B: Rename Private Mainline Arrays To Plain Role Names

Example target names:

```text
rpts0s      -> left_sampled_boundary
rpts1s      -> right_sampled_boundary
rptsc0      -> left_mid_candidate
rptsc1      -> right_mid_candidate
rptsc0_num  -> left_mid_candidate_num
rptsc1_num  -> right_mid_candidate_num
```

Keep low-level RT1064 primitive names:

```text
track_leftline()
track_rightline()
build_rptsn()
```

Pros:

- Mainline becomes easier to read.
- Reference primitive names remain.
- Diff is mostly inside `mainline.cpp`.

Cons:

- Mixed naming: plain arrays, reference function names.
- Reference comparison needs a glossary.

### Option C: Rename Final Builder Too

Example target:

```text
build_rptsn() -> build_control_midline()
```

Pros:

- Most direct for a human reader.
- Makes final ownership obvious.

Cons:

- Loses the strongest reference-name anchor.
- Touches `imgproc.hpp`, `imgproc.cpp`, and all callers.
- Should wait until Stage 5 control-origin/error choices are stable.

## Recommended Stage 6 Path

Recommended now:

```text
Choose Option A or B first.
Do not choose Option C yet.
Do not split files yet.
Do not rename public runtime/control/report fields yet.
```

If the user values RT1064 comparison most:

```text
Use Option A.
Stage 6 source pass = comments + flow section only.
```

If the user values immediate human readability most:

```text
Use Option B.
Stage 6 source pass = private `mainline.cpp` array rename + comments.
```

Both are valid. The wrong choice is mixing Option B/C with ring/control behavior
changes.

## Human Decision Questions

1. Should `rpts0s/rpts1s/rptsc0/rptsc1` stay as RT1064-style names, or become
   plain role names inside `mainline.cpp`?
2. Should `build_rptsn()` stay for RT1064 comparison, or eventually become
   `build_control_midline()`?
3. Should `track_leftline()` / `track_rightline()` stay as reference primitive
   names?
4. Should `boundary_t::original_pts/now_pts/work_pts` be renamed now, or only
   clarified by comments?
5. Should `center_x/control_center_x/mid_position` be renamed now, or deferred
   until Patch 5A control-origin work?
6. Should `frame_action_t/frame_mode_t` be renamed to show frame-start timing
   more explicitly?
7. Should `ring.cpp::build_opp()` be renamed to make "detection-only synthetic
   opposite boundary" obvious, or kept until ring behavior is stable?
8. Should `report.cpp` live output get longer human-readable field names, or
   keep compact keys for real-time use?
9. Should `assistant.cpp` be split into transport and overlay later, or remain
   one display adapter?
10. Should `imgproc.cpp` eventually split into seed/trace/point/midline files,
    or stay RT1064-like as one algorithm kernel?
11. Should `mainline.cpp` eventually split into line-output and frame
    orchestration files, or remain the single readable pipeline owner?
12. Should Stage 6 source work be only comments/flow map first, or include
    private `mainline.cpp` renames in the same patch?

## Source Change Gate

Before any Stage 6 source pass, lock these rules:

```text
No behavior changes.
No seed acquisition changes.
No ring/cross state transition changes.
No control origin or guide_error changes.
No PID/control changes.
No assistant protocol changes.
No public runtime_t field rename unless explicitly selected.
No physical file split unless explicitly selected.
```

Minimal verification for a source pass:

```bash
git diff --check -- code
bash code/test.sh --host
git grep -n "rptsc0\\|rptsc1\\|build_rptsn" -- code
```

For a rename pass, also verify no mixed old/new names remain in the touched
scope.
