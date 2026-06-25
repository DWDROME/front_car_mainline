#include "app/assistant.hpp"

#include "app/options.hpp"
#include "tracking/perspective.hpp"
#include "clip.hpp"

#include "seekfree_assistant.hpp"
#include "seekfree_assistant_interface.hpp"
#include "zf_driver_tcp_client.hpp"

extern "C" {
#include "headfile.h"
}

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

// 上位机显示直读 ATG 全局变量，对应大佬 Cpu0_Main.c 的 TFT 调试语义：
// 发送图为上下拼接的 160x240：上半是原图，下半是 IPM 俯视图（逐像素 inv_rot 反向采样）。
//   左/右边线 = ipts0/ipts1 (raw 追线点，画在上半)
//   中线      = inv_rptsn (port step 每帧已把 rptsn 投回原图，画在上半)
//   断点扫描线 = 圆环入口 inner-hit 的 Lpt seed 竖向参考线；左右种子 ipts0[0]/ipts1[0] 画方框叠加在图上
//   角点      = Lpt0/Lpt1 (rpts0s/rpts1s 上的 L 角，经 inv_rot 投回原图画十字)
//   圆环 B/C  = circle_B_point/circle_C_point (raw 几何点，复用角点 marker 通道并叠加到原图)
//   环岛补线  = Splicing_*/leftline/rightline 按大佬显示分支的状态条件叠加在上半图
//               （环岛 IN/OUT 时 rpts 控制选线直接取 Splicing_*_center，补线就是控制输入）
//   IPM 下半  = rpts0s/rpts1s/rptsn 既作为 boundary 发给上位机，也用灰度像素直接叠加
// 失败帧合同：reference_step.c 每帧入口清 ipts*_num/rptsn_num，find_corners() 清 Lpt*_found，
// 因此这里不会显示旧帧点列。本文件是纯显示旁路，不读 runtime_t 算法字段，只取 rt->gray 当底图。

namespace
{
constexpr const char *k_default_ip = "192.168.0.100"; // 上位机默认 IP
constexpr int k_default_port = 8086;                  // 上位机默认端口
constexpr int k_default_div = 20;                     // 发送分频：每 div 帧发一次图传
constexpr int k_default_reconnect_div = 30;           // 断线后每 reconnect_div 帧重连一次
constexpr int k_default_connect_ms = 30;              // 单次 TCP 连接最多等待时间，避免卡住主循环
constexpr int k_display_point_stride = 2;             // 只影响上位机显示线，控制/识别点列不受影响
constexpr int k_point_limit = POINT_MAX;
constexpr int k_assistant_boundary_capacity = SEEKFREE_ASSISTANT_CAMERA_MAX_BOUNDARY;
constexpr int k_assistant_boundary_count_field_limit = 0x0F; // camera_type/dot_type 低四位保存边界数量
constexpr int k_assistant_coord8_limit = 256;         // dot_type 未置 16-bit 坐标位，坐标必须落在 0..255
constexpr int k_assistant_dot_count_limit = UINT16_MAX;
constexpr int k_marker_radius = 3;                    // L 角十字标记半径
constexpr uint8_t k_marker_value = 255;               // L 角十字标记亮度
constexpr uint8_t k_marker_dark_value = 0;             // 几何点外框亮度；配合亮十字保证黑/白底都能看见
constexpr int k_seed_box_radius = 3;                  // 种子点显示方框半径
constexpr uint8_t k_seed_box_value = 255;             // 种子点方框亮度
constexpr uint8_t k_splice_edge_value = 80;           // 环岛拼接边线/几何延长线叠加亮度（暗）
constexpr uint8_t k_splice_center_value = 220;        // 环岛补线中心线叠加亮度（亮；它就是控制选线来源）
constexpr int k_send_image_h = RAW_H + IPM_H;         // 发送图高度：上半原图 + 下半 IPM 俯视图
constexpr uint8_t k_ipm_left_value = 80;              // IPM 半区左边线 rpts0s 亮度
constexpr uint8_t k_ipm_right_value = 220;            // IPM 半区右边线 rpts1s 亮度
constexpr uint8_t k_ipm_mid_value = 255;              // IPM 半区控制中线 rptsn 亮度
constexpr uint8_t k_ipm_blank_value = 255;            // IPM 反算不到原图的像素填白

enum display_channel_t
{
    DISPLAY_CHANNEL_LEFT = 0,
    DISPLAY_CHANNEL_MID = 1,
    DISPLAY_CHANNEL_RIGHT = 2,
    DISPLAY_CHANNEL_ENTRY_SCAN = 3,
    DISPLAY_CHANNEL_IPM_LEFT = 4,
    DISPLAY_CHANNEL_IPM_MID = 5,
    DISPLAY_CHANNEL_IPM_RIGHT = 6,
    DISPLAY_CHANNEL_LPT = 7,
    DISPLAY_CHANNEL_COUNT = 8,
};

constexpr int k_display_boundary_limit = DISPLAY_CHANNEL_COUNT; // raw 左/中/右 / 断点扫描 / IPM 左/中/右 / L/B/C 标记

static_assert(k_display_boundary_limit <= k_assistant_boundary_capacity,
              "display boundary count exceeds SeekFree assistant protocol capacity");
static_assert(k_display_boundary_limit <= k_assistant_boundary_count_field_limit,
              "display boundary count exceeds assistant packet low-nibble capacity");
static_assert(k_point_limit <= k_assistant_dot_count_limit,
              "assistant dot_num field is uint16");
static_assert(RAW_W <= k_assistant_coord8_limit && k_send_image_h <= k_assistant_coord8_limit,
              "assistant XY boundary uses 8-bit coordinates");

struct assistant_t_impl
{
    int enabled;
    int div;
    int reconnect_div;
    int connected;
    const char *ip;
    int port;
    int connect_ms;
    zf_driver_tcp_client tcp;
    // 显示边界 raw 坐标缓冲：通道语义见 display_channel_t。
    uint8_t display_x[k_display_boundary_limit][k_point_limit];
    uint8_t display_y[k_display_boundary_limit][k_point_limit];
    uint8_t image[k_send_image_h][RAW_W]; // 发送图：上半原图（含叠加），下半 IPM 俯视图
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
    if(g_asst.tcp.init_with_timeout(g_asst.ip,
                                    static_cast<uint32>(g_asst.port),
                                    static_cast<uint32>(g_asst.connect_ms)) != 0)
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
    ys[*count] = static_cast<uint8_t>(std::clamp(y, 0, k_send_image_h - 1));
    ++(*count);
    return 1;
}

// 把 ATG raw 整型点列（ipts0/ipts1）隔点拷成上位机要的 uint8 x/y，返回有效点数。
int copy_atg_raw_pts(const int src[][2], int num, uint8_t *xs, uint8_t *ys)
{
    if(src == nullptr || xs == nullptr || ys == nullptr || num <= 0)
    {
        return 0;
    }

    int n = 0;
    for(int i = 0; i < num && n < k_point_limit; i += k_display_point_stride)
    {
        if(!raw_point_valid(src[i][0], src[i][1]))
        {
            continue;
        }
        append_display_pt(xs, ys, &n, src[i][0], src[i][1]);
    }
    return n;
}

// 把 ATG 已投回原图的浮点点列（inv_rptsn）隔点拷成 uint8 x/y；投影出界点直接跳过，不 clamp 到边缘。
int copy_atg_inv_pts(const float src[][2], int num, uint8_t *xs, uint8_t *ys)
{
    if(src == nullptr || xs == nullptr || ys == nullptr || num <= 0)
    {
        return 0;
    }

    int n = 0;
    for(int i = 0; i < num && n < k_point_limit; i += k_display_point_stride)
    {
        const int x = round_i(src[i][0]);
        const int y = round_i(src[i][1]);
        if(!raw_point_valid(x, y))
        {
            continue;
        }
        append_display_pt(xs, ys, &n, x, y);
    }
    return n;
}

// 把 IPM 域点列拷成上位机 XY boundary，纵坐标偏移到下半图。
int copy_atg_ipm_pts(const float src[][2], int num, uint8_t *xs, uint8_t *ys)
{
    if(src == nullptr || xs == nullptr || ys == nullptr || num <= 0)
    {
        return 0;
    }

    int n = 0;
    for(int i = 0; i < num && n < k_point_limit; i += k_display_point_stride)
    {
        const int x = round_i(src[i][0]);
        const int y = round_i(src[i][1]);
        if(x < 0 || x >= IPM_W || y < 0 || y >= IPM_H)
        {
            continue;
        }
        append_display_pt(xs, ys, &n, x, RAW_H + y);
    }
    return n;
}

// 上半 raw 图叠加专用的 IPM->raw 反投：参考版显示语义，不做 IPM 渲染域入口检查。
// ATG 的 IPM 点列不受 160x120 渲染域约束（pixel_per_meter=116 时 1m 外 y<0，宽度可到 187），
// 远处 L 点/补线点 IPM 坐标出渲染域是正常的；只要反投回 raw 后在画面内就应该显示。
// perspective_lookup_ipm_to_raw() 的域检查只适用于下半 IPM 渲染图，不要用它画上半图标记。
int ipm_pt_to_raw_display(float ix, float iy, int *x, int *y)
{
    if(x == nullptr || y == nullptr)
    {
        return 0;
    }

    const float x0 = Cal_inv_rot_x(ix, iy);
    const float y0 = Cal_inv_rot_y(ix, iy);
    const int rx = round_i(x0);
    const int ry = round_i(y0);
    if(!raw_point_valid(rx, ry))
    {
        return 0;
    }
    *x = rx;
    *y = ry;
    return 1;
}

void append_lpt_cross(int found, const float pts[][2], int num, int id, uint8_t *xs, uint8_t *ys, int *count)
{
    if(!found || pts == nullptr || xs == nullptr || ys == nullptr || count == nullptr || id < 0 || id >= num)
    {
        return;
    }

    int x = 0;
    int y = 0;
    if(!ipm_pt_to_raw_display(pts[id][0], pts[id][1], &x, &y))
    {
        return;
    }

    for(int dy = -k_marker_radius; dy <= k_marker_radius; ++dy)
    {
        if(raw_point_valid(x, y + dy))
        {
            append_display_pt(xs, ys, count, x, y + dy);
        }
    }
    for(int dx = -k_marker_radius; dx <= k_marker_radius; ++dx)
    {
        if(dx == 0)
        {
            continue;
        }
        if(raw_point_valid(x + dx, y))
        {
            append_display_pt(xs, ys, count, x + dx, y);
        }
    }
}

void append_raw_cross(int found, int x, int y, uint8_t *xs, uint8_t *ys, int *count)
{
    if(!found || xs == nullptr || ys == nullptr || count == nullptr || !raw_point_valid(x, y))
    {
        return;
    }

    for(int dy = -k_marker_radius; dy <= k_marker_radius; ++dy)
    {
        if(raw_point_valid(x, y + dy))
        {
            append_display_pt(xs, ys, count, x, y + dy);
        }
    }
    for(int dx = -k_marker_radius; dx <= k_marker_radius; ++dx)
    {
        if(dx == 0)
        {
            continue;
        }
        if(raw_point_valid(x + dx, y))
        {
            append_display_pt(xs, ys, count, x + dx, y);
        }
    }
}

int copy_marker_crosses(uint8_t *xs, uint8_t *ys)
{
    int n = 0;
    append_lpt_cross(Lpt0_found ? 1 : 0, rpts0s, rpts0s_num, Lpt0_rpts0s_id, xs, ys, &n);
    append_lpt_cross(Lpt1_found ? 1 : 0, rpts1s, rpts1s_num, Lpt1_rpts1s_id, xs, ys, &n);
    append_raw_cross(circle_B_point.found, circle_B_point.raw_x, circle_B_point.raw_y, xs, ys, &n);
    append_raw_cross(circle_C_point.found, circle_C_point.raw_x, circle_C_point.raw_y, xs, ys, &n);
    return n;
}

// assistant 图像边界共用一个 dot_num。
// 短线只能补齐到同长度，不能把 dot_num 改成最短线长度，否则会裁短边线。
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

int send_camera_packet(uint8 boundary_num)
{
    seekfree_assistant_camera_struct packet = {};
    packet.head = SEEKFREE_ASSISTANT_SEND_HEAD;
    packet.function = SEEKFREE_ASSISTANT_CAMERA_FUNCTION;
    packet.camera_type = (SEEKFREE_ASSISTANT_MT9V03X << 5) | boundary_num;
    packet.length = sizeof(seekfree_assistant_camera_struct);
    packet.image_width = RAW_W;
    packet.image_height = k_send_image_h;

    if(!assistant_send_all(reinterpret_cast<const uint8 *>(&packet), sizeof(packet)))
    {
        return 0;
    }
    return assistant_send_all(reinterpret_cast<const uint8 *>(g_asst.image[0]), RAW_W * k_send_image_h);
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

// 在图上 (x,y) 处画一个十字标记（标 L 角用）。
void mark_cross(uint8_t image[][RAW_W], int x, int y, uint8_t value)
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

// 把 ATG 的 L 角画到发送图上：角点坐标在 rpts0s/rpts1s（IPM 重采样点列），
// 必须经 inv_rot 反投回 raw；不能拿 rpts*s 索引去查 ipts*（两个点列长度和间距不同）。
void draw_atg_corner(uint8_t image[][RAW_W],
                     int found,
                     const float pts[][2],
                     int num,
                     int id)
{
    if(image == nullptr || !found || pts == nullptr || id < 0 || id >= num)
    {
        return;
    }

    int x = 0;
    int y = 0;
    if(!ipm_pt_to_raw_display(pts[id][0], pts[id][1], &x, &y))
    {
        return;
    }
    mark_cross(image, x, y, k_marker_value);
}

int circle_entry_scan_seed_raw(int *seed_x, int *seed_y)
{
    if(seed_x == nullptr || seed_y == nullptr)
    {
        return 0;
    }

    // 入口侧判定为上位机显示用。种子公式(左 +2/-5、右 +5/-5)单一来源在
    // circle.c::circle_entry_inner_seed,这里只复用,避免重复公式造成显示线与算法扫描线漂移。
    const int left_entry_side =
        circle_type == CIRCLE_LEFT_BEGIN ||
        (circle_type == CIRCLE_NONE && Lpt0_found && !Lpt1_found);
    const int right_entry_side =
        circle_type == CIRCLE_RIGHT_BEGIN ||
        (circle_type == CIRCLE_NONE && !Lpt0_found && Lpt1_found);

    int left_side = -1;
    if(left_entry_side)
    {
        left_side = 1;
    }
    else if(right_entry_side)
    {
        left_side = 0;
    }
    else
    {
        return 0;
    }

    float seed_raw_x = 0.0F;
    float seed_raw_y = 0.0F;
    return circle_entry_inner_seed(left_side, seed_x, seed_y, &seed_raw_x, &seed_raw_y);
}

// 圆环入口断点/inner-hit 诊断线：与 circle.c 的 Lpt seed 同源，显示为竖线。
// 它不是 begin_y 起搜横线；它用来确认入口 inner-hit 正在从哪一列附近找黑点。
int entry_scan_line_pts(uint8_t *xs, uint8_t *ys)
{
    if(xs == nullptr || ys == nullptr)
    {
        return 0;
    }

    int seed_x = 0;
    int seed_y = 0;
    if(!circle_entry_scan_seed_raw(&seed_x, &seed_y))
    {
        return 0;
    }

    int n = 0;
    for(int y = 0; y < RAW_H && n < k_point_limit; y += k_display_point_stride)
    {
        append_display_pt(xs, ys, &n, seed_x, y);
    }
    append_raw_cross(1, seed_x, seed_y, xs, ys, &n);
    return n;
}

void draw_entry_scan_line_on_image(uint8_t image[][RAW_W])
{
    if(image == nullptr)
    {
        return;
    }

    int seed_x = 0;
    int seed_y = 0;
    if(!circle_entry_scan_seed_raw(&seed_x, &seed_y))
    {
        return;
    }

    for(int y = 0; y < RAW_H; ++y)
    {
        image[y][seed_x] = k_marker_value;
    }
    mark_cross(image, seed_x, seed_y, k_marker_dark_value);
}

// 在图上 (x,y) 处画一个空心方框（标种子点用，和角点十字区分）。
void mark_box(uint8_t image[][RAW_W], int x, int y, uint8_t value)
{
    if(image == nullptr || !raw_point_valid(x, y))
    {
        return;
    }

    const int r = k_seed_box_radius;
    for(int d = -r; d <= r; ++d)
    {
        const int xx = x + d;
        if(xx >= 0 && xx < RAW_W)
        {
            if(y - r >= 0)
            {
                image[y - r][xx] = value;
            }
            if(y + r < RAW_H)
            {
                image[y + r][xx] = value;
            }
        }
        const int yy = y + d;
        if(yy >= 0 && yy < RAW_H)
        {
            if(x - r >= 0)
            {
                image[yy][x - r] = value;
            }
            if(x + r < RAW_W)
            {
                image[yy][x + r] = value;
            }
        }
    }
}

void draw_circle_anchor_point(uint8_t image[][RAW_W], const circle_anchor_point_t *point)
{
    if(image == nullptr || point == nullptr || !point->found ||
       !raw_point_valid(point->raw_x, point->raw_y))
    {
        return;
    }

    mark_cross(image, point->raw_x, point->raw_y, k_marker_value);
    mark_box(image, point->raw_x, point->raw_y, k_marker_dark_value);
}

void draw_circle_anchor_points(uint8_t image[][RAW_W])
{
    draw_circle_anchor_point(image, &circle_B_point);
    draw_circle_anchor_point(image, &circle_C_point);
}

// 把 ATG 实际找到的左右种子（ipts0[0]/ipts1[0]，即追线起点）画成方框叠加到发送图上。
// 判断方法：方框应该正好落在左右赛道边线上；缺失或落在别处说明第一步起搜不正确。
void draw_atg_seeds(uint8_t image[][RAW_W])
{
    if(ipts0_num > 0)
    {
        mark_box(image, ipts0[0][0], ipts0[0][1], k_seed_box_value);
    }
    if(ipts1_num > 0)
    {
        mark_box(image, ipts1[0][0], ipts1[0][1], k_seed_box_value);
    }
}

// 把一条 IPM 浮点点列逐点经 inv_rot 反投回 raw 后叠加到发送图上（对应大佬 lcd_Show_inv_Line）。
void draw_atg_ipm_line(uint8_t image[][RAW_W], const float pts[][2], int num, uint8_t value)
{
    if(image == nullptr || pts == nullptr || num <= 0)
    {
        return;
    }

    for(int i = 0; i < num; ++i)
    {
        int x = 0;
        int y = 0;
        if(ipm_pt_to_raw_display(pts[i][0], pts[i][1], &x, &y))
        {
            image[y][x] = value;
        }
    }
}

// 环岛补线叠加：状态条件照抄大佬 Cpu0_Main.c 显示分支，旧帧补线被 circle_type gate 住不会误显。
// 暗线 = 拼接边线/几何延长线（补线原料），亮线 = 补线中心（环岛 IN/OUT 它就是 rpts 控制选线来源）。
void draw_atg_splicing(uint8_t image[][RAW_W])
{
    if(circle_type == CIRCLE_RIGHT_BEGIN && circle_ref_mode == CIRCLE_REF_IN_C)
    {
        if(far_Lpt1_found)
        {
            draw_atg_ipm_line(image, Splicing_leftline, Splicing_leftline_num, k_splice_edge_value);
            draw_atg_ipm_line(image, Splicing_leftline_center, Splicing_leftline_center_num, k_splice_center_value);
        }
    }
    else if(circle_type == CIRCLE_RIGHT_OUT)
    {
        if((Lpt0_found && far_rpts0s_num > 0) || rpts0s_num < 0.6F / sample_dist)
        {
            draw_atg_ipm_line(image, leftline, leftline_num, k_splice_edge_value);
            draw_atg_ipm_line(image, Splicing_leftline_center, Splicing_leftline_center_num, k_splice_center_value);
        }
    }
    else if(circle_type == CIRCLE_LEFT_BEGIN && circle_ref_mode == CIRCLE_REF_IN_C)
    {
        if(far_Lpt0_found)
        {
            draw_atg_ipm_line(image, Splicing_rightline, Splicing_rightline_num, k_splice_edge_value);
            draw_atg_ipm_line(image, Splicing_rightline_center, Splicing_rightline_center_num, k_splice_center_value);
        }
    }
    else if(circle_type == CIRCLE_LEFT_OUT)
    {
        if(Lpt1_found || rpts1s_num < 0.6F / sample_dist)
        {
            draw_atg_ipm_line(image, rightline, rightline_num, k_splice_edge_value);
            draw_atg_ipm_line(image, Splicing_rightline_center, Splicing_rightline_center_num, k_splice_center_value);
        }
    }
}

// 下半 IPM 俯视图：对每个 IPM 像素经 inv_rot 反向采样原图灰度，反算不到的像素填白。
// 只在发送分频命中的帧才执行，不增加每帧主循环开销。
void render_ipm_half(uint8_t image[][RAW_W], const uint8_t gray[RAW_H][RAW_W])
{
    for(int y = 0; y < IPM_H; ++y)
    {
        for(int x = 0; x < IPM_W; ++x)
        {
            int rx = 0;
            int ry = 0;
            image[RAW_H + y][x] =
                perspective_lookup_ipm_to_raw(x, y, &rx, &ry) ? gray[ry][rx] : k_ipm_blank_value;
        }
    }
}

// 把 IPM 域浮点点列按原生坐标画进下半图（y 偏移 RAW_H），出界点跳过。
void draw_ipm_pts(uint8_t image[][RAW_W], const float pts[][2], int num, uint8_t value)
{
    if(image == nullptr || pts == nullptr || num <= 0)
    {
        return;
    }

    for(int i = 0; i < num; ++i)
    {
        const int x = round_i(pts[i][0]);
        const int y = round_i(pts[i][1]);
        if(x >= 0 && x < IPM_W && y >= 0 && y < IPM_H)
        {
            image[RAW_H + y][x] = value;
        }
    }
}

// 组装并下发一帧上位机数据：左/中/右三条线 + 断点扫描线 + 灰度图 + 角点/种子叠加，全部直读 ATG 当前帧全局。
// 显示边界共用一个 dot_num（取 max 后 pad 补齐），不能用最短线长度，否则会裁短边线。
int config_points(const runtime_t *rt)
{
    if(rt == nullptr)
    {
        return 0;
    }

    int point_count[k_display_boundary_limit] = {};
    point_count[DISPLAY_CHANNEL_LEFT] =
        copy_atg_raw_pts(ipts0,
                         ipts0_num,
                         g_asst.display_x[DISPLAY_CHANNEL_LEFT],
                         g_asst.display_y[DISPLAY_CHANNEL_LEFT]);
    point_count[DISPLAY_CHANNEL_MID] =
        copy_atg_inv_pts(inv_rptsn,
                         rptsn_num,
                         g_asst.display_x[DISPLAY_CHANNEL_MID],
                         g_asst.display_y[DISPLAY_CHANNEL_MID]);
    point_count[DISPLAY_CHANNEL_RIGHT] =
        copy_atg_raw_pts(ipts1,
                         ipts1_num,
                         g_asst.display_x[DISPLAY_CHANNEL_RIGHT],
                         g_asst.display_y[DISPLAY_CHANNEL_RIGHT]);
    point_count[DISPLAY_CHANNEL_ENTRY_SCAN] =
        entry_scan_line_pts(g_asst.display_x[DISPLAY_CHANNEL_ENTRY_SCAN],
                            g_asst.display_y[DISPLAY_CHANNEL_ENTRY_SCAN]);
    point_count[DISPLAY_CHANNEL_IPM_LEFT] =
        copy_atg_ipm_pts(rpts0s,
                         rpts0s_num,
                         g_asst.display_x[DISPLAY_CHANNEL_IPM_LEFT],
                         g_asst.display_y[DISPLAY_CHANNEL_IPM_LEFT]);
    point_count[DISPLAY_CHANNEL_IPM_MID] =
        copy_atg_ipm_pts(rptsn,
                         rptsn_num,
                         g_asst.display_x[DISPLAY_CHANNEL_IPM_MID],
                         g_asst.display_y[DISPLAY_CHANNEL_IPM_MID]);
    point_count[DISPLAY_CHANNEL_IPM_RIGHT] =
        copy_atg_ipm_pts(rpts1s,
                         rpts1s_num,
                         g_asst.display_x[DISPLAY_CHANNEL_IPM_RIGHT],
                         g_asst.display_y[DISPLAY_CHANNEL_IPM_RIGHT]);
    point_count[DISPLAY_CHANNEL_LPT] =
        copy_marker_crosses(g_asst.display_x[DISPLAY_CHANNEL_LPT],
                            g_asst.display_y[DISPLAY_CHANNEL_LPT]);

    // 通道数每帧固定：空通道发一个右下角哨兵点，避免上位机因边界数量跳变而闪屏。
    // 这是显示协议占位，不是算法数据；线丢失时该通道整条收缩到角落一个点，诊断语义保留。
    for(int channel = 0; channel < k_display_boundary_limit; ++channel)
    {
        if(point_count[channel] <= 0)
        {
            int n = 0;
            append_display_pt(g_asst.display_x[channel],
                              g_asst.display_y[channel],
                              &n,
                              RAW_W - 1,
                              k_send_image_h - 1);
            point_count[channel] = n;
        }
    }

    display_boundary_t bd[k_display_boundary_limit] = {};
    int boundary_count = 0;
    int dot_num = 0;
    for(int channel = 0; channel < k_display_boundary_limit; ++channel)
    {
        add_display_boundary(bd, &boundary_count, &dot_num, channel, point_count[channel]);
    }

    std::memcpy(g_asst.image[0], rt->gray[0], RAW_W * RAW_H);
    render_ipm_half(g_asst.image, rt->gray);
    draw_entry_scan_line_on_image(g_asst.image);
    draw_atg_splicing(g_asst.image);
    draw_atg_seeds(g_asst.image);
    draw_atg_corner(g_asst.image, Lpt0_found ? 1 : 0, rpts0s, rpts0s_num, Lpt0_rpts0s_id);
    draw_atg_corner(g_asst.image, Lpt1_found ? 1 : 0, rpts1s, rpts1s_num, Lpt1_rpts1s_id);
    draw_circle_anchor_points(g_asst.image);
    draw_ipm_pts(g_asst.image, rpts0s, rpts0s_num, k_ipm_left_value);
    draw_ipm_pts(g_asst.image, rpts1s, rpts1s_num, k_ipm_right_value);
    draw_ipm_pts(g_asst.image, rptsn, rptsn_num, k_ipm_mid_value);
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
    g_asst.connect_ms = 0;
    std::memset(g_asst.display_x, 0, sizeof(g_asst.display_x));
    std::memset(g_asst.display_y, 0, sizeof(g_asst.display_y));
    std::memset(g_asst.image, 0, sizeof(g_asst.image));
    g_asst.enabled = assistant_enabled();
    g_asst.div = read_env_int_clamped("SMARTCAR_ASSISTANT_DIV", k_default_div, 1, 10000);
    g_asst.reconnect_div = read_env_int_clamped("SMARTCAR_ASSISTANT_RECONNECT_DIV", k_default_reconnect_div, 1, 10000);
    g_asst.ip = read_env_text("SMARTCAR_ASSISTANT_IP", k_default_ip);
    g_asst.port = read_env_int_clamped("SMARTCAR_ASSISTANT_PORT", k_default_port, 1, 65535);
    g_asst.connect_ms = read_env_int_clamped("SMARTCAR_ASSISTANT_CONNECT_MS", k_default_connect_ms, 1, 5000);
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
//  @param      rt        当前帧运行时快照；这里只取 rt->gray 当底图，线和角点直读 ATG 全局
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
