# 📐 圆环 Log 分析指引（强制格式）

> **⚠️ 重要：所有圆环测试 log 分析必须严格按照以下 8 段格式输出。**
> 不允许省略任何一段，不允许改变顺序，不允许用其他格式替代。

---

## 强制分析模板

每次分析 log 必须严格按照以下 8 段格式：

### ① 入口防误判（ray hit） ✅/❌
```
seed=xx,yy  hit=1@xx,yy  ray=-1,-1  命中内圆边界
锚点 Lpt0 id=xx（正常/异常，id<35）
```
- 记录 seed 坐标、hit 命中位置、ray 方向
- 判断 Lpt id 是否在合理范围

### ② BEGIN 阶段（多帧详细）
```
帧    near      lpt锚点  guide   yaw    duty    说明
1     xx/xx   id=xx   +x.xx  -xxx   xx/xx   入BEGIN
10    xx/xx   id=xx   +x.xx  -xxx   xx/xx   ...
...
末    xx/xx   id=xx   +x.xx  -xxx   xx/xx   BEGIN末
```
- 取 >3 个代表性的帧展示趋势
- 必须标注：远线 far=0/0 有无、近线左右值、Lpt id 变化
- 必须标注 `src=` 源线类型

### ③ IN 阶段
```
首:  near=x/x   guide=+xx.xx(饱和!)  yaw=-xxxx  duty=xx/-xx  入IN
末:  near=x/x   guide=+xx.xx          yaw=-xxxx  duty=xx/-xx  出IN
```
- 必须标注 guide/yaw 是否饱和
- 必须说明远线有无、线是否全丢

### ④ RUNNING 阶段
```
首:  near=x/x   guide=+xx.xx  yaw=-xxxx  duty=xx/-xx  入RUNNING (heading=xxxx°)
末:  near=x/x   guide=+xx.xx  yaw=-xxxx  duty=xx/xx   出RUNNING
```
- 必须标注 guide 变化趋势（下降/不变/上升）
- 必须标注远线全程有无

### ⑤ OUT 阶段
```
首:  near=x/x   guide=+xx.xx(饱和!)  yaw=-xxxx(饱和!)  duty=xx/-xx  入OUT
末:  near=x/x   guide=+xx.xx          yaw=-xxxx          duty=xx/-xx   出OUT
```
- 必须标注 guide/yaw 是否饱和
- 必须标注远线全程有无、far_l 值

### ⑥ END 阶段（关键！）
```
首:  near=x/x   src=14  guide=+x.xx  yaw=-xxx  duty=xx/xx   conf=x
末:  near=x/x   src=14  guide=+x.xx  yaw=-xxx  duty=xx/xx   ← vision_lpt_exit heading=xxxx°
```
- 必须确认 src=14 固定线打出来 ✅ 时机
- 必须标注 guide 方向是否正确且温和
- 必须标注远线全程有无
- 必须记录 vision_lpt_exit 时的 heading 和 dist

### ⑦ END→CIRCLE_NONE
```
END末:          guide=+x.xx  ✅/❌ src=14固定线
CIRCLE_NONE:    guide=x.xx  duty=x/x  road=x  状态描述
```
- 必须对比 END 末和 CIRCLE_NONE 首帧的 guide 变化
- 必须标注 duty 是否停车、road 状态
- 必须判断出弯是否正常（guide 是否翻负/停车/正常）

### ⑧ 各检查点结论表

```text
┌────────────────────────┬──────────────────┬──────────────────────────┐
│         检查项         │       结果       │          说明            │
├────────────────────────┼──────────────────┼──────────────────────────┤
│ 右侧直线远线可识别？   │ ✅/❌            │ 说明                     │
│ 固定线(src=14)打出来？ │ ✅/❌ 帧范围     │ 时机是否正确             │
│ 固定线 guide 方向？    │ ✅/❌ +x.xx      │ 是否正且温和             │
│ 入口锚点 Lpt id？      │ ✅/⚠️/❌ id=xx   │ 是否正常范围内           │
│ ray hit 命中？         │ ✅/❌ hit=1@xx   │ 是否正确                 │
│ 各阶段 guide 变化？    │ 描述             │ 是否正常趋势             │
│ END→CIRCLE_NONE 衔接？ │ ✅/❌ 描述       │ 是否正常过渡             │
│ 对比 exit heading      │ xxxx°            │ 多次测试的对比           │
└────────────────────────┴──────────────────┴──────────────────────────┘
```

---

## 其他测试指引（Joshua 入口判据）

### 改动概要
对齐 Joshua(Enterprise_E)的 7/9 圆环入口判据,从单一判据升级到 **7 条件 AND 门**:
- **5 个静态条件**:对侧长≥80、近线长≥35、双边存在(各≥10)、Lpt id∈[10,35)、对侧直道
- **2 个时序条件**(关键):对侧单调性(反弹≤1)、内侧连续性(间距≤15)

**核心目标:挡住 drive28 类假开口(普通弯道),保留真入口(drive24/26/27/30/32/34)**

---

## 测试方法

### 第1步:启用详细 log
在车载端设置环境变量(启动前):
```bash
export FRONT_CAR_CIRCLE_CAL_LOG=1
```
或在 systemd service 文件中加入:
```ini
Environment="FRONT_CAR_CIRCLE_CAL_LOG=1"
```

### 第2步:跑测试场景
重点测试 2 类场景:
1. **假开口**(普通弯道,之前误入):drive28 类似场景,注意车道开口处
2. **真入口**(已知能进):drive24/26/27/30/32/34 类似场景,验证不被误拒

### 第3步:看 log 判断结果

#### 情况A:假开口被正确拒绝(期望)
**日志特征:**
```
ATGCircleEntryReject: side=L base=1 opp_long=1(124>80) near=1(64>50) both=1(...) 
  lpt_id=1(33∈[10,35)) mono=0(bounce=2≤1) cont=1(gap=120≤15²)
                        ^^^^^^^^^^^^^^^^^^^^^^
```
- **看哪个条件=0**:上例 `mono=0` 说明对侧角点反弹 2 次(>1 阈值)→ 被单调性挡住 ✅
- **其他可能**:`cont=0` 内侧边线断点过大 ✅

**验证通过标准:**
- drive28 类假开口打 `ATGCircleEntryReject` log
- `mono=0` 或 `cont=0`(至少一个时序条件失败)
- 车辆不进 `CIRCLE_LEFT_BEGIN` 状态,继续普通巡线

#### 情况B:真入口被误拒(需调参)
**日志特征:**
```
ATGCircleEntryReject: side=L base=1 opp_long=1(124>80) near=0(38>35) both=1(...) 
  lpt_id=1(21∈[10,35)) mono=1(bounce=0≤1) cont=1(gap=80≤15²)
                        ^^^^^^^^^^^
```
- **看哪个条件=0**:上例 `near=0` 说明近线 38 点刚好低于阈值 35 → 被近线长挡住 ❌

**调参建议:**
| 失败条件 | 当前值 | 调整方向 | 风险 |
|---|---|---|---|
| `opp_long=0` | 80 | 放宽→70 | 可能让假开口也满足(慎重) |
| `near=0` | 35 | 放宽→30 | drive34 near=39 有 4 点容错,可放宽 |
| `both=0` | 10 | 放宽→5 | 双边存在是基础,不建议低于 5 |
| `lpt_id=0` | id∈[10,35) | 放宽下界→5 或上界→40 | id<10 太近会误触,id≥35 太远已放宽过 |
| `mono=0` | bounce≤1 | 放宽→2 | 真入口角点应单调,慎重放宽 |
| `cont=0` | gap≤15(225²) | 放宽→20(400²) | 真入口边线应连续,可适当放宽 |

**调参位置:**
```c
// atg_reference/Project/CODE/circle.c, 约 line 34-40
CIRCLE_ENTRY_OPPOSITE_MIN_POINTS = 80    // 对侧长
CIRCLE_ENTRY_NEAR_MIN_POINTS = 35        // 近线长
CIRCLE_ENTRY_BOTH_MIN_POINTS = 10        // 双边最少点
CIRCLE_ENTRY_LPT_MIN_ID = 10             // Lpt id 下界
CIRCLE_ENTRY_MONOTONICITY_MAX_BOUNCE = 1 // 反弹次数
CIRCLE_ENTRY_CONTINUITY_MAX_GAP = 15     // 间距阈值
```

#### 情况C:假开口静态条件就不满足(也是期望)
**日志特征:**
```
ATGCircleEntryReject: side=L base=1 opp_long=0(65>80) near=1(55>35) both=1(...) 
  lpt_id=1(28∈[10,35)) mono=1(bounce=0≤1) cont=1(gap=100≤15²)
```
- `opp_long=0`:对侧线 65 点 < 80 阈值 → 被对侧长挡住 ✅
- **验证通过**:静态条件就能挡住,时序判据是二次保险

---

## 常见问题排查

### Q1: 没有看到 ATGCircleEntryReject log
**原因:**
1. 环境变量 `FRONT_CAR_CIRCLE_CAL_LOG=1` 没生效 → 重启进程,确认环境变量
2. entry base 条件(单 Lpt + 对侧直道)不满足 → 还没到 Joshua 判据,正常

**诊断方法:**
看是否有 `ATGCircleBeginDiag` log(BEGIN 后每帧都打),如果有说明已进 BEGIN,反推 entry 曾满足。

### Q2: drive28 假开口仍进 BEGIN
**排查步骤:**
1. 看是否有 `ATGCircleEntryReject` log → 没有=Joshua 判据全过了(不符预期)
2. 看 log 中各条件实际值 → 对比阈值,找出哪个阈值太松
3. **重点看 `mono` 和 `cont`**(时序判据):
   - `mono=1(bounce=0)` = 假开口角点居然单调了?不太可能,**检查 Lpt id 历史是否正确记录**
   - `cont=1(gap=80)` = 假开口边线居然连续?可能 `MAX_GAP=15` 太松 → 收紧到 10

### Q3: 真入口全部被拒
**可能原因:**
- 时序判据太严(mono/cont 阈值过小)
- 静态判据过严(near/opp 阈值过大)

**诊断方法:**
看多个真入口的 `ATGCircleEntryReject` log,找出**共同失败的条件**(如都是 `near=0`)→ 放宽该阈值。

---

## 预期测试结果

### ✅ 成功标准
- drive28 类假开口被 `ATGCircleEntryReject` 拒绝(`mono=0` 或 `cont=0`)
- drive24/26/27/30/32/34 类真入口正常进 `CIRCLE_LEFT_BEGIN`(无 Reject log 或 Reject 后再次投票成功)
- 完整跑圆环无 stall/误出环

### ⚠️ 需调参
- 真入口被 Reject → 看 log 放宽对应阈值
- 假开口漏进 → 看 log 哪个条件全=1,收紧该阈值(优先收紧时序判据)

### ❌ 失败需回退
- 所有真入口都被拒,放宽后仍拒 → 可能 Joshua 判据不适配当前赛道,回退到上一版本

---

## 联系与反馈
测试完成后反馈:
1. **假开口拒绝情况**:drive28 类场景是否被挡?哪个条件卡住的(`mono`/`cont`/其他)?
2. **真入口通过率**:drive24-34 类场景通过率,被拒的场景看哪个条件=0?
3. **调参记录**:调了哪个阈值(从X→Y),效果如何?
4. **完整日志**:上传包含 `ATGCircleEntryReject` 的完整日志文件

## 附录：完整分析示例

参见本目录下 `circle-log-analysis-example.md` 中的 drive62 完整分析示例。
