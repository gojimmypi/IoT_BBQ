#include "../UART/UART.h"
#include <stm32l4xx_hal.h>
// #include <stm32_hal_legacy.h>

#ifdef __cplusplus
extern "C" {
#endif


    int UART_VERSION() {
        return 1;
    }



    //    void SysTick_Handler(void)
    //{
    //    HAL_IncTick();
    //    HAL_SYSTICK_IRQHandler();
    //}
    static UART_HandleTypeDef s_UARTHandle = UART_HandleTypeDef();

    void UART_Thread1(void const* argument) {
        (void)argument;

        for (;;)
        {
            static uint8_t buffer[1];
            HAL_UART_Receive(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
            HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
        }
    }

    int UART_init(void)
    {
        s_UARTHandle = UART_HandleTypeDef();

        __UART4_CLK_ENABLE();
        __GPIOA_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.Pin = GPIO_PIN_1;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Alternate = GPIO_AF8_UART4;
        GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStructure.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.Pin = GPIO_PIN_0;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

        s_UARTHandle.Instance = UART4;
        s_UARTHandle.Init.BaudRate = 115200;
        s_UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;
        s_UARTHandle.Init.StopBits = UART_STOPBITS_1;
        s_UARTHandle.Init.Parity = UART_PARITY_NONE;
        s_UARTHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        s_UARTHandle.Init.Mode = UART_MODE_TX_RX;

        if (HAL_UART_Init(&s_UARTHandle) != HAL_OK)
            asm("bkpt 255");
    }

#ifdef __cplusplus
}
#endif    