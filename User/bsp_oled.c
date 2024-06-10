#include "bsp_oled.h"

#include "stm32f10x_rcc.h"

#define I2C_Speed       400000
#define I2C_OWN_ADDR

void InitOLED()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 初始化GPIO
    GPIO_InitTypeDef iicGPIO;
    iicGPIO.GPIO_Mode = GPIO_Mode_AF_OD;
    iicGPIO.GPIO_Pin = OLED_SCK_PIN;
    iicGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &iicGPIO);

    iicGPIO.GPIO_Mode = GPIO_Mode_AF_OD;
    iicGPIO.GPIO_Pin = OLED_SDA_PIN;
    GPIO_Init(GPIOB, &iicGPIO);

    // 初始化IIC
    I2C_InitTypeDef iicOLED;
    iicOLED.I2C_Ack = I2C_Ack_Enable;
    iicOLED.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    iicOLED.I2C_ClockSpeed = I2C_Speed;
    iicOLED.I2C_DutyCycle = I2C_DutyCycle_2;
    iicOLED.I2C_Mode = I2C_Mode_I2C;
    iicOLED.I2C_OwnAddress1 = 0x12;
    I2C_Init(I2C2, &iicOLED);
}

void WriteByte(uint8_t d)
{
    
}