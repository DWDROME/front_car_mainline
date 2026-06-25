# drive59

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive59-front_car_circle_drive59.log
- remote_log: /tmp/front_car_circle_drive59.log
- started_at: 2026-06-22T03:51:17+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive59 6
```

2347 /tmp/front_car_circle_drive59.log
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=0/7 centerNum=0/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-166.06@84,144 dx=0.4 idx=3/6 dist=28/28 sel=1:-162.16@85,144 dx=0.5 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=80,119
ATGSeedDiag: seed=1@43,108/1@101,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(74.4) imip=0/6 pass=11111 acc=1 ipm=91.2,114.8 inv=94.9,100.1
frame=852 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=46/6 raw=157/37 sel=46/78 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=172.6/66.3/0.0/0.0 dist=0 m0=(84,119) ml=(115,113) md=33/1/166 cxcy=84.0,119.6 guide=-46.37 atg=60.0/14.0/0.0 pure=-10.47/-2.46 yaw=2782 cmd=2982 actual=-478 signed=0 rps=913/9087:4199/11499 duty=0/22 pwm=PWM2:0/PWM1:22 motor=2:0/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@1 nearNum=46/6 centerNum=46/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=46/78 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-46.09@111,117 dx=26.8 idx=4/13 dist=33/176 right=1:-116.35@86,144 dx=1.9 idx=2/5 dist=6/6 sel=1:-46.03@113,115 dx=29.0 idx=0/16 dist=32/154 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=107,87 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@101,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=21(172.6) imip=11/31 pass=11010 acc=-1 ipm=107.0,86.7 inv=104.1,51.3 | 1(66.3) imip=0/5 pass=11111 acc=1 ipm=91.0,114.7 inv=94.5,99.9
frame=853 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/7 raw=0/39 sel=7/13 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/79.2/0.0/0.0 dist=0 m0=(84,119) ml=(85,119) md=9/0/9 cxcy=84.0,119.6 guide=-2.36 atg=35.0/14.0/14.0 pure=-35.61/-35.61 yaw=60 cmd=260 actual=-431 signed=0 rps=4643/5357:4129/12265 duty=11/6 pwm=PWM2:11/PWM1:6 motor=2:11/1:6
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=0/7 centerNum=0/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-157.22@85,144 dx=0.6 idx=3/6 dist=28/28 sel=1:-153.08@85,144 dx=0.8 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=81,118
ATGSeedDiag: seed=1@44,108/1@102,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(79.2) imip=0/6 pass=11111 acc=1 ipm=91.8,114.7 inv=96.3,99.8
frame=855 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/7 raw=0/39 sel=7/13 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/77.1/0.0/0.0 dist=0 m0=(84,119) ml=(86,119) md=10/0/10 cxcy=84.0,119.6 guide=-4.77 atg=60.0/28.0/28.0 pure=-36.03/-36.03 yaw=122 cmd=322 actual=-284 signed=0 rps=4559/5441:3683/13117 duty=11/5 pwm=PWM2:11/PWM1:5 motor=2:11/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=0/7 centerNum=0/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-130.94@86,144 dx=1.7 idx=3/6 dist=28/28 sel=1:-128.27@86,144 dx=1.8 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=81,118
ATGSeedDiag: seed=1@44,108/1@103,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(77.1) imip=0/6 pass=11111 acc=1 ipm=92.2,114.5 inv=97.0,99.1
frame=856 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/7 raw=13/40 sel=7/13 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/81.4/0.0/0.0 dist=0 m0=(84,119) ml=(86,119) md=10/0/10 cxcy=84.0,119.6 guide=-4.77 atg=60.0/28.0/28.0 pure=-36.25/-36.25 yaw=122 cmd=322 actual=-199 signed=0 rps=4559/5441:4100/13150 duty=11/5 pwm=PWM2:11/PWM1:5 motor=2:11/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=2/7 centerNum=2/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=7/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:35.93@51,97 dx=-33.1 idx=0/1 dist=2/2 right=1:-128.94@86,144 dx=1.5 idx=3/6 dist=28/28 sel=1:-127.14@86,144 dx=1.5 idx=0/12 dist=24/24 edge=1:21.04@74.5,118.0 dx=-9.5 width=15.0 l=67,118 r=82,118
CxScan: raw_ref=80.0 edge=74.5,118.0 best_raw_x=55 best_err=-0.15 best_cxcy=74.4,119.5 scan=0:-40.9,10:-35.3,20:-28.8,30:-21.4,40:-13.3,50:-4.6,60:4.3,70:13.0,80:21.0,90:28.3,100:34.7,110:40.2,120:45.0,130:49.0,140:52.5
ATGSeedDiag: seed=1@44,108/1@104,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(81.4) imip=0/6 pass=11111 acc=1 ipm=92.8,114.4 inv=98.3,98.8
frame=857 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=27/7 raw=86/42 sel=27/25 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.0/91.2/0.0/0.0 dist=0 m0=(84,119) ml=(115,115) md=32/1/48 cxcy=84.0,119.6 guide=-48.02 atg=60.0/60.0/60.0 pure=-13.71/-13.71 yaw=2881 cmd=3081 actual=-108 signed=0 rps=777/9223:5422/14021 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@1 nearNum=27/7 centerNum=27/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=27/25 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-46.46@110,118 dx=25.6 idx=4/14 dist=33/57 right=1:-133.30@85,144 dx=1.1 idx=3/6 dist=6/6 sel=1:-47.18@113,116 dx=29.2 idx=0/16 dist=32/48 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=108,89 r=-1,-1
ATGSeedDiag: seed=1@45,108/1@105,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=15(12.0) imip=5/25 pass=10110 acc=-1 ipm=97.5,94.8 inv=95.3,60.3 | 1(91.2) imip=0/6 pass=11111 acc=1 ipm=93.6,114.5 inv=100.1,99.1
frame=858 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=27/7 raw=86/43 sel=27/25 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/92.7/0.0/0.0 dist=0 m0=(84,119) ml=(115,115) md=32/1/48 cxcy=84.0,119.6 guide=-48.46 atg=60.0/60.0/60.0 pure=-13.74/-13.74 yaw=2907 cmd=3107 actual=-32 signed=0 rps=741/9259:4610/10578 duty=0/23 pwm=PWM2:0/PWM1:23 motor=2:0/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@1 nearNum=27/7 centerNum=27/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=27/25 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-46.95@110,119 dx=25.8 idx=4/14 dist=33/57 right=1:-128.08@85,144 dx=1.2 idx=3/6 dist=6/6 sel=1:-47.11@113,116 dx=29.0 idx=0/16 dist=32/48 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=108,89 r=-1,-1
ATGSeedDiag: seed=1@45,108/1@106,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=16(12.5) imip=6/26 pass=10110 acc=-1 ipm=99.4,93.5 inv=97.4,58.7 | 1(92.7) imip=0/6 pass=11111 acc=1 ipm=94.1,114.4 inv=101.1,99.0
frame=859 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=22/7 raw=77/45 sel=22/21 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.7/94.3/0.0/0.0 dist=0 m0=(84,119) ml=(115,114) md=33/1/39 cxcy=84.0,119.6 guide=-47.96 atg=60.0/60.0/60.0 pure=-15.02/-15.02 yaw=2877 cmd=3077 actual=28 signed=0 rps=782/9218:4945/10889 duty=0/23 pwm=PWM2:0/PWM1:23 motor=2:0/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@1 nearNum=22/7 centerNum=22/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-46.31@109,119 dx=24.8 idx=4/13 dist=32/48 right=1:-109.01@86,143 dx=1.7 idx=3/6 dist=6/6 sel=1:-47.15@113,116 dx=29.0 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=107,89 r=-1,-1
ATGSeedDiag: seed=1@45,108/1@107,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=20(14.7) imip=10/21 pass=10110 acc=-1 ipm=107.4,89.0 inv=105.9,53.6 | 1(94.3) imip=0/6 pass=11111 acc=1 ipm=94.7,114.1 inv=102.2,98.1
frame=860 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=27/8 raw=83/45 sel=27/25 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.3/100.9/0.0/0.0 dist=0 m0=(84,119) ml=(115,114) md=32/1/47 cxcy=84.0,119.6 guide=-47.79 atg=60.0/60.0/60.0 pure=-13.61/-13.61 yaw=2868 cmd=3068 actual=86 signed=0 rps=796/9204:4398/11019 duty=0/23 pwm=PWM2:0/PWM1:23 motor=2:0/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@1 nearNum=27/8 centerNum=27/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=27/25 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-46.55@110,118 dx=25.9 idx=4/14 dist=33/57 right=1:-112.12@89,145 dx=4.7 idx=5/7 dist=4/4 sel=1:-46.63@113,115 dx=29.0 idx=0/16 dist=32/48 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=107,89 r=-1,-1
ATGSeedDiag: seed=1@45,108/1@108,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(12.3) imip=7/26 pass=10110 acc=-1 ipm=101.1,91.9 inv=99.0,56.8 | 1(100.9) imip=0/7 pass=11111 acc=1 ipm=95.1,114.2 inv=103.1,98.1
frame=861 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/8 raw=12/48 sel=8/13 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/96.6/0.0/0.0 dist=0 m0=(84,119) ml=(87,119) md=11/0/11 cxcy=84.0,119.6 guide=-7.16 atg=60.0/42.0/42.0 pure=-35.40/-35.40 yaw=430 cmd=630 actual=140 signed=0 rps=4137/5863:3862/12498 duty=10/7 pwm=PWM2:10/PWM1:7 motor=2:10/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=2/8 centerNum=2/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/13 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:38.16@49,99 dx=-34.6 idx=0/1 dist=2/2 right=1:-118.65@87,144 dx=3.1 idx=4/7 dist=27/27 sel=1:-118.64@87,144 dx=3.1 idx=0/12 dist=24/24 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=67,118 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@109,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(96.6) imip=0/7 pass=11111 acc=1 ipm=95.4,114.4 inv=104.1,99.0
frame=862 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/8 raw=13/48 sel=8/12 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/100.3/0.0/0.0 dist=0 m0=(84,119) ml=(88,119) md=6/0/6 cxcy=84.0,119.6 guide=-9.53 atg=60.0/56.0/56.0 pure=-35.28/-35.28 yaw=572 cmd=772 actual=170 signed=0 rps=3942/6058:3057/12570 duty=10/8 pwm=PWM2:10/PWM1:8 motor=2:10/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=2/8 centerNum=2/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:38.08@49,99 dx=-34.6 idx=0/1 dist=2/2 right=1:-112.23@88,144 dx=3.7 idx=5/7 dist=25/25 sel=1:-110.11@88,144 dx=3.8 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=67,118 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@109,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(100.3) imip=0/7 pass=11111 acc=1 ipm=95.7,114.1 inv=104.4,98.0
frame=863 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/8 raw=0/49 sel=8/12 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/97.0/0.0/0.0 dist=0 m0=(84,119) ml=(88,119) md=8/0/8 cxcy=84.0,119.6 guide=-9.53 atg=60.0/56.0/56.0 pure=-35.44/-35.44 yaw=572 cmd=772 actual=201 signed=0 rps=3942/6058:2780/13334 duty=10/7 pwm=PWM2:10/PWM1:7 motor=2:10/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=0/8 centerNum=0/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-112.74@87,144 dx=2.8 idx=4/7 dist=27/27 sel=1:-89.89@88,143 dx=4.0 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@110,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(97.0) imip=0/7 pass=11111 acc=1 ipm=96.0,114.1 inv=105.1,98.0
frame=864 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/9 raw=0/51 sel=9/12 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/100.4/0.0/0.0 dist=0 m0=(84,119) ml=(89,119) md=5/0/5 cxcy=84.0,119.6 guide=-11.87 atg=60.0/60.0/60.0 pure=-34.57/-34.57 yaw=712 cmd=912 actual=223 signed=0 rps=3750/6250:2946/14007 duty=9/7 pwm=PWM2:9/PWM1:7 motor=2:9/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=0/9 centerNum=0/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-112.20@89,145 dx=5.1 idx=6/8 dist=26/26 sel=1:-108.96@89,145 dx=5.1 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@111,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(100.4) imip=0/8 pass=11111 acc=1 ipm=96.3,114.4 inv=106.1,98.9
frame=865 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/9 raw=0/53 sel=9/12 far=0/0 far_raw=0/0 l=0@-1/1@2 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/107.3/0.0/0.0 dist=0 m0=(84,119) ml=(86,119) md=8/0/8 cxcy=84.0,119.6 guide=-4.77 atg=60.0/28.0/28.0 pure=-36.24/-36.24 yaw=122 cmd=7 actual=236 signed=0 rps=4990/5010:3182/13283 duty=13/3 pwm=PWM2:13/PWM1:3 motor=2:13/1:3
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@2 nearNum=0/9 centerNum=0/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-117.81@86,144 dx=1.6 idx=5/8 dist=26/26 sel=1:-94.54@86,143 dx=2.4 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@112,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(107.3) imip=0/8 pass=11111 acc=2 ipm=96.7,112.1 inv=104.7,92.3
frame=866 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/9 raw=0/52 sel=9/11 far=0/0 far_raw=0/0 l=0@-1/1@2 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/100.5/0.0/0.0 dist=0 m0=(84,119) ml=(89,119) md=5/0/5 cxcy=84.0,119.6 guide=-11.87 atg=60.0/60.0/60.0 pure=-34.74/-34.74 yaw=712 cmd=912 actual=253 signed=0 rps=3750/6250:3987/13355 duty=8/8 pwm=PWM2:8/PWM1:8 motor=2:8/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@2 nearNum=0/9 centerNum=0/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-108.23@89,144 dx=4.8 idx=6/8 dist=25/25 sel=1:-83.34@89,142 dx=5.3 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@112,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(100.5) imip=0/8 pass=11111 acc=2 ipm=95.8,112.1 inv=102.9,92.3
frame=867 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/10 raw=0/54 sel=10/12 far=0/0 far_raw=0/0 l=0@-1/1@2 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/116.0/0.0/0.0 dist=0 m0=(84,119) ml=(90,119) md=6/0/6 cxcy=84.0,119.6 guide=-14.17 atg=60.0/60.0/60.0 pure=-34.14/-34.14 yaw=850 cmd=1050 actual=266 signed=0 rps=3561/6439:4421/11561 duty=7/11 pwm=PWM2:7/PWM1:11 motor=2:7/1:11
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@2 nearNum=0/10 centerNum=0/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/12 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-107.36@90,145 dx=6.2 idx=7/9 dist=26/26 sel=1:-104.11@90,144 dx=6.2 idx=0/11 dist=22/22 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@44,108/1@113,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(116.0) imip=0/9 pass=11111 acc=2 ipm=97.4,111.8 inv=105.9,91.5

- stopped_at: 2026-06-22T03:51:29+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive59
```
