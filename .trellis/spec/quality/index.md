# Embedded Tracking Quality Specs

This layer applies to embedded C/C++ tracking, control input, runtime config,
driver-facing helpers, diagnostics, and host/board validation for this
repository.

## Pre-Development Checklist

- Read [Embedded Tracking Guidelines](./embedded-tracking-guidelines.md).
- Read [Smartcar Competition Code Style](./smartcar-code-style.md).
- If the work touches `code/tracking/`, tracking-derived control input, or
  tracking report output, also read
  [Tracking Critical Audit Guide](../tracking/critical-audit-guide.md).
- Search the current owner code and recent diff before changing thresholds,
  config fields, parser behavior, or state-machine rules.

## Quality Check

- Confirm the change stays simple, direct, and tied to current-frame evidence or
  a reference-version contract.
- Confirm invalid config/env/sysfs input is explicit and does not silently
  coerce to a plausible value.
- Confirm there is no stale-geometry fallback, hidden state masking, second
  truth source, or broad rewrite.
- Run the narrowest meaningful validation first, then `git diff --check` and
  the relevant `code/test.sh` target when code changed.

## Guidelines Index

| Guide | Description | Status |
| --- | --- | --- |
| [Embedded Tracking Guidelines](./embedded-tracking-guidelines.md) | C/C++ quality, parsing, tracking evidence, and validation contracts | Active |
| [Smartcar Competition Code Style](./smartcar-code-style.md) | 比赛代码主链、命名、函数边界和禁止工程化方向 | Active |
| [Refactoring And Diagnostic Discipline](./refactoring-and-diagnostic-discipline.md) | Commit boundary purity, debug display seed source consistency, extract-and-gate diagnostic pattern | Active |
