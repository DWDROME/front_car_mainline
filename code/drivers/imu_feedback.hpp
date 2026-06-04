#pragma once

struct gyro_sample_t
{
    // 三轴原始值、零漂和差值，直接来自 IIO sysfs raw 数据。
    int raw_x = 0;
    int raw_y = 0;
    int raw_z = 0;
    int bias_x = 0;
    int bias_y = 0;
    int bias_z = 0;
    int delta_x = 0;
    int delta_y = 0;
    int delta_z = 0;

    // 三轴角速度，单位 rad/s。
    double rad_s_x = 0.0;
    double rad_s_y = 0.0;
    double rad_s_z = 0.0;

    // 兼容旧控制入口的单轴字段；当前取 Y 轴作为 yaw-rate 反馈。
    int raw = 0;
    int bias = 0;
    int delta = 0;
    double rad_s = 0.0;
};

//----------------------------------------------------------------------------------------------------------------------
//  @brief      初始化 IMU yaw-rate 反馈
//  @param      raw_to_rad_s  raw count 到 rad/s 的换算比例
//  @return     bool          true 成功 / false 设备初始化、sysfs 打开或零漂采样失败
//  @note       初始化阶段会静置采样零漂；IMU 方向和比例未实车验证前，可在控制配置里关闭反馈内环。
//----------------------------------------------------------------------------------------------------------------------
bool imu_feedback_init(double raw_to_rad_s);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      读取一帧陀螺仪反馈
//  @param      gy    输出三轴和兼容单轴角速度
//  @return     bool  true 成功 / false 未初始化或 sysfs 读取失败
//  @note       gy->rad_s 当前取 Y 轴，drive_output_read_feedback() 会转成 mrad/s 给控制层。
//----------------------------------------------------------------------------------------------------------------------
bool imu_feedback_read(gyro_sample_t *gy);
