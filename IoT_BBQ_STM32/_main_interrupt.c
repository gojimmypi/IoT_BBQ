#include "Common/globals.h"
#include <stm32l4xx_hal.h>

#include "LED/LED.h"

volatile static int ButtonPressFound = 0;
volatile static int ButtonLongPressFound = 0;

volatile static GPIO_PinState ButtonState;

void SysTick_Handler(void)
{
    HAL_IncTick();
    osSystickHandler();
    HAL_SYSTICK_IRQHandler(); // for UART
    
    // TODO we should move this long button press logic to a thread for performance reasons. (we don't really need to check on EVERY systick)
    ButtonState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    
    if (ButtonPressFound && (ButtonState == GPIO_PIN_SET))
    {
        int thisTick = HAL_GetTick();
        if ((thisTick - ButtonPressFound) > 1000)
        {
            ButtonLongPressFound = 1;
        }
        ButtonPressFound = 0;
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    ButtonPressFound =  HAL_GetTick();
    
    // reminder we are already in an interrupt handler from EXTI15_10_IRQHandler(), so we don't need to portENTER_CRITICAL()
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
