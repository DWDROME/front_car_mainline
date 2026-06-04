# tracking 主线合同

目标：固定 `front_car_mainline` 当前唯一主链，避免后续清理时重新引入旁路、wrapper 或 report-only 状态。

## 主链

```text
app/main.cpp
-> live / analyze / replay
-> tracking_process_frame(rt)
   -> find_seeds
   -> trace_edges / trace_single
   -> build_boundary_from_trace
   -> perspective_points / blur_points / resample_points
   -> refresh_boundary_corners
   -> element_process
   -> track_leftline / track_rightline
   -> center_x / guide_error writeback
   -> build_zebra_mid / zebra_process
-> solve_runtime / solve_runtime_with_feedback
-> drive_output_apply
```

tracking 内部顺序：

```text
raw gray
-> find_seeds
-> trace_edges / trace_single
-> build_boundary_from_trace
-> perspective_points / blur_points / resample_points
-> refresh_boundary_corners
-> element_process
   -> cross_process / ring_process 互斥
-> track_leftline / track_rightline
-> center_x / guide_error writeback
-> build_zebra_mid / zebra_process
```

当前对齐范围：

```text
已实现并继续向参考工程对齐：seed / trace / boundary / cross / ring / zebra / control
当前未实现，不纳入本轮主线对齐：yroad / 三叉
```

## 模块边界

```text
app/main.cpp          程序入口和模式分发
app/options.cpp       CLI/env/default 参数；被 main 和 runners 共用，暂不并入 main
app/runners.cpp       live/analyze/replay 编排，drive 使能，调试输出
tracking/mainline.cpp 每帧 tracking 编排，固定 rpts0/rpts1/rpts0b/rpts1b/rpts0s/rpts1s
tracking/imgproc.cpp  raw seed / trace + 单边/双边中线工具函数
tracking/boundary.cpp trace -> boundary、corner、front boundary
tracking/element.cpp  zebra / cross / ring 互斥调度
tracking/cross.cpp    十字状态树和 front farline
tracking/ring.cpp     环岛状态树和真实边界补线
tracking/zebra.cpp    斑马线黑白段扫描和 stop_line 状态
core/control.cpp      guide_error + 元素状态 + feedback -> target_yaw/duty
drivers/drive_output  duty 下发；未使能、停车或无有效输入时停机
```

## 必要状态

```text
输入：rt->gray, rt->matrix, rt->control_center_x
seed：rt->seeds, rt->seed_state, rt->mid_position
trace：rt->left_trace, rt->right_trace
boundary：rt->track.left/right
元素：rt->cross, rt->ring, rt->zebra
十字远线：cross.not_have_line, left/right_far_found, left/right_num, left/right_l
中线：rt->track.mid, track_type, center_x, guide_error
控制：input_valid, stop_request, target_yaw_rate_mrad_s, left_duty/right_duty
反馈累计：encoder_total（live 帧均值累计编码器总量，仅供元素状态推进）
```

`zebra` 当前语义：

```text
zebra.detected 不直接复用当前控制中线；mainline 会按参考 garage 语义另建扫描中线。
只有单侧 L 点时检查斑马线：左 L 用右边线外扩中线，右 L 用左边线外扩中线。
十字 IN 阶段不做斑马线黑白段扫描，只继续更新底部 stop_line。
stop_line 仍由原图底部大面积黑线连续多帧确认，控制层看到 stop_line 后置 stop_request。
```

`guide_error` 当前语义：

```text
track_leftline / track_rightline 先把控制中线起点归一化到 ref = {control_center_x, START_HIGH}
-> midline->dist[] 按这个起点累计弧长
-> lookahead_error() 按 LOOKAHEAD_DIST 取预瞄点
-> guide_error = atan2(预瞄点.x - ref.x, ref.y - 预瞄点.y)，单位 degree
```

注意：`guide_error` 是视觉外环输入，不是最终舵机角，也不是轮速差；控制层再按 `outer_kp/outer_kd/outer_sign` 转成 `target_yaw`。

`track_type` 当前判定顺序：

```text
十字 IN 直接吃 cross.track_type
-> 非十字态如果 ring 进行中，直接按 ring.state 定当前循线侧
-> 普通巡线按 rpts0s_num / rpts1s_num 失衡规则切单边
-> 双边都够长时沿用上一帧单边，不主动切 TRACK_TYPE_DUAL
-> 其余情况退回普通 left / right
```

注意：参考主循环只有 `TRACK_LEFT / TRACK_RIGHT` 两种普通巡线侧别；`track_dualline()` 仍保留在 `imgproc.cpp/hpp`，但当前普通主线不主动调用它。后续除非明确做双边中线实验，否则不要把它接回普通主链。

`boundary` 当前角点合同：

```text
当前工程不分 Y 角，也不把“任何大转角”都当成状态机入口。
refresh_boundary_corners() 当前按固定窗口先生成 `angle + nms` 数组，再按 `conf = |a[i]| - (|a[i-win]| + |a[i+win]|)/2` 只取边界前段第一个有效 L 角。
当前角点判定已去掉 raw 3x3 亮点复核，回到更接近参考版的纯几何角度语义；ring/cross 入口都只认 L 角。双 L 复核按参考默认值近似：角点间距约 45±15 像素，角点后 50 点张开距离需超过约 70 像素。
straight 仍单独由 boundary_is_straight() 现算，并且和参考版一样只看前段 nms 峰上的小角门槛。
```

`seed / trace` 当前合同：

```text
find_seeds() 当前按参考版 `begin_x / begin_y` 语义，从固定起线行、中心两侧固定偏移直接起搜；不再保留失败后向上补搜这条第二入口。
find_column_seed() 当前按 fixed-column 的“先白后黑，返回前一个白点起线”语义实现，并且只保留向上搜索这一条真实用法；ring 使用这一条固定列起线入口。cross 远线仍保留自己的 find_far_seed()，因为它有固定远线列和 edge_col 细节。
trace_left/trace_right 当前按参考版迷宫巡线模子推进：front 不通就转，side 可走就斜进，否则直进。
当前 trace 主核不再保留 visited / 回踩 / stuck 保护层。
```

`ring` 当前功能合同已经按参考圆环切成五阶段：

```text
BEGIN  单侧 L 角 + 对侧 straight 单帧进入；要求是单侧 L 角，不允许双侧 L 角同时误入；控车走外侧
IN     BEGIN 阶段按“先丢后有”两段确认后进入；控车走内侧
RUN    IN 阶段内侧线很短后直接进入；控车走外侧
OUT    RUN 阶段检测到当前真实外侧边前段 L 角后进入；控车走内侧
END    OUT 阶段检测到对侧 straight 后直接进入；控车走外侧
NONE   END 阶段先累计 lost，重新满足 have 后直接退出 ring
```

注意：

```text
当前 cross 已收成参考版单状态：`CROSS_STATE_NONE -> CROSS_STATE_BEGIN -> CROSS_STATE_IN`，不再额外保留 `kind + state` 双层十字状态。
当前元素互斥顺序也已收回参考版语义：十字优先级高于环岛；已有 cross 先跑，cross 仍在时清掉 ring；空闲或 cross 本帧退出后再尝试 ring。
当前 cross 的 farline 已按参考版收成固定双列主链：左侧固定列 `86/376 * RAW_W`，右侧固定列 `280/376 * RAW_W`；每侧都只在这一列向上找“先白后黑” seed，不再保留多列候选搜索壳。
当前 cross 的 farline 主流程是：固定列 seed -> trace_single -> IPM 投影 -> 平滑 -> 重采样 -> far L 点；远线只要 `rt->has_matrix` 就按 IPM 投影，不再依赖近线 seed pair 是否完整；当前 `rt->cross.left_pts/right_pts` 保存整条 farline sampled 点列，`left_l/right_l` 单独记录 far L 点位置；十字 IN 阶段主线现在直接从 `rt->cross.left_pts/right_pts + left_l/right_l` 这一段消费 farline，不再先搬进通用工作数组，也不再回到 raw trace 重做点列处理。
当前普通主线的左右边界点列也只要 `rt->has_matrix` 就按 IPM 投影；`seed_pair_accepted()` 只保留为 seed 宽度/IPM 几何诊断，不再决定单边外扩是否进入 IPM。
当前 farline 的“整条线构建成功”和“L 点命中成功”也已经拆成两层行为：`left_far_found/right_far_found` 只表示 farline 本身是否建出来，`left_l/right_l >= 0` 才表示当前这条 farline 上真的找到了 far L 点；十字选边时先看 L 点，再看近线丢失侧用于保持参考版 track_type 语义。
当前十字 IN 阶段的“这一帧到底跟左还是跟右”也已经收回 `cross` 状态机自己决定：`cross.track_type` 直接按 far L 点优先、近线丢失侧次之写入，`mainline` 十字分支现在直接消费这个字段，不再经过统一 `element hint` 分发层。
当前十字里原来的泛字段 `phase_counter` 也已经删除，直接改成参考语义 `not_have_line`：它只表示“近线双丢了多少帧”，不再伪装成通用阶段计数器。
当前本帧开始前已经处于 `CROSS_IN` 时，不再经过 `pick_track_type()` 这类普通巡线选择器；十字态只能直接吃 `cross.track_type` 的单边结果，拿不到侧别就直接拒绝，不再偷偷回退到 dual/普通单边长度规则。
当前本帧开始前已经处于 `CROSS_IN` 时，不再被普通 seed/trace 失败提前挡掉；即使近线 seed 或 trace 失败，仍会继续执行 `cross_process()` 里的远线搜索，再按 `cross.track_type` 生成十字中线。非 `CROSS_IN` 状态仍按普通 seed/trace 失败直接拒绝。
当前十字远线中线求解也已经从普通主线里单独抽出：本帧开始前已经处于 `CROSS_IN` 时，只按 `rt->cross.left_pts/right_pts + left_l/right_l` 这段 farline 单边结果调用 `track_leftline_from_start/track_rightline_from_start`；远线 L 不可用就直接拒绝本帧中线，不再回近线兜底，也不再像普通帧那样先选型、再走通用双边/单边中线分支。`from_start` 入口对齐参考版 `CROSS_IN begin_id = 0`，不做最近点重定位。
当前 `tracking_process_frame()` 的后半段顺序也已经收直：先看本帧开始前是否已是 `CROSS_IN`，再决定走十字远线分支还是普通/截短近线分支，不再在一个大段里来回三次判断十字 IN 状态。
当前 BEGIN -> IN 的推进门槛已经改成看 `当前边界重采样后的近角点位置`，不再继续盯 `original trace` 的旧索引；并且当前直接按固定前段 step 推进，不再按当前线长占比漂移，这更接近参考版里“近线 L 点已经很靠前”的固定采样距离语义。
当前 BEGIN -> IN 也继续要求双侧 L 角同帧仍然成立，不会因为只剩单侧近角点还在就误切进 `CROSS_IN`。
当前 IN 阶段里的近线丢失/恢复和补判，也已经统一改成按 `当前边界 now_step` 判断，不再继续混用 `original_step` 旧长度语义。
当前 BEGIN 阶段截近线时，也已经改成 `截到角点前`，不再把角点本身继续留在近线结果里；这更接近参考版先截近线、再切远线的模子。
当前 `tracking_process_frame()` 在 `element_process()` 后会把 BEGIN 截线同步回本文件内的 `rpts0s_num/rpts1s_num`，保证本帧普通中线不会继续吃到 L 角后面的近线；即使同一帧从 BEGIN 切到 IN，也先保留参考版“先截近线、再切远线”的顺序。
当前十字远线分支只在“本帧开始前已经是 `CROSS_IN`”时执行；同一帧从 BEGIN 切进 IN 时，仍按参考版用截短后的近线完成本帧中线，不立刻要求 `cross.track_type`。
当前 `cross_begin()` 里“近角点是否已经进入前段”的判断，也已经提前到截断之前完成；不再先改 `now_step` 再用同一索引回头判前段，避免门槛语义被自己刚做的截断污染。
当前 farline 的 trace 和前向几何中间态已经退回 `cross.cpp` 局部过程，不再挂在 runtime / track 主状态树上，也不再暴露成 `boundary` 层公共接口。
当前 ring 已不再使用旧的 ENTER_LOST / RECOVER / INNER_FILL / MID_FILL / OUT_CORNER / EXIT_* / DONE 语义。
当前 ring 仍保留真实 opposite boundary 补线链 build_opp()，不删真实控车数据来源。
当前 build_opp() 已改成局部构造 ring 自己的临时 trace，并用“起点直线补点 + trace 尾段拼接”直接补边；不再构造 ring 私有 front，也不再把中转状态落回 runtime 的 `track.front_left/right`。补右边界时走右手追线，补左边界时走左手追线，不再把“左环/右环”直接当成 trace 侧别。
当前 build_opp()/sync_bd() 生成 opposite boundary 后，也已经重新接回 `build_boundary_from_trace()` 这条主 boundary 链，保证环岛补边和普通边界使用同一套 `IPM -> blur -> resample` 语义。
当前 ring 的 opposite boundary 补边也只要 `rt->has_matrix` 就按 IPM 投影，不再依赖普通 seed pair 是否完整。
当前 build_opp() 入口就先清空当前帧 opposite boundary；一旦失败直接保持空边界，避免上一帧补边缓存偷偷混进当前帧判断。
当前 ring 已接入最小编码器里程门槛：live 主循环会把每帧左右编码器均值累计到 `rt->encoder_total`，`BEGIN -> IN` 时记录 `encoder0`，`IN -> RUN` 按“内侧线很短 或 走过约四分之一圆”推进。
当前入口已收成参考版的单帧进入 BEGIN：只要命中“单侧 L 角 + 对侧 straight”，就直接进入 BEGIN，不再额外保留 pending_kind 或入口连续确认门槛。
当前 BEGIN 的“先丢后有”已改成参考版那种双计数语义：`lost_count` 只记 lost 确认，`have_count` 只记 have 确认，不再把两段逻辑揉进一个计数器里递减模拟。
当前 BEGIN 阶段也不再主动清空当前控车边；它现在只读当前边长度做“先丢后有”判断，不额外改写边界。
当前 IN -> RUN 已补成参考版的双门槛推进：`内侧线很短` 或 `累计编码器超过约四分之一圆`。
当前 IN 阶段会保留内侧当前边，只补外侧边，不再像旧实现那样把控车侧边界清零。
当前 ring 各阶段的“线长是否足够/是否丢边”已经统一改成看 `当前重采样后的 now_step`，不再继续混用 `original_step` 这种 raw trace 长度；这和参考版按 `rpts0s_num/rpts1s_num` 推状态的语义一致。
当前 BEGIN / END 的“先丢后有”门槛按参考默认物理距离折算到当前 3px 重采样点列：`lost < 7`、`have > 34`；当前 `IN -> RUN` 的短边门槛为 `now_step < 4`，RUN 外环 L 点前段门槛为 `index < 14`。
当前 RUN -> OUT 已收回参考版语义：直接看当前真实外侧边 L 角，不再在 RUN 阶段继续补 fake opposite boundary 再控车。
当前 RUN 阶段一旦找到外侧 L 角，就会先把当前真实外侧边截到角点；是否推进到 OUT 再单独按 `corner_now_index` 是否落在固定前段 step 判据决定，不再继续拿 `corner_original_index/original_step` 这组 raw 语义做推进。
当前 OUT -> END 也已收成参考版的单门槛推进，不再额外做 straight 连续确认。
当前 OUT 不再截短当前边界，避免比参考版多做一层边界改写。
当前 END 阶段要求先累计 enough lost；一旦重新满足 have 条件就直接退出 ring，不再额外做第二段 have 连续确认。左右退出门槛也已对齐参考版细节：左环按 `lost > 3`，右环按 `lost > 2`。
当前 ring_state_t 只保留 `kind/state/lost_count/have_count/encoder0` 五个运行字段，不再保留 pending_kind / pending_count 这类入口候选缓存。
旧的 sum_zangle 和 ring_add_yaw_delta() 已从当前代码合同删除，不再保留无消费 yaw 累积壳层。
```

必须保留的 report/audit 字段：

```text
line_found
track_reject_reason
track_type
ring_kind / ring_state
cross_state
zebra_detected / zebra_stop_line
mid_position
control_center_x
left_seed / right_seed / seed_row / seed_width
left_trace_step / right_trace_step
mid_step
center_x / guide_error
matrix_loaded / ipm_geometry_reject_reason
```

注意：`seed_row/seed_width` 不是纯 report-only；它们参与 `seed_pair_accepted()`、IPM 几何判断和十字远线搜索起点。

## 参数入口

```text
RAW_W / RAW_H              utils/tuning.hpp
CONTROL_CENTER_X           utils/tuning.hpp / SMARTCAR_CONTROL_CENTER_X
START_HIGH / MINI_HIGH     utils/tuning.hpp
ROAD_HALF_WIDTH            utils/tuning.hpp
LOOKAHEAD_DIST             utils/tuning.hpp
TRACE_MIN_STEP             utils/tuning.hpp
FRONT_CAR_MATRIX           app/options.cpp / FRONT_CAR_MATRIX
control loop defaults      code/core/config.hpp 默认值，启动时读 /root/front_car_mainline.yaml；FRONT_CAR_CONFIG 可指定外置路径
```

调参顺序：

```text
seed/trace/midline
-> START_HIGH / MINI_HIGH
-> local threshold
-> ROAD_HALF_WIDTH / CONTROL_CENTER_X / LOOKAHEAD_DIST
-> corner / cross / ring / zebra
-> control PID
```

## 禁止事项

- 不在 `tracking_process_frame()` 外再套 tracking orchestrator。
- 不恢复 `state_machine_enabled`、`FRONT_CAR_ELEMENTS`、`--force-cross-in`、`--force-ring`。
- 不恢复多套 seed 候选池、shadow pipeline、simple fallback 或旧新双路线。
- 不让 IPM 图接管 raw seed/trace；IPM 当前只做点级几何、预览和审计。
- 不让 report/audit 伪造状态或把宽表字段塞回 runtime。
- 不在 `ring.cpp`、`cross.cpp`、`zebra.cpp` 内写电机或 PID。
- 不把 PID 调试混回 tracking 主线。

## 验证入口

```bash
bash "code/test.sh" --host
bash "scripts/straight_baseline_audit.sh" ".diag/front_car_capture_live_current.png"
bash "scripts/ipm_geometry_audit.sh" ".diag/front_car_capture_live_current.png"
```
