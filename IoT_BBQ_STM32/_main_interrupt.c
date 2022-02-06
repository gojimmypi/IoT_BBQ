#include "Common/globals.h"
#include <stm32l4xx_hal.h>

#include "LED/LED.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
    osSystickHandler();

    HAL_SYSTICK_IRQHandler(); // for UART
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13) // GPIOC
    {
        switch (LED_GetMode())
        {
        case IsBlinking:
            LED_SetMode(AlwaysOn);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            break;
            
        case AlwaysOn:
            LED_SetMode(AlwaysOff);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        case AlwaysOff:
            LED_SetMode(IsBlinking);
            break;
            
        default:
            LED_SetMode(IsBlinking);
            break;
        }    
    }
    // when done here, recall we'll return to EXTI15_10_IRQHandler()
}

// EXTI15_10_IRQHandler is a predefined name. See STM32L4xx_HAL_Driver\Src\stm32l4xx_hal_gpio.c
void EXTI15_10_IRQHandler(void)
{
    // when an interrupt occurs, we arrive here, but we need to figure out which pin triggered it.
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13); // check to see if this is our interrupt. if so clear it and call the HAL_GPIO_EXTI_Callback(GPIO_Pin)
}
