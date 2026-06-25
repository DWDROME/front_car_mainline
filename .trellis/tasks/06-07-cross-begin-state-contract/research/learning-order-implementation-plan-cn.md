# Learning-Order Guard 实施记录

本文记录 `learning-order guard` 的代码级合同和已执行 patch。

## 1. 修改目标

只解决一种学习污染：

> 帧首普通、seed/trace/IPM 通过，但最终没有 selected usable midline 时，
> 当前代码仍可能提前写 `mid_position/width_base`。

不解决、也不伪装解决：

- 单侧身份静态不可证明；
- 错误单侧身份但完整前方预瞄发布门也成立；
- 控制 yaw/duty 抖动；
- ring/cross 真实相机验证缺失。

## 2. 文件范围

只改：

| 文件 | 改动 |
| --- | --- |
| `code/tracking/mainline.cpp` | 改 `update_search_center()` 签名；调整调用时序；加入 `ordinary_frame0` |

不改：

| 文件/函数 | 原因 |
| --- | --- |
| `publish_track_result()` | 控制发布安全门保持原样，但普通帧 learning 现在等它成功后才写回 |
| `midline_has_forward_lookahead()` | 普通帧完整前方预瞄门同时约束控制发布和下一帧搜索中心学习 |
| `find_seeds()` | 不改 seed 搜索 |
| `trace_edges()` | 不改 raw 身份门 |
| `work_pair_order_ok()` | 不改 IPM 反序门 |
| `cross.cpp` / `ring.cpp` | 第一版不混入元素状态机变更 |
| `control.cpp` | 不碰 yaw/duty/PID |

## 3. 精确代码步骤

### 3.1 改 `update_search_center()` 签名

当前：

```cpp
void update_search_center(runtime_t *rt)
```

目标：

```cpp
void update_search_center(runtime_t *rt, int allow_width_base)
```

内部只改 `width_base` 低通条件：

```cpp
if(allow_width_base && seed_pair_accepted(&rt->seeds, rt->seed_state))
```

不要继续用：

```cpp
rt->ring.kind == RING_KIND_NONE && rt->cross.state == CROSS_STATE_NONE
```

原因：延后到 `element_process()` 后时，这两个状态已经可能被本帧修改；`width_base` 是否允许低通必须来自帧首普通语义。

### 3.2 帧首记录 `ordinary_frame0`

位置：`frame_action_t action = {};` 设置完 `cross_state0/ring_kind0` 后。

```cpp
const int ordinary_frame0 =
    action.cross_state0 == CROSS_STATE_NONE &&
    action.ring_kind0 == RING_KIND_NONE;
```

### 3.3 当前早期学习点改成延后服务已在元素态的 nearline 路径

当前位置在 `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` 未触发后的分支中。

当前：

```cpp
update_search_center(rt);
snapshot_ring_frame_start_action(rt, &action);
element_process(rt);
action.base_candidates_ready = 1;
```

第一版目标曾是：

```cpp
if(!ordinary_frame0)
{
    update_search_center(rt, 0);
}
snapshot_ring_frame_start_action(rt, &action);
element_process(rt);
action.base_candidates_ready = 1;
```

原因：帧首已经在 cross/ring 的帧保持第一版边界；这些帧不允许 `width_base` 低通。

2026-06-09 后续收紧后，元素态也不在这里直接学习，只记录这个路径原本会学习：

```cpp
if(!ordinary_frame0)
{
    defer_element_search_center_update = 1;
}
snapshot_ring_frame_start_action(rt, &action);
element_process(rt);
action.base_candidates_ready = 1;
```

原因：元素帧最终 `publish_track_result()` 失败时，不应把当前 seed 教给下一帧。
但只在原早期学习所在的 accepted nearline 分支置 flag，避免给 CROSS_IN farline-only
或 IPM 反序后远线成功路径新增学习。

### 3.4 publish 成功后补普通帧学习

位置：`const int mid_ok = build_selected_midline(rt, &mode, ref);` 后，
`publish_track_result()` 成功后。

```cpp
if(!publish_track_result(rt, &mode, mid_ok, ref))
{
    return 0;
}
if(ordinary_frame0)
{
    update_search_center(rt, 1);
}
else if(defer_element_search_center_update)
{
    update_search_center(rt, 0);
}
```

2026-06-09 收紧原因：普通帧已经新增完整前方预瞄发布门。若一个短中线或
后方预瞄帧被 `publish_track_result()` 拒绝，却仍先写入 `mid_position`，
它不会发当前控制，但会污染下一帧 seed acquisition。因此普通帧 learning
必须等最终发布门成功。

## 4. 预期行为变化

| 帧类型 | 旧行为 | 新行为 |
| --- | --- | --- |
| 帧首普通，`work_track_type == NONE` | 可能已经学习 | 不学习 |
| 帧首普通，selected side 存在但 `mid_ok < k_min_border_step` | 可能已经学习 | 不学习 |
| 帧首普通，`mid_ok >= k_min_border_step`，forward-lookahead 失败 | 学习，但不发布控制 | 不学习，不发布控制 |
| 帧首已在 cross/ring，且 nearline seed/trace/IPM 通过 | 早期学习，`width_base` 不更新 | 发布成功后学习，`width_base` 不更新 |
| CROSS_IN farline-only 或 IPM 反序后远线 | 不学习 | 保持不学习 |
| IPM 反序拒绝 | 不学习 | 保持 |

## 5. 必须满足的不变量

- 不改变 `publish_track_result()` 内部语义。
- 不改变 `midline_has_forward_lookahead()` 内部语义。
- 不改变 `guide_error` 计算。
- 不改变 `track_type_keep` 更新位置。
- 不改变 cross/ring 状态机。
- 不新增 single-side reject。
- 不新增 same-trace dual hypothesis。
- 不新增宽度/漂移/attach-distance runtime gate。
- 不复用旧中线、旧边界、旧 `guide_error`、旧 duty。

## 6. 复核点

改完后人工检查：

1. `rg -n "update_search_center\\(" code/tracking/mainline.cpp`
   只能看到：
   - 函数定义；
   - accepted nearline 非普通帧只置 `defer_element_search_center_update`；
   - publish 成功后普通帧调用 `update_search_center(rt, 1)`；
   - publish 成功后且 `defer_element_search_center_update` 为真时调用
     `update_search_center(rt, 0)`。
2. `TRACE_IDENTITY_REJECT_IPM_SIDE_CROSS` 分支仍在任何学习前返回或切 farline。
3. `ordinary_frame0` 只由 `action.cross_state0/action.ring_kind0` 定义。
4. 普通帧 learning 在 `publish_track_result()` 成功之后。
5. 没有新增任何 side identity guess。

## 7. 理由表

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 没有动态 `mid_position/width_base`；普通帧从固定起点重建线，selected centerline 成立后才进入控制计算。 | 当前项目为了 Front_Car 式恢复保留跨帧搜索中心；新增普通帧完整前方预瞄门后，短/后方预瞄帧可能被拒绝控制但仍提前学习。 | 只把帧首普通帧的学习延后到 `publish_track_result()` 成功后。 | 让跨帧 acquisition prior 由当前可发布的完整前方预瞄中线背书。 | 不合成线、不双假设、不 hold 旧输出、不加宽度/漂移阈值；失败帧仍失败且不写下一帧搜索中心。 |
| RT1064 允许单侧普通追线。 | 当前单侧/no-opposite-anchor 身份仍不可静态证明。 | 不加单侧硬拒绝。 | 静态代码无法证明单侧身份；硬拒绝会误杀合法曲线/元素接近。 | 保持单侧 tracking 允许，只保护学习时序。 |
| RT1064 steering publish 与当前 acquisition learning 不是同一个状态；RT1064 也没有项目本地动态搜索中心。 | 当前 `publish_track_result()` 同时检查 `mid_ok` 和完整前方 lookahead，且 lookahead 失败正是本轮实车风险。 | 用完整 publish success 作为普通帧 learning gate。 | 防止 `frame=2911` 后方预瞄和 Image #4 短预瞄这类失败帧教坏下一帧 seed 搜索中心。 | publish 失败仍不输出当前控制，也不复用旧状态；只是拒绝把失败几何写入 acquisition prior。 |

## 8. 当前状态

已实现。

实施点：

- `code/tracking/mainline.cpp:update_search_center()` 增加显式
  `allow_width_base` 参数；
- 帧首普通帧跳过 IPM 复核后的早期学习；
- `publish_track_result()` 成功后，只有帧首普通帧才学习
  `mid_position/width_base`；
- 帧首已在 cross/ring 的 accepted nearline 帧发布成功后学习，且
  `allow_width_base = 0`；
- `publish_track_result()`、`midline_has_forward_lookahead()`、cross/ring 状态机和
  control 链路未改。

已验证：

- `git diff --check`
- `bash code/test.sh --host`
- `bash code/test.sh`
- host analyze smoke:
  - `.diag/video_crop_input/t16.png`
  - `.diag/video_crop_input/t36.png`
  - `.diag/video_crop_input/t60.png`
  - `.diag/synth/straight_cross_like.png`

验证结果：t16/t36/t60 仍 `line_found=1` 且 `ring_kind=0/ring_state=0`；
`straight_cross_like` 仍因当前帧身份拒绝失败，`ring_kind=0/ring_state=0`。
