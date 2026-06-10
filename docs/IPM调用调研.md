# IPM 调用调研

这份文档记录当前 `port/autop-direct-reference-control` 分支的真实 IPM 合同。旧的
`ipm_table_generated.*`、`g_raw_to_ipm_*`、`g_ipm_to_raw_*` 和 `/root/ipm_matrix.txt`
主线路线已经删除，不再作为当前实现依据。

## 当前结论

当前主线只保留一个 IPM 真相源：

```text
autop_reference/Project/CODE/camera_param.c
```

这个文件使用 RT1064 参考版同名符号：

```text
K[3][3]
D[4]
H[3][3]
H_inv[3][3]
mapx[MT9V03X_CSI_H][MT9V03X_CSI_W]
mapy[MT9V03X_CSI_H][MT9V03X_CSI_W]
invx[MT9V03X_CSI_H][MT9V03X_CSI_W]
invy[MT9V03X_CSI_H][MT9V03X_CSI_W]
map_inv()
```

当前尺寸仍是本车运行时的 `160x120`，不是 RT1064 的 `376x240`。这是硬件输入尺寸差异，不是第二套 IPM 结构。

## 参考版合同

RT1064 参考版核心文件：

```text
RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/camera_param.c
RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/camera_param.h
```

参考版语义：

```text
mapx/mapy:
  raw 原图点 -> IPM 点

map_inv():
  IPM 点
  -> H 投影到去畸变原图坐标
  -> invx/invy 查回 raw 原图坐标
```

当前工程保持同一读取方式：算法和显示都通过 `camera_param.c` 的这些符号拿 IPM 数据。

## 当前代码路径

主算法路径：

```text
autop_reference/port/reference_step.c
  -> autop_reference_process_image()
  -> autop_reference_project_points_until_invalid(..., mapx, mapy)
  -> blur_points()
  -> resample_points()
  -> find_corners()
  -> check_cross() / run_cross()
  -> check_circle() / run_circle()
```

十字远线：

```text
autop_reference/Project/CODE/cross.c
  -> cross_farline()
  -> autop_reference_project_points_until_invalid(..., mapx, mapy)
```

上位机 / IPM 预览：

```text
code/tracking/perspective.cpp
  -> perspective_lookup_raw_to_ipm(): 读 mapx/mapy
  -> perspective_lookup_ipm_to_raw(): 调 map_inv()
```

构建入口：

```text
code/CMakeLists.txt
  -> ../autop_reference/Project/CODE/camera_param.c
```

## 为什么删除旧表

旧结构有第二套真相源：

```text
code/tracking/ipm_table_generated.hpp
code/tracking/ipm_table_generated.cpp
code/tracking/autop_reference_ipm_bridge.cpp
```

问题是它让参考算法看到的是被中间层填充后的表，而不是参考版自己的
`camera_param.c` 符号。当前分支已经删除这些文件，避免重新标定后又生成旧表。

## 当前标定工具输出

标定工具在：

```text
../TC264-Peripheral-perspective
```

它现在直接输出：

```text
camera_param.c
```

生成结果通过脚本安装：

```bash
bash scripts/ipm_recalib_capture.sh
cmake -S ../TC264-Peripheral-perspective -B ../TC264-Peripheral-perspective/build
cmake --build ../TC264-Peripheral-perspective/build
../TC264-Peripheral-perspective/build/ipm_generator \
  --input .diag/ipm_recalib/ipm_raw_640x360.png \
  --out .diag/ipm_recalib
bash scripts/ipm_recalib_apply.sh .diag/ipm_recalib/camera_param.c
```

安装后必须重新构建：

```bash
bash code/test.sh --host
bash code/test.sh
```

## 当前限制

当前 `TC264-Peripheral-perspective` 生成的是无畸变模型：

```text
K/D: 占位
H/H_inv: 真实四点单应矩阵
mapx/mapy: raw -> IPM 查表
invx/invy: identity 去畸变原图 -> raw 表
```

如果后面要补真实畸变，仍然应该继续生成同一个 `camera_param.c`，不要把旧
`ipm_table_generated.*` 或运行时 matrix 路线加回来。
