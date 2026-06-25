# Naming And File Boundary Plan

Updated: 2026-06-06 11:59:42 +0800.

Scope: brainstorm only. No source implementation in this task.

## Core Position

Use RT1064 names where they clarify the algorithm contract, not where they only rename wrappers.

The first cut should not add files. The current file set is enough:

```text
code/tracking/imgproc.hpp/.cpp   low-level image/point operations and centerline primitives
code/tracking/boundary.hpp/.cpp  boundary interpretation and corner finding
code/tracking/mainline.cpp       frame orchestration and selected control midline
code/tracking/cross.cpp          cross state and farline construction
code/tracking/ring.cpp           ring state and current project-specific boundary edits
code/tracking/zebra.cpp          zebra scan over selected control midline
```

## Rename / Keep Table

| Current | Reference relation | First-cut decision | Reason |
|---|---|---|---|
| `tracking_process_frame()` | Similar to RT1064 frame loop around `process_image()`, element runs, centerline selection, and control error. | Keep name. | It is much broader than RT1064 `process_image()`. Renaming it would be false alignment. |
| `find_seeds()` | Covers RT1064 `process_image()` seed start part plus local missing-side upward search. | Keep name. | Reference has no function boundary here; current name is clear. |
| `trace_single()` | Public wrapper around left/right maze tracing. | Keep name. | It validates seed, chooses side, and returns a `trace_t`; it is not exactly `findline_lefthand_adaptive()`. |
| private `trace_left()` / `trace_right()` | Correspond to RT1064 `findline_lefthand_adaptive()` / `findline_righthand_adaptive()`. | Optional later rename only. | Not needed for first cut; renaming private helpers can be done after behavior settles. |
| `region_otsu()` / `frame_seed_threshold()` | Similar to RT1064 `getOSTUThreshold()`. | Keep names. | Current names are clearer and avoid copying old `OSTU` spelling / `image_t` interface. |
| `perspective_points()` | Corresponds to RT1064 point-wise `mapx/mapy` mapping in `process_image()`. | Keep name. | Do not rename to `remap()`: RT1064 `remap()` means whole-image mapping. |
| `blur_points()` | Same reference name. | Keep. | Already aligned. |
| `resample_points()` | Same reference name. | Keep. | Already aligned. |
| `track_leftline()` / `track_rightline()` | Same reference name, but current semantics are too broad. | Keep name, change semantics in first implementation task. | These should become pure candidate-centerline functions like RT1064 `imgproc.c:611-635`. |
| `track_leftline_from_start()` / `track_rightline_from_start()` | Current adapter for RT1064 `CROSS_IN begin_id = 0`. | Remove only after `build_rptsn(force_begin_id0)` replaces all callers. | Do not leave two final-midline generators after first cut. Also do not delete them without replacement. |
| `build_rpts0()` / `build_rpts1()` | Encapsulate RT1064 `process_image()` point pipeline for each side. | Keep. | Directly maps to `rpts0/rpts1/rpts0b/rpts0s`. |
| `refresh_boundary_corners()` | Corresponds to RT1064 `find_corners()`. | Keep. | Current `boundary.cpp` is the correct owner; do not create `corner.cpp` in first cut. |
| `lookahead_error()` | Corresponds to reference aim/error calculation, not all pure pursuit math. | Keep in first cut; later consider `calc_aim_error()`. | Avoid mixing naming cleanup with midline ownership split. |
| `midline_has_lookahead()` | Project-specific strict ordinary-road gate. | Keep. | RT1064 clips aim index; current project still wants ordinary no-line safety. |
| `cross_process()` | Combines RT1064 `check_cross()` + `run_cross()` plus local farline build. | Keep. | Splitting check/run is a later element cleanup, not first cut. |
| `build_cross_farline()` | Builds one side of farline. | Keep. | Do not rename to `cross_farline()` because reference function builds both sides and owns more globals. |
| `ring_process()` | Combines RT1064 `check_circle()` + `run_circle()`. | Keep. | Do not rename files/types from ring to circle in first cut. |
| `zebra_process()` | Project-specific zebra scan. | Keep. | No direct reference target in the current RT1064 files used for this pass. |
| `control_mid_pts()` | Assistant display adapter. | Keep. | Good direct name for red-line display from final control midline. |

## New Names To Introduce

Preferred first-cut names:

```text
rptsc0, rptsc1     candidate centerlines from left/right side boundary
rpts, rpts_num     selected candidate centerline pointer/count
rptsn              normalized control midline workspace
rptsn_num          normalized count before writing midline_t
begin_id           selected begin index before normalization
cx, cy             fixed control start point
force_begin_id0    special mode flag, initially CROSS_IN only
build_rptsn()      selected candidate -> normalized midline_t
```

`build_rptsn()` is intentionally reference-like. It should be documented as the only place that:

```text
finds begin_id
overwrites selected begin with cx/cy
resamples selected tail
fills rt->track.mid.pts/dist/step
```

## File Boundary Decision

First implementation task should touch only:

```text
code/tracking/imgproc.hpp
code/tracking/imgproc.cpp
code/tracking/mainline.cpp
```

Possible compile-only touch if declarations force it:

```text
none expected
```

Do not touch in first cut:

```text
code/types.hpp
code/tracking/cross.cpp
code/tracking/ring.cpp
code/tracking/zebra.cpp
code/app/assistant.cpp
code/app/report.cpp
code/core/control.cpp
```

Exception: `zebra` currently depends on old `track_leftline/rightline()` through `build_zebra_mid()` in `mainline.cpp`, not in `zebra.cpp`. Adapt this call site inside `mainline.cpp`; do not edit `zebra.cpp` in first cut.

## First-Cut Non-Renames

Do not rename:

```text
tracking_process_frame -> process_image
trace_single -> findline_*_adaptive
perspective_points -> remap
ring.* -> circle.*
cross_process -> run_cross/check_cross split
ring_process -> run_circle/check_circle split
zebra_process -> garage_process
```

These are not harmless names. Each would imply ownership or flow changes beyond the first cut.
