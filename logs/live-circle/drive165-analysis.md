# drive165 — 右圆环测试分析

> 2026-06-22, branch: port/atg2022-reference-control
> 代码: circle.c + reference_step.c 大佬出环修复 + 280° OUT→END 阈值
> 配置: outer_kp=0.08, yaw_kp=2.0, max_yaw_rate_correction=0.40, slowdown=0.60

## 状态机转换 ✅

| 转移 | steering | heading | 帧数 |
|------|---------|---------|------|
| NONE→RIGHT_BEGIN | entry_vote | 0° | 191f |
| RIGHT_BEGIN→RIGHT_IN | entry_distance (2003) | 3.4° | 22f |
| RIGHT_IN→RIGHT_RUNNING | gyro (600) | 60.0° | 40f |
| RIGHT_RUNNING→RIGHT_OUT | gyro (2000) | 200.0° | 21f |
| RIGHT_OUT→RIGHT_END | gyro (2804) | 280.4° ✅ | 40f |
| RIGHT_END→NONE | distance | — | 105f |

## 核心问题：RIGHT_IN 固定线几何过猛

### 入口证据（正常）
```
frame=0: near=125/37 raw=105/119 l=0@-1/1@18 straight=1/0 → 有左右线点、有Lpt1
```
入口检测正常，赛道线可见。不是"road classifier 不认"。

### 从 RIGHT_IN 开始失控
```
RIGHT_IN 第1帧: guide=-56.84（饱和）, yaw=+4500（饱和，=max_target_yaw_rate）
                duty=-12/33（左轮逆向刹车）, near=153/0（右线已消失）
```

### 左右环对比（饱和/不对称证据）

| 指标 | 左环 drive164 | 右环 drive165 | 差距 |
|------|-------------|-------------|------|
| approach guide | 0.6° | -2.8° | 对称 |
| IN guide | +37.4° | **-56.84°** | 右环大 52% |
| IN→RUNNING dist | 661 | **452** | 右环短 32% |
| RUNNING yaw avg | -1903 | **+4500** | 右环饱和 |
| RUNNING→OUT dist | 2505 | **569** | 右环短 77% |
| RUNNING 帧数 | 149f | **40f** | 右环仅 27% |
| END 后恢复 | road=3 760f | road=0 卡死 | |

右环固定线幅值比左环大约 52%（56.8° vs 37.4°），导致车以饱和 yaw 高速旋过圆环。

### 根因

`circle_in_fixed_left` / `circle_out_fixed_left`（右环用）的固定线几何
与 `circle_in_fixed_right` / `circle_out_fixed_right`（左环用）不对称。

推测：
- 固定线的 RAW_LEFT_ANCHOR_X vs RAW_RIGHT_ANCHOR_X 偏移侧不对称
- 或者 point_Cal_Line vs point_Cal_Line_2 的点序差异导致 guide 符号/幅值放大

### 建议（给大佬）

1. 右环问题与 road 类型分类无关，是固定线几何问题
2. 不要动左环 280° 出环阈值（drive164 已验证成功）
3. 如要右环实车，优先调 CIRCLE_RIGHT_IN 固定线的偏移量或点序

## 原始日志

logs/live-circle/20260621-drive165-front_car_circle_drive165.log
