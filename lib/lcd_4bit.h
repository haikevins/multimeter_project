/*
  ******************************************************************************
  * @file    lcd_4bit.h                                                        *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __LCD_4BIT_H__
#define __LCD_4BIT_H__

#include "stm32f10x.h"

/*functions*/
void LCD4_Init(void);
void LCD4_Clear(void);
void LCD4_Print(char* str);
void LCD4_SetCursor(uint8_t row, uint8_t col);
void LCD4_PrintFloat(float value, uint8_t decimalPlaces);

#endif

/********************************* END OF FILE ********************************/