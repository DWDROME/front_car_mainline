# drive135

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive135-front_car_circle_drive135.log
- remote_log: /tmp/front_car_circle_drive135.log
- started_at: 2026-06-22T15:06:17+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive135 6
```

4501 /tmp/front_car_circle_drive135.log
ATGSeedDiag: seed=1@4,92/1@118,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(77.0) imip=20/40 pass=11110 acc=-1 ipm=100.8,68.8 inv=90.7,37.9 | 9(94.3) imip=0/11 pass=11111 acc=9 ipm=118.3,109.3 inv=144.2,84.8
frame=920 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=150/10 raw=170/44 sel=150/130 far=0/0 far_raw=0/0 l=0@-1/1@8 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=77.5/87.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(99,99) md=32/1/187 cxcy=84.0,119.6 guide=-19.68 atg=60.0/33.0/21.0 pure=-7.63/-2.72 yaw=1181 cmd=1381 actual=465 signed=0 rps=1632/5416:5211/6165 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@8 nearNum=150/10 centerNum=150/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=150/130 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-16.63@97,100 dx=12.9 idx=7/21 dist=33/312 right=1:-26.77@112,86 dx=28.4 idx=0/9 dist=18/18 sel=1:-20.21@101,97 dx=16.7 idx=0/16 dist=32/258 edge=1:-21.26@103.0,94.0 dx=19.0 width=48.2 l=87,76 r=119,112
CxScan: raw_ref=80.0 edge=103.0,94.0 best_raw_x=130 best_err=0.20 best_cxcy=103.2,119.7 scan=0:-45.7,10:-43.4,20:-40.9,30:-38.1,40:-35.2,50:-32.1,60:-28.7,70:-25.1,80:-21.3,90:-17.2,100:-13.0,110:-8.7,120:-4.3,130:0.2,140:4.7
ATGSeedDiag: seed=1@4,93/1@121,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(77.5) imip=20/40 pass=11110 acc=-1 ipm=100.8,68.4 inv=90.6,37.7 | 8(87.2) imip=0/9 pass=11111 acc=8 ipm=118.2,109.5 inv=144.3,85.3
frame=921 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=150/10 raw=170/43 sel=150/128 far=0/0 far_raw=0/0 l=0@-1/1@8 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=76.9/96.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(101,98) md=32/1/185 cxcy=84.0,119.6 guide=-21.56 atg=60.0/28.0/18.0 pure=-7.24/-2.45 yaw=1293 cmd=1493 actual=574 signed=0 rps=1337/5430:5237/6121 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@8 nearNum=150/10 centerNum=150/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=150/128 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-18.21@98,100 dx=14.2 idx=8/21 dist=32/311 right=1:-27.30@113,87 dx=28.8 idx=0/9 dist=18/18 sel=1:-22.79@103,97 dx=19.4 idx=0/16 dist=32/254 edge=1:-22.07@104.0,93.5 dx=20.0 width=47.6 l=89,75 r=119,112
CxScan: raw_ref=80.0 edge=104.0,93.5 best_raw_x=130 best_err=-0.96 best_cxcy=103.2,119.7 scan=0:-46.0,10:-43.7,20:-41.2,30:-38.6,40:-35.7,50:-32.6,60:-29.3,70:-25.8,80:-22.1,90:-18.1,100:-14.0,110:-9.8,120:-5.4,130:-1.0,140:3.5
ATGSeedDiag: seed=1@4,94/1@122,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(76.9) imip=19/39 pass=11110 acc=-1 ipm=99.7,70.3 inv=90.1,38.8 | 8(96.2) imip=0/9 pass=11111 acc=8 ipm=118.3,110.2 inv=145.9,86.9
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=141/10 raw=170/41 sel=141/120 far=0/0 far_raw=0/0 l=0@-1/1@7 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=76.8/89.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(102,98) md=32/1/184 cxcy=84.0,119.6 guide=-22.71 atg=60.0/24.0/17.0 pure=-7.05/-2.26 yaw=1363 cmd=1563 actual=696 signed=0 rps=1155/5438:5258/6143 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@7 nearNum=141/10 centerNum=141/10 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=141/120 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.82@100,100 dx=15.6 idx=8/21 dist=33/295 right=1:-29.22@115,88 dx=30.7 idx=0/9 dist=18/18 sel=1:-23.89@104,97 dx=20.4 idx=0/16 dist=32/238 edge=1:-22.40@103.5,95.5 dx=19.5 width=48.3 l=88,77 r=119,114
CxScan: raw_ref=80.0 edge=103.5,95.5 best_raw_x=130 best_err=-0.40 best_cxcy=103.2,119.7 scan=0:-46.9,10:-44.6,20:-42.1,30:-39.4,40:-36.5,50:-33.3,60:-29.9,70:-26.3,80:-22.4,90:-18.3,100:-14.0,110:-9.6,120:-5.0,130:-0.4,140:4.2
ATGSeedDiag: seed=1@4,95/1@123,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(76.8) imip=19/39 pass=11110 acc=-1 ipm=99.2,70.2 inv=89.6,38.8 | 7(89.0) imip=0/9 pass=11111 acc=7 ipm=117.2,109.4 inv=142.2,85.1
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=134/9 raw=170/39 sel=134/111 far=0/0 far_raw=0/0 l=0@-1/1@7 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=77.1/91.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(103,99) md=32/1/182 cxcy=84.0,119.6 guide=-24.17 atg=60.0/21.0/17.0 pure=-6.97/-2.14 yaw=1450 cmd=1650 actual=794 signed=0 rps=925/5449:5330/6138 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@7 nearNum=134/9 centerNum=134/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=134/111 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-19.23@98,102 dx=14.3 idx=8/20 dist=31/263 right=1:-27.96@113,88 dx=29.1 idx=0/8 dist=16/16 sel=1:-25.03@105,98 dx=21.1 idx=0/16 dist=32/220 edge=1:-23.99@105.5,94.5 dx=21.5 width=44.7 l=93,76 r=118,113
CxScan: raw_ref=80.0 edge=105.5,94.5 best_raw_x=135 best_err=-0.49 best_cxcy=105.1,119.7 scan=0:-47.4,10:-45.2,20:-42.8,30:-40.2,40:-37.4,50:-34.4,60:-31.2,70:-27.7,80:-24.0,90:-20.1,100:-16.0,110:-11.7,120:-7.3,130:-2.8,140:1.8
ATGSeedDiag: seed=1@4,96/1@124,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(77.1) imip=18/38 pass=11110 acc=-1 ipm=98.3,72.4 inv=89.1,40.1 | 7(91.8) imip=0/8 pass=11111 acc=7 ipm=117.6,111.2 inv=146.4,89.5
frame=924 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=133/8 raw=170/37 sel=133/110 far=0/0 far_raw=0/0 l=0@-1/1@6 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=77.1/82.8/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(105,98) md=33/1/182 cxcy=84.0,119.6 guide=-25.86 atg=60.0/19.0/16.0 pure=-6.61/-2.00 yaw=1551 cmd=1751 actual=875 signed=0 rps=661/5461:5079/5714 duty=0/15 pwm=PWM2:0/PWM1:15 motor=2:0/1:15
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@6 nearNum=133/8 centerNum=133/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=133/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.09@102,100 dx=18.3 idx=9/21 dist=32/254 right=1:-27.43@113,88 dx=28.5 idx=0/7 dist=14/14 sel=1:-26.31@107,97 dx=22.6 idx=0/16 dist=32/218 edge=1:-24.21@105.5,95.0 dx=21.5 width=43.8 l=93,77 r=118,113
CxScan: raw_ref=80.0 edge=105.5,95.0 best_raw_x=135 best_err=-0.50 best_cxcy=105.1,119.7 scan=0:-47.7,10:-45.5,20:-43.1,30:-40.5,40:-37.7,50:-34.7,60:-31.4,70:-27.9,80:-24.2,90:-20.3,100:-16.1,110:-11.8,120:-7.3,130:-2.8,140:1.8
ATGSeedDiag: seed=1@4,96/1@125,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=27(77.1) imip=17/37 pass=11110 acc=-1 ipm=97.2,74.4 inv=88.5,41.4 | 6(82.8) imip=0/7 pass=11111 acc=6 ipm=116.7,111.4 inv=144.7,89.8
frame=925 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=134/8 raw=170/36 sel=134/109 far=0/0 far_raw=0/0 l=0@-1/1@6 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=78.8/90.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(105,98) md=33/1/184 cxcy=84.0,119.6 guide=-25.60 atg=60.0/17.0/13.0 pure=-6.60/-1.94 yaw=1536 cmd=1736 actual=951 signed=0 rps=701/5459:5134/5863 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@6 nearNum=134/8 centerNum=134/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=134/109 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.12@102,100 dx=18.4 idx=9/21 dist=32/256 right=1:-28.12@113,89 dx=29.0 idx=0/7 dist=14/14 sel=1:-26.27@107,97 dx=22.6 idx=0/16 dist=32/216 edge=1:-23.13@104.0,96.0 dx=20.0 width=44.4 l=91,78 r=117,114
CxScan: raw_ref=80.0 edge=104.0,96.0 best_raw_x=130 best_err=-1.01 best_cxcy=103.2,119.7 scan=0:-47.5,10:-45.2,20:-42.7,30:-40.0,40:-37.1,50:-34.0,60:-30.6,70:-27.0,80:-23.1,90:-19.0,100:-14.7,110:-10.3,120:-5.7,130:-1.0,140:3.7
ATGSeedDiag: seed=1@4,95/1@125,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=27(78.8) imip=17/37 pass=11110 acc=-1 ipm=97.3,74.3 inv=88.6,41.4 | 6(90.6) imip=0/7 pass=11111 acc=6 ipm=116.5,112.1 inv=145.8,91.8
frame=926 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=140/8 raw=170/34 sel=140/115 far=0/0 far_raw=0/0 l=0@-1/1@6 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=78.2/85.7/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(104,98) md=32/1/187 cxcy=84.0,119.6 guide=-24.75 atg=60.0/16.0/11.0 pure=-6.45/-1.83 yaw=1485 cmd=1685 actual=1023 signed=0 rps=835/5453:5115/6212 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@6 nearNum=140/8 centerNum=140/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=140/115 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.44@103,99 dx=19.1 idx=9/21 dist=33/274 right=1:-30.25@115,89 dx=31.1 idx=0/7 dist=14/14 sel=1:-25.82@106,97 dx=22.3 idx=0/16 dist=32/228 edge=1:-23.36@104.0,96.5 dx=20.0 width=45.2 l=91,78 r=117,115
CxScan: raw_ref=80.0 edge=104.0,96.5 best_raw_x=130 best_err=-1.02 best_cxcy=103.2,119.7 scan=0:-47.8,10:-45.5,20:-43.0,30:-40.3,40:-37.4,50:-34.3,60:-30.9,70:-27.3,80:-23.4,90:-19.2,100:-14.9,110:-10.4,120:-5.7,130:-1.0,140:3.7
ATGSeedDiag: seed=1@4,95/1@126,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=27(78.2) imip=17/37 pass=11110 acc=-1 ipm=96.6,73.4 inv=87.7,40.8 | 6(85.7) imip=0/7 pass=11111 acc=6 ipm=116.4,113.3 inv=148.1,95.1
frame=927 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=137/7 raw=170/33 sel=137/111 far=0/0 far_raw=0/0 l=0@-1/1@5 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=78.3/87.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(105,98) md=33/1/188 cxcy=84.0,119.6 guide=-25.43 atg=60.0/13.0/10.0 pure=-6.23/-1.67 yaw=1526 cmd=1726 actual=1105 signed=0 rps=728/5458:4782/6185 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@5 nearNum=137/7 centerNum=137/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=137/111 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-24.42@104,98 dx=20.2 idx=9/21 dist=34/261 right=1:-27.29@112,89 dx=27.9 idx=0/6 dist=12/12 sel=1:-26.07@106,97 dx=22.5 idx=0/16 dist=32/220 edge=1:-23.13@104.0,96.0 dx=20.0 width=43.3 l=92,78 r=116,114
CxScan: raw_ref=80.0 edge=104.0,96.0 best_raw_x=130 best_err=-1.01 best_cxcy=103.2,119.7 scan=0:-47.5,10:-45.2,20:-42.7,30:-40.0,40:-37.1,50:-34.0,60:-30.6,70:-27.0,80:-23.1,90:-19.0,100:-14.7,110:-10.3,120:-5.7,130:-1.0,140:3.7
ATGSeedDiag: seed=1@4,95/1@127,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=26(78.3) imip=16/36 pass=11110 acc=-1 ipm=95.2,75.3 inv=86.6,42.1 | 5(87.2) imip=0/6 pass=11111 acc=5 ipm=115.5,112.3 inv=144.2,92.5
frame=928 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=135/7 raw=170/31 sel=135/110 far=0/0 far_raw=0/0 l=0@-1/1@5 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=78.1/77.6/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,98) md=33/1/188 cxcy=84.0,119.6 guide=-26.46 atg=60.0/10.0/10.0 pure=-5.95/-1.51 yaw=1587 cmd=1787 actual=1174 signed=0 rps=566/5465:4710/6510 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@5 nearNum=135/7 centerNum=135/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=135/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.26@102,100 dx=18.4 idx=9/20 dist=32/263 right=1:-30.37@115,90 dx=31.1 idx=0/6 dist=12/12 sel=1:-27.08@108,97 dx=23.6 idx=0/16 dist=32/218 edge=1:-24.90@105.5,96.5 dx=21.5 width=45.3 l=94,77 r=117,116
CxScan: raw_ref=80.0 edge=105.5,96.5 best_raw_x=135 best_err=-0.52 best_cxcy=105.1,119.7 scan=0:-48.6,10:-46.4,20:-44.0,30:-41.4,40:-38.6,50:-35.5,60:-32.2,70:-28.7,80:-24.9,90:-20.9,100:-16.6,110:-12.2,120:-7.6,130:-2.9,140:1.8
ATGSeedDiag: seed=1@4,96/1@128,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(78.1) imip=15/35 pass=11110 acc=-1 ipm=94.0,77.2 inv=85.7,43.4 | 5(77.6) imip=0/6 pass=11111 acc=5 ipm=115.8,113.7 inv=147.5,96.2
frame=929 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=133/6 raw=170/30 sel=133/110 far=0/0 far_raw=0/0 l=0@-1/1@4 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=79.4/67.2/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,98) md=32/1/186 cxcy=84.0,119.6 guide=-26.20 atg=60.0/9.0/9.0 pure=-5.72/-1.36 yaw=1572 cmd=1772 actual=1222 signed=0 rps=607/5464:4525/6375 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@4 nearNum=133/6 centerNum=133/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=133/110 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-24.43@104,100 dx=19.6 idx=9/20 dist=32/261 right=1:-26.74@111,89 dx=27.1 idx=0/5 dist=10/10 sel=1:-27.41@108,96 dx=24.1 idx=0/16 dist=32/218 edge=1:-23.71@105.0,95.0 dx=21.0 width=45.7 l=94,75 r=116,115
CxScan: raw_ref=80.0 edge=105.0,95.0 best_raw_x=135 best_err=0.10 best_cxcy=105.1,119.7 scan=0:-47.4,10:-45.2,20:-42.8,30:-40.2,40:-37.3,50:-34.3,60:-31.0,70:-27.5,80:-23.7,90:-19.7,100:-15.6,110:-11.2,120:-6.7,130:-2.2,140:2.4
ATGSeedDiag: seed=1@4,98/1@129,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(79.4) imip=15/35 pass=11110 acc=-1 ipm=94.0,77.0 inv=85.6,43.3 | 4(67.2) imip=0/5 pass=11111 acc=4 ipm=114.3,113.0 inv=142.9,94.2
frame=930 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=132/6 raw=170/29 sel=132/109 far=0/0 far_raw=0/0 l=0@-1/1@4 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=80.0/84.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,98) md=32/1/189 cxcy=84.0,119.6 guide=-26.40 atg=60.0/7.0/7.0 pure=-5.57/-1.24 yaw=1584 cmd=1784 actual=1282 signed=0 rps=574/5465:4612/6621 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@4 nearNum=132/6 centerNum=132/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=132/109 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-24.87@104,99 dx=20.1 idx=9/20 dist=33/251 right=1:-28.62@113,90 dx=29.0 idx=0/5 dist=10/10 sel=1:-27.52@108,96 dx=24.2 idx=0/16 dist=32/216 edge=1:-24.16@105.0,96.0 dx=21.0 width=43.9 l=94,77 r=116,115
CxScan: raw_ref=80.0 edge=105.0,96.0 best_raw_x=135 best_err=0.10 best_cxcy=105.1,119.7 scan=0:-48.0,10:-45.8,20:-43.4,30:-40.8,40:-37.9,50:-34.8,60:-31.5,70:-28.0,80:-24.2,90:-20.1,100:-15.9,110:-11.4,120:-6.9,130:-2.2,140:2.4
ATGSeedDiag: seed=1@4,98/1@130,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(80.0) imip=15/35 pass=11110 acc=-1 ipm=93.5,76.8 inv=85.1,43.2 | 4(84.3) imip=0/5 pass=11111 acc=4 ipm=114.9,113.4 inv=144.9,95.4
frame=931 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=135/6 raw=170/27 sel=135/112 far=0/0 far_raw=0/0 l=0@-1/1@4 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=79.0/74.0/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,97) md=33/1/191 cxcy=84.0,119.6 guide=-26.29 atg=60.0/5.0/5.0 pure=-5.32/-1.09 yaw=1577 cmd=1777 actual=1352 signed=0 rps=592/5464:4436/6335 duty=0/14 pwm=PWM2:0/PWM1:14 motor=2:0/1:14
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@4 nearNum=135/6 centerNum=135/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=135/112 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.04@102,101 dx=17.9 idx=9/19 dist=31/257 right=1:-32.85@117,91 dx=33.4 idx=0/5 dist=10/10 sel=1:-27.11@108,96 dx=23.9 idx=0/16 dist=32/222 edge=1:-23.36@104.0,96.5 dx=20.0 width=47.5 l=92,76 r=116,117
CxScan: raw_ref=80.0 edge=104.0,96.5 best_raw_x=130 best_err=-1.02 best_cxcy=103.2,119.7 scan=0:-47.8,10:-45.5,20:-43.0,30:-40.3,40:-37.4,50:-34.3,60:-30.9,70:-27.3,80:-23.4,90:-19.2,100:-14.9,110:-10.4,120:-5.7,130:-1.0,140:3.7
ATGSeedDiag: seed=1@4,98/1@131,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=24(79.0) imip=14/34 pass=11110 acc=-1 ipm=92.0,78.0 inv=83.6,44.0 | 4(74.0) imip=0/5 pass=11111 acc=4 ipm=115.0,114.9 inv=148.6,100.0
frame=932 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=137/5 raw=170/26 sel=137/111 far=0/0 far_raw=0/0 l=0@-1/1@3 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=79.3/77.3/0.0/0.0 dist=0 begin=0/0 m0=(84,119) ml=(106,97) md=33/1/192 cxcy=84.0,119.6 guide=-25.07 atg=60.0/4.0/4.0 pure=-5.10/-0.94 yaw=1504 cmd=1598 actual=1411 signed=0 rps=930/5309:4720/6433 duty=0/13 pwm=PWM2:0/PWM1:13 motor=2:0/1:13
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/1@3 nearNum=137/5 centerNum=137/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=137/111 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-23.53@103,100 dx=18.7 idx=9/19 dist=32/261 right=1:-29.09@113,90 dx=29.3 idx=0/4 dist=8/8 sel=1:-26.68@108,96 dx=23.7 idx=0/16 dist=32/220 edge=1:-21.35@102.5,95.5 dx=18.5 width=48.0 l=90,75 r=115,116
CxScan: raw_ref=80.0 edge=102.5,95.5 best_raw_x=130 best_err=0.81 best_cxcy=103.2,119.7 scan=0:-46.3,10:-43.9,20:-41.4,30:-38.6,40:-35.7,50:-32.4,60:-29.0,70:-25.3,80:-21.4,90:-17.2,100:-12.9,110:-8.4,120:-3.8,130:0.8,140:5.4
ATGSeedDiag: seed=1@4,97/1@132,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=24(79.3) imip=14/34 pass=11110 acc=-1 ipm=91.2,77.3 inv=82.6,43.5 | 3(77.3) imip=0/4 pass=11111 acc=3 ipm=113.6,114.1 inv=143.6,97.6

- stopped_at: 2026-06-22T15:06:30+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive135
```
