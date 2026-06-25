# drive54

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive54-front_car_circle_drive54.log
- remote_log: /tmp/front_car_circle_drive54.log
- started_at: 2026-06-22T03:32:47+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive54 6
```

3868 /tmp/front_car_circle_drive54.log
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/34 centerNum=0/34 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=34/58 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:16.39@70,96 dx=-13.7 idx=0/6 dist=33/134 sel=1:13.35@72,91 dx=-12.4 idx=0/16 dist=32/114 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,84
ATGSeedDiag: seed=0@-1,-1/1@118,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 8(43.7) imip=0/18 pass=10111 acc=-1 ipm=96.2,99.2 inv=95.3,66.4
frame=871 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/33 raw=0/106 sel=33/56 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/42.1/0.0/0.0 dist=0 m0=(84,119) ml=(72,92) md=33/1/122 cxcy=84.0,119.6 guide=12.44 atg=12.0/60.0/60.0 pure=-1.57/-5.63 yaw=-746 cmd=-546 actual=-1081 signed=0 rps=5749/4251:6931/6193 duty=11/9
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/33 centerNum=0/33 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=33/56 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:14.65@71,94 dx=-12.6 idx=0/6 dist=34/128 sel=1:11.80@73,90 dx=-11.0 idx=0/16 dist=32/110 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=115,85
ATGSeedDiag: seed=0@-1,-1/1@117,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 9(42.1) imip=0/19 pass=10111 acc=-1 ipm=98.3,96.9 inv=97.4,63.1
frame=872 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/32 raw=0/104 sel=32/54 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/41.2/0.0/0.0 dist=0 m0=(84,119) ml=(73,91) md=33/1/118 cxcy=84.0,119.6 guide=11.16 atg=19.0/60.0/60.0 pure=-1.95/-5.85 yaw=-670 cmd=-470 actual=-1040 signed=0 rps=5644/4356:6897/5918 duty=11/10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/32 centerNum=0/32 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=32/54 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:14.67@72,96 dx=-12.2 idx=0/5 dist=31/125 sel=1:10.46@74,89 dx=-9.9 idx=0/16 dist=32/106 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=114,86
ATGSeedDiag: seed=0@-1,-1/1@116,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 10(41.2) imip=0/20 pass=10111 acc=-1 ipm=100.8,95.0 inv=100.1,60.5
frame=873 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=73/31 raw=158/100 sel=31/52 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.3/35.9/0.0/0.0 dist=0 m0=(84,119) ml=(75,90) md=33/1/115 cxcy=84.0,119.6 guide=9.91 atg=37.0/60.0/60.0 pure=-2.66/-6.26 yaw=-595 cmd=-395 actual=-1025 signed=0 rps=5541/4459:7385/6117 duty=10/10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=73/31 centerNum=73/31 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=31/52 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-0.31@84,89 dx=0.3 idx=0/20 dist=33/127 right=1:11.72@74,93 dx=-10.2 idx=0/5 dist=31/119 sel=1:7.92@76,88 dx=-7.7 idx=0/16 dist=32/102 edge=1:-4.18@88.5,81.5 dx=4.5 width=58.5 l=60,75 r=117,88
CxScan: raw_ref=80.0 edge=88.5,81.5 best_raw_x=90 best_err=-0.60 best_cxcy=87.9,119.6 scan=0:-30.0,10:-27.2,20:-24.2,30:-21.2,40:-18.0,50:-14.6,60:-11.2,70:-7.7,80:-4.2,90:-0.6,100:3.0,110:6.5,120:10.0,130:13.4,140:16.8
ATGSeedDiag: seed=1@4,87/1@115,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=9(18.3) imip=0/19 pass=10110 acc=-1 ipm=50.9,88.4 inv=32.9,53.5 | 7(35.9) imip=0/17 pass=10111 acc=-1 ipm=98.7,101.1 inv=100.3,69.3
frame=874 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=72/30 raw=157/97 sel=30/51 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=23.7/34.7/0.0/0.0 dist=0 m0=(84,119) ml=(76,89) md=33/1/111 cxcy=84.0,119.6 guide=7.88 atg=48.0/60.0/60.0 pure=-3.01/-6.50 yaw=-473 cmd=-273 actual=-1016 signed=0 rps=5374/4626:7507/6248 duty=9/10
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=72/30 centerNum=72/30 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=30/51 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-1.67@86,89 dx=1.6 idx=0/20 dist=33/123 right=1:9.67@75,92 dx=-8.7 idx=0/5 dist=32/115 sel=1:6.53@78,87 dx=-6.4 idx=0/16 dist=32/100 edge=1:-4.72@89.0,82.5 dx=5.0 width=55.5 l=62,76 r=116,89
CxScan: raw_ref=80.0 edge=89.0,82.5 best_raw_x=95 best_err=0.74 best_cxcy=89.8,119.6 scan=0:-30.7,10:-27.9,20:-25.0,30:-21.9,40:-18.7,50:-15.3,60:-11.9,70:-8.3,80:-4.7,90:-1.1,100:2.6,110:6.2,120:9.7,130:13.2,140:16.6
ATGSeedDiag: seed=1@4,88/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=61(23.7) imip=51/71 pass=10100 acc=-1 ipm=157.9,48.6 inv=131.2,28.2 | 8(34.7) imip=0/18 pass=10111 acc=-1 ipm=101.1,99.0 inv=102.9,66.0
frame=875 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=71/29 raw=157/95 sel=29/49 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=19.8/33.0/0.0/0.0 dist=0 m0=(84,119) ml=(78,89) md=32/1/106 cxcy=84.0,119.6 guide=5.60 atg=60.0/60.0/60.0 pure=-3.37/-6.63 yaw=-143 cmd=57 actual=-994 signed=0 rps=4922/5078:7022/6094 duty=8/12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=71/29 centerNum=71/29 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=29/49 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-2.25@86,91 dx=2.0 idx=0/20 dist=32/121 right=1:5.85@78,88 dx=-5.6 idx=0/6 dist=34/108 sel=1:5.09@79,87 dx=-5.0 idx=0/16 dist=32/96 edge=1:-5.76@90.0,83.5 dx=6.0 width=57.5 l=62,77 r=118,90
CxScan: raw_ref=80.0 edge=90.0,83.5 best_raw_x=95 best_err=-0.22 best_cxcy=89.8,119.6 scan=0:-31.9,10:-29.1,20:-26.2,30:-23.1,40:-19.8,50:-16.5,60:-13.0,70:-9.4,80:-5.8,90:-2.1,100:1.6,110:5.3,120:8.9,130:12.5,140:16.0
ATGSeedDiag: seed=1@4,89/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(19.8) imip=0/20 pass=10110 acc=-1 ipm=53.6,87.4 inv=36.9,52.5 | 8(33.0) imip=0/18 pass=10111 acc=-1 ipm=102.0,99.4 inv=104.5,66.6
frame=876 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/27 raw=157/92 sel=27/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.0/32.5/0.0/0.0 dist=0 m0=(84,119) ml=(79,88) md=32/1/99 cxcy=84.0,119.6 guide=4.32 atg=60.0/60.0/60.0 pure=-3.68/-6.49 yaw=-110 cmd=90 actual=-935 signed=0 rps=4877/5123:6960/6541 duty=8/12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/27 centerNum=70/27 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=27/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-2.70@86,91 dx=2.4 idx=0/20 dist=33/124 right=1:6.00@78,89 dx=-5.6 idx=0/5 dist=32/102 sel=1:3.76@80,86 dx=-3.7 idx=0/16 dist=32/90 edge=1:-6.77@91.0,84.0 dx=7.0 width=57.7 l=63,77 r=119,91
CxScan: raw_ref=80.0 edge=91.0,84.0 best_raw_x=100 best_err=0.67 best_cxcy=91.7,119.6 scan=0:-32.8,10:-30.0,20:-27.1,30:-24.1,40:-20.8,50:-17.5,60:-14.0,70:-10.4,80:-6.8,90:-3.1,100:0.7,110:4.4,120:8.1,130:11.7,140:15.2
ATGSeedDiag: seed=1@4,89/1@113,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=67(17.0) imip=57/69 pass=10100 acc=-1 ipm=171.5,57.4 inv=148.4,31.7 | 8(32.5) imip=0/18 pass=10111 acc=-1 ipm=103.2,99.5 inv=106.4,66.7
frame=877 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/27 raw=157/89 sel=27/46 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=24.1/30.5/0.0/0.0 dist=0 m0=(84,119) ml=(82,86) md=34/1/99 cxcy=84.0,119.6 guide=2.94 atg=60.0/60.0/60.0 pure=-4.02/-6.68 yaw=-75 cmd=125 actual=-842 signed=0 rps=4829/5171:6477/6499 duty=9/12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/27 centerNum=70/27 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=27/46 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-3.46@87,91 dx=3.1 idx=0/20 dist=33/120 right=1:4.43@80,88 dx=-4.2 idx=0/5 dist=33/102 sel=1:2.35@82,86 dx=-2.3 idx=0/16 dist=32/90 edge=1:-7.73@92.0,84.0 dx=8.0 width=59.7 l=63,77 r=121,91
CxScan: raw_ref=80.0 edge=92.0,84.0 best_raw_x=100 best_err=-0.30 best_cxcy=91.7,119.6 scan=0:-33.5,10:-30.8,20:-27.9,30:-24.9,40:-21.7,50:-18.4,60:-14.9,70:-11.4,80:-7.7,90:-4.0,100:-0.3,110:3.4,120:7.1,130:10.7,140:14.3
ATGSeedDiag: seed=1@4,90/1@113,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=59(24.1) imip=49/69 pass=10100 acc=-1 ipm=155.9,50.8 inv=131.0,29.1 | 8(30.5) imip=0/18 pass=10111 acc=-1 ipm=104.2,99.8 inv=108.3,67.2
frame=878 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=70/26 raw=157/87 sel=26/44 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.4/30.4/0.0/0.0 dist=0 m0=(84,119) ml=(82,88) md=32/1/95 cxcy=84.0,119.6 guide=1.73 atg=60.0/60.0/60.0 pure=-4.32/-6.64 yaw=-44 cmd=156 actual=-747 signed=0 rps=4786/5214:6718/6896 duty=8/12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=70/26 centerNum=70/26 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=26/44 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-2.14@86,93 dx=1.9 idx=0/19 dist=32/124 right=1:2.70@81,88 dx=-2.6 idx=0/5 dist=33/98 sel=1:1.06@83,86 dx=-1.1 idx=0/16 dist=32/86 edge=1:-8.83@93.0,85.0 dx=9.0 width=59.7 l=64,78 r=122,92
CxScan: raw_ref=80.0 edge=93.0,85.0 best_raw_x=105 best_err=0.60 best_cxcy=93.6,119.6 scan=0:-34.6,10:-31.9,20:-29.1,30:-26.1,40:-22.9,50:-19.6,60:-16.1,70:-12.5,80:-8.8,90:-5.1,100:-1.3,110:2.5,120:6.3,130:10.0,140:13.6
ATGSeedDiag: seed=1@4,91/1@113,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(17.4) imip=0/20 pass=10110 acc=-1 ipm=55.1,88.5 inv=38.2,53.6 | 10(30.4) imip=0/20 pass=10111 acc=-1 ipm=109.0,97.3 inv=113.6,63.5
frame=879 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=69/25 raw=157/83 sel=25/43 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=18.8/29.3/0.0/0.0 dist=0 m0=(84,119) ml=(83,87) md=33/1/93 cxcy=84.0,119.6 guide=1.06 atg=60.0/60.0/60.0 pure=-4.64/-6.72 yaw=-27 cmd=173 actual=-667 signed=0 rps=4763/5237:6506/6622 duty=8/12
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=69/25 centerNum=69/25 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=25/43 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-4.63@88,93 dx=4.1 idx=0/20 dist=33/121 right=1:0.82@83,87 dx=-0.8 idx=0/5 dist=34/95 sel=1:-0.38@84,85 dx=0.4 idx=0/16 dist=32/84 edge=1:-9.88@94.0,85.5 dx=10.0 width=59.9 l=65,78 r=123,93
CxScan: raw_ref=80.0 edge=94.0,85.5 best_raw_x=105 best_err=-0.40 best_cxcy=93.6,119.6 scan=0:-35.5,10:-32.9,20:-30.0,30:-27.1,40:-23.9,50:-20.6,60:-17.1,70:-13.6,80:-9.9,90:-6.1,100:-2.3,110:1.5,120:5.3,130:9.1,140:12.7
ATGSeedDiag: seed=1@4,92/1@113,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=59(18.8) imip=49/68 pass=10100 acc=-1 ipm=156.7,51.0 inv=131.7,29.1 | 10(29.3) imip=0/20 pass=10111 acc=-1 ipm=110.3,97.7 inv=116.0,64.0
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=68/24 raw=157/81 sel=68/54 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=14.7/32.3/0.0/0.0 dist=0 m0=(84,119) ml=(83,98) md=33/1/116 cxcy=84.0,119.6 guide=1.31 atg=60.0/60.0/60.0 pure=-6.57/-8.44 yaw=-34 cmd=166 actual=-569 signed=0 rps=4772/5228:6945/6897 duty=8/12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=68/24 centerNum=68/24 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=68/54 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.57@81,100 dx=-3.4 idx=0/13 dist=33/132 right=1:-13.52@100,75 dx=16.4 idx=0/11 dist=34/72 sel=1:-0.84@85,96 dx=0.7 idx=0/16 dist=32/106 edge=1:-10.55@94.5,86.5 dx=10.5 width=60.9 l=65,79 r=124,94
CxScan: raw_ref=80.0 edge=94.5,86.5 best_raw_x=105 best_err=-0.91 best_cxcy=93.6,119.6 scan=0:-36.3,10:-33.7,20:-30.9,30:-27.9,40:-24.7,50:-21.4,60:-17.9,70:-14.3,80:-10.5,90:-6.7,100:-2.9,110:1.0,120:4.9,130:8.7,140:12.5
ATGSeedDiag: seed=1@4,92/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=5(14.7) imip=0/15 pass=10110 acc=-1 ipm=50.5,99.3 inv=23.9,67.1 | 10(32.3) imip=0/20 pass=10111 acc=-1 ipm=111.2,98.5 inv=118.0,65.1
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=67/23 raw=156/79 sel=67/52 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.1/27.7/0.0/0.0 dist=0 m0=(84,119) ml=(86,97) md=33/1/112 cxcy=84.0,119.6 guide=-1.45 atg=60.0/60.0/60.0 pure=-7.25/-8.87 yaw=37 cmd=237 actual=-472 signed=0 rps=4675/5325:6809/6500 duty=8/13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/23 centerNum=67/23 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=67/52 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-1.61@85,97 dx=1.3 idx=2/17 dist=33/123 right=1:-15.12@102,75 dx=18.4 idx=0/11 dist=34/68 sel=1:-4.60@88,95 dx=3.8 idx=0/16 dist=32/102 edge=1:-11.63@95.5,87.0 dx=11.5 width=61.1 l=66,79 r=125,95
CxScan: raw_ref=80.0 edge=95.5,87.0 best_raw_x=110 best_err=0.02 best_cxcy=95.5,119.6 scan=0:-37.2,10:-34.6,20:-31.8,30:-28.9,40:-25.7,50:-22.4,60:-19.0,70:-15.4,80:-11.6,90:-7.8,100:-3.9,110:0.0,120:3.9,130:7.8,140:11.6
ATGSeedDiag: seed=1@4,92/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(16.1) imip=0/20 pass=10110 acc=-1 ipm=57.0,89.5 inv=40.2,54.5 | 10(27.7) imip=0/20 pass=10111 acc=-1 ipm=112.1,99.0 inv=119.9,65.9
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=65/22 raw=156/76 sel=65/50 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=16.2/27.2/0.0/0.0 dist=0 m0=(84,119) ml=(87,98) md=33/1/108 cxcy=84.0,119.6 guide=-4.58 atg=60.0/60.0/60.0 pure=-7.76/-9.27 yaw=117 cmd=317 actual=-376 signed=0 rps=4566/5434:7021/6424 duty=7/13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=65/22 centerNum=65/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=65/50 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-0.71@85,99 dx=0.5 idx=2/16 dist=32/123 right=1:-16.65@104,75 dx=20.3 idx=0/11 dist=34/64 sel=1:-5.58@89,96 dx=4.5 idx=0/16 dist=32/98 edge=1:-12.83@96.5,88.0 dx=12.5 width=61.1 l=67,80 r=126,96
CxScan: raw_ref=80.0 edge=96.5,88.0 best_raw_x=115 best_err=0.97 best_cxcy=97.4,119.7 scan=0:-38.4,10:-35.8,20:-33.0,30:-30.1,40:-27.0,50:-23.7,60:-20.2,70:-16.6,80:-12.8,90:-9.0,100:-5.0,110:-1.0,120:3.0,130:6.9,140:10.8
ATGSeedDiag: seed=1@4,93/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=8(16.2) imip=0/18 pass=10110 acc=-1 ipm=54.8,93.7 inv=34.7,59.4 | 10(27.2) imip=0/20 pass=10111 acc=-1 ipm=113.1,99.7 inv=122.0,66.8
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=64/21 raw=156/73 sel=64/48 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=17.2/39.2/0.0/0.0 dist=0 m0=(84,119) ml=(88,97) md=32/1/104 cxcy=84.0,119.6 guide=-6.61 atg=60.0/60.0/60.0 pure=-8.16/-9.50 yaw=396 cmd=596 actual=-295 signed=0 rps=4183/5817:7127/6508 duty=6/15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=64/21 centerNum=64/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=64/48 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-2.59@86,99 dx=2.0 idx=3/17 dist=33/115 right=1:-17.57@105,76 dx=21.3 idx=0/11 dist=33/60 sel=1:-7.82@90,96 dx=6.4 idx=0/16 dist=32/94 edge=1:-13.95@97.5,88.5 dx=13.5 width=61.4 l=68,80 r=127,97
CxScan: raw_ref=80.0 edge=97.5,88.5 best_raw_x=115 best_err=-0.07 best_cxcy=97.4,119.7 scan=0:-39.3,10:-36.7,20:-34.0,30:-31.1,40:-28.0,50:-24.8,60:-21.3,70:-17.7,80:-13.9,90:-10.1,100:-6.1,110:-2.1,120:1.9,130:6.0,140:9.9
ATGSeedDiag: seed=1@4,93/1@114,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(17.2) imip=0/20 pass=10110 acc=-1 ipm=58.0,90.1 inv=41.2,55.3 | 10(39.2) imip=0/20 pass=10111 acc=-1 ipm=114.0,100.2 inv=124.1,67.6

- stopped_at: 2026-06-22T03:32:59+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive54
```
