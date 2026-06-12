# IPM 调用调研

这份文档记录当前 `port/atg2022-reference-control` 分支的真实 IPM 合同。旧 RT1064 路线里的 `camera_param.c`、`mapx/mapy` 查表、`autop_reference` IPM bridge 和运行时 `/root/ipm_matrix.txt` 都不是当前生产路径；`autop_reference/` 代码树也已经从当前分支删除。

## 当前结论

当前主线只保留一个 IPM 真相源：

```text
atg_reference/Project/CODE/shy_Image.c
  -> rot[3][3]
  -> inv_rot[3][3]
  -> Cal_rot_x() / Cal_rot_y()
  -> Cal_inv_rot_x() / Cal_inv_rot_y()
```

`rot` 表示 raw 原图坐标到 ATG IPM 坐标的单应矩阵，`inv_rot` 表示 IPM 坐标反投回 raw 原图坐标的单应矩阵。当前运行尺寸仍是本车的 `160x120`，不是上游 ATG/RT 工程的原始相机尺寸。

尺度合同也必须同源：当前 ATG 参数是 `ROAD_WIDTH=0.45m`、`pixel_per_meter=116`，因此 IPM 里的赛道宽度应约为 `52.2px`。标定生成器的默认目标矩形按这个宽度生成，避免 `sample_dist`、`pixel_per_meter` 和元素距离门槛互相打架。

## 当前代码路径

ATG 算法路径：

```text
atg_reference/port/reference_step.c
  -> atg_reference_process_frame(gray, encoder_total)
  -> image_handle()
  -> find_corners()
  -> check_round/check_Half/Check_ramp/check_circle/check_yroad
  -> run_round/Run_Ramp/run_cross/run_circle/run_yroad
  -> selected rptsn
```

其中 IPM 投影由 ATG 原始函数负责：

```text
atg_reference/Project/CODE/shy_Image.c
  -> Cal_rot_x() / Cal_rot_y()        # raw -> IPM
  -> Cal_inv_rot_x() / Cal_inv_rot_y()# IPM -> raw
```

上位机 / IPM 预览也走同一套函数：

```text
code/tracking/perspective.cpp
  -> perspective_lookup_raw_to_ipm(): 调 Cal_rot_x()/Cal_rot_y()
  -> perspective_lookup_ipm_to_raw(): 调 Cal_inv_rot_x()/Cal_inv_rot_y()
```

构建入口：

```text
code/CMakeLists.txt
  -> ../atg_reference/Project/CODE/shy_Image.c
```

## 为什么不再使用 camera_param.c

旧 RT1064 移植分支曾经使用：

```text
autop_reference/Project/CODE/camera_param.c
mapx/mapy/invx/invy/map_inv()
```

这条路线现在已经不是 ATG 分支的生产合同，相关 `autop_reference/` 代码也不再保留在当前分支。ATG 算法本身直接调用 `Cal_rot_*` / `Cal_inv_rot_*`，如果继续把标定结果写进旧 `camera_param.c`，算法层和显示层会看到不同 IPM 来源，反而形成第二套真相源。

## 当前标定工具输出和应用

标定工具仍在本仓：

```text
tools/ipm_generator
```

它会生成预览图和矩阵文件：

```text
selected_points.json
ipm_matrix_initial.txt
ipm_matrix_tuned.txt
preview_original_points.png
preview_ipm_initial.png
preview_ipm_tuned.png
camera_param.c              # 兼容旧生成器输出，当前 ATG 分支不直接应用它
```

当前 ATG 分支真正应用的是：

```bash
bash scripts/ipm_recalib_apply.sh .diag/ipm_recalib/ipm_matrix_tuned.txt
```

这个脚本会把 `ipm_matrix_tuned.txt` 转成 ATG 的矩阵排布，并替换：

```text
atg_reference/Project/CODE/shy_Image.c::rot
atg_reference/Project/CODE/shy_Image.c::inv_rot
```

为了兼容旧命令，如果传入 `.diag/ipm_recalib/camera_param.c`，脚本会自动改用同目录下的 `ipm_matrix_tuned.txt`。

环岛补线里需要从 raw 底边左右锚点投到 IPM。当前 port 使用 `MT9V03X_W/H` 推导的锚点，不再保留 ATG 原作者 188 宽图像下的 `180/185` 旧坐标。

应用后必须重新构建：

```bash
bash code/test.sh --host
bash code/test.sh
```

## 当前限制

当前 `tools/ipm_generator` 使用的是四点无畸变单应矩阵模型。它不做镜头畸变建模；如果后面要补真实畸变，也应该先明确 ATG `Cal_rot_*`/`Cal_inv_rot_*` 的新合同，不要把旧 `camera_param.c` 查表路线重新接回生产主线。

## 相关文档

- [IPM 重标定流程（SOP）](IPM重标定流程.md) — 队友可直接执行的操作手册
- [PORTING.md](../atg_reference/PORTING.md) — ATG port 边界和控制参数
