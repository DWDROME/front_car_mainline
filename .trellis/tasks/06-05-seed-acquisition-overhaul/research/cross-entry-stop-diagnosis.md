# Research: 十字进入即停（无远线无 L）根因诊断

- **Query**: front_car_mainline "十字进入即停且无远线无 L 角点" 根因 + 最小修法候选
- **Scope**: internal（只读 + 复现运行）
- **Date**: 2026-06-05
- **复现二进制**: `code/build-host/front_car_mainline`（Jun 5 04:47 构建）
- **复现帧**: `.diag/front_car_capture_current.png`、`.diag/front_car_capture_recheck.png`（均复现 bug）；`.diag/front_car_capture_live_current.png`（无十字，正常出线，对照组）

---

## 根因判定（先给结论）

**卡死的确切门 = 候选 (a)：卡在 CROSS_STATE_BEGIN，没进 IN，BEGIN 帧走"普通巡线"路径，截短近线产出的中线过短 → `midline_has_lookahead` 失败 → `NO_MIDLINE`(=4) 停车。**

- 双 L **找到且复核通过**（`l_ok=1`、`l_pair_state=0`），所以候选 (c)「corner_pair 清零」**不成立**。
- 从未进 IN（cross_state 终值=1=BEGIN），`cross_evolve`/远线根本没跑（`far_found=0`、`far_num=0`），所以候选 (b)「IN 内远线太少」**不是当前帧的触发门**，只是历史 06-04 修过的另一条路径。
- 卡在 BEGIN 的直接原因：BEGIN→IN 的近门 `id <= k_cross_begin_near_step(=4)`，而实测 `l_now_index=7 > 4`，`near_ok` 永远为 0（cross.cpp:331/341/365）。

---

## A. cross 状态流 NONE→BEGIN→IN（set state 行号 + 每态本帧产出）

调用链：`tracking_process_frame()`（mainline.cpp:477）→ `element_process()`（mainline.cpp:552）→ `cross_process()`（cross.cpp:477）。

| state | set state 位置 | 本帧产出 |
|---|---|---|
| NONE | 初始 / `cross_leave()` | 非十字，走普通巡线 |
| NONE→BEGIN | **cross.cpp:496** `rt->cross.state = CROSS_STATE_BEGIN`（条件 both_l，cross.cpp:489-494）；随即 `cross_begin()`（:498） | **不产远线**；BEGIN 帧把近线截到 L 点（cross.cpp:348-358）→ 回到 mainline.cpp 走普通路径产中线 |
| BEGIN→IN | **cross.cpp:367** `rt->cross.state = CROSS_STATE_IN`（条件 `both_l && near_ok`，cross.cpp:365） | 切 IN 当帧由 `cross_evolve()` 起一次远线（cross.cpp:499-502 / :510-513） |
| IN | 保持，`cross_evolve()`（cross.cpp:517） | 走远线 / track_type 选边 |
| IN→NONE | `cross_leave()`（cross.cpp:466，需 `not_have_line>2 && both_near_recover`） | 退出十字 |

**BEGIN 帧到底产不产中线**：产，但走的是**普通巡线分支**，不是远线分支。关键时序在 mainline.cpp：
- `cross_in0` 在帧**开头**采样（mainline.cpp:494-498）：只有"进帧时已是 IN"才置 1。
- BEGIN/NONE→BEGIN 帧 `cross_in0=0`，trace 成功 → 走 `normal_ok` 路径（mainline.cpp:530-562）。
- 其中 mainline.cpp:554-561：cross 非 NONE 且本帧从 NONE/BEGIN 切入时，把 `rpts0s_num/rpts1s_num` 截到 `now_step`（即截到 L 点）。
- 然后 mainline.cpp:642-676 用截短点列 `pick_track_type()` + `track_leftline/rightline` 产中线，受 `k_min_border_step(=6)`（:667）和 `midline_has_lookahead(LOOKAHEAD_DIST=35)`（:672）两道门约束。

## B. 十字语境下所有把 reject 置 NO_MIDLINE(=4) 的路径

| 行号 | 触发条件 | 适用 state |
|---|---|---|
| mainline.cpp:573-574 | `cross_in0 && IN` 且 `track_type==TRACK_TYPE_NONE` | CROSS_IN（远线全 NONE） |
| mainline.cpp:579-581 | `solve_cross_mid < k_min_border_step(6)` | CROSS_IN |
| mainline.cpp:584-585 | IN 中线 `!midline_has_lookahead(35)` | CROSS_IN |
| mainline.cpp:596-597 | `!normal_ok`（trace 全断且非 IN，或 cross_process 后仍无近线） | BEGIN/普通 |
| mainline.cpp:644-645 | 普通/ring 路径 `track_type==NONE` | NONE/BEGIN/ring |
| **mainline.cpp:669-670** | **普通路径 `mid_ok < 6`** | **BEGIN（本 bug 候选）** |
| **mainline.cpp:674-675** | **普通路径 `!midline_has_lookahead(35)`** | **BEGIN（本 bug 实测命中）** |

`midline_has_lookahead`（imgproc.cpp:1223-1246）：要求中线存在点 `dist >= aim*2/3 = 35*2/3 ≈ 23`。BEGIN 帧近线被截到 L 点，中线深度只到 L 点行，达不到 23 → 失败。

## C. 实跑数据（三帧 `--analyze`）

| 字段 | current | recheck | live_current(对照) |
|---|---|---|---|
| cross_state | **1 (BEGIN)** | **1 (BEGIN)** | 0 (NONE) |
| reject | **4 (NO_MIDLINE)** | **4** | 0 (NONE) |
| line_found | **0** | **0** | 1 |
| track_type | 0 | 0 | 2 |
| left/right_far_found | 0 / 0 | 0 / 0 | 0 / 0 |
| left/right_num(far) | 0 / 0 | 0 / 0 | 0 / 0 |
| left/right_l(far) | 0 / 0 | 0 / 0 | — |
| left/right_l_found | **1 / 1** | **1 / 1** | 0 / 0 |
| left/right_l_ok | **1 / 1** | **1 / 1** | 0 / 0 |
| l_now_index L/R | **7 / 7** | **7 / 7** | — |
| l_pair_state | **0 (pass)** | **0 (pass)** | 0 |
| l_pair_width0 / width1 | 54.0 / 94.0 | 54.0 / 94.0 | — |
| mid_step | **7** | **7** | 39 |
| mid_look (x,y) | 75,**99** | 75,**99** | 83,86 |

**指认**：双 L 已找到且 `corner_pair_ok` 通过（width0=54 在 45±15 内、width1=94>70、方向合格），但 `l_now_index=7 > k_cross_begin_near_step(4)` → BEGIN 永不切 IN（cross.cpp:331/341/365）。BEGIN 帧走普通路径：近线被截到 L 点（now_step=7），中线只到 y≈99（距起线 START_HIGH=116 仅约 17 行 < 23），`midline_has_lookahead` 失败 → **NO_MIDLINE 卡死的确切门是 mainline.cpp:674-675**（前置门 :669 的 `mid_step=7≥6` 已通过）。
注：replay 对静态图重复，cross 不会运动推进，所以会"永远卡在 BEGIN"，与"进入即停"现象一致。

## D. 对照 RT1064 run_cross / cross_farline（据 archived 06-04 prd:104-157）

- RT1064 `track_type` 只有 LEFT/RIGHT，**无 NONE→停车态**；主循环先按普通线不平衡更新 track_type，元素态再覆写，中线消费"当前选中侧"，从不因元素产不出而停（prd:27、104-110）。
- RT1064 `run_cross` 在 IN：far R→RIGHT / far L→LEFT / 否则按 not_have_line + 近线丢侧 / **否则保留上一帧 track_type**（prd:125-134）。
- front_car 多出的硬门：`tracking_process_frame` 把 `cross.track_type==NONE`、`solve_cross_mid<6`、远线无 lookahead 都翻成 `NO_MIDLINE`，control 视为无效输入停车（prd:24、149）。
- **本 bug 与 RT1064 的差异不在 IN，而在 BEGIN**：参考版 BEGIN 截近线后照样能产可用中线继续走、且最终落到 LEFT/RIGHT；front_car 的 BEGIN 帧用了同一套普通巡线 + `midline_has_lookahead(35)` 硬门，截短近线不够深直接 NO_MIDLINE。RT1064 普通路径无此 23px 前瞻硬门（其 begin_y/远线扫描是另一条路）。

## E. seed 中心跟随（ce65c9d）对十字进入的影响

- ce65c9d 的 `update_search_center`（mainline.cpp:431-457）只改 `find_seeds` 起搜中心，缓解"单侧先出画→边线丢→双 L 进不去"，对**双 L 能否被识别**有正面作用——实测 current/recheck 双 L 确实都 found+ok，说明 seed 跟随已帮到这一步。
- 但它**不触碰 BEGIN→IN 的近门，也不触碰 `midline_has_lookahead` 硬门**：在元素态它主动冻结 width_base、不更新双边记忆（:441-443 的 `cross.state==NONE` 条件）。所以"双 L 进得来、却卡在 BEGIN 出不去 / BEGIN 帧产不出够深中线"这一截，ce65c9d **没覆盖，仍差一截**。

## F. 最小修法候选（按风险从低到高，带行号）

1. **(最低风险，首选) 放宽 BEGIN→IN 近门，让其尽快进 IN 走远线分支。** cross.cpp:20 `k_cross_begin_near_step` 现=4，实测 L 点稳定落在 `l_now_index=7`。把该门提到 ≥8（或改判 `id <= now_step` 范围内即视为已贴近），即可让 current/recheck 直接 `both_l && near_ok` 切 IN（cross.cpp:365-367），下一帧由 `cross_evolve` 起远线、走 IN 分支。风险：纯阈值、单点、不动状态机；需复核不会让远未到位的 L 提前进 IN（可配合 width0/width1 已通过的 corner_pair 复核兜底）。

2. **(低风险) BEGIN 帧对前瞻门放宽，让截短近线中线也算有效。** 当前 mainline.cpp:672-675 对"刚从 NONE/BEGIN 切入"的帧仍用 `midline_has_lookahead(LOOKAHEAD_DIST=35)`。可对 `cross_state0==BEGIN/NONE 且本帧 cross!=NONE` 的截短帧降低 aim（如用 `LOOKAHEAD_DIST` 的一半）或跳过该门、只保留 `mid_ok>=k_min_border_step`(:667)。语义=BEGIN 帧只要近线截短中线非空就放行，等下一帧进 IN。风险：要确保不波及普通无线帧（须以 cross_state0 为条件，非全局）。

3. **(中风险) BEGIN→IN 切换当帧直接走 IN 远线分支，而非普通截短分支。** 现 `cross_in0` 在帧首采样（mainline.cpp:494-498），导致"切 IN 当帧"仍走普通路径。若让 element_process 切到 IN 后当帧即用远线，需把 :568 的 `cin0 && IN` 改为 `IN`（去掉 cin0 前置），并保证 `cross_evolve` 已在 element_process 内跑过。风险：触及 BEGIN→IN 时序契约（mainline.cpp:553-561 注释明确"刚切 IN 的帧仍走截短近线"），改动需重测远线起扫。

**不建议**：重写状态机；让 NO_MIDLINE 全局非致命（archived prd:67 明确禁止，普通无线帧必须停）。

## Caveats / Not Found

- 项目内**无 RT1064 `cross.c` 源文件**，D 节对照基于 archived `06-04-cross-ring-l-loss-stop/prd.md`（已核引用，prd:104-157）转述，非一手代码核对。
- replay/analyze 是静态单帧重复，能确指"卡在 BEGIN 哪道门"，但无法验证"实车运动中 L 点推进到 index<=门后是否就能进 IN"——需实车或多帧序列验证候选 1 的实际效果。
- 候选 1 的阈值（≥8）是按当前帧 `l_now_index=7` 估的下界，实车不同距离下 L 索引会变，最终值需调参验证。
