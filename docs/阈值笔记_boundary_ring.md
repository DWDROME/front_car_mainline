## boundary / ring 阈值笔记

这份笔记只记录当前 `front_car_mainline` 里和 `boundary.cpp`、`ring.cpp` 直接相关的关键阈值，方便后面查和讨论。

先说一句总判断：

这些参数看起来多，不代表都在独立调车。它们其实主要分成 4 组：

1. 距离类阈值：按 RT1064 `circle.c` 的物理长度换算成当前点数。
2. 角度/曲率类阈值：定义什么叫直线、什么叫 L 角。
3. 状态计次类阈值：防止一帧误触发。
4. 几何补线类阈值：给 ring 补对侧边界时找 seed、补起点用。

真正经常需要重点盯的，不是全部参数，而是少数几组：

- `boundary_is_straight()` 相关
- 双 L 二次复核相关
- ring 状态切换相关

---

## 1. `code/tracking/boundary.cpp` 阈值

位置：`code/tracking/boundary.cpp`

### A. 直线判定相关

```cpp
const int k_curvature_threshold = 3;      // 曲率门，单位 1/pixel
const int k_angle_threshold = 8;          // 前段局部角峰门，单位 degree
const int k_straight_scan_step = 34;      // 直线判定前探长度，单位 点
const int k_straight_min_step = 34;       // 直线最短长度门，单位 点
```

作用：

- 给 `boundary_is_straight()` 用。
- ring 入口和出环都依赖这组值。

当前语义：

- `k_straight_min_step = 34`：先要求边界长度至少约 1.0m。
- `k_straight_scan_step = 34`：只检查前约 1.0m 的局部角峰。
- `k_curvature_threshold = 3`：全局曲率不能太大。
- `k_angle_threshold = 8`：前段不能出现过强局部拐点峰。

说明：

- 这里不是“只要够长就是直线”，而是“够长 + 曲率小 + 前段局部角峰小”。
- 这组对 ring 比对 cross 更敏感。

### B. L 角检测相关

```cpp
const int k_l_angle_low = 70;             // L角下限，单位 degree
const int k_l_angle_high = 140;           // L角上限，单位 degree
const int k_window_size = 10;             // 局部角计算窗口，单位 点
const int k_corner_scan_step = 28;        // 只在前段扫描 L 角，单位 点
const int k_corner_front_step = 28;       // L角最远允许位置，单位 点
```

作用：

- 给 `scan_corner()`、`refresh_boundary_corners()` 用。
- 这里只产出单侧 L 候选/单侧 L 消费门；当前代码已经把 cross 的 strict 双 L 入口拆到 `l_pair_ok`。

当前语义：

- `l_found`：边界几何扫描看到了单侧 L 候选。
- `l_ok`：单侧 L 消费门，供 ring、zebra 扫描选择和裁剪类逻辑使用。
- `l_pair_ok`：双 L 二次复核通过；`cross.cpp::strict_double_l_ok()` 只消费这个字段。
- `70~140`：什么角度范围算近线 L 角。
- `k_corner_scan_step = 28`：只扫前约 0.8m。
- `k_corner_front_step = 28`：就算扫到了，超过前约 0.8m 也作废。

说明：

- 这组决定“能不能看见可用 L 角”。
- 目前已经按 RT1064 近线 L 角 `0.8m` 物理语义收到了 `28`。

### C. 双 L 二次复核相关

```cpp
const int k_corner_open_step = 34;        // 从L点往前看的距离，单位 点
const double k_corner_pair_width_ref = 45.0;   // L点处标准宽度，单位 pixel
const double k_corner_pair_tol = 15.0;         // L点处宽度容差，单位 pixel
const double k_corner_pair_open_ref = 70.0;    // 往前张开宽度门，单位 pixel
```

作用：

- 给 `corner_pair_ok()` 用，结果写到 `l_pair_ok / l_pair_state / l_pair_width*`。
- 主要影响 cross strict 双 L 入口是否成立；复核失败不会清掉单侧 `l_ok`。

当前语义：

- `w0 ~= 45 +/- 15`：当前 L 点处宽度先得像路宽。
- `k_corner_open_step = 34`：从 L 点往前看约 1.0m。
- `w1 > 70`：前方宽度必须明显张开。
- 方向还必须满足：左线继续往左、右线继续往右。

说明：

- 这组不是在找 L 角，而是在验证“两个 L 角是不是构成真的十字入口”。
- `k_corner_open_step` 是前面几轮里最关键的一刀，已经从 50 收到 34。

### D. 其他

```cpp
const int k_boundary_blur_kernel = 3;     // 当前文件里是占位常量
const int k_boundary_resample_dist = 3;   // 边界重采样步长，单位 点

const int k_pair_none = 0;
const int k_pair_width0_bad = 1;
const int k_pair_open_bad = 2;
const int k_pair_dir_bad = 3;
```

说明：

- `k_boundary_resample_dist = 3` 是所有“按点数换算物理距离”的基础。
- `k_pair_*` 不是调参量，是双 L 复核失败原因码。

---

## 2. `code/tracking/ring.cpp` 阈值

位置：`code/tracking/ring.cpp`

```cpp
const int k_lost_step = 7;                // 丢线门，约 0.2m
const int k_have_step = 34;               // 恢复有线门，约 1.0m
const int k_seed_dx = 5;                  // 补边 seed 横移
const int k_seed_dy = 3;                  // 补边 seed 纵移
const int k_in_lost_step = 4;             // 入环后内侧线几乎没了，约 0.1m
const int k_run_corner_step = 14;         // RUN 阶段角点靠近门，约 0.4m
const int k_lost_confirm_n = 2;           // BEGIN 丢线确认次数
const int k_have_confirm_n = 1;           // BEGIN 恢复有线确认次数
const int k_end_left_exit_lost_n = 3;     // 左环 END 退出确认次数
const int k_end_right_exit_lost_n = 2;    // 右环 END 退出确认次数
const int k_encoder_per_meter = 5800;     // 编码器比例，步/米
const int k_in_encoder_step = k_encoder_per_meter * 314 / 200; // 约 1.57m
```

### A. 距离类状态门

- `k_lost_step = 7`
  - 语义：边界短到约 0.2m，认为“基本丢了”。
- `k_have_step = 34`
  - 语义：边界恢复到约 1.0m，认为“重新有线”。
- `k_in_lost_step = 4`
  - 语义：内侧边界短到约 0.1m，认为入环段已经跑完。
- `k_run_corner_step = 14`
  - 语义：RUN 阶段补出来的对侧 L 角已经靠近到约 0.4m，准备 OUT。

说明：

- 这 4 个值本质上都能从 RT1064 `circle.c` 物理距离换算出来。
- 当前 ring 主链按 RT1064 `circle.c::check_circle()` / `run_circle()` 对齐；Unity `CD.cpp` 的 `AIB/BW/pending/ring_times` 只保存在 `docs/reference/unity_CD_old.cpp` 里作 old 对照。

RT1064 对照表：

| 当前常量 | RT1064 `circle.c` 依据 | 说明 |
| --- | --- | --- |
| `k_lost_step = 7` | `rpts*s_num < 0.2 / sample_dist` | `0.2m / 0.03m ~= 6.7`，取 7 点。 |
| `k_have_step = 34` | `rpts*s_num > 1.0 / sample_dist` | `1.0m / 0.03m ~= 33.3`，取 34 点。 |
| `k_in_lost_step = 4` | `rpts*s_num < 0.1 / sample_dist` | `0.1m / 0.03m ~= 3.3`，取 4 点。 |
| `k_run_corner_step = 14` | `Lpt*s_id < 0.4 / sample_dist` | `0.4m / 0.03m ~= 13.3`，取 14 点。 |
| `k_in_encoder_step = 5800 * 314 / 200` | `ENCODER_PER_METER * (3.14 * 1 / 2)` | RT1064 注释为编码器打表过约 1/4 圆。 |
| `k_lost_confirm_n = 2` | `none_*_line > 2` | BEGIN 阶段先丢线再有线。 |
| `k_have_confirm_n = 1` | `have_*_line > 1` | BEGIN 阶段恢复有线后进入 IN。 |
| `k_end_left_exit_lost_n = 3` | `none_left_line > 3` | 左环 END 退出。 |
| `k_end_right_exit_lost_n = 2` | `none_right_line > 2` | 右环 END 退出。 |

### B. 状态计次门

- `k_lost_confirm_n = 2`
- `k_have_confirm_n = 1`
- `k_end_left_exit_lost_n = 3`
- `k_end_right_exit_lost_n = 2`

说明：

- 这几项不是物理距离，而是“连续多少次才算真发生”。
- 作用是防一帧抖动误切状态。

### C. 几何补线相关

- `k_seed_dx = 5`
- `k_seed_dy = 3`

说明：

- 这两项只在 `build_ring_opp_for_detection()` 里用；旧文档里可能还写作 `build_opp()`。
- 它们不是 ring 状态机门，而是补对侧边界时给种子点的偏移量。

### D. 编码器里程门

- `k_encoder_per_meter = 5800`
- `k_in_encoder_step = 5800 * 314 / 200`

说明：

- 这条链不是视觉距离，而是 RT1064 `circle.c` 里已有的里程阶段门。
- 语义是“跑过约四分之一圆”后进入 RUN；这里不是额外兜底，也不复用旧视觉几何。

---

## 3. 为什么会觉得参数太多

因为它们都堆在文件头，看起来像一坨。

但本质上不是几十个独立旋钮，而是下面这些组：

### `boundary.cpp`

1. straight 判定组
2. L 角检测组
3. 双 L 二次复核组

### `ring.cpp`

1. 距离类状态门
2. 连续计次门
3. 补线 seed 偏移
4. 编码器里程门

所以后面真调参时，不应该一个一个零散改，而应该按组看：

- ring 进不去 / 出不来：先看 straight 判定组 + ring 距离门
- cross 进不去：先看 L 角检测组 + 双 L 二次复核组
- 补边乱：再看 seed 偏移

---

## 4. 当前最关键、最常看的不是全部参数

### 如果看 cross

优先看：

- `k_corner_scan_step`
- `k_corner_front_step`
- `k_corner_open_step`
- `k_corner_pair_width_ref`
- `k_corner_pair_tol`
- `k_corner_pair_open_ref`

### 如果看 ring

优先看：

- `k_curvature_threshold`
- `k_angle_threshold`
- `k_straight_scan_step`
- `k_straight_min_step`
- `k_lost_step`
- `k_have_step`
- `k_in_lost_step`
- `k_run_corner_step`

---

## 5. 当前已经按数学换算对齐的关键值

### boundary

- `0.8m -> 28`
  - `k_corner_scan_step`
  - `k_corner_front_step`
- `1.0m -> 34`
  - `k_corner_open_step`
  - `k_straight_scan_step`
  - `k_straight_min_step`
- `0.45m -> 45px`
  - `k_corner_pair_width_ref`
- `0.15m -> 15px`
  - `k_corner_pair_tol`
- `0.7m -> 70px`
  - `k_corner_pair_open_ref`

### ring

- `0.2m -> 7`
  - `k_lost_step`
- `1.0m -> 34`
  - `k_have_step`
- `0.1m -> 4`
  - `k_in_lost_step`
- `0.4m -> 14`
  - `k_run_corner_step`

---

## 6. 一句话记忆版

不要把这些全当成“很多参数”。

更准确的理解是：

- `boundary.cpp` 负责解释边界几何，所以参数多一些；
- `ring.cpp` 负责状态切换和补边，所以还有一组状态门；
- 真正常调的不是全部值，而是几组成套阈值。

---

## 7. `code/tracking/cross.cpp` 当前关键阈值

位置：`code/tracking/cross.cpp`

这部分这轮没有继续大改，只把十字入口近角门收成了显式常量，方便后面继续核对 RT1064 `cross.c` 语义。

```cpp
const int k_cross_min_front_step = 8;    // 远线最短有效长度
const int k_cross_begin_near_step = 4;   // BEGIN 近角门，约 0.1m
const int k_cross_near_lost_step = 5;    // IN 阶段近线一起丢失门
const int k_cross_near_recover_step = 20; // IN 阶段近线一起恢复门
const int k_cross_far_resample_dist = 3; // 十字远线重采样步长
const int k_cross_far_l_window = 4;      // 远 L 局部角窗口
const int k_cross_far_l_angle_min = 70;  // 远 L 角下限
const int k_cross_far_l_angle_max = 110; // 远 L 角上限
```

说明：

- `k_cross_begin_near_step = 4` 已按 RT1064 `cross.c` 的 `0.1m` 近角门收成当前 3px 重采样下的等效值。
- `k_cross_near_lost_step = 5`、`k_cross_near_recover_step = 20` 这轮先不动。
- 原因不是算不出来，而是它们直接影响 `CROSS_IN` 的退出时机，属于状态门，不适合在几何层还在收口时一起乱改。

如果后面看 cross，建议先分清两层：

1. `boundary.cpp` 的双 L / 几何解释层是否已经把入口看对。
2. `cross.cpp` 的 `lost / recover` 状态门是否导致进得去但退不掉，或者退得太早。

---

## 8. 本轮计划实际落地结果

这轮的原则不是“把所有元素参数都改一遍”，而是先把几何解释层收直，再决定要不要动状态门。

### A. 已实际落地

#### `boundary.cpp`

- `k_curvature_threshold: 2 -> 3`
- `k_angle_threshold: 5 -> 8`
- `k_corner_open_step: 50 -> 34`
- `k_straight_scan_step: 50 -> 34`
- `k_corner_scan_step: 40 -> 28`
- `k_corner_front_step: 40 -> 28`
- 新增 `k_straight_min_step = 34`

这几刀的目的很明确：

- 直线判定只看前约 `1.0m`
- L 角只在前约 `0.8m` 内算有效
- 双 L 张开复核只看前约 `1.0m`
- 先把当前 `160x120 + 3px` 重采样下的物理长度语义收回到 RT1064 附近

#### `cross.cpp`

- `k_cross_begin_near_step` 改成显式 `4`

目的：

- 不再写成 `STEP_MAX / 10` 这种间接表达。
- 直接把“约 0.1m 近角门”写死在当前工程语义里，方便后面查。

### B. 这轮明确先不动

#### `ring.cpp` 主状态门

当前保持：

- `k_lost_step = 7`
- `k_have_step = 34`
- `k_in_lost_step = 4`
- `k_run_corner_step = 14`

原因：

- 这几项已经基本能按 RT1064 `circle.c` 物理长度换算回当前点数。
- 在几何层还没彻底跑现场之前，先不去动 ring 状态机门槛，避免把“几何识别问题”和“状态切换问题”搅在一起。

#### `cross.cpp` 的退出门

当前保持：

- `k_cross_near_lost_step = 5`
- `k_cross_near_recover_step = 20`

原因：

- 这两项直接改的是十字退出节奏，不是单纯几何解释。
- 后面如果真要继续压，应该基于自然帧序列看：
  - 是不是已经能稳定进十字；
  - 退出是太早、太晚，还是刚好。

### C. 这轮收口后的理解

当前最重要的结论不是“参数更多了”，而是分层更清楚了：

- `boundary.cpp` 先负责把边界几何解释对。
- `cross.cpp` / `ring.cpp` 再拿这个结果做状态切换。
- 所以这轮优先压的是 `boundary`，不是把所有状态门一起乱拧。

### D. 后面如果继续调，顺序建议

1. 先看上位机图，确认近线 L 角、双 L 张开、straight 判定是不是已经符合预期。
2. 如果 cross 进不去，先看 `boundary.cpp` 的 L 角检测组和双 L 复核组。
3. 如果 cross 进得去但退不掉，再看 `k_cross_near_lost_step / k_cross_near_recover_step`。
4. 如果 ring 进不去或出不来，再看 straight 判定组和 `ring.cpp` 距离类状态门。
