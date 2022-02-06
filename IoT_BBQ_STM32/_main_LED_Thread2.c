// 
// 
// 

#include "_main_LED_Thread2.h"


void LED_Thread2(void const *argument)
{
    uint32_t count;
    (void) argument;
  
    for (;;)
    {
        int blink_Count = 0;
        switch (LED_GetMode())
        {
        case IsBlinking:
            blink_Count = 1;
            break;
            
        case AlwaysOn:
            blink_Count = 2;
            break;

        case AlwaysOff:
            blink_Count = 3;
            break;
            
        default:
            blink_Count = 4;
        }    

        for (size_t i = 0; i < blink_Count; i++)
        {
            LED2_TOGGLE();
            osDelay((TickType_t)(200 / portTICK_PERIOD_MS));
            
            LED2_TOGGLE();
            osDelay((TickType_t)(200 / portTICK_PERIOD_MS));
        }        
        osDelay((TickType_t)(2000 / portTICK_PERIOD_MS));
    }
    osDelay((TickType_t)(2000 / portTICK_PERIOD_MS));
}
