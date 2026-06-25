# drive168

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 12
- local_log: logs/live-circle/20260621-drive168-front_car_circle_drive168.log
- remote_log: /tmp/front_car_circle_drive168.log
- started_at: 2026-06-22T16:19:43+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive168 12
```

5934 /tmp/front_car_circle_drive168.log
frame=1319 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=10/0 sel=2/14 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(84,119) ml=(74,91) md=28/0/28 cxcy=84.0,119.6 guide=10.98 atg=-41.0/-16.0/-16.0 pure=4.15/4.15 yaw=-878 cmd=-1278 actual=119 signed=0 rps=6166/2662:1251/1404 duty=20/9 pwm=PWM2:20/PWM1:9 motor=2:20/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/14 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:11.61@73,90 dx=-10.7 idx=0/1 dist=31/31 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:11.47@74,91 dx=-10.5 idx=0/13 dist=26/26 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=67,116 r=-1,-1
ATGSeedDiag: seed=1@47,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1320 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=3/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-41.0/-16.0/-16.0 pure=4.15/4.15 yaw=0 cmd=0 actual=137 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@46,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1321 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=11/0 sel=2/14 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(84,119) ml=(73,92) md=27/0/27 cxcy=84.0,119.6 guide=12.28 atg=-49.0/-19.0/-19.0 pure=4.52/4.52 yaw=-982 cmd=-1382 actual=195 signed=0 rps=6239/2451:2014/1495 duty=19/8 pwm=PWM2:19/PWM1:8 motor=2:19/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/14 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:12.70@72,91 dx=-11.8 idx=0/1 dist=31/31 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:12.49@73,92 dx=-11.3 idx=0/13 dist=26/26 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=66,116 r=-1,-1
ATGSeedDiag: seed=1@44,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1322 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=3/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-49.0/-19.0/-19.0 pure=4.52/4.52 yaw=0 cmd=0 actual=-213 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@43,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1323 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-49.0/-19.0/-19.0 pure=4.52/4.52 yaw=0 cmd=0 actual=-115 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@42,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1325 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-49.0/-19.0/-19.0 pure=4.52/4.52 yaw=0 cmd=0 actual=-92 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@38,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1339 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-49.0/-19.0/-19.0 pure=4.52/4.52 yaw=0 cmd=0 actual=-6 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@24,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1340 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=5/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-49.0/-19.0/-19.0 pure=4.52/4.52 yaw=0 cmd=0 actual=-17 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@23,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1352 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=9/0 sel=2/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(84,119) ml=(63,92) md=33/0/33 cxcy=84.0,119.6 guide=22.54 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=-1803 cmd=-2203 actual=-93 signed=0 rps=6817/779:641/519 duty=23/2 pwm=PWM2:23/PWM1:2 motor=2:23/1:2
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/16 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:23.31@62,91 dx=-22.5 idx=0/1 dist=37/37 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.80@63,92 dx=-21.3 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=55,116 r=-1,-1
ATGSeedDiag: seed=1@17,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1353 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=3/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=0 cmd=0 actual=-36 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@17,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1356 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=0 cmd=0 actual=-206 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@16,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1357 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=0 cmd=0 actual=-43 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@15,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1438 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=0 cmd=0 actual=-1 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@10,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1439 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=0 cmd=0 actual=0 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@9,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1494 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=0 cmd=0 actual=0 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@10,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=1495 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=4/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2875 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=0 cmd=0 actual=-1 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@10,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T16:20:02+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive168
```
