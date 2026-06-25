# Claude Review Prompt

Copy this prompt to Claude when asking for architecture review.

```text
请只做架构审查，不改代码。仓库路径：
/mnt/e/longxin/ls2k0300_library/ls2k300_library/seekfree_ls2k0300_opensource_library/test_project/front_car_mainline

请阅读：
.trellis/tasks/06-06-align-midline-pipeline-to-autop/research/claude-review-flowchart.md
.trellis/tasks/06-06-align-midline-pipeline-to-autop/research/claude-review-resolution.md
.trellis/tasks/06-06-align-midline-pipeline-to-autop/research/all-stage-refactor-plan.md
.trellis/tasks/06-06-align-midline-pipeline-to-autop/research/non-reference-retention-plan.md
.trellis/tasks/06-06-align-midline-pipeline-to-autop/research/naming-and-file-boundary-plan.md

然后对 Stage 1 方案做审查：
1. 判断 `rpts0s/rpts1s -> rptsc0/rptsc1 -> selected rpts/rpts_num -> build_rptsn() -> rt->track.mid` 这条合同是否完整。
2. 检查是否有遗漏的调用点：track_leftline/rightline、track_leftline_from_start/rightline_from_start、build_zebra_mid、solve_cross_mid、普通/ring/cross 分支。
3. 检查是否破坏当前已推送的非参考修复：单侧 seed 补搜、trace 后 update_search_center/width_base、元素短线门、ring 帧首 action、assistant 红线。
4. 检查 Stage 1 是否不该触碰的东西：seed、ring 状态转移、cross farline detection、control/PID、assistant 协议、文件改名。
5. 输出结论：通过 / 不通过；如果不通过，按阻塞级别列出必须修改的方案点，并给出对应代码位置。

注意：不要实现，不要修改源码，只审查方案和风险。
```
