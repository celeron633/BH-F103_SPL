#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define UART_GPIO       GPIOA
#define UART_RX_PIN     GPIO_Pin_10
#define UART_TX_PIN     GPIO_Pin_9

void InitUART();
void UARTSend(uint8_t ch);
void UARTSendBytes(uint8_t ch[], size_t size);

void vprint(const char *fmt, va_list argp);
void uart_printf(const char *fmt, ...);

#endif