# circle.c BEGIN→IN 几何相位锚定

## Goal

把 `CIRCLE_LEFT/RIGHT_BEGIN -> *_IN` 从旧的 `mouth_loss + begin_dist >= 600` 推进，改成几何主线：

```text
A 点确认入口 → 同侧 B 点到指定 raw_y 行 → 切 IN → IN 内找 C 点 → C 点稳定后补线接管 → C 证据 + gyro 进 RUNNING
```

目标是让入环动作由当前帧入口结构决定，而不是靠丢线/距离窗口把固定补线提前或拖后。

## Current Implementation（2026-06-25）

- A 点：左环使用 `Lpt0`，右环使用 `Lpt1`。
- B 点：同侧边线从 A 后继续扫描；左环在 `rpts0s` 找 raw_x 局部最大，右环在 `rpts1s` 找 raw_x 局部最小。
- BEGIN→IN：`circle_B_streak >= 2 && B.raw_y >= 58`，transition reason 为 `B_row`。
- `mouth_ready` 只保留在 `ATGCircleABCDiag`/`ATGCircleBeginDiag` 里做诊断，不再触发 IN。
- C 点：IN 阶段继续在同侧边线上找 raw_y 局部最大，并要求比 B 更靠内侧。
- C 补线：`circle_C_streak >= 2` 后才设置 `circle_ref_mode = CIRCLE_REF_IN_C`。
- `reference_step.c` 中 `CIRCLE_*_IN && CIRCLE_REF_IN_C` 才发布 `circle_in_c_left/right`，不再无条件走旧 fixed IN 线。当前 C 补线是“同侧底部 raw anchor -> C，再半赛宽偏移成中心线”，不是“C -> 外侧直道”的双边融合线。
- IN→RUNNING：`circle_C_streak >= 2 && heading >= 600`，避免 C 没接管就靠 gyro 进 RUNNING。

## Acceptance Criteria

- [x] BEGIN→IN 主触发改为 `B_row`，左右对称。
- [x] `mouth_loss` 不再作为 `print_circle_transition()` 的 reason，只作为诊断字段 `mouth_ready`。
- [x] IN 阶段新增 C 点搜索，C 点稳定后才发布 `CIRCLE_REF_IN_C`。
- [x] `reference_step.c` 的 IN 选线改为 C 补线来源 `circle_in_c_left/right`，旧 fixed IN 不再自动接管。
- [x] `git diff --check`、`bash code/test.sh --host`、`touch atg_reference/Project/CODE/circle.c atg_reference/port/reference_step.c && bash code/test.sh` 均通过。
- [ ] 上车实测：`ATGCircleABCDiag` 中 B/C 是否稳定出现，`B_row` 时刻是否合理，`sel` 是否出现 `circle_in_c_left/right`。
- [ ] 上车实测：普通弯道是否误出 B/C。当前 B/C 只有局部极值，没有 Lpt 那种角度显著度门；若误判，再考虑把 `mouth_ready` 从诊断升级为 `B_row` 的 AND 确认。
- [ ] 上车实测：C 补线形状是否符合入环路径。若“同侧底部 -> C”偏差大，再单独评估 “C -> 外侧直道”锚点。

## Out of Scope

- 不继续调 END；END 编码器释放只是防死锁补洞。
- 不实现 BEGIN 阶段 A-B 补线封口。本轮先让 BEGIN 继续跟外线，只用 B 到行决定切 IN。
- 不引入 Joshua 行数组/白列数据结构；继续复用 ATG `Lpt`、`rpts0s/rpts1s`、`track_leftline/track_rightline` 管道。
- 不改控制链：当前控制仍是 `rptsn -> guide_error -> yaw_cmd -> duty`。

## Decision (ADR-lite)

**Context**: 旧方案把 BEGIN→IN 简化到 `mouth_loss + 600` 后，仍然没有真正的 B/C 几何点，也没有 C 点补线。用户明确要求回到“先识别结构点，再补线造路”的主线。

**Decision**: 保留 ATG 当前 IPM/rpts 管道，用 `Lpt0/Lpt1` 当 A，沿同侧 `rpts*s` 找 B/C：B 到指定 raw_y 行触发 IN，C 连续确认后在 `reference_step.c` 构造入环补线，IN→RUNNING 叠加 C 证据和 60° gyro。

**Consequences**: 入环是否成功现在主要看 B/C 点是否在实车画面稳定出现。若 C 点找不到，IN 会没有 C 补线并最终由 stall reset 显式暴露，而不是悄悄走旧 fixed line。

## Research References

- `research/geometry-entry-rationale.md` — 本轮几何入环行为变更表。
- `research/begin-dist-distribution.md` — 旧 `mouth_loss + 600` 方案的离线依据，现仅作为历史背景。
- [`../../../atg_reference/PORTING.md`](../../../atg_reference/PORTING.md) — 当前移植层 Change Rationale。
