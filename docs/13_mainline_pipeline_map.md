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
            -> check_round() / check_Half() / Check_ramp() / check_circle() / check_yroad()
            -> run_round() / Run_Ramp() / run_cross() / run_circle() / run_yroad()
            -> 环岛补线拼接 (Patching_Line.c)
            -> 选线归一化到 rptsn
            -> check_road()
         -> 拷贝 ATG 当前帧状态/点列到 rt 诊断快照
         -> copy_atg_midline() + atg_lookahead_error() -> rt->track.guide_error
      -> control_input_t(line_found, guide_error, element_active, stop_line)
      -> solve_control_input() / solve_control_input_with_feedback()
      -> drive_output_apply()                       # live 闭环路径
      -> assistant / report / print 输出
```

主链只保留一条。不要新增 parallel pipeline、shadow pipeline 或强制元素状态入口。

## 2. 各层合同

- `atg_reference/Project/CODE/` 是算法 owner：起搜、追线、IPM(`rot/inv_rot`)、平滑、重采样、角点、十字/半十字/环岛/回环/Y 路/坡道/道路分类全部由 ATG 自己的全局变量和状态机维护。每帧顺序证据见 `atg_reference/Project/USER/Cpu0_Main.c` 和 `atg_reference/PORTING.md`。
- `atg_reference/port/reference_step.c` 按 ATG 的 `Cpu0_Main.c` 顺序调用算法，并从帧间 `encoder_total` 增量维护 ATG 的 `total_distence` 距离合同。
- `code/tracking/atg_reference_mainline.cpp` 是桥接层：`tracking_process_frame(rt)` 调用 ATG step，返回值就是 `line_found`；同时把 ATG 当前帧 `cross_type`/`circle_type`/`round_type`/点列拷贝到 `runtime_t` 供 report/assistant 消费，并从 `rptsn` 计算 `guide_error`。
- `code/core/control.cpp` 只消费 `control_input_t`（`line_found`、`guide_error`、`element_active`、`stop_line`），不公开消费 `runtime_t`；输出链是 `guide_error -> target_yaw -> yaw_cmd -> target_l/r -> duty`。
- `code/app/runners.cpp` 在 `tracking_process_frame(rt)` 之后直接用当前帧 ATG 结果生成 `control_input_t`；`line_found` 来自返回值，不在 runner 里重新解释 `track_type`/`reject_reason`。
- `runtime_t` 只是 report/assistant 等外围消费者的当前帧快照，不是控制 API，也不是算法状态 owner。
- `code/drivers/` 保留 LS2K 外设事实：UVC 采集、`QUAD1=left`/`QUAD2=right` 编码器、`left->PWM2`/`right->PWM1` 电机映射和硬件占空上限。

## 3. 控制中线发布链

```text
ATG ipts0/ipts1 (raw 追线)
-> rpts0s/rpts1s (IPM + blur + resample)
-> 元素状态机选线 / 环岛补线
-> rptsn (归一化选线)
-> copy_atg_midline() -> rt->track.mid
-> atg_lookahead_error() -> guide_error
```

`guide_error` 是差速 yaw-rate 外环输入；不要把 ATG 舵机 `pure_angle -> servo_pid` 移植进这条链。

## 4. 已退休的旧主线

旧本地 tracking 实现（`find_seeds/trace_edges/boundary/element/cross/ring/zebra/mainline` 一族）、旧控制入口 `solve_runtime*`、上一条 RT1064/autop 桥接文件和 `autop_reference/` 代码树都已经从当前分支移除。元素状态必须从 ATG 状态机自然推进，不能靠 CLI 或环境变量伪造。

## 5. 当前有效验证入口

```bash
bash code/test.sh --host
```

如需离线行为证据，必须提供满足 `RAW_W x RAW_H` 的真实回放图像序列；文档截图不能作为 replay 输入。
