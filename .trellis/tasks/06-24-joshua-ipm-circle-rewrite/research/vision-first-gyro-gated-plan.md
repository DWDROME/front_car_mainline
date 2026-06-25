# Vision-First Gyro-Gated Circle Plan

## Decision

User chose:

```text
vision-first + gyro-gated, gradual changes
```

Meaning:

* Do not keep moving further toward pure gyro-driven circle phases.
* Do not directly port Joshua's raw `Line[H]` implementation.
* Re-express Joshua's visual phase semantics on the current ATG/IPM point-set
  pipeline.
* Keep gyro as a gate / anti-false-positive condition, not as the only phase
  driver.

## Why This Direction Fits The Evidence

Three-state-machine comparison showed:

* ATG original visual gates were hard to tune because `lost -> reappear -> short`
  can fail during biased ring entry.
* Current `circle.c` bypasses much of that visual brittleness with gyro
  thresholds, but this creates a new tuning burden and loses current-frame
  visual self-correction.
* Joshua's useful idea is not the raw code; it is the phase philosophy:
  visual feature first, gyro opens or confirms later decisions.

## First-Layer Owner Chain

Right-circle selected-line chain:

```text
CIRCLE_RIGHT_IN / CIRCLE_RIGHT_RUNNING / CIRCLE_RIGHT_OUT
-> reference_step.c::build_circle_spliced_lines()
-> build_fixed_left_center_for_circle()
-> track_leftline()
-> Splicing_leftline_center
-> select_work_line(): circle_*_fixed_left
-> normalize_selected_line()
-> rptsn
-> atg_reference_mainline.cpp::atg_lookahead_error()
-> guide_error
```

Important correction:

`cross_farline_R()` is still called in `CIRCLE_RIGHT_IN`, but current fixed-line
control for right circle does not directly use the `cross_farline_R()` far-line
result. The old far-line splice code is commented out in
`build_circle_spliced_lines()`. Today, right `IN/RUNNING/OUT` primarily uses
the fixed-left selected line.

So for right-circle inner-side bias, the first implementation target should not
be "rewrite `cross_farline_R()`" unless logs show selected source switched back
to a far-line or natural-line path. The first target is selected-line geometry
and the fixed-vs-natural gate.

## What `cross_farline_L/R` Still Does

`cross_farline_L()` / `cross_farline_R()`:

* seed a raw-image search point from near Lpt or a fixed raw point;
* search a far-side line in raw image;
* transform far points through IPM;
* resample to `far_rpts*s`;
* compute far Lpt through local angle + NMS.

This is still useful as visual evidence for a future Joshua-style state split,
but it is not currently the main half-width centerline generator for circle
fixed action.

## What "Half-Side Line" Means In The Current Code

The actual half-side centerline generator is:

* `imgproc.c::track_leftline()`: shift a left boundary inward by `dist`.
* `imgproc.c::track_rightline()`: shift a right boundary inward by `dist`.

The fixed circle helpers use this:

* `build_fixed_left_center_for_circle()` builds a synthetic left boundary, then
  calls `track_leftline(... ROAD_WIDTH / 2)` to create a centerline.
* `build_fixed_right_center_for_circle()` builds a synthetic right boundary,
  then calls `track_rightline(... ROAD_WIDTH / 2)` to create a centerline.

This is already the current-code equivalent of Joshua's "use reliable outside
line + half road width" idea.

## Gradual Plan

### Step 1: Evidence Before Change

Use existing logs or collect one right-circle run with:

* circle state stream;
* `g_selected_line_source`;
* `rptsn_num`;
* selected point count and guide error;
* raw `rpts0s/rpts1s/rptsc0/rptsc1` counts;
* heading angle.

Decision:

* If selected source is `circle_*_fixed_left` while the car goes inner-side,
  debug fixed-left geometry.
* If selected source changes away from fixed-left during right `RUNNING`, debug
  `circle_right_running_natural_left_ready()`.
* If state advances too early/late, debug visual phase gates before line
  geometry.

### Step 2: First Code Change Should Be Local

Candidate A: fixed-left geometry tuning.

* Scope: `build_fixed_left_center_for_circle()` constants / target geometry.
* When: selected source remains fixed-left and guide trend points inner.
* Risk: low blast radius if only right fixed-left helper is touched.

Candidate B: natural-left readiness gate.

* Scope: `circle_right_running_natural_left_ready()`.
* When: right `RUNNING` switches from fixed-left to natural `rptsc0` too early.
* Risk: moderate; affects how long right ring remains fixed-line.

Candidate C: visual phase gate introduction.

* Scope: `run_circle()` transition from `RIGHT_IN -> RIGHT_RUNNING` or
  `RIGHT_RUNNING -> RIGHT_OUT`.
* When: logs show state timing, not selected-line geometry, is the problem.
* Risk: higher; touches state-machine behavior.

Recommended first implementation after evidence:

```text
Diagnose selected-line source and guide trend first.
Then make one local change: either fixed-left geometry or natural-left gate.
Do not change gyro thresholds and fixed-line geometry in the same run.
```

### Step 3: Gradually Move Toward Joshua Semantics

Once the right-circle local behavior is stable:

1. Split current `BEGIN` into clearer visual subconditions in comments and
   diagnostics first.
2. Add rpts/IPM equivalents of Joshua "continuity tear" and "monotonicity
   change" only where logs prove the state transition needs visual correction.
3. Keep gyro thresholds as gates:
   * do not open out-ring visual judgment before enough heading;
   * allow gyro force-out only as a guard, not normal path.
4. Preserve the active ATG/IPM selected-line path.

## Out Of Scope For First Change

* No raw Joshua `Left_Line[H]` / `Right_Line[H]` arrays.
* No `Longest_White_Column()` port.
* No control-layer `pure_angle` steering path.
* No stale-frame fallback.
* No simultaneous threshold/geometry/state rewrite.
