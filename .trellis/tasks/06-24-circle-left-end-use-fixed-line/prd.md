# 左环 END 阶段使用固定拼接线

## 问题
左环 END 阶段选了 `circle_end_left_half`（rptsc0），但左半线在左环出口处只有 14 个点，frame=92 即掉光，30帧后 stall reset。

## 改动
1. `build_circle_spliced_lines()` — LEFT_END 也构建右拼接中心线
2. `select_work_line()` — LEFT_END 走固定线分支（`circle_out_fixed_right`），rptsc0 做 fallback

## 验证
左环跑一圈，确认 LEFT_RUNNING→OUT→END 完整退出，不 stall。

---

## 追加范围:圆环入门误触收紧(2026-06-24, drive28)

### 问题
drive28 失败**不是出环失败**,是**入口误触**:`check_circle()` 在普通弯道/开口处(离真圆环很远)就误触 `CIRCLE_LEFT_BEGIN`(frame=81),随后内侧左线在 frame84-85 短暂丢失、frame86 恢复。旧 `run_circle()` 把 `none_left_line` 和 `Count_dis_Flag` 当成粘性历史证据,线恢复后不清零,导致距离继续累计,最终在 frame223 被 `total_distence>2000` 推进到 `CIRCLE_LEFT_IN`。

drive30 远点真入口证明上一版 `begin_dist < 300` early revoke 方案不成立:frame65 一帧内侧线丢失后触发 `reset_circle_to_none()` + 150 帧重入抑制,frame66 线恢复但后续真实入口窗口被 suppress 错过。**不能一帧早丢线就撤销 BEGIN**。

详见 `research/drive28-entry-false-positive-analysis.md`(含日志证据表、参考合同对比、git 回归、rationale table)。

### 改动
- 删除 `reference_step.c::revoke_idle_circle_begin()` 中被 drive30 证伪的 `begin_dist < 300` early revoke,保留原有"`BEGIN` 太久不丢线"撤回。
- 删除 `circle.c::run_circle()` 中被 drive33 证伪的 `CIRCLE_BEGIN_LINE_RECOVER_COUNT` 恢复清零逻辑。该逻辑会让远点真入口在内侧线仍较长时反复清零 `none_*_line`/`Count_dis_Flag`,导致 BEGIN 长时间不推进并最终 idle revoke。
- 删除被实机证伪的 Joshua 7 条件硬 AND / anti-flicker 硬撤回:`near/id/mono/cont`、`have_*_line >= 2`、`begin_dist < 350` 都不能作为拒绝门。真入口远点、近点、二次短塌缩都可能合法。
- `check_circle()` 保留 ATG 原始入口发现条件,但把入口投票证据从"单个近 Lpt"提升为"同侧近 Lpt + 同侧远 Lpt"双断点。实现上只在 base 命中时调用 `cross_farline_L/R()` 做当前帧远断点探测,并保存/恢复会污染普通巡线的近线计数和 far 状态;只有双断点同时成立才累计 2 帧 vote 进入 `CIRCLE_*_BEGIN`。

### 验证
- `git diff --check`、`bash code/test.sh --host`、`bash code/test.sh`
- 下一趟 live:先确认真入口 drive30/32/34/39 不再被 `EntryReject`、early revoke、恢复清零或 anti-flicker 撤回误杀;再看 drive28 类似弯道的 `ATGCircleEntryBreakpoints` 是否缺远断点,以及后续是否还出现 `LEFT_BEGIN -> LEFT_IN` 链路。
- drive30 远点入口不应再出现 `ATGCircleReset ... lost too early`;frame65 一帧丢线后允许 frame66 恢复继续保持/重判入口。
- 真左环 drive24/26/27 类场景仍能正常 BEGIN→IN。

### 非目标(入口误触这一轮不动)
- 入口误触修复不动 `guide_error -> target_yaw -> yaw_cmd -> duty` 控制链,不接 `pure_angle`。
- 不只改 `Lpt0_rpts0s_id < 35`、`near/id/mono/cont` 或 `CIRCLE_ENTRY_CONFIRM_FRAMES`(会回退 docs/04 P0"圆环进不去",且挡不住持续候选)。
- 不把单帧丢线、恢复次数、near/id、mono/cont 升级成拒绝门,除非下一趟 live 证明某个当前帧几何量稳定区分真假入口。
- 不做 Joshua 9 阶段重构,不引入原图逐行 `Left_Line[H]/Right_Line[H]` 数组。
- 不删除/恢复日志。
- 不把 `pure_angle` 接入控制。

---

## 追加范围:LEFT_END 转不起来(2026-06-24, drive35)

> 已撤回:用户明确确认 `CIRCLE_HEADING_READY_OUT_TO_END_DEG10=2660` 可用,本轮入口误判修复不得继续调出环阈值。以下 drive35/drive36 记录仅保留为历史分析,不作为当前实现要求。

### 问题
drive35 使用 `CIRCLE_END_LPT_EXIT_ID=12` 后,`END->NONE` 只比 id=15 多等约
30 deg10 heading,但 `LEFT_END` 内 guide 从 +3.63 很快穿零到 -6.31,右线消失后一直
转不回正。问题不在 END 退出 ID,而在 `LEFT_OUT->LEFT_END` 交棒过早。

详见 `research/drive35-ready-out-to-end-analysis.md`。

### 改动
保留源码中的 `CIRCLE_END_LPT_EXIT_ID=15`;把
`CIRCLE_HEADING_READY_OUT_TO_END_DEG10` 从 2660 调到 2800,让
OUT/Readyout 固定线多转一段再进入 END。drive36 已验证 2800 不是让 END 首帧变正,
而是让 `END->NONE` 后 2 帧内 guide 回正。

### 验证
- `git diff --check -- atg_reference/Project/CODE/circle.c`
- `bash code/test.sh --host`
- `bash code/test.sh`
- 下一趟 live 看 `LEFT_OUT->LEFT_END heading≈2800`,退出前 guide 是否接近 0,`NONE` 后 1-3 帧是否回正。
