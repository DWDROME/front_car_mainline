# 圆环渐进重构结论：视觉为主 + 陀螺门限 + END 视觉退出 (2026-06-24)

> 归档 2026-06-24 会话的圆环工作：三方状态机对比定位病根 → 渐进对症改动 → drive02/03/04/06 live 验证。
> 改动均在工作区未提交，host + cross build 全过（WSL，见 [[wsl-build-git-environment]]）。

## 方法：三方状态机对比（ATG 原版 / 我们 / Joshua）

| 阶段 | ATG 原版 | 我们(改造前) | Joshua |
|---|---|---|---|
| RUNNING→OUT | 对侧 Lpt 截断(视觉) | 纯陀螺 200° | 单调突变点 + 陀螺>200°门限 |
| 补线 | 角点截断 | Splicing 半边补线 | 半边补线/斜率死线 |

## 病根
我们当初为绕开 ATG 视觉门卡死，把各阶段切换**全换成纯陀螺角度阈值**(600/2000/2500/3550)，丢失当前帧视觉自校正 → 4 阈值难标定 + 陀螺零偏致状态错位 + IN guide 过猛 + OUT 补不出线。

## 改动清单（工作区未提交，build 全过）

| # | 文件:落点 | 改动 | 依据 |
|---|---|---|---|
| 阶段0① | `cross.c` cross_farline_R 右环IN丢线种子 | x `140→120` | 与左环 x=40 关于 W=160 镜像；140 偏右致远线搜索偏外→贴内 |
| 阶段0② | `cross.c` 同上动态种子 | y `-8→-5` | 与左环对齐 |
| 阶段1 | `reference_step.c` enum | `CIRCLE_FIXED_RIGHT_IN_TARGET_RAW_X_OFFSET 25→35` | 与左 35 镜像；25 使右环**主拼接线**目标偏内 10px→贴内（**主因**） |
| 阶段2 | `circle.c` 左右 RUNNING→OUT | 加「对侧 Lpt + 陀螺门限 1500」为主，陀螺 2000 兜底 | 恢复 ATG 视觉触发 + Joshua 陀螺门限 |
| END | `circle.c` 左右 END→NONE | 出口角点 `Lpt < CIRCLE_END_LPT_EXIT_ID(15)` 视觉退出，距离兜底 | drive04 出环口 Lpt conf96 id8；drive02 END Lpt1=1@9 在停车前 |

## Live 验证（drive02/03/04/06，均左环）

### ✅ END 视觉退出 — 成功（最大突破）
- drive06：END→NONE **22 帧 `vision_lpt_exit`**，vs drive02 **2000 帧 stall**
- frame522 id14<15 触发，出环后普通巡线接住、不停车
- END 时长 2000→22 帧；退出 stall→vision_lpt_exit；出环后 停车→继续

### ❌ RUNNING→OUT vision_lpt — 左环时序必败（认 gyro，非 bug）
- drive06 RUNNING 全程 140 帧 Lpt1=0；gyro 2008° 兜底
- drive04 手动放出环口：Lpt1 conf96 id8 清晰存在
- **铁律：左环出口角点 heading > 2000°（物理位置晚），gyro 2000° 必先触发。降 gate 无效（角点出现时车已离开 RUNNING）。**
- 右环未测（右转时左侧出口角点可能更早进视野，vision 可能有效）

## 关键结论（可引用）
1. **左环 vision_lpt 时序必败**：角点 heading > gyro 阈值 → 左环出环认 gyro
2. **出口角点 redirect 给 END**：清晰角点(conf96)用于 END 视觉退出，不是 RUNNING→OUT
3. **右环贴内双根因**：主拼接线 offset（主因）+ 丢线种子，均已对称化，待右环 live
4. **差速车丢线即停 = 移植根矛盾**：舵机车滑行能恢复，我们停车→stall；END 视觉退出趁有线交棒规避；同一根矛盾的另一表现见"出环后急弯死锁"

## 遗留问题

| 问题 | 优先级 | 说明 |
|---|---|---|
| 右环未测 | 高 | 阶段0 对称化 + RUNNING→OUT vision 右环是否有效 |
| 出环后急弯死锁(摆尾) | 高 | **独立于圆环的普通巡线/控制层问题**：road=3 急弯+单线(右丢)→guide 饱和 -46→丢线停→抓线猛打→死锁。落点 `control.cpp` guide 限幅/丢线策略，非 circle.c。与差速车「丢线即停」同根 |
| 十字未测 | 中 | HALF aim 对称化，见 `06-22-cross-entry-truncation` |
| EXIT_ID 微调 | 低 | drive06 id14 触发 / id16 不触发，差 1 点 |

## 后续 live 微调（已在工作区）
- `CIRCLE_END_MIN_EXIT_COUNTS=180`：END 至少跑一小段再允许视觉退出，防刚看到角点就秒放手交棒
- `CIRCLE_HEADING_READY_OUT_TO_END_DEG10` `2800→2600`

## 测试数据
- `logs/live-cross/20260622-drive02/03/04/06-*.log`
- drive04 78 行（出环口静止观察）、drive06 4651 行（左环完整运行）
