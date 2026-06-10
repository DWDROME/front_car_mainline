# ATG2022 Reference Source

This directory contains the purchased ATG2022 reference algorithm source used as
the new tracking and element-recognition migration target.

Source root on the local machine:

```text
/mnt/c/Users/ds_ev/Downloads/Compressed/智能车比赛资料v1.2/智能车比赛资料v1.2/ATG2022_Master/ATG2022_Master V1.2
```

Copied source groups:

| Destination | Source | Purpose |
| --- | --- | --- |
| `Project/CODE/` | `CODE/*.c`, `CODE/*.h` selected algorithm files | Line search, perspective helpers, corners, cross, half-cross, circle, patching, y-road, ramp, road classification |
| `Project/USER/` | `USER/Cpu0_Main.c`, `USER/Cpu0_Main.h` | Main-loop evidence and selected-line logic reference |
| `port/` | local files only | LS2K adapter layer, no TC264 peripherals |

Mechanical cleanup already applied after copy:

- CRLF converted to LF.
- Trailing spaces and tabs removed.

The copied algorithm files are otherwise intended to stay close to the source.
Port-specific definitions, hardware replacement, and report bridging belong in
`atg_reference/port/` or `code/tracking/`.
