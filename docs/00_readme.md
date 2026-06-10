# Front_Car Mainline

这套工程是独立的 `Front_Car` 风格主线，不再继续修补 `project/user`。

## 当前入口

```bash
bash "scripts/test.sh" --host
bash "scripts/straight_baseline_audit.sh" ".diag/front_car_capture_live_current.png"
```

当前 `port/autop-direct-reference-control` 分支的 tracking 主链只保留一条：

```text
app/main.cpp
-> live / analyze / replay
-> tracking_process_frame(rt)
   -> autop_reference_process_frame(rt->gray, rt->encoder_total)
      -> RT1064 process_image / find_corners
      -> check_cross / run_cross
      -> check_circle / run_circle
      -> selected reference rptsn
   -> copy reference globals into rt diagnostics
   -> copy reference rptsn into rt->track.mid
-> solve_runtime / solve_runtime_with_feedback
-> drive_output_apply
```

## 当前状态

- 新入口在 `app/main.cpp`。
- tracking 主体来自 `autop_reference/Project/CODE` 的 RT1064 参考算法。
- 本车仍保留 UVC、编码器、GPIO/PWM、电机差速控制、report 和逐飞上位机链路。
- 移植边界在 `autop_reference/port` 和 `code/tracking/autop_reference_*`。
- 旧本地 tracking 实现已经不参与构建，避免第二套中线真相源。
- 关键阈值、控制参考点、seed 显示和 IPM overlay 判断见 `autop_reference/PORTING.md`。

## 阅读顺序

优先看当前事实：

```text
autop_reference/PORTING.md
docs/13_mainline_pipeline_map.md
docs/09_acceptance_checklist.md
```
