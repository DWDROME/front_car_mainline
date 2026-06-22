# drive170 — 右环测试（point_Cal_Line_2 bugfix + IN offset 30 + RUNNING clamp）

## 右环三次迭代对比

| 指标 | drive165(原版) | drive168(+0.75缩放) | **drive170(三修)** | 趋势 |
|------|:---:|:---:|:---:|:---:|
| RIGHT_IN guide | -56.84 | -42.63 | **-40.19** | ↓ 降29% |
| RIGHT_IN yaw | 4500(饱和) | 3410 | **3216** | ↓ 降29% |
| RIGHT_RUNNING guide | -56.84(饱和) | -56.84(饱和) | **[-35.00~0] clamp生效** | ✅ 关键突破 |
| RIGHT_RUNNING yaw | 4500(饱和) | 4500(饱和) | **2800→0 动态变化** | ✅ 不再饱和 |
| IN→RUNNING dist | 452 | 524 | **570** | ↑ 26% |
| RUNNING→OUT dist | 569 | 754 | **1616** | ↑ **184%** ✅ |
| NONE 恢复 | road=0 | road=0 | **road=3** | ⚠️ 有改善但卡死 |

## 关键发现

### RIGHT_IN 固定线
- offset center+35→center+30 让 guide 从 -56.84 降到 -40.19
- 仍然偏高（左环 IN 只有 37.4°），需要继续降 offset

### RIGHT_RUNNING clamp 生效（最大突破）
```
drive165(drive168): guide=-56.84 yaw=4500 → 全程饱和
drive170:            guide=-35.00 yaw=2800 → 然后 guide快速降到0°附近
                    near=0/23→78/37 → 真实线点恢复！← 之前从未有过
```
这是第一次右环 RUNNING 阶段不是全程饱和——clamp 把 yaw 限制在 2800（非 4500），
车有足够时间找到真实赛道线（near=78/37）。

### 但 RUNNING 中段不稳定
guide 在 -35(钳位) ↔ 0° 之间来回振荡，线点时有时无。说明：
1. `circle_out_fixed_left` 固定线偏移量仍需要微调
2. OUT 阶段还没修（大佬说这轮先不动 OUT）

## 状态转换

NONE→RIGHT_BEGIN: entry_vote ✅
RIGHT_BEGIN→RIGHT_IN: distance(2002) ✅ heading=0.3°
RIGHT_IN→RIGHT_RUNNING: gyro(617) ✅ dist=570
RIGHT_RUNNING→RIGHT_OUT: gyro(2009) ✅ dist=1616
RIGHT_OUT→RIGHT_END: gyro(2808) ✅ dist=479
RIGHT_END→NONE ✅

## 结论

三处修改中 RUNNING clamp 效果最显著——解决了 yaw 饱和问题，让 IN→RUNNING 过渡后
车可以找到真实线。但 IN offset（30 还不够）和 RUNNING 固定线振荡仍需大佬继续调。

## 原始日志

logs/live-circle/20260621-drive170-front_car_circle_drive170.log (5833 lines)
