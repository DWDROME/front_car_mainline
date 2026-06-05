# Research: 参考 RT1064(SJTU-AuTop) 圆环外圈识别与起扫行/阈值机制对照 front_car

- **Query**: 深挖 RT1064 圆环外圈识别与起扫行/阈值机制，判断 front_car 的"边线贴左右边缘采不到"要不要专门解
- **Scope**: internal（两套本地代码库对照）
- **Date**: 2026-06-05
- **参考库根**: `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/`
- **当前库根**: `/mnt/e/longxin/.../front_car_mainline/`

> 说明：fast_context MCP 在本会话工具表里未暴露，已降级为 Read + Grep 直接打开两库实际源文件核对行号（这些文件路径精确已知，为最强证据）。证据边界：仅静态读码，未运行。

## 关键事实校正（影响后续所有判断）

- **RT1064 图像分辨率不是 160×120，而是 376×240**。
  - `Libraries/seekfree_peripheral/SEEKFREE_MT9V03X_CSI.h:43-44`：`MT9V03X_CSI_W = 376`、`MT9V03X_CSI_H = 240`。
  - 注意 RT1064 的边线追踪在**去畸变/透视变换前的原图坐标系**做，之后才用 `mapx/mapy` 投影到地面坐标系（`main.c:548-557`）。
- **front_car 图像 160×120**，几何常量在 `code/tuning.hpp`：`RAW_W=160`、`RAW_H=120`、`START_HIGH=116`、`MINI_HIGH=60`、`ROAD_HALF_WIDTH=20`。
- 因此两者的"行号/像素阈值"不能直接照搬，需按比例换算。

---

## A. RT1064 圆环外圈识别机制

**结论：圆环不是另一套搜线机制，而是复用同一套 `process_image`(seed+findline) 产出的左右边线 `rpts0s/rpts1s`，圆环只是一个状态机切换"跟左线还是跟右线"(track_type)，不重新起种子、不用 far line。**

证据 `Project/CODE/circle.c`：
- 状态机枚举 `circle.c:8-15`：NONE / LEFT_BEGIN / RIGHT_BEGIN / *_IN / *_RUNNING / *_OUT / *_END。
- `check_circle()` `circle.c:23-31`：靠普通主线产出的 `Lpt0_found/Lpt1_found`(L 角点) + `is_straight0/1`(直道) 进环判定，输入全部来自普通 `process_image`+`find_corners`，没有独立图像处理。
- `run_circle()` `circle.c:33-146`：每个状态做的唯一实质动作就是设 `track_type = TRACK_LEFT / TRACK_RIGHT`，再用 `rpts0s_num / rpts1s_num`(普通边线点数)、`Lpt*_found`、编码器里程 `ENCODER_PER_METER*(3.14/2)` 来推进状态。例：
  - LEFT_BEGIN `circle.c:37-51` 跟右线、靠左线"先丢后有"判进环；
  - LEFT_IN `circle.c:53-59` 跟左线(内圆)、编码器过 1/4 圆切 RUNNING；
  - LEFT_RUNNING `circle.c:61-69` 跟右线(外圆)、右 L 角点 `Lpt1_rpts1s_id<0.4/sample_dist` 切 OUT；
  - LEFT_OUT/END `circle.c:71-89` 跟内圆/右线收尾。
- **"外圈那条贴边的边线靠什么被稳定追到"**：靠的就是普通 `findline_*_adaptive` 八邻域追线本身(见 C)。圆环没有任何专门的"外圈贴边补偿"。它能稳，是因为 RT1064 的 seed 起点恒在画面中央(width/2±begin_x)、外圈线在 376 宽大图里基本不会贴到 x=0/375，加上自适应阈值八邻域沿白边能一路爬到画面顶部。
- `draw_circle()` `circle.c:149-151` 是空函数，进一步说明圆环没有独立的图像/边线生成逻辑。

---

## B. 起扫行 begin_y

**结论：RT1064 的 begin_y 是固定常量(默认 167)，不是逐帧自适应择优；而且它不是底边，是 240 高图像里约 70% 高度处(比底边上抬约 73 行)。front_car 的 START_HIGH=116 在 120 高里几乎贴底(只留 3~4 行)。**

证据：
- `Project/CODE/flash_param.c:22-23`：`begin_x=32`、`begin_y=167`（固定值，存 flash，可调但默认就是定值）。
- `flash_param.c:19-29` 一并固定：`thres=140`、`block_size=7`、`clip_value=2`、`pixel_per_meter=102`、`sample_dist=0.02` 等。
- 调试可调范围 `main.c:80,83`：begin_x∈[0,188]、begin_y∈[0,240]，只是上位机调参滑条，不是运行时自适应。
- `process_image()` `main.c:534,540`：起点 `x1 = width/2 - begin_x = 188-32 = 156`，`x2 = width/2 + begin_x = 220`，`y1=y2=begin_y=167`。**两个起点都在画面横向中央附近、纵向 167 行**。
- 167/240 ≈ 0.696，即起扫行明显高于底边(底边是 239)。对照 front_car 116/120 ≈ 0.967(贴底)。
- 起点不是直接当边线点：`main.c:536-537` 先从 `x1` 沿行**向左**扫到第一个 `<thres` 的列(即白→黑)定位边沿列，再判 `AT_IMAGE(x1,y1)>=thres` 才启动 `findline_lefthand_adaptive`；右侧 `main.c:542-544` 对称向右扫。这一步等价于 front_car 的 `find_left/right_edge` 找种子，只是 RT1064 用全局固定 `thres`，front_car 用局部均值阈值。

---

## C. 阈值/追线鲁棒性：findline_*_adaptive 的自适应阈值

**结论：RT1064 的"自适应阈值"是逐点局部块均值阈值(block_size×block_size 邻域均值 - clip_value)，不是大津；它是八邻域(实际四方向 dir + 前/前侧)迷宫巡线沿白边一路爬升的鲁棒性核心。这与 front_car 种子层 find_left/right_edge "在固定行单向找一次白→黑、找不到返回 -1"有本质差异——但 front_car 真正的追线层 trace_single 其实也是同类八邻域追线。**

证据 `Project/CODE/imgproc.c`：
- `findline_lefthand_adaptive` `imgproc.c:247-287`、`findline_righthand_adaptive` `imgproc.c:290-330`：
  - 每步用 `block_size×block_size` 邻域和 / 面积 - `clip_value` 得 `local_thres`(`imgproc.c:254-261/297-304`)，**逐点重算**，所以光照/反光渐变时阈值跟着走；
  - 用 `dir_front / dir_frontleft(右手为 frontright)` 做迷宫式沿边：前方暗则转向(turn++)、前左/前右暗则直行、否则斜进并回转(`imgproc.c:266-284 / 309-327`)；
  - 循环边界 `imgproc.c:253`(左手)：`half<x && x<width-half-1 && half<y && y<height-half-1`；`imgproc.c:296`(右手)：`0<x && x<width-1 && 0<y && y<height-1`。**到边即停，但因起点在中央、白边沿不贴边，正常不会触边。**
- 大津 `getOSTUThreshold` `imgproc.c:416+` 存在，但 findline 用的是局部块阈值，不是大津。
- **front_car 对照**：种子层 `code/tracking/imgproc.cpp`
  - `find_left_edge` `imgproc.cpp:82-101`：在 `row` 固定行从 `x0` **向左**逐列找 `gray[x]>th && gray[x-1]<=th0`(白→黑邻接)，**循环 `x>0` 到列 0 仍没命中就返回 -1**；
  - `find_right_edge` `imgproc.cpp:104-122`：对称向右，到 `RAW_W-1` 没命中返回 -1；
  - 阈值 `calc_th_core` 是局部块均值 - kLocalClipValue(`imgproc.cpp:68-80`)，思路与 RT1064 局部阈值同源；
  - 真正的追线 `trace_single` `imgproc.cpp:512-550` + `trace_left/trace_right`，是八邻域沿边追线，**这才是与 RT1064 findline 对位的部分**，front_car 并不缺自适应八邻域追线能力。
- 本质差异：RT1064 没有"在某固定行找一次边、找不到就该侧丢线"的薄弱环节——它的边线点完全由八邻域追线连续产出；而 front_car 的**种子获取层**(find_seeds 调 find_left/right_edge，`imgproc.cpp:244-245`)依赖在 START_HIGH 这一行命中白→黑，贴边出画(x=0/159)时该行扫不到边而返回 -1，丢的是种子，不是追线能力。

---

## D. 边线贴左右边缘(x≈0 / x≈W)时

**结论：RT1064 结构上不会出现"清晰边线贴边导致丢线"，因为它从不在贴边处起种子；其 findline 循环到边界会停(右手 `0<x<width-1`，左手留 half)，但起点恒在画面中央、376 宽大图给了足够横向余量，外圈线极少贴到 x=0/375。圆环没有针对"贴边"的专门处理。**

证据：
- 起种子点 `main.c:534/540`：永远是 width/2±begin_x(156 与 220)，离左右边缘各 150+ 像素，根本不在边缘起。
- findline 触边即停 `imgproc.c:253/296`，但这是"线走出画面顶部/侧边后自然结束"，不是"贴边采不到导致整条丢"。
- 没有 grep 到 RT1064 的 border-margin 丢弃边线逻辑(circle.c / imgproc.c findline 内均无)；唯一"裁切"是调试绘图时把 begin_y 行两端涂黑(`main.c:473-478`)，与追线无关。
- **front_car 对照**：`trace_single` 有显式 border margin —— `imgproc.cpp:527-534` 当 `seed.x<=kTraceBorderMargin || seed.x>=RAW_W-1-kTraceBorderMargin`(`kTraceBorderMargin=2`，`imgproc.cpp:27`)时直接 `return 0`。叠加种子层 `find_left/right_edge` 贴边返回 -1，front_car 在"边线贴 x=0/159"时是**种子拿不到 + 追线种子被边距否决**双重丢线。RT1064 因起点在中央而天然规避了这两关。

---

## E. front_car ring.cpp 外圈处理对照

**结论：front_car 的圆环外圈是"复用同一套八邻域追线 trace_single + 单边几何外扩补线(build_opp)"，跟 RT1064 "纯切 track_type、不补线"的机制不同。build_opp 自己重新起种子并追对侧线，并不直接依赖普通搜线把贴边那条线采到。**

证据 `code/tracking/ring.cpp`：
- `build_opp` `ring.cpp:78-132`：left=1(左环)补右侧线、left=0 补左侧。
  - 补线种子：若当前边界有点，从 `cur.original_pts` 里按 `v=dx*dy`(最靠对侧外缘且最靠车头底部)挑种子 `ring.cpp:104-123`，再横移 `k_seed_dx=5`、上移 `k_seed_dy=3`(`ring.cpp:16-17,124-132`)；没点则用固定种子 `{10,START_HIGH}` 或 `{RAW_W-11,START_HIGH}`(`ring.cpp:94-98`)。
  - `find_column_seed`(`ring.cpp:136`，定义 `imgproc.cpp:349`)在列内找种子 → `trace_single`(`ring.cpp:140`)八邻域追对侧线 → trace 上按 `v=dx*dy*dy`(平方放大远端权重)挑拼接点 `ring.cpp:152-170`。
  - 拼接基准 x0 用**稳定几何中心 MID_X** 而非跟随的 mid_position(`ring.cpp:172-190` 注释明说"避免动态中心污染环岛对称补点")，再线性插值连成对侧边界 `ring.cpp:195-204+`。
- 调用点 `ring.cpp:356`：`build_opp(*rt,*cur,*opp,left,has_matrix)`。
- **关键差异**：RT1064 圆环靠"摄像头看得到的两条真实边线 + 切跟线方向"走完，从不几何补线；front_car 因近底起扫 + 小图(160×120) + 进环时一侧线易出画，需要 build_opp 主动重起种子追对侧、几何外扩补出对侧边界。两者解决的是同一物理问题，但 front_car 多了"补线"这层，且补线种子也依赖 trace_single 不贴边。

---

## F. 判断材料：front_car"边线贴左右边缘采不到"是否需要专门解

**判断：不需要为了"贴边采不到"再单独造一套机制；该问题的根因不是缺自适应阈值/八邻域(front_car 的 trace_single/calc_th_core 已具备)，而是两点结构选择 —— (1) 种子获取固定在近底行 START_HIGH=116 用 find_left/right_edge 单行单向找白→黑，贴边出画时该行无边可命中即返回 -1；(2) trace_single 有 kTraceBorderMargin=2 的贴边否决。RT1064 之所以"看起来不用专门解"，本质是它把起种子点恒放在画面横向中央(width/2±begin_x)、并在 376×240 大图、起扫行上抬到 167(≈70%高)，从源头避免了边线贴边。**

可借鉴方向（仅陈述参考库做法，不含 virtual edge seed，该方向已 out-of-scope）：
1. **起种子点放中央而非贴边找**：RT1064 从中线 width/2±begin_x 起、沿行扫到白→黑定边沿列(`main.c:534-544`)，front_car 现有 find_seeds 也是从中心向外偏移起搜(`imgproc.cpp:25 kSeedStartOffset=ROAD_HALF_WIDTH`)，但用的是"找白→黑"语义，贴边行整行无边时仍丢。可参考"贴边那侧让 trace 沿边走完"而非"在该行硬找一次边"。
2. **起扫行上抬**：RT1064 begin_y=167 不贴底(≈70%高)；front_car START_HIGH=116 几近贴底(96.7%)。贴底行恰是边线最易因透视而横向贴出画面边缘的位置；适当上抬起扫行可减少"近端贴边"概率(注意 front_car 另有 MINI_HIGH=60 的上界，换算需谨慎)。
3. **圆环外圈靠 build_opp 已能补对侧线**(E)，对"一侧出画"已有应对；真正薄弱点是普通主线种子层对贴边的零容忍，而非圆环逻辑本身。

## Caveats / Not Found

- RT1064 begin_y=167 与 front_car START_HIGH=116 的"上抬"对比是按各自图像高度归一化(0.70 vs 0.97)给出的相对结论；两库相机安装高度/俯角不同，绝对几何不可直接照搬。
- 未运行任一程序，结论基于静态读码。
- 未深入 `trace_left/trace_right`(`imgproc.cpp` 398+/453+) 的逐方向实现细节，仅确认其为八邻域沿边追线且 trace_single 入口有 border margin 否决(`imgproc.cpp:527-534`)。
- RT1064 far line(远线)仅 `cross.c`(far_x1=86/far_x2=280/far_y 渐变，`cross.c:48,77-79`)用于十字，圆环不涉及，已排除。

## 后续更正（同会话，一手读 RT1064 cross.c/main.c 后）

- **begin_y 是共用量，非仅普通起扫行**：除 `main.c:534/540` 普通 process_image 起种子外，`begin_y` 同样是十字远线 `cross_farline()` 的基准行(`cross.c:134/161`，`:77` 注释"远线控制进十字 begin_y 渐变靠近防丢线")。B 节"begin_y=167 是普通起扫行"属实但不完整。
- **F#2"上抬 START_HIGH"已收回**：begin_y 的"距底偏移"由相机安装高度/俯角决定，两库不可照搬；且 front_car `START_HIGH` 同时是控制参考行(`mainline.cpp` `ref={control_center_x, START_HIGH}`)，动它会涟漪到控制，不是自由旋钮。F#1(中央起种子，本会话 ce65c9d 已做中心跟随)与 F#3(build_opp 补对侧)仍成立。
- **"边线贴边"补搜决策 = 维持现状(option A)**：现有单侧补搜(`imgproc.cpp:275-300`，9cd95ff)已满足"一侧在→向上逐行补另一侧丢线起点"，不改。
- **"十字进入即停"另有真因**：经 `cross-entry-stop-diagnosis.md` 定位，是 BEGIN 帧"中线过短→NO_MIDLINE"硬停的死锁(与起扫行无关)，已对齐 RT1064 在十字态放宽该硬门修复，非靠上抬起扫行。
