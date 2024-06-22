#include "bsp_tm1637.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#include <string.h>
#include <stdlib.h>

#include "bsp_uart.h"

// Start, Stop, Write时序参考TM1637手册

unsigned char digitMap[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void tm1637Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef tm1637GPIO;
    // 使用开漏模式输出, 设置寄存器为1时, 输出高阻态
    tm1637GPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    tm1637GPIO.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    tm1637GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &tm1637GPIO);
}

void tm1637Start(void)
{
    // 开始：CLK有效的情况下，DIO从高到低
    CLK_H();
    delay_us2(2);
    DIO_H();
    delay_us2(2);
    DIO_L();
}

void tm1637Stop(void)
{
    // 结束：时钟有效的情况下，DIO从低到高
    CLK_L();
    delay_us2(2);
    DIO_L();
    delay_us2(2);
    CLK_H();
    delay_us2(2);
    DIO_H();
}

void tm1637Write(uint8_t dat)
{
    for (int i = 0; i < 8; i++) {
        CLK_L();
        delay_us2(3);
        if ((dat & 0x01) == 1) {
            DIO_H();
        } else {
            DIO_L();
        }
        dat = (dat >> 1);
        CLK_H();
        delay_us2(3);
    }
}

void tm1637WaitACK(void)
{
    DIO_IN();

    CLK_L();
    delay_us2(5);
    // 等待TM1637将DIO拉高
    while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 1) {

    }
    CLK_H();
    delay_us2(2);
    CLK_L();

    DIO_OUT();
}

void tm1637Display(const char *dat, size_t len)
{
    if (len > 4) {
        len = 4;
    }

    uint8_t num2Display[4] = {0};
    for (size_t i = 0; i < 4; i++) {
        uint8_t idx = 0;
        if (len >= i + 1) {
            idx = (dat[i] - '0');
        } else {
            idx = 0;
        }
        if (idx > sizeof(digitMap)/sizeof(digitMap[0])) {
            idx = 0;
        }
        num2Display[i] = digitMap[idx];
        // uprintf("dat[%c] idx is %d\n", dat[i], idx);
    }

    // 设置模式
    // 40 地址自加模式，44 固定地址模式
    tm1637Start();
    tm1637Write(0x40);
    tm1637WaitACK();
    tm1637Stop();

    // 设置首地址
    tm1637Start();
    tm1637Write(0xc0);
    tm1637WaitACK();

    // 显示
    for (int i = 0; i < 4; i++) {
        tm1637Write(num2Display[i]);
        tm1637WaitACK();
    }
    tm1637Stop();

    // 亮度
    tm1637Start();
    tm1637Write(0x8c);
    tm1637WaitACK();
    tm1637Stop();
}

void tm1637DisplayInt(int i)
{
    char buf[8] = {0};
    /* if (!itoa(i, buf, 10)) {
        tm1637Display("0000", 4);
    } */

    snprintf(buf, sizeof(buf), "%04d", i);
    int len = strlen(buf);
    tm1637Display(buf, len);
}