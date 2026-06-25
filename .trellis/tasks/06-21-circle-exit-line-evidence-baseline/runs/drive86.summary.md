# drive86

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive86-front_car_circle_drive86.log
- remote_log: /tmp/front_car_circle_drive86.log
- started_at: 2026-06-22T06:18:04+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive86 6
```

3706 /tmp/front_car_circle_drive86.log
ATGSeedDiag: seed=1@4,107/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(11.5) imip=0/12 pass=10110 acc=-1 ipm=54.3,111.5 inv=16.6,91.5 | 3(9.2) imip=0/5 pass=10111 acc=-1 ipm=115.7,113.4 inv=146.9,95.5
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/6 raw=155/21 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.7/7.8/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-36.43 atg=60.0/60.0/60.0 pure=-11.52/-11.35 yaw=2186 cmd=2386 actual=1419 signed=0 rps=1731/8269:3591/5190 duty=2/27 pwm=PWM2:2/PWM1:27 motor=2:2/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/6 centerNum=53/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.81@108,104 dx=24.2 idx=9/27 dist=33/80 right=1:-25.72@110,88 dx=26.4 idx=0/5 dist=10/10 sel=1:-37.23@115,102 dx=30.8 idx=0/16 dist=32/64 edge=1:-27.15@108.0,96.0 dx=24.0 width=40.0 l=96,80 r=120,112
CxScan: raw_ref=80.0 edge=108.0,96.0 best_raw_x=140 best_err=-1.23 best_cxcy=107.0,119.7 scan=0:-49.6,10:-47.5,20:-45.3,30:-42.8,40:-40.1,50:-37.2,60:-34.1,70:-30.8,80:-27.1,90:-23.3,100:-19.2,110:-14.9,120:-10.5,130:-5.9,140:-1.2
ATGSeedDiag: seed=1@4,107/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(13.7) imip=35/52 pass=10100 acc=-1 ipm=141.7,74.2 inv=134.7,41.0 | 3(7.8) imip=0/5 pass=10111 acc=-1 ipm=115.8,113.6 inv=147.4,95.8
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/6 raw=154/20 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.1/8.5/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-35.63 atg=60.0/60.0/60.0 pure=-11.54/-11.39 yaw=2138 cmd=2338 actual=1454 signed=0 rps=1796/8204:3735/5267 duty=2/27 pwm=PWM2:2/PWM1:27 motor=2:2/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/6 centerNum=53/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.57@107,105 dx=22.6 idx=9/26 dist=32/83 right=1:-26.10@111,88 dx=26.8 idx=0/5 dist=10/10 sel=1:-37.44@115,102 dx=31.0 idx=0/16 dist=32/64 edge=1:-27.63@108.5,96.0 dx=24.5 width=40.6 l=96,80 r=121,112
CxScan: raw_ref=80.0 edge=108.5,96.0 best_raw_x=140 best_err=-1.84 best_cxcy=107.0,119.7 scan=0:-49.9,10:-47.8,20:-45.6,30:-43.1,40:-40.5,50:-37.6,60:-34.5,70:-31.2,80:-27.6,90:-23.8,100:-19.8,110:-15.5,120:-11.1,130:-6.5,140:-1.8
ATGSeedDiag: seed=1@4,107/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.1) imip=0/20 pass=10110 acc=-1 ipm=66.4,97.5 inv=49.7,64.2 | 4(8.5) imip=0/5 pass=10111 acc=-1 ipm=118.4,112.8 inv=151.2,93.7
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/6 raw=154/20 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.2/8.2/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/69 cxcy=84.0,119.6 guide=-35.63 atg=60.0/60.0/60.0 pure=-11.54/-11.48 yaw=2138 cmd=2338 actual=1493 signed=0 rps=1796/8204:4248/5746 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/6 centerNum=52/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.56@107,105 dx=22.6 idx=9/26 dist=32/81 right=1:-26.26@111,88 dx=27.0 idx=0/5 dist=10/10 sel=1:-37.43@115,102 dx=31.0 idx=0/16 dist=32/62 edge=1:-27.63@108.5,96.0 dx=24.5 width=40.6 l=96,80 r=121,112
CxScan: raw_ref=80.0 edge=108.5,96.0 best_raw_x=140 best_err=-1.84 best_cxcy=107.0,119.7 scan=0:-49.9,10:-47.8,20:-45.6,30:-43.1,40:-40.5,50:-37.6,60:-34.5,70:-31.2,80:-27.6,90:-23.8,100:-19.8,110:-15.5,120:-11.1,130:-6.5,140:-1.8
ATGSeedDiag: seed=1@4,107/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(12.2) imip=34/51 pass=10110 acc=-1 ipm=139.7,74.2 inv=132.6,41.0 | 2(8.2) imip=0/5 pass=10111 acc=-1 ipm=114.1,114.4 inv=145.5,98.5
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/6 raw=155/19 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.3/7.3/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-36.43 atg=60.0/60.0/60.0 pure=-11.52/-11.35 yaw=2186 cmd=2386 actual=1534 signed=0 rps=1731/8269:4145/5355 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/6 centerNum=53/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.90@108,104 dx=24.3 idx=9/27 dist=33/80 right=1:-26.39@111,88 dx=27.2 idx=0/5 dist=10/10 sel=1:-37.22@115,102 dx=30.8 idx=0/16 dist=32/64 edge=1:-27.63@108.5,96.0 dx=24.5 width=40.6 l=96,80 r=121,112
CxScan: raw_ref=80.0 edge=108.5,96.0 best_raw_x=140 best_err=-1.84 best_cxcy=107.0,119.7 scan=0:-49.9,10:-47.8,20:-45.6,30:-43.1,40:-40.5,50:-37.6,60:-34.5,70:-31.2,80:-27.6,90:-23.8,100:-19.8,110:-15.5,120:-11.1,130:-6.5,140:-1.8
ATGSeedDiag: seed=1@4,107/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(13.3) imip=35/52 pass=10100 acc=-1 ipm=141.9,74.2 inv=134.8,41.0 | 4(7.3) imip=0/5 pass=10111 acc=-1 ipm=118.6,112.9 inv=151.8,93.9
frame=886 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/6 raw=154/19 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.0/8.9/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-36.43 atg=60.0/60.0/60.0 pure=-11.51/-11.35 yaw=2186 cmd=2386 actual=1578 signed=0 rps=1731/8269:4361/5409 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/6 centerNum=53/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.47@107,104 dx=22.7 idx=9/26 dist=32/81 right=1:-26.79@112,88 dx=27.6 idx=0/5 dist=10/10 sel=1:-37.21@115,102 dx=30.8 idx=0/16 dist=32/64 edge=1:-27.63@108.5,96.0 dx=24.5 width=40.6 l=96,80 r=121,112
CxScan: raw_ref=80.0 edge=108.5,96.0 best_raw_x=140 best_err=-1.84 best_cxcy=107.0,119.7 scan=0:-49.9,10:-47.8,20:-45.6,30:-43.1,40:-40.5,50:-37.6,60:-34.5,70:-31.2,80:-27.6,90:-23.8,100:-19.8,110:-15.5,120:-11.1,130:-6.5,140:-1.8
ATGSeedDiag: seed=1@4,107/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.0) imip=0/20 pass=10110 acc=-1 ipm=66.4,97.5 inv=49.7,64.2 | 1(8.9) imip=0/5 pass=10111 acc=-1 ipm=112.4,115.4 inv=143.7,101.7
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/6 raw=154/18 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.3/7.5/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-36.31 atg=60.0/60.0/60.0 pure=-11.48/-11.31 yaw=2179 cmd=2379 actual=1617 signed=0 rps=1740/8260:4485/5543 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/6 centerNum=53/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.48@107,104 dx=22.7 idx=9/26 dist=32/82 right=1:-26.94@112,88 dx=27.8 idx=0/5 dist=10/10 sel=1:-37.09@115,102 dx=30.8 idx=0/16 dist=32/64 edge=1:-27.63@108.5,96.0 dx=24.5 width=40.6 l=96,80 r=121,112
CxScan: raw_ref=80.0 edge=108.5,96.0 best_raw_x=140 best_err=-1.84 best_cxcy=107.0,119.7 scan=0:-49.9,10:-47.8,20:-45.6,30:-43.1,40:-40.5,50:-37.6,60:-34.5,70:-31.2,80:-27.6,90:-23.8,100:-19.8,110:-15.5,120:-11.1,130:-6.5,140:-1.8
ATGSeedDiag: seed=1@4,107/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(11.3) imip=36/52 pass=10100 acc=-1 ipm=144.2,74.2 inv=137.3,41.0 | 4(7.5) imip=0/5 pass=10111 acc=-1 ipm=119.0,113.0 inv=152.9,94.1
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/5 raw=154/18 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/7.4/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-36.43 atg=60.0/60.0/60.0 pure=-11.50/-11.31 yaw=2186 cmd=2386 actual=1654 signed=0 rps=1731/8269:4250/5403 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/5 centerNum=53/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.41@109,104 dx=24.7 idx=9/27 dist=33/81 right=1:-25.06@109,89 dx=25.2 idx=0/4 dist=8/8 sel=1:-37.28@115,102 dx=30.9 idx=0/16 dist=32/64 edge=1:-26.91@107.5,96.5 dx=23.5 width=40.2 l=96,80 r=119,113
CxScan: raw_ref=80.0 edge=107.5,96.5 best_raw_x=140 best_err=-0.62 best_cxcy=107.0,119.7 scan=0:-49.7,10:-47.6,20:-45.3,30:-42.8,40:-40.1,50:-37.2,60:-34.0,70:-30.6,80:-26.9,90:-23.0,100:-18.8,110:-14.5,120:-10.0,130:-5.3,140:-0.6
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(12.5) imip=35/52 pass=10100 acc=-1 ipm=142.0,74.2 inv=135.0,41.0 | 1(7.4) imip=0/4 pass=10111 acc=-1 ipm=112.8,115.4 inv=144.6,101.7
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/5 raw=155/17 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.3/5.7/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-35.82 atg=60.0/60.0/60.0 pure=-11.51/-11.35 yaw=2149 cmd=2349 actual=1696 signed=0 rps=1780/8220:4368/5860 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/5 centerNum=53/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.61@107,105 dx=22.6 idx=9/26 dist=32/82 right=1:-25.35@110,89 dx=25.5 idx=0/4 dist=8/8 sel=1:-37.61@115,102 dx=31.1 idx=0/16 dist=32/64 edge=1:-26.91@107.5,96.5 dx=23.5 width=40.2 l=96,80 r=119,113
CxScan: raw_ref=80.0 edge=107.5,96.5 best_raw_x=140 best_err=-0.62 best_cxcy=107.0,119.7 scan=0:-49.7,10:-47.6,20:-45.3,30:-42.8,40:-40.1,50:-37.2,60:-34.0,70:-30.6,80:-26.9,90:-23.0,100:-18.8,110:-14.5,120:-10.0,130:-5.3,140:-0.6
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(13.3) imip=35/52 pass=10100 acc=-1 ipm=142.0,74.3 inv=135.0,41.1 | 3(5.7) imip=0/4 pass=10111 acc=-1 ipm=117.2,113.8 inv=150.8,96.4
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/5 raw=155/17 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.6/6.1/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/72 cxcy=84.0,119.6 guide=-36.33 atg=60.0/60.0/60.0 pure=-11.53/-11.38 yaw=2180 cmd=2380 actual=1743 signed=0 rps=1738/8262:4110/5819 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/5 centerNum=53/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.32@108,104 dx=24.4 idx=9/27 dist=33/81 right=1:-25.69@110,89 dx=25.9 idx=0/4 dist=8/8 sel=1:-37.84@115,102 dx=31.3 idx=0/16 dist=32/64 edge=1:-28.14@108.5,97.0 dx=24.5 width=39.4 l=97,81 r=120,113
CxScan: raw_ref=80.0 edge=108.5,97.0 best_raw_x=140 best_err=-1.88 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.4,20:-46.2,30:-43.8,40:-41.1,50:-38.2,60:-35.1,70:-31.8,80:-28.1,90:-24.3,100:-20.2,110:-15.8,120:-11.3,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(12.6) imip=32/52 pass=10110 acc=-1 ipm=135.2,74.1 inv=127.9,41.0 | 2(6.1) imip=0/4 pass=10111 acc=-1 ipm=115.1,114.6 inv=148.1,99.0
frame=891 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/5 raw=154/17 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.0/6.0/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-35.96 atg=60.0/60.0/60.0 pure=-11.56/-11.42 yaw=2157 cmd=2357 actual=1789 signed=0 rps=1769/8231:4115/6083 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/5 centerNum=53/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.85@107,105 dx=22.7 idx=9/26 dist=32/83 right=1:-25.78@110,89 dx=26.0 idx=0/4 dist=8/8 sel=1:-37.71@115,102 dx=31.2 idx=0/16 dist=32/64 edge=1:-28.14@108.5,97.0 dx=24.5 width=39.4 l=97,81 r=120,113
CxScan: raw_ref=80.0 edge=108.5,97.0 best_raw_x=140 best_err=-1.88 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.4,20:-46.2,30:-43.8,40:-41.1,50:-38.2,60:-35.1,70:-31.8,80:-28.1,90:-24.3,100:-20.2,110:-15.8,120:-11.3,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.0) imip=0/20 pass=10110 acc=-1 ipm=66.6,97.6 inv=49.9,64.4 | 2(6.0) imip=0/4 pass=10111 acc=-1 ipm=115.1,114.6 inv=148.2,99.1
frame=892 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=154/17 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.8/5.6/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/69 cxcy=84.0,119.6 guide=-35.96 atg=60.0/60.0/60.0 pure=-11.56/-11.48 yaw=2157 cmd=2357 actual=1825 signed=0 rps=1769/8231:3889/5971 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.85@107,105 dx=22.7 idx=9/26 dist=32/80 right=1:-25.74@110,89 dx=25.9 idx=0/4 dist=8/8 sel=1:-37.71@115,102 dx=31.2 idx=0/16 dist=32/62 edge=1:-27.65@108.0,97.0 dx=24.0 width=38.8 l=97,81 r=119,113
CxScan: raw_ref=80.0 edge=108.0,97.0 best_raw_x=140 best_err=-1.25 best_cxcy=107.0,119.7 scan=0:-50.2,10:-48.2,20:-45.9,30:-43.4,40:-40.7,50:-37.8,60:-34.7,70:-31.3,80:-27.7,90:-23.7,100:-19.6,110:-15.2,120:-10.7,130:-6.0,140:-1.3
ATGSeedDiag: seed=1@4,107/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(13.8) imip=32/51 pass=10110 acc=-1 ipm=135.3,74.1 inv=127.9,41.0 | 3(5.6) imip=0/4 pass=10111 acc=-1 ipm=117.2,114.0 inv=151.2,97.1
frame=893 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=154/16 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.8/5.9/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/69 cxcy=84.0,119.6 guide=-35.96 atg=60.0/60.0/60.0 pure=-11.56/-11.48 yaw=2157 cmd=2357 actual=1865 signed=0 rps=1769/8231:4004/6282 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.61@107,105 dx=22.6 idx=9/26 dist=33/81 right=1:-26.10@110,89 dx=26.4 idx=0/4 dist=8/8 sel=1:-37.70@115,102 dx=31.1 idx=0/16 dist=32/62 edge=1:-27.88@108.5,96.5 dx=24.5 width=40.2 l=97,80 r=120,113
CxScan: raw_ref=80.0 edge=108.5,96.5 best_raw_x=140 best_err=-1.86 best_cxcy=107.0,119.7 scan=0:-50.2,10:-48.1,20:-45.9,30:-43.4,40:-40.8,50:-37.9,60:-34.8,70:-31.5,80:-27.9,90:-24.0,100:-19.9,110:-15.6,120:-11.2,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@4,107/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(13.8) imip=32/51 pass=10110 acc=-1 ipm=135.3,74.1 inv=127.9,41.0 | 1(5.9) imip=0/4 pass=10111 acc=-1 ipm=113.3,115.5 inv=146.1,102.0
frame=894 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/5 raw=154/16 sel=53/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.1/6.7/0.0/0.0 dist=0 begin=0/3293 m0=(84,119) ml=(113,103) md=33/1/71 cxcy=84.0,119.6 guide=-35.96 atg=60.0/60.0/60.0 pure=-11.54/-11.39 yaw=2157 cmd=2357 actual=1880 signed=0 rps=1769/8231:4077/6452 duty=1/25 pwm=PWM2:1/PWM1:25 motor=2:1/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/5 centerNum=53/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.67@107,105 dx=22.7 idx=9/26 dist=33/83 right=1:-26.33@111,89 dx=26.7 idx=0/4 dist=8/8 sel=1:-37.69@115,102 dx=31.1 idx=0/16 dist=32/64 edge=1:-27.88@108.5,96.5 dx=24.5 width=40.2 l=97,80 r=120,113
CxScan: raw_ref=80.0 edge=108.5,96.5 best_raw_x=140 best_err=-1.86 best_cxcy=107.0,119.7 scan=0:-50.2,10:-48.1,20:-45.9,30:-43.4,40:-40.8,50:-37.9,60:-34.8,70:-31.5,80:-27.9,90:-24.0,100:-19.9,110:-15.6,120:-11.2,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@4,107/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(12.1) imip=32/52 pass=10110 acc=-1 ipm=135.3,74.1 inv=127.9,41.0 | 1(6.7) imip=0/4 pass=10111 acc=-1 ipm=113.3,115.5 inv=146.1,102.0

- stopped_at: 2026-06-22T06:18:17+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive86
```
