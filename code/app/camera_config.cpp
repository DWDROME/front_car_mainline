#include "app/camera_config.hpp"
#include "app/options.hpp"

camera_options_t read_camera_options()
{
    camera_options_t opt = {
        read_env_text("SMARTCAR_UVC_PATH", default_uvc_path()),
        read_env_int_clamped("SMARTCAR_UVC_WIDTH", default_uvc_width(), 1, 4096),
        read_env_int_clamped("SMARTCAR_UVC_HEIGHT", default_uvc_height(), 1, 4096),
        read_env_int_clamped("SMARTCAR_UVC_FPS", default_uvc_fps(), 1, 240)
    };
    return opt;
}
