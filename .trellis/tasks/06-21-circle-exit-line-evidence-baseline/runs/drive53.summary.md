# drive53

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive53-front_car_circle_drive53.log
- remote_log: /tmp/front_car_circle_drive53.log
- started_at: 2026-06-22T03:28:36+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive53 6
```

4177 /tmp/front_car_circle_drive53.log
frame=867 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=143/0 sel=46/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.2/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,110) md=33/1/65 cxcy=84.0,119.6 guide=-43.85 atg=60.0/60.0/60.0 pure=-12.41/-12.41 yaw=2631 cmd=2466 actual=2797 signed=0 rps=1621/8379:5543/8753 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.13@110,111 dx=25.9 idx=8/24 dist=33/75 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.29@118,109 dx=34.0 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=98,87 r=-1,-1
ATGSeedDiag: seed=1@15,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(11.2) imip=0/17 pass=10110 acc=-1 ipm=67.9,103.7 inv=49.3,74.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=868 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=145/0 sel=46/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.9/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,110) md=32/1/64 cxcy=84.0,119.6 guide=-44.83 atg=60.0/60.0/60.0 pure=-12.54/-12.54 yaw=2690 cmd=2536 actual=2844 signed=0 rps=1525/8475:5594/9336 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.47@110,111 dx=26.0 idx=8/24 dist=32/73 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.48@118,110 dx=33.8 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=105,86 r=-1,-1
ATGSeedDiag: seed=1@15,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(11.9) imip=0/17 pass=10110 acc=-1 ipm=67.9,104.0 inv=49.2,74.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=870 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=143/0 sel=46/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.0/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,110) md=32/1/63 cxcy=84.0,119.6 guide=-44.98 atg=60.0/60.0/60.0 pure=-12.58/-12.58 yaw=2699 cmd=2525 actual=2872 signed=0 rps=1539/8461:5108/8802 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.32@108,112 dx=24.4 idx=8/23 dist=32/75 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.76@118,110 dx=33.8 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,86 r=-1,-1
ATGSeedDiag: seed=1@16,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(11.0) imip=0/15 pass=10110 acc=-1 ipm=65.0,107.2 inv=42.1,81.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=872 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=142/0 sel=46/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.2/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,110) md=32/1/66 cxcy=84.0,119.6 guide=-44.98 atg=60.0/60.0/60.0 pure=-12.39/-12.18 yaw=2699 cmd=2499 actual=2936 signed=0 rps=1576/8424:4045/6897 duty=0/25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-40.28@111,111 dx=27.0 idx=8/24 dist=33/75 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.52@118,109 dx=34.1 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,86 r=-1,-1
ATGSeedDiag: seed=1@18,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.2) imip=0/20 pass=10110 acc=-1 ipm=74.7,99.7 inv=61.9,67.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=873 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=141/0 sel=46/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.8/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,110) md=32/1/66 cxcy=84.0,119.6 guide=-44.83 atg=60.0/60.0/60.0 pure=-12.27/-12.19 yaw=2690 cmd=2490 actual=2966 signed=0 rps=1587/8413:4540/7813 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.24@110,111 dx=25.7 idx=8/23 dist=32/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.53@118,109 dx=34.1 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,86 r=-1,-1
ATGSeedDiag: seed=1@19,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(15.8) imip=34/45 pass=10110 acc=-1 ipm=150.0,82.6 inv=152.1,47.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=874 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=140/0 sel=46/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.2/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,110) md=32/1/66 cxcy=84.0,119.6 guide=-44.83 atg=60.0/60.0/60.0 pure=-12.25/-12.13 yaw=2690 cmd=2490 actual=2976 signed=0 rps=1587/8413:4725/8287 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.46@110,111 dx=26.0 idx=8/23 dist=33/76 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.37@118,109 dx=34.1 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,86 r=-1,-1
ATGSeedDiag: seed=1@20,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(10.2) imip=0/12 pass=10110 acc=-1 ipm=61.9,112.3 inv=31.6,93.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=875 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=138/0 sel=46/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.7/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(115,110) md=32/1/66 cxcy=84.0,119.6 guide=-44.25 atg=60.0/60.0/60.0 pure=-12.32/-12.18 yaw=2655 cmd=2455 actual=2983 signed=0 rps=1636/8364:5811/10400 duty=0/20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.34@109,112 dx=24.7 idx=7/22 dist=33/78 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.88@117,109 dx=33.3 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=100,87 r=-1,-1
ATGSeedDiag: seed=1@21,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(12.7) imip=34/45 pass=10110 acc=-1 ipm=150.6,82.4 inv=152.6,47.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=876 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=45/0 raw=138/0 sel=45/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.2/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(115,110) md=32/1/66 cxcy=84.0,119.6 guide=-44.54 atg=60.0/60.0/60.0 pure=-12.33/-12.18 yaw=2672 cmd=2472 actual=2982 signed=0 rps=1612/8388:4520/8252 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/0 centerNum=45/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.71@109,112 dx=24.8 idx=7/22 dist=33/76 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.97@117,110 dx=33.2 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=100,87 r=-1,-1
ATGSeedDiag: seed=1@20,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=39(9.2) imip=29/44 pass=10110 acc=-1 ipm=139.2,81.0 inv=138.0,46.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=877 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=45/0 raw=137/0 sel=45/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.9/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,110) md=33/1/65 cxcy=84.0,119.6 guide=-44.20 atg=60.0/60.0/60.0 pure=-12.37/-12.37 yaw=2652 cmd=2452 actual=2982 signed=0 rps=1639/8361:5006/8826 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/0 centerNum=45/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.00@109,112 dx=25.0 idx=8/22 dist=32/76 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.77@118,110 dx=34.0 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=103,87 r=-1,-1
ATGSeedDiag: seed=1@20,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(7.9) imip=32/44 pass=10110 acc=-1 ipm=146.4,82.4 inv=147.7,47.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=878 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=45/0 raw=137/0 sel=45/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.5/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(117,110) md=33/1/66 cxcy=84.0,119.6 guide=-44.68 atg=60.0/60.0/60.0 pure=-12.45/-12.26 yaw=2681 cmd=2481 actual=2969 signed=0 rps=1600/8400:5053/8346 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/0 centerNum=45/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-37.92@108,113 dx=23.5 idx=7/21 dist=32/77 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.38@117,110 dx=33.3 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,87 r=-1,-1
ATGSeedDiag: seed=1@21,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=33(7.5) imip=23/43 pass=10110 acc=-1 ipm=125.9,82.1 inv=123.7,47.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=45/0 raw=136/0 sel=45/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.7/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(117,110) md=33/1/65 cxcy=84.0,119.6 guide=-44.68 atg=60.0/60.0/60.0 pure=-12.32/-12.19 yaw=2681 cmd=2481 actual=2953 signed=0 rps=1600/8400:5426/8659 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/0 centerNum=45/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.54@110,112 dx=25.6 idx=7/22 dist=33/76 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.26@117,110 dx=33.4 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,87 r=-1,-1
ATGSeedDiag: seed=1@22,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(12.7) imip=33/44 pass=10110 acc=-1 ipm=149.0,82.4 inv=150.8,47.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=136/0 sel=46/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(117,109) md=33/1/68 cxcy=84.0,119.6 guide=-44.39 atg=60.0/60.0/60.0 pure=-12.17/-11.92 yaw=2664 cmd=2464 actual=2944 signed=0 rps=1624/8376:5536/9090 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-39.44@110,111 dx=25.8 idx=7/22 dist=33/79 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.88@117,109 dx=33.3 idx=0/16 dist=32/62 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=104,86 r=-1,-1
ATGSeedDiag: seed=1@23,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.7) imip=0/20 pass=10110 acc=-1 ipm=76.7,99.5 inv=64.9,67.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=135/0 sel=46/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.0/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(115,110) md=32/1/69 cxcy=84.0,119.6 guide=-44.10 atg=60.0/60.0/60.0 pure=-12.12/-11.79 yaw=2646 cmd=2446 actual=2949 signed=0 rps=1647/8353:5038/8805 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.30@109,112 dx=24.7 idx=7/21 dist=32/79 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.67@117,109 dx=33.3 idx=0/16 dist=32/62 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,86 r=-1,-1
ATGSeedDiag: seed=1@24,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(7.0) imip=2/22 pass=10110 acc=-1 ipm=80.8,96.5 inv=71.4,62.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/0 raw=135/0 sel=46/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.5/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(115,110) md=32/1/69 cxcy=84.0,119.6 guide=-43.96 atg=60.0/60.0/60.0 pure=-12.07/-11.79 yaw=2637 cmd=2437 actual=2952 signed=0 rps=1660/8340:4997/9371 duty=0/21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/0 centerNum=46/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.34@109,112 dx=24.7 idx=7/21 dist=32/79 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.42@117,109 dx=33.2 idx=0/16 dist=32/62 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=99,87 r=-1,-1
ATGSeedDiag: seed=1@24,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.5) imip=0/20 pass=10110 acc=-1 ipm=77.0,99.3 inv=65.4,66.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=45/0 raw=135/0 sel=45/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.4/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,109) md=33/1/68 cxcy=84.0,119.6 guide=-43.49 atg=60.0/60.0/60.0 pure=-12.22/-11.87 yaw=2610 cmd=2410 actual=2939 signed=0 rps=1698/8302:4733/8812 duty=0/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/0 centerNum=45/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.70@109,112 dx=24.8 idx=6/21 dist=33/79 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-44.05@116,109 dx=32.3 idx=0/16 dist=32/62 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,87 r=-1,-1
ATGSeedDiag: seed=1@25,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.4) imip=0/20 pass=10110 acc=-1 ipm=77.3,99.3 inv=65.9,66.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=45/0 raw=134/0 sel=45/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.3/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(118,109) md=34/1/66 cxcy=84.0,119.6 guide=-44.54 atg=60.0/60.0/60.0 pure=-12.12/-12.00 yaw=2672 cmd=2472 actual=2902 signed=0 rps=1612/8388:4700/8095 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/0 centerNum=45/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-40.28@111,111 dx=26.8 idx=7/22 dist=33/76 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-45.01@118,109 dx=33.5 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=102,86 r=-1,-1
ATGSeedDiag: seed=1@26,107/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(14.3) imip=33/44 pass=10110 acc=-1 ipm=150.4,81.4 inv=151.2,46.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T03:28:50+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive53
```
