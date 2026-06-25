# drive58

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive58-front_car_circle_drive58.log
- remote_log: /tmp/front_car_circle_drive58.log
- started_at: 2026-06-22T03:50:57+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive58 6
```

4739 /tmp/front_car_circle_drive58.log
ATGSeedDiag: seed=1@34,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.9) imip=0/8 pass=10111 acc=-1 ipm=62.0,115.6 inv=28.1,103.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=862 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=9/0 raw=30/0 sel=9/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/43/0/0 lost=0/0 conf=3.7/0.0/0.0/0.0 dist=1323 m0=(84,119) ml=(65,89) md=33/1/41 cxcy=84.0,119.6 guide=19.52 atg=-60.0/-60.0/-60.0 pure=7.32/7.32 yaw=-1171 cmd=-1371 actual=-781 signed=1 rps=5679/1921:3907/3588 duty=15/3 pwm=PWM2:15/PWM1:3 motor=2:15/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:61.2,115.6:26.1,103.4:3.7:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=3.7/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:16.45@69,90 dx=-15.4 idx=0/2 dist=33/45 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:19.36@65,89 dx=-18.9 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=46,109 r=-1,-1
ATGSeedDiag: seed=1@32,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(3.7) imip=0/8 pass=10111 acc=-1 ipm=61.2,115.6 inv=26.1,103.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=864 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=8/0 raw=27/0 sel=8/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/45/0/0 lost=0/0 conf=4.6/0.0/0.0/0.0 dist=1345 m0=(84,119) ml=(64,89) md=34/1/40 cxcy=84.0,119.6 guide=19.48 atg=-60.0/-60.0/-60.0 pure=7.29/7.29 yaw=-1169 cmd=-1369 actual=-794 signed=1 rps=5676/1924:4123/3583 duty=15/3 pwm=PWM2:15/PWM1:3 motor=2:15/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:59.9,115.7:23.2,103.7:4.6:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=4.6/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:15.61@70,91 dx=-14.3 idx=0/1 dist=32/44 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.10@64,89 dx=-19.6 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=47,110 r=-1,-1
ATGSeedDiag: seed=1@29,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(4.6) imip=0/7 pass=10111 acc=-1 ipm=59.9,115.7 inv=23.2,103.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=865 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=7/0 raw=25/0 sel=7/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/46/0/0 lost=0/0 conf=4.8/0.0/0.0/0.0 dist=1356 m0=(84,119) ml=(66,90) md=32/1/38 cxcy=84.0,119.6 guide=19.80 atg=-60.0/-60.0/-60.0 pure=7.16/7.16 yaw=-1188 cmd=-1388 actual=-804 signed=1 rps=5703/1897:4427/3638 duty=14/3 pwm=PWM2:14/PWM1:3 motor=2:14/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:59.1,115.6:21.2,103.5:4.8:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=4.8/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=7/0 centerNum=7/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:16.38@69,91 dx=-15.1 idx=0/1 dist=32/42 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.50@64,89 dx=-19.9 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,111 r=-1,-1
ATGSeedDiag: seed=1@27,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(4.8) imip=0/6 pass=10111 acc=-1 ipm=59.1,115.6 inv=21.2,103.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=867 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=6/0 raw=21/0 sel=6/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/48/0/0 lost=0/0 conf=4.4/0.0/0.0/0.0 dist=1378 m0=(84,119) ml=(63,90) md=34/1/38 cxcy=84.0,119.6 guide=20.74 atg=-60.0/-60.0/-60.0 pure=7.31/7.31 yaw=-1244 cmd=-1444 actual=-861 signed=1 rps=5780/1820:4643/3424 duty=14/3 pwm=PWM2:14/PWM1:3 motor=2:14/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:57.4,115.5:17.4,103.2:4.4:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=4.4/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/0 centerNum=6/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:17.73@68,91 dx=-16.4 idx=0/1 dist=33/41 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:21.22@63,90 dx=-20.6 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=49,112 r=-1,-1
ATGSeedDiag: seed=1@23,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(4.4) imip=0/5 pass=10111 acc=-1 ipm=57.4,115.5 inv=17.4,103.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=869 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=6/0 raw=18/0 sel=6/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/50/0/0 lost=0/0 conf=2.3/0.0/0.0/0.0 dist=1404 m0=(84,119) ml=(65,91) md=32/1/38 cxcy=84.0,119.6 guide=21.22 atg=-60.0/-60.0/-60.0 pure=7.44/7.44 yaw=-1273 cmd=-1473 actual=-938 signed=1 rps=5819/1781:4696/3325 duty=14/3 pwm=PWM2:14/PWM1:3 motor=2:14/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=3:51.9,113.5:8.3,97.3:2.3:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=2.3/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/0 centerNum=6/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.68@67,91 dx=-17.3 idx=0/1 dist=33/41 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:21.82@63,90 dx=-21.2 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,112 r=-1,-1
ATGSeedDiag: seed=1@20,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(2.3) imip=0/5 pass=10111 acc=-1 ipm=51.9,113.5 inv=8.3,97.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=871 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=5/0 raw=15/0 sel=5/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/52/0/0 lost=0/0 conf=2.3/0.0/0.0/0.0 dist=1426 m0=(84,119) ml=(64,91) md=33/1/37 cxcy=84.0,119.6 guide=21.45 atg=-60.0/-60.0/-60.0 pure=7.40/7.40 yaw=-1287 cmd=-1487 actual=-984 signed=1 rps=5838/1762:4844/3631 duty=14/3 pwm=PWM2:14/PWM1:3 motor=2:14/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:54.8,115.2:11.8,102.5:2.3:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=2.3/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:19.96@65,91 dx=-18.7 idx=0/1 dist=34/40 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.42@62,90 dx=-21.8 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,112 r=-1,-1
ATGSeedDiag: seed=1@17,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.3) imip=0/4 pass=10111 acc=-1 ipm=54.8,115.2 inv=11.8,102.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=872 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=5/0 raw=15/0 sel=5/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/53/0/0 lost=0/0 conf=4.1/0.0/0.0/0.0 dist=1441 m0=(84,119) ml=(64,91) md=33/1/37 cxcy=84.0,119.6 guide=21.53 atg=-60.0/-60.0/-60.0 pure=7.43/7.43 yaw=-1292 cmd=-1492 actual=-1001 signed=1 rps=5844/1756:4446/3555 duty=15/3 pwm=PWM2:15/PWM1:3 motor=2:15/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=3:50.2,113.4:4.9,96.9:4.1:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=4.1/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:19.93@66,92 dx=-18.5 idx=0/1 dist=33/39 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.60@62,90 dx=-21.9 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,112 r=-1,-1
ATGSeedDiag: seed=1@16,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(4.1) imip=0/4 pass=10111 acc=-1 ipm=50.2,113.4 inv=4.9,96.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=873 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=4/0 raw=14/0 sel=4/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/54/0/0 lost=0/0 conf=3.7/0.0/0.0/0.0 dist=1451 m0=(84,119) ml=(64,91) md=33/1/35 cxcy=84.0,119.6 guide=20.92 atg=-60.0/-60.0/-60.0 pure=7.30/7.30 yaw=-1255 cmd=-1455 actual=-1019 signed=1 rps=5795/1805:4595/3957 duty=14/2 pwm=PWM2:14/PWM1:2 motor=2:14/1:2
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:54.0,115.4:9.9,102.9:3.7:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=3.7/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:20.54@65,92 dx=-19.2 idx=0/1 dist=34/38 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.84@62,90 dx=-22.1 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=50,113 r=-1,-1
ATGSeedDiag: seed=1@15,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(3.7) imip=0/3 pass=10111 acc=-1 ipm=54.0,115.4 inv=9.9,102.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=876 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=3/0 raw=12/0 sel=3/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/57/0/0 lost=0/0 conf=1.6/0.0/0.0/0.0 dist=1486 m0=(84,119) ml=(64,91) md=33/1/33 cxcy=84.0,119.6 guide=20.96 atg=-60.0/-57.0/-57.0 pure=7.20/7.20 yaw=-1258 cmd=-1436 actual=-1079 signed=1 rps=5768/1832:4604/3923 duty=14/3 pwm=PWM2:14/PWM1:3 motor=2:14/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:52.8,115.2:7.2,102.5:1.6:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=1.6/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:21.34@64,92 dx=-19.9 idx=0/1 dist=34/36 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:21.75@64,91 dx=-20.5 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=51,114 r=-1,-1
ATGSeedDiag: seed=1@12,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(1.6) imip=0/2 pass=10111 acc=-1 ipm=52.8,115.2 inv=7.2,102.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=877 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=3/0 raw=9/0 sel=3/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/58/0/0 lost=0/0 conf=2.6/0.0/0.0/0.0 dist=1498 m0=(84,119) ml=(63,92) md=33/1/33 cxcy=84.0,119.6 guide=21.20 atg=-60.0/-60.0/-60.0 pure=7.32/7.32 yaw=-1272 cmd=-1446 actual=-1098 signed=1 rps=5781/1819:4621/3779 duty=14/3 pwm=PWM2:14/PWM1:3 motor=2:14/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:51.8,115.1:5.3,102.2:2.6:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=2.6/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:21.99@63,92 dx=-20.6 idx=0/1 dist=35/37 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.11@63,92 dx=-20.8 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=50,114 r=-1,-1
ATGSeedDiag: seed=1@10,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.6) imip=0/2 pass=10111 acc=-1 ipm=51.8,115.1 inv=5.3,102.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=878 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=2/0 raw=8/0 sel=2/15 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/59/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=1510 m0=(84,119) ml=(65,94) md=30/0/30 cxcy=84.0,119.6 guide=20.85 atg=-60.0/-56.0/-56.0 pure=7.44/7.44 yaw=-1251 cmd=-1384 actual=-1118 signed=1 rps=5697/1903:4950/3949 duty=14/3 pwm=PWM2:14/PWM1:3 motor=2:14/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.14@63,92 dx=-20.7 idx=0/1 dist=35/35 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:21.54@65,94 dx=-19.4 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=51,115 r=-1,-1
ATGSeedDiag: seed=1@9,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=880 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=2/0 raw=8/0 sel=2/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/61/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=1535 m0=(84,119) ml=(63,92) md=33/1/33 cxcy=84.0,119.6 guide=21.66 atg=-60.0/-60.0/-60.0 pure=7.49/7.49 yaw=-1299 cmd=-1432 actual=-1167 signed=1 rps=5762/1838:5207/3993 duty=14/2 pwm=PWM2:14/PWM1:2 motor=2:14/1:2
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.71@63,92 dx=-21.3 idx=0/1 dist=35/35 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:22.65@63,92 dx=-21.2 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=51,115 r=-1,-1
ATGSeedDiag: seed=1@8,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=882 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/0 raw=5/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/63/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=1560 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=7.50/7.50 yaw=0 cmd=0 actual=-1257 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,90.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@6,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T03:51:10+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive58
```
