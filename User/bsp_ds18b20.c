#include "bsp_ds18b20.h"

#include "delay.h"

void ds18b20Init()
{
    RCC_APB2PeriphClockCmd(DS18B20_CLOCK, ENABLE);
    GPIO_InitTypeDef sensorGPIO;
    sensorGPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    sensorGPIO.GPIO_Pin = DS18B20_DQ_PIN;
    sensorGPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &sensorGPIO);
}

// ds18b20复位
int ds18b20Reset()
{
    DQ_OUT();
    DQ_LOW();
    // 拉低DQ线500毫秒
    delay_us(500);
    // 释放掉DQ控制
    DQ_HIGH();
    delay_us(10);
    if (ds18b20WaitAck() < 0) {
        return -1;
    }

    return 0;
}

int ds18b20WaitAck()
{
    // 切换为输入模式
    DQ_IN();

    int retryCount = 0;
    // 读取DQ线电平, 等待DQ被拉低
    while (GPIO_ReadInputDataBit(DS18B20_GPIO, DS18B20_DQ_PIN) == 1)
    {
        delay_us(1);
        retryCount++;
        // 最多等240us, 若DQ还没有被DS18B20拉低, 认为等待ACK失败
        if (retryCount > 240) {
            return -1;
        }
    }
    retryCount = 0;
    // 等待DQ被重新释放
    while (GPIO_ReadInputDataBit(DS18B20_GPIO, DS18B20_DQ_PIN) == 0)
    {
        delay_ms(1);
        retryCount++;
        if (retryCount > 240) {
            return -1;
        }
    }

    return 0;
}

void writeByte(uint8_t d)
{

}

uint8_t readByte(void)
{

    
}