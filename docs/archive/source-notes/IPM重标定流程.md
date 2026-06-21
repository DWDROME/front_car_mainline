# IPM 重标定流程（SOP）

这份文档是**队友可独立执行**的操作手册。不需要理解 IPM 算法或参考代码结构，按步骤走就能完成重标定并验收。

---

## 1. 什么时候需要重标定

不是每次跑车前都要做。只有以下情况才需要：

| 场景 | 是否需要重标定 |
|------|---------------|
| 中线远端明显向左/向右偏 | **需要** |
| 相机被碰过、重新固定过 | **需要** |
| 换了新的硬件（相机模组、镜头） | **需要** |
| 软件更新但没动相机 | 不需要 |
| 第一次在新车上部署 | **需要** |
| IPM 预览里直线赛道看起来明显弯曲 | **需要** |

如果不确定，先跑验收审计看当前状态（见第 4.5 节）。

---

## 2. 前置条件

开始之前确认以下条件都满足：

### 2.1 本机（你的电脑）

```bash
# 必须有 ffmpeg
ffmpeg -version

# 必须有 cmake 和 OpenCV（用于编译 ipm_generator）
cmake --version
pkg-config --modversion opencv4
```

如果没有 OpenCV：
```bash
sudo apt install libopencv-dev cmake
```

### 2.2 板端（小车上的 LS2K0300）

- 板端能 ping 通：默认 IP `192.168.0.102`
- 能 SSH 上去：`ssh root@192.168.0.102`（免密或知悉密码）
- 板端 `/root/` 下有 `front_car_mainline` 可执行文件
- 相机已经接好、镜头没有盖子

确认板端连通性：
```bash
ping -c 2 192.168.0.102
ssh root@192.168.0.102 "ls -l /root/front_car_mainline"
```

### 2.3 环境变量（可选覆盖）

脚本内置了默认值，大多数情况不需要改。如果需要自定义：

| 变量 | 默认值 | 说明 |
|------|--------|------|
| `REMOTE_IP` | `192.168.0.102` | 板端 IP |
| `REMOTE_USER` | `root` | SSH 用户 |
| `REMOTE_RAW` | `/tmp/ipm_raw_capture.png` | 板端抓图路径 |

---

## 3. 一键流程

从项目根目录执行，顺序不能乱：

```bash
# 步骤 1：从板子抓一张 640x360 灰度标定图
bash scripts/ipm_recalib_capture.sh

# 步骤 2：在图上交互点选四个点，生成 IPM 矩阵和预览图
bash scripts/ipm_recalib_generate.sh

# 步骤 3：把生成的矩阵写入 ATG rot/inv_rot
bash scripts/ipm_recalib_apply.sh .diag/ipm_recalib/ipm_matrix_tuned.txt

# 步骤 4：编译验证（host + target）
bash code/test.sh --host
bash code/test.sh

# 步骤 5：审计验收
bash scripts/ipm_geometry_audit.sh
```

如果一切顺利，走完这五步就完成了。

---

## 4. 详细操作说明

### 4.1 步骤 1：抓图

```bash
bash scripts/ipm_recalib_capture.sh
```

这个脚本做的事：
1. SSH 到板端，停掉正在跑的 `front_car_mainline`
2. 用 `--capture-frame` 抓一张当前相机的原始灰度图（160x120）
3. scp 拉回本机
4. 用 ffmpeg 放大到 640x360（最近邻，不模糊）
5. 把板端进程重新拉起来（assistant 模式，不驱动电机）

产出文件：
```text
.diag/ipm_recalib/ipm_raw_160x120.png   ← 原始尺寸
.diag/ipm_recalib/ipm_raw_640x360.png   ← 标定输入（用这个）
```

**关键要求**：抓图时小车必须停在赛道上，相机对着赛道。图像里要能看到赛道的左右边界线。

### 4.2 步骤 2：点选四点

```bash
bash scripts/ipm_recalib_generate.sh
```

这会弹出一个 OpenCV 窗口，显示 640x360 的赛道灰度图。

#### 怎么选点

你需要按顺序点击**四个点**，这四个点围成一个**矩形**，代表赛道上的一个矩形区域（已知尺寸的标定参考区域）：

```
点 1（left-bottom）  →  矩形左下角，左边界线上
点 2（right-bottom） →  矩形右下角，右边界线上
点 3（left-top）     →  矩形左上角，左边界线上
点 4（right-top）    →  矩形右上角，右边界线上
```

**选点原则**：
- 四个点要在赛道上围成一个**真实世界中的矩形**（比如赛道的某一段直道区域）
- 左右点分别落在赛道的**左边界线**和**右边界线**上
- 上下两对点的间距应该大致相等（赛道宽度在近处和远处看上去不一样，但实际宽度不变）
- 尽量选**近处**的点（图像下半部分），因为近处像素更多、更准确
- 不要选弯道里的点——选**直道段**

#### 窗口操作

| 按键 | 作用 |
|------|------|
| 鼠标点击 | 按顺序放点 |
| `u` | 撤销上一个点 |
| `r` | 清空所有点，重新开始 |
| `Enter` 或 `Space` | 四个点放完后确认 |
| `Esc` | 放弃，退出 |

#### 点选后的预览

确认后会生成三张预览图，在 `.diag/ipm_recalib/` 下：

| 文件 | 内容 |
|------|------|
| `preview_original_points.png` | 你选的四个点在原图上的位置 |
| `preview_ipm_initial.png` | 初始 IPM 投影结果 |
| `preview_ipm_tuned.png` | 调优后的 IPM 投影结果（最终使用的） |

**怎么看 preview_ipm_tuned.png**：
- 赛道左右边界线应该近似**竖直**
- 左右边界之间的宽度应接近 **52px**（当前 ATG 参数 `ROAD_WIDTH=0.45m`、`pixel_per_meter=116`）
- 如果边界线明显倾斜，说明点选的位置不够好，重新选
- 如果边界是直的但宽度明显不是 52px，说明 IPM 尺度和 ATG 距离阈值不一致，也需要重做

#### 非交互模式（自动化/CI）

如果已经知道四个点的像素坐标，可以跳过交互窗口：

```bash
bash scripts/ipm_recalib_generate.sh \
  .diag/ipm_recalib/ipm_raw_640x360.png \
  .diag/ipm_recalib \
  --points x1,y1,x2,y2,x3,y3,x4,y4 \
  --no-window
```

点顺序仍然是 left-bottom, right-bottom, left-top, right-top。坐标必须在 640x360 范围内。

### 4.3 步骤 3：应用

```bash
bash scripts/ipm_recalib_apply.sh .diag/ipm_recalib/ipm_matrix_tuned.txt
```

这个脚本做的事：
1. 检查 `ipm_matrix_tuned.txt` 是否是 3x3 单应矩阵
2. 计算反矩阵并转换成 ATG 的矩阵排布
3. 替换 `atg_reference/Project/CODE/shy_Image.c` 里的 `rot` 和 `inv_rot`

如果矩阵文件缺失、格式不对或不可逆，会直接报错退出。

兼容说明：如果误传 `.diag/ipm_recalib/camera_param.c`，脚本会自动改用同目录下的 `ipm_matrix_tuned.txt`。当前 ATG 分支真正生效的是 `shy_Image.c::rot/inv_rot`，不是旧 `camera_param.c`。

**不会**自动提交 git——应用后你需要自己确认效果再提交。

### 4.4 步骤 4：编译

```bash
bash code/test.sh --host    # 本机编译
bash code/test.sh            # 交叉编译（需要工具链）
```

两份都通过才算编译成功。`code/test.sh` 需要交叉编译工具链；如果本机没有，至少保证 `--host` 通过。

### 4.5 步骤 5：审计验收

```bash
bash scripts/ipm_geometry_audit.sh
```

验收标准（全部满足才算通过）：

| 检查项 | 怎么判断 |
|--------|---------|
| 编译通过 | `code/test.sh --host` 和 `code/test.sh` 都返回 0 |
| IPM 预览直道近似竖直 | 看 `preview_ipm_tuned.png`，边界线不应明显倾斜 |
| IPM 赛道宽度接近 52px | 当前 ATG `0.45m * 116px/m = 52.2px`，偏差太大会影响元素距离门槛 |
| 中线不系统性偏移 | 跑直道时 `control_ref` 的 x 坐标不应持续偏左或偏右 |
| `m0` 和 `ml` 接近 | report 里 `m0.x` 和 `ml.x` 差异小 |

---

## 5. 输出文件一览

重标定过程中生成的所有文件都在 `.diag/ipm_recalib/` 下：

| 文件 | 阶段 | 说明 |
|------|------|------|
| `ipm_raw_160x120.png` | 抓图 | 板端相机原始灰度图 |
| `ipm_raw_640x360.png` | 抓图 | 放大到 640x360 的标定输入图 |
| `selected_points.json` | 生成 | 你选的四个点的坐标 |
| `ipm_matrix_initial.txt` | 生成 | 初始单应矩阵 |
| `ipm_matrix_tuned.txt` | 生成 | 调优后的单应矩阵 |
| `preview_original_points.png` | 生成 | 原图 + 标记的四个点 |
| `preview_ipm_initial.png` | 生成 | 初始 IPM 投影预览 |
| `preview_ipm_tuned.png` | 生成 | 最终 IPM 投影预览 |
| `camera_param.c` | 生成 | 旧 RT1064 查表格式的兼容产物，当前 ATG 分支不直接应用 |

当前 ATG 分支最终生效的是 `ipm_matrix_tuned.txt` 经 `ipm_recalib_apply.sh` 写入后的 `atg_reference/Project/CODE/shy_Image.c::rot/inv_rot`。其他文件用于调试和审计。

---

## 6. 常见问题与故障排除

### 6.1 连不上板子

```
ssh: connect to host 192.168.0.102 port 22: No route to host
```

- 检查网线是否插好
- 检查板端是否已开机
- 检查本机和板端是否在同一网段
- 如果 IP 不是默认的 `192.168.0.102`，设置环境变量：
  ```bash
  REMOTE_IP=192.168.0.xxx bash scripts/ipm_recalib_capture.sh
  ```

### 6.2 没有 ffmpeg

```
ERROR: ffmpeg is required
```

```bash
sudo apt install ffmpeg
```

### 6.3 图像不是 640x360

`ipm_generator` 要求输入必须是 640x360 灰度图。抓图脚本已经用 ffmpeg 做了缩放，通常不会出问题。

如果手动准备图片：
```bash
ffmpeg -i your_image.png -vf "scale=640:360:flags=neighbor,format=gray" input_640x360.png
```

### 6.4 点选顺序反了

**这是最常见的错误。** 顺序必须是：
```
left-bottom → right-bottom → left-top → right-top
```

如果顺序反了，生成的 IPM 投影会是乱的（图像翻转、镜像、严重扭曲）。解决：重新运行 `ipm_recalib_generate.sh`。

### 6.5 矩阵文件格式不对

```
ERROR: expected 3 rows ...
ERROR: expected 3 columns ...
ERROR: IPM matrix is singular
```

说明 `ipm_matrix_tuned.txt` 不是有效 3x3 单应矩阵，或矩阵不可逆。检查是否用了最新的 `tools/ipm_generator` 代码，必要时重新生成：
```bash
rm -rf tools/ipm_generator/build
bash scripts/ipm_recalib_generate.sh
```

### 6.6 编译失败

先确认 `shy_Image.c` 里已经写入新的 `rot/inv_rot`：
```bash
sed -n '1,28p' atg_reference/Project/CODE/shy_Image.c
```

如果 `rot` / `inv_rot` 仍是旧值，说明应用脚本没有执行成功。

### 6.7 重标定后效果更差

- 检查四个点是否围成一个合理的矩形（不是一个很扁或很歪的四边形）
- 检查是否选在了直道上（不是弯道）
- 检查小车抓图时是否停在赛道正中
- 看 `preview_ipm_tuned.png` 判断投影质量
- 如果不行，回滚（见第 7 节）后重做

---

## 7. 回滚

如果重标定后效果变差，用 git 恢复：

```bash
# 查看当前状态
git diff atg_reference/Project/CODE/shy_Image.c

# 回滚到上一个提交的版本
git checkout -- atg_reference/Project/CODE/shy_Image.c

# 重新编译
bash code/test.sh --host
bash code/test.sh
```

---

## 8. 禁止事项

这些操作**不要**做：

| 禁止 | 原因 |
|------|------|
| 恢复 `ipm_table_generated.*` 文件 | 这些文件已删除，旧路线有第二套真相源，会导致算法看到不一致的 IPM 数据 |
| 使用 `/root/ipm_matrix.txt` | 旧路线，不再作为当前实现依据 |
| 改旧 tracking 实现 | 当前分支已删除旧 tracking，只有 ATG `rot/inv_rot` 一条生产路线 |
| 手动编辑 `rot/inv_rot` | 必须由 `ipm_generator` 生成矩阵再应用，手工改容易破坏坐标排布 |
| 跳过编译步骤 | 不编译就无法确认 `shy_Image.c` 和代码兼容 |

---

## 9. 相关文档

- [IPM 调用调研](IPM调用调研.md) — 当前 IPM 合同和代码路径
- [PORTING.md](../atg_reference/PORTING.md) — port 边界和控制参数
- [tools/README.md](../tools/README.md) — 工具入口索引
- [ipm_generator README](../tools/ipm_generator/README.md) — 生成器详细说明
