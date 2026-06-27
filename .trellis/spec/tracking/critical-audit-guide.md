# Tracking Critical Audit Guide

Use this guide before changing `code/tracking/`, tracking-related control
inputs, or tracking report output.

## Trigger

Read this guide when a task touches:

- cross, ring, zebra, mainline, boundary, or imgproc state;
- control reference point or steering input derived from tracking;
- diagnostic fields used to judge tracking behavior;
- any threshold or state transition that can affect current-frame geometry.

## Tool Routing

- Local semantic discovery: use `fast_context_search` first when the file,
  call chain, or data flow is unclear.
- Slow MCP rule: `fast_context_search` can take about 200s to appear. Retry or
  wait before declaring it unavailable.
- Downgrade rule: if `fast_context_search` remains unavailable, record that
  fact and use `rg` plus direct file reads. Do not treat this as repository-wide
  semantic coverage.
- External/current facts: use `smart-search-cli`; fetch source text before
  making claim-level conclusions.

## Four Fixed Audit Roles

For critical tracking edits, use four read-only audit roles when the runtime
allows sub-agents:

1. Reference contract: compare the relevant reference implementation line by
   line and list exact behavioral contracts.
2. Current implementation: inspect the current owner functions and identify
   mismatches or already-correct paths.
3. Git regression: compare the known baseline, regression commit, and current
   HEAD to isolate behavior changes.
4. Trellis/check gate: verify PRD, spec, research notes, validation commands,
   and final scope alignment.

If the runtime cannot host all four agents, record the limit, run the missing
roles in the main session, and retry when slots free. Never claim a role ran if
it did not.

## Architecture Quick Reference (必读)

本工程核心心智模型：**ATG2022 舵机车大脑 → LS2K 差速车手脚**。所有问题都来自这个"语言不匹配"。

### 三层身份

| 层 | 身份 | 关键文件 |
|---|------|----------|
| ① ATG2022 源头 | 买来的舵机车算法 | `atg_reference/Project/CODE/`（circle.c / cross.c / shy_Image.c…） |
| ② 移植层 | 龙芯适配胶水 | `atg_reference/port/reference_step.c` |
| ③ 当前车 | 差速车，guide_error → yaw_cmd → 左右轮 duty | `code/tracking/`, `code/core/control.cpp` |

### 一帧管道

```text
摄像头灰度图 → ATG 算法（搜线/角点/IPM/十字/圆环/补线/选线）
→ rptsn 中线 → atg_lookahead_error() → guide_error
→ control.cpp（guide_error → target_yaw → yaw_cmd → duty）
→ 左右电机
```

### 硬边界（别碰）

- `pure_angle` 是参考版舵机角，**不进控制环**
- `cross_type` / `circle_type` 只用于减速/刹车，**不直接转方向**
- IPM 生产真相源只有 `shy_Image.c::rot/inv_rot`，不接旧 `camera_param.c`

### 已退休路线

- 旧本地 tracking（find_seeds / trace_edges / boundary…）
- 旧控制入口（solve_runtime*）
- Unity CD 旧参考
- 旧 IPM 表路线
- 不看旧本地 `ring/cross/mainline` 状态机字段
- 不从 Unity CD 恢复 `pending/AIB/BW/ring_times` 合同
- 不用上一帧中线/边界或 guessed opposite side 伪造当前帧几何
- 不把参考版舵机 `pure_angle` 当成当前差速控制输入

详细内容见：
- `docs/01_全局地图.md` — 三层身份和转向"语言"差异
- `docs/02_当前主链与参考版对比.md` — 逐帧管道和层级合同
- `docs/03_调参与验证手册.md` — 控制参数来源和验证命令
- `docs/04_当前问题.md` — P0/P1 现状

## Three Reference Sources (必读)

每次修改 tracking 元素识别逻辑前，确认已知以下三个参考源及其路径：

| # | 参考 | 路径 | 用途 |
|---|------|------|------|
| 1 | **ATG2022** | `atg_reference/Project/CODE/` | 购入的参考算法，迁移主目标。圆环用 `circle.c`，十字用 `cross.c` + `Half_check.c`，补线用 `Patching_Line.c` |
| 2 | **Joshua.Xu 智能车开源** | `.reference/joshua-xu-smartcar/` | 第18届四轮车开源，环岛9阶段状态机 + 十字角点撕裂法 + 陀螺仪防误判门限 |
| 3 | **ittuann 圆环参考** | `E:\longxin\参考\`（`Ring.c` / `Ring.h` / `tracking_ring.cc`） | 陀螺仪积分圆环方案，heading 阶段判断，项目外独立存放 |

**关键映射**：
- 圆环阶段转换：ATG 用距离+视觉，ittuann 用 heading 角度，Joshua.Xu 用陀螺仪积分+视觉组合
- 角点检测：ATG 用 LPT，Joshua.Xu 用边界撕裂法（下方连续+上方撕裂）
- 陀螺仪防误判：Joshua.Xu 出环要求积分>=200° 才开单调转折判断，防光干扰

**修改行为前必须回答**：我的改动对应哪个参考的哪个行为？是否有第三个参考给出了不同方案？

## Evidence Checklist

- [ ] Symptom: screenshot, log, replay frame, or command output is identified.
- [ ] Reference: matching reference code or an explicit limitation is recorded.
- [ ] Current owner: exact current functions and state variables are inspected.
- [ ] History: relevant git diff is checked for regressions.
- [ ] If the frame is single-side/no-opposite-anchor, the audit states that
      current-frame identity is not uniquely provable without an extra
      assumption.
- [ ] Current-frame control risk and cross-frame learning risk are separated;
      do not collapse them into one generic reject rule.
- [ ] If the task touches `update_search_center()`, identify whether the gate is
      trace success, IPM order success, selected `mid_ok >= k_min_border_step`,
      or full `publish_track_result()` success. Do not use "publish" as
      shorthand for all of these.
- [ ] If the task moves element-frame `update_search_center()` timing, verify
      the writeback trigger domain is unchanged: accepted nearline paths may be
      delayed, but CROSS_IN farline-only and IPM-rejected continuation paths
      must not gain new search-center learning.
- [ ] If `width_base` may update after `element_process()`, verify the decision
      comes from frame-start ordinary state, not mutated post-element
      `rt->cross.state` / `rt->ring.kind`.
- [ ] If the suspected symptom is straight-line twisting, decide whether
      `guide_error` is unstable before touching tracking; stable `guide_error`
      points to the differential control path.
- [ ] If using live logs, check whether changed-state filtering may have
      suppressed quiet drift frames before claiming the logs prove stability.
- [ ] Fix shape: no stale-midline fallback, no hidden state masking, no broad
      rewrite.
- [ ] Code style: the edit is simple, direct, and local.
- [ ] Validation: `git diff --check`, `bash code/test.sh --host`,
      `bash code/test.sh`, and targeted analyze/replay are run or blocked with
      a reason.

## Change Rationale Table

Every tracking behavior change must leave a short fixed table in the task
research note or final handoff. Do this even for a small edit.

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| `<reference file:line + contract>` | `<current owner and mismatch>` | `<file:function>` | `<current-frame reason>` | `<reject/fail/validation evidence>` |

Rules:

- The `参考版怎么样` column must cite the reference code path or say explicitly
  that no direct equivalent exists.
- For single-side/no-opposite-anchor changes, the table must say which extra
  assumption is introduced. If no behavior changes, say the patch is
  diagnostic-only.
- For ring/circle behavior, cite `atg_reference/Project/CODE/circle.c` as the
  active mainline reference. ittuann heading 方案见 `E:\longxin\参考\Ring.c`。
  Joshua.Xu 9阶段状态机见
  `.reference/joshua-xu-smartcar/06-circle-island.md`。若 Unity `CD.cpp`
  被提及，标注为 archived old evidence，除非用户明确重新选择 Unity 路径。
- The `当前代码差异` and `原因` columns must explain the local owner and why the
  edit maps to the reference contract.
- The `不是兜底的证据` column must show that the edit rejects, fails, or reports
  current-frame evidence instead of reusing stale state. If a threshold is
  introduced or changed, state whether it comes from the reference, measured
  frames, or a hardware/input difference; do not hide it as generic cleanup.

## Single-Side / No-Opposite-Anchor Audit

Before changing behavior for a single-side frame, answer these questions:

1. Is exactly one side present after trace filtering?
2. Is the opposite seed or trace absent, rather than rejected by a proven
   identity gate?
3. Are there enough paired IPM/work points to judge left/right order? If not,
   say explicitly that IPM order is unknowable in this frame.
4. Did `update_search_center()` learn from this frame before final publication
   succeeded or failed?
5. Did the selected side produce `mid_ok >= k_min_border_step` before learning?
   If not, the issue is learning-order, not side-identity proof.
6. Did the frame fail only on the lookahead part of `publish_track_result()`?
   If so, do not automatically treat it as acquisition geometry failure.
7. Did the frame publish `guide_error`, and did that guide align with the
   observed twist/crawl?
8. Which assumption would a proposed gate introduce: center-column, attach
   distance, temporal prior, or another hardware-specific rule?

Allowed conclusion if these cannot be answered: **insufficient evidence; add
diagnostics or collect better logs before changing behavior.**
