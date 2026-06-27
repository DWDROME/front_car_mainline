# reference_step 命名减负

## Goal

把 `atg_reference/port/reference_step.c` 里一批工程化长名字改成更短的比赛代码名字，降低阅读负担。只做命名减负，不改算法、不改状态条件、不重构函数边界的大结构。

## Requirements

* 文件内部变量改短：
  * `g_vehicle_raw_ref_x` -> `car_raw_x`（用户先要求短名，后按审查意见接受该语义名）
  * `g_selected_line_source` -> `src`（`line_src()` 留给对外函数名，C 里变量/函数不能同名）
  * `g_selected_line_begin_id` -> `line_begin`
  * `g_circle_stall_frames` -> `circle_stall`
  * `g_circle_begin_dist` -> `begin_dist`
  * `g_circle_begin_last_dist` -> `last_begin_dist`
* 文件内部函数改短：
  * `truncate_cross_half_candidate_near_lines` -> `cut_half_line`
  * `choose_track_type_from_near_lines` -> `choose_track`
  * `build_circle_spliced_lines` -> `build_circle_line`
  * `normalize_selected_line` -> `norm_line`
  * `selected_line_ok` -> `line_ok`
  * `update_vehicle_ref_ipm` -> `update_car_ipm`
  * `find_selected_line_begin` -> `find_line_begin`
  * `update_aim_points` -> `update_aim`
  * `calc_guides` -> `calc_guide`
* 对外查询/辅助接口也删掉 `atg_reference_` 和 `atg_` 前缀，改成短名：
  * `atg_reference_track_line_found` -> `line_found`
  * `atg_reference_selected_line_source` -> `line_src`
  * `atg_reference_selected_line_source_id` -> `line_src_id`
  * `atg_reference_vehicle_raw_ref_x` -> `car_x`
  * `atg_reference_set_vehicle_raw_ref_x` -> `set_car_x`
  * `atg_reference_raw_ref_to_ipm` -> `raw_to_ipm`
* 不保留旧接口兼容 wrapper；外部调用点全部迁移到新短接口。
* 避免抽象框架味命名，例如 `source_selector`、`line_normalizer`、`element_dispatcher`。
* 长常量改成局部短 `enum` 名：
  * `RAW_LEFT_ANCHOR_X` -> `l_x`
  * `RAW_RIGHT_ANCHOR_X` -> `r_x`
  * `RAW_BOTTOM_ANCHOR_Y` -> `bot_y`
  * `CIRCLE_FIXED_IN_TARGET_RAW_Y` -> `in_y`
  * `CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X_OFFSET` -> `in_dx`（文件级不要用 `dx`，`dx/dy` 留给局部变量）
  * `CROSS_HALF_CANDIDATE_LPT_ID_MAX` -> `lpt_max`，但放进 `cut_half_line()` 局部
* 中文注释负责解释语义，不靠超长名字解释语义。

## Current Session Constraints / 防失忆约束

这项任务已经跨过多轮讨论，后续继续时必须先读本节，避免把已确定边界弄丢。

* 当前目标仍是**命名减负和仓库瘦身审查**，不是算法重构。
* 不改算法、不改状态机、不改控制逻辑；除非用户明确要求，避免新阈值、新 fallback、新状态条件。
* 用户明确要求：
  * 不保留旧接口兼容 wrapper。
  * 先别围绕 `report.cpp` 继续扩展清理；report 只做必要调用点同步。
  * 全局 `Lpt0_found/Ypt0_found/far_Lpt0_found` 这批变量**先不要改**，避免一次改太多。
  * `Xfound/Yfound` 这种局部变量改成 `x_found/y_found` 风格。
  * `CIRCLE_SIDE_*` 不要 enum；圆环 side 口径为 `0=左，1=右`。
  * `outer_ready(0/1)` 这种魔法参数不要，改成 `l_ready()/r_ready()` 这类直白函数。
  * `c_l/c_r` 太短，改成 `fix_l_by_c/fix_r_by_c`。
  * `done/stop` 语义不准，改成 `ran/found`。
* 已确认并删除：
  * `g_atg_reference_encoder_total`
  * `get_total_encoder()`
  * `motor.h` 中的旧声明
  这些只是 ATG port 里的空桥接。**不要误删真实编码器功能**。
* 真实编码器/电机路径在 `code/drivers/drive_output.cpp`：
  * `zf_driver_encoder`
  * `drive_output_read_feedback()`
  * `fb.left_speed_count/right_speed_count`
  * `runners.cpp` 累加 `rt->encoder_total`
  * `atg_reference_process_frame(gray, rt->encoder_total)`
  * `reference_step.c::update_dist(encoder_total)`
* 当前仓库结构审查结论：
  * 真实运行主线由 `code/CMakeLists.txt` 定义。
  * ATG 核心当前仍在 `atg_reference/port` + `atg_reference/Project/CODE`。
  * `.reference/`、`atg_reference/Project/USER/Cpu0_Main.c`、`logs/`、`.diag/`、`code/build*` 属于参考/日志/产物，不是主线。
  * `atg_reference/Project/CODE/data.c/h` 没编译、没 include。
  * `atg_reference/port/motor.h` 仍被 `circle.c/cross.c/yroad.c` include，但已是空壳；下一步若瘦身，可先删 include 再删头。
* 用户当前要求“结构审查只输出清单，不要改代码”。真正移动/删除文件需要下一步明确确认。
* 验证边界：
  * 用户多次表示当前阶段不需要编译，不要擅自转去修编译/report。
  * 可以做 `rg`、`git diff --check`、diff review。
  * 没跑构建时不能声称构建通过。

## Acceptance Criteria

* [x] 上述目标符号在代码中完成重命名；旧长接口名不在源码声明、实现或调用点中残留。
* [x] `reference_step.c` 的控制流程、判断条件、阈值、状态机行为保持不变。
* [x] `atg_reference_step.h` 只声明新短接口，不保留旧 `atg_reference_*` 兼容声明。
* [x] `code/app/runners.cpp`、`code/app/report.cpp`、`code/app/replay_log.cpp`、`code/tracking/atg_reference_mainline.cpp` 等外部调用点改用新短接口。
* [x] 最小相关构建或测试通过；如果无法运行完整构建，需要说明原因和替代检查。

## Definition of Done

* Diff 只包含命名、声明、调用点和注释同步，不夹带算法/状态条件调整。
* 运行最小相关验证。
* 收尾前检查 diff，确认没有引入第二套逻辑、静默 fallback、无关格式化或死代码。

## Technical Approach

采用机械重命名为主：先定位定义、声明和调用点，再替换为短名。对外接口直接切换到新短名，不保留旧 `atg_reference_*` wrapper。

## Decision (ADR-lite)

**Context**: 当前 `reference_step.c` 里存在 `atg_reference_vehicle_raw_ref_x` 这类重复前缀和长业务名，阅读负担高；用户希望简化成比赛代码风格。

**Decision**: 内部变量/函数直接改短；对外接口也删掉 `atg` 前缀，不保留旧 `atg_reference_*` wrapper。

**Consequences**: 源码更短、更贴近调车阅读习惯；短全局 C 函数名更容易与未来代码撞名，因此实现后必须用全仓搜索和构建确认没有冲突或漏改。

## Out of Scope

* 不改算法。
* 不改状态条件、阈值、优先级或状态机转移。
* 不做结构性拆文件、抽象层重构或 API 语义重设计。
* 不修改环境变量/config key，除非编译必须；`FRONT_CAR_VEHICLE_RAW_REF_X` 和 `vehicle_raw_ref_x` 本次保持不变。
* 仓库瘦身阶段只做清单与建议；没有用户确认前不移动/删除文件。

## Technical Notes

* 目标文件：`atg_reference/port/reference_step.c`
* 头文件：`atg_reference/port/atg_reference_step.h`
* 外部调用点已检查：
  * `code/tracking/atg_reference_mainline.cpp`
  * `code/app/runners.cpp`
  * `code/app/report.cpp`
  * `code/app/replay_log.cpp`
* 短名冲突初查：
  * `line_found` 已作为字段/日志键存在，没有同名函数。
  * `car_x` / `line_src` 作为对外函数名使用，文件内部状态分别落地为 `car_raw_x` / `src`，避免 C 标识符冲突。
  * `raw_to_ipm` 在工具脚本中作为局部变量出现，不影响 C/C++ 符号。

## Latest Structure Audit Snapshot

依据 `code/CMakeLists.txt`、include 搜索和调用搜索：

* 主目标 `front_car_mainline` 编译：
  * `code/app/*.cpp` 中的主链文件
  * `code/core/control.cpp`, `code/core/config.cpp`
  * `code/drivers/device.cpp`, `drive_output.cpp`, `imu_feedback.cpp`
  * `code/tracking/atg_reference_mainline.cpp`, `perspective.cpp`
  * `atg_reference/port/reference_globals.c`, `reference_step.c`
  * ATG CODE: `shy_Image/imgproc/utils/cross/Half_check/circle/Patching_Line/round/yroad/Ramp/road`
* 独立 target / host test：
  * `code/tools/key_supervisor.cpp`
  * `code/test/config_parsing_test.cpp`
  * `code/test/options_parsing_test.cpp`
* 未进主目标：
  * `atg_reference/Project/CODE/data.c/h`
  * `atg_reference/Project/USER/Cpu0_Main.c/h`
  * `code/drivers/motor_pulse.cpp/hpp`
* 明显可瘦身候选：
  * `code/build/`, `code/build-host/`
  * `.diag/`, `.diag.zip`, `.runtime/`
  * 大量 `logs/live-circle/*.log`，除非作为 replay 样例
  * `.reference/` 可改为 archive 或只保留必要参考文档/片段
  * 重复脚本：`scripts/*.sh` 与 `tools/*.sh`

## Progress

2026-06-27 已完成命名减负实现与复验：

* `reference_step.c` 内部变量/函数已按短名落地，外部查询接口改为 `line_found()`、`line_src()`、`line_src_id()`、`car_x()`、`set_car_x()`、`raw_to_ipm()`。
* `atg_reference_step.h` 只声明新短接口，不保留旧 `atg_reference_*` 兼容 wrapper。
* `code/tracking/atg_reference_mainline.cpp` 已同步调用短接口；app 层通过 tracking adapter 读取，不直接接触 port 短接口。
* 删除 `g_atg_reference_encoder_total`、`get_total_encoder()` 和 `motor.h` 里的旧编码器声明；真实编码器主线仍是 `drive_output_read_feedback()` -> `rt->encoder_total` -> `atg_reference_process_frame(...)`。
* diff review 时修正了两个容易混入行为变化的点：
  * 十字远线左分支保持旧的 `track_leftline(..., far_rpts0s_num - start - 1)` 输入点数和 `rpts_num = far_rpts0s_num - start` 输出计数合同。
  * 圆环 side 编码改为 `0=左,1=右` 后，`check_circle()` 双侧同时命中时仍按旧的右优先顺序仲裁。
* 保留旧 `circle_in_fixed_left/right` 的 source id 映射，避免日志/数据字典语义收窄。

验证：

```bash
git diff --check -- atg_reference/Project/CODE/circle.c atg_reference/Project/CODE/circle.h atg_reference/Project/CODE/cross.c atg_reference/Project/CODE/yroad.c atg_reference/port/atg_reference_step.h atg_reference/port/motor.h atg_reference/port/reference_globals.c atg_reference/port/reference_step.c code/app/assistant.cpp code/app/control_input_builder.cpp code/app/replay_log.cpp code/app/report.cpp code/app/runners.cpp code/tracking/atg_reference_mainline.cpp code/tracking/atg_reference_mainline.hpp
rg -n "atg_reference_track_line_found|atg_reference_selected_line_source\\(|atg_reference_selected_line_source_id\\(|atg_reference_vehicle_raw_ref_x|atg_reference_set_vehicle_raw_ref_x|atg_reference_raw_ref_to_ipm|get_total_encoder|g_atg_reference_encoder_total" atg_reference code
bash test.sh --host
bash test.sh
```

结果：

* `git diff --check` 通过。
* 旧 port 查询/编码器空桥接名搜索无命中。
* `bash test.sh --host` 通过。
* `bash test.sh` 通过。
