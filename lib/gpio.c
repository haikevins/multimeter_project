#include "gpio.h"

/**
  * @brief  Configure GPIO pin with specified parameters
  * @param  GPIOx: GPIO port (GPIOA, GPIOB, GPIOC, etc.)
  * @param  GPIO_Pin: GPIO pin to configure (GPIO_Pin_0 to GPIO_Pin_15)
  * @param  GPIO_Mode: GPIO mode (GPIO_Mode_IN_FLOATING, GPIO_Mode_Out_PP, etc.)
  * @param  GPIO_Speed: GPIO speed (GPIO_Speed_10MHz, GPIO_Speed_2MHz, GPIO_Speed_50MHz)
  * @retval None
  */
void Gpio_Config(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, GPIOSpeed_TypeDef GPIO_Speed)
{
    /* Enable clock for corresponding GPIO port */
    if (GPIOx == GPIOA)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
    // Add other ports if needed
    
    /* Configure GPIO pin */
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = GPIO_Pin;
    gpio_init.GPIO_Mode = GPIO_Mode;
    gpio_init.GPIO_Speed = GPIO_Speed;
    GPIO_Init(GPIOx, &gpio_init);
}