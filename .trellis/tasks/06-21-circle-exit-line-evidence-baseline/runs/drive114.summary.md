# drive114

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive114-front_car_circle_drive114.log
- remote_log: /tmp/front_car_circle_drive114.log
- started_at: 2026-06-22T07:31:04+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive114 6
```

4451 /tmp/front_car_circle_drive114.log
ATGSeedDiag: seed=1@14,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.0) imip=0/20 pass=10110 acc=-1 ipm=67.4,95.6 inv=51.8,61.7 | 2(23.1) imip=0/11 pass=10111 acc=-1 ipm=111.5,113.0 inv=137.1,94.4
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/12 raw=151/39 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.7/22.6/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,97) md=33/1/84 cxcy=84.0,119.6 guide=-28.90 atg=60.0/60.0/60.0 pure=-10.17/-9.83 yaw=1734 cmd=1934 actual=960 signed=0 rps=2349/7651:4055/5388 duty=3/25 pwm=PWM2:3/PWM1:25 motor=2:3/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/12 centerNum=58/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.74@106,99 dx=22.3 idx=5/25 dist=33/96 right=1:-28.63@118,81 dx=33.7 idx=0/11 dist=24/24 sel=1:-30.36@111,97 dx=27.1 idx=0/16 dist=32/76 edge=1:-24.31@106.5,93.0 dx=22.5 width=51.9 l=83,82 r=130,104
CxScan: raw_ref=80.0 edge=106.5,93.0 best_raw_x=140 best_err=0.57 best_cxcy=107.0,119.7 scan=0:-47.1,10:-44.9,20:-42.5,30:-40.0,40:-37.3,50:-34.4,60:-31.2,70:-27.9,80:-24.3,90:-20.5,100:-16.6,110:-12.4,120:-8.2,130:-3.8,140:0.6
ATGSeedDiag: seed=1@14,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.7) imip=0/20 pass=10110 acc=-1 ipm=67.4,95.7 inv=51.8,61.8 | 2(22.6) imip=0/11 pass=10111 acc=-1 ipm=111.6,113.0 inv=137.3,94.5
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=57/11 raw=152/39 sel=57/38 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.7/21.5/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,97) md=33/1/83 cxcy=84.0,119.6 guide=-28.90 atg=60.0/60.0/60.0 pure=-10.17/-9.92 yaw=1734 cmd=1934 actual=977 signed=0 rps=2349/7651:3316/4607 duty=4/26 pwm=PWM2:4/PWM1:26 motor=2:4/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=57/11 centerNum=57/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/38 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.50@106,99 dx=22.0 idx=5/25 dist=33/93 right=1:-26.61@114,82 dx=30.2 idx=0/10 dist=20/20 sel=1:-30.37@111,97 dx=27.1 idx=0/16 dist=32/74 edge=1:-24.31@106.5,93.0 dx=22.5 width=49.2 l=85,81 r=128,105
CxScan: raw_ref=80.0 edge=106.5,93.0 best_raw_x=140 best_err=0.57 best_cxcy=107.0,119.7 scan=0:-47.1,10:-44.9,20:-42.5,30:-40.0,40:-37.3,50:-34.4,60:-31.2,70:-27.9,80:-24.3,90:-20.5,100:-16.6,110:-12.4,120:-8.2,130:-3.8,140:0.6
ATGSeedDiag: seed=1@13,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.7) imip=0/20 pass=10110 acc=-1 ipm=67.1,95.9 inv=51.4,62.1 | 2(21.5) imip=0/10 pass=10111 acc=-1 ipm=111.6,113.0 inv=137.3,94.5
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=57/11 raw=151/39 sel=57/38 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.2/20.9/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=33/1/83 cxcy=84.0,119.6 guide=-28.22 atg=60.0/60.0/60.0 pure=-10.17/-9.93 yaw=1693 cmd=1893 actual=1000 signed=0 rps=2405/7595:3459/4943 duty=4/25 pwm=PWM2:4/PWM1:25 motor=2:4/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=57/11 centerNum=57/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/38 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.44@105,99 dx=20.6 idx=5/24 dist=32/94 right=1:-26.79@114,82 dx=30.5 idx=0/10 dist=20/20 sel=1:-30.55@111,97 dx=27.2 idx=0/16 dist=32/74 edge=1:-24.31@106.5,93.0 dx=22.5 width=49.2 l=85,81 r=128,105
CxScan: raw_ref=80.0 edge=106.5,93.0 best_raw_x=140 best_err=0.57 best_cxcy=107.0,119.7 scan=0:-47.1,10:-44.9,20:-42.5,30:-40.0,40:-37.3,50:-34.4,60:-31.2,70:-27.9,80:-24.3,90:-20.5,100:-16.6,110:-12.4,120:-8.2,130:-3.8,140:0.6
ATGSeedDiag: seed=1@13,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.2) imip=0/20 pass=10110 acc=-1 ipm=67.3,95.7 inv=51.7,61.9 | 1(20.9) imip=0/10 pass=10111 acc=-1 ipm=110.0,114.7 inv=137.0,99.5
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/11 raw=151/38 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.2/21.2/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=33/1/84 cxcy=84.0,119.6 guide=-28.99 atg=60.0/60.0/60.0 pure=-10.17/-9.82 yaw=1740 cmd=1940 actual=1038 signed=0 rps=2342/7658:3486/4820 duty=4/25 pwm=PWM2:4/PWM1:25 motor=2:4/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/11 centerNum=58/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.41@105,99 dx=20.6 idx=5/24 dist=33/96 right=1:-27.05@115,82 dx=30.8 idx=0/10 dist=20/20 sel=1:-30.53@111,97 dx=27.1 idx=0/16 dist=32/76 edge=1:-24.31@106.5,93.0 dx=22.5 width=49.2 l=85,81 r=128,105
CxScan: raw_ref=80.0 edge=106.5,93.0 best_raw_x=140 best_err=0.57 best_cxcy=107.0,119.7 scan=0:-47.1,10:-44.9,20:-42.5,30:-40.0,40:-37.3,50:-34.4,60:-31.2,70:-27.9,80:-24.3,90:-20.5,100:-16.6,110:-12.4,120:-8.2,130:-3.8,140:0.6
ATGSeedDiag: seed=1@13,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.2) imip=0/20 pass=10110 acc=-1 ipm=67.3,95.8 inv=51.6,61.9 | 1(21.2) imip=0/10 pass=10111 acc=-1 ipm=110.0,114.8 inv=137.0,99.6
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/11 raw=151/37 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.1/20.8/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=33/1/84 cxcy=84.0,119.6 guide=-28.22 atg=60.0/60.0/60.0 pure=-10.17/-9.78 yaw=1693 cmd=1893 actual=1057 signed=0 rps=2405/7595:3757/5065 duty=4/25 pwm=PWM2:4/PWM1:25 motor=2:4/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/11 centerNum=58/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.41@105,99 dx=20.6 idx=5/24 dist=33/98 right=1:-27.23@115,82 dx=31.0 idx=0/10 dist=20/20 sel=1:-30.54@111,97 dx=27.2 idx=0/16 dist=32/76 edge=1:-24.31@106.5,93.0 dx=22.5 width=49.2 l=85,81 r=128,105
CxScan: raw_ref=80.0 edge=106.5,93.0 best_raw_x=140 best_err=0.57 best_cxcy=107.0,119.7 scan=0:-47.1,10:-44.9,20:-42.5,30:-40.0,40:-37.3,50:-34.4,60:-31.2,70:-27.9,80:-24.3,90:-20.5,100:-16.6,110:-12.4,120:-8.2,130:-3.8,140:0.6
ATGSeedDiag: seed=1@13,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(15.1) imip=0/20 pass=10110 acc=-1 ipm=67.2,95.7 inv=51.5,61.8 | 1(20.8) imip=0/10 pass=10111 acc=-1 ipm=110.0,114.8 inv=137.1,99.6
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/11 raw=151/36 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.8/20.5/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=32/1/82 cxcy=84.0,119.6 guide=-30.22 atg=60.0/60.0/60.0 pure=-10.16/-9.83 yaw=1813 cmd=2013 actual=1097 signed=0 rps=2241/7759:3937/4759 duty=3/26 pwm=PWM2:3/PWM1:26 motor=2:3/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/11 centerNum=58/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.54@105,100 dx=20.5 idx=6/24 dist=32/96 right=1:-27.61@116,83 dx=31.5 idx=0/10 dist=20/20 sel=1:-30.85@111,97 dx=27.5 idx=0/16 dist=32/76 edge=1:-25.04@107.5,92.5 dx=23.5 width=48.0 l=87,80 r=128,105
CxScan: raw_ref=80.0 edge=107.5,92.5 best_raw_x=140 best_err=-0.57 best_cxcy=107.0,119.7 scan=0:-47.3,10:-45.2,20:-42.9,30:-40.4,40:-37.8,50:-34.9,60:-31.8,70:-28.5,80:-25.0,90:-21.3,100:-17.4,110:-13.4,120:-9.2,130:-4.9,140:-0.6
ATGSeedDiag: seed=1@13,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.8) imip=0/20 pass=10110 acc=-1 ipm=67.2,95.8 inv=51.6,62.0 | 1(20.5) imip=0/10 pass=10111 acc=-1 ipm=110.1,114.8 inv=137.2,99.7
frame=894 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/10 raw=152/35 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.2/16.8/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=32/1/83 cxcy=84.0,119.6 guide=-30.15 atg=60.0/60.0/60.0 pure=-10.17/-9.82 yaw=1809 cmd=2009 actual=1093 signed=0 rps=2246/7754:3958/4650 duty=3/26 pwm=PWM2:3/PWM1:26 motor=2:3/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/10 centerNum=58/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.55@106,99 dx=21.8 idx=6/25 dist=33/95 right=1:-26.37@113,84 dx=29.3 idx=0/9 dist=18/18 sel=1:-30.82@111,97 dx=27.2 idx=0/16 dist=32/76 edge=1:-23.56@105.5,93.5 dx=21.5 width=48.0 l=85,81 r=126,106
CxScan: raw_ref=80.0 edge=105.5,93.5 best_raw_x=135 best_err=-0.48 best_cxcy=105.1,119.7 scan=0:-46.8,10:-44.6,20:-42.2,30:-39.6,40:-36.8,50:-33.9,60:-30.6,70:-27.2,80:-23.6,90:-19.7,100:-15.6,110:-11.4,120:-7.1,130:-2.7,140:1.7
ATGSeedDiag: seed=1@12,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.2) imip=0/20 pass=10110 acc=-1 ipm=66.9,95.9 inv=51.0,62.0 | 2(16.8) imip=0/9 pass=10111 acc=-1 ipm=111.9,113.4 inv=138.6,95.4
frame=895 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/10 raw=152/34 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.0/15.7/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=32/1/82 cxcy=84.0,119.6 guide=-30.15 atg=60.0/60.0/60.0 pure=-10.17/-9.71 yaw=1809 cmd=2009 actual=1107 signed=0 rps=2246/7754:4084/5087 duty=3/25 pwm=PWM2:3/PWM1:25 motor=2:3/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/10 centerNum=58/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.37@104,100 dx=20.3 idx=6/24 dist=33/98 right=1:-26.52@114,84 dx=29.5 idx=0/9 dist=18/18 sel=1:-30.62@111,97 dx=27.1 idx=0/16 dist=32/76 edge=1:-23.56@105.5,93.5 dx=21.5 width=48.0 l=85,81 r=126,106
CxScan: raw_ref=80.0 edge=105.5,93.5 best_raw_x=135 best_err=-0.48 best_cxcy=105.1,119.7 scan=0:-46.8,10:-44.6,20:-42.2,30:-39.6,40:-36.8,50:-33.9,60:-30.6,70:-27.2,80:-23.6,90:-19.7,100:-15.6,110:-11.4,120:-7.1,130:-2.7,140:1.7
ATGSeedDiag: seed=1@12,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=56(18.0) imip=46/57 pass=10100 acc=-1 ipm=164.8,68.3 inv=152.2,37.2 | 2(15.7) imip=0/9 pass=10111 acc=-1 ipm=112.0,113.4 inv=138.8,95.5
frame=896 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/10 raw=152/34 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.0/15.3/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=32/1/82 cxcy=84.0,119.6 guide=-30.31 atg=60.0/60.0/60.0 pure=-10.17/-9.67 yaw=1819 cmd=2019 actual=1118 signed=0 rps=2233/7767:3873/5053 duty=3/26 pwm=PWM2:3/PWM1:26 motor=2:3/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/10 centerNum=58/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.51@104,100 dx=20.4 idx=6/24 dist=32/96 right=1:-26.70@114,84 dx=29.7 idx=0/9 dist=18/18 sel=1:-30.96@111,97 dx=27.4 idx=0/16 dist=32/76 edge=1:-24.04@106.0,93.5 dx=22.0 width=48.9 l=85,81 r=127,106
CxScan: raw_ref=80.0 edge=106.0,93.5 best_raw_x=135 best_err=-1.06 best_cxcy=105.1,119.7 scan=0:-47.1,10:-44.9,20:-42.5,30:-40.0,40:-37.2,50:-34.3,60:-31.1,70:-27.7,80:-24.0,90:-20.2,100:-16.2,110:-12.0,120:-7.7,130:-3.3,140:1.2
ATGSeedDiag: seed=1@12,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=56(17.0) imip=46/57 pass=10100 acc=-1 ipm=165.0,68.0 inv=152.1,37.1 | 2(15.3) imip=0/9 pass=10111 acc=-1 ipm=112.1,113.5 inv=139.1,95.6
frame=897 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/10 raw=152/33 sel=58/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.3/15.8/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=32/1/82 cxcy=84.0,119.6 guide=-30.31 atg=60.0/60.0/60.0 pure=-10.16/-9.60 yaw=1819 cmd=2019 actual=1128 signed=0 rps=2233/7767:3936/5288 duty=3/25 pwm=PWM2:3/PWM1:25 motor=2:3/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/10 centerNum=58/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.73@105,100 dx=20.5 idx=6/24 dist=32/96 right=1:-26.94@114,84 dx=30.0 idx=0/9 dist=18/18 sel=1:-31.01@111,97 dx=27.4 idx=0/16 dist=32/78 edge=1:-24.79@107.0,93.0 dx=23.0 width=47.7 l=87,80 r=127,106
CxScan: raw_ref=80.0 edge=107.0,93.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-47.3,10:-45.2,20:-42.9,30:-40.4,40:-37.7,50:-34.8,60:-31.7,70:-28.3,80:-24.8,90:-21.0,100:-17.1,110:-13.0,120:-8.7,130:-4.4,140:-0.0
ATGSeedDiag: seed=1@12,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.3) imip=0/20 pass=10110 acc=-1 ipm=67.1,96.0 inv=51.3,62.2 | 1(15.8) imip=0/9 pass=10111 acc=-1 ipm=110.4,114.9 inv=138.2,100.1
frame=898 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/10 raw=152/33 sel=58/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.7/19.3/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=32/1/82 cxcy=84.0,119.6 guide=-30.40 atg=60.0/60.0/60.0 pure=-10.16/-9.60 yaw=1824 cmd=2024 actual=1148 signed=0 rps=2226/7774:3936/5345 duty=3/25 pwm=PWM2:3/PWM1:25 motor=2:3/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/10 centerNum=58/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.76@105,100 dx=20.5 idx=6/24 dist=32/97 right=1:-27.19@114,84 dx=30.3 idx=0/9 dist=18/18 sel=1:-31.23@111,97 dx=27.5 idx=0/16 dist=32/78 edge=1:-24.26@106.0,94.0 dx=22.0 width=49.4 l=85,81 r=127,107
CxScan: raw_ref=80.0 edge=106.0,94.0 best_raw_x=135 best_err=-1.07 best_cxcy=105.1,119.7 scan=0:-47.4,10:-45.2,20:-42.8,30:-40.3,40:-37.5,50:-34.5,60:-31.3,70:-27.9,80:-24.3,90:-20.4,100:-16.3,110:-12.1,120:-7.8,130:-3.3,140:1.2
ATGSeedDiag: seed=1@12,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.7) imip=0/20 pass=10110 acc=-1 ipm=67.1,96.0 inv=51.2,62.2 | 1(19.3) imip=0/9 pass=10111 acc=-1 ipm=110.6,114.9 inv=138.4,99.9
frame=899 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/10 raw=152/33 sel=58/40 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.7/19.5/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=33/1/84 cxcy=84.0,119.6 guide=-28.84 atg=60.0/60.0/60.0 pure=-10.17/-9.68 yaw=1731 cmd=1931 actual=1168 signed=0 rps=2354/7646:3704/5100 duty=4/25 pwm=PWM2:4/PWM1:25 motor=2:4/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/10 centerNum=58/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.90@106,100 dx=21.9 idx=6/25 dist=33/94 right=1:-27.29@114,84 dx=30.4 idx=0/9 dist=18/18 sel=1:-31.12@111,98 dx=27.3 idx=0/16 dist=32/78 edge=1:-24.26@106.0,94.0 dx=22.0 width=49.4 l=85,81 r=127,107
CxScan: raw_ref=80.0 edge=106.0,94.0 best_raw_x=135 best_err=-1.07 best_cxcy=105.1,119.7 scan=0:-47.4,10:-45.2,20:-42.8,30:-40.3,40:-37.5,50:-34.5,60:-31.3,70:-27.9,80:-24.3,90:-20.4,100:-16.3,110:-12.1,120:-7.8,130:-3.3,140:1.2
ATGSeedDiag: seed=1@11,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=56(16.7) imip=46/57 pass=10100 acc=-1 ipm=165.0,68.0 inv=152.1,37.1 | 1(19.5) imip=0/9 pass=10111 acc=-1 ipm=110.6,114.9 inv=138.4,99.9
frame=900 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=58/10 raw=152/32 sel=58/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.5/18.2/0.0/0.0 dist=0 begin=0/2714 m0=(84,119) ml=(109,98) md=33/1/83 cxcy=84.0,119.6 guide=-28.68 atg=60.0/60.0/60.0 pure=-10.17/-9.71 yaw=1721 cmd=1921 actual=1182 signed=0 rps=2368/7632:3866/5342 duty=4/25 pwm=PWM2:4/PWM1:25 motor=2:4/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=58/10 centerNum=58/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=58/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-26.78@106,100 dx=21.7 idx=6/25 dist=33/93 right=1:-27.55@115,84 dx=30.8 idx=0/9 dist=18/18 sel=1:-31.09@111,98 dx=27.3 idx=0/16 dist=32/76 edge=1:-25.01@107.0,93.5 dx=23.0 width=48.3 l=87,80 r=127,107
CxScan: raw_ref=80.0 edge=107.0,93.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-47.6,10:-45.5,20:-43.2,30:-40.7,40:-38.0,50:-35.0,60:-31.9,70:-28.6,80:-25.0,90:-21.2,100:-17.2,110:-13.1,120:-8.8,130:-4.4,140:-0.0
ATGSeedDiag: seed=1@11,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=56(16.5) imip=46/57 pass=10100 acc=-1 ipm=164.9,68.4 inv=152.4,37.3 | 1(18.2) imip=0/9 pass=10111 acc=-1 ipm=110.6,114.9 inv=138.6,100.0

- stopped_at: 2026-06-22T07:31:18+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive114
```
