# drive95

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive95-front_car_circle_drive95.log
- remote_log: /tmp/front_car_circle_drive95.log
- started_at: 2026-06-22T06:36:28+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive95 6
```

4657 /tmp/front_car_circle_drive95.log
ATGLptDiag: best=25(91.4) imip=15/35 pass=11110 acc=-1 ipm=98.7,78.3 inv=91.1,44.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=875 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=71/0 raw=170/0 sel=71/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.6/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(112,100) md=33/1/208 cxcy=84.0,119.6 guide=-32.82 atg=60.0/2.0/-1.0 pure=-6.25/-0.72 yaw=1969 cmd=2109 actual=1829 signed=0 rps=2110/7890:4389/6312 duty=2/25 pwm=PWM2:2/PWM1:25 motor=2:2/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=71/0 centerNum=71/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=71/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.75@109,103 dx=24.6 idx=8/19 dist=32/220 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-33.36@113,98 dx=29.4 idx=0/16 dist=32/188 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=97,80 r=-1,-1
ATGSeedDiag: seed=1@11,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(94.6) imip=15/35 pass=11110 acc=-1 ipm=97.9,78.1 inv=90.2,44.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=876 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=71/0 raw=170/0 sel=71/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.6/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(110,101) md=32/1/207 cxcy=84.0,119.6 guide=-32.24 atg=60.0/1.0/-2.0 pure=-6.08/-0.52 yaw=1935 cmd=2037 actual=1832 signed=0 rps=2209/7791:4325/6041 duty=2/25 pwm=PWM2:2/PWM1:25 motor=2:2/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=71/0 centerNum=71/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=71/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.77@109,102 dx=25.4 idx=8/19 dist=32/222 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-32.91@113,98 dx=29.2 idx=0/16 dist=32/188 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=97,77 r=-1,-1
ATGSeedDiag: seed=1@11,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=24(93.6) imip=14/34 pass=11110 acc=-1 ipm=97.1,79.7 inv=89.6,45.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=877 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=23/0 raw=167/0 sel=23/21 far=0/0 far_raw=0/0 l=1@24/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.0/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(110,101) md=32/1/45 cxcy=84.0,119.6 guide=-31.46 atg=60.0/60.0/60.0 pure=-9.03/-9.03 yaw=1888 cmd=1977 actual=1798 signed=0 rps=2291/7709:4116/5652 duty=3/25 pwm=PWM2:3/PWM1:25 motor=2:3/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@24/0@-1 nearNum=23/0 centerNum=23/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=23/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.70@110,100 dx=26.4 idx=8/19 dist=34/49 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-32.23@113,97 dx=28.7 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=94,83 r=-1,-1
ATGSeedDiag: seed=1@11,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=24(95.0) imip=14/34 pass=11111 acc=24 ipm=95.6,78.7 inv=87.7,44.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=878 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=22/1 raw=163/4 sel=22/20 far=0/0 far_raw=0/0 l=1@23/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.2/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(109,100) md=32/1/43 cxcy=84.0,119.6 guide=-31.04 atg=60.0/60.0/60.0 pure=-9.12/-9.12 yaw=1862 cmd=1939 actual=1785 signed=0 rps=2342/7658:4301/5863 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@23/0@-1 nearNum=22/1 centerNum=22/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.63@109,101 dx=24.7 idx=8/18 dist=31/46 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-31.51@112,97 dx=28.2 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=92,83 r=-1,-1
ATGSeedDiag: seed=1@12,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(93.2) imip=13/33 pass=11111 acc=23 ipm=94.3,79.7 inv=86.5,45.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=66/1 raw=161/5 sel=66/90 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.8/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(109,100) md=32/1/196 cxcy=84.0,119.6 guide=-30.35 atg=60.0/0.0/-9.0 pure=-5.17/0.31 yaw=1821 cmd=1873 actual=1770 signed=0 rps=2434/7566:4239/5847 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=66/1 centerNum=66/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=66/90 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.52@110,99 dx=25.5 idx=8/18 dist=33/208 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-30.97@112,96 dx=27.8 idx=0/16 dist=32/178 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=88,76 r=-1,-1
ATGSeedDiag: seed=1@12,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=22(91.8) imip=12/32 pass=11110 acc=-1 ipm=92.8,81.4 inv=85.1,46.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=21/1 raw=159/5 sel=21/20 far=0/0 far_raw=0/0 l=1@22/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.6/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(109,100) md=32/1/43 cxcy=84.0,119.6 guide=-30.10 atg=60.0/60.0/60.0 pure=-8.86/-8.86 yaw=1806 cmd=1867 actual=1745 signed=0 rps=2442/7558:4500/6250 duty=3/23 pwm=PWM2:3/PWM1:23 motor=2:3/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@22/0@-1 nearNum=21/1 centerNum=21/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.41@110,98 dx=26.2 idx=8/18 dist=35/45 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-30.59@111,96 dx=27.5 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=90,85 r=-1,-1
ATGSeedDiag: seed=1@12,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=22(96.6) imip=12/32 pass=11111 acc=22 ipm=92.1,81.0 inv=84.2,46.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=20/1 raw=155/6 sel=20/19 far=0/0 far_raw=0/0 l=1@21/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.3/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(110,98) md=34/1/41 cxcy=84.0,119.6 guide=-29.77 atg=60.0/60.0/60.0 pure=-9.07/-9.07 yaw=1786 cmd=1873 actual=1699 signed=0 rps=2434/7566:4474/6082 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@21/0@-1 nearNum=20/1 centerNum=20/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=20/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.70@109,100 dx=24.6 idx=8/17 dist=33/43 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-30.13@111,96 dx=27.1 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=88,86 r=-1,-1
ATGSeedDiag: seed=1@13,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=21(94.3) imip=11/31 pass=11111 acc=21 ipm=91.2,82.4 inv=83.6,47.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=20/1 raw=154/6 sel=20/20 far=0/0 far_raw=0/0 l=1@21/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.6/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(109,98) md=33/1/42 cxcy=84.0,119.6 guide=-29.21 atg=60.0/60.0/60.0 pure=-8.61/-8.61 yaw=1753 cmd=1848 actual=1658 signed=0 rps=2468/7532:4816/6306 duty=2/23 pwm=PWM2:2/PWM1:23 motor=2:2/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@21/0@-1 nearNum=20/1 centerNum=20/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=20/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.33@109,99 dx=24.8 idx=7/17 dist=35/45 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-29.51@110,96 dx=26.4 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=88,86 r=-1,-1
ATGSeedDiag: seed=1@13,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=21(96.6) imip=11/31 pass=11111 acc=21 ipm=90.1,81.9 inv=82.2,47.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=19/1 raw=152/7 sel=19/18 far=0/0 far_raw=0/0 l=1@20/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.2/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(109,98) md=33/1/37 cxcy=84.0,119.6 guide=-28.49 atg=60.0/60.0/60.0 pure=-9.06/-9.06 yaw=1710 cmd=1797 actual=1622 signed=0 rps=2537/7463:4754/6124 duty=3/23 pwm=PWM2:3/PWM1:23 motor=2:3/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@20/0@-1 nearNum=19/1 centerNum=19/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=19/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-28.74@109,97 dx=25.1 idx=7/17 dist=35/40 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-28.80@110,96 dx=25.9 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=86,87 r=-1,-1
ATGSeedDiag: seed=1@13,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=20(94.2) imip=10/30 pass=11111 acc=20 ipm=89.4,83.7 inv=81.6,48.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=18/2 raw=147/8 sel=18/17 far=0/0 far_raw=0/0 l=1@19/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.4/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(108,97) md=33/1/35 cxcy=84.0,119.6 guide=-27.72 atg=60.0/60.0/60.0 pure=-9.06/-9.06 yaw=1663 cmd=1770 actual=1556 signed=0 rps=2574/7426:5087/6208 duty=2/23 pwm=PWM2:2/PWM1:23 motor=2:2/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@19/0@-1 nearNum=18/2 centerNum=18/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=18/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-27.62@108,97 dx=23.7 idx=7/16 dist=34/39 right=1:-20.14@101,95 dx=17.5 idx=0/1 dist=2/2 sel=1:-27.65@109,95 dx=25.1 idx=0/16 dist=32/32 edge=1:-22.36@101.0,101.5 dx=17.0 width=43.4 l=84,88 r=118,115
CxScan: raw_ref=80.0 edge=101.0,101.5 best_raw_x=125 best_err=0.36 best_cxcy=101.3,119.7 scan=0:-49.3,10:-46.9,20:-44.2,30:-41.3,40:-38.2,50:-34.7,60:-30.9,70:-26.8,80:-22.4,90:-17.7,100:-12.7,110:-7.6,120:-2.3,130:3.0,140:8.2
ATGSeedDiag: seed=1@14,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=19(94.4) imip=9/29 pass=11111 acc=19 ipm=87.6,84.7 inv=79.6,49.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=886 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=18/2 raw=145/10 sel=18/18 far=0/0 far_raw=0/0 l=1@19/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=98.1/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(108,97) md=33/1/37 cxcy=84.0,119.6 guide=-27.30 atg=60.0/60.0/60.0 pure=-8.59/-8.59 yaw=1638 cmd=1775 actual=1501 signed=0 rps=2567/7433:4809/5654 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@19/0@-1 nearNum=18/2 centerNum=18/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=18/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.90@106,100 dx=21.8 idx=7/15 dist=32/42 right=1:-19.50@101,96 dx=16.7 idx=0/1 dist=2/2 sel=1:-27.20@109,95 dx=24.7 idx=0/16 dist=32/34 edge=1:-22.96@101.5,101.5 dx=17.5 width=42.6 l=85,88 r=118,115
CxScan: raw_ref=80.0 edge=101.5,101.5 best_raw_x=125 best_err=-0.33 best_cxcy=101.3,119.7 scan=0:-49.6,10:-47.2,20:-44.6,30:-41.7,40:-38.6,50:-35.1,60:-31.4,70:-27.3,80:-23.0,90:-18.3,100:-13.4,110:-8.2,120:-3.0,130:2.3,140:7.6
ATGSeedDiag: seed=1@14,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=19(98.1) imip=9/29 pass=11111 acc=19 ipm=86.5,84.2 inv=78.2,49.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/3 raw=140/14 sel=17/17 far=0/0 far_raw=0/0 l=1@18/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.7/1.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(107,96) md=33/1/35 cxcy=84.0,119.6 guide=-26.20 atg=60.0/60.0/60.0 pure=-8.68/-8.68 yaw=1572 cmd=1666 actual=1478 signed=0 rps=2717/7283:4937/5818 duty=3/23 pwm=PWM2:3/PWM1:23 motor=2:3/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@18/0@-1 nearNum=17/3 centerNum=17/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=17/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.48@107,97 dx=22.8 idx=7/15 dist=35/40 right=1:-20.75@102,94 dx=18.4 idx=0/2 dist=4/4 sel=1:-26.46@108,94 dx=24.2 idx=0/16 dist=32/32 edge=1:-22.71@101.5,101.0 dx=17.5 width=44.1 l=83,89 r=120,113
CxScan: raw_ref=80.0 edge=101.5,101.0 best_raw_x=125 best_err=-0.33 best_cxcy=101.3,119.7 scan=0:-49.3,10:-46.9,20:-44.3,30:-41.4,40:-38.2,50:-34.8,60:-31.1,70:-27.1,80:-22.7,90:-18.1,100:-13.2,110:-8.1,120:-2.9,130:2.3,140:7.5
ATGSeedDiag: seed=1@15,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=18(94.7) imip=8/28 pass=11111 acc=18 ipm=85.0,85.4 inv=76.5,50.2 | 1(1.0) imip=0/2 pass=10111 acc=-1 ipm=118.3,115.0 inv=156.0,100.2
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/4 raw=140/17 sel=17/18 far=0/0 far_raw=0/0 l=1@18/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.8/3.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(107,96) md=33/1/37 cxcy=84.0,119.6 guide=-26.20 atg=60.0/60.0/60.0 pure=-8.26/-8.26 yaw=1572 cmd=1684 actual=1460 signed=0 rps=2692/7308:4557/5567 duty=4/23 pwm=PWM2:4/PWM1:23 motor=2:4/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@18/0@-1 nearNum=17/4 centerNum=17/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=17/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.24@107,96 dx=22.9 idx=7/15 dist=35/40 right=1:-22.03@104,92 dx=20.3 idx=0/3 dist=6/6 sel=1:-26.19@108,94 dx=24.0 idx=0/16 dist=32/34 edge=1:-23.87@102.5,101.0 dx=18.5 width=44.8 l=83,90 r=122,112
CxScan: raw_ref=80.0 edge=102.5,101.0 best_raw_x=130 best_err=0.92 best_cxcy=103.2,119.7 scan=0:-49.8,10:-47.5,20:-45.0,30:-42.2,40:-39.1,50:-35.7,60:-32.1,70:-28.1,80:-23.9,90:-19.3,100:-14.5,110:-9.5,120:-4.3,130:0.9,140:6.1
ATGSeedDiag: seed=1@15,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=18(97.8) imip=8/28 pass=11111 acc=18 ipm=84.7,85.5 inv=76.2,50.3 | 2(3.0) imip=0/3 pass=10111 acc=-1 ipm=120.0,113.4 inv=156.0,95.4
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/0 raw=136/0 sel=16/17 far=0/0 far_raw=0/0 l=1@17/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.4/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(106,97) md=32/1/34 cxcy=84.0,119.6 guide=-25.68 atg=60.0/60.0/60.0 pure=-8.58/-8.58 yaw=1541 cmd=1635 actual=1446 signed=0 rps=2759/7241:4552/6003 duty=4/23 pwm=PWM2:4/PWM1:23 motor=2:4/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@17/0@-1 nearNum=16/0 centerNum=16/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=16/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.72@105,98 dx=21.5 idx=6/14 dist=33/38 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-25.54@107,95 dx=23.0 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=82,91 r=-1,-1
ATGSeedDiag: seed=1@16,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(97.4) imip=7/27 pass=11111 acc=17 ipm=84.2,86.9 inv=75.6,51.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/0 raw=134/0 sel=16/17 far=0/0 far_raw=0/0 l=1@17/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.8/0.0/0.0/0.0 dist=0 begin=0/2614 m0=(84,119) ml=(106,96) md=33/1/35 cxcy=84.0,119.6 guide=-25.15 atg=60.0/60.0/60.0 pure=-8.32/-8.32 yaw=1509 cmd=1607 actual=1412 signed=0 rps=2798/7202:4338/6013 duty=4/22 pwm=PWM2:4/PWM1:22 motor=2:4/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@17/0@-1 nearNum=16/0 centerNum=16/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=16/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.15@106,97 dx=21.7 idx=6/14 dist=35/40 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-24.95@107,94 dx=22.7 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=81,91 r=-1,-1
ATGSeedDiag: seed=1@16,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(94.8) imip=7/27 pass=11111 acc=17 ipm=82.5,86.5 inv=73.5,51.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T06:36:42+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive95
```
