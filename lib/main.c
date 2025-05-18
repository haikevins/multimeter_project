#include "stm32f10x.h"                  // Device header
#include "gpio.h"
#include "mystring.h"
#include "systick.h"
#include "uart1.h"
#include "tim2.h"
#include "adc.h"
#include "lcd_4bit.h"
#include "lcd_8bit.h"
#include "lcd_i2c2.h"

float R_known = 10000.0f;
float Vcc = 3.3f;

int main(void)
{
	Uart1_Config(9600);
	Tim2_Config();
	I2C2_LCD_Init();
	
	uint8_t addr = I2C2_Scan_Address();
	
	Uart1_Send_String("Quet dia chi LCD hoan tat. Dia chi: 0x");
	Uart1_Send_Hex(addr);
	Uart1_Send_String("\r\n");	
	
//	I2C2_LCD_Init();	
//	I2C2_LCD_Set_Cursor(0, 0);
//	I2C2_LCD_Send_String("hdadh");
	
//	LCD4_Init();
//	LCD4_SetCursor(0, 0);
//	LCD4_Print("hsasdada");

//	LCD8_Init();
//	LCD8_SetCursor(0, 0);
//	LCD8_Print("hsasdada");
	while(1)
	{
//		Uart1_Send_String("dsdads\r\n");
//		Tim2_Delay_Ms(100);
	}
}



	