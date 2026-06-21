# 当前配置基线（2026-06-22）

## 核心参数

```cpp
// .trellis/inject_template.cpp
IN_SEED_MULT = 0.75      // 从 1.0 降到 0.75
RUNNING_SEED_MULT = 0.81 // 从 1.0 降到 0.81
OUT_SEED_MULT = 1.0      // 不改

rps_target = 3.8         // 从 4.2 降到 3.8
```

## 参数演化历史

| 版本 | IN scale | RUNNING scale | rps | 问题 |
|------|----------|---------------|-----|------|
| drive39 | 1.0 | 0.81 | 3.8 | RUNNING 后段外漂（guide 27→35, sel L 51→43, actual -1456→-1700） |
| drive42 | 0.75 | 0.81 | 3.8 | RUNNING 后段改善（guide 29→25, sel L 52→55, actual -1516→-1500） |
| drive43 | 0.75 | 0.81 | 3.8 | 重复性测试中 |

## 设计意图

### IN×0.75 的作用
- 削弱 IN 阶段的电磁引导强度
- 减少入环时的过度内偏
- 让车在 RUNNING 后段有更多外扩余地

### RUNNING×0.81 的作用
- 保持 RUNNING 阶段的电磁引导稳定性
- 避免过度削弱导致丢线

### rps=3.8 的作用
- 降低车速，给视觉和控制更多反应时间
- 避免高速下的轨迹振荡

## 实验证据
参见 `in-scale-075-evidence.md`（drive42 vs drive39 对比）

## 已证伪的方向
- **dynamic seed**（OUT seed 从 1.0 降到 0.6 在 30 帧内）：END 阶段 near L 稳定但 yaw 饱和，未改善
- **IN scale 大范围扫**（0.5-1.0）：和 IN dist、入环姿态强耦合，0.75 附近最有效

## 下一步验证
- drive43 重复性测试（配置不变）
- 判据：RUNNING 后段 guide 下降或稳定 25-30，sel L 不持续下降，actual 不继续负向发散
- 如果重复性差，试 IN×0.78（不回 1.0，不降到 0.70）

## 不改动的部分
- seed 初值（IN/RUNNING/OUT）
- 阈值（guide/near/dist）
- END 参数
- 视觉链（cross/IPM/外扩）
