/* =====================================================================
 *  视觉主链图像基础函数（imgproc）
 *
 *  当前只保留沿线追踪和点列处理 primitive。
 * ===================================================================== */
#include "imgproc.h"
#include <math.h>

#define AT                  AT_IMAGE
/* ================= 沿线追踪 ================= */

/* 方向向量表：dir=0/1/2/3 分别对应 上/右/下/左
 * dir_front：正前方（主方向）
 * dir_frontleft：左前方（左手追踪用）
 * dir_frontright：右前方（右手追踪用） */
static const int dir_front[4][2] = {{0,  -1},
                                    {1,  0},
                                    {0,  1},
                                    {-1, 0}};
static const int dir_frontleft[4][2] = {{-1, -1},
                                        {1,  -1},
                                        {1,  1},
                                        {-1, 1}};
static const int dir_frontright[4][2] = {{1,  -1},
                                         {1,  1},
                                         {-1, 1},
                                         {-1, -1}};


/* 左手法则沿边线追踪：从 (x,y) 出发，沿黑色边界左侧前进。
 * 算法：每步计算局部自适应阈值，判断前方和左前方是否为黑线；
 *   - 前方黑 → 右转（dir+1）
 *   - 左前方黑 → 直走
 *   - 都不黑 → 左前方走并左转（dir-1）
 * 连续右转 6 次认为追踪结束（遇到死角或回环）。 */
void findline_lefthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num) {
    int half = block_size / 2;
    int step = 0, dir = 0, turn = 0;
    while (step < *num && half < x && x < img->width - half - 1 &&
           half < y && y < img->height - half - 1 && turn < 6) {
        int local_thres = 0;
        for (int dy = -half; dy <= half; dy++) {
            for (int dx = -half; dx <= half; dx++) {
                local_thres += AT(img, x + dx, y + dy);
            }
        }
        local_thres /= block_size * block_size;
        local_thres -= clip_value;

        int front_value = AT(img, x + dir_front[dir][0], y + dir_front[dir][1]);
        int frontleft_value = AT(img, x + dir_frontleft[dir][0], y + dir_frontleft[dir][1]);
        if (front_value < local_thres) {
            dir = (dir + 1) % 4;
            turn++;
        } else if (frontleft_value < local_thres) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        } else {
            x += dir_frontleft[dir][0];
            y += dir_frontleft[dir][1];
            dir = (dir + 3) % 4;
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        }
    }
    *num = step;
}


/* 右手法则沿边线追踪：与左手对称，沿黑色边界右侧前进。 */
void findline_righthand_adaptive(image_t *img, int block_size, int clip_value, int x, int y, int pts[][2], int *num) {
    int half = block_size / 2;
    int step = 0, dir = 0, turn = 0;
    while (step < *num && half < x && x < img->width - half - 1 &&
           half < y && y < img->height - half - 1 && turn < 6) {
        int local_thres = 0;
        for (int dy = -half; dy <= half; dy++) {
            for (int dx = -half; dx <= half; dx++) {
                local_thres += AT(img, x + dx, y + dy);
            }
        }
        local_thres /= block_size * block_size;
        local_thres -= clip_value;

        int front_value = AT(img, x + dir_front[dir][0], y + dir_front[dir][1]);
        int frontright_value = AT(img, x + dir_frontright[dir][0], y + dir_frontright[dir][1]);
        if (front_value < local_thres) {
            dir = (dir + 3) % 4;
            turn++;
        } else if (frontright_value < local_thres) {
            x += dir_front[dir][0];
            y += dir_front[dir][1];
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        } else {
            x += dir_frontright[dir][0];
            y += dir_frontright[dir][1];
            dir = (dir + 1) % 4;
            pts[step][0] = x;
            pts[step][1] = y;
            step++;
            turn = 0;
        }
    }

    *num = step;
}


/* ================= 点集处理 ================= */

/* 点集平滑：三角核加权平均，kernel 控制平滑窗口大小。
 * 边界点用 clip 钳位索引，避免越界。 */
void blur_points(float pts_in[][2], int num, float pts_out[][2], int kernel){
    int half = kernel / 2;
    for (int i = 0; i < num; i++) {
        pts_out[i][0] = pts_out[i][1] = 0;
        for (int j = -half; j <= half; j++) {
            pts_out[i][0] += pts_in[clip(i + j, 0, num - 1)][0] * (half + 1 - fabs(j));
            pts_out[i][1] += pts_in[clip(i + j, 0, num - 1)][1] * (half + 1 - fabs(j));
        }
        /* 归一化：三角核权重和 = (2*half+2)*(half+1)/2 */
        pts_out[i][0] /= (2 * half + 2) * (half + 1) / 2;
        pts_out[i][1] /= (2 * half + 2) * (half + 1) / 2;
    }
}


/* 点集等间距重采样：沿折线按 dist 间距插入新点。
 * 用于把不均匀的边线点转为等间距采样，方便后续计算角度和偏移。
 * 算法：逐段遍历，用线性插值在当前段内按 dist 间距生成新点。 */
void resample_points(float pts_in[][2], int num1, float pts_out[][2], int *num2, float dist){
    if (num1 <= 0 || pts_in == 0 || pts_out == 0 || num2 == 0 || *num2 <= 0) {
        if (num2 != 0) {
            *num2 = 0;
        }
        return;
    }
    pts_out[0][0] = pts_in[0][0];
    pts_out[0][1] = pts_in[0][1];
    int len = 1;
    for (int i = 0; i < num1 - 1 && len < *num2; i++) {
        float x0 = pts_in[i][0];
        float y0 = pts_in[i][1];
        float x1 = pts_in[i + 1][0];
        float y1 = pts_in[i + 1][1];

        do {
            float x = pts_out[len - 1][0];
            float y = pts_out[len - 1][1];

            float dx0 = x0 - x;
            float dy0 = y0 - y;
            float dx1 = x1 - x;
            float dy1 = y1 - y;

            float dist0 = sqrt(dx0 * dx0 + dy0 * dy0);
            float dist1 = sqrt(dx1 * dx1 + dy1 * dy1);

            float r0 = (dist1 - dist) / (dist1 - dist0);
            float r1 = 1 - r0;

            if (r0 < 0 || r1 < 0) break;
            x0 = x0 * r0 + x1 * r1;
            y0 = y0 * r0 + y1 * r1;
            pts_out[len][0] = x0;
            pts_out[len][1] = y0;
            len++;
        } while (len < *num2);

    }
    *num2 = len;
}

/* 计算点集上每点的局部转角：用前后 dist 个点的方向差算出转角。
 * angle_out[i] = atan2(cross, dot)，正值左转，负值右转。 */
void local_angle_points(float pts_in[][2], int num, float angle_out[], int dist){
    for (int i = 0; i < num; i++) {
        if (i <= 0 || i >= num - 1) {
            angle_out[i] = 0;
            continue;
        }
        float dx1 = pts_in[i][0] - pts_in[clip(i - dist, 0, num - 1)][0];
        float dy1 = pts_in[i][1] - pts_in[clip(i - dist, 0, num - 1)][1];
        float dn1 = sqrtf(dx1 * dx1 + dy1 * dy1);
        float dx2 = pts_in[clip(i + dist, 0, num - 1)][0] - pts_in[i][0];
        float dy2 = pts_in[clip(i + dist, 0, num - 1)][1] - pts_in[i][1];
        float dn2 = sqrtf(dx2 * dx2 + dy2 * dy2);
        float c1 = dx1 / dn1;
        float s1 = dy1 / dn1;
        float c2 = dx2 / dn2;
        float s2 = dy2 / dn2;
        angle_out[i] = atan2f(c1 * s2 - c2 * s1, c2 * c1 + s2 * s1);
    }
}


/* 角度非极大值抑制（NMS）：在 kernel 窗口内，只保留绝对值最大的角度，
 * 其他置零。用于提取尖锐的角点（如十字 L 角点、圆环入口角点）。 */
void nms_angle(float angle_in[], int num, float angle_out[], int kernel){
    int half = kernel / 2;
    for (int i = 0; i < num; i++) {
        angle_out[i] = angle_in[i];
        for (int j = -half; j <= half; j++) {
            if (fabs(angle_in[clip(i + j, 0, num - 1)]) > fabs(angle_out[i])) {
                angle_out[i] = 0;
                break;
            }
        }
    }
}

/* ================= 线偏移 ================= */

/* 左线偏移：把边线向左偏移 dist 距离，生成中心线。
 * 用 approx_num 个点的平均方向计算法向量，避免单点噪声。
 * track_rightline 是镜像版本，向右偏移。 */
void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist) {
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] - dy * dist;
        pts_out[i][1] = pts_in[i][1] + dx * dist;


    }
}


/* 右线偏移：与左线偏移镜像，向右偏移 dist 距离 */
void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist){
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] + dy * dist;
        pts_out[i][1] = pts_in[i][1] - dx * dist;
    }
}
