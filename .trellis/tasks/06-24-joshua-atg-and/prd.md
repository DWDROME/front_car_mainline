# Joshua 入口判据对齐(保留 ATG 阈值 + 叠加多条件 AND)

## 背景
drive28 假入口暴露 ATG 单一判据(`Lpt0_found && !Lpt1_found && is_straight1 && id<35`)太弱,普通弯道开口轻松满足。当前 anti-flicker(`have>=2 && begin_dist<350`)已被证明会误杀真入口(真入口也可能有 2 次短暂丢线)。

Joshua(Enterprise_E)的圆环入口用 **9 条件 AND 门 + 丢线范围 [10,50] + 角点位置校验**,稳健识别真入口并拒绝假开口。

## 目标
**保留 ATG 现有阈值**(id<35/vote=2/is_straight),**叠加 Joshua 的额外判据作为 AND 门**,挡住 drive28 假开口且不破坏 drive24/26/27/30 远点真入口。

## 改动

### 1. check_circle() 加 Joshua 的 4 个额外 AND 条件

保留 ATG base 判据(`Lpt0_found && !Lpt1_found && is_straight1 && id<35`),新增 Joshua 映射的 4 条件:

```c
// atg_reference/Project/CODE/circle.c, check_circle() 约 line 208

// ATG base 判据(保持不变)
const int left_entry_base = Lpt0_found && !Lpt1_found && is_straight1 && Lpt0_rpts0s_id < 35;

// Joshua 额外判据 1: 对侧(右)直道足够长(对应 Joshua Right_Lost_Time<=10)
const int left_entry_opposite_long = rpts1s_num > 80;

// Joshua 额外判据 2: 近线(左)足够长,视野到近处(对应 Joshua Boundry_Start>=H-20)
const int left_entry_near_valid = rpts0s_num > 50;

// Joshua 额外判据 3: 双边丢线少(对应 Joshua Both_Lost_Time<=10)
const int left_entry_both_exist = (rpts0s_num > 10 && rpts1s_num > 10);

// Joshua 额外判据 4: entry Lpt id 下界(不能太近,对应 Joshua 角点 y>=30 靠下不贴底)
const int left_entry_lpt_reasonable = (Lpt0_rpts0s_id >= 10 && Lpt0_rpts0s_id < 35);

// 最终 = ATG base + Joshua 4 条件 AND
const int left_entry = left_entry_base && 
                       left_entry_opposite_long && 
                       left_entry_near_valid &&
                       left_entry_both_exist &&
                       left_entry_lpt_reasonable;

// 右环对称
const int right_entry_base = !Lpt0_found && Lpt1_found && is_straight0 && Lpt1_rpts1s_id < 35;
const int right_entry_opposite_long = rpts0s_num > 80;
const int right_entry_near_valid = rpts1s_num > 50;
const int right_entry_both_exist = (rpts0s_num > 10 && rpts1s_num > 10);
const int right_entry_lpt_reasonable = (Lpt1_rpts1s_id >= 10 && Lpt1_rpts1s_id < 35);
const int right_entry = right_entry_base &&
                        right_entry_opposite_long &&
                        right_entry_near_valid &&
                        right_entry_both_exist &&
                        right_entry_lpt_reasonable;
```

阈值常量新增(enum 中):
```c
// 对齐 Joshua 的边线长度/双边存在判据
CIRCLE_ENTRY_OPPOSITE_MIN_POINTS = 80,   // 对侧直道最短长度
CIRCLE_ENTRY_NEAR_MIN_POINTS = 50,       // 近线最短长度(视野到近处)
CIRCLE_ENTRY_BOTH_MIN_POINTS = 10,       // 双边最少点数(双边都存在)
CIRCLE_ENTRY_LPT_MIN_ID = 10,            // entry Lpt id 下界(不能太近)
```

### 2. revoke_idle_circle_begin() 改用丢线窗口判据

删除现有的 `have>=2 && begin_dist<350` flicker 撤回,改为**丢线帧数窗口**(对齐 Joshua `Left_Lost_Time ∈ [10,50]`):

```c
// atg_reference/port/reference_step.c

// 新增全局:BEGIN 后累计帧数
static int g_circle_begin_frames;

// 在 update_distance_counters() 中 BEGIN 时递增:
if(circle_type == CIRCLE_LEFT_BEGIN || circle_type == CIRCLE_RIGHT_BEGIN) {
    g_circle_begin_frames++;
}
else {
    g_circle_begin_frames = 0;
}

// revoke_idle_circle_begin() 中删除 have>=2 分支,改为:
if(circle_type == CIRCLE_LEFT_BEGIN && 
   g_circle_begin_frames >= 30 &&
   (none_left_line < 3 || none_left_line > 15)) {
    reset_circle_to_none("LEFT_BEGIN lost-line count out of [3,15] window,");
}
else if(circle_type == CIRCLE_RIGHT_BEGIN &&
        g_circle_begin_frames >= 30 &&
        (none_right_line < 3 || none_right_line > 15)) {
    reset_circle_to_none("RIGHT_BEGIN lost-line count out of [3,15] window,");
}
// 保留原有的 none==0 && begin_dist>6000 idle 撤回
```

enum 新增:
```c
ATG_CIRCLE_BEGIN_MIN_FRAMES = 30,        // 累计此帧数后开始检查丢线窗口
ATG_CIRCLE_BEGIN_MIN_LOST_FRAMES = 3,   // 丢线帧数下界(太少=直道误判)
ATG_CIRCLE_BEGIN_MAX_LOST_FRAMES = 15,  // 丢线帧数上界(太多=反复塌缩假开口)
// 删除 ATG_CIRCLE_BEGIN_FLICKER_MAX_DIST_COUNTS
```

### 3. circle.c 保留 collapsed 标志但删除其使用

`circle_left/right_begin_collapsed` 和 `have_left/right_line` 计数逻辑**全部删除**(run_circle LEFT/RIGHT_BEGIN 恢复到原始丢线-only 语义),因为 have>=2 判据已被证伪。`reset_circle_begin_flags()` 也清理掉 collapsed 标志。

## 验证
1. `git diff --check`
2. `bash code/test.sh --host`(gcc 编译)
3. `bash code/test.sh`(mips cross 编译)
4. 下一趟 live:
   - drive28 类似弯道开口是否被 Joshua 4 条件挡住(预期:对侧右线或近线不满足 → entry=0)
   - drive24/26/27/30 真入口是否仍能触发(预期:远点 Lpt id 可能 >10 但其他条件满足 → entry=1)
   - BEGIN 后 30 帧内如果 none 出窗口 [3,15] 是否撤回

## 非目标
- 不动 `CIRCLE_HEADING_READY_OUT_TO_END_DEG10`(保持 2660)
- 不动 guide_error/target_yaw 控制链
- 不做 Joshua 的原图逐行数组 `Left_Line[H]`/角点精确 (x,y) 校验(工作量大,阈值标定先观察)
