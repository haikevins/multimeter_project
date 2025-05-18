/*
  ******************************************************************************
  * @file    uart1.h                                                           *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __UART1_H__
#define __UART1_H__

#include "stm32f10x.h"

/*global varibles*/
extern uint32_t uart1_index;
extern char uart1_buffer[100];

/*functions*/
void Uart1_Send_Char(char chr);
void Uart1_Send_Digit(int num);
void Uart1_Send_Hex(uint16_t num);
void Uart1_Send_String(char *str);
void Uart1_Config(uint16_t baudrate);

#endif

/********************************* END OF FILE ********************************/