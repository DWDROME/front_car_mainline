# Behavior Change Rationale

## Audit Notes

* `fast_context_search` is not available in this Codex tool surface; local discovery used `rg`, direct file reads, `git show`, and build output.
* No sub-agent dispatch tool is available in this session, so the four audit roles were covered in the main session:
  * reference/history: `atg_reference/Project/CODE/circle.old`, recent `git show d236990`, `git show 4111488`;
  * current implementation: `atg_reference/Project/CODE/circle.c`, `circle.h`, `atg_reference/port/reference_step.c`;
  * Trellis/spec gate: `.trellis/spec/tracking/critical-audit-guide.md`, `.trellis/spec/quality/embedded-tracking-guidelines.md`, `.trellis/spec/quality/refactoring-and-diagnostic-discipline.md`;
  * validation: `git diff --check`, `bash code/test.sh --host`, `bash code/test.sh`.
* Targeted replay/analyze is blocked: the repository has live text logs and documentation screenshots, but no relevant `RAW_W x RAW_H` image frame/sequence for `front_car_mainline --analyze` or `--replay`.

## Fixed Rationale Table

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| Active ATG path `circle.old::check_circle()` entered `CIRCLE_*_BEGIN` after entry votes from A+B double-breakpoint evidence. No direct ATG `ENTRY` state exists. | Current rewritten `circle.c::check_circle()` still searched B in `NONE` and jumped straight to `BEGIN`. | Added `CIRCLE_LEFT_ENTRY` / `CIRCLE_RIGHT_ENTRY`; `NONE` now only confirms A/basic and latches first A. | PRD requires separating suspected entry from confirmed B, so `BEGIN` no longer means "A entry maybe exists". | `NONE` no longer accepts hidden B evidence; if A/basic disappears before votes, pending A is cleared. |
| Existing B search used raw A-relative bounded scanning after inner-hit evidence. | Current `circle_find_B()` was still a raw window scan and `BEGIN` called it every frame from current A. | Replaced B search with `seed_line_x + mirrored opposite-line slope -> seed -> findline_*_adaptive() -> trace extreme`. | B must be current-frame boundary evidence on a traced arc, not a raw row/window hit. | Missing slope, seed, trace, legal extreme, or sharp-far conflict returns explicit failure reasons; no previous B is accepted as current B. |
| Existing C search was gated by stable B and B raw-y phase, but used a raw jump scan from B. | Current `circle_find_C()` accepted a single-row jump, not a traced sharp point. | Replaced C search with B-derived seed line, basic line trace, `local_angle_points()` + `nms_angle()` sharp-point selection. | C is semantically A-like sharp geometry after B, so it must be confirmed from a point list. | C is cleared when phase-gated or not found; `CIRCLE_REF_IN_C` is set only after consecutive current-frame C confirmations. |
| No direct reference for "current fixed point" abstraction; old code repeatedly read A in BEGIN. | `BEGIN` depended on current A and reset B streak from fresh A-based search. | ENTRY owns A seed-line updates; `ENTRY -> BEGIN` clears A, stores B, and sets `seed_line_x = B.x + signed offset`; BEGIN uses B only and locally follows B when visible. | This encodes the design invariant: ENTRY fixed point is A, BEGIN fixed point is B. | B follow only updates from current-frame traced evidence near the B anchor; if it fails, the defined seed-line hold is reported by logs and does not create new state evidence. |

## Validation

* `git diff --check` passed.
* `bash code/test.sh --host` passed.
* `bash code/test.sh` passed.
* Targeted circle replay/analyze not run because no suitable raw image input is present in the repository.
