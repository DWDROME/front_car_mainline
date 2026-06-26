# 圆环状态重构：NONE→ENTRY→BEGIN→RUNNING→OUT 状态链

## Goal

重构 `circle.c` 的圆环入口状态机，把“疑似入口”和“确认入口”分离：`NONE` 只识别 A 入口迹象并进入 `ENTRY`，`ENTRY` 使用 A 对应 `seed_line_x` 生成预测线找 B seed，再基础搜线验证 B；B ready 连续成立后进入 `BEGIN`，`BEGIN` 不再检查双断点，只使用 B 对应预测线恢复远端边界并确认 C，随后按 heading 进入 `RUNNING`，最后 `OUT` 交棒回普通巡线。不增加 `IN` 状态。

## What I Already Know

* 用户明确不打算增加 `IN` 状态。
* 目标状态链是 `NONE -> ENTRY -> BEGIN -> RUNNING -> OUT -> NONE`，左右环对称。
* 旧问题：`A + 对侧直道 + inner_hit + 连续帧` 直接进入 `BEGIN`，导致 BEGIN 过早。
* 期望：旧 BEGIN 条件变成新 ENTRY 条件；真正的 BEGIN 条件变成 B 有效。
* `ENTRY` 需要锁存进入该状态时的 A raw 坐标，用于记录入口证据、约束 A-B 几何，并维护 A 对应的 `seed_line_x` 来生成 B 预测线。
* “锁存 A”只表示保存第一次命中的入口种子，不表示冻结视觉点；A 自身仍会继续变化。
* `seed_line_x` 不是 A 的一次性固定值，而是“当前固定点”导出的横向锚点状态。A 固定过，B 也会固定过；但状态机真正消费的是当前固定点对应的 `seed_line_x`。`ENTRY` 期间当前固定点始终是 A：A 可见时跟随当前 A 更新，A 到近端客观丢失后保持最后一次 A 值。只有 `ENTRY -> BEGIN` 成立的瞬间，当前固定点才切到 B，并同步用 `B.x + signed_offset` 给 `seed_line_x` 赋值。BEGIN 后 B 随后客观丢失时，保持最后一次 B 赋值后的 `seed_line_x`。
* A/B/C 的几何语义已重新确认：A 是入口近端尖锐点；B 是基础搜线识别到的环岛中心圆/圆弧边界上的横向极值点，不是尖点；C 是 B 后再次断线、再恢复远端边界后出现的尖锐点，语义上与 A 同类。
* B/C 的搜索都应复用现有基础搜线能力，且都通过当前固定点对应的 `seed_line_x` 生成预测线来跨断线找 seed：B 使用 A 对应的预测线，C 使用 B 对应的预测线。
* 双断点只服务 `ENTRY -> BEGIN`，但其状态语义不是“当前帧 A 仍可见”。A 是 `NONE -> ENTRY` 阶段确认并锁存过的入口尖锐点，B 是 `ENTRY` 阶段当前基础搜线确认的中心圆/圆弧边界极值点；真正推进到 `BEGIN` 的首要因素是 B ready 连续成立。
* 预测线用于跨断线找下一个固定点：ENTRY 中用 A 对应的 `seed_line_x` 生成预测线找 B；进入 BEGIN 的瞬间切到 B 并同步更新 `seed_line_x`；BEGIN 中再用 B 对应的 `seed_line_x` 生成预测线找 C。进入 BEGIN 时已经放弃 A，BEGIN 只消费最近稳定 B/上一帧 B 和 B 对应的 `seed_line_x`。右环按左右镜像处理。
* 第一版保留 `CIRCLE_REF_IN_C`，但改变其置位来源：只有 C 点由基础搜线点列尖锐判据确认后才允许置位；`reference_step.c` 继续用该模式生成/选择 C 拉线，避免本任务同时重写消费端 contract。
* 用户倾向把圆环入口前置识别抽成独立分类函数，`circle_entry_basic()` 可能删除，保留一个更清晰的 `road_class_detect()` / 场景分类入口。

## Current Code Notes

* `atg_reference/Project/CODE/circle.h` 当前枚举只有 `CIRCLE_NONE`、左右 `BEGIN`、左右 `RUNNING`、左右 `OUT`。
* `atg_reference/Project/CODE/circle.c` 当前 `check_circle()` 在 `circle_entry_votes[side] >= CIRCLE_ENTRY_CONFIRM_FRAMES` 后直接设置 `CIRCLE_LEFT_BEGIN` / `CIRCLE_RIGHT_BEGIN`。
* 当前 `circle_entry_candidate()` 已经在 `NONE` 阶段同时检查 A/basic 条件和 `circle_find_B()`，这与“ENTRY 中验证 B”的目标不一致。
* 当前 `run_circle_begin()` 每帧从当前 A 重新 `circle_find_B()`，再 gate C；这与“BEGIN 后不再依赖 A”的目标不一致。
* 当前已有 `ATGCircleEntryProbe`、`ATGCircleEntryAB`、`ATGCircleABC` 日志基础，但 ENTRY 专属 B 失败原因和 `B_reach_row` 还需要按新状态补齐。
* 当前 `circle_find_B()` 是 raw 图像窗口横扫，不是基础搜线；新方案要求删除这种 B 横扫语义，改为“A 对应预测线找 seed -> 基础搜线 -> 点列取 B”。
* 当前 `circle_find_C()` 只做相对 B 的横向跳变判据，不足以证明 C 是尖锐点；新方案要求 C 来自断线后恢复边界点列上的尖锐/角点判据。

## Requirements (Evolving)

* 增加左右 `ENTRY` 状态，不增加 `IN` 状态。
* `NONE` 只负责识别疑似圆环入口并锁存 A，不应在同一阶段确认 B。
* `circle_entry_detect(side, &A)` 只做 A/basic 前门判断，不包含 `inner_hit`；`inner_hit` 只保留为实现层内部辅助探针，不列入状态门槛。
* `ENTRY` 负责用 A 对应的 `seed_line_x` 生成预测线，沿预测线寻找 B 的基础搜线 seed，再通过基础搜线确认 B；B ready 连续 2 帧成立后进入 `BEGIN`。当前帧 A 不要求继续有效，A 丢失不清零 B ready 确认计数。A 到近端后丢失是正常几何阶段，但不会切换固定点；`ENTRY` 内当前固定点仍是 A，`seed_line_x` 保持最后一次 A 值用于继续找 B。只有进入 `BEGIN` 的瞬间才放弃 A、切到 B，并同步用 `B.x + signed_offset` 重新赋值 `seed_line_x`。B 尖锐/十字冲突立即退出到 `NONE`。
* `BEGIN` 负责 C 搜索和补线入环；找到 C 后先判断 C 拉线与当前外边线是否接得上，满足接线门槛后才启用 C 拉线，未找到 C 或 C 拉线过远时继续外圈/AB 追踪，heading 达到 `CIRCLE_HEADING_ENTER_DEG10` 后进入 `RUNNING`。
* `BEGIN -> RUNNING` 保留当前 heading 门槛：`CIRCLE_HEADING_ENTER_DEG10 = 600`。
* `RUNNING -> OUT` 和 `OUT -> NONE` 第一版沿用现有规则，不在本任务重构出环链路。
* 入环是本任务最高风险点：状态链确定后，还需要明确 ENTRY/BEGIN 期间的参考线连续性、B/C 锚点有效性，以及 A 消失后的处理策略。
* `RUNNING` 和 `OUT` 的现有 heading/视觉出环链路原则上保持，只在状态枚举和重置语义需要时做最小调整。
* 新状态机必须保持当前帧证据优先，不能用隐藏 fallback 或 stale geometry 掩盖 B/C 搜索失败。
* 圆环入口的前置分类可以抽成单独函数，但它应服务于圆环入口状态机，不应无边界地扩展成全局道路等级真相源。
* `circle_entry_detect(side, &A)` 替代 `circle_entry_basic()`，只判断当前帧是否具备圆环 ENTRY 的 A/basic 迹象，不负责 B 确认，也不负责 `inner_hit`。
* `NONE` 阶段第一次 `circle_entry_detect()` 命中时立即锁存 A seed；连续 2 帧命中后进入 `ENTRY`，并继续使用第一次命中的锁存 A。
* `ENTRY -> BEGIN` 采用 B ready 作为主门槛：B 可以单帧有效地维持 ENTRY，但只有当 B 到达入口行并连续 2 帧成立时才进入 BEGIN；当前 A 是否仍可见不参与该确认计数。
* B 搜索必须走基础搜线：由 A 对应的 `seed_line_x + 对称斜率` 生成预测线，在预测线上找基础搜线起点，调用现有 `findline_lefthand_adaptive()` / `findline_righthand_adaptive()` 得到中心圆边界点列，再在合法区域内选 B。
* B 选点规则：左环在合法 B 区域内取 x 最大点，右环取 x 最小点；合法区域继续复用现有 A-B 几何约束，包括 `dy`、`inner_dx`、`dist2`、搜索纵向范围和走势连续性。
* C 搜索必须走“B 后断线恢复”：BEGIN 中使用 B 对应的 `seed_line_x + 对称斜率` 生成预测线寻找远端边界 seed，再调用基础搜线得到远端边界点列；C 必须由该点列上的尖锐/角点判据确认。最近稳定 B 可用于限定搜索段和几何顺序，不负责生成主斜率。
* 预测线不是控制拉线，也不是最终补线；它只用于跨断线寻找基础搜线 seed：ENTRY 用 A 对应预测线找 B，BEGIN 用 B 对应预测线找 C。
* 预测线生成规则：`seed_line_x` 由当前固定点导出。ENTRY 内当前固定点是 A，A 可见时跟随 A 更新，A 到近端丢失后保持最后一次 A 值；`ENTRY -> BEGIN` 成立的瞬间，当前固定点切到 B，并同步执行 `seed_line_x = B.x + CIRCLE_SEED_LINE_B_OFFSET_X`，偏移量按左右环镜像取有符号值；BEGIN 内 B 随后丢失时保持最后一次 B 赋值。斜率来自右侧边线的中心对称直线斜率。该规则不能改回固定竖线或 raw 全窗口横扫。

## Trigger Contract

* `NONE -> ENTRY`：
  - 只确认疑似圆环入口 A/basic 成立，不要求 B 可见，不在 `NONE` 中搜索或确认 B。
  - 第一次 `circle_entry_detect(side, &A)` 命中时锁存 pending A seed；连续 `CIRCLE_ENTRY_CONFIRM_FRAMES` 帧命中后进入对应 `ENTRY`。
  - 触发条件包括：A found、`A_id < CIRCLE_ENTRY_A_ID_MAX`、`A.raw_y <= 100`、对侧 Lpt 不存在、对侧 straight、连续确认帧数满足。
  - `inner_hit` 不属于状态触发条件；它只作为实现层内部辅助探针，最多用于日志、调试或 B 搜索的内部过滤。
  - `seed_line_x` 记录自首次命中的 A seed，进入 `ENTRY` 后持续更新；ENTRY 内当前固定点始终是 A，A 仍可见时 `seed_line_x` 跟随当前 A 更新，A 到近端丢失后保持最后一次 A 值。不得因为 A 丢失就在 ENTRY 内切到 B。
* `ENTRY -> BEGIN`：
  - 首要触发因素是当前帧 B 由基础搜线确认有效并达到 B ready 阈值，连续 2 帧成立。
  - B 必须来自“A 对应预测线找 seed -> 基础搜线 -> 点列取极值”，位于中心圆/圆弧边界点列上，且通过合法 B 区域、A-B 几何约束、点列连续性和非十字冲突检查。
  - A 只要求曾在 `NONE -> ENTRY` 阶段确认并锁存过；当前帧 A 不要求有效，A 丢失不清零 B ready streak。
  - 进入 `BEGIN` 的同时放弃 A，并在这个状态切换瞬间把当前固定点切到 B，同步执行 `seed_line_x = B.x + CIRCLE_SEED_LINE_B_OFFSET_X`。BEGIN 只继承最近稳定 B/上一帧 B 和该 B 对应的 `seed_line_x`。
  - `A+B 双断点`在实现和日志中应解释为“已锁存的 A 入口证据 + 当前 B ready 证据”，不能解释为“当前帧 A 和 B 同时可见”。
* `ENTRY -> NONE`：
  - 明确 false-entry 立即退出：B sharp_far、B 与十字/尖点冲突、基础搜线结果违反 A-B 几何硬约束。
  - 普通单帧 no_b/no_seed/no_extreme 只清 B ready streak，不直接退出。
  - 如果 A 已到近端或已客观丢失，但进入 `ENTRY` 后从未得到有效 B，则退出 `NONE`。A 丢失本身不是退出条件；有稳定 B 时继续维持 ENTRY，直到 B ready 连续成立后在 `ENTRY -> BEGIN` 瞬间切到 B 并给 `seed_line_x` 赋值。
* `BEGIN -> RUNNING`：只看 heading 门槛 `circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)`，当前为 600；BEGIN 内不再检查 A/B 双断点。
* `RUNNING -> OUT` 与 `OUT -> NONE`：第一版沿用现有出环规则，仅做状态枚举和重置语义所需的最小调整。

## Proposed State Tree

```text
CIRCLE_NONE
  action:
    - 普通巡线
    - 每帧调用 circle_entry_detect(side, &A)
    - 第一次 detect 命中时保存 pending A seed
    - 连续 2 帧 detect 命中后进入对应 ENTRY，并使用第一次命中的 A seed 作为锁存 A
  trigger to ENTRY:
    - A found
    - A_id < CIRCLE_ENTRY_A_ID_MAX
    - A.raw_y <= 100
    - 对侧 Lpt 不存在
    - 对侧 straight
    - 连续 CIRCLE_ENTRY_CONFIRM_FRAMES 帧

CIRCLE_LEFT_ENTRY / CIRCLE_RIGHT_ENTRY
  action:
    - 继续贴外侧巡线，不进入 C 补线
    - 不要求双断点
    - 使用 A 对应 `seed_line_x` + 对称斜率生成预测线，并沿预测线寻找基础搜线 seed
    - 调用基础搜线得到中心圆/圆弧边界点列
    - 在点列合法区域内选择 B：左环取 x 最大点，右环取 x 最小点
    - 打印 ENTRY B seed/trace/probe 日志
  trigger to BEGIN:
    - B trace valid
    - B 位于中心圆/圆弧边界点列上，不是 sharp point
    - B ready 门槛满足；第一版可继续使用 raw_y 近端阈值，但语义应从 `CIRCLE_B_ENTER_ROW` 改为 `CIRCLE_B_READY_RAW_Y_MIN`
    - B ready 连续 2 帧成立；当前 A 不要求有效，A 丢失不清零确认计数
  trigger to NONE:
    - B sharp_far
    - B 与十字/尖点冲突，或基础搜线结果违反 A-B 几何硬约束
    - 进入 ENTRY 后一直没有识别到有效 B，且入口搜索窗口耗尽；近端初始参数使用 `A_id <= CIRCLE_ENTRY_A_NEAR_ID`，`CIRCLE_ENTRY_A_NEAR_ID = 8`
    - 必要时可对 no_a/no_b/no_extreme 分原因日志，但不引入候选状态变量

CIRCLE_LEFT_BEGIN / CIRCLE_RIGHT_BEGIN
  action:
    - B 已确认；BEGIN 后放弃 A，不再依赖当前 A，也不再用 A 更新任何几何状态
    - 不再检查双断点；A 只作为 ENTRY 的历史入口证据，B ready 是进入 BEGIN 的主触发
    - 使用 `ENTRY -> BEGIN` 瞬间由 B 赋值的 `seed_line_x` + 右侧线中心对称直线斜率生成预测线；B 丢失后继续保持最后一次 B 赋值
    - 沿预测线寻找断线后远端边界 seed
    - 调用基础搜线恢复远端边界点列
    - 在恢复点列上使用与 A 同类的尖锐/角点判据确认 C
    - C 连续确认后设置 `circle_ref_mode = CIRCLE_REF_IN_C`
    - `reference_step.c` 继续按 `CIRCLE_REF_IN_C` 构建/选择 C 拉线；若后续加入 `CIRCLE_C_JOIN_DX`，应在消费端选择 C 拉线前 gating
    - if(C not found) 继续使用 AB 或外圈追踪
  trigger to RUNNING:
    - circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)，当前为 600
  trigger to NONE:
    - 仅保留明确 false-entry 保险丝，不作为正常推进路径

CIRCLE_LEFT_RUNNING / CIRCLE_RIGHT_RUNNING
  action:
    - 环内巡线，保持现有出环判据
  trigger to OUT:
    - 沿用现有规则：对侧出口 Lpt 近端 + heading gate
    - 沿用现有规则：或 heading 达到 start-out gate

CIRCLE_LEFT_OUT / CIRCLE_RIGHT_OUT
  action:
    - 出环巡线
  trigger to NONE:
    - 沿用现有规则：heading ready + 对侧 straight 连续确认
    - 沿用现有规则：或 heading soft finish
```

## Search Geometry Contract

* raw 图像坐标约定：`y` 越小越远，`y` 越大越近。A/B/C 的纵向顺序必须是 `A.y > B.y > C.y`。
* A：入口近端尖锐点，来自感知层现有同侧 Lpt。A 不由本任务重新搜线。
* B：从 A 出发后，基础搜线识别到的环岛中心圆/圆弧边界上的横向极值点。B 不是尖点，不用尖锐判据确认。
* C：B 后再次断线，沿预测线恢复远端边界后，在恢复点列上出现的尖锐点。C 与 A 同类，需要角点/尖锐判据确认。
* 预测线：只用于跨断线寻找基础搜线起始 seed，不是控制补线，不是最终参考线，不直接作为 B/C 真值。ENTRY 内用 A 对应预测线找 B；BEGIN 内用 B 对应预测线找 C。
* 预测线生成：
  - 触发条件：ENTRY 内 A 入口证据锁存后即可用 A 对应预测线找 B；`ENTRY -> BEGIN` 瞬间切到 B 并赋值后，BEGIN 内用 B 对应预测线找 C。BEGIN 内不再重新检查双断点。
  - 横向位置：`seed_line_x` 总是由当前固定点导出。ENTRY 内当前固定点是 A，A 可见时 `seed_line_x` 跟随当前 A 更新；A 到近端丢失后仍保持最后一次 A 值，不切 B。只有 `ENTRY -> BEGIN` 成立的瞬间，当前固定点才切到 B，并执行 `seed_line_x = B.x + CIRCLE_SEED_LINE_B_OFFSET_X`，偏移量按左右环镜像取有符号值；BEGIN 内 B 丢失后保持最后一次 B 赋值。BEGIN 入口后不再允许 A 重新成为当前固定点。
  - 斜率来源：使用右侧线做中心对称后的直线斜率，保持预测线方向与对侧有效边界一致。右环按左右镜像处理。
  - 使用范围：预测线只为基础搜线找 seed；ENTRY 内使用 A 对应 `seed_line_x` 找 B seed，BEGIN 内使用 B 对应 `seed_line_x` 找 C seed；不能作为状态推进证据，也不能替代基础搜线结果。
* 基础搜线：复用 `findline_lefthand_adaptive()` / `findline_righthand_adaptive()` 生成真实边界点列；B/C 的确认必须基于该点列，而不是 raw 图像固定窗口横扫。
* B 搜索流程：
  1. 以锁存 A 为入口证据，使用 A 对应的 `seed_line_x + 对称斜率` 生成预测线，在预测线上寻找可靠黑点 seed。
  2. 从 seed 调用基础搜线，得到中心圆/圆弧边界点列。
  3. 在点列中筛选合法 B 区域，左环取 x 最大点，右环取 x 最小点。
  4. 使用锁存 A seed 与现有 A-B 几何约束确认 B，包括纵向范围、`inner_dx`、`dist2`、点列连续性和非十字冲突。当前 A 可用于日志或早期退出判断，但不能作为 `ENTRY -> BEGIN` 的必需当前帧证据。
  5. B ready 第一版可用 raw_y 近端阈值对齐日志，但命名为 `CIRCLE_B_READY_RAW_Y_MIN`，不再把它理解为固定扫描行。
  6. B ready 连续 2 帧成立后进入 `BEGIN`；单帧 no_b/no_seed/no_extreme 只清 B ready streak，不直接退出 `ENTRY`。
* C 搜索流程：
  1. 使用 `ENTRY -> BEGIN` 瞬间由 B 赋值的 `seed_line_x` 与右侧线中心对称斜率生成 B 后预测线；BEGIN 入口必须已有最近稳定 B/上一帧 B，因此该 `seed_line_x` 在切换瞬间同步赋值。B 后续可见时可继续由 B 的 x 加有符号偏移更新，B 丢失后保持最后一次 B 赋值。最近稳定 B 可用于限定搜索起止段，但不改变预测线主斜率来源。BEGIN 内不再读取 A 来更新该值。
  2. 沿预测线寻找断线后远端边界 seed。
  3. 从 seed 调用基础搜线恢复远端边界点列。
  4. 对恢复点列执行尖锐判据确认 C：优先复用 `local_angle_points()` / `nms_angle()`；若接口不便，第一版在 `circle.c` 内实现轻量三点转角判据。
  5. C 连续确认后设置 `CIRCLE_REF_IN_C`，由 `reference_step.c` 沿用现有 C 拉线构建和选线逻辑。
* 动态性处理：B/C 坐标每帧由当前基础搜线点列重新计算；状态只短期锁存最近稳定的 B/C anchor 和确认 streak，不把旧 raw 坐标当长期真相源。`seed_line_x` 的维护规则是：ENTRY 内当前固定点是 A，A 可见时跟 A，A 到近端丢失后保持最后一次 A 值；`ENTRY -> BEGIN` 瞬间当前固定点切到 B，并同步用 `B.x + CIRCLE_SEED_LINE_B_OFFSET_X` 赋值；BEGIN 内 B 可见时继续跟 B，B 丢失后保持最后一次 B 赋值。BEGIN 入口后 A 被放弃，最终保留最后一个可用的最小值用于追 C。

## Feasibility Analysis

* 方案合理性：状态机本身已收敛，难点转为 ENTRY/BEGIN 的几何搜索和补线连续性。最小实现应避免全局道路元素真相源，使用 `circle_type` 内部状态表达 `ENTRY` 候选即可。
* 调度可实现：`check_circle()` 只在 `CIRCLE_NONE` 内做 `circle_entry_detect()` 和 A seed 捕获；`run_circle()` 新增 ENTRY 分支处理 B 搜索；BEGIN 分支只处理 C 搜索和入环参考线。这样不会要求 cross/road/yroad 改调度。
* 算力风险可控：B/C 搜索只在 ENTRY/BEGIN 启用；预测线找 seed 的窗口有限，基础搜线已有步数上限，不需要新写全图搜索。
* 最小实现倾向：B/C 都使用基础搜线，不保留当前 raw 固定窗口横扫作为并行 fallback。需要保留的只是日志对照和失败原因，不应引入第二套真相源。
* B 搜索可实现：ENTRY 中不要求双断线，直接由 A 对应 `seed_line_x + 对称斜率` 生成预测线找基础搜线 seed，基础搜线应能识别中心圆整段圆弧；B 从点列合法区域取左环 x 最大/右环 x 最小点，并复用当前 A-B 几何约束。A 到近端丢失后仍不切 B，ENTRY 内继续用最后一次 A 值对应的预测线找 B；只有 `ENTRY -> BEGIN` 瞬间才切到 B 并同步赋值 `seed_line_x`。
* C 搜索可实现：BEGIN 中不再检查双断点；直接用 `ENTRY -> BEGIN` 瞬间由 B 赋值的 `seed_line_x` 和对称斜率生成预测线找远端边界 seed，基础搜线恢复远端边界，再用局部角度变化率/三点转角尖锐判据确认 C。
* `CIRCLE_REF_IN_C` 保留可控：`reference_step.c` 当前依赖该模式构建 `circle_in_c_left/right`，第一版只改变该模式置位条件，不删除枚举和消费端 contract。
* 主要风险：C 预测线小左偏量或对称斜率计算错误，会把基础搜线 seed 带离真实圆环边界；因此日志要输出 seed_line_x、左偏量、对称斜率、预测线端点、C seed、基础搜线点数、C 尖点候选、失败原因。B 日志单独输出 A seed、B seed、基础搜线点数、B 极值点、B ready。
* 非目标：第一版不做全局 `road_class`、不做完整迷宫图搜索、不重构出环。

## Open Questions

以下问题是编码阶段从当前实现和接口中解出的实现细节，不再阻塞状态机设计：

* 右侧线中心对称后的预测线斜率精确计算公式。
* `CIRCLE_SEED_LINE_B_OFFSET_X` 初值及左右环有符号镜像方式。
* `CIRCLE_B_READY_RAW_Y_MIN` 第一版是否沿用旧值 58，还是结合基础搜线点列位置重新标定。
* `local_angle_points()` / `nms_angle()` 角点接口是否可直接复用；若不可用，第一版在 `circle.c` 内实现轻量三点转角判据。

## Acceptance Criteria (Evolving)

* [ ] `circle_type_e` 包含左右 `ENTRY`，没有 `IN`。
* [ ] 旧 entry vote 不再直接进入 `BEGIN`。
* [ ] 第一次 entry detect 命中时锁存 A raw 坐标；锁存 A 用于入口证据、A-B 几何约束和 A 对应 `seed_line_x` 维护。
* [ ] `ENTRY` 阶段 B 搜索不要求双断线，使用“A 对应 `seed_line_x` 预测线找 seed -> 基础搜线 -> 点列取极值 B”，不再使用当前 raw 固定窗口横扫作为 B 真值。
* [ ] `ENTRY` 阶段可单帧维持 B 有效，但只有 B ready 连续 2 帧成立才进入 `BEGIN`；当前 A 不要求有效，A 丢失不清零 B ready streak。
* [ ] `ENTRY` 阶段普通单帧 no_b/no_seed/no_extreme 只清 B ready streak，不直接退出；若一直无法识别有效 B 且入口搜索窗口耗尽，应退出 `NONE`。
* [ ] `ENTRY` 阶段日志能解释 A seed、B seed、基础搜线点数、B 极值点、B 失败原因、是否达到 B ready。
* [ ] `BEGIN` 阶段放弃 A，不再依赖当前 A 作为状态推进或几何更新依据。
* [ ] `BEGIN` 阶段不再检查双断点，直接使用 `ENTRY -> BEGIN` 瞬间由 B 赋值的 `seed_line_x + 右侧线中心对称斜率` 生成预测线，再找 C seed、基础搜线恢复远端边界并用点列尖锐判据确认 C，不再使用当前单行横向跳变作为 C 真值。
* [ ] 第一版保留 `CIRCLE_REF_IN_C`；C 连续确认后置位该模式，`reference_step.c` 继续使用现有 `circle_in_c_left/right` 选线通道。
* [ ] `BEGIN -> RUNNING` 保留 `CIRCLE_HEADING_ENTER_DEG10 = 600` 作为状态切换门槛。
* [x] `circle_find_B()` 已机械拆分为 `find_B_entry()` 和 `follow_B_begin()`，去掉 `follow_mode` 参数，保留原返回语义和日志字段含义。
* [x] `follow_B_begin()` 会在 BEGIN 阶段更新 `circle_B_search_*` 诊断字段，避免 `log_circle_abc()` 打印 ENTRY 阶段旧 B 搜索值。
* [x] `run_circle_entry()` 明确区分 `a_visible` 与 `a_locked`，保持 A 不可见时继续用锁存 A 搜 B 的行为。
* [x] `find_B_entry()`、`follow_B_begin()`、`circle_find_C()` 已按比赛代码流程风格拆成 `B_*` / `C_*` 短动作函数；未新增 context/config/state 结构体，也未引入 B/C 通用搜索器。
* [x] 最小相关编译/检查通过，或记录无法运行的具体原因。

## Definition of Done

* 实现前完成状态机触发条件确认。
* 按 tracking spec 做小而可审查的 diff。
* 改代码后运行最小相关验证。
* 收尾前检查 diff，确认没有隐藏 fallback、第二真相源或无关改动。

## Out of Scope

* 不新增 `IN` 状态。
* 不重写整个圆环算法。
* 不在本任务中调大范围视觉阈值，除非状态机改动必须触及。
* 不处理与本状态链无关的出环策略重构。

## Technical Notes

* Relevant specs:
  * `.trellis/spec/tracking/index.md`
  * `.trellis/spec/quality/embedded-tracking-guidelines.md`
* Relevant code:
  * `atg_reference/Project/CODE/circle.h`
  * `atg_reference/Project/CODE/circle.c`
* Existing dirty worktree has many uncommitted changes; implementation must not revert unrelated user work.

## Validation

* `rg -n "circle_find_B|follow_mode|find_B_entry|follow_B_begin" atg_reference/Project/CODE/circle.c` confirms only `find_B_entry()` / `follow_B_begin()` remain.
* `follow_B_begin()` success and failure paths now write `circle_B_search_reason/detail/trace/seed/best/slope/ready`, so BEGIN `ATGCircleABC` B_search output is current-frame follow evidence rather than stale ENTRY evidence.
* `git diff --check` passed.
* `./test.sh --host` passed; it rebuilt `atg_reference/Project/CODE/circle.c` and ran `config_parsing_test` / `options_parsing_test`.
* `./test.sh` passed; it rebuilt the target `front_car_mainline` including `circle.c`.
* 2026-06-26 follow-up: `follow_B_begin()` duplicate half-edit was removed and its success path now returns `1`; `circle_find_C()` was mechanically split into `C_reset()` / `C_check_B()` / `C_get_seed()` / `C_trace()` / `C_pick_corner()` / `C_lock()` / `C_log()` while preserving the current seed, trace, angle, join, and return semantics.
* `fast_context_search` was not available in this runtime, so local discovery used `rg`, direct file reads, and `git diff` review.
* Follow-up validation passed: `git diff --check`; `./test.sh --host`; `./test.sh`. Both builds rebuilt `atg_reference/Project/CODE/circle.c`; the only compiler warning observed was an existing `reference_step.c:857` unused static function warning unrelated to this split.
* 2026-06-26 reduction pass: `B_reset()` was renamed to `B_entry_reset()` because it clears `circle_B_point`; `find_B_entry(side)` now reads `circle_A_point` and locks `circle_B_point` directly; `circle_find_C()` was renamed to `find_C_begin(side)` and now reads `circle_B_point` and locks `circle_C_point` directly. `B_entry` / `B_follow` / `C_begin` remain three separate flows with no mode parameter or generic point-search pipeline.
* Reduction-pass validation passed: `git diff --check`; `./test.sh --host`; `./test.sh`. `rg` confirmed no `CircleContext` / `CircleConfig` / `CircleSearchContext` / `PointSearchConfig`, no `follow_mode`, and no stale `circle_find_C` / `B_reset` / `B_check_A` symbols in `circle.c`.
* 2026-06-26 constant-localization pass: top-level circle constants were reduced to state gates and commonly tuned thresholds (`ENTRY_OK_FRAMES`, `B_OK_FRAMES`, `C_OK_FRAMES`, `GYRO_*`, `B_READY_Y`, `OUT_*`, `REENTRY_SUPPRESS_FRAMES`). B-entry geometry, B-follow window, C angle/window checks, A id gates, and BEGIN false-entry fuse values are now local short `enum` values in their owning functions.
* Constant-localization validation passed: `rg` confirmed no residual `CIRCLE_ENTRY_AB*` / `CIRCLE_ENTRY_B*` / `CIRCLE_B_UP*` / `CIRCLE_C_*` geometry constant names, no old `CIRCLE_*_CONFIRM_FRAMES` gate names, and no old BEGIN-loss constant names in `circle.c`; `git diff --check -- atg_reference/Project/CODE/circle.c`; `./test.sh --host`; `./test.sh`.

## Decisions

* `NONE` 阶段 A seed 锁存时机：选择第一次 `circle_entry_detect()` 命中即锁存；连续确认只决定是否进入 `ENTRY`，不推迟 A seed 捕获。
* `ENTRY -> BEGIN` 门槛：B ready 是主触发因素。`ENTRY` 已持有锁存 A 入口证据与 A 对应的 `seed_line_x`，且当前帧 B trace valid、B 位于中心圆/圆弧边界点列上、B ready 阈值满足；上述 B 确认连续 2 帧成立后进入 `BEGIN`。进入 BEGIN 的瞬间必须保留最近稳定 B/上一帧 B 位置，并同步执行 `seed_line_x = B.x + CIRCLE_SEED_LINE_B_OFFSET_X`。BEGIN 入口后放弃 A；当前帧 A 不要求有效，A 丢失不清零 B ready streak。
* `BEGIN` 中 C 的使用方式：第一版保留 `CIRCLE_REF_IN_C`，只改变置位来源；C 必须由基础搜线恢复点列上的尖锐判据连续确认后才置位。删除 `CIRCLE_REF_IN_C` 和改造 `reference_step.c` 消费端作为后续任务。
* `ENTRY -> NONE` B 缺失规则：圆环和斜入十字通常在较远距离就能看到 B；普通单帧 no_b/no_seed/no_extreme 只清 B ready streak，不直接退出。若 A 已到近端或已客观丢失，但进入 `ENTRY` 后从未得到有效 B，则该 ENTRY 无效并退回 `NONE`。A 丢失不会触发切 B；只有 B ready 连续成立并发生 `ENTRY -> BEGIN` 时才切到 B 并给 `seed_line_x` 赋值。初始参数 `CIRCLE_ENTRY_A_NEAR_ID = 8` 保留作近端几何判别，后续通过日志调试。
* `BEGIN -> RUNNING`：保留 heading 600 作为入环完成状态门槛。
* `RUNNING -> OUT` 和 `OUT -> NONE`：第一版沿用现有出环规则。
* B/C 搜索策略：B 和 C 都必须走基础搜线；B 的 seed 来自 A 对应 `seed_line_x` 生成的预测线，C 的 seed 来自 B 对应 `seed_line_x` 生成的预测线。
* 预测线策略：`seed_line_x` 由当前固定点导出。ENTRY 内当前固定点是 A，A 可见时跟随 A，A 到近端丢失后保持最后一次 A 值，用 A 对应预测线找 B；`ENTRY -> BEGIN` 瞬间当前固定点切到 B，并同步用 `B.x + CIRCLE_SEED_LINE_B_OFFSET_X` 赋值；BEGIN 入口后放弃 A，使用 B 对应的 `seed_line_x` 和右侧线中心对称后的直线斜率生成预测线，在远端搜索窗口找 C seed；右环镜像处理。BEGIN 内不再检查双断点。
* B 语义：B 是中心圆/圆弧边界点列上的横向极值点，左环取 x 最大，右环取 x 最小；B 不是尖锐点。
* C 语义：C 是 B 后断线恢复出的远端边界尖锐点；第一版用 `local_angle_points()` / `nms_angle()` 或三点转角判据确认，不应由单行横向跳变独立确认。
* 入环补线策略：ENTRY 找 A/B，BEGIN 找 C；C 成立后沿用 `CIRCLE_REF_IN_C` 进入现有 C 拉线通道。控制拉线与 seed 预测线是两类东西，不得混用。
