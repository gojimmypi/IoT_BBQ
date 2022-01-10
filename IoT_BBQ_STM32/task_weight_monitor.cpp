#include "task_weight_monitor.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include  "HX711.h"
#include "SSD1306_demo.h"

    void theScaleTask()
    {
        SSD1306_test();

        // ssd1306_TestAll();

        GetScaleWeight();
    }
    
#ifdef __cplusplus
}
#endif