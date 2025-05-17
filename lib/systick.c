#include "systick.h"

static volatile uint32_t systick_counter = 0;

/*
	 Khoi tao SysTick de tao delay 1ms
	 Su dung nguon clock = HCLK (8MHz hoac 72MHz tuy cau hinh)
*/
void Sys_Config(void)
{
	SysTick_Config(SystemCoreClock / 1000);
}

/*
	 Ham delay don vi millisecond

	 Tham so:
	 - time_ms: so millisecond can delay
*/
void Sys_Delay_Ms(uint16_t time_ms)
{
	  systick_counter = time_ms;
    while(systick_counter != 0);
}

/*
	 Ham xu ly ngat SysTick
	 Giam bien systick_counter moi 1ms
*/
void SysTick_Handler(void)
{
    if (systick_counter > 0)
        systick_counter--;
}