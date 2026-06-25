# Cross Half Aim Symmetry

## Context

User feedback: angled cross entry is worse on the left path. The left
`CROSS_HALF` branch used `aim_distance = 0.25`, while the right branch used
`0.75`. The source of this asymmetry is not currently remembered or documented.

Joshua's cross reference treats angled entry, angled exit, curve-entry cross,
and mid-cross frames as the same cross class. We are not porting Joshua's raw
row / four-corner implementation here; the current ATG/IPM point-set pipeline
stays in place.

## Change

Keep this as one variable:

* Keep normal double-L `CROSS_BEGIN` at the original `aim_distance = 0.4f`.
* `CROSS_HALF_AIM_DISTANCE = 0.75f` for both left and right `CROSS_HALF`.

This preserves the right-half working value and removes the left-only near
lookahead that likely caused fast reaction / overshoot.

## Rationale Table

| Reference behavior | Current difference | Change | Reason | Not a fallback evidence |
| --- | --- | --- | --- | --- |
| ATG `cross.c::run_cross()` already uses one `aim_distance = 0.4` for normal double-L `CROSS_BEGIN`. Joshua's cross reference says angled entry is still a cross, but its raw-row corner linking is not directly portable to our IPM point-set path. | `CROSS_HALF` used left `0.25` and right `0.75`, making the left path look much nearer and react harder. | Add only `CROSS_HALF_AIM_DISTANCE = 0.75f` and use it for both `Lpt0_found_flag` and `Lpt1_found_flag` branches; leave normal `CROSS_BEGIN` at `0.4f`. | User reports the left path is worse; `0.25` matches the expected symptom of too-near lookahead, while `0.75` is the existing right-half working value. | This only changes the current-frame lookahead distance for an already selected current-frame line. It does not reuse stale geometry, guess the opposite side, or change entry / exit state gates. |

## Validation

Static checks after the patch:

```bash
git diff --check
bash code/test.sh --host
bash code/test.sh
```

Live check should use `.trellis/tasks/06-22-cross-entry-truncation/live_cross_test.sh`.
Compare left and right angled `CROSS_HALF` attempts. If the left path changes
from overshoot to cutting/late response, tune `CROSS_HALF_AIM_DISTANCE` down as
a single variable.
