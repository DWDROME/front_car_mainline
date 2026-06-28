# Refactoring Discipline And Diagnostic Source Consistency

> 行为保持重构的边界纪律与调试输出同源要求。

---

## Overview

本文件记录从"拆 runners + seed 去重 + 日志门控"任务中学到的三条教训:

1. **Commit 边界纪律** —— 重构提交不得混合算法行为改动。
2. **调试显示同源** —— 上位机显示坐标必须从算法模块导出,禁止独立推算。
3. **诊断提取+门控模式** —— 每帧诊断应提取为独立函数再套环境变量门控,而非散落 `if-env` 在各调用点。
4. **视觉主链与诊断边界分开** —— runners 可直接跑
   `vision_step()`；report/replay/assistant 只读 `vision_view` 的 snapshot/view。

---

## 1. Convention: Pure Refactoring Commits Must Not Mix Algorithm Changes

### What

一次 commit 应当只做一类改动:

- **重构**(纯搬代码、改文件名、调 include、加日志门控) —— 行为不变,可 replay 逐字节验证。
- **算法行为改动**(改阈值、调搜索方向、变状态机) —— 行为变,需上车/analyze 验证。

两者不得混入同一个 commit。

### Why

混合后:

- `git diff` 无法一次性判定"哪些行是行为保持的、哪些行是行为变了"。
- Trellis check 会标记 out-of-scope 改动,评审和回归困难。
- 如果行为改动有问题,无法单独 revert 重构部分而不引入冲突。

### Wrong

```c
// 同一个 commit 同时做了:
// 1) 拆 runners.cpp (行为保持重构)
// 2) 改 find_circle_B_vertical 扫描方向 (算法改动)
// git log 看不出来项 2 的存在,check 时才发现。
```

### Correct

```git
commit A: refactor(runners): split report/control_input_builder/...
commit B: fix(circle): right B-arc scanning skips edge-line false target
```

项 A 验证:replay 同一份 drive 日志 → 输出逐字节一致。
项 B 验证:上车跑圆环 → B 找到正确弧面。

### Enforcement

- 在 `git commit` 之前做 `git diff --stat`,确认每个改动的文件只属于本 commit 的类别。
- 如果同一文件既有重构又有行为改,要么拆 commit,要么拆文件(例如先 refactor 提交,再 behavior 提交)。
- Trellis check 须检查 commit 的 diff 是否混合不可验证类别。

---

## 2. Convention: Debug Display Must Reuse Algorithm Seed Source

### What

上位机(assistant)的调试显示坐标、种子点、扫描线起始位置,必须从算法模块导出,不得在 `assistant.cpp` 中独立计算。

### Why

`assistant.cpp` 是纯显示旁路。如果它在助理层维护一份不同的种子算法规约(z.B. `-10` vs algorithm 的 `+2`),就产生了第二真相源。后果:

- 上位机显示的扫描线和算法实际扫描线不一致,调试人员被误导。
- 改算法时如果只改 `circle.c`、忘了改 `assistant.cpp`,偏差逐渐积累。
- 重现问题需要同时检查两份公式,增加了调试成本。

### Example from this project

旧版 `circle.c` 的入口种子公式:

```c
*seed_raw_x = Cal_inv_rot_x(rpts0s[id][0], rpts0s[id][1]) + 2.0f;
```

旧版 `assistant.cpp` 的入口种子公式:

```cpp
const float raw_x = Cal_inv_rot_x(rpts0s[id][0], rpts0s[id][1]) - 10.0F;
```

12 像素偏差导致上位机显示的入口扫描线与实际算法扫描线错位。修复方法:assistant 改为调用 `circle_entry_inner_seed()`,公式只保存在 `circle.c` 一处。

### Pattern

```c
// circle.h —— 算法模块导出种子函数
int circle_entry_inner_seed(int left_side, int *seed_x, int *seed_y,
                            float *seed_raw_x, float *seed_raw_y);
```

```cpp
// assistant.cpp —— 显示层复用,不重新推导
int circle_entry_scan_seed_raw(int *seed_x, int *seed_y)
{
    // ... 侧判定(显示层负责判断当前扫描哪一侧) ...
    float seed_raw_x = 0.0F, seed_raw_y = 0.0F;
    return circle_entry_inner_seed(left_side, seed_x, seed_y,
                                   &seed_raw_x, &seed_raw_y);
}
```

### Enforcement

- assistant 中任何直接计算 raw/inv_rot 坐标的代码,如使用 `Cal_inv_rot_x/y` 或在坐标系偏移前写死 +/- 常量,须有明确理由:是该种子属于显示层独有的语义(例如十字标记偏移),否则必须从算法模块复用。
- 新增调试显示点时,优先检查算法模块是否已有同义函数;如果有,直接调用;没有则在算法模块新增导出。

---

## 3. Pattern: Extract And Gate Per-Frame Diagnostics

### What

每个每帧无条件打印的诊断输出,应当是:

1. **独立的静态函数**(便于加门控);
2. **被环境变量门控包裹**(调用点 insert gate check,非散落 `if-env`)。

### Why

旧做法:诊断代码嵌入在算法逻辑中间,门控散落在三四处调用点:

```c
// 做法 A(散落):每一处调用前都包 if-env
if(circle_cal_log_enabled()) {
    printf("ATGCircleSomeDiag: ...");
}
...

// 另一处
if(circle_cal_log_enabled()) {
    printf("ATGCircleSomeDiag2: ...");
}
```

问题:
- 如果新增一处调用忘了包 `if-env`,诊断就变成无条件打印。
- 无法在调用函数入口统一 gate → 被包的点不一定覆盖所有路径。
- 重构改调用点时容易遗漏 `if-env`。

### Correct: Extract + Gate At Function Level

```c
// 诊断函数本身:提取为独立函数,在函数入口统一 gate
static void print_circle_something_diag(...)
{
    if(circle_type == CIRCLE_NONE) return;   // 非活跃态→跳过(保护性)
    if(!circle_cal_log_enabled()) return;    // 门控:默认静默
    printf("ATGCircleSomeDiag: ...");
}
```

这样:
- 只要函数被调用就自动 gate,新增调用点不会漏。
- 注释清楚:没有门控的话诊断就是每帧打印,在实车运行时有害。
- 便于未来归入多域日志框架(如 `LOG_DIAG(CIRCLE, ...)`)。

### Application

此 repo 已有 `circle_cal_log_enabled()` 环境变量门控(读 `FRONT_CAR_CIRCLE_CAL_LOG`)。它的工作模式:

| 环境变量 | 效果 |
|----------|------|
| 不设置 或 `0` / `false` | 圆环诊断默认静默 |
| `1` / `true` | 圆环诊断每帧打印(调试时用) |

适用该模式的诊断函数示例:

- `print_circle_abc_diag()` —— 圆环 A/B/C 点全景诊断(已 gate)。
- `print_circle_transition()` —— 圆环状态切换(已 gate)。
- `print_left_begin_diag()` / `print_right_begin_diag()` —— 左/右 BEGIN 状态诊断(已 gate)。
- `circle_entry_find_inner_hit_on_seed_line()` 中的 inner-hit 结果(已 gate)。

如果未来需要其他域的类似控制(十字、普通线、控制),按照相同的模式即可:
不需要全量框架,只需要在目标诊断前加一个 `if(!domain_enabled()) return;`。

### Convention Summary

- 每个新加的每帧诊断(非 ERROR/WARN)必须是独立函数。
- 该函数在打印前必须检查对应域的环境变量门控。
- 禁止在算法逻辑中间散落 `if(env_gate) printf(...)`。
- 现有诊断:如果发现某处散落 `if-env` + `printf`,提取为独立函数再加统一 gate。

---

## 4. Convention: Vision Step Is App Mainline, Diagnostics Use Vision View

### What

当前主链按比赛代码心智模型保持扁平:

```text
main -> runners -> vision_step -> control -> drive/report
```

`code/app/vision_step.c` 是当前比赛视觉一帧主流程，不再放在 `code/port/`。
`code/app/runners.cpp` 直接调用 `vision_step()`，再直接读取 ATG 当前帧全局变量
写入 `runtime_t::vision` 和控制输入。允许 app 主链 include `vision_step.h`、
`headfile.h` 以及必要的元素头；比赛代码优先直白，不为每个全局变量增加
`vision_*` 查询函数。

`code/app/vision_step.h` 只保留动作入口和少量直接全局出口:

```c
void vision_reset(void);
int vision_step(uint8_t gray[120][160], int64_t encoder_total);
void vision_set_car_x(float x);
void vision_update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid);
void raw_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y);

extern const char *src;
extern int src_id;
extern int64_t begin_dist;
extern int64_t last_begin_dist;
extern float car_raw_x;
```

不要新增这类 getter/query adapter:

```c
vision_selected_line();
vision_ipm_cx();
vision_pixel_per_meter();
vision_element_active();
vision_circle_begin_dist();
line_src();
line_src_id();
```

外部需要 `rptsn`、`Guide`、`cx/cy`、`pixel_per_meter`、`circle_type`、
`cross_type`、`road_type` 等当前帧状态时，直接 include 已有 ATG 头并读全局。

`code/report` 里的 report、replay、assistant 仍必须通过
`report/vision_view.hpp` 读取诊断快照、点列和坐标辅助，不能各自重新解释 ATG
全局变量。

允许的诊断边界 API:

```cpp
vision_snapshot_t vision_snapshot();
vision_line_view_t vision_line(vision_line_id id);
vision_raw_view_t vision_raw_line(vision_raw_id id);
void vision_raw_to_ipm(float raw_x, float raw_y, float *ipm_x, float *ipm_y);
void vision_ipm_to_raw(float ipm_x, float ipm_y, float *raw_x, float *raw_y);
int vision_circle_entry_seed(int *seed_x, int *seed_y);
```

#### Vision Adapter Boundary Contract

1. Scope / Trigger: applies whenever `code/report` needs ATG-derived diagnostics,
   line views, raw/IPM conversion, or element state from `report/vision_view.hpp`.
   The active runtime chain is allowed to use `vision_step()` directly.
2. Signatures: `vision_snapshot()` is the only snapshot出口; point lists use
   `vision_line(vision_line_id)` and `vision_raw_line(vision_raw_id)`;
   coordinate helpers use `vision_raw_to_ipm()` / `vision_ipm_to_raw()`;
   entry seed display uses `vision_circle_entry_seed()`.
3. Contracts: report code may keep output labels such as `atg_*` for report
   compatibility, but C++ API names and public types at this boundary use
   `vision_*`; single-value diagnostics such as type names, selected-line
   source, begin distance, and vehicle raw ref live in `vision_snapshot_t`
   fields instead of public getters.
4. Validation & Error Matrix: missing/null point views return `{nullptr, 0}`;
   invalid seed output pointers return `0`; unsupported enum values map to
   empty views or `*_UNKNOWN` type-name fields, not app-side fallback formulas.
5. Good/Base/Bad Cases: good = app mainline directly reads current-frame ATG
   globals after `vision_step()` and report/replay/assistant read one
   `vision_snapshot_t`; bad = adding public single-value `vision_*` getters or
   report/assistant recreating `Cal_inv_rot_*`/line-source/type-name logic.
6. Tests Required: after boundary changes run `git diff --check`,
   `bash test.sh --host`, `bash test.sh`, and `rg` checks proving old public
   ATG-named legacy snapshot/view/IPM helper APIs are absent from report code
   and the public header.
7. Wrong vs Correct:

```cpp
// Wrong: app owns a second public ATG getter path.
const char *src = vision_line_src();

// Correct in app mainline: read the current-frame global directly.
const char *name = src;

// Correct in report/assistant: use the diagnostic snapshot.
const vision_snapshot_t vision = vision_snapshot();
const char *report_name = vision.line_src_name;
```

`headfile.h` 和 ATG 全局变量允许出现在 `code/app/runners.cpp`、
`code/app/control_input_builder.cpp`、`code/app/vision_step.c` 以及
`code/report/vision_view.cpp`。report/assistant/replay 的其它文件不直接 include
这些底层头。

### Why

诊断层各自直读 ATG 全局会制造三类问题:

- report/assistant 变成第二个 ATG port,后续移动视觉核心时调用面爆炸。
- report/assistant 容易保存自己的坐标公式或枚举解释,形成第二真相源。
- 诊断字段散落在多个文件里,行为保持重构时难以确认输出是否同源。

app 主链不同：它是实时边界，读当前帧全局变量比再包一层查询接口更清楚。

### Wrong

```cpp
#include "headfile.h"
#include "shy_Image.h"

printf("atg_rpts0s_num=%d\n", rpts0s_num);
```

### Correct

```cpp
#include "report/vision_view.hpp"

const vision_snapshot_t atg = vision_snapshot();
printf("atg_rpts0s_num=%d\n", atg.rpts0s_num);
```

### Enforcement

- 改 app 或 report 诊断前先搜索:
  ```bash
  rg -n "#include \"(headfile|common|motor|shy_Image)\\.h\"|#include <common\\.h>" code/app code/report
  ```
- 预期 `code/app/runners.cpp`、`code/app/control_input_builder.cpp` 和
  `code/app/vision_step.c` 可以直接使用底层视觉头；`code/report` 只有
  `vision_view.cpp` 需要底层视觉头。
- assistant 新增显示点时,优先扩展 adapter view/snapshot;如果点的公式属于算法语义,在算法模块导出,再由 adapter 转发。

---

## 5. Convention: `code/` Is Source Tree, Not Build Tree

### 1. Scope / Trigger

适用于修改 `test.sh`、`code/test.sh`、`tools/*.sh`、CMake 配置或任何会创建
CMake build tree 的脚本。

### 2. Signatures

项目保留两个测试入口:

```bash
bash test.sh [--host|--reconfigure|--clean|--upload]
bash code/test.sh [--host|--reconfigure|--clean|--upload]
```

`test.sh` 是顶层短入口,转发到 `code/test.sh`。`code/test.sh` 的源码根是
`code/`,但构建输出目录是仓库根目录:

```text
build/       # cross build
build-host/  # host build
```

### 3. Contracts

- `code/` 只放源码、测试源码、CMake 输入和少量源码相关脚本。
- 不在 `code/` 下生成或长期保留 `build/`、`build-host/`、临时备份入口或
  CMake cache。
- `code/test.sh --reconfigure` 必须清理当前 build dir 里的
  `CMakeCache.txt`、`CMakeFiles`、`Makefile`、`cmake_install.cmake`,再重新
  `cmake`。否则从旧目录迁移来的 build tree 会继续记住旧路径。
- `tools/*.sh` 如果需要 host 二进制,统一从仓库根目录 `build-host/` 读取。

### 4. Validation & Error Matrix

| Condition | Expected |
| --- | --- |
| `code/build/` 或 `code/build-host/` 存在 | 迁出或删除生成产物,不要提交 |
| 脚本引用 `code/build-host` | 改为 `${ROOT}/build-host` |
| 移动过 build tree 后运行 `--reconfigure` | 先清 CMake cache,再配置 |
| `bash test.sh --host` | 在 `build-host/` 构建并运行 host tests |
| `bash test.sh` | 在 `build/` 构建交叉目标 |

### 5. Good/Base/Bad Cases

- Good: `code/test.sh` 使用 `CODE_ROOT` 作为 CMake source dir,使用 repo
  `ROOT` 下的 `build/` 和 `build-host/` 作为 binary dir。
- Base: 顶层 `test.sh` 只转发参数,不维护第二套构建逻辑。
- Bad: `BUILD="${ROOT}/code/build-host"` 或把 `main.old.cpp` 这类旧入口备份
  留在 `code/app/`。

### 6. Tests Required

修改构建入口或相关工具脚本后至少运行:

```bash
find code -maxdepth 2 -type d \( -name build -o -name build-host \) -print
rg -n "code/build|code/build-host|BUILD=\"\$\{ROOT\}/code/build" . --glob '!build/**' --glob '!build-host/**'
bash -n test.sh code/test.sh tools/*.sh
bash test.sh --host
```

如果改动影响 cross build 路径,还要运行:

```bash
bash test.sh --reconfigure
```

### 7. Wrong vs Correct

Wrong:

```bash
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_HOST="${ROOT}/build-host"   # 在 code/test.sh 里等价于 code/build-host
cmake "${ROOT}"
```

Correct:

```bash
CODE_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "${CODE_ROOT}/.." && pwd)"
BUILD_HOST="${ROOT}/build-host"
cmake "${CODE_ROOT}"
```
