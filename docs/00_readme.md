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
   -> build_frame_boundaries_and_candidates
      -> build_boundary_from_trace
      -> build_rpts0 / build_rpts1
      -> refresh_boundary_corners
      -> track_leftline / track_rightline into rptsc0/rptsc1
   -> snapshot_ring_frame_start_action
   -> element_process
   -> classify_frame_mode
   -> apply_frame_start_element_crop
   -> build_selected_midline
      -> build_rptsn into rt->track.mid
   -> publish_track_result
   -> run_zebra_scan
-> solve_runtime / solve_runtime_with_feedback
-> drive_output_apply
```

## 当前状态

- 新入口在 `app/main.cpp`。
- tracking 已接入 seed、trace、boundary、候选中线、element 状态树、`rt->track.mid` 和控制误差输出。
- `cross / ring` 通过 `element_process()` 互斥推进；`zebra` 只消费 mainline 构造的扫描中线和 raw image。
- 当前帧控制中线只由 `mainline.cpp` 发布；`cross.cpp` / `ring.cpp` 不直接写 `rt->track.mid`。
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
