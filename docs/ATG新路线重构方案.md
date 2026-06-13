# ATG 新路线重构方案

本文用于记录我们后续把当前工程收敛到 ATG 新主线的讨论结论。

核心方向：

- ATG 算法层作为新的视觉与元素识别主线，尽量保持大佬代码原始结构。
- 当前 LS2K 工程继续负责外设、差速控制、上位机、离线调试和部署。
- 中间层只做必要的数据交换，不再维护旧 `runtime_t` 风格的大杂烩状态。

## 意见一：建立单文件外设驱动入口

建立一个外设驱动文件，集中启动摄像头、IMU、编码器、电机、上位机等所有外设。

这个文件参考官方 `Motherboard_Demo` 的写法：在一个清晰入口里初始化设备对象，然后在主循环中按顺序获取当前帧数据、读取反馈、下发输出。

目标是让外设启动和主循环更接近官方 Example 的简单结构，避免把外设初始化、帧采集、控制反馈和显示发送散落在多个运行时状态包装里。

初步形态：

```text
device_runtime_init()
while (1) {
    capture_gray_frame()
    read_encoder_imu_feedback()
    run_atg_reference_step()
    solve_differential_control()
    apply_motor_output()
    send_assistant_frame()
}
```

注意：这里的“单文件”指外设编排入口集中，不表示把底层库或已有驱动实现复制进一个文件。

## 意见二：写入当前外设参数和硬件合同

外设驱动入口建立后，把当前工程里已经验证或正在使用的外设参数写进去，并在代码旁边加清楚注释。

这些参数不是重新设计，而是从现有工程收拢到新的外设入口，避免后续再分散在 `runners.cpp`、`device.cpp`、`drive_output.cpp`、`imu_feedback.cpp` 等多个地方。

初步需要收拢的参数：

```text
camera:
    path   = SMARTCAR_UVC_PATH，默认 /dev/video0
    width  = 160
    height = 120
    fps    = 30

motor:
    left  -> PWM2
    right -> PWM1
    forward direction gpio level = 0
    hardware duty limit = 35%

encoder:
    QUAD1 -> left
    QUAD2 -> right
    left sign  = -1
    right sign = 1

imu:
    gyro raw sysfs device = /sys/bus/iio/devices/iio:device1/
    yaw axis = Y axis
    gyro_raw_to_rad_s comes from control config
    startup bias sampling must stay explicit

assistant:
    enable = SMARTCAR_ASSISTANT && SMARTCAR_VIEWER
    ip     = SMARTCAR_ASSISTANT_IP，默认 192.168.0.100
    port   = SMARTCAR_ASSISTANT_PORT，默认 8086
    div    = SMARTCAR_ASSISTANT_DIV，默认 20
```

注释要求：

- 每个硬件映射旁边都写明“为什么是这个映射”，尤其是 `left -> PWM2`、`right -> PWM1`、`QUAD1 -> left`、`QUAD2 -> right`。
- 编码器符号修正只在外设层做，控制层拿到的左右速度必须已经是“前进为正”。
- PWM 的 35% 硬上限保留在外设层，不能被 YAML 或控制参数放开。
- 摄像头宽高必须继续按 `160x120` 校验，不做隐式 resize。
- IMU 初始化要保留零漂采样说明；如果后续改 IMU 设备号或 yaw 轴，必须在这里改注释和参数。

## 意见四：逐步把现有主循环收敛成 ATG 写法

这一阶段只讨论主循环和算法调用方式，不涉及上位机显示。

目标不是做复杂重构，而是直接模仿 ATG 大佬代码的组织方式：一帧图像进来后，按固定顺序调用 ATG 算法函数，外面只负责准备输入、读取反馈、下发控制。

ATG 原始顺序可以抽象为：

```text
img_raw.data = camera_image
image_handle()
find_corners()
choose_track_type_from_near_lines()
run_atg_elements()
update_distance_counters()
select_work_line()
normalize_selected_line()
check_road()
```

当前工程后续应逐步靠近这个形态：

```text
while (1) {
    capture_gray_frame()
    read_encoder_imu_feedback()

    img_raw.data = gray
    atg_reference_step(encoder_total)

    build_control_input_from_atg()
    solve_differential_control()
    apply_motor_output()
}
```

建议拆成小步骤：

| 步骤 | 当前代码 | 目标形态 | 说明 |
| --- | --- | --- | --- |
| 1 | `live(runtime_t *rt)` 里维护大 `rt` | `runtime_t` 已收薄为 `gray/encoder_total/control_center_x/vision/control` | 保留函数签名，先消掉旧语义字段。 |
| 2 | `tracking_process_frame(rt)` | `atg_reference_process_frame(gray, encoder_total)` | 视觉入口直接表达 ATG 主线，不再伪装成旧 tracking。 |
| 3 | `atg_reference_mainline.cpp` 大量拷贝 ATG 状态到 `runtime_t` | 已改为只导出控制必须的薄结果 | `line_found`、`guide_error`、`vision.mid`；元素诊断由 report/assistant 直读 ATG。 |
| 4 | `solve_control_input_with_feedback(control_input, ...)` | `solve_control_input_with_feedback(control_input, feedback, ...)` | 控制只读当前帧控制输入，不再依赖旧 `track_result_t`。 |
| 5 | `runtime_t` 继续包含旧 seed/trace 字段 | 已删除旧主线残留字段 | `seeds`、`left_trace`、`right_trace`、`cross/ring/zebra`、`track_result_t`、`mid_position`、`width_base` 都不再存在。 |

本阶段先不处理：

- 上位机红/黄/绿线显示。
- report 字段重写。（已完成：输出 `atg_*` 原生键）
- ATG 元素状态的可视化。
- 复杂参数自动调节。

这些等 ATG 主循环语义稳定后再单独处理。

判断本阶段完成的标准：

- 主循环顺序能一眼对应 ATG 每帧顺序。
- ATG 算法内部仍使用自己的全局变量和状态机。
- 外部控制层只拿到必要控制输入，不再依赖旧 `runtime_t.track` 的复杂字段。
- 代码里没有为了兼容旧主线而新增大规模映射。
