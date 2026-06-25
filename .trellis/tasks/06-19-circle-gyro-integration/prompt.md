# 圆环陀螺仪积分辅助 — 实现提示词

## 任务

在 ATG 圆环状态机（`circle.c`）中引入陀螺仪 Z 轴积分（heading），替代 `total_distence` 做圆环阶段判断。

## 项目背景

- 这是一个龙芯 LS2K0300 差速车项目，基于 ATG2022 舵机算法移植
- 圆环状态机在 `atg_reference/Project/CODE/circle.c`，完全靠视觉 + 编码器判断阶段
- 陀螺仪只在 `code/core/control.cpp` 的 yaw-rate 内环里参与控制，圆环不读 IMU 数据
- 当前问题：圆环入环时偏左，可能与纯视觉阶段判断不稳定有关

## 两个参考实现

### 参考 1：ATG 当前实现（`circle.c`）

左圆环各阶段：

| 阶段 | track_type | 进入条件 | 退出条件 |
|------|-----------|---------|---------|
| NONE→BEGIN | TRACK_RIGHT | `Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 25`（连续2帧投票） | - |
| BEGIN→IN | TRACK_LEFT | - | `rpts0s_num < 60 && total_distence > 2000 && have_left_line` |
| IN→RUNNING | TRACK_RIGHT | - | `(rpts1s_num > 25 && none_right_line > 1) \|\| (total_distence > 2000 && rpts0s_num < 60 && rpts1s_num > 25)` |
| RUNNING→OUT | TRACK_LEFT | - | `Lpt1_found && Lpt1_rpts1s_id < 0.7/sample_dist` |
| OUT→END | TRACK_RIGHT | - | `(rpts1s_num > 30 && !Lpt1_found && none_right_line > 1) \|\| total_distence > 4500` |
| END→NONE | TRACK_RIGHT | - | `total_distence >= 7500` |

右圆环对称。

### 参考 2：ittuann/Enterprise_E（第16届智能车全国一等奖第14名）

仓库：https://github.com/ittuann/Enterprise_E（已克隆到 `.reference/ittuann-enterprise-e/`）

说明：Enterprise_E 是摄像头循迹主链，电磁/ELC 只作为辅助判断和保护信号；当前开源仓库明确缺少摄像头核心处理代码。因此这里只借鉴其圆环陀螺积分阈值和元素内固定动作组织方式，不把它当作纯电磁参考实现，也不照搬其入环识别。

陀螺仪积分逻辑（`gyro.c:366-375`）：

```c
void Get_Attitude(void) {
    float Gyro_DeadZone = 0.065f;    // 死区，消除静止漂移
    float Gyro_Rate = 1.1557f;       // 比例系数（换算到 0.1°）
    if ((fabsf(Gyro_Z_FilterLast[0]) - Gyro_DeadZone) > 0.0f) {
        Attitude_Angel_X += Gyro_Z_FilterLast[0];   // 积分
        Attitude_Yaw = (int16)(Gyro_Rate * Attitude_Angel_X);  // 0.1° 单位
    }
}
```

圆环状态机（`control.c:1023-1072`）：

```c
void Gyro_Circle_Control(void) {
    if (circle_flag != 0) {
        Gyro_Integral = 1;
        Attitude_Err = ABS(Attitude_Yaw);  // 取绝对值，左右环通用

        if (circle_flag == 1) {  // 左环
            if (Attitude_Err >= 600)   Gyro_Repair_End_Flag = 1;    // 60° 结束补线
            if (Attitude_Err >= 2000)  Gyro_StartIdOutCir_Flag = 1; // 200° 开始出环识别
            if (Attitude_Err >= 2500)  Gyro_TimeOutCir_Flag = 1;    // 250° 强制出环
            if (Attitude_Err >= 3500)  Gyro_Trans_Flag = 1;         // 350° 开始偏转
            if (Attitude_Err >= 3550)  Gyro_OutCircle_Flag = 1;     // 355° 出环完成
        }
        // 右环阈值相同
    }
}
```

注意：`Attitude_Yaw` 单位是 **0.1°**（600 = 60°，3550 = 355°）。

## 逐阶段对应关系

| ATG 阶段 | ATG 判断依据 | ittuann 对应 | ittuann 判断依据 | 可替代性 |
|----------|-------------|-------------|-----------------|---------|
| NONE→BEGIN | 视觉 L 角点 + 直道 | 入环检测 | 摄像头元素状态，可能结合 ELC 辅助 | **保留 ATG 触发** |
| BEGIN→IN | `total_distence > 2000` + 丢线重获 | 补线结束 | `heading >= 60°` | ✓ 可替代 |
| IN→RUNNING | 丢线计数 + `total_distence > 2000` | 环内运行 | heading 持续 | ✓ 可替代 |
| RUNNING→OUT | 视觉 L 角点靠近 | 开始出环识别 | `heading >= 200°` | ✓ 可替代 |
| OUT→END | 视觉 + `total_distence > 4500` | 强制出环 | `heading >= 250°` | ✓ 可替代 |
| END→NONE | `total_distence >= 7500` | 出环完成 | `heading >= 355°` | ✓ 可替代 |

## 关键约束

1. **保留 ATG 的视觉入环触发**（`check_circle()`），只在触发后用 heading 替代 `total_distence`
2. **保留视觉条件作为 fallback**（双保险 OR 模式）：heading 阈值 OR 视觉条件，任一满足就切换
3. **积分清零时机**：`CIRCLE_LEFT_BEGIN` 或 `CIRCLE_RIGHT_BEGIN` 触发时清零
4. **左右环**：用 `ABS(heading)` 统一处理
5. **单位**：当前 IMU 输出 `gyro_raw_to_rad_s: 0.001277562`，输出是 rad/s，需要积分后换算成角度
6. **死区**：需要加死区消除静止漂移（参考 ittuann 的 `Gyro_DeadZone = 0.065f`）
7. **不修改 `control.cpp` 的 yaw-rate 内环**

## 当前项目 IMU 基础

- 零漂采样：`code/drivers/imu_feedback.cpp`（启动时采样 48 次取均值）
- yaw-rate 反馈：`code/core/control.cpp`（`imu_yaw_feedback_enabled=1`，`max_yaw_rate_correction=0.20`）
- 配置参数：`front_car_mainline.yaml` 中 `gyro_raw_to_rad_s: 0.001277562`

## 实现要求

1. 在 `circle.c` 中新增 `heading` 变量和积分逻辑
2. 在 `check_circle()` 触发 BEGIN 时清零 `heading`
3. 在 `run_circle()` 各阶段用 `heading` 阈值替代 `total_distence`
4. 保留视觉条件作为 fallback（OR 模式）
5. 在 `reference_step.c` 的 `atg_reference_process_frame()` 中每帧调用积分
6. 添加死区处理
7. 入环触发后才开始积分，非圆环状态不积分

## 详细研究文件

- 逐阶段对比：`.trellis/tasks/06-19-circle-gyro-integration/research/circle-stage-comparison.md`
- PRD：`.trellis/tasks/06-19-circle-gyro-integration/prd.md`
- ittuann 源码：`.reference/ittuann-enterprise-e/CODE/control.c` + `gyro.c`
- ATG 圆环源码：`atg_reference/Project/CODE/circle.c`
- 移植胶水层：`atg_reference/port/reference_step.c`
- IMU 驱动：`code/drivers/imu_feedback.cpp`
