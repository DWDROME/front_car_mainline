# 睡前计划：视频证据驱动的 tracking 复核

## 当前约束

- 当前没有联调环境，不能把任一现象直接归因到算法、控制或图传。
- 本轮不新增 tracking 行为功能，不扩大改动面。
- 曾有 `code/tracking/imgproc.cpp` 中线前向推进检查草稿，现已撤回；在完成视频/日志证据表和多轮确认前，不作为实施方案推进。
- 当前代码工作树已恢复干净；本文件位于被 `.gitignore` 忽略的 `.trellis/` 下，属于本地任务证据，不是 runtime 补丁。
- 用户提供的视频已确认可在 WSL 路径读取：
  `/mnt/e/Documents/xwechat_files/wxid_kpektjxqvx4722_59bd/msg/video/2026-06/e122b50088b48a3708486e73becd76dd.mp4`。
- `ffprobe` 显示视频约 54.83 秒，720x1610，约 1828 帧，标称 60 fps，但平均帧率约 33.34 fps；这只说明视频文件属性，不直接证明图传链路刷新率问题。
- 参考版优先级最高：RT1064 全国一等奖代码是当前 tracking 合同的主要依据。任何改进必须先对照参考版，无法直接对照时必须明确写“无直接参考等价”。
- 每一次推送都按关键生产变更对待：必须现象可认同、参考可对照、补丁足够小、验证可回看。

## 已知现场现象

- `frame=0`：普通直道有线，`track=2`，`mid=36`，`m0=(89,109)`，`ml=(87,74)`，`guide=1.97`。
- `frame=2911`：刚检测左环 BEGIN，`ring=1/0`，但当前帧按帧首状态仍可能是普通选线；`track=1`，`mid=120`，`m0=(89,109)`，`ml=(84,117)`，`guide=18.31`，现场表现为直道硬拐。
- `frame=3570`：`ring=1/2` RUN 中，`line=0`，`seed=(-1,-1)-(-1,-1)`，`trace=0/0`，属于当前帧无可用线索，不能用旧中线隐藏。
- 用户观察包括：十字可能有问题、环岛状态切换基本可接受、搜线不容易丢、刷新率不足、长期识别不到、中线有毛病。
- 用户补充硬规则：`最远搜到 y=34，就改了这个` 必须被记录为独立线索；不能把它散进泛化阈值或顺手改动里。

## 视频与截图索引

抽帧文件仅作本地查看，放在 `/tmp/front_car_video_frames/`，不提交二进制图片。

| 索引 | 视频时间 | 视频约帧号 | 底部日志锚点 | 可见事实 | 暂不下的结论 |
| --- | ---: | ---: | --- | --- | --- |
| V00 | 00:20 | 667 | `frame=1454/1455` | 上位机显示 FPS=10，左右边界与红中线均可见，`guide` 约 27.63/31.30，`duty` 有明显差动。 | 不能仅凭视频文件帧率证明图传链路瓶颈；也不能直接证明控制错误。 |
| V01 | 00:28 | 934 | `frame=2361/2364` | 一帧 `line=0 rej=4 track=0` 后恢复 `track=1 mid=35 guide=8.90`；画面主要见左/绿色边界。 | 不能直接归因于单侧身份错误，需要查 seed/trace/IPM/order。 |
| V02 | 00:29 | 967 | `frame=2563/2564` | `ring=2/0`，先 `track=1 mid=40 guide=28.15 duty=14/0`，紧接 `line=0 rej=3 track=0`；画面有左右边界和红中线。 | 不能直接说 BEGIN 复位或中线前向规则就是修复点。 |
| V03 | 00:37 | 1234 | `frame=3502/3504` | `ring=2/3`，多帧 `line=0 track=0`；画面无红中线。 | 不能用旧中线兜底解释或修复。 |
| V04 | 00:38 | 1267 | `frame=3556/3557` | `ring=2/3`，局部绿色边线与十字光标可见，`line=0 track=0`。 | 不能单帧判定是环岛 END、视觉阈值或图传问题。 |
| V05 | 00:47 | 1567 | `frame=4596/4597` | `ring=1/2`，先 `track=2 mid=29 guide=44.83 duty=0/16`，下一帧 `line=0 rej=4 track=0`；红中线在弧线区域有折返/断续。 | 不能直接扩成单侧硬拒绝或控制平滑。 |

## 核心问题形式化

把问题拆成四个互不混淆的判定：

1. 当前帧中线几何是否成立：起点是否贴近控制参考点，后续点是否向远处推进，是否有足够 lookahead。
2. 元素状态切换是否影响当前帧控制：`element_process()` 内新进入 BEGIN/RUN 的状态，不应反向改变当前帧已经选择的模式。
3. 单侧/no-opposite-anchor 是否可证明身份：如果缺少对侧 seed/trace/IPM paired evidence，只能记录不充分，不能直接加单侧硬拒绝。
4. 控制链是否放大视觉误差：若 `guide_error` 稳定而 yaw/duty 大摆，优先转向控制/反馈审计；若 `guide_error` 本身跳变，才继续收紧 tracking 几何。
5. `y=34` 线索是否代表 farthest point/search depth 不足、元素裁剪过早、图传显示采样误导，还是当前帧真实几何只到这里。这个问题必须用 owner 函数和日志字段确认，不能直接改阈值。

## 证据采集计划

1. 从视频抽关键帧和缩略接触表：
   - 按时间均匀抽帧，先建立全局时间轴。
   - 对用户指出的硬拐、长期识别不到、中线异常位置，额外抽邻域帧。
   - 只标注画面事实：边线、红/中线显示、车辆姿态、是否接近十字/环岛。

2. 建日志时间轴：
   - 将用户给出的 `frame=0/2911/3570` 作为锚点。
   - 后续每次新日志都追加到同一张表，不单帧下结论。
   - 每行至少记录 `ring/cross/line/rej/track/mid/seed/trace/m0/ml/guide/yaw/duty`。

3. 建分支/提交对照轴：
   - 当前 `main` 在 `d101ad7`，本地比 `origin/main` 多一个 learning-order commit。
   - 只读比较关键分支：`upload/mainline-convergence`、`upload/mainline-convergence-ready`、`redline-control-midline-push`、`backup/*`。
   - 重点找行为合同变化，不做跨分支大搬运。

4. 四审计同步：
   - 参考合同：RT1064 `circle.c`、RT1064 `main.c` 的中线重采样/元素时序。
   - 当前实现：`mainline.cpp`、`imgproc.cpp`、`ring.cpp`、`cross.cpp`、`assistant.cpp/report.cpp`。
   - Git 回归：`103daa6 -> bdc7b27 -> d101ad7` 以及相关分支差异。
   - Trellis/check gate：PRD、tracking-critical-audit-guide、quality-guidelines、现有 research notes。

## 决策门

任何行为改动必须先通过这些门：

- 有视频帧或日志帧能稳定复现，不靠截图印象。
- 能指出当前 owner 函数和具体不变量失败。
- 能说明参考版是否有直接等价合同；没有就明确写“无直接参考等价”。
- 能填写固定表：`参考版怎么样 / 当前代码差异 / 我修改什么 / 原因 / 不是兜底的证据`。
- 一次只改一个行为面：tracking 几何、元素状态、图传降采样、控制链路不能混在一个补丁里。
- 补丁先以只读诊断或 host-only test 优先；确需 runtime 行为时，再单独确认。
- 任何“绝对可能的改进”必须先变成可验收命题：现象上用户认可、参考版可对照、失败帧能命中、修复后有相同索引可回看。

## 问题索引

| 编号 | 问题 | 现象锚点 | 初始 owner 候选 | 参考优先级 | 下一步 |
| --- | --- | --- | --- | --- | --- |
| P0 | 最初根因是否仍未解决 | 用户强调需要能回看“根本的一开始的问题并没有解决” | 任务全局索引 | RT1064 主链 + 关键历史提交 | 每次改动后回填此行：是否解决、证据是什么、是否只是绕开。 |
| P1 | 直道硬拐/中线向后或横向异常 | `frame=2911`，`m0=(89,109)`，`ml=(84,117)`，`guide=18.31` | `classify_frame_mode()`、`build_frame_boundaries_and_candidates()`、`build_selected_midline()`、`build_rptsn()` | RT1064 `main.c` 车轮点归一化和重采样 | 先证明当前中线点序是否违反前向/远端几何，再讨论是否有参考等价门。 |
| P2 | 环岛 RUN/END 当前帧无 seed/trace 停车 | `frame=3570`、V03/V04 | `ring_process()`、`crop_candidates_for_mode()`、seed/trace owner | RT1064 `circle.c` BEGIN/RUN/END 状态链 | 先查 RUN/END 期是否应改变 track side 或裁剪范围。 |
| P3 | BEGIN/RUN 中强指令后下一帧丢线 | V02 `frame=2563->2564`、V05 `4596->4597` | `publish_track_result()`、`update_search_center()`、ring state transition | RT1064 ring + 当前 learning-order guard | 区分当前控制风险与下一帧 acquisition 风险。 |
| P4 | `最远搜到 y=34` | 用户补充 | search/trace/resample/farline 相关 owner 待定位 | 参考版扫描范围与重采样合同 | 明天先补字段索引，不能直接调阈值。 |
| P5 | 图传 FPS=10/点数多 | V00-V05 上位机 UI | `code/app/assistant.cpp`、report/assistant packet | 无 tracking 参考等价，属于图传性能面 | 单独任务确认；不能与 tracking 行为补丁混做。 |
| P6 | 十字可能有问题 | 用户观察，无新具体日志 | `cross.cpp`、farline old_l/source/reuse | RT1064 cross + 当前已修 source guard | 等新日志或视频锚点，不抢先改。 |

## 多 agent 只读审计记录

| 角色 | 状态 | 核心结论 | 对后续的约束 |
| --- | --- | --- | --- |
| Trellis/spec/check gate | 已完成 | 硬规则成立：不急加功能、不 stale fallback、单侧不硬拒、图传和 tracking 分开、每个行为改动必须 rationale table。 | 任何 runtime 改动前先过 gate；`imgproc.cpp` 草稿、BEGIN 超时、图传点数都不是已批准方案。 |
| Git regression | 已完成 | 当前 `main=d101ad7`，比 `origin/main=d2ccaf0` ahead 1；`upload/*`、`redline-control-midline-push`、`backup/*` 都是祖先/历史线索，不应直接合并。 | 若要确认“根本问题没解决”，用 worktree 对照 `d2ccaf0`/`d101ad7`/`aafcea8`/`bdc7b27`/`103daa6`，同输入只比关键字段。 |
| Reference + current contract | 已完成 | `frame=2911 ring=1/0` 是本帧刚检测左环，按当前合同仍应普通选线；硬拐更直接指向普通候选中线/选边/重采样。`build_rptsn()` 与 RT1064 一样找最近点并固定到 `cx/cy`，当前未检查后续点是否前向。 | 不能把 `frame=2911` 归因到环岛 RUN；若要改 `build_rptsn()`，必须先证明候选/输出点序失败，而不是凭一行日志。 |
| Video/log evidence index | 已完成 | 已新增 `research/video-log-evidence-index-2026-06-09-cn.md`。问题至少分三类：`frame=2911` 类是发布可疑中线/预瞄点；`frame=2564/3570/4597` 类是当前帧无线/无几何；`frame=1454/1455/2563/4596` 类是当前帧强 guide 控制风险。 | 三类问题不能混修；`FPS: 10` 只支持图传/显示层刷新率约 10 FPS，不能证明算法帧率不足。 |

## 分支与提交索引

| 提交/分支 | 作用 | 后续用途 |
| --- | --- | --- |
| `103daa6` | 中线起点、`guide_error`、控制参考点对齐参考版的关键点。 | 只比较起点/误差合同，不证明当前中线一定正确。 |
| `bdc7b27` | 拆分 single-side `l_ok` 与 strict double-L，重整十字/环岛语义。 | 回归起点之一；不能整段回滚。 |
| `7e5663d` / `033b633` / `02dc1e0` | 曾经的 Unity/CD 风格 ring pending/AIB/BW 链路。 | 只解释历史，不作为当前主参考。 |
| `aafcea8` | 恢复 RT1064 风格 ring：单侧 L + 对侧 straight 进 BEGIN。 | 当前环岛主合同参考之一。 |
| `d2ccaf0` | `origin/main`，搜索中心写回到 IPM 身份复核后的远端基线。 | 明天最小对照基线。 |
| `d101ad7` | 本地 ahead 1，普通帧搜索中心学习延后到 selected midline 几何成立后。 | 当前候选修正；必须用日志/视频与 `d2ccaf0` 对照。 |
| `upload/mainline-convergence*` / `redline-control-midline-push` / `backup/*` | 祖先阶段快照，包含远线、搜索中心、显示红线等历史。 | 只作索引，不直接合并。 |

最小 Git 对照计划：

1. 不切当前分支，必要时用 worktree 建只读对照目录。
2. 同一批视频抽帧/日志输入分别跑 `d2ccaf0` 和 `d101ad7`。
3. 只比 `frame=2911` 的 `m0/ml/guide/track/ring_kind0`，`frame=3570` 的 `seed/trace/rej/ring state`。
4. 若两边都复现，说明 `d101ad7` 没解决根本问题；再向前比 `aafcea8`、`bdc7b27`、`103daa6`。

## `y=34` 线索初查

`rg` 显示 `34` 不是单一概念：

- `code/tracking/ring.cpp`：`k_have_step = 34`，有线步长阈值。
- `code/tracking/boundary.cpp`：`k_corner_open_step = 34`、`k_straight_scan_step = 34`、`k_straight_min_step = 34`。
- `docs/阈值笔记_boundary_ring.md`：多处解释 `1.0m -> 34`，并记录 `k_corner_open_step: 50 -> 34`、`k_straight_scan_step: 50 -> 34` 等历史。
- `code/tracking/ipm_table_generated.cpp` 有大量普通数值 `34`，不可作为阈值证据。

所以“最远搜到 y=34，就改了这个”明天必须先分清：

- 是 raw 图像行 `y=34`；
- 是中线/边界点数 `34`；
- 是 `1.0m / 0.03m ~= 34` 的距离阈值；
- 还是远线/环岛状态报告里某个没有打印出来的最远 y。

不能在这个问题未分清前直接改阈值。

## 明天第一轮诊断字段

优先补 `frame=2911` 附近，只读或诊断优先：

- `rptsc0_num/rptsc1_num`；
- 被选中的 `work_track_type` 来自普通还是元素；
- `build_rptsn()` 的 `begin_id`；
- `begin_id` 前后 3-5 个 `rpts` 点；
- 输出 `midline` 前 5 个点；
- `midline` 中最小 y、最大 y、lookahead 命中的点；
- 原始边界 `trace` 的 min_y/max_y 和是否跨 seed/同 row 反序；
- 若涉及 `y=34`，同步打印这个 `34` 的来源字段名。

`frame=3570` / V03-V05 第二优先：

- seed 搜索失败原因：无白入口、阈值失败、起搜中心偏出，还是状态裁剪后无候选；
- ring RUN/END 当帧选边；
- crop 前后的左右候选点数；
- 是否存在图像中有边线但算法 `seed=-1/trace=0` 的矛盾。

## 已落第一刀：普通帧前方预瞄发布门

这不是诊断字段，而是针对 `frame=2911` 的实质修正。

算法判断：

- `frame=2911` 是 `line=1`、`track=1`、`mid=120`，不是无线停车。
- 但 `m0=(89,109)`，`ml=(84,117)`，预瞄点 `ml.y` 比参考点 `m0.y` 更大；本项目坐标系 `y` 向下增大，所以该预瞄目标在车后方。
- 当前 `lookahead_error()` 使用 `dy = ref.y - target.y + ROAD_HALF_WIDTH * 8/9`。代入 `dx=-5`、`ref.y=109`、`target.y=117`、`ROAD_HALF_WIDTH=26`，可得到约 `18.31deg`，与日志 `guide=18.31` 对上。
- 这说明前向偏置把一个后方目标“救成了可计算角度”，旧发布门只看累计弧长，不看目标方向。
- Image #4 进一步证明短中线也会发布强控制：`frame=2089 line=1 track=1 mid=8 guide=25.21 yaw=1500`。旧门允许 `2/3 * LOOKAHEAD_DIST` 的短预瞄，普通帧不应这样发强指令。

代码改动：

- `code/tracking/imgproc.hpp/.cpp` 新增 `midline_has_forward_lookahead()`，要求普通帧覆盖完整 `LOOKAHEAD_DIST`，且目标满足 `target.y < ref.y`。
- `code/tracking/mainline.cpp::publish_track_result()` 中，普通帧发布控制前改为检查完整前方预瞄。
- 新增 host-only `code/test/midline_lookahead_test.cpp`，证明旧距离门对后方预瞄、短前方预瞄仍会通过，而新门会拒绝。
- `code/CMakeLists.txt` 和 `code/test.sh` 接入该 host 测试。

固定 rationale table：

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `main.c:381-401` 找最近 `begin_id`、固定到 `cx/cy` 并重采样；`main.c:404-410` 用预瞄点计算 `dy = cy - rptsn[aim_idx][1] + 0.2 * pixel_per_meter`。参考版按 `aim_distance` 取预瞄点，没有 `2/3` 短预瞄发布合同。 | 当前 `midline_has_lookahead()` 只要求 `2/3` 覆盖且不看方向；`frame=2911` 中 `ml.y=117 >= m0.y=109` 仍发布 `guide=18.31`，Image #4 中 `mid=8` 仍发布 `guide=25.21/yaw=1500`。 | 只在普通帧发布门加入完整前方预瞄检查；不改 `build_rptsn()` 归一化，不改选边，不改控制公式。 | `frame=2911` 是后方预瞄风险；Image #4 是短预瞄强控制风险。普通帧没有元素短线特权，必须有完整且在前方的预瞄目标。 | 失败时返回 `TRACK_REJECT_NO_MIDLINE`，不复用旧中线、旧 `guide_error`、旧 duty，不合成点，也不改变 ring/cross 状态。验证：`git diff --check`、`bash code/test.sh --host`、`bash code/test.sh` 通过。 |

未解决项仍保持独立：

- `frame=2564/3570/4597` 的 `seed=-1 trace=0` 无几何问题没有被这刀解决。
- `frame=1454/1455/2563/4596` 的强 `guide` 控制风险没有被宣称解决。
- `y=34` 仍需确认到底是 raw 行、点数、距离阈值还是未打印的 farthest 字段。

## 已落第二刀：`rej=3/4` 的当前帧证据保留

这不是控制修正，而是为了让下一次日志能定位真正 owner。

算法判断：

- 旧日志里 `seed=(-1,-1)-(-1,-1) trace=0/0` 不一定表示 `find_seeds()` 完全没找到。当前 `trace_edges()` 会在身份拒绝后清空对应 seed/trace，所以日志只看到了过滤后的结果。
- Image #9 里 `frame=4815 line=0 rej=3 seed=(-1,-1)-(-1,-1) trace=0/0 idrej=2` 同时出现，强烈提示“有过当前帧证据，但被身份门清掉”的可能。
- Image #3/#4 里 `rej=4` 但 seed/trace 仍有值，说明还有一类是“有线但中线/预瞄发布失败”。
- 因此第二刀先补证据，不放宽 seed、trace、identity、ring，也不发布旧控制。

代码改动：

- `code/types.hpp::track_result_t` 增加帧首 ring 状态、`find_seeds()` 后 seed、身份过滤前 trace 步数诊断字段。
- `code/tracking/mainline.cpp` 在帧开始时写入 `control_ref`、`action_ring_kind0/action_ring_state0`，修正早退日志里 `xst=...@0,0` 的诊断缺口。
- `code/tracking/mainline.cpp::trace_edges()` 在身份过滤清空 trace 前记录 `trace_left_raw_step/trace_right_raw_step`。
- `code/app/report.cpp`、`code/app/runners.cpp` 输出 `r0=` 和 `pre=`：
  - `ring=` 仍表示处理后的当前状态；
  - `r0=` 表示本帧动作判定前的 ring 状态；
  - `seed=`、`trace=` 仍表示过滤后的结果；
  - `pre=state:(left)-(right)/left_raw/right_raw` 表示 `find_seeds()` 后与身份过滤前的当前帧证据。
- `reset_frame_tracking_state()` 同步清 `seed_state`，避免失败帧继承上一帧 bit 造成诊断污染。

固定 rationale table：

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `main.c:532-587` 每帧重新产生当前 `ipts/rpts/rptsc`；`main.c:447-449` 点不足就不控制。参考版没有同名日志字段，但主合同是当前帧证据归零必须可见。 | 当前日志只打印身份过滤后的 `seed/trace`，`rej=3 seed=-1 trace=0` 无法区分“真没搜到”和“搜到后被身份门清掉”；早退帧 `control_ref` 也可能显示 `0,0`。 | 只增加 `pre=`/`r0=`/key-value report 诊断字段，并在清空前记录当前帧 seed/trace；同时清零 `seed_state`。 | `frame=2564/3570/4815` 类问题下一刀必须知道 owner：seed 搜索、trace 身份过滤、ring 选边裁剪、还是 publish 中线门。没有这个字段会继续猜。 | 不改变 `track_type`、`guide_error`、`midline`、`ring_process()`、seed 搜索策略或 identity gate；失败仍失败，不复用旧中线/旧 duty。验证：`git diff --check`、`bash code/test.sh --host`、`bash code/test.sh` 通过。 |

第二刀后下一次日志判读规则：

- `pre=0:(-1,-1)-(-1,-1)/0/0` 且 `rej=1`：真无 seed，优先查起搜中心、图像阈值和 `find_seeds()` 搜索范围。
- `pre!=0` 但最终 `seed=(-1,-1)-(-1,-1) trace=0/0` 且 `rej=3`：当前帧证据被 trace/identity 过滤清掉，优先查 `idrej` 和 raw trace 范围。
- `pre` 有值、最终 `trace` 有值但 `rej=4`：有线但发布失败，优先查 `mid`、lookahead、前方性和短中线门。
- `r0` 与 `ring` 不一致：本帧元素状态发生切换，必须按帧首动作合同分析，不能把 post-state 误当成控制选择依据。

## 已落第三刀：上位机显示线点默认降采样

这不是 tracking 行为补丁，只影响逐飞助手显示线的发送点数。

事实判断：

- 截图中上位机显示 `FPS: 10`，字节数/秒约 `174092` 到 `197818`。
- 160x120 灰度图本体每帧约 19200 字节，10 FPS 本身就接近 192000 字节/秒；所以 FPS 主要由图像帧发送频率和灰度图本体决定，三条线点数不是主因。
- 但用户明确接受“回传显示的边线点可以少一点”，减少 overlay 点数能降低显示线负担，也能让画面更轻一点，不影响算法本体。

代码改动：

- `code/app/assistant.cpp` 增加固定本地常量 `k_display_point_stride = 2`。
- `copy_pts()` 和 `control_mid_pts()` 只对发送到上位机的黄/红/绿线做 `i += 2` 隔点采样；没有运行时配置、没有端点补齐。
- `rt->track.mid`、`boundary.original_pts`、`trace`、`guide_error`、`duty` 均不变。

固定 rationale table：

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| 无 RT1064 tracking 参考等价；这是上位机显示/传输层，不参与参考版控制链。 | 当前 assistant 三条线最多各 160 点，协议共用 `dot_num=max(n0,n1,n2)`，短线还会 pad 到同长度。 | 只在 `assistant.cpp` 的显示发送前固定隔点拷贝，stride=2，不加配置机制。 | 响应“显示点可以少一点”，降低 overlay 点负担；同时明确 FPS 主负载仍是 160x120 图像本体。 | 只读 `runtime_t`，不改 tracking/control 状态，不改变 `track_line_found()`、`guide_error`、`target_yaw` 或 duty。验证：`git diff --check`、`bash code/test.sh --host`、`bash code/test.sh` 通过。 |

显示层后续如果要真提 FPS：

- 先不要继续改 tracking。
- 如果网络和上位机能承受，可以单独把 `SMARTCAR_ASSISTANT_DIV` 从默认 20 调低到 10 或运行时用环境变量覆盖；这会增加图像帧发送频率和字节数/秒，不是“减少线点”能单独解决。
- 若要降字节量，需要考虑图像分辨率/压缩/发送频率，这属于单独图传任务。

## 已落第四刀：普通帧搜索中心学习等发布门成功

这不是 ring 修复，也不是单侧身份修复；它是第一刀后的跨帧 acquisition 收紧。

算法判断：

- 第一刀让普通帧必须有完整前方预瞄才发布控制。
- 如果普通帧被该发布门拒绝，却已经提前执行 `update_search_center()`，
  就会出现“当前帧不发控制，但短中线/后方预瞄仍教下一帧起搜中心”的污染。
- 这和历史 `ce65c9d -> e1069df -> d2ccaf0 -> d101ad7` 的方向一致：
  `mid_position/width_base` 是下一帧 acquisition prior，必须越来越晚地由当前帧可靠证据背书。
- 参考版 RT1064 没有动态 `mid_position/width_base`，所以这里不能直接照搬；
  只能按本项目额外状态的风险做更严格的 fail-closed 写回。

代码改动：

- `code/tracking/mainline.cpp` 中，帧首普通帧不再在 `mid_ok >= k_min_border_step` 后立即学习。
- 现在普通帧必须先通过 `publish_track_result()`，再 `update_search_center(rt, 1)`。
- 帧首已在 cross/ring 的帧仍保持早期 `update_search_center(rt, 0)`，不更新 `width_base`。
- 不改 `publish_track_result()` 内部逻辑，不改 `midline_has_forward_lookahead()`，不改 ring/cross 状态机。

固定 rationale table：

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `main.c:532-587` 每帧从固定左右起点重建线，没有动态 `mid_position/width_base`。`main.c:381-410` 只有 selected centerline 成立后才计算当前控制误差。 | 当前项目保留 Front_Car 式动态搜索中心；第一刀新增普通帧完整前方预瞄门后，失败帧可能不发控制但仍提前写下一帧搜索中心。 | 只把帧首普通帧的 `update_search_center(rt, 1)` 移到 `publish_track_result()` 成功之后。 | `frame=2911` 后方预瞄、Image #4 短预瞄这类失败几何不应影响下一帧 seed acquisition。 | 失败帧仍返回失败，不复用旧中线/旧 guide/旧 duty，不合成对侧线，不加单侧硬拒；只是拒绝把失败几何写入跨帧 acquisition prior。 |

第四刀仍不解决：

- `frame=2564/3570/4597` 的 `rej=3 seed=-1 trace=0` 根因。
- ring RUN/END 是否裁剪导致 `rej=4`。
- 单侧错误身份但已经能完整前方发布的更强坏例。

## 已落第五刀：ring/cross 裁剪与 selected midline 诊断

这不是 ring 裁剪策略修复，也不是中线发布策略修复；它只补下一轮日志解释力。

四审计结论：

- 参考合同：RT1064 `circle.c` 的 RUN 阶段会选外侧线，并在发现外侧 L 后裁到 L 点；`main.c` 的主合同是点数不足不控制。参考版没有同名 `xcrop` 日志字段。
- 当前实现：`snapshot_ring_frame_start_action()` 把 RUN 裁剪 side/index 保存在局部 `frame_action_t`，`apply_frame_start_element_crop()` 才真正裁 `rptsc0_num/rptsc1_num`，旧日志看不到裁剪前后点数。
- Git 回归：不能恢复 Unity `pending/AIB/BW/ring_times`，也不能把 search center 学习移回 identity/IPM 检查之前。
- Trellis gate：这刀只能是 diagnostic-only；live changed-state 只能放 coarse bucket，不能把 raw count/index 放进去刷屏/beep。

代码改动：

- `code/types.hpp::track_result_t` 增加 `candidate_crop_side/index`、`candidate_left/right_before_crop`、`candidate_left/right_after_crop`、`selected_mid_ok`。
- `code/tracking/mainline.cpp::apply_frame_start_element_crop()` 只记录裁剪前后候选点数；不改任何 `clip_i()` 条件。
- `code/tracking/mainline.cpp::tracking_process_frame()` 在 `build_selected_midline()` 后记录 `selected_mid_ok`。
- `code/app/report.cpp` 输出 `Cand:`、live 单行 `xcrop=`、report key-value；live signature 只加入 positive bucket，不加入 raw 点数。
- `code/app/runners.cpp` 回放单行同步输出 `xcrop=`。

固定 rationale table：

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `circle.c` RUN 阶段选外侧线并在外侧 L 点后裁线；RT1064 `main.c:447-449` 点数不足则不控制。参考版没有同名日志字段。 | 当前 `ring_frame_start_crop_side/index` 只存在于局部 `frame_action_t`，`rptsc0_num/rptsc1_num` 裁剪前后也不出日志；`rej=4` 无法区分“候选原本短”“RUN 裁剪裁短”“build_rptsn 输出短”“普通前方预瞄拒绝”。 | 只把候选裁剪 side/index、裁剪前后点数、`selected_mid_ok` 写进 `track_result_t`、detail/live/replay/report。 | 下一轮需要定位 V05/Image #7 这类有 seed/trace 但 `line=0/rej=4` 的 owner，先拿证据再决定是否改 ring crop 或 selected midline。 | 不改变 `rptsc0_num/rptsc1_num` 计算，不改变 crop 条件，不改变 `track_type`、`guide_error`、`publish_track_result()`、ring/cross 状态机；失败仍失败。当前验证：`git diff --check`、`bash code/test.sh --host`、`bash code/test.sh` 通过。 |

第五刀后下一次日志判读规则：

- `xcrop=side/index/b0/b1/a0/a1/smid` 中 `b*` 有点而 `a*` 变很小：优先查 ring RUN 或 cross near 裁剪 owner。
- `a*` 足够但 `smid` 很小：优先查 `build_rptsn()` 最近点归一化和候选点序。
- `smid` 足够但 `rej=4`：优先查普通帧完整前方预瞄门；元素态则查 `k_element_min_mid_step` 和实际选边。
- `xcrop=0/-1/...` 且 `mode_ring_active=0`：不要把该帧归因到 ring RUN 裁剪。

## 已落第六刀：元素帧搜索中心也等发布成功

这是真算法改动，但仍只改跨帧 acquisition 学习，不改 ring/cross 状态机、裁剪、选边或控制输出公式。

算法判断：

- RT1064 没有动态 `mid_position/width_base`，每帧从固定起点重建边界；因此没有直接等价迁移。
- RT1064 的参考原则是：ring/cross 可以改 `track_type`、裁剪候选或使用远线，但最终仍只有中线足够时才进入控制计算；点不足时 `rptsn_num=0`，不控制舵机。
- 当前项目有额外的跨帧搜索中心。如果帧首已在 ring/cross，旧代码会在 `element_process()` 和最终发布前先 `update_search_center(rt, 0)`；这意味着一个最终 `rej=4` 的元素帧仍可能教下一帧 seed 搜索中心。
- V03/V05/Image #7 这类元素阶段 `rej=4`/无线问题已经把 owner 推到元素候选裁剪、selected midline 和发布门；继续让发布失败元素帧学习搜索中心不符合 fail-closed 原则。

代码改动：

- `code/tracking/mainline.cpp` 删除帧首已在 cross/ring 分支里的早期 `update_search_center(rt, 0)`。
- 对帧首已在 cross/ring、且原本会在 seed/trace/IPM 通过后早期学习的帧，先置
  `defer_element_search_center_update=1`，等 `publish_track_result()` 成功后再
  `update_search_center(rt, 0)`。
- 普通帧仍在 `publish_track_result()` 成功后 `update_search_center(rt, 1)`。
- `ordinary_frame0` 仍只由帧首 `action.cross_state0/action.ring_kind0` 决定；因此 `width_base` 仍只允许普通帧低通更新，ring/cross 只更新 `mid_position`。
- `find_seeds()` 失败、trace 失败、IPM 反序失败、CROSS_IN 远线-only 路径仍不学习；不扩大 `d2ccaf0` 以后“IPM 反序拒绝前不学习”的触发域。

固定 rationale table：

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 没有动态 search center；ring/cross 先改 `track_type`/裁剪/远线，最后只有 `begin_id >= 0 && rpts_num - begin_id >= 3` 才生成 `rptsn` 并控制，点不足则 `rptsn_num=0`。 | 当前项目有 `mid_position` 跨帧学习；帧首已在 ring/cross 时旧代码会在最终中线发布前学习，即使后面 `publish_track_result()` 失败。 | 删除元素帧早期学习；只对原本会早期学习的元素帧置 `defer_element_search_center_update`，发布成功后再 `update_search_center(rt, 0)`。普通帧仍成功后 `update_search_center(rt, 1)`。 | 发布失败的元素帧不应控制当前帧，也不应教下一帧 seed acquisition；但成功发布的元素帧仍可让搜索中心跟随，且不更新路宽。 | 不复用旧中线/旧 guide/旧 duty，不合成对侧线，不改 ring/cross 状态机，不加单侧硬拒或宽度/漂移阈值；不让 CROSS_IN farline-only 或 IPM reject 后远线路径新增学习。失败帧仍失败且不学习。 |

第六刀仍不解决：

- 错误身份单侧线如果能成功发布，仍可能学习 `mid_position`；这需要真实日志证明具体身份谓词，不能用本刀伪装解决。
- `frame=3570` 真无 seed/trace 的 owner 仍要靠 `pre=`、`idrej=`、`xcrop=` 新日志分类。
- ring RUN 裁剪是否过早仍未改，只能由下一轮 `xcrop` 证据判断。

第六刀新增日志判读：

- `xlearn=kind/mid_before/mid_after/width_before/width_after`。
- `kind=0` 表示本帧没有 search-center 学习；若 `rej!=0` 却出现 `kind!=0`，就是回归。
- `kind=1` 表示普通帧发布成功后学习，允许 `width_base` 更新。
- `kind=2` 表示帧首已在元素态的 accepted nearline 分支发布成功后学习，`width_base` 不应变化。

本地 smoke：

- `.diag/video_crop_input/t04..t60.png` 和 `.diag/synth/straight_cross_like.png`
  均为失败帧，且 `xlearn/search_update_kind=0`，说明失败帧没有学习。
- 当前缺少真实 already-in-ring/cross 成功发布序列，不能宣称 V03/V05 根因已解决。

## 明确不做

- 不复用旧中线、旧边界、旧 `guide_error`、旧 duty。
- 不因为单侧/no-opposite-anchor 直接硬拒绝普通帧。
- 不把 RT1064 `pure_angle` 移植进当前 differential `guide_error -> target_yaw -> yaw_cmd` 链路。
- 不同时改 tracking、控制、图传刷新率。
- 不把已撤回的 `imgproc.cpp` 未确认草稿视为已批准方案。
- 不用 BEGIN 超时复位、单侧硬拒绝、控制平滑、保留旧输出来快速掩盖现象。

## 第一轮可确认问题

推荐第一轮只确认一个优先级：先围绕“直道硬拐/中线反向”建立视频-日志证据表；刷新率/图传点数作为第二个独立小任务，不和 tracking 行为补丁混做。
