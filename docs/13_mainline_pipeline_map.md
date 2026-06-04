# 主流程快照

这份文档只保存当前 `front_car_mainline` 的活跃主链。详细阶段合同看 `../.agentdocs/tracking_mainline_contract.md`，复杂度判断看 `../.agentdocs/tracking_complexity_map.md`。

## 1. 当前主链

```text
app/main.cpp
-> run_mainline()
   -> live() / analyze() / replay()
      -> device_capture_gray() / device_load_gray()
      -> tracking_process_frame()
         -> find_seeds()
         -> trace_edges() / trace_single()
         -> build_boundary_from_trace()
         -> element_process()
         -> perspective_points() / blur_points() / resample_points()
         -> track_dualline() / track_leftline() / track_rightline()
      -> solve_runtime()
      -> print / display / assistant stream
```

主链只保留一条。不要再新增 parallel pipeline、shadow pipeline 或强制状态入口。

## 2. tracking 内部顺序

```text
raw gray
-> find_seeds
-> trace_edges / trace_single
-> build_boundary_from_trace
-> refresh_boundary_corners
-> element_process
-> perspective_points / blur_points / resample_points
-> track_dualline / track_leftline / track_rightline
-> center_x / guide_error writeback
```

关键边界：

- `imgproc.cpp` 负责原图 seed / trace，以及点级 perspective/blur/resample/track 中线工具。
- `boundary.cpp` 负责 boundary、corner、front boundary。
- `element.cpp` 只做 zebra / ring / cross 互斥调度。
- `cross.cpp`、`ring.cpp`、`zebra.cpp` 只处理各自状态树。

当前范围说明：

- 当前工程没有 `yroad` / 三叉模块。
- 当前“向参考工程对齐”只覆盖已存在的 `tracking / cross / ring / zebra / control` 主线。
- 三叉属于参考工程额外能力，不当作当前主链里的收直项。

## 3. 已删除的旁路

这些不再属于当前主线：

```text
state_machine_enabled
FRONT_CAR_ELEMENTS
--force-cross-in
--force-ring
```

含义：元素状态必须从主链自然推进，不能靠 CLI 或环境变量伪造状态。

## 4. 当前有效验证入口

```bash
bash "scripts/test.sh" --host
bash "scripts/straight_baseline_audit.sh"
bash "scripts/ipm_geometry_audit.sh"
```

下面这些旧入口不再作为主线通过条件：

```text
scripts/behavior_equivalence.sh
```

`cross_farline_audit.sh` 和 `ring_track_type_audit.sh` 已从仓库删除，因为它们过去依赖强制状态旁路。
`behavior_equivalence.sh` 已退休，因为当前不再保留 `front_car_mainline_legacy` 旧路线。

## 5. 当前还重的地方

优先级从高到低：

1. `boundary.cpp` 仍混合 boundary / corner / front boundary。
2. `mainline.cpp` 已删 frame wrapper，但仍负责元素前后粘合。
3. `imgproc.cpp` 已合并 seed / trace / midline，后续只清内部短函数名。
4. `cross.cpp` / `ring.cpp` 暂时保留状态树，不先重写。

不要把问题误判成“文件越少越好”。当前目标是职责清楚，而不是把核心算法硬塞回一个大文件。
