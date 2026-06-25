# drive127

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive127-front_car_circle_drive127.log
- remote_log: /tmp/front_car_circle_drive127.log
- started_at: 2026-06-22T14:57:31+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive127 6
```

4223 /tmp/front_car_circle_drive127.log
frame=901 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/0 raw=154/0 sel=49/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,107) md=33/1/62 cxcy=84.0,119.6 guide=-41.52 atg=60.0/60.0/60.0 pure=-12.44/-12.44 yaw=2491 cmd=2430 actual=2552 signed=0 rps=0/6384:5174/7436 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/0 centerNum=49/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-34.63@108,108 dx=23.7 idx=10/26 dist=32/75 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.35@118,107 dx=34.1 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,83 r=-1,-1
ATGSeedDiag: seed=1@4,105/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(15.0) imip=0/11 pass=10110 acc=-1 ipm=53.1,113.3 inv=11.4,96.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=902 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/0 raw=154/0 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,107) md=33/1/65 cxcy=84.0,119.6 guide=-41.20 atg=60.0/60.0/60.0 pure=-12.30/-12.30 yaw=2472 cmd=2376 actual=2568 signed=0 rps=0/6325:5346/7893 duty=0/15 pwm=PWM2:0/PWM1:15 motor=2:0/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/0 centerNum=49/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-35.86@109,108 dx=25.2 idx=10/27 dist=33/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.11@118,106 dx=34.0 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,83 r=-1,-1
ATGSeedDiag: seed=1@4,105/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(13.9) imip=0/11 pass=10110 acc=-1 ipm=53.2,113.3 inv=11.5,96.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=903 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/0 raw=153/0 sel=49/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,107) md=33/1/62 cxcy=84.0,119.6 guide=-41.36 atg=60.0/60.0/60.0 pure=-12.44/-12.44 yaw=2482 cmd=2376 actual=2587 signed=0 rps=0/6318:5175/7929 duty=0/15 pwm=PWM2:0/PWM1:15 motor=2:0/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/0 centerNum=49/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.00@109,108 dx=25.4 idx=10/27 dist=33/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.26@118,107 dx=34.1 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,83 r=-1,-1
ATGSeedDiag: seed=1@4,105/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(11.5) imip=32/48 pass=10110 acc=-1 ipm=138.0,79.8 inv=135.5,45.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=904 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,107) md=32/1/62 cxcy=84.0,119.6 guide=-43.17 atg=60.0/60.0/60.0 pure=-12.52/-12.52 yaw=2590 cmd=2593 actual=2587 signed=0 rps=0/6530:4812/7382 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.26@109,108 dx=25.1 idx=10/27 dist=33/73 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.63@118,107 dx=34.3 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,83 r=-1,-1
ATGSeedDiag: seed=1@4,105/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(12.9) imip=36/47 pass=10100 acc=-1 ipm=147.4,82.6 inv=149.2,47.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=905 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=32/1/62 cxcy=84.0,119.6 guide=-43.44 atg=60.0/60.0/60.0 pure=-12.65/-12.65 yaw=2607 cmd=2635 actual=2578 signed=0 rps=0/6575:4766/7231 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.66@109,109 dx=25.4 idx=10/27 dist=32/71 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.04@118,107 dx=34.5 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,83 r=-1,-1
ATGSeedDiag: seed=1@4,106/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.9) imip=0/20 pass=10110 acc=-1 ipm=68.1,98.7 inv=51.7,66.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=906 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=32/1/62 cxcy=84.0,119.6 guide=-43.59 atg=60.0/60.0/60.0 pure=-12.64/-12.64 yaw=2615 cmd=2668 actual=2562 signed=0 rps=0/6614:4962/7598 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.71@109,109 dx=25.4 idx=10/27 dist=32/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.06@119,107 dx=34.5 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,84 r=-1,-1
ATGSeedDiag: seed=1@4,106/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.3) imip=0/20 pass=10110 acc=-1 ipm=68.2,98.9 inv=51.8,66.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=908 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=154/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,107) md=32/1/62 cxcy=84.0,119.6 guide=-43.31 atg=60.0/60.0/60.0 pure=-12.50/-12.50 yaw=2599 cmd=2657 actual=2541 signed=0 rps=0/6611:4597/7095 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.55@109,109 dx=25.3 idx=10/27 dist=32/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.80@118,107 dx=34.5 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,83 r=-1,-1
ATGSeedDiag: seed=1@4,107/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.0) imip=0/20 pass=10110 acc=-1 ipm=68.2,99.0 inv=51.8,66.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=909 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/0 raw=153/0 sel=49/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.2/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,107) md=33/1/63 cxcy=84.0,119.6 guide=-42.37 atg=60.0/60.0/60.0 pure=-12.50/-12.50 yaw=2542 cmd=2551 actual=2534 signed=0 rps=0/6510:4724/7210 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/0 centerNum=49/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-37.06@110,108 dx=25.9 idx=10/27 dist=33/73 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.79@118,107 dx=34.5 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,83 r=-1,-1
ATGSeedDiag: seed=1@4,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=39(11.2) imip=29/48 pass=10110 acc=-1 ipm=131.6,79.7 inv=128.3,45.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=910 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=154/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/63 cxcy=84.0,119.6 guide=-42.71 atg=60.0/60.0/60.0 pure=-12.46/-12.46 yaw=2563 cmd=2595 actual=2531 signed=0 rps=0/6554:4587/7036 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.82@110,109 dx=25.6 idx=10/27 dist=33/73 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.93@119,107 dx=34.5 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,84 r=-1,-1
ATGSeedDiag: seed=1@4,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(12.9) imip=0/11 pass=10110 acc=-1 ipm=53.9,114.2 inv=11.6,99.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=911 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/63 cxcy=84.0,119.6 guide=-42.71 atg=60.0/60.0/60.0 pure=-12.46/-12.46 yaw=2563 cmd=2592 actual=2534 signed=0 rps=0/6549:4933/7638 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.99@110,109 dx=25.7 idx=10/27 dist=32/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-43.95@119,107 dx=34.5 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,84 r=-1,-1
ATGSeedDiag: seed=1@4,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(11.7) imip=36/47 pass=10100 acc=-1 ipm=147.8,82.5 inv=149.4,47.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=152/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/63 cxcy=84.0,119.6 guide=-41.95 atg=60.0/60.0/60.0 pure=-12.55/-12.55 yaw=2517 cmd=2487 actual=2547 signed=0 rps=0/6442:4908/7481 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-37.54@110,109 dx=26.2 idx=10/27 dist=33/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.36@119,107 dx=34.6 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,84 r=-1,-1
ATGSeedDiag: seed=1@5,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.8) imip=0/20 pass=10110 acc=-1 ipm=68.9,99.2 inv=52.8,66.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=913 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=152/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=8.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/63 cxcy=84.0,119.6 guide=-42.22 atg=60.0/60.0/60.0 pure=-12.56/-12.56 yaw=2533 cmd=2505 actual=2562 signed=0 rps=0/6454:5170/7845 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.40@112,109 dx=28.1 idx=10/28 dist=33/70 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.75@119,108 dx=34.8 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,84 r=-1,-1
ATGSeedDiag: seed=1@5,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=41(8.8) imip=31/47 pass=10110 acc=-1 ipm=136.9,81.0 inv=135.4,46.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=914 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=152/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/63 cxcy=84.0,119.6 guide=-42.22 atg=60.0/60.0/60.0 pure=-12.60/-12.60 yaw=2533 cmd=2508 actual=2559 signed=0 rps=0/6458:5271/8058 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.15@111,109 dx=26.5 idx=10/27 dist=32/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.92@119,108 dx=34.8 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,84 r=-1,-1
ATGSeedDiag: seed=1@5,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.5) imip=0/20 pass=10110 acc=-1 ipm=69.2,99.5 inv=53.1,67.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=916 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=152/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.2/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/63 cxcy=84.0,119.6 guide=-42.22 atg=60.0/60.0/60.0 pure=-12.56/-12.56 yaw=2533 cmd=2497 actual=2569 signed=0 rps=0/6444:5217/7514 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-37.97@111,109 dx=26.5 idx=9/27 dist=33/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.66@119,108 dx=34.6 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,84 r=-1,-1
ATGSeedDiag: seed=1@6,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(10.2) imip=0/11 pass=10110 acc=-1 ipm=54.8,114.3 inv=13.5,99.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=152/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=33/1/63 cxcy=84.0,119.6 guide=-42.22 atg=60.0/60.0/60.0 pure=-12.56/-12.56 yaw=2533 cmd=2481 actual=2585 signed=0 rps=0/6422:4974/7068 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.72@109,109 dx=25.0 idx=9/26 dist=32/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.65@119,108 dx=34.6 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,84 r=-1,-1
ATGSeedDiag: seed=1@6,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.5) imip=0/20 pass=10110 acc=-1 ipm=69.4,99.4 inv=53.5,67.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=918 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=151/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(116,108) md=32/1/62 cxcy=84.0,119.6 guide=-43.86 atg=60.0/60.0/60.0 pure=-12.56/-12.56 yaw=2632 cmd=2672 actual=2592 signed=0 rps=0/6606:5050/7456 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-37.02@109,109 dx=25.2 idx=9/26 dist=32/73 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.67@119,108 dx=34.6 idx=0/16 dist=32/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,84 r=-1,-1
ATGSeedDiag: seed=1@6,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(10.3) imip=0/19 pass=10110 acc=-1 ipm=67.7,100.8 inv=50.2,69.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T14:57:46+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive127
```
