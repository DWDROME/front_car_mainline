#include "core/config.hpp"

#include <cmath>
#include <cstdio>
#include <fstream>

namespace
{
constexpr const char *kTestConfigPath = "/tmp/front_car_config_parsing_test.yaml";

void write_config(const char *text)
{
    std::ofstream out(kTestConfigPath);
    out << text;
}

void expect_int(const char *name, int actual, int expected, int *failed)
{
    if(actual != expected)
    {
        std::fprintf(stderr, "FAIL: %s actual=%d expected=%d\n", name, actual, expected);
        *failed = 1;
    }
}

void expect_float(const char *name, float actual, float expected, int *failed)
{
    if(std::fabs(actual - expected) > 0.000001F)
    {
        std::fprintf(stderr, "FAIL: %s actual=%f expected=%f\n", name, actual, expected);
        *failed = 1;
    }
}
}

int main()
{
    int failed = 0;

    const control_config_t &defaults = control_config();
    expect_int("default control_period_ms", defaults.control_period_ms, 10, &failed);
    expect_float("default target_rps", defaults.target_rps, 4.0F, &failed);
    expect_float("default outer_kp", defaults.outer_kp, 0.03F, &failed);
    expect_float("default guide_error_bias", defaults.guide_error_bias_deg, 0.0F, &failed);
    expect_int("default max_duty_percent", defaults.max_duty_percent, 35, &failed);

    write_config("control_period_ms: bad\n"
                 "target_rps: nope\n"
                 "outer_kp: nan\n"
                 "guide_error_bias_deg: bad\n"
                 "max_duty_percent: 999999999999999999999\n");
    if(!load_control_config(kTestConfigPath))
    {
        std::fprintf(stderr, "FAIL: invalid-value config file should still load\n");
        failed = 1;
    }
    const control_config_t &after_bad = control_config();
    expect_int("bad int keeps default", after_bad.control_period_ms, 10, &failed);
    expect_float("bad float keeps default", after_bad.target_rps, 4.0F, &failed);
    expect_float("nan keeps default", after_bad.outer_kp, 0.03F, &failed);
    expect_float("bad guide bias keeps default", after_bad.guide_error_bias_deg, 0.0F, &failed);
    expect_int("overflow keeps default", after_bad.max_duty_percent, 35, &failed);

    write_config("control_period_ms: 20\n"
                 "target_rps: 5.5\n"
                 "outer_kp: 0.06\n"
                 "guide_error_bias_deg: 13.0\n"
                 "max_duty_percent: 30\n");
    if(!load_control_config(kTestConfigPath))
    {
        std::fprintf(stderr, "FAIL: valid config file should load\n");
        failed = 1;
    }
    const control_config_t &after_valid = control_config();
    expect_int("valid int applied", after_valid.control_period_ms, 20, &failed);
    expect_float("valid float applied", after_valid.target_rps, 5.5F, &failed);
    expect_float("valid outer_kp applied", after_valid.outer_kp, 0.06F, &failed);
    expect_float("valid guide bias applied", after_valid.guide_error_bias_deg, 13.0F, &failed);
    expect_int("valid max duty applied", after_valid.max_duty_percent, 30, &failed);

    write_config("# inline comments should not become numeric tails\n"
                 "control_period_ms: 15 # ms\n"
                 "target_rps: 4.5 # ordinary speed\n"
                 "outer_kp: 0.04 # visual gain\n"
                 "guide_error_bias_deg: 12.5 # static center calibration\n"
                 "max_duty_percent: 28 # hard yaml cap\n");
    if(!load_control_config(kTestConfigPath))
    {
        std::fprintf(stderr, "FAIL: comment config file should load\n");
        failed = 1;
    }
    const control_config_t &after_comments = control_config();
    expect_int("comment int applied", after_comments.control_period_ms, 15, &failed);
    expect_float("comment float applied", after_comments.target_rps, 4.5F, &failed);
    expect_float("comment outer_kp applied", after_comments.outer_kp, 0.04F, &failed);
    expect_float("comment guide bias applied", after_comments.guide_error_bias_deg, 12.5F, &failed);
    expect_int("comment max duty applied", after_comments.max_duty_percent, 28, &failed);

    write_config("not_a_control_key: 123\n");
    if(!load_control_config(kTestConfigPath))
    {
        std::fprintf(stderr, "FAIL: unknown-key config file should still load\n");
        failed = 1;
    }
    const control_config_t &after_unknown = control_config();
    expect_int("unknown key keeps int", after_unknown.control_period_ms, 15, &failed);
    expect_float("unknown key keeps float", after_unknown.target_rps, 4.5F, &failed);
    expect_float("unknown key keeps outer_kp", after_unknown.outer_kp, 0.04F, &failed);
    expect_float("unknown key keeps guide bias", after_unknown.guide_error_bias_deg, 12.5F, &failed);
    expect_int("unknown key keeps max duty", after_unknown.max_duty_percent, 28, &failed);

    write_config("control_period_ms: 20ms\n"
                 "target_rps: 6.0x\n"
                 "outer_kp: inf\n"
                 "guide_error_bias_deg: nan\n"
                 "max_duty_percent: bad\n");
    if(!load_control_config(kTestConfigPath))
    {
        std::fprintf(stderr, "FAIL: trailing-value config file should still load\n");
        failed = 1;
    }
    const control_config_t &after_trailing = control_config();
    expect_int("bad int keeps previous", after_trailing.control_period_ms, 15, &failed);
    expect_float("trailing float keeps previous", after_trailing.target_rps, 4.5F, &failed);
    expect_float("inf keeps previous", after_trailing.outer_kp, 0.04F, &failed);
    expect_float("bad guide bias keeps previous", after_trailing.guide_error_bias_deg, 12.5F, &failed);
    expect_int("bad max duty keeps previous", after_trailing.max_duty_percent, 28, &failed);

    std::remove(kTestConfigPath);

    if(failed)
    {
        return 1;
    }
    std::printf("config_parsing_test: ok\n");
    return 0;
}
