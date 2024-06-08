# UART收发

## 硬件信息
- Board: BH-F103
- CPU: STM32F103ZET6
- Flash: 512KB
- SRAM: 64KB


## 开发环境
- ToolChain: GCC
- IDE: VSCode + cortex debug + openOCD

## 实现步骤
1. 初始化UART1对应的GPIO（PA10：RX，PA9：TX），模式使用GPIO_Mode_AF，不要使用PP
2. 初始化USART1（USART_Init），使能USART（USART_Cmd(USART1, ENABLE)）
3. 配置NVIC使能来自USART的中断，优先级分组暂时都设置为1
4. 启用USART的中断USART_ITConfig，条件为RXNE，即收到了数据
5. 重写weak函数USART1_IRQHandler处理中断
