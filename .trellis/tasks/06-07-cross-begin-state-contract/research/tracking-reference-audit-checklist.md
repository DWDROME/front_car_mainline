# Tracking Reference Audit Checklist

## Read This First: Latest Contract Index

This file is append-only research, so older sections may show earlier
intermediate positions. Use this index to resolve conflicts:

1. Active reference priority:
   RT1064 is the primary contract for ordinary tracking/cross/ring shape.
   Front_Car history explains why current `mid_position/width_base` exists.
   Git history is regression evidence, not the reference contract.
2. Same-trace left/right dual hypothesis:
   rejected. Do not implement and do not revive it as a plan. See
   `Post-Rejection Audit: Why Dual Hypothesis Was Not Needed`.
3. Single-side/no-opposite-anchor identity:
   still underdetermined from static code alone. Do not hard-reject single-side
   frames with center/width/drift/temporal rules without real-frame proof.
4. Current implemented learning-order contract:
   a learning-order guard only. For frame-start ordinary frames, delay
   `mid_position/width_base` learning until `publish_track_result()` succeeds.
   This 2026-06-09 tightening follows the new ordinary-frame complete
   forward-lookahead publish gate: a short or backward-lookahead frame must not
   teach the next seed-search center. See
   `Formal Learning-Order Contract` and
   `Learning-Order Truth Table And Impact Scope`.
5. Candidate boundary:
   preserve already-in-cross/ring timing for the first patch, preserve
   `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` before learning, preserve
   the internal `publish_track_result()` / `midline_has_forward_lookahead()`
   semantics, and pass an explicit frame-start `allow_width_base` flag into
   `update_search_center()`.
6. Remaining risk after that candidate:
   a wrong single-side identity that still passes the complete forward-lookahead
   publish gate can still learn and publish `guide_error`. That requires
   diagnostics or real-frame evidence before any stricter identity predicate is
   added.

## Known Issues To Verify

- [x] Cross BEGIN stale state: BEGIN must exit when strict pair evidence disappears; no fallback midline.
- [x] Frame-start element contract: newly entered cross/ring must not affect current-frame midline selection.
- [x] Ring active reference source: RT1064 `circle.c::check_circle()` is the
  current mainline contract.
- [x] Ring old Unity chain: `check_ring/AIB/BW/pending/ring_times` is archived
  under `docs/reference/` and must not be used as the active contract.
- [x] Straight tracking regression audit: dual-side raw trace and IPM reversal
  cases are covered; single-seed/no-opposite-anchor risk remains listed below.
- [x] Historical validation recorded: host/device builds, straight/crop diagnostic
  replays, and targeted regression commands exist from earlier passes; do not
  report them as newly run in the current no-test audit.
- [x] CROSS_IN far-L whitebox coverage: host-only test covers `NEW -> REUSED`,
  failure cleanup, and reset-zero source guard for current `build_cross_farline()`.
- [ ] Real camera CROSS_IN replay: still needs a captured sequence that reaches
  `CROSS_STATE_IN` and prints `far_src=1 -> 2` / increasing `far_reuse`.
- [ ] Real ring replay: still needs a captured sequence that proves RT1064-style
  ring BEGIN -> IN -> RUN -> OUT -> END on camera input.
- [ ] Single-seed straight tracking gap: still needs sample-backed handling if
  opposite-side crawl appears without a current opposite anchor.

## Evidence Notes

- Current repo state and command outputs must be checked before declaring done.
- 2026-06-08 trace identity pass: see
  `research/trace-identity-audit.md` for the four-role audit, reference
  contract, regression chain, validation commands, and remaining risks.
- 2026-06-08 CROSS_IN far-L audit: keep `old_l` continuity, but require a prior
  far-L source before reuse and print source/reuse diagnostics.
- 2026-06-08 ring source correction: Unity pending/AIB/BW/ring_times was
  archived as old; active ring entry follows RT1064 single-side L plus opposite
  straight.
- 2026-06-08 whitebox coverage audit: `code/test.sh --host` now runs
  `cross_farline_reuse_test`, which exercises the current `old_l` source guard
  without changing runtime tracking behavior.

## 2026-06-08 Current Issue Status Matrix

This table is the current single-page status for the problems raised in this
debug thread. "Solved" means current code plus recorded validation directly
covers the contract. "Limited" means the code direction is reference-aligned but
real replay/input evidence is still missing. "Do not change" means the audited
behavior is intentionally different because current hardware/control
architecture is different.

| Problem | Reference contract | Current owner / evidence | Status | Next action |
| --- | --- | --- | --- | --- |
| Cross BEGIN stayed active after strict double-L disappeared, causing `cross=1` with `pair=0/0` and sometimes no midline. | Cross entry/BEGIN must depend on strict double-L evidence; if both strict Ls are absent, BEGIN must leave instead of keeping stale element mode. | `code/tracking/cross.cpp:373-430` exits via `cross_leave()` when `both_l` is false, and only enters `CROSS_STATE_IN` when strict L is near. `trace-identity-audit.md:398` records this as aligned; validation notes are at `trace-identity-audit.md:416-431`. | Solved for current code contract. | Still capture a real camera cross sequence if one appears; checked-in `.diag` images did not enter `CROSS_STATE_BEGIN/IN`. |
| Newly entered cross/ring in `element_process()` could affect current-frame midline selection. | Current-frame control should use frame-start element state; newly entered element state should affect the next frame, not steal the current midline. | `code/tracking/mainline.cpp:228-270` classifies with `action->cross_state0`, `action->ring_kind0`, and `base_candidates_ready`; `mainline.cpp:1067-1083` snapshots before `element_process()` and records mode fields. | Solved for current code contract. | Keep this frame-start contract; do not simplify it back into post-element reads. |
| CROSS_IN farline can miss a new far L for one frame; deleting `old_l` may reintroduce stopping. | RT1064 keeps far-L ids across `cross_farline()` calls and consumes those ids for `CROSS_IN` farline midline start. | `code/tracking/cross.cpp:267-358` preserves an old index only after current farline points rebuild and previous source is known. `trace-identity-audit.md:489-547` records the host-only `cross_farline_reuse_test` coverage. | Solved by code inspection and whitebox test; limited by lack of real camera `CROSS_STATE_IN` replay. | Do not delete `old_l`; do not add drift/width/reuse-count thresholds without reference or real sample evidence. |
| Ring mainline should not keep the Unity CD.cpp chain. | Active reference is RT1064 `circle.c::check_circle()`: single-side L + opposite straight directly enters circle BEGIN. Unity `check_ring/AIB/BW/pending/ring_times` is now old comparison only. | `code/tracking/ring.cpp` has been restored to RT1064-style direct entry; `docs/reference/unity_CD_old.cpp` keeps the old Unity source and is not listed in `code/CMakeLists.txt`. Active `code/` grep has no `pending/rpend/check_ring/AIB/BW/ring_times/ring_blocks_cross_entry` hits. | Solved for active code and docs contract; limited by lack of real ring replay. | Capture real camera ring sequence later to validate BEGIN -> IN -> RUN -> OUT -> END behavior. |
| Straight tracking crawled to the opposite side after the regression region. | Reference keeps left/right ownership separate; no lane-width fallback is used to repair swapped sides. | `code/tracking/mainline.cpp:375-403` rejects raw trace identity crossing; `mainline.cpp:130-147` rejects IPM-side reversal before boundary/midline consumers. `trace-identity-audit.md:150` records the fixed table and validations. | Solved for covered dual-side raw/IPM crossing cases. | Single-seed/no-opposite-anchor cases remain a watch item; do not hard-reject single-side tracking without reference/sample proof. |
| Straight-road twisting may be blamed on RT1064 `pure_angle`. | RT1064 `pure_angle` feeds a steering servo path, not a differential yaw-rate path. External pure-pursuit material also separates Ackermann steering-angle output from differential curvature/yaw-rate output. | `docs/控制参数笔记.md:217-242` and `trace-identity-audit.md:265-360` separate `error`, `pure_angle`, current `guide_error`, current `target_yaw/yaw_cmd`, and external curvature/yaw-rate evidence. | Do not change runtime formula from this evidence. | If twisting persists, inspect `guide_error` stability, `outer_kp/outer_kd/straight_turn_scale`, yaw feedback, wheel track/diameter calibration, and real logs as a control/diagnostic task. |
| Stale docs could drive future wrong fixes. | Reference behavior is the primary contract; push history is regression evidence only. | `docs/流程图.md` now states this rule and shows RT1064-style ring entry; `workflow-norms-audit.md` records the Unity-to-RT1064 correction. | Solved for the known stale ring-source docs. | Keep updating docs when code/audit contracts change. |

## Current Hard Gaps

- No checked-in real camera sequence reaches `CROSS_STATE_IN` with
  `far_src=1 -> 2` and increasing `far_reuse`; current whitebox coverage proves
  the owner function but not the camera path.
- No checked-in real ring replay proves RT1064-style ring BEGIN/RUN/OUT/END on
  current camera input.
- Unity PA/pitch/ramp `roll_times` is no longer part of the active mainline
  ring contract; keep it only in old-reference notes unless the user explicitly
  asks to reintroduce the Unity path.
- Single-seed straight tracking without an opposite-side anchor is not broadly
  solved by the existing dual-side identity gates. It should remain observed,
  not patched with a generic width threshold.

## 2026-06-08 Renewed Static Audit, No Tests By User Request

User constraint for this pass: do not run tests or replay now. Therefore the
old validation records in this task remain historical evidence only; they must
not be reported as newly executed validation for this pass.

Runtime state at audit start:

- `HEAD == origin/main == aafcea8602508a517072933c996c8a92e7e6db48`.
- Tracked working tree was clean before this note.
- Four fixed read-only roles were used with one global-direction gate:
  RT1064 reference contract, current implementation owner, git regression, and
  Trellis/global check gate.
- Earlier renewed audit used `fast_context_search` for the single-seed owner
  chain, then current files and git history were read directly. In the later
  RT1064 `update_search_center()` subsection, `fast_context_search` returned
  `resource_exhausted` twice, so the evidence there is from `rg`, git history,
  and direct file reads only.

Current issue list after renewed audit:

| 问题 | 当前状态 | 本轮证据 | 后续动作 |
| --- | --- | --- | --- |
| Cross BEGIN stale `cross=1` with `pair=0/0` | Current code contract is closed. | `code/tracking/cross.cpp` keeps `strict_double_l_ok()` on `l_pair_ok`, and `cross_begin()` calls `cross_leave()` when strict pair disappears. | Keep as solved unless a new log shows strict pair still present but line missing. |
| CROSS_IN `old_l` continuity | Keep it. It is a narrowed current-farline index continuity rule, not old midline reuse. | `build_cross_farline()` clears current farline points every frame and only reuses `old_l` when previous source exists and the index fits the current point list. | Do not delete it; do not add drift/width/reuse-count thresholds without real `CROSS_STATE_IN` evidence. |
| Ring active reference source | Current active code follows RT1064 `circle.c`; Unity CD.cpp is archive only. | `ring.cpp` enters from single-side `l_ok` plus opposite `boundary_is_straight()`. Active `code/` has no Unity `pending/AIB/BW/ring_times/ring_blocks_cross_entry`. | If ring still false-triggers, inspect `l_ok` quality and `boundary_is_straight()`, not Unity pending. |
| Straight trace crossing to opposite side | Covered for dual-side raw crossing and IPM work-point reversal. | `trace_identity_reject_bits()` rejects crossing against current opposite seed or same-row cross; `work_pair_order_ok()` rejects IPM-side reversal when paired evidence is sufficient. | Watch for legal sharp curves that might be over-rejected, but do not relax without samples. |
| IPM work-point reversal could still poison next-frame search center before being rejected. | Fixed in this pass by moving `update_search_center()` after `build_frame_boundaries_and_candidates()` and after the `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` branch. | `724c7cb` added IPM reversal rejection, but current code still updated `mid_position` before that rejection; this contradicted the `e1069df` "update after verified trace" reason once IPM identity verification became a later gate. | If IPM reversal is hit, the frame now fails before search-center writeback; no threshold or fallback was added. |
| Single-seed straight crawl with no opposite anchor | Still open and now the highest straight-line risk. | `find_seeds()` upward missing-side search was introduced by `9cd95ff`, not by `bdc7b27`; `ce65c9d/e1069df` gave `mid_position/width_base` historical reasons. A wrong single-side trace can still update `mid_position` after trace success because there is no opposite anchor. | Need sample-backed owner proof before changing code. Candidate investigation: a current-frame identity gate against the opposite start column, but only if real frames prove it does not kill valid curves. |
| `track_type_keep` ordinary dual-side inertia | Watch item, not a confirmed bug. | Current `pick_track_type()` matches RT1064 point-count selection and preserves last side when both sides are long. | If straight still twists with stable dual-side evidence, inspect whether `track_type_keep` alternates with `guide_error`; do not change without log evidence. |
| Straight-road twisting blamed on RT1064 `pure_angle` | Do not change runtime control formula from this evidence. | RT1064 active path is `pure_angle -> servo_pid -> smotor1_control`; current path is `guide_error -> target_yaw -> yaw_cmd -> target_l/r`. | If visual midline is stable but car still twists, open a separate control/log audit for outer gains, yaw feedback, IMU sign/scale, wheel track, and wheel diameter. |

Current behavior-change rationale table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 ordinary tracking does not have an IPM-side reversal gate; its left/right identity mainly comes from fixed `width/2 ± begin_x` start ownership and separate left/right point arrays. | Current project added `work_pair_order_ok()` in `724c7cb` because IPM/pass-through work points can prove current-frame left/right reversal after raw trace survives. Before this pass, `update_search_center()` still ran before that later identity gate. | In `code/tracking/mainline.cpp`, move `update_search_center()` after `build_frame_boundaries_and_candidates()` and only run it when `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` is not set. | This restores the `e1069df` contract at the newer gate depth: next-frame `mid_position` may only be updated by current-frame seed/trace evidence that survived all identity checks available before element processing. | Rejected IPM-reversed frames now fail before search-center writeback. The edit does not synthesize a line, hold a previous midline, hold `guide_error`, change thresholds, or guess an opposite boundary. |
| RT1064 ordinary tracking starts from fixed `begin_y` and `center ± begin_x`, then uses point counts to select side. | Current project intentionally adds `mid_position/width_base` dynamic center from Front_Car history; `ce65c9d/e1069df` record why it was kept and moved after trace success. | No single-seed hard gate was added in this pass; recorded single-seed/no-opposite-anchor as the top open risk. | Removing dynamic center would likely reintroduce the known lost-line stop. Adding a generic single-side opposite-start-column or width/drift gate has no direct RT1064 contract or sample proof. | This pass does not reject valid single-side current-frame geometry without evidence; it only prevents an already rejected dual-side/IPM identity failure from updating persistent search center. |
| RT1064 ring and cross contracts are direct and current-frame evidence based. | Current architecture uses frame-start element action so a newly entered ring/cross affects the next frame, not the current midline. | No ring/cross runtime code change in this pass. | Copying RT1064 same-loop action timing mechanically would break the current anti-stale frame-start contract. | Current code still rejects missing current geometry; no hidden element-state fallback was added. |
| RT1064 `pure_angle` is a steering-servo command. | Current car is differential drive and consumes heading-style `guide_error` through `target_yaw/yaw_cmd`. | No control runtime code change in this pass. | The actuator boundary is different, so twisting cannot be solved by mechanically inserting `pure_angle`. | No smoothing, old-error hold, PID change, or duty hold was added. |

## 2026-06-08 RT1064 Special Audit For `update_search_center()` Timing

This subsection records the read-only reference audit for the current candidate
edit: move `update_search_center()` until after
`TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` has been checked. No tests/builds/replay
were run for this subsection by user request.

### Reference Findings

1. RT1064 has no direct `update_search_center()` equivalent.
   - `USER/src/main.c::process_image()` starts each ordinary frame at
     `img_raw.width / 2 - begin_x, begin_y` and
     `img_raw.width / 2 + begin_x, begin_y`.
   - `CODE/flash_param.c` default parameters are `begin_x = 32` and
     `begin_y = 167`.
   - The reference does not keep a per-frame `mid_position` or `width_base`
     state for the next frame's seed search.

2. RT1064 does not support a single-seed hard reject contract.
   - `findline_lefthand_adaptive()` and `findline_righthand_adaptive()` only
     trace from their own start point while the local maze condition, bounds,
     and `turn < 4` hold.
   - Ordinary side selection later uses `rpts0s_num/rpts1s_num` point counts.
   - There is no ordinary-line rule equivalent to "single left crossing the
     opposite start column must be rejected". Such a rule would be a current
     project identity rule and needs real sample proof before code changes.

3. RT1064 principles that can be migrated:
   - Current-frame evidence owns the frame: start points, traced point counts,
     and generated centerline are rebuilt in the current pass.
   - Left/right identity is preserved by separate left/right start ownership
     and separate point arrays.
   - If the selected centerline is too short, RT1064 sets `rptsn_num = 0` and
     does not update the steering servo in that branch.
   - `pure_angle -> servo_pid -> smotor1_control()` is a steering-servo chain,
     not a differential-drive yaw-rate chain.

### Candidate Edit Interpretation

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 has no dynamic search-center writeback; it starts from fixed `center ± begin_x` and `begin_y` each ordinary frame. | Current project intentionally has `mid_position/width_base` as cross-frame seed-search state; `ce65c9d` added it to avoid fixed-center lost-line stops, and `e1069df` moved it after trace success to avoid seed-only noise poisoning. | Keep `update_search_center()` but call it only after `build_frame_boundaries_and_candidates()` and after the `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` branch has not fired. | `724c7cb` added a later current-frame identity gate in IPM/work-point space. If a frame is rejected there, letting it update `mid_position` contradicts the older "only verified geometry writes next-frame center" contract. | The frame is rejected using current-frame left/right work-point reversal evidence. No previous midline, previous boundary, previous `guide_error`, synthetic opposite side, or new width/drift threshold is used. |
| RT1064 has no ordinary single-seed hard reject against center/opposite-start-column. | Current code can still accept a single-side trace when no opposite seed/trace/IPM pair exists, and that remains the highest open straight-line risk. | Do not add a single-seed hard gate in this candidate. | Without real frames, a center/opposite-start-column rule could kill valid sharp curves and cannot be claimed as RT1064 reference behavior. | Leaving this open avoids an unproven fallback-style patch; it is recorded as sample-backed future work rather than hidden by thresholds. |
| RT1064 point-count selection and too-short-centerline failure happen before steering servo update. | Current `publish_track_result()` also fails when midline is too short or lacks lookahead, but `mid_position` is an earlier persistent search state outside the control output. | The candidate protects the persistent search state, not the control formula. | A rejected identity frame should not control the next frame's seed start even if the current frame already fails. | No control smoothing or actuator hold was added; this is a visual state ownership fix. |

### Git Regression Chain Readback

This subsection answers the git-chain audit requested for the current candidate.
It is based on `git show` for `9cd95ff`, `ce65c9d`, `e1069df`, `bdc7b27`,
`52f0801`, `724c7cb`, and `aafcea8`, plus `git log -G` over
`bdc7b27..HEAD`.

| Check | Result | Evidence |
| --- | --- | --- |
| Which commits prove `mid_position/width_base` must stay? | `ce65c9d` and `e1069df`. | `ce65c9d` says constant `mid_position=80` caused one side to leave the image first, then line/L/cross/ring starvation; it added `width_base` and dynamic center. `e1069df` kept the algorithm and only moved writeback later. |
| Which commit proves `update_search_center()` should run after verification? | `e1069df`. | It explicitly moved writeback from after `find_seeds()` to after `trace_edges()` because seed-only noise could be filtered by `trace_single()` but had already poisoned the next-frame center. |
| Which commit added the later identity gate that makes the candidate necessary? | `724c7cb`. | It added `work_pair_order_ok()` after boundary/IPM work-point construction, sets `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS`, clears boundary/rpts candidates, and returns `TRACK_TYPE_NONE` when paired current-frame points prove left/right reversal. |
| Does `bdc7b27..HEAD` support a single-seed hard gate? | No. | Pickaxe over `bdc7b27..HEAD` finds identity-gate changes in `52f0801` and `724c7cb` only. Current raw gate needs an opposite seed or both traces; current IPM gate needs enough paired dual-side points. No commit establishes a no-opposite-anchor single-seed reject. |
| Is the candidate the minimal history-consistent repair? | Yes, only for the IPM-reversal timing hole. | `HEAD` still called `update_search_center()` before the `724c7cb` IPM reject branch. Moving it after that branch preserves `ce65c9d` dynamic center and extends `e1069df`'s verified-before-write rule to the newest identity verification depth. |

## 2026-06-08 Deep Algorithmic Reasoning After User Rejected Short Summary

This section separates the hard problems so a local timing fix is not mistaken
for a full straight-tracking solution.

### Layered Problem Model

| Layer | Owner | What can go wrong | Current status |
| --- | --- | --- | --- |
| Raw seed acquisition | `find_seeds()` | Fixed-row seed may find only one side, or may find mixed-row sides after upward missing-side search. | Intended history from `9cd95ff`; do not delete without reintroducing lost-line risk. |
| Raw trace ownership | `trace_edges()` / `trace_identity_reject_bits()` | A raw left trace can become right evidence, or right trace can become left evidence. | Covered only when there is an opposite seed or both traces cross on a same row. |
| IPM/work-point ownership | `build_frame_boundaries_and_candidates()` / `work_pair_order_ok()` | Raw traces survive, but after IPM/resample paired work points prove `left_x >= right_x`. | Covered by `724c7cb`, but `HEAD` still wrote `mid_position` before this gate; candidate fixes that timing hole. |
| Persistent search state | `update_search_center()` | A bad current frame can write next-frame `mid_position` and pull later seed search toward the wrong side. | Must stay because `ce65c9d` fixed lost-line stops; writeback must happen only after all currently available identity checks. |
| Midline publication | `build_selected_midline()` / `publish_track_result()` | A bad candidate can publish `guide_error`. | Too late to protect `mid_position`; not the right owner for the current candidate. |
| Control actuator | `control.cpp` | Stable visual midline may still twist due to yaw/outer-loop calibration. | Separate control/log task; RT1064 `pure_angle` cannot be mechanically ported. |

### Exact Old Failure Path Closed By The Candidate

1. `find_seeds()` produces current-frame seed bits and seed coordinates.
2. `trace_edges()` runs raw `trace_single()` on each valid seed.
3. `trace_identity_reject_bits()` can reject raw ownership only with an
   opposite seed or dual trace row-cross evidence.
4. At `HEAD` before the candidate, `tracking_process_frame()` then called
   `update_search_center()` immediately after `trace_edges()` success.
5. Only after that writeback did `build_frame_boundaries_and_candidates()` call
   `work_pair_order_ok()`.
6. If `work_pair_order_ok()` found enough paired work points with
   `left_x >= right_x`, it set `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS`, cleared
   boundaries/rpts, and made the current frame fail.
7. The current frame failed, but the persistent next-frame search center was
   already written from a frame that was later proven identity-bad.

That is the precise contradiction: after `724c7cb`, "verified before
writeback" must include the IPM/work-point identity gate, not just raw trace.

### Candidate Failure Path After The Move

1. `find_seeds()` and `trace_edges()` still run unchanged.
2. `build_frame_boundaries_and_candidates()` now runs before
   `update_search_center()`.
3. If `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` is set, ordinary frames return 0
   before center writeback.
4. In `CROSS_STATE_IN`, the rejected near-line path is cleared and only the
   cross farline path is allowed to continue; the rejected near trace still does
   not update `mid_position`.
5. Only the non-rejected branch calls `update_search_center()`, then snapshots
   ring frame-start action and runs `element_process()`.

This is fail-closed for the rejected current frame. It does not synthesize or
hold geometry.

### Why This Is Still Not Enough For The Whole Straight-Crawl Problem

The highest remaining straight-line risk is still single-seed/no-opposite-anchor:

1. `find_seeds()` returns success when either side exists.
2. `trace_single()` validates seed brightness, bounds, step count, and vertical
   gain, but not "this line is truly left/right lane identity".
3. `trace_identity_reject_bits()` cannot compare a left trace to a missing right
   seed, or a right trace to a missing left seed.
4. `work_pair_order_ok()` cannot run without enough left and right work points.
5. `pick_track_type()` is intentionally allowed to select one side when only
   one side has enough points, matching the reference point-count style.
6. Therefore a wrong single-side trace can still build a current midline and
   write `mid_position`.

This remains open because a hard single-side boundary such as "left trace must
not cross the opposite start column" is not in RT1064 and may kill legal curves
or element approaches. It needs real frames/logs that show:

- `seed_state` is single-side;
- the retained trace is visually/semantically the opposite boundary;
- raw trace/IPM dual gates cannot fire because the opposite side is absent;
- `mid_position` moves the next frame toward the wrong side;
- the same rule would not kill nearby legal turn/ring/cross approach frames.

### Reference-Fitted Next Fix Shapes, Ordered By Alignment

The next plan must preserve the RT1064 shape: single-side tracking is allowed,
current-frame point quality decides whether a centerline/control output exists,
and there is no ordinary single-side "cross center" hard reject in the
reference. Therefore the main follow-up should constrain current project's
extra dynamic state, not invent a new single-side reference rule.

| Candidate | Owner | Reference fit | Remaining risk |
| --- | --- | --- | --- |
| Move ordinary `mid_position` writeback after successful `publish_track_result()` | `tracking_process_frame()` | Closest adaptation of RT1064's "only a valid current centerline reaches actuator update"; since RT1064 has no dynamic search center, failed current midline should not teach the next frame. | Broader than current candidate; may reduce recovery from frames with valid trace but short final midline. Needs a separate audit of cross/ring frame-start timing and `ce65c9d` lost-line history. |
| Keep current candidate only, and add single-seed diagnostics for trace range vs start columns | report/debug fields | Preserves RT1064 single-side allowance while collecting proof for the no-opposite-anchor case. | Does not change behavior; requires real logs/images to become useful. |
| Gate single-side `mid_position` writeback only after a current-frame selected midline exists | `update_search_center()` caller plus selected-side result | More reference-fitted than raw hard reject because it does not reject single-side tracking itself; it only protects the extra dynamic center state. | Still a state-writeback rule absent from RT1064; must prove it does not undo `ce65c9d`. |
| Single-side raw identity gate against opposite start column | `trace_identity_reject_bits()` | Weak reference fit. It preserves left/right identity but is not present in RT1064 ordinary tracking. | Highest risk of killing legal sharp curves or element approaches; only allowed after real frame proof and nearby legal-frame counterproof. |
| Skip `mid_position` writeback for vague "suspicious" single-side frames | `update_search_center()` caller | Poor reference fit unless suspicion is tied to a concrete current-frame failure. | Too easy to become stale-center fallback; not acceptable as a generic patch. |

### Current Commit Boundary

The current tracked source edit should remain a single narrow commit:

- It closes the `724c7cb`/`e1069df` timing contradiction.
- It does not claim to solve single-seed/no-opposite-anchor.
- It does not touch ring, cross, control, seed thresholds, trace thresholds, or
  midline math.
- It should be committed separately so future single-seed work can be audited
  against a clean baseline.

### Follow-up Audit: Do Not Move To `publish_track_result()` Yet

After the user agreed to continue the reference-fitted audit, the broader
candidate was rechecked: moving ordinary `mid_position` writeback after
successful `publish_track_result()`. This subsection records why that broader
change is not implemented in the current patch.

Checked evidence:

- `fast_context_search` was available in this pass and returned the relevant
  owners: `mainline.cpp`, `element.cpp`, `cross.cpp`, `imgproc.cpp`,
  `runners.cpp`, and docs hits for the pipeline.
- Current code read directly:
  - `code/tracking/imgproc.cpp:214-326`: `find_seeds()` reads
    `mid_position` as the next-frame seed-search center.
  - `code/tracking/mainline.cpp:405-428`: `publish_track_result()` gates
    current-frame control publication by midline length and lookahead.
  - `code/tracking/mainline.cpp:943-980`: `update_search_center()` writes
    only the cross-frame seed-search state and `width_base`.
  - `code/tracking/mainline.cpp:1006-1107`: current frame order.
  - `code/tracking/element.cpp:8-45`, `cross.cpp:552-598`, and
    `ring.cpp:252-421`: element state machines do not read/write
    `mid_position`; ring detection helpers deliberately avoid dynamic
    `mid_position` for symmetric fill starts.
- RT1064 reference read directly:
  - `USER/src/main.c:532-545`: ordinary frame starts from fixed
    `img_raw.width / 2 ± begin_x, begin_y`.
  - `USER/src/main.c:395-449`: if the selected midline is too short, RT1064
    sets `rptsn_num = 0` and does not control the steering servo.
  - `CODE/imgproc.c:247-329`: left/right tracing owns separate point arrays.
- Git history read directly:
  - `ce65c9d` says constant `mid_position=80` caused one side to leave the
    image first, then line/L/cross/ring starvation; it introduced dynamic
    center plus `width_base`.
  - `e1069df` moved writeback from after `find_seeds()` to after
    `trace_edges()` specifically because `trace_single()` could filter seed
    noise and clear the failed side from `seed_state`.
  - `724c7cb` added the later IPM/work-point identity reject. That is the new
    gate depth this patch must respect.

Decision table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 has no `mid_position/width_base`; ordinary search always starts from fixed `center ± begin_x, begin_y`. If current midline is too short, it suppresses servo control for that frame. | Current project intentionally adds cross-frame seed-search state. `publish_track_result()` is a control-publication gate, while `update_search_center()` is next-frame seed-search learning. | Superseded on 2026-06-09: the earlier IPM-only timing fix did not move ordinary learning after publish; the active contract now does for frame-start ordinary frames. | The later field evidence showed short/backward ordinary lookahead itself is the risk class, so failed publish must not update next-frame seed search. | This remains fail-closed: no old midline, old boundary, old `guide_error`, smoothing, threshold, or guessed opposite side is introduced. |
| RT1064 point arrays are rebuilt from current-frame left/right tracing; no dynamic search center can be polluted. | Current `update_search_center()` already runs after raw trace filtering, and now after IPM work-point identity filtering. | Do not add a single-side or publish-success gate without real sample proof. | The still-open single-seed/no-opposite-anchor case lacks a current opposite anchor and has no direct RT1064 hard-reject equivalent. | Keeping this open avoids a hidden stale-center policy. Future handling must come from real logs that prove a wrong single-side trace updates `mid_position` and that the proposed rule does not kill valid curves/elements. |
| RT1064 element checks and run functions happen before current-frame midline selection, but there is no `width_base` low-pass state. | Current `update_search_center()` freezes `width_base` when `ring.kind != NONE` or `cross.state != NONE`. If moved after `element_process()`/`publish_track_result()`, newly entered elements would change the low-pass timing. | Leave the current pre-`element_process()` writeback timing for non-rejected base candidates. | Changing this would be a separate element-entry width-base contract change, not a consequence of the IPM identity bug. | No width thresholds or element-state fallbacks are added. The broader timing question is recorded as future evidence work, not hidden in this patch. |
| RT1064 has no separate "near trace rejected but farline still publishes" dynamic-center state; `CROSS_IN` consumes farline ids directly. | Current `CROSS_STATE_IN` can continue through `cross_process()` and successfully publish farline output after the near-line IPM order gate rejects the base candidates. In that branch, `seed_state` is not cleared by `build_frame_boundaries_and_candidates()`. | Do not mechanically call `update_search_center()` after `publish_track_result()` for all successful frames. | A naive post-publish call would reintroduce the exact bug this patch closes: a near-line `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` frame could still publish a farline midline, then write `mid_position` from the rejected near-line seed. | The current patch keeps the call inside the non-IPM-rejected branch. Rejected near lines in `CROSS_IN` may continue farline control, but they still cannot update next-frame search center. |

Four-role status for this follow-up:

- Reference contract: supports fixed start ownership and current-frame control
  suppression, but has no direct dynamic-search-center writeback equivalent.
- Current implementation: `mid_position` feeds only `find_seeds()` next frame;
  `publish_track_result()` owns current-frame `track_type/center_x/guide_error`.
- Git regression: `ce65c9d/e1069df/724c7cb` support the current 4-line timing
  fix; no checked commit proves a publish-success-only writeback contract.
- Trellis/spec gate: fixed rationale table is present; tests/build/replay are
  not run in this pass because the user explicitly prohibited testing. Full
  quality gate therefore remains blocked by user constraint, not passed.

## 2026-06-08 Single-Seed / No-Opposite-Anchor Deep Audit After `d2ccaf0`

This subsection records the renewed no-test audit after `d2ccaf0` was pushed.
It does not introduce a runtime change. The purpose is to keep the remaining
straight-crawl problem separated from the already-fixed dual-side identity
paths.

Current repo state checked in this pass:

- `HEAD == origin/main == d2ccaf050d76404eb31e74b658a3ee3249b538b8`.
- The tracked working tree was clean before this research-note update.
- `fast_context_search` returned the current owner chain:
  `mainline.cpp`, `imgproc.cpp`, `types.hpp`, report/docs hits.
- Four read-only agents were used:
  global direction guard, RT1064/git reference contract, current
  implementation data flow, and algorithm proof/candidate ranking.
- No tests, builds, replay, or analyze commands were run in this pass by user
  instruction.

### Agreement Across The Four Agents

| Role | Supported conclusion |
| --- | --- |
| Global direction guard | `d2ccaf0` only closes the IPM-reversal writeback timing hole. The highest remaining straight-line risk is `single-seed/no-opposite-anchor`. |
| RT1064 + git contract | RT1064 ordinary tracking allows independent left/right traces and point-count side selection. `9cd95ff`, `ce65c9d`, and `e1069df` do not support a broad single-side hard reject. |
| Current implementation | Single-side seed can survive `find_seeds()`, `trace_edges()`, and `work_pair_order_ok()`, then update `mid_position` and possibly publish `guide_error`. |
| Algorithm proof | The strongest reference-fitted future direction is protecting the extra cross-frame learning state, not banning single-side current-frame tracking. |

### Exact Remaining Open Path

1. `find_seeds()` uses `mid_position` as the search center and returns success
   when either side exists.
2. If only one side is found, the raw identity checks have no opposite seed to
   compare against.
3. If only one side is traced, the IPM/work-point order gate has no paired
   left/right evidence, so it correctly cannot prove reversal.
4. `update_search_center()` then uses the retained single-side seed and
   `width_base / 2` to write the next-frame `mid_position`.
5. `pick_track_type()` may select that single side by point count, matching the
   reference shape.
6. `build_selected_midline()` can offset that side into a candidate control
   midline.
7. `publish_track_result()` can publish `guide_error` if the midline is long
   enough and has lookahead.

This means there are two distinct risks:

- Learning risk: a single-side trace can update `mid_position` even if the
  later selected midline fails publication.
- Control risk: a wrong single-side trace can also publish a current-frame
  `guide_error` if it forms a long enough candidate midline.

These must not be collapsed into one generic reject rule.

### Why No Single-Side Hard Gate Is Added Now

| 参考版怎么样 | 当前代码差异 | 本轮是否修改 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `process_image()` starts from fixed `center ± begin_x, begin_y`, traces left and right independently, then ordinary logic selects by point count. It does not contain an ordinary rule that rejects a single side because no opposite anchor exists. | Current project intentionally adds `mid_position/width_base` as a next-frame seed-search state. Single-side tracking is a valid recovery path from `9cd95ff/ce65c9d/e1069df`, but it can be polluted if the retained single side is actually the opposite boundary. | No runtime hard gate was added. | A rule such as "single left must not cross the opposite start column" has no direct RT1064 equivalent and can kill legal sharp curves, ring approach, or cross approach frames. | Leaving the path open is not a fallback: it avoids inventing an unproven threshold. Current dual-side current-frame identity failures still reject/fail closed. |
| RT1064 suppresses servo control when the selected centerline is too short. | Current `publish_track_result()` already suppresses current-frame output, but `update_search_center()` writes a different persistent learning state. | Superseded on 2026-06-09: frame-start ordinary learning now waits for `publish_track_result()` success. | `frame=2911` and Image #4 made short/backward ordinary lookahead a concrete acquisition-pollution risk, not only a control-output risk. | No stale midline, old boundary, old `guide_error`, smoothing, or guessed opposite side is introduced. |
| RT1064 has no `mid_position/width_base`, so there is no direct reference line for how current extra learning should behave. | Current learning is project-specific and must be protected only by evidence-backed current-frame validity gates. | Keep `d2ccaf0` as the current runtime boundary. | The only newly proven invalidity after `e1069df` was the IPM paired reversal added by `724c7cb`; that is now before writeback. | The active runtime edit remains current-frame reject before learning, not fallback stabilization. |

### Future Candidate Ranking

| Priority | Candidate | Reference fit | Current risk |
| --- | --- | --- | --- |
| P0 | Keep `d2ccaf0` runtime as-is and require single-seed diagnostics/log proof before another behavior edit. | High. Preserves RT1064 single-side allowance and only rejects proven current-frame identity failures. | Does not solve the no-opposite-anchor case by itself. |
| P1 | If real logs prove single-side frames learn from a trace that later fails publication, gate only the single-side `mid_position` writeback on a successfully built selected midline; do not reject current-frame single-side tracking. | Medium-high. It maps RT1064 "bad centerline does not control" onto the current project's extra learning state without banning single-side geometry. | Could weaken `ce65c9d` recovery if valid single-side trace often has short final midline. Requires samples. |
| P2 | Add diagnostics for single-side trace range vs start columns and selected-side publication outcome. | High for investigation, no behavior change. | More logs but no direct fix. |
| P3 | Hard reject single-side raw trace against a center/opposite-start-column rule. | Weak. No direct RT1064 ordinary equivalent. | High false-reject risk on curves/elements; only allowed after sample proof and legal-frame counterproof. |
| P4 | Synthesize/guess the missing opposite side, clamp by width, or smooth/hold `guide_error`. | Reject. | This is fallback-style masking. |

### Current Decision

Do not change runtime code in this pass. The current correct next state is:

- keep `d2ccaf0`;
- treat `single-seed/no-opposite-anchor` as the highest remaining visual
  algorithm risk;
- do not hard-reject single-side tracking without sample-backed proof;
- do not move all `update_search_center()` calls after publication without a
  separate proof that it will not undo `ce65c9d/e1069df`;
- if a future code change is required, prefer a narrow single-side learning
  guard or diagnostics over a control/output fallback.

## 2026-06-08 Historical Dirty-State Verification Before `aafcea8`

This verification was run earlier, before the current `aafcea8` clean-tree
state. It remains useful as historical evidence for that edit batch, but it is
not a newly executed validation for the renewed static audit above. The tracked
dirty files at that earlier point were `AGENTS.md`,
`code/tracking/mainline.cpp`, `docs/控制参数笔记.md`, and `docs/流程图.md`;
`.trellis/` research/spec files remained ignored local task state.

- `git diff --check` passed.
- `bash code/test.sh --host` passed and printed `cross_farline_reuse_test: ok`.
- `bash code/test.sh` passed target-side build.
- No runtime formula, threshold, state transition, stale geometry reuse, or
  fallback behavior was changed in this dirty state.
- `.trellis/spec/quality/embedded-tracking-guidelines.md` now records the
  tracking-derived control boundary: RT1064 `pure_angle -> servo_pid` is a
  steering-servo path, while current `guide_error -> target_yaw -> yaw_cmd` is
  the differential-drive path.

## 2026-06-08 Renewed Algorithm Audit: Drop Dual-Hypothesis Expansion

This pass is analysis-only. No runtime code, tests, build, replay, or push were
performed. The user challenged the proposed "try both left/right offsets on the
same single-side trace" idea. Re-reading the current code and RT1064 reference
shows the challenge is correct.

### Corrected Layer Split

| Layer | Current evidence | Decision |
| --- | --- | --- |
| Candidate generation | Current mainline already builds `rptsc0` from `track_leftline(rpts0s, ...)` and `rptsc1` from `track_rightline(rpts1s, ...)`. RT1064 does the same in `process_image()`. | Do not add a dual-hypothesis expansion on the same trace. It is not reference-backed. |
| Candidate selection | Current `pick_track_type()` selects one of the already-built candidates by point count / previous side, matching the RT1064 shape. | Keep this shape. A wrong selected side is an ownership/evidence problem, not a missing offset-function problem. |
| Candidate attach to control point | Current `build_rptsn()` finds the nearest candidate point to `control_ref`, then overwrites that point with `control_ref`; RT1064 also overwrites `rpts[begin_id]` with `cx/cy`. | Treat attach distance as a possible diagnostic/analysis metric only. Do not turn it into a behavior gate without real frame proof. |
| Cross-frame learning | Current project adds `mid_position/width_base`, absent in RT1064. `ce65c9d/e1069df` explain why it exists and why trace-level validation matters. | If future samples prove a single-side trace pollutes learning, protect learning narrowly; do not ban single-side tracking. |

### Why The Dual-Hypothesis Idea Is Rejected

| 参考版怎么样 | 当前代码差异 | 本轮是否修改 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 traces left and right independently, offsets left with `track_leftline()` and right with `track_rightline()`, then follows one selected `track_type`. It does not run both offset identities on one single-side trace. | Current code already keeps the same two-candidate structure. The remaining single-side/no-opposite-anchor risk is that only one candidate survives with no opposite evidence to prove ownership. | No runtime code change. The dual-hypothesis proposal is withdrawn. | Adding both identities on one trace would create an invented identity-guessing layer and increase ambiguity. It does not repair the real evidence gap. | Rejecting this proposal avoids synthesizing missing geometry, holding old output, or hiding wrong ownership with extra choices. |

### Attach Distance Status

Attach distance remains useful as a proof concept but not as an approved fix.
The reason is subtle:

1. It is true that `build_rptsn()` can make a far candidate look connected by
   replacing the selected begin point with `control_ref`.
2. But RT1064 has the same overwrite pattern after finding `begin_id`.
3. Therefore a generic "attach_dist <= ROAD_HALF_WIDTH" gate is not a direct
   reference contract.
4. It may become valid only if real logs show that current project's extra
   dynamic center state selects a distant wrong single-side candidate and then
   learns from it.

So the corrected ranking is:

| Priority | Candidate | Current decision |
| --- | --- | --- |
| P0 | Keep `d2ccaf0` runtime boundary. | Approved current state. |
| P1 | Add/inspect diagnostics for single-side learning pollution. | Analysis-only candidate; no behavior change. |
| P2 | Gate only single-side `mid_position` learning after stronger current-frame proof. | Future candidate only, requires real samples and `ce65c9d/e1069df` counterproof. |
| P3 | Attach-distance behavior gate. | Not approved; diagnostic/proof metric only. |
| P4 | Single-side hard reject or dual-hypothesis expansion. | Rejected unless future evidence proves a narrower contract; current answer is no. |

### Current Working Conclusion

The remaining hard problem is not "how to build a left/right midline from a
single trace." That is already implemented and reference-aligned. The remaining
hard problem is:

> When the current frame has only one side, there may be no current-frame
> opposite anchor to prove that the surviving side still owns its declared
> identity. Current-frame control and next-frame learning must be reasoned
> separately.

Until real frame evidence narrows this, the safest reference-aligned position is
to keep single-side tracking allowed, reject only proven dual-side identity
failures, and avoid any new fallback or identity-guessing layer.

### Four-Agent Recheck For This Correction

All four read-only agents were run again after the user challenged the
dual-hypothesis idea. They did not edit files, run tests, build, replay, or
commit.

| Role | Conclusion |
| --- | --- |
| Global direction guard | Stop inventing new algorithm layers. `dual hypothesis` has the highest reference-divergence risk; `attach gate` is only a diagnostic/proof metric unless real frames justify it. |
| Current implementation dataflow | The minimum suspicious chain is `single-side wrong identity -> no opposite anchor -> selected single-side candidate -> build_rptsn control-point overwrite -> guide_error publication and/or early mid_position learning`. |
| RT1064 reference contract | RT1064 has no `TRACK_TYPE_DUAL`, no ordinary single-side hard reject, no attach-distance gate, and no same-trace dual-offset hypothesis. It does have left/right independent traces and left/right candidate offsets. |
| Git regression audit | `103daa6..bdc7b27` is a single stage7 contract commit. It split single-side `l_ok` from strict `l_pair_ok`; it did not introduce single-side legality. Later commits fixed cross BEGIN, Unity ring mixing, raw/IPM dual-side identity, old-L source guarding, and IPM-reversal learning pollution. The open point remains single-side/no-opposite-anchor. |

The corrected working rule for future edits is therefore:

> Do not solve single-side/no-opposite-anchor by adding a new candidate identity
> system. If a future behavior edit is justified by real frame evidence, scope it
> to current-project extra learning state first, and document why it does not
> break the `ce65c9d/e1069df` search-center recovery reason.

## 2026-06-08 Evidence Capture Audit For Single-Side Proof

This pass is also analysis-only. No runtime code, tests, build, replay, or push
were performed.

The key question was whether the current live/analyze/replay logs can prove the
remaining single-side/no-opposite-anchor chain without adding another behavior
change.

### Existing Evidence Channels

| Channel | Current useful fields | Limitation for single-side proof |
| --- | --- | --- |
| `print_live()` single-line live output | seed coordinates, trace steps, `idrej`, L/pair state, frame mode, `mid.step`, `center`, `m0`, lookahead point, `guide`, loop/yaw/duty. | It only prints when `make_live_state_signature()` changes. The signature does not include `seed_state`, seed coordinates, `mid_position`, `width_base`, `guide_error`, yaw, or duty, so straight-line drift can be hidden if element/topology state is stable. |
| `print_detail()` analyze output | seed coordinates, `seed_state`, current `mid_position`, trace steps, `idrej`, corners, midline, loop output, element state. | Single-frame only; it does not show `mid_position` before vs after learning, and does not show trace x ranges, rpts/rptsc counts, begin id, or attach distance. |
| `write_report()` key/value file | `mid_position`, seed coordinates, trace steps, `idrej`, L/pair fields, midline start/lookahead, center, guide. | It lacks `seed_state`, `width_base`, trace x ranges, rpts/rptsc counts, begin id, attach distance, and publish-before-learning timing. |
| `print_replay_frame()` replay output | element/cross/ring/midline summary each replay frame. | Useful for cross/ring sequencing, but insufficient for the single-side ownership proof because it lacks search-center learning details and trace ownership geometry. |

### Strong Proof Needs More Than Current Live State Changes

To prove the remaining issue on real frames, the evidence must identify both
control risk and learning risk:

| Proof target | Minimum required evidence |
| --- | --- |
| Single-side frame exists | `seed_state`, left/right seed coordinates, left/right trace steps. |
| No opposite anchor exists | opposite seed invalid and opposite trace step zero, plus `trace_identity_reject` not set because no comparison exists. |
| The surviving side may be physically wrong | raw trace x range or same-row relation against stable start columns; current logs only have trace step counts, not trace ranges. |
| Candidate was selected | selected `track_type`, `rpts0s/rpts1s` and `rptsc0/rptsc1` counts, final `mid.step`. |
| `build_rptsn()` forcibly attached a distant candidate | selected `begin_id` and distance from candidate begin point to `control_ref` before overwrite. Current logs do not expose this. |
| Current-frame control risk | published `guide_error`, midline start/lookahead point, target yaw/duty. Current live output has these, but changed-only gating can suppress stable-state oscillations. |
| Cross-frame learning risk | `mid_position` and `width_base` before and after `update_search_center()`, plus whether final publication later succeeded. Current logs expose only after-state `mid_position` in detail/report and no `width_base`. |

### Current Decision

Do not treat current changed-only live logs as sufficient proof of the
single-side/no-opposite-anchor root cause. They are enough for coarse state
transitions, cross/ring sequencing, and obvious guide/yaw jumps when a printed
state transition happens; they are not enough to prove quiet straight-line
drift.

If future code is allowed, the most reference-aligned first step is diagnostic
only: expose the missing proof fields without changing tracking behavior. The
diagnostic must still obey the no-fallback rule: no old midline, no guessed
opposite side, no smoothing/holding, no behavior gate hidden behind logging.

### Minimal Diagnostic-Only Design If Code Is Later Allowed

This is not an implementation approval. It records the smallest owner-correct
shape for a future diagnostic patch, so the next edit does not accidentally
become a behavior change.

| Owner | Add only factual fields | Why this owner |
| --- | --- | --- |
| `track_result_t` | `seed_state_find`, `seed_state_trace`, `search_mid_before/after`, `width_base_before/after`, raw trace x ranges, `rpts0s/rpts1s` counts, `rptsc0/rptsc1` counts, selected midline begin id and attach distance. | `track_result_t` is already the per-frame tracking report surface and is reset every frame. These are facts about the current frame, not control decisions. |
| `tracking_process_frame()` | Record `search_mid_before/width_base_before` before `find_seeds()`, and `search_mid_after/width_base_after` immediately after `update_search_center()`. | This is the only owner that knows the exact learning timing. It avoids guessing from final state later. |
| `trace_edges()` | Record initial/final seed state and raw trace min/max x ranges using the existing trace range helper. | This proves whether a single-side frame really had no opposite anchor and whether the surviving trace crossed suspicious raw territory. |
| `build_frame_boundaries_and_candidates()` / crop stage | Record `rpts0s/rpts1s` and `rptsc0/rptsc1` counts before and after element crop if needed. | This separates "trace existed" from "candidate could be built/selected". |
| `build_rptsn()` | Prefer an optional debug output owned by `build_rptsn()` for `begin_id` and attach distance before `work[0]=control_ref`. | `build_rptsn()` owns begin selection and control-point overwrite; duplicating the nearest-point logic elsewhere risks drift. |
| `report.cpp` | Print/write these factual fields. Do not change tracking/control behavior. | Report code stays a read-only consumer. |

Rejected diagnostic shapes:

- Do not infer missing opposite geometry in logs.
- Do not add a behavior gate while adding the fields.
- Do not make live changed-state beeps depend on every raw numeric jitter by
  default; if live proof is needed later, use coarse single-side proof buckets or
  an explicit diagnostic mode.
- Do not move `update_search_center()` solely to make logging easier.

The diagnostic patch, if requested later, should have the fixed rationale table:

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 has no `mid_position/width_base` learning state and does not expose attach distance. | Current project has extra cross-frame search-center learning and current logs cannot prove quiet single-side drift. | Add factual per-frame diagnostic fields and report them; do not change tracking output, selected candidate, `guide_error`, `mid_position`, or control output. | Future behavior edits require real proof. Current changed-only logs can suppress stable-topology straight drift. | The diagnostic only records current-frame facts; it does not synthesize geometry, reuse old output, smooth, hold, or reject anything. |

## 2026-06-08 Real-Frame Decision Tree For The Remaining Risk

This section defines how to classify future real frames once sufficient
diagnostic fields exist. It is not a runtime algorithm.

### Step 0: Exclude Cases Already Covered Elsewhere

| If the frame shows... | Classification |
| --- | --- |
| Both sides are present and raw trace crosses opposite seed or same row. | Dual-side raw identity issue; covered by `52f0801` behavior. |
| Both IPM/work sides have enough paired overlap and `left_x >= right_x`. | Dual-side IPM order issue; covered by `724c7cb/d2ccaf0` behavior. |
| `cross.state == BEGIN` and strict double-L is absent. | Cross BEGIN stale issue; covered by `bf06e90` behavior. |
| Active ring entry from single-side L plus opposite straight. | Ring reference contract; not a bug by itself because RT1064 uses this shape. |

Only continue this decision tree for ordinary or non-farline frames where the
surviving evidence is single-side and there is no current opposite anchor.

### Step 1: Prove Single-Side / No-Opposite-Anchor

Required facts:

1. Exactly one side remains after trace filtering.
2. The other side has no valid seed or no valid trace.
3. `trace_identity_reject` is not set because there was no opposite comparison,
   not because the frame was proven good.
4. `work_pair_order_ok()` had insufficient paired points, or only one side
   existed, so IPM order could not be judged.

If any of these are missing, classification is **insufficient evidence**.

### Step 2: Split Control Risk From Learning Risk

| Evidence | Meaning |
| --- | --- |
| Selected side has enough candidate points, `build_rptsn()` publishes, and `guide_error` jumps while midline start/lookahead also jump. | Current-frame visual control risk. The wrong single-side candidate may be controlling this frame. |
| `update_search_center()` changes `mid_position`/`width_base` before final publication fails or before a suspicious candidate is proven. | Cross-frame learning risk. The next frame can be taught by a weak or wrong single-side frame. |
| `guide_error` remains stable but `target_yaw`/duty oscillates. | Control-loop risk, not a visual identity proof. Inspect `outer_kp/kd`, IMU yaw feedback, wheel geometry, and duty saturation separately. |
| `mid_position` drifts across frames while topology fields remain unchanged and live logs are suppressed. | Evidence capture gap. Current changed-only live logs are not enough; use diagnostic fields or explicit proof mode. |

### Step 3: Use Attach Distance Only As A Symptom, Not A Gate

Attach distance can support a diagnosis if:

- the selected candidate's nearest point to `control_ref` is far before
  `build_rptsn()` overwrites it;
- the resulting `guide_error` or `mid_position` change matches the observed
  straight-line crawl/twist;
- the same frame has no opposite anchor that could independently verify side
  identity.

Attach distance alone cannot justify a runtime reject, because RT1064 also
normalizes the nearest candidate point to `cx/cy` without such a gate.

### Step 4: Allowed Conclusions

| Classification | Allowed next action |
| --- | --- |
| Proven current-frame visual control risk | Consider a behavior change only if it can be tied to current-frame evidence, not old geometry. Still do not synthesize the missing opposite side. |
| Proven cross-frame learning risk | Prefer a narrow guard around single-side `mid_position/width_base` learning, not a ban on single-side tracking. |
| Proven control-loop risk | Work in `front_car_control_calib` or control config, not tracking geometry, unless visual `guide_error` is also unstable. |
| Insufficient evidence | Add diagnostics or capture better logs. Do not change behavior. |

This tree is deliberately stricter than "looks wrong in the image" because the
previous regression came from modifying contracts before proving which layer
owned the symptom.

## 2026-06-08 Information Boundary Of Single-Side Identity

This section records the algorithmic limit behind the remaining risk.

When only one current-frame boundary survives, the frame contains a single
polyline `P` plus its declared slot (`left` or `right`). Without an opposite
seed, opposite trace, paired work points, or another independent lane marker,
the image evidence cannot uniquely prove whether `P` is:

1. the physical left boundary correctly stored in the left slot;
2. the physical right boundary incorrectly stored in the left slot;
3. a legal curve/ring/cross-approach boundary whose x range crosses a simple
   center/start-column heuristic;
4. a noise/black-mark trace that happens to pass step and vertical-gain checks.

The dual-side checks solve a different problem because they have relational
evidence:

| Evidence type | Why it can prove identity failure |
| --- | --- |
| Left trace passes right seed / right trace passes left seed | A current-frame opposite seed exists, so a side can be compared against an independent anchor. |
| Left/right traces cross on the same row | Both traces exist, so same-row ownership can be compared. |
| IPM/work paired points have `left_x >= right_x` | Both work sides have enough paired overlap, so ordering is directly testable. |

Single-side/no-opposite-anchor lacks all three relational witnesses. Any
runtime rule that rejects or rewrites it must therefore introduce an extra
assumption.

### Possible Extra Assumptions And Their Cost

| Assumption | What it tries to infer | Cost / risk |
| --- | --- | --- |
| "A left trace must stay left of center/opposite start column." | Raw x range can prove side identity. | Can reject legal curves, ring approach, cross approach, and shifted camera/track geometry. Not RT1064 ordinary contract. |
| "Candidate must attach near `control_ref` within a fixed distance." | A distant candidate is wrong. | RT1064 also normalizes nearest candidate to `cx/cy` without such a gate. Needs sample proof and a hardware-specific threshold. |
| "Single-side frames cannot update `mid_position` until final midline publishes." | Learning should follow published control validity. | More reference-fitted because RT1064 has no learning state, but can weaken `ce65c9d/e1069df` recovery if valid traces have short final midlines. |
| "Use previous frame side/center as a prior." | Temporal continuity can resolve ownership. | Risks stale-state fallback. Must not hold old midline/guide/error or hide missing geometry. |
| "Synthesize the missing opposite boundary from width." | Recreate relational evidence. | Explicitly rejected fallback: guessed geometry can make wrong frames look valid. |

### Consequence For Future Fixes

There is no zero-assumption current-frame fix for single-side identity. The
acceptable future direction is not to pretend otherwise, but to choose the
least dangerous assumption only after real-frame evidence proves which failure
mode exists.

Current ranking remains:

1. Prefer diagnostics.
2. If proven, protect only the project-specific learning state
   `mid_position/width_base`.
3. Avoid hard rejecting single-side current-frame control unless a real frame
   set proves legal curves/elements are not harmed.
4. Never synthesize missing geometry or hold stale control output.

## 2026-06-08 Current Issue Ledger Against HEAD

This is a static source audit of current `HEAD`. It is not a runtime replay or
test result.

| Issue | Current status | Source evidence | Remaining gap |
| --- | --- | --- | --- |
| Cross BEGIN stayed alive after strict double-L disappeared. | Solved in current source. | `cross_begin()` reads `left.l_pair_ok/right.l_pair_ok`; if both are not present it calls `cross_leave()` and returns. | Real camera regression still needs future replay/log confirmation if symptoms return. |
| Frame newly entering cross/ring should not use new element mode in the same frame. | Solved in current source. | `tracking_process_frame()` snapshots `action.cross_state0` and `action.ring_kind0` before `element_process()`, and `classify_frame_mode()` uses frame-start action fields. | No runtime replay in this pass. |
| Unity `CD.cpp` ring chain accidentally treated as active reference. | Solved for active code. | Active `ring_process()` enters from RT1064-style single-side `l_ok` plus opposite `boundary_is_straight()`; grep only finds Unity terms in docs/reference and explanatory docs, not active `code/`. | If ring false-triggers now, inspect `l_ok` and `boundary_is_straight()` quality, not Unity pending logic. |
| Ring single-side entrance suspected as weak. | Reference-aligned, not automatically a bug. | RT1064 ring uses single-side L plus opposite straight; current active code follows that shape. | Needs real ring frames to judge whether thresholds/straight detection are too permissive on this hardware. |
| Raw left/right trace crosses to opposite side in dual-side frames. | Solved for frames with opposite evidence. | `trace_identity_reject_bits()` rejects left passing right seed, right passing left seed, or same-row trace crossing. | Does not cover single-side/no-opposite-anchor by design. |
| IPM/work-point left/right order reverses in dual-side frames. | Solved for paired overlap frames. | `work_pair_order_ok()` rejects only when enough paired work points exist and `left_x >= right_x`; `d2ccaf0` delays `update_search_center()` until after this gate. | Does not cover single-side/no-opposite-anchor. |
| Cross farline old L reuse could reuse stale index blindly. | Solved for source-guarded reuse. | `build_cross_farline()` keeps `old_l_source`; it only reuses an old L if a prior source exists and the index is usable for the current farline. | Real CROSS_IN sequence still needs camera replay to validate the intended continuity. |
| Straight line crawl to opposite side with only one surviving side. | Open. | Single-side path still has no current opposite anchor; raw/IPM dual-side gates cannot prove identity. | Requires diagnostics or real frames with proof fields before behavior change. |
| Straight-line twisting. | Split/unknown. | Visual path publishes `guide_error`; control path consumes `guide_error -> target_yaw -> yaw_cmd`. | Need logs that show whether `guide_error` jumps with midline or remains stable while yaw/duty oscillates. |
| Current changed-only live logs prove quiet straight drift. | Open evidence gap. | `make_live_state_signature()` excludes `seed_state`, seed coords, `mid_position`, `width_base`, `guide_error`, yaw, and duty; `print_live()` returns if signature is unchanged. | Need diagnostic fields or explicit proof mode before claiming root cause from quiet live drift. |

Current bottom line:

- The known dual-side identity and cross/ring reference-mixing bugs are closed
  in source.
- The remaining algorithmic risk is single-side/no-opposite-anchor plus the
  extra project-specific learning state.
- The remaining evidence risk is that current live logs can suppress straight
  drift when topology does not change.

## 2026-06-08 Future Diagnostic-Only Patch Blueprint

This is a blueprint only. Do not implement it unless the user explicitly allows
a diagnostic code change.

### Field Naming Contract

Use names that expose facts and timing, not conclusions:

| Field group | Proposed fields | Invalid value |
| --- | --- | --- |
| Seed state timing | `seed_state_found`, `seed_state_traced` | `0` is meaningful; no invalid value needed. |
| Search-center learning | `search_mid_before`, `search_mid_after`, `width_base_before`, `width_base_after` | `-1` for not recorded. |
| Raw trace range | `left_trace_min_x`, `left_trace_max_x`, `right_trace_min_x`, `right_trace_max_x` | `-1` for no trace. |
| Work/candidate counts | `rpts0s_num_dbg`, `rpts1s_num_dbg`, `rptsc0_num_dbg`, `rptsc1_num_dbg` | `-1` for not built; count `0` remains meaningful. |
| Selected midline attach | `mid_begin_id`, `mid_attach_dist`, `mid_input_num`, `mid_force_begin_id0` | `-1` for no selected build. |

Notes:

- Keep `rpts0s/rpts1s/rptsc0/rptsc1` in the names so they remain easy to
  compare with RT1064 and current globals.
- Do not call these fields `bad_*`, `wrong_*`, `reject_*`, or `ok_*`; they are
  observations, not decisions.
- Set invalid fields to `-1` in `reset_frame_tracking_state()` after the
  existing `memset`, because zero is a valid count, x coordinate, and distance.

### Minimal File Scope If Implemented

| File | Purpose |
| --- | --- |
| `code/types.hpp` | Add factual fields to `track_result_t`; optionally add a tiny `rptsn_debug_t` if `build_rptsn()` owns begin/attach reporting. |
| `code/tracking/imgproc.hpp/.cpp` | Optional `rptsn_debug_t *dbg` parameter for `build_rptsn()` so begin id and pre-overwrite attach distance are reported by the owner of that logic. Existing callers can use the default/null path. |
| `code/tracking/mainline.cpp` | Fill seed timing, search-center before/after, raw trace ranges, rpts/rptsc counts, and selected midline debug. Do not change decisions or call order. |
| `code/app/report.cpp` | Print/write the new facts. Do not change `track_line_found()`, `guide_error`, control output, or live state behavior by default. |

### Stage Split

| Stage | Allowed change | Not allowed |
| --- | --- | --- |
| A | Add fields to detail/report and, if safe, replay summaries. | No behavior change; no live beep signature expansion. |
| B | If real live proof is needed, add explicit diagnostic mode or coarse buckets for single-side proof. | Do not make default live output beep on every numeric jitter. |
| C | Only after real-frame proof, consider a narrow learning-state guard. | Do not combine diagnostics and behavior gate in the same first patch. |

### Expected Review Question

Before committing any diagnostic patch, the reviewer should be able to answer:

1. Does this patch change any tracking/control branch condition? It must not.
2. Does it change `mid_position`, `width_base`, `guide_error`, selected
   `track_type`, or duty output? It must not.
3. Can every new field be traced to a single owner and a current-frame fact?
   It must.
4. Does the final rationale table say there is no direct RT1064 diagnostic
   equivalent for current-project learning state? It must.

## 2026-06-08 No-Code Evidence Collection Runbook

This runbook uses current source only. It does not claim to solve the remaining
issue; it states what can and cannot be collected before a diagnostic patch.

### Current Entrypoints

| Entrypoint | What current source does | Useful for | Not enough for |
| --- | --- | --- | --- |
| `--analyze image.png --report path` | Runs one image through tracking/control, prints detail, writes key/value report and IPM preview. | Single-frame seed, trace step count, L/pair, midline, guide, report fields. | Cross-frame `mid_position/width_base` learning before/after, quiet drift, real control feedback. |
| `--replay image.png count --report path` | Repeats the same image for `count` frames and prints replay summaries. | State-machine continuity with a fixed image, especially cross/ring counters. | Real video changes; it cannot prove natural straight drift because input is constant. |
| Live main binary | Captures camera frames, runs tracking, reads feedback, computes duty, sends assistant, then calls `print_live()`. | Real vehicle sequence and control feedback at the publish point. | Quiet drift if `make_live_state_signature()` does not change. |
| `key_supervisor` start path | Starts mainline with assistant enabled, display disabled, process fps 120, drive enabled, output redirected to the mainline log. | Practical on-car start path. | It does not add extra proof fields. |

### Beep / Changed-State Behavior

Current live beep behavior is:

1. `print_live()` calls `live_beep_tick()`.
2. It builds `make_live_state_signature()`.
3. If the signature is unchanged, it returns and prints nothing.
4. If changed and `frame_id != 0`, it calls `live_beep_once()`.
5. Beep path defaults to `/dev/zf_gpio_beep`; `FRONT_CAR_STATE_BEEP=0`
   disables it; `FRONT_CAR_BEEP_PATH` overrides the device path.

This is good for "state changed" awareness. It is not proof of quiet straight
drift because the signature intentionally excludes many numeric fields.

### What Can Be Collected Now Without Code Changes

| Question | Current evidence source |
| --- | --- |
| Did cross/ring/zebra/topology state change? | Live changed-state line and beep. |
| Did a printed frame publish a line and guide? | Live `line/rej/track/mid/center/m0/ml/guide` fields. |
| Did the printed frame have dual L / single L evidence? | Live `l=... pair=... ps=... pw=...` fields. |
| Did the printed frame have raw identity reject bits? | Live `idrej` field. |
| Did target yaw/duty react to a printed guide? | Live `yaw` and `duty` fields. |
| What does a single still image produce? | `--analyze` detail output and report file. |

### What Cannot Be Proven Now Without Diagnostics

| Missing proof | Why current source cannot prove it |
| --- | --- |
| `mid_position` before vs after `update_search_center()` | Current logs expose only final `mid_position` in detail/report, not exact learning timing. |
| `width_base` learning behavior | Current logs do not print/write `width_base`. |
| Single-side trace crossed suspicious raw x range | Current logs print trace step counts, not trace min/max x. |
| Candidate count before/after selection/crop | Current logs do not expose `rpts0s/rpts1s/rptsc0/rptsc1` counts. |
| `build_rptsn()` attached a far candidate | Current logs do not expose begin id or pre-overwrite attach distance. |
| Quiet straight-line drift with stable topology | Current live changed-state signature can suppress those frames. |

### Practical Use Before Diagnostics Exist

Use current logs only to classify coarse cases:

- If live prints show guide/midline jumps at the same time as topology changes,
  the printed frame is useful.
- If the car visibly drifts/twists but live prints stay silent, classify it as
  **evidence gap**, not as proof of a specific algorithm bug.
- If `guide` is stable in printed frames but yaw/duty changes, investigate
  control path separately.
- If the same symptoms require quiet straight frames, request/implement the
  diagnostic-only patch first.

## 2026-06-08 Renewed Algorithm Audit After Rejecting Dual Hypothesis

User correction: the ordinary reference-shaped flow is already "if it is the
left boundary, run `track_leftline()`; if it is the right boundary, run
`track_rightline()`". Adding a same-trace left/right dual hypothesis is not
needed and is not reference-backed.

### Why Dual Hypothesis Was Rejected

| Point | Conclusion |
| --- | --- |
| Why it was considered | A single-side/no-opposite-anchor frame cannot prove boundary identity from current-frame relational evidence alone. Trying both identities would expose that ambiguity. |
| Why it is wrong for this task | RT1064 ordinary tracking does not try both identities for the same trace. It preserves left/right ownership from separate start points and arrays, then selects one candidate. |
| Hidden extra assumption | Any later choice between the two hypotheses would need a distance, width, temporal, or continuity rule. That becomes a new heuristic gate rather than a reference contract. |
| Final decision | Do not implement dual hypothesis and do not use it as the plan. Keep it only as a rejected route. |

### Current Reference-Aligned Ordinary Flow

| Stage | Current owner | Reference fit | Remaining risk |
| --- | --- | --- | --- |
| Seed ownership | `find_seeds()` | Central seed owner; can return one or both sides. | Single-side seed identity is not self-proving. Mixed-row dual seed can still write a center even when no same-row pair exists. |
| Raw trace | `trace_edges()` + `trace_identity_reject_bits()` | Left seed traces left-side, right seed traces right-side; proven raw crossing is rejected. | No opposite seed/trace means no raw relational reject condition. |
| Work/IPM order | `build_frame_boundaries_and_candidates()` + `work_pair_order_ok()` | Paired current-frame work points can prove left/right reversal and fail closed. | If either side is short or pairing is insufficient, the gate intentionally cannot decide. |
| Candidate generation | `track_leftline(rpts0s)` and `track_rightline(rpts1s)` | Matches RT1064 single-side candidate shape. | This assumes upstream left/right ownership is already correct. |
| Side selection | `pick_track_type()` | Matches RT1064 point-count single-side selection and `track_type_keep` style. | It selects a side; it does not prove side identity. |
| Learning state | `update_search_center()` | Current-project extension, needed by Front_Car history; RT1064 has no direct equivalent. | Current code still writes before final midline publication, so an unpublishable single-side frame can teach next-frame search center. |

### Strongest Remaining Choke Point

`d2ccaf0` correctly moved `update_search_center()` after the IPM identity gate,
so a frame already proven reversed by `work_pair_order_ok()` cannot teach the
next frame.

That is still narrower than the full learning-state contract. Current
`tracking_process_frame()` still calls `update_search_center()` before
`build_selected_midline()` and `publish_track_result()`. Therefore:

1. A single-side seed/trace can survive because no opposite anchor exists.
2. `work_pair_order_ok()` can allow it because it has insufficient paired
   evidence, not because identity is proven.
3. `update_search_center()` can write `mid_position` using
   `seed +/- width_base / 2`.
4. Only after that does the code attempt selected midline construction and
   publication.
5. If publication fails or produces unstable guide, the next-frame search
   center may already have moved.

This is not a stale-midline fallback; it is a cross-frame learning-order risk.
It also explains why a quiet straight drift can accumulate without a dramatic
state change in live logs.

### Reference-Fitted Candidate If Behavior Change Is Later Allowed

Do not ban single-side tracking. The closer reference-shaped candidate is:

| 参考版怎么样 | 当前代码差异 | 候选修改 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 has no cross-frame `mid_position`; each frame rebuilds starts and only a valid selected centerline reaches the steering update branch. | Current project needs `mid_position/width_base`, but writes it before final selected midline publication. | Move ordinary `update_search_center()` after successful `publish_track_result()` for non-`CROSS_STATE_IN` ordinary frames, or equivalently only commit the learned center after final midline success. | This protects the current-project learning state using a reference principle: failed/unpublished current-frame geometry should not teach the next frame. | The edit would not synthesize a line, reuse old midline, guess the opposite side, smooth guide_error, hold duty, or add width/drift thresholds. It only delays learning until the current frame has a valid selected midline. |

Risk: this candidate is broader than `d2ccaf0`. It may reduce recovery in frames
where trace is good but final midline is too short. Before code, audit whether
such frames were intentionally allowed by `ce65c9d/e1069df`, and prefer
diagnostic proof if real frames are available.

### Current Best Explanation Of The Two User Symptoms

| Symptom | More likely owner | Reasoning | What would disprove it |
| --- | --- | --- | --- |
| Left/green line crawls to the opposite side on straight | Visual learning and side ownership, especially single-side/no-opposite-anchor plus early `mid_position` learning. | Dual-side raw/IPM reversal is now guarded, but single-side frames still can teach the search center and later pull seed columns. | Logs showing `mid_position/width_base` stable and `guide_error` stable while the car still physically drifts. |
| Twisting strongly on straight | First classify by `guide_error`; only then control. | Current control consumes `guide_error -> target_yaw -> yaw_cmd`; it does not re-validate line identity. If guide jumps, control is reacting to visual input. If guide is stable, control parameters/IMU/wheel geometry become primary. | A real sequence with stable guide/midline but oscillating yaw/duty points to the differential control path. |

### Non-Negotiable Next Rules

- Do not revive dual hypothesis.
- Do not add a single-side hard reject without real-frame proof.
- Do not use attach distance, width, drift, or temporal continuity as a hidden
  behavior gate.
- If code is allowed later, first choice is diagnostic-only evidence; if a
  behavior fix is justified, protect learning-state timing before changing
  side-selection semantics.

## 2026-06-08 Refined Learning-State Candidate Audit

The previous section's "move ordinary `update_search_center()` after
`publish_track_result()`" candidate is directionally useful but incomplete if
implemented literally. A direct move would change the element timing contract
because `update_search_center()` currently reads `rt->ring.kind` and
`rt->cross.state` when deciding whether `width_base` may low-pass update.

### Why A Literal Move Is Too Crude

Current order in `tracking_process_frame()`:

1. Snapshot frame-start element state into `action.cross_state0` and
   `action.ring_kind0`.
2. Seed and trace.
3. Build boundaries and candidates.
4. If IPM order is not rejected, call `update_search_center()`.
5. Snapshot ring frame-start action, then run `element_process()`.
6. Build/publish the selected midline.

Therefore `update_search_center()` currently sees the frame-start element
state, not a newly entered cross/ring state. In particular, when a frame starts
ordinary and `element_process()` enters cross or ring later in the same frame,
`width_base` is still treated as ordinary-frame learning.

If the function is simply moved after `element_process()` and
`publish_track_result()`, the same frame would see `rt->cross.state` or
`rt->ring.kind` after mutation. That would silently change whether `width_base`
is updated on newly entered element frames.

### Minimal Behavior Shape If Code Is Later Allowed

Do not change CROSS_IN/ring-internal learning in the first behavior patch. The
targeted straight-road fix should only defer ordinary frame-start learning:

| Frame-start state | Current behavior | Refined candidate |
| --- | --- | --- |
| `cross_state0 == NONE` and `ring_kind0 == NONE` | Learn search center after trace + IPM order gate, before final selected midline publication. | Defer learning until the selected midline geometry reaches the ordinary minimum. Use the frame-start ordinary flag for the `width_base` low-pass decision, not mutated post-element state. |
| Already in cross or ring at frame start | Learn at the current point after trace + IPM order gate, before element evolution/publication. | Leave unchanged in the first patch unless real element-frame evidence proves this owner is also wrong. |
| CROSS_IN farline path with no valid near seed/trace | No ordinary search-center update. | Leave unchanged. |
| IPM side-cross rejected frame | No search-center update after `d2ccaf0`. | Leave unchanged. |

### Implementation Sketch, Not Approved Code

If behavior code is later explicitly allowed, the simple shape should be:

1. Compute `ordinary_frame0 = action.cross_state0 == CROSS_STATE_NONE &&
   action.ring_kind0 == RING_KIND_NONE`.
2. Let frames that are already inside cross/ring keep the current
   `update_search_center()` timing.
3. For `ordinary_frame0`, skip the early call and call the learning function
   only after `build_selected_midline()` returns at least the ordinary minimum.
4. Do not let the post-`element_process()` mutated `rt->cross.state` or
   `rt->ring.kind` decide `width_base`; pass/use the frame-start ordinary flag
   for that specific decision.

This keeps the code direct and avoids a new fallback. It also preserves the
history-backed reason for `width_base`: dynamic center follows real ordinary
frames, while element frames do not recalibrate road width.

### Updated Rationale Table

Superseded note: this 2026-06-08 table captured the earlier geometry-only
learning candidate. The active 2026-06-09 contract is stricter: ordinary frames
learn only after `publish_track_result()` succeeds.

| 参考版怎么样 | 当前代码差异 | 候选修改 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 has no dynamic cross-frame seed center; ordinary start ownership is rebuilt from fixed start columns, and a selected valid midline is normalized before steering math. | Current project has `mid_position/width_base` for recovery, but ordinary frames can learn before selected midline geometry is built. `width_base` also depends on whether the frame is ordinary. | For frame-start ordinary frames only, commit `mid_position/width_base` after selected midline geometry reaches the ordinary minimum; preserve frame-start ordinary state for the `width_base` low-pass decision. | This extends the `e1069df` and `d2ccaf0` principle from "trace/IPM verified before learning" to "selected current midline geometry verified before ordinary learning", without perturbing already-in-element behavior. | The candidate does not ban single-side tracking, add a width/drift gate, synthesize an opposite line, reuse stale midline, or hold old guide/duty. It only delays cross-frame learning until the current ordinary frame has a usable selected midline geometry. |

Superseded open risk: this section previously worried that publish-success-only
learning might reduce recovery on short-lookahead frames. The 2026-06-09 field
evidence changed the balance: short/backward ordinary lookahead is now a known
bad-frame class, so it must not update the next seed center.

## 2026-06-08 Superseded Learning Gate Refinement

This section is retained as history only. It argued for separating geometry
success from control publish before the 2026-06-09 field evidence showed that
short/backward ordinary lookahead can also poison the next seed-search center.
The active contract is now stricter: ordinary learning waits for
`publish_track_result()` success.

The older analysis split `publish_track_result()` into two contracts:

1. Geometry minimum: `mid_ok >= k_min_border_step` for ordinary frames.
2. Control safety: `midline_has_lookahead(mid, LOOKAHEAD_DIST)`.

RT1064's ordinary midline branch is closer to the geometry minimum: after a
valid `begin_id`, it requires enough points after the begin point, normalizes
the centerline, and clips the aim index into the available centerline length.
It does not have a separate "must cover 2/3 of lookahead distance" learning
contract.

### Gate Comparison

| Possible learning gate | What it proves | Reference fit | Risk |
| --- | --- | --- | --- |
| Seed found | Some candidate start point exists. | Too weak for current project; `e1069df` already rejected this timing. | Seed noise can poison next frame before trace rejects it. |
| Trace survived + IPM order not rejected | Current `d2ccaf0` state: trace and available identity checks passed. | Better than seed-only and preserves current recovery behavior. | Still learns before proving the selected candidate can attach to the control reference. |
| Selected midline geometry success (`build_selected_midline()` returns at least ordinary minimum) | The chosen side produced a current-frame control-coordinate midline from the selected candidate. | Closest split: acquisition learning follows a usable current geometry, while control safety remains separate. | A short but plausible midline can still learn even when lookahead safety blocks guide output. |
| Full `publish_track_result()` success | Midline is long enough for current control output and guide publication. | Safer for control, but stricter than RT1064's midline availability branch. | May starve search-center recovery on short but valid current geometry, undoing part of `ce65c9d`'s reason. |

### Updated Best Candidate

If a behavior patch is later allowed and real diagnostics do not contradict
this reasoning, the best first behavior candidate should be:

1. For frame-start ordinary frames only, skip the early
   `update_search_center()`.
2. Build the selected midline.
3. Run `publish_track_result()` with the existing gates.
4. If publish succeeds, commit search-center learning using the frame-start
   ordinary flag for `width_base`.

This protects against both older learning-order pollution and the newer
2026-06-09 risk: ordinary frames rejected by the complete forward-lookahead
publish gate must not teach the next seed-search center.

### Updated Rationale Table

| 参考版怎么样 | 当前代码差异 | 候选修改 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 normalizes and consumes a centerline once the selected candidate has a valid begin and enough remaining points; it has no dynamic `mid_position/width_base`. | Current project has a stricter complete-forward-lookahead publish gate plus a separate cross-frame seed learning state. A publish-failed ordinary frame could otherwise still teach the next frame. | For frame-start ordinary frames, learn only after `publish_track_result()` succeeds. | This makes the project-local acquisition prior fail closed when current-frame geometry is too short or points backward. | The failed frame remains failed; no old geometry, guide, duty, opposite side, or identity guess is reused. |

### Remaining Need For Diagnostics

This refined gate still cannot prove single-side identity when no opposite
anchor exists. It only ensures a single-side frame cannot teach the next frame
until the selected side has produced an actual current midline. Real diagnostics
are still needed to decide whether a further single-side identity rule is ever
justified.

## 2026-06-08 Exact Patch Contract If Behavior Is Approved

This section is not an approval to edit runtime code. It records the smallest
code shape that currently matches the audit, so a future patch does not drift
into a fallback or broad rewrite.

### Read-Only Impact Check

Current source search shows:

- `find_seeds()` is the only tracking owner that consumes `rt->mid_position`
  for seed search.
- `element_process()`, `cross_process()`, and `ring_process()` do not read
  `mid_position` for their current-frame decisions.
- `ring.cpp` uses stable `MID_X` for degenerate ring opposite-side geometry.
- `zebra.cpp` uses stable `MID_X` for the Otsu split instead of dynamic
  `mid_position`.

Therefore deferring ordinary-frame search-center learning until after selected
midline construction should not change same-frame element detection inputs.
The important preserved contract is `width_base`: its "ordinary frame" decision
must use frame-start state, not post-`element_process()` mutated state.

### Minimal Code Shape

Keep naming short and direct:

| Name | Meaning |
| --- | --- |
| `ordinary_frame0` | Frame started outside cross and ring. Suffix `0` follows existing `cross_state0` frame-start naming. |
| `allow_width_base` | This update is allowed to low-pass `width_base`; it is true only for frame-start ordinary learning. |

The function shape should be:

```cpp
void update_search_center(runtime_t *rt, int allow_width_base)
{
    ...
    if((rt->seed_state & 3) == 3)
    {
        mid = (rt->seeds.left.x + rt->seeds.right.x) / 2;
        if(allow_width_base && seed_pair_accepted(&rt->seeds, rt->seed_state))
        {
            ...
        }
    }
    ...
}
```

The frame flow should be:

```cpp
const int ordinary_frame0 =
    action.cross_state0 == CROSS_STATE_NONE &&
    action.ring_kind0 == RING_KIND_NONE;

...
if(!ordinary_frame0)
{
    update_search_center(rt, 0);
}
snapshot_ring_frame_start_action(rt, &action);
element_process(rt);
action.base_candidates_ready = 1;
...
const int mid_ok = build_selected_midline(rt, &mode, ref);
if(!publish_track_result(rt, &mode, mid_ok, ref))
{
    return 0;
}
if(ordinary_frame0)
{
    update_search_center(rt, 1);
}
```

### What This Must Not Change

| Area | Required preservation |
| --- | --- |
| Single-side tracking | Still allowed. No hard reject is added. |
| IPM side-cross reject | `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` still returns before any learning. |
| Frames already in cross/ring at frame start | Keep current learning timing for the first patch. |
| Newly entered cross/ring frame | Current-frame selected midline still uses frame-start ordinary action. `width_base` learning, if allowed, uses `ordinary_frame0`, not mutated element state. |
| Control publish | `publish_track_result()` and `midline_has_lookahead()` remain unchanged. A short lookahead frame may learn acquisition state but still withhold control output. |
| Diagnostics/logs | No new behavior gate should be hidden behind reporting fields. |

### Why This Is Still Not A Full Fix

This patch shape only prevents learning before the selected side can create a
usable current midline. It still does not prove that a single-side frame has the
correct left/right identity when no opposite anchor exists. That unsolved part
must remain a diagnostic/sample-backed question, not a guessed rule.

## 2026-06-09 Element Learning Gate Supersedes First-Patch Boundary

This section supersedes the earlier "keep already-in-cross/ring learning
timing" first-patch boundary for the accepted nearline path only. Historical
sections above remain as audit trail; do not use their early element-learning
snippet as the current contract.

| Frame class | Current active contract |
| --- | --- |
| Frame-start ordinary, publish succeeds | `update_search_center(rt, 1)` after `publish_track_result()` succeeds. |
| Frame-start ordinary, publish fails | No search-center learning. |
| Frame-start cross/ring, accepted nearline seed/trace/IPM branch reached | Set `defer_element_search_center_update=1`; after successful `publish_track_result()`, call `update_search_center(rt, 0)`. |
| Frame-start cross/ring, publish fails | No search-center learning. |
| CROSS_IN farline-only path with no accepted nearline branch | No newly added search-center learning. |
| IPM side-cross rejected nearline path, including CROSS_IN farline continuation | No search-center learning before or after farline publication. |

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 has no dynamic search-center state. Ring/cross may choose `track_type`, crop candidates, or use farline, but final centerline control only happens when the selected candidate can produce enough `rptsn`; otherwise `rptsn_num=0` and steering is not updated. | Current project has `mid_position` as a cross-frame acquisition prior. The first patch preserved early learning for already-in-cross/ring frames, so a later `publish_track_result()` failure could still teach the next seed search center. | Move only the already-existing accepted-nearline element learning to after successful `publish_track_result()`: set a deferred flag at the old call site and call `update_search_center(rt, 0)` after publish succeeds. | Unpublished element geometry should neither drive the current frame nor teach the next frame. Successful element frames may still move the search center, but must not update `width_base`. | No old midline, old boundary, old guide, or duty is reused. No opposite line is synthesized. No single-side hard reject, width/drift/attach-distance gate, or ring/cross state-machine change is added. IPM-rejected and farline-only paths do not gain new learning. |

Invariants:

- The deferred flag must be set only at the old early-learning site after
  seed/trace and IPM order have been accepted.
- Do not call `update_search_center()` for CROSS_IN farline-only frames that
  never reached the accepted nearline branch.
- Do not call `update_search_center()` after
  `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS`; this preserves `d2ccaf0`.
- `allow_width_base` remains true only for frame-start ordinary publication.
- `publish_track_result()` and `midline_has_forward_lookahead()` remain the
  publication gates; do not weaken them for learning.

## 2026-06-08 Single-Side Identity Observability Boundary

This section records the algorithmic boundary behind the user's rejection of
fallback-style rules. The issue is not that the current code forgot one simple
condition; the issue is that some frames do not contain enough relational
evidence to prove side identity.

### What Current Code Can Prove

| Evidence owner | Current proof | Required relational evidence |
| --- | --- | --- |
| `trace_identity_reject_bits()` vs opposite seed | A left trace passing the current right seed, or a right trace passing the current left seed, is identity-bad. | The opposite seed must exist. |
| `traces_cross_on_same_row()` | Both raw traces existing on the same row with `left_x >= right_x` is identity-bad. | Both traces must exist with overlapping rows. |
| `work_pair_order_ok()` | Paired IPM/work points with `left_x >= right_x` are identity-bad. | Both sides must have enough resampled work points and enough y-neighbor pairs. |
| `build_selected_midline()` | The selected side can generate a current-frame midline geometry. | A selected candidate exists and can attach to the control reference. |

These are all current-frame facts. They reject when the current frame proves a
bad relation. They do not guess the missing opposite side.

### What A Single-Side Frame Cannot Prove

For a frame with only one surviving side:

1. There is no opposite seed, so "passed opposite seed" is undefined.
2. There is no opposite trace, so same-row crossing is undefined.
3. There are not enough paired work points, so IPM left/right order is
   unknowable.
4. The selected side can still generate a plausible centerline by normal
   offset, because RT1064 and current code both allow single-side tracking.

Therefore the frame can prove "this one side produced usable geometry", but it
cannot prove "this side is truly the left/right lane boundary" unless another
assumption is introduced.

### Assumptions That Would Be New Behavior

| Proposed rule family | Hidden assumption | Why it is not reference-proof by itself |
| --- | --- | --- |
| Center-column / opposite-start-column gate | A true left boundary must never cross a chosen center/opposite start x, or a true right boundary must never cross the opposite start x. | Curves, ring approaches, camera/IPM shifts, and dynamic `mid_position` can make this false without an actual identity swap. |
| Width/drift threshold | Road width or center drift should remain within a chosen bound. | RT1064 does not use a generic ordinary width/drift reject for single-side frames; thresholds would be hardware/sample-derived. |
| Temporal continuity gate | The previous side/center is trustworthy enough to reject current geometry. | This risks becoming stale-state fallback if the previous frame is not itself current-evidence verified. |
| Attach-distance gate | A valid candidate should attach near the control reference. | Useful diagnostic, but it still needs a threshold and does not identify left vs right without additional context. |
| Dual hypothesis | Try both identities and choose the "better" one. | The final chooser must use one of the assumptions above, so the ambiguity is only moved, not solved. |

### Allowed Conclusion For No-Opposite Frames

The correct conclusion is:

> With one side only, current-frame identity is underdetermined. The code may
> still use the side for single-side tracking, but persistent learning should
> only happen after the selected side proves usable geometry. Any stricter
> identity reject needs real-frame evidence and an explicitly named assumption.

This is why the current best candidate protects learning order instead of
forbidding single-side tracking.

### Evidence Ladder For Future Behavior Rules

| Evidence level | What it allows |
| --- | --- |
| Static code/reference only | Protect ordering of existing current-frame facts; do not invent a single-side identity gate. |
| Diagnostic logs with `seed_state`, trace x ranges, rpts/rptsc counts, mid begin/attach, `mid_position/width_base` before/after | Decide whether the observed failure is learning pollution, publish pollution, ring/cross mis-entry, or control response. |
| Real frame sequence showing the same single-side pattern repeatedly pulls `mid_position` across the lane while selected midline geometry is suspicious | Consider a narrow learning-state guard, not a control fallback. |
| Real frame sequence proving a specific geometric predicate separates bad straight crawl from legal curves/ring/cross approaches | Consider a named single-side identity gate, with the predicate and sample boundary recorded. |

Until that last level exists, a single-side hard reject is not justified.

## 2026-06-08 Latest Issue Ledger After Learning-Gate Audit

This ledger is the current state after the learning-gate and single-side
observability audits. It supersedes earlier shorthand that treated "publish
success" as the learning gate.

| Issue | Current evidence | Status | Next correct action |
| --- | --- | --- | --- |
| Dual hypothesis proposal | RT1064 ordinary flow keeps left/right arrays and selects one side; current code already generates `rptsc0` from left and `rptsc1` from right. | Rejected route. | Do not revive. Any chooser would introduce a hidden assumption. |
| Cross BEGIN stale state | `cross_begin()` requires strict double-L and calls `cross_leave()` when both strict Ls disappear. | Runtime code closed for the known contract. | Real CROSS_IN camera replay still useful, but do not patch BEGIN without new evidence. |
| CROSS_IN far-L `old_l` continuity | Current farline rebuilds current points, then reuses old L only when prior source exists and index fits current farline length. | Keep. This is guarded farline-index continuity, not stale midline fallback. | Do not delete; do not add reuse-count/drift thresholds without real CROSS_IN evidence. |
| Ring active reference | Active `ring_process()` enters from single-side `l_ok` plus opposite `boundary_is_straight()`; Unity pending/AIB/BW/ring_times is archived old evidence only. | Active source aligned to RT1064-style ring contract. | If ring false-triggers, inspect `l_ok` quality and opposite straight evidence, not Unity chain. |
| Dual-side raw trace identity | `trace_identity_reject_bits()` rejects left passing right seed, right passing left seed, and same-row crossing. | Covered for frames with relational raw evidence. | Do not relax without a legal-frame counterexample. |
| Dual-side IPM/work identity | `work_pair_order_ok()` rejects current-frame paired work points with `left_x >= right_x`; `d2ccaf0` prevents rejected frames from learning `mid_position`. | Covered for frames with enough paired work evidence. | Do not add width bounds; current gate is order-only. |
| Single-side/no-opposite identity | With one side only, opposite seed/trace/IPM relation is undefined, so identity is underdetermined. | Open by information boundary. | Do not hard reject. Protect learning order first; require diagnostics before any identity gate. |
| Ordinary search-center learning before selected midline geometry | Current code still calls `update_search_center()` before `build_selected_midline()`. | Open; best behavior candidate identified, not implemented. | If behavior change is approved, ordinary-frame learning should wait until selected midline geometry reaches `k_min_border_step`, while preserving frame-start `width_base` semantics. |
| Straight twisting | Current control chain is `guide_error -> target_yaw -> yaw_cmd -> target_l/r`; it does not revalidate visual identity. | Split unresolved. | If `guide_error` jumps, keep investigating vision/learning. If `guide_error` is stable but yaw/duty oscillates, investigate control/IMU/wheel parameters separately. |
| Live log proof gap | Current changed-state live output can suppress quiet straight drift and lacks exact learning before/after fields. | Open evidence gap. | Diagnostic-only fields remain the safest first code change if real logs are needed. |

### Current Best Behavior Candidate, Not Implemented

For ordinary frame-start only:

1. Do not learn at the current early `update_search_center()` location.
2. Run `build_selected_midline()`.
3. Run `publish_track_result()`.
4. If publish succeeds and this was a frame-start ordinary frame, learn
   `mid_position/width_base`.
5. Use `ordinary_frame0`, not post-element `rt->cross.state` or
   `rt->ring.kind`, to decide whether `width_base` may low-pass.
6. Leave `publish_track_result()` and lookahead control safety internals
   unchanged.

This candidate moves toward the requested end state because it protects the
cross-frame learning owner without inventing a single-side identity rule.

## 2026-06-08 Post-Rejection Audit: Why Dual Hypothesis Was Not Needed

User challenged the same-trace left/right dual-hypothesis idea with: "we
already do left boundary -> `track_leftline()` and right boundary ->
`track_rightline()`". The challenge is correct. This section records the fixed
reasoning so the rejected route is not revived after context compaction.

### Fresh Four-Role Read-Only Recheck

| Role | Rechecked evidence | Conclusion |
| --- | --- | --- |
| RT1064 reference contract | RT1064 starts two independent traces from `center - begin_x` and `center + begin_x`, builds `rptsc0` with `track_leftline()` and `rptsc1` with `track_rightline()`, then selected `track_type` consumes only one side. `track_type_e` has no dual state. | RT1064 has no same-trace left/right dual hypothesis. |
| Current implementation dataflow | Current `build_frame_boundaries_and_candidates()` already builds `rptsc0` from left trace and `rptsc1` from right trace. `pick_track_type()` selects one side. `build_selected_midline()` consumes only the selected candidate. | Current ordinary path already matches the reference candidate shape. |
| Git regression audit | `ce65c9d` introduced `mid_position/width_base`; `e1069df`, `52f0801`, `724c7cb`, and `d2ccaf0` progressively moved learning behind stronger current-frame evidence. None proves a same-trace dual-hypothesis contract. | The historical trend is "learn later from verified evidence", not "try both identities". |
| Global direction guard | Any same-trace chooser must use center, width, temporal continuity, attach distance, or another hidden assumption. | Dual hypothesis only moves the ambiguity; it does not solve the single-side evidence gap. |

### Fixed Rationale Table

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 does not try both identities for one trace; left trace uses `track_leftline()`, right trace uses `track_rightline()`, and ordinary control selects one candidate. | Current ordinary path already does this: `rptsc0 = track_leftline(rpts0s, ...)`, `rptsc1 = track_rightline(rpts1s, ...)`, and `build_selected_midline()` chooses by `work_track_type`. | No runtime change. The dual-hypothesis proposal is withdrawn and remains a rejected research route only. | Adding both identities would introduce an invented chooser and hide the real no-opposite-anchor observability problem. | Nothing is synthesized, no old centerline or `guide_error` is held, and no width/drift threshold is introduced. Rejecting the proposal reduces fallback-like behavior rather than adding it. |
| RT1064 has no `mid_position/width_base`; it rebuilds ordinary starts from fixed begin parameters each frame. | Current project intentionally keeps `mid_position/width_base` from Front_Car history for recovery, so this extra learning state needs stricter ownership than RT1064 can directly provide. | The remaining behavior candidate is only a learning-order guard: for frame-start ordinary frames, learn after selected midline geometry reaches `k_min_border_step`. It is not implemented in this section. | This follows the commit trend from `e1069df` and `d2ccaf0`: move cross-frame learning behind the strongest available current-frame evidence. | It does not reject single-side tracking, guess an opposite side, smooth output, or change control publication. It only delays the persistent acquisition prior if later approved. |

### Current Final Position

The reason the dual-hypothesis idea appeared was an attempted answer to
single-side/no-opposite-anchor identity ambiguity. That reason is insufficient.
With only one side visible, current-frame left/right identity is underdetermined
unless an extra assumption is added. The correct next line of thought is not to
try both identities, but to protect the current project's extra cross-frame
learning state and require real diagnostic evidence before adding any stricter
single-side identity rule.

## 2026-06-08 Formal Learning-Order Contract

This section tightens the remaining behavior candidate after re-reading current
consumers and the frame-mode classifier. It is still a candidate, not an
implemented runtime change.

### Consumer Audit

| State | Runtime consumers | Meaning |
| --- | --- | --- |
| `mid_position` | `find_seeds()` reads it as the next-frame seed search center. `report.cpp` prints/writes it. `runners.cpp` initializes it at live start and preserves it across replay frames. | Acquisition prior for the next frame, not the current control centerline. |
| `width_base` | `update_search_center()` reads it for single-side center extrapolation and low-pass updates it on ordinary paired seed evidence. `runners.cpp` initializes it. | Cross-frame road-width prior for seed acquisition. |
| `guide_error` | `control.cpp` consumes it through `guide_error -> target_yaw -> yaw_cmd -> target_l/r`. | Current-frame control input. It is not recomputed from `mid_position`. |
| `ring` / `zebra` helpers | They deliberately use stable `MID_X` for symmetric fill/threshold starts where dynamic center would pollute detection. | Dynamic `mid_position` is intentionally scoped away from those helpers. |

The important result is that delaying `update_search_center()` changes only the
next-frame seed acquisition prior. It does not directly alter the current
published `guide_error`, control formula, or actuator command.

### Frame-Mode Timing Detail

Current `classify_frame_mode()` only treats a frame as `cross_near` or
`ring_active` when the element already existed at frame start:

- `cross_near` requires `action.cross_state0 != CROSS_STATE_NONE`.
- `ring_active` requires `action.ring_kind0 != RING_KIND_NONE`.

Therefore a frame that newly detects cross or ring during `element_process()` is
still selected by the ordinary candidate path for this frame. This matters for
the learning-order candidate: moving ordinary learning after
`build_selected_midline()` does not automatically make newly-entered element
frames consume element crop/short-midline semantics. The frame-mode contract
already prevents that.

### Minimal Candidate Contract

If runtime behavior is approved later, the smallest contract is:

1. Capture `ordinary_frame0` immediately after the frame-start action fields:
   `action.cross_state0 == CROSS_STATE_NONE && action.ring_kind0 == RING_KIND_NONE`.
2. Keep the current early `update_search_center()` timing for frames that were
   already in cross/ring at frame start. This avoids changing CROSS_IN farline
   and existing ring-stage semantics in the first patch.
3. For `ordinary_frame0`, skip the current early call.
4. Run `snapshot_ring_frame_start_action()`, `element_process()`,
   `classify_frame_mode()`, `apply_frame_start_element_crop()`, and
   `build_selected_midline()` in the current order.
5. Run `publish_track_result()`.
6. If it succeeds and `ordinary_frame0` is true, commit the learned
   `mid_position/width_base`. The 2026-06-09 complete-forward-lookahead gate is
   now part of the ordinary learning contract because short/backward lookahead
   frames were observed to create strong bad control commands.
7. Change `update_search_center()` to accept an explicit `allow_width_base`
   flag. Use `allow_width_base = ordinary_frame0` for delayed ordinary learning
   and `allow_width_base = 0` for already-in-element early learning. Do not let
   post-`element_process()` mutated `rt->cross.state` / `rt->ring.kind` decide
   whether `width_base` may low-pass update.

Pseudo-shape:

```cpp
void update_search_center(runtime_t *rt, int allow_width_base)
{
    ...
    if(allow_width_base && seed_pair_accepted(&rt->seeds, rt->seed_state))
    {
        ...
    }
    ...
}
```

And in the frame owner:

```cpp
const int ordinary_frame0 =
    action.cross_state0 == CROSS_STATE_NONE &&
    action.ring_kind0 == RING_KIND_NONE;

...
if(!ordinary_frame0)
{
    update_search_center(rt, 0);
}
...
const int mid_ok = build_selected_midline(rt, &mode, ref);
if(!publish_track_result(rt, &mode, mid_ok, ref))
{
    return 0;
}
if(ordinary_frame0)
{
    update_search_center(rt, 1);
}
```

### Why This Is Not A Fallback

| 参考版怎么样 | 当前代码差异 | 候选改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 has no dynamic search-center state; it rebuilds starts each ordinary frame and only computes control after a selected centerline is built. | Current project has `mid_position/width_base`, kept for Front_Car-style acquisition recovery; short/backward ordinary midlines can now fail publish by design. | Delay ordinary-frame learning until `publish_track_result()` succeeds. | This extends verified-before-learn through the current ordinary publish gate. | It does not create a line, choose between two identities, hold old output, change `guide_error`, change duty, or add width/drift thresholds. |
| RT1064 ordinary track selection is left/right single-side, not dual. | Current ordinary path already matches this. | Keep single-side tracking allowed. | The problem is cross-frame learning ownership, not ordinary candidate generation. | The selected side still controls only if the existing midline/publish gates pass. |
| RT1064 control publication and current seed acquisition are separate concepts in this project, and RT1064 has no dynamic search-center prior. | `publish_track_result()` includes complete forward lookahead, and this gate now represents the known bad-frame class. | Use full publish success as the ordinary learning gate. | Avoid letting a frame that is unsafe for current ordinary control teach next-frame acquisition. | Failed publish still withholds current control and now also withholds cross-frame learning; no old state is substituted. |

### Still Not Solved

This candidate does not prove a single-side trace has the correct left/right
identity when no opposite seed/trace/work-point relation exists. It only ensures
that such a frame cannot teach the next seed search center unless it also passes
the ordinary publish gate.

If real frames later show that wrong single-side identity can still pass the
complete forward-lookahead publish gate, then the next step is diagnostic
evidence for a specific identity predicate. It is not same-trace dual
hypothesis and not a generic width/drift/temporal fallback.

## 2026-06-08 Learning-Order Truth Table And Impact Scope

This section records the exact frame classes affected by the candidate. It is
intended to prevent accidental broad behavior changes if the candidate is later
implemented.

### Truth Table

| Frame class | Current `HEAD` behavior | Candidate behavior | Runtime effect |
| --- | --- | --- | --- |
| `find_seeds()` fails, not `CROSS_IN` | Return `TRACK_REJECT_NO_SEED`; no learning. | Same. | No change. |
| `find_seeds()` fails in `CROSS_IN` | Run `cross_process()` farline path; no `update_search_center()`. | Same. | No change. |
| seed exists but `trace_edges()` fails, not `CROSS_IN` | Return trace failure; no learning. | Same. | No change. |
| seed exists but `trace_edges()` fails in `CROSS_IN` | Run farline path; no learning. | Same. | No change. |
| trace succeeds but `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` fires, not `CROSS_IN` | Return before learning (`d2ccaf0`). | Same. | No change. |
| trace succeeds but IPM side-cross fires in `CROSS_IN` | Clear near candidates and run farline; no learning. | Same. | No change. |
| Frame started in cross or ring and trace/IPM are accepted | Current early `update_search_center()` runs before element evolution; `width_base` does not update because state is already non-ordinary. | Keep early call, with `allow_width_base = 0`. | Preserve first patch boundary for existing element frames. |
| Frame started ordinary, selected side exists and publish succeeds | Current could learn before publish. | Learn after publish. | Learned value is backed by the same current-frame geometry allowed to drive control. |
| Frame started ordinary, no selected side (`work_track_type == NONE`) | Current may already have learned from seed/trace before returning no midline. | Do not learn. | Intended change: no selected current side means no cross-frame acquisition writeback. |
| Frame started ordinary, selected side exists but `mid_ok < k_min_border_step` | Current may already have learned from seed/trace. | Do not learn. | Intended change: too-short selected geometry cannot teach next-frame seed center. |
| Frame started ordinary, `mid_ok >= k_min_border_step` but `publish_track_result()` fails on forward lookahead | Current could learn and withhold control output. | Do not learn. | Prevents short/backward lookahead geometry from poisoning next-frame seed acquisition. |

### Invariants Required If Implemented

| Invariant | Why it matters |
| --- | --- |
| `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` must still return before any learning. | Keeps `d2ccaf0` intact; rejected current-frame identity cannot teach next-frame center. |
| `snapshot_ring_frame_start_action()` remains before `element_process()`. | Ring crop/action still uses frame-start state. |
| `classify_frame_mode()` and `apply_frame_start_element_crop()` order remains unchanged. | Avoids changing cross/ring current-frame candidate ownership. |
| Already-in-cross/ring learning timing is preserved in the first patch. | Avoids mixing the ordinary straight fix with CROSS_IN/ring behavior changes. |
| `publish_track_result()` and `midline_has_lookahead()` are not changed. | Current control publication safety remains exactly as before. |
| `update_search_center()` receives explicit `allow_width_base`; it must not infer ordinary status from post-element mutated state. | Preserves the current frame-start ordinary width-base semantics. |
| No single-side identity reject is added. | The candidate is not a guessed left/right identity fix. |
| No old `mid_position`, old midline, old `guide_error`, or duty hold is introduced. | Keeps the change out of fallback/smoothing territory. |

### Exact Remaining Risk

The candidate blocks a class of learning pollution where seed/trace/IPM survive
but no publishable ordinary midline exists. It does not block a wrong
single-side identity that can still pass the complete forward-lookahead publish
gate. That remaining risk needs real-frame diagnostics with `seed_state`, seed
coordinates, trace ranges, candidate counts, `mid_ok`,
`mid_position/width_base` before/after, and final `guide_error`.
