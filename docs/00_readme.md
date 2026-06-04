# Front_Car Mainline

这套工程是独立的 `Front_Car` 风格主线，不再继续修补 `project/user`。

## 当前入口

```bash
bash "scripts/test.sh" --host
bash "scripts/straight_baseline_audit.sh" ".diag/front_car_capture_live_current.png"
```

主链只保留一条：

```text
app/main.cpp
-> live / analyze / replay
-> tracking_process_frame(rt)
   -> find_seeds
   -> trace_edges / trace_single
   -> build_boundary_from_trace
   -> element_process
   -> perspective_points / blur_points / resample_points
   -> track_dualline / track_leftline / track_rightline
-> solve_runtime / solve_runtime_with_feedback
-> drive_output_apply
```

## 当前状态

- 新入口在 `app/main.cpp`。
- tracking 已接入 seed、trace、boundary、element 状态树、midline 和控制误差输出。
- `ring / cross / zebra` 通过 `element_process()` 自动互斥推进，不再使用固定序列或 CLI 强制状态。
- 旧 `tools/*audit.sh` 已逐步收窄；依赖强制状态旁路的入口已经退休。
- `scripts/behavior_equivalence.sh` 已退休，不再保留 legacy 双路线审计。

## 阅读顺序

优先看当前事实：

```text
docs/13_mainline_pipeline_map.md
docs/09_acceptance_checklist.md
.agentdocs/index.md
.agentdocs/tracking_mainline_contract.md
.agentdocs/tracking_complexity_map.md
```
