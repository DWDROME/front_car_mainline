# drive105

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive105-front_car_circle_drive105.log
- remote_log: /tmp/front_car_circle_drive105.log
- started_at: 2026-06-22T07:14:28+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive105 6
```

3916 /tmp/front_car_circle_drive105.log
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=2/0 raw=68/0 sel=2/10 far=0/0 far_raw=0/0 l=1@3/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.0/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(84,99) md=20/0/20 cxcy=84.0,119.6 guide=0.03 atg=0.0/0.0/0.0 pure=-0.08/-0.08 yaw=-1 cmd=-201 actual=753 signed=0 rps=5275/4725:4930/5640 duty=12/12 pwm=PWM2:12/PWM1:12 motor=2:12/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@3/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/10 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-0.20@84,96 dx=0.2 idx=0/1 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-0.19@84,99 dx=0.1 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@30,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(97.0) imip=0/13 pass=11111 acc=3 ipm=67.5,110.3 inv=44.9,88.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=886 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=63/0 sel=1/0 far=0/0 far_raw=0/0 l=1@2/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.6/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=0.23/0.23 yaw=0 cmd=0 actual=378 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@2/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@31,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(93.6) imip=0/12 pass=11111 acc=2 ipm=66.7,112.2 inv=41.8,93.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=889 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/0 raw=56/0 sel=0/0 far=0/0 far_raw=0/0 l=1@1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.0/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=0.23/0.23 yaw=0 cmd=0 actual=485 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@33,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(93.0) imip=0/11 pass=11111 acc=1 ipm=66.3,114.2 inv=39.3,98.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=892 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/0 raw=47/0 sel=0/0 far=0/0 far_raw=0/0 l=1@1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=76.1/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=0.23/0.23 yaw=0 cmd=0 actual=396 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@35,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(76.1) imip=0/11 pass=11111 acc=1 ipm=66.0,113.9 inv=39.0,98.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=893 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=11/0 raw=44/0 sel=11/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=48.9/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(71,89) md=33/1/48 cxcy=84.0,119.6 guide=13.59 atg=-60.0/-60.0/-60.0 pure=7.14/7.14 yaw=-816 cmd=-1016 actual=365 signed=0 rps=6392/3608:5463/5249 duty=16/8 pwm=PWM2:16/PWM1:8 motor=2:16/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/0 centerNum=11/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:12.08@73,89 dx=-11.5 idx=0/2 dist=33/49 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:15.49@69,88 dx=-15.2 idx=0/16 dist=32/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=45,108 r=-1,-1
ATGSeedDiag: seed=1@35,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(48.9) imip=0/10 pass=10111 acc=-1 ipm=65.0,114.1 inv=36.6,98.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=894 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=10/0 raw=44/0 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=35.7/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(70,89) md=32/1/45 cxcy=84.0,119.6 guide=15.59 atg=-60.0/-60.0/-60.0 pure=7.13/7.13 yaw=-936 cmd=-1136 actual=306 signed=0 rps=6556/3444:5351/5179 duty=16/7 pwm=PWM2:16/PWM1:7 motor=2:16/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:12.79@72,90 dx=-12.1 idx=0/2 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:16.39@68,88 dx=-16.0 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=47,109 r=-1,-1
ATGSeedDiag: seed=1@35,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(35.7) imip=0/9 pass=10111 acc=-1 ipm=64.7,114.6 inv=35.3,100.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=895 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=10/0 raw=38/0 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.2/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(69,89) md=32/1/45 cxcy=84.0,119.6 guide=16.84 atg=-60.0/-60.0/-60.0 pure=7.38/7.38 yaw=-1010 cmd=-1210 actual=286 signed=0 rps=6659/3341:3571/3464 duty=19/9 pwm=PWM2:19/PWM1:9 motor=2:19/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:14.67@70,90 dx=-13.9 idx=0/2 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:17.70@67,89 dx=-17.3 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=46,110 r=-1,-1
ATGSeedDiag: seed=1@36,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(9.2) imip=0/9 pass=10111 acc=-1 ipm=64.1,115.2 inv=33.4,102.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=896 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=9/0 raw=35/0 sel=9/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.1/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(68,90) md=32/1/43 cxcy=84.0,119.6 guide=17.92 atg=-60.0/-60.0/-60.0 pure=7.38/7.38 yaw=-1075 cmd=-1275 actual=243 signed=0 rps=6748/3252:4181/4219 duty=18/8 pwm=PWM2:18/PWM1:8 motor=2:18/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:13.84@71,91 dx=-12.8 idx=0/1 dist=32/46 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:18.69@66,89 dx=-18.2 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,111 r=-1,-1
ATGSeedDiag: seed=1@37,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(2.1) imip=0/8 pass=10111 acc=-1 ipm=61.1,114.8 inv=27.0,100.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=897 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=8/0 raw=32/0 sel=8/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=1.6/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(65,89) md=33/1/40 cxcy=84.0,119.6 guide=19.22 atg=-60.0/-60.0/-60.0 pure=7.39/7.39 yaw=-1153 cmd=-1353 actual=207 signed=0 rps=6854/3146:4152/4334 duty=19/7 pwm=PWM2:19/PWM1:7 motor=2:19/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:15.59@70,91 dx=-14.5 idx=0/1 dist=32/44 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:19.78@65,89 dx=-19.2 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=49,112 r=-1,-1
ATGSeedDiag: seed=1@34,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(1.6) imip=0/7 pass=10111 acc=-1 ipm=62.0,115.7 inv=27.9,103.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=898 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=7/0 raw=28/0 sel=7/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.5/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(66,90) md=32/1/41 cxcy=84.0,119.6 guide=20.24 atg=-60.0/-60.0/-60.0 pure=7.63/7.63 yaw=-1214 cmd=-1414 actual=172 signed=0 rps=6938/3062:4371/4621 duty=19/6 pwm=PWM2:19/PWM1:6 motor=2:19/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=7/0 centerNum=7/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:17.44@68,91 dx=-16.3 idx=0/1 dist=33/43 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.88@64,90 dx=-20.3 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=49,112 r=-1,-1
ATGSeedDiag: seed=1@30,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(3.5) imip=0/6 pass=10111 acc=-1 ipm=60.3,115.8 inv=23.8,104.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=899 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=5/0 raw=19/0 sel=5/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.9/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(64,91) md=33/1/40 cxcy=84.0,119.6 guide=21.80 atg=-60.0/-60.0/-60.0 pure=7.83/7.83 yaw=-1308 cmd=-1508 actual=132 signed=0 rps=7067/2933:4322/4599 duty=19/6 pwm=PWM2:19/PWM1:6 motor=2:19/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:21.32@64,91 dx=-20.3 idx=0/1 dist=35/41 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.82@62,90 dx=-22.1 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=50,114 r=-1,-1
ATGSeedDiag: seed=1@21,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(3.9) imip=0/4 pass=10111 acc=-1 ipm=56.5,115.8 inv=14.9,104.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=900 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=4/0 raw=15/0 sel=4/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=5.0/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(63,92) md=33/1/38 cxcy=84.0,119.6 guide=22.69 atg=-60.0/-60.0/-60.0 pure=7.79/7.79 yaw=-1361 cmd=-1561 actual=59 signed=0 rps=7140/2860:4182/4443 duty=20/6 pwm=PWM2:20/PWM1:6 motor=2:20/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.94@62,91 dx=-22.0 idx=0/1 dist=36/40 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:23.62@61,90 dx=-22.9 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=50,114 r=-1,-1
ATGSeedDiag: seed=1@17,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(5.0) imip=0/3 pass=10111 acc=-1 ipm=54.8,115.8 inv=10.9,104.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=901 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=3/0 raw=11/0 sel=3/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=5.5/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(62,93) md=33/1/38 cxcy=84.0,119.6 guide=23.95 atg=-60.0/-60.0/-60.0 pure=7.99/7.99 yaw=-1437 cmd=-1637 actual=-8 signed=0 rps=7244/2756:4234/4405 duty=20/5 pwm=PWM2:20/PWM1:5 motor=2:20/1:5
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:24.77@60,91 dx=-24.1 idx=0/1 dist=38/40 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:24.64@60,91 dx=-23.7 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=51,115 r=-1,-1
ATGSeedDiag: seed=1@13,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(5.5) imip=0/2 pass=10111 acc=-1 ipm=53.1,115.8 inv=7.0,104.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=902 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=2/0 raw=7/0 sel=2/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(84,119) ml=(61,94) md=33/1/36 cxcy=84.0,119.6 guide=24.78 atg=-60.0/-60.0/-60.0 pure=8.23/8.23 yaw=-1487 cmd=-1687 actual=-80 signed=0 rps=7312/2688:4497/4476 duty=20/5 pwm=PWM2:20/PWM1:5 motor=2:20/1:5
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:26.51@58,90 dx=-26.1 idx=0/1 dist=39/39 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:25.97@59,92 dx=-24.8 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=51,116 r=-1,-1
ATGSeedDiag: seed=1@9,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=903 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=3/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=8.23/8.23 yaw=0 cmd=0 actual=-323 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@5,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=904 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/3027 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=8.23/8.23 yaw=0 cmd=0 actual=-408 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T07:14:41+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive105
```
