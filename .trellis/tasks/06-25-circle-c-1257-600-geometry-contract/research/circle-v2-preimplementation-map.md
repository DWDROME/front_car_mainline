# circle_v2 preimplementation map

## Baseline

Use the current working-tree `atg_reference/Project/CODE/circle.c` as the rewrite baseline, not raw `HEAD`.

This baseline already includes:

* `find_circle_B_vertical()` renamed to `find_circle_B()`.
* C search phase gate via `update_circle_C_search()`.
* `B_row` no longer promotes `circle_ref_mode` to `CIRCLE_REF_IN_C` by itself.
* Right BEGIN now latches A and prints `ATGCircleABCDiag`.

Do not lose these changes when writing `circle_v2.c`.

## Current owner functions

| Current function | Role | Rewrite target |
| --- | --- | --- |
| `circle_cal_log_enabled()` | Env gate for circle calibration logs. | Keep public function unchanged. |
| `print_circle_entry_probe_diag()` | `ATGCircleEntryProbe` when A exists but B search fails/rejects. | Merge into 4-event log helper. |
| `circle_heading_deg10()` | Internal heading reporting conversion. | Keep as static helper or inline in state log. |
| `print_circle_transition()` | State transition log, currently `ATGCircleCal`. | Rename/reshape as `CircleState` only if parsers are updated; otherwise preserve string. |
| `reset_circle_entry_votes()` | Public reset for entry vote counters. | `circle_reset_votes()`, public wrapper name must remain exported. |
| `suppress_circle_entry_frames()` / `suppress_circle_reentry_after_exit()` / `clear_circle_entry_suppression()` / `circle_entry_suppressed()` | Re-entry suppression after exit or external reset. | Keep behavior; side helper does not change this global throttle. |
| `reset_circle_begin_flags()` | Public reset for `none_*` / `have_*` and begin lost streaks. | Keep public function unchanged; internally reset side begin counters. |
| `reset_circle_geometry_state()` | Public reset for ref mode, A/B/C, B/C streak, search diagnostics. | `circle_reset_anchors()` plus search-diagnostic reset; public wrapper name must remain exported. |
| `update_circle_heading()` / `circle_heading_abs_ge()` / `circle_heading_enter_ready()` | Gyro integration and phase thresholds. | Keep public functions unchanged; internal helper can stay. |
| `finish_circle_exit()` | OUT -> NONE normal release and re-entry suppression. | `circle_reset_to_none(reason)` or `circle_finish_exit(reason)`; must increment `circle_count`. |
| `abort_circle_begin()` | BEGIN -> NONE when mouth loss is too late. | Same reset path as above but without incrementing `circle_count`. |
| `circle_get_raw_point()` | Convert same-side rpts id to raw A. | `circle_get_raw_point(side, id, point_t*)`. |
| `latch_circle_A()` | Save current same-side Lpt into public `circle_A_point`. | `circle_get_A(side, point_t*)` plus public anchor update. |
| `find_circle_C()` | B-relative C scan. | `circle_find_C(side, B, C)`; must still be gated by phase. |
| `circle_C_search_phase_ready()` / `update_circle_C_search()` | Prevent early C search and expose `phase_gate`. | Keep semantic contract in BEGIN. |
| `print_circle_abc_diag()` | Full ABC diagnostic, currently logs `ATGCircleABCDiag`. | Keep equivalent fields or update downstream parser at the same time. |
| `print_left_begin_diag()` / `print_right_begin_diag()` | Side-specific begin lost-line diagnostic. | Replace with side-param log helper. |
| `circle_entry_inner_seed()` | Public single source for entry seed; assistant depends on it. | Keep function signature and formula exactly unless assistant/report are updated. |
| `circle_entry_find_inner_hit_ray()` / `circle_entry_find_inner_hit_on_seed_line()` | Inner-hit proof. | `circle_inner_hit(side, A)`; preserve diagnostic gate. |
| `circle_entry_check_angle_variance()` | Diagnostic-only curvature observation. | P2/defer per PRD unless needed for logs. |
| `find_circle_B()` | A-relative B scan with skip-edge, bounded mouth window, geometric rejects, sharp-far veto. | `circle_find_B(side, A, B)`. |
| `circle_entry_find_double_breakpoint()` | Entry candidate owner: basic conditions + A raw gate + B search. | `circle_entry_candidate(side)`. |
| `circle_entry_candidate_pending()` | Public Half suppression signal. | Keep public function unchanged. |
| `check_circle()` | NONE entry voting and BEGIN transition. | Keep public function; call `circle_entry_candidate(LEFT/RIGHT)`. |
| `run_circle()` | Full left/right BEGIN/RUNNING/OUT state machine. | Thin dispatcher to `run_circle_begin/running/out(side)`. |

## External ABI and data dependencies

These names are consumed outside `circle.c`; `circle_v2.c` must still define them if it replaces `circle.c`:

* Public globals: `circle_count`, `circle_type`, `circle_ref_mode`, `circle_A_point`, `circle_B_point`, `circle_C_point`, `circle_type_name`, `none_left_line`, `none_right_line`, `have_left_line`, `have_right_line`.
* Public functions declared by `circle.h`: `check_circle`, `run_circle`, `circle_entry_candidate_pending`, reset/suppress helpers, `update_circle_heading`, `circle_heading_enter_ready`, `circle_cal_log_enabled`, `circle_entry_inner_seed`.
* `reference_step.c` reads `circle_C_point` for IN_C splicing, reads A/B/C for `ATGCircleRefDiag`, calls reset/suppress helpers, and uses `circle_entry_candidate_pending()` to suppress Half.
* `assistant.cpp` calls `circle_entry_inner_seed()` and draws `circle_B_point` / `circle_C_point`.
* `report.cpp` logs `circle_type`, `circle_ref_mode`, A/B/C, and `none/have` flags.
* `atg_reference_mainline.cpp` scales `guide_error` when BEGIN + `CIRCLE_REF_IN_C`.

Therefore `circle.h` can gain a geometry contract comment, but its ABI should stay unchanged for the first v2 pass.

## State that must survive the rewrite

| State | Purpose |
| --- | --- |
| Entry votes | Consecutive-frame confirmation before BEGIN. |
| Re-entry suppression | Prevent immediate re-detection after exit/reset. |
| Begin lost streak + loss-start distance | BEGIN abort contract for late mouth loss. |
| Heading integral | BEGIN -> RUNNING, RUNNING -> OUT, OUT -> NONE thresholds. |
| Out straight streak | OUT -> NONE release requires heading plus opposite straight. |
| B/C streaks | Ref mode promotion: B -> `BEGIN_AB`, C -> `IN_C`. |
| B/C search diagnostics | Required for live log debugging and `phase_gate` visibility. |

## Geometry contract implementation notes

* Side convention should be centralized. Current code uses `left_side == 1` for left circle and `0` for right circle.
* A is same-side near Lpt: left circle `Lpt0`, right circle `Lpt1`.
* Inner-hit uses `circle_entry_inner_seed()` and scans toward inner circle: left circle raw x decreasing, right circle raw x increasing.
* B uses A as seed, skips near edge, scans opposite arc within bounded x/y window: left circle raw x increasing and takes max x; right circle raw x decreasing and takes min x.
* C must remain phase-gated. Do not search/accept C before B is stable and reaches `CIRCLE_B_ENTER_ROW`.
* No old-frame A/B/C geometry may be reused when current-frame search fails.

## Build-switch plan

Do not add `circle_v2.c` to `DIR_SRCS` while `circle.c` is also present. Both files would define the same public globals/functions.

Recommended CMake shape:

```cmake
option(SMARTCAR_USE_CIRCLE_V2 "Build ATG circle v2 implementation" OFF)
if(SMARTCAR_USE_CIRCLE_V2)
    set(ATG_CIRCLE_SRC ../atg_reference/Project/CODE/circle_v2.c)
else()
    set(ATG_CIRCLE_SRC ../atg_reference/Project/CODE/circle.c)
endif()
```

Then replace the literal `../atg_reference/Project/CODE/circle.c` entry in `DIR_SRCS` with `${ATG_CIRCLE_SRC}`.

Validation commands:

* Existing baseline: `bash code/test.sh --host`
* v2 host build: configure host build with `-DSMARTCAR_USE_CIRCLE_V2=ON`, then build and run host tests.
* Target build: configure target build with `-DSMARTCAR_USE_CIRCLE_V2=ON`, then `bash code/test.sh` or an equivalent one-shot build command.

## Replay reality check

Existing replay/analyze can validate image-chain routing and state-machine continuity on still images, but previous PRDs note it cannot fully validate gyro/distance-driven circle phase progression unless the replay path injects IMU/encoder updates.

For this rewrite, replay is useful for:

* confirming the binary runs with v2 selected;
* checking `CircleEntryProbe` / `CircleEntryAB` / `CircleState` / `CircleABC` log shape;
* detecting obvious selected-line or guide regressions on available images.

It is not sufficient by itself to prove live BEGIN/RUNNING/OUT timing.

## Immediate blockers before implementation

1. Current working tree has uncommitted `circle.c` changes from `circle-c-search-phase-gate`; decide whether to commit them first or treat them as part of the v2 rewrite baseline.
2. The new task is active in this Codex session, but `.trellis/tasks/06-25-circle-c-search-phase-gate` remains unarchived/in-progress. Do not archive it until its code changes are committed or intentionally absorbed.
3. Implementing `circle_v2.c` requires a CMake switch; otherwise host build cannot validate v2 without replacing `circle.c` directly.
