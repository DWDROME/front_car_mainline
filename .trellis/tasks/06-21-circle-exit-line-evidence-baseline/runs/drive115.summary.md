# drive115

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive115-front_car_circle_drive115.log
- remote_log: /tmp/front_car_circle_drive115.log
- started_at: 2026-06-22T07:32:08+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive115 6
```

4570 /tmp/front_car_circle_drive115.log
ATGSeedDiag: seed=1@4,108/1@147,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=31(89.5) imip=21/41 pass=11110 acc=-1 ipm=108.4,73.0 inv=99.6,40.4 | 2(0.5) imip=0/3 pass=10111 acc=-1 ipm=117.8,114.2 inv=153.0,97.6
frame=909 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=76/5 raw=170/16 sel=76/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=90.7/1.3/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(113,100) md=33/1/213 cxcy=84.0,119.6 guide=-34.43 atg=60.0/28.0/9.0 pure=-7.71/-2.53 yaw=2066 cmd=2266 actual=1625 signed=0 rps=1895/8105:4441/5901 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=76/5 centerNum=76/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=76/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.16@109,103 dx=25.2 idx=9/23 dist=32/229 right=1:-25.15@109,89 dx=25.2 idx=0/4 dist=8/8 sel=1:-34.81@114,99 dx=30.4 idx=0/16 dist=32/192 edge=1:-28.58@109.5,96.0 dx=25.5 width=40.6 l=97,80 r=122,112
CxScan: raw_ref=80.0 edge=109.5,96.0 best_raw_x=140 best_err=-3.06 best_cxcy=107.0,119.7 scan=0:-50.4,10:-48.4,20:-46.2,30:-43.8,40:-41.2,50:-38.4,60:-35.4,70:-32.1,80:-28.6,90:-24.8,100:-20.8,110:-16.6,120:-12.2,130:-7.7,140:-3.1
ATGSeedDiag: seed=1@5,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=31(90.7) imip=21/41 pass=11110 acc=-1 ipm=107.8,71.7 inv=98.5,39.7 | 3(1.3) imip=0/4 pass=10111 acc=-1 ipm=119.5,113.3 inv=154.7,95.0
frame=910 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=76/5 raw=170/16 sel=76/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.2/2.0/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(112,100) md=32/1/212 cxcy=84.0,119.6 guide=-34.17 atg=60.0/24.0/6.0 pure=-7.54/-2.36 yaw=2050 cmd=2250 actual=1659 signed=0 rps=1916/8084:4524/6155 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=76/5 centerNum=76/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=76/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.60@110,102 dx=26.1 idx=9/23 dist=34/224 right=1:-25.14@109,89 dx=25.1 idx=0/4 dist=8/8 sel=1:-34.61@114,99 dx=30.3 idx=0/16 dist=32/192 edge=1:-28.58@109.5,96.0 dx=25.5 width=40.6 l=97,80 r=122,112
CxScan: raw_ref=80.0 edge=109.5,96.0 best_raw_x=140 best_err=-3.06 best_cxcy=107.0,119.7 scan=0:-50.4,10:-48.4,20:-46.2,30:-43.8,40:-41.2,50:-38.4,60:-35.4,70:-32.1,80:-28.6,90:-24.8,100:-20.8,110:-16.6,120:-12.2,130:-7.7,140:-3.1
ATGSeedDiag: seed=1@5,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(91.2) imip=20/40 pass=11110 acc=-1 ipm=106.4,73.3 inv=97.7,40.7 | 1(2.0) imip=0/4 pass=10111 acc=-1 ipm=115.5,115.5 inv=150.9,101.8
frame=911 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/4 raw=170/16 sel=75/96 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.9/1.0/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(112,100) md=32/1/212 cxcy=84.0,119.6 guide=-34.07 atg=60.0/19.0/4.0 pure=-7.38/-2.14 yaw=2044 cmd=2244 actual=1700 signed=0 rps=1924/8076:4582/6328 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/4 centerNum=75/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/96 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.98@111,101 dx=27.0 idx=9/23 dist=33/219 right=1:-23.70@107,90 dx=23.0 idx=0/3 dist=6/6 sel=1:-34.45@114,99 dx=30.2 idx=0/16 dist=32/190 edge=1:-27.88@108.5,96.5 dx=24.5 width=40.2 l=97,80 r=120,113
CxScan: raw_ref=80.0 edge=108.5,96.5 best_raw_x=140 best_err=-1.86 best_cxcy=107.0,119.7 scan=0:-50.2,10:-48.1,20:-45.9,30:-43.4,40:-40.8,50:-37.9,60:-34.8,70:-31.5,80:-27.9,90:-24.0,100:-19.9,110:-15.6,120:-11.2,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@5,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(91.9) imip=20/40 pass=11110 acc=-1 ipm=105.3,72.6 inv=96.3,40.2 | 2(1.0) imip=0/3 pass=10111 acc=-1 ipm=117.7,114.3 inv=153.2,98.1
frame=912 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=74/4 raw=170/16 sel=74/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.4/1.3/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(112,100) md=32/1/209 cxcy=84.0,119.6 guide=-33.50 atg=60.0/14.0/2.0 pure=-7.11/-1.85 yaw=2010 cmd=2210 actual=1726 signed=0 rps=1971/8029:4298/6012 duty=1/26 pwm=PWM2:1/PWM1:26 motor=2:1/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=74/4 centerNum=74/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=74/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.85@109,102 dx=25.1 idx=9/22 dist=32/220 right=1:-23.68@107,90 dx=23.0 idx=0/3 dist=6/6 sel=1:-34.12@114,98 dx=30.1 idx=0/16 dist=32/188 edge=1:-28.58@109.5,96.0 dx=25.5 width=40.0 l=99,79 r=120,113
CxScan: raw_ref=80.0 edge=109.5,96.0 best_raw_x=140 best_err=-3.06 best_cxcy=107.0,119.7 scan=0:-50.4,10:-48.4,20:-46.2,30:-43.8,40:-41.2,50:-38.4,60:-35.4,70:-32.1,80:-28.6,90:-24.8,100:-20.8,110:-16.6,120:-12.2,130:-7.7,140:-3.1
ATGSeedDiag: seed=1@5,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(91.4) imip=19/39 pass=11110 acc=-1 ipm=103.6,73.8 inv=95.0,41.0 | 1(1.3) imip=0/3 pass=10111 acc=-1 ipm=115.7,115.5 inv=151.4,101.6
frame=914 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=73/5 raw=170/18 sel=73/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=92.8/1.0/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(112,99) md=33/1/209 cxcy=84.0,119.6 guide=-32.76 atg=60.0/8.0/0.0 pure=-6.75/-1.44 yaw=1966 cmd=2166 actual=1766 signed=0 rps=2032/7968:4340/6218 duty=2/25 pwm=PWM2:2/PWM1:25 motor=2:2/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=73/5 centerNum=73/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=73/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.40@111,100 dx=26.9 idx=9/22 dist=34/217 right=1:-24.54@108,89 dx=24.4 idx=0/4 dist=8/8 sel=1:-33.48@114,98 dx=29.8 idx=0/16 dist=32/188 edge=1:-28.58@109.5,96.0 dx=25.5 width=40.6 l=97,80 r=122,112
CxScan: raw_ref=80.0 edge=109.5,96.0 best_raw_x=140 best_err=-3.06 best_cxcy=107.0,119.7 scan=0:-50.4,10:-48.4,20:-46.2,30:-43.8,40:-41.2,50:-38.4,60:-35.4,70:-32.1,80:-28.6,90:-24.8,100:-20.8,110:-16.6,120:-12.2,130:-7.7,140:-3.1
ATGSeedDiag: seed=1@5,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(92.8) imip=18/38 pass=11110 acc=-1 ipm=101.3,74.7 inv=92.8,41.6 | 1(1.0) imip=0/4 pass=10111 acc=-1 ipm=115.7,115.4 inv=151.1,101.3
frame=915 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=73/5 raw=170/19 sel=73/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=92.6/1.0/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(112,99) md=33/1/209 cxcy=84.0,119.6 guide=-32.15 atg=60.0/6.0/0.0 pure=-6.47/-1.18 yaw=1929 cmd=2074 actual=1784 signed=0 rps=2157/7843:4082/5781 duty=2/25 pwm=PWM2:2/PWM1:25 motor=2:2/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=73/5 centerNum=73/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=73/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-30.67@108,102 dx=24.4 idx=9/21 dist=32/220 right=1:-24.30@108,89 dx=24.1 idx=0/4 dist=8/8 sel=1:-32.80@113,97 dx=29.4 idx=0/16 dist=32/188 edge=1:-28.33@109.5,95.5 dx=25.5 width=41.4 l=97,79 r=122,112
CxScan: raw_ref=80.0 edge=109.5,95.5 best_raw_x=140 best_err=-3.02 best_cxcy=107.0,119.7 scan=0:-50.1,10:-48.1,20:-45.9,30:-43.5,40:-40.9,50:-38.1,60:-35.1,70:-31.8,80:-28.3,90:-24.6,100:-20.6,110:-16.5,120:-12.1,130:-7.6,140:-3.0
ATGSeedDiag: seed=1@5,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=27(92.6) imip=17/37 pass=11110 acc=-1 ipm=99.8,76.1 inv=91.7,42.6 | 2(1.0) imip=0/4 pass=10111 acc=-1 ipm=117.7,114.2 inv=152.9,97.6
frame=916 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=73/5 raw=170/19 sel=73/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.1/0.8/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(112,98) md=34/1/209 cxcy=84.0,119.6 guide=-31.92 atg=60.0/3.0/0.0 pure=-6.24/-0.96 yaw=1915 cmd=2040 actual=1790 signed=0 rps=2204/7796:4147/5866 duty=2/25 pwm=PWM2:2/PWM1:25 motor=2:2/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=73/5 centerNum=73/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=73/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.00@109,100 dx=25.5 idx=9/21 dist=33/220 right=1:-24.16@108,89 dx=23.9 idx=0/4 dist=8/8 sel=1:-32.40@113,97 dx=29.2 idx=0/16 dist=32/188 edge=1:-28.33@109.5,95.5 dx=25.5 width=41.4 l=97,79 r=122,112
CxScan: raw_ref=80.0 edge=109.5,95.5 best_raw_x=140 best_err=-3.02 best_cxcy=107.0,119.7 scan=0:-50.1,10:-48.1,20:-45.9,30:-43.5,40:-40.9,50:-38.1,60:-35.1,70:-31.8,80:-28.3,90:-24.6,100:-20.6,110:-16.5,120:-12.1,130:-7.6,140:-3.0
ATGSeedDiag: seed=1@5,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=26(91.1) imip=16/36 pass=11110 acc=-1 ipm=98.4,77.5 inv=90.5,43.6 | 2(0.8) imip=0/4 pass=10111 acc=-1 ipm=117.7,114.2 inv=152.8,97.5
frame=917 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=73/5 raw=170/19 sel=73/96 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.6/0.6/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(111,98) md=33/1/209 cxcy=84.0,119.6 guide=-31.32 atg=60.0/2.0/0.0 pure=-6.06/-0.75 yaw=1879 cmd=1978 actual=1780 signed=0 rps=2289/7711:3905/5551 duty=3/25 pwm=PWM2:3/PWM1:25 motor=2:3/1:25
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=73/5 centerNum=73/5 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=73/96 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.79@108,102 dx=23.5 idx=9/20 dist=31/221 right=1:-24.15@108,89 dx=24.0 idx=0/4 dist=8/8 sel=1:-31.81@113,96 dx=28.8 idx=0/16 dist=32/190 edge=1:-27.83@109.5,94.5 dx=25.5 width=41.4 l=97,78 r=122,111
CxScan: raw_ref=80.0 edge=109.5,94.5 best_raw_x=140 best_err=-2.96 best_cxcy=107.0,119.7 scan=0:-49.5,10:-47.5,20:-45.3,30:-42.9,40:-40.3,50:-37.5,60:-34.5,70:-31.3,80:-27.8,90:-24.1,100:-20.2,110:-16.1,120:-11.9,130:-7.5,140:-3.0
ATGSeedDiag: seed=1@6,108/1@149,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=26(95.6) imip=16/36 pass=11110 acc=-1 ipm=97.9,76.4 inv=89.7,42.8 | 2(0.6) imip=0/4 pass=10111 acc=-1 ipm=118.3,113.8 inv=153.2,96.4
frame=918 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=25/6 raw=170/21 sel=25/22 far=0/0 far_raw=0/0 l=1@26/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=96.1/1.7/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(111,98) md=33/1/47 cxcy=84.0,119.6 guide=-30.53 atg=60.0/60.0/60.0 pure=-8.55/-8.55 yaw=1832 cmd=1892 actual=1771 signed=0 rps=2407/7593:4082/5949 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@26/0@-1 nearNum=25/6 centerNum=25/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=25/22 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.54@108,101 dx=23.8 idx=9/20 dist=32/51 right=1:-25.06@109,88 dx=25.4 idx=0/5 dist=10/10 sel=1:-31.40@113,96 dx=28.6 idx=0/16 dist=32/42 edge=1:-28.08@109.5,95.0 dx=25.5 width=41.7 l=95,80 r=124,110
CxScan: raw_ref=80.0 edge=109.5,95.0 best_raw_x=140 best_err=-2.99 best_cxcy=107.0,119.7 scan=0:-49.8,10:-47.8,20:-45.6,30:-43.2,40:-40.6,50:-37.8,60:-34.8,70:-31.6,80:-28.1,90:-24.4,100:-20.4,110:-16.3,120:-12.0,130:-7.5,140:-3.0
ATGSeedDiag: seed=1@6,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=26(96.1) imip=16/36 pass=11111 acc=26 ipm=96.8,75.8 inv=88.3,42.4 | 1(1.7) imip=0/5 pass=10111 acc=-1 ipm=115.8,115.4 inv=151.2,101.3
frame=919 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=72/6 raw=170/23 sel=72/96 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.0/2.3/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(111,97) md=34/1/208 cxcy=84.0,119.6 guide=-30.02 atg=60.0/0.0/-3.0 pure=-5.50/-0.25 yaw=1801 cmd=1839 actual=1763 signed=0 rps=2480/7520:4160/6060 duty=3/24 pwm=PWM2:3/PWM1:24 motor=2:3/1:24
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=72/6 centerNum=72/6 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=72/96 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-29.79@109,99 dx=25.2 idx=9/20 dist=33/223 right=1:-24.65@109,88 dx=24.9 idx=0/5 dist=10/10 sel=1:-30.70@112,95 dx=28.1 idx=0/16 dist=32/190 edge=1:-26.89@109.0,93.5 dx=25.0 width=43.3 l=95,77 r=123,110
CxScan: raw_ref=80.0 edge=109.0,93.5 best_raw_x=140 best_err=-2.32 best_cxcy=107.0,119.7 scan=0:-48.7,10:-46.6,20:-44.4,30:-42.0,40:-39.4,50:-36.6,60:-33.6,70:-30.3,80:-26.9,90:-23.2,100:-19.3,110:-15.3,120:-11.1,130:-6.7,140:-2.3
ATGSeedDiag: seed=1@6,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=25(94.0) imip=15/35 pass=11110 acc=-1 ipm=94.8,76.9 inv=86.5,43.2 | 1(2.3) imip=0/5 pass=10111 acc=-1 ipm=115.7,115.3 inv=151.1,101.3
frame=921 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=68/7 raw=165/27 sel=68/91 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.7/0.9/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(110,97) md=33/1/197 cxcy=84.0,119.6 guide=-29.42 atg=60.0/0.0/-9.0 pure=-4.98/0.26 yaw=1765 cmd=1798 actual=1732 signed=0 rps=2536/7464:4700/6272 duty=3/23 pwm=PWM2:3/PWM1:23 motor=2:3/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=68/7 centerNum=68/7 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=68/91 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-28.79@108,99 dx=24.0 idx=9/19 dist=32/210 right=1:-25.20@110,87 dx=26.1 idx=0/6 dist=12/12 sel=1:-29.71@111,95 dx=27.4 idx=0/16 dist=32/180 edge=1:-25.50@108.0,92.5 dx=24.0 width=47.4 l=91,76 r=125,109
CxScan: raw_ref=80.0 edge=108.0,92.5 best_raw_x=140 best_err=-1.14 best_cxcy=107.0,119.7 scan=0:-47.6,10:-45.5,20:-43.2,30:-40.7,40:-38.1,50:-35.3,60:-32.2,70:-29.0,80:-25.5,90:-21.8,100:-18.0,110:-13.9,120:-9.7,130:-5.5,140:-1.1
ATGSeedDiag: seed=1@6,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(91.7) imip=13/33 pass=11110 acc=-1 ipm=92.4,80.2 inv=84.4,45.7 | 2(0.9) imip=0/6 pass=10111 acc=-1 ipm=117.6,113.9 inv=152.0,96.9
frame=922 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=67/8 raw=162/29 sel=67/90 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.3/0.9/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(110,96) md=34/1/195 cxcy=84.0,119.6 guide=-28.43 atg=60.0/0.0/-11.0 pure=-4.76/0.43 yaw=1706 cmd=1711 actual=1700 signed=0 rps=2655/7345:4617/5978 duty=3/23 pwm=PWM2:3/PWM1:23 motor=2:3/1:23
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=67/8 centerNum=67/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=67/90 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-28.62@109,97 dx=24.9 idx=8/19 dist=33/209 right=1:-25.96@112,86 dx=27.7 idx=0/7 dist=14/14 sel=1:-29.12@111,94 dx=27.0 idx=0/16 dist=32/178 edge=1:-25.07@108.0,91.5 dx=24.0 width=49.0 l=89,76 r=127,107
CxScan: raw_ref=80.0 edge=108.0,91.5 best_raw_x=140 best_err=-1.12 best_cxcy=107.0,119.7 scan=0:-47.0,10:-44.9,20:-42.6,30:-40.2,40:-37.6,50:-34.7,60:-31.7,70:-28.5,80:-25.1,90:-21.4,100:-17.6,110:-13.7,120:-9.6,130:-5.4,140:-1.1
ATGSeedDiag: seed=1@7,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=23(93.3) imip=13/33 pass=11110 acc=-1 ipm=91.9,79.3 inv=83.7,45.0 | 5(0.9) imip=0/7 pass=10111 acc=-1 ipm=123.2,109.8 inv=154.5,85.8
frame=923 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=21/8 raw=158/30 sel=21/18 far=0/0 far_raw=0/0 l=1@22/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=93.5/1.6/0.0/0.0 dist=0 begin=0/2651 m0=(84,119) ml=(109,95) md=34/1/38 cxcy=84.0,119.6 guide=-27.19 atg=60.0/60.0/60.0 pure=-8.56/-8.56 yaw=1631 cmd=1585 actual=1678 signed=0 rps=2827/7173:4826/6102 duty=4/22 pwm=PWM2:4/PWM1:22 motor=2:4/1:22
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=1@22/0@-1 nearNum=21/8 centerNum=21/8 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=21/18 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-27.07@107,98 dx=22.9 idx=8/18 dist=31/41 right=1:-25.58@111,86 dx=27.2 idx=0/7 dist=14/14 sel=1:-27.85@110,93 dx=26.1 idx=0/16 dist=32/34 edge=1:-25.93@107.0,95.5 dx=23.0 width=46.1 l=87,84 r=127,107
CxScan: raw_ref=80.0 edge=107.0,95.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-48.8,10:-46.7,20:-44.3,30:-41.8,40:-39.1,50:-36.2,60:-33.0,70:-29.6,80:-25.9,90:-22.0,100:-17.9,110:-13.6,120:-9.2,130:-4.6,140:-0.0
ATGSeedDiag: seed=1@7,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=22(93.5) imip=12/32 pass=11111 acc=22 ipm=89.9,80.5 inv=81.7,46.0 | 1(1.6) imip=0/7 pass=10111 acc=-1 ipm=115.7,115.2 inv=150.6,100.9

- stopped_at: 2026-06-22T07:32:22+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive115
```
