# 整体搜线获取层重构：搜索中心跟随（不可分割方案）

## Goal

把"从错误现象（弯道外圈偏移丢线、单/双 L 丢失即停、十字/环岛被上游饿死）整体推出的搜线获取层修法"作为一个**不可分割的整体方案**落地：让 seed 起搜中心 `mid_position` 每帧跟随车道横移（双边走中点、单边用路宽基准外推、全失保持上一帧），对齐 Front_Car 实证契约，把当前项目 seed/acquisition 层"中心恒 80、永不跟随"的根因一次性补齐。

## 不可分割性（用户强调）

这些修法由错误现象整体推出、互相依赖，不能再"砍一刀、缓一刀"地拆。链条：
搜索中心不跟随 → 弯道外圈偏移后固定中心搜不到边 → 单侧先出画 → 边线丢 → L 丢 → 十字/环岛状态机进不去/卡死。
故 seed 层的「中心跟随 + 单边路宽外推 + 全失保持 + 下游读者涟漪隔离」必须作为一个整体同时落地：
- 只加写回、不隔离涟漪 → zebra 阈值分区 / ring 补点起点被动态中心污染；
- 只隔离涟漪、不写回 → 跟随没实现；
- 不加 `width_base` 字段 → 单边帧无路宽基准可外推。

## Decisions（已用代码核实，行号已核）

事实层（代码已读，确定）：
- `mid_position` 全仓写入仅 4 处：`runners.cpp:128`(init_frame 离线)、`runners.cpp:317`(run_live 循环外一次性)、`mainline.cpp:433`(tracking_reset)，外加 `report.cpp:298` 仅打印。运行期**从不更新**。
- `find_seeds`(`imgproc.cpp:215-327`) 形参 `int *mid_position` **只读不写**；双边命中(258-269)写 `seeds`(含 `width`) 但不回写中心；单边向上补搜(274-300) `[MINI_HIGH, y-1]`；`seed_pair_accepted`(330-346) 现成可复用。
- **在线主循环 `run_live`(`runners.cpp:341 while(1)`) 不调用 init_frame**（循环内仅 354 `gray_valid=1` + 355 `tracking_process_frame`），所以在 tracking 内写回的中心能**跨帧保持**——这是方案成立的前提，已确认成立。
- 涟漪读者两处：`zebra.cpp:117` 用 `mid_position` 作 otsu 区域右边界；`ring.cpp:174/177` 用 `mid_position` 作环岛直线补点兜底起点（仅 `original_step==0` 时）。`control_center_x` 已解耦，控车不受影响。

决策层：
- **采用 Front_Car 契约**：双边 `mid=(left+right)/2`；单边 `mid=已知侧±width_base/2`；全失保持上一帧（不学 TC264 重置回中点）。
- **新增 `runtime_t.width_base`**（路宽基准，帧间记忆）。不放 `seed_pair_t`（每帧 memset 清零，`mainline.cpp:449`）。
- **width_base 更新**：仅"常态(非 ring/cross)双边接受帧"用 `seeds.width` 低通更新 `(3*old+new)/4`，限幅 [10, RAW_W-ROAD_HALF_WIDTH=140]；元素变形帧路宽不可信，冻结。（与 Front_Car"只标定一次"的差异：低通能纠正首帧落在噪声/弯道的错误标定，更鲁棒，且路宽稳定时低通值收敛到真值。）
- **涟漪从读者侧隔离**（比"写回侧按元素态冻结 mid"更干净）：`zebra.cpp:117`、`ring.cpp:174/177` 改用稳定几何中心 `MID_X`，使 `mid_position` 可全程跟随而不污染这两处。
- **全失保持复用现状天然行为**：`seed_ok==0` 帧不进写回，`mid_position` 自然留存上一帧值。

## Implementation Plan（4 类不可分割改动，共 7 处）

1. 字段 —— `code/types.hpp` `runtime_t` 加 `int width_base;`（紧邻 `mid_position`，:204 后）。
2. 初始化/复位 —— 三处 `mid_position` 初始化旁补 `width_base = ROAD_HALF_WIDTH*2`(=40)：`mainline.cpp:433`、`runners.cpp:128`、`runners.cpp:317`。
3. 写回核心 —— `code/tracking/mainline.cpp` 加 static `update_search_center(rt, seed_ok)`，在 `find_seeds`(:464) 返回后调用：
   - 全失：直接 return（保持）。
   - 双边(`seed_pair_accepted`)：`mid=(left.x+right.x)/2`；常态再低通更新 `width_base`。
   - 单边左(`state&1`)：`mid=left.x+width_base/2`；单边右(`state&2`)：`mid=right.x-width_base/2`。
   - 写回前 `clip_i(mid, 1, RAW_W-2)` 限幅（对齐 find_seeds 读取校验区间）。
   - 复用 `seed_pair_accepted` + `clip_i`(`clip.hpp`)；width_base 限幅常量在 mainline 局部定义并注释对齐 imgproc `kSeedMinWidth/kSeedMaxWidth` 语义。
4. 涟漪隔离 —— `zebra.cpp:117` `frame_seed_threshold(gray, rt->mid_position)`→`MID_X`；`ring.cpp:174,177` `rt.mid_position`→`MID_X`。

## Out of Scope / 观察项（事实依据，非遗漏）

- **`corner_pair_ok` 阈值**(`boundary.cpp:29-32`: width_ref=45/tol=15/open_ref=70/open_step=34)：已核实是**带单位注释、与 160 尺度量级自洽**的命名常量（双 L 基点距 45±15px ≈ 全路宽 40px 量级），**无代码证据是 bug**。element-coupling 那句"需按 RAW 分辨率校准"是保守推断。它与 seed 层解耦（boundary.cpp:503-509 双 L 复核不过才清零双侧 l_ok）。**不进本次方案**（盲改阈值需实车数据，违反"不伪造已验证"）。seed 修好后若十字仍被双 L 复核清零，再单独开 task 用实车数据校准。这不违背"不可分割"——它本就在原"三刀"之外，是调研额外挖出的独立项。
- **`init_frame` 逐帧重置 `mid_position`/`width_base`**：~~原列为无害观察项~~ → **本 agent 已移除**（override 了上面的"无害保留"判断）。理由：保留逐帧重置会让 replay 多帧无法复现中心跟随、且与不调 init_frame 的 live 主循环不一致；移除后单图 analyze/offline 由启动 `tracking_reset` 提供初值、单帧行为不变，replay 可复现跟随。如倾向保留 codex 原决定，回退仅需补回两行 `mid_position=MID_X; width_base=ROAD_HALF_WIDTH*2;`。
- 控制层兜底 / 延迟停车 / 从零重写状态机：不动。

## Verification

- 构建：`code/build` 下 CMake host 构建（`-O2`），确认编译/链接通过、无新 warning。
- 静态核对：`grep mid_position` 确认写入点新增且无新读者破坏；`width_base` 仅在常态双边帧更新。
- 行为：实车/实图序列回归由用户跑（弯道不丢线、十字/环岛进入是否随上游恢复）；我不伪造"已验证"。

### 本 agent 补充修复 + 实际验证结果

- **补修：双 bit 即中点**（`update_search_center`）—— 原写回用 `seed_pair_accepted`(严格成对) 判中点，否则落单边外推。但十字开口处两侧远边都找到、间距 > `kSeedMaxWidth=140` 时 `find_seeds` 不填 width(=0)→`seed_pair_accepted` 失败→误走单边把中心猛拉边界。改为 **`(seed_state&3)==3` 即取中点**（两侧已知时中点恒优于单边外推），`width_base` 刷新仍严格门控在合法成对。此即作者注释"双边取中点"的本意，原被 width=0 落空。
- **构建**：`./test.sh --host` → `[100%] Built target front_car_mainline`，`-Wall` 无警告。
- **冒烟**（`.diag/front_car_capture_current.png`，160×120 真实采集帧）：`--replay … 6` exit 0、6 帧无崩溃；`update_search_center` 每帧执行。
- **修复实证**：该帧 `left_seed=7,116 / right_seed=151,116`（间距 144>140，`seed_width=0`）。补修前 `mid_position=27`（单边猛拉左边界），**补修后 `mid_position=79`（中点居中）**。
- **corner_pair_ok 实测通过**：该帧双 L lb=(54,99)/rb=(108,100)/la=(43,100)/ra=(137,98) → w0≈54∈[30,60]、w1≈94>70、方向合格 → 复核 **PASS**，佐证其常量在 160×120 非明显错误、不应盲改（与上面 Out of Scope 一致）。
- **未验证**：跟随对四类错误现象的实际消除须实车 / 真实连续帧（本机仅静态标定帧，单帧不触发跨帧跟随）。

## Research References

- `research/search-center-contract.md` — TC264/Front_Car/RT1064 契约 vs 当前 4 缺口（实现直接依据）
- `research/mainline-gap-and-ripple.md` — 落地差距 + width_base 字段设计 + mid_position 涟漪逐点
- `research/element-coupling.md` — seed 层→十字/环岛连锁，状态机不改/corner_pair_ok 解耦依据

## Technical Notes

- 项目根 `front_car_mainline`；参考库 `Front_Car`(最全契约)、`TC264-Peripheral-perspective`(简化版)、`RT1064`(反例) 均在 `/mnt/e/longxin/` 下。
- 06-04 已归档（commit 9cd95ff / 2d5e5ef 的 prd.md 含四层契约/三刀/Patch V1-V2 历史分析，可引用不搬运）。
- 搜索：本地优先 fast_context + 实际文件核对；已知精确符号用 rg 验证。
