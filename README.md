# LED跑马灯

## 硬件信息
- Board: BH-F103
- CPU: STM32F103ZET6
- Flash: 512KB
- SRAM: 64KB


## 开发环境
- ToolChain: GCC
- IDE: VSCode + cortex debug + openOCD

## 实现步骤
1. 初始化3个LED对应GPIO的APB2总线的时钟
2. 通过控制对应GPIO的ODR寄存器的值，控制不同灯的亮灭
