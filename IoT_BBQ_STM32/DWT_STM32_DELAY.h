#pragma once
#ifndef DWT_STM32_DELAY_H
#define DWT_STM32_DELAY_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
    // see https://community.st.com/s/question/0D50X0000BGkxmCSQR/stm32l462-delay-in-a-microsecondus
 
// #include "stm32f1xx_hal.h"
    uint32_t DWT_Delay_Init(void);
 
 
 
    /**
     * @brief  This function provides a delay (in microseconds)
     * @param  microseconds: delay in microseconds
     */
    __STATIC_INLINE void DWT_Delay_us(volatile uint32_t microseconds)
    {
        uint32_t clk_cycle_start = DWT->CYCCNT;
 
        /* Go to number of cycles for system */
        microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);
 
        /* Delay till end */
// TODO        while ((DWT->CYCCNT - clk_cycle_start) < microseconds) ;
    }
 
 
#ifdef __cplusplus
}
#endif
 
#endif