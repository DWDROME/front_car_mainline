# drive176

- commit: ee88b09
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 12
- local_log: logs/live-circle/20260621-drive176-front_car_circle_drive176.log
- remote_log: /tmp/front_car_circle_drive176.log
- started_at: 2026-06-22T17:01:00+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive176 12
```

8202 /tmp/front_car_circle_drive176.log
ATGSeedDiag: seed=1@46,108/1@155,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=63(11.4) imip=53/64 pass=10101 acc=-1 ipm=-35.3,14.3 inv=3.3,19.3 | 2(14.0) imip=0/12 pass=10111 acc=-1 ipm=119.5,106.5 inv=141.6,78.7
frame=1677 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=64/170 raw=94/138 sel=170/164 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=37.5/13.7/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(67,88) md=40/1/152 cxcy=84.0,119.6 guide=17.75 atg=-60.0/-60.0/-60.0 pure=5.64/4.46 yaw=-1420 cmd=-1020 actual=-1626 signed=0 rps=5451/2655:5093/4304 duty=13/5 pwm=PWM2:13/PWM1:5 motor=2:13/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/170 centerNum=64/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/164 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:20.43@55,65 dx=-29.0 idx=0/20 dist=40/133 right=1:18.46@65,87 dx=-18.7 idx=8/24 dist=40/330 sel=1:19.51@63,85 dx=-20.5 idx=0/20 dist=40/326 edge=1:21.33@56.0,71.0 dx=-28.0 width=46.6 l=36,83 r=76,59
CxScan: raw_ref=80.0 edge=56.0,71.0 best_raw_x=5 best_err=-0.63 best_cxcy=55.2,119.3 scan=0:-2.2,10:0.9,20:4.0,30:7.0,40:10.0,50:13.0,60:15.8,70:18.6,80:21.3,90:23.9,100:26.4,110:28.8,120:31.1,130:33.3,140:35.3
ATGSeedDiag: seed=1@45,108/1@155,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=62(37.5) imip=52/63 pass=10101 acc=-1 ipm=-32.3,14.4 inv=5.0,19.3 | 2(13.7) imip=0/12 pass=10111 acc=-1 ipm=119.5,106.5 inv=141.6,78.7
frame=1678 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=64/168 raw=93/136 sel=168/162 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=63.8/17.3/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(67,88) md=40/1/151 cxcy=84.0,119.6 guide=17.87 atg=-60.0/-60.0/-60.0 pure=5.53/4.34 yaw=-1429 cmd=-1123 actual=-1582 signed=0 rps=5586/2508:5124/4390 duty=13/4 pwm=PWM2:13/PWM1:4 motor=2:13/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/168 centerNum=64/168 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=168/162 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:19.97@56,65 dx=-28.4 idx=0/20 dist=40/138 right=1:17.99@66,86 dx=-18.4 idx=8/24 dist=40/326 sel=1:18.94@64,84 dx=-20.1 idx=0/20 dist=40/322 edge=1:20.42@57.5,71.5 dx=-26.5 width=47.0 l=37,83 r=78,60
CxScan: raw_ref=80.0 edge=57.5,71.5 best_raw_x=10 best_err=-0.29 best_cxcy=57.1,119.4 scan=0:-3.4,10:-0.3,20:2.8,30:5.9,40:8.9,50:11.9,60:14.8,70:17.7,80:20.4,90:23.1,100:25.6,110:28.1,120:30.4,130:32.6,140:34.7
ATGSeedDiag: seed=1@45,108/1@155,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=62(63.8) imip=52/63 pass=11101 acc=-1 ipm=-31.9,14.2 inv=5.4,19.3 | 1(17.3) imip=0/11 pass=10111 acc=-1 ipm=120.6,108.7 inv=147.4,83.3
frame=1679 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=67/165 raw=96/134 sel=165/159 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=108.5/11.9/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(67,87) md=41/1/150 cxcy=84.0,119.6 guide=16.78 atg=-60.0/-60.0/-60.0 pure=5.34/4.21 yaw=-1342 cmd=-967 actual=-1530 signed=0 rps=5430/2780:6010/4926 duty=12/5 pwm=PWM2:12/PWM1:5 motor=2:12/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/165 centerNum=67/165 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=165/159 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:19.55@56,64 dx=-27.8 idx=0/20 dist=40/147 right=1:18.58@64,84 dx=-19.9 idx=8/25 dist=41/319 sel=1:18.62@64,84 dx=-19.9 idx=0/20 dist=40/316 edge=1:19.71@58.5,71.5 dx=-25.5 width=47.9 l=37,82 r=80,61
CxScan: raw_ref=80.0 edge=58.5,71.5 best_raw_x=15 best_err=0.46 best_cxcy=59.1,119.4 scan=0:-4.2,10:-1.1,20:2.0,30:5.1,40:8.1,50:11.1,60:14.1,70:16.9,80:19.7,90:22.4,100:25.0,110:27.4,120:29.8,130:32.0,140:34.2
ATGSeedDiag: seed=1@45,108/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=65(108.5) imip=55/66 pass=11101 acc=-1 ipm=-35.0,12.2 inv=4.5,18.9 | 1(11.9) imip=0/11 pass=10111 acc=-1 ipm=120.4,108.8 inv=147.2,83.5
frame=1680 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=68/163 raw=97/131 sel=163/157 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.6/13.6/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(67,86) md=40/1/146 cxcy=84.0,119.6 guide=17.45 atg=-60.0/-60.0/-60.0 pure=5.21/4.11 yaw=-1396 cmd=-1241 actual=-1474 signed=0 rps=5769/2369:5599/4294 duty=13/4 pwm=PWM2:13/PWM1:4 motor=2:13/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=68/163 centerNum=68/163 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=163/157 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:19.18@57,64 dx=-27.3 idx=0/20 dist=40/151 right=1:17.46@66,84 dx=-18.4 idx=8/24 dist=40/316 sel=1:18.25@64,83 dx=-19.8 idx=0/20 dist=40/312 edge=1:19.71@58.5,71.5 dx=-25.5 width=47.9 l=37,82 r=80,61
CxScan: raw_ref=80.0 edge=58.5,71.5 best_raw_x=15 best_err=0.46 best_cxcy=59.1,119.4 scan=0:-4.2,10:-1.1,20:2.0,30:5.1,40:8.1,50:11.1,60:14.1,70:16.9,80:19.7,90:22.4,100:25.0,110:27.4,120:29.8,130:32.0,140:34.2
ATGSeedDiag: seed=1@44,108/1@154,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=65(90.6) imip=55/67 pass=11101 acc=-1 ipm=-34.5,7.7 inv=6.9,17.9 | 1(13.6) imip=0/11 pass=10111 acc=-1 ipm=120.0,108.7 inv=146.3,83.5
frame=1681 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=68/159 raw=98/130 sel=159/154 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=80.7/8.9/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(68,87) md=40/1/147 cxcy=84.0,119.6 guide=16.64 atg=-60.0/-60.0/-60.0 pure=5.16/4.06 yaw=-1331 cmd=-1121 actual=-1437 signed=0 rps=5648/2577:5838/4277 duty=13/5 pwm=PWM2:13/PWM1:5 motor=2:13/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=68/159 centerNum=68/159 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=159/154 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:18.79@57,64 dx=-26.8 idx=0/20 dist=40/153 right=1:17.45@66,84 dx=-18.4 idx=7/24 dist=41/309 sel=1:17.81@65,83 dx=-19.0 idx=0/20 dist=40/306 edge=1:19.23@59.0,71.0 dx=-25.0 width=46.5 l=38,81 r=80,61
CxScan: raw_ref=80.0 edge=59.0,71.0 best_raw_x=15 best_err=0.05 best_cxcy=59.1,119.4 scan=0:-4.6,10:-1.5,20:1.6,30:4.7,40:7.7,50:10.7,60:13.6,70:16.5,80:19.2,90:21.9,100:24.5,110:26.9,120:29.3,130:31.6,140:33.7
ATGSeedDiag: seed=1@44,108/1@155,91 begin=7,108 block=5 clip=8
ATGLptDiag: best=65(80.7) imip=55/67 pass=11101 acc=-1 ipm=-33.6,8.5 inv=7.1,18.1 | 2(8.9) imip=0/12 pass=10111 acc=-1 ipm=118.6,107.3 inv=141.3,80.4
frame=1682 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=68/158 raw=99/128 sel=158/153 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.3/12.0/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(66,85) md=42/1/147 cxcy=84.0,119.6 guide=16.50 atg=-60.0/-60.0/-60.0 pure=5.07/4.00 yaw=-1320 cmd=-1097 actual=-1432 signed=0 rps=5624/2616:6047/4305 duty=12/5 pwm=PWM2:12/PWM1:5 motor=2:12/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=68/158 centerNum=68/158 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=158/153 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:18.44@58,64 dx=-26.3 idx=0/20 dist=40/158 right=1:17.32@66,84 dx=-18.4 idx=7/24 dist=41/307 sel=1:17.64@65,83 dx=-19.0 idx=0/20 dist=40/304 edge=1:19.21@58.5,69.5 dx=-25.5 width=47.0 l=38,81 r=79,58
CxScan: raw_ref=80.0 edge=58.5,69.5 best_raw_x=15 best_err=0.44 best_cxcy=59.1,119.4 scan=0:-4.1,10:-1.1,20:2.0,30:5.0,40:7.9,50:10.8,60:13.7,70:16.5,80:19.2,90:21.8,100:24.4,110:26.8,120:29.1,130:31.3,140:33.4
ATGSeedDiag: seed=1@43,108/1@154,91 begin=7,108 block=5 clip=8
ATGLptDiag: best=63(91.3) imip=53/67 pass=11101 acc=-1 ipm=-29.3,8.8 inv=9.3,18.2 | 1(12.0) imip=0/11 pass=10111 acc=-1 ipm=119.5,109.1 inv=146.2,84.4
frame=1683 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=67/159 raw=101/129 sel=159/154 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.6/11.5/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(68,86) md=40/1/147 cxcy=84.0,119.6 guide=16.47 atg=-60.0/-60.0/-60.0 pure=5.03/3.96 yaw=-1318 cmd=-1120 actual=-1416 signed=0 rps=5657/2587:5845/4160 duty=13/5 pwm=PWM2:13/PWM1:5 motor=2:13/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/159 centerNum=67/159 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=159/154 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:17.98@58,64 dx=-25.7 idx=0/20 dist=40/162 right=1:17.27@66,84 dx=-18.3 idx=7/24 dist=40/308 sel=1:17.65@65,83 dx=-19.0 idx=0/20 dist=40/306 edge=1:18.39@60.0,70.5 dx=-24.0 width=47.0 l=39,81 r=81,60
CxScan: raw_ref=80.0 edge=60.0,70.5 best_raw_x=15 best_err=-0.74 best_cxcy=59.1,119.4 scan=0:-5.3,10:-2.3,20:0.8,30:3.8,40:6.9,50:9.8,60:12.8,70:15.6,80:18.4,90:21.1,100:23.7,110:26.1,120:28.5,130:30.8,140:33.0
ATGSeedDiag: seed=1@43,108/1@155,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=61(95.6) imip=51/66 pass=11101 acc=-1 ipm=-24.7,10.2 inv=11.3,18.4 | 1(11.5) imip=0/11 pass=10111 acc=-1 ipm=119.6,109.5 inv=147.1,85.3
frame=1684 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=67/156 raw=101/127 sel=156/151 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.5/9.2/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(68,86) md=40/1/148 cxcy=84.0,119.6 guide=16.06 atg=-60.0/-60.0/-60.0 pure=4.92/3.86 yaw=-1285 cmd=-1074 actual=-1390 signed=0 rps=5616/2671:6050/4506 duty=12/5 pwm=PWM2:12/PWM1:5 motor=2:12/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/156 centerNum=67/156 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=156/151 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:17.58@59,64 dx=-25.1 idx=0/20 dist=40/166 right=1:16.96@66,83 dx=-18.1 idx=7/24 dist=41/303 sel=1:17.29@65,82 dx=-18.8 idx=0/20 dist=40/300 edge=1:17.92@60.5,70.0 dx=-23.5 width=47.4 l=39,80 r=82,60
CxScan: raw_ref=80.0 edge=60.5,70.0 best_raw_x=20 best_err=0.39 best_cxcy=61.0,119.4 scan=0:-5.7,10:-2.6,20:0.4,30:3.4,40:6.4,50:9.4,60:12.3,70:15.1,80:17.9,90:20.6,100:23.2,110:25.7,120:28.1,130:30.3,140:32.5
ATGSeedDiag: seed=1@43,108/1@155,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=61(90.5) imip=51/66 pass=11101 acc=-1 ipm=-24.0,10.7 inv=11.6,18.5 | 1(9.2) imip=0/11 pass=10111 acc=-1 ipm=119.5,109.6 inv=147.1,85.4
frame=1685 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=67/155 raw=102/126 sel=155/150 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.6/6.4/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(68,86) md=40/1/148 cxcy=84.0,119.6 guide=15.84 atg=-60.0/-60.0/-60.0 pure=4.84/3.80 yaw=-1267 cmd=-1108 actual=-1347 signed=0 rps=5673/2637:6031/4878 duty=13/4 pwm=PWM2:13/PWM1:4 motor=2:13/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/155 centerNum=67/155 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=155/150 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:17.22@59,64 dx=-24.5 idx=0/20 dist=40/168 right=1:16.61@66,83 dx=-17.9 idx=7/24 dist=40/300 sel=1:16.90@66,82 dx=-18.4 idx=0/20 dist=40/298 edge=1:17.92@60.5,70.0 dx=-23.5 width=47.4 l=39,80 r=82,60
CxScan: raw_ref=80.0 edge=60.5,70.0 best_raw_x=20 best_err=0.39 best_cxcy=61.0,119.4 scan=0:-5.7,10:-2.6,20:0.4,30:3.4,40:6.4,50:9.4,60:12.3,70:15.1,80:17.9,90:20.6,100:23.2,110:25.7,120:28.1,130:30.3,140:32.5
ATGSeedDiag: seed=1@42,108/1@155,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=60(93.6) imip=50/66 pass=11101 acc=-1 ipm=-21.1,10.3 inv=13.3,18.4 | 1(6.4) imip=0/11 pass=10111 acc=-1 ipm=119.4,109.7 inv=147.0,85.6
frame=1686 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=67/152 raw=103/124 sel=152/148 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=85.7/5.1/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(68,84) md=41/1/149 cxcy=84.0,119.6 guide=15.12 atg=-60.0/-60.0/-60.0 pure=4.72/3.71 yaw=-1210 cmd=-1061 actual=-1284 signed=0 rps=5647/2740:5701/4975 duty=13/5 pwm=PWM2:13/PWM1:5 motor=2:13/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/152 centerNum=67/152 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=152/148 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:16.78@60,63 dx=-23.9 idx=0/20 dist=40/171 right=1:16.10@67,82 dx=-17.5 idx=7/24 dist=41/295 sel=1:16.21@66,82 dx=-17.7 idx=0/20 dist=40/294 edge=1:16.81@62.5,71.5 dx=-21.5 width=48.1 l=40,80 r=85,63
CxScan: raw_ref=80.0 edge=62.5,71.5 best_raw_x=25 best_err=0.33 best_cxcy=62.9,119.4 scan=0:-7.4,10:-4.3,20:-1.2,30:1.9,40:5.0,50:8.0,60:11.0,70:13.9,80:16.8,90:19.6,100:22.3,110:24.8,120:27.3,130:29.7,140:31.9
ATGSeedDiag: seed=1@42,108/1@155,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=60(85.7) imip=50/66 pass=11101 acc=-1 ipm=-20.5,10.8 inv=13.5,18.5 | 1(5.1) imip=0/11 pass=10111 acc=-1 ipm=119.3,109.8 inv=147.0,85.9
frame=1688 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=68/152 raw=105/122 sel=152/148 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=86.6/7.6/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(70,86) md=40/1/152 cxcy=84.0,119.6 guide=14.37 atg=-60.0/-60.0/-60.0 pure=4.47/3.55 yaw=-1150 cmd=-1070 actual=-1189 signed=0 rps=5700/2767:5229/4859 duty=14/5 pwm=PWM2:14/PWM1:5 motor=2:14/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=68/152 centerNum=68/152 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=152/148 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:16.26@61,63 dx=-23.3 idx=0/20 dist=40/177 right=1:14.95@68,83 dx=-15.9 idx=6/23 dist=40/296 sel=1:15.32@67,82 dx=-16.7 idx=0/20 dist=40/294 edge=1:16.33@63.0,71.0 dx=-21.0 width=48.7 l=40,79 r=86,63
CxScan: raw_ref=80.0 edge=63.0,71.0 best_raw_x=25 best_err=-0.07 best_cxcy=62.9,119.4 scan=0:-7.7,10:-4.7,20:-1.6,30:1.5,40:4.5,50:7.6,60:10.6,70:13.5,80:16.3,90:19.1,100:21.8,110:24.4,120:26.8,130:29.2,140:31.5
ATGSeedDiag: seed=1@41,107/1@155,93 begin=7,108 block=5 clip=8
ATGLptDiag: best=60(86.6) imip=50/67 pass=11101 acc=-1 ipm=-18.2,7.8 inv=16.0,17.9 | 2(7.6) imip=0/12 pass=10111 acc=-1 ipm=117.7,108.2 inv=141.2,82.4
frame=1689 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=70/148 raw=108/120 sel=148/144 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=88.3/3.4/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(70,85) md=40/1/151 cxcy=84.0,119.6 guide=13.79 atg=-60.0/-60.0/-60.0 pure=4.38/3.45 yaw=-1103 cmd=-1023 actual=-1143 signed=0 rps=5667/2862:5621/5100 duty=13/5 pwm=PWM2:13/PWM1:5 motor=2:13/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/148 centerNum=70/148 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=148/144 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:15.81@61,63 dx=-22.5 idx=0/20 dist=40/186 right=1:14.50@68,82 dx=-15.6 idx=6/23 dist=40/288 sel=1:14.81@68,81 dx=-16.2 idx=0/20 dist=40/286 edge=1:16.22@63.0,70.5 dx=-21.0 width=49.0 l=40,79 r=86,62
CxScan: raw_ref=80.0 edge=63.0,70.5 best_raw_x=25 best_err=-0.07 best_cxcy=62.9,119.4 scan=0:-7.7,10:-4.6,20:-1.6,30:1.5,40:4.5,50:7.5,60:10.5,70:13.4,80:16.2,90:19.0,100:21.6,110:24.2,120:26.7,130:29.0,140:31.3
ATGSeedDiag: seed=1@41,108/1@155,94 begin=7,108 block=5 clip=8
ATGLptDiag: best=61(88.3) imip=51/69 pass=11101 acc=-1 ipm=-18.4,5.3 inv=16.9,17.5 | 3(3.4) imip=0/13 pass=10111 acc=-1 ipm=116.3,106.4 inv=135.7,78.6
frame=1690 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=69/147 raw=108/119 sel=147/143 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=82.6/7.1/0.0/0.0 dist=0 begin=0/3656 m0=(84,119) ml=(69,83) md=41/1/151 cxcy=84.0,119.6 guide=14.26 atg=-60.0/-60.0/-60.0 pure=4.30/3.40 yaw=-1141 cmd=-1214 actual=-1105 signed=0 rps=5903/2576:5893/5113 duty=14/4 pwm=PWM2:14/PWM1:4 motor=2:14/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=69/147 centerNum=69/147 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=147/143 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:15.66@62,63 dx=-22.3 idx=0/20 dist=40/184 right=1:14.52@68,82 dx=-15.7 idx=6/23 dist=40/286 sel=1:14.89@68,81 dx=-16.4 idx=0/20 dist=40/284 edge=1:15.39@64.0,70.0 dx=-20.0 width=48.7 l=41,78 r=87,62
CxScan: raw_ref=80.0 edge=64.0,70.0 best_raw_x=30 best_err=0.66 best_cxcy=64.8,119.4 scan=0:-8.4,10:-5.4,20:-2.4,30:0.7,40:3.7,50:6.7,60:9.6,70:12.6,80:15.4,90:18.1,100:20.8,110:23.4,120:25.9,130:28.2,140:30.5
ATGSeedDiag: seed=1@41,108/1@155,95 begin=7,108 block=5 clip=8
ATGLptDiag: best=59(82.6) imip=49/68 pass=11101 acc=-1 ipm=-14.3,7.6 inv=18.3,17.9 | 1(7.1) imip=0/11 pass=10111 acc=-1 ipm=118.4,110.7 inv=147.0,88.0

- stopped_at: 2026-06-22T17:01:19+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive176
```
