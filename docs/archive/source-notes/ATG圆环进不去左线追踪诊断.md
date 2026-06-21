# ATG 圆环进不去：左线追踪诊断（B 类根因）

时间：2026-06-20

承接 `docs/ATG尺度合同与参数来源审计.md`、`docs/ATG圆环角点阈值推导.md`、`docs/ATG角点斜车身问题交接.md`。本文记录"圆环进不去 / 补不了线"现场的根因定性，结论是 **B：左边线没覆盖到圆弧拐点**，并列出可动闸门。

> 阈值/参数以当前 HEAD `f7c6fa3` 为准。本会话期间 conf 阈值与爬线 turn 上限已被放宽并提交（见末尾「已落地改动」），早期讨论里的 `73°/id<25/turn<4` 是旧值。

## 现象（上位机两帧，偏右进左环）

1. **补不了线**：车在赛道偏右处进左环，中线笔直不向左弯，补线没出现。
2. **环进不去**：左侧圆弧清晰可见，但 `circle_type` 一直 `NONE`，引导线直行冲过入口。

## 核心诊断：两个现象是同一根因

补线（`cross_farline_L/R`、`Splicing_*`）只在 `circle_type != CIRCLE_NONE`（已进 `run_circle` 环内分支）才执行。`check_circle()` 没触发 → `circle_type` 恒 `NONE` → 普通巡线 → 中线笔直 → **既进不去环，也轮不到补线**。

> 根因唯一：`check_circle()` 没触发。补线是它的下游，识别不了就没有补线这一步。

## 精确化：识别的是入环口 L 角点，不是"圆弧"

`check_circle()`（`atg_reference/Project/CODE/circle.c:84`，当前值）：

```c
left_entry = Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 35;
```

L 角点来自 `find_corners()`，普通态当前阈值 `60° < conf < 140°`（`shy_Image.c:347`，eac413d 放宽后）。

- 靠 `Lpt0_found`（**左边线上的 L 角点**），不是直接识别那段黑色圆弧。
- 纯圆弧 `conf≈0`（曲率恒定、二阶差分相消），算法看不见圆弧本身；要的是"直道→圆弧入口"那个折点。
- 现场对照：右线（黄，`ipts1`）完整长直 → `is_straight1`✓、`!Lpt1_found`✓；**缺的是 `Lpt0_found`**。

## 定性结论 B：左线没覆盖到圆弧拐点

现场判定为 **B**（区别于 conf 口径问题 A）：

> 车偏右 → 左边线 `ipts0/rpts0s` 离得远、追得短 → 左线没延伸到圆弧拐点 → `find_corners()` 在 `rpts0s` 上扫不到那个角 → `Lpt0_found` 必为 false。

**强化证据**：conf 阈值已放宽到 60°、入环 id 放宽到 35、爬线 turn 上限放宽到 6（见末尾），若此版本下仍进不去，说明问题不在 conf 门槛（A），而在左线根本没扫到拐点（B）。

## 左线追踪链路与闸门

```
种子搜索（起点 x = 80 − begin_x = 73，从 begin_y=108 向上扫到 y=85）
   ├ 闸门A  begin_x=7            横向起点          (headfile.h:25)
   ├ 闸门B  seed_y_top=85        只向上扫到这行     (shy_Image.c:178) ← 移植新增的限制，未动
   └ 闸门C  seed_dark_run=2      连续2暗点确认       (shy_Image.c:177)   → 找不到 = B1 (ipts0_num=0)
爬线 findline_lefthand_adaptive  (imgproc.c:176)
   ├ 闸门D  turn<6               连续转向6次才停    (imgproc.c:180)   ← 已从4放宽(f7c6fa3) → 线短 = B2
   ├ 闸门E  到图像边缘停
   └ 闸门F  block=5 / clip=8     二值化            (reference_step.c:74-75)，未动
透视 → blur → resample(sample_dist=0.02) → rpts0s
   └ 闸门G  find_corners 扫 MIN(rpts0s_num,80) 且 Lpt 要 i<45  (shy_Image.c:309/347)
```

## B1 / B2 区分（现成日志，`report.cpp` 已输出，无需加代码）

抓"偏右进左环"一帧，看日志 `seed=`（`atg_seed0_found@x,y`）和 `raw=`（`ipts0_num/ipts1_num`）：

| 日志 | 判定 | 该动 |
| --- | --- | --- |
| `seed=` 左侧 = **0** | **B1** 种子覆盖不到左边界 | 闸门 A / B |
| 左 `seed=1@x,y` 但 `raw=` 左 num **很小** | **B2** 爬线提前终止 | 闸门 D（已放宽）/ F |
| 左种子 `x,y` 落在**圆环内圈黑块**而非赛道左边界 | 种子认错目标 | 闸门 A + 起搜方向 |

## 可动项清单（标注已动 / 未动）

| # | 可动项 | 位置 | 改前→现状 | 对症 | 备注 |
| --- | --- | --- | --- | --- | --- |
| 1 | **`seed_y_top`** | shy_Image.c:178 | 85（**未动**） | **B1** | **当前头号嫌疑**：种子只向上扫到 85，圆弧入口更远则左线起点都找不到。可降到 70-75 |
| 2 | `turn` | imgproc.c:180 | 4→**6** ✓(f7c6fa3) | B2 | 已放宽；若日志仍显示 turn 终止可再到 8 |
| 3 | `block`/`clip` | reference_step.c:74-75 | 5/8（**未动**） | B2 | 圆弧弱边界二值化丢失；向 9/2 靠，全局影响 |
| 4 | `conf` 阈值 | shy_Image.c:347 | 73→**60** ✓(eac413d) | A | 已降，配合 id 25→35 |
| 5 | `begin_x` | headfile.h:25 | 7（**未动**） | B1 | 偏右时左边界相对位置，影响左右对称起搜，谨慎 |

A 与 B 方向都已各动一项（conf 降到 60、turn 放宽到 6）。**仍进不去时，未动项里头号嫌疑是 `seed_y_top=85`**（大佬版固定 `begin_y` 一行起搜，没有这道墙）。

## 已落地的相关改动（本会话期间提交）

- `eac413d fix(atg-ref): 放宽圆环与十字角点阈值` — conf 73→60、120→140，入环 id 25→35（A 方向）
- `f7c6fa3 fix(atg-ref): 放宽边线爬线转向上限` — turn 4→6（B 方向，对应可动项 #2）

## 治本提醒

若"偏右"是巡线控制跑偏（不是赛道布局要求），治本是巡线回中，而不是一路放宽种子迁就偏移姿态——后者会让正常巡线也更容易认错边界。需先区分这个偏右是"入环前本就靠右"还是"控制跑偏"。

## 下一步

1. 先确认现象图是否在 `f7c6fa3`（turn=6 / conf=60 / id=35）之后拍的；若是，说明放宽 conf/turn 仍不够。
2. 抓"偏右进左环"一帧日志（左 `seed=` / `raw=`），锁定 B1 还是 B2、种子是否认错目标。
3. 据此主攻未动项：优先 `seed_y_top`（B1），其次 `block/clip`（B2）。改代码走 task 流程；保持失败显性，不复用上一帧、不造假角点。

## 关联结论

- **`pixel_per_meter` 尺度不变性**：`local_angle_points` 用 `c=dx/norm`，IPM 坐标统一缩放不改变 `conf`，ppm 不是识别失败原因（详见 `docs/ATG尺度合同与参数来源审计.md`）。
- **`sample_dist=0.02`** 已提交（当前 HEAD 含）。
