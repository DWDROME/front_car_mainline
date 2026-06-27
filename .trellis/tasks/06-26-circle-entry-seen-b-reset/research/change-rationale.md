# Change Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| Active mainline is `atg_reference/Project/CODE/circle.c`: `ENTRY` owns B search; `BEGIN` starts only after B is confirmed for `CIRCLE_B_CONFIRM_FRAMES`; failed point searches must reject/report current-frame evidence instead of reusing stale points. | `run_circle_entry()` already cleared `circle_entry_seen_B[side]` when `b_ret != 1`, but kept it true when `b_ret == 1` and `circle_B_search_ready == 0` while `circle_B_streak` was reset. That left a non-ready B candidate able to suppress `no_b_window`. | In `run_circle_entry()`, set `circle_entry_seen_B[side] = 1` only when `b_ret == 1 && circle_B_search_ready`; clear it when `b_ret == 1` but not ready. | `circle_entry_seen_B` is used as the guard for "we have usable B evidence"; it must stay synchronized with the B confirmation streak. A non-ready B cannot advance to BEGIN and should not prevent ENTRY abort when A is near/lost. | The edit rejects a non-ready current-frame B candidate by clearing the latch and streak. It does not reuse previous B geometry, widen thresholds, synthesize a point, or add a fallback path. |

## Verification

* `git diff --check` passed.
* `bash code/test.sh --host` passed and rebuilt `circle.c`.
* `bash code/test.sh` passed and rebuilt `circle.c`.
* No circle image frame was available for `front_car_mainline --analyze` or
  `--replay`; existing `logs/live-circle/*.log` files are text logs from prior
  runs and cannot execute this new binary path.
