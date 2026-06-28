/* =====================================================================
 *  Y 路检测（yroad）
 *
 *  Y 路是指分叉路口，车辆需要选择左或右分支。
 *  当前状态：默认关闭（ATG_ENABLE_YROAD=0），需要时由 vision_step.c 统一启用。
 *
 *  状态机：
 *    YROAD_NONE  → YROAD_FOUND  → YROAD_NEAR  → YROAD_LEFT/RIGHT_RUN
 *                                                    ↓
 *                                            YROAD_LEFT/RIGHT_OUT → YROAD_NONE
 *
 *  检测依据：Ypt0/Ypt1_found（Y 形角点）
 *  选择逻辑：根据 yroad_cnt 奇偶性交替选择左右分支
 * ===================================================================== */
#include "yroad.h"
#include "headfile.h"

/* ================= 全局状态 ================= */

enum yroad_type_e yroad_type = YROAD_NONE;

/* 记录第几次经过 Y 路：用于交替选择左右分支 */
int8 yroad_cnt = 0;

/* ================= Y 路检测入口 ================= */

/* 检测 Y 路：Ypt0 或 Ypt1 存在时标记 YROAD_FOUND。
 * 仅在 YROAD_NONE 状态下触发，防止重复触发。 */
void check_yroad(void)
{
    bool y_found = Ypt0_found || Ypt1_found;

    /* 状态切换：发现 Y 角点 → YROAD_FOUND */
    if(yroad_type == YROAD_NONE && y_found)
    {
        yroad_type = YROAD_FOUND;
        Count_dis_Flag = 1;
    }
}

/* ================= Y 路主流程 ================= */

/* Y 路主流程：处理 YROAD_FOUND/NEAR/RUN/OUT 各阶段的状态切换。
 *
 * FOUND/NEAR 阶段：
 *   - 等待 Y 角点靠近（Ypt id < 0.6m 对应的点数）
 *   - 根据 if_check_ramp 和 yroad_cnt 奇偶性选择跟踪左线或右线
 *   - 行驶超过 6500 counts 且 Y 角点消失 → 进入 RUN 阶段
 *
 * RUN 阶段：
 *   - 等待 Y 角点再次出现 → 进入 OUT 阶段
 *
 * OUT 阶段：
 *   - 行驶超过 4000 counts 且 Y 角点消失 → 回到 NONE
 */
void run_yroad(void)
{
    bool y_found = Ypt0_found || Ypt1_found;

    /* FOUND/NEAR 阶段：等待靠近并选择分支 */
    if(yroad_type == YROAD_FOUND || yroad_type == YROAD_NEAR)
    {
        aim_distance = AIM_DISTENCE;

        /* Y 角点足够近 → 进入 NEAR */
        if(y_found && (Ypt0_rpts0s_id < 0.6 / sample_dist || Ypt1_rpts1s_id < 0.6 / sample_dist))
        {
            yroad_type = YROAD_NEAR;
        }

        /* 根据坡道状态和 yroad_cnt 奇偶性选择跟踪线 */
        if(if_check_ramp)
        {
            if(yroad_cnt % 2 == 0) track_type = TRACK_LEFT;
            else track_type = TRACK_LEFT;
        }
        else
        {
            if(yroad_cnt % 2 == 0) track_type = TRACK_RIGHT;
            else track_type = TRACK_LEFT;
        }

        /* 行驶超过 6500 counts 且 Y 角点消失 → 进入 RUN 阶段 */
        if(total_distence >= 6500 && !y_found)
        {
            Count_dis_Flag = 0;
            if(if_check_ramp)
            {
                if(yroad_cnt % 2 == 0) yroad_type = YROAD_LEFT_RUN;
                else yroad_type = YROAD_LEFT_RUN;
            }
            else
            {
                if(yroad_cnt % 2 == 0) yroad_type = YROAD_RIGHT_RUN;
                else yroad_type = YROAD_LEFT_RUN;
            }

            yroad_cnt++;
        }
    }
    /* LEFT_RUN 阶段：Y 角点再次出现 → 进入 LEFT_OUT */
    else if(yroad_type == YROAD_LEFT_RUN && y_found)
    {
        yroad_type = YROAD_LEFT_OUT;
        Count_dis_Flag = 1;
    }
    /* RIGHT_RUN 阶段：Y 角点再次出现 → 进入 RIGHT_OUT */
    else if(yroad_type == YROAD_RIGHT_RUN && y_found)
    {
        yroad_type = YROAD_RIGHT_OUT;
        Count_dis_Flag = 1;
    }
    /* LEFT_OUT 阶段：行驶超过 4000 counts 且 Y 角点消失 → 回到 NONE */
    else if(yroad_type == YROAD_LEFT_OUT && !y_found && total_distence >= 4000)
    {
        yroad_type = YROAD_NONE;
        begin_y = BEGIN_Y;
        Count_dis_Flag = 0;
    }
    /* RIGHT_OUT 阶段：行驶超过 4000 counts 且 Y 角点消失 → 回到 NONE */
    else if(yroad_type == YROAD_RIGHT_OUT && !y_found && total_distence >= 4000)
    {
        yroad_type = YROAD_NONE;
        begin_y = BEGIN_Y;
        Count_dis_Flag = 0;
    }

    /* RUN/OUT 阶段强制选择对应方向的线 */
    if(yroad_type == YROAD_LEFT_RUN || yroad_type == YROAD_LEFT_OUT)
    {
        track_type = TRACK_LEFT;
    }
    else if(yroad_type == YROAD_RIGHT_RUN || yroad_type == YROAD_RIGHT_OUT)
    {
        track_type = TRACK_RIGHT;
    }
}
