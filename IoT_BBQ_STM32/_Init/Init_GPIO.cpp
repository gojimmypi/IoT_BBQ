// 
// 
// 
#include "Init_GPIO.h"

#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif


void ConfigureI2CPins2()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    __GPIOC_CLK_ENABLE();
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void GPIO_init();

#ifdef __cplusplus
}
#endif    