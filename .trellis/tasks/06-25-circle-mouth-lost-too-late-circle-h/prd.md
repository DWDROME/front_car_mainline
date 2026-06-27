# circle 代码清理：标注废弃变量、改名 mouth_lost_too_late、修正 circle.h 注释

## Goal

对 circle.c / circle.h 进行零行为清理，提高代码可读性和可维护性。不动阈值、不动逻辑。

## Requirements

1. `have_left_line`/`have_right_line` 声明处加 `// DEPRECATED: not used for state progression`
2. `mouth_lost_too_late` → `abort_late_mouth_loss`，配注释说明这是异常撤回条件，不是推进条件
3. circle.h `enum circle_type_e` 注释从当前乱码修正为三段状态机说明
4. 如需要，统一日志字段名（优先级最低）

## Acceptance Criteria

- [ ] 编译通过，无 warning
- [ ] `git diff` 仅显示注释/命名改动，无逻辑变化
- [ ] `have_left_line`/`have_right_line` 出现处均有 DEPRECATED 标记
- [ ] `mouth_lost_too_late` 不再出现在代码中，全部替换为 `abort_late_mouth_loss`
- [ ] circle.h 枚举注释清晰描述三个阶段的语义

## Out of Scope

- 不改变任何阈值常量
- 不改动状态跳转逻辑
- 不改动 reference_step.c 或其他文件
