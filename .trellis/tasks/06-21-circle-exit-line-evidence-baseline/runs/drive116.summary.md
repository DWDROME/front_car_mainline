# drive116

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive116-front_car_circle_drive116.log
- remote_log: /tmp/front_car_circle_drive116.log
- started_at: 2026-06-22T07:34:10+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive116 6
```

4187 /tmp/front_car_circle_drive116.log
frame=892 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=76/0 sel=2/11 far=0/0 far_raw=0/0 l=1@3/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.5/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(86,96) md=23/0/23 cxcy=84.0,119.6 guide=-2.42 atg=2.0/1.0/1.0 pure=-1.25/-1.25 yaw=62 cmd=-138 actual=640 signed=0 rps=4811/5189:5784/4966 duty=13/12 pwm=PWM2:12/PWM1:13 motor=2:12/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@3/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-3.13@87,94 dx=2.6 idx=0/1 dist=25/25 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-3.01@86,96 dx=2.4 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(94.5) imip=0/13 pass=11111 acc=3 ipm=71.3,109.9 inv=52.8,87.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=893 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=72/0 sel=2/12 far=0/0 far_raw=0/0 l=1@3/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.5/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(85,94) md=25/0/25 cxcy=84.0,119.6 guide=-1.15 atg=0.0/0.0/0.0 pure=-0.63/-0.63 yaw=29 cmd=-171 actual=592 signed=0 rps=4766/5234:5868/5291 duty=12/12 pwm=PWM2:12/PWM1:12 motor=2:12/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@3/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-1.62@85,93 dx=1.4 idx=0/1 dist=27/27 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-1.59@85,94 dx=1.4 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@42,107/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(96.5) imip=0/13 pass=11111 acc=3 ipm=71.3,109.5 inv=52.9,86.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=894 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=70/0 sel=1/0 far=0/0 far_raw=0/0 l=1@2/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=92.1/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=-0.63/-0.63 yaw=0 cmd=0 actual=327 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@2/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@42,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(92.1) imip=0/12 pass=11111 acc=2 ipm=70.8,112.0 inv=50.5,92.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=895 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=69/0 sel=1/0 far=0/0 far_raw=0/0 l=1@2/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.3/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=-0.63/-0.63 yaw=0 cmd=0 actual=238 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@2/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@43,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(93.3) imip=0/12 pass=11111 acc=2 ipm=70.9,111.9 inv=50.8,92.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=897 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=63/0 sel=0/0 far=0/0 far_raw=0/0 l=1@1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.2/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=-0.63/-0.63 yaw=0 cmd=0 actual=385 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@43,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(90.2) imip=0/11 pass=11111 acc=1 ipm=70.2,114.1 inv=48.1,98.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=899 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=57/0 sel=0/0 far=0/0 far_raw=0/0 l=1@1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.6/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=-0.63/-0.63 yaw=0 cmd=0 actual=533 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@45,107/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(91.6) imip=0/11 pass=11111 acc=1 ipm=70.6,113.7 inv=49.1,97.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=900 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=56/0 sel=0/0 far=0/0 far_raw=0/0 l=1@1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=68.5/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=0.0/0.0/0.0 pure=-0.63/-0.63 yaw=0 cmd=0 actual=525 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@45,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(68.5) imip=0/11 pass=11111 acc=1 ipm=69.7,113.9 inv=47.1,98.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=901 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/0 raw=53/0 sel=12/24 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=36.1/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(72,89) md=33/1/51 cxcy=84.0,119.6 guide=12.58 atg=-60.0/-60.0/-60.0 pure=7.41/7.41 yaw=-755 cmd=-955 actual=484 signed=0 rps=3691/6309:5920/4700 duty=7/16 pwm=PWM2:16/PWM1:7 motor=2:16/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=12/0 centerNum=12/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/24 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:10.79@74,89 dx=-10.3 idx=0/2 dist=33/53 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:14.41@70,88 dx=-14.1 idx=0/16 dist=32/46 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=46,109 r=-1,-1
ATGSeedDiag: seed=1@45,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(36.1) imip=0/11 pass=10111 acc=-1 ipm=68.6,114.5 inv=44.3,99.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=902 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/0 raw=49/0 sel=11/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.7/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(71,89) md=32/1/48 cxcy=84.0,119.6 guide=14.77 atg=-60.0/-60.0/-60.0 pure=7.46/7.46 yaw=-886 cmd=-1086 actual=392 signed=0 rps=3511/6489:5456/4384 duty=7/17 pwm=PWM2:17/PWM1:7 motor=2:17/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/0 centerNum=11/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:11.93@73,89 dx=-11.3 idx=0/2 dist=33/49 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:15.69@69,88 dx=-15.3 idx=0/16 dist=32/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,110 r=-1,-1
ATGSeedDiag: seed=1@46,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(12.7) imip=0/10 pass=10111 acc=-1 ipm=68.3,115.2 inv=43.1,102.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=903 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=10/0 raw=44/0 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=4.2/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(70,89) md=32/1/46 cxcy=84.0,119.6 guide=16.18 atg=-60.0/-60.0/-60.0 pure=7.54/7.54 yaw=-971 cmd=-1171 actual=315 signed=0 rps=3395/6605:5359/4539 duty=7/17 pwm=PWM2:17/PWM1:7 motor=2:17/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:13.84@71,90 dx=-13.1 idx=0/2 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:17.26@67,89 dx=-16.7 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=49,111 r=-1,-1
ATGSeedDiag: seed=1@46,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(4.2) imip=0/9 pass=10111 acc=-1 ipm=67.1,115.6 inv=39.8,103.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=904 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=10/0 raw=42/0 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.7/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(68,90) md=32/1/45 cxcy=84.0,119.6 guide=17.64 atg=-60.0/-60.0/-60.0 pure=7.77/7.77 yaw=-1059 cmd=-1259 actual=250 signed=0 rps=3275/6725:6037/5789 duty=6/16 pwm=PWM2:16/PWM1:6 motor=2:16/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:15.14@70,90 dx=-14.3 idx=0/2 dist=33/47 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:18.41@66,89 dx=-17.8 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,112 r=-1,-1
ATGSeedDiag: seed=1@44,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.7) imip=0/9 pass=10111 acc=-1 ipm=66.2,116.0 inv=37.4,104.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=905 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/0 raw=35/0 sel=8/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=5.1/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(64,90) md=34/1/43 cxcy=84.0,119.6 guide=19.65 atg=-60.0/-60.0/-60.0 pure=7.87/7.87 yaw=-1179 cmd=-1379 actual=212 signed=0 rps=3110/6890:3873/3889 duty=8/19 pwm=PWM2:19/PWM1:8 motor=2:19/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:16.24@69,91 dx=-15.2 idx=0/1 dist=33/45 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.21@64,90 dx=-19.6 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=50,113 r=-1,-1
ATGSeedDiag: seed=1@37,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(5.1) imip=0/7 pass=10111 acc=-1 ipm=63.2,116.0 inv=30.3,105.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=907 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/0 raw=20/0 sel=5/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=6.3/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(63,92) md=33/1/40 cxcy=84.0,119.6 guide=22.39 atg=-60.0/-60.0/-60.0 pure=7.99/7.99 yaw=-1343 cmd=-1543 actual=160 signed=0 rps=2885/7115:4568/5214 duty=6/18 pwm=PWM2:18/PWM1:6 motor=2:18/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.36@63,91 dx=-21.5 idx=0/1 dist=36/42 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:23.25@61,90 dx=-22.6 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=50,114 r=-1,-1
ATGSeedDiag: seed=1@22,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(6.3) imip=0/4 pass=10111 acc=-1 ipm=56.9,116.0 inv=15.4,105.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=908 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=8/0 sel=2/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(60,94) md=34/1/38 cxcy=84.0,119.6 guide=26.02 atg=-60.0/-60.0/-60.0 pure=8.47/8.47 yaw=-1561 cmd=-1761 actual=87 signed=0 rps=2586/7414:4535/5130 duty=5/20 pwm=PWM2:20/PWM1:5 motor=2:20/1:5
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:28.12@56,90 dx=-28.1 idx=0/1 dist=41/41 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:27.16@58,93 dx=-25.7 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=52,116 r=-1,-1
ATGSeedDiag: seed=1@10,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=909 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=8.47/8.47 yaw=0 cmd=0 actual=-95 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=910 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2668 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=8.47/8.47 yaw=0 cmd=0 actual=-211 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T07:34:23+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive116
```
