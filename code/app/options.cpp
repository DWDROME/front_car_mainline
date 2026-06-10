#include "app/options.hpp"

#include "core/control.hpp"
#include "clip.hpp"

#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

// ==== 运行参数数值解析 ====
int parse_int_text(const char *value, int *out)
{
    if(value == nullptr || value[0] == '\0' || out == nullptr)
    {
        return 0;
    }

    errno = 0;
    char *end = nullptr;
    const long parsed = std::strtol(value, &end, 10);
    if(end == value || *end != '\0' || errno != 0 || parsed < INT_MIN || parsed > INT_MAX)
    {
        return 0;
    }

    *out = static_cast<int>(parsed);
    return 1;
}

int read_positive_arg(const char *value, int fallback)
{
    int parsed = 0;
    if(!parse_int_text(value, &parsed) || parsed <= 0)
    {
        return fallback;
    }
    return parsed;
}

int option_value_present(int argc, char **argv, int index)
{
    return argv != nullptr && index < argc && argv[index] != nullptr && argv[index][0] != '\0';
}

int option_value_token(int argc, char **argv, int index)
{
    return option_value_present(argc, argv, index) &&
           !(argv[index][0] == '-' && argv[index][1] == '-');
}
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
    if(name == nullptr || name[0] == '\0')
    {
        return fallback;
    }

    const char *val = std::getenv(name);
    return val == nullptr || val[0] == '\0' ? fallback : val;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      从环境变量读取整数，未设置或为空时返回 fallback
//  @return     int          解析后的整数
//  @note       非法字符串会打印 EnvWarn 并回退到 fallback；调用方需要自己决定是否再限幅。
//-------------------------------------------------------------------------------------------------------------------
int read_env_int(const char *name, int fallback)
{
    if(name == nullptr || name[0] == '\0')
    {
        return fallback;
    }

    const char *val = std::getenv(name);
    if(val == nullptr || val[0] == '\0')
    {
        return fallback;
    }

    int parsed = 0;
    if(!parse_int_text(val, &parsed))
    {
        std::printf("EnvWarn: invalid integer for %s='%s'\n", name, val);
        return fallback;
    }
    return parsed;
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
//  @brief      读取环境变量布尔位，只接受明确的 0/1/false/true
//  @return     int          1 启用 / 0 关闭
//  @note       非法非空字符串会打印 EnvWarn 并回退到 fallback，避免误启用电机或上位机。
//-------------------------------------------------------------------------------------------------------------------
int read_env_flag(const char *name, int fallback)
{
    if(name == nullptr || name[0] == '\0')
    {
        return fallback;
    }

    const char *val = std::getenv(name);
    if(val == nullptr || val[0] == '\0')
    {
        return fallback;
    }
    if(std::strcmp(val, "0") == 0 || std::strcmp(val, "false") == 0)
    {
        return 0;
    }
    if(std::strcmp(val, "1") == 0 || std::strcmp(val, "true") == 0)
    {
        return 1;
    }
    std::printf("EnvWarn: invalid flag for %s='%s'\n", name, val);
    return fallback;
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
    opt->input_path = nullptr;
    opt->analyze_path = nullptr;
    opt->replay_path = nullptr;
    opt->ipm_path = k_default_ipm_path;
    opt->report_path = k_default_report_path;
    opt->replay_count = 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      解析命令行参数（--input / --analyze / --replay / --capture-frame / --ipm / --report）并写入 opt
//  @return     void
//  @note       未识别参数保持忽略，真正模式分发在 main.cpp。
//-------------------------------------------------------------------------------------------------------------------
void parse_options(int argc, char **argv, options_t *opt)
{
    if(opt == nullptr || argv == nullptr)
    {
        return;
    }

    for(int i = 1; i < argc; ++i)
    {
        const char *a = argv[i];
        if(a == nullptr)
        {
            continue;
        }
        if(std::strcmp(a, "--input") == 0 && option_value_token(argc, argv, i + 1))
        {
            opt->input_path = argv[++i];
        }
        else if(std::strcmp(a, "--analyze") == 0 && option_value_token(argc, argv, i + 1))
        {
            opt->analyze_path = argv[++i];
        }
        else if(std::strcmp(a, "--replay") == 0 &&
                option_value_token(argc, argv, i + 1) &&
                option_value_token(argc, argv, i + 2))
        {
            opt->replay_path = argv[++i];
            opt->replay_count = read_positive_arg(argv[++i], 1);
        }
        else if(std::strcmp(a, "--capture-frame") == 0 && option_value_token(argc, argv, i + 1))
        {
            opt->capture_path = argv[++i];
        }
        else if(std::strcmp(a, "--ipm") == 0 && option_value_token(argc, argv, i + 1))
        {
            opt->ipm_path = argv[++i];
        }
        else if(std::strcmp(a, "--report") == 0 && option_value_token(argc, argv, i + 1))
        {
            opt->report_path = argv[++i];
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      打印命令行用法与可用环境变量说明
//  @return     void
//  @note       这里只列运行模式和上位机相关环境变量，不列控制 yaml 参数。
//-------------------------------------------------------------------------------------------------------------------
void print_usage(const char *name)
{
    const char *program = name != nullptr && name[0] != '\0' ? name : "front_car_mainline";

    std::printf("Usage:\n");
    std::printf("  %s\n", program);
    std::printf("  %s --input image.png\n", program);
    std::printf("  %s --capture-frame frame.png\n", program);
    std::printf("  %s --analyze image.png\n", program);
    std::printf("  %s --replay image.png count\n", program);
    std::printf("Env:\n");
    std::printf("  FRONT_CAR_CONFIG=/root/front_car_mainline.yaml # control yaml path\n");
    std::printf("  SMARTCAR_UVC_PATH=/dev/video0  # camera device path\n");
    std::printf("  SMARTCAR_UVC_WIDTH=160         # expected camera width\n");
    std::printf("  SMARTCAR_UVC_HEIGHT=120        # expected camera height\n");
    std::printf("  SMARTCAR_UVC_FPS=30            # camera fps hint\n");
    std::printf("  FRONT_CAR_PROCESS_FPS=120      # cap live vision processing rate\n");
    std::printf("  FRONT_CAR_PRINT_DIV=8          # live log divider\n");
    std::printf("  FRONT_CAR_ENABLE_DRIVE=1       # enable motor output, default off\n");
    std::printf("  FRONT_CAR_PROFILE=1            # enable profile output\n");
    std::printf("  FRONT_CAR_PROFILE_DIV=30       # profile report divider\n");
    std::printf("  FRONT_CAR_STATE_BEEP=0         # disable state-change beep\n");
    std::printf("  FRONT_CAR_BEEP_PATH=/dev/zf_gpio_beep # beep device path\n");
    std::printf("  SMARTCAR_CONTROL_CENTER_X=86   # tracking control center fallback override\n");
    std::printf("  SMARTCAR_ASSISTANT=1           # seekfree assistant stream\n");
    std::printf("  SMARTCAR_VIEWER=0              # legacy alias for disabling assistant stream\n");
    std::printf("  SMARTCAR_ASSISTANT_IP=192.168.0.101 # upper-monitor ip\n");
    std::printf("  SMARTCAR_ASSISTANT_PORT=8086   # upper-monitor port\n");
    std::printf("  SMARTCAR_ASSISTANT_DIV=20      # upper-monitor send divider\n");
    std::printf("  SMARTCAR_ASSISTANT_RECONNECT_DIV=30 # reconnect every N frames if disconnected\n");
}
