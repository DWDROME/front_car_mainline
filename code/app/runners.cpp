#include "app/runners.hpp"

#include "app/options.hpp"
#include "app/report.hpp"
#include "app/assistant.hpp"
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

namespace
{
constexpr double kEncoderCountsPerRev = 1024.0 * 4.0;
constexpr double kAtgEncoderCountsPerMeter = 5800.0;
constexpr int kCrossHalfRelayDefaultMs = 500;
constexpr int kCrossHalfRelayMaxMs = 3000;
// 半十字无线 relay 只放在 runner/control 边界；ATG tracking 仍然报告本帧无线。
int g_cross_half_relay_frames;
int g_cross_half_relay_timeout_reported;

struct live_profile_t
{
    int enabled;
    int divider;
    uint32_t frames;
    uint64_t total_us;
    uint64_t capture_us;
    uint64_t pts_us;
    uint64_t feedback_us;
    uint64_t control_us;
    uint64_t drive_us;
    uint64_t print_us;
};

struct camera_options_t
{
    const char *path;
    int width;
    int height;
    int fps;
};

int abs_i_local(int value)
{
    return value < 0 ? -value : value;
}

int sign_i_local(int value)
{
    return value < 0 ? -1 : 1;
}

int64_t atg_distance_counts_from_encoder_delta(const control_feedback_t &fb)
{
    const int64_t wheel_delta = (static_cast<int64_t>(fb.left_speed_count) +
                                 static_cast<int64_t>(fb.right_speed_count)) / 2;
    if(wheel_delta == 0)
    {
        return 0;
    }

    const control_config_t &c = control_config();
    const double wheel_m = static_cast<double>(wheel_delta) / kEncoderCountsPerRev *
                           3.14159265358979323846 *
                           static_cast<double>(c.encoder_gear_diameter_m);
    return static_cast<int64_t>(std::llround(wheel_m * kAtgEncoderCountsPerMeter));
}

int cross_half_relay_limit_frames(int period_ms)
{
    const int relay_ms = read_env_int_clamped("FRONT_CAR_CROSS_HALF_RELAY_MS",
                                             kCrossHalfRelayDefaultMs,
                                             0,
                                             kCrossHalfRelayMaxMs);
    if(relay_ms <= 0)
    {
        return 0;
    }
    return (relay_ms + period_ms - 1) / period_ms;
}

void apply_cross_half_relay(control_input_t *input, int line_found)
{
    if(input == nullptr)
    {
        return;
    }
    if(cross_type != CROSS_HALF || line_found)
    {
        g_cross_half_relay_frames = 0;
        g_cross_half_relay_timeout_reported = 0;
        return;
    }

    // ATG 参考车远线短暂丢失时仍会靠惯性往前滚；本差速车无线会立刻停车。
    // 这里只把这个物理前提翻译成一个有时间上限的直行 relay：
    // 不生成线、不复用旧 guide，窗口结束仍无线就恢复停车。
    const int period_ms = clip_i(control_config().control_period_ms, 1, 100);
    const int limit_frames = cross_half_relay_limit_frames(period_ms);
    if(limit_frames <= 0)
    {
        return;
    }

    if(g_cross_half_relay_frames == 0 && !g_cross_half_relay_timeout_reported)
    {
        std::printf("ATGCrossHalfRelay: start limit_frames=%d period_ms=%d\n",
                    limit_frames,
                    period_ms);
    }

    if(g_cross_half_relay_frames >= limit_frames)
    {
        if(!g_cross_half_relay_timeout_reported)
        {
            std::printf("ATGCrossHalfRelay: timeout frames=%d cross_type=%d, stop on no-line\n",
                        g_cross_half_relay_frames,
                        (int)cross_type);
            g_cross_half_relay_timeout_reported = 1;
        }
        return;
    }

    // 真正的“短时低速直行”就是下面几行；前面的计数/上限只防止无限盲走。
    g_cross_half_relay_frames++;
    input->line_found = 1;
    input->stop_line = 0;
    input->element_active = 1;
    input->fixed_yaw_rate_valid = 0;
    input->fixed_yaw_rate_mrad_s = 0;
    input->spin_mode = 0;
    input->guide_error = 0.0;
}

control_input_t control_input_from_current_frame(const runtime_t *rt, int line_found)
{
    control_input_t input = {};
    if(rt == nullptr)
    {
        return input;
    }

    input.line_found = line_found ? 1 : 0;
    input.guide_error = rt->vision.guide_error;
    input.element_active =
        (cross_type != CROSS_NONE ||
         circle_type != CIRCLE_NONE ||
         round_type != ROUND_NONE ||
         yroad_type != YROAD_NONE ||
         ramp_type != RAMP_NONE ||
         garage_type != GARAGE_NONE) ? 1 : 0;
    // ATG2022 当前接入链没有原生停车线状态；不要把旧 zebra 语义伪造成 stop_line。
    input.stop_line = 0;

    apply_cross_half_relay(&input, line_found);

    if(read_env_flag("FRONT_CAR_FORCE_LINE", 0))
    {
        input.line_found = 1;
        input.stop_line = 0;
        input.element_active = 0;
        input.guide_error = 0.0;
    }

    const int fixed_yaw_mrad_s = read_env_int("FRONT_CAR_FIXED_YAW_MRAD_S", 0);
    if(fixed_yaw_mrad_s != 0)
    {
        input.line_found = 1;
        input.stop_line = 0;
        input.element_active = 0;
        input.fixed_yaw_rate_valid = 1;
        input.fixed_yaw_rate_mrad_s = fixed_yaw_mrad_s;
        input.guide_error = 0.0;
    }

    const int spin_yaw_mrad_s = read_env_int("FRONT_CAR_SPIN_YAW_MRAD_S", 0);
    if(spin_yaw_mrad_s != 0)
    {
        input.line_found = 1;
        input.stop_line = 0;
        input.element_active = 0;
        input.fixed_yaw_rate_valid = 1;
        input.fixed_yaw_rate_mrad_s = spin_yaw_mrad_s;
        input.spin_mode = 1;
        input.guide_error = 0.0;
    }
    return input;
}

// ==== 摄像头运行参数 ====
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

// ==== 路径参数检查 ====
int path_present(const char *path)
{
    return path != nullptr && path[0] != '\0';
}

// 实时性能分桶用的单调时钟，单位 us。
uint64_t monotonic_us()
{
    using clock = std::chrono::steady_clock;
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(clock::now().time_since_epoch()).count());
}

// 把一段耗时累加到 profile 分桶；异常时间顺序直接忽略。
void profile_add(uint64_t *bucket, uint64_t t0, uint64_t t1)
{
    if(bucket != nullptr && t1 >= t0)
    {
        *bucket += t1 - t0;
    }
}

// 把累计 us 换算为每帧平均 ms。
double avg_ms(uint64_t us, uint32_t frames)
{
    if(frames == 0U)
    {
        return 0.0;
    }
    return static_cast<double>(us) / static_cast<double>(frames) / 1000.0;
}

// fps 转单帧周期；fps<=0 表示不限速。
int frame_period_us_from_fps(int fps)
{
    if(fps <= 0)
    {
        return 0;
    }
    return 1000000 / fps;
}

// 实时主循环节拍控制，本帧没跑满 period_us 时补 sleep。
void sleep_remaining_frame_time(uint64_t t0, int period_us)
{
    if(period_us <= 0)
    {
        return;
    }

    const uint64_t now = monotonic_us();
    const uint64_t used = now >= t0 ? now - t0 : 0;
    if(used < static_cast<uint64_t>(period_us))
    {
        usleep(static_cast<useconds_t>(period_us - used));
    }
}

// ==== 控制周期边界 ====
int live_control_period_ms()
{
    const int ms = control_config().control_period_ms;
    if(ms < 1)
    {
        std::printf("ConfigWarn: control_period_ms=%d below live range, using 1\n", ms);
        return 1;
    }
    if(ms > 100)
    {
        std::printf("ConfigWarn: control_period_ms=%d above live range, using 100\n", ms);
        return 100;
    }
    return ms;
}

// profile 达到分频后打印各阶段平均耗时并清零。
void profile_report_and_reset(live_profile_t *prof)
{
    if(prof == nullptr || !prof->enabled || prof->frames < static_cast<uint32_t>(prof->divider))
    {
        return;
    }

    const uint32_t num = prof->frames;
    std::printf("profile frames=%u avg_ms total=%.2f capture=%.2f pts=%.2f feedback=%.2f "
                "control=%.2f drive=%.2f print=%.2f\n",
                num,
                avg_ms(prof->total_us, num),
                avg_ms(prof->capture_us, num),
                avg_ms(prof->pts_us, num),
                avg_ms(prof->feedback_us, num),
                avg_ms(prof->control_us, num),
                avg_ms(prof->drive_us, num),
                avg_ms(prof->print_us, num));
    std::fflush(stdout);

    prof->frames = 0;
    prof->total_us = 0;
    prof->capture_us = 0;
    prof->pts_us = 0;
    prof->feedback_us = 0;
    prof->control_us = 0;
    prof->drive_us = 0;
    prof->print_us = 0;
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

// 单帧离线公共流程：读图 -> tracking -> 无反馈控制，按需打印详细信息。
int process_loaded_frame(runtime_t *rt, const char *image_path, int print_detail_enabled)
{
    if(rt == nullptr || !path_present(image_path))
    {
        std::fprintf(stderr, "ERROR: image arguments invalid\n");
        return 0;
    }

    if(!device_load_gray(image_path, rt->gray))
    {
        std::fprintf(stderr, "ERROR: load image failed: %s\n", image_path);
        return 0;
    }

    init_frame(rt);
    const int line_found = tracking_process_frame(rt);
    const control_input_t control_input = control_input_from_current_frame(rt, line_found);
    solve_control_input(&control_input, &rt->control);
    if(print_detail_enabled)
    {
        print_detail(rt);
    }
    return 1;
}

// 单帧离线处理：读图 -> tracking -> 无反馈控制 -> 详细打印。
int process_frame(runtime_t *rt, const char *image_path)
{
    return process_loaded_frame(rt, image_path, 1);
}

// 回放用单帧处理：和 process_frame 相同，但不打印详细信息。
int process_frame_quiet(runtime_t *rt, const char *image_path)
{
    return process_loaded_frame(rt, image_path, 0);
}

// 回放模式每帧单行摘要：只输出 ATG 原生状态和薄控制结果，不再翻译旧 runtime 字段。
void print_replay_frame(int frame, const runtime_t *rt)
{
    point_t m0 = {-1, -1};
    point_t ml = {-1, -1};
    int ml_dist = -1;
    int max_dist = -1;
    int ml_forward = 0;
    const int aim_distance = atg_lookahead_dist_px();
    mid_points_for_report(rt->vision.mid,
                          rt->vision.control_ref.y,
                          aim_distance,
                          &m0,
                          &ml,
                          &ml_dist,
                          &max_dist,
                          &ml_forward);

    std::printf("replay frame=%d line=%d track=%d cross=%d circle=%d round=%d yroad=%d ramp=%d road=%d speed=%d "
                "near=%d/%d raw=%d/%d ipm=%d/%d center=%d/%d sel=%d/%d "
                "l=%d@%d/%d@%d y=%d@%d/%d@%d far_l=%d@%d/%d@%d far_num=%d/%d "
                "straight=%d/%d far_straight=%d/%d conf=%.1f/%.1f/%.1f/%.1f "
                "dist=%d begin=%lld/%lld ramp_dist=%d m0=(%d,%d) ml=(%d,%d) md=%d/%d/%d "
                "cxcy=%.1f,%.1f guide=%.2f atg_guide=%.1f/%.1f/%.1f "
                "duty=%d/%d pwm=PWM2:%d/PWM1:%d motor=2:%d/1:%d\n",
                frame,
                track_line_found(rt),
                track_type,
                cross_type,
                circle_type,
                round_type,
                yroad_type,
                ramp_type,
                road_type,
                speed_type,
                rpts0s_num,
                rpts1s_num,
                ipts0_num,
                ipts1_num,
                rpts0_num,
                rpts1_num,
                rptsc0_num,
                rptsc1_num,
                rpts_num,
                rptsn_num,
                Lpt0_found ? 1 : 0,
                Lpt0_found ? Lpt0_rpts0s_id : -1,
                Lpt1_found ? 1 : 0,
                Lpt1_found ? Lpt1_rpts1s_id : -1,
                Ypt0_found ? 1 : 0,
                Ypt0_found ? Ypt0_rpts0s_id : -1,
                Ypt1_found ? 1 : 0,
                Ypt1_found ? Ypt1_rpts1s_id : -1,
                far_Lpt0_found ? 1 : 0,
                far_Lpt0_found ? far_Lpt0_rpts0s_id : -1,
                far_Lpt1_found ? 1 : 0,
                far_Lpt1_found ? far_Lpt1_rpts1s_id : -1,
                far_rpts0s_num,
                far_rpts1s_num,
                is_straight0 ? 1 : 0,
                is_straight1 ? 1 : 0,
                is_straight_far_0 ? 1 : 0,
                is_straight_far_1 ? 1 : 0,
                conf1_max * 180.0f / 3.14159265358979323846f,
                conf2_max * 180.0f / 3.14159265358979323846f,
                conf3_max * 180.0f / 3.14159265358979323846f,
                conf4_max * 180.0f / 3.14159265358979323846f,
                total_distence,
                (long long)atg_reference_circle_begin_dist(),
                (long long)atg_reference_circle_begin_last_dist(),
                Ramp_total_distence,
                m0.x,
                m0.y,
                ml.x,
                ml.y,
                ml_dist,
                ml_forward,
                max_dist,
                cx,
                cy,
                rt->vision.guide_error,
                Guide,
                Guide_up,
                Guide_up_up,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty,
                rt->control.left_duty,
                rt->control.right_duty);
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
