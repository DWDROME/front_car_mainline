# drive146

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive146-front_car_circle_drive146.log
- remote_log: /tmp/front_car_circle_drive146.log
- started_at: 2026-06-22T15:20:25+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive146 6
```

4897 /tmp/front_car_circle_drive146.log
ATGSeedDiag: seed=1@5,86/1@119,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(12.5) imip=34/53 pass=10110 acc=-1 ipm=137.4,72.6 inv=129.0,40.0 | 1(18.0) imip=0/10 pass=10111 acc=-1 ipm=103.4,115.2 inv=123.0,101.3
frame=938 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=54/10 raw=153/39 sel=54/36 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.0/14.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,98) md=48/1/77 cxcy=84.0,119.6 guide=-40.64 atg=60.0/60.0/60.0 pure=-11.54/-11.55 yaw=3657 cmd=3857 actual=2822 signed=0 rps=0/7035:4783/8204 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/10 centerNum=54/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/36 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-32.27@111,100 dx=27.2 idx=10/31 dist=48/90 right=1:-27.23@114,85 dx=29.5 idx=0/9 dist=18/18 sel=1:-42.81@125,99 dx=40.9 idx=0/24 dist=48/70 edge=1:-33.67@118.5,91.0 dx=34.5 width=38.3 l=116,72 r=121,110
CxScan: raw_ref=80.0 edge=118.5,91.0 best_raw_x=140 best_err=-12.49 best_cxcy=107.0,119.7 scan=0:-51.7,10:-50.0,20:-48.1,30:-46.1,40:-44.0,50:-41.7,60:-39.2,70:-36.5,80:-33.7,90:-30.6,100:-27.4,110:-23.9,120:-20.3,130:-16.5,140:-12.5
ATGSeedDiag: seed=1@4,87/1@119,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=52(13.0) imip=42/53 pass=10100 acc=-1 ipm=154.9,77.7 inv=152.0,43.4 | 4(14.3) imip=0/9 pass=10111 acc=-1 ipm=109.9,112.5 inv=132.9,93.1
frame=939 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=54/11 raw=153/40 sel=54/36 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.7/15.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,98) md=48/1/78 cxcy=84.0,119.6 guide=-40.47 atg=60.0/60.0/60.0 pure=-11.42/-11.42 yaw=3643 cmd=3843 actual=2816 signed=0 rps=0/7028:5001/8313 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/11 centerNum=54/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/36 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-32.27@111,100 dx=27.3 idx=10/31 dist=48/90 right=1:-29.31@116,85 dx=32.3 idx=0/10 dist=20/20 sel=1:-42.82@125,99 dx=40.9 idx=0/24 dist=48/70 edge=1:-34.80@120.0,91.0 dx=36.0 width=38.8 l=116,72 r=124,110
CxScan: raw_ref=80.0 edge=120.0,91.0 best_raw_x=140 best_err=-14.06 best_cxcy=107.0,119.7 scan=0:-52.3,10:-50.6,20:-48.8,30:-46.9,40:-44.8,50:-42.6,60:-40.2,70:-37.6,80:-34.8,90:-31.8,100:-28.7,110:-25.3,120:-21.7,130:-18.0,140:-14.1
ATGSeedDiag: seed=1@4,87/1@119,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(11.7) imip=35/53 pass=10100 acc=-1 ipm=139.5,72.6 inv=131.1,40.0 | 3(15.5) imip=0/10 pass=10111 acc=-1 ipm=107.7,113.4 inv=129.6,95.7
frame=940 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=54/10 raw=153/39 sel=54/36 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.3/16.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,98) md=48/1/78 cxcy=84.0,119.6 guide=-40.56 atg=60.0/60.0/60.0 pure=-11.47/-11.46 yaw=3650 cmd=3850 actual=2825 signed=0 rps=0/7032:5125/8414 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=54/10 centerNum=54/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=54/36 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-32.28@111,100 dx=27.3 idx=10/31 dist=48/90 right=1:-27.94@114,86 dx=30.3 idx=0/9 dist=18/18 sel=1:-42.81@125,99 dx=40.9 idx=0/24 dist=48/70 edge=1:-34.31@119.0,91.5 dx=35.0 width=39.5 l=116,72 r=122,111
CxScan: raw_ref=80.0 edge=119.0,91.5 best_raw_x=140 best_err=-13.14 best_cxcy=107.0,119.7 scan=0:-52.2,10:-50.5,20:-48.6,30:-46.7,40:-44.5,50:-42.3,60:-39.8,70:-37.1,80:-34.3,90:-31.3,100:-28.0,110:-24.6,120:-20.9,130:-17.1,140:-13.1
ATGSeedDiag: seed=1@4,87/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(11.3) imip=35/53 pass=10100 acc=-1 ipm=139.5,72.8 inv=131.2,40.1 | 8(16.6) imip=0/9 pass=10111 acc=-1 ipm=119.3,110.7 inv=148.9,88.2
frame=941 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/10 raw=153/38 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.4/14.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(120,99) md=48/1/75 cxcy=84.0,119.6 guide=-40.89 atg=60.0/60.0/60.0 pure=-11.66/-11.61 yaw=3680 cmd=3880 actual=2844 signed=0 rps=0/7047:5058/8032 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-32.58@112,100 dx=27.5 idx=10/31 dist=48/87 right=1:-28.07@114,86 dx=30.5 idx=0/9 dist=18/18 sel=1:-42.82@125,99 dx=40.9 idx=0/24 dist=48/68 edge=1:-34.57@119.0,92.0 dx=35.0 width=38.5 l=116,73 r=122,111
CxScan: raw_ref=80.0 edge=119.0,92.0 best_raw_x=140 best_err=-13.26 best_cxcy=107.0,119.7 scan=0:-52.4,10:-50.7,20:-48.9,30:-46.9,40:-44.8,50:-42.5,60:-40.1,70:-37.4,80:-34.6,90:-31.5,100:-28.3,110:-24.8,120:-21.1,130:-17.3,140:-13.3
ATGSeedDiag: seed=1@4,87/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(14.4) imip=33/52 pass=10110 acc=-1 ipm=135.0,72.8 inv=126.7,40.1 | 3(14.5) imip=0/9 pass=10111 acc=-1 ipm=108.2,113.4 inv=130.7,95.6
frame=942 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/10 raw=153/38 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.9/17.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,100) md=48/1/75 cxcy=84.0,119.6 guide=-41.58 atg=60.0/60.0/60.0 pure=-11.78/-11.78 yaw=3742 cmd=3942 actual=2829 signed=0 rps=0/7076:5199/7831 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-33.98@113,100 dx=28.8 idx=10/32 dist=49/87 right=1:-28.66@115,86 dx=31.1 idx=0/9 dist=18/18 sel=1:-44.07@125,100 dx=41.3 idx=0/24 dist=48/68 edge=1:-33.27@117.0,92.5 dx=33.0 width=38.3 l=112,74 r=122,111
CxScan: raw_ref=80.0 edge=117.0,92.5 best_raw_x=140 best_err=-11.22 best_cxcy=107.0,119.7 scan=0:-51.9,10:-50.1,20:-48.2,30:-46.2,40:-43.9,50:-41.6,60:-39.0,70:-36.2,80:-33.3,90:-30.1,100:-26.7,110:-23.1,120:-19.3,130:-15.3,140:-11.2
ATGSeedDiag: seed=1@4,87/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(13.9) imip=35/52 pass=10100 acc=-1 ipm=139.9,74.5 inv=133.0,41.2 | 8(17.0) imip=0/9 pass=10111 acc=-1 ipm=119.6,111.1 inv=150.2,89.1
frame=943 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/10 raw=153/38 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.8/14.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,100) md=48/1/74 cxcy=84.0,119.6 guide=-41.67 atg=60.0/60.0/60.0 pure=-11.88/-11.89 yaw=3750 cmd=3950 actual=2810 signed=0 rps=0/7080:5109/7482 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-32.89@111,101 dx=27.2 idx=10/31 dist=48/87 right=1:-28.48@115,86 dx=30.8 idx=0/9 dist=18/18 sel=1:-44.18@125,100 dx=41.4 idx=0/24 dist=48/68 edge=1:-35.97@120.5,92.5 dx=36.5 width=37.1 l=119,74 r=122,111
CxScan: raw_ref=80.0 edge=120.5,92.5 best_raw_x=140 best_err=-14.99 best_cxcy=107.0,119.7 scan=0:-53.3,10:-51.7,20:-49.9,30:-48.0,40:-45.9,50:-43.7,60:-41.3,70:-38.7,80:-36.0,90:-33.0,100:-29.8,110:-26.4,120:-22.8,130:-19.0,140:-15.0
ATGSeedDiag: seed=1@4,87/1@120,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(14.8) imip=40/52 pass=10100 acc=-1 ipm=151.0,78.1 inv=148.1,43.7 | 4(14.2) imip=0/9 pass=10111 acc=-1 ipm=110.4,112.9 inv=134.5,94.1
frame=944 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/10 raw=153/37 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.0/15.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(121,100) md=48/1/76 cxcy=84.0,119.6 guide=-41.76 atg=60.0/60.0/60.0 pure=-11.79/-11.78 yaw=3759 cmd=3959 actual=2792 signed=0 rps=0/7084:5393/8121 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-32.92@111,101 dx=27.2 idx=10/31 dist=48/87 right=1:-28.97@116,86 dx=31.5 idx=0/9 dist=18/18 sel=1:-44.26@126,100 dx=41.6 idx=0/24 dist=48/68 edge=1:-34.45@118.5,92.5 dx=34.5 width=37.7 l=115,74 r=122,111
CxScan: raw_ref=80.0 edge=118.5,92.5 best_raw_x=140 best_err=-12.85 best_cxcy=107.0,119.7 scan=0:-52.5,10:-50.8,20:-49.0,30:-47.0,40:-44.8,50:-42.5,60:-40.0,70:-37.3,80:-34.4,90:-31.4,100:-28.1,110:-24.5,120:-20.8,130:-16.9,140:-12.9
ATGSeedDiag: seed=1@4,87/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(16.0) imip=40/52 pass=10100 acc=-1 ipm=151.1,77.7 inv=147.9,43.3 | 1(15.2) imip=0/9 pass=10111 acc=-1 ipm=104.4,115.4 inv=125.4,101.6
frame=945 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/10 raw=153/36 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=8.9/13.5/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,99) md=49/1/74 cxcy=84.0,119.6 guide=-42.35 atg=60.0/60.0/60.0 pure=-11.67/-11.65 yaw=3812 cmd=4012 actual=2785 signed=0 rps=0/7110:5328/8455 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/10 centerNum=53/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-34.09@113,100 dx=29.1 idx=10/32 dist=49/88 right=1:-29.06@116,86 dx=31.6 idx=0/9 dist=18/18 sel=1:-43.23@126,99 dx=41.5 idx=0/24 dist=48/68 edge=1:-35.22@119.5,92.5 dx=35.5 width=37.3 l=117,74 r=122,111
CxScan: raw_ref=80.0 edge=119.5,92.5 best_raw_x=140 best_err=-13.93 best_cxcy=107.0,119.7 scan=0:-52.9,10:-51.2,20:-49.4,30:-47.5,40:-45.4,50:-43.1,60:-40.7,70:-38.0,80:-35.2,90:-32.2,100:-28.9,110:-25.5,120:-21.8,130:-18.0,140:-13.9
ATGSeedDiag: seed=1@4,87/1@121,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(8.9) imip=0/20 pass=10110 acc=-1 ipm=63.0,92.5 inv=46.8,57.9 | 3(13.5) imip=0/9 pass=10111 acc=-1 ipm=108.8,113.6 inv=132.3,96.2
frame=946 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/9 raw=153/36 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.0/14.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,99) md=49/1/74 cxcy=84.0,119.6 guide=-42.36 atg=60.0/60.0/60.0 pure=-11.65/-11.62 yaw=3812 cmd=4012 actual=2781 signed=0 rps=0/7110:5151/8424 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/9 centerNum=53/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-34.34@113,100 dx=29.3 idx=10/32 dist=49/89 right=1:-27.34@113,86 dx=29.2 idx=0/8 dist=16/16 sel=1:-43.32@126,99 dx=41.7 idx=0/24 dist=48/68 edge=1:-34.84@119.0,92.5 dx=35.0 width=37.2 l=117,74 r=121,111
CxScan: raw_ref=80.0 edge=119.0,92.5 best_raw_x=140 best_err=-13.39 best_cxcy=107.0,119.7 scan=0:-52.7,10:-51.0,20:-49.2,30:-47.2,40:-45.1,50:-42.8,60:-40.4,70:-37.7,80:-34.8,90:-31.8,100:-28.5,110:-25.0,120:-21.3,130:-17.4,140:-13.4
ATGSeedDiag: seed=1@4,88/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(14.0) imip=36/52 pass=10100 acc=-1 ipm=142.0,74.2 inv=134.9,41.0 | 1(14.2) imip=0/8 pass=10111 acc=-1 ipm=104.9,115.4 inv=126.5,101.6
frame=947 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/9 raw=153/35 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.8/13.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(124,100) md=50/1/74 cxcy=84.0,119.6 guide=-42.04 atg=60.0/60.0/60.0 pure=-11.64/-11.63 yaw=3784 cmd=3984 actual=2773 signed=0 rps=0/7096:5063/8561 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/9 centerNum=53/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-34.39@113,100 dx=29.2 idx=10/32 dist=49/87 right=1:-27.56@113,86 dx=29.4 idx=0/8 dist=16/16 sel=1:-44.55@126,100 dx=42.0 idx=0/24 dist=48/68 edge=1:-32.87@116.5,92.5 dx=32.5 width=38.1 l=112,74 r=121,111
CxScan: raw_ref=80.0 edge=116.5,92.5 best_raw_x=140 best_err=-10.67 best_cxcy=107.0,119.7 scan=0:-51.6,10:-49.9,20:-47.9,30:-45.9,40:-43.6,50:-41.2,60:-38.7,70:-35.9,80:-32.9,90:-29.7,100:-26.2,110:-22.6,120:-18.8,130:-14.8,140:-10.7
ATGSeedDiag: seed=1@4,88/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(14.8) imip=36/52 pass=10100 acc=-1 ipm=142.5,74.4 inv=135.6,41.1 | 7(13.3) imip=0/8 pass=10111 acc=-1 ipm=118.3,111.6 inv=148.5,90.5
frame=948 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/9 raw=153/34 sel=53/35 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.4/12.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(122,100) md=48/1/75 cxcy=84.0,119.6 guide=-42.32 atg=60.0/60.0/60.0 pure=-11.79/-11.69 yaw=3809 cmd=4009 actual=2763 signed=0 rps=0/7108:4742/8037 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/9 centerNum=53/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/35 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-33.64@112,101 dx=27.8 idx=10/31 dist=48/87 right=1:-27.96@114,86 dx=29.9 idx=0/8 dist=16/16 sel=1:-44.75@126,100 dx=42.3 idx=0/24 dist=48/68 edge=1:-34.84@119.0,92.5 dx=35.0 width=37.2 l=117,74 r=121,111
CxScan: raw_ref=80.0 edge=119.0,92.5 best_raw_x=140 best_err=-13.39 best_cxcy=107.0,119.7 scan=0:-52.7,10:-51.0,20:-49.2,30:-47.2,40:-45.1,50:-42.8,60:-40.4,70:-37.7,80:-34.8,90:-31.8,100:-28.5,110:-25.0,120:-21.3,130:-17.4,140:-13.4
ATGSeedDiag: seed=1@4,88/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(13.4) imip=38/52 pass=10100 acc=-1 ipm=147.1,76.0 inv=141.8,42.2 | 3(12.4) imip=0/8 pass=10111 acc=-1 ipm=109.7,113.7 inv=134.4,96.4
frame=949 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/9 raw=153/34 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.8/15.4/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(122,100) md=48/1/72 cxcy=84.0,119.6 guide=-42.40 atg=60.0/60.0/60.0 pure=-11.85/-11.90 yaw=3816 cmd=4016 actual=2755 signed=0 rps=0/7112:5057/8062 duty=0/18 pwm=PWM2:0/PWM1:18 motor=2:0/1:18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/9 centerNum=53/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-35.73@114,101 dx=29.9 idx=10/32 dist=49/87 right=1:-28.51@115,87 dx=30.5 idx=0/8 dist=16/16 sel=1:-44.73@126,100 dx=42.3 idx=0/24 dist=48/66 edge=1:-35.10@119.0,93.0 dx=35.0 width=38.2 l=117,74 r=121,112
CxScan: raw_ref=80.0 edge=119.0,93.0 best_raw_x=140 best_err=-13.52 best_cxcy=107.0,119.7 scan=0:-53.0,10:-51.3,20:-49.5,30:-47.5,40:-45.4,50:-43.1,60:-40.6,70:-38.0,80:-35.1,90:-32.0,100:-28.7,110:-25.2,120:-21.5,130:-17.6,140:-13.5
ATGSeedDiag: seed=1@4,88/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(15.8) imip=32/52 pass=10110 acc=-1 ipm=133.5,74.1 inv=126.1,41.0 | 7(15.4) imip=0/8 pass=10111 acc=-1 ipm=118.8,111.9 inv=150.1,91.2
frame=950 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/9 raw=153/33 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.7/12.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(123,101) md=48/1/70 cxcy=84.0,119.6 guide=-43.91 atg=60.0/60.0/60.0 pure=-11.97/-12.00 yaw=3951 cmd=4151 actual=2739 signed=0 rps=0/7177:4970/7544 duty=0/19 pwm=PWM2:0/PWM1:19 motor=2:0/1:19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/9 centerNum=52/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=49 cxcy=84.0,119.6 left=1:-37.10@115,101 dx=31.3 idx=11/33 dist=48/82 right=1:-28.86@115,87 dx=31.0 idx=0/8 dist=16/16 sel=1:-46.20@128,101 dx=43.6 idx=0/24 dist=48/64 edge=1:-36.14@120.0,93.5 dx=36.0 width=37.2 l=118,75 r=122,112
CxScan: raw_ref=80.0 edge=120.0,93.5 best_raw_x=140 best_err=-14.74 best_cxcy=107.0,119.7 scan=0:-53.7,10:-52.0,20:-50.2,30:-48.3,40:-46.2,50:-44.0,60:-41.6,70:-39.0,80:-36.1,90:-33.1,100:-29.9,110:-26.4,120:-22.7,130:-18.8,140:-14.7
ATGSeedDiag: seed=1@4,88/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(15.7) imip=35/51 pass=10100 acc=-1 ipm=140.5,75.7 inv=134.6,42.0 | 5(12.3) imip=0/8 pass=10111 acc=-1 ipm=114.6,112.7 inv=143.1,93.4

- stopped_at: 2026-06-22T15:20:37+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive146
```
