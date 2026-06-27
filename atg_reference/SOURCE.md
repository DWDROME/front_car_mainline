# ATG2022 参考源码

本目录存放已购入的 ATG2022 参考算法源码，作为新赛道循迹与元素识别
迁移目标。

本地机器上的源码根路径：

```text
/mnt/c/Users/ds_ev/Downloads/Compressed/智能车比赛资料v1.2/智能车比赛资料v1.2/ATG2022_Master/ATG2022_Master V1.2
```

已复制的源码分组：

| 目标目录 | 来源 | 用途 |
| --- | --- | --- |
| `Project/CODE/` | `CODE/*.c`, `CODE/*.h` 精选算法文件 | 边线搜索、透视变换辅助、角点检测、十字、半十字、圆环、补线、Y 字路、坡道、赛道分类 |
| `Project/USER/` | `USER/Cpu0_Main.c`, `USER/Cpu0_Main.h` | 主循环证据与选线逻辑参考 |
| `port/` | 仅本地文件 | LS2K 适配层，不含 TC264 外设 |

复制后已执行的机械清理：

- CRLF 转换为 LF。
- 清除行尾空格与制表符。

复制后的算法文件原则上保持与原始源码接近。移植相关定义、硬件替换
及上报桥接属于 `atg_reference/port/` 或 `code/tracking/` 的职责。
