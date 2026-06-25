# drive90

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive90-front_car_circle_drive90.log
- remote_log: /tmp/front_car_circle_drive90.log
- started_at: 2026-06-22T06:29:56+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive90 6
```

4278 /tmp/front_car_circle_drive90.log
ATGSeedDiag: seed=1@15,108/1@136,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=55(14.7) imip=45/65 pass=10100 acc=-1 ipm=151.7,50.7 inv=127.5,29.0 | 10(36.2) imip=0/20 pass=10111 acc=-1 ipm=118.7,97.6 inv=128.4,63.7
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=68/22 raw=158/71 sel=68/48 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.9/34.1/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(99,92) md=33/1/97 cxcy=84.0,119.6 guide=-16.34 atg=60.0/60.0/60.0 pure=-7.91/-8.50 yaw=981 cmd=1181 actual=389 signed=0 rps=3382/6618:3617/3919 duty=8/22 pwm=PWM2:8/PWM1:22 motor=2:8/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=68/22 centerNum=68/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=68/48 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-15.34@98,92 dx=13.9 idx=2/23 dist=32/115 right=1:-18.60@107,75 dx=23.0 idx=0/11 dist=34/64 sel=1:-17.77@101,90 dx=16.8 idx=0/16 dist=32/94 edge=1:-17.08@101.0,87.5 dx=17.0 width=63.0 l=70,82 r=132,93
CxScan: raw_ref=80.0 edge=101.0,87.5 best_raw_x=125 best_err=0.27 best_cxcy=101.3,119.7 scan=0:-40.9,10:-38.5,20:-36.0,30:-33.3,40:-30.4,50:-27.3,60:-24.1,70:-20.6,80:-17.1,90:-13.4,100:-9.6,110:-5.7,120:-1.7,130:2.2,140:6.2
ATGSeedDiag: seed=1@15,107/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.9) imip=0/20 pass=10110 acc=-1 ipm=62.5,93.7 inv=45.7,59.3 | 10(34.1) imip=0/20 pass=10111 acc=-1 ipm=118.9,97.8 inv=129.0,64.0
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=67/21 raw=159/71 sel=67/47 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.1/43.6/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(99,92) md=33/1/98 cxcy=84.0,119.6 guide=-15.79 atg=60.0/60.0/60.0 pure=-8.01/-8.58 yaw=948 cmd=1148 actual=412 signed=0 rps=3427/6573:4887/5011 duty=6/21 pwm=PWM2:6/PWM1:21 motor=2:6/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/21 centerNum=67/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=67/47 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-14.54@97,94 dx=12.8 idx=2/22 dist=32/115 right=1:-18.62@107,75 dx=22.9 idx=0/11 dist=34/61 sel=1:-18.09@101,91 dx=17.1 idx=0/16 dist=32/92 edge=1:-17.22@101.0,88.0 dx=17.0 width=62.8 l=70,83 r=132,93
CxScan: raw_ref=80.0 edge=101.0,88.0 best_raw_x=125 best_err=0.27 best_cxcy=101.3,119.7 scan=0:-41.2,10:-38.8,20:-36.2,30:-33.5,40:-30.6,50:-27.5,60:-24.3,70:-20.8,80:-17.2,90:-13.5,100:-9.6,110:-5.7,120:-1.7,130:2.3,140:6.2
ATGSeedDiag: seed=1@14,108/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(16.1) imip=0/20 pass=10110 acc=-1 ipm=62.4,94.0 inv=45.3,59.7 | 10(43.6) imip=0/20 pass=10111 acc=-1 ipm=119.0,97.9 inv=129.3,64.2
frame=891 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=66/21 raw=158/69 sel=66/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.9/42.4/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(100,93) md=33/1/96 cxcy=84.0,119.6 guide=-17.70 atg=60.0/60.0/60.0 pure=-8.27/-8.79 yaw=1062 cmd=1262 actual=431 signed=0 rps=3271/6729:3907/4040 duty=7/23 pwm=PWM2:7/PWM1:23 motor=2:7/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=66/21 centerNum=66/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=66/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-15.00@97,94 dx=13.0 idx=2/22 dist=33/113 right=1:-19.47@108,75 dx=24.0 idx=0/11 dist=33/60 sel=1:-18.95@102,91 dx=17.6 idx=0/16 dist=32/90 edge=1:-17.85@101.5,88.5 dx=17.5 width=62.0 l=71,83 r=132,94
CxScan: raw_ref=80.0 edge=101.5,88.5 best_raw_x=125 best_err=-0.25 best_cxcy=101.3,119.7 scan=0:-41.7,10:-39.4,20:-36.8,30:-34.1,40:-31.2,50:-28.2,60:-24.9,70:-21.5,80:-17.9,90:-14.1,100:-10.2,110:-6.3,120:-2.3,130:1.8,140:5.8
ATGSeedDiag: seed=1@13,108/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=57(14.9) imip=47/65 pass=10100 acc=-1 ipm=158.4,55.8 inv=136.1,31.1 | 10(42.4) imip=0/20 pass=10111 acc=-1 ipm=119.4,98.3 inv=130.3,64.8
frame=892 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=65/20 raw=158/68 sel=65/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.5/42.7/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(100,93) md=33/1/95 cxcy=84.0,119.6 guide=-17.83 atg=60.0/60.0/60.0 pure=-8.36/-8.88 yaw=1070 cmd=1270 actual=434 signed=0 rps=3260/6740:3943/4217 duty=7/22 pwm=PWM2:7/PWM1:22 motor=2:7/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=65/20 centerNum=65/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=65/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.35@98,94 dx=14.4 idx=2/23 dist=33/111 right=1:-19.57@108,75 dx=24.0 idx=0/11 dist=33/57 sel=1:-19.21@102,92 dx=17.8 idx=0/16 dist=32/88 edge=1:-18.33@102.0,88.5 dx=18.0 width=63.0 l=71,83 r=133,94
CxScan: raw_ref=80.0 edge=102.0,88.5 best_raw_x=125 best_err=-0.78 best_cxcy=101.3,119.7 scan=0:-42.0,10:-39.7,20:-37.2,30:-34.5,40:-31.6,50:-28.6,60:-25.3,70:-21.9,80:-18.3,90:-14.6,100:-10.7,110:-6.8,120:-2.8,130:1.2,140:5.2
ATGSeedDiag: seed=1@13,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.5) imip=0/20 pass=10110 acc=-1 ipm=63.0,94.2 inv=46.0,60.0 | 9(42.7) imip=0/19 pass=10111 acc=-1 ipm=117.6,99.7 inv=129.2,66.9
frame=893 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=65/20 raw=158/67 sel=65/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.3/40.5/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(100,93) md=33/1/94 cxcy=84.0,119.6 guide=-18.75 atg=60.0/60.0/60.0 pure=-8.37/-8.82 yaw=1125 cmd=1325 actual=453 signed=0 rps=3184/6816:3938/4401 duty=7/23 pwm=PWM2:7/PWM1:23 motor=2:7/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=65/20 centerNum=65/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=65/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.29@98,94 dx=14.3 idx=2/23 dist=33/112 right=1:-19.82@108,75 dx=24.3 idx=0/11 dist=32/56 sel=1:-19.26@102,92 dx=17.8 idx=0/16 dist=32/88 edge=1:-18.33@102.0,88.5 dx=18.0 width=63.0 l=71,83 r=133,94
CxScan: raw_ref=80.0 edge=102.0,88.5 best_raw_x=125 best_err=-0.78 best_cxcy=101.3,119.7 scan=0:-42.0,10:-39.7,20:-37.2,30:-34.5,40:-31.6,50:-28.6,60:-25.3,70:-21.9,80:-18.3,90:-14.6,100:-10.7,110:-6.8,120:-2.8,130:1.2,140:5.2
ATGSeedDiag: seed=1@13,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.3) imip=0/20 pass=10110 acc=-1 ipm=63.0,94.3 inv=46.0,60.0 | 9(40.5) imip=0/19 pass=10111 acc=-1 ipm=117.8,100.0 inv=129.8,67.2
frame=894 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=65/20 raw=158/66 sel=65/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.6/39.0/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(100,93) md=33/1/94 cxcy=84.0,119.6 guide=-18.03 atg=60.0/60.0/60.0 pure=-8.32/-8.74 yaw=1082 cmd=1282 actual=479 signed=0 rps=3243/6757:3968/4566 duty=7/22 pwm=PWM2:7/PWM1:22 motor=2:7/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=65/20 centerNum=65/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=65/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.29@98,94 dx=14.3 idx=3/23 dist=33/113 right=1:-20.24@109,76 dx=24.8 idx=0/11 dist=32/56 sel=1:-19.62@102,92 dx=18.2 idx=0/16 dist=32/90 edge=1:-18.49@102.0,89.0 dx=18.0 width=63.2 l=71,83 r=133,95
CxScan: raw_ref=80.0 edge=102.0,89.0 best_raw_x=125 best_err=-0.79 best_cxcy=101.3,119.7 scan=0:-42.3,10:-40.0,20:-37.4,30:-34.7,40:-31.9,50:-28.8,60:-25.5,70:-22.1,80:-18.5,90:-14.7,100:-10.8,110:-6.9,120:-2.8,130:1.2,140:5.3
ATGSeedDiag: seed=1@13,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=57(13.6) imip=47/64 pass=10100 acc=-1 ipm=158.7,55.9 inv=136.5,31.1 | 9(39.0) imip=0/19 pass=10111 acc=-1 ipm=118.1,100.1 inv=130.5,67.5
frame=895 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=65/19 raw=158/65 sel=65/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.0/39.3/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(100,93) md=33/1/94 cxcy=84.0,119.6 guide=-18.03 atg=60.0/60.0/60.0 pure=-8.43/-8.76 yaw=1082 cmd=1282 actual=515 signed=0 rps=3243/6757:4029/4648 duty=7/22 pwm=PWM2:7/PWM1:22 motor=2:7/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=65/19 centerNum=65/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=65/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.78@99,94 dx=14.7 idx=3/23 dist=33/112 right=1:-22.22@112,75 dx=27.9 idx=0/12 dist=34/52 sel=1:-19.65@102,92 dx=18.2 idx=0/16 dist=32/88 edge=1:-18.97@102.5,89.0 dx=18.5 width=64.1 l=71,83 r=134,95
CxScan: raw_ref=80.0 edge=102.5,89.0 best_raw_x=130 best_err=0.71 best_cxcy=103.2,119.7 scan=0:-42.6,10:-40.3,20:-37.8,30:-35.1,40:-32.2,50:-29.2,60:-26.0,70:-22.6,80:-19.0,90:-15.2,100:-11.4,110:-7.4,120:-3.4,130:0.7,140:4.8
ATGSeedDiag: seed=1@12,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.0) imip=0/20 pass=10110 acc=-1 ipm=62.9,94.3 inv=45.9,60.1 | 8(39.3) imip=0/18 pass=10111 acc=-1 ipm=116.4,101.6 inv=129.4,69.8
frame=896 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=65/19 raw=158/64 sel=65/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.0/37.5/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(99,94) md=32/1/94 cxcy=84.0,119.6 guide=-18.11 atg=60.0/60.0/60.0 pure=-8.61/-8.89 yaw=1087 cmd=1287 actual=549 signed=0 rps=3236/6764:3764/4399 duty=7/22 pwm=PWM2:7/PWM1:22 motor=2:7/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=65/19 centerNum=65/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=65/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.86@99,94 dx=14.6 idx=3/23 dist=32/109 right=1:-22.64@112,75 dx=28.5 idx=0/12 dist=34/52 sel=1:-20.18@103,92 dx=18.6 idx=0/16 dist=32/88 edge=1:-18.97@102.5,89.0 dx=18.5 width=64.1 l=71,83 r=134,95
CxScan: raw_ref=80.0 edge=102.5,89.0 best_raw_x=130 best_err=0.71 best_cxcy=103.2,119.7 scan=0:-42.6,10:-40.3,20:-37.8,30:-35.1,40:-32.2,50:-29.2,60:-26.0,70:-22.6,80:-19.0,90:-15.2,100:-11.4,110:-7.4,120:-3.4,130:0.7,140:4.8
ATGSeedDiag: seed=1@12,108/1@132,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(16.0) imip=44/64 pass=10100 acc=-1 ipm=152.3,55.5 inv=130.9,31.0 | 8(37.5) imip=0/18 pass=10111 acc=-1 ipm=116.7,101.5 inv=129.9,69.7
frame=897 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=65/19 raw=158/64 sel=65/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.7/38.6/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(101,94) md=33/1/95 cxcy=84.0,119.6 guide=-18.23 atg=60.0/60.0/60.0 pure=-8.69/-8.97 yaw=1094 cmd=1294 actual=578 signed=0 rps=3227/6773:3820/4595 duty=7/22 pwm=PWM2:7/PWM1:22 motor=2:7/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=65/19 centerNum=65/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=65/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.31@99,95 dx=14.9 idx=3/23 dist=33/112 right=1:-22.81@113,75 dx=28.6 idx=0/12 dist=34/52 sel=1:-20.52@103,92 dx=18.8 idx=0/16 dist=32/90 edge=1:-19.78@103.0,90.0 dx=19.0 width=63.2 l=72,84 r=134,96
CxScan: raw_ref=80.0 edge=103.0,90.0 best_raw_x=130 best_err=0.18 best_cxcy=103.2,119.7 scan=0:-43.4,10:-41.1,20:-38.6,30:-36.0,40:-33.1,50:-30.1,60:-26.8,70:-23.4,80:-19.8,90:-16.0,100:-12.1,110:-8.1,120:-4.0,130:0.2,140:4.3
ATGSeedDiag: seed=1@12,108/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.7) imip=0/20 pass=10110 acc=-1 ipm=62.9,94.3 inv=45.9,60.1 | 8(38.6) imip=0/18 pass=10111 acc=-1 ipm=116.5,101.8 inv=130.0,70.2
frame=898 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=64/19 raw=158/63 sel=64/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.6/37.1/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(101,94) md=33/1/94 cxcy=84.0,119.6 guide=-19.08 atg=60.0/60.0/60.0 pure=-8.70/-8.94 yaw=1145 cmd=1345 actual=604 signed=0 rps=3157/6843:3605/4441 duty=7/23 pwm=PWM2:7/PWM1:23 motor=2:7/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/19 centerNum=64/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.16@99,95 dx=14.8 idx=3/23 dist=33/109 right=1:-23.00@113,75 dx=28.8 idx=0/12 dist=34/52 sel=1:-20.47@103,92 dx=18.8 idx=0/16 dist=32/88 edge=1:-19.78@103.0,90.0 dx=19.0 width=63.2 l=72,84 r=134,96
CxScan: raw_ref=80.0 edge=103.0,90.0 best_raw_x=130 best_err=0.18 best_cxcy=103.2,119.7 scan=0:-43.4,10:-41.1,20:-38.6,30:-36.0,40:-33.1,50:-30.1,60:-26.8,70:-23.4,80:-19.8,90:-16.0,100:-12.1,110:-8.1,120:-4.0,130:0.2,140:4.3
ATGSeedDiag: seed=1@11,108/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(16.6) imip=0/20 pass=10110 acc=-1 ipm=62.9,94.3 inv=45.9,60.1 | 8(37.1) imip=0/18 pass=10111 acc=-1 ipm=116.7,102.1 inv=130.5,70.6
frame=899 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=64/18 raw=158/63 sel=64/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.1/38.0/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(101,94) md=33/1/94 cxcy=84.0,119.6 guide=-20.08 atg=60.0/60.0/60.0 pure=-8.70/-9.01 yaw=1205 cmd=1405 actual=618 signed=0 rps=3075/6925:3649/4555 duty=7/23 pwm=PWM2:7/PWM1:23 motor=2:7/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/18 centerNum=64/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.16@99,95 dx=14.7 idx=3/23 dist=33/110 right=1:-23.03@113,75 dx=28.7 idx=0/12 dist=34/49 sel=1:-20.45@103,93 dx=18.7 idx=0/16 dist=32/88 edge=1:-19.78@103.0,90.0 dx=19.0 width=63.2 l=72,84 r=134,96
CxScan: raw_ref=80.0 edge=103.0,90.0 best_raw_x=130 best_err=0.18 best_cxcy=103.2,119.7 scan=0:-43.4,10:-41.1,20:-38.6,30:-36.0,40:-33.1,50:-30.1,60:-26.8,70:-23.4,80:-19.8,90:-16.0,100:-12.1,110:-8.1,120:-4.0,130:0.2,140:4.3
ATGSeedDiag: seed=1@11,108/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(16.1) imip=0/20 pass=10110 acc=-1 ipm=62.9,94.4 inv=45.8,60.2 | 7(38.0) imip=0/17 pass=10111 acc=-1 ipm=114.8,103.4 inv=129.1,72.9
frame=900 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=64/18 raw=158/62 sel=64/45 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.6/37.1/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(101,94) md=33/1/93 cxcy=84.0,119.6 guide=-20.08 atg=60.0/60.0/60.0 pure=-8.78/-9.06 yaw=1205 cmd=1405 actual=627 signed=0 rps=3075/6925:3701/4505 duty=7/23 pwm=PWM2:7/PWM1:23 motor=2:7/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/18 centerNum=64/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/45 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.23@99,95 dx=14.7 idx=3/23 dist=33/109 right=1:-23.20@113,75 dx=28.9 idx=0/12 dist=34/49 sel=1:-20.74@103,93 dx=18.8 idx=0/16 dist=32/88 edge=1:-19.78@103.0,90.0 dx=19.0 width=63.2 l=72,84 r=134,96
CxScan: raw_ref=80.0 edge=103.0,90.0 best_raw_x=130 best_err=0.18 best_cxcy=103.2,119.7 scan=0:-43.4,10:-41.1,20:-38.6,30:-36.0,40:-33.1,50:-30.1,60:-26.8,70:-23.4,80:-19.8,90:-16.0,100:-12.1,110:-8.1,120:-4.0,130:0.2,140:4.3
ATGSeedDiag: seed=1@11,108/1@131,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.6) imip=0/20 pass=10110 acc=-1 ipm=62.9,94.4 inv=45.9,60.2 | 7(37.1) imip=0/17 pass=10111 acc=-1 ipm=114.9,103.5 inv=129.4,73.1
frame=902 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=63/18 raw=158/61 sel=63/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.3/36.1/0.0/0.0 dist=0 begin=0/3304 m0=(84,119) ml=(102,94) md=33/1/92 cxcy=84.0,119.6 guide=-21.17 atg=60.0/60.0/60.0 pure=-9.11/-9.17 yaw=1270 cmd=1470 actual=640 signed=0 rps=2985/7015:3802/4310 duty=6/24 pwm=PWM2:6/PWM1:24 motor=2:6/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=63/18 centerNum=63/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=63/44 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.65@99,96 dx=14.9 idx=4/23 dist=32/107 right=1:-23.89@114,76 dx=29.8 idx=0/12 dist=33/48 sel=1:-21.79@104,93 dx=19.8 idx=0/16 dist=32/86 edge=1:-20.44@103.5,90.5 dx=19.5 width=64.3 l=72,84 r=135,97
CxScan: raw_ref=80.0 edge=103.5,90.5 best_raw_x=130 best_err=-0.36 best_cxcy=103.2,119.7 scan=0:-44.0,10:-41.7,20:-39.2,30:-36.6,40:-33.7,50:-30.7,60:-27.5,70:-24.1,80:-20.4,90:-16.7,100:-12.7,110:-8.7,120:-4.5,130:-0.4,140:3.8
ATGSeedDiag: seed=1@10,108/1@131,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.3) imip=0/20 pass=10110 acc=-1 ipm=63.2,94.6 inv=46.2,60.4 | 7(36.1) imip=0/17 pass=10111 acc=-1 ipm=115.1,103.8 inv=130.1,73.6

- stopped_at: 2026-06-22T06:30:09+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive90
```
