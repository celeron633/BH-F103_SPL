#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include <stdint.h>
#include "stm32f10x.h"

#define LED_R_PIN GPIO_Pin_5
#define LED_G_PIN GPIO_Pin_0
#define LED_B_PIN GPIO_Pin_1

void InitLedGPIO(void);

#define R()                 \
    GPIOB->ODR = 0xffffffff;         \
    GPIOB->ODR &= (uint32_t)0x1f;   // 1f: 0b011111


#define G()                 \
    GPIOB->ODR = 0xffffffff;         \
    GPIOB->ODR &= (uint32_t)0x3e;   // 3e: 0b111110


#define B()                 \
    GPIOB->ODR = 0xffffffff;         \
    GPIOB->ODR &= (uint32_t)0x3d;   // 3d: 0b111101

#endif