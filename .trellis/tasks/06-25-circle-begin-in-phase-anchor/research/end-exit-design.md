# circle END 安全出口设计（视觉主出口 + END 局部编码器防死锁）

## 结论

END 不恢复全阶段 distance 兜底，也不使用帧数 timeout。

当前只保留两条 END 出口：

1. `vision_lpt_exit`
   - `heading >= 3550`
   - 出口近角点出现：左环 `Lpt1_rpts1s_id < 15`，右环 `Lpt0_rpts0s_id < 15`
2. `end_encoder_release`
   - `heading >= 3300`
   - END 内局部编码器距离 `total_distence >= 8000`

## 为什么不用帧数

同样的 END 帧数在不同车速下代表不同物理距离：

- 车速快：120 帧可能已经走很远
- 车速慢：120 帧可能还没出完
- 低速卡住：帧数到了但物理位置没到

所以死锁保护用 END 内编码器距离，而不是 END 帧计数器。

## 为什么还要 heading 门

只看 END 内距离仍可能太早：车如果还在圆里绕，编码器也会涨。

因此 encoder release 必须叠加软 heading 门：

```text
heading >= 3300 && END 内 total_distence >= 8000
```

含义是：车已经基本绕完，只是 `3550 + Lpt` 没同时出现，不再让 END 固定补线无限生效。

## 实现约束

- `OUT -> END` 保留 `Count_dis_Flag = 0`，同帧 `update_distance_counters()` 会清零 `total_distence`。
- 下一帧 END 设置 `Count_dis_Flag = 1` 后，`total_distence` 就是从进入 END 后累计的局部距离。
- 右环 END 和左环 END 对称：视觉出口都必须叠加 `heading >= 3550`。
- `finish_circle_exit(reason)` 只封装原 END 退出清理动作，不添加新状态。
- `ATGCircleEndDiag` 输出 `heading/dist/rpts/straight/Lpt/lpt_exit/encoder_release`，用于上车标定。

## 调参规则

- 正常样本都走 `vision_lpt_exit`：不用管 encoder release。
- 卡死样本触发 `end_encoder_release`：阈值方向正确。
- 大量正常样本都走 `end_encoder_release`：优先检查视觉出口是否太严，再考虑提高 `CIRCLE_END_MAX_DIST`。
- `end_encoder_release` 后车仍在圆内：先把 `CIRCLE_HEADING_FINISH_SOFT_DEG10` 从 3300 提到 3400，不先加距离。
