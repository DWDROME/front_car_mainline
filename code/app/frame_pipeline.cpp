#include "app/frame_pipeline.hpp"

#include "app/control_input_builder.hpp"
#include "app/report.hpp"
#include "core/control.hpp"
#include "drivers/device.hpp"
#include "tracking/atg_reference_mainline.hpp"

#include <cstdio>

int process_loaded_frame(runtime_t *rt, const char *image_path, int print_detail_enabled)
{
    if(rt == nullptr || !path_present(image_path))
    {
        std::fprintf(stderr, "ERROR: image arguments invalid\n");
        return 0;
    }

    if(!device_load_gray(image_path, rt->gray))
    {
        std::fprintf(stderr, "ERROR: load image failed: %s\n", image_path);
        return 0;
    }

    init_frame(rt);
    const int line_found = tracking_process_frame(rt);
    const control_input_t control_input = control_input_from_current_frame(rt, line_found);
    solve_control_input(&control_input, &rt->control);
    if(print_detail_enabled)
    {
        print_detail(rt);
    }
    return 1;
}

int process_frame(runtime_t *rt, const char *image_path)
{
    return process_loaded_frame(rt, image_path, 1);
}

int process_frame_quiet(runtime_t *rt, const char *image_path)
{
    return process_loaded_frame(rt, image_path, 0);
}
