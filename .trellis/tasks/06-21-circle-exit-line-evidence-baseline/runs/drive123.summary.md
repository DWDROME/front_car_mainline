# drive123

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive123-front_car_circle_drive123.log
- remote_log: /tmp/front_car_circle_drive123.log
- started_at: 2026-06-22T14:51:24+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive123 6
```

4690 /tmp/front_car_circle_drive123.log
frame=914 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=46/101 raw=104/158 sel=101/86 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=24.8/15.8/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(77,90) md=32/1/148 cxcy=84.0,119.6 guide=6.95 atg=-60.0/-60.0/-60.0 pure=3.10/4.61 yaw=-417 cmd=-409 actual=-426 signed=0 rps=5560/4440:6970/6524 duty=10/7 pwm=PWM2:10/PWM1:7 motor=2:10/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=46/101 centerNum=46/101 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=101/86 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.23@80,82 dx=-4.5 idx=0/12 dist=33/140 right=1:7.50@77,91 dx=-6.8 idx=0/12 dist=32/203 sel=1:6.32@78,86 dx=-6.3 idx=0/16 dist=32/170 edge=1:5.40@78.0,79.0 dx=-6.0 width=50.0 l=53,79 r=103,79
CxScan: raw_ref=80.0 edge=78.0,79.0 best_raw_x=65 best_err=0.24 best_cxcy=78.3,119.5 scan=0:-21.3,10:-18.2,20:-15.0,30:-11.7,40:-8.3,50:-4.9,60:-1.5,70:2.0,80:5.4,90:8.8,100:12.1,110:15.3,120:18.5,130:21.5,140:24.4
ATGSeedDiag: seed=1@11,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=19(24.8) imip=9/29 pass=10111 acc=-1 ipm=49.5,73.0 inv=39.1,40.9 | 21(15.8) imip=11/31 pass=10111 acc=-1 ipm=100.7,68.2 inv=90.6,37.6
frame=915 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=45/100 raw=103/158 sel=100/86 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=24.6/19.2/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(77,90) md=32/1/147 cxcy=84.0,119.6 guide=6.95 atg=-60.0/-60.0/-60.0 pure=3.31/4.91 yaw=-417 cmd=-425 actual=-409 signed=0 rps=5583/4417:6808/6314 duty=10/8 pwm=PWM2:10/PWM1:8 motor=2:10/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=45/100 centerNum=45/100 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=100/86 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.94@80,82 dx=-4.2 idx=0/12 dist=33/139 right=1:7.39@77,91 dx=-6.7 idx=0/12 dist=32/200 sel=1:6.26@78,86 dx=-6.3 idx=0/16 dist=32/170 edge=1:5.40@78.0,79.0 dx=-6.0 width=50.0 l=53,79 r=103,79
CxScan: raw_ref=80.0 edge=78.0,79.0 best_raw_x=65 best_err=0.24 best_cxcy=78.3,119.5 scan=0:-21.3,10:-18.2,20:-15.0,30:-11.7,40:-8.3,50:-4.9,60:-1.5,70:2.0,80:5.4,90:8.8,100:12.1,110:15.3,120:18.5,130:21.5,140:24.4
ATGSeedDiag: seed=1@11,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=18(24.6) imip=8/28 pass=10111 acc=-1 ipm=50.5,75.1 inv=39.3,42.3 | 20(19.2) imip=10/30 pass=10111 acc=-1 ipm=101.4,70.4 inv=91.8,38.9
frame=916 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=44/97 raw=103/158 sel=97/82 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=25.6/20.5/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(78,88) md=33/1/140 cxcy=84.0,119.6 guide=6.27 atg=-60.0/-60.0/-60.0 pure=3.45/4.98 yaw=-376 cmd=-354 actual=-398 signed=0 rps=5485/4515:7051/6514 duty=9/8 pwm=PWM2:9/PWM1:8 motor=2:9/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=44/97 centerNum=44/97 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=97/82 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.65@80,82 dx=-3.9 idx=0/12 dist=34/136 right=1:6.38@78,90 dx=-5.9 idx=0/13 dist=33/192 sel=1:6.07@78,86 dx=-6.1 idx=0/16 dist=32/162 edge=1:5.44@78.0,79.5 dx=-6.0 width=50.0 l=53,79 r=103,80
CxScan: raw_ref=80.0 edge=78.0,79.5 best_raw_x=65 best_err=0.25 best_cxcy=78.3,119.5 scan=0:-21.4,10:-18.3,20:-15.1,30:-11.8,40:-8.4,50:-5.0,60:-1.5,70:2.0,80:5.4,90:8.9,100:12.2,110:15.5,120:18.6,130:21.7,140:24.6
ATGSeedDiag: seed=1@11,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=18(25.6) imip=8/28 pass=10111 acc=-1 ipm=50.5,75.3 inv=39.1,42.4 | 20(20.5) imip=10/30 pass=10111 acc=-1 ipm=101.4,70.5 inv=91.8,38.9
frame=917 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=10/97 raw=55/158 sel=97/81 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=172.9/19.8/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(78,88) md=33/1/140 cxcy=84.0,119.6 guide=6.54 atg=-60.0/-60.0/-60.0 pure=3.54/5.00 yaw=-392 cmd=-393 actual=-392 signed=0 rps=5539/4461:7081/6675 duty=10/7 pwm=PWM2:10/PWM1:7 motor=2:10/1:7
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/97 centerNum=10/97 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=97/81 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:6.32@78,90 dx=-5.9 idx=0/13 dist=32/193 sel=1:5.89@78,85 dx=-5.9 idx=0/16 dist=32/160 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,80
ATGSeedDiag: seed=1@36,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(172.9) imip=0/9 pass=11010 acc=-1 ipm=58.4,110.1 inv=26.8,88.0 | 19(19.8) imip=9/29 pass=10111 acc=-1 ipm=102.2,72.7 inv=93.2,40.3
frame=918 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=10/98 raw=51/158 sel=98/82 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=172.1/19.2/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,87) md=34/1/141 cxcy=84.0,119.6 guide=6.00 atg=-60.0/-60.0/-60.0 pure=3.41/4.97 yaw=-153 cmd=47 actual=-378 signed=0 rps=4936/5064:6565/6389 duty=8/10 pwm=PWM2:8/PWM1:10 motor=2:8/1:10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/98 centerNum=10/98 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=98/82 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:5.90@79,90 dx=-5.5 idx=0/13 dist=32/195 sel=1:5.63@78,85 dx=-5.7 idx=0/16 dist=32/162 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,80
ATGSeedDiag: seed=1@35,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(172.1) imip=0/9 pass=11010 acc=-1 ipm=57.5,110.8 inv=24.1,89.6 | 19(19.2) imip=9/29 pass=10111 acc=-1 ipm=102.3,72.8 inv=93.3,40.4
frame=919 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=43/100 raw=102/158 sel=100/85 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=25.1/15.4/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,87) md=34/1/146 cxcy=84.0,119.6 guide=5.82 atg=-60.0/-60.0/-60.0 pure=3.41/4.95 yaw=-149 cmd=51 actual=-351 signed=0 rps=4929/5071:6960/6964 duty=8/9 pwm=PWM2:8/PWM1:9 motor=2:8/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=43/100 centerNum=43/100 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=100/85 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.65@80,81 dx=-3.9 idx=0/12 dist=34/135 right=1:5.52@79,89 dx=-5.2 idx=0/13 dist=32/197 sel=1:5.50@78,85 dx=-5.6 idx=0/16 dist=32/168 edge=1:5.44@78.0,79.5 dx=-6.0 width=52.0 l=52,79 r=104,80
CxScan: raw_ref=80.0 edge=78.0,79.5 best_raw_x=65 best_err=0.25 best_cxcy=78.3,119.5 scan=0:-21.4,10:-18.3,20:-15.1,30:-11.8,40:-8.4,50:-5.0,60:-1.5,70:2.0,80:5.4,90:8.9,100:12.2,110:15.5,120:18.6,130:21.7,140:24.6
ATGSeedDiag: seed=1@11,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(25.1) imip=7/27 pass=10111 acc=-1 ipm=51.1,77.4 inv=38.9,43.9 | 18(15.4) imip=8/28 pass=10111 acc=-1 ipm=103.0,75.0 inv=94.8,41.8
frame=920 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=42/97 raw=100/158 sel=97/81 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=26.1/18.4/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,87) md=34/1/140 cxcy=84.0,119.6 guide=5.65 atg=-60.0/-60.0/-60.0 pure=3.55/5.01 yaw=-144 cmd=41 actual=-329 signed=0 rps=4944/5056:6789/6791 duty=8/9 pwm=PWM2:8/PWM1:9 motor=2:8/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=42/97 centerNum=42/97 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=97/81 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.44@80,84 dx=-3.5 idx=0/11 dist=32/132 right=1:5.51@79,90 dx=-5.1 idx=0/13 dist=32/193 sel=1:5.62@78,85 dx=-5.7 idx=0/16 dist=32/160 edge=1:5.48@78.0,80.0 dx=-6.0 width=52.0 l=52,80 r=104,80
CxScan: raw_ref=80.0 edge=78.0,80.0 best_raw_x=65 best_err=0.25 best_cxcy=78.3,119.5 scan=0:-21.6,10:-18.4,20:-15.2,30:-11.9,40:-8.5,50:-5.0,60:-1.5,70:2.0,80:5.5,90:8.9,100:12.3,110:15.6,120:18.8,130:21.8,140:24.7
ATGSeedDiag: seed=1@12,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=17(26.1) imip=7/27 pass=10111 acc=-1 ipm=50.7,77.6 inv=38.4,44.1 | 18(18.4) imip=8/28 pass=10111 acc=-1 ipm=102.9,75.0 inv=94.7,41.8
frame=921 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=6/96 raw=38/157 sel=96/82 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=170.6/17.7/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,87) md=34/1/140 cxcy=84.0,119.6 guide=5.82 atg=-60.0/-60.0/-60.0 pure=3.94/5.31 yaw=-149 cmd=1 actual=-298 signed=0 rps=4999/5001:7057/6922 duty=8/9 pwm=PWM2:8/PWM1:9 motor=2:8/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/96 centerNum=6/96 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=96/82 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:5.64@79,90 dx=-5.2 idx=0/13 dist=33/190 sel=1:5.93@78,85 dx=-6.0 idx=0/16 dist=32/162 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,80
ATGSeedDiag: seed=1@30,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(170.6) imip=0/5 pass=11010 acc=-1 ipm=58.9,113.5 inv=23.8,97.0 | 18(17.7) imip=8/28 pass=10111 acc=-1 ipm=102.2,75.2 inv=93.9,41.9
frame=922 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=40/93 raw=98/157 sel=93/77 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=27.9/19.9/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(78,87) md=34/1/136 cxcy=84.0,119.6 guide=6.00 atg=-60.0/-60.0/-60.0 pure=4.12/5.38 yaw=-153 cmd=-39 actual=-267 signed=0 rps=5053/4947:7099/6894 duty=8/9 pwm=PWM2:8/PWM1:9 motor=2:8/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=40/93 centerNum=40/93 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=93/77 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.18@81,83 dx=-3.3 idx=0/11 dist=33/128 right=1:5.62@79,91 dx=-5.1 idx=0/13 dist=33/183 sel=1:6.05@78,85 dx=-6.1 idx=0/16 dist=32/152 edge=1:6.39@77.0,80.0 dx=-7.0 width=52.0 l=51,80 r=103,80
CxScan: raw_ref=80.0 edge=77.0,80.0 best_raw_x=60 best_err=-0.59 best_cxcy=76.4,119.5 scan=0:-20.8,10:-17.6,20:-14.4,30:-11.0,40:-7.6,50:-4.1,60:-0.6,70:2.9,80:6.4,90:9.8,100:13.2,110:16.4,120:19.6,130:22.6,140:25.5
ATGSeedDiag: seed=1@12,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=16(27.9) imip=6/26 pass=10111 acc=-1 ipm=51.4,80.0 inv=38.1,45.9 | 79(19.9) imip=69/89 pass=10101 acc=-1 ipm=-15.1,3.4 inv=19.3,17.1
frame=923 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=39/93 raw=98/157 sel=93/77 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=28.1/19.9/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,89) md=32/1/136 cxcy=84.0,119.6 guide=5.81 atg=-60.0/-60.0/-60.0 pure=4.12/5.38 yaw=-148 cmd=-57 actual=-239 signed=0 rps=5078/4922:7318/7125 duty=8/8 pwm=PWM2:8/PWM1:8 motor=2:8/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=39/93 centerNum=39/93 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=93/77 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.48@80,83 dx=-3.6 idx=0/11 dist=33/125 right=1:5.45@79,91 dx=-5.0 idx=0/13 dist=33/183 sel=1:5.97@78,85 dx=-6.1 idx=0/16 dist=32/152 edge=1:5.94@77.5,80.0 dx=-6.5 width=53.0 l=51,80 r=104,80
CxScan: raw_ref=80.0 edge=77.5,80.0 best_raw_x=65 best_err=0.71 best_cxcy=78.3,119.5 scan=0:-21.2,10:-18.0,20:-14.8,30:-11.4,40:-8.0,50:-4.5,60:-1.0,70:2.5,80:5.9,90:9.4,100:12.7,110:16.0,120:19.2,130:22.2,140:25.1
ATGSeedDiag: seed=1@12,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=15(28.1) imip=5/25 pass=10111 acc=-1 ipm=52.5,82.0 inv=38.4,47.5 | 79(19.9) imip=69/89 pass=10101 acc=-1 ipm=-15.1,3.4 inv=19.3,17.1
frame=924 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=39/93 raw=97/157 sel=93/77 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=27.9/23.4/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,89) md=32/1/136 cxcy=84.0,119.6 guide=5.81 atg=-60.0/-60.0/-60.0 pure=4.12/5.37 yaw=-148 cmd=-84 actual=-212 signed=0 rps=5115/4885:7291/7041 duty=8/8 pwm=PWM2:8/PWM1:8 motor=2:8/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=39/93 centerNum=39/93 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=93/77 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.62@80,83 dx=-3.8 idx=0/11 dist=33/123 right=1:5.34@79,91 dx=-4.9 idx=0/13 dist=33/182 sel=1:5.97@78,85 dx=-6.0 idx=0/16 dist=32/152 edge=1:5.94@77.5,80.0 dx=-6.5 width=53.0 l=51,80 r=104,80
CxScan: raw_ref=80.0 edge=77.5,80.0 best_raw_x=65 best_err=0.71 best_cxcy=78.3,119.5 scan=0:-21.2,10:-18.0,20:-14.8,30:-11.4,40:-8.0,50:-4.5,60:-1.0,70:2.5,80:5.9,90:9.4,100:12.7,110:16.0,120:19.2,130:22.2,140:25.1
ATGSeedDiag: seed=1@12,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=15(27.9) imip=5/25 pass=10111 acc=-1 ipm=52.1,82.1 inv=37.9,47.6 | 79(23.4) imip=69/89 pass=10101 acc=-1 ipm=-14.8,3.1 inv=19.6,17.0
frame=925 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=3/96 raw=16/157 sel=96/82 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=1.6/17.4/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,89) md=32/1/141 cxcy=84.0,119.6 guide=5.81 atg=-60.0/-60.0/-60.0 pure=4.19/5.38 yaw=-148 cmd=-123 actual=-173 signed=0 rps=5169/4831:6724/6505 duty=9/9 pwm=PWM2:9/PWM1:9 motor=2:9/1:9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/96 centerNum=3/96 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=96/82 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:5.32@79,91 dx=-4.8 idx=0/13 dist=33/194 sel=1:5.98@78,85 dx=-6.1 idx=0/16 dist=32/162 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=104,80
ATGSeedDiag: seed=1@19,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(1.6) imip=0/2 pass=10110 acc=-1 ipm=59.8,117.7 inv=19.7,110.8 | 17(17.4) imip=7/27 pass=10111 acc=-1 ipm=103.0,77.5 inv=95.5,43.6
frame=926 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=38/93 raw=95/157 sel=93/78 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=27.5/20.4/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,89) md=32/1/138 cxcy=84.0,119.6 guide=5.81 atg=-60.0/-60.0/-60.0 pure=4.24/5.39 yaw=-148 cmd=-161 actual=-135 signed=0 rps=5221/4779:6780/6701 duty=9/8 pwm=PWM2:9/PWM1:8 motor=2:9/1:8
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=38/93 centerNum=38/93 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=93/78 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.10@80,82 dx=-4.4 idx=0/11 dist=34/121 right=1:5.31@79,91 dx=-4.8 idx=0/13 dist=33/185 sel=1:6.17@78,85 dx=-6.3 idx=0/16 dist=32/154 edge=1:6.89@76.5,80.5 dx=-7.5 width=53.0 l=50,81 r=103,80
CxScan: raw_ref=80.0 edge=76.5,80.5 best_raw_x=60 best_err=-0.13 best_cxcy=76.4,119.5 scan=0:-20.5,10:-17.3,20:-14.0,30:-10.6,40:-7.2,50:-3.7,60:-0.1,70:3.4,80:6.9,90:10.3,100:13.7,110:17.0,120:20.1,130:23.1,140:26.0
ATGSeedDiag: seed=1@12,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=15(27.5) imip=5/25 pass=10111 acc=-1 ipm=51.4,82.3 inv=36.8,47.8 | 78(20.4) imip=68/88 pass=10101 acc=-1 ipm=-13.1,4.1 inv=20.2,17.2
frame=927 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=6 speed=0 near=36/92 raw=94/156 sel=92/77 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=29.5/18.3/0.0/0.0 dist=0 begin=0/2498 m0=(84,119) ml=(79,89) md=32/1/137 cxcy=84.0,119.6 guide=6.33 atg=-60.0/-60.0/-60.0 pure=4.47/5.57 yaw=-380 cmd=-580 actual=-114 signed=0 rps=5794/4206:6428/6511 duty=11/6 pwm=PWM2:11/PWM1:6 motor=2:11/1:6
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=36/92 centerNum=36/92 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=92/77 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.35@79,81 dx=-4.7 idx=0/11 dist=34/118 right=1:5.55@79,90 dx=-5.1 idx=0/14 dist=33/180 sel=1:6.83@77,85 dx=-6.9 idx=0/16 dist=32/152 edge=1:7.35@76.0,80.5 dx=-8.0 width=54.0 l=49,81 r=103,80
CxScan: raw_ref=80.0 edge=76.0,80.5 best_raw_x=60 best_err=0.33 best_cxcy=76.4,119.5 scan=0:-20.1,10:-16.9,20:-13.6,30:-10.2,40:-6.7,50:-3.2,60:0.3,70:3.9,80:7.3,90:10.8,100:14.1,110:17.4,120:20.5,130:23.5,140:26.4
ATGSeedDiag: seed=1@12,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=14(29.5) imip=4/24 pass=10111 acc=-1 ipm=52.2,84.4 inv=36.8,49.6 | 16(18.3) imip=6/26 pass=10111 acc=-1 ipm=103.0,79.8 inv=96.3,45.3

- stopped_at: 2026-06-22T14:51:37+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive123
```
