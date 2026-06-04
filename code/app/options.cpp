#include "app/options.hpp"

#include "core/control.hpp"
#include "clip.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

namespace
{
constexpr const char *k_default_uvc_path = "/dev/video0";
constexpr int k_default_uvc_width = 160;
constexpr int k_default_uvc_height = 120;
constexpr int k_default_uvc_fps = 30;
constexpr const char *k_default_ipm_path = "/tmp/front_car_ipm.png";
constexpr const char *k_default_report_path = "/tmp/front_car_report.txt";
constexpr int k_default_live_print_divider = 8;
constexpr int k_default_control_center_x = CONTROL_CENTER_X;
}

// 默认 UVC 摄像头设备路径。
const char *default_uvc_path()
{
    return k_default_uvc_path;
}

// 默认 UVC 采集宽度；当前逐飞库实际只按 path 初始化，尺寸在采集阶段校验。
int default_uvc_width()
{
    return k_default_uvc_width;
}

// 默认 UVC 采集高度；tracking 内部要求 RAW_W x RAW_H。
int default_uvc_height()
{
    return k_default_uvc_height;
}

// 默认 UVC 帧率；当前逐飞库版本不在 device_open_camera() 中下发 fps。
int default_uvc_fps()
{
    return k_default_uvc_fps;
}

// 默认 IPM 透视预览图保存路径。
const char *default_ipm_path()
{
    return k_default_ipm_path;
}

// 默认分析报告文本保存路径。
const char *default_report_path()
{
    return k_default_report_path;
}

// 实时模式默认打印分频值，每 N 帧打印一次。
int default_live_print_divider()
{
    return k_default_live_print_divider;
}

// 默认控制基准列；和图像几何中心 MID_X 不一定相同。
int default_control_center_x()
{
    return k_default_control_center_x;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从环境变量读取字符串，未设置或为空时返回 fallback
//  @return     const char*  有效的字符串指针
//  @note       不复制字符串；返回 getenv() 指针或 fallback 指针。
//-------------------------------------------------------------------------------------------------------------------
const char *read_env_text(const char *name, const char *fallback)
{
    const char *val = std::getenv(name);
    return val == nullptr || val[0] == '\0' ? fallback : val;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从环境变量读取整数，未设置或为空时返回 fallback
//  @return     int          解析后的整数
//  @note       使用 atoi()，非法字符串会按 0 处理；调用方需要自己决定是否再限幅。
//-------------------------------------------------------------------------------------------------------------------
int read_env_int(const char *name, int fallback)
{
    const char *val = std::getenv(name);
    return val == nullptr || val[0] == '\0' ? fallback : std::atoi(val);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从环境变量读取整数并按上下限夹取
//  @return     int          夹取后的整数，范围 [min_value, max_value]
//  @note       用于 fps、打印分频等运行参数；不用于控制 yaml 参数。
//-------------------------------------------------------------------------------------------------------------------
int read_env_int_clamped(const char *name, int fallback, int min_value, int max_value)
{
    return clip_i(read_env_int(name, fallback), min_value, max_value);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取环境变量布尔位（'0' 视为 0，其余非空字符视为 1）
//  @return     int          1 启用 / 0 关闭
//  @note       只判断首字符，适合 FRONT_CAR_DISPLAY、SMARTCAR_ASSISTANT 这类开关。
//-------------------------------------------------------------------------------------------------------------------
int read_env_flag(const char *name, int fallback)
{
    const char *val = std::getenv(name);
    return val == nullptr || val[0] == '\0' ? fallback : (val[0] != '0' ? 1 : 0);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      用默认值初始化 options_t 结构体
//  @return     void
//  @note       控制参数不在这里初始化；控制参数走 config.hpp 默认值和 /root/front_car_mainline.yaml。
//-------------------------------------------------------------------------------------------------------------------
void init_options(options_t *opt)
{
    if(opt == nullptr)
    {
        return;
    }

    opt->capture_path = nullptr;
    opt->analyze_path = nullptr;
    opt->replay_path = nullptr;
    opt->ipm_path = k_default_ipm_path;
    opt->report_path = k_default_report_path;
    opt->replay_count = 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      解析命令行参数（--analyze / --replay / --capture-frame / --ipm / --report）并写入 opt
//  @return     void
//  @note       未识别参数保持忽略，真正模式分发在 main.cpp。
//-------------------------------------------------------------------------------------------------------------------
void parse_options(int argc, char **argv, options_t *opt)
{
    if(opt == nullptr)
    {
        return;
    }

    for(int i = 1; i < argc; ++i)
    {
        const char *a = argv[i];
        if(std::strcmp(a, "--analyze") == 0 && i + 1 < argc)
        {
            opt->analyze_path = argv[++i];
        }
        else if(std::strcmp(a, "--replay") == 0 && i + 2 < argc)
        {
            opt->replay_path = argv[++i];
            opt->replay_count = std::max(1, std::atoi(argv[++i]));
        }
        else if(std::strcmp(a, "--capture-frame") == 0 && i + 1 < argc)
        {
            opt->capture_path = argv[++i];
        }
        else if(std::strcmp(a, "--ipm") == 0 && i + 1 < argc)
        {
            opt->ipm_path = argv[++i];
        }
        else if(std::strcmp(a, "--report") == 0 && i + 1 < argc)
        {
            opt->report_path = argv[++i];
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      打印命令行用法与可用环境变量说明
//  @return     void
//  @note       这里只列运行模式和显示/上位机相关环境变量，不列控制 yaml 参数。
//-------------------------------------------------------------------------------------------------------------------
void print_usage(const char *name)
{
    std::printf("Usage:\n");
    std::printf("  %s\n", name);
    std::printf("  %s --input image.png\n", name);
    std::printf("  %s --capture-frame frame.png\n", name);
    std::printf("  %s --analyze image.png\n", name);
    std::printf("  %s --replay image.png count\n", name);
    std::printf("Env:\n");
    std::printf("  FRONT_CAR_DISPLAY=1       # IPS200 debug display, set 0 to disable\n");
    std::printf("  FRONT_CAR_DISPLAY_DIV=8   # update display every N frames\n");
    std::printf("  FRONT_CAR_DISPLAY_RELOAD=1 # reload IPS200 framebuffer driver\n");
    std::printf("  FRONT_CAR_PROCESS_FPS=120 # cap live vision processing rate\n");
    std::printf("  SMARTCAR_ASSISTANT=1      # seekfree assistant stream, set 0 to disable\n");
    std::printf("  SMARTCAR_VIEWER=0         # legacy alias for disabling assistant stream\n");
    std::printf("  SMARTCAR_ASSISTANT_DIV=20 # upper-monitor send divider\n");
    std::printf("  SMARTCAR_ASSISTANT_CONNECT_MS=30 # bounded connect probe before live loop\n");
    std::printf("  SMARTCAR_ASSISTANT_RECONNECT_DIV=30 # reconnect every N frames if disconnected\n");
}
