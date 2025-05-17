/*
  ******************************************************************************
  * @file    adc.h                                                            *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/
#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f10x.h"                  // Device header

/*functions*/
void ADC_Config(void);
uint16_t ADC_Read(void);
float Resistor_Measure(float R_known, float Vcc);
float Capacitor_Measure(float R_ohm, float Vcc);
float ADC_LowPassFilter(float input, float prev_output, float alpha);

#endif

/********************************* END OF FILE ********************************/