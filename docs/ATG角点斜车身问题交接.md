# ATG 角点识别斜车身问题交接

时间：2026-06-13

## 当前状态

问题还没有解决。当前按现场观察记录：

- 车身完全摆正时，算法/日志侧曾经能稳定给出两侧 L 点；但当前上位机仍没有看到原版那种明显的 L 十字标记。
- 更准确的现象是：靠近时 L 十字能出现；离得远时，即便日志已经识别到 L 点，上位机也没有显示对应 L 十字。
- 车身稍微斜一点或目标离远后，画面上肉眼能看到黑白边线和 L 形结构，但上位机没有对应 L 角点输出。
- 用户确认：正确版本的 L 十字应当非常明显，不能把“不明显”“被背景吃掉”当默认解释。
- 注释掉左侧方向门限后重新烧录，现象仍未解决；这次修改只能算排除实验，不是有效修复。
- 上位机图传、IPM 下半图、端口和 PC IP 已经打通；当前不优先怀疑 TCP/IP 连接本身，但必须怀疑 L 点显示链路。

有一批曾经看到过的日志包含 `circle=7`、`sel=0/0`、`l=1@...`，用户要求忽略。本交接和下面给 fable 的提示词都不把那批日志作为结论依据。

## 本轮必须记录的结论

当前不要再回溯成“看不清”或“阈值随手调小”。这轮实机观察后，问题拆成两个层级：

1. P0：远处 L 角点显示链路问题已经定位并修复到代码。根因不是识别阈值，而是显示侧误用了 IPM 渲染域检查；靠近时通过，离远后 IPM y 变成负数被拒绝，所以日志识别到了但上位机不画。
2. P1：斜车身时 L 点算法鲁棒性仍需重新审查，但必须等 P0 实机确认后再动算法，否则会把显示 bug 和识别 bug 混在一起。

交接文档里原先的实验 A/B 已不需要优先做：P0 根因已经由矩阵和尺度关系坐实。现在只剩一次实机确认：上传后把 L 角放到 1.2~1.5m 远处，看上位机是否出现 L 十字；同时对照 `ATGLptDiag` 的 `inv` 坐标，十字位置应一致。

## 2026-06-13 P0 根因和修复

P0 根因：远处 L 点被“IPM 渲染域检查”错杀。

当前显示链路原来复用了 `perspective_lookup_ipm_to_raw()` 把 L 点从 IPM 投回 raw。这个函数是为下半 IPM 渲染图写的，入口会先检查 IPM 坐标必须落在 `0 <= x < 160, 0 <= y < 120`。但 ATG 的 `rpts0s/rpts1s` 点列不受这个渲染域约束；远处 L 点在当前 `pixel_per_meter=116` 的尺度下，约 1m 外 IPM y 会变成 0 以下，这是正常几何结果，不代表不能投回原图显示。

这解释了三个现场现象：

- 靠近时 IPM y 还在 0..119 内，十字能显示。
- 离远后 IPM y 出渲染域，显示函数提前拒绝，十字不进 boundary，也不叠加进灰度图。
- `find_corners()` 和日志仍能识别到，因为诊断里的 `inv` 直接用 `Cal_inv_rot_x/y`，没有走这个错误域检查。

修复：

- 新增 `code/app/assistant.cpp::ipm_pt_to_raw_display()`，专供上半 raw 显示使用。
- 该函数直接用 `Cal_inv_rot_x/y` 反投 IPM 浮点坐标，只检查反投后的 raw 坐标是否在 `0 <= x < RAW_W, 0 <= y < RAW_H`。
- 替换 `append_lpt_cross()`、`draw_atg_corner()`、`draw_atg_ipm_line()` 三处调用。
- `render_ipm_half()` 和 `copy_atg_ipm_pts()` 保留原来的 IPM 渲染域检查，因为下半 IPM 图本来就只显示 160x120 渲染域。

参考版差异：

- 参考版显示逻辑用 `Cal_inv_rot_x/y` 算完后只做屏幕范围检查，不会先要求 IPM 点落在 160x120 渲染域内。
- `inv_Lpt0_found/inv_Lpt1_found` 里的 `-5/-17`、`+5/-17` 偏移是十字远线搜索起点/元素逻辑，不是单纯显示补偿；本次没有照搬。
- 第 8 条 `LPT` boundary 通道本身不是已知根因，协议上限和 `valid_flag` 仍按现有实现保留。

剩余验证：

- 需要实机上传后验证 1.2~1.5m 远处 L 点是否显示。
- 预期上位机应同时看到 LPT boundary 十字和灰度白十字。
- 日志对照 `ATGLptDiag` 的 `inv=x,y`，十字应落在对应 raw 坐标附近。

## 和大佬版本的确定差异

参考版本路径：

```text
/mnt/e/longxin/LS2K0300_Library/LS2K300_Library/Seekfree_LS2K0300_Opensource_Library/test_project/智能车比赛资料v1.2_2/智能车比赛资料v1.2/ATG2022_Master/ATG2022_Master V1.2
```

大佬版 `USER/Cpu0_Main.c` 的核心参数：

```c
block_size = 9;
clip_value = 2;
sample_dist = 0.02;
pixel_per_meter = 41;
angle_dist = 0.2;
BEGIN_X = 7;
BEGIN_Y = MT9V03X_H * 0.9;
```

当前 `atg_reference/port/reference_step.c::reset_atg_params()`：

```c
block_size = 5;
clip_value = 8;
sample_dist = 0.03f;
pixel_per_meter = 116;
angle_dist = 0.2f;
BEGIN_X = 7;
BEGIN_Y = MT9V03X_H * 0.9;
```

这不是小差异。`sample_dist`、`pixel_per_meter`、`angle_dist` 共同决定重采样点距、局部角度窗口和 `i < 45`、`0.7 / sample_dist` 这类 id 门限的实际物理含义。不能只调 `60/73 deg` 一个阈值。

起搜逻辑差异：

- 大佬版固定在 `begin_y` 一行，从 `(W/2 - begin_x, begin_y)` 和 `(W/2 + begin_x, begin_y)` 向左右扫，要求连续 4 个暗点。
- 当前版从 `BEGIN_Y` 向上逐行扫到 `y=85`，要求连续 2 个暗点，并修正了局部阈值累加器不清零的问题。
- 这个改动让摄像头启动后更快找到边线，也让正放更稳定，但没有解决斜车身掉角点。

L 点判定差异：

- 大佬 C 版左侧 L 点本来就有方向门限：

```c
rpts0s[im1][0] > rpts0s[ip1][0] && rpts0s[im1][1] > rpts0s[ip1][1]
```

- 当前曾经把这个门限注释掉试过，但没有解决问题。
- 所以“左侧方向门限是迁移新增 bug”这个说法不准确；它是原算法自带约束。真正问题更可能是：原算法这套固定阈值、固定 id 门限、单点曲率峰值和当前相机/IPM/尺度不再匹配。

## 当前判断

我不建议继续盲目降阈值。现在需要先把失败原因打出来。

当前 `find_corners()` 的日志只给 `Lpt*_found/id` 和 `conf*_max`，不足以判断失败门限。尤其 `conf*_max` 只是循环中的最大值，不等于最终被接受或被拒绝的候选点；还可能受提前 `break` 顺序影响。因此看到 `conf` 高或低，都不能直接推出到底是哪一个门限失败。

更可疑的是这几个点：

- 斜车身会改变 IPM 点列方向和局部角度峰值位置，单点 `fabs(angle[i]) - neighbor_avg` 很容易被摊平或偏移。
- 当前只接受第一个满足条件的 NMS 候选，不输出“最强候选但被哪个条件拒绝”。
- 左侧有方向门限、右侧没有等价门限；这来自原算法，但在当前 IPM 尺度下仍然可能变得脆。
- `i < 45`、`Lpt*_id < 5`、`Lpt*_id < 25` 这类门限和 `sample_dist` 强绑定，迁移后物理距离语义已经变了。
- 上位机远处没看到角点，还需要区分四种情况：`find_corners()` 没找到、找到了但投回原图越界、找到了但投影/显示坐标落到错误位置、找到了但 boundary/灰度叠加链路在远处被裁掉或不可见。

## 建议下一步

第一步只加诊断，不改变行为：

- 起搜诊断：左右 `seed_found`、`seed_x`、`seed_y`、搜索到的是第几行。
- 每侧 L 候选诊断：`best_i`、`best_conf_deg`、`im1/ip1`、`i<45`、角度下限、角度上限、左侧方向门限、最终是否接受。
- 候选坐标诊断：`rpts*s[i]`、`rpts*s[im1]`、`rpts*s[ip1]`，以及投回原图后的 `inv_x/inv_y` 是否在上位机画面内。
- 选线诊断：`track_type`、`cross_type`、`circle_type`、`rpts_num`、`rptsn_num`、选中的是 `rptsc0/rptsc1/Splicing_*` 哪一路。这个只作为分流排查，不引用被忽略的旧日志。

第二步再改算法：

- 不要继续只调 `60/73 deg`。
- 改成“扫描全部候选，选最强且通过几何条件的候选”，不要第一个满足就停。
- 用 IPM 重采样点列的窗口向量夹角和 signed cross product 表达拐点方向，左右两侧给对称但符号相反的约束。
- id 门限尽量写成物理距离再换算成点数，例如 `near_lpt_limit = round(near_m / sample_dist)`。
- 保持失败显性失败，不复用上一帧角点，不造假角点，不为了上位机好看发假 L 点。


## 2026-06-13 最新实机结果

这次要修正当前问题分类：曾有一组板端日志显示算法已经找到 L 点：

```text
frame=0 line=1 track=1 cross=0 circle=0 raw=84/90 sel=6/13 l=1@6/1@6 conf=94.1/86.0
ATGSeedDiag: seed=1@10,108/1@130,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=6(94.1) imip=0/11 pass=11111 acc=6 ipm=51.8,97.1 inv=37.3,59.9 | 6(86.0) imip=0/13 pass=11111 acc=6 ipm=103.9,94.9 inv=113.4,62.2
```

这组日志只用于说明“显示链路可能独立有问题”，不要扩大成“所有姿态算法都没问题”。结论：

- `l=1@6/1@6`、`pass=11111`、`acc=6` 说明 `find_corners()` 已经接受左右 L 点。
- 投回原图坐标约为左 `(37,60)`、右 `(113,62)`，没有被 `0 <= y < 120` 这类 raw 范围过滤。
- 之前白色方框是种子点，不是 L 点。
- 已尝试把 L 点从“只画进灰度图像”改为额外的 `LPT` boundary 通道；由于逐飞 assistant 最多 8 条 boundary，左右 L 点合并为同一条通道。最新实机现象更精确地说是：靠近时能看到，离远后即便日志已经识别到，也看不到原先那种明显十字。

因此当前必须新增一个更优先的子问题：**远处角点显示链路 bug**。它和“斜车身算法鲁棒性”有关联，但不是同一个问题。fable 接手时应先判断为什么在 `Lpt*_found=1` 且投影坐标合法的远处帧里，上位机仍不显示明显十字；同时也要保留“斜一点可能算法本身也掉点”的后续问题。

需要重点检查：

- `code/app/assistant.cpp::draw_atg_corner()` 是否用错投影函数、坐标取整或画图时机，尤其是远处 L 点投回 raw 后的位置是否和参考版一致。
- `config_points()` 中先构造 boundary、再修改 `g_asst.image`、最后 `send_display_frame()` 的顺序是否满足逐飞协议预期。
- 逐飞助手是否只显示前若干条 boundary，或第 8 条 boundary 颜色/图层不可见。
- `k_marker_value=255` 在当前灰度底图上是否被上位机显示策略覆盖；但不要把“肉眼不明显”当默认解释，用户确认正确版本的十字应明显可见。
- 是否应该复用大佬原始调试显示方式里的 `inv_Lpt0_found/inv_Lpt1_found` 偏移逻辑，而不是当前直接用 `rpts*s[id] -> inv_rot`；近处可见、远处不可见时，这个差异优先级更高。

## 给 fable5 的提示词

```text
你现在接手 LS2K0300 小车项目的 ATG 角点显示和识别问题。请先读真实代码、真实 diff 和当前交接文档，不要只按聊天记忆判断。

当前工作目录：
/mnt/e/longxin/LS2K0300_Library/LS2K300_Library/Seekfree_LS2K0300_Opensource_Library/test_project/front_car_mainline_autop_direct

大佬原始参考版本：
/mnt/e/longxin/LS2K0300_Library/LS2K300_Library/Seekfree_LS2K0300_Opensource_Library/test_project/智能车比赛资料v1.2_2/智能车比赛资料v1.2/ATG2022_Master/ATG2022_Master V1.2

请重点读：
1. docs/ATG角点斜车身问题交接.md
2. atg_reference/Project/CODE/shy_Image.c
3. atg_reference/Project/CODE/imgproc.c
4. atg_reference/Project/CODE/cross.c
5. atg_reference/Project/CODE/Half_check.c
6. atg_reference/Project/CODE/circle.c
7. atg_reference/port/reference_step.c
8. code/app/assistant.cpp
9. code/app/report.cpp
10. 参考版的 CODE/shy_Image.c、CODE/cross.c、USER/Cpu0_Main.c

当前不要一上来调阈值。问题要拆成 P0/P1：

P0：远处角点显示链路没有闭环。更准确的现象是：靠近时 L 十字能出现；离得远时，即便日志已经识别到 L 点，上位机也没有显示对应 L 十字。用户确认正确版本的 L 十字应非常明显；不要用“肉眼不明显”“被背景吃掉”解释。

P1：斜车身时算法鲁棒性仍然可疑，但必须等 P0 证明清楚后再动算法，避免把显示 bug 和识别 bug 混在一起。

有一组板端日志显示算法曾经找到并接受左右 L 点：

frame=0 line=1 track=1 cross=0 circle=0 raw=84/90 sel=6/13 l=1@6/1@6 conf=94.1/86.0
ATGSeedDiag: seed=1@10,108/1@130,108 begin=7,108 block=5 clip=8
ATGLptDiag: best=6(94.1) imip=0/11 pass=11111 acc=6 ipm=51.8,97.1 inv=37.3,59.9 | 6(86.0) imip=0/13 pass=11111 acc=6 ipm=103.9,94.9 inv=113.4,62.2

这说明：
- find_corners() 在这类帧里已经接受 Lpt0/Lpt1。
- 投回 raw 的坐标大约是左 (37,60)、右 (113,62)，没有 y 过高或 raw 越界过滤。
- 用户截图里白色方框是种子点，不是 L 点。
- 已尝试新增一个 LPT boundary 通道，把左右 L 点十字一起发给上位机；逐飞 assistant 最多 8 条 boundary，所以没有拆成两个通道。实机表现是靠近时能显示，离远后即便日志识别到也看不到原先那种明显十字。
- 上面这组日志只用于证明“显示链路可能独立有问题”，不要扩大成“所有姿态算法都没问题”。用户明确说不需要回溯旧日志。

请先审查并解决“远处角点显示链路 bug”：
1. 检查 code/app/assistant.cpp::draw_atg_corner()、copy_lpt_crosses()、config_points()、send_display_frame() 的时序和协议是否正确。
2. 判断逐飞助手是否只显示前若干 boundary，或第 8 条 boundary 有颜色/图层不可见问题。
3. 做最小证明实验，不要先改算法：
   - 实验 A：把远处日志识别到的 L 点十字临时放进一个已知可见的低编号 boundary 通道，例如 seed 行或 raw 左/右通道，确认上位机能否显示远处十字。
   - 实验 B：不用算法结果，直接在远处 raw 坐标画一个大十字；坐标优先用当帧 ATGLptDiag 的 inv_x/inv_y，确认灰度图叠加是否真的随图像发送。
   - 如果 A 可见而第 8 通道不可见，优先查 boundary 通道/颜色/valid_flag/上位机显示限制。
   - 如果 B 不可见，优先查图像叠加时机、send_camera_packet() 发送顺序、上位机是否使用了未叠加的底图。
4. 检查当前直接用 rpts*s[id] 经 perspective_lookup_ipm_to_raw() 反投是否和参考版显示一致。参考版 cross.c 里有 inv_Lpt0_found/inv_Lpt1_found，并带有 -5/-17、+5/-17 等显示偏移；需要判断这是显示补偿还是元素远线搜索起点，不要盲目照搬。
5. 不要把“肉眼不明显”当默认解释，用户确认正确版本十字应明显可见。
6. 输出 P0 的最小 patch 和实机验证步骤。如果需要实机验证，明确告诉用户“现在需要重新开板测试哪一个实验”。

第二个问题才是“斜车身算法鲁棒性”，不要和显示问题混在一起。已知算法差异：
- 参考版参数：block_size=9, clip_value=2, sample_dist=0.02, pixel_per_meter=41, angle_dist=0.2。
- 当前参数：block_size=5, clip_value=8, sample_dist=0.03, pixel_per_meter=116, angle_dist=0.2。
- 参考版起搜固定 begin_y 一行、连续 4 暗点；当前起搜从 BEGIN_Y 向上扫到 y=85、连续 2 暗点。
- 参考版左侧 L 点本来就有方向门限：
  rpts0s[im1][0] > rpts0s[ip1][0] && rpts0s[im1][1] > rpts0s[ip1][1]
- 当前曾去掉这个门限试验，但没有解决，所以不要简单把它定性为迁移新增 bug。
- 当前普通 L 阈值曾从 73 deg 降到 60 deg，但斜车身仍不稳定。

完成显示问题审查后，再设计算法侧方案：
1. 解释 sample_dist、pixel_per_meter、angle_dist、i<45、Lpt_id<5/25 等门限在迁移后物理意义是否改变。
2. 检查 find_corners() 当前是否只是第一个满足 NMS/阈值的点；是否应改为扫描全部候选并选择最强且几何一致的 L 点。
3. 检查左/右 L 点几何约束是否应改成对称 signed-turn 条件，而不是简单删除左侧方向门限。
4. 保持失败显性失败，不复用上一帧角点，不造假角点，不用隐藏 fallback。
5. 如果算法改动必须实机确认，列出具体摆车姿态：完全正、轻微左斜、轻微右斜；每种姿态要看日志里的 Lpt found/acc/inv 和上位机十字是否一致。

验证命令：
MAKE_JOBS=4 bash ./test.sh --host
MAKE_JOBS=4 bash ./test.sh --upload

板端启动命令参考：
ssh root@ls2k0300 'killall -9 front_car_mainline 2>/dev/null || true; env SMARTCAR_ASSISTANT=1 SMARTCAR_ASSISTANT_IP=192.168.0.100 SMARTCAR_ASSISTANT_PORT=8086 SMARTCAR_ASSISTANT_CONNECT_MS=30 SMARTCAR_ASSISTANT_RECONNECT_DIV=30 SMARTCAR_ASSISTANT_DIV=12 FRONT_CAR_DISPLAY=0 FRONT_CAR_PROCESS_FPS=120 FRONT_CAR_PRINT_DIV=1 FRONT_CAR_ENABLE_DRIVE=0 /root/front_car_mainline >/tmp/front_car_mainline.log 2>&1 &'

请输出：
- 角点显示链路根因判断
- 最小显示修复/验证方案
- 和参考版显示方式的差异
- 斜车身算法问题的后续方案
- 风险点
- 最小修改顺序
- 哪些点必须实机验证，以及用户需要怎么摆车/看日志
```
