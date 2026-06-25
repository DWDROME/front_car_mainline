# drive25

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive25-front_car_circle_drive25.log
- remote_log: /tmp/front_car_circle_drive25.log
- started_at: 2026-06-22T01:17:19+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive25 6
```

4701 /tmp/front_car_circle_drive25.log
CxScan: raw_ref=80.0 edge=97.5,88.5 best_raw_x=115 best_err=-0.07 best_cxcy=97.4,119.7 scan=0:-39.3,10:-36.7,20:-34.0,30:-31.1,40:-28.0,50:-24.8,60:-21.3,70:-17.7,80:-13.9,90:-10.1,100:-6.1,110:-2.1,120:1.9,130:6.0,140:9.9
ATGSeedDiag: seed=1@4,108/1@124,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=48(62.1) imip=38/58 pass=11100 acc=-1 ipm=132.1,52.4 inv=112.7,29.8 | 20(87.6) imip=10/21 pass=11111 acc=20 ipm=132.2,101.4 inv=154.8,69.3
frame=881 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=122/21 raw=170/73 sel=122/107 far=0/0 far_raw=0/0 l=0@-1/1@17 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=62.7/96.5/0.0/0.0 dist=181 m0=(84,119) ml=(93,95) md=33/1/164 cxcy=84.0,119.6 guide=-11.47 atg=60.0/60.0/60.0 pure=-7.96/-6.22 yaw=688 cmd=888 actual=385 signed=1 rps=2783/5217:5181/5573 duty=3/14
ATGCorner: L=0@-1/1@17 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/131.9,95.7:145.6,61.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=47:130.9,53.8:112.4,30.4:62.7:11100/17:131.9,95.7:145.6,61.0:96.5:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=62.7/96.5/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@17 nearNum=122/21 centerNum=122/21 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-7.86@90,96 dx=6.4 idx=2/20 dist=32/257 right=1:-17.51@105,75 dx=21.3 idx=0/10 dist=34/72 sel=1:-12.08@95,94 dx=10.5 idx=0/16 dist=32/212 edge=1:-15.07@98.5,89.0 dx=14.5 width=64.1 l=67,83 r=130,95
CxScan: raw_ref=80.0 edge=98.5,89.0 best_raw_x=120 best_err=0.90 best_cxcy=99.3,119.7 scan=0:-40.2,10:-37.7,20:-35.0,30:-32.1,40:-29.1,50:-25.8,60:-22.4,70:-18.8,80:-15.1,90:-11.2,100:-7.2,110:-3.2,120:0.9,130:5.0,140:9.0
ATGSeedDiag: seed=1@4,108/1@124,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(62.7) imip=37/57 pass=11100 acc=-1 ipm=130.9,53.8 inv=112.4,30.4 | 17(96.5) imip=7/20 pass=11111 acc=17 ipm=131.9,95.7 inv=145.6,61.0
frame=882 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=126/20 raw=170/71 sel=126/108 far=0/0 far_raw=0/0 l=0@-1/1@17 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=62.9/78.8/0.0/0.0 dist=196 m0=(84,119) ml=(93,95) md=32/1/163 cxcy=84.0,119.6 guide=-11.70 atg=60.0/60.0/60.0 pure=-8.03/-6.21 yaw=702 cmd=902 actual=399 signed=1 rps=2764/5236:5475/5716 duty=3/14
ATGCorner: L=0@-1/1@17 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/131.7,96.8:146.7,62.5 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=47:131.2,53.6:112.5,30.3:62.9:11100/17:131.7,96.8:146.7,62.5:78.8:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=62.9/78.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@17 nearNum=126/20 centerNum=126/20 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=126/108 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-9.51@92,96 dx=7.9 idx=2/21 dist=33/262 right=1:-17.58@105,76 dx=21.2 idx=0/10 dist=32/65 sel=1:-12.43@95,94 dx=10.8 idx=0/16 dist=32/214 edge=1:-15.07@98.5,89.0 dx=14.5 width=64.1 l=67,83 r=130,95
CxScan: raw_ref=80.0 edge=98.5,89.0 best_raw_x=120 best_err=0.90 best_cxcy=99.3,119.7 scan=0:-40.2,10:-37.7,20:-35.0,30:-32.1,40:-29.1,50:-25.8,60:-22.4,70:-18.8,80:-15.1,90:-11.2,100:-7.2,110:-3.2,120:0.9,130:5.0,140:9.0
ATGSeedDiag: seed=1@4,108/1@124,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(62.9) imip=37/57 pass=11100 acc=-1 ipm=131.2,53.6 inv=112.5,30.3 | 17(78.8) imip=7/19 pass=11111 acc=17 ipm=131.7,96.8 inv=146.7,62.5
frame=883 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=126/19 raw=170/71 sel=126/106 far=0/0 far_raw=0/0 l=0@-1/1@16 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=62.1/93.3/0.0/0.0 dist=210 m0=(84,119) ml=(94,95) md=33/1/165 cxcy=84.0,119.6 guide=-11.04 atg=60.0/60.0/60.0 pure=-8.19/-6.12 yaw=663 cmd=863 actual=415 signed=1 rps=2818/5182:5206/5313 duty=3/14
ATGCorner: L=0@-1/1@16 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/130.9,95.8:144.3,61.2 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=47:131.4,53.3:112.6,30.2:62.1:11100/16:130.9,95.8:144.3,61.2:93.3:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=62.1/93.3/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@16 nearNum=126/19 centerNum=126/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=126/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.18@92,96 dx=8.4 idx=3/21 dist=32/255 right=1:-19.66@108,75 dx=24.0 idx=0/11 dist=34/59 sel=1:-13.91@96,94 dx=12.1 idx=0/16 dist=32/210 edge=1:-16.20@99.5,89.5 dx=15.5 width=64.3 l=68,83 r=131,96
CxScan: raw_ref=80.0 edge=99.5,89.5 best_raw_x=120 best_err=-0.17 best_cxcy=99.3,119.7 scan=0:-41.1,10:-38.6,20:-36.0,30:-33.1,40:-30.1,50:-26.9,60:-23.5,70:-19.9,80:-16.2,90:-12.3,100:-8.3,110:-4.3,120:-0.2,130:3.9,140:8.0
ATGSeedDiag: seed=1@4,108/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=47(62.1) imip=37/57 pass=11100 acc=-1 ipm=131.4,53.3 inv=112.6,30.2 | 16(93.3) imip=6/18 pass=11111 acc=16 ipm=130.9,95.8 inv=144.3,61.2
frame=884 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=125/19 raw=170/68 sel=125/105 far=0/0 far_raw=0/0 l=0@-1/1@16 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=63.4/96.0/0.0/0.0 dist=224 m0=(84,119) ml=(94,95) md=33/1/163 cxcy=84.0,119.6 guide=-13.30 atg=60.0/60.0/60.0 pure=-8.34/-6.11 yaw=798 cmd=998 actual=450 signed=1 rps=2632/5368:5349/5342 duty=2/15
ATGCorner: L=0@-1/1@16 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/131.2,97.6:147.1,63.6 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=46:130.2,55.7:112.6,31.2:63.4:11100/16:131.2,97.6:147.1,63.6:96.0:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=63.4/96.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@16 nearNum=125/19 centerNum=125/19 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=125/105 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-9.32@91,98 dx=7.4 idx=3/20 dist=32/258 right=1:-18.51@106,77 dx=22.1 idx=0/10 dist=31/60 sel=1:-14.29@96,94 dx=12.4 idx=0/16 dist=32/208 edge=1:-16.50@99.5,90.5 dx=15.5 width=64.8 l=68,83 r=131,98
CxScan: raw_ref=80.0 edge=99.5,90.5 best_raw_x=120 best_err=-0.17 best_cxcy=99.3,119.7 scan=0:-41.6,10:-39.1,20:-36.5,30:-33.6,40:-30.6,50:-27.4,60:-23.9,70:-20.3,80:-16.5,90:-12.6,100:-8.5,110:-4.4,120:-0.2,130:4.0,140:8.1
ATGSeedDiag: seed=1@4,108/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(63.4) imip=36/56 pass=11100 acc=-1 ipm=130.2,55.7 inv=112.6,31.2 | 16(96.0) imip=6/18 pass=11111 acc=16 ipm=131.2,97.6 inv=147.1,63.6
frame=885 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=122/18 raw=170/67 sel=122/107 far=0/0 far_raw=0/0 l=0@-1/1@16 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=63.8/92.0/0.0/0.0 dist=238 m0=(84,119) ml=(95,96) md=33/1/163 cxcy=84.0,119.6 guide=-13.29 atg=60.0/60.0/60.0 pure=-8.52/-6.06 yaw=797 cmd=997 actual=483 signed=1 rps=2633/5367:5048/5099 duty=3/15
ATGCorner: L=0@-1/1@16 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/130.3,99.5:148.6,66.3 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=46:130.5,55.3:112.7,31.0:63.8:11100/16:130.3,99.5:148.6,66.3:92.0:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=63.8/92.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@16 nearNum=122/18 centerNum=122/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=122/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-10.98@93,97 dx=8.8 idx=3/21 dist=33/256 right=1:-20.82@109,76 dx=25.4 idx=0/11 dist=33/54 sel=1:-14.95@97,95 dx=12.8 idx=0/16 dist=32/212 edge=1:-16.80@99.5,91.5 dx=15.5 width=62.8 l=69,84 r=130,99
CxScan: raw_ref=80.0 edge=99.5,91.5 best_raw_x=120 best_err=-0.17 best_cxcy=99.3,119.7 scan=0:-42.2,10:-39.7,20:-37.0,30:-34.1,40:-31.1,50:-27.8,60:-24.3,70:-20.7,80:-16.8,90:-12.8,100:-8.7,110:-4.4,120:-0.2,130:4.1,140:8.3
ATGSeedDiag: seed=1@4,108/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=46(63.8) imip=36/56 pass=11100 acc=-1 ipm=130.5,55.3 inv=112.7,31.0 | 16(92.0) imip=6/17 pass=11111 acc=16 ipm=130.3,99.5 inv=148.6,66.3
frame=886 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=120/18 raw=170/67 sel=120/101 far=0/0 far_raw=0/0 l=0@-1/1@15 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=64.4/98.2/0.0/0.0 dist=252 m0=(84,119) ml=(96,96) md=32/1/161 cxcy=84.0,119.6 guide=-15.57 atg=60.0/60.0/60.0 pure=-8.72/-5.94 yaw=934 cmd=1134 actual=510 signed=1 rps=2446/5554:5088/5433 duty=2/15
ATGCorner: L=0@-1/1@15 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/129.9,98.0:145.8,64.2 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=45:129.5,57.3:112.7,31.9:64.4:11100/15:129.9,98.0:145.8,64.2:98.2:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=64.4/98.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@15 nearNum=120/18 centerNum=120/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=120/101 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.81@94,97 dx=10.5 idx=4/22 dist=33/250 right=1:-21.41@110,76 dx=26.2 idx=0/11 dist=33/55 sel=1:-16.66@98,95 dx=14.4 idx=0/16 dist=32/200 edge=1:-16.96@99.5,92.0 dx=15.5 width=63.1 l=69,84 r=130,100
CxScan: raw_ref=80.0 edge=99.5,92.0 best_raw_x=120 best_err=-0.17 best_cxcy=99.3,119.7 scan=0:-42.4,10:-40.0,20:-37.3,30:-34.4,40:-31.3,50:-28.0,60:-24.5,70:-20.8,80:-17.0,90:-12.9,100:-8.7,110:-4.5,120:-0.2,130:4.1,140:8.4
ATGSeedDiag: seed=1@4,107/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(64.4) imip=35/55 pass=11100 acc=-1 ipm=129.5,57.3 inv=112.7,31.9 | 15(98.2) imip=5/17 pass=11111 acc=15 ipm=129.9,98.0 inv=145.8,64.2
frame=887 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=121/18 raw=170/65 sel=121/105 far=0/0 far_raw=0/0 l=0@-1/1@15 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=64.9/100.6/0.0/0.0 dist=267 m0=(84,119) ml=(96,96) md=32/1/161 cxcy=84.0,119.6 guide=-15.38 atg=60.0/60.0/60.0 pure=-8.72/-5.95 yaw=923 cmd=1123 actual=531 signed=1 rps=2461/5539:5046/5814 duty=2/15
ATGCorner: L=0@-1/1@15 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/130.2,99.4:148.2,66.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=45:129.5,57.4:112.7,31.9:64.9:11100/15:130.2,99.4:148.2,66.1:100.6:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=64.9/100.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@15 nearNum=121/18 centerNum=121/18 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=121/105 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-12.73@94,97 dx=10.4 idx=4/22 dist=33/257 right=1:-22.40@112,76 dx=27.5 idx=0/11 dist=34/55 sel=1:-16.50@98,95 dx=14.2 idx=0/16 dist=32/208 edge=1:-17.28@99.5,93.0 dx=15.5 width=63.6 l=69,84 r=130,102
CxScan: raw_ref=80.0 edge=99.5,93.0 best_raw_x=120 best_err=-0.18 best_cxcy=99.3,119.7 scan=0:-43.0,10:-40.5,20:-37.8,30:-34.9,40:-31.8,50:-28.5,60:-25.0,70:-21.2,80:-17.3,90:-13.2,100:-8.9,110:-4.6,120:-0.2,130:4.2,140:8.5
ATGSeedDiag: seed=1@4,107/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=45(64.9) imip=35/55 pass=11100 acc=-1 ipm=129.5,57.4 inv=112.7,31.9 | 15(100.6) imip=5/17 pass=11111 acc=15 ipm=130.2,99.4 inv=148.2,66.1
frame=888 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=124/17 raw=170/63 sel=124/106 far=0/0 far_raw=0/0 l=0@-1/1@15 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=63.6/95.8/0.0/0.0 dist=282 m0=(84,119) ml=(96,96) md=32/1/160 cxcy=84.0,119.6 guide=-15.38 atg=60.0/60.0/60.0 pure=-8.70/-5.89 yaw=923 cmd=1123 actual=567 signed=1 rps=2461/5539:4720/5769 duty=3/15
ATGCorner: L=0@-1/1@15 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/129.7,100.6:149.4,68.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=44:127.8,57.9:111.6,32.2:63.6:11110/15:129.7,100.6:149.4,68.0:95.8:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=63.6/95.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@15 nearNum=124/17 centerNum=124/17 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-13.04@95,97 dx=10.6 idx=4/22 dist=32/257 right=1:-22.23@111,77 dx=27.0 idx=0/11 dist=32/49 sel=1:-16.55@98,95 dx=14.2 idx=0/16 dist=32/210 edge=1:-16.91@99.0,93.5 dx=15.0 width=62.9 l=69,84 r=129,103
CxScan: raw_ref=80.0 edge=99.0,93.5 best_raw_x=120 best_err=0.40 best_cxcy=99.3,119.7 scan=0:-43.0,10:-40.5,20:-37.8,30:-34.8,40:-31.7,50:-28.3,60:-24.7,70:-20.9,80:-16.9,90:-12.7,100:-8.4,110:-4.0,120:0.4,130:4.8,140:9.2
ATGSeedDiag: seed=1@4,106/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(63.6) imip=34/54 pass=11110 acc=-1 ipm=127.8,57.9 inv=111.6,32.2 | 15(95.8) imip=5/16 pass=11111 acc=15 ipm=129.7,100.6 inv=149.4,68.0
frame=889 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=127/17 raw=170/64 sel=127/106 far=0/0 far_raw=0/0 l=0@-1/1@15 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=64.0/91.4/0.0/0.0 dist=297 m0=(84,119) ml=(98,96) md=33/1/160 cxcy=84.0,119.6 guide=-15.64 atg=60.0/60.0/60.0 pure=-8.72/-5.78 yaw=939 cmd=1139 actual=595 signed=1 rps=2440/5560:4571/5679 duty=3/15
ATGCorner: L=0@-1/1@15 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/129.5,101.5:150.5,69.5 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=44:128.0,57.7:111.6,32.1:64.0:11110/15:129.5,101.5:150.5,69.5:91.4:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=64.0/91.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@15 nearNum=127/17 centerNum=127/17 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=127/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-14.84@96,96 dx=12.3 idx=5/23 dist=33/260 right=1:-22.90@112,77 dx=27.9 idx=0/11 dist=32/50 sel=1:-18.13@100,95 dx=15.8 idx=0/16 dist=32/210 edge=1:-17.61@99.5,94.0 dx=15.5 width=62.3 l=70,84 r=129,104
CxScan: raw_ref=80.0 edge=99.5,94.0 best_raw_x=120 best_err=-0.18 best_cxcy=99.3,119.7 scan=0:-43.6,10:-41.1,20:-38.4,30:-35.5,40:-32.4,50:-29.0,60:-25.4,70:-21.6,80:-17.6,90:-13.4,100:-9.1,110:-4.7,120:-0.2,130:4.3,140:8.7
ATGSeedDiag: seed=1@4,106/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(64.0) imip=34/54 pass=11110 acc=-1 ipm=128.0,57.7 inv=111.6,32.1 | 15(91.4) imip=5/16 pass=11111 acc=15 ipm=129.5,101.5 inv=150.5,69.5
frame=890 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=128/17 raw=170/62 sel=128/106 far=0/0 far_raw=0/0 l=0@-1/1@14 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=63.8/98.4/0.0/0.0 dist=311 m0=(84,119) ml=(98,95) md=33/1/159 cxcy=84.0,119.6 guide=-17.44 atg=60.0/60.0/60.0 pure=-8.72/-5.71 yaw=1046 cmd=1246 actual=646 signed=1 rps=2292/5708:4681/5861 duty=2/15
ATGCorner: L=0@-1/1@14 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/129.2,99.7:147.2,66.7 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=44:128.1,57.5:111.7,32.0:63.8:11110/14:129.2,99.7:147.2,66.7:98.4:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=63.8/98.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@14 nearNum=128/17 centerNum=128/17 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=128/106 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-15.24@97,96 dx=12.6 idx=5/23 dist=33/259 right=1:-23.47@113,77 dx=28.7 idx=0/11 dist=32/50 sel=1:-18.36@100,94 dx=16.1 idx=0/16 dist=32/210 edge=1:-17.61@99.5,94.0 dx=15.5 width=62.3 l=70,84 r=129,104
CxScan: raw_ref=80.0 edge=99.5,94.0 best_raw_x=120 best_err=-0.18 best_cxcy=99.3,119.7 scan=0:-43.6,10:-41.1,20:-38.4,30:-35.5,40:-32.4,50:-29.0,60:-25.4,70:-21.6,80:-17.6,90:-13.4,100:-9.1,110:-4.7,120:-0.2,130:4.3,140:8.7
ATGSeedDiag: seed=1@4,106/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=44(63.8) imip=34/54 pass=11110 acc=-1 ipm=128.1,57.5 inv=111.7,32.0 | 14(98.4) imip=4/16 pass=11111 acc=14 ipm=129.2,99.7 inv=147.2,66.7
frame=891 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=2 speed=0 near=128/16 raw=170/58 sel=128/107 far=0/0 far_raw=0/0 l=0@-1/1@14 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=63.1/98.8/0.0/0.0 dist=326 m0=(84,119) ml=(97,97) md=33/1/161 cxcy=84.0,119.6 guide=-14.94 atg=60.0/60.0/60.0 pure=-8.82/-5.75 yaw=896 cmd=1096 actual=696 signed=1 rps=2497/5503:4843/5997 duty=3/14
ATGCorner: L=0@-1/1@14 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/129.1,101.6:150.2,69.7 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=43:126.2,58.7:110.5,32.5:63.1:11110/14:129.1,101.6:150.2,69.7:98.8:11111 seed_src=none/lpt seed=40.0,91.8/51.3,29.5 far_start=51,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=63.1/98.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@14 nearNum=128/16 centerNum=128/16 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=128/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-14.09@95,98 dx=11.3 idx=4/22 dist=33/269 right=1:-23.80@113,77 dx=29.0 idx=0/11 dist=31/44 sel=1:-17.85@99,95 dx=15.3 idx=0/16 dist=32/212 edge=1:-17.61@99.5,94.0 dx=15.5 width=62.3 l=70,84 r=129,104
CxScan: raw_ref=80.0 edge=99.5,94.0 best_raw_x=120 best_err=-0.18 best_cxcy=99.3,119.7 scan=0:-43.6,10:-41.1,20:-38.4,30:-35.5,40:-32.4,50:-29.0,60:-25.4,70:-21.6,80:-17.6,90:-13.4,100:-9.1,110:-4.7,120:-0.2,130:4.3,140:8.7
ATGSeedDiag: seed=1@4,107/1@124,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=43(63.1) imip=33/53 pass=11110 acc=-1 ipm=126.2,58.7 inv=110.5,32.5 | 14(98.8) imip=4/15 pass=11111 acc=14 ipm=129.1,101.6 inv=150.2,69.7

- stopped_at: 2026-06-22T01:17:32+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive25
```
