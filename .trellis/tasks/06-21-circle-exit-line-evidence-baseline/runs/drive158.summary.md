# drive158

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive158-front_car_circle_drive158.log
- remote_log: /tmp/front_car_circle_drive158.log
- started_at: 2026-06-22T15:30:30+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive158 6
```

4569 /tmp/front_car_circle_drive158.log
ATGSeedDiag: seed=1@4,99/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(13.0) imip=33/50 pass=10110 acc=-1 ipm=138.5,77.3 inv=133.9,43.2 | 2(3.6) imip=0/3 pass=10111 acc=-1 ipm=115.2,115.2 inv=149.5,100.7
frame=911 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/16 sel=50/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.2/3.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(122,104) md=41/1/66 cxcy=84.0,119.6 guide=-44.91 atg=60.0/60.0/60.0 pure=-12.17/-12.14 yaw=3593 cmd=3793 actual=2794 signed=0 rps=0/7004:5124/8048 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/31 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.58@113,105 dx=28.9 idx=10/30 dist=40/77 right=1:-26.05@110,90 dx=26.0 idx=0/3 dist=6/6 sel=1:-46.71@125,104 dx=40.8 idx=0/20 dist=40/60 edge=1:-32.34@113.0,97.0 dx=29.0 width=36.9 l=109,79 r=117,115
CxScan: raw_ref=80.0 edge=113.0,97.0 best_raw_x=140 best_err=-7.45 best_cxcy=107.0,119.7 scan=0:-52.7,10:-50.8,20:-48.8,30:-46.6,40:-44.2,50:-41.6,60:-38.7,70:-35.7,80:-32.3,90:-28.8,100:-24.9,110:-20.9,120:-16.6,130:-12.1,140:-7.4
ATGSeedDiag: seed=1@4,100/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(13.2) imip=37/49 pass=10100 acc=-1 ipm=148.0,80.1 inv=147.0,45.2 | 2(3.0) imip=0/3 pass=10111 acc=-1 ipm=115.2,115.2 inv=149.7,101.0
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/16 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.2/2.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,104) md=42/1/64 cxcy=84.0,119.6 guide=-44.57 atg=60.0/60.0/60.0 pure=-12.37/-12.37 yaw=3566 cmd=3766 actual=2783 signed=0 rps=0/6991:4895/7781 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.02@113,105 dx=29.2 idx=10/30 dist=40/77 right=1:-26.36@110,90 dx=26.3 idx=0/3 dist=6/6 sel=1:-46.91@125,104 dx=41.0 idx=0/20 dist=40/58 edge=1:-33.23@114.0,97.0 dx=30.0 width=36.5 l=111,79 r=117,115
CxScan: raw_ref=80.0 edge=114.0,97.0 best_raw_x=140 best_err=-8.67 best_cxcy=107.0,119.7 scan=0:-53.1,10:-51.3,20:-49.3,30:-47.1,40:-44.8,50:-42.3,60:-39.5,70:-36.5,80:-33.2,90:-29.7,100:-26.0,110:-22.0,120:-17.7,130:-13.3,140:-8.7
ATGSeedDiag: seed=1@4,100/1@141,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(12.2) imip=32/49 pass=10110 acc=-1 ipm=136.7,78.7 inv=133.2,44.2 | 2(2.3) imip=0/3 pass=10111 acc=-1 ipm=115.2,115.3 inv=150.0,101.3
frame=913 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/15 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.4/3.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,104) md=42/1/64 cxcy=84.0,119.6 guide=-44.57 atg=60.0/60.0/60.0 pure=-12.37/-12.37 yaw=3566 cmd=3766 actual=2749 signed=0 rps=0/6991:4965/7843 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.56@115,105 dx=30.9 idx=10/31 dist=40/75 right=1:-26.55@111,90 dx=26.5 idx=0/3 dist=6/6 sel=1:-46.88@125,104 dx=41.0 idx=0/20 dist=40/58 edge=1:-33.66@114.5,97.0 dx=30.5 width=36.7 l=111,79 r=118,115
CxScan: raw_ref=80.0 edge=114.5,97.0 best_raw_x=140 best_err=-9.28 best_cxcy=107.0,119.7 scan=0:-53.4,10:-51.5,20:-49.6,30:-47.4,40:-45.1,50:-42.6,60:-39.9,70:-36.9,80:-33.7,90:-30.2,100:-26.5,110:-22.5,120:-18.3,130:-13.9,140:-9.3
ATGSeedDiag: seed=1@4,100/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(12.4) imip=32/49 pass=10110 acc=-1 ipm=136.7,78.7 inv=133.1,44.2 | 2(3.8) imip=0/3 pass=10111 acc=-1 ipm=115.7,115.3 inv=150.7,101.0
frame=914 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/15 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.6/3.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,104) md=42/1/64 cxcy=84.0,119.6 guide=-45.23 atg=60.0/60.0/60.0 pure=-12.37/-12.37 yaw=3618 cmd=3818 actual=2731 signed=0 rps=0/7017:4955/7919 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.52@115,105 dx=30.9 idx=10/31 dist=41/77 right=1:-26.85@111,90 dx=26.9 idx=0/3 dist=6/6 sel=1:-46.81@125,104 dx=40.9 idx=0/20 dist=40/58 edge=1:-33.66@114.5,97.0 dx=30.5 width=36.7 l=111,79 r=118,115
CxScan: raw_ref=80.0 edge=114.5,97.0 best_raw_x=140 best_err=-9.28 best_cxcy=107.0,119.7 scan=0:-53.4,10:-51.5,20:-49.6,30:-47.4,40:-45.1,50:-42.6,60:-39.9,70:-36.9,80:-33.7,90:-30.2,100:-26.5,110:-22.5,120:-18.3,130:-13.9,140:-9.3
ATGSeedDiag: seed=1@4,100/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(12.6) imip=32/49 pass=10110 acc=-1 ipm=136.7,78.5 inv=132.9,44.1 | 2(3.0) imip=0/3 pass=10111 acc=-1 ipm=115.7,115.3 inv=150.9,101.3
frame=915 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/4 raw=153/14 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.0/5.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,104) md=42/1/64 cxcy=84.0,119.6 guide=-45.23 atg=60.0/60.0/60.0 pure=-12.31/-12.31 yaw=3618 cmd=3818 actual=2718 signed=0 rps=0/7017:4702/7825 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/4 centerNum=50/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-37.85@113,105 dx=29.1 idx=10/30 dist=40/77 right=1:-27.17@111,90 dx=27.3 idx=0/3 dist=6/6 sel=1:-46.87@125,104 dx=41.0 idx=0/20 dist=40/58 edge=1:-33.66@114.5,97.0 dx=30.5 width=36.7 l=111,79 r=118,115
CxScan: raw_ref=80.0 edge=114.5,97.0 best_raw_x=140 best_err=-9.28 best_cxcy=107.0,119.7 scan=0:-53.4,10:-51.5,20:-49.6,30:-47.4,40:-45.1,50:-42.6,60:-39.9,70:-36.9,80:-33.7,90:-30.2,100:-26.5,110:-22.5,120:-18.3,130:-13.9,140:-9.3
ATGSeedDiag: seed=1@4,100/1@143,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(12.0) imip=32/49 pass=10110 acc=-1 ipm=136.7,78.4 inv=132.9,44.0 | 2(5.2) imip=0/3 pass=10111 acc=-1 ipm=116.1,115.3 inv=151.7,101.0
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/3 raw=153/13 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.4/0.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,105) md=40/1/65 cxcy=84.0,119.6 guide=-44.95 atg=60.0/60.0/60.0 pure=-12.37/-12.37 yaw=3596 cmd=3796 actual=2713 signed=0 rps=0/7006:4943/8086 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/3 centerNum=50/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.40@113,106 dx=29.5 idx=10/30 dist=40/77 right=1:-25.63@109,90 dx=25.2 idx=0/2 dist=4/4 sel=1:-47.16@125,104 dx=41.4 idx=0/20 dist=40/58 edge=1:-33.23@114.0,97.0 dx=30.0 width=36.5 l=111,79 r=117,115
CxScan: raw_ref=80.0 edge=114.0,97.0 best_raw_x=140 best_err=-8.67 best_cxcy=107.0,119.7 scan=0:-53.1,10:-51.3,20:-49.3,30:-47.1,40:-44.8,50:-42.3,60:-39.5,70:-36.5,80:-33.2,90:-29.7,100:-26.0,110:-22.0,120:-17.7,130:-13.3,140:-8.7
ATGSeedDiag: seed=1@4,101/1@144,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(14.4) imip=32/49 pass=10110 acc=-1 ipm=136.9,78.4 inv=133.1,44.0 | 1(0.3) imip=0/2 pass=10111 acc=-1 ipm=114.3,116.0 inv=149.3,103.5
frame=919 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/3 raw=153/12 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.0/0.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,105) md=40/1/65 cxcy=84.0,119.6 guide=-45.14 atg=60.0/60.0/60.0 pure=-12.43/-12.43 yaw=3611 cmd=3811 actual=2692 signed=0 rps=0/7013:5119/7991 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/3 centerNum=50/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.83@114,106 dx=29.8 idx=10/30 dist=40/76 right=1:-26.03@110,90 dx=25.6 idx=0/2 dist=4/4 sel=1:-47.35@126,104 dx=41.7 idx=0/20 dist=40/58 edge=1:-32.63@113.0,97.5 dx=29.0 width=35.9 l=109,80 r=117,115
CxScan: raw_ref=80.0 edge=113.0,97.5 best_raw_x=140 best_err=-7.53 best_cxcy=107.0,119.7 scan=0:-53.0,10:-51.1,20:-49.1,30:-46.9,40:-44.5,50:-41.9,60:-39.0,70:-36.0,80:-32.6,90:-29.0,100:-25.2,110:-21.1,120:-16.7,130:-12.2,140:-7.5
ATGSeedDiag: seed=1@4,102/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=41(13.0) imip=31/49 pass=10110 acc=-1 ipm=134.7,78.4 inv=130.6,44.0 | 1(0.3) imip=0/2 pass=10111 acc=-1 ipm=114.7,116.0 inv=150.3,103.5
frame=920 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/3 raw=153/12 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.9/0.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,105) md=40/1/65 cxcy=84.0,119.6 guide=-45.04 atg=60.0/60.0/60.0 pure=-12.43/-12.43 yaw=3603 cmd=3803 actual=2698 signed=0 rps=0/7010:5398/8222 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/3 centerNum=50/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-40.07@115,105 dx=31.4 idx=10/31 dist=41/76 right=1:-26.47@110,90 dx=26.1 idx=0/2 dist=4/4 sel=1:-47.30@126,104 dx=41.6 idx=0/20 dist=40/58 edge=1:-32.63@113.0,97.5 dx=29.0 width=35.9 l=109,80 r=117,115
CxScan: raw_ref=80.0 edge=113.0,97.5 best_raw_x=140 best_err=-7.53 best_cxcy=107.0,119.7 scan=0:-53.0,10:-51.1,20:-49.1,30:-46.9,40:-44.5,50:-41.9,60:-39.0,70:-36.0,80:-32.6,90:-29.0,100:-25.2,110:-21.1,120:-16.7,130:-12.2,140:-7.5
ATGSeedDiag: seed=1@4,102/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(12.9) imip=0/20 pass=10110 acc=-1 ipm=66.7,97.3 inv=50.2,64.1 | 1(0.1) imip=0/2 pass=10111 acc=-1 ipm=114.7,116.1 inv=150.5,103.7
frame=921 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/3 raw=153/11 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.1/0.1/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,105) md=40/1/65 cxcy=84.0,119.6 guide=-45.04 atg=60.0/60.0/60.0 pure=-12.47/-12.47 yaw=3603 cmd=3803 actual=2693 signed=0 rps=0/7010:5211/7743 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/3 centerNum=50/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-38.81@114,106 dx=29.7 idx=10/30 dist=40/77 right=1:-26.39@110,90 dx=26.0 idx=0/2 dist=4/4 sel=1:-47.30@126,104 dx=41.6 idx=0/20 dist=40/58 edge=1:-32.63@113.0,97.5 dx=29.0 width=35.9 l=109,80 r=117,115
CxScan: raw_ref=80.0 edge=113.0,97.5 best_raw_x=140 best_err=-7.53 best_cxcy=107.0,119.7 scan=0:-53.0,10:-51.1,20:-49.1,30:-46.9,40:-44.5,50:-41.9,60:-39.0,70:-36.0,80:-32.6,90:-29.0,100:-25.2,110:-21.1,120:-16.7,130:-12.2,140:-7.5
ATGSeedDiag: seed=1@4,102/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(13.1) imip=30/49 pass=10110 acc=-1 ipm=132.3,78.4 inv=128.1,44.0 | 1(0.1) imip=0/2 pass=10111 acc=-1 ipm=115.1,116.0 inv=151.3,103.5
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/3 raw=153/10 sel=49/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.0/0.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,106) md=40/1/63 cxcy=84.0,119.6 guide=-45.80 atg=60.0/60.0/60.0 pure=-12.53/-12.53 yaw=3664 cmd=3864 actual=2676 signed=0 rps=0/7039:5511/8290 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/3 centerNum=49/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/29 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-39.97@115,106 dx=31.0 idx=10/31 dist=40/72 right=1:-26.88@111,90 dx=26.6 idx=0/2 dist=4/4 sel=1:-47.59@126,105 dx=41.8 idx=0/20 dist=40/56 edge=1:-34.39@115.0,97.5 dx=31.0 width=35.5 l=112,80 r=118,115
CxScan: raw_ref=80.0 edge=115.0,97.5 best_raw_x=140 best_err=-9.99 best_cxcy=107.0,119.7 scan=0:-53.9,10:-52.1,20:-50.1,30:-48.0,40:-45.7,50:-43.2,60:-40.5,70:-37.6,80:-34.4,90:-30.9,100:-27.2,110:-23.3,120:-19.0,130:-14.6,140:-10.0
ATGSeedDiag: seed=1@4,102/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=38(13.0) imip=28/48 pass=10110 acc=-1 ipm=127.8,78.3 inv=123.1,44.0 | 1(0.6) imip=0/2 pass=10111 acc=-1 ipm=115.6,116.0 inv=152.3,103.5
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/3 raw=153/10 sel=49/29 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.7/0.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(124,105) md=42/1/62 cxcy=84.0,119.6 guide=-46.61 atg=60.0/60.0/60.0 pure=-12.52/-12.52 yaw=3729 cmd=3929 actual=2653 signed=0 rps=0/7070:5224/8106 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/3 centerNum=49/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/29 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-40.13@115,106 dx=31.2 idx=10/31 dist=40/72 right=1:-27.15@111,90 dx=26.9 idx=0/2 dist=4/4 sel=1:-47.75@126,105 dx=41.8 idx=0/20 dist=40/56 edge=1:-32.47@112.5,98.0 dx=28.5 width=35.7 l=107,81 r=118,115
CxScan: raw_ref=80.0 edge=112.5,98.0 best_raw_x=140 best_err=-6.99 best_cxcy=107.0,119.7 scan=0:-53.1,10:-51.2,20:-49.1,30:-46.9,40:-44.5,50:-41.8,60:-39.0,70:-35.8,80:-32.5,90:-28.8,100:-24.9,110:-20.7,120:-16.3,130:-11.7,140:-7.0
ATGSeedDiag: seed=1@4,103/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=39(12.7) imip=29/48 pass=10110 acc=-1 ipm=130.3,78.4 inv=125.9,44.1 | 1(0.6) imip=0/2 pass=10111 acc=-1 ipm=115.6,116.1 inv=152.4,103.7
frame=924 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/2 raw=153/9 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.5/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(124,105) md=41/1/63 cxcy=84.0,119.6 guide=-46.38 atg=60.0/60.0/60.0 pure=-12.42/-12.42 yaw=3711 cmd=3911 actual=2649 signed=0 rps=0/7061:5267/8493 duty=0/17 pwm=PWM2:0/PWM1:17 motor=2:0/1:17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/2 centerNum=50/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-41.45@117,105 dx=33.0 idx=10/32 dist=40/73 right=1:-25.78@109,91 dx=25.0 idx=0/1 dist=2/2 sel=1:-47.63@126,104 dx=42.1 idx=0/20 dist=40/58 edge=1:-33.81@114.0,98.0 dx=30.0 width=36.2 l=112,80 r=116,116
CxScan: raw_ref=80.0 edge=114.0,98.0 best_raw_x=140 best_err=-8.86 best_cxcy=107.0,119.7 scan=0:-53.7,10:-51.9,20:-49.9,30:-47.8,40:-45.4,50:-42.9,60:-40.1,70:-37.1,80:-33.8,90:-30.3,100:-26.5,110:-22.4,120:-18.1,130:-13.6,140:-8.9
ATGSeedDiag: seed=1@4,103/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(13.5) imip=30/49 pass=10110 acc=-1 ipm=132.5,78.4 inv=128.3,44.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=925 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/2 raw=153/8 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.0/0.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(124,104) md=41/1/64 cxcy=84.0,119.6 guide=-46.37 atg=60.0/60.0/60.0 pure=-12.37/-12.37 yaw=3710 cmd=3910 actual=2659 signed=0 rps=0/7061:4939/8234 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/2 centerNum=50/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=41 cxcy=84.0,119.6 left=1:-41.70@117,105 dx=33.3 idx=10/32 dist=41/74 right=1:-26.32@110,91 dx=25.7 idx=0/1 dist=2/2 sel=1:-47.82@126,104 dx=42.3 idx=0/20 dist=40/58 edge=1:-32.92@113.0,98.0 dx=29.0 width=36.5 l=110,80 r=116,116
CxScan: raw_ref=80.0 edge=113.0,98.0 best_raw_x=140 best_err=-7.61 best_cxcy=107.0,119.7 scan=0:-53.3,10:-51.4,20:-49.4,30:-47.2,40:-44.8,50:-42.2,60:-39.3,70:-36.3,80:-32.9,90:-29.3,100:-25.4,110:-21.3,120:-16.9,130:-12.3,140:-7.6
ATGSeedDiag: seed=1@4,104/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=40(14.0) imip=30/49 pass=10110 acc=-1 ipm=132.7,78.4 inv=128.4,44.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T15:30:44+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive158
```
