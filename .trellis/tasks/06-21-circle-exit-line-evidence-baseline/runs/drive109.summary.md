# drive109

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive109-front_car_circle_drive109.log
- remote_log: /tmp/front_car_circle_drive109.log
- started_at: 2026-06-22T07:22:07+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive109 6
```

4669 /tmp/front_car_circle_drive109.log
frame=887 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/27 raw=170/107 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/9.2/0.0/0.0 dist=401 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2654 signed=1 rps=-586/8186:3118/6189 duty=-7/25 pwm=PWM2:-7/PWM1:25 motor=2:-7/1:25
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/11:73.1,105.4:57.7,77.3:9.2:10111 seed_src=lost/circle seed=0.0,0.0/-11.0,61.0 far_start=2,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/9.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/27 centerNum=1/27 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:67.11@47,127 dx=-37.4 idx=5/21 dist=32/42 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=53,101
ATGSeedDiag: seed=1@19,104/1@109,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 11(9.2) imip=1/21 pass=10111 acc=-1 ipm=73.1,105.4 inv=57.7,77.3
frame=889 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/25 raw=170/102 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/12.0/0.0/0.0 dist=418 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2673 signed=1 rps=-586/8186:2278/4393 duty=-6/28 pwm=PWM2:-6/PWM1:28 motor=2:-6/1:28
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/10:72.7,107.1:56.5,80.8:12.0:10111 seed_src=lost/circle seed=0.0,0.0/-11.0,65.0 far_start=2,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/12.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/25 centerNum=1/25 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:70.16@46,129 dx=-37.6 idx=4/20 dist=32/40 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=52,103
ATGSeedDiag: seed=1@16,108/1@104,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(12.0) imip=0/20 pass=10111 acc=-1 ipm=72.7,107.1 inv=56.5,80.8
frame=890 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/23 raw=15/97 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=4.1/10.2/0.0/0.0 dist=428 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2696 signed=1 rps=-586/8186:2224/4435 duty=-6/28 pwm=PWM2:-6/PWM1:28 motor=2:-6/1:28
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=1:78.6,109.5:67.2,86.0:4.1:10111/10:70.1,108.2:51.2,83.2:10.2:10111 seed_src=none/circle seed=0.0,0.0/-11.0,69.0 far_start=2,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=4.1/10.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/23 centerNum=3/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-0.70@85,84 dx=0.7 idx=0/2 dist=4/4 right=1:73.49@44,131 dx=-39.8 idx=4/20 dist=32/36 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=1:29.60@64.0,107.5 dx=-20.0 width=24.2 l=76,109 r=52,106
CxScan: raw_ref=80.0 edge=64.0,107.5 best_raw_x=30 best_err=1.36 best_cxcy=64.8,119.4 scan=0:-17.0,10:-11.1,20:-4.9,30:1.4,40:7.6,50:13.6,60:19.3,70:24.7,80:29.6,90:34.1,100:38.1,110:41.7,120:45.0,130:47.9,140:50.5
ATGSeedDiag: seed=1@73,90/1@99,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(4.1) imip=0/2 pass=10111 acc=-1 ipm=78.6,109.5 inv=67.2,86.0 | 10(10.2) imip=0/20 pass=10111 acc=-1 ipm=70.1,108.2 inv=51.2,83.2
frame=891 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/22 raw=2/95 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/11.7/0.0/0.0 dist=438 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2725 signed=1 rps=-586/8186:2287/4674 duty=-6/27 pwm=PWM2:-6/PWM1:27 motor=2:-6/1:27
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/9:71.3,109.4:52.9,86.0:11.7:10111 seed_src=lost/circle seed=0.0,0.0/-11.0,71.0 far_start=2,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/11.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/22 centerNum=1/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:75.23@43,132 dx=-40.9 idx=4/20 dist=32/34 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=51,106
ATGSeedDiag: seed=1@73,92/1@97,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 9(11.7) imip=0/19 pass=10111 acc=-1 ipm=71.3,109.4 inv=52.9,86.0
frame=892 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/21 raw=2/92 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/12.9/0.0/0.0 dist=448 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2745 signed=1 rps=-586/8186:2364/5038 duty=-6/27 pwm=PWM2:-6/PWM1:27 motor=2:-6/1:27
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/9:69.9,109.9:49.9,87.1:12.9:10111 seed_src=lost/circle seed=0.0,0.0/-11.0,73.0 far_start=2,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/12.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/21 centerNum=1/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:76.64@44,133 dx=-40.1 idx=3/19 dist=32/34 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=49,107
ATGSeedDiag: seed=1@73,94/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 9(12.9) imip=0/19 pass=10111 acc=-1 ipm=69.9,109.9 inv=49.9,87.1
frame=893 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/20 raw=2/89 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/13.1/0.0/0.0 dist=458 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2770 signed=1 rps=-586/8186:2186/5028 duty=-5/27 pwm=PWM2:-5/PWM1:27 motor=2:-5/1:27
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/9:68.4,110.5:46.7,88.5:13.1:10111 seed_src=lost/circle seed=0.0,0.0/-11.0,76.0 far_start=2,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/13.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/20 centerNum=1/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:77.80@45,134 dx=-39.0 idx=2/18 dist=32/34 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=50,108
ATGSeedDiag: seed=1@73,96/1@91,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 9(13.1) imip=0/19 pass=10111 acc=-1 ipm=68.4,110.5 inv=46.7,88.5
frame=894 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/19 raw=12/85 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/11.6/0.0/0.0 dist=469 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2809 signed=1 rps=-586/8186:2222/5535 duty=-6/26 pwm=PWM2:-6/PWM1:26 motor=2:-6/1:26
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/8:68.9,111.4:47.0,90.9:11.6:10111 seed_src=none/circle seed=0.0,0.0/-11.0,78.0 far_start=2,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/11.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/19 centerNum=2/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-2.04@86,88 dx=2.0 idx=0/1 dist=2/2 right=1:79.47@43,135 dx=-40.6 idx=2/18 dist=32/32 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=1:32.88@63.5,111.0 dx=-20.5 width=31.3 l=79,113 r=48,109
CxScan: raw_ref=80.0 edge=63.5,111.0 best_raw_x=25 best_err=-1.07 best_cxcy=62.9,119.4 scan=0:-17.9,10:-11.4,20:-4.5,30:2.4,40:9.3,50:15.9,60:22.1,70:27.7,80:32.9,90:37.5,100:41.5,110:45.2,120:48.4,130:51.2,140:53.7
ATGSeedDiag: seed=1@73,98/1@87,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 8(11.6) imip=0/18 pass=10111 acc=-1 ipm=68.9,111.4 inv=47.0,90.9
frame=895 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=5/0 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/1 conf=0.0/0.0/0.0/0.0 dist=480 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2839 signed=1 rps=-586/8186:2128/5372 duty=-5/26 pwm=PWM2:-5/PWM1:26 motor=2:-5/1:26
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/circle seed=0.0,0.0/140.0,91.8 far_start=140,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/1 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@73,101/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=897 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=5/0 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/1 conf=0.0/0.0/0.0/0.0 dist=500 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2841 signed=1 rps=-586/8186:2302/5531 duty=-6/26 pwm=PWM2:-6/PWM1:26 motor=2:-6/1:26
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/circle seed=0.0,0.0/140.0,91.8 far_start=140,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/1 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@73,105/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=898 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=14/0 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/1 conf=0.0/0.0/0.0/0.0 dist=511 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2851 signed=1 rps=-586/8186:2290/5451 duty=-6/26 pwm=PWM2:-6/PWM1:26 motor=2:-6/1:26
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/circle seed=0.0,0.0/140.0,91.8 far_start=140,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/1 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-2.05@86,91 dx=1.9 idx=0/1 dist=2/2 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=79,116 r=-1,-1
ATGSeedDiag: seed=1@73,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=899 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=3/0 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/1 conf=0.0/0.0/0.0/0.0 dist=524 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2879 signed=1 rps=-586/8186:2255/5134 duty=-6/27 pwm=PWM2:-6/PWM1:27 motor=2:-6/1:27
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/circle seed=0.0,0.0/140.0,91.8 far_start=140,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/1 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@69,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=902 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/0 raw=170/0 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/1 conf=0.0/0.0/0.0/0.0 dist=556 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2917 signed=1 rps=-586/8186:2325/4862 duty=-6/27 pwm=PWM2:-6/PWM1:27 motor=2:-6/1:27
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/circle seed=0.0,0.0/140.0,91.8 far_start=140,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/0 centerNum=1/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/1 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@32,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=903 line=1 track=1 cross=0 circle=4(CIRCLE_RIGHT_IN) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/1 raw=0/170 sel=87/103 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/1 conf=0.0/0.0/0.0/0.0 dist=567 begin=0/2056 m0=(84,119) ml=(116,119) md=32/0/213 cxcy=84.0,119.6 guide=-55.03 atg=60.0/44.0/10.0 pure=-13.51/-4.50 yaw=3200 cmd=3200 actual=2934 signed=1 rps=-586/8186:2315/4886 duty=-6/27 pwm=PWM2:-6/PWM1:27 motor=2:-6/1:27
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=lost/circle seed=0.0,0.0/140.0,91.8 far_start=140,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/1 not_have=0 final=87/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-59.72@110,128 dx=26.0 idx=0/16 dist=32/204 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@151,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T07:22:20+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive109
```
