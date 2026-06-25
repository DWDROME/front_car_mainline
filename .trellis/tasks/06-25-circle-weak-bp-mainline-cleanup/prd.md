# circle 弱双断点主线收敛与语义清理

## Goal

把当前 `circle.c` 主线先研究透、命名讲清,再做第一步零行为语义清理。目标不是继续叠入口/出环机制,而是降低后续调试的混乱度:哪些是入口证据、哪些是状态推进、哪些只是历史残留,必须在代码和日志里表达清楚。

## What I Already Know

- 当前入口主线不是完整"双断点",而是 `Lpt + 对侧直 + 内侧 raw 黑点 hit` 的弱几何确认。
- `BEGIN -> IN` 不应再插双断点或 flicker 逻辑;双断点属于 `check_circle()` 入口几何,不是状态推进。
- `CIRCLE_BEGIN_LINE_RECOVER_COUNT` 恢复清零逻辑已移除;当前 `none_*_line` 不再因线恢复而清零。
- `Count_dis_Flag==1` 才累计 `total_distence`,否则清零;BEGIN 阶段 `total_distence` 实际是从首次内侧丢线起算的 lost distance。
- `g_circle_begin_dist` 才是 BEGIN 后累计距离,用于 idle revoke。
- 左环 END 的 `src=14 circle_end_fixed_right` 在 drive59/60/61/62 中方向正确;问题在过早退到 `CIRCLE_NONE` 后普通巡线 guide 变负或归零。
- 用户要求保持 `CIRCLE_HEADING_READY_OUT_TO_END_DEG10=2660`,不改控制链,不接 `pure_angle`。

## Requirements

- 先完成 `circle.c` 主线研究文档,再进入第一阶段语义清理。
- 第一阶段只做语义清理,不改变任何状态判断结果。
- 清理 `circle.c` 命名和死代码时必须一项一项验证,避免夹带行为变化。
- 入口日志若改名,函数内两个 `ATGCircleEntryBreakpoints` 输出点必须同步改。
- 未使用的 `CIRCLE_HEADING_FORCE_OUT_DEG10=2500` 可删除。
- `circle_encoder` 只赋值无消费,可以作为残留项清理或标明。
- `OUT->END` 的 `4500`,左 END `7500`,右 END `4000` 应提成 enum 常量,数值不变。
- 右环诊断日志可以补齐,但不能改变右环条件。
- 文档必须保留当前事实:左右 BEGIN 阈值不同、左右 END 门不同、大小环当前无控制消费、`broadcast_flag/if_clean_pid` 当前不是实车控制主链。

## Acceptance Criteria

- [ ] `atg_reference/CIRCLE_DEEPDIVE.md` 覆盖 1→7 盲区:距离语义、副作用消费链、cross_farline、heading、inner_hit、异常路径、大小环。
- [ ] 第一阶段代码 diff 只包含改名、删死常量/残留、提常量、诊断日志,不包含条件数值或判断顺序改变。
- [ ] `git diff --check` 通过。
- [ ] `bash code/test.sh --host` 通过。
- [ ] `bash code/test.sh` 通过。
- [ ] 若上车验证,同一日志状态流应与清理前一致;若只编译验证,最终回复必须说明未做实机等价对比。

## Out of Scope

- 不改 `CIRCLE_HEADING_READY_OUT_TO_END_DEG10=2660`。
- 不改 `guide_error -> target_yaw -> yaw_cmd -> duty`。
- 不把 `pure_angle` 接入控制。
- 不新增 BEGIN flicker / early revoke / Joshua 7 条件 AND 门。
- 不删除 live logs。
- 不把右环 END 行为强行对齐左环;右环统一放到后续行为任务。
- 不在"语义清理"阶段改入口、IN、RUNNING、OUT、END 的状态推进逻辑。

## Technical Approach

采用两阶段:

1. **研究/文档阶段**:把 `circle.c` 与 `reference_step.c` 的状态、距离、选线、撤回、控制边界写清楚。研究结论只描述现状,不夹带行为修改。
2. **零行为清理阶段**:只改语义表达和死代码/常量组织。每个改动都必须能通过 diff 证明不改变判断条件、不改变阈值数值、不改变状态推进顺序。

执行第一阶段代码清理时,每项改动前后都用 `rg` 或 diff 核验引用面,最后跑:

```bash
git diff --check
bash code/test.sh --host
bash code/test.sh
```

若做实机等价验证,对比清理前后同一 replay/log 的状态流;若未做实机,交付时必须明确说明。

## Decision (ADR-lite)

**Context**: 最近多轮圆环调试把入口误判、BEGIN 推进、OUT/END 交棒、控制链、历史标志混在一起,导致修复不断叠机制且难以归因。

**Decision**: 本任务把"弱双断点/inner-hit 入口主线 + 零行为语义清理"定为唯一第一步。先清名称、死代码、散落常量和诊断语义,不再在第一步修改状态机行为。

**Consequences**: 第一阶段不会直接解决实车出环问题,但会把可调边界变清楚。后续若要改右环 END、src14 释放或入口几何,必须作为新的行为任务,带日志证据和验证。

## Research References

- [`research/circle-deepdive-1-7.md`](research/circle-deepdive-1-7.md) — 1->7 深挖结论摘要。
- [`../../../atg_reference/CIRCLE_DEEPDIVE.md`](../../../atg_reference/CIRCLE_DEEPDIVE.md) — 长文档,逐状态和逐衔接点说明。

## Implementation Plan

1. **PR1: 研究定稿**
   - 校正 `CIRCLE_DEEPDIVE.md` 中副作用标志、距离时序、inner-hit 与 farline 的边界表述。
   - 保持代码行为不变。
2. **PR2: 零行为语义清理**
   - 改入口日志名两处。
   - 删除未引用 heading 常量。
   - 清理或标明 `circle_encoder` 残留。
   - 提取 `4500/7500/4000` enum 常量,数值不变。
   - 可补右环诊断日志,但不改右环条件。
3. **PR3: 行为任务另开**
   - 如需处理 src14 释放、右环 END 对称、入口几何加强,单独建行为任务并用 live log/replay 证明。

## Technical Notes

- 主文档: `atg_reference/CIRCLE_DEEPDIVE.md`。
- 代码主线: `atg_reference/Project/CODE/circle.c`, `atg_reference/port/reference_step.c`。
- 控制边界: `code/tracking/atg_reference_mainline.cpp`, `code/app/runners.cpp`, `code/core/control.cpp`。
- 入口几何日志当前名: `ATGCircleEntryBreakpoints`,实际含义更接近 `EntryInnerHit`。
- 当前有效实车控制链:
  - `circle_type -> select_work_line/src -> rptsn -> atg_lookahead_error() -> guide_error`
  - `circle_type != NONE -> element_active -> element_target_rps`
