/* =====================================================================
 *  圆环检测模块接口（circle）
 *
 *  状态机：
 *    NONE → ENTRY → BEGIN → RUNNING → OUT → NONE
 *
 *  锚点：
 *    A = 入口近端拐点（L 角点）
 *    B = 圆环外侧远端极值点（从 A 出发追线找到）
 *    C = 圆环最深处拐点（从 B 出发向上找）
 * ===================================================================== */
#ifndef CIRCLE_H
#define CIRCLE_H

/* 圆环状态枚举 */
enum circle_type_e {
    CIRCLE_NONE = 0,                            /* 无圆环 */
    CIRCLE_LEFT_ENTRY, CIRCLE_RIGHT_ENTRY,      /* ENTRY：A 点已锁定，正在找 B */
    CIRCLE_LEFT_BEGIN, CIRCLE_RIGHT_BEGIN,      /* BEGIN：B 已确认，正在找 C */
    CIRCLE_LEFT_RUNNING, CIRCLE_RIGHT_RUNNING,  /* RUNNING：环内行驶 */
    CIRCLE_LEFT_OUT, CIRCLE_RIGHT_OUT,          /* OUT：出环过渡 */
    CIRCLE_NUM,                                 /* 状态总数 */
};

/* 圆环参考模式：决定选线来源 */
enum circle_ref_mode_e {
    CIRCLE_REF_NONE = 0,
    CIRCLE_REF_BEGIN_AB,    /* BEGIN 阶段用普通外侧线兜底（C 未确认时） */
    CIRCLE_REF_IN_C,        /* BEGIN 阶段用 C 点补线（C 已确认） */
};

/* 圆环锚点结构体：A/B/C 点的坐标和状态 */
typedef struct circle_anchor_point_s {
    int found;      /* 是否找到 */
    int id;         /* 在 rptss 数组中的索引 */
    int raw_x;      /* 原图 x 坐标 */
    int raw_y;      /* 原图 y 坐标 */
} circle_anchor_point_t;

/* 状态名称表（用于日志） */
extern const char *circle_type_name[CIRCLE_NUM];

/* 当前圆环状态 */
extern enum circle_type_e circle_type;

/* 当前参考模式 */
extern enum circle_ref_mode_e circle_ref_mode;

/* A/B/C 锚点 */
extern circle_anchor_point_t circle_A_point;
extern circle_anchor_point_t circle_B_point;
extern circle_anchor_point_t circle_C_point;

/* 丢线计数：none_left/right_line > 0 表示对应侧边线丢失 */
extern int none_left_line, none_right_line;

/* 有线标记（废弃，不再用于状态推进） */
extern int have_left_line, have_right_line;

/* 圆环计数 */
extern int circle_count;

/* 左右环自然线点数 */
extern int round_cirlce_left_num, round_cirlce_right_num;

/* ================= 接口函数 ================= */

/* 圆环检测入口：检测 A 点，确认进入 ENTRY */
void check_circle();

/* 重置 ENTRY 投票状态 */
void reset_circle_entry_votes();

/* 抑制圆环检测指定帧数 */
void suppress_circle_entry_frames(int frames);

/* 出环后抑制重新进入（防止立即重新触发） */
void suppress_circle_reentry_after_exit(void);

/* 清除 ENTRY 抑制 */
void clear_circle_entry_suppression(void);

/* 重置 BEGIN 阶段标记 */
void reset_circle_begin_flags();

/* 重置圆环几何状态（A/B/C 点） */
void reset_circle_geometry_state(void);

/* 更新圆环航向角（陀螺仪积分） */
void update_circle_heading(float yaw_rate_rad_s, int period_ms, int valid);

/* 圆环调试日志是否启用 */
int circle_cal_log_enabled(void);

/* 圆环入口 inner-hit 种子坐标（供 assistant 显示线复用）
 * left_side: 1=左环, 0=右环
 * 返回 1 表示有效 */
int circle_entry_inner_seed(int left_side, int *seed_x, int *seed_y,
                            float *seed_raw_x, float *seed_raw_y);

/* 圆环主流程：处理 ENTRY/BEGIN/RUNNING/OUT 各阶段 */
void run_circle();

/* 圆环绘制（调试用） */
void draw_circle();

#endif /* CIRCLE_H */
