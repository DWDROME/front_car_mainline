# drive126

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive126-front_car_circle_drive126.log
- remote_log: /tmp/front_car_circle_drive126.log
- started_at: 2026-06-22T14:56:06+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive126 6
```

5205 /tmp/front_car_circle_drive126.log
ATGSeedDiag: seed=1@42,90/1@138,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=921 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,92/1@139,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=923 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@44,95/1@125,102 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=924 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@45,98/1@135,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=925 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,92/1@135,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=926 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/2 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/none seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/2 centerNum=1/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,92/1@135,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=927 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/4 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/12.1/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/1:108.3,114.2:132.3,98.0:12.1:10111 seed_src=circle/none seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/12.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/4 centerNum=1/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@45,108/1@135,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(12.1) imip=0/3 pass=10111 acc=-1 ipm=108.3,114.2 inv=132.3,98.0
frame=928 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/2 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/none seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/2 centerNum=1/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@66,96/1@141,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=929 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,92/1@138,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=930 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/2 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/none seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/2 centerNum=1/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@36,91/1@138,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=931 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,92/1@131,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=932 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,91/1@135,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=933 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@41,92/1@135,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=934 line=1 track=0 cross=0 circle=3(CIRCLE_LEFT_IN) round=0 yroad=0 ramp=0 road=6 speed=0 near=1/1 raw=170/170 sel=92/17 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=1/0 conf=0.0/0.0/0.0/0.0 dist=36 begin=0/214 m0=(84,119) ml=(56,119) md=28/0/28 cxcy=84.0,119.6 guide=37.36 atg=-60.0/-60.0/-60.0 pure=20.82/20.82 yaw=-2242 cmd=-2442 actual=0 signed=1 rps=7147/453:0/0 duty=32/3 pwm=PWM2:32/PWM1:3 motor=2:32/1:3
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=circle/lost seed=40.0,91.8/0.0,0.0 far_start=40,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=1/0 not_have=0 final=92/17 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:57.82@56,125 dx=-27.9 idx=0/16 dist=32/32 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@31,99/1@122,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T14:56:19+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive126
```
