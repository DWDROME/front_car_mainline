/*
 * runners.cpp —— 应用层运行器：单图分析 / 回放 / 离线 / 实时跑车 / 抓帧
 *
 * 职责：组合摄像头、视觉识别、控制求解、电机输出、打印报告，
 *       从顶层组织一次运行的完整流程。
 *
 * 运行模式（由 main 根据命令行参数选择其一）：
 *   analyze     单帧分析 → 写 IPM 预览 + 报告
 *   replay      同一帧重复跑 N 次 → 写报告
 *   offline     单帧处理（仅输出到终端）
 *   live        实时循环：采图→识别→控制→输出
 *   capture     从摄像头抓一帧存为 PNG
 */

#include "app/runners.hpp"

#include "app/control_input_builder.hpp"
#include "report/options.hpp"
#include "report/report.hpp"
#include "report/assistant.hpp"
#include "core/config.hpp"
#include "core/control.hpp"
#include "drivers/device.hpp"
#include "drivers/drive_output.hpp"
#include "core/perspective.hpp"

extern "C" {
#include "vision_step.h"
#include "headfile.h"
}

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <unistd.h>

#include <opencv2/imgcodecs.hpp>

/* ================= 小工具 ================= */

constexpr double kEncoderCountsPerRev = 1024.0 * 4.0;
constexpr double kAtgEncoderCountsPerMeter = 5800.0;

/** 路径是否非空 */
static int has_path(const char *path)
{
    return path != nullptr && path[0] != '\0';
}

static const char *camera_path_param()
{
    return read_env_text("SMARTCAR_UVC_PATH", kDefaultUvcPath);
}

static int control_center_x_param()
{
    return read_env_int_clamped("SMARTCAR_CONTROL_CENTER_X",
                                kDefaultControlCenterX,
                                0,
                                RAW_W - 1);
}

/** 单调时钟微秒（不随系统时间跳变） */
static uint64_t monotonic_us()
{
    timespec ts = {};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)ts.tv_nsec / 1000ULL;
}

/** 帧内剩余时间 sleep，保持帧率稳定 */
static void sleep_remaining_frame_time(uint64_t t0, int period_us)
{
    if(period_us <= 0)
    {
        return;
    }

    uint64_t now = monotonic_us();
    uint64_t used = now >= t0 ? now - t0 : 0;
    if(used < (uint64_t)period_us)
    {
        usleep((useconds_t)((uint64_t)period_us - used));
    }
}

/** 从全局 rptsn 数组复制中线点到 runtime 结构 */
static void copy_vision_midline(runtime_t *rt)
{
    midline_t *mid = &rt->vision.mid;
    point_t ref = rt->vision.control_ref;
    int last_x = ref.x;
    int last_y = ref.y;
    int dist = 0;

    mid->step = rptsn_num < POINT_MAX ? rptsn_num : POINT_MAX;
    for(int i = 0; i < mid->step; ++i)
    {
        int x = std::clamp((int)std::lround(rptsn[i][0]), 0, IPM_W - 1);
        int y = std::clamp((int)std::lround(rptsn[i][1]), 0, IPM_H - 1);

        mid->pts[i].x = x;
        mid->pts[i].y = y;

        if(i == 0)
        {
            mid->dist[i] = 0;
        }
        else
        {
            double dx = (double)(x - last_x);
            double dy = (double)(y - last_y);
            dist += (int)std::lround(std::hypot(dx, dy));
            mid->dist[i] = dist;
        }

        last_x = x;
        last_y = y;
    }
}

/**
 * 从中线点的前视窗口计算 guide error（度）
 *
 * 流程：
 *   1. 在前视距离附近取一个小窗口（±lookahead/5，最小 4 像素）
 *   2. 若窗口内有有效点 → 均值法计算方向角
 *   3. 若无有效点 → 回退到最近邻单点
 * 角度 = -atan2(dx, dy)，dx 以 cx（图像中心 x）为基准。
 */
static double guide_error_from_midline(const midline_t *mid)
{
    if(mid == nullptr || mid->step <= 0)
    {
        return 0.0;
    }

    int lookahead = control_lookahead_dist_px(pixel_per_meter);
    int window = lookahead / 5;
    if(window < 4)
    {
        window = 4;
    }

    double sum_x = 0.0;
    double sum_y = 0.0;
    int count = 0;
    for(int i = 0; i < mid->step; ++i)
    {
        if(mid->dist[i] < lookahead - window ||
           mid->dist[i] > lookahead + window)
        {
            continue;
        }

        sum_x += (double)mid->pts[i].x;
        sum_y += (double)mid->pts[i].y;
        count++;
    }

    if(count > 0)
    {
        double dx = sum_x / (double)count - (double)cx;
        double dy = (double)cy - sum_y / (double)count + ROAD_HALF_WIDTH * 8.0 / 9.0;
        return -atan2(dx, dy) * 180.0 / 3.14159265358979323846;
    }

    /* 回退：找最接近前视距离的单点 */
    int best = 0;
    int best_err = 1 << 30;
    for(int i = 0; i < mid->step; ++i)
    {
        if(mid->dist[i] <= 0)
        {
            continue;
        }

        int err = mid->dist[i] - lookahead;
        if(err < 0)
        {
            err = -err;
        }
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }

    double dx = (double)mid->pts[best].x - (double)cx;
    double dy = (double)cy - (double)mid->pts[best].y + ROAD_HALF_WIDTH * 8.0 / 9.0;
    return -atan2(dx, dy) * 180.0 / 3.14159265358979323846;
}

/**
 * 将视觉步骤的完整结果复制到 runtime，包括：
 *   - guide_error（含 bias 修正 + 赛道特殊缩放）
 *   - line_found 标志
 *
 * 赛道特殊缩放（经验标定值）：
 *   圆环入 / 圆环出          → ×0.75（削弱视觉误差的陡变）
 *   圆环 RUNNING 阶段        → ×0.81，钳位 ±35°
 */
static int copy_vision_result(runtime_t *rt, int step_ok)
{
    std::memset(&rt->vision, 0, sizeof(rt->vision));
    rt->vision.control_ref.x = std::clamp(rt->control_center_x, 0, RAW_W - 1);
    rt->vision.control_ref.y = START_HIGH;
    rt->vision.line_found = step_ok && rptsn_num > 0 ? 1 : 0;
    if(!rt->vision.line_found)
    {
        return 0;
    }

    copy_vision_midline(rt);
    rt->vision.guide_error =
        guide_error_from_midline(&rt->vision.mid) -
        (double)control_config().guide_error_bias_deg;

    if(road_type == CURVE_NEAR && control_config().curve_entry_bias_deg != 0.0F)
    {
        double curve_sign = pure_angle < 0 ? 1.0 : (pure_angle > 0 ? -1.0 : 0.0);
        rt->vision.guide_error += curve_sign * (double)control_config().curve_entry_bias_deg;
    }
    if((circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_RIGHT_BEGIN) &&
       circle_ref_mode == CIRCLE_REF_IN_C)
    {
        rt->vision.guide_error *= 0.75;
    }
    else if(circle_type == CIRCLE_RIGHT_OUT)
    {
        rt->vision.guide_error *= 0.75;
    }
    else if(circle_type == CIRCLE_LEFT_RUNNING || circle_type == CIRCLE_RIGHT_RUNNING)
    {
        rt->vision.guide_error *= 0.81;
        if(rt->vision.guide_error < -35.0)
        {
            rt->vision.guide_error = -35.0;
        }
        if(rt->vision.guide_error > 35.0)
        {
            rt->vision.guide_error = 35.0;
        }
    }

    return 1;
}

/** 加载一张图片并完成视觉 → 控制全流程，可选打印详细输出 */
static int process_loaded_frame(runtime_t *rt, const char *image_path, int print_detail_enabled)
{
    if(rt == nullptr || !has_path(image_path))
    {
        std::fprintf(stderr, "错误: 图片输入参数无效\n");
        return 0;
    }

    if(!device_load_gray(image_path, rt->gray))
    {
        std::fprintf(stderr, "错误: 图片读取失败: %s\n", image_path);
        return 0;
    }

    rt->gray_valid = 1;
    rt->control_center_x = control_center_x_param();

    int step_ok = vision_step(rt->gray, rt->encoder_total);
    int line_found = copy_vision_result(rt, step_ok);

    control_input_t control_input = control_input_from_current_frame(rt, line_found);
    solve_control_input(&control_input, nullptr, &rt->control);

    if(print_detail_enabled)
    {
        print_detail(rt);
    }
    return 1;
}

/* ================= 单图分析 ================= */

/** 分析模式：处理一幅图像 → 写 IPM 预览 + 分析报告 */
int analyze(runtime_t *rt, const analyze_paths_t *paths)
{
    if(paths == nullptr || !has_path(paths->image_path))
    {
        std::fprintf(stderr, "错误: 单图分析缺少图片路径\n");
        return 1;
    }

    if(!process_loaded_frame(rt, paths->image_path, 1))
    {
        return 1;
    }

    cv::Mat ipm;
    perspective_preview(rt->gray, &ipm);
    if(!ipm.empty() && has_path(paths->ipm_path) && !cv::imwrite(paths->ipm_path, ipm))
    {
        std::fprintf(stderr, "警告: IPM 预览图写入失败: %s\n", paths->ipm_path);
    }

    if(has_path(paths->report_path) && !write_report(rt, paths->report_path))
    {
        std::fprintf(stderr, "警告: 分析报告写入失败: %s\n", paths->report_path);
    }
    return 0;
}

/* ================= 回放 ================= */

/** 回放模式：同一幅图反复跑 count 次，打印每帧回放日志，可选写报告 */
int replay(runtime_t *rt, const char *image_path, int count, const char *report_path)
{
    if(rt == nullptr || !has_path(image_path) || count <= 0)
    {
        std::fprintf(stderr, "错误: 回放参数无效\n");
        return 1;
    }

    for(int frame = 0; frame < count; ++frame)
    {
        if(!process_loaded_frame(rt, image_path, 0))
        {
            return 1;
        }
        print_replay_frame(frame, rt);
    }

    if(has_path(report_path) && !write_report(rt, report_path))
    {
        std::fprintf(stderr, "警告: 回放报告写入失败: %s\n", report_path);
    }
    return 0;
}

/* ================= 离线单图 ================= */

/** 离线模式：处理一张图，结果输出到终端（用于调试单帧） */
int offline(runtime_t *rt, const char *image_path)
{
    if(!process_loaded_frame(rt, image_path, 1))
    {
        return 1;
    }
    return 0;
}

/* ================= 实时跑车 ================= */

/**
 * 实时模式主循环
 *
 * 流程：
 *   1. 启动摄像头 + 电机初始化
 *   2. 循环：采图 → 读反馈（里程/陀螺仪）→ 视觉识别 → 控制求解 → 电机输出
 *   3. 到达 run_ms 上限或手动退出时停车
 */
int live(runtime_t *rt)
{
    if(rt == nullptr)
    {
        std::fprintf(stderr, "错误: live 缺少 runtime\n");
        return 1;
    }

    /* ================= 启动外设 ================= */

    const char *camera_path = camera_path_param();
    const int drive_on = read_env_flag("FRONT_CAR_ENABLE_DRIVE", 0);
    const int process_fps = read_env_int_clamped("FRONT_CAR_PROCESS_FPS", 30, 1, 120);
    const int period_us = 1000000 / process_fps;
    const int print_div = read_env_int_clamped("FRONT_CAR_PRINT_DIV",
                                               kDefaultLivePrintDivider,
                                               1,
                                               10000);
    const int run_ms = read_env_int_clamped("FRONT_CAR_RUN_MS", 0, 0, 60000);
    int control_ms = control_config().control_period_ms;
    if(control_ms < 1)
    {
        std::printf("配置警告: control_period_ms=%d 小于实时范围，改用 1\n", control_ms);
        control_ms = 1;
    }
    if(control_ms > 100)
    {
        std::printf("配置警告: control_period_ms=%d 大于实时范围，改用 100\n", control_ms);
        control_ms = 100;
    }
    rt->control_center_x = control_center_x_param();
    vision_set_car_x((float)read_env_int_clamped("FRONT_CAR_VEHICLE_RAW_REF_X",
                                                 (int)std::lround(control_config().vehicle_raw_ref_x),
                                                 0,
                                                 RAW_W - 1));

    if(!device_open_camera(camera_path))
    {
        std::fprintf(stderr,
                "错误: 摄像头启动失败 path=%s\n",
                camera_path);
        return 1;
    }

    drive_output_init(drive_on);
    assistant_init();

    std::printf("实时: 摄像头=%s 处理fps=%d 电机=%s\n",
           camera_path,
           process_fps,
           drive_on ? "开" : "关");

    /* ================= 主循环 ================= */
    uint32_t frame_id = 0;
    uint64_t start_us = monotonic_us();
    while(1)
    {
        uint64_t t0 = monotonic_us();

        if(run_ms > 0 && t0 - start_us >= (uint64_t)run_ms * 1000ULL)
        {
            drive_output_stop();
            break;
        }

        /* 采图 */
        if(!device_capture_gray(rt->gray))
        {
            std::fprintf(stderr, "警告: 采图失败\n");
            continue;
        }

        /* 读反馈，更新里程和圆环陀螺仪 */
        control_feedback_t fb = {};
        drive_output_read_feedback(&fb, control_ms);
        const int64_t wheel_delta =
            (static_cast<int64_t>(fb.left_speed_count) +
             static_cast<int64_t>(fb.right_speed_count)) / 2;
        if(wheel_delta != 0)
        {
            const double wheel_m = static_cast<double>(wheel_delta) / kEncoderCountsPerRev *
                                   3.14159265358979323846 *
                                   static_cast<double>(control_config().encoder_gear_diameter_m);
            rt->encoder_total += static_cast<int64_t>(
                std::llround(wheel_m * kAtgEncoderCountsPerMeter));
        }
        vision_update_circle_heading((float)fb.actual_yaw_rate_mrad_s / 1000.0F,
                                     fb.period_ms,
                                     fb.actual_yaw_rate_valid);

        /* 视觉识别 */
        rt->gray_valid = 1;
        int step_ok = vision_step(rt->gray, rt->encoder_total);
        int line_found = copy_vision_result(rt, step_ok);

        /* 控制求解（带反馈补偿） */
        control_input_t input = control_input_from_current_frame(rt, line_found);
        solve_control_input(&input, &fb, &rt->control);

        /* 下发执行（最终给到舵机/电机） */
        drive_output_apply(&rt->control);

        /* 打印 */
        print_live(frame_id, rt, print_div);
        assistant_tick(rt, frame_id);
        frame_id++;

        sleep_remaining_frame_time(t0, period_us);
    }
    return 0;
}

/* ================= 抓一帧 ================= */

/** 抓帧模式：打开摄像头抓一帧存为 PNG，然后退出 */
int capture_frame(runtime_t *rt, const char *capture_path)
{
    if(rt == nullptr || !has_path(capture_path))
    {
        std::fprintf(stderr, "错误: 抓帧参数无效\n");
        return 1;
    }

    const char *camera_path = camera_path_param();
    if(!device_open_camera(camera_path))
    {
        std::fprintf(stderr, "错误: 摄像头启动失败\n");
        return 1;
    }
    if(!device_capture_gray(rt->gray))
    {
        std::fprintf(stderr, "错误: 抓帧失败\n");
        return 1;
    }

    cv::Mat img(RAW_H, RAW_W, CV_8UC1, rt->gray[0]);
    if(!cv::imwrite(capture_path, img))
    {
        std::fprintf(stderr, "错误: 抓帧图片写入失败: %s\n", capture_path);
        return 1;
    }
    std::printf("抓帧完成: %s\n", capture_path);
    return 0;
}
