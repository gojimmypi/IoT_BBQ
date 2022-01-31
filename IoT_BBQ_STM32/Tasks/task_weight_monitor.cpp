#include <cmsis_os.h>


#ifdef __cplusplus

extern "C"
{
#endif

#include "../HX711/HX711.h"
#include "task_weight_monitor.h"
    
    // SemaphoreHandle_t xHX711_Semaphore = NULL;
    SemaphoreHandle_t xHX711_Semaphore = xSemaphoreCreateMutex();
    static long TheScaleWeight = 0;
    static bool IsInitialized = false;
    
    static HX711 scale; 
    
    long GetScaleWeight()
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
                    scale.power_down();
                    osDelay(5000);
                    scale.begin(0, 0); // TODO params not current used! hard coded
                    IsInitialized = true;

                    // calibrate
                    int DoCalibrate = 0;
                    if (DoCalibrate == 1)
                    {
                        scale.set_scale();
                    
                        // Step 2 Call tare() with no parameter.
                        scale.tare();

                        // Step 3 Place a known weight on the scale and call get_units(10).
                        float a = scale.get_units(10);

                        // Divide the result in step 3 to your known weight.You should get about the parameter you need to pass to set_scale().
                        float theValue = a / 2;
                    
                        scale.set_scale(theValue);
                        }
                    // Step 1 Call set_scale() with no parameter.
                }
                
                TheScaleWeight = scale.get_units(10);


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
        else
        {
            // TODO how did we end up here? xHX711_Semaphore should never be null
        }

        return TheScaleWeight;
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