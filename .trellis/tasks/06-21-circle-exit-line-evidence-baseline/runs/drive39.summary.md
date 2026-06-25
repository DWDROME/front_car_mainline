# drive39

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive39-front_car_circle_drive39.log
- remote_log: /tmp/front_car_circle_drive39.log
- started_at: 2026-06-22T02:15:36+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive39 6
```

4596 /tmp/front_car_circle_drive39.log
ATGSeedDiag: seed=1@8,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(10.1) imip=18/38 pass=10110 acc=-1 ipm=53.3,51.5 inv=49.2,29.8 | 42(101.5) imip=32/52 pass=11111 acc=42 ipm=143.1,39.6 inv=115.7,25.2
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=151/69 raw=143/136 sel=151/147 far=0/0 far_raw=0/0 l=0@-1/1@43 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.9/104.9/0.0/0.0 dist=0 m0=(84,119) ml=(78,88) md=32/1/167 cxcy=84.0,119.6 guide=6.54 atg=-4.0/13.0/29.0 pure=0.80/-1.48 yaw=-392 cmd=-564 actual=-220 signed=0 rps=5774/4226:6042/5633 duty=13/10
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@43 nearNum=151/69 centerNum=151/69 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=151/147 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.49@77,84 dx=-6.6 idx=0/13 dist=33/333 right=1:3.63@80,81 dx=-3.9 idx=0/14 dist=33/237 sel=1:6.44@77,84 dx=-6.7 idx=0/16 dist=32/292 edge=1:4.95@78.5,79.0 dx=-5.5 width=55.0 l=51,79 r=106,79
CxScan: raw_ref=80.0 edge=78.5,79.0 best_raw_x=65 best_err=-0.20 best_cxcy=78.3,119.5 scan=0:-21.6,10:-18.6,20:-15.4,30:-12.1,40:-8.8,50:-5.4,60:-1.9,70:1.5,80:5.0,90:8.3,100:11.7,110:14.9,120:18.1,130:21.1,140:24.0
ATGSeedDiag: seed=1@7,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(7.9) imip=15/35 pass=10110 acc=-1 ipm=50.7,58.3 inv=45.3,32.7 | 43(104.9) imip=33/53 pass=11111 acc=43 ipm=144.9,37.1 inv=116.0,24.4
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=153/69 raw=145/135 sel=153/150 far=0/0 far_raw=0/0 l=0@-1/1@43 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.8/101.7/0.0/0.0 dist=0 m0=(84,119) ml=(77,88) md=32/1/169 cxcy=84.0,119.6 guide=6.88 atg=-6.0/10.0/25.0 pure=0.96/-1.37 yaw=-413 cmd=-613 actual=-170 signed=0 rps=5839/4161:6149/5914 duty=13/9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@43 nearNum=153/69 centerNum=153/69 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=153/150 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.59@77,84 dx=-6.7 idx=0/13 dist=33/341 right=1:2.97@81,78 dx=-3.4 idx=0/15 dist=34/230 sel=1:6.57@77,84 dx=-6.8 idx=0/16 dist=32/298 edge=1:4.51@79.0,79.0 dx=-5.0 width=56.0 l=51,79 r=107,79
CxScan: raw_ref=80.0 edge=79.0,79.0 best_raw_x=65 best_err=-0.65 best_cxcy=78.3,119.5 scan=0:-22.0,10:-19.0,20:-15.8,30:-12.6,40:-9.2,50:-5.8,60:-2.4,70:1.1,80:4.5,90:7.9,100:11.2,110:14.5,120:17.7,130:20.7,140:23.6
ATGSeedDiag: seed=1@7,108/1@129,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(9.8) imip=18/38 pass=10110 acc=-1 ipm=50.8,51.4 inv=47.2,29.8 | 43(101.7) imip=33/53 pass=11111 acc=43 ipm=145.2,36.5 inv=116.0,24.2
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=153/67 raw=146/134 sel=153/149 far=0/0 far_raw=0/0 l=0@-1/1@42 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=8.0/99.3/0.0/0.0 dist=0 m0=(84,119) ml=(78,88) md=32/1/167 cxcy=84.0,119.6 guide=6.73 atg=-4.0/12.0/30.0 pure=0.81/-1.48 yaw=-404 cmd=-604 actual=-132 signed=0 rps=5827/4173:5733/5873 duty=13/9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@42 nearNum=153/67 centerNum=153/67 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=153/149 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.60@77,85 dx=-6.7 idx=0/13 dist=33/339 right=1:3.53@80,81 dx=-3.8 idx=0/14 dist=32/230 sel=1:6.57@77,84 dx=-6.8 idx=0/16 dist=32/296 edge=1:4.95@78.5,79.0 dx=-5.5 width=55.0 l=51,79 r=106,79
CxScan: raw_ref=80.0 edge=78.5,79.0 best_raw_x=65 best_err=-0.20 best_cxcy=78.3,119.5 scan=0:-21.6,10:-18.6,20:-15.4,30:-12.1,40:-8.8,50:-5.4,60:-1.9,70:1.5,80:5.0,90:8.3,100:11.7,110:14.9,120:18.1,130:21.1,140:24.0
ATGSeedDiag: seed=1@7,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(8.0) imip=0/11 pass=10111 acc=-1 ipm=53.3,113.8 inv=11.0,98.1 | 42(99.3) imip=32/52 pass=11111 acc=42 ipm=144.4,39.6 inv=116.7,25.2
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=158/62 raw=147/132 sel=158/151 far=0/0 far_raw=0/0 l=0@-1/1@39 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.5/96.5/0.0/0.0 dist=0 m0=(84,119) ml=(78,88) md=32/1/166 cxcy=84.0,119.6 guide=6.20 atg=-2.0/24.0/48.0 pure=0.51/-2.11 yaw=-372 cmd=-572 actual=-145 signed=0 rps=5784/4216:5842/6278 duty=13/9
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@39 nearNum=158/62 centerNum=158/62 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=158/151 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.24@78,85 dx=-6.3 idx=0/13 dist=33/349 right=1:3.84@80,80 dx=-4.2 idx=0/14 dist=33/218 sel=1:6.20@78,84 dx=-6.4 idx=0/16 dist=32/300 edge=1:4.95@78.5,79.0 dx=-5.5 width=55.0 l=51,79 r=106,79
CxScan: raw_ref=80.0 edge=78.5,79.0 best_raw_x=65 best_err=-0.20 best_cxcy=78.3,119.5 scan=0:-21.6,10:-18.6,20:-15.4,30:-12.1,40:-8.8,50:-5.4,60:-1.9,70:1.5,80:5.0,90:8.3,100:11.7,110:14.9,120:18.1,130:21.1,140:24.0
ATGSeedDiag: seed=1@7,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(9.5) imip=19/39 pass=10110 acc=-1 ipm=54.1,49.3 inv=50.3,28.9 | 39(96.5) imip=29/49 pass=11111 acc=39 ipm=140.8,45.1 inv=116.4,27.0
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=170/58 raw=170/130 sel=170/154 far=0/0 far_raw=0/0 l=0@-1/1@37 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=52.1/94.9/0.0/0.0 dist=0 m0=(84,119) ml=(79,86) md=33/1/163 cxcy=84.0,119.6 guide=5.07 atg=0.0/44.0/60.0 pure=-0.08/-2.96 yaw=-129 cmd=-116 actual=-142 signed=0 rps=5160/4840:6034/6435 duty=10/11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@37 nearNum=170/58 centerNum=170/58 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/154 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.50@79,86 dx=-5.5 idx=0/13 dist=33/361 right=1:4.43@79,82 dx=-4.7 idx=0/13 dist=32/209 sel=1:5.32@79,84 dx=-5.5 idx=0/16 dist=32/306 edge=1:4.95@78.5,79.0 dx=-5.5 width=53.0 l=52,79 r=105,79
CxScan: raw_ref=80.0 edge=78.5,79.0 best_raw_x=65 best_err=-0.20 best_cxcy=78.3,119.5 scan=0:-21.6,10:-18.6,20:-15.4,30:-12.1,40:-8.8,50:-5.4,60:-1.9,70:1.5,80:5.0,90:8.3,100:11.7,110:14.9,120:18.1,130:21.1,140:24.0
ATGSeedDiag: seed=1@8,107/1@128,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=75(52.1) imip=65/85 pass=10100 acc=-1 ipm=144.1,-4.7 inv=103.5,15.3 | 37(94.9) imip=27/47 pass=11111 acc=37 ipm=139.4,50.4 inv=117.7,29.0
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=156/55 raw=170/128 sel=156/133 far=0/0 far_raw=0/0 l=0@-1/1@35 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=53.0/94.0/0.0/0.0 dist=0 m0=(84,119) ml=(79,86) md=33/1/163 cxcy=84.0,119.6 guide=4.83 atg=5.0/60.0/60.0 pure=-0.91/-3.91 yaw=-123 cmd=-113 actual=-134 signed=0 rps=5155/4845:5838/5957 duty=11/12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@35 nearNum=156/55 centerNum=156/55 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=156/133 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.71@79,87 dx=-4.6 idx=0/13 dist=32/309 right=1:5.00@79,82 dx=-5.3 idx=0/13 dist=32/203 sel=1:4.39@79,83 dx=-4.6 idx=0/16 dist=32/264 edge=1:4.51@79.0,79.0 dx=-5.0 width=52.0 l=53,79 r=105,79
CxScan: raw_ref=80.0 edge=79.0,79.0 best_raw_x=65 best_err=-0.65 best_cxcy=78.3,119.5 scan=0:-22.0,10:-19.0,20:-15.8,30:-12.6,40:-9.2,50:-5.8,60:-2.4,70:1.1,80:4.5,90:7.9,100:11.2,110:14.5,120:17.7,130:20.7,140:23.6
ATGSeedDiag: seed=1@8,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=68(53.0) imip=58/78 pass=10100 acc=-1 ipm=138.0,8.3 inv=103.1,17.6 | 35(94.0) imip=25/45 pass=11111 acc=35 ipm=136.7,53.8 inv=117.1,30.3
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=2 speed=0 near=149/53 raw=170/127 sel=149/133 far=0/0 far_raw=0/0 l=0@-1/1@34 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=59.0/89.3/0.0/0.0 dist=0 m0=(84,119) ml=(80,88) md=32/1/165 cxcy=84.0,119.6 guide=4.12 atg=12.0/60.0/60.0 pure=-1.37/-4.20 yaw=-105 cmd=-61 actual=-149 signed=0 rps=5084/4916:6184/6122 duty=10/12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@34 nearNum=149/53 centerNum=149/53 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=149/133 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.11@80,86 dx=-4.1 idx=0/14 dist=33/313 right=1:5.21@78,81 dx=-5.6 idx=0/13 dist=34/200 sel=1:4.09@80,83 dx=-4.2 idx=0/16 dist=32/264 edge=1:4.06@79.5,79.0 dx=-4.5 width=51.0 l=54,79 r=105,79
CxScan: raw_ref=80.0 edge=79.5,79.0 best_raw_x=70 best_err=0.62 best_cxcy=80.2,119.5 scan=0:-22.4,10:-19.4,20:-16.2,30:-13.0,40:-9.7,50:-6.3,60:-2.8,70:0.6,80:4.1,90:7.5,100:10.8,110:14.1,120:17.3,130:20.3,140:23.3
ATGSeedDiag: seed=1@8,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=67(59.0) imip=57/77 pass=10100 acc=-1 ipm=139.2,11.7 inv=104.5,18.2 | 34(89.3) imip=24/44 pass=11111 acc=34 ipm=135.9,56.7 inv=117.9,31.6
ATGCircleCal: from=CIRCLE_NONE to=CIRCLE_RIGHT_BEGIN reason=entry_vote heading_deg10=0 dist=0
frame=886 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=153/53 raw=170/128 sel=153/129 far=0/0 far_raw=0/0 l=0@-1/1@34 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=59.5/92.4/0.0/0.0 dist=0 m0=(84,119) ml=(80,88) md=32/1/165 cxcy=84.0,119.6 guide=4.12 atg=9.0/60.0/60.0 pure=-1.25/-4.17 yaw=-247 cmd=-338 actual=-157 signed=1 rps=4263/3337:6063/5855 duty=7/6
ATGCorner: L=0@-1/1@34 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/136.5,56.2:118.1,31.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=67:138.8,12.3:104.5,18.4:59.5:10100/34:136.5,56.2:118.1,31.4:92.4:11111 seed_src=none/lpt seed=40.0,91.8/56.9,27.5 far_start=56,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=59.5/92.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@34 nearNum=153/53 centerNum=153/53 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=153/129 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.31@80,86 dx=-4.3 idx=0/14 dist=33/307 right=1:4.75@79,81 dx=-5.1 idx=0/13 dist=34/199 sel=1:4.27@80,83 dx=-4.4 idx=0/16 dist=32/256 edge=1:4.06@79.5,79.0 dx=-4.5 width=51.0 l=54,79 r=105,79
CxScan: raw_ref=80.0 edge=79.5,79.0 best_raw_x=70 best_err=0.62 best_cxcy=80.2,119.5 scan=0:-22.4,10:-19.4,20:-16.2,30:-13.0,40:-9.7,50:-6.3,60:-2.8,70:0.6,80:4.1,90:7.5,100:10.8,110:14.1,120:17.3,130:20.3,140:23.3
ATGSeedDiag: seed=1@8,108/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=67(59.5) imip=57/77 pass=10100 acc=-1 ipm=138.8,12.3 inv=104.5,18.4 | 34(92.4) imip=24/44 pass=11111 acc=34 ipm=136.5,56.2 inv=118.1,31.4
frame=887 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=162/54 raw=170/128 sel=162/141 far=0/0 far_raw=0/0 l=0@-1/1@35 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=58.8/94.1/0.0/0.0 dist=0 m0=(84,119) ml=(79,88) md=32/1/167 cxcy=84.0,119.6 guide=5.17 atg=4.0/60.0/60.0 pure=-0.83/-3.70 yaw=-310 cmd=-467 actual=-154 signed=1 rps=4439/3161:6449/5995 duty=7/5
ATGCorner: L=0@-1/1@35 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/139.1,55.4:119.9,31.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=71:143.4,6.8:105.7,17.3:58.8:10100/35:139.1,55.4:119.9,31.0:94.1:11111 seed_src=none/lpt seed=40.0,91.8/56.9,27.5 far_start=56,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=58.8/94.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@35 nearNum=162/54 centerNum=162/54 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=162/141 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.02@79,87 dx=-4.9 idx=0/13 dist=32/333 right=1:4.33@79,81 dx=-4.7 idx=0/13 dist=34/204 sel=1:4.80@79,84 dx=-5.0 idx=0/16 dist=32/280 edge=1:4.06@79.5,79.0 dx=-4.5 width=53.0 l=53,79 r=106,79
CxScan: raw_ref=80.0 edge=79.5,79.0 best_raw_x=70 best_err=0.62 best_cxcy=80.2,119.5 scan=0:-22.4,10:-19.4,20:-16.2,30:-13.0,40:-9.7,50:-6.3,60:-2.8,70:0.6,80:4.1,90:7.5,100:10.8,110:14.1,120:17.3,130:20.3,140:23.3
ATGSeedDiag: seed=1@8,108/1@128,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=71(58.8) imip=61/81 pass=10100 acc=-1 ipm=143.4,6.8 inv=105.7,17.3 | 35(94.1) imip=25/45 pass=11111 acc=35 ipm=139.1,55.4 inv=119.9,31.0
frame=888 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=170/56 raw=170/127 sel=170/153 far=0/0 far_raw=0/0 l=0@-1/1@36 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=45.4/96.1/0.0/0.0 dist=0 m0=(84,119) ml=(79,88) md=32/1/162 cxcy=84.0,119.6 guide=5.51 atg=1.0/52.0/60.0 pure=-0.40/-3.17 yaw=-331 cmd=-519 actual=-143 signed=1 rps=4511/3089:6209/5588 duty=8/5
ATGCorner: L=0@-1/1@36 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/140.4,53.7:120.1,30.3 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=74:145.3,-1.8:104.8,15.8:45.4:10100/36:140.4,53.7:120.1,30.3:96.1:11111 seed_src=none/lpt seed=40.0,91.8/56.9,27.5 far_start=56,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=45.4/96.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@36 nearNum=170/56 centerNum=170/56 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=170/153 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.57@79,86 dx=-5.5 idx=0/13 dist=32/357 right=1:3.68@80,81 dx=-4.0 idx=0/13 dist=33/208 sel=1:5.37@78,84 dx=-5.6 idx=0/16 dist=32/304 edge=1:4.51@79.0,79.0 dx=-5.0 width=54.0 l=52,79 r=106,79
CxScan: raw_ref=80.0 edge=79.0,79.0 best_raw_x=65 best_err=-0.65 best_cxcy=78.3,119.5 scan=0:-22.0,10:-19.0,20:-15.8,30:-12.6,40:-9.2,50:-5.8,60:-2.4,70:1.1,80:4.5,90:7.9,100:11.2,110:14.5,120:17.7,130:20.7,140:23.6
ATGSeedDiag: seed=1@7,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=74(45.4) imip=64/84 pass=10100 acc=-1 ipm=145.3,-1.8 inv=104.8,15.8 | 36(96.1) imip=26/46 pass=11111 acc=36 ipm=140.4,53.7 inv=120.1,30.3
frame=889 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=163/58 raw=152/128 sel=163/155 far=0/0 far_raw=0/0 l=0@-1/1@37 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=46.1/101.6/0.0/0.0 dist=0 m0=(84,119) ml=(78,88) md=32/1/167 cxcy=84.0,119.6 guide=6.03 atg=0.0/45.0/60.0 pure=-0.21/-2.95 yaw=-362 cmd=-562 actual=-129 signed=1 rps=4570/3030:6202/5632 duty=8/5
ATGCorner: L=0@-1/1@37 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/142.8,51.2:120.8,29.3 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=77:149.5,-4.5:106.3,15.3:46.1:10100/37:142.8,51.2:120.8,29.3:101.6:11111 seed_src=none/lpt seed=40.0,91.8/56.9,27.5 far_start=56,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=46.1/101.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@37 nearNum=163/58 centerNum=163/58 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=163/155 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.94@78,87 dx=-5.8 idx=0/13 dist=33/356 right=1:3.28@80,81 dx=-3.5 idx=0/13 dist=33/215 sel=1:5.76@78,84 dx=-6.0 idx=0/16 dist=32/308 edge=1:4.06@79.5,79.0 dx=-4.5 width=55.0 l=52,79 r=107,79
CxScan: raw_ref=80.0 edge=79.5,79.0 best_raw_x=70 best_err=0.62 best_cxcy=80.2,119.5 scan=0:-22.4,10:-19.4,20:-16.2,30:-13.0,40:-9.7,50:-6.3,60:-2.8,70:0.6,80:4.1,90:7.5,100:10.8,110:14.1,120:17.3,130:20.3,140:23.3
ATGSeedDiag: seed=1@7,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=77(46.1) imip=67/87 pass=10100 acc=-1 ipm=149.5,-4.5 inv=106.3,15.3 | 37(101.6) imip=27/47 pass=11111 acc=37 ipm=142.8,51.2 inv=120.8,29.3
frame=890 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=161/58 raw=150/130 sel=161/154 far=0/0 far_raw=0/0 l=0@-1/1@37 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=39.4/102.9/0.0/0.0 dist=0 m0=(84,119) ml=(78,86) md=33/1/165 cxcy=84.0,119.6 guide=6.07 atg=0.0/46.0/60.0 pure=-0.34/-2.96 yaw=-364 cmd=-563 actual=-166 signed=1 rps=4571/3029:5773/5447 duty=9/5
ATGCorner: L=0@-1/1@37 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/143.5,52.0:121.7,29.6 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=76:147.4,-4.1:105.4,15.4:39.4:10100/37:143.5,52.0:121.7,29.6:102.9:11111 seed_src=none/lpt seed=40.0,91.8/56.9,27.5 far_start=56,0 far_raw=0/0 far_num=0/0 straight=1/0 far_straight=0/0 conf_deg=39.4/102.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@37 nearNum=161/58 centerNum=161/58 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=161/154 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.80@78,87 dx=-5.7 idx=0/13 dist=33/349 right=1:3.21@81,81 dx=-3.5 idx=0/13 dist=34/217 sel=1:5.55@78,84 dx=-5.7 idx=0/16 dist=32/306 edge=1:4.06@79.5,79.0 dx=-4.5 width=55.0 l=52,79 r=107,79
CxScan: raw_ref=80.0 edge=79.5,79.0 best_raw_x=70 best_err=0.62 best_cxcy=80.2,119.5 scan=0:-22.4,10:-19.4,20:-16.2,30:-13.0,40:-9.7,50:-6.3,60:-2.8,70:0.6,80:4.1,90:7.5,100:10.8,110:14.1,120:17.3,130:20.3,140:23.3
ATGSeedDiag: seed=1@7,108/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=76(39.4) imip=66/86 pass=10100 acc=-1 ipm=147.4,-4.1 inv=105.4,15.4 | 37(102.9) imip=27/47 pass=11111 acc=37 ipm=143.5,52.0 inv=121.7,29.6

- stopped_at: 2026-06-22T02:15:49+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive39
```
