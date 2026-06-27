# cross farline mechanical split

## Goal

Mechanically split the large `cross_farline_L()` and `cross_farline_R()` functions in `atg_reference/Project/CODE/cross.c` into short, readable same-side helper steps without changing tracking behavior. The goal is to make the far-line pipeline readable while keeping all existing global-state behavior and current threshold/judgment logic intact.

## What I already know

* The user-provided review explicitly says the current outer cross state cleanup is acceptable, but `cross_farline_L()` and `cross_farline_R()` remain too large.
* The requested next step is a mechanical split only: no algorithm changes, no judgment-condition changes, no new structs, no generic side parameter, no large parameter list.
* Existing worktree already contains uncommitted `cross.c` / `cross.h` state cleanup changes, including `reset_cross_state()` and `clear_cross_farline_outputs()`.
* Current `cross_farline_L()` contains seed/cut, scan/trace, IPM, filtering/resampling/angle/NMS, and far L-point detection.
* Current `cross_farline_R()` contains the same pipeline plus left-circle OUT dynamic seed diagnostics.
* `cross_farline()` is a separate older two-side function and is out of scope for this task.

## Assumptions

* The task should build on the current dirty worktree and must not revert earlier cleanup changes.
* Helper functions can remain `static` in `cross.c` and can keep using existing globals.
* The right-side circle-out seed logic should be extracted as a named helper, but its internal conditions and logging text should remain unchanged.

## Requirements

* Keep `cross_farline_L()` as a short workflow wrapper with same-side helper calls such as `far_l_seed()`, `far_l_cut()`, `far_l_scan()`, `far_l_trace()`, `far_l_ipm()`, `far_l_proc()`, and `far_l_find_lpt()`.
* Keep `cross_farline_R()` as a short workflow wrapper with same-side helper calls such as `far_r_seed()`, `far_r_cut()`, `far_r_scan()`, `far_r_trace()`, `far_r_ipm()`, `far_r_proc()`, and `far_r_find_lpt()`.
* Do not introduce a shared `side` abstraction, config struct, context struct, or large parameter-passing API.
* Continue using existing global variables and existing image/point buffers.
* Preserve the current order of operations and existing side effects.
* Preserve all thresholds, constants, branch conditions, logging text, and display behavior unless a compile issue forces a purely mechanical local declaration adjustment.
* Keep edits scoped to `cross.c` unless prototypes or build requirements make another file necessary.
* Make `far_l_seed()` and `far_r_seed()` return `1` only when they set a same-side raw search seed; callers must return early on failure instead of scanning from an old seed.
* Make `far_l_scan()` and `far_r_scan()` return `1` only when they find a valid `far_y1`; callers must return early on failure.
* Store the scan threshold in file-local `far_l_thres` / `far_r_thres` so `far_l_trace()` and `far_r_trace()` stay parameterless.
* Make same-side L-point finders clear only their own found flag, not the opposite side flag.

## Acceptance Criteria

* [x] `cross_farline_L()` is reduced to a short sequence of helper calls.
* [x] `cross_farline_R()` is reduced to a short sequence of helper calls.
* [x] The right circle-out dynamic seed block is behind a named helper such as `far_r_seed_circle_out()`.
* [x] No generic left/right abstraction or new data structure is added.
* [x] `far_l_seed()` / `far_r_seed()` return success/failure and wrappers stop on failure.
* [x] `far_l_scan()` / `far_r_scan()` return success/failure and wrappers stop on failure.
* [x] `far_l_find_lpt()` only clears `far_Lpt0_found`; `far_r_find_lpt()` only clears `far_Lpt1_found`.
* [x] `git diff --check` passes.
* [x] The narrowest available compile/build check for the affected firmware code is run, or a concrete reason is recorded if it cannot be run.

## Out of Scope

* Changing cross, circle, or ramp state-machine semantics.
* Changing thresholds, geometric constants, or L-point detection conditions.
* Refactoring `run_cross()` beyond what already exists.
* Refactoring `cross_farline()` or deleting additional legacy code.
* Adding new diagnostics beyond preserving existing logs/displays.

## Technical Notes

* Relevant file inspected: `atg_reference/Project/CODE/cross.c`.
* Relevant spec indexes inspected: `.trellis/spec/quality/index.md`, `.trellis/spec/tracking/index.md`, `.trellis/spec/guides/index.md`.
* Quality constraints: small diff, no hidden fallback, no second truth source, no stale geometry fallback, explicit validation.

## Validation

* `git diff --check` passed.
* `./test.sh --host` passed; it rebuilt `atg_reference/Project/CODE/cross.c` and ran `config_parsing_test` / `options_parsing_test`.
* `./test.sh` passed; it rebuilt the cross-compiled `front_car_mainline` target including `cross.c`.

## Spec Update Decision

No `.trellis/spec/` update is needed for this task. The change follows the existing pure-refactor discipline and does not introduce a new executable contract, threshold, API, state-machine rule, diagnostic convention, or cross-layer behavior.
