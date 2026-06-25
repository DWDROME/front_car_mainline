# drive91

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive91-front_car_circle_drive91.log
- remote_log: /tmp/front_car_circle_drive91.log
- started_at: 2026-06-22T06:31:41+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive91 6
```

4032 /tmp/front_car_circle_drive91.log
ATGSeedDiag: seed=1@34,108/1@155,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=59(10.1) imip=49/69 pass=10100 acc=-1 ipm=26.0,5.6 inv=41.2,17.4 | 33(21.1) imip=23/43 pass=10111 acc=-1 ipm=70.0,57.7 inv=62.1,32.4
frame=890 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=17/82 raw=47/170 sel=82/106 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.2/22.4/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(65,96) md=33/1/227 cxcy=84.0,119.6 guide=22.90 atg=-60.0/-30.0/-11.0 pure=6.28/2.41 yaw=-1374 cmd=-1574 actual=380 signed=0 rps=7158/2842:4383/4953 duty=20/5 pwm=PWM2:20/PWM1:5 motor=2:20/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=17/82 centerNum=17/82 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=82/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:27.39@48,74 dx=-35.7 idx=0/16 dist=32/32 right=1:21.74@66,97 dx=-18.3 idx=8/22 dist=34/247 sel=1:23.50@63,95 dx=-20.8 idx=0/16 dist=32/210 edge=1:25.48@56.5,85.0 dx=-27.5 width=51.1 l=33,95 r=80,75
CxScan: raw_ref=80.0 edge=56.5,85.0 best_raw_x=10 best_err=0.64 best_cxcy=57.1,119.4 scan=0:-3.2,10:0.6,20:4.5,30:8.2,40:11.9,50:15.5,60:19.0,70:22.3,80:25.5,90:28.5,100:31.3,110:34.0,120:36.5,130:38.9,140:41.1
ATGSeedDiag: seed=1@33,108/1@155,102 begin=7,108 block=5 clip=8
ATGLptDiag: best=14(7.2) imip=4/16 pass=10111 acc=-1 ipm=36.9,98.3 inv=3.7,65.8 | 33(22.4) imip=23/43 pass=10111 acc=-1 ipm=69.3,58.1 inv=61.4,32.6
frame=891 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/82 raw=41/170 sel=82/106 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=4.5/21.1/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(64,96) md=34/1/228 cxcy=84.0,119.6 guide=22.19 atg=-60.0/-31.0/-11.0 pure=6.28/2.44 yaw=-1331 cmd=-1531 actual=313 signed=0 rps=7098/2902:4470/4864 duty=19/6 pwm=PWM2:19/PWM1:6 motor=2:19/1:6
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=14/82 centerNum=14/82 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=82/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:26.43@52,78 dx=-32.3 idx=0/13 dist=27/27 right=1:22.22@65,97 dx=-18.6 idx=8/22 dist=33/246 sel=1:24.07@63,95 dx=-21.4 idx=0/16 dist=32/210 edge=1:23.88@60.0,88.5 dx=-24.0 width=49.6 l=38,100 r=82,77
CxScan: raw_ref=80.0 edge=60.0,88.5 best_raw_x=15 best_err=-0.99 best_cxcy=59.1,119.4 scan=0:-7.1,10:-3.0,20:1.0,30:5.1,40:9.1,50:13.0,60:16.8,70:20.4,80:23.9,90:27.2,100:30.3,110:33.2,120:35.9,130:38.4,140:40.8
ATGSeedDiag: seed=1@31,108/1@155,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(4.5) imip=2/13 pass=10111 acc=-1 ipm=39.5,101.3 inv=4.0,70.4 | 33(21.1) imip=23/43 pass=10111 acc=-1 ipm=69.0,58.4 inv=61.1,32.7
frame=892 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/81 raw=33/170 sel=81/104 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.6/21.4/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(63,97) md=32/1/224 cxcy=84.0,119.6 guide=24.74 atg=-60.0/-31.0/-12.0 pure=6.39/2.46 yaw=-1484 cmd=-1684 actual=237 signed=0 rps=7308/2692:4890/4934 duty=19/5 pwm=PWM2:19/PWM1:5 motor=2:19/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/81 centerNum=11/81 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=81/104 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:25.57@55,82 dx=-29.2 idx=0/10 dist=20/20 right=1:23.49@65,98 dx=-19.5 idx=8/22 dist=34/242 sel=1:25.90@61,95 dx=-23.1 idx=0/16 dist=32/206 edge=1:24.69@60.0,90.5 dx=-24.0 width=46.6 l=41,104 r=79,77
CxScan: raw_ref=80.0 edge=60.0,90.5 best_raw_x=15 best_err=-1.03 best_cxcy=59.1,119.4 scan=0:-7.3,10:-3.1,20:1.1,30:5.3,40:9.4,50:13.5,60:17.4,70:21.1,80:24.7,90:28.0,100:31.2,110:34.2,120:36.9,130:39.5,140:41.9
ATGSeedDiag: seed=1@27,108/1@155,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(3.6) imip=0/10 pass=10111 acc=-1 ipm=43.3,105.5 inv=4.4,78.0 | 33(21.4) imip=23/43 pass=10111 acc=-1 ipm=68.1,59.3 inv=60.3,33.1
frame=893 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=10/81 raw=30/170 sel=81/104 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.7/19.4/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(62,97) md=33/1/226 cxcy=84.0,119.6 guide=26.09 atg=-60.0/-32.0/-11.0 pure=6.42/2.48 yaw=-1566 cmd=-1766 actual=139 signed=0 rps=7420/2580:5237/4848 duty=19/5 pwm=PWM2:19/PWM1:5 motor=2:19/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=10/81 centerNum=10/81 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=81/104 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:25.38@56,83 dx=-28.3 idx=0/9 dist=18/18 right=1:24.24@64,98 dx=-20.0 idx=8/22 dist=33/241 sel=1:26.73@60,96 dx=-23.7 idx=0/16 dist=32/206 edge=1:25.11@60.0,91.5 dx=-24.0 width=46.2 l=42,106 r=78,77
CxScan: raw_ref=80.0 edge=60.0,91.5 best_raw_x=15 best_err=-1.05 best_cxcy=59.1,119.4 scan=0:-7.5,10:-3.2,20:1.1,30:5.4,40:9.6,50:13.7,60:17.7,70:21.5,80:25.1,90:28.5,100:31.7,110:34.7,120:37.4,130:40.0,140:42.4
ATGSeedDiag: seed=1@25,108/1@155,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(3.7) imip=0/9 pass=10111 acc=-1 ipm=44.3,106.8 inv=4.2,80.7 | 34(19.4) imip=24/44 pass=10111 acc=-1 ipm=67.8,57.2 inv=60.2,32.2
frame=894 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/80 raw=27/170 sel=80/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.5/19.8/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(61,97) md=33/1/222 cxcy=84.0,119.6 guide=27.00 atg=-60.0/-29.0/-10.0 pure=6.43/2.41 yaw=-1620 cmd=-1820 actual=46 signed=0 rps=7494/2506:5114/4458 duty=20/5 pwm=PWM2:20/PWM1:5 motor=2:20/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/80 centerNum=9/80 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=80/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:25.17@57,84 dx=-27.5 idx=0/8 dist=16/16 right=1:25.45@63,99 dx=-21.0 idx=8/22 dist=32/240 sel=1:27.55@60,96 dx=-24.5 idx=0/16 dist=32/204 edge=1:24.87@60.5,92.0 dx=-23.5 width=46.1 l=43,107 r=78,77
CxScan: raw_ref=80.0 edge=60.5,92.0 best_raw_x=20 best_err=0.55 best_cxcy=61.0,119.4 scan=0:-8.1,10:-3.8,20:0.6,30:4.9,40:9.2,50:13.3,60:17.4,70:21.2,80:24.9,90:28.3,100:31.5,110:34.6,120:37.4,130:40.0,140:42.4
ATGSeedDiag: seed=1@23,108/1@155,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.5) imip=0/8 pass=10111 acc=-1 ipm=57.4,115.1 inv=18.2,101.8 | 32(19.8) imip=22/42 pass=10111 acc=-1 ipm=68.3,61.9 inv=60.1,34.4
frame=895 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=7/78 raw=24/170 sel=78/101 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.1/19.9/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(61,97) md=33/1/221 cxcy=84.0,119.6 guide=27.26 atg=-60.0/-27.0/-8.0 pure=6.39/2.33 yaw=-1635 cmd=-1835 actual=-46 signed=0 rps=7516/2484:5365/4518 duty=20/5 pwm=PWM2:20/PWM1:5 motor=2:20/1:5
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=7/78 centerNum=7/78 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/101 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:23.80@59,87 dx=-24.8 idx=0/6 dist=12/12 right=1:26.12@63,99 dx=-21.5 idx=8/22 dist=32/233 sel=1:28.30@59,96 dx=-25.3 idx=0/16 dist=32/200 edge=1:25.08@60.5,92.5 dx=-23.5 width=43.9 l=46,109 r=75,76
CxScan: raw_ref=80.0 edge=60.5,92.5 best_raw_x=20 best_err=0.56 best_cxcy=61.0,119.4 scan=0:-8.2,10:-3.8,20:0.6,30:4.9,40:9.3,50:13.5,60:17.5,70:21.4,80:25.1,90:28.5,100:31.8,110:34.8,120:37.6,130:40.3,140:42.7
ATGSeedDiag: seed=1@20,108/1@155,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(2.1) imip=0/6 pass=10111 acc=-1 ipm=54.3,113.7 inv=13.3,97.7 | 33(19.9) imip=23/43 pass=10111 acc=-1 ipm=68.1,59.8 inv=60.2,33.4
frame=896 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/78 raw=21/170 sel=78/100 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.0/23.4/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(59,97) md=34/1/218 cxcy=84.0,119.6 guide=28.02 atg=-60.0/-25.0/-7.0 pure=6.32/2.23 yaw=-1681 cmd=-1881 actual=-131 signed=0 rps=7578/2422:5205/4361 duty=20/4 pwm=PWM2:20/PWM1:4 motor=2:20/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/78 centerNum=6/78 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/100 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:23.33@60,88 dx=-23.7 idx=0/5 dist=10/10 right=1:28.63@59,97 dx=-24.8 idx=9/23 dist=33/228 sel=1:29.50@57,96 dx=-26.6 idx=0/16 dist=32/198 edge=1:25.08@60.5,92.5 dx=-23.5 width=44.2 l=47,110 r=74,75
CxScan: raw_ref=80.0 edge=60.5,92.5 best_raw_x=20 best_err=0.56 best_cxcy=61.0,119.4 scan=0:-8.2,10:-3.8,20:0.6,30:4.9,40:9.3,50:13.5,60:17.5,70:21.4,80:25.1,90:28.5,100:31.8,110:34.8,120:37.6,130:40.3,140:42.7
ATGSeedDiag: seed=1@18,108/1@155,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(3.0) imip=0/5 pass=10111 acc=-1 ipm=53.4,113.7 inv=11.4,97.7 | 32(23.4) imip=22/42 pass=10111 acc=-1 ipm=68.3,62.3 inv=60.0,34.6
frame=897 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/77 raw=19/170 sel=77/99 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.9/20.8/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(59,97) md=33/1/219 cxcy=84.0,119.6 guide=29.02 atg=-60.0/-25.0/-6.0 pure=6.31/2.21 yaw=-1741 cmd=-1941 actual=-203 signed=0 rps=7661/2339:5380/4668 duty=20/4 pwm=PWM2:20/PWM1:4 motor=2:20/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/77 centerNum=6/77 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/99 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:24.03@59,88 dx=-24.5 idx=0/5 dist=10/10 right=1:27.45@61,99 dx=-22.6 idx=9/22 dist=32/231 sel=1:29.74@57,96 dx=-26.9 idx=0/16 dist=32/196 edge=1:26.01@59.5,92.5 dx=-24.5 width=44.2 l=46,110 r=73,75
CxScan: raw_ref=80.0 edge=59.5,92.5 best_raw_x=15 best_err=-0.50 best_cxcy=59.1,119.4 scan=0:-7.1,10:-2.7,20:1.7,30:6.1,40:10.4,50:14.5,60:18.6,70:22.4,80:26.0,90:29.4,100:32.6,110:35.6,120:38.3,130:40.9,140:43.3
ATGSeedDiag: seed=1@16,108/1@155,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.9) imip=0/5 pass=10111 acc=-1 ipm=54.6,114.9 inv=12.0,101.3 | 33(20.8) imip=23/43 pass=10111 acc=-1 ipm=68.3,60.1 inv=60.3,33.5
frame=898 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/78 raw=17/170 sel=78/100 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=4.1/22.6/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(59,97) md=33/1/220 cxcy=84.0,119.6 guide=29.21 atg=-60.0/-24.0/-6.0 pure=6.29/2.16 yaw=-1753 cmd=-1953 actual=-255 signed=0 rps=7676/2324:5118/4694 duty=21/4 pwm=PWM2:21/PWM1:4 motor=2:21/1:4
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/78 centerNum=5/78 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/100 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:23.44@61,89 dx=-23.3 idx=0/4 dist=8/8 right=1:28.13@61,99 dx=-23.2 idx=9/22 dist=33/235 sel=1:29.99@57,96 dx=-27.1 idx=0/16 dist=32/198 edge=1:25.02@61.5,94.5 dx=-22.5 width=44.2 l=48,112 r=75,77
CxScan: raw_ref=80.0 edge=61.5,94.5 best_raw_x=20 best_err=-0.61 best_cxcy=61.0,119.4 scan=0:-9.7,10:-5.2,20:-0.6,30:4.0,40:8.5,50:12.9,60:17.1,70:21.2,80:25.0,90:28.6,100:32.0,110:35.1,120:38.0,130:40.7,140:43.2
ATGSeedDiag: seed=1@14,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(4.1) imip=0/4 pass=10111 acc=-1 ipm=53.9,115.0 inv=10.3,101.6 | 32(22.6) imip=22/42 pass=10111 acc=-1 ipm=68.4,62.3 inv=60.1,34.6
frame=899 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/78 raw=13/170 sel=78/100 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.5/22.0/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(58,97) md=34/1/219 cxcy=84.0,119.6 guide=29.41 atg=-60.0/-24.0/-6.0 pure=6.28/2.15 yaw=-1764 cmd=-1964 actual=-314 signed=0 rps=7692/2308:5305/5191 duty=20/3 pwm=PWM2:20/PWM1:3 motor=2:20/1:3
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/78 centerNum=4/78 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/100 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:23.41@61,90 dx=-23.0 idx=0/3 dist=6/6 right=1:28.31@61,99 dx=-23.3 idx=9/22 dist=31/234 sel=1:30.30@57,96 dx=-27.4 idx=0/16 dist=32/198 edge=1:24.53@62.0,94.5 dx=-22.0 width=43.6 l=49,112 r=75,77
CxScan: raw_ref=80.0 edge=62.0,94.5 best_raw_x=25 best_err=1.09 best_cxcy=62.9,119.4 scan=0:-10.3,10:-5.8,20:-1.2,30:3.4,40:7.9,50:12.3,60:16.6,70:20.7,80:24.5,90:28.2,100:31.6,110:34.7,120:37.7,130:40.4,140:42.9
ATGSeedDiag: seed=1@11,107/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(2.5) imip=0/3 pass=10111 acc=-1 ipm=50.5,113.7 inv=5.1,97.7 | 32(22.0) imip=22/42 pass=10111 acc=-1 ipm=68.4,62.4 inv=60.1,34.6
frame=900 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/78 raw=11/170 sel=78/101 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.3/21.2/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(58,97) md=33/1/218 cxcy=84.0,119.6 guide=29.79 atg=-60.0/-22.0/-5.0 pure=6.26/2.10 yaw=-1787 cmd=-1987 actual=-373 signed=0 rps=7723/2277:4984/4939 duty=21/3 pwm=PWM2:21/PWM1:3 motor=2:21/1:3
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/78 centerNum=3/78 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/101 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.80@62,91 dx=-21.9 idx=0/2 dist=4/4 right=1:29.09@60,99 dx=-24.3 idx=9/22 dist=32/234 sel=1:30.54@56,96 dx=-27.7 idx=0/16 dist=32/200 edge=1:24.99@62.0,95.5 dx=-22.0 width=44.1 l=50,114 r=74,77
CxScan: raw_ref=80.0 edge=62.0,95.5 best_raw_x=25 best_err=1.11 best_cxcy=62.9,119.4 scan=0:-10.5,10:-5.9,20:-1.2,30:3.4,40:8.1,50:12.6,60:16.9,70:21.1,80:25.0,90:28.7,100:32.1,110:35.3,120:38.2,130:41.0,140:43.5
ATGSeedDiag: seed=1@11,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.3) imip=0/2 pass=10111 acc=-1 ipm=52.3,115.1 inv=6.4,102.0 | 31(21.2) imip=21/41 pass=10111 acc=-1 ipm=68.7,64.2 inv=60.1,35.6
frame=901 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/76 raw=9/170 sel=76/99 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/21.8/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(58,98) md=32/1/214 cxcy=84.0,119.6 guide=30.39 atg=-60.0/-21.0/-4.0 pure=6.25/2.04 yaw=-1823 cmd=-2023 actual=-441 signed=0 rps=7773/2227:5178/5103 duty=21/3 pwm=PWM2:21/PWM1:3 motor=2:21/1:3
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/76 centerNum=2/76 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=76/99 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.45@63,92 dx=-21.1 idx=0/1 dist=2/2 right=1:29.65@59,99 dx=-24.9 idx=9/22 dist=33/228 sel=1:30.96@56,96 dx=-28.1 idx=0/16 dist=32/196 edge=1:24.72@62.5,96.0 dx=-21.5 width=44.4 l=51,115 r=74,77
CxScan: raw_ref=80.0 edge=62.5,96.0 best_raw_x=25 best_err=0.51 best_cxcy=62.9,119.4 scan=0:-11.2,10:-6.6,20:-1.9,30:2.9,40:7.5,50:12.1,60:16.5,70:20.7,80:24.7,90:28.5,100:31.9,110:35.2,120:38.2,130:40.9,140:43.5
ATGSeedDiag: seed=1@9,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 31(21.8) imip=21/41 pass=10111 acc=-1 ipm=68.9,64.3 inv=60.3,35.6
frame=902 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/76 raw=6/170 sel=76/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/26.4/0.0/0.0 dist=0 begin=0/2668 m0=(84,119) ml=(57,98) md=33/1/214 cxcy=84.0,119.6 guide=30.25 atg=-60.0/-19.0/-3.0 pure=6.23/1.95 yaw=-1815 cmd=-2015 actual=-505 signed=0 rps=7762/2238:5003/4803 duty=21/3 pwm=PWM2:21/PWM1:3 motor=2:21/1:3
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/76 centerNum=2/76 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=76/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:22.91@62,92 dx=-21.5 idx=0/1 dist=2/2 right=1:30.52@58,99 dx=-26.0 idx=9/22 dist=34/229 sel=1:31.42@56,96 dx=-28.5 idx=0/16 dist=32/194 edge=1:24.72@62.5,96.0 dx=-21.5 width=44.4 l=51,115 r=74,77
CxScan: raw_ref=80.0 edge=62.5,96.0 best_raw_x=25 best_err=0.51 best_cxcy=62.9,119.4 scan=0:-11.2,10:-6.6,20:-1.9,30:2.9,40:7.5,50:12.1,60:16.5,70:20.7,80:24.7,90:28.5,100:31.9,110:35.2,120:38.2,130:40.9,140:43.5
ATGSeedDiag: seed=1@7,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 30(26.4) imip=20/40 pass=10111 acc=-1 ipm=69.2,66.4 inv=60.3,36.7

- stopped_at: 2026-06-22T06:31:54+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive91
```
