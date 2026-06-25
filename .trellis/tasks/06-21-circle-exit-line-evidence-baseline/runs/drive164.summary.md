# drive164

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 12
- local_log: logs/live-circle/20260621-drive164-front_car_circle_drive164.log
- remote_log: /tmp/front_car_circle_drive164.log
- started_at: 2026-06-22T16:06:42+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive164 12
```

8563 /tmp/front_car_circle_drive164.log
ATGSeedDiag: seed=1@39,108/1@155,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(38.9) imip=0/19 pass=10111 acc=-1 ipm=55.3,100.0 inv=30.9,68.1 | 62(20.7) imip=52/63 pass=10101 acc=-1 ipm=3.5,56.3 inv=5.7,32.1
frame=1662 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=19/63 raw=67/159 sel=63/48 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=37.8/17.8/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(72,93) md=40/1/105 cxcy=84.0,119.6 guide=14.52 atg=-60.0/-60.0/-60.0 pure=7.75/8.61 yaw=-1162 cmd=-1442 actual=-1021 signed=0 rps=6202/2249:5930/5222 duty=14/2 pwm=PWM2:14/PWM1:2 motor=2:14/1:2
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=19/63 centerNum=19/63 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/48 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:22.32@55,72 dx=-29.0 idx=0/14 dist=40/52 right=1:9.95@76,95 dx=-8.4 idx=1/22 dist=41/119 sel=1:17.00@68,91 dx=-16.0 idx=0/20 dist=40/94 edge=1:18.53@65.0,86.0 dx=-19.0 width=62.6 l=35,95 r=95,77
CxScan: raw_ref=80.0 edge=65.0,86.0 best_raw_x=30 best_err=-0.17 best_cxcy=64.8,119.4 scan=0:-11.7,10:-7.9,20:-4.1,30:-0.2,40:3.7,50:7.6,60:11.3,70:15.0,80:18.5,90:21.9,100:25.2,110:28.2,120:31.1,130:33.9,140:36.4
ATGSeedDiag: seed=1@39,108/1@155,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(37.8) imip=0/18 pass=10111 acc=-1 ipm=57.0,101.5 inv=32.5,70.5 | 5(17.8) imip=0/15 pass=10111 acc=-1 ipm=115.5,104.2 inv=131.3,74.3
frame=1663 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=19/63 raw=66/159 sel=63/48 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=38.1/20.6/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(73,94) md=40/1/106 cxcy=84.0,119.6 guide=13.78 atg=-60.0/-60.0/-60.0 pure=7.87/8.71 yaw=-1102 cmd=-1279 actual=-1014 signed=0 rps=6018/2513:6444/5464 duty=13/3 pwm=PWM2:13/PWM1:3 motor=2:13/1:3
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=19/63 centerNum=19/63 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/48 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:23.00@54,72 dx=-29.9 idx=0/14 dist=41/53 right=1:7.34@78,97 dx=-5.8 idx=0/20 dist=40/121 sel=1:16.28@69,92 dx=-14.9 idx=0/20 dist=40/94 edge=1:18.68@65.0,86.5 dx=-19.0 width=62.9 l=35,96 r=95,77
CxScan: raw_ref=80.0 edge=65.0,86.5 best_raw_x=30 best_err=-0.17 best_cxcy=64.8,119.4 scan=0:-11.8,10:-8.0,20:-4.1,30:-0.2,40:3.7,50:7.6,60:11.4,70:15.1,80:18.7,90:22.1,100:25.4,110:28.4,120:31.4,130:34.1,140:36.7
ATGSeedDiag: seed=1@40,108/1@155,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(38.1) imip=0/18 pass=10111 acc=-1 ipm=56.8,101.7 inv=31.9,70.9 | 10(20.6) imip=0/20 pass=10111 acc=-1 ipm=110.5,93.8 inv=113.1,58.9
frame=1664 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=18/62 raw=65/158 sel=62/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=37.6/20.4/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(69,92) md=41/1/99 cxcy=84.0,119.6 guide=17.01 atg=-60.0/-60.0/-60.0 pure=8.25/8.86 yaw=-1361 cmd=-1761 actual=-1025 signed=0 rps=6506/1680:6540/5296 duty=14/0 pwm=PWM2:14/PWM1:0 motor=2:14/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=18/62 centerNum=18/62 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/46 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:23.34@54,73 dx=-30.1 idx=0/14 dist=40/49 right=1:12.14@74,95 dx=-10.3 idx=2/23 dist=41/115 sel=1:18.80@66,91 dx=-17.5 idx=0/20 dist=40/90 edge=1:18.23@65.5,86.5 dx=-18.5 width=60.1 l=37,96 r=94,77
CxScan: raw_ref=80.0 edge=65.5,86.5 best_raw_x=30 best_err=-0.68 best_cxcy=64.8,119.4 scan=0:-12.3,10:-8.5,20:-4.6,30:-0.7,40:3.2,50:7.1,60:10.9,70:14.6,80:18.2,90:21.7,100:24.9,110:28.0,120:31.0,130:33.7,140:36.3
ATGSeedDiag: seed=1@40,108/1@155,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(37.6) imip=0/17 pass=10111 acc=-1 ipm=58.4,103.2 inv=33.4,73.5 | 10(20.4) imip=0/20 pass=10111 acc=-1 ipm=110.1,93.6 inv=112.4,58.7
frame=1665 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=18/60 raw=63/157 sel=60/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=35.0/19.0/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(65,92) md=41/1/95 cxcy=84.0,119.6 guide=21.30 atg=-60.0/-60.0/-60.0 pure=8.78/9.14 yaw=-1704 cmd=-2104 actual=-1035 signed=0 rps=6748/981:6607/5089 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=18/60 centerNum=18/60 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/44 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.22@50,73 dx=-34.3 idx=0/15 dist=42/48 right=1:15.83@70,95 dx=-13.6 idx=4/25 dist=40/108 sel=1:22.04@63,91 dx=-20.9 idx=0/20 dist=40/86 edge=1:19.46@64.5,87.5 dx=-19.5 width=60.1 l=36,97 r=93,78
CxScan: raw_ref=80.0 edge=64.5,87.5 best_raw_x=30 best_err=0.35 best_cxcy=64.8,119.4 scan=0:-11.5,10:-7.6,20:-3.6,30:0.3,40:4.3,50:8.3,60:12.1,70:15.9,80:19.5,90:22.9,100:26.2,110:29.3,120:32.2,130:34.9,140:37.5
ATGSeedDiag: seed=1@40,108/1@155,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(35.0) imip=0/17 pass=10111 acc=-1 ipm=58.0,103.7 inv=32.3,74.3 | 9(19.0) imip=0/19 pass=10111 acc=-1 ipm=110.7,95.8 inv=115.0,61.4
frame=1666 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=18/60 raw=62/157 sel=60/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=35.0/19.3/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(65,92) md=42/1/96 cxcy=84.0,119.6 guide=20.21 atg=-60.0/-60.0/-60.0 pure=8.71/9.07 yaw=-1617 cmd=-2017 actual=-1058 signed=0 rps=6686/1159:6843/5184 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=18/60 centerNum=18/60 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/44 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.72@49,73 dx=-35.1 idx=0/15 dist=42/48 right=1:14.61@72,95 dx=-12.4 idx=4/24 dist=40/108 sel=1:21.94@63,91 dx=-20.7 idx=0/20 dist=40/86 edge=1:19.63@64.5,88.0 dx=-19.5 width=60.4 l=36,98 r=93,78
CxScan: raw_ref=80.0 edge=64.5,88.0 best_raw_x=30 best_err=0.35 best_cxcy=64.8,119.4 scan=0:-11.6,10:-7.7,20:-3.7,30:0.3,40:4.4,50:8.3,60:12.2,70:16.0,80:19.6,90:23.1,100:26.4,110:29.5,120:32.4,130:35.2,140:37.7
ATGSeedDiag: seed=1@40,108/1@155,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(35.0) imip=0/17 pass=10111 acc=-1 ipm=57.8,103.9 inv=31.7,74.7 | 10(19.3) imip=0/20 pass=10111 acc=-1 ipm=109.3,93.9 inv=111.5,59.1
frame=1667 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/60 raw=61/156 sel=60/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=24.1/18.5/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(66,92) md=41/1/98 cxcy=84.0,119.6 guide=20.06 atg=-60.0/-60.0/-60.0 pure=8.64/9.00 yaw=-1605 cmd=-2005 actual=-1105 signed=0 rps=6678/1182:6392/4993 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/60 centerNum=17/60 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/45 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.50@50,74 dx=-34.5 idx=0/15 dist=41/44 right=1:14.92@71,95 dx=-12.7 idx=4/24 dist=41/110 sel=1:21.89@63,91 dx=-20.7 idx=0/20 dist=40/88 edge=1:19.16@65.0,88.0 dx=-19.0 width=57.6 l=38,98 r=92,78
CxScan: raw_ref=80.0 edge=65.0,88.0 best_raw_x=30 best_err=-0.18 best_cxcy=64.8,119.4 scan=0:-12.1,10:-8.2,20:-4.2,30:-0.2,40:3.8,50:7.8,60:11.7,70:15.5,80:19.2,90:22.6,100:26.0,110:29.1,120:32.0,130:34.8,140:37.4
ATGSeedDiag: seed=1@40,108/1@155,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(24.1) imip=0/15 pass=10111 acc=-1 ipm=61.3,106.7 inv=35.7,80.2 | 10(18.5) imip=0/20 pass=10111 acc=-1 ipm=109.1,93.7 inv=111.1,58.8
frame=1668 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/60 raw=60/156 sel=60/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=32.8/19.2/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(66,92) md=41/1/98 cxcy=84.0,119.6 guide=20.06 atg=-60.0/-60.0/-60.0 pure=8.71/9.03 yaw=-1605 cmd=-2005 actual=-1155 signed=0 rps=6678/1182:6461/5380 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/60 centerNum=17/60 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/45 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:27.15@49,74 dx=-35.3 idx=0/15 dist=41/44 right=1:16.15@70,94 dx=-14.0 idx=4/25 dist=41/108 sel=1:21.85@63,91 dx=-20.6 idx=0/20 dist=40/88 edge=1:19.16@65.0,88.0 dx=-19.0 width=57.6 l=38,98 r=92,78
CxScan: raw_ref=80.0 edge=65.0,88.0 best_raw_x=30 best_err=-0.18 best_cxcy=64.8,119.4 scan=0:-12.1,10:-8.2,20:-4.2,30:-0.2,40:3.8,50:7.8,60:11.7,70:15.5,80:19.2,90:22.6,100:26.0,110:29.1,120:32.0,130:34.8,140:37.4
ATGSeedDiag: seed=1@41,108/1@155,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=6(32.8) imip=0/16 pass=10111 acc=-1 ipm=59.2,105.6 inv=32.8,77.9 | 9(19.2) imip=0/19 pass=10111 acc=-1 ipm=110.6,95.5 inv=114.6,61.1
frame=1669 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/60 raw=59/156 sel=60/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=26.4/16.3/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(65,92) md=41/1/95 cxcy=84.0,119.6 guide=19.89 atg=-60.0/-60.0/-60.0 pure=8.84/9.09 yaw=-1591 cmd=-1991 actual=-1195 signed=0 rps=6668/1210:6160/5349 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/60 centerNum=17/60 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/44 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:27.48@48,74 dx=-35.6 idx=0/15 dist=41/44 right=1:16.45@70,95 dx=-14.2 idx=5/25 dist=41/109 sel=1:22.42@63,91 dx=-21.3 idx=0/20 dist=40/86 edge=1:19.63@64.5,88.0 dx=-19.5 width=58.5 l=37,98 r=92,78
CxScan: raw_ref=80.0 edge=64.5,88.0 best_raw_x=30 best_err=0.35 best_cxcy=64.8,119.4 scan=0:-11.6,10:-7.7,20:-3.7,30:0.3,40:4.4,50:8.3,60:12.2,70:16.0,80:19.6,90:23.1,100:26.4,110:29.5,120:32.4,130:35.2,140:37.7
ATGSeedDiag: seed=1@41,108/1@155,102 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(26.4) imip=0/15 pass=10111 acc=-1 ipm=60.9,107.1 inv=34.6,80.9 | 4(16.3) imip=0/14 pass=10111 acc=-1 ipm=116.0,105.6 inv=134.0,77.0
frame=1670 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/60 raw=60/156 sel=60/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=32.3/18.9/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(65,92) md=41/1/95 cxcy=84.0,119.6 guide=21.11 atg=-60.0/-60.0/-60.0 pure=8.99/9.23 yaw=-1689 cmd=-2089 actual=-1234 signed=0 rps=6737/1011:6559/5665 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/60 centerNum=17/60 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/44 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:28.03@48,74 dx=-36.4 idx=0/15 dist=41/44 right=1:16.52@70,95 dx=-14.2 idx=5/25 dist=40/106 sel=1:22.81@62,91 dx=-21.6 idx=0/20 dist=40/86 edge=1:19.79@64.5,88.5 dx=-19.5 width=58.9 l=37,99 r=92,78
CxScan: raw_ref=80.0 edge=64.5,88.5 best_raw_x=30 best_err=0.35 best_cxcy=64.8,119.4 scan=0:-11.7,10:-7.8,20:-3.7,30:0.4,40:4.4,50:8.4,60:12.3,70:16.1,80:19.8,90:23.3,100:26.6,110:29.7,120:32.7,130:35.4,140:38.0
ATGSeedDiag: seed=1@41,108/1@155,102 begin=7,108 block=5 clip=8
ATGLptDiag: best=6(32.3) imip=0/16 pass=10111 acc=-1 ipm=58.9,105.8 inv=32.0,78.3 | 10(18.9) imip=0/20 pass=10111 acc=-1 ipm=109.1,93.6 inv=111.0,58.7
frame=1671 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/59 raw=58/155 sel=59/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=31.4/17.0/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(64,93) md=41/1/92 cxcy=84.0,119.6 guide=22.47 atg=-60.0/-60.0/-60.0 pure=9.06/9.42 yaw=-1798 cmd=-2198 actual=-1278 signed=0 rps=6814/789:8346/6754 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=16/59 centerNum=16/59 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/43 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:28.33@48,75 dx=-36.5 idx=0/15 dist=40/40 right=1:17.09@69,95 dx=-14.6 idx=5/25 dist=41/106 sel=1:23.23@62,92 dx=-21.7 idx=0/20 dist=40/84 edge=1:19.49@65.0,89.0 dx=-19.0 width=56.5 l=39,100 r=91,78
CxScan: raw_ref=80.0 edge=65.0,89.0 best_raw_x=30 best_err=-0.18 best_cxcy=64.8,119.4 scan=0:-12.3,10:-8.3,20:-4.3,30:-0.2,40:3.9,50:8.0,60:11.9,70:15.8,80:19.5,90:23.0,100:26.4,110:29.5,120:32.5,130:35.3,140:37.9
ATGSeedDiag: seed=1@41,108/1@155,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(31.4) imip=0/15 pass=10111 acc=-1 ipm=60.5,107.3 inv=33.7,81.5 | 6(17.0) imip=0/16 pass=10111 acc=-1 ipm=113.9,101.2 inv=125.0,69.2
frame=1672 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/58 raw=57/155 sel=58/41 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=31.2/17.5/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(63,93) md=40/1/88 cxcy=84.0,119.6 guide=24.40 atg=-60.0/-60.0/-60.0 pure=9.52/9.59 yaw=-1952 cmd=-2352 actual=-1335 signed=0 rps=6922/476:6289/5018 duty=16/0 pwm=PWM2:16/PWM1:0 motor=2:16/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=16/58 centerNum=16/58 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/41 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:29.05@47,76 dx=-37.3 idx=0/15 dist=40/40 right=1:17.64@69,96 dx=-14.8 idx=6/25 dist=41/103 sel=1:25.24@60,92 dx=-23.7 idx=0/20 dist=40/80 edge=1:19.49@65.0,89.0 dx=-19.0 width=56.5 l=39,100 r=91,78
CxScan: raw_ref=80.0 edge=65.0,89.0 best_raw_x=30 best_err=-0.18 best_cxcy=64.8,119.4 scan=0:-12.3,10:-8.3,20:-4.3,30:-0.2,40:3.9,50:8.0,60:11.9,70:15.8,80:19.5,90:23.0,100:26.4,110:29.5,120:32.5,130:35.3,140:37.9
ATGSeedDiag: seed=1@41,108/1@155,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(31.2) imip=0/15 pass=10111 acc=-1 ipm=60.3,107.5 inv=33.2,81.8 | 7(17.5) imip=0/17 pass=10111 acc=-1 ipm=112.5,99.2 inv=120.7,66.2
frame=1673 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/58 raw=56/155 sel=58/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=30.3/14.8/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(62,93) md=41/1/91 cxcy=84.0,119.6 guide=23.68 atg=-60.0/-60.0/-60.0 pure=9.55/9.53 yaw=-1895 cmd=-2295 actual=-1387 signed=0 rps=6882/592:6549/5127 duty=16/0 pwm=PWM2:16/PWM1:0 motor=2:16/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=16/58 centerNum=16/58 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/42 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:29.31@46,76 dx=-37.6 idx=0/15 dist=40/40 right=1:17.93@69,97 dx=-14.9 idx=6/25 dist=40/103 sel=1:26.08@59,93 dx=-24.6 idx=0/20 dist=40/82 edge=1:20.31@64.5,90.0 dx=-19.5 width=57.4 l=38,101 r=91,79
CxScan: raw_ref=80.0 edge=64.5,90.0 best_raw_x=30 best_err=0.36 best_cxcy=64.8,119.4 scan=0:-12.0,10:-8.0,20:-3.8,30:0.4,40:4.5,50:8.7,60:12.7,70:16.6,80:20.3,90:23.9,100:27.2,110:30.4,120:33.4,130:36.2,140:38.8
ATGSeedDiag: seed=1@41,108/1@155,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(30.3) imip=0/15 pass=10111 acc=-1 ipm=60.2,107.6 inv=32.7,82.1 | 1(14.8) imip=0/11 pass=10111 acc=-1 ipm=117.4,112.4 inv=148.3,92.7
frame=1674 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/59 raw=56/155 sel=59/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=28.9/18.0/0.0/0.0 dist=0 begin=0/3132 m0=(84,119) ml=(62,93) md=41/1/91 cxcy=84.0,119.6 guide=23.51 atg=-60.0/-60.0/-60.0 pure=9.35/9.43 yaw=-1880 cmd=-2280 actual=-1430 signed=0 rps=6872/621:6845/5234 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=15/59 centerNum=15/59 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/42 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:27.37@50,77 dx=-34.2 idx=0/14 dist=36/36 right=1:19.14@68,95 dx=-16.4 idx=6/26 dist=41/102 sel=1:25.83@60,92 dx=-24.5 idx=0/20 dist=40/82 edge=1:18.86@66.0,90.0 dx=-18.0 width=54.6 l=41,101 r=91,79
CxScan: raw_ref=80.0 edge=66.0,90.0 best_raw_x=35 best_err=0.82 best_cxcy=66.8,119.4 scan=0:-13.6,10:-9.6,20:-5.4,30:-1.3,40:2.9,50:7.1,60:11.1,70:15.1,80:18.9,90:22.5,100:25.9,110:29.2,120:32.2,130:35.1,140:37.8
ATGSeedDiag: seed=1@41,108/1@155,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(28.9) imip=0/14 pass=10111 acc=-1 ipm=61.8,109.2 inv=34.5,85.6 | 10(18.0) imip=0/20 pass=10111 acc=-1 ipm=108.3,93.9 inv=110.1,59.0

- stopped_at: 2026-06-22T16:07:04+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive164
```
