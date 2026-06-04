# seed/搜索中心层 → 十字/环岛状态机 连锁依赖分析

调研日期 2026-06-05。范围：front_car_mainline `code/tracking/`，对照 RT1064 `SJTU-AuTop-RT1064-Code/Project/CODE/cross.c`、`circle.c`、`imgproc.c`。
结论性质：依赖链均为代码事实（行号已核），“seed 修好后是否缓解”为推断。

---

## A. l_ok 的上游依赖链（front_car）

每帧入口 `tracking_process_frame()`（mainline.cpp:438）严格串行，任一步断 → 下游 l_ok=0：

1. `find_seeds()`（mainline.cpp:460 → imgproc.cpp:215）
   - 搜索中心 `center = *mid_position`（imgproc.cpp:233-239），在**固定行 START_HIGH** 起搜，单侧丢失时只向上补搜缺失侧（imgproc.cpp:274-300）。
   - **断点1**：边界出画 / 搜索中心偏 → `ok0`/`ok1` 不成对（imgproc.cpp:246-258）→ seed_state 缺一侧 → 该侧后续全断。
2. `trace_edges()`（mainline.cpp:479）→ `trace_single()`（imgproc.cpp:512）跟踪原图边界点。
   - **断点2**：seed 在边缘 margin 内或追线过短（imgproc.cpp:533-536）→ trace 失败 → 整帧 return 0。
3. `build_boundary_from_trace()`（mainline.cpp:491-492 → boundary.cpp:338）：perspective→blur→resample，生成 `now_pts/now_step`。
4. `build_rpts0/1()`（mainline.cpp:494-501）生成 IPM 重采样边线点列 `rpts0s/rpts1s`。
   - **断点3**：点数 <3（boundary.cpp:451）→ 该侧 clear_corner，l_ok=0。
5. `refresh_boundary_corners()`（mainline.cpp:502 → boundary.cpp:430）：
   - `scan_corner()` 命中即 `l_found=l_ok=1`（boundary.cpp:486-491）；
   - L 角太远（l_now_index ≥ 28）清零（boundary.cpp:493-500）；
   - **断点4**：左右都有 L 但 `corner_pair_ok()` 宽度/张开/方向不合格（boundary.cpp:296/314/320）→ **双侧 l_ok 一起清零**（boundary.cpp:503-509）。

**核心根因（搜索中心不跟随）**：`rt->mid_position` 仅在 `tracking_reset()` 被设为 `MID_X`（mainline.cpp:433），全帧循环内**无任何回写**（全仓库仅 imgproc.cpp:236 读、mainline.cpp:433 写）。即 `find_seeds` 永远以静态画面中心起搜——弯道/十字偏置时单侧先出画，断点1 必然触发。

---

## B. seed 修好后，状态机要不要改？（核心结论）

**判断：seed/搜索中心修复是必要且强主导的上游修复，但不是充分——状态机仍有 1 处独立缺陷必须改，其余可大概率自然缓解。**

可自然缓解（纯上游依赖，状态机无独立 bug）：
- 十字双 L 进入：cross_process:488-489 与 cross_begin:319-325 的 `both_l` 完全等于 `left->l_ok && right->l_ok`，门槛仅转发 l_ok。seed 恢复 → 双侧 L 稳定 → 进入/不卡 BEGIN 自然成立。near_ok（cross_begin:360-364）依赖 `l_now_index ≤ 4`，同样随边线恢复满足。**无独立逻辑缺陷。**
- 环岛入环：ring_process:266-287 的 `l_ok` + `boundary_is_straight` 直接来自上游；内圈 RUN/END 用 `cur->now_step`（贴边近线长度）做 lost/have（ring.cpp:326-414），near_step 即 now_step，seed 恢复 → 近线变长 → 不再“饿死”。**无独立逻辑缺陷。**

必须独立改（与 seed 无关的状态机硬约束）：
- **`corner_pair_ok()` 双 L 复核（boundary.cpp:275-329）**：即便两侧 L 都被 seed 修复检出，宽度需 `|w0-45|≤15`、张开 `w1>70`、方向 `lp1.x<lp.x && rp1.x>rp.x` 三关全过，否则 503-509 把双侧 l_ok 清零，十字判不出。这是阈值/几何门，**seed 修好也绕不过**，需按当前 RAW 分辨率独立校准。
- 次要：CROSS_IN 退出门槛 `near_recover>20`（cross.cpp:23）与 NO_MIDLINE 三重严判（mainline.cpp:527-545）是退出/产出环节，seed 恢复后通常能满足，列为观察项而非必改。

→ **整套修法不是“不可分割”，但 seed 层是主依赖：先修 seed（mid_position 回写 + 出画兜底），再独立校准 `corner_pair_ok` 阈值。两者解耦，可分两步验证。**

---

## C. RT1064 vs front_car 关键差异

1. **L 点/选边数据源同构但量纲不同**：RT1064 `Lpt0/1_found`、`far_Lpt0/1_found` 来自全局边线点列 `rpts0s/rpts1s`、`far_rpts0s/1s`（cross.c:52/87-90、circle.c:25-29）；所有 lost/have 用**点数按米归一** `rpts1s_num < 0.2/sample_dist`（circle.c:41/57/95）。front_car 改用 `boundary.l_ok` + 整数 `now_step` 阈值（cross.cpp:402/456、ring.cpp:14-15）——语义一致，只是 front_car 把全局点列封装进 boundary_t，依赖路径更长（多一层 build_boundary_from_trace）。
2. **搜索中心同样不跟随中线**：RT1064 远线/begin 起点也是固定 `width/2 ± begin_x`（cross.c:134/161，begin_x=32 flash 常量），基础边线靠 `findline_lefthand/righthand_adaptive`（imgproc.c:247/290）自适应阈值追线。即 front_car 的“中心不跟随”并非偏离参考，差异在 **front_car 缺自适应阈值追线的鲁棒性 + 出画无兜底**，使固定中心的副作用被放大。
3. **front_car 多一道双 L 几何复核**：RT1064 进十字仅 `Lpt0_found && Lpt1_found`（cross.c:52），**无宽度/张开二次门**；front_car 额外加 `corner_pair_ok`（B 节），是 front_car 独有的、与 seed 解耦的进入门槛。
