#include "bsp_uart.h"
#include "stm32f10x_rcc.h"

void InitUART()
{
    // 初始化GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // 初始化GPIO
    GPIO_InitTypeDef uartGPIO;
    uartGPIO.GPIO_Mode = GPIO_Mode_AF_PP;
    uartGPIO.GPIO_Pin =  UART_TX_PIN;
    uartGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &uartGPIO);

    uartGPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    uartGPIO.GPIO_Pin = UART_RX_PIN;
    GPIO_Init(GPIOA, &uartGPIO);

    // 初始化UART
    USART_InitTypeDef uart1;
    uart1.USART_BaudRate = 9600;
    uart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    uart1.USART_Parity = USART_Parity_No;
    uart1.USART_StopBits = USART_StopBits_1;
    uart1.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &uart1);

    // 使能UART
    USART_Cmd(USART1, ENABLE);

    // 初始化NVIC
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = USART1_IRQn;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&nvic);

    // 收到数据触发中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void UARTSend(uint8_t ch)
{
    // 这个要先reset, 不然第一个byte丢失
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_SendData(USART1, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        /* code */
    }
    
}

void UARTSendBytes(uint8_t ch[], size_t size)
{
    for (uint32_t i = 0; i < size; i++) {
        UARTSend(ch[i]);
    }
}

void uprintf(const char *fmt, ...)
{
    char buf[256] = {0};

    va_list argp;
    va_start(argp, fmt);
    int sLen = vsprintf(buf, fmt, argp);
    va_end(argp);

    if (sLen > 0) {
        UARTSendBytes((uint8_t *)buf, sLen);
    }
}