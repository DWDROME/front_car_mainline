#pragma once

#include <cstdint>

// 坐标约定：x 向右增大，y 向下增大。
// 运行时所有搜线、角点、逆透视坐标都统一按 160x120 解释。
// device 层不再替高分辨率输入做隐式 resize；尺寸不匹配时直接失败。
// 不要把非 160x120 的像素坐标直接喂给 tracking，否则矩阵和角点基准会错位。
enum
{
    // 主流程内部使用的原图尺寸，不等于传感器必须输出的物理分辨率。
    RAW_W = 160,
    RAW_H = 120,

    // 俯视图尺寸，当前保持和原图一致，便于调试对照。
    IPM_W = 160,
    IPM_H = 120,

    // 单条边界或中线最多保留的点数。
    POINT_MAX = 160,

    // 图像几何中心列。
    // 它仍然用于原图几何、seed 起搜和部分调试统计，但不再直接等同于控车参考中心。
    // Front_Car 原版用的是 188 宽图，所以默认 mid_position=94 正好居中。
    // 我们现在主流程内部已经统一成 160 宽，如果这里还保留 94，
    // 起搜中心会系统性右偏，右侧强边更容易被误吸成主入口。
    MID_X = RAW_W / 2,

    // 当前这套车模 + 相机安装位的实机验证结果表明：
    // 控制参考中心和图像几何中心解耦。上一版用 87，2026-06 根据 IPM_DBG
    // 实测路面中心约 86px，默认按当前硬件标定值取 86。
    CONTROL_CENTER_X = 86,

    // 固定起线行，按参考版 begin_y 语义优先在靠近车头的位置找左右边界种子。
    START_HIGH = 116,

    // 斑马线等纵向扫描的上边界；不再用于种子向上补搜。
    MINI_HIGH = 60,

    // 判直道等几何逻辑时使用的最小有效步数基准。
    STEP_MAX = 40,

    // 半赛道宽，用单边边界外扩生成中线。
    // 旧值 20 偏窄；2026-06 根据 IPM_DBG 实测路面宽约 52px，半宽取 26。
    ROAD_HALF_WIDTH = 26,

    // 预瞄距离，按控制中线累计弧长选取目标点算转向误差。
    // ATG 参考控制使用 aim_distance_far=0.58m，当前 pixel_per_meter=116，
    // 折算约 67px。旧值 35px 太靠近被 ATG 归一化强行钉到 cx/cy 的近端锚点，
    // 斜车身入弯时会把假横移当成真实中线趋势。
    LOOKAHEAD_DIST = 67,

    // 八邻域搜线至少要走到这个步数，才认为边界有效。
    TRACE_MIN_STEP = 6,

    // 预留给后续曲率类状态机的阈值。
    CURVE_THRESHOLD = 18
};

struct point_t
{
    // 坐标统一按当前运行时图像解释：x 向右，y 向下。
    int x;
    int y;
};

struct midline_t
{
    // 控制中线点列，语义是 ATG IPM/控制坐标；不是 assistant 原图红线。
    point_t pts[POINT_MAX];

    // dist[i] 是从 pts[0] 到 pts[i] 的累计近似弧长，lookahead_error 按它选预瞄点。
    int dist[POINT_MAX];
    int step;
};

struct vision_state_t
{
    // 只保留控制层和外围输出真正需要的 ATG 当前帧薄结果。
    int line_found;
    point_t control_ref;
    midline_t mid;
    double guide_error;
};

struct control_state_t
{
    // 控制输出状态。yaw-rate 单位为 mrad/s，duty 单位按 drive_output 的 PWM 占空比解释。
    int input_valid;
    int stop_request;
    int target_yaw_rate_mrad_s;
    int yaw_cmd_mrad_s;
    int actual_yaw_rate_mrad_s;
    int left_target_rps_milli;
    int right_target_rps_milli;
    int left_actual_rps_milli;
    int right_actual_rps_milli;
    int signed_output;
    int left_duty;
    int right_duty;
};

struct control_input_t
{
    // 控制层需要的当前帧视觉输入，由 runner 从当前 ATG step 结果生成。
    int line_found;
    int stop_line;
    int element_active;
    int fixed_yaw_rate_valid;
    int fixed_yaw_rate_mrad_s;
    int spin_mode;
    double guide_error;
};

struct control_feedback_t
{
    // 一个控制周期内的编码器增量和 IMU yaw-rate 反馈。
    int left_speed_count;
    int right_speed_count;
    int actual_yaw_rate_mrad_s;
    int actual_yaw_rate_valid;
    int period_ms;
};

struct runtime_t
{
    // 输入图像与 ATG 距离状态。ATG 算法状态由 atg_reference 自己的全局变量维护。
    uint8_t gray[RAW_H][RAW_W];
    int gray_valid;
    int64_t encoder_total;

    // 控制参考中心来自本车标定；不是 ATG 算法内的 seed 搜索中心。
    int control_center_x;

    vision_state_t vision;
    control_state_t control;
};
