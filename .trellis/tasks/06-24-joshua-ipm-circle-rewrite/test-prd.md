# Circle Refactor Test PRD

## Goal

Define the verification contract for the gradual circle refactor:

```text
current ATG/IPM pipeline
+ Joshua-style visual-first phase semantics
+ gyro as gate / guard
+ one-variable field validation
```

This document exists to prevent the next change from mixing three different
problems:

1. selected line geometry is biased;
2. circle phase timing is wrong;
3. the log does not expose enough evidence to decide.

If the evidence cannot separate those three cases, the next patch is diagnostic
only.

## Scope

This test PRD covers:

* Stage 0: right-circle local geometry / symmetry evidence.
* Stage 1: half-side selected-line expansion for stable `RUNNING` / `OUT`.
* Stage 2: visual-driven phase transitions with gyro gates.
* Stage 3: cleanup and documentation after field evidence.

It does not cover:

* direct Joshua raw-row `Left_Line[H]` / `Right_Line[H]` porting;
* `Longest_White_Column()` porting;
* differential control redesign;
* making `pure_angle` a control input;
* stale-frame geometry fallback.

## Test Principles

* One run should test one behavior change. Do not change geometry, thresholds,
  phase timing, and guide scaling in the same slice.
* Judge trends over at least 5-10 consecutive frames. Do not conclude from one
  frame.
* Compare right circle against the working left circle, but do not assume every
  left/right constant must be numerically mirrored. First prove the owner.
* Keep the control contract unchanged:

```text
rptsn -> guide_error -> target_yaw -> yaw_cmd -> duty
```

* Gyro thresholds are allowed as gates or guards. They are not enough evidence
  by themselves to declare a visual phase correct.
* If selected-line source is missing from logs, add explicit diagnostics before
  changing circle behavior.

## Required Static Checks

Run after every code change:

```bash
git diff --check
bash code/test.sh --host
bash code/test.sh
```

For doc-only changes, static build checks are not required, but the changed
Trellis files must be readable and linked from the task PRD.

## Live Test Commands

Use the existing live-circle script:

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh verify-build
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh upload
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run <drive_id> <duration_seconds>
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review <drive_id>
```

Required runtime environment for circle evidence:

```bash
FRONT_CAR_CIRCLE_CAL_LOG=1
FRONT_CAR_ENABLE_DRIVE=1
FRONT_CAR_PROCESS_FPS=120
FRONT_CAR_PRINT_DIV=1
```

Minimum live coverage for a behavior patch:

* right circle: slow speed and target speed, at least one full attempt each;
* left circle: at least one regression attempt after right-circle behavior
  improves;
* record the drive id, commit short hash, local log path, and patch summary.

## Required Evidence Fields

The log review must expose or derive these fields before a behavior patch is
accepted:

| Evidence | Why it matters |
| --- | --- |
| `circle_type` stream | proves whether the issue is entry, fixed action, running, out, or end. |
| selected-line source | separates fixed-left geometry from natural-line switching. |
| `rptsn_num` / selected count | proves whether the controller has a usable selected line. |
| `guide_error` trend | shows whether the selected line asks the car to move inward or outward. |
| `rpts0s/rpts1s/rptsc0/rptsc1` counts | shows near and centerline availability. |
| `far_rpts0s/far_rpts1s` counts | keeps far-line evidence available without assuming it is the selected output. |
| `Lpt0/Lpt1` and `far_Lpt0/far_Lpt1` | supports visual phase gate decisions. |
| heading / `ATGCircleCal heading_deg10` | verifies gyro gate timing. |
| distance / lost counters | separates timeout fallback from normal phase advance. |

If `selected-line source` is not visible in the current frame output, Stage 0
starts with a diagnostic patch only. Do not tune geometry blind.

## Review Order

Review every live log in this order:

1. Check `ATGCircleCal` and entry candidate evidence.
2. List circle state progression and frame ranges.
3. Identify selected-line source through each circle phase.
4. Inspect 5-10 frame windows around each phase transition.
5. Inspect guide / yaw trend while selected line is non-empty.
6. Inspect the final 50 frames for stall, reset, or silent no-line behavior.

This order matters because "right circle went inner" can be caused by different
owners depending on whether the selected line existed and which source produced
it.

## Stage 0 Test Matrix: Right-Circle Local Evidence

Stage 0 is the first guardrail for the current pain point: right circle drives
near the inner side.

### Stage 0A: Evidence Run

No behavior edit yet.

Pass condition:

* right circle enters a non-`NONE` circle state, or the log proves why it did
  not enter;
* a 5-10 frame window exists for `CIRCLE_RIGHT_IN`, `CIRCLE_RIGHT_RUNNING`, or
  `CIRCLE_RIGHT_OUT`;
* selected-line source and `guide_error` can be tied to that window.

Fail / next action:

* if selected-line source is missing, add diagnostics first;
* if the run never enters right circle, do not tune fixed-line geometry yet;
* if the run only has one isolated right-circle frame, collect another run.

### Stage 0B: Owner Decision

Use this decision table before editing:

| Evidence pattern | First owner to change | Do not change yet |
| --- | --- | --- |
| selected source stays `circle_*_fixed_left`, `rptsn` is non-empty, guide trend points inner | `reference_step.c::build_fixed_left_center_for_circle()` | gyro thresholds, END distance |
| source switches away from fixed-left during `RIGHT_RUNNING`, then guide or selected count degrades | `reference_step.c::circle_right_running_natural_left_ready()` | fixed-left geometry |
| selected count drops to zero in `RIGHT_OUT` while far/near evidence exists | Stage 1 selected-line policy | phase thresholds |
| phase advances early or late while selected line itself looks sane | `circle.c::run_circle()` visual gate | fixed-line geometry |
| right entry candidate exists but vote/suppression blocks entry | `circle.c::check_circle()` entry evidence | OUT / END logic |

### Stage 0C: First Patch Acceptance

The first Stage 0 behavior patch passes only if:

* it changes one owner only;
* right-circle evidence improves in the targeted window;
* left circle still progresses through its previous working phases;
* `guide_error` does not clamp continuously because of the new selected line;
* no new empty-selected-line window appears in the same phase.

## Stage 1 Test Matrix: Half-Side Selected Line

Goal: make `RUNNING` / `OUT` selected-line output stable without relying on a
fragile far-line splice.

Precondition:

* Stage 0 has identified whether the selected-line problem is geometry,
  switching, or no-line output.

Pass condition:

* `RUNNING` / `OUT` keeps a non-empty selected line for at least 10 consecutive
  circle frames;
* selected-line source is a known half-side source;
* guide trend is smooth enough to avoid continuous clamp;
* left-circle regression still has non-empty selected line through its known
  working path.

Fail / next action:

* if selected line is stable but the phase is wrong, move to Stage 2 instead of
  tuning geometry again;
* if selected source toggles between two sources, fix selection priority before
  changing geometry constants.

## Stage 2 Test Matrix: Visual Phase + Gyro Gate

Goal: move from pure gyro-driven phase transitions toward visual triggers with
gyro gates.

Each transition must be changed and tested independently:

| Transition | Normal trigger | Gyro role | Required proof |
| --- | --- | --- | --- |
| `IN -> RUNNING` | fixed-action visual progress / stable selected line | guard or timeout only | selected line is sane before transition. |
| `RUNNING -> OUT` | opposite-side visual feature or rpts/IPM monotonic change | open judgment after enough heading | visual feature appears after gyro gate opens. |
| `OUT -> END` | exit visual evidence / selected-line recovery | force-out guard only | no long zero-selected-line stall before END. |
| `END -> NONE` | stable ordinary-road evidence or distance completion | fallback only | no early release into empty selected line. |

Pass condition:

* visual evidence explains the transition in the reviewed frame window;
* gyro gate prevents obviously early false positives;
* distance or gyro fallback is logged as fallback, not silently treated as the
  normal path.

Fail / next action:

* if a transition depends only on heading in normal runs, the Stage 2 goal was
  not met;
* if a visual trigger fires before the gyro gate, tighten the gate before
  changing selected-line geometry.

## Stage 3 Test Matrix: Cleanup

Cleanup is allowed only after field evidence shows the new path is stable.

Pass condition:

* obsolete diagnostics or bypasses are removed only when no current test relies
  on them;
* docs and Trellis task notes describe the final owner chain;
* validation commands and live logs are listed in the task closeout.

Do not remove gyro thresholds, legacy evidence logs, or fallback guards just
because one run passed.

## Regression Checks

Every behavior patch must answer:

* Did right circle improve in the targeted phase?
* Did left circle keep its previous working behavior?
* Did selected-line count stay non-zero where the controller needed it?
* Did `guide_error` remain interpretable, not silently zero because selected
  line disappeared?
* Did the patch preserve the differential control boundary?

## Rollback Rules

Rollback is per owner:

* fixed-line geometry patch fails -> revert that geometry patch only;
* natural-line readiness patch fails -> revert that gate only;
* visual phase gate patch fails -> revert that transition only;
* diagnostic patch is noisy but harmless -> keep only if it helps the next
  evidence decision.

Do not stack a second behavior patch on top of a failed first patch to hide the
failure. Re-establish the baseline, then test again.

## Acceptance Criteria

This test PRD is complete when:

* every implementation stage has a concrete pass/fail contract;
* Stage 0 can decide between geometry, selection switching, phase timing, and
  missing diagnostics;
* the live script and required environment are documented;
* control-layer boundaries are explicitly protected;
* the main task PRD links to this document.
