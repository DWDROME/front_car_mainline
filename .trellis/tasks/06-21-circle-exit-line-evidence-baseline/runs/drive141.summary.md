# drive141

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive141-front_car_circle_drive141.log
- remote_log: /tmp/front_car_circle_drive141.log
- started_at: 2026-06-22T15:15:19+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive141 6
```

4299 /tmp/front_car_circle_drive141.log
frame=901 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/0 raw=170/0 sel=8/11 far=0/0 far_raw=0/0 l=1@9/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(84,100) md=23/0/23 cxcy=84.0,119.6 guide=0.03 atg=0.0/0.0/0.0 pure=0.30/0.30 yaw=-1 cmd=-201 actual=1020 signed=0 rps=5275/4724:4066/4818 duty=13/13 pwm=PWM2:13/PWM1:13 motor=2:13/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@9/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/11 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-0.09@84,99 dx=0.1 idx=3/7 dist=24/24 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:0.66@84,100 dx=-0.5 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,85/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(95.5) imip=0/19 pass=11111 acc=9 ipm=61.7,94.2 inv=44.2,60.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=903 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=8/0 raw=170/0 sel=8/13 far=0/0 far_raw=0/0 l=1@9/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=92.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(84,96) md=25/0/25 cxcy=84.0,119.6 guide=0.03 atg=0.0/0.0/0.0 pure=-0.09/-0.09 yaw=-1 cmd=-201 actual=944 signed=0 rps=5274/4724:4671/5248 duty=13/12 pwm=PWM2:13/PWM1:12 motor=2:13/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@9/0@-1 nearNum=8/0 centerNum=8/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/13 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-0.49@84,96 dx=0.4 idx=2/7 dist=28/28 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-0.21@84,96 dx=0.2 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,86/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(92.3) imip=0/19 pass=11111 acc=9 ipm=60.2,93.6 inv=42.4,59.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=904 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=7/0 raw=170/0 sel=7/11 far=0/0 far_raw=0/0 l=1@8/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.1/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(82,99) md=21/0/21 cxcy=84.0,119.6 guide=2.66 atg=-1.0/0.0/0.0 pure=0.97/0.97 yaw=-68 cmd=-268 actual=905 signed=0 rps=5307/4573:4801/5395 duty=13/12 pwm=PWM2:13/PWM1:12 motor=2:13/1:12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@8/0@-1 nearNum=7/0 centerNum=7/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/11 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:1.00@83,97 dx=-0.8 idx=2/6 dist=25/25 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:2.17@82,99 dx=-1.6 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@5,86/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(96.1) imip=0/18 pass=11111 acc=8 ipm=60.3,95.7 inv=41.5,61.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=906 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/0 raw=170/0 sel=6/11 far=0/0 far_raw=0/0 l=1@7/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.6/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(81,100) md=22/0/22 cxcy=84.0,119.6 guide=4.06 atg=-5.0/-2.0/-2.0 pure=1.89/1.89 yaw=-243 cmd=-443 actual=850 signed=0 rps=5391/4176:4826/5384 duty=13/10 pwm=PWM2:13/PWM1:10 motor=2:13/1:10
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@7/0@-1 nearNum=6/0 centerNum=6/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/11 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:3.14@82,99 dx=-2.4 idx=1/5 dist=25/25 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:4.15@81,100 dx=-3.1 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,88/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(95.6) imip=0/17 pass=11111 acc=7 ipm=58.9,98.2 inv=37.9,65.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=908 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/0 raw=170/0 sel=5/11 far=0/0 far_raw=0/0 l=1@6/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.6/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(80,101) md=21/0/21 cxcy=84.0,119.6 guide=5.52 atg=-10.0/-4.0/-4.0 pure=2.62/2.62 yaw=-331 cmd=-531 actual=729 signed=0 rps=5434/3978:5153/5560 duty=13/9 pwm=PWM2:13/PWM1:9 motor=2:13/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@6/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/11 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:4.65@80,99 dx=-3.5 idx=0/4 dist=24/24 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:5.72@80,101 dx=-4.2 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@5,89/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=6(95.6) imip=0/16 pass=11111 acc=6 ipm=58.0,100.1 inv=35.2,68.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=910 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/0 raw=170/0 sel=5/12 far=0/0 far_raw=0/0 l=1@6/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.2/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(80,98) md=23/0/23 cxcy=84.0,119.6 guide=5.15 atg=-8.0/-3.0/-3.0 pure=2.21/2.21 yaw=-309 cmd=-509 actual=581 signed=0 rps=5423/4028:5177/5451 duty=13/9 pwm=PWM2:13/PWM1:9 motor=2:13/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@6/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/12 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:5.15@80,98 dx=-4.1 idx=0/4 dist=26/26 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:5.20@80,98 dx=-4.1 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,90/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=6(96.2) imip=0/16 pass=11111 acc=6 ipm=57.7,100.4 inv=34.5,68.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=911 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/0 raw=170/0 sel=5/12 far=0/0 far_raw=0/0 l=1@6/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.1/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(79,97) md=24/0/24 cxcy=84.0,119.6 guide=6.28 atg=-11.0/-4.0/-4.0 pure=2.38/2.38 yaw=-377 cmd=-577 actual=505 signed=0 rps=5456/3875:5213/5365 duty=13/9 pwm=PWM2:13/PWM1:9 motor=2:13/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@6/0@-1 nearNum=5/0 centerNum=5/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/12 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:5.28@80,96 dx=-4.3 idx=0/4 dist=27/27 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:5.68@79,97 dx=-4.5 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,91/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=6(93.1) imip=0/16 pass=11111 acc=6 ipm=57.1,100.3 inv=33.6,68.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/0 raw=170/0 sel=4/10 far=0/0 far_raw=0/0 l=1@5/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.1/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(78,101) md=19/0/19 cxcy=84.0,119.6 guide=8.23 atg=-22.0/-8.0/-8.0 pure=3.73/3.73 yaw=-494 cmd=-694 actual=426 signed=0 rps=5512/3610:4899/5029 duty=13/8 pwm=PWM2:13/PWM1:8 motor=2:13/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@5/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/10 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:7.02@79,99 dx=-5.4 idx=0/3 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:8.21@78,101 dx=-6.0 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,92/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(96.1) imip=0/15 pass=11111 acc=5 ipm=56.8,102.8 inv=31.0,72.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=913 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/0 raw=170/0 sel=4/11 far=0/0 far_raw=0/0 l=1@5/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.4/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(79,99) md=21/0/21 cxcy=84.0,119.6 guide=6.56 atg=-15.0/-6.0/-6.0 pure=3.04/3.04 yaw=-394 cmd=-594 actual=345 signed=0 rps=5464/3836:5150/5322 duty=13/9 pwm=PWM2:13/PWM1:9 motor=2:13/1:9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@5/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/11 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:6.94@79,98 dx=-5.4 idx=0/3 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:7.05@79,99 dx=-5.5 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,93/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(97.4) imip=0/15 pass=11111 acc=5 ipm=57.2,103.3 inv=31.2,73.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=914 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/0 raw=170/0 sel=4/11 far=0/0 far_raw=0/0 l=1@5/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.3/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(78,98) md=22/0/22 cxcy=84.0,119.6 guide=7.68 atg=-18.0/-7.0/-7.0 pure=3.13/3.13 yaw=-461 cmd=-661 actual=281 signed=0 rps=5496/3684:5306/5530 duty=13/8 pwm=PWM2:13/PWM1:8 motor=2:13/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@5/0@-1 nearNum=4/0 centerNum=4/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/11 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:6.87@79,98 dx=-5.4 idx=0/3 dist=24/24 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:7.28@78,98 dx=-5.7 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,94/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(96.3) imip=0/15 pass=11111 acc=5 ipm=57.3,103.4 inv=31.3,73.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=916 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/0 raw=170/0 sel=3/10 far=0/0 far_raw=0/0 l=1@4/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(77,100) md=19/0/19 cxcy=84.0,119.6 guide=9.35 atg=-28.0/-11.0/-11.0 pure=4.03/4.03 yaw=-561 cmd=-761 actual=230 signed=0 rps=5544/3458:5691/5823 duty=12/6 pwm=PWM2:12/PWM1:6 motor=2:12/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@4/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/10 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:8.70@77,100 dx=-6.6 idx=0/2 dist=22/22 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:9.07@77,100 dx=-6.8 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,96/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(95.9) imip=0/14 pass=11111 acc=4 ipm=56.3,105.9 inv=27.3,78.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=918 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/0 raw=170/0 sel=3/10 far=0/0 far_raw=0/0 l=1@4/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=97.8/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(76,100) md=19/0/19 cxcy=84.0,119.6 guide=10.65 atg=-36.0/-14.0/-14.0 pure=4.53/4.53 yaw=-639 cmd=-839 actual=186 signed=0 rps=5582/3282:6092/5813 duty=12/6 pwm=PWM2:12/PWM1:6 motor=2:12/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@4/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/10 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:9.15@77,98 dx=-7.2 idx=0/2 dist=24/24 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:10.28@76,100 dx=-7.7 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,97/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(97.8) imip=0/14 pass=11111 acc=4 ipm=56.7,106.4 inv=27.6,79.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=919 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/0 raw=57/0 sel=3/11 far=0/0 far_raw=0/0 l=1@4/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.9/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(76,98) md=21/0/21 cxcy=84.0,119.6 guide=10.19 atg=-32.0/-13.0/-13.0 pure=4.12/4.12 yaw=-611 cmd=-811 actual=124 signed=0 rps=5568/3345:5813/5538 duty=12/6 pwm=PWM2:12/PWM1:6 motor=2:12/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@4/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/11 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:9.36@77,97 dx=-7.5 idx=0/2 dist=24/24 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:9.78@76,98 dx=-7.7 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,98/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(94.9) imip=0/14 pass=11111 acc=4 ipm=56.4,106.2 inv=27.1,79.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=920 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=53/0 sel=2/10 far=0/0 far_raw=0/0 l=1@3/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.1/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(76,100) md=19/0/19 cxcy=84.0,119.6 guide=10.65 atg=-37.0/-15.0/-15.0 pure=4.75/4.75 yaw=-639 cmd=-839 actual=48 signed=0 rps=5582/3282:5824/5467 duty=12/6 pwm=PWM2:12/PWM1:6 motor=2:12/1:6
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@3/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/10 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:11.27@75,99 dx=-8.8 idx=0/1 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:10.82@76,100 dx=-8.1 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@5,98/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(95.1) imip=0/13 pass=11111 acc=3 ipm=55.7,108.3 inv=23.7,83.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=51/0 sel=2/10 far=0/0 far_raw=0/0 l=1@3/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.1/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(76,100) md=19/0/19 cxcy=84.0,119.6 guide=10.65 atg=-38.0/-15.0/-15.0 pure=4.87/4.87 yaw=-639 cmd=-839 actual=-124 signed=0 rps=5582/3282:4764/4412 duty=14/8 pwm=PWM2:14/PWM1:8 motor=2:14/1:8
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@3/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/10 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:11.59@75,99 dx=-9.0 idx=0/1 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:11.11@76,100 dx=-8.3 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,100/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(96.1) imip=0/13 pass=11111 acc=3 ipm=56.0,109.2 inv=23.2,85.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=51/0 sel=2/10 far=0/0 far_raw=0/0 l=1@3/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=98.2/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(76,100) md=19/0/19 cxcy=84.0,119.6 guide=10.65 atg=-38.0/-15.0/-15.0 pure=4.81/4.81 yaw=-639 cmd=-839 actual=-200 signed=0 rps=5582/3282:5159/4830 duty=13/7 pwm=PWM2:13/PWM1:7 motor=2:13/1:7
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@3/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/10 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:11.41@75,99 dx=-8.9 idx=0/1 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:10.97@76,100 dx=-8.2 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@4,102/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(98.2) imip=0/13 pass=11111 acc=3 ipm=56.4,109.6 inv=23.4,86.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T15:15:31+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive141
```
