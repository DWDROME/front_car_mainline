# 搜索中心跟随 落地差距清单 + 涟漪评估

调研目标：让 `mid_position`（seed 起搜中心）每帧跟随，而非恒 80。
规则：双边帧 `mid = (left + right) / 2`；单边帧 `mid = 已知侧 ± width_base/2`。

---

## 0. 现状事实（已核对）

- `mid_position` 字段：`code/types.hpp:204`（`runtime_t`，类型 `int`）。
- 仅被写入为常量 `MID_X`（=`RAW_W/2`，见 `tuning.hpp:25`），从不每帧更新：
  - `code/app/runners.cpp:128`、`code/app/runners.cpp:317`（初始化）
  - `code/tracking/mainline.cpp:433`（`tracking_reset`）
- 被读取的三处：
  - `code/tracking/imgproc.cpp:234-236` —— `find_seeds` 起搜中心
  - `code/tracking/zebra.cpp:117` —— `frame_seed_threshold(gray, mid_position)`
  - `code/tracking/ring.cpp:174`、`code/tracking/ring.cpp:177` —— 环岛直线补点起点
- `find_seeds` 入参 `mid_position` 只读不写（`imgproc.cpp:215-219`，签名 `int *mid_position`，函数体内无 `*mid_position = ...`）。
- `seed_pair_t`（`types.hpp:14-21`）：`left/right(point_t)`、`row(int)`、`width(int)`，已含 `width`，但仅双边帧写入（`imgproc.cpp:263`），单边帧 `width` 不填。
- 关键常量：`kSeedStartOffset = ROAD_HALF_WIDTH = 20`（`imgproc.cpp:25` / `tuning.hpp:42`）；`kSeedMinWidth=10`、`kSeedMaxWidth=RAW_W-20`（`imgproc.cpp:23-24`）。
- `control_center_x`（`types.hpp:202`）与 `mid_position` 已解耦：控车参考点 `ref = {rt->control_center_x, START_HIGH}`（`mainline.cpp:526`），默认 `CONTROL_CENTER_X=80`（`tuning.hpp:30`），由环境变量 `SMARTCAR_CONTROL_CENTER_X` 初始化（`runners.cpp:124-125/313-314`），全程不读 `mid_position`。

---

## A. 差距清单（最小改动，按依赖顺序）

落地"搜索中心跟随"需要：在 seed 成功后把本帧中心算出来，写回 `rt->mid_position`，供下一帧 `find_seeds` 起搜。最小方案 = 单点写回。

1. **写回点（核心，唯一必需改动）** —— `mainline.cpp` `tracking_process_frame`，在 `find_seeds`（`mainline.cpp:460-464`）返回 `seed_ok` 之后、`trace_edges` 之前，新增中心更新：
   - 双边（`rt->seed_state == 3`，或 `seed_pair_accepted` 为真）：`mid = (seeds.left.x + seeds.right.x) / 2`。
   - 单边左（`seed_state & 1`）：`mid = seeds.left.x + width_base/2`。
   - 单边右（`seed_state & 2`）：`mid = seeds.right.x - width_base/2`。
   - 写回前 `clip_i(mid, 边界, RAW_W-边界)` 限幅后再赋 `rt->mid_position`。
   - 这是最小落地点：复用现成 `rt->seeds` + `rt->seed_state`，不动 `find_seeds` 内部签名。

2. **可选（更内聚）** —— 改为在 `find_seeds`（`imgproc.cpp:215`）内部，用已有的 out 参 `int *mid_position` 回写（注释 `imgproc.hpp:24` 已写"输入/输出"，目前是死语义）。若走此路，需在双边分支 `imgproc.cpp:260-268` 和单边分支 `imgproc.cpp:302-326` 各加 `*mid_position = ...`，并保证失败/`seed_state==0` 时不写（保留旧值）。改 1 处调用方影响小，改内部影响面更集中但需同步 cross_in 失败路径（`mainline.cpp:465-475` 仍读 `rt->mid_position`，下一帧用）。

3. **重置/失效**（必需，配合 C）—— `tracking_reset`（`mainline.cpp:433`）已把 `mid_position` 复位 `MID_X`；新增 `width_base` 字段后须在此处一并复位初值。seed 全失帧（`seed_ok==0`）应保持 `mid_position` 不变（用上一帧值继续起搜），不要清零。

> 依赖顺序：先定 width_base 字段（C）→ 再加写回逻辑（A1 或 A2）→ 再在 reset 处复位（A3）。

---

## B. mid_position 动态化的涟漪（逐读者评估）

### B1. `zebra.cpp:117` — `frame_seed_threshold(rt->gray, rt->mid_position)`
- 行为：`region_otsu(gray, 0, mid_position, MINI_HIGH, START_HIGH)`（`imgproc.cpp:389`），用 `mid_position` 作为 otsu 取阈区域的**右边界 x**（取左半区域算阈值）。
- 变化：mid 跟随后，取阈区域宽度随车每帧浮动。弯道/单边时 mid 可能偏小（区域变窄、样本变少）或偏大。
- 风险：**中**。otsu 阈值帧间抖动 → 斑马线/停车线 `th` 抖动 → 误检/漏检概率上升。建议：zebra 的阈值改用稳定中心（如常量 `MID_X` 或 `control_center_x`），与 seed 起搜中心解耦；最简整改是这一处不传 `rt->mid_position` 而传 `MID_X`。

### B2. `ring.cpp:174 / 177` — 环岛直线补点起点 `mid_position ± w/2`
- 行为：`x0 = clip_i(rt.mid_position ∓ w/2, 3, RAW_W-4)`，`w = ROAD_HALF_WIDTH*2 = 40`，作为左/右环补种子的横向起点（仅在 `cur.original_step==0` 时用，否则用边界点 `original_pts[0].x + w`，见 `ring.cpp:180-184`）。
- 变化：mid 跟随后，环岛 BEGIN 帧若 seed 偏移，补点起点跟着偏。
- 风险：**中高**。环岛是强依赖几何对称的元素，补点起点漂移可能让内/外圈补线偏向一侧，影响入/出环判定。建议：环岛态（`rt->ring.kind != RING_KIND_NONE`）下冻结 mid 跟随，或这两行改用稳定常量 `MID_X`，避免动态中心污染环岛补点。

### B3. `control_center_x`（控车）
- 结论：**已解耦，控车不受影响**。控车误差用 `ref = {rt->control_center_x, START_HIGH}`（`mainline.cpp:526/642/549`），`control_center_x` 独立来源（`CONTROL_CENTER_X=80` + 环境变量），全程不读 `mid_position`。
- 风险：**低**。仅需确认改动不误把 `mid_position` 写进 `control_center_x` 或 `ref.x`。`CONTROL_CENTER_X=80` 与 `MID_X=80`（RAW_W=160）数值巧合相等，注意别把二者混为同一变量。

---

## C. 单边 width_base 设计（最小且安全）

- **字段位置**：`runtime_t`（`types.hpp:196`），紧邻 `mid_position`（`types.hpp:204`）新增 `int width_base;`。
  - 不放 `seed_pair_t`：seed 每帧 memset 清零（`mainline.cpp:449`），无法跨帧保留；width_base 需要帧间记忆，必须放 `runtime_t`。
- **谁写**：A 的写回逻辑里，**仅双边帧**用 `seeds.width`（已存在，`imgproc.cpp:263`）更新：`width_base = clip_i(seeds.width, W_MIN, W_MAX)`。单边帧只读不写。
- **谁读**：A 的单边分支读 `width_base` 算 `mid = 已知侧 ± width_base/2`。
- **初始值**：`tracking_reset`（`mainline.cpp:433`）与 `runners.cpp:128/317` 处一并设 `width_base = ROAD_HALF_WIDTH*2`（=40，即一个全路宽，与 ring.cpp 的 `w` 同义）。
- **更新规则**：只在双边且 `seed_pair_accepted` 为真时刷新；可加轻量低通（如 `width_base = (width_base*3 + seeds.width)/4`）抑制单帧噪声，最小版可直接赋值。
- **失效/重置时机**：
  - seed 全失帧（`seed_ok==0`）：保留 `width_base` 不动（继续用历史值起搜）。
  - 跨元素（进入 ring / cross / zebra 态）：建议冻结更新（这些态几何已变形，`seeds.width` 不再代表正常路宽），保留上次正常路宽值；最简做法是仅在 `ring.kind==NONE && cross.state==NONE` 时才刷新 width_base。
  - `tracking_reset` 时复位回 40。
- **限幅建议**：`W_MIN = kSeedMinWidth (=10)`，`W_MAX = kSeedMaxWidth (=RAW_W-20 = 140)`，与 `find_seeds` 现有宽度合法区间一致（`imgproc.cpp:23-24/258`），避免单边外推把 mid 推出图像或贴边。

---

## 结论一句话
最小落地 = `runtime_t` 加 1 个 `width_base` 字段 + `tracking_process_frame`（seed 成功后）单点写回 `mid_position`，并把 `zebra.cpp:117`、`ring.cpp:174/177` 这两处改用稳定中心或在元素态冻结，以免动态中心污染阈值分区和环岛补点；`control_center_x` 已解耦，控车安全。
