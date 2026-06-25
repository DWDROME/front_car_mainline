# Geometry-driven circle entry rationale

## Scope

本轮只处理入环主线：

```text
A(Lpt) -> B row -> IN -> C point -> C anchored repaired line -> RUNNING
```

END 编码器释放是防死锁补洞，不是本文件的重点。

## Current behavior contract

- A 点：左环 `Lpt0`，右环 `Lpt1`。
- B 点：同侧边线 A 后继续扫描；左环找 raw_x 局部最大，右环找 raw_x 局部最小。
- BEGIN -> IN：`B` 连续确认 2 帧且 `B.raw_y >= 58`，transition reason 为 `B_row`。
- `mouth_ready`：只作为诊断字段保留，不再触发 IN。
- C 点：IN 阶段找同侧 raw_y 局部最大点，并要求比 B 更靠内侧。
- C 补线：C 连续确认 2 帧后才设置 `CIRCLE_REF_IN_C`；`reference_step.c` 才发布 `circle_in_c_left/right`。
- 当前 C 补线形状：同侧底部 raw anchor 到 C 点，然后复用 `track_leftline/track_rightline` 偏移半赛宽成中心线；不是 C 点到外侧直道的双边融合线。
- IN -> RUNNING：C 连续确认 2 帧且 heading >= 60 度。

## Change rationale table

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| Joshua circle-island 文档把环岛拆成结构点识别、分阶段补线和 gyro 切状态；三类关键特征包含角点、边界连续性、单调性转折。 | 本地 `circle.c` 只有 A 类 `Lpt0/Lpt1`，没有同侧 B/C；BEGIN->IN 由 `mouth_loss + begin_dist` 推进，`reference_step.c` 的 IN 旧逻辑无条件走 fixed line。 | `circle.c` 增加 A/B/C 几何状态；B 到指定 raw_y 行触发 IN；C 连续确认后设置 `CIRCLE_REF_IN_C`；`reference_step.c` 仅在 C 模式下生成 `circle_in_c_left/right`。 | 用户当前主问题是入环，不是 END；入环需要由当前帧入口几何和 C 补线决定，而不是丢线窗口和固定线。 | B/C 每帧从当前 `rpts0s/rpts1s` 逆变换 raw 坐标得到；没有 B/C 时不发布 C 补线，最终显式 line failure/stall，而不是复用旧线。 |
| ATG/Joshua 均保留 gyro 作为状态切换确认，而不是单独追某个目标点。 | 旧 IN->RUNNING 只看 heading，C 未找到也可能推进。 | IN->RUNNING 改成 `C_streak >= 2 && heading >= 600`。 | 没有 C 补线接管就不算真正入环；gyro 只确认已转入，不负责替代视觉几何。 | C 丢失时 `circle_ref_mode` 清为 `NONE`，不会隐藏成旧 fixed IN 路径。 |
| ATG 现有半边补线 helper `track_leftline/track_rightline` 已经根据一侧边界偏移半赛宽生成中心线。 | 直接新增双边融合器会扩大改动面，也会引入第二套选线真相源。 | C 补线先用 C 点和底部 raw anchor 构造人工边界，再复用 `track_leftline/track_rightline` 生成中心线。 | 这是最小改动：让普通 line-follow 控制消费 `rptsn`，不碰控制链。 | 仍是当前帧 C 点生成的边界；`build_circle_spliced_lines()` 每帧清空 splice 数量，不会复用上一帧中心线。 |

## Known risks before live test

- B/C 显著度不足：当前 B 是 raw_x 局部极值，C 是 raw_y 局部极值，没有 Lpt 的角度显著度门。普通弯道也可能出现局部极值。先用日志确认误判率；若普通弯误触发，再把 `mouth_ready` 从诊断字段升级为 `B_row` 的 AND 确认。
- C 补线锚点：当前是同侧底部 raw anchor -> C，不是 C -> 外侧直道。如果 `circle_in_c_*` 的 guide 形状不对，下一步应单独改补线锚点，不要同时改 B/C 识别。

## Live log checks

实车日志重点看：

- `ATGCircleABCDiag phase=BEGIN`：B 是否连续出现，`B_row_ready=1` 时 `B.raw_y` 是否合理。
- `ATGCircleCal ... to=CIRCLE_LEFT_IN/CIRCLE_RIGHT_IN reason=B_row`：确认没有 `mouth_loss` transition。
- `ATGCircleABCDiag phase=IN`：C 是否连续出现，`C_ready=1` 后 `ref=2`。
- 普通帧 `src`/selected-line source：IN 内应出现 `circle_in_c_left`/`circle_in_c_right`，source id 为 `15/16`。
- 若 C 找不到，预期是没有 C source，必要时由 `ATGCircleStall` 暴露，而不是旧 fixed IN 静默接管。
