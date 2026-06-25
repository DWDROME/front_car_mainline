# drive171

- commit: aa6d2e2
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive171-front_car_circle_drive171.log
- remote_log: /tmp/front_car_circle_drive171.log
- started_at: 2026-06-25T20:54:36+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive171 6
```

3628 /tmp/front_car_circle_drive171.log
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@2,41 ray=-1,-1 sharp=0 raw=32.6,71.6 th=146
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@4 seed=33,74 hit=1@15,38 ray=-1,-2 sharp=0 raw=33.2,74.9 th=89
ATGCircleEntryProbe: side=L A=1@4(raw=31,79) B=0 ret=0 reason=no_extreme hits=36 range=64..29
frame=879 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/124 raw=60/105 sel=124/126 src=11 far=0/0 far_raw=0/0 l=1@4/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 ref=0 A=0@-1,-1#0 B=0@-1,-1#-1 C=0@-1,-1#0 conf=94.4/7.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(85,78) md=41/1/136 cxcy=84.0,119.6 guide=-1.24 atg=2.0/1.0/2.0 pure=-0.61/-0.53 yaw=42 cmd=128 actual=-1 signed=0 rps=4796/5147:0/0 duty=24/28 pwm=PWM2:24/PWM1:28 motor=2:24/1:28
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@4/0@-1 nearNum=12/124 centerNum=12/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.45@54,83 dx=-29.7 idx=0/11 dist=27/27 right=1:-1.38@86,74 dx=1.6 idx=0/17 dist=42/254 sel=1:-1.41@86,73 dx=1.7 idx=0/20 dist=40/250 edge=1:6.34@78.0,88.5 dx=-6.0 width=77.4 l=44,107 r=112,70
CxScan: raw_ref=80.0 edge=78.0,88.5 best_raw_x=65 best_err=0.29 best_cxcy=78.3,119.5 scan=0:-24.6,10:-21.1,20:-17.5,30:-13.7,40:-9.8,50:-5.8,60:-1.7,70:2.3,80:6.3,90:10.3,100:14.1,110:17.9,120:21.4,130:24.8,140:28.0
ATGSeedDiag: seed=1@18,107/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(94.4) imip=0/11 pass=11111 acc=4 ipm=58.8,106.6 inv=31.2,79.9 | 1(7.1) imip=0/11 pass=10111 acc=-1 ipm=108.5,114.3 inv=132.8,98.1
ATGCircleEntryInnerHit: side=L near=1@4 seed=33,74 hit=1@15,38 ray=-1,-2 sharp=0 raw=33.2,74.9 th=89
ATGCircleEntryProbe: side=L A=1@4(raw=31,79) B=0 ret=0 reason=no_extreme hits=36 range=64..29
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
frame=881 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/124 raw=61/105 sel=124/126 src=11 far=0/0 far_raw=0/0 l=1@5/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 ref=0 A=0@-1,-1#0 B=0@-1,-1#-1 C=0@-1,-1#0 conf=95.3/7.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(85,78) md=41/1/136 cxcy=84.0,119.6 guide=-1.12 atg=2.0/1.0/2.0 pure=-0.61/-0.53 yaw=38 cmd=115 actual=0 signed=0 rps=4817/5132:0/0 duty=24/28 pwm=PWM2:24/PWM1:28 motor=2:24/1:28
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@5/0@-1 nearNum=12/124 centerNum=12/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:25.82@55,83 dx=-28.7 idx=0/11 dist=27/27 right=1:-1.38@86,74 dx=1.6 idx=0/17 dist=41/253 sel=1:-1.41@86,73 dx=1.7 idx=0/20 dist=40/250 edge=1:6.34@78.0,88.5 dx=-6.0 width=77.4 l=44,107 r=112,70
CxScan: raw_ref=80.0 edge=78.0,88.5 best_raw_x=65 best_err=0.29 best_cxcy=78.3,119.5 scan=0:-24.6,10:-21.1,20:-17.5,30:-13.7,40:-9.8,50:-5.8,60:-1.7,70:2.3,80:6.3,90:10.3,100:14.1,110:17.9,120:21.4,130:24.8,140:28.0
ATGSeedDiag: seed=1@18,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(95.3) imip=0/11 pass=11111 acc=5 ipm=57.6,104.9 inv=30.6,76.6 | 1(7.1) imip=0/11 pass=10111 acc=-1 ipm=108.5,114.3 inv=132.8,98.1
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=69
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@4 seed=33,74 hit=1@15,38 ray=-1,-2 sharp=0 raw=33.2,74.9 th=89
ATGCircleEntryProbe: side=L A=1@4(raw=31,79) B=0 ret=0 reason=no_extreme hits=36 range=64..29
frame=886 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/124 raw=60/105 sel=124/126 src=11 far=0/0 far_raw=0/0 l=1@4/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 ref=0 A=0@-1,-1#0 B=0@-1,-1#-1 C=0@-1,-1#0 conf=94.4/7.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(85,78) md=41/1/136 cxcy=84.0,119.6 guide=-1.24 atg=2.0/1.0/2.0 pure=-0.61/-0.53 yaw=42 cmd=128 actual=-1 signed=0 rps=4796/5148:0/0 duty=24/28 pwm=PWM2:24/PWM1:28 motor=2:24/1:28
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@4/0@-1 nearNum=12/124 centerNum=12/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.45@54,83 dx=-29.7 idx=0/11 dist=27/27 right=1:-1.38@86,74 dx=1.6 idx=0/17 dist=41/253 sel=1:-1.41@86,73 dx=1.7 idx=0/20 dist=40/250 edge=1:6.34@78.0,88.5 dx=-6.0 width=77.4 l=44,107 r=112,70
CxScan: raw_ref=80.0 edge=78.0,88.5 best_raw_x=65 best_err=0.29 best_cxcy=78.3,119.5 scan=0:-24.6,10:-21.1,20:-17.5,30:-13.7,40:-9.8,50:-5.8,60:-1.7,70:2.3,80:6.3,90:10.3,100:14.1,110:17.9,120:21.4,130:24.8,140:28.0
ATGSeedDiag: seed=1@18,107/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(94.4) imip=0/11 pass=11111 acc=4 ipm=58.8,106.6 inv=31.2,79.9 | 1(7.2) imip=0/11 pass=10111 acc=-1 ipm=108.5,114.3 inv=132.8,98.1
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
frame=887 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/124 raw=61/105 sel=124/126 src=11 far=0/0 far_raw=0/0 l=1@5/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 ref=0 A=0@-1,-1#0 B=0@-1,-1#-1 C=0@-1,-1#0 conf=95.3/7.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(85,78) md=41/1/136 cxcy=84.0,119.6 guide=-1.24 atg=2.0/1.0/2.0 pure=-0.61/-0.53 yaw=42 cmd=128 actual=-1 signed=0 rps=4796/5148:0/0 duty=24/28 pwm=PWM2:24/PWM1:28 motor=2:24/1:28
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@5/0@-1 nearNum=12/124 centerNum=12/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:25.82@55,83 dx=-28.7 idx=0/11 dist=27/27 right=1:-1.38@86,74 dx=1.6 idx=0/17 dist=42/254 sel=1:-1.41@86,73 dx=1.7 idx=0/20 dist=40/250 edge=1:6.34@78.0,88.5 dx=-6.0 width=77.4 l=44,107 r=112,70
CxScan: raw_ref=80.0 edge=78.0,88.5 best_raw_x=65 best_err=0.29 best_cxcy=78.3,119.5 scan=0:-24.6,10:-21.1,20:-17.5,30:-13.7,40:-9.8,50:-5.8,60:-1.7,70:2.3,80:6.3,90:10.3,100:14.1,110:17.9,120:21.4,130:24.8,140:28.0
ATGSeedDiag: seed=1@18,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(95.3) imip=0/11 pass=11111 acc=5 ipm=57.6,104.9 inv=30.6,76.6 | 1(7.2) imip=0/11 pass=10111 acc=-1 ipm=108.5,114.3 inv=132.8,98.1
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@4 seed=33,74 hit=1@15,38 ray=-1,-2 sharp=0 raw=33.2,74.9 th=89
ATGCircleEntryProbe: side=L A=1@4(raw=31,79) B=0 ret=0 reason=no_extreme hits=36 range=64..29
frame=889 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/124 raw=60/105 sel=124/126 src=11 far=0/0 far_raw=0/0 l=1@4/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 ref=0 A=0@-1,-1#0 B=0@-1,-1#-1 C=0@-1,-1#0 conf=94.4/7.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(85,78) md=41/1/136 cxcy=84.0,119.6 guide=-1.24 atg=2.0/1.0/2.0 pure=-0.61/-0.53 yaw=42 cmd=129 actual=-1 signed=0 rps=4795/5149:0/0 duty=24/28 pwm=PWM2:24/PWM1:28 motor=2:24/1:28
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@4/0@-1 nearNum=12/124 centerNum=12/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.45@54,83 dx=-29.7 idx=0/11 dist=27/27 right=1:-1.38@86,74 dx=1.6 idx=0/17 dist=41/253 sel=1:-1.41@86,73 dx=1.7 idx=0/20 dist=40/250 edge=1:6.34@78.0,88.5 dx=-6.0 width=77.4 l=44,107 r=112,70
CxScan: raw_ref=80.0 edge=78.0,88.5 best_raw_x=65 best_err=0.29 best_cxcy=78.3,119.5 scan=0:-24.6,10:-21.1,20:-17.5,30:-13.7,40:-9.8,50:-5.8,60:-1.7,70:2.3,80:6.3,90:10.3,100:14.1,110:17.9,120:21.4,130:24.8,140:28.0
ATGSeedDiag: seed=1@18,107/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(94.4) imip=0/11 pass=11111 acc=4 ipm=58.8,106.6 inv=31.2,79.9 | 1(7.2) imip=0/11 pass=10111 acc=-1 ipm=108.5,114.3 inv=132.8,98.1
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=69
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
frame=890 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/124 raw=61/105 sel=124/126 src=11 far=0/0 far_raw=0/0 l=1@5/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 ref=0 A=0@-1,-1#0 B=0@-1,-1#-1 C=0@-1,-1#0 conf=95.3/7.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(85,78) md=41/1/136 cxcy=84.0,119.6 guide=-1.24 atg=2.0/1.0/2.0 pure=-0.61/-0.53 yaw=42 cmd=128 actual=-1 signed=0 rps=4796/5148:0/0 duty=24/28 pwm=PWM2:24/PWM1:28 motor=2:24/1:28
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@5/0@-1 nearNum=12/124 centerNum=12/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:25.82@55,83 dx=-28.7 idx=0/11 dist=27/27 right=1:-1.38@86,74 dx=1.6 idx=0/17 dist=41/253 sel=1:-1.41@86,73 dx=1.7 idx=0/20 dist=40/250 edge=1:6.34@78.0,88.5 dx=-6.0 width=77.4 l=44,107 r=112,70
CxScan: raw_ref=80.0 edge=78.0,88.5 best_raw_x=65 best_err=0.29 best_cxcy=78.3,119.5 scan=0:-24.6,10:-21.1,20:-17.5,30:-13.7,40:-9.8,50:-5.8,60:-1.7,70:2.3,80:6.3,90:10.3,100:14.1,110:17.9,120:21.4,130:24.8,140:28.0
ATGSeedDiag: seed=1@18,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(95.3) imip=0/11 pass=11111 acc=5 ipm=57.6,104.9 inv=30.6,76.6 | 1(7.2) imip=0/11 pass=10111 acc=-1 ipm=108.5,114.3 inv=132.8,98.1
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=69
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=69
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@5 seed=32,71 hit=1@15,37 ray=-1,-2 sharp=0 raw=32.6,71.6 th=70
ATGCircleEntryProbe: side=L A=1@5(raw=30,76) B=0 ret=0 reason=no_extreme hits=36 range=61..26
ATGCircleEntryInnerHit: side=L near=1@4 seed=33,74 hit=1@15,38 ray=-1,-2 sharp=0 raw=33.2,74.9 th=89
ATGCircleEntryProbe: side=L A=1@4(raw=31,79) B=0 ret=0 reason=no_extreme hits=36 range=64..29
frame=895 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=12/124 raw=60/105 sel=124/126 src=11 far=0/0 far_raw=0/0 l=1@4/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 ref=0 A=0@-1,-1#0 B=0@-1,-1#-1 C=0@-1,-1#0 conf=94.4/7.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(85,78) md=41/1/136 cxcy=84.0,119.6 guide=-1.24 atg=2.0/1.0/2.0 pure=-0.61/-0.53 yaw=42 cmd=127 actual=0 signed=0 rps=4798/5146:0/0 duty=24/28 pwm=PWM2:24/PWM1:28 motor=2:24/1:28
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@4/0@-1 nearNum=12/124 centerNum=12/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:26.45@54,83 dx=-29.7 idx=0/11 dist=27/27 right=1:-1.38@86,74 dx=1.6 idx=0/17 dist=41/253 sel=1:-1.41@86,73 dx=1.7 idx=0/20 dist=40/250 edge=1:6.34@78.0,88.5 dx=-6.0 width=77.4 l=44,107 r=112,70
CxScan: raw_ref=80.0 edge=78.0,88.5 best_raw_x=65 best_err=0.29 best_cxcy=78.3,119.5 scan=0:-24.6,10:-21.1,20:-17.5,30:-13.7,40:-9.8,50:-5.8,60:-1.7,70:2.3,80:6.3,90:10.3,100:14.1,110:17.9,120:21.4,130:24.8,140:28.0
ATGSeedDiag: seed=1@18,107/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(94.4) imip=0/11 pass=11111 acc=4 ipm=58.8,106.6 inv=31.2,79.9 | 1(7.2) imip=0/11 pass=10111 acc=-1 ipm=108.5,114.3 inv=132.8,98.1

- stopped_at: 2026-06-25T20:54:50+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive171
```
