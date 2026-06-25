# drive160

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive160-front_car_circle_drive160.log
- remote_log: /tmp/front_car_circle_drive160.log
- started_at: 2026-06-22T15:32:31+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive160 6
```

4704 /tmp/front_car_circle_drive160.log
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(13.0) imip=0/12 pass=10110 acc=-1 ipm=54.5,111.8 inv=16.6,92.4 | 1(6.9) imip=0/4 pass=10111 acc=-1 ipm=112.9,115.5 inv=145.1,101.9
frame=945 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=51/5 raw=155/17 sel=51/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.3/6.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,103) md=41/1/66 cxcy=84.0,119.6 guide=-45.02 atg=60.0/60.0/60.0 pure=-12.01/-11.93 yaw=3601 cmd=4001 actual=3263 signed=0 rps=0/8083:4325/8812 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=51/5 centerNum=51/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=51/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.11@115,104 dx=31.3 idx=9/31 dist=41/77 right=1:-25.98@110,89 dx=26.3 idx=0/4 dist=8/8 sel=1:-46.22@126,103 dx=41.5 idx=0/20 dist=40/60 edge=1:-31.34@112.5,96.0 dx=28.5 width=36.4 l=106,79 r=119,113
CxScan: raw_ref=80.0 edge=112.5,96.0 best_raw_x=140 best_err=-6.69 best_cxcy=107.0,119.7 scan=0:-51.8,10:-49.9,20:-47.9,30:-45.6,40:-43.2,50:-40.6,60:-37.7,70:-34.7,80:-31.3,90:-27.8,100:-24.0,110:-19.9,120:-15.7,130:-11.3,140:-6.7
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(12.3) imip=33/50 pass=10110 acc=-1 ipm=138.6,77.1 inv=133.8,43.0 | 1(6.9) imip=0/4 pass=10111 acc=-1 ipm=112.9,115.5 inv=145.1,101.9
frame=946 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=51/5 raw=154/17 sel=51/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/5.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,103) md=41/1/66 cxcy=84.0,119.6 guide=-44.81 atg=60.0/60.0/60.0 pure=-12.01/-11.89 yaw=3585 cmd=3985 actual=3272 signed=0 rps=0/8071:4543/9442 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=51/5 centerNum=51/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=51/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.68@114,104 dx=29.5 idx=9/30 dist=40/78 right=1:-25.68@110,89 dx=25.9 idx=0/4 dist=8/8 sel=1:-46.18@125,103 dx=41.4 idx=0/20 dist=40/60 edge=1:-32.66@114.0,96.0 dx=30.0 width=35.4 l=109,79 r=119,113
CxScan: raw_ref=80.0 edge=114.0,96.0 best_raw_x=140 best_err=-8.49 best_cxcy=107.0,119.7 scan=0:-52.5,10:-50.7,20:-48.7,30:-46.5,40:-44.2,50:-41.6,60:-38.9,70:-35.9,80:-32.7,90:-29.2,100:-25.5,110:-21.5,120:-17.4,130:-13.0,140:-8.5
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.7) imip=0/20 pass=10110 acc=-1 ipm=67.0,98.1 inv=50.3,65.1 | 1(5.9) imip=0/4 pass=10111 acc=-1 ipm=112.9,115.5 inv=145.1,101.9
frame=947 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=51/5 raw=154/17 sel=51/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/7.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,103) md=41/1/66 cxcy=84.0,119.6 guide=-44.81 atg=60.0/60.0/60.0 pure=-11.91/-11.89 yaw=3585 cmd=3985 actual=3272 signed=0 rps=0/8071:4698/10000 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=51/5 centerNum=51/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=51/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.87@115,104 dx=31.3 idx=9/31 dist=41/76 right=1:-25.65@110,89 dx=25.9 idx=0/4 dist=8/8 sel=1:-46.16@125,103 dx=41.4 idx=0/20 dist=40/60 edge=1:-31.34@112.5,96.0 dx=28.5 width=36.4 l=106,79 r=119,113
CxScan: raw_ref=80.0 edge=112.5,96.0 best_raw_x=140 best_err=-6.69 best_cxcy=107.0,119.7 scan=0:-51.8,10:-49.9,20:-47.9,30:-45.6,40:-43.2,50:-40.6,60:-37.7,70:-34.7,80:-31.3,90:-27.8,100:-24.0,110:-19.9,120:-15.7,130:-11.3,140:-6.7
ATGSeedDiag: seed=1@4,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(12.5) imip=38/50 pass=10100 acc=-1 ipm=149.9,79.0 inv=148.0,44.4 | 3(7.1) imip=0/4 pass=10111 acc=-1 ipm=117.2,113.8 inv=150.9,96.5
frame=948 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=51/5 raw=155/17 sel=51/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.8/5.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,103) md=41/1/66 cxcy=84.0,119.6 guide=-44.39 atg=60.0/60.0/60.0 pure=-11.86/-11.81 yaw=3551 cmd=3951 actual=3258 signed=0 rps=0/8048:4560/9652 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=51/5 centerNum=51/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=51/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.10@116,104 dx=31.7 idx=9/31 dist=41/76 right=1:-25.43@110,89 dx=25.6 idx=0/4 dist=8/8 sel=1:-46.01@125,103 dx=41.3 idx=0/20 dist=40/60 edge=1:-31.34@112.5,96.0 dx=28.5 width=36.4 l=106,79 r=119,113
CxScan: raw_ref=80.0 edge=112.5,96.0 best_raw_x=140 best_err=-6.69 best_cxcy=107.0,119.7 scan=0:-51.8,10:-49.9,20:-47.9,30:-45.6,40:-43.2,50:-40.6,60:-37.7,70:-34.7,80:-31.3,90:-27.8,100:-24.0,110:-19.9,120:-15.7,130:-11.3,140:-6.7
ATGSeedDiag: seed=1@4,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.8) imip=0/20 pass=10110 acc=-1 ipm=67.0,98.1 inv=50.3,65.2 | 3(5.3) imip=0/4 pass=10111 acc=-1 ipm=117.2,113.8 inv=150.9,96.5
frame=949 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=153/17 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.9/5.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,103) md=41/1/68 cxcy=84.0,119.6 guide=-44.19 atg=60.0/60.0/60.0 pure=-11.76/-11.65 yaw=3535 cmd=3935 actual=3256 signed=0 rps=0/8036:4675/9999 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.11@116,103 dx=32.0 idx=9/31 dist=41/80 right=1:-25.35@110,89 dx=25.5 idx=0/4 dist=8/8 sel=1:-45.27@125,102 dx=41.3 idx=0/20 dist=40/62 edge=1:-31.34@112.5,96.0 dx=28.5 width=36.4 l=106,79 r=119,113
CxScan: raw_ref=80.0 edge=112.5,96.0 best_raw_x=140 best_err=-6.69 best_cxcy=107.0,119.7 scan=0:-51.8,10:-49.9,20:-47.9,30:-45.6,40:-43.2,50:-40.6,60:-37.7,70:-34.7,80:-31.3,90:-27.8,100:-24.0,110:-19.9,120:-15.7,130:-11.3,140:-6.7
ATGSeedDiag: seed=1@5,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.9) imip=0/20 pass=10110 acc=-1 ipm=67.3,97.9 inv=50.9,64.8 | 3(5.7) imip=0/4 pass=10111 acc=-1 ipm=117.2,113.8 inv=150.8,96.4
frame=950 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=154/17 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.7/4.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=40/1/69 cxcy=84.0,119.6 guide=-43.30 atg=60.0/60.0/60.0 pure=-11.64/-11.56 yaw=3464 cmd=3853 actual=3269 signed=0 rps=0/7971:4372/9489 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.83@116,103 dx=31.8 idx=9/31 dist=41/80 right=1:-25.10@109,89 dx=25.2 idx=0/4 dist=8/8 sel=1:-45.04@125,102 dx=41.3 idx=0/20 dist=40/62 edge=1:-31.07@112.5,95.5 dx=28.5 width=37.3 l=106,78 r=119,113
CxScan: raw_ref=80.0 edge=112.5,95.5 best_raw_x=140 best_err=-6.62 best_cxcy=107.0,119.7 scan=0:-51.5,10:-49.6,20:-47.6,30:-45.3,40:-42.9,50:-40.3,60:-37.4,70:-34.4,80:-31.1,90:-27.5,100:-23.7,110:-19.7,120:-15.5,130:-11.1,140:-6.6
ATGSeedDiag: seed=1@5,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(13.7) imip=39/51 pass=10100 acc=-1 ipm=152.1,77.7 inv=149.0,43.4 | 1(4.0) imip=0/4 pass=10111 acc=-1 ipm=112.9,115.5 inv=145.1,101.9
frame=951 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=152/18 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.2/6.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=40/1/71 cxcy=84.0,119.6 guide=-43.03 atg=60.0/60.0/60.0 pure=-11.59/-11.42 yaw=3442 cmd=3748 actual=3289 signed=0 rps=0/7841:4322/9444 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.53@114,103 dx=30.3 idx=8/30 dist=40/81 right=1:-24.90@109,89 dx=25.0 idx=0/4 dist=8/8 sel=1:-44.84@125,101 dx=41.1 idx=0/20 dist=40/64 edge=1:-30.44@111.5,96.0 dx=27.5 width=37.2 l=104,79 r=119,113
CxScan: raw_ref=80.0 edge=111.5,96.0 best_raw_x=140 best_err=-5.48 best_cxcy=107.0,119.7 scan=0:-51.4,10:-49.4,20:-47.3,30:-45.0,40:-42.6,50:-39.9,60:-37.0,70:-33.8,80:-30.4,90:-26.8,100:-22.9,110:-18.8,120:-14.5,130:-10.1,140:-5.5
ATGSeedDiag: seed=1@6,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.2) imip=0/20 pass=10110 acc=-1 ipm=67.7,97.8 inv=51.4,64.7 | 2(6.3) imip=0/4 pass=10111 acc=-1 ipm=115.0,114.5 inv=147.5,98.6
frame=952 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=153/18 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.2/6.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,101) md=42/1/71 cxcy=84.0,119.6 guide=-42.76 atg=60.0/60.0/60.0 pure=-11.59/-11.40 yaw=3420 cmd=3651 actual=3305 signed=0 rps=0/7723:4019/8940 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.23@114,103 dx=30.1 idx=8/30 dist=41/82 right=1:-24.66@109,89 dx=24.7 idx=0/4 dist=8/8 sel=1:-44.82@125,101 dx=41.0 idx=0/20 dist=40/64 edge=1:-30.44@111.5,96.0 dx=27.5 width=37.2 l=104,79 r=119,113
CxScan: raw_ref=80.0 edge=111.5,96.0 best_raw_x=140 best_err=-5.48 best_cxcy=107.0,119.7 scan=0:-51.4,10:-49.4,20:-47.3,30:-45.0,40:-42.6,50:-39.9,60:-37.0,70:-33.8,80:-30.4,90:-26.8,100:-22.9,110:-18.8,120:-14.5,130:-10.1,140:-5.5
ATGSeedDiag: seed=1@6,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.2) imip=0/20 pass=10110 acc=-1 ipm=67.5,97.9 inv=51.2,64.9 | 1(6.7) imip=0/4 pass=10111 acc=-1 ipm=112.9,115.4 inv=144.7,101.6
frame=953 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=153/18 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.4/7.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,101) md=42/1/69 cxcy=84.0,119.6 guide=-42.49 atg=60.0/60.0/60.0 pure=-11.51/-11.42 yaw=3399 cmd=3597 actual=3300 signed=0 rps=0/7664:4054/9475 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.52@115,103 dx=30.7 idx=8/30 dist=40/80 right=1:-26.56@111,88 dx=27.4 idx=0/5 dist=10/10 sel=1:-44.74@125,101 dx=40.9 idx=0/20 dist=40/62 edge=1:-31.07@112.5,95.5 dx=28.5 width=37.1 l=104,79 r=121,112
CxScan: raw_ref=80.0 edge=112.5,95.5 best_raw_x=140 best_err=-6.62 best_cxcy=107.0,119.7 scan=0:-51.5,10:-49.6,20:-47.6,30:-45.3,40:-42.9,50:-40.3,60:-37.4,70:-34.4,80:-31.1,90:-27.5,100:-23.7,110:-19.7,120:-15.5,130:-11.1,140:-6.6
ATGSeedDiag: seed=1@6,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(13.4) imip=32/51 pass=10110 acc=-1 ipm=136.1,74.1 inv=128.7,41.0 | 4(7.2) imip=0/5 pass=10111 acc=-1 ipm=119.2,112.8 inv=152.9,93.5
frame=954 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=152/19 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.3/8.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(122,101) md=41/1/69 cxcy=84.0,119.6 guide=-42.67 atg=60.0/60.0/60.0 pure=-11.50/-11.39 yaw=3413 cmd=3650 actual=3295 signed=0 rps=0/7727:3845/9390 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.66@116,102 dx=32.4 idx=8/31 dist=41/79 right=1:-26.35@111,88 dx=27.1 idx=0/5 dist=10/10 sel=1:-44.36@125,101 dx=40.7 idx=0/20 dist=40/62 edge=1:-30.81@112.5,95.0 dx=28.5 width=38.0 l=104,78 r=121,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@7,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.3) imip=0/20 pass=10110 acc=-1 ipm=67.7,97.5 inv=51.5,64.3 | 1(8.7) imip=0/5 pass=10111 acc=-1 ipm=112.7,115.4 inv=144.4,101.5
frame=955 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=153/19 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.4/9.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(122,101) md=41/1/69 cxcy=84.0,119.6 guide=-42.67 atg=60.0/60.0/60.0 pure=-11.51/-11.39 yaw=3413 cmd=3651 actual=3294 signed=0 rps=0/7728:3903/9591 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.04@115,102 dx=30.5 idx=8/30 dist=40/80 right=1:-26.07@111,88 dx=26.8 idx=0/5 dist=10/10 sel=1:-44.18@125,101 dx=40.7 idx=0/20 dist=40/62 edge=1:-30.81@112.5,95.0 dx=28.5 width=38.0 l=104,78 r=121,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@7,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.4) imip=0/20 pass=10110 acc=-1 ipm=67.5,97.7 inv=51.3,64.5 | 1(9.3) imip=0/5 pass=10111 acc=-1 ipm=112.7,115.3 inv=144.2,101.3
frame=956 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=151/20 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.4/7.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,101) md=42/1/71 cxcy=84.0,119.6 guide=-42.77 atg=60.0/60.0/60.0 pure=-11.48/-11.35 yaw=3422 cmd=3690 actual=3288 signed=0 rps=0/7776:4118/9617 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.47@115,102 dx=30.9 idx=8/30 dist=40/81 right=1:-25.76@110,88 dx=26.4 idx=0/5 dist=10/10 sel=1:-44.23@125,101 dx=40.8 idx=0/20 dist=40/64 edge=1:-31.25@113.0,95.0 dx=29.0 width=37.6 l=105,78 r=121,112
CxScan: raw_ref=80.0 edge=113.0,95.0 best_raw_x=140 best_err=-7.14 best_cxcy=107.0,119.7 scan=0:-51.5,10:-49.6,20:-47.5,30:-45.3,40:-42.9,50:-40.3,60:-37.5,70:-34.5,80:-31.2,90:-27.8,100:-24.0,110:-20.1,120:-15.9,130:-11.6,140:-7.1
ATGSeedDiag: seed=1@8,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(12.4) imip=34/51 pass=10110 acc=-1 ipm=141.2,74.2 inv=134.1,41.0 | 3(7.0) imip=0/5 pass=10111 acc=-1 ipm=116.6,113.4 inv=148.8,95.4
frame=957 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=152/19 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.7/8.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,101) md=42/1/71 cxcy=84.0,119.6 guide=-42.77 atg=60.0/60.0/60.0 pure=-11.48/-11.24 yaw=3422 cmd=3771 actual=3247 signed=0 rps=0/7887:4287/9280 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.25@115,102 dx=30.8 idx=8/30 dist=40/81 right=1:-26.20@111,88 dx=27.1 idx=0/5 dist=10/10 sel=1:-44.31@125,101 dx=40.8 idx=0/20 dist=40/64 edge=1:-31.25@113.0,95.0 dx=29.0 width=38.5 l=104,78 r=122,112
CxScan: raw_ref=80.0 edge=113.0,95.0 best_raw_x=140 best_err=-7.14 best_cxcy=107.0,119.7 scan=0:-51.5,10:-49.6,20:-47.5,30:-45.3,40:-42.9,50:-40.3,60:-37.5,70:-34.5,80:-31.2,90:-27.8,100:-24.0,110:-20.1,120:-15.9,130:-11.6,140:-7.1
ATGSeedDiag: seed=1@8,108/1@141,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.7) imip=0/20 pass=10110 acc=-1 ipm=67.9,97.6 inv=51.9,64.4 | 1(8.2) imip=0/5 pass=10111 acc=-1 ipm=113.0,115.1 inv=144.3,100.5

- stopped_at: 2026-06-22T15:32:43+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive160
```
