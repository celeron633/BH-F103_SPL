#include <stdint.h>
#include "stm32f10x.h"

#include "bsp_led.h"
#include "bsp_uart.h"
#include "bsp_tm1637.h"
#include "delay.h"

int main(void)
{
	InitLedGPIO();
	InitUART();
	tm1637Init();

	uprintf("hello world\n");
	tm1637Display("0000", 4);
	while (1) {
		G();
		delay_ms(250);
		R();
		delay_ms(250);
	}

	return 0;
}
