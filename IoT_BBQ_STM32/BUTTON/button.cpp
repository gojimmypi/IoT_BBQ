// 
// 
// 

#include <stm32l4xx_hal.h>
#include "Common/globals.h"
#include "button.h"
#include "Tasks/state_machine.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    void CheckForLongPress() {
        GPIO_PinState ButtonState;
        TickType_t xButtonDelay = (100 / portTICK_PERIOD_MS);
        int t = 0;
        do {
            
            // FreeRTOS API functions must not be called from within a critical section.
            portENTER_CRITICAL();
            ButtonState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
            portEXIT_CRITICAL();
            
            osDelay(xButtonDelay);
            t++;
        } while ((ButtonState == GPIO_PIN_RESET) && (t <= 21));
        
        // did we wait more than 2 seconds?
        if (t >=  20)
        {
            SetAppState(Tare);
        }
    }

#ifdef __cplusplus
}
#endif    

