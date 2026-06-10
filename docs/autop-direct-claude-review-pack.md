# autop-direct 分支审查索引

日期：2026-06-10

这个文件是给昂贵模型先读的入口。目标不是让它重新全仓考古，而是让它只检查最可能出错的接线点。

## 任务目标

当前分支目标：

```text
直接使用 SJTU-AuTop RT1064 参考版的图像/元素算法，
保留本车现有硬件和控制闭环：
电机、编码器、GPIO、UVC、差速控制、上位机报告。
```

不做的事：

```text
不继续修旧 tracking 算法。
不把 RT1064 舵机 pure_angle 控制链搬进差速车。
不靠隐藏 fallback、旧中线复用、补线接控制来掩盖几何失败。
```

## 分支和源码

目标 worktree：

```text
/mnt/e/longxin/LS2K0300_Library/LS2K300_Library/Seekfree_LS2K0300_Opensource_Library/test_project/front_car_mainline_autop_direct
```

目标分支：

```text
port/autop-direct-reference-control
```

参考版来源：

```text
GitHub: https://github.com/SJTU-AuTop/RT1064-Code.git
Local:  /mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code
Commit: 4038f81ad85f915adc988f3791887b1c823ae350
Log:    4038f81 Merge pull request #6 from Calvariaa/master
```

参考版必须对照的文件：

```text
Project/CODE/imgproc.c
Project/CODE/imgproc.h
Project/CODE/cross.c
Project/CODE/cross.h
Project/CODE/circle.c
Project/CODE/circle.h
Project/CODE/camera_param.c
Project/CODE/camera_param.h
Project/CODE/motor.h
```

## 当前改动边界

当前分支 `code/CMakeLists.txt` 已把主程序链接从旧 tracking `.cpp` 切到 `code/autop_ref/`：

```text
移除主链:
  tracking/imgproc.cpp
  tracking/boundary.cpp
  tracking/mainline.cpp
  tracking/zebra.cpp
  tracking/ring.cpp
  tracking/element.cpp
  tracking/cross.cpp

新增主链:
  autop_ref/autop_runtime.cpp
  autop_ref/report_helpers.cpp
  autop_ref/imgproc.c
  autop_ref/utils.c
  autop_ref/cross.c
  autop_ref/circle.c

仍保留:
  tracking/perspective.cpp
  tracking/ipm_table_generated.cpp
  core/control.cpp
  drivers/device.cpp
  drivers/drive_output.cpp
  drivers/imu_feedback.cpp
  app/runners.cpp
```

注意：`code/autop_ref/` 当前还是 untracked 目录。审查时不能只看 `git diff`，要直接读这些文件。

## 当前运行链路

实时链路应是：

```text
device_capture_gray(rt->gray)
-> tracking_process_frame(rt)          // code/autop_ref/autop_runtime.cpp
-> drive_output_read_feedback()
-> rt->encoder_total += avg(left/right encoder count)
-> solve_runtime_with_feedback()       // guide_error -> target_yaw -> yaw_cmd
-> drive_output_apply()
-> assistant_tick()/print_live()
```

控制链必须保持本车差速合同：

```text
rt->track.guide_error
-> code/core/control.cpp 视觉外环 PD
-> target_yaw
-> yaw-rate PI / yaw_cmd
-> 左右轮 duty
```

RT1064 的 `pure_angle -> servo_pid -> smotor1_control()` 是舵机链，不是本车差速控制链。不要把它作为“对齐参考版”的修改建议。

## autop_ref 适配层职责

`code/autop_ref/autop_runtime.cpp` 只应该做这些桥接：

```text
1. 把 rt->gray 接到参考版 img_raw。
2. 把当前 160x120 静态 IPM 表拷到参考版 mapx/mapy/invx/invy。
3. 把参考版固定远线列按 376 宽比例缩到 160 宽：86/280 -> 36/119。
4. 把参考版 rptsn 中线转换为 rt->track.mid 和 rt->track.guide_error。
5. 把参考版 cross_type/circle_type/track_type 映射回 runtime_t，用于上位机和控制状态。
```

必须保留的主分支硬件标定值：

```text
CONTROL_CENTER_X = 86
ROAD_HALF_WIDTH  = 26
LOOKAHEAD_DIST   = 35
```

当前适配层关键参数：

```text
point_sample_dist = 3.0F
sample_dist       = 0.03F
angle_dist        = 0.20F
begin_x           = 14.0F
begin_y           = 84.0F
pixel_per_meter   = ROAD_HALF_WIDTH * 2 / ROAD_WIDTH
```

审查重点：`point_sample_dist=3px` 是当前 160x120/IPM 点列重采样；`sample_dist=0.03m` 仍被参考版状态机用来表达 `0.2m/1.0m/0.4m` 这种阶段门。不要把二者混成一个单位。

## 旧主分支已有结论

这些不是背景噪声，是本次移植必须继承的结论。

必须先读：

```text
/mnt/e/.../front_car_mainline/docs/tracking-audit-notes.md
```

读它确认：

```text
主链: gray -> seed -> trace -> IPM -> blur -> resample -> offset -> element -> midline -> guide_error
RT1064 circle.c/cross.c 是 active reference
十字远线固定列 86/280 需要按 376->160 比例缩放
Calvariaa PR #6 的重采样、区域 OTSU、控制参考点查表问题已被主分支测试锁住
ring_opp 补线在旧主分支只是检测/诊断，不进控制
```

必须先读：

```text
/mnt/e/.../front_car_mainline/docs/阈值笔记_boundary_ring.md
```

读它确认：

```text
k_boundary_resample_dist = 3
ring 物理距离门来自 RT1064 circle.c:
  lost 7, have 34, in_lost 4, run_corner 14
k_in_encoder_step = 5800 * 314 / 200
ENCODER_PER_METER 必须是 5800，不是 1024
```

必须先读：

```text
/mnt/e/.../front_car_mainline/docs/IPM调用调研.md
```

读它确认：

```text
参考版十字远线是在 raw 点列上 trace 后逐点查 mapx/mapy。
当前项目使用静态表 g_raw_to_ipm_x/y 和 g_ipm_to_raw_x/y。
当前 160x120 表不等于参考版 376x240 K/D/H 全链路，只能继承查表调用语义。
```

必须先读：

```text
/mnt/e/.../front_car_mainline/docs/控制参数笔记.md
```

读它确认：

```text
控制参考点可以参考 RT1064 raw wheel point -> mapx/mapy -> IPM。
guide_error 形状接近 RT1064 error，不是 pure_angle。
本车是 guide_error -> target_yaw -> yaw_cmd -> 左右轮差速。
```

可作为旧问题索引：

```text
/mnt/e/.../front_car_mainline/docs/6-5用户修改.md
/mnt/e/.../front_car_mainline/docs/13_mainline_pipeline_map.md
/mnt/e/.../front_car_mainline/docs/流程图.md
/mnt/e/.../front_car_mainline/docs/reference/README.md
/mnt/e/.../front_car_mainline/docs/reference/unity_CD_old.cpp
/mnt/e/.../front_car_mainline/docs/aegis/plans/2026-05-31-control-direct-flow.md
```

## 主分支重要提交

审查时不要重复推翻这些结论，除非有当前分支证据：

```text
07bec91 fix bug：对齐参考版中线生成流程
103daa6 fix bug：对齐参考版中线起点和误差计算
6058590 fix(tracking): 对齐十字远线和环岛帧首控制合同
8f0967e feat(app): 扩展上位机 seed 搜索诊断显示
f8de6db fix(tracking): 清晰化搜线起点与搜索中心学习合同
d101ad7 fix(tracking): 延后普通帧搜索中心学习到中线几何成立后
d2ccaf0 fix(tracking): 延后搜索中心写回到IPM身份复核后
aafcea8 fix(tracking): 恢复RT1064环岛主链并归档Unity旧实现
```

## 已发现并处理的问题

1. `circle_type` 左右映射

参考版 `circle_type_e` 是左右交替：

```text
NONE,
LEFT_BEGIN, RIGHT_BEGIN,
LEFT_IN, RIGHT_IN,
LEFT_RUNNING, RIGHT_RUNNING,
LEFT_OUT, RIGHT_OUT,
LEFT_END, RIGHT_END
```

`autop_runtime.cpp::map_element_state()` 不能用连续范围判断左/右，否则右环 BEGIN/IN/RUN/OUT 会被当成左环。当前已加奇偶判断。

2. `circle_type_name[]` 顺序

参考版 `circle.c` 的字符串表把 RUNNING 和 IN 顺序写反。当前 `code/autop_ref/circle.c` 已按 enum 顺序修正，避免上位机/日志误导。

3. 编码器比例

`code/autop_ref/motor.h` 必须是：

```c
#define ENCODER_PER_METER 5800
```

这和参考版 `Project/CODE/motor.h` 以及旧主分支 ring 合同一致。

4. `imgproc.c` 基础防护

当前 `code/autop_ref/imgproc.c` 已给以下路径加了最小防护：

```text
resample_points(): 空指针、num<=0、dist<=0、零长度线段
local_angle_points(): dn1/dn2 为 0
track_leftline/rightline(): 切向长度为 0
```

这是为了避免当前 160x120/IPM 表出界或重复点导致 NaN 传播。需要审查这些防护是否改变了参考版状态机语义。

## 剩余高价值审查问题

只审这些，不要泛泛重构。

1. `autop_runtime.cpp::process_image()`

问题：它是参考版 `process_image()` 的 160x120 版本，直接查 `mapx/mapy` 后重采样。

要确认：

```text
begin_x=14 / begin_y=84 是否确实对应参考版 32/167 的 376x240 缩放。
trace seed 搜索方向和阈值 thres/block_size/clip_value 是否仍适合当前 UVC 灰度图。
mapx/mapy 出界或负值是否会污染 blur/resample。
```

2. `autop_runtime.cpp::find_corners()`

问题：它混合了参考版角点扫描和旧主分支 strict pair 复核。

要确认：

```text
i < 0.8/sample_dist、i < 1.0/sample_dist 在 point_sample_dist=3px 的点列上仍是预期点数。
id + 50 的 pair open 复核是否过远；旧主分支后来把类似 open step 收到 34。
l_pair_ok 报告语义是否会误导，因为 copy_l_diag 现在只写 Lpt0_found && Lpt1_found。
```

3. `autop_ref/cross.c`

当前相对参考版的实质改动只有两类：

```text
mapx/mapy 维度改成 MT9V03X_CSI_H/W。
远线 resample 从 sample_dist * pixel_per_meter 改成 point_sample_dist。
```

要确认：

```text
far_x1/far_x2 每帧被设成 36/119 后，仍落在当前相机视野内有效赛道区域。
angle_dist/sample_dist 得到的角度窗口与 3px 重采样点列匹配。
参考版没有远 L 复用；当前 direct 分支也不应该重新引入旧 L 长期复用。
```

4. `autop_ref/circle.c`

要确认：

```text
RUN 阶段 Lpt_found 先裁 rpts*s_num/rptsc*_num，再近 L 切 OUT。
IN 阶段仍主要靠 rpts*s_num < 0.1/sample_dist 或编码器里程切 RUN。
ENCODER_PER_METER=5800 的单位和 rt->encoder_total 累计单位一致。
```

5. `autop_runtime.cpp::build_selected_midline()`

要确认：

```text
普通/ring 走参考版 track_type 选 rptsc0/rptsc1。
CROSS_IN 走 far L 后重建单边外扩候选。
begin_id=0 后把 rpts[0] 改成控制参考点，是否等价于旧主分支 force_begin_id0=1。
guide_error_from_mid() 的 LOOKAHEAD_DIST=35 和 forward_bias=ROAD_HALF_WIDTH*8/9 是否继承旧主分支控制合同。
```

6. IPM 和控制参考点

要确认：

```text
init_camera_tables_once() 确实把 160x120 静态表放进参考版 mapx/mapy/invx/invy。
control_ref_point() 仍优先 raw (RAW_W/2, RAW_H*0.78) -> IPM。
fallback CONTROL_CENTER_X=86 只在查表失败时用。
has_matrix=1 在 direct 分支是否合理；它改变了 offline/analyze 对矩阵缺失的旧语义。
```

7. 上位机和报告

要确认：

```text
report_helpers.cpp 是否满足旧 tracking/imgproc.hpp 对外 helper 符号。
app/runners.cpp 打印的 ring_opp/candidate_crop/search 学习字段是否只是零值，还是会误导调车。
assistant_tick()/print_live 收到的 rt->ring/cross/mid/guide_error 是否来自 autop_ref 当前帧。
```

8. 控制和硬件保留

要确认：

```text
drivers/device.cpp 的 UVC 采集没有被替换。
drivers/drive_output.cpp 的 PWM/GPIO/编码器/IMU 反馈没有被替换。
core/control.cpp 仍消费 guide_error，不消费 pure_angle。
实时 loop 中 encoder_total 的累计方向和参考版 get_total_encoder() 期望一致。
```

## 建议 Claude 输出格式

只输出这四块：

```text
1. 阻塞级问题：会导致不能烧录、不能跑、右环/十字/控制链明显错误。
2. 高风险问题：能编译但实车大概率异常，给出文件和函数。
3. 建议 patch：只给最小 diff，不做重构。
4. 不需要改的点：说明为什么不是问题，避免重复争论。
```

不要输出：

```text
不要泛泛列全仓文件。
不要建议重写架构。
不要把 pure_angle 移植到差速控制。
不要建议把 ring_opp 直接接到控制中线。
不要忽略旧主分支文档和提交记录。
```

## 给 Claude 的短提示词

```text
你只审查 autop-direct 参考版直移分支，不要全仓漫游。

先读：
/mnt/e/longxin/LS2K0300_Library/LS2K300_Library/Seekfree_LS2K0300_Opensource_Library/test_project/front_car_mainline_autop_direct/docs/autop-direct-claude-review-pack.md

然后只按其中“剩余高价值审查问题”逐项检查。参考版源码是：
https://github.com/SJTU-AuTop/RT1064-Code.git
本地路径：
/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code
commit:
4038f81ad85f915adc988f3791887b1c823ae350

当前目标分支路径：
/mnt/e/longxin/LS2K0300_Library/LS2K300_Library/Seekfree_LS2K0300_Opensource_Library/test_project/front_car_mainline_autop_direct

目标：确认 code/autop_ref 直移 RT1064 图像/十字/环岛算法后，是否正确接上本车现有 UVC、IPM 表、编码器里程、guide_error 差速控制、上位机报告。

不要浪费上下文重新整理旧主分支历史；review pack 已经列出必须继承的旧结论和文档。不要建议把 RT1064 pure_angle 舵机链搬进当前差速控制。不要建议把 ring_opp 补边直接喂控制。

输出只要四块：
1. 阻塞级问题
2. 高风险问题
3. 最小 patch 建议
4. 明确不需要改的点

每个结论必须给文件和函数。没有证据就写“未确认”，不要猜。
```

## 本地验证命令

审查或 patch 后至少跑：

```bash
git diff --check
bash code/test.sh
bash code/test.sh --host
git status --short --branch
```

当前注意事项：

```text
code/autop_ref/ 是 untracked，验证前后都要看 git status。
host tests 多数仍是旧测试目标，只能证明构建/符号基本健康，不能证明实车环岛/十字行为正确。
实车可用必须看 replay/上位机/烧录后的 UVC+编码器+差速闭环。
```

本文件写入后当前验证结果：

```text
git diff --check      通过
bash code/test.sh     通过，front_car_mainline 可链接；autop_ref C 文件有 unused-variable warnings
bash code/test.sh --host 通过，11 个 host 测试 ok
git status --short:
  M code/CMakeLists.txt
  ?? code/autop_ref/
  ?? docs/autop-direct-claude-review-pack.md
```
