# 搜索中心跟随 + seed 获取 + 单边处理：参考库契约 vs 当前项目缺口

调研对象：摄像头巡线智能车 seed 起搜中心（mid_position / 等价量）的完整生命周期。
当前项目根：`front_car_mainline`，固定常量（`code/tuning.hpp`）：RAW_W=160, RAW_H=120, MID_X=80, START_HIGH=116, MINI_HIGH=60, ROAD_HALF_WIDTH=20。

---

## 库 1：Front_Car（最完整契约，含 width_base 单边修正）

文件：`/mnt/e/longxin/Front_Car/code/image_processing.c.bak`（完整实现）与 `code/image_processing.c`（同函数体，find_edge_canny_row 在 .c 中已被掏空为 stub，见 :206-212；逻辑以 .bak 为准）。

全局量声明：
- `mid_position`：`.bak:9` 初始化 `uint8 mid_position = 94;`（注意 .c 现版是 `:17 = 94`，TC264 无此量在 .c）。
- `width_base`：`.bak:12 uint8 width_base = 0;`（0 表示尚未标定）。

`Seek_Pts_Seed(uint8 High, uint8 mini_high)`（`.bak:288-350`）：

A. 搜索中心生命周期
- 初始化：`width_base=0`、`mid_position=94`（编译期常量），随后每帧由本函数更新。
- 入口越界保护：`.bak:290-293` High>=MT9V03X_H 或 <1 直接置 `Seed_State=no_pts` 返回。
- 双边起搜：固定行 High，从 `mid_position` 两侧用 `find_edge_canny_row(High, mid_position, 0/1)` 找左右白→黑边沿（`.bak:300、306`）。
- 命中判定：左 `found_left_x>=3`、右 `found_right_x<=MT9V03X_W-3`（`.bak:301、307`），即带 3 像素边界留白。
- **双边命中更新中心**：`.bak:337-341`，`result==two_pts` 时
  - 若 `width_base==0` 则首次标定 `width_base = Seed_right[0]-Seed_left[0]`（`:339`）；
  - `mid_position = (Seed_left[0]+Seed_right[0])/2`（`:341`）。即双边命中走中点。
- **单边命中用 width_base 修正中心**：`.bak:342-346`
  - 仅左：`if(width_base!=0) mid_position = Seed_left[0] + width_base/2;`（`:343`）
  - 仅右：`if(width_base!=0) mid_position = Seed_right[0] - width_base/2;`（`:345`）
  - 即用上次标定的路宽，把单侧边沿推算出虚拟中心，让下帧起搜中心跟着外圈平移。
- **seed 全失（no_pts）**：`.bak:336-350` 的更新块对 no_pts 无分支 → `mid_position` 保持上一帧值（不重置、不归零）。
- 限幅/越界保护：mid_position 本身无显式 clamp；保护来自 find_edge_canny_row 内部行/列范围与命中判定的 ±3 留白。

B. 单侧丢失时的行重试（`.bak:312-334`）
- 触发：`result != two_pts`。
- 方向：**向上**（行号递减）`for(uint8 i = High-1; i >= mini_high; i--)`（`:314、324`）。范围 [mini_high, High-1]。
- 缺右补右（`result==left_pts`，:313-322）：逐行 `find_edge_canny_row(i, mid_position, 1)`，命中 `<=MT9V03X_W-3` 即接受，写 `Seed_right` 含行号 i 并 break。
- 缺左补左（`result==Right_pts`，:323-333）：逐行 `find_edge_canny_row(i, mid_position, 0)`，命中 `>=3` 即接受。
- 注意：补搜命中后 result 升级为 two_pts，但左右行号 i 不同（非同一行），中心更新仍走 :341 中点。
- 备份：`.bak:348-349` memcpy 到 original_left/original_right。

find_edge_canny_row 行内搜索方向（`.bak:1017` 起，col 版 `image_processing.c:269-286` 同构）：从 start_x 出发，左方向向左、右方向向右，沿行扫到边沿返回。

---

## 库 2：TC264-Peripheral-perspective（结构同 Front_Car，但缺 width_base 修正）

文件：`/mnt/e/longxin/TC264-Peripheral-perspective/code/image_processing.c`，`Seek_Pts_Seed`（`:225-277`）。

A. 与 Front_Car 几乎逐行相同（双边搜 :237-247、单边重试 :249-271），**但中心更新只有一行**：
- `:274 mid_position = (Seed_left[0] + Seed_right[0]) / 2;`（无论 result 是几）。
- **没有 width_base、没有单边 width_base 修正分支**。单边时 Seed_left/right 之一是初始化的 0 或 MT9V03X_W（:233-236），导致 mid_position 会被拉偏 → 这是 TC264 版的弱点。
- seed 全失：mid_position = (0+MT9V03X_W)/2，等于被重置回图像中点（与 Front_Car 的"保持"不同）。
B. 单侧丢失行重试：与 Front_Car 完全一致（向上、[mini_high,High-1]、±3 接受、含行号、break）。`:250-270`。
- find_edge_canny_row 定义在 TC264 .c 中也已是 stub（grep 未命中函数体，逻辑等价 Front_Car）。

结论：TC264 = "双边中点跟随 + 单边向上行重试"，但**无 width_base 单边平移**，是 Front_Car 的前身/简化版。

---

## 库 3：RT1064（SJTU-AuTop）——无 seed 中心跟随，靠透视后中线跟踪

文件：`/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/USER/src/main.c`，`process_image`（`:532-588`）。

A. 起搜中心 = **图像几何中心固定 ±begin_x**，全程不跟随：
- `:534 int x1 = img_raw.width/2 - begin_x, y1 = begin_y;`（左起点）
- `:540 int x2 = img_raw.width/2 + begin_x, y2 = begin_y;`（右起点）
- `begin_x` 是可调参数，固定值 32（`Project/CODE/flash_param.c:22 float begin_x = 32;`），运行期不随边界更新。
- 起点先沿行扫黑（`:536、542`），命中阈值后用 `findline_lefthand_adaptive/righthand` 八邻域爬线（:538、544）。
- 无 mid_position 概念、无双边中点回写、无单边 width_base 修正。
B. 单侧丢失：不做"换行向上补搜种子"，直接 `ipts0_num=0/ipts1_num=0`（:539、545）丢该侧。鲁棒性靠后续透视去畸变（:547-557）+ blur/resample/局部角度（:559-581）+ `track_leftline/track_rightline` 单边中线跟踪（:584-587，按 ROAD_WIDTH/2 偏移补中线）。
- 即 RT1064 把"单边鲁棒"放在透视后的中线重建，而非 seed 阶段。

结论：RT1064 不提供"搜索中心跟随"契约，仅作反例——它用固定中心 + 后端单边中线补偿。本任务的"中心跟随"应对齐 Front_Car。

---

## C. 当前项目 front_car_mainline 现状对照与缺口

真实入口（非 zebra.cpp 的空壳）：
- `code/tracking/imgproc.cpp:215-327 find_seeds(gray, start_row, *mid_position, *seed_state, *seeds)`
- 调用方 `code/tracking/mainline.cpp:460-464`，传 `START_HIGH(116)` 与 `&rt->mid_position`。
- seed 常量：`imgproc.cpp:22-25` kSeedBorderMargin=3, kSeedMinWidth=10, kSeedMaxWidth=RAW_W-ROAD_HALF_WIDTH, kSeedStartOffset=ROAD_HALF_WIDTH(20)。
- 注意：`code/tracking/zebra.cpp:261 Seek_Pts_Seed` 是 `(void)` 空壳（zebra.cpp:206-212/237-263），已废弃，非真实路径。

现状逐项对照 Front_Car 契约：
1. 初始化：`mainline.cpp:433 rt->mid_position = MID_X(80)`。有。
2. 双边命中起搜：`find_seeds` 用 center±kSeedStartOffset 起搜（`:238-245`），对齐"从中心两侧偏移搜白→黑"。有，但起搜是 center±20 的偏移列，不是 Front_Car 的"从中心单点扫到边"。
3. **双边命中回写中心 =(left+right)/2：缺**。`find_seeds` 命中后 `:258-269` 只写 seeds，**从不写 *mid_position**；`mainline.cpp:460-464` 拿到结果后也不回写 `rt->mid_position`。
4. **单边命中用 width_base 修正中心：缺**。项目无 width_base 概念；`find_seeds` 单边只产出 single_left_x/right_x（`:303-312`），不推算虚拟中心、不回写。
5. **seed 全失保持：N/A（因为根本不更新）**。mid_position 全程恒为 80，既不更新也谈不上保持/重置。
6. 单侧丢失行重试：**有，且方向/范围对齐**。`imgproc.cpp:275-300` 仅向上 `for(yy=y-1; yy>=MINI_HIGH; --yy)`，[60,115]，命中 `find_left/right_edge` 后 ±kSeedBorderMargin 接受并记录行号，与 Front_Car 一致（注释 :274 自称"沿用 TC264/Front_Car"）。
7. 限幅：`find_seeds:234` 仅读取时校验 `*mid_position`∈[0,RAW_W)，但因从不回写，clamp 形同虚设。
8. 读者依赖（证明缺口有害）：
   - `ring.cpp:174-177` 用 `rt.mid_position` 作环岛直线补点起点（`mid_position ± w/2`）；
   - `zebra.cpp:117` 用 `rt.mid_position` 作 `frame_seed_threshold` 的 otsu 区域分界（`imgproc.cpp:383-389`）。
   - 两处读者都假设 mid_position 会跟随车道横移，但实际恒 80 → 弯道外圈偏移后这些下游也跟着错。

### 当前缺的步骤（对齐 Front_Car 需补）
- 缺 1：双边命中后 `mid_position = (left.x + right.x)/2` 的回写（find_seeds 内或 mainline 回写）。
- 缺 2：width_base 量的引入与首次双边命中标定（`width_base = right.x - left.x`，仅 width_base==0 时）。
- 缺 3：单边命中用 width_base 推算并回写中心（仅左 `left.x + width_base/2`；仅右 `right.x - width_base/2`）。
- 缺 4：seed 全失时显式"保持上一帧 mid_position"（Front_Car 行为；勿学 TC264 的重置回中点）。
- 已有：向上单边行重试（缺口 6 已满足）、初始化、入口/边界 ±3 留白、读取侧 clamp 壳。
- 已对齐方向：行重试向上、范围 [MINI_HIGH, START_HIGH-1]、命中 ±kSeedBorderMargin 接受。
