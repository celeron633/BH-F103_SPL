#include "bsp_led.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

void InitLedGPIO(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef ledGPIO;
    ledGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    ledGPIO.GPIO_Pin = LED_R_PIN | LED_G_PIN | LED_B_PIN;
    ledGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &ledGPIO);

    // 先熄灭所有LED
    GPIOB->ODR = 0xffffffff;
}

