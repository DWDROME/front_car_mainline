# 左环测试记录汇总 drive20-28

## 已知 Log 清单

| Log | 阈值 | 状态 | 问题 |
|---|---|---|---|
| drive20 | 原始代码 | ❌ END stall | guide全负，END 4帧丢线 |
| drive21 | 原始代码+fix | ❌ 位置差 | END 1帧 |
| drive22 | 同 | ❌ END stall | END 8帧但guide全负 |
| drive23 | 同 | ❌ END stall | END 4帧 guide=-13~-17 |
| **drive24** | **2600** | **✅ 成功** | END guide=+1.3穿零→+0.3出环，无stall |
| drive25 | 2500 | ❌ 出环反方向 | END guide=-5 退环右转回起点 |
| drive26 | 2600复现 | ✅ 复现成功 | END guide=+8.9穿零→出环 |
| drive27 | 2650 | ✅ 还可以 | END guide=+4.2穿零，平滑 |
| drive28 | 2660 | ❌ 误入环 | **frame=81就触发了LEFT_BEGIN**，还离环很远 |

## 成败规律

### LEFT_END 退出（已基本解决）
- **2600~2660 都能出环**，guide 从正起始→穿零→退出
- 2650 是中间值：guide=+4.2 起始，穿零自然
- 2500 太早退环→方向反
- 2700 太迟退环→guide 已经负了

### 圆环入门检测（新问题）
- **drive28 在 frame=81 就触发了 LEFT_BEGIN**
- 用户说刚过第一个开口就误判，离真环还很远
- 综合之前测试，急弯/赛道不平都容易误触发
- 这意味着 circle entry 检测的阈值或条件过于宽松

## 建议
- 当前 READY_OUT_TO_END=2660 表现可以，但**入门误判**是更大的问题
- 需要调松 entry detection 的条件——比如加大需要的角点数、提高conf门限、或加入距离/headin约束
