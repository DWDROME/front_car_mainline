# drive76

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive76-front_car_circle_drive76.log
- remote_log: /tmp/front_car_circle_drive76.log
- started_at: 2026-06-22T05:24:10+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive76 6
```

4271 /tmp/front_car_circle_drive76.log
ATGSeedDiag: seed=1@10,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.9) imip=0/20 pass=10110 acc=-1 ipm=69.0,97.6 inv=53.6,64.4 | 1(2.7) imip=0/2 pass=10111 acc=-1 ipm=115.9,115.6 inv=152.0,102.1
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/3 raw=149/11 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/0.8/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/77 cxcy=84.0,119.6 guide=-37.08 atg=60.0/60.0/60.0 pure=-11.25/-10.72 yaw=2225 cmd=2425 actual=1932 signed=0 rps=1677/8323:5023/7404 duty=0/25 pwm=PWM2:0/PWM1:25 motor=2:0/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/3 centerNum=53/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.47@110,104 dx=25.5 idx=8/26 dist=32/84 right=1:-23.88@107,91 dx=22.9 idx=0/2 dist=4/4 sel=1:-38.59@116,102 dx=32.2 idx=0/16 dist=32/68 edge=1:-26.41@106.0,98.5 dx=22.0 width=40.8 l=94,82 r=118,115
CxScan: raw_ref=80.0 edge=106.0,98.5 best_raw_x=135 best_err=-1.18 best_cxcy=105.1,119.7 scan=0:-50.1,10:-48.0,20:-45.6,30:-43.0,40:-40.2,50:-37.2,60:-33.9,70:-30.3,80:-26.4,90:-22.3,100:-17.9,110:-13.3,120:-8.5,130:-3.6,140:1.3
ATGSeedDiag: seed=1@10,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.7) imip=0/20 pass=10110 acc=-1 ipm=69.0,97.6 inv=53.6,64.4 | 1(0.8) imip=0/2 pass=10111 acc=-1 ipm=115.8,115.6 inv=151.8,102.0
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/3 raw=149/10 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/1.4/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=32/1/76 cxcy=84.0,119.6 guide=-38.05 atg=60.0/60.0/60.0 pure=-11.31/-10.72 yaw=2283 cmd=2483 actual=1915 signed=0 rps=1597/8403:3681/5350 duty=1/28 pwm=PWM2:1/PWM1:28 motor=2:1/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/3 centerNum=53/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.56@109,105 dx=25.4 idx=8/26 dist=32/83 right=1:-24.57@108,91 dx=23.9 idx=0/2 dist=4/4 sel=1:-38.65@116,102 dx=32.3 idx=0/16 dist=32/68 edge=1:-26.66@106.5,98.0 dx=22.5 width=39.4 l=95,82 r=118,114
CxScan: raw_ref=80.0 edge=106.5,98.0 best_raw_x=140 best_err=0.63 best_cxcy=107.0,119.7 scan=0:-50.1,10:-47.9,20:-45.6,30:-43.0,40:-40.3,50:-37.3,60:-34.0,70:-30.5,80:-26.7,90:-22.6,100:-18.3,110:-13.8,120:-9.1,130:-4.2,140:0.6
ATGSeedDiag: seed=1@10,108/1@148,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.5) imip=0/20 pass=10110 acc=-1 ipm=69.0,97.6 inv=53.6,64.4 | 1(1.4) imip=0/2 pass=10111 acc=-1 ipm=116.3,115.3 inv=152.2,101.2
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/3 raw=149/11 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.2/1.0/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=32/1/76 cxcy=84.0,119.6 guide=-38.28 atg=60.0/60.0/60.0 pure=-11.29/-10.72 yaw=2297 cmd=2497 actual=1901 signed=0 rps=1578/8422:4038/5773 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/3 centerNum=53/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-34.84@111,104 dx=27.0 idx=8/27 dist=33/82 right=1:-23.95@107,91 dx=23.1 idx=0/2 dist=4/4 sel=1:-38.86@116,103 dx=32.4 idx=0/16 dist=32/68 edge=1:-26.92@106.5,98.5 dx=22.5 width=40.2 l=95,82 r=118,115
CxScan: raw_ref=80.0 edge=106.5,98.5 best_raw_x=140 best_err=0.64 best_cxcy=107.0,119.7 scan=0:-50.4,10:-48.3,20:-45.9,30:-43.4,40:-40.6,50:-37.6,60:-34.3,70:-30.7,80:-26.9,90:-22.8,100:-18.5,110:-13.9,120:-9.2,130:-4.3,140:0.6
ATGSeedDiag: seed=1@10,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.2) imip=0/20 pass=10110 acc=-1 ipm=69.0,97.6 inv=53.6,64.4 | 1(1.0) imip=0/2 pass=10111 acc=-1 ipm=115.6,115.6 inv=151.3,102.1
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/3 raw=151/11 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/0.7/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/77 cxcy=84.0,119.6 guide=-36.94 atg=60.0/60.0/60.0 pure=-11.25/-10.56 yaw=2216 cmd=2416 actual=1904 signed=0 rps=1688/8312:4113/5795 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/3 centerNum=53/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.19@109,104 dx=25.2 idx=8/26 dist=32/84 right=1:-23.91@107,91 dx=23.0 idx=0/2 dist=4/4 sel=1:-38.45@116,102 dx=32.2 idx=0/16 dist=32/68 edge=1:-27.17@107.0,98.0 dx=23.0 width=40.5 l=96,81 r=118,115
CxScan: raw_ref=80.0 edge=107.0,98.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.6,50:-37.7,60:-34.4,70:-30.9,80:-27.2,90:-23.1,100:-18.9,110:-14.4,120:-9.7,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.5) imip=0/20 pass=10110 acc=-1 ipm=68.7,97.8 inv=53.0,64.7 | 1(0.7) imip=0/2 pass=10111 acc=-1 ipm=115.6,115.6 inv=151.3,102.1
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=54/3 raw=151/11 sel=54/36 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.1/2.1/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/78 cxcy=84.0,119.6 guide=-36.62 atg=60.0/60.0/60.0 pure=-11.04/-10.29 yaw=2197 cmd=2397 actual=1914 signed=0 rps=1715/8285:3820/5298 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/3 centerNum=54/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/36 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.90@109,104 dx=25.0 idx=8/26 dist=33/87 right=1:-23.92@107,91 dx=23.0 idx=0/2 dist=4/4 sel=1:-38.09@116,102 dx=32.0 idx=0/16 dist=32/70 edge=1:-27.17@107.0,98.0 dx=23.0 width=40.5 l=96,81 r=118,115
CxScan: raw_ref=80.0 edge=107.0,98.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.6,50:-37.7,60:-34.4,70:-30.9,80:-27.2,90:-23.1,100:-18.9,110:-14.4,120:-9.7,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(13.1) imip=42/53 pass=10100 acc=-1 ipm=160.0,72.9 inv=152.1,40.0 | 1(2.1) imip=0/2 pass=10111 acc=-1 ipm=115.5,115.6 inv=151.2,102.0
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/3 raw=170/11 sel=70/68 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=68.0/2.1/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/133 cxcy=84.0,119.6 guide=-36.75 atg=60.0/60.0/60.0 pure=-11.02/-7.75 yaw=2205 cmd=2405 actual=1914 signed=0 rps=1704/8296:3878/5365 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/3 centerNum=70/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=70/68 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.91@109,104 dx=25.1 idx=8/26 dist=33/160 right=1:-23.92@107,91 dx=23.0 idx=0/2 dist=4/4 sel=1:-38.20@116,102 dx=32.0 idx=0/16 dist=32/134 edge=1:-27.17@107.0,98.0 dx=23.0 width=40.5 l=96,81 r=118,115
CxScan: raw_ref=80.0 edge=107.0,98.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.6,50:-37.7,60:-34.4,70:-30.9,80:-27.2,90:-23.1,100:-18.9,110:-14.4,120:-9.7,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(68.0) imip=44/64 pass=11100 acc=-1 ipm=163.9,70.6 inv=153.7,38.6 | 1(2.1) imip=0/2 pass=10111 acc=-1 ipm=115.5,115.6 inv=151.2,102.0
frame=886 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=69/3 raw=170/11 sel=69/67 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=69.1/2.7/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/132 cxcy=84.0,119.6 guide=-36.75 atg=60.0/60.0/60.0 pure=-11.01/-7.71 yaw=2205 cmd=2405 actual=1912 signed=0 rps=1704/8296:3662/5165 duty=1/28 pwm=PWM2:1/PWM1:28 motor=2:1/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=69/3 centerNum=69/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=69/67 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.79@109,104 dx=24.9 idx=8/26 dist=33/159 right=1:-23.96@107,91 dx=23.1 idx=0/2 dist=4/4 sel=1:-38.20@116,102 dx=32.0 idx=0/16 dist=32/132 edge=1:-26.41@106.0,98.5 dx=22.0 width=40.8 l=94,82 r=118,115
CxScan: raw_ref=80.0 edge=106.0,98.5 best_raw_x=135 best_err=-1.18 best_cxcy=105.1,119.7 scan=0:-50.1,10:-48.0,20:-45.6,30:-43.0,40:-40.2,50:-37.2,60:-33.9,70:-30.3,80:-26.4,90:-22.3,100:-17.9,110:-13.3,120:-8.5,130:-3.6,140:1.3
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=54(69.1) imip=44/64 pass=11100 acc=-1 ipm=163.5,69.8 inv=152.5,38.1 | 1(2.7) imip=0/2 pass=10111 acc=-1 ipm=115.5,115.6 inv=151.0,102.0
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/3 raw=170/11 sel=70/69 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=70.9/2.7/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/138 cxcy=84.0,119.6 guide=-36.75 atg=60.0/60.0/60.0 pure=-11.05/-7.67 yaw=2205 cmd=2405 actual=1916 signed=0 rps=1704/8296:3692/5466 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/3 centerNum=70/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=70/69 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.35@107,105 dx=23.2 idx=8/25 dist=32/161 right=1:-23.96@107,91 dx=23.1 idx=0/2 dist=4/4 sel=1:-38.26@116,102 dx=32.0 idx=0/16 dist=32/136 edge=1:-27.17@107.0,98.0 dx=23.0 width=40.5 l=96,81 r=118,115
CxScan: raw_ref=80.0 edge=107.0,98.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.6,50:-37.7,60:-34.4,70:-30.9,80:-27.2,90:-23.1,100:-18.9,110:-14.4,120:-9.7,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=53(70.9) imip=43/63 pass=11100 acc=-1 ipm=161.8,70.6 inv=151.6,38.6 | 1(2.7) imip=0/2 pass=10111 acc=-1 ipm=115.5,115.6 inv=151.0,102.0
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/4 raw=170/12 sel=70/69 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=70.1/4.8/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/140 cxcy=84.0,119.6 guide=-36.89 atg=60.0/60.0/60.0 pure=-11.14/-7.58 yaw=2214 cmd=2414 actual=1924 signed=0 rps=1692/8308:3723/5846 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/4 centerNum=70/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=70/69 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.82@109,104 dx=24.7 idx=8/26 dist=33/160 right=1:-25.68@109,90 dx=25.5 idx=0/3 dist=6/6 sel=1:-38.55@116,102 dx=32.1 idx=0/16 dist=32/136 edge=1:-27.91@108.0,97.5 dx=24.0 width=40.8 l=96,81 r=120,114
CxScan: raw_ref=80.0 edge=108.0,97.5 best_raw_x=140 best_err=-1.27 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.5,20:-46.2,30:-43.7,40:-41.1,50:-38.2,60:-35.0,70:-31.6,80:-27.9,90:-24.0,100:-19.8,110:-15.4,120:-10.8,130:-6.1,140:-1.3
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(70.1) imip=42/62 pass=11100 acc=-1 ipm=159.7,70.8 inv=149.7,38.7 | 2(4.8) imip=0/3 pass=10111 acc=-1 ipm=117.5,114.6 inv=153.4,99.0
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/3 raw=170/11 sel=70/70 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=69.5/2.4/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=32/1/144 cxcy=84.0,119.6 guide=-38.28 atg=60.0/60.0/60.0 pure=-11.13/-7.49 yaw=2297 cmd=2497 actual=1915 signed=0 rps=1578/8422:3571/5731 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/3 centerNum=70/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=70/70 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.07@109,105 dx=24.8 idx=8/26 dist=33/164 right=1:-24.03@107,91 dx=23.2 idx=0/2 dist=4/4 sel=1:-38.81@116,103 dx=32.3 idx=0/16 dist=32/138 edge=1:-27.17@107.0,98.0 dx=23.0 width=40.5 l=96,81 r=118,115
CxScan: raw_ref=80.0 edge=107.0,98.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.6,50:-37.7,60:-34.4,70:-30.9,80:-27.2,90:-23.1,100:-18.9,110:-14.4,120:-9.7,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=51(69.5) imip=41/61 pass=11100 acc=-1 ipm=157.6,70.9 inv=147.7,38.8 | 1(2.4) imip=0/2 pass=10111 acc=-1 ipm=115.4,115.6 inv=150.9,102.1
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/3 raw=170/11 sel=70/71 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=69.6/0.3/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=32/1/146 cxcy=84.0,119.6 guide=-38.28 atg=60.0/60.0/60.0 pure=-11.11/-7.44 yaw=2297 cmd=2497 actual=1896 signed=0 rps=1578/8422:3845/6024 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/3 centerNum=70/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=70/71 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.06@109,105 dx=24.8 idx=8/26 dist=33/170 right=1:-24.34@108,90 dx=23.7 idx=0/2 dist=4/4 sel=1:-39.05@116,103 dx=32.4 idx=0/16 dist=32/140 edge=1:-26.92@107.0,97.5 dx=23.0 width=39.7 l=96,81 r=118,114
CxScan: raw_ref=80.0 edge=107.0,97.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.0,10:-47.9,20:-45.6,30:-43.1,40:-40.3,50:-37.4,60:-34.1,70:-30.7,80:-26.9,90:-22.9,100:-18.7,110:-14.2,120:-9.6,130:-4.8,140:-0.0
ATGSeedDiag: seed=1@9,108/1@147,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(69.6) imip=40/60 pass=11100 acc=-1 ipm=155.6,71.7 inv=146.5,39.3 | 1(0.3) imip=0/2 pass=10111 acc=-1 ipm=115.9,115.3 inv=151.4,101.3
frame=891 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/4 raw=170/12 sel=70/71 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=73.0/5.5/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=32/1/147 cxcy=84.0,119.6 guide=-38.28 atg=60.0/60.0/60.0 pure=-11.00/-7.39 yaw=2297 cmd=2497 actual=1884 signed=0 rps=1578/8422:3781/5779 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/4 centerNum=70/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=70/71 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.55@107,105 dx=23.2 idx=8/25 dist=32/167 right=1:-25.68@109,90 dx=25.5 idx=0/3 dist=6/6 sel=1:-38.79@116,103 dx=32.3 idx=0/16 dist=32/140 edge=1:-27.91@108.0,97.5 dx=24.0 width=40.8 l=96,81 r=120,114
CxScan: raw_ref=80.0 edge=108.0,97.5 best_raw_x=140 best_err=-1.27 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.5,20:-46.2,30:-43.7,40:-41.1,50:-38.2,60:-35.0,70:-31.6,80:-27.9,90:-24.0,100:-19.8,110:-15.4,120:-10.8,130:-6.1,140:-1.3
ATGSeedDiag: seed=1@9,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(73.0) imip=40/60 pass=11100 acc=-1 ipm=155.3,71.2 inv=145.7,39.0 | 2(5.5) imip=0/3 pass=10111 acc=-1 ipm=117.5,114.6 inv=153.3,98.9
frame=892 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=72/3 raw=170/11 sel=72/74 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=67.0/2.8/0.0/0.0 dist=0 begin=0/2603 m0=(84,119) ml=(114,103) md=33/1/155 cxcy=84.0,119.6 guide=-36.57 atg=60.0/60.0/60.0 pure=-10.89/-7.30 yaw=2194 cmd=2394 actual=1900 signed=0 rps=1719/8281:4011/5987 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=72/3 centerNum=72/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=72/74 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.36@108,104 dx=24.4 idx=8/26 dist=33/175 right=1:-24.15@107,91 dx=23.4 idx=0/2 dist=4/4 sel=1:-38.29@116,102 dx=32.0 idx=0/16 dist=32/146 edge=1:-26.92@107.0,97.5 dx=23.0 width=39.7 l=96,81 r=118,114
CxScan: raw_ref=80.0 edge=107.0,97.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.0,10:-47.9,20:-45.6,30:-43.1,40:-40.3,50:-37.4,60:-34.1,70:-30.7,80:-26.9,90:-22.9,100:-18.7,110:-14.2,120:-9.6,130:-4.8,140:-0.0
ATGSeedDiag: seed=1@8,108/1@147,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(67.0) imip=40/60 pass=11100 acc=-1 ipm=154.6,69.7 inv=143.7,38.1 | 1(2.8) imip=0/2 pass=10111 acc=-1 ipm=115.8,115.3 inv=151.1,101.1

- stopped_at: 2026-06-22T05:24:23+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive76
```
