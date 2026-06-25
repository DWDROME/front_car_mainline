# drive140

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive140-front_car_circle_drive140.log
- remote_log: /tmp/front_car_circle_drive140.log
- started_at: 2026-06-22T15:14:31+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive140 6
```

4982 /tmp/front_car_circle_drive140.log
frame=910 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=22/0 raw=74/0 sel=22/37 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=22.0/0.0/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(81,83) md=40/1/80 cxcy=84.0,119.6 guide=4.34 atg=-60.0/-60.0/-60.0 pure=5.50/6.59 yaw=-260 cmd=-460 actual=733 signed=0 rps=5371/4109:5711/6501 duty=12/8 pwm=PWM2:12/PWM1:8 motor=2:12/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=22/0 centerNum=22/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/37 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:3.47@80,83 dx=-3.6 idx=0/6 dist=42/86 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:6.90@77,81 dx=-7.4 idx=0/20 dist=40/72 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=37,97 r=-1,-1
ATGSeedDiag: seed=1@63,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(22.0) imip=0/12 pass=10111 acc=-1 ipm=74.5,112.2 inv=58.2,93.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=911 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=20/0 raw=70/0 sel=20/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=24.7/0.0/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(79,83) md=40/1/74 cxcy=84.0,119.6 guide=6.36 atg=-60.0/-60.0/-60.0 pure=5.91/6.59 yaw=-382 cmd=-582 actual=681 signed=0 rps=5415/3821:5378/6275 duty=12/7 pwm=PWM2:12/PWM1:7 motor=2:12/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=20/0 centerNum=20/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=20/34 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:3.47@80,85 dx=-3.5 idx=0/5 dist=40/81 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:8.87@74,81 dx=-9.6 idx=0/20 dist=40/66 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=37,98 r=-1,-1
ATGSeedDiag: seed=1@61,107/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(24.7) imip=0/15 pass=10111 acc=-1 ipm=68.2,107.6 inv=47.9,81.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=19/0 raw=68/0 sel=19/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=22.6/0.0/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(77,84) md=40/1/71 cxcy=84.0,119.6 guide=7.72 atg=-60.0/-60.0/-60.0 pure=6.25/6.70 yaw=-463 cmd=-663 actual=631 signed=0 rps=5446/3627:5588/6510 duty=12/6 pwm=PWM2:12/PWM1:6 motor=2:12/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=19/0 centerNum=19/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=19/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:4.79@79,85 dx=-4.9 idx=0/5 dist=40/77 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:10.25@73,82 dx=-11.1 idx=0/20 dist=40/64 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=39,100 r=-1,-1
ATGSeedDiag: seed=1@60,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(22.6) imip=0/13 pass=10111 acc=-1 ipm=71.3,110.9 inv=52.1,89.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=913 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/64 raw=62/153 sel=64/52 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=23.9/15.2/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(62,95) md=41/1/105 cxcy=84.0,119.6 guide=24.35 atg=-60.0/-60.0/-60.0 pure=9.45/7.73 yaw=-1461 cmd=-1661 actual=593 signed=0 rps=5815/1263:5876/6459 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/64 centerNum=17/64 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/52 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:27.73@50,78 dx=-34.2 idx=0/15 dist=41/44 right=1:21.09@66,96 dx=-17.9 idx=10/27 dist=41/114 sel=1:26.89@59,94 dx=-24.6 idx=0/20 dist=40/102 edge=1:27.09@55.0,86.0 dx=-29.0 width=42.5 l=41,102 r=69,70
CxScan: raw_ref=80.0 edge=55.0,86.0 best_raw_x=5 best_err=0.22 best_cxcy=55.2,119.3 scan=0:-1.7,10:2.2,20:6.0,30:9.9,40:13.6,50:17.2,60:20.6,70:23.9,80:27.1,90:30.1,100:32.9,110:35.5,120:37.9,130:40.2,140:42.4
ATGSeedDiag: seed=1@57,108/1@155,87 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(23.9) imip=0/14 pass=10111 acc=-1 ipm=67.3,110.1 inv=44.6,87.6 | 7(15.2) imip=0/17 pass=10111 acc=-1 ipm=114.6,95.8 inv=120.6,61.4
frame=914 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/63 raw=59/153 sel=63/51 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=21.9/15.5/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(60,95) md=41/1/103 cxcy=84.0,119.6 guide=27.03 atg=-60.0/-60.0/-60.0 pure=9.61/7.72 yaw=-1622 cmd=-1822 actual=527 signed=0 rps=5875/882:6031/5915 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=16/63 centerNum=16/63 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/51 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:28.81@48,78 dx=-35.6 idx=0/15 dist=40/40 right=1:22.38@65,97 dx=-18.7 idx=10/27 dist=41/111 sel=1:28.64@58,95 dx=-26.2 idx=0/20 dist=40/100 edge=1:27.29@55.0,86.5 dx=-29.0 width=42.0 l=42,103 r=68,70
CxScan: raw_ref=80.0 edge=55.0,86.5 best_raw_x=5 best_err=0.22 best_cxcy=55.2,119.3 scan=0:-1.7,10:2.2,20:6.1,30:9.9,40:13.7,50:17.3,60:20.8,70:24.1,80:27.3,90:30.3,100:33.1,110:35.7,120:38.2,130:40.5,140:42.7
ATGSeedDiag: seed=1@55,108/1@155,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(21.9) imip=0/14 pass=10111 acc=-1 ipm=66.2,110.3 inv=42.1,88.3 | 9(15.5) imip=0/19 pass=10111 acc=-1 ipm=110.6,93.2 inv=112.7,58.1
frame=915 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/63 raw=56/153 sel=63/51 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.1/15.5/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(60,96) md=41/1/102 cxcy=84.0,119.6 guide=27.30 atg=-60.0/-60.0/-60.0 pure=9.60/7.70 yaw=-1638 cmd=-1838 actual=425 signed=0 rps=5881/843:6784/5918 duty=12/0 pwm=PWM2:12/PWM1:0 motor=2:12/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=15/63 centerNum=15/63 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/51 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:28.23@50,79 dx=-34.1 idx=0/14 dist=36/36 right=1:21.16@67,98 dx=-17.4 idx=9/26 dist=40/112 sel=1:28.85@58,95 dx=-26.4 idx=0/20 dist=40/100 edge=1:25.85@57.5,88.0 dx=-26.5 width=43.2 l=43,104 r=72,72
CxScan: raw_ref=80.0 edge=57.5,88.0 best_raw_x=10 best_err=-0.38 best_cxcy=57.1,119.4 scan=0:-4.4,10:-0.4,20:3.7,30:7.6,40:11.6,50:15.4,60:19.0,70:22.5,80:25.8,90:29.0,100:32.0,110:34.7,120:37.3,130:39.8,140:42.0
ATGSeedDiag: seed=1@53,108/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(17.1) imip=0/11 pass=10111 acc=-1 ipm=70.8,114.6 inv=49.0,100.0 | 10(15.5) imip=0/20 pass=10111 acc=-1 ipm=108.4,92.0 inv=109.0,56.8
frame=916 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/64 raw=53/153 sel=64/52 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.2/15.9/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(59,95) md=41/1/102 cxcy=84.0,119.6 guide=28.34 atg=-60.0/-60.0/-60.0 pure=9.52/7.65 yaw=-1700 cmd=-1900 actual=278 signed=0 rps=5904/695:6566/5522 duty=12/0 pwm=PWM2:12/PWM1:0 motor=2:12/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=15/64 centerNum=15/64 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/52 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:29.15@49,80 dx=-35.3 idx=0/14 dist=36/36 right=1:22.88@65,97 dx=-19.3 idx=9/27 dist=40/112 sel=1:29.09@57,94 dx=-26.9 idx=0/20 dist=40/102 edge=1:27.93@55.0,88.0 dx=-29.0 width=42.8 l=42,105 r=68,71
CxScan: raw_ref=80.0 edge=55.0,88.0 best_raw_x=5 best_err=0.23 best_cxcy=55.2,119.3 scan=0:-1.8,10:2.2,20:6.3,30:10.2,40:14.1,50:17.8,60:21.3,70:24.7,80:27.9,90:31.0,100:33.8,110:36.5,120:38.9,130:41.3,140:43.4
ATGSeedDiag: seed=1@51,108/1@155,91 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(18.2) imip=0/12 pass=10111 acc=-1 ipm=68.0,113.2 inv=43.9,96.1 | 1(15.9) imip=0/11 pass=10111 acc=-1 ipm=120.6,108.9 inv=147.9,83.9
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/1 raw=50/170 sel=14/26 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.6/0.0/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(65,84) md=42/1/55 cxcy=84.0,119.6 guide=16.90 atg=-60.0/-60.0/-60.0 pure=7.16/7.16 yaw=-1014 cmd=-1214 actual=137 signed=0 rps=5650/2322:6670/5599 duty=11/2 pwm=PWM2:11/PWM1:2 motor=2:11/1:2
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=14/1 centerNum=14/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=14/26 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:15.71@68,85 dx=-16.2 idx=0/6 dist=41/58 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:19.49@63,84 dx=-20.8 idx=0/20 dist=40/50 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=43,106 r=-1,-1
ATGSeedDiag: seed=1@49,108/1@149,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(17.6) imip=0/12 pass=10111 acc=-1 ipm=67.0,113.4 inv=41.5,96.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=918 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=13/63 raw=47/153 sel=63/50 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.1/13.7/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(58,95) md=40/1/100 cxcy=84.0,119.6 guide=28.96 atg=-60.0/-60.0/-60.0 pure=9.51/7.63 yaw=-1737 cmd=-1937 actual=4 signed=0 rps=5918/608:6509/5675 duty=12/0 pwm=PWM2:12/PWM1:0 motor=2:12/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=13/63 centerNum=13/63 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/50 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:28.36@51,82 dx=-32.8 idx=0/12 dist=28/28 right=1:23.01@65,97 dx=-19.4 idx=10/27 dist=40/111 sel=1:29.71@56,94 dx=-27.8 idx=0/20 dist=40/98 edge=1:27.53@56.0,89.0 dx=-28.0 width=43.3 l=44,107 r=68,71
CxScan: raw_ref=80.0 edge=56.0,89.0 best_raw_x=5 best_err=-0.84 best_cxcy=55.2,119.3 scan=0:-2.9,10:1.2,20:5.3,30:9.4,40:13.3,50:17.1,60:20.8,70:24.2,80:27.5,90:30.6,100:33.6,110:36.3,120:38.8,130:41.2,140:43.4
ATGSeedDiag: seed=1@47,108/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(18.1) imip=0/12 pass=10111 acc=-1 ipm=65.9,113.6 inv=39.1,97.1 | 6(13.7) imip=0/16 pass=10111 acc=-1 ipm=114.7,98.7 inv=123.7,65.4
frame=919 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/61 raw=44/153 sel=61/48 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.2/13.8/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(60,97) md=40/1/101 cxcy=84.0,119.6 guide=28.46 atg=-60.0/-60.0/-60.0 pure=9.85/8.00 yaw=-1708 cmd=-1908 actual=-110 signed=0 rps=5907/678:6084/5712 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=12/61 centerNum=12/61 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=61/48 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:27.72@53,83 dx=-31.3 idx=0/11 dist=23/23 right=1:23.75@64,98 dx=-19.6 idx=10/27 dist=41/107 sel=1:30.94@56,95 dx=-28.4 idx=0/20 dist=40/94 edge=1:27.98@56.0,90.0 dx=-28.0 width=42.2 l=45,108 r=67,72
CxScan: raw_ref=80.0 edge=56.0,90.0 best_raw_x=5 best_err=-0.85 best_cxcy=55.2,119.3 scan=0:-2.9,10:1.2,20:5.4,30:9.5,40:13.5,50:17.4,60:21.1,70:24.6,80:28.0,90:31.1,100:34.0,110:36.8,120:39.3,130:41.7,140:43.9
ATGSeedDiag: seed=1@45,108/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(15.2) imip=0/11 pass=10111 acc=-1 ipm=64.9,113.8 inv=36.5,97.8 | 5(13.8) imip=0/15 pass=10111 acc=-1 ipm=116.0,100.6 inv=127.8,68.3
frame=920 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/60 raw=42/153 sel=60/47 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.1/14.2/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(59,98) md=40/1/100 cxcy=84.0,119.6 guide=29.73 atg=-60.0/-60.0/-60.0 pure=10.17/8.29 yaw=-1784 cmd=-1984 actual=-204 signed=0 rps=5935/498:6167/6176 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/60 centerNum=11/60 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/47 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:27.03@54,84 dx=-29.8 idx=0/10 dist=20/20 right=1:26.54@62,99 dx=-21.9 idx=10/28 dist=41/104 sel=1:32.29@55,97 dx=-29.0 idx=0/20 dist=40/92 edge=1:28.43@56.0,91.0 dx=-28.0 width=41.2 l=46,109 r=66,73
CxScan: raw_ref=80.0 edge=56.0,91.0 best_raw_x=5 best_err=-0.87 best_cxcy=55.2,119.3 scan=0:-3.0,10:1.3,20:5.5,30:9.7,40:13.8,50:17.7,60:21.5,70:25.1,80:28.4,90:31.6,100:34.6,110:37.3,120:39.9,130:42.3,140:44.5
ATGSeedDiag: seed=1@43,108/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(14.1) imip=0/10 pass=10111 acc=-1 ipm=64.0,114.0 inv=34.4,98.5 | 7(14.2) imip=0/17 pass=10111 acc=-1 ipm=112.6,97.3 inv=119.1,63.5
frame=921 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=10/58 raw=38/153 sel=58/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.6/13.2/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(55,99) md=41/1/96 cxcy=84.0,119.6 guide=33.31 atg=-60.0/-60.0/-60.0 pure=10.48/8.60 yaw=-1999 cmd=-2199 actual=-304 signed=0 rps=6015/0:6066/6088 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/58 centerNum=10/58 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/45 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:27.22@54,85 dx=-29.6 idx=0/9 dist=18/18 right=1:27.94@62,100 dx=-22.5 idx=10/28 dist=40/100 sel=1:34.83@53,98 dx=-31.1 idx=0/20 dist=40/88 edge=1:29.76@55.0,92.0 dx=-29.0 width=39.4 l=47,110 r=63,74
CxScan: raw_ref=80.0 edge=55.0,92.0 best_raw_x=5 best_err=0.25 best_cxcy=55.2,119.3 scan=0:-1.9,10:2.4,20:6.8,30:11.0,40:15.1,50:19.1,60:22.8,70:26.4,80:29.8,90:32.9,100:35.8,110:38.6,120:41.1,130:43.4,140:45.6
ATGSeedDiag: seed=1@40,108/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(11.6) imip=0/9 pass=10111 acc=-1 ipm=64.6,115.1 inv=34.7,101.9 | 5(13.2) imip=0/15 pass=10111 acc=-1 ipm=115.3,101.1 inv=127.1,69.1
frame=922 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/57 raw=35/153 sel=57/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=8.9/12.1/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(56,100) md=40/1/96 cxcy=84.0,119.6 guide=34.15 atg=-60.0/-60.0/-60.0 pure=10.54/8.70 yaw=-2049 cmd=-2249 actual=-390 signed=0 rps=6033/0:5718/5561 duty=14/0 pwm=PWM2:14/PWM1:0 motor=2:14/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/57 centerNum=9/57 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/44 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.86@55,86 dx=-28.8 idx=0/8 dist=16/16 right=1:31.00@59,101 dx=-25.3 idx=10/29 dist=41/95 sel=1:36.35@52,99 dx=-32.3 idx=0/20 dist=40/86 edge=1:30.26@55.0,93.0 dx=-29.0 width=38.6 l=48,111 r=62,75
CxScan: raw_ref=80.0 edge=55.0,93.0 best_raw_x=5 best_err=0.25 best_cxcy=55.2,119.3 scan=0:-2.0,10:2.5,20:6.9,30:11.2,40:15.4,50:19.4,60:23.3,70:26.9,80:30.3,90:33.4,100:36.4,110:39.1,120:41.6,130:44.0,140:46.2
ATGSeedDiag: seed=1@37,108/1@155,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(8.9) imip=0/8 pass=10111 acc=-1 ipm=61.2,114.3 inv=27.7,99.5 | 1(12.1) imip=0/11 pass=10111 acc=-1 ipm=119.8,109.4 inv=147.3,85.1
frame=923 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/57 raw=32/153 sel=57/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.5/14.4/0.0/0.0 dist=0 begin=0/903 m0=(84,119) ml=(52,99) md=41/1/93 cxcy=84.0,119.6 guide=36.22 atg=-60.0/-60.0/-60.0 pure=10.41/8.66 yaw=-2173 cmd=-2373 actual=-463 signed=0 rps=6079/0:5965/5426 duty=14/0 pwm=PWM2:14/PWM1:0 motor=2:14/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=8/57 centerNum=8/57 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/43 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.48@56,87 dx=-28.0 idx=0/7 dist=14/14 right=1:31.69@58,101 dx=-25.9 idx=11/29 dist=40/94 sel=1:37.76@50,99 dx=-34.2 idx=0/20 dist=40/84 edge=1:31.11@54.0,93.0 dx=-30.0 width=39.3 l=49,112 r=59,74
CxScan: raw_ref=80.0 edge=54.0,93.0 best_raw_x=0 best_err=-0.82 best_cxcy=53.3,119.3 scan=0:-0.8,10:3.6,20:8.0,30:12.3,40:16.5,50:20.4,60:24.2,70:27.8,80:31.1,90:34.2,100:37.1,110:39.8,120:42.3,130:44.6,140:46.7
ATGSeedDiag: seed=1@34,108/1@155,93 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(7.5) imip=0/7 pass=10111 acc=-1 ipm=62.0,115.3 inv=28.5,102.5 | 10(14.4) imip=0/20 pass=10111 acc=-1 ipm=105.5,94.4 inv=106.6,59.7

- stopped_at: 2026-06-22T15:14:47+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive140
```
