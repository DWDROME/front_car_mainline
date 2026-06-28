/* =====================================================================
 *  十字检测模块接口（cross）
 *
 *  状态机：NONE → BEGIN → IN → HALF
 *
 *  检测依据：近端 L 角点 + 远端 L 角点同时出现
 *  远线搜索：从近端 L 角点出发，向远端追线，生成十字中心线
 * ===================================================================== */
#ifndef CROSS_H
#define CROSS_H
#include "headfile.h"

/* 十字状态枚举 */
enum cross_type_e {
    CROSS_NONE = 0,     /* 非十字模式 */
    CROSS_BEGIN,        /* 找到左右两个 L 角点 */
    CROSS_IN,           /* 两个 L 角点很近，进入十字内部（切换远线控制） */
    CROSS_HALF,         /* 半十字：只有单侧 L 角点 + 远端边线 */
    CROSS_NUM
};

/* 当前十字状态 */
extern enum cross_type_e cross_type;

/* 状态名称表（用于日志） */
extern const char *cross_type_name[CROSS_NUM];

/* ================= 接口函数 ================= */

/* 十字主流程 */
void run_cross(void);

/* 左远端边线搜索 */
void cross_farline_L(void);

/* 右远端边线搜索 */
void cross_farline_R(void);

/* 清除远端边线输出 */
void clear_cross_farline_outputs(void);

/* ================= 远端角点状态 ================= */

/* 远端 L 角点是否找到 */
extern _Bool far_Lpt0_found, far_Lpt1_found;

/* 远端 L 角点在远端边线数组中的索引 */
extern int far_Lpt0_rpts0s_id, far_Lpt1_rpts1s_id;

/* 丢线标记 */
extern uint8 if_lost_left_line, if_lost_right_line;

/* 角点置信度历史最大值（调试用） */
extern float conf3_max, conf4_max;

/* L 角点找到标记（供 vision_step 和诊断输出使用） */
extern int8 Lpt0_found_flag, Lpt1_found_flag;

/* ================= 远端边线数组 =================
 *
 * 命名规则与主边线一致：
 *   far_ipts  = 原图坐标（int）
 *   far_rpts  = 俯视角坐标（float）
 *   far_rptsb = 滤波后
 *   far_rptss = 等距采样后
 *   far_rptsa = 局部转角
 *   far_rptsan = NMS 后
 *   0 = 左线，1 = 右线
 */

/* 远端原图边线 */
extern int far_ipts0[MT9V03X_H][2];
extern int far_ipts1[MT9V03X_H][2];
extern int far_ipts0_num, far_ipts1_num;

/* 远端俯视角边线 */
extern float far_rpts0[MT9V03X_H][2];
extern float far_rpts1[MT9V03X_H][2];
extern int far_rpts0_num, far_rpts1_num;

/* 远端滤波后边线 */
extern float far_rpts0b[MT9V03X_H][2];
extern float far_rpts1b[MT9V03X_H][2];
extern int far_rpts0b_num, far_rpts1b_num;

/* 远端等距采样边线 */
extern float far_rpts0s[MT9V03X_H][2];
extern float far_rpts1s[MT9V03X_H][2];
extern int far_rpts0s_num, far_rpts1s_num;

/* 远端局部转角 */
extern float far_rpts0a[MT9V03X_H];
extern float far_rpts1a[MT9V03X_H];
extern int far_rpts0a_num, far_rpts1a_num;

/* 远端 NMS 转角 */
extern float far_rpts0an[MT9V03X_H];
extern float far_rpts1an[MT9V03X_H];
extern int far_rpts0an_num, far_rpts1an_num;

/* 近端/远端 L 角点逆透视坐标（调试用） */
extern float inv_Lpt0_found[2], inv_Lpt1_found[2];
extern float inv_far_Lpt0_found[2], inv_far_Lpt1_found[2];

/* 远端搜线辅助坐标（诊断用） */
extern int far_x11, far_y1;

#endif /* CROSS_H */
