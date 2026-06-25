# drive84

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive84-front_car_circle_drive84.log
- remote_log: /tmp/front_car_circle_drive84.log
- started_at: 2026-06-22T06:05:22+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive84 6
```

3074 /tmp/front_car_circle_drive84.log
frame=712 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=7/0 raw=48/0 sel=7/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=148.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(59,95) md=34/1/50 cxcy=84.0,119.6 guide=27.49 atg=-60.0/-60.0/-60.0 pure=10.52/10.52 yaw=-1649 cmd=-1849 actual=-96 signed=0 rps=7534/2466:2779/2472 duty=23/7 pwm=PWM2:23/PWM1:7 motor=2:23/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=7/0 centerNum=7/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:29.46@55,92 dx=-28.7 idx=0/1 dist=40/50 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:28.69@57,94 dx=-26.8 idx=0/16 dist=32/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=66,118 r=-1,-1
ATGSeedDiag: seed=1@45,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(148.0) imip=0/6 pass=11010 acc=-1 ipm=68.7,111.8 inv=46.4,91.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=713 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/1 raw=2/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=10.52/10.52 yaw=0 cmd=0 actual=-383 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@16,108/1@141,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=714 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/0 raw=43/0 sel=6/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=143.4/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(59,95) md=34/1/47 cxcy=84.0,119.6 guide=27.49 atg=-60.0/-60.0/-60.0 pure=10.49/10.49 yaw=-1649 cmd=-1849 actual=-434 signed=0 rps=7534/2466:3113/2655 duty=22/7 pwm=PWM2:22/PWM1:7 motor=2:22/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/0 centerNum=6/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:29.50@55,92 dx=-28.7 idx=0/1 dist=40/48 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:28.73@57,94 dx=-26.8 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=66,118 r=-1,-1
ATGSeedDiag: seed=1@45,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(143.4) imip=0/5 pass=11010 acc=-1 ipm=69.6,113.9 inv=46.9,97.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=715 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/0 raw=41/0 sel=6/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=147.4/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(57,97) md=34/1/46 cxcy=84.0,119.6 guide=30.35 atg=-60.0/-60.0/-60.0 pure=11.21/11.21 yaw=-1821 cmd=-2021 actual=-462 signed=0 rps=7770/2230:2940/2508 duty=24/6 pwm=PWM2:24/PWM1:6 motor=2:24/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/0 centerNum=6/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:32.09@53,94 dx=-30.8 idx=0/1 dist=40/48 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:31.09@56,96 dx=-28.4 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=66,119 r=-1,-1
ATGSeedDiag: seed=1@45,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(147.4) imip=0/5 pass=11010 acc=-1 ipm=69.7,113.9 inv=47.1,97.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=716 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/0 raw=38/0 sel=5/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=132.4/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(63,92) md=33/1/41 cxcy=84.0,119.6 guide=22.91 atg=-60.0/-60.0/-60.0 pure=8.65/8.65 yaw=-1374 cmd=-1574 actual=-428 signed=0 rps=7158/2842:3423/2688 duty=21/8 pwm=PWM2:21/PWM1:8 motor=2:21/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:23.30@61,89 dx=-23.0 idx=0/1 dist=38/44 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:23.07@62,90 dx=-22.5 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=66,117 r=-1,-1
ATGSeedDiag: seed=1@45,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(132.4) imip=0/4 pass=11110 acc=-1 ipm=69.5,113.9 inv=46.7,98.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=717 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=12/0 sel=2/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=8.65/8.65 yaw=0 cmd=0 actual=-649 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@39,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=718 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=8.65/8.65 yaw=0 cmd=0 actual=-692 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@11,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=719 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/0 raw=32/0 sel=4/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=110.3/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(64,91) md=33/1/39 cxcy=84.0,119.6 guide=22.63 atg=-60.0/-60.0/-60.0 pure=8.17/8.17 yaw=-1358 cmd=-1558 actual=-620 signed=0 rps=7135/2865:3255/2794 duty=21/8 pwm=PWM2:21/PWM1:8 motor=2:21/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.45@62,89 dx=-22.2 idx=0/1 dist=38/42 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.32@62,90 dx=-21.8 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=66,117 r=-1,-1
ATGSeedDiag: seed=1@46,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(110.3) imip=0/3 pass=11110 acc=-1 ipm=66.5,114.9 inv=39.1,101.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=720 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/0 raw=31/0 sel=4/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=107.3/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(60,94) md=34/1/41 cxcy=84.0,119.6 guide=26.02 atg=-60.0/-60.0/-60.0 pure=9.11/9.11 yaw=-1561 cmd=-1761 actual=-518 signed=0 rps=7414/2586:3428/3030 duty=22/7 pwm=PWM2:22/PWM1:7 motor=2:22/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:27.60@57,91 dx=-27.0 idx=0/1 dist=39/43 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:27.00@58,93 dx=-25.5 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=66,118 r=-1,-1
ATGSeedDiag: seed=1@46,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(107.3) imip=0/3 pass=11110 acc=-1 ipm=68.5,114.5 inv=43.9,99.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=721 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=6/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.11/9.11 yaw=0 cmd=0 actual=-477 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@8,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=722 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=7/0 sel=2/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(63,92) md=33/1/33 cxcy=84.0,119.6 guide=21.66 atg=-60.0/-60.0/-60.0 pure=7.50/7.50 yaw=-1299 cmd=-1499 actual=-712 signed=0 rps=7055/2945:3554/2686 duty=20/8 pwm=PWM2:20/PWM1:8 motor=2:20/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.67@63,92 dx=-21.2 idx=0/1 dist=35/35 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.67@63,92 dx=-21.2 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=51,115 r=-1,-1
ATGSeedDiag: seed=1@7,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=723 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/0 raw=26/0 sel=3/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=72.4/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(62,93) md=33/1/35 cxcy=84.0,119.6 guide=22.94 atg=-60.0/-60.0/-60.0 pure=7.68/7.68 yaw=-1376 cmd=-1576 actual=-732 signed=0 rps=7160/2840:3577/2823 duty=21/8 pwm=PWM2:21/PWM1:8 motor=2:21/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:24.25@61,91 dx=-23.5 idx=0/1 dist=37/39 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:24.20@61,91 dx=-23.4 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=67,117 r=-1,-1
ATGSeedDiag: seed=1@47,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(72.4) imip=0/2 pass=11110 acc=-1 ipm=68.3,115.5 inv=42.8,102.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=724 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.68/7.68 yaw=0 cmd=0 actual=-747 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@5,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=726 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/0 raw=19/0 sel=3/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=76.5/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(56,99) md=33/1/38 cxcy=84.0,119.6 guide=32.69 atg=-60.0/-60.0/-60.0 pure=10.38/10.38 yaw=-1962 cmd=-2162 actual=-721 signed=0 rps=7962/2038:3038/2686 duty=24/5 pwm=PWM2:24/PWM1:5 motor=2:24/1:5
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:34.52@52,96 dx=-32.2 idx=0/1 dist=40/42 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:33.53@54,98 dx=-29.9 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=67,119 r=-1,-1
ATGSeedDiag: seed=1@48,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(76.5) imip=0/2 pass=11110 acc=-1 ipm=67.9,116.5 inv=40.9,106.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=727 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=13/0 sel=2/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(84,119) ml=(51,108) md=33/1/39 cxcy=84.0,119.6 guide=44.46 atg=-60.0/-60.0/-60.0 pure=13.42/13.42 yaw=-2668 cmd=-2868 actual=-604 signed=0 rps=8930/1070:3259/2899 duty=27/1 pwm=PWM2:27/PWM1:1 motor=2:27/1:1
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:47.10@45,106 dx=-39.5 idx=0/1 dist=42/42 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:44.92@49,108 dx=-35.1 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=67,119 r=-1,-1
ATGSeedDiag: seed=1@44,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=728 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3193 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=13.42/13.42 yaw=0 cmd=0 actual=-805 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T06:05:35+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive84
```
