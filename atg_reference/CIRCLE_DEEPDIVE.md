# circle.c 逐行深度精读(主营文件)

> ⚠️ 2026-06-25 cleanup 后本文是**历史快照**，不再代表当前 `circle.c`
> 的状态机事实。当前事实源以 `atg_reference/Project/CODE/circle.c`、
> `.trellis/tasks/06-25-circle-begin-in-phase-anchor/research/cleanup-inventory.md`
> 的执行决策、以及 `atg_reference/PORTING.md` 的 Change Rationale 为准。
> 主要变化:旧 `circle_in_length/circle_in_distance`、`CIRCLE_*_DISTANCE*`
> 距离兜底、`if_clean_pid`、`broadcast_flag`、`is_large/small_circle`
> 已从活跃 LS2K 编译链清掉;入口日志已正名为 `ATGCircleEntryInnerHit`;
> 入环主线已改为 A(`Lpt0/Lpt1`) -> B 到行(`B_row`) -> IN 找 C ->
> `circle_in_c_left/right` C 点补线;旧 `mouth_loss` 只保留为诊断字段。
> END 只保留 `vision_lpt_exit` 和基于 END 内局部编码器距离的
> `end_encoder_release`,其余失败由 `ATGCircleStall` 显式复位。

> 目标:把圆环主营文件 `atg_reference/Project/CODE/circle.c`(约 680 行)讲透。
> 所有外部输入量(感知量 / 环境量)的语义、来源都内联在本文,读本文即可完全理解 circle.c,
> 无需再翻其他文件。`[STEP]` 指衔接层 `port/reference_step.c`,`[IMG]` 指感知层 `shy_Image.c`。
>
> 全文只陈述代码确凿事实,标注左右不一致点 / 死代码 / 踩坑史;不含重构主张。

---

## 0. 输入量速查(讲透 circle.c 的前提)

### 0.1 感知量(来自 [IMG] image_handle / find_corners,每帧刷新)

| 量 | 含义 | 关键语义 |
|---|---|---|
| `rpts0s` / `rpts0s_num` | **左**边线等距采样点 / 点数 | `0=左`,IPM 逆透视坐标,`[i][0]`=横向 `[i][1]`=纵向 |
| `rpts1s` / `rpts1s_num` | **右**边线等距采样点 / 点数 | `1=右` |
| 下标 `i` | 采样点序号 | **`i` 小=离车近,`i` 大=离车远**(从车前 `begin_y` 往上爬) |
| `Lpt0_found` / `Lpt0_rpts0s_id` | **左**线 L 角点是否存在 / 其在 rpts0s 的下标 | id 小=角点离车近 |
| `Lpt1_found` / `Lpt1_rpts1s_id` | **右**线 L 角点 / 下标 | |
| `is_straight0` / `is_straight1` | **左** / **右**线是否长直道 | 点数>50 且近 50 点内无明显折角(conf<20°) |
| `conf1` / `conf2` | 左 / 右当前角点显著度 | 单位弧度,角点判据 60°~140° |

采样间距 `sample_dist*pixel_per_meter = 0.02*116 ≈ 2.32` IPM 单位/点 → `1.0/sample_dist = 50` 点 ≈ 1m。

> **感知层自带的左右不对称(重要)**:`Lpt0`(左)判定带方向判据
> `rpts0s[im1][0]>rpts0s[ip1][0] && rpts0s[im1][1]>rpts0s[ip1][1]`([IMG] L348);
> `Lpt1`(右)**无方向判据**,只要 conf2∈(60°,140°) 且 id<60([IMG] L397)。
> → 右角点更易被判定,圆环右环入口天然比左环松。

### 0.2 环境量 / 衔接量(来自 [STEP],circle.c 读写其中一部分)

| 量 | 来源/消费 | 语义 |
|---|---|---|
| `total_distence` | [STEP] update_distance_counters L167 | `Count_dis_Flag==1` 才累加编码器增量,`==0` **直接清零**。int16,饱和 32767 |
| `Count_dis_Flag` | circle.c 写,[STEP] 读 | 距离累计总开关。进 BEGIN 时置 0,**内侧丢线帧**才置 1 |
| `circle_heading_rad` | circle.c 内部,陀螺积分 | 见 §3.1。进 IN 清零,后续累计转角 |
| `g_circle_begin_dist` | [STEP] L197 | 进 BEGIN 后累计里程,离开清零;用于 idle 撤回 |
| `track_type` | circle.c 写,[STEP] 选线读 | `TRACK_LEFT`=跟左线,`TRACK_RIGHT`=跟右线 |

> **关键推论**:进 BEGIN 时 `Count_dis_Flag=0`(清零 total_distence),只有内侧丢线帧
> (circle.c L342/L518)才置 1 → **BEGIN 阶段的 `total_distence` 实际是"从首次内侧丢线起算的里程"**。
> 另一个容易漏掉的点:[STEP] 一帧顺序是 `run_atg_elements()` → `update_distance_counters()`。
> 所以 `circle.c` 本帧状态跳转看到的是上一帧已经累计好的 `total_distence`;
> 本帧写 `Count_dis_Flag=1/0` 后,距离累计/清零到下一次 `update_distance_counters()` 才生效。

### 0.3 circle.c 写出的副作用标志(当前消费情况)

| 标志 | 设置时机 | 语义 |
|---|---|---|
| `if_clean_pid=1` | 进 IN / OUT | 历史 PID 清零标志;当前 port 控制层不读它,reset 路径会清 0 |
| `if_lost_right_line/left=0` | 进 IN/OUT/END | 清 `cross_farline_L/R` 的丢线 latch,影响远线 seed 分支和诊断 |
| `is_large_circle/is_small_circle` | IN 内按 `rpts*s_num>70` 判 | 大小环历史标志;当前 port 不参与速度控制 |
| `broadcast_flag=1` | 进 END | 旧参考的播报/提示标志;当前实车主链不读它转向 |
| `road_type/begin_y/aim_distance` | END 退出复位 | 恢复普通巡线/搜线/预瞄参数;`aim_distance` 会进入 [STEP] 选线归一化 |
| `circle_count++` | END 自然退出 | 已过环计数;reset/stall 撤回不递增 |

---

## 1. 全局常量 enum (L29-51)

```c
CIRCLE_ENTRY_CONFIRM_FRAMES      = 2      // 入口连续 2 帧投票才进 BEGIN
CIRCLE_BEGIN_LOST_CONFIRM_FRAMES = 2      // 内侧丢线累计 2 次才允许进 IN
CIRCLE_IN_DISTANCE_CONFIRM       = 2000   // IN→RUNNING 的距离兜底(陀螺失效时)
CIRCLE_RUNNING_FORCE_OUT_COUNTS  = 16000  // RUNNING 距离强制出环,≈2.76m(16000/5800),陀螺失效兜底
CIRCLE_HEADING_ENTER_DEG10       = 600    // 60°  进 IN / IN→RUNNING 的陀螺门
CIRCLE_HEADING_START_OUT_DEG10   = 2000   // 200° RUNNING→OUT 纯陀螺兜底
CIRCLE_HEADING_OUT_GATE_DEG10    = 1500   // 150° 视觉出环时的陀螺门(防假角点早触发)
CIRCLE_OUT_LPT_NEAR_ID           = 55     // 对侧出口角点 id<55 才算"已到出环口"(drive02 实测 id=51)
CIRCLE_END_LPT_EXIT_ID           = 15     // 出口角点 id<15(很近)→ 趁有线交棒普通巡线
CIRCLE_HEADING_FORCE_OUT_DEG10   = 2500   // 250° —— ★定义了但 run_circle 未引用 = 死常量
CIRCLE_HEADING_READY_OUT_TO_END_DEG10 = 2660  // 266° OUT→END(drive24 可出环 / drive25 250°早退会回起点)
CIRCLE_HEADING_FINISH_DEG10      = 3550   // 355° 满圈,左 END 视觉退出的硬门
CIRCLE_REENTRY_SUPPRESS_FRAMES   = 150    // 出环后抑制重入帧数
CIRCLE_GYRO_DEADZONE_RAD_S       = 0.065  // 陀螺死区,|yaw_rate|≤此值不积分
CIRCLE_RAD_TO_DEG10              = 1800/π // 弧度→0.1度
```

> heading 阈值单位都是 **0.1°**,由 `circle_heading_rad`(陀螺积分弧度)× `RAD_TO_DEG10` 得到。
> 整条出环阈值链是单调递增的:`OUT_GATE(150°) < START_OUT(200°) < READY_OUT_TO_END(266°) < FINISH(355°)`。

---

## 2. 状态变量与生命周期

```c
enum circle_type_e circle_type     // 当前圆环状态机状态(全局,NONE/LEFT_*/RIGHT_*),[STEP] 据此调度
int none_left_line, none_right_line // 内侧丢线累计计数(只增,不在恢复时减)
int have_left_line, have_right_line // 重新找到线计数 —— ★当前基本残留(见 §5.1)
int64_t circle_encoder             // 防重复触发用 —— ★仅右环 IN 赋值,实际未参与判定(残留)
static int circle_left/right_entry_votes  // 入口连续命中投票
static int circle_entry_suppress_frames   // 入口抑制倒计时
static float circle_heading_rad           // 陀螺积分转角(弧度)
```

`reset_circle_begin_flags()`(L137):把 none_/have_ 四个全清零。
`reset_circle_entry_votes()`(L101):清左右投票。

---

## 3. 辅助函数

### 3.1 陀螺积分 `update_circle_heading`(L150-167)
```c
circle_type==NONE → reset(heading=0); return        // 非圆环态恒清零
!valid || period<=0 → return                         // 无效陀螺帧跳过
|yaw_rate| <= 0.065 → return                          // 死区内不积分(滤静止漂移)
circle_heading_rad += yaw_rate_rad_s * period_ms/1000 // 梯形积分,累加转角
```
- `circle_heading_abs_ge(t)`(L169):`|heading_rad|*RAD_TO_DEG10 >= t`,把弧度转 0.1° 比阈值
- `reset_circle_heading()`:进 IN 时调,把环内转角从 0 起算

### 3.2 投票 / 抑制(L101-135)
- `suppress_circle_entry_frames(n)`:设抑制倒计时(取 max),并清投票
- `suppress_circle_reentry_after_exit()`:出环后调,抑制 150 帧防立刻重入
- `circle_entry_suppressed()`:倒计时>0 则递减并清投票、返回 1(本帧不检测入口)

### 3.3 内侧黑点验证 `circle_entry_find_inner_hit_on_seed_line(left_side)`(L194-295)★

**这是"弱双断点"的第二证据,逐行讲透:**
```c
取 lpt_id/lpt_num/found_lpt = 该侧(left_side?左:右)的 Lpt id / 点数 / 是否找到
若 !found_lpt || lpt_num<=0 → 打 near=0 日志, return 0      // 无角点直接判负

// 1) 取种子点:角点处的边线点,转回【原图】坐标,再偏移
左:seed_raw = Cal_inv_rot(rpts0s[lpt_id]) ;  x-10(往左多偏,扩大内圆扫描) y-5
右:seed_raw = Cal_inv_rot(rpts1s[lpt_id]) ;  x+5                          y-5
seed 再 clip 到图像有效范围

// 2) 从种子往【内侧】扫黑点
inner_dx = left_side ? -1 : 1               // 左环往原图 x 减小(左)、右环往 x 增大(右)
3 条 ray:dy = {0,-1,-2}(略微上挑),每条最多 45 步
每步:算 block_size 邻域局部自适应阈值(均值 - clip_value)
     若 AT_IMAGE(x,y) < 局部阈值 → 命中黑点 hit,break

return hit_y >= 0                            // 扫到黑点=1
```

> **它证明的是**:从入口角点往赛道内侧扫,存在黑色边界结构(圆环内圈黑边)。
> **它不是**第二个边线断点,只是"内侧 raw 结构验证"。故整套入口门叫"**弱双断点**":
> 单角点 + 对侧直 + 内侧黑点,而非"同侧两个边线断点"。

---

## 4. 入口判断 `check_circle()`(L297-331)

```c
circle_type != NONE → 清投票 return            // 已在圆环态,不重复检测
circle_entry_suppressed() → return             // 抑制期内不检测

// 左环入口候选
left_entry_base  = Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 35
left_entry       = left_entry_base && circle_entry_find_inner_hit_on_seed_line(1)
// 右环入口候选(镜像)
right_entry_base = !Lpt0_found && Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 35
right_entry      = right_entry_base && circle_entry_find_inner_hit_on_seed_line(0)

votes 连续累加;命中 >= 2 帧 → 置 circle_type=*_BEGIN; reset_begin_flags; Count_dis_Flag=0; 清投票
```

**左环入口语义**(车要左转进环):
- `Lpt0_found`:内侧(左)出现入口 L 角点
- `!Lpt1_found`:外侧(右)无角点
- `is_straight1`:外侧(右)是直的
- `Lpt0_rpts0s_id<35`:角点在近处(≈0.7m 内)才认,防远端透视畸变误判
- `+ inner_hit(1)`:左角点内侧扫到黑边

**前置互斥**([STEP] L320):`check_circle` 仅在 `!cross_type && !round/ramp/yroad/garage` 时调用 → 十字优先,十字认领后本帧不检测圆环。

---

## 5. 左环 run_circle 五状态(L337-510)

### 5.1 CIRCLE_LEFT_BEGIN(L337-378)— 等入环口内侧丢线
```c
track_type = TRACK_RIGHT                        // 贴外侧右线行驶
if (rpts0s_num < 2 && !Lpt0_found) {            // 内侧(左)线几乎全丢
    Count_dis_Flag = 1;                          // ★开启 total_distence 累计(=lost_dist 起点)
    none_left_line++;
    have_left_line = 0;
}
// 进 IN:丢线确认 + (距离 或 陀螺)
none_left_line>=2 && total_distence>circle_in_distance(2000) → LEFT_IN  "entry_distance"
none_left_line>=2 && heading>=600(60°)                       → LEFT_IN  "entry_gyro"
   进 IN 副作用:reset_heading; if_lost_right_line=0; reset_begin_flags; if_clean_pid=1; Count_dis_Flag=0
```
- L349-357 注释:legacy 的"丢线后线重现(have_left_line++)再进 IN"已废弃,因偏置进环时内侧线追不到"重现→再变短"会卡 BEGIN。现仅要求"已丢线 + 距离/陀螺"。
- **`have_left_line` 在此只被清零、不参与判定 → 残留变量**。
- **撤回**(不在 circle.c,在 [STEP] L700 `revoke_idle_circle_begin`):`none_left_line==0 && begin_dist>6000(≈1m)` → 复位 NONE,防直道伪 L 误入后锁死。

### 5.2 CIRCLE_LEFT_IN(L379-413)— 固定动作切入
```c
cross_farline_L();                              // 远线搜索(刷新标志位,补线不依赖它)
track_type = TRACK_LEFT; Count_dis_Flag = 1
rpts0s_num>70 ? is_large_circle : is_small_circle  // 判大小环
heading>=600(60°)            → LEFT_RUNNING; track_type=TRACK_RIGHT; none_right_line=0  "gyro"
total_distence>2000          → LEFT_RUNNING; 同上                                       "distance"
```
- 选线由 [STEP] 接管:`LEFT_IN` → 固定右补线 `Splicing_rightline_center`(日志 sel=5 circle_in_fixed_right)。
- L392-398 注释:legacy 的"对侧线重现计数(none_right_line)进 RUNNING"已废弃,改纯陀螺/距离。

### 5.3 CIRCLE_LEFT_RUNNING(L414-452)— 环内主行程
```c
track_type = TRACK_RIGHT; Count_dis_Flag = 1
// 出环触发,优先级:
1) Lpt1_found && Lpt1_rpts1s_id<55 && heading>=1500(150°) → LEFT_OUT  "vision_lpt"  // 对侧出口角点+陀螺门
2) heading>=2000(200°)                                    → LEFT_OUT  "gyro"        // 纯陀螺兜底
3) total_distence>16000                                   → LEFT_OUT  "distance"    // 距离兜底
   出 OUT 副作用:Count_dis_Flag=0; if_lost_right_line=0; if_clean_pid=1
```
- L418-427 注释:legacy 的"Lpt 出现即截断对侧线长度"已废弃,改"对侧角点 + 陀螺门"。
- 选线:右线自然点数够([STEP] `>=20`)用实时右线,否则继续固定右补线。

### 5.4 CIRCLE_LEFT_OUT(L453-480)— 准备出环(对照参考的 ReadyoutRing)
```c
track_type = TRACK_LEFT; Count_dis_Flag = 1
heading>=2660(266°)  → LEFT_END  "gyro"
total_distence>4500  → LEFT_END  "distance"     // ★注意此处是 4500,非 enum 常量(硬编码)
```
- 选线:固定右补线(sel=6);无补线时 [STEP] 兜底用 `rptsc1`(sel=9 out_rptsc1)防崩塌。

### 5.5 CIRCLE_LEFT_END(L481-510)— 出环交棒(对照 outRing)
```c
track_type = TRACK_RIGHT; broadcast_flag = 1; Count_dis_Flag = 1
end_lpt_exit_l = heading>=3550(355°满圈) && Lpt1_found && Lpt1_rpts1s_id<15  // ★视觉退出必须叠满圈门
if (end_lpt_exit_l || total_distence>=7500) {                                // 7500 硬编码
    circle_type=NONE; road_type=ROAD_NORMAL; begin_y=BEGIN_Y; aim_distance=AIM_DISTENCE;
    is_large/small=0; if_lost_right/left_line=0; circle_count++;
    none_/have_ 全清; suppress_circle_reentry_after_exit();   // 抑制 150 帧重入
}
```
- L486-488 注释(踩坑):drive59/60/61/62 证明 `Lpt1` 单独放行会在普通巡线仍反向/无线时撤掉 END 固定线 → 必须叠 355° 满圈 heading,否则继续用 sel=14 带出环。
- 选线:[STEP] 用右直道交接线(sel=14 circle_end_fixed_right),防出环口右线变短把 guide 拉负回头。

---

## 6. 右环五状态 + 左右不一致总表(L513-678)

右环结构与左环镜像(左右 Lpt / track_type / none_line 互换)。**但存在多处实质不一致:**

| 环节 | 左环 | 右环 | 不一致 |
|---|---|---|---|
| 入口角点方向判据(感知层) | Lpt0 **有**方向判据 | Lpt1 **无**方向判据 | 右环入口更易命中 |
| BEGIN 内侧丢线阈值 | `rpts0s_num<2`(L341) | `rpts1s_num<10`(L517) | **右环更松更早**触发丢线 |
| IN 进入副作用 | 无 `circle_encoder` | `circle_encoder=current_encoder`(L536/547) | 右环多赋值(但未被消费=残留) |
| IN→RUNNING 额外动作 | 无 | `begin_y=BEGIN_Y`(L577/585) | 右环重置搜线起点 |
| OUT→END 阈值 | heading 2660 / dist 4500 | heading 2660 / dist 4500 | 一致 |
| END 视觉退出门 | `heading>=3550 && Lpt1<15`(L489) | **仅** `Lpt0<15`(L660),**无满圈门** | **右环缺 heading 硬门** |
| END 距离兜底 | `>=7500`(L493) | `>=4000`(L661) | 阈值不同 |

> 右环 BEGIN 注释(L516)直言:"右环沿用原来的 <10 阈值" → 左用新逻辑、右用旧逻辑,是当前混乱的直接证据。
> 右环 END(L655-659)注释也确认仅靠 Lpt0 近即退,无满圈保护。

---

## 7. circle.c x reference_step.c 衔接点清单

`circle.c` 只负责"状态怎么跳"和"本状态希望跟哪侧";真正发布给控制层的线在
`reference_step.c` 里生成、选择、归一化。

| circle.c 产物 | reference_step.c 消费点 | 当前效果 |
|---|---|---|
| `circle_type` | `run_atg_elements()` L353 | 非 NONE 才调用 `run_circle()` |
| `circle_type` | `build_circle_spliced_lines()` L461-L489 | 决定是否生成圆环固定补线 |
| `circle_type` | `select_work_line()` L502-L530 | 决定选线来源 `src` |
| `circle_type` | `control_input_from_current_frame()` | 非 NONE 使 `element_active=1`, 控制层切 `element_target_rps` |
| `Count_dis_Flag` | `update_distance_counters()` L167-L180 | 为 1 时累加 `total_distence`;为 0 时直接清零 |
| `track_type` | `select_work_line()` L542-L552 | 普通/兜底路径中 `TRACK_LEFT -> rptsc0`, 否则 `rptsc1` |
| 进入 `*_BEGIN` | `update_distance_counters()` L195-L205 | 累加 `g_circle_begin_dist`,离开 BEGIN 后保存到 `g_circle_begin_last_dist` |
| BEGIN 无丢线 | `revoke_idle_circle_begin()` L700-L711 | `begin_dist>6000` 且 `none_*_line==0` 时复位 NONE |
| 选线为空 | `exit_circle_after_stall()` L714-L731 | 圆环态连续 30 帧 `rptsn` 为空时复位 NONE |
| `if_lost_left/right_line` | `cross_farline_L/R()` + report | 影响远线起点是否走 Lpt 分支;也进入诊断输出 |
| `is_large_circle/is_small_circle` | 当前 port 无控制消费 | 只 reset/报告/旧注释;`road.c` 里的大小环 road_type 分支已注释 |
| `if_clean_pid` | 当前 port 无控制消费 | 只 reset/旧参考保留;`code/core/control.cpp` 不读它 |
| `broadcast_flag` | 当前 port 无实车控制消费 | 旧 `Cpu0_Main.c` 用于串口播报;当前运行链主要靠 state-change beep,不读该 flag |

**最重要的实际控制链只有两条**:

```text
circle_type -> select_work_line/src -> rptsn -> atg_lookahead_error() -> guide_error
circle_type != NONE -> element_active=1 -> control.cpp 使用 element_target_rps / element_reverse_brake
```

所以后续不要把 `if_clean_pid`、`broadcast_flag`、`is_large_circle` 当成当前实车控制主因。

---

## 8. 选线来源表(src 语义)

`src` 是当前最有用的圆环诊断字段,来自 `atg_reference_selected_line_source_id()`:

| src | 名称 | 触发状态 | 线来源 | 控制含义 |
|---:|---|---|---|---|
| 1 | `circle_running_fixed_left` | `RIGHT_RUNNING` 且左自然线不足 | 固定左补线 | 右环环内兜底 |
| 2 | `circle_in_fixed_left` | `RIGHT_IN` | 固定左补线 | 右环入环固定动作 |
| 3 | `circle_out_fixed_left` | `RIGHT_OUT` | 固定左补线 | 右环出环准备 |
| 4 | `circle_running_fixed_right` | `LEFT_RUNNING` 且右自然线不足 | 固定右补线 | 左环环内兜底 |
| 5 | `circle_in_fixed_right` | `LEFT_IN` | 固定右补线 | 左环入环固定动作 |
| 6 | `circle_out_fixed_right` | `LEFT_OUT` | 固定右补线 | 左环出环准备 |
| 7 | `circle_end_left_half` | `RIGHT_END` | 当前左半线 `rptsc0` | 右环 END 交棒 |
| 8 | `circle_end_right_half` | 当前代码已无 LEFT_END 选中路径 | 旧右半线 | 保留 id,非当前左 END 主线 |
| 9 | `out_rptsc1` | `LEFT_OUT` 固定补线为空且右半线存在 | 当前右半线 | LEFT_OUT 防空线兜底 |
| 10 | `rptsc0` | 普通 `TRACK_LEFT` | 当前左半线 | 普通巡线 |
| 11 | `rptsc1` | 普通 `TRACK_RIGHT` | 当前右半线 | 普通巡线 |
| 12 | `far_left` | CROSS/GARAGE 远线路径 | 左远线 | 十字/车库显示或控制路径 |
| 13 | `far_right` | CROSS/GARAGE 远线路径 | 右远线 | 十字/车库显示或控制路径 |
| 14 | `circle_end_fixed_right` | `LEFT_END` | 固定右直道交接线 | 左环 END 当前主线 |

drive59/60/61/62 的关键事实就是: `LEFT_END src=14 guide=+6.82` 时方向正确;
退出到 `CIRCLE_NONE src=10/11` 后 guide 变 0 或负,所以问题是"何时撤掉 src14"。

---

## 9. cross_farline_L/R 在圆环里的真实作用

`circle.c` 只在两个 IN 状态显式调用:

```c
CIRCLE_LEFT_IN  -> cross_farline_L()
CIRCLE_RIGHT_IN -> cross_farline_R()
```

这两个函数不是简单"十字远线",它们在圆环状态下也会刷新远端线缓存和丢线标志:

注意不要把这里和 `circle_entry_find_inner_hit_on_seed_line()` 混在一起:
入口 inner-hit 的 seed 是 `circle.c` 内部 raw 黑点扫描,左侧当前偏移是 `x-10,y-5`;
`cross_farline_L/R` 是 `cross.c` 的远线搜索,Lpt 分支仍是旧参考的 `x-5/+5,y-17`。
前者服务 `check_circle()` 入口确认,后者服务 IN/OUT/END 远线缓存、截断和诊断。

### 9.1 cross_farline_L()

入口分支:

- 若 `Lpt0_found && rpts0s_num>=3 && !if_lost_left_line`:
  - 从左近角点转 raw 后偏移 `x-5,y-17`;
  - 截断 `rpts0s_num = Lpt0_rpts0s_id-1`;
  - 用该点向上扫左远线。
- 若处于 `CIRCLE_LEFT_IN`:
  - `ipts0_num>12 && !if_lost_left_line` 时用左近线末端 `ipts0[ipts0_num-3]+(15,-5)` 作远线起点;
  - 否则置 `if_lost_left_line=1`,用固定点 `(40, begin_y*0.85)`。
- 若处于 `CIRCLE_RIGHT_OUT/RIGHT_END`:
  - 用固定点 `(80, begin_y*0.85)`。

输出:

- `far_ipts0/far_rpts0/far_rpts0s/far_Lpt0_found`;
- 可能改 `rpts1s_num/rptsc1_num` 截断对侧角点后的线;
- 可能置 `if_lost_left_line=1`。

### 9.2 cross_farline_R()

入口分支:

- 若 `Lpt1_found && Lpt1_rpts1s_id>2 && !if_lost_right_line`:
  - 从右近角点转 raw 后偏移 `x+5,y-17`;
  - 截断 `rpts1s_num = Lpt1_rpts1s_id`;
  - 用该点向上扫右远线。
- 若处于 `CIRCLE_RIGHT_IN`:
  - `ipts1_num>12 && !if_lost_right_line` 时用右近线末端 `ipts1[ipts1_num-3]+(-15,-5)`;
  - 否则置 `if_lost_right_line=1`,用固定点 `(120, begin_y*0.85)`。
- 若处于 `CIRCLE_LEFT_OUT/LEFT_END`:
  - `LEFT_OUT` 会尝试用当前 `rptsc1` 斜率外推动态 seed;
  - 不满足时回固定点 `(80,105)` 或 `(110,105)`。

输出:

- `far_ipts1/far_rpts1/far_rpts1s/far_Lpt1_found`;
- 可能改 `rpts0s_num/rptsc0_num` 截断对侧角点后的线;
- 可能置 `if_lost_right_line=1`。

### 9.3 当前 port 与旧参考的差异

旧 `Cpu0_Main.c` 会直接用 `far_Lpt*` 或 `far_rpts*s` 拼接 `Splicing_*`。
当前 `reference_step.c::build_circle_spliced_lines()` 对 `*_IN/OUT` 主要改成 raw 固定几何补线,
不再强依赖 `far_Lpt*` 才能建控制线。也就是说:

- `cross_farline_L/R` 仍会刷新远线和 `if_lost_*` 诊断;
- 但当前 `src=2/3/5/6/14` 这些固定补线不是直接由 `far_Lpt*` 拼出来的;
- 不要把 "far=0/0" 直接等同于固定补线没打出来,要看 `src` 和 `sel`。

---

## 10. heading 阈值与物理阶段

heading 从进入 `*_IN` 时清零,之后在圆环态按陀螺积分累计。

| 阈值 | 度数 | 代码位置 | 物理含义 |
|---|---:|---|---|
| `CIRCLE_HEADING_ENTER_DEG10=600` | 60° | BEGIN->IN gyro / IN->RUNNING gyro | 已切入环口,允许从入环动作转环内 |
| `CIRCLE_HEADING_OUT_GATE_DEG10=1500` | 150° | RUNNING->OUT vision_lpt 门 | 看到出口角点时,要求车已转过足够角度,防假 Lpt |
| `CIRCLE_HEADING_START_OUT_DEG10=2000` | 200° | RUNNING->OUT gyro | 视觉不可靠时的纯陀螺出环兜底 |
| `CIRCLE_HEADING_READY_OUT_TO_END_DEG10=2660` | 266° | OUT->END | 从 ReadyoutRing 交到 END/outRing 的时机;用户要求保持 2660 |
| `CIRCLE_HEADING_FINISH_DEG10=3550` | 355° | 左 END 视觉退出 | 满圈附近才允许 `Lpt1<15` 撤掉 `src=14` |

关键点:

- `2660` 是 OUT->END,不是最终退出;它决定什么时候开始用 END 交接线。
- `3550` 是左 END 的最终视觉退出硬门;它解决的是 `Lpt1` 单独早退导致普通巡线反向。
- `CIRCLE_HEADING_FORCE_OUT_DEG10=2500` 当前无引用,不是有效门限。

---

## 11. 距离阈值的 per-state 语义

`total_distence` 不是全程累计。`Count_dis_Flag=0` 时每帧清零,所以每段距离从该状态第一次置
`Count_dis_Flag=1` 后重新算。

执行顺序补充:每帧先跑 `run_circle()`,再由 [STEP] `update_distance_counters()` 根据当前
`Count_dis_Flag` 更新 `total_distence`。因此:

- BEGIN 丢线帧把 `Count_dis_Flag` 置 1 后,`lost_dist` 从该帧之后开始增长;
- 进 IN/RUNNING/OUT/END 时通常先把 `Count_dis_Flag=0`,本帧末尾会清距离,下一状态下一帧再重新置 1;
- 表格里的 state distance 都是"状态内已累计到当前帧之前"的距离门,不是进入状态瞬间的全程里程。

| 状态 | Count_dis_Flag 时机 | total_distence 起算点 | 阈值 |
|---|---|---|---|
| BEGIN | 只有内侧丢线帧置 1 | 首次内侧丢线后 | `>2000` 进 IN |
| IN | 状态内每帧置 1 | 进 IN 后 | `>2000` 进 RUNNING |
| RUNNING | 状态内每帧置 1 | 进 RUNNING 后 | `>16000` 强制 OUT |
| OUT | 状态内每帧置 1 | 进 OUT 后 | `>4500` 强制 END |
| LEFT_END | 状态内每帧置 1 | 进 END 后 | `>=7500` 退出 NONE |
| RIGHT_END | 状态内每帧置 1 | 进 END 后 | `>=4000` 退出 NONE |

另有 `g_circle_begin_dist`:只要在 `*_BEGIN` 就累加,不管 `Count_dis_Flag`;
它才是日志里的 `begin=` 语义,用于 idle revoke。

---

## 12. 异常路径与复位集

当前圆环有三类退出/复位:

| 路径 | 所在函数 | 条件 | 复位动作 |
|---|---|---|---|
| 自然 END 退出 | `circle.c` LEFT/RIGHT_END | 视觉退出或 END 距离兜底 | `circle_type=NONE`,恢复 `road_type/begin_y/aim_distance`,清大小环/丢线/none/have,`circle_count++`,抑制重入 |
| BEGIN idle 撤回 | `reference_step.c::revoke_idle_circle_begin()` | BEGIN 后 `none_*_line==0 && begin_dist>6000` | `reset_circle_to_none()`,无 `circle_count++` |
| stall 撤回 | `reference_step.c::exit_circle_after_stall()` | 圆环态连续 30 帧无选线 | `reset_circle_to_none()`,无 `circle_count++` |

`reset_circle_to_none()` 会打 `ATGCircleReset`,并清:

- `circle_type`, `road_type`, `begin_y`, `Count_dis_Flag`, `aim_distance`;
- `is_large_circle/is_small_circle`;
- `if_lost_left/right_line`;
- `none_left/right_line`, `have_left/right_line`;
- `if_clean_pid`, `g_circle_stall_frames`, `g_circle_begin_dist/last_dist`;
- 并调用 `suppress_circle_reentry_after_exit()` 抑制 150 帧重入。

自然 END 退出和 reset 撤回的区别:

- 自然退出会 `circle_count++`;
- reset 撤回不会加 `circle_count`;
- reset 会清 `if_clean_pid=0`;自然退出没有显式清 `if_clean_pid`。

---

## 13. 大小环与速度的真实消费

`circle.c` 在 `*_IN` 里用内侧点数判断大小环:

```c
rpts0s_num > 70 或 rpts1s_num > 70 -> is_large_circle=1
否则 is_small_circle=1
```

但当前 port 中:

- `road.c` 里基于 `is_large_circle` 设置 `Large_Circle/Small_Cirlce` 的分支已注释;
- `code/core/control.cpp` 不读取 `is_large_circle/is_small_circle`;
- 当前实车速度只看 `element_active`:圆环态统一用 `element_target_rps`;
- `atg_reference_mainline.cpp` 只按 `circle_type` 对 guide 做阶段性 scale,不看大小环。

所以"大小环"目前是诊断/历史残留,不是当前速度控制主线。

---

## 14. 当前 circle.c 的客观问题清单(供下一步清理)

1. **入口命名不准**:
   `ATGCircleEntryBreakpoints` 实际不是完整双断点,而是"单 Lpt + 对侧直 + 内侧黑点"。
   如果改名,函数内两处日志都要改。

2. **死常量 / 死变量**:
   `CIRCLE_HEADING_FORCE_OUT_DEG10=2500` 未引用;
   `circle_encoder` 只在右环 IN 赋值,无消费;
   `have_left_line/have_right_line` 在 circle 当前逻辑只清零/日志,不再参与进 IN。

3. **硬编码阈值散落**:
   `OUT->END` 的 `4500`,左 END `7500`,右 END `4000` 都直接写在条件里。
   数值不变也应提到 enum,否则后续调参容易漏。

4. **左右不一致**:
   左/右 Lpt 感知方向判据不同;
   左/右 BEGIN 丢线阈值 `<2` vs `<10`;
   左 END 有 `heading>=3550` 硬门,右 END 没有;
   左/右 END 距离兜底 `7500` vs `4000`。

5. **真实主线分散在两文件**:
   状态跳转在 `circle.c`,距离/撤回/选线/补线在 `reference_step.c`。
   后续清理必须同时看这两个文件,不能只读 `circle.c`。

6. **控制层不要误读**:
   当前差速控制只吃 `guide_error` 和 `element_active`;
   不要从 `pure_angle`、`if_clean_pid`、`broadcast_flag` 推导控制行为。

---

## 15. 状态机时序速览

```text
NONE
  └─ check_circle: 弱双断点/内侧黑点入口连续2帧
      -> *_BEGIN
          ├─ BEGIN idle: begin_dist>6000 且无内侧丢线 -> reset NONE
          └─ 内侧丢线>=2 且 (lost_dist>2000 或 heading>=60°)
              -> *_IN
                  └─ heading>=60° 或 state_dist>2000
                      -> *_RUNNING
                          └─ 对侧出口角点<55+heading>=150°
                             或 heading>=200°
                             或 state_dist>16000
                              -> *_OUT
                                  └─ heading>=266°
                                     或 state_dist>4500
                                      -> *_END
                                          ├─ LEFT: heading>=355° 且 Lpt1<15 -> NONE
                                          ├─ RIGHT: Lpt0<15 -> NONE
                                          ├─ LEFT: state_dist>=7500 -> NONE
                                          └─ RIGHT: state_dist>=4000 -> NONE

任意圆环态: selected line 连续30帧为空 -> ATGCircleStall reset NONE
自然/撤回退出后: suppress reentry 150帧
```

---

## 16. 建议的第一步清理边界(零行为)

如果后续进入实现,第一步应只做语义清理,不改任何判断结果:

1. 改入口日志名:两处 `ATGCircleEntryBreakpoints` 同步改为更准确的
   `ATGCircleEntryInnerHit` 或类似名字。
2. 删除未引用 `CIRCLE_HEADING_FORCE_OUT_DEG10`。
3. 删除或注释标明 `circle_encoder` 为历史残留;若删除需同步 header/引用检索。
4. 将 `4500/7500/4000` 提成 enum 常量,数值不变。
5. 在 PRD 中明确:不改 `2660`,不改 `guide_error -> target_yaw -> yaw_cmd -> duty`,
   不改入口/IN/OUT/END 条件。

---
*基于真实读取:circle.c(679行)、reference_step.c(835行)、cross.c、shy_Image.c、road.c、runners.cpp、control.cpp。2026-06-25*
