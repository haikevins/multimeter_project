#include "tim2.h"

static volatile uint32_t counter_ms = 0;

void Tim2_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef timInit;
    timInit.TIM_Prescaler = 72 - 1;          // 72 MHz / 72 = 1 MHz (1 µs/tick)
    timInit.TIM_CounterMode = TIM_CounterMode_Up;
    timInit.TIM_Period = 1000 - 1;           // 1000 µs = 1 ms
    timInit.TIM_ClockDivision = TIM_CKD_DIV1;
    timInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timInit);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // Enable update interrupt
    TIM_Cmd(TIM2, ENABLE);                      // Start timer

    NVIC_InitTypeDef nvicInit;
    nvicInit.NVIC_IRQChannel = TIM2_IRQn;
    nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
    nvicInit.NVIC_IRQChannelSubPriority = 0;
    nvicInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicInit);
}

static uint32_t millis(void)
{
    return counter_ms; 
}

void Tim2_Delay_Ms(uint32_t time_ms)
{
    uint32_t start_time = millis();
    while ((millis() - start_time) < time_ms); 
}

void Tim2_Delay_Us(uint16_t time_us)
{
    TIM_SetCounter(TIM2, 0);  // Reset counter v? 0

    while (TIM_GetCounter(TIM2) < time_us);
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		counter_ms++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
