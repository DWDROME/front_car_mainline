# drive152

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive152-front_car_circle_drive152.log
- remote_log: /tmp/front_car_circle_drive152.log
- started_at: 2026-06-22T15:26:09+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive152 6
```

4769 /tmp/front_car_circle_drive152.log
ATGSeedDiag: seed=1@10,108/1@130,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(16.4) imip=39/58 pass=10100 acc=-1 ipm=145.7,64.0 inv=130.8,35.0 | 3(22.9) imip=0/13 pass=10111 acc=-1 ipm=109.4,110.4 inv=128.5,87.5
frame=915 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=157/54 sel=59/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.9/31.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(104,97) md=33/1/87 cxcy=84.0,119.6 guide=-22.97 atg=60.0/60.0/60.0 pure=-9.88/-9.97 yaw=1608 cmd=1408 actual=2140 signed=0 rps=3071/6929:5590/7572 duty=3/18 pwm=PWM2:3/PWM1:18 motor=2:3/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.28@101,98 dx=17.3 idx=5/24 dist=33/97 right=1:-27.98@119,77 dx=35.1 idx=0/13 dist=34/40 sel=1:-25.52@106,96 dx=22.3 idx=0/16 dist=32/78 edge=1:-21.68@104.0,92.5 dx=20.0 width=61.8 l=74,85 r=134,100
CxScan: raw_ref=80.0 edge=104.0,92.5 best_raw_x=130 best_err=-0.94 best_cxcy=103.2,119.7 scan=0:-45.4,10:-43.1,20:-40.7,30:-38.0,40:-35.2,50:-32.1,60:-28.8,70:-25.4,80:-21.7,90:-17.8,100:-13.7,110:-9.6,120:-5.3,130:-0.9,140:3.4
ATGSeedDiag: seed=1@9,108/1@130,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(16.9) imip=39/58 pass=10100 acc=-1 ipm=145.4,64.0 inv=130.5,35.0 | 5(31.8) imip=0/15 pass=10111 acc=-1 ipm=112.4,107.6 inv=130.2,81.0
frame=916 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=157/55 sel=59/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.0/32.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(104,97) md=33/1/86 cxcy=84.0,119.6 guide=-23.69 atg=60.0/60.0/60.0 pure=-9.88/-9.95 yaw=1658 cmd=1458 actual=2145 signed=0 rps=3001/6999:5955/8520 duty=3/17 pwm=PWM2:3/PWM1:17 motor=2:3/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.86@101,98 dx=16.9 idx=5/24 dist=32/97 right=1:-26.17@116,77 dx=32.1 idx=0/12 dist=32/41 sel=1:-25.22@106,96 dx=21.9 idx=0/16 dist=32/78 edge=1:-21.97@104.5,92.0 dx=20.5 width=61.1 l=75,84 r=134,100
CxScan: raw_ref=80.0 edge=104.5,92.0 best_raw_x=135 best_err=0.66 best_cxcy=105.1,119.7 scan=0:-45.4,10:-43.1,20:-40.7,30:-38.1,40:-35.3,50:-32.3,60:-29.0,70:-25.6,80:-22.0,90:-18.1,100:-14.2,110:-10.0,120:-5.8,130:-1.5,140:2.8
ATGSeedDiag: seed=1@8,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(16.0) imip=39/58 pass=10100 acc=-1 ipm=145.2,64.0 inv=130.3,35.0 | 5(32.9) imip=0/15 pass=10111 acc=-1 ipm=112.2,107.5 inv=129.9,81.0
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=60/16 raw=158/55 sel=60/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=20.3/32.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(104,96) md=33/1/87 cxcy=84.0,119.6 guide=-24.13 atg=60.0/60.0/60.0 pure=-9.88/-9.84 yaw=1689 cmd=1489 actual=2142 signed=0 rps=2960/7040:5144/7479 duty=3/18 pwm=PWM2:3/PWM1:18 motor=2:3/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=60/16 centerNum=60/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.25@101,98 dx=16.5 idx=6/24 dist=33/100 right=1:-28.03@119,77 dx=35.3 idx=0/13 dist=34/40 sel=1:-24.94@106,95 dx=22.0 idx=0/16 dist=32/78 edge=1:-21.38@103.5,93.0 dx=19.5 width=63.1 l=73,85 r=134,101
CxScan: raw_ref=80.0 edge=103.5,93.0 best_raw_x=130 best_err=-0.38 best_cxcy=103.2,119.7 scan=0:-45.4,10:-43.1,20:-40.6,30:-37.9,40:-35.1,50:-32.0,60:-28.6,70:-25.1,80:-21.4,90:-17.4,100:-13.3,110:-9.1,120:-4.8,130:-0.4,140:4.0
ATGSeedDiag: seed=1@7,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=58(20.3) imip=48/59 pass=10100 acc=-1 ipm=164.4,68.6 inv=152.2,37.4 | 5(32.4) imip=0/15 pass=10111 acc=-1 ipm=112.0,107.7 inv=129.6,81.2
frame=919 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=60/16 raw=158/55 sel=60/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.9/32.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(104,97) md=33/1/87 cxcy=84.0,119.6 guide=-23.62 atg=60.0/60.0/60.0 pure=-9.88/-9.90 yaw=1654 cmd=1454 actual=2160 signed=0 rps=3008/6992:5642/7935 duty=3/18 pwm=PWM2:3/PWM1:18 motor=2:3/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=60/16 centerNum=60/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.89@99,99 dx=14.9 idx=6/23 dist=32/100 right=1:-27.85@119,77 dx=34.9 idx=0/13 dist=34/40 sel=1:-25.09@106,96 dx=21.9 idx=0/16 dist=32/78 edge=1:-20.87@103.0,93.0 dx=19.0 width=62.1 l=73,85 r=133,101
CxScan: raw_ref=80.0 edge=103.0,93.0 best_raw_x=130 best_err=0.20 best_cxcy=103.2,119.7 scan=0:-45.1,10:-42.8,20:-40.3,30:-37.6,40:-34.7,50:-31.5,60:-28.2,70:-24.6,80:-20.9,90:-16.9,100:-12.8,110:-8.5,120:-4.2,130:0.2,140:4.6
ATGSeedDiag: seed=1@6,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(12.9) imip=0/12 pass=10110 acc=-1 ipm=54.2,111.5 inv=16.5,91.5 | 5(32.1) imip=0/15 pass=10111 acc=-1 ipm=111.6,107.7 inv=128.9,81.3
frame=920 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=159/55 sel=59/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.0/31.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(103,97) md=32/1/86 cxcy=84.0,119.6 guide=-24.07 atg=60.0/60.0/60.0 pure=-9.88/-10.01 yaw=1685 cmd=1485 actual=2185 signed=0 rps=2965/7035:5520/7358 duty=3/18 pwm=PWM2:3/PWM1:18 motor=2:3/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.86@99,100 dx=14.8 idx=6/23 dist=32/98 right=1:-27.78@119,77 dx=34.6 idx=0/13 dist=34/40 sel=1:-24.95@106,96 dx=21.6 idx=0/16 dist=32/78 edge=1:-21.68@104.0,92.5 dx=20.0 width=60.4 l=75,84 r=133,101
CxScan: raw_ref=80.0 edge=104.0,92.5 best_raw_x=130 best_err=-0.94 best_cxcy=103.2,119.7 scan=0:-45.4,10:-43.1,20:-40.7,30:-38.0,40:-35.2,50:-32.1,60:-28.8,70:-25.4,80:-21.7,90:-17.8,100:-13.7,110:-9.6,120:-5.3,130:-0.9,140:3.4
ATGSeedDiag: seed=1@5,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(16.0) imip=39/58 pass=10100 acc=-1 ipm=144.4,64.0 inv=129.6,35.0 | 5(31.3) imip=0/15 pass=10111 acc=-1 ipm=111.3,107.8 inv=128.5,81.5
frame=921 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=158/55 sel=59/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.2/32.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,97) md=34/1/86 cxcy=84.0,119.6 guide=-24.39 atg=60.0/60.0/60.0 pure=-10.21/-10.18 yaw=1707 cmd=1507 actual=2192 signed=0 rps=2935/7065:6010/7753 duty=2/18 pwm=PWM2:2/PWM1:18 motor=2:2/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.30@100,99 dx=16.1 idx=6/24 dist=33/99 right=1:-28.01@119,77 dx=35.0 idx=0/13 dist=34/40 sel=1:-25.11@106,97 dx=21.6 idx=0/16 dist=32/78 edge=1:-23.99@107.5,90.0 dx=23.5 width=55.5 l=82,79 r=133,101
CxScan: raw_ref=80.0 edge=107.5,90.0 best_raw_x=140 best_err=-0.55 best_cxcy=107.0,119.7 scan=0:-45.9,10:-43.8,20:-41.5,30:-39.0,40:-36.4,50:-33.6,60:-30.6,70:-27.4,80:-24.0,90:-20.4,100:-16.7,110:-12.8,120:-8.8,130:-4.7,140:-0.5
ATGSeedDiag: seed=1@5,107/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.2) imip=0/20 pass=10110 acc=-1 ipm=62.9,95.2 inv=45.5,61.3 | 5(32.0) imip=0/15 pass=10111 acc=-1 ipm=111.0,107.8 inv=128.1,81.6
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=160/55 sel=59/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.5/30.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(104,97) md=32/1/83 cxcy=84.0,119.6 guide=-24.67 atg=60.0/60.0/60.0 pure=-10.21/-10.22 yaw=1727 cmd=1527 actual=2200 signed=0 rps=2907/7093:6194/8042 duty=2/18 pwm=PWM2:2/PWM1:18 motor=2:2/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.34@99,99 dx=15.3 idx=7/24 dist=32/97 right=1:-27.90@119,77 dx=34.7 idx=0/13 dist=34/40 sel=1:-25.46@106,97 dx=22.0 idx=0/16 dist=32/76 edge=1:-20.56@102.5,93.5 dx=18.5 width=62.8 l=72,86 r=133,101
CxScan: raw_ref=80.0 edge=102.5,93.5 best_raw_x=130 best_err=0.78 best_cxcy=103.2,119.7 scan=0:-45.1,10:-42.8,20:-40.2,30:-37.5,40:-34.5,50:-31.4,60:-28.0,70:-24.4,80:-20.6,90:-16.5,100:-12.4,110:-8.1,120:-3.7,130:0.8,140:5.2
ATGSeedDiag: seed=1@4,108/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(14.5) imip=0/15 pass=10110 acc=-1 ipm=55.8,105.0 inv=27.2,76.8 | 5(30.5) imip=0/15 pass=10111 acc=-1 ipm=110.8,108.0 inv=127.8,82.0
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=158/55 sel=59/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.6/31.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(102,98) md=32/1/86 cxcy=84.0,119.6 guide=-23.32 atg=60.0/60.0/60.0 pure=-10.20/-10.32 yaw=1633 cmd=1433 actual=2203 signed=0 rps=3036/6964:5986/7982 duty=3/17 pwm=PWM2:3/PWM1:17 motor=2:3/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.54@100,99 dx=15.5 idx=6/24 dist=33/97 right=1:-27.97@119,77 dx=34.7 idx=0/13 dist=34/40 sel=1:-24.02@105,97 dx=20.5 idx=0/16 dist=32/78 edge=1:-23.99@107.5,90.0 dx=23.5 width=55.5 l=82,79 r=133,101
CxScan: raw_ref=80.0 edge=107.5,90.0 best_raw_x=140 best_err=-0.55 best_cxcy=107.0,119.7 scan=0:-45.9,10:-43.8,20:-41.5,30:-39.0,40:-36.4,50:-33.6,60:-30.6,70:-27.4,80:-24.0,90:-20.4,100:-16.7,110:-12.8,120:-8.8,130:-4.7,140:-0.5
ATGSeedDiag: seed=1@4,106/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(15.6) imip=44/58 pass=10100 acc=-1 ipm=155.6,68.2 inv=143.4,37.3 | 5(31.1) imip=0/15 pass=10111 acc=-1 ipm=110.7,107.9 inv=127.6,81.8
frame=924 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=158/55 sel=59/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.4/31.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(103,97) md=32/1/86 cxcy=84.0,119.6 guide=-23.62 atg=60.0/60.0/60.0 pure=-10.21/-10.25 yaw=1654 cmd=1454 actual=2206 signed=0 rps=3008/6992:6548/8965 duty=2/16 pwm=PWM2:2/PWM1:16 motor=2:2/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.47@99,99 dx=15.5 idx=7/24 dist=32/95 right=1:-28.06@119,77 dx=34.9 idx=0/13 dist=34/40 sel=1:-24.45@105,97 dx=21.0 idx=0/16 dist=32/78 edge=1:-25.12@109.0,89.5 dx=25.0 width=52.4 l=86,77 r=132,102
CxScan: raw_ref=80.0 edge=109.0,89.5 best_raw_x=140 best_err=-2.15 best_cxcy=107.0,119.7 scan=0:-46.4,10:-44.3,20:-42.1,30:-39.7,40:-37.2,50:-34.5,60:-31.5,70:-28.4,80:-25.1,90:-21.6,100:-18.0,110:-14.2,120:-10.3,130:-6.2,140:-2.1
ATGSeedDiag: seed=1@4,105/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.4) imip=0/20 pass=10110 acc=-1 ipm=62.2,94.7 inv=44.7,60.6 | 5(31.1) imip=0/15 pass=10111 acc=-1 ipm=110.5,108.1 inv=127.3,82.2
frame=925 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=158/55 sel=59/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.5/31.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(103,98) md=33/1/85 cxcy=84.0,119.6 guide=-21.92 atg=60.0/60.0/60.0 pure=-10.21/-10.26 yaw=1534 cmd=1334 actual=2225 signed=0 rps=3171/6829:5797/8135 duty=3/17 pwm=PWM2:3/PWM1:17 motor=2:3/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.31@99,99 dx=15.3 idx=7/24 dist=33/97 right=1:-28.11@119,77 dx=35.0 idx=0/13 dist=34/40 sel=1:-24.85@105,97 dx=21.3 idx=0/16 dist=32/76 edge=1:-25.12@109.0,89.5 dx=25.0 width=52.4 l=86,77 r=132,102
CxScan: raw_ref=80.0 edge=109.0,89.5 best_raw_x=140 best_err=-2.15 best_cxcy=107.0,119.7 scan=0:-46.4,10:-44.3,20:-42.1,30:-39.7,40:-37.2,50:-34.5,60:-31.5,70:-28.4,80:-25.1,90:-21.6,100:-18.0,110:-14.2,120:-10.3,130:-6.2,140:-2.1
ATGSeedDiag: seed=1@4,105/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.5) imip=0/20 pass=10110 acc=-1 ipm=62.3,94.8 inv=44.8,60.7 | 5(31.3) imip=0/15 pass=10111 acc=-1 ipm=110.4,108.1 inv=127.3,82.2
frame=926 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/16 raw=157/55 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.1/21.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(102,98) md=33/1/85 cxcy=84.0,119.6 guide=-21.47 atg=60.0/60.0/60.0 pure=-10.21/-10.25 yaw=1503 cmd=1303 actual=2235 signed=0 rps=3214/6786:5926/8413 duty=3/16 pwm=PWM2:3/PWM1:16 motor=2:3/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/16 centerNum=58/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.87@100,99 dx=15.7 idx=6/24 dist=33/96 right=1:-26.15@116,78 dx=31.7 idx=0/12 dist=32/41 sel=1:-24.46@105,97 dx=20.6 idx=0/16 dist=32/76 edge=1:-24.44@108.0,90.0 dx=24.0 width=53.7 l=84,78 r=132,102
CxScan: raw_ref=80.0 edge=108.0,90.0 best_raw_x=140 best_err=-1.09 best_cxcy=107.0,119.7 scan=0:-46.2,10:-44.1,20:-41.8,30:-39.4,40:-36.8,50:-34.0,60:-31.0,70:-27.8,80:-24.4,90:-20.9,100:-17.2,110:-13.3,120:-9.3,130:-5.2,140:-1.1
ATGSeedDiag: seed=1@4,104/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(15.1) imip=38/57 pass=10100 acc=-1 ipm=142.8,65.8 inv=129.3,36.0 | 1(21.0) imip=0/11 pass=10111 acc=-1 ipm=103.6,114.4 inv=122.1,98.6
frame=927 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/16 raw=157/55 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.0/30.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(103,98) md=32/1/84 cxcy=84.0,119.6 guide=-24.11 atg=60.0/60.0/60.0 pure=-10.21/-10.25 yaw=1688 cmd=1488 actual=2219 signed=0 rps=2961/7039:5540/7869 duty=3/18 pwm=PWM2:3/PWM1:18 motor=2:3/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/16 centerNum=58/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.78@100,99 dx=15.6 idx=7/24 dist=32/95 right=1:-28.01@119,78 dx=34.7 idx=0/13 dist=34/40 sel=1:-25.04@105,97 dx=21.3 idx=0/16 dist=32/76 edge=1:-25.12@109.0,89.5 dx=25.0 width=52.4 l=86,77 r=132,102
CxScan: raw_ref=80.0 edge=109.0,89.5 best_raw_x=140 best_err=-2.15 best_cxcy=107.0,119.7 scan=0:-46.4,10:-44.3,20:-42.1,30:-39.7,40:-37.2,50:-34.5,60:-31.5,70:-28.4,80:-25.1,90:-21.6,100:-18.0,110:-14.2,120:-10.3,130:-6.2,140:-2.1
ATGSeedDiag: seed=1@4,104/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(15.0) imip=38/57 pass=10100 acc=-1 ipm=142.7,65.8 inv=129.3,36.0 | 5(30.1) imip=0/15 pass=10111 acc=-1 ipm=110.1,108.2 inv=126.9,82.4
frame=928 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=59/16 raw=157/55 sel=59/41 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.8/30.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(102,98) md=34/1/90 cxcy=84.0,119.6 guide=-20.53 atg=60.0/60.0/60.0 pure=-10.20/-10.21 yaw=1437 cmd=1237 actual=2226 signed=0 rps=3305/6695:5517/7764 duty=4/17 pwm=PWM2:4/PWM1:17 motor=2:4/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=59/16 centerNum=59/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/41 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.56@97,101 dx=12.6 idx=6/22 dist=33/102 right=1:-28.27@119,78 dx=35.0 idx=0/13 dist=34/40 sel=1:-23.47@104,97 dx=19.7 idx=0/16 dist=32/80 edge=1:-23.01@106.0,91.0 dx=22.0 width=56.5 l=80,80 r=132,102
CxScan: raw_ref=80.0 edge=106.0,91.0 best_raw_x=135 best_err=-1.01 best_cxcy=105.1,119.7 scan=0:-45.7,10:-43.5,20:-41.1,30:-38.6,40:-35.9,50:-32.9,60:-29.8,70:-26.5,80:-23.0,90:-19.3,100:-15.4,110:-11.4,120:-7.3,130:-3.1,140:1.1
ATGSeedDiag: seed=1@4,102/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.8) imip=0/20 pass=10110 acc=-1 ipm=62.3,94.4 inv=44.9,60.2 | 5(30.8) imip=0/15 pass=10111 acc=-1 ipm=110.1,108.2 inv=126.9,82.4

- stopped_at: 2026-06-22T15:26:22+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive152
```
