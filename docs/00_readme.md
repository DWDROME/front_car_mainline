# Front_Car Mainline

这套工程是独立的差速车主线，基于 ATG2022 舵机算法移植到龙芯 LS2K0300。

当前分支：`port/atg2022-reference-control`

## 阅读顺序

```text
docs/01_全局地图.md              # 新手先读：三层身份 + 舵机/差速冲突 + 数据流
atg_reference/PORTING.md         # 移植边界：什么搬了什么没搬、每条改动的理由
docs/13_mainline_pipeline_map.md # 逐帧管道、各层合同、字段名
docs/控制参数笔记.md              # 控制参数位置、加载顺序、每帧调用关系
docs/ATG新路线重构方案.md         # 后续收敛方向讨论
docs/ATG环岛问题记录.md           # 环岛问题排查记录
docs/ATG库接入点评估.md           # ATG 各模块接入评估
docs/IPM重标定流程.md             # IPM 标定 SOP
docs/IPM调用调研.md               # IPM 代码路径和合同
docs/09_acceptance_checklist.md   # 验收单
```

`docs/archive/` 是历史路线背景，不作为当前调参依据。

## 当前入口

```bash
bash "scripts/test.sh" --host
bash "scripts/straight_baseline_audit.sh" ".diag/front_car_capture_live_current.png"
```

## 一帧主链

```text
app/main.cpp
-> live / analyze / replay
-> device_capture_gray / device_load_gray
-> drive_output_read_feedback(&fb)        # live: 读编码器
-> tracking_process_frame(rt)
   -> atg_reference_process_frame(gray, encoder_total)
      -> ATG image_handle / find_corners / elements / selected rptsn
   -> copy_atg_midline() + atg_lookahead_error()
-> control_input_t(line_found, guide_error, element_active, stop_line)
-> solve_control_input / solve_control_input_with_feedback
-> drive_output_apply
```

## 当前状态速览

| 项目 | 状态 |
|------|------|
| 主入口 | `app/main.cpp` |
| tracking 算法 | ATG2022（`atg_reference/Project/CODE`） |
| 外设 | UVC、编码器、GPIO/PWM、差速电机、report、上位机 |
| 移植边界 | `atg_reference/port` + `code/tracking/atg_reference_mainline.cpp` |
| 旧 tracking 实现 | 已移除，避免第二套中线真相源 |
| 控制 API | `control_input_t`（非完整 `runtime_t`） |
| 移植说明 | `atg_reference/PORTING.md` |
