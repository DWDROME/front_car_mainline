# 左环三测综合逐帧分析 (drive44/45/46)

## 1. 入口防误判机制 (ray hit) 验证

三测全部显示 `hit=1`，射线命中内圆边界:

| 测试 | 种子点 | 命中射线 | 命中点 | 说明 |
|---|---|---|---|---|
| drive44 | seed=56,28 | ray=-1,0 (水平) | hit=1@18,28 | ✅ |
| drive44 | seed=56,28 | ray=-1,-1 (左上) | hit=1@47,19 | ✅ |
| drive45 | seed=57,26 | ray=-1,0 | hit=1@16,26 | ✅ |
| drive46 | seed=54,30 | ray=-1,0 | hit=1@17,30 | ✅ |

结论：三测射线全部命中，未出现 false negative。drive28 类假开口待验证。

---

## 2. 入口阶段逐帧 (BEGIN→IN)

### drive44 (heading链)
```
BEGIN→IN: entry_distance, heading=101°, dist=2010, begin_dist=3339
IN→RUNNING: gyro, heading=612°, dist=633
RUNNING→OUT: gyro, heading=2000°, dist=2480
OUT→END: gyro, heading=2666°, dist=430
END→NONE: vision_lpt_exit, heading=2782°, dist=68
```

### drive45
```
BEGIN→IN: entry_distance, heading=0°, dist=2013, begin_dist=3698
IN→RUNNING: gyro, heading=609°, dist=625
RUNNING→OUT: gyro, heading=2005°, dist=2462
OUT→END: gyro, heading=2674°, dist=449
END→NONE: vision_lpt_exit, heading=2799°, dist=296
```

### drive46
```
BEGIN→IN: entry_distance, heading=0°, dist=2002, begin_dist=3476
IN→RUNNING: gyro, heading=600°, dist=634
RUNNING→OUT: gyro, heading=2010°, dist=2497
OUT→END: gyro, heading=2673°, dist=463
END→NONE: vision_lpt_exit, heading=2800°, dist=81
```

三测 BEGIN→IN 全用 entry_distance (dist≈2000-2013)，一致性好。

---

## 3. 环中关键角度与速度

### drive45 各阶段 duty/rps
| 阶段 | heading | duty | rps左 | rps右 | 趋势 |
|---|---|---|---|---|---|
| BEGIN末 | 0° | 9/7 | 4000/3600 | 平衡推进 |
| IN首 | →600° | 24/-10 | 8445/-845 | 左转(右电机反转) |
| IN末 | 609° | 17/0 | 7348/252 | 渐平稳 |
| RUNNING首 | 609° | 12/3 | 5851/1749 | 转弯减轻 |
| RUNNING末 | 2005° | 15/0 | 7094/506 | 右轮几乎停 |
| OUT首 | 2005° | 27/-12 | 9810/-2210 | 强左转(右轮反) |
| OUT末 | 2674° | 21/-6 | 8714/-1114 | 仍左转 |
| END首 | 2674° | 1/15 | 3395/4205 | 右轮从反转→正转 |
| END末 | 2799° | 9/7 | 正常化 | 准备exit |

**OUT 全程饱和**——guide=49.82 静态 28~37 帧。

---

## 4. END 阶段逐帧对比

```
字段: frame | guide | near | duty | yaw | heading | dist

drive44 (6帧, dist=68 exit):
530: +4.42  25/61  3/14  -354   → 正入END
531: +2.64  26/56  2/15  -212
532: -1.33  27/51  1/17   107   ← 穿零
533: -3.74  28/47  1/16   299
534: -5.26  29/43  2/16   421
535: -7.59  30/38  1/15   608   ← vision_lpt_exit dist=68

drive45 (22帧, dist=296 exit):
574: +2.29  24/60  1/15  -183   → 正入END
575: +0.17  25/55  0/16   -14   ← 穿零
576: -1.35  26/50  1/16   108
577: -3.82  27/46  1/16   306
578: -6.04  28/42  2/16   483
579: -7.72  29/38  2/15   618
580: -5.48  30/0   3/13   438   ← 右线消失!
581:~590: -7~-11  31~33/0 2/15  持续负guide
592:~596: -8→-3   32~28/0 3/15→9/7 逐渐回正但exit前仍是-2.97

drive46 (7帧, dist=81 exit):
542: +5.80  24/63  4/14  -464   → 正入END
543: +3.63  25/58  3/15  -290
544: +1.60  26/53  2/15  -128
545: +0.16  27/49  3/15   -13   ← 穿零
546: -2.43  28/45  2/15   195
547: -4.16  30/41  3/15   333
548: -6.14  30/37  2/15   491   ← vision_lpt_exit dist=81
```

---

## 5. END→NONE 退出分析

### drive44 exit
```
END末: guide=-7.59  dist=68
CIRCLE_NONE首帧: guide=?  (4s太短)
```

### drive45 exit (错误-反方向)
```
END末: guide=-2.97  duty=9/7  dist=296 heading=2799°
CIRCLE_NONE首帧: guide=-5.32  duty=8/16  road=2
→ 出环后 guide 仍负 → 反向走
```

### drive46 exit
```
END末: guide=-6.14  duty=2/15  dist=81 heading=2800°
CIRCLE_NONE首帧: guide=-5.98  duty=13/21  road=1
→ 出环后 guide 仍负 → 同样反向
```

---

## 6. 一致性问题总结

| 问题 | 描述 | 严重度 |
|---|---|---|
| 右线消失后guide偏负 | END中段右线消失→只剩左半线→guide恒负 | 🔴 P0 |
| 出口heading太早 | 2799~2800°, 距3550°差750°(75°) | 🔴 P1 |
| exit时guide为负 | drive45=-2.97, drive46=-6.14 | 🔴 P0 |
| OUT全程控制饱和 | guide=49.82,yaw=-3986定死,37帧不变 | 🟡 P2 |
| END帧数不稳定 | 6帧~22帧,取决于右线何时消失 | 🟡 P2 |

## 7. 核心矛盾

**guide 不能在 END 内恢复为正方向。** 右线一消失→只剩左半线(rptsc0)→选线方向偏右→guide 恒负。drive45 跑了 22 帧也没能翻正。要解决必须动 END 的选线逻辑——右线消失后改回固定 OUT 线或另一线源。

---

## 8. 2026-06-24 修复:LEFT_END 专用右直线 + 视觉退出最小距离

### 结论

这不是入口问题,也不是继续调 `CIRCLE_HEADING_READY_OUT_TO_END_DEG10=2660`
的问题。drive44/45/46 显示切入 `LEFT_END` 后改用当前右半线,右线逐步
变短并消失,guide 随之穿零变负;drive49/50/51/52 显示直接复用 OUT
固定线会让 `sel=23/17` 且 `guide=49.82` 饱和。左环正确出环方向应
保持正 guide,但不能沿用 OUT 的内圈强转线,因此修复点是给 `LEFT_END`
单独建立一条更接近右直道交棒方向的固定右线。

### 改动

`build_circle_spliced_lines()` 对 `CIRCLE_LEFT_END` 构建 END 专用右固定线:
右下角锚点 -> raw `(110,70)`。这不是 OUT 固定线的 raw `(45,70)`,避免
drive49/52 的 `guide=49.82` 大转圈。`select_work_line()` 在 `LEFT_END`
优先选择该线源并标记为 `circle_end_fixed_right`;原 `circle_end_right_half`
保留为固定线不可用时的次级当前帧线源。

同时,`circle.c` 给左环 `vision_lpt_exit` 增加最小 END 距离:
`total_distence >= 300`。该门只阻止刚进 END 就被近 Lpt 立即退出:
drive44/46 的 `dist=68/81`,drive50/51 的 `dist=0`,以及 drive45 的
`dist=296` 都会被挡住;不修改 `2660` 进 END heading 阈值,也不修改控制链。

### Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| ATG/port 已把 `LEFT_OUT` 映射为固定右斜线,用于 ReadyoutRing 出环引导 | 本车 `LEFT_END` 直接切到当前右半线;drive44/45/46 中右线变短/消失后 guide 从正穿零到 -7~-11;直接复用 OUT 线则 drive49/52 饱和 `guide=49.82` | `reference_step.c::build_fixed_right_center_for_left_end()` 构建 raw `(110,70)` END 专用右线,`select_work_line()` 标记 `circle_end_fixed_right` | 左环出环应继续保持正 guide,但 END 需要右直道交棒方向,不能再用 OUT 内圈强转目标 | 每帧重新构建固定线,不复用旧帧;目标点来自实测区分 OUT 饱和和 END 负 guide 两类失败 |
| ATG `LEFT_END` 视觉退出只看近 Lpt | 本车 drive44/46/50/51 刚进 END 即 `vision_lpt_exit` 或短距离退出,出环时 guide 仍负/或固定线只执行 1 帧 | `circle.c::CIRCLE_LEFT_END` 要求 `total_distence >= 300` 才允许 `vision_lpt_exit` | 300 counts 来自当前日志:挡住 0/68/81/296 的 early exit,给 END 线源至少一个短行驶窗口 | 这是退出条件延后,不是伪造线;距离不够时仍停留在显式 `LEFT_END`,最终仍有 7500 distance 兜底 |

### 下一趟 live 看点

- `CIRCLE_LEFT_OUT -> CIRCLE_LEFT_END` 仍应在 heading 约 2660 附近,确认没有改阈值。
- `circle=9(CIRCLE_LEFT_END)` 内线源应为 `circle_end_fixed_right`/source id 14;live/replay 单行日志现在会打印 `src=14`。
- guide 应保持正值或至少不持续为负,同时不应再长时间钉死 `49.82`。
- drive45/46 类场景中右线 `near=*/0` 后不应再出现 guide 长时间 `-7~-11`。
- 不应再出现 `END -> NONE reason=vision_lpt_exit dist=0/68/81/296`。
- `END -> NONE` 前 guide 应接近 0 或为正;`CIRCLE_NONE` 首帧不应仍为明显负值。
