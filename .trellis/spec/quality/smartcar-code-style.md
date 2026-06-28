# Smartcar Competition Code Style

> 本项目是智能车比赛代码，不是后端服务、SDK 或大型软件工程。最高目标是快速看懂主链、快速调车、快速定位搜线/补线/元素状态/控制输出。

---

## 1. Mental Model

代码应尽量像原始 ATG / `Cpu0_Main.c` 的比赛程序：

```text
采图
读反馈
图像处理
找角点
元素处理
选线
归一化
控制
下发
打印
```

主线必须直白、可见、少跳转。不要让 wrapper、adapter、getter、snapshot、
mapping、pipeline、scheduler 把当前帧数据流藏起来。

目标链路：

```text
main
  -> live
      -> device_capture_gray
      -> drive_output_read_feedback
      -> vision_step
      -> 直接读取视觉全局结果
      -> make_control_input
      -> solve_control
      -> drive_output_apply
      -> print / assistant
```

避免链路膨胀成：

```text
main -> run_mainline -> live -> tracking_process_frame -> vision_frame
     -> atg_reference_process_frame -> copy_midline -> guide_error wrapper
```

---

## 2. File Roles

### `main.cpp`

只负责读取配置、解析参数、选择运行模式。

允许：

```cpp
load_control_config();
parse_options();
vision_reset();

if(argc == 1) return live(&rt);
if(opt.replay_path) return replay(...);
if(opt.analyze_path) return analyze(...);
```

禁止在 `main.cpp` 里启动摄像头、电机、写视觉算法、处理 ATG 细节，或加只被
`main()` 调用的 `run_mainline()` 空包装。

### `runners.cpp`

`runners.cpp` 是 Linux 版比赛主循环。`live()` 应直接展开：

```text
启动外设
读取实时参数
while(1) {
    采图
    读反馈
    更新里程/陀螺仪
    vision_step
    直接读 rptsn / Guide / cx / cy / circle_type / cross_type
    构造控制输入
    solve_control
    drive_output_apply
    print_live / assistant_tick
}
```

不要把每个阶段拆成 `capture_stage`、`feedback_stage`、`tracking_stage`。
不要把 profile、spin test 等诊断模式塞进 live 主循环。

### `vision_step.c`

`vision_step.c` 是视觉算法主流程，不是 port adapter。它应像原始 ATG 视觉段：

```text
本帧准备
image_handle
find_corners
元素处理
choose_line
norm_line
check_road
```

`vision_step.h` 只保留动作入口和少量直接全局出口：

```c
vision_reset()
vision_step()
vision_set_car_x()
vision_update_circle_heading()
raw_to_ipm()
```

不要新增只读全局的 getter：

```c
vision_selected_line()
vision_ipm_cx()
vision_pixel_per_meter()
vision_element_active()
vision_circle_begin_dist()
line_src()
line_src_id()
```

主链需要这些数据时直接读全局变量。

### `circle.c` / `cross.c` / `Half_check.c` / `road.c` / `imgproc.c`

元素和算法参数靠近算法。圆环 B/C 搜索阈值、十字拐点阈值、补线 dx/dy、
C 点角度阈值等不要搬到 runner 或通用 config。

### `report` / `assistant`

调试旁路不参与主链。允许一个统一 snapshot/view 边界服务 report/assistant，
但不得为了调试反向污染 `vision_step` 或 `runners`。

---

## 3. Parameters And Globals

运行参数集中在 `runners.cpp` 或极薄的本地读取点：

```text
drive_on
fps
period_us
print_div
run_ms
control_ms
car_x
control_center_x
```

算法参数就地，局部数字就局部。不要把 runner 变成算法参数垃圾桶。

原则：

```text
运行参数集中；
算法参数就地；
局部数字就局部；
能全局就全局；
不要为全局变量做 getter 中间层。
```

---

## 4. Function Boundaries

保留明确算法动作函数：

```text
image_handle
find_corners
run_circle
run_cross
check_circle
check_Half
choose_line
norm_line
resample_points
local_angle_points
nms_angle
raw_to_ipm
```

不要为了几行 `if / else` 拆函数：

```text
run_active_element
check_new_element
run_new_element
select_cross_far_line
select_circle_line
selected_line_ok
update_vehicle_ref_ipm
```

判断标准：

```text
控制流优先摊开；
算法动作可以成函数；
重复但语义不同可以复制；
不要为了复用搞 mode 参数；
不要为了名字漂亮多跳一层。
```

---

## 5. Naming And Comments

名字短一点，注释说人话。

偏好：

```text
vision_step
live
cut_half_line
car_x
src
src_id
line_begin
norm_line
choose_line
```

避免：

```text
atg_reference_process_frame
tracking_process_frame
truncate_cross_half_candidate_near_lines
atg_reference_vehicle_raw_ref_x
CIRCLE_FIXED_LEFT_IN_TARGET_RAW_X_OFFSET
```

局部变量可以短：`x`、`y`、`dx`、`dy`、`n`、`id`、`ok`、`cnt`、`src`。

注释偏好中文分区：

```c
/* ================= 实时跑车 ================= */
/* ================= 基础搜线 ================= */
/* ================= 元素处理 ================= */
/* ================= 选线 ================= */
/* ================= 归一化 ================= */
```

注释解释原因，不解释语法。避免 Doxygen 风格大段 `@brief/@return/@note`。

---

## 6. Forbidden Directions

不要引入：

```text
Context
Config
Pipeline
Scheduler
ElementOps
统一 Element 对象
大型状态机框架
通用 point search pipeline
mode 参数大函数
过度 public getter
过度 adapter wrapper
```

不要把智能车比赛代码写成后端服务。

---

## 7. Review Checklist

改代码前后检查：

- `main.cpp` 是否仍只做模式选择？
- `live()` 是否仍能一眼看到采图、反馈、视觉、控制、下发、打印？
- `vision_step.c` 是否仍是视觉主流程，而不是查询接口中心？
- 新函数是否是算法动作，而不是几行控制流包装？
- 主链是否直接读当前帧全局，而不是绕 getter？
- report/assistant 是否仍是旁路，没有反向污染主链？
- 是否新增了 `Pipeline`、`Context`、`Scheduler`、`ElementOps` 这类工程化结构？
- 是否为了“减少重复”引入了 mode 参数或更难读的抽象？
