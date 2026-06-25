# drive78

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive78-front_car_circle_drive78.log
- remote_log: /tmp/front_car_circle_drive78.log
- started_at: 2026-06-22T05:38:00+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive78 6
```

4467 /tmp/front_car_circle_drive78.log
ATGLptDiag: best=13(94.7) imip=3/23 pass=11111 acc=13 ipm=75.9,92.0 inv=64.7,57.2 | 2(11.0) imip=0/3 pass=10111 acc=-1 ipm=118.4,112.7 inv=151.0,93.4
frame=872 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/4 raw=115/22 sel=12/13 far=0/0 far_raw=0/0 l=1@13/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.6/14.5/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(99,98) md=26/0/26 cxcy=84.0,119.6 guide=-18.53 atg=60.0/43.0/43.0 pure=-7.23/-7.23 yaw=1112 cmd=1223 actual=1001 signed=0 rps=3324/6676:6013/6830 duty=4/19 pwm=PWM2:4/PWM1:19 motor=2:4/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@13/0@-1 nearNum=12/4 centerNum=12/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.51@100,96 dx=15.6 idx=4/11 dist=29/29 right=1:-19.78@102,93 dx=17.9 idx=0/3 dist=6/6 sel=1:-18.50@99,98 dx=15.0 idx=0/12 dist=24/24 edge=1:-18.51@97.0,104.0 dx=13.0 width=48.7 l=74,96 r=120,112
CxScan: raw_ref=80.0 edge=97.0,104.0 best_raw_x=115 best_err=0.64 best_cxcy=97.4,119.7 scan=0:-48.6,10:-46.0,20:-43.0,30:-39.8,40:-36.2,50:-32.3,60:-28.1,70:-23.5,80:-18.5,90:-13.3,100:-7.8,110:-2.2,120:3.5,130:9.0,140:14.4
ATGSeedDiag: seed=1@16,108/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(97.6) imip=3/23 pass=11111 acc=13 ipm=75.9,92.2 inv=64.7,57.4 | 2(14.5) imip=0/3 pass=10111 acc=-1 ipm=118.0,113.1 inv=151.0,94.5
frame=873 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/4 raw=113/21 sel=11/12 far=0/0 far_raw=0/0 l=1@12/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.9/21.5/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(98,100) md=24/0/24 cxcy=84.0,119.6 guide=-18.14 atg=60.0/42.0/42.0 pure=-7.53/-7.53 yaw=1088 cmd=1210 actual=966 signed=0 rps=3341/6659:4604/5257 duty=5/21 pwm=PWM2:5/PWM1:21 motor=2:5/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@12/0@-1 nearNum=11/4 centerNum=11/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.62@99,99 dx=14.7 idx=4/10 dist=26/26 right=1:-20.61@103,92 dx=19.0 idx=0/3 dist=6/6 sel=1:-18.52@98,100 dx=14.3 idx=0/11 dist=22/22 edge=1:-18.28@96.5,105.0 dx=12.5 width=49.0 l=73,98 r=120,112
CxScan: raw_ref=80.0 edge=96.5,105.0 best_raw_x=115 best_err=1.41 best_cxcy=97.4,119.7 scan=0:-49.0,10:-46.3,20:-43.4,30:-40.1,40:-36.5,50:-32.5,60:-28.1,70:-23.4,80:-18.3,90:-12.9,100:-7.3,110:-1.5,120:4.3,130:10.0,140:15.5
ATGSeedDiag: seed=1@17,108/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(93.9) imip=2/22 pass=11111 acc=12 ipm=75.0,94.1 inv=63.2,59.7 | 2(21.5) imip=0/3 pass=10111 acc=-1 ipm=118.0,113.1 inv=151.1,94.6
frame=874 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/4 raw=111/20 sel=11/12 far=0/0 far_raw=0/0 l=1@12/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.0/30.8/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(98,99) md=23/0/23 cxcy=84.0,119.6 guide=-17.75 atg=60.0/40.0/40.0 pure=-7.24/-7.24 yaw=1065 cmd=1195 actual=934 signed=0 rps=3362/6638:4784/5409 duty=5/21 pwm=PWM2:5/PWM1:21 motor=2:5/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@12/0@-1 nearNum=11/4 centerNum=11/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.08@99,97 dx=14.9 idx=4/10 dist=27/27 right=1:-22.49@105,91 dx=21.3 idx=0/3 dist=6/6 sel=1:-17.91@98,99 dx=14.0 idx=0/11 dist=22/22 edge=1:-18.51@96.5,105.5 dx=12.5 width=49.3 l=73,98 r=120,113
CxScan: raw_ref=80.0 edge=96.5,105.5 best_raw_x=115 best_err=1.43 best_cxcy=97.4,119.7 scan=0:-49.4,10:-46.7,20:-43.8,30:-40.5,40:-36.8,50:-32.8,60:-28.4,70:-23.7,80:-18.5,90:-13.0,100:-7.3,110:-1.5,120:4.4,130:10.1,140:15.7
ATGSeedDiag: seed=1@18,108/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(97.0) imip=2/22 pass=11111 acc=12 ipm=74.7,93.7 inv=62.8,59.2 | 2(30.8) imip=0/3 pass=10111 acc=-1 ipm=118.1,113.3 inv=151.7,95.0
frame=875 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=10/3 raw=109/18 sel=10/12 far=0/0 far_raw=0/0 l=1@11/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.2/8.7/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(97,100) md=24/0/24 cxcy=84.0,119.6 guide=-16.91 atg=60.0/37.0/37.0 pure=-7.17/-7.17 yaw=1015 cmd=1117 actual=912 signed=0 rps=3469/6531:4968/5573 duty=5/20 pwm=PWM2:5/PWM1:20 motor=2:5/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@11/0@-1 nearNum=10/3 centerNum=10/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.40@98,99 dx=13.7 idx=3/9 dist=26/26 right=1:-18.24@100,95 dx=15.7 idx=0/2 dist=4/4 sel=1:-17.37@97,100 dx=13.3 idx=0/11 dist=22/22 edge=1:-16.62@95.0,106.0 dx=11.0 width=48.1 l=72,99 r=118,113
CxScan: raw_ref=80.0 edge=95.0,106.0 best_raw_x=110 best_err=0.81 best_cxcy=95.5,119.6 scan=0:-48.8,10:-46.0,20:-42.9,30:-39.5,40:-35.7,50:-31.5,60:-26.9,70:-22.0,80:-16.6,90:-11.0,100:-5.1,110:0.8,120:6.7,130:12.5,140:18.0
ATGSeedDiag: seed=1@19,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(94.2) imip=1/21 pass=11111 acc=11 ipm=74.4,95.7 inv=62.1,61.7 | 1(8.7) imip=0/2 pass=10111 acc=-1 ipm=116.7,114.8 inv=152.0,99.5
frame=876 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=10/3 raw=106/15 sel=10/13 far=0/0 far_raw=0/0 l=1@11/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.4/26.7/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(98,97) md=25/0/25 cxcy=84.0,119.6 guide=-17.01 atg=60.0/35.0/35.0 pure=-6.38/-6.38 yaw=1021 cmd=1156 actual=886 signed=0 rps=3416/6584:5200/5854 duty=5/20 pwm=PWM2:5/PWM1:20 motor=2:5/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@11/0@-1 nearNum=10/3 centerNum=10/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.47@98,96 dx=13.8 idx=3/9 dist=28/28 right=1:-21.09@103,93 dx=19.2 idx=0/2 dist=4/4 sel=1:-16.46@98,97 dx=13.6 idx=0/12 dist=24/24 edge=1:-17.79@95.5,107.0 dx=11.5 width=49.0 l=72,100 r=119,114
CxScan: raw_ref=80.0 edge=95.5,107.0 best_raw_x=110 best_err=0.03 best_cxcy=95.5,119.6 scan=0:-49.9,10:-47.2,20:-44.1,30:-40.7,40:-37.0,50:-32.8,60:-28.2,70:-23.2,80:-17.8,90:-12.1,100:-6.1,110:0.0,120:6.1,130:12.1,140:17.7
ATGSeedDiag: seed=1@20,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(94.4) imip=1/21 pass=11111 acc=11 ipm=72.9,95.2 inv=60.0,61.1 | 1(26.7) imip=0/2 pass=10111 acc=-1 ipm=116.8,114.8 inv=152.2,99.5
frame=877 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/3 raw=104/14 sel=9/12 far=0/0 far_raw=0/0 l=1@10/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.3/30.8/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(96,99) md=25/0/25 cxcy=84.0,119.6 guide=-15.34 atg=60.0/31.0/31.0 pure=-6.53/-6.53 yaw=920 cmd=959 actual=881 signed=0 rps=3685/6315:5194/5933 duty=6/19 pwm=PWM2:6/PWM1:19 motor=2:6/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@10/0@-1 nearNum=9/3 centerNum=9/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-15.75@97,98 dx=12.7 idx=2/8 dist=27/27 right=1:-23.10@106,92 dx=21.7 idx=0/2 dist=4/4 sel=1:-15.81@96,99 dx=12.3 idx=0/11 dist=22/22 edge=1:-17.29@95.0,107.5 dx=11.0 width=49.7 l=71,101 r=119,114
CxScan: raw_ref=80.0 edge=95.0,107.5 best_raw_x=110 best_err=0.84 best_cxcy=95.5,119.6 scan=0:-50.0,10:-47.2,20:-44.1,30:-40.7,40:-36.8,50:-32.6,60:-27.9,70:-22.8,80:-17.3,90:-11.4,100:-5.4,110:0.8,120:7.0,130:13.0,140:18.7
ATGSeedDiag: seed=1@21,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(96.3) imip=0/20 pass=11111 acc=10 ipm=73.0,97.2 inv=59.7,63.8 | 1(30.8) imip=0/2 pass=10111 acc=-1 ipm=116.9,114.9 inv=152.7,99.8
frame=878 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/2 raw=102/12 sel=9/13 far=0/0 far_raw=0/0 l=1@10/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=99.3/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(97,97) md=26/0/26 cxcy=84.0,119.6 guide=-15.86 atg=60.0/31.0/31.0 pure=-5.99/-5.99 yaw=952 cmd=1029 actual=874 signed=0 rps=3589/6411:4849/5571 duty=6/20 pwm=PWM2:6/PWM1:20 motor=2:6/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@10/0@-1 nearNum=9/2 centerNum=9/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-15.30@97,96 dx=12.8 idx=2/8 dist=28/28 right=1:-18.22@100,96 dx=15.5 idx=0/1 dist=2/2 sel=1:-15.32@97,97 dx=12.6 idx=0/12 dist=24/24 edge=1:-16.01@94.0,108.0 dx=10.0 width=48.1 l=71,101 r=117,115
CxScan: raw_ref=80.0 edge=94.0,108.0 best_raw_x=105 best_err=-0.65 best_cxcy=93.6,119.6 scan=0:-49.7,10:-46.8,20:-43.7,30:-40.1,40:-36.2,50:-31.8,60:-27.0,70:-21.7,80:-16.0,90:-10.0,100:-3.8,110:2.5,120:8.7,130:14.7,140:20.4
ATGSeedDiag: seed=1@22,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(99.3) imip=0/20 pass=11111 acc=10 ipm=72.6,96.8 inv=59.3,63.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/2 raw=101/11 sel=8/11 far=0/0 far_raw=0/0 l=1@9/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.7/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(95,101) md=21/0/21 cxcy=84.0,119.6 guide=-14.76 atg=60.0/27.0/27.0 pure=-6.29/-6.29 yaw=885 cmd=899 actual=872 signed=0 rps=3768/6232:4850/5562 duty=7/19 pwm=PWM2:7/PWM1:19 motor=2:7/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@9/0@-1 nearNum=8/2 centerNum=8/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-14.71@96,99 dx=11.6 idx=2/7 dist=25/25 right=1:-18.48@100,96 dx=15.7 idx=0/1 dist=2/2 sel=1:-14.69@95,101 dx=11.1 idx=0/10 dist=20/20 edge=1:-15.68@93.5,109.0 dx=9.5 width=48.5 l=70,103 r=117,115
CxScan: raw_ref=80.0 edge=93.5,109.0 best_raw_x=105 best_err=0.18 best_cxcy=93.6,119.6 scan=0:-50.2,10:-47.3,20:-44.1,30:-40.5,40:-36.4,50:-31.9,60:-27.0,70:-21.5,80:-15.7,90:-9.5,100:-3.1,110:3.4,120:9.8,130:15.9,140:21.7
ATGSeedDiag: seed=1@22,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(95.7) imip=0/19 pass=11111 acc=9 ipm=72.3,99.2 inv=58.2,66.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/2 raw=99/8 sel=8/12 far=0/0 far_raw=0/0 l=1@9/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.5/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(95,99) md=24/0/24 cxcy=84.0,119.6 guide=-14.11 atg=60.0/25.0/25.0 pure=-5.80/-5.80 yaw=846 cmd=823 actual=870 signed=0 rps=3872/6128:4568/5263 duty=7/19 pwm=PWM2:7/PWM1:19 motor=2:7/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@9/0@-1 nearNum=8/2 centerNum=8/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-13.86@95,97 dx=11.4 idx=1/7 dist=28/28 right=1:-22.97@105,93 dx=21.3 idx=0/1 dist=2/2 sel=1:-13.99@95,99 dx=10.9 idx=0/11 dist=22/22 edge=1:-16.46@94.0,109.0 dx=10.0 width=49.5 l=70,103 r=118,115
CxScan: raw_ref=80.0 edge=94.0,109.0 best_raw_x=105 best_err=-0.67 best_cxcy=93.6,119.6 scan=0:-50.5,10:-47.7,20:-44.5,30:-41.0,40:-37.0,50:-32.5,60:-27.6,70:-22.3,80:-16.5,90:-10.3,100:-3.9,110:2.6,120:9.0,130:15.1,140:21.0
ATGSeedDiag: seed=1@23,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(97.5) imip=0/19 pass=11111 acc=9 ipm=71.9,98.8 inv=57.7,66.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=7/1 raw=97/5 sel=7/11 far=0/0 far_raw=0/0 l=1@8/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.6/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(94,100) md=22/0/22 cxcy=84.0,119.6 guide=-13.16 atg=56.0/22.0/22.0 pure=-5.69/-5.69 yaw=790 cmd=729 actual=850 signed=0 rps=4000/6000:4726/5500 duty=8/18 pwm=PWM2:8/PWM1:18 motor=2:8/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@8/0@-1 nearNum=7/1 centerNum=7/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-13.16@94,99 dx=10.4 idx=1/6 dist=25/25 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-13.23@94,100 dx=10.0 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,105 r=-1,-1
ATGSeedDiag: seed=1@24,108/1@154,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(94.6) imip=0/18 pass=11111 acc=8 ipm=71.5,100.8 inv=56.3,69.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=7/1 raw=95/5 sel=7/12 far=0/0 far_raw=0/0 l=1@8/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=99.1/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(94,97) md=25/0/25 cxcy=84.0,119.6 guide=-12.32 atg=50.0/20.0/20.0 pure=-5.08/-5.08 yaw=739 cmd=644 actual=835 signed=0 rps=4118/5882:4614/5409 duty=8/18 pwm=PWM2:8/PWM1:18 motor=2:8/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@8/0@-1 nearNum=7/1 centerNum=7/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.46@94,97 dx=10.2 idx=1/6 dist=26/26 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-12.51@94,97 dx=10.1 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,105 r=-1,-1
ATGSeedDiag: seed=1@25,108/1@155,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(99.1) imip=0/18 pass=11111 acc=8 ipm=71.6,100.4 inv=56.6,68.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=7/1 raw=94/4 sel=7/13 far=0/0 far_raw=0/0 l=1@8/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=98.4/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(94,96) md=26/0/26 cxcy=84.0,119.6 guide=-12.07 atg=46.0/18.0/18.0 pure=-4.61/-4.61 yaw=724 cmd=637 actual=811 signed=0 rps=4127/5873:4993/5832 duty=8/17 pwm=PWM2:8/PWM1:17 motor=2:8/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@8/0@-1 nearNum=7/1 centerNum=7/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-11.64@94,96 dx=9.7 idx=0/6 dist=28/28 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-11.66@94,96 dx=9.7 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,105 r=-1,-1
ATGSeedDiag: seed=1@25,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(98.4) imip=0/18 pass=11111 acc=8 ipm=70.8,100.4 inv=55.5,68.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/1 raw=91/2 sel=6/12 far=0/0 far_raw=0/0 l=1@7/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=98.3/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(93,97) md=25/0/25 cxcy=84.0,119.6 guide=-11.12 atg=39.0/15.0/15.0 pure=-4.44/-4.44 yaw=667 cmd=549 actual=785 signed=0 rps=4248/5752:4965/5737 duty=8/17 pwm=PWM2:8/PWM1:17 motor=2:8/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@7/0@-1 nearNum=6/1 centerNum=6/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.87@93,97 dx=8.8 idx=0/5 dist=25/25 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-10.87@93,97 dx=8.8 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=68,106 r=-1,-1
ATGSeedDiag: seed=1@26,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(98.3) imip=0/17 pass=11111 acc=7 ipm=70.8,102.4 inv=54.8,71.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/0 raw=88/0 sel=6/12 far=0/0 far_raw=0/0 l=1@7/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.4/0.0/0.0/0.0 dist=0 begin=0/2467 m0=(84,119) ml=(92,96) md=25/0/25 cxcy=84.0,119.6 guide=-9.70 atg=31.0/12.0/12.0 pure=-3.89/-3.89 yaw=582 cmd=411 actual=752 signed=0 rps=4436/5564:5183/5814 duty=9/16 pwm=PWM2:9/PWM1:16 motor=2:9/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@7/0@-1 nearNum=6/0 centerNum=6/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-9.50@92,95 dx=8.1 idx=0/5 dist=27/27 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-9.63@92,96 dx=7.9 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,106 r=-1,-1
ATGSeedDiag: seed=1@27,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(97.4) imip=0/17 pass=11111 acc=7 ipm=69.8,102.0 inv=53.3,71.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T05:38:13+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive78
```
