#include "config.hpp"

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

// 按 key 把字符串值写入对应配置字段：I() 走 atoi 当整型，F() 走 strtof 当浮点。
// 宏里的字段名必须和 control_config_t 成员逐字一致；改了结构体成员名要同步这里。
// 未知 key 只打印 ConfigWarn、不中断：拼错 key 会静默沿用默认值，是调参时的常见陷阱。
void set_field(const std::string &k, const std::string &v)
{
#define I(name) if(k == #name) { g_cfg.name = std::atoi(v.c_str()); return; }
#define F(name) if(k == #name) { g_cfg.name = std::strtof(v.c_str(), nullptr); return; }
    I(control_period_ms)
    F(target_rps)
    F(element_target_rps)
    F(speed_target_rps)
    F(left_speed_base_percent)
    F(right_speed_base_percent)
    F(left_speed_kp)
    F(right_speed_kp)
    F(left_speed_ki)
    F(right_speed_ki)
    F(wheel_track_m)
    F(encoder_gear_diameter_m)
    F(gyro_raw_to_rad_s)
    I(imu_yaw_feedback_enabled)
    F(outer_kp)
    F(outer_kd)
    F(outer_sign)
    F(straight_error_threshold)
    F(straight_turn_scale)
    F(max_target_yaw_rate)
    F(yaw_kp)
    F(yaw_ki)
    F(max_yaw_rate_correction)
    F(rps_filter_alpha)
    I(yaw_rate_filter_window)
    I(max_duty_percent)
#undef I
#undef F
    std::printf("ConfigWarn: unknown key '%s'\n", k.c_str());
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
        std::printf("ConfigWarn: %s not found, using config.hpp defaults\n", path);
        return false;
    }

    std::string line;
    while(std::getline(input, line))
    {
        parse_config_line(line);
    }
    std::printf("ConfigInfo: loaded %s\n", path);
    return true;
}

const control_config_t &control_config()
{
    return g_cfg;
}
