# drive49

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive49-front_car_circle_drive49.log
- remote_log: /tmp/front_car_circle_drive49.log
- started_at: 2026-06-22T02:57:45+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive49 6
```

4109 /tmp/front_car_circle_drive49.log
frame=855 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=17/170 sel=2/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-9.97/-9.97 yaw=0 cmd=0 actual=1442 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@58,103/1@98,86 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=856 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/1 raw=170/170 sel=6/11 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=4.4/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(99,107) md=23/0/23 cxcy=84.0,119.6 guide=-22.78 atg=60.0/60.0/60.0 pure=-10.48/-10.48 yaw=1367 cmd=1263 actual=1470 signed=0 rps=3269/6731:4747/6266 duty=6/19
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/1 centerNum=6/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-22.65@99,106 dx=15.4 idx=0/5 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-23.22@99,107 dx=15.4 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=73,104 r=-1,-1
ATGSeedDiag: seed=1@52,105/1@149,87 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(4.4) imip=0/5 pass=10110 acc=-1 ipm=73.3,106.1 inv=58.0,78.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=857 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=6/1 raw=170/170 sel=6/11 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.6/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(99,107) md=22/0/22 cxcy=84.0,119.6 guide=-22.78 atg=60.0/60.0/60.0 pure=-10.16/-10.16 yaw=1367 cmd=1333 actual=1400 signed=0 rps=3173/6827:5869/7661 duty=4/18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=6/1 centerNum=6/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=6/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.98@99,106 dx=14.8 idx=0/5 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-22.38@99,107 dx=14.8 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=73,105 r=-1,-1
ATGSeedDiag: seed=1@51,108/1@96,88 begin=7,108 block=5 clip=8
ATGLptDiag: best=4(7.6) imip=0/5 pass=10110 acc=-1 ipm=72.9,107.0 inv=56.9,80.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=858 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/0 raw=23/0 sel=3/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.4/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/60.0/60.0 pure=-10.16/-10.16 yaw=0 cmd=0 actual=1465 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/0 centerNum=3/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@57,97/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(17.4) imip=0/2 pass=10110 acc=-1 ipm=72.7,115.4 inv=53.0,102.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=859 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/1 raw=170/170 sel=5/10 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.6/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(98,106) md=20/0/20 cxcy=84.0,119.6 guide=-20.86 atg=60.0/53.0/53.0 pure=-9.63/-9.63 yaw=1252 cmd=1055 actual=1449 signed=0 rps=3555/6445:5310/6805 duty=6/17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/1 centerNum=5/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/10 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.71@98,105 dx=13.7 idx=0/4 dist=22/22 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-20.92@98,106 dx=13.9 idx=0/9 dist=18/18 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=72,104 r=-1,-1
ATGSeedDiag: seed=1@51,100/1@97,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=3(9.6) imip=0/4 pass=10110 acc=-1 ipm=71.9,106.8 inv=55.0,80.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=860 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=5/1 raw=170/170 sel=5/11 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.7/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(97,103) md=22/0/22 cxcy=84.0,119.6 guide=-18.11 atg=60.0/41.0/41.0 pure=-7.91/-7.91 yaw=1087 cmd=887 actual=1389 signed=0 rps=3785/6215:4974/6360 duty=7/17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=5/1 centerNum=5/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=5/11 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.93@97,103 dx=13.0 idx=0/4 dist=23/23 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-18.07@97,103 dx=13.0 idx=0/10 dist=20/20 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=71,104 r=-1,-1
ATGSeedDiag: seed=1@51,98/1@96,93 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(9.7) imip=0/4 pass=10111 acc=-1 ipm=71.5,108.4 inv=53.7,83.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=861 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/1 raw=170/170 sel=4/9 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.3/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(96,107) md=17/0/17 cxcy=84.0,119.6 guide=-18.56 atg=60.0/43.0/43.0 pure=-9.09/-9.09 yaw=1114 cmd=914 actual=1358 signed=0 rps=3748/6252:5005/6262 duty=7/17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/1 centerNum=4/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/9 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.28@96,106 dx=12.0 idx=0/3 dist=19/19 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-18.90@96,107 dx=12.2 idx=0/8 dist=16/16 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=70,108 r=-1,-1
ATGSeedDiag: seed=1@48,103/1@95,96 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(9.3) imip=0/3 pass=10111 acc=-1 ipm=70.4,110.1 inv=50.7,87.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=862 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/1 raw=170/170 sel=3/8 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=8.6/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(96,109) md=15/0/15 cxcy=84.0,119.6 guide=-19.58 atg=60.0/47.0/47.0 pure=-9.92/-9.92 yaw=1175 cmd=997 actual=1353 signed=0 rps=3634/6366:5035/6168 duty=6/18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/1 centerNum=3/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/8 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.32@96,109 dx=11.9 idx=0/2 dist=17/17 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-19.67@96,109 dx=11.9 idx=0/7 dist=14/14 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=70,109 r=-1,-1
ATGSeedDiag: seed=1@47,101/1@146,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(8.6) imip=0/2 pass=10111 acc=-1 ipm=70.0,111.7 inv=49.1,91.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=863 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/1 raw=170/170 sel=4/9 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=19.5/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(95,106) md=17/0/17 cxcy=84.0,119.6 guide=-16.66 atg=60.0/34.0/34.0 pure=-7.89/-7.89 yaw=1000 cmd=800 actual=1363 signed=0 rps=3904/6096:4634/5674 duty=8/17
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/1 centerNum=4/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/9 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-15.27@94,105 dx=10.4 idx=0/3 dist=19/19 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-16.53@95,106 dx=11.0 idx=0/8 dist=16/16 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,108 r=-1,-1
ATGSeedDiag: seed=1@46,104/1@146,93 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(19.5) imip=0/3 pass=10111 acc=-1 ipm=69.5,110.4 inv=48.8,88.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=864 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=3/1 raw=170/170 sel=3/7 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.8/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(95,111) md=13/0/13 cxcy=84.0,119.6 guide=-19.11 atg=60.0/45.0/45.0 pure=-10.45/-10.45 yaw=1147 cmd=947 actual=1386 signed=0 rps=3702/6298:4636/5919 duty=7/18
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=3/1 centerNum=3/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/7 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.21@95,109 dx=11.0 idx=0/2 dist=16/16 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-19.63@95,111 dx=11.2 idx=0/6 dist=12/12 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=69,111 r=-1,-1
ATGSeedDiag: seed=1@45,105/1@92,101 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(3.8) imip=0/2 pass=10111 acc=-1 ipm=69.2,113.0 inv=46.5,95.3 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=865 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=4/1 raw=31/170 sel=4/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.1/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=60.0/45.0/45.0 pure=-10.45/-10.45 yaw=0 cmd=0 actual=1433 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=4/1 centerNum=4/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=4/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@50,94/1@95,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=2(16.1) imip=0/3 pass=10110 acc=-1 ipm=69.8,116.7 inv=45.3,106.9 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=866 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=170/170 sel=2/8 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(92,106) md=14/0/14 cxcy=84.0,119.6 guide=-12.27 atg=48.0/19.0/19.0 pure=-6.09/-6.09 yaw=736 cmd=536 actual=1413 signed=0 rps=4265/5735:4913/6958 duty=9/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/8 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-13.16@93,104 dx=9.1 idx=0/1 dist=18/18 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-12.37@92,106 dx=8.2 idx=0/7 dist=14/14 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=68,109 r=-1,-1
ATGSeedDiag: seed=1@45,94/1@92,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=867 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=2/1 raw=170/170 sel=2/8 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(92,105) md=15/0/15 cxcy=84.0,119.6 guide=-11.95 atg=46.0/18.0/18.0 pure=-5.83/-5.83 yaw=717 cmd=517 actual=1357 signed=0 rps=4291/5709:4762/6395 duty=9/15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=2/1 centerNum=2/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=2/8 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.24@92,105 dx=8.3 idx=0/1 dist=17/17 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-11.84@92,105 dx=7.8 idx=0/7 dist=14/14 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=67,112 r=-1,-1
ATGSeedDiag: seed=1@43,101/1@94,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=868 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/1 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=46.0/18.0/18.0 pure=-5.83/-5.83 yaw=0 cmd=0 actual=1267 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@70,97/1@146,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=870 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/1 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=46.0/18.0/18.0 pure=-5.83/-5.83 yaw=0 cmd=0 actual=1073 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@67,102/1@105,97 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=871 line=0 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=1/1 raw=170/2 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=46.0/18.0/18.0 pure=-5.83/-5.83 yaw=0 cmd=0 actual=1019 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=1/1 centerNum=1/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=1@66,104/1@155,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0

- stopped_at: 2026-06-22T02:57:58+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive49
```
