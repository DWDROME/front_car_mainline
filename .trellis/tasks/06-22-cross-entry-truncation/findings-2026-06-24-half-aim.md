# 十字斜入 — HALF aim 对称化结论 (2026-06-24)

> 归档 2026-06-24 会话的十字工作：三套对比（ATG/我们/Joshua）找不对称 → 对症改 → 待 live。
> 改动在工作区未提交，host + cross build 过。

## 痛点
斜入十字（车身歪着进），要顺左/右通路过去，靠「截断中线」功能。**左侧通路（aim 0.25）爱抖/过冲**（用户实测左侧更糟）。

## 三套范式对比
- 我们/ATG：双 Lpt 角点判十字（`check_cross`）+ `cross_farline` 远线 + Lpt 截断；rpts 点集 + IPM
- Joshua：角点撕裂（边线作差）+ 单调突变点 + 斜率/半边补线；原图逐行
- 结论：范式差异同圆环，完善走对症修（rpts/Lpt/IPM），不照搬 Joshua 原图法

## 病根
`CROSS_HALF` 前瞻 `aim_distance` 左 `0.25` / 右 `0.75`（`cross.c:125` / `cross.c:144`），**左右前瞻差 3 倍**。`aim_distance` 是前瞻距离（`normalize_selected_line` 里 `aim_idx = aim/sample_dist`）。斜入左右通路是镜像，前瞻本应一致。用户确认**忘了为何 0.25/0.75** → 非有物理依据的有意值。

## 改动
`cross.c:125` 左半十字 `aim_distance 0.25→0.75`（对齐右半工作值；右半未抱怨=工作，不动右侧无风险）。host + cross build 过。

## 待 live 验证
斜入往左通路抖/过冲是否消失、左右是否对齐。若左切弯则回调 `0.5~0.75`。

## 后续（这刀不够时，按可能性）
1. **截断点**：斜入两侧角点 id 不对称，`BEGIN` Lpt 截断 / `truncate_cross_half_candidate_near_lines` 可能让中线偏
2. `Half_check` 单侧判定阈值（斜入丢线进 HALF 的条件）
3. `check_cross` 极简（双 Lpt 即十字）误判防护
4. Joshua 四角点补线后半（`.reference/joshua-xu-smartcar/05-straight-curve-cross.md:424-810`，未读全）

## 测试数据
- `logs/live-cross/20260622-drive02/03/04/06-*.log`（这几次主要测圆环，十字 HALF aim 改动尚未专门 live）
