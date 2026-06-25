# drive28

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive28-front_car_circle_drive28.log
- remote_log: /tmp/front_car_circle_drive28.log
- started_at: 2026-06-22T01:26:41+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive28 6
```

4409 /tmp/front_car_circle_drive28.log
ATGSeedDiag: seed=1@21,108/1@153,94 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(76.8) imip=15/35 pass=11111 acc=25 ipm=55.0,60.2 inv=48.5,33.6 | 23(62.3) imip=13/33 pass=11111 acc=23 ipm=106.5,67.5 inv=95.9,37.1
frame=868 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=45/50 raw=121/138 sel=45/72 far=0/0 far_raw=0/0 l=1@25/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=79.5/53.8/0.0/0.0 dist=0 m0=(84,119) ml=(79,86) md=33/1/160 cxcy=84.0,119.6 guide=5.45 atg=-3.0/-57.0/-60.0 pure=0.69/3.45 yaw=-139 cmd=-175 actual=-103 signed=0 rps=5240/4760:4387/4691 duty=13/13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@25/0@-1 nearNum=45/50 centerNum=45/50 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/72 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.51@78,89 dx=-6.1 idx=0/12 dist=33/168 right=1:7.35@77,84 dx=-7.5 idx=6/15 dist=34/148 sel=1:4.85@79,84 dx=-5.0 idx=0/16 dist=32/142 edge=1:3.40@80.0,75.0 dx=-4.0 width=55.3 l=53,81 r=107,69
CxScan: raw_ref=80.0 edge=80.0,75.0 best_raw_x=70 best_err=0.16 best_cxcy=80.2,119.5 scan=0:-21.6,10:-18.7,20:-15.7,30:-12.6,40:-9.5,50:-6.3,60:-3.1,70:0.2,80:3.4,90:6.6,100:9.8,110:12.9,120:15.9,130:18.8,140:21.7
ATGSeedDiag: seed=1@20,108/1@155,96 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(79.5) imip=15/35 pass=11111 acc=25 ipm=54.9,60.1 inv=48.5,33.6 | 23(53.8) imip=13/33 pass=10111 acc=-1 ipm=107.3,68.6 inv=97.1,37.8
frame=869 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=45/49 raw=120/139 sel=45/73 far=0/0 far_raw=0/0 l=1@25/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=75.9/58.8/0.0/0.0 dist=0 m0=(84,119) ml=(78,88) md=32/1/162 cxcy=84.0,119.6 guide=6.01 atg=-4.0/-58.0/-60.0 pure=0.79/3.43 yaw=-360 cmd=-560 actual=-118 signed=0 rps=5768/4232:5016/5138 duty=14/11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@25/0@-1 nearNum=45/49 centerNum=45/49 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=45/73 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:7.17@77,91 dx=-6.5 idx=0/11 dist=32/169 right=1:7.22@77,85 dx=-7.3 idx=6/15 dist=33/146 sel=1:5.37@78,84 dx=-5.6 idx=0/16 dist=32/144 edge=1:3.40@80.0,75.0 dx=-4.0 width=55.3 l=53,81 r=107,69
CxScan: raw_ref=80.0 edge=80.0,75.0 best_raw_x=70 best_err=0.16 best_cxcy=80.2,119.5 scan=0:-21.6,10:-18.7,20:-15.7,30:-12.6,40:-9.5,50:-6.3,60:-3.1,70:0.2,80:3.4,90:6.6,100:9.8,110:12.9,120:15.9,130:18.8,140:21.7
ATGSeedDiag: seed=1@19,108/1@155,97 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(75.9) imip=15/35 pass=11111 acc=25 ipm=53.8,60.1 inv=47.5,33.6 | 24(58.8) imip=14/34 pass=10111 acc=-1 ipm=108.9,66.9 inv=98.1,36.8
frame=870 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=24/24 raw=121/139 sel=24/30 far=0/0 far_raw=0/0 l=1@26/1@24 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=79.4/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(78,86) md=33/1/65 cxcy=84.0,119.6 guide=6.47 atg=-3.0/-1.0/-1.0 pure=0.76/0.76 yaw=-388 cmd=-588 actual=-157 signed=0 rps=5806/4194:5153/5010 duty=14/11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@26/1@24 nearNum=24/24 centerNum=24/24 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=24/30 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:7.41@77,89 dx=-7.0 idx=0/12 dist=33/69 right=1:7.92@77,89 dx=-7.5 idx=5/14 dist=31/76 sel=1:5.67@78,84 dx=-5.9 idx=0/16 dist=32/58 edge=1:3.79@79.5,74.5 dx=-4.5 width=56.5 l=52,81 r=107,68
CxScan: raw_ref=80.0 edge=79.5,74.5 best_raw_x=70 best_err=0.58 best_cxcy=80.2,119.5 scan=0:-21.1,10:-18.2,20:-15.2,30:-12.2,40:-9.0,50:-5.9,60:-2.6,70:0.6,80:3.8,90:7.0,100:10.1,110:13.2,120:16.2,130:19.1,140:21.9
ATGSeedDiag: seed=1@18,108/1@154,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=26(79.4) imip=16/36 pass=11111 acc=26 ipm=53.3,58.0 inv=47.6,32.6 | 24(63.2) imip=14/34 pass=11111 acc=24 ipm=108.8,66.2 inv=97.7,36.4
frame=872 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=23/23 raw=120/137 sel=23/29 far=0/0 far_raw=0/0 l=1@25/1@23 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=74.9/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(77,88) md=32/1/64 cxcy=84.0,119.6 guide=6.71 atg=-3.0/-1.0/-1.0 pure=0.79/0.79 yaw=-402 cmd=-528 actual=-276 signed=0 rps=5724/4276:5484/4766 duty=13/11
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@25/1@23 nearNum=23/23 centerNum=23/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=23/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:7.28@77,89 dx=-6.8 idx=0/12 dist=32/66 right=1:7.26@77,87 dx=-7.1 idx=5/14 dist=32/72 sel=1:5.69@78,84 dx=-5.9 idx=0/16 dist=32/56 edge=1:3.82@79.5,75.0 dx=-4.5 width=55.9 l=52,80 r=107,70
CxScan: raw_ref=80.0 edge=79.5,75.0 best_raw_x=70 best_err=0.58 best_cxcy=80.2,119.5 scan=0:-21.2,10:-18.3,20:-15.3,30:-12.2,40:-9.1,50:-5.9,60:-2.7,70:0.6,80:3.8,90:7.0,100:10.2,110:13.3,120:16.3,130:19.2,140:22.0
ATGSeedDiag: seed=1@16,108/1@153,100 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(74.9) imip=15/35 pass=11111 acc=25 ipm=53.5,59.9 inv=47.3,33.5 | 23(61.4) imip=13/33 pass=11111 acc=23 ipm=108.7,68.3 inv=98.3,37.6
frame=873 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=23/23 raw=120/139 sel=23/29 far=0/0 far_raw=0/0 l=1@25/1@23 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=80.6/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(78,86) md=33/1/63 cxcy=84.0,119.6 guide=5.85 atg=-3.0/-1.0/-1.0 pure=0.73/0.73 yaw=-149 cmd=51 actual=-398 signed=0 rps=4930/5070:5779/4764 duty=10/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@25/1@23 nearNum=23/23 centerNum=23/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=23/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.84@78,89 dx=-6.4 idx=0/12 dist=33/68 right=1:7.32@77,88 dx=-7.0 idx=5/14 dist=32/72 sel=1:5.21@79,84 dx=-5.4 idx=0/16 dist=32/56 edge=1:3.42@80.0,75.5 dx=-4.0 width=54.7 l=53,80 r=107,71
CxScan: raw_ref=80.0 edge=80.0,75.5 best_raw_x=70 best_err=0.16 best_cxcy=80.2,119.5 scan=0:-21.7,10:-18.8,20:-15.8,30:-12.7,40:-9.6,50:-6.4,60:-3.1,70:0.2,80:3.4,90:6.7,100:9.9,110:13.0,120:16.0,130:19.0,140:21.8
ATGSeedDiag: seed=1@16,107/1@155,102 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(80.6) imip=15/35 pass=11111 acc=25 ipm=53.4,59.8 inv=47.2,33.4 | 23(62.0) imip=13/33 pass=11111 acc=23 ipm=108.2,68.9 inv=98.0,37.9
frame=874 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=22/23 raw=119/138 sel=22/28 far=0/0 far_raw=0/0 l=1@24/1@23 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=80.1/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(79,86) md=33/1/61 cxcy=84.0,119.6 guide=5.05 atg=-3.0/-1.0/-1.0 pure=0.71/0.71 yaw=-129 cmd=71 actual=-499 signed=0 rps=4902/5098:5804/4732 duty=10/15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@24/1@23 nearNum=22/23 centerNum=22/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=22/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:6.37@78,90 dx=-5.9 idx=0/12 dist=33/65 right=1:6.81@77,87 dx=-6.6 idx=5/14 dist=32/72 sel=1:4.63@79,84 dx=-4.8 idx=0/16 dist=32/54 edge=1:2.58@81.0,75.5 dx=-3.0 width=54.7 l=54,80 r=108,71
CxScan: raw_ref=80.0 edge=81.0,75.5 best_raw_x=70 best_err=-0.69 best_cxcy=80.2,119.5 scan=0:-22.5,10:-19.6,20:-16.6,30:-13.5,40:-10.4,50:-7.2,60:-4.0,70:-0.7,80:2.6,90:5.8,100:9.0,110:12.2,120:15.2,130:18.2,140:21.1
ATGSeedDiag: seed=1@15,108/1@155,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=24(80.1) imip=14/34 pass=11111 acc=24 ipm=54.3,62.0 inv=47.4,34.5 | 23(62.0) imip=13/33 pass=11111 acc=23 ipm=109.2,69.4 inv=99.2,38.2
frame=875 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=42/45 raw=119/136 sel=42/68 far=0/0 far_raw=0/0 l=1@23/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=79.5/59.9/0.0/0.0 dist=0 m0=(84,119) ml=(80,86) md=33/1/150 cxcy=84.0,119.6 guide=4.45 atg=-3.0/-60.0/-60.0 pure=0.72/3.84 yaw=-113 cmd=87 actual=-565 signed=0 rps=4881/5119:5411/4617 duty=10/15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@23/0@-1 nearNum=42/45 centerNum=42/45 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=42/68 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:5.60@79,90 dx=-5.1 idx=0/12 dist=32/159 right=1:7.64@77,90 dx=-7.0 idx=4/13 dist=31/142 sel=1:3.84@80,84 dx=-4.0 idx=0/16 dist=32/134 edge=1:1.72@82.0,75.5 dx=-2.0 width=54.7 l=55,80 r=109,71
CxScan: raw_ref=80.0 edge=82.0,75.5 best_raw_x=75 best_err=0.09 best_cxcy=82.1,119.5 scan=0:-23.2,10:-20.3,20:-17.4,30:-14.3,40:-11.2,50:-8.0,60:-4.8,70:-1.5,80:1.7,90:5.0,100:8.2,110:11.4,120:14.4,130:17.4,140:20.3
ATGSeedDiag: seed=1@15,108/1@154,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(79.5) imip=13/33 pass=11111 acc=23 ipm=56.1,64.1 inv=48.5,35.6 | 22(59.9) imip=12/32 pass=10111 acc=-1 ipm=108.9,71.5 inv=99.6,39.5
frame=876 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=21/22 raw=119/138 sel=21/27 far=0/0 far_raw=0/0 l=1@23/1@22 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=83.9/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(80,86) md=33/1/59 cxcy=84.0,119.6 guide=3.83 atg=-1.0/0.0/0.0 pure=0.50/0.50 yaw=-98 cmd=102 actual=-577 signed=0 rps=4860/5140:5376/5040 duty=10/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@23/1@22 nearNum=21/22 centerNum=21/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/27 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.97@79,90 dx=-4.6 idx=0/12 dist=32/62 right=1:7.27@77,91 dx=-6.6 idx=4/13 dist=31/71 sel=1:3.24@81,83 dx=-3.4 idx=0/16 dist=32/52 edge=1:2.18@81.5,76.5 dx=-2.5 width=53.5 l=55,80 r=108,73
CxScan: raw_ref=80.0 edge=81.5,76.5 best_raw_x=75 best_err=0.53 best_cxcy=82.1,119.5 scan=0:-23.1,10:-20.2,20:-17.2,30:-14.2,40:-11.0,50:-7.7,60:-4.4,70:-1.1,80:2.2,90:5.5,100:8.7,110:11.9,120:15.0,130:18.1,140:21.0
ATGSeedDiag: seed=1@15,108/1@155,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(83.9) imip=13/33 pass=11111 acc=23 ipm=56.1,64.2 inv=48.6,35.6 | 22(62.0) imip=12/32 pass=11111 acc=22 ipm=108.9,71.6 inv=99.6,39.5
frame=877 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=21/22 raw=119/136 sel=21/27 far=0/0 far_raw=0/0 l=1@23/1@22 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=85.0/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(81,86) md=33/1/59 cxcy=84.0,119.6 guide=3.43 atg=-1.0/0.0/0.0 pure=0.44/0.44 yaw=-88 cmd=112 actual=-546 signed=0 rps=4846/5154:5034/5111 duty=11/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@23/1@22 nearNum=21/22 centerNum=21/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/27 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.59@80,90 dx=-4.2 idx=0/12 dist=32/63 right=1:6.39@78,90 dx=-5.9 idx=4/13 dist=31/70 sel=1:2.85@81,83 dx=-3.0 idx=0/16 dist=32/52 edge=1:1.75@82.0,76.5 dx=-2.0 width=52.5 l=56,80 r=108,73
CxScan: raw_ref=80.0 edge=82.0,76.5 best_raw_x=75 best_err=0.09 best_cxcy=82.1,119.5 scan=0:-23.5,10:-20.6,20:-17.6,30:-14.6,40:-11.4,50:-8.2,60:-4.9,70:-1.6,80:1.8,90:5.1,100:8.3,110:11.5,120:14.6,130:17.7,140:20.6
ATGSeedDiag: seed=1@15,107/1@155,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(85.0) imip=13/33 pass=11111 acc=23 ipm=56.2,64.4 inv=48.5,35.7 | 22(62.6) imip=12/32 pass=11111 acc=22 ipm=109.8,71.6 inv=100.5,39.5
frame=878 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=21/22 raw=120/135 sel=21/26 far=0/0 far_raw=0/0 l=1@23/1@22 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=84.2/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(81,86) md=33/1/56 cxcy=84.0,119.6 guide=3.03 atg=0.0/0.0/0.0 pure=0.35/0.35 yaw=-77 cmd=123 actual=-487 signed=0 rps=4832/5168:5187/5561 duty=11/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@23/1@22 nearNum=21/22 centerNum=21/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/26 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.67@81,88 dx=-3.5 idx=0/13 dist=33/61 right=1:5.38@79,89 dx=-5.1 idx=4/13 dist=31/71 sel=1:2.48@81,83 dx=-2.6 idx=0/16 dist=32/50 edge=1:0.89@83.0,76.5 dx=-1.0 width=54.5 l=56,80 r=110,73
CxScan: raw_ref=80.0 edge=83.0,76.5 best_raw_x=75 best_err=-0.77 best_cxcy=82.1,119.5 scan=0:-24.2,10:-21.4,20:-18.4,30:-15.4,40:-12.2,50:-9.0,60:-5.7,70:-2.4,80:0.9,90:4.2,100:7.5,110:10.7,120:13.8,130:16.9,140:19.9
ATGSeedDiag: seed=1@14,108/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(84.2) imip=13/33 pass=11111 acc=23 ipm=57.1,64.1 inv=49.4,35.6 | 22(61.8) imip=12/32 pass=11111 acc=22 ipm=111.0,71.5 inv=101.7,39.5
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=42/44 raw=120/132 sel=42/69 far=0/0 far_raw=0/0 l=1@23/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=84.2/59.9/0.0/0.0 dist=0 m0=(84,119) ml=(81,86) md=33/1/152 cxcy=84.0,119.6 guide=3.26 atg=-2.0/-60.0/-60.0 pure=0.57/3.82 yaw=-83 cmd=117 actual=-403 signed=0 rps=4840/5160:4981/5303 duty=11/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@23/0@-1 nearNum=42/44 centerNum=42/44 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=42/69 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.47@81,88 dx=-3.3 idx=0/13 dist=34/159 right=1:4.15@80,87 dx=-4.0 idx=3/13 dist=34/141 sel=1:2.46@81,83 dx=-2.5 idx=0/16 dist=32/136 edge=1:0.45@83.5,76.5 dx=-0.5 width=55.4 l=56,80 r=111,73
CxScan: raw_ref=80.0 edge=83.5,76.5 best_raw_x=80 best_err=0.45 best_cxcy=84.0,119.6 scan=0:-24.6,10:-21.8,20:-18.8,30:-15.8,40:-12.6,50:-9.4,60:-6.2,70:-2.9,80:0.5,90:3.8,100:7.0,110:10.3,120:13.4,130:16.5,140:19.5
ATGSeedDiag: seed=1@14,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(84.2) imip=13/33 pass=11111 acc=23 ipm=56.9,64.0 inv=49.3,35.5 | 22(59.9) imip=12/32 pass=10111 acc=-1 ipm=112.5,71.2 inv=103.1,39.3
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=21/22 raw=120/131 sel=21/27 far=0/0 far_raw=0/0 l=1@23/1@22 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=86.3/23.0/0.0/0.0 dist=0 m0=(84,119) ml=(81,86) md=33/1/59 cxcy=84.0,119.6 guide=2.83 atg=0.0/0.0/0.0 pure=0.37/0.37 yaw=-72 cmd=128 actual=-307 signed=0 rps=4825/5175:5359/5581 duty=10/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@23/1@22 nearNum=21/22 centerNum=21/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/27 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:3.27@81,88 dx=-3.1 idx=0/13 dist=34/62 right=1:3.57@80,86 dx=-3.5 idx=3/13 dist=34/72 sel=1:2.30@82,83 dx=-2.4 idx=0/16 dist=32/52 edge=1:0.45@83.5,76.0 dx=-0.5 width=55.6 l=56,80 r=111,72
CxScan: raw_ref=80.0 edge=83.5,76.0 best_raw_x=80 best_err=0.45 best_cxcy=84.0,119.6 scan=0:-24.4,10:-21.6,20:-18.7,30:-15.7,40:-12.5,50:-9.4,60:-6.1,70:-2.8,80:0.5,90:3.7,100:7.0,110:10.2,120:13.3,130:16.4,140:19.3
ATGSeedDiag: seed=1@14,108/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(86.3) imip=13/33 pass=11111 acc=23 ipm=56.9,64.0 inv=49.3,35.5 | 22(62.5) imip=12/32 pass=11111 acc=22 ipm=112.9,71.0 inv=103.5,39.2
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=0 speed=0 near=41/42 raw=119/127 sel=41/67 far=0/0 far_raw=0/0 l=1@22/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=81.7/60.0/0.0/0.0 dist=0 m0=(84,119) ml=(82,86) md=33/1/148 cxcy=84.0,119.6 guide=2.43 atg=-2.0/-60.0/-60.0 pure=0.58/4.01 yaw=-62 cmd=114 actual=-238 signed=0 rps=4844/5156:5324/5341 duty=10/14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@22/0@-1 nearNum=41/42 centerNum=41/42 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=41/67 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:2.74@81,88 dx=-2.6 idx=0/13 dist=33/154 right=1:3.99@80,88 dx=-3.8 idx=2/12 dist=34/139 sel=1:1.94@82,83 dx=-2.0 idx=0/16 dist=32/132 edge=1:-0.84@85.0,76.5 dx=1.0 width=56.4 l=57,80 r=113,73
CxScan: raw_ref=80.0 edge=85.0,76.5 best_raw_x=85 best_err=0.81 best_cxcy=85.9,119.6 scan=0:-25.7,10:-22.9,20:-20.0,30:-17.0,40:-13.9,50:-10.7,60:-7.4,70:-4.2,80:-0.8,90:2.5,100:5.8,110:9.0,120:12.2,130:15.3,140:18.3
ATGSeedDiag: seed=1@13,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=22(81.7) imip=12/32 pass=11111 acc=22 ipm=57.8,66.2 inv=49.5,36.7 | 21(60.0) imip=11/31 pass=10111 acc=-1 ipm=112.9,72.7 inv=104.1,40.2

- stopped_at: 2026-06-22T01:26:54+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive28
```
