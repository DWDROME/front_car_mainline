# drive106

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive106-front_car_circle_drive106.log
- remote_log: /tmp/front_car_circle_drive106.log
- started_at: 2026-06-22T07:15:29+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive106 6
```

3842 /tmp/front_car_circle_drive106.log
ATGSeedDiag: seed=1@32,108/1@155,100 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(66.2) imip=19/37 pass=11111 acc=29 ipm=35.6,67.3 inv=27.9,37.5 | 39(71.2) imip=29/49 pass=11111 acc=39 ipm=80.8,38.6 inv=71.3,25.1
frame=902 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=26/39 raw=100/147 sel=26/44 far=0/0 far_raw=0/0 l=1@28/1@39 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=49.0/75.4/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(94,91) md=33/1/95 cxcy=84.0,119.6 guide=-10.46 atg=-17.0/-54.0/-54.0 pure=1.74/3.82 yaw=628 cmd=428 actual=2301 signed=0 rps=4414/5586:1561/3138 duty=14/19 pwm=PWM2:14/PWM1:19 motor=2:14/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@28/1@39 nearNum=26/39 centerNum=26/39 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/44 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.52@95,95 dx=10.7 idx=0/7 dist=32/99 right=1:-1.74@86,85 dx=1.8 idx=0/22 dist=33/85 sel=1:-9.54@93,89 dx=9.1 idx=0/16 dist=32/86 edge=1:0.02@84.0,81.0 dx=-0.0 width=60.0 l=54,82 r=114,80
CxScan: raw_ref=80.0 edge=84.0,81.0 best_raw_x=80 best_err=0.02 best_cxcy=84.0,119.6 scan=0:-26.5,10:-23.6,20:-20.5,30:-17.3,40:-14.0,50:-10.5,60:-7.1,70:-3.5,80:0.0,90:3.6,100:7.1,110:10.6,120:13.9,130:17.2,140:20.4
ATGSeedDiag: seed=1@32,108/1@155,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(64.5) imip=18/36 pass=11111 acc=28 ipm=35.3,68.7 inv=26.9,38.3 | 39(75.4) imip=29/49 pass=11111 acc=39 ipm=78.3,40.6 inv=69.5,25.8
frame=903 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=26/40 raw=97/148 sel=26/44 far=0/0 far_raw=0/0 l=1@28/1@40 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=49.7/75.0/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(92,90) md=33/1/95 cxcy=84.0,119.6 guide=-9.29 atg=-25.0/-60.0/-60.0 pure=2.16/4.07 yaw=557 cmd=357 actual=2239 signed=0 rps=4511/5489:1818/3476 duty=14/18 pwm=PWM2:14/PWM1:18 motor=2:14/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@28/1@40 nearNum=26/40 centerNum=26/40 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/44 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.78@94,93 dx=9.5 idx=0/7 dist=33/99 right=1:-0.80@85,86 dx=0.8 idx=0/22 dist=33/88 sel=1:-7.72@92,88 dx=7.5 idx=0/16 dist=32/86 edge=1:1.43@82.5,81.5 dx=-1.5 width=61.1 l=52,83 r=113,80
CxScan: raw_ref=80.0 edge=82.5,81.5 best_raw_x=75 best_err=-0.37 best_cxcy=82.1,119.5 scan=0:-25.6,10:-22.6,20:-19.4,30:-16.1,40:-12.7,50:-9.3,60:-5.7,70:-2.2,80:1.4,90:5.0,100:8.5,110:12.0,120:15.3,130:18.6,140:21.7
ATGSeedDiag: seed=1@32,108/1@155,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(66.7) imip=18/35 pass=11111 acc=28 ipm=33.1,69.4 inv=24.4,38.7 | 40(75.0) imip=30/50 pass=11111 acc=40 ipm=75.4,40.0 inv=67.4,25.6
frame=904 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=26/41 raw=94/149 sel=26/43 far=0/0 far_raw=0/0 l=1@28/1@41 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=47.8/74.0/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(91,89) md=33/1/93 cxcy=84.0,119.6 guide=-7.10 atg=-38.0/-60.0/-60.0 pure=2.56/4.22 yaw=426 cmd=226 actual=2149 signed=0 rps=4690/5310:1952/3580 duty=14/17 pwm=PWM2:14/PWM1:17 motor=2:14/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@28/1@41 nearNum=26/41 centerNum=26/41 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-8.50@92,91 dx=7.7 idx=0/7 dist=33/99 right=1:-0.40@84,87 dx=0.4 idx=0/22 dist=33/90 sel=1:-5.98@90,87 dx=5.9 idx=0/16 dist=32/84 edge=1:2.38@81.5,82.0 dx=-2.5 width=63.0 l=50,83 r=113,81
CxScan: raw_ref=80.0 edge=81.5,82.0 best_raw_x=75 best_err=0.57 best_cxcy=82.1,119.5 scan=0:-25.0,10:-21.9,20:-18.7,30:-15.4,40:-11.9,50:-8.4,60:-4.8,70:-1.2,80:2.4,90:6.0,100:9.5,110:13.0,120:16.3,130:19.6,140:22.7
ATGSeedDiag: seed=1@32,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(67.3) imip=18/34 pass=11111 acc=28 ipm=30.7,70.6 inv=21.2,39.4 | 41(74.0) imip=31/51 pass=11111 acc=41 ipm=72.6,39.6 inv=65.4,25.5
frame=905 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=26/41 raw=90/148 sel=26/42 far=0/0 far_raw=0/0 l=1@28/1@41 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=46.9/72.5/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(88,87) md=34/1/91 cxcy=84.0,119.6 guide=-4.39 atg=-60.0/-60.0/-60.0 pure=3.27/4.54 yaw=112 cmd=-88 actual=2062 signed=0 rps=5121/4879:2176/3886 duty=15/15 pwm=PWM2:15/PWM1:15 motor=2:15/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@28/1@41 nearNum=26/41 centerNum=26/41 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-4.99@89,89 dx=4.7 idx=0/7 dist=34/97 right=1:1.94@82,88 dx=-1.9 idx=0/22 dist=33/89 sel=1:-2.71@87,85 dx=2.7 idx=0/16 dist=32/82 edge=1:4.33@79.5,83.0 dx=-4.5 width=61.1 l=49,85 r=110,81
CxScan: raw_ref=80.0 edge=79.5,83.0 best_raw_x=70 best_err=0.66 best_cxcy=80.2,119.5 scan=0:-23.8,10:-20.6,20:-17.3,30:-13.8,40:-10.3,50:-6.7,60:-3.0,70:0.7,80:4.3,90:8.0,100:11.5,110:15.0,120:18.3,130:21.6,140:24.6
ATGSeedDiag: seed=1@31,108/1@153,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(68.9) imip=18/32 pass=11111 acc=28 ipm=26.8,72.9 inv=15.7,41.0 | 41(72.5) imip=31/51 pass=11111 acc=41 ipm=68.4,41.2 inv=62.3,26.0
frame=906 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=26/41 raw=86/150 sel=26/41 far=0/0 far_raw=0/0 l=1@28/1@41 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=43.9/74.7/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(86,87) md=32/1/87 cxcy=84.0,119.6 guide=-1.32 atg=-60.0/-60.0/-60.0 pure=3.60/4.65 yaw=34 cmd=-166 actual=1967 signed=0 rps=5228/4772:2355/4064 duty=16/14 pwm=PWM2:16/PWM1:14 motor=2:16/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@28/1@41 nearNum=26/41 centerNum=26/41 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/41 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-4.36@88,90 dx=4.0 idx=0/6 dist=32/96 right=1:3.48@81,88 dx=-3.3 idx=0/22 dist=32/86 sel=1:-1.14@85,85 dx=1.1 idx=0/16 dist=32/80 edge=1:6.28@77.5,83.5 dx=-6.5 width=61.2 l=47,86 r=108,81
CxScan: raw_ref=80.0 edge=77.5,83.5 best_raw_x=65 best_err=0.75 best_cxcy=78.3,119.5 scan=0:-22.3,10:-19.0,20:-15.6,30:-12.1,40:-8.5,50:-4.8,60:-1.1,70:2.6,80:6.3,90:9.9,100:13.5,110:16.9,120:20.2,130:23.4,140:26.4
ATGSeedDiag: seed=1@31,108/1@152,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(68.8) imip=18/30 pass=11111 acc=28 ipm=24.7,74.6 inv=12.2,42.1 | 41(74.7) imip=31/51 pass=11111 acc=41 ipm=66.0,42.1 inv=60.4,26.3
frame=907 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=26/42 raw=84/151 sel=26/41 far=0/0 far_raw=0/0 l=1@28/1@42 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=43.8/72.5/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(85,87) md=32/1/87 cxcy=84.0,119.6 guide=-0.14 atg=-60.0/-60.0/-60.0 pure=3.91/4.85 yaw=4 cmd=-196 actual=1867 signed=0 rps=5269/4731:2384/3931 duty=16/14 pwm=PWM2:16/PWM1:14 motor=2:16/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@28/1@42 nearNum=26/42 centerNum=26/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/41 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-1.23@85,87 dx=1.2 idx=0/7 dist=34/95 right=1:3.76@81,90 dx=-3.5 idx=0/21 dist=33/96 sel=1:0.21@84,85 dx=-0.2 idx=0/16 dist=32/80 edge=1:7.71@76.0,83.5 dx=-8.0 width=62.2 l=45,86 r=107,81
CxScan: raw_ref=80.0 edge=76.0,83.5 best_raw_x=60 best_err=0.34 best_cxcy=76.4,119.5 scan=0:-21.0,10:-17.7,20:-14.3,30:-10.7,40:-7.1,50:-3.4,60:0.3,70:4.0,80:7.7,90:11.3,100:14.8,110:18.2,120:21.5,130:24.6,140:27.5
ATGSeedDiag: seed=1@30,108/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(68.6) imip=18/30 pass=11111 acc=28 ipm=23.1,75.9 inv=9.4,43.0 | 42(72.5) imip=32/52 pass=11111 acc=42 ipm=62.9,41.2 inv=58.3,26.1
frame=908 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=26/42 raw=81/152 sel=26/41 far=0/0 far_raw=0/0 l=1@28/1@42 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=41.7/68.5/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(84,86) md=33/1/88 cxcy=84.0,119.6 guide=0.43 atg=-60.0/-60.0/-60.0 pure=4.18/4.99 yaw=-11 cmd=-211 actual=1771 signed=0 rps=5289/4711:2642/3995 duty=15/14 pwm=PWM2:15/PWM1:14 motor=2:15/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@28/1@42 nearNum=26/42 centerNum=26/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/41 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-0.82@85,88 dx=0.8 idx=0/6 dist=33/95 right=1:6.22@78,90 dx=-5.8 idx=0/22 dist=33/94 sel=1:1.68@82,85 dx=-1.7 idx=0/16 dist=32/80 edge=1:9.29@74.5,84.5 dx=-9.5 width=63.2 l=43,87 r=106,82
CxScan: raw_ref=80.0 edge=74.5,84.5 best_raw_x=55 best_err=-0.06 best_cxcy=74.4,119.5 scan=0:-20.1,10:-16.6,20:-13.1,30:-9.4,40:-5.7,50:-2.0,60:1.8,70:5.6,80:9.3,90:12.9,100:16.4,110:19.8,120:23.1,130:26.1,140:29.1
ATGSeedDiag: seed=1@30,108/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(74.0) imip=18/29 pass=11111 acc=28 ipm=21.4,77.3 inv=6.4,44.1 | 42(68.5) imip=32/52 pass=11111 acc=42 ipm=61.6,41.7 inv=57.3,26.2
frame=909 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=25/41 raw=78/152 sel=25/39 far=0/0 far_raw=0/0 l=1@27/1@41 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=41.3/71.2/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(82,86) md=34/1/84 cxcy=84.0,119.6 guide=1.06 atg=-60.0/-60.0/-60.0 pure=4.43/5.11 yaw=-27 cmd=-227 actual=1663 signed=0 rps=5311/4689:2664/3734 duty=15/14 pwm=PWM2:15/PWM1:14 motor=2:15/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@27/1@41 nearNum=25/41 centerNum=25/41 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=25/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:2.32@82,85 dx=-2.3 idx=0/7 dist=34/90 right=1:6.27@78,91 dx=-5.7 idx=0/21 dist=33/91 sel=1:2.91@81,84 dx=-3.0 idx=0/16 dist=32/76 edge=1:10.72@73.0,84.5 dx=-11.0 width=62.2 l=42,87 r=104,82
CxScan: raw_ref=80.0 edge=73.0,84.5 best_raw_x=50 best_err=-0.48 best_cxcy=72.5,119.5 scan=0:-18.8,10:-15.3,20:-11.7,30:-8.0,40:-4.3,50:-0.5,60:3.3,70:7.0,80:10.7,90:14.3,100:17.8,110:21.1,120:24.3,130:27.3,140:30.2
ATGSeedDiag: seed=1@29,108/1@149,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=27(77.9) imip=17/28 pass=11111 acc=27 ipm=21.6,77.3 inv=6.6,44.0 | 41(71.2) imip=31/51 pass=11111 acc=41 ipm=60.8,44.3 inv=56.3,27.1
frame=910 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=28/42 raw=76/154 sel=28/42 far=0/0 far_raw=0/0 l=0@-1/1@42 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=55.8/71.1/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(81,86) md=33/1/90 cxcy=84.0,119.6 guide=3.36 atg=-60.0/-60.0/-60.0 pure=4.69/5.48 yaw=-86 cmd=-286 actual=1549 signed=0 rps=5392/4608:2873/3866 duty=15/14 pwm=PWM2:15/PWM1:14 motor=2:15/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@42 nearNum=28/42 centerNum=28/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=28/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:2.48@82,87 dx=-2.4 idx=0/6 dist=33/96 right=1:6.08@79,93 dx=-5.3 idx=0/20 dist=32/93 sel=1:4.17@80,84 dx=-4.3 idx=0/16 dist=32/82 edge=1:10.42@73.5,85.5 dx=-10.5 width=61.4 l=43,89 r=104,82
CxScan: raw_ref=80.0 edge=73.5,85.5 best_raw_x=55 best_err=0.94 best_cxcy=74.4,119.5 scan=0:-19.5,10:-16.0,20:-12.4,30:-8.6,40:-4.8,50:-1.0,60:2.9,70:6.7,80:10.4,90:14.1,100:17.6,110:21.0,120:24.3,130:27.3,140:30.3
ATGSeedDiag: seed=1@29,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=26(55.8) imip=16/27 pass=10111 acc=-1 ipm=22.2,78.1 inv=6.6,44.6 | 42(71.1) imip=32/52 pass=11111 acc=42 ipm=58.0,43.6 inv=54.3,26.9
frame=911 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=27/42 raw=73/151 sel=27/40 far=0/0 far_raw=0/0 l=0@-1/1@42 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=36.7/68.3/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(81,88) md=32/1/86 cxcy=84.0,119.6 guide=3.46 atg=-60.0/-60.0/-60.0 pure=4.89/5.45 yaw=-88 cmd=-288 actual=1456 signed=0 rps=5395/4605:2861/3737 duty=16/14 pwm=PWM2:16/PWM1:14 motor=2:16/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@42 nearNum=27/42 centerNum=27/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=27/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.80@80,86 dx=-3.7 idx=0/6 dist=33/89 right=1:8.04@77,92 dx=-7.2 idx=0/21 dist=33/95 sel=1:5.24@79,84 dx=-5.4 idx=0/16 dist=32/78 edge=1:11.96@72.0,86.0 dx=-12.0 width=62.5 l=41,90 r=103,82
CxScan: raw_ref=80.0 edge=72.0,86.0 best_raw_x=50 best_err=0.52 best_cxcy=72.5,119.5 scan=0:-18.3,10:-14.7,20:-11.0,30:-7.2,40:-3.4,50:0.5,60:4.4,70:8.2,80:12.0,90:15.6,100:19.1,110:22.5,120:25.7,130:28.7,140:31.6
ATGSeedDiag: seed=1@28,108/1@148,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(36.7) imip=0/14 pass=10111 acc=-1 ipm=62.2,107.0 inv=37.0,80.7 | 42(68.3) imip=32/52 pass=11111 acc=42 ipm=56.7,44.0 inv=53.3,27.0
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=26/42 raw=71/156 sel=26/39 far=0/0 far_raw=0/0 l=0@-1/1@42 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=37.1/75.1/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(80,88) md=32/1/85 cxcy=84.0,119.6 guide=4.49 atg=-60.0/-60.0/-60.0 pure=5.12/5.54 yaw=-115 cmd=-315 actual=1345 signed=0 rps=5431/4569:3063/3898 duty=15/14 pwm=PWM2:15/PWM1:14 motor=2:15/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@42 nearNum=26/42 centerNum=26/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.68@81,88 dx=-3.5 idx=0/5 dist=32/88 right=1:8.80@76,92 dx=-7.8 idx=0/21 dist=33/93 sel=1:6.29@78,84 dx=-6.4 idx=0/16 dist=32/76 edge=1:12.93@71.0,86.0 dx=-13.0 width=62.5 l=40,90 r=102,82
CxScan: raw_ref=80.0 edge=71.0,86.0 best_raw_x=45 best_err=-0.41 best_cxcy=70.6,119.5 scan=0:-17.4,10:-13.8,20:-10.0,30:-6.2,40:-2.4,50:1.5,60:5.4,70:9.2,80:12.9,90:16.5,100:20.0,110:23.3,120:26.5,130:29.5,140:32.3
ATGSeedDiag: seed=1@28,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(37.1) imip=0/15 pass=10111 acc=-1 ipm=60.4,105.0 inv=35.5,76.6 | 42(75.1) imip=32/52 pass=11111 acc=42 ipm=54.7,45.6 inv=51.5,27.6
frame=913 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=25/42 raw=68/156 sel=25/38 far=0/0 far_raw=0/0 l=0@-1/1@42 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=36.0/73.6/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(79,88) md=32/1/82 cxcy=84.0,119.6 guide=5.69 atg=-60.0/-60.0/-60.0 pure=5.30/5.65 yaw=-145 cmd=-345 actual=1240 signed=0 rps=5473/4527:3091/3766 duty=16/14 pwm=PWM2:16/PWM1:14 motor=2:16/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@42 nearNum=25/42 centerNum=25/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=25/38 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.01@79,88 dx=-4.8 idx=0/5 dist=32/86 right=1:10.09@75,93 dx=-8.8 idx=0/21 dist=33/93 sel=1:7.35@77,84 dx=-7.5 idx=0/16 dist=32/74 edge=1:14.00@70.0,86.5 dx=-14.0 width=62.6 l=39,91 r=101,82
CxScan: raw_ref=80.0 edge=70.0,86.5 best_raw_x=45 best_err=0.61 best_cxcy=70.6,119.5 scan=0:-16.6,10:-12.9,20:-9.1,30:-5.3,40:-1.4,50:2.6,60:6.5,70:10.3,80:14.0,90:17.6,100:21.1,110:24.4,120:27.5,130:30.5,140:33.2
ATGSeedDiag: seed=1@27,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(36.0) imip=0/15 pass=10111 acc=-1 ipm=59.6,105.1 inv=33.9,76.9 | 42(73.6) imip=32/52 pass=11111 acc=42 ipm=53.5,46.1 inv=50.5,27.8
frame=914 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=23/42 raw=66/156 sel=42/40 far=0/0 far_raw=0/0 l=0@-1/1@42 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=34.7/71.4/0.0/0.0 dist=0 begin=0/3245 m0=(84,119) ml=(72,91) md=33/1/86 cxcy=84.0,119.6 guide=14.11 atg=-60.0/-60.0/-60.0 pure=6.76/5.80 yaw=-846 cmd=-1046 actual=1151 signed=0 rps=6434/3566:3224/3745 duty=19/10 pwm=PWM2:19/PWM1:10 motor=2:19/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@42 nearNum=23/42 centerNum=23/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=42/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:16.15@65,76 dx=-19.3 idx=0/11 dist=34/65 right=1:9.84@76,94 dx=-8.4 idx=1/20 dist=33/95 sel=1:14.73@70,90 dx=-13.8 idx=0/16 dist=32/78 edge=1:14.95@69.0,86.5 dx=-15.0 width=62.6 l=38,91 r=100,82
CxScan: raw_ref=80.0 edge=69.0,86.5 best_raw_x=40 best_err=-0.33 best_cxcy=68.7,119.4 scan=0:-15.7,10:-11.9,20:-8.1,30:-4.2,40:-0.3,50:3.6,60:7.5,70:11.3,80:15.0,90:18.5,100:21.9,110:25.2,120:28.3,130:31.2,140:34.0
ATGSeedDiag: seed=1@27,108/1@146,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(34.7) imip=0/14 pass=10111 acc=-1 ipm=60.1,107.2 inv=32.9,81.2 | 42(71.4) imip=32/52 pass=11111 acc=42 ipm=52.1,46.6 inv=49.3,28.0

- stopped_at: 2026-06-22T07:15:42+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive106
```
