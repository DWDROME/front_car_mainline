# drive169

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 12
- local_log: logs/live-circle/20260621-drive169-front_car_circle_drive169.log
- remote_log: /tmp/front_car_circle_drive169.log
- started_at: 2026-06-22T16:27:43+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive169 12
```

8923 /tmp/front_car_circle_drive169.log
ATGSeedDiag: seed=1@4,100/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(13.1) imip=0/20 pass=10110 acc=-1 ipm=65.9,96.4 inv=49.3,62.8 | 3(6.5) imip=0/4 pass=10111 acc=-1 ipm=116.1,114.3 inv=149.6,98.1
frame=1677 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=51/5 raw=153/18 sel=51/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.4/7.2/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(122,103) md=41/1/66 cxcy=84.0,119.6 guide=-44.06 atg=60.0/60.0/60.0 pure=-12.18/-12.17 yaw=3525 cmd=3925 actual=3018 signed=0 rps=0/8029:4302/8591 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=51/5 centerNum=51/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=51/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.34@115,104 dx=30.7 idx=10/31 dist=41/77 right=1:-26.77@111,89 dx=27.2 idx=0/4 dist=8/8 sel=1:-45.30@124,103 dx=40.2 idx=0/20 dist=40/60 edge=1:-32.51@113.5,96.5 dx=29.5 width=36.7 l=108,79 r=119,114
CxScan: raw_ref=80.0 edge=113.5,96.5 best_raw_x=140 best_err=-7.98 best_cxcy=107.0,119.7 scan=0:-52.6,10:-50.7,20:-48.7,30:-46.5,40:-44.2,50:-41.6,60:-38.8,70:-35.8,80:-32.5,90:-29.0,100:-25.2,110:-21.2,120:-17.0,130:-12.5,140:-8.0
ATGSeedDiag: seed=1@4,100/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.4) imip=0/20 pass=10110 acc=-1 ipm=66.1,96.6 inv=49.6,63.0 | 3(7.2) imip=0/4 pass=10111 acc=-1 ipm=116.6,114.3 inv=150.7,97.9
frame=1678 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/5 raw=153/18 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.0/6.1/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(122,104) md=41/1/66 cxcy=84.0,119.6 guide=-44.70 atg=60.0/60.0/60.0 pure=-12.24/-12.20 yaw=3576 cmd=3976 actual=2991 signed=0 rps=0/8065:4562/9209 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/5 centerNum=50/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-36.94@112,105 dx=28.5 idx=10/30 dist=40/77 right=1:-26.73@111,89 dx=27.1 idx=0/4 dist=8/8 sel=1:-46.65@125,104 dx=40.6 idx=0/20 dist=40/60 edge=1:-32.94@114.0,96.5 dx=30.0 width=36.4 l=109,79 r=119,114
CxScan: raw_ref=80.0 edge=114.0,96.5 best_raw_x=140 best_err=-8.58 best_cxcy=107.0,119.7 scan=0:-52.8,10:-51.0,20:-49.0,30:-46.8,40:-44.5,50:-41.9,60:-39.2,70:-36.2,80:-32.9,90:-29.5,100:-25.7,110:-21.7,120:-17.5,130:-13.1,140:-8.6
ATGSeedDiag: seed=1@4,100/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(13.0) imip=37/49 pass=10100 acc=-1 ipm=147.7,80.3 inv=146.9,45.4 | 3(6.1) imip=0/4 pass=10111 acc=-1 ipm=116.6,114.4 inv=150.8,98.4
frame=1679 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/5 raw=153/17 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.9/5.3/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(122,104) md=41/1/66 cxcy=84.0,119.6 guide=-44.70 atg=60.0/60.0/60.0 pure=-12.27/-12.20 yaw=3576 cmd=3976 actual=2952 signed=0 rps=0/8065:4628/9040 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/5 centerNum=50/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.21@114,104 dx=30.2 idx=10/31 dist=41/77 right=1:-27.33@112,89 dx=27.8 idx=0/4 dist=8/8 sel=1:-46.64@125,104 dx=40.6 idx=0/20 dist=40/60 edge=1:-32.94@114.0,96.5 dx=30.0 width=36.4 l=109,79 r=119,114
CxScan: raw_ref=80.0 edge=114.0,96.5 best_raw_x=140 best_err=-8.58 best_cxcy=107.0,119.7 scan=0:-52.8,10:-51.0,20:-49.0,30:-46.8,40:-44.5,50:-41.9,60:-39.2,70:-36.2,80:-32.9,90:-29.5,100:-25.7,110:-21.7,120:-17.5,130:-13.1,140:-8.6
ATGSeedDiag: seed=1@4,100/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.9) imip=0/20 pass=10110 acc=-1 ipm=66.3,96.7 inv=49.8,63.2 | 2(5.3) imip=0/4 pass=10111 acc=-1 ipm=114.9,115.0 inv=148.4,100.2
frame=1680 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/5 raw=154/17 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.9/5.7/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(122,104) md=41/1/66 cxcy=84.0,119.6 guide=-44.70 atg=60.0/60.0/60.0 pure=-12.21/-12.14 yaw=3576 cmd=3976 actual=2935 signed=0 rps=0/8065:5091/9784 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/5 centerNum=50/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-36.62@112,105 dx=28.2 idx=10/30 dist=40/78 right=1:-27.16@112,89 dx=27.6 idx=0/4 dist=8/8 sel=1:-46.59@125,104 dx=40.6 idx=0/20 dist=40/60 edge=1:-32.51@113.5,96.5 dx=29.5 width=36.7 l=108,79 r=119,114
CxScan: raw_ref=80.0 edge=113.5,96.5 best_raw_x=140 best_err=-7.98 best_cxcy=107.0,119.7 scan=0:-52.6,10:-50.7,20:-48.7,30:-46.5,40:-44.2,50:-41.6,60:-38.8,70:-35.8,80:-32.5,90:-29.0,100:-25.2,110:-21.2,120:-17.0,130:-12.5,140:-8.0
ATGSeedDiag: seed=1@4,101/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(15.9) imip=0/11 pass=10110 acc=-1 ipm=52.0,112.0 inv=11.1,93.0 | 3(5.7) imip=0/4 pass=10111 acc=-1 ipm=117.0,114.4 inv=151.8,98.5
frame=1681 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=51/5 raw=153/16 sel=51/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.4/4.9/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(122,104) md=41/1/66 cxcy=84.0,119.6 guide=-44.70 atg=60.0/60.0/60.0 pure=-12.22/-12.14 yaw=3576 cmd=3976 actual=2938 signed=0 rps=0/8065:5136/9571 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=51/5 centerNum=51/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=51/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.20@114,104 dx=30.2 idx=10/31 dist=41/78 right=1:-27.21@112,89 dx=27.7 idx=0/4 dist=8/8 sel=1:-46.46@125,104 dx=40.7 idx=0/20 dist=40/60 edge=1:-33.38@114.5,96.5 dx=30.5 width=36.7 l=109,79 r=120,114
CxScan: raw_ref=80.0 edge=114.5,96.5 best_raw_x=140 best_err=-9.18 best_cxcy=107.0,119.7 scan=0:-53.1,10:-51.2,20:-49.3,30:-47.1,40:-44.8,50:-42.3,60:-39.5,70:-36.6,80:-33.4,90:-29.9,100:-26.2,110:-22.3,120:-18.1,130:-13.7,140:-9.2
ATGSeedDiag: seed=1@4,102/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(12.4) imip=35/50 pass=10100 acc=-1 ipm=143.0,78.7 inv=140.0,44.2 | 2(4.9) imip=0/4 pass=10111 acc=-1 ipm=115.2,115.0 inv=149.1,100.4
frame=1682 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/15 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.2/4.8/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(121,104) md=40/1/67 cxcy=84.0,119.6 guide=-44.48 atg=60.0/60.0/60.0 pure=-12.11/-12.06 yaw=3558 cmd=3958 actual=2942 signed=0 rps=0/8053:5376/9318 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.85@115,105 dx=30.6 idx=10/31 dist=41/77 right=1:-25.97@110,90 dx=25.9 idx=0/3 dist=6/6 sel=1:-47.01@125,104 dx=41.2 idx=0/20 dist=40/60 edge=1:-32.51@113.5,96.5 dx=29.5 width=36.1 l=109,79 r=118,114
CxScan: raw_ref=80.0 edge=113.5,96.5 best_raw_x=140 best_err=-7.98 best_cxcy=107.0,119.7 scan=0:-52.6,10:-50.7,20:-48.7,30:-46.5,40:-44.2,50:-41.6,60:-38.8,70:-35.8,80:-32.5,90:-29.0,100:-25.2,110:-21.2,120:-17.0,130:-12.5,140:-8.0
ATGSeedDiag: seed=1@4,103/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(11.2) imip=37/49 pass=10100 acc=-1 ipm=147.9,79.9 inv=146.7,45.0 | 1(4.8) imip=0/3 pass=10111 acc=-1 ipm=113.5,115.7 inv=146.8,102.5
frame=1683 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/15 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.9/3.2/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(123,104) md=42/1/67 cxcy=84.0,119.6 guide=-44.38 atg=60.0/60.0/60.0 pure=-12.15/-12.08 yaw=3551 cmd=3951 actual=2922 signed=0 rps=0/8047:5556/9282 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.45@115,105 dx=30.9 idx=9/31 dist=41/76 right=1:-26.04@110,90 dx=25.9 idx=0/3 dist=6/6 sel=1:-46.92@125,104 dx=41.0 idx=0/20 dist=40/60 edge=1:-32.79@113.5,97.0 dx=29.5 width=37.1 l=109,79 r=118,115
CxScan: raw_ref=80.0 edge=113.5,97.0 best_raw_x=140 best_err=-8.06 best_cxcy=107.0,119.7 scan=0:-52.9,10:-51.1,20:-49.0,30:-46.9,40:-44.5,50:-41.9,60:-39.1,70:-36.1,80:-32.8,90:-29.3,100:-25.5,110:-21.4,120:-17.1,130:-12.7,140:-8.1
ATGSeedDiag: seed=1@4,104/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(10.9) imip=0/20 pass=10110 acc=-1 ipm=66.8,97.4 inv=50.3,64.2 | 2(3.2) imip=0/3 pass=10111 acc=-1 ipm=115.6,115.2 inv=150.4,100.7
frame=1684 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=154/14 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/2.4/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(123,104) md=42/1/67 cxcy=84.0,119.6 guide=-44.38 atg=60.0/60.0/60.0 pure=-12.11/-12.04 yaw=3551 cmd=3951 actual=2911 signed=0 rps=0/8047:5193/9049 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.71@113,105 dx=29.0 idx=9/30 dist=40/78 right=1:-26.20@110,90 dx=26.1 idx=0/3 dist=6/6 sel=1:-46.92@125,104 dx=41.0 idx=0/20 dist=40/60 edge=1:-32.51@113.5,96.5 dx=29.5 width=36.1 l=109,79 r=118,114
CxScan: raw_ref=80.0 edge=113.5,96.5 best_raw_x=140 best_err=-7.98 best_cxcy=107.0,119.7 scan=0:-52.6,10:-50.7,20:-48.7,30:-46.5,40:-44.2,50:-41.6,60:-38.8,70:-35.8,80:-32.5,90:-29.0,100:-25.2,110:-21.2,120:-17.0,130:-12.5,140:-8.0
ATGSeedDiag: seed=1@4,104/1@143,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(11.7) imip=0/11 pass=10110 acc=-1 ipm=52.9,113.0 inv=11.4,95.8 | 2(2.4) imip=0/3 pass=10111 acc=-1 ipm=116.1,115.1 inv=151.3,100.5
frame=1685 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=154/14 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.6/1.3/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(123,104) md=42/1/67 cxcy=84.0,119.6 guide=-44.38 atg=60.0/60.0/60.0 pure=-12.11/-12.04 yaw=3551 cmd=3951 actual=2923 signed=0 rps=0/8047:5144/9575 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.18@115,105 dx=30.7 idx=9/31 dist=41/76 right=1:-26.16@110,90 dx=26.1 idx=0/3 dist=6/6 sel=1:-46.88@125,104 dx=41.0 idx=0/20 dist=40/60 edge=1:-32.51@113.5,96.5 dx=29.5 width=36.1 l=109,79 r=118,114
CxScan: raw_ref=80.0 edge=113.5,96.5 best_raw_x=140 best_err=-7.98 best_cxcy=107.0,119.7 scan=0:-52.6,10:-50.7,20:-48.7,30:-46.5,40:-44.2,50:-41.6,60:-38.8,70:-35.8,80:-32.5,90:-29.0,100:-25.2,110:-21.2,120:-17.0,130:-12.5,140:-8.0
ATGSeedDiag: seed=1@4,104/1@143,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(13.6) imip=0/11 pass=10110 acc=-1 ipm=52.8,113.0 inv=11.3,95.7 | 2(1.3) imip=0/3 pass=10111 acc=-1 ipm=116.0,115.2 inv=151.4,100.7
frame=1686 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=154/13 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.9/3.2/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(123,104) md=42/1/67 cxcy=84.0,119.6 guide=-44.48 atg=60.0/60.0/60.0 pure=-12.21/-12.14 yaw=3558 cmd=3958 actual=2952 signed=0 rps=0/8053:5059/9991 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.46@115,105 dx=30.9 idx=9/31 dist=40/75 right=1:-26.50@110,90 dx=26.5 idx=0/3 dist=6/6 sel=1:-46.93@125,104 dx=41.0 idx=0/20 dist=40/60 edge=1:-32.94@114.0,96.5 dx=30.0 width=36.4 l=109,79 r=119,114
CxScan: raw_ref=80.0 edge=114.0,96.5 best_raw_x=140 best_err=-8.58 best_cxcy=107.0,119.7 scan=0:-52.8,10:-51.0,20:-49.0,30:-46.8,40:-44.5,50:-41.9,60:-39.2,70:-36.2,80:-32.9,90:-29.5,100:-25.7,110:-21.7,120:-17.5,130:-13.1,140:-8.6
ATGSeedDiag: seed=1@4,104/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(11.9) imip=0/20 pass=10110 acc=-1 ipm=66.7,97.5 inv=50.2,64.3 | 2(3.2) imip=0/3 pass=10111 acc=-1 ipm=116.5,115.1 inv=152.2,100.6
frame=1687 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=154/13 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.2/0.8/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(121,105) md=40/1/65 cxcy=84.0,119.6 guide=-45.14 atg=60.0/60.0/60.0 pure=-12.29/-12.29 yaw=3611 cmd=4011 actual=2953 signed=0 rps=0/8090:4781/9512 duty=0/20 pwm=PWM2:0/PWM1:20 motor=2:0/1:20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.83@115,105 dx=31.1 idx=9/31 dist=40/75 right=1:-26.59@111,90 dx=26.6 idx=0/3 dist=6/6 sel=1:-47.37@126,104 dx=41.7 idx=0/20 dist=40/58 edge=1:-32.92@113.0,98.0 dx=29.0 width=36.1 l=107,81 r=119,115
CxScan: raw_ref=80.0 edge=113.0,98.0 best_raw_x=140 best_err=-7.61 best_cxcy=107.0,119.7 scan=0:-53.3,10:-51.4,20:-49.4,30:-47.2,40:-44.8,50:-42.2,60:-39.3,70:-36.3,80:-32.9,90:-29.3,100:-25.4,110:-21.3,120:-16.9,130:-12.3,140:-7.6
ATGSeedDiag: seed=1@4,105/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=39(11.2) imip=29/49 pass=10110 acc=-1 ipm=129.8,78.3 inv=125.3,44.0 | 2(0.8) imip=0/3 pass=10111 acc=-1 ipm=116.5,115.2 inv=152.4,100.8
frame=1688 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/3 raw=153/12 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.0/0.1/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(124,104) md=42/1/64 cxcy=84.0,119.6 guide=-45.42 atg=60.0/60.0/60.0 pure=-12.29/-12.29 yaw=3633 cmd=4033 actual=2926 signed=0 rps=0/8105:4878/9318 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/3 centerNum=50/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-41.43@117,105 dx=33.0 idx=9/32 dist=40/74 right=1:-25.04@108,90 dx=24.4 idx=0/2 dist=4/4 sel=1:-47.58@126,104 dx=42.0 idx=0/20 dist=40/58 edge=1:-32.01@112.0,98.0 dx=28.0 width=35.4 l=107,81 r=117,115
CxScan: raw_ref=80.0 edge=112.0,98.0 best_raw_x=140 best_err=-6.36 best_cxcy=107.0,119.7 scan=0:-52.8,10:-50.9,20:-48.8,30:-46.6,40:-44.1,50:-41.5,60:-38.6,70:-35.4,80:-32.0,90:-28.3,100:-24.4,110:-20.2,120:-15.7,130:-11.1,140:-6.4
ATGSeedDiag: seed=1@4,106/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(12.0) imip=30/49 pass=10110 acc=-1 ipm=132.4,78.4 inv=128.1,44.0 | 1(0.1) imip=0/2 pass=10111 acc=-1 ipm=114.7,115.9 inv=150.0,103.2
frame=1689 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/3 raw=154/11 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.9/0.1/0.0/0.0 dist=0 begin=0/3258 m0=(84,119) ml=(122,105) md=40/1/65 cxcy=84.0,119.6 guide=-45.60 atg=60.0/60.0/60.0 pure=-12.29/-12.29 yaw=3648 cmd=4048 actual=2900 signed=0 rps=0/8116:4623/8782 duty=0/21 pwm=PWM2:0/PWM1:21 motor=2:0/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/3 centerNum=50/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-40.32@116,105 dx=31.6 idx=9/31 dist=40/75 right=1:-25.28@109,90 dx=24.7 idx=0/2 dist=4/4 sel=1:-47.74@126,104 dx=42.2 idx=0/20 dist=40/58 edge=1:-32.01@112.0,98.0 dx=28.0 width=35.4 l=107,81 r=117,115
CxScan: raw_ref=80.0 edge=112.0,98.0 best_raw_x=140 best_err=-6.36 best_cxcy=107.0,119.7 scan=0:-52.8,10:-50.9,20:-48.8,30:-46.6,40:-44.1,50:-41.5,60:-38.6,70:-35.4,80:-32.0,90:-28.3,100:-24.4,110:-20.2,120:-15.7,130:-11.1,140:-6.4
ATGSeedDiag: seed=1@4,106/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(11.9) imip=32/49 pass=10110 acc=-1 ipm=137.1,78.6 inv=133.4,44.1 | 1(0.1) imip=0/2 pass=10111 acc=-1 ipm=115.1,115.9 inv=151.0,103.1

- stopped_at: 2026-06-22T16:28:02+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive169
```
