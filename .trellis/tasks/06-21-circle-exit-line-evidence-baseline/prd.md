# Circle Exit Line Evidence Baseline PRD

## Goal

Recover a clean debugging path for the current circle failure by starting from the last pushed baseline, measuring whether the car reaches `OUT` with usable current-frame line evidence, and only then running one-variable experiments. The focus is no longer "gyro threshold tuning" by itself; the focus is whether `OUT` / `END` can provide the control layer a correct selected line.

## What I Already Know

* The branch has been reset to the last committed runtime baseline before the noisy experimental stack.
* A separate line-ending guard commit (`.gitattributes`) was added so future diffs do not become whole-file CRLF noise.
* Previous live/debug rounds mixed too many variables at once: entry gates, `IN` fixed-line behavior, `OUT` fixed-line behavior, reentry suppression, END release, and stall reset.
* `RUNNING -> OUT` being driven by gyro/distance is still a reasonable direction, but successful exit also requires current-frame line construction in `OUT` / `END`.
* Ordinary right L points have appeared in logs, so the problem is not simply "corner detector never works."
* `ATGCircleEndRelease`-style reset from `END` to `NONE` because a selected line exists is considered a wrong direction.
* Ad-hoc entry gates such as `near >= 35` are unsafe unless logs prove true circle entries still pass.
* `drive21` showed the clean baseline failure boundary: the car reached
  `CIRCLE_LEFT_OUT`, `cross_farline_R()` returned no farline
  (`far_ipts1=0`, `far_rpts1s=0`), the first OUT frame still selected `rptsc1`
  with `Guide=-60.00` and `ok=1`, then the next frame fell to empty `rptsc0`
  after `track_type` became `TRACK_LEFT`.
* `Guide=-60.00` is a severe geometry symptom, not proof that
  `normalize_selected_line()` rejected the selected line. The first OUT frame
  with `Guide=-60.00` had `ok=1`; the later `ok=0` frame selected an empty
  input line.
* `drive23` showed that forcing `CIRCLE_LEFT_OUT` to prefer `rptsc1` when the
  splice is empty can keep selection alive long enough to reach `END`, but this
  is an experimental bypass, not a root-cause fix. It still leaves farline /
  splice construction missing and can drive at the guide clamp.
* `drive32` shifted the immediate priority: `CIRCLE_LEFT_IN` held the fixed
  line at `guide=49.82` for about 49 frames, driving the differential yaw path
  to roughly `yaw=-2989` and `actual≈-3069` before `RUNNING` started.
  `RUNNING` was initially controllable after the existing `0.81` bridge scale,
  then degraded as the car drifted outward. The next experiment therefore
  targets IN shock, not another RUNNING guide reduction.

## Problem Statement

The car can advance circle states without necessarily having a valid exit trajectory. In particular, a transition into `CIRCLE_LEFT_OUT` does not prove that `cross_farline_R()` built the right-side far line or that `select_work_line()` normalized a usable selected line. When this evidence is missing or geometrically wrong, the control layer receives either no line or an over-aggressive guide/yaw command, and the car fails exit even if gyro state progression looks correct.

The current root investigation has two separate failure boundaries that must
not be mixed:

* IN posture: `CIRCLE_LEFT_IN` can inject an excessive guide into the LS2K
  differential controller before the car reaches a fair `RUNNING` pose.
* OUT construction: `cross_farline_R()` can still fail to build a real farline
  / splice, and `out_rptsc1` is only a diagnostic bypass.

The immediate next experiment targets IN posture only. OUT dynamic seed and
END release remain separate follow-up experiments after the car reaches OUT
from a less violent entry.

## Primary Questions

1. Does the current baseline enter the circle reliably?
2. If exit fails, what exact `RUNNING -> OUT -> END -> NONE` flow occurs?
3. During `CIRCLE_LEFT_OUT`, are these available in the current frame?
   * `Lpt1_found`
   * `Lpt1_rpts1s_id`
   * `far_ipts1_num`
   * `far_rpts1s_num`
   * `far_Lpt1_found`
   * selected line / `rptsn_num`
4. During `END`, is the selected line present, geometrically sane, and producing bounded `guide` / `yaw`?
5. During `CIRCLE_LEFT_OUT`, can a dynamic farline seed derived from the current
   right-curve slope make `cross_farline_R()` produce `far_ipts1`,
   `far_rpts1s`, and a spliced exit line?
6. During `CIRCLE_LEFT_IN`, does attenuating only the bridge `guide_error`
   reduce yaw saturation while still letting gyro/distance transition to
   `RUNNING`?
7. If `END` still fails after OUT has real farline/splice evidence and non-
   clamped guide, what release/stabilization evidence is missing?
8. Is `CIRCLE_LEFT_RUNNING` already carrying a track-quality problem before
   OUT, such as sustained guide around 25-29, asymmetric duty, and outward drift?
   This is a separate class from OUT farline construction and must not be mixed
   into the dynamic seed experiment.

## Requirements

* Start from the current committed baseline plus the line-ending guard commit. Do not stack behavior changes before the baseline run.
* Each live run must map to the exact local commit used for build/upload.
* First run is baseline only: no circle behavior changes.
* If baseline can enter but fails exit, the first code change is logs only. It must not alter state transitions, selected-line construction, thresholds, or control output.
* Behavior experiments must be one variable per run.
* Entry logic, `IN` fixed line, `OUT` fixed line, reentry suppression, `END` release, and stall reset must not be changed in the same run.
* Thresholds `600 / 2000 / 2500 / 3550 / 16000` are out of scope until stable entry and stable arrival at `OUT` are proven.
* Do not add hidden fallback, previous-frame line reuse, silent state reset, or control-layer special casing.
* Logs must be explicit and grep-friendly, guarded by an environment flag such as `FRONT_CAR_CIRCLE_CAL_LOG=1`.
* Do not treat `out_rptsc1` as the final OUT solution. It may be kept only as a
  short-lived experiment or diagnostic guard to prove the empty-`rptsc0` failure
  boundary.
* The next behavior experiment must change only the control bridge output for
  `CIRCLE_LEFT_IN`: scale final `rt->vision.guide_error` by `0.75`. Do not
  change the fixed IN anchors, entry logic, state thresholds, OUT seed, END
  release, stall reset, or control-layer gains in the same run.
* The existing `CIRCLE_LEFT_RUNNING` bridge scale may stay at `0.81` for this
  run because drive32 showed the RUNNING front segment was initially
  controllable with it. Do not add another RUNNING reduction in the IN
  experiment.

## Baseline Run Plan

Before changing code:

```bash
git status --short --branch
git rev-parse --short HEAD
git diff --check
bash code/test.sh --host
bash code/test.sh
```

Then upload the compiled target binary manually and run one bounded live test with per-frame logs. The run must record the commit hash and output path.

Baseline run questions:

* Did `circle_type` enter `CIRCLE_LEFT_BEGIN` / `CIRCLE_LEFT_IN` / `CIRCLE_LEFT_RUNNING`?
* Did it reach `CIRCLE_LEFT_OUT`?
* If it reached `OUT`, did `rptsn_num` stay nonzero?
* During `OUT`, did `far_rpts1s_num` and `far_Lpt1_found` appear?
* Did `guide` or `yaw` spike when entering `IN`, `OUT`, or `END`?

## Standard Live Test Path

The fixed local entry point for this task is:

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh
```

It is intentionally split into explicit subcommands so build/upload/review can
be run without accidentally starting the car.

### 0. Local Setup

```bash
cd /mnt/e/longxin/ls2k0300_library/ls2k300_library/seekfree_ls2k0300_opensource_library/test_project/front_car_mainline_autop_direct
mkdir -p logs/live-circle
```

### 1. Build And Host Checks

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh verify-build
```

This command is the standardized version of:

```bash
git status --short --branch
git rev-parse --short HEAD
git diff --check
cmake --build code/build-host -j"$(nproc)"
cmake --build code/build -j"$(nproc)"
cd code/build-host && ./config_parsing_test && ./options_parsing_test && cd ../..
```

### 2. Upload Only

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh upload
```

Default target:

```text
root@192.168.0.101:/root/front_car_mainline
```

Override with `BOARD_HOST`, `BOARD_USER`, `BOARD_BIN`, or `LOCAL_BIN` only when
the board path changes. Upload does not start the drive binary.

### 3. Bounded Live Run

Only execute this after the car has been placed safely for the next short test.
Replace `drive15` with the current run id.

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive15 18
```

The command:

* kills any old `front_car_mainline`;
* runs with `FRONT_CAR_ENABLE_DRIVE=1`,
  `FRONT_CAR_CIRCLE_CAL_LOG=1`, `FRONT_CAR_DISPLAY=0`,
  `SMARTCAR_ASSISTANT=0`, `FRONT_CAR_PROCESS_FPS=120`, and
  `FRONT_CAR_PRINT_DIV=1`;
* sleeps for the bounded duration;
* kills the process;
* prints `wc -l` and `tail -80`;
* pulls the log to `logs/live-circle/20260621-drive15-front_car_circle_drive15.log`;
* writes run metadata to
  `.trellis/tasks/06-21-circle-exit-line-evidence-baseline/runs/drive15.summary.md`.

### 4. Review Existing Log

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive15
```

or:

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review logs/live-circle/20260621-drive15-front_car_circle_drive15.log
```

The review output is fixed to the following order:

1. `ATGCircleCal` / reset / stall / suppress / farline / L-point-window /
   `ATGCircleOutEvidence` / `ATGCircleSelectEvidence` events.
2. All nonzero `circle=[1-9](` frames.
3. Key circle states `circle=1/3/5/7/9`.
4. Entry candidate statistics and the first 20 left/right candidates.

### 5. Full Path

Use only when the car is ready and one command is acceptable:

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh all drive15 18
```

This runs `verify-build`, `upload`, `run`, and `review` in order.

## Small-Model Review Contract

When handing a log to a smaller model, require this exact order and do not let
it branch into algorithm changes:

1. Report whether `ATGCircleCal: from=CIRCLE_NONE to=CIRCLE_LEFT_BEGIN` or
   `CIRCLE_RIGHT_BEGIN` appeared.
2. If it did not appear, report left/right entry candidate counts and the first
   20 candidate frames.
3. If it did appear, list the complete `ATGCircleCal` state flow.
4. Inspect the last 50 frames before failure and report `circle`, `sel`, `far`,
   `l`, `far_l`, `guide`, `yaw`, `road`, and corner position fields.
5. Use at least a continuous 5-10 frame trend before making any conclusion.
6. End with one of the PRD failure classes: entry never reaches circle,
   `RUNNING -> OUT` timing issue, OUT far-line / selected-line construction
   issue, IN fixed-line over-aggression, RUNNING trajectory-quality issue, or
   END stabilization / release issue.
7. If the run reaches `END`, do not conclude that END is the root cause until
   OUT evidence proves `far_rpts1s_num > 0`, `splice_right > 0`, and guide is
   not continuously clamped. Otherwise report the END result as "contaminated by
   OUT geometry".

## Logs-Only Instrumentation Plan

Only if baseline enters circle but exit evidence remains unclear, add logs without behavior changes.

Baseline `drive15` reached `CIRCLE_LEFT_OUT` and then stalled for 30 frames
without selected line. Existing report fields show `sel=0/0`, `far=0/0`,
`l=0@-1/0@-1`, and `far_l=0@-1/0@-1` during the sustained OUT failure window,
but they do not yet separate `cross_farline_R()` seed/build failure from
selected-line normalization failure. Therefore the next implementation step is
logs-only OUT evidence, not a behavior experiment.

### RUNNING

Record:

```text
ATGCircleRunEvidence:
circle_type
Lpt1_found
Lpt1_rpts1s_id
circle_heading_deg10
total_distence
rpts0s_num
rpts1s_num
rptsn_num
```

Purpose: determine whether right L-point evidence exists before `RUNNING -> OUT`.

### OUT

Record after `cross_farline_R()` for left circle:

```text
ATGCircleOutEvidence:
circle_type
seed_source
Lpt1_found
Lpt1_rpts1s_id
far_ipts1_num
far_rpts1s_num
far_Lpt1_found
far_Lpt1_rpts1s_id
rptsn_num
circle_heading_deg10
total_distence
```

Purpose: determine whether OUT actually builds a right far line / exit line.

### END

Record:

```text
ATGCircleEndEvidence:
circle_type
rptsn_num
guide_error
target_yaw_or_yaw_cmd
total_distence
release_reason
```

Purpose: prevent early reset or ordinary-road takeover from hiding a broken exit-stabilization phase.

## Evidence Update After drive21-drive23

### drive21 Baseline Failure

`drive21` reached the target failure boundary:

```text
CIRCLE_NONE -> CIRCLE_LEFT_BEGIN
            -> CIRCLE_LEFT_IN
            -> CIRCLE_LEFT_RUNNING
            -> CIRCLE_LEFT_OUT
            -> ATGCircleStall
```

Observed OUT chain:

```text
cross_farline_R(): far_ipts1=0, far_rpts1s=0, far_Lpt1=0/-1
splice_right=0
first OUT selected source=rptsc1, rpts=48, rptsn=36, Guide=-60.00, ok=1
next selected source=rptsc0, rpts=0, rptsn=0, ok=0
30 frames without selected line -> stall reset
```

Interpretation:

* `cross_farline_R()` did not build the right farline.
* `Guide=-60.00` is not the direct `normalize_selected_line()` rejection cause
  for the first OUT frame because that frame had `ok=1`.
* The direct stall path is `track_type=TRACK_LEFT` selecting empty `rptsc0`
  after OUT lacks farline/splice evidence.

### drive23 out_rptsc1 Experiment

The `out_rptsc1` experiment changed `select_work_line()` so
`CIRCLE_LEFT_OUT` can select raw right line `rptsc1` when spliced OUT line is
empty:

```c
else if(circle_type == CIRCLE_LEFT_OUT && rptsc1_num > 0)
{
    rpts = rptsc1;
    rpts_num = rptsc1_num;
    g_selected_line_source = "out_rptsc1";
}
```

Result:

```text
NONE -> BEGIN -> IN -> RUNNING -> OUT -> END -> stall
```

Interpretation:

* This proves that empty `rptsc0` fallback was the immediate OUT stall trigger.
* This does not prove OUT is fixed. The experiment bypasses farline/splice
  construction and can still run at `Guide=-60.00`.
* END analysis is not clean while OUT entered END through clamped `out_rptsc1`
  control instead of a real spliced exit line.

### RUNNING Outward-Drift Observation

Middle-model review of `drive21` reported a separate trajectory-quality symptom
during `CIRCLE_LEFT_RUNNING`: guide stays around 25-29, yaw command is strongly
negative, left/right duty is highly asymmetric, and near-line evidence trends
from roughly `0/54` toward `12/60`. This may indicate the car is already moving
outward before OUT, which can make farline acquisition harder.

This is a valid failure class, but `drive32` shows the immediate first cut is
the IN bridge guide shock. Do not tune RUNNING guide, centerline choice,
control gains, OUT seed, or END release in the same run as the IN attenuation
experiment.

## Evidence Update After drive32

### IN Shock

`drive32` showed `CIRCLE_LEFT_IN` was the first severe control problem:

```text
frame 272-320:
circle=CIRCLE_LEFT_IN
guide=49.82
yaw≈-2989
actual=-4 -> -3069
near=0/124 -> 1/52
```

Interpretation:

* The fixed IN line itself is present and selected, so this is not a missing
  line problem.
* The ATG reference uses fixed ring lines as a servo steering action; this port
  sends `rt->vision.guide_error` into a differential yaw-rate controller.
* Keeping the same fixed geometry but attenuating the bridge guide is the
  narrowest LS2K-specific adaptation. It does not fabricate line evidence or
  alter the circle state machine.

### RUNNING Front Segment

Immediately after IN, `RUNNING` was initially acceptable with the existing
bridge scale:

```text
frame 321-338:
guide≈16-18
near_left=6 -> 16
duty roughly 8/6 to 11/4
actual=-3068 -> -1105
```

Interpretation:

* Do not further reduce RUNNING guide as the next step.
* Later RUNNING guide growth (`23-33`) is likely a consequence of already-bad
  posture / outward drift, not proof that the first fix belongs in RUNNING.

### OUT Seed Remains Separate

The dynamic OUT seed experiment in `drive32` projected to the far left of the
image (`raw≈5,54`) for many frames. That result is not enough to change OUT
again in the same run because the OUT pose was already contaminated by the IN
shock and later outward drift.

## Next Behavior Experiment: IN Bridge Guide Attenuation

### Hypothesis

`CIRCLE_LEFT_IN` fixed geometry is too aggressive for the LS2K differential
controller when converted directly into `rt->vision.guide_error`. Scaling only
the final bridge guide in `CIRCLE_LEFT_IN` should reduce yaw saturation and
start `RUNNING` from a cleaner posture without changing ATG circle state
timing or fixed-line anchors.

### Scope

Only change the final bridge output in
`code/tracking/atg_reference_mainline.cpp`:

```c++
if(circle_type == CIRCLE_LEFT_IN) {
    rt->vision.guide_error *= 0.75;
}
```

Keep the existing `CIRCLE_LEFT_RUNNING` bridge scale at `0.81` for this run.

Do not change:

* entry thresholds;
* fixed IN anchors (`CIRCLE_FIXED_*`);
* `CIRCLE_LEFT_IN -> CIRCLE_LEFT_RUNNING` gyro/distance thresholds;
* OUT dynamic seed;
* fixed OUT anchors;
* END release or stall reset;
* guide clamp or selected-line normalization rules;
* control-layer gains / motor signed-output behavior.

### Success Criteria

The IN attenuation experiment succeeds only if the first half of the circle
improves:

* `CIRCLE_LEFT_IN` still reaches `CIRCLE_LEFT_RUNNING`.
* IN `guide` drops from about `49.82` to about `37`.
* IN `yaw` / `cmd` no longer sit near the previous saturated range for the
  whole IN window.
* At RUNNING entry, `actual` is less extreme than `-3069` and begins recovering
  earlier.
* RUNNING front segment keeps `near_left` rising or stable for at least 10
  frames.

If this succeeds, retest OUT evidence before modifying `cross_farline_R()`
again.

### Change Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `/mnt/e/longxin/参考/tracking_ring.cc` uses `Left_intoRing_processing()` / `creat_fixedRightLine()` for left-ring entry, then `Left_inRing_processing()` returns to natural midline composition; the reference actuator is not this LS2K differential `guide_error -> yaw_cmd` path. | This port converts the selected ATG `rptsn` line into `rt->vision.guide_error`, then the LS2K controller maps it to differential yaw. In `drive32`, fixed IN produced `guide=49.82` for about 49 frames and drove yaw/actual near saturation before RUNNING. | `code/tracking/atg_reference_mainline.cpp`: scale only final `rt->vision.guide_error` by `0.75` while `circle_type == CIRCLE_LEFT_IN`; keep existing RUNNING bridge scale at `0.81`. | This is the narrowest LS2K bridge adaptation for the measured IN shock. It preserves ATG fixed line geometry and state thresholds while reducing the command sent to the differential controller. | The selected line is still current-frame ATG geometry. No previous-frame line is reused, no fake line is created, and no state transition or threshold is loosened. Failure remains visible through `line_found=0`, `sel`, `near`, `guide`, `yaw`, and circle logs. |
| The ATG-style IN to RUNNING handoff is not pure "any right line exists"; it is a lost-then-reappeared opposite-side evidence gate, and the project PRD keeps the 600/2000/2500/3550/16000 thresholds out of scope. | `drive42` succeeded with RUNNING entry `near=0/46`, `sel=46/41`, `ml=(55,108)`, `guide=32.46`; `drive65` failed after entering with `near=19/61`, `sel=61/47`, `ml=(78,97)`, `guide=7.01`, meaning the natural right line was still too long and the car was too close to the inner path. A later edit had also changed `CIRCLE_HEADING_ENTER_DEG10` from 600 to 400. | `atg_reference/Project/CODE/circle.c`: restore `CIRCLE_HEADING_ENTER_DEG10` to 600 and require left-ring `IN -> RUNNING` current-frame geometry to satisfy `rpts1s_num > 25`, `rpts1s_num <= circle_in_length`, `rpts0s_num < 0.2/sample_dist`, and `none_right_line > 1`. | This keeps the successful drive42 window while rejecting the measured drive65 early/inner geometry before RUNNING takes natural right-line control. | This rejects a bad current frame instead of fabricating or holding a line. It does not change fixed anchors, speed, OUT/END, guide calculation, or gyro/distance thresholds beyond restoring the PRD boundary value 600. |

## Follow-Up Behavior Experiment: Dynamic OUT Farline Seed

### Hypothesis

The fixed OUT seed used by `cross_farline_R()` is not robust enough for the
current left-circle exit pose. The frame still contains raw right-line evidence
(`rptsc1`), but the fixed seed/search path does not connect to the farline. A
seed projected from the current right-curve slope should place the farline
search on a more plausible right-lower-to-left-upper trajectory.

### Scope

Only change the seed source used before `cross_farline_R()` in
`CIRCLE_LEFT_OUT`.

Do not change:

* entry thresholds;
* `CIRCLE_LEFT_IN` geometry;
* fixed OUT anchors;
* END release or stall reset;
* gyro/distance thresholds `600 / 2000 / 2500 / 3550 / 16000`;
* guide clamp or selected-line normalization rules;
* control-layer `guide_error -> target_yaw -> yaw_cmd` behavior.

### Seed Construction Requirement

The dynamic seed must come from current-frame right-line evidence, preferably
`rptsc1` / `rpts1s`, not from previous-frame memory.

Minimum design:

1. Take a stable lower/middle segment of the current right line.
2. Estimate the curve trend from lower-right toward upper-left.
3. Accept the dynamic seed only when the trend is geometrically plausible for
   left-circle OUT.
4. Project upward/left by a bounded distance and clamp to the image frame.
5. Log `seed_mode`, source line count, slope/delta, selected seed, and
   `cross_farline_R()` result.
6. If the dynamic seed is invalid, fall back to the existing fixed seed and log
   the fallback reason.

### Success Criteria

The dynamic seed experiment succeeds only if the OUT evidence improves, not
merely if the state reaches END:

* `ATGCircleOutEvidence` shows `far_ipts1_num > 0` or `far_rpts1s_num > 0`
  for consecutive OUT frames.
* `Splicing_rightline_center_num > 0` appears during OUT.
* `ATGCircleSelectEvidence` selects the intended spliced/farline source rather
  than empty `rptsc0` or long-running `out_rptsc1`.
* `Guide` is not continuously clamped at `-60.00` during OUT.
* OUT keeps a nonempty selected line for at least 10 consecutive frames.

If these criteria are not met, continue investigating farline seed/search
internals before touching END release.

## Single-Variable Experiment Order

Only after the logs-only run identifies the failing boundary:

1. IN bridge guide attenuation experiment:
   * Keep entry, fixed IN anchors, OUT seed, END, stall, clamp, thresholds, and
     control gains unchanged.
   * Change only final `rt->vision.guide_error` in `CIRCLE_LEFT_IN` with scale
     `0.75`.
   * Test whether IN yaw saturation drops and RUNNING begins from a cleaner
     posture.
2. OUT dynamic farline seed experiment:
   * Run only after IN posture is less contaminated, or if IN attenuation does
     not change OUT pose.
   * Keep entry, `IN`, fixed OUT anchors, END, stall, clamp, and thresholds
     unchanged.
   * Change only the seed source for `cross_farline_R()` in
     `CIRCLE_LEFT_OUT`.
   * Test whether far-line evidence, splice construction, selected source, and
     guide geometry improve.
3. OUT direct-`rptsc1` guard assessment:
   * Treat `out_rptsc1` as a diagnostic bypass only.
   * Use it to prove the empty-`rptsc0` failure mechanism, not as final exit
     construction.
   * Remove or narrow it once dynamic seed / splice works.
4. END stabilization / release experiment:
   * Only after OUT has real farline/splice evidence and non-clamped guide.
   * Do not modify release/stall conditions while OUT is still controlled by
     clamped `out_rptsc1`.
5. RUNNING trajectory-quality experiment:
   * Only after OUT seed evidence has been tested cleanly or if logs prove the
     car cannot reach a fair OUT pose.
   * Keep entry, IN geometry, OUT seed, END, stall, and thresholds unchanged.
   * Investigate sustained RUNNING guide, duty asymmetry, and outward drift as
     a separate variable.
6. Entry experiment:
   * Only if baseline fails to enter.
   * Do not add broad near-count gates without proving true entries still pass.
7. Threshold calibration:
   * Only after stable entry and stable OUT evidence are present.

## Acceptance Criteria

* [ ] Baseline run is captured from a known commit with command, duration, and log path recorded.
* [ ] Baseline summary answers whether circle entry is reliable.
* [ ] Baseline summary maps `RUNNING / OUT / END` state flow.
* [ ] Baseline summary states whether `LEFT_OUT` has `Lpt1`, `far_rpts1s`, `far_Lpt1`, and nonempty selected line.
* [ ] If code is changed, the first change is logs-only and passes `git diff --check`, `bash code/test.sh --host`, and `bash code/test.sh`.
* [ ] No run mixes entry changes, IN fixed-line changes, OUT fixed-line changes, reentry suppression, END release, or stall reset.
* [ ] `drive21-drive23` conclusions are recorded: `out_rptsc1` is a diagnostic
      bypass, not a final OUT fix.
* [ ] The next behavior experiment changes only `CIRCLE_LEFT_IN` bridge guide
      attenuation.
* [ ] END release is not changed until OUT shows real farline/splice evidence
      and guide is not continuously clamped.

## Definition of Done

* A clean baseline log exists and is summarized.
* The failing boundary is classified as one of:
  * entry never reaches circle,
  * `RUNNING -> OUT` timing issue,
  * OUT far-line / selected-line construction issue,
  * IN fixed-line over-aggression,
  * RUNNING trajectory-quality issue,
  * END stabilization / release issue.
* The next code experiment, if any, changes exactly one behavior variable.
* For the current task state, "OUT fixed" means `cross_farline_R()` plus
  splicing produces a usable selected line. Reaching `END` through
  `out_rptsc1` alone is not sufficient.

## Out Of Scope

* Tuning `600 / 2000 / 2500 / 3550 / 16000` before OUT evidence is stable.
* Adding new candidate layers, second truth sources, previous-frame fallback lines, or control-layer circle special cases.
* Reintroducing broad experimental stacks such as entry gate + IN change + OUT change + reentry suppression in one run.
* Treating gyro state advancement as proof that exit trajectory construction is correct.
* Treating `out_rptsc1` as the final OUT solution while farline/splice evidence
  remains absent.
* Modifying END release because a run reaches END after clamped OUT control.
* Tuning RUNNING guide, centerline choice, fixed IN anchors, OUT seed, or
  control gains in the same run as IN bridge guide attenuation.

## Technical Notes

Relevant owners:

* `atg_reference/Project/CODE/circle.c` owns circle state transitions and calls `cross_farline_R()` / `cross_farline_L()` during OUT.
* `atg_reference/port/reference_step.c` owns selected-line normalization and port-layer spliced/fixed line construction.
* `code/tracking/atg_reference_mainline.cpp` converts selected ATG line into `guide_error`.
* `code/core/control.cpp` consumes `guide_error` through the differential-drive `guide_error -> target_yaw -> yaw_cmd -> target_l/r` contract.

Key lesson:

```text
IN fixed-line selection is not automatically a safe differential-control input.
State transition to OUT is not equivalent to having a controllable exit line.
State transition to END through out_rptsc1 is not equivalent to a fixed OUT.
```

## Related Task Context

Older tasks such as `06-21-circle-gyro-threshold-calibration` and `06-21-circle-gyro-fixed-action-plan` are background only. This PRD supersedes their immediate next-step priority: do not tune thresholds or rewrite fixed action until baseline evidence identifies the failing boundary.
