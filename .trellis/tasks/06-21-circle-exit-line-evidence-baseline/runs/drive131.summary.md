# drive131

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive131-front_car_circle_drive131.log
- remote_log: /tmp/front_car_circle_drive131.log
- started_at: 2026-06-22T15:01:39+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive131 6
```

4339 /tmp/front_car_circle_drive131.log
ATGSeedDiag: seed=1@4,101/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.3) imip=0/20 pass=10110 acc=-1 ipm=64.0,95.2 inv=47.1,61.2 | 8(14.2) imip=0/9 pass=10111 acc=-1 ipm=122.2,108.9 inv=150.9,83.7
frame=931 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=55/9 raw=154/33 sel=55/36 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.5/12.8/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(107,101) md=33/1/78 cxcy=84.0,119.6 guide=-29.08 atg=60.0/60.0/60.0 pure=-11.05/-10.88 yaw=1745 cmd=1780 actual=1710 signed=0 rps=379/5259:4488/6461 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=55/9 centerNum=55/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=55/36 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.14@103,102 dx=18.9 idx=8/25 dist=33/90 right=1:-26.40@113,85 dx=28.6 idx=0/8 dist=16/16 sel=1:-30.78@109,100 dx=25.2 idx=0/16 dist=32/70 edge=1:-25.71@107.5,94.0 dx=23.5 width=43.1 l=92,79 r=123,109
CxScan: raw_ref=80.0 edge=107.5,94.0 best_raw_x=140 best_err=-0.59 best_cxcy=107.0,119.7 scan=0:-48.2,10:-46.0,20:-43.8,30:-41.3,40:-38.6,50:-35.7,60:-32.6,70:-29.3,80:-25.7,90:-21.9,100:-17.9,110:-13.8,120:-9.5,130:-5.1,140:-0.6
ATGSeedDiag: seed=1@4,101/1@130,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.5) imip=0/20 pass=10110 acc=-1 ipm=64.2,95.1 inv=47.4,61.1 | 7(12.8) imip=0/8 pass=10111 acc=-1 ipm=120.7,109.7 inv=149.5,85.6
frame=932 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=54/9 raw=154/32 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.0/14.2/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(111,100) md=34/1/74 cxcy=84.0,119.6 guide=-31.24 atg=60.0/60.0/60.0 pure=-11.28/-11.09 yaw=1874 cmd=2020 actual=1729 signed=0 rps=0/5425:4548/6542 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/9 centerNum=54/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.39@103,103 dx=19.0 idx=9/25 dist=33/88 right=1:-26.86@113,85 dx=29.1 idx=0/8 dist=16/16 sel=1:-32.27@111,100 dx=26.7 idx=0/16 dist=32/68 edge=1:-26.42@108.5,93.5 dx=24.5 width=42.4 l=94,78 r=123,109
CxScan: raw_ref=80.0 edge=108.5,93.5 best_raw_x=140 best_err=-1.74 best_cxcy=107.0,119.7 scan=0:-48.4,10:-46.3,20:-44.1,30:-41.6,40:-39.0,50:-36.2,60:-33.2,70:-29.9,80:-26.4,90:-22.7,100:-18.8,110:-14.7,120:-10.5,130:-6.2,140:-1.7
ATGSeedDiag: seed=1@4,100/1@130,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(15.0) imip=33/53 pass=10110 acc=-1 ipm=135.2,71.0 inv=125.6,39.0 | 7(14.2) imip=0/8 pass=10111 acc=-1 ipm=120.9,109.8 inv=150.2,85.9
frame=933 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=54/9 raw=154/31 sel=54/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.3/13.1/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(109,102) md=32/1/73 cxcy=84.0,119.6 guide=-32.25 atg=60.0/60.0/60.0 pure=-11.48/-11.36 yaw=1935 cmd=2135 actual=1723 signed=0 rps=0/5507:4363/6051 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/9 centerNum=54/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.60@103,103 dx=18.9 idx=9/25 dist=32/83 right=1:-27.66@114,85 dx=30.0 idx=0/8 dist=16/16 sel=1:-32.93@111,101 dx=27.1 idx=0/16 dist=32/66 edge=1:-26.89@108.5,94.5 dx=24.5 width=43.8 l=93,79 r=124,110
CxScan: raw_ref=80.0 edge=108.5,94.5 best_raw_x=140 best_err=-1.78 best_cxcy=107.0,119.7 scan=0:-49.0,10:-46.9,20:-44.7,30:-42.2,40:-39.6,50:-36.8,60:-33.7,70:-30.4,80:-26.9,90:-23.1,100:-19.2,110:-15.0,120:-10.7,130:-6.3,140:-1.8
ATGSeedDiag: seed=1@4,100/1@131,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(15.3) imip=0/19 pass=10110 acc=-1 ipm=62.7,96.9 inv=44.3,63.5 | 6(13.1) imip=0/8 pass=10111 acc=-1 ipm=119.1,110.7 inv=148.3,88.1
frame=934 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=54/9 raw=154/30 sel=54/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.3/14.0/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(109,102) md=32/1/73 cxcy=84.0,119.6 guide=-32.25 atg=60.0/60.0/60.0 pure=-11.47/-11.30 yaw=1935 cmd=2135 actual=1703 signed=0 rps=0/5507:4623/6245 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/9 centerNum=54/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.80@103,103 dx=19.1 idx=9/25 dist=33/85 right=1:-27.95@114,86 dx=30.4 idx=0/8 dist=16/16 sel=1:-32.94@111,101 dx=27.1 idx=0/16 dist=32/66 edge=1:-27.83@109.5,94.5 dx=25.5 width=42.4 l=95,79 r=124,110
CxScan: raw_ref=80.0 edge=109.5,94.5 best_raw_x=140 best_err=-2.96 best_cxcy=107.0,119.7 scan=0:-49.5,10:-47.5,20:-45.3,30:-42.9,40:-40.3,50:-37.5,60:-34.5,70:-31.3,80:-27.8,90:-24.1,100:-20.2,110:-16.1,120:-11.9,130:-7.5,140:-3.0
ATGSeedDiag: seed=1@4,100/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.3) imip=0/20 pass=10110 acc=-1 ipm=64.5,95.4 inv=47.8,61.5 | 7(14.0) imip=0/8 pass=10111 acc=-1 ipm=121.5,110.2 inv=152.2,86.9
frame=935 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=54/8 raw=154/29 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.1/10.8/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(109,102) md=32/1/75 cxcy=84.0,119.6 guide=-32.25 atg=60.0/60.0/60.0 pure=-11.31/-11.14 yaw=1935 cmd=2135 actual=1699 signed=0 rps=0/5507:4799/6464 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/8 centerNum=54/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.98@103,103 dx=19.3 idx=9/25 dist=32/88 right=1:-26.18@112,86 dx=27.8 idx=0/7 dist=14/14 sel=1:-33.01@111,101 dx=27.2 idx=0/16 dist=32/68 edge=1:-26.89@108.5,94.5 dx=24.5 width=41.1 l=95,79 r=122,110
CxScan: raw_ref=80.0 edge=108.5,94.5 best_raw_x=140 best_err=-1.78 best_cxcy=107.0,119.7 scan=0:-49.0,10:-46.9,20:-44.7,30:-42.2,40:-39.6,50:-36.8,60:-33.7,70:-30.4,80:-26.9,90:-23.1,100:-19.2,110:-15.0,120:-10.7,130:-6.3,140:-1.8
ATGSeedDiag: seed=1@4,100/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.1) imip=0/20 pass=10110 acc=-1 ipm=64.6,95.4 inv=47.8,61.5 | 5(10.8) imip=0/7 pass=10111 acc=-1 ipm=117.5,111.5 inv=146.6,90.1
frame=936 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=54/8 raw=153/28 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.8/12.6/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(109,102) md=32/1/75 cxcy=84.0,119.6 guide=-32.48 atg=60.0/60.0/60.0 pure=-11.26/-11.14 yaw=1949 cmd=2149 actual=1714 signed=0 rps=0/5509:4732/6433 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/8 centerNum=54/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-28.30@106,103 dx=21.5 idx=9/26 dist=33/85 right=1:-26.57@112,86 dx=28.3 idx=0/7 dist=14/14 sel=1:-33.39@111,101 dx=27.5 idx=0/16 dist=32/68 edge=1:-26.89@108.5,94.5 dx=24.5 width=41.1 l=95,79 r=122,110
CxScan: raw_ref=80.0 edge=108.5,94.5 best_raw_x=140 best_err=-1.78 best_cxcy=107.0,119.7 scan=0:-49.0,10:-46.9,20:-44.7,30:-42.2,40:-39.6,50:-36.8,60:-33.7,70:-30.4,80:-26.9,90:-23.1,100:-19.2,110:-15.0,120:-10.7,130:-6.3,140:-1.8
ATGSeedDiag: seed=1@4,101/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.8) imip=0/20 pass=10110 acc=-1 ipm=64.8,95.5 inv=48.1,61.6 | 2(12.6) imip=0/7 pass=10111 acc=-1 ipm=111.4,114.1 inv=138.8,97.5
frame=937 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=54/8 raw=154/27 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.0/13.2/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(112,101) md=34/1/74 cxcy=84.0,119.6 guide=-32.85 atg=60.0/60.0/60.0 pure=-11.42/-11.24 yaw=1971 cmd=2171 actual=1737 signed=0 rps=0/5512:5052/6863 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/8 centerNum=54/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.70@104,104 dx=19.6 idx=9/25 dist=32/85 right=1:-27.04@113,86 dx=28.8 idx=0/7 dist=14/14 sel=1:-33.75@112,101 dx=27.7 idx=0/16 dist=32/68 edge=1:-27.36@109.0,94.5 dx=25.0 width=41.8 l=95,79 r=123,110
CxScan: raw_ref=80.0 edge=109.0,94.5 best_raw_x=140 best_err=-2.37 best_cxcy=107.0,119.7 scan=0:-49.2,10:-47.2,20:-45.0,30:-42.6,40:-40.0,50:-37.1,60:-34.1,70:-30.9,80:-27.4,90:-23.6,100:-19.7,110:-15.6,120:-11.3,130:-6.9,140:-2.4
ATGSeedDiag: seed=1@4,101/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.0) imip=0/20 pass=10110 acc=-1 ipm=64.9,95.8 inv=48.1,61.9 | 1(13.2) imip=0/7 pass=10111 acc=-1 ipm=109.7,115.2 inv=137.2,101.1
frame=938 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=53/7 raw=154/25 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.0/11.9/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(110,102) md=32/1/72 cxcy=84.0,119.6 guide=-33.34 atg=60.0/60.0/60.0 pure=-11.48/-11.27 yaw=2000 cmd=2200 actual=1759 signed=0 rps=0/5515:4870/6581 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/7 centerNum=53/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.98@104,104 dx=19.8 idx=9/25 dist=32/86 right=1:-25.98@111,87 dx=27.3 idx=0/6 dist=12/12 sel=1:-33.93@112,102 dx=27.7 idx=0/16 dist=32/66 edge=1:-25.93@107.0,95.5 dx=23.0 width=41.8 l=93,80 r=121,111
CxScan: raw_ref=80.0 edge=107.0,95.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-48.8,10:-46.7,20:-44.3,30:-41.8,40:-39.1,50:-36.2,60:-33.0,70:-29.6,80:-25.9,90:-22.0,100:-17.9,110:-13.6,120:-9.2,130:-4.6,140:-0.0
ATGSeedDiag: seed=1@4,101/1@135,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.0) imip=0/20 pass=10110 acc=-1 ipm=65.0,95.9 inv=48.2,62.1 | 1(11.9) imip=0/6 pass=10111 acc=-1 ipm=110.3,115.0 inv=138.2,100.3
frame=939 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=53/8 raw=153/26 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.6/12.0/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(109,102) md=32/1/73 cxcy=84.0,119.6 guide=-33.17 atg=60.0/60.0/60.0 pure=-11.47/-11.32 yaw=1990 cmd=2190 actual=1791 signed=0 rps=0/5513:5072/6879 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/8 centerNum=53/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-27.12@104,104 dx=19.9 idx=9/25 dist=33/85 right=1:-27.73@114,86 dx=29.6 idx=0/7 dist=14/14 sel=1:-34.04@112,102 dx=27.7 idx=0/16 dist=32/66 edge=1:-27.61@109.0,95.0 dx=25.0 width=42.5 l=95,79 r=123,111
CxScan: raw_ref=80.0 edge=109.0,95.0 best_raw_x=140 best_err=-2.40 best_cxcy=107.0,119.7 scan=0:-49.5,10:-47.5,20:-45.3,30:-42.9,40:-40.2,50:-37.4,60:-34.4,70:-31.1,80:-27.6,90:-23.9,100:-19.9,110:-15.7,120:-11.4,130:-6.9,140:-2.4
ATGSeedDiag: seed=1@4,101/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.6) imip=0/20 pass=10110 acc=-1 ipm=65.0,95.7 inv=48.3,61.8 | 3(12.0) imip=0/7 pass=10111 acc=-1 ipm=114.0,113.3 inv=143.0,95.1
frame=940 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=53/7 raw=154/25 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.5/12.0/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(109,102) md=32/1/73 cxcy=84.0,119.6 guide=-33.17 atg=60.0/60.0/60.0 pure=-11.53/-11.36 yaw=1990 cmd=2155 actual=1826 signed=0 rps=0/5465:4814/6451 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/7 centerNum=53/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-27.15@104,104 dx=19.9 idx=9/25 dist=32/86 right=1:-26.00@111,87 dx=27.1 idx=0/6 dist=12/12 sel=1:-34.08@112,102 dx=27.7 idx=0/16 dist=32/66 edge=1:-26.66@108.0,95.0 dx=24.0 width=41.2 l=95,79 r=121,111
CxScan: raw_ref=80.0 edge=108.0,95.0 best_raw_x=140 best_err=-1.20 best_cxcy=107.0,119.7 scan=0:-49.0,10:-46.9,20:-44.7,30:-42.2,40:-39.5,50:-36.7,60:-33.6,70:-30.2,80:-26.7,90:-22.9,100:-18.8,110:-14.6,120:-10.2,130:-5.8,140:-1.2
ATGSeedDiag: seed=1@4,100/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.5) imip=0/20 pass=10110 acc=-1 ipm=64.9,95.7 inv=48.2,61.8 | 1(12.0) imip=0/6 pass=10111 acc=-1 ipm=110.1,115.3 inv=138.2,101.2
frame=941 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=53/7 raw=153/25 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.8/10.9/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(110,103) md=33/1/73 cxcy=84.0,119.6 guide=-33.56 atg=60.0/60.0/60.0 pure=-11.65/-11.46 yaw=2013 cmd=2172 actual=1854 signed=0 rps=0/5461:5018/6512 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/7 centerNum=53/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-27.37@104,104 dx=20.0 idx=9/25 dist=32/85 right=1:-26.34@112,87 dx=27.5 idx=0/6 dist=12/12 sel=1:-34.47@112,102 dx=27.9 idx=0/16 dist=32/66 edge=1:-27.14@108.5,95.0 dx=24.5 width=40.6 l=96,79 r=121,111
CxScan: raw_ref=80.0 edge=108.5,95.0 best_raw_x=140 best_err=-1.80 best_cxcy=107.0,119.7 scan=0:-49.3,10:-47.2,20:-45.0,30:-42.5,40:-39.9,50:-37.0,60:-34.0,70:-30.7,80:-27.1,90:-23.4,100:-19.4,110:-15.2,120:-10.8,130:-6.3,140:-1.8
ATGSeedDiag: seed=1@4,101/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=51(17.8) imip=41/52 pass=10100 acc=-1 ipm=154.8,77.7 inv=151.9,43.4 | 2(10.9) imip=0/6 pass=10111 acc=-1 ipm=112.3,114.3 inv=141.1,98.1
frame=942 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=53/7 raw=154/24 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.1/9.4/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(111,103) md=33/1/71 cxcy=84.0,119.6 guide=-34.53 atg=60.0/60.0/60.0 pure=-11.63/-11.50 yaw=2072 cmd=2272 actual=1869 signed=0 rps=0/5524:4671/5994 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/7 centerNum=53/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.07@106,104 dx=21.6 idx=9/26 dist=33/82 right=1:-26.60@112,87 dx=27.8 idx=0/6 dist=12/12 sel=1:-35.52@113,102 dx=28.9 idx=0/16 dist=32/64 edge=1:-29.00@110.5,95.0 dx=26.5 width=40.0 l=100,78 r=121,112
CxScan: raw_ref=80.0 edge=110.5,95.0 best_raw_x=140 best_err=-4.18 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.3,20:-46.1,30:-43.8,40:-41.3,50:-38.5,60:-35.6,70:-32.4,80:-29.0,90:-25.4,100:-21.5,110:-17.4,120:-13.1,130:-8.7,140:-4.2
ATGSeedDiag: seed=1@4,101/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(15.1) imip=35/52 pass=10100 acc=-1 ipm=141.4,74.4 inv=134.5,41.1 | 2(9.4) imip=0/6 pass=10111 acc=-1 ipm=112.4,114.4 inv=141.6,98.4
frame=943 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=53/7 raw=154/24 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.7/10.0/0.0/0.0 dist=0 begin=0/2086 m0=(84,119) ml=(111,103) md=32/1/73 cxcy=84.0,119.6 guide=-34.86 atg=60.0/60.0/60.0 pure=-11.62/-11.39 yaw=2091 cmd=2291 actual=1873 signed=0 rps=0/5526:4655/6201 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/7 centerNum=53/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.37@106,104 dx=21.9 idx=9/26 dist=33/84 right=1:-26.60@112,87 dx=27.8 idx=0/6 dist=12/12 sel=1:-35.55@113,102 dx=29.0 idx=0/16 dist=32/66 edge=1:-29.00@110.5,95.0 dx=26.5 width=40.0 l=100,78 r=121,112
CxScan: raw_ref=80.0 edge=110.5,95.0 best_raw_x=140 best_err=-4.18 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.3,20:-46.1,30:-43.8,40:-41.3,50:-38.5,60:-35.6,70:-32.4,80:-29.0,90:-25.4,100:-21.5,110:-17.4,120:-13.1,130:-8.7,140:-4.2
ATGSeedDiag: seed=1@4,101/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(13.7) imip=0/11 pass=10110 acc=-1 ipm=52.0,112.0 inv=11.0,93.0 | 5(10.0) imip=0/6 pass=10111 acc=-1 ipm=118.9,112.2 inv=150.9,91.9

- stopped_at: 2026-06-22T15:01:52+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive131
```
