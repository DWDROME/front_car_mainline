# 弯道按转向连续减速

## Goal

给普通巡线增加**按转向幅度连续降低前进速度**的能力，解决"弯道基础速度过快、冲出赛道"。直道保持已 sweep 上去的高基速，弯道按转向需求自动减速。

## Context / 现状（已核实）

前进速度只有一处源头 —— `control.cpp:171-179` 的 `center_rps`：
```c
float center_rps = c.target_rps;                              // 直道+弯道共用，无区分
if(input->element_active) center_rps = c.element_target_rps;  // 仅 cross/圆环等"元素"降速
if(input->spin_mode)      center_rps = 0.0F;
```
- 普通赛道的弯（`check_road()` 已分出 `CURVE_NEAR/IN/OUT/S_CURVE`）**不是元素 → 全程满速 `target_rps`**。
- 弯道靠 `yaw_cmd` 拆左右轮差速转向，但**中心前进速度不降** → 冲出去。
- 全局降 `target_rps` 不可行（直道刚 sweep 上去）。

## 设计（方案 A，已选定）

在 `target_yaw` 算出后、差速运动学（`control.cpp:~327`）前，按转向幅度连续缩 `center_rps`：

```c
// 仅普通巡线生效；元素/spin 已各自管速度
if(!input->element_active && !input->spin_mode && c.curve_speed_slowdown > 0.0F)
{
    const float ratio = clip_f(abs_f(target_yaw) / c.max_target_yaw_rate, 0.0F, 1.0F);
    center_rps *= (1.0F - c.curve_speed_slowdown * ratio);
}
```

定型决策：
1. **信号用 `target_yaw`**（视觉外环需求，IMU 内环修正之前）：它反映赛道弯曲程度，且已被 `straight_turn_scale` 抑制直道抖动 → 直道≈满速、弯越急越慢、预瞄提前刹。不用 `yaw_cmd`（含 IMU 修正，不纯）。
2. **单参数 `curve_speed_slowdown ∈ [0,1]`**：满转向时速度 = `target_rps * (1 - curve_speed_slowdown)`。线性、一个旋钮。
3. **默认 0 = 不改变现有行为**：合入后行为与现在逐位一致，上车把它从 0 往上调到弯道稳住。
4. **只在 `!element_active && !spin_mode` 生效**：元素/spin 速度各有归属，不叠加。
5. **配置走 yaml**：与 `target_rps`/`element_target_rps`/`base_percent` 同类（都是上车 sweep 的调参项），加到 `config.hpp` 默认值 + `config.cpp` 的 `F()` 绑定 + `front_car_mainline.yaml`。

## Requirements

- [ ] `config.hpp` 增 `float curve_speed_slowdown = 0.0F;`
- [ ] `config.cpp` 在解析宏里加 `F(curve_speed_slowdown)`
- [ ] `front_car_mainline.yaml` 增 `curve_speed_slowdown:`（带注释，默认 0）
- [ ] `control.cpp` 在 `target_yaw` 后、运动学前注入上面的连续缩放
- [ ] 默认 0 时行为与原版一致

## Acceptance Criteria

- [ ] `cmake --build code/build-host` 通过
- [ ] `config_parsing_test` / `options_parsing_test` 通过（新增字段不破坏解析）
- [ ] 默认 `curve_speed_slowdown=0` 时，control 输出与改动前一致（无行为变化）
- [ ] diff 自审：单点注入、无第二速度源、无跨层接线
- [ ]（硬件侧）上车从 0 调起，弯道不冲出、直道基速不受影响

## Definition of Done

- 改动落地，host build + 既有测试绿
- diff 自审通过（仅 control.cpp + config 三处 + yaml）
- 代码侧 DoD 到 build+测试；`curve_speed_slowdown` 标定在车上做

## Out of Scope

- 不接 `road_type` / 不做离散弯/直分速（方案 B）
- 不加转向死区/拐点（knee）——v1 先线性，单旋钮；如直道被拖慢再议
- 不动 `element_target_rps` / `spin_mode` / yaw 内环 / FF-PI
- 不引入按曲率半径或速度自适应的复杂模型

## Decision (ADR-lite)

**Context**: 弯道与直道共用 `target_rps`，弯道不减速会冲出；需要按弯减速且不拖慢直道。
**Decision**: 在 `center_rps` 单点按 `|target_yaw|/max_target_yaw_rate` 连续缩放（方案 A），单参数 `curve_speed_slowdown`，默认 0。
**Consequences**: 单点、不跨层、默认无行为变化、比例+预瞄对"冲出去"对症。放弃方案 B（road_type 离散分速）的理由：跨层接线、二值跳变、依赖 `check_road` 阈值在差速车上的可靠性。

## Technical Notes

- 注入点：`code/core/control.cpp` `solve_control_input_with_feedback`，`target_yaw` 定义在 ~238-263、运动学在 ~319-331。
- 速度源：`center_rps`（control.cpp:171-179）。
- 配置：`code/core/config.hpp:13-17`、`code/core/config.cpp:104-106`、`front_car_mainline.yaml`。
- 弯/直分类（本任务未用，仅备参）：`atg_reference/Project/CODE/road.c` `check_road()`。
