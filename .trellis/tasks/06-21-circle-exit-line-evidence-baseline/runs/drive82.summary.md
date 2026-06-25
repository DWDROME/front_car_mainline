# drive82

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive82-front_car_circle_drive82.log
- remote_log: /tmp/front_car_circle_drive82.log
- started_at: 2026-06-22T06:08:54+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive82 6
```

3894 /tmp/front_car_circle_drive82.log
ATGSeedDiag: seed=1@31,107/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=14(66.8) imip=4/16 pass=11111 acc=14 ipm=40.3,93.7 inv=14.2,59.6 | 23(80.6) imip=13/33 pass=11111 acc=23 ipm=87.6,72.2 inv=78.3,40.1
frame=874 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/23 raw=62/170 sel=23/25 far=0/0 far_raw=0/0 l=1@14/1@23 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=67.1/81.0/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(71,93) md=32/1/52 cxcy=84.0,119.6 guide=15.07 atg=-60.0/-40.0/-40.0 pure=4.56/4.56 yaw=-904 cmd=-1104 actual=-303 signed=0 rps=6514/3486:4617/4091 duty=17/9 pwm=PWM2:17/PWM1:9 motor=2:17/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@14/1@23 nearNum=12/23 centerNum=12/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=23/25 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:19.26@61,76 dx=-23.3 idx=0/11 dist=30/30 right=1:13.06@73,97 dx=-10.6 idx=5/16 dist=31/58 sel=1:15.68@69,91 dx=-14.6 idx=0/16 dist=32/48 edge=1:13.73@71.5,91.5 dx=-12.5 width=52.6 l=46,98 r=97,85
CxScan: raw_ref=80.0 edge=71.5,91.5 best_raw_x=45 best_err=-1.01 best_cxcy=70.6,119.5 scan=0:-19.6,10:-15.7,20:-11.6,30:-7.4,40:-3.2,50:1.1,60:5.4,70:9.6,80:13.7,90:17.7,100:21.5,110:25.1,120:28.5,130:31.6,140:34.6
ATGSeedDiag: seed=1@31,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=14(67.1) imip=4/16 pass=11111 acc=14 ipm=40.2,94.5 inv=13.3,60.5 | 23(81.0) imip=13/33 pass=11111 acc=23 ipm=87.7,72.1 inv=78.3,40.0
frame=875 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=11/23 raw=61/170 sel=23/24 far=0/0 far_raw=0/0 l=1@13/1@23 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=68.5/82.0/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(69,92) md=33/1/50 cxcy=84.0,119.6 guide=16.39 atg=-60.0/-40.0/-40.0 pure=4.63/4.63 yaw=-983 cmd=-1183 actual=-322 signed=0 rps=6621/3379:5101/4533 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@13/1@23 nearNum=11/23 centerNum=11/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=23/24 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.87@62,78 dx=-22.3 idx=0/10 dist=27/27 right=1:15.16@71,94 dx=-13.2 idx=6/17 dist=32/55 sel=1:16.58@68,90 dx=-15.8 idx=0/16 dist=32/46 edge=1:13.99@71.5,92.5 dx=-12.5 width=50.7 l=47,99 r=96,86
CxScan: raw_ref=80.0 edge=71.5,92.5 best_raw_x=45 best_err=-1.03 best_cxcy=70.6,119.5 scan=0:-20.0,10:-16.0,20:-11.9,30:-7.6,40:-3.2,50:1.2,60:5.5,70:9.8,80:14.0,90:18.0,100:21.9,110:25.5,120:28.9,130:32.1,140:35.1
ATGSeedDiag: seed=1@30,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(68.5) imip=3/16 pass=11111 acc=13 ipm=41.9,94.8 inv=15.4,61.0 | 23(82.0) imip=13/33 pass=11111 acc=23 ipm=87.6,72.3 inv=78.3,40.2
frame=876 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=11/22 raw=59/170 sel=22/23 far=0/0 far_raw=0/0 l=1@13/1@22 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=67.6/79.8/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(70,91) md=33/1/48 cxcy=84.0,119.6 guide=15.30 atg=-60.0/-39.0/-39.0 pure=4.75/4.75 yaw=-918 cmd=-1118 actual=-334 signed=0 rps=6532/3468:5046/4531 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@13/1@22 nearNum=11/22 centerNum=11/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.95@62,78 dx=-22.3 idx=0/10 dist=27/27 right=1:15.35@70,93 dx=-13.7 idx=6/17 dist=33/52 sel=1:16.32@68,89 dx=-15.6 idx=0/16 dist=32/44 edge=1:13.99@71.5,92.5 dx=-12.5 width=50.7 l=47,99 r=96,86
CxScan: raw_ref=80.0 edge=71.5,92.5 best_raw_x=45 best_err=-1.03 best_cxcy=70.6,119.5 scan=0:-20.0,10:-16.0,20:-11.9,30:-7.6,40:-3.2,50:1.2,60:5.5,70:9.8,80:14.0,90:18.0,100:21.9,110:25.5,120:28.9,130:32.1,140:35.1
ATGSeedDiag: seed=1@29,107/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(67.6) imip=3/15 pass=11111 acc=13 ipm=41.0,95.6 inv=13.2,62.0 | 22(79.8) imip=12/32 pass=11111 acc=22 ipm=88.4,74.4 inv=79.3,41.5
frame=877 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=11/22 raw=57/170 sel=22/23 far=0/0 far_raw=0/0 l=1@13/1@22 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/80.9/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(70,93) md=32/1/49 cxcy=84.0,119.6 guide=15.65 atg=-60.0/-39.0/-39.0 pure=4.69/4.69 yaw=-939 cmd=-1139 actual=-372 signed=0 rps=6561/3439:5385/4883 duty=16/8 pwm=PWM2:16/PWM1:8 motor=2:16/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@13/1@22 nearNum=11/22 centerNum=11/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.93@62,78 dx=-22.2 idx=0/10 dist=25/25 right=1:15.92@70,92 dx=-14.5 idx=6/17 dist=33/52 sel=1:16.56@68,89 dx=-15.9 idx=0/16 dist=32/44 edge=1:16.46@68.0,88.5 dx=-16.0 width=48.8 l=46,99 r=90,78
CxScan: raw_ref=80.0 edge=68.0,88.5 best_raw_x=40 best_err=0.71 best_cxcy=68.7,119.4 scan=0:-15.2,10:-11.4,20:-7.4,30:-3.3,40:0.7,50:4.8,60:8.8,70:12.7,80:16.5,90:20.1,100:23.6,110:26.9,120:30.0,130:32.9,140:35.6
ATGSeedDiag: seed=1@28,106/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(63.8) imip=3/14 pass=11111 acc=13 ipm=40.1,96.3 inv=11.1,63.0 | 22(80.9) imip=12/32 pass=11111 acc=22 ipm=88.4,73.9 inv=79.3,41.2
frame=878 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=11/22 raw=58/170 sel=22/24 far=0/0 far_raw=0/0 l=1@13/1@22 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=69.3/81.2/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(70,93) md=32/1/51 cxcy=84.0,119.6 guide=15.82 atg=-60.0/-37.0/-37.0 pure=4.47/4.47 yaw=-949 cmd=-1149 actual=-408 signed=0 rps=6575/3425:5393/4914 duty=16/8 pwm=PWM2:16/PWM1:8 motor=2:16/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@13/1@22 nearNum=11/22 centerNum=11/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/24 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.98@62,79 dx=-22.1 idx=0/10 dist=25/25 right=1:16.28@69,92 dx=-15.0 idx=6/17 dist=33/52 sel=1:16.75@68,89 dx=-16.1 idx=0/16 dist=32/46 edge=1:16.65@67.5,87.5 dx=-16.5 width=48.8 l=46,99 r=89,76
CxScan: raw_ref=80.0 edge=67.5,87.5 best_raw_x=35 best_err=-0.78 best_cxcy=66.8,119.4 scan=0:-14.5,10:-10.7,20:-6.7,30:-2.8,40:1.2,50:5.2,60:9.1,70:12.9,80:16.7,90:20.2,100:23.6,110:26.9,120:29.9,130:32.8,140:35.5
ATGSeedDiag: seed=1@28,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(69.3) imip=3/14 pass=11111 acc=13 ipm=40.2,96.7 inv=10.8,63.5 | 22(81.2) imip=12/32 pass=11111 acc=22 ipm=88.4,73.8 inv=79.3,41.1
frame=879 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=10/21 raw=57/170 sel=21/22 far=0/0 far_raw=0/0 l=1@12/1@21 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=70.3/80.6/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(70,93) md=32/1/47 cxcy=84.0,119.6 guide=16.00 atg=-60.0/-38.0/-38.0 pure=4.87/4.87 yaw=-960 cmd=-1160 actual=-444 signed=0 rps=6589/3411:5152/4708 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@12/1@21 nearNum=10/21 centerNum=10/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.82@63,80 dx=-21.5 idx=0/9 dist=23/23 right=1:15.35@71,95 dx=-13.1 idx=6/16 dist=31/50 sel=1:16.83@68,89 dx=-16.2 idx=0/16 dist=32/42 edge=1:16.25@68.5,89.5 dx=-15.5 width=48.8 l=47,101 r=90,78
CxScan: raw_ref=80.0 edge=68.5,89.5 best_raw_x=40 best_err=0.19 best_cxcy=68.7,119.4 scan=0:-16.0,10:-12.1,20:-8.1,30:-3.9,40:0.2,50:4.3,60:8.4,70:12.4,80:16.3,90:20.0,100:23.5,110:26.9,120:30.0,130:33.0,140:35.8
ATGSeedDiag: seed=1@27,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(70.3) imip=2/14 pass=11111 acc=12 ipm=41.7,96.7 inv=13.0,63.5 | 21(80.6) imip=11/31 pass=11111 acc=21 ipm=88.6,76.4 inv=79.7,42.9
frame=880 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=10/21 raw=54/170 sel=21/22 far=0/0 far_raw=0/0 l=1@12/1@21 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/81.0/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(68,91) md=33/1/46 cxcy=84.0,119.6 guide=16.76 atg=-60.0/-38.0/-38.0 pure=4.82/4.82 yaw=-1005 cmd=-1205 actual=-469 signed=0 rps=6652/3348:5216/4872 duty=17/7 pwm=PWM2:17/PWM1:7 motor=2:17/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@12/1@21 nearNum=10/21 centerNum=10/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:19.01@62,80 dx=-21.8 idx=0/9 dist=23/23 right=1:16.97@68,90 dx=-16.2 idx=6/17 dist=34/49 sel=1:17.08@67,89 dx=-16.6 idx=0/16 dist=32/42 edge=1:17.09@67.5,89.0 dx=-16.5 width=48.3 l=46,100 r=89,78
CxScan: raw_ref=80.0 edge=67.5,89.0 best_raw_x=35 best_err=-0.80 best_cxcy=66.8,119.4 scan=0:-14.9,10:-10.9,20:-6.9,30:-2.8,40:1.3,50:5.3,60:9.4,70:13.3,80:17.1,90:20.7,100:24.2,110:27.5,120:30.6,130:33.5,140:36.2
ATGSeedDiag: seed=1@25,107/1@152,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(64.2) imip=2/13 pass=11111 acc=12 ipm=40.5,98.0 inv=9.8,65.3 | 21(81.0) imip=11/31 pass=11111 acc=21 ipm=88.8,76.0 inv=79.9,42.6
frame=881 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=9/20 raw=54/170 sel=20/20 far=0/0 far_raw=0/0 l=1@11/1@20 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=70.3/80.0/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(68,91) md=33/1/42 cxcy=84.0,119.6 guide=16.97 atg=-60.0/-39.0/-39.0 pure=5.15/5.15 yaw=-1018 cmd=-1218 actual=-499 signed=0 rps=6669/3331:4859/4674 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@11/1@20 nearNum=9/20 centerNum=9/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=20/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.72@63,81 dx=-20.9 idx=0/8 dist=22/22 right=1:16.31@69,93 dx=-14.5 idx=6/16 dist=31/45 sel=1:17.13@67,89 dx=-16.7 idx=0/16 dist=32/38 edge=1:16.19@69.0,91.0 dx=-15.0 width=47.4 l=48,102 r=90,80
CxScan: raw_ref=80.0 edge=69.0,91.0 best_raw_x=40 best_err=-0.36 best_cxcy=68.7,119.4 scan=0:-17.0,10:-13.0,20:-8.8,30:-4.6,40:-0.4,50:3.9,60:8.1,70:12.2,80:16.2,90:20.0,100:23.6,110:27.1,120:30.3,130:33.4,140:36.2
ATGSeedDiag: seed=1@24,107/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(70.3) imip=1/13 pass=11111 acc=11 ipm=42.4,97.8 inv=12.9,65.1 | 20(80.0) imip=10/30 pass=11111 acc=20 ipm=89.3,78.2 inv=80.7,44.2
frame=882 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=9/20 raw=53/170 sel=20/21 far=0/0 far_raw=0/0 l=1@11/1@20 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=68.2/79.5/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(68,90) md=33/1/43 cxcy=84.0,119.6 guide=17.05 atg=-60.0/-39.0/-39.0 pure=4.89/4.89 yaw=-1023 cmd=-1223 actual=-509 signed=0 rps=6676/3324:4932/4839 duty=17/7 pwm=PWM2:17/PWM1:7 motor=2:17/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@11/1@20 nearNum=9/20 centerNum=9/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=20/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.18@64,82 dx=-20.0 idx=0/8 dist=21/21 right=1:16.64@69,92 dx=-15.3 idx=6/16 dist=33/48 sel=1:17.20@67,88 dx=-16.8 idx=0/16 dist=32/40 edge=1:16.19@69.0,91.0 dx=-15.0 width=47.4 l=48,102 r=90,80
CxScan: raw_ref=80.0 edge=69.0,91.0 best_raw_x=40 best_err=-0.36 best_cxcy=68.7,119.4 scan=0:-17.0,10:-13.0,20:-8.8,30:-4.6,40:-0.4,50:3.9,60:8.1,70:12.2,80:16.2,90:20.0,100:23.6,110:27.1,120:30.3,130:33.4,140:36.2
ATGSeedDiag: seed=1@24,108/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(68.2) imip=1/12 pass=11111 acc=11 ipm=42.0,99.0 inv=10.9,66.8 | 20(79.5) imip=10/30 pass=11111 acc=20 ipm=89.9,78.0 inv=81.3,44.0
frame=884 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=8/19 raw=52/170 sel=19/19 far=0/0 far_raw=0/0 l=1@10/1@19 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=72.9/81.3/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(68,90) md=32/1/38 cxcy=84.0,119.6 guide=16.95 atg=-60.0/-37.0/-37.0 pure=5.24/5.24 yaw=-1017 cmd=-1217 actual=-534 signed=0 rps=6668/3332:5029/4536 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@10/1@19 nearNum=8/19 centerNum=8/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=19/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.57@64,83 dx=-20.2 idx=0/7 dist=20/20 right=1:17.08@68,91 dx=-15.9 idx=6/16 dist=33/43 sel=1:17.29@67,88 dx=-17.0 idx=0/16 dist=32/36 edge=1:15.74@70.0,93.0 dx=-14.0 width=47.4 l=49,104 r=91,82
CxScan: raw_ref=80.0 edge=70.0,93.0 best_raw_x=45 best_err=0.69 best_cxcy=70.6,119.5 scan=0:-18.6,10:-14.5,20:-10.3,30:-5.9,40:-1.5,50:2.9,60:7.3,70:11.6,80:15.7,90:19.7,100:23.5,110:27.1,120:30.5,130:33.6,140:36.5
ATGSeedDiag: seed=1@22,108/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(72.9) imip=0/12 pass=11111 acc=10 ipm=43.5,99.8 inv=12.2,68.0 | 19(81.3) imip=9/29 pass=11111 acc=19 ipm=89.9,80.5 inv=81.7,46.0
frame=885 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=8/18 raw=48/170 sel=18/18 far=0/0 far_raw=0/0 l=1@10/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=70.1/81.7/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(68,90) md=32/1/37 cxcy=84.0,119.6 guide=16.86 atg=-60.0/-38.0/-38.0 pure=5.37/5.37 yaw=-1012 cmd=-1212 actual=-545 signed=0 rps=6661/3339:5200/4441 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@10/1@18 nearNum=8/18 centerNum=8/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=18/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:19.14@63,82 dx=-21.0 idx=0/7 dist=17/17 right=1:16.78@69,93 dx=-15.1 idx=6/15 dist=32/42 sel=1:17.19@67,88 dx=-17.1 idx=0/16 dist=32/34 edge=1:16.05@70.0,94.0 dx=-14.0 width=48.3 l=48,104 r=92,84
CxScan: raw_ref=80.0 edge=70.0,94.0 best_raw_x=45 best_err=0.70 best_cxcy=70.6,119.5 scan=0:-19.0,10:-14.8,20:-10.5,30:-6.1,40:-1.6,50:3.0,60:7.4,70:11.8,80:16.0,90:20.1,100:24.0,110:27.6,120:31.0,130:34.1,140:37.1
ATGSeedDiag: seed=1@20,107/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(70.1) imip=0/11 pass=11111 acc=10 ipm=42.1,101.5 inv=7.9,70.7 | 18(81.7) imip=8/28 pass=11111 acc=18 ipm=90.6,82.2 inv=82.8,47.4
frame=886 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=7/18 raw=48/170 sel=18/18 far=0/0 far_raw=0/0 l=1@9/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=70.3/82.1/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(68,90) md=32/1/37 cxcy=84.0,119.6 guide=17.20 atg=-60.0/-38.0/-38.0 pure=5.36/5.36 yaw=-1032 cmd=-1232 actual=-547 signed=0 rps=6688/3312:5204/4296 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@9/1@18 nearNum=7/18 centerNum=7/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=18/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:17.36@66,86 dx=-17.9 idx=0/6 dist=12/12 right=1:16.94@69,92 dx=-15.4 idx=6/15 dist=31/41 sel=1:17.26@67,87 dx=-17.2 idx=0/16 dist=32/34 edge=1:15.81@70.5,95.0 dx=-13.5 width=48.3 l=49,106 r=92,84
CxScan: raw_ref=80.0 edge=70.5,95.0 best_raw_x=45 best_err=0.11 best_cxcy=70.6,119.5 scan=0:-19.9,10:-15.7,20:-11.3,30:-6.8,40:-2.2,50:2.4,60:7.0,70:11.5,80:15.8,90:20.0,100:23.9,110:27.6,120:31.1,130:34.3,140:37.3
ATGSeedDiag: seed=1@20,108/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(70.3) imip=0/10 pass=11111 acc=9 ipm=44.1,101.4 inv=11.3,70.5 | 18(82.1) imip=8/28 pass=11111 acc=18 ipm=90.8,82.3 inv=83.1,47.5
frame=887 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=7/18 raw=48/170 sel=18/19 far=0/0 far_raw=0/0 l=1@9/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=72.8/82.2/0.0/0.0 dist=0 begin=0/3267 m0=(84,119) ml=(68,89) md=33/1/39 cxcy=84.0,119.6 guide=17.08 atg=-60.0/-36.0/-36.0 pure=5.06/5.06 yaw=-1025 cmd=-1225 actual=-572 signed=0 rps=6678/3322:5501/4528 duty=17/8 pwm=PWM2:17/PWM1:8 motor=2:17/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@9/1@18 nearNum=7/18 centerNum=7/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=18/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:17.95@65,85 dx=-18.7 idx=0/6 dist=12/12 right=1:17.16@68,91 dx=-16.1 idx=6/15 dist=35/45 sel=1:17.23@67,87 dx=-17.2 idx=0/16 dist=32/36 edge=1:16.37@70.0,95.0 dx=-14.0 width=47.4 l=49,106 r=91,84
CxScan: raw_ref=80.0 edge=70.0,95.0 best_raw_x=45 best_err=0.72 best_cxcy=70.6,119.5 scan=0:-19.4,10:-15.1,20:-10.7,30:-6.2,40:-1.6,50:3.0,60:7.6,70:12.1,80:16.4,90:20.5,100:24.4,110:28.1,120:31.5,130:34.7,140:37.7
ATGSeedDiag: seed=1@19,108/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(72.8) imip=0/10 pass=11111 acc=9 ipm=43.7,102.1 inv=9.9,71.7 | 18(82.2) imip=8/28 pass=11111 acc=18 ipm=91.1,81.8 inv=83.3,47.1

- stopped_at: 2026-06-22T06:09:07+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive82
```
