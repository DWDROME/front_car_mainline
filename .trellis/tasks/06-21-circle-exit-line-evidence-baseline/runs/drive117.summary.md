# drive117

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive117-front_car_circle_drive117.log
- remote_log: /tmp/front_car_circle_drive117.log
- started_at: 2026-06-22T07:36:48+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive117 6
```

4581 /tmp/front_car_circle_drive117.log
ATGSeedDiag: seed=1@15,108/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(18.0) imip=44/63 pass=10100 acc=-1 ipm=153.4,55.5 inv=131.8,31.0 | 8(38.8) imip=0/18 pass=10111 acc=-1 ipm=117.4,101.6 inv=131.1,69.8
frame=894 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=64/19 raw=156/63 sel=64/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=20.2/37.6/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(102,93) md=32/1/92 cxcy=84.0,119.6 guide=-20.72 atg=60.0/60.0/60.0 pure=-8.74/-8.99 yaw=1243 cmd=1443 actual=332 signed=0 rps=6978/3022:4086/3694 duty=23/6 pwm=PWM2:6/PWM1:23 motor=2:6/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/19 centerNum=64/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/44 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.31@100,95 dx=15.9 idx=3/23 dist=32/109 right=1:-23.30@113,75 dx=29.3 idx=0/12 dist=34/52 sel=1:-21.89@104,92 dx=20.4 idx=0/16 dist=32/86 edge=1:-20.56@104.0,89.5 dx=20.0 width=63.3 l=73,83 r=135,96
CxScan: raw_ref=80.0 edge=104.0,89.5 best_raw_x=130 best_err=-0.89 best_cxcy=103.2,119.7 scan=0:-43.7,10:-41.5,20:-39.0,30:-36.4,40:-33.6,50:-30.6,60:-27.5,70:-24.1,80:-20.6,90:-16.9,100:-13.0,110:-9.0,120:-5.0,130:-0.9,140:3.2
ATGSeedDiag: seed=1@15,108/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=53(20.2) imip=43/63 pass=10100 acc=-1 ipm=151.2,55.7 inv=130.1,31.1 | 8(37.6) imip=0/18 pass=10111 acc=-1 ipm=117.6,101.8 inv=131.6,70.1
frame=895 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=63/18 raw=156/62 sel=63/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.7/37.4/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(103,93) md=33/1/92 cxcy=84.0,119.6 guide=-21.84 atg=60.0/60.0/60.0 pure=-8.77/-9.07 yaw=1311 cmd=1511 actual=379 signed=0 rps=7070/2930:4105/3488 duty=24/6 pwm=PWM2:6/PWM1:24 motor=2:6/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=63/18 centerNum=63/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/44 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.67@101,94 dx=17.4 idx=3/24 dist=33/105 right=1:-23.41@113,75 dx=29.3 idx=0/12 dist=33/48 sel=1:-22.07@105,92 dx=20.5 idx=0/16 dist=32/86 edge=1:-20.74@104.0,90.0 dx=20.0 width=63.2 l=73,84 r=135,96
CxScan: raw_ref=80.0 edge=104.0,90.0 best_raw_x=130 best_err=-0.90 best_cxcy=103.2,119.7 scan=0:-44.0,10:-41.7,20:-39.3,30:-36.7,40:-33.9,50:-30.9,60:-27.7,70:-24.3,80:-20.7,90:-17.0,100:-13.1,110:-9.1,120:-5.0,130:-0.9,140:3.2
ATGSeedDiag: seed=1@15,108/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=59(17.7) imip=49/62 pass=10100 acc=-1 ipm=165.2,60.4 inv=145.5,33.1 | 7(37.4) imip=0/17 pass=10111 acc=-1 ipm=115.9,103.2 inv=130.7,72.6
frame=896 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=63/18 raw=156/61 sel=63/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.5/37.3/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(103,94) md=32/1/90 cxcy=84.0,119.6 guide=-22.11 atg=60.0/60.0/60.0 pure=-8.79/-9.10 yaw=1327 cmd=1527 actual=418 signed=0 rps=7092/2908:4321/3484 duty=23/6 pwm=PWM2:6/PWM1:23 motor=2:6/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=63/18 centerNum=63/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.78@100,95 dx=16.1 idx=3/23 dist=32/105 right=1:-23.90@114,75 dx=29.9 idx=0/12 dist=33/48 sel=1:-22.44@105,93 dx=20.7 idx=0/16 dist=32/84 edge=1:-20.74@104.0,90.0 dx=20.0 width=63.2 l=73,84 r=135,96
CxScan: raw_ref=80.0 edge=104.0,90.0 best_raw_x=130 best_err=-0.90 best_cxcy=103.2,119.7 scan=0:-44.0,10:-41.7,20:-39.3,30:-36.7,40:-33.9,50:-30.9,60:-27.7,70:-24.3,80:-20.7,90:-17.0,100:-13.1,110:-9.1,120:-5.0,130:-0.9,140:3.2
ATGSeedDiag: seed=1@14,108/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.5) imip=0/20 pass=10110 acc=-1 ipm=64.3,94.4 inv=47.8,60.2 | 7(37.3) imip=0/17 pass=10111 acc=-1 ipm=116.1,103.4 inv=131.3,73.0
frame=897 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=63/18 raw=156/59 sel=63/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=19.2/36.0/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(103,94) md=33/1/91 cxcy=84.0,119.6 guide=-22.11 atg=60.0/60.0/60.0 pure=-8.89/-9.20 yaw=1327 cmd=1527 actual=446 signed=0 rps=7092/2908:4419/3466 duty=23/6 pwm=PWM2:6/PWM1:23 motor=2:6/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=63/18 centerNum=63/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.81@100,95 dx=16.1 idx=3/23 dist=32/106 right=1:-24.44@115,75 dx=30.8 idx=0/12 dist=33/48 sel=1:-22.83@105,93 dx=21.0 idx=0/16 dist=32/84 edge=1:-21.21@104.5,90.0 dx=20.5 width=64.1 l=73,84 r=136,96
CxScan: raw_ref=80.0 edge=104.5,90.0 best_raw_x=135 best_err=0.63 best_cxcy=105.1,119.7 scan=0:-44.3,10:-42.0,20:-39.6,30:-37.0,40:-34.2,50:-31.3,60:-28.1,70:-24.8,80:-21.2,90:-17.5,100:-13.6,110:-9.6,120:-5.6,130:-1.4,140:2.7
ATGSeedDiag: seed=1@14,108/1@134,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(19.2) imip=42/62 pass=10100 acc=-1 ipm=150.1,57.8 inv=130.5,32.0 | 7(36.0) imip=0/17 pass=10111 acc=-1 ipm=116.5,103.4 inv=131.9,72.9
frame=898 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=63/18 raw=155/59 sel=63/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.5/35.6/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(103,94) md=33/1/90 cxcy=84.0,119.6 guide=-22.11 atg=60.0/60.0/60.0 pure=-8.99/-9.21 yaw=1327 cmd=1527 actual=480 signed=0 rps=7092/2908:4217/3306 duty=24/6 pwm=PWM2:6/PWM1:24 motor=2:6/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=63/18 centerNum=63/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.24@102,95 dx=17.7 idx=3/24 dist=33/105 right=1:-24.40@115,76 dx=30.5 idx=0/12 dist=33/48 sel=1:-22.74@105,93 dx=20.8 idx=0/16 dist=32/84 edge=1:-21.40@104.5,90.5 dx=20.5 width=64.3 l=73,84 r=136,97
CxScan: raw_ref=80.0 edge=104.5,90.5 best_raw_x=135 best_err=0.64 best_cxcy=105.1,119.7 scan=0:-44.5,10:-42.3,20:-39.9,30:-37.3,40:-34.5,50:-31.5,60:-28.3,70:-25.0,80:-21.4,90:-17.7,100:-13.8,110:-9.7,120:-5.6,130:-1.5,140:2.7
ATGSeedDiag: seed=1@14,108/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(18.5) imip=42/62 pass=10100 acc=-1 ipm=150.2,58.2 inv=130.8,32.2 | 7(35.6) imip=0/17 pass=10111 acc=-1 ipm=116.4,103.7 inv=132.2,73.4
frame=899 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=62/17 raw=155/59 sel=62/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.8/35.7/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(103,94) md=33/1/89 cxcy=84.0,119.6 guide=-22.18 atg=60.0/60.0/60.0 pure=-9.05/-9.18 yaw=1331 cmd=1531 actual=514 signed=0 rps=7098/2902:4740/3715 duty=23/6 pwm=PWM2:6/PWM1:23 motor=2:6/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=62/17 centerNum=62/17 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.36@102,95 dx=17.7 idx=3/24 dist=33/103 right=1:-24.40@114,76 dx=30.4 idx=0/12 dist=32/44 sel=1:-22.89@105,93 dx=20.9 idx=0/16 dist=32/82 edge=1:-21.40@104.5,90.5 dx=20.5 width=64.3 l=73,84 r=136,97
CxScan: raw_ref=80.0 edge=104.5,90.5 best_raw_x=135 best_err=0.64 best_cxcy=105.1,119.7 scan=0:-44.5,10:-42.3,20:-39.9,30:-37.3,40:-34.5,50:-31.5,60:-28.3,70:-25.0,80:-21.4,90:-17.7,100:-13.8,110:-9.7,120:-5.6,130:-1.5,140:2.7
ATGSeedDiag: seed=1@14,108/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=51(16.8) imip=41/61 pass=10100 acc=-1 ipm=148.0,57.9 inv=128.8,32.0 | 6(35.7) imip=0/16 pass=10111 acc=-1 ipm=114.7,105.2 inv=131.2,76.2
frame=901 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=62/17 raw=155/57 sel=62/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.5/33.2/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(104,94) md=33/1/89 cxcy=84.0,119.6 guide=-23.10 atg=60.0/60.0/60.0 pure=-9.08/-9.19 yaw=1386 cmd=1586 actual=583 signed=0 rps=7174/2826:4189/3492 duty=24/6 pwm=PWM2:6/PWM1:24 motor=2:6/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=62/17 centerNum=62/17 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.64@102,95 dx=17.9 idx=4/24 dist=33/102 right=1:-24.84@115,76 dx=30.8 idx=0/12 dist=32/44 sel=1:-23.77@106,93 dx=21.9 idx=0/16 dist=32/82 edge=1:-21.87@105.0,90.5 dx=21.0 width=63.3 l=74,84 r=136,97
CxScan: raw_ref=80.0 edge=105.0,90.5 best_raw_x=135 best_err=0.09 best_cxcy=105.1,119.7 scan=0:-44.8,10:-42.6,20:-40.2,30:-37.6,40:-34.9,50:-31.9,60:-28.8,70:-25.4,80:-21.9,90:-18.2,100:-14.3,110:-10.3,120:-6.2,130:-2.0,140:2.2
ATGSeedDiag: seed=1@13,108/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=51(15.5) imip=41/61 pass=10100 acc=-1 ipm=148.3,57.9 inv=129.0,32.1 | 6(33.2) imip=0/16 pass=10111 acc=-1 ipm=115.0,105.4 inv=132.0,76.7
frame=903 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=62/17 raw=155/56 sel=62/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.8/33.3/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(104,94) md=33/1/91 cxcy=84.0,119.6 guide=-23.17 atg=60.0/60.0/60.0 pure=-9.18/-9.23 yaw=1390 cmd=1590 actual=631 signed=0 rps=7180/2820:4252/3955 duty=24/5 pwm=PWM2:5/PWM1:24 motor=2:5/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=62/17 centerNum=62/17 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.74@101,96 dx=16.6 idx=4/23 dist=32/103 right=1:-25.37@116,76 dx=31.5 idx=0/12 dist=32/44 sel=1:-24.23@106,93 dx=22.2 idx=0/16 dist=32/84 edge=1:-22.53@105.5,91.0 dx=21.5 width=64.5 l=74,84 r=137,98
CxScan: raw_ref=80.0 edge=105.5,91.0 best_raw_x=135 best_err=-0.46 best_cxcy=105.1,119.7 scan=0:-45.4,10:-43.2,20:-40.8,30:-38.2,40:-35.5,50:-32.6,60:-29.4,70:-26.1,80:-22.5,90:-18.8,100:-14.9,110:-10.9,120:-6.8,130:-2.6,140:1.6
ATGSeedDiag: seed=1@13,108/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=55(16.8) imip=45/61 pass=10100 acc=-1 ipm=158.0,60.2 inv=139.0,33.1 | 6(33.3) imip=0/16 pass=10111 acc=-1 ipm=115.1,105.6 inv=132.4,76.9
frame=904 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=62/16 raw=155/55 sel=62/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.1/33.0/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(104,95) md=32/1/88 cxcy=84.0,119.6 guide=-23.86 atg=60.0/60.0/60.0 pure=-9.20/-9.36 yaw=1432 cmd=1632 actual=659 signed=0 rps=7236/2764:3998/3822 duty=24/5 pwm=PWM2:5/PWM1:24 motor=2:5/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=62/16 centerNum=62/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.95@101,97 dx=16.7 idx=4/23 dist=32/106 right=1:-27.29@119,76 dx=34.6 idx=0/13 dist=34/40 sel=1:-24.62@106,94 dx=22.4 idx=0/16 dist=32/82 edge=1:-21.77@104.5,91.5 dx=20.5 width=62.8 l=74,84 r=135,99
CxScan: raw_ref=80.0 edge=104.5,91.5 best_raw_x=135 best_err=0.65 best_cxcy=105.1,119.7 scan=0:-45.1,10:-42.9,20:-40.4,30:-37.8,40:-35.0,50:-32.0,60:-28.8,70:-25.4,80:-21.8,90:-18.0,100:-14.0,110:-9.9,120:-5.7,130:-1.5,140:2.8
ATGSeedDiag: seed=1@13,108/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.1) imip=0/20 pass=10110 acc=-1 ipm=64.8,94.8 inv=48.4,60.6 | 5(33.0) imip=0/15 pass=10111 acc=-1 ipm=113.4,107.1 inv=131.4,80.1
frame=905 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=61/16 raw=155/55 sel=61/41 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.8/32.4/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(105,95) md=33/1/88 cxcy=84.0,119.6 guide=-24.52 atg=60.0/60.0/60.0 pure=-9.37/-9.47 yaw=1471 cmd=1671 actual=686 signed=0 rps=7291/2709:4181/4017 duty=24/5 pwm=PWM2:5/PWM1:24 motor=2:5/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=61/16 centerNum=61/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=61/41 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.23@102,96 dx=18.0 idx=4/24 dist=32/101 right=1:-27.54@119,76 dx=34.9 idx=0/13 dist=34/40 sel=1:-25.03@107,94 dx=22.7 idx=0/16 dist=32/80 edge=1:-21.77@104.5,91.5 dx=20.5 width=62.8 l=74,84 r=135,99
CxScan: raw_ref=80.0 edge=104.5,91.5 best_raw_x=135 best_err=0.65 best_cxcy=105.1,119.7 scan=0:-45.1,10:-42.9,20:-40.4,30:-37.8,40:-35.0,50:-32.0,60:-28.8,70:-25.4,80:-21.8,90:-18.0,100:-14.0,110:-9.9,120:-5.7,130:-1.5,140:2.8
ATGSeedDiag: seed=1@13,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.8) imip=0/20 pass=10110 acc=-1 ipm=64.9,94.8 inv=48.6,60.7 | 5(32.4) imip=0/15 pass=10111 acc=-1 ipm=113.4,107.2 inv=131.7,80.3
frame=906 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=61/16 raw=155/54 sel=61/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.6/32.9/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(105,95) md=34/1/90 cxcy=84.0,119.6 guide=-23.25 atg=60.0/60.0/60.0 pure=-9.54/-9.50 yaw=1395 cmd=1595 actual=712 signed=0 rps=7186/2814:4111/3867 duty=24/5 pwm=PWM2:5/PWM1:24 motor=2:5/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=61/16 centerNum=61/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=61/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.30@101,97 dx=16.8 idx=4/23 dist=32/103 right=1:-27.93@119,76 dx=35.4 idx=0/13 dist=34/40 sel=1:-25.11@107,94 dx=22.7 idx=0/16 dist=32/82 edge=1:-21.97@104.5,92.0 dx=20.5 width=62.6 l=74,85 r=135,99
CxScan: raw_ref=80.0 edge=104.5,92.0 best_raw_x=135 best_err=0.66 best_cxcy=105.1,119.7 scan=0:-45.4,10:-43.1,20:-40.7,30:-38.1,40:-35.3,50:-32.3,60:-29.0,70:-25.6,80:-22.0,90:-18.1,100:-14.2,110:-10.0,120:-5.8,130:-1.5,140:2.8
ATGSeedDiag: seed=1@12,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=59(15.6) imip=49/60 pass=10100 acc=-1 ipm=167.5,66.4 inv=153.0,36.2 | 5(32.9) imip=0/15 pass=10111 acc=-1 ipm=113.5,107.3 inv=131.9,80.4
frame=907 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=61/16 raw=155/54 sel=61/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.7/32.4/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(105,96) md=33/1/89 cxcy=84.0,119.6 guide=-24.20 atg=60.0/60.0/60.0 pure=-9.54/-9.44 yaw=1452 cmd=1652 actual=739 signed=0 rps=7264/2736:4497/4008 duty=24/5 pwm=PWM2:5/PWM1:24 motor=2:5/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=61/16 centerNum=61/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=61/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.61@102,97 dx=18.2 idx=4/24 dist=32/101 right=1:-27.98@119,76 dx=35.4 idx=0/13 dist=34/40 sel=1:-25.32@107,95 dx=22.8 idx=0/16 dist=32/82 edge=1:-22.53@105.5,91.0 dx=21.5 width=61.1 l=76,83 r=135,99
CxScan: raw_ref=80.0 edge=105.5,91.0 best_raw_x=135 best_err=-0.46 best_cxcy=105.1,119.7 scan=0:-45.4,10:-43.2,20:-40.8,30:-38.2,40:-35.5,50:-32.6,60:-29.4,70:-26.1,80:-22.5,90:-18.8,100:-14.9,110:-10.9,120:-6.8,130:-2.6,140:1.6
ATGSeedDiag: seed=1@12,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(14.7) imip=44/60 pass=10100 acc=-1 ipm=156.8,62.4 inv=139.6,34.1 | 5(32.4) imip=0/15 pass=10111 acc=-1 ipm=113.6,107.3 inv=132.2,80.5
frame=908 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=61/16 raw=155/53 sel=61/41 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.4/30.4/0.0/0.0 dist=0 begin=0/2781 m0=(84,119) ml=(105,95) md=34/1/88 cxcy=84.0,119.6 guide=-24.02 atg=60.0/60.0/60.0 pure=-9.43/-9.40 yaw=1441 cmd=1641 actual=773 signed=0 rps=7249/2751:4843/4064 duty=23/5 pwm=PWM2:5/PWM1:23 motor=2:5/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=61/16 centerNum=61/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=61/41 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.57@101,97 dx=17.0 idx=4/23 dist=32/101 right=1:-27.99@119,76 dx=35.3 idx=0/13 dist=34/40 sel=1:-25.03@107,94 dx=22.6 idx=0/16 dist=32/80 edge=1:-21.97@104.5,92.0 dx=20.5 width=62.6 l=74,85 r=135,99
CxScan: raw_ref=80.0 edge=104.5,92.0 best_raw_x=135 best_err=0.66 best_cxcy=105.1,119.7 scan=0:-45.4,10:-43.1,20:-40.7,30:-38.1,40:-35.3,50:-32.3,60:-29.0,70:-25.6,80:-22.0,90:-18.1,100:-14.2,110:-10.0,120:-5.8,130:-1.5,140:2.8
ATGSeedDiag: seed=1@12,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(15.4) imip=40/60 pass=10100 acc=-1 ipm=147.2,60.0 inv=129.4,33.0 | 5(30.4) imip=0/15 pass=10111 acc=-1 ipm=113.6,107.5 inv=132.4,80.9

- stopped_at: 2026-06-22T07:37:01+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive117
```
