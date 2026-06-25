# drive118

- commit: 247fdd6
- board: root@192.168.0.101
- binary: /root/front_car_mainline
- duration_seconds: 6
- local_log: logs/live-circle/20260621-drive118-front_car_circle_drive118.log
- remote_log: /tmp/front_car_circle_drive118.log
- started_at: 2026-06-22T07:39:39+08:00

## Commands

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh run drive118 6
```

3179 /tmp/front_car_circle_drive118.log
ATGSeedDiag: seed=0@-1,-1/1@138,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(8.5) imip=0/11 pass=10111 acc=-1 ipm=109.2,114.0 inv=133.8,97.2
frame=871 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=228/0/0/0 lost=0/0 conf=0.0/5.4/0.0/0.0 dist=1138 begin=1855/0 m0=(84,119) ml=(85,87) md=32/1/132 cxcy=84.0,119.6 guide=-1.66 atg=1.0/1.0/1.0 pure=-0.44/-0.41 yaw=100 cmd=180 actual=20 signed=1 rps=2246/1754:920/839 duty=8/5 pwm=PWM2:5/PWM1:8 motor=2:5/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/1:109.2,114.2:134.2,98.0:5.4:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/5.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.77@86,85 dx=1.8 idx=0/13 dist=33/255 sel=1:-2.08@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,80
ATGSeedDiag: seed=0@-1,-1/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(5.4) imip=0/11 pass=10111 acc=-1 ipm=109.2,114.2 inv=134.2,98.0
frame=874 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=231/0/0/0 lost=0/0 conf=0.0/6.2/0.0/0.0 dist=1144 begin=1861/0 m0=(84,119) ml=(85,87) md=32/1/132 cxcy=84.0,119.6 guide=-1.50 atg=1.0/1.0/1.0 pure=-0.44/-0.41 yaw=90 cmd=144 actual=35 signed=1 rps=2198/1802:923/855 duty=8/6 pwm=PWM2:6/PWM1:8 motor=2:6/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/1:109.2,114.2:134.3,98.0:6.2:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/6.2/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.77@86,85 dx=1.8 idx=0/13 dist=33/255 sel=1:-2.08@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,80
ATGSeedDiag: seed=0@-1,-1/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(6.2) imip=0/11 pass=10111 acc=-1 ipm=109.2,114.2 inv=134.3,98.0
frame=881 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=238/0/0/0 lost=0/0 conf=0.0/2.7/0.0/0.0 dist=1159 begin=1876/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.36/-0.37 yaw=90 cmd=158 actual=21 signed=1 rps=2217/1783:803/874 duty=8/6 pwm=PWM2:6/PWM1:8 motor=2:6/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/17:112.5,77.4:105.8,43.4:2.7:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/2.7/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.59@86,85 dx=1.6 idx=0/13 dist=32/252 sel=1:-1.75@86,83 dx=1.8 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,80
ATGSeedDiag: seed=0@-1,-1/1@138,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 17(2.7) imip=7/27 pass=10111 acc=-1 ipm=112.5,77.4 inv=105.8,43.4
frame=882 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/104 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=239/0/0/0 lost=0/0 conf=0.0/3.6/0.0/0.0 dist=1161 begin=1878/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.36/-0.37 yaw=90 cmd=168 actual=12 signed=1 rps=2230/1770:844/925 duty=8/5 pwm=PWM2:5/PWM1:8 motor=2:5/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/1:109.1,113.9:133.5,97.1:3.6:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/3.6/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.61@86,84 dx=1.6 idx=0/13 dist=32/252 sel=1:-1.75@86,83 dx=1.8 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,79
ATGSeedDiag: seed=0@-1,-1/1@138,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(3.6) imip=0/11 pass=10111 acc=-1 ipm=109.1,113.9 inv=133.5,97.1
frame=884 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/104 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=241/0/0/0 lost=0/0 conf=0.0/2.8/0.0/0.0 dist=1165 begin=1882/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.38/-0.37 yaw=90 cmd=186 actual=-7 signed=1 rps=2255/1745:879/921 duty=8/5 pwm=PWM2:5/PWM1:8 motor=2:5/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/17:112.6,77.1:105.7,43.2:2.8:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/2.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.67@86,84 dx=1.7 idx=0/13 dist=32/252 sel=1:-1.89@86,83 dx=2.0 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,79
ATGSeedDiag: seed=0@-1,-1/1@138,107 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 17(2.8) imip=7/27 pass=10111 acc=-1 ipm=112.6,77.1 inv=105.7,43.2
frame=886 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=243/0/0/0 lost=0/0 conf=0.0/3.4/0.0/0.0 dist=1169 begin=1886/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.42/-0.37 yaw=90 cmd=193 actual=-13 signed=1 rps=2264/1736:863/895 duty=8/5 pwm=PWM2:5/PWM1:8 motor=2:5/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/16:112.6,79.7:107.1,45.2:3.4:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/3.4/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.77@86,85 dx=1.8 idx=0/13 dist=33/254 sel=1:-2.08@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 16(3.4) imip=6/26 pass=10111 acc=-1 ipm=112.6,79.7 inv=107.1,45.2
frame=893 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=250/0/0/0 lost=0/0 conf=0.0/3.0/0.0/0.0 dist=1185 begin=1902/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.39/-0.37 yaw=90 cmd=174 actual=6 signed=1 rps=2238/1762:793/801 duty=8/6 pwm=PWM2:6/PWM1:8 motor=2:6/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/2:109.0,111.9:129.9,91.4:3.0:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/3.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.92@86,85 dx=1.9 idx=0/13 dist=33/253 sel=1:-2.09@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 2(3.0) imip=0/12 pass=10111 acc=-1 ipm=109.0,111.9 inv=129.9,91.4
frame=894 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=251/0/0/0 lost=0/0 conf=0.0/2.9/0.0/0.0 dist=1187 begin=1904/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.39/-0.37 yaw=90 cmd=176 actual=4 signed=1 rps=2241/1759:839/858 duty=8/5 pwm=PWM2:5/PWM1:8 motor=2:5/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/16:112.5,79.7:106.9,45.2:2.9:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/2.9/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.92@86,85 dx=1.9 idx=0/13 dist=33/253 sel=1:-2.09@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 16(2.9) imip=6/26 pass=10111 acc=-1 ipm=112.5,79.7 inv=106.9,45.2
frame=897 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=254/0/0/0 lost=0/0 conf=0.0/3.0/0.0/0.0 dist=1193 begin=1910/0 m0=(84,119) ml=(86,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.66 atg=1.0/0.0/1.0 pure=-0.44/-0.37 yaw=100 cmd=190 actual=10 signed=1 rps=2260/1740:867/869 duty=8/5 pwm=PWM2:5/PWM1:8 motor=2:5/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/15:112.5,82.1:108.2,47.1:3.0:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/3.0/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.97@86,85 dx=2.0 idx=0/13 dist=32/253 sel=1:-2.14@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 15(3.0) imip=5/25 pass=10111 acc=-1 ipm=112.5,82.1 inv=108.2,47.1
frame=898 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=255/0/0/0 lost=0/0 conf=0.0/2.8/0.0/0.0 dist=1195 begin=1912/0 m0=(84,119) ml=(86,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.66 atg=1.0/0.0/1.0 pure=-0.42/-0.37 yaw=100 cmd=184 actual=16 signed=1 rps=2252/1748:827/828 duty=9/5 pwm=PWM2:5/PWM1:9 motor=2:5/1:9
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/16:112.6,79.7:107.1,45.2:2.8:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/2.8/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.97@86,85 dx=2.0 idx=0/13 dist=33/254 sel=1:-2.14@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=113,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 16(2.8) imip=6/26 pass=10111 acc=-1 ipm=112.6,79.7 inv=107.1,45.2
frame=900 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=257/0/0/0 lost=0/0 conf=0.0/3.1/0.0/0.0 dist=1199 begin=1916/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.36/-0.37 yaw=90 cmd=166 actual=14 signed=1 rps=2227/1773:808/843 duty=8/6 pwm=PWM2:6/PWM1:8 motor=2:6/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/15:112.4,82.0:108.0,47.0:3.1:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/3.1/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.92@86,85 dx=1.9 idx=0/13 dist=32/252 sel=1:-2.09@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 15(3.1) imip=5/25 pass=10111 acc=-1 ipm=112.4,82.0 inv=108.0,47.0
frame=901 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=258/0/0/0 lost=0/0 conf=0.0/3.5/0.0/0.0 dist=1201 begin=1918/0 m0=(84,119) ml=(85,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.50 atg=1.0/0.0/1.0 pure=-0.35/-0.37 yaw=90 cmd=172 actual=7 signed=1 rps=2236/1764:831/879 duty=8/5 pwm=PWM2:5/PWM1:8 motor=2:5/1:8
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/1:108.8,114.2:133.3,97.9:3.5:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/3.5/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.91@86,85 dx=1.9 idx=0/13 dist=32/253 sel=1:-2.09@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 1(3.5) imip=0/11 pass=10111 acc=-1 ipm=108.8,114.2 inv=133.3,97.9
frame=906 line=1 track=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN) round=0 yroad=0 ramp=0 road=7 speed=0 near=0/124 raw=0/105 sel=124/126 far=0/0 far_raw=0/0 l=0@-1/0@-1 far_l=0@-1/0@-1 straight=0/1 far_straight=0/0 circle_cnt=263/0/0/0 lost=0/0 conf=0.0/3.3/0.0/0.0 dist=1212 begin=1929/0 m0=(84,119) ml=(86,87) md=32/1/131 cxcy=84.0,119.6 guide=-1.66 atg=1.0/0.0/1.0 pure=-0.36/-0.37 yaw=100 cmd=207 actual=-7 signed=1 rps=2283/1717:805/820 duty=9/5 pwm=PWM2:5/PWM1:9 motor=2:5/1:9
ATGCorner: L=0@-1/0@-1 Y=0@-1/0@-1 farL=0@-1/0@-1 Lxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 Yxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 farLxy=-1.0,-1.0:-1.0,-1.0/-1.0,-1.0:-1.0,-1.0 best=-1:-1.0,-1.0:-1.0,-1.0:-57295.8:00000/15:112.4,82.0:108.0,47.0:3.3:10111 seed_src=lost/none seed=0.0,0.0/0.0,0.0 far_start=70,0 far_raw=0/0 far_num=0/0 straight=0/1 far_straight=0/0 conf_deg=0.0/3.3/0.0/0.0
CrossDiag: type=CROSS_NONE track=1 half_lr=0/0 nearL=0@-1/0@-1 nearNum=0/124 centerNum=0/124 farL=0@-1/0@-1 farNum=0/0 farRaw=0/0 lost=0/0 not_have=0 final=124/126 flags=0/0
LineErr: aim=33 cxcy=84.0,119.6 left=0:0.00@-1,-1 dx=0.0 idx=-1/-1 dist=-1/-1 right=1:-1.97@86,85 dx=2.0 idx=0/13 dist=33/253 sel=1:-2.09@86,83 dx=2.2 idx=0/16 dist=32/250 edge=0:0.00@-1.0,-1.0 dx=0.0 width=0.0 l=-1,-1 r=112,80
ATGSeedDiag: seed=0@-1,-1/1@139,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=-1(-57295.8) imip=-1/-1 pass=00000 acc=-1 ipm=-1.0,-1.0 inv=-1.0,-1.0 | 15(3.3) imip=5/25 pass=10111 acc=-1 ipm=112.4,82.0 inv=108.0,47.0

- stopped_at: 2026-06-22T07:39:51+08:00

## Review

```bash
.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh review drive118
```
