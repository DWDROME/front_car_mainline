#include "zebra.hpp"

#include "clip.hpp"
#include "imgproc.hpp"
#include "perspective.hpp"
#include "tuning.hpp"

#include <cstdlib>
#include <cstring>

namespace
{
const int k_scan_min_i = 10; // 从中线第 10 个点开始扫，避开车头附近噪声。
const int k_scan_max_i = 80; // 最远只扫到中线上第 80 个点，避免太远处纹理误判。
const int k_scan_dx = 50; // 从中线向左右单侧最多横扫 50 像素找黑白段。
const int k_seg_min = 2; // 单个黑白段最小宽度，小于这个通常是噪声点。
const int k_seg_max = 20; // 单个黑白段最大宽度，大于这个更像普通路面块而不是斑马条纹。
const int k_seg_diff_max = 10; // 相邻两段宽度允许的最大差值，过大说明条纹不均匀。
const int k_seg_need = 6; // 单侧至少要看到 6 段以上连续黑白变化才算像斑马线。
const int k_stop_black_threshold = RAW_W * 4 / 5; // 底部黑像素超过全宽 4/5，才认为可能压到停车线。
const int k_stop_confirm_frames = 3; // 连续 3 帧都满足底部黑线条件，才真正置 stop_line。

// 把控制中线点映回原图行列。无矩阵时说明中线本身已经按原图坐标使用。
int mid_to_raw(const runtime_t *rt, point_t p, point_t *out)
{
    if(rt == nullptr || out == nullptr)
    {
        return 0;
    }

    int ix = p.x;
    int iy = p.y;
    if(rt->has_matrix)
    {
        if(!perspective_lookup_ipm_to_raw(p.x, p.y, &ix, &iy))
        {
            return 0;
        }
    }

    if(ix < 0 || ix >= RAW_W || iy < 0 || iy >= RAW_H)
    {
        return 0;
    }
    *out = {ix, iy};
    return 1;
}

// 从中线点向一侧扫黑白段，段宽过短、过长或相邻段差太大都不算斑马线。
int scan_side(const uint8_t gray[RAW_H][RAW_W], int th, int x0, int y, int dir)
{
    int seg[30] = {};
    int num = 0;
    int begin_white = gray[y][x0] > th;
    int last = begin_white;

    for(int x = x0 + dir;
        x >= 0 && x < RAW_W && std::abs(x - x0) <= k_scan_dx;
        x += dir)
    {
        const int now = gray[y][x] > th;
        if(now == last)
        {
            seg[num]++;
        }
        else
        {
            if(num + 1 >= (int)(sizeof(seg) / sizeof(seg[0])))
            {
                break;
            }
            num++;
            seg[num]++;
            last = now;
        }
    }

    int i = 1;
    for(; i < num; ++i)
    {
        if(seg[i] < k_seg_min ||
           seg[i] >= k_seg_max ||
           std::abs(seg[i + 1] - seg[i]) >= k_seg_diff_max)
        {
            break;
        }
    }
    return i > k_seg_need;
}

// 统计底部起线行(START_HIGH)上灰度低于阈值的像素数，用于压线/停车线判断。
int bottom_black_count(const uint8_t gray[RAW_H][RAW_W], int th)
{
    int num = 0;
    for(int x = 0; x < RAW_W; ++x)
    {
        if(gray[START_HIGH][x] < th)
        {
            num++;
        }
    }
    return num;
}
}

// 斑马线检测：
// 输入：mainline 选出的扫描中线、原图灰度和动态阈值。
// 输出：zebra.detected 表示中线两侧有连续黑白段；stop_line 表示底部大面积黑线确认。
// 风险：k_scan_dx 和 k_stop_confirm_frames 会直接影响误识别/漏识别，实车调参要小步改。
void zebra_process(runtime_t *rt, const midline_t *scan_mid)
{
    if(rt == nullptr)
    {
        return;
    }

    const int th = frame_seed_threshold(rt->gray, rt->mid_position);
    rt->zebra.detected = 0;

    if(scan_mid != nullptr && scan_mid->step > k_scan_min_i)
    {
        const int end = std::min(k_scan_max_i, scan_mid->step);
        for(int i = k_scan_min_i; i < end; ++i)
        {
            point_t pt = {-1, -1};
            if(!mid_to_raw(rt, scan_mid->pts[i], &pt))
            {
                break;
            }
            int left_ok = scan_side(rt->gray, th, pt.x, pt.y, -1);
            int right_ok = 0;
            if(left_ok)
            {
                right_ok = scan_side(rt->gray, th, pt.x, pt.y, 1);
            }
            if(left_ok && right_ok)
            {
                rt->zebra.detected = 1;
                break;
            }
        }
    }

    if(bottom_black_count(rt->gray, th) > k_stop_black_threshold)
    {
        rt->zebra.stop_count++;
    }
    else
    {
        rt->zebra.stop_count = 0;
    }
    rt->zebra.stop_line = rt->zebra.stop_count > k_stop_confirm_frames;
}
