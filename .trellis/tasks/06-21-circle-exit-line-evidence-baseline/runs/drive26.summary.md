# drive26

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive26-front_car_circle_drive26.log
- remote_log: /tmp/front_car_circle_drive26.log
- started_at: 2026-06-22T01:19:41+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive26 6
```

4718 /tmp/front_car_circle_drive26.log
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.55@101,97 dx=17.2 idx=8/20 dist=34/284 right=1:-29.91@115,88 dx=31.3 idx=0/9 dist=18/18 sel=1:-22.58@104,95 dx=19.9 idx=0/16 dist=32/238 edge=1:-22.40@103.5,95.5 dx=19.5 width=48.3 l=88,77 r=119,114
CxScan: raw_ref=80.0 edge=103.5,95.5 best_raw_x=130 best_err=-0.40 best_cxcy=103.2,119.7 scan=0:-46.9,10:-44.6,20:-42.1,30:-39.4,40:-36.5,50:-33.3,60:-29.9,70:-26.3,80:-22.4,90:-18.3,100:-14.0,110:-9.6,120:-5.0,130:-0.4,140:4.2
ATGSeedDiag: seed=1@4,97/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(74.9) imip=15/35 pass=11110 acc=-1 ipm=91.4,74.6 inv=82.4,41.6 | 5(68.5) imip=0/9 pass=11111 acc=5 ipm=112.2,109.9 inv=133.2,86.2
frame=877 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=143/9 raw=170/55 sel=143/121 far=0/0 far_raw=0/0 l=0@-1/1@5 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=76.4/75.9/0.0/0.0 dist=0 m0=(84,119) ml=(102,96) md=34/1/194 cxcy=84.0,119.6 guide=-20.32 atg=60.0/6.0/4.0 pure=-5.38/-1.11 yaw=1219 cmd=1019 actual=1505 signed=1 rps=2603/5397:3975/5454 duty=3/14
ATGCorner: L=0@-1/1@5 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/112.4,110.2:134.1,87.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=25:91.1,74.4:82.1,41.5:76.4:11110/5:112.4,110.2:134.1,87.1:75.9:11111 seed_src=none/lpt seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=76.4/75.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@5 nearNum=143/9 centerNum=143/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=143/121 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.59@99,99 dx=14.8 idx=8/19 dist=31/279 right=1:-29.50@114,89 dx=30.5 idx=0/8 dist=16/16 sel=1:-22.51@104,95 dx=19.8 idx=0/16 dist=32/240 edge=1:-21.56@102.5,96.0 dx=18.5 width=47.8 l=88,77 r=117,115
CxScan: raw_ref=80.0 edge=102.5,96.0 best_raw_x=130 best_err=0.82 best_cxcy=103.2,119.7 scan=0:-46.6,10:-44.3,20:-41.7,30:-38.9,40:-36.0,50:-32.7,60:-29.2,70:-25.5,80:-21.6,90:-17.4,100:-13.0,110:-8.5,120:-3.9,130:0.8,140:5.5
ATGSeedDiag: seed=1@4,97/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(76.4) imip=15/35 pass=11110 acc=-1 ipm=91.1,74.4 inv=82.1,41.5 | 5(75.9) imip=0/8 pass=11111 acc=5 ipm=112.4,110.2 inv=134.1,87.1
frame=878 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=139/10 raw=170/59 sel=139/113 far=0/0 far_raw=0/0 l=0@-1/1@8 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=76.2/125.7/0.0/0.0 dist=0 m0=(84,119) ml=(102,96) md=34/1/195 cxcy=84.0,119.6 guide=-20.93 atg=60.0/3.0/3.0 pure=-5.05/-0.91 yaw=1256 cmd=1056 actual=1509 signed=1 rps=2553/5447:4032/5351 duty=3/15
ATGCorner: L=0@-1/1@8 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/117.2,115.0:153.5,100.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=24:89.6,75.5:80.6,42.2:76.2:11110/8:117.2,115.0:153.5,100.0:125.7:11111 seed_src=none/lpt seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=76.2/125.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@8 nearNum=139/10 centerNum=139/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=139/113 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.77@100,97 dx=16.3 idx=8/19 dist=32/256 right=1:-32.48@117,91 dx=33.0 idx=0/9 dist=18/18 sel=1:-22.17@104,95 dx=19.6 idx=0/16 dist=32/224 edge=1:-21.45@102.0,97.0 dx=18.0 width=48.8 l=88,77 r=116,117
CxScan: raw_ref=80.0 edge=102.0,97.0 best_raw_x=125 best_err=-0.93 best_cxcy=101.3,119.7 scan=0:-46.9,10:-44.6,20:-42.0,30:-39.2,40:-36.1,50:-32.8,60:-29.3,70:-25.5,80:-21.4,90:-17.2,100:-12.7,110:-8.0,120:-3.3,130:1.5,140:6.2
ATGSeedDiag: seed=1@4,97/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=24(76.2) imip=14/34 pass=11110 acc=-1 ipm=89.6,75.5 inv=80.6,42.2 | 8(125.7) imip=0/9 pass=11111 acc=8 ipm=117.2,115.0 inv=153.5,100.0
frame=879 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=138/9 raw=170/45 sel=138/116 far=0/0 far_raw=0/0 l=0@-1/1@5 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=75.6/93.7/0.0/0.0 dist=0 m0=(84,119) ml=(102,96) md=34/1/197 cxcy=84.0,119.6 guide=-20.72 atg=60.0/2.0/2.0 pure=-4.86/-0.75 yaw=1243 cmd=1043 actual=1502 signed=1 rps=2570/5430:3861/5009 duty=3/15
ATGCorner: L=0@-1/1@5 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/112.7,110.9:135.9,88.8 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=23:88.1,77.3:79.3,43.6:75.6:11110/5:112.7,110.9:135.9,88.8:93.7:11111 seed_src=none/lpt seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=75.6/93.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@5 nearNum=138/9 centerNum=138/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=138/116 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.55@101,97 dx=17.2 idx=8/19 dist=34/263 right=1:-32.42@117,91 dx=32.9 idx=0/8 dist=16/16 sel=1:-22.08@103,95 dx=19.4 idx=0/16 dist=32/230 edge=1:-21.45@102.0,97.0 dx=18.0 width=48.8 l=88,77 r=116,117
CxScan: raw_ref=80.0 edge=102.0,97.0 best_raw_x=125 best_err=-0.93 best_cxcy=101.3,119.7 scan=0:-46.9,10:-44.6,20:-42.0,30:-39.2,40:-36.1,50:-32.8,60:-29.3,70:-25.5,80:-21.4,90:-17.2,100:-12.7,110:-8.0,120:-3.3,130:1.5,140:6.2
ATGSeedDiag: seed=1@4,97/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(75.6) imip=13/33 pass=11110 acc=-1 ipm=88.1,77.3 inv=79.3,43.6 | 5(93.7) imip=0/8 pass=11111 acc=5 ipm=112.7,110.9 inv=135.9,88.8
frame=880 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=138/8 raw=170/57 sel=138/114 far=0/0 far_raw=0/0 l=0@-1/1@4 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=76.6/74.1/0.0/0.0 dist=0 m0=(84,119) ml=(102,96) md=34/1/198 cxcy=84.0,119.6 guide=-20.72 atg=60.0/1.0/1.0 pure=-4.63/-0.59 yaw=1243 cmd=1043 actual=1493 signed=1 rps=2570/5430:4158/5281 duty=3/15
ATGCorner: L=0@-1/1@4 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/110.4,111.4:132.1,90.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=23:87.6,76.7:78.7,43.1:76.6:11110/4:110.4,111.4:132.1,90.1:74.1:11111 seed_src=none/lpt seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=76.6/74.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@4 nearNum=138/8 centerNum=138/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=138/114 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.86@99,98 dx=15.2 idx=8/18 dist=32/258 right=1:-29.70@114,90 dx=30.2 idx=0/7 dist=14/14 sel=1:-21.91@103,95 dx=19.3 idx=0/16 dist=32/226 edge=1:-20.10@101.5,95.0 dx=17.5 width=51.0 l=87,74 r=116,116
CxScan: raw_ref=80.0 edge=101.5,95.0 best_raw_x=125 best_err=-0.29 best_cxcy=101.3,119.7 scan=0:-45.4,10:-43.0,20:-40.4,30:-37.6,40:-34.6,50:-31.3,60:-27.8,70:-24.1,80:-20.1,90:-15.9,100:-11.6,110:-7.1,120:-2.6,130:2.0,140:6.5
ATGSeedDiag: seed=1@4,97/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(76.6) imip=13/33 pass=11110 acc=-1 ipm=87.6,76.7 inv=78.7,43.1 | 4(74.1) imip=0/7 pass=11111 acc=4 ipm=110.4,111.4 inv=132.1,90.1
frame=881 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=139/8 raw=170/49 sel=139/115 far=0/0 far_raw=0/0 l=0@-1/1@4 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=77.4/87.1/0.0/0.0 dist=0 m0=(84,119) ml=(101,96) md=33/1/204 cxcy=84.0,119.6 guide=-19.27 atg=60.0/0.0/0.0 pure=-4.15/-0.25 yaw=1156 cmd=956 actual=1470 signed=1 rps=2689/5311:4353/5555 duty=3/14
ATGCorner: L=0@-1/1@4 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/111.0,111.9:134.0,91.3 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=22:85.6,77.9:76.7,44.0:77.4:11110/4:111.0,111.9:134.0,91.3:87.1:11111 seed_src=none/lpt seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=77.4/87.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@4 nearNum=139/8 centerNum=139/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=139/115 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.20@100,97 dx=16.1 idx=8/18 dist=34/256 right=1:-33.15@117,92 dx=33.4 idx=0/7 dist=14/14 sel=1:-21.17@103,94 dx=18.8 idx=0/16 dist=32/228 edge=1:-19.25@100.0,97.0 dx=16.0 width=51.6 l=85,76 r=115,118
CxScan: raw_ref=80.0 edge=100.0,97.0 best_raw_x=120 best_err=-0.82 best_cxcy=99.3,119.7 scan=0:-45.7,10:-43.3,20:-40.6,30:-37.6,40:-34.5,50:-31.0,60:-27.4,70:-23.4,80:-19.2,90:-14.9,100:-10.3,110:-5.6,120:-0.8,130:4.0,140:8.7
ATGSeedDiag: seed=1@4,96/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=22(77.4) imip=12/32 pass=11110 acc=-1 ipm=85.6,77.9 inv=76.7,44.0 | 4(87.1) imip=0/7 pass=11111 acc=4 ipm=111.0,111.9 inv=134.0,91.3
frame=883 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=147/0 raw=170/0 sel=147/121 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=77.3/0.0/0.0/0.0 dist=14 m0=(84,119) ml=(101,95) md=34/1/208 cxcy=84.0,119.6 guide=-18.71 atg=60.0/0.0/0.0 pure=-3.67/0.04 yaw=1123 cmd=923 actual=1443 signed=1 rps=2735/5265:4542/5885 duty=3/13
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=21:83.7,78.7:74.6,44.7:77.3:11110/-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000 seed_src=none/lost seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=77.3/0.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=147/0 centerNum=147/0 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=147/121 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.68@99,97 dx=14.6 idx=8/17 dist=33/284 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-20.25@102,94 dx=18.2 idx=0/16 dist=32/240 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=81,73 r=-1,-1
ATGSeedDiag: seed=1@4,96/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=21(77.3) imip=11/31 pass=11110 acc=-1 ipm=83.7,78.7 inv=74.6,44.7 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=884 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=146/7 raw=170/55 sel=146/121 far=0/0 far_raw=0/0 l=0@-1/1@3 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=77.5/68.9/0.0/0.0 dist=28 m0=(84,119) ml=(100,95) md=33/1/211 cxcy=84.0,119.6 guide=-18.96 atg=60.0/0.0/0.0 pure=-3.45/0.23 yaw=1138 cmd=938 actual=1427 signed=1 rps=2715/5285:4400/5601 duty=3/14
ATGCorner: L=0@-1/1@3 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/109.0,112.9:131.5,94.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=21:82.8,78.3:73.6,44.3:77.5:11110/3:109.0,112.9:131.5,94.0:68.9:11111 seed_src=none/lpt seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=77.5/68.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@3 nearNum=146/7 centerNum=146/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=146/121 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.16@99,96 dx=15.3 idx=8/17 dist=34/278 right=1:-31.29@116,91 dx=31.5 idx=0/6 dist=12/12 sel=1:-19.98@102,93 dx=17.9 idx=0/16 dist=32/240 edge=1:-15.35@97.0,95.5 dx=13.0 width=54.8 l=80,74 r=114,117
CxScan: raw_ref=80.0 edge=97.0,95.5 best_raw_x=115 best_err=0.52 best_cxcy=97.4,119.7 scan=0:-42.9,10:-40.3,20:-37.4,30:-34.3,40:-31.0,50:-27.4,60:-23.6,70:-19.6,80:-15.4,90:-10.9,100:-6.4,110:-1.8,120:2.8,130:7.4,140:11.9
ATGSeedDiag: seed=1@4,96/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=21(77.5) imip=11/31 pass=11110 acc=-1 ipm=82.8,78.3 inv=73.6,44.3 | 3(68.9) imip=0/6 pass=11111 acc=3 ipm=109.0,112.9 inv=131.5,94.0
frame=885 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=140/7 raw=170/54 sel=140/115 far=0/0 far_raw=0/0 l=0@-1/1@3 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=78.8/67.6/0.0/0.0 dist=42 m0=(84,119) ml=(102,94) md=33/1/209 cxcy=84.0,119.6 guide=-19.78 atg=50.0/0.0/0.0 pure=-2.99/0.41 yaw=1187 cmd=987 actual=1405 signed=1 rps=2648/5352:4581/5761 duty=3/14
ATGCorner: L=0@-1/1@3 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/109.4,113.2:132.8,94.9 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=20:82.2,80.5:73.0,46.0:78.8:11110/3:109.4,113.2:132.8,94.9:67.6:11111 seed_src=none/lpt seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=78.8/67.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@3 nearNum=140/7 centerNum=140/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=140/115 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.74@100,96 dx=16.0 idx=9/17 dist=34/262 right=1:-31.79@116,91 dx=32.0 idx=0/6 dist=12/12 sel=1:-20.72@103,92 dx=19.2 idx=0/16 dist=32/228 edge=1:-13.51@95.5,95.0 dx=11.5 width=57.5 l=77,73 r=114,117
CxScan: raw_ref=80.0 edge=95.5,95.0 best_raw_x=110 best_err=0.02 best_cxcy=95.5,119.6 scan=0:-41.6,10:-38.9,20:-36.0,30:-32.8,40:-29.4,50:-25.7,60:-21.9,70:-17.8,80:-13.5,90:-9.1,100:-4.6,110:0.0,120:4.6,130:9.1,140:13.5
ATGSeedDiag: seed=1@4,96/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=20(78.8) imip=10/30 pass=11110 acc=-1 ipm=82.2,80.5 inv=73.0,46.0 | 3(67.6) imip=0/6 pass=11111 acc=3 ipm=109.4,113.2 inv=132.8,94.9
frame=886 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=140/6 raw=170/42 sel=140/118 far=0/0 far_raw=0/0 l=0@-1/1@2 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=78.2/74.5/0.0/0.0 dist=56 m0=(84,119) ml=(102,93) md=34/1/211 cxcy=84.0,119.6 guide=-19.17 atg=39.0/-1.0/-1.0 pure=-2.62/0.54 yaw=1150 cmd=950 actual=1389 signed=1 rps=2698/5302:4420/5539 duty=3/14
ATGCorner: L=0@-1/1@2 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/107.5,113.9:129.9,97.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=20:80.9,79.7:71.5,45.4:78.2:11110/2:107.5,113.9:129.9,97.1:74.5:11111 seed_src=none/none seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=78.2/74.5/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@2 nearNum=140/6 centerNum=140/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=140/118 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.23@101,94 dx=17.0 idx=9/17 dist=34/266 right=1:-34.05@118,93 dx=33.8 idx=0/5 dist=10/10 sel=1:-20.49@103,91 dx=19.2 idx=0/16 dist=32/234 edge=1:-11.80@94.0,95.0 dx=10.0 width=59.7 l=75,72 r=113,118
CxScan: raw_ref=80.0 edge=94.0,95.0 best_raw_x=105 best_err=-0.47 best_cxcy=93.6,119.6 scan=0:-40.6,10:-37.8,20:-34.8,30:-31.5,40:-28.0,50:-24.3,60:-20.3,70:-16.1,80:-11.8,90:-7.3,100:-2.8,110:1.8,120:6.4,130:10.8,140:15.2
ATGSeedDiag: seed=1@4,96/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=20(78.2) imip=10/30 pass=11110 acc=-1 ipm=80.9,79.7 inv=71.5,45.4 | 2(74.5) imip=0/5 pass=11111 acc=2 ipm=107.5,113.9 inv=129.9,97.1
frame=887 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=139/6 raw=170/52 sel=139/114 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=78.4/70.0/0.0/0.0 dist=70 m0=(84,119) ml=(102,93) md=33/1/212 cxcy=84.0,119.6 guide=-19.55 atg=32.0/-2.0/-1.0 pure=-2.32/0.66 yaw=1173 cmd=992 actual=1353 signed=1 rps=2640/5360:4529/5638 duty=3/14
ATGCorner: L=0@-1/1@1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/105.5,114.8:126.8,99.7 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=19:80.2,81.9:70.6,47.2:78.4:11110/1:105.5,114.8:126.8,99.7:70.0:11111 seed_src=none/none seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=78.4/70.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@1 nearNum=139/6 centerNum=139/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=139/114 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.42@101,93 dx=17.5 idx=9/17 dist=34/260 right=1:-33.29@117,92 dx=33.3 idx=0/5 dist=10/10 sel=1:-20.43@103,91 dx=19.4 idx=0/16 dist=32/226 edge=1:-9.96@92.5,94.5 dx=8.5 width=62.4 l=72,71 r=113,118
CxScan: raw_ref=80.0 edge=92.5,94.5 best_raw_x=100 best_err=-0.96 best_cxcy=91.7,119.6 scan=0:-39.2,10:-36.3,20:-33.2,30:-29.9,40:-26.3,50:-22.5,60:-18.5,70:-14.3,80:-10.0,90:-5.5,100:-1.0,110:3.6,120:8.1,130:12.4,140:16.7
ATGSeedDiag: seed=1@4,96/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=19(78.4) imip=9/29 pass=11110 acc=-1 ipm=80.2,81.9 inv=70.6,47.2 | 1(70.0) imip=0/5 pass=11111 acc=1 ipm=105.5,114.8 inv=126.8,99.7
frame=888 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=6 speed=0 near=139/6 raw=170/47 sel=139/118 far=0/0 far_raw=0/0 l=0@-1/1@1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=78.4/66.4/0.0/0.0 dist=83 m0=(84,119) ml=(101,94) md=33/1/215 cxcy=84.0,119.6 guide=-18.92 atg=29.0/-3.0/-2.0 pure=-2.30/0.84 yaw=1135 cmd=937 actual=1333 signed=1 rps=2715/5285:4272/5233 duty=3/14
ATGCorner: L=0@-1/1@1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/105.7,114.9:127.6,100.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=19:79.3,81.3:69.6,46.7:78.4:11110/1:105.7,114.9:127.6,100.1:66.4:11111 seed_src=none/none seed=40.0,91.8/67.4,27.7 far_start=67,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=78.4/66.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@1 nearNum=139/6 centerNum=139/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=139/118 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-17.81@99,95 dx=15.2 idx=8/16 dist=34/262 right=1:-33.82@118,92 dx=33.8 idx=0/5 dist=10/10 sel=1:-19.59@102,92 dx=18.1 idx=0/16 dist=32/234 edge=1:-9.29@92.0,94.0 dx=8.0 width=63.8 l=71,70 r=113,118
CxScan: raw_ref=80.0 edge=92.0,94.0 best_raw_x=100 best_err=-0.37 best_cxcy=91.7,119.6 scan=0:-38.6,10:-35.7,20:-32.6,30:-29.2,40:-25.6,50:-21.8,60:-17.8,70:-13.6,80:-9.3,90:-4.9,100:-0.4,110:4.1,120:8.5,130:12.9,140:17.0
ATGSeedDiag: seed=1@4,96/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=19(78.4) imip=9/29 pass=11110 acc=-1 ipm=79.3,81.3 inv=69.6,46.7 | 1(66.4) imip=0/5 pass=11111 acc=1 ipm=105.7,114.9 inv=127.6,100.1

- stopped_at: 2026-06-22T01:19:54+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive26
```
