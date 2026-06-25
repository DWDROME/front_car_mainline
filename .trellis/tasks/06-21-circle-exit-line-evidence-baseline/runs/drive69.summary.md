# drive69

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive69-front_car_circle_drive69.log
- remote_log: /tmp/front_car_circle_drive69.log
- started_at: 2026-06-22T04:39:56+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive69 6
```

4395 /tmp/front_car_circle_drive69.log
ATGSeedDiag: seed=1@4,87/1@109,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(16.8) imip=0/20 pass=10110 acc=-1 ipm=56.4,88.2 inv=40.1,53.3 | 10(27.0) imip=0/20 pass=10111 acc=-1 ipm=111.4,99.9 inv=119.7,67.3
frame=877 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=64/21 raw=154/76 sel=64/48 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.6/38.4/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(89,96) md=33/1/106 cxcy=84.0,119.6 guide=-6.06 atg=60.0/60.0/60.0 pure=-8.05/-9.37 yaw=364 cmd=564 actual=-586 signed=0 rps=4228/5772:6561/6573 duty=7/14 pwm=PWM2:7/PWM1:14 motor=2:7/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/21 centerNum=64/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/48 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-3.21@87,97 dx=2.6 idx=5/18 dist=32/115 right=1:-16.71@104,76 dx=20.1 idx=0/11 dist=33/60 sel=1:-7.80@91,95 dx=6.6 idx=0/16 dist=32/94 edge=1:-12.83@96.5,88.0 dx=12.5 width=61.7 l=67,79 r=126,97
CxScan: raw_ref=80.0 edge=96.5,88.0 best_raw_x=115 best_err=0.97 best_cxcy=97.4,119.7 scan=0:-38.4,10:-35.8,20:-33.0,30:-30.1,40:-27.0,50:-23.7,60:-20.2,70:-16.6,80:-12.8,90:-9.0,100:-5.0,110:-1.0,120:3.0,130:6.9,140:10.8
ATGSeedDiag: seed=1@4,88/1@109,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(17.6) imip=44/63 pass=10100 acc=-1 ipm=150.4,57.9 inv=130.9,32.1 | 10(38.4) imip=0/20 pass=10111 acc=-1 ipm=112.4,100.6 inv=121.9,68.3
frame=878 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=62/20 raw=154/72 sel=62/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.5/36.6/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(90,97) md=32/1/99 cxcy=84.0,119.6 guide=-7.42 atg=60.0/60.0/60.0 pure=-8.76/-9.82 yaw=445 cmd=645 actual=-477 signed=0 rps=4116/5884:6561/6705 duty=6/15 pwm=PWM2:6/PWM1:15 motor=2:6/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=62/20 centerNum=62/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-4.07@87,99 dx=3.1 idx=5/18 dist=32/111 right=1:-17.84@105,76 dx=21.3 idx=0/11 dist=32/56 sel=1:-9.97@92,95 dx=8.3 idx=0/16 dist=32/90 edge=1:-14.20@97.5,89.5 dx=13.5 width=62.0 l=68,80 r=127,99
CxScan: raw_ref=80.0 edge=97.5,89.5 best_raw_x=115 best_err=-0.07 best_cxcy=97.4,119.7 scan=0:-39.8,10:-37.3,20:-34.5,30:-31.6,40:-28.5,50:-25.2,60:-21.7,70:-18.0,80:-14.2,90:-10.3,100:-6.2,110:-2.1,120:2.0,130:6.1,140:10.1
ATGSeedDiag: seed=1@4,88/1@110,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.5) imip=0/20 pass=10110 acc=-1 ipm=58.1,89.3 inv=41.8,54.3 | 9(36.6) imip=0/19 pass=10111 acc=-1 ipm=111.2,102.2 inv=121.7,70.9
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=61/19 raw=153/68 sel=61/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.7/34.5/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(91,97) md=34/1/99 cxcy=84.0,119.6 guide=-7.65 atg=60.0/60.0/60.0 pure=-9.01/-10.02 yaw=459 cmd=659 actual=-408 signed=0 rps=4097/5903:6729/6755 duty=6/15 pwm=PWM2:6/PWM1:15 motor=2:6/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=61/19 centerNum=61/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=61/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-7.02@89,98 dx=5.5 idx=5/19 dist=32/109 right=1:-21.38@110,76 dx=26.1 idx=0/12 dist=34/52 sel=1:-10.97@93,96 dx=9.0 idx=0/16 dist=32/88 edge=1:-17.04@100.5,89.0 dx=16.5 width=59.2 l=73,78 r=128,100
CxScan: raw_ref=80.0 edge=100.5,89.0 best_raw_x=125 best_err=0.81 best_cxcy=101.3,119.7 scan=0:-41.4,10:-39.0,20:-36.4,30:-33.6,40:-30.7,50:-27.5,60:-24.2,70:-20.7,80:-17.0,90:-13.2,100:-9.3,110:-5.3,120:-1.2,130:2.8,140:6.9
ATGSeedDiag: seed=1@4,89/1@110,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(16.7) imip=40/60 pass=10100 acc=-1 ipm=143.9,62.1 inv=127.8,34.1 | 8(34.5) imip=0/18 pass=10111 acc=-1 ipm=110.4,103.6 inv=121.8,73.4
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=61/18 raw=154/63 sel=61/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.5/32.1/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(91,98) md=32/1/96 cxcy=84.0,119.6 guide=-10.01 atg=60.0/60.0/60.0 pure=-9.07/-9.88 yaw=601 cmd=801 actual=-353 signed=0 rps=3903/6097:6321/6063 duty=6/16 pwm=PWM2:6/PWM1:16 motor=2:6/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=61/18 centerNum=61/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=61/44 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-8.96@91,98 dx=7.1 idx=6/20 dist=33/108 right=1:-23.19@113,76 dx=28.5 idx=0/12 dist=33/48 sel=1:-13.16@95,96 dx=10.9 idx=0/16 dist=32/86 edge=1:-16.50@99.5,90.5 dx=15.5 width=63.9 l=69,81 r=130,100
CxScan: raw_ref=80.0 edge=99.5,90.5 best_raw_x=120 best_err=-0.17 best_cxcy=99.3,119.7 scan=0:-41.6,10:-39.1,20:-36.5,30:-33.6,40:-30.6,50:-27.4,60:-23.9,70:-20.3,80:-16.5,90:-12.6,100:-8.5,110:-4.4,120:-0.2,130:4.0,140:8.1
ATGSeedDiag: seed=1@4,89/1@111,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(16.5) imip=0/20 pass=10110 acc=-1 ipm=59.0,90.0 inv=42.6,55.0 | 7(32.1) imip=0/17 pass=10111 acc=-1 ipm=110.0,104.5 inv=122.2,75.0
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=62/18 raw=154/64 sel=62/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=19.6/31.1/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(91,98) md=33/1/101 cxcy=84.0,119.6 guide=-7.92 atg=60.0/60.0/60.0 pure=-8.90/-9.67 yaw=475 cmd=675 actual=-305 signed=0 rps=4075/5925:6808/6327 duty=6/15 pwm=PWM2:6/PWM1:15 motor=2:6/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=62/18 centerNum=62/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-5.50@88,99 dx=4.2 idx=5/18 dist=32/114 right=1:-22.79@112,77 dx=27.5 idx=0/12 dist=33/48 sel=1:-11.40@93,97 dx=9.3 idx=0/16 dist=32/90 edge=1:-16.65@99.5,91.0 dx=15.5 width=64.2 l=69,81 r=130,101
CxScan: raw_ref=80.0 edge=99.5,91.0 best_raw_x=120 best_err=-0.17 best_cxcy=99.3,119.7 scan=0:-41.9,10:-39.4,20:-36.7,30:-33.9,40:-30.8,50:-27.6,60:-24.1,70:-20.5,80:-16.6,90:-12.7,100:-8.6,110:-4.4,120:-0.2,130:4.0,140:8.2
ATGSeedDiag: seed=1@4,90/1@113,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=51(19.6) imip=41/61 pass=10100 acc=-1 ipm=145.8,60.1 inv=128.2,33.1 | 7(31.1) imip=0/17 pass=10111 acc=-1 ipm=110.0,105.5 inv=123.2,76.9
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=63/18 raw=154/61 sel=63/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.4/29.2/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(93,97) md=32/1/100 cxcy=84.0,119.6 guide=-11.07 atg=60.0/60.0/60.0 pure=-8.79/-9.47 yaw=664 cmd=864 actual=-250 signed=0 rps=3816/6184:6645/6243 duty=5/16 pwm=PWM2:5/PWM1:16 motor=2:5/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=63/18 centerNum=63/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-9.37@91,98 dx=7.4 idx=6/20 dist=33/113 right=1:-23.93@113,78 dx=28.9 idx=0/12 dist=33/48 sel=1:-13.42@95,95 dx=11.3 idx=0/16 dist=32/90 edge=1:-20.21@104.0,88.5 dx=20.0 width=59.5 l=77,76 r=131,101
CxScan: raw_ref=80.0 edge=104.0,88.5 best_raw_x=130 best_err=-0.87 best_cxcy=103.2,119.7 scan=0:-43.2,10:-40.9,20:-38.5,30:-35.9,40:-33.1,50:-30.2,60:-27.0,70:-23.7,80:-20.2,90:-16.6,100:-12.8,110:-8.9,120:-4.9,130:-0.9,140:3.1
ATGSeedDiag: seed=1@4,91/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=60(18.4) imip=50/62 pass=10100 acc=-1 ipm=165.9,64.9 inv=150.0,35.4 | 7(29.2) imip=0/17 pass=10111 acc=-1 ipm=110.9,105.9 inv=125.4,77.7
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=63/17 raw=154/58 sel=63/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.9/26.7/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(94,97) md=33/1/100 cxcy=84.0,119.6 guide=-11.16 atg=60.0/60.0/60.0 pure=-8.87/-9.45 yaw=669 cmd=869 actual=-166 signed=0 rps=3808/6192:6970/6844 duty=5/16 pwm=PWM2:5/PWM1:16 motor=2:5/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=63/17 centerNum=63/17 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-9.95@92,98 dx=7.9 idx=6/20 dist=33/112 right=1:-24.66@114,78 dx=29.6 idx=0/12 dist=32/44 sel=1:-14.44@96,95 dx=12.2 idx=0/16 dist=32/90 edge=1:-18.32@101.0,91.5 dx=17.0 width=65.5 l=70,81 r=132,102
CxScan: raw_ref=80.0 edge=101.0,91.5 best_raw_x=125 best_err=0.29 best_cxcy=101.3,119.7 scan=0:-43.1,10:-40.7,20:-38.1,30:-35.3,40:-32.3,50:-29.1,60:-25.7,70:-22.1,80:-18.3,90:-14.4,100:-10.3,110:-6.1,120:-1.8,130:2.4,140:6.6
ATGSeedDiag: seed=1@4,91/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(17.9) imip=44/62 pass=10100 acc=-1 ipm=153.0,60.1 inv=134.5,33.0 | 6(26.7) imip=0/16 pass=10111 acc=-1 ipm=109.7,107.4 inv=125.2,80.8
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=62/15 raw=153/53 sel=62/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.2/24.9/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(95,97) md=33/1/98 cxcy=84.0,119.6 guide=-12.65 atg=60.0/60.0/60.0 pure=-9.22/-9.67 yaw=759 cmd=959 actual=-69 signed=0 rps=3685/6315:6949/7115 duty=4/16 pwm=PWM2:4/PWM1:16 motor=2:4/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=62/15 centerNum=62/15 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=62/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.85@93,99 dx=8.5 idx=6/20 dist=33/109 right=1:-28.23@119,78 dx=34.6 idx=0/13 dist=33/36 sel=1:-16.00@97,96 dx=13.5 idx=0/16 dist=32/88 edge=1:-18.66@101.5,91.0 dx=17.5 width=60.0 l=74,79 r=129,103
CxScan: raw_ref=80.0 edge=101.5,91.0 best_raw_x=125 best_err=-0.27 best_cxcy=101.3,119.7 scan=0:-43.1,10:-40.7,20:-38.1,30:-35.4,40:-32.4,50:-29.3,60:-25.9,70:-22.4,80:-18.7,90:-14.8,100:-10.7,110:-6.6,120:-2.4,130:1.8,140:6.0
ATGSeedDiag: seed=1@4,92/1@117,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(17.2) imip=44/61 pass=10100 acc=-1 ipm=153.3,62.1 inv=136.3,34.0 | 4(24.9) imip=0/14 pass=10111 acc=-1 ipm=107.3,109.7 inv=123.4,85.9
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=60/15 raw=154/52 sel=60/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.3/25.2/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(98,97) md=33/1/93 cxcy=84.0,119.6 guide=-17.01 atg=60.0/60.0/60.0 pure=-9.74/-9.97 yaw=1021 cmd=1221 actual=-6 signed=0 rps=3327/6673:6499/6799 duty=4/18 pwm=PWM2:4/PWM1:18 motor=2:4/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=60/15 centerNum=60/15 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=60/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.68@94,99 dx=9.8 idx=7/21 dist=32/104 right=1:-29.15@119,79 dx=35.4 idx=0/13 dist=33/36 sel=1:-19.06@100,96 dx=16.0 idx=0/16 dist=32/84 edge=1:-23.59@107.5,89.0 dx=23.5 width=54.1 l=85,74 r=130,104
CxScan: raw_ref=80.0 edge=107.5,89.0 best_raw_x=140 best_err=-0.54 best_cxcy=107.0,119.7 scan=0:-45.4,10:-43.2,20:-41.0,30:-38.5,40:-35.9,50:-33.1,60:-30.1,70:-26.9,80:-23.6,90:-20.1,100:-16.4,110:-12.5,120:-8.6,130:-4.6,140:-0.5
ATGSeedDiag: seed=1@4,92/1@118,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(17.3) imip=42/59 pass=10100 acc=-1 ipm=150.7,64.1 inv=135.4,35.0 | 4(25.2) imip=0/14 pass=10111 acc=-1 ipm=107.4,110.4 inv=124.7,87.6
frame=886 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/14 raw=154/50 sel=58/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.6/22.6/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(99,99) md=32/1/86 cxcy=84.0,119.6 guide=-19.88 atg=60.0/60.0/60.0 pure=-10.16/-10.44 yaw=1193 cmd=1393 actual=47 signed=0 rps=3091/6909:6193/6736 duty=3/19 pwm=PWM2:3/PWM1:19 motor=2:3/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/14 centerNum=58/14 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-15.44@96,100 dx=11.8 idx=7/22 dist=33/100 right=1:-30.25@120,80 dx=36.4 idx=0/13 dist=32/32 sel=1:-20.83@101,98 dx=17.1 idx=0/16 dist=32/78 edge=1:-24.19@107.5,90.5 dx=23.5 width=50.2 l=87,76 r=128,105
CxScan: raw_ref=80.0 edge=107.5,90.5 best_raw_x=140 best_err=-0.55 best_cxcy=107.0,119.7 scan=0:-46.2,10:-44.1,20:-41.8,30:-39.3,40:-36.7,50:-33.8,60:-30.8,70:-27.6,80:-24.2,90:-20.6,100:-16.8,110:-12.9,120:-8.9,130:-4.7,140:-0.6
ATGSeedDiag: seed=1@4,93/1@119,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(18.6) imip=37/57 pass=10100 acc=-1 ipm=140.5,65.8 inv=127.2,36.0 | 3(22.6) imip=0/13 pass=10111 acc=-1 ipm=106.3,112.0 inv=124.5,91.8
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=57/13 raw=154/47 sel=57/38 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.2/16.1/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(102,99) md=32/1/81 cxcy=84.0,119.6 guide=-23.51 atg=60.0/60.0/60.0 pure=-10.54/-10.80 yaw=1411 cmd=1611 actual=92 signed=0 rps=2793/7207:6194/6939 duty=2/20 pwm=PWM2:2/PWM1:20 motor=2:2/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=57/13 centerNum=57/13 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/38 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.88@98,101 dx=13.5 idx=8/23 dist=32/94 right=1:-29.54@119,81 dx=34.7 idx=0/12 dist=28/28 sel=1:-23.91@104,98 dx=20.1 idx=0/16 dist=32/74 edge=1:-24.14@107.0,91.5 dx=23.0 width=49.4 l=87,77 r=127,106
CxScan: raw_ref=80.0 edge=107.0,91.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-46.5,10:-44.3,20:-42.0,30:-39.5,40:-36.8,50:-34.0,60:-30.9,70:-27.6,80:-24.1,90:-20.5,100:-16.6,110:-12.6,120:-8.5,130:-4.3,140:-0.0
ATGSeedDiag: seed=1@4,94/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(14.2) imip=0/11 pass=10110 acc=-1 ipm=49.7,109.5 inv=10.4,86.6 | 1(16.1) imip=0/11 pass=10111 acc=-1 ipm=103.4,114.8 inv=122.4,100.0
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=56/12 raw=153/44 sel=56/38 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.5/21.7/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(103,99) md=32/1/81 cxcy=84.0,119.6 guide=-24.76 atg=60.0/60.0/60.0 pure=-10.83/-10.93 yaw=1486 cmd=1686 actual=129 signed=0 rps=2690/7310:6240/6918 duty=2/20 pwm=PWM2:2/PWM1:20 motor=2:2/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=56/12 centerNum=56/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=56/38 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.42@100,101 dx=15.6 idx=8/24 dist=33/93 right=1:-28.52@117,83 dx=32.7 idx=0/11 dist=24/24 sel=1:-25.42@105,98 dx=21.1 idx=0/16 dist=32/74 edge=1:-25.07@108.0,91.5 dx=24.0 width=47.5 l=90,76 r=126,107
CxScan: raw_ref=80.0 edge=108.0,91.5 best_raw_x=140 best_err=-1.12 best_cxcy=107.0,119.7 scan=0:-47.0,10:-44.9,20:-42.6,30:-40.2,40:-37.6,50:-34.7,60:-31.7,70:-28.5,80:-25.1,90:-21.4,100:-17.6,110:-13.7,120:-9.6,130:-5.4,140:-1.1
ATGSeedDiag: seed=1@4,94/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(15.5) imip=36/55 pass=10100 acc=-1 ipm=140.2,69.4 inv=129.3,38.0 | 10(21.7) imip=0/11 pass=10111 acc=-1 ipm=123.3,107.3 inv=149.9,80.2
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=56/11 raw=154/40 sel=56/38 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.3/16.8/0.0/0.0 dist=0 begin=0/2765 m0=(84,119) ml=(103,99) md=32/1/83 cxcy=84.0,119.6 guide=-25.03 atg=60.0/60.0/60.0 pure=-10.83/-10.90 yaw=1502 cmd=1702 actual=191 signed=0 rps=2668/7332:6036/6416 duty=2/21 pwm=PWM2:2/PWM1:21 motor=2:2/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=56/11 centerNum=56/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=56/38 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.29@98,102 dx=14.4 idx=8/23 dist=32/94 right=1:-27.71@115,84 dx=31.1 idx=0/10 dist=20/20 sel=1:-25.62@105,99 dx=21.2 idx=0/16 dist=32/74 edge=1:-25.04@107.5,92.5 dx=23.5 width=46.8 l=90,77 r=125,108
CxScan: raw_ref=80.0 edge=107.5,92.5 best_raw_x=140 best_err=-0.57 best_cxcy=107.0,119.7 scan=0:-47.3,10:-45.2,20:-42.9,30:-40.4,40:-37.8,50:-34.9,60:-31.8,70:-28.5,80:-25.0,90:-21.3,100:-17.4,110:-13.4,120:-9.2,130:-4.9,140:-0.6
ATGSeedDiag: seed=1@4,95/1@124,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(15.3) imip=37/55 pass=10100 acc=-1 ipm=142.4,69.5 inv=131.6,38.0 | 6(16.8) imip=0/10 pass=10111 acc=-1 ipm=115.6,109.6 inv=139.6,85.6

- stopped_at: 2026-06-22T04:40:09+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive69
```
