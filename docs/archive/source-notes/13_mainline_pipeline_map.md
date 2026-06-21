# 主流程快照

这份文档只记录当前 `port/atg2022-reference-control` 分支的活跃主链。历史方案、已退休入口和阶段性推测不写进这里。

## 1. 当前一帧主链

```text
app/main.cpp
-> run_mainline()
   -> live() / analyze() / replay() / offline()
      -> device_capture_gray() / device_load_gray()
      -> drive_output_read_feedback(&fb)            # live 闭环路径
      -> encoder_total += 左右编码器增量均值          # live 闭环路径
      -> tracking_process_frame(rt)
         -> atg_reference_process_frame(rt->gray, rt->encoder_total)
            -> image_handle()
            -> find_corners()
            -> 近线 track_type 切换
            -> 当前比赛元素 profile: check_Half() / check_circle()
            -> run_cross() / run_circle()
            -> round/ramp/yroad/garage 状态保持禁用
            -> 环岛补线拼接 (Patching_Line.c)
            -> 选线归一化到 rptsn
            -> check_road()
         -> copy_atg_midline() + atg_lookahead_error() -> rt->vision.guide_error
      -> control_input_t(line_found, guide_error, element_active, stop_line)
      -> solve_control_input() / solve_control_input_with_feedback()
      -> drive_output_apply()                       # live 闭环路径
      -> assistant / report / print 输出
```

主链只保留一条。不要新增 parallel pipeline、shadow pipeline 或强制元素状态入口。

## 2. 各层合同

- `atg_reference/Project/CODE/` 是算法 owner：起搜、追线、IPM(`rot/inv_rot`)、平滑、重采样、角点、十字/半十字/环岛/回环/Y 路/坡道/道路分类全部保留在 ATG 原始源码中。当前比赛 profile 只激活十字/半十字和环岛；回环、Y 路、坡道、车库残留不删源码，但不进入状态机。
- `atg_reference/port/reference_step.c` 按当前比赛 profile 调用 ATG 算法，并从帧间 `encoder_total` 增量维护 ATG 的 `total_distence` 距离合同。元素启用开关集中在该文件顶部的 `ATG_ENABLE_*` 常量。
- `code/tracking/atg_reference_mainline.cpp` 是薄桥接层：`tracking_process_frame(rt)` 调用 ATG step，返回值就是 `line_found`；它只把控制必需的 `rptsn` 中线和 `guide_error` 写入 `rt->vision`，不再把 ATG 元素状态翻译成旧 `track/cross/ring/zebra` 字段。
- `code/core/control.cpp` 只消费 `control_input_t`（`line_found`、`guide_error`、`element_active`、`stop_line`），不公开消费 `runtime_t`；输出链是 `guide_error -> target_yaw -> yaw_cmd -> target_l/r -> duty`。
- `code/app/runners.cpp` 在 `tracking_process_frame(rt)` 之后直接用当前帧 ATG 结果生成 `control_input_t`；`line_found` 来自返回值，不在 runner 里重新解释 `track_type`/`reject_reason`。当前 `element_active` 只看 `cross_type/circle_type`，用于十字/环岛内降速。
- `code/app/report.cpp` 和 `code/app/assistant.cpp` 直接读取 ATG 当前帧全局变量输出调试证据；`runtime_t` 只保留 `gray/encoder_total/control_center_x/vision/control`，不是算法状态 owner。
- `code/drivers/` 保留 LS2K 外设事实：UVC 采集、`QUAD1=left`/`QUAD2=right` 编码器、`left->PWM2`/`right->PWM1` 电机映射和硬件占空上限。

## 3. 控制中线发布链

```text
ATG ipts0/ipts1 (raw 追线)
-> rpts0s/rpts1s (IPM + blur + resample)
-> 元素状态机选线 / 环岛补线
-> rptsn (归一化选线)
-> copy_atg_midline() -> rt->vision.mid
-> atg_lookahead_error() -> guide_error
```

`guide_error` 是差速 yaw-rate 外环输入；不要把 ATG 舵机 `pure_angle -> servo_pid` 移植进这条链。

## 4. 已退休的旧主线

旧本地 tracking 实现（`find_seeds/trace_edges/boundary/element/cross/ring/zebra/mainline` 一族）、旧控制入口 `solve_runtime*`、上一条 RT1064/autop 桥接文件和 `autop_reference/` 代码树都已经从当前分支移除。元素状态必须从 ATG 状态机自然推进，不能靠 CLI 或环境变量伪造。

旧 `runtime_t` 里的 `seeds/left_trace/right_trace/cross/ring/zebra/track_result_t` 诊断结构也已经移除。后续调参看 `atg_*` 报告键、live/replay 的 ATG 原生枚举和上位机原图/IPM 叠加，不再看旧字段名。

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| ATG `reference_step.c` 和 `Project/CODE/*` 用 `cross_type/circle_type/round_type/rptsn/rpts*s_num/Lpt*` 等全局变量表达当前帧事实。 | 旧 `runtime_t` 把这些事实再翻译成本地 `track/cross/ring/zebra/trace` 诊断字段，字段名容易被误读成旧主线仍在工作。 | 删除旧诊断结构，只保留 `rt->vision` 的 `line_found/mid/guide_error`，report/replay 直读 ATG 原生变量。 | 调参时应该看 ATG 的真实状态机和点列，不看伪翻译字段。 | 不改 `atg_reference/Project/CODE` 阈值、状态机或点列生成；无线时仍返回无线，不复用上一帧中线。 |

## 5. 当前有效验证入口

```bash
bash code/test.sh --host
```

如需离线行为证据，必须提供满足 `RAW_W x RAW_H` 的真实回放图像序列；文档截图不能作为 replay 输入。
