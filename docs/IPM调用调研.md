# IPM 调用调研

这份文档只记录当前 `front_car_mainline` 与参考版 IPM 的真实对齐状态，不再保留旧的 matrix 主线路线描述。

## 1. 参考版 IPM 结构

参考版主要位置：

```text
RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/camera_param.c
RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/camera_param.h
RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/imgproc.c
RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/cross.c
```

### 1.1 camera_param.c / camera_param.h

参考版声明了两类矩阵和两类查表：

```text
K / D：相机内参和畸变参数。
H：俯视 -> 去畸变原图。
H_inv：去畸变原图 -> 俯视。
mapx[240][376] / mapy[240][376]：raw 原图点 -> IPM 点。
invx[240][376] / invy[240][376]：IPM 反查到 raw 原图点。
```

`map_inv()` 的语义是：

```text
IPM 点
-> H 算到去畸变图坐标
-> invx / invy 查回原图 raw 坐标
```

这说明参考版 IPM 不只是 3x3 透视矩阵，还把畸变链一起编进整体映射。

### 1.2 imgproc.c::remap()

参考版 `remap()` 是图像级重映射：

```text
img0 原图
-> 对每个像素查 mapx / mapy
-> 生成 img1 俯视图
```

这个是整图 remap，不等于边线点列投影。

### 1.3 cross.c 十字远线

参考版十字远线直接把 raw 点列查表成 IPM 点列：

```c
far_rpts0[i][0] = mapx[far_ipts0[i][1]][far_ipts0[i][0]];
far_rpts0[i][1] = mapy[far_ipts0[i][1]][far_ipts0[i][0]];
```

对应流程：

```text
far_ipts0 / far_ipts1 raw 点列
-> mapx[y][x] / mapy[y][x]
-> far_rpts0 / far_rpts1 IPM 点列
-> blur_points()
-> resample_points()
-> local_angle_points()
-> nms_angle()
-> 找远线 L 点
```

关键点：

```text
参考版十字远线不是先生成整张 IPM 图再追线，
而是在 raw 图上追线后，把 raw 点列逐点映射成 IPM 点列。
```

## 2. 当前工程 IPM 结构

当前工程主要位置：

```text
code/app/main.cpp
code/tracking/perspective.cpp
code/tracking/perspective.hpp
code/tracking/ipm_table_generated.hpp
code/tracking/ipm_table_generated.cpp
code/tracking/imgproc.cpp
code/tracking/boundary.cpp
code/tracking/mainline.cpp
code/tracking/cross.cpp
code/tracking/ring.cpp
```

### 2.1 启动入口已经切成静态表

当前 `code/app/main.cpp` 启动逻辑是：

```text
tracking_reset(&g_rt)
-> g_rt.has_matrix = 1
-> 打印 "front_car_mainline: ipm=static table"
```

当前含义：

```text
主链 IPM 已经不再依赖 /root/ipm_matrix.txt。
运行时不再加载 matrix 文件，不再走 matrix 成功/失败分支。
当前工程把静态表直接编进程序，主链固定使用静态查表。
```

### 2.2 perspective.cpp 现在只保留查表封装

`code/tracking/perspective.cpp` 当前已经收成查表实现，主入口是：

```text
perspective_lookup_raw_to_ipm()
perspective_lookup_ipm_to_raw()
perspective_point()
perspective_preview()
```

其中：

```text
perspective_lookup_raw_to_ipm()：raw 点查 g_raw_to_ipm_x/y。
perspective_lookup_ipm_to_raw()：IPM 点查 g_ipm_to_raw_x/y。
perspective_point()：单点投影，失败写 (-1,-1)。
perspective_preview()：IPM 图逐像素反查 raw 灰度。
```

`perspective.hpp` 里保留的 `matrix` 参数现在只是兼容旧调用签名，当前实现内部已经 `(void)matrix`，不再依赖传入矩阵。

### 2.3 静态表位置

当前查表产物放在当前工程内部：

```text
code/tracking/ipm_table_generated.hpp
code/tracking/ipm_table_generated.cpp
```

数组为：

```text
g_raw_to_ipm_x[RAW_H][RAW_W]
g_raw_to_ipm_y[RAW_H][RAW_W]
g_ipm_to_raw_x[IPM_H][IPM_W]
g_ipm_to_raw_y[IPM_H][IPM_W]
```

这四张表已经直接编进 `front_car_mainline`，不是外部 include，也不是运行时再加载别处文件。

### 2.4 imgproc.cpp::perspective_points() 已按参考版对齐

当前 tracking 主链最常用的点列投影入口仍然是：

```cpp
int perspective_points(const point_t *raw_pts,
                       int raw_num,
                       const double *matrix,
                       int has_matrix,
                       double pts[POINT_MAX][2]);
```

但内部语义已经改成：

```text
raw 点列
-> has_matrix 为真时逐点查 g_raw_to_ipm_x/y
-> 查表失败写 (-1, -1)
-> 输出点数保持和输入点数一致
```

这里最重要的对齐点是：

```text
对齐参考版 cross.c：raw 点列逐点查表，不再做“前段跳过、后段截断”。
```

也就是：

```text
far_rpts_num = far_ipts_num
```

这一条现在已经在 `perspective_points()` 里落地。

主要调用点仍然是：

```text
mainline.cpp::build_rpts0()
mainline.cpp::build_rpts1()
cross.cpp::build_cross_farline()
ring.cpp::refresh_ring_corners()
```

另外，环岛阶段“跟内圈/跟外圈”的切边逻辑不在 `ring.cpp` 内部直接改 `track_type`，
而是在 `mainline.cpp` 里按 `ring.kind + ring.state` 选择：

```text
BEGIN/RUN/END：跟外圈
IN/OUT：跟内圈
```

这和参考版 `circle.c` 的阶段切边节奏一致。

### 2.5 boundary.cpp 这条链现在并到主线 float 点列链

`boundary.cpp` 现在不再单独维护 `point_t` 版 blur/resample 链，已经直接复用主线这一套：

```text
trace raw 点列
-> perspective_points()
-> blur_points()
-> resample_points()
-> boundary.work_pts
-> round 到 boundary.now_pts
```

其中 `perspective_points()` 当前语义是：

```text
逐点查表；
失败点写 (-1,-1)；
输出点数保持和输入一致。
```

后续 `blur_points()` / `resample_points()` 只处理第一段连续有效点列，所以 `boundary`、`mainline`、`cross`、`ring` 看到的是同一套 float 点列主链。

另外，`find_raw_corner()` 现在在 raw->IPM 映射失败时会直接跳过该 raw 点，不再偷偷回退到 raw 原坐标做最近点匹配。

## 3. 当前与参考版的真实差异

### 3.1 点列调用结构已基本对齐

参考版十字远线：

```text
raw 点列 -> mapx/mapy -> IPM 浮点点列
```

当前主链：

```text
raw 点列 -> g_raw_to_ipm_x/y -> IPM 浮点点列
```

这一层已经对齐，且调用集中在 `perspective_points()`，没有把查表散落到各元素文件里。

### 3.2 出界策略已经对齐到两条点列链

当前状态要分开看：

```text
perspective_points()：已对齐参考版，逐点查表，输出点数保持不变，失败点写 (-1,-1)。
boundary 主链：已经并到 perspective_points() -> blur_points() -> resample_points()。
```

所以如果问题是“十字远线 / 主链 rpts 是否已按参考版处理”，答案是：

```text
是，已经对齐。
```

如果问题是“当前工程所有 IPM 投影语义是否都和参考版一样”，答案是：

```text
还不是，结构承载仍是当前工程自己的 boundary_t，不是参考版原样数组；另外完整畸变链也还没补齐。
```

### 3.3 畸变链还没有真正补齐，只留了占位

`ipm_table_generated.hpp` 当前已经明确写了占位说明：

```text
当前表由 3x3 单应矩阵离线生成；
后续若补齐 K/D 畸变数据，应重新生成本表，调用侧不再改。
```

这表示当前工程已经把“未来补 K/D 畸变链”的接口位置留住了，但现在还没有伪造一套假的畸变模型。

也就是说：

```text
当前已经对齐了“静态查表式调用结构”；
当前还没有对齐参考版完整的 K / D / invx / invy 畸变链能力。
```

### 3.4 g_ipm_to_raw_x / y 里存在 -1 是正常现象

当前 `perspective_lookup_ipm_to_raw()` 的判断是：

```text
只要 g_ipm_to_raw_x/y 某点为负，就认为这个 IPM 点无法有效反查回 raw。
```

因此表中存在 `-1` 代表的是：

```text
该 IPM 像素没有合法 raw 来源，或者离线生成时判断为出界。
```

这类点在 `perspective_preview()` 里会保持白色，在回绘时会被当成无效点跳过。只要这些 `-1` 分布符合标定覆盖范围，就不是错误。

## 4. 当前已经完成的对齐项

### 4.1 运行时 matrix 主线已移除

当前已经不再：

```text
启动时读 /root/ipm_matrix.txt
根据加载成功与否决定是否启用 IPM
在主链里实时做 matrix 投影
```

### 4.2 静态表已经内置在当前工程

当前已经：

```text
把 ipm_table_generated.hpp/.cpp 放进 front_car_mainline
在 code/CMakeLists.txt 里显式加入 tracking/ipm_table_generated.cpp
不再外部 include ipm_autocal 目录
```

### 4.3 raw 点列主线已经改成查表

当前已经：

```text
perspective_points() 逐点查 g_raw_to_ipm_x/y
失败点写 (-1,-1)
输出点数保持和输入点数一致
```

这正是参考版 `cross.c` 的核心风格。

### 4.4 反查链也已经切到静态表

当前已经：

```text
perspective_preview() 用 g_ipm_to_raw_x/y 反查灰度
assistant.cpp 用 g_ipm_to_raw_x/y 回绘原图
zebra.cpp 用 g_ipm_to_raw_x/y 把中线点反投回原图
```

## 5. 当前未完成的对齐项

### 5.1 完整畸变链未补

当前表大概率仍只是 3x3 单应矩阵离线预计算结果，不等价于参考版完整的：

```text
K / D + H / H_inv + invx / invy
```

所以后续如果用户补齐对应标定数据，应该做的是：

```text
重新生成 g_raw_to_ipm_x/y 和 g_ipm_to_raw_x/y
```

而不是再去改调用侧代码。

## 6. 当前结论

```text
1. 当前 front_car_mainline 的 IPM 主线已经切到静态查表，不再走运行时 matrix 主线。
2. 当前 raw 点列主线已经对齐参考版：逐点查表，输出点数保持和输入点数一致。
3. 当前静态表已经内置到 front_car_mainline，不再外部引用 ipm_autocal。
4. 当前已为参考版畸变链建立占位，但还没有补齐真实 K/D 数据。
5. 当前主链统一通过 perspective_points() 进入 IPM 浮点点列，不再保留旧的 point_t 边界投影主链。
6. 当前如果后续补齐新的标定能力，应重生成表，不应再把复杂度加回调用主链。
```

## 7. 后续只需要盯住一件事

```text
1. 如果补齐 K/D 畸变数据，只重生成 ipm_table_generated.cpp，不改调用侧。
```
