/*
  ******************************************************************************
  * @file    systick.h                                                         *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f10x.h"                  // Device header

/*functions*/
void Sys_Config(void);
void Sys_Delay_Ms(uint16_t time_ms);

#endif

/********************************* END OF FILE ********************************/