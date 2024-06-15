#include <stdint.h>
#include "stm32f10x.h"

#include "bsp_uart.h"
#include "bsp_oled.h"
#include "delay.h"

int main(void)
{
	oledPeriphInit();
	oledInit();

	delay_ms(100);
	oledFill(0xff);
	delay_ms(100);
	oledFill(0x00);

	// oledShowChar(0, 0, 'a');
	// oledShowString(0, 0, (char *)"hello world1234567890123456");
	oledShowChineseTest(0, 0);

	while (1)
	{
		
	}
	

	return 0;
}
