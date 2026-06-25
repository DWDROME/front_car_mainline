# drive143

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive143-front_car_circle_drive143.log
- remote_log: /tmp/front_car_circle_drive143.log
- started_at: 2026-06-22T15:17:20+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive143 6
```

4695 /tmp/front_car_circle_drive143.log
LineErr: aim=41 cxcy=84.0,119.6 left=1:-24.96@104,100 dx=19.8 idx=10/27 dist=40/94 right=1:-29.49@117,84 dx=33.2 idx=0/11 dist=24/24 sel=1:-33.91@114,98 dx=29.9 idx=0/20 dist=40/74 edge=1:-30.90@115.0,91.0 dx=31.0 width=40.2 l=106,73 r=124,109
CxScan: raw_ref=80.0 edge=115.0,91.0 best_raw_x=140 best_err=-8.76 best_cxcy=107.0,119.7 scan=0:-50.1,10:-48.3,20:-46.3,30:-44.2,40:-41.9,50:-39.4,60:-36.8,70:-33.9,80:-30.9,90:-27.7,100:-24.2,110:-20.6,120:-16.8,130:-12.8,140:-8.8
ATGSeedDiag: seed=1@4,87/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(13.3) imip=0/11 pass=10110 acc=-1 ipm=47.8,106.8 inv=10.5,80.6 | 1(20.6) imip=0/11 pass=10111 acc=-1 ipm=101.6,115.1 inv=118.7,100.9
frame=915 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=55/12 raw=153/44 sel=55/38 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.5/18.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(112,99) md=41/1/82 cxcy=84.0,119.6 guide=-32.43 atg=60.0/60.0/60.0 pure=-11.45/-11.00 yaw=2594 cmd=2794 actual=2384 signed=0 rps=0/6523:5262/7896 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=55/12 centerNum=55/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=55/38 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-24.85@104,101 dx=19.6 idx=10/27 dist=41/94 right=1:-29.65@117,84 dx=33.3 idx=0/11 dist=24/24 sel=1:-34.05@114,98 dx=30.0 idx=0/20 dist=40/74 edge=1:-31.55@115.5,91.5 dx=31.5 width=38.9 l=107,74 r=124,109
CxScan: raw_ref=80.0 edge=115.5,91.5 best_raw_x=140 best_err=-9.39 best_cxcy=107.0,119.7 scan=0:-50.6,10:-48.8,20:-46.9,30:-44.8,40:-42.5,50:-40.0,60:-37.4,70:-34.6,80:-31.6,90:-28.3,100:-24.9,110:-21.3,120:-17.5,130:-13.5,140:-9.4
ATGSeedDiag: seed=1@4,86/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.5) imip=0/20 pass=10110 acc=-1 ipm=62.0,91.6 inv=45.9,56.8 | 10(18.4) imip=0/11 pass=10111 acc=-1 ipm=121.6,109.4 inv=150.8,85.0
frame=916 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=55/12 raw=152/44 sel=55/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/17.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(111,99) md=41/1/84 cxcy=84.0,119.6 guide=-31.60 atg=60.0/60.0/60.0 pure=-11.48/-10.92 yaw=2528 cmd=2641 actual=2415 signed=0 rps=0/6372:5167/7610 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=55/12 centerNum=55/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=55/39 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-23.68@102,101 dx=18.4 idx=9/26 dist=40/95 right=1:-29.80@118,84 dx=33.5 idx=0/11 dist=24/24 sel=1:-33.22@113,99 dx=28.9 idx=0/20 dist=40/76 edge=1:-29.72@113.0,92.0 dx=29.0 width=42.2 l=102,74 r=124,110
CxScan: raw_ref=80.0 edge=113.0,92.0 best_raw_x=140 best_err=-6.73 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.9,20:-45.8,30:-43.6,40:-41.2,50:-38.6,60:-35.9,70:-32.9,80:-29.7,90:-26.3,100:-22.8,110:-19.0,120:-15.0,130:-10.9,140:-6.7
ATGSeedDiag: seed=1@5,86/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(11.7) imip=0/11 pass=10110 acc=-1 ipm=48.0,106.4 inv=11.5,79.8 | 2(17.8) imip=0/11 pass=10111 acc=-1 ipm=103.9,114.1 inv=122.3,97.7
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=55/11 raw=153/43 sel=55/39 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.1/18.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(112,99) md=41/1/85 cxcy=84.0,119.6 guide=-32.69 atg=60.0/60.0/60.0 pure=-11.44/-10.82 yaw=2615 cmd=2794 actual=2436 signed=0 rps=0/6505:5620/7879 duty=0/16 pwm=PWM2:0/PWM1:16 motor=2:0/1:16
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=55/11 centerNum=55/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=55/39 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-25.30@104,101 dx=19.9 idx=10/27 dist=40/94 right=1:-27.78@115,85 dx=30.5 idx=0/10 dist=20/20 sel=1:-34.51@114,98 dx=30.5 idx=0/20 dist=40/76 edge=1:-30.98@114.5,92.0 dx=30.5 width=39.0 l=107,74 r=122,110
CxScan: raw_ref=80.0 edge=114.5,92.0 best_raw_x=140 best_err=-8.38 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.6,20:-46.6,30:-44.5,40:-42.1,50:-39.6,60:-37.0,70:-34.1,80:-31.0,90:-27.7,100:-24.2,110:-20.5,120:-16.6,130:-12.5,140:-8.4
ATGSeedDiag: seed=1@4,86/1@116,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(11.1) imip=0/18 pass=10110 acc=-1 ipm=58.6,94.6 inv=39.6,60.5 | 9(18.5) imip=0/10 pass=10111 acc=-1 ipm=119.7,109.9 inv=148.0,86.1
frame=918 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/11 raw=170/43 sel=11/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/16.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,86) md=41/1/48 cxcy=84.0,119.6 guide=-21.95 atg=60.0/60.0/60.0 pure=-7.54/-7.54 yaw=1756 cmd=1556 actual=2447 signed=0 rps=1307/5571:5238/7113 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/11 centerNum=1/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/23 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-20.73@105,86 dx=21.5 idx=0/6 dist=41/49 sel=1:-23.69@109,85 dx=25.2 idx=0/20 dist=40/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=122,110
ATGSeedDiag: seed=1@27,86/1@116,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(16.1) imip=0/10 pass=10111 acc=-1 ipm=104.3,114.2 inv=123.3,97.9
frame=919 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/11 raw=170/43 sel=11/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/15.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,86) md=41/1/48 cxcy=84.0,119.6 guide=-22.24 atg=60.0/60.0/60.0 pure=-7.58/-7.58 yaw=1780 cmd=1580 actual=2464 signed=0 rps=1253/5583:5396/7341 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/11 centerNum=1/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/23 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-20.77@105,86 dx=21.5 idx=0/6 dist=41/49 sel=1:-23.82@109,86 dx=25.3 idx=0/20 dist=40/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=122,110
ATGSeedDiag: seed=1@24,89/1@116,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 6(15.7) imip=0/10 pass=10111 acc=-1 ipm=113.0,111.2 inv=136.9,89.4
frame=920 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/11 raw=170/42 sel=11/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/17.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(107,86) md=40/1/47 cxcy=84.0,119.6 guide=-22.49 atg=60.0/60.0/60.0 pure=-7.65/-7.65 yaw=1799 cmd=1599 actual=2472 signed=0 rps=1209/5592:5085/7197 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/11 centerNum=1/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/23 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-19.77@104,87 dx=20.2 idx=0/5 dist=40/50 sel=1:-24.18@110,86 dx=25.7 idx=0/20 dist=40/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=123,110
ATGSeedDiag: seed=1@19,93/1@117,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 9(17.3) imip=0/10 pass=10111 acc=-1 ipm=120.4,110.3 inv=150.1,87.1
frame=921 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/11 raw=170/41 sel=11/23 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/16.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,86) md=41/1/48 cxcy=84.0,119.6 guide=-22.79 atg=60.0/60.0/60.0 pure=-7.69/-7.69 yaw=1823 cmd=1623 actual=2474 signed=0 rps=1155/5604:5198/7810 duty=0/12 pwm=PWM2:0/PWM1:12 motor=2:0/1:12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/11 centerNum=1/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/23 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-20.02@104,87 dx=20.4 idx=0/5 dist=40/50 sel=1:-24.39@110,86 dx=25.9 idx=0/20 dist=40/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=123,110
ATGSeedDiag: seed=1@16,96/1@117,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 3(16.1) imip=0/10 pass=10111 acc=-1 ipm=107.0,113.3 inv=127.9,95.4
frame=922 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/10 raw=170/40 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/15.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,86) md=41/1/45 cxcy=84.0,119.6 guide=-21.87 atg=60.0/60.0/60.0 pure=-7.48/-7.48 yaw=1749 cmd=1549 actual=2454 signed=0 rps=1322/5568:4823/7404 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/10 centerNum=1/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-20.10@104,87 dx=20.4 idx=0/5 dist=40/48 sel=1:-24.60@110,86 dx=26.0 idx=0/20 dist=40/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=121,111
ATGSeedDiag: seed=1@15,99/1@118,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 4(15.1) imip=0/9 pass=10111 acc=-1 ipm=109.5,112.6 inv=132.2,93.3
frame=923 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/10 raw=170/40 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/13.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,86) md=41/1/45 cxcy=84.0,119.6 guide=-22.01 atg=60.0/60.0/60.0 pure=-7.50/-7.50 yaw=1761 cmd=1561 actual=2418 signed=0 rps=1295/5574:4884/7563 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/10 centerNum=1/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-20.25@105,87 dx=20.6 idx=0/5 dist=40/48 sel=1:-24.76@110,86 dx=26.2 idx=0/20 dist=40/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=121,111
ATGSeedDiag: seed=1@9,104/1@118,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 4(13.7) imip=0/9 pass=10111 acc=-1 ipm=109.7,112.7 inv=132.6,93.6
frame=924 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/10 raw=170/39 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/17.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,86) md=40/1/45 cxcy=84.0,119.6 guide=-22.45 atg=60.0/60.0/60.0 pure=-7.58/-7.58 yaw=1796 cmd=1596 actual=2378 signed=0 rps=1216/5591:5020/7657 duty=0/12 pwm=PWM2:0/PWM1:12 motor=2:0/1:12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/10 centerNum=1/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-21.04@105,87 dx=21.4 idx=0/5 dist=40/48 sel=1:-25.07@111,86 dx=26.5 idx=0/20 dist=40/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=121,111
ATGSeedDiag: seed=1@7,107/1@119,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 8(17.1) imip=0/9 pass=10111 acc=-1 ipm=119.2,111.1 inv=149.2,89.0
frame=925 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/10 raw=5/39 sel=10/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/16.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(108,87) md=40/1/45 cxcy=84.0,119.6 guide=-22.72 atg=60.0/60.0/60.0 pure=-7.61/-7.61 yaw=1818 cmd=1618 actual=2341 signed=0 rps=1168/5601:4915/7039 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/10 centerNum=1/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=10/22 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-20.94@105,87 dx=21.3 idx=0/5 dist=40/48 sel=1:-25.19@111,86 dx=26.6 idx=0/20 dist=40/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=121,111
ATGSeedDiag: seed=1@7,108/1@119,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 8(16.0) imip=0/9 pass=10111 acc=-1 ipm=119.1,111.1 inv=149.1,89.2
frame=926 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=57/10 raw=153/37 sel=57/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.9/13.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(114,100) md=41/1/86 cxcy=84.0,119.6 guide=-35.27 atg=60.0/60.0/60.0 pure=-11.40/-9.83 yaw=2822 cmd=3022 actual=2300 signed=0 rps=0/6633:5238/6937 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=57/10 centerNum=57/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/42 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-26.59@105,102 dx=20.6 idx=10/27 dist=41/99 right=1:-28.90@115,86 dx=31.4 idx=0/9 dist=18/18 sel=1:-36.86@116,100 dx=32.2 idx=0/20 dist=40/82 edge=1:-32.47@116.0,92.5 dx=32.0 width=38.9 l=110,74 r=122,111
CxScan: raw_ref=80.0 edge=116.0,92.5 best_raw_x=140 best_err=-10.13 best_cxcy=107.0,119.7 scan=0:-51.4,10:-49.6,20:-47.7,30:-45.6,40:-43.3,50:-40.9,60:-38.3,70:-35.5,80:-32.5,90:-29.2,100:-25.8,110:-22.1,120:-18.3,130:-14.3,140:-10.1
ATGSeedDiag: seed=1@4,87/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.9) imip=0/20 pass=10110 acc=-1 ipm=62.7,92.2 inv=46.6,57.5 | 4(13.6) imip=0/9 pass=10111 acc=-1 ipm=110.6,112.9 inv=135.0,94.2
frame=927 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=57/9 raw=153/36 sel=57/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.4/12.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(114,100) md=40/1/85 cxcy=84.0,119.6 guide=-36.44 atg=60.0/60.0/60.0 pure=-11.39/-9.82 yaw=2915 cmd=3115 actual=2254 signed=0 rps=0/6678:5244/6734 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=57/9 centerNum=57/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/42 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-28.66@107,101 dx=22.7 idx=10/28 dist=41/97 right=1:-27.28@113,86 dx=29.1 idx=0/8 dist=16/16 sel=1:-36.97@116,100 dx=32.4 idx=0/20 dist=40/82 edge=1:-31.07@114.0,93.0 dx=30.0 width=37.9 l=108,75 r=120,111
CxScan: raw_ref=80.0 edge=114.0,93.0 best_raw_x=140 best_err=-7.99 best_cxcy=107.0,119.7 scan=0:-50.8,10:-48.9,20:-46.9,30:-44.7,40:-42.4,50:-39.9,60:-37.1,70:-34.2,80:-31.1,90:-27.7,100:-24.1,110:-20.3,120:-16.4,130:-12.2,140:-8.0
ATGSeedDiag: seed=1@4,87/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(10.4) imip=0/19 pass=10110 acc=-1 ipm=61.1,93.8 inv=43.5,59.5 | 2(12.2) imip=0/8 pass=10111 acc=-1 ipm=106.7,114.5 inv=129.1,98.9
frame=928 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=57/9 raw=153/36 sel=57/42 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.2/13.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(114,101) md=40/1/85 cxcy=84.0,119.6 guide=-36.60 atg=60.0/60.0/60.0 pure=-11.39/-9.82 yaw=2928 cmd=3128 actual=2226 signed=0 rps=0/6684:5506/7212 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=57/9 centerNum=57/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=57/42 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-28.62@106,102 dx=22.3 idx=10/28 dist=41/97 right=1:-27.63@113,87 dx=29.4 idx=0/8 dist=16/16 sel=1:-37.16@116,100 dx=32.5 idx=0/20 dist=40/82 edge=1:-31.32@114.0,93.5 dx=30.0 width=38.9 l=108,75 r=120,112
CxScan: raw_ref=80.0 edge=114.0,93.5 best_raw_x=140 best_err=-8.07 best_cxcy=107.0,119.7 scan=0:-51.1,10:-49.2,20:-47.2,30:-45.0,40:-42.7,50:-40.2,60:-37.4,70:-34.5,80:-31.3,90:-27.9,100:-24.3,110:-20.5,120:-16.5,130:-12.4,140:-8.1
ATGSeedDiag: seed=1@4,87/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.2) imip=0/20 pass=10110 acc=-1 ipm=63.0,92.5 inv=46.8,57.9 | 7(13.7) imip=0/8 pass=10111 acc=-1 ipm=117.9,111.9 inv=148.3,91.3

- stopped_at: 2026-06-22T15:17:35+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive143
```
