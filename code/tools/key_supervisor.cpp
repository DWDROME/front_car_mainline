// key_supervisor：板端独立看门狗小程序，与 front_car_mainline 主程序分开编译运行。
// 轮询 K1/K2/K3 三个物理按键：K1 后台拉起 mainline，K2 停车并杀进程，K3 停车后拍高清照片。
// 通过 system("nohup ... &") 启动 mainline 二进制，不是函数调用；控制参数只走 yaml。
// 约定：按键低电平为按下；蜂鸣时长区分动作；看门狗日志在 /tmp/key_supervisor.log。
#include "zf_driver_gpio.hpp"
#include "zf_driver_pwm.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <fcntl.h>
#include <ctime>
#include <unistd.h>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>

namespace
{
constexpr int k_poll_ms = 20;                 // 按键轮询周期，单位 ms
constexpr int k_debounce_ticks = 3;           // 去抖：连续 3 次状态变化才确认一次边沿
constexpr const char *k_mainline_bin = "/root/front_car_mainline";    // 主程序二进制路径
constexpr const char *k_mainline_log = "/tmp/front_car_mainline.log"; // 主程序日志重定向目标
constexpr const char *k_supervisor_log = "/tmp/key_supervisor.log";   // 看门狗自身日志
constexpr const char *k_photo_dir = "/root/1_photo";                  // K3 抓拍照片目录
constexpr const char *k_photo_device = "/dev/video0";                 // 抓拍用 UVC 设备（独立于主链）
constexpr int k_photo_width = 1280;           // 抓拍分辨率宽（高清，与主链 160x120 灰度链不同）
constexpr int k_photo_height = 720;           // 抓拍分辨率高
constexpr int k_photo_fps = 30;               // 抓拍帧率

zf_driver_gpio key1(ZF_GPIO_KEY_1, O_RDWR);
zf_driver_gpio key2(ZF_GPIO_KEY_2, O_RDWR);
zf_driver_gpio key3(ZF_GPIO_KEY_3, O_RDWR);
zf_driver_gpio beep(ZF_GPIO_BEEP, O_RDWR);
zf_driver_gpio motor_dir_1(ZF_GPIO_MOTOR_1, O_RDWR);
zf_driver_gpio motor_dir_2(ZF_GPIO_MOTOR_2, O_RDWR);
zf_driver_pwm motor_pwm_1(ZF_PWM_MOTOR_1);
zf_driver_pwm motor_pwm_2(ZF_PWM_MOTOR_2);

// 追加一行 supervisor 日志，带时分秒前缀，便于板端确认按键事件。
void append_log(const char *fmt, ...)
{
    FILE *fp = std::fopen(k_supervisor_log, "a");
    if(fp == nullptr)
    {
        return;
    }

    std::time_t now = std::time(nullptr);
    std::tm tm_now = {};
    localtime_r(&now, &tm_now);
    std::fprintf(fp,
                 "[%02d:%02d:%02d] ",
                 tm_now.tm_hour,
                 tm_now.tm_min,
                 tm_now.tm_sec);

    va_list args;
    va_start(args, fmt);
    std::vfprintf(fp, fmt, args);
    va_end(args);
    std::fputc('\n', fp);
    std::fclose(fp);
}

// 按键低电平表示按下。
bool is_pressed(zf_driver_gpio &key)
{
    return !key.get_level();
}

// 执行板端 shell 命令；失败时同时写 stdout 和 supervisor 日志。
int run_shell(const char *cmd)
{
    // ==== shell 命令执行 ====
    if(cmd == nullptr || cmd[0] == '\0')
    {
        append_log("command skipped: empty command");
        return -1;
    }

    const int ok = std::system(cmd);
    if(ok != 0)
    {
        std::printf("command failed(%d): %s\n", ok, cmd);
        append_log("command failed(%d): %s", ok, cmd);
    }
    return ok;
}

// 蜂鸣器短鸣，单位 ms。
void short_beep(int ms)
{
    beep.set_level(1);
    usleep(ms * 1000);
    beep.set_level(0);
}

// key_supervisor 自己的硬停机：清零左右 PWM，并把方向引脚置 0。
void stop_motor_now()
{
    motor_pwm_1.set_duty(0);
    motor_pwm_2.set_duty(0);
    motor_dir_1.set_level(0);
    motor_dir_2.set_level(0);
}

// 停掉当前 front_car_mainline 进程。
void kill_mainline()
{
    run_shell("killall -9 front_car_mainline 2>/dev/null || true");
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      用预置运行环境后台拉起 front_car_mainline，控制参数只走 yaml
//  @return     void
//  @note       这里不再拼 target_rps/outer_kp/yaw_kp 等控制参数；控制参数统一由 yaml 管。
//-------------------------------------------------------------------------------------------------------------------
void start_mainline()
{
    kill_mainline();
    stop_motor_now();

    // ==== mainline 启动命令 ====
    char cmd[1400] = {};
    const int n = std::snprintf(cmd,
                                sizeof(cmd),
                                "SMARTCAR_ASSISTANT=1 "
                                "SMARTCAR_ASSISTANT_IP=192.168.0.100 "
                                "SMARTCAR_ASSISTANT_PORT=8086 "
                                "SMARTCAR_ASSISTANT_CONNECT_MS=30 "
                                "SMARTCAR_ASSISTANT_RECONNECT_DIV=30 "
                                "SMARTCAR_ASSISTANT_DIV=12 "
                                "FRONT_CAR_PROCESS_FPS=120 "
                                "FRONT_CAR_PRINT_DIV=30 "
                                "FRONT_CAR_ENABLE_DRIVE=1 "
                                "nohup %s >%s 2>&1 &",
                                k_mainline_bin,
                                k_mainline_log);
    if(n < 0 || n >= static_cast<int>(sizeof(cmd)))
    {
        append_log("start failed: command truncated");
        return;
    }
    run_shell(cmd);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      直接打开 UVC 摄像头同步拍一张高清图，保存成功后返回 true
//  @return     bool         true 保存成功 / false 打开、取帧或写文件失败
//  @note       K3 抓拍是独立工具动作，会先停 mainline 和电机，图片保存到 /root/1_photo。
//-------------------------------------------------------------------------------------------------------------------
bool capture_photo_once()
{
    kill_mainline();
    stop_motor_now();
    if(run_shell("mkdir -p /root/1_photo") != 0)
    {
        append_log("capture failed: mkdir %s", k_photo_dir);
        return false;
    }

    cv::VideoCapture cap(k_photo_device);
    if(!cap.isOpened())
    {
        append_log("capture failed: open %s", k_photo_device);
        return false;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, k_photo_width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, k_photo_height);
    cap.set(cv::CAP_PROP_FPS, k_photo_fps);

    cv::Mat frame;
    for(int i = 0; i < 5; ++i)
    {
        cap >> frame;
        if(frame.empty())
        {
            usleep(50 * 1000);
        }
    }
    if(frame.empty())
    {
        append_log("capture failed: empty frame");
        return false;
    }

    std::time_t now = std::time(nullptr);
    std::tm tm_now = {};
    localtime_r(&now, &tm_now);
    // ==== 高清抓拍路径 ====
    char path[256] = {};
    const int n = std::snprintf(path,
                                sizeof(path),
                                "%s/front_car_hd_%04d%02d%02d_%02d%02d%02d.png",
                                k_photo_dir,
                                tm_now.tm_year + 1900,
                                tm_now.tm_mon + 1,
                                tm_now.tm_mday,
                                tm_now.tm_hour,
                                tm_now.tm_min,
                                tm_now.tm_sec);
    if(n < 0 || n >= static_cast<int>(sizeof(path)))
    {
        append_log("capture failed: path truncated");
        return false;
    }

    if(!cv::imwrite(path, frame))
    {
        append_log("capture failed: write %s", path);
        return false;
    }

    append_log("capture ok: %s size=%dx%d", path, frame.cols, frame.rows);
    std::printf("K3 capture saved: %s size=%dx%d\n", path, frame.cols, frame.rows);
    return true;
}

struct key_debounce_t
{
    bool last_pressed;
    int ticks;
};

// 连续 k_debounce_ticks 次状态变化后才确认一次按下边沿。
bool pressed_edge(zf_driver_gpio &key, key_debounce_t *st)
{
    const bool now = is_pressed(key);
    if(now == st->last_pressed)
    {
        st->ticks = 0;
        return false;
    }

    ++st->ticks;
    if(st->ticks < k_debounce_ticks)
    {
        return false;
    }

    st->last_pressed = now;
    st->ticks = 0;
    return now;
}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      看门狗程序入口：轮询 K1/K2/K3 三个按键，分别完成启动、停车、抓帧三类动作
//  @return     int          永不返回；保留 0 仅满足 main 签名
//  @note       K1 启动 mainline(鸣 80ms)；K2 停车并杀进程(鸣 180ms)；K3 停车后拍高清图(触发鸣 120ms，成功补 60ms / 失败 240ms)。
//-------------------------------------------------------------------------------------------------------------------
int main()
{
    std::setvbuf(stdout, nullptr, _IOLBF, 0);
    std::setvbuf(stderr, nullptr, _IOLBF, 0);
    std::printf("front_car_mainline key_supervisor: K1=start, K2=stop, K3=capture\n");
    append_log("boot: key_supervisor started");
    beep.set_level(0);
    stop_motor_now();

    key_debounce_t k1 = {is_pressed(key1), 0};
    key_debounce_t k2 = {is_pressed(key2), 0};
    key_debounce_t k3 = {is_pressed(key3), 0};
    append_log("boot: initial key state k1=%d k2=%d k3=%d",
               k1.last_pressed ? 1 : 0,
               k2.last_pressed ? 1 : 0,
               k3.last_pressed ? 1 : 0);

    while(true)
    {
        if(pressed_edge(key1, &k1))
        {
            std::printf("K1 pressed: start front_car_mainline\n");
            append_log("event: K1 pressed -> start mainline");
            short_beep(80);
            start_mainline();
        }
        if(pressed_edge(key2, &k2))
        {
            std::printf("K2 pressed: stop front_car_mainline\n");
            append_log("event: K2 pressed -> stop mainline");
            stop_motor_now();
            kill_mainline();
            short_beep(180);
            stop_motor_now();
        }
        if(pressed_edge(key3, &k3))
        {
            std::printf("K3 pressed: capture HD photo\n");
            append_log("event: K3 pressed -> capture HD photo");
            short_beep(120);
            if(capture_photo_once())
            {
                short_beep(60);
            }
            else
            {
                short_beep(240);
            }
        }
        usleep(k_poll_ms * 1000);
    }
    return 0;
}
