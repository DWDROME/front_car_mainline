# drive32

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive32-front_car_circle_drive32.log
- remote_log: /tmp/front_car_circle_drive32.log
- started_at: 2026-06-22T01:37:09+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive32 6
```

4241 /tmp/front_car_circle_drive32.log
ATGSeedDiag: seed=0@-1,-1/1@133,106 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 5(89.2) imip=0/15 pass=11111 acc=5 ipm=107.6,104.5 inv=118.1,75.1
frame=871 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/3 raw=0/170 sel=3/0 far=0/0 far_raw=0/0 l=0@-1/1@3 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/88.2/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=13.69/6.81 yaw=0 cmd=0 actual=133 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@3 nearNum=0/3 centerNum=0/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=3/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=108,109
ATGSeedDiag: seed=0@-1,-1/1@130,100 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 29(88.2) imip=19/39 pass=11111 acc=3 ipm=49.0,102.0 inv=18.7,71.5
frame=872 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/0 raw=0/0 sel=0/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=13.69/6.81 yaw=0 cmd=0 actual=175 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/0 centerNum=0/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=0/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/0@-1,-1 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=873 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/1 raw=0/170 sel=1/0 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/0.0/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=13.69/6.81 yaw=0 cmd=0 actual=342 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/1 centerNum=0/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=-1,-1
ATGSeedDiag: seed=0@-1,-1/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=874 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=0/29 raw=0/170 sel=29/28 far=0/0 far_raw=0/0 l=0@-1/1@29 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=0.0/170.2/0.0/0.0 dist=0 m0=(84,119) ml=(51,119) md=33/0/53 cxcy=84.0,119.6 guide=54.70 atg=-60.0/-60.0/-60.0 pure=15.64/15.64 yaw=-3200 cmd=-3200 actual=344 signed=0 rps=9386/614:4340/4693 duty=27/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@29 nearNum=0/29 centerNum=0/29 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=29/28 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:63.29@60,131 dx=-23.7 idx=13/21 dist=31/62 sel=1:66.51@55,130 dx=-28.8 idx=0/16 dist=32/54 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=49,104
ATGSeedDiag: seed=0@-1,-1/1@111,86 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(170.2) imip=0/12 pass=11011 acc=29 ipm=106.9,109.0 inv=121.7,84.3
frame=875 line=0 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/1 raw=170/170 sel=1/0 far=0/0 far_raw=0/0 l=1@16/1@3 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=84.4/90.6/0.0/0.0 dist=0 m0=(-1,-1) ml=(-1,-1) md=-1/0/-1 cxcy=84.0,119.6 guide=0.00 atg=-60.0/-60.0/-60.0 pure=15.64/15.64 yaw=0 cmd=0 actual=392 signed=0 rps=0/0:0/0 duty=0/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=1@16/1@3 nearNum=15/1 centerNum=15/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=1/0 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:19.65@64,87 dx=-20.0 idx=0/14 dist=19/19 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=48,108 r=-1,-1
ATGSeedDiag: seed=1@73,85/1@131,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=16(84.4) imip=6/26 pass=11111 acc=16 ipm=44.0,106.2 inv=4.6,79.3 | 3(90.6) imip=0/13 pass=11111 acc=3 ipm=107.4,108.4 inv=121.9,83.0
frame=876 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/2 raw=71/170 sel=16/31 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.8/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(79,87) md=32/1/69 cxcy=84.0,119.6 guide=5.13 atg=-60.0/-60.0/-60.0 pure=7.70/7.91 yaw=-131 cmd=-331 actual=227 signed=0 rps=5453/4547:4829/4910 duty=13/12
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=16/2 centerNum=16/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=16/31 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:4.97@79,83 dx=-5.2 idx=0/1 dist=37/66 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:4.97@79,83 dx=-5.2 idx=0/16 dist=32/60 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=46,108 r=-1,-1
ATGSeedDiag: seed=1@73,86/1@120,89 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(2.8) imip=0/11 pass=10111 acc=-1 ipm=78.4,108.9 inv=66.9,84.6 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=877 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/52 raw=71/170 sel=52/63 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.2/86.0/0.0/0.0 dist=0 m0=(84,119) ml=(52,119) md=32/0/127 cxcy=84.0,119.6 guide=54.24 atg=-60.0/-60.0/-60.0 pure=15.76/8.52 yaw=-3200 cmd=-3200 actual=-61 signed=0 rps=9386/614:5085/5171 duty=27/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@1 nearNum=16/52 centerNum=16/52 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=52/63 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:31.88@47,83 dx=-37.4 idx=0/15 dist=30/30 right=1:62.86@64,133 dx=-19.8 idx=10/18 dist=31/141 sel=1:67.15@59,132 dx=-24.9 idx=0/16 dist=32/124 edge=1:46.38@46.5,107.0 dx=-37.5 width=4.1 l=46,109 r=47,105
CxScan: raw_ref=80.0 edge=46.5,107.0 best_raw_x=0 best_err=10.83 best_cxcy=53.3,119.3 scan=0:10.8,10:16.7,20:22.2,30:27.2,40:31.9,50:36.1,60:39.9,70:43.3,80:46.4,90:49.1,100:51.6,110:53.8,120:55.8,130:57.6,140:59.3
ATGSeedDiag: seed=1@73,88/1@125,91 begin=7,108 block=5 clip=8
ATGLptDiag: best=12(3.2) imip=2/15 pass=10111 acc=-1 ipm=52.9,109.2 inv=17.0,85.9 | 27(86.0) imip=17/37 pass=11111 acc=1 ipm=46.8,105.0 inv=11.3,77.0
frame=878 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=16/43 raw=71/170 sel=43/54 far=0/0 far_raw=0/0 l=0@-1/1@2 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.1/89.2/0.0/0.0 dist=0 m0=(84,119) ml=(51,119) md=33/0/103 cxcy=84.0,119.6 guide=54.91 atg=-60.0/-60.0/-60.0 pure=16.18/8.81 yaw=-3200 cmd=-3200 actual=-87 signed=0 rps=9386/614:4943/4891 duty=27/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@2 nearNum=16/43 centerNum=16/43 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=43/54 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:32.46@46,83 dx=-37.7 idx=0/15 dist=30/30 right=1:62.99@66,134 dx=-17.9 idx=10/19 dist=32/125 sel=1:68.01@61,133 dx=-23.3 idx=0/16 dist=32/106 edge=1:47.22@47.0,108.5 dx=-37.0 width=3.6 l=46,110 r=48,107
CxScan: raw_ref=80.0 edge=47.0,108.5 best_raw_x=0 best_err=10.48 best_cxcy=53.3,119.3 scan=0:10.5,10:16.6,20:22.3,30:27.6,40:32.4,50:36.8,60:40.6,70:44.1,80:47.2,90:50.0,100:52.5,110:54.7,120:56.7,130:58.5,140:60.1
ATGSeedDiag: seed=1@73,89/1@130,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(7.1) imip=0/11 pass=10111 acc=-1 ipm=78.4,110.3 inv=66.8,88.0 | 2(89.2) imip=0/12 pass=11111 acc=2 ipm=107.1,110.4 inv=124.0,87.6
frame=879 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/41 raw=71/170 sel=41/52 far=0/0 far_raw=0/0 l=0@-1/1@2 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=6.8/89.0/0.0/0.0 dist=0 m0=(84,119) ml=(52,119) md=32/0/98 cxcy=84.0,119.6 guide=54.78 atg=-60.0/-60.0/-60.0 pure=16.29/8.94 yaw=-3200 cmd=-3200 actual=-163 signed=0 rps=9386/614:5578/4901 duty=26/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@2 nearNum=15/41 centerNum=15/41 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=41/52 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:30.84@49,84 dx=-35.1 idx=0/14 dist=28/28 right=1:65.09@65,134 dx=-18.7 idx=10/19 dist=32/117 sel=1:69.04@61,134 dx=-23.3 idx=0/16 dist=32/102 edge=1:46.84@47.5,108.5 dx=-36.5 width=3.2 l=48,110 r=47,107
CxScan: raw_ref=80.0 edge=47.5,108.5 best_raw_x=0 best_err=9.67 best_cxcy=53.3,119.3 scan=0:9.7,10:15.8,20:21.6,30:26.9,40:31.8,50:36.2,60:40.2,70:43.7,80:46.8,90:49.7,100:52.2,110:54.4,120:56.5,130:58.3,140:59.9
ATGSeedDiag: seed=1@73,91/1@130,103 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(6.8) imip=3/14 pass=10111 acc=-1 ipm=50.6,110.4 inv=10.7,88.8 | 2(89.0) imip=0/12 pass=11111 acc=2 ipm=106.9,110.4 inv=123.5,87.5
frame=880 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/38 raw=71/170 sel=38/47 far=0/0 far_raw=0/0 l=0@-1/1@2 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=1.7/86.9/0.0/0.0 dist=0 m0=(84,119) ml=(52,119) md=32/0/85 cxcy=84.0,119.6 guide=54.37 atg=-60.0/-60.0/-60.0 pure=16.50/9.98 yaw=-3200 cmd=-3200 actual=-251 signed=0 rps=9386/614:6549/5014 duty=25/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@2 nearNum=15/38 centerNum=15/38 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=38/47 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:31.19@49,85 dx=-35.1 idx=0/14 dist=28/28 right=1:66.55@66,135 dx=-17.9 idx=10/19 dist=32/109 sel=1:70.55@61,135 dx=-22.7 idx=0/16 dist=32/92 edge=1:47.68@47.5,109.5 dx=-36.5 width=3.2 l=48,111 r=47,108
CxScan: raw_ref=80.0 edge=47.5,109.5 best_raw_x=0 best_err=9.95 best_cxcy=53.3,119.3 scan=0:10.0,10:16.3,20:22.2,30:27.6,40:32.6,50:37.0,60:41.0,70:44.5,80:47.7,90:50.5,100:53.0,110:55.2,120:57.2,130:59.0,140:60.7
ATGSeedDiag: seed=1@73,93/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=10(1.7) imip=0/14 pass=10111 acc=-1 ipm=57.5,111.2 inv=23.7,90.8 | 2(86.9) imip=0/12 pass=11111 acc=2 ipm=106.8,111.9 inv=125.4,91.5
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/2 raw=71/12 sel=15/27 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.9/0.0/0.0/0.0 dist=0 m0=(84,119) ml=(76,86) md=33/1/59 cxcy=84.0,119.6 guide=9.03 atg=-60.0/-60.0/-60.0 pure=8.16/8.16 yaw=-542 cmd=-742 actual=-340 signed=0 rps=6017/3983:6387/4521 duty=13/10
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=15/2 centerNum=15/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=15/27 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:7.68@76,86 dx=-7.6 idx=1/2 dist=34/58 right=1:-22.10@107,87 dx=22.6 idx=0/1 dist=2/2 sel=1:10.76@73,86 dx=-10.8 idx=0/16 dist=32/52 edge=1:13.07@77.0,112.5 dx=-7.0 width=58.0 l=48,112 r=106,113
CxScan: raw_ref=80.0 edge=77.0,112.5 best_raw_x=60 best_err=-1.23 best_cxcy=76.4,119.5 scan=0:-38.3,10:-33.5,20:-28.0,30:-22.0,40:-15.4,50:-8.5,60:-1.2,70:6.0,80:13.1,90:19.7,100:25.9,110:31.4,120:36.3,130:40.7,140:44.6
ATGSeedDiag: seed=1@73,94/1@118,97 begin=7,108 block=5 clip=8
ATGLptDiag: best=1(7.9) imip=0/11 pass=10111 acc=-1 ipm=78.4,112.2 inv=66.5,93.0 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=882 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=15/31 raw=71/170 sel=31/40 far=0/0 far_raw=0/0 l=0@-1/1@31 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.1/169.1/0.0/0.0 dist=0 m0=(84,119) ml=(86,119) md=32/0/76 cxcy=84.0,119.6 guide=-1.15 atg=-60.0/-60.0/-60.0 pure=27.19/19.42 yaw=29 cmd=229 actual=-438 signed=0 rps=4686/5314:6764/4702 duty=8/15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@31 nearNum=15/31 centerNum=15/31 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=31/40 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:31.79@49,86 dx=-35.2 idx=0/14 dist=28/28 right=1:-71.95@101,137 dx=16.5 idx=0/5 dist=34/94 sel=1:-62.55@95,137 dx=11.0 idx=0/16 dist=32/78 edge=1:48.21@48.5,111.0 dx=-35.5 width=2.2 l=48,112 r=49,110
CxScan: raw_ref=80.0 edge=48.5,111.0 best_raw_x=0 best_err=8.65 best_cxcy=53.3,119.3 scan=0:8.6,10:15.3,20:21.6,30:27.3,40:32.5,50:37.2,60:41.3,70:45.0,80:48.2,90:51.1,100:53.6,110:55.9,120:57.9,130:59.7,140:61.4
ATGSeedDiag: seed=1@73,96/1@103,98 begin=7,108 block=5 clip=8
ATGLptDiag: best=13(7.1) imip=3/14 pass=10111 acc=-1 ipm=50.6,112.4 inv=7.5,94.0 | 4(169.1) imip=0/14 pass=11011 acc=31 ipm=105.3,113.9 inv=125.2,97.0
frame=883 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/30 raw=71/170 sel=30/39 far=0/0 far_raw=0/0 l=0@-1/1@30 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=3.5/167.7/0.0/0.0 dist=0 m0=(84,119) ml=(84,119) md=32/0/73 cxcy=84.0,119.6 guide=1.67 atg=-60.0/-60.0/-60.0 pure=26.80/19.78 yaw=-43 cmd=157 actual=-613 signed=0 rps=4784/5216:6190/4508 duty=9/15
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@30 nearNum=14/30 centerNum=14/30 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=30/39 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:30.33@51,87 dx=-32.8 idx=0/13 dist=26/26 right=1:-72.65@100,138 dx=16.1 idx=0/5 dist=33/93 sel=1:-61.47@94,137 dx=9.7 idx=0/16 dist=32/76 edge=1:47.43@50.0,111.5 dx=-34.0 width=3.6 l=51,113 r=49,110
CxScan: raw_ref=80.0 edge=50.0,111.5 best_raw_x=0 best_err=6.06 best_cxcy=53.3,119.3 scan=0:6.1,10:13.0,20:19.5,30:25.5,40:31.0,50:35.8,60:40.2,70:44.0,80:47.4,90:50.4,100:53.1,110:55.4,120:57.6,130:59.4,140:61.1
ATGSeedDiag: seed=1@73,98/1@107,100 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(3.5) imip=1/13 pass=10111 acc=-1 ipm=55.2,113.1 inv=16.3,95.9 | 3(167.7) imip=0/13 pass=11011 acc=30 ipm=104.6,114.4 inv=124.3,98.7
frame=884 line=1 track=1 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=14/28 raw=71/170 sel=28/29 far=0/0 far_raw=0/0 l=0@-1/1@28 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=2.4/171.2/0.0/0.0 dist=0 m0=(84,119) ml=(51,119) md=33/0/47 cxcy=84.0,119.6 guide=53.82 atg=-60.0/-60.0/-60.0 pure=18.14/18.14 yaw=-3200 cmd=-3200 actual=-666 signed=0 rps=9386/614:6009/4680 duty=25/0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/1@28 nearNum=14/28 centerNum=14/28 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=28/29 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:30.45@52,88 dx=-32.4 idx=0/13 dist=26/26 right=1:72.54@68,138 dx=-15.6 idx=11/18 dist=32/64 sel=1:75.51@64,138 dx=-19.7 idx=0/16 dist=32/56 edge=1:48.36@50.0,112.5 dx=-34.0 width=3.6 l=51,114 r=49,111
CxScan: raw_ref=80.0 edge=50.0,112.5 best_raw_x=0 best_err=6.26 best_cxcy=53.3,119.3 scan=0:6.3,10:13.4,20:20.1,30:26.2,40:31.8,50:36.7,60:41.1,70:45.0,80:48.4,90:51.3,100:54.0,110:56.3,120:58.4,130:60.2,140:61.9
ATGSeedDiag: seed=1@73,102/1@124,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=11(2.4) imip=1/13 pass=10111 acc=-1 ipm=55.2,114.1 inv=14.8,98.8 | 1(171.2) imip=0/11 pass=11011 acc=28 ipm=106.5,116.0 inv=131.4,103.8

- stopped_at: 2026-06-22T01:37:22+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive32
```
