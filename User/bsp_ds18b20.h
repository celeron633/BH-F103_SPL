#ifndef __BSP_DS18B20_H__
#define __BSP_DS18B20_H__

#include <stdint.h>

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define PIN
#define POUT

#define DS18B20_DQ_PIN  GPIO_Pin_10
#define DS18B20_GPIO    GPIOB
#define DS18B20_CLOCK   RCC_APB2Periph_GPIOB

void ds18b20Init();
int ds18b20Reset();
int ds18b20WaitAck();

void ds18b20WriteByte(uint8_t d);
uint8_t ds18b20readByte(void);

int ds18b20ReadTemperature(void);


#define DQ_IN()  DS18B20_GPIO->CRH &= 0xFFFFF0FF; DS18B20_GPIO->CRH |= 0x4 << 8
#define DQ_OUT() DS18B20_GPIO->CRH &= 0xFF0FF0FF; DS18B20_GPIO->CRH |= 0x7 << 8

#define DQ_LOW()    GPIO_ResetBits(DS18B20_GPIO, DS18B20_DQ_PIN)
#define DQ_HIGH()   GPIO_SetBits(DS18B20_GPIO, DS18B20_DQ_PIN)


#endif