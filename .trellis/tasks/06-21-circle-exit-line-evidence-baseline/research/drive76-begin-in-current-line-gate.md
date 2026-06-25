# drive76 BEGIN to IN Current-Line Gate

## Symptom

`drive76` failed before `CIRCLE_LEFT_OUT`: it stalled in `CIRCLE_LEFT_RUNNING`.
The visible "early turn" was caused by entering `CIRCLE_LEFT_IN` while the
current left line was still long.

## Evidence

Successful baseline `drive42`:

```text
prev frame=278 circle=CIRCLE_LEFT_BEGIN near=0/124 raw=0/105 sel=124/125 dist=2010 guide=2.06
next frame=279 circle=CIRCLE_LEFT_IN    near=0/124 raw=0/105 sel=92/17  dist=0    guide=37.36
```

Failed `drive76`:

```text
prev frame=426 circle=CIRCLE_LEFT_BEGIN near=24/124 raw=72/105 sel=124/126 dist=1980 guide=-0.99
next frame=430 circle=CIRCLE_LEFT_IN    near=23/124 raw=72/105 sel=92/17  dist=0    guide=37.36
```

`drive76` had a historical `none_left_line` event, but the current frame still
had a long left line. The previous implementation allowed that stale event plus
distance to trigger fixed-line `CIRCLE_LEFT_IN`.

## Change Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `atg_reference/Project/CODE/circle.c` legacy comment keeps `rpts0s_num < circle_in_length` in the left `BEGIN -> IN` gate. | Current port had weakened that gate to `none_left_line >= 2 && distance/gyro`, so a past left-line loss could trigger fixed IN even after the current left line returned long. | `run_circle()` now requires `rpts0s_num < circle_in_length` for both left `entry_distance` and `entry_gyro`. | `drive76` entered IN with `raw L=72`, while `drive42` entered with `raw L=0`; the fixed IN line should start only when current inner-left evidence is already short. | This rejects a bad current frame. It does not reuse stale geometry, does not change fixed anchors, does not change `600/2000/2500/3550/16000`, and leaves failure visible if the current line evidence never becomes short. |

