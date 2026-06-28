#pragma once

#include "types.hpp"

// 命令行和运行模式参数。控制环参数不在这里，控制参数走 config.hpp 和 yaml。
struct options_t
{
    // 抓帧、分析、回放和输出路径。
    const char *capture_path;
    const char *input_path;
    const char *analyze_path;
    const char *replay_path;
    const char *ipm_path;
    const char *report_path;
    int replay_count;
};

// 默认运行参数。
constexpr const char *kDefaultUvcPath = "/dev/video0";
constexpr const char *kDefaultIpmPath = "/tmp/front_car_ipm.png";
constexpr const char *kDefaultReportPath = "/tmp/front_car_report.txt";
constexpr int kDefaultLivePrintDivider = 8;
constexpr int kDefaultControlCenterX = CONTROL_CENTER_X;

// 环境变量读取只用于运行模式、显示、上位机和开关参数；不要把控制 yaml 参数混到这里。
const char *read_env_text(const char *name, const char *fallback);
int read_env_int(const char *name, int fallback);
int read_env_int_clamped(const char *name, int fallback, int min_value, int max_value);
int read_env_flag(const char *name, int fallback);

// 初始化和解析命令行参数，不负责启动任何运行模式。
void init_options(options_t *opt);
int parse_options(int argc, char **argv, options_t *opt);
void print_usage(const char *name);
