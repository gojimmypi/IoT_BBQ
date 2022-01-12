#ifdef __cplusplus
extern "C"
{
#endif

#include "../HX711/HX711.h"
#include "../SSD1306/ssd1306.h"
#include "./Tasks/task_weight_monitor.h"

#include "../SSD1306/ssd1306_demo.h" // TODO - remove, as only for temporary SSD1306_test();

    void theScaleTask()
    {
        SSD1306_test();

        // ssd1306_TestAll();

        GetScaleWeight();
    }
    
#ifdef __cplusplus
}
#endif