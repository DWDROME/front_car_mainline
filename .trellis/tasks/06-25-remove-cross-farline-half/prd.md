# 删除未使用 cross_farline_half

## Goal

删除未使用且与 `cross_farline()` 几乎重复的 `cross_farline_half()`，减少重复逻辑和后续维护分叉。

## Requirements

* 删除 `atg_reference/Project/CODE/cross.c` 中的 `cross_farline_half()` 定义。
* 删除 `atg_reference/Project/CODE/cross.h` 中的 `cross_farline_half()` 声明。
* 保持 `cross_farline()` 现有行为不变。
* 不引入新的 helper、参数化接口或额外重构。

## Acceptance Criteria

* [ ] `rg "cross_farline_half"` 只在历史/任务文档中出现，不再出现在编译代码声明或定义中。
* [ ] `cross_farline()` 的代码 diff 不包含行为变更。
* [ ] 最小相关构建或静态检查完成；如无法运行，说明原因。

## Definition of Done

* 变更范围限于删除死代码和对应声明。
* 收尾前检查 diff，确认无无关改动。

## Technical Approach

直接删除未调用的函数定义和头文件声明。之前仓库检索显示 `cross_farline_half()` 只有定义和声明，没有调用点。

## Decision (ADR-lite)

**Context**: `cross_farline_half()` 与 `cross_farline()` 大段重复，唯一实质差异是右远线 L 角点搜索上限为 40 而不是 70，但当前没有调用点。

**Decision**: 删除 `cross_farline_half()`，不保留参数化入口。

**Consequences**: 降低重复维护成本；如果未来重新需要 40 点搜索窗口，应在明确调用场景后从 `cross_farline()` 提取参数化 helper。

## Out of Scope

* 不调整 `cross_farline()` 阈值、搜索窗口或识别逻辑。
* 不修改圆环、半十字或十字识别流程的其他行为。
* 不做文件重命名或大范围格式化。

## Technical Notes

* 目标文件：`atg_reference/Project/CODE/cross.c`
* 目标声明：`atg_reference/Project/CODE/cross.h`
* 用户已确认删除。
