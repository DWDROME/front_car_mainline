# Circle C Search Phase Gate Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `atg_reference/Project/CODE/circle.c` is the active circle reference in this branch. Entry confirmation already uses A+B in `check_circle()`, while C is searched in `run_circle()` during BEGIN. | BEGIN searched C immediately after B, and B row readiness alone could set `circle_ref_mode = CIRCLE_REF_IN_C` even without confirmed C. | `circle.c:run_circle()` now calls `update_circle_C_search()`; C search is skipped until stable B reaches `CIRCLE_B_ENTER_ROW`, and B row alone no longer promotes `CIRCLE_REF_IN_C`. | User observed B/C can both land on the middle roundabout line and create jumps. Early BEGIN should keep A/B-B reference until the vehicle phase is mature enough to look for C. | No stale point is reused. When the phase is too early, C is explicitly cleared and `C_search=phase_gate` is reported under `FRONT_CAR_CIRCLE_CAL_LOG=1`; only current-frame C evidence after the gate can enter `CIRCLE_REF_IN_C`. |

## Validation

* `git diff --check` passed.
* `bash code/test.sh --host` passed and rebuilt `atg_reference/Project/CODE/circle.c`.
