# circle-log-analysis-example
> 使用强制 8 段格式的完整分析示例（drive62）

## ① 入口防误判（ray hit）✅

```
seed=38,20  hit=1@34,16  ray=-1,-1  命中内圆边界
锚点 Lpt0 id=33（正常，id<35，但偏大说明在较远处触发BEGIN）
```

- `ATGCircleEntryBreakpoints: side=L near=1@34 seed=38,20 hit=1@34,16 ray=-1,-1 sharp=0 raw=38.9,20.2 th=105`
- 第二次 breakpoints: `near=1@33 seed=39,20 hit=1@35,16 ray=-1,-1`
- 紧接着 `ATGCircleCal: from=CIRCLE_NONE to=CIRCLE_LEFT_BEGIN reason=entry_vote`
- **结论**: ray hit 正确，但 Lpt0 id=33 偏大，说明入口检测在较远处就触发了

## ② BEGIN 阶段（frame 71-253，共183帧，约1.8秒）

```
帧    near      lpt锚点  guide   yaw    duty     src  说明
71    61/124   id=33   +5.49  -439   13/5     11   入BEGIN，远线0/0
82    1/124    id=28   +4.56  -365   11/7     11   近线几乎全丢一次(conf=0)
120   57/124   id=31   +3.11  -249   8/10     11   左线持续，guide下降
183   54/124   id=29   +1.82  -146   7/12     11   guide继续下降
253   0/124    id=-1   +0.80  -64    11/8     11   BEGIN末，左线消失
```

- **远线**: far=0/0 全程无
- **近线**: 左线从61逐渐降到0，右线124保持，全程双线→末仅右线
- **Lpt id**: 33→28→31→29→-1，正常递减
- **guide**: 从+5.49逐渐降到+0.80，正常趋势
- **circle_cnt**: 全程0/0/0/0（未触发固定线）
- **BEGIN末**：`near=0/124` 左线已全丢，`conf=0.0/2.4` 左线置信度0
- **过渡条件**: `ATGCircleCal: BEGIN→IN reason=entry_distance heading_deg10=23 dist=2004`

## ③ IN 阶段（frame 254-305，共52帧）

```
首(254):  near=0/124  guide=+37.36(饱和!)  yaw=-2989  duty=27/-9  src=5  入IN
末(305):  near=0/65   guide=+37.36(饱和!)  yaw=-2989  duty=24/-8  src=5  出IN
```

- **guide/yaw 全程定死饱和**: guide=+37.36, yaw=-2989, 全程不变
- **远线**: far=0/0 全程无
- **近线**: 全程左线0(全丢)，右线124→65逐渐减少
- **src**: 切换到 src=5（远线模式）
- **线丢失**: lost=1 阶段后期开始丢线
- **控制**: duty 始终左偏（左电机24-27，右电机-9~-8），硬左转
- **过渡条件**: `ATGCircleCal: IN→RUNNING reason=gyro heading_deg10=607 dist=649`

## ④ RUNNING 阶段（frame 306-431，共126帧）

```
首(306):  near=0/65   guide=+35.00  yaw=-2800  duty=23/-7  src=11  入RUNNING(heading=607°)
末(431):  near=0/0    guide=+35.00  yaw=-2800  duty=19/0   src=4   出RUNNING
```

- **guide 全程不变**: +35.00 饱和，无下降趋势
- **yaw 全程不变**: -2800 饱和
- **远线**: far=0/0 全程无
- **近线**: 首帧 left=0, right=65；末帧 left=0, right=0（线全丢）
- **src**: src=11→src=4，说明从普通巡线切换到无有效线
- **lost**: 全程 lost=1，持续丢线状态
- **过渡条件**: `ATGCircleCal: RUNNING→OUT reason=gyro heading_deg10=2014 dist=1514`

## ⑤ OUT 阶段（frame 432-465，共34帧）

```
首(432):  near=0/0    guide=+49.82(饱和!)  yaw=-3986(饱和!)  duty=29/-12  src=6  入OUT
末(465):  near=3/0    guide=+49.82(饱和!)  yaw=-3986(饱和!)  duty=27/-9   src=6  出OUT
```

- **guide/yaw 全程饱和**: guide=+49.82, yaw=-3986，全程不变
- **远线**: far=0/0 全程无，far_l=0@-1
- **近线**: 全程 near=0/0 或 near=3/0，基本无线
- **src**: src=6（固定线模式未激活）
- **控制**: duty 极端左偏（29/-12→27/-9），极强左转
- **过渡条件**: `ATGCircleCal: OUT→END reason=gyro heading_deg10=2677 dist=385`

## ⑥ END 阶段（关键！）（frame 466-694，共229帧）

```
首(466):  near=1/0    src=14  guide=+6.82  yaw=-545  duty=7/16   conf=0.0/0.0  固定线打出来
中(580):  near=0/0    src=14  guide=+6.82  yaw=-545  duty=10/10  conf=0.0/0.0  无线，固定线撑着
末(694):  near=0/1    src=14  guide=+6.82  yaw=-545  duty=12/8   conf=0.0/0.0  ← vision_lpt_exit heading=3070° dist=2668
```

- **src=14 固定线**: ✅ 帧466入END立刻打出，持续229帧全程
- **guide 方向**: ✅ +6.82，正且温和
- **远线**: far=0/0 全程无
- **近线**: 入END时 left=1, right=0；全程 near 基本为0/0，偶有0/1
- **conf**: 置信度全程 0.0/0.0/0.0/0.0 — 无任何有效视觉线
- **固定线持续作用**: 229帧，duty 从7/16逐渐变到12/8
- **vision_lpt_exit**: heading=3070° dist=2668

## ⑦ END→CIRCLE_NONE

```
END末(f694):        guide=+6.82  yaw=-545  duty=12/8   src=14 ✅ 固定线撑着 heading=3070°
CIRCLE_NONE(f700):  guide=0.00   yaw=0     duty=0/0    road=0   ❌ 停车！
CIRCLE_NONE(f710):  guide=6.36   yaw=-508  duty=18/8   road=2   ✅ 恢复巡线
```

- **出环瞬间（f700）**: guide=0.00, duty=0/0, road=0 — 完全停车！
- **但10帧后（f710）**: guide=6.36, duty=18/8 — 自行恢复了普通巡线
- **对比之前测试**: drive59/60/61 出环后 guide 翻负→撞路肩，本次虽然停车但没翻负
- **结论**: 停了一下但没出界，比之前有改善但仍不理想（理想是平滑过渡到普通巡线）

## ⑧ 各检查点结论表

```text
┌─────────────────────────────┬───────────────────┬──────────────────────────────┐
│          检查项             │       结果        │            说明              │
├─────────────────────────────┼───────────────────┼──────────────────────────────┤
│ 右侧直线远线可识别？        │ ❌ far=0/0 全程   │ 整个左环无远线               │
│ 固定线(src=14)打出来？      │ ✅ 帧466-694      │ 时机正确，入END立刻打出      │
│ 固定线 guide 方向？         │ ✅ +6.82          │ 正且温和                     │
│ 入口锚点 Lpt id？           │ ⚠️ id=33(偏大)   │ 远处触发BEGIN                │
│ ray hit 命中？              │ ✅ hit=1@34,16    │ 正确                         │
│ 各阶段 guide 变化？         │ ❌ 全部饱和      │ IN/RUNNING/OUT guide全程不变 │
│ BEGIN→IN 触发原因？         │ entry_distance   │ heading=23°, dist=2004       │
│ IN→RUNNING 触发原因？       │ gyro             │ heading=607°                 │
│ RUNNING→OUT 触发原因？      │ gyro             │ heading=2014°                │
│ OUT→END 触发原因？          │ gyro             │ heading=2677°                │
│ END→CIRCLE_NONE 衔接？      │ ⚠️ 停车10帧后恢复│ duty=0/0 停了但自行恢复      │
│ 对比 exit heading           │ 3070°            │ 2680°→2692°→3121°→3070°→??? │
│ 总体判定                    │ ❌ 失败          │ 全程饱和+出环停车            │
└─────────────────────────────┴───────────────────┴──────────────────────────────┘
```

## 核心问题总结

1. **IN/RUNNING/OUT 全程 guide/yaw 饱和**: guide=+37.36→+35.00→+49.82 全部是饱和值，无任何视觉反馈参与控制。说明圆环内视觉完全失效（无线可巡）

2. **远线全程 0**: 左环全程无远线，这可能是原因之一——没有远线引导导致 inside 圆环视觉全盲

3. **出环停车（f700）**: END→CIRCLE_NONE 时 duty=0/0 停了10帧，虽然自行恢复但说明过渡逻辑在无线场景下有问题

4. **vs drive59(2680°)/60(2692°)/61(3121°)**: 本次 heading=3070°，出口位置与其他次不同，但每次都会在出环处有问题
