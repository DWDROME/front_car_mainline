# circle C search phase gate

## Goal

Delay circle C-point search until the vehicle has progressed far enough inside `BEGIN`, so C is not immediately detected on the same middle roundabout line as B and does not cause unstable `CIRCLE_REF_IN_C` transitions.

## Requirements

* Keep circle entry detection based on the existing A+B double-breakpoint logic; C must not participate in `check_circle()` entry confirmation.
* In `CIRCLE_LEFT_BEGIN` and `CIRCLE_RIGHT_BEGIN`, continue using B/A-B as the early BEGIN reference.
* Do not run or accept C search during the earliest BEGIN frames unless the phase is mature enough.
* Gate C search with existing runtime evidence where possible, such as stable B detection, B row readiness, heading progress, or begin distance.
* Preserve calibration logs so live runs can show whether C search was skipped, allowed, found, or rejected.
* Keep changes scoped to `atg_reference/Project/CODE/circle.c` unless a compile error requires a matching declaration update.

## Acceptance Criteria

* [ ] `check_circle()` still transitions into `CIRCLE_LEFT_BEGIN` / `CIRCLE_RIGHT_BEGIN` from A+B only.
* [ ] BEGIN initially allows `CIRCLE_REF_BEGIN_AB` without immediately enabling `CIRCLE_REF_IN_C`.
* [ ] C search is only attempted after the new BEGIN phase gate is satisfied.
* [ ] If C search is skipped by the phase gate, diagnostic output makes that visible when `FRONT_CAR_CIRCLE_CAL_LOG=1`.
* [ ] The modified code compiles or passes the closest available project build/check.

## Definition of Done

* Scope is minimal and reviewable.
* No hidden fallback, mock success, or swallowed error path is added.
* Existing left/right symmetry is preserved.
* Diff is reviewed before handoff.

## Technical Approach

Add a small helper that decides whether C search is allowed in BEGIN. The helper should use already tracked evidence instead of creating a second source of truth. Early BEGIN keeps B search and `CIRCLE_REF_BEGIN_AB`; once the gate is satisfied, `find_circle_C()` may run and consecutive confirmations may promote `CIRCLE_REF_IN_C`.

## Decision (ADR-lite)

**Context**: The current code already searches C inside BEGIN, but it does so immediately after B. Because the roundabout has two visible lines, B and C can both land on the middle roundabout structure and create a reference jump.

**Decision**: Keep A+B entry unchanged, but gate C search by BEGIN phase maturity. Do not redesign the whole C detector in this task.

**Consequences**: This reduces early `CIRCLE_REF_IN_C` false positives while preserving the existing state machine. C geometry may still need a later dedicated rewrite if live logs show the detector itself is selecting the wrong structure after the gate opens.

## Out of Scope

* Rewriting the complete nine-stage circle state machine.
* Porting this behavior into non-reference/mainline files.
* Retuning all gyro thresholds from live data.
* Replacing B detection or entry A+B detection.

## Technical Notes

* Primary file: `atg_reference/Project/CODE/circle.c`.
* Relevant functions: `check_circle()`, `run_circle()`, `find_circle_B_vertical()`, `find_circle_C()`, `print_circle_abc_diag()`.
* User-confirmed direction: enter BEGIN using current detection, then search C later rather than treating immediate B/C middle-ring detections as reliable.
