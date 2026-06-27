# CODE_MAP

这份文件只做仓库路牌：打开项目时先看哪里，哪些目录不是主线。
主目标以 `code/CMakeLists.txt` 里的 `front_car_mainline` 为准。

## 先看主线

入口：

```text
code/app/main.cpp
code/app/runners.cpp
```

实时处理链：

```text
code/app/frame_pipeline.cpp
code/app/control_input_builder.cpp
code/tracking/atg_reference_mainline.cpp
atg_reference/port/reference_step.c
code/core/control.cpp
code/drivers/drive_output.cpp
```

编码器/电机当前主线：

```text
code/drivers/drive_output.cpp
code/app/runners.cpp
code/tracking/atg_reference_mainline.cpp
atg_reference/port/reference_step.c
```

## ATG 算法核心

当前参与主目标编译的核心文件在：

```text
atg_reference/Project/CODE/
```

重点文件：

```text
circle.c
cross.c
Half_check.c
imgproc.c
Patching_Line.c
road.c
round.c
yroad.c
Ramp.c
shy_Image.c
utils.c
```

适配层：

```text
atg_reference/port/reference_step.c
atg_reference/port/reference_globals.c
```

运行包装层：

```text
code/tracking/atg_reference_mainline.cpp
code/tracking/perspective.cpp
```

## 工具和测试

独立 CMake 工具：

```text
code/tools/key_supervisor.cpp
```

host 测试：

```text
code/test/config_parsing_test.cpp
code/test/options_parsing_test.cpp
```

脚本和离线工具：

```text
tools/
```

顶层 `test.sh` 只作为 `code/test.sh` 的短入口保留。`tools/` 是脚本和离线工具入口，不要和 `code/tools/` 的 CMake 工具混成一类。

## 历史参考

这些文件/目录不按当前主线优先阅读：

```text
atg_reference/Project/USER/
atg_reference/Project/CODE/circle.old
atg_reference/Project/CODE/data.c
atg_reference/Project/CODE/data.h
docs/archive/
docs/reference/
.reference/
```

`code/drivers/motor_pulse.cpp` 和 `code/drivers/motor_pulse.hpp` 当前未进主目标，先按旧诊断/候选工具看待，不要当成编码器主线。

## 不应进仓库的运行产物

这些路径默认不应和主线代码平级长期保留：

```text
logs/
build-host/
code/build/
code/build-host/
.diag/
.diag.zip
.runtime/
.trellis/.runtime/
.trellis/scripts/common/__pycache__/
```

日志如果要保留，只保留明确可 replay 的少量样例，并在删除前列出 exact keep/remove 清单。
当前保留的 replay 样例在 `test/replay/live-circle/`。

## 瘦身原则

不要按“没进 `front_car_mainline`”直接删文件。先分类：

```text
A 主目标必需
B 独立工具 target
C host test target
D 原始参考/历史保留
E 运行产物/日志/AI 中间产物
```

删除或移动原文件/目录前，先列清单并确认。
