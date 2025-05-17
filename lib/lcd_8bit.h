/*
  ******************************************************************************
  * @file    lcd_8bit.h                                                        *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __LCD_8BIT_H__
#define __LCD_8BIT_H__

#include "stm32f10x.h"

/*functions*/
void LCD8_Init(void);
void LCD8_Clear(void);
void LCD8_Print(char* str);
void LCD8_SetCursor(uint8_t row, uint8_t col);
void LCD8_PrintFloat(float value, uint8_t decimalPlaces);

#endif

/********************************* END OF FILE ********************************/