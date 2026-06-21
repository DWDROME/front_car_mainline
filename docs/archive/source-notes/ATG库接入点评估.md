# ATG 库接入点评估

本文只记录 ATG 新库在当前工程中的可接入位置，用于后续讨论和拆任务。

当前目标不是把 ATG 改写成旧 `runtime_t` 风格，而是让 ATG 做算法主线，当前工程只保留外设、差速控制、上位机和必要中间层。

## 总体分层

| 层 | 当前文件 | ATG 对应文件 | 建议 |
| --- | --- | --- | --- |
| 外设入口 | `code/app/runners.cpp`, `code/drivers/*.cpp` | 官方 Example 的 `user/main.cpp` 风格 | 后续收敛成一个外设编排入口，负责摄像头、IMU、编码器、电机、上位机。 |
| ATG 算法主线 | `atg_reference/port/reference_step.c` | `atg_reference/Project/USER/Cpu0_Main.c` | 继续按 ATG 每帧顺序组织，不回到旧 tracking 主线。 |
| 基础视觉 | 当前旧 `code/tracking/imgproc.cpp` 已不作为主线 | `shy_Image.c`, `imgproc.c` | 由 ATG 接管起搜、追线、IPM、平滑、重采样、角点。 |
| 元素识别 | 当前旧 cross/ring/zebra 已不作为主线 | `cross.c`, `Half_check.c`, `circle.c`, `round.c`, `yroad.c`, `Ramp.c`, `road.c` | 可作为 ATG 主线继续保留，但传感器依赖项要逐个确认。 |
| 中间层输出 | `code/tracking/atg_reference_mainline.cpp` | ATG 全局 `rptsn`, `cross_type`, `circle_type` 等 | 已收敛成薄 `vision_state_t`：只给控制层 `line_found/guide_error/midline`，元素诊断直读 ATG 原生状态。 |
| 控制层 | `code/core/control.cpp` | ATG `pure_angle`, `Guide` | 当前仍用 LS2K 差速控制；ATG 舵机输出不直接接入。 |
| 上位机/报告 | `code/app/assistant.cpp`, `code/app/report.cpp` | ATG 全局点列和状态 | 后续直接读取 `atg_snapshot` 或 ATG 只读快照，减少旧字段映射。 |

## 具体接入表

| 当前工程位置 | 当前职责 | ATG 可替代/插入位置 | 建议动作 | 需要确认的参数/风险 |
| --- | --- | --- | --- | --- |
| `device_capture_gray()` | 获取 `160x120` 灰度图 | ATG `img_raw.data` | 保留 LS2K 摄像头采集，把灰度指针交给 `atg_reference_process_frame()`。 | 摄像头必须仍是 `160x120`；不做隐式 resize。 |
| `tracking_process_frame()` | 当前对外视觉入口 | `atg_reference_process_frame(gray, encoder_total)` | 后续可以去掉旧名字，改成更直接的 `atg_step()` 或 `vision_step()`。 | 外部调用方需要同步改为读 ATG 输出快照。 |
| `image_handle()` | 无旧等价主线 | `shy_Image.c::image_handle()` | 作为 ATG 基础视觉入口保留。 | `begin_x`, `begin_y`, `block_size`, `clip_value` 需要实车估计。 |
| 起点搜索 | 旧 seed 逻辑已不是主线 | `image_handle()` 内连续 4 点局部阈值搜索 | 保留 ATG 做法，作为直道/元素识别前置。 | 起搜行偏低会导致搜线短；需要报告里输出起点和 `ipts*_num`。 |
| 左右手追线 | 旧 `trace_single()` 已不是主线 | `findline_lefthand_adaptive()`, `findline_righthand_adaptive()` | 由 ATG 接管。 | `block_size/clip_value` 直接影响边界稳定性。 |
| IPM 投影 | 旧静态表曾经是主线 | `Cal_rot_x()`, `Cal_rot_y()`, `Cal_inv_rot_*()` | 如果走 ATG 主线，就让 ATG 的 `rot/inv_rot` 成为视觉算法内的唯一 IPM 来源。 | 必须确认新标定结果已写入 `rot/inv_rot`，否则直线会弯。 |
| 点列平滑 | 旧 `blur_points` 已不是主线 | `imgproc.c::blur_points()` | 保留 ATG 实现。 | `line_blur_kernel=7` 是否适合当前图像需用直道帧确认。 |
| 等距重采样 | 旧 resample 已不是主线 | `imgproc.c::resample_points()` | 保留 ATG 实现。 | `sample_dist` 与 `pixel_per_meter` 的组合决定点距语义。 |
| 角度/NMS | 旧 boundary 角点已不是主线 | `local_angle_points()`, `nms_angle()` | 保留 ATG 作为 L/Y/直道判断依据。 | `angle_dist/sample_dist` 决定角点窗口。 |
| L/Y 点识别 | 历史本地实现已归档 | `find_corners()` | 由 ATG 负责元素入口特征。 | Y 路是否启用要和赛题需求确认；误识别会影响元素状态。 |
| 直道判断 | 旧 straight 判断已不是主线 | `is_straight0`, `is_straight1` | 作为 ATG 元素触发条件保留。 | 直道失败优先看 `rpts*s_num` 与 `conf*_max`。 |
| 十字 | 历史本地实现已归档 | `cross.c`, `Half_check.c` | 保留 ATG 的十字/半十字逻辑。 | 远线扫描和 `far_Lpt*` 需要上位机显示验证。 |
| 圆环/回环 | 历史本地实现已归档 | `circle.c`, `round.c`, `Patching_Line.c` | 保留 ATG 圆环/回环和补线拼接。 | 编码器距离、补线点列、阶段切换需要实车验证。 |
| Y 路 | 当前项目旧路线不强调 | `yroad.c` | 先保留为 ATG 算法能力，但需要决定是否在比赛中启用。 | 如果赛题不需要，建议后续加显式开关，避免误触发。 |
| 坡道 | 当前 LS2K 没接 TFmini | `Ramp.c` | 代码可保留，但输入传感器未接前只能视为待适配。 | `TFmini_Plus_Dis/Strong` 当前默认值无法代表真实坡道。 |
| 道路分类/速度策略 | 当前速度由 YAML 控制 | `road.c` | 可以作为诊断保留；不要直接改 LS2K 速度策略。 | `pure_angle/Guide` 与差速控制量纲不同。 |
| ATG 舵机输出 | 当前无舵机控制链 | `pure_angle`, `Guide`, `Guide_up` | 不直接接入电机控制。 | 如要使用，只能重新定义差速控制接口，不可简单赋给 `guide_error`。 |
| 差速控制 | `core/control.cpp` | 无直接 ATG 等价 | 保留当前 LS2K 控制，输入来自 ATG 中线误差。 | `guide_error` 量纲必须稳定，不能混入舵机 PWM 语义。 |
| 上位机红/黄/绿线 | `assistant.cpp` 直读 ATG 全局，`runtime_t` 只提供灰度底图 | ATG `ipts/rpts/rptsn/far_rpts` | 已切到上半原图、下半 IPM；不再依赖旧 `track_result_t`。 | 需要实机看 IPM 直道是否平行竖直。 |
| 报告日志 | `report.cpp` 直读 ATG 全局状态 | ATG 全局状态 | 已改成 `atg_*` 原生诊断键。 | 不再输出旧 `ring_kind/cross_state/zebra/trace` 翻译字段。 |

## 优先级建议

| 优先级 | 项 | 原因 |
| --- | --- | --- |
| P0 | 校验 `rot/inv_rot` 是否同步新 IPM 标定 | IPM 错会直接导致直道弯、元素误判。 |
| P0 | 输出 `ipts*_num`, `rpts*s_num`, `rptsn_num`, `is_straight*`, `conf*_max` | 这是判断“直道识别不了”的最小证据。 |
| P0 | 明确 `sample_dist`, `pixel_per_meter`, `block_size`, `clip_value`, `begin_y` | 这些是当前 ATG 主线最关键的参数估计点。 |
| P1 | 把 `runtime_t` 瘦成 `atg_snapshot` | 已完成，减少旧主线语义干扰。 |
| P1 | 重写上位机/报告读取接口 | 已完成，显示和日志直接表达 ATG 点列和状态。 |
| P2 | 决定 Y 路、坡道、道路分类是否启用 | 它们属于 ATG 能力，但传感器和赛题需求需要确认。 |

## 不建议替代的部分

| 模块 | 不建议原因 |
| --- | --- |
| `code/drivers/` 底层逐飞设备封装 | 当前 LS2K 硬件已经能跑，ATG 原工程不是 LS2K 外设。 |
| `code/core/control.cpp` 的差速控制结构 | ATG 是舵机/速度调度思路，不能直接替代差速控制。 |
| YAML 控制参数 | 当前控制层仍依赖这些参数，ATG 算法接入不应顺手改控制调参来源。 |
| 官方 Example 的极简主循环原样复制 | Example 只有显示功能，没有 ATG 元素、闭环控制、上位机多线诊断。应学习结构，不是照搬全部。 |
