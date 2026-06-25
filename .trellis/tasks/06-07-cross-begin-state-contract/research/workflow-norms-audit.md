# Workflow Norms Audit

## Scope

This note records the evidence for adding project-local workflow norms to the
active tracking reference-alignment task.

## Tool Evidence

- `smart-search doctor --format json` was run in this repo. Result: overall
  `ok: true`; main search, Exa, Context7, and web fetch capabilities are
  available. Zhipu is not configured. Tavily returned a warning, but web fetch
  still has configured fallback capability.
- `tool_search` was queried for `fast_context_search` / fast-context MCP twice
  during this pass. It returned no available tool. Per the new rule, this pass
  records the unavailability and used `rg` plus direct file reads for local
  evidence.
- 2026-06-08 update: after the user restarted the MCP configuration,
  `mcp__fast_context__fast_context_search` was available and was used for the
  trace/midline ownership chain before final validation.

## Fixed Audit Roles Covered

- Entry-rule audit: checked `AGENTS.md`, workflow, and spec placement.
- Trellis coordination audit: checked `prd.md`, `task.json`, `implement.jsonl`,
  `check.jsonl`, and spec indices.
- Simple-code/fallback audit: checked quality wording for direct C/C++ code,
  trace/midline ownership, and forbidden stale-geometry patterns.
- Final consistency audit: checked whether workflow breadcrumbs, task context,
  tool routing, four-role audit, and simple-code rules were all aligned.

## Files Updated

- `AGENTS.md`: project entry norms outside the Trellis managed block.
- `.trellis/workflow.md`: critical tracking add-on in both in-progress
  breadcrumb blocks.
- `.trellis/spec/quality/index.md`: embedded tracking quality guideline status.
- `.trellis/spec/quality/embedded-tracking-guidelines.md`: tracking modification contract,
  forbidden fallbacks, highest code rule, trace/midline ownership, and validation
  checklist.
- `.trellis/spec/guides/index.md`: tracking-risk trigger and `rg`/fast-context
  search wording.
- `.trellis/spec/tracking/critical-audit-guide.md`: tool routing,
  four fixed audit roles, and evidence checklist.
- `.trellis/tasks/06-07-cross-begin-state-contract/prd.md`: scope and
  acceptance criteria for workflow norms.
- `.trellis/tasks/06-07-cross-begin-state-contract/task.json`: title,
  description, notes, and workflow metadata.
- `.trellis/tasks/06-07-cross-begin-state-contract/implement.jsonl` and
  `check.jsonl`: added active checklist/spec/guide entries.

## Git Boundary

`.trellis/` is currently ignored by the repository `.gitignore`, so normal
`git status` only shows `AGENTS.md`. The Trellis changes are local workflow
state unless they are force-added with `git add -f` or the ignore policy is
changed.

## 2026-06-08 Reference-First Flowchart Recheck

User correction: the main line is reference-version alignment. Existing pushes
are important evidence, but they are not the primary contract.

During the renewed reference-first audit, `docs/流程图.md` and Trellis docs mixed
two reference sources. The Unity CD.cpp `check_ring/AIB/BW/pending/ring_times`
path is now old archived comparison only. The active ring contract is RT1064
`circle.c::check_circle()`: single-side L plus opposite straight enters BEGIN.

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `circle.c:23-31` enters left/right circle BEGIN from single-side L plus opposite straight; RT1064 `main.c:330-347` checks cross first and clears circle when cross exists. | Active code had been moved to Unity-style pending/AIB/BW/ring_times, and docs/specs were still calling that generic "reference". | Copied Unity `CD.cpp` into `docs/reference/unity_CD_old.cpp`, restored active `ring.cpp/element.cpp/types/report` to the RT1064 chain, and updated flow/spec/task notes. | This prevents future agents from mixing Unity CD.cpp and RT1064 as one "reference version". | The change removes a Unity-only staging path instead of adding hidden state. Ring entry still depends on current-frame `l_ok` and opposite straight evidence; no stale midline/boundary/control output is reused. |
