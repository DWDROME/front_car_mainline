# drive159

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive159-front_car_circle_drive159.log
- remote_log: /tmp/front_car_circle_drive159.log
- started_at: 2026-06-22T15:31:30+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive159 6
```

4788 /tmp/front_car_circle_drive159.log
ATGSeedDiag: seed=1@4,101/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(13.9) imip=0/11 pass=10110 acc=-1 ipm=52.0,112.0 inv=11.1,93.0 | 3(9.6) imip=0/6 pass=10111 acc=-1 ipm=114.3,113.6 inv=144.1,96.1
frame=918 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/7 raw=154/25 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.2/9.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,101) md=41/1/71 cxcy=84.0,119.6 guide=-41.72 atg=60.0/60.0/60.0 pure=-11.83/-11.67 yaw=3338 cmd=3538 actual=2937 signed=0 rps=0/7623:4805/8967 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/7 centerNum=52/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.02@112,103 dx=28.1 idx=9/30 dist=41/82 right=1:-26.65@112,87 dx=27.8 idx=0/6 dist=12/12 sel=1:-43.11@123,102 dx=38.6 idx=0/20 dist=40/64 edge=1:-31.85@114.0,94.5 dx=30.0 width=37.7 l=107,77 r=121,112
CxScan: raw_ref=80.0 edge=114.0,94.5 best_raw_x=140 best_err=-8.23 best_cxcy=107.0,119.7 scan=0:-51.7,10:-49.8,20:-47.8,30:-45.6,40:-43.3,50:-40.7,60:-38.0,70:-35.0,80:-31.8,90:-28.4,100:-24.8,110:-20.9,120:-16.9,130:-12.6,140:-8.2
ATGSeedDiag: seed=1@4,101/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(12.2) imip=0/19 pass=10110 acc=-1 ipm=63.8,97.7 inv=45.5,64.7 | 5(9.2) imip=0/6 pass=10111 acc=-1 ipm=118.5,112.4 inv=150.6,92.4
frame=919 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/7 raw=153/24 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.2/10.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,101) md=41/1/71 cxcy=84.0,119.6 guide=-41.62 atg=60.0/60.0/60.0 pure=-11.82/-11.62 yaw=3330 cmd=3530 actual=2943 signed=0 rps=0/7618:4950/9412 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/7 centerNum=52/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.03@112,103 dx=28.1 idx=9/30 dist=40/81 right=1:-27.02@112,87 dx=28.3 idx=0/6 dist=12/12 sel=1:-43.01@123,101 dx=38.5 idx=0/20 dist=40/64 edge=1:-31.85@114.0,94.5 dx=30.0 width=37.7 l=107,77 r=121,112
CxScan: raw_ref=80.0 edge=114.0,94.5 best_raw_x=140 best_err=-8.23 best_cxcy=107.0,119.7 scan=0:-51.7,10:-49.8,20:-47.8,30:-45.6,40:-43.3,50:-40.7,60:-38.0,70:-35.0,80:-31.8,90:-28.4,100:-24.8,110:-20.9,120:-16.9,130:-12.6,140:-8.2
ATGSeedDiag: seed=1@4,101/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(12.2) imip=0/19 pass=10110 acc=-1 ipm=63.8,97.7 inv=45.6,64.6 | 2(10.3) imip=0/6 pass=10111 acc=-1 ipm=112.4,114.4 inv=141.6,98.5
frame=920 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/7 raw=153/24 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.3/10.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,101) md=41/1/71 cxcy=84.0,119.6 guide=-41.93 atg=60.0/60.0/60.0 pure=-11.82/-11.67 yaw=3355 cmd=3555 actual=2953 signed=0 rps=0/7635:4795/8816 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/7 centerNum=52/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.09@112,103 dx=28.2 idx=9/30 dist=41/81 right=1:-27.11@112,87 dx=28.4 idx=0/6 dist=12/12 sel=1:-43.15@123,102 dx=38.7 idx=0/20 dist=40/64 edge=1:-31.25@113.0,95.0 dx=29.0 width=37.6 l=105,78 r=121,112
CxScan: raw_ref=80.0 edge=113.0,95.0 best_raw_x=140 best_err=-7.14 best_cxcy=107.0,119.7 scan=0:-51.5,10:-49.6,20:-47.5,30:-45.3,40:-42.9,50:-40.3,60:-37.5,70:-34.5,80:-31.2,90:-27.8,100:-24.0,110:-20.1,120:-15.9,130:-11.6,140:-7.1
ATGSeedDiag: seed=1@4,102/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.3) imip=0/20 pass=10110 acc=-1 ipm=65.7,96.3 inv=49.1,62.6 | 2(10.4) imip=0/6 pass=10111 acc=-1 ipm=112.4,114.4 inv=141.7,98.5
frame=921 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/7 raw=154/23 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.6/10.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(119,103) md=40/1/69 cxcy=84.0,119.6 guide=-41.65 atg=60.0/60.0/60.0 pure=-11.97/-11.90 yaw=3332 cmd=3532 actual=2938 signed=0 rps=0/7619:5174/8802 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/7 centerNum=52/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.90@113,103 dx=28.5 idx=9/30 dist=41/81 right=1:-27.39@113,87 dx=28.7 idx=0/6 dist=12/12 sel=1:-43.59@123,102 dx=39.1 idx=0/20 dist=40/62 edge=1:-31.25@113.0,95.0 dx=29.0 width=37.6 l=105,78 r=121,112
CxScan: raw_ref=80.0 edge=113.0,95.0 best_raw_x=140 best_err=-7.14 best_cxcy=107.0,119.7 scan=0:-51.5,10:-49.6,20:-47.5,30:-45.3,40:-42.9,50:-40.3,60:-37.5,70:-34.5,80:-31.2,90:-27.8,100:-24.0,110:-20.1,120:-15.9,130:-11.6,140:-7.1
ATGSeedDiag: seed=1@4,102/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(12.6) imip=0/11 pass=10110 acc=-1 ipm=52.3,112.4 inv=11.1,93.9 | 5(10.2) imip=0/6 pass=10111 acc=-1 ipm=119.1,112.4 inv=151.9,92.4
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/7 raw=154/23 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/9.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(119,103) md=40/1/69 cxcy=84.0,119.6 guide=-41.92 atg=60.0/60.0/60.0 pure=-11.99/-11.90 yaw=3353 cmd=3553 actual=2894 signed=0 rps=0/7634:4920/8253 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/7 centerNum=52/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-36.08@113,104 dx=28.6 idx=9/30 dist=40/80 right=1:-27.42@113,87 dx=28.8 idx=0/6 dist=12/12 sel=1:-44.40@123,103 dx=39.3 idx=0/20 dist=40/62 edge=1:-31.25@113.0,95.0 dx=29.0 width=37.6 l=105,78 r=121,112
CxScan: raw_ref=80.0 edge=113.0,95.0 best_raw_x=140 best_err=-7.14 best_cxcy=107.0,119.7 scan=0:-51.5,10:-49.6,20:-47.5,30:-45.3,40:-42.9,50:-40.3,60:-37.5,70:-34.5,80:-31.2,90:-27.8,100:-24.0,110:-20.1,120:-15.9,130:-11.6,140:-7.1
ATGSeedDiag: seed=1@4,102/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(12.5) imip=0/11 pass=10110 acc=-1 ipm=52.3,112.4 inv=11.1,93.9 | 3(9.3) imip=0/6 pass=10111 acc=-1 ipm=114.7,113.7 inv=145.3,96.3
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/7 raw=154/23 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/11.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=42/1/69 cxcy=84.0,119.6 guide=-41.55 atg=60.0/60.0/60.0 pure=-11.98/-11.90 yaw=3324 cmd=3524 actual=2856 signed=0 rps=0/7614:5054/8903 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/7 centerNum=52/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-34.29@111,104 dx=26.7 idx=9/29 dist=40/82 right=1:-27.55@113,87 dx=28.9 idx=0/6 dist=12/12 sel=1:-43.48@123,102 dx=38.9 idx=0/20 dist=40/62 edge=1:-31.68@113.5,95.0 dx=29.5 width=38.0 l=105,78 r=122,112
CxScan: raw_ref=80.0 edge=113.5,95.0 best_raw_x=140 best_err=-7.73 best_cxcy=107.0,119.7 scan=0:-51.7,10:-49.8,20:-47.8,30:-45.6,40:-43.3,50:-40.7,60:-37.9,70:-34.9,80:-31.7,90:-28.2,100:-24.5,110:-20.6,120:-16.5,130:-12.2,140:-7.7
ATGSeedDiag: seed=1@4,102/1@136,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(12.5) imip=0/11 pass=10110 acc=-1 ipm=52.3,112.4 inv=11.1,93.9 | 1(11.3) imip=0/6 pass=10111 acc=-1 ipm=110.7,115.4 inv=139.7,101.6
frame=924 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/7 raw=154/22 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.9/9.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=42/1/69 cxcy=84.0,119.6 guide=-41.55 atg=60.0/60.0/60.0 pure=-11.90/-11.84 yaw=3324 cmd=3524 actual=2859 signed=0 rps=0/7614:5136/9563 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/7 centerNum=52/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.46@112,103 dx=28.2 idx=9/30 dist=40/79 right=1:-27.61@113,87 dx=29.0 idx=0/6 dist=12/12 sel=1:-43.39@123,102 dx=38.9 idx=0/20 dist=40/62 edge=1:-30.81@112.5,95.0 dx=28.5 width=38.9 l=103,78 r=122,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@4,102/1@136,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(13.9) imip=33/51 pass=10110 acc=-1 ipm=137.3,75.6 inv=131.2,42.0 | 3(9.2) imip=0/6 pass=10111 acc=-1 ipm=115.1,113.7 inv=146.0,96.2
frame=925 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=153/22 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.2/7.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(119,103) md=40/1/69 cxcy=84.0,119.6 guide=-41.75 atg=60.0/60.0/60.0 pure=-11.91/-11.84 yaw=3340 cmd=3540 actual=2873 signed=0 rps=0/7625:4860/9257 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.17@114,103 dx=30.3 idx=9/31 dist=41/78 right=1:-25.57@110,88 dx=26.2 idx=0/5 dist=10/10 sel=1:-43.65@123,102 dx=39.2 idx=0/20 dist=40/62 edge=1:-32.12@114.0,95.0 dx=30.0 width=36.1 l=108,78 r=120,112
CxScan: raw_ref=80.0 edge=114.0,95.0 best_raw_x=140 best_err=-8.32 best_cxcy=107.0,119.7 scan=0:-51.9,10:-50.1,20:-48.1,30:-45.9,40:-43.6,50:-41.0,60:-38.3,70:-35.3,80:-32.1,90:-28.7,100:-25.0,110:-21.1,120:-17.0,130:-12.7,140:-8.3
ATGSeedDiag: seed=1@4,103/1@136,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(14.2) imip=33/51 pass=10110 acc=-1 ipm=137.5,75.7 inv=131.5,42.0 | 4(7.5) imip=0/5 pass=10111 acc=-1 ipm=117.3,113.0 inv=149.4,94.2
frame=926 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=154/22 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/8.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=41/1/69 cxcy=84.0,119.6 guide=-42.80 atg=60.0/60.0/60.0 pure=-11.89/-11.77 yaw=3424 cmd=3624 actual=2874 signed=0 rps=0/7684:4887/9267 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-36.24@113,103 dx=28.8 idx=9/30 dist=40/79 right=1:-25.73@110,88 dx=26.4 idx=0/5 dist=10/10 sel=1:-43.99@124,102 dx=39.6 idx=0/20 dist=40/62 edge=1:-30.81@112.5,95.0 dx=28.5 width=37.2 l=105,78 r=120,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@4,104/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(12.5) imip=33/51 pass=10110 acc=-1 ipm=137.6,75.7 inv=131.6,42.0 | 2(8.6) imip=0/5 pass=10111 acc=-1 ipm=113.2,114.5 inv=143.6,98.6
frame=927 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=154/21 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.0/6.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(122,102) md=42/1/69 cxcy=84.0,119.6 guide=-43.02 atg=60.0/60.0/60.0 pure=-11.78/-11.68 yaw=3441 cmd=3641 actual=2867 signed=0 rps=0/7696:4505/8499 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.56@115,103 dx=30.6 idx=9/31 dist=40/77 right=1:-25.68@110,88 dx=26.3 idx=0/5 dist=10/10 sel=1:-44.13@124,102 dx=39.8 idx=0/20 dist=40/62 edge=1:-30.81@112.5,95.0 dx=28.5 width=37.2 l=105,78 r=120,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@4,104/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(14.0) imip=34/51 pass=10110 acc=-1 ipm=139.9,75.7 inv=134.0,42.0 | 3(6.4) imip=0/5 pass=10111 acc=-1 ipm=115.5,113.7 inv=146.9,96.2
frame=928 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=154/21 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.4/7.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=41/1/71 cxcy=84.0,119.6 guide=-42.71 atg=60.0/60.0/60.0 pure=-11.74/-11.54 yaw=3417 cmd=3617 actual=2865 signed=0 rps=0/7679:4419/8629 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.19@114,103 dx=30.3 idx=9/31 dist=41/80 right=1:-25.96@111,88 dx=26.6 idx=0/5 dist=10/10 sel=1:-43.90@124,101 dx=39.7 idx=0/20 dist=40/64 edge=1:-30.81@112.5,95.0 dx=28.5 width=37.2 l=105,78 r=120,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@4,105/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.4) imip=0/20 pass=10110 acc=-1 ipm=66.1,97.0 inv=49.4,63.6 | 4(7.4) imip=0/5 pass=10111 acc=-1 ipm=117.8,113.0 inv=150.3,94.2
frame=929 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=154/21 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/7.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=41/1/71 cxcy=84.0,119.6 guide=-42.60 atg=60.0/60.0/60.0 pure=-11.74/-11.54 yaw=3408 cmd=3608 actual=2887 signed=0 rps=0/7673:4231/8695 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.14@114,103 dx=30.3 idx=9/31 dist=40/79 right=1:-25.96@111,88 dx=26.7 idx=0/5 dist=10/10 sel=1:-43.82@124,101 dx=39.6 idx=0/20 dist=40/64 edge=1:-30.81@112.5,95.0 dx=28.5 width=37.2 l=105,78 r=120,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@4,104/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.7) imip=0/20 pass=10110 acc=-1 ipm=66.0,96.9 inv=49.3,63.5 | 4(7.5) imip=0/5 pass=10111 acc=-1 ipm=117.8,113.0 inv=150.3,94.2
frame=930 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=154/21 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.5/8.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,102) md=41/1/69 cxcy=84.0,119.6 guide=-42.91 atg=60.0/60.0/60.0 pure=-11.84/-11.77 yaw=3433 cmd=3633 actual=2901 signed=0 rps=0/7690:4480/9231 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.67@115,103 dx=30.5 idx=9/31 dist=40/79 right=1:-26.24@111,88 dx=27.0 idx=0/5 dist=10/10 sel=1:-44.08@124,102 dx=39.7 idx=0/20 dist=40/62 edge=1:-30.81@112.5,95.0 dx=28.5 width=37.2 l=105,78 r=120,112
CxScan: raw_ref=80.0 edge=112.5,95.0 best_raw_x=140 best_err=-6.55 best_cxcy=107.0,119.7 scan=0:-51.2,10:-49.3,20:-47.3,30:-45.0,40:-42.6,50:-40.0,60:-37.2,70:-34.1,80:-30.8,90:-27.3,100:-23.5,110:-19.5,120:-15.4,130:-11.0,140:-6.6
ATGSeedDiag: seed=1@4,104/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(13.5) imip=34/51 pass=10110 acc=-1 ipm=139.9,76.0 inv=134.2,42.2 | 4(8.6) imip=0/5 pass=10111 acc=-1 ipm=118.0,113.0 inv=150.9,94.1

- stopped_at: 2026-06-22T15:31:46+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive159
```
