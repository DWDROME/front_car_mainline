# drive147

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive147-front_car_circle_drive147.log
- remote_log: /tmp/front_car_circle_drive147.log
- started_at: 2026-06-22T15:21:01+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive147 6
```

4832 /tmp/front_car_circle_drive147.log
CxScan: raw_ref=80.0 edge=77.5,117.0 best_raw_x=65 best_err=1.72 best_cxcy=78.3,119.5 scan=0:-43.5,10:-38.5,20:-32.8,30:-26.3,40:-19.0,50:-11.0,60:-2.6,70:6.0,80:14.2,90:21.9,100:28.8,110:34.9,120:40.2,130:44.7,140:48.7
ATGSeedDiag: seed=1@73,108/1@87,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(175.2) imip=0/5 pass=11010 acc=-1 ipm=78.4,116.9 inv=65.9,107.4 | 10(171.4) imip=0/17 pass=11011 acc=-1 ipm=65.1,119.0 inv=31.3,115.9
frame=939 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/2 raw=170/170 sel=14/24 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=159.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(109,119) md=33/0/33 cxcy=84.0,119.6 guide=-43.20 atg=60.0/60.0/60.0 pure=-25.32/-25.32 yaw=3888 cmd=4088 actual=-1 signed=0 rps=0/7147:204/1871 duty=0/26 pwm=PWM2:0/PWM1:26 motor=2:0/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=14/2 centerNum=14/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=14/24 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-90.16@87,143 dx=3.3 idx=0/3 dist=32/53 right=1:-9.28@92,91 dx=8.4 idx=0/1 dist=2/2 sel=1:-86.47@94,142 dx=9.9 idx=0/16 dist=32/46 edge=1:-34.58@103.5,114.5 dx=19.5 width=4.2 l=105,113 r=102,116
CxScan: raw_ref=80.0 edge=103.5,114.5 best_raw_x=130 best_err=-0.66 best_cxcy=103.2,119.7 scan=0:-60.8,10:-58.8,20:-56.6,30:-54.0,40:-51.1,50:-47.7,60:-43.9,70:-39.5,80:-34.6,90:-28.9,100:-22.6,110:-15.7,120:-8.3,130:-0.7,140:7.0
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(159.9) imip=0/11 pass=11010 acc=-1 ipm=78.4,116.9 inv=65.9,107.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=940 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=24/2 raw=170/170 sel=24/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(112,113) md=32/1/69 cxcy=84.0,119.6 guide=-41.01 atg=60.0/0.0/0.0 pure=-12.17/-0.16 yaw=3690 cmd=3890 actual=-8 signed=0 rps=0/7051:238/1085 duty=0/27 pwm=PWM2:0/PWM1:27 motor=2:0/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=24/2 centerNum=24/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=24/42 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-80.35@95,141 dx=11.4 idx=19/20 dist=24/97 right=1:-9.45@93,91 dx=8.6 idx=0/1 dist=2/2 sel=1:-53.45@104,128 dx=19.9 idx=0/17 dist=33/81 edge=1:-17.89@92.5,116.5 dx=8.5 width=19.0 l=83,117 r=102,116
CxScan: raw_ref=80.0 edge=92.5,116.5 best_raw_x=100 best_err=-1.77 best_cxcy=91.7,119.6 scan=0:-56.4,10:-53.6,20:-50.4,30:-46.7,40:-42.3,50:-37.4,60:-31.6,70:-25.1,80:-17.9,90:-10.0,100:-1.8,110:6.5,120:14.6,130:22.0,140:28.7
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(90.8) imip=7/23 pass=11110 acc=-1 ipm=78.3,116.9 inv=65.6,107.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=941 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=21/2 raw=170/170 sel=21/26 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(78,91) md=32/1/56 cxcy=84.0,119.6 guide=7.44 atg=-60.0/-60.0/-60.0 pure=13.82/13.82 yaw=-669 cmd=-869 actual=-19 signed=0 rps=5596/3214:149/832 duty=19/12 pwm=PWM2:19/PWM1:12 motor=2:19/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=21/2 centerNum=21/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/26 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.14@78,91 dx=-5.6 idx=17/19 dist=32/59 right=1:-8.63@92,92 dx=7.8 idx=0/1 dist=2/2 sel=1:10.46@75,94 dx=-9.0 idx=0/16 dist=32/50 edge=1:-17.58@92.5,116.0 dx=8.5 width=19.0 l=83,116 r=102,116
CxScan: raw_ref=80.0 edge=92.5,116.0 best_raw_x=100 best_err=-1.73 best_cxcy=91.7,119.6 scan=0:-55.9,10:-53.1,20:-49.9,30:-46.1,40:-41.8,50:-36.8,60:-31.2,70:-24.7,80:-17.6,90:-9.8,100:-1.7,110:6.4,120:14.3,130:21.6,140:28.3
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(94.3) imip=0/15 pass=11110 acc=-1 ipm=87.6,116.3 inv=87.6,105.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=942 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=25/2 raw=170/170 sel=25/149 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=177.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(73,95) md=32/1/272 cxcy=84.0,119.6 guide=11.64 atg=-60.0/-60.0/60.0 pure=12.88/33.66 yaw=-1048 cmd=-1248 actual=-25 signed=0 rps=5779/2359:156/999 duty=20/8 pwm=PWM2:20/PWM1:8 motor=2:20/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=25/2 centerNum=25/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=25/149 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:21.54@66,98 dx=-17.6 idx=5/6 dist=28/350 right=1:-9.45@93,91 dx=8.6 idx=0/1 dist=2/2 sel=1:10.88@75,93 dx=-9.5 idx=0/16 dist=32/295 edge=1:-17.89@92.5,116.5 dx=8.5 width=19.0 l=83,117 r=102,116
CxScan: raw_ref=80.0 edge=92.5,116.5 best_raw_x=100 best_err=-1.77 best_cxcy=91.7,119.6 scan=0:-56.4,10:-53.6,20:-50.4,30:-46.7,40:-42.3,50:-37.4,60:-31.6,70:-25.1,80:-17.9,90:-10.0,100:-1.8,110:6.5,120:14.6,130:22.0,140:28.7
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(177.0) imip=0/15 pass=11010 acc=-1 ipm=87.6,116.3 inv=87.6,105.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=943 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/2 raw=170/170 sel=11/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=176.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(101,119) md=25/0/25 cxcy=84.0,119.6 guide=-35.65 atg=60.0/60.0/60.0 pure=-29.24/-29.24 yaw=3208 cmd=3408 actual=-23 signed=0 rps=0/6819:383/957 duty=0/26 pwm=PWM2:0/PWM1:26 motor=2:0/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/2 centerNum=11/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-87.60@89,143 dx=5.1 idx=0/5 dist=32/42 right=1:-9.45@93,91 dx=8.6 idx=0/1 dist=2/2 sel=1:-86.79@94,142 dx=9.7 idx=0/16 dist=32/38 edge=1:-31.15@100.5,115.5 dx=16.5 width=3.2 l=99,115 r=102,116
CxScan: raw_ref=80.0 edge=100.5,115.5 best_raw_x=125 best_err=1.59 best_cxcy=101.3,119.7 scan=0:-60.2,10:-58.0,20:-55.6,30:-52.8,40:-49.5,50:-45.8,60:-41.6,70:-36.7,80:-31.2,90:-24.9,100:-17.9,110:-10.3,120:-2.4,130:5.6,140:13.3
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(176.9) imip=0/10 pass=11010 acc=-1 ipm=78.4,116.9 inv=65.9,107.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=944 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/7 raw=170/170 sel=7/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=19.9/158.3/0.0/0.0 dist=0 begin=0/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-29.24/-29.24 yaw=0 cmd=0 actual=-87 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/7 centerNum=4/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-85.88@88,142 dx=4.3 idx=0/3 dist=6/6 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=88,116 r=-1,-1
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(19.9) imip=0/3 pass=10110 acc=-1 ipm=83.0,117.0 inv=76.9,107.8 | 1(158.3) imip=0/6 pass=11011 acc=-1 ipm=101.9,115.6 inv=120.1,102.3
frame=945 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=24/2 raw=170/170 sel=24/148 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.6/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(77,93) md=34/1/269 cxcy=84.0,119.6 guide=8.21 atg=-60.0/-14.0/60.0 pure=14.91/36.68 yaw=-739 cmd=-939 actual=-17 signed=0 rps=5630/3056:183/549 duty=19/12 pwm=PWM2:19/PWM1:12 motor=2:19/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=24/2 centerNum=24/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=24/148 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:12.86@73,93 dx=-11.3 idx=5/6 dist=29/346 right=1:-8.48@92,92 dx=7.6 idx=0/1 dist=2/2 sel=1:7.88@77,93 dx=-6.9 idx=0/17 dist=32/292 edge=1:-17.89@92.5,116.5 dx=8.5 width=19.0 l=83,117 r=102,116
CxScan: raw_ref=80.0 edge=92.5,116.5 best_raw_x=100 best_err=-1.77 best_cxcy=91.7,119.6 scan=0:-56.4,10:-53.6,20:-50.4,30:-46.7,40:-42.3,50:-37.4,60:-31.6,70:-25.1,80:-17.9,90:-10.0,100:-1.8,110:6.5,120:14.6,130:22.0,140:28.7
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(90.6) imip=7/23 pass=11110 acc=-1 ipm=78.3,116.9 inv=65.6,107.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=946 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=22/2 raw=170/170 sel=22/111 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(77,108) md=32/1/151 cxcy=84.0,119.6 guide=11.66 atg=-30.0/-32.0/-35.0 pure=6.19/10.02 yaw=-1049 cmd=-1249 actual=-16 signed=0 rps=5779/2355:198/336 duty=20/9 pwm=PWM2:20/PWM1:9 motor=2:20/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=22/2 centerNum=22/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/111 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:30.39@84,142 dx=-0.3 idx=6/10 dist=34/262 right=1:-9.45@93,91 dx=8.6 idx=0/1 dist=2/2 sel=1:-88.66@89,143 dx=4.7 idx=0/16 dist=32/218 edge=1:-17.58@92.5,116.0 dx=8.5 width=19.0 l=83,116 r=102,116
CxScan: raw_ref=80.0 edge=92.5,116.0 best_raw_x=100 best_err=-1.73 best_cxcy=91.7,119.6 scan=0:-55.9,10:-53.1,20:-49.9,30:-46.1,40:-41.8,50:-36.8,60:-31.2,70:-24.7,80:-17.6,90:-9.8,100:-1.7,110:6.4,120:14.3,130:21.6,140:28.3
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(90.0) imip=0/15 pass=11110 acc=-1 ipm=87.6,116.3 inv=87.6,105.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=947 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/2 raw=170/170 sel=12/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=175.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(103,119) md=27/0/27 cxcy=84.0,119.6 guide=-38.72 atg=60.0/60.0/60.0 pure=-28.16/-28.16 yaw=3485 cmd=3685 actual=-23 signed=0 rps=0/6952:343/141 duty=0/28 pwm=PWM2:0/PWM1:28 motor=2:0/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=12/2 centerNum=12/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-88.24@89,143 dx=5.2 idx=0/5 dist=32/45 right=1:-8.63@92,92 dx=7.8 idx=0/1 dist=2/2 sel=1:-86.44@94,142 dx=9.8 idx=0/16 dist=32/40 edge=1:-32.67@101.5,115.5 dx=17.5 width=1.4 l=101,115 r=102,116
CxScan: raw_ref=80.0 edge=101.5,115.5 best_raw_x=125 best_err=-0.51 best_cxcy=101.3,119.7 scan=0:-60.7,10:-58.6,20:-56.2,30:-53.5,40:-50.4,50:-46.9,60:-42.8,70:-38.0,80:-32.7,90:-26.6,100:-19.8,110:-12.3,120:-4.5,130:3.5,140:11.3
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(175.9) imip=0/11 pass=11010 acc=-1 ipm=78.4,116.9 inv=65.9,107.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=948 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/2 raw=170/170 sel=17/26 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=173.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,119) md=33/0/36 cxcy=84.0,119.6 guide=-42.44 atg=60.0/60.0/60.0 pure=-27.49/-27.49 yaw=3820 cmd=4020 actual=-45 signed=0 rps=0/7114:233/131 duty=0/28 pwm=PWM2:0/PWM1:28 motor=2:0/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/2 centerNum=17/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=17/26 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-87.02@89,143 dx=4.6 idx=0/3 dist=33/57 right=1:-8.63@92,92 dx=7.8 idx=0/1 dist=2/2 sel=1:-86.86@94,142 dx=9.7 idx=0/16 dist=32/50 edge=1:-30.37@100.0,115.5 dx=16.0 width=4.1 l=98,115 r=102,116
CxScan: raw_ref=80.0 edge=100.0,115.5 best_raw_x=120 best_err=-1.37 best_cxcy=99.3,119.7 scan=0:-59.9,10:-57.7,20:-55.2,30:-52.4,40:-49.1,50:-45.3,60:-41.0,70:-36.0,80:-30.4,90:-24.0,100:-16.9,110:-9.3,120:-1.4,130:6.6,140:14.3
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=14(173.7) imip=4/16 pass=11010 acc=-1 ipm=102.5,113.7 inv=118.9,96.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=949 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/2 raw=170/170 sel=17/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=179.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,111) md=33/1/66 cxcy=84.0,119.6 guide=-37.95 atg=60.0/0.0/0.0 pure=-13.40/-0.09 yaw=3416 cmd=3616 actual=-16 signed=0 rps=0/6919:103/730 duty=0/27 pwm=PWM2:0/PWM1:27 motor=2:0/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/2 centerNum=17/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=17/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-81.42@96,141 dx=12.4 idx=10/13 dist=30/100 right=1:-8.42@92,92 dx=7.6 idx=0/1 dist=2/2 sel=1:-61.98@100,134 dx=16.1 idx=0/16 dist=32/84 edge=1:-19.50@93.5,116.0 dx=9.5 width=17.0 l=85,116 r=102,116
CxScan: raw_ref=80.0 edge=93.5,116.0 best_raw_x=105 best_err=0.22 best_cxcy=93.6,119.6 scan=0:-56.6,10:-53.9,20:-50.7,30:-47.1,40:-43.0,50:-38.2,60:-32.7,70:-26.5,80:-19.5,90:-11.9,100:-3.9,110:4.3,120:12.3,130:19.8,140:26.6
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(179.8) imip=0/16 pass=11010 acc=-1 ipm=85.3,116.2 inv=82.1,104.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=950 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=13/2 raw=170/170 sel=13/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=175.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(105,119) md=29/0/29 cxcy=84.0,119.6 guide=-40.16 atg=60.0/60.0/60.0 pure=-27.13/-27.13 yaw=3615 cmd=3815 actual=-5 signed=0 rps=0/7015:6/1769 duty=0/26 pwm=PWM2:0/PWM1:26 motor=2:0/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=13/2 centerNum=13/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=13/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-87.34@89,143 dx=5.4 idx=0/5 dist=32/47 right=1:-8.26@91,92 dx=7.4 idx=0/1 dist=2/2 sel=1:-86.84@94,142 dx=9.9 idx=0/16 dist=32/42 edge=1:-34.84@103.0,115.5 dx=19.0 width=2.2 l=104,115 r=102,116
CxScan: raw_ref=80.0 edge=103.0,115.5 best_raw_x=130 best_err=0.36 best_cxcy=103.2,119.7 scan=0:-61.5,10:-59.5,20:-57.2,30:-54.6,40:-51.7,50:-48.3,60:-44.4,70:-40.0,80:-34.8,90:-29.0,100:-22.5,110:-15.3,120:-7.6,130:0.4,140:8.3
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(175.9) imip=0/11 pass=11010 acc=-1 ipm=78.4,116.9 inv=65.9,107.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=951 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=24/2 raw=170/170 sel=24/147 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(77,92) md=32/1/272 cxcy=84.0,119.6 guide=9.43 atg=-60.0/29.0/60.0 pure=16.27/-36.31 yaw=-849 cmd=-1049 actual=12 signed=0 rps=5683/2809:-51/2593 duty=20/8 pwm=PWM2:20/PWM1:8 motor=2:20/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=24/2 centerNum=24/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=24/147 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.23@79,91 dx=-4.8 idx=5/7 dist=33/341 right=1:-9.45@93,91 dx=8.6 idx=0/1 dist=2/2 sel=1:9.62@76,94 dx=-8.3 idx=0/16 dist=32/292 edge=1:-17.89@92.5,116.5 dx=8.5 width=19.0 l=83,117 r=102,116
CxScan: raw_ref=80.0 edge=92.5,116.5 best_raw_x=100 best_err=-1.77 best_cxcy=91.7,119.6 scan=0:-56.4,10:-53.6,20:-50.4,30:-46.7,40:-42.3,50:-37.4,60:-31.6,70:-25.1,80:-17.9,90:-10.0,100:-1.8,110:6.5,120:14.6,130:22.0,140:28.7
ATGSeedDiag: seed=1@73,108/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(91.3) imip=7/23 pass=11110 acc=-1 ipm=78.3,116.9 inv=65.6,107.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T15:21:14+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive147
```
