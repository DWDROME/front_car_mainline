#include "circle.h"
#include "atg_reference_step.h"
#include "motor.h"
#include "headfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENCODER_PER_METER   (5800)
int is_large_circle,is_small_circle,circle_count;  //记录赛道有几个圆环及其大小，配合离线调参可以提前预判大小圆环从而进行加减速操作
int circle_in_length=60,circle_in_distance=2000;   //入环时内侧边线长度，入环时编码器记录长度
enum circle_type_e circle_type = CIRCLE_NONE;


const char *circle_type_name[CIRCLE_NUM] = {
        "CIRCLE_NONE",
        "CIRCLE_LEFT_BEGIN", "CIRCLE_RIGHT_BEGIN",
        "CIRCLE_LEFT_IN", "CIRCLE_RIGHT_IN",
        "CIRCLE_LEFT_RUNNING", "CIRCLE_RIGHT_RUNNING",
        "CIRCLE_LEFT_OUT", "CIRCLE_RIGHT_OUT",
        "CIRCLE_LEFT_END", "CIRCLE_RIGHT_END",
};


int64_t circle_encoder;                                     // 编码器，用于防止一些重复触发等。

int none_left_line = 0, none_right_line = 0;                //丢线标志位
int have_left_line = 0, have_right_line = 0;                //重找到线的线标志位

enum
{
    CIRCLE_ENTRY_CONFIRM_FRAMES = 2,
    CIRCLE_BEGIN_LOST_CONFIRM_FRAMES = 2,
    CIRCLE_IN_DISTANCE_CONFIRM = 2000,
    // RUNNING 是环内最长段。该值只是陀螺失效时的距离兜底，16000 / 5800 about 2.76m，需上车标定。
    CIRCLE_RUNNING_FORCE_OUT_COUNTS = 16000,
    // 参考陀螺积分圆环：阈值单位是 0.1 度，进 IN 后单次清零，后续累计比较。
    CIRCLE_HEADING_ENTER_DEG10 = 600,
    CIRCLE_HEADING_START_OUT_DEG10 = 2000,
    CIRCLE_HEADING_FORCE_OUT_DEG10 = 2500,
    CIRCLE_HEADING_FINISH_DEG10 = 3550,
    CIRCLE_REENTRY_SUPPRESS_FRAMES = 150,
};
static const float CIRCLE_GYRO_DEADZONE_RAD_S = 0.065f;
static const float CIRCLE_RAD_TO_DEG10 = 1800.0f / 3.14159265358979f;

static int circle_left_entry_votes;
static int circle_right_entry_votes;
static int circle_entry_suppress_frames;
static float circle_heading_rad;

int circle_cal_log_enabled(void)
{
    const char *val = getenv("FRONT_CAR_CIRCLE_CAL_LOG");
    static int warned_invalid;
    if(val == NULL || val[0] == '\0' || strcmp(val, "0") == 0 || strcmp(val, "false") == 0)
    {
        return 0;
    }
    if(strcmp(val, "1") == 0 || strcmp(val, "true") == 0)
    {
        return 1;
    }
    if(!warned_invalid)
    {
        printf("EnvWarn: invalid flag for FRONT_CAR_CIRCLE_CAL_LOG='%s'\n", val);
        warned_invalid = 1;
    }
    return 0;
}

static int circle_heading_deg10(void)
{
    return (int)(fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10);
}

static void print_circle_transition(enum circle_type_e from,
                                    enum circle_type_e to,
                                    const char *reason)
{
    if(!circle_cal_log_enabled())
    {
        return;
    }
    printf("ATGCircleCal: from=%s to=%s reason=%s heading_deg10=%d dist=%d begin_dist=%lld begin_last=%lld\n",
           circle_type_name[from],
           circle_type_name[to],
           reason,
           circle_heading_deg10(),
           total_distence,
           (long long)atg_reference_circle_begin_dist(),
           (long long)atg_reference_circle_begin_last_dist());
}

static void print_left_out_farline_evidence(void)
{
    if(!circle_cal_log_enabled())
    {
        return;
    }
    printf("ATGCircleOutEvidence: stage=after_cross_farline_R circle=%s "
           "Lpt1=%d/%d rpts1s=%d rptsc1=%d lost_right=%d seed_raw=%.1f,%.1f "
           "far_ipts1=%d far_rpts1s=%d far_Lpt1=%d/%d far_seed_raw=%.1f,%.1f "
           "dist=%d heading_deg10=%d\n",
           circle_type_name[circle_type],
           Lpt1_found ? 1 : 0,
           Lpt1_found ? Lpt1_rpts1s_id : -1,
           rpts1s_num,
           rptsc1_num,
           if_lost_right_line,
           inv_Lpt1_found[0],
           inv_Lpt1_found[1],
           far_ipts1_num,
           far_rpts1s_num,
           far_Lpt1_found ? 1 : 0,
           far_Lpt1_found ? far_Lpt1_rpts1s_id : -1,
           inv_far_Lpt1_found[0],
           inv_far_Lpt1_found[1],
           total_distence,
           circle_heading_deg10());
}

void reset_circle_entry_votes()
{
    circle_left_entry_votes = 0;
    circle_right_entry_votes = 0;
}

void suppress_circle_entry_frames(int frames)
{
    if(frames > circle_entry_suppress_frames)
    {
        circle_entry_suppress_frames = frames;
    }
    reset_circle_entry_votes();
}

void suppress_circle_reentry_after_exit(void)
{
    suppress_circle_entry_frames(CIRCLE_REENTRY_SUPPRESS_FRAMES);
}

static int circle_entry_suppressed(void)
{
    if(circle_entry_suppress_frames <= 0)
    {
        return 0;
    }
    circle_entry_suppress_frames--;
    reset_circle_entry_votes();
    return 1;
}

void reset_circle_begin_flags()
{
    none_left_line = 0;
    none_right_line = 0;
    have_left_line = 0;
    have_right_line = 0;
}

static void reset_circle_heading(void)
{
    circle_heading_rad = 0.0f;
}

void update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid)
{
    if(circle_type == CIRCLE_NONE)
    {
        reset_circle_heading();
        return;
    }
    if(!valid || period_ms <= 0)
    {
        return;
    }

    if(fabsf(yaw_rate_rad_s) <= CIRCLE_GYRO_DEADZONE_RAD_S)
    {
        return;
    }
    circle_heading_rad += yaw_rate_rad_s * ((float)period_ms / 1000.0f);
}

static int circle_heading_abs_ge(int tenth_deg)
{
    return fabsf(circle_heading_rad) * CIRCLE_RAD_TO_DEG10 >= (float)tenth_deg;
}

void check_circle() {
    if (circle_type != CIRCLE_NONE) {
        reset_circle_entry_votes();
        return;
    }

    if (circle_entry_suppressed()) {
        return;
    }

    // 非圆环模式下，单边L角点, 单边长直道，且当比较靠近近处时才开启判别，防止远端图像畸变产生的误判（凡是id<一个数的都是为了靠近时再识别，在远处识别会有误判）
    const int left_entry = Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 35;
    const int right_entry = !Lpt0_found && Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 35;

    circle_left_entry_votes = left_entry ? circle_left_entry_votes + 1 : 0;
    circle_right_entry_votes = right_entry ? circle_right_entry_votes + 1 : 0;

    if (circle_left_entry_votes >= CIRCLE_ENTRY_CONFIRM_FRAMES) {
        print_circle_transition(circle_type, CIRCLE_LEFT_BEGIN, "entry_vote");
        circle_type = CIRCLE_LEFT_BEGIN;
        reset_circle_begin_flags();
        Count_dis_Flag=0;
        reset_circle_entry_votes();
    }

    if (circle_right_entry_votes >= CIRCLE_ENTRY_CONFIRM_FRAMES) {
        print_circle_transition(circle_type, CIRCLE_RIGHT_BEGIN, "entry_vote");
        circle_type = CIRCLE_RIGHT_BEGIN;
        reset_circle_begin_flags();
        Count_dis_Flag=0;
        reset_circle_entry_votes();
    }
}

void run_circle() {
    int64_t current_encoder = 1;

    // ===================== 左环 =====================
    if (circle_type == CIRCLE_LEFT_BEGIN) {
        track_type = TRACK_RIGHT;

        // 入环口必然出现的内侧(左)线丢失事件：保留，它是进 IN 的真证据来源。
        if (rpts0s_num < 2 && !Lpt0_found) {
            Count_dis_Flag = 1;
            none_left_line++;
            have_left_line = 0;
        }

        /*
         * legacy visual reappear gate:
         * if (rpts0s_num > 30 && none_left_line) have_left_line++;
         * if ((rpts0s_num < circle_in_length && total_distence > circle_in_distance && have_left_line) ||
         *     (rpts0s_num < circle_in_length && have_left_line && circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)))
         *
         * 偏置进环时内侧线可能追不到"重现 -> 再变短"，会卡在 BEGIN。
         * 现在只要求已发生丢线事件，再由距离或陀螺确认进入固定动作 IN。
         */
        if (none_left_line >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
            total_distence > circle_in_distance) {
            print_circle_transition(circle_type, CIRCLE_LEFT_IN, "entry_distance");
            circle_type = CIRCLE_LEFT_IN;
            reset_circle_heading();
            if_lost_right_line = 0;
            reset_circle_begin_flags();
            if_clean_pid = 1;
            Count_dis_Flag = 0;
        }
        else if (none_left_line >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
                 circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_LEFT_IN, "entry_gyro");
            circle_type = CIRCLE_LEFT_IN;
            reset_circle_heading();
            if_lost_right_line = 0;
            reset_circle_begin_flags();
            if_clean_pid = 1;
            Count_dis_Flag = 0;
        }
    }
    else if (circle_type == CIRCLE_LEFT_IN) {
        cross_farline_L();                     // 固定补线不依赖远线，但保留远线搜索供其他标志位刷新。
        track_type = TRACK_LEFT;
        Count_dis_Flag = 1;

        if (rpts0s_num > 70) {
            is_large_circle = 1;
            is_small_circle = 0;
        }
        else {
            is_small_circle = 1;
        }

        /*
         * legacy visual reappear gate:
         * if (rpts1s_num < 0.2 / sample_dist) none_right_line++;
         * if ((rpts1s_num > 25 && none_right_line > 1) ||
         *     (total_distence > CIRCLE_IN_DISTANCE_CONFIRM && rpts0s_num < circle_in_length && rpts1s_num > 25) ||
         *     (rpts0s_num < circle_in_length && rpts1s_num > 25 && circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)))
         */
        if (circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_LEFT_RUNNING, "gyro");
            circle_type = CIRCLE_LEFT_RUNNING;
            track_type = TRACK_RIGHT;
            Count_dis_Flag = 0;
            none_right_line = 0;
        }
        else if (total_distence > CIRCLE_IN_DISTANCE_CONFIRM) {
            print_circle_transition(circle_type, CIRCLE_LEFT_RUNNING, "distance");
            circle_type = CIRCLE_LEFT_RUNNING;
            track_type = TRACK_RIGHT;
            Count_dis_Flag = 0;
            none_right_line = 0;
        }
    }
    else if (circle_type == CIRCLE_LEFT_RUNNING) {
        track_type = TRACK_RIGHT;
        Count_dis_Flag = 1;

        /*
         * legacy Lpt out trigger and truncation:
         * if (Lpt1_found) {
         *     rpts1s_num = Lpt1_rpts1s_id - 2;
         *     rptsc1_num = Lpt1_rpts1s_id - 2;
         * }
         * if (Lpt1_found && Lpt1_rpts1s_id < 0.7 / sample_dist) ...
         *
         * RUNNING -> OUT 现在只用累计陀螺正常触发；距离只作陀螺失效兜底。
         */
        if (circle_heading_abs_ge(CIRCLE_HEADING_START_OUT_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_LEFT_OUT, "gyro");
            circle_type = CIRCLE_LEFT_OUT;
            Count_dis_Flag = 0;
            if_lost_right_line = 0;
            if_clean_pid = 1;
        }
        else if (total_distence > CIRCLE_RUNNING_FORCE_OUT_COUNTS) {
            print_circle_transition(circle_type, CIRCLE_LEFT_OUT, "distance");
            circle_type = CIRCLE_LEFT_OUT;
            Count_dis_Flag = 0;
            if_lost_right_line = 0;
            if_clean_pid = 1;
        }
    }
    else if (circle_type == CIRCLE_LEFT_OUT) {
        cross_farline_R();
        print_left_out_farline_evidence();
        track_type = TRACK_LEFT;
        Count_dis_Flag = 1;

        /*
         * legacy visual reappear gate:
         * if (rpts1s_num < 5) none_right_line++;
         * if (rpts1s_num > 30 && !Lpt1_found && none_right_line > 1) ...
         */
        if (circle_heading_abs_ge(CIRCLE_HEADING_FORCE_OUT_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_LEFT_END, "gyro");
            circle_type = CIRCLE_LEFT_END;
            none_right_line = 0;
            Count_dis_Flag = 0;
        }
        else if (total_distence > 4500) {
            print_circle_transition(circle_type, CIRCLE_LEFT_END, "distance");
            circle_type = CIRCLE_LEFT_END;
            none_right_line = 0;
            Count_dis_Flag = 0;
        }
    }
    else if (circle_type == CIRCLE_LEFT_END) {
        track_type = TRACK_RIGHT;
        broadcast_flag = 1;
        Count_dis_Flag = 1;

        if (circle_heading_abs_ge(CIRCLE_HEADING_FINISH_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_NONE, "gyro");
            circle_type = CIRCLE_NONE;
            road_type = ROAD_NORMAL;
            begin_y = BEGIN_Y;
            Count_dis_Flag = 0;
            aim_distance = AIM_DISTENCE;
            is_large_circle = is_small_circle = 0;
            if_lost_right_line = 0;
            if_lost_left_line = 0;
            circle_count++;
            none_right_line = 0;
            have_right_line = 0;
            none_left_line = 0;
            have_left_line = 0;
            suppress_circle_reentry_after_exit();
        }
        else if (total_distence >= 7500) {
            print_circle_transition(circle_type, CIRCLE_NONE, "distance");
            circle_type = CIRCLE_NONE;
            road_type = ROAD_NORMAL;
            begin_y = BEGIN_Y;
            Count_dis_Flag = 0;
            aim_distance = AIM_DISTENCE;
            is_large_circle = is_small_circle = 0;
            if_lost_right_line = 0;
            if_lost_left_line = 0;
            circle_count++;
            none_right_line = 0;
            have_right_line = 0;
            none_left_line = 0;
            have_left_line = 0;
            suppress_circle_reentry_after_exit();
        }
    }

    // ===================== 右环 =====================
    else if (circle_type == CIRCLE_RIGHT_BEGIN) {
        track_type = TRACK_LEFT;

        // 内侧(右)线丢失事件：保留，右环沿用原来的 <10 阈值。
        if (rpts1s_num < 10 && !Lpt1_found) {
            Count_dis_Flag = 1;
            none_right_line++;
            have_right_line = 0;
        }

        /*
         * legacy visual reappear gate:
         * if (rpts1s_num > 30 && none_right_line) have_right_line++;
         * if ((rpts1s_num < circle_in_length && total_distence > circle_in_distance && have_right_line) ||
         *     (rpts1s_num < circle_in_length && have_right_line && circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)))
         */
        if (none_right_line >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
            total_distence > circle_in_distance) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_IN, "entry_distance");
            circle_type = CIRCLE_RIGHT_IN;
            reset_circle_heading();
            if_lost_left_line = 0;
            reset_circle_begin_flags();
            circle_encoder = current_encoder;
            Count_dis_Flag = 0;
            if_clean_pid = 1;
        }
        else if (none_right_line >= CIRCLE_BEGIN_LOST_CONFIRM_FRAMES &&
                 circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_IN, "entry_gyro");
            circle_type = CIRCLE_RIGHT_IN;
            reset_circle_heading();
            if_lost_left_line = 0;
            reset_circle_begin_flags();
            circle_encoder = current_encoder;
            Count_dis_Flag = 0;
            if_clean_pid = 1;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_IN) {
        cross_farline_R();
        track_type = TRACK_RIGHT;
        Count_dis_Flag = 1;

        if (rpts1s_num > 70) {
            is_large_circle = 1;
            is_small_circle = 0;
        }
        else {
            is_small_circle = 1;
        }

        /*
         * legacy visual reappear gate:
         * if (rpts0s_num < 5) none_left_line++;
         * if ((rpts0s_num > 25 && none_left_line > 1) ||
         *     (total_distence > CIRCLE_IN_DISTANCE_CONFIRM && rpts1s_num < circle_in_length && rpts0s_num > 25) ||
         *     (rpts1s_num < circle_in_length && rpts0s_num > 25 && circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)))
         */
        if (circle_heading_abs_ge(CIRCLE_HEADING_ENTER_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_RUNNING, "gyro");
            circle_type = CIRCLE_RIGHT_RUNNING;
            track_type = TRACK_LEFT;
            Count_dis_Flag = 0;
            begin_y = BEGIN_Y;
            none_left_line = 0;
        }
        else if (total_distence > CIRCLE_IN_DISTANCE_CONFIRM) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_RUNNING, "distance");
            circle_type = CIRCLE_RIGHT_RUNNING;
            track_type = TRACK_LEFT;
            Count_dis_Flag = 0;
            begin_y = BEGIN_Y;
            none_left_line = 0;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_RUNNING) {
        track_type = TRACK_LEFT;
        Count_dis_Flag = 1;

        /*
         * legacy Lpt out trigger and truncation:
         * if (Lpt0_found) {
         *     rpts0s_num = Lpt0_rpts0s_id - 2;
         *     rptsc0_num = Lpt0_rpts0s_id - 2;
         * }
         * if (Lpt0_found && Lpt0_rpts0s_id < 0.7 / sample_dist) ...
         */
        if (circle_heading_abs_ge(CIRCLE_HEADING_START_OUT_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_OUT, "gyro");
            circle_type = CIRCLE_RIGHT_OUT;
            Count_dis_Flag = 0;
            if_lost_left_line = 0;
            if_clean_pid = 1;
        }
        else if (total_distence > CIRCLE_RUNNING_FORCE_OUT_COUNTS) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_OUT, "distance");
            circle_type = CIRCLE_RIGHT_OUT;
            Count_dis_Flag = 0;
            if_lost_left_line = 0;
            if_clean_pid = 1;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_OUT) {
        cross_farline_L();
        track_type = TRACK_RIGHT;
        broadcast_flag = 1;
        Count_dis_Flag = 1;

        /*
         * legacy visual reappear gate:
         * if (rpts0s_num < 5) none_left_line++;
         * if (rpts0s_num > 30 && !Lpt0_found && none_left_line >= 1) ...
         */
        if (circle_heading_abs_ge(CIRCLE_HEADING_FORCE_OUT_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_END, "gyro");
            circle_type = CIRCLE_RIGHT_END;
            none_left_line = 0;
            Count_dis_Flag = 0;
        }
        else if (total_distence > 4500) {
            print_circle_transition(circle_type, CIRCLE_RIGHT_END, "distance");
            circle_type = CIRCLE_RIGHT_END;
            none_left_line = 0;
            Count_dis_Flag = 0;
        }
    }
    else if (circle_type == CIRCLE_RIGHT_END) {
        track_type = TRACK_LEFT;
        Count_dis_Flag = 1;

        /*
         * legacy unused line-loss count:
         * if (rpts1s_num < 0.2 / sample_dist) { none_right_line++; Count_dis_Flag = 1; }
         */
        if (circle_heading_abs_ge(CIRCLE_HEADING_FINISH_DEG10)) {
            print_circle_transition(circle_type, CIRCLE_NONE, "gyro");
            circle_type = CIRCLE_NONE;
            road_type = ROAD_NORMAL;
            begin_y = BEGIN_Y;
            Count_dis_Flag = 0;
            aim_distance = AIM_DISTENCE;
            is_large_circle = is_small_circle = 0;
            if_lost_right_line = 0;
            if_lost_left_line = 0;
            circle_count++;
            none_right_line = 0;
            have_right_line = 0;
            none_left_line = 0;
            have_left_line = 0;
            suppress_circle_reentry_after_exit();
        }
        else if (total_distence >= 4000) {
            print_circle_transition(circle_type, CIRCLE_NONE, "distance");
            circle_type = CIRCLE_NONE;
            road_type = ROAD_NORMAL;
            begin_y = BEGIN_Y;
            Count_dis_Flag = 0;
            aim_distance = AIM_DISTENCE;
            is_large_circle = is_small_circle = 0;
            if_lost_right_line = 0;
            if_lost_left_line = 0;
            circle_count++;
            none_right_line = 0;
            have_right_line = 0;
            none_left_line = 0;
            have_left_line = 0;
            suppress_circle_reentry_after_exit();
        }
    }
}
