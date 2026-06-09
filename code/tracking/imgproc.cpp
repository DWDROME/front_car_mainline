#include "imgproc.hpp"

#include "perspective.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>


// 主链路图像处理核：
// 原图灰度 -> 局部阈值 -> 起线点 -> 左/右手追线 -> IPM 点列 -> 单边/双边中线。
// 这里保持参考工程的固定数组和直接过程式写法，不做控制层状态。

namespace
{

// 局部阈值与 seed/trace 的现场常量，单位均为 raw 像素。
constexpr int kLocalBlockSize = 5;        // 局部阈值取均值的窗口边长（5x5）
constexpr int kLocalClipValue = 8;        // 局部阈值在均值上再下压的量，越大越偏向判黑
constexpr int kSeedBorderMargin = 3;      // seed 距左右图像边的最小留白，太靠边的边沿丢弃
constexpr int kSeedMinWidth = 10;         // 双 seed 最小间距，窄于此判噪声不成对
constexpr int kSeedMaxWidth = RAW_W - ROAD_HALF_WIDTH;  // 双 seed 最大间距上限
constexpr int kSeedStartOffset = ROAD_HALF_WIDTH;       // 从中心列向左右各偏移这么多列起搜 seed
constexpr int kTraceMinVerticalGain = 8;  // 追线纵向至少要爬升的行数，达不到判无效线
constexpr int kTraceBorderMargin = 2;     // 追线时距图像边的停止留白

// RT1064 迷宫法方向表合同：dir 顺序固定为 上、右、下、左。
// 因 y 向下，DY[0]=-1 表示朝图像上方（赛道更远处）。左右转公式依赖这个顺序：
// (dir + 1) % 4 是右转，(dir + 3) % 4 是左转，不能只改方向表不改转向公式。
// DX/DY=正前方一步；LDX/LDY=左手斜前方一步；RDX/RDY=右手斜前方一步。
constexpr int DX[4] = {0, 1, 0, -1};   // 正前 x 增量：dir=0 上, 1 右, 2 下, 3 左
constexpr int DY[4] = {-1, 0, 1, 0};   // 正前 y 增量（y 向下，-1 即向上/向远）
constexpr int LDX[4] = {-1, 1, 1, -1}; // 左手斜前 x 增量
constexpr int LDY[4] = {-1, -1, 1, 1}; // 左手斜前 y 增量
constexpr int RDX[4] = {1, 1, -1, -1}; // 右手斜前 x 增量
constexpr int RDY[4] = {-1, 1, 1, -1}; // 右手斜前 y 增量

int clamp_i(int value, int low, int high);
int calc_th_core(const uint8_t gray[RAW_H][RAW_W], int x, int y);
int find_left_edge(const uint8_t gray[RAW_H][RAW_W], int row, int x0);
int find_right_edge(const uint8_t gray[RAW_H][RAW_W], int row, int x0);

} // namespace

namespace
{

// 整型限幅到 [low, high]。
int clamp_i(int value, int low, int high)
{
    return std::max(low, std::min(value, high));
}

// 以 (x,y) 为中心取局部均值再减 kLocalClipValue，输出 0~255 的局部二值化阈值。
int calc_th_core(const uint8_t gray[RAW_H][RAW_W], int x, int y)
{
    if(gray == nullptr)
    {
        return 0;
    }
    x = clamp_i(x, 0, RAW_W - 1);
    y = clamp_i(y, 0, RAW_H - 1);

    const int radius = kLocalBlockSize / 2;
    int sum = 0;
    int count = 0;
    for(int yy = std::max(0, y - radius); yy <= std::min(RAW_H - 1, y + radius); ++yy)
    {
        for(int xx = std::max(0, x - radius); xx <= std::min(RAW_W - 1, x + radius); ++xx)
        {
            sum += gray[yy][xx];
            ++count;
        }
    }
    if(count <= 0)
    {
        return gray[y][x];
    }
    return clamp_i(sum / count - kLocalClipValue, 0, 255);
}

// 在指定行从 x0 向左扫最近的白->黑邻接边沿，未命中返回 -1。
// 对应视频迁移版 find_leftbase()：二值图里找 ptr[x]==255 && ptr[x-1]==0；
// 当前项目保留同一边界语义，但用局部阈值替代固定 255/0。
int find_left_edge(const uint8_t gray[RAW_H][RAW_W], int row, int x0)
{
    if(gray == nullptr || row < 0 || row >= RAW_H)
    {
        return -1;
    }

    x0 = clamp_i(x0, 1, RAW_W - 2);
    for(int x = x0; x > 0; --x)
    {
        const int th = calc_th_core(gray, x, row);
        const int th0 = calc_th_core(gray, x - 1, row);
        if(gray[row][x] > th && gray[row][x - 1] <= th0)
        {
            return x;
        }
    }
    return -1;
}

// 在指定行从 x0 向右扫最近的白->黑邻接边沿，未命中返回 -1。
// 这是 find_leftbase() 的右侧对称版：当前像素仍在白区，右邻进入黑区。
int find_right_edge(const uint8_t gray[RAW_H][RAW_W], int row, int x0)
{
    if(gray == nullptr || row < 0 || row >= RAW_H)
    {
        return -1;
    }

    x0 = clamp_i(x0, 1, RAW_W - 2);
    for(int x = x0; x < RAW_W - 1; ++x)
    {
        const int th = calc_th_core(gray, x, row);
        const int th1 = calc_th_core(gray, x + 1, row);
        if(gray[row][x] > th && gray[row][x + 1] <= th1)
        {
            return x;
        }
    }
    return -1;
}

} // namespace

int calc_th(const uint8_t gray[RAW_H][RAW_W], int x, int y)
{
    return calc_th_core(gray, x, y);
}

// Mainline 公开接口：阈值与种子点。

// 区域大津阈值；输入矩形会先限幅并自动处理起止顺序。
int region_otsu(const uint8_t gray[RAW_H][RAW_W], int x_start, int x_end, int y_start, int y_end)
{
    if(gray == nullptr)
    {
        return 0;
    }

    x_start = clamp_i(x_start, 0, RAW_W - 1);
    x_end = clamp_i(x_end, 0, RAW_W - 1);
    y_start = clamp_i(y_start, 0, RAW_H - 1);
    y_end = clamp_i(y_end, 0, RAW_H - 1);
    if(x_start > x_end)
    {
        std::swap(x_start, x_end);
    }
    if(y_start > y_end)
    {
        std::swap(y_start, y_end);
    }

    int hist[256] = {};
    int min_v = 255;
    int max_v = 0;
    int num = 0;
    int sum = 0;
    for(int y = y_start; y <= y_end; ++y)
    {
        for(int x = x_start; x <= x_end; ++x)
        {
            const int v = gray[y][x];
            ++hist[v];
            min_v = std::min(min_v, v);
            max_v = std::max(max_v, v);
            ++num;
            sum += v;
        }
    }

    if(num <= 0)
    {
        return 0;
    }
    if(min_v >= max_v)
    {
        return min_v;
    }

    int num0 = 0;
    int sum0 = 0;
    double best_score = -1.0;
    int best_th = min_v;
    for(int th = min_v; th < max_v; ++th)
    {
        num0 += hist[th];
        if(num0 <= 0)
        {
            continue;
        }

        const int num1 = num - num0;
        if(num1 <= 0)
        {
            break;
        }

        sum0 += hist[th] * th;
        const int sum1 = sum - sum0;
        const double mean0 = (double)sum0 / num0;
        const double mean1 = (double)sum1 / num1;
        const double d = mean0 - mean1;
        const double score = (double)num0 * num1 * d * d;
        if(score > best_score)
        {
            best_score = score;
            best_th = th;
        }
    }
    return best_th;
}

// 查找左右起线点：按固定起线行和中心两侧固定偏移直接起搜。
int find_seeds(const uint8_t gray[RAW_H][RAW_W],
               int start_row,
               int *search_center,
               int *seed_state,
               seed_pair_t *seeds)
{
    if(seeds != nullptr)
    {
        *seeds = {};
        seeds->left = {-1, -1};
        seeds->right = {-1, -1};
        seeds->row = -1;
    }
    if(gray == nullptr || seeds == nullptr)
    {
        return 0;
    }

    int center = MID_X;
    if(search_center != nullptr && *search_center >= 0 && *search_center < RAW_W)
    {
        center = *search_center;
    }
    const int left_x0 = clamp_i(center - kSeedStartOffset, 1, RAW_W - 2);
    const int right_x0 = clamp_i(center + kSeedStartOffset, 1, RAW_W - 2);

    const int y = clamp_i(start_row, 1, RAW_H - 2);
    int single_left_x = -1;
    int single_right_x = -1;
    const int x0 = find_left_edge(gray, y, left_x0);
    const int x1 = find_right_edge(gray, y, right_x0);
    const int ok0 = x0 >= kSeedBorderMargin && x0 <= left_x0;
    const int ok1 = x1 >= right_x0 && x1 <= RAW_W - 1 - kSeedBorderMargin;
    if(ok0)
    {
        single_left_x = x0;
    }
    if(ok1)
    {
        single_right_x = x1;
    }

    const int w = x1 - x0;
    if(ok0 && ok1 && w >= kSeedMinWidth && w <= kSeedMaxWidth)
    {
        seeds->left = {x0, y};
        seeds->right = {x1, y};
        seeds->row = y;
        if(seed_state != nullptr)
        {
            *seed_state = 3;
        }
        return 1;
    }

    int left_y = y;
    int right_y = y;

    // 固定行只找到一侧时，沿用 TC264/Front_Car 的保守补搜：只向上找缺失侧。
    if(ok0 && !ok1)
    {
        for(int yy = y - 1; yy >= MINI_HIGH; --yy)
        {
            const int xr = find_right_edge(gray, yy, right_x0);
            if(xr >= right_x0 && xr <= RAW_W - 1 - kSeedBorderMargin)
            {
                single_right_x = xr;
                right_y = yy;
                break;
            }
        }
    }
    else if(!ok0 && ok1)
    {
        for(int yy = y - 1; yy >= MINI_HIGH; --yy)
        {
            const int xl = find_left_edge(gray, yy, left_x0);
            if(xl >= kSeedBorderMargin && xl <= left_x0)
            {
                single_left_x = xl;
                left_y = yy;
                break;
            }
        }
    }

    int state = 0;
    if(single_left_x >= 0)
    {
        seeds->left = {single_left_x, left_y};
        state |= 1;
    }
    if(single_right_x >= 0)
    {
        seeds->right = {single_right_x, right_y};
        state |= 2;
    }
    if(state == 3 && left_y == right_y)
    {
        seeds->row = left_y;
    }
    else
    {
        seeds->row = -1;
    }

    if(seed_state != nullptr)
    {
        *seed_state = state;
    }
    return state != 0;
}

// 判断左右种子是否成对可用：state 含双边、行号一致、同排 span 合法。
// seed 仍只是 trace 起点；这里的 span 只用于同排 pair 诊断和宽度基准更新。
int seed_pair_accepted(const seed_pair_t *seeds, int seed_state)
{
    if(seeds == nullptr)
    {
        return 0;
    }
    if((seed_state & 1) == 0 || (seed_state & 2) == 0)
    {
        return 0;
    }
    if(seeds->left.y != seeds->right.y || seeds->row != seeds->left.y)
    {
        return 0;
    }
    const int span = seeds->right.x - seeds->left.x;
    return span >= kSeedMinWidth &&
           span <= kSeedMaxWidth;
}

// 从固定列找种子：沿 y 向上先看到白，再遇黑时返回前一个白点。
int find_column_seed(const uint8_t gray[RAW_H][RAW_W], point_t start, point_t *seed)
{
    if(seed != nullptr)
    {
        *seed = {-1, -1};
    }
    if(gray == nullptr || seed == nullptr)
    {
        return 0;
    }

    const int dy = -1;
    const int x = clamp_i(start.x, 1, RAW_W - 2);
    int seen_white = 0;
    for(int y = clamp_i(start.y, 1, RAW_H - 2); y >= 1 && y < RAW_H - 1; y += dy)
    {
        const int th = calc_th_core(gray, x, y);
        if(gray[y][x] > th)
        {
            seen_white = 1;
            continue;
        }
        if(seen_white)
        {
            *seed = {x, clamp_i(y - dy, 1, RAW_H - 2)};
            return 1;
        }
    }
    return 0;
}

// Mainline 公开接口：灰度输出与阈值包装。

// 取中线左半区域的大津阈值，供斑马线等全局阈值检测使用。
int frame_seed_threshold(const uint8_t gray[RAW_H][RAW_W], int mid_position)
{
    if(gray == nullptr)
    {
        return 0;
    }
    return region_otsu(gray, 0, mid_position, MINI_HIGH, START_HIGH);
}

namespace
{

//-------------------------------------------------------------------------------------------------------------------
//  @brief      左手追线：front 不通就右转，front-left 可走就斜进，否则直进
//  @return     int          1 步数和纵向跨度均达标 / 0 失败
//  @note       输入 seed 必须已经在 trace_single() 里完成边界和亮度检查。
//-------------------------------------------------------------------------------------------------------------------
int trace_left(const uint8_t gray[RAW_H][RAW_W], point_t seed, trace_t *trace)
{
    int x = seed.x;
    int y = seed.y;
    int dir = 0;
    int turn = 0;
    int min_y = seed.y;

    point_t now = {x, y};
    trace->pts[trace->step++] = now;
    while(trace->step < POINT_MAX &&
          kTraceBorderMargin < x && x < RAW_W - 1 - kTraceBorderMargin &&
          kTraceBorderMargin < y && y < RAW_H - 1 - kTraceBorderMargin &&
          turn < 4)
    {
        const int th = calc_th(gray, x, y);
        point_t front = {x + DX[dir], y + DY[dir]};
        point_t side = {x + LDX[dir], y + LDY[dir]};
        const int front_white = gray[front.y][front.x] >= th;
        const int side_white = gray[side.y][side.x] >= th;
        if(!front_white)
        {
            dir = (dir + 1) % 4;  // 正前方是黑：顺时针右转 90°，换方向重试
            ++turn;
            continue;
        }

        if(side_white)
        {
            x = side.x;
            y = side.y;
            dir = (dir + 3) % 4;  // 左手斜前可走：走过去并逆时针回正，保持贴左边线
        }
        else
        {
            x = front.x;
            y = front.y;
        }

        now = {x, y};
        trace->pts[trace->step++] = now;
        trace->stop_point = now;
        turn = 0;
        min_y = std::min(min_y, y);
    }

    const int vertical_gain = seed.y - min_y;
    return trace->step >= TRACE_MIN_STEP && vertical_gain >= kTraceMinVerticalGain;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      右手追线：front 不通就左转，front-right 可走就斜进，否则直进
//  @return     int          1 步数和纵向跨度均达标 / 0 失败
//  @note       输入 seed 必须已经在 trace_single() 里完成边界和亮度检查。
//-------------------------------------------------------------------------------------------------------------------
int trace_right(const uint8_t gray[RAW_H][RAW_W], point_t seed, trace_t *trace)
{
    int x = seed.x;
    int y = seed.y;
    int dir = 0;
    int turn = 0;
    int min_y = seed.y;

    point_t now = {x, y};
    trace->pts[trace->step++] = now;
    while(trace->step < POINT_MAX &&
          kTraceBorderMargin < x && x < RAW_W - 1 - kTraceBorderMargin &&
          kTraceBorderMargin < y && y < RAW_H - 1 - kTraceBorderMargin &&
          turn < 4)
    {
        const int th = calc_th(gray, x, y);
        point_t front = {x + DX[dir], y + DY[dir]};
        point_t side = {x + RDX[dir], y + RDY[dir]};
        const int front_white = gray[front.y][front.x] >= th;
        const int side_white = gray[side.y][side.x] >= th;
        if(!front_white)
        {
            dir = (dir + 3) % 4;  // 正前方是黑：逆时针左转 90°，换方向重试
            ++turn;
            continue;
        }

        if(side_white)
        {
            x = side.x;
            y = side.y;
            dir = (dir + 1) % 4;  // 右手斜前可走：走过去并顺时针回正，保持贴右边线
        }
        else
        {
            x = front.x;
            y = front.y;
        }

        now = {x, y};
        trace->pts[trace->step++] = now;
        trace->stop_point = now;
        turn = 0;
        min_y = std::min(min_y, y);
    }

    const int vertical_gain = seed.y - min_y;
    return trace->step >= TRACE_MIN_STEP && vertical_gain >= kTraceMinVerticalGain;
}

} // namespace

//-------------------------------------------------------------------------------------------------------------------
//  @brief      单侧追线入口：先检查种子位置和起点亮度，再按 left_side 走左手/右手追线
//  @return     int          1 追线成功 / 0 种子无效、起点过暗或纵向跨度不足
//  @note       left_side=1 走左手追线；left_side=0 走右手追线。
//-------------------------------------------------------------------------------------------------------------------
int trace_single(const uint8_t gray[RAW_H][RAW_W], point_t seed, int left_side, trace_t *trace)
{
    if(gray == nullptr || trace == nullptr)
    {
        return 0;
    }
    if(seed.x < 0 || seed.x >= RAW_W || seed.y < 0 || seed.y >= RAW_H)
    {
        return 0;
    }

    std::memset(trace, 0, sizeof(*trace));
    trace->left_side = 0;
    if(left_side)
    {
        trace->left_side = 1;
    }
    trace->seed = seed;
    trace->stop_point = seed;
    const int seed_threshold = calc_th_core(gray, seed.x, seed.y);

    if(seed.x <= kTraceBorderMargin ||
       seed.x >= RAW_W - 1 - kTraceBorderMargin ||
       seed.y <= kTraceBorderMargin ||
       seed.y >= RAW_H - 1 - kTraceBorderMargin)
    {
        return 0;
    }
    if(gray[seed.y][seed.x] < seed_threshold)
    {
        return 0;
    }

    if(left_side)
    {
        return trace_left(gray, seed, trace);
    }
    return trace_right(gray, seed, trace);
}

// Mainline 公开接口：中线生成。

namespace
{

const int kMinBorderStep = 6;
const int kDualPairMaxDy = 8;
const int kDualMinStep = 12;
const int kDualMinOverlap = 10;
const int kDualMaxYGap = 18;
const int kDualMinWidth = 12;
const int kMidlineSampleDist = 3;
const double k_mid_eps = 1e-6;

// 浮点四舍五入成 int，负数按对称方向处理。
int round_i(double value)
{
    return value >= 0.0 ? (int)(value + 0.5) : (int)(value - 0.5);
}

// 推入一个中线点，重复点跳过；dist[] 记录从起点累计的近似弧长。
void push_mid(midline_t *midline, int *len, point_t *last, double x, double y)
{
    if(midline == nullptr || len == nullptr || last == nullptr || *len >= POINT_MAX)
    {
        return;
    }

    point_t current = {
        clamp_i(round_i(x), 0, IPM_W - 1),
        clamp_i(round_i(y), 0, IPM_H - 1)
    };
    if(current.x == last->x && current.y == last->y)
    {
        return;
    }

    const double segment = std::hypot((double)current.x - last->x,
                                      (double)current.y - last->y);
    midline->pts[*len] = current;
    midline->dist[*len] = midline->dist[*len - 1] + round_i(segment);
    *last = current;
    ++(*len);
}

} // namespace

//-------------------------------------------------------------------------------------------------------------------
//  @brief      原图点列投影到 IPM 浮点点列；未启用 IPM 时直接复制
//  @return     int          输出点数
//  @note       对齐参考版 cross.c：raw 点列逐点查 mapx/mapy，输出点数保持和输入点数一致。
//-------------------------------------------------------------------------------------------------------------------
int perspective_points(const point_t *raw_pts, int raw_num, const double *matrix, int has_matrix, double pts[POINT_MAX][2])
{
    if(raw_pts == nullptr || raw_num <= 0)
    {
        return 0;
    }

    int num = raw_num;
    if(num > POINT_MAX)
    {
        num = POINT_MAX;
    }

    int count = 0;
    for(int i = 0; i < num && count < POINT_MAX; ++i)
    {
        const double raw_x = raw_pts[i].x;
        const double raw_y = raw_pts[i].y;
        double x = raw_x;
        double y = raw_y;
        (void)matrix;
        if(has_matrix)
        {
            if(!perspective_lookup_raw_to_ipm(raw_pts[i].x, raw_pts[i].y, &x, &y))
            {
                x = -1.0;
                y = -1.0;
            }
        }
        pts[count][0] = x;
        pts[count][1] = y;
        ++count;
    }
    return count;
}

// 判断 IPM/工作点是否有效：perspective_points 对查表越界的点写 (-1,-1)，这里据此过滤。
int ipm_pt_valid(double x, double y)
{
    if(x < 0.0 || y < 0.0)
    {
        return 0;
    }
    return 1;
}

// 找点列中第一段连续有效点区间 [begin, end)；整列无有效点时返回 0。
int first_valid_run(const double pts[POINT_MAX][2], int num, int *begin, int *end)
{
    if(pts == nullptr || begin == nullptr || end == nullptr || num <= 0)
    {
        return 0;
    }

    int i = 0;
    for(; i < num; ++i)
    {
        if(ipm_pt_valid(pts[i][0], pts[i][1]))
        {
            break;
        }
    }
    if(i >= num)
    {
        return 0;
    }

    int j = i;
    for(; j < num; ++j)
    {
        if(!ipm_pt_valid(pts[j][0], pts[j][1]))
        {
            break;
        }
    }

    *begin = i;
    *end = j;
    return 1;
}

// 浮点点列 1-2-1 平滑：首尾保持，中间用三角窗。
void blur_points(const double pts_in[POINT_MAX][2], int num_in, double pts_out[POINT_MAX][2], int *num_out)
{
    int num = num_in;
    if(num < 0)
    {
        num = 0;
    }
    if(num > POINT_MAX)
    {
        num = POINT_MAX;
    }

    int begin = 0;
    int end = 0;
    if(!first_valid_run(pts_in, num, &begin, &end))
    {
        if(num_out != nullptr)
        {
            *num_out = 0;
        }
        return;
    }

    const int run = end - begin;
    for(int i = 0; i < run; ++i)
    {
        pts_out[i][0] = pts_in[begin + i][0];
        pts_out[i][1] = pts_in[begin + i][1];
    }
    if(run > 2)
    {
        double prev_x = pts_out[0][0];
        double prev_y = pts_out[0][1];
        double cur_x = pts_out[1][0];
        double cur_y = pts_out[1][1];
        for(int i = 1; i < run - 1; ++i)
        {
            const double next_x = pts_out[i + 1][0];
            const double next_y = pts_out[i + 1][1];
            pts_out[i][0] = (prev_x + 2.0 * cur_x + next_x) / 4.0;
            pts_out[i][1] = (prev_y + 2.0 * cur_y + next_y) / 4.0;
            prev_x = cur_x;
            prev_y = cur_y;
            cur_x = next_x;
            cur_y = next_y;
        }
    }
    if(num_out != nullptr)
    {
        *num_out = run;
    }
}

// 按等弧长 sample_dist 重采样浮点点列，输出密度更均匀的工作点。
void resample_points(const double pts_in[POINT_MAX][2],
                     int num_in,
                     double pts_out[POINT_MAX][2],
                     int *num_out,
                     int sample_dist)
{
    int num = num_in;
    if(num < 0)
    {
        num = 0;
    }
    if(num > POINT_MAX)
    {
        num = POINT_MAX;
    }
    int out_num = 0;
    int begin = 0;
    int end = 0;
    if(num > 0 && sample_dist > 0 && first_valid_run(pts_in, num, &begin, &end))
    {
        pts_out[out_num][0] = pts_in[begin][0];
        pts_out[out_num][1] = pts_in[begin][1];
        ++out_num;

        double accumulated = 0.0;
        for(int i = begin; i < end - 1 && out_num < POINT_MAX; ++i)
        {
            double x0 = pts_in[i][0];
            double y0 = pts_in[i][1];
            const double x1 = pts_in[i + 1][0];
            const double y1 = pts_in[i + 1][1];
            double dx = x1 - x0;
            double dy = y1 - y0;
            double segment = std::hypot(dx, dy);
            if(segment < k_mid_eps)
            {
                continue;
            }
            dx /= segment;
            dy /= segment;

            while(accumulated + segment >= sample_dist && out_num < POINT_MAX)
            {
                const double need = sample_dist - accumulated;
                x0 += dx * need;
                y0 += dy * need;
                pts_out[out_num][0] = x0;
                pts_out[out_num][1] = y0;
                ++out_num;
                segment -= need;
                accumulated = 0.0;
            }
            accumulated += segment;
        }
    }
    if(num_out != nullptr)
    {
        *num_out = out_num;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      左边线法向外扩生成候选中线；点数与输入边线一一对应
//  @return     int          候选点数；输入不足或无法形成有效点时返回 0
//-------------------------------------------------------------------------------------------------------------------
int track_leftline(const double pts_in[POINT_MAX][2],
                   int num,
                   double pts_out[POINT_MAX][2],
                   int approx_num,
                   double dist)
{
    if(num < 2 || pts_out == nullptr || approx_num <= 0 || dist <= 0.0)
    {
        return 0;
    }

    for(int i = 0; i < num; ++i)
    {
        const int im = clamp_i(i - approx_num, 0, num - 1);
        const int ip = clamp_i(i + approx_num, 0, num - 1);
        if(!ipm_pt_valid(pts_in[im][0], pts_in[im][1]) ||
           !ipm_pt_valid(pts_in[i][0], pts_in[i][1]) ||
           !ipm_pt_valid(pts_in[ip][0], pts_in[ip][1]))
        {
            return 0;
        }

        double dx = pts_in[ip][0] - pts_in[im][0];
        double dy = pts_in[ip][1] - pts_in[im][1];
        const double dn = std::hypot(dx, dy);
        if(dn < k_mid_eps)
        {
            return 0;
        }
        dx /= dn;
        dy /= dn;

        pts_out[i][0] = pts_in[i][0] - dy * dist;
        pts_out[i][1] = pts_in[i][1] + dx * dist;
    }
    return num;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      右边线法向内扩生成候选中线；点数与输入边线一一对应
//  @return     int          候选点数；输入不足或无法形成有效点时返回 0
//-------------------------------------------------------------------------------------------------------------------
int track_rightline(const double pts_in[POINT_MAX][2],
                    int num,
                    double pts_out[POINT_MAX][2],
                    int approx_num,
                    double dist)
{
    if(num < 2 || pts_out == nullptr || approx_num <= 0 || dist <= 0.0)
    {
        return 0;
    }

    for(int i = 0; i < num; ++i)
    {
        const int im = clamp_i(i - approx_num, 0, num - 1);
        const int ip = clamp_i(i + approx_num, 0, num - 1);
        if(!ipm_pt_valid(pts_in[im][0], pts_in[im][1]) ||
           !ipm_pt_valid(pts_in[i][0], pts_in[i][1]) ||
           !ipm_pt_valid(pts_in[ip][0], pts_in[ip][1]))
        {
            return 0;
        }

        double dx = pts_in[ip][0] - pts_in[im][0];
        double dy = pts_in[ip][1] - pts_in[im][1];
        const double dn = std::hypot(dx, dy);
        if(dn < k_mid_eps)
        {
            return 0;
        }
        dx /= dn;
        dy /= dn;

        pts_out[i][0] = pts_in[i][0] + dy * dist;
        pts_out[i][1] = pts_in[i][1] - dx * dist;
    }
    return num;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      候选中线归一化为最终控制中线：固定起点、重采样、累计距离
//  @return     int          控制中线点数；输入不足或无法形成有效点时返回 0
//  @note       force_begin_id0 对齐参考版 CROSS_IN 的 begin_id = 0 特例。
//-------------------------------------------------------------------------------------------------------------------
int build_rptsn(const double rpts[POINT_MAX][2],
                int rpts_num,
                int cx,
                int cy,
                int force_begin_id0,
                midline_t *midline)
{
    if(rpts == nullptr || rpts_num < 2 || midline == nullptr)
    {
        return 0;
    }

    std::memset(midline, 0, sizeof(*midline));
    cx = clamp_i(cx, 0, IPM_W - 1);
    cy = clamp_i(cy, 0, IPM_H - 1);

    int begin = 0;
    int run_begin = 0;
    int run_end = rpts_num;
    if(!force_begin_id0)
    {
        if(!first_valid_run(rpts, rpts_num, &run_begin, &run_end))
        {
            return 0;
        }
        begin = -1;
        double best_d = 1e30;
        for(int i = run_begin; i < run_end; ++i)
        {
            const double dx = rpts[i][0] - cx;
            const double dy = rpts[i][1] - cy;
            const double d = dx * dx + dy * dy;
            if(d < best_d)
            {
                best_d = d;
                begin = i;
            }
        }
        if(begin < 0)
        {
            return 0;
        }
    }
    else
    {
        for(int i = 0; i < rpts_num; ++i)
        {
            if(!ipm_pt_valid(rpts[i][0], rpts[i][1]))
            {
                return 0;
            }
        }
    }

    double work[POINT_MAX][2] = {};
    const int work_num = clamp_i(run_end - begin, 0, POINT_MAX);
    if(work_num < 2)
    {
        return 0;
    }
    for(int i = 0; i < work_num; ++i)
    {
        work[i][0] = rpts[begin + i][0];
        work[i][1] = rpts[begin + i][1];
    }
    work[0][0] = cx;
    work[0][1] = cy;

    double sample[POINT_MAX][2] = {};
    int sample_num = POINT_MAX;
    resample_points(work, work_num, sample, &sample_num, kMidlineSampleDist);
    if(sample_num <= 0)
    {
        return 0;
    }

    int len = 1;
    point_t last = {cx, cy};
    midline->pts[0] = last;
    midline->dist[0] = 0;
    for(int i = 1; i < sample_num && len < POINT_MAX; ++i)
    {
        push_mid(midline, &len, &last, sample[i][0], sample[i][1]);
    }
    midline->step = len;
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      双边求中线：左右点按 y 配对，宽度合格后取中点，从离参考点最近的配对后开始输出
//  @return     int          中线点数；重叠不足、配对不足或宽度不合格时返回 0
//  @note       当前普通主线不主动走 TRACK_TYPE_DUAL；保留此函数供明确接入时复用。
//-------------------------------------------------------------------------------------------------------------------
int track_dualline(const double pts0[POINT_MAX][2],
                   int num0,
                   const double pts1[POINT_MAX][2],
                   int num1,
                   int half_width,
                   int ref_x,
                   int ref_y,
                   midline_t *midline)
{
    if(midline == nullptr || num0 < kDualMinStep || num1 < kDualMinStep)
    {
        return 0;
    }

    const double min_width = std::max((double)kDualMinWidth, half_width * 0.5);
    const double max_width = RAW_W - 4.0;
    int j0 = 0;
    int pair_count = 0;
    int begin_pair = -1;
    double best_d = 1e30;

    for(int i = 0; i < num0; ++i)
    {
        if(!ipm_pt_valid(pts0[i][0], pts0[i][1]))
        {
            continue;
        }
        int best = -1;
        double best_dy = kDualPairMaxDy + 1.0;
        for(int j = j0; j < num1; ++j)
        {
            if(!ipm_pt_valid(pts1[j][0], pts1[j][1]))
            {
                continue;
            }
            const double dy = std::fabs(pts0[i][1] - pts1[j][1]);
            if(dy < best_dy)
            {
                best_dy = dy;
                best = j;
            }
            if(pts1[j][1] < pts0[i][1] - kDualMaxYGap)
            {
                break;
            }
        }
        if(best < 0 || best_dy > kDualPairMaxDy)
        {
            continue;
        }

        j0 = best;
        const double w = pts1[best][0] - pts0[i][0];
        const double gap = std::fabs(pts0[i][1] - pts1[best][1]);
        if(w < min_width || w > max_width || gap > kDualMaxYGap)
        {
            continue;
        }

        const double x = (pts0[i][0] + pts1[best][0]) * 0.5;
        const double y = (pts0[i][1] + pts1[best][1]) * 0.5;
        const double dx = x - ref_x;
        const double dy = y - ref_y;
        const double d = dx * dx + dy * dy;
        if(d < best_d)
        {
            best_d = d;
            begin_pair = pair_count;
        }
        ++pair_count;
    }
    if(pair_count < kDualMinOverlap || begin_pair < 0)
    {
        return 0;
    }

    ref_x = clamp_i(ref_x, 0, IPM_W - 1);
    ref_y = clamp_i(ref_y, 0, IPM_H - 1);
    int len = 1;
    point_t last = {ref_x, ref_y};
    midline->pts[0] = last;
    midline->dist[0] = 0;
    j0 = 0;
    pair_count = 0;
    for(int i = 0; i < num0 && len < POINT_MAX; ++i)
    {
        if(!ipm_pt_valid(pts0[i][0], pts0[i][1]))
        {
            continue;
        }
        int best = -1;
        double best_dy = kDualPairMaxDy + 1.0;
        for(int j = j0; j < num1; ++j)
        {
            if(!ipm_pt_valid(pts1[j][0], pts1[j][1]))
            {
                continue;
            }
            const double dy = std::fabs(pts0[i][1] - pts1[j][1]);
            if(dy < best_dy)
            {
                best_dy = dy;
                best = j;
            }
            if(pts1[j][1] < pts0[i][1] - kDualMaxYGap)
            {
                break;
            }
        }
        if(best < 0 || best_dy > kDualPairMaxDy)
        {
            continue;
        }

        j0 = best;
        const double w = pts1[best][0] - pts0[i][0];
        const double gap = std::fabs(pts0[i][1] - pts1[best][1]);
        if(w < min_width || w > max_width || gap > kDualMaxYGap)
        {
            continue;
        }

        if(pair_count > begin_pair)
        {
            push_mid(midline,
                     &len,
                     &last,
                     (pts0[i][0] + pts1[best][0]) * 0.5,
                     (pts0[i][1] + pts1[best][1]) * 0.5);
        }
        ++pair_count;
    }
    midline->step = len;
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      判断控制中线是否至少覆盖预瞄距离的 2/3，避免短中线被拿去算预瞄
//  @return     int          1 覆盖足够 / 0 中线过短
//  @note       这里只检查长度覆盖，不计算 guide_error。
//-------------------------------------------------------------------------------------------------------------------
int midline_has_lookahead(const midline_t *midline, int aim_distance)
{
    if(midline == nullptr || midline->step <= 0)
    {
        return 0;
    }

    int best = 0;
    int best_err = 1 << 30;
    for(int i = 0; i < midline->step; ++i)
    {
        if(midline->dist[i] <= 0)
        {
            continue;
        }
        const int err = std::abs(midline->dist[i] - aim_distance);
        if(err < best_err)
        {
            best_err = err;
            best = i;
        }
    }
    return midline->dist[best] >= aim_distance * 2 / 3;
}

int midline_has_forward_lookahead(const midline_t *midline, int aim_distance, int ref_y)
{
    if(midline == nullptr || midline->step <= 0)
    {
        return 0;
    }

    int best = -1;
    for(int i = 0; i < midline->step; ++i)
    {
        if(midline->dist[i] < aim_distance)
        {
            continue;
        }
        if(best < 0 || midline->dist[i] < midline->dist[best])
        {
            best = i;
        }
    }
    if(best < 0)
    {
        return 0;
    }
    return midline->pts[best].y < ref_y;
}
