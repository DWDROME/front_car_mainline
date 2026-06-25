# drive72

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive72-front_car_circle_drive72.log
- remote_log: /tmp/front_car_circle_drive72.log
- started_at: 2026-06-22T04:54:23+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive72 6
```

4054 /tmp/front_car_circle_drive72.log
frame=878 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/32 raw=0/170 sel=32/37 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/29.0/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(79,86) md=33/1/81 cxcy=84.0,119.6 guide=4.65 atg=-1.0/0.0/0.0 pure=0.40/-0.03 yaw=-119 cmd=-319 actual=434 signed=0 rps=5437/4563:5382/5120 duty=12/12 pwm=PWM2:12/PWM1:12 motor=2:12/1:12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/32 centerNum=0/32 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=32/37 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:4.73@79,86 dx=-4.7 idx=0/11 dist=32/82 sel=1:4.34@80,84 dx=-4.5 idx=0/16 dist=32/72 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=106,75
ATGSeedDiag: seed=1@4,88/1@124,95 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 30(29.0) imip=20/31 pass=10111 acc=-1 ipm=109.5,43.1 inv=92.5,26.5
frame=879 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/26 raw=0/170 sel=26/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/12.4/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(79,88) md=32/1/66 cxcy=84.0,119.6 guide=5.17 atg=0.0/0.0/0.0 pure=0.25/0.25 yaw=-132 cmd=-332 actual=427 signed=0 rps=5455/4545:6486/6777 duty=11/10 pwm=PWM2:11/PWM1:10 motor=2:11/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/26 centerNum=0/26 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:4.80@79,85 dx=-4.9 idx=0/12 dist=32/64 sel=1:4.69@79,84 dx=-4.8 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=106,77
ATGSeedDiag: seed=1@4,88/1@126,99 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 24(12.4) imip=14/25 pass=10111 acc=-1 ipm=107.7,58.2 inv=94.4,32.4
frame=880 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/21 raw=5/170 sel=21/25 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/5.5/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(79,86) md=33/1/54 cxcy=84.0,119.6 guide=5.07 atg=-2.0/-1.0/-1.0 pure=0.65/0.65 yaw=-129 cmd=-329 actual=408 signed=0 rps=5451/4549:4657/5128 duty=13/12 pwm=PWM2:13/PWM1:12 motor=2:13/1:12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/21 centerNum=1/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/25 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:5.31@79,86 dx=-5.3 idx=0/11 dist=32/52 sel=1:5.01@79,84 dx=-5.2 idx=0/16 dist=32/48 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=105,76
ATGSeedDiag: seed=1@4,88/1@124,96 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 19(5.5) imip=9/20 pass=10111 acc=-1 ipm=106.2,68.6 inv=96.0,37.8
frame=881 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/30 raw=6/170 sel=30/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/15.7/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(78,86) md=34/1/75 cxcy=84.0,119.6 guide=5.55 atg=-2.0/0.0/0.0 pure=0.58/0.29 yaw=-141 cmd=-341 actual=381 signed=0 rps=5468/4532:4984/5707 duty=13/11 pwm=PWM2:13/PWM1:11 motor=2:13/1:11
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/30 centerNum=1/30 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=30/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:5.30@79,84 dx=-5.5 idx=0/13 dist=33/70 sel=1:5.35@79,84 dx=-5.5 idx=0/16 dist=32/66 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=105,77
ATGSeedDiag: seed=1@4,87/1@126,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 28(15.7) imip=18/29 pass=10111 acc=-1 ipm=106.7,49.5 inv=91.7,28.8
frame=882 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/5 raw=2/170 sel=5/9 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/6.0/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(79,102) md=17/0/17 cxcy=84.0,119.6 guide=7.04 atg=-17.0/-7.0/-7.0 pure=3.52/3.52 yaw=-423 cmd=-623 actual=352 signed=0 rps=5853/4147:4933/5580 duty=14/10 pwm=PWM2:14/PWM1:10 motor=2:14/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/5 centerNum=1/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/9 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:7.43@79,102 dx=-5.3 idx=0/4 dist=18/18 sel=1:7.50@79,102 dx=-5.3 idx=0/8 dist=16/16 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=105,103
ATGSeedDiag: seed=1@4,86/1@122,94 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 3(6.0) imip=0/4 pass=10111 acc=-1 ipm=104.6,104.9 inv=113.1,75.8
frame=883 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/110 raw=0/170 sel=110/114 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/2.0/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(78,89) md=32/1/128 cxcy=84.0,119.6 guide=6.27 atg=-4.0/0.0/0.0 pure=0.78/0.33 yaw=-376 cmd=-576 actual=318 signed=0 rps=5790/4210:5305/5842 duty=14/10 pwm=PWM2:14/PWM1:10 motor=2:14/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/110 centerNum=0/110 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=110/114 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:5.88@78,83 dx=-6.1 idx=0/13 dist=33/229 sel=1:5.97@78,84 dx=-6.1 idx=0/16 dist=32/226 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,77
ATGSeedDiag: seed=1@4,85/1@124,99 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 11(2.0) imip=1/21 pass=10111 acc=-1 ipm=103.9,88.2 inv=100.9,52.7
frame=884 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2676 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-4.0/0.0/0.0 pure=0.78/0.33 yaw=0 cmd=0 actual=230 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=885 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/9 raw=1/170 sel=9/11 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/16.2/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(78,99) md=22/0/22 cxcy=84.0,119.6 guide=7.86 atg=-19.0/-7.0/-7.0 pure=3.33/3.33 yaw=-471 cmd=-671 actual=250 signed=0 rps=5920/4080:6073/5737 duty=13/9 pwm=PWM2:13/PWM1:9 motor=2:13/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/9 centerNum=1/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:7.24@78,98 dx=-5.7 idx=0/8 dist=22/22 sel=1:7.73@78,99 dx=-6.0 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,97
ATGSeedDiag: seed=1@4,85/1@127,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 7(16.2) imip=0/8 pass=10111 acc=-1 ipm=103.8,99.7 inv=107.6,67.0
frame=886 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/28 raw=170/170 sel=28/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/15.4/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(77,89) md=32/1/69 cxcy=84.0,119.6 guide=7.34 atg=-5.0/-1.0/-1.0 pure=0.87/0.75 yaw=-441 cmd=-641 actual=242 signed=0 rps=5878/4122:6027/5630 duty=13/9 pwm=PWM2:13/PWM1:9 motor=2:13/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/28 centerNum=1/28 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=28/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:6.72@77,85 dx=-6.8 idx=0/13 dist=32/62 sel=1:6.65@77,85 dx=-6.8 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,78
ATGSeedDiag: seed=1@10,93/1@126,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 26(15.4) imip=16/27 pass=10111 acc=-1 ipm=104.1,55.0 inv=90.7,31.0
frame=887 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2676 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-5.0/-1.0/-1.0 pure=0.87/0.75 yaw=0 cmd=0 actual=216 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=888 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/123 raw=170/96 sel=123/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/3.1/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(77,89) md=32/1/123 cxcy=84.0,119.6 guide=7.34 atg=-7.0/-1.0/0.0 pure=1.01/0.46 yaw=-441 cmd=-641 actual=23 signed=0 rps=5878/4122:6073/5585 duty=13/10 pwm=PWM2:13/PWM1:10 motor=2:13/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/123 centerNum=1/123 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=123/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:7.06@77,86 dx=-7.0 idx=0/12 dist=32/252 sel=1:6.96@77,85 dx=-7.1 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=103,77
ATGSeedDiag: seed=1@8,97/1@123,99 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(3.1) imip=0/11 pass=10111 acc=-1 ipm=104.0,111.3 inv=118.9,90.0
frame=889 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/18 raw=170/170 sel=18/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/14.5/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(77,87) md=33/1/47 cxcy=84.0,119.6 guide=7.14 atg=-10.0/-4.0/-4.0 pure=1.53/1.53 yaw=-429 cmd=-629 actual=-30 signed=0 rps=5861/4139:5586/5315 duty=14/10 pwm=PWM2:14/PWM1:10 motor=2:14/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/18 centerNum=1/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=18/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:7.53@77,88 dx=-7.2 idx=0/10 dist=32/48 sel=1:7.12@77,84 dx=-7.3 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=103,74
ATGSeedDiag: seed=1@6,99/1@119,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 16(14.5) imip=6/17 pass=10111 acc=-1 ipm=103.1,74.0 inv=94.5,41.1
frame=890 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/15 raw=0/170 sel=15/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/24.6/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(77,87) md=33/1/40 cxcy=84.0,119.6 guide=7.14 atg=-12.0/-5.0/-5.0 pure=1.83/1.83 yaw=-429 cmd=-629 actual=-45 signed=0 rps=5861/4139:5677/5770 duty=13/9 pwm=PWM2:13/PWM1:9 motor=2:13/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/15 centerNum=0/15 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=15/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:7.43@77,87 dx=-7.2 idx=0/10 dist=32/42 sel=1:7.10@77,84 dx=-7.3 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,79
ATGSeedDiag: seed=0@-1,-1/1@119,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 13(24.6) imip=3/14 pass=10111 acc=-1 ipm=103.3,81.0 inv=97.1,46.3
frame=891 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/25 raw=0/170 sel=25/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/16.7/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(76,88) md=33/1/61 cxcy=84.0,119.6 guide=8.09 atg=-7.0/-2.0/-2.0 pure=1.07/1.07 yaw=-485 cmd=-685 actual=-15 signed=0 rps=5939/4061:5307/5706 duty=14/9 pwm=PWM2:14/PWM1:9 motor=2:14/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/25 centerNum=0/25 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=25/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:7.56@76,86 dx=-7.6 idx=0/13 dist=33/57 sel=1:7.53@76,85 dx=-7.6 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=103,79
ATGSeedDiag: seed=0@-1,-1/1@125,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 23(16.7) imip=13/24 pass=10111 acc=-1 ipm=103.1,62.3 inv=91.4,34.4
frame=892 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/2 raw=0/170 sel=2/5 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2676 m0=(84,119) ml=(79,112) md=8/0/8 cxcy=84.0,119.6 guide=9.31 atg=-30.0/-12.0/-12.0 pure=6.13/6.13 yaw=-558 cmd=-758 actual=-2 signed=0 rps=6039/3961:5354/5905 duty=14/8 pwm=PWM2:14/PWM1:8 motor=2:14/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/2 centerNum=0/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/5 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:11.05@78,111 dx=-6.2 idx=0/1 dist=10/10 sel=1:10.16@79,112 dx=-5.5 idx=0/4 dist=8/8 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,114
ATGSeedDiag: seed=0@-1,-1/1@126,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=893 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2676 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-30.0/-12.0/-12.0 pure=6.13/6.13 yaw=0 cmd=0 actual=70 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@11,101/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T04:54:36+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive72
```
