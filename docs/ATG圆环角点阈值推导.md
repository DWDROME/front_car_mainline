# ATG 圆环角点阈值推导

本文记录圆环入口角点的代码事实和定量推导，目标是判断当前角点阈值是否匹配本车摄像头/IPM 标定后的几何口径。

重要校正：`conf > 60 deg` 不能直接解释成“圆环赛道夹角大于 60 度”。参考版的代码事实是：圆环入口复用普通态 `Lpt`，因此它期待被检测的那条边线在开口处呈现接近 L 型的方向突变。按当前理想折线模型，`conf > 60 deg` 约对应真实折线突变 `70.6 deg`，这个数不是环岛几何设计角。

如果本车看到的圆环入口边线实际只是 `30 deg ~ 60 deg` 的锐角或圆角过渡，那么普通态 `Lpt` 本身就不应该稳定触发；这说明要么我们观察的不是参考版触发的同一个边线角点，要么当前摄像头/IPM/二值化让参考版原本能看到的 L 型开口被抹成了锐角/圆角。

## 代码事实

当前圆环入口仍由 `Lpt*_found` 触发：

- `atg_reference/Project/CODE/circle.c`
  - `left_entry = Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 35`
  - `right_entry = !Lpt0_found && Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 35`

角点来自 `atg_reference/Project/CODE/shy_Image.c::find_corners()`：

- `Ypt`: `40 deg < conf < 66 deg`
- 普通态 `Lpt`: `60 deg < conf < 140 deg`
- `round_type` 下 `Lpt`: `50 deg < conf < 140 deg`

处理链路：

```text
原图边线 -> IPM -> blur_points(kernel=7) -> resample(sample_dist)
        -> local_angle(angle_dist/sample_dist) -> nms_angle -> conf
```

当前参数来自 `atg_reference/port/reference_globals.c` 和 `reference_step.c`：

| 参数 | 当前值 | 几何含义 |
| --- | ---: | --- |
| `sample_dist` | `0.02 m` | 重采样后相邻点间距 |
| `pixel_per_meter` | `116` | `0.02 m = 2.32 px` |
| `angle_dist` | `0.2 m` | 局部角度窗口 |
| `round(angle_dist / sample_dist)` | `10` 点 | 角度计算取 `i-10, i, i+10` |
| 角度半窗口 | `0.20 m` | `10 * 0.02 m` |
| 角度全跨度 | `0.40 m` | 前后各 `0.20 m` |
| `line_blur_kernel` | `7` | 三角核 `[1,2,3,4,3,2,1]/16` |
| blur 半支撑 | 3 个原始追线点 | `blur_points()` 在重采样前执行，不能直接按 `sample_dist` 换算 |
| blur 全支撑 | 7 个原始追线点 | 同上 |

`conf` 的代码公式：

```text
conf = abs(angle[i]) - (abs(angle[i-10]) + abs(angle[i+10])) / 2
```

它测的是角度突变尖锐度，不是单纯的局部转角。

## 理想折角模型

模型：两条直线在一个点形成真实几何折角 `theta`，按当前 `sample_dist` 采样，经过同样的 `blur_points`、`local_angle_points`、`nms_angle` 和 `conf` 计算。

这个模型不包含二值化噪声、IPM 误差和真实边线毛刺，只隔离“阈值和几何角是否匹配”这一件事。

### 真实折角到 conf

当前参数：`sample_dist=0.02 m`，`angle_dist=0.2 m`，`line_blur_kernel=7`。

| 真实折角 | 计算得到的 `conf` | 峰值处 `angle[i]` |
| ---: | ---: | ---: |
| 20 deg | 16.3 deg | 17.5 deg |
| 25 deg | 20.4 deg | 22.0 deg |
| 30 deg | 24.6 deg | 26.4 deg |
| 35 deg | 28.8 deg | 30.8 deg |
| 40 deg | 33.0 deg | 35.3 deg |
| 45 deg | 37.3 deg | 39.8 deg |
| 50 deg | 41.6 deg | 44.4 deg |
| 55 deg | 46.0 deg | 49.0 deg |
| 60 deg | 50.4 deg | 53.6 deg |
| 65 deg | 54.9 deg | 58.3 deg |
| 70 deg | 59.5 deg | 63.0 deg |
| 75 deg | 64.1 deg | 67.8 deg |
| 80 deg | 68.9 deg | 72.6 deg |
| 85 deg | 73.7 deg | 77.4 deg |
| 90 deg | 78.6 deg | 82.4 deg |

结论：在 `sample_dist=0.02 m`、`blur7` 的理想折线模型下，普通态 `Lpt` 的 `conf > 60 deg` 约等价于折线方向突变超过 `70.6 deg`。这个数是模型反推，不是圆环赛道中心几何角。

如果本车实际送进 `find_corners()` 的圆环入口点列只有 `30 deg ~ 60 deg` 方向突变，当前处理链下对应的 `conf` 约为：

| 目标真实角范围 | 当前 `blur7` 下对应 `conf` |
| ---: | ---: |
| 30 deg - 60 deg | 24.6 deg - 50.4 deg |
| 35 deg - 60 deg | 28.8 deg - 50.4 deg |
| 40 deg - 60 deg | 33.0 deg - 50.4 deg |
| 45 deg - 60 deg | 37.3 deg - 50.4 deg |

## 阈值反推真实折角

同样的理想折角模型，反推“某个 `conf` 门槛要求真实折角至少多大”。

| `conf` 门槛 | blur1 | blur3 | blur5 | blur7 | blur9 |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 22 deg | 22.0 deg | 24.6 deg | 27.0 deg | 29.7 deg | 32.8 deg |
| 30 deg | 30.0 deg | 33.4 deg | 36.6 deg | 40.1 deg | 44.1 deg |
| 35 deg | 35.0 deg | 38.9 deg | 42.5 deg | 46.4 deg | 50.9 deg |
| 40 deg | 40.0 deg | 44.3 deg | 48.3 deg | 52.6 deg | 57.4 deg |
| 46 deg | 46.0 deg | 50.8 deg | 55.2 deg | 59.9 deg | 65.0 deg |
| 50 deg | 50.0 deg | 55.1 deg | 59.7 deg | 64.6 deg | 69.8 deg |
| 60 deg | 60.0 deg | 65.7 deg | 70.7 deg | 75.9 deg | 81.4 deg |
| 66 deg | 66.0 deg | 72.0 deg | 77.2 deg | 82.4 deg | 87.9 deg |
| 73 deg | 73.0 deg | 79.2 deg | 84.5 deg | 89.8 deg | 95.2 deg |

这个表说明两件事：

- 降低 blur 可以提高 `conf`，但不能把 `conf > 60 deg` 变成 30-60 度圆环角检测；当前 `blur7` 下仍要求真实折角约 `70.6 deg`。
- 当前 `Ypt` 的 `40 deg ~ 66 deg` 在 `sample_dist=0.02`、`blur7` 下约对应真实折角 `48.2 deg ~ 77.0 deg`。它比 `Lpt` 更接近圆环角，但仍不覆盖真实 `30 deg ~ 45 deg` 的入口角。

## 点距影响

固定 `angle_dist=0.2 m`、`blur7`，改变重采样点距，反推阈值对应的真实折角。

| `conf` 门槛 | `sample_dist=0.020` | `sample_dist=0.025` | `sample_dist=0.030` | `sample_dist=0.040` |
| ---: | ---: | ---: | ---: | ---: |
| 30 deg | 36.5 deg | 38.5 deg | 40.1 deg | 46.0 deg |
| 40 deg | 48.2 deg | 50.7 deg | 52.6 deg | 59.7 deg |
| 50 deg | 59.5 deg | 62.4 deg | 64.6 deg | 72.3 deg |
| 60 deg | 70.6 deg | 73.6 deg | 75.9 deg | 83.9 deg |
| 66 deg | 77.0 deg | 80.1 deg | 82.4 deg | 90.4 deg |
| 73 deg | 84.3 deg | 87.5 deg | 89.8 deg | 97.6 deg |

较小点距会让角点更容易过阈值，但主导问题仍是阈值口径。`sample_dist=0.020` 且 `blur7` 时，`conf > 60 deg` 约要求真实折角 `70.6 deg`。

## 圆角化入口模型

模型：直线进入一个总转角 `60 deg` 的圆弧，再接直线。这里看圆弧半径 `R` 对 `conf` 的影响。

下表是历史审计里的 `sample_dist=0.03 m` 旧配置结果，用于解释为什么恢复到 `0.02 m` 会提高角点 `conf`。当前运行配置已经恢复为 `0.02 m`。

| 半径 R | blur1 | blur3 | blur5 | blur7 | blur9 |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 0.10 m | 49.0 deg | 47.4 deg | 44.2 deg | 40.7 deg | 37.1 deg |
| 0.12 m | 46.9 deg | 45.5 deg | 43.2 deg | 40.1 deg | 36.7 deg |
| 0.15 m | 43.2 deg | 42.1 deg | 40.2 deg | 37.5 deg | 34.4 deg |
| 0.18 m | 40.3 deg | 39.4 deg | 37.8 deg | 35.7 deg | 32.8 deg |
| 0.20 m | 39.1 deg | 38.2 deg | 36.9 deg | 35.0 deg | 32.2 deg |
| 0.25 m | 33.4 deg | 32.7 deg | 31.6 deg | 30.0 deg | 28.1 deg |
| 0.30 m | 27.5 deg | 26.9 deg | 25.9 deg | 24.6 deg | 23.2 deg |
| 0.35 m | 21.3 deg | 20.7 deg | 20.0 deg | 19.2 deg | 18.3 deg |
| 0.40 m | 17.8 deg | 17.1 deg | 16.6 deg | 16.2 deg | 15.7 deg |
| 0.50 m | 8.9 deg | 8.6 deg | 7.8 deg | 7.6 deg | 7.8 deg |
| 0.70 m | 5.5 deg | 5.3 deg | 4.1 deg | 3.1 deg | 3.2 deg |
| 1.00 m | 4.1 deg | 3.8 deg | 3.7 deg | 2.8 deg | 2.9 deg |

结论：只要入口不是尖折角，而是明显圆角化的过渡，`conf` 会快速下降。总转角 `60 deg`、`R=0.25 m`、`blur7` 时，`conf` 约 `30 deg`；`R=0.30 m` 时约 `24.6 deg`。

这类入口不可能通过普通态 `Lpt` 的 `60 deg` 门槛，也很难稳定进入 `Ypt` 的 `40 deg ~ 66 deg` 区间。

## 参考版到底认为圆环角点是多少

参考版没有“圆环夹角”常量。它的合同是代码合同：

| 项 | 参考版代码事实 |
| --- | --- |
| 入环触发 | `check_circle()` 使用 `Lpt*_found`，不使用 `Ypt*_found`。 |
| 参考版普通态 `Lpt` | `73 deg < conf < 120 deg`，并要求近端 `i < 45`。 |
| 当前实验普通态 `Lpt` | `60 deg < conf < 140 deg`，并要求近端 `i < 45`。 |
| `Ypt` | `40 deg < conf < 66 deg`，但不参与 `check_circle()` 入环。 |
| 参考参数 | `sample_dist=0.02`，`angle_dist=0.2`，`line_blur_kernel=7`。 |

所以严格说，参考版不是“认为环岛几何夹角是 84 度”，而是“入环必须先在单侧边线上识别到普通 L 点”。当前实验把普通 Lpt 门槛降到 `60 deg`，按当前 `sample_dist=0.02`、`blur7` 的理想模型约对应真实折线突变 `70.6 deg`。

## 当前判断

1. 当前 `check_circle()` 的入口使用 `Lpt_found`，普通态 `Lpt` 已从参考版的 `73~120 deg` 放宽到 `60~140 deg`。
2. 如果本车实际看到的是锐角/圆角圆环开口，当前 `Lpt` 口径与这类点列不匹配；但这需要先确认参考版原本触发的是哪一条边线上的 L 型开口。
3. 恢复 `sample_dist=0.02 m` 后，角点 `conf` 比 `0.03 m` 更接近参考版；本次又把普通 Lpt 降到 `60 deg`，用于覆盖更弱的圆环入口折角。
4. 对本车来说，下一步板端最有价值的数据不是只看 `Lpt_found`，而是记录入环口附近的 `best_conf`、`best_i`、`Lpt*_found` 和最终 `circle_type`。这样能判断真实峰值常落在 `20 deg ~ 50 deg`，还是已经接近或超过 `60 deg`。
