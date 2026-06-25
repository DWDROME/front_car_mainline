# drive22

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive22-front_car_circle_drive22.log
- remote_log: /tmp/front_car_circle_drive22.log
- started_at: 2026-06-22T00:47:24+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive22 6
```

4540 /tmp/front_car_circle_drive22.log
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=15/1 centerNum=15/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=15/23 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-42.95@110,114 dx=26.4 idx=0/6 dist=33/50 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-41.58@112,111 dx=27.9 idx=0/16 dist=32/44 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=94,87 r=-1,-1
ATGSeedDiag: seed=1@71,107/1@137,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(17.0) imip=3/14 pass=10110 acc=-1 ipm=93.9,88.9 inv=88.3,53.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=856 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/2 raw=170/170 sel=14/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.5/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(112,111) md=32/1/43 cxcy=84.0,119.6 guide=-41.08 atg=60.0/60.0/60.0 pure=-11.56/-11.56 yaw=2465 cmd=2665 actual=1689 signed=0 rps=1348/8652:4424/6902 duty=0/26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=14/2 centerNum=14/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=14/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-42.38@110,114 dx=26.3 idx=0/6 dist=33/48 right=1:-33.00@117,93 dx=32.6 idx=0/1 dist=2/2 sel=1:-41.09@112,111 dx=27.8 idx=0/16 dist=32/42 edge=1:-23.12@101.0,103.0 dx=17.0 width=32.2 l=93,89 r=109,117
CxScan: raw_ref=80.0 edge=101.0,103.0 best_raw_x=125 best_err=0.37 best_cxcy=101.3,119.7 scan=0:-50.4,10:-48.0,20:-45.3,30:-42.4,40:-39.2,50:-35.7,60:-31.8,70:-27.6,80:-23.1,90:-18.3,100:-13.2,110:-7.8,120:-2.4,130:3.1,140:8.5
ATGSeedDiag: seed=1@71,107/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(9.5) imip=2/13 pass=10110 acc=-1 ipm=92.3,90.7 inv=86.8,55.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=857 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/5 raw=170/170 sel=14/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=15.4/24.8/0.0/0.0 dist=0 m0=(84,119) ml=(112,110) md=33/1/44 cxcy=84.0,119.6 guide=-40.22 atg=60.0/60.0/60.0 pure=-11.29/-11.29 yaw=2413 cmd=2613 actual=1917 signed=0 rps=1418/8582:5330/8212 duty=0/24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=14/5 centerNum=14/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=14/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-41.74@110,113 dx=26.4 idx=0/6 dist=33/48 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-40.46@112,110 dx=27.8 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=92,88 r=-1,-1
ATGSeedDiag: seed=1@71,107/1@141,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(15.4) imip=2/13 pass=10110 acc=-1 ipm=91.7,90.5 inv=85.9,55.3 | 1(24.8) imip=0/4 pass=10111 acc=-1 ipm=108.6,117.0 inv=138.3,107.2
frame=858 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=13/1 raw=170/170 sel=13/22 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=21.2/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(111,110) md=33/1/46 cxcy=84.0,119.6 guide=-40.07 atg=60.0/60.0/60.0 pure=-10.43/-10.43 yaw=2404 cmd=2604 actual=2109 signed=0 rps=1431/8569:3998/6069 duty=0/27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=13/1 centerNum=13/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=13/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-40.74@110,112 dx=26.4 idx=0/5 dist=32/48 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-38.81@112,108 dx=28.1 idx=0/16 dist=32/42 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=90,88 r=-1,-1
ATGSeedDiag: seed=1@73,101/1@140,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(21.2) imip=1/12 pass=10110 acc=-1 ipm=90.4,90.4 inv=84.2,55.2 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=859 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=13/4 raw=170/170 sel=13/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=6.7/18.7/0.0/0.0 dist=0 m0=(84,119) ml=(111,109) md=33/1/42 cxcy=84.0,119.6 guide=-39.20 atg=60.0/60.0/60.0 pure=-11.32/-11.32 yaw=2352 cmd=2405 actual=2299 signed=0 rps=1704/8296:4227/6666 duty=1/25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=13/4 centerNum=13/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=13/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-38.99@111,110 dx=26.7 idx=1/7 dist=33/43 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-37.83@112,107 dx=27.9 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=90,90 r=-1,-1
ATGSeedDiag: seed=1@70,108/1@133,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(6.7) imip=0/11 pass=10110 acc=-1 ipm=81.0,114.0 inv=72.0,98.0 | 1(18.7) imip=0/3 pass=10111 acc=-1 ipm=104.7,117.0 inv=128.9,107.1
frame=860 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/8 raw=170/170 sel=12/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=21.5/24.6/0.0/0.0 dist=0 m0=(84,119) ml=(109,109) md=32/1/43 cxcy=84.0,119.6 guide=-36.93 atg=60.0/60.0/60.0 pure=-10.51/-10.51 yaw=2216 cmd=2016 actual=2485 signed=0 rps=2237/7763:4127/7093 duty=3/22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=12/8 centerNum=12/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.89@110,109 dx=25.7 idx=0/6 dist=32/43 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-35.31@111,105 dx=26.8 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=87,90 r=-1,-1
ATGSeedDiag: seed=1@70,102/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(21.5) imip=0/11 pass=10110 acc=-1 ipm=87.4,92.4 inv=80.5,57.5 | 1(24.6) imip=0/7 pass=10111 acc=-1 ipm=101.4,117.3 inv=121.5,108.4
frame=861 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=13/170 sel=2/14 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(58,104) md=28/0/28 cxcy=84.0,119.6 guide=33.94 atg=-60.0/-60.0/-60.0 pure=11.97/11.97 yaw=-2037 cmd=-2237 actual=2653 signed=0 rps=8065/1935:3976/7331 duty=23/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/14 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:33.62@58,104 dx=-26.0 idx=0/1 dist=30/30 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:33.47@58,104 dx=-25.7 idx=0/13 dist=26/26 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=79,119 r=-1,-1
ATGSeedDiag: seed=1@73,108/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=862 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=12/1 raw=170/170 sel=12/20 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=4.1/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(108,107) md=33/1/42 cxcy=84.0,119.6 guide=-34.28 atg=60.0/60.0/60.0 pure=-10.22/-10.22 yaw=2057 cmd=1857 actual=2796 signed=0 rps=2455/7545:4246/7587 duty=3/21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=12/1 centerNum=12/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=12/20 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-34.40@108,107 dx=24.3 idx=0/7 dist=33/41 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-33.28@109,105 dx=24.9 idx=0/16 dist=32/38 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=85,92 r=-1,-1
ATGSeedDiag: seed=1@67,108/1@109,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(4.1) imip=0/11 pass=10110 acc=-1 ipm=81.6,107.5 inv=72.9,81.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=863 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/1 raw=170/170 sel=11/19 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=11.6/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(108,107) md=32/1/41 cxcy=84.0,119.6 guide=-33.00 atg=60.0/60.0/60.0 pure=-9.97/-9.97 yaw=1980 cmd=1780 actual=2831 signed=0 rps=2561/7439:4885/7623 duty=3/20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/1 centerNum=11/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/19 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.40@108,105 dx=24.1 idx=0/7 dist=33/39 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-31.56@109,103 dx=24.7 idx=0/16 dist=32/36 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=84,92 r=-1,-1
ATGSeedDiag: seed=1@67,104/1@115,87 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(11.6) imip=0/10 pass=10110 acc=-1 ipm=83.7,94.8 inv=75.5,60.4 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=864 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=11/0 raw=170/0 sel=11/18 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=5.0/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(107,106) md=32/1/39 cxcy=84.0,119.6 guide=-31.49 atg=60.0/60.0/60.0 pure=-10.13/-10.13 yaw=1890 cmd=1690 actual=2803 signed=0 rps=2684/7316:4884/7311 duty=3/20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=11/0 centerNum=11/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=11/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.61@107,105 dx=23.1 idx=0/7 dist=32/38 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-29.84@108,102 dx=23.6 idx=0/16 dist=32/34 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=82,93 r=-1,-1
ATGSeedDiag: seed=1@65,107/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(5.0) imip=0/10 pass=10110 acc=-1 ipm=81.6,100.1 inv=72.6,68.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=865 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=170/170 sel=2/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-10.13/-10.13 yaw=0 cmd=0 actual=2517 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@68,99/1@114,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=866 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/1 raw=170/170 sel=9/16 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.5/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(104,98) md=34/1/34 cxcy=84.0,119.6 guide=-26.02 atg=60.0/60.0/60.0 pure=-8.95/-8.95 yaw=1561 cmd=1361 actual=2680 signed=0 rps=3134/6866:4964/6293 duty=5/20
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/1 centerNum=9/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/16 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-25.38@105,100 dx=20.5 idx=0/7 dist=32/34 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-24.46@104,98 dx=20.2 idx=0/15 dist=30/30 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=78,95 r=-1,-1
ATGSeedDiag: seed=1@63,100/1@112,91 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(18.5) imip=0/8 pass=10110 acc=-1 ipm=78.5,97.6 inv=67.9,64.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=867 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=16/170 sel=2/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-8.95/-8.95 yaw=0 cmd=0 actual=2393 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@65,104/1@111,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=868 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=12/170 sel=2/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-8.95/-8.95 yaw=0 cmd=0 actual=2311 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@63,108/1@106,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=869 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=9/0 raw=170/0 sel=9/15 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=6.7/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(101,99) md=32/0/32 cxcy=84.0,119.6 guide=-22.49 atg=60.0/56.0/56.0 pure=-8.32/-8.32 yaw=1349 cmd=1149 actual=2112 signed=0 rps=3425/6575:5310/7660 duty=5/17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=9/0 centerNum=9/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=9/15 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.76@101,98 dx=17.0 idx=0/8 dist=32/32 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-21.45@101,99 dx=17.1 idx=0/14 dist=28/28 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=75,98 r=-1,-1
ATGSeedDiag: seed=1@58,108/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=7(6.7) imip=0/8 pass=10110 acc=-1 ipm=75.1,100.1 inv=62.4,68.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=870 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/0 raw=14/0 sel=2/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/56.0/56.0 pure=-8.32/-8.32 yaw=0 cmd=0 actual=2082 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/0 centerNum=2/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@61,106/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T00:47:38+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive22
```
