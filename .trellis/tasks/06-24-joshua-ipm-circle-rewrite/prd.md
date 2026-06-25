# brainstorm: Joshua 9-stage IPM circle rewrite

## Goal

Clarify the current circle recognition and control-output flow before changing
the algorithm. The immediate focus is the asymmetry where the left circle works
but the right circle drives close to the inner side.

## What I Already Know

* User wants a direct explanation of the circle recognition flow first.
* User does not want sub-agents for this work.
* Longer-term direction is to evaluate and likely rewrite toward Joshua.Xu's
  9-stage circle logic.
* Current project is IPM-based; Joshua.Xu's original implementation uses raw
  image coordinate assumptions, so direct copying is unsafe.
* Enterprise_E corresponds to the ATG reference source, not Joshua.Xu.
* The active ATG port currently recognizes circle entry in `check_circle()`,
  advances phases in `run_circle()`, and chooses the actual line in
  `reference_step.c::select_work_line()`.
* User chose the rewrite philosophy: visual-first + gyro-gated, implemented
  gradually.

## Requirements

* Explain the active circle flow in simple terms before making more changes.
* Compare the state machines of ATG native `round.c`, current active
  `circle.c`, and Joshua.Xu `Island.c` before deciding a rewrite shape.
* Keep left-circle and right-circle behavior separate when auditing symptoms.
* Treat right-circle inner-side bias as a selected-line / fixed-line geometry
  question first, not as a control-layer steering rewrite.
* Keep gyro as a gate / guard for phase transitions rather than the only normal
  phase driver.
* Make the first implementation step evidence-driven and local; do not combine
  threshold, geometry, and state-machine changes in one run.
* Do not use sub-agents.

## Acceptance Criteria

* [x] Current circle entry, state advance, selected-line output, and control
      handoff are mapped with file/function evidence.
* [x] The likely right-circle failure points are listed in plain language.
* [x] ATG native/current/Joshua state machines are compared in a Trellis
      research artifact.
* [x] The visual-first gyro-gated gradual direction is recorded.
* [ ] Any later behavior change includes reference/current/rationale evidence.

## Out of Scope

* No algorithm rewrite in this first explanation step.
* No control-layer `pure_angle` or direct yaw special case.
* No stale-frame geometry fallback.

## Technical Notes

* Current state machine owner: `atg_reference/Project/CODE/circle.c`.
* Selected circle line owner: `atg_reference/port/reference_step.c`.
* Reference 2 real project: `E:\longxin\参考2\the-18th-smartcar`.
* Reference comparison: `research/circle-reference-comparison.md`.
* State-machine comparison:
  `research/circle-state-machine-comparison.md`.
* Gradual rewrite plan:
  `research/vision-first-gyro-gated-plan.md`.
* Technical design / implementation guardrails:
  `info.md`.
* Test PRD / validation contract:
  `test-prd.md`.
* Relevant specs:
  * `.trellis/spec/tracking/critical-audit-guide.md`
  * `.trellis/spec/quality/embedded-tracking-guidelines.md`

## Research References

* [`research/circle-reference-comparison.md`](research/circle-reference-comparison.md)
  — compares ATG/Enterprise_E, Joshua.Xu real project, and ittuann ring
  references for the right-circle inner-side investigation.
* [`research/circle-state-machine-comparison.md`](research/circle-state-machine-comparison.md)
  — compares disabled ATG `round.c`, active `circle.c`, and Joshua.Xu
  `Island.c` state-machine shapes.
* [`research/vision-first-gyro-gated-plan.md`](research/vision-first-gyro-gated-plan.md)
  — records the chosen visual-first + gyro-gated direction and the first local
  evidence-driven change candidates.
* [`research/stage-3-cleanup-and-rationale.md`](research/stage-3-cleanup-and-rationale.md)
  — records cleanup, rationale table, and remaining live validation contract
  after the first implementation slice.
* [`test-prd.md`](test-prd.md)
  — defines the staged static/live validation contract, right-circle owner
  decision table, required logs, and rollback rules.

## Decision (ADR-lite)

**Context**: ATG visual gates were hard to tune, but the current pure-gyro
direction loses visual self-correction and creates several sensitive thresholds.
Joshua's raw-row implementation cannot be copied into the current IPM point-set
pipeline, but its phase philosophy fits the observed problem.

**Decision**: Keep the current ATG/IPM data path and move gradually toward
Joshua-style visual phase semantics, with gyro used as a gate or guard.

**Consequences**: The first implementation must be small and evidence-driven.
Right-circle inner-side bias should first be diagnosed through selected-line
source and `guide_error` trend, then fixed either in fixed-left geometry or the
natural-left readiness gate before broader state-machine work.

## Technical Approach

Implementation is staged:

1. Stage 0: right-circle local symmetry/geometry, one variable only.
2. Stage 1: half-side selected-line expansion for stable `RUNNING/OUT`.
3. Stage 2: visual-driven phase transitions with gyro gates.
4. Stage 3: cleanup after field evidence.

The first code patch must pass the evidence gate in `info.md`; it should not
change thresholds, fixed-line geometry, and state timing together.

## Implementation Plan

* PR1 / Stage 0 evidence: inspect or collect right-circle log slice with
  selected source, counts, heading, and guide trend.
* PR2 / Stage 0 first patch: change exactly one proven owner
  (`build_fixed_left_center_for_circle()`,
  `circle_right_running_natural_left_ready()`, or one verified asymmetric
  threshold).
* PR3 / Stage 1-2: after Stage 0 evidence, move one circle phase at a time
  from pure gyro drive toward visual trigger + gyro gate.
