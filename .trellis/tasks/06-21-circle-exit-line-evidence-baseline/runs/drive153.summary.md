# drive153

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive153-front_car_circle_drive153.log
- remote_log: /tmp/front_car_circle_drive153.log
- started_at: 2026-06-22T15:26:47+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive153 6
```

1628 /tmp/front_car_circle_drive153.log
ATGSeedDiag: seed=1@4,93/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(14.2) imip=33/53 pass=10110 acc=-1 ipm=135.1,72.6 inv=126.6,40.0 | 10(20.5) imip=0/11 pass=10111 acc=-1 ipm=123.0,108.6 inv=151.7,83.0
frame=782 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=54/12 raw=153/42 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.7/19.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,101) md=33/1/74 cxcy=84.0,119.6 guide=-28.45 atg=60.0/60.0/60.0 pure=-11.63/-11.50 yaw=2276 cmd=2076 actual=3110 signed=0 rps=2155/7845:4174/8560 duty=2/20 pwm=PWM2:2/PWM1:20 motor=2:2/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/12 centerNum=54/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.13@101,102 dx=17.3 idx=9/25 dist=33/86 right=1:-29.73@118,84 dx=33.8 idx=0/11 dist=24/24 sel=1:-29.19@107,101 dx=23.4 idx=0/16 dist=32/68 edge=1:-28.02@110.5,93.0 dx=26.5 width=43.2 l=96,77 r=125,109
CxScan: raw_ref=80.0 edge=110.5,93.0 best_raw_x=140 best_err=-4.02 best_cxcy=107.0,119.7 scan=0:-49.1,10:-47.1,20:-45.0,30:-42.6,40:-40.1,50:-37.4,60:-34.5,70:-31.4,80:-28.0,90:-24.5,100:-20.7,110:-16.7,120:-12.6,130:-8.4,140:-4.0
ATGSeedDiag: seed=1@4,92/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(14.7) imip=42/53 pass=10100 acc=-1 ipm=155.1,77.9 inv=152.4,43.5 | 10(19.7) imip=0/11 pass=10111 acc=-1 ipm=123.0,108.6 inv=151.8,83.1
frame=783 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=54/11 raw=153/42 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.5/20.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,101) md=33/1/74 cxcy=84.0,119.6 guide=-28.45 atg=60.0/60.0/60.0 pure=-11.62/-11.50 yaw=2276 cmd=2076 actual=3105 signed=0 rps=2155/7845:4742/10124 duty=1/18 pwm=PWM2:1/PWM1:18 motor=2:1/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/11 centerNum=54/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.19@99,103 dx=15.4 idx=9/24 dist=32/88 right=1:-27.26@114,84 dx=30.2 idx=0/10 dist=20/20 sel=1:-29.23@107,101 dx=23.4 idx=0/16 dist=32/68 edge=1:-26.19@108.5,93.0 dx=24.5 width=43.2 l=94,77 r=123,109
CxScan: raw_ref=80.0 edge=108.5,93.0 best_raw_x=140 best_err=-1.73 best_cxcy=107.0,119.7 scan=0:-48.1,10:-46.0,20:-43.8,30:-41.4,40:-38.7,50:-35.9,60:-32.9,70:-29.7,80:-26.2,90:-22.5,100:-18.6,110:-14.6,120:-10.4,130:-6.1,140:-1.7
ATGSeedDiag: seed=1@4,92/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(13.5) imip=42/53 pass=10100 acc=-1 ipm=155.0,77.8 inv=152.2,43.4 | 1(20.7) imip=0/10 pass=10111 acc=-1 ipm=103.6,115.0 inv=123.1,100.5
frame=785 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=54/11 raw=153/41 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.3/19.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,101) md=33/1/74 cxcy=84.0,119.6 guide=-28.45 atg=60.0/60.0/60.0 pure=-11.62/-11.50 yaw=2276 cmd=2076 actual=3081 signed=0 rps=2155/7845:4809/8930 duty=1/20 pwm=PWM2:1/PWM1:20 motor=2:1/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/11 centerNum=54/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.26@99,103 dx=15.5 idx=9/24 dist=32/87 right=1:-27.83@115,84 dx=30.8 idx=0/10 dist=20/20 sel=1:-29.13@107,101 dx=23.3 idx=0/16 dist=32/68 edge=1:-26.42@108.5,93.5 dx=24.5 width=42.4 l=94,78 r=123,109
CxScan: raw_ref=80.0 edge=108.5,93.5 best_raw_x=140 best_err=-1.74 best_cxcy=107.0,119.7 scan=0:-48.4,10:-46.3,20:-44.1,30:-41.6,40:-39.0,50:-36.2,60:-33.2,70:-29.9,80:-26.4,90:-22.7,100:-18.8,110:-14.7,120:-10.5,130:-6.2,140:-1.7
ATGSeedDiag: seed=1@4,92/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(14.3) imip=42/53 pass=10100 acc=-1 ipm=155.0,77.9 inv=152.3,43.5 | 9(19.6) imip=0/10 pass=10111 acc=-1 ipm=121.1,109.1 inv=149.1,84.2
frame=786 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=54/11 raw=153/40 sel=54/36 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.4/20.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,101) md=33/1/77 cxcy=84.0,119.6 guide=-28.45 atg=60.0/60.0/60.0 pure=-11.53/-11.42 yaw=2276 cmd=2076 actual=3066 signed=0 rps=2155/7845:5044/9149 duty=1/20 pwm=PWM2:1/PWM1:20 motor=2:1/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/11 centerNum=54/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/36 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.33@100,103 dx=15.5 idx=9/24 dist=32/89 right=1:-28.56@116,84 dx=31.9 idx=0/10 dist=20/20 sel=1:-29.13@107,101 dx=23.3 idx=0/16 dist=32/70 edge=1:-26.89@109.0,93.5 dx=25.0 width=43.1 l=94,78 r=124,109
CxScan: raw_ref=80.0 edge=109.0,93.5 best_raw_x=140 best_err=-2.32 best_cxcy=107.0,119.7 scan=0:-48.7,10:-46.6,20:-44.4,30:-42.0,40:-39.4,50:-36.6,60:-33.6,70:-30.3,80:-26.9,90:-23.2,100:-19.3,110:-15.3,120:-11.1,130:-6.7,140:-2.3
ATGSeedDiag: seed=1@4,92/1@121,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(15.4) imip=34/53 pass=10110 acc=-1 ipm=137.4,72.6 inv=129.0,40.0 | 9(20.4) imip=0/10 pass=10111 acc=-1 ipm=121.8,109.0 inv=150.3,84.0
frame=787 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=54/11 raw=153/41 sel=54/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.4/18.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,101) md=34/1/74 cxcy=84.0,119.6 guide=-28.63 atg=60.0/60.0/60.0 pure=-11.59/-11.48 yaw=2291 cmd=2091 actual=3067 signed=0 rps=2135/7865:4909/9159 duty=1/20 pwm=PWM2:1/PWM1:20 motor=2:1/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/11 centerNum=54/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.52@100,103 dx=15.6 idx=9/24 dist=32/87 right=1:-27.92@115,84 dx=31.0 idx=0/10 dist=20/20 sel=1:-29.53@108,101 dx=23.6 idx=0/16 dist=32/68 edge=1:-28.46@111.0,93.0 dx=27.0 width=41.2 l=98,77 r=124,109
CxScan: raw_ref=80.0 edge=111.0,93.0 best_raw_x=140 best_err=-4.59 best_cxcy=107.0,119.7 scan=0:-49.4,10:-47.4,20:-45.2,30:-42.9,40:-40.5,50:-37.8,60:-34.9,70:-31.8,80:-28.5,90:-24.9,100:-21.2,110:-17.3,120:-13.2,130:-8.9,140:-4.6
ATGSeedDiag: seed=1@4,93/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(15.4) imip=34/53 pass=10110 acc=-1 ipm=137.3,72.7 inv=128.9,40.1 | 4(18.3) imip=0/10 pass=10111 acc=-1 ipm=110.0,111.8 inv=131.9,91.2
frame=788 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/11 raw=153/41 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.2/18.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,102) md=34/1/77 cxcy=84.0,119.6 guide=-27.01 atg=60.0/60.0/60.0 pure=-11.72/-11.63 yaw=2161 cmd=1961 actual=3082 signed=0 rps=2313/7687:5125/9844 duty=1/18 pwm=PWM2:1/PWM1:18 motor=2:1/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/11 centerNum=53/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-24.07@102,103 dx=17.7 idx=9/25 dist=33/86 right=1:-28.27@115,84 dx=31.4 idx=0/10 dist=20/20 sel=1:-30.15@108,102 dx=23.8 idx=0/16 dist=32/68 edge=1:-26.89@109.0,93.5 dx=25.0 width=43.1 l=94,78 r=124,109
CxScan: raw_ref=80.0 edge=109.0,93.5 best_raw_x=140 best_err=-2.32 best_cxcy=107.0,119.7 scan=0:-48.7,10:-46.6,20:-44.4,30:-42.0,40:-39.4,50:-36.6,60:-33.6,70:-30.3,80:-26.9,90:-23.2,100:-19.3,110:-15.3,120:-11.1,130:-6.7,140:-2.3
ATGSeedDiag: seed=1@4,93/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.2) imip=0/20 pass=10110 acc=-1 ipm=63.4,93.6 inv=47.0,59.2 | 1(18.6) imip=0/10 pass=10111 acc=-1 ipm=104.1,115.1 inv=124.5,100.9
frame=789 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/11 raw=153/41 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.4/18.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,102) md=32/1/75 cxcy=84.0,119.6 guide=-29.97 atg=60.0/60.0/60.0 pure=-11.67/-11.61 yaw=2397 cmd=2197 actual=3081 signed=0 rps=1988/8012:4895/9398 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/11 centerNum=53/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.85@102,103 dx=17.5 idx=10/25 dist=32/86 right=1:-28.35@116,84 dx=31.5 idx=0/10 dist=20/20 sel=1:-30.89@109,101 dx=24.8 idx=0/16 dist=32/68 edge=1:-27.57@110.0,93.0 dx=26.0 width=42.5 l=96,77 r=124,109
CxScan: raw_ref=80.0 edge=110.0,93.0 best_raw_x=140 best_err=-3.45 best_cxcy=107.0,119.7 scan=0:-48.9,10:-46.8,20:-44.7,30:-42.3,40:-39.8,50:-37.0,60:-34.1,70:-30.9,80:-27.6,90:-24.0,100:-20.2,110:-16.2,120:-12.1,130:-7.8,140:-3.4
ATGSeedDiag: seed=1@4,93/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.4) imip=0/20 pass=10110 acc=-1 ipm=63.4,93.6 inv=46.9,59.2 | 3(18.5) imip=0/10 pass=10111 acc=-1 ipm=108.3,112.8 inv=129.9,93.9
frame=790 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/11 raw=153/39 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.4/18.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,101) md=34/1/74 cxcy=84.0,119.6 guide=-28.83 atg=60.0/60.0/60.0 pure=-11.64/-11.60 yaw=2306 cmd=2106 actual=3079 signed=0 rps=2113/7887:5072/9689 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/11 centerNum=53/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.01@100,103 dx=15.9 idx=9/24 dist=33/87 right=1:-29.00@116,84 dx=32.4 idx=0/10 dist=20/20 sel=1:-29.75@108,101 dx=23.7 idx=0/16 dist=32/68 edge=1:-27.35@109.5,93.5 dx=25.5 width=43.8 l=94,78 r=125,109
CxScan: raw_ref=80.0 edge=109.5,93.5 best_raw_x=140 best_err=-2.90 best_cxcy=107.0,119.7 scan=0:-48.9,10:-46.9,20:-44.7,30:-42.3,40:-39.7,50:-37.0,60:-34.0,70:-30.8,80:-27.3,90:-23.7,100:-19.9,110:-15.8,120:-11.6,130:-7.3,140:-2.9
ATGSeedDiag: seed=1@4,93/1@122,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.4) imip=0/20 pass=10110 acc=-1 ipm=63.3,93.5 inv=46.8,59.1 | 2(18.0) imip=0/10 pass=10111 acc=-1 ipm=106.8,113.7 inv=128.1,96.4
frame=791 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/11 raw=153/40 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.4/18.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(105,102) md=33/1/76 cxcy=84.0,119.6 guide=-26.73 atg=60.0/60.0/60.0 pure=-11.65/-11.55 yaw=2138 cmd=1938 actual=3084 signed=0 rps=2344/7656:4774/9076 duty=2/19 pwm=PWM2:2/PWM1:19 motor=2:2/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/11 centerNum=53/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.07@100,103 dx=16.0 idx=9/24 dist=33/86 right=1:-28.60@116,84 dx=31.8 idx=0/10 dist=20/20 sel=1:-29.71@108,101 dx=23.6 idx=0/16 dist=32/68 edge=1:-26.89@109.0,93.5 dx=25.0 width=43.1 l=94,78 r=124,109
CxScan: raw_ref=80.0 edge=109.0,93.5 best_raw_x=140 best_err=-2.32 best_cxcy=107.0,119.7 scan=0:-48.7,10:-46.6,20:-44.4,30:-42.0,40:-39.4,50:-36.6,60:-33.6,70:-30.3,80:-26.9,90:-23.2,100:-19.3,110:-15.3,120:-11.1,130:-6.7,140:-2.3
ATGSeedDiag: seed=1@4,93/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.4) imip=0/20 pass=10110 acc=-1 ipm=63.3,93.5 inv=46.8,59.1 | 1(18.4) imip=0/10 pass=10111 acc=-1 ipm=104.6,115.1 inv=125.4,100.9
frame=792 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/11 raw=153/40 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.4/19.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,102) md=34/1/76 cxcy=84.0,119.6 guide=-27.01 atg=60.0/60.0/60.0 pure=-11.64/-11.52 yaw=2161 cmd=1961 actual=3111 signed=0 rps=2313/7687:4874/9360 duty=1/19 pwm=PWM2:1/PWM1:19 motor=2:1/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/11 centerNum=53/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.60@100,104 dx=16.3 idx=9/24 dist=32/86 right=1:-28.77@116,84 dx=32.0 idx=0/10 dist=20/20 sel=1:-30.00@108,102 dx=23.8 idx=0/16 dist=32/68 edge=1:-26.18@108.0,94.0 dx=24.0 width=43.9 l=92,79 r=124,109
CxScan: raw_ref=80.0 edge=108.0,94.0 best_raw_x=140 best_err=-1.18 best_cxcy=107.0,119.7 scan=0:-48.4,10:-46.3,20:-44.1,30:-41.6,40:-39.0,50:-36.1,60:-33.0,70:-29.7,80:-26.2,90:-22.4,100:-18.5,110:-14.3,120:-10.0,130:-5.6,140:-1.2
ATGSeedDiag: seed=1@4,93/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.4) imip=0/20 pass=10110 acc=-1 ipm=63.5,93.6 inv=47.0,59.2 | 2(19.2) imip=0/10 pass=10111 acc=-1 ipm=106.5,113.9 inv=127.8,97.0
frame=793 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/10 raw=153/39 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.9/16.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(109,102) md=34/1/74 cxcy=84.0,119.6 guide=-30.00 atg=60.0/60.0/60.0 pure=-11.67/-11.55 yaw=2400 cmd=2200 actual=3134 signed=0 rps=1985/8015:4648/9210 duty=1/20 pwm=PWM2:1/PWM1:20 motor=2:1/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.97@101,104 dx=16.5 idx=9/24 dist=32/87 right=1:-26.81@113,85 dx=29.2 idx=0/9 dist=18/18 sel=1:-30.93@109,102 dx=24.5 idx=0/16 dist=32/68 edge=1:-27.35@109.5,93.5 dx=25.5 width=39.8 l=97,78 r=122,109
CxScan: raw_ref=80.0 edge=109.5,93.5 best_raw_x=140 best_err=-2.90 best_cxcy=107.0,119.7 scan=0:-48.9,10:-46.9,20:-44.7,30:-42.3,40:-39.7,50:-37.0,60:-34.0,70:-30.8,80:-27.3,90:-23.7,100:-19.9,110:-15.8,120:-11.6,130:-7.3,140:-2.9
ATGSeedDiag: seed=1@4,94/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.9) imip=0/20 pass=10110 acc=-1 ipm=63.6,93.9 inv=47.1,59.6 | 2(16.4) imip=0/9 pass=10111 acc=-1 ipm=106.7,114.0 inv=128.3,97.3
frame=794 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/10 raw=153/38 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.6/17.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(109,102) md=33/1/72 cxcy=84.0,119.6 guide=-31.63 atg=60.0/60.0/60.0 pure=-11.76/-11.63 yaw=2531 cmd=2331 actual=3137 signed=0 rps=1806/8194:4689/9625 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.39@101,104 dx=16.7 idx=9/24 dist=32/87 right=1:-27.53@114,85 dx=30.2 idx=0/9 dist=18/18 sel=1:-31.67@109,102 dx=25.2 idx=0/16 dist=32/66 edge=1:-28.46@111.0,93.0 dx=27.0 width=40.0 l=99,77 r=123,109
CxScan: raw_ref=80.0 edge=111.0,93.0 best_raw_x=140 best_err=-4.59 best_cxcy=107.0,119.7 scan=0:-49.4,10:-47.4,20:-45.2,30:-42.9,40:-40.5,50:-37.8,60:-34.9,70:-31.8,80:-28.5,90:-24.9,100:-21.2,110:-17.3,120:-13.2,130:-8.9,140:-4.6
ATGSeedDiag: seed=1@4,94/1@123,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.6) imip=0/20 pass=10110 acc=-1 ipm=63.8,94.0 inv=47.2,59.7 | 1(17.5) imip=0/9 pass=10111 acc=-1 ipm=105.2,114.9 inv=126.5,100.0
frame=795 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=4 speed=0 near=53/10 raw=153/39 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.4/20.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,102) md=33/1/73 cxcy=84.0,119.6 guide=-31.01 atg=60.0/60.0/60.0 pure=-11.74/-11.63 yaw=2480 cmd=2280 actual=3106 signed=0 rps=1875/8125:4379/9316 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.18@101,104 dx=16.7 idx=10/24 dist=32/86 right=1:-27.05@114,85 dx=29.5 idx=0/9 dist=18/18 sel=1:-31.96@110,101 dx=25.7 idx=0/16 dist=32/66 edge=1:-28.02@110.5,93.0 dx=26.5 width=39.4 l=99,77 r=122,109
CxScan: raw_ref=80.0 edge=110.5,93.0 best_raw_x=140 best_err=-4.02 best_cxcy=107.0,119.7 scan=0:-49.1,10:-47.1,20:-45.0,30:-42.6,40:-40.1,50:-37.4,60:-34.5,70:-31.4,80:-28.0,90:-24.5,100:-20.7,110:-16.7,120:-12.6,130:-8.4,140:-4.0
ATGSeedDiag: seed=1@4,94/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(13.4) imip=0/19 pass=10110 acc=-1 ipm=61.9,95.4 inv=43.9,61.4 | 1(20.5) imip=0/9 pass=10111 acc=-1 ipm=104.9,115.0 inv=126.1,100.6

- stopped_at: 2026-06-22T15:26:59+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive153
```
