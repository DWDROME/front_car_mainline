#pragma once

struct camera_options_t
{
    const char *path;
    int width;
    int height;
    int fps;
};

camera_options_t read_camera_options();
