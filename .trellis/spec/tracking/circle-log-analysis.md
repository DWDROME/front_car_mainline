# 圆环 Log 分析强制格式

> **适用场景**：用户要求分析圆环（左环/右环）测试 log 时。
> **所有模型（主模型、trellis-check、trellis-implement）只要涉及圆环 log 分析，均须遵守此格式。**

---

## 强制 8 段格式

以下 8 段必须全部输出，顺序不可改变，不可省略。

### ① 入口防误判（ray hit）

记录 seed、hit 坐标、ray 方向、锚点 Lpt0 id。

格式：
```
seed=xx,yy  hit=1@xx,yy  ray=-1,-1  命中内圆边界
锚点 Lpt0 id=xx（正常/异常，id<35）
```

### ② BEGIN 阶段（多帧详细）

取 ≥3 帧展示趋势（首帧 + 中间趋势 + 末帧）。标注远线有无、近线左右值、Lpt id 变化、src 源线类型。

格式：
```
帧    near      lpt锚点  guide   yaw    duty    src  说明
1     xx/xx   id=xx   +x.xx  -xxx   xx/xx   xx   入BEGIN
...
末    xx/xx   id=xx   +x.xx  -xxx   xx/xx   xx   BEGIN末
```

### ③ IN 阶段

```
首:  near=x/x   guide=+xx.xx(饱和?)  yaw=-xxxx  duty=xx/-xx  src=x
末:  near=x/x   guide=+xx.xx          yaw=-xxxx  duty=xx/-xx  src=x
```

必须标注：
- guide/yaw 是否饱和
- 远线有无
- 线是否全丢

### ④ RUNNING 阶段

```
首:  near=x/x   guide=+xx.xx  yaw=-xxxx  duty=xx/-xx  (heading=xxxx°)
末:  near=x/x   guide=+xx.xx  yaw=-xxxx  duty=xx/xx
```

必须标注：
- guide 变化趋势（下降/不变/上升）
- 远线全程有无

### ⑤ OUT 阶段

```
首:  near=x/x   guide=+xx.xx(饱和?)  yaw=-xxxx(饱和?)  duty=xx/-xx
末:  near=x/x   guide=+xx.xx          yaw=-xxxx          duty=xx/-xx
```

必须标注：
- guide/yaw 是否饱和
- 远线全程有无、far_l

### ⑥ END 阶段（关键！）

```
首:  near=x/x   src=14  guide=+x.xx  yaw=-xxx  duty=xx/xx
末:  near=x/x   src=14  guide=+x.xx  yaw=-xxx  duty=xx/xx  ← vision_lpt_exit heading=xxxx° dist=xxxx
```

必须确认：
- src=14 固定线是否打出、时机
- guide 方向是否正确且温和
- vision_lpt_exit 时的 heading 和 dist

### ⑦ END→CIRCLE_NONE

对比 END 末帧和 CIRCLE_NONE 首帧：

```
END末:          guide=+x.xx  duty=x/x  src=14
CIRCLE_NONE:    guide=x.xx   duty=x/x  road=x
```

必须判断：
- guide 有无跳变（翻负/归零/保持）
- duty 是否停车
- road 状态
- 是否正常过渡

### ⑧ 各检查点结论表

标准表格，至少覆盖以下检查项：

| 检查项 | 结果 | 说明 |
|--------|------|------|
| 右侧直线远线可识别？ | ✅/❌ | 全程远线值 |
| 固定线(src=14)打出来？ | ✅/❌ 帧范围 | 时机是否正确 |
| 固定线 guide 方向？ | ✅/❌ +x.xx | 正且温和？ |
| 入口锚点 Lpt id？ | ✅/⚠️/❌ id=xx | 正常范围？ |
| ray hit 命中？ | ✅/❌ hit=1@xx | 正确命中？ |
| 各阶段 guide 变化？ | 描述 | 正常趋势？ |
| END→CIRCLE_NONE 衔接？ | ✅/⚠️/❌ | 过渡是否平滑 |
| 对比 exit heading | xxxx° | 与之前测试对比 |
| 总体判定 | ✅/⚠️/❌ | 本次测试结论 |
