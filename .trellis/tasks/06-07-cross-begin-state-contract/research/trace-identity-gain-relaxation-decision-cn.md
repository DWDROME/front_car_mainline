# Trace 身份门纵向增益放宽撤回记录

日期：2026-06-09

## 结论

不保留“越过对侧 seed 发生得足够远就放行”的行为改动。

当前保留的是诊断，不是放行阈值：

- `tg=left/right`：trace 原始纵向爬升量；
- `tp=left/right`：trace 第一次越过对侧 seed 时已经爬升的行数；
- `trace_identity_reject_bits()` 仍然只要当前帧双 seed 关系中出现越过对侧
  seed，就拒绝对应 trace。

这次撤回的原因不是构建问题，而是证据不足：`t28/t32/t56` 在单帧 fresh runtime
下放行后会发布控制，但原视频控制台里这些帧附近属于 cross/element 时序，不能拿
fresh ordinary analyze 证明这是合法普通帧。现有 Trellis 规格和历史研究都要求
`t28/t32/t56` 保持 fail-closed，除非后续拿到序列级合法反例。

## 固定理由表

| 参考版怎么样 | 当前代码差异 | 我修改什么 | 原因 | 不是兜底的证据 |
| --- | --- | --- | --- | --- |
| RT1064 `imgproc.c:247-330` 左/右手追线分开执行，`imgproc.c:611-635` 左/右边线分别外扩到中线；没有“越过对侧 seed 但纵向爬升足够就放行”的阈值合同。 | 当前项目有额外的 raw trace 身份门，历史研究已把 `t28/t32/t56` 记录为应由身份门拒绝的样本；临时 `gain < 8` 放宽会把这些帧变成可发布控制。 | 撤回纵向增益放行条件；`code/tracking/mainline.cpp::trace_identity_reject_bits()` 仍在 `trace_pass_seed_gain() >= 0` 时拒绝。保留 `tp` 仅用于日志解释。 | 没有序列级合法反例能证明 `tp=60/66/72` 的越过是正确边界；单帧 fresh analyze 与现场 cross 状态不一致。 | 失败帧仍失败，不复用旧中线/旧 guide/旧 duty，不合成对侧线；`t28/t32/t56` 串行重跑为 `idrej=1/1/2`、`rej=3`，`t60` 仍 `line=1`。 |

## smart-search 旁证

命令：

```bash
smart-search doctor --format json
smart-search search "line following robot smart car left right boundary tracing seed crossing opposite side identity rejection single side line tracking" --model "grok-4.20-multi-agent-xhigh" --extra-sources 3 --timeout 120 --format json --output .trellis/tasks/06-07-cross-begin-state-contract/research/smart-search/line-tracking-identity-search-2026-06-09.json
smart-search fetch "https://patents.google.com/patent/CN114863387A/zh" --format json --output .trellis/tasks/06-07-cross-begin-state-contract/research/smart-search/cn114863387a-fetch-2026-06-09.json
smart-search fetch "https://blog.csdn.net/longqiu_LQ/article/details/160896921" --format json --output .trellis/tasks/06-07-cross-begin-state-contract/research/smart-search/longqiu-line-tracking-fetch-2026-06-09.json
```

结果：

- `smart-search doctor` 可用；实际使用 `grok-4.20-multi-agent-xhigh`。
- broad search 支持“智能车视觉循迹常见左右边界、单边循迹、身份/方向拒判、元素处理”
  这些通用概念，但没有提供能支撑本项目放宽 dual-seed 身份门的强合同。
- fetched `CN114863387A` 是循迹智能车赛道识别与分类方法的通用背景资料；
  fetched CSDN 页面主要是竞赛/硬件/规则经验，不能替代本地 RT1064 参考版。

因此外部资料只作为旁证：它支持继续保留身份/方向拒判和单边循迹并存的设计方向，
但不支持新增“远处越过对侧 seed 可放行”的行为阈值。

## 验证

命令：

```bash
git diff --check
bash code/test.sh --host
./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t28.png
./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t32.png
./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t56.png
./code/build-host/front_car_mainline --analyze .diag/video_crop_input/t60.png
```

结果：

- `git diff --check` 通过。
- `bash code/test.sh --host` 通过。
- `t28`：`idrej=1`，`rej=3`，`line=0`，`tp=72/-1`。
- `t32`：`idrej=1`，`rej=3`，`line=0`，`tp=66/-1`。
- `t56`：`idrej=2`，`rej=3`，`line=0`，`tp=-1/60`。
- `t60`：`idrej=0`，`rej=0`，`line=1`，`guide=12.88`。

## 后续判断门

如果后续要再次讨论放宽身份门，必须先满足以下条件：

- 有真实序列级 replay 或现场日志，而不是 fresh runtime 单帧；
- 该序列证明越过对侧 seed 的 trace 是合法同侧边界，不是 cross/ring/状态错位；
- 同时证明 strict reject 是造成当前问题的 owner，而不是 farline、候选裁剪、
  selected midline、publish lookahead 或控制链的问题。
