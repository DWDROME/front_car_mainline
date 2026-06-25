# begin_dist@IN 离线分布 + A 方案印证

> 数据源：`logs/live-circle/*.log` 共 45 条，其中 25 条进了 LEFT_IN。
> 提取字段：`ATGCircleCal to=CIRCLE_LEFT_IN` 的 `begin_dist`，及逐帧 `ATGCircleBeginDiag` 的 `none_left/begin_dist`。

## 1. 旧逻辑下 begin_dist@IN（进 IN 时刻）

- 触发全是 `entry_distance`（24/25），即 `total_distence(丢线起算)>2000` 主导；仅 drive40 是 entry_gyro。
- begin_dist@IN 范围 **2087~3735**，成功案例本身就横跨 2087~3462 → **begin_dist 绝对值无法区分成功/失败**（不能当窗口判据）。

## 2. 真正有相位区分度的量：进 BEGIN→首次丢线距离（≈begin_dist − dist）

| 类别 | drive | 进BEGIN→首丢线 |
|---|---|---|
| 正常入口 | 大多数(34/35/39/44/49/52/54/58/59/60...) | **1000~1500** |
| 异常早丢线（第一个开口） | drive57=28, drive32=78, drive62=146 | **<200** |
| 中间档 | drive51=586, drive50=695 | 600~700 |

→ "第一个开口"特征是 **进 BEGIN 后几乎立刻丢线（<200）**。下界 600 正好把这类挡在外面。

## 3. A 方案（lost_streak>=2 && begin_dist>=600）逐帧印证：drive60-best_run

| 帧事件 | begin_dist | dist(丢线起算) | none_left |
|---|---|---|---|
| 进 BEGIN | 0 | 0 | 0 |
| 首次丢线 | 1268 | 0 | 1 |
| **lost_streak=2（新逻辑触发点）** | **1281** | 13 | 2 |
| 之后持续丢线不恢复 | 1292→1389→... | ↑ | 3,4,... |
| 旧逻辑触发(dist>2000) | ~3276 | 2000 | — |

**结论**：
- 新逻辑在 begin_dist≈**1281** 进 IN；旧逻辑在 ≈**3276**。提前约 **2000 counts（≈0.33m）**。
- 正常 case 的 lost_streak=2 时 begin_dist 已 >600，**下界 600 不影响正常入环**。
- 下界 600 只对早开口（drive32 lost_streak=2@~84）起作用：要等 begin_dist 涨到 600 才进，把早进延后/避免误进。

## 4. 待上车验证

- 实车 `mouth_loss` 行的 begin_dist@IN 是否真集中在 ~1200。
- 早开口场景 begin_dist<600 是否被挡住（不再出现超早 IN）。
- 进 IN 提前 0.33m 后，RUNNING/OUT/END 的 heading 相位是否需重标定。
