# Thinking Guides

> **Purpose**: Expand your thinking to catch things you might not have considered.

---

## Why Thinking Guides?

**Most bugs and tech debt come from "didn't think of that"**, not from lack of skill:

- Didn't think about what happens at layer boundaries → cross-layer bugs
- Didn't think about code patterns repeating → duplicated code everywhere
- Didn't think about edge cases → runtime errors
- Didn't think about future maintainers → unreadable code

These guides help you **ask the right questions before coding**.

---

## Available Guides

| Guide | Purpose | When to Use |
|-------|---------|-------------|
| [Code Reuse Thinking Guide](./code-reuse-thinking-guide.md) | Identify patterns and reduce duplication | When you notice repeated patterns |
| [Cross-Layer Thinking Guide](./cross-layer-thinking-guide.md) | Think through data flow across layers | Features spanning multiple layers |
| [Tracking Critical Audit Guide](../tracking/critical-audit-guide.md) | Coordinate reference, history, tool, and sub-agent checks for tracking changes | Before changing cross/ring/mainline/boundary/imgproc/control tracking behavior |

---

## Quick Reference: Thinking Triggers

### When to Think About Cross-Layer Issues

- [ ] Feature touches 3+ layers (frame input, tracking, control, drive, report)
- [ ] Coordinate system, sign, scale, or validity semantics change between layers
- [ ] Multiple runtime paths need the same config or tracking-derived value
- [ ] You're not sure where to put some logic

→ Read [Cross-Layer Thinking Guide](./cross-layer-thinking-guide.md)

### When to Think About Code Reuse

- [ ] You're writing similar code to something that exists
- [ ] You see the same pattern repeated 3+ times
- [ ] You're adding a new field to multiple places
- [ ] **You're modifying any constant or config**
- [ ] **You're creating a new utility/helper function** ← Search first!

→ Read [Code Reuse Thinking Guide](./code-reuse-thinking-guide.md)

### When to Think About Tracking Risk

- [ ] You are changing `code/tracking/`
- [ ] You are changing tracking-derived control input
- [ ] You are changing cross/ring/mainline/boundary/imgproc thresholds or state
- [ ] You are investigating a regression from a known git baseline
- [ ] The user asks for reference-version alignment or rejects fallback fixes

→ Read [Tracking Critical Audit Guide](../tracking/critical-audit-guide.md)

### When to Analyze Circle Logs

- [ ] The user provides a circle test log or asks "分析 log"
- [ ] The user asks about a roundabout test result (左环/右环)
- [ ] You need to evaluate entry detection, in-circle control, or exit behavior

**流程:**
1. 先用 `live_circle_test.sh review <drive_id>` 提取关键数据
   - 脚本位置：`.trellis/tasks/06-21-circle-exit-line-evidence-baseline/live_circle_test.sh`
   - 如果没给 drive_id，手动 run grep 提取状态转换和关键帧
2. 按 [Circle Log Analysis Format](../tracking/circle-log-analysis.md) **严格 8 段格式**输出分析
   - ③④⑤ 阶段必须标注 guide/yaw 是否饱和
   - ⑥ 必须确认 src=14 固定线
   - ⑦ 必须对比 END→CIRCLE_NONE 的 guide 跳变
   - ⑧ 必须给出结论表
3. 任何一句模型（主模型/trellis-check/trellis-implement）在做 log 分析时都须遵守此格式

---

## Pre-Modification Rule (CRITICAL)

> **Before changing ANY value, ALWAYS search first!**

```bash
# Exact value or symbol search
rg "value_to_change" .
```

If the location or data flow is unclear, use `fast_context_search` first. If
the MCP is slow to appear, retry/wait before downgrading to `rg`.

This single habit prevents most "forgot to update X" bugs.

---

## How to Use This Directory

1. **Before coding**: Skim the relevant thinking guide
2. **During coding**: If something feels repetitive or complex, check the guides
3. **After bugs**: Add new insights to the relevant guide (learn from mistakes)

---

## Contributing

Found a new "didn't think of that" moment? Add it to the relevant guide.

---

**Core Principle**: 30 minutes of thinking saves 3 hours of debugging.
