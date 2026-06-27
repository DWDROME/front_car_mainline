# circle ENTRY B seen reset and diagnostics

## Goal

Tighten the circle ENTRY state so a non-confirming or stale B probe cannot keep
ENTRY alive after A disappears or reaches the near window. Also confirm the
BEGIN B-follow diagnostics and the new `imgproc.h` dependency are present.

## What I Already Know

* User review found one medium-risk issue: `circle_entry_seen_B` can outlive a
  failed B confirmation and block the `no_b_window` abort path.
* Current `circle.c` already clears `circle_entry_seen_B[side]` when
  `b_ret != 1`, and already logs B-follow misses with `miss_streak`.
* Current `imgproc.h` declares `findline_lefthand_adaptive`,
  `findline_righthand_adaptive`, `local_angle_points`, and `nms_angle`.
* One remaining gap remains: when `b_ret == 1` but
  `circle_B_search_ready == 0`, `circle_B_streak` is reset while
  `circle_entry_seen_B[side]` still stays true.

## Requirements

* In ENTRY, `circle_entry_seen_B[side]` must only stay true when the current
  frame has ready B evidence that can contribute to `circle_B_streak`.
* When a B probe is absent, invalid, or not ready, both `circle_B_streak` and
  `circle_entry_seen_B[side]` must be cleared so `no_b_window` can abort.
* Preserve the existing immediate abort on `b_ret < 0` / `sharp_far`.
* Preserve the existing BEGIN behavior where B-follow failure keeps the last B
  anchor but logs a miss streak.
* Do not add fallback geometry, mock success paths, or a second B truth source.

## Acceptance Criteria

* [x] `run_circle_entry()` clears `circle_entry_seen_B[side]` whenever
  `circle_B_streak` is reset due to missing or not-ready B evidence.
* [x] `ENTRY -> BEGIN` still requires `circle_B_streak >=
  CIRCLE_B_CONFIRM_FRAMES`, `circle_B_point.found`, and
  `circle_B_search_ready`.
* [x] `ENTRY -> NONE` still immediately aborts on `sharp_far` and aborts on
  `no_b_window` when A is near/lost and no ready B has been seen.
* [x] `circle_follow_B_in_begin()` miss logging includes enough state to debug
  B-follow failures.
* [x] `imgproc.h` declares all functions used by the B/C search helpers.
* [x] Run the narrowest available static/build check, or record why it is not
  available.

## Technical Approach

Treat `circle_entry_seen_B` as a "ready B seen" latch, not merely "any B-like
candidate was found." This keeps it synchronized with `circle_B_streak` and
prevents a non-ready candidate from suppressing the existing `no_b_window`
escape path.

## Out of Scope

* No threshold tuning for A/B/C geometry.
* No changes to RUNNING/OUT behavior.
* No log-format rewrite beyond preserving or tightening the existing diagnostics.
* No changes to `imgproc.c` algorithms.

## Technical Notes

* Target code: `atg_reference/Project/CODE/circle.c`.
* Header dependency: `atg_reference/Project/CODE/imgproc.h`.
* Relevant specs: `.trellis/spec/quality/embedded-tracking-guidelines.md`,
  `.trellis/spec/tracking/critical-audit-guide.md`.
* Rationale and validation notes: `research/change-rationale.md`.
