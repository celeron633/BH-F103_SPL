#ifndef __BSP_TM1637_H__
#define __BSP_TM1637_H__

#include <stdint.h>
#include <stdio.h>

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"


#define TM1637_CLK  GPIO_Pin_4
#define TM1637_DIO  GPIO_Pin_5
#define TM1637_GPIO GPIOA

void tm1637Init(void);

void tm1637Start(void);
void tm1637Stop(void);
void tm1637Write(uint8_t dat);
void tm1637WaitACK(void);
void tm1637Display(const char *dat, size_t len);
void tm1637DisplayInt(int i);

#define CLK_H() GPIO_SetBits(TM1637_GPIO, TM1637_CLK)
#define CLK_L() GPIO_ResetBits(TM1637_GPIO, TM1637_CLK)

#define DIO_H() GPIO_SetBits(TM1637_GPIO, TM1637_DIO)
#define DIO_L() GPIO_ResetBits(TM1637_GPIO, TM1637_DIO)

#define DIO_IN()  GPIOA->CRL &= 0xFF0FFFFF; GPIOA->CRL |= 0x4 << 20
// CNF: 01 通用开漏输出模式 MODE: 11: 输出模式 50MHz
#define DIO_OUT() GPIOA->CRL &= 0xFF0FFFFF; GPIOA->CRL |= 0x7 << 20

#endif