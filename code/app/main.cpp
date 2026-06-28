#include "app/runners.hpp"
#include "core/config.hpp"
#include "report/options.hpp"
#include "vision_step.h"

#include <cstdio>
#include <cstring>

static runtime_t rt;

int main(int argc, char **argv)
{
    const char *prog = "front_car_mainline";

    if(argc > 0 && argv != nullptr && argv[0] != nullptr)
    {
        prog = argv[0];
    }

    /* ================= 读取配置 ================= */
    load_control_config(read_env_text("FRONT_CAR_CONFIG",
                                      "/root/front_car_mainline.yaml"));

    /* ================= 帮助信息 ================= */
    if(argc == 2 && argv != nullptr && argv[1] != nullptr &&
       (std::strcmp(argv[1], "-h") == 0 ||
        std::strcmp(argv[1], "--help") == 0))
    {
        print_usage(prog);
        return 0;
    }

    /* ================= 解析参数 ================= */
    options_t opt = {};
    init_options(&opt);

    if(!parse_options(argc, argv, &opt))
    {
        print_usage(prog);
        return 1;
    }

    /* ================= 初始化视觉主线 ================= */
    std::memset(&rt, 0, sizeof(rt));
    rt.control_center_x = CONTROL_CENTER_X;
    vision_reset();

    /* ================= 实时模式 =================
     * 不带参数时直接上车跑。
     * 摄像头、电机、外设初始化放在 live() 里面。
     */
    if(argc == 1)
    {
        return live(&rt);
    }

    /* ================= 回放模式 ================= */
    if(opt.replay_path != nullptr)
    {
        return replay(&rt, opt.replay_path, opt.replay_count, opt.report_path);
    }

    /* ================= 单图分析 ================= */
    if(opt.analyze_path != nullptr)
    {
        analyze_paths_t p = {
            opt.analyze_path,
            opt.ipm_path,
            opt.report_path,
        };

        return analyze(&rt, &p);
    }

    /* ================= 抓一帧图像 ================= */
    if(opt.capture_path != nullptr)
    {
        return capture_frame(&rt, opt.capture_path);
    }

    /* ================= 离线输入 ================= */
    if(opt.input_path != nullptr)
    {
        return offline(&rt, opt.input_path);
    }

    print_usage(prog);
    return 1;
}
