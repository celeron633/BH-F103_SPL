
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