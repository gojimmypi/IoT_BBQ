#include <cmsis_os.h>

// 
// 
// 

#include "state_machine.h"
#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

    volatile static enum AppState current_app_state = Startup; // we'll use a button to trigger an interrupt to set LED mode, starting with blinky

    int state_machine_VERSION() {
        return 1;
    }
    
    //
    // Get the current application state
    //
    enum AppState GetCurrentAppState()
    {
        enum AppState TheValue;
        
        // FreeRTOS API functions must not be called from within a critical section.
        portENTER_CRITICAL();
        
        TheValue = current_app_state;

        portEXIT_CRITICAL();

        return TheValue;
        
    };
    
    //
    // Set new application state
    //
    int SetAppState(enum AppState NewState)
    {
        portENTER_CRITICAL();
        
        current_app_state = NewState;

        portEXIT_CRITICAL();

        return 0; // TODO check for error, return non-zero
    }

#ifdef __cplusplus
}
#endif    