# 圆环 B/C 搜索纵向方向修复 - 修改总结

## 2026-06-25 追加修正：B 扫描跳过近端线边缘假目标

现场 `ATGCircleEntryProbe: A=1@4(raw=31,79) hits=4 range=64..36 reason=no_extreme`
显示 B 搜索每帧能看到暗像素，但命中的都是近端左线边缘：

- 从 `seed_x=31` 起扫时，第一暗点常在 `x=32`，`inner_dx=1`，小于 `CIRCLE_ENTRY_AB_X_MIN=6`。
- 真正右弧顶在 `x≈66`，会被“每行遇到第一个暗点就 break”的近端线边缘挡住。
- 修复为先跳过近端线宽，再找对侧弧面：左环从 `seed_x + 20` 向右扫；右环从 `seed_x - 20` 向左扫。
- `drive172` 静止采样证明全图右扫会混入右侧普通边线：`best=115/116, dx=85, detail=jump_bad`。`drive173` 证明 `seed_x+60` 仍会混入 `x≈85` 普通边线。最终把扫描限制在口门横向窗口：左环 `seed_x+20..seed_x+45`，右环 `seed_x-20..seed_x-45`。

### 行为变更依据表

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| ATG 当前帧 A 点和 `ATGCircleEntryProbe` 已证明 A 上方窗口有暗像素，但近端线边缘会先命中；真 B 是对侧弧面点。 | `circle.c::find_circle_B_vertical()` 从 `seed_raw_x` 起扫会被近端边缘挡住；改为全图对侧扫后又混入普通右边线，`drive172` 显示 `best=115/116, detail=jump_bad`，`drive173` 显示 `seed_x+60` 仍混入 `x≈85`。 | `find_circle_B_vertical()` 增加 `CIRCLE_ENTRY_B_SKIP_EDGE_X=20` 和 `CIRCLE_ENTRY_B_SCAN_SPAN_X=45`，左环只扫 `seed_x+20..seed_x+45`，右环对称；AB 横向展开语义恢复为对侧弧面展开。 | 跳过的是当前帧 A 附近近端线宽，横向上限用于隔离右侧普通边线；这样 B 才能落到对侧弧面口门窗口。 | 无暗点、命中数不足、跳变过大、AB 距离/横向展开/高度窗口不满足仍然通过 `ATGCircleEntryProbe`/`ATGCircleABCDiag` 暴露并返回失败。 |

## 2026-06-25 中间尝试：B 改用 inner-hit 同向有界扫描（已被上方线边缘修正覆盖）

最新现场判断覆盖下方早期“单纯反转 raw_y 方向”的结论：

- `inner_hit` 已能用斜向射线从 seed `(25,80)` 沿 `dx=-1, dy=-2` 命中内边界约 `(5,40)`。
- 失败点不是“没有内边界”，而是 `find_circle_B_vertical()` 每行从 A 的 x 附近水平扫，遇到斜向内边界时跨不到，导致 `best_y < 0`。
- 尝试从 ray hit 点进入 `findline_*_adaptive()` 后，实测 `trace=1`，手性追线不能稳定覆盖口门点。
- 最终修复为从当前帧 A 的 raw 坐标出发，在 A 上方窗口内逐行沿 `inner_hit` 同向扫描：左环向 raw x 减小取 min_x，右环向 raw x 增大取 max_x。
- `CIRCLE_ENTRY_B_MIN_RISE_HITS` 调整为 1：远端口门可见点少，防噪继续交给 AB 纵向距离、同向横向展开、空间距离、高度窗口和跳变检查。

### 行为变更依据表

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `inner_hit` 日志已证明左环入口存在 `seed=(25,80) -> hit=(5,40)` 的当前帧斜向内边界证据。 | `circle.c::find_circle_B_vertical()` 曾一度向外侧取极值，和 `inner_hit` 方向冲突，导致 B 的定义不稳定。 | `find_circle_B_vertical()` 改为在 A 上方窗口内从 A.raw_x 沿 inner-hit 同向扫描；左环取 min_x，右环取 max_x，并恢复 `inner_dx_ab` 为同向展开语义。 | B 是口门确认点，应跟随 inner-hit 的真实几何方向，而不是突然换到相反侧找外侧极值。 | 没有复用上一帧/旧 B；无暗点、命中数不足、跳变过大、AB 距离/同向 dx/高度窗口不满足都会通过 `ATGCircleEntryProbe`/`ATGCircleABCDiag` 暴露并返回失败。 |

## 修改文件

- `atg_reference/Project/CODE/circle.c`

## 核心问题

上位机人眼坐标和程序 raw_y 坐标系相反：`raw_y = 120 - viewer_y`

这导致：
- 人眼往上走 → raw_y 变大
- 人眼往下走 → raw_y 变小

但代码一直按"raw_y 减小 = 往上"在搜索，导致 B/C 搜索方向反了。

## 修改内容

### 1. `find_circle_B_vertical()` - B 点纵向搜索方向

**修改前（692-694 行）：**
```c
circle_B_search_start = clip(seed_raw_y - 5, block_size / 2 + 1, MT9V03X_H - block_size / 2);
for(int y = circle_B_search_start;
    y > block_size / 2 + 5; y--)
```

**修改后（696-702 行）：**
```c
// 从 A 稍上方开始,竖线向上逐行扫
// raw_y = 120 - viewer_y, 所以 raw_y 增大 = 人眼往上
const int y_min = block_size / 2 + 5;
const int y_max = MT9V03X_H - block_size / 2 - 1;
circle_B_search_start = clip(seed_raw_y + CIRCLE_B_UP_MIN, y_min, y_max);
const int circle_B_search_stop = clip(seed_raw_y + CIRCLE_B_UP_MAX, y_min, y_max);
for(int y = circle_B_search_start;
    y <= circle_B_search_stop; y++)
```

**说明：**
- 从 `seed_raw_y + 15` 开始，扫到 `seed_raw_y + 50`
- `y++` 递增，对应人眼往上（圆环弧顶方向）

### 2. B 点 dy 计算修正

**修改前（754 行和 776 行）：**
```c
const int dy_ab = seed_raw_y - best_y;
const int up_dy = seed_raw_y - best_y;
```

**修改后（756 行和 779 行）：**
```c
// raw_y 越大 = 人眼越上，所以 dy_ab = best_y - seed_raw_y
const int dy_ab = best_y - seed_raw_y;
const int up_dy = best_y - seed_raw_y;
```

**说明：**
- 正确 B 在人眼更上方，对应 `best_y > seed_raw_y`
- 例如：A_raw_y=46, B_raw_y=79, dy=79-46=33

### 3. `find_circle_C()` - C 点纵向搜索方向

**修改前（383 行）：**
```c
for(int y = circle_B_point.raw_y - 1; y > block_size / 2 + 5; y--)
```

**修改后（385-387 行）：**
```c
// 从 B 的位置,沿 B 的 x 列往上扫,每行往内侧扫到底找黑点
// raw_y 增大 = 人眼往上
const int y_max = MT9V03X_H - block_size / 2 - 1;
for(int y = circle_B_point.raw_y + 1; y < y_max; y++)
```

**说明：**
- C 在 B 的人眼更上方，所以从 `B_raw_y + 1` 开始 `y++`

### 4. 注释和常量说明更新

**CIRCLE_B_ENTER_ROW 注释（35-38 行）：**
```c
// CIRCLE_B_ENTER_ROW: 注意坐标系 raw_y = 120 - viewer_y
// raw_y >= 58 表示 viewer_y <= 62，即 B 在人眼较上方（非车身附近）
// 当前只用于改 ref_mode，不做状态切换，语义待重新定义
CIRCLE_B_ENTER_ROW = 58,
```

**CIRCLE_B_UP 窗口注释（47-48 行）：**
```c
// B 必须在 A 上方高度窗口中:B_raw_y - A_raw_y ∈ [UP_MIN, UP_MAX]
// 上位机坐标→raw:raw_y = 120 - viewer_y。A_viewer≈74→A_raw≈46, B_viewer≈41→B_raw≈79。窗口靠实测定。
```

## 横向方向（未修改）

**保持不变：**
```c
const int inner_dir = left_circle ? -1 : 1;
```

- 左环：`x--`（向左）
- 右环：`x++`（向右）

这个是正确的，不需要修改。

## 预期效果

- 左环 B：从 A 位置出发，`x--`（向左），`raw_y++`（向人眼上方）
- 右环 B：从 A 位置出发，`x++`（向右），`raw_y++`（向人眼上方）
- B 落点应在圆环弧顶附近（人眼 y≈41，raw_y≈79），而不是 A 附近
- C 继续向弧顶上方搜索

## 验证方法

编译后观察上位机：
1. B 橙色竖线应落在圆环弧顶附近
2. B.raw_y 应显著大于 A.raw_y（例如 79 vs 46）
3. C 应继续向弧顶上方搜索
4. `ATGCircleABCDiag` 日志中 B_raw_y 和 dy 值应合理
