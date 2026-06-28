/* =====================================================================
 *  图像处理主框架（shy_Image）
 *
 *  核心处理流程（image_handle）：
 *    1. 种子点搜索：从固定位置向左右找边线起点（自适应阈值暗行检测）
 *    2. 沿线追踪：左/右手法则追踪边线（findline_lefthand/righthand_adaptive）
 *    3. 透视变换：原图坐标 → 俯视角坐标（rot_img_process）
 *    4. 边线滤波：三角核平滑（blur_points）
 *    5. 等距采样：重采样为等间距点（resample_points）
 *    6. 角度计算：局部转角 + NMS 提取角点（local_angle_points + nms_angle）
 *    7. 中线跟踪：左右边线偏移半赛宽生成中心线（track_leftline/rightline）
 *
 *  角点检测（find_corners）：
 *    在等距采样后的边线上找 Y 角点（Y 路）和 L 角点（十字/圆环）
 *    角点置信度 = |当前角度| - (|前角度|+|后角度|)/2
 * ===================================================================== */
#include "shy_Image.h"
#include "headfile.h"
#include <math.h>
#include <stdlib.h>

#define PI               3.14159265358979f
/* ================= IPM 变换矩阵 =================
 * rot：原图 → 俯视角（透视变换矩阵）
 * inv_rot：俯视角 → 原图（逆透视变换矩阵）
 * 由 tools/ipm_generator 离线标定生成 */
float rot[3][3]={
        //透视变换矩阵，由 tools/ipm_generator 生成
        {1.62544442e+01f, 8.05372315e-02f, -2.69678643e+02f},
        {8.74958852e+00f, 5.31380219e+00f, -2.95622645e+02f},
        {1.08501770e-01f, 3.36679900e-04f, 1.00000000e+00f}
};
float inv_rot[3][3]={
        //逆透视变换矩阵，由 tools/ipm_generator 生成
        {6.31894948e-02f, -1.99995498e-03f, 1.64496253e+01f},
        {-4.76549676e-01f, 5.31294421e-01f, 2.85473918e+01f},
        {-6.69572736e-03f, 3.81225039e-05f, 1.00000000e+00f}
};
/* ================= 全局状态 ================= */
int16 delta_y = 0;
int16 delta_x = 0;
float conf1, conf2, conf1_max, conf2_max;           /* 当前边线最大角点置信度，用于调试阈值 */

/* 种子点搜索结果 */
int atg_seed0_found, atg_seed1_found;
int atg_seed0_x = -1, atg_seed0_y = -1, atg_seed1_x = -1, atg_seed1_y = -1;

/* 角点检测结果（用于调试和日志） */
int atg_lpt0_best_i = -1, atg_lpt1_best_i = -1;
int atg_lpt0_best_im1 = -1, atg_lpt0_best_ip1 = -1;
int atg_lpt1_best_im1 = -1, atg_lpt1_best_ip1 = -1;
int atg_lpt0_pass_nms, atg_lpt0_pass_low, atg_lpt0_pass_high, atg_lpt0_pass_near, atg_lpt0_pass_dir;
int atg_lpt1_pass_nms, atg_lpt1_pass_low, atg_lpt1_pass_high, atg_lpt1_pass_near, atg_lpt1_pass_dir;
int atg_lpt0_accept_i = -1, atg_lpt1_accept_i = -1;
float atg_lpt0_best_conf, atg_lpt1_best_conf;
float atg_lpt0_best_x, atg_lpt0_best_y, atg_lpt1_best_x, atg_lpt1_best_y;
float atg_lpt0_best_inv_x, atg_lpt0_best_inv_y, atg_lpt1_best_inv_x, atg_lpt1_best_inv_y;

/* ================= 种子点搜索 ================= */

/* 暗行检测：从 (x,y) 沿 dir 方向检查 run 个像素是否都低于局部自适应阈值。
 * 用于种子点搜索：连续 run 个暗像素说明找到了赛道边界。
 * 返回 1 表示找到暗行，0 表示未找到。 */
static int seed_dark_run_found(image_t *img, int x, int y, int dir, int run, int block, int clip_val)
{
    int dark_num = 0;
    const int half = block / 2;
    for(int i = 1; i <= run; i++)
    {
        const int sx = x + dir * i;
        int local_thres = 0;
        for(int dy = -half; dy <= half; dy++)
        {
            for(int dx = -half; dx <= half; dx++)
            {
                local_thres += AT_IMAGE(img, sx + dx, y + dy);
            }
        }
        local_thres /= block * block;
        local_thres -= clip_val;
        if(AT_IMAGE(img, sx, y) < local_thres)
        {
            dark_num++;
        }
    }
    return dark_num >= run;
}

/* 透视变换：把原图边线 ipts0/ipts1 转换为俯视角边线 rpts0/rpts1。
 * 变换公式：rot_x = (a11*x + a12*y + a13) / (a31*x + a32*y + a33) */
void rot_img_process(void)
{
    for(int i=0;i<ipts0_num;i++)
    {
        rpts0[i][0] = (rot[1][0]*ipts0[i][1]+rot[1][1]*ipts0[i][0]+rot[1][2])/(rot[2][0]*ipts0[i][1]+rot[2][1]*ipts0[i][0]+rot[2][2])+delta_x;
        rpts0[i][1] = (rot[0][0]*ipts0[i][1]+rot[0][1]*ipts0[i][0]+rot[0][2])/(rot[2][0]*ipts0[i][1]+rot[2][1]*ipts0[i][0]+rot[2][2])+delta_y;
    }
    for(int i=0;i<ipts1_num;i++)
    {
        rpts1[i][0] = (rot[1][0]*ipts1[i][1]+rot[1][1]*ipts1[i][0]+rot[1][2])/(rot[2][0]*ipts1[i][1]+rot[2][1]*ipts1[i][0]+rot[2][2])+delta_x;
        rpts1[i][1] = (rot[0][0]*ipts1[i][1]+rot[0][1]*ipts1[i][0]+rot[0][2])/(rot[2][0]*ipts1[i][1]+rot[2][1]*ipts1[i][0]+rot[2][2])+delta_y;
    }
    rpts0_num = ipts0_num;
    rpts1_num = ipts1_num;

}
/* ================= 图像处理主入口 =================
 *
 * image_handle() 是每帧图像处理的主入口，完整流程：
 *   1. 种子点搜索：从固定位置向左右找边线起点
 *   2. 沿线追踪：左/右手法则追踪边线
 *   3. 透视变换：原图 → 俯视角
 *   4. 边线滤波：三角核平滑
 *   5. 等距采样：重采样为等间距点
 *   6. 角度计算：局部转角 + NMS 提取角点
 *   7. 中线跟踪：左右边线偏移半赛宽生成中心线
 *
 * 种子点搜索策略：
 *   从固定位置（begin_x, begin_y）向左右找边线起点。
 *   横坐标每移动一次，计算当前点的自适应阈值，并检查连续 seed_dark_run 个暗像素。
 *   这种方法类似阳光算法，不需要手动调整阈值。
 */
void image_handle(void)
{
    /*
    for(;y1>0;y1--){
        for(x1= img_raw.width / 2 - begin_x;x1>3;x1--){
            if (AT_IMAGE(&img_raw, x1 - 1, y1) < OSTU_thres){
                x1_flag = 1;
            }
        }
    }
    if(x1_flag==1) break;
     */
    const int seed_dark_run = 2;
    const int seed_y_top = 85;
    const int seed_y_min = block_size / 2;
    const int seed_y_max = img_raw.height - block_size / 2 - 1;
    const int seed_y_stop = seed_y_top > seed_y_min ? seed_y_top : seed_y_min;
    const int left_min_x = block_size / 2 + seed_dark_run;
    const int right_max_x = img_raw.width - block_size / 2 - seed_dark_run - 1;
    atg_seed0_found = atg_seed1_found = 0;
    atg_seed0_x = atg_seed0_y = atg_seed1_x = atg_seed1_y = -1;
    int x1= img_raw.width / 2 - begin_x, y1 = begin_y;
    ipts0_num = sizeof(ipts0) / sizeof(ipts0[0]);
    int left_seed_found = 0;
    for(y1 = clip(begin_y, seed_y_min, seed_y_max); y1 >= seed_y_stop && !left_seed_found; y1--)
    {
        // 从图像中线左侧 begin_x 处开始向左找左边线起点。
        for(x1 = img_raw.width / 2 - begin_x; x1 >= left_min_x; x1--)
        {
            if(seed_dark_run_found(&img_raw, x1, y1, -1, seed_dark_run, block_size, clip_value))
            {
                atg_seed0_found = 1;
                atg_seed0_x = x1;
                atg_seed0_y = y1;
                left_seed_found = 1;
                break;
            }
        }
    }
    if (left_seed_found){
        findline_lefthand_adaptive(&img_raw, block_size, clip_value, x1, y1, ipts0, &ipts0_num);
    }
    else ipts0_num = 0;
    int x2 = img_raw.width / 2 + begin_x, y2 = begin_y;
    ipts1_num = sizeof(ipts1) / sizeof(ipts1[0]);
    int right_seed_found = 0;

    for(y2 = clip(begin_y, seed_y_min, seed_y_max); y2 >= seed_y_stop && !right_seed_found; y2--)
    {
        // 从图像中线右侧 begin_x 处开始向右找右边线起点。
        for(x2 = img_raw.width / 2 + begin_x; x2 <= right_max_x; x2++)
        {
            if(seed_dark_run_found(&img_raw, x2, y2, 1, seed_dark_run, block_size, clip_value))
            {
                atg_seed1_found = 1;
                atg_seed1_x = x2;
                atg_seed1_y = y2;
                right_seed_found = 1;
                break;
            }
        }
    }
    if (right_seed_found){
        findline_righthand_adaptive(&img_raw, block_size, clip_value, x2, y2, ipts1, &ipts1_num);
    }

    else ipts1_num = 0;

    // 透视变换
    rot_img_process();

    // 边线滤波
    blur_points(rpts0, rpts0_num, rpts0b, (int) round(line_blur_kernel));
    rpts0b_num = rpts0_num;
    blur_points(rpts1, rpts1_num, rpts1b, (int) round(line_blur_kernel));
    rpts1b_num = rpts1_num;


    // 边线等距采样
    rpts0s_num = sizeof(rpts0s) / sizeof(rpts0s[0]);
    resample_points(rpts0b, rpts0b_num, rpts0s, &rpts0s_num, sample_dist * pixel_per_meter);
    rpts1s_num = sizeof(rpts1s) / sizeof(rpts1s[0]);
    resample_points(rpts1b, rpts1b_num, rpts1s, &rpts1s_num, sample_dist * pixel_per_meter);
    // 边线局部角度变化率，采用我们的算法可以得到稳定且等距的边线前提下，直接取每个点前后20cm构成一个三点，
         //利用向量的角度计算公式算实际角度即可。为方便判断，
    local_angle_points(rpts0s, rpts0s_num, rpts0a, (int) round(angle_dist / sample_dist));
    rpts0a_num = rpts0s_num;
    local_angle_points(rpts1s, rpts1s_num, rpts1a, (int) round(angle_dist / sample_dist));//angle_dist / sample_dist
    rpts1a_num = rpts1s_num;
    // 角度变化率非极大抑制
        //我们又进行了角度的非极大抑制，保证只留下角度最大的点，即角点。这样算出来的角度很稳定，跟实际也很接近。（前提是透视变换做的正确）
    nms_angle(rpts0a, rpts0a_num, rpts0an, (int) round(angle_dist / sample_dist) * 2 + 1);//angle_dist / sample_dist
    rpts0an_num = rpts0a_num;
    nms_angle(rpts1a, rpts1a_num, rpts1an, (int) round(angle_dist / sample_dist) * 2 + 1);//angle_dist / sample_dist
    rpts1an_num = rpts1a_num;

    // 左右中线跟踪
    track_leftline(rpts0s, rpts0s_num, rptsc0, (int) round(10.0), pixel_per_meter * ROAD_WIDTH / 2);//
    rptsc0_num = rpts0s_num;
    track_rightline(rpts1s, rpts1s_num, rptsc1, (int) round(10.0), pixel_per_meter * ROAD_WIDTH / 2);//
    rptsc1_num = rpts1s_num;

}
/* ================= 角点检测 =================
 *
 * 在等距采样后的边线上找 Y 角点（Y 路）和 L 角点（十字/圆环）。
 *
 * 角点置信度计算：
 *   conf = |当前角度| - (|前角度| + |后角度|) / 2
 *   置信度越高，说明这个点越像真正的角点（角度突变）。
 *
 * Y 角点阈值：40°~66°，在 0.7m 以内
 * L 角点阈值：60°~140°（一般）或 50°~140°（回环阶段），在 60 点以内
 * 长直道判断：点数 > 1.0m 对应的点数
 *
 * Y 点二次检查：两个 Y 角点距离应在 0.45m 附近，且角点后张开。
 */
void find_corners(void) {
    /* 识别 Y、L 拐点 */
    Ypt0_found = Ypt1_found = Lpt0_found = Lpt1_found = false;
    is_straight0 = rpts0s_num > (1.0 / sample_dist);    /* 长直道判断：点数 > 1.0m 对应的点数 */
    is_straight1 = rpts1s_num > (1.0 / sample_dist);    /* 长直道判断 */
    conf1_max =conf2_max = 0;
    atg_lpt0_best_i = atg_lpt1_best_i = -1;
    atg_lpt0_best_im1 = atg_lpt0_best_ip1 = -1;
    atg_lpt1_best_im1 = atg_lpt1_best_ip1 = -1;
    atg_lpt0_pass_nms = atg_lpt0_pass_low = atg_lpt0_pass_high = atg_lpt0_pass_near = atg_lpt0_pass_dir = 0;
    atg_lpt1_pass_nms = atg_lpt1_pass_low = atg_lpt1_pass_high = atg_lpt1_pass_near = atg_lpt1_pass_dir = 0;
    atg_lpt0_accept_i = atg_lpt1_accept_i = -1;
    atg_lpt0_best_conf = atg_lpt1_best_conf = -1000.0f;
    atg_lpt0_best_x = atg_lpt0_best_y = atg_lpt1_best_x = atg_lpt1_best_y = -1.0f;
    atg_lpt0_best_inv_x = atg_lpt0_best_inv_y = atg_lpt1_best_inv_x = atg_lpt1_best_inv_y = -1.0f;
    for (int i = 0; i < MIN(rpts0s_num,80); i++) {
        if (rpts0an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, rpts0s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, rpts0s_num - 1);
        conf1 = 0;
        conf1  = fabs(rpts0a[i]) - (fabs(rpts0a[im1]) + fabs(rpts0a[ip1])) / 2;
        if (atg_lpt0_best_i < 0 || conf1 > atg_lpt0_best_conf) {
            atg_lpt0_best_i = i;
            atg_lpt0_best_im1 = im1;
            atg_lpt0_best_ip1 = ip1;
            atg_lpt0_best_conf = conf1;
            atg_lpt0_best_x = rpts0s[i][0];
            atg_lpt0_best_y = rpts0s[i][1];
            atg_lpt0_best_inv_x = Cal_inv_rot_x(rpts0s[i][0], rpts0s[i][1]);
            atg_lpt0_best_inv_y = Cal_inv_rot_y(rpts0s[i][0], rpts0s[i][1]);
            atg_lpt0_pass_nms = 1;
            atg_lpt0_pass_low = conf1 > (round_type ? 50.0f : 60.0f) / 180.0f * PI;
            atg_lpt0_pass_high = conf1 < 140.0f / 180.0f * PI;
            atg_lpt0_pass_near = i < 60;
            atg_lpt0_pass_dir = rpts0s[im1][0] > rpts0s[ip1][0] && rpts0s[im1][1] > rpts0s[ip1][1];
        }
        /* Y 角点阈值：40°~66°，在 0.7m 以内 */
        if (Ypt0_found == false && 40. / 180. * PI < conf1 && conf1 < 66. / 180. * PI && i < 0.7 / sample_dist) {
            Ypt0_rpts0s_id = i;
            Ypt0_found = true;
        }
        /* L 角点阈值：60°~140°（一般）或 50°~140°（回环阶段），在 60 点以内。
         * 方向判断：前一点 x > 后一点 x 且 前一点 y > 后一点 y，确保角点方向正确。 */
        if(round_type){
            /* 回环阶段的单独阈值（更宽松） */
            if (Lpt0_found == false && 50. / 180. * PI < conf1 && conf1 < 140. / 180. * PI && i<60
                    &&(rpts0s[im1][0]>rpts0s[ip1][0]&&rpts0s[im1][1]>rpts0s[ip1][1])) {
                Lpt0_rpts0s_id = i;
                Lpt0_found = true;
                atg_lpt0_accept_i = i;
            }
        }
        else{
            /* 一般情况下的阈值 */
            if (Lpt0_found == false && 60. / 180. * PI < conf1 && conf1 < 140. / 180. * PI && i<60
                    &&(rpts0s[im1][0]>rpts0s[ip1][0]&&rpts0s[im1][1]>rpts0s[ip1][1]))
            {
                Lpt0_rpts0s_id = i;
                Lpt0_found = true;
                atg_lpt0_accept_i = i;
            }
        }


        /* 长直道判断：在 1.0m 以内出现 >20° 的角度变化 → 不是直道 */
        if (conf1 > 20. / 180. * PI && i < 1.0 / sample_dist) is_straight0 = false;
        if (Ypt0_found == true && Lpt0_found == true && is_straight0 == false) break;
        if(conf1>conf1_max)conf1_max = conf1;
    }


    for (int i = 0; i < MIN(rpts1s_num,80); i++) {
        if (rpts1an[i] == 0) continue;
        int im1 = clip(i - (int) round(angle_dist / sample_dist), 0, rpts1s_num - 1);
        int ip1 = clip(i + (int) round(angle_dist / sample_dist), 0, rpts1s_num - 1);
        conf2 =0;
        conf2 = fabs(rpts1a[i]) - (fabs(rpts1a[im1]) + fabs(rpts1a[ip1])) / 2;
        if (atg_lpt1_best_i < 0 || conf2 > atg_lpt1_best_conf) {
            atg_lpt1_best_i = i;
            atg_lpt1_best_im1 = im1;
            atg_lpt1_best_ip1 = ip1;
            atg_lpt1_best_conf = conf2;
            atg_lpt1_best_x = rpts1s[i][0];
            atg_lpt1_best_y = rpts1s[i][1];
            atg_lpt1_best_inv_x = Cal_inv_rot_x(rpts1s[i][0], rpts1s[i][1]);
            atg_lpt1_best_inv_y = Cal_inv_rot_y(rpts1s[i][0], rpts1s[i][1]);
            atg_lpt1_pass_nms = 1;
            atg_lpt1_pass_low = conf2 > (round_type ? 50.0f : 60.0f) / 180.0f * PI;
            atg_lpt1_pass_high = conf2 < 140.0f / 180.0f * PI;
            atg_lpt1_pass_near = i < 60;
            atg_lpt1_pass_dir = 1;
        }
        if (Ypt1_found == false && 40. / 180. * PI < conf2 && conf2 < 66. / 180. * PI && i < 0.7 / sample_dist) {
            Ypt1_rpts1s_id = i;
            Ypt1_found = true;
        }
        if(round_type){
            if (Lpt1_found == false && 50. / 180. * PI < conf2 && conf2 < 140. / 180. * PI&& i < 60 ) {
                Lpt1_rpts1s_id = i;
                Lpt1_found = true;
                atg_lpt1_accept_i = i;
            }
        }
        else{
            if (Lpt1_found == false && 60. / 180. * PI < conf2 && conf2 < 140. / 180. * PI&& i < 60 ) {
                Lpt1_rpts1s_id = i;
                Lpt1_found = true;
                atg_lpt1_accept_i = i;
            }
        }
        if (conf2 > 20. / 180. * PI && i < 1.0 / sample_dist) is_straight1 = false;
        if (Ypt1_found == true && Lpt1_found == true && is_straight1 == false) break;
        if(conf2>conf2_max)conf2_max = conf2;
    }

    /* Y 点二次检查：依据两角点距离及角点后张开特性。
     * 两个 Y 角点距离应在 0.45m 附近，且角点后 50 点处应张开（>0.7m）。
     * 对于视野受限的情况，可能无法同时看到两个拐点，二次检查会失败。 */
    if (Ypt0_found && Ypt1_found) {
        float dx = rpts0s[Ypt0_rpts0s_id][0] - rpts1s[Ypt1_rpts1s_id][0];
        float dy = rpts0s[Ypt0_rpts0s_id][1] - rpts1s[Ypt1_rpts1s_id][1];
        float dn = sqrtf(dx * dx + dy * dy);
        if (fabs(dn - 0.45 * pixel_per_meter) < 0.15 * pixel_per_meter) {
            float dwx = rpts0s[clip(Ypt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] -
                        rpts1s[clip(Ypt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0];
            float dwy = rpts0s[clip(Ypt0_rpts0s_id + 50, 0, rpts0s_num - 1)][1] -
                        rpts1s[clip(Ypt1_rpts1s_id + 50, 0, rpts1s_num - 1)][1];
            float dwn = sqrtf(dwx * dwx + dwy * dwy);
            if (!(dwn > 0.7 * pixel_per_meter &&
                  rpts0s[clip(Ypt0_rpts0s_id + 50, 0, rpts0s_num - 1)][0] < rpts0s[Ypt0_rpts0s_id][0] &&
                  rpts1s[clip(Ypt1_rpts1s_id + 50, 0, rpts1s_num - 1)][0] > rpts1s[Ypt1_rpts1s_id][0])) {
                Ypt0_found = Ypt1_found = false;
            }
        } else {
            Ypt0_found = Ypt1_found = false;
        }
    }
    if(Ypt0_found&&!Ypt1_found&&rpts1s_num>30)Ypt0_found = false;
    if(Ypt1_found&&!Ypt0_found&&rpts0s_num>30)Ypt1_found = false;


}
/* ================= 坐标变换 ================= */

/* 透视变换横坐标：原图 (x,y) → 俯视角 x */
float Cal_rot_x(float x,float y){
    float rot_x;
    rot_x = (rot[1][0]*y+rot[1][1]*x+rot[1][2])/(rot[2][0]*y+rot[2][1]*x+rot[2][2]);
    return rot_x;
}
/* 透视变换纵坐标：原图 (x,y) → 俯视角 y */
float Cal_rot_y(float x,float y){
    float rot_y;
    rot_y = (rot[0][0]*y+rot[0][1]*x+rot[0][2])/(rot[2][0]*y+rot[2][1]*x+rot[2][2]);
    return rot_y;
}
/* 逆透视变换横坐标：俯视角 (x,y) → 原图 x */
float Cal_inv_rot_x(float x,float y){
    float inv_rot_x;
    inv_rot_x = (inv_rot[1][0]*y + inv_rot[1][1]*x + inv_rot[1][2])/(inv_rot[2][0]*y+inv_rot[2][1]*x+1);
    return inv_rot_x;


}
/* 逆透视变换纵坐标：俯视角 (x,y) → 原图 y */
float Cal_inv_rot_y(float x,float y){
    float inv_rot_y;
    inv_rot_y = (inv_rot[0][0]*y + inv_rot[0][1]*x + inv_rot[0][2])/(inv_rot[2][0]*y+inv_rot[2][1]*x+1);
    return inv_rot_y;
}
