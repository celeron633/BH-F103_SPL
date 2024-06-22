#ifndef __DELAY_H__
#define __DELAY_H__

#include <stdint.h>

#include "stm32f10x.h"
#include "core_cm3.h"


void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

void delay_us2(uint32_t us);

#endif