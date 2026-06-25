# drive83

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive83-front_car_circle_drive83.log
- remote_log: /tmp/front_car_circle_drive83.log
- started_at: 2026-06-22T06:03:14+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive83 6
```

3155 /tmp/front_car_circle_drive83.log
frame=579 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=170/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2205 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=225 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@52,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=582 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=2/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2235 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=11 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@46,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=584 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=170/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2253 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=188 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@43,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=585 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=2/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2262 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=124 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=588 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=3/0 raw=12/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.7/0.0/0.0/0.0 dist=2289 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=-129 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:62.5,115.3:29.6,102.6:2.7:10111/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=2.7/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:13.16@72,91 dx=-12.2 idx=0/2 dist=4/4 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=60,114 r=-1,-1
ATGSeedDiag: seed=1@35,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.7) imip=0/2 pass=10111 acc=-1 ipm=62.5,115.3 inv=29.6,102.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=589 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=2/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2297 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=-43 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@33,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=593 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/1 raw=2/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2329 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=261 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@25,108/1@145,87 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=594 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=6/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2338 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=102 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@23,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=598 line=0 track=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/0 raw=170/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2370 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=203 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=19.0,54.0/0.0,0.0 far_start=19,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@15,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
ATGCircleStall: circle_type=5 stalled 30 frames without selected line, reset to NONE
frame=599 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/0 raw=2/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=2378 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=258 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@13,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=600 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/0 raw=2/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=201 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@11,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=604 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=77 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=734 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=1/0 raw=170/0 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=-1 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@11,107/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=735 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/2598 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/49.0/49.0 pure=-7.23/-7.23 yaw=0 cmd=0 actual=-1 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T06:03:27+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive83
```
