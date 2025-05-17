#include "adc.h"
#include "gpio.h"
#include "tim2.h"

static uint32_t time_us = 0;
static float filtered = 0.0f;

// Ham khoi tao ADC1 tren kenh PA0 (ADC_Channel_0)
void ADC_Config(void)
{
    // Bat clock cho GPIOA va ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    // Cau hinh chan PA0 o che do Analog Input
    GPIO_InitTypeDef gpioInit;
    gpioInit.GPIO_Pin = GPIO_Pin_0;
    gpioInit.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &gpioInit);

    // Cau hinh ADC1
    ADC_InitTypeDef adcInit;
    adcInit.ADC_Mode = ADC_Mode_Independent;            // Che do doc doc lap
    adcInit.ADC_ScanConvMode = DISABLE;                 // Khong quet nhieu kenh
    adcInit.ADC_ContinuousConvMode = DISABLE;           // Che do doc mot lan
    adcInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // Khong su dung trigger ngoai
    adcInit.ADC_DataAlign = ADC_DataAlign_Right;        // Canh phai
    adcInit.ADC_NbrOfChannel = 1;                       // So kenh can doc: 1
    ADC_Init(ADC1, &adcInit);

    // Cau hinh kenh ADC: Channel 0, thu tu 1, thoi gian lay mau 28.5 chu ky
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5);

    // Bat ADC1
    ADC_Cmd(ADC1, ENABLE);

    // Hieu chuan ADC
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

// Ham doc trung binh 50 gia tri ADC tu kenh PA0
uint16_t ADC_Read(void)
{
    uint32_t sum = 0;
    for (int i = 0; i < 50; ++i)
    {
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);           // Bat dau chuyen doi
        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));   // Cho chuyen doi hoan thanh
        sum += ADC_GetConversionValue(ADC1);              // Cong don gia tri
    }
		
    uint16_t raw_value = (uint16_t)(sum / 50);  // Tra ve gia tri trung binh
		
		filtered = ADC_LowPassFilter((float)raw_value, filtered, 0.2f);
		
		return (uint16_t)filtered;
}

float ADC_LowPassFilter(float input, float prev_output, float alpha)
{
    return alpha * input + (1.0f - alpha) * prev_output;  // Công th?c l?c
}

// Ham do dien tro su dung phan ap
float Resistor_Measure(float R_known, float Vcc)
{
    uint16_t adc_val = ADC_Read();
    float Vadc = (adc_val / 4095.0f) * Vcc;       // Chuyen gia tri ADC thanh dien ap

    // Kiem tra de tranh chia cho 0
    if ((Vcc - Vadc) < 0.01f)
		{
				return -1.0f;
		}

    float R_unknown = R_known * (Vadc / (Vcc - Vadc));    // Ap dung cong thuc tinh R
    return R_unknown;
}

float Capacitor_Measure(float R_ohm, float Vcc)
{
		Gpio_Config(GPIOA, GPIO_Pin_1, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
	
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		Tim2_Delay_Ms(100);
	
		Gpio_Config(GPIOA, GPIO_Pin_1, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
		
		float target_voltage = 0.632f * Vcc;
		
    while (1)
    {
				uint16_t adc_val = ADC_Read();
				float Vadc = (adc_val / 4095.0f) * Vcc;
        if (Vadc >= target_voltage)
				{
						break;
				}
				
				Tim2_Delay_Us(1);
        time_us++;
				
        if (time_us > 1000000)
				{
						return -1.0f;
				}
		}
		 
    float C_farad = (float)time_us / R_ohm;
    float C_uF = C_farad * 1e6f;

    return C_uF;			
}
