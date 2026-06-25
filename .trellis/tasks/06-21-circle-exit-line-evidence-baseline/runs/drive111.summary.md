# drive111

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive111-front_car_circle_drive111.log
- remote_log: /tmp/front_car_circle_drive111.log
- started_at: 2026-06-22T07:23:31+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive111 6
```

1407 /tmp/front_car_circle_drive111.log
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-18.68@102,91 dx=17.5 idx=0/5 dist=33/273 sel=1:-18.87@103,88 dx=18.8 idx=0/16 dist=32/268 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=134,76
ATGSeedDiag: seed=0@-1,-1/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 23(3.9) imip=13/33 pass=10111 acc=-1 ipm=140.4,60.4 inv=123.7,33.3
frame=221 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/127 raw=170/86 sel=127/136 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=6/0/0/0 lost=0/0 conf=0.0/4.6/0.0/0.0 dist=677 begin=1284/0 m0=(84,119) ml=(103,90) md=33/1/150 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/45.0 pure=-4.20/-2.64 yaw=0 cmd=21 actual=-21 signed=1 rps=3772/3828:3125/2970 duty=10/12 pwm=PWM2:10/PWM1:12 motor=2:10/1:12
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/1:123.5,107.9:151.5,81.6:4.6:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/4.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/127 centerNum=1/127 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=127/136 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-19.25@102,92 dx=17.6 idx=0/4 dist=32/276 sel=1:-19.48@103,88 dx=19.3 idx=0/16 dist=32/270 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=136,75
ATGSeedDiag: seed=1@59,93/1@155,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(4.6) imip=0/11 pass=10111 acc=-1 ipm=123.5,107.9 inv=151.5,81.6
frame=223 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/126 raw=0/86 sel=126/135 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=8/0/0/0 lost=0/0 conf=0.0/4.6/0.0/0.0 dist=692 begin=1299/0 m0=(84,119) ml=(102,90) md=33/1/150 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/45.0 pure=-4.20/-2.64 yaw=0 cmd=42 actual=-42 signed=1 rps=3743/3857:2962/2709 duty=10/12 pwm=PWM2:10/PWM1:12 motor=2:10/1:12
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/1:123.5,107.9:151.5,81.6:4.6:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/4.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/126 centerNum=0/126 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=126/135 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-19.25@102,92 dx=17.6 idx=0/4 dist=32/274 sel=1:-19.32@103,88 dx=19.2 idx=0/16 dist=32/268 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=135,75
ATGSeedDiag: seed=0@-1,-1/1@155,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(4.6) imip=0/11 pass=10111 acc=-1 ipm=123.5,107.9 inv=151.5,81.6
frame=225 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=10/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=708 begin=1315/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=8 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@114,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=229 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=14/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=737 begin=1344/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=1 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@116,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=233 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=18/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=765 begin=1372/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=92 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@117,96 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=234 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=1/1 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=19/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=773 begin=1380/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=148 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@57,107/1@118,97 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=235 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=20/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=780 begin=1387/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=134 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@118,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=237 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=22/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=794 begin=1401/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=68 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@119,100 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=241 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=26/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=822 begin=1429/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=148 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@120,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=245 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=30/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=846 begin=1453/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=28 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=248 line=0 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=33/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=862 begin=1469/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=109 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/lost seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
ATGCircleStall: circle_type=1 stalled 30 frames without selected line, reset to NONE
frame=254 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=892 begin=1499/0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=64 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=255 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 begin=0/1499 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/44.0 pure=-4.21/-2.62 yaw=0 cmd=0 actual=55 signed=0 rps=0/0:0/0 duty=0/0 pwm=PWM2:0/PWM1:0 motor=2:0/1:0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T07:23:43+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive111
```
