#ifndef __BSP_OLED_H__
#define __BSP_OLED_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#include <stdio.h>
#include <stdint.h>

#define OLED_GPIO       GPIOB
#define OLED_SDA_PIN    GPIO_Pin_11
#define OLED_SCK_PIN    GPIO_Pin_10

void InitOLED();
void WriteByte(uint8_t d);
void WriteData(uint8_t *d, size_t len);

#endif