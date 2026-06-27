/* =====================================================================
 *  半十字检测（Half_check）
 *
 *  半十字是指只有单侧出现 L 角点 + 远端边线的情况（另一侧正常）。
 *  与全十字的区别：全十字两侧都有 L 角点，半十字只有一侧。
 *
 *  检测流程：
 *    1. check_Half()          — 入口，根据 Lpt0/Lpt1_found 选择左右检测
 *    2. check_Half_left()     — 左侧半十字检测
 *    3. check_Half_right()    — 右侧半十字检测
 *
 *  每侧检测步骤：
 *    1. 搜索远端边线（cross_farline_L/R）
 *    2. 验证远端 L 角点与近端 L 角点的距离合理性
 *    3. 判断远端边线是否为直道（回环标志检查）
 *    4. 条件满足则标记 CROSS_HALF，否则回滚近线状态
 *
 *  与圆环的关系：check_circle() 优先级更高，check_Half() 只在圆环未激活时运行。
 *  半十字不会抢占圆环已认领的角点。
 * ===================================================================== */
#include "Half_check.h"

/* ================= 全局变量 ================= */

/* 远端右线端点坐标 */
float Far_rLine_endpoint_x, Far_rLine_endpoint_y;
/* 近端右线端点坐标 */
float near_rLine_endpoint_x, near_rLine_endpoint_y;
/* 反投影斜率点（右/左） */
float inv_Slope_point_R[2], inv_Slope_point_L[2];
/* 车库检测相关变量 */
int find_garage_left_x, find_garage_left_y;
int find_garage_white = 1, find_garage_black;
int find_garage_num, find_garage_change_num;
int find_garage;

///

#define PI               3.14159265358979f
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)

/* ================= 近线快照：用于检测失败时回滚 ================= */

/* 近线快照：保存 rpts0s/rpts1s/rptsc0/rptsc1 的点数。
 * 检测前保存，检测失败时恢复，防止远端搜线过程污染近线数据。 */
typedef struct half_near_snapshot_s
{
    int rpts0s_num;
    int rpts1s_num;
    int rptsc0_num;
    int rptsc1_num;
} half_near_snapshot_t;

static void half_save_near_snapshot(half_near_snapshot_t *snapshot)
{
    snapshot->rpts0s_num = rpts0s_num;
    snapshot->rpts1s_num = rpts1s_num;
    snapshot->rptsc0_num = rptsc0_num;
    snapshot->rptsc1_num = rptsc1_num;
}

static void half_restore_near_snapshot(const half_near_snapshot_t *snapshot)
{
    rpts0s_num = snapshot->rpts0s_num;
    rpts1s_num = snapshot->rpts1s_num;
    rptsc0_num = snapshot->rptsc0_num;
    rptsc1_num = snapshot->rptsc1_num;
}

/* ================= 半十字检测入口 ================= */

/* 半十字检测入口：根据 Lpt0/Lpt1_found 选择左右检测。
 * 圆环优先：circle_type != CIRCLE_NONE 时直接返回。
 * 左侧 L 角点存在且左侧线多于右侧 → 尝试左半十字；
 * 右侧 L 角点存在且右侧线多于左侧 → 尝试右半十字。 */
void check_Half()
{
    if(circle_type != CIRCLE_NONE) return;
    if(Lpt0_found && rpts0s_num > rpts1s_num)
    {
        if(check_Half_left()) return;
    }
    if(Lpt1_found && rpts1s_num > rpts0s_num)
    {
        (void)check_Half_right();
    }
}

/* ================= 左侧半十字检测 ================= */

/* 左侧半十字检测：
 *
 * 检测步骤：
 *   1. 搜索左远端边线（cross_farline_L）
 *   2. 验证远端 L 与近端 L 的距离（应在 0.35m 附近，容差 0.35m）
 *   3. 判断远端边线是否为直道（点数够多、回环标志检查）
 *   4. 条件满足 → 标记 CROSS_HALF，返回 1
 *   5. 不满足 → 回滚近线状态，返回 0
 *
 * 判断条件：
 *   - 远端 L 角点存在（far_Lpt0_found）
 *   - 近端 L 角点存在且 id < 10（L 点在近端，不是远端弯曲）
 *   - 近端不是直道（!is_straight1）——直道不会出现真正的半十字
 *   - 圆环未激活（circle_type == CIRCLE_NONE）
 *
 * 返回：1 表示检测到半十字，0 表示未检测到。 */
int check_Half_left()
{
    half_near_snapshot_t snapshot;
    int commit_half = 0;
    half_save_near_snapshot(&snapshot);

    /* 步骤 1：搜索左远端边线 */
    cross_farline_L();

    /* 步骤 2：L 点距离检查——远端 L 与近端 L 的距离应在 0.35m 附近。
     * 距离太远说明远端 L 不是对应这个近端 L 的十字对角。 */
    if(far_Lpt0_found && Lpt0_found)
    {
        float dx = far_rpts0s[far_Lpt0_rpts0s_id][0] - rpts0s[Lpt0_rpts0s_id][0];
        float dy = far_rpts0s[far_Lpt0_rpts0s_id][1] - rpts0s[Lpt0_rpts0s_id][1];
        float dn = sqrtf(dx * dx + dy * dy);
        if(fabs(dn - 0.35 * pixel_per_meter) > 0.35 * pixel_per_meter) far_Lpt0_found = false;
    }

    /* 步骤 3：判断远端边线是否为直道。
     * is_straight_far_0 需要同时满足：
     *   - 远端边线点数足够（> 0.55m）
     *   - 远端原始线回环（首尾接近）
     *   - 远端原始线不回绕（首尾 y 方向合理） */
    is_straight_far_0 = far_rpts0s_num > (0.55 / sample_dist);

    /* 回环标志检查：远端原始线首尾 x 坐标应在合理范围，
     * 且首尾 y 方向不回绕（远端线从左到右应该是单调的） */
    if(far_ipts0_num < 6 || far_ipts0[far_ipts0_num - 5][0] < 130 || far_ipts0[5][0] > 50 || far_ipts0[far_ipts0_num - 2][1] > far_ipts0[0][1])
        is_straight_far_0 = false;

    /* 回环距离检查：远端线首尾距离应接近 0.35m（十字对角线长度）。
     * 如果首尾太近，说明远端线回绕了，不是真正的十字远端。 */
    if(far_rpts0s_num > 15 && far_ipts0_num >= 6)
    {
        float dx = far_ipts0[5][0] - far_ipts0[far_ipts0_num - 5][0];
        float dy = far_ipts0[5][1] - far_ipts0[far_ipts0_num - 5][1];
        float dn = sqrtf(dx * dx + dy * dy);
        if(fabs(dn - 0.35 * pixel_per_meter) < 0.10 * pixel_per_meter)
        {
            is_straight_far_0 = false;
        }
    }

    /* 步骤 4：判定半十字。
     * 条件：远端 L 存在 + 圆环未激活 + 近端不是直道 + L 点在近端（id<10）
     * 虽然找到了同一个方向的 90 度端点，但没找到近端直道，可能是转弯十字 */
    if(far_Lpt0_found && circle_type == CIRCLE_NONE && !is_straight1 && Lpt0_rpts0s_id < 10)
    {
        commit_half = 1;
        cross_type = CROSS_HALF;
        garage_type = GARAGE_NONE;
        /* 标记找到半十字或全十字 */
        Lpt0_found_flag = 1;
    }
    /* Circle entry is owned by check_circle(); Half_check only claims CROSS_HALF. */

    /* 步骤 5：未检测到半十字则回滚近线状态，防止远端搜线污染近线 */
    if(!commit_half)
    {
        half_restore_near_snapshot(&snapshot);
        clear_cross_farline_outputs();
    }
    return commit_half;
}

/* ================= 右侧半十字检测 ================= */

/* 右侧半十字检测：逻辑与左侧镜像对称。
 *
 * 与左侧的差异：
 *   - 远端 L 距离容差略小（0.30m vs 0.35m）
 *   - 远端直道判断阈值略小（0.45m vs 0.55m）
 *   - 回环距离检查用 0.20m（右侧远端线形状略有不同）
 *   - 回环标志检查的 x/y 方向与左侧镜像
 *
 * 返回：1 表示检测到半十字，0 表示未检测到。 */
int check_Half_right() /* 右侧同理 */
{
    half_near_snapshot_t snapshot;
    int commit_half = 0;
    half_save_near_snapshot(&snapshot);

    /* 步骤 1：搜索右远端边线 */
    cross_farline_R();

    /* 步骤 2：L 点距离检查 */
    if(far_Lpt1_found && Lpt1_found)
    {
        float dx = far_rpts1s[far_Lpt1_rpts1s_id][0] - rpts1s[Lpt1_rpts1s_id][0];
        float dy = far_rpts1s[far_Lpt1_rpts1s_id][1] - rpts1s[Lpt1_rpts1s_id][1];
        float dn = sqrtf(dx * dx + dy * dy);
        if(fabs(dn - 0.35 * pixel_per_meter) > 0.30 * pixel_per_meter) far_Lpt1_found = false;
    }

    /* 步骤 3：判断远端边线是否为直道 */
    is_straight_far_1 = far_rpts1s_num > (0.45 / sample_dist);

    /* 回环标志检查 */
    if(far_ipts1_num < 6 || far_ipts1[far_ipts1_num - 3][0] > 10 || far_ipts1[5][0] < 50 || (far_ipts1[far_ipts1_num - 1][1] < far_ipts1[0][1]))
        is_straight_far_1 = false;

    /* 回环距离检查 */
    if(far_rpts1s_num > 15 && far_ipts1_num >= 6)
    {
        float dx = far_ipts1[5][0] - far_ipts1[far_ipts1_num - 5][0];
        float dy = far_ipts1[5][1] - far_ipts1[far_ipts1_num - 5][1];
        float dn = sqrtf(dx * dx + dy * dy);
        if(fabs(dn - 0.20 * pixel_per_meter) < 0.10 * pixel_per_meter)
        {
            is_straight_far_1 = false;
        }
    }

    /* 步骤 4：判定半十字 */
    if(far_Lpt1_found && circle_type == CIRCLE_NONE && !is_straight0 && Lpt1_rpts1s_id < 10)
    {
        commit_half = 1;
        cross_type = CROSS_HALF;
        garage_type = GARAGE_NONE;
        /* 标记找到半十字或全十字 */
        Lpt1_found_flag = 1;
    }
    /* Circle entry is owned by check_circle(); Half_check only claims CROSS_HALF. */

    /* 步骤 5：未检测到则回滚 */
    if(!commit_half)
    {
        half_restore_near_snapshot(&snapshot);
        clear_cross_farline_outputs();
    }
    return commit_half;
}
