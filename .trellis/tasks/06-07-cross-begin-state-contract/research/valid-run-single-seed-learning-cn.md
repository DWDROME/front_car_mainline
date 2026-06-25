# 候选有效段与普通单侧学习保护

日期：2026-06-09

## 结论

本轮新增两处小算法修正，均来自 `.diag/video_crop_input/t48.png` 的可复现证据。

1. `build_rptsn()` 的普通/近线路径不应因为候选中线前缀存在无效点就整条拒绝。
   它应先取连续有效段，再从有效段中选择离控制参考点最近的 begin。
2. 普通帧单侧 seed 发布成功后，如果按 `width_base` 外推得到的下一帧搜索中心
   距已发布中线起点超过半路宽，不应学习这次单侧外推。

这两处都不改变当前帧控制的证据来源，不复用旧中线，也不合成对侧线。

## 现场证据

改动前 `t48`：

- 图像中左边界清晰；
- `left_trace_raw_step=160`，`left_trace_raw_gain=63`；
- `candidate_left_after_crop=50`；
- 但 `selected_mid_ok=0`，`line_found=0`。

原因：

- 左边界靠近图像边缘，单边外扩候选的前缀可能落到 IPM 有效区域外；
- 旧 `build_rptsn()` 在非 `force_begin_id0` 路径上要求所有候选点有效，因此整条拒绝；
- 解开后，`t48` 当前帧能生成 `mid=62`，`mid_max_dist=188`，`mid_forward_lookahead=1`。

随后发现第二个问题：

- 解开 `t48` 后，普通单侧学习把 `mid_position=80` 拉到 `41`；
- 同一张图 replay 第二帧会误找到右 seed，进入 `idrej=1/rej=3`；
- 这不是当前帧控制问题，而是跨帧 acquisition prior 被边缘单侧 seed 污染。

修正后：

- `t48` 当前帧仍发布：`line_found=1 guide=-32.0705`；
- `xlearn=1/80/80/52/52`，即普通帧学习路径被记录，但 `mid_position` 不移动；
- 同图 replay 3 帧均保持 `line=1`；
- `t60` 仍允许合理单侧学习：`xlearn=1/80/73/52/52`。

## 固定理由表：候选有效段

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 不存在当前项目的 IPM 查表无效点合同；其点列在自身坐标链内直接生成 `rpts/rptsn`。当前项目已有 `first_valid_run()` 处理 IPM 有效连续段。 | `build_rptsn()` 非 `force_begin_id0` 路径旧代码遇到任意无效候选点就返回 0；靠边单边外扩时，前缀越界会误杀后续有效段。 | `code/tracking/imgproc.cpp::build_rptsn()` 在 `force_begin_id0=0` 时先取第一段连续有效点，只在该有效段内选 begin，并只使用 begin 到有效段结尾。`force_begin_id0=1` 仍保持全点有效的严格要求。 | 普通/近线候选的语义是从当前帧有效控制中线段发布，不是要求候选数组每个槽位都在视野内。CROSS_IN 强制 begin0 是参考合同，不能被这刀放宽。 | 不复用旧中线，不合成对侧线，不降低发布门。`t48` 因当前帧有效段足够才发布；`t16/t36` 仍因 `mid_max_dist=28/29` 失败；CROSS_IN forced begin 测试仍拒绝无效前缀。 |

## 固定理由表：普通单侧学习保护

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 没有 `mid_position/width_base` 跨帧学习；每帧从固定种子附近重建。项目 spec 已要求单侧风险优先保护 learning state，而不是硬拒当前帧。 | 当前普通帧单侧成功发布后直接用 `seed +/- width_base/2` 学习下一帧中心。`t48` 的边缘左 seed 会把中心从 80 拉到 41，下一帧同图误找右 seed 并 `idrej=1`。 | `code/tracking/mainline.cpp::update_search_center()` 中，仅当 `allow_width_base=1` 的普通单侧外推中心与已发布 `center_x` 相差不超过 `ROAD_HALF_WIDTH` 时才学习。元素帧 `allow_width_base=0` 不受此保护影响。 | 当前帧可控制不等于下一帧 seed search prior 一定可信。普通边缘单侧 seed 的外推中心若偏离已发布中线起点超过半路宽，说明它会把下一帧搜索中心拉到车道外。 | 不拒绝当前帧，不复用旧中线/旧 guide/旧 duty，不合成对侧线；只是不把异常单侧外推写入跨帧 acquisition prior。`t48` 当前帧仍发布，replay 稳定；`t60` 合理单侧仍学习到 73。 |

## 新增诊断

- `trace_left_raw_gain`
- `trace_right_raw_gain`
- live/replay 单行 `tg=left/right`

用途：

- 区分 `raw_step=160` 是有效向前爬线，还是横向贴线/循环。
- 当前批量结果显示 `t20/t24/t40/t52` 的右 trace 虽然 `raw_step=160`，
  但 `raw_gain=1`，因此保持失败合理。

## 验证

命令：

```bash
git diff --check
bash code/test.sh --host
bash code/test.sh
./code/build-host/front_car_mainline --replay .diag/video_crop_input/t48.png 3 --report .diag/video_crop_input/t48.replay_report.txt
```

结果：

- `git diff --check` 通过。
- `bash code/test.sh --host` 通过。
- `bash code/test.sh` 通过。
- `t48` replay 3 帧均 `line=1`，`xlearn=1/80/80/52/52`。
- 批量 `.diag/video_crop_input/*.png`：
  - `t16/t36` 仍失败且不学习；
  - `t20/t24/t40/t52` 仍因 raw trace 纵向爬升不足失败；
  - `t48/t60` 发布；
  - 失败帧 `search_update_kind=0`。

## 保留风险

- `t48 guide=-32.0705` 较大，但该图像本身是明显弯道/边界靠左场景；
  当前没有证据证明这是直道硬拐。下一轮现场若出现直道大 guide，需要结合
  `md/tg/xlearn` 和图像一起判定。
- 已知仍缺真实 already-in-ring/cross 成功发布序列，不能声称 V03/V05 或
  `frame=3570` 根因已解决。
