# ATG 环岛问题记录

时间：2026-06-13

## 当前结论

这轮实机不是“算法完全没有进入环岛”。板端日志显示状态机已经进入左环岛，并按以下顺序推进：

```text
CIRCLE_LEFT_BEGIN -> CIRCLE_LEFT_IN -> CIRCLE_LEFT_RUNNING -> CIRCLE_LEFT_OUT
```

但从现场观察看，车体/上位机表现不像稳定入环；最后在 `CIRCLE_LEFT_OUT` 阶段选线为空，触发了 port 层的 `ATGCircleStall` 复位。

因此环岛问题现在拆成两件事：

- 状态机能进入环岛：已确认。
- 环岛状态是否正确引导车体入环、上位机是否正确显示环岛状态：仍未确认。

## 实机证据

关键日志片段：

```text
frame=60   line=1 cross=0 circle=1(CIRCLE_LEFT_BEGIN)  l=1@24/0@-1 straight=0/1
frame=480  line=0 cross=0 circle=3(CIRCLE_LEFT_IN)     sel=0/0 l=1@13/0@-1
frame=510  line=1 cross=0 circle=5(CIRCLE_LEFT_RUNNING)
...
frame=2460 line=0 cross=0 circle=7(CIRCLE_LEFT_OUT)    sel=0/0 l=0@-1/1@9
ATGCircleStall: circle_type=7 stalled 30 frames without selected line, reset to NONE
frame=2490 line=1 cross=0 circle=0(CIRCLE_NONE)
```

含义：

- `frame=60` 起，左环岛入口已被 `check_circle()` 或 `Half_check()` 触发。
- `frame=480` 进入 `CIRCLE_LEFT_IN` 时出现一次 `sel=0/0`，但后续又恢复到 `CIRCLE_LEFT_RUNNING`。
- `frame=510` 到 `frame=2430` 大量帧停留在 `CIRCLE_LEFT_RUNNING`，说明状态机长时间认为车处于左环运行段。
- `frame=2460` 进入 `CIRCLE_LEFT_OUT` 后选线为空，差速车停车。
- `ATGCircleStall` 生效，把错误/停滞的环岛状态复位到 `CIRCLE_NONE`，避免永久锁死。

## 已经修过的环岛相关问题

### 1. `circle.c` 左环状态块括号错误

`CIRCLE_LEFT_IN` 的结束括号位置曾导致后续逻辑脱离原状态分支。已修正，让 `rpts1s_num > 25 && none_right_line > 1` 的 `CIRCLE_LEFT_RUNNING` 转移留在 `CIRCLE_LEFT_IN` 内。

同时给 `CIRCLE_LEFT_OUT` 的出口条件补了括号：

```c
if((rpts1s_num > 30 && !Lpt1_found && none_right_line > 1) || total_distence > 4500)
```

### 2. 环岛停滞出口

ATG 原工程是舵机车，选线失败时车仍会继续滚动，状态机可依赖视觉变化或 `total_distence > 4500` 退出。当前差速车在 `line_found=0` 时直接停车，画面和编码器都冻结，可能死锁。

已在 `atg_reference/port/reference_step.c` 增加 port 层停滞出口：

```text
circle active 且连续 30 帧无 selected line -> reset circle_type 到 CIRCLE_NONE
```

这不伪造线，也不复用旧帧，只释放已经无法满足物理出口条件的环岛状态。

### 3. 环岛补线中心每帧清零

`Splicing_leftline_center_num` / `Splicing_rightline_center_num` 现在每帧重建。补线失败时选线显式为空，避免拿旧帧补线继续控制。

### 4. 单 L 误入环岛捷径加对侧证据

`Half_check.c` 原本有“近 L `<5` 且无远 L”直接进入环岛的捷径，这是原作者赛道先验，不是几何证据。当前赛道斜车身靠近十字时会丢对侧线，容易误入左环。

现在两侧捷径都补了对侧长直线证据：

```c
// 左环捷径
Lpt0_rpts0s_id < 5 && !far_Lpt0_found && is_straight1

// 右环捷径
Lpt1_rpts1s_id < 5 && !far_Lpt1_found && is_straight0
```

这与 `check_circle()` 正门条件一致。

## 当前未解决点

1. 上位机状态显示未知

日志能证明 `circle_type` 已进入并推进，但上位机是否画出环岛状态、是否有对应颜色/通道显示，目前没有证据。下一步如果要查显示，应看 `code/app/assistant.cpp` 是否发送 `circle_type` 或环岛补线通道，而不是继续猜状态机。

2. 车体不像稳定入环

虽然状态机进入了左环，但实际控制长时间停在 `CIRCLE_LEFT_RUNNING`，且最终靠 `CIRCLE_LEFT_OUT` 的右 L 触发出环。需要判断车体轨迹是否真的在跑环，还是被外侧右线牵着直走/偏走。

3. `CIRCLE_LEFT_RUNNING` 持续时间很长

从 `frame=510` 到 `frame=2430` 都是 `circle=5`。如果车已经绕完或错过出环点，这说明出环触发条件太依赖右 L：

```c
if (Lpt1_found && Lpt1_rpts1s_id < 0.7 / sample_dist)
    circle_type = CIRCLE_LEFT_OUT;
```

当前需要用实机画面确认右 L 是否真的出现但未被识别，还是车体轨迹导致右 L 根本不在预期位置。

4. `CIRCLE_LEFT_OUT` 仍会短暂停车

`ATGCircleStall` 已能恢复，但这只是解死锁。真正要跑顺，还需要 `CIRCLE_LEFT_OUT` 能产生有效补线，而不是靠 30 帧停滞后退出。

## 下一步建议

先不要再改速度环。环岛下一轮建议只做两类验证：

1. 显示验证

确认上位机是否能看见当前 `circle_type` 和环岛补线：

- 日志显示 `circle=1/3/5/7` 时，上位机是否有状态提示。
- 如果没有，补一个明显的 `circle` 文本/颜色标记或 boundary 诊断通道。
- 目的只是显示状态，不改变控制。

2. 轨迹验证

低速重跑左环，人工记录三个时刻：

- `CIRCLE_LEFT_BEGIN` 时车是否沿右外侧直线进环。
- `CIRCLE_LEFT_RUNNING` 时车是否真的贴环运行，还是近似直走。
- `CIRCLE_LEFT_OUT` 前后右 L 是否在画面中明显出现。

如果右 L 肉眼明显但日志 `Lpt1_found=0`，问题转到右 L 识别；如果右 L 不在画面预期位置，问题转到环岛控制线/补线几何。

## 2026-06-13 现场补充：第一角点和第二角点

现场观察：上位机能看到红色中线进入圆环，但只出现一两帧，之后消失；车体实际走得相对顺。

结合左环状态机，当前判断如下：

- 第一角点已经能识别。日志里的 `circle=1(CIRCLE_LEFT_BEGIN)` 通常由左侧近 L 触发，例如 `l=1@24/0@-1`、`l=1@7/0@-1`。
- 第一角点的作用是进入左环开始态。进入 `CIRCLE_LEFT_BEGIN` 后，算法主要沿右外侧线走，等待左线经历“丢线再出现”和距离条件，随后切到 `CIRCLE_LEFT_IN`。
- 第二角点不是入环用的，而是出环用的。左环在 `CIRCLE_LEFT_RUNNING` 阶段会等待右侧 L：

```c
if (Lpt1_found && Lpt1_rpts1s_id < 0.7 / sample_dist) {
    circle_type = CIRCLE_LEFT_OUT;
}
```

也就是说，按当前 ATG 状态机，左环完整闭环仍然需要识别第二个角点：右侧出环 L 点。没有这个角点，状态会长期停在 `CIRCLE_LEFT_RUNNING`；如果后续补线/选线失败，就只能靠 `ATGCircleStall` 解锁。

红色中线只短暂出现，优先怀疑的是 `CIRCLE_LEFT_IN/OUT` 阶段的补线显示/补线生成不稳定。因为 `select_work_line()` 在 `CIRCLE_LEFT_IN` 和 `CIRCLE_LEFT_OUT` 不再选普通右线，而是选 `Splicing_rightline_center`；一旦远线证据不足，补线中心为空，上位机上的红色中线就会消失。

当前不要把“红线消失”直接等同于“没进环岛”。日志能证明状态机已经进过环岛；下一步应分开确认：

- 红色中线消失时，状态是否在 `CIRCLE_LEFT_IN/OUT`。
- `Splicing_rightline_center_num` 是否为 0。
- 右侧第二 L 是否在 `CIRCLE_LEFT_RUNNING` 后段被识别到。
- 如果车体实际能顺利通过，但状态长期靠 stall reset 退出，说明控制轨迹可接受，但状态机出环证据仍不干净。
