# Embedded Tracking Guidelines

> Code quality standards for this embedded C/C++ tracking project.

---

## Overview

This repository is a small embedded C/C++ tracking project. Code quality means
the behavior is traceable from current-frame image evidence, the reference
version, and a narrow validation command. Prefer simple local logic over clever
abstractions.

---

## Forbidden Patterns

### Fallback-Style Tracking Fixes

Do not hide missing geometry by reusing stale state or by silently widening a
condition until the output "looks" stable.

Forbidden:

- Reusing last-frame midline or last-frame boundary as a substitute for missing
  current-frame evidence.
- Adding broad "if missing, keep previous" logic in `mainline`, `cross`,
  `ring`, `boundary`, or `imgproc`.
- Silently holding `guide_error`, `track_type`, trace points, or boundaries when
  current-frame midline construction fails.
- Converting a failed or identity-swapped trace into a guessed opposite-side
  line.
- Letting `l_ok` enter cross or ring unless the reference contract explicitly
  allows that state.
- Changing thresholds without tying them to the reference implementation, a
  measured diagnostic frame, or a clear hardware constraint.
- Adding a complex abstraction before proving the current simple function cannot
  express the fix.

Wrong:

```cpp
if(midline.count == 0) {
    midline = rt->last_midline;
}
```

Correct:

```cpp
if(!has_current_geometry) {
    return TRACK_TYPE_NONE;
}
```

Reason: control must know when the current frame lacks valid geometry. A hidden
fallback masks the defect and makes later cross/ring/mainline audits unreliable.

Allowed:

- Reject the frame or state path with a precise reason.
- Keep diagnostics that explain why current-frame evidence failed.
- Suppress an element state only when the reference state machine has the same
  suppression behavior or the current project records why an input is missing.

### Evidence-Free Tracking Changes

Every tracking modification is high risk. Before editing, collect and record:

- the current symptom or failing diagnostic frame/log;
- the reference-version contract or the explicit reason it cannot apply;
- the recent git diff region if the bug is a regression;
- the smallest code surface that owns the state or data flow.

Do not start with a defensive branch, timeout, or smoothing rule unless the
reference version contains that concept or a diagnostic proves it is the owner
of the defect.

---

## Required Patterns

### Runtime And Config Numeric Parsing Contract

#### 1. Scope / Trigger

Applies when changing command-line parsing, environment variables, yaml config
loading, sysfs numeric reads, or any helper that feeds runtime/config values
into app, driver, control, or diagnostic code.

#### 2. Signatures

- Command parser: `parse_options(int argc, char **argv, options_t *opt)`
- Environment helpers: `read_env_text()`, `read_env_int()`,
  `read_env_int_clamped()`, `read_env_flag()`
- Config loader: `load_control_config(const char *path)`
- Driver/sysfs numeric readers: local `strtol` helpers such as IMU raw reads

#### 3. Contracts

- Integer text must be parsed with `strtol` plus `errno`, range, and full-tail
  validation. Do not use `atoi`.
- Float text must be parsed with `strtof` plus `errno`, full-tail validation,
  and finite-value validation. Do not allow `nan`, `inf`, or trailing junk.
- Flat yaml config lines may use `#` comments; strip the comment before
  key/value trim and numeric parsing so inline comments are not treated as
  numeric tails.
- Sysfs numeric readers may accept trailing whitespace/newline only; any other
  trailing character is invalid.
- Missing or empty optional env/config values may keep defaults, but invalid
  non-empty values must be explicit (`EnvWarn` or `ConfigWarn`) and must not
  silently coerce to zero.
- Env flag helpers must accept only explicit boolean text: `0`, `1`, `false`,
  or `true`. Any other non-empty value is invalid and must return the caller's
  fallback after printing `EnvWarn`.
- Public app helpers must guard null pointers directly before dereferencing.

#### 4. Validation & Error Matrix

- Env unset/empty -> return fallback, no warning.
- Env flag `0`/`false` -> return 0; `1`/`true` -> return 1.
- Env invalid non-empty -> print `EnvWarn`, return fallback.
- Env flag invalid non-empty, such as `2`, `yes`, or `off` -> print `EnvWarn`,
  return fallback.
- Config unknown key -> print `ConfigWarn`, preserve existing/default fields.
- Config invalid value -> print `ConfigWarn`, preserve that field's current
  value.
- Config line `target_rps: 4.5 # ordinary speed` -> parse `4.5`.
- Sysfs empty, overflow, or non-whitespace tail -> report read failure to caller.

#### 5. Good/Base/Bad Cases

- Good: `SMARTCAR_UVC_FPS=60` parses to `60`.
- Good: `target_rps: 4.5 # ordinary speed` parses to `4.5`.
- Good: `FRONT_CAR_ENABLE_DRIVE=1` enables drive and
  `FRONT_CAR_ENABLE_DRIVE=false` disables it.
- Base: missing `SMARTCAR_UVC_FPS` uses the default fps.
- Bad: `SMARTCAR_UVC_FPS=60x`, `outer_kp=nan`, or `control_period_ms=20ms`
  must not be accepted.
- Bad: `FRONT_CAR_ENABLE_DRIVE=2` or `SMARTCAR_ASSISTANT=off` must not be
  treated as true.

#### 6. Tests Required

- Host tests must cover valid values, missing/empty values, invalid trailing
  text, overflow, and default/previous-value preservation where practical.
- Config tests must cover inline `#` comments because the parser is not a full
  YAML library but does support comments in the flat `key: value` format.
- Env flag tests must cover unset/empty fallback, `0`, `1`, `false`, `true`,
  and at least one invalid non-empty value returning fallback.
- If a parser is not directly host-testable because it depends on board-only
  drivers, at minimum the affected target must compile in `bash code/test.sh`
  and the parser contract must be reviewed in diff.

#### 7. Wrong vs Correct

Wrong:

```cpp
cfg.control_period_ms = std::atoi(value);
```

Correct:

```cpp
int parsed = 0;
if(!parse_int_value(value, &parsed)) {
    warn_bad_value("control_period_ms", value);
    return;
}
cfg.control_period_ms = parsed;
```

Wrong:

```cpp
return val == nullptr || val[0] == '\0' ? fallback : (val[0] != '0');
```

Correct:

```cpp
if(std::strcmp(val, "0") == 0 || std::strcmp(val, "false") == 0) {
    return 0;
}
if(std::strcmp(val, "1") == 0 || std::strcmp(val, "true") == 0) {
    return 1;
}
warn_bad_flag(name, val);
return fallback;
```

### Tracking Modification Contract

For changes under `code/tracking/`, `code/core/control.cpp`, or tracking report
output:

1. Use Trellis to keep the active `prd.md`, research notes, spec updates, and
   check context aligned.
2. Prefer `fast_context_search` for unclear local code discovery. If the MCP is
   not visible at first, wait/retry because it can load slowly; only then
   downgrade to `rg` and direct file reads, and state that downgrade in notes.
3. Use `smart-search-cli` for external/current documentation, tool behavior, or
   user-provided URLs. Fetch page text before relying on a source.
4. Compare against the reference version before changing behavior.
5. Keep the edit small, direct, and readable in plain C/C++; do not introduce
   new framework-style abstractions for a local state-machine fix.
6. For critical tracking edits, request four fixed read-only audit roles when
   the runtime allows it:
   - reference contract audit;
   - current implementation audit;
   - git regression audit;
   - Trellis/spec/check-gate audit.
7. If the agent limit prevents four roles, record the limit and cover the
   missing roles in the main session before editing.
8. Validate with the narrowest meaningful command first, then the project check
   commands listed below.
9. Record the fixed change rationale table required by
   `.trellis/spec/tracking/critical-audit-guide.md` for every behavior
   change. The table must state what the reference does, why the current edit
   is justified, whether a threshold or hardware difference is involved, and
   how it was validated.

### Highest Code Rule

Tracking C/C++ must stay simple and direct. Prefer explicit local checks and
named state over new abstraction layers, hidden caches, generic policy engines,
or broad rewrites.

If a helper is added, it must remove real duplication or make a reference
contract easier to verify line by line. Do not introduce a helper only to make a
small state-machine rule look generic.

### Trace And Midline Ownership

Left and right evidence must keep their identity:

- A left trace must remain left-boundary evidence.
- A right trace must remain right-boundary evidence.
- If both current-frame seeds exist, a left trace that reaches or passes the
  current right seed x position is invalid left evidence.
- If both current-frame seeds exist, a right trace that reaches or passes the
  current left seed x position is invalid right evidence.
- If both traces have points on the same raw row, the left trace x must stay
  strictly left of the right trace x on that row.
- `build_boundary_from_trace()` must not turn identity-swapped traces into valid
  boundaries.
- `pick_track_type()` and midline builders must select from verified
  current-frame geometry, not stale or guessed ownership.

This rule is not a fallback. Rejecting invalid ownership is preserving the
meaning of the evidence.

Wrong:

```cpp
build_boundary_from_trace(&rt->left_trace, rt->matrix, use_matrix, &rt->track.left);
build_boundary_from_trace(&rt->right_trace, rt->matrix, use_matrix, &rt->track.right);
```

Correct:

```cpp
const int reject = trace_identity_reject_bits(rt, left_ok, right_ok);
if(reject & TRACE_IDENTITY_REJECT_ROW_CROSS) {
    left_ok = 0;
    right_ok = 0;
}
// Only surviving current-frame traces may enter build_boundary_from_trace().
```

### Single-Side Identity Boundary

A single surviving side with no current opposite seed, opposite trace, or paired
IPM/work points is not the same evidence class as a dual-side identity failure.

Required rule:

- Do not add a hard single-side reject only because the frame has no opposite
  anchor.
- Do not run both left/right offset hypotheses on the same single-side trace in
  the ordinary mainline. Current code and RT1064 already build separate
  left-derived and right-derived candidates.
- Do not treat attach distance to `control_ref` as a reference-backed runtime
  gate. RT1064 also finds the nearest candidate point and normalizes it to
  `cx/cy` without an attach-distance reject.
- If single-side frames are suspected of corrupting tracking, separate
  current-frame control risk from cross-frame learning risk before editing.
- If a behavior change is later justified, prefer protecting the project-local
  `mid_position/width_base` learning state over banning single-side tracking.

Allowed:

- Add diagnostic-only fields that record the single-side evidence path.
- Reject a frame only when current-frame relational evidence proves invalid
  ownership, such as opposite-seed crossing, same-row trace crossing, or paired
  IPM/work-point reversal.

Wrong:

```cpp
if((rt->seed_state & 3) != 3) {
    return TRACK_TYPE_NONE; // Wrong: RT1064 ordinary tracking allows single-side control.
}
```

Correct:

```cpp
if(left_ok && right_ok && traces_cross_on_same_row(&rt->left_trace, &rt->right_trace)) {
    left_ok = 0;
    right_ok = 0;
}
```

Reason: a single polyline does not uniquely prove whether it is a correct
single-side boundary, an identity-swapped boundary, a legal curve/element
approach, or noise. Any runtime rule for this case introduces an extra
assumption and must be justified by real-frame evidence.

### Search-Center Learning Order

`mid_position` and `width_base` are cross-frame seed acquisition state. They
are not the current control centerline and must not be used as a substitute for
current-frame geometry.

Required rules:

- `find_seeds()` may read `mid_position` as the current frame's seed-search
  center.
- `update_search_center()` may write `mid_position/width_base` only from
  current-frame seed/trace evidence that has survived the relevant identity
  checks.
- `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` must return or switch to the valid
  farline path before any search-center writeback.
- Search-center learning must be gated by a successfully published selected
  midline, not by a guessed single-side identity.
- Use successful `publish_track_result()` as the `mid_position` learning gate
  for frames that have current-frame nearline seed/trace evidence. Ordinary
  frames require complete forward lookahead before publishing, so a short or
  backward-lookahead frame must not teach the next seed-search center.
- For frame-start cross/ring frames that reached the accepted nearline
  seed/trace/IPM branch where search-center learning used to occur, keep
  `width_base` frozen but delay `mid_position` learning until publication
  succeeds. Do not add learning to CROSS_IN farline-only or IPM-rejected
  fallback paths that previously had no search-center writeback.
- Keep `publish_track_result()` and `midline_has_forward_lookahead()` as
  publication safety gates; do not weaken them to make learning easier.
- Use an explicit frame-start ordinary flag, such as `allow_width_base`, when
  deciding whether `width_base` may low-pass update. Do not infer this from
  `rt->cross.state` or `rt->ring.kind` after `element_process()` has mutated
  them.

Wrong:

```cpp
element_process(rt);
if(rt->cross.state == CROSS_STATE_NONE && rt->ring.kind == RING_KIND_NONE) {
    update_search_center(rt); // Wrong: post-element state changes the frame-start learning contract.
}
```

Correct shape if the delayed ordinary-learning contract is approved:

```cpp
const int ordinary_frame0 =
    action.cross_state0 == CROSS_STATE_NONE &&
    action.ring_kind0 == RING_KIND_NONE;

int defer_element_search_center_update = 0;
...
if(!ordinary_frame0) {
    defer_element_search_center_update = 1;
}
...
const int mid_ok = build_selected_midline(rt, &mode, ref);
if(!publish_track_result(rt, &mode, mid_ok, ref)) {
    return 0;
}
if(ordinary_frame0) {
    commit_search_center_update(rt, TRACK_SEARCH_UPDATE_ORDINARY, 1);
} else if(defer_element_search_center_update) {
    commit_search_center_update(rt, TRACK_SEARCH_UPDATE_ELEMENT, 0);
}
```

Reason: this protects the project-local acquisition prior without synthesizing
geometry, trying both identities, holding old output, or letting a
current-frame publish failure affect the next-frame seed search. The
`ordinary_frame0` flag keeps road-width learning tied to frame-start ordinary
geometry. The explicit deferred-element flag preserves the previous element
trigger domain while moving its writeback after a publishable current frame.

### Diagnostic-Only Tracking Reports

Tracking diagnostics must not become hidden behavior changes.

Diagnostic fields may record:

- seed state immediately after `find_seeds()` and after `trace_edges()`;
- `mid_position` and `width_base` before and after `update_search_center()`;
- `search_update_kind` as the learning submission path. Actual movement is the
  `before/after` delta; a guard may enter the ordinary path but keep the same
  `mid_position`.
- raw trace min/max x ranges;
- `rpts0s/rpts1s` and `rptsc0/rptsc1` counts;
- selected `build_rptsn()` begin id and pre-overwrite attach distance.

Forbidden in a diagnostic patch:

- changing `track_type`, `guide_error`, `mid_position`, `width_base`, or duty
  output;
- changing tracking/control branch conditions while adding report fields;
- expanding live beeps to every numeric jitter by default;
- synthesizing missing opposite geometry for report convenience.

If a diagnostic patch is needed, do it as a separate commit from any behavior
change. The first diagnostic patch should prefer detail/report/replay output;
live changed-state expansion requires an explicit diagnostic mode or coarse
proof buckets.

### Assistant Display Boundary Contract

Assistant display changes are diagnostics unless they explicitly change
tracking or control state.

Required rules:

- The active SDK helper
  `seekfree_assistant_camera_boundary_config(boundary_type, dot_num, x1, x2,
  x3, y1, y2, y3)` exposes only three boundary inputs, but the protocol structs
  define `SEEKFREE_ASSISTANT_CAMERA_MAX_BOUNDARY == 8`.
- If more than three display boundaries are needed, send camera and dot packets
  through the existing transfer callback contract instead of editing tracking
  data. Keep `dot_type` as `XY_BOUNDARY`, low nibble as the active boundary
  count, and `valid_flag` bits aligned with display channel indexes.
- Every displayed boundary in one frame shares one `dot_num`; shorter display
  point arrays must be padded with their final point. Do not reduce `dot_num`
  to the shortest line because that silently hides longer left/right/midline
  evidence.
- Seed-search diagnostics may read `START_HIGH`,
  `track.seed_state_find`, `track.seed_left_find`, and
  `track.seed_right_find` to draw search-row and seed markers, but must not
  write `seed_state`, `mid_position`, `width_base`, `track_type`,
  `guide_error`, trace points, or control output.

Wrong:

```cpp
// Wrong: replacing one control/display line to free a color hides evidence.
seekfree_assistant_camera_boundary_config(XY_BOUNDARY, n, left_x, seed_row_x, right_x,
                                          left_y, seed_row_y, right_y);
```

Correct:

```cpp
// Correct: keep left/mid/right and add seed diagnostics as extra display-only
// channels in the camera dot packet.
send_display_frame(display_boundaries, display_count, max_dot_num);
```

### Tracking-Derived Control Boundary

Do not mechanically port a reference steering-servo command into the current
differential-drive outer loop. RT1064 computes both a heading-style `error` and
a `pure_angle`, but the active reference path feeds `pure_angle` into
`pid_solve(&servo_pid, pure_angle)` and then into the steering servo. Current
`front_car_mainline` feeds `rt->track.guide_error` into
`guide_error -> target_yaw -> yaw_cmd -> target_l/target_r`.

Allowed reference-alignment area:

- The raw wheel-point / IPM control reference point may be compared to RT1064
  `mapx/mapy` and `(W/2, H*0.78)` behavior.
- The heading-style angle error may be compared to RT1064 `error` and its
  forward bias.
- The current differential chain may be tuned or redesigned only as an explicit
  control-architecture task, with its own rationale table and validation.

Forbidden:

- Replacing `guide_error` with RT1064 `pure_angle` only because the reference
  calls that section "pure pursuit".
- Treating `SMOTOR_RATE`, `servo_pid`, `SMOTOR1_CENTER`, or `servo_duty()` as
  available concepts in the differential-drive output chain.
- Hiding straight-road twisting by adding smoothing, stale error reuse, or a
  steering-angle formula without proving the current owner of the defect.

Wrong:

```cpp
// Wrong: pure_angle is a steering-servo target in RT1064, not this car's yaw-rate demand.
rt->track.guide_error = pure_angle;
```

Correct:

```cpp
// Current contract: publish heading-style guide_error; control.cpp converts it to target_yaw.
rt->track.guide_error = lookahead_error(&rt->track.mid, LOOKAHEAD_DIST, ref);
```

### IPM Table Indexing And Control Reference

The generated IPM tables are row-major image tables. Raw-to-IPM lookups must
read `g_raw_to_ipm_x[raw_y][raw_x]` and `g_raw_to_ipm_y[raw_y][raw_x]`;
IPM-to-raw lookups must read `g_ipm_to_raw_x[ipm_y][ipm_x]` and
`g_ipm_to_raw_y[ipm_y][ipm_x]`.

Required rules:

- The wheel/control reference raw point is `(RAW_W / 2, RAW_H * 0.78F)`.
- With IPM enabled, `control_ref_point()` maps that raw point through
  `perspective_lookup_raw_to_ipm()` and clips the rounded IPM result.
- With IPM disabled or lookup failure, `control_ref_point()` falls back to
  `{rt->control_center_x, START_HIGH}`.
- Do not swap `[x][y]` into the table access. Calvariaa PR #6 fixed the RT1064
  reference from `mapx[W/2][H*0.78]` to `mapx[H*0.78][W/2]`; the current
  project must preserve that corrected `[y][x]` contract.

Required test:

- `search_center_learning_test` must keep a whitebox contract that compares
  `control_ref_point()` with direct `g_raw_to_ipm_*[raw_y][raw_x]` access.

If pure-pursuit curvature is ever introduced for the current differential car,
define a new contract explicitly, for example current-frame geometry ->
curvature -> `target_yaw` or `yaw_cmd`, and validate it against
`code/core/control.cpp` instead of copying the servo formula.

### Boundary Corner And Straight Contract

`code/tracking/boundary.cpp` owns the current-frame corner and straight
signals used by cross and ring:

- Input must be the current frame's boundary point set after perspective,
  smoothing, and equal-distance resampling.
- `local_angle_d()` / `build_ang_pts()` are the project-local equivalent of
  RT1064 `local_angle_points()` plus `nms_angle()`: use a three-point local
  vector angle and non-maximum suppression, not row-by-row center scanning.
- `l_found` means a single-side L candidate was seen in boundary geometry.
- `l_ok` means that single-side L is in the consumable front segment. Ring and
  zebra may use it; cross must not.
- `l_pair_ok` means the left and right L candidates passed strict double-L
  width/open-direction checks. Cross entry may use `l_pair_ok`.
- `boundary_is_straight()` is the current opposite-side straight predicate for
  ring. It must reject short, curved, or L-containing boundaries.
- This project has no Y-road requirement; do not add Y-corner state only
  because the AuTop article mentions it.

Wrong:

```cpp
// Wrong: lets a weak single-side L enter the strict cross path.
if(rt->track.left.l_ok && rt->track.right.l_ok) {
    rt->cross.state = CROSS_STATE_BEGIN;
}
```

Correct:

```cpp
if(rt->track.left.l_pair_ok && rt->track.right.l_pair_ok) {
    rt->cross.state = CROSS_STATE_BEGIN;
}
```

Tests:

- `code/test/boundary_contract_test.cpp` must stay wired into
  `code/test.sh --host` and cover plain straight, single-L plus opposite
  straight, and strict double-L semantics.
- `code/test/element_entry_contract_test.cpp` must stay wired into
  `code/test.sh --host` and prove cross consumes strict double-L while ring
  consumes single-L plus opposite-straight.
- `code/test/search_center_learning_test.cpp` must keep the frame-start element
  action assertions: newly entered cross/ring state is deferred to the next
  frame, while frame-start cross/ring state may select the current element
  candidate.
- If a threshold or scan window in `boundary.cpp` changes, update that test or
  add a narrower current-owner test before changing cross/ring state logic.

### Point Resampling Contract

`code/tracking/imgproc.cpp::resample_points()` owns equal-distance resampling
for boundary, cross farline, ring detection refresh, and final control midline
normalization.

Required:

- Keep residual distance as floating point. Do not store the remaining segment
  length in an integer.
- A segment from `(0,0)` to `(4,3)` has length `5`; with `sample_dist=2`, the
  output must include `(0,0)`, `(1.6,1.2)`, and `(3.2,2.4)` in that order.
- Repeated inserted points that jump back to the previous source point are a
  bug, not acceptable simplification.
- Invalid-prefix trimming may happen through `first_valid_run()`, but valid
  interior segments must preserve their fractional spacing.

Background:

- Calvariaa PR #6 in `SJTU-AuTop/RT1064-Code` fixed the RT1064 reference
  `resample_points()` bug by changing `remain` from integer to floating point.
  Keep this project on the fixed contract.

Test:

- `code/test/midline_lookahead_test.cpp` must keep the resample no-repeat
  regression case based on `(0,0)->(4,3)` and `sample_dist=2`.

### Region OTSU Contract

`code/tracking/imgproc.cpp::region_otsu()` is an auxiliary regional threshold
helper for seed/diagnostic-style scanning. It is not the main maze trace
binarization path.

Required:

- The function must use only the caller-provided rectangle after clamping and
  normalizing coordinate order.
- Reversed x/y bounds must describe the same rectangle as sorted bounds.
- Pixels outside the rectangle must not affect the threshold.
- Do not replace the maze trace path with full-image OTSU. `trace_single()`
  should continue using point-local adaptive thresholding through `calc_th()`.

Background:

- Calvariaa PR #6 changed RT1064 `getOSTUThreshold()` from a full-image-style
  interface to a regional interface. Keep this project on the regional helper
  contract.

Test:

- `code/test/line_trace_contract_test.cpp` must keep the region OTSU regression
  cases for constant rectangle, reversed bounds, and bimodal rectangle.

### Tracking Ring Entrance Contract

The active ring entrance contract is RT1064 `circle.c::check_circle()`:

- `RING_KIND_LEFT` enters from current-frame `left.l_ok`, no current-frame
  `right.l_ok`, and `boundary_is_straight(&right)`.
- `RING_KIND_RIGHT` enters from no current-frame `left.l_ok`,
  current-frame `right.l_ok`, and `boundary_is_straight(&left)`.
- There is no Unity CD.cpp `AIB/BW` image basis, no `pending` stage, and no
  `ring_times` cross-entry gate in the active chain.
- `BEGIN -> IN -> RUN -> OUT -> END` may keep the current project helpers for
  state continuity and detection-side boundary refresh, but those helpers must
  not publish the current-frame control midline.

Archived, not active:

```text
docs/reference/unity_CD_old.cpp
```

Wrong:

```cpp
const int first = check_ring_like_reference(rt, RING_KIND_NONE);
// Record pending only; set ring.kind only after delayed same-direction confirmation.
```

Correct:

```cpp
if(rt->track.left.l_ok && !rt->track.right.l_ok &&
   boundary_is_straight(&rt->track.right)) {
    rt->ring.kind = RING_KIND_LEFT;
}
```

Reason: Unity CD.cpp is now an archived old reference for comparison only. The
mainline must not keep Unity-only `check_ring/AIB/BW/pending/ring_times` as the
runtime contract after the user explicitly selected the RT1064 chain.

### ATG Circle Auxiliary Point Search

When adding or repairing ATG circle A/B/C auxiliary point searches in
`atg_reference/Project/CODE/circle.c`, use current-frame image evidence from
the existing ATG line-search helpers, inner-hit rays, or bounded local scans:

- The entry state contract is `NONE -> ENTRY -> BEGIN -> RUNNING -> OUT`.
  `NONE` may only confirm A/basic entry evidence. `ENTRY` owns B search.
  `BEGIN` owns C search and must not read A as a current-frame dependency.
- The active fixed point changes exactly once at `ENTRY -> BEGIN`.
  In `ENTRY`, the fixed point is A: `seed_line_x` follows current A while A is
  visible, then holds the last A-derived value when A is objectively lost. On
  `ENTRY -> BEGIN`, clear A, keep the confirmed B, and set
  `seed_line_x = B.x + signed_B_offset`. In `BEGIN`, the fixed point is B:
  B may follow current-frame traced evidence near the B anchor, otherwise the
  last B-derived seed line is held.
- The seed prediction line is only a way to find a line-search seed. It is not
  a control line and not B/C truth. If mirrored opposite-line slope, seed, or
  trace is missing, report an explicit failure reason and reject that point.
- Prefer `findline_lefthand_adaptive()` for left-side boundary tracing and
  `findline_righthand_adaptive()` for right-side boundary tracing when the
  current-frame seed is on the correct side of the boundary for that hand rule.
- If the hand-rule trace immediately terminates, a bounded directional scan
  from the current-frame A/raw point is allowed. Keep it inside the measured
  A/B y window. When the first dark pixel is the near-side line edge, skip that
  local edge width before scanning for the opposite arc, and keep the scan
  inside the口门横向窗口: left circle -> `seed_x + 20 .. seed_x + 45`;
  right circle -> `seed_x - 20 .. seed_x - 45`.
- If a search cannot produce a current-frame hit, trace point, or geometry
  window match, report the failure reason and reject that point. Do not reuse a
  previous A/B/C point or synthesize a line.
- ENTRY latches that suppress an abort window must represent evidence that can
  advance the same state machine. For example, if B is found but does not pass
  the ready gate used by `circle_B_streak`, clear both the B-seen latch and the
  streak; a non-ready B candidate must not block `no_b_window`.
- Keep the final accept gate geometric and local, for example A-to-B distance,
  opposite-arc x expansion, y window, and trace jump checks.
- C must be confirmed from a traced point list with a sharp/angle criterion
  such as `local_angle_points()` plus `nms_angle()` or a local three-point
  angle. Do not accept C from a single raw-row lateral jump.
- When `circle_type != CIRCLE_NONE`, circle owns the ATG element frame. Clear
  competing `cross_type` claim flags before `select_work_line()` runs, because
  `CROSS_IN` and `CROSS_HALF` are also farline selection modes there. A
  scheduler early-return alone does not prevent stale cross state from stealing
  the selected line.

Wrong:

```c
for(int y = start_y; y > stop_y; y--) {
    for(int x = seed_x; x >= x_limit; x--) {
        if(is_dark(x, y)) { best = point(x, y); break; }
    }
}
```

Correct:

```c
for(int y = y_max; y >= y_min; y--) {
    for(int x = a_raw_x + 20; x <= a_raw_x + 45; x++) {
        if(is_current_frame_dark(x, y)) {
            // Pick B from current-frame hits inside the A/B geometry window.
            break;
        }
    }
}
```

Reason: Circle inner boundaries can be diagonal in the raw image. The B search
must stay tied to current-frame A/ray evidence, but it must not let the
near-side line edge mask the opposite arc point. Skip only the local edge width,
then reject missing geometry explicitly instead of reusing stale points.

---

## Testing Requirements

<!-- What level of testing is expected -->

- Tracking/ring changes must pass `git diff --check`, `bash code/test.sh --host`, and `bash code/test.sh`.
- If report or replay fields change, run at least one host `--analyze` or `--replay` smoke to confirm formatted output still prints correctly.
- For cross/ring/mainline/boundary/imgproc behavior changes, run at least one
  targeted diagnostic analyze or replay that covers the changed state path.
- If real replay images cannot hit an internal tracking contract, a host-only
  whitebox test is allowed only when it calls the current owner code directly,
  is wired into `code/test.sh --host`, is excluded from cross-compile targets,
  and records why this is test coverage rather than a runtime fallback.

---

## Code Review Checklist

<!-- What reviewers should check -->

- [ ] Was the reference version checked before the behavior changed?
- [ ] Is the edit the smallest direct owner of the bug?
- [ ] Are thresholds and state transitions backed by evidence?
- [ ] Is there no stale-midline or stale-boundary fallback?
- [ ] Did the audit cover reference, current implementation, git regression,
      and Trellis/check-gate roles?
- [ ] If the frame is single-side/no-opposite-anchor, did the review avoid
      pretending that a zero-assumption identity proof exists?
- [ ] If diagnostics changed, can every new field be traced to a current-frame
      fact, with no branch-condition or output changes?
- [ ] Is there a change rationale table with reference behavior, current
      reasoning, threshold/hardware notes, and validation?
- [ ] Were `git diff --check`, host test, device-oriented test, and targeted
      diagnostics run or explicitly blocked?
