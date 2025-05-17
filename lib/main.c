#include "stm32f10x.h"                  // Device header
#include "gpio.h"
#include "mystring.h"
#include "systick.h"
#include "uart.h"
#include "tim2.h"
#include "adc.h"
#include "lcd_i2c.h"

float R_known = 10000.0f;
float Vcc = 3.3f;

int main(void)
{
	Uart_Config(9600);
	Tim2_Config();
	I2C2_LCD_Init();
	LCD_Init();

	LCD_Set_Cursor(0, 0);
	LCD_Send_String("Fuck you");
	LCD_Set_Cursor(1, 1);
	LCD_Send_String("Thang");
	while(1)
	{
	}
}



	