# drive122

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive122-front_car_circle_drive122.log
- remote_log: /tmp/front_car_circle_drive122.log
- started_at: 2026-06-22T07:59:33+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive122 6
```

4689 /tmp/front_car_circle_drive122.log
ATGSeedDiag: seed=1@6,108/1@145,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=37(85.3) imip=27/47 pass=11110 acc=-1 ipm=121.8,68.8 inv=111.2,37.8 | 2(0.0) imip=0/3 pass=10111 acc=-1 ipm=116.9,114.8 inv=152.5,99.5
frame=886 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=77/4 raw=170/12 sel=77/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=89.2/2.8/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(114,103) md=32/1/207 cxcy=84.0,119.6 guide=-37.11 atg=60.0/60.0/54.0 pure=-9.13/-4.41 yaw=2227 cmd=2427 actual=1496 signed=0 rps=1674/8326:3722/5042 duty=1/28 pwm=PWM2:1/PWM1:28 motor=2:1/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=77/4 centerNum=77/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-34.21@111,104 dx=26.6 idx=9/26 dist=34/228 right=1:-25.28@109,90 dx=25.0 idx=0/3 dist=6/6 sel=1:-37.66@116,102 dx=31.7 idx=0/16 dist=32/188 edge=1:-27.17@107.0,98.0 dx=23.0 width=40.0 l=95,82 r=119,114
CxScan: raw_ref=80.0 edge=107.0,98.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.6,50:-37.7,60:-34.4,70:-30.9,80:-27.2,90:-23.1,100:-18.9,110:-14.4,120:-9.7,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@6,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=36(89.2) imip=26/46 pass=11110 acc=-1 ipm=120.6,70.4 inv=110.7,38.7 | 1(2.8) imip=0/3 pass=10111 acc=-1 ipm=115.0,115.6 inv=150.0,102.0
frame=887 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=77/4 raw=170/12 sel=77/95 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=87.8/2.0/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(114,102) md=32/1/207 cxcy=84.0,119.6 guide=-36.66 atg=60.0/60.0/47.0 pure=-9.01/-4.25 yaw=2200 cmd=2400 actual=1525 signed=0 rps=1711/8289:3824/5278 duty=1/28 pwm=PWM2:1/PWM1:28 motor=2:1/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=77/4 centerNum=77/4 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/95 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-34.72@111,103 dx=27.4 idx=9/26 dist=34/228 right=1:-25.53@109,90 dx=25.3 idx=0/3 dist=6/6 sel=1:-37.34@116,101 dx=31.6 idx=0/16 dist=32/188 edge=1:-28.40@108.5,97.5 dx=24.5 width=39.1 l=98,81 r=119,114
CxScan: raw_ref=80.0 edge=108.5,97.5 best_raw_x=140 best_err=-1.90 best_cxcy=107.0,119.7 scan=0:-50.8,10:-48.7,20:-46.5,30:-44.1,40:-41.4,50:-38.5,60:-35.4,70:-32.0,80:-28.4,90:-24.5,100:-20.4,110:-16.0,120:-11.4,130:-6.7,140:-1.9
ATGSeedDiag: seed=1@6,108/1@146,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=36(87.8) imip=26/46 pass=11110 acc=-1 ipm=119.5,69.3 inv=109.2,38.1 | 2(2.0) imip=0/3 pass=10111 acc=-1 ipm=117.3,114.8 inv=153.4,99.6
frame=888 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=77/3 raw=170/12 sel=77/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=89.5/0.2/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(114,102) md=32/1/212 cxcy=84.0,119.6 guide=-36.66 atg=60.0/60.0/43.0 pure=-8.92/-4.10 yaw=2200 cmd=2400 actual=1543 signed=0 rps=1711/8289:4079/5752 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=77/3 centerNum=77/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.13@109,104 dx=25.2 idx=9/25 dist=32/226 right=1:-24.04@107,91 dx=23.2 idx=0/2 dist=4/4 sel=1:-37.31@116,101 dx=31.7 idx=0/16 dist=32/192 edge=1:-28.18@108.0,98.0 dx=24.0 width=39.4 l=98,81 r=118,115
CxScan: raw_ref=80.0 edge=108.0,98.0 best_raw_x=140 best_err=-1.28 best_cxcy=107.0,119.7 scan=0:-50.9,10:-48.8,20:-46.5,30:-44.1,40:-41.4,50:-38.5,60:-35.3,70:-31.9,80:-28.2,90:-24.2,100:-20.0,110:-15.6,120:-10.9,130:-6.1,140:-1.3
ATGSeedDiag: seed=1@6,108/1@147,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=35(89.5) imip=25/45 pass=11110 acc=-1 ipm=118.4,70.7 inv=108.7,39.0 | 1(0.2) imip=0/2 pass=10111 acc=-1 ipm=115.5,115.6 inv=151.2,102.2
frame=890 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=77/3 raw=170/11 sel=77/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=87.3/1.0/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(114,102) md=32/1/212 cxcy=84.0,119.6 guide=-36.96 atg=60.0/60.0/32.0 pure=-8.65/-3.73 yaw=2218 cmd=2418 actual=1580 signed=0 rps=1687/8313:4163/5759 duty=1/28 pwm=PWM2:1/PWM1:28 motor=2:1/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=77/3 centerNum=77/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=77/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.99@109,105 dx=24.8 idx=9/24 dist=31/233 right=1:-24.03@107,91 dx=23.1 idx=0/2 dist=4/4 sel=1:-37.29@116,101 dx=31.8 idx=0/16 dist=32/192 edge=1:-27.44@107.0,98.5 dx=23.0 width=39.7 l=96,82 r=118,115
CxScan: raw_ref=80.0 edge=107.0,98.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.7,10:-48.5,20:-46.2,30:-43.7,40:-41.0,50:-38.0,60:-34.7,70:-31.2,80:-27.4,90:-23.4,100:-19.1,110:-14.5,120:-9.8,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@7,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=34(87.3) imip=24/44 pass=11110 acc=-1 ipm=115.7,70.3 inv=105.9,38.7 | 1(1.0) imip=0/2 pass=10111 acc=-1 ipm=116.0,115.6 inv=152.3,102.1
frame=891 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/3 raw=170/11 sel=78/99 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=86.8/2.9/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(114,102) md=32/1/216 cxcy=84.0,119.6 guide=-36.85 atg=60.0/56.0/27.0 pure=-8.50/-3.52 yaw=2211 cmd=2411 actual=1604 signed=0 rps=1696/8304:4294/6038 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/3 centerNum=78/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/99 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.62@110,104 dx=25.8 idx=9/24 dist=33/236 right=1:-24.09@107,91 dx=23.2 idx=0/2 dist=4/4 sel=1:-36.92@116,101 dx=31.6 idx=0/16 dist=32/196 edge=1:-27.44@107.0,98.5 dx=23.0 width=39.7 l=96,82 r=118,115
CxScan: raw_ref=80.0 edge=107.0,98.5 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.7,10:-48.5,20:-46.2,30:-43.7,40:-41.0,50:-38.0,60:-34.7,70:-31.2,80:-27.4,90:-23.4,100:-19.1,110:-14.5,120:-9.8,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@7,108/1@148,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=33(86.8) imip=23/43 pass=11110 acc=-1 ipm=113.9,71.5 inv=104.6,39.4 | 1(2.9) imip=0/2 pass=10111 acc=-1 ipm=116.0,115.6 inv=152.4,102.3
frame=893 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=78/3 raw=170/11 sel=78/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=89.9/0.0/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(114,102) md=32/1/216 cxcy=84.0,119.6 guide=-36.48 atg=60.0/44.0/19.0 pure=-8.24/-3.16 yaw=2189 cmd=2389 actual=1644 signed=0 rps=1726/8274:4266/5694 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=78/3 centerNum=78/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=78/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-34.51@111,103 dx=27.4 idx=9/24 dist=34/229 right=1:-23.71@107,91 dx=22.7 idx=0/2 dist=4/4 sel=1:-36.69@116,100 dx=31.5 idx=0/16 dist=32/194 edge=1:-27.17@107.0,98.0 dx=23.0 width=38.8 l=96,82 r=118,114
CxScan: raw_ref=80.0 edge=107.0,98.0 best_raw_x=140 best_err=-0.01 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.6,50:-37.7,60:-34.4,70:-30.9,80:-27.2,90:-23.1,100:-18.9,110:-14.4,120:-9.7,130:-4.9,140:-0.0
ATGSeedDiag: seed=1@7,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=32(89.9) imip=22/42 pass=11110 acc=-1 ipm=111.7,72.1 inv=102.7,39.9 | 1(0.0) imip=0/2 pass=10111 acc=-1 ipm=116.3,115.5 inv=152.8,101.9
frame=894 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=76/3 raw=170/12 sel=76/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.4/0.4/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(113,101) md=32/1/212 cxcy=84.0,119.6 guide=-35.56 atg=60.0/34.0/12.0 pure=-7.96/-2.79 yaw=2133 cmd=2333 actual=1620 signed=0 rps=1802/8198:4100/5275 duty=1/28 pwm=PWM2:1/PWM1:28 motor=2:1/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=76/3 centerNum=76/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=76/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.31@110,104 dx=25.8 idx=9/23 dist=32/224 right=1:-23.72@107,91 dx=22.6 idx=0/2 dist=4/4 sel=1:-36.14@115,100 dx=31.3 idx=0/16 dist=32/192 edge=1:-28.18@108.0,98.0 dx=24.0 width=39.4 l=98,81 r=118,115
CxScan: raw_ref=80.0 edge=108.0,98.0 best_raw_x=140 best_err=-1.28 best_cxcy=107.0,119.7 scan=0:-50.9,10:-48.8,20:-46.5,30:-44.1,40:-41.4,50:-38.5,60:-35.3,70:-31.9,80:-28.2,90:-24.2,100:-20.0,110:-15.6,120:-10.9,130:-6.1,140:-1.3
ATGSeedDiag: seed=1@7,108/1@149,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=31(91.4) imip=21/41 pass=11110 acc=-1 ipm=109.4,72.8 inv=100.6,40.3 | 1(0.4) imip=0/2 pass=10111 acc=-1 ipm=116.2,115.7 inv=152.8,102.3
frame=895 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=76/3 raw=170/11 sel=76/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=87.9/1.2/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(113,101) md=32/1/213 cxcy=84.0,119.6 guide=-35.19 atg=60.0/30.0/10.0 pure=-7.80/-2.64 yaw=2112 cmd=2312 actual=1623 signed=0 rps=1832/8168:4186/5323 duty=1/28 pwm=PWM2:1/PWM1:28 motor=2:1/1:28
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=76/3 centerNum=76/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=76/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.55@110,103 dx=26.5 idx=9/23 dist=32/222 right=1:-23.54@106,91 dx=22.4 idx=0/2 dist=4/4 sel=1:-35.83@115,100 dx=31.2 idx=0/16 dist=32/192 edge=1:-28.14@108.5,97.0 dx=24.5 width=40.0 l=98,80 r=119,114
CxScan: raw_ref=80.0 edge=108.5,97.0 best_raw_x=140 best_err=-1.88 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.4,20:-46.2,30:-43.8,40:-41.1,50:-38.2,60:-35.1,70:-31.8,80:-28.1,90:-24.3,100:-20.2,110:-15.8,120:-11.3,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@7,108/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(87.9) imip=20/40 pass=11110 acc=-1 ipm=107.9,74.2 inv=99.6,41.2 | 1(1.2) imip=0/2 pass=10111 acc=-1 ipm=116.7,115.5 inv=153.5,101.6
frame=896 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=76/3 raw=170/11 sel=76/98 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=92.7/0.4/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(113,101) md=32/1/214 cxcy=84.0,119.6 guide=-35.09 atg=60.0/25.0/7.0 pure=-7.66/-2.43 yaw=2105 cmd=2305 actual=1637 signed=0 rps=1841/8159:4168/5500 duty=1/27 pwm=PWM2:1/PWM1:27 motor=2:1/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=76/3 centerNum=76/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=76/98 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.09@109,104 dx=24.5 idx=8/22 dist=32/225 right=1:-23.67@107,91 dx=22.5 idx=0/2 dist=4/4 sel=1:-35.58@115,99 dx=31.0 idx=0/16 dist=32/194 edge=1:-27.42@107.5,97.5 dx=23.5 width=40.2 l=96,81 r=119,114
CxScan: raw_ref=80.0 edge=107.5,97.5 best_raw_x=140 best_err=-0.64 best_cxcy=107.0,119.7 scan=0:-50.3,10:-48.2,20:-45.9,30:-43.4,40:-40.7,50:-37.8,60:-34.6,70:-31.1,80:-27.4,90:-23.4,100:-19.2,110:-14.8,120:-10.2,130:-5.4,140:-0.6
ATGSeedDiag: seed=1@8,108/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=30(92.7) imip=20/40 pass=11110 acc=-1 ipm=107.3,73.1 inv=98.6,40.5 | 1(0.4) imip=0/2 pass=10111 acc=-1 ipm=116.7,115.5 inv=153.6,101.7
frame=897 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/3 raw=170/11 sel=75/96 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=92.1/1.9/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(113,100) md=33/1/210 cxcy=84.0,119.6 guide=-34.43 atg=60.0/21.0/5.0 pure=-7.49/-2.22 yaw=2066 cmd=2266 actual=1665 signed=0 rps=1895/8105:3847/5354 duty=2/27 pwm=PWM2:2/PWM1:27 motor=2:2/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/3 centerNum=75/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/96 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.64@110,103 dx=25.6 idx=8/22 dist=33/222 right=1:-23.68@107,91 dx=22.6 idx=0/2 dist=4/4 sel=1:-35.29@115,99 dx=30.9 idx=0/16 dist=32/190 edge=1:-28.63@109.0,97.0 dx=25.0 width=39.4 l=99,80 r=119,114
CxScan: raw_ref=80.0 edge=109.0,97.0 best_raw_x=140 best_err=-2.50 best_cxcy=107.0,119.7 scan=0:-50.7,10:-48.7,20:-46.5,30:-44.1,40:-41.5,50:-38.6,60:-35.5,70:-32.2,80:-28.6,90:-24.8,100:-20.7,110:-16.4,120:-11.9,130:-7.2,140:-2.5
ATGSeedDiag: seed=1@8,108/1@150,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(92.1) imip=19/39 pass=11110 acc=-1 ipm=105.9,74.6 inv=97.6,41.5 | 1(1.9) imip=0/2 pass=10111 acc=-1 ipm=116.7,115.5 inv=153.7,101.8
frame=898 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/3 raw=170/11 sel=75/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=94.0/0.9/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(113,100) md=33/1/213 cxcy=84.0,119.6 guide=-34.48 atg=60.0/17.0/3.0 pure=-7.31/-2.00 yaw=2069 cmd=2269 actual=1670 signed=0 rps=1891/8109:3938/5820 duty=2/27 pwm=PWM2:2/PWM1:27 motor=2:2/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/3 centerNum=75/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-32.89@110,102 dx=26.3 idx=8/22 dist=33/224 right=1:-23.31@106,92 dx=22.0 idx=0/2 dist=4/4 sel=1:-34.80@115,99 dx=30.6 idx=0/16 dist=32/192 edge=1:-28.14@108.5,97.0 dx=24.5 width=40.0 l=98,80 r=119,114
CxScan: raw_ref=80.0 edge=108.5,97.0 best_raw_x=140 best_err=-1.88 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.4,20:-46.2,30:-43.8,40:-41.1,50:-38.2,60:-35.1,70:-31.8,80:-28.1,90:-24.3,100:-20.2,110:-15.8,120:-11.3,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@8,108/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=29(94.0) imip=19/39 pass=11110 acc=-1 ipm=104.9,74.0 inv=96.4,41.1 | 1(0.9) imip=0/2 pass=10111 acc=-1 ipm=117.0,115.4 inv=154.0,101.5
frame=899 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=75/3 raw=170/12 sel=75/97 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=91.5/0.2/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(113,100) md=33/1/213 cxcy=84.0,119.6 guide=-34.00 atg=60.0/14.0/1.0 pure=-7.15/-1.84 yaw=2040 cmd=2240 actual=1672 signed=0 rps=1930/8070:3719/5718 duty=2/27 pwm=PWM2:2/PWM1:27 motor=2:2/1:27
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=75/3 centerNum=75/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=75/97 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-33.31@111,101 dx=27.4 idx=8/22 dist=34/224 right=1:-22.80@105,92 dx=21.4 idx=0/2 dist=4/4 sel=1:-34.60@115,99 dx=30.5 idx=0/16 dist=32/192 edge=1:-28.14@108.5,97.0 dx=24.5 width=40.0 l=98,80 r=119,114
CxScan: raw_ref=80.0 edge=108.5,97.0 best_raw_x=140 best_err=-1.88 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.4,20:-46.2,30:-43.8,40:-41.1,50:-38.2,60:-35.1,70:-31.8,80:-28.1,90:-24.3,100:-20.2,110:-15.8,120:-11.3,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@8,108/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(91.5) imip=18/38 pass=11110 acc=-1 ipm=103.8,75.4 inv=95.7,42.1 | 1(0.2) imip=0/2 pass=10111 acc=-1 ipm=116.9,115.4 inv=153.9,101.3
frame=900 line=1 track=0 cross=0 circle=0(CIRCLE_NONE) round=0 yroad=0 ramp=0 road=3 speed=0 near=74/3 raw=170/13 sel=74/96 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/0 far_straight=0/0 circle_cnt=0/0/0/0 lost=0/0 conf=95.1/2.1/0.0/0.0 dist=0 begin=0/2594 m0=(84,119) ml=(113,100) md=33/1/212 cxcy=84.0,119.6 guide=-33.69 atg=60.0/11.0/0.0 pure=-6.99/-1.63 yaw=2021 cmd=2221 actual=1685 signed=0 rps=1956/8044:3873/5956 duty=2/26 pwm=PWM2:2/PWM1:26 motor=2:2/1:26
CrossDiag: type=CROSS_NONE track=0 half_lr=0/0 nearL=0@-1/0@-1 nearNum=74/3 centerNum=74/3 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=74/96 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=1:-31.91@109,103 dx=24.8 idx=8/21 dist=32/220 right=1:-22.77@105,92 dx=21.4 idx=0/2 dist=4/4 sel=1:-34.35@114,98 dx=30.4 idx=0/16 dist=32/190 edge=1:-28.14@108.5,97.0 dx=24.5 width=40.0 l=98,80 r=119,114
CxScan: raw_ref=80.0 edge=108.5,97.0 best_raw_x=140 best_err=-1.88 best_cxcy=107.0,119.7 scan=0:-50.5,10:-48.4,20:-46.2,30:-43.8,40:-41.1,50:-38.2,60:-35.1,70:-31.8,80:-28.1,90:-24.3,100:-20.2,110:-15.8,120:-11.3,130:-6.6,140:-1.9
ATGSeedDiag: seed=1@8,108/1@151,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=28(95.1) imip=18/38 pass=11110 acc=-1 ipm=102.9,74.6 inv=94.5,41.6 | 1(2.1) imip=0/2 pass=10111 acc=-1 ipm=116.9,115.3 inv=153.6,101.2

- stopped_at: 2026-06-22T07:59:46+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive122
```
