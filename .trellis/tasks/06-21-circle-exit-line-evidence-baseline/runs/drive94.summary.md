# drive94

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive94-front_car_circle_drive94.log
- remote_log: /tmp/front_car_circle_drive94.log
- started_at: 2026-06-22T06:33:55+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive94 6
```

4393 /tmp/front_car_circle_drive94.log
ATGSeedDiag: seed=1@4,108/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=37(87.7) imip=27/47 pass=11110 acc=-1 ipm=120.0,67.0 inv=108.7,36.8 | 1(5.5) imip=0/6 pass=10111 acc=-1 ipm=112.0,115.4 inv=142.8,101.6
frame=878 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/7 raw=170/20 sel=78/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=86.9/3.5/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(111,101) md=32/1/211 cxcy=84.0,119.6 guide=-33.56 atg=60.0/60.0/40.0 pure=-8.71/-3.96 yaw=2014 cmd=2214 actual=1471 signed=0 rps=1966/8034:5303/7217 duty=0/24 pwm=PWM2:0/PWM1:24 motor=2:0/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/7 centerNum=78/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.93@111,101 dx=26.7 idx=8/26 dist=34/228 right=1:-26.63@112,87 dx=28.0 idx=0/6 dist=12/12 sel=1:-34.46@113,100 dx=29.2 idx=0/16 dist=32/192 edge=1:-28.33@109.5,95.5 dx=25.5 width=41.1 l=96,80 r=123,111
CxScan: raw_ref=80.0 edge=109.5,95.5 best_raw_x=140 best_err=-3.02 best_cxcy=107.0,119.7 scan=0:-50.1,10:-48.1,20:-45.9,30:-43.5,40:-40.9,50:-38.1,60:-35.1,70:-31.8,80:-28.3,90:-24.6,100:-20.6,110:-16.5,120:-12.1,130:-7.6,140:-3.0
ATGSeedDiag: seed=1@4,108/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=35(86.9) imip=25/45 pass=11110 acc=-1 ipm=116.1,69.0 inv=105.7,37.9 | 1(3.5) imip=0/6 pass=10111 acc=-1 ipm=112.5,115.5 inv=143.9,101.7
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/7 raw=170/20 sel=78/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=86.4/1.4/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,101) md=32/1/214 cxcy=84.0,119.6 guide=-34.39 atg=60.0/56.0/28.0 pure=-8.43/-3.51 yaw=2063 cmd=2263 actual=1533 signed=0 rps=1898/8102:4225/6217 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/7 centerNum=78/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.36@110,102 dx=25.8 idx=9/25 dist=34/231 right=1:-26.74@112,87 dx=28.1 idx=0/6 dist=12/12 sel=1:-34.99@114,100 dx=30.1 idx=0/16 dist=32/194 edge=1:-28.33@109.5,95.5 dx=25.5 width=41.1 l=96,80 r=123,111
CxScan: raw_ref=80.0 edge=109.5,95.5 best_raw_x=140 best_err=-3.02 best_cxcy=107.0,119.7 scan=0:-50.1,10:-48.1,20:-45.9,30:-43.5,40:-40.9,50:-38.1,60:-35.1,70:-31.8,80:-28.3,90:-24.6,100:-20.6,110:-16.5,120:-12.1,130:-7.6,140:-3.0
ATGSeedDiag: seed=1@4,108/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=34(86.4) imip=24/44 pass=11110 acc=-1 ipm=113.6,69.6 inv=103.6,38.3 | 5(1.4) imip=0/6 pass=10111 acc=-1 ipm=121.3,111.6 inv=154.6,90.3
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/6 raw=170/20 sel=78/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=87.3/0.8/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,101) md=32/1/216 cxcy=84.0,119.6 guide=-34.28 atg=60.0/50.0/23.0 pure=-8.29/-3.35 yaw=2057 cmd=2257 actual=1565 signed=0 rps=1907/8093:4147/6160 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/6 centerNum=78/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.84@108,103 dx=23.5 idx=9/24 dist=31/228 right=1:-25.53@110,88 dx=26.1 idx=0/5 dist=10/10 sel=1:-34.94@114,100 dx=30.1 idx=0/16 dist=32/194 edge=1:-27.86@109.0,95.5 dx=25.0 width=40.5 l=96,80 r=122,111
CxScan: raw_ref=80.0 edge=109.0,95.5 best_raw_x=140 best_err=-2.42 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.5,50:-37.7,60:-34.7,70:-31.4,80:-27.9,90:-24.1,100:-20.1,110:-15.9,120:-11.5,130:-7.0,140:-2.4
ATGSeedDiag: seed=1@4,108/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=33(87.3) imip=23/43 pass=11110 acc=-1 ipm=112.2,71.0 inv=102.7,39.1 | 4(0.8) imip=0/5 pass=10111 acc=-1 ipm=119.5,112.5 inv=153.0,92.8
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/6 raw=170/20 sel=78/99 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=89.5/3.0/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(114,99) md=34/1/217 cxcy=84.0,119.6 guide=-34.18 atg=60.0/45.0/20.0 pure=-8.15/-3.15 yaw=2051 cmd=2251 actual=1588 signed=0 rps=1915/8085:4347/6330 duty=1/25 pwm=PWM2:1/PWM1:25 motor=2:1/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/6 centerNum=78/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/99 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.71@109,103 dx=24.8 idx=9/24 dist=31/230 right=1:-25.51@110,88 dx=26.1 idx=0/5 dist=10/10 sel=1:-34.86@114,99 dx=30.1 idx=0/16 dist=32/196 edge=1:-27.86@109.0,95.5 dx=25.0 width=40.5 l=96,80 r=122,111
CxScan: raw_ref=80.0 edge=109.0,95.5 best_raw_x=140 best_err=-2.42 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.5,50:-37.7,60:-34.7,70:-31.4,80:-27.9,90:-24.1,100:-20.1,110:-15.9,120:-11.5,130:-7.0,140:-2.4
ATGSeedDiag: seed=1@5,108/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=33(89.5) imip=23/43 pass=11110 acc=-1 ipm=111.5,69.7 inv=101.5,38.4 | 1(3.0) imip=0/5 pass=10111 acc=-1 ipm=113.5,115.6 inv=146.5,102.2
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/6 raw=170/19 sel=78/99 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=89.3/0.6/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,100) md=32/1/215 cxcy=84.0,119.6 guide=-34.08 atg=60.0/40.0/17.0 pure=-8.01/-3.00 yaw=2045 cmd=2245 actual=1629 signed=0 rps=1924/8076:4615/6553 duty=1/25 pwm=PWM2:1/PWM1:25 motor=2:1/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/6 centerNum=78/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/99 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.04@110,102 dx=25.6 idx=9/24 dist=32/232 right=1:-25.65@110,88 dx=26.3 idx=0/5 dist=10/10 sel=1:-34.53@114,99 dx=30.0 idx=0/16 dist=32/196 edge=1:-27.86@109.0,95.5 dx=25.0 width=40.5 l=96,80 r=122,111
CxScan: raw_ref=80.0 edge=109.0,95.5 best_raw_x=140 best_err=-2.42 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.5,50:-37.7,60:-34.7,70:-31.4,80:-27.9,90:-24.1,100:-20.1,110:-15.9,120:-11.5,130:-7.0,140:-2.4
ATGSeedDiag: seed=1@5,108/1@143,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=32(89.3) imip=22/42 pass=11110 acc=-1 ipm=110.1,71.1 inv=100.7,39.3 | 3(0.6) imip=0/5 pass=10111 acc=-1 ipm=118.0,113.4 inv=151.7,95.5
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/6 raw=170/19 sel=78/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=88.9/1.0/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,100) md=32/1/214 cxcy=84.0,119.6 guide=-33.87 atg=60.0/36.0/13.0 pure=-7.86/-2.84 yaw=2032 cmd=2232 actual=1649 signed=0 rps=1941/8059:4491/6206 duty=1/25 pwm=PWM2:1/PWM1:25 motor=2:1/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/6 centerNum=78/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.36@110,101 dx=26.3 idx=9/24 dist=34/229 right=1:-25.64@110,88 dx=26.3 idx=0/5 dist=10/10 sel=1:-34.41@114,99 dx=30.0 idx=0/16 dist=32/194 edge=1:-27.86@109.0,95.5 dx=25.0 width=40.5 l=96,80 r=122,111
CxScan: raw_ref=80.0 edge=109.0,95.5 best_raw_x=140 best_err=-2.42 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.5,50:-37.7,60:-34.7,70:-31.4,80:-27.9,90:-24.1,100:-20.1,110:-15.9,120:-11.5,130:-7.0,140:-2.4
ATGSeedDiag: seed=1@5,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=32(88.9) imip=22/42 pass=11110 acc=-1 ipm=109.3,70.4 inv=99.6,38.8 | 4(1.0) imip=0/5 pass=10111 acc=-1 ipm=120.3,112.2 inv=154.0,92.0
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=77/6 raw=170/19 sel=77/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.3/1.7/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,100) md=32/1/215 cxcy=84.0,119.6 guide=-33.67 atg=60.0/30.0/10.0 pure=-7.71/-2.63 yaw=2020 cmd=2220 actual=1669 signed=0 rps=1957/8043:4748/6292 duty=1/25 pwm=PWM2:1/PWM1:25 motor=2:1/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=77/6 centerNum=77/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.78@108,102 dx=24.0 idx=9/23 dist=31/226 right=1:-25.63@110,88 dx=26.3 idx=0/5 dist=10/10 sel=1:-34.06@114,99 dx=29.9 idx=0/16 dist=32/194 edge=1:-27.61@109.0,95.0 dx=25.0 width=41.2 l=96,79 r=122,111
CxScan: raw_ref=80.0 edge=109.0,95.0 best_raw_x=140 best_err=-2.40 best_cxcy=107.0,119.7 scan=0:-49.5,10:-47.5,20:-45.3,30:-42.9,40:-40.2,50:-37.4,60:-34.4,70:-31.1,80:-27.6,90:-23.9,100:-19.9,110:-15.7,120:-11.4,130:-6.9,140:-2.4
ATGSeedDiag: seed=1@5,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=31(90.3) imip=21/41 pass=11110 acc=-1 ipm=107.9,71.9 inv=98.7,39.8 | 1(1.7) imip=0/5 pass=10111 acc=-1 ipm=114.2,115.5 inv=148.1,101.9
frame=886 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=77/6 raw=170/21 sel=77/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=92.1/1.6/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,100) md=32/1/215 cxcy=84.0,119.6 guide=-33.31 atg=60.0/26.0/7.0 pure=-7.55/-2.42 yaw=1999 cmd=2199 actual=1696 signed=0 rps=1987/8013:4531/5791 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=77/6 centerNum=77/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.23@109,102 dx=24.8 idx=9/23 dist=33/229 right=1:-25.35@110,88 dx=25.9 idx=0/5 dist=10/10 sel=1:-33.73@114,98 dx=29.7 idx=0/16 dist=32/194 edge=1:-27.61@109.0,95.0 dx=25.0 width=41.2 l=96,79 r=122,111
CxScan: raw_ref=80.0 edge=109.0,95.0 best_raw_x=140 best_err=-2.40 best_cxcy=107.0,119.7 scan=0:-49.5,10:-47.5,20:-45.3,30:-42.9,40:-40.2,50:-37.4,60:-34.4,70:-31.1,80:-27.6,90:-23.9,100:-19.9,110:-15.7,120:-11.4,130:-6.9,140:-2.4
ATGSeedDiag: seed=1@5,108/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=31(92.1) imip=21/41 pass=11110 acc=-1 ipm=106.8,71.1 inv=97.4,39.3 | 1(1.6) imip=0/5 pass=10111 acc=-1 ipm=114.1,115.6 inv=147.9,102.2
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=77/6 raw=170/20 sel=77/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.3/0.9/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,100) md=32/1/215 cxcy=84.0,119.6 guide=-33.16 atg=60.0/21.0/5.0 pure=-7.40/-2.21 yaw=1990 cmd=2190 actual=1709 signed=0 rps=1999/8001:4798/5947 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=77/6 centerNum=77/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.82@110,101 dx=26.0 idx=9/23 dist=34/226 right=1:-25.29@110,88 dx=25.8 idx=0/5 dist=10/10 sel=1:-33.57@114,98 dx=29.6 idx=0/16 dist=32/194 edge=1:-28.08@109.5,95.0 dx=25.5 width=41.9 l=96,79 r=123,111
CxScan: raw_ref=80.0 edge=109.5,95.0 best_raw_x=140 best_err=-2.99 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.6,50:-37.8,60:-34.8,70:-31.6,80:-28.1,90:-24.4,100:-20.4,110:-16.3,120:-12.0,130:-7.5,140:-3.0
ATGSeedDiag: seed=1@5,108/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(94.3) imip=20/40 pass=11110 acc=-1 ipm=105.7,72.5 inv=96.8,40.2 | 4(0.9) imip=0/5 pass=10111 acc=-1 ipm=120.6,112.0 inv=154.1,91.4
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/6 raw=170/21 sel=75/96 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.8/1.6/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,99) md=33/1/210 cxcy=84.0,119.6 guide=-32.96 atg=60.0/17.0/3.0 pure=-7.22/-1.98 yaw=1978 cmd=2178 actual=1716 signed=0 rps=2015/7985:4574/5704 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/6 centerNum=75/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/96 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.41@108,102 dx=23.7 idx=9/22 dist=32/222 right=1:-25.16@110,88 dx=25.7 idx=0/5 dist=10/10 sel=1:-33.39@114,98 dx=29.6 idx=0/16 dist=32/190 edge=1:-28.08@109.5,95.0 dx=25.5 width=41.9 l=96,79 r=123,111
CxScan: raw_ref=80.0 edge=109.5,95.0 best_raw_x=140 best_err=-2.99 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.6,50:-37.8,60:-34.8,70:-31.6,80:-28.1,90:-24.4,100:-20.4,110:-16.3,120:-12.0,130:-7.5,140:-3.0
ATGSeedDiag: seed=1@5,108/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(90.8) imip=19/39 pass=11110 acc=-1 ipm=104.1,74.2 inv=95.6,41.3 | 2(1.6) imip=0/5 pass=10111 acc=-1 ipm=116.6,114.3 inv=150.7,98.1
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/6 raw=170/22 sel=75/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=88.7/0.7/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,99) md=33/1/213 cxcy=84.0,119.6 guide=-32.15 atg=60.0/12.0/1.0 pure=-6.89/-1.68 yaw=1929 cmd=2129 actual=1721 signed=0 rps=2082/7918:4606/6134 duty=1/25 pwm=PWM2:1/PWM1:25 motor=2:1/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/6 centerNum=75/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.13@109,101 dx=25.3 idx=9/22 dist=34/226 right=1:-25.03@110,88 dx=25.5 idx=0/5 dist=10/10 sel=1:-32.99@113,97 dx=29.4 idx=0/16 dist=32/192 edge=1:-28.08@109.5,95.0 dx=25.5 width=41.9 l=96,79 r=123,111
CxScan: raw_ref=80.0 edge=109.5,95.0 best_raw_x=140 best_err=-2.99 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.6,50:-37.8,60:-34.8,70:-31.6,80:-28.1,90:-24.4,100:-20.4,110:-16.3,120:-12.0,130:-7.5,140:-3.0
ATGSeedDiag: seed=1@5,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(88.7) imip=19/39 pass=11110 acc=-1 ipm=102.3,72.6 inv=93.3,40.2 | 4(0.7) imip=0/5 pass=10111 acc=-1 ipm=120.8,111.8 inv=154.2,91.0
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/6 raw=170/22 sel=75/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.0/1.3/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(112,99) md=33/1/213 cxcy=84.0,119.6 guide=-32.15 atg=60.0/9.0/0.0 pure=-6.76/-1.50 yaw=1929 cmd=2129 actual=1721 signed=0 rps=2082/7918:4333/6195 duty=2/25 pwm=PWM2:2/PWM1:25 motor=2:2/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/6 centerNum=75/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.90@107,102 dx=23.3 idx=9/21 dist=32/228 right=1:-24.85@109,88 dx=25.3 idx=0/5 dist=10/10 sel=1:-32.86@113,97 dx=29.4 idx=0/16 dist=32/192 edge=1:-28.54@110.0,95.0 dx=26.0 width=41.2 l=97,79 r=123,111
CxScan: raw_ref=80.0 edge=110.0,95.0 best_raw_x=140 best_err=-3.59 best_cxcy=107.0,119.7 scan=0:-50.0,10:-48.0,20:-45.8,30:-43.5,40:-40.9,50:-38.2,60:-35.2,70:-32.0,80:-28.5,90:-24.9,100:-21.0,110:-16.8,120:-12.5,130:-8.1,140:-3.6
ATGSeedDiag: seed=1@6,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(94.0) imip=18/38 pass=11110 acc=-1 ipm=101.7,74.2 inv=93.1,41.3 | 3(1.3) imip=0/5 pass=10111 acc=-1 ipm=118.8,113.0 inv=152.6,94.2
frame=891 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/6 raw=170/23 sel=75/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.1/1.7/0.0/0.0 dist=0 begin=0/2625 m0=(84,119) ml=(111,98) md=33/1/215 cxcy=84.0,119.6 guide=-31.43 atg=60.0/7.0/0.0 pure=-6.57/-1.34 yaw=1886 cmd=2050 actual=1721 signed=0 rps=2190/7810:4348/6424 duty=2/24 pwm=PWM2:2/PWM1:24 motor=2:2/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/6 centerNum=75/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.70@108,101 dx=23.7 idx=9/21 dist=32/226 right=1:-24.78@109,88 dx=25.2 idx=0/5 dist=10/10 sel=1:-32.16@113,97 dx=29.0 idx=0/16 dist=32/194 edge=1:-28.05@110.0,94.0 dx=26.0 width=41.2 l=97,78 r=123,110
CxScan: raw_ref=80.0 edge=110.0,94.0 best_raw_x=140 best_err=-3.52 best_cxcy=107.0,119.7 scan=0:-49.4,10:-47.4,20:-45.3,30:-42.9,40:-40.4,50:-37.6,60:-34.6,70:-31.5,80:-28.0,90:-24.4,100:-20.6,110:-16.5,120:-12.3,130:-8.0,140:-3.5
ATGSeedDiag: seed=1@6,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(93.1) imip=18/38 pass=11110 acc=-1 ipm=100.7,73.3 inv=91.8,40.7 | 1(1.7) imip=0/5 pass=10111 acc=-1 ipm=114.9,115.4 inv=149.4,101.5

- stopped_at: 2026-06-22T06:34:08+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive94
```
