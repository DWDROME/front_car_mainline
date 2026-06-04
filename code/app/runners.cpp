#include "app/runners.hpp"

#include "app/options.hpp"
#include "app/report.hpp"
#include "app/assistant.hpp"
#include "core/config.hpp"
#include "core/control.hpp"
#include "drivers/device.hpp"
#include "drivers/drive_output.hpp"
#include "tracking/perspective.hpp"
#include "tracking/mainline.hpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <unistd.h>

#include <opencv2/imgcodecs.hpp>

namespace
{
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

// 每帧识别前写入图像有效标记、控制中心和 seed 起搜中心。
void init_frame(runtime_t *rt)
{
    rt->gray_valid = 1;
    rt->control_center_x = read_env_int_clamped("SMARTCAR_CONTROL_CENTER_X",
                                                default_control_center_x(),
                                                0,
                                                RAW_W - 1);
    rt->mid_position = MID_X;
}

// 单帧离线处理：读图 -> tracking -> 无反馈控制 -> 详细打印。
int process_frame(runtime_t *rt, const char *image_path)
{
    if(!device_load_gray(image_path, rt->gray))
    {
        std::fprintf(stderr, "ERROR: load image failed: %s\n", image_path);
        return 0;
    }

    init_frame(rt);
    tracking_process_frame(rt);
    solve_runtime(rt, &rt->control);
    print_detail(rt);
    return 1;
}

// 回放用单帧处理：和 process_frame 相同，但不打印详细信息。
int process_frame_quiet(runtime_t *rt, const char *image_path)
{
    if(!device_load_gray(image_path, rt->gray))
    {
        std::fprintf(stderr, "ERROR: load image failed: %s\n", image_path);
        return 0;
    }

    init_frame(rt);
    tracking_process_frame(rt);
    solve_runtime(rt, &rt->control);
    return 1;
}

// 回放模式每帧单行摘要，主要看元素状态、远线、中线和 reject_reason。
// 字段缩写：far=左/右远线found，far_num=左/右远线点数，far_l=左/右远 L 索引；
//   lb/la=左边界双 L 基点/张开点，rb/ra=右边界同；mid=控制中线点数，guide=预瞄误差。
void print_replay_frame(int frame, const runtime_t *rt)
{
    std::printf("replay frame=%d line=%d ring=%d/%d cross=%d zebra=%d no_line=%d far=%d/%d "
                "far_num=%d/%d far_l=%d/%d "
                "lb=(%d,%d) la=(%d,%d) rb=(%d,%d) ra=(%d,%d) "
                "track=%d mid=%d guide=%.2f reject=%d\n",
                frame,
                track_line_found(rt),
                rt->ring.kind,
                rt->ring.state,
                rt->cross.state,
                rt->zebra.detected,
                rt->cross.not_have_line,
                rt->cross.left_far_found,
                rt->cross.right_far_found,
                rt->cross.left_num,
                rt->cross.right_num,
                rt->cross.left_l,
                rt->cross.right_l,
                rt->track.left.l_pair_base_pt.x,
                rt->track.left.l_pair_base_pt.y,
                rt->track.left.l_pair_open_pt.x,
                rt->track.left.l_pair_open_pt.y,
                rt->track.right.l_pair_base_pt.x,
                rt->track.right.l_pair_base_pt.y,
                rt->track.right.l_pair_open_pt.x,
                rt->track.right.l_pair_open_pt.y,
                rt->track.track_type,
                rt->track.mid.step,
                rt->track.guide_error,
                rt->track.reject_reason);
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
    if((frame_id % static_cast<uint32_t>(div)) == 0U)
    {
        print_live(frame_id, rt);
    }
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
    if(paths == nullptr || paths->image_path == nullptr)
    {
        std::fprintf(stderr, "ERROR: analyze image path missing\n");
        return 1;
    }

    if(!process_frame(rt, paths->image_path))
    {
        return 1;
    }

    cv::Mat ipm;
    perspective_preview(rt->gray, rt->matrix, &ipm);
    if(!ipm.empty() && paths->ipm_path != nullptr && !cv::imwrite(paths->ipm_path, ipm))
    {
        std::fprintf(stderr, "WARN: write ipm failed: %s\n", paths->ipm_path);
    }

    if(paths->report_path != nullptr && !write_report(rt, paths->report_path))
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
    if(rt == nullptr || image_path == nullptr || count <= 0)
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

    if(report_path != nullptr && !write_report(rt, report_path))
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
//  @brief      实时模式主循环：开摄像头 → 采集 → 识别 → 读编码器 → 控制 → 下发电机 → 同步打印
//  @return     int          摄像头初始化失败时返回 1，正常情况下进入死循环不返回
//  @note       drive 是否真正输出由 FRONT_CAR_ENABLE_DRIVE 控制，默认不开电机。
//-------------------------------------------------------------------------------------------------------------------
int live(runtime_t *rt)
{
    const char *uvc = read_env_text("SMARTCAR_UVC_PATH", default_uvc_path());
    int w = read_env_int("SMARTCAR_UVC_WIDTH", default_uvc_width());
    int h = read_env_int("SMARTCAR_UVC_HEIGHT", default_uvc_height());
    int fps = read_env_int("SMARTCAR_UVC_FPS", default_uvc_fps());
    int div = read_env_int("FRONT_CAR_PRINT_DIV", default_live_print_divider());
    int drive_enabled = read_env_flag("FRONT_CAR_ENABLE_DRIVE", 0);
    int process_fps = read_env_int_clamped("FRONT_CAR_PROCESS_FPS", fps, 1, 120);
    const int period_us = frame_period_us_from_fps(process_fps);
    int control_period_ms = read_env_int_clamped("control_period_ms",
                                                 control_config().control_period_ms,
                                                 1,
                                                 100);
    rt->control_center_x = read_env_int_clamped("SMARTCAR_CONTROL_CENTER_X",
                                                default_control_center_x(),
                                                0,
                                                RAW_W - 1);
    rt->mid_position = MID_X;
    if(div < 1)
    {
        div = 1;
    }
    live_profile_t prof = {};
    prof.enabled = read_env_flag("FRONT_CAR_PROFILE", 0);
    prof.divider = read_env_int_clamped("FRONT_CAR_PROFILE_DIV", 30, 1, 10000);
    if(!device_open_camera(uvc, w, h, fps))
    {
        std::fprintf(stderr, "ERROR: camera init failed\n");
        return 1;
    }

    drive_output_init(drive_enabled);
    assistant_init();
    std::printf("front_car_mainline: live %s %dx%d@%d process_fps=%d drive=%s\n",
                uvc,
                w,
                h,
                fps,
                process_fps,
                drive_enabled ? "on" : "off");
    uint32_t frame_id = 0;
    while(1)
    {
        // 实时主链按真实顺序展开；t0~t6 是 profile 各阶段计时点。
        const uint64_t t0 = (prof.enabled || period_us > 0) ? monotonic_us() : 0;
        // [t0->t1] 采集一帧 RAW_W x RAW_H 灰度
        if(!device_capture_gray(rt->gray))
        {
            std::fprintf(stderr, "WARN: capture failed\n");
            continue;
        }
        const uint64_t t1 = prof.enabled ? monotonic_us() : 0;

        // [t1->t2] 视觉识别：seed -> trace -> boundary -> element -> midline -> guide_error
        rt->gray_valid = 1;
        tracking_process_frame(rt);
        const uint64_t t2 = prof.enabled ? monotonic_us() : 0;
        // [t2->t3] 读编码器/IMU 反馈，并把左右编码器均值累加到里程
        control_feedback_t fb = {};
        drive_output_read_feedback(&fb, control_period_ms);
        rt->encoder_total += (int64_t)(fb.left_speed_count + fb.right_speed_count) / 2;
        const uint64_t t3 = prof.enabled ? monotonic_us() : 0;
        // [t3->t4] 闭环控制：guide_error -> target_yaw -> 左右 duty
        solve_runtime_with_feedback(rt, &fb, &rt->control);
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
            profile_add(&prof.pts_us, t1, t2);
            profile_add(&prof.feedback_us, t2, t3);
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
    const char *uvc = read_env_text("SMARTCAR_UVC_PATH", default_uvc_path());
    int w = read_env_int("SMARTCAR_UVC_WIDTH", default_uvc_width());
    int h = read_env_int("SMARTCAR_UVC_HEIGHT", default_uvc_height());
    int fps = read_env_int("SMARTCAR_UVC_FPS", default_uvc_fps());
    if(!device_open_camera(uvc, w, h, fps))
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
