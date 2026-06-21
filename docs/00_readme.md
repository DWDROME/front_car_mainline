# Front_Car Mainline Docs

这套工程是基于 ATG2022 舵机车算法移植到龙芯 LS2K0300 的差速车主线。

当前分支：`port/atg2022-reference-control`

## 先读这四篇

| 顺序 | 文档 | 用途 |
| --- | --- | --- |
| 1 | [01_全局地图.md](01_全局地图.md) | 建立心智模型：ATG 舵机车大脑如何接到 LS2K 差速车手脚。 |
| 2 | [02_当前主链与参考版对比.md](02_当前主链与参考版对比.md) | 当前一帧主链、运行合同、当前代码和 ATG2022 参考版的边界。 |
| 3 | [03_调参与验证手册.md](03_调参与验证手册.md) | 控制参数、IPM 标定、偏移检查、最小验证命令。 |
| 4 | [04_当前问题.md](04_当前问题.md) | 仍未解决或待实车验证的问题，只看这里跟进现状。 |

`00_readme.md` 是入口，不承载细节。顶层长期文档只保留入口型材料；原始调研和已解决问题都在 `archive/`。

## 当前有效结论

- 当前运行合同以本分支代码为准，不以旧本地 tracking 主线、Unity CD 旧参考或历史调研草稿为准。
- ATG2022 参考版是算法来源和对照对象；当前车是差速车，不能直接照搬参考版舵机 `pure_angle -> servo_pid` 控制链。
- 当前 profile 只激活十字、半十字和圆环；回环、Y 路、坡道、车库源码保留但不进入状态机。
- 当前没有停车线检测，`stop_line` 恒为 0，这是能力缺口，不是调参现象。

## 当前入口命令

```bash
bash code/test.sh --host
bash code/test.sh
bash scripts/straight_baseline_audit.sh .diag/front_car_capture_live_current.png
```

IPM 重标定入口见 [03_调参与验证手册.md](03_调参与验证手册.md)。

## 归档规则

[archive/](archive/) 只作证据追溯，不作为当前调参入口：

- `archive/resolved/`：已解决或不再作为当前问题跟进的记录。
- `archive/source-notes/`：被 `02/03/04` 吸收后的原始调研、推导、SOP、验收清单。
- `archive/old-mainline/`：已删除的旧本地 tracking 主线资料。
- `archive/aegis-old-runtime/`：已删除的旧 runtime/control 改造资料。

[reference/](reference/) 是原始参考材料，不是当前运行入口。
