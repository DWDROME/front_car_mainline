# drive81

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive81-front_car_circle_drive81.log
- remote_log: /tmp/front_car_circle_drive81.log
- started_at: 2026-06-22T05:56:41+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive81 6
```

3511 /tmp/front_car_circle_drive81.log
ATGSeedDiag: seed=1@4,98/1@155,90 begin=7,108 block=5 clip=8
ATGLptDiag: best=66(14.3) imip=56/76 pass=10100 acc=-1 ipm=180.0,32.8 inv=137.9,23.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=879 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=79/1 raw=152/2 sel=79/61 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=33.2/0.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(113,102) md=33/1/105 cxcy=84.0,119.6 guide=-35.47 atg=60.0/60.0/60.0 pure=-8.86/-6.41 yaw=2128 cmd=2328 actual=1768 signed=0 rps=1809/8191:3298/5571 duty=2/26 pwm=PWM2:2/PWM1:26 motor=2:2/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=79/1 centerNum=79/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=79/61 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-36.51@115,100 dx=31.4 idx=10/26 dist=33/132 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-36.29@115,101 dx=30.9 idx=0/16 dist=32/120 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=100,79 r=-1,-1
ATGSeedDiag: seed=1@5,98/1@155,91 begin=7,108 block=5 clip=8
ATGLptDiag: best=75(33.2) imip=65/78 pass=10100 acc=-1 ipm=200.1,29.3 inv=149.0,22.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=880 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=80/1 raw=153/2 sel=80/61 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=33.2/0.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(113,101) md=34/1/104 cxcy=84.0,119.6 guide=-34.52 atg=60.0/60.0/60.0 pure=-8.74/-6.33 yaw=2071 cmd=2271 actual=1820 signed=0 rps=1887/8113:3556/5914 duty=2/25 pwm=PWM2:2/PWM1:25 motor=2:2/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=80/1 centerNum=80/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=80/61 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-35.80@115,100 dx=31.0 idx=10/26 dist=33/133 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-35.68@115,100 dx=30.7 idx=0/16 dist=32/120 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=100,79 r=-1,-1
ATGSeedDiag: seed=1@4,99/1@155,92 begin=7,108 block=5 clip=8
ATGLptDiag: best=77(33.2) imip=67/79 pass=10100 acc=-1 ipm=203.7,29.6 inv=151.5,22.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=881 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=80/1 raw=153/2 sel=80/61 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=35.0/0.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(111,102) md=32/1/102 cxcy=84.0,119.6 guide=-33.77 atg=60.0/60.0/60.0 pure=-8.56/-6.24 yaw=2026 cmd=2153 actual=1900 signed=0 rps=2050/7950:3528/5832 duty=3/25 pwm=PWM2:3/PWM1:25 motor=2:3/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=80/1 centerNum=80/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=80/61 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-35.18@115,99 dx=30.9 idx=10/26 dist=33/133 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-34.98@114,99 dx=30.4 idx=0/16 dist=32/120 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=99,78 r=-1,-1
ATGSeedDiag: seed=1@4,99/1@155,93 begin=7,108 block=5 clip=8
ATGLptDiag: best=78(35.0) imip=68/79 pass=10100 acc=-1 ipm=205.2,29.6 inv=152.5,22.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=882 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=82/1 raw=153/2 sel=82/62 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.6/0.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(111,102) md=32/1/110 cxcy=84.0,119.6 guide=-33.40 atg=60.0/60.0/60.0 pure=-8.42/-6.16 yaw=2004 cmd=2066 actual=1942 signed=0 rps=2168/7832:3793/6059 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=82/1 centerNum=82/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=82/62 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-34.93@115,98 dx=31.0 idx=10/26 dist=33/134 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-34.62@114,99 dx=30.3 idx=0/16 dist=32/122 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=99,78 r=-1,-1
ATGSeedDiag: seed=1@4,100/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=58(7.6) imip=48/68 pass=10100 acc=-1 ipm=159.2,34.1 inv=124.5,23.5 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=883 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=82/1 raw=153/2 sel=82/61 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.1/0.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(110,101) md=32/1/108 cxcy=84.0,119.6 guide=-32.87 atg=60.0/60.0/60.0 pure=-8.33/-6.11 yaw=1972 cmd=1998 actual=1947 signed=0 rps=2262/7738:3687/5580 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=82/1 centerNum=82/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=82/61 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.75@113,99 dx=29.2 idx=10/25 dist=32/136 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-34.05@114,99 dx=29.9 idx=0/16 dist=32/120 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=99,77 r=-1,-1
ATGSeedDiag: seed=1@4,101/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=56(7.1) imip=46/66 pass=10100 acc=-1 ipm=154.2,35.1 inv=121.6,23.8 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=884 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=82/1 raw=152/3 sel=82/62 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=22.3/0.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(111,100) md=33/1/107 cxcy=84.0,119.6 guide=-32.33 atg=60.0/60.0/60.0 pure=-8.28/-6.08 yaw=1940 cmd=1952 actual=1928 signed=0 rps=2325/7675:3903/5658 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=82/1 centerNum=82/1 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=82/62 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.67@114,98 dx=29.5 idx=9/25 dist=33/137 right=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 sel=1:-33.56@113,99 dx=29.3 idx=0/16 dist=32/122 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=99,77 r=-1,-1
ATGSeedDiag: seed=1@5,102/1@154,94 begin=7,108 block=5 clip=8
ATGLptDiag: best=77(22.3) imip=67/81 pass=10100 acc=-1 ipm=200.9,25.4 inv=147.0,21.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=885 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=83/2 raw=152/8 sel=83/64 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=13.2/0.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(111,100) md=33/1/107 cxcy=84.0,119.6 guide=-32.12 atg=60.0/60.0/60.0 pure=-8.18/-6.06 yaw=1927 cmd=1961 actual=1894 signed=0 rps=2312/7688:3810/5325 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=83/2 centerNum=83/2 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=83/64 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.52@114,98 dx=29.7 idx=9/25 dist=33/141 right=1:-20.89@103,94 dx=18.6 idx=0/1 dist=2/2 sel=1:-33.30@113,98 dx=29.1 idx=0/16 dist=32/126 edge=1:-27.63@108.5,96.0 dx=24.5 width=42.7 l=97,78 r=120,114
CxScan: raw_ref=80.0 edge=108.5,96.0 best_raw_x=140 best_err=-1.84 best_cxcy=107.0,119.7 scan=0:-49.9,10:-47.8,20:-45.6,30:-43.1,40:-40.5,50:-37.6,60:-34.5,70:-31.2,80:-27.6,90:-23.8,100:-19.8,110:-15.5,120:-11.1,130:-6.5,140:-1.8
ATGSeedDiag: seed=1@5,104/1@155,104 begin=7,108 block=5 clip=8
ATGLptDiag: best=78(13.2) imip=68/82 pass=10100 acc=-1 ipm=202.8,25.5 inv=148.3,21.1 | -1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0
frame=886 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=83/3 raw=153/27 sel=83/64 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=5.6/15.5/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(111,100) md=33/1/106 cxcy=84.0,119.6 guide=-31.96 atg=60.0/60.0/60.0 pure=-8.06/-6.02 yaw=1918 cmd=1965 actual=1871 signed=0 rps=2307/7693:3965/5379 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=83/3 centerNum=83/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=83/64 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.22@114,98 dx=29.6 idx=9/25 dist=33/141 right=1:-20.23@102,94 dx=18.0 idx=0/2 dist=4/4 sel=1:-32.92@113,98 dx=28.8 idx=0/16 dist=32/126 edge=1:-26.66@108.0,95.0 dx=24.0 width=41.6 l=96,78 r=120,112
CxScan: raw_ref=80.0 edge=108.0,95.0 best_raw_x=140 best_err=-1.20 best_cxcy=107.0,119.7 scan=0:-49.0,10:-46.9,20:-44.7,30:-42.2,40:-39.5,50:-36.7,60:-33.6,70:-30.2,80:-26.7,90:-22.9,100:-18.8,110:-14.6,120:-10.2,130:-5.8,140:-1.2
ATGSeedDiag: seed=1@4,106/1@155,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=66(5.6) imip=56/76 pass=10100 acc=-1 ipm=174.1,25.0 inv=130.0,21.1 | 1(15.5) imip=0/2 pass=10111 acc=-1 ipm=118.9,114.3 inv=155.8,98.0
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=85/5 raw=153/20 sel=85/64 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.6/2.2/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(111,99) md=34/1/111 cxcy=84.0,119.6 guide=-31.17 atg=60.0/60.0/60.0 pure=-7.90/-5.89 yaw=1870 cmd=1866 actual=1874 signed=0 rps=2443/7557:4027/5375 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=85/5 centerNum=85/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=85/64 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.83@112,98 dx=27.6 idx=9/24 dist=32/145 right=1:-23.70@107,90 dx=23.3 idx=0/4 dist=8/8 sel=1:-32.19@112,98 dx=28.5 idx=0/16 dist=32/126 edge=1:-27.80@110.0,93.5 dx=26.0 width=43.3 l=96,77 r=124,110
CxScan: raw_ref=80.0 edge=110.0,93.5 best_raw_x=140 best_err=-3.48 best_cxcy=107.0,119.7 scan=0:-49.2,10:-47.1,20:-45.0,30:-42.6,40:-40.1,50:-37.3,60:-34.4,70:-31.2,80:-27.8,90:-24.2,100:-20.4,110:-16.4,120:-12.2,130:-7.9,140:-3.5
ATGSeedDiag: seed=1@4,107/1@155,105 begin=7,108 block=5 clip=8
ATGLptDiag: best=56(7.6) imip=46/66 pass=10100 acc=-1 ipm=151.3,31.8 inv=118.3,22.9 | 2(2.2) imip=0/4 pass=10111 acc=-1 ipm=120.7,112.8 inv=156.0,93.5
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=86/9 raw=153/33 sel=86/66 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=5.0/3.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(109,100) md=32/1/113 cxcy=84.0,119.6 guide=-30.52 atg=60.0/60.0/60.0 pure=-7.70/-5.80 yaw=1831 cmd=1791 actual=1871 signed=0 rps=2545/7455:3763/5075 duty=4/24 pwm=PWM2:4/PWM1:24 motor=2:4/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=86/9 centerNum=86/9 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=86/66 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.26@112,97 dx=27.5 idx=9/24 dist=32/147 right=1:-26.49@113,85 dx=28.9 idx=0/8 dist=16/16 sel=1:-31.54@112,97 dx=28.2 idx=0/16 dist=32/130 edge=1:-28.82@112.5,91.0 dx=28.5 width=44.8 l=95,77 r=130,105
CxScan: raw_ref=80.0 edge=112.5,91.0 best_raw_x=140 best_err=-6.05 best_cxcy=107.0,119.7 scan=0:-49.0,10:-47.0,20:-45.0,30:-42.7,40:-40.3,50:-37.7,60:-35.0,70:-32.0,80:-28.8,90:-25.4,100:-21.9,110:-18.1,120:-14.2,130:-10.2,140:-6.1
ATGSeedDiag: seed=1@4,107/1@155,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=67(5.0) imip=57/77 pass=10100 acc=-1 ipm=173.6,20.8 inv=127.8,20.1 | 7(3.0) imip=0/8 pass=10111 acc=-1 ipm=128.0,106.0 inv=156.0,77.6
frame=889 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=88/32 raw=153/85 sel=88/66 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=7.1/41.3/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(109,99) md=33/1/117 cxcy=84.0,119.6 guide=-29.60 atg=60.0/60.0/60.0 pure=-7.54/-5.63 yaw=1776 cmd=1681 actual=1870 signed=0 rps=2696/7304:3835/5375 duty=5/23 pwm=PWM2:5/PWM1:23 motor=2:5/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=88/32 centerNum=88/32 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=88/66 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.52@111,97 dx=27.1 idx=9/24 dist=32/148 right=1:-30.20@124,74 dx=39.9 idx=0/16 dist=33/63 sel=1:-30.78@112,96 dx=27.8 idx=0/16 dist=32/130 edge=1:-30.47@118.0,85.0 dx=34.0 width=49.4 l=95,76 r=141,94
CxScan: raw_ref=80.0 edge=118.0,85.0 best_raw_x=140 best_err=-10.76 best_cxcy=107.0,119.7 scan=0:-48.4,10:-46.6,20:-44.7,30:-42.7,40:-40.6,50:-38.3,60:-35.8,70:-33.2,80:-30.5,90:-27.5,100:-24.5,110:-21.2,120:-17.9,130:-14.4,140:-10.8
ATGSeedDiag: seed=1@4,108/1@154,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=56(7.1) imip=46/66 pass=10100 acc=-1 ipm=148.3,28.3 inv=115.0,22.0 | 2(41.3) imip=0/12 pass=10111 acc=-1 ipm=116.2,112.9 inv=147.0,94.1
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=89/34 raw=152/73 sel=89/68 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=9.1/6.5/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(108,99) md=32/1/114 cxcy=84.0,119.6 guide=-29.14 atg=60.0/60.0/60.0 pure=-7.38/-5.53 yaw=1748 cmd=1638 actual=1859 signed=0 rps=2755/7245:3681/5400 duty=5/22 pwm=PWM2:5/PWM1:22 motor=2:5/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=89/34 centerNum=89/34 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=89/68 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.09@111,96 dx=27.3 idx=8/24 dist=33/153 right=1:-30.24@125,73 dx=40.9 idx=0/16 dist=32/67 sel=1:-30.01@111,96 dx=27.1 idx=0/16 dist=32/134 edge=1:-30.25@118.0,84.5 dx=34.0 width=52.2 l=93,77 r=143,92
CxScan: raw_ref=80.0 edge=118.0,84.5 best_raw_x=140 best_err=-10.67 best_cxcy=107.0,119.7 scan=0:-48.1,10:-46.4,20:-44.5,30:-42.5,40:-40.3,50:-38.0,60:-35.6,70:-33.0,80:-30.3,90:-27.3,100:-24.3,110:-21.1,120:-17.7,130:-14.2,140:-10.7
ATGSeedDiag: seed=1@5,108/1@154,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=67(9.1) imip=57/77 pass=10100 acc=-1 ipm=170.6,16.6 inv=124.3,19.2 | 32(6.5) imip=22/33 pass=10111 acc=-1 ipm=170.3,66.8 inv=155.9,36.4
frame=891 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=90/37 raw=151/90 sel=90/67 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=37.7/43.0/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(108,99) md=32/1/121 cxcy=84.0,119.6 guide=-28.47 atg=60.0/60.0/60.0 pure=-7.23/-5.48 yaw=1708 cmd=1562 actual=1854 signed=0 rps=2859/7141:3854/5950 duty=5/21 pwm=PWM2:5/PWM1:21 motor=2:5/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=90/37 centerNum=90/37 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=90/67 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.67@111,95 dx=27.4 idx=8/24 dist=33/149 right=1:-29.26@122,74 dx=38.3 idx=0/16 dist=33/77 sel=1:-29.48@111,95 dx=26.9 idx=0/16 dist=32/132 edge=1:-29.35@116.5,85.0 dx=32.5 width=49.6 l=93,77 r=140,93
CxScan: raw_ref=80.0 edge=116.5,85.0 best_raw_x=140 best_err=-9.32 best_cxcy=107.0,119.7 scan=0:-47.7,10:-45.9,20:-44.0,30:-41.9,40:-39.7,50:-37.3,60:-34.8,70:-32.2,80:-29.3,90:-26.4,100:-23.2,110:-19.9,120:-16.5,130:-13.0,140:-9.3
ATGSeedDiag: seed=1@6,108/1@153,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=79(37.7) imip=69/89 pass=10100 acc=-1 ipm=197.2,11.4 inv=137.3,18.0 | 2(43.0) imip=0/12 pass=10111 acc=-1 ipm=115.4,113.3 inv=145.9,95.0
frame=892 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=7 speed=0 near=90/37 raw=150/76 sel=90/68 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=1/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=20.8/13.9/0.0/0.0 dist=0 begin=0/2002 m0=(84,119) ml=(108,98) md=33/1/125 cxcy=84.0,119.6 guide=-28.29 atg=60.0/60.0/60.0 pure=-7.14/-5.46 yaw=1697 cmd=1542 actual=1853 signed=0 rps=2887/7113:3731/5837 duty=5/21 pwm=PWM2:5/PWM1:21 motor=2:5/1:21
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=90/37 centerNum=90/37 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=90/68 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-28.79@110,96 dx=25.9 idx=8/23 dist=32/151 right=1:-29.35@124,73 dx=39.5 idx=0/16 dist=32/82 sel=1:-29.10@111,95 dx=26.6 idx=0/16 dist=32/134 edge=1:-29.46@117.5,83.5 dx=33.5 width=51.2 l=93,76 r=142,91
CxScan: raw_ref=80.0 edge=117.5,83.5 best_raw_x=140 best_err=-10.02 best_cxcy=107.0,119.7 scan=0:-47.4,10:-45.6,20:-43.7,30:-41.7,40:-39.5,50:-37.2,60:-34.8,70:-32.2,80:-29.5,90:-26.6,100:-23.5,110:-20.3,120:-17.0,130:-13.6,140:-10.0
ATGSeedDiag: seed=1@7,108/1@152,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=77(20.8) imip=67/87 pass=10100 acc=-1 ipm=192.5,11.6 inv=134.8,18.1 | 33(13.9) imip=23/36 pass=10111 acc=-1 ipm=170.5,64.1 inv=153.5,34.9

- stopped_at: 2026-06-22T05:56:54+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive81
```
