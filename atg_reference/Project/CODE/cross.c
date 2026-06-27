/* =====================================================================
 *  十字检测与远线搜索
 *
 *  整体流程：
 *
 *    ┌──────────────────────────────────────────────────────────────┐
 *    │  NONE ──(双L角点)──► BEGIN ──(近角点太短)──► IN ──(远线)──► HALF │
 *    │    ▲                                            │           │
 *    │    │                                            ▼           │
 *    │    └─────────────(先丢后有线)────────────────────┘           │
 *    └──────────────────────────────────────────────────────────────┘
 *
 *  各阶段任务：
 *
 *  BEGIN — 近线截断
 *    检测到双 L 角点后，截断近线到角点位置，用近线控制。
 *    当近角点太短（id < 0.1/sample_dist）→ 进入 IN。
 *
 *  IN — 远线控制
 *    调用 cross_farline() 寻找远端边线和远端 L 角点。
 *    根据远端 L 角点选择跟左线还是右线。
 *
 *  HALF — 单侧远线通过
 *    最终阶段，仅靠一侧远线通过十字。
 *    Lpt0_found_flag / Lpt1_found_flag 记录看到的是哪一侧。
 *    先丢后有线 → 退出十字。
 *
 *  远线搜索链（每侧）：
 *    seed → scan → trace → ipm → proc → find_lpt
 *    1. seed：从近端 L 角点偏移得到搜索起点
 *    2. scan：从起点向上扫描，找到暗点（边线起点）
 *    3. trace：从暗点开始沿边界搜线
 *    4. ipm：逆透视变换，转到俯视角
 *    5. proc：滤波 → 等距采样 → 局部角度 → NMS
 *    6. find_lpt：从角度序列中找 L 角点
 *
 *  坐标系：
 *    far_ipts*  — 原图坐标（搜索结果）
 *    far_rpts*  — 俯视角坐标（IPM 变换后）
 *    far_rpts*s — 等距采样后的俯视角坐标
 *    far_rpts*a — 局部角度序列
 *    far_rpts*an — NMS 抑制后的角度序列
 *    inv_Lpt*_found — 近端 L 角点的原图坐标（逆旋转后）
 *    inv_far_Lpt*_found — 远端 L 角点的原图坐标（逆旋转后）
 * ===================================================================== */
#include "cross.h"
#include "motor.h"
#include "headfile.h"

#define PI               3.14159265358979f
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* ================= 十字全局状态 ================= */

enum cross_type_e cross_type = CROSS_NONE;             /* 当前十字状态机阶段 */

const char *cross_type_name[CROSS_NUM] = {
        "CROSS_NONE",
        "CROSS_BEGIN", "CROSS_IN",
        "CROSS_HALF"
};

float conf3,conf4,conf3_max,conf4_max;  /* 远端 L 角点的角度置信度及历史最大值 */

uint8 if_lost_left_line = 0,if_lost_right_line = 0;   /* 近端边线是否曾经丢失过 */

/* ================= 远线搜索全局变量 ================= */

/* 远端 L 角点检测结果 */
bool far_Lpt0_found, far_Lpt1_found;                  /* 远端左/右 L 角点是否找到 */
int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;           /* 远端 L 角点在采样序列中的索引 */
int8 Lpt0_found_flag,Lpt1_found_flag;                  /* HALF 阶段：记录看到的是哪一侧 */

/* 远线原图坐标（搜索结果） */
int far_ipts0[MT9V03X_H][2];
int far_ipts1[MT9V03X_H][2];
int far_ipts0_num, far_ipts1_num;

/* 远线俯视角坐标（IPM 变换后） */
float far_rpts0[MT9V03X_H][2];
float far_rpts1[MT9V03X_H][2];
int far_rpts0_num, far_rpts1_num;

/* 远线滤波后坐标 */
float far_rpts0b[MT9V03X_H][2];
float far_rpts1b[MT9V03X_H][2];
int far_rpts0b_num, far_rpts1b_num;

/* 远线等距采样后坐标 */
float far_rpts0s[MT9V03X_H][2];
float far_rpts1s[MT9V03X_H][2];
int far_rpts0s_num, far_rpts1s_num;

/* 远线局部角度序列 */
float far_rpts0a[MT9V03X_H];
float far_rpts1a[MT9V03X_H];
int far_rpts0a_num, far_rpts1a_num;

/* 远线 NMS 抑制后的角度序列 */
float far_rpts0an[MT9V03X_H];
float far_rpts1an[MT9V03X_H];
int far_rpts0an_num, far_rpts1an_num;

int not_have_line = 0;                                /* 连续无线帧数，用于退出十字判断 */

/* 远线搜索起始坐标 */
int far_x1 = 32, far_x2 = 118, far_y1, far_y2;       /* 左/右远线搜索起点（原图坐标） */
int far_x11=70;                                        /* 当前帧实际使用的 x 起点 */

/* 近端/远端 L 角点的原图坐标（逆旋转后） */
float inv_Lpt0_found[2],inv_Lpt1_found[2];            /* 近端 L 角点 */
float inv_far_Lpt0_found[2],inv_far_Lpt1_found[2];    /* 远端 L 角点 */

static int far_l_thres;                                /* 左远线搜索的自适应阈值 */
static int far_r_thres;                                /* 右远线搜索的自适应阈值 */

/* ================= 状态复位 ================= */

/* 清空远线搜索的所有输出，每帧搜索前调用 */
void clear_cross_farline_outputs()
{
    far_Lpt0_found = false;
    far_Lpt1_found = false;
    far_Lpt0_rpts0s_id = 0;
    far_Lpt1_rpts1s_id = 0;
    far_ipts0_num = 0;
    far_ipts1_num = 0;
    far_rpts0_num = 0;
    far_rpts1_num = 0;
    far_rpts0b_num = 0;
    far_rpts1b_num = 0;
    far_rpts0s_num = 0;
    far_rpts1s_num = 0;
    far_rpts0a_num = 0;
    far_rpts1a_num = 0;
    far_rpts0an_num = 0;
    far_rpts1an_num = 0;
    inv_far_Lpt0_found[0] = 0.0f;
    inv_far_Lpt0_found[1] = 0.0f;
    inv_far_Lpt1_found[0] = 0.0f;
    inv_far_Lpt1_found[1] = 0.0f;
    conf3 = 0.0f;
    conf4 = 0.0f;
    conf3_max = 0.0f;
    conf4_max = 0.0f;
}

/* 十字退出收口：恢复状态，清空远线输出 */
void reset_cross_state()
{
    cross_type = CROSS_NONE;
    ramp_type = RAMP_NONE;
    Clean_Time_count_flag = 0;
    aim_distance = AIM_DISTENCE;
    not_have_line = 0;
    if_lost_left_line = 0;
    if_lost_right_line = 0;
    Lpt0_found_flag = 0;
    Lpt1_found_flag = 0;
    clear_cross_farline_outputs();
}

/* ================= 十字检测与主流程 ================= */

/* 入口检测：双 L 角点同时出现 → 进入 BEGIN */
void check_cross() {
    bool x_found = Lpt0_found && Lpt1_found;
    if (cross_type == CROSS_NONE && x_found) cross_type = CROSS_BEGIN;
}
/* 十字状态机主流程：
 *
 * BEGIN：截断近线到角点位置，用近线控制。
 *        近角点太短 → 进入 IN。
 * IN：远线控制，寻远线后选择跟左/右线。
 * HALF：单侧远线通过，先丢后有线 → 退出十字。
 */
void run_cross()
{
    bool x_found = Lpt0_found && Lpt1_found;

    /* --- BEGIN：近线截断 --- */
    if (cross_type == CROSS_BEGIN) {
        if (Lpt0_found) {
            rptsc0_num = rpts0s_num = Lpt0_rpts0s_id;
        }
        if (Lpt1_found) {
            rptsc1_num = rpts1s_num = Lpt1_rpts1s_id;
        }

        //aim_distance = AIM_DISTENCE;
        aim_distance = 0.4; // 参考的
        /* 近角点太短（id < 0.1/sample_dist）→ 进入远线控制 */
        if ((x_found && (Lpt0_rpts0s_id < 0.1 / sample_dist || Lpt1_rpts1s_id < 0.1 / sample_dist))/* || (rpts1_num <30 && rpts0_num<30)*/) {
            cross_type = CROSS_IN;
        }
    }

    /* --- IN：远线控制 --- */
    else if (cross_type == CROSS_IN) {
        cross_farline();                               /* 寻远线 */

        if (rpts1s_num < 5 && rpts0s_num < 5) { not_have_line++; }
        if (not_have_line > 2 && rpts1s_num > 20 && rpts0s_num > 20) {
            reset_cross_state();
            return;
        }
        if (far_Lpt1_found) { track_type = TRACK_RIGHT; }
        else if (far_Lpt0_found) { track_type = TRACK_LEFT; }
        else if (not_have_line > 0 && rpts1s_num < 5) { track_type = TRACK_RIGHT; }
        else if (not_have_line > 0 && rpts0s_num < 5) { track_type = TRACK_LEFT; }

    }
    /* --- HALF：单侧远线通过 ---
     * 最终阶段，仅靠一侧远线通过十字（另一侧全丢都没问题）。
     * Lpt0_found_flag / Lpt1_found_flag 记录看到的是哪一侧。
     * 先丢后有线 → 退出十字。 */
    else if(cross_type == CROSS_HALF){
        if(Lpt0_found_flag)
        {
            /* 左侧：搜左远线，跟左线 */
            cross_farline_L();
            aim_distance = 0.75;                       /* 斜入对称化：左半前瞻对齐右半 */
            track_type = TRACK_LEFT;
            if (rpts0s_num < 5) { not_have_line++; }
            if (not_have_line > 2 && rpts1s_num > 20 && rpts0s_num > 20) {
                //经历过一个先丢先再有线的过程说明可以刷掉十字了
                reset_cross_state();
                return;
            }
        }
        if(Lpt1_found_flag)
        {
            /* 右侧：搜右远线，跟右线 */
            cross_farline_R();
            aim_distance = 0.75;
            track_type = TRACK_RIGHT;
            if (rpts1s_num < 5) { not_have_line++; }
            if (not_have_line > 2 && rpts0s_num > 20 && rpts1s_num > 20) {
                reset_cross_state();
                return;
            }
        }

    }
}
/* ================= 左远线搜索链 ================= */

/* 左远线 seed：从近端 L 角点偏移得到搜索起点。
 *
 * 三种情况：
 * 1. 正常：从 L 角点偏移 (-5, -17) 得到起点
 * 2. 右圆环出环：用固定点 (80, begin_y*0.85) 搜索
 * 3. 边线丢失：用固定点 (20, begin_y-5) 搜索
 *
 * 偏移的目的是保证起点始终在近端边线上方，避免搜到近端边线。 */
static int far_l_seed()
{

    if (Lpt0_found&&rpts0s_num>=3&&!if_lost_left_line) {
        /*
         * if_lost_left_line表示边线是否曾经丢失过
                        若if_lost_left_line的条件不满足，则说明边线经过了一个先有线后丢线的过程，有可能是某个元素行进到了下一个阶段
                        比如圆环从CIRCLE_LEFT_BEGIN进入入环补线相位，从十字路口中间驶离十字元素等情况都会经过这个过程
                        第一步，当找到左侧拐点，且左侧的拐点边线还在没丢的情况下，将俯视角下的拐点坐标映射回原图坐标
                        利用此坐标作为起始点，可以向上去找同侧远端边线
                        假设*表示边线，&为近处的拐点，#表示远处的拐点，则在这个近处拐点&的坐标基础上进行一定的偏移，用￥表示远端边线搜索的起始点坐标
                        偏移的目的是保证这个点，在车身无论多歪的情况下能够始终在近端边线的上方，从而能够向上搜到远处的边线

                                 *
                                 *
                                 *
                                 *
                                 *
                                 *
          ***********************#




                                                  ￥

          ***********************&
                                 *
                                 *
                                 *
                                 *
                                 *
                                 *
                                 *
                                 *


         */
        inv_Lpt0_found[0] = Cal_inv_rot_x(rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][0],rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][1])-5;
        inv_Lpt0_found[1] = Cal_inv_rot_y(rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][0],rpts0s[clip(Lpt0_rpts0s_id,0,rpts0s_num-1)][1])-17;//-5和-17都是在拐点坐标的基础上进行相对偏移
        rptsc0_num = rpts0s_num = Lpt0_rpts0s_id-1 ;            //截断处理，防止顺着一侧边线划出去
        return 1;
    }
    else if(circle_type== CIRCLE_RIGHT_OUT){

        //在这个if条件中主要用于圆环各阶段近处丢线情况下，寻找合适的起始点，从而从远端的边线信息中提取角点，从而进行补线的操作
        //这是出环阶段的情况下，原本的CIRCLE_RIGHT_OUT是利用内侧边线划出去，但是R50这种小圆也是极容易丢失边线的
        //因此我选了一个比较靠近图像正中下方的一个点，这样他既不会在向上搜边线的时候碰到外环边线，而且能搜到赛道对侧的长直道，用于出环补线
        inv_Lpt0_found[0] = 80;
        inv_Lpt0_found[1] = begin_y*0.85;
        return 1;


    }
    else if(rpts0s_num<2){
        //在非圆环且边线几乎丢失的情况下，说明近端空白，可以用一个固定的点位去向上搜索，固定点的坐标需要根据你图像的尺寸和摄像头高度修改
        if_lost_left_line = 1;
        inv_Lpt0_found[0] = 20;
        inv_Lpt0_found[1] = begin_y-5;
        return 1;
    }

    return 0;
}

/* 右侧近端拐点截断：防止近端边线干扰远线搜索 */
static void far_l_cut_right()
{
    if (Lpt1_found) {
        rptsc1_num = rpts1s_num = Lpt1_rpts1s_id -2;
    }
}

/* 从 seed 点向上扫描，找到边线起点（暗点）。
 *
 * 算法：
 *   1. 先向上找白→黑跳变（OSTU 阈值）
 *   2. 再从黑跳变处向上，用自适应阈值找真正的边线起点
 *   3. 自适应阈值 = block 内均值 - clip_value
 *
 * 返回：far_y1 > block_size/2 表示找到有效起点 */
static int far_l_scan()
{
    far_y1 = 0, far_y2 = 0;
    int y1 = clip((int)inv_Lpt0_found[1], block_size/2 + 1, MT9V03X_H - block_size/2 - 1);
    far_x11 = clip((int)inv_Lpt0_found[0], block_size/2, MT9V03X_W - block_size/2 - 1);
    far_ipts0_num = sizeof(far_ipts0) / sizeof(far_ipts0[0]);

    int local_thres_left_up = 0;

    /* 第一步：向上找白→黑跳变 */
    for (; y1 > block_size/2; y1--) {
        if (AT_IMAGE(&img_raw, far_x11, y1-1) < OSTU_thres) {
            break;
        }
    }

    /* 第二步：从黑跳变处向上，用自适应阈值找边线起点 */
    for (; y1 > block_size/2; y1--) {
        local_thres_left_up = 0;
        for (int dy = -block_size/2; dy <= block_size/2; dy++) {
            for (int dx = -block_size/2; dx <= block_size/2; dx++) {
                local_thres_left_up += AT_IMAGE(&img_raw, far_x11 + dx, y1 + dy);
            }
        }
        local_thres_left_up /= block_size * block_size;
        local_thres_left_up -= clip_value;

        if (AT_IMAGE(&img_raw, far_x11 , y1 - 1 ) < local_thres_left_up)
        {
            far_y1 = y1;
            break;
        }
    }
    far_l_thres = local_thres_left_up;
    return far_y1 > block_size/2;
}

/* 从找到的边线起点开始，沿边界搜线（左手准则） */
static void far_l_trace()
{
    if (far_y1 > block_size/2 && AT_IMAGE(&img_raw, far_x11, far_y1 -1) < far_l_thres)
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, far_x11, far_y1 , far_ipts0, &far_ipts0_num);
    else far_ipts0_num = 0;
}

/* 逆透视变换：原图坐标 → 俯视角坐标 */
static void far_l_ipm()
{
    for(int i=0;i<far_ipts0_num;i++)
    {
        far_rpts0[i][0] = (rot[1][0]*far_ipts0[i][1]+rot[1][1]*far_ipts0[i][0]+rot[1][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_x;
        far_rpts0[i][1] = (rot[0][0]*far_ipts0[i][1]+rot[0][1]*far_ipts0[i][0]+rot[0][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_y;
    }

    far_rpts0_num = far_ipts0_num;
}

/* 远线后处理：滤波 → 等距采样 → 局部角度 → NMS */
static void far_l_proc()
{
    /* 边线滤波 */
    blur_points(far_rpts0, far_rpts0_num, far_rpts0b, (int) round(line_blur_kernel));
    far_rpts0b_num = far_rpts0_num;

    /* 边线等距采样 */
    far_rpts0s_num = sizeof(far_rpts0s) / sizeof(far_rpts0s[0]);
    resample_points(far_rpts0b, far_rpts0b_num, far_rpts0s, &far_rpts0s_num, sample_dist * pixel_per_meter);

    /* 边线局部角度变化率 */
    local_angle_points(far_rpts0s, far_rpts0s_num, far_rpts0a, (int) round(angle_dist / sample_dist));
    far_rpts0a_num = far_rpts0s_num;

    /* 角度变化率非极大抑制 */
    nms_angle(far_rpts0a, far_rpts0a_num, far_rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts0an_num = far_rpts0a_num;
}

/* 从远线角度序列中找 L 角点。
 *
 * 判断逻辑：
 *   1. 角度置信度 conf = |angle[i]| - (|angle[i-1]| + |angle[i+1]|) / 2
 *   2. 50° < conf < 140° → 角度范围合理
 *   3. i < 40 → 角点不能太远
 *   4. 拐点与前后点的相对位置关系 → 防止误判
 *
 * 找到后逆旋转回原图坐标，存入 inv_far_Lpt0_found。 */
static void far_l_find_lpt()
{
    far_Lpt0_found = false;
    for (int i = 0; i < MIN(far_rpts0s_num, 70); i++) {
        if (far_rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        conf3 = fabs(far_rpts0a[i]) - (fabs(far_rpts0a[im1]) + fabs(far_rpts0a[ip1])) / 2;
        /* 角度范围 + 位置关系判断 */
        if (50. / 180. * PI < conf3 && conf3 < 140. / 180. * PI && i < 40&&far_rpts0s[i][0]<=far_rpts0s[ip1][0]&&i>1&&far_rpts0s[i][1]>far_rpts0s[ip1][1]&&far_rpts0s[im1][0]<far_rpts0s[ip1][0]) {
            far_Lpt0_rpts0s_id = i;
            far_Lpt0_found = true;
            /* 逆旋转回原图坐标 */
            inv_far_Lpt0_found[0] = Cal_inv_rot_x(far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][0],far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][1]);
            inv_far_Lpt0_found[1] = Cal_inv_rot_y(far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][0],far_rpts0s[clip(far_Lpt0_rpts0s_id,0,far_rpts0s_num-1)][1]);
            break;
        }
        if(conf3>conf3_max)conf3_max = conf3;          /* 记录最大角度值，方便调参 */
    }





}


/* 左远线搜索完整链：
 * seed → scan → trace → ipm → proc → find_lpt
 * 任何一步失败都会提前返回，far_Lpt0_found 保持 false。 */
void cross_farline_L()
{
    far_Lpt0_found = false;
    if (!far_l_seed()) return;                         /* 没有合适的搜索起点 */
    far_l_cut_right();                                 /* 截断右侧近端边线 */
    if (!far_l_scan()) return;                         /* 没找到边线起点 */
    far_l_trace();                                     /* 搜线 */
    far_l_ipm();                                       /* 逆透视变换 */
    far_l_proc();                                      /* 滤波+采样+角度+NMS */
    far_l_find_lpt();                                  /* 找 L 角点 */
}


/* ================= 右远线搜索链 ================= */

/* 左侧近端拐点截断 */
static void far_r_cut_left()
{
    if (Lpt0_found) {
        rptsc0_num = rpts0s_num = Lpt0_rpts0s_id -2;
    }
}

/* 左圆环出环时的动态 seed：
 * 从右侧边线的趋势推算搜索起点，比固定点更可靠。
 * 如果推算失败，回退到固定点。 */
static void far_r_seed_circle_out()
{
    int seed_mode_dynamic = 0;
    const char *seed_reason = "not_left_out";
    const int idx_low = rptsc1_num / 3;
    const int idx_high = rptsc1_num * 2 / 3;
    if(rptsc1_num > 10)
    {
        const float raw_low_x = Cal_inv_rot_x(rptsc1[idx_low][0], rptsc1[idx_low][1]);
        const float raw_low_y = Cal_inv_rot_y(rptsc1[idx_low][0], rptsc1[idx_low][1]);
        const float raw_high_x = Cal_inv_rot_x(rptsc1[idx_high][0], rptsc1[idx_high][1]);
        const float raw_high_y = Cal_inv_rot_y(rptsc1[idx_high][0], rptsc1[idx_high][1]);
        const float dx_raw = raw_high_x - raw_low_x;
        const float dy_raw = raw_high_y - raw_low_y;
        const float len = sqrtf(dx_raw * dx_raw + dy_raw * dy_raw);

        /*
         * Left-circle OUT should see the right boundary trend from
         * lower-right toward upper-left in raw coordinates. Use that
         * current-frame trend only when both axes agree.
         */
        if(len > 1.0f && dx_raw < -1.0f && dy_raw < -1.0f)
        {
            const float proj = 20.0f;
            const float sx = raw_high_x + dx_raw / len * proj;
            const float sy = raw_high_y + dy_raw / len * proj;
            const float min_dynamic_x = MT9V03X_W * 0.5f;
            const float max_dynamic_x = MT9V03X_W - block_size / 2 - 1;
            const float min_dynamic_y = block_size / 2 + 1;
            const float max_dynamic_y = MT9V03X_H - block_size / 2 - 1;
            if(sx >= min_dynamic_x && sx <= max_dynamic_x &&
               sy >= min_dynamic_y && sy <= max_dynamic_y)
            {
                inv_Lpt1_found[0] = sx;
                inv_Lpt1_found[1] = sy;
                seed_mode_dynamic = 1;
                seed_reason = "ok";
                if(circle_cal_log_enabled())
                {
                    printf("ATGCircleOutSeed: mode=dynamic circle=%s rptsc1=%d "
                           "idx=%d/%d ipm=%.1f,%.1f -> %.1f,%.1f "
                           "raw_seg=%.1f,%.1f -> %.1f,%.1f "
                           "delta=%.1f,%.1f raw=%.1f,%.1f proj=%.1f reason=%s\n",
                           circle_type_name[circle_type], rptsc1_num,
                           idx_low, idx_high,
                           rptsc1[idx_low][0], rptsc1[idx_low][1],
                           rptsc1[idx_high][0], rptsc1[idx_high][1],
                           raw_low_x, raw_low_y,
                           raw_high_x, raw_high_y,
                           dx_raw, dy_raw,
                           inv_Lpt1_found[0], inv_Lpt1_found[1], proj,
                           seed_reason);
                }
            }
            else
            {
                seed_reason = "out_of_band";
                if(circle_cal_log_enabled())
                {
                    printf("ATGCircleOutSeed: mode=rejected_dynamic circle=%s rptsc1=%d "
                           "idx=%d/%d raw=%.1f,%.1f bounds=%.1f..%.1f,%.1f..%.1f "
                           "reason=%s\n",
                           circle_type_name[circle_type], rptsc1_num,
                           idx_low, idx_high,
                           sx, sy,
                           min_dynamic_x, max_dynamic_x,
                           min_dynamic_y, max_dynamic_y,
                           seed_reason);
                }
            }
        }
        else
        {
            seed_reason = len <= 1.0f ? "degenerate" : "bad_slope";
        }
    }
    else
    {
        seed_reason = "few_rptsc1";
    }

    if(!seed_mode_dynamic)
    {
        if(rpts1s_num > 10){
            inv_Lpt1_found[0] = 80;
            inv_Lpt1_found[1] = 105;
        }
        else{
            inv_Lpt1_found[0] = 110;
            inv_Lpt1_found[1] = 105;
        }
        if(circle_cal_log_enabled())
        {
            printf("ATGCircleOutSeed: mode=fixed circle=%s rptsc1=%d rpts1s=%d "
                   "raw=%.1f,%.1f reason=%s\n",
                   circle_type_name[circle_type], rptsc1_num, rpts1s_num,
                   inv_Lpt1_found[0], inv_Lpt1_found[1],
                   seed_reason);
        }
    }
}

/* 右远线 seed：从近端 L 角点偏移得到搜索起点。
 * 三种情况：正常 / 左圆环出环 / 边线丢失 */
static int far_r_seed()
{
    if (Lpt1_found&&Lpt1_rpts1s_id>2&&!if_lost_right_line) {
        inv_Lpt1_found[0] = Cal_inv_rot_x(rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][0],rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][1])+5;
        inv_Lpt1_found[1] = Cal_inv_rot_y(rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][0],rpts1s[clip(Lpt1_rpts1s_id,0,rpts1s_num-1)][1])-17;
        rptsc1_num = rpts1s_num = Lpt1_rpts1s_id ;
        return 1;
    }
    else if(circle_type== CIRCLE_LEFT_OUT&&!garage_type){
        far_r_seed_circle_out();
        return 1;
    }
    else if(rpts1s_num<2){
        if_lost_right_line = 1;
        inv_Lpt1_found[0] = 160;
        inv_Lpt1_found[1] = begin_y-5;
        return 1;
    }

    return 0;
}

static void far_r_show_seed()
{
    if(DisPlay_Flag&&!thres)
        {
            if(3<(inv_Lpt1_found[0]/X_zoom)&&(inv_Lpt1_found[0]/X_zoom)<101&&3<(inv_Lpt1_found[1]/Y_zoom)&&(inv_Lpt1_found[1]/Y_zoom)<64) for(int i=-2;i<3;i++)for(int j=-2;j<3;j++)lcd_drawpoint((int)(inv_Lpt1_found[0]+i)/X_zoom,(int)(inv_Lpt1_found[1]+j)/Y_zoom,RED);
        }
}

static int far_r_scan()
{
    far_y1 = 0, far_y2 = 0;
    int y1 = clip((int)inv_Lpt1_found[1], block_size/2 + 1, MT9V03X_H - block_size/2 - 1);
    far_x11 = clip((int)inv_Lpt1_found[0], block_size/2, MT9V03X_W - block_size/2 - 1);
    far_ipts1_num = sizeof(far_ipts1) / sizeof(far_ipts1[0]);

    int local_thres_right_up = 0;
    for (; y1 > block_size/2; y1--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x11, y1-1) < OSTU_thres) {
            break;
        }
    }
         for (; y1 > block_size/2; y1--) {


             local_thres_right_up = 0;
             for (int dy = -block_size/2; dy <= block_size/2; dy++) {
                 for (int dx = -block_size/2; dx <= block_size/2; dx++) {
                     local_thres_right_up += AT_IMAGE(&img_raw, far_x11 + dx, y1 + dy);
                 }
             }
             local_thres_right_up /= block_size * block_size;
             local_thres_right_up -= clip_value;

             if (AT_IMAGE(&img_raw, far_x11 , y1 - 1 ) < local_thres_right_up)
             {
                 far_y1 = y1;
                 break;
             }
         }
    far_r_thres = local_thres_right_up;
    return far_y1 > block_size/2;
}

static void far_r_trace()
{
         //从找到角点位置开始寻找
         if (far_y1 > block_size/2 && AT_IMAGE(&img_raw, far_x11, far_y1 -1) < far_r_thres)
        findline_righthand_adaptive(&img_raw, block_size, clip_value, far_x11, far_y1 , far_ipts1, &far_ipts1_num);
         else far_ipts1_num = 0;
}

static void far_r_ipm()
{
    // 去畸变+透视变换
    for(int i=0;i<far_ipts1_num;i++)
    {
        far_rpts1[i][0] = (rot[1][0]*far_ipts1[i][1]+rot[1][1]*far_ipts1[i][0]+rot[1][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_x;
        far_rpts1[i][1] = (rot[0][0]*far_ipts1[i][1]+rot[0][1]*far_ipts1[i][0]+rot[0][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_y;

    }

    far_rpts1_num = far_ipts1_num;
}

static void far_r_proc()
{
    // 边线滤波
    blur_points(far_rpts1, far_rpts1_num, far_rpts1b, (int) round(line_blur_kernel));
    far_rpts1b_num = far_rpts1_num;

    // 边线等距采样
    far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);
    resample_points(far_rpts1b, far_rpts1b_num, far_rpts1s, &far_rpts1s_num, sample_dist * pixel_per_meter);
    //far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);


    // 边线局部角度变化率
    local_angle_points(far_rpts1s, far_rpts1s_num, far_rpts1a, (int) round(angle_dist / sample_dist));
    far_rpts1a_num = far_rpts1s_num;

    // 角度变化率非极大抑制
    nms_angle(far_rpts1a, far_rpts1a_num, far_rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts1an_num = far_rpts1a_num;
}

static void far_r_find_lpt()
{
    // 找远线上的L角点


    far_Lpt1_found = false;
    for (int i = 0; i < MIN(far_rpts1s_num, 70); i++) {
        if (far_rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        conf4 = fabs(far_rpts1a[i]) - (fabs(far_rpts1a[im1]) + fabs(far_rpts1a[ip1])) / 2;
        if (50. / 180. * PI < conf4 && conf4 < 140. / 180. * PI&&i<40 &&far_rpts1s[i][0]>=far_rpts1s[ip1][0]&&i>1&&far_rpts1s[i][1]>=far_rpts1s[ip1][1]&&far_rpts1s[im1][0]>=far_rpts1s[ip1][0]) {
            far_Lpt1_rpts1s_id = i;
            far_Lpt1_found = true;
            inv_far_Lpt1_found[0] = Cal_inv_rot_x(far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][0],far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][1]);
            inv_far_Lpt1_found[1] = Cal_inv_rot_y(far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][0],far_rpts1s[clip(far_Lpt1_rpts1s_id,0,far_rpts1s_num-1)][1]);
            break;
        }
        if(conf4>conf4_max)conf4_max = conf4;
    }


}


/* 右远线搜索完整链：与左远线对称 */
void cross_farline_R()
{
    far_Lpt1_found = false;
    far_r_cut_left();
    if (!far_r_seed()) return;
    far_r_show_seed();
    if (!far_r_scan()) return;
    far_r_trace();
    far_r_ipm();
    far_r_proc();
    far_r_find_lpt();
}



/* ================= 双侧远线搜索（IN 阶段用） ================= */

/* 双侧远线搜索：
 * 从画面左右两侧固定位置开始，同时搜索左右远线。
 * 用于 CROSS_IN 阶段，与 cross_farline_L/R（HALF 阶段用）不同。 */
void cross_farline() {
    int cross_width = 4;
//    far_x1 = cross_width, far_x2 = img_raw.width -cross_width;
    far_y1 = 0, far_y2 = 0;
//    int x1 = img_raw.width / 2 - begin_x
    int y1 = begin_y;
    bool white_found = false;
    far_ipts0_num = sizeof(far_ipts0) / sizeof(far_ipts0[0]);

    //在begin_y向两边找黑线
//    for(;x1>cross_width*2; x1--)
//    {
//      if(AT_IMAGE(&img_raw, x1-1, y1) < low_thres) {
//        far_x1 = x1 - cross_width;
//        break;
//      }
//    }
    //全白  far_x1 = 0,从边界找
    for (; y1 > 0; y1--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x1, y1) >= thres) { white_found = true; }
        if (AT_IMAGE(&img_raw, far_x1, y1) < thres && (white_found || far_x1 == cross_width)) {
            far_y1 = y1;
            break;
        }
    }

    //从找到角点位置开始寻找
    if (AT_IMAGE(&img_raw, far_x1, far_y1 + 1) >= thres)
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, far_x1, far_y1 + 1, far_ipts0, &far_ipts0_num);
    else far_ipts0_num = 0;

    //int x2 = img_raw.width / 2 + begin_x,
    int y2 = begin_y;
    white_found = false;
    far_ipts1_num = sizeof(far_ipts1) / sizeof(far_ipts1[0]);

    //在begin_y向两边找黑线
//    for(;x2<img_raw.width-cross_width*2; x2++)
//    {
//      if(AT_IMAGE(&img_raw, x2+1, y2) < low_thres) {
//        far_x2 = x2 + cross_width;
//        break;
//      }
//    }
    //全白  far_x2 = 0,从边界找
    for (; y2 > 0; y2--) {
        //先黑后白，先找white
        if (AT_IMAGE(&img_raw, far_x2, y2) >= thres) { white_found = true; }
        if (AT_IMAGE(&img_raw, far_x2, y2) < thres && (white_found || far_x2 == img_raw.width - cross_width)) {
            far_y2 = y2;
            break;
        }
    }

    //从找到角点位置开始寻找
    if (AT_IMAGE(&img_raw, far_x2, far_y2 + 1) >= thres)
        findline_righthand_adaptive(&img_raw, block_size, clip_value, far_x2, far_y2 + 1, far_ipts1, &far_ipts1_num);

    else far_ipts1_num = 0;

    // 去畸变+透视变换
    for(int i=0;i<far_ipts0_num;i++)
    {
        far_rpts0[i][0] = (rot[1][0]*far_ipts0[i][1]+rot[1][1]*far_ipts0[i][0]+rot[1][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_x;
        far_rpts0[i][1] = (rot[0][0]*far_ipts0[i][1]+rot[0][1]*far_ipts0[i][0]+rot[0][2])/(rot[2][0]*far_ipts0[i][1]+rot[2][1]*far_ipts0[i][0]+1.0)+delta_y;

    }
    for(int i=0;i<far_ipts1_num;i++)
    {
        far_rpts1[i][0] = (rot[1][0]*far_ipts1[i][1]+rot[1][1]*far_ipts1[i][0]+rot[1][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_x;
        far_rpts1[i][1] = (rot[0][0]*far_ipts1[i][1]+rot[0][1]*far_ipts1[i][0]+rot[0][2])/(rot[2][0]*far_ipts1[i][1]+rot[2][1]*far_ipts1[i][0]+1.0)+delta_y;

    }
    far_rpts0_num = far_ipts0_num;
    far_rpts1_num = far_ipts1_num;

    // 边线滤波
    blur_points(far_rpts0, far_rpts0_num, far_rpts0b, (int) round(line_blur_kernel));
    far_rpts0b_num = far_rpts0_num;
    blur_points(far_rpts1, far_rpts1_num, far_rpts1b, (int) round(line_blur_kernel));
    far_rpts1b_num = far_rpts1_num;

    // 边线等距采样
    far_rpts0s_num = sizeof(far_rpts0s) / sizeof(far_rpts0s[0]);
    resample_points(far_rpts0b, far_rpts0b_num, far_rpts0s, &far_rpts0s_num, sample_dist * pixel_per_meter);
    far_rpts1s_num = sizeof(far_rpts1s) / sizeof(far_rpts1s[0]);
    resample_points(far_rpts1b, far_rpts1b_num, far_rpts1s, &far_rpts1s_num, sample_dist * pixel_per_meter);


    // 边线局部角度变化率
    local_angle_points(far_rpts0s, far_rpts0s_num, far_rpts0a, (int) round(angle_dist / sample_dist));
    far_rpts0a_num = far_rpts0s_num;
    local_angle_points(far_rpts1s, far_rpts1s_num, far_rpts1a, (int) round(angle_dist / sample_dist));
    far_rpts1a_num = far_rpts1s_num;

    // 角度变化率非极大抑制
    nms_angle(far_rpts0a, far_rpts0a_num, far_rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts0an_num = far_rpts0a_num;
    nms_angle(far_rpts1a, far_rpts1a_num, far_rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);
    far_rpts1an_num = far_rpts1a_num;

    // 找远线上的L角点

    far_Lpt0_found = far_Lpt1_found = false;
    for (int i = 0; i < MIN(far_rpts0s_num, 40); i++) {
        if (far_rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts0s_num - 1);
        float conf = fabs(far_rpts0a[i]) - (fabs(far_rpts0a[im1]) + fabs(far_rpts0a[ip1])) / 2;
        if (60. / 180. * PI < conf && conf < 140. / 180. * PI && i < 100) {
            far_Lpt0_rpts0s_id = i;
            far_Lpt0_found = true;
            break;
        }
    }
    for (int i = 0; i < MIN(far_rpts1s_num, 70); i++) {
        if (far_rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, far_rpts1s_num - 1);
        float conf = fabs(far_rpts1a[i]) - (fabs(far_rpts1a[im1]) + fabs(far_rpts1a[ip1])) / 2;

        if (60. / 180. * PI < conf && conf < 140. / 180. * PI && i < 100) {
            far_Lpt1_rpts1s_id = i;
            far_Lpt1_found = true;
            break;
        }
    }

#if If_DisPlay
    lcd_showint8(70 ,6,far_Lpt0_found);
    lcd_showint8(105,6,far_Lpt1_found);
#endif
}
