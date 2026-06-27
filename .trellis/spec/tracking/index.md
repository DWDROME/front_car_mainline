# Tracking Audit Specs

This layer applies to high-risk tracking behavior changes: cross, ring,
mainline, boundary, imgproc, tracking-derived control input, and tracking
diagnostic/report output.

## Pre-Development Checklist

- Read [Critical Audit Guide](./critical-audit-guide.md).
- Read [Embedded Tracking Guidelines](../quality/embedded-tracking-guidelines.md)
  for coding and validation constraints.
- Identify the exact symptom, reference contract, current owner function, and
  relevant history before editing behavior.
- Use `fast_context_search` for unclear local discovery when available; fall
  back to `rg` plus direct reads only after recording the downgrade.

## Quality Check

- Four audit roles are run or accounted for: reference contract, current
  implementation, git regression, and Trellis/spec/check gate.
- Any behavior change leaves the fixed rationale table required by the critical
  audit guide.
- Current-frame control risk and cross-frame learning risk are kept separate.
- Validation commands are run or blocked with a concrete reason.

## Guidelines Index

| Guide | Description | Status |
| --- | --- | --- |
| [Critical Audit Guide](./critical-audit-guide.md) | Reference/history/tool/check workflow for critical tracking edits | Active |
| [Circle Log Analysis](./circle-log-analysis.md) | 圆环测试 log 强制 8 段分析格式 | Active |
