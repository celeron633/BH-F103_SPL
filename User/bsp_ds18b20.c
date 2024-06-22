#include "bsp_ds18b20.h"
#include "delay.h"
#include "bsp_uart.h"

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
    delay_us2(500);
    // 释放掉DQ控制
    DQ_HIGH();
    delay_us2(10);
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
    // 读取DQ线电平, 等待DQ被DS18B20拉低
    while (GPIO_ReadInputDataBit(DS18B20_GPIO, DS18B20_DQ_PIN) == 1)
    {
        delay_us2(1);
        retryCount++;
        // 最多等240us, 若DQ还没有被DS18B20拉低, 认为等待ACK失败
        if (retryCount > 240) {
            return -1;
        }
    }
    retryCount = 0;
    // 等待DQ被DS18B20重新释放
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

void ds18b20WriteByte(uint8_t d)
{
    for (int i = 0; i < 8; i++) {
        uint8_t tmp = (d & (uint8_t)0x01);
        d = (d >> 1);

        DQ_OUT();
        DQ_LOW();
        delay_us2(15);
        if (tmp != 0) {
            DQ_HIGH();
        }
        delay_us2(45);
        DQ_HIGH();
        delay_us2(1);
    }
}

uint8_t ds18b20ReadByte(void)
{
    uint8_t dat = 0;

    for (int i = 0; i < 8; i++) {
        DQ_OUT();
        DQ_LOW();
        delay_us2(10);
        DQ_HIGH();
        DQ_IN();
        delay_us2(10);

        dat = (dat >> 1);
        if (GPIO_ReadInputDataBit(DS18B20_GPIO, DS18B20_DQ_PIN) > 0) {
            dat |= 0x80;
        }
        delay_us2(1);
    }

    return dat;
}

int ds18b20ReadTemperature(void)
{
    uint16_t temp;
    uint8_t temp_low = 0, temp_high = 0;

    if (ds18b20Reset() < 0) {
        uprintf("reset failed!\n");
        return -1;
    }
    // 跳过ROM序列检测
    ds18b20WriteByte(0xCC);
    // 启动一次温度转换
    ds18b20WriteByte(0x44);
    // 等待温度转换完成
    while(ds18b20ReadByte() != 0xFF) {

    }

    if (ds18b20Reset() < 0) {
        uprintf("reset failed!\n");
        return -1;
    }
    // 跳过ROM序列检测
    ds18b20WriteByte(0xCC);
    // 启动一次温度转换
    ds18b20WriteByte(0xBE);

    temp_low = ds18b20ReadByte();
    temp_high = ds18b20ReadByte();

    uprintf("low:[%d], high:[%d]\n", temp_low, temp_high);

    temp = temp_high;
    temp = ((temp << 8) | temp_low);

    return temp;
}