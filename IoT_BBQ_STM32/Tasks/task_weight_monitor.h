#pragma once
#include "../_Init/startup.h"

#ifdef __cplusplus
extern "C"
{
#endif

    extern SemaphoreHandle_t xHX711_Semaphore;
    
    int DoScaleTare();
    long GetScaleWeight();
    
    int GetScaleIsInitialized();

#ifdef __cplusplus
}
#endif
