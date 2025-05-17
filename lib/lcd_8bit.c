#include "lcd_8bit.h"
#include "stdio.h"
#include "tim2.h"
#include "gpio.h"

#define LCD8_GPIO         GPIOB
#define LCD8_RS_PIN       GPIO_Pin_9
#define LCD8_EN_PIN       GPIO_Pin_10

const uint16_t data_pins[8] = {
    GPIO_Pin_0,  // D0
    GPIO_Pin_1,  // D1
    GPIO_Pin_3,  // D2
    GPIO_Pin_4,  // D3
    GPIO_Pin_5,  // D4
    GPIO_Pin_6,  // D5
    GPIO_Pin_7,  // D6
    GPIO_Pin_8   // D7
};

static void LCD8_EnablePulse(void)
{
    GPIO_SetBits(LCD8_GPIO, LCD8_EN_PIN);
    Tim2_Delay_Us(1);
    GPIO_ResetBits(LCD8_GPIO, LCD8_EN_PIN);
    Tim2_Delay_Us(40);
}

static void LCD8_Write8Bits(uint8_t data)
{
    for (int i = 0; i < 8; ++i)
    {
        if (data & (1 << i))
            GPIO_SetBits(LCD8_GPIO, data_pins[i]);
        else
            GPIO_ResetBits(LCD8_GPIO, data_pins[i]);
    }
}

static void LCD8_Send(uint8_t data, uint8_t is_data)
{
    if (is_data)
        GPIO_SetBits(LCD8_GPIO, LCD8_RS_PIN);
    else
        GPIO_ResetBits(LCD8_GPIO, LCD8_RS_PIN);

    LCD8_Write8Bits(data);
    LCD8_EnablePulse();
}

void LCD8_SendCmd(uint8_t cmd)
{
    LCD8_Send(cmd, 0);
}

void LCD8_SendData(uint8_t data)
{
    LCD8_Send(data, 1);
}

void LCD8_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

		Gpio_Config(GPIOB, LCD8_RS_PIN | LCD8_EN_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

		Gpio_Config(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

    Tim2_Delay_Ms(50);

    LCD8_SendCmd(0x38); 
		Tim2_Delay_Us(40);
    LCD8_SendCmd(0x0C);
		Tim2_Delay_Us(40);
    LCD8_SendCmd(0x06); 
		Tim2_Delay_Us(40);
    LCD8_SendCmd(0x01);
		Tim2_Delay_Ms(2);
}

void LCD8_Clear(void)
{
    LCD8_SendCmd(0x01);
    Tim2_Delay_Ms(2);
}

void LCD8_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address = (row == 0) ? col : 0x40 + col;
    LCD8_SendCmd(0x80 | address);
}

void LCD8_Print(char* str)
{
    if (str == NULL) return;
    while (*str)
    {
        LCD8_SendData(*str++);
    }
}

void LCD8_PrintFloat(float value, uint8_t decimalPlaces)
{
    char buffer[16];
    sprintf(buffer, "%.*f", decimalPlaces, value);
    LCD8_Print(buffer);
}