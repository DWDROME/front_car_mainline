# brainstorm: ATG 新路线重构执行方案

## Goal

把当前 `port/atg2022-reference-control` 分支从“ATG 算法接入到旧 `runtime_t` 壳”逐步收敛为“ATG 算法主线 + LS2K 外设/差速控制 + 极薄中间层”的结构。目标是降低旧 runtime 语义对后续调参和实车验证的干扰，同时保持 ATG 大佬代码尽量原样。

## What I already know

- 用户目标是完全转向 ATG 新路线，不是把 ATG 拆成纯函数后塞回旧 `tracking/mainline.cpp`。
- 当前目标 checkout 是 `/mnt/e/longxin/ls2k0300_library/ls2k300_library/seekfree_ls2k0300_opensource_library/test_project/front_car_mainline_autop_direct`。
- 当前分支是 `port/atg2022-reference-control`，已推送到 `origin/port/atg2022-reference-control`。
- 当前 ATG 主线已经编译进 `code/CMakeLists.txt`：`shy_Image.c`, `imgproc.c`, `cross.c`, `Half_check.c`, `circle.c`, `Patching_Line.c`, `round.c`, `yroad.c`, `Ramp.c`, `road.c`。
- 当前 `tracking_process_frame()` 实际调用 `atg_reference_process_frame(rt->gray, rt->encoder_total)`，再把 ATG 全局状态拷贝回 `runtime_t`。
- 当前 `runtime_t` 已不再是算法 owner，更像 LS2K app/control/report/assistant 的共享快照。
- 官方 `Motherboard_Demo/E8_camera/E08_04_uvc_tft180_display_demo/user/main.cpp` 是单文件设备对象 + 顺序主循环风格，没有 `runtime_t`。
- 已创建方案文档：
  - `docs/ATG新路线重构方案.md`
  - `docs/ATG库接入点评估.md`
- 当前方案明确：第四步不涉及上位机显示。

## Assumptions (temporary)

- MVP 应先收敛主循环、外设入口和控制输入语义，避免同时重写上位机显示和 report。
- ATG 算法层继续使用自己的全局变量和状态机，不把它改写成 `runtime_t` 风格。
- 当前 LS2K 差速控制仍保留，不直接迁移 ATG 舵机 `pure_angle -> servo` 输出。
- `runtime_t` 最终可以删除或大幅瘦身，但不应在第一步就把所有消费者一起改完。

## Open Questions

- 是否需要在第一阶段同时处理上位机和 report：暂定不处理，除非它们阻塞构建或基本运行。
- `code/app/report.cpp` 的未提交 `atg_*` 诊断补丁不纳入第一阶段；本阶段不扩展 report/assistant，只收敛核心 live/control/ATG step 路径。

## Requirements (evolving)

- 建立一个集中外设编排入口，参考官方 Example 的简单主循环风格。
- 外设入口收拢现有硬件参数和注释：UVC、PWM、电机方向、编码器映射、IMU、上位机连接参数。
- 每帧视觉调用方式向 ATG 原始顺序靠拢：采图、读反馈、调用 ATG step、生成控制输入、差速控制、下发电机。
- ATG 算法内部保持全局变量和状态机，不强行拆成旧 runtime 数据结构。
- MVP 第一阶段采用“直接控制输入 + 外设编排入口”路线：核心 live/control 链路不再公开 `runtime_t` 控制入口；`runtime_t` 暂时只服务 report/assistant 等外围消费者。
- 控制输入只承接 `line_found`、`guide_error`、元素降速状态和停车状态；由当前 ATG step 结果直接生成，不新增公开 runtime 适配层。
- MVP 第一阶段覆盖控制链和 live 主循环：让 `core/control.cpp` 使用薄控制输入，同时把 `runners.cpp::live()` 的顺序整理得更接近官方 Example / ATG 每帧流程。
- 同类范围取舍按“核心路径先收敛、诊断显示后处理”的理念执行：优先 live/control/ATG step，暂不扩散到上位机显示和完整 report 重写。
- 本阶段不处理上位机红/黄/绿线显示重写。
- 本阶段不混入 `code/app/report.cpp` 的 `atg_*` 诊断补丁；该补丁若需要保留，应作为后续单独诊断任务处理。

## Acceptance Criteria (evolving)

- [ ] 方案执行后主循环顺序能一眼对应 ATG 每帧顺序。
- [ ] ATG 算法入口不再伪装成旧 tracking 主线语义。
- [ ] 控制层只读取必要控制输入，而不是依赖完整 `runtime_t.track` 大结构。
- [ ] `runners.cpp::live()` 的采图、反馈、ATG step、控制、下发顺序更接近官方 Example 的显式主循环。
- [ ] 外设参数和硬件映射集中且有注释。
- [ ] 不引入 ATG 舵机/PID/TC264 外设输出。
- [ ] 本阶段不重写上位机显示。
- [ ] `git diff --check` 通过。
- [ ] `bash code/test.sh --host` 通过。
- [ ] `bash code/test.sh` 通过，或说明无法运行的硬件/环境原因。

## Definition of Done (team quality bar)

- 代码改动小步提交，避免一次性重写所有模块。
- 改动前后必须保留 ATG 算法主线可编译。
- 行为变化必须能用当前文件和命令解释，不依赖聊天记忆。
- 文档更新同步说明当前阶段做了什么、没做什么。
- 测试/构建命令结果记录在最终交付里。

## Out of Scope (explicit)

- 本阶段不重写上位机显示协议和红/黄/绿线发送。
- 本阶段不重写完整 report 字段体系。
- 本阶段不迁移 ATG 舵机控制、TC264 PID、ADRC、UART、TFT、flash、key 驱动。
- 本阶段不做复杂自动调参。
- 本阶段不解决所有 ATG 元素实车参数，只为后续调参降低结构干扰。

## Technical Notes

- 目标方案文档：
  - `/mnt/e/longxin/ls2k0300_library/ls2k300_library/seekfree_ls2k0300_opensource_library/test_project/front_car_mainline_autop_direct/docs/ATG新路线重构方案.md`
  - `/mnt/e/longxin/ls2k0300_library/ls2k300_library/seekfree_ls2k0300_opensource_library/test_project/front_car_mainline_autop_direct/docs/ATG库接入点评估.md`
- 当前关键文件：
  - `code/app/runners.cpp`
  - `code/drivers/device.cpp`
  - `code/drivers/drive_output.cpp`
  - `code/drivers/imu_feedback.cpp`
  - `code/tracking/atg_reference_mainline.cpp`
  - `atg_reference/port/reference_step.c`
  - `atg_reference/Project/USER/Cpu0_Main.c`
  - `code/core/control.cpp`
- 当前未提交状态：
  - `code/app/report.cpp` 有上次 ATG 诊断补丁，尚未提交。
  - `.diag.zip` 未跟踪。
  - 两份 ATG 方案文档未跟踪。

## Initial Approach Options

### Approach A: 先建立直接控制输入和外设编排入口（Recommended）

- 核心 live/control 调用不再使用 `runtime_t` 作为控制 API。
- 先做 `control_input_t`，承接 `line_found`, `guide_error`, 元素状态和停车线。
- 外设入口逐步从 `runners.cpp` 收敛。
- 风险较低，适合先跑通和调参。

### Approach B: 直接删除 `runtime_t`

- 一次性改 `runners/control/report/assistant/tracking` 所有接口。
- 结构最终更干净。
- 风险高，容易把主循环重构 bug、控制 bug、ATG 参数问题混在一起。

### Approach C: 只写文档，不改代码

- 继续把方案细化，不触碰当前分支。
- 风险最低，但不能改善当前结构问题。

## Decision (ADR-lite)

**Context**: 当前 `runtime_t` 混合了承载图像、旧 tracking 诊断、ATG 映射、控制输入和上位机输出等多种职责。用户希望最终语义靠近 ATG 和官方 Example 的顺序主循环，但当前还需要继续实车参数校验。

**Decision**: MVP 第一阶段选择 Approach A，并采用“控制链 + live 主循环一起整理”的范围：先建立直接控制输入和外设编排入口。核心控制 API 直接消费 `control_input_t`；`runtime_t` 不再作为控制入口，只暂留给还没重构的 report/assistant。

**Consequences**: 这能直接切断控制层对旧 `runtime_t.track` 的公开依赖，并让 live 主循环更接近 ATG/官方 Example 的顺序结构，同时避免把 report/assistant 显示重写混进第一阶段。后续如果 ATG 主线和实车参数稳定，再继续把外围快照瘦成 `atg_snapshot` 或删除。

## Scope Principle

后续类似取舍按这个理念默认决策：优先让核心路径直接服务最终实车运行，避免只做外围整理；但每一步仍控制范围，先改 live/control/ATG step，不把上位机显示、完整 report 和复杂调参混进第一阶段。

## Implementation Plan (small PRs)

### PR1: 建立直接控制输入

- 新增一个小结构承载控制层实际需要的数据，例如 `line_found`、`guide_error`、`cross_active`、`ring_active`、`stop_line`。
- 给 `core/control.cpp` 增加新入口，让控制层从薄输入计算输出。
- 删除旧 `solve_runtime*()` 控制入口；离线和 live 都直接生成 `control_input_t`。
- 不改 ATG 算法，不改上位机显示。

### PR2: 整理 live 主循环

- 在 `runners.cpp::live()` 中把关键变量显式化：`gray`、`encoder_total`、`feedback`、`control`。
- 将每帧顺序整理为：采图 -> 读反馈/更新里程 -> ATG step -> 构建薄控制输入 -> 控制 -> 下发电机。
- 保留必要的 profile/print 行为，但避免继续扩大 `runtime_t` 依赖。
- 不重写 report 和 assistant。

### PR3: 外设入口收拢

- 建立或收敛一个外设编排文件，集中初始化摄像头、IMU、编码器、电机和上位机连接参数。
- 把当前硬件映射和注释写清楚：`left -> PWM2`、`right -> PWM1`、`QUAD1 -> left`、`QUAD2 -> right`、编码器符号、35% PWM 硬上限、IMU yaw 轴。
- 不复制逐飞底层库实现。

### PR4: 删除或隔离旧 runtime 残留

- 在不影响 `report/assistant` 的前提下，减少核心路径对 `runtime_t.track` 的依赖。
- `seeds`、`left_trace`、`right_trace`、`mid_position`、`width_base` 等旧主线字段先从核心路径移除，是否从类型定义删除留到后续。

## Current Dirty Worktree Handling

- `code/app/report.cpp` 当前有未提交 `atg_*` 诊断字段补丁。
- 这个补丁对“直道识别不了”的参数校验有价值，但它属于 report 诊断，不属于第一阶段核心 live/control 收敛。
- 本阶段不纳入这个补丁，也不继续扩大 report；实现和验证时只把它视为既有脏改，最终交付会单独说明。

## Brainstorm Reopen: 主线澄清

用户反馈当前问题是不清晰，需要先讨论确定最佳主线，再继续收口。当前事实：

- `code/app/runners.cpp` 已经在 `tracking_process_frame(rt)` 后构造 `control_input_t`。
- `line_found` 已来自 `tracking_process_frame(rt)` 返回值，而不是 runner 重新解释 `track_type/reject_reason`。
- `code/core/control.hpp/.cpp` 已去掉公开 `solve_runtime*()` 入口，控制公开入口为 `solve_control_input*()`。
- `runtime_t` 仍存在，当前主要服务 report/assistant/离线快照；是否继续保留到哪一层需要确认。
- `docs/13_mainline_pipeline_map.md` 和部分说明文档还在从旧 mainline 语义向 ATG 语义迁移。

当前待确认的第一优先级问题：

- 最终主线应定义到什么程度：只改核心实时链路，还是继续把 report/assistant 也改成直接读 ATG 快照，进而删除大部分 `runtime_t`？
