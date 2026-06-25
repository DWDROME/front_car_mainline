# Technical Design: Visual-First Gyro-Gated Circle Refactor

## Agreed Direction

Keep the current ATG/IPM data path and move gradually toward Joshua-style
visual phase semantics. Gyro remains a gate or guard, not the primary normal
phase driver.

This is not a direct Joshua port. Do not introduce raw `Left_Line[H]`,
`Right_Line[H]`, or `Longest_White_Column()`.

## Implementation Shape

Use four stages, but implement one stage at a time:

1. Stage 0: right-circle symmetry / local geometry evidence.
2. Stage 1: half-side selected-line expansion for stable OUT/RUNNING.
3. Stage 2: visual-driven phase transitions with gyro gates.
4. Stage 3: cleanup and documentation after field evidence.

## Stage 0 Guardrails

Stage 0 is allowed to be implemented independently, but it is not permission to
change every asymmetric constant at once.

Before editing, verify each candidate with current file evidence and, where
possible, logs:

| Candidate | File / owner | Must verify before edit |
| --- | --- | --- |
| Right IN raw seed point vs left IN raw seed point | `cross.c::cross_farline_R/L` | `MT9V03X_W` and whether raw x values are actually non-mirrored around image center. |
| Right BEGIN lost-line threshold `<10` vs left `<2` | `circle.c::run_circle()` | Whether right line detection is noisier by evidence, or this is inherited asymmetry without measured need. |
| Right `IN -> RUNNING` `begin_y = BEGIN_Y` assignment | `circle.c::run_circle()` | Whether this changes selected geometry or only resets search region. |
| Right END distance `4000` vs left `7500` | `circle.c::run_circle()` | Whether right exits too early in state stream; do not change based only on geometric suspicion. |
| Right fixed-left selected line | `reference_step.c::build_fixed_left_center_for_circle()` | Whether selected source remains `circle_*_fixed_left` while guide trend points inner. |
| Natural-left readiness gate | `reference_step.c::circle_right_running_natural_left_ready()` | Whether right `RUNNING` switches away from fixed-left too early. |

Stage 0 first patch should choose exactly one of:

* fixed-left geometry;
* natural-left readiness gate;
* one proven asymmetric threshold.

Do not combine geometry, threshold, and phase timing in the same first run.

## Evidence Gate For First Patch

The first patch needs a right-circle evidence slice showing:

```text
circle_type stream
selected_line_source
rptsn_num
guide_error trend
rpts0s/rpts1s/rptsc0/rptsc1 counts
circle heading
```

Decision rules:

* `circle_*_fixed_left` throughout + guide points inner -> fixed-left geometry.
* switches away from fixed-left in `RIGHT_RUNNING` -> natural-left readiness
  gate.
* phase transition clearly early/late -> visual phase gate, not line geometry.

## Validation

For any code change:

1. `git diff --check`
2. `bash code/test.sh --host`
3. `bash code/test.sh`
4. Live right-circle run with `FRONT_CAR_CIRCLE_CAL_LOG=1`; compare at least
   5-10 consecutive frames, not a single frame.

If live validation is unavailable, stop after build/test and record the missing
field evidence explicitly.

## Stage 3 Cleanup Note

Cleanup and rationale for the first implementation slice are recorded in
`research/stage-3-cleanup-and-rationale.md`.

This does not mark the behavior field-proven. The next live right-circle run
must still verify selected-line source, guide trend, and `RUNNING -> OUT`
transition reason.
