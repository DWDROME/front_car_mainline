# Initial Baseline

Date: 2026-05-31

## Authority

- Project rules: `AGENTS.md`
- Control owner: `code/core/control.cpp`
- Runtime driver output owner: `code/drivers/drive_output.cpp`
- Validation entry: `bash "code/test.sh" --host`

## Main Chain

```text
tracking_process_frame(rt)
-> guide_error
-> target_yaw
-> duty
-> drive_output_apply
```

## Current Control Concern

`code/core/control.cpp` currently works like a compact closed-loop control library. It mixes feedback filtering, visual outer loop, yaw feedback loop, wheel target calculation, and wheel PI into helper functions and a state struct. The next plan should preserve behavior while rewriting the file into direct, stage-commented, field-readable flow.

