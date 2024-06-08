#include <stdint.h>
#include "stm32f10x.h"

#include "bsp_led.h"
#include "bsp_uart.h"
#include "delay.h"

int main(void)
{
	InitLedGPIO();
	InitUART();

	// printf("hello world\n");
	uart_printf("hello world\n");

	while (1) {
		R();
		delay_us(100 * 1000);
		G();
		delay_us(100 * 1000);
		B();
		UARTSend('1');
		delay_us(100 * 1000);
	}

	return 0;
}
