# Trace Identity Audit

## Scope

This note records the evidence for the straight-road regression where a left
trace can crawl to the right-side line, enter the ordinary midline path, and
produce a large wrong steering error.

The fix is intentionally placed at the current-frame trace ownership gate in
`code/tracking/mainline.cpp`. It rejects invalid trace evidence before
`build_boundary_from_trace()`, `pick_track_type()`, and `build_selected_midline()`
can consume it. It does not reuse stale midline, stale boundary, or last-frame
control output.

## Tool Evidence

- `mcp__fast_context__fast_context_search` was available after the user's MCP
  restart and returned the trace/midline ownership chain:
  `mainline.cpp`, `imgproc.cpp`, `boundary.cpp`, `cross.cpp`, `types.hpp`.
- Source files opened and checked directly:
  - `code/tracking/mainline.cpp`
  - `code/tracking/imgproc.cpp`
  - `code/tracking/boundary.cpp`
  - `code/types.hpp`
  - `code/app/report.cpp`
  - `code/app/runners.cpp`
- Exact search confirmed no stale fallback owner in the changed path:
  `build_boundary_from_trace`, `pick_track_type`, `track_type_keep`,
  `guide_error`, `trace_identity_reject`.

## Four Fixed Audit Roles

1. Reference contract audit:
   - Reference `CD.cpp` uses row-owned `leftedge` and `rightedge` arrays.
   - Left evidence and right evidence have separate ownership before midline
     construction.
   - Current-frame midline generation consumes current left/right evidence,
     not a stale line.
   - Conclusion: rejecting identity-swapped trace evidence before boundary and
     midline construction preserves the reference contract.
2. Current implementation audit:
   - `trace_single()` only checks seed validity, brightness, step count, and
     vertical gain.
   - `build_boundary_from_trace()` copies trace points into boundary state
     without identity validation.
   - `pick_track_type()` chooses from point counts and `track_type_keep`, not
     from side ownership.
   - Conclusion: the correct choke point is immediately after tracing and
     before boundary construction.
3. Git regression audit:
   - `103daa68..bdc7b27` exposes the missing trace identity gate.
   - The regression commit removed the weak pair-width state cleanup around
     seeds, while trace acceptance still depended only on `trace_single()`.
   - The propagation point is ordinary single-side midline publication through
     `build_selected_midline()`.
   - Conclusion: the dirty fix targets the real owner in `trace_edges()`, not
     display or control.
4. Trellis/check gate audit:
   - Code shape is local, direct C/C++, and current-frame only.
   - No stale midline or stale boundary fallback was introduced.
   - `idrej` diagnostic was wired into detail/live/replay/report output.
   - Required validation was completed in the main session after this audit.

## Implemented Contract

New current-frame reject bits:

- `TRACE_IDENTITY_REJECT_LEFT_PASSED_RIGHT_SEED`: left trace reaches or passes
  the current right seed x position.
- `TRACE_IDENTITY_REJECT_RIGHT_PASSED_LEFT_SEED`: right trace reaches or passes
  the current left seed x position.
- `TRACE_IDENTITY_REJECT_ROW_CROSS`: both traces have evidence on the same raw
  row and the left trace is not left of the right trace.

If a bit rejects one side, that side's trace and seed are cleared before
boundary construction. If the row-cross bit is set, both sides are cleared. If
both sides are cleared, `TRACK_REJECT_TRACE_FILTERED` is returned.

## Validation

Commands run from repo root:

- `git diff --check` passed.
- `bash code/test.sh --host` passed.
- `bash code/test.sh` passed.
- `./code/build-host/front_car_mainline --analyze .diag/synth/straight_cross_like.png --report /tmp/straight_cross_like_after.txt`
  produced `line_found=0`, `track_reject_reason=3`,
  `trace_identity_reject=4`, `guide_error=0`.
- `./code/build-host/front_car_mainline --replay .diag/synth/straight_cross_like.png 3`
  produced three frames with `line=0`, `reject=3`, `idrej=4`.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t28.png --report /tmp/t28_after.txt`
  produced `line_found=0`, `track_reject_reason=3`,
  `trace_identity_reject=1`, `guide_error=0`.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t32.png --report /tmp/t32_after.txt`
  produced `line_found=0`, `track_reject_reason=3`,
  `trace_identity_reject=1`, `guide_error=0`.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t60.png --report /tmp/t60_after.txt`
  remained valid with `line_found=1`, `track_reject_reason=0`,
  `trace_identity_reject=0`, `guide_error=12.8786`.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t04.png --report /tmp/t04_after.txt`
  remained no-line with `trace_identity_reject=0`.
- Batch scan over `.diag/video_crop_input/*.png` and `.diag/synth/*.png`
  showed `ring_kind=0`, `ring_state=0`, `ring_pending_kind=0`, and
  `cross_state=0` for the scanned frames. New identity rejects appeared only on
  `t28`, `t32`, `t56`, and `straight_cross_like`; valid `t60` remained
  `idrej=0`.

## Remaining Risks

- Single-seed frames cannot use opposite-seed crossing bits. A single-side
  wrong seed can still be a later investigation target.
- If `find_seeds()` labels the wrong physical boundary as left or right, this
  pass trusts that seed identity.
- `TRACE_IDENTITY_REJECT_ROW_CROSS` is raw-row based. A case that only becomes
  inverted after IPM/resampling is not covered by this bit.
- `CROSS_IN` farline identity is a separate path and is not changed by this
  ordinary trace ownership gate.
- The reference roll/pitch `roll_times` gate for ring remains unavailable in
  current inputs and is still tracked separately.

## 2026-06-08 IPM Work-Point Order Check

User concern: the proposed "only check `left_x < right_x`, do not add width
upper/lower limits" shape could be an answer shaped to satisfy the style
request instead of a reference-backed decision.

Reference check:

- `CD.cpp:1520-1608` owns left/right identity with row arrays:
  `leftedge[i]` is found from the left scan and propagated as left evidence;
  `rightedge[i]` is found from the right scan and propagated as right evidence.
- `CD.cpp:1611-1693` builds `middleline` from valid left/right row evidence.
  Dual-side rows use `(leftedge[i] + rightedge[i]) >> 1`; single-side rows use
  a fixed image-side estimate and clamp. This is midline construction, not a
  width-based identity reject gate.
- `CD.cpp:1767-1823` selects control rows by left/right validity counts. It
  does not reject a row because `rightedge[i] - leftedge[i]` is outside a width
  band.
- Exact search for width-style identity checks found no
  `rightedge - leftedge` upper/lower gate in the reference control path.

Conclusion: the reference contract supports preserving left/right row identity
and consuming current-frame evidence. It does not support adding a new lane
width upper/lower reject policy as part of the identity fix.

Change rationale table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `CD.cpp:1520-1608` keeps left/right ownership in separate row arrays; `CD.cpp:1611-1693` consumes left/right validity and middleline, with no width reject gate. | Current IPM/resample points can invert after raw trace identity checks; this point-pair layer has no direct reference function. | `code/tracking/mainline.cpp:work_pair_order_ok`; `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS`. | With enough same-y pairs, `left_x >= right_x` proves current-frame side identity is wrong, so reject before boundary/midline consumers. No lane-width threshold is added; `k_pair_max_y_diff` and `k_pair_min_count` only decide whether there is enough paired evidence to make the order check. | The gate clears current-frame near-line candidates and returns no ordinary track; it does not reuse old midline or boundary. Validation passed: `git diff --check`, `bash code/test.sh --host`, `bash code/test.sh`. Batch analyze over `.diag/video_crop_input/*.png` and `.diag/synth/*.png` kept valid `t16/t36/t60` as `line_found=1,idrej=0`; existing rejects stayed `t28/t32=1`, `t56=2`, `straight_cross_like=4`; no `idrej=8` false trigger in current samples. |
| No reference-code equivalent; this is workflow guardrail. | `.trellis/` is local/ignored, so the tracked project rule also needs a durable entry. | `AGENTS.md` plus `.trellis/spec/tracking/critical-audit-guide.md`. | User requires every future tracking modification to include reference behavior and reasoning in a fixed table. This prevents undocumented policy changes hidden as simplification. | The rule records evidence requirements only; it does not change runtime behavior. |

Additional audit conclusions from this round:

- Do not add a hard single-seed identity gate now. There is no current-frame
  opposite-side anchor and no direct reference equivalent for that local shape.
- Do not implement `roll_times` by guessing in `ring.cpp`; reference uses
  `CD.PA > ramp_angle`, while current runtime lacks a pitch/ramp input chain.
- `CROSS_IN` farline identity remains a separate audit target because this
  work-point gate only covers ordinary dual-side work points after IPM/resample.

## 2026-06-08 CROSS_IN Far-L Source Audit

User concern: `build_cross_farline()` reuses `old_l` when current farline point
generation succeeds but `far_l_index()` does not find a new L point. This looked
similar to a forbidden stale-index fallback, so it was rechecked against the
reference versions, the commit that introduced it, and the current consumer.

Reference and history check:

- RT1064 reference `cross.c:78-90` runs `cross_farline()` during `CROSS_IN` and
  chooses `track_type` by `far_Lpt1_found`, then `far_Lpt0_found`, then near-line
  loss side.
- RT1064 reference `cross.c:128-251` builds far raw points, maps them to IPM,
  blurs/resamples, and finds `far_Lpt*_rpts*s_id`; the main loop then uses that
  id as the start of `track_leftline()` / `track_rightline()`.
- Unity reference `CD.cpp:1296-1318` has no `old_l`/`cross_farline` equivalent.
  It keeps cross active through `cross_times` and `set_ED()`, so the comparable
  idea is element-stage continuity, not an identical L-index variable.
- Commit `adfa1ce` introduced the current `old_l` rule with an explicit reason:
  preserving `track_type` alone was not enough because `solve_cross_mid()` still
  requires `left_l/right_l`. The commit also states that old farline point lists
  are not reused and farline generation failure still clears the side L index.
- `docs/6-5用户修改.md:120-130` records the narrow contract: only when the current
  frame has a farline point list but `far_l_index()` returns `-1`, the old id may
  be kept if it still fits the current point count and leaves enough tail points.

Then-current implementation check:

- `code/tracking/cross.cpp:263-341` clears current farline points every frame.
  Seed, trace, IPM, and resample failures all clear `*far_l = -1`.
- `far_l_index_usable()` requires `old_l >= 0`, `old_l < current_num`, and
  `current_num - old_l >= k_cross_min_front_step`.
- `code/tracking/mainline.cpp:543-688` consumes only current `left_pts/right_pts`
  from `left_l/right_l` onward. It does not fall back to near lines, old midline,
  old farline points, or old control output.

Decision:

- Do not delete `old_l`. It is a narrow current-farline index continuity rule
  created to avoid reintroducing the `adfa1ce` "farline exists but L id flickers
  to -1 and the car stops" failure.
- Tighten the validity source: because `tracking_reset()` and `cross_leave()`
  zero `left_l/right_l`, index `0` must not be treated as a reusable old L until
  that side has previously produced a real `NEW` or verified `REUSED` far-L
  source.
- Do not strengthen it with unproven width/drift thresholds. The reference does
  not provide such a threshold and current samples do not show that `old_l` is
  the owner of the wrong-side crawl.
- Add diagnostics only: `left_far_l_source/right_far_l_source`, where
  `0=none`, `1=new`, `2=reused`, plus `left/right_far_l_reuse_count`. This lets
  future logs prove whether a frame used a newly detected far L or a reused
  current-farline index, and whether reuse lasted multiple frames.

Change rationale table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `cross.c:78-90` enters `cross_farline()` in `CROSS_IN` and selects side from current `far_Lpt*_found`; `main.c:363-371` uses `far_Lpt*_rpts*s_id` as farline-midline start. Unity `CD.cpp:1296-1318` has no farline L id but keeps cross active through `cross_times/set_ED()`. | Current architecture needs `left_l/right_l` for `solve_cross_mid()`. Since `adfa1ce`, when current farline exists but no new L is detected, the old same-side index can be reused only if it fits the current farline length and tail length. However reset/leave zero-initialize `left_l/right_l`, so index `0` needs a source-validity guard. | Kept `old_l` continuity but require previous `left/right_far_l_source != CROSS_FAR_L_NONE` before reuse. Added `CROSS_FAR_L_NONE/NEW/REUSED`, `left/right_far_l_source`, `left/right_far_l_reuse_count`, and report/replay/live/detail printing. | This preserves the old special-purpose behavior: if a valid L was seen before and one current frame misses L while farline points still exist, continue from the same current-farline index. It also prevents first-use reset value `0` from pretending to be historical L evidence. | The code still clears farline points every frame; seed/trace/IPM/resample failure still clears `far_l` and reuse count; first use without prior source fails instead of starting at 0; `solve_cross_mid()` still consumes only current farline points and fails instead of using stale midline. Source changes are diagnostic except for the source-validity guard, which rejects only unproven initialized index 0. |

Validation:

- `git diff --check` passed.
- `bash code/test.sh --host` passed.
- `bash code/test.sh` passed.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t16.png --report /tmp/t16_after_ring_gate.txt`
  remained valid with `line_found=1`, `track_reject_reason=0`,
  `trace_identity_reject=0`, `guide_error=-21.5208`, and
  `cross_left_l_source=0`, `cross_right_l_source=0`,
  `cross_left_l_reuse_count=0`, `cross_right_l_reuse_count=0`.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t60.png --report /tmp/t60_after_ring_gate.txt`
  remained valid with `line_found=1`, `track_reject_reason=0`,
  `trace_identity_reject=0`, `guide_error=12.8786`, and
  `cross_left_l_source=0`, `cross_right_l_source=0`,
  `cross_left_l_reuse_count=0`, `cross_right_l_reuse_count=0`.
- `./code/build-host/front_car_mainline --replay .diag/video_crop_input/t16.png 2`
  printed `far_src=0/0` and `far_reuse=0/0`, confirming replay formatting.
- Batch analyze over `.diag/video_crop_input/*.png` and `.diag/synth/*.png`
  kept valid `t16/t36/t60` with `line_found=1`, `track_reject_reason=0`,
  and `trace_identity_reject=0`; existing rejected frames stayed rejected.

Coverage gap:

- The current checked-in diagnostic samples did not enter `CROSS_STATE_IN`, so
  they do not exercise a real `NEW -> REUSED` far-L sequence. The source guard
  was verified by code inspection and ordinary-frame regression samples; a future
  CROSS_IN replay should confirm `far_src=1 -> 2` and increasing
  `far_reuse` on a real one-frame L-miss sequence.

Sub-agent cross-check correction:

- A first reference-only audit called `old_l` "no reference equivalent". That
  wording was too strong.
- Corrected conclusion: RT1064 has no explicit `old_l`/source/reuse-count field,
  but it does have an implicit far-L id persistence behavior. `cross.c:227-247`
  clears only `far_Lpt*_found`, not `far_Lpt*_rpts*s_id`; `cross.c:87-90` can
  keep or choose `track_type` without a new far-L found; `main.c:364-371` then
  consumes `far_Lpt*_rpts*s_id` by `track_type` without checking `found`.
- Current `old_l_source != NONE && far_l_index_usable(old_l, current_num)` is
  therefore not a direct copied reference contract. It is a narrowed explicit
  version of the RT1064 implicit id-holding risk: current farline points are
  rebuilt, the old index must still fit the current list and tail, and reset
  index `0` cannot fake a prior source.

## 2026-06-08 Guide Error / Pure Pursuit Audit

User-visible risk: straight-road twisting may come from the visual error chain,
so commit `103daa6` ("align reference midline start and error calculation") was
rechecked against the reference implementation and the current control owner.

Reference check:

- RT1064 `main.c:375-401` maps the raw wheel point `(MT9V03X_CSI_W/2,
  MT9V03X_CSI_H*0.78)` through `mapx/mapy`, finds the nearest midline start,
  writes that start to `(cx, cy)`, and resamples from there.
- RT1064 `main.c:408-420` computes heading-style `error` and `error_near` with
  `-atan2f(dx, cy - y + 0.2 * pixel_per_meter)`.
- RT1064 `main.c:428-444` does not feed that `error` into the servo in the
  active path. It feeds `pure_angle =
  -atanf(pixel_per_meter * 2 * 0.2 * dx / dn / dn) / PI * 180 / SMOTOR_RATE`
  into `pid_solve(&servo_pid, pure_angle)`, clamps `angle`, then outputs
  `smotor1_control(servo_duty(SMOTOR1_CENTER + angle))`.

Current implementation check:

- `code/app/runners.cpp:404-417` runs one live frame as
  `tracking_process_frame()` -> feedback read -> `solve_runtime_with_feedback()`
  -> `drive_output_apply()`.
- `code/tracking/mainline.cpp:919-940` uses the same raw wheel-point idea for
  `control_ref_point()`.
- `code/tracking/mainline.cpp:888-916` computes `guide_error` as the
  heading-style `-atan2(dx, dy + forward_bias)` value.
- `code/core/control.cpp:231-258` consumes `guide_error` through a differential
  drive visual outer loop: `guide_error -> target_yaw`, not through a servo
  `pure_angle -> servo_pid` path.
- `code/core/control.cpp:260-326` then applies optional yaw-rate PI and
  differential kinematics: `target_yaw -> yaw_cmd -> target_l/target_r`.
- `code/core/control.cpp:350-432` consumes `target_l/target_r` only as local
  wheel-speed targets and publishes `left_duty/right_duty`.
- `code/types.hpp:268-277` stores `target_yaw_rate_mrad_s` and duty outputs; it
  has no persistent `target_l/target_r` control output field.
- `code/app/report.cpp:541-546` reports `guide_error`, `target_yaw`, and duty,
  not a steering-servo angle.

External control-model evidence:

- Re-checked on 2026-06-08 with `smart-search fetch`; both Thomas Fermi and
  MathWorks pages fetched successfully through the configured web-fetch path.
- Fetched `https://thomasfermi.github.io/Algorithms-for-Automated-Driving/Control/PurePursuit.html`
  with `smart-search fetch`. The page describes pure pursuit for the kinematic
  bicycle model as choosing a front wheel angle `delta` and acting by setting
  that steering angle.
- Fetched `https://www.mathworks.com/help/robotics/ref/purepursuit.html` with
  `smart-search fetch`. The block is documented for car-like or
  differential-drive vehicles as outputting linear velocity and curvature; it
  also states that angular velocity is calculated by multiplying curvature by
  linear velocity.
- Fetched `https://raw.githubusercontent.com/ros-navigation/navigation2/main/nav2_regulated_pure_pursuit_controller/README.md`
  and related Nav2 regulated pure pursuit docs/source. The README describes
  finding curvature to the lookahead point and applying it to velocity commands,
  while the source computes a curvature from the carrot point before producing
  velocity commands.
- These sources are only auxiliary evidence for the actuator boundary. Local
  RT1064 source and current `control.cpp` remain the deciding evidence for this
  repository.

Git regression check:

- Commit `103daa6` changed `code/tracking/mainline.cpp` to add
  `k_error_forward_bias`, flip `lookahead_error()` to
  `-std::atan2(dx, dy + k_error_forward_bias)`, and add
  `control_ref_point()` with raw wheel point `(RAW_W/2, RAW_H*0.78)` IPM lookup.
- `git grep -n "pure_angle" 103daa6 -- .` and the same grep at `bdc7b27` both
  returned no matches, so neither commit imported RT1064 `pure_angle`.
- `103daa6:code/core/control.cpp` and `bdc7b27:code/core/control.cpp` have the
  same blob hash `6e157b0c24cf515b60e4dff42f5cd86a7db7bf03`; `git diff
  103daa6 bdc7b27 -- code/core/control.cpp` is empty.
- `bdc7b27` did change tracking contracts such as search-center/width update
  behavior, but not the `guide_error -> target_yaw -> yaw_cmd` control formula.

Decision:

- Do not mechanically replace current `guide_error` with RT1064 `pure_angle`.
  The reference output actuator is a steering servo, while current control is
  differential yaw-rate. That would be a control-architecture change, not a
  line-tracking reference alignment fix.
- Fix the misleading comment only. The previous comment called
  `lookahead_error()` "RT1064 pure tracking error"; it should instead say this
  is the heading-style guide error consumed by the current yaw outer loop, while
  RT1064 also computes a separate `pure_angle` for the servo.

Detailed comparison table:

| 对照项 | RT1064 参考版 | 当前 `front_car_mainline` | Research conclusion |
| --- | --- | --- | --- |
| Control reference point | `main.c:375-401` maps the raw wheel point `(W/2, H*0.78)` through `mapx/mapy`, writes nearest midline start to `(cx, cy)`, then resamples. | `mainline.cpp:920-940` uses `control_ref_point()` with the same raw wheel-point lookup when IPM is available, otherwise falls back to current hardware calibration. | Safe reference-alignment area: this is geometry normalization, not actuator control. |
| Heading-style error | `main.c:408-420` computes `error=-atan2f(dx, cy - y + 0.2 * pixel_per_meter)` and `error_near`, but the active servo path below does not feed them to `pid_solve`. | `mainline.cpp:888-917` computes `guide_error=-atan2(dx, dy + k_error_forward_bias)`. | Current `guide_error` resembles RT1064 `error`, not RT1064 `pure_angle`. |
| Servo pure pursuit | `main.c:428-444` computes `pure_angle=-atanf(pixel_per_meter * 2 * 0.2 * dx / dn / dn) / PI * 180 / SMOTOR_RATE`, calls `pid_solve(&servo_pid, pure_angle)`, clamps `angle`, then outputs `smotor1_control(servo_duty(SMOTOR1_CENTER + angle))`. `smotor.h:21-22` says `SMOTOR_RATE` maps front-wheel angle to steering servo angle; `smotor.c:5-6` defines `servo_pid`. | Current repo has no steering servo `servo_pid`, `SMOTOR1_CENTER + angle`, or `servo_duty` in the drive chain. | Not directly portable. Copying this formula into `guide_error` would change the controller output meaning from yaw-rate demand to servo-angle demand. |
| Current visual outer loop | No direct equivalent in RT1064; RT1064 controls a steering servo. | `control.cpp:231-258` maps `guide_error -> target_yaw` through PD, sign, straight small-error scale, and yaw-rate clamp. | This is the current differential-drive contract. Tuning or formula changes here are control/PID work, not pure tracking reference alignment. |
| Current yaw and wheel chain | No direct equivalent in RT1064 line-tracking servo chain. | `control.cpp:260-326` maps `target_yaw -> yaw_cmd -> target_l/target_r` via yaw-rate feedback and differential kinematics. | Straight-road twisting must be investigated through `guide_error` stability, outer-loop parameters, yaw feedback, and wheel geometry; RT1064 `pure_angle` alone does not explain the full chain. |
| External kinematics | Ackermann/bicycle-model pure pursuit sources compute a steering/front-wheel angle `delta`, matching RT1064's servo consumer shape. | Differential-drive sources express pure pursuit as linear velocity plus curvature/angular velocity; MathWorks explicitly documents curvature output and angular velocity as curvature times linear velocity. | If future work introduces pure-pursuit curvature, the contract must be `curvature/yaw-rate -> target_yaw/yaw_cmd`, not RT1064 `pure_angle -> guide_error`. |

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `main.c:408-444` computes both `error=-atan2(...)` and `pure_angle=-atan(...)`; active servo path uses `pure_angle -> servo_pid -> smotor1_control`. | Current `mainline.cpp` publishes heading-style `guide_error`, and `control.cpp` maps it to differential `target_yaw/yaw_cmd`; this is not RT1064 servo `pure_angle`. | Comment-only correction in `code/tracking/mainline.cpp:888` plus docs table in `docs/控制参数笔记.md`. | Prevent future audits from treating the current guide-error formula as the exact RT1064 pure-pursuit servo command. No behavior change until the control architecture is explicitly reviewed. | Runtime formula, thresholds, state, old midline, and control output are unchanged. This records an architecture boundary instead of adding a fallback or tuning guess. |
| External pure-pursuit material separates steering-angle output from curvature/angular-velocity output. | Current project has no `servo_pid`/`SMOTOR` consumer; the physical consumer is differential wheel duty. | Added source-backed control-model evidence to the task research note and tracked control-parameter doc. | This prevents future "reference alignment" from silently changing actuator semantics. | Documentation-only evidence update; no cache, smoothing, stale frame reuse, threshold, PID, or runtime output changed. |

## 2026-06-08 Push-Chain Protection Recheck

User concern: every push must be rechecked so historically meaningful special
handling is not accidentally deleted. This pass did not change runtime code.
It re-audited the current `origin/main` chain, the known reference versions, and
the four fixed read-only agent roles.

Scope correction: the reference implementation remains the primary contract.
The push chain is a regression-evidence and historical-intent index only; it
must not override a direct reference-version behavior contract.

Repository state:

- `git fetch origin main --prune` confirmed `HEAD == origin/main ==
  086844b`.
- Tracked working tree was clean before and after the audit. Local `.trellis/`,
  `.diag/`, and build directories are ignored.
- `mcp__fast_context__fast_context_search` was used for the local
  `CROSS_IN/farline/solve_cross_mid` data-flow search, then every claim below
  was verified by direct file reads and git history.

Four fixed read-only agent conclusions:

- Global push-chain audit: no confirmed evidence that a historical special
  handling was deleted after `bdc7b27`; current highest-protection item is
  still `old_l`.
- CROSS_IN/farline audit: do not delete `old_l`; `086844b` correctly preserves
  continuity but prevents reset-initialized index `0` from becoming fake
  evidence.
- Straight/current implementation audit: `bdc7b27` exposed missing identity
  gates; `52f0801` and `724c7cb` now reject raw trace crossing and IPM
  left/right work-point reversal for covered dual-side cases.
- Superseded Unity ring audit: the old AIB/BW pending path was later archived
  under `docs/reference/unity_CD_old.cpp`. Active ring entry now follows RT1064
  `circle.c::check_circle()`.

Historical special handling still present:

| 历史提交 | 当时解决的问题 | 当前承载点 | 当前判断 |
| --- | --- | --- | --- |
| `adfa1ce` | 十字远线存在但 L id 闪断会停车。 | `code/tracking/cross.cpp:267-358` keeps same-side `old_l` only after current farline rebuild succeeds; `086844b` adds `old_l_source` guard. | 保留，不能删。 |
| `a11ad36` | 十字远线起扫行不对。 | `code/tracking/cross.cpp:18` keeps `k_cross_far_begin_y` scaled from reference `167/240`. | 保留。 |
| `ce65c9d` / `e1069df` | 搜索中心不跟随导致丢线停车，但不能用未验证 seed 更新。 | `code/tracking/mainline.cpp:947-978` updates `mid_position` only after current trace survives. | 保留。 |
| `331f55b` / `6a9f9f5` | 十字刚进入时中线过短导致硬停死锁；元素帧要有明确后段合同。 | `k_element_min_mid_step=3`, `frame_action_t`, `frame_mode_t`, and frame-start element action in `mainline.cpp`. | 保留。 |
| `103daa6` | 控制中线起点/误差计算需要对齐参考版车轮点。 | `code/tracking/mainline.cpp:919-940` uses raw wheel point IPM lookup before fallback to hardware `CONTROL_CENTER_X`. | 保留。 |

Push-chain status from baseline `103daa6` to `086844b`:

| commit | 行为变化 | 当前状态 | 仍需关注 |
| --- | --- | --- | --- |
| `bdc7b27` | 拆分 single-side `l_ok` 与 strict double-L `l_pair_ok`; ring 对侧合成只做 detection; mainline 合同重整。 | 参考对齐方向成立，但这是回归暴露点。 | single-side 无对侧锚点仍不能硬拒绝。 |
| `eca5910` | 增加 cross/farline/midline 诊断。 | 诊断层，无运行时策略变化。 | 只需保持日志字段可读。 |
| `00a2ff0` | live 状态变化才打印并 beep。 | 调试层已可用。 | 无算法影响。 |
| `bf06e90` | `CROSS_STATE_BEGIN` 在 strict pair 消失时退出；同帧新进入元素不立即选线。 | 已对齐当前帧状态合同。 | 真实 cross replay 仍缺。 |
| `7e5663d` | ring 入口改为 delayed first/second confirmation。 | 已归档到 `docs/reference/unity_CD_old.cpp`，不再是 active 主链。 | 真实 RT1064 ring replay 仍缺。 |
| `033b633` | 修正 pending timing / false-ring wait。 | 已归档到 `docs/reference/unity_CD_old.cpp`，不再是 active 主链。 | 只作 Unity 旧路径回溯。 |
| `02dc1e0` | ring first/second image basis 对齐 `AIB/BW`。 | 已归档到 `docs/reference/unity_CD_old.cpp`，不再是 active 主链。 | 只作 Unity 旧路径回溯。 |
| `a10bf50` | 增加 tracking 协作规范。 | 流程层。 | 每次行为改动必须继续写固定表。 |
| `52f0801` | raw trace 身份漂移拒绝。 | 当前样本覆盖 `t28/t32/straight_cross_like`。 | single-seed 风险仍存在。 |
| `724c7cb` | IPM 后左右 work-point 反序拒绝；不加车道宽度阈值。 | 参考支持身份顺序，不支持宽度 reject。 | 未覆盖 CROSS_IN farline。 |
| `086844b` | `old_l` source guard; far source/reuse diagnostics; ring pending-second blocks new cross. | `old_l` source guard 保留；ring pending cross gate 已随 Unity 旧路径归档。 | 缺真实 `CROSS_IN NEW -> REUSED` 样本。 |

Full current `.diag` coverage scan:

- Scanned all image files under `.diag` with host `--analyze`.
- No existing checked-in `.diag` sample entered `CROSS_STATE_BEGIN` or
  `CROSS_STATE_IN`.
- All scanned frames reported `far_src=0/0` and `far_reuse=0/0`, so the current
  samples validate no-regression for ordinary/straight frames but do not
  validate far-L reuse on a real cross sequence.

Final validation in this pass:

- `git diff --check` passed.
- `bash code/test.sh --host` passed.
- `bash code/test.sh` passed.
- Targeted analyze:
  - `t16`: `line_found=1`, `reject=0`, `idrej=0`, `cross_state=0`,
    `ring_pending_stage=0`, `guide=-21.5208`.
  - `t28`: `line_found=0`, `reject=3`, `idrej=1`.
  - `t32`: `line_found=0`, `reject=3`, `idrej=1`.
  - `t56`: `line_found=0`, `reject=3`, `idrej=2`.
  - `t60`: `line_found=1`, `reject=0`, `idrej=0`, `guide=12.8786`.
  - `straight_cross_like`: `line_found=0`, `reject=3`, `idrej=4`.
- Replay smoke:
  `./code/build-host/front_car_mainline --replay .diag/video_crop_input/t16.png 2`
  printed `far_src=0/0` and `far_reuse=0/0` on both frames.

Current no-code-change decision:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 preserves far-L id variables across `cross_farline()` calls while `CROSS_IN` uses `far_Lpt*_rpts*s_id` as the midline start; Unity has no direct far-L id equivalent. | Current code already preserves `old_l` only when the current farline point list rebuilds successfully and the prior source is known. | No runtime code change in this pass. | Deleting `old_l` would risk reintroducing the `adfa1ce` stop; adding drift/width/reuse-count thresholds has no reference or sample evidence. | Current code fails closed on seed/trace/IPM/resample failure, rejects reset index `0` without prior source, and reports `far_src/far_reuse`; no stale midline or old farline points are reused. |
| Unity `check_ring()` uses `AIB/BW` scans, pending delay, same-direction second confirmation, and `roll_times == 0`; first detection is not an immediate ring action. | This was the old Unity-aligned path and has since been archived under `docs/reference/unity_CD_old.cpp`; active ring code follows RT1064. | No runtime code change in that earlier pass; later correction archived this path. | Keeping this row only documents why the old archive exists. | It must not be used as the active mainline contract. |

## 2026-06-08 Ring Pending Blocks New Cross Entry (Superseded Unity Path)

User concern at that time: ring false/pending behavior needed direct reference
alignment against Unity CD.cpp. This section is now superseded for active
runtime behavior by the later RT1064 ring source correction; it remains only as
history for the archived Unity path.

Reference check:

- Unity reference `CD.cpp:1307` allows new cross only when
  `ring_times < 2 && roll_times == 0`.
- Unity reference `CD.cpp:1356-1387` uses `ring_times == 2` for the second ring
  confirmation and final entry.
- Unity reference `CD.cpp:1389-1415` uses `ring_times == 1` for the first wait
  before second confirmation, so first pending still satisfies `ring_times < 2`.
- Unity reference `CD.cpp:1419` derives `roll_times` from `CD.PA > ramp_angle`;
  current runtime has no pitch/ramp angle input, so that half remains an input
  limitation rather than a safe local `ring.cpp` fix.

Current implementation check:

- `code/tracking/element.cpp` previously ran `cross_process()` before ring
  pending processing. If strict double-L appeared during `ring.pending_stage==2`,
  cross could enter and clear `rt->ring`.
- `code/tracking/ring.cpp` uses `k_ring_pending_first=1` and
  `k_ring_pending_second=2`, matching the reference first-wait / second-check
  shape.

Change rationale table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `CD.cpp:1307` allows new cross only when `ring_times < 2 && roll_times == 0`; `CD.cpp:1356` says `ring_times == 2` is second ring confirmation. | Current `element_process()` ran `cross_process()` before ring pending, so second pending could be stolen by a new cross and then `rt->ring = {}`. | Added `ring_blocks_cross_entry()` and changed `element.cpp` scheduling so existing cross still runs first, but ring active/pending-second/false-wait stages run before any new cross entry. | This maps directly to `ring_times < 2`: pending first remains allowed, pending second is protected, confirmed ring is protected. | The edit only blocks new cross entry while ring is already in a protected state; it does not synthesize lines, change midline, change thresholds, or keep old control output. Ring still confirms, times out, or clears from current-frame state. |
| `CD.cpp:1419` uses `CD.PA > ramp_angle` to set `roll_times`, and cross entry also requires `roll_times == 0`. | Current `runtime_t/control_feedback_t/imu_feedback` has no PA/pitch chain. | Did not implement `roll_times` in `ring.cpp`. | Using yaw-rate or a guessed threshold would not match the reference input. | The limitation is recorded; no fake slope/roll gate was added. |

Validation:

- `git diff --check` passed.
- `bash code/test.sh --host` passed.
- `bash code/test.sh` passed.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t16.png --report /tmp/t16_after_ring_gate.txt`
  remained valid: `line_found=1`, `track_reject_reason=0`, `ring_pending_stage=0`,
  `cross_state=0`, `trace_identity_reject=0`.
- `./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t60.png --report /tmp/t60_after_ring_gate.txt`
  remained valid: `line_found=1`, `track_reject_reason=0`, `ring_pending_stage=0`,
  `cross_state=0`, `trace_identity_reject=0`.
- Batch analyze over `.diag/video_crop_input/*.png` and `.diag/synth/*.png`
  showed no new ring/cross trigger on the current samples.

## 2026-06-08 CROSS_IN Far-L Reuse Whitebox Coverage

User concern: the push chain must be checked carefully so historically
meaningful special handling is not accidentally deleted. The remaining hard
gap was not another runtime behavior change; it was that existing replay images
never entered `CROSS_STATE_IN`, so the `old_l` continuity branch was only
verified by code inspection.

Reference and current check:

- RT1064 `cross.c:15-16` stores `far_Lpt*_rpts*s_id` as persistent farline L
  ids; `cross.c:227-247` clears `far_Lpt*_found` and overwrites ids only when a
  new far L is found.
- RT1064 `main.c:363-371` consumes `far_Lpt*_rpts*s_id` as the start index for
  farline-based midline generation in `CROSS_IN`.
- Unity `CD.cpp:1293-1318` has no direct farline L-id equivalent; it keeps
  cross through `cross_times/set_ED()`.
- Current `code/tracking/cross.cpp:267-358` keeps the same-side old index only
  after current farline points rebuild successfully, `new_l < 0`, previous
  source is known, and the old index still fits the current point count/tail.
- Current `code/tracking/mainline.cpp:543-688` consumes only current farline
  points from `left_l/right_l` onward; it does not reuse old points or old
  midline.

Change rationale table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 keeps persistent farline L ids and uses them as the `CROSS_IN` farline-midline start; Unity has no direct farline L-id equivalent. | Current runtime already has the correct source guard, but checked-in replay images do not enter `CROSS_STATE_IN`, so `NEW -> REUSED` was not executable coverage. | Added host-only `code/test/cross_farline_reuse_test.cpp`, wired it into `code/CMakeLists.txt` only when `SMARTCAR_CROSS_COMPILE=OFF`, and made `code/test.sh --host` run it. | The test directly exercises current `build_cross_farline()` without changing `code/tracking/` runtime behavior: first frame finds a new far L, second frame rebuilds current farline points with no new L and reuses the previous valid index, third frame fails closed, and reset index `0` without source is rejected. | This is test-only coverage. It does not synthesize runtime midlines, does not change thresholds, does not keep old farline points, and does not add a replay fallback. Validation passed: `git diff --check`, `./code/build-host/cross_farline_reuse_test`, `bash code/test.sh --host`, `bash code/test.sh --reconfigure`, `bash code/test.sh`, targeted analyze, and valid `.diag` batch scan. |

Validation:

- `git diff --check` passed.
- `./code/build-host/cross_farline_reuse_test` passed with
  `cross_farline_reuse_test: ok`.
- `bash code/test.sh --host` passed and ran `cross_farline_reuse_test: ok`.
- `bash code/test.sh --reconfigure` passed for target build.
- `bash code/test.sh` passed.
- `./code/build-host/front_car_mainline --replay .diag/video_crop_input/t16.png 2`
  printed `far_src=0/0` and `far_reuse=0/0` on both ordinary frames, confirming
  replay formatting still works.
- Targeted analyze stayed consistent:
  - `t16`: `line_found=1`, `reject=0`, `idrej=0`, `cross_state=0`,
    `ring_pending_stage=0`, `guide=-21.5208`.
  - `t28`: `line_found=0`, `reject=3`, `idrej=1`.
  - `t32`: `line_found=0`, `reject=3`, `idrej=1`.
  - `t56`: `line_found=0`, `reject=3`, `idrej=2`.
  - `t60`: `line_found=1`, `reject=0`, `idrej=0`, `guide=12.8786`.
  - `straight_cross_like`: `line_found=0`, `reject=3`, `idrej=4`.
- Valid replay corpus scan over `.diag/video_crop_input` and `.diag/synth`
  covered 16 images and found `triggers=0` for ring/cross state.

Remaining limitation:

- This closes executable coverage for the current `build_cross_farline()` L-index
  continuity contract, including `NEW -> REUSED` and reset-zero guard. It is not
  a real camera `CROSS_STATE_IN` replay. A future real cross image sequence
  should still be captured when available, but deleting or thresholding `old_l`
  is not justified by the current evidence.

## 2026-06-08 Ring Reference Source Correction

User correction: Unity CD.cpp must not remain the active ring contract. The
Unity-aligned `check_ring/AIB/BW/pending/ring_times` source was copied to
`docs/reference/unity_CD_old.cpp` and the active mainline was changed back to the RT1064
`circle.c::check_circle()` chain.

Change rationale table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `circle.c:23-31` enters `CIRCLE_LEFT_BEGIN` from `Lpt0_found && !Lpt1_found && is_straight1`, and enters `CIRCLE_RIGHT_BEGIN` from `!Lpt0_found && Lpt1_found && is_straight0`. RT1064 `main.c:330-347` checks cross first and clears circle when cross exists. | Current mainline had Unity CD.cpp-only `AIB/BW` scans, pending first/second confirmation, false-ring wait, and `ring_blocks_cross_entry()`. | Archived Unity `CD.cpp` under `docs/reference/unity_CD_old.cpp`, restored active `code/tracking/ring.cpp` to direct single-side L + opposite-straight entry, removed `ring_blocks_cross_entry()`, and removed `pending/rpend` active report fields. | The user explicitly chose the RT1064 ring chain as the mainline contract. Keeping Unity pending in active code would mix two references and make future audits ambiguous. | This removes an extra confirmation/state chain instead of adding a fallback. Ring still enters only from current-frame L/straight evidence; no old midline, old boundary, smoothing, or synthetic geometry is introduced. |

Validation:

- `git diff --check` passed.
- `python3 ./.trellis/scripts/task.py validate 06-07-cross-begin-state-contract`
  passed.
- `bash code/test.sh --host` passed and ran `cross_farline_reuse_test: ok`.
- `bash code/test.sh` passed.
- Active code grep for `pending_/rpend/ring_pending/check_ring_like_reference/AIB/BW/ring_times/ring_blocks_cross_entry`
  returned no matches.
- `--analyze` / `--replay` smoke on `.diag/video_crop_input/t16.png` printed
  only `ring_kind` and `ring_state`; no active `rpend` or `ring_pending_*`
  report fields remain.

## 2026-06-08 Existing Diag Corpus Coverage Audit

Goal: check whether the current local `.diag` corpus can prove the two remaining
runtime paths: real camera `CROSS_STATE_IN` far-L reuse and RT1064-style ring
`BEGIN -> IN -> RUN -> OUT -> END`.

Command summary:

```text
find .diag -maxdepth 3 -type f \( -iname '*.png' -o -iname '*.jpg' -o -iname '*.jpeg' -o -iname '*.bmp' \)
code/build-host/front_car_mainline --analyze <image> --report <tmp-report>
```

Result:

- 64 image files were present under `.diag`.
- 16 images were accepted by the host analyzer:
  `.diag/synth/straight_cross_like.png` plus 15
  `.diag/video_crop_input/t*.png` images.
- 48 images were rejected before tracking because their size was not the
  expected `160x120` analyzer input:
  - `.diag/video_console/t04.png`: `1960x190`
  - `.diag/video_frames/frame_01.png`: `320x143`
  - `.diag/video_full/t04.png`: `1610x720`
  These are console/full-frame artifacts, not direct host-analyze samples.
- All 16 accepted samples reported `ring=0/0`, `cross_state=0`,
  `far_src=0/0`, and `far_reuse=0/0`.
- Accepted sample aggregate:
  - `line_found=1`: 3 images (`t16`, `t36`, `t60`)
  - `line_found=0`: 13 images
  - `track_reject_reason=3`: 12 images
  - `track_reject_reason=4`: 1 image
  - `trace_identity_reject=1`: 2 images
  - `trace_identity_reject=2`: 1 image
  - `trace_identity_reject=4`: 1 image

Coverage conclusion:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `cross.c/main.c` needs real `CROSS_IN` frames to prove current farline L id reuse on camera data. | Current local accepted `.diag` images never enter `CROSS_STATE_IN`; host whitebox already covers owner-function `NEW -> REUSED`. | No runtime code change. Recorded corpus coverage limits. | Existing images cannot prove the real camera path, so the limitation must stay explicit. | This does not add synthetic runtime behavior; it only states that current samples are insufficient. |
| RT1064 `circle.c` ring contract is a state sequence from `BEGIN` through `END`. | Current local accepted `.diag` images all report `ring=0/0`; no ring stage is exercised. | No runtime code change. Keep the real ring replay gap open. | Passing t16 smoke only proves formatting/build health, not ring behavior. | No fallback, threshold, or state hold was added to make tests pass. |
| Host analyzer expects `160x120` direct input. | Console/full-frame `.diag` files are larger visualization artifacts and fail before tracking. | No runtime code change. Classified them as non-coverage artifacts. | Prevents treating size-mismatch failures as tracking regressions. | The failed files never reached tracking; no algorithm path is hidden. |
