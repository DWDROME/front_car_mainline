# drive162

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 10
- local_log: logs/live-circle/20260621-drive162-front_car_circle_drive162.log
- remote_log: /tmp/front_car_circle_drive162.log
- started_at: 2026-06-22T15:38:12+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive162 10
```

7707 /tmp/front_car_circle_drive162.log
ATGSeedDiag: seed=1@13,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=37(32.9) imip=27/47 pass=10110 acc=-1 ipm=119.5,60.0 inv=105.2,33.2 | 8(17.2) imip=0/12 pass=10111 acc=-1 ipm=125.9,104.1 inv=148.9,73.9
frame=1409 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=170/13 raw=170/51 sel=170/144 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=32.4/26.2/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(116,94) md=40/1/145 cxcy=84.0,119.6 guide=-33.58 atg=60.0/60.0/60.0 pure=-8.09/-4.69 yaw=2686 cmd=2900 actual=2580 signed=0 rps=0/7183:5020/8862 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=170/13 centerNum=170/13 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/144 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-31.53@113,95 dx=29.5 idx=6/26 dist=41/334 right=1:-28.54@119,79 dx=34.9 idx=0/12 dist=29/29 sel=1:-34.69@120,91 dx=35.7 idx=0/20 dist=40/286 edge=1:-29.61@116.0,86.5 dx=32.0 width=45.0 l=98,73 r=134,100
CxScan: raw_ref=80.0 edge=116.0,86.5 best_raw_x=140 best_err=-9.07 best_cxcy=107.0,119.7 scan=0:-48.2,10:-46.4,20:-44.4,30:-42.4,40:-40.1,50:-37.7,60:-35.2,70:-32.5,80:-29.6,90:-26.6,100:-23.3,110:-20.0,120:-16.5,130:-12.8,140:-9.1
ATGSeedDiag: seed=1@14,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=35(32.4) imip=25/45 pass=10110 acc=-1 ipm=115.6,62.1 inv=102.6,34.2 | 10(26.2) imip=0/12 pass=10111 acc=-1 ipm=129.5,101.2 inv=150.0,69.0
frame=1410 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=170/14 raw=170/51 sel=170/151 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=33.6/21.1/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(115,93) md=40/1/146 cxcy=84.0,119.6 guide=-32.45 atg=60.0/60.0/60.0 pure=-7.94/-4.53 yaw=2596 cmd=2676 actual=2556 signed=0 rps=0/6937:4616/8154 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=170/14 centerNum=170/14 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/151 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-31.47@114,94 dx=29.9 idx=6/26 dist=42/348 right=1:-29.50@121,77 dx=37.4 idx=0/13 dist=32/32 sel=1:-34.18@119,91 dx=35.3 idx=0/20 dist=40/300 edge=1:-29.61@116.0,86.5 dx=32.0 width=47.2 l=96,74 r=136,99
CxScan: raw_ref=80.0 edge=116.0,86.5 best_raw_x=140 best_err=-9.07 best_cxcy=107.0,119.7 scan=0:-48.2,10:-46.4,20:-44.4,30:-42.4,40:-40.1,50:-37.7,60:-35.2,70:-32.5,80:-29.6,90:-26.6,100:-23.3,110:-20.0,120:-16.5,130:-12.8,140:-9.1
ATGSeedDiag: seed=1@15,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=35(33.6) imip=25/45 pass=10110 acc=-1 ipm=115.1,60.9 inv=101.7,33.6 | 9(21.1) imip=0/13 pass=10111 acc=-1 ipm=127.2,102.1 inv=147.9,70.6
frame=1412 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=170/147 raw=170/136 sel=170/152 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=33.5/31.0/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(115,93) md=40/1/144 cxcy=84.0,119.6 guide=-32.22 atg=60.0/60.0/60.0 pure=-7.58/-4.25 yaw=2577 cmd=2685 actual=2524 signed=0 rps=0/6961:4531/8405 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=170/147 centerNum=170/147 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/152 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-29.38@111,95 dx=26.9 idx=5/24 dist=40/348 right=1:-31.31@128,70 dx=44.0 idx=0/19 dist=41/396 sel=1:-33.49@119,90 dx=34.7 idx=0/20 dist=40/302 edge=1:-31.59@122.0,81.0 dx=38.0 width=53.9 l=96,74 r=148,88
CxScan: raw_ref=80.0 edge=122.0,81.0 best_raw_x=140 best_err=-13.62 best_cxcy=107.0,119.7 scan=0:-48.2,10:-46.5,20:-44.7,30:-42.9,40:-40.9,50:-38.7,60:-36.5,70:-34.1,80:-31.6,90:-28.9,100:-26.1,110:-23.2,120:-20.1,130:-16.9,140:-13.6
ATGSeedDiag: seed=1@17,108/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=33(33.5) imip=23/43 pass=10110 acc=-1 ipm=110.7,62.2 inv=98.2,34.3 | 45(31.0) imip=35/55 pass=10101 acc=-1 ipm=171.5,35.9 inv=133.9,24.0
frame=1414 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=170/147 raw=170/149 sel=170/144 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=33.3/30.2/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(114,92) md=40/1/145 cxcy=84.0,119.6 guide=-31.39 atg=60.0/60.0/60.0 pure=-7.19/-3.99 yaw=2512 cmd=2650 actual=2442 signed=0 rps=0/6958:4374/8081 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=170/147 centerNum=170/147 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/144 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-29.72@112,94 dx=28.0 idx=5/24 dist=41/334 right=1:-29.93@126,70 dx=41.7 idx=0/19 dist=41/382 sel=1:-32.75@118,90 dx=34.2 idx=0/20 dist=40/286 edge=1:-30.22@120.0,81.0 dx=36.0 width=53.4 l=94,75 r=146,87
CxScan: raw_ref=80.0 edge=120.0,81.0 best_raw_x=140 best_err=-11.86 best_cxcy=107.0,119.7 scan=0:-47.3,10:-45.6,20:-43.8,30:-41.8,40:-39.8,50:-37.6,60:-35.3,70:-32.8,80:-30.2,90:-27.5,100:-24.6,110:-21.6,120:-18.5,130:-15.2,140:-11.9
ATGSeedDiag: seed=1@18,108/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=31(33.3) imip=21/41 pass=10110 acc=-1 ipm=106.4,64.3 inv=94.9,35.4 | 44(30.2) imip=34/54 pass=10111 acc=-1 ipm=166.4,35.9 inv=130.3,24.0
frame=1415 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=170/156 raw=170/143 sel=170/149 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=34.3/30.5/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(114,92) md=40/1/145 cxcy=84.0,119.6 guide=-30.72 atg=60.0/60.0/60.0 pure=-6.96/-3.82 yaw=2458 cmd=2582 actual=2395 signed=0 rps=0/6901:4552/8496 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=170/156 centerNum=170/156 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/149 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-28.52@110,94 dx=26.4 idx=5/23 dist=40/335 right=1:-29.60@127,68 dx=42.5 idx=0/21 dist=41/400 sel=1:-32.09@118,89 dx=33.8 idx=0/20 dist=40/296 edge=1:-29.82@120.0,80.0 dx=36.0 width=53.4 l=94,74 r=146,86
CxScan: raw_ref=80.0 edge=120.0,80.0 best_raw_x=140 best_err=-11.68 best_cxcy=107.0,119.7 scan=0:-46.9,10:-45.1,20:-43.3,30:-41.4,40:-39.3,50:-37.2,60:-34.8,70:-32.4,80:-29.8,90:-27.1,100:-24.3,110:-21.3,120:-18.2,130:-15.0,140:-11.7
ATGSeedDiag: seed=1@19,108/1@144,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(34.3) imip=20/40 pass=10110 acc=-1 ipm=104.5,65.1 inv=93.4,35.8 | 43(30.5) imip=33/53 pass=10111 acc=-1 ipm=163.3,36.2 inv=128.4,24.1
frame=1416 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=158/161 raw=135/147 sel=158/149 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=34.5/32.1/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(115,90) md=42/1/145 cxcy=84.0,119.6 guide=-30.10 atg=60.0/60.0/60.0 pure=-6.82/-3.64 yaw=2408 cmd=2503 actual=2361 signed=0 rps=0/6825:4446/8317 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=158/161 centerNum=158/161 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=158/149 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-28.50@111,94 dx=26.7 idx=4/23 dist=40/342 right=1:-28.70@124,70 dx=39.7 idx=0/19 dist=40/414 sel=1:-31.21@117,89 dx=32.8 idx=0/20 dist=40/296 edge=1:-28.78@118.5,80.0 dx=34.5 width=53.9 l=92,75 r=145,85
CxScan: raw_ref=80.0 edge=118.5,80.0 best_raw_x=140 best_err=-10.36 best_cxcy=107.0,119.7 scan=0:-46.2,10:-44.4,20:-42.6,30:-40.6,40:-38.5,50:-36.3,60:-33.9,70:-31.4,80:-28.8,90:-26.0,100:-23.1,110:-20.1,120:-16.9,130:-13.7,140:-10.4
ATGSeedDiag: seed=1@19,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(34.5) imip=20/40 pass=10110 acc=-1 ipm=103.5,64.1 inv=92.2,35.3 | 44(32.1) imip=34/54 pass=10111 acc=-1 ipm=162.5,33.6 inv=126.6,23.4
frame=1417 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=153/170 raw=134/147 sel=153/146 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=34.9/31.7/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(113,91) md=40/1/144 cxcy=84.0,119.6 guide=-29.34 atg=60.0/60.0/60.0 pure=-6.61/-3.47 yaw=2347 cmd=2359 actual=2341 signed=0 rps=202/6669:4893/8370 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=153/170 centerNum=153/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=153/146 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-28.03@111,93 dx=26.6 idx=4/23 dist=41/330 right=1:-28.53@125,67 dx=41.2 idx=0/22 dist=41/435 sel=1:-30.57@116,88 dx=32.4 idx=0/20 dist=40/290 edge=1:-28.94@119.0,79.5 dx=35.0 width=53.2 l=93,74 r=145,85
CxScan: raw_ref=80.0 edge=119.0,79.5 best_raw_x=140 best_err=-10.72 best_cxcy=107.0,119.7 scan=0:-46.2,10:-44.5,20:-42.6,30:-40.6,40:-38.6,50:-36.3,60:-34.0,70:-31.5,80:-28.9,90:-26.2,100:-23.3,110:-20.3,120:-17.2,130:-14.0,140:-10.7
ATGSeedDiag: seed=1@19,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(34.9) imip=20/40 pass=10110 acc=-1 ipm=102.4,63.5 inv=91.1,35.0 | 44(31.7) imip=34/54 pass=10111 acc=-1 ipm=160.8,32.5 inv=124.9,23.1
frame=1418 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=150/170 raw=131/151 sel=150/144 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=34.8/34.5/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(113,91) md=40/1/144 cxcy=84.0,119.6 guide=-29.06 atg=60.0/60.0/60.0 pure=-6.36/-3.36 yaw=2325 cmd=2382 actual=2296 signed=0 rps=185/6715:5254/8106 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=150/170 centerNum=150/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=150/144 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-28.50@112,91 dx=27.8 idx=4/23 dist=42/328 right=1:-27.95@124,67 dx=40.3 idx=0/22 dist=41/437 sel=1:-30.15@116,87 dx=32.2 idx=0/20 dist=40/286 edge=1:-28.24@118.0,79.5 dx=34.0 width=52.8 l=92,75 r=144,84
CxScan: raw_ref=80.0 edge=118.0,79.5 best_raw_x=140 best_err=-9.84 best_cxcy=107.0,119.7 scan=0:-45.8,10:-44.0,20:-42.1,30:-40.1,40:-38.0,50:-35.8,60:-33.4,70:-30.9,80:-28.2,90:-25.5,100:-22.6,110:-19.5,120:-16.4,130:-13.2,140:-9.8
ATGSeedDiag: seed=1@20,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(34.8) imip=19/39 pass=10110 acc=-1 ipm=100.6,64.4 inv=89.6,35.5 | 44(34.5) imip=34/54 pass=10111 acc=-1 ipm=158.3,31.7 inv=122.9,22.8
frame=1419 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=144/170 raw=127/152 sel=144/139 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=35.1/32.0/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(112,90) md=40/1/146 cxcy=84.0,119.6 guide=-28.09 atg=60.0/60.0/60.0 pure=-6.15/-3.18 yaw=2247 cmd=2249 actual=2246 signed=0 rps=420/6584:5014/7593 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=144/170 centerNum=144/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=144/139 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-26.82@110,92 dx=25.5 idx=4/22 dist=40/317 right=1:-27.38@123,67 dx=39.4 idx=0/22 dist=41/439 sel=1:-29.44@116,87 dx=31.7 idx=0/20 dist=40/276 edge=1:-27.53@117.0,79.5 dx=33.0 width=52.8 l=91,75 r=143,84
CxScan: raw_ref=80.0 edge=117.0,79.5 best_raw_x=140 best_err=-8.96 best_cxcy=107.0,119.7 scan=0:-45.3,10:-43.5,20:-41.6,30:-39.6,40:-37.4,50:-35.2,60:-32.7,70:-30.2,80:-27.5,90:-24.7,100:-21.8,110:-18.7,120:-15.6,130:-12.3,140:-9.0
ATGSeedDiag: seed=1@20,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(35.1) imip=18/38 pass=10110 acc=-1 ipm=98.5,65.9 inv=88.0,36.3 | 44(32.0) imip=34/54 pass=10111 acc=-1 ipm=156.8,31.0 inv=121.6,22.7
frame=1420 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=143/170 raw=127/163 sel=143/138 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=36.0/33.9/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(112,89) md=40/1/147 cxcy=84.0,119.6 guide=-27.83 atg=60.0/53.0/60.0 pure=-5.90/-2.99 yaw=2226 cmd=2270 actual=2204 signed=0 rps=405/6627:5101/8191 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=143/170 centerNum=143/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=143/138 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-26.81@110,91 dx=26.0 idx=4/22 dist=41/313 right=1:-26.84@123,66 dx=38.9 idx=0/23 dist=41/429 sel=1:-28.73@115,86 dx=31.1 idx=0/20 dist=40/274 edge=1:-27.00@116.0,80.0 dx=32.0 width=54.6 l=89,76 r=143,84
CxScan: raw_ref=80.0 edge=116.0,80.0 best_raw_x=140 best_err=-8.14 best_cxcy=107.0,119.7 scan=0:-45.1,10:-43.3,20:-41.3,30:-39.3,40:-37.1,50:-34.8,60:-32.3,70:-29.7,80:-27.0,90:-24.1,100:-21.2,110:-18.1,120:-14.8,130:-11.5,140:-8.1
ATGSeedDiag: seed=1@21,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=27(36.0) imip=17/37 pass=10110 acc=-1 ipm=96.7,66.9 inv=86.4,36.9 | 45(33.9) imip=35/55 pass=10101 acc=-1 ipm=155.9,28.2 inv=119.9,21.9
frame=1421 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=141/170 raw=124/157 sel=141/137 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=36.0/33.9/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(112,89) md=41/1/150 cxcy=84.0,119.6 guide=-26.93 atg=60.0/49.0/60.0 pure=-5.69/-2.86 yaw=2154 cmd=2102 actual=2180 signed=0 rps=683/6444:5184/8516 duty=0/15 pwm=PWM2:0/PWM1:15 motor=2:0/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=141/170 centerNum=141/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=141/137 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-26.68@110,90 dx=26.5 idx=4/22 dist=40/308 right=1:-26.01@122,65 dx=38.1 idx=0/24 dist=41/427 sel=1:-28.03@115,85 dx=30.6 idx=0/20 dist=40/272 edge=1:-26.27@115.5,79.0 dx=31.5 width=53.6 l=89,75 r=142,83
CxScan: raw_ref=80.0 edge=115.5,79.0 best_raw_x=140 best_err=-7.58 best_cxcy=107.0,119.7 scan=0:-44.4,10:-42.6,20:-40.6,30:-38.5,40:-36.3,50:-34.0,60:-31.6,70:-29.0,80:-26.3,90:-23.4,100:-20.5,110:-17.4,120:-14.2,130:-10.9,140:-7.6
ATGSeedDiag: seed=1@21,108/1@143,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=27(36.0) imip=17/37 pass=10110 acc=-1 ipm=95.7,66.2 inv=85.4,36.5 | 44(33.9) imip=34/54 pass=10111 acc=-1 ipm=152.4,29.1 inv=118.0,22.2
frame=1422 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=141/170 raw=123/159 sel=141/137 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=35.4/30.1/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(111,88) md=40/1/150 cxcy=84.0,119.6 guide=-26.53 atg=60.0/46.0/59.0 pure=-5.45/-2.79 yaw=2122 cmd=2049 actual=2159 signed=0 rps=777/6393:4640/7418 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=141/170 centerNum=141/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=141/137 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-26.52@111,89 dx=27.0 idx=4/22 dist=42/312 right=1:-25.11@120,66 dx=35.9 idx=0/23 dist=41/427 sel=1:-27.29@114,85 dx=30.0 idx=0/20 dist=40/272 edge=1:-25.74@115.0,78.5 dx=31.0 width=52.5 l=89,75 r=141,82
CxScan: raw_ref=80.0 edge=115.0,78.5 best_raw_x=140 best_err=-7.08 best_cxcy=107.0,119.7 scan=0:-43.9,10:-42.1,20:-40.1,30:-38.0,40:-35.8,50:-33.5,60:-31.0,70:-28.5,80:-25.7,90:-22.9,100:-19.9,110:-16.8,120:-13.7,130:-10.4,140:-7.1
ATGSeedDiag: seed=1@21,108/1@143,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=26(35.4) imip=16/36 pass=10110 acc=-1 ipm=93.8,67.6 inv=83.8,37.2 | 42(30.1) imip=32/52 pass=10111 acc=-1 ipm=148.6,32.6 inv=116.8,23.1
frame=1423 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=142/170 raw=124/161 sel=142/138 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=36.2/35.4/0.0/0.0 dist=0 begin=0/3213 m0=(84,119) ml=(111,88) md=40/1/154 cxcy=84.0,119.6 guide=-26.11 atg=60.0/44.0/56.0 pure=-5.19/-2.69 yaw=2089 cmd=2041 actual=2113 signed=0 rps=811/6404:4899/7661 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=142/170 centerNum=142/170 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=142/138 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-25.62@109,90 dx=25.1 idx=4/21 dist=41/305 right=1:-24.07@119,64 dx=35.0 idx=0/25 dist=41/434 sel=1:-26.92@114,84 dx=29.6 idx=0/20 dist=40/274 edge=1:-24.84@114.0,78.0 dx=30.0 width=52.3 l=88,75 r=140,81
CxScan: raw_ref=80.0 edge=114.0,78.0 best_raw_x=140 best_err=-6.16 best_cxcy=107.0,119.7 scan=0:-43.3,10:-41.4,20:-39.4,30:-37.3,40:-35.0,50:-32.7,60:-30.2,70:-27.6,80:-24.8,90:-22.0,100:-19.0,110:-15.9,120:-12.7,130:-9.5,140:-6.2
ATGSeedDiag: seed=1@21,108/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(36.2) imip=15/35 pass=10110 acc=-1 ipm=92.1,69.3 inv=82.4,38.3 | 42(35.4) imip=32/52 pass=10111 acc=-1 ipm=145.8,31.8 inv=114.7,22.9

- stopped_at: 2026-06-22T15:38:28+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive162
```
