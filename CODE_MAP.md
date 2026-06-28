# CODE_MAP

这份文件只做仓库路牌：打开项目时先看哪里，哪些目录不是主线。
主目标以 `code/CMakeLists.txt` 里的 `front_car_mainline` 为准。

## 先看主线

入口：

```text
code/app/main.cpp
code/app/runners.cpp
```

`code/app/` 只放主流程入口、调度和控制输入：`main`、`runners`、
`control_input_builder`。摄像头参数、实时运行参数和帧周期计时由
`runners.cpp` 在 live 边界集中处理。

实时处理链：

```text
code/app/runners.cpp
code/app/vision_step.c
code/app/control_input_builder.cpp
code/core/control.cpp
code/drivers/drive_output.cpp
```

编码器/电机当前主线：

```text
code/drivers/drive_output.cpp
code/app/runners.cpp
code/app/vision_step.c
```

## ATG 算法核心

当前参与主目标编译的核心文件在：

```text
code/core/
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

视觉主流程：

```text
code/app/vision_step.c
code/app/vision_step.h
```

`vision_step.c` 是当前比赛视觉一帧主线：采到灰度图后按 ATG 顺序跑
`image_handle()`、`find_corners()`、元素处理、选线和归一化。`runners.cpp`
和 `control_input_builder.cpp` 需要当前视觉结果时，直接读 `rptsn`、`Guide`、
`cx/cy`、`circle_type`、`cross_type` 等 ATG 全局变量；不要再给这些全局变量套
`vision_*` 查询函数。

视觉全局状态：

```text
code/app/vision_globals.c
```

`atg_reference/` 现在只作为原始参考目录，不作为 `front_car_mainline` 的构建输入。
`code/app/headfile.h` 是当前主线可见的 ATG 全局总头，暂时保留 ATG 类型别名、
宏、LCD 空实现和全局 `extern` 声明。`code/port/` 已不再承载当前主线文件。

运行与诊断包装：

```text
code/core/perspective.cpp
code/report/vision_view.cpp
```

诊断、回放摘要、上位机显示和参数解析：

```text
code/report/
```

## 工具和测试

独立 CMake 工具：

```text
code/tools/key_supervisor.cpp
code/test/motor_pulse.cpp
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
docs/archive/source-notes/code-app-main.old.cpp
```

开环电机脉冲诊断已移到 `code/test/motor_pulse.cpp`，由 CMake 单独生成 `motor_pulse` 命令行工具；主线电机输出只走 `code/drivers/drive_output.cpp`。

## 不应进仓库的运行产物

这些路径默认不应和主线代码平级长期保留：

```text
logs/
build-host/
.diag/
.diag.zip
.runtime/
.trellis/.runtime/
.trellis/scripts/common/__pycache__/
```

`code/` 是源码区；`code/test.sh` 会把 CMake 产物放到仓库根目录的
`build/` 和 `build-host/`，不要在 `code/` 下重新生成 `build/` 或
`build-host/`。
临时备份、旧入口快照等不参与当前 CMake 目标的文件也不要留在 `code/app/`
里；需要保留证据时放到 `docs/archive/source-notes/`。

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
