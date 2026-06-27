# cross.c 十字状态减法清理

## Goal

删掉 `cross.c`/`cross.h` 中没有运行合同的十字状态、壳函数和重复远线入口，降低维护复杂度。优先减法，不重写远线算法，不引入参数化抽象。

## What I Already Know

* 用户明确要求“赶紧删了，做吧，大胆做”。
* `cross.c` 当前仍把状态机、远线扫线、圆环补线和半十字状态混在一起。
* `CROSS_HALF_BEGIN`、`CROSS_HALF_RIGHT`、`CROSS_HALF_LEFT` 只在 enum/report 名字映射中出现，没有运行时写入。
* `Double_check_cross_L/R()` 只是 `cross_farline_L/R()` 的无调用壳函数。
* `cross_farline_half()` 没有调用点，并且重复 `cross_farline()` 主体。
* `far_Lpt0_found_flag` / `far_Lpt1_found_flag` 只被清零，没有读者。

## Requirements

* 删除未使用的 `CROSS_HALF_BEGIN/RIGHT/LEFT` 状态。
* 删除未使用的 `Double_check_cross_L/R()` 壳函数。
* 删除未使用的 `cross_farline_half()`。
* 删除只清不读的 `far_Lpt0_found_flag` / `far_Lpt1_found_flag`。
* 保留当前可达行为：`CROSS_NONE`、`CROSS_BEGIN`、`CROSS_IN`、`CROSS_HALF`，以及 `cross_farline()`、`cross_farline_L()`、`cross_farline_R()`。
* 只对 `cross_farline_L()` / `cross_farline_R()` 做机械流程拆分，保留现有判断条件和全局变量。
* 拆分后 `cross_farline_L()` / `cross_farline_R()` 只保留短流程调用，不新增通用 `side` 参数、不新增结构体。

## Out Of Scope

* 不重写远线扫线算法。
* 不把左右远线改成参数化通用函数。
* 不改半十字进入判据。
* 不改圆环 OUT 借用远线搜索的行为。

## Acceptance Criteria

* [x] 全仓库不再引用删除的状态/函数/flag。
* [x] `cross_type_name[CROSS_NUM]` 与 enum 数量一致。
* [x] `git diff --check` 通过。
* [x] `bash code/test.sh --host` 通过。
* [x] `bash code/test.sh` 通过。
* [ ] `cross_farline_L()` / `cross_farline_R()` 拆成短流程函数。

## Technical Notes

* 适用规范：`.trellis/spec/tracking/critical-audit-guide.md`、`.trellis/spec/quality/embedded-tracking-guidelines.md`。
* 当前任务属于删除无合同状态和死路径，不是添加兜底。
