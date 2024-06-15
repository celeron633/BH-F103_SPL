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

void oledPeriphInit();
void i2cWriteByte(uint8_t regAddr, uint8_t data);

void oledInit(void);
void oledWriteCmd(uint8_t cmd);
void oledWriteData(uint8_t data);
void oledSetPos(uint8_t x, uint8_t y);
void oledFill(uint8_t data);
void oledPrint(uint8_t x, uint8_t y, const char *str);
void oledPrintTest(uint8_t x, uint8_t y, uint8_t off);
void oledShowChar(uint8_t x, uint8_t y, char c);
void oledShowString(uint8_t x, uint8_t y, char str[]);

void oledShowChineseTest(uint8_t x, uint8_t y);

#endif