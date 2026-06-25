# drive70

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive70-front_car_circle_drive70.log
- remote_log: /tmp/front_car_circle_drive70.log
- started_at: 2026-06-22T04:45:55+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive70 6
```

1494 /tmp/front_car_circle_drive70.log
ATGSeedDiag: seed=1@52,108/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(17.9) imip=0/4 pass=10111 acc=-1 ipm=113.9,114.9 inv=145.9,99.9
frame=304 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/4 raw=0/18 sel=4/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/10.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(105,91) md=34/1/38 cxcy=84.0,119.6 guide=-22.41 atg=60.0/60.0/60.0 pure=-7.70/-7.70 yaw=1345 cmd=1545 actual=-1696 signed=0 rps=2883/7117:2211/12181 duty=7/13 pwm=PWM2:7/PWM1:13 motor=2:7/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/4 centerNum=0/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-22.13@105,90 dx=21.2 idx=0/1 dist=36/40 sel=1:-23.08@106,90 dx=22.4 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=117,115
ATGSeedDiag: seed=1@52,108/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(10.9) imip=0/3 pass=10111 acc=-1 ipm=114.4,115.0 inv=147.5,100.3
frame=305 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/4 raw=0/18 sel=4/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/11.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(105,92) md=33/1/38 cxcy=84.0,119.6 guide=-22.57 atg=60.0/60.0/60.0 pure=-7.77/-7.77 yaw=1354 cmd=1554 actual=-1719 signed=0 rps=2870/7130:2296/12270 duty=7/13 pwm=PWM2:7/PWM1:13 motor=2:7/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/4 centerNum=0/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-22.62@106,91 dx=21.7 idx=0/1 dist=36/40 sel=1:-23.37@107,90 dx=22.7 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=117,115
ATGSeedDiag: seed=1@52,108/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(11.1) imip=0/3 pass=10111 acc=-1 ipm=114.4,115.2 inv=147.8,100.9
frame=307 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/4 raw=0/17 sel=4/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/5.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,92) md=34/1/40 cxcy=84.0,119.6 guide=-23.43 atg=60.0/60.0/60.0 pure=-8.26/-8.26 yaw=1406 cmd=1606 actual=-1729 signed=0 rps=2799/7201:2563/11646 duty=7/14 pwm=PWM2:7/PWM1:14 motor=2:7/1:14
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/4 centerNum=0/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-24.14@107,91 dx=23.4 idx=0/1 dist=37/41 sel=1:-24.12@107,91 dx=23.3 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=117,115
ATGSeedDiag: seed=1@52,108/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(5.8) imip=0/3 pass=10111 acc=-1 ipm=114.9,115.6 inv=149.7,102.2
frame=308 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/4 raw=0/17 sel=4/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/4.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,93) md=33/1/40 cxcy=84.0,119.6 guide=-23.90 atg=60.0/60.0/60.0 pure=-8.35/-8.35 yaw=1434 cmd=1634 actual=-1729 signed=0 rps=2760/7240:2777/11393 duty=6/15 pwm=PWM2:6/PWM1:15 motor=2:6/1:15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/4 centerNum=0/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-24.78@108,91 dx=24.1 idx=0/1 dist=38/42 sel=1:-24.66@108,91 dx=23.7 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=117,116
ATGSeedDiag: seed=1@52,108/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(4.8) imip=0/3 pass=10111 acc=-1 ipm=114.8,115.9 inv=150.2,102.9
frame=309 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/3 raw=12/16 sel=3/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,93) md=34/1/38 cxcy=84.0,119.6 guide=-24.30 atg=60.0/60.0/60.0 pure=-8.12/-8.12 yaw=1458 cmd=1658 actual=-1727 signed=0 rps=2728/7272:2826/10566 duty=6/16 pwm=PWM2:6/PWM1:16 motor=2:6/1:16
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/3 centerNum=2/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:34.18@54,98 dx=-30.5 idx=0/1 dist=2/2 right=1:-25.41@109,91 dx=24.8 idx=0/1 dist=38/40 sel=1:-25.14@108,91 dx=24.1 idx=0/16 dist=32/34 edge=1:-18.21@92.5,117.0 dx=8.5 width=45.0 l=70,118 r=115,116
CxScan: raw_ref=80.0 edge=92.5,117.0 best_raw_x=100 best_err=-1.80 best_cxcy=91.7,119.6 scan=0:-56.9,10:-54.1,20:-50.9,30:-47.2,40:-42.9,50:-37.9,60:-32.1,70:-25.6,80:-18.2,90:-10.2,100:-1.8,110:6.7,120:14.8,130:22.4,140:29.2
ATGSeedDiag: seed=1@52,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(0.5) imip=0/2 pass=10111 acc=-1 ipm=113.0,116.3 inv=147.2,104.6
frame=310 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/3 raw=12/16 sel=3/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/1.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,93) md=34/1/38 cxcy=84.0,119.6 guide=-25.00 atg=60.0/60.0/60.0 pure=-8.18/-8.18 yaw=1500 cmd=1700 actual=-1734 signed=0 rps=2670/7330:3091/11020 duty=5/15 pwm=PWM2:5/PWM1:15 motor=2:5/1:15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/3 centerNum=2/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:34.18@54,98 dx=-30.5 idx=0/1 dist=2/2 right=1:-26.01@109,91 dx=25.5 idx=0/1 dist=39/41 sel=1:-25.61@109,92 dx=24.5 idx=0/16 dist=32/34 edge=1:-18.21@92.5,117.0 dx=8.5 width=45.0 l=70,118 r=115,116
CxScan: raw_ref=80.0 edge=92.5,117.0 best_raw_x=100 best_err=-1.80 best_cxcy=91.7,119.6 scan=0:-56.9,10:-54.1,20:-50.9,30:-47.2,40:-42.9,50:-37.9,60:-32.1,70:-25.6,80:-18.2,90:-10.2,100:-1.8,110:6.7,120:14.8,130:22.4,140:29.2
ATGSeedDiag: seed=1@52,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(1.9) imip=0/2 pass=10111 acc=-1 ipm=113.0,116.4 inv=147.2,104.9
frame=312 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/3 raw=0/15 sel=3/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/2.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,94) md=33/1/39 cxcy=84.0,119.6 guide=-25.18 atg=60.0/60.0/60.0 pure=-8.22/-8.22 yaw=1511 cmd=1711 actual=-1718 signed=0 rps=2656/7344:3270/11863 duty=5/14 pwm=PWM2:5/PWM1:14 motor=2:5/1:14
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/3 centerNum=0/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-26.46@110,91 dx=26.0 idx=0/1 dist=39/41 sel=1:-25.97@109,92 dx=24.8 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=116,116
ATGSeedDiag: seed=1@53,108/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(2.3) imip=0/2 pass=10111 acc=-1 ipm=113.4,116.4 inv=148.2,104.9
frame=313 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/3 raw=0/15 sel=3/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/2.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,94) md=33/1/38 cxcy=84.0,119.6 guide=-25.33 atg=60.0/60.0/60.0 pure=-8.28/-8.28 yaw=1520 cmd=1720 actual=-1708 signed=0 rps=2643/7357:3154/11479 duty=5/15 pwm=PWM2:5/PWM1:15 motor=2:5/1:15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/3 centerNum=0/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-26.82@110,91 dx=26.3 idx=0/1 dist=39/41 sel=1:-26.29@109,92 dx=25.0 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=116,116
ATGSeedDiag: seed=1@53,108/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(2.7) imip=0/2 pass=10111 acc=-1 ipm=113.4,116.6 inv=148.6,105.5
frame=314 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/3 raw=0/14 sel=3/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/1.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,94) md=34/1/40 cxcy=84.0,119.6 guide=-25.97 atg=60.0/60.0/60.0 pure=-8.66/-8.66 yaw=1558 cmd=1758 actual=-1695 signed=0 rps=2590/7410:3164/11461 duty=5/15 pwm=PWM2:5/PWM1:15 motor=2:5/1:15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/3 centerNum=0/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-27.90@112,91 dx=27.6 idx=0/1 dist=40/42 sel=1:-27.10@110,93 dx=25.6 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=116,116
ATGSeedDiag: seed=1@53,108/1@143,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(1.1) imip=0/2 pass=10111 acc=-1 ipm=113.8,116.6 inv=149.6,105.5
frame=316 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/3 raw=0/12 sel=3/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/4.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,96) md=32/1/41 cxcy=84.0,119.6 guide=-26.60 atg=60.0/60.0/60.0 pure=-8.67/-8.67 yaw=1596 cmd=1796 actual=-1646 signed=0 rps=2538/7462:3029/12055 duty=5/15 pwm=PWM2:5/PWM1:15 motor=2:5/1:15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/3 centerNum=0/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-28.08@112,91 dx=27.8 idx=0/1 dist=40/42 sel=1:-27.27@110,93 dx=25.7 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=117,116
ATGSeedDiag: seed=1@53,108/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(4.8) imip=0/2 pass=10111 acc=-1 ipm=114.7,116.7 inv=151.7,105.7
frame=317 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=37/2 raw=129/11 sel=37/73 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=175.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(117,117) md=33/0/150 cxcy=84.0,119.6 guide=-51.12 atg=60.0/14.0/0.0 pure=-10.97/-2.84 yaw=3067 cmd=3200 actual=-1605 signed=0 rps=614/9386:3010/12543 duty=0/22 pwm=PWM2:0/PWM1:22 motor=2:0/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=37/2 centerNum=37/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=37/73 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-49.73@109,122 dx=24.6 idx=3/10 dist=33/170 right=1:-30.02@114,91 dx=30.1 idx=0/1 dist=2/2 sel=1:-50.68@113,119 dx=28.7 idx=0/16 dist=32/144 edge=1:-34.01@109.5,105.0 dx=25.5 width=26.4 l=104,93 r=115,117
CxScan: raw_ref=80.0 edge=109.5,105.0 best_raw_x=140 best_err=-3.78 best_cxcy=107.0,119.7 scan=0:-56.3,10:-54.4,20:-52.2,30:-49.9,40:-47.3,50:-44.5,60:-41.3,70:-37.8,80:-34.0,90:-29.8,100:-25.2,110:-20.3,120:-15.0,130:-9.5,140:-3.8
ATGSeedDiag: seed=1@54,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=19(175.9) imip=9/29 pass=11010 acc=-1 ipm=101.5,94.5 inv=100.9,59.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=318 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/2 raw=0/8 sel=2/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(109,95) md=34/1/38 cxcy=84.0,119.6 guide=-27.44 atg=60.0/60.0/60.0 pure=-8.87/-8.87 yaw=1646 cmd=1846 actual=-1553 signed=0 rps=2470/7530:2766/11968 duty=5/15 pwm=PWM2:5/PWM1:15 motor=2:5/1:15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/2 centerNum=0/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-29.72@114,91 dx=29.8 idx=0/1 dist=41/41 sel=1:-28.48@111,94 dx=26.6 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=116,117
ATGSeedDiag: seed=1@54,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=319 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/1 raw=0/7 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-8.87/-8.87 yaw=0 cmd=0 actual=-1316 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@54,108/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=320 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/1 raw=170/6 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-8.87/-8.87 yaw=0 cmd=0 actual=-1246 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@55,108/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=321 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=12/6 sel=2/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(56,99) md=33/1/33 cxcy=84.0,119.6 guide=31.58 atg=-60.0/-60.0/-60.0 pure=10.65/10.65 yaw=-1895 cmd=-2095 actual=-1200 signed=0 rps=7871/2129:1763/11502 duty=25/0 pwm=PWM2:25/PWM1:0 motor=2:25/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:33.16@55,98 dx=-29.4 idx=0/1 dist=37/37 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:32.45@56,99 dx=-27.9 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=71,118 r=-1,-1
ATGSeedDiag: seed=1@54,108/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T04:46:07+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive70
```
