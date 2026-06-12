# Front_Car Mainline

这套工程是独立的 `Front_Car` 风格主线，不再继续修补 `project/user`。

## 当前入口

```bash
bash "scripts/test.sh" --host
bash "scripts/straight_baseline_audit.sh" ".diag/front_car_capture_live_current.png"
```

当前 `port/atg2022-reference-control` 分支的主链只保留一条：

```text
app/main.cpp
-> live / analyze / replay
-> device_capture_gray / device_load_gray
-> drive_output_read_feedback() 更新 encoder_total   # live 闭环路径
-> tracking_process_frame(rt)
   -> atg_reference_process_frame(rt->gray, rt->encoder_total)
      -> ATG image_handle / find_corners / elements / selected rptsn
   -> copy selected rptsn + guide_error into rt->vision
-> control_input_t(line_found, guide_error, element_active, stop_line)
-> solve_control_input / solve_control_input_with_feedback
-> drive_output_apply
```

## 当前状态

- 新入口在 `app/main.cpp`。
- tracking 主体来自 `atg_reference/Project/CODE` 的 ATG2022 算法。
- 本车仍保留 UVC、编码器、GPIO/PWM、电机差速控制、report 和逐飞上位机链路。
- 移植边界在 `atg_reference/port` 和 `code/tracking/atg_reference_mainline.cpp`。
- 旧本地 tracking 实现和上一条 RT1064/autop 代码树已从当前分支移除，避免第二套中线真相源。
- 当前核心控制 API 消费 `control_input_t`，不再公开消费完整 `runtime_t`。
- 关键 port 边界和 ATG 接入说明见 `atg_reference/PORTING.md`。

## 阅读顺序

优先看当前事实：

```text
atg_reference/PORTING.md
docs/13_mainline_pipeline_map.md
docs/ATG新路线重构方案.md
docs/ATG库接入点评估.md
docs/IPM重标定流程.md
docs/IPM调用调研.md
docs/控制参数笔记.md
docs/09_acceptance_checklist.md
```

`docs/archive/` 只保留旧路线背景，不作为当前调参和改算法依据。
