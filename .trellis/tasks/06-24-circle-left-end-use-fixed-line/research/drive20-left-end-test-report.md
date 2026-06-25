# drive20: 左环 LEFT_END 测试报告

## 元信息

| 项目 | 值 |
|---|---|
| 日期 | 2026-06-24 |
| 测试 | 左环 LEFT_END 使用固定拼接线 (`circle_out_fixed_right`) |
| Log | `logs/live-circle/20260624-drive20-left_end_test.log` |
| 行数 | 5230 |
| 帧率 | 120 fps |
| 打印间隔 | 1 (每帧) |
| 二进制 | commit `9c2b1ce` + uncommitted 9 files (含 LEFT_END fix) |
| 环境 | FRONT_CAR_ENABLE_DRIVE=1, FRONT_CAR_PRINT_DIV=1 |

## 左环状态帧数

| 状态 | 帧数 |
|---|---|
| CIRCLE_LEFT_BEGIN (1) | 233 |
| CIRCLE_LEFT_IN (3) | 31 |
| CIRCLE_LEFT_RUNNING (5) | 158 |
| CIRCLE_LEFT_OUT (7) | 32 |
| CIRCLE_LEFT_END (9) | **7** |

## LEFT_END 序列

```
帧    guide   yaw     dist  duty     conf       线状态
540  -9.61    769      0   0/20     25.4/0.0   near=1/0 sel=1/0
541  -11.72   937     12   0/21     25.5/0.0
542  -13.12  1050     24   0/21     26.1/0.0
543  -14.37  1149     38   0/20     24.9/0.0
544  -15.93  1274     53   0/19     26.9/0.0
545  -17.92  1433     69   0/18     26.7/0.0
546   0.00     0      87   0/0      0.0      line=0 丢线
```

## 关键行为

- **guide 全负**（-9.6 ~ -17.9）：视觉出右转指令，但 duty=0/20（仅右电机）实际产生左转
- **yaw 增长** 769→1433：车头持续向左增加，方向正确
- **只维持 6 帧**、dist=87，远 < CIRCLE_END_EXIT_MIN_COUNTS=800
- 之后 stall 30 帧 → reset

## 多轮 LEFT_END 对比

| 轮次 | 有效帧 | guide 范围 | 最大 dist | 特征 |
|---|---|---|---|---|
| drive17 | 6 | -12~-19 | 76 | 全程负 guide |
| drive18 | 多次 | -30~+49 | 291 | **出现翻正** +12~+49 持续 4 帧 |
| drive19-1 | 3 | +15~+22 | 287 | **全程正 guide** |
| drive19-2 | 多段 | -30~+29 | 363 | Phase 2 正 guide 持续 7 帧 |
| drive20 | 6 | -9~-18 | 87 | 全程负 guide |

## 结论

1. **固定线 fix 有时能给出正确方向**（guide 翻正时是左转退出方向）
2. **但不可控**：是否翻正取决于车进入 END 位置时的线条件
3. **所有轮次最终均丢线 stall**，无一次 dist 接近 800
4. **瓶颈**：LEFT_END 期间可用线太少（near=1），维持不了足够距离
