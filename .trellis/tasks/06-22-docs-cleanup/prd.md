# docs 文档收敛与归档

## Goal

把 `docs/` 从“问题记录和调研文件平铺”整理成少入口、低噪声、能指导当前 `port/atg2022-reference-control` 分支调参和交接的文档体系。

这次不是简单搬文件。目标是建立新的主文档入口，保留固定存在的大局观和流程图信息，明确当前代码与 ATG2022 参考版这两个信息源的边界，把已解决问题和历史路线移入归档，避免后续调参继续被旧结论干扰。

## What I Already Know

- 用户反馈当前 `docs/` 文件数量仍然太多，Mimo 上一轮只完成了表面归档，没有降低入口复杂度。
- 当前 `docs/` 顶层仍有 12 个 Markdown 文档，另有 `archive/` 与 `reference/`。
- 固定重要信息必须保留：
  - 大局观：`docs/01_全局地图.md`
  - 流程图/主链合同：`docs/13_mainline_pipeline_map.md`
  - 控制参数：`docs/控制参数笔记.md`
  - 当前入口索引：`docs/00_readme.md`
- 当前文档体系涉及两个源：
  - 当前分支代码：`port/atg2022-reference-control`
  - 参考版：ATG2022 舵机车源头算法，主要经 `atg_reference/`、`atg_reference/PORTING.md`、`docs/reference/` 与若干 ATG 调研文档体现
- 已经归档但仍需重新判定入口可见性：
  - `docs/archive/06-22-resolved/ATG角点斜车身问题交接.md`
  - `docs/archive/06-22-resolved/ATG环岛问题记录.md`
- 旧路线资料不应作为当前调参依据：
  - `docs/archive/old-mainline/`
  - `docs/archive/aegis-old-runtime/`
- 当前活跃问题不应和已解决问题混在一起：
  - `docs/04_当前问题.md`
- 用户已选择合并型收敛方案（选项 1）：顶层只保留入口型文档，原始长文归档。

## Problem Statement

现状的问题不是缺少索引，而是信息层级不清：

- 顶层文件太多，读者需要自己判断哪些是当前事实、哪些是历史分析、哪些是参考版对比。
- 旧问题文档虽然移动了一部分，但 `00_readme.md` 仍把大量参考资料暴露为平级入口。
- 大局观、流程图、参考版对比、控制参数、IPM 标定、当前问题、历史问题之间没有明确的阅读边界。
- 部分文档标题以具体事故或调研命名，适合作为证据材料，不适合作为长期入口。

## Target Information Architecture

推荐最终只保留少量顶层入口：

```text
docs/
├── 00_readme.md                    # 唯一阅读入口：当前应读什么、不应读什么
├── 01_全局地图.md                  # 固定存在：项目大局观，可适度更新
├── 02_当前主链与参考版对比.md       # 新建：当前代码 vs ATG2022 参考版，吸收接入评估/新路线/尺度合同摘要
├── 03_调参与验证手册.md             # 新建：控制参数、IPM、验收、偏移诊断的可执行入口
├── 04_当前问题.md                  # 新建：只放仍未解决或正在验证的问题
├── archive/                        # 历史路线、已解决问题、被吸收的原始材料
└── reference/                      # 原始参考版代码片段/材料，保留但不作为阅读入口
```

固定信息的归宿：

| 信息 | 归宿 |
|------|------|
| 大局观、三层身份、舵机/差速边界 | 保留并更新 `01_全局地图.md` |
| 一帧主链、流程图、字段合同 | 合并进 `02_当前主链与参考版对比.md`，必要时保留原 `13_mainline_pipeline_map.md` 为被吸收材料 |
| 当前代码与 ATG2022 参考版对比 | 新建 `02_当前主链与参考版对比.md` |
| 控制参数、IPM 标定、偏移诊断、验收命令 | 新建 `03_调参与验证手册.md` |
| 当前圆环左线追踪问题、drive32 外漂等未解决事项 | 新建 `04_当前问题.md` |
| 已解决问题、旧路线、旧 runtime/control 改造 | `archive/` |
| 原始调研、推导、审计长文 | 归档为证据材料，主入口只保留摘要和链接 |

## Requirements

### 1. 重新定义顶层入口

- [x] 将 `docs/00_readme.md` 改为唯一入口，明确“先读 / 按需读 / 不作为当前依据”。
- [x] 顶层长期入口控制在 4-5 个 Markdown 文档以内。
- [x] 顶层入口必须能回答：
  - 当前工程是什么
  - 当前一帧怎么走
  - 当前代码与参考版差在哪里
  - 调参和验证看哪里
  - 还有哪些问题没解决

### 2. 建立当前主链与参考版对比文档

- [x] 新建 `docs/02_当前主链与参考版对比.md`。
- [x] 吸收或摘要以下内容：
  - `docs/13_mainline_pipeline_map.md`
  - `docs/ATG库接入点评估.md`
  - `docs/ATG新路线重构方案.md`
  - `docs/ATG尺度合同与参数来源审计.md`
  - `atg_reference/PORTING.md`
- [x] 明确两个源的边界：
  - 当前代码是运行合同
  - ATG2022 参考版是算法来源和对照对象
  - 差速控制边界不能按舵机 `pure_angle` 直接照搬
- [x] 原文长篇分析如仍有证据价值，移动到 `archive/` 或 `archive/source-notes/`，不留在顶层。

### 3. 建立调参与验证手册

- [x] 新建 `docs/03_调参与验证手册.md`。
- [x] 吸收或摘要以下内容：
  - `docs/控制参数笔记.md`
  - `docs/IPM调用调研.md`
  - `docs/IPM重标定流程.md`
  - `docs/14_偏移诊断与修正记录.md`
  - `docs/09_acceptance_checklist.md`
- [x] 文档必须以可执行动作为主：
  - 参数文件在哪里
  - 哪些参数控制哪一层
  - IPM 何时重标定
  - 最小验证命令是什么
  - 实车偏移如何检查
- [x] 原始 SOP/审计长文如过长，移动到 `archive/`，主文档只保留稳定步骤与链接。

### 4. 建立当前问题文档

- [x] 新建 `docs/04_当前问题.md`。
- [x] 只保留当前仍需要实车验证、调参或代码跟进的问题。
- [x] 吸收或摘要：
  - `docs/ATG圆环进不去左线追踪诊断.md`
  - PRD 中记录的 `drive32` 外漂问题
- [x] 每个问题至少包含：
  - 现象
  - 当前判断
  - 可验证证据或日志入口
  - 下一步动作
  - 明确不再追的旧方向

### 5. 归档和重命名原始材料

- [x] 建立清晰的归档分区，建议：
  - `docs/archive/resolved/`
  - `docs/archive/source-notes/`
  - `docs/archive/old-mainline/`
  - `docs/archive/aegis-old-runtime/`
- [x] 已解决问题放入 `resolved/`，并在 `archive/README.md` 写明解决状态和不再作为当前依据。
- [x] 被新文档吸收的长篇调研、审计、推导放入 `source-notes/`，作为证据链接保留。
- [x] 不删除 `docs/reference/`，但在 `00_readme.md` 中说明它是原始参考材料，不是当前入口。

### 6. 更新索引与交叉链接

- [x] `docs/00_readme.md` 只列新入口和归档规则，不再列一屏参考资料。
- [x] `docs/archive/README.md` 更新为“为什么归档 / 归档内容 / 何时还需要看”。
- [x] 新文档中保留必要的来源链接，避免信息失踪。
- [x] 旧文档移动后，主入口不出现断链。

## Acceptance Criteria

- [x] `docs/` 顶层 Markdown 入口不超过 5 个，且每个入口职责清晰。
- [x] `00_readme.md` 能在 1 分钟内告诉新接手者应该读哪几篇。
- [x] 当前代码与 ATG2022 参考版的关系在一个文档中讲清楚。
- [x] 调参、IPM、偏移检查、验收命令在一个手册中能直接执行。
- [x] 当前未解决问题集中在一个文档，不和已解决问题混杂。
- [x] 已解决问题和历史路线都在 `archive/`，并明确不作为当前调参依据。
- [x] 被归档的原始材料仍可追溯，未丢失关键证据。
- [x] `find docs -maxdepth 2 -type f | sort` 输出能体现新的层级。

## Definition of Done

- PRD 完成并确认收敛方案。
- 按 PRD 新建或重写文档。
- 移动归档文件，保留可追溯路径。
- 更新 `00_readme.md` 和 `archive/README.md`。
- 用 `find` / `rg` 检查顶层入口、断链和旧问题残留。
- 最后查看 `git diff -- docs .trellis/tasks/06-22-docs-cleanup/prd.md`，确认没有无关代码改动混入。

## Out of Scope

- 不修改运行代码。
- 不重新设计控制算法。
- 不删除参考版原始材料。
- 不把已解决问题重新展开讨论。
- 不把所有历史长文合并进新入口；新入口只承载当前事实、稳定步骤和必要链接。

## Decision (ADR-lite)

**Context**: 上一轮整理按文件逐项打勾，仍让大量调研/问题/验收文档平铺在顶层，读者无法快速区分当前事实、参考证据和历史问题。

**Decision**: 采用“少入口 + 原始材料归档”的信息架构。顶层只保留入口型文档；长篇调研、推导、已解决问题进入归档；当前代码与参考版对比、调参与验证、当前问题分别形成新的主文档。

**Consequences**: 顶层文档数量会明显减少，阅读路径更清楚；代价是需要从原文中抽取摘要并维护来源链接，避免证据丢失。

## Decision Follow-up

用户已选择“合并型收敛”：把 `13_mainline_pipeline_map.md`、`控制参数笔记.md` 等吸收到新入口后归档原文。

## Technical Notes

- 当前分支：`port/atg2022-reference-control`
- 整理前 `docs/` 顶层文档包括：
  - `00_readme.md`
  - `01_全局地图.md`
  - `09_acceptance_checklist.md`
  - `13_mainline_pipeline_map.md`
  - `14_偏移诊断与修正记录.md`
  - `ATG圆环角点阈值推导.md`
  - `ATG圆环进不去左线追踪诊断.md`
  - `ATG尺度合同与参数来源审计.md`
  - `ATG库接入点评估.md`
  - `ATG新路线重构方案.md`
  - `IPM调用调研.md`
  - `IPM重标定流程.md`
  - `控制参数笔记.md`
- 当前已有归档：
  - `docs/archive/06-22-resolved/`
  - `docs/archive/old-mainline/`
  - `docs/archive/aegis-old-runtime/`
- 当前已有原始参考材料：
  - `docs/reference/`
  - `atg_reference/`
  - `atg_reference/PORTING.md`
- 整理后顶层入口：
  - `docs/00_readme.md`
  - `docs/01_全局地图.md`
  - `docs/02_当前主链与参考版对比.md`
  - `docs/03_调参与验证手册.md`
  - `docs/04_当前问题.md`
