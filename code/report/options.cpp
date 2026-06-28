#include "report/options.hpp"

#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
// ==== 运行参数数值解析 ====
int parse_int_text(const char *value, int *out)
{
    if(value == nullptr || value[0] == '\0' || out == nullptr)
    {
        return 0;
    }

    errno = 0;
    char *end = nullptr;
    long parsed = std::strtol(value, &end, 10);
    if(end == value || *end != '\0' || errno != 0 || parsed < INT_MIN || parsed > INT_MAX)
    {
        return 0;
    }

    *out = (int)parsed;
    return 1;
}

}

/* ================= 环境变量 ================= */

const char *read_env_text(const char *name, const char *fallback)
{
    if(name == nullptr || name[0] == '\0')
    {
        return fallback;
    }

    const char *val = std::getenv(name);
    return val == nullptr || val[0] == '\0' ? fallback : val;
}

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
        std::printf("环境警告: %s='%s' 不是有效整数，使用默认值\n", name, val);
        return fallback;
    }
    return parsed;
}

int read_env_int_clamped(const char *name, int fallback, int min_value, int max_value)
{
    return std::clamp(read_env_int(name, fallback), min_value, max_value);
}

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
    std::printf("环境警告: %s='%s' 不是有效开关，只接受 0/1/false/true，使用默认值\n", name, val);
    return fallback;
}

/* ================= 命令行参数 ================= */

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
    opt->ipm_path = kDefaultIpmPath;
    opt->report_path = kDefaultReportPath;
    opt->replay_count = 1;
}

int parse_options(int argc, char **argv, options_t *opt)
{
    if(opt == nullptr || argv == nullptr)
    {
        return 0;
    }

    for(int i = 1; i < argc; ++i)
    {
        const char *a = argv[i];
        if(a == nullptr)
        {
            continue;
        }

        const char *v1 = (i + 1 < argc) ? argv[i + 1] : nullptr;
        const char *v2 = (i + 2 < argc) ? argv[i + 2] : nullptr;
        const int v1_ok = v1 != nullptr && v1[0] != '\0' && !(v1[0] == '-' && v1[1] == '-');
        const int v2_ok = v2 != nullptr && v2[0] != '\0' && !(v2[0] == '-' && v2[1] == '-');

        if(std::strcmp(a, "--input") == 0 && v1_ok)
        {
            opt->input_path = argv[++i];
        }
        else if(std::strcmp(a, "--analyze") == 0 && v1_ok)
        {
            opt->analyze_path = argv[++i];
        }
        else if(std::strcmp(a, "--replay") == 0 && v1_ok && v2_ok)
        {
            opt->replay_path = argv[++i];
            int replay_count = 0;
            if(!parse_int_text(argv[i + 1], &replay_count) || replay_count <= 0)
            {
                std::printf("参数错误: 回放次数无效: %s\n", argv[i + 1]);
                return 0;
            }
            opt->replay_count = replay_count;
            ++i;
        }
        else if(std::strcmp(a, "--capture-frame") == 0 && v1_ok)
        {
            opt->capture_path = argv[++i];
        }
        else if(std::strcmp(a, "--ipm") == 0 && v1_ok)
        {
            opt->ipm_path = argv[++i];
        }
        else if(std::strcmp(a, "--report") == 0 && v1_ok)
        {
            opt->report_path = argv[++i];
        }
        else
        {
            std::printf("参数错误: 未知或缺少参数值: %s\n", a);
            return 0;
        }
    }
    return 1;
}

void print_usage(const char *name)
{
    const char *program = name != nullptr && name[0] != '\0' ? name : "front_car_mainline";

    std::printf("用法:\n");
    std::printf("  %s                         # 实时跑车\n", program);
    std::printf("  %s --input image.png        # 离线跑一张图\n", program);
    std::printf("  %s --capture-frame frame.png # 摄像头抓一帧\n", program);
    std::printf("  %s --analyze image.png      # 单图分析，可输出 IPM 和报告\n", program);
    std::printf("  %s --replay image.png count # 同一张图重复回放\n", program);
    std::printf("环境变量:\n");
    std::printf("  FRONT_CAR_CONFIG=/root/front_car_mainline.yaml # 控制参数 yaml\n");
    std::printf("  SMARTCAR_UVC_PATH=/dev/video0  # 摄像头设备\n");
    std::printf("  FRONT_CAR_PROCESS_FPS=120      # 实时视觉处理 fps 上限\n");
    std::printf("  FRONT_CAR_PRINT_DIV=8          # 实时打印分频\n");
    std::printf("  FRONT_CAR_ENABLE_DRIVE=1       # 启用电机输出，默认关闭\n");
    std::printf("  FRONT_CAR_STATE_BEEP=0         # 关闭状态切换蜂鸣\n");
    std::printf("  FRONT_CAR_BEEP_PATH=/dev/zf_gpio_beep # 蜂鸣器设备\n");
    std::printf("  SMARTCAR_CONTROL_CENTER_X=86   # 控制参考中心列\n");
}
