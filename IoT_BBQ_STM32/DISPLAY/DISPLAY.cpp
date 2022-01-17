#include "DISPLAY.h"
#include <stm32l4xx_hal.h>

#ifdef __cplusplus
#include <SSD1306/SSD1306_demo.h>

extern "C" {
#endif

    int DISPLAY_VERSION() {
        return 1;
    }

    void DISPLAY_Thread1(void const* argument) {
        (void)argument;

        for (;;)
        {
            SSD1306_test();
        }
    }
    
#ifdef __cplusplus
}
#endif    

