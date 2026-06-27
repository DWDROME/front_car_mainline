# ATG2022 移植边界说明

目标：以 ATG2022 为新算法主线，同时保留当前 LS2K 的外设、控制与上位机层。

## 分层职责

| 层 | 目录 | 规则 |
| --- | --- | --- |
| ATG 算法核心 | `atg_reference/Project/CODE/` | 尽量贴近复制源码。不在此处隐藏移植逻辑。 |
| ATG 主循环证据 | `atg_reference/Project/USER/` | 仅供只读参考，用于确认执行顺序、选线逻辑与元素序列。 |
| 移植层 | `atg_reference/port/` | 提供 TC264 类型别名、全局变量、编码器钩子、图像输入及 LS2K 桥接函数。 |
| 当前桥接层 | `code/tracking/` | 对外暴露已有的 `tracking_process_frame()` 接口给 app/core/report。 |
| LS2K app/core/drivers | `code/app/`、`code/core/`、`code/drivers/` | 保留当前 UVC 采集、差速控制、编码器累积及上位机输出。 |

## 迁移内容

| 领域 | 决策 |
| --- | --- |
| 边线搜索与重采样 | 迁移至 ATG `shy_Image.c` 路径。 |
| 角点检测 | 迁移至 ATG 阈值与方向校验。 |
| 十字与半十字 | 迁移至 ATG `cross.c` + `Half_check.c`。 |
| 圆环与补线 | 迁移至 ATG `circle.c` + `Patching_Line.c`，在 ATG 层内保留 ATG 枚举顺序。 |
| 环岛、Y 字、坡道、车库 | 源码保留且需要时仍参与编译，但当前比赛配置在移植步骤中将这些状态保持空闲。 |
| 赛道分类 | 在有效选线后仍计算，用于上报/调试证据。 |

## 不迁移内容

| 领域 | 原因 |
| --- | --- |
| TC264 电机、舵机、ADRC、PID、按键、TFT、Flash、UART 及传感器驱动 | 硬件与控制环路与 LS2K 不同。 |
| TC264 直接执行器输出 | 当前车模使用 LS2K 差速 `guide_error -> yaw_cmd -> motor duty`。 |
| 第二套生产 IPM 真值源 | 当前生产 IPM 为 ATG `shy_Image.c::rot/inv_rot`；不重新引入旧的 `camera_param.c` 查表路径作为并行运行时源。 |

## 当前迁移顺序

1. 保留已推送的 RT1064/autop 分支历史作为旧基线。
2. 将本分支构建为 `port/atg2022-reference-control`。
3. 将 ATG 源码复制到 `atg_reference/`。
4. 创建最小化的 ATG 移植层，使其可在主机端编译，不依赖 TC264 驱动。
5. 仅在 `code/tracking` 保留 ATG 循迹桥接；旧的 `autop_reference/` 目录树与桥接从本分支移除。
6. 使用 `git diff --check`、`bash code/test.sh --host` 及定向离线/分析帧进行验证。

## 当前阶段

本分支当前编译所复制的 ATG `Project/CODE` 循迹与元素主线：

| 构建中活跃 | 状态 |
| --- | --- |
| `atg_reference/Project/CODE/shy_Image.c` | 活跃 |
| `atg_reference/Project/CODE/imgproc.c` | 活跃 |
| `atg_reference/Project/CODE/utils.c` | 活跃 |
| `atg_reference/Project/CODE/cross.c` | 活跃 |
| `atg_reference/Project/CODE/Half_check.c` | 活跃 |
| `atg_reference/Project/CODE/circle.c` | 活跃 |
| `atg_reference/Project/CODE/Patching_Line.c` | 活跃 |
| `atg_reference/Project/CODE/round.c` | 活跃 |
| `atg_reference/Project/CODE/yroad.c` | 活跃 |
| `atg_reference/Project/CODE/Ramp.c` | 活跃 |
| `atg_reference/Project/CODE/road.c` | 活跃 |
| `atg_reference/port/reference_step.c` | 活跃 |
| `code/tracking/atg_reference_mainline.cpp` | 活跃桥接 |

活跃的移植步骤按相关 `Cpu0_Main.c` 顺序执行，并收窄至当前比赛配置：

1. `image_handle()`
2. `find_corners()`
3. 近线 `track_type` 切换
4. `check_Half()` 用于十字/半十字入口检测
5. `check_circle()` 用于圆环入口检测
6. `run_cross()` / `run_circle()`
7. 保持 `round/ramp/yroad/garage` 状态空闲
8. 圆环补线来自 `Patching_Line.c`
9. 选线归一化为 `rptsn`
10. 在 ATG 预览变量计算完成后执行 `check_road()`

`code/tracking/atg_reference_mainline.cpp` 现为薄桥接层：它调用 ATG 步骤，
仅将选中的 `rptsn` 中线和 `guide_error` 复制到 `rt->vision`，元素证据留在
ATG 原生全局变量中供上报/辅助工具直接读取。它不引入 ATG 舵机 PID 或电机
输出；当前控制仍为 `guide_error -> yaw_cmd -> 差速电机占空比`。

TC264 车库动作、电机/舵机 PID、UART 广播、TFT 显示、Flash、按键及传感器
驱动仍在构建之外。环岛、坡道、Y 字路和车库逻辑保留在复制的 ATG 源码中
以便后续复用，但 `reference_step.c` 在当前比赛配置中不激活这些状态。

## 修改理由

| 参考版原本 | 当前代码差异 | 做了什么修改 | 原因 | 不引入兜底错误的证据 |
| --- | --- | --- | --- | --- |
| `Project/USER/Cpu0_Main.c` 依次执行 `image_handle()`、`find_corners()`、元素检测、元素运行及选线归一化。 | 此前 ATG 分支仅运行基础边线搜索并复制 `rptsc0/rptsc1`，已复制的元素文件未编译也未调用。 | `atg_reference/port/reference_step.c` 现在调用 ATG 的十字/半十字/圆环序列及选线逻辑。 | 算法主线必须依循 ATG 状态机的拥有者，而非旧的本地运行时。 | 几何缺失时仍返回无 `rptsn`；不复用旧帧中线。 |
| ATG `cross.c` 独立控制 `CROSS_IN/CROSS_HALF` 远线逻辑。 | 桥接层不再将十字状态镜像到本地 `runtime_t.cross` 结构。 | `report.cpp`/`assistant.cpp` 直接从 ATG 全局变量读取 `cross_type`、`far_rpts*` 及 `far_Lpt*`。 | 上位机与日志应展示 ATG 的真实状态，而非翻译后的旧主线字段。 | 数据仅为当前帧 ATG 证据；控制仍消费已发布的当前 `rptsn`。 |
| ATG `circle.c` 配合 `Patching_Line.c` 构建圆环各阶段的拼接中线。 | 圆环状态不再翻译到本地环诊断。 | `reference_step.c` 为 ATG 圆环 `BEGIN`/`RUNNING`/`OUT` 状态构建拼接中线；上报/辅助工具直接读取 `circle_type`、`circle_ref_mode` 及 `Splicing_*` 证据。 | 圆环选线行为属于已购入的 ATG 改进路径的一部分。 | 不产生合成兜底线；仅当 ATG 状态与远线证据使该分支活跃时才拼接。 |
| ATG `Cpu0_Main.c` 还包含环岛、坡道、Y 字路和车库相关分支。 | 当前比赛不需要这些元素，且部分触发条件依赖传感器或场景约定，未在本车上验证。 | 保留复制的源码，但通过 `ATG_ENABLE_*` 进行门控：仅启用十字/半十字和圆环；环岛/坡道/Y 字路/车库保持在 `NONE`。 | 这样保留 ATG 代码可用，同时避免未启用的元素抢占状态机。 | 禁用状态在 `reference_step.c` 中每帧显式重置；不引入旧帧线或假元素状态。 |
| ATG 中断服务例程仅在 `Count_dis_Flag` 置位时累积 `total_distence`。 | LS2K 没有 TC264 的中断/电机模块。 | 移植层从帧间 `encoder_total` 增量更新 `total_distence`。 | 该计数器对诊断、END 局部死锁释放及非圆环元素计时仍有价值；圆环入口推进现已由 B/C 当前帧几何主导。 | 计数器在 ATG 状态清除 `Count_dis_Flag` 时精确复位；不会掩盖缺失的视觉证据。 |
| ATG 距离计数器使用参考值 `ENCODER_PER_METER=5800` 缩放，在 `Count_dis_Flag` 置位时生效。 | LS2K 车轮反馈为原始 4096 线/转编码器脉冲。当前圆环状态机不再使用 `IN`/`RUNNING`/`OUT` 的距离兜底出口。 | `runners.cpp` 将平均车轮编码器增量通过轮周转换为 ATG 距离计数后更新 `runtime_t.encoder_total`；`circle.c` 保留 `mouth_ready`/`begin_dist` 作为诊断，END 局部 `total_distence` 仅配合软 heading 门使用。 | 保持单位桥接使日志和剩余距离开销处于统一 ATG 计数标度，同时圆环推进简化为几何/陀螺/视觉触发。 | 仅改动单位和诊断/剩余计数器消费者；不伪造几何、不复用旧线、不重新引入基于距离的圆环状态出口。 |
| ATG 圆环阶段计数器如 `none_right_line` 和 `none_left_line` 描述当前阶段内观察到的证据。`have_left_line` / `have_right_line` 为废弃残留（已标 `// DEPRECATED`，仅 reset/丢线时清零，不参与状态推进）。 | 当前移植不再有 `CIRCLE_LEFT_IN/CIRCLE_RIGHT_IN` 枚举状态；`BEGIN` 承担入环准备，`circle_ref_mode` 区分 `BEGIN_AB` 和 `IN_C` 补线模式。 | 进入 `BEGIN` 时重置圆环起点标志，然后在 `BEGIN` 内保持 A/B/C 证据为当前帧，直到 heading 将状态推进至 `RUNNING`。 | 计数器与几何数据必须描述活跃的 `BEGIN` 帧，而非过时的入口前证据。 | 不放松任何转换阈值，不伪造线；`RUNNING` 仍需要当前元素运动的陀螺进展。 |
| Joshua 风格的圆环入口首先识别同侧入口几何，然后使用线段修复使普通循迹进入环岛。 | 本地移植有 A（`Lpt0/Lpt1`）但无 B/C 几何，因此旧的入口推进来自 `mouth_loss + begin_dist` 和旧固定线。 | `circle.c` 现在将 A 视为 `Lpt0/Lpt1`，用 inner-hit 验证入口，并在跳过近侧边线边缘后扫描另一弧上的 B（左环扫 `seed_x+20..seed_x+45`；右环扫 `seed_x-20..seed_x-45`），状态保持在 `BEGIN`，仅 C 稳定后才设 `circle_ref_mode=IN_C`。`reference_step.c` 使用已有的半线辅助函数从 C 点锚定的修复边界发布 `circle_in_c_left/right`。 | 这使入口时机与入口路径依赖当前帧 A/B/C 几何而非丢线/距离窗口，同时保持在既有 ATG `rpts`/IPM/选线管线之内。 | 若 B/C 缺失，`BEGIN` 不会静默回退到旧固定线；选线失败通过 `ATGCircleABCDiag`、源 id `15/16` 及已有 stall 复位可见。 |
| ATG 参考在圆环各阶段通过 `pure_angle` 计算转向，对 `IN`、`RUNNING/END` 和 `OUT` 使用独立的 PID 增益；`Guide` 从选中线计算，但活跃参考执行器路径仍为舵机专用。 | LS2K 是差速车模，其公共控制协议为 `guide_error -> target_yaw -> yaw_cmd -> target_l/r`；将 `pure_angle` 或饱和 `Guide` 直接送入此外环会混合执行器单位。 | 保持桥接输出为航向风格的 `guide_error`，由 `atg_lookahead_error()` 基于当前选中的 `rptsn` 线计算；稍后将 `cross_type/circle_type` 仅作为速度/刹车行为的元素上下文使用。 | 这保留了当前差速控制边界，同时仍让 ATG `circle.c` 拥有选线和圆环状态。 | 不复用旧帧几何、不伪造线；控制输入来自当前帧选中的 ATG 线，而 `pure_angle`/`Guide` 保留为诊断/参考证据，除非单独设计差速 pure-pursuit 协议。 |
| ATG 圆环有多个基于距离的阶段出口，在原始舵机车模上很有用。 | 在此 LS2K 移植中那些距离分支成为陀螺/视觉之外的又一调参面，使日志因果难以阅读。 | 移除 `IN`、`RUNNING`、`OUT` 中圆环距离兜底出口及旧的 `END` 距离分支；保留陀螺/视觉作为正常圆环推进路径。 | 当前调试方向是清晰度优于隐性安全窗口：若陀螺/视觉无法推进状态，失败应以 stall 复位或下面 END 局部释放的方式浮出水面，而非悄悄走各阶段距离分支。 | 非 END 兜底为显式 `ATGCircleStall`，记录失败并复位元素；不适用旧帧几何或猜测线。 |
| END 应通过物理进展释放固定圆环线，而非任意帧超时。 | `LEFT_END` 固定右线可在无近出口 Lpt 时使车保持有效选线状态；全局距离兜底移除后，这可能使 END 阶段死锁。右 END 也缺少与左 END 相同的 355° 视觉门。 | 仅保留两个 END 出口：`vision_lpt_exit` 要求 355° heading + 近出口 Lpt；`end_encoder_release` 要求 heading >= 330° + END 局部 `total_distence >= 8000`。`OUT → END` 清除 `Count_dis_Flag`，因此后续 END 帧从 END 入口点开始计量距离。`ATGCircleEndDiag` 记录 heading、END 距离、线数、直道标志、Lpt 状态及两个出口布尔值。 | 这解决了固定线死锁，无需恢复 `IN`/`RUNNING`/`OUT` 距离出口或添加帧计数超时。 | 安全路径由陀螺进展加 END 阶段编码器距离门控；不重用过时几何、不伪造线、不声称普通循迹已成功。 |
| ATG 舵机转向可在车轮无需先降速时发出车身偏航指令。 | LS2K 差速驱动在 `yaw=±2000` 时钳制内侧目标轮接近或低于零，但日志显示内侧轮在占空比为零时仍惯性滑行数 rps，导致车身在丢线前沿偏航不足。 | 增加 `element_reverse_brake_percent`，仅允许元素活跃控制在内侧轮输出小幅带符号反向占空比；正常循迹保持纯正向。 | 这将转向权限转化为差速驱动制动权限——当元素几何已要求最大偏航时。 | 受限于显式小百分比，仅在活跃十字/圆环状态下生效，且仍依赖当前帧 `guide/yaw` 而非伪造几何或元素状态。 |
| ATG `Cpu0_Main.c` 将帧结果直接送入自身控制路径（`pure_angle -> servo`）；算法与控制之间没有运行时适配器。 | LS2K 控制入口曾为 `solve_runtime*(runtime_t)`，控制层消费整个 `runtime_t.track` 快照而非当前 ATG 帧结果。 | 公共控制入口现为 `solve_control_input(_with_feedback)(control_input_t)`；`runners.cpp` 在 ATG 步骤之后立即构建 `control_input_t`（`line_found` 来自 `tracking_process_frame()` 返回值，加上 `guide_error`/`element_active`/`stop_line`），`runtime_t` 仅保留 `gray/encoder_total/control_center_x/vision/control`。 | ATG 算法不变，因此控制链可一步产生最终输入；保留公共运行时适配器层只会保留旧主线语义。 | `line_found` 来自当前帧 ATG 步骤结果；无线或遇停止线时控制层清除状态并输出停止，而非保持任何历史中线或占空比。 |
| ATG2022 迁移后的主线没有斑马线停止检测；其比赛结束处理是已关闭的 TC264 车库路径。 | 旧本地主线有斑马线扫描，设置 `stop_line` 并驱动 `stop_request`。 | `control_input_t.stop_line` 恒为 0，在 `runners.cpp` 中有显式注释；旧的斑马线扫描随旧循迹树一同移除。 | 从非 ATG 证据伪造停止线会重新引入旧主线语义；停止必须来自移植后的真实检测器。 | 此为有文档记录的能力缺口，非静默兜底：在有 ATG 原生或新的停止检测器加入之前，车无自动停止。 |
| ATG 圆环可依赖持续运动来达到后续视觉或距离出口。 | 本差速车在 `line_found=0` 时停止；距离兜底移除后，未能推进的圆环状态必须可见地失败，而非被另一窗口掩盖。 | `reference_step.c` 保留移植层 stall 出口：在"圆环活跃但无选线"连续 30 帧后，以显式 `ATGCircleStall` 日志复位圆环状态。`build_circle_spliced_lines()` 每帧仍清除 `Splicing_*_center_num`。 | stall 复位现为唯一的非陀螺/非视觉逃生口，与当前清理决策一致。 | 不伪造线、不复用旧帧：车保持停止直到真实当前帧证据产生线；复位仅释放物理前提已不存在的状态，并以显式日志而非静默失败。 |
| ATG `CROSS_HALF` 从远线证据选线，依赖舵机车在远线帧丢失时继续运动。 | 本差速车在 `line_found=0` 时停止；若 `CROSS_HALF` 远线选择不产生 `rptsn`，图像冻结，正常十字出口无法观察到后续近线恢复。 | `runners.cpp` 增加有界 `CROSS_HALF` 中继：半十字活跃且当前 ATG 步骤无选线时，允许控制输入在短时间窗口（`FRONT_CAR_CROSS_HALF_RELAY_MS`，默认 500ms）内以元素速度走直线。 | 这将参考车"错过远线帧仍向前运动"的物理假设显式转化为有界差速车行为。 | 循迹仍报告无选线，不伪造线、不复用前帧、不引入近线兜底；中继使用零 guide_error，时间窗口过后若无当前帧线恢复则再次停止。 |
| `Half_check.c` 从裸"近 L (<5) + 无远 L"捷径进入 `CIRCLE_*_BEGIN`；作者注释称在他的赛道上此类角点只可能是圆环。`check_circle()` 自身入口额外要求对侧长直道标志（`is_straight1/0`）。 | 在当前赛道上，车身未摆正时接近十字会丢失整条对侧边界；该捷径随后将十字分类为 `CIRCLE_LEFT_BEGIN`（实车日志 frame=1920：`l=1@4/0@-1`，右侧种子丢失，车停止）。 | 将相同的对侧证据（左捷径加 `is_straight1`，右捷径加 `is_straight0`）加入 `Half_check.c` 的两个圆环捷径，使其与 `check_circle()` 的正门条件对齐。`check_cross()` 保持参考作者留下的禁用状态不变。 | 该捷径编码了赛道特定先验，非几何；真正的圆环入口总有对侧长直道，因此统一证据要求能区分两种场景。 | 收紧证据而非放松：不伪造状态或线，无证据帧保持普通单侧循迹，真正的圆环仍可通过任一入口触发，因为其对侧直道使标志为真。 |

## 2026-06-25 零行为清理

| 改动 | 文件 | 说明 |
| --- | --- | --- |
| `have_left_line` / `have_right_line` → 标 `// DEPRECATED` | `circle.c:74`、`circle.h:37` | 这两个计数器仅 reset/丢线时清零，不参与状态推进判断。标废弃后防止误读为"线重现即推进"。 |
| `mouth_lost_too_late` → `abort_late_mouth_loss` | `circle.c:763、767` | 重命名澄清这是假入口异常撤回，不是正常推进条件。注释："不是推进条件，是异常撤回"。 |
| `circle.h` 枚举注释乱码 → 三段英文注释 | `circle.h:4-10` | 旧乱码替换为当前三段状态机（`BEGIN` → `RUNNING` → `OUT`）对应的 Phase 1/2/3 英文描述。 |
