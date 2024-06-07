# 点亮一个LED灯

## 硬件信息
- Board: BH-F103
- CPU: STM32F103ZET6
- Flash: 512KB
- SRAM: 64KB

## 开发环境
- ToolChain: GCC
- IDE: VSCode + cortex debug + openOCD

## 实现步骤
1. 初始化LED对应GPIO的APB2总线的时钟
2. 通过库函数控制对应GPIO的引脚电平，拉低电平点亮灯泡
