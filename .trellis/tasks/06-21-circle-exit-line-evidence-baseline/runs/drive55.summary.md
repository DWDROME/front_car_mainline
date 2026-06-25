# drive55

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive55-front_car_circle_drive55.log
- remote_log: /tmp/front_car_circle_drive55.log
- started_at: 2026-06-22T03:33:49+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive55 6
```

3812 /tmp/front_car_circle_drive55.log
CxScan: raw_ref=80.0 edge=108.0,92.0 best_raw_x=140 best_err=-1.13 best_cxcy=107.0,119.7 scan=0:-47.3,10:-45.2,20:-42.9,30:-40.5,40:-37.8,50:-35.0,60:-32.0,70:-28.7,80:-25.3,90:-21.6,100:-17.8,110:-13.8,120:-9.7,130:-5.4,140:-1.1
ATGSeedDiag: seed=1@4,98/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(14.4) imip=0/20 pass=10110 acc=-1 ipm=63.1,94.1 inv=46.2,59.9 | 1(17.2) imip=0/10 pass=10111 acc=-1 ipm=106.2,115.1 inv=128.9,100.6
frame=865 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=56/10 raw=154/36 sel=56/37 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.1/16.0/0.0/0.0 dist=0 m0=(84,119) ml=(103,100) md=32/1/82 cxcy=84.0,119.6 guide=-25.63 atg=60.0/60.0/60.0 pure=-10.91/-10.88 yaw=1538 cmd=1738 actual=481 signed=0 rps=2619/7381:7856/8845 duty=0/18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=56/10 centerNum=56/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=56/37 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.88@101,101 dx=16.7 idx=8/24 dist=32/92 right=1:-27.41@114,85 dx=30.2 idx=0/9 dist=18/18 sel=1:-28.62@108,100 dx=23.6 idx=0/16 dist=32/72 edge=1:-25.26@107.5,93.0 dx=23.5 width=46.0 l=91,77 r=124,109
CxScan: raw_ref=80.0 edge=107.5,93.0 best_raw_x=140 best_err=-0.58 best_cxcy=107.0,119.7 scan=0:-47.6,10:-45.5,20:-43.2,30:-40.7,40:-38.0,50:-35.2,60:-32.1,70:-28.8,80:-25.3,90:-21.5,100:-17.6,110:-13.5,120:-9.3,130:-5.0,140:-0.6
ATGSeedDiag: seed=1@4,99/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(15.1) imip=35/55 pass=10100 acc=-1 ipm=138.5,69.4 inv=127.8,38.0 | 8(16.0) imip=0/9 pass=10111 acc=-1 ipm=121.7,109.0 inv=150.3,84.1
frame=866 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=55/9 raw=154/33 sel=55/36 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.5/13.8/0.0/0.0 dist=0 m0=(84,119) ml=(107,100) md=32/1/78 cxcy=84.0,119.6 guide=-29.84 atg=60.0/60.0/60.0 pure=-11.03/-11.02 yaw=1790 cmd=1990 actual=569 signed=0 rps=2272/7728:5800/6528 duty=1/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=55/9 centerNum=55/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=55/36 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.61@102,101 dx=18.1 idx=9/25 dist=33/89 right=1:-26.75@113,85 dx=28.9 idx=0/8 dist=16/16 sel=1:-30.99@110,100 dx=25.7 idx=0/16 dist=32/70 edge=1:-25.95@108.0,93.5 dx=24.0 width=44.6 l=93,77 r=123,110
CxScan: raw_ref=80.0 edge=108.0,93.5 best_raw_x=140 best_err=-1.17 best_cxcy=107.0,119.7 scan=0:-48.1,10:-46.0,20:-43.8,30:-41.3,40:-38.7,50:-35.8,60:-32.8,70:-29.5,80:-26.0,90:-22.2,100:-18.3,110:-14.2,120:-9.9,130:-5.6,140:-1.2
ATGSeedDiag: seed=1@4,99/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(13.5) imip=36/54 pass=10100 acc=-1 ipm=141.4,71.1 inv=131.8,39.0 | 7(13.8) imip=0/8 pass=10111 acc=-1 ipm=120.5,110.0 inv=149.7,86.3
frame=867 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/9 raw=170/30 sel=9/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/13.8/0.0/0.0 dist=0 m0=(84,119) ml=(103,89) md=33/1/42 cxcy=84.0,119.6 guide=-19.22 atg=60.0/60.0/60.0 pure=-7.50/-7.50 yaw=1153 cmd=1353 actual=660 signed=0 rps=3146/6854:6241/7155 duty=3/18
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/9 centerNum=1/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-16.35@99,91 dx=15.2 idx=0/1 dist=32/46 sel=1:-19.68@103,89 dx=19.3 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=124,110
ATGSeedDiag: seed=1@49,101/1@131,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 3(13.8) imip=0/8 pass=10111 acc=-1 ipm=112.7,113.1 inv=139.6,94.5
frame=868 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/8 raw=170/28 sel=8/21 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/11.5/0.0/0.0 dist=0 m0=(84,119) ml=(102,90) md=32/1/43 cxcy=84.0,119.6 guide=-19.86 atg=60.0/60.0/60.0 pure=-7.66/-7.66 yaw=1191 cmd=1391 actual=752 signed=0 rps=3093/6907:6010/6968 duty=3/18
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/8 centerNum=1/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=8/21 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-16.97@100,91 dx=15.8 idx=0/1 dist=33/45 sel=1:-20.25@104,89 dx=19.8 idx=0/16 dist=32/40 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=122,111
ATGSeedDiag: seed=1@48,104/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 3(11.5) imip=0/7 pass=10111 acc=-1 ipm=113.5,113.2 inv=141.7,95.0
frame=870 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/6 raw=170/23 sel=6/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/10.6/0.0/0.0 dist=0 m0=(84,119) ml=(103,90) md=33/1/39 cxcy=84.0,119.6 guide=-21.11 atg=60.0/60.0/60.0 pure=-7.49/-7.49 yaw=1267 cmd=1467 actual=895 signed=0 rps=2990/7010:5996/6991 duty=3/19
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/6 centerNum=1/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-18.49@101,91 dx=17.2 idx=0/1 dist=33/41 sel=1:-21.45@105,90 dx=20.9 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=120,112
ATGSeedDiag: seed=1@46,108/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(10.6) imip=0/5 pass=10111 acc=-1 ipm=113.1,114.3 inv=143.1,98.2
frame=871 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=53/6 raw=154/21 sel=53/34 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.5/8.7/0.0/0.0 dist=0 m0=(84,119) ml=(111,103) md=33/1/74 cxcy=84.0,119.6 guide=-33.75 atg=60.0/60.0/60.0 pure=-11.59/-11.39 yaw=2025 cmd=2225 actual=949 signed=0 rps=1950/8050:5616/6642 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=53/6 centerNum=53/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=53/34 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.35@106,104 dx=21.9 idx=9/26 dist=32/82 right=1:-26.43@111,88 dx=27.1 idx=0/5 dist=10/10 sel=1:-35.64@113,102 dx=29.2 idx=0/16 dist=32/66 edge=1:-27.40@108.0,96.5 dx=24.0 width=40.8 l=96,80 r=120,113
CxScan: raw_ref=80.0 edge=108.0,96.5 best_raw_x=140 best_err=-1.24 best_cxcy=107.0,119.7 scan=0:-49.9,10:-47.8,20:-45.6,30:-43.1,40:-40.4,50:-37.5,60:-34.4,70:-31.0,80:-27.4,90:-23.5,100:-19.4,110:-15.1,120:-10.6,130:-5.9,140:-1.2
ATGSeedDiag: seed=1@4,102/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(12.5) imip=0/11 pass=10110 acc=-1 ipm=52.3,112.4 inv=11.1,93.9 | 1(8.7) imip=0/5 pass=10111 acc=-1 ipm=111.5,115.6 inv=142.0,102.1
frame=872 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=154/18 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.9/5.5/0.0/0.0 dist=0 m0=(84,119) ml=(112,103) md=34/1/70 cxcy=84.0,119.6 guide=-34.06 atg=60.0/60.0/60.0 pure=-11.64/-11.62 yaw=2043 cmd=2243 actual=997 signed=0 rps=1925/8075:5951/7258 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.67@106,105 dx=21.8 idx=9/26 dist=32/80 right=1:-25.66@110,89 dx=25.9 idx=0/4 dist=8/8 sel=1:-36.65@114,103 dx=29.9 idx=0/16 dist=32/62 edge=1:-26.91@107.5,96.5 dx=23.5 width=40.2 l=96,80 r=119,113
CxScan: raw_ref=80.0 edge=107.5,96.5 best_raw_x=140 best_err=-0.62 best_cxcy=107.0,119.7 scan=0:-49.7,10:-47.6,20:-45.3,30:-42.8,40:-40.1,50:-37.2,60:-34.0,70:-30.6,80:-26.9,90:-23.0,100:-18.8,110:-14.5,120:-10.0,130:-5.3,140:-0.6
ATGSeedDiag: seed=1@4,103/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(15.9) imip=32/51 pass=10110 acc=-1 ipm=134.7,74.1 inv=127.4,41.0 | 1(5.5) imip=0/4 pass=10111 acc=-1 ipm=112.4,115.6 inv=144.1,102.1
frame=873 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/5 raw=153/15 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.7/4.9/0.0/0.0 dist=0 m0=(84,119) ml=(112,104) md=32/1/69 cxcy=84.0,119.6 guide=-36.96 atg=60.0/60.0/60.0 pure=-11.75/-11.64 yaw=2218 cmd=2418 actual=1064 signed=0 rps=1686/8314:5837/7237 duty=0/24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/5 centerNum=52/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.59@106,105 dx=22.4 idx=9/26 dist=32/81 right=1:-26.88@111,89 dx=27.3 idx=0/4 dist=8/8 sel=1:-37.55@115,103 dx=30.6 idx=0/16 dist=32/62 edge=1:-28.14@108.5,97.0 dx=24.5 width=39.4 l=97,81 r=120,113
CxScan: raw_ref=80.0 edge=108.5,97.0 best_raw_x=140 best_err=-1.88 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.4,20:-46.2,30:-43.8,40:-41.1,50:-38.2,60:-35.1,70:-31.8,80:-28.1,90:-24.3,100:-20.2,110:-15.8,120:-11.3,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@4,104/1@142,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(10.7) imip=0/19 pass=10110 acc=-1 ipm=64.5,98.5 inv=46.3,65.8 | 3(4.9) imip=0/4 pass=10111 acc=-1 ipm=117.8,114.1 inv=152.9,97.3
frame=874 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/2 raw=154/170 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.6/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(113,104) md=33/1/69 cxcy=84.0,119.6 guide=-36.51 atg=60.0/60.0/60.0 pure=-11.72/-11.59 yaw=2191 cmd=2391 actual=1132 signed=0 rps=1723/8277:6199/7662 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/2 centerNum=52/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.03@107,105 dx=22.7 idx=9/26 dist=32/80 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-38.03@115,103 dx=31.0 idx=0/16 dist=32/62 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=99,80 r=-1,-1
ATGSeedDiag: seed=1@4,104/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(12.6) imip=0/18 pass=10110 acc=-1 ipm=62.9,100.3 inv=42.8,68.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=875 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/4 raw=154/12 sel=52/33 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.9/3.7/0.0/0.0 dist=0 m0=(84,119) ml=(113,104) md=33/1/72 cxcy=84.0,119.6 guide=-36.89 atg=60.0/60.0/60.0 pure=-11.68/-11.46 yaw=2214 cmd=2414 actual=1205 signed=0 rps=1692/8308:6335/7875 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/4 centerNum=52/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/33 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.00@109,105 dx=24.7 idx=9/27 dist=33/80 right=1:-26.59@111,90 dx=26.5 idx=0/3 dist=6/6 sel=1:-38.52@115,103 dx=31.4 idx=0/16 dist=32/64 edge=1:-27.91@108.0,97.5 dx=24.0 width=39.7 l=97,81 r=119,114
CxScan: raw_ref=80.0 edge=108.0,97.5 best_raw_x=140 best_err=-1.27 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.5,20:-46.2,30:-43.7,40:-41.1,50:-38.2,60:-35.0,70:-31.6,80:-27.9,90:-24.0,100:-19.8,110:-15.4,120:-10.8,130:-6.1,140:-1.3
ATGSeedDiag: seed=1@4,105/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(11.9) imip=0/11 pass=10110 acc=-1 ipm=53.1,113.3 inv=11.4,96.6 | 1(3.7) imip=0/3 pass=10111 acc=-1 ipm=114.7,116.1 inv=150.3,103.6
frame=876 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=52/1 raw=154/170 sel=52/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=12.2/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(114,104) md=34/1/70 cxcy=84.0,119.6 guide=-36.73 atg=60.0/60.0/60.0 pure=-11.70/-11.61 yaw=2204 cmd=2404 actual=1291 signed=0 rps=1706/8294:6056/7559 duty=0/23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=52/1 centerNum=52/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.67@109,105 dx=25.0 idx=9/27 dist=32/78 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-39.16@116,104 dx=31.9 idx=0/16 dist=32/62 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=99,81 r=-1,-1
ATGSeedDiag: seed=1@4,106/1@135,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(12.2) imip=34/51 pass=10110 acc=-1 ipm=140.6,75.7 inv=134.7,42.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=877 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=51/2 raw=154/7 sel=51/32 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.5/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(114,105) md=32/1/69 cxcy=84.0,119.6 guide=-39.36 atg=60.0/60.0/60.0 pure=-11.81/-11.65 yaw=2362 cmd=2562 actual=1378 signed=0 rps=1489/8511:5849/7197 duty=0/25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=51/2 centerNum=51/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=51/32 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.99@109,106 dx=24.9 idx=9/27 dist=33/78 right=1:-25.46@109,91 dx=24.6 idx=0/1 dist=2/2 sel=1:-39.98@116,104 dx=32.5 idx=0/16 dist=32/62 edge=1:-28.94@108.5,98.5 dx=24.5 width=38.9 l=100,81 r=117,116
CxScan: raw_ref=80.0 edge=108.5,98.5 best_raw_x=140 best_err=-1.94 best_cxcy=107.0,119.7 scan=0:-51.4,10:-49.4,20:-47.1,30:-44.7,40:-42.1,50:-39.2,60:-36.0,70:-32.6,80:-28.9,90:-25.0,100:-20.8,110:-16.3,120:-11.7,130:-6.8,140:-1.9
ATGSeedDiag: seed=1@4,107/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(13.5) imip=39/50 pass=10100 acc=-1 ipm=152.4,79.0 inv=150.7,44.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=878 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=50/1 raw=154/3 sel=50/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=10.5/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(115,106) md=32/1/64 cxcy=84.0,119.6 guide=-41.27 atg=60.0/60.0/60.0 pure=-12.15/-12.15 yaw=2476 cmd=2676 actual=1464 signed=0 rps=1332/8668:5915/7230 duty=0/25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=50/1 centerNum=50/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=50/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.79@111,107 dx=26.9 idx=9/28 dist=33/74 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-41.96@118,105 dx=33.6 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,82 r=-1,-1
ATGSeedDiag: seed=1@4,107/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=42(10.5) imip=32/49 pass=10110 acc=-1 ipm=137.4,78.4 inv=133.6,44.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=49/0 raw=154/0 sel=49/30 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.8/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(116,107) md=33/1/65 cxcy=84.0,119.6 guide=-41.20 atg=60.0/60.0/60.0 pure=-12.24/-12.24 yaw=2472 cmd=2672 actual=1553 signed=0 rps=1338/8662:5521/7033 duty=0/25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=49/0 centerNum=49/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=49/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-35.85@109,108 dx=25.2 idx=9/27 dist=32/73 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-42.98@118,106 dx=34.0 idx=0/16 dist=32/58 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=101,83 r=-1,-1
ATGSeedDiag: seed=1@4,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(11.8) imip=37/48 pass=10100 acc=-1 ipm=149.2,81.6 inv=150.0,46.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T03:34:02+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive55
```
