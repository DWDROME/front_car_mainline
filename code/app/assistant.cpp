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
constexpr int k_display_point_stride = 2;             // 只影响上位机显示线，控制/识别点列不受影响
constexpr int k_point_limit = POINT_MAX;
constexpr int k_assistant_boundary_capacity = SEEKFREE_ASSISTANT_CAMERA_MAX_BOUNDARY;
constexpr int k_assistant_boundary_count_field_limit = 0x0F; // camera_type/dot_type 低四位保存边界数量
constexpr int k_assistant_coord8_limit = 256;         // dot_type 未置 16-bit 坐标位，坐标必须落在 0..255
constexpr int k_assistant_dot_count_limit = UINT16_MAX;
constexpr uint8_t k_left_far_value = 80;              // 左远线在灰度图上叠加的像素亮度
constexpr uint8_t k_right_far_value = 220;            // 右远线在灰度图上叠加的像素亮度
constexpr uint8_t k_ring_opp_value = 170;             // 环岛检测补边在灰度图上叠加的像素亮度
constexpr int k_seed_box_radius = 3;                  // seed 点显示方框半径
constexpr int k_marker_radius = 3;                    // L 角/远线十字标记半径
constexpr uint8_t k_marker_value = 255;               // L 角/远线十字标记亮度
constexpr int k_reference_seed_row = 84;              // RT1064 begin_y 按 120 高度缩放后的起搜行

enum display_channel_t
{
    DISPLAY_CHANNEL_LEFT = 0,
    DISPLAY_CHANNEL_MID = 1,
    DISPLAY_CHANNEL_RIGHT = 2,
    DISPLAY_CHANNEL_SEED_ROW = 3,
    DISPLAY_CHANNEL_LEFT_SEED = 4,
    DISPLAY_CHANNEL_RIGHT_SEED = 5,
    DISPLAY_CHANNEL_COUNT = 6,
};

constexpr int k_display_boundary_limit = DISPLAY_CHANNEL_COUNT; // 左/中/右 + seed 行 + 左/右 seed 方框

static_assert(k_display_boundary_limit <= k_assistant_boundary_capacity,
              "display boundary count exceeds SeekFree assistant protocol capacity");
static_assert(k_display_boundary_limit <= k_assistant_boundary_count_field_limit,
              "display boundary count exceeds assistant packet low-nibble capacity");
static_assert(k_point_limit <= k_assistant_dot_count_limit,
              "assistant dot_num field is uint16");
static_assert(RAW_W <= k_assistant_coord8_limit && RAW_H <= k_assistant_coord8_limit,
              "assistant XY boundary uses 8-bit coordinates");

struct assistant_t_impl
{
    int enabled;
    int div;
    int reconnect_div;
    int connected;
    const char *ip;
    int port;
    zf_driver_tcp_client tcp;
    // 显示边界 raw 坐标缓冲：通道语义见 display_channel_t。
    uint8_t display_x[k_display_boundary_limit][k_point_limit];
    uint8_t display_y[k_display_boundary_limit][k_point_limit];
    uint8_t image[RAW_H][RAW_W]; // 发送给上位机的灰度图（含远线/拐点叠加）
};

struct display_boundary_t
{
    uint8_t *xs;
    uint8_t *ys;
    int point_count;
    int valid_channel;
};

assistant_t_impl g_asst = {};

int raw_point_valid(int x, int y)
{
    return x >= 0 && x < RAW_W && y >= 0 && y < RAW_H;
}

// ==== TCP 回调边界 ====
// 把成员 tcp 对象包成逐飞 assistant 库要求的 C 风格收发回调。
uint32 tcp_send_wrap(const uint8 *buf, uint32 len)
{
    const uint32 sent = g_asst.tcp.send_data(buf, len);
    if(sent != len)
    {
        g_asst.connected = 0;
    }
    return sent;
}

uint32 tcp_read_wrap(uint8 *buf, uint32 len)
{
    const uint32 got = g_asst.tcp.read_data(buf, len);
    if(got == static_cast<uint32>(-1))
    {
        g_asst.connected = 0;
        return 0;
    }
    return got;
}

// ==== assistant 数据发送 ====
int assistant_send_all(const uint8 *buf, uint32 len)
{
    if(!g_asst.connected)
    {
        return 0;
    }
    if(len == 0)
    {
        return 1;
    }
    if(buf == nullptr)
    {
        return 0;
    }
    return tcp_send_wrap(buf, len) == len ? 1 : 0;
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
    g_asst.connected = 1;
    std::printf("front_car_mainline: assistant %s:%d connected\n", g_asst.ip, g_asst.port);
    return 1;
}

int append_display_pt(uint8_t *xs, uint8_t *ys, int *count, int x, int y)
{
    if(xs == nullptr || ys == nullptr || count == nullptr || *count >= k_point_limit)
    {
        return 0;
    }
    xs[*count] = static_cast<uint8_t>(std::clamp(x, 0, RAW_W - 1));
    ys[*count] = static_cast<uint8_t>(std::clamp(y, 0, RAW_H - 1));
    ++(*count);
    return 1;
}

// 把 point_t 数组隔点 clamp 到 [0,RAW-1] 后拷成上位机要的 uint8 x/y，返回有效点数。
int copy_pts(const point_t *src, int step, uint8_t *xs, uint8_t *ys)
{
    if(src == nullptr || xs == nullptr || ys == nullptr)
    {
        return 0;
    }
    if(step <= 0)
    {
        return 0;
    }

    const int nsrc = std::min(step, k_point_limit);
    int n = 0;
    for(int i = 0; i < nsrc && n < k_point_limit; i += k_display_point_stride)
    {
        append_display_pt(xs, ys, &n, src[i].x, src[i].y);
    }
    return n;
}

// assistant 图像边界共用一个 dot_num。
// 短线只能补齐到同长度，不能把 dot_num 改成最短线长度，否则会裁短边线或 seed 方框。
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

point_t boundary_seed_pt(const boundary_t &bd)
{
    if(bd.original_step <= 0)
    {
        return {-1, -1};
    }
    const point_t seed = bd.original_pts[0];
    if(!raw_point_valid(seed.x, seed.y))
    {
        return {-1, -1};
    }
    return seed;
}

int seed_display_row(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return k_reference_seed_row;
    }

    const point_t left = boundary_seed_pt(rt->track.left);
    const point_t right = boundary_seed_pt(rt->track.right);
    const int left_ok = raw_point_valid(left.x, left.y);
    const int right_ok = raw_point_valid(right.x, right.y);
    if(left_ok && right_ok)
    {
        return (left.y + right.y) / 2;
    }
    if(left_ok)
    {
        return left.y;
    }
    if(right_ok)
    {
        return right.y;
    }
    return k_reference_seed_row;
}

int seed_row_pts(const runtime_t *rt, uint8_t *xs, uint8_t *ys)
{
    if(xs == nullptr || ys == nullptr)
    {
        return 0;
    }

    int n = 0;
    const int y = std::clamp(seed_display_row(rt), 0, RAW_H - 1);
    for(int x = 0; x < RAW_W && n < k_point_limit; ++x)
    {
        append_display_pt(xs, ys, &n, x, y);
    }
    return n;
}

int seed_box_pts(point_t seed, uint8_t *xs, uint8_t *ys)
{
    if(xs == nullptr || ys == nullptr ||
       !raw_point_valid(seed.x, seed.y))
    {
        return 0;
    }

    int n = 0;
    const int r = k_seed_box_radius;
    const int x0 = std::clamp(seed.x - r, 0, RAW_W - 1);
    const int x1 = std::clamp(seed.x + r, 0, RAW_W - 1);
    const int y0 = std::clamp(seed.y - r, 0, RAW_H - 1);
    const int y1 = std::clamp(seed.y + r, 0, RAW_H - 1);

    for(int x = x0; x <= x1; ++x)
    {
        append_display_pt(xs, ys, &n, x, y0);
    }
    for(int y = y0 + 1; y <= y1; ++y)
    {
        append_display_pt(xs, ys, &n, x1, y);
    }
    for(int x = x1 - 1; x >= x0; --x)
    {
        append_display_pt(xs, ys, &n, x, y1);
    }
    for(int y = y1 - 1; y > y0; --y)
    {
        append_display_pt(xs, ys, &n, x0, y);
    }
    return n;
}

int send_camera_packet(uint8 boundary_num)
{
    seekfree_assistant_camera_struct packet = {};
    packet.head = SEEKFREE_ASSISTANT_SEND_HEAD;
    packet.function = SEEKFREE_ASSISTANT_CAMERA_FUNCTION;
    packet.camera_type = (SEEKFREE_ASSISTANT_MT9V03X << 5) | boundary_num;
    packet.length = sizeof(seekfree_assistant_camera_struct);
    packet.image_width = RAW_W;
    packet.image_height = RAW_H;

    if(!assistant_send_all(reinterpret_cast<const uint8 *>(&packet), sizeof(packet)))
    {
        return 0;
    }
    return assistant_send_all(reinterpret_cast<const uint8 *>(g_asst.image[0]), RAW_W * RAW_H);
}

int send_dot_packet(const display_boundary_t *bd, int boundary_count, uint16 dot_num)
{
    if(bd == nullptr || boundary_count <= 0 ||
       boundary_count > k_display_boundary_limit || dot_num == 0)
    {
        return 0;
    }

    seekfree_assistant_camera_dot_struct packet = {};
    packet.head = SEEKFREE_ASSISTANT_SEND_HEAD;
    packet.function = SEEKFREE_ASSISTANT_CAMERA_DOT_FUNCTION;
    packet.dot_type = static_cast<uint8>((XY_BOUNDARY << 6) | boundary_count);
    packet.length = sizeof(seekfree_assistant_camera_dot_struct);
    packet.dot_num = dot_num;
    for(int i = 0; i < boundary_count; ++i)
    {
        if(bd[i].xs == nullptr || bd[i].ys == nullptr ||
           bd[i].valid_channel < 0 || bd[i].valid_channel >= k_display_boundary_limit)
        {
            return 0;
        }
        packet.valid_flag |= static_cast<uint8>(1U << bd[i].valid_channel);
    }

    if(!assistant_send_all(reinterpret_cast<const uint8 *>(&packet), sizeof(packet)))
    {
        return 0;
    }
    // 坐标数组按非空边界紧凑发送；valid_flag 只告诉上位机这些数组对应哪个显示通道。
    for(int i = 0; i < boundary_count; ++i)
    {
        if(!assistant_send_all(reinterpret_cast<const uint8 *>(bd[i].xs), dot_num) ||
           !assistant_send_all(reinterpret_cast<const uint8 *>(bd[i].ys), dot_num))
        {
            return 0;
        }
    }
    return 1;
}

void add_display_boundary(display_boundary_t *bd,
                          int *boundary_count,
                          int *dot_num,
                          int valid_channel,
                          int point_count)
{
    if(bd == nullptr || boundary_count == nullptr || dot_num == nullptr ||
       point_count <= 0 || point_count > k_point_limit ||
       valid_channel < 0 || valid_channel >= k_display_boundary_limit ||
       *boundary_count >= k_display_boundary_limit)
    {
        return;
    }

    bd[*boundary_count] = {
        g_asst.display_x[valid_channel],
        g_asst.display_y[valid_channel],
        point_count,
        valid_channel,
    };
    ++(*boundary_count);
    *dot_num = std::max(*dot_num, point_count);
}

int send_display_frame(display_boundary_t *bd, int boundary_count, int dot_num)
{
    if(boundary_count <= 0 || dot_num <= 0)
    {
        return send_camera_packet(0);
    }
    if(bd == nullptr || boundary_count > k_display_boundary_limit || dot_num > k_point_limit)
    {
        return 0;
    }

    const uint8 boundary_num = static_cast<uint8>(boundary_count);
    if(!send_camera_packet(boundary_num))
    {
        return 0;
    }

    const uint16 dn = static_cast<uint16>(dot_num);
    for(int i = 0; i < boundary_num; ++i)
    {
        if(bd[i].point_count <= 0 || bd[i].point_count > dn)
        {
            return 0;
        }
        pad_pts(bd[i].xs, bd[i].ys, bd[i].point_count, dn);
    }
    return send_dot_packet(bd, boundary_num, dn);
}

// 在图上 (x,y) 处画一个十字标记（标拐点/远 L 点用）。
void mark_cross(uint8_t image[RAW_H][RAW_W], int x, int y, uint8_t value)
{
    if(image == nullptr)
    {
        return;
    }

    for(int dy = -k_marker_radius; dy <= k_marker_radius; ++dy)
    {
        const int yy = y + dy;
        if(raw_point_valid(x, yy))
        {
            image[yy][x] = value;
        }
    }
    for(int dx = -k_marker_radius; dx <= k_marker_radius; ++dx)
    {
        const int xx = x + dx;
        if(raw_point_valid(xx, y))
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
    if(!raw_point_valid(pt.x, pt.y))
    {
        return;
    }
    mark_cross(image, pt.x, pt.y, k_marker_value);
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
        if(!perspective_lookup_ipm_to_raw(rx, ry, &rx, &ry))
        {
            return 0;
        }
    }

    if(!raw_point_valid(rx, ry))
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
    for(int i = 0; i < step && n < k_point_limit; i += k_display_point_stride)
    {
        const point_t &mid = rt->track.mid.pts[i];

        point_t raw = {-1, -1};
        if(!ipm_to_raw_point(rt, mid.x, mid.y, &raw))
        {
            continue;
        }

        append_display_pt(xs, ys, &n, raw.x, raw.y);
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
            mark_cross(image, p.x, p.y, k_marker_value);
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

// ==== 环岛补边叠加显示 ====
void draw_ring_opp(uint8_t image[RAW_H][RAW_W], const runtime_t *rt)
{
    if(rt == nullptr || rt->track.ring_opp_build_result <= 0)
    {
        return;
    }

    const boundary_t *opp = &rt->track.left;
    if(rt->track.ring_opp_left)
    {
        opp = &rt->track.right;
    }

    const int step = std::min(opp->original_step, k_point_limit);
    for(int i = 0; i < step; i += k_display_point_stride)
    {
        const point_t p = opp->original_pts[i];
        if(raw_point_valid(p.x, p.y))
        {
            image[p.y][p.x] = k_ring_opp_value;
        }
    }
}

// 组装并下发一帧上位机数据：左/中/右 + seed 行/方框 + 灰度图 + 远线/拐点叠加。
// 显示边界共用一个 dot_num（取 max 后 pad 补齐），不能用最短线长度，否则会裁短边线。
int config_points(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }

    int point_count[k_display_boundary_limit] = {};
    point_count[DISPLAY_CHANNEL_LEFT] =
        copy_pts(rt->track.left.original_pts,
                 rt->track.left.original_step,
                 g_asst.display_x[DISPLAY_CHANNEL_LEFT],
                 g_asst.display_y[DISPLAY_CHANNEL_LEFT]);
    point_count[DISPLAY_CHANNEL_MID] =
        control_mid_pts(rt,
                        g_asst.display_x[DISPLAY_CHANNEL_MID],
                        g_asst.display_y[DISPLAY_CHANNEL_MID]);
    point_count[DISPLAY_CHANNEL_RIGHT] =
        copy_pts(rt->track.right.original_pts,
                 rt->track.right.original_step,
                 g_asst.display_x[DISPLAY_CHANNEL_RIGHT],
                 g_asst.display_y[DISPLAY_CHANNEL_RIGHT]);
    point_count[DISPLAY_CHANNEL_SEED_ROW] =
        seed_row_pts(rt,
                     g_asst.display_x[DISPLAY_CHANNEL_SEED_ROW],
                     g_asst.display_y[DISPLAY_CHANNEL_SEED_ROW]);
    const point_t left_seed = boundary_seed_pt(rt->track.left);
    const point_t right_seed = boundary_seed_pt(rt->track.right);
    if(raw_point_valid(left_seed.x, left_seed.y))
    {
        point_count[DISPLAY_CHANNEL_LEFT_SEED] =
            seed_box_pts(left_seed,
                         g_asst.display_x[DISPLAY_CHANNEL_LEFT_SEED],
                         g_asst.display_y[DISPLAY_CHANNEL_LEFT_SEED]);
    }
    if(raw_point_valid(right_seed.x, right_seed.y))
    {
        point_count[DISPLAY_CHANNEL_RIGHT_SEED] =
            seed_box_pts(right_seed,
                         g_asst.display_x[DISPLAY_CHANNEL_RIGHT_SEED],
                         g_asst.display_y[DISPLAY_CHANNEL_RIGHT_SEED]);
    }

    display_boundary_t bd[k_display_boundary_limit] = {};
    int boundary_count = 0;
    int dot_num = 0;
    for(int channel = 0; channel < k_display_boundary_limit; ++channel)
    {
        add_display_boundary(bd, &boundary_count, &dot_num, channel, point_count[channel]);
    }

    std::memcpy(g_asst.image, rt->gray, sizeof(g_asst.image));
    draw_farline(g_asst.image, rt);
    draw_ring_opp(g_asst.image, rt);
    draw_l_corner(g_asst.image, &rt->track.left);
    draw_l_corner(g_asst.image, &rt->track.right);
    return send_display_frame(bd, boundary_count, dot_num);
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
    std::memset(g_asst.display_x, 0, sizeof(g_asst.display_x));
    std::memset(g_asst.display_y, 0, sizeof(g_asst.display_y));
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
//  @brief      每帧上位机入口：按分频重连/发送，组装显示边界和图像后下发
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

    if(!config_points(rt) || !g_asst.connected)
    {
        return;
    }
    seekfree_assistant_data_analysis();
}
