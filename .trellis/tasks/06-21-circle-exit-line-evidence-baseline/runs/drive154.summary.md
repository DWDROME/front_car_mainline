# drive154

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive154-front_car_circle_drive154.log
- remote_log: /tmp/front_car_circle_drive154.log
- started_at: 2026-06-22T15:27:28+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive154 6
```

4314 /tmp/front_car_circle_drive154.log
frame=901 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/60 cxcy=84.0,119.6 guide=-42.85 atg=60.0/60.0/60.0 pure=-12.89/-12.89 yaw=2571 cmd=2771 actual=2020 signed=0 rps=1202/8798:7240/11456 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.82@109,109 dx=25.2 idx=11/27 dist=32/70 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.66@118,108 dx=34.3 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,84 r=-1,-1
ATGSeedDiag: seed=1@4,101/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=37(11.8) imip=27/47 pass=10110 acc=-1 ipm=126.9,80.9 inv=123.9,46.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=902 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=32/1/60 cxcy=84.0,119.6 guide=-44.27 atg=60.0/60.0/60.0 pure=-12.91/-12.91 yaw=2656 cmd=2856 actual=2116 signed=0 rps=1085/8915:4746/7450 duty=0/26 pwm=PWM2:0/PWM1:26 motor=2:0/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.92@109,110 dx=24.9 idx=11/27 dist=32/71 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.99@119,108 dx=34.7 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,84 r=-1,-1
ATGSeedDiag: seed=1@4,102/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.7) imip=0/20 pass=10110 acc=-1 ipm=67.8,98.3 inv=51.5,65.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=904 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=47/0 raw=153/0 sel=47/27 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,109) md=33/1/58 cxcy=84.0,119.6 guide=-44.58 atg=60.0/60.0/60.0 pure=-13.15/-13.15 yaw=2675 cmd=2875 actual=2380 signed=0 rps=1060/8940:6497/9614 duty=0/24 pwm=PWM2:0/PWM1:24 motor=2:0/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=47/0 centerNum=47/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=47/27 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.30@110,110 dx=25.7 idx=11/27 dist=32/69 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-46.41@119,109 dx=35.2 idx=0/16 dist=32/52 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,85 r=-1,-1
ATGSeedDiag: seed=1@4,103/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=37(11.7) imip=27/46 pass=10110 acc=-1 ipm=127.7,82.1 inv=125.8,47.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=905 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=47/0 raw=153/0 sel=47/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,110) md=33/1/61 cxcy=84.0,119.6 guide=-45.09 atg=60.0/60.0/60.0 pure=-13.10/-13.10 yaw=2706 cmd=2899 actual=2512 signed=0 rps=1026/8974:5961/9188 duty=0/24 pwm=PWM2:0/PWM1:24 motor=2:0/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=47/0 centerNum=47/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=47/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.47@110,111 dx=25.5 idx=11/27 dist=32/70 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-46.57@119,109 dx=35.4 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,85 r=-1,-1
ATGSeedDiag: seed=1@4,104/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.7) imip=0/20 pass=10110 acc=-1 ipm=68.5,99.1 inv=52.2,66.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=906 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=47/0 raw=153/0 sel=47/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.6/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,110) md=33/1/61 cxcy=84.0,119.6 guide=-45.61 atg=60.0/60.0/60.0 pure=-13.14/-13.14 yaw=2737 cmd=2837 actual=2637 signed=0 rps=1112/8888:6200/10270 duty=0/23 pwm=PWM2:0/PWM1:23 motor=2:0/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=47/0 centerNum=47/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=47/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.40@110,111 dx=26.1 idx=11/27 dist=32/69 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.13@120,110 dx=35.5 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=105,85 r=-1,-1
ATGSeedDiag: seed=1@4,105/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.6) imip=0/20 pass=10110 acc=-1 ipm=68.8,99.4 inv=52.6,67.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=908 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=153/0 sel=46/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.2/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,111) md=33/1/60 cxcy=84.0,119.6 guide=-45.45 atg=60.0/60.0/60.0 pure=-13.10/-13.10 yaw=2727 cmd=2596 actual=2858 signed=0 rps=1442/8558:5789/10422 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-40.35@110,112 dx=26.4 idx=10/27 dist=33/69 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.14@119,110 dx=34.9 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,86 r=-1,-1
ATGSeedDiag: seed=1@4,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.2) imip=0/20 pass=10110 acc=-1 ipm=69.5,100.3 inv=53.4,68.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=910 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=151/0 sel=46/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,111) md=33/1/60 cxcy=84.0,119.6 guide=-45.63 atg=60.0/60.0/60.0 pure=-13.16/-13.16 yaw=2738 cmd=2538 actual=3048 signed=0 rps=1522/8478:5180/9994 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.74@110,112 dx=25.5 idx=10/26 dist=32/69 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.38@119,110 dx=35.1 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,86 r=-1,-1
ATGSeedDiag: seed=1@6,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.3) imip=0/20 pass=10110 acc=-1 ipm=70.2,100.2 inv=54.6,68.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=45/0 raw=149/0 sel=45/27 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,111) md=33/1/58 cxcy=84.0,119.6 guide=-46.71 atg=60.0/60.0/60.0 pure=-13.43/-13.43 yaw=2802 cmd=2602 actual=3192 signed=0 rps=1433/8567:5491/10145 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/0 centerNum=45/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/27 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-41.51@111,113 dx=26.8 idx=10/26 dist=33/67 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.44@119,111 dx=35.3 idx=0/16 dist=32/52 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=106,87 r=-1,-1
ATGSeedDiag: seed=1@8,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.5) imip=0/20 pass=10110 acc=-1 ipm=71.3,100.5 inv=56.3,68.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=44/0 raw=144/0 sel=44/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,112) md=32/1/60 cxcy=84.0,119.6 guide=-47.51 atg=60.0/60.0/60.0 pure=-13.23/-13.23 yaw=2850 cmd=2650 actual=3281 signed=0 rps=1368/8632:5053/9540 duty=0/22 pwm=PWM2:0/PWM1:22 motor=2:0/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=44/0 centerNum=44/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=44/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-40.88@110,113 dx=25.7 idx=9/24 dist=32/69 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.03@119,112 dx=34.6 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,88 r=-1,-1
ATGSeedDiag: seed=1@13,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.7) imip=0/20 pass=10110 acc=-1 ipm=73.6,100.5 inv=59.8,68.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=918 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=44/0 raw=143/0 sel=44/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,112) md=32/1/60 cxcy=84.0,119.6 guide=-47.20 atg=60.0/60.0/60.0 pure=-13.20/-13.20 yaw=2832 cmd=2632 actual=3276 signed=0 rps=1393/8607:5227/10217 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=44/0 centerNum=44/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=44/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-41.19@110,113 dx=26.0 idx=9/24 dist=32/69 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.99@119,111 dx=34.7 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=106,87 r=-1,-1
ATGSeedDiag: seed=1@14,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.7) imip=0/20 pass=10110 acc=-1 ipm=74.0,100.5 inv=60.5,68.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=919 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=44/0 raw=142/0 sel=44/28 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=8.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,112) md=33/1/60 cxcy=84.0,119.6 guide=-47.49 atg=60.0/60.0/60.0 pure=-13.15/-13.15 yaw=2850 cmd=2650 actual=3286 signed=0 rps=1369/8631:5116/10800 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=44/0 centerNum=44/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=44/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-41.83@111,113 dx=26.6 idx=9/24 dist=32/69 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.12@119,112 dx=34.8 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=106,87 r=-1,-1
ATGSeedDiag: seed=1@15,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=34(8.8) imip=24/43 pass=10110 acc=-1 ipm=127.0,84.5 inv=126.9,49.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=920 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=44/0 raw=141/0 sel=44/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,112) md=32/1/61 cxcy=84.0,119.6 guide=-46.94 atg=60.0/60.0/60.0 pure=-13.07/-13.07 yaw=2817 cmd=2617 actual=3322 signed=0 rps=1414/8586:4701/10229 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=44/0 centerNum=44/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=44/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-40.74@109,114 dx=25.1 idx=8/23 dist=32/71 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.78@118,112 dx=33.9 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=105,88 r=-1,-1
ATGSeedDiag: seed=1@16,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(9.8) imip=0/20 pass=10110 acc=-1 ipm=74.9,100.6 inv=61.9,68.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=43/0 raw=139/0 sel=43/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,113) md=32/1/61 cxcy=84.0,119.6 guide=-47.24 atg=60.0/60.0/60.0 pure=-13.07/-13.07 yaw=2835 cmd=2635 actual=3342 signed=0 rps=1389/8611:4840/9741 duty=0/22 pwm=PWM2:0/PWM1:22 motor=2:0/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=43/0 centerNum=43/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=43/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-41.83@110,114 dx=26.0 idx=8/23 dist=33/70 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.00@118,112 dx=33.9 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=106,88 r=-1,-1
ATGSeedDiag: seed=1@19,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=41(12.8) imip=31/42 pass=10110 acc=-1 ipm=144.7,85.9 inv=149.9,50.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=43/0 raw=137/0 sel=43/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,112) md=32/1/61 cxcy=84.0,119.6 guide=-46.94 atg=60.0/60.0/60.0 pure=-12.95/-12.95 yaw=2817 cmd=2617 actual=3332 signed=0 rps=1414/8586:5197/10440 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=43/0 centerNum=43/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=43/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-41.16@109,114 dx=25.2 idx=8/22 dist=33/73 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.76@118,112 dx=33.9 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,88 r=-1,-1
ATGSeedDiag: seed=1@20,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(9.7) imip=0/20 pass=10110 acc=-1 ipm=76.5,100.4 inv=64.5,68.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=924 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=44/0 raw=136/0 sel=44/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=6.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,112) md=32/1/64 cxcy=84.0,119.6 guide=-46.79 atg=60.0/60.0/60.0 pure=-12.70/-12.70 yaw=2807 cmd=2607 actual=3346 signed=0 rps=1427/8573:5420/10984 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=44/0 centerNum=44/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=44/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-41.21@110,114 dx=25.5 idx=8/22 dist=33/75 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.45@118,112 dx=33.9 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,88 r=-1,-1
ATGSeedDiag: seed=1@21,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(6.9) imip=1/21 pass=10110 acc=-1 ipm=78.7,99.0 inv=68.2,66.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=925 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=43/0 raw=136/0 sel=43/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.4/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,112) md=33/1/63 cxcy=84.0,119.6 guide=-46.72 atg=60.0/60.0/60.0 pure=-12.70/-12.70 yaw=2803 cmd=2603 actual=3352 signed=0 rps=1433/8567:5218/10430 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=43/0 centerNum=43/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=43/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-40.17@108,114 dx=24.3 idx=7/21 dist=32/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-46.71@117,112 dx=32.8 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,88 r=-1,-1
ATGSeedDiag: seed=1@22,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.4) imip=0/20 pass=10110 acc=-1 ipm=77.1,100.3 inv=65.5,68.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T15:27:41+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive154
```
