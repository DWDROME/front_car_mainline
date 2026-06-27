# brainstorm: ATG 收编为项目单一主线

## Goal

把当前“外来 ATG 参考库 + port 胶水 + code/tracking 薄桥”的三段式结构，收敛成当前项目自己的单一主线。目标不是改算法行为，而是让打开仓库时只看到一条生产链路：`code/app` 调用项目视觉/元素模块，模块内部拥有 ATG-derived 算法实现；外部 ATG 原始参考只作为只读证据归档存在。

## What I Already Know

* 用户明确要求处理全库，不只是新增 `CODE_MAP.md` 或做局部瘦身。
* 当前 `CODE_MAP.md` 已把主目标和 ATG 三层路牌写清楚，但它仍承认 `atg_reference/Project/CODE/` 是活跃算法核心。
* 当前 `code/CMakeLists.txt` 直接编译：
  * `code/tracking/atg_reference_mainline.cpp`
  * `../atg_reference/port/reference_globals.c`
  * `../atg_reference/port/reference_step.c`
  * `../atg_reference/Project/CODE/{shy_Image,imgproc,utils,cross,Half_check,circle,Patching_Line,round,yroad,Ramp,road}.c`
* 当前 public include 路径直接暴露：
  * `../atg_reference/port`
  * `../atg_reference/Project/CODE`
* 当前 app 层仍直接 include ATG/port 头：
  * `code/app/runners.cpp`
  * `code/app/control_input_builder.cpp`
  * `code/app/replay_log.cpp`
  * `code/app/report.cpp`
  * `code/app/assistant.cpp`
* 当前 ATG 算法文件中已有项目移植改动，不再是纯 upstream 副本。例如 `circle.c` include `atg_reference_step.h` 并调用当前项目的 circle begin distance helper。
* `atg_reference/Project/USER/`、`circle.old`、`data.c/h` 已被标注为历史参考/非主线。
* `.reference/` 是外部参考工程，当前由 `.gitignore` 屏蔽，不应进入主线。
* 上一阶段已完成日志和脚本入口清理，提交为 `dea14f9 chore(repo): 收敛日志样例和工具入口`。

## Assumptions

* “彻底变成我们的单一主线”不等于重写算法，也不等于删除 ATG-derived 算法；它表示生产源码应归入项目命名和项目目录。
* 外部 ATG 原始材料仍需要保留可追溯来源，但应从生产编译路径中降级为 `docs/reference/` 或 `archive/reference/` 类只读证据。
* 行为保持是第一优先级：目录移动、include 改名、CMake 收敛必须能通过 host build 和 replay/分析验证。
* 本任务不直接处理所有算法细修；它先处理源码归属、命名和编译边界。

## Requirements (evolving)

* 生产算法源码不能继续放在 `atg_reference/Project/CODE/` 这种外来工程路径下。
* 生产 port 胶水不能继续放在 `atg_reference/port/` 并被 app 层直接 include。
* `code/CMakeLists.txt` 应只从 `code/` 内部编译当前生产主线源码，外部参考路径不应作为 active source list。
* app/report/assistant/replay/control_input 不应直接 include `headfile.h`、`atg_reference_step.h` 这类外来/port 头；应通过项目拥有的窄接口读取视觉、元素和诊断快照。
* ATG-derived 算法可以保留 C 文件和函数名作为第一阶段行为保持，但目录、CMake、文档和接口命名应表达“这是本项目主线”。
* 原始 ATG 来源、旧主循环证据、未启用元素和历史源码应归档为只读参考，不和生产主线平级。
* 每个阶段都必须可验证、可回滚，不和算法行为改动混在一个提交里。

## Feasible Approaches

### Approach A: 物理收编到 `code/vision/atg/`（推荐）

* How: 把当前活跃 `atg_reference/Project/CODE/*.c/h` 和 `atg_reference/port/*` 分批移动到 `code/vision/atg/` 或 `code/tracking/atg/`，先保留 C 文件名和内部函数名；CMake 只引用 `code/` 内路径；外部原始参考改放 `docs/reference/atg2022/` 或 `archive/reference/atg2022/`。
* Pros: 打开仓库时生产源码归属最清楚；后续可以逐步改名、封装接口、删掉外来头。
* Cons: 一次性路径 churn 大，需要分多 PR 做 include/CMake/doc 更新。

### Approach B: 先逻辑收编，再物理移动

* How: 先在 `code/tracking/` 增加项目窄接口，app 层不再直接 include ATG 头；保留 `atg_reference/` 物理路径一段时间；之后再搬源码。
* Pros: 初期 diff 小，行为风险低。
* Cons: 外来目录仍在主线，用户当前最痛的“仓库看起来不是我们的”问题解决不彻底。

### Approach C: 保留 ATG 为 third_party/vendor

* How: 把 `atg_reference` 改名为 `third_party/atg2022` 或 `vendor/atg2022`，项目只通过 wrapper 调用。
* Pros: 来源边界清楚，适合真正未改 upstream 的依赖。
* Cons: 当前 ATG 文件已经被大量项目化修改，继续叫 third_party/vendor 会制造新的谎言；不符合“单一主线”目标。

## Recommended Direction

用户已选择“先接口封装，再搬目录”。总体采用 Approach A 的最终形态，但第一刀按 Approach B 的低风险方式落地：先把 app 层和 ATG/port 内部头解耦，再物理移动 active source。

1. **PR 1: 主线边界封装**
   建立项目窄接口，让 app/report/assistant/replay 不再直接 include port/ATG 内部头。行为保持。
2. **PR 2: 物理移动活跃源码**
   把 active source 从 `atg_reference/Project/CODE` 和 `atg_reference/port` 移入 `code/vision/atg/`（最终目录名待定），更新 CMake/include/doc。行为保持。
3. **PR 3: 原始参考降级归档**
   保留来源说明和只读参考，移走或归档 `Project/USER`、`circle.old`、`data.c/h`、`atg_reference/SOURCE.md`、`PORTING.md` 等旧边界文档。
4. **PR 4+: 命名去 ATG 化**
   在行为验证稳定后，再逐步把 `atg_reference_*`、`headfile.h`、`Project/CODE` 风格命名改成项目语义名。

## Expansion Sweep

### Future evolution

* 1-3 个月后应能把 circle/cross/mainline/IPM 分拆成项目模块，而不是继续由 `headfile.h` 聚合所有全局变量。
* 可以保留“ATG-derived”来源注释，但生产路径应读作当前车自己的视觉主线。

### Related scenarios

* `tools/ipm_recalib_apply.sh`、docs、report keys、assistant display 都引用 ATG 路径或 ATG 命名，需要同步迁移。
* Trellis spec 中 tracking critical audit 仍使用 `atg_reference/Project/CODE` 作为主线参考，后续需要更新为新路径。

### Failure / edge cases

* 文件移动期间可能和当前未提交的 circle/cross/reference_step 改动冲突；实施前必须先处理或隔离这些并行改动。
* C 源码 include 顺序和 `headfile.h` 聚合可能隐藏依赖；不能边搬边改算法逻辑。
* `git mv` 大量文件后 review 变差，必须按阶段拆 commit，并用 `bash test.sh --host` 验证每步。

## Open Questions

* 已回答：第一阶段先做“接口封装减少 app 层直读 ATG 内部头”。

## Decision (ADR-lite)

**Context**: 当前生产主线虽然已经由 ATG-derived 算法承担，但 app/report/assistant/replay/control_input 仍直接 include `headfile.h`、`atg_reference_step.h` 和 ATG 内部头，导致仓库结构和依赖方向仍像“外来库 + 胶水层”，不是项目自己的单一主线。

**Decision**: 先做接口封装。第一阶段不搬文件、不改算法行为，只在项目侧建立窄接口，让上层读取项目定义的视觉/元素/诊断 API，而不是直接接触 ATG/port 内部全局头。接口稳定后，再做 active source 的物理移动。

**Consequences**:

* 优点：第一阶段 diff 可审查，和当前未提交的 `circle.c/cross.c/reference_step.c` 算法改动冲突更少。
* 代价：`atg_reference/` 物理目录会短暂继续存在，单一主线视觉感需要第二阶段完成。
* 约束：第一阶段必须行为保持，不改状态机、不改阈值、不改控制链。

## PR 1 Scope: Interface Encapsulation

目标是让 app 层不再直连 ATG/port 内部头。候选处理对象：

* `code/app/control_input_builder.cpp`
* `code/app/replay_log.cpp`
* `code/app/report.cpp`
* `code/app/runners.cpp`
* `code/app/assistant.cpp`
* `code/tracking/atg_reference_mainline.cpp`

预期做法：

* 在 `code/tracking/` 增加或扩展项目拥有的 ATG-derived 窄接口。
* app 层只 include `tracking/...hpp` 项目头。
* `headfile.h`、`atg_reference_step.h`、`shy_Image.h` 等内部头只留在 tracking/adapter 层。
* 函数名可以暂时保留 `atg_` 前缀作为来源标记，但不能让 app 层知道 `Project/CODE` 和 `port` 目录结构。
* 不移动 `atg_reference/` 文件，不改 CMake active source list；这些留到 PR 2。

### PR 1 Slice 1 Progress

已完成第一小步：控制输入、replay 日志、live 主循环不再直接 include ATG/port 内部头。

改动点：

* `code/tracking/atg_reference_mainline.hpp/.cpp`
  * 新增只读 replay snapshot。
  * 新增元素状态查询：cross half、element active、cross type value。
  * 新增 port 查询/转发 wrapper：选线来源、圆环 begin 距离、raw_to_ipm、vehicle raw ref、circle heading update。
* `code/app/control_input_builder.cpp`
  * 移除 `atg_reference_step.h` / `headfile.h` include。
  * 通过 tracking wrapper 判断 half-cross relay 和 element active。
* `code/app/replay_log.cpp`
  * 移除 `atg_reference_step.h` / `headfile.h` include。
  * 通过 `atg_replay_snapshot()` 保持原 replay 输出字段。
* `code/app/runners.cpp`
  * 移除 `atg_reference_step.h` / `headfile.h` include。
  * 通过 wrapper 设置 ATG 车辆 raw ref 和更新 circle heading。
* `code/app/report.cpp`
  * 移除 `atg_reference_step.h` include。
  * 仍保留 `headfile.h` / `shy_Image.h`，因为 report 仍直接读取大量 ATG 点列、枚举和 circle 诊断结构。

剩余直连点：

* `code/app/report.cpp`：仍直读 ATG 点列、枚举、circle 诊断结构。
* `code/app/assistant.cpp`：仍直读 ATG 点列、补线点列和 circle seed 同源函数。

后续 PR 1 Slice 2 应专门设计 diagnostic/display snapshot API，再移除上述两个诊断文件的 `headfile.h` / `shy_Image.h` 依赖。

### PR 1 Slice 2 Progress

已完成第二小步：report 与 assistant 显示/诊断不再直接 include ATG/port 内部头。

改动点：

* `code/tracking/atg_reference_mainline.hpp/.cpp`
  * 新增只读 report snapshot，集中导出 report/live 需要的 ATG 计数、元素状态、角点、圆环 A/B/C、LPT 诊断、参数和 guide/pure_angle 诊断值。
  * 新增 raw/IPM 点列 view：`ipts0/ipts1`、`rpts0s/rpts1s/rptsn/rptsc*`、`inv_rptsn`、farline、circle splicing/center line 等只读显示点列。
  * 新增 `atg_ipm_to_raw()`、`atg_circle_type_name()`、`atg_cross_type_name()` 和 `atg_circle_entry_scan_seed_raw()`，让 app 显示层复用算法侧 seed/坐标来源。
* `code/app/report.cpp`
  * 移除 `headfile.h` / `shy_Image.h` include。
  * 所有 live/report/detail 输出字段改为读取 tracking adapter 的 snapshot/view，输出 key 和 printf 格式保持不变。
* `code/app/assistant.cpp`
  * 移除 `headfile.h` include。
  * raw 边线、中线、IPM 半区、L/B/C marker、种子框和圆环补线叠加全部通过 tracking adapter view 读取。
  * 圆环入口扫描线继续由算法侧 `circle_entry_inner_seed()` 间接提供，assistant 不再保存独立 seed 公式。

剩余直连点：

* `code/tracking/atg_reference_mainline.cpp` 仍 include `atg_reference_step.h` / `headfile.h`，这是当前 PR 1 预期的唯一 ATG adapter 边界。
* PR 2 才处理 active source 从 `atg_reference/` 物理移入 `code/`，因此 CMake/source tree 仍未达到单一主线最终形态。

## Acceptance Criteria (evolving)

* [ ] `code/CMakeLists.txt` 的 active source list 不再引用 `../atg_reference/...`。
* [x] app 层不再直接 include `headfile.h` 或 `atg_reference_step.h`。
* [ ] 当前生产视觉/元素源码位于 `code/` 下的项目主线目录。
* [ ] 原始 ATG 来源和历史证据被归入只读 reference/archive，不参与编译。
* [ ] `CODE_MAP.md` 和当前 docs 反映新主线，而不是三层外来库结构。
* [x] `bash test.sh --host` 通过。
* [ ] 若只移动文件不改行为，至少一份 replay/analyze 输出对比无行为变化，或明确记录无法对比的原因。

## Definition of Done

* 每个 PR 都能说明“行为保持”还是“命名/接口变化”，不得混合算法行为改动。
* 删除或移动原文件/目录前列 exact 清单并得到用户确认。
* 最小验证包含 `git diff --check`、`bash test.sh --host`。
* 触及源码路径时同步 CMake、tools、docs、Trellis spec 中的路径引用。
* 收尾前检查没有第二套生产真相源、隐藏 fallback、旧 reference 路径混入 active source。

## Out of Scope

* 不在本任务里重写 circle/cross 状态机。
* 不把 `pure_angle` 或参考舵机控制链引入当前差速控制。
* 不恢复旧本地 tracking 主线。
* 不一次性删除 `.reference/` 外部参考工程；只处理生产路径和可见仓库结构。
* 不在并行未提交算法改动未处理前做大规模 `git mv`。

## Technical Notes

* Inspected:
  * `CODE_MAP.md`
  * `code/CMakeLists.txt`
  * `atg_reference/PORTING.md`
  * `atg_reference/SOURCE.md`
  * include references under `code/app`, `code/tracking`, `atg_reference/port`, `atg_reference/Project/CODE`
* Relevant active compile list is currently in `code/CMakeLists.txt`.
* Existing dirty workspace contains unrelated ATG/tracking source edits; implementation must not mix them into this task unless the user explicitly decides to fold them in.

## Verification

2026-06-27 PR 1 Slice 1 已运行：

```bash
bash test.sh --host
git diff --check -- code/app/control_input_builder.cpp code/app/replay_log.cpp code/app/runners.cpp code/app/report.cpp code/tracking/atg_reference_mainline.hpp code/tracking/atg_reference_mainline.cpp .trellis/tasks/06-27-atg-mainline-unification/prd.md
rg -n "#include \"(headfile|atg_reference_step|shy_Image)\\.h\"" code/app code/tracking
```

结果：

* `bash test.sh --host` 通过。
* `git diff --check` 通过。
* include 搜索显示 app 层剩余直连为 `report.cpp` (`headfile.h`/`shy_Image.h`) 和 `assistant.cpp` (`headfile.h`)；`control_input_builder.cpp`、`replay_log.cpp`、`runners.cpp` 已解耦。

2026-06-27 PR 1 Slice 2 已运行：

```bash
bash test.sh --host
bash test.sh
git diff --check -- code/app/control_input_builder.cpp code/app/replay_log.cpp code/app/runners.cpp code/app/report.cpp code/app/assistant.cpp code/tracking/atg_reference_mainline.hpp code/tracking/atg_reference_mainline.cpp .trellis/tasks/06-27-atg-mainline-unification/prd.md
git diff --no-index --check /dev/null .trellis/tasks/06-27-atg-mainline-unification/prd.md
rg -n "#include \"(headfile|atg_reference_step|shy_Image)\\.h\"" code/app code/tracking
rg -n "atg_reference_(selected|circle|raw|vehicle|set|update|track_line)|#include \"(headfile|atg_reference_step|shy_Image)\\.h\"" code/app
```

结果：

* `bash test.sh --host` 通过。
* `bash test.sh` 交叉编译通过；仍有 ATG C 文件既有 warning（unused variable、`Patching_Line` 指针赋值、Ramp 条件优先级提示）。
* `git diff --check` 通过；未跟踪 PRD 另用 `git diff --no-index --check /dev/null ...` 检查，无 whitespace error 输出。
* app 层 include 搜索无命中；剩余 `headfile.h` / `atg_reference_step.h` include 只在 `code/tracking/atg_reference_mainline.cpp` adapter 内。
* app 层旧 `atg_reference_*` wrapper 名称和内部头 include 搜索无命中。

2026-06-27 PR 1 收口复验：

```bash
git diff --check -- .trellis/spec/quality/refactoring-and-diagnostic-discipline.md atg_reference/Project/CODE/circle.c atg_reference/Project/CODE/circle.h atg_reference/Project/CODE/cross.c atg_reference/Project/CODE/yroad.c atg_reference/port/atg_reference_step.h atg_reference/port/motor.h atg_reference/port/reference_globals.c atg_reference/port/reference_step.c code/app/assistant.cpp code/app/control_input_builder.cpp code/app/replay_log.cpp code/app/report.cpp code/app/runners.cpp code/tracking/atg_reference_mainline.cpp code/tracking/atg_reference_mainline.hpp
rg -n "#include \"(headfile|atg_reference_step|shy_Image)\\.h\"" code/app code/tracking
rg -n "atg_reference_track_line_found|atg_reference_selected_line_source\\(|atg_reference_selected_line_source_id\\(|atg_reference_vehicle_raw_ref_x|atg_reference_set_vehicle_raw_ref_x|atg_reference_raw_ref_to_ipm|get_total_encoder|g_atg_reference_encoder_total" atg_reference code
rg -n "atg_reference_(selected|circle|raw|vehicle|set|update|track_line)|#include \"(headfile|atg_reference_step|shy_Image)\\.h\"" code/app
bash test.sh --host
bash test.sh
```

结果：

* `git diff --check` 通过。
* 内部头 include 搜索只剩 `code/tracking/atg_reference_mainline.cpp`。
* app 层旧直连搜索无命中；旧 port 查询名在 `atg_reference` / `code` 主源码中无命中。
* `bash test.sh --host` 通过。
* `bash test.sh` 通过。
* 已补充 `.trellis/spec/quality/refactoring-and-diagnostic-discipline.md`：app/report/assistant 诊断必须通过 tracking adapter snapshot/view，不直接 include ATG/port 内部头。
