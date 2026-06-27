# 圆环优先执行顺序

## 目标

把 `run_atg_elements()` 改成固定顺序：

1. 圆环已经激活时，本帧只跑圆环。
2. 圆环未激活时，先检查圆环入口。
3. 圆环本帧没有进入 ENTRY，才检查 Half。
4. Half 没有提交，再检查其他元素。

第一版不做“圆环退回 NONE 后同帧补跑 Half”。圆环退回后，下一帧再按正常顺序重新判断。

## 4 个问题和修法

1. `circle_entry_ever_valid_B` 一帧没看到 B 就被清零。
   修法：它在 ENTRY 生命周期内保持粘滞；只有进入 ENTRY、退出 ENTRY、ENTRY 中止、外部重置时清零。

2. A-only pending 会挡住 Half。
   修法：`check_circle()` 只有真正进入 ENTRY 才占本帧；单纯 A/basic 候选不能阻止 `check_Half()`。

3. `far_Lpt0_found/far_Lpt1_found` 可能是上一帧留下来的。
   修法：每帧元素处理前清掉 far 输出，或给 far 输出记录帧号；所有使用 far 的地方必须确认它来自本帧。

4. `cross_farline_L/R()` 一边检查远线，一边改全局线数据。
   修法：拆成“检查”和“提交”两步。检查只写局部结果；只有 Half 确认后，提交步骤才写全局 far 线、`cross_type` 和近线截断。

## `run_atg_elements()` 目标顺序

```text
if circle_type != CIRCLE_NONE:
    run_circle()
    return

check_circle()
if circle_type != CIRCLE_NONE:
    return

check_Half()
if cross_type == CROSS_HALF:
    return

check_cross_and_other_elements()
```

## `ever_valid_B` 生命周期

```text
enter_ENTRY:
    ever_valid_B = 0
    B_ready_streak = 0

run_ENTRY:
    if b_ret == 1:
        ever_valid_B = 1
        update B_ready_streak
    else if b_ret == 0:
        B_ready_streak = 0
        keep ever_valid_B
    else:
        abort ENTRY
        ever_valid_B = 0

ENTRY -> BEGIN:
    ever_valid_B = 0

ENTRY -> NONE:
    ever_valid_B = 0
```

## 验收清单

* [ ] `circle_type != CIRCLE_NONE` 时，`run_atg_elements()` 只跑 `run_circle()` 并返回。
* [ ] `circle_type == CIRCLE_NONE` 时，先跑 `check_circle()`。
* [ ] `check_circle()` 进入 ENTRY 后，本帧不再跑 Half。
* [ ] 只有圆环本帧没有进入 ENTRY，才跑 `check_Half()`。
* [ ] 圆环 ENTRY 中止到 NONE 后，第一版不做同帧 Half fallback。
* [ ] `ever_valid_B` 不会因为单帧 `b_ret == 0` 清零。
* [ ] `far_Lpt0_found/far_Lpt1_found` 不会跨帧误用。
* [ ] Half 的远线检查在确认前不写全局 far 线、不截断近线、不改 `cross_type`。
* [ ] BEGIN 只在 `C_valid && C_join_ok` 时设置 `CIRCLE_REF_IN_C`。
* [ ] `git diff --check`、`bash code/test.sh --host`、`bash code/test.sh` 通过；跑不了或失败时记录原因。
