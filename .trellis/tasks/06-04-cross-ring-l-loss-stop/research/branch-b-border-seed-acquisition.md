# Branch B: Ordinary Border-Entry Seed Acquisition

## Scope

This note records the Branch B research for the observed case where a clear boundary enters from the image side border but the ordinary tracking pipeline does not acquire it. It is a mechanism note only. No source code change is proposed as final here.

## Smart Search Evidence

Commands run:

```bash
smart-search doctor --format json > .trellis/tasks/06-04-cross-ring-l-loss-stop/research/smart-search-doctor.json
smart-search deep "智能车巡线 图像边缘 入画 边界 丢线 seed 起线点 补线 处理方案" --format json > .trellis/tasks/06-04-cross-ring-l-loss-stop/research/branch-b-deep-plan.json
smart-search search "智能车 巡线 边界 从图像边缘进入 起线点 seed 补线 丢线" --validation balanced --extra-sources 3 --timeout 90 --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/branch-b-cn-search.json
smart-search search "line following robot boundary tracking seed point image border lane line enters from side edge" --validation balanced --extra-sources 3 --timeout 90 --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/branch-b-en-search.json
smart-search search "智能车 摄像头 八邻域 起点搜索 边线 从边缘进入 丢线 补线 十字 环岛" --validation balanced --extra-sources 5 --timeout 90 --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/branch-b-cn-search-2.json
smart-search fetch "https://patents.google.com/patent/CN114863387A/zh" --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/fetch-CN114863387A.json
smart-search fetch "https://www.cnblogs.com/zyly/p/19830032" --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/fetch-cnblogs-zyly-19830032.json
smart-search fetch "https://bbs.huaweicloud.com/blogs/320221" --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/fetch-huaweicloud-320221.json
smart-search fetch "https://bbs.huaweicloud.com/blogs/320229" --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/fetch-huaweicloud-320229.json
smart-search fetch "https://blog.csdn.net/Lovely_him/article/details/119255431" --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/fetch-csdn-Lovely_him-119255431.json
smart-search fetch "https://en.wikipedia.org/wiki/Boundary_tracing" --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/fetch-wikipedia-boundary-tracing.json
```

Blocked command:

```bash
smart-search zhipu-search "智能车 摄像头 八邻域 追线 起始点 边界 丢线 补线 十字 环岛" --count 8 --content-size high --format json --output .trellis/tasks/06-04-cross-ring-l-loss-stop/research/branch-b-zhipu-cn.json
```

Result: `ZHIPU_API_KEY` is not configured. This does not block the main `search/fetch` path, but it means no Zhipu Chinese-search reinforcement was available in this run.

## External Findings

### 1. Seed acquisition and boundary tracing are separate stages

Fetched Chinese smart-car sources consistently describe the pipeline as:

```text
binary image
-> scan for boundary / starting point
-> follow boundary with neighboring pixels or row scan
-> detect loss/corners/elements
-> repair line / compute midline
```

The patent source `CN114863387A` describes scanning from a near row and center column toward both sides, then using the found boundary as a seed to continue boundary extraction. It also explicitly treats missing one side as a later repair/midline problem, not as proof that the seed stage can be skipped.

The important implication for our bug: if the seed stage does not produce a current-frame seed, downstream single-side midline capability cannot help. It has no current boundary points to offset.

Sources:

* https://patents.google.com/patent/CN114863387A/zh
* https://www.cnblogs.com/zyly/p/19830032

### 2. Smart-car reports distinguish center scan, edge scan, and element-specific scan starts

The Huawei Cloud smart-car technical report describes three scan-start strategies:

* center scan: scan from previous/current center toward both sides;
* edge scan: scan from prior left/right boundary positions;
* element-specific scan starts: use known element state and feature geometry to choose scan starts.

This maps well to our decision boundary:

* current `find_seeds()` is a very narrow center-row start;
* `find_column_seed()` is an existing vertical column start, but not used for ordinary seeds;
* cross farline uses its own element-specific fixed-column seed logic.

Source:

* https://bbs.huaweicloud.com/blogs/320221

### 3. Border-entry failure is plausible at the seed layer

The CSDN source about smart-car image processing emphasizes that losing a near vertical edge can be serious because later scanning starts from near curve/boundary geometry. It also separates "find starting point" from "follow point" and "find left/right boundary".

This supports the user's video observation: a line can be visually clear, but if it does not intersect the narrow expected seed row/window, the ordinary trace never starts.

Source:

* https://blog.csdn.net/Lovely_him/article/details/119255431

### 4. General boundary tracing confirms that an initial boundary pixel matters

The general boundary tracing source is lower authority for smart-car specifics, but it confirms the algorithmic structure: boundary tracing starts after locating an initial boundary pixel, then follows neighboring boundary pixels. A side-border entrant is therefore not solved by the follower alone; it needs a usable initial pixel inside the valid image area.

Source:

* https://en.wikipedia.org/wiki/Boundary_tracing

## Local Code Mapping

### Ordinary seed acquisition

Current code:

* `code/tracking/imgproc.cpp:214-290`

Mechanism:

```text
center = rt->mid_position or MID_X
left_x0 = center - kSeedStartOffset
right_x0 = center + kSeedStartOffset
y = START_HIGH
find_left_edge(gray, y, left_x0)
find_right_edge(gray, y, right_x0)
```

Important constants:

* `code/tracking/imgproc.cpp:22`: `kSeedBorderMargin = 3`
* `code/tracking/imgproc.cpp:25`: `kSeedStartOffset = ROAD_HALF_WIDTH`
* `code/tracking/imgproc.cpp:26`: `kTraceMinVerticalGain = 8`
* `code/tracking/imgproc.cpp:27`: `kTraceBorderMargin = 2`
* `code/tuning.hpp:48`: `TRACE_MIN_STEP = 6`

Why this fails for a side-border entrant:

* It checks only one row.
* It starts from center offsets, not from side-border intersections.
* A line that begins at the left image border but does not cross `START_HIGH` within the expected search range can be completely missed.
* If no seed is produced, `trace_edges()` never gets a side to trace.

### Existing vertical seed helper

Current code:

* `code/tracking/imgproc.cpp:311-341`

Mechanism:

```text
scan upward on a fixed x
first see white
then see black
return the previous white point
```

This is conceptually close to the RT1064 cross farline fixed-column seed, but it is not currently wired into ordinary seed acquisition.

### Trace acceptance gate

Current code:

* `code/tracking/imgproc.cpp:475-513`

Mechanism:

```text
reject if seed is outside image
reject if seed is too close to image border
reject if seed pixel is dark
then trace by left-hand or right-hand rule
```

Implication:

* A naive patch that returns `(0, y)` or `(RAW_W - 1, y)` as a border seed will still be rejected.
* Any side-border supplement must return a seed at least inside `kTraceBorderMargin`, preferably also compatible with `kSeedBorderMargin`.

### Mainline consequence

Current code:

* `code/tracking/mainline.cpp:460-488`

Mechanism:

```text
find_seeds()
if no seed and not CROSS_IN -> TRACK_REJECT_NO_SEED
if seed exists but trace fails and not CROSS_IN -> reject
```

Implication:

* Branch B can explain a hard stop before or around an element without touching control code.
* It can also starve cross/ring corner detection because no ordinary trace means no near-line point list and no L corner.

## RT1064 Reference Mapping

Reference ordinary line extraction:

* `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/USER/src/main.c:532-545`

Mechanism:

```text
x1 = image_center - begin_x
y1 = begin_y
scan x1 left on the fixed y1 row
trace left-hand from the found point

x2 = image_center + begin_x
y2 = begin_y
scan x2 right on the fixed y2 row
trace right-hand from the found point
```

Reference cross farline extraction:

* `/mnt/e/longxin/RT1064_Code_ref/SJTU-AuTop-RT1064-Code/Project/CODE/cross.c:128-186`

Mechanism:

```text
fixed far_x1 / far_x2 columns
scan upward from begin_y
find white then black boundary
seed = (far_x, far_y + 1)
trace from that current-frame seed
```

Interpretation:

* Ordinary border-entry recovery is not a direct copied feature from RT1064 ordinary `process_image()`.
* But the vertical fixed-column search pattern is reference-aligned at the mechanism level because RT1064 cross farline already uses it.
* Therefore the closest reference-compatible Branch B idea is not "reuse stale trace"; it is "add a current-frame vertical seed supplement under strict conditions."

## Candidate Branch B Directions

### B1. Side-column seed supplement in `find_seeds()` recommended for discussion

Mechanism:

```text
run current fixed-row seed search first
if one side is missing or both sides missing under element-suspect geometry
    scan one or more inner columns near the missing image side
    produce a current-frame seed inside trace margins
    let existing `trace_single()` validate the seed
```

Why it fits:

* It targets the seed choke point directly.
* It does not reuse stale geometry.
* It keeps trace and midline safety gates unchanged.
* It reuses an existing idea already present in `find_column_seed()` and RT1064 cross farline.

Risks:

* If enabled too broadly, it can pick a side-border noise patch or element branch as a lane boundary.
* If the seed is too close to the border, `trace_single()` rejects it anyway.
* If it changes seed priority before ordinary row search, it can regress straight/normal curves.

Minimum constraints if implemented later:

* keep fixed-row seed as primary;
* use side-column supplement only when the corresponding side is missing;
* choose columns inside `kTraceBorderMargin` and `kSeedBorderMargin`, not at x=0 or x=RAW_W-1;
* require `trace_single()` success before accepting;
* do not change final `NO_MIDLINE` stop behavior.

### B2. Multi-row horizontal seed scan

Mechanism:

```text
try START_HIGH
if missing, try several nearby rows above START_HIGH
use the first row that gives a valid seed/trace
```

Benefits:

* Still uses the same horizontal edge search idea.
* Less likely to pick a pure side-border artifact than a vertical scan.

Risks:

* Left and right seeds can come from different rows unless tightly constrained.
* A fixed list of rows may still miss a true side entrant.
* It can change ordinary curve behavior more broadly because all frames may get extra search rows.

### B3. Element-state-only seed supplement

Mechanism:

```text
only enable side-column seed supplement when cross/ring is already suspected or active
```

Benefits:

* Lower risk to ordinary road behavior.
* Better matches the user's symptom concentration around cross/ring.

Risks:

* May be too late if ordinary seed starvation prevents L/corner detection before entering the element state.
* It does not help visible side-border loss during sharp ordinary curves.

## Current Recommendation

Preferred research direction: B1, but only as a very small, current-frame seed supplement after the existing fixed-row search fails for a side.

Do not implement yet without a line-level patch table. The first design decision is whether the supplement should be:

1. always available for missing side seeds;
2. only available when the image shape suggests element entry;
3. only available inside cross/ring state.

Given the user's video description, option 1 is the most direct but highest impact. Option 2 is likely the best compromise. Option 3 is safest but may miss the actual starvation frame.

## Source Change Guardrails

Do not change these in Branch B MVP:

* `code/core/control.cpp::line_ok()`
* `code/drivers/drive_output.cpp::drive_output_apply()`
* global `TRACK_REJECT_NO_MIDLINE`
* cross entry from double L to single L
* ring forced-side state table
* global retention of stale `left_trace/right_trace`

Any Branch B patch must list:

* exact seed column(s) and row range;
* which side(s) can use the supplement;
* how seed is kept inside `kTraceBorderMargin`;
* whether the seed can coexist with a fixed-row seed on the other side;
* how `seed_state`, `seeds->row`, and `seeds->width` are represented if sides come from different rows;
* what happens when `trace_single()` rejects the supplemented seed.
