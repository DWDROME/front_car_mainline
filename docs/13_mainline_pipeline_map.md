# 主流程快照

这份文档只记录当前 `front_car_mainline` 的活跃主链。历史方案、已退休入口和阶段性推测不写进这里。

## 1. 当前一帧主链

```text
app/main.cpp
-> run_mainline()
   -> live() / analyze() / replay()
      -> device_capture_gray() / device_load_gray()
      -> tracking_process_frame()
         -> find_seeds()
         -> trace_edges()
         -> build_frame_boundaries_and_candidates()
            -> build_boundary_from_trace(left/right)
            -> build_rpts0() / build_rpts1()
            -> refresh_boundary_corners()
            -> track_leftline() / track_rightline() into rptsc0/rptsc1
         -> snapshot_ring_frame_start_action()
         -> element_process()
         -> classify_frame_mode()
         -> apply_frame_start_element_crop()
         -> build_selected_midline()
         -> publish_track_result()
         -> run_zebra_scan()
      -> solve_runtime()
      -> print / display / assistant stream
```

主链只保留一条。不要新增 parallel pipeline、shadow pipeline 或强制元素状态入口。

## 2. tracking 内部合同

当前控制中线发布链：

```text
raw boundary
-> rpts0s/rpts1s
-> rptsc0/rptsc1 or CROSS_IN far candidate
-> build_rptsn()
-> rt->track.mid
-> guide_error
```

关键边界：

- `imgproc.cpp` 负责 seed、trace、点列 perspective/blur/resample、单边候选外扩和 `build_rptsn()` 等底层工具。
- `boundary.cpp` 负责解释边界几何：`l_found`、`l_ok`、`l_pair_ok`、直线判定。
- `element.cpp` 只做元素互斥调度；已有 cross 继续优先，但 ring pending second、false-wait 和已确认 ring 会挡新 cross 入口。
- `cross.cpp` 只维护 cross 状态、远线点列和 `cross.track_type`；不发布 `rt->track.mid`。
- `ring.cpp` 只维护 ring 状态和检测/状态连续用边界；不重建当前帧控制候选。
- `mainline.cpp` 是当前帧唯一的控制中线 owner。
- `zebra.cpp` 只消费 mainline 给的 scan midline 和 raw image；不选择控制中线。
- `report.cpp` / `runners.cpp` 只输出诊断字段；不定义算法门槛。
- `control.cpp` 只消费 `track_line_found()`、`guide_error` 和停车状态；不重新解释视觉几何。

## 3. 元素对中线的影响

```text
build_frame_boundaries_and_candidates()
  -> 当前帧 rptsc0/rptsc1 已经生成
snapshot_ring_frame_start_action()
  -> 捕获帧首 ring 选边和 RUN 裁剪动作
element_process()
  -> cross/ring 状态推进
classify_frame_mode()
  -> cross_far / cross_near / ring / ordinary
apply_frame_start_element_crop()
  -> 只裁剪已存在的 rptsc0/rptsc1 点数
build_selected_midline()
  -> CROSS_IN farline 或 rptsc0/rptsc1 -> rt->track.mid
```

`ring.cpp` 可能在 `element_process()` 内补边或截边并刷新角点，但这只服务 ring 检测和状态连续；当前帧控制候选不会从 ring 修改后的 `boundary_t` 重建。

## 4. 已删除的旁路

这些不再属于当前主线：

```text
state_machine_enabled
FRONT_CAR_ELEMENTS
--force-cross-in
--force-ring
```

含义：元素状态必须从主链自然推进，不能靠 CLI 或环境变量伪造状态。

## 5. 当前有效验证入口

```bash
bash code/test.sh --host
```

如需离线行为证据，必须提供满足 `RAW_W x RAW_H` 的真实回放图像序列；文档截图不能作为 replay 输入。

## 6. 当前仍重但边界已定的地方

1. `mainline.cpp` 仍是帧级 orchestration owner；这是当前主链合同，不是未决边界。
2. `boundary.cpp` 同时做边界点解释、L 角和直线判定；这是 boundary 几何 owner，不是元素 owner。
3. `cross.cpp` 和 `ring.cpp` 保留状态树；是否调整 weak cross entry 或 ring 阈值属于行为证据门槛，不是 owner 未定。
4. `track_dualline()` 保留为明确实验入口；普通主线不主动选择 `TRACK_TYPE_DUAL`。

当前目标是职责清楚，而不是把核心算法硬塞回一个大文件。
