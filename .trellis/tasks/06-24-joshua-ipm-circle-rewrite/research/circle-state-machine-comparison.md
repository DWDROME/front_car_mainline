# Circle State Machine Comparison

## Purpose

The user clarified the immediate goal: compare ATG original/current/Joshua
state machines first. This document focuses on state-machine shape and evidence
owners, not on implementing a fix.

## Which ATG Circle Path Is Active

`atg_reference/port/reference_step.c` defaults:

```c
#define ATG_ENABLE_CIRCLE 1
#define ATG_ENABLE_ROUND 0
```

Therefore:

* `circle.c` is the active circle path.
* `round.c` is present but disabled by default.
* `keep_disabled_elements_idle()` forces `round_type = ROUND_NONE` when
  `ATG_ENABLE_ROUND` is off.
* `run_atg_elements()` would call `check_round()` / `run_round()` only behind
  `#if ATG_ENABLE_ROUND`.

Conclusion: current live behavior comes from `circle.c` plus the selected-line
logic in `reference_step.c`. `round.c` is still useful as an ATG-native
comparison because it uses the same Lpt/rpts/farline tool family.

## Data-Structure Baseline

| Implementation | Boundary representation | Geometry helpers | Copy risk |
| --- | --- | --- | --- |
| ATG `round.c` | `rpts0s/rpts1s`, `rptsc0/rptsc1`, `Lpt0/Lpt1`, far Lpt | `cross_farline_L/R`, clipping, `track_type` | Low conceptual risk; same family as current port, but disabled and simpler. |
| Current `circle.c` | same ATG point-set family plus gyro state | `cross_farline_L/R`, fixed IPM selected-line builders in `reference_step.c` | Active code; already modified toward gyro/fixed action. |
| Joshua `Island.c` | raw per-row arrays `Left_Line[H]`, `Right_Line[H]` | longest white column, continuity tear, monotonicity change, slope draw | High direct-copy risk; must translate semantics to ATG/IPM point-set representation. |

## ATG `round.c`: Disabled Native Reference

State enum:

```text
ROUND_NONE
ROUND_LEFT_BEGIN / ROUND_RIGHT_BEGIN
ROUND_LEFT_IN    / ROUND_RIGHT_IN
ROUND_LEFT_END   / ROUND_RIGHT_END
```

Plain state flow:

1. `check_round()` detects candidate by shared Lpt + straight-line evidence:
   * left: `Lpt0_found && is_straight1 && Lpt0_rpts0s_id < 30`
   * right: `Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 30`
2. `check_round_L/R()` calls `cross_farline_L/R()` and requires far Lpt before
   entering `ROUND_*_BEGIN`. This also overlaps with garage handling.
3. `BEGIN` tracks the outside line and waits for inner-line disappearance then
   reappearance.
4. `IN` continues outside-line tracking until opposite Lpt appears.
5. `END` clips the opposite-side line around Lpt, waits for distance and line
   evidence, then resets to `ROUND_NONE`.

Important lesson:

`round.c` proves ATG's native point-set pipeline can implement a circle-like
state machine without Joshua-style raw row arrays. It is not the target behavior
because it is coarse and garage-coupled, but its primitives are compatible with
the current project.

## Current `circle.c`: Active ATG Port

State enum:

```text
CIRCLE_NONE
CIRCLE_LEFT_BEGIN  / CIRCLE_RIGHT_BEGIN
CIRCLE_LEFT_IN     / CIRCLE_RIGHT_IN
CIRCLE_LEFT_RUNNING/ CIRCLE_RIGHT_RUNNING
CIRCLE_LEFT_OUT    / CIRCLE_RIGHT_OUT
CIRCLE_LEFT_END    / CIRCLE_RIGHT_END
```

Plain state flow:

1. `check_circle()` enters `BEGIN` by shared Lpt + opposite straight-line
   evidence with two-frame voting.
2. `BEGIN` tracks outside line and requires inner-line loss; then distance or
   gyro enters `IN`.
3. `IN` uses fixed selected-line action and advances by gyro or distance.
4. `RUNNING` follows the ring and advances to `OUT` by cumulative gyro or
   distance fallback.
5. `OUT` maps to a ReadyoutRing-like fixed outside-line phase.
6. `END` maps to outRing / final stabilization and exits by distance.

Selected-line owner:

* Right circle `IN/RUNNING/OUT` prefers `Splicing_leftline_center`.
* Left circle `IN/RUNNING/OUT` prefers `Splicing_rightline_center`.
* These are built in `reference_step.c`, not in `circle.c` itself.

Important lesson:

Current `circle.c` is already no longer pure ATG-original visual logic. It is a
hybrid of ATG Lpt/rpts entry, ittuann-style gyro phase gates, and fixed
outside-line selected geometry.

## Joshua `Island.c`: Main Semantic Reference

State model:

```text
Island_State 0: no island
1: entry candidate with lower corner still present
2: lower corner lost, arc descending
3: preparing to enter, find upper corner and draw dead line
4: in island
5: preparing out, draw fixed boundary
6: continuing out
7: basically out, find upper corner
8: final line extension
9: anti-continuous-detection tail
```

Core evidence:

* Entry uses continuity tear, lost-line counts, opposite continuity, search stop
  line, boundary start location, and lower corner validation.
* State 1/2 uses monotonicity change and line addition.
* State 3 draws a dead line from the first acceptable upper corner and uses
  gyro around `60` degrees to enter state 4.
* State 4 waits until gyro around `200` degrees before opening out-ring
  monotonicity judgment.
* State 5/6 keeps a fixed slope boundary through exit; state 6 can advance by
  line recovery or gyro around `320` degrees.
* State 7/8 handles final corner/line extension and state 9 prevents immediate
  re-detection.

Important lesson:

Joshua's value is the semantic split:

```text
detect -> staged entry -> fixed/dead line -> in-ring -> gated out-ring ->
fixed/dead exit -> final extension -> anti-retrigger
```

Its implementation details are raw-row-array-specific and should not be copied
directly into the ATG/IPM pipeline.

## State Mapping Proposal For Discussion

This is not an implementation decision yet; it is a comparison map.

| Joshua semantic phase | Current active closest phase | ATG native primitive to use | Notes |
| --- | --- | --- | --- |
| 0 no island | `CIRCLE_NONE` | shared Lpt/rpts checks | Current active entry is simpler than Joshua. |
| 1 lower corner candidate | `CIRCLE_*_BEGIN` early | `Lpt*`, `is_straight*`, inner-line loss | Could strengthen with rpts continuity/shape, but no raw `Boundry_Start`. |
| 2 lower corner gone / arc descends | `CIRCLE_*_BEGIN` late | inner-line loss + distance/gyro | Current code collapses Joshua 1/2 into `BEGIN`. |
| 3 enter with dead/fixed line | `CIRCLE_*_IN` | fixed outside-line center in `reference_step.c` | This is where right fixed-left geometry matters. |
| 4 in ring | `CIRCLE_*_RUNNING` | natural outside line or fixed fallback | Current `*_natural_*_ready()` gate decides fixed vs natural. |
| 5 ready out | `CIRCLE_*_OUT` | fixed outside-line center | Matches ittuann ReadyoutRing shape more than old ATG. |
| 6 out ring | `CIRCLE_*_END` first part | outside half-width current line | Current `END` is shorter/simpler. |
| 7/8 final extension | `CIRCLE_*_END` late | Lpt/line extension if added | Current code exits by distance; Joshua has more visual finish semantics. |
| 9 anti retrigger | reentry suppress frames | `suppress_circle_reentry_after_exit()` | Current code has explicit frame suppression. |

## Interpretation For "We Started From ATG But It Is Hard To Tune"

The tuning difficulty is not because ATG primitives are unusable. The stronger
statement is:

* ATG's data representation is the right substrate for this project.
* ATG `round.c` is too coarse and garage-coupled.
* Current `circle.c` is a hybrid with several borrowed ideas but not a clean
  state model.
* Joshua's 9-stage decomposition is the clearer high-level model, but it must
  be re-expressed using ATG `Lpt/rpts/IPM/fixed selected line` primitives.

So the likely redesign direction is:

```text
Keep ATG/IPM data path.
Use Joshua's phase semantics.
Use current/ittuann gyro cumulative gates.
Avoid introducing Joshua raw Line[H] / Longest_White_Column into this project.
```

## Right-Circle Inner Bias In This Comparison

The right-circle symptom should be treated as a state/selected-line evidence
problem before a full rewrite:

1. If state progression is wrong, compare current `BEGIN/IN/RUNNING` timing
   against Joshua phases 1-4.
2. If state progression is right but the car hugs inner side, inspect
   `CIRCLE_RIGHT_IN/RUNNING/OUT -> build_fixed_left_center_for_circle() ->
   Splicing_leftline_center`.
3. If fixed-left is only used in part of the run, inspect
   `circle_right_running_natural_left_ready()` because it decides when natural
   left line is trusted.

This supports the user's requested comparison first, while keeping the local
right-circle geometry bug separable from the larger 9-stage rewrite.
