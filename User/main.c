#include <stdint.h>
#include "stm32f10x.h"

#include "bsp_led.h"
#include "bsp_uart.h"
#include "bsp_tm1637.h"
#include "bsp_ds18b20.h"
#include "delay.h"

int count = 0;

int main(void)
{
	InitLedGPIO();
	InitUART();
	
	uprintf("hello world\n");

	// 初始化ds18b20的GPIO
	ds18b20Init();
	if (ds18b20Reset() < 0) {
		uprintf("ds18b20 init failed!\n");
	} else {
		uprintf("ds18b20 init success!\n");
	}


	int temp = ds18b20ReadTemperature();
	uprintf("temp is [%.2f]\n", temp * 0.0625);


	while (1) {
		delay_ms(100);
	}

	return 0;
}
