# Stage 3 Cleanup And Rationale

## What Stage 3 Means Here

Stage 3 is cleanup and documentation after the first implementation slice. It
does not mean the circle behavior is field-proven.

The current code has passed local host/cross build in the previous handoff, but
right-circle behavior still needs live evidence. Treat the next drive log as
the source of truth.

## Cleanup Performed

* Added an explicit selected-line-source accessor:
  `atg_reference_selected_line_source()`.
* Added `src=<selected source>` to live frame output so the test PRD can decide
  whether right-circle bias is fixed-line geometry, natural-line switching, or
  no-line output.
* Removed large commented-out legacy far-line splice blocks from
  `build_circle_spliced_lines()`. The active selected-line path is the
  fixed outside-line half-width path; far-line evidence remains diagnostic.
* Unified circle stall reset through `reset_circle_to_none()` so stall reset
  and idle-BEGIN reset cannot silently diverge.
* Removed dead commented `Half_check` circle-entry shortcuts. `Half_check`
  owns `CROSS_HALF`; circle entry is owned by `check_circle()` with vote and
  re-entry suppression.
* Kept and documented `truncate_cross_half_candidate_near_lines()`: when
  current-frame near L + far L evidence looks like an unclaimed `CROSS_HALF`
  candidate, truncate that near line before normal line selection so the bent
  corner segment does not leak into ordinary tracking.

## Change Rationale Table

| Reference behavior | Current difference | Change | Reason | Not a fallback evidence |
| --- | --- | --- | --- | --- |
| Joshua uses visual evidence to decide phase and recommends outside-line half-width control instead of fragile corner-only repair. | Current ATG/IPM path already has fixed outside-line half-width helpers, but selected-line source was maintained only internally. | Expose `atg_reference_selected_line_source()` and print `src=...` in live frame logs. | The test PRD requires selected source to distinguish fixed-line geometry from natural-line switching. | Diagnostic-only: no selected line, guide, state, or control output changes. |
| ATG active circle selected line is now fixed outside-line half-width for `IN/RUNNING/OUT` when the natural line is not ready. | `reference_step.c` still carried full commented legacy far-line splice code, making it look like far-line was still an active selected output. | Remove the commented splice bodies and keep the active half-width path. | Reduces future owner confusion: far-line remains evidence for phase gates, not the selected control line. | No behavior change: removed comments only. |
| Port-layer circle reset must restore the same state set for stall and idle-BEGIN reset. | `exit_circle_after_stall()` duplicated most of `reset_circle_to_none()` and could drift. | Route stall reset through `reset_circle_to_none()`. | One reset owner is easier to audit and preserves the same re-entry suppression path. | Does not fabricate geometry; still resets only after 30 active-circle frames without selected line. |
| Circle entry is owned by `check_circle()` in the active mainline. | `Half_check.c` contained dead commented shortcuts that directly assigned `CIRCLE_*_BEGIN`, bypassing vote and suppression. | Remove dead shortcut blocks, leave a short owner comment. | Prevents future cleanup from restoring the wrong entry owner. | No behavior change: the code was already commented out. |
| ATG `Half_check` owns `CROSS_HALF` when near L and far L evidence agree. | If `check_Half()` does not formally claim the element, the same bent near segment could still flow into normal selected-line choice. | Keep `truncate_cross_half_candidate_near_lines()` after element checks and before selected-line choice. | Prevents an unclaimed cross-half candidate from being treated as ordinary lane geometry. | Current-frame evidence only: it truncates when near L + far L are present and no element is active; it does not reuse stale geometry or guess an opposite side. |

## Live Validation Still Required

Next right-circle live run should answer:

1. Does `src` remain `circle_*_fixed_left` during right `IN/RUNNING/OUT`?
2. If yes, does guide trend still point the car inward?
3. Does `RUNNING -> OUT` transition report `reason=vision_lpt`, `gyro`, or
   `distance`?
4. Does selected line stay non-empty through at least 5-10 consecutive circle
   frames?
5. Does left circle still follow its previous working path?

Recommended command:

```bash
FRONT_CAR_CIRCLE_CAL_LOG=1 \
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive177 18
```

Then review:

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive177
```

Do not record this implementation as behavior-proven until live evidence exists.
