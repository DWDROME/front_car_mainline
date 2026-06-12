# tools

> **IPM 重标定？** 如果你是来重标定相机的，直接看 [IPM 重标定流程（SOP）](../docs/IPM重标定流程.md)。那个文档不需要理解算法，按步骤走就行。

当前推荐入口在 `scripts/`。`tools/` 只保留实际执行体、历史兼容入口和少量人工辅助脚本。

## 常用验证

```bash
bash "scripts/test.sh" --host
bash "scripts/straight_baseline_audit.sh" ".diag/front_car_capture_live_current.png"
bash "scripts/ipm_geometry_audit.sh"
```

## 当前主线入口

```text
scripts/test.sh                 编译 host/target
scripts/straight_baseline_audit.sh  直道 baseline 审计
scripts/ipm_geometry_audit.sh       IPM 几何只读审计
scripts/ipm_recalib_capture.sh      从当前板子抓一张 IPM 重标定灰度图
scripts/ipm_recalib_generate.sh     交互点选四点并生成 IPM 矩阵和预览图
scripts/ipm_recalib_apply.sh        把生成的矩阵写入 ATG shy_Image.c::rot/inv_rot
```

`tools/straight_baseline_audit.sh` 和 `tools/ipm_geometry_audit.sh` 是实际执行体；用户侧优先走 `scripts/` 包装入口。

## 已退休入口

```text
scripts/behavior_equivalence.sh
```

原因：这些入口依赖旧新双路线或强制状态旁路。现在只保留当前主链，状态树必须自然推进，不能通过 CLI 伪造 `cross/ring` 状态。

`tools/cross_farline_audit.sh` 和 `tools/ring_track_type_audit.sh` 已删除，不再保留仓库占位脚本。

## 降级入口

```text
tools/board_current_smoke.sh
tools/control_center_sensitivity_audit.sh
```

这些只能作为手动历史审计或现场辅助，不作为当前主线通过门禁。

## 图传 / 显示

当前仓库不再保留 `start_viewer_gui.sh` 和 `start_viewer_tunnel_background.sh`。
图传、IPS200、本地打印都是旁路；怀疑拖慢主循环时先关闭：

```bash
SMARTCAR_ASSISTANT=0 FRONT_CAR_DISPLAY=0 ./front_car_mainline
```

## live / analyze

板端直接运行：

```bash
cd "/home/root"
./front_car_mainline
```

抓当前帧：

```bash
./front_car_mainline --capture-frame /tmp/front_car_capture.png
```

重标定抓图：

```bash
bash "scripts/ipm_recalib_capture.sh"
```

点选四点：

```bash
bash "scripts/ipm_recalib_generate.sh"
```

应用新 ATG IPM 矩阵：

```bash
bash "scripts/ipm_recalib_apply.sh" ".diag/ipm_recalib/ipm_matrix_tuned.txt"
```

离线诊断：

```bash
./front_car_mainline --analyze /tmp/front_car_capture.png --report /tmp/front_car_report.txt --ipm /tmp/front_car_ipm.png
```

## 当前约束

- 默认输入坐标按 `160x120` 解释。
- IPM 标定结果只通过 `atg_reference/Project/CODE/shy_Image.c` 的 `rot/inv_rot` 接入。
- `ring / cross` 只走自然状态树，不再保留运行时禁用旁路。
- 删除 retired 脚本或旧 `.diag` 生成物前需要明确确认。
