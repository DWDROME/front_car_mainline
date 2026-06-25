# drive42

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive42-front_car_circle_drive42.log
- remote_log: /tmp/front_car_circle_drive42.log
- started_at: 2026-06-22T02:23:28+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive42 6
```

4882 /tmp/front_car_circle_drive42.log
CxScan: raw_ref=80.0 edge=98.0,87.5 best_raw_x=115 best_err=-0.59 best_cxcy=97.4,119.7 scan=0:-39.1,10:-36.6,20:-33.9,30:-31.0,40:-28.0,50:-24.8,60:-21.4,70:-17.9,80:-14.2,90:-10.4,100:-6.5,110:-2.6,120:1.4,130:5.3,140:9.2
ATGSeedDiag: seed=1@7,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(60.4) imip=40/60 pass=11100 acc=-1 ipm=137.0,51.7 inv=116.4,29.5 | 18(83.1) imip=8/21 pass=11111 acc=18 ipm=133.7,92.5 inv=143.8,57.0
frame=881 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/22 raw=170/77 sel=122/107 far=0/0 far_raw=0/0 l=0@-1/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=61.0/93.2/0.0/0.0 dist=0 m0=(84,119) ml=(92,95) md=33/1/169 cxcy=84.0,119.6 guide=-9.98 atg=60.0/60.0/60.0 pure=-7.71/-6.53 yaw=599 cmd=799 actual=393 signed=1 rps=2705/4895:4705/5196 duty=3/13
ATGCorner: L=0@-1/1@18 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.0,92.8:144.6,57.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=50:137.4,51.3:116.5,29.4:61.0:11100/18:134.0,92.8:144.6,57.4:93.2:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=61.0/93.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@18 nearNum=122/22 centerNum=122/22 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-8.48@91,96 dx=7.0 idx=1/20 dist=32/260 right=1:-15.43@102,76 dx=18.4 idx=0/10 dist=32/74 sel=1:-12.46@95,92 dx=11.1 idx=0/16 dist=32/212 edge=1:-14.32@98.0,88.0 dx=14.0 width=62.8 l=67,83 r=129,93
CxScan: raw_ref=80.0 edge=98.0,88.0 best_raw_x=115 best_err=-0.59 best_cxcy=97.4,119.7 scan=0:-39.3,10:-36.8,20:-34.1,30:-31.3,40:-28.2,50:-25.0,60:-21.6,70:-18.0,80:-14.3,90:-10.5,100:-6.6,110:-2.6,120:1.4,130:5.4,140:9.3
ATGSeedDiag: seed=1@7,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(61.0) imip=40/60 pass=11100 acc=-1 ipm=137.4,51.3 inv=116.5,29.4 | 18(93.2) imip=8/21 pass=11111 acc=18 ipm=134.0,92.8 inv=144.6,57.4
frame=882 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/21 raw=170/75 sel=122/106 far=0/0 far_raw=0/0 l=0@-1/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=60.7/100.8/0.0/0.0 dist=0 m0=(84,119) ml=(94,93) md=33/1/166 cxcy=84.0,119.6 guide=-12.42 atg=60.0/60.0/60.0 pure=-7.86/-6.47 yaw=745 cmd=945 actual=416 signed=1 rps=2505/5095:4779/5467 duty=2/13
ATGCorner: L=0@-1/1@18 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/134.4,93.6:146.2,58.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=50:137.5,51.1:116.5,29.3:60.7:11100/18:134.4,93.6:146.2,58.4:100.8:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=60.7/100.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@18 nearNum=122/21 centerNum=122/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-9.76@92,95 dx=8.3 idx=2/21 dist=32/256 right=1:-18.04@106,74 dx=22.2 idx=0/11 dist=34/66 sel=1:-13.24@96,92 dx=11.9 idx=0/16 dist=32/210 edge=1:-14.94@98.5,88.5 dx=14.5 width=64.0 l=67,83 r=130,94
CxScan: raw_ref=80.0 edge=98.5,88.5 best_raw_x=120 best_err=0.89 best_cxcy=99.3,119.7 scan=0:-39.9,10:-37.4,20:-34.7,30:-31.9,40:-28.9,50:-25.6,60:-22.2,70:-18.7,80:-14.9,90:-11.1,100:-7.1,110:-3.1,120:0.9,130:4.9,140:8.9
ATGSeedDiag: seed=1@6,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(60.7) imip=40/60 pass=11100 acc=-1 ipm=137.5,51.1 inv=116.5,29.3 | 18(100.8) imip=8/20 pass=11111 acc=18 ipm=134.4,93.6 inv=146.2,58.4
frame=883 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=121/21 raw=170/73 sel=121/105 far=0/0 far_raw=0/0 l=0@-1/1@18 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=60.7/78.9/0.0/0.0 dist=0 m0=(84,119) ml=(94,94) md=33/1/167 cxcy=84.0,119.6 guide=-10.94 atg=60.0/60.0/60.0 pure=-7.93/-6.45 yaw=656 cmd=856 actual=438 signed=1 rps=2627/4973:4437/5134 duty=3/13
ATGCorner: L=0@-1/1@18 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/133.8,96.0:148.7,61.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=50:137.6,51.1:116.6,29.3:60.7:11100/18:133.8,96.0:148.7,61.4:78.9:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=60.7/78.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@18 nearNum=121/21 centerNum=121/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=121/105 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.02@92,95 dx=8.4 idx=2/21 dist=33/253 right=1:-17.17@105,76 dx=20.8 idx=0/10 dist=33/70 sel=1:-13.46@96,92 dx=12.0 idx=0/16 dist=32/208 edge=1:-14.94@98.5,88.5 dx=14.5 width=64.0 l=67,83 r=130,94
CxScan: raw_ref=80.0 edge=98.5,88.5 best_raw_x=120 best_err=0.89 best_cxcy=99.3,119.7 scan=0:-39.9,10:-37.4,20:-34.7,30:-31.9,40:-28.9,50:-25.6,60:-22.2,70:-18.7,80:-14.9,90:-11.1,100:-7.1,110:-3.1,120:0.9,130:4.9,140:8.9
ATGSeedDiag: seed=1@6,108/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=50(60.7) imip=40/60 pass=11100 acc=-1 ipm=137.6,51.1 inv=116.6,29.3 | 18(78.9) imip=8/20 pass=11111 acc=18 ipm=133.8,96.0 inv=148.7,61.4
frame=884 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/21 raw=170/73 sel=122/106 far=0/0 far_raw=0/0 l=0@-1/1@17 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=62.6/95.7/0.0/0.0 dist=0 m0=(84,119) ml=(94,94) md=34/1/169 cxcy=84.0,119.6 guide=-10.86 atg=60.0/60.0/60.0 pure=-8.06/-6.50 yaw=651 cmd=851 actual=431 signed=1 rps=2633/4967:4477/5298 duty=3/13
ATGCorner: L=0@-1/1@17 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/132.9,94.5:145.4,59.6 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=49:136.0,53.7:116.5,30.3:62.6:11100/17:132.9,94.5:145.4,59.6:95.7:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=62.6/95.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@17 nearNum=122/21 centerNum=122/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.12@92,95 dx=8.5 idx=2/21 dist=33/258 right=1:-17.63@105,76 dx=21.2 idx=0/10 dist=33/70 sel=1:-13.44@96,93 dx=12.0 idx=0/16 dist=32/210 edge=1:-16.06@99.5,89.0 dx=15.5 width=64.1 l=68,83 r=131,95
CxScan: raw_ref=80.0 edge=99.5,89.0 best_raw_x=120 best_err=-0.16 best_cxcy=99.3,119.7 scan=0:-40.8,10:-38.3,20:-35.7,30:-32.9,40:-29.9,50:-26.7,60:-23.3,70:-19.8,80:-16.1,90:-12.2,100:-8.3,110:-4.2,120:-0.2,130:3.9,140:7.9
ATGSeedDiag: seed=1@6,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(62.6) imip=39/59 pass=11100 acc=-1 ipm=136.0,53.7 inv=116.5,30.3 | 17(95.7) imip=7/20 pass=11111 acc=17 ipm=132.9,94.5 inv=145.4,59.6
frame=885 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=121/21 raw=170/71 sel=121/103 far=0/0 far_raw=0/0 l=0@-1/1@17 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=62.6/99.5/0.0/0.0 dist=0 m0=(84,119) ml=(94,95) md=32/1/166 cxcy=84.0,119.6 guide=-13.08 atg=60.0/60.0/60.0 pure=-8.13/-6.46 yaw=785 cmd=985 actual=435 signed=1 rps=2450/5150:4422/5294 duty=3/14
ATGCorner: L=0@-1/1@17 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/133.1,95.4:146.9,60.6 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=49:136.4,53.3:116.6,30.1:62.6:11100/17:133.1,95.4:146.9,60.6:99.5:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=62.6/99.5/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@17 nearNum=121/21 centerNum=121/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=121/103 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.55@93,96 dx=8.7 idx=2/21 dist=32/253 right=1:-18.20@106,76 dx=22.0 idx=0/10 dist=33/70 sel=1:-13.89@96,93 dx=12.3 idx=0/16 dist=32/204 edge=1:-16.06@99.5,89.0 dx=15.5 width=64.1 l=68,83 r=131,95
CxScan: raw_ref=80.0 edge=99.5,89.0 best_raw_x=120 best_err=-0.16 best_cxcy=99.3,119.7 scan=0:-40.8,10:-38.3,20:-35.7,30:-32.9,40:-29.9,50:-26.7,60:-23.3,70:-19.8,80:-16.1,90:-12.2,100:-8.3,110:-4.2,120:-0.2,130:3.9,140:7.9
ATGSeedDiag: seed=1@6,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=49(62.6) imip=39/59 pass=11100 acc=-1 ipm=136.4,53.3 inv=116.6,30.1 | 17(99.5) imip=7/20 pass=11111 acc=17 ipm=133.1,95.4 inv=146.9,60.6
frame=886 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/20 raw=170/70 sel=122/101 far=0/0 far_raw=0/0 l=0@-1/1@17 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=60.3/94.7/0.0/0.0 dist=0 m0=(84,119) ml=(95,95) md=32/1/166 cxcy=84.0,119.6 guide=-13.82 atg=60.0/60.0/60.0 pure=-8.28/-6.35 yaw=829 cmd=1029 actual=433 signed=1 rps=2389/5211:4271/5073 duty=3/14
ATGCorner: L=0@-1/1@17 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/132.7,97.4:149.2,63.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=48:134.5,54.1:115.4,30.5:60.3:11100/17:132.7,97.4:149.2,63.4:94.7:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=60.3/94.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@17 nearNum=122/20 centerNum=122/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/101 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.70@93,96 dx=8.8 idx=3/21 dist=33/250 right=1:-18.39@106,76 dx=22.1 idx=0/10 dist=32/64 sel=1:-15.02@97,93 dx=13.3 idx=0/16 dist=32/200 edge=1:-16.20@99.5,89.5 dx=15.5 width=64.3 l=68,83 r=131,96
CxScan: raw_ref=80.0 edge=99.5,89.5 best_raw_x=120 best_err=-0.17 best_cxcy=99.3,119.7 scan=0:-41.1,10:-38.6,20:-36.0,30:-33.1,40:-30.1,50:-26.9,60:-23.5,70:-19.9,80:-16.2,90:-12.3,100:-8.3,110:-4.3,120:-0.2,130:3.9,140:8.0
ATGSeedDiag: seed=1@5,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(60.3) imip=38/58 pass=11100 acc=-1 ipm=134.5,54.1 inv=115.4,30.5 | 17(94.7) imip=7/19 pass=11111 acc=17 ipm=132.7,97.4 inv=149.2,63.4
frame=887 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=121/20 raw=170/69 sel=121/102 far=0/0 far_raw=0/0 l=0@-1/1@17 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=62.6/92.1/0.0/0.0 dist=0 m0=(84,119) ml=(96,95) md=33/1/166 cxcy=84.0,119.6 guide=-13.99 atg=60.0/60.0/60.0 pure=-8.43/-6.38 yaw=839 cmd=1039 actual=446 signed=1 rps=2376/5224:4184/4788 duty=3/15
ATGCorner: L=0@-1/1@17 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/132.5,97.9:149.6,64.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=48:134.9,54.8:116.1,30.8:62.6:11100/17:132.5,97.9:149.6,64.0:92.1:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=62.6/92.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@17 nearNum=121/20 centerNum=121/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=121/102 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.18@94,96 dx=10.2 idx=3/22 dist=33/252 right=1:-18.88@107,76 dx=22.7 idx=0/10 dist=32/65 sel=1:-15.43@98,93 dx=13.6 idx=0/16 dist=32/202 edge=1:-16.70@100.0,89.5 dx=16.0 width=65.3 l=68,83 r=132,96
CxScan: raw_ref=80.0 edge=100.0,89.5 best_raw_x=120 best_err=-0.70 best_cxcy=99.3,119.7 scan=0:-41.4,10:-38.9,20:-36.3,30:-33.5,40:-30.5,50:-27.3,60:-24.0,70:-20.4,80:-16.7,90:-12.8,100:-8.9,110:-4.8,120:-0.7,130:3.4,140:7.5
ATGSeedDiag: seed=1@5,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(62.6) imip=38/58 pass=11100 acc=-1 ipm=134.9,54.8 inv=116.1,30.8 | 17(92.1) imip=7/19 pass=11111 acc=17 ipm=132.5,97.9 inv=149.6,64.0
frame=888 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=120/19 raw=170/67 sel=120/104 far=0/0 far_raw=0/0 l=0@-1/1@16 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=64.5/94.0/0.0/0.0 dist=0 m0=(84,119) ml=(96,95) md=33/1/167 cxcy=84.0,119.6 guide=-14.05 atg=60.0/60.0/60.0 pure=-8.49/-6.38 yaw=843 cmd=1043 actual=469 signed=1 rps=2371/5229:4518/4866 duty=2/14
ATGCorner: L=0@-1/1@16 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/132.0,96.6:147.0,62.2 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=48:135.2,55.3:116.7,31.0:64.5:11100/16:132.0,96.6:147.0,62.2:94.0:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=64.5/94.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@16 nearNum=120/19 centerNum=120/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=120/104 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-11.08@93,97 dx=9.0 idx=3/21 dist=32/258 right=1:-20.86@110,75 dx=25.6 idx=0/11 dist=34/59 sel=1:-15.57@98,94 dx=13.7 idx=0/16 dist=32/206 edge=1:-17.50@100.5,90.5 dx=16.5 width=64.3 l=69,84 r=132,97
CxScan: raw_ref=80.0 edge=100.5,90.5 best_raw_x=125 best_err=0.83 best_cxcy=101.3,119.7 scan=0:-42.2,10:-39.8,20:-37.2,30:-34.4,40:-31.4,50:-28.2,60:-24.8,70:-21.2,80:-17.5,90:-13.6,100:-9.6,110:-5.4,120:-1.3,130:2.9,140:7.1
ATGSeedDiag: seed=1@5,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(64.5) imip=38/58 pass=11100 acc=-1 ipm=135.2,55.3 inv=116.7,31.0 | 16(94.0) imip=6/18 pass=11111 acc=16 ipm=132.0,96.6 inv=147.0,62.2
frame=889 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/19 raw=170/66 sel=122/104 far=0/0 far_raw=0/0 l=0@-1/1@16 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=62.4/97.0/0.0/0.0 dist=0 m0=(84,119) ml=(96,95) md=33/1/165 cxcy=84.0,119.6 guide=-14.35 atg=60.0/60.0/60.0 pure=-8.54/-6.29 yaw=861 cmd=1061 actual=496 signed=1 rps=2346/5254:4470/4644 duty=2/15
ATGCorner: L=0@-1/1@16 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/132.2,96.9:147.8,62.7 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=47:133.6,55.8:115.6,31.2:62.4:11100/16:132.2,96.9:147.8,62.7:97.0:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=62.4/97.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@16 nearNum=122/19 centerNum=122/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/104 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-11.58@93,97 dx=9.4 idx=3/21 dist=32/258 right=1:-21.26@110,76 dx=26.1 idx=0/11 dist=34/60 sel=1:-16.16@98,94 dx=14.2 idx=0/16 dist=32/206 edge=1:-17.50@100.5,90.5 dx=16.5 width=64.3 l=69,84 r=132,97
CxScan: raw_ref=80.0 edge=100.5,90.5 best_raw_x=125 best_err=0.83 best_cxcy=101.3,119.7 scan=0:-42.2,10:-39.8,20:-37.2,30:-34.4,40:-31.4,50:-28.2,60:-24.8,70:-21.2,80:-17.5,90:-13.6,100:-9.6,110:-5.4,120:-1.3,130:2.9,140:7.1
ATGSeedDiag: seed=1@5,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(62.4) imip=37/57 pass=11100 acc=-1 ipm=133.6,55.8 inv=115.6,31.2 | 16(97.0) imip=6/18 pass=11111 acc=16 ipm=132.2,96.9 inv=147.8,62.7
frame=890 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=122/19 raw=170/67 sel=122/106 far=0/0 far_raw=0/0 l=0@-1/1@16 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=61.8/99.8/0.0/0.0 dist=0 m0=(84,119) ml=(97,95) md=33/1/164 cxcy=84.0,119.6 guide=-16.29 atg=60.0/60.0/60.0 pure=-8.56/-6.26 yaw=977 cmd=1177 actual=518 signed=1 rps=2187/5413:4737/4855 duty=1/15
ATGCorner: L=0@-1/1@16 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/132.3,98.4:150.0,64.7 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=47:133.8,55.6:115.6,31.1:61.8:11100/16:132.3,98.4:150.0,64.7:99.8:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=61.8/99.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@16 nearNum=122/19 centerNum=122/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.08@94,97 dx=9.7 idx=3/21 dist=33/261 right=1:-19.89@108,77 dx=23.8 idx=0/10 dist=31/60 sel=1:-16.66@99,94 dx=14.6 idx=0/16 dist=32/210 edge=1:-17.66@100.5,91.0 dx=16.5 width=64.5 l=69,84 r=132,98
CxScan: raw_ref=80.0 edge=100.5,91.0 best_raw_x=125 best_err=0.84 best_cxcy=101.3,119.7 scan=0:-42.5,10:-40.1,20:-37.5,30:-34.6,40:-31.6,50:-28.4,60:-25.0,70:-21.4,80:-17.7,90:-13.7,100:-9.7,110:-5.5,120:-1.3,130:2.9,140:7.1
ATGSeedDiag: seed=1@5,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(61.8) imip=37/57 pass=11100 acc=-1 ipm=133.8,55.6 inv=115.6,31.1 | 16(99.8) imip=6/18 pass=11111 acc=16 ipm=132.3,98.4 inv=150.0,64.7
frame=891 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=121/18 raw=170/65 sel=121/105 far=0/0 far_raw=0/0 l=0@-1/1@16 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=63.3/97.3/0.0/0.0 dist=0 m0=(84,119) ml=(97,95) md=32/1/163 cxcy=84.0,119.6 guide=-16.23 atg=60.0/60.0/60.0 pure=-8.58/-6.16 yaw=974 cmd=1174 actual=567 signed=1 rps=2191/5409:4886/5159 duty=1/15
ATGCorner: L=0@-1/1@16 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/131.7,99.7:151.2,66.6 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=47:133.9,55.6:115.7,31.1:63.3:11100/16:131.7,99.7:151.2,66.6:97.3:11111 seed_src=none/lpt seed=40.0,91.8/73.8,25.1 far_start=73,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=63.3/97.3/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@16 nearNum=121/18 centerNum=121/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=121/105 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-13.21@95,97 dx=10.9 idx=4/22 dist=32/256 right=1:-21.85@111,76 dx=26.7 idx=0/11 dist=33/54 sel=1:-17.36@99,94 dx=15.3 idx=0/16 dist=32/208 edge=1:-17.98@100.5,92.0 dx=16.5 width=65.0 l=69,84 r=132,100
CxScan: raw_ref=80.0 edge=100.5,92.0 best_raw_x=125 best_err=0.85 best_cxcy=101.3,119.7 scan=0:-43.1,10:-40.6,20:-38.0,30:-35.2,40:-32.1,50:-28.9,60:-25.5,70:-21.8,80:-18.0,90:-14.0,100:-9.8,110:-5.6,120:-1.3,130:3.0,140:7.3
ATGSeedDiag: seed=1@5,108/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(63.3) imip=37/57 pass=11100 acc=-1 ipm=133.9,55.6 inv=115.7,31.1 | 16(97.3) imip=6/17 pass=11111 acc=16 ipm=131.7,99.7 inv=151.2,66.6

- stopped_at: 2026-06-22T02:23:42+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive42
```
