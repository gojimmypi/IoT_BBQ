#include <cmsis_os.h>


#ifdef __cplusplus

extern "C"
{
#endif

#include "../HX711/HX711.h"
#include "task_weight_monitor.h"
    
    // SemaphoreHandle_t xHX711_Semaphore = NULL;
    SemaphoreHandle_t xHX711_Semaphore = xSemaphoreCreateMutex();
    static double t = 0;
    static bool IsInitialized = false;
    
    static HX711 scale; 
    
    void GetScaleWeight()
    {
        if (xHX711_Semaphore != NULL)
        {
            /* See if we can obtain the semaphore.  If the semaphore is not
            available wait 10 ticks to see if it becomes free. */
            if (xSemaphoreTake(xHX711_Semaphore, (TickType_t) 10) == pdTRUE)
            {
                /* We were able to obtain the semaphore and can now access the
                shared resource. */

                /* ... */
                if (IsInitialized)
                {
                    // the scale is already initialized
                }
                else 
                {
                    scale.begin(GPIO_PIN_9, GPIO_PIN_8);
                    IsInitialized = true;
                }
                
                t = scale.read_average(2);


                /* We have finished accessing the shared resource.  Release the
                semaphore. */
                xSemaphoreGive(xHX711_Semaphore);
            }
            else
            {
                osDelay(1000);
                /* We could not obtain the semaphore and can therefore not access
                the shared resource safely. */
            }
        }        

        return;
    }

    void theScaleTask()
    {
        while (1)
        {
            GetScaleWeight();
            osDelay(555);
        }
    }

#ifdef __cplusplus
}
#endif