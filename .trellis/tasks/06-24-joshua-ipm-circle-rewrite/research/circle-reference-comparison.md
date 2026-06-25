# Circle Reference Comparison

## Purpose

Answer the user's question: "参考呢?" for the current right-circle inner-side
bias investigation. This is a planning/research artifact only; no behavior
change is proposed here.

## Reference Sources

| Ref | Path | Role |
| --- | --- | --- |
| ATG / Enterprise_E | `atg_reference/Project/CODE/circle.c` plus `atg_reference/port/reference_step.c` | Active port currently driving the car. This is the code that must be explained and audited first. |
| Joshua.Xu real project | `/mnt/e/longxin/参考2/the-18th-smartcar/project/code/Island.c` plus `Camera.c` and `Gyroscope.c` | Main redesign reference for a future 9-stage circle rewrite. |
| ittuann ring reference | `/mnt/e/longxin/参考/Ring.c`, `Ring.h`, `tracking_ring.cc` | Borrowed reference for gyro phase gating and fixed-line action concepts. |

## Current ATG Port: What Actually Runs

Owner files:

* `atg_reference/Project/CODE/circle.c`
* `atg_reference/port/reference_step.c`

Plain flow:

1. `check_circle()` recognizes circle entry only when `circle_type ==
   CIRCLE_NONE`.
2. Entry uses shared L-point and straight-line evidence:
   * left circle: `Lpt0_found && !Lpt1_found && is_straight1 &&
     Lpt0_rpts0s_id < 35`
   * right circle: `!Lpt0_found && Lpt1_found && is_straight0 &&
     Lpt1_rpts1s_id < 35`
3. `run_circle()` advances states:
   * `BEGIN`: wait for inner-side line loss, then enter by distance or gyro.
   * `IN`: fixed entering action, then advance by gyro or distance.
   * `RUNNING`: stay in ring until gyro or distance force-out.
   * `OUT`: fixed outside-line action before `END`.
   * `END`: finish by distance and suppress reentry.
4. `select_work_line()` chooses the actual control line:
   * right circle `IN/RUNNING/OUT` prefers `Splicing_leftline_center`.
   * left circle `IN/RUNNING/OUT` prefers `Splicing_rightline_center`.
   * `END` uses current outside half-width line (`rptsc0` or `rptsc1`).
5. Control receives the selected midline indirectly as `guide_error`; the
   reference steering `pure_angle` is not the current differential control input.

Important right-circle chain:

```text
CIRCLE_RIGHT_IN / RUNNING / OUT
-> build_fixed_left_center_for_circle()
-> Splicing_leftline_center
-> select_work_line(): "circle_*_fixed_left"
-> normalize selected line
-> guide_error
-> differential yaw control
```

Right-circle inner bias should therefore be checked first as selected-line /
fixed-left geometry, not as a control-layer special steering problem.

## Joshua.Xu Real Project: Main Redesign Reference

Owner files:

* `/mnt/e/longxin/参考2/the-18th-smartcar/project/code/Island.c`
* `/mnt/e/longxin/参考2/the-18th-smartcar/project/code/Camera.c`
* `/mnt/e/longxin/参考2/the-18th-smartcar/project/code/Gyroscope.c`

Core model:

* `Camera.c` owns raw binary image arrays and per-row raw left/right lines:
  `image_two_value`, `Left_Line[]`, `Right_Line[]`, `Search_Stop_Line`,
  `Boundry_Start_Left`, `Boundry_Start_Right`, `Left_Lost_Time`,
  `Right_Lost_Time`, `Both_Lost_Time`.
* `Island.c::Island_Detect()` uses those raw-line arrays directly.
* It is a 9-state island/ring flow, with state `9` used as an anti-immediate
  re-detection tail.
* Entry recognition combines:
  * side continuity tear,
  * side lost counts,
  * opposite-side continuity,
  * search stop line,
  * lower corner point,
  * monotonicity change point.
* Middle phases draw fixed/dead lines by slope (`K_Draw_Line`,
  `K_Add_Boundry_Left`, `K_Add_Boundry_Right`) and refresh line search with
  `Longest_White_Column()`.
* Gyro is a gate, not the only source of geometry:
  * state 3 enters state 4 after about `abs(FJ_Angle) >= 60`.
  * state 4 opens out-ring visual judgment only after about `200` degrees.
  * state 6 can force toward state 7 around `320` degrees.

Direct-copy risk:

Joshua's implementation is built around raw image row/column lines. Our active
port publishes IPM/resampled points and selected centerlines. A safe rewrite has
to map each raw-image concept to an IPM owner explicitly:

| Joshua concept | Direct meaning there | Current project equivalent / risk |
| --- | --- | --- |
| `Left_Line[]` / `Right_Line[]` | raw row-indexed boundary column | ATG port has traced/resampled point arrays and IPM helpers; not a one-line equivalent. |
| continuity tear | row-to-row x jump in raw boundary | Need an IPM/current-frame owner before using as a state trigger. |
| monotonicity change | raw boundary x trend reversal | Could be approximated from current line points, but coordinate direction and sample order must be verified. |
| slope/dead line drawing | draw into raw boundary arrays | Current port should build IPM selected centerline via fixed outside line, not mutate raw Joshua arrays. |
| gyro gate | phase eligibility | Already partially present as `circle_heading_rad` and `circle_heading_abs_ge()`. |

## ittuann Reference: Borrow Only

Owner files:

* `/mnt/e/longxin/参考/Ring.c`
* `/mnt/e/longxin/参考/tracking_ring.cc`

Useful contracts:

* `Ring.c` uses staged functions: pre-meet, first meeting, enter, turning,
  ring-running, out, straighten, over.
* `Ring.c` accumulates a local `gyro_angle` and uses thresholds around `20`,
  `100`, and `160` in later phases.
* `tracking_ring.cc` uses explicit states such as `Right_intoRing`,
  `Right_inRing`, `Right_ReadyoutRing`, `Right_outRing`, and mirrored left
  states.
* It resets gyro integration once on entering ring road via
  `gyro_integration_clean()`, then compares cumulative thresholds.
* It has fixed-line processing functions:
  * `Right_intoRing_processing()` -> `creat_fixedLeftLine()`
  * `Right_ReadyoutRing_processing()` -> `creat_fixedLeftLine()`
  * `Left_intoRing_processing()` -> `creat_fixedRightLine()`
  * `Left_ReadyoutRing_processing()` -> `creat_fixedRightLine()`

Borrowed lesson:

Fixed outside-line action plus cumulative gyro phase gates is a valid shape.
But ittuann is not the main circle recognition reference and should not override
Joshua's richer visual-state model.

## What This Means For The Right-Circle Inner Bias

The current most relevant reference alignment is:

| Symptom question | Reference-backed way to inspect it |
| --- | --- |
| Is the right circle detected by the wrong condition? | Compare `check_circle()` right-entry L-point/straight-line condition with Joshua's right-entry tear/lost/opposite-continuity conditions. |
| Does it enter the right phase at the wrong time? | Compare current `BEGIN -> IN -> RUNNING` gyro/distance transitions with Joshua state 1-4 and ittuann cumulative gyro gates. |
| Does the line itself point inward? | Inspect `build_fixed_left_center_for_circle()` and selected source `"circle_*_fixed_left"` across right `IN/RUNNING/OUT`. |
| Is the left/right mirror actually symmetric? | Compare `build_fixed_left_center_for_circle()` vs `build_fixed_right_center_for_circle()` after IPM conversion, not only by source-code symmetry. |
| Is control causing the issue? | Only after selected-line and `guide_error` evidence look correct. The reference/control boundary says `pure_angle` is diagnostic, not actuator input here. |

## Next Planning Step

Before implementation, collect or inspect a right-circle run where selected-line
source and guide are visible. The first evidence target is:

```text
circle state stream
selected_line_source
selected point count
guide_error trend
right/left source point counts
gyro heading
```

If the right-circle selected source remains `"circle_*_fixed_left"` while the car
goes inner-side, the first candidate is fixed-left-line IPM geometry. If it
switches away from fixed-left too early, the first candidate is the
`circle_right_running_natural_left_ready()` gate.
