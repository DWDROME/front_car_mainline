# drive142

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive142-front_car_circle_drive142.log
- remote_log: /tmp/front_car_circle_drive142.log
- started_at: 2026-06-22T15:16:30+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive142 6
```

4599 /tmp/front_car_circle_drive142.log
frame=937 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/59 raw=0/155 sel=59/106 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/43.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(52,103) md=40/1/229 cxcy=84.0,119.6 guide=38.74 atg=-60.0/-3.0/2.0 pure=7.89/0.96 yaw=-2712 cmd=-2912 actual=-1764 signed=0 rps=6580/0:6029/4627 duty=16/0 pwm=PWM2:16/PWM1:0 motor=2:16/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/59 centerNum=0/59 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=59/106 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:41.80@55,110 dx=-29.1 idx=2/10 dist=41/248 sel=1:39.68@52,105 dx=-31.6 idx=0/20 dist=40/210 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=84,73
ATGSeedDiag: seed=0@-1,-1/1@108,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 48(43.1) imip=38/58 pass=10101 acc=-1 ipm=136.5,77.0 inv=131.5,43.0
frame=938 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/56 raw=0/151 sel=56/100 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/39.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(52,101) md=42/1/215 cxcy=84.0,119.6 guide=38.04 atg=-60.0/-1.0/4.0 pure=7.49/0.57 yaw=-2663 cmd=-2863 actual=-1819 signed=0 rps=6557/0:5431/4047 duty=16/0 pwm=PWM2:16/PWM1:0 motor=2:16/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/56 centerNum=0/56 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=56/100 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:41.66@56,111 dx=-27.9 idx=2/9 dist=39/233 sel=1:38.75@53,104 dx=-31.5 idx=0/20 dist=40/198 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=87,74
ATGSeedDiag: seed=0@-1,-1/1@107,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 45(39.2) imip=35/55 pass=10101 acc=-1 ipm=134.2,74.0 inv=126.7,40.9
frame=939 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/54 raw=0/147 sel=54/96 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/36.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(53,102) md=40/1/208 cxcy=84.0,119.6 guide=36.51 atg=-60.0/0.0/8.0 pure=7.05/0.18 yaw=-2556 cmd=-2756 actual=-1888 signed=0 rps=6505/0:5157/3588 duty=16/0 pwm=PWM2:16/PWM1:0 motor=2:16/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/54 centerNum=0/54 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/96 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:40.59@56,110 dx=-28.3 idx=2/9 dist=40/227 sel=1:37.46@53,102 dx=-31.2 idx=0/20 dist=40/190 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=87,75
ATGSeedDiag: seed=0@-1,-1/1@106,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 45(36.7) imip=35/53 pass=10101 acc=-1 ipm=136.2,77.2 inv=131.3,43.1
frame=940 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/52 raw=0/145 sel=52/94 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/38.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(53,101) md=41/1/201 cxcy=84.0,119.6 guide=36.38 atg=-60.0/0.0/9.0 pure=7.19/0.11 yaw=-2547 cmd=-2747 actual=-1953 signed=0 rps=6501/0:5905/3717 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/52 centerNum=0/52 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/94 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:40.70@57,111 dx=-27.2 idx=1/8 dist=40/222 sel=1:37.50@54,103 dx=-30.2 idx=0/20 dist=40/186 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=89,75
ATGSeedDiag: seed=0@-1,-1/1@105,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 41(38.0) imip=31/51 pass=10111 acc=-1 ipm=131.3,73.9 inv=123.7,40.9
frame=941 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/50 raw=0/143 sel=50/90 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/36.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(54,99) md=42/1/193 cxcy=84.0,119.6 guide=35.03 atg=-60.0/0.0/14.0 pure=6.65/-0.35 yaw=-2452 cmd=-2652 actual=-2004 signed=0 rps=6455/0:6757/4015 duty=14/0 pwm=PWM2:14/PWM1:0 motor=2:14/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/50 centerNum=0/50 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/90 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:39.41@56,109 dx=-27.7 idx=1/8 dist=41/212 sel=1:36.02@54,102 dx=-29.9 idx=0/20 dist=40/178 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=92,75
ATGSeedDiag: seed=0@-1,-1/1@104,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 39(36.0) imip=29/49 pass=10111 acc=-1 ipm=129.8,74.4 inv=122.5,41.3
frame=943 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/47 raw=0/138 sel=47/86 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/37.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(55,99) md=42/1/185 cxcy=84.0,119.6 guide=33.77 atg=-60.0/2.0/23.0 pure=6.28/-0.89 yaw=-2364 cmd=-2564 actual=-2100 signed=0 rps=6412/0:6002/3606 duty=15/0 pwm=PWM2:15/PWM1:0 motor=2:15/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/47 centerNum=0/47 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=47/86 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:37.87@57,109 dx=-26.5 idx=0/7 dist=41/199 sel=1:34.64@56,102 dx=-28.4 idx=0/20 dist=40/170 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=97,76
ATGSeedDiag: seed=0@-1,-1/1@103,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 12(37.8) imip=2/22 pass=10111 acc=-1 ipm=81.5,92.8 inv=72.4,58.0
frame=944 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/46 raw=0/135 sel=46/84 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/34.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(56,99) md=40/1/182 cxcy=84.0,119.6 guide=31.45 atg=-60.0/6.0/33.0 pure=5.54/-1.40 yaw=-2202 cmd=-2270 actual=-2134 signed=0 rps=6153/0:5714/3607 duty=14/0 pwm=PWM2:14/PWM1:0 motor=2:14/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/46 centerNum=0/46 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/84 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:35.90@57,106 dx=-26.5 idx=0/7 dist=41/194 sel=1:32.35@56,99 dx=-27.7 idx=0/20 dist=40/166 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=97,77
ATGSeedDiag: seed=0@-1,-1/1@102,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 39(34.6) imip=29/45 pass=10111 acc=-1 ipm=136.9,79.9 inv=134.4,45.1
frame=945 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/45 raw=0/133 sel=45/81 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/35.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(57,98) md=41/1/175 cxcy=84.0,119.6 guide=30.83 atg=-60.0/9.0/39.0 pure=5.09/-1.75 yaw=-2158 cmd=-2163 actual=-2153 signed=0 rps=6046/118:5832/4062 duty=14/0 pwm=PWM2:14/PWM1:0 motor=2:14/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/45 centerNum=0/45 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/81 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:34.47@58,105 dx=-26.2 idx=0/7 dist=41/188 sel=1:30.98@57,98 dx=-27.0 idx=0/20 dist=40/160 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=99,78
ATGSeedDiag: seed=0@-1,-1/1@102,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 11(35.3) imip=1/21 pass=10111 acc=-1 ipm=83.6,94.0 inv=75.3,59.4
frame=946 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/44 raw=0/132 sel=44/79 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/42.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(58,96) md=42/1/172 cxcy=84.0,119.6 guide=29.24 atg=-60.0/14.0/49.0 pure=4.56/-2.15 yaw=-2047 cmd=-1949 actual=-2144 signed=0 rps=5853/509:5561/4133 duty=14/0 pwm=PWM2:14/PWM1:0 motor=2:14/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/44 centerNum=0/44 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=44/79 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:32.87@58,103 dx=-25.7 idx=0/7 dist=42/186 sel=1:29.44@58,96 dx=-26.2 idx=0/20 dist=40/156 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=101,78
ATGSeedDiag: seed=0@-1,-1/1@102,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(42.9) imip=0/20 pass=10111 acc=-1 ipm=84.2,96.1 inv=76.3,62.2
frame=947 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/41 raw=0/127 sel=41/74 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/45.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(60,95) md=42/1/163 cxcy=84.0,119.6 guide=26.68 atg=-50.0/30.0/60.0 pure=3.36/-3.08 yaw=-1868 cmd=-1668 actual=-2127 signed=0 rps=5625/1054:5878/4386 duty=12/0 pwm=PWM2:12/PWM1:0 motor=2:12/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/41 centerNum=0/41 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=41/74 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:28.83@60,98 dx=-24.4 idx=0/7 dist=42/172 sel=1:25.49@60,93 dx=-23.7 idx=0/20 dist=40/146 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=106,80
ATGSeedDiag: seed=0@-1,-1/1@101,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(45.0) imip=0/20 pass=10111 acc=-1 ipm=86.7,95.3 inv=80.0,61.1
frame=948 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/39 raw=0/125 sel=39/70 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/44.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(61,96) md=42/1/156 cxcy=84.0,119.6 guide=26.70 atg=-36.0/39.0/60.0 pure=2.80/-3.51 yaw=-1869 cmd=-1669 actual=-2127 signed=0 rps=5626/1052:5747/4119 duty=13/0 pwm=PWM2:13/PWM1:0 motor=2:13/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/39 centerNum=0/39 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=39/70 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:29.16@61,101 dx=-23.4 idx=0/6 dist=39/163 sel=1:23.74@62,92 dx=-22.5 idx=0/20 dist=40/138 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=108,81
ATGSeedDiag: seed=0@-1,-1/1@101,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(44.3) imip=0/20 pass=10111 acc=-1 ipm=87.9,95.4 inv=81.8,61.2
frame=949 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/38 raw=0/122 sel=38/69 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/44.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(62,94) md=41/1/153 cxcy=84.0,119.6 guide=23.85 atg=-21.0/51.0/60.0 pure=2.11/-4.00 yaw=-1670 cmd=-1470 actual=-2131 signed=0 rps=5530/1502:6444/4455 duty=11/0 pwm=PWM2:11/PWM1:0 motor=2:11/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/38 centerNum=0/38 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=38/69 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:26.55@62,98 dx=-22.4 idx=0/6 dist=39/158 sel=1:21.27@63,90 dx=-20.7 idx=0/20 dist=40/136 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=110,81
ATGSeedDiag: seed=0@-1,-1/1@100,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(44.6) imip=0/20 pass=10111 acc=-1 ipm=89.4,94.8 inv=83.7,60.4
frame=950 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/36 raw=0/119 sel=36/65 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/43.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(63,93) md=41/1/144 cxcy=84.0,119.6 guide=22.18 atg=-10.0/60.0/60.0 pure=1.55/-4.40 yaw=-1553 cmd=-1353 actual=-2123 signed=0 rps=5474/1766:6274/4281 duty=11/2 pwm=PWM2:11/PWM1:2 motor=2:11/1:2
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/36 centerNum=0/36 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=36/65 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:24.63@63,96 dx=-21.4 idx=0/6 dist=40/151 sel=1:19.37@65,88 dx=-19.1 idx=0/20 dist=40/128 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,82
ATGSeedDiag: seed=0@-1,-1/1@100,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(43.2) imip=0/20 pass=10111 acc=-1 ipm=90.9,95.0 inv=86.0,60.6
frame=951 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/35 raw=0/116 sel=35/63 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/41.9/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(65,91) md=40/1/138 cxcy=84.0,119.6 guide=19.26 atg=-3.0/60.0/60.0 pure=0.91/-4.80 yaw=-1348 cmd=-1148 actual=-2115 signed=0 rps=5375/2227:6341/4261 duty=11/4 pwm=PWM2:11/PWM1:4 motor=2:11/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/35 centerNum=0/35 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=35/63 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:22.22@64,94 dx=-19.8 idx=0/6 dist=40/145 sel=1:17.19@67,87 dx=-17.2 idx=0/20 dist=40/124 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=114,83
ATGSeedDiag: seed=0@-1,-1/1@100,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(41.9) imip=0/20 pass=10111 acc=-1 ipm=92.4,94.9 inv=88.1,60.5
frame=952 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/34 raw=0/114 sel=34/61 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/40.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(66,90) md=40/1/134 cxcy=84.0,119.6 guide=17.43 atg=0.0/60.0/60.0 pure=0.41/-5.03 yaw=-1220 cmd=-1020 actual=-2096 signed=0 rps=5314/2517:6032/4057 duty=11/5 pwm=PWM2:11/PWM1:5 motor=2:11/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/34 centerNum=0/34 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=34/61 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:20.37@65,93 dx=-18.6 idx=0/6 dist=41/140 sel=1:15.38@68,86 dx=-15.6 idx=0/20 dist=40/120 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=116,84
ATGSeedDiag: seed=0@-1,-1/1@100,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(40.5) imip=0/20 pass=10111 acc=-1 ipm=93.9,95.1 inv=90.2,60.7
frame=953 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/33 raw=0/111 sel=33/59 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/39.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(69,87) md=41/1/129 cxcy=84.0,119.6 guide=15.25 atg=0.0/60.0/60.0 pure=-0.22/-5.44 yaw=-1067 cmd=-867 actual=-2060 signed=0 rps=5240/2863:5961/4073 duty=11/6 pwm=PWM2:11/PWM1:6 motor=2:11/1:6
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/33 centerNum=0/33 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=33/59 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:17.80@67,91 dx=-16.6 idx=0/6 dist=41/134 sel=1:13.10@71,85 dx=-13.5 idx=0/20 dist=40/116 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=116,85
ATGSeedDiag: seed=0@-1,-1/1@100,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(39.8) imip=0/20 pass=10111 acc=-1 ipm=95.4,95.1 inv=92.4,60.7

- stopped_at: 2026-06-22T15:16:43+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive142
```
