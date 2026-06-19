# ATG 尺度合同与参数来源审计

时间：2026-06-19

本文记录 `pixel_per_meter`、`sample_dist`、IPM 尺度和角点阈值之间的来源、推送记录证据和风险判断。重点是把“哪些有提交理由”“哪些只是初始 port 参数”分清楚。

## 当前结论

| 项 | 当前判断 |
| --- | --- |
| `pixel_per_meter=116` | 有明确的后续提交理由：当前 IPM 生成器按 `ROAD_WIDTH=0.45m` 和 `pixel_per_meter=116` 生成目标赛道宽度，约 `52.2px`。 |
| `sample_dist=0.02f` | 当前已恢复到参考版物理采样步长。历史上的 `0.03f` 来自 ATG port 初建提交，但没有找到同等级别的提交说明解释为什么从参考版 `0.02` 改成 `0.03`。 |
| 参考版阈值能否照搬 | 不能直接照搬。`sample_dist` 已恢复为参考版 `0.02`，但 `pixel_per_meter=116`、IPM 标定、二值化参数和摄像头视角仍与参考版不同。 |
| 当前最大风险 | `pixel_per_meter=116` 和 IPM 宽度合同是自洽的；`sample_dist=0.02` 恢复了角度窗口和 id 门限的参考版物理语义，但角点阈值和实际板端 `best_conf` 仍需要实测闭环。 |

补充校正：角度算法本身对 IPM 坐标的统一缩放不敏感。若 IPM 标定和 `pixel_per_meter` 是自洽的，单独把坐标统一放大不会改变 `local_angle_points()` 的夹角。真正直接改变 `conf` 的主要是 `sample_dist` 与 `angle_dist` 决定的离散角度窗口，以及 IPM 非线性/边线提取误差带来的真实点列形状变化。`line_blur_kernel` 也会影响角点尖锐度，但它在代码里发生在 `resample_points()` 之前，真实物理平滑长度取决于原始追线点列经 IPM 后的间距，不能简单用 `sample_dist` 换算。`pixel_per_meter` 的风险在于它定义全局 IPM 尺度和外扩/距离合同，不应被简单当成角度变小的直接原因。

## Git 证据链

### 1. `fad5e28` 初始引入当前 port 参数

提交：

```text
fad5e28 feat(atg-ref): 搭建 ATG2022 算法主线
```

提交说明重点：

- 从 RT1064 参考基线切出 `port/atg2022-reference-control`。
- 把 ATG2022 算法源码按 `atg_reference/Project` 结构收进仓库。
- `Project/CODE` 基本保持原样，适配逻辑集中在 `atg_reference/port` 和 `code/tracking/atg_reference_mainline.cpp`。

该提交在 `atg_reference/port/reference_globals.c` 和 `atg_reference/port/reference_step.c` 中引入当前 port 默认参数：

```c
block_size = 5;
clip_value = 8;
line_blur_kernel = 7;
sample_dist = 0.03f;
pixel_per_meter = 116;
angle_dist = 0.2f;
ROAD_WIDTH = 0.45f;
```

审计判断：

- 这是历史 `sample_dist=0.03f` 和 `pixel_per_meter=116` 进入 ATG port 的起点。
- 该提交说明没有单独解释为什么参考版 `sample_dist=0.02`、`pixel_per_meter=41` 被改成 `0.03`、`116`。
- 因此，`fad5e28` 能证明“何时引入”，不能证明“为什么这样定”。

### 2. `38deb58` 给 `pixel_per_meter=116` 建立 IPM 宽度合同

提交：

```text
38deb58 feat(atg-ref): 收敛 ATG 控制链路和 IPM 标定
```

提交说明中的明确合同：

```text
IPM 尺度与 ROAD_WIDTH=0.45、pixel_per_meter=116 对齐，目标赛道宽度约 52.2px。
```

该提交修改 `tools/ipm_generator/src/ipm_generator.cpp`：

```c
constexpr float kAtgRoadWidthMeters = 0.45f;
constexpr float kAtgPixelPerMeter = 116.0f;
constexpr float kTargetCenterX = static_cast<float>(kIpmWidth) * 0.5f;
constexpr float kTargetHalfRoadWidth = kAtgRoadWidthMeters * kAtgPixelPerMeter * 0.5f;
```

默认目标矩形从固定 `(63, 70)` / `(97, 70)` 改成按宽度计算：

```text
left-bottom:  (53.9, 70)
right-bottom: (106.1, 70)
left-top:     (53.9, 30)
right-top:    (106.1, 30)
```

因为：

```text
0.45m * 116px/m = 52.2px
center_x = 80
half_width = 26.1px
left = 80 - 26.1 = 53.9
right = 80 + 26.1 = 106.1
```

同一提交在 `docs/IPM调用调研.md` 中记录：

```text
尺度合同也必须同源：当前 ATG 参数是 ROAD_WIDTH=0.45m、pixel_per_meter=116，
因此 IPM 里的赛道宽度应约为 52.2px。
标定生成器的默认目标矩形按这个宽度生成，
避免 sample_dist、pixel_per_meter 和元素距离门槛互相打架。
```

审计判断：

- `pixel_per_meter=116` 的后续理由是“让当前 IPM 目标宽度与 ATG 距离尺度同源”。
- 但历史顺序更像是：port 层先已有 `116`，随后 IPM 生成器对齐到这个 `116`。
- 该提交没有重新论证 `sample_dist=0.03f`。

### 3. `f15b77b` 记录参数差异风险

提交：

```text
f15b77b fix(atg-ref): 收敛实车元素入环控制诊断
```

提交说明重点：

- 补充环岛状态日志、停滞复位、BEGIN 误入撤销。
- 收紧 `Half_check` 单 L 入环捷径。
- 扩展 live 日志字段，输出角点诊断。
- 已知风险里记录“圆环状态能进入，但入环轨迹仍可能不足”。

该提交新增 `docs/ATG角点斜车身问题交接.md`，明确记录参考版和当前参数差异：

```c
// 参考版
block_size = 9;
clip_value = 2;
sample_dist = 0.02;
pixel_per_meter = 41;
angle_dist = 0.2;

// 当前
block_size = 5;
clip_value = 8;
sample_dist = 0.03f;
pixel_per_meter = 116;
angle_dist = 0.2f;
```

文档当时已经写明：

```text
这不是小差异。sample_dist、pixel_per_meter、angle_dist 共同决定重采样点距、
局部角度窗口和 i < 45、0.7 / sample_dist 这类 id 门限的实际物理含义。
不能只调 60/73 deg 一个阈值。
```

审计判断：

- `f15b77b` 不是 `sample_dist=0.03` 的来源。
- 它是第一次把“参考版参数和当前参数不等价”作为风险记录下来。
- 当时已经意识到不能只调角度阈值，但没有完成尺度合同审计。

### 4. `82a293d` 不是尺度参数来源

提交：

```text
82a293d fix(atg-ref): 用车体 raw 参考点校准 IPM 中心
```

提交说明重点：

- 根据实车 `CxScan`，将直道居中修正从 `guide_error_bias_deg` 迁回几何参考点。
- 新增 `vehicle_raw_ref_x=80.0`。
- `guide_error_bias_deg` 从 `13.0` 归零。
- 更新 `rot/inv_rot`。

审计判断：

- 该提交处理的是车体参考点和 IPM 中心偏差。
- 它不是 `pixel_per_meter=116` 或 `sample_dist=0.03` 的来源。
- 它会影响 `cx/cy` 和 guide 零点，但不能解释圆环角点阈值口径。

## 参考版与当前尺度对比

| 参数 | 参考版 | 当前移植 | 影响 |
| --- | ---: | ---: | --- |
| `block_size` | `9` | `5` | 局部二值化窗口变小，边线响应和噪声特性改变。 |
| `clip_value` | `2` | `8` | 阈值偏移更强，黑白分割口径改变。 |
| `line_blur_kernel` | `7` | `7` | 平滑核点数相同；由于它在重采样前执行，实际物理平滑长度取决于原始追线点列经 IPM 后的间距。 |
| `sample_dist` | `0.02m` | `0.02m` | 当前已恢复参考版每点物理距离。 |
| `pixel_per_meter` | `41` | `116` | IPM 坐标尺度约 2.83 倍。 |
| `angle_dist` | `0.2m` | `0.2m` | 物理角度窗口相同，离散点数同为 10 点。 |
| `ROAD_WIDTH` | `0.45m` | `0.45m` | 赛道物理宽度一致。 |

派生量：

| 派生量 | 参考版 | 当前移植 | 影响 |
| --- | ---: | ---: | --- |
| 重采样点距 | `0.02 * 41 = 0.82px` | `0.02 * 116 = 2.32px` | IPM 像素距离约为参考版 `2.83` 倍；这是坐标尺度现象，不可直接等同于角度算法“粗 2.83 倍”。 |
| 赛道 IPM 宽度 | `0.45 * 41 = 18.45px` | `0.45 * 116 = 52.2px` | 当前 IPM 中赛道宽度更宽，分辨率更高。 |
| 单边外扩距离 | `0.45 * 41 / 2 = 9.225px` | `0.45 * 116 / 2 = 26.1px` | 单边线外扩到中线的像素距离变化很大。 |
| 角度窗口点数 | `round(0.2/0.02)=10` | `round(0.2/0.02)=10` | 当前已恢复参考版角度窗口点数。 |
| 角度半窗口物理长度 | `10*0.02=0.20m` | `10*0.02=0.20m` | 当前已恢复参考版物理窗口。 |
| blur 半支撑 | 3 个原始追线点 | 3 个原始追线点 | 不能直接按 `sample_dist` 换算；它发生在重采样前。 |
| `i < 45` 物理距离 | `0.90m` | `0.90m` | 当前已恢复参考版近端角点接受距离。 |
| 圆环入口 `Lpt_id` 物理距离 | `25 点 = 0.50m` | `35 点 = 0.70m` | 当前实验把圆环入口窗口放宽到 `0.7m`。 |
| `0.7 / sample_dist` | `35` 点 | `35` 点 | 当前已恢复参考版点数。 |

## 角度算法尺度不变性校验

`local_angle_points()` 的核心是：

```c
dx1 = pts[i].x - pts[i-dist].x;
dy1 = pts[i].y - pts[i-dist].y;
dx2 = pts[i+dist].x - pts[i].x;
dy2 = pts[i+dist].y - pts[i].y;

c1 = dx1 / norm1;
s1 = dy1 / norm1;
c2 = dx2 / norm2;
s2 = dy2 / norm2;

angle[i] = atan2(c1 * s2 - c2 * s1, c2 * c1 + s2 * s1);
```

如果所有 IPM 坐标同时乘以同一个比例 `k`，`dx/dy/norm` 都会乘以 `k`，归一化后的 `c/s` 不变，因此角度不变。`conf` 又是角度之间的差值，也不受统一缩放影响。

用理想折角模型复算，固定 `sample_dist` 时改变 `pixel_per_meter`，`conf` 不变：

| 真实角 | `sd=0.02, ppm=41` | `sd=0.02, ppm=116` | `sd=0.03, ppm=41` | `sd=0.03, ppm=116` |
| ---: | ---: | ---: | ---: | ---: |
| 30 deg | 24.58 deg | 24.58 deg | 22.24 deg | 22.24 deg |
| 40 deg | 33.00 deg | 33.00 deg | 29.94 deg | 29.94 deg |
| 50 deg | 41.59 deg | 41.59 deg | 37.88 deg | 37.88 deg |
| 60 deg | 50.41 deg | 50.41 deg | 46.12 deg | 46.12 deg |
| 70 deg | 59.49 deg | 59.49 deg | 54.72 deg | 54.72 deg |
| 80 deg | 68.86 deg | 68.86 deg | 63.73 deg | 63.73 deg |
| 90 deg | 78.56 deg | 78.56 deg | 73.20 deg | 73.20 deg |

这说明：

- `pixel_per_meter=116` 不应被直接当作角点 `conf` 下降的数学原因。
- 历史 `sample_dist=0.03` 是旧配置里让 `conf` 下降的主因；当前已恢复为 `0.02`。
- `pixel_per_meter` 仍然危险，因为它影响 IPM 标定目标、外扩距离、控制公式和所有用米转像素的合同；但这是全局几何合同风险，不是 `local_angle_points()` 的统一缩放风险。

## 对圆环角点的直接影响

当前 `find_corners()` 里普通态 `Lpt` 使用：

```c
60 deg < conf < 140 deg
```

当前圆环入口 `check_circle()` 使用：

```c
left_entry  = Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 35;
right_entry = !Lpt0_found && Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 35;
```

这意味着圆环入口正在复用普通 `Lpt` 口径。

按当前 `sample_dist=0.02m`、`angle_dist=0.2m`、`blur7` 的理想折角计算：

| 真实折角 | 当前计算得到的 `conf` |
| ---: | ---: |
| 30 deg | 24.6 deg |
| 40 deg | 33.0 deg |
| 50 deg | 41.6 deg |
| 60 deg | 50.4 deg |
| 70 deg | 59.5 deg |
| 80 deg | 68.9 deg |
| 90 deg | 78.6 deg |

所以在这个理想折线模型下，`conf > 60 deg` 约对应折线方向突变超过 `70.6 deg`。这个数不是圆环赛道的几何夹角；它只说明普通态 `Lpt` 口径仍更接近明显折点，而不是平滑圆角过渡。

同样 `blur7` 下，参考版和当前的阈值反推：

| `conf` 门槛 | 当前/参考版 `sample_dist=0.02` 需要真实角 | 历史旧配置 `sample_dist=0.03` 需要真实角 |
| ---: | ---: | ---: |
| `40 deg` | `48.2 deg` | `52.6 deg` |
| `50 deg` | `59.5 deg` | `64.6 deg` |
| `60 deg` | `70.6 deg` | `75.9 deg` |
| `66 deg` | `77.0 deg` | `82.4 deg` |
| `73 deg` | `84.3 deg` | `89.8 deg` |

历史 `0.03` 旧配置下的差异：

- 历史 `sample_dist=0.03` 会让同一个角点比参考版更难过阈值。
- 当前已恢复 `sample_dist=0.02`，因此这部分离散角度窗口差异已经消除；剩余差异主要来自 IPM 标定、二值化、原始追线点列、实际圆环几何和共享 `Lpt` 阈值口径。
- 如果板端 `best_conf` 常落在 `20 deg ~ 60 deg`，那么问题不应归因于圆环状态机，而应优先归因于角点口径和尺度合同不匹配。

## 当前不能直接做的事

| 动作 | 风险 |
| --- | --- |
| 直接把 `pixel_per_meter` 从 `116` 改回 `41` | 会破坏当前 IPM 宽度合同，所有外扩、距离、预瞄和元素阈值都会变。 |
| 继续频繁改 `sample_dist` | 会改变全部点列数量、角点窗口点数、id 门限、选线预瞄索引和性能负担。当前已恢复 `0.02`，后续应以板端日志验证。 |
| 全局降低 `Lpt` 阈值 | 十字、半十字、环岛、回环等共享 `Lpt`，会扩大误识别面；当前实验已从 `73 deg` 降到 `60 deg`，需要板端日志确认收益。 |
| 只凭上位机画面判断角点失败 | 之前已经出现过显示链路误杀远处角点的问题，必须看 `best_conf`、`accept_i`、`Ypt/Lpt found` 等诊断。 |

## 后续审计方向

这部分只是记录后续要查的点，不代表已经决定改代码。

1. 先用板端日志确认入圆环口附近的真实 `best_conf` 分布。
   - 看 `atg_lpt*_best_conf`。
   - 同时看 `Ypt*_found`、`Lpt*_found`、`accept_i`、`best_i`、`circle_type`。
2. 验证 `sample_dist=0.02` 恢复后的板端效果。
   - 它最早来自 `fad5e28` 初始 port。
   - 当前没有找到 `0.03` 的强理由，因此恢复到参考版 `0.02`。
   - 它对角点、id 门限和选线预瞄都有影响，需要实车日志确认。
3. 保持 `pixel_per_meter=116` 暂不动。
   - 当前 IPM 生成器、SOP 和验收都围绕 `52.2px` 赛道宽度建立。
   - 若要改 `pixel_per_meter`，必须同时重做 IPM 目标矩形、外扩距离、控制预瞄和元素距离阈值。
4. 圆环入口角点口径应单独审计。
   - 圆环入口是锐角类角点。
   - 当前入口复用普通 `Lpt` 近直角口径。
   - 先用日志证明分布，再决定是否拆出圆环入口角点口径。

## 审计命令记录

本次主要用过的 git 命令：

```bash
git log --oneline --decorate --all --date=short -- \
  atg_reference/port/reference_globals.c \
  atg_reference/port/reference_step.c \
  tools/ipm_generator/src/ipm_generator.cpp \
  tools/ipm_generator/README.md \
  docs/IPM调用调研.md \
  docs/IPM重标定流程.md \
  docs/ATG角点斜车身问题交接.md

git log --all --oneline -S'pixel_per_meter = 116' -- \
  atg_reference/port/reference_globals.c \
  atg_reference/port/reference_step.c \
  atg_reference/Project/CODE tools docs

git log --all --oneline -S'sample_dist = 0.03' -- \
  atg_reference/port/reference_globals.c \
  atg_reference/port/reference_step.c \
  atg_reference/Project/CODE docs

git show --format=medium --find-renames fad5e28 -- \
  atg_reference/port/reference_globals.c \
  atg_reference/port/reference_step.c \
  atg_reference/PORTING.md \
  atg_reference/SOURCE.md

git show --format=medium --find-renames 38deb58 -- \
  tools/ipm_generator/src/ipm_generator.cpp \
  tools/ipm_generator/README.md \
  docs/IPM调用调研.md \
  docs/IPM重标定流程.md \
  atg_reference/PORTING.md

git show --format=medium --find-renames f15b77b -- \
  atg_reference/port/reference_step.c \
  atg_reference/Project/CODE/shy_Image.c \
  atg_reference/PORTING.md \
  docs/ATG角点斜车身问题交接.md \
  docs/ATG环岛问题记录.md

git show --format=medium --find-renames 82a293d -- \
  atg_reference/Project/CODE/shy_Image.c \
  atg_reference/port/reference_step.c \
  front_car_mainline.yaml
```
