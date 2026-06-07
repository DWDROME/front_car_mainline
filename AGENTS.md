<!-- TRELLIS:START -->
# Trellis Instructions

These instructions are for AI assistants working in this project.

This project is managed by Trellis. The working knowledge you need lives under `.trellis/`:

- `.trellis/workflow.md` — development phases, when to create tasks, skill routing
- `.trellis/spec/` — package- and layer-scoped coding guidelines (read before writing code in a given layer)
- `.trellis/workspace/` — per-developer journals and session traces
- `.trellis/tasks/` — active and archived tasks (PRDs, research, jsonl context)

If a Trellis command is available on your platform (e.g. `/trellis:finish-work`, `/trellis:continue`), prefer it over manual steps. Not every platform exposes every command.

If you're using Codex or another agent-capable tool, additional project-scoped helpers may live in:
- `.agents/skills/` — reusable Trellis skills
- `.codex/agents/` — optional custom subagents

Managed by Trellis. Edits outside this block are preserved; edits inside may be overwritten by a future `trellis update`.

<!-- TRELLIS:END -->

## Project Operating Norms

- User-facing replies should be in Simplified Chinese; keep code identifiers,
  paths, commands, symbols, and logs exact.
- Use Trellis as the coordinator for non-trivial tracking work. Keep the active
  task PRD, research notes, specs, and check context aligned; do not rely on
  chat memory as the source of truth.
- For local repository discovery, prefer `fast_context_search` when the code
  location, call chain, or data flow is unclear. The MCP can take about 200s to
  appear; retry/check availability before declaring it unavailable. If it is
  still unavailable, record that fact and continue with `rg` plus direct file
  reads.
- For external, current, documentation, or URL-backed facts, use
  `smart-search-cli` and fetch source text before making claim-level
  conclusions.
- Critical tracking changes require four fixed read-only audit roles when the
  runtime allows it: reference contract, current implementation, git regression,
  and Trellis/spec/check gate. If the agent limit prevents all four, record the
  limit, cover the missing roles in the main session, and retry when slots free.
- Highest coding rule: keep C/C++ simple and direct. Make small local edits,
  avoid broad abstractions, avoid hidden state, and do not add fallback-style
  behavior to hide missing current-frame geometry.
- Tracking fixes must be evidence-backed: compare the reference version, inspect
  the current code and recent diff, then run targeted validation. Do not reuse
  last-frame midlines or drift thresholds without a documented reason.
- For ring/circle behavior, RT1064 `circle.c` is the active mainline reference.
  Unity `CD.cpp` is archived old comparison evidence only; do not treat
  `check_ring/AIB/BW/pending/ring_times` as the active tracking contract.
- When comparing RT1064 control code, keep the actuator boundary explicit:
  RT1064 `pure_angle -> servo_pid` is a steering-servo path, while this project
  uses differential `guide_error -> target_yaw -> yaw_cmd`; do not port
  `pure_angle` into the current outer loop as a tracking alignment fix.
- Every tracking behavior change must include a fixed rationale table in the
  task research note or final handoff: `参考版怎么样`, `当前代码差异`,
  `我修改什么`, `原因`, and `不是兜底的证据`. If no direct reference
  equivalent exists, say that explicitly instead of implying one.
- When committing multi-file or high-impact tracking changes, use a clear
  Chinese commit body, not only a short title. The body must state why the
  change is needed, what active reference contract it follows, what changed,
  why it is not fallback-style behavior, and which validations passed.
