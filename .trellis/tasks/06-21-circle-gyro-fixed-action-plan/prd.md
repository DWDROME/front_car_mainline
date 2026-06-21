# brainstorm: gyro fixed-action circle state machine

## Goal

Rework the ATG circle state machine toward the `tracking_ring.cc` style: keep visual detection as the entrance, use a deliberate fixed-action entering phase, and drive later circle phase transitions with gyro angle and distance rather than waiting for brittle line reappearance patterns.

This is a planning task only until the user approves implementation.

## What I Already Know

* User wants a complete plan before a larger circle rewrite.
* User does not want extra diagnostic/candidate layers for this task.
* User prefers minimal direct control flow, hard-coded parameters where reasonable, and no over-engineered glue.
* User explicitly asked not to delete old code; old branches should be commented with `//` or `/* ... */`.
* `参考/tracking_ring.cc` uses:
  * `Left_intoRing` / `Right_intoRing` as the entering action phase.
  * Fixed line generation during `*_intoRing_processing()`.
  * `gyro_integration_clean()` once when entering the ring road.
  * Monotonic cumulative gyro thresholds for `intoRing -> inRing -> ReadyoutRing -> outRing`; it does not reset gyro at every phase.
  * Motor distance for final exit from out-ring state.
* Current `atg_reference/Project/CODE/circle.c` uses:
  * `CIRCLE_*_BEGIN` as pre-entry / outside-line phase.
  * `CIRCLE_*_IN` as active entering phase with far-line splicing.
  * `CIRCLE_*_RUNNING`, `OUT`, `END` as later phases.
  * Existing gyro integration in `circle_heading_rad`, updated from `code/app/runners.cpp`.
* Current gyro update path:
  * `code/app/runners.cpp` reads IMU feedback.
  * It calls `update_circle_heading(yaw_rate_rad_s, period_ms, valid)` before `tracking_process_frame()`.
  * `update_circle_heading()` resets only when `circle_type == CIRCLE_NONE`; otherwise it accumulates through all circle states.
* Current selected-line owner:
  * `run_circle()` sets `track_type` and `circle_type`.
  * `reference_step.c::select_work_line()` actually chooses near-line center or spliced circle center.
  * `build_circle_spliced_lines()` currently builds fixed/spliced circle lines only for `CIRCLE_*_IN` and `CIRCLE_*_OUT`, not for `BEGIN`.

## Current Problem Shape

Current `BEGIN -> IN` requires a brittle visual sequence:

```text
inner side line almost disappears
-> same side line reappears long enough
-> same side line becomes short again
-> distance or gyro allows IN
```

For a biased approach into a left ring, the inner line may be short or unstable without cleanly satisfying `rpts0s_num > 30` reappearance. That can leave the car stuck in `CIRCLE_LEFT_BEGIN` or repeatedly revoked.

`tracking_ring.cc` does not wait for that visual reappearance. It switches into an entering action phase, applies fixed line processing, and then uses gyro angle to advance.

## Requirements

* Keep `check_circle()` / `Half_check.c` entrance behavior out of scope for the first rewrite unless implementation proves it blocks the fixed action.
* Preserve existing state enum names to avoid touching report and assistant consumers.
* Use current states with new meaning:
  * `CIRCLE_LEFT_BEGIN` / `RIGHT_BEGIN`: pre-entry, follow outside line, wait for enough entry evidence.
  * `CIRCLE_LEFT_IN` / `RIGHT_IN`: fixed-action entering phase, equivalent to `tracking_ring.cc` `Left_intoRing` / `Right_intoRing`.
  * `CIRCLE_LEFT_RUNNING` / `RIGHT_RUNNING`: in-ring phase.
  * `CIRCLE_LEFT_OUT` / `RIGHT_OUT`: ready/out phase.
  * `CIRCLE_LEFT_END` / `RIGHT_END`: exit stabilization, distance or gyro finish.
* Transition into `CIRCLE_*_IN` must reset the circle gyro angle once, then later circle phases use cumulative thresholds.
* Fixed action must be implemented in the tracking/selected-line layer, not by adding control-layer special cases.
* Do not reuse old frame geometry.
* Do not delete old visual transition code; comment it out with a short reason.
* `BEGIN -> IN` must still require the inner-line lost event (`none_left_line > 0` / `none_right_line > 0`) so a false `BEGIN` from half-cross logic cannot drive directly into fixed circle action by distance alone.
* Distance exits remain as failure guards. Gyro is the normal phase trigger, but distance guards keep the car from depending only on unvalidated borrowed thresholds.

## Proposed State Mapping

| `tracking_ring.cc` | Current ATG state to use | Action owner |
| --- | --- | --- |
| `Left_intoRing` / `Right_intoRing` | `CIRCLE_LEFT_IN` / `CIRCLE_RIGHT_IN` | `build_circle_spliced_lines()` fixed line |
| `Left_inRing` / `Right_inRing` | `CIRCLE_LEFT_RUNNING` / `CIRCLE_RIGHT_RUNNING` | current near/far line policy, adjusted by gyro |
| `Left_ReadyoutRing` / `Right_ReadyoutRing` | `CIRCLE_LEFT_OUT` / `CIRCLE_RIGHT_OUT` | existing out splice/fixed action |
| `Left_outRing` / `Right_outRing` | `CIRCLE_LEFT_END` / `CIRCLE_RIGHT_END` | distance or gyro finish |

## Fixed Action Design

The fixed action should live in `atg_reference/port/reference_step.c::build_circle_spliced_lines()`.

For left ring entering (`CIRCLE_LEFT_IN`):

```c
// New fixed action:
// Build a synthetic right boundary from a bottom-right raw anchor to a fixed
// upper target, then track_rightline() to get the centerline.
point_Cal_Line_2(Cal_rot_x(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                 Cal_rot_y(RAW_RIGHT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
                 Cal_rot_x(CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X,
                           CIRCLE_FIXED_IN_TARGET_RAW_Y),
                 Cal_rot_y(CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X,
                           CIRCLE_FIXED_IN_TARGET_RAW_Y),
                 rightline,
                 &rightline_num);
resample_points(rightline, rightline_num, Splicing_rightline_s0s,
                &Splicing_rightline_s0s_num, sample_dist * pixel_per_meter);
track_rightline(Splicing_rightline_s0s, Splicing_rightline_s0s_num,
                Splicing_rightline_center, (int)round(2.0),
                pixel_per_meter * ROAD_WIDTH / 2);
Splicing_rightline_center_num = Splicing_rightline_s0s_num;
```

For right ring entering (`CIRCLE_RIGHT_IN`), mirror it:

```c
point_Cal_Line(Cal_rot_x(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
               Cal_rot_y(RAW_LEFT_ANCHOR_X, RAW_BOTTOM_ANCHOR_Y),
               Cal_rot_x(CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X,
                         CIRCLE_FIXED_IN_TARGET_RAW_Y),
               Cal_rot_y(CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X,
                         CIRCLE_FIXED_IN_TARGET_RAW_Y),
               leftline,
               &leftline_num);
resample_points(leftline, leftline_num, Splicing_leftline_s1s,
                &Splicing_leftline_s1s_num, sample_dist * pixel_per_meter);
track_leftline(Splicing_leftline_s1s, Splicing_leftline_s1s_num,
               Splicing_leftline_center, (int)round(2.0),
               pixel_per_meter * ROAD_WIDTH / 2);
Splicing_leftline_center_num = Splicing_leftline_s1s_num;
```

Hard-coded first-pass targets:

```c
enum
{
    CIRCLE_FIXED_IN_TARGET_RAW_Y = 70,
    CIRCLE_FIXED_IN_TARGET_RAW_X_OFFSET = 35,
    CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X = MT9V03X_W / 2 - CIRCLE_FIXED_IN_TARGET_RAW_X_OFFSET,
    CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X = MT9V03X_W / 2 + CIRCLE_FIXED_IN_TARGET_RAW_X_OFFSET,
};
```

Reasoning:

* It mirrors `tracking_ring.cc` `creat_fixedRightLine()` / `creat_fixedLeftLine()`.
* It stays inside tracking geometry; no control-layer fixed yaw or hidden control fallback.
* It is an explicit element action, not stale-frame reuse.
* The constants are local and hard-coded first; no YAML/config expansion.

## Gyro Synchronization Plan

Current `circle_heading_rad` is cumulative across all circle states. Keep that model because it matches `tracking_ring.cc`: the reference resets gyro once when entering ring action, then compares against increasing cumulative thresholds.

Do not add per-phase reset or split threshold constants. That would create extra reset points and drift away from the reference behavior.

Required synchronization:

* Keep `code/app/runners.cpp` gyro update order unchanged. It already feeds `update_circle_heading()` before `tracking_process_frame()`.
* Keep the `update_circle_heading()` `circle_type == CIRCLE_NONE` cleanup as the idle/global cleanup.
* Add an explicit `reset_circle_heading()` at the `BEGIN -> IN` transition. This makes `CIRCLE_*_IN` start from a clean ring-action angle even if `BEGIN -> IN` used the existing `CIRCLE_HEADING_ENTER_DEG10` guard.
* After entering `IN`, use existing cumulative thresholds:
  * `CIRCLE_HEADING_ENTER_DEG10` for `IN -> RUNNING`.
  * `CIRCLE_HEADING_START_OUT_DEG10` for `RUNNING -> OUT`.
  * `CIRCLE_HEADING_FORCE_OUT_DEG10` as a force/guard threshold.
  * `CIRCLE_HEADING_FINISH_DEG10` for final gyro finish where currently applicable.

This keeps the number of moving parameters unchanged.

## `run_circle()` Rewrite Shape

Left side first-pass shape:

```c
if(circle_type == CIRCLE_LEFT_BEGIN)
{
    track_type = TRACK_RIGHT;
    Count_dis_Flag = 1;

    /*
     * legacy visual reappear gate:
     * if (rpts0s_num < 2 && !Lpt0_found) ...
     * if (rpts0s_num > 30 && none_left_line) ...
     * if ((rpts0s_num < circle_in_length && total_distence > circle_in_distance && have_left_line) || ...)
     */

    if(none_left_line > 0 &&
       (total_distence > circle_in_distance ||
        circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)))
    {
        reset_circle_heading();
        circle_type = CIRCLE_LEFT_IN;
        if_lost_right_line = 0;
        Count_dis_Flag = 0;
        if_clean_pid = 1;
    }
}
else if(circle_type == CIRCLE_LEFT_IN)
{
    // Fixed action is built in build_circle_spliced_lines().
    track_type = TRACK_LEFT;
    Count_dis_Flag = 1;

    if(circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10))
    {
        circle_type = CIRCLE_LEFT_RUNNING;
        Count_dis_Flag = 0;
    }
}
```

Right side mirrors this with `TRACK_LEFT` in `BEGIN`, `TRACK_RIGHT` in `IN`.

Later stages should be rewritten in the same pass so state meanings stay single-source:

* `RUNNING -> OUT`: gyro threshold is the normal trigger. The old `Lpt*` visual trigger should be commented as legacy, not used as a parallel trigger.
* If the old `Lpt*` visual trigger is removed, do not keep unconditional `Lpt*` truncation as an invisible steering shaper. Either comment the truncation together with the trigger, or reintroduce it later behind a gyro-near-out condition after live evidence shows it is needed.
* `OUT -> END` / `END -> NONE`: keep existing distance guards and gyro guards where present. These are failure/finish guards, not the brittle visual reappear sequence.
* Do not delete distance limits such as `total_distence > 4500`, `> 7500`, or `> 4000`; they are the only protection if borrowed gyro thresholds are not yet tuned on this car.
* `RUNNING -> OUT` currently has no distance force-out. If the visual `Lpt*` trigger is removed, add at most one local hard-coded distance guard for this long phase, and mark it as a live-tuning placeholder rather than a proven value.

## Old Code Preservation Rule

Do not delete the old `BEGIN -> IN` visual gate. Wrap it:

```c
/*
 * legacy visual reappear gate, kept for rollback:
 * The original ATG BEGIN waits for inner line lost -> reappeared long -> short.
 * On the current car this can miss biased ring entry. The fixed-action rewrite
 * uses distance/gyro to enter CIRCLE_*_IN, then the selected-line layer builds
 * a deliberate fixed circle line.
 *
 * old code ...
 */
```

Do the same for old `CIRCLE_*_IN` far-line-only splice if the fixed action replaces it as the primary line builder.

## Implementation Plan

1. Update `circle.c`
   * Do not add a multi-phase `enter_circle_state()` helper.
   * Do not add stage-local gyro constants.
   * Rewrite `BEGIN -> IN` for left and right:
     * keep the inner-line lost event as a required precondition;
     * keep the line-lost counter increment itself, because it is the source of `none_left_line > 0` / `none_right_line > 0`;
     * remove the old line-reappeared / line-short-again sequence;
     * call `reset_circle_heading()` exactly when entering `CIRCLE_*_IN`.
   * Rewrite later visual phase triggers to cumulative gyro triggers in the same pass.
   * Do not keep unconditional `Lpt*` truncation in `RUNNING` if the corresponding `Lpt*` trigger is disabled.
   * Keep distance force exits as guards.
   * Keep old visual gate commented.

2. Update `reference_step.c`
   * Add fixed raw target constants near `RAW_LEFT_ANCHOR_X`.
   * Add fixed-action line builders for `CIRCLE_LEFT_IN` and `CIRCLE_RIGHT_IN`.
   * Keep old far-line splice code commented or behind a clearly disabled `#if 0` block for rollback.

3. Keep `runners.cpp` gyro call order unchanged
   * It already reads feedback before tracking.
   * State transition reset occurs in `run_circle()`; the next frame's feedback integrates the new stage.

4. Validation
   * `rg` for deleted old branches: old code must still exist in comments.
   * `git diff --check` where possible; note current CRLF noise if it persists.
   * Host build.
   * `config_parsing_test` and `options_parsing_test`.
   * Replay/analyze can verify compile-time routing and selected-line construction only. It cannot validate gyro phase progression unless the replay path injects IMU and encoder updates.

## Risks

* Fixed line constants may need board tuning.
* If `BEGIN` is falsely triggered, fixed action can drive into an incorrect path. The `none_left_line > 0` / `none_right_line > 0` precondition is required to keep `Half_check.c` false positives from entering fixed action by distance alone.
* The gyro thresholds were inherited from reference behavior and are not yet proven on this car. Keep distance guards until live tuning proves the gyro thresholds.
* Any new `RUNNING` distance guard is a placeholder unless measured on the car. `ENCODER_PER_METER` is 5800, so a value such as 16000 means about 2.76 m and should not be treated as validated.
* Gyro and distance are fed in live mode. Existing replay/offline/analyze paths may not advance gyro/distance-driven circle phases, so they must not be treated as full behavior validation for this rewrite.

## Out Of Scope

* No new diagnostic/candidate layer.
* No YAML parameter expansion for fixed-action constants.
* No control-layer fixed yaw/relay for circle.
* No deletion of old code.
* No rewrite of `check_circle()` thresholds unless implementation proves `BEGIN` itself is wrong.

## Recommended Scope

The recommended scope is no longer a half rewrite. Implement the whole circle lifecycle in one pass, but keep the diff small:

1. Fixed-action line for `CIRCLE_LEFT_IN` / `CIRCLE_RIGHT_IN`.
2. Explicit reset when entering `CIRCLE_*_IN`.
3. `CIRCLE_*_IN -> CIRCLE_*_RUNNING` by existing cumulative `CIRCLE_HEADING_ENTER_DEG10`.
4. `CIRCLE_*_RUNNING -> CIRCLE_*_OUT` by existing cumulative `CIRCLE_HEADING_START_OUT_DEG10`; comment out the old `Lpt*` visual trigger and its unconditional truncation unless live evidence justifies a gated version.
5. Preserve existing distance force/finish guards, and add only one `RUNNING` distance guard if removing the visual trigger would otherwise leave no non-gyro escape from `RUNNING`.
6. Do not change `check_circle()` / `Half_check.c` entrance logic in this task.

This avoids the mixed semantics where `IN` is fixed-action but later states still wait for visual reappearance.
