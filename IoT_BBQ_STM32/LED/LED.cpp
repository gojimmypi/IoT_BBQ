#include "../LED/LED.h"
#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

    int LED_VERSION() {
        return 1;
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
        switch (current_LED_MODE)
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
        switch (current_LED_MODE)
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