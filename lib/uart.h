/*
  ******************************************************************************
  * @file    uart.h                                                            *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"

/*global varibles*/
extern uint32_t uart_index;
extern char uart_buffer[100];

/*functions*/
void Uart_Send_Char(char chr);
void Uart_Send_Digit(int num);
void Uart_Send_Hex(uint16_t num);
void Uart_Send_String(char *str);
void Uart_Config(uint16_t baudrate);

#endif

/********************************* END OF FILE ********************************/