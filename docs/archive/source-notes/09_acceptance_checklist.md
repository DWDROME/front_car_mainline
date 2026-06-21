# 验收单

结构验收：

- 新工程不修改 `project/user`
- 核心状态只用 plain struct
- 热路径没有 namespace/class 包装

算法验收：

- 能找到左右种子
- 能输出左右边界点数
- 能生成中线和 `guide_error`
- 有矩阵时走点级 IPM，无矩阵时可退回原图

运行验收：

- `bash "scripts/test.sh" --host` 可编译 host 主目标
- `bash "scripts/test.sh"` 可编译目标版本
- `./build-host/front_car_mainline --input xxx` 可离线跑
- `./build-host/front_car_mainline --analyze xxx --ipm xxx --report xxx` 可输出诊断结果
- 板端 live 模式可持续输出状态
