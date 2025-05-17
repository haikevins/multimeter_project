/*
  ******************************************************************************
  * @file    lcd_i2c.h                                                         *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __I2C_LCD_H__
#define __I2C_LCD_H__

#include "stm32f10x.h"

// Public macros
#define I2C_TIMEOUT 10000

extern uint8_t lcd_address;

// Public functions
void I2C2_LCD_Init(void);
uint8_t I2C2_Scan_Address(void);

void I2C2_Send_Start(void);
void I2C2_Send_Stop(void);
void I2C2_Send_Address(uint8_t addr);
void I2C2_Send_Data(uint8_t data);

void LCD_Init(void);
void LCD_Write_byte(char data);
void LCD_Data_Write(char data);
void LCD_Control_Write(char data);
void LCD_Send_String(char *str);
void LCD_Clear(void);
void LCD_Set_Cursor(char col, char row);
void LCD_Send_Number(uint16_t num);
void LCD_Send_Float(float number);

#endif

/********************************* END OF FILE ********************************/