#include "../LED/LED.h"
#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

    volatile static enum LED_Mode __current_LED_MODE = IsBlinking; // we'll use a button to trigger an interrupt to set LED mode, starting with blinky

    int LED_VERSION() {
        return 1;
    }
    
    LED_Mode LED_GetMode()
    {
        // TODO RTOS wrap
        LED_Mode thisState = __current_LED_MODE;
        
        return thisState;
    }
    
    int LED_SetMode(LED_Mode NewState)
    {
        // TODO RTOS wrap
        __current_LED_MODE = NewState;
        
        return 0; // TODO check for errors
    }
    
    int LED_init()
    {
        GPIO_InitTypeDef GPIO_InitStructureA;

        GPIO_InitStructureA.Pin = GPIO_PIN_5;

        GPIO_InitStructureA.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructureA.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructureA.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructureA);
        
        return 0;
    }

    void LED_ON() {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }

    void LED_OFF() {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }

    //
    // Turn the LED on (unless button mode set to always off, or always on)
    //
     void STATE_LED_ON()
    {
        switch (__current_LED_MODE)
        {
        case IsBlinking:
            LED_ON();
            break;

        case AlwaysOn:
            LED_ON();
            break;
            
        case AlwaysOff:
            LED_OFF();
            break;

        default:
            LED_ON();
            break;
        }
    }


    //
    // Turn the LED off (unless button mode set to always on, or always off)
    //
     void STATE_LED_OFF()
    {
        switch (__current_LED_MODE)
        {
        case IsBlinking:
            LED_OFF();  // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        case AlwaysOn:
            LED_ON(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            break;

        case AlwaysOff:
            LED_OFF();  // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        default:
            LED_OFF(); //  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        }
    }


#ifdef __cplusplus
}
#endif    