# drive15 Baseline Summary

## Run Metadata

- local_log: `logs/live-circle/20260621-drive15-front_car_circle_drive15.log`
- commit: `51cfb97 chore(report): add circle corner diagnostics`
- run_type: baseline with circle diagnostics
- classification: OUT far-line / selected-line construction issue

## Build And Upload

Reported by live run operator:

- `code/build-host` build passed.
- `code/build` build passed.
- `config_parsing_test` passed.
- `options_parsing_test` passed.
- Remote binary replacement and PID start/stop succeeded.

## Circle State Flow

Observed directly in the log:

```text
22:ATGCircleCal: from=CIRCLE_NONE to=CIRCLE_LEFT_BEGIN reason=entry_vote heading_deg10=0 dist=0
1033:ATGCircleCal: from=CIRCLE_LEFT_BEGIN to=CIRCLE_LEFT_IN reason=entry_distance heading_deg10=3 dist=2003
1220:ATGCircleCal: from=CIRCLE_LEFT_IN to=CIRCLE_LEFT_RUNNING reason=gyro heading_deg10=603 dist=695
2315:ATGCircleCal: from=CIRCLE_LEFT_RUNNING to=CIRCLE_LEFT_OUT reason=gyro heading_deg10=2007 dist=2661
2448:ATGCircleStall: circle_type=7 stalled 30 frames without selected line, reset to NONE
```

Result:

```text
CIRCLE_NONE -> CIRCLE_LEFT_BEGIN -> CIRCLE_LEFT_IN -> CIRCLE_LEFT_RUNNING -> CIRCLE_LEFT_OUT -> ATGCircleStall -> CIRCLE_NONE
```

## Entry Candidate Check

The issue is not missing circle entry.

- left_entry_candidates: 48
- right_entry_candidates: 1
- entry did trigger at log line 22.

## OUT Failure Window

The first `CIRCLE_LEFT_OUT` frame still has a selected line, then the selected
line collapses immediately.

```text
2316 frame=436 circle=7 sel=51/35 far=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 guide=34.25 yaw=-2055 road=2 m0=(84,119) near=1/51 raw=3/141
2322 frame=437 circle=7 sel=1/0   far=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 guide=0.00  yaw=0     road=2 m0=(-1,-1) near=1/51 raw=2/141
2328 frame=438 circle=7 sel=0/0   far=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 guide=0.00  yaw=0     road=2 m0=(-1,-1) near=0/51 raw=0/140
```

From frame 438 through the stall reset, the trend is continuous:

- `circle=7(CIRCLE_LEFT_OUT)`
- `sel=0/0`
- `far=0/0`
- `l=0@-1/0@-1`
- `far_l=0@-1/0@-1`
- `m0=(-1,-1)`
- `guide=0.00`
- `yaw=0`

Last OUT frames before stall:

```text
2388 frame=449 circle=7 sel=0/0 near=0/70 raw=0/170
2394 frame=450 circle=7 sel=0/0 near=0/69 raw=0/170
2400 frame=454 circle=7 sel=0/0 near=0/68 raw=0/170
2406 frame=455 circle=7 sel=0/0 near=0/69 raw=0/170
2412 frame=457 circle=7 sel=0/0 near=0/67 raw=0/170
2418 frame=458 circle=7 sel=0/0 near=0/67 raw=0/170
2424 frame=459 circle=7 sel=0/0 near=0/69 raw=0/170
2430 frame=460 circle=7 sel=0/0 near=0/44 raw=0/127
2436 frame=464 circle=7 sel=0/0 near=0/42 raw=0/124
2442 frame=465 circle=7 sel=0/0 near=0/41 raw=0/123
2448 ATGCircleStall: circle_type=7 stalled 30 frames without selected line, reset to NONE
```

## Post-Reset Observation

After `ATGCircleStall` resets to `CIRCLE_NONE`, ordinary-road logic starts
publishing large left-turn guide/yaw from a bad recovery pose:

```text
2449 frame=466 circle=0 sel=0/0 guide=0.00  yaw=0     road=0
2454 frame=467 circle=0 sel=40/31 guide=47.17 yaw=-2830 road=0
2459 frame=468 circle=0 sel=40/32 guide=47.66 yaw=-2860 road=0
2464 frame=469 circle=0 sel=39/31 guide=48.65 yaw=-2919 road=0
```

This supports the rule that early reset/ordinary-road takeover cannot be used
as the exit fix.

## Conclusion

drive15 proves the baseline enters the circle and reaches `CIRCLE_LEFT_OUT`.
The failure is the OUT-stage line evidence path: `LEFT_OUT` has no far line,
no L-point evidence, and loses selected line for a sustained 30-frame window.

The next code change, if any, must be logs-only. It should distinguish whether
`cross_farline_R()` fails to seed/build farline evidence, or whether selected
line normalization discards available evidence after OUT begins.
