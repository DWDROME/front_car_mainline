# drive35 LEFT_END 转不起来分析

日期:2026-06-24
日志:`logs/live-circle/20260624-drive35-lpt12.log`

## 结论

drive35 不是 `END->NONE` 退出条件太早,而是 `OUT->END` 太早。进入 `LEFT_END`
后 guide 很快穿零变负,随后右线消失,END 内部已经没有能力继续把车向出环方向转起来。

因此本轮不继续压 `CIRCLE_END_LPT_EXIT_ID`,改回用
`CIRCLE_HEADING_READY_OUT_TO_END_DEG10` 延后 `OUT->END`,让
ReadyoutRing/OUT 固定线多带一段再交给 END。

drive36 的 2800 实测不是让 END 首帧变正,而是让普通巡线接棒后 2 帧内回正:
`LEFT_END->NONE` 时 guide=-1.20,`NONE` 首帧 -0.93,下一帧 +0.68。相比 drive35
`NONE` 首帧 -13.93 且后续多帧负向,2800 是当前证据下更接近正确交棒的位置。

## 关键帧

| 帧 | 状态 | heading | dist | near | Lpt | guide | 说明 |
|---|---|---:|---:|---|---|---:|---|
| 532 | LEFT_OUT | - | 479 | 25/67 | Lpt1@22 | +49.82 | 仍在 OUT 固定线强左转 |
| 533 | LEFT_END | 2672 | 0 | 26/61 | Lpt1@21 | +3.63 | 切入 END,方向刚开始还对 |
| 535 | LEFT_END | - | 27 | 28/51 | Lpt1@19 | +0.42 | guide 快穿零 |
| 536 | LEFT_END | - | 42 | 29/48 | Lpt1@18 | -1.79 | 已开始右转 |
| 539 | LEFT_END | - | 87 | 31/36 | Lpt1@15 | -7.11 | 右线变短,guide 继续负 |
| 543 | LEFT_END | - | 144 | 33/0 | none | -9.09 | 右线消失 |
| 552 | LEFT_END | - | 266 | 31/0 | none | -6.31 | 退出前仍为负 |
| 553 | NONE | 2789 | 0 | 31/19 | Lpt1@8 | -13.93 | 普通巡线接棒仍右转 |

对比 `CIRCLE_END_LPT_EXIT_ID=15` 与 `12`:退出 heading 只从 2759 到 2789,
增加约 30 deg10,但 guide 从 -2.42 变为 -6.31,没有解决"END 内不再左转"。

## 改动 rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `circle.c` 主状态机允许 `LEFT_OUT` 用 heading 门进入 `LEFT_END`; ittuann/Joshua 类 heading 分阶段方案也把出环交棒放在角度门上 | drive35 在 heading=2672 进 END 后 guide 第 3 帧变负,右线消失后持续负;继续调 END 退出 ID 不改变 END 内转不起来 | `CIRCLE_HEADING_READY_OUT_TO_END_DEG10: 2660 -> 2800`;`CIRCLE_END_LPT_EXIT_ID` 保持源码默认 15 | 让 OUT/Readyout 固定线多转一段再进入 END;drive36 在 heading=2817 进 END,END->NONE 后 2 帧 guide 回正 | 没有复用旧线或伪造几何;只是延后状态交棒,下一趟 live 直接看 OUT->END heading 和 END 首尾 guide |

## 下一趟 live 看点

- `ATGCircleCal: LEFT_OUT -> LEFT_END` 的 `heading_deg10` 应接近 2800。
- `LEFT_END -> NONE` 前 guide 应接近 0;`NONE` 后 1-3 帧应回正。
- 若 `NONE` 后仍持续负向,不要继续压 `CIRCLE_END_LPT_EXIT_ID`;优先复核 END 选线几何。
