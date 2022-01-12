#include "startup.h"

#include  "../HX711/HX711.h"

#ifdef __cplusplus
extern "C" {
#endif


    HX711 scale; 
    void GetScaleWeight()
    {
        scale.begin(GPIO_PIN_9, GPIO_PIN_8);
        long t = -1;
        t = scale.read();
        t = scale.read();
        t = scale.read();
        return;
    }
    
    //    void SysTick_Handler()
    //    {
    //        return;
    //    }
#ifdef __cplusplus
}
#endif    