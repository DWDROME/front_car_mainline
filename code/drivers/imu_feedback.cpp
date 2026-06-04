#include "imu_feedback.hpp"

#include "zf_common_typedef.hpp"
#include "zf_device_imu.hpp"
#include "zf_driver_delay.hpp"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

namespace
{
// IIO sysfs 陀螺仪三轴 raw 路径，固定挂在 iio:device1；若板上 IMU 枚举到别的 deviceN，需改这里。
constexpr const char *kGyroXPath = "/sys/bus/iio/devices/iio:device1/in_anglvel_x_raw";
constexpr const char *kGyroYPath = "/sys/bus/iio/devices/iio:device1/in_anglvel_y_raw";
constexpr const char *kGyroZPath = "/sys/bus/iio/devices/iio:device1/in_anglvel_z_raw";
// 静置零漂标定参数：先暖机，再丢弃最前面若干采样，然后取均值作为零漂。
constexpr int kBiasWarmupDelayMs = 100;  // 采零漂前的暖机等待，单位 ms
constexpr int kBiasDiscardCount = 16;    // 丢弃最前面的采样数（剔除上电抖动）
constexpr int kBiasSampleCount = 48;     // 实际参与均值的采样数
constexpr int kBiasSampleDelayMs = 2;    // 相邻采样间隔，单位 ms

zf_device_imu g_imu_dev;
int g_gyro_x_fd = -1;
int g_gyro_y_fd = -1;
int g_gyro_z_fd = -1;
int g_gyro_x_bias = 0;
int g_gyro_y_bias = 0;
int g_gyro_z_bias = 0;
double g_raw_to_rad_s = 0.001064;
bool g_imu_ready = false;

// 从已打开的 sysfs 文件描述符读取一路 int32；每次先 seek 到 0 再读。
bool read_int32_fd(int fd, int *out)
{
    if(fd < 0 || out == nullptr)
    {
        return false;
    }

    char buf[32] = {0};
    lseek(fd, 0, SEEK_SET);
    const ssize_t num = read(fd, buf, sizeof(buf) - 1);
    if(num <= 0)
    {
        return false;
    }

    *out = static_cast<int>(std::strtol(buf, nullptr, 10));
    return true;
}

// IMU 设备类型日志字符串。
const char *imu_type_name(imu_device_type_enum type)
{
    switch(type)
    {
        case DEV_IMU660RA: return "IMU660RA";
        case DEV_IMU660RB: return "IMU660RB";
        case DEV_IMU963RA: return "IMU963RA";
        default: return "NO_FIND";
    }
}

// 关闭三轴陀螺仪 sysfs 文件描述符，并把 fd 重置为 -1。
void close_gyro_files()
{
    if(g_gyro_x_fd >= 0) { close(g_gyro_x_fd); }
    if(g_gyro_y_fd >= 0) { close(g_gyro_y_fd); }
    if(g_gyro_z_fd >= 0) { close(g_gyro_z_fd); }
    g_gyro_x_fd = -1;
    g_gyro_y_fd = -1;
    g_gyro_z_fd = -1;
}

// 静置采样一路陀螺仪零漂：先丢前若干采样，再求均值和极值。
bool sample_bias_fd(int fd, int *bias, int *valid, int *min_value, int *max_value)
{
    if(bias == nullptr || valid == nullptr || min_value == nullptr || max_value == nullptr)
    {
        return false;
    }

    system_delay_ms(kBiasWarmupDelayMs);
    for(int i = 0; i < kBiasDiscardCount; ++i)
    {
        int unused = 0;
        read_int32_fd(fd, &unused);
        system_delay_ms(kBiasSampleDelayMs);
    }

    long long sum = 0;
    int num = 0;
    int min_v = 0;
    int max_v = 0;
    for(int i = 0; i < kBiasSampleCount; ++i)
    {
        int raw = 0;
        if(read_int32_fd(fd, &raw))
        {
            if(num == 0)
            {
                min_v = raw;
                max_v = raw;
            }
            else
            {
                if(raw < min_v) { min_v = raw; }
                if(raw > max_v) { max_v = raw; }
            }
            sum += raw;
            ++num;
        }
        system_delay_ms(kBiasSampleDelayMs);
    }

    if(num <= 0)
    {
        return false;
    }

    *bias = static_cast<int>(sum / num);
    *valid = num;
    *min_value = min_v;
    *max_value = max_v;
    return true;
}
}

// 初始化 IMU、打开三轴 raw sysfs，并采样三轴零漂；gyro_raw_to_rad_s 单位是 rad/s per raw count。
bool imu_feedback_init(double gyro_raw_to_rad_s)
{
    if(g_imu_ready)
    {
        return true;
    }

    const imu_device_type_enum type = g_imu_dev.init();
    if(type == DEV_NO_FIND)
    {
        std::printf("ImuError: device init failed\n");
        return false;
    }

    g_gyro_z_fd = open(kGyroZPath, O_RDONLY);
    g_gyro_x_fd = open(kGyroXPath, O_RDONLY);
    g_gyro_y_fd = open(kGyroYPath, O_RDONLY);
    if(g_gyro_x_fd < 0 || g_gyro_y_fd < 0 || g_gyro_z_fd < 0)
    {
        std::printf("ImuError: open gyro raw files failed errno=%d\n", errno);
        close_gyro_files();
        return false;
    }

    int valid_x = 0;
    int valid_y = 0;
    int valid_z = 0;
    int min_x = 0;
    int min_y = 0;
    int min_z = 0;
    int max_x = 0;
    int max_y = 0;
    int max_z = 0;
    if(!sample_bias_fd(g_gyro_x_fd, &g_gyro_x_bias, &valid_x, &min_x, &max_x) ||
       !sample_bias_fd(g_gyro_y_fd, &g_gyro_y_bias, &valid_y, &min_y, &max_y) ||
       !sample_bias_fd(g_gyro_z_fd, &g_gyro_z_bias, &valid_z, &min_z, &max_z))
    {
        std::printf("ImuError: bias sample failed\n");
        close_gyro_files();
        return false;
    }

    g_raw_to_rad_s = gyro_raw_to_rad_s;
    g_imu_ready = true;
    std::printf("ImuReady: type=%s bias_x=%d bias_y=%d bias_z=%d samples=%d/%d/%d min=%d/%d/%d max=%d/%d/%d scale=%.9f_rad_s_per_count\n",
                imu_type_name(type),
                g_gyro_x_bias,
                g_gyro_y_bias,
                g_gyro_z_bias,
                valid_x,
                valid_y,
                valid_z,
                min_x,
                min_y,
                min_z,
                max_x,
                max_y,
                max_z,
                g_raw_to_rad_s);
    return true;
}

// 读取三轴陀螺仪，扣零漂并换算为 rad/s；兼容字段 raw/bias/delta/rad_s 仍取 Y 轴。
bool imu_feedback_read(gyro_sample_t *sample)
{
    if(!g_imu_ready || sample == nullptr)
    {
        return false;
    }

    int x = 0;
    int y = 0;
    int z = 0;
    if(!read_int32_fd(g_gyro_x_fd, &x) ||
       !read_int32_fd(g_gyro_y_fd, &y) ||
       !read_int32_fd(g_gyro_z_fd, &z))
    {
        return false;
    }

    sample->raw_x = x;
    sample->raw_y = y;
    sample->raw_z = z;
    sample->bias_x = g_gyro_x_bias;
    sample->bias_y = g_gyro_y_bias;
    sample->bias_z = g_gyro_z_bias;
    sample->delta_x = x - g_gyro_x_bias;
    sample->delta_y = y - g_gyro_y_bias;
    sample->delta_z = z - g_gyro_z_bias;
    sample->rad_s_x = static_cast<double>(sample->delta_x) * g_raw_to_rad_s;
    sample->rad_s_y = static_cast<double>(sample->delta_y) * g_raw_to_rad_s;
    sample->rad_s_z = static_cast<double>(sample->delta_z) * g_raw_to_rad_s;

    // 兼容单轴字段：当前车体装配下 yaw 轴对应 IMU 的 Y 轴，故 rad_s 取 Y 轴。
    // 若 IMU 安装方向改变，应改这里选用的轴，而不是在控制层补符号。
    sample->raw = y;
    sample->bias = g_gyro_y_bias;
    sample->delta = sample->delta_y;
    sample->rad_s = sample->rad_s_y;
    return true;
}
