# drive43

- commit: 51cfb97
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive43-front_car_circle_drive43.log
- remote_log: /tmp/front_car_circle_drive43.log
- started_at: 2026-06-22T02:28:36+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive43 6
```

4539 /tmp/front_car_circle_drive43.log
CxScan: raw_ref=80.0 edge=104.5,92.5 best_raw_x=135 best_err=0.66 best_cxcy=105.1,119.7 scan=0:-45.7,10:-43.4,20:-41.0,30:-38.4,40:-35.5,50:-32.5,60:-29.3,70:-25.8,80:-22.2,90:-18.3,100:-14.3,110:-10.1,120:-5.8,130:-1.5,140:2.8
ATGSeedDiag: seed=1@4,102/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=36(67.8) imip=26/46 pass=11110 acc=-1 ipm=113.6,64.8 inv=101.7,35.6 | 10(122.3) imip=0/11 pass=11111 acc=10 ipm=123.1,106.4 inv=147.9,78.5
frame=879 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=130/12 raw=170/50 sel=130/110 far=0/0 far_raw=0/0 l=0@-1/1@10 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=69.4/99.5/0.0/0.0 dist=553 m0=(84,119) ml=(102,98) md=32/1/163 cxcy=84.0,119.6 guide=-23.22 atg=60.0/60.0/60.0 pure=-8.74/-4.14 yaw=1393 cmd=1306 actual=1481 signed=1 rps=2011/5589:4061/5332 duty=2/16
ATGCorner: L=0@-1/1@10 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/122.2,107.7:148.6,81.2 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=35:112.3,66.5:101.1,36.5:69.4:11110/10:122.2,107.7:148.6,81.2:99.5:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=69.4/99.5/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@10 nearNum=130/12 centerNum=130/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=130/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.04@100,99 dx=15.9 idx=7/24 dist=33/269 right=1:-28.88@116,85 dx=32.0 idx=0/11 dist=26/26 sel=1:-24.14@104,97 dx=20.4 idx=0/16 dist=32/218 edge=1:-20.63@102.0,95.0 dx=18.0 width=51.6 l=81,80 r=123,110
CxScan: raw_ref=80.0 edge=102.0,95.0 best_raw_x=125 best_err=-0.89 best_cxcy=101.3,119.7 scan=0:-45.7,10:-43.3,20:-40.8,30:-38.0,40:-35.0,50:-31.7,60:-28.3,70:-24.6,80:-20.6,90:-16.5,100:-12.2,110:-7.7,120:-3.2,130:1.4,140:5.9
ATGSeedDiag: seed=1@4,101/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=35(69.4) imip=25/45 pass=11110 acc=-1 ipm=112.3,66.5 inv=101.1,36.5 | 10(99.5) imip=0/11 pass=11111 acc=10 ipm=122.2,107.7 inv=148.6,81.2
frame=880 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=131/12 raw=170/49 sel=131/110 far=0/0 far_raw=0/0 l=0@-1/1@9 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=68.6/100.1/0.0/0.0 dist=566 m0=(84,119) ml=(102,98) md=32/1/163 cxcy=84.0,119.6 guide=-22.97 atg=60.0/60.0/60.0 pure=-8.62/-3.99 yaw=1378 cmd=1286 actual=1470 signed=1 rps=2038/5562:4304/5367 duty=1/16
ATGCorner: L=0@-1/1@9 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/120.7,106.0:143.1,77.7 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=34:110.4,67.4:99.6,37.1:68.6:11110/9:120.7,106.0:143.1,77.7:100.1:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=68.6/100.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@9 nearNum=131/12 centerNum=131/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=131/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.50@100,99 dx=16.3 idx=7/24 dist=33/269 right=1:-28.98@116,85 dx=32.0 idx=0/11 dist=26/26 sel=1:-24.03@104,97 dx=20.3 idx=0/16 dist=32/218 edge=1:-20.10@101.5,95.0 dx=17.5 width=50.8 l=81,80 r=122,110
CxScan: raw_ref=80.0 edge=101.5,95.0 best_raw_x=125 best_err=-0.29 best_cxcy=101.3,119.7 scan=0:-45.4,10:-43.0,20:-40.4,30:-37.6,40:-34.6,50:-31.3,60:-27.8,70:-24.1,80:-20.1,90:-15.9,100:-11.6,110:-7.1,120:-2.6,130:2.0,140:6.5
ATGSeedDiag: seed=1@4,101/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=34(68.6) imip=24/44 pass=11110 acc=-1 ipm=110.4,67.4 inv=99.6,37.1 | 9(100.1) imip=0/11 pass=11111 acc=9 ipm=120.7,106.0 inv=143.1,77.7
frame=881 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=131/12 raw=170/49 sel=131/110 far=0/0 far_raw=0/0 l=0@-1/1@9 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=69.6/105.6/0.0/0.0 dist=580 m0=(84,119) ml=(102,98) md=32/1/165 cxcy=84.0,119.6 guide=-22.79 atg=60.0/60.0/55.0 pure=-8.53/-3.87 yaw=1367 cmd=1290 actual=1444 signed=1 rps=2032/5568:4268/5193 duty=2/16
ATGCorner: L=0@-1/1@9 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/120.9,106.4:143.9,78.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=34:109.7,66.7:98.7,36.7:69.6:11110/9:120.9,106.4:143.9,78.4:105.6:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=69.6/105.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@9 nearNum=131/12 centerNum=131/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=131/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.87@101,99 dx=16.7 idx=7/24 dist=34/262 right=1:-29.26@116,85 dx=32.1 idx=0/11 dist=26/26 sel=1:-23.89@104,97 dx=20.2 idx=0/16 dist=32/218 edge=1:-21.15@102.5,95.0 dx=18.5 width=50.4 l=83,79 r=122,111
CxScan: raw_ref=80.0 edge=102.5,95.0 best_raw_x=130 best_err=0.80 best_cxcy=103.2,119.7 scan=0:-46.0,10:-43.6,20:-41.1,30:-38.3,40:-35.4,50:-32.2,60:-28.7,70:-25.1,80:-21.1,90:-17.0,100:-12.7,110:-8.3,120:-3.8,130:0.8,140:5.4
ATGSeedDiag: seed=1@4,100/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=34(69.6) imip=24/44 pass=11110 acc=-1 ipm=109.7,66.7 inv=98.7,36.7 | 9(105.6) imip=0/11 pass=11111 acc=9 ipm=120.9,106.4 inv=143.9,78.4
frame=882 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=132/12 raw=170/50 sel=132/111 far=0/0 far_raw=0/0 l=0@-1/1@9 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=69.7/109.9/0.0/0.0 dist=594 m0=(84,119) ml=(102,98) md=32/1/166 cxcy=84.0,119.6 guide=-22.79 atg=60.0/60.0/52.0 pure=-8.37/-3.69 yaw=1367 cmd=1279 actual=1456 signed=1 rps=2048/5552:4468/5572 duty=1/15
ATGCorner: L=0@-1/1@9 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/120.8,106.7:144.4,79.1 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=33:108.2,67.8:97.6,37.3:69.7:11110/9:120.8,106.7:144.4,79.1:109.9:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=69.7/109.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@9 nearNum=132/12 centerNum=132/12 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=132/111 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.78@102,98 dx=17.7 idx=7/24 dist=34/272 right=1:-29.28@116,86 dx=32.0 idx=0/11 dist=26/26 sel=1:-24.00@104,97 dx=20.2 idx=0/16 dist=32/220 edge=1:-21.98@103.5,94.5 dx=19.5 width=49.6 l=85,78 r=122,111
CxScan: raw_ref=80.0 edge=103.5,94.5 best_raw_x=130 best_err=-0.39 best_cxcy=103.2,119.7 scan=0:-46.3,10:-44.0,20:-41.5,30:-38.8,40:-35.9,50:-32.8,60:-29.4,70:-25.8,80:-22.0,90:-17.9,100:-13.7,110:-9.4,120:-4.9,130:-0.4,140:4.1
ATGSeedDiag: seed=1@4,100/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=33(69.7) imip=23/43 pass=11110 acc=-1 ipm=108.2,67.8 inv=97.6,37.3 | 9(109.9) imip=0/11 pass=11111 acc=9 ipm=120.8,106.7 inv=144.4,79.1
frame=883 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=131/11 raw=170/48 sel=131/110 far=0/0 far_raw=0/0 l=0@-1/1@9 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=70.9/98.2/0.0/0.0 dist=608 m0=(84,119) ml=(104,97) md=34/1/168 cxcy=84.0,119.6 guide=-23.02 atg=60.0/60.0/48.0 pure=-8.35/-3.57 yaw=1381 cmd=1274 actual=1488 signed=1 rps=2054/5546:4255/5526 duty=2/15
ATGCorner: L=0@-1/1@9 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/120.3,108.6:146.9,83.3 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=33:107.7,67.5:97.1,37.1:70.9:11110/9:120.3,108.6:146.9,83.3:98.2:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=70.9/98.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@9 nearNum=131/11 centerNum=131/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=131/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.87@100,100 dx=15.5 idx=7/23 dist=34/269 right=1:-27.18@113,86 dx=29.2 idx=0/10 dist=20/20 sel=1:-24.10@104,97 dx=20.3 idx=0/16 dist=32/218 edge=1:-22.28@104.0,94.0 dx=20.0 width=48.1 l=87,77 r=121,111
CxScan: raw_ref=80.0 edge=104.0,94.0 best_raw_x=130 best_err=-0.97 best_cxcy=103.2,119.7 scan=0:-46.3,10:-44.0,20:-41.5,30:-38.9,40:-36.0,50:-32.9,60:-29.6,70:-26.0,80:-22.3,90:-18.3,100:-14.2,110:-9.9,120:-5.4,130:-1.0,140:3.5
ATGSeedDiag: seed=1@4,100/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=33(70.9) imip=23/43 pass=11110 acc=-1 ipm=107.7,67.5 inv=97.1,37.1 | 9(98.2) imip=0/10 pass=11111 acc=9 ipm=120.3,108.6 inv=146.9,83.3
frame=884 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=128/11 raw=170/47 sel=128/107 far=0/0 far_raw=0/0 l=0@-1/1@9 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=70.2/99.1/0.0/0.0 dist=622 m0=(84,119) ml=(103,99) md=32/1/169 cxcy=84.0,119.6 guide=-24.16 atg=60.0/53.0/43.0 pure=-8.11/-3.36 yaw=1449 cmd=1393 actual=1505 signed=1 rps=1891/5709:4325/5845 duty=1/16
ATGCorner: L=0@-1/1@9 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/120.1,109.2:147.3,84.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=32:106.0,68.3:95.7,37.6:70.2:11110/9:120.1,109.2:147.3,84.4:99.1:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=70.2/99.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@9 nearNum=128/11 centerNum=128/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=128/107 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.57@101,99 dx=17.1 idx=7/23 dist=34/255 right=1:-27.49@113,86 dx=29.4 idx=0/10 dist=20/20 sel=1:-24.60@105,98 dx=20.7 idx=0/16 dist=32/212 edge=1:-21.47@103.0,94.5 dx=19.0 width=48.8 l=85,78 r=121,111
CxScan: raw_ref=80.0 edge=103.0,94.5 best_raw_x=130 best_err=0.20 best_cxcy=103.2,119.7 scan=0:-46.0,10:-43.7,20:-41.1,30:-38.4,40:-35.5,50:-32.3,60:-28.9,70:-25.3,80:-21.5,90:-17.4,100:-13.2,110:-8.8,120:-4.3,130:0.2,140:4.7
ATGSeedDiag: seed=1@4,100/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=32(70.2) imip=22/42 pass=11110 acc=-1 ipm=106.0,68.3 inv=95.7,37.6 | 9(99.1) imip=0/10 pass=11111 acc=9 ipm=120.1,109.2 inv=147.3,84.4
frame=885 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=127/11 raw=170/47 sel=127/105 far=0/0 far_raw=0/0 l=0@-1/1@8 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=71.4/103.9/0.0/0.0 dist=636 m0=(84,119) ml=(103,99) md=32/1/171 cxcy=84.0,119.6 guide=-24.34 atg=60.0/50.0/41.0 pure=-8.02/-3.21 yaw=1460 cmd=1408 actual=1512 signed=1 rps=1870/5730:4143/5567 duty=1/16
ATGCorner: L=0@-1/1@8 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/118.9,107.3:142.0,80.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=31:104.6,70.6:95.0,38.9:71.4:11110/8:118.9,107.3:142.0,80.4:103.9:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=71.4/103.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@8 nearNum=127/11 centerNum=127/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=127/105 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-21.90@102,99 dx=17.5 idx=7/23 dist=34/246 right=1:-27.56@113,87 dx=29.3 idx=0/10 dist=20/20 sel=1:-24.92@105,98 dx=21.0 idx=0/16 dist=32/208 edge=1:-21.98@103.5,94.5 dx=19.5 width=48.1 l=87,77 r=120,112
CxScan: raw_ref=80.0 edge=103.5,94.5 best_raw_x=130 best_err=-0.39 best_cxcy=103.2,119.7 scan=0:-46.3,10:-44.0,20:-41.5,30:-38.8,40:-35.9,50:-32.8,60:-29.4,70:-25.8,80:-22.0,90:-17.9,100:-13.7,110:-9.4,120:-4.9,130:-0.4,140:4.1
ATGSeedDiag: seed=1@4,100/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=31(71.4) imip=21/41 pass=11110 acc=-1 ipm=104.6,70.6 inv=95.0,38.9 | 8(103.9) imip=0/10 pass=11111 acc=8 ipm=118.9,107.3 inv=142.0,80.4
frame=886 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=131/11 raw=170/47 sel=131/110 far=0/0 far_raw=0/0 l=0@-1/1@8 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=70.4/99.8/0.0/0.0 dist=650 m0=(84,119) ml=(104,98) md=33/1/172 cxcy=84.0,119.6 guide=-23.35 atg=60.0/45.0/37.0 pure=-7.87/-3.09 yaw=1401 cmd=1278 actual=1524 signed=1 rps=2048/5552:4314/5866 duty=1/15
ATGCorner: L=0@-1/1@8 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/118.9,108.6:144.2,83.3 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=30:102.7,71.4:93.3,39.5:70.4:11110/8:118.9,108.6:144.2,83.3:99.8:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=70.4/99.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@8 nearNum=131/11 centerNum=131/11 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=131/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.99@100,100 dx=15.5 idx=7/22 dist=32/255 right=1:-29.38@115,87 dx=31.1 idx=0/10 dist=20/20 sel=1:-24.29@104,98 dx=20.4 idx=0/16 dist=32/218 edge=1:-22.70@104.0,95.0 dx=20.0 width=48.2 l=88,77 r=120,113
CxScan: raw_ref=80.0 edge=104.0,95.0 best_raw_x=130 best_err=-0.99 best_cxcy=103.2,119.7 scan=0:-46.9,10:-44.6,20:-42.1,30:-39.4,40:-36.6,50:-33.4,60:-30.1,70:-26.5,80:-22.7,90:-18.7,100:-14.4,110:-10.1,120:-5.6,130:-1.0,140:3.6
ATGSeedDiag: seed=1@4,100/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(70.4) imip=20/40 pass=11110 acc=-1 ipm=102.7,71.4 inv=93.3,39.5 | 8(99.8) imip=0/10 pass=11111 acc=8 ipm=118.9,108.6 inv=144.2,83.3
frame=887 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=134/10 raw=170/45 sel=134/112 far=0/0 far_raw=0/0 l=0@-1/1@8 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=71.4/90.1/0.0/0.0 dist=664 m0=(84,119) ml=(105,97) md=33/1/173 cxcy=84.0,119.6 guide=-23.86 atg=60.0/40.0/32.0 pure=-7.50/-2.88 yaw=1431 cmd=1323 actual=1540 signed=1 rps=1987/5613:4083/5646 duty=2/15
ATGCorner: L=0@-1/1@8 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/118.3,109.8:145.1,85.9 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=30:102.2,70.7:92.6,39.1:71.4:11110/8:118.3,109.8:145.1,85.9:90.1:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=71.4/90.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@8 nearNum=134/10 centerNum=134/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=134/112 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.99@100,99 dx=15.8 idx=8/22 dist=32/274 right=1:-26.70@112,87 dx=28.1 idx=0/9 dist=18/18 sel=1:-24.78@105,97 dx=21.3 idx=0/16 dist=32/222 edge=1:-21.47@103.0,94.5 dx=19.0 width=47.4 l=87,77 r=119,112
CxScan: raw_ref=80.0 edge=103.0,94.5 best_raw_x=130 best_err=0.20 best_cxcy=103.2,119.7 scan=0:-46.0,10:-43.7,20:-41.1,30:-38.4,40:-35.5,50:-32.3,60:-28.9,70:-25.3,80:-21.5,90:-17.4,100:-13.2,110:-8.8,120:-4.3,130:0.2,140:4.7
ATGSeedDiag: seed=1@4,98/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(71.4) imip=20/40 pass=11110 acc=-1 ipm=102.2,70.7 inv=92.6,39.1 | 8(90.1) imip=0/9 pass=11111 acc=8 ipm=118.3,109.8 inv=145.1,85.9
frame=888 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=136/10 raw=170/47 sel=136/112 far=0/0 far_raw=0/0 l=0@-1/1@7 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=71.9/93.8/0.0/0.0 dist=677 m0=(84,119) ml=(100,99) md=32/1/178 cxcy=84.0,119.6 guide=-22.01 atg=60.0/38.0/28.0 pure=-7.55/-2.83 yaw=1321 cmd=1121 actual=1556 signed=1 rps=2264/5336:4132/5707 duty=2/14
ATGCorner: L=0@-1/1@7 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/116.8,108.2:139.5,82.4 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=30:101.5,69.7:91.7,38.5:71.9:11110/7:116.8,108.2:139.5,82.4:93.8:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=71.9/93.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@7 nearNum=136/10 centerNum=136/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=136/112 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-20.70@101,99 dx=16.6 idx=7/22 dist=33/266 right=1:-26.97@112,87 dx=28.3 idx=0/9 dist=18/18 sel=1:-23.26@104,97 dx=19.6 idx=0/16 dist=32/222 edge=1:-21.47@103.0,94.5 dx=19.0 width=47.4 l=87,77 r=119,112
CxScan: raw_ref=80.0 edge=103.0,94.5 best_raw_x=130 best_err=0.20 best_cxcy=103.2,119.7 scan=0:-46.0,10:-43.7,20:-41.1,30:-38.4,40:-35.5,50:-32.3,60:-28.9,70:-25.3,80:-21.5,90:-17.4,100:-13.2,110:-8.8,120:-4.3,130:0.2,140:4.7
ATGSeedDiag: seed=1@4,98/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(71.9) imip=20/40 pass=11110 acc=-1 ipm=101.5,69.7 inv=91.7,38.5 | 7(93.8) imip=0/9 pass=11111 acc=7 ipm=116.8,108.2 inv=139.5,82.4
frame=889 line=1 track=0 cross=0 circle=2(CIRCLE_RIGHT_BEGIN) round=0 yroad=0 ramp=0 road=0 speed=0 near=136/10 raw=170/44 sel=136/111 far=0/0 far_raw=0/0 l=0@-1/1@7 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/1/0/0 lost=0/0 conf=72.5/98.0/0.0/0.0 dist=689 m0=(84,119) ml=(101,98) md=33/1/180 cxcy=84.0,119.6 guide=-21.12 atg=60.0/33.0/25.0 pure=-7.41/-2.64 yaw=1267 cmd=1067 actual=1550 signed=1 rps=2338/5262:3870/5281 duty=3/14
ATGCorner: L=0@-1/1@7 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/117.3,108.9:141.6,84.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=29:100.0,71.1:90.5,39.3:72.5:11110/7:117.3,108.9:141.6,84.0:98.0:11111 seed_src=none/lpt seed=19.0,51.0/55.4,24.6 far_start=55,0 far_raw=0/0 far_num=0/0 straight=0/0 far_straight=0/0 conf_deg=72.5/98.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@7 nearNum=136/10 centerNum=136/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=136/111 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.60@98,100 dx=14.3 idx=7/21 dist=31/270 right=1:-28.57@114,88 dx=30.0 idx=0/9 dist=18/18 sel=1:-23.10@103,97 dx=19.4 idx=0/16 dist=32/220 edge=1:-21.67@103.0,95.0 dx=19.0 width=48.2 l=87,77 r=119,113
CxScan: raw_ref=80.0 edge=103.0,95.0 best_raw_x=130 best_err=0.20 best_cxcy=103.2,119.7 scan=0:-46.3,10:-44.0,20:-41.4,30:-38.7,40:-35.8,50:-32.6,60:-29.2,70:-25.5,80:-21.7,90:-17.6,100:-13.3,110:-8.9,120:-4.4,130:0.2,140:4.8
ATGSeedDiag: seed=1@4,98/1@124,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(72.5) imip=19/39 pass=11110 acc=-1 ipm=100.0,71.1 inv=90.5,39.3 | 7(98.0) imip=0/9 pass=11111 acc=7 ipm=117.3,108.9 inv=141.6,84.0

- stopped_at: 2026-06-22T02:28:49+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive43
```
