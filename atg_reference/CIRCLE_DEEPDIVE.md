# circle.c 逐层精读（当前口径）

> 本文完全基于当前 `atg_reference/Project/CODE/circle.c` 的实况编写，
> 与代码一一对应。不是历史快照，是当前事实源。
>
> 当前圆环状态机为 **三段**：`BEGIN → RUNNING → OUT → NONE`。
> `circle_ref_mode` 在 `BEGIN` 内区分 `NONE / BEGIN_AB / IN_C` 三种补线模式，
> 其余阶段 `circle_ref_mode = CIRCLE_REF_NONE`。
>
> `[STEP]` 指 `port/reference_step.c`，`[IMG]` 指 `shy_Image.c`。
> `[PATCH]` 指 `Patching_Line.c`。

---

## 0. 输入量速查

### 0.1 感知量（来自 [IMG]，每帧刷新）

| 量 | 含义 | 备注 |
|---|---|---|
| `rpts0s` / `rpts0s_num` | 左边线等距采样点 / 点数 | IPM 坐标，`[i][0]`=横 `[i][1]`=纵；`i` 小=近 |
| `rpts1s` / `rpts1s_num` | 右边线等距采样点 / 点数 | 同上 |
| `Lpt0_found` / `Lpt0_rpts0s_id` | 左线 L 角点 / 下标 | id 小=离车近 |
| `Lpt1_found` / `Lpt1_rpts1s_id` | 右线 L 角点 / 下标 | |
| `is_straight0` / `is_straight1` | 左 / 右线是否长直道 | 点数>50 且近 50 点无明显折角 |

采样间距：`sample_dist * pixel_per_meter = 0.02 × 116 ≈ 2.32` IPM 单位/点，约 50 点 = 1 米。

### 0.2 全局环境量（circle.c 读写）

| 量 | 语义 |
|---|---|
| `circle_type` | 当前圆环状态，`NONE / LEFT_BEGIN / RIGHT_BEGIN / LEFT_RUNNING / RIGHT_RUNNING / LEFT_OUT / RIGHT_OUT` |
| `circle_ref_mode` | BEGIN 内补线模式：`NONE → BEGIN_AB → IN_C`；非 BEGIN 阶段为 `NONE` |
| `circle_A/B/C_point` | A/B/C 三个锚点（含 `found / id / raw_x / raw_y`） |
| `circle_heading_rad` | 陀螺积分转角（弧度），圆环态内累积，NONE 时清零 |
| `circle_entry_votes[2]` | 左右入口连续命中投票，≥2 帧进 `*_BEGIN` |
| `circle_entry_suppress_frames` | 入口抑制倒计时，出环后 150 帧禁止重入 |
| `circle_B_streak` / `circle_C_streak` | B / C 连续稳定的帧数，达到 `CIRCLE_B/C_CONFIRM_FRAMES` 后推进 `circle_ref_mode` |
| `circle_begin_lost_streak[2]` | BEGIN 内同侧丢线连续帧数 |
| `circle_loss_start_begin_dist[2]` | 开始丢线时的里程（用于 `abort_late_mouth_loss` 判断） |
| `circle_out_straight_streak[2]` | OUT 内对侧直道连续帧数，出口条件之一 |
| `Count_dis_Flag` | 距离累计开关。`BEGIN` 时=0；`RUNNING / OUT` 时=1；退出后=0 |
| `total_distence` | 编码器累计距离（`Count_dis_Flag==1` 时才累加） |
| `track_type` | 本状态期望跟哪侧边线（`TRACK_LEFT / TRACK_RIGHT`） |
| `begin_y` / `aim_distance` / `road_type` | 退出时恢复为 `BEGIN_Y / AIM_DISTENCE / ROAD_NORMAL` |

### 0.3 废弃/残留标志

| 量 | 状态 | 说明 |
|---|---|---|
| `have_left_line` / `have_right_line` | `// DEPRECATED` | 仅 reset / 丢线时清零，不参与任何状态推进判断 |
| `none_left_line` / `none_right_line` | 仅诊断 | 同侧丢线累计次数，只在日志中有意义 |

---

## 1. 全局常量（三组）

### 1.1 圆环状态门：真正决定流程

这些是唯一需要你在调环时关注的参数。

```c
CIRCLE_ENTRY_CONFIRM_FRAMES        = 2     // 入口连续投票 2 帧才进 BEGIN
CIRCLE_B_CONFIRM_FRAMES            = 2     // B 点连续稳定 2 帧 → ref = BEGIN_AB
CIRCLE_C_CONFIRM_FRAMES            = 2     // C 点连续稳定 2 帧 → ref = IN_C

CIRCLE_HEADING_ENTER_DEG10         = 600   // 60°  BEGIN → RUNNING
CIRCLE_HEADING_OUT_GATE_DEG10      = 1500  // 150° RUNNING → OUT 视觉门（叠加出口 Lpt）
CIRCLE_HEADING_START_OUT_DEG10     = 2000  // 200° RUNNING → OUT 纯陀螺兜底
CIRCLE_HEADING_READY_OUT_TO_END_DEG10 = 2660 // 266° OUT → NONE（需外侧直道 2 帧）
CIRCLE_HEADING_FINISH_SOFT_DEG10   = 3300  // 330° OUT → NONE 软释放

CIRCLE_OUT_LPT_NEAR_ID             = 55    // 出口 Lpt id < 55 才认
CIRCLE_REENTRY_SUPPRESS_FRAMES     = 150   // 出环后抑制重入帧数
```

> heading 阈值单位均为 **0.1°**。出环阈值链单调递增：
> `OUT_GATE(150°) < START_OUT(200°) < READY_OUT_TO_END(266°) < FINISH_SOFT(330°)`。

### 1.2 入口 A/B/C 几何：B/C 搜索器内部参数

正常调车不动，只在 B/C 点定位偏差时才调整。这些是 `circle_find_B()` / `circle_find_C()`
内部的具体约束，**不是状态推进门槛**。

```c
CIRCLE_ENTRY_A_ID_MAX              = 35    // A 点 id 上限
CIRCLE_B_ENTER_ROW                 = 58    // B 搜索行（原图 y）
CIRCLE_ENTRY_AB_DIST_MIN           = 23    // A-B 最小 IPM 距离
CIRCLE_ENTRY_AB_Y_MIN              = 8     // A-B 最小纵向间距
CIRCLE_ENTRY_AB_X_MIN              = 6     // A-B 最小横向间距
CIRCLE_ENTRY_B_SKIP_EDGE_X         = 20    // 跳过边线边缘像素
CIRCLE_ENTRY_B_SCAN_SPAN_X         = 45    // 扫描跨距
CIRCLE_ENTRY_B_MIN_HITS            = 1     // 最小命中黑点数
CIRCLE_ENTRY_B_MIN_RISE_HITS       = 1     // 最小上沿命中数
CIRCLE_ENTRY_B_MAX_STEP_X          = 18    // 相邻命中最大横向步长
CIRCLE_B_UP_MIN                    = 15    // 搜索上界
CIRCLE_B_UP_MAX                    = 50    // 搜索上界
CIRCLE_ENTRY_FAR_LPT_NEAR_RAW_DIST = 20    // C 点远 L 角点最小距离
```

### 1.3 BEGIN 异常撤回：保险丝

`abort_late_mouth_loss` 的触发条件。只在假入口（直道伪 L）卡住时起效。
**不是正常推进路径，不要依赖它调环。**

```c
CIRCLE_BEGIN_LOST_CONFIRM_FRAMES = 2       // 丢线确认帧数
CIRCLE_BEGIN_LOST_RPTS_MAX       = 2       // 丢线时同侧 rpts 点数上限
CIRCLE_BEGIN_MOUTH_MIN_DIST      = 600     // 丢线撤回的最小里程
CIRCLE_BEGIN_LOSS_MAX_DIST       = 4000    // 丢线撤回的最大距离
```

---

## 2. 状态变量与生命周期

```c
circle_type         // 状态机主状态（全局，NONE/LEFT_*/RIGHT_*）
circle_ref_mode     // BEGIN 内补线模式（NONE → BEGIN_AB → IN_C）
circle_A/B/C_point  // 三个锚点结构体（found/id/raw_x/raw_y）
circle_heading_rad  // 陀螺积分转角（弧度），NONE 清零，环内累加
circle_B_streak     // B 点连续存在帧数   ≥ CIRCLE_B_CONFIRM_FRAMES → ref = BEGIN_AB
circle_C_streak     // C 点连续存在帧数   ≥ CIRCLE_C_CONFIRM_FRAMES → ref = IN_C
```

**关键生命周期**：
- 进 `*_BEGIN` 时：`reset_circle_begin_flags()` + `reset_circle_geometry_state()`，`Count_dis_Flag=0`
- 进 `*_RUNNING` 时：`circle_ref_mode=CIRCLE_REF_NONE`，`reset_circle_heading()`，`Count_dis_Flag=0`
- 进 `*_OUT` 时：`circle_out_straight_streak=0`，`Count_dis_Flag=0`
- 退出到 `NONE` 时：`finish_circle_exit()` 全部复位，`circle_count++`，抑制 150 帧重入
- BEGIN 假入口撤回时：`abort_circle_begin()`，清投票、不递增 `circle_count`

---

## 3. 辅助函数

### 3.1 陀螺积分 `update_circle_heading`（约 L~）

```c
circle_type == NONE → 清零 return
无效或死区 → return
heading += yaw_rate * period/1000
```

- `circle_heading_abs_ge(t)`：`|heading_rad| × 1800/π >= t`（`t` 单位 0.1°）
- `circle_heading_enter_ready()`：`heading >= 60°` 的便捷查询

### 3.2 投票与抑制

- `check_circle()` 每帧对左/右分别投票，连续命中 ≥ `CIRCLE_ENTRY_CONFIRM_FRAMES`（2 帧）才进 `*_BEGIN`
- `circle_entry_suppress_frames` 倒计时 > 0 时跳过入口检测，递减后清投票
- `suppress_circle_reentry_after_exit()`：出环后设 150 帧抑制

### 3.3 锚点函数

- `circle_get_A(side, *A)`：从同侧 Lpt 取逆透视坐标，填充 `circle_A_point`
- `raw_dark(x, y, *th)`：原图坐标处自适应阈值判黑
- `circle_inner_hit(side, *A)`：从 A 点种子往内侧扫黑点，验证圆环内圈黑边存在
- `circle_entry_inner_seed(left_side, *x, *y, *rx, *ry)`：计算 inner-hit 的扫描种子坐标

### 3.4 B 点搜索 `circle_find_B`

- 在 `CIRCLE_B_ENTER_ROW`（原图 y=58）行上，从 A 点内侧 `seed_x ± SKIP_EDGE_X` 开始
- 扫描范围 `± SCAN_SPAN_X`，找自适应黑点
- 约束：相邻命中横向步长 ≤ `MAX_STEP_X`，命中数 ≥ `MIN_HITS`，上沿命中 ≥ `MIN_RISE_HITS`
- 成功则填充 `circle_B_point`
- 返回枚举原因码（`ok / no_b / no_extreme / no_v / phase_gate`）

### 3.5 C 点搜索 `circle_find_C`

- 沿同侧近线 `rpts*s` 从近到远扫描
- 本侧 Lpt id 足够小、远线存在 L 角点，且远 L 角点与近线距离 ≥ `FAR_LPT_NEAR_RAW_DIST`（20）
- 取当前最近边线点的逆透视坐标作为 C 点，填充 `circle_C_point`

### 3.6 `log_circle_abc`

打印 A/B/C 当前帧诊断：`side / circle_type / ref_mode / A 坐标 / B 坐标 / C 坐标 / B_streak / C_streak`。

仅在 `FRONT_CAR_CIRCLE_CAL_LOG=1 或 true` 时输出。

---

## 4. 入口判断 `check_circle()`

```
circle_type ≠ NONE → 清投票 return           // 已在圆环态
circle_entry_suppressed() → return            // 抑制期内

左环候选：
  left_base = Lpt0_found && !Lpt1_found        // 同侧有角点，对侧无角点
           && is_straight1                     // 对侧是直道
           && Lpt0_rpts0s_id < A_ID_MAX(35)    // 角点够近
  left_ok = left_base && circle_inner_hit()    // 内侧黑边验证

右环候选：镜像

投票累加；命中 ≥ 2 帧 → circle_type = *_BEGIN，reset 计时/几何/投票
```

**入口判定要点**：
- A 点由同侧 L 角点充当（`Lpt0` 左环 / `Lpt1` 右环）
- inner-hit 验证该角点内侧存在黑色边界（圆环内圈），不是第二个边线断点
- 对侧必须长直道且无 L 角点（排除十字干扰）
- 连续 2 帧投票机制防止单帧噪点误入

**前置互斥**（[STEP]）：`check_circle` 仅在 `!cross_type && !round/ramp/yroad/garage` 时调用 → 十字优先。

---

## 5. 三段状态机分述

### 5.1 `CIRCLE_*_BEGIN` — 入环准备态

```
track_type = side_begin_track(side)   // 贴外侧行驶（左环贴右线、右环贴左线）
Count_dis_Flag = 0                    // 不累距

每帧：
  1) circle_get_A()                   // 刷新 A 点（同侧 Lpt 逆透视坐标）
  2) circle_find_B()                  // 在 B_ENTER_ROW 行上搜索 B 点
  3) circle_find_C()                  // 沿同侧近线搜索 C 点
  4) 更新 streak 和 circle_ref_mode：
     B 连续 ≥ B_CONFIRM_FRAMES → ref = CIRCLE_REF_BEGIN_AB
     C 连续 ≥ C_CONFIRM_FRAMES → ref = CIRCLE_REF_IN_C
  5) log_circle_abc()                 // 打印 A/B/C 诊断

推进条件：
  heading >= 60° → *_RUNNING
  副作用：circle_ref_mode = NONE; reset_circle_heading()

异常撤回：
  同侧丢线 ≥ BEGIN_LOST_CONFIRM_FRAMES
  && 丢线起始里程 ≥ MOUTH_MIN_DIST(600)
  && 丢线起始里程 > LOSS_MAX_DIST(4000)
  → abort_circle_begin()
```

**关键**：`BEGIN` 不进 `RUNNING` 之前，每帧都在重新找 A/B/C。B/C 不稳定时 `circle_ref_mode` 退化到 `NONE` 或 `BEGIN_AB`，补线不发布。

### 5.2 `CIRCLE_*_RUNNING` — 环内主行程

```
track_type = side_begin_track(side)   // 跟内侧线（左环跟左线、右环跟右线）
Count_dis_Flag = 1                    // 累距（用于诊断，非推进条件）

推进到 OUT 的两种路径：
  1) 视觉出口：对侧 Lpt_found && 对侧 Lpt_id < OUT_LPT_NEAR_ID(55) && heading >= 150°
     → *_OUT  "vision_lpt"
  2) 纯陀螺兜底：heading >= 200°
     → *_OUT  "gyro"

副作用：Count_dis_Flag=0; 清 if_lost_*_line
```

**注意**：无距离兜底出口。陀螺失效时由 stall 复位兜底（见 §7）。

### 5.3 `CIRCLE_*_OUT` — 出环交棒

```
track_type = side_out_track(side)     // 贴外侧行驶（左环跟左线、右环跟右线）
Count_dis_Flag = 1

外侧直道检测：
  if (side_out_straight(side)) streak++ else streak=0

退出到 NONE 的两种路径：
  1) 直道门：heading >= 266° && streak >= 2
  2) 软完成门：heading >= 330°
  → finish_circle_exit("straight_exit")
```

**注意**：当前没有独立 `END` 状态，`OUT` 直接退出到 `NONE`。`finish_circle_exit()` 会复位全部参数、递增 `circle_count`、抑制 150 帧重入。

### 5.4 `run_circle()` 总调度

```c
switch(circle_type) {
    case LEFT_BEGIN:  run_circle_begin(CIRCLE_SIDE_LEFT);   break;
    case RIGHT_BEGIN: run_circle_begin(CIRCLE_SIDE_RIGHT);  break;
    case LEFT_RUNNING:run_circle_running(CIRCLE_SIDE_LEFT);  break;
    case RIGHT_RUNNING:run_circle_running(CIRCLE_SIDE_RIGHT);break;
    case LEFT_OUT:    run_circle_out(CIRCLE_SIDE_LEFT);      break;
    case RIGHT_OUT:   run_circle_out(CIRCLE_SIDE_RIGHT);     break;
    default: break;
}
```

---

## 6. 左右对称性

当前三段状态机对左右环**完全对称**：所有 side 函数（`side_lpt_found / side_begin_state / side_out_track` 等）通过 `CIRCLE_SIDE_LEFT / CIRCLE_SIDE_RIGHT` 索引自动切换左右语义。

| 环节 | 左环 | 右环 | 一致性 |
|---|---|---|---|
| 入口判断 | `Lpt0` + `is_straight1` | `Lpt1` + `is_straight0` | 镜像 |
| BEGIN track | `TRACK_RIGHT` | `TRACK_LEFT` | 镜像 |
| RUNNING track | `TRACK_RIGHT` | `TRACK_LEFT` | 镜像 |
| OUT track | `TRACK_LEFT` | `TRACK_RIGHT` | 镜像 |
| 推进门限 | 全部相同 | 全部相同 | 完全一致 |
| inner-hit 方向 | `inner_dx = -1`（左扫） | `inner_dx = +1`（右扫） | 镜像 |
| B 搜索方向 | `seed_x + 20..+65` | `seed_x - 20..-65` | 镜像 |

**注意**：感知层 `Lpt0/Lpt1` 的判定不对称（`Lpt0` 带方向判据、`Lpt1` 无）属于 [IMG] 层问题，不影响 circle.c 内逻辑。

---

## 7. circle.c × reference_step.c 衔接

`circle.c` 负责 **状态怎么跳、本状态希望跟哪侧**。真正发布给控制层的线在 [STEP] 中生成。

| circle.c 产物 | [STEP] 消费 | 效果 |
|---|---|---|
| `circle_type` | `run_atg_elements()` | 非 NONE 才调用 `run_circle()` |
| `circle_type` | `build_circle_spliced_lines()` | 决定是否生成圆环固定补线 |
| `circle_type + circle_ref_mode` | `select_work_line()` | 决定选线来源 `src` |
| `circle_ref_mode == IN_C` | `select_work_line()` | 选 `circle_in_c_left/right`（C 点补线） |
| `track_type` | 近线切换 | 决定默认跟哪侧边线 |
| `Count_dis_Flag` | `update_distance_counters()` | =1 时累加 `total_distence` |

**选线规则**（[STEP] `select_work_line()`）：
```
LEFT_BEGIN + IN_C  → circle_in_c_left
RIGHT_BEGIN + IN_C → circle_in_c_right
LEFT_RUNNING/OUT   → 优先固定右补线
RIGHT_RUNNING/OUT  → 优先固定左补线
否则              → rptsc0/rptsc1（近线）
```

**stall 复位**（[STEP]）：连续 30 帧"圆环活跃但无选线"→ 显式 `ATGCircleStall` 日志复位。

---

## 8. 调试/日志入口

| 环境变量 | 作用 |
|---|---|
| `FRONT_CAR_CIRCLE_CAL_LOG=1` 或 `=true` | 开启 A/B/C 每帧诊断 + 状态跳转日志 |

关键日志行：
```
ATGCircleState: from=* to=* reason=* heading_deg10=* dist=*    // 状态跳转
ATGCircleABC: side=* type=* ref=* A=(*,*) B=(*,*) C=(*,*)...   // A/B/C 锚点
```

出问题时排查顺序：① 看 `ATGCircleState` 确认状态 → ② 看 `ATGCircleABC` 确认 A/B/C 证据 → ③ 看 `select_work_line` 的 `src` 确认线源 → ④ 看 `rptsn_num` 确认线是否成功归一化。
