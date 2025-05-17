/*
  ******************************************************************************
  * @file    tim2.h                                                            *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __TIM2_H__
#define __TIM2_H__

#include "stm32f10x.h"

/*functions*/
void Tim2_Config(void);
void Tim2_Delay_Ms(uint32_t time_ms);
void Tim2_Delay_Us(uint16_t time_us);

#endif

/********************************* END OF FILE ********************************/