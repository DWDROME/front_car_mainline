#include "app/assistant.hpp"

#include "app/options.hpp"
#include "tracking/perspective.hpp"
#include "clip.hpp"

#include "seekfree_assistant.hpp"
#include "seekfree_assistant_interface.hpp"
#include "zf_driver_tcp_client.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace
{
constexpr const char *k_default_ip = "192.168.0.101"; // 上位机默认 IP
constexpr int k_default_port = 8086;                  // 上位机默认端口
constexpr int k_default_div = 20;                     // 发送分频：每 div 帧发一次图传
constexpr int k_default_reconnect_div = 30;           // 断线后每 reconnect_div 帧重连一次
constexpr int k_point_limit = POINT_MAX;
constexpr uint8_t k_left_far_value = 80;              // 左远线在灰度图上叠加的像素亮度
constexpr uint8_t k_right_far_value = 220;            // 右远线在灰度图上叠加的像素亮度

struct assistant_t_impl
{
    int enabled;
    int div;
    int reconnect_div;
    int connected;
    const char *ip;
    int port;
    zf_driver_tcp_client tcp;
    // 三条显示线的 raw 坐标缓冲：0=左边线(黄)，1=控制中线反投影(红)，2=右边线(绿)。
    uint8_t x0[k_point_limit];
    uint8_t y0[k_point_limit];
    uint8_t x1[k_point_limit];
    uint8_t y1[k_point_limit];
    uint8_t x2[k_point_limit];
    uint8_t y2[k_point_limit];
    uint8_t image[RAW_H][RAW_W]; // 发送给上位机的灰度图（含远线/拐点叠加）
};

assistant_t_impl g_asst = {};

// 把成员 tcp 对象包成逐飞 assistant 库要求的 C 风格收发回调。
uint32 tcp_send_wrap(const uint8 *buf, uint32 len)
{
    return g_asst.tcp.send_data(buf, len);
}

uint32 tcp_read_wrap(uint8 *buf, uint32 len)
{
    return g_asst.tcp.read_data(buf, len);
}

// 只有 SMARTCAR_ASSISTANT 和 SMARTCAR_VIEWER 两个开关同时为真才启用上位机（VIEWER 是 legacy 别名）。
int assistant_enabled()
{
    const int en = read_env_flag("SMARTCAR_ASSISTANT", 0);
    const int viewer = read_env_flag("SMARTCAR_VIEWER", 1);
    return en && viewer;
}

// 建一次 TCP 连接并初始化逐飞 assistant 接口和相机信息；成功置 connected=1。
int connect_once()
{
    if(g_asst.tcp.init(g_asst.ip, static_cast<uint32>(g_asst.port)) != 0)
    {
        g_asst.connected = 0;
        return 0;
    }
    seekfree_assistant_interface_init(tcp_send_wrap, tcp_read_wrap);
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X,
                                                 g_asst.x0,
                                                 RAW_W,
                                                 RAW_H);
    g_asst.connected = 1;
    std::printf("front_car_mainline: assistant %s:%d connected\n", g_asst.ip, g_asst.port);
    return 1;
}

// 把 point_t 数组 clamp 到 [0,RAW-1] 后拷成上位机要的 uint8 x/y，返回有效点数。
int copy_pts(const point_t *src, int step, uint8_t *xs, uint8_t *ys)
{
    if(src == nullptr || xs == nullptr || ys == nullptr)
    {
        return 0;
    }

    const int n = std::min(step, k_point_limit);
    for(int i = 0; i < n; ++i)
    {
        xs[i] = static_cast<uint8_t>(std::clamp(src[i].x, 0, RAW_W - 1));
        ys[i] = static_cast<uint8_t>(std::clamp(src[i].y, 0, RAW_H - 1));
    }
    return n;
}

// assistant 协议三条线共用一个 dot_num。
// 短线只能补齐到同长度，不能把 dot_num 改成最短线长度，否则会裁短左右边线。
void pad_pts(uint8_t *xs, uint8_t *ys, int count, int total)
{
    if(xs == nullptr || ys == nullptr || count <= 0 || total <= count)
    {
        return;
    }

    const uint8_t last_x = xs[count - 1];
    const uint8_t last_y = ys[count - 1];
    for(int i = count; i < total; ++i)
    {
        xs[i] = last_x;
        ys[i] = last_y;
    }
}

// 在图上 (x,y) 处画一个 7x7 十字标记（标拐点/远 L 点用）。
void mark_cross(uint8_t image[RAW_H][RAW_W], int x, int y, uint8_t value)
{
    if(image == nullptr)
    {
        return;
    }

    for(int dy = -3; dy <= 3; ++dy)
    {
        const int yy = y + dy;
        if(yy >= 0 && yy < RAW_H && x >= 0 && x < RAW_W)
        {
            image[yy][x] = value;
        }
    }
    for(int dx = -3; dx <= 3; ++dx)
    {
        const int xx = x + dx;
        if(y >= 0 && y < RAW_H && xx >= 0 && xx < RAW_W)
        {
            image[y][xx] = value;
        }
    }
}

// 取边界 L 拐点的 raw 坐标：优先 original_pts，退化到 now_pts；无 L 角返回 (-1,-1)。
point_t corner_pt(const boundary_t *bd)
{
    point_t pt = {-1, -1};
    if(bd == nullptr || !bd->l_ok)
    {
        return pt;
    }
    if(bd->original_step > 0)
    {
        const int i = std::clamp(bd->l_original_index, 0, bd->original_step - 1);
        return bd->original_pts[i];
    }
    if(bd->now_step > 0)
    {
        const int i = std::clamp(bd->l_now_index, 0, bd->now_step - 1);
        return bd->now_pts[i];
    }
    return pt;
}

// 把一个边界的 L 拐点在图上画成十字标记。
void draw_l_corner(uint8_t image[RAW_H][RAW_W], const boundary_t *bd)
{
    point_t pt = corner_pt(bd);
    if(pt.x < 0 || pt.x >= RAW_W || pt.y < 0 || pt.y >= RAW_H)
    {
        return;
    }
    mark_cross(image, pt.x, pt.y, 255);
}

// 把 IPM/控制坐标点经反查表换算回 raw 像素点；无矩阵时直接取整，越界返回 0。
int ipm_to_raw_point(const runtime_t *rt, double ix, double iy, point_t *pt)
{
    if(rt == nullptr || pt == nullptr)
    {
        return 0;
    }

    int rx = round_i(ix);
    int ry = round_i(iy);
    if(rt->has_matrix)
    {
        if(!perspective_lookup_ipm_to_raw(round_i(ix), round_i(iy), &rx, &ry))
        {
            return 0;
        }
    }

    if(rx < 0 || rx >= RAW_W || ry < 0 || ry >= RAW_H)
    {
        return 0;
    }

    *pt = {rx, ry};
    return 1;
}

// 红线显示真实控制中线：rt->track.mid 是 IPM/控制坐标，必须反投影回 raw 后再发送。
int control_mid_pts(const runtime_t *rt, uint8_t *xs, uint8_t *ys)
{
    if(rt == nullptr || xs == nullptr || ys == nullptr)
    {
        return 0;
    }
    if(rt->track.track_type == TRACK_TYPE_NONE)
    {
        return 0;
    }
    if(rt->track.reject_reason != TRACK_REJECT_NONE)
    {
        return 0;
    }

    const int step = std::min(rt->track.mid.step, k_point_limit);
    if(step <= 0)
    {
        return 0;
    }

    int n = 0;
    for(int i = 0; i < step && n < k_point_limit; ++i)
    {
        const point_t &mid = rt->track.mid.pts[i];

        point_t raw = {-1, -1};
        if(!ipm_to_raw_point(rt, mid.x, mid.y, &raw))
        {
            continue;
        }

        xs[n] = static_cast<uint8_t>(raw.x);
        ys[n] = static_cast<uint8_t>(raw.y);
        ++n;
    }

    if(n < 2)
    {
        return 0;
    }
    return n;
}

// 把一条远线点列反算回 raw 后逐点叠加到图上，并在 l_index 处画十字。
void draw_far_points(uint8_t image[RAW_H][RAW_W],
                     const runtime_t *rt,
                     const double pts[POINT_MAX][2],
                     int num,
                     int l_index,
                     uint8_t value)
{
    if(image == nullptr || rt == nullptr || pts == nullptr || num <= 0)
    {
        return;
    }

    const int step = std::min(num, k_point_limit);
    for(int i = 0; i < step; ++i)
    {
        point_t p = {-1, -1};
        if(ipm_to_raw_point(rt, pts[i][0], pts[i][1], &p))
        {
            image[p.y][p.x] = value;
        }
    }

    if(l_index >= 0 && l_index < step)
    {
        point_t p = {-1, -1};
        if(ipm_to_raw_point(rt, pts[l_index][0], pts[l_index][1], &p))
        {
            mark_cross(image, p.x, p.y, 255);
        }
    }
}

// 十字 IN 阶段把左右远线点列叠加到发送图上（左远线亮度 80，右远线 220）。
void draw_farline(uint8_t image[RAW_H][RAW_W], const runtime_t *rt)
{
    if(rt == nullptr || rt->cross.state != CROSS_STATE_IN)
    {
        return;
    }

    if(rt->cross.left_far_found)
    {
        draw_far_points(image,
                        rt,
                        rt->cross.left_pts,
                        rt->cross.left_num,
                        rt->cross.left_l,
                        k_left_far_value);
    }
    if(rt->cross.right_far_found)
    {
        draw_far_points(image,
                        rt,
                        rt->cross.right_pts,
                        rt->cross.right_num,
                        rt->cross.right_l,
                        k_right_far_value);
    }
}

// 组装并下发一帧上位机数据：三条线(左/中/右) + 灰度图 + 远线/拐点叠加。
// 三条线共用一个 dot_num（取三者 max 后 pad 补齐），不能用最短线长度，否则会裁短边线。
void config_points(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return;
    }

    const int n0 = copy_pts(rt->track.left.original_pts, rt->track.left.original_step, g_asst.x0, g_asst.y0);
    const int n1 = control_mid_pts(rt, g_asst.x1, g_asst.y1);
    const int n2 = copy_pts(rt->track.right.original_pts, rt->track.right.original_step, g_asst.x2, g_asst.y2);

    // 三条线使用同一个协议长度，必须取 max 后 pad。
    // n0/n2 是 raw 原图边线；n1 是控制中线反投影到 raw 后的红线。
    const int dot_num = std::max({n0, n1, n2});

    std::memcpy(g_asst.image, rt->gray, sizeof(g_asst.image));
    draw_farline(g_asst.image, rt);
    draw_l_corner(g_asst.image, &rt->track.left);
    draw_l_corner(g_asst.image, &rt->track.right);
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X,
                                                 g_asst.image[0],
                                                 RAW_W,
                                                 RAW_H);
    if(dot_num <= 0)
    {
        seekfree_assistant_camera_boundary_config(NO_BOUNDARY, 0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        return;
    }

    pad_pts(g_asst.x0, g_asst.y0, n0, dot_num);
    pad_pts(g_asst.x1, g_asst.y1, n1, dot_num);
    pad_pts(g_asst.x2, g_asst.y2, n2, dot_num);
    seekfree_assistant_camera_boundary_config(XY_BOUNDARY,
                                              static_cast<uint16>(dot_num),
                                              n0 > 0 ? g_asst.x0 : nullptr,
                                              n1 > 0 ? g_asst.x1 : nullptr,
                                              n2 > 0 ? g_asst.x2 : nullptr,
                                              n0 > 0 ? g_asst.y0 : nullptr,
                                              n1 > 0 ? g_asst.y1 : nullptr,
                                              n2 > 0 ? g_asst.y2 : nullptr);
}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化 assistant：清空状态、读取 env 配置，启用时尝试首次 TCP 连接
//  @note       仅当 SMARTCAR_ASSISTANT 且 SMARTCAR_VIEWER 同时为真才启用；连接失败只打印日志，不影响主链。
//-------------------------------------------------------------------------------------------------------------------
void assistant_init()
{
    g_asst.enabled = 0;
    g_asst.div = 0;
    g_asst.reconnect_div = 0;
    g_asst.connected = 0;
    g_asst.ip = nullptr;
    g_asst.port = 0;
    std::memset(g_asst.x0, 0, sizeof(g_asst.x0));
    std::memset(g_asst.y0, 0, sizeof(g_asst.y0));
    std::memset(g_asst.x1, 0, sizeof(g_asst.x1));
    std::memset(g_asst.y1, 0, sizeof(g_asst.y1));
    std::memset(g_asst.x2, 0, sizeof(g_asst.x2));
    std::memset(g_asst.y2, 0, sizeof(g_asst.y2));
    std::memset(g_asst.image, 0, sizeof(g_asst.image));
    g_asst.enabled = assistant_enabled();
    g_asst.div = read_env_int_clamped("SMARTCAR_ASSISTANT_DIV", k_default_div, 1, 10000);
    g_asst.reconnect_div = read_env_int_clamped("SMARTCAR_ASSISTANT_RECONNECT_DIV", k_default_reconnect_div, 1, 10000);
    g_asst.ip = read_env_text("SMARTCAR_ASSISTANT_IP", k_default_ip);
    g_asst.port = read_env_int_clamped("SMARTCAR_ASSISTANT_PORT", k_default_port, 1, 65535);
    if(!g_asst.enabled)
    {
        return;
    }
    if(!connect_once())
    {
        std::printf("front_car_mainline: assistant %s:%d connect failed\n", g_asst.ip, g_asst.port);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      每帧上位机入口：按分频重连/发送，组装三条线和图像后下发
//  @param      rt        当前帧运行时状态（只读）
//  @param      frame_id  帧序号，用于发送分频(div)和断线重连分频(reconnect_div)
//  @note       未启用或未连接时直接返回；纯显示旁路，不改变 tracking/control 主链。
//-------------------------------------------------------------------------------------------------------------------
void assistant_tick(const runtime_t *rt, unsigned frame_id)
{
    if(!g_asst.enabled || rt == nullptr)
    {
        return;
    }

    if(!g_asst.connected)
    {
        if(frame_id % static_cast<unsigned>(g_asst.reconnect_div) != 0U)
        {
            return;
        }
        if(!connect_once())
        {
            return;
        }
    }

    if(frame_id % static_cast<unsigned>(g_asst.div) != 0U)
    {
        return;
    }

    config_points(rt);
    seekfree_assistant_camera_send();
    seekfree_assistant_data_analysis();
}
