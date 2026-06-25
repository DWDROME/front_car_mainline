# 圆环 B/C 搜索纵向方向反转修复

## 问题根因

上位机人眼坐标和程序 raw_y 坐标系相反：

```
raw_y = 120 - viewer_y
```

这导致：
- 人眼往上走 → raw_y 变大
- 人眼往下走 → raw_y 变小

当前 B/C 搜索的纵向方向沿用旧理解（raw_y 减小 = 往上），导致它往人眼下方找，而不是往圆环弧顶上方找。

## 现象

左环 A seed 在人眼 y≈74（raw_y≈46），正确 B 应在人眼 y≈41（raw_y≈79），但当前代码从 `seed_raw_y - 5` 开始 `y--` 搜索，导致 B 落在 A 附近/下面，而不是圆环弧顶上方。

## 修复范围

**横向方向不要动**（已经正确）：
- 左环：`x--`
- 右环：`x++`

**纵向方向要反转**：
- 向上找 B/C 在程序里应该是 `raw_y++`，不是 `raw_y--`

## 具体改动

### 1. `find_circle_B_vertical()` 的 y 搜索

**当前（错误）：**
```c
circle_B_search_start = clip(seed_raw_y - 5, ...);

for(int y = circle_B_search_start;
    y > block_size / 2 + 5;
    y--)
```

**修改为：**
```c
const int y_min = block_size / 2 + 5;
const int y_max = MT9V03X_H - block_size / 2 - 1;

circle_B_search_start = clip(seed_raw_y + CIRCLE_B_UP_MIN, y_min, y_max);
const int circle_B_search_stop = clip(seed_raw_y + CIRCLE_B_UP_MAX, y_min, y_max);

for(int y = circle_B_search_start;
    y <= circle_B_search_stop;
    y++)
```

### 2. B 的 `dy_ab` / `up_dy` 计算

**当前（错误）：**
```c
const int dy_ab = seed_raw_y - best_y;
const int up_dy = seed_raw_y - best_y;
```

**修改为：**
```c
const int dy_ab = best_y - seed_raw_y;
const int up_dy = best_y - seed_raw_y;
```

因为正确 B 是 `best_y > seed_raw_y`（例如 79 > 46）。

### 3. `find_circle_C()` 的 y 搜索

**当前（错误）：**
```c
for(int y = circle_B_point.raw_y - 1;
    y > block_size / 2 + 5;
    y--)
```

**修改为：**
```c
const int y_max = MT9V03X_H - block_size / 2 - 1;

for(int y = circle_B_point.raw_y + 1;
    y < y_max;
    y++)
```

### 4. 横向 `inner_dir` 保持不变

```c
const int inner_dir = left_circle ? -1 : 1;
```

不要改回去。

## 预期效果

- 左环 B：从 A 位置出发，`x--`（向左），`raw_y++`（向人眼上方）
- 右环 B：从 A 位置出发，`x++`（向右），`raw_y++`（向人眼上方）
- B 落点应在圆环弧顶附近（人眼 y≈41，raw_y≈79），而不是 A 附近

## 验证

编译后观察上位机：
- B 橙色竖线应落在圆环弧顶附近
- B.raw_y 应显著大于 A.raw_y（例如 79 vs 46）
- C 应继续向弧顶上方搜索

## 附注

`CIRCLE_B_ENTER_ROW` 的语义也变了：
- 如果 raw_y 越大代表人眼越上，那当前 `circle_B_point.raw_y >= CIRCLE_B_ENTER_ROW` 表示"B 更靠上/更远"，不是"B 靠近车身"
- 若表达"B 到了车身附近"，应改为 `circle_B_point.raw_y <= 某阈值`
- 但当前不让 B_row 直接切状态，只改 ref_mode，所以这个不是最急，**先只改搜索方向和 dy 计算**
