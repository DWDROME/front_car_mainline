# ATG 圆环状态机 vs ittuann 陀螺仪积分方案：逐阶段对比

> ⚠️ **更正（2026-06-19）**：Enterprise_E 不是纯电磁车，而是**摄像头为主 + gyro 圆环 + 电磁辅助**。其摄像头部分**未开源**（`CODE/photo.c:99` `get_mid_line()` 为空），`CODE/control.c:211` `Camera_Process()→get_mid_line(0)` 是主链，`USER/isr.c:206` 每周期 `ELC_Get()/Magnet_Identify()` 是电磁辅助。因此：**可参考其 gyro 圆环阈值（可信、几何量）**；下文凡把入环检测标为"电磁特征"的均为**推测、不可证**（摄像头逻辑不可见），勿据此推断 ATG 的视觉链（cross 远线 / IPM 搜线 / 外扩规则）。详见 memory `atg-circle-heading-thresholds-provenance`。

## 1. ATG 圆环状态机（当前实现）

来源：`atg_reference/Project/CODE/circle.c`

### 左圆环各阶段

| 阶段 | `track_type` | 进入条件 | 退出条件 | 使用的距离/视觉量 |
|------|-------------|---------|---------|-----------------|
| **NONE** | 正常 | - | `check_circle()` 触发 | `Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 25`（连续2帧） |
| **BEGIN** | TRACK_RIGHT | 从 NONE 投票确认 | `rpts0s_num < circle_in_length(60) && total_distence > circle_in_distance(2000) && have_left_line` | `none_left_line`（丢线计数）、`have_left_line`（重获线计数）、`total_distence`（编码器距离） |
| **IN** | TRACK_LEFT | 从 BEGIN 切换 | `(rpts1s_num > 25 && none_right_line > 1) \|\| (total_distence > 2000 && rpts0s_num < 60 && rpts1s_num > 25)` | `none_right_line`（右侧丢线计数）、`total_distence`、`rpts0s_num`（内线长度） |
| **RUNNING** | TRACK_RIGHT | 从 IN 切换 | `Lpt1_found && Lpt1_rpts1s_id < 0.7/sample_dist` | `Lpt1_found`（右侧 L 角点）、`Lpt1_rpts1s_id`（L 角点位置） |
| **OUT** | TRACK_LEFT | 从 RUNNING 切换 | `(rpts1s_num > 30 && !Lpt1_found && none_right_line > 1) \|\| total_distence > 4500` | `none_right_line`、`rpts1s_num`、`total_distence` |
| **END** | TRACK_RIGHT | 从 OUT 切换 | `total_distence >= 7500` | `total_distence`（纯距离门） |

### 右圆环各阶段（对称）

| 阶段 | `track_type` | 进入条件 | 退出条件 |
|------|-------------|---------|---------|
| **BEGIN** | TRACK_LEFT | `!Lpt0_found && Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 25`（连续2帧） | `rpts1s_num < 60 && total_distence > 2000 && have_right_line` |
| **IN** | TRACK_RIGHT | 从 BEGIN | `(rpts0s_num > 25 && none_left_line > 1) \|\| (total_distence > 2000 && rpts1s_num < 60 && rpts0s_num > 25)` |
| **RUNNING** | TRACK_LEFT | 从 IN | `Lpt0_found && Lpt0_rpts0s_id < 0.7/sample_dist` |
| **OUT** | TRACK_RIGHT | 从 RUNNING | `(rpts0s_num > 30 && !Lpt0_found && none_left_line >= 1) \|\| total_distence > 4500` |
| **END** | TRACK_LEFT | 从 OUT | `total_distence >= 4000` |

---

## 2. ittuann 陀螺仪积分方案（参考实现）

来源：`.reference/ittuann-enterprise-e/CODE/control.c` + `gyro.c`

### 陀螺仪积分逻辑

```c
// gyro.c:366-375
void Get_Attitude(void) {
    float Gyro_DeadZone = 0.065f;    // 死区，消除静止漂移
    float Gyro_Rate = 1.1557f;       // 比例系数（单位换算到 0.1°）
    if ((fabsf(Gyro_Z_FilterLast[0]) - Gyro_DeadZone) > 0.0f) {
        Attitude_Angel_X += Gyro_Z_FilterLast[0];   // 积分
        Attitude_Yaw = (int16)(Gyro_Rate * Attitude_Angel_X);  // 换算成 0.1° 单位
    }
}
```

- `Attitude_Yaw` 单位：**0.1°**（600 = 60°，3550 = 355°）
- 积分在每帧控制循环中调用
- 有死区（0.065）消除静止漂移
- 有比例系数（1.1557）做单位换算

### 圆环状态机用 heading 阈值

```c
// control.c:1023-1072
void Gyro_Circle_Control(void) {
    if (circle_flag != 0) {
        Gyro_Integral = 1;                    // 开启积分
        Attitude_Err = ABS(Attitude_Yaw);     // 取绝对值（左右环通用）

        if (circle_flag == 1) {               // 左环
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

### ittuann 的完整状态机

| 阶段 | 触发条件 | heading 阈值 | 动作 |
|------|---------|-------------|------|
| **入环检测** | 电磁特征（内侧横向电感极值） | - | `heading = 0`，开始补线 |
| **补线结束** | `heading >= 60°` | 600 | 停止补线，进入环内 |
| **环内记录** | `100° < heading < 225°` | 1000~2250 | 累加转向 PID 输出，记录环内平均打角 |
| **开始出环识别** | `heading >= 200°` | 2000 | 用摄像头/电感识别出环特征 |
| **强制出环** | `heading >= 250°` | 2500 | 摄像头识别失败时强制出环 |
| **偏转** | `heading >= 350°` | 3500 | 开始偏转 |
| **出环完成** | `heading >= 355°` | 3550 | 清标志位，0.8s 冷却防重复触发 |

---

## 3. 逐阶段对应关系

| ATG 阶段 | ATG 判断依据 | ittuann 对应阶段 | ittuann 判断依据 | 对应关系 |
|----------|-------------|-----------------|-----------------|---------|
| **NONE → BEGIN** | 视觉：单边 L 角点 + 对侧长直道（连续2帧投票） | 入环检测 | 摄像头/电磁（未开源，推测） | ATG 用视觉触发；ittuann 入环机制不可证（摄像头未开源）。本项目保留 ATG 视觉入环 |
| **BEGIN → IN** | `total_distence > 2000` + 丢线后重获线 + 内线长度 < 60 | 补线结束 | `heading >= 60°` | **可替代**：ittuann 用角度，ATG 用距离+视觉。heading 更可靠 |
| **IN → RUNNING** | `none_right_line > 1` + 右线重现，或 `total_distence > 2000` + 内线短 + 右线长 | 环内运行 | `heading >= 60°` 后持续 | **可替代**：ATG 用视觉+距离，ittuann 用角度持续 |
| **RUNNING → OUT** | `Lpt1_found` + L 角点靠近近处 | 开始出环识别 | `heading >= 200°` | **可替代**：ATG 用视觉 L 角点，ittuann 用角度 |
| **OUT → END** | `rpts1s_num > 30` + 右线重现，或 `total_distence > 4500` | 强制出环 | `heading >= 250°` | **可替代**：ATG 用视觉+距离，ittuann 用角度 |
| **END → NONE** | `total_distence >= 7500` | 出环完成 | `heading >= 355°` | **可替代**：ATG 用纯距离，ittuann 用角度 |

---

## 4. 关键差异和风险点

### 4.1 入环触发方式不同

- **ATG**：视觉检测（L 角点 + 直道特征），连续 2 帧投票确认
- **ittuann**：电磁检测（内侧横向电感极值）

**风险**：如果 ATG 的视觉入环触发不准（如第一个开口误触发），heading 积分也会从错误的起点开始。

**建议**：保留 ATG 的视觉入环触发，只在触发后用 heading 替代 `total_distence` 做阶段判断。

### 4.2 积分清零时机

- **ittuann**：入环检测成功时 `heading = 0`
- **ATG 需要**：`CIRCLE_LEFT_BEGIN` 或 `CIRCLE_RIGHT_BEGIN` 触发时清零

**风险**：如果清零时机不对，heading 会累积错误的角度。

### 4.3 左右环符号处理

- **ittuann**：`Attitude_Err = ABS(Attitude_Yaw)`，取绝对值，左右环通用
- **ATG 需要**：左右环分开处理，或者也取绝对值

**建议**：用 `ABS(heading)` 简化处理，和 ittuann 一致。

### 4.4 单位换算

- **ittuann**：`Attitude_Yaw` 单位是 0.1°（600 = 60°）
- **ATG 需要**：需要确认 `gyro_raw_to_rad_s` 的换算关系

**当前项目**：`gyro_raw_to_rad_s: 0.001277562`，输出是 rad/s。需要积分后换算成角度。

### 4.5 死区和滤波

- **ittuann**：有死区（0.065）和比例系数（1.1557）
- **ATG 需要**：需要类似的死区处理，否则静止时积分会漂移

**当前项目**：IMU 零漂采样已在 `imu_feedback.cpp` 实现，但没有死区处理。

### 4.6 环内平均打角记录

- **ittuann**：在 `100° < heading < 225°` 区间累加转向 PID 输出，出环时使用平均值
- **ATG**：没有这个机制

**建议**：可以作为后续优化，先不做。

---

## 5. 实现路径（后续）

如果要在 ATG `circle.c` 中引入 heading：

1. 在 `circle.c` 中新增 `heading` 变量和积分逻辑
2. 在 `check_circle()` 触发 BEGIN 时清零 `heading`
3. 在 `run_circle()` 各阶段用 `heading` 阈值替代 `total_distence`
4. 保留视觉条件作为 fallback（双保险 OR 模式）
5. 在 `reference_step.c` 的 `atg_reference_process_frame()` 中每帧调用积分

需要确认：`gyro_raw_to_rad_s` 的值是否准确，以及是否需要死区处理。
