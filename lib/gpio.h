/*
  ******************************************************************************
  * @file    gpio.h                                                            *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f10x.h"                  // Device header

/*functions*/
void Gpio_Config(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOSpeed_TypeDef GPIO_Speed);

#endif

/********************************* END OF FILE ********************************/