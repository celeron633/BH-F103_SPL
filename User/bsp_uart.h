#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include <stdio.h>

#define UART_GPIO       GPIOA
#define UART_RX_PIN     GPIO_Pin_10
#define UART_TX_PIN     GPIO_Pin_9

void InitUART();
void UARTSend(uint8_t ch);
void UARTSendBytes(uint8_t ch[], size_t size);

#endif