#pragma once

#include <cstdint>

#include "types.hpp"

// 原图 seed / trace + 中线生成统一放进一个主核，风格对齐 RT1064 的 imgproc。

//----------------------------------------------------------------------------------------------------------------------
//  @brief      计算指定原图区域的大津阈值
//  @param      gray     输入 raw 灰度图
//  @param      x_start  区域起始 x，函数内部会限幅并处理起止顺序
//  @param      x_end    区域结束 x
//  @param      y_start  区域起始 y
//  @param      y_end    区域结束 y
//  @return     int      0~255 阈值；gray 为空或区域无效时返回 0
//----------------------------------------------------------------------------------------------------------------------
int region_otsu(const uint8_t gray[RAW_H][RAW_W], int x_start, int x_end, int y_start, int y_end);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      从起线行查找左右 seed
//  @param      gray       输入 raw 灰度图
//  @param      start_row  起线行
//  @param      mid        输入/输出上一帧中心参考列，允许为空
//  @param      state      输出 bit 状态：1 左 seed，2 右 seed，3 双 seed
//  @param      sd         输出左右 seed、行号和宽度
//  @return     int        1 至少找到一侧 seed / 0 未找到
//  @note       这里只找原图 seed，不做 IPM，不生成中线。
//----------------------------------------------------------------------------------------------------------------------
int find_seeds(const uint8_t gray[RAW_H][RAW_W],
               int start_row,
               int *mid,
               int *state,
               seed_pair_t *sd);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      判断 find_seeds() 的左右 seed 是否可作为一对使用
//  @param      sd     find_seeds() 输出的 seed 对
//  @param      state  find_seeds() 输出的 bit 状态
//  @return     int    1 双边 seed 同行且宽度合法 / 0 不可作为双边起线
//----------------------------------------------------------------------------------------------------------------------
int seed_pair_accepted(const seed_pair_t *sd, int state);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      从固定列向上找单侧 seed
//  @param      gray   输入 raw 灰度图
//  @param      start  起扫 raw 点
//  @param      seed   输出 raw seed；失败时写 (-1, -1)
//  @return     int    1 成功 / 0 未找到
//  @note       用于补找单侧起线点；沿列先见白，再遇黑时取前一个白点。
//----------------------------------------------------------------------------------------------------------------------
int find_column_seed(const uint8_t gray[RAW_H][RAW_W], point_t start, point_t *seed);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      计算 raw 点附近的局部阈值
//  @param      gray  输入 raw 灰度图
//  @param      x     raw x
//  @param      y     raw y
//  @return     int   0~255 局部阈值
//----------------------------------------------------------------------------------------------------------------------
int calc_th(const uint8_t gray[RAW_H][RAW_W], int x, int y);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      计算当前帧 seed/元素检测用的基础阈值
//  @param      gray  输入 raw 灰度图
//  @param      mid   中心参考列
//  @return     int   左半区域大津阈值
//----------------------------------------------------------------------------------------------------------------------
int frame_seed_threshold(const uint8_t gray[RAW_H][RAW_W], int mid);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      单侧迷宫追线入口
//  @param      gray       输入 raw 灰度图
//  @param      seed       raw 起线点
//  @param      left_side  1 左手追线 / 0 右手追线
//  @param      tr         输出 trace 点列
//  @return     int        1 追线成功 / 0 seed 无效、起点过暗或纵向跨度不足
//----------------------------------------------------------------------------------------------------------------------
int trace_single(const uint8_t gray[RAW_H][RAW_W], point_t seed, int left_side, trace_t *tr);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      将 raw 点列转成 IPM/工作浮点点列
//  @param      raw_pts     输入 raw 点列
//  @param      raw_num     输入点数
//  @param      matrix      raw -> ipm 单应矩阵
//  @param      has_matrix  1 使用矩阵 / 0 直接复制 raw 坐标
//  @param      pts         输出工作点列
//  @return     int         输出有效点数
//  @note       已有有效点后再投影越界会截断，避免断线后的远端脏点进入中线。
//----------------------------------------------------------------------------------------------------------------------
int perspective_points(const point_t *raw_pts, int raw_num, const double *matrix, int has_matrix, double pts[POINT_MAX][2]);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      对工作点列做 1-2-1 平滑
//  @param      pts_in   输入工作点列
//  @param      num_in   输入点数
//  @param      pts_out  输出工作点列
//  @param      num_out  输出点数，允许为空
//----------------------------------------------------------------------------------------------------------------------
void blur_points(const double pts_in[POINT_MAX][2], int num_in, double pts_out[POINT_MAX][2], int *num_out);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      按近似等弧长重采样工作点列
//  @param      pts_in       输入工作点列
//  @param      num_in       输入点数
//  @param      pts_out      输出工作点列
//  @param      num_out      输出点数，允许为空
//  @param      sample_dist  采样间隔，单位为当前工作坐标像素
//----------------------------------------------------------------------------------------------------------------------
void resample_points(const double pts_in[POINT_MAX][2],
                     int num_in,
                     double pts_out[POINT_MAX][2],
                     int *num_out,
                     int sample_dist);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      左边线单边外扩生成控制中线
//  @param      pts         输入左边线工作点列
//  @param      num         输入点数
//  @param      half_width  半车道宽，单位为工作坐标像素
//  @param      ref_x       中线起点参考 x
//  @param      ref_y       中线起点参考 y
//  @param      midline     输出控制中线
//  @return     int         中线点数；输入不足或无法形成有效点时返回 0
//  @note       输出是 IPM/控制坐标，不是 assistant 原图红线。
//----------------------------------------------------------------------------------------------------------------------
int track_leftline(const double pts[POINT_MAX][2], int num, int half_width, int ref_x, int ref_y, midline_t *midline);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      左边线从第 0 个点开始单边外扩生成控制中线
//  @param      pts         输入左边线工作点列
//  @param      num         输入点数
//  @param      half_width  半车道宽，单位为工作坐标像素
//  @param      ref_x       中线起点参考 x
//  @param      ref_y       中线起点参考 y
//  @param      midline     输出控制中线
//  @return     int         中线点数；输入不足或无法形成有效点时返回 0
//  @note       用于 CROSS_IN 远线控制，对齐参考版 begin_id = 0。
//----------------------------------------------------------------------------------------------------------------------
int track_leftline_from_start(const double pts[POINT_MAX][2], int num, int half_width, int ref_x, int ref_y, midline_t *midline);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      右边线单边内扩生成控制中线
//  @param      pts         输入右边线工作点列
//  @param      num         输入点数
//  @param      half_width  半车道宽，单位为工作坐标像素
//  @param      ref_x       中线起点参考 x
//  @param      ref_y       中线起点参考 y
//  @param      midline     输出控制中线
//  @return     int         中线点数；输入不足或无法形成有效点时返回 0
//  @note       输出是 IPM/控制坐标，不是 assistant 原图红线。
//----------------------------------------------------------------------------------------------------------------------
int track_rightline(const double pts[POINT_MAX][2], int num, int half_width, int ref_x, int ref_y, midline_t *midline);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      右边线从第 0 个点开始单边内扩生成控制中线
//  @param      pts         输入右边线工作点列
//  @param      num         输入点数
//  @param      half_width  半车道宽，单位为工作坐标像素
//  @param      ref_x       中线起点参考 x
//  @param      ref_y       中线起点参考 y
//  @param      midline     输出控制中线
//  @return     int         中线点数；输入不足或无法形成有效点时返回 0
//  @note       用于 CROSS_IN 远线控制，对齐参考版 begin_id = 0。
//----------------------------------------------------------------------------------------------------------------------
int track_rightline_from_start(const double pts[POINT_MAX][2], int num, int half_width, int ref_x, int ref_y, midline_t *midline);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      双边配对取中点生成控制中线
//  @param      pts0        输入左侧工作点列
//  @param      num0        左侧点数
//  @param      pts1        输入右侧工作点列
//  @param      num1        右侧点数
//  @param      half_width  半车道宽，参与宽度合法性判断
//  @param      ref_x       中线起点参考 x
//  @param      ref_y       中线起点参考 y
//  @param      midline     输出控制中线
//  @return     int         中线点数；配对不足或宽度不合格时返回 0
//  @note       当前普通主线不主动选择 TRACK_TYPE_DUAL；接入前必须重新实车验证。
//----------------------------------------------------------------------------------------------------------------------
int track_dualline(const double pts0[POINT_MAX][2],
                   int num0,
                   const double pts1[POINT_MAX][2],
                   int num1,
                   int half_width,
                   int ref_x,
                   int ref_y,
                   midline_t *midline);

//----------------------------------------------------------------------------------------------------------------------
//  @brief      判断控制中线是否覆盖预瞄距离
//  @param      midline       输入控制中线
//  @param      aim_distance  预瞄距离，单位为 midline->dist 的累计像素距离
//  @return     int           1 覆盖足够 / 0 中线过短
//  @note       这里只检查距离覆盖，不计算 guide_error。
//----------------------------------------------------------------------------------------------------------------------
int midline_has_lookahead(const midline_t *midline, int aim_distance);
