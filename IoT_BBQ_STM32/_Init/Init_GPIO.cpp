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

    void GPIO_init()
    {
        // -------------------------------------------------------------------------
        // start of regular app
        // -------------------------------------------------------------------------
        __GPIOA_CLK_ENABLE(); //    __HAL_RCC_GPIOA_CLK_ENABLE();
        __GPIOB_CLK_ENABLE(); //    __HAL_RCC_GPIOB_CLK_ENABLE();
        __GPIOC_CLK_ENABLE();
        __GPIOD_CLK_ENABLE();


        // Initialize Port A
        GPIO_InitTypeDef GPIO_InitStructureA;

        GPIO_InitStructureA.Pin = GPIO_PIN_5;

        GPIO_InitStructureA.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructureA.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructureA.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructureA);

    
        // Initialize Port B
        GPIO_InitTypeDef GPIO_InitStructureB;

        GPIO_InitStructureB.Pin = GPIO_PIN_14 | GPIO_PIN_8;

        GPIO_InitStructureB.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructureB.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructureB.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStructureB);

        GPIO_InitStructureB.Pin = GPIO_PIN_9;
        GPIO_InitStructureB.Mode = GPIO_MODE_INPUT;
        GPIO_InitStructureB.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructureB.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStructureB);
    
        // Initialize Port C
        GPIO_InitTypeDef GPIO_InitStructureC = { 0 }; 

        GPIO_InitStructureC.Pin = GPIO_PIN_13;

        GPIO_InitStructureC.Mode = GPIO_MODE_IT_FALLING;
        GPIO_InitStructureC.Speed = GPIO_SPEED_LOW;
        GPIO_InitStructureC.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStructureC);
    

        /* EXTI interrupt init*/
        HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);    
    
        // I2C
        ConfigureI2CPins();
        
    }

#ifdef __cplusplus
}
#endif    