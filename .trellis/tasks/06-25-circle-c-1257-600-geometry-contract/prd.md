# 重写 circle.c:1257→600行+固定geometry contract

## Goal

将圆环识别与状态机从当前 1257 行重写为 ~600 行。核心逻辑:16 函数骨架 + side helper 消除左右重复 + 4 事件日志 + 固定 geometry contract。不碰摄像头、IPM、控制器、补线采样等附属层。

## What I already know

### Geometry Contract(已定稿,于 `circle.h`)

```c
/*
 * Circle entry geometry contract:
 *
 * A: same-side near Lpt.
 *
 * inner-hit:
 *   proves inner circle boundary exists.
 *   left circle  scans raw x decreasing.
 *   right circle scans raw x increasing.
 *
 * B:
 *   confirms opposite arc / mouth boundary after skipping near edge.
 *   left circle  scans raw x increasing and takes max x.
 *   right circle scans raw x decreasing and takes min x.
 *
 * C:
 *   searched only after B reaches phase gate; used for real entry splice.
 */
```

### 核心函数骨架(16 个)

```c
// 坐标与 side
static int circle_raw_to_view_y(int raw_y);
static int circle_get_raw_point(int side, int id, point_t *p);
static int circle_get_A(int side, point_t *A);

// 状态管理
static void circle_reset_votes(void);
static void circle_reset_anchors(void);
static void circle_reset_to_none(const char *reason);
void update_circle_heading(float yaw_rate, int period_ms, int valid);

// 入口 A/B/C
static int circle_entry_basic(int side, const point_t *A);
static int circle_inner_hit(int side, const point_t *A);
static int circle_find_B(int side, const point_t *A, point_t *B);
static int circle_find_C(int side, const point_t *B, point_t *C);
static int circle_entry_candidate(int side);

// 状态机
void check_circle(void);
static void run_circle_begin(int side);
static void run_circle_running(int side);
static void run_circle_out(int side);
void run_circle(void);
```

### B 方向(已确认 = HEAD aa6d2e2 方向)

| | 左环 | 右环 |
|---|---|---|
| A | Lpt0, same-side | Lpt1, same-side |
| inner-hit | raw x 减小 | raw x 增大 |
| B | 跳过边缘后增大,取 max x | 跳过边缘后减小,取 min x |
| C | B 到达 phase gate 后才搜 | 镜像 |

### 状态机(已确认,不带 IN enum)

- NONE: 每帧搜 A + inner-hit + B, 连续 2 帧 → BEGIN
- BEGIN: track 外侧线, 继续搜 B; B 稳定 → ref=BEGIN_AB; 搜 C; C 稳定 → ref=IN_C; heading≥60° → RUNNING
- RUNNING: track 外侧线/固定线; 对侧出口 Lpt + heading gate → OUT; 或 heading≥200° → OUT
- OUT: track 出环侧线; heading≥266° + 对侧直线连续 → NONE; 或 heading≥330° → NONE

### 文件组织(Preference question)

分析建议了两种:

- **A. 单文件**: `circle.c` 按 `类型/常量→side helper→reset/heading→A/inner-hit→B→C→check_circle→run_circle_sub→run_circle→log` 顺序排。
- **B. 多文件**: `circle.c`(入口状态机) + `circle_entry.c`(A/inner-hit/B) + `circle_anchor.c`(A/B/C 工具) + `circle_state.c`(reset/abort/finish/heading) + `circle_log.c`(日志)。

### 保持不动的内容

`image_handle()`, `find_corners()`, `rpts0s/rpts1s`, `Lpt0/Lpt1`, `Cal_inv_rot_x/y`, `Cal_rot_x/y`, `Patching_Line`, `reference_step.c` 选线归一化, `control.cpp` 全部不碰。

## Assumptions

- 重写后 `circle.h` 公共接口不变(向上兼容 `reference_step.c`、`assistant.cpp`、`report.cpp`、`atg_reference_mainline.cpp`)
- GYRO 方向数据硬件层不变,积分使用方式不变
- 临时 `#define LEFT 1 / RIGHT 0` 或等同的 side 枚举

## Decision(ADR-lite)

**Context**: circle.c 重写涉及 16 个函数大量共享 static 全局变量(left/right entry votes,A/B/C 点,B/C streak 等),需选择文件结构。
**Decision**: 单文件,按 section 顺序排列。放弃多文件拆分方案。
**Consequences**: 省去跨文件 extern 声明开销,CMakeLists 只需改一个文件名,保持与原有 circle.h 接口兼容。后续行数超过 800 时可再议拆分。

## Requirements(locked)

- P0: 16 函数核心骨架(见上) + entry geometry contract + 4 事件日志
  (CircleEntryProbe / CircleEntryAB / CircleState / CircleABC)
- P1: side helper 消除左右重复 + `run_circle` 拆为 3 个子函数(begin/running/out)
- P2: 日志函数 defer(angle_variance 等非必需诊断推迟)
- 关键常量 headeroffset 在 circle.h 以 geometry contract block 形式写死

## Acceptance Criteria

- [ ] 重写后 `circle.c` 行数 ≤ 650(不含空行/注释 ~500)
- [ ] 函数数量 ~16 个,不膨胀
- [ ] A/inner-hit/B/C 扫描方向符合 geometry contract
- [ ] `run_circle` 左右环通过 side helper 消除明显重复
- [ ] 4 事件日志覆盖入口探测/AB/状态切换/ABC 全景
- [ ] 不做 C 搜索除非 B 达到 phase gate(防过早补线)
- [ ] WSL host build 通过
- [ ] replay 同一年 drive 日志输出无退化

## Out of Scope

- 删除现有 `circle.c` 前需保留副本用于行为对比(不删除旧文件)
- `circle_cal_log_enabled()` 等 env gate 沿用现有设施,不新建框架
- 摄像头/IPM/控制器/补线采样(`Patching_Line`)不改

## Technical Notes

- 构建: WSL host build via `./test.sh --host`
- 重写策略: 新建 `circle_v2.c`, 逐步实现在侧,旧 `circle.c` 不动直到新 file 通过 replay 验证
- spec 引用: `.trellis/spec/quality/refactoring-and-diagnostic-discipline.md`(seed 同源纪律)
- geometry contract 须写在 `circle.h` 注释里,作为唯一权威来源
