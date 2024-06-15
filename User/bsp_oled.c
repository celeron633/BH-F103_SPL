#include "bsp_oled.h"

#include "stm32f10x_rcc.h"

#include "delay.h"
#include "oled_font.h"

#define I2C_Speed       400000
#define I2C_OWN_ADDR
#define OLED_ADDR       0x78

void oledPeriphInit()
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
    // Master端I2C地址
    iicOLED.I2C_OwnAddress1 = 0x12;
    I2C_Init(I2C2, &iicOLED);
}

void i2cWriteByte(uint8_t regAddr, uint8_t data)
{
    // 检测总线繁忙等待
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

    // I2C起始
    I2C_GenerateSTART(I2C2, ENABLE);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

    // 发送地址
    I2C_Send7bitAddress(I2C2, OLED_ADDR, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    // 发送数据
    I2C_SendData(I2C2, regAddr);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING));

    // 发送数据
    I2C_SendData(I2C2, data);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    
    // 停止
    I2C_GenerateSTOP(I2C2, ENABLE);
}

void oledWriteCmd(uint8_t cmd)
{
    i2cWriteByte(0x00, cmd);
}

void oledWriteData(uint8_t data)
{
    i2cWriteByte(0x40, data);
}

void oledInit(void)
{
    delay_ms(500);

    oledWriteCmd(0xAE);     // 屏幕关
	oledWriteCmd(0x20);	    // 设置寻址模式
	oledWriteCmd(0x10);	    /* 00,Horizontal Addressing Mode;
					     			 01,Vertical Addressing Mode;
					     			 10,Page    Addressing Mode (RESET);
					     			 11,Invalid */
	oledWriteCmd(0xb0);	    // Set Page Start Address for Page Addressing Mode,0-7
	oledWriteCmd(0xc8);	    // COM扫描反向
	oledWriteCmd(0x00);     // 起始列地址低位
	oledWriteCmd(0x10);     // 起始列地址高位
	oledWriteCmd(0x40);     // --set start line address
	oledWriteCmd(0x81);     // 设置对比度
	oledWriteCmd(0xff);     // 亮度调节 范围0x00~0xff
	oledWriteCmd(0xa1);     // set segment re-map 0 to 127
	oledWriteCmd(0xa6);     // 正常显示
	
	oledWriteCmd(0xa8);     // 设置MUX数(1 to 64)
	oledWriteCmd(0x3F);     // MUX=63 显示63行
	
	oledWriteCmd(0xa4);     // 0xa4,输出 RAM 内容;0xa5,忽略 RAM 内容
	oledWriteCmd(0xd3);     //  设置显示偏移
	oledWriteCmd(0x00);     // 没有偏移
	
	oledWriteCmd(0xd5);     // 设置显示时钟分频数、振荡器频率
	oledWriteCmd(0xf0);     // --set divide ratio
	oledWriteCmd(0xd9);     // 设置预充电周期
	oledWriteCmd(0x22);     //
	oledWriteCmd(0xda);     // COM引脚配置
	oledWriteCmd(0x12);     // 启用左右反置
	
	oledWriteCmd(0xdb);     // 设置 vcomh 输出
	oledWriteCmd(0x20);     // 0x20,0.77xVcc
	
	oledWriteCmd(0x8d);     // --set DC-DC enable
	oledWriteCmd(0x14);     //
	oledWriteCmd(0xaf);     // --turn on oled panel
}

void oledSetPos(uint8_t x, uint8_t y)
{
    // b0~b7: 设置页地址
    oledWriteCmd(0xb0 + y);

    
    /*
    // x坐标低4位
    uint8_t colAddrLow4bit  = 0x00;
    // x坐标高4位
    uint8_t colAddrHigh4bit = 0x10;

    colAddrLow4bit  |=  (x & 0x0f);
    colAddrHigh4bit |= (x & 0xf0);

    oledWriteCmd(colAddrHigh4bit);
    oledWriteCmd(colAddrLow4bit);
    */

   
   // 低4位
   oledWriteCmd((x&0x0f));
   // 高4位
   oledWriteCmd((x&0xf0)>>4 | 0x10);
   
}

void oledFill(uint8_t data)
{   
    // 8个page, 每个page有8行
    for (int i = 0; i < 8; i++) {
        oledSetPos(0, i);
        // 每个page 128列
        for (int j = 0; j < 128; j++) {
            oledWriteData(data);
        }
    }
}

void oledShowChar(uint8_t x, uint8_t y, char chr)
{
    uint8_t index = chr - ' ';

    oledSetPos(x, y);
    for (int i = 0; i < 6; i++) {
        oledWriteData(F6x8[index][i]);
    }
}

void oledShowString(uint8_t x, uint8_t y, char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        oledShowChar(x, y, str[i]);
        i++;
        x += 8;
        if (x > 120) {
            x = 0;
            y += 1;
        }
    }
}

void oledShowChineseTest(uint8_t x, uint8_t y)
{
   oledSetPos(x, y);
   // 上半部分
   for (int i = 0; i < 10; i+=2) {
        for (int j = 0; j < 16; j++) {
            oledWriteData(FTEST2[i][j]);
        }
   }
   y += 1;
   // 下半部分
   oledSetPos(x, y);
   for (int i = 1; i < 10; i+=2) {
        for (int j = 0; j < 16; j++) {
            oledWriteData(FTEST2[i][j]);
        }
   }
}