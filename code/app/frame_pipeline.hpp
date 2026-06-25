#pragma once

#include "types.hpp"

// path_present, init_frame 定义在 runners.cpp 中，供 frame_pipeline.cpp 和 mode runners 共用。
int path_present(const char *path);
void init_frame(runtime_t *rt);

int process_loaded_frame(runtime_t *rt, const char *image_path, int print_detail_enabled);
int process_frame(runtime_t *rt, const char *image_path);
int process_frame_quiet(runtime_t *rt, const char *image_path);
