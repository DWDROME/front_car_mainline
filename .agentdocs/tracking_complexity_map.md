# tracking 清理地图

目标：继续减少 set-style 中间层、wrapper、report-only 状态、重复缓存和诊断-only 字段，但不删真实控车链路。

## 已收束

主链已经固定：

```text
find_frame_seeds
find_seeds
-> trace_edges / trace_single
-> build_boundary_from_trace
-> element_process
-> perspective_points / blur_points / resample_points
-> track_leftline / track_rightline
-> solve_runtime / solve_runtime_with_feedback
-> drive_output_apply
```

注意：`track_dualline()` 仍作为 `imgproc.cpp/hpp` 的显式工具函数保留，但当前普通主线不主动进入 `TRACK_TYPE_DUAL`；双边都够长时沿用上一帧单边。

已删除或折叠的主要复杂度：

```text
state_machine_enabled / FRONT_CAR_ELEMENTS / 强制元素 CLI
element_state_t / runtime_t::element / element_active_kind
element_hint_t / control_input_t wrapper
track confidence/source/cross_candidate/frame_valid/lookahead_row
trace valid/avg_thres/seed_gray/seed_threshold/stop_reason
runtime low_threshold/width_base/frame_has_matrix/gray_main
corner_map_t / corners_t / boundary_t::map[3] / far_anchor_original_index
seed source/confidence/reject_reason/valid 等解释字段
line_points raw/ipm/filtered/normalized/candidate 中间 set
count_side_midline / count_dual_midline / choose_midline_side 预统计分支
side/dual 中线隐藏 fallback 和元素指定单边后的另一侧回退
build_midline_from_edges 大包裹接口
imgproc prepare_border 中线预处理 wrapper
imgproc otsu_threshold_1d + values[] 区域中转
imgproc trace_point_visited/mark_trace_point_visited/same_point 小转手
imgproc row_black_run/left_edge_at/right_edge_at/traverse walk-area 小转手
trace_pair / trace_quality_ok / trace_has_min_step / trace_down 等单用 wrapper
imgproc trace_single 左右合并循环
imgproc build_side_midline 左右合并函数
imgproc row_edge_at/find_row_edge_near 左右合并扫描
imgproc dual_mid_point 回写式配对 helper
imgproc left_mid_point/right_mid_point/build_*_midline/midline_has_lookahead_impl 中线壳层
imgproc perspective_points_core/blur_points_core/resample_points_core 公开转手层
cross_entry_ready report-only 接口
ring candidate_kind/candidate_count 旧候选命名
zebra transition_row/transition_count 观测缓存
control_state_t report 型速度/比例中间量
旧 solve_control()/step() 控制支线
application.cpp/.hpp 单函数入口编译层
find_frame_seeds/update_frame_boundaries/commit_frame_midline frame wrapper
imgproc trace 方向表 kDirFront* 长名字
imgproc 中线 left_x/left_y/right_x/right_y 长名字
mainline 中线 left_points/right_points 长名字
control loop target_yaw/actual_yaw/left/right 局部长名
boundary 角点检测 used_window/edge_guard/original_index 长名字
cross 远线 trial_trace/trial_boundary/far_l_index 长名字
ring_boundaries_t 边界 wrapper
boundary/control/mainline/ring 中复杂三元和长调用表达式
boundary copy_points/project_trace_common/finish_projected_boundary 转手层
boundary local_thres/bright_num/angle_peak/save_corner/corner_win/corner_guard 单用 helper
boundary max_corner_angle 单用 helper
cross trace_dy/far_trace_ok/trim_boundary/trim_boundary_to_corner 单用 helper
cross corner_near/cross_judge 单用 helper
cross corner_pt/cross_pair_ok 单用 helper
mainline has_dual_seed_pair 单用 helper
mainline seed_in_image/clear_line_work 单用 helper
mainline fail_track/clear_track_result 单用 helper
mainline clear_frame/save_midline 单用 helper
ring write_boundary_from_points 单用 helper
ring copy_points 单用 helper
ring rebuild_boundary 单用 helper
docs 迁移期长文档
.diag 旧报告
```

当前 report 已压到主线必要字段；`element_active_kind` 不再保留，元素活跃信息直接看 `ring/cross/zebra` 源状态。

## 当前保留

```text
runtime_t           仍集中保存一帧状态，暂不整体拆
cross/ring/zebra    必要比赛状态树，不作为第一删除目标
seed_row/width      参与 seed_pair_accepted/IPM/cross，不能当纯 report-only 删除
imgproc 中线数组    x0/y0/x1/y1 是投影、滤波、重采样工作区
options.cpp         main/runners 共用 CLI/env/default 参数，暂不并入 main.cpp
```

## 下一刀

```text
mainline/cross/ring 内部重复模子继续收短名
boundary_is_straight 这类几何判定段继续收直
```

## 判断标准

一次清理必须同时满足：

```text
主入口仍一眼能看出顺序
同一事实出现位置更少
没有新增 manager/adapter/orchestrator
没有 hidden fallback / mock success / shadow pipeline
guide_error -> target_yaw -> duty -> drive output 链路不变
host 构建和基础 audit 通过
```

如果只是把代码挪到新文件、增加解释层、增加配置项，行数少了也不算变清楚。

## 文件覆盖

当前必须按代码文件逐个收敛，不再只覆盖 `mainline.cpp/imgproc.cpp`。覆盖范围按 `code/CMakeLists.txt` 的编译目标、本项目头文件、构建脚本和当前保留的 audit 工具计算：主程序 `.cpp`、`tools/key_supervisor.cpp`、`app/core/drivers/tracking/utils` 下公开 `.hpp`、`test.sh`/`scripts/*.sh`/`tools/*.sh`、`code/CMakeLists.txt` 和 `code/cross.cmake`。

```text
app/main.cpp            已收：入口保持分发，矩阵加载局部 ok、分析路径 p
app/options.cpp         已收：CLI/env 参数合同不动，只收 val/a
app/report.cpp          已收：报告字段合同不动，IPM 检查和 trace 别名收成 p0/p1/ok0/ok1/tr0/tr1；详细日志和离线报告已补十字远线观测字段 `not_have_line/far_found/num/l`，用于现场判断 CROSS_IN 是否真的跑到远线和 L 点
app/runners.cpp         已收：live 主循环不压缩，profile 计时收成 t0..t6、fb/prof
app/options.hpp         已收：声明参数名 options -> opt
app/report.hpp          已扫不改：接口已短，report_path 保持语义
app/runners.hpp         已收：分析路径参数 paths -> p
core/control.cpp        已收：控制环局部 yaw/rps/base/out 固定左右模子；wheel_output_t 和长参数堆叠已去掉
core/control.hpp        已收：声明参数 feedback/control -> fb/ctrl
drivers/device.cpp      已收：图像读入局部 img/g，错误信息不动
drivers/drive_output.cpp 已收：feedback/control 和编码器局部收成 fb/ctrl/cnt0/cnt1
drivers/imu_feedback.cpp 已收：读缓冲和采样统计收成 buf/num/min_v/max_v，三轴读数 x/y/z
drivers/motor_pulse.cpp 已收：脉冲参数和编码器局部收成 p0/p1/ms/cnt0/cnt1；当前不编进 front_car_mainline 主目标，只作为独立诊断源保留
drivers/device.hpp      已扫不改：接口参数 path/width/height/fps/gray 语义明确
drivers/drive_output.hpp 已收：声明参数 feedback/control -> fb/ctrl
drivers/imu_feedback.hpp 已收：声明参数 raw_to_rad_s/gy
drivers/motor_pulse.hpp 已收：声明参数 p0/p1/ms
tools/key_supervisor.cpp 已收：漏项补齐，command/state -> cmd/st
test.sh                 已收：包装入口 ROOT_DIR -> ROOT
scripts/test.sh         已收：包装入口 ROOT_DIR -> ROOT
code/test.sh            已收：构建变量 WORK_DIR/TARGET_NAME/BUILD_DIR 等收成 ROOT/TARGET/BUILD/OUT
scripts/straight_baseline_audit.sh 已收：包装入口 ROOT_DIR -> ROOT
scripts/ipm_geometry_audit.sh 已收：包装入口 ROOT_DIR -> ROOT
scripts/behavior_equivalence.sh 已退休：旧新双二进制对比入口删除执行体，固定 exit 2
tools/board_current_smoke.sh 已收：板端冒烟变量 ROOT/BUILD/OUT/REMOTE_IMG/REMOTE_RPT，旧 report-only grep 字段移除
tools/straight_baseline_audit.sh 已收：审计变量 ROOT/BUILD/OUT/img/rpt/log
tools/ipm_geometry_audit.sh 已收：审计变量 ROOT/BUILD/OUT/img/rpt/log/ipm
tools/control_center_sensitivity_audit.sh 已收：审计变量 ROOT/BUILD/OUT/img/x/rpt/log
tools/cross_farline_audit.sh 已扫不改：退休入口必须 exit 2，不改成成功旁路
tools/ring_track_type_audit.sh 已扫不改：退休入口必须 exit 2，不改成成功旁路
tools/start_viewer_gui.sh 已确认不存在：README 残留提及，不纳入当前文件覆盖
tools/start_viewer_tunnel_background.sh 已确认不存在：README 残留提及，不纳入当前文件覆盖
code/CMakeLists.txt     已扫不改：构建目标结构清楚，DIR_SRCS 保留显式列表
code/cross.cmake        已扫不改：交叉编译工具链设置是合同
tracking/mainline.cpp   已再收：十字是否在 IN 段现在直接看 `rt->cross.state == CROSS_STATE_IN`，普通帧直接吃 `track.left/right.original_pts`，十字 IN 直接吃 `rt->cross.left_pts/right_pts`，不再保留 `pick_pts()` 这层空壳；当前 `element_track_type()` 里的十字定侧也已退回 `cross.track_type`，不再让 `mainline` 在十字分支里重复推一次 far L / near lost。并且 `CROSS_IN` 当前也不再回到 `pick_track_type()` 这种通用选择器，拿不到 `cross.track_type` 就直接拒绝，不再偷偷落回 dual/普通单边长度规则；十字态中线求解也已单独抽成 `solve_cross_mid()`，直接按 `rt->cross.left_pts/right_pts + left_l/right_l` 这段 farline 单边结果调用 `track_leftline/track_rightline`，不再先搬到 `rpts0s/rpts1s`，也不再借道普通双边/单边求解分支。当前 `tracking_process_frame()` 后半段也已收成先判一次 `rt->cross.state`、再走十字段/普通段的顺序式结构，不再来回重复判断十字 IN 状态。参考点/预瞄误差内部名也已收成 ref/raw_pt/ipm_pt/best_i/best_d
tracking/mainline.cpp   已再收：十字段和普通态的选边已经彻底拆开；十字 IN 直接读 `cross.track_type`，ring 进行中时普通态也直接按 `ring.state` 定侧，不再经过 `ring_track_type() -> pick_track_type(hint)` 这层间接壳；普通巡线自己的长度规则只留在 `pick_track_type()` 里，`element_track_type()` 这层统一分发壳已删除
tracking/mainline.cpp   已再收：普通主线点列投影现在只看 `rt->has_matrix`，不再用 `seed_pair_accepted()` 卡住单边 IPM；单边识别时也会走 `perspective_points -> blur_points -> resample_points -> track_leftline/track_rightline`，更贴近参考版先 mapx/mapy 再单边外扩的语义
tracking/mainline.cpp   已再收：`CROSS_IN` 现在不会被普通 seed/trace 失败提前 return；近线 seed 或 trace 失败时只允许已处于 `CROSS_IN` 的帧继续执行 `cross_process()` 远线链，非十字态仍直接失败。这是参考版 `CROSS_IN -> cross_farline()` 语义，不是普通巡线 fallback
tracking/imgproc.cpp    已再收：trace 方向表 DX/DY，midline 直接吃 pts[][2]，region_otsu 现场统计直方图，不再抄 values[] 再调 otsu_threshold_1d；左右找边和 walk-area/threshold 判断并回现场，不再绕 row_black_run/left_edge_at/right_edge_at/trace_point_*；白/黑判定 helper 也已退掉，find_left_edge/find_right_edge 直接现场读阈值和像素值；局部阈值也只保留一个入口 `calc_th`，不再拆 local_threshold + public wrapper 双名字；单边/双边补中线直接写在 track_leftline/track_rightline/track_dualline，本地删掉 left_mid_point/right_mid_point/build_*_midline/midline_has_lookahead_impl；perspective_points/blur_points/resample_points 也已直写公开函数，不再绕 *_core
tracking/imgproc.cpp    已再收：`find_seeds()` 的单边 fallback 也已收回同一条搜索行，不再让左/右 seed 分别落在两条 row 上再拼出混合事实；这样更接近参考版 `begin_y` 单行起线的入口语义
tracking/imgproc.cpp    已再收：`find_seeds()` 现在直接按参考版 `begin_x / begin_y` 语义，从固定起线行和中心两侧固定偏移起搜；失败就失败，不再保留向上补搜这条第二入口，也不再在 `[START_HIGH..MINI_HIGH]` 间混扫多行
tracking/imgproc.cpp    已再收：`find_column_seed()` 现在也改成参考版 fixed-column 的明写模子：沿固定列先见白、后见黑，返回前一个白点作为起线点；ring 不再吃“黑边沿点”和“白起线点”混在一起的语义。原来的 `search_down` 假通用参数也已删除，只保留向上搜索这一条真实用法
tracking/imgproc.cpp    已再收：`trace_left/trace_right` 的主判断已改成参考式固定模子，只围绕 `front/side/turn` 三件事推进，不再保留 `w0/v0/w1/v1` 这类绕的布尔拼接
tracking/imgproc.cpp    已再收：`trace_left/trace_right` 现在也不再保留 visited / 回踩 / stuck 保护层；`trace_single()` 的空 `stuck` 参数和上游转手也已一起删除，主核直接按参考版迷宫巡线顺序推进
tracking/imgproc.cpp    已再收：`find_left_edge/find_right_edge` 不再叠“连续黑段确认”，而是直接按行内白->黑邻接过渡取边，更接近参考版沿 `begin_y` 找起线点的原始模子
tracking/boundary.cpp   已再收：build_boundary_from_trace 继续作为主边界入口保留，并且生成 now_pts 后同步填 work_pts，避免 boundary_is_straight 依赖 refresh_boundary_corners 的调用顺序；`build_front_from_trace/front_boundary_t` 已从公共接口和实现中删除，不再把“前向边界”暴露成 boundary 层的长期概念。角点主核已收成参考式固定模子：`build_ang()` 先做 `angle + nms`，`angle_conf()` 再算 `conf`，`scan_l_corner()` 只在前段找第一个 L 角，`find_raw_corner()` 单独负责映回原始点列；不再把 raw 3x3 亮点复核塞进角点判定。local_angle 改成固定 dx/dy/dot/cross 模子，不再绕 c1/s1/c2/s2 归一化中间量；boundary_is_straight 也已收成单窗口、前段 nms 峰小角判据，boundary_is_lost 已从当前接口和实现中删除
tracking/boundary.cpp   已再收：双侧角点现在补了参考式二次检查；如果左右角点距离不像赛道宽，或角后边界没有继续向外张开，就同时清掉双角，先压掉会误触发 cross/ring 入口的假 L 角
tracking/boundary.cpp   已再收：单侧角点也加了前段约束；角点如果太靠后，或角后已经没剩下足够点列继续观察，就直接清掉，避免 `corner_now_index` 位置假靠前/假可用继续推进状态机
tracking/boundary.cpp   已再收：当前工程不引入 Y 角状态；`refresh_boundary_corners()` 现在只保留 `L / none`，不再让 `ring/cross` 吃“泛 corner”语义
tracking/boundary.cpp   已再收：`refresh_boundary_corners()` 已删除未使用的 raw gray 参数，L 角判定只依赖左右工作点列和 raw->IPM 矩阵
tracking/boundary.cpp   已再收：`boundary_is_straight()` 的角度门槛已从宽松大角收回到更接近参考版的直道小角阈值，避免对侧“其实在弯”却被当成长直道
tracking/boundary.cpp   已再收：L 角搜索现在只在前段固定范围内取第一个有效 L 角，不再在整条边上挑“最大峰”；这更接近参考版按前景角点推进状态机的写法
utils/types.hpp         已再收：cross_state_t 里的 left_flag/right_flag 改成 left_far_found/right_far_found，字段语义直接对齐十字远线是否找到；十字状态也已从 `kind + state` 双层收成参考版单状态 `NONE/BEGIN/IN`；同时新增 `left_l/right_l`，把“整条 farline sampled 点列”和“far L 点截断位”拆成两层事实；runtime / track 主状态树里的 `front_left_trace/front_right_trace/front_left/front_right` 已删除，十字 farline 中间态不再挂成全局主状态
utils/types.hpp         已再收：`TRACK_REJECT_NO_DUAL_TRACE` 已删除，当前普通主线不再保留双线失败 reject 分支；保留后续 reject 数字不前移，避免 report 语义漂移
app/runners.cpp         已同步：replay 打印里的 cross far 字段跟随 left_far_found/right_far_found，避免输出和 runtime 语义脱节
tracking/cross.cpp      已继续按参考工程收功能：NONE 入口现在直接按双 L 角点进十字，不再额外叠加宽度/角度/朝外几何 gate；BEGIN 截近线后也不再做连续确认，但当前推进到 IN 仍要求双 L 角同帧成立，避免单侧角点掉了还误切进十字。近角点“是否足够靠前”现在改成按 `当前边界重采样后的角点位置` 判断，不再继续盯 `original trace` 的旧索引；同时门槛也不再按当前线长占比漂移，而是直接按固定前段 step 推进，更贴参考版的固定采样距离语义。BEGIN 阶段当前也已经改成 `截到角点前`，不再把角点本身继续留在近线结果里；并且“近角点是否已经进入前段”的判断顺序也已提前到截断之前，避免先改 `now_step` 再回头判门槛。IN 阶段控车侧别也已进一步收回 `cross` 自己处理：`cross.track_type` 直接按“右 far L 优先、左 far L 次之、近线丢失补判最后”的顺序写入，`mainline` 只消费这个结果，不再重复推一次十字侧别；原先泛化的 `phase_counter` 也已改回参考语义 `not_have_line`，现在它只表示“近线双丢帧数”，不再伪装成通用阶段计数器。而且这部分近线丢失/恢复和补判判据现在也统一改成按 `now_step` 判断，不再混用 `original_step` 旧长度语义。当前 farline 仍保留为真实控车链，但外层和 L 点内核都继续向参考收拢：固定列 seed、单次 trace、IPM 投影、平滑、重采样、角度数组、NMS、L 角定位，不再保留多列候选搜索壳，也不再直接靠 front boundary 折角当 far L 点。当前 `cross_state_t` 不再直接只存 `L 点之后` 的结果，而是像参考版那样同时保留 `整条 farline sampled 点列 + L 点索引`，主线消费时再从 `L 点起` 取单边中线输入；同时 farline 的“整条线建出来”与“L 点找到”也已拆成两层行为，`left_far_found/right_far_found` 不再被 `far_l_index()` 成败绑死。原先挂在 runtime/track 上的 front trace/front boundary 中间态已经退回 cross 局部过程，而且“回切 raw trace”这条支线也已删除。当前固定列找 seed 的扫描段和失败清理也已并回 `build_cross_farline()` 主流程，不再额外保留 `cross_far_seed/clear_far_side` 这种单用 helper；但 cross 远线仍保留 `find_far_seed()`，没有强行复用 `find_column_seed()`，因为远线固定列和 edge_col 细节不同
tracking/cross.cpp      已再收：`build_cross_farline()` 的 raw -> IPM 点列投影已改用 `perspective_points()`，十字远线和普通主线/ring 共用同一套“前段出界跳过、已有有效点后出界截断”的投影语义，不再保留手写单应矩阵循环；远线投影现在只看 `rt->has_matrix`，不再被近线 seed pair 是否完整卡住，更贴近参考版 cross_farline 找到远线后直接 mapx/mapy 的语义
tracking/ring.cpp       功能合同已切到参考圆环五阶段：`BEGIN -> IN -> RUN -> OUT -> END`。`utils/types.hpp` 的 `RING_STATE_*` 已从旧的 `ENTER_LOST/RECOVER/INNER_FILL/MID_FILL/OUT_CORNER/EXIT_* /DONE` 改成参考语义；`tracking/mainline.cpp` 的 `ring_track_type()` 也同步改成 `BEGIN 外侧 -> IN 内侧 -> RUN 外侧 -> OUT 内侧 -> END 外侧`。`ring.cpp` 入口现在已经收成参考版那种单帧进入：只要命中“单侧 L 角 + 对侧 straight”，就直接进入 `BEGIN`，不再额外做入口连续确认，也不再保留 `pending_kind` 这类候选缓存；`BEGIN` 现在按参考版的“先丢后有”两段确认推进到 `IN`，并且这两段确认已拆成 `lost_count` 记 lost、`have_count` 记 have，不再把两件事揉进一个计数器里递减模拟；同时 `BEGIN` 不再主动清空当前控车边，并且在进入 `IN` 时直接记下 `encoder0`。当前 ring 的长度门槛也已继续收回参考版输入语义：BEGIN/END 统一按 `now_step` 做 `lost < 4`、`have > 20`，IN 阶段按 `now_step < 2` 或编码器里程推进；不再继续混用 `original_step` 这种 raw trace 长度。`RUN` 的出环判据现在直接看当前真实外侧边 L 角，不再在 RUN 阶段继续补 fake opposite boundary 再控车；一旦找到外侧 L 角，就先把当前真实外侧边截到角点，再按固定前段 step 推进到 `OUT`。`OUT` 现已收成参考版那种单门槛推进，对侧 straight 就直接进 `END`，不再额外做 straight 连续确认，也不再截短当前边界；`END` 现在要求先累计 enough lost，但一旦重新满足 have 条件就直接退出 `NONE`，不再额外做第二段 have 连续确认，并且左右退出门槛也已收回参考版细节：左环 `lost > 3`，右环 `lost > 2`。旧的 `lost/recover/fill/done` 语义已经从代码主流程中删除，不再把环岛写成通用恢复型状态机。与此同时，`build_opp()` 仍保留为真实补边链，但只留在 `IN` 阶段补外侧边，不再把 RUN 阶段也拖进补边支线；当前帧先清空 opposite boundary，再找 seed、trace、直线补点、拼接尾段、写回 opposite boundary；它已经不再把 ring 私有的临时 trace/front 落回 runtime 的 `track.front_left/right`，也不再额外构造 `front_boundary_t` 中转，而是直接用局部 `trace_t` 的原始点列当场补边。当前 `sync_bd()` 也已经改成重新走 `build_boundary_from_trace()`，所以环岛补出来的 opposite boundary 和普通主线边界使用同一套 `IPM -> blur -> resample` 语义；并且 `build_opp()` 入口就先清空当前帧 opposite boundary，失败时直接保持空边界，不再借上一帧 `opp` 偷续。当前 `ring_state_t` 已只保留 `kind/state/lost_count/have_count/encoder0` 五个运行字段；旧的 `pending_kind`、`pending_count`、`sum_zangle` 和空壳 `ring_add_yaw_delta()` 已从当前代码合同中删除。
tracking/ring.cpp       已再收：状态推进不再绕 `runtime_t &s / kind / st / phase / have` 这层别名，`ring_process()` 直接读写 `rt->ring.*` 和 `rt->track.*`，主流程更接近参考版的顺序式状态机模子；`build_opp()` 入口清空 opposite boundary 也已直接回到现场 `memset`，不再留 `clear_bd()` 这种单用 helper
tracking/ring.cpp       已再收：ring 私有 `has_matrix` 现在只看 `rt->has_matrix`，不再用 `seed_pair_accepted()` 卡住 opposite boundary 的 IPM 投影；环岛补边和普通单边主线使用同一套“有矩阵就投影”的控制坐标语义
tracking/ring.cpp       已再收：`build_opp()` 内部两段“打分找点”局部变量已统一回同一套 `best_i/best_v/dx/dy/v` 模子，不再一段叫 `seed_i/seed_v`、另一段又换 `join_i/join_v`
tracking/ring.cpp       已再收：`build_opp()` 里的 `best_i/best_v` 现在从 seed 选点到 trace 拼接整段复用同一组局部变量，固定列起点也从 `tr0` 收成更直白的 `p0`
tracking/ring.cpp       已再收：`build_opp()` 末尾那层无意义的 `if(num <= 0)` 已删除；直线补点本身就保证至少会写入一个点，不再保留假保护分支
tracking/element.cpp    已再收：内部调度名收成 run_state；元素互斥顺序改回参考版 cross 优先，cross 仍在时清 ring，空闲或 cross 本帧退出后再尝试 ring
tracking/perspective.cpp 已收：矩阵齐次分母 w，投影临时 p/num/rx/ry/x0/y0
tracking/zebra.cpp      已收：阈值和计数局部 th/num
tracking/mainline.hpp   已扫不改：接口已短，注释保留主流程含义
tracking/imgproc.hpp    已收：声明参数按 pts0/pts1/num0/num1/ref_x/ref_y 收敛
tracking/boundary.hpp   已收：声明参数 trace/boundary -> tr/bd
tracking/cross.hpp      已扫不改：单接口已短
tracking/ring.hpp       已收：声明参数 yaw_delta_deg -> dyaw_deg
tracking/element.hpp    已扫不改：单接口已短
tracking/perspective.hpp 已收：声明参数 raw/ipm 坐标按 x/y/ix/iy 收敛
tracking/zebra.hpp      已扫不改：单接口已短
utils/types.hpp         已扫不改：结构字段是跨模块合同，当前不做短名化
utils/tuning.hpp        已扫不改：参数名是调参合同，当前不做短名化
utils/clip.hpp          已收：内联参数 value/min/max -> v/min_v/max_v
```
