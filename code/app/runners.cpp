#include "app/runners.hpp"

#include "app/assistant.hpp"
#include "app/camera_config.hpp"
#include "app/control_input_builder.hpp"
#include "app/frame_pipeline.hpp"
#include "app/live_profile.hpp"
#include "app/options.hpp"
#include "app/replay_log.hpp"
#include "app/report.hpp"
#include "clip.hpp"
#include "core/config.hpp"
#include "core/control.hpp"
#include "drivers/device.hpp"
#include "drivers/drive_output.hpp"
#include "tracking/atg_reference_mainline.hpp"
#include "tracking/perspective.hpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <unistd.h>

#include <opencv2/imgcodecs.hpp>

extern "C" {
#include "atg_reference_step.h"
#include "headfile.h"
}

// ==== 路径参数检查 ====
int path_present(const char *path)
{
    return path != nullptr && path[0] != '\0';
}

// 每帧识别前写入图像有效标记和本车控制参考中心。
void init_frame(runtime_t *rt)
{
    rt->gray_valid = 1;
    rt->control_center_x = read_env_int_clamped("SMARTCAR_CONTROL_CENTER_X",
                                                default_control_center_x(),
                                                0,
                                                RAW_W - 1);
}

namespace
{
int abs_i_local(int value)
{
    return value < 0 ? -value : value;
}

int sign_i_local(int value)
{
    return value < 0 ? -1 : 1;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      实时主循环的同步发布点：识别/反馈/控制/驱动全部完成后，按分频打印 runtime 快照
//  @return     void
//  @note       这里只做同步点输出，不重新计算 tracking 或 control。
//-------------------------------------------------------------------------------------------------------------------
void publish_completed_live_frame(uint32_t frame_id, const runtime_t *rt, int div, live_profile_t *prof)
{
    // 同步点：识别、反馈读取、控制求解和电机下发都完成后，调试输出只消费这一份 runtime 快照。
    const uint64_t t0 = (prof != nullptr && prof->enabled) ? monotonic_us() : 0;
    print_live(frame_id, rt, div);
    if(prof != nullptr && prof->enabled)
    {
        const uint64_t t1 = monotonic_us();
        profile_add(&prof->print_us, t0, t1);
    }
}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      分析模式：单张图片识别一遍，并按需输出 IPM 预览图和分析报告
//  @return     int          0 成功 / 1 失败（参数缺失或处理失败）
//  @note       只用于离线检查，不进入 drive_output_apply()。
//-------------------------------------------------------------------------------------------------------------------
int analyze(runtime_t *rt, const analyze_paths_t *paths)
{
    if(paths == nullptr || !path_present(paths->image_path))
    {
        std::fprintf(stderr, "ERROR: analyze image path missing\n");
        return 1;
    }

    if(!process_frame(rt, paths->image_path))
    {
        return 1;
    }

    cv::Mat ipm;
    perspective_preview(rt->gray, &ipm);
    if(!ipm.empty() && path_present(paths->ipm_path) && !cv::imwrite(paths->ipm_path, ipm))
    {
        std::fprintf(stderr, "WARN: write ipm failed: %s\n", paths->ipm_path);
    }

    if(path_present(paths->report_path) && !write_report(rt, paths->report_path))
    {
        std::fprintf(stderr, "WARN: write report failed: %s\n", paths->report_path);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      回放模式：对同一张图反复处理 count 次，模拟连续帧并打印每帧摘要
//  @return     int          0 成功 / 1 参数无效或处理失败
//  @note       可观察 cross/ring 跨帧状态推进，但输入图像不变化。
//-------------------------------------------------------------------------------------------------------------------
int replay(runtime_t *rt, const char *image_path, int count, const char *report_path)
{
    if(rt == nullptr || !path_present(image_path) || count <= 0)
    {
        std::fprintf(stderr, "ERROR: replay arguments invalid\n");
        return 1;
    }

    for(int frame = 0; frame < count; ++frame)
    {
        if(!process_frame_quiet(rt, image_path))
        {
            return 1;
        }
        print_replay_frame(frame, rt);
    }

    if(path_present(report_path) && !write_report(rt, report_path))
    {
        std::fprintf(stderr, "WARN: write report failed: %s\n", report_path);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      离线模式：处理单张图片并打印详细信息
//  @return     int          0 成功 / 1 失败
//  @note       只跑 tracking + 无反馈控制，不下发电机。
//-------------------------------------------------------------------------------------------------------------------
int offline(runtime_t *rt, const char *image_path)
{
    if(!process_frame(rt, image_path))
    {
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      实时模式主循环：开摄像头 → 采集 → 读反馈/里程 → ATG识别 → 薄输入控制 → 下发电机 → 同步打印
//  @return     int          摄像头初始化失败时返回 1，正常情况下进入死循环不返回
//  @note       drive 是否真正输出由 FRONT_CAR_ENABLE_DRIVE 控制，默认不开电机。
//-------------------------------------------------------------------------------------------------------------------
int live(runtime_t *rt)
{
    if(rt == nullptr)
    {
        std::fprintf(stderr, "ERROR: live runtime missing\n");
        return 1;
    }

    const camera_options_t camera = read_camera_options();
    int div = read_env_int_clamped("FRONT_CAR_PRINT_DIV", default_live_print_divider(), 1, 10000);
    int drive_enabled = read_env_flag("FRONT_CAR_ENABLE_DRIVE", 0);
    int process_fps = read_env_int_clamped("FRONT_CAR_PROCESS_FPS", camera.fps, 1, 120);
    int run_ms = read_env_int_clamped("FRONT_CAR_RUN_MS", 0, 0, 60000);
    const int spin_yaw_mrad_s = read_env_int("FRONT_CAR_SPIN_YAW_MRAD_S", 0);
    const int spin_angle_deg = read_env_int_clamped("FRONT_CAR_SPIN_ANGLE_DEG", 0, -360, 360);
    const int period_us = frame_period_us_from_fps(process_fps);
    int control_period_ms = live_control_period_ms();
    rt->control_center_x = read_env_int_clamped("SMARTCAR_CONTROL_CENTER_X",
                                                default_control_center_x(),
                                                0,
                                                RAW_W - 1);
    atg_reference_set_vehicle_raw_ref_x(
        static_cast<float>(read_env_int_clamped("FRONT_CAR_VEHICLE_RAW_REF_X",
                                                static_cast<int>(std::lround(control_config().vehicle_raw_ref_x)),
                                                0,
                                                MT9V03X_W - 1)));
    if(div < 1)
    {
        div = 1;
    }
    live_profile_t prof = {};
    prof.enabled = read_env_flag("FRONT_CAR_PROFILE", 0);
    prof.divider = read_env_int_clamped("FRONT_CAR_PROFILE_DIV", 30, 1, 10000);
    if(!device_open_camera(camera.path, camera.width, camera.height, camera.fps))
    {
        std::fprintf(stderr, "ERROR: camera init failed\n");
        return 1;
    }

    drive_output_init(drive_enabled);
    assistant_init();
    std::printf("front_car_mainline: live %s %dx%d@%d process_fps=%d drive=%s\n",
                camera.path,
                camera.width,
                camera.height,
                camera.fps,
                process_fps,
                drive_enabled ? "on" : "off");
    if(spin_angle_deg != 0 && spin_yaw_mrad_s == 0)
    {
        std::printf("SpinAngleWarn: FRONT_CAR_SPIN_ANGLE_DEG requires FRONT_CAR_SPIN_YAW_MRAD_S\n");
    }
    uint32_t frame_id = 0;
    const uint64_t run_t0 = (run_ms > 0 || spin_angle_deg != 0) ? monotonic_us() : 0;
    double spin_yaw_deg = 0.0;
    const int spin_angle_sign = spin_angle_deg != 0 ? sign_i_local(spin_angle_deg) : 0;
    const int spin_angle_abs = abs_i_local(spin_angle_deg);
    while(1)
    {
        if(run_ms > 0 && monotonic_us() - run_t0 >= static_cast<uint64_t>(run_ms) * 1000ULL)
        {
            drive_output_stop();
            break;
        }
        // 实时主链按真实顺序展开；t0~t6 是 profile 各阶段计时点。
        const uint64_t t0 = (prof.enabled || period_us > 0) ? monotonic_us() : 0;
        // [t0->t1] 采集一帧 RAW_W x RAW_H 灰度
        if(!device_capture_gray(rt->gray))
        {
            std::fprintf(stderr, "WARN: capture failed\n");
            continue;
        }
        const uint64_t t1 = prof.enabled ? monotonic_us() : 0;

        // [t1->t2] 读编码器/IMU 反馈，并把左右编码器均值累加到 ATG 里程输入。
        control_feedback_t fb = {};
        drive_output_read_feedback(&fb, control_period_ms);
        rt->encoder_total += atg_distance_counts_from_encoder_delta(fb);
        update_circle_heading(static_cast<float>(fb.actual_yaw_rate_mrad_s) / 1000.0F,
                              fb.period_ms,
                              fb.actual_yaw_rate_valid);
        if(spin_angle_deg != 0 && spin_yaw_mrad_s != 0 && fb.actual_yaw_rate_valid)
        {
            const double dt_s = fb.period_ms > 0 ? static_cast<double>(fb.period_ms) / 1000.0 : 0.0;
            spin_yaw_deg += static_cast<double>(fb.actual_yaw_rate_mrad_s) / 1000.0 *
                            dt_s * 180.0 / 3.14159265358979323846;
            if(static_cast<double>(spin_angle_sign) * spin_yaw_deg >= static_cast<double>(spin_angle_abs))
            {
                drive_output_stop();
                std::printf("SpinAngleResult: reached=1 target_deg=%d yaw_deg=%.2f elapsed_ms=%llu actual_yaw=%d\n",
                            spin_angle_deg,
                            spin_yaw_deg,
                            static_cast<unsigned long long>((monotonic_us() - run_t0) / 1000ULL),
                            fb.actual_yaw_rate_mrad_s);
                break;
            }
        }
        const uint64_t t2 = prof.enabled ? monotonic_us() : 0;

        // [t2->t3] ATG 视觉识别：image_handle -> find_corners -> elements -> selected line。
        rt->gray_valid = 1;
        const int line_found = tracking_process_frame(rt);
        const uint64_t t3 = prof.enabled ? monotonic_us() : 0;
        // [t3->t4] 闭环控制：当前 ATG 帧 -> 薄控制输入 -> target_yaw -> 左右 duty。
        const control_input_t control_input = control_input_from_current_frame(rt, line_found);
        solve_control_input_with_feedback(&control_input, &fb, &rt->control);
        const uint64_t t4 = prof.enabled ? monotonic_us() : 0;
        // [t4->t5] 下发电机 PWM + 推送上位机显示
        drive_output_apply(&rt->control);
        assistant_tick(rt, frame_id);
        const uint64_t t5 = prof.enabled ? monotonic_us() : 0;
        // [t5->t6] 同步发布点：按分频打印本帧 runtime 快照
        publish_completed_live_frame(frame_id, rt, div, &prof);
        if(prof.enabled)
        {
            const uint64_t t6 = monotonic_us();
            prof.frames++;
            profile_add(&prof.capture_us, t0, t1);
            profile_add(&prof.feedback_us, t1, t2);
            profile_add(&prof.pts_us, t2, t3);
            profile_add(&prof.control_us, t3, t4);
            profile_add(&prof.drive_us, t4, t5);
            profile_add(&prof.total_us, t0, t6);
            profile_report_and_reset(&prof);
        }
        frame_id++;

        sleep_remaining_frame_time(t0, period_us);
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      抓帧模式：打开摄像头采集一帧灰度图并写到指定路径
//  @return     int          0 成功 / 1 失败（摄像头/采集/写文件任一环节失败）
//  @note       只保存 RAW_W x RAW_H 灰度图，不跑 tracking/control。
//-------------------------------------------------------------------------------------------------------------------
int capture_frame(runtime_t *rt, const char *capture_path)
{
    if(rt == nullptr || !path_present(capture_path))
    {
        std::fprintf(stderr, "ERROR: capture arguments invalid\n");
        return 1;
    }

    const camera_options_t camera = read_camera_options();
    if(!device_open_camera(camera.path, camera.width, camera.height, camera.fps))
    {
        std::fprintf(stderr, "ERROR: camera init failed\n");
        return 1;
    }
    if(!device_capture_gray(rt->gray))
    {
        std::fprintf(stderr, "ERROR: capture failed\n");
        return 1;
    }

    cv::Mat img(RAW_H, RAW_W, CV_8UC1, rt->gray[0]);
    if(!cv::imwrite(capture_path, img))
    {
        std::fprintf(stderr, "ERROR: write capture failed: %s\n", capture_path);
        return 1;
    }
    std::printf("Captured frame: %s\n", capture_path);
    return 0;
}
