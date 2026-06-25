# drive101

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive101-front_car_circle_drive101.log
- remote_log: /tmp/front_car_circle_drive101.log
- started_at: 2026-06-22T06:49:58+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive101 6
```

2753 /tmp/front_car_circle_drive101.log
frame=571 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=4/1 raw=21/170 sel=4/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(84,119) ml=(66,94) md=31/0/31 cxcy=84.0,119.6 guide=18.00 atg=-60.0/-52.0/-52.0 pure=7.32/7.32 yaw=-1080 cmd=-1280 actual=66 signed=0 rps=6754/3246:1256/1748 duty=22/11 pwm=PWM2:22/PWM1:11 motor=2:22/1:11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/1 centerNum=4/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:18.20@68,93 dx=-16.2 idx=0/2 dist=32/34 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:20.75@66,94 dx=-18.4 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=74,119 r=-1,-1
ATGSeedDiag: seed=1@73,108/1@103,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(2.0) imip=0/3 pass=10110 acc=-1 ipm=76.3,118.1 inv=60.4,112.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=572 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-52.0/-52.0 pure=7.32/7.32 yaw=0 cmd=0 actual=382 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@15,107/1@130,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=573 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-52.0/-52.0 pure=7.32/7.32 yaw=0 cmd=0 actual=123 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@40,98/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=576 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-52.0/-52.0 pure=7.32/7.32 yaw=0 cmd=0 actual=149 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@39,100/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=577 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/12 raw=170/70 sel=12/24 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/14.0/0.0/0.0 dist=0 begin=0/2014 m0=(84,119) ml=(97,90) md=32/1/51 cxcy=84.0,119.6 guide=-15.46 atg=60.0/60.0/60.0 pure=-9.58/-9.58 yaw=928 cmd=1128 actual=93 signed=0 rps=3455/6545:1221/1465 duty=11/24 pwm=PWM2:11/PWM1:24 motor=2:11/1:24
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/12 centerNum=1/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/24 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-12.17@95,90 dx=11.4 idx=0/2 dist=33/52 sel=1:-16.73@100,90 dx=15.8 idx=0/16 dist=32/46 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,119
ATGSeedDiag: seed=1@39,100/1@87,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 3(14.0) imip=0/11 pass=10111 acc=-1 ipm=94.9,116.0 inv=104.5,104.0
frame=578 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/12 raw=170/70 sel=12/24 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/11.9/0.0/0.0 dist=0 begin=0/2014 m0=(84,119) ml=(98,90) md=33/1/51 cxcy=84.0,119.6 guide=-14.56 atg=60.0/60.0/60.0 pure=-9.66/-9.66 yaw=874 cmd=1074 actual=84 signed=0 rps=3529/6471:1297/1572 duty=11/24 pwm=PWM2:11/PWM1:24 motor=2:11/1:24
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/12 centerNum=1/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/24 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-12.39@96,90 dx=11.5 idx=0/2 dist=32/51 sel=1:-17.03@100,90 dx=16.0 idx=0/16 dist=32/46 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,119
ATGSeedDiag: seed=1@38,101/1@87,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 4(11.9) imip=0/11 pass=10111 acc=-1 ipm=97.3,116.4 inv=110.3,105.1
frame=579 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/12 raw=170/70 sel=12/24 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/12.0/0.0/0.0 dist=0 begin=0/2014 m0=(84,119) ml=(98,90) md=33/1/51 cxcy=84.0,119.6 guide=-14.67 atg=60.0/60.0/60.0 pure=-9.68/-9.68 yaw=880 cmd=1080 actual=140 signed=0 rps=3520/6480:1286/1654 duty=11/24 pwm=PWM2:11/PWM1:24 motor=2:11/1:24
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/12 centerNum=1/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/24 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-12.34@95,90 dx=11.4 idx=0/2 dist=32/51 sel=1:-17.08@100,91 dx=16.0 idx=0/16 dist=32/46 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,119
ATGSeedDiag: seed=1@38,102/1@87,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 3(12.0) imip=0/11 pass=10111 acc=-1 ipm=94.9,116.4 inv=104.8,105.2
frame=580 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/11 raw=170/67 sel=11/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/10.2/0.0/0.0 dist=0 begin=0/2014 m0=(84,119) ml=(98,91) md=32/1/48 cxcy=84.0,119.6 guide=-16.67 atg=60.0/60.0/60.0 pure=-9.43/-9.43 yaw=1000 cmd=1200 actual=176 signed=0 rps=3355/6645:1391/1758 duty=10/24 pwm=PWM2:10/PWM1:24 motor=2:10/1:24
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/11 centerNum=1/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-13.19@96,91 dx=12.2 idx=0/2 dist=32/48 sel=1:-17.83@101,91 dx=16.7 idx=0/16 dist=32/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,119
ATGSeedDiag: seed=1@38,102/1@89,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 9(10.2) imip=0/10 pass=10111 acc=-1 ipm=109.5,118.5 inv=143.7,112.6
frame=581 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/10 raw=170/61 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/8.2/0.0/0.0 dist=0 begin=0/2014 m0=(84,119) ml=(100,91) md=32/1/46 cxcy=84.0,119.6 guide=-18.47 atg=60.0/60.0/60.0 pure=-9.30/-9.30 yaw=1108 cmd=1308 actual=199 signed=0 rps=3207/6793:1458/1825 duty=9/25 pwm=PWM2:9/PWM1:25 motor=2:9/1:25
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/10 centerNum=1/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-15.23@98,91 dx=14.1 idx=0/2 dist=33/47 sel=1:-19.44@102,91 dx=18.2 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=111,119
ATGSeedDiag: seed=1@37,103/1@93,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 5(8.2) imip=0/9 pass=10111 acc=-1 ipm=102.1,117.3 inv=123.0,108.2
frame=582 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/9 raw=170/55 sel=9/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/7.3/0.0/0.0 dist=0 begin=0/2014 m0=(84,119) ml=(104,91) md=34/1/43 cxcy=84.0,119.6 guide=-20.08 atg=60.0/60.0/60.0 pure=-9.18/-9.18 yaw=1205 cmd=1405 actual=223 signed=0 rps=3075/6925:1434/1713 duty=9/26 pwm=PWM2:9/PWM1:26 motor=2:9/1:26
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/9 centerNum=1/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-15.58@98,91 dx=14.4 idx=0/1 dist=32/46 sel=1:-21.06@104,91 dx=19.8 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=111,119
ATGSeedDiag: seed=1@37,104/1@98,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 7(7.3) imip=0/8 pass=10111 acc=-1 ipm=108.7,118.6 inv=141.9,113.1
frame=583 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/1 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-9.18/-9.18 yaw=0 cmd=0 actual=399 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@37,104/1@98,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=584 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-9.18/-9.18 yaw=0 cmd=0 actual=396 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=585 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/1 raw=170/3 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-9.18/-9.18 yaw=0 cmd=0 actual=257 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@36,106/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=586 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/1 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-9.18/-9.18 yaw=0 cmd=0 actual=294 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@36,106/1@98,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=587 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-9.18/-9.18 yaw=0 cmd=0 actual=341 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@35,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=589 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2014 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-9.18/-9.18 yaw=0 cmd=0 actual=400 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T06:50:11+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive101
```
