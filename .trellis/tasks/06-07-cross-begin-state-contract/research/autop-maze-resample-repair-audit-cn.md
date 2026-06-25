# 巡线审计备忘录

日期：2026-06-10

## 结论

当前巡线主链已经和 AuTop 思路基本一致：按需局部阈值、迷宫法追边、IPM 查表、点集平滑/重采样、单边外扩中线、元素状态机选边。

现在需要守住的不是“重写迷宫法”，而是以下合同：

- 十字：strict double-L 进入，`CROSS_IN` 用远线 trace -> IPM -> resample -> 远 L 后外扩生成控制候选。
- 环岛：单 L + 对侧直线进入，按 `BEGIN -> IN -> RUN -> OUT -> END` 切换内外侧候选；RUN 阶段发现外环 L 先裁线，近处 L 才切 OUT。
- ring 内部补对侧边界只服务检测、诊断和显示，不发布当前帧控制中线。
- 本帧元素动作来自帧首 `frame_action_t`；`element_process()` 推进出的新状态留到下一帧生效。
- `build_selected_midline()` 只消费明确候选：十字远线、左候选或右候选。

## 参考合同

本轮 claim-level 证据以本地代码为准：

- RT1064 参考：`/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/cross.c`
- RT1064 参考：`/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/circle.c`
- 当前实现：`code/tracking/{imgproc,perspective,boundary,cross,ring,mainline}.cpp`

知乎正文在当前环境会被登录墙挡住，用户转录内容只作为背景；逐行合同仍以 RT1064 参考代码和当前仓库文件为准。

## 当前链路

- 二值化：`imgproc.cpp::calc_th_core()` 按需局部阈值，不做全图二值化。
- 起点：`find_seeds()` 使用动态 `mid_position` 找左右 seed。
- 追线：`trace_single()` 左/右手规则沿白边界走线。
- IPM：`perspective_points()` 查 `g_raw_to_ipm_x/y` 表。
- 点集处理：`blur_points()` 三角滤波，`resample_points()` 等距采样。
- 中线：`track_leftline()` / `track_rightline()` 单边外扩，`build_rptsn()` 从控制参考点归一化中线。
- 元素：`cross_process()` 和 `ring_process()` 只维护元素状态和检测几何；最终控制候选由 `build_selected_midline()` 选择。

## 关键修改

### 环岛诊断与显示

- `types.hpp` 增加 `ring_opp_*` 诊断字段。
- `ring.cpp::record_ring_opp_diag()` 记录 ring 内部补边的最终检测状态。
- `report.cpp` / `runners.cpp` 输出 `xrng` 和 key/value 字段。
- `assistant.cpp` 在灰度图上叠加 ring 补边显示。

这部分不改变控制行为。`ring_opp_*` 不表示当前帧控制中线使用了补线。

### 边界角点合同

- `boundary.cpp` 已有三点角度、NMS、单 L、strict double-L、直线判断。
- `boundary_contract_test.cpp` 固定三类输入：直线、单 L + 对侧直线、双 L 张开。
- `element_entry_contract_test.cpp` 固定 cross/ring 入口消费语义。

### Calvariaa PR #6 回归合同

Calvariaa fork 的关键提交已经合入官方 RT1064 master。当前项目用测试锁住对应风险：

- `midline_lookahead_test.cpp`：`resample_points()` 不回到原点、不重复旧点。
- `line_trace_contract_test.cpp`：`region_otsu()` 只消费指定区域，区域外亮区不污染阈值。
- `search_center_learning_test.cpp`：控制参考点查表索引保持 `[raw_y][raw_x]`。

### 环岛 RUN

- `boundary.cpp` 拆开 `l_found` 和 `l_ok`：`l_found` 表示扫描范围内发现 L，`l_ok` 表示近处可消费 L。
- `mainline.cpp::snapshot_ring_frame_start_crop()` 在 RUN 阶段用外侧 `l_found` 裁剪本帧候选。
- `ring.cpp` RUN 阶段也用 `l_found` 先裁线，但切 OUT 仍要求近处 L。
- `element_entry_contract_test.cpp` 和 `element_deferred_mode_test.cpp` 固定“远 L 先裁线、不提前 OUT”的行为。

### 帧首动作

- `mainline.cpp` 删除 live-state fallback；ring 选边只由帧首 `action.ring_kind0/action.ring_state0` 推导。
- `candidate_crop_side/index` 只在真实执行 ring 裁剪时写入。
- `element_deferred_mode_test.cpp` 固定新进入 cross/ring 不抢当前帧普通候选。

### 十字远线 L

- `cross.cpp` 增加 `k_cross_far_l_reuse_max = 1`。
- 远线 L 漏检只桥接 1 帧；第二个连续漏检帧释放旧 L。
- `cross_farline_reuse_test.cpp` 固定 NEW -> REUSED -> NONE 的生命周期。

## 理由表摘要

| 主题 | 参考版怎么样 | 当前处理 | 不是兜底的证据 |
| --- | --- | --- | --- |
| ring 补边诊断 | RT1064 圆环主要是状态机选边和 RUN 裁剪现有候选 | 只增加 `ring_opp_*`、`xrng`、灰度叠加显示 | 不写 `track_type`，不改 `guide_error`，不改 `rptsc0/rptsc1` |
| 角点/直线 | RT1064 用局部角 + NMS 判断 L/straight | 增加 `boundary_contract_test` 和入口合同测试 | 不改阈值，不改状态机，只锁住当前帧信号 |
| Calvariaa 修复 | PR #6 修过重采样、区域 OTSU、查表索引 | 用最小回归测试锁住当前实现 | 不改运行时逻辑，只防止回退 |
| ring RUN | 参考版 `Lpt_found` 先裁线，近 L 才 OUT | RUN 裁线用 `l_found`，OUT 仍用近处 index | 只用当前帧 L 点，不补圆、不猜线 |
| 帧首动作 | 当前项目额外建立帧首动作合同 | ring 选边只读 frame action，删除 current-state fallback | 帧首状态无法推导时显性无候选，不读 post-element 状态兜底 |
| cross 远 L | 参考版每帧重新找远 L | 当前只允许旧 L 桥接 1 帧 | 超过 1 帧清 `far_l=-1`、`source=NONE` |

## 控制补线候选项

控制补线可以作为后续增强，但不是当前参考版合同。

只有出现以下证据时才考虑落地：

- 元素态 `selected_mid_ok` 经常不足，导致 `TRACK_REJECT_NO_MIDLINE` 或前瞻点不够。
- `guide_error` 在十字/环岛特定阶段跳变，且状态机选边正确、真实候选线确实被截得过短。
- `ring IN/OUT` 或 `cross BEGIN/IN` 可视化显示真实边界消失，但几何可由角点、已知宽度和状态阶段稳定推出。

落地边界：

- 不把补线作为静默 fallback。
- 不复用旧中线或旧边线。
- 不把 `ring_opp_*` 直接接进 `rptsc0/rptsc1`。
- 如需参与控制，应新增明确路径，例如 `solve_ring_mid()` 或 `ring_control_candidate`，并输出来源、输入点数、输出点数、是否用于中线、最终 `guide_error`。

## 验证

已建立或更新的 host 测试：

- `cross_farline_reuse_test`
- `line_trace_contract_test`
- `boundary_contract_test`
- `element_entry_contract_test`
- `midline_lookahead_test`
- `search_center_learning_test`
- `element_deferred_mode_test`
- `ring_opp_diag_test`

常规验证命令：

```bash
git diff --check
bash code/test.sh --host
bash code/test.sh
```

## 后续排查顺序

如果实车或 replay 表现异常，优先看这些字段：

- 十字：`cross_mid_fail`、`cross_left/right_l_source`、`cross_left/right_l_reuse_count`、`mode_cross_far`、`selected_mid_ok`。
- 环岛：`mode_ring_active`、`candidate_crop_side/index`、`ring_opp_*`、`selected_mid_ok`。
- 控制：`guide_error` 是否稳定；若 `guide_error` 稳定但车体扭，优先查差速控制而不是 tracking。

不要优先做的事：

- 不重写迷宫法。
- 不改回全图二值化。
- 不直接照搬 376x240 的像素常数。
- 不靠改 `ROAD_HALF_WIDTH` 或补线阈值掩盖标定/IPM 问题。
