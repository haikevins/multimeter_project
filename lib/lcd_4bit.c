#include "lcd_4bit.h"
#include "stdio.h"
#include "tim2.h"
#include "gpio.h"

#define LCD4_GPIO         GPIOB
#define LCD4_RS_PIN       GPIO_Pin_9
#define LCD4_EN_PIN       GPIO_Pin_10

const uint16_t lcd4_data_pins[4] = {
    GPIO_Pin_4,  // D4
    GPIO_Pin_5,  // D5
    GPIO_Pin_6,  // D6
    GPIO_Pin_7   // D7
};

static void LCD4_Write4Bits(uint8_t nibble)
{
    for (int i = 0; i < 4; ++i)
    {
        if (nibble & (1 << i))
            GPIO_SetBits(LCD4_GPIO, lcd4_data_pins[i]);
        else
            GPIO_ResetBits(LCD4_GPIO, lcd4_data_pins[i]);
    }
}

static void LCD4_EnablePulse(void)
{
    GPIO_SetBits(LCD4_GPIO, LCD4_EN_PIN);
    Tim2_Delay_Us(1);
    GPIO_ResetBits(LCD4_GPIO, LCD4_EN_PIN);
    Tim2_Delay_Us(40);
}

static void LCD4_Send(uint8_t data, uint8_t is_data)
{
    if (is_data)
        GPIO_SetBits(LCD4_GPIO, LCD4_RS_PIN);
    else
        GPIO_ResetBits(LCD4_GPIO, LCD4_RS_PIN);

    LCD4_Write4Bits(data >> 4);
    LCD4_EnablePulse();

    LCD4_Write4Bits(data & 0x0F);
    LCD4_EnablePulse();
}

void LCD4_Cmd(uint8_t cmd)
{
    LCD4_Send(cmd, 0);
}

void LCD4_Data(uint8_t data)
{
    LCD4_Send(data, 1);
}

void LCD4_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

		Gpio_Config(GPIOB, LCD4_RS_PIN | LCD4_EN_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

		Gpio_Config(GPIOB, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);

    Tim2_Delay_Ms(50);

    LCD4_Write4Bits(0x03); 
		LCD4_EnablePulse();
    Tim2_Delay_Ms(5);
    LCD4_Write4Bits(0x03); 
		LCD4_EnablePulse();
    Tim2_Delay_Us(150);
    LCD4_Write4Bits(0x03); 
		LCD4_EnablePulse();
    LCD4_Write4Bits(0x02); 
		LCD4_EnablePulse();

    LCD4_Cmd(0x28);
    LCD4_Cmd(0x0C);
    LCD4_Cmd(0x06);
    LCD4_Cmd(0x01);
    Tim2_Delay_Ms(2);
}

void LCD4_Clear(void)
{
    LCD4_Cmd(0x01);
    Tim2_Delay_Ms(2);
}

void LCD4_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? col : 0x40 + col;
    LCD4_Cmd(0x80 | addr);
}

void LCD4_Print(char* str)
{
    if (str == NULL) return;
    while (*str)
        LCD4_Data(*str++);
}

void LCD4_PrintFloat(float value, uint8_t decimalPlaces)
{
    char buffer[16];
    sprintf(buffer, "%.*f", decimalPlaces, value);
    LCD4_Print(buffer);
}

