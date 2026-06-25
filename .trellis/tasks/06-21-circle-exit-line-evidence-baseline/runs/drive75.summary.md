# drive75

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive75-front_car_circle_drive75.log
- remote_log: /tmp/front_car_circle_drive75.log
- started_at: 2026-06-22T05:12:48+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive75 6
```

4140 /tmp/front_car_circle_drive75.log
frame=870 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=18/0 raw=148/0 sel=18/18 far=0/0 far_raw=0/0 l=1@19/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.5/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(109,99) md=33/1/37 cxcy=84.0,119.6 guide=-29.57 atg=60.0/60.0/60.0 pure=-9.42/-9.42 yaw=1774 cmd=1807 actual=1741 signed=0 rps=2523/7477:4837/6617 duty=3/22 pwm=PWM2:3/PWM1:22 motor=2:3/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@19/0@-1 nearNum=18/0 centerNum=18/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=18/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.23@107,102 dx=22.9 idx=7/15 dist=32/42 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-29.62@110,97 dx=26.0 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=86,89 r=-1,-1
ATGSeedDiag: seed=1@17,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=19(96.5) imip=9/29 pass=11111 acc=19 ipm=89.3,85.1 inv=81.7,49.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=871 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/0 raw=145/0 sel=17/17 far=0/0 far_raw=0/0 l=1@18/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.0/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(108,98) md=33/1/36 cxcy=84.0,119.6 guide=-28.52 atg=60.0/60.0/60.0 pure=-9.56/-9.56 yaw=1711 cmd=1702 actual=1720 signed=0 rps=2668/7332:4534/6076 duty=4/22 pwm=PWM2:4/PWM1:22 motor=2:4/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@18/0@-1 nearNum=17/0 centerNum=17/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=17/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-28.67@107,100 dx=23.4 idx=7/15 dist=33/38 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-28.83@110,96 dx=25.5 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=84,90 r=-1,-1
ATGSeedDiag: seed=1@17,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=18(91.0) imip=8/28 pass=11111 acc=18 ipm=87.6,86.7 inv=79.9,51.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=872 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/0 raw=141/0 sel=17/18 far=0/0 far_raw=0/0 l=1@18/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.7/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(107,99) md=32/1/36 cxcy=84.0,119.6 guide=-27.75 atg=60.0/60.0/60.0 pure=-9.15/-9.15 yaw=1665 cmd=1641 actual=1689 signed=0 rps=2751/7249:4754/6212 duty=4/22 pwm=PWM2:4/PWM1:22 motor=2:4/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@18/0@-1 nearNum=17/0 centerNum=17/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=17/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-27.86@106,101 dx=21.8 idx=6/14 dist=33/43 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-28.10@108,97 dx=24.4 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=85,90 r=-1,-1
ATGSeedDiag: seed=1@18,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=18(95.7) imip=8/28 pass=11111 acc=18 ipm=86.7,85.7 inv=78.6,50.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=874 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/0 raw=137/0 sel=16/17 far=0/0 far_raw=0/0 l=1@17/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.1/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(107,98) md=33/1/35 cxcy=84.0,119.6 guide=-27.23 atg=60.0/60.0/60.0 pure=-9.07/-9.07 yaw=1634 cmd=1671 actual=1597 signed=0 rps=2709/7291:5035/6459 duty=3/22 pwm=PWM2:3/PWM1:22 motor=2:3/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@17/0@-1 nearNum=16/0 centerNum=16/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=16/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-27.06@107,99 dx=22.6 idx=6/14 dist=35/40 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-26.88@108,96 dx=23.7 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=83,91 r=-1,-1
ATGSeedDiag: seed=1@18,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(97.1) imip=7/27 pass=11111 acc=17 ipm=85.0,87.2 inv=76.7,51.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=876 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/0 raw=131/0 sel=15/17 far=0/0 far_raw=0/0 l=1@16/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.6/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(107,97) md=33/1/36 cxcy=84.0,119.6 guide=-26.33 atg=60.0/60.0/60.0 pure=-8.57/-8.57 yaw=1580 cmd=1642 actual=1518 signed=0 rps=2750/7250:7808/9556 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@16/0@-1 nearNum=15/0 centerNum=15/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=15/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.08@106,98 dx=21.7 idx=6/13 dist=33/38 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-25.75@107,94 dx=23.3 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=82,92 r=-1,-1
ATGSeedDiag: seed=1@20,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=16(95.6) imip=6/26 pass=11111 acc=16 ipm=82.9,88.3 inv=74.1,53.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=877 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/0 raw=130/0 sel=14/15 far=0/0 far_raw=0/0 l=1@15/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.3/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(105,98) md=31/0/31 cxcy=84.0,119.6 guide=-25.09 atg=60.0/60.0/60.0 pure=-9.26/-9.26 yaw=1505 cmd=1531 actual=1479 signed=0 rps=2901/7099:6169/7532 duty=2/20 pwm=PWM2:2/PWM1:20 motor=2:2/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@15/0@-1 nearNum=14/0 centerNum=14/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=14/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.74@106,97 dx=21.9 idx=6/13 dist=34/34 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-25.72@105,98 dx=21.4 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=80,94 r=-1,-1
ATGSeedDiag: seed=1@20,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=15(95.3) imip=5/25 pass=11111 acc=15 ipm=82.8,90.5 inv=74.0,55.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=13/0 raw=123/0 sel=13/15 far=0/0 far_raw=0/0 l=1@14/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.9/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(104,98) md=30/0/30 cxcy=84.0,119.6 guide=-24.04 atg=60.0/60.0/60.0 pure=-8.78/-8.78 yaw=1442 cmd=1451 actual=1434 signed=0 rps=3012/6988:4880/5943 duty=4/21 pwm=PWM2:4/PWM1:21 motor=2:4/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@14/0@-1 nearNum=13/0 centerNum=13/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=13/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-24.08@105,97 dx=20.6 idx=5/12 dist=34/34 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-24.13@104,98 dx=20.1 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=79,95 r=-1,-1
ATGSeedDiag: seed=1@22,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=14(94.9) imip=4/24 pass=11111 acc=14 ipm=81.0,91.2 inv=71.7,56.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/0 raw=120/0 sel=12/15 far=0/0 far_raw=0/0 l=1@13/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.0/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(103,98) md=30/0/30 cxcy=84.0,119.6 guide=-23.17 atg=60.0/60.0/60.0 pure=-8.69/-8.69 yaw=1390 cmd=1400 actual=1380 signed=0 rps=3081/6919:4818/5684 duty=5/21 pwm=PWM2:5/PWM1:21 motor=2:5/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@13/0@-1 nearNum=12/0 centerNum=12/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.33@103,98 dx=19.2 idx=4/11 dist=32/32 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-23.33@103,98 dx=19.1 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=77,97 r=-1,-1
ATGSeedDiag: seed=1@23,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(96.0) imip=3/23 pass=11111 acc=13 ipm=79.8,92.9 inv=70.0,58.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/0 raw=119/0 sel=12/15 far=0/0 far_raw=0/0 l=1@13/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=98.9/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(103,98) md=30/0/30 cxcy=84.0,119.6 guide=-22.93 atg=60.0/60.0/60.0 pure=-8.49/-8.49 yaw=1376 cmd=1419 actual=1333 signed=0 rps=3055/6945:4896/5878 duty=4/21 pwm=PWM2:4/PWM1:21 motor=2:4/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@13/0@-1 nearNum=12/0 centerNum=12/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.87@103,97 dx=19.2 idx=4/11 dist=32/32 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-22.92@103,98 dx=18.9 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=77,97 r=-1,-1
ATGSeedDiag: seed=1@23,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(98.9) imip=3/23 pass=11111 acc=13 ipm=79.6,92.8 inv=69.7,58.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/0 raw=117/0 sel=11/13 far=0/0 far_raw=0/0 l=1@12/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.7/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(102,101) md=27/0/27 cxcy=84.0,119.6 guide=-23.33 atg=60.0/60.0/60.0 pure=-9.07/-9.07 yaw=1400 cmd=1504 actual=1296 signed=0 rps=2939/7061:4659/5842 duty=4/22 pwm=PWM2:4/PWM1:22 motor=2:4/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@12/0@-1 nearNum=11/0 centerNum=11/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.87@102,100 dx=18.1 idx=4/10 dist=28/28 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-22.87@102,101 dx=17.6 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=76,98 r=-1,-1
ATGSeedDiag: seed=1@24,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(96.7) imip=2/22 pass=11111 acc=12 ipm=78.7,94.6 inv=68.4,60.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/0 raw=115/0 sel=11/15 far=0/0 far_raw=0/0 l=1@12/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.7/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(102,98) md=30/0/30 cxcy=84.0,119.6 guide=-21.81 atg=60.0/59.0/59.0 pure=-8.31/-8.31 yaw=1309 cmd=1355 actual=1263 signed=0 rps=3143/6857:4862/6354 duty=5/20 pwm=PWM2:5/PWM1:20 motor=2:5/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@12/0@-1 nearNum=11/0 centerNum=11/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.25@102,98 dx=18.4 idx=3/10 dist=31/31 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-22.25@102,98 dx=18.3 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=76,98 r=-1,-1
ATGSeedDiag: seed=1@25,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(97.7) imip=2/22 pass=11111 acc=12 ipm=78.1,94.1 inv=67.5,59.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=10/0 raw=113/0 sel=10/13 far=0/0 far_raw=0/0 l=1@11/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.0/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(100,101) md=26/0/26 cxcy=84.0,119.6 guide=-20.98 atg=60.0/55.0/55.0 pure=-8.60/-8.60 yaw=1259 cmd=1283 actual=1234 signed=0 rps=3241/6759:5040/6519 duty=5/20 pwm=PWM2:5/PWM1:20 motor=2:5/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@11/0@-1 nearNum=10/0 centerNum=10/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.35@101,99 dx=17.1 idx=3/9 dist=29/29 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-21.39@100,101 dx=16.4 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=75,100 r=-1,-1
ATGSeedDiag: seed=1@26,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(96.0) imip=1/21 pass=11111 acc=11 ipm=77.5,96.0 inv=66.5,62.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/0 raw=108/0 sel=9/13 far=0/0 far_raw=0/0 l=1@10/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.8/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(99,100) md=27/0/27 cxcy=84.0,119.6 guide=-19.34 atg=60.0/48.0/48.0 pure=-8.09/-8.09 yaw=1160 cmd=1148 actual=1172 signed=0 rps=3426/6574:5394/6509 duty=5/19 pwm=PWM2:5/PWM1:19 motor=2:5/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@10/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.83@100,98 dx=16.0 idx=2/8 dist=30/30 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-19.98@99,100 dx=15.4 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=74,101 r=-1,-1
ATGSeedDiag: seed=1@28,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(96.8) imip=0/20 pass=11111 acc=10 ipm=76.4,97.3 inv=64.7,63.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/0 raw=107/0 sel=9/14 far=0/0 far_raw=0/0 l=1@10/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.4/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(100,98) md=28/0/28 cxcy=84.0,119.6 guide=-19.68 atg=60.0/47.0/47.0 pure=-7.37/-7.37 yaw=1181 cmd=1218 actual=1144 signed=0 rps=3331/6669:5247/6116 duty=5/20 pwm=PWM2:5/PWM1:20 motor=2:5/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@10/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/14 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.21@100,97 dx=15.8 idx=2/8 dist=30/30 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-19.22@100,98 dx=15.8 idx=0/13 dist=26/26 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=74,101 r=-1,-1
ATGSeedDiag: seed=1@28,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(97.4) imip=0/20 pass=11111 acc=10 ipm=75.7,97.2 inv=63.7,63.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/0 raw=106/0 sel=8/12 far=0/0 far_raw=0/0 l=1@9/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.2/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(98,101) md=24/0/24 cxcy=84.0,119.6 guide=-18.54 atg=60.0/43.0/43.0 pure=-7.77/-7.77 yaw=1112 cmd=1117 actual=1108 signed=0 rps=3470/6530:5553/6140 duty=5/19 pwm=PWM2:5/PWM1:19 motor=2:5/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@9/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.50@99,99 dx=14.6 idx=2/7 dist=28/28 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-18.67@98,101 dx=14.1 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=73,103 r=-1,-1
ATGSeedDiag: seed=1@29,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(95.2) imip=0/19 pass=11111 acc=9 ipm=75.5,99.3 inv=63.1,66.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/0 raw=103/0 sel=8/14 far=0/0 far_raw=0/0 l=1@9/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=99.3/0.0/0.0/0.0 dist=0 begin=0/2639 m0=(84,119) ml=(98,97) md=29/0/29 cxcy=84.0,119.6 guide=-17.01 atg=60.0/38.0/38.0 pure=-6.84/-6.84 yaw=1021 cmd=981 actual=1061 signed=0 rps=3656/6344:5340/5661 duty=6/19 pwm=PWM2:6/PWM1:19 motor=2:6/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@9/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/14 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.60@99,97 dx=14.6 idx=1/7 dist=31/31 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-17.64@98,97 dx=14.5 idx=0/13 dist=26/26 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=73,103 r=-1,-1
ATGSeedDiag: seed=1@30,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(99.3) imip=0/19 pass=11111 acc=9 ipm=75.1,98.7 inv=62.6,65.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T05:13:01+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive75
```
