# Goal

对 `front_car_mainline` 做第一刀低风险复杂度清理：删除无效构建/配置/死路径，让主程序只保留真实实车主链需要的源码和配置入口。

本计划只覆盖第一刀，不执行第二刀接口降噪和第三刀重复算法规则清理。

# Architecture

当前主程序结构保持不变：

```text
code/app/main.cpp
-> tracking_process_frame()
-> control solve_runtime / solve_runtime_with_feedback
-> drive_output_apply()
```

本计划不新增 manager、adapter、wrapper、strategy、registry，不新增配置源，不新增 fallback，不移动主链算法文件。

# Tech Stack

- CMake: `"code/CMakeLists.txt"`
- C++17/C99
- OpenCV linked by existing `find_package(OpenCV REQUIRED)`
- 逐飞 LS2K0300 外部库：`"../../../libraries/zf_*"`
- 验证入口：`bash "code/test.sh" --host`

# Baseline/Authority Refs

- `"AGENTS.md"`：简单实车主线、禁止隐藏 fallback、禁止工程化抽象、修改后自查。
- `".agentdocs/index.md"`：当前主线事实和禁止恢复 shadow pipeline / old-new dual routes。
- `"docs/aegis/baseline/2026-05-31-initial-baseline.md"`：Aegis 当前基线。
- 当前文件事实：
  - `".gitignore"` 当前只有 `.ace-tool/`。
  - `"code/CMakeLists.txt"` 当前把 `"drivers/motor_pulse.cpp"` 编进 `front_car_mainline` 主目标。
  - `"code/tools/key_supervisor.cpp"` 当前在 `start_mainline()` 里拼接无效控制参数环境变量。
  - `"code/tracking/boundary.hpp"` 和 `"code/tracking/boundary.cpp"` 当前保留 `boundary_is_lost()`。
  - `"code/tracking/mainline.cpp"` 当前保留 `TRACK_TYPE_DUAL` 求中线分支，但 `pick_track_type()` 不主动返回 `TRACK_TYPE_DUAL`。

# Compatibility Boundary

必须保持：

- 不改控车主链：`guide_error -> target_yaw -> duty -> drive_output_apply`。
- 不改 tracking 算法阈值、公式、状态跳转条件。
- 不改 `/root/front_car_mainline.yaml` 作为控制参数覆盖入口。
- 不新增 env 控制参数读取。
- 不删除 `"drivers/motor_pulse.cpp"` 文件本身，只从主程序目标摘掉。
- 不删除 `"imgproc.cpp"` 里的 `track_dualline()`，只摘掉当前普通主链中的不可达 DUAL 分支。
- `key_supervisor` 仍保留 K1 启动、K2 停车、K3 高清拍照。

需要明确的行为边界：

- 删除 `TRACK_TYPE_DUAL` 主链分支属于删除死执行路径。当前 `pick_track_type()` 不返回 DUAL，因此按现状不改变运行行为；但如果未来有人手动把 `track_type` 改成 DUAL，这条路径会消失。执行前需要用户确认这一点可以接受。

# Verification

每个任务局部检查后，最终必须跑：

```bash
bash "code/test.sh" --host
```

期望输出包含：

```text
[100%] Built target front_car_mainline
```

如 host 环境缺 OpenCV CMake 包导致 `find_package(OpenCV REQUIRED)` 失败，不能声称编译通过；需要记录为环境缺失，不把它当源码错误。

# Plan Basis

事实：

- `.gitignore` 缺少 `build/`、`build-host/`、二进制产物忽略规则。
- `front_car_mainline` 主目标编入了 `drivers/motor_pulse.cpp`。
- `key_supervisor.cpp` 拼接了 `target_rps`、`outer_kp` 等控制参数环境变量，但当前配置实际由 `config.hpp` 默认值、`/root/front_car_mainline.yaml`、`FRONT_CAR_CONFIG` 控制。
- `boundary_is_lost()` 有声明和定义，但当前主链没有接入。
- `TRACK_TYPE_DUAL` 分支存在于 `tracking_process_frame()`，但普通选边函数当前不返回 DUAL。

假设：

- `drivers/motor_pulse.cpp` 是诊断/开环测试代码，不应随主程序常驻初始化硬件对象。
- 当前队伍更重视现场可读和单一配置入口，而不是保留多余备用路径。

未知：

- 是否已有队友依赖手动修改 `track_type` 进入 DUAL 分支做实验。
- 是否希望后续把 `motor_pulse` 单独做成诊断 target。第一刀不做。

Ripple Signal Triage：

- CMake 改动影响 host/cross build 和上传包内容。
- `key_supervisor` 改动影响 K1 启动主程序时的环境变量。
- `boundary_is_lost()` 删除影响任何潜在未提交调用；执行前只能用已知文件直接核对，ACE 当前不稳定时不做全库搜索假确认。
- `TRACK_TYPE_DUAL` 主链摘除影响未来实验路径，需在计划中列为 retirement 项。

# Files

修改：

- `".gitignore"`
- `"code/CMakeLists.txt"`
- `"code/tools/key_supervisor.cpp"`
- `"code/tracking/boundary.hpp"`
- `"code/tracking/boundary.cpp"`
- `"code/tracking/mainline.cpp"`

不修改：

- `"drivers/motor_pulse.cpp"` 和 `"drivers/motor_pulse.hpp"` 文件本体。
- `"code/tracking/imgproc.cpp"` 的 `track_dualline()`。
- `"code/core/config.cpp"`，不新增 env 参数读取。
- 外部逐飞库。
- `front_car_control_calib`。

# Plan Pressure Test

- Owner / contract / retirement: 这是一组删除无效入口和摘除死路径的治理清理，owner 分别是 `.gitignore`、CMake、supervisor、tracking 边界和 mainline。
- Verification scope: 本地 host 编译足够证明语法/链接；实车行为因不改算法，上传不是此计划必须 gate。
- Task executability: 每项都是小文件小 diff，可单独执行和回退。
- Pressure result: proceed，但 `TRACK_TYPE_DUAL` 主链摘除执行前需要再次确认。

# Plan-Time Complexity Check

- Target files: `.gitignore`, `code/CMakeLists.txt`, `code/tools/key_supervisor.cpp`, `code/tracking/boundary.hpp`, `code/tracking/boundary.cpp`, `code/tracking/mainline.cpp`
- Existing size / shape signals: `key_supervisor.cpp` 是独立工具入口；`mainline.cpp` 是主链；`boundary.cpp` 是边界解释层。
- Owner fit: 每个修改都落在原 owner 文件内，不新增文件。
- Add-in-place risk: 低。主要风险是误删仍被使用的符号或删掉未来实验路径。
- Better file boundary: 不需要新文件；不做单独 `motor_pulse_tool`，因为第一刀只摘主目标。
- Recommendation: edit-in-place。

# Tasks

## Task 1: 忽略构建产物

Files:

- Modify `".gitignore"`

Why:

- 避免 `build/`、`build-host/`、二进制和中间产物进入仓库，减少 CMake 旧路径污染。

Impact/Compatibility:

- 不影响运行行为。
- 不删除任何现有构建目录，只改变 git 忽略规则。

Repair Track:

- Root cause: `.gitignore` 只忽略 `.ace-tool/`，没有覆盖本项目常见构建输出。
- Canonical owner: `".gitignore"`
- Stable repair: 添加构建目录和产物模式。
- Compat boundary: 不加过宽规则，不忽略源码、yaml、docs。
- Verification: grep 检查规则存在。

Retirement Track:

- Old owner/fallback: 无。
- Active status: 规则添加后长期保留。
- Deletion trigger: 如果项目改成单独 out-of-tree build 规范，可再调整。

Steps:

- [ ] Write test: 运行以下命令确认当前缺少规则。

```bash
grep -qx 'build/' ".gitignore"; test $? -ne 0
grep -qx 'build-host/' ".gitignore"; test $? -ne 0
grep -qx 'front_car_mainline' ".gitignore"; test $? -ne 0
```

- [ ] Verify RED: 上面三条命令应返回 0，表示这些规则当前缺失。
- [ ] Minimal code: 把 `".gitignore"` 改成：

```gitignore
.ace-tool/
build/
build-host/
*.o
*.d
*.a
*.so
*.elf
front_car_mainline
key_supervisor
```

- [ ] Verify GREEN:

```bash
grep -qx 'build/' ".gitignore"
grep -qx 'build-host/' ".gitignore"
grep -qx 'front_car_mainline' ".gitignore"
```

- [ ] Commit: 不自动提交。若用户明确确认提交，再执行：

```bash
git add ".gitignore"
git commit -m "chore: ignore front car build outputs"
```

## Task 2: 从主程序目标摘掉 motor_pulse 诊断代码

Files:

- Modify `"code/CMakeLists.txt"`

Why:

- `drivers/motor_pulse.cpp` 是诊断/开环测试代码，不应进入 `front_car_mainline` 实车主程序目标。
- 避免主程序里常驻第二套电机/PWM/编码器静态对象。

Impact/Compatibility:

- `front_car_mainline` 不再编译 `drivers/motor_pulse.cpp`。
- 不删除文件本体，不影响以后单独做诊断 target。
- 如果有人期望主程序内调用 `run_motor_pulse()`，编译会暴露缺符号；当前主链不应依赖它。

Repair Track:

- Root cause: 诊断源码混入主目标。
- Canonical owner: `"code/CMakeLists.txt"` 的 `DIR_SRCS`。
- Stable repair: 从 `DIR_SRCS` 删除 `drivers/motor_pulse.cpp`。
- Compat boundary: 不新增 `motor_pulse_tool`，不改驱动接口。
- Verification: CMake/host build。

Retirement Track:

- Old owner/fallback: `drivers/motor_pulse.cpp` 保留为未编入源码。
- Active status: 暂时保留文件，等待是否要单独诊断 target。
- Deletion trigger: 用户确认不再需要开环脉冲测试后，另开删除任务。

Steps:

- [ ] Write test:

```bash
grep -n 'drivers/motor_pulse.cpp' "code/CMakeLists.txt"
```

- [ ] Verify RED: 命令应输出 `drivers/motor_pulse.cpp` 所在行。
- [ ] Minimal code: 从 `"code/CMakeLists.txt"` 的 `set(DIR_SRCS ...)` 中删除这一行：

```cmake
    drivers/motor_pulse.cpp
```

- [ ] Verify GREEN:

```bash
! grep -n 'drivers/motor_pulse.cpp' "code/CMakeLists.txt"
bash "code/test.sh" --host
```

- [ ] Commit: 不自动提交。若用户明确确认提交，再执行：

```bash
git add "code/CMakeLists.txt"
git commit -m "build: exclude motor pulse diagnostic from mainline"
```

## Task 3: 删除 key_supervisor 无效控制参数环境变量

Files:

- Modify `"code/tools/key_supervisor.cpp"`

Why:

- `start_mainline()` 当前拼接的 `target_rps`、`outer_kp` 等控制参数环境变量不会被 `core/config.cpp` 读取。
- 保持控制参数唯一入口：默认值 + `/root/front_car_mainline.yaml` + `FRONT_CAR_CONFIG`。

Impact/Compatibility:

- K1 仍会启动 `front_car_mainline`。
- assistant、FPS、打印、drive enable 等运行环境变量保留。
- 不新增 env 控制参数读取。

Repair Track:

- Root cause: supervisor 里存在伪配置路径。
- Canonical owner: `"code/tools/key_supervisor.cpp"` 的 `start_mainline()`。
- Stable repair: 删除无效控制参数 env。
- Compat boundary: 不改 YAML 解析，不改 K1/K2/K3 行为。
- Verification: grep 检查变量不存在，host build。

Retirement Track:

- Old owner/fallback: 无效 env 参数直接删除，不保留注释。
- Active status: 控制参数统一交给 yaml。
- Deletion trigger: 已在本任务删除。

Steps:

- [ ] Write test:

```bash
grep -nE 'target_rps|outer_kp|outer_kd|straight_error_threshold|straight_turn_scale|max_target_yaw_rate|yaw_kp' "code/tools/key_supervisor.cpp"
```

- [ ] Verify RED: 命令应输出 `start_mainline()` 中的无效 env 参数。
- [ ] Minimal code: 从 `std::snprintf()` 的命令字符串中删除以下片段：

```cpp
                  "target_rps=6 "
                  "outer_kp=0.010 "
                  "outer_kd=0 "
                  "straight_error_threshold=12 "
                  "straight_turn_scale=0.6 "
                  "max_target_yaw_rate=0.35 "
                  "yaw_kp=8 "
```

保留：

```cpp
                  "SMARTCAR_ASSISTANT=1 "
                  "SMARTCAR_ASSISTANT_IP=192.168.0.101 "
                  "SMARTCAR_ASSISTANT_PORT=8086 "
                  "SMARTCAR_ASSISTANT_CONNECT_MS=30 "
                  "SMARTCAR_ASSISTANT_RECONNECT_DIV=30 "
                  "SMARTCAR_ASSISTANT_DIV=12 "
                  "FRONT_CAR_DISPLAY=0 "
                  "FRONT_CAR_PROCESS_FPS=120 "
                  "FRONT_CAR_PRINT_DIV=30 "
                  "FRONT_CAR_ENABLE_DRIVE=1 "
```

- [ ] Verify GREEN:

```bash
! grep -nE 'target_rps|outer_kp|outer_kd|straight_error_threshold|straight_turn_scale|max_target_yaw_rate|yaw_kp' "code/tools/key_supervisor.cpp"
bash "code/test.sh" --host
```

- [ ] Commit: 不自动提交。若用户明确确认提交，再执行：

```bash
git add "code/tools/key_supervisor.cpp"
git commit -m "chore: remove unused supervisor control env"
```

## Task 4: 删除未接入的 boundary_is_lost()

Files:

- Modify `"code/tracking/boundary.hpp"`
- Modify `"code/tracking/boundary.cpp"`

Why:

- `boundary_is_lost()` 当前没有接入主链，保留会制造“丢边策略已经存在”的误导。

Impact/Compatibility:

- 删除声明和定义。
- 如果存在未发现调用，编译会失败并暴露真实依赖。
- 不新增替代 fallback。

Repair Track:

- Root cause: 未来可能使用的判断提前占位。
- Canonical owner: boundary 接口文件和实现文件。
- Stable repair: 删除未接入函数。
- Compat boundary: 不改 `boundary_is_straight()` 和角点逻辑。
- Verification: grep 检查符号不存在，host build。

Retirement Track:

- Old owner/fallback: `boundary_is_lost()` 删除。
- Active status: 不保留。
- Deletion trigger: 本任务完成即退休。

Steps:

- [ ] Write test:

```bash
grep -n 'boundary_is_lost' "code/tracking/boundary.hpp" "code/tracking/boundary.cpp"
```

- [ ] Verify RED: 命令应输出声明和定义。
- [ ] Minimal code: 删除 `"code/tracking/boundary.hpp"` 中：

```cpp
int boundary_is_lost(const boundary_t *bd);
```

删除 `"code/tracking/boundary.cpp"` 中整个函数：

```cpp
int boundary_is_lost(const boundary_t *bd)
{
    if(bd == nullptr)
    {
        return 1;
    }
    if(bd->now_step < 3)
    {
        return 1;
    }

    const point_t p0 = bd->now_pts[0];
    const point_t p1 = bd->now_pts[bd->now_step - 1];
    const int dx = std::abs(p1.x - p0.x);
    const int dy = std::abs(p1.y - p0.y);
    const int len = dx + dy;
    return len < 5;
}
```

- [ ] Verify GREEN:

```bash
! grep -n 'boundary_is_lost' "code/tracking/boundary.hpp" "code/tracking/boundary.cpp"
bash "code/test.sh" --host
```

- [ ] Commit: 不自动提交。若用户明确确认提交，再执行：

```bash
git add "code/tracking/boundary.hpp" "code/tracking/boundary.cpp"
git commit -m "chore: remove unused boundary lost helper"
```

## Task 5: 从当前普通主链摘掉 TRACK_TYPE_DUAL 分支

Files:

- Modify `"code/tracking/mainline.cpp"`

Why:

- 当前 `pick_track_type()` 在双边足够时沿用上一帧单边，不主动返回 `TRACK_TYPE_DUAL`。
- `TRACK_TYPE_DUAL` 求解分支挂在主链中，但当前普通主链不可达，属于半废弃路径。

Impact/Compatibility:

- 按当前代码路径，不改变普通巡线行为。
- 不删除 `TRACK_TYPE_DUAL` 枚举，不删除 `track_dualline()`，避免扩大影响。
- 如果未来需要双边中线，应另开任务让 `pick_track_type()` 明确返回 DUAL 并实车验证。

Repair Track:

- Root cause: 旧/实验路径挂在主链里但不由选边策略进入。
- Canonical owner: `"code/tracking/mainline.cpp"` 的中线求解分支。
- Stable repair: 删除 `if(track_type == TRACK_TYPE_DUAL)` 分支，让主链只处理当前实际 LEFT/RIGHT。
- Compat boundary: 保留 `track_dualline()` 作为未接入实验函数，不动 `imgproc.cpp`。
- Verification: host build；运行时观察 `track` 仍为 LEFT/RIGHT/NONE。

Retirement Track:

- Old owner/fallback: 主链 DUAL 分支退休。
- Active status: `track_dualline()` 暂时保留，主链不接。
- Deletion trigger: 后续如果确认不再实验双边中线，可单独删除 `track_dualline()` 和 `TRACK_TYPE_DUAL` 枚举。

Steps:

- [ ] Write test:

```bash
grep -n 'track_type == TRACK_TYPE_DUAL' "code/tracking/mainline.cpp"
```

- [ ] Verify RED: 命令应输出当前 DUAL 分支。
- [ ] Minimal code: 删除 `"code/tracking/mainline.cpp"` 中：

```cpp
    if(track_type == TRACK_TYPE_DUAL)
    {
        // 普通主线目前很少走到这里；保留双边中点算法，不在本刀改行为。
        mid_ok = track_dualline(rpts0s,
                                rpts0s_num,
                                rpts1s,
                                rpts1s_num,
                                ROAD_HALF_WIDTH,
                                ref.x,
                                ref.y,
                                &rt->track.mid);
    }
    else if(track_type == TRACK_TYPE_LEFT)
```

改成：

```cpp
    if(track_type == TRACK_TYPE_LEFT)
```

保留后面的 `TRACK_TYPE_LEFT` 和 `TRACK_TYPE_RIGHT` 分支。

- [ ] Verify GREEN:

```bash
! grep -n 'track_type == TRACK_TYPE_DUAL' "code/tracking/mainline.cpp"
bash "code/test.sh" --host
```

- [ ] Commit: 不自动提交。若用户明确确认提交，再执行：

```bash
git add "code/tracking/mainline.cpp"
git commit -m "chore: remove unreachable dual midline branch"
```

# Risks

- `git status` 在当前挂载盘曾卡住；执行时不要依赖长时间 `git status` 作为唯一检查，可以用定向文件读取和 host build。
- ACE 当前可能超时或 502。若需要全库调用确认且 ACE 不可用，必须报告 `ACE unavailable, search aborted`，不能用 shell 搜索伪装代码检索。
- `TRACK_TYPE_DUAL` 主链摘除虽然按当前路径不可达，但属于删除执行路径；需要用户执行前确认。
- `key_supervisor` 改动会影响板端 K1 启动命令。删除的是无效控制参数 env，不应影响 yaml 控制参数。
- `motor_pulse.cpp` 从主目标移除后，如果它曾意外提供某个链接符号，host build 会暴露。

# Retirement

第一刀完成后应退休：

- 构建产物进入仓库的风险。
- `motor_pulse.cpp` 作为主程序源码的混入状态。
- `key_supervisor` 中无效控制参数 env。
- `boundary_is_lost()` 未接入占位函数。
- `tracking_process_frame()` 中普通主线不可达的 DUAL 求解分支。

第一刀不退休：

- `drivers/motor_pulse.cpp/.hpp` 文件本体。
- `TRACK_TYPE_DUAL` 枚举。
- `track_dualline()` 实现。
- `cross.cpp` 重复手写投影。
- `corner_pair_ok()` 的 `const_cast`。
- `boundary_is_straight()` 未用参数。

# Self-Review

- Spec coverage: 覆盖用户贴出的第一刀 5 项；第二刀/第三刀只列入后续，不混入执行。
- Placeholder scan: 无 TBD/TODO。
- Type consistency: 未新增签名；删除 `boundary_is_lost()` 时声明/定义同步删除。
- Compatibility: 不改控制链、不新增配置源、不新增 fallback、不删除诊断文件本体。
- Minimality: 每项在原 owner 文件内编辑，不新增文件，不新增构建目标。
- Verification: 每项有 grep 局部检查，最终有 `bash "code/test.sh" --host`。
- Dual-track: 删除项均写明 retirement；保留项写明后续删除触发条件。
