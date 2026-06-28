#include "config.hpp"

#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

// 极简手写配置解析器：只认 front_car_mainline.yaml 里 "key: value" 的平铺写法，
// 不支持嵌套/列表/缩进等完整 YAML 语法；'#' 之后视作注释。找不到文件时保留 config.hpp 默认值。

namespace
{

control_config_t g_cfg;

// 去掉字符串首尾空白（空格/制表符/回车/换行）。
std::string trim(const std::string &s)
{
    const auto b = s.find_first_not_of(" \t\r\n");
    if(b == std::string::npos) { return ""; }
    const auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// ==== 控制 YAML 数值解析 ====
bool parse_int_value(const std::string &v, int *out)
{
    if(out == nullptr || v.empty())
    {
        return false;
    }

    errno = 0;
    char *end = nullptr;
    const long parsed = std::strtol(v.c_str(), &end, 10);
    if(end == v.c_str() || *end != '\0' || errno != 0 || parsed < INT_MIN || parsed > INT_MAX)
    {
        return false;
    }

    *out = static_cast<int>(parsed);
    return true;
}

bool parse_float_value(const std::string &v, float *out)
{
    if(out == nullptr || v.empty())
    {
        return false;
    }

    errno = 0;
    char *end = nullptr;
    const float parsed = std::strtof(v.c_str(), &end);
    if(end == v.c_str() || *end != '\0' || errno != 0 || !std::isfinite(parsed))
    {
        return false;
    }

    *out = parsed;
    return true;
}

void warn_bad_value(const char *key, const std::string &v)
{
    std::printf("配置警告: %s='%s' 不是有效数值，保留原值\n", key, v.c_str());
}

bool set_int_field(const std::string &k, const std::string &v, const char *name, int *field)
{
    if(k != name)
    {
        return false;
    }

    int parsed = 0;
    if(!parse_int_value(v, &parsed))
    {
        warn_bad_value(name, v);
        return true;
    }

    *field = parsed;
    return true;
}

bool set_float_field(const std::string &k, const std::string &v, const char *name, float *field)
{
    if(k != name)
    {
        return false;
    }

    float parsed = 0.0F;
    if(!parse_float_value(v, &parsed))
    {
        warn_bad_value(name, v);
        return true;
    }

    *field = parsed;
    return true;
}

// 按 key 把字符串值写入对应配置字段。未知 key 或非法值只打印配置警告、不中断；
// 对应字段保留原值。
void set_field(const std::string &k, const std::string &v)
{
    if(set_int_field(k, v, "control_period_ms", &g_cfg.control_period_ms)) return;
    if(set_float_field(k, v, "target_rps", &g_cfg.target_rps)) return;
    if(set_float_field(k, v, "element_target_rps", &g_cfg.element_target_rps)) return;
    if(set_float_field(k, v, "speed_target_rps", &g_cfg.speed_target_rps)) return;
    if(set_float_field(k, v, "curve_speed_slowdown", &g_cfg.curve_speed_slowdown)) return;
    if(set_float_field(k, v, "left_speed_base_percent", &g_cfg.left_speed_base_percent)) return;
    if(set_float_field(k, v, "right_speed_base_percent", &g_cfg.right_speed_base_percent)) return;
    if(set_float_field(k, v, "left_speed_kp", &g_cfg.left_speed_kp)) return;
    if(set_float_field(k, v, "right_speed_kp", &g_cfg.right_speed_kp)) return;
    if(set_float_field(k, v, "left_speed_ki", &g_cfg.left_speed_ki)) return;
    if(set_float_field(k, v, "right_speed_ki", &g_cfg.right_speed_ki)) return;
    if(set_float_field(k, v, "wheel_track_m", &g_cfg.wheel_track_m)) return;
    if(set_float_field(k, v, "encoder_gear_diameter_m", &g_cfg.encoder_gear_diameter_m)) return;
    if(set_float_field(k, v, "gyro_raw_to_rad_s", &g_cfg.gyro_raw_to_rad_s)) return;
    if(set_int_field(k, v, "imu_yaw_feedback_enabled", &g_cfg.imu_yaw_feedback_enabled)) return;
    if(set_float_field(k, v, "outer_kp", &g_cfg.outer_kp)) return;
    if(set_float_field(k, v, "outer_kd", &g_cfg.outer_kd)) return;
    if(set_float_field(k, v, "outer_sign", &g_cfg.outer_sign)) return;
    if(set_float_field(k, v, "straight_error_threshold", &g_cfg.straight_error_threshold)) return;
    if(set_float_field(k, v, "straight_turn_scale", &g_cfg.straight_turn_scale)) return;
    if(set_float_field(k, v, "max_target_yaw_rate", &g_cfg.max_target_yaw_rate)) return;
    if(set_int_field(k, v, "element_reverse_brake_percent", &g_cfg.element_reverse_brake_percent)) return;
    if(set_float_field(k, v, "yaw_kp", &g_cfg.yaw_kp)) return;
    if(set_float_field(k, v, "yaw_ki", &g_cfg.yaw_ki)) return;
    if(set_float_field(k, v, "max_yaw_rate_correction", &g_cfg.max_yaw_rate_correction)) return;
    if(set_float_field(k, v, "rps_filter_alpha", &g_cfg.rps_filter_alpha)) return;
    if(set_int_field(k, v, "yaw_rate_filter_window", &g_cfg.yaw_rate_filter_window)) return;
    if(set_float_field(k, v, "lookahead_time_s", &g_cfg.lookahead_time_s)) return;
    if(set_float_field(k, v, "vehicle_raw_ref_x", &g_cfg.vehicle_raw_ref_x)) return;
    if(set_float_field(k, v, "guide_error_bias_deg", &g_cfg.guide_error_bias_deg)) return;
    if(set_float_field(k, v, "curve_entry_bias_deg", &g_cfg.curve_entry_bias_deg)) return;
    if(set_int_field(k, v, "max_duty_percent", &g_cfg.max_duty_percent)) return;

    std::printf("配置警告: 未知配置项 '%s'，已忽略\n", k.c_str());
}

// 解析一行配置：先去掉 '#' 注释，再按第一个 ':' 拆成 key/value 并各自 trim，空行或缺冒号直接跳过。
void parse_config_line(std::string line)
{
    const auto hash = line.find('#');
    if(hash != std::string::npos)
    {
        line.erase(hash);
    }
    line = trim(line);
    if(line.empty())
    {
        return;
    }

    const auto colon = line.find(':');
    if(colon == std::string::npos)
    {
        return;
    }

    const std::string k = trim(line.substr(0, colon));
    const std::string v = trim(line.substr(colon + 1));
    if(k.empty() || v.empty())
    {
        return;
    }
    set_field(k, v);
}

} // namespace

bool load_control_config(const char *path)
{
    if(path == nullptr || path[0] == '\0')
    {
        return false;
    }
    std::ifstream input(path);
    if(!input.is_open())
    {
        std::printf("配置警告: 找不到 %s，使用 config.hpp 默认值\n", path);
        return false;
    }

    std::string line;
    while(std::getline(input, line))
    {
        parse_config_line(line);
    }
    std::printf("配置: 已加载 %s\n", path);
    return true;
}

const control_config_t &control_config(void)
{
    return g_cfg;
}

int control_lookahead_dist_px(int pixel_per_meter)
{
    const double circ = 3.14159265358979323846 * static_cast<double>(g_cfg.encoder_gear_diameter_m);
    const double v_mps = static_cast<double>(g_cfg.target_rps) * circ;
    double dist_m = static_cast<double>(g_cfg.lookahead_time_s) * v_mps;

    if(dist_m < 0.20)
    {
        dist_m = 0.20;
    }
    if(dist_m > 0.58)
    {
        dist_m = 0.58;
    }
    return static_cast<int>(std::lround(dist_m * static_cast<double>(pixel_per_meter)));
}
