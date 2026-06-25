# drive110

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive110-front_car_circle_drive110.log
- remote_log: /tmp/front_car_circle_drive110.log
- started_at: 2026-06-22T07:22:47+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive110 6
```

1364 /tmp/front_car_circle_drive110.log
frame=260 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=10/0 raw=57/0 sel=10/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=22.7/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(84,119) ml=(66,90) md=33/1/47 cxcy=84.0,119.6 guide=18.40 atg=-60.0/-60.0/-60.0 pure=9.12/9.12 yaw=-1104 cmd=-1304 actual=-84 signed=0 rps=6788/3212:1857/1653 duty=22/11 pwm=PWM2:22/PWM1:11 motor=2:22/1:11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:14.73@70,89 dx=-14.0 idx=0/1 dist=33/49 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:19.03@66,90 dx=-18.2 idx=0/16 dist=32/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=53,117 r=-1,-1
ATGSeedDiag: seed=1@54,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(22.7) imip=0/9 pass=10110 acc=-1 ipm=71.1,115.5 inv=49.2,103.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=261 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=10/0 raw=56/0 sel=10/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=22.2/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(84,119) ml=(66,90) md=33/1/47 cxcy=84.0,119.6 guide=18.62 atg=-60.0/-60.0/-60.0 pure=9.13/9.13 yaw=-1117 cmd=-1317 actual=-196 signed=0 rps=6806/3194:1892/1640 duty=22/11 pwm=PWM2:22/PWM1:11 motor=2:22/1:11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:14.79@70,89 dx=-14.1 idx=0/1 dist=33/49 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:19.17@66,90 dx=-18.3 idx=0/16 dist=32/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=53,117 r=-1,-1
ATGSeedDiag: seed=1@54,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(22.2) imip=0/9 pass=10110 acc=-1 ipm=71.0,115.6 inv=49.0,103.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=262 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=9/0 raw=55/0 sel=9/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=20.5/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(84,119) ml=(67,90) md=32/1/45 cxcy=84.0,119.6 guide=18.95 atg=-60.0/-60.0/-60.0 pure=8.99/8.99 yaw=-1137 cmd=-1337 actual=-311 signed=0 rps=6833/3167:2060/1705 duty=21/11 pwm=PWM2:21/PWM1:11 motor=2:21/1:11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:15.46@69,90 dx=-14.7 idx=0/1 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:19.77@65,90 dx=-18.8 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=55,117 r=-1,-1
ATGSeedDiag: seed=1@54,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(20.5) imip=0/8 pass=10110 acc=-1 ipm=70.9,115.8 inv=48.5,103.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=263 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=9/0 raw=55/0 sel=9/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.5/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(84,119) ml=(67,90) md=32/1/46 cxcy=84.0,119.6 guide=20.07 atg=-60.0/-60.0/-60.0 pure=9.01/9.01 yaw=-1204 cmd=-1404 actual=-427 signed=0 rps=6925/3075:2235/1783 duty=22/10 pwm=PWM2:22/PWM1:10 motor=2:22/1:10
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:15.52@69,90 dx=-14.7 idx=0/1 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.01@65,91 dx=-19.0 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=55,117 r=-1,-1
ATGSeedDiag: seed=1@54,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(13.5) imip=0/8 pass=10110 acc=-1 ipm=70.8,116.0 inv=48.2,104.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=265 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=9/0 raw=55/0 sel=9/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=8.5/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(84,119) ml=(65,91) md=33/1/45 cxcy=84.0,119.6 guide=19.90 atg=-60.0/-60.0/-60.0 pure=9.11/9.11 yaw=-1194 cmd=-1394 actual=-608 signed=0 rps=6911/3089:2473/1784 duty=21/10 pwm=PWM2:21/PWM1:10 motor=2:21/1:10
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:15.73@69,90 dx=-14.8 idx=0/1 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.41@65,91 dx=-19.3 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=55,118 r=-1,-1
ATGSeedDiag: seed=1@55,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(8.5) imip=0/8 pass=10110 acc=-1 ipm=70.8,116.4 inv=48.0,105.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=266 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=10/0 raw=58/0 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.7/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(84,119) ml=(65,91) md=33/1/45 cxcy=84.0,119.6 guide=19.74 atg=-60.0/-60.0/-60.0 pure=9.17/9.17 yaw=-1184 cmd=-1384 actual=-689 signed=0 rps=6897/3103:2484/1706 duty=21/10 pwm=PWM2:21/PWM1:10 motor=2:21/1:10
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:14.73@70,91 dx=-13.6 idx=0/1 dist=32/48 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.50@65,91 dx=-19.3 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=54,118 r=-1,-1
ATGSeedDiag: seed=1@58,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(9.7) imip=0/9 pass=10110 acc=-1 ipm=72.1,117.0 inv=50.7,108.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=267 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=8/0 raw=49/0 sel=8/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.6/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(84,119) ml=(65,91) md=32/1/44 cxcy=84.0,119.6 guide=22.12 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=-1327 cmd=-1527 actual=-760 signed=0 rps=7093/2907:2753/1768 duty=22/9 pwm=PWM2:22/PWM1:9 motor=2:22/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.67@67,91 dx=-17.4 idx=0/1 dist=33/45 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.81@63,92 dx=-21.5 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=55,118 r=-1,-1
ATGSeedDiag: seed=1@51,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(9.6) imip=0/7 pass=10110 acc=-1 ipm=69.2,117.1 inv=43.6,108.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=268 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=-1016 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=270 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=-976 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@124,85 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=273 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=-797 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@127,88 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=277 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=-454 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@131,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=281 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=-390 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@135,96 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=285 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=-156 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@137,100 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=291 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=-27 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@140,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=297 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=107 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=301 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1423 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=9.24/9.24 yaw=0 cmd=0 actual=158 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T07:23:00+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive110
```
