#include "app/options.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
void expect_int(const char *name, int actual, int expected, int *failed)
{
    if(actual != expected)
    {
        std::fprintf(stderr, "FAIL: %s actual=%d expected=%d\n", name, actual, expected);
        *failed = 1;
    }
}

void expect_text(const char *name, const char *actual, const char *expected, int *failed)
{
    if(actual == nullptr || expected == nullptr || std::strcmp(actual, expected) != 0)
    {
        std::fprintf(stderr,
                     "FAIL: %s actual=%s expected=%s\n",
                     name,
                     actual == nullptr ? "<null>" : actual,
                     expected == nullptr ? "<null>" : expected);
        *failed = 1;
    }
}

void expect_null(const char *name, const char *actual, int *failed)
{
    if(actual != nullptr)
    {
        std::fprintf(stderr, "FAIL: %s actual=%s expected=<null>\n", name, actual);
        *failed = 1;
    }
}
}

int main()
{
    int failed = 0;

    options_t opt = {};
    init_options(&opt);
    expect_null("default capture_path", opt.capture_path, &failed);
    expect_null("default input_path", opt.input_path, &failed);
    expect_null("default analyze_path", opt.analyze_path, &failed);
    expect_null("default replay_path", opt.replay_path, &failed);
    expect_text("default ipm_path", opt.ipm_path, default_ipm_path(), &failed);
    expect_text("default report_path", opt.report_path, default_report_path(), &failed);
    expect_int("default replay_count", opt.replay_count, 1, &failed);

    char arg0[] = "front_car_mainline";
    char input_flag[] = "--input";
    char input_path[] = "frame.png";
    char replay_flag[] = "--replay";
    char replay_path[] = "loop.png";
    char replay_count[] = "7";
    char ipm_flag[] = "--ipm";
    char ipm_path[] = "ipm.png";
    char report_flag[] = "--report";
    char report_path[] = "report.txt";
    char *argv[] = {
        arg0,
        input_flag,
        input_path,
        replay_flag,
        replay_path,
        replay_count,
        ipm_flag,
        ipm_path,
        report_flag,
        report_path,
    };
    parse_options(static_cast<int>(sizeof(argv) / sizeof(argv[0])), argv, &opt);
    expect_text("parsed input_path", opt.input_path, input_path, &failed);
    expect_text("parsed replay_path", opt.replay_path, replay_path, &failed);
    expect_int("parsed replay_count", opt.replay_count, 7, &failed);
    expect_text("parsed ipm_path", opt.ipm_path, ipm_path, &failed);
    expect_text("parsed report_path", opt.report_path, report_path, &failed);

    options_t null_argv = {};
    init_options(&null_argv);
    parse_options(3, nullptr, &null_argv);
    expect_null("null argv keeps input null", null_argv.input_path, &failed);
    expect_text("null argv keeps report default", null_argv.report_path, default_report_path(), &failed);

    options_t null_item = {};
    init_options(&null_item);
    char *null_item_argv[] = {arg0, nullptr, input_flag, input_path};
    parse_options(static_cast<int>(sizeof(null_item_argv) / sizeof(null_item_argv[0])),
                  null_item_argv,
                  &null_item);
    expect_text("null argv item skipped", null_item.input_path, input_path, &failed);

    options_t null_value = {};
    init_options(&null_value);
    char empty_value[] = "";
    char *null_value_argv[] = {arg0, input_flag, nullptr, ipm_flag, empty_value};
    parse_options(static_cast<int>(sizeof(null_value_argv) / sizeof(null_value_argv[0])),
                  null_value_argv,
                  &null_value);
    expect_null("null input value ignored", null_value.input_path, &failed);
    expect_text("empty ipm value ignored", null_value.ipm_path, default_ipm_path(), &failed);

    options_t flag_value = {};
    init_options(&flag_value);
    char capture_flag[] = "--capture-frame";
    char report2_path[] = "late_report.txt";
    char *flag_value_argv[] = {
        arg0,
        input_flag,
        replay_flag,
        replay_path,
        ipm_flag,
        ipm_path,
        report_flag,
        report2_path,
        capture_flag,
        report_flag,
    };
    parse_options(static_cast<int>(sizeof(flag_value_argv) / sizeof(flag_value_argv[0])),
                  flag_value_argv,
                  &flag_value);
    expect_null("flag token not input path", flag_value.input_path, &failed);
    expect_null("missing replay count ignored", flag_value.replay_path, &failed);
    expect_text("later report still parsed", flag_value.report_path, report2_path, &failed);
    expect_null("flag token not capture path", flag_value.capture_path, &failed);

    options_t bad_replay = {};
    init_options(&bad_replay);
    char bad_count[] = "bad";
    char *bad_argv[] = {arg0, replay_flag, replay_path, bad_count};
    parse_options(static_cast<int>(sizeof(bad_argv) / sizeof(bad_argv[0])), bad_argv, &bad_replay);
    expect_text("bad replay path still parsed", bad_replay.replay_path, replay_path, &failed);
    expect_int("bad replay count falls back", bad_replay.replay_count, 1, &failed);

    options_t zero_replay = {};
    init_options(&zero_replay);
    char zero_count[] = "0";
    char *zero_argv[] = {arg0, replay_flag, replay_path, zero_count};
    parse_options(static_cast<int>(sizeof(zero_argv) / sizeof(zero_argv[0])), zero_argv, &zero_replay);
    expect_text("zero replay path still parsed", zero_replay.replay_path, replay_path, &failed);
    expect_int("zero replay count falls back", zero_replay.replay_count, 1, &failed);

    options_t negative_replay = {};
    init_options(&negative_replay);
    char negative_count[] = "-3";
    char *negative_argv[] = {arg0, replay_flag, replay_path, negative_count};
    parse_options(static_cast<int>(sizeof(negative_argv) / sizeof(negative_argv[0])),
                  negative_argv,
                  &negative_replay);
    expect_text("negative replay path still parsed", negative_replay.replay_path, replay_path, &failed);
    expect_int("negative replay count falls back", negative_replay.replay_count, 1, &failed);

    unsetenv("FRONT_CAR_TEST_INT");
    expect_int("null env int fallback", read_env_int(nullptr, 42), 42, &failed);
    expect_int("empty env int fallback", read_env_int("", 42), 42, &failed);
    expect_int("unset env int fallback", read_env_int("FRONT_CAR_TEST_INT", 42), 42, &failed);
    setenv("FRONT_CAR_TEST_INT", "17", 1);
    expect_int("valid env int", read_env_int("FRONT_CAR_TEST_INT", 42), 17, &failed);
    setenv("FRONT_CAR_TEST_INT", "17x", 1);
    expect_int("invalid env int fallback", read_env_int("FRONT_CAR_TEST_INT", 42), 42, &failed);
    setenv("FRONT_CAR_TEST_INT", "999999999999999999999", 1);
    expect_int("overflow env int fallback", read_env_int("FRONT_CAR_TEST_INT", 42), 42, &failed);
    setenv("FRONT_CAR_TEST_INT", "-3", 1);
    expect_int("clamped env int", read_env_int_clamped("FRONT_CAR_TEST_INT", 42, 1, 10), 1, &failed);

    unsetenv("FRONT_CAR_TEST_TEXT");
    expect_text("null env text fallback", read_env_text(nullptr, "fallback"), "fallback", &failed);
    expect_text("empty env text fallback", read_env_text("", "fallback"), "fallback", &failed);
    expect_text("unset env text fallback", read_env_text("FRONT_CAR_TEST_TEXT", "fallback"), "fallback", &failed);
    setenv("FRONT_CAR_TEST_TEXT", "", 1);
    expect_text("empty env text fallback", read_env_text("FRONT_CAR_TEST_TEXT", "fallback"), "fallback", &failed);
    setenv("FRONT_CAR_TEST_TEXT", "value", 1);
    expect_text("valid env text", read_env_text("FRONT_CAR_TEST_TEXT", "fallback"), "value", &failed);

    unsetenv("FRONT_CAR_TEST_FLAG");
    expect_int("null flag fallback", read_env_flag(nullptr, 1), 1, &failed);
    expect_int("empty flag fallback", read_env_flag("", 1), 1, &failed);
    expect_int("unset flag fallback", read_env_flag("FRONT_CAR_TEST_FLAG", 1), 1, &failed);
    setenv("FRONT_CAR_TEST_FLAG", "0", 1);
    expect_int("zero flag false", read_env_flag("FRONT_CAR_TEST_FLAG", 1), 0, &failed);
    setenv("FRONT_CAR_TEST_FLAG", "1", 1);
    expect_int("one flag true", read_env_flag("FRONT_CAR_TEST_FLAG", 0), 1, &failed);
    setenv("FRONT_CAR_TEST_FLAG", "false", 1);
    expect_int("false flag false", read_env_flag("FRONT_CAR_TEST_FLAG", 1), 0, &failed);
    setenv("FRONT_CAR_TEST_FLAG", "true", 1);
    expect_int("true flag true", read_env_flag("FRONT_CAR_TEST_FLAG", 0), 1, &failed);
    setenv("FRONT_CAR_TEST_FLAG", "2", 1);
    expect_int("invalid flag fallback", read_env_flag("FRONT_CAR_TEST_FLAG", 1), 1, &failed);
    setenv("FRONT_CAR_TEST_FLAG", "off", 1);
    expect_int("invalid off flag stays fallback false", read_env_flag("FRONT_CAR_TEST_FLAG", 0), 0, &failed);

    unsetenv("FRONT_CAR_TEST_INT");
    unsetenv("FRONT_CAR_TEST_TEXT");
    unsetenv("FRONT_CAR_TEST_FLAG");

    if(failed)
    {
        return 1;
    }
    std::printf("options_parsing_test: ok\n");
    return 0;
}
