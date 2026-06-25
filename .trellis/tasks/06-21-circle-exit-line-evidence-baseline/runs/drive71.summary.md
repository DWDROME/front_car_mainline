# drive71

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive71-front_car_circle_drive71.log
- remote_log: /tmp/front_car_circle_drive71.log
- started_at: 2026-06-22T04:46:34+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive71 6
```

4720 /tmp/front_car_circle_drive71.log
LineErr: aim=33 cxcy=84.0,119.6 left=1:-5.41@89,93 dx=4.7 idx=0/20 dist=33/258 right=1:-9.59@95,77 dx=11.1 idx=0/10 dist=31/108 sel=1:-8.39@92,90 dx=7.7 idx=0/16 dist=32/212 edge=1:-10.37@94.5,85.5 dx=10.5 width=61.7 l=64,81 r=125,90
CxScan: raw_ref=80.0 edge=94.5,85.5 best_raw_x=105 best_err=-0.90 best_cxcy=93.6,119.6 scan=0:-35.9,10:-33.2,20:-30.4,30:-27.5,40:-24.3,50:-21.0,60:-17.6,70:-14.0,80:-10.4,90:-6.6,100:-2.8,110:1.0,120:4.8,130:8.6,140:12.3
ATGSeedDiag: seed=1@6,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=53(59.4) imip=43/63 pass=10100 acc=-1 ipm=139.6,46.6 inv=116.1,27.6 | 21(93.5) imip=11/26 pass=11111 acc=21 ipm=136.0,89.8 inv=143.7,54.1
frame=876 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=123/26 raw=170/93 sel=123/107 far=0/0 far_raw=0/0 l=0@-1/1@20 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=59.2/93.1/0.0/0.0 dist=0 begin=639/3245 m0=(84,119) ml=(90,92) md=33/1/169 cxcy=84.0,119.6 guide=-6.48 atg=60.0/60.0/60.0 pure=-6.90/-6.63 yaw=389 cmd=483 actual=294 signed=1 rps=3138/4462:5099/5912 duty=4/10 pwm=PWM2:4/PWM1:10 motor=2:4/1:10
ATGCorner: L=0@-1/1@20 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.8,88.8:140.9,53.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=53:140.0,46.4:116.3,27.5:59.2:10100/20:134.8,88.8:140.9,53.1:93.1:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=59.2/93.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@20 nearNum=123/26 centerNum=123/26 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=123/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-7.03@90,92 dx=6.2 idx=0/21 dist=33/253 right=1:-10.17@96,77 dx=11.8 idx=0/10 dist=31/96 sel=1:-8.99@92,91 dx=8.2 idx=0/16 dist=32/212 edge=1:-10.94@95.0,86.0 dx=11.0 width=62.5 l=64,82 r=126,90
CxScan: raw_ref=80.0 edge=95.0,86.0 best_raw_x=110 best_err=0.52 best_cxcy=95.5,119.6 scan=0:-36.4,10:-33.8,20:-31.0,30:-28.1,40:-24.9,50:-21.6,60:-18.2,70:-14.6,80:-10.9,90:-7.2,100:-3.3,110:0.5,120:4.4,130:8.2,140:11.9
ATGSeedDiag: seed=1@6,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=53(59.2) imip=43/63 pass=10100 acc=-1 ipm=140.0,46.4 inv=116.3,27.5 | 20(93.1) imip=10/25 pass=11111 acc=20 ipm=134.8,88.8 inv=140.9,53.1
frame=877 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=124/26 raw=170/85 sel=124/108 far=0/0 far_raw=0/0 l=0@-1/1@20 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=59.5/94.8/0.0/0.0 dist=0 begin=653/3245 m0=(84,119) ml=(91,92) md=33/1/169 cxcy=84.0,119.6 guide=-8.25 atg=60.0/60.0/60.0 pure=-7.04/-6.57 yaw=495 cmd=667 actual=323 signed=1 rps=2886/4714:4869/5451 duty=4/11 pwm=PWM2:4/PWM1:11 motor=2:4/1:11
ATGCorner: L=0@-1/1@20 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/135.3,89.5:142.4,53.8 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=53:140.2,46.3:116.4,27.5:59.5:10100/20:135.3,89.5:142.4,53.8:94.8:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=59.5/94.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@20 nearNum=124/26 centerNum=124/26 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/108 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-6.19@89,93 dx=5.4 idx=1/20 dist=33/260 right=1:-13.45@100,74 dx=16.5 idx=0/11 dist=35/97 sel=1:-9.69@93,90 dx=9.0 idx=0/16 dist=32/214 edge=1:-11.53@95.5,86.5 dx=11.5 width=61.7 l=65,82 r=126,91
CxScan: raw_ref=80.0 edge=95.5,86.5 best_raw_x=110 best_err=0.02 best_cxcy=95.5,119.6 scan=0:-37.0,10:-34.4,20:-31.6,30:-28.7,40:-25.5,50:-22.3,60:-18.8,70:-15.2,80:-11.5,90:-7.7,100:-3.9,110:0.0,120:3.9,130:7.7,140:11.5
ATGSeedDiag: seed=1@6,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=53(59.5) imip=43/63 pass=10100 acc=-1 ipm=140.2,46.3 inv=116.4,27.5 | 20(94.8) imip=10/25 pass=11111 acc=20 ipm=135.3,89.5 inv=142.4,53.8
frame=878 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/25 raw=170/83 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/1@20 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/96.3/0.0/0.0 dist=0 begin=667/3245 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-7.04/-6.57 yaw=0 cmd=0 actual=447 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/1@20 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/135.7,90.3:143.8,54.6 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:135.7,90.3:143.8,54.6:96.3:11111 seed_src=lost/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/96.3/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@20 nearNum=1/25 centerNum=1/25 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-11.59@98,77 dx=13.5 idx=0/10 dist=31/90 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=127,91
ATGSeedDiag: seed=1@10,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(96.3) imip=10/24 pass=11111 acc=20 ipm=135.7,90.3 inv=143.8,54.6
frame=879 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/25 raw=170/87 sel=122/107 far=0/0 far_raw=0/0 l=0@-1/1@19 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=59.5/92.7/0.0/0.0 dist=0 begin=682/3245 m0=(84,119) ml=(91,93) md=34/1/170 cxcy=84.0,119.6 guide=-7.19 atg=60.0/60.0/60.0 pure=-7.18/-6.65 yaw=432 cmd=444 actual=419 signed=1 rps=3191/4409:5737/5524 duty=4/11 pwm=PWM2:4/PWM1:11 motor=2:4/1:11
ATGCorner: L=0@-1/1@19 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.0,90.7:142.0,55.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=52:139.2,48.3:116.6,28.2:59.5:10100/19:134.0,90.7:142.0,55.1:92.7:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=59.5/92.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@19 nearNum=122/25 centerNum=122/25 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-6.87@90,94 dx=5.8 idx=0/20 dist=33/257 right=1:-12.47@99,76 dx=14.7 idx=0/10 dist=31/93 sel=1:-9.82@93,92 dx=8.8 idx=0/16 dist=32/212 edge=1:-12.12@96.0,87.0 dx=12.0 width=62.8 l=65,82 r=127,92
CxScan: raw_ref=80.0 edge=96.0,87.0 best_raw_x=110 best_err=-0.49 best_cxcy=95.5,119.6 scan=0:-37.6,10:-35.0,20:-32.2,30:-29.3,40:-26.2,50:-22.9,60:-19.4,70:-15.8,80:-12.1,90:-8.3,100:-4.4,110:-0.5,120:3.4,130:7.3,140:11.1
ATGSeedDiag: seed=1@6,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(59.5) imip=42/62 pass=10100 acc=-1 ipm=139.2,48.3 inv=116.6,28.2 | 19(92.7) imip=9/24 pass=11111 acc=19 ipm=134.0,90.7 inv=142.0,55.1
frame=880 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=123/24 raw=170/81 sel=123/106 far=0/0 far_raw=0/0 l=0@-1/1@19 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=59.2/95.2/0.0/0.0 dist=0 begin=697/3245 m0=(84,119) ml=(91,94) md=33/1/169 cxcy=84.0,119.6 guide=-8.35 atg=60.0/60.0/60.0 pure=-7.38/-6.67 yaw=501 cmd=648 actual=355 signed=1 rps=2912/4688:5405/5217 duty=3/12 pwm=PWM2:3/PWM1:12 motor=2:3/1:12
ATGCorner: L=0@-1/1@19 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.4,91.5:143.6,56.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=52:139.5,48.0:116.6,28.1:59.2:10100/19:134.4,91.5:143.6,56.0:95.2:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=59.2/95.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@19 nearNum=123/24 centerNum=123/24 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=123/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-5.92@89,96 dx=4.9 idx=0/19 dist=33/256 right=1:-13.06@99,76 dx=15.4 idx=0/10 dist=31/84 sel=1:-9.65@93,92 dx=8.6 idx=0/16 dist=32/210 edge=1:-13.10@97.0,87.0 dx=13.0 width=62.8 l=66,82 r=128,92
CxScan: raw_ref=80.0 edge=97.0,87.0 best_raw_x=115 best_err=0.44 best_cxcy=97.4,119.7 scan=0:-38.2,10:-35.7,20:-32.9,30:-30.0,40:-27.0,50:-23.7,60:-20.3,70:-16.8,80:-13.1,90:-9.3,100:-5.4,110:-1.5,120:2.4,130:6.3,140:10.1
ATGSeedDiag: seed=1@6,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(59.2) imip=42/62 pass=10100 acc=-1 ipm=139.5,48.0 inv=116.6,28.1 | 19(95.2) imip=9/23 pass=11111 acc=19 ipm=134.4,91.5 inv=143.6,56.0
frame=881 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/23 raw=170/79 sel=122/105 far=0/0 far_raw=0/0 l=0@-1/1@19 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=60.5/88.8/0.0/0.0 dist=0 begin=712/3245 m0=(84,119) ml=(91,94) md=33/1/170 cxcy=84.0,119.6 guide=-8.42 atg=60.0/60.0/60.0 pure=-7.46/-6.70 yaw=505 cmd=674 actual=336 signed=1 rps=2876/4724:5571/5508 duty=3/12 pwm=PWM2:3/PWM1:12 motor=2:3/1:12
ATGCorner: L=0@-1/1@19 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.7,92.1:144.7,56.6 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=51:137.9,50.6:116.6,29.1:60.5:11100/19:134.7,92.1:144.7,56.6:88.8:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=60.5/88.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@19 nearNum=122/23 centerNum=122/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/105 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-4.91@88,97 dx=3.9 idx=0/18 dist=33/259 right=1:-13.36@100,77 dx=15.7 idx=0/10 dist=31/79 sel=1:-10.06@93,93 dx=8.9 idx=0/16 dist=32/208 edge=1:-13.21@97.0,87.5 dx=13.0 width=63.0 l=66,82 r=128,93
CxScan: raw_ref=80.0 edge=97.0,87.5 best_raw_x=115 best_err=0.45 best_cxcy=97.4,119.7 scan=0:-38.5,10:-35.9,20:-33.2,30:-30.3,40:-27.2,50:-23.9,60:-20.5,70:-16.9,80:-13.2,90:-9.4,100:-5.5,110:-1.5,120:2.4,130:6.4,140:10.2
ATGSeedDiag: seed=1@6,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=51(60.5) imip=41/61 pass=11100 acc=-1 ipm=137.9,50.6 inv=116.6,29.1 | 19(88.8) imip=9/22 pass=11111 acc=19 ipm=134.7,92.1 inv=144.7,56.6
frame=882 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=123/23 raw=170/78 sel=123/108 far=0/0 far_raw=0/0 l=0@-1/1@19 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=58.9/91.0/0.0/0.0 dist=0 begin=728/3245 m0=(84,119) ml=(90,95) md=32/1/171 cxcy=84.0,119.6 guide=-8.43 atg=60.0/60.0/60.0 pure=-7.56/-6.63 yaw=506 cmd=677 actual=335 signed=1 rps=2872/4728:5335/5480 duty=3/12 pwm=PWM2:3/PWM1:12 motor=2:3/1:12
ATGCorner: L=0@-1/1@19 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.0,94.5:147.0,59.5 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=50:136.3,52.1:116.0,29.7:58.9:10100/19:134.0,94.5:147.0,59.5:91.0:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=58.9/91.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@19 nearNum=123/23 centerNum=123/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=123/108 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-7.12@90,95 dx=6.0 idx=1/20 dist=33/258 right=1:-14.40@101,76 dx=17.1 idx=0/10 dist=31/80 sel=1:-10.73@94,92 dx=9.6 idx=0/16 dist=32/214 edge=1:-13.21@97.0,87.5 dx=13.0 width=63.0 l=66,82 r=128,93
CxScan: raw_ref=80.0 edge=97.0,87.5 best_raw_x=115 best_err=0.45 best_cxcy=97.4,119.7 scan=0:-38.5,10:-35.9,20:-33.2,30:-30.3,40:-27.2,50:-23.9,60:-20.5,70:-16.9,80:-13.2,90:-9.4,100:-5.5,110:-1.5,120:2.4,130:6.4,140:10.2
ATGSeedDiag: seed=1@6,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(58.9) imip=40/60 pass=10100 acc=-1 ipm=136.3,52.1 inv=116.0,29.7 | 19(91.0) imip=9/22 pass=11111 acc=19 ipm=134.0,94.5 inv=147.0,59.5
frame=883 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=123/23 raw=170/77 sel=123/108 far=0/0 far_raw=0/0 l=0@-1/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=60.8/95.2/0.0/0.0 dist=0 begin=744/3245 m0=(84,119) ml=(92,94) md=34/1/170 cxcy=84.0,119.6 guide=-8.52 atg=60.0/60.0/60.0 pure=-7.60/-6.63 yaw=511 cmd=663 actual=360 signed=1 rps=2892/4708:5491/5868 duty=3/11 pwm=PWM2:3/PWM1:11 motor=2:3/1:11
ATGCorner: L=0@-1/1@18 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/133.4,92.8:143.8,57.5 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=50:136.6,51.9:116.1,29.6:60.8:11100/18:133.4,92.8:143.8,57.5:95.2:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=60.8/95.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@18 nearNum=123/23 centerNum=123/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=123/108 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-7.63@90,96 dx=6.3 idx=1/20 dist=33/259 right=1:-14.92@102,76 dx=17.8 idx=0/10 dist=32/81 sel=1:-11.14@94,93 dx=9.9 idx=0/16 dist=32/214 edge=1:-13.83@97.5,88.0 dx=13.5 width=63.8 l=66,83 r=129,93
CxScan: raw_ref=80.0 edge=97.5,88.0 best_raw_x=115 best_err=-0.07 best_cxcy=97.4,119.7 scan=0:-39.0,10:-36.5,20:-33.8,30:-30.9,40:-27.8,50:-24.6,60:-21.1,70:-17.6,80:-13.8,90:-10.0,100:-6.1,110:-2.1,120:1.9,130:5.9,140:9.8
ATGSeedDiag: seed=1@5,108/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(60.8) imip=40/60 pass=11100 acc=-1 ipm=136.6,51.9 inv=116.1,29.6 | 18(95.2) imip=8/22 pass=11111 acc=18 ipm=133.4,92.8 inv=143.8,57.5
frame=885 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=126/21 raw=170/73 sel=126/108 far=0/0 far_raw=0/0 l=0@-1/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=60.8/95.0/0.0/0.0 dist=0 begin=773/3245 m0=(84,119) ml=(92,95) md=32/1/169 cxcy=84.0,119.6 guide=-10.86 atg=60.0/60.0/60.0 pure=-7.81/-6.62 yaw=652 cmd=852 actual=413 signed=1 rps=2633/4967:5005/5624 duty=3/13 pwm=PWM2:3/PWM1:13 motor=2:3/1:13
ATGCorner: L=0@-1/1@18 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.1,94.7:147.3,59.7 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=50:137.4,51.3:116.5,29.3:60.8:11100/18:134.1,94.7:147.3,59.7:95.0:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=60.8/95.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@18 nearNum=126/21 centerNum=126/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=126/108 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-7.14@90,97 dx=5.8 idx=1/19 dist=33/261 right=1:-16.41@104,76 dx=19.6 idx=0/10 dist=32/69 sel=1:-11.58@94,93 dx=10.1 idx=0/16 dist=32/214 edge=1:-14.94@98.5,88.5 dx=14.5 width=64.0 l=67,83 r=130,94
CxScan: raw_ref=80.0 edge=98.5,88.5 best_raw_x=120 best_err=0.89 best_cxcy=99.3,119.7 scan=0:-39.9,10:-37.4,20:-34.7,30:-31.9,40:-28.9,50:-25.6,60:-22.2,70:-18.7,80:-14.9,90:-11.1,100:-7.1,110:-3.1,120:0.9,130:4.9,140:8.9
ATGSeedDiag: seed=1@5,108/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(60.8) imip=40/60 pass=11100 acc=-1 ipm=137.4,51.3 inv=116.5,29.3 | 18(95.0) imip=8/20 pass=11111 acc=18 ipm=134.1,94.7 inv=147.3,59.7
frame=886 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=126/21 raw=170/73 sel=126/106 far=0/0 far_raw=0/0 l=0@-1/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=60.2/94.7/0.0/0.0 dist=0 begin=787/3245 m0=(84,119) ml=(94,95) md=33/1/168 cxcy=84.0,119.6 guide=-12.15 atg=60.0/60.0/60.0 pure=-7.98/-6.54 yaw=729 cmd=929 actual=432 signed=1 rps=2527/5073:4990/5849 duty=3/13 pwm=PWM2:3/PWM1:13 motor=2:3/1:13
ATGCorner: L=0@-1/1@18 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/133.9,96.0:148.9,61.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=50:137.5,51.2:116.5,29.3:60.2:11100/18:133.9,96.0:148.9,61.4:94.7:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=60.2/94.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@18 nearNum=126/21 centerNum=126/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=126/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-8.71@91,96 dx=7.1 idx=2/20 dist=32/260 right=1:-17.16@105,76 dx=20.6 idx=0/10 dist=33/70 sel=1:-12.92@95,93 dx=11.4 idx=0/16 dist=32/210 edge=1:-15.07@98.5,89.0 dx=14.5 width=64.1 l=67,83 r=130,95
CxScan: raw_ref=80.0 edge=98.5,89.0 best_raw_x=120 best_err=0.90 best_cxcy=99.3,119.7 scan=0:-40.2,10:-37.7,20:-35.0,30:-32.1,40:-29.1,50:-25.8,60:-22.4,70:-18.8,80:-15.1,90:-11.2,100:-7.2,110:-3.2,120:0.9,130:5.0,140:9.0
ATGSeedDiag: seed=1@5,108/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(60.2) imip=40/60 pass=11100 acc=-1 ipm=137.5,51.2 inv=116.5,29.3 | 18(94.7) imip=8/20 pass=11111 acc=18 ipm=133.9,96.0 inv=148.9,61.4
frame=887 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/21 raw=170/71 sel=122/107 far=0/0 far_raw=0/0 l=0@-1/1@17 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=61.4/94.0/0.0/0.0 dist=0 begin=801/3245 m0=(84,119) ml=(94,95) md=33/1/168 cxcy=84.0,119.6 guide=-11.77 atg=60.0/60.0/60.0 pure=-8.08/-6.54 yaw=706 cmd=906 actual=475 signed=1 rps=2558/5042:4665/5528 duty=3/13 pwm=PWM2:3/PWM1:13 motor=2:3/1:13
ATGCorner: L=0@-1/1@17 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/132.8,95.1:146.1,60.3 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=49:136.1,53.6:116.5,30.3:61.4:11100/17:132.8,95.1:146.1,60.3:94.0:11111 seed_src=none/lpt seed=40.0,91.8/114.3,9.3 far_start=114,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=61.4/94.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@17 nearNum=122/21 centerNum=122/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-9.84@92,96 dx=8.2 idx=2/21 dist=32/255 right=1:-18.04@106,76 dx=21.8 idx=0/10 dist=33/70 sel=1:-13.31@96,93 dx=11.7 idx=0/16 dist=32/212 edge=1:-15.07@98.5,89.0 dx=14.5 width=64.1 l=67,83 r=130,95
CxScan: raw_ref=80.0 edge=98.5,89.0 best_raw_x=120 best_err=0.90 best_cxcy=99.3,119.7 scan=0:-40.2,10:-37.7,20:-35.0,30:-32.1,40:-29.1,50:-25.8,60:-22.4,70:-18.8,80:-15.1,90:-11.2,100:-7.2,110:-3.2,120:0.9,130:5.0,140:9.0
ATGSeedDiag: seed=1@5,108/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(61.4) imip=39/59 pass=11100 acc=-1 ipm=136.1,53.6 inv=116.5,30.3 | 17(94.0) imip=7/20 pass=11111 acc=17 ipm=132.8,95.1 inv=146.1,60.3

- stopped_at: 2026-06-22T04:46:47+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive71
```
