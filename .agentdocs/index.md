# Agent Docs

`.agentdocs` 只保留当前事实，不再保存迁移期长账本。

## 活跃入口

- `"tracking_mainline_contract.md"`：当前唯一主线、模块边界、必要观测字段、参数和禁止事项。
- `"tracking_complexity_map.md"`：已经清掉的 set/wrapper/report-only 状态、剩余清理点、验证入口。

## 当前结论

```text
app/main.cpp
-> live / analyze / replay
-> tracking_process_frame
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

- 主线只保留一条，不恢复 shadow pipeline、simple fallback、强制元素状态或旧新双路线。
- 普通主线对齐参考版只主动选择 `TRACK_TYPE_LEFT / TRACK_TYPE_RIGHT`；`track_dualline()` 仍保留为明确实验和实车验证后的双边中线函数，不接回当前主链。
- `app/application.cpp/.hpp` 已删除；入口逻辑并入 `app/main.cpp`。
- `app/options.cpp` 暂时保留，因为 `main.cpp` 和 `runners.cpp` 都消费默认路径、环境变量和控制中心读取。
- `seed_row/seed_width` 虽然会进 report，但也被 `seed_pair_accepted()`、IPM 几何和十字远线搜索消费，不能当纯 report-only 字段删除。
- assistant 黄/绿边线发送 raw `original_pts`；红线用 raw 左右边界同 y 行中点，不直接发送控制中线 `rt->track.mid`。
- assistant 三条线共用一个 `dot_num`，当前取 `max(n0,n1,n2)` 并用末点补齐短线，不能再裁成最短线。
- L 角双边复核点仍然保留；assistant 只画真正 `l_ok` 的 L 角和十字远线，不画 pair 支撑点，也不把角点混进边界三线发送。`seekfree_assistant_camera_boundary_slots_config()` 作为一次多槽位试验残留保留在共享库注释里，front_car_mainline 当前 runtime 已退回只发 `slot0/1/2 = 左/中/右主线`。
- `key_supervisor` 当前只清理 `front_car_mainline` 进程，不再保留旧名 `project` 的 kill 兼容路径；控制参数统一由 `config.hpp` 默认值和 `/root/front_car_mainline.yaml` / `FRONT_CAR_CONFIG` 管。
- `key_supervisor` 的 K3 抓拍会先停车并杀主程序，请求 `/dev/video0` 输出 `1280x720`，图片保存到 `/root/1_photo`；日志会记录实际保存尺寸。
- `max_duty_percent` 是控制层输出上限；`drive_output.cpp` 仍保留 35% 驱动层硬件安全上限，yaml 不能越过该边界。

## 压缩结果

迁移期长账本已删除，只保留当前事实入口：

```text
index.md
tracking_mainline_contract.md
tracking_complexity_map.md
```
