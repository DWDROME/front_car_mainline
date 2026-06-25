# drive77 IN to RUNNING Current-Right Gate

## Symptom

`drive77` still looked like "early circle entry", but the state evidence shows
`BEGIN -> IN` matched the successful drive42 entry. The bad handoff was
`CIRCLE_LEFT_IN -> CIRCLE_LEFT_RUNNING`: gyro reached 600 while the current
right line was absent, so `TRACK_RIGHT` selected no line and the car stopped.

## Evidence

Successful baseline `drive42`:

```text
BEGIN -> IN prev: near=0/124 raw=0/105 dist=2010
IN -> RUNNING prev: near=0/44 raw=0/111 dist=954 guide=37.36
RUNNING next usable: sel=46/41 guide=32.46
```

Failed `drive77`:

```text
BEGIN -> IN prev: near=0/124 raw=0/105 dist=2008
IN -> RUNNING prev: near=1/0 raw=1/0 dist=938 guide=37.36
RUNNING next: sel=0/0 guide=0.00 duty=0/0
```

So the first gate was not early relative to drive42. The second gate handed
control to `TRACK_RIGHT` when `rpts1s_num == 0`.

## Change Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| The legacy left `IN -> RUNNING` comment requires current right-line evidence: `rpts1s_num > 25` in the gyro/distance paths. | Current port allowed gyro/distance alone to switch to `CIRCLE_LEFT_RUNNING`, even when current right-line evidence was empty. | `run_circle()` now requires `rpts1s_num > 25 && rpts1s_num <= circle_in_length` before either gyro or distance can switch left `IN -> RUNNING`. | `drive77` switched with `raw R=0`, then `TRACK_RIGHT` selected `sel=0/0`; `drive42` switched with current right evidence around 44-46 points. The upper bound rejects the long straight-edge case that previously produced too-inner RUNNING entries. | This rejects a bad current frame. It does not reuse stale geometry, hold previous guide, change fixed anchors, change speed, or change `600/2000/2500/3550/16000`; if current right evidence never becomes ready, failure remains visible in `CIRCLE_LEFT_IN`. |
