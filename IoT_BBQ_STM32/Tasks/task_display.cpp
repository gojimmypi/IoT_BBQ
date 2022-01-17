// 
// 
// 
#include "task_display.h"
#include <stm32l4xx_hal.h>
#include "../SSD1306/ssd1306.h"

#include <SSD1306/SSD1306_demo.h> // TODO we probably don't actually want the demo in the final product, but perhaps implement a self-test?


#ifdef __cplusplus
extern "C" {
#endif

    int task_display_VERSION() {
        return 1;
    }

    void TheDisplayTask()
    {
        while (1)
        {
            SSD1306_test();
        }
    }


#ifdef __cplusplus
}
#endif    