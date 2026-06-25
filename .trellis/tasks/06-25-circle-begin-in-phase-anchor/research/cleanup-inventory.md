# circle.c 零行为清理清单（删除/保留）

> 每项附证据。🗑️=纯垃圾零行为删 / 🏷️=假名正名 / 🧹=无消费写删 / 📊=日志证明的死保险 / 🔒=保留。
> 证据来源：全库 `rg` 引用审计 + 45 条 live 日志 reason 分布 + 当前控制链(control.cpp/runners.cpp/atg_reference_mainline.cpp)消费检查。

## 日志 reason 分布（证哪些触发是死的）

```
26 NONE→LEFT_BEGIN      entry_vote
24 LEFT_OUT→LEFT_END    gyro          | distance(4500)  0次
24 LEFT_IN→LEFT_RUNNING gyro          | distance(2000)  1次
24 LEFT_BEGIN→LEFT_IN   entry_distance(旧日志,现为mouth_loss) | entry_gyro 1次
22 LEFT_RUNNING→LEFT_OUT gyro + 2 vision_lpt | distance(16000) 0次
18 LEFT_END→NONE        vision_lpt_exit | distance(7500) 1次
```
结论：每个转换主触发都是 **gyro/vision 一条**；distance 兜底是陀螺失效保险，平时 0~1 次。

---

## 🗑️ 第1类 纯垃圾——零行为，证据确凿，建议直接删

| 项 | 证据 | 动作 |
|---|---|---|
| `CIRCLE_HEADING_FORCE_OUT_DEG10=2500` | 全库仅 circle.c:47 定义，**0 引用** | 删常量 |
| `circle_encoder` | 仅 circle.c:24 定义 + :530 赋值，**0 读取** | 删变量 + 删 :530 赋值 + `current_encoder` 局部 |
| 成段 legacy 注释块(约 5-7 处) | `/* legacy visual reappear gate */` 等死注释(349-357/391-398/418-427/457-461/552-553...) | 删注释 |
| `circle_in_length=60` | 仅出现在上述死注释里(391/392/552/553)，活代码无引用 | 随注释删 |

## 🏷️ 第2类 假名正名——零行为

| 项 | 证据 | 动作 |
|---|---|---|
| 日志名 `ATGCircleEntryBreakpoints` | 实为 inner-hit 像素扫描(从角点种子扫黑点)，非"双断点" | 改名 `ATGCircleEntryInnerHit`(两处输出点同步) |

## 🧹 第3类 无消费 flag——circle.c 内的写无意义（控制链 grep 全空）

> control.cpp / runners.cpp / atg_reference_mainline.cpp 对这些 flag **0 读取**；Cpu0_Main.c 不在 CMakeLists（不编译）。

| 项 | 证据 | 建议动作 | 需你定 |
|---|---|---|---|
| `if_clean_pid` | 控制链 0 读；circle.c/round.c 只写 | 删 circle.c 内的写 | 变量定义留(round 也写) |
| `broadcast_flag` | 当前 build 0 消费 | 删 circle.c:483 写 | 变量留 |
| `is_large_circle/is_small_circle` | 控制链 0 读；仅 report.cpp 打印 | 删 circle.c 判定赋值(380-384/541-545) | **诊断字段要不要一起删?** |

## 📊 第4类 日志证明的死/罕见保险——建议【保留】(不是垃圾,是陀螺失效兜底)

| 项 | 日志触发 | 建议 |
|---|---|---|
| RUNNING→OUT `distance 16000` | 0 次 | 🔒保留(陀螺失效唯一保险) |
| OUT→END `distance 4500` | 0 次 | 🔒保留 |
| IN→RUNNING `distance 2000` | 1 次 | 🔒保留 |
| END→NONE `distance 7500` | 1 次 | 🔒保留 |

> 删这些=成功case零行为,但陀螺一旦失效就裸奔。这才是你说的"踩坑换来的真兜底",建议留。可做的是**把它们注释成"陀螺失效保险"**,消除"窗口太多"错觉。

## 🔒 第5类 绝对保留

- END 满圈门 `heading>=355°`(drive59-62 踩坑)、`mouth_loss` begin_dist 锁位、`track_type` 选线主链、`point_Cal_Line_2` 静态补线、inner-hit 机制本身。
- `have_left_line/have_right_line` **变量**：round.c:30-34/85-103 真在用，**不能删变量**；circle.c 内冗余写(147/148/352/500/502/515/656)删属低风险(circle 判定不读它,但跨元素共享需确认 round 不依赖 circle 的清零)。

---

## ✅ 执行决策（用户确认 2026-06-25）

- **第1类 🗑️**：全删。
- **第2类 🏷️**：正名 `ATGCircleEntryBreakpoints` → `ATGCircleEntryInnerHit`。
- **第3类 🧹【彻底删,跨文件】**：`is_large_circle`/`is_small_circle`/`broadcast_flag`/`if_clean_pid` —— 变量定义、extern、reset、report.cpp 诊断字段、circle.c 赋值、round.c 内 `if_clean_pid` 写**全部删干净**。
  - ⚠️ circle.c:9 `int is_large_circle,is_small_circle,circle_count;` —— **`circle_count` 必须保留**(END `circle_count++`)，拆行只删两个 circle。
  - ⚠️ report.cpp 删字段时保持格式串与其余参数对齐。
- **第4类 📊【全删旧 distance 兜底——行为改动】**：删 IN→RUNNING(`CIRCLE_IN_DISTANCE_CONFIRM`)、RUNNING→OUT(`CIRCLE_RUNNING_FORCE_OUT_COUNTS`)、OUT→END(`4500`)、旧 END→NONE(`7500`/`4000`) 四类 `total_distence` 分支(左右环对称,共约8处)，常规推进只留 gyro/vision。删后无引用的常量(`CIRCLE_RUNNING_FORCE_OUT_COUNTS`/`CIRCLE_IN_DISTANCE_CONFIRM`/`circle_in_distance`)一并删。后续 END 单独补了 `heading>=3300 && END内total_distence>=8000` 的 `end_encoder_release` 防死锁出口；非 END 滞留仍由 `exit_circle_after_stall` 显式兜底。
- **第5类 🔒**：绝对不动——满圈门355°、mouth_loss、track_type、point_Cal_Line_2、inner-hit、`have_left/right_line` 变量(round.c 依赖,只删 circle.c 内冗余写)。

## 验证要求

- 每删一符号先 `rg` 全库确认引用点,逐一清理,不留悬空引用。
- `touch circle.c && bash code/test.sh` 交叉编译过 + `Building circle.c.o`/`Built target` 零错误。
- 成功 case 日志状态流仍一致(distance 平时不触发→删后正常流程不变)。
- **不 commit**(交 main session)。

## 预期效果

circle.c 大幅瘦身:去死常量+残留变量+5~7段死注释+无消费flag(跨文件)+旧 distance 兜底分支,假双断点正名。常规状态转换只剩 gyro/vision 主触发,骨架清晰。END 额外保留局部编码器防死锁出口,非 END 滞留由 stall reset 显式兜底。
