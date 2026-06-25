# drive28/drive30/drive37 圆环入口误触分析(硬门被证伪,改为双断点入口)

日期:2026-06-24
分支:port/atg2022-reference-control
任务:06-24-circle-left-end-use-fixed-line(追加范围:圆环入门误触收紧)

## drive30 修正结论(上一版 300 early revoke 已证伪)

drive30 远点真入口证明上一版"BEGIN 后内侧线在 `begin_dist < 300` 内丢失即假入口"不成立:

```
frame=61  进入 CIRCLE_LEFT_BEGIN, Lpt id=33, begin=16
frame=65  内侧线丢 1 帧, early revoke 触发 reset + 150 帧 reentry suppress
frame=66  左线恢复, Lpt id=32, 但 BEGIN 已被撤销
frame=66-93 Lpt id 继续从 32 下降到 22, 因 suppress 无法重入
```

早丢线本身不是假入口证据。真正问题是 `run_circle()` BEGIN 中 `none_*_line`/`Count_dis_Flag` 是粘性历史证据:短暂丢线恢复后不清零,距离继续累计,最后把普通弯道推进到 IN。但后续实机又证明两类直接补丁都不成立:

- 删除 `reference_step.c::revoke_idle_circle_begin()` 的 `begin_dist < 300` early revoke 分支,保留"`BEGIN` 太久不丢线"撤回。
- 删除被 drive33 证伪的恢复清零方案:`rpts*_num > 30` 时清 `none_*_line` / `Count_dis_Flag` 会让远点真入口一直卡在 BEGIN,最后 idle revoke。
- 删除被真入口二次短塌缩证伪的 anti-flicker 撤回:`have_*_line >= 2 && begin_dist < 350` 会误杀合法入口。
- 删除被 drive26/27/37 证伪的 Joshua 7 条件硬 AND:`near/id/mono/cont` 作为硬门会挡真入口。

## 问题摘要

drive28 失败**不是出环失败**。链路:

```
frame=81  误触 CIRCLE_LEFT_BEGIN(离真圆环很远,刚过第一个开口)
frame=84  内侧左线丢失(near=1, l=0@-1, none_left_line=1), begin_dist=66
frame=86  左线又回来(near=62, l=1@32)  ← 短丢线恢复,应清掉连续丢线证据和距离推进
frame=222 total_distence=2005 > circle_in_distance(2000)
frame=223 被距离门推进 CIRCLE_LEFT_IN(circle=3), 进入固定动作, 错误已发生
```

根因:`check_circle()` 入口太松(单 Lpt + 对侧直道 + 连续 2 帧投票)在普通弯道/开口处误触 BEGIN;随后 `run_circle()` LEFT_BEGIN 把"内侧曾经丢过线"当成永久证据,线恢复后不清 `none_left_line` 和 `Count_dis_Flag`,导致 `total_distence` 持续累计,最终推进 IN。现有的 `revoke_idle_circle_begin()` 只挡"BEGIN 后一直不丢线"(`none_left_line==0 && begin_dist>6000`)的假入口,挡不住"短丢线恢复后历史证据粘住"的 drive28。

## 非问题(本轮不动)

- **不是 `CIRCLE_HEADING_READY_OUT_TO_END_DEG10=2660` 的问题。** drive24(2600)、drive26(2600)、drive27(2650)均已证明 2600~2660 方向能正常穿零出环。本轮 **2660 保持不动**,不再调出环阈值。
- 不是 `guide_error -> target_yaw -> yaw_cmd -> duty` 控制链问题。
- 不是补线/选线问题。

## 日志证据表(审计B,实测,交叉验证手算)

`begin_dist` = `g_circle_begin_dist`(进入 BEGIN 后累计编码器 counts);`first_lost_begin_dist` = 内侧左线**首次**丢失(`none_left_line` 0→≥1)那一帧的 begin_dist。

| drive | 阈值 | BEGIN | entry Lpt id | first_lost frame | **first_lost begin_dist** | IN frame | result |
|---|---|---|---|---|---|---|---|
| drive24 | 2600 | 早 | 24 | 133 | **1243** | 283 | ✅ success |
| drive25 | 2500 | 早 | 23 | 132 | **1199** | 284 | ✅ 入环成功(出环过早) |
| drive26 | 2600 | 早 | 11 | 81 | **631** | 232 | ✅ success |
| drive27 | 2650 | 早 | 7 | 63 | **445** | 213 | ✅ success |
| drive28 | 2660 | frame=81 | 33 | 84 | **66** | 223 | ❌ false-entry |

**真入环内侧丢线距离 631~1243,最小 drive27=445;drive28 仅 66,差一个数量级。**

drive30 更新:真入口远点也可能在早期出现一帧内侧线丢失,所以 `begin_dist < 300` 不能作为撤销依据。drive33/后续真入口更新:恢复清零、二次恢复撤回、near/id/mono/cont 硬 AND 都会误杀真入口。

用户提出的“双断点”方向更贴合 ATG 现有机理:ATG 已有 `cross_farline_L/R()` 通过近端 Lpt 往上找同侧远端边线和远 Lpt;`round.c::check_round_L/R()` 注释也明确把"同侧近 Lpt + 同侧远 Lpt"作为环形/车库类结构证据。drive28/drive30 在入口触发帧的近端单 Lpt 几乎一样,所以仅靠近 Lpt 单帧不可区分;双断点把入口证据从"一个近角点"提升为"同侧两个角点结构"。

## 为什么不只改 `id<35` 或 `vote=2`

- **单纯 `Lpt0_rpts0s_id < 35` 改 `<30`**:drive28 entry Lpt id=33,改 30 只把 frame81 误触延后到约 frame92,因为同段弯道后续 Lpt 会继续掉到 29/28/27,挡不住。
- **单纯 `CIRCLE_ENTRY_CONFIRM_FRAMES` 从 2 改 3**:drive28 候选持续很多帧,投票门照样满足。
- 这两个阈值历史上(`eac413d` 06-19)正是为解决"圆环进不去"(docs/04 P0)才从 `<25` 放宽到 `<35`;再收紧会回退 P0。
- 不能把 `near/id/mono/cont` 或 "第 2 次塌缩恢复" 作为硬拒绝门:drive26/27 的 `near/id` 本来就小,drive37 出现长期 `EntryReject`,真入口也可能出现两次短塌缩恢复。

## 当前 owner

- `atg_reference/Project/CODE/circle.c::check_circle()` — 入口判定(单 Lpt + 对侧直道 + vote≥2)
- `atg_reference/Project/CODE/circle.c::run_circle()` LEFT_BEGIN/RIGHT_BEGIN — 内侧丢线计数(`none_left_line`/`none_right_line`)+ `total_distence>2000` 距离门推进 IN
- `atg_reference/port/reference_step.c::revoke_idle_circle_begin()` — 现有假入口撤销(仅"不丢线"对偶);`g_circle_begin_dist` 维护在 `update_distance_counters()`;`reset_circle_to_none()` 已含 `suppress_circle_reentry_after_exit()`(150 帧)

## 参考合同对比(审计A)

| 维度 | Joshua.Xu Island.c 左环入口 | 当前 ATG port |
|---|---|---|
| 判据 | 9 条件 AND 门 + 角点终确认 | 单 Lpt + 对侧直道 + 连续 2 帧投票 |
| 丢线范围 | `Left_Lost_Time ∈ [10,50]`(有上下界) | 仅要求发生丢线事件 + 距离推进,无"太早丢线"拒绝 |
| 误判处理 | 角点位置不合理立即 `Island_State=0`(矛盾即归零) | 无 BEGIN 内"过早丢线"撤回 |

**Joshua 入口强调"组合视觉证据 + 丢线范围约束 + 误判归零",不是单角点持续投票。** 但 ATG 当前可用信号不足以把 Joshua 7 条件直接做成硬 AND。硬移植已被实机证伪,本轮只保留候选期观测,不再用这些观测项拒绝入口。

## 修复方案

当前修复目标不是再叠 Joshua 硬门,而是先撤掉已证伪的死门,恢复真入口能力,并用 ATG 自己的 farline 机制补入口结构证据。

- `check_circle()` 保留 ATG 原 base:`Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 35` / 对称右环。
- base 命中时,调用 `cross_farline_L/R()` 探测同侧远 Lpt;由于该函数会截断 `rpts*s_num/rptsc*_num` 并改写 far 全局,入口探测必须保存/恢复现场,不能污染普通巡线。
- 只有"近 Lpt + 同侧 far Lpt"双断点同时成立才累计 `CIRCLE_ENTRY_CONFIRM_FRAMES=2` 投票并进入 `CIRCLE_*_BEGIN`。
- 打印 `ATGCircleEntryBreakpoints: side near far far_len`,供下一趟 live 判断 drive28 类假入口是否缺远断点。
- `run_circle()` BEGIN->IN 恢复为不清 `none_*_line` 的原语义,避免 drive33 的 "永远进不去"。
- `reference_step.c::revoke_idle_circle_begin()` 只保留原有 "`BEGIN` 后 >1m 仍无丢线证据" 撤回。

## critical audit rationale table

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
|---|---|---|---|---|
| ATG `round.c::check_round_L/R` 已使用 `cross_farline_L/R` 从近 Lpt 找同侧远 Lpt,把同侧双 Lpt 当强结构证据;`circle.c` 当前入口只看近 Lpt + 对侧直道 | `check_circle()` 仅单近 Lpt 连续 2 帧即可 BEGIN,drive28 普通弯道能满足;Claude 版 `near/id/mono/cont` 硬门、`begin_dist<300` early revoke、恢复清零、`have>=2` flicker 撤回分别被 drive26/27/30/33/37/后续真入口证伪 | `circle.c::check_circle()` base 命中后增加同侧 far Lpt 探测,双断点成立才投票;同时删 `CIRCLE_BEGIN_LINE_RECOVER_COUNT` 清零逻辑 | 同侧近/远两个断点是当前帧结构证据,比单近 Lpt 更接近入口形态;只在 base 命中时计算,不改变出环阈值和控制链 | `cross_farline_L/R` 是当前帧图像重算;探测前后保存/恢复会污染普通巡线的状态,不复用旧线、不伪造线;下一趟 live 用 `ATGCircleEntryBreakpoints` 验证真假入口差异 |

## git 回归背景(审计C)

- `f15b77b`(06-13)收紧+加安全网(entry_vote、stall reset、BEGIN idle revoke)
- `eac413d`(06-19)**放宽入口** `id<25 → <35`,解决"圆环进不去"
- `39471b7`(06-21)收紧 BEGIN→IN(丢线确认 `>=2`、idle revoke `24000→6000`)
- `75a2b1e`(06-22)加 150 帧 reentry suppression

结论:入口放宽是历史上为解决 P0"圆环进不去"引入的,drive28 暴露其在特定弯道几何下的副作用。drive30/33/37 进一步证明不能靠"过早丢线"、恢复清零、Joshua 静态硬 AND 或二次 flicker 撤回来修。本轮保留 ATG 发现能力,把入口证据从单近 Lpt 提升为同侧近/远双断点。

## 验证(待跑)

1. `git diff --check`
2. `bash code/test.sh --host`
3. `bash code/test.sh`(cross build)
4. 下一趟 live 看:真入口不再出现 `ATGCircleEntryReject` / `lost too early` / 恢复清零卡 BEGIN / flicker reset;drive28 类似弯道是否缺同侧 far Lpt、是否仍推进 LEFT_IN。观察 `ATGCircleEntryBreakpoints`、begin_dist、circle_cnt、dist、reason、sel、near、l id。
