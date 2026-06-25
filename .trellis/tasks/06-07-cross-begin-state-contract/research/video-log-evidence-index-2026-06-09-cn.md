# Video/Log Evidence Index - 2026-06-09

## Scope

本文件只记录本轮睡前排查的视频、截图、日志证据索引。它不提出 runtime 行为改动，也不把任何截图观察直接升级为 tracking 修复结论。

视频路径：

`/mnt/e/Documents/xwechat_files/wxid_kpektjxqvx4722_59bd/msg/video/2026-06/e122b50088b48a3708486e73becd76dd.mp4`

临时抽帧目录：

`/tmp/tracking_video_evidence/`

## Video File Facts

`ffprobe` 只读检查结果：

| Field | Value |
| --- | --- |
| Container | QuickTime / MOV, MP4 compatible |
| Size | 7,740,517 bytes |
| Duration | 54.828367 s |
| Video codec | H.264 / AVC |
| Stored frame size | 720 x 1610 |
| Display rotation | 90 deg |
| Extracted frame size | 1610 x 720 |
| Video `r_frame_rate` | 60/1 |
| Video `avg_frame_rate` | 54840000/1644851 ~= 33.34 fps |
| Video `nb_frames` | 1828 |
| Audio | AAC mono 48 kHz |
| Creation time | 2026-06-08T14:35:40Z |

注意：视频文件帧率、上位机显示 FPS、算法日志 `frame=` 是三个不同时间轴。不能把它们直接等同。

## Extracted Evidence Frames

已抽取少量关键帧到 `/tmp/tracking_video_evidence/`：

- `t0.jpg`
- `t20.jpg`, `t20_logcrop.jpg`
- `t28.jpg`, `t28_logcrop.jpg`
- `t29.jpg`, `t29_logcrop.jpg`
- `t37.jpg`, `t37_logcrop.jpg`
- `t38.jpg`, `t38_logcrop.jpg`
- `t47.jpg`, `t47_logcrop.jpg`
- `t54.jpg`

`*_logcrop.jpg` 是从底部日志区域裁剪并放大增强的只读辅助图，便于人工读数。

## Readable Timeline Anchors

以下是从视频帧和用户日志能直接读到或较可靠读到的锚点。

| Video time | Log frame | Readable log facts | Screen facts | Evidence strength |
| --- | ---: | --- | --- | --- |
| User log | 0 | `ring=0/0 line=1 track=2 mid=36 seed=(10,116)-(140,116) trace=81/81 m0=(89,109) ml=(87,74) guide=1.97 yaw=55 duty=14/16` | 用户描述直道正常 | 用户文本日志，强 |
| 20 s | 1454 | `ring=0/0 line=1 track=1 mid=16 seed=(3,118)-(-1,-1) trace=22/0 m0=(89,109) ml=(68,92) guide=27.63 yaw=1500 duty=2/17` | 上位机 `FPS: 10`，字节数/秒 `197590`；画面有左右边线和红线 | 裁剪日志可读，强 |
| 20 s | 1455 | `ring=0/0 line=1 track=2 mid=42 seed=(-1,-1)-(133,116) trace=0/92 m0=(89,109) ml=(64,91) guide=31.38 yaw=1500 duty=2/17` | 同上 | 裁剪日志可读，强 |
| 28 s | 2361 | `ring=0/0 line=0 rej=4 track=0 mid=0 seed=(-1,-1)-(131,116) trace=0/86 center=-1 guide=0.00 duty=0/0` | 画面只见绿色左边线，未见红中线 | 裁剪日志可读，强 |
| 28 s | 2364 | `ring=0/0 line=1 track=1 mid=35 seed=(3,112)-(131,116) trace=86/95 m0=(89,109) ml=(81,81) guide=8.90 yaw=249 duty=5/10` | 随后恢复红中线 | 裁剪日志可读，强 |
| 29 s | 2563 | `ring=2/0 line=1 track=1 mid=40 seed=(16,116)-(153,107) trace=99/160 m0=(89,109) ml=(111,91) guide=-28.15 yaw=-1500 duty=14/0` | 画面有双边线和红中线，红中线偏向右侧弯内 | 裁剪日志可读，强 |
| 29 s | 2564 | `ring=2/0 line=0 rej=3 track=0 mid=0 seed=(-1,-1)-(-1,-1) trace=0/0 center=-1 guide=0.00 duty=0/0` | 下一帧无线 | 裁剪日志可读，强 |
| User log | 2911 | `ring=1/0 line=1 track=1 mid=120 seed=(3,112)-(131,116) trace=160/81 l=1/1@14/... m0=(89,109) ml=(84,117) guide=18.31 yaw=1282 duty=9/24` | 用户描述直道硬拐 | 用户文本日志，强 |
| 37 s | 3502 | `ring=2/3 line=0 rej=4 track=0 mid=0 seed=(12,116)-(-1,-1) trace=147/0 center=-1 guide=0.00 duty=0/0` | 画面未见红中线 | 裁剪日志可读，强 |
| 37 s | 3504 | `ring=2/3 line=0 rej=3 track=0 mid=0 seed=(-1,-1)-(-1,-1) trace=0/0 center=-1 guide=0.00 duty=0/0` | 画面未见红中线 | 裁剪日志可读，强 |
| 38 s | 3556 | `ring=2/3 line=0 rej=4 track=0 mid=0 seed=(8,116)-(-1,-1) trace=150/0 center=-1 guide=0.00 duty=0/0` | 只有绿色边线折到近处，未见红中线 | 裁剪日志可读，强 |
| 38 s | 3557 | `ring=2/3 line=0 rej=3 track=0 mid=0 seed=(-1,-1)-(-1,-1) trace=0/0 center=-1 guide=0.00 duty=0/0` | 同上 | 裁剪日志可读，强 |
| User log | 3570 | `ring=1/2 line=0 rej=3 track=0 mid=0 seed=(-1,-1)-(-1,-1) trace=0/0 center=-1 m0=(-1,-1) ml=(-1,-1) guide=0.00 duty=0/0` | 用户描述 RUN 丢线停车 | 用户文本日志，强 |
| 47 s | 4596 | `ring=1/2 line=1 track=2 mid=29 seed=(-1,-1)-(136,116) trace=0/135 m0=(89,109) ml=(64,107) guide=44.87 yaw=1500 duty=0/16` | 画面有黄色右边线和红中线，红中线在近处左侧弧形/折返 | 裁剪日志可读，强 |
| 47 s | 4597 | `ring=1/2 line=0 rej=3 track=0 mid=0 seed=(-1,-1)-(-1,-1) trace=0/0 center=-1 guide=0.00 duty=0/0` | 下一帧无线 | 裁剪日志可读，强 |

## User-Attached Image Anchors

本节记录用户后来重新贴出的截图/录屏帧。聊天中两个临时图片路径已失效，无法读取：

- `/mnt/e/Documents/xwechat_files/wxid_kpektjxqvx4722_59bd/temp/RWTemp/2026-06/8059a71b028bbcbe29e29af8c027b04f/583e8dc64f8dc07edadf0319c56cee49.png`
- `/mnt/e/Documents/xwechat_files/wxid_kpektjxqvx4722_59bd/temp/RWTemp/2026-06/8059a71b028bbcbe29e29af8c027b04f/c7161f4137347fc5d250431e8d92f501.jpg`

可见截图事实如下，仍按“先记录，不直接下结论”的规则处理：

| Image | Video time | Readable log facts | Screen facts | Immediate use |
| --- | ---: | --- | --- | --- |
| Image #3 | 00:20 | 可读到 `frame=1550 ring=0/0 line=0 rej=4 track=0 seed=(11,116)-(143,116) trace=96/88 ... xst=0/1/...@89,109 ... center=-1 m0=(-1,-1) ml=(-1,-1) guide=0.00`；下一行约 `frame=1551 line=1 track=1 seed=(7,116)-(-1,-1) trace=93/0 ... center=89 m0=(89,109)` | 红中线/黄边线在弯道处可见，FPS=10，字节数/秒约 197590 | `rej=4` 且 seed/trace 都有，说明存在“有当前边界但发布失败”的中线/预瞄门问题。 |
| Image #4 | 00:20+ | `frame=2088 ring=0/0 line=0 rej=4 track=0 mid=7 seed=(6,116)-(-1,-1) trace=11/0 idrej=2 ... center=-1 m0=(89,109) ml=(75,98) guide=0.00`；下一行 `frame=2089 line=1 track=1 mid=8 seed=(6,116)-(-1,-1) trace=10/0 idrej=2 ... center=89 ... guide=25.21 yaw=1500 duty=4/20` | 单侧黄边线和红中线都很短，FPS=10 | 这是“短中线 + 强 guide”的当前帧控制风险候选，不能和 `frame=2911` 后方预瞄混为一类。 |
| Image #5 | 00:28 | `frame=2563 ring=2/0 line=1 track=1 mid=40 seed=(16,116)-(153,107) trace=99/160 ... ml=(111,91) guide=-28.15 yaw=-1500 duty=14/0`；`frame=2564 ring=2/0 line=0 rej=3 seed=(-1,-1)-(-1,-1) trace=0/0` | 双边线和红中线可见，随后无线 | `line=1` 强指令后一帧 `rej=3`，需要区分 seed 真失败还是身份过滤清空。 |
| Image #6 | 00:29 | 同 `frame=2563/2564` 邻域 | 画面中左右边线均可见，红中线偏弯内 | 支持 V02 锚点，不新增独立结论。 |
| Image #7 | 00:37 | `frame=3556 ring=2/3 line=0 rej=4 seed=(8,116)-(-1,-1) trace=150/0 ... center=-1 m0=(-1,-1)`；下一行 `frame=3557 ring=2/3 line=0 rej=3 seed=(-1,-1)-(-1,-1) trace=0/0` | 画面未见红中线，边界显示很少 | 环岛 OUT/END 附近存在“有单侧 trace 但无控制中线”和随后全空。 |
| Image #8 | 00:38 | 同 `frame=3556/3557` 邻域 | 可见绿色单侧边界折线和白色十字光标，FPS=10，字节数/秒约 177600 | 需要确认 overlay 代表 raw 边界、过滤后边界还是显示采样；不能据此发布旧中线。 |
| Image #9 | 00:47 | `frame=4815 ring=1/2 line=0 rej=3 seed=(-1,-1)-(-1,-1) trace=0/0 idrej=2 ...`；下一行约 `frame=4816 ring=1/2 line=1 track=2 mid=31 seed=(-1,-1)-(132,116) trace=0/132 ... center=89 m0=(89,109) ml=(59,...)` | 黄色边线和红中线可见，红中线弯折明显，FPS=10，字节数/秒约 174092 | `rej=3` 同时 `idrej=2` 是高价值证据：显示层的 `seed=-1 trace=0` 可能是身份拒绝后清空，不一定是 find_seeds 完全失败。 |

从这些补充截图新增出的最有用结论：

- `rej=4` 不是“没线”，因为 Image #3/#4 能看到 seed/trace 仍有值；owner 更可能是 `publish_track_result()` 的中线数量、预瞄距离或前方性门。
- `rej=3` 也不能再简单读成“完全没搜到”，因为 Image #9 中 `idrej=2` 与 `seed=-1 trace=0` 同时出现，符合“trace/seed 曾存在但被身份过滤清掉”的可能。
- 下一版日志必须新增 `pre=` 字段，保留 `find_seeds()` 后和身份过滤前的当前帧 seed/trace；否则无法决定下一刀是 seed 搜索、identity gate，还是 midline 发布门。

## Rough Time Mapping

用可读视频锚点做最小二乘，仅作为“去哪段视频找帧”的索引：

`log_frame ~= 116.742 * video_time_s - 865.874`

由此估算：

| Log frame | Approx video time |
| ---: | ---: |
| 2911 | 32.35 s |
| 3570 | 38.00 s |

用 29 s `frame=2563` 到 38 s `frame=3556` 的局部线性估算：

| Log frame | Approx video time |
| ---: | ---: |
| 2911 | 32.15 s |
| 3570 | 38.13 s |

限制：视频底部日志不是每一算法帧都可见，视频录屏帧率也不是算法帧率；这个换算只能用于定位邻域，不能作为行为时序证明。

## Facts Directly Supported

- 上位机画面多处显示 `FPS: 10`，字节数/秒约 `174092` 到 `197818`；这支持“显示/传输层可见刷新率约 10 FPS”，不能单独证明算法处理帧率不足。
- 普通 `ring=0/0` 阶段也出现单侧 seed/trace + 较大 guide 的帧，例如 `frame=1454/1455`。
- `frame=2563` 和 `frame=4596` 都是 `line=1` 且 guide 很大，紧邻下一条可读日志转为 `line=0 track=0 seed=-1 trace=0`。
- `frame=3502/3556` 一类 `ring=2/3` 帧存在单侧 seed/trace，但仍 `line=0 track=0 mid=0`；随后可见全无 seed/trace。
- 用户给出的 `frame=3570 ring=1/2 line=0 seed=-1 trace=0` 与视频中 37-38 s 的“元素阶段无线/无中线输出”属于同类现象，但方向/阶段不完全相同。
- 用户给出的 `frame=2911` 的 `ml=(84,117)` 在 y 上落在 `m0=(89,109)` 后方，和“中线方向/预瞄点异常”高度相关；这是从文本日志直接支持的事实。

## Not Supported Yet

- 不能仅凭视频证明 `frame=2911` 的硬拐由环岛状态切换导致；该帧是 `ring=1/0`，但是否当前帧按元素模式控制仍需对照代码时序。
- 不能仅凭截图证明“长期识别不到”的持续长度；当前只读样本显示有短周期丢线-恢复，也有连续无线段，需要更密日志或更密抽帧确认。
- 不能仅凭 `FPS: 10` 判断 tracking 算法刷新率不足；它可能只是上位机显示/图传层频率。
- 不能据此加单侧硬拒绝。普通帧和环岛帧都存在单侧证据，Trellis spec 明确要求 single-side/no-opposite-anchor 先区分当前帧控制风险和跨帧学习风险。
- 不能用旧中线、旧边界、旧 guide 或旧 duty 作为修复方案；所有无线帧必须暴露为当前帧缺失几何。

## Minimal Follow-Up Data Needed

下一轮用户如果能补日志，最小字段建议保持一行可 grep：

`frame ring cross line rej track mid seed trace idrej l pair ps pw xst xfar xmid center m0 ml guide yaw duty`

建议额外补充但不要一次塞太多：

- 当前帧 `mode` 或元素选择结果：普通 / ring / cross / zebra。
- `ring_kind0/ring_kind_after` 和 `cross_state0/cross_state_after`，用于判断 frame-start 状态和 element_process 后状态是否混淆。
- `selected_midline` 的首点、最后点、最小 y、最大 y、预瞄点 index；尤其记录是否存在 `ml.y >= m0.y`。
- `build_rptsn` 的 `begin_id`、输入点数、输出点数、输出最小 y；用于复核“最远搜到 y=34，就改了这个”是否真的解决根问题。
- `publish_track_result` 失败原因拆分：无 seed、无 trace、midline 数量不足、lookahead 不足、方向不前进、元素短线允许/不允许。
- 图传单独记录 `assistant FPS/bytes_per_sec/dot_num/SMARTCAR_ASSISTANT_DIV`，不要与 tracking 行为补丁混在一起。

## First Priority Index

先围绕以下三个根问题分开排查：

1. `frame=2911` 类：`line=1`、`track` 有值、`mid` 很多，但 `ml.y >= m0.y` 或 guide 突变，属于“发布了可疑中线/预瞄点”。
2. `frame=2564/3570/4597` 类：`line=0`、`seed=-1`、`trace=0`，属于“当前帧无线/无几何”，不能用 fallback 隐藏。
3. `frame=1454/1455/2563/4596` 类：单侧或元素阶段 `line=1` 且 guide 很大，属于“当前帧控制风险”，需要和学习状态污染分开。
