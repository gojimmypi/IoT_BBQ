#pragma once
#include "../_Init/startup.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void theScaleTask();

    extern SemaphoreHandle_t xHX711_Semaphore;
    long GetScaleWeight();
    
    int GetScaleIsInitialized();

#ifdef __cplusplus
}
#endif
