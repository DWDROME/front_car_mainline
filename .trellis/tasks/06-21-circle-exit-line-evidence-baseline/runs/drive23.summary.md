# drive23

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive23-front_car_circle_drive23.log
- remote_log: /tmp/front_car_circle_drive23.log
- started_at: 2026-06-22T00:49:03+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive23 6
```

5252 /tmp/front_car_circle_drive23.log
ATGSeedDiag: seed=1@15,90/1@113,85 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(28.1) imip=10/30 pass=10111 acc=-1 ipm=76.0,72.7 inv=66.4,40.5
frame=882 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/82 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/32.4/0.0/0.0 dist=1148 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=212 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:75.7,73.5:66.1,41.0:32.4:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/32.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/82 centerNum=1/82 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:32.58@59,103 dx=-25.3 idx=2/12 dist=32/316 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,76
ATGSeedDiag: seed=1@13,92/1@114,87 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(32.4) imip=10/30 pass=10111 acc=-1 ipm=75.7,73.5 inv=66.1,41.0
frame=883 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/81 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/32.6/0.0/0.0 dist=1158 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=183 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:75.8,74.0:66.1,41.4:32.6:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/32.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/81 centerNum=1/81 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:33.32@56,100 dx=-27.9 idx=3/13 dist=33/312 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,76
ATGSeedDiag: seed=1@13,93/1@114,88 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(32.6) imip=10/30 pass=10111 acc=-1 ipm=75.8,74.0 inv=66.1,41.4
frame=884 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/80 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/32.0/0.0/0.0 dist=1170 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=190 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/19:75.3,76.8:65.4,43.3:32.0:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/32.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/80 centerNum=1/80 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:33.94@56,101 dx=-28.2 idx=3/13 dist=33/310 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,77
ATGSeedDiag: seed=1@11,95/1@114,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 19(32.0) imip=9/29 pass=10111 acc=-1 ipm=75.3,76.8 inv=65.4,43.3
frame=885 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/78 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/31.7/0.0/0.0 dist=1182 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=271 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:75.5,75.3:65.7,42.2:31.7:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/31.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/78 centerNum=1/78 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:34.55@56,102 dx=-28.1 idx=3/13 dist=33/301 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,78
ATGSeedDiag: seed=1@10,96/1@115,91 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(31.7) imip=10/30 pass=10111 acc=-1 ipm=75.5,75.3 inv=65.7,42.2
frame=886 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/77 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/29.4/0.0/0.0 dist=1192 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=295 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:75.5,75.7:65.7,42.5:29.4:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/29.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/77 centerNum=1/77 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:35.08@56,102 dx=-28.5 idx=3/13 dist=33/299 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,78
ATGSeedDiag: seed=1@11,97/1@115,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(29.4) imip=10/30 pass=10111 acc=-1 ipm=75.5,75.7 inv=65.7,42.5
frame=887 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/76 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/34.7/0.0/0.0 dist=1203 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=279 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/19:74.9,78.8:64.8,44.8:34.7:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/34.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/76 centerNum=1/76 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:35.16@56,103 dx=-28.1 idx=3/13 dist=33/297 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,79
ATGSeedDiag: seed=1@9,99/1@116,94 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 19(34.7) imip=9/29 pass=10111 acc=-1 ipm=74.9,78.8 inv=64.8,44.8
frame=888 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/76 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/34.2/0.0/0.0 dist=1213 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=327 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/19:74.7,78.7:64.5,44.7:34.2:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/34.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/76 centerNum=1/76 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:35.77@55,103 dx=-28.8 idx=3/13 dist=33/297 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,79
ATGSeedDiag: seed=1@9,100/1@115,94 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 19(34.2) imip=9/29 pass=10111 acc=-1 ipm=74.7,78.7 inv=64.5,44.7
frame=889 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/75 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/33.2/0.0/0.0 dist=1223 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=354 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:74.5,77.6:64.5,43.8:33.2:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/33.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/75 centerNum=1/75 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:36.43@56,104 dx=-28.2 idx=3/13 dist=33/295 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,78
ATGSeedDiag: seed=1@7,102/1@117,96 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(33.2) imip=10/30 pass=10111 acc=-1 ipm=74.5,77.6 inv=64.5,43.8
frame=890 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/75 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/33.3/0.0/0.0 dist=1233 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=381 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:74.5,77.8:64.4,44.0:33.3:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/33.3/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/75 centerNum=1/75 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:36.44@56,105 dx=-28.2 idx=3/13 dist=33/291 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=75,78
ATGSeedDiag: seed=1@6,104/1@117,97 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(33.3) imip=10/30 pass=10111 acc=-1 ipm=74.5,77.8 inv=64.4,44.0
frame=891 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/74 raw=2/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/36.2/0.0/0.0 dist=1242 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=428 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/19:74.0,80.6:63.6,46.2:36.2:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/36.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/74 centerNum=1/74 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:37.07@56,105 dx=-28.5 idx=3/13 dist=33/287 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=74,78
ATGSeedDiag: seed=1@4,106/1@117,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 19(36.2) imip=9/29 pass=10111 acc=-1 ipm=74.0,80.6 inv=63.6,46.2
frame=892 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/73 raw=2/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/33.4/0.0/0.0 dist=1251 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=443 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:74.0,79.1:63.8,45.0:33.4:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/33.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/73 centerNum=1/73 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:37.43@53,103 dx=-30.6 idx=4/14 dist=34/288 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=74,79
ATGSeedDiag: seed=1@4,107/1@118,100 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(33.4) imip=10/30 pass=10111 acc=-1 ipm=74.0,79.1 inv=63.8,45.0
frame=893 line=0 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=1/72 raw=2/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/81/0/0 lost=0/0 conf=0.0/33.1/0.0/0.0 dist=1260 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=454 signed=0 rps=0/0:0/0 duty=0/0
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/20:74.0,79.5:63.7,45.3:33.1:10111 seed_src=lost/none seed=40.0,91.8/75.3,30.5 far_start=75,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=0.0/33.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/72 centerNum=1/72 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:37.96@53,103 dx=-31.0 idx=4/14 dist=34/284 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=74,79
ATGSeedDiag: seed=1@4,108/1@118,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(33.1) imip=10/30 pass=10111 acc=-1 ipm=74.0,79.5 inv=63.7,45.3
ATGCircleStall: circle_type=2 stalled 30 frames without selected line, reset to NONE
frame=894 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=0/71 raw=0/170 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/35.5/0.0/0.0 dist=1268 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-53.0/-53.0 pure=7.08/7.08 yaw=0 cmd=0 actual=442 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/71 centerNum=0/71 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:38.48@53,104 dx=-31.2 idx=4/14 dist=34/281 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=74,80
ATGSeedDiag: seed=0@-1,-1/1@118,102 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 20(35.5) imip=10/30 pass=10111 acc=-1 ipm=73.7,79.8 inv=63.4,45.6

- stopped_at: 2026-06-22T00:49:16+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive23
```
