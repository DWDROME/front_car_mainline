# drive144

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive144-front_car_circle_drive144.log
- remote_log: /tmp/front_car_circle_drive144.log
- started_at: 2026-06-22T15:18:36+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive144 6
```

4567 /tmp/front_car_circle_drive144.log
frame=895 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/48 raw=0/142 sel=48/89 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/36.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(53,101) md=42/1/191 cxcy=84.0,119.6 guide=37.37 atg=-60.0/0.0/14.0 pure=7.16/-0.26 yaw=-2990 cmd=-3190 actual=-2474 signed=0 rps=6714/0:6148/4078 duty=16/0 pwm=PWM2:16/PWM1:0 motor=2:16/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/48 centerNum=0/48 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/89 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:42.21@56,111 dx=-28.4 idx=0/6 dist=40/207 sel=1:38.33@53,104 dx=-30.9 idx=0/20 dist=40/176 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=92,77
ATGSeedDiag: seed=0@-1,-1/1@95,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 12(36.8) imip=2/22 pass=10111 acc=-1 ipm=78.7,92.5 inv=68.5,57.7
frame=896 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/46 raw=0/138 sel=46/86 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/36.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(54,102) md=41/1/186 cxcy=84.0,119.6 guide=36.28 atg=-60.0/1.0/22.0 pure=6.54/-0.81 yaw=-2903 cmd=-3103 actual=-2471 signed=0 rps=6672/0:6736/4314 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/46 centerNum=0/46 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/86 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:40.07@55,109 dx=-28.7 idx=0/6 dist=40/197 sel=1:36.47@54,102 dx=-30.4 idx=0/20 dist=40/170 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=93,79
ATGSeedDiag: seed=0@-1,-1/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 11(36.2) imip=1/21 pass=10111 acc=-1 ipm=79.7,94.1 inv=69.8,59.6
frame=897 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/44 raw=0/136 sel=44/82 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/44.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(55,102) md=40/1/178 cxcy=84.0,119.6 guide=34.71 atg=-60.0/5.0/31.0 pure=5.93/-1.35 yaw=-2777 cmd=-2977 actual=-2475 signed=0 rps=6611/0:6155/3917 duty=16/0 pwm=PWM2:16/PWM1:0 motor=2:16/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/44 centerNum=0/44 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=44/82 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:38.36@56,107 dx=-28.5 idx=0/6 dist=41/190 sel=1:34.60@55,100 dx=-29.5 idx=0/20 dist=40/162 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=95,79
ATGSeedDiag: seed=0@-1,-1/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(44.9) imip=0/20 pass=10111 acc=-1 ipm=80.7,96.0 inv=71.2,62.0
frame=898 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/43 raw=0/133 sel=43/80 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/45.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(56,101) md=40/1/174 cxcy=84.0,119.6 guide=33.79 atg=-60.0/10.0/42.0 pure=5.36/-1.85 yaw=-2703 cmd=-2903 actual=-2493 signed=0 rps=6576/0:6328/4049 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/43 centerNum=0/43 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=43/80 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:36.41@56,105 dx=-28.1 idx=0/6 dist=41/184 sel=1:32.83@55,98 dx=-28.7 idx=0/20 dist=40/158 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=98,80
ATGSeedDiag: seed=0@-1,-1/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(45.5) imip=0/20 pass=10111 acc=-1 ipm=81.9,95.7 inv=73.0,61.6
frame=899 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/42 raw=0/131 sel=42/78 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/44.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(57,101) md=40/1/173 cxcy=84.0,119.6 guide=32.27 atg=-60.0/16.0/53.0 pure=4.71/-2.30 yaw=-2582 cmd=-2730 actual=-2508 signed=0 rps=6447/0:6012/3910 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/42 centerNum=0/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=42/78 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:34.37@57,103 dx=-27.4 idx=0/6 dist=41/180 sel=1:30.55@57,96 dx=-27.4 idx=0/20 dist=40/154 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=100,80
ATGSeedDiag: seed=0@-1,-1/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(44.4) imip=0/20 pass=10111 acc=-1 ipm=83.3,95.3 inv=75.0,61.1
frame=900 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/40 raw=0/126 sel=40/73 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/43.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(59,97) md=41/1/162 cxcy=84.0,119.6 guide=28.74 atg=-50.0/31.0/60.0 pure=3.39/-3.20 yaw=-2299 cmd=-2099 actual=-2522 signed=0 rps=5833/80:6104/4122 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/40 centerNum=0/40 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=40/73 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:30.25@59,99 dx=-25.5 idx=0/6 dist=42/171 sel=1:26.24@59,93 dx=-24.7 idx=0/20 dist=40/144 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,81
ATGSeedDiag: seed=0@-1,-1/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(43.5) imip=0/20 pass=10111 acc=-1 ipm=86.1,94.8 inv=79.0,60.5
frame=901 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/38 raw=0/124 sel=38/69 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/42.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(60,96) md=40/1/152 cxcy=84.0,119.6 guide=25.85 atg=-36.0/42.0/60.0 pure=2.79/-3.66 yaw=-2068 cmd=-1868 actual=-2528 signed=0 rps=5722/602:5941/3987 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/38 centerNum=0/38 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=38/69 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:27.90@60,97 dx=-24.1 idx=0/6 dist=42/161 sel=1:24.02@61,91 dx=-23.0 idx=0/20 dist=40/136 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=106,82
ATGSeedDiag: seed=0@-1,-1/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(42.8) imip=0/20 pass=10111 acc=-1 ipm=87.7,94.7 inv=81.2,60.3
frame=902 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/37 raw=0/122 sel=37/67 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/43.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(61,94) md=41/1/147 cxcy=84.0,119.6 guide=24.08 atg=-22.0/52.0/60.0 pure=2.22/-4.09 yaw=-1926 cmd=-1726 actual=-2517 signed=0 rps=5654/922:6190/3931 duty=12/0 pwm=PWM2:12/PWM1:0 motor=2:12/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/37 centerNum=0/37 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=37/67 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:26.39@61,96 dx=-23.2 idx=0/6 dist=42/156 sel=1:22.18@63,90 dx=-21.5 idx=0/20 dist=40/132 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=108,83
ATGSeedDiag: seed=0@-1,-1/1@95,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(43.0) imip=0/20 pass=10111 acc=-1 ipm=89.1,95.1 inv=83.4,60.8
frame=903 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/35 raw=0/118 sel=35/64 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/42.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(64,90) md=42/1/139 cxcy=84.0,119.6 guide=21.37 atg=-10.0/60.0/60.0 pure=1.47/-4.59 yaw=-1710 cmd=-1510 actual=-2505 signed=0 rps=5549/1411:6528/3858 duty=11/1 pwm=PWM2:11/PWM1:1 motor=2:11/1:1
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/35 centerNum=0/35 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=35/64 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:25.62@62,97 dx=-22.0 idx=0/5 dist=39/148 sel=1:19.54@65,88 dx=-19.3 idx=0/20 dist=40/126 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=111,84
ATGSeedDiag: seed=0@-1,-1/1@95,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(42.3) imip=0/20 pass=10111 acc=-1 ipm=91.0,94.9 inv=86.1,60.5
frame=904 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/34 raw=0/115 sel=34/62 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/41.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(65,91) md=40/1/136 cxcy=84.0,119.6 guide=19.22 atg=-3.0/60.0/60.0 pure=0.79/-5.08 yaw=-1538 cmd=-1338 actual=-2482 signed=0 rps=5466/1800:6316/3692 duty=11/3 pwm=PWM2:11/PWM1:3 motor=2:11/1:3
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/34 centerNum=0/34 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=34/62 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:22.86@64,95 dx=-20.1 idx=0/5 dist=39/142 sel=1:17.24@67,87 dx=-17.3 idx=0/20 dist=40/122 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,85
ATGSeedDiag: seed=0@-1,-1/1@95,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(41.0) imip=0/20 pass=10111 acc=-1 ipm=92.7,95.1 inv=88.6,60.7
frame=905 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/32 raw=0/112 sel=32/58 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/38.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(68,88) md=41/1/127 cxcy=84.0,119.6 guide=16.87 atg=0.0/60.0/60.0 pure=0.07/-5.52 yaw=-1350 cmd=-1150 actual=-2449 signed=0 rps=5376/2225:6561/3891 duty=11/4 pwm=PWM2:11/PWM1:4 motor=2:11/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/32 centerNum=0/32 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=32/58 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:20.57@65,93 dx=-18.7 idx=0/5 dist=39/134 sel=1:14.55@69,86 dx=-14.9 idx=0/20 dist=40/114 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=115,87
ATGSeedDiag: seed=0@-1,-1/1@95,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(38.2) imip=0/20 pass=10111 acc=-1 ipm=94.5,95.3 inv=91.2,61.0
frame=906 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/31 raw=0/109 sel=31/56 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/36.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(69,88) md=40/1/123 cxcy=84.0,119.6 guide=14.41 atg=1.0/60.0/60.0 pure=-0.59/-5.88 yaw=-1153 cmd=-953 actual=-2393 signed=0 rps=5281/2669:6495/4048 duty=10/6 pwm=PWM2:10/PWM1:6 motor=2:10/1:6
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/31 centerNum=0/31 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=31/56 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:18.07@67,92 dx=-16.7 idx=0/5 dist=40/128 sel=1:12.10@71,84 dx=-12.6 idx=0/20 dist=40/110 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=117,88
ATGSeedDiag: seed=0@-1,-1/1@95,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(36.5) imip=0/20 pass=10111 acc=-1 ipm=96.2,95.6 inv=93.7,61.3
frame=907 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/30 raw=0/105 sel=30/54 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/34.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(73,85) md=42/1/118 cxcy=84.0,119.6 guide=11.89 atg=7.0/60.0/60.0 pure=-1.25/-6.22 yaw=-951 cmd=-751 actual=-2311 signed=0 rps=5184/3126:6088/4177 duty=11/7 pwm=PWM2:11/PWM1:7 motor=2:11/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/30 centerNum=0/30 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=30/54 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:12.98@71,87 dx=-12.9 idx=0/6 dist=40/119 sel=1:9.56@74,83 dx=-10.1 idx=0/20 dist=40/106 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=120,88
ATGSeedDiag: seed=0@-1,-1/1@95,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(34.0) imip=0/20 pass=10111 acc=-1 ipm=98.1,95.7 inv=96.5,61.5
frame=908 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/30 raw=0/103 sel=30/54 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/31.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(73,86) md=40/1/119 cxcy=84.0,119.6 guide=10.03 atg=13.0/60.0/60.0 pure=-1.73/-6.48 yaw=-802 cmd=-602 actual=-2220 signed=0 rps=5112/3462:6416/4957 duty=10/8 pwm=PWM2:10/PWM1:8 motor=2:10/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/30 centerNum=0/30 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=30/54 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:9.13@75,84 dx=-9.5 idx=0/7 dist=42/118 sel=1:7.75@76,82 dx=-8.2 idx=0/20 dist=40/106 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=121,89
ATGSeedDiag: seed=0@-1,-1/1@96,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 9(31.5) imip=0/19 pass=10111 acc=-1 ipm=97.5,97.8 inv=96.7,64.4
frame=909 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/28 raw=0/100 sel=28/50 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/33.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(76,84) md=41/1/109 cxcy=84.0,119.6 guide=7.87 atg=25.0/60.0/60.0 pure=-2.27/-6.86 yaw=-630 cmd=-430 actual=-2134 signed=0 rps=5029/3851:5500/4499 duty=11/10 pwm=PWM2:11/PWM1:10 motor=2:11/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/28 centerNum=0/28 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=28/50 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:9.25@75,86 dx=-9.3 idx=0/6 dist=40/110 sel=1:5.59@78,82 dx=-6.0 idx=0/20 dist=40/98 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=123,91
ATGSeedDiag: seed=0@-1,-1/1@97,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(33.5) imip=0/20 pass=10111 acc=-1 ipm=100.8,96.8 inv=101.1,62.9
frame=910 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/27 raw=0/97 sel=27/48 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/31.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(79,83) md=42/1/105 cxcy=84.0,119.6 guide=5.73 atg=39.0/60.0/60.0 pure=-2.84/-6.90 yaw=-458 cmd=-258 actual=-2027 signed=0 rps=4947/4238:5558/4630 duty=10/11 pwm=PWM2:10/PWM1:11 motor=2:10/1:11
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/27 centerNum=0/27 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=27/48 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:7.17@77,85 dx=-7.3 idx=0/6 dist=40/107 sel=1:3.42@80,81 dx=-3.7 idx=0/20 dist=40/94 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=124,91
ATGSeedDiag: seed=0@-1,-1/1@97,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(31.0) imip=0/20 pass=10111 acc=-1 ipm=102.3,97.3 inv=103.6,63.5

- stopped_at: 2026-06-22T15:18:50+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive144
```
