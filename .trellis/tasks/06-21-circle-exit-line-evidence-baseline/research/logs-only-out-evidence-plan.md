# Logs-Only OUT Evidence Plan

## Problem

`drive15` proved the car reaches `CIRCLE_LEFT_OUT`, then loses selected line for
the stall window:

```text
frame=436 circle=7 sel=51/35
frame=437 circle=7 sel=1/0
frame=438..465 circle=7 sel=0/0 far=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1
ATGCircleStall: circle_type=7 stalled 30 frames without selected line
```

Existing report fields prove the selected output is gone, but they do not
separate these two failure boundaries:

1. `cross_farline_R()` cannot seed/build farline evidence in `CIRCLE_LEFT_OUT`.
2. Farline evidence exists, but port-layer splicing/selection/normalization
   loses it before `rptsn`.

## Implementation

This patch is diagnostic-only. It does not change thresholds, state transitions,
track selection, farline construction, selected-line construction, or control
input.

Added logs under the existing `FRONT_CAR_CIRCLE_CAL_LOG=1` gate:

- `ATGCircleOutEvidence`
  - emitted in `circle.c` immediately after `cross_farline_R()` during
    `CIRCLE_LEFT_OUT`;
  - records ordinary right L point, near right line count, `rptsc1_num`,
    right-lost flag, seed raw point, `far_ipts1_num`, `far_rpts1s_num`,
    far right L point, distance, and heading.

- `ATGCircleSelectEvidence`
  - emitted in `reference_step.c` after `select_work_line()` and
    `normalize_selected_line()`;
  - records selected source, pre-normalize `rpts_num`, post-normalize
    `rptsn_num`, spliced center counts, farline counts, right L point, and
    normalized guide values when `ok=1`.

The task-local review script now includes both events in its first grep block.

## Rationale Table

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `circle.c` calls `cross_farline_R()` in `CIRCLE_LEFT_OUT`; USER layer then uses farline/splicing/selection to construct the exit line. | LS2K port reaches `CIRCLE_LEFT_OUT` but stalls with `sel=0/0`; current logs do not show whether `cross_farline_R()` or selected-line normalization is the failing boundary. | Added `ATGCircleOutEvidence` and `ATGCircleSelectEvidence` logs only. | Need one more live run to classify the failing boundary before a behavior experiment. | No state, threshold, geometry, or control output changed; logs report current-frame evidence and selected-line results only. |

## Next Live Run

Run `drive16` with the standard script:

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh all drive16 18
```

Interpretation:

- If `ATGCircleOutEvidence` shows `far_ipts1=0` / `far_rpts1s=0`, the failure is
  inside `cross_farline_R()` seed/search for OUT.
- If `far_rpts1s>0` but `ATGCircleSelectEvidence source=rptsc0` or `ok=0`, the
  failure is port-layer splicing/selection/normalization.
- If `source=circle_splice_right` and `ok=1` exists briefly then collapses, look
  at the frame trend around the collapse before changing behavior.
