# External Comments And Video Plan - 2026-06-09

## Scope

本记录只沉淀用户提供的评论区线索和视频分析计划。评论区内容不是本项目当前算法合同，也不是可直接替代本地代码、日志、视频逐帧证据的证明。

当前要落地的显示改动是 diagnostic-only：在上位机显示中增加 seed 搜索行和左右 seed 方框，帮助判断 `find_seeds()` 后的当前帧证据。它不改变 tracking/control 输出。

## Comment Set A: shuiyee_ Video Thread

可记录线索：

| 线索 | 评论中依据 | 对本任务的用处 |
| --- | --- | --- |
| 巡线思路被问到“大津 + 八邻域”，UP 回复“对” | 用户提供评论 | 后续分析视频时重点观察二值化阈值、八邻域 trace、trace 起点和停止条件。不是本项目必改依据。 |
| 交叉路口判定被回答为“角点” | 用户提供评论 | 对照本项目 `boundary`/`cross` 的 L 角和 strict double-L 诊断，不把对方角点条件直接搬过来。 |
| 环岛进出被回答为“状态机” | 用户提供评论 | 后续视频和日志分析要按阶段记录 BEGIN/IN/RUN/OUT/END 或对方等价状态。 |
| 评论中多人提到图像角点、1/4 圆弧长度、出入环条件 | 用户提供评论 | 作为待 OCR/逐帧确认点，不能先推断对方算法就是弧长积分。 |
| 有人指出紫色线可能是扫线起始行，车头以下不适合算中线 | 用户提供评论 | 本项目显示层新增 seed 搜索行，直接对应 `START_HIGH=116`，用于确认起搜位置和车头遮挡关系。 |
| 龙芯组摄像头视野广，建议设置扫线范围/截止行 | 用户提供评论 | 后续排查相机视角、`START_HIGH`、`MINI_HIGH`、追线范围时作为背景线索；阈值仍需本地帧证据。 |
| 赛道宽度已知 | 用户提供评论 | 关联本项目 `ROAD_HALF_WIDTH`、`width_base` 学习诊断，不能直接使用对方赛道宽。 |
| 控制被问“串三环”，UP 回复确认 | 用户提供评论 | 仅作为控制架构背景。当前项目是 `guide_error -> target_yaw -> yaw_cmd` 差速链，不能机械移植。 |

## Comment Set B: 九天-7 / SmartCarLineHunting Thread

可记录线索：

| 线索 | 评论中依据 | 对本任务的用处 |
| --- | --- | --- |
| 置顶称源码更新到 `https://github.com/jtwws/SmartCarLineHunting.git` | 用户提供评论；本轮已用 `git ls-remote` 验证 HEAD/master 为 `10cb7a52dafb0ca34913f3951d6fde7378c7330d`，并在 `/tmp/SmartCarLineHunting` 初查同版本源码 | 作为候选参考实现优先级上调。若用于对齐，仍需和本项目真实代码逐行比较；不能只引用评论或直接移植 OpenCV/Windows 上位机演示逻辑。 |
| OpenCV/视觉处理在上位机，通常 Linux 板子跑 C++，MCU 只传感/执行 | 用户提供评论 | 说明该方案算力边界和本项目 LS2K0300 本机处理不完全相同。 |
| 上下位机通信可用串口；无线可蓝牙/WiFi | 用户提供评论 | 对本任务只作为通信背景，不改本项目图传/assistant 协议。 |
| 正常摄像头 30fps，视频中处理速度接近 100fps；OpenCV 传统图像处理可几毫秒 | 用户提供评论 | 后续分析时区分图传 FPS、算法 FPS、视频播放倍速，不用 FPS 猜测替代日志。 |
| “程序没改就是数据问题，可能没有读到数据” | 用户提供评论 | 本项目排查无线/无 seed 时仍要保留 `pre=` seed/trace 诊断，不用静默 fallback。 |
| OpenCV 路径问题：绝对路径、中文路径可能导致读写失败 | 用户提供评论 | 只影响后续本地视频/OCR工具链路径选择，优先用无中文绝对路径。 |
| 摄像头太高导致提前看到弯道并提前转向 | 用户提供评论 | 对应本项目需要观察 `LOOKAHEAD_DIST`、中线前方性和 seed 搜索范围，但不是直接调参依据。 |
| 上交方案被说是迷宫法，和该方案不同 | 用户提供评论 | 记录外部参考不能混用；引用前必须区分方案来源。 |

## Video Agent Status

本轮视频分析要求：

- `/mnt/c/Users/ds_ev/Downloads/Video/37173200447-1-192.mp4`：逐帧/近逐帧分析视觉叠加、seed 行、角点、环岛/交叉状态。
- `/mnt/c/Users/ds_ev/Downloads/Video/34850997340-1-192.mp4`：逐帧/近逐帧 OCR 和代码重建，兼顾算法思路。

运行记录：

| Agent | Model | 目标 | 状态 |
| --- | --- | --- | --- |
| `019eaac8-c986-70f1-908e-ddaeefaef378` | `gpt-5.5` | `37173200447` | 401 Unauthorized，失败，无有效产物。 |
| `019eaac8-fa1b-7b12-a953-d294b355dcd9` | `gpt-5.5` | `34850997340` | 401 Unauthorized，失败，无有效产物。 |
| `019eaad5-c5d7-7e01-940f-e041ee019340` | `gpt-5.3-codex` | `37173200447` | 用户中断后报 503，不使用。 |
| `019eaad6-e08e-7672-bbe1-00074cb67ded` | `gpt-5.4 xhigh` | `37173200447` | 用户判断价值不足，已手动暂停；不作为完成证据。 |
| `019eaad7-2459-7d83-a922-dc751e83ba0b` | `gpt-5.4 xhigh` | `34850997340` | 用户判断价值不足，已手动暂停；不作为完成证据。 |

用户已判断两个视频 agent 价值不足并要求暂停。本任务后续不再等待 agent 输出，也不把视频中间产物作为完成证据。若后续重新需要视频证据，主会话降级为本地流程：

1. `ffprobe` 记录 fps、时长、总帧数。
2. `ffmpeg` 抽全帧缩略图或按真实 fps 抽帧。
3. 用帧差筛关键变化帧。
4. 对代码视频高频抽取代码区域，能 OCR 则 OCR，不能 OCR 则保存关键帧让人工核验。

## SmartCarLineHunting Initial Source Check

`SmartCarLineHunting` 当前只作为候选参考实现，不是本项目 active reference contract。已核验证据：

- 远端 HEAD/master：`10cb7a52dafb0ca34913f3951d6fde7378c7330d`。
- 本地临时源码：`/tmp/SmartCarLineHunting/opencvTest.cpp`。
- 项目形态：Visual Studio / OpenCV 单文件上位机演示，非 LS2K0300 本机 tracking/control 链。
- 关键源码线索：
  - `opencvTest.cpp:41`、`:369` 使用 `THRESH_BINARY + THRESH_OTSU`。
  - `opencvTest.cpp:10` 定义 `daodianju=3`，`:92-123` 对左右道点做相邻点距离约束。
  - `opencvTest.cpp:11-13` 定义 `feichezhanbi`、`yuanhuanyuzhi`、`yuanhuanjingdu`。
  - `opencvTest.cpp:146` 以后用左右道点数量差和横向扫描记录圆环状态/位置点。
  - `opencvTest.cpp:253` 画紫色横线，形态上类似用户要求的 seed/扫线诊断线，但这只说明显示参考，不证明算法合同等价。

可借鉴边界：

| 可参考点 | 不能直接移植的原因 |
| --- | --- |
| Otsu 二值化、连续边界点约束、紫色扫线/环岛辅助线这类显示和诊断思路 | 当前项目已有 `find_seeds()`、trace、IPM、boundary、cross/ring 状态机，且 active ring reference 是 RT1064 `circle.c`。 |
| 圆环用左右边界点数量差和局部横扫找环岛位置点 | 当前 ring 合同已明确为 RT1064 单侧 L + 对侧直线进入，不能把 `yuanhuan*sign` 状态直接并入主链。 |
| 上位机 OpenCV 传统图像处理可作为算力背景 | 当前任务只改 LS2K0300 本机跟踪和 assistant 显示，不改变上下位机架构。 |

## Display Diagnostic Rationale

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| 无直接参考版等价；这是显示诊断，不是 tracking 行为合同。逐飞 assistant 协议结构支持最多 8 条边界，但当前 SDK 公开 `seekfree_assistant_camera_boundary_config()` 只暴露 3 条。 | 当前 `code/app/assistant.cpp` 只发送左/中/右三条边界；`START_HIGH=116` 和 `track.seed_*_find` 只在日志中可见，图像上不能直观看到 seed 搜索行/seed 点。 | 在 `code/app/assistant.cpp` 本地按协议结构发送最多 6 条 XY 边界：左、中、右、seed 行、左 seed 方框、右 seed 方框。 | 不牺牲左/中/右主显示线，同时让当前帧 `find_seeds()` 后的 seed 行和左右 seed 点直接可视化。 | 只读取 `rt->track.seed_state_find`、`seed_left_find`、`seed_right_find`、`START_HIGH` 生成显示点；不写 `track_type`、`guide_error`、`mid_position`、`width_base`、trace 或 control 输出。 |

## Follow-Up Checks

- 不再等待两个视频 agent 的 `report.md` 或重建代码产物；它们已暂停且不作为证据。
- `SmartCarLineHunting` 已完成初查，可作为后续外部参考优先项；使用前仍必须按具体源码行和本项目真实代码比较，明确哪些内容能映射到 LS2K0300 本机视觉链。
- 上位机实机验证时确认第 4 条边界是否显示为紫色；如果颜色映射不符合预期，再考虑 UI/协议层颜色表，而不是改 tracking。
- 验证显示 packet 后，重点看 seed 行是否与日志 `pre=` 中的 seed 坐标一致。
