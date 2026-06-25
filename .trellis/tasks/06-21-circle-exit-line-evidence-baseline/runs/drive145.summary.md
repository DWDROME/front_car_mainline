# drive145

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive145-front_car_circle_drive145.log
- remote_log: /tmp/front_car_circle_drive145.log
- started_at: 2026-06-22T15:19:33+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive145 6
```

4410 /tmp/front_car_circle_drive145.log
CxScan: raw_ref=80.0 edge=114.5,97.0 best_raw_x=140 best_err=-9.28 best_cxcy=107.0,119.7 scan=0:-53.4,10:-51.5,20:-49.6,30:-47.4,40:-45.1,50:-42.6,60:-39.9,70:-36.9,80:-33.7,90:-30.2,100:-26.5,110:-22.5,120:-18.3,130:-13.9,140:-9.3
ATGSeedDiag: seed=1@4,86/1@134,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(10.5) imip=33/49 pass=10110 acc=-1 ipm=137.8,78.5 inv=134.2,44.1 | 3(5.3) imip=0/4 pass=10111 acc=-1 ipm=114.6,115.7 inv=149.3,102.3
frame=910 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/5 raw=153/21 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/3.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(119,104) md=41/1/66 cxcy=84.0,119.6 guide=-42.69 atg=60.0/60.0/60.0 pure=-12.59/-12.52 yaw=3842 cmd=4042 actual=2423 signed=0 rps=0/7124:4624/6684 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/5 centerNum=50/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.84@111,105 dx=27.0 idx=12/30 dist=40/78 right=1:-29.86@114,90 dx=30.5 idx=0/4 dist=8/8 sel=1:-44.43@122,104 dx=37.6 idx=0/20 dist=40/60 edge=1:-34.39@115.0,97.5 dx=31.0 width=37.5 l=112,79 r=118,116
CxScan: raw_ref=80.0 edge=115.0,97.5 best_raw_x=140 best_err=-9.99 best_cxcy=107.0,119.7 scan=0:-53.9,10:-52.1,20:-50.1,30:-48.0,40:-45.7,50:-43.2,60:-40.5,70:-37.6,80:-34.4,90:-30.9,100:-27.2,110:-23.3,120:-19.0,130:-14.6,140:-10.0
ATGSeedDiag: seed=1@4,86/1@136,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(11.7) imip=30/49 pass=10110 acc=-1 ipm=130.9,78.3 inv=126.5,44.0 | 2(3.0) imip=0/4 pass=10111 acc=-1 ipm=113.2,116.1 inv=146.9,103.7
frame=911 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/19 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.4/1.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,104) md=42/1/66 cxcy=84.0,119.6 guide=-43.02 atg=60.0/60.0/60.0 pure=-12.69/-12.66 yaw=3872 cmd=4072 actual=2449 signed=0 rps=0/7139:4845/6821 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.33@112,105 dx=28.4 idx=12/31 dist=41/76 right=1:-28.87@113,90 dx=29.1 idx=0/3 dist=6/6 sel=1:-44.60@122,104 dx=37.9 idx=0/20 dist=40/60 edge=1:-33.96@114.5,97.5 dx=30.5 width=37.1 l=113,79 r=116,116
CxScan: raw_ref=80.0 edge=114.5,97.5 best_raw_x=140 best_err=-9.38 best_cxcy=107.0,119.7 scan=0:-53.7,10:-51.9,20:-49.9,30:-47.8,40:-45.4,50:-42.9,60:-40.2,70:-37.2,80:-34.0,90:-30.5,100:-26.7,110:-22.7,120:-18.5,130:-14.0,140:-9.4
ATGSeedDiag: seed=1@4,86/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(10.4) imip=38/49 pass=10100 acc=-1 ipm=149.0,82.9 inv=151.3,47.4 | 2(1.3) imip=0/3 pass=10111 acc=-1 ipm=114.0,116.2 inv=149.1,104.0
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/18 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.2/3.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,106) md=42/1/67 cxcy=84.0,119.6 guide=-44.11 atg=60.0/60.0/60.0 pure=-12.74/-12.70 yaw=3970 cmd=4170 actual=2472 signed=0 rps=0/7186:4688/6734 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.42@111,105 dx=26.6 idx=12/30 dist=40/77 right=1:-29.60@114,90 dx=29.9 idx=0/3 dist=6/6 sel=1:-45.73@122,106 dx=38.0 idx=0/20 dist=40/60 edge=1:-34.39@115.0,97.5 dx=31.0 width=37.2 l=113,79 r=117,116
CxScan: raw_ref=80.0 edge=115.0,97.5 best_raw_x=140 best_err=-9.99 best_cxcy=107.0,119.7 scan=0:-53.9,10:-52.1,20:-50.1,30:-48.0,40:-45.7,50:-43.2,60:-40.5,70:-37.6,80:-34.4,90:-30.9,100:-27.2,110:-23.3,120:-19.0,130:-14.6,140:-10.0
ATGSeedDiag: seed=1@4,86/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(13.2) imip=35/49 pass=10100 acc=-1 ipm=142.6,81.1 inv=142.0,46.1 | 2(3.3) imip=0/3 pass=10111 acc=-1 ipm=114.4,116.2 inv=150.1,104.2
frame=913 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/3 raw=153/16 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.7/4.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(118,106) md=40/1/65 cxcy=84.0,119.6 guide=-43.45 atg=60.0/60.0/60.0 pure=-12.78/-12.78 yaw=3910 cmd=4110 actual=2518 signed=0 rps=0/7157:5436/8331 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/3 centerNum=49/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-35.88@111,106 dx=26.9 idx=12/30 dist=40/76 right=1:-28.58@113,90 dx=28.5 idx=0/2 dist=4/4 sel=1:-45.92@122,106 dx=38.3 idx=0/20 dist=40/58 edge=1:-33.52@114.0,97.5 dx=30.0 width=37.1 l=113,79 r=115,116
CxScan: raw_ref=80.0 edge=114.0,97.5 best_raw_x=140 best_err=-8.77 best_cxcy=107.0,119.7 scan=0:-53.4,10:-51.6,20:-49.6,30:-47.5,40:-45.1,50:-42.6,60:-39.8,70:-36.8,80:-33.5,90:-30.0,100:-26.2,110:-22.2,120:-17.9,130:-13.4,140:-8.8
ATGSeedDiag: seed=1@4,87/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(9.7) imip=0/20 pass=10110 acc=-1 ipm=64.5,94.0 inv=48.3,59.7 | 1(4.0) imip=0/2 pass=10111 acc=-1 ipm=113.0,116.7 inv=147.7,105.7
frame=914 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/2 raw=153/12 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(118,106) md=40/1/65 cxcy=84.0,119.6 guide=-43.18 atg=60.0/60.0/60.0 pure=-12.77/-12.77 yaw=3886 cmd=4086 actual=2565 signed=0 rps=0/7146:4251/6729 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/2 centerNum=49/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.19@113,106 dx=29.0 idx=12/31 dist=41/75 right=1:-28.95@113,91 dx=28.8 idx=0/1 dist=2/2 sel=1:-46.45@123,106 dx=39.0 idx=0/20 dist=40/58 edge=1:-34.11@114.0,98.5 dx=30.0 width=37.1 l=113,80 r=115,117
CxScan: raw_ref=80.0 edge=114.0,98.5 best_raw_x=140 best_err=-8.96 best_cxcy=107.0,119.7 scan=0:-54.1,10:-52.2,20:-50.3,30:-48.1,40:-45.8,50:-43.2,60:-40.4,70:-37.4,80:-34.1,90:-30.6,100:-26.7,110:-22.6,120:-18.3,130:-13.7,140:-9.0
ATGSeedDiag: seed=1@4,88/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(11.3) imip=30/48 pass=10110 acc=-1 ipm=131.7,79.7 inv=128.4,45.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=915 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/2 raw=153/10 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(119,106) md=41/1/66 cxcy=84.0,119.6 guide=-43.41 atg=60.0/60.0/60.0 pure=-12.70/-12.70 yaw=3907 cmd=4107 actual=2613 signed=0 rps=0/7156:4506/7378 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/2 centerNum=49/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.52@113,106 dx=29.4 idx=12/31 dist=41/75 right=1:-30.07@114,91 dx=30.2 idx=0/1 dist=2/2 sel=1:-46.57@123,106 dx=39.2 idx=0/20 dist=40/58 edge=1:-34.11@114.0,98.5 dx=30.0 width=37.1 l=113,80 r=115,117
CxScan: raw_ref=80.0 edge=114.0,98.5 best_raw_x=140 best_err=-8.96 best_cxcy=107.0,119.7 scan=0:-54.1,10:-52.2,20:-50.3,30:-48.1,40:-45.8,50:-43.2,60:-40.4,70:-37.4,80:-34.1,90:-30.6,100:-26.7,110:-22.6,120:-18.3,130:-13.7,140:-9.0
ATGSeedDiag: seed=1@4,88/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(10.5) imip=30/48 pass=10110 acc=-1 ipm=131.7,79.7 inv=128.5,45.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=916 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/2 raw=152/8 sel=49/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(118,106) md=40/1/67 cxcy=84.0,119.6 guide=-43.54 atg=60.0/60.0/60.0 pure=-12.73/-12.67 yaw=3919 cmd=4119 actual=2673 signed=0 rps=0/7162:4260/7229 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/2 centerNum=49/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.57@112,106 dx=28.0 idx=11/30 dist=41/76 right=1:-31.17@116,91 dx=31.5 idx=0/1 dist=2/2 sel=1:-45.86@122,106 dx=38.2 idx=0/20 dist=40/60 edge=1:-33.66@113.5,98.5 dx=29.5 width=37.3 l=111,80 r=116,117
CxScan: raw_ref=80.0 edge=113.5,98.5 best_raw_x=140 best_err=-8.33 best_cxcy=107.0,119.7 scan=0:-53.8,10:-52.0,20:-50.0,30:-47.8,40:-45.4,50:-42.9,60:-40.0,70:-37.0,80:-33.7,90:-30.1,100:-26.2,110:-22.1,120:-17.7,130:-13.1,140:-8.3
ATGSeedDiag: seed=1@5,88/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(10.3) imip=30/48 pass=10110 acc=-1 ipm=132.2,79.7 inv=128.9,45.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/1 raw=153/7 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(119,106) md=40/1/65 cxcy=84.0,119.6 guide=-44.65 atg=60.0/60.0/60.0 pure=-12.76/-12.76 yaw=4019 cmd=4219 actual=2727 signed=0 rps=0/7210:4327/7536 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/1 centerNum=49/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.15@114,107 dx=29.5 idx=12/31 dist=41/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-46.84@124,106 dx=39.5 idx=0/20 dist=40/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=113,80 r=-1,-1
ATGSeedDiag: seed=1@4,89/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(12.0) imip=30/48 pass=10110 acc=-1 ipm=131.9,79.7 inv=128.7,45.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=918 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/1 raw=153/5 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,106) md=41/1/64 cxcy=84.0,119.6 guide=-45.91 atg=60.0/60.0/60.0 pure=-12.84/-12.84 yaw=4132 cmd=4332 actual=2781 signed=0 rps=0/7264:4346/7491 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/1 centerNum=49/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.31@114,107 dx=29.5 idx=12/31 dist=41/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-47.01@124,106 dx=39.8 idx=0/20 dist=40/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=114,81 r=-1,-1
ATGSeedDiag: seed=1@4,89/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=38(11.5) imip=28/48 pass=10110 acc=-1 ipm=127.4,79.7 inv=123.7,45.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=919 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/1 raw=153/2 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.2/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,107) md=40/1/64 cxcy=84.0,119.6 guide=-45.93 atg=60.0/60.0/60.0 pure=-12.94/-12.94 yaw=4134 cmd=4334 actual=2826 signed=0 rps=0/7265:4150/6993 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/1 centerNum=49/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.49@114,107 dx=29.6 idx=12/31 dist=41/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.30@124,107 dx=40.2 idx=0/20 dist=40/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=114,81 r=-1,-1
ATGSeedDiag: seed=1@4,90/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(10.2) imip=30/48 pass=10110 acc=-1 ipm=132.4,80.9 inv=130.3,46.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=920 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,107) md=40/1/63 cxcy=84.0,119.6 guide=-46.13 atg=60.0/60.0/60.0 pure=-13.10/-13.10 yaw=4152 cmd=4352 actual=2849 signed=0 rps=0/7274:4565/7573 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.71@113,107 dx=29.5 idx=12/31 dist=40/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.52@125,107 dx=40.5 idx=0/20 dist=40/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=114,81 r=-1,-1
ATGSeedDiag: seed=1@4,90/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=39(11.7) imip=29/47 pass=10110 acc=-1 ipm=130.2,81.0 inv=127.8,46.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=921 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=153/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.6/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,107) md=40/1/63 cxcy=84.0,119.6 guide=-46.13 atg=60.0/60.0/60.0 pure=-13.03/-13.03 yaw=4152 cmd=4352 actual=2888 signed=0 rps=0/7274:4846/8149 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-41.09@115,107 dx=31.3 idx=12/32 dist=41/71 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.54@125,107 dx=40.5 idx=0/20 dist=40/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=114,81 r=-1,-1
ATGSeedDiag: seed=1@4,90/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(11.6) imip=30/47 pass=10110 acc=-1 ipm=132.5,81.1 inv=130.6,46.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=48/0 raw=152/0 sel=48/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,107) md=40/1/63 cxcy=84.0,119.6 guide=-46.13 atg=60.0/60.0/60.0 pure=-12.97/-12.97 yaw=4152 cmd=4352 actual=2938 signed=0 rps=0/7274:4837/7750 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=48/0 centerNum=48/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=48/29 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-40.02@114,107 dx=30.2 idx=12/31 dist=41/72 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.62@125,107 dx=40.7 idx=0/20 dist=40/56 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=114,81 r=-1,-1
ATGSeedDiag: seed=1@5,90/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(11.5) imip=34/47 pass=10110 acc=-1 ipm=142.0,82.4 inv=142.7,47.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/0 raw=153/0 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.6/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,107) md=40/1/65 cxcy=84.0,119.6 guide=-46.13 atg=60.0/60.0/60.0 pure=-12.89/-12.89 yaw=4152 cmd=4352 actual=2974 signed=0 rps=0/7274:5272/8102 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/0 centerNum=49/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.83@114,107 dx=30.0 idx=12/31 dist=40/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-48.63@125,107 dx=40.7 idx=0/20 dist=40/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=114,81 r=-1,-1
ATGSeedDiag: seed=1@4,91/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(10.6) imip=36/48 pass=10100 acc=-1 ipm=146.1,83.7 inv=148.9,48.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T15:19:48+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive145
```
