
#include "delay.h"



void delay_us(uint32_t us)
{
	volatile uint32_t i;
	volatile uint32_t j;
	
	for (i = 0; i < us; i++) {
		j = 11;
		while (j != 0) {
			j--;
		}
	}
}

void delay_ms(uint32_t ms)
{
	delay_us(ms * 1000);
}

void delay_us2(uint32_t us)
{
	// 设置要等待的周期数
	SysTick_Config(SystemCoreClock/1000000);

	for (uint32_t i = 0; i < us; i++) {
		while (!((SysTick->CTRL) & (1 << 16)));
	}

	// 关闭定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}