# drive113

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive113-front_car_circle_drive113.log
- remote_log: /tmp/front_car_circle_drive113.log
- started_at: 2026-06-22T07:26:43+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive113 6
```

3405 /tmp/front_car_circle_drive113.log
frame=673 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/0 raw=3/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=23.0/9.0/9.0 pure=-2.97/-2.97 yaw=0 cmd=0 actual=-353 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@68,108/1@155,86 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=674 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=5/1 raw=22/7 sel=5/15 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.8/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(84,119) ml=(84,90) md=31/0/31 cxcy=84.0,119.6 guide=-2.19 atg=0.0/0.0/0.0 pure=-0.04/-0.04 yaw=56 cmd=255 actual=-143 signed=0 rps=4651/5349:6927/7233 duty=8/12 pwm=PWM2:8/PWM1:12 motor=2:8/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/1 centerNum=5/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:1.19@83,89 dx=-1.1 idx=0/4 dist=33/33 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-0.11@84,90 dx=0.1 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,112 r=-1,-1
ATGSeedDiag: seed=1@65,108/1@155,85 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(2.8) imip=0/4 pass=10111 acc=-1 ipm=71.5,112.7 inv=51.6,94.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=675 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/0 raw=5/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=-0.04/-0.04 yaw=0 cmd=0 actual=-46 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@62,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=676 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=3/0 raw=12/0 sel=3/13 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.4/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(84,119) ml=(85,92) md=27/0/27 cxcy=84.0,119.6 guide=-1.10 atg=0.0/0.0/0.0 pure=-0.53/-0.53 yaw=28 cmd=75 actual=-19 signed=0 rps=4897/5103:6073/6805 duty=10/12 pwm=PWM2:10/PWM1:12 motor=2:10/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-0.22@84,92 dx=0.2 idx=0/2 dist=29/29 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-1.39@85,92 dx=1.2 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=71,114 r=-1,-1
ATGSeedDiag: seed=1@60,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(0.4) imip=0/2 pass=10111 acc=-1 ipm=73.3,115.3 inv=54.3,102.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=677 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=-0.53/-0.53 yaw=0 cmd=0 actual=24 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@57,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=679 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=2/0 raw=10/0 sel=2/12 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(84,119) ml=(81,94) md=25/0/25 cxcy=84.0,119.6 guide=3.56 atg=-4.0/-1.0/-1.0 pure=1.44/1.44 yaw=-91 cmd=-127 actual=-54 signed=0 rps=5175/4825:6317/6195 duty=10/12 pwm=PWM2:10/PWM1:12 motor=2:10/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.78@81,92 dx=-3.4 idx=0/1 dist=28/28 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:3.63@81,94 dx=-3.1 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,115 r=-1,-1
ATGSeedDiag: seed=1@50,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=680 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-4.0/-1.0/-1.0 pure=1.44/1.44 yaw=0 cmd=0 actual=28 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@47,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=681 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/0 raw=170/0 sel=11/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=4.6/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(84,119) ml=(71,89) md=32/1/45 cxcy=84.0,119.6 guide=14.52 atg=-60.0/-60.0/-60.0 pure=6.77/6.77 yaw=-871 cmd=-1071 actual=240 signed=0 rps=6468/3532:6490/5920 duty=15/7 pwm=PWM2:15/PWM1:7 motor=2:15/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/0 centerNum=11/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:12.77@72,89 dx=-12.1 idx=0/3 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:15.44@69,88 dx=-15.1 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=47,107 r=-1,-1
ATGSeedDiag: seed=1@43,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(4.6) imip=0/10 pass=10111 acc=-1 ipm=48.9,108.5 inv=10.2,84.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=682 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=6.77/6.77 yaw=0 cmd=0 actual=309 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@40,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=687 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=170/0 sel=2/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(84,119) ml=(64,91) md=33/1/33 cxcy=84.0,119.6 guide=20.62 atg=-60.0/-55.0/-55.0 pure=6.95/6.95 yaw=-1237 cmd=-1437 actual=36 signed=0 rps=6970/3030:4584/5642 duty=19/5 pwm=PWM2:19/PWM1:5 motor=2:19/1:5
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:21.04@64,91 dx=-20.0 idx=0/1 dist=35/35 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.98@64,91 dx=-19.9 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=56,115 r=-1,-1
ATGSeedDiag: seed=1@19,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=688 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/0 raw=16/0 sel=4/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.2/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(84,119) ml=(63,92) md=33/1/38 cxcy=84.0,119.6 guide=22.39 atg=-60.0/-60.0/-60.0 pure=7.73/7.73 yaw=-1343 cmd=-1543 actual=56 signed=0 rps=7115/2885:5161/5903 duty=18/4 pwm=PWM2:18/PWM1:4 motor=2:18/1:4
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.25@63,91 dx=-21.2 idx=0/1 dist=36/40 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:23.47@61,90 dx=-22.7 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=50,114 r=-1,-1
ATGSeedDiag: seed=1@16,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(3.2) imip=0/3 pass=10111 acc=-1 ipm=54.4,115.7 inv=10.3,104.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=689 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=8/0 sel=2/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(84,119) ml=(62,93) md=33/1/36 cxcy=84.0,119.6 guide=23.51 atg=-60.0/-60.0/-60.0 pure=7.93/7.93 yaw=-1411 cmd=-1611 actual=93 signed=0 rps=7207/2793:5307/5502 duty=19/4 pwm=PWM2:19/PWM1:4 motor=2:19/1:4
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:25.23@59,91 dx=-24.6 idx=0/1 dist=38/38 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:25.00@60,91 dx=-24.0 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=52,116 r=-1,-1
ATGSeedDiag: seed=1@11,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=690 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=5/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.93/7.93 yaw=0 cmd=0 actual=225 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@6,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=691 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.93/7.93 yaw=0 cmd=0 actual=166 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=696 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.93/7.93 yaw=0 cmd=0 actual=156 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@12,101/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=697 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2520 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.93/7.93 yaw=0 cmd=0 actual=355 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T07:26:57+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive113
```
