#include "app/options.hpp"
#include "app/runners.hpp"
#include "core/config.hpp"
#include "tracking/perspective.hpp"
#include "tracking/mainline.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
runtime_t g_rt;

const char *resolve_config_path()
{
    const char *env = std::getenv("FRONT_CAR_CONFIG");
    if(env != nullptr && env[0] != '\0')
    {
        return env;
    }
    return "/root/front_car_mainline.yaml";
}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      命令行调度入口，根据传入参数选择实时/抓图/离线分析/回放等运行模式
//  @return     int          0 表示成功，1 表示参数无效（已打印用法）
//  @note       启动时先读 FRONT_CAR_CONFIG 或 /root/front_car_mainline.yaml；IPM 使用编译进来的静态查表。
//-------------------------------------------------------------------------------------------------------------------
int run_mainline(int argc, char **argv)
{
    if(argc == 2 && (std::strcmp(argv[1], "-h") == 0 || std::strcmp(argv[1], "--help") == 0))
    {
        print_usage(argv[0]);
        return 0;
    }

    load_control_config(resolve_config_path());

    options_t opt = {};
    init_options(&opt);
    parse_options(argc, argv, &opt);

    tracking_reset(&g_rt);
    g_rt.has_matrix = 1;
    std::printf("front_car_mainline: ipm=static table\n");

    if(argc == 1)
    {
        return live(&g_rt);
    }

    if(opt.capture_path != nullptr)
    {
        return capture_frame(&g_rt, opt.capture_path);
    }

    if(opt.analyze_path != nullptr)
    {
        analyze_paths_t p = {
            opt.analyze_path,
            opt.ipm_path,
            opt.report_path,
        };
        return analyze(&g_rt, &p);
    }

    if(opt.replay_path != nullptr)
    {
        return replay(&g_rt, opt.replay_path, opt.replay_count, opt.report_path);
    }

    if(argc == 3 && std::strcmp(argv[1], "--input") == 0)
    {
        return offline(&g_rt, argv[2]);
    }

    print_usage(argv[0]);
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      程序入口，转发到 run_mainline 进行命令行分发
//  @return     int          run_mainline 的返回值
//-------------------------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    return run_mainline(argc, argv);
}
