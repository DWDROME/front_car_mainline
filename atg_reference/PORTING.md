# ATG2022 Porting Boundary

Goal: make ATG2022 the new algorithm mainline while keeping the current LS2K
peripheral, control, and upper-monitor layers.

## Layer Contract

| Layer | Directory | Rule |
| --- | --- | --- |
| ATG algorithm core | `atg_reference/Project/CODE/` | Keep close to copied source. Do not hide port logic here. |
| ATG loop evidence | `atg_reference/Project/USER/` | Read-only reference for ordering, selected-line choice, and element sequence. |
| Port layer | `atg_reference/port/` | Provide TC264 type aliases, globals, encoder hooks, image input, and LS2K bridge functions. |
| Current bridge | `code/tracking/` | Expose the existing `tracking_process_frame()` contract to app/core/report. |
| LS2K app/core/drivers | `code/app/`, `code/core/`, `code/drivers/` | Keep current UVC capture, differential control, encoder accumulation, and upper-monitor output. |

## What Migrates

| Area | Decision |
| --- | --- |
| Line search and resampling | Migrate to ATG `shy_Image.c` path. |
| Corner detection | Migrate to ATG thresholds and direction checks. |
| Cross and half-cross | Migrate to ATG `cross.c` + `Half_check.c`. |
| Circle and patching | Migrate to ATG `circle.c` + `Patching_Line.c`, preserving ATG enum order inside the ATG layer. |
| Y-road, ramp, road classification | Keep source available; connect after the main line/cross/circle path is stable. |

## What Does Not Migrate

| Area | Reason |
| --- | --- |
| TC264 motor, servo, ADRC, PID, key, TFT, flash, UART, and sensor drivers | Hardware and control loop differ from LS2K. |
| TC264 direct actuator output | Current car uses LS2K differential `guide_error -> yaw_cmd -> motor duty`. |
| A second production IPM truth source | Current production IPM remains the generated `camera_param.c` style map contract unless this branch explicitly changes that after validation. |

## Current Migration Order

1. Preserve `port/autop-direct-reference-control` as the pushed RT1064 baseline.
2. Build this branch as `port/atg2022-reference-control`.
3. Copy ATG source into `atg_reference/`.
4. Create a minimal ATG port layer that compiles host-side without TC264 drivers.
5. Switch `code/tracking` from `autop_reference` to `atg_reference` only after the ATG step function can process a 160x120 gray frame.
6. Validate with `git diff --check`, `bash code/test.sh --host`, and targeted offline/analyze frames.

## Current Stage

The branch currently builds the ATG base line-search path:

| Active in build | Status |
| --- | --- |
| `atg_reference/Project/CODE/shy_Image.c` | active |
| `atg_reference/Project/CODE/imgproc.c` | active |
| `atg_reference/Project/CODE/utils.c` | active |
| `atg_reference/port/reference_step.c` | active |
| `code/tracking/atg_reference_mainline.cpp` | active bridge |

Element files such as `cross.c`, `Half_check.c`, `circle.c`, `Patching_Line.c`,
`round.c`, `yroad.c`, and `Ramp.c` are copied but not yet compiled. They should
be enabled one group at a time from the port layer so the copied algorithm files
remain close to the source.
