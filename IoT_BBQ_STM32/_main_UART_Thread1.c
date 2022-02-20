
#include "Common/globals.h"
#include <stm32l4xx_hal.h>
#include "UART/UART.h"
#include "_main_UART_Thread1.h"

void UART_Thread1(void const* argument) {
    (void)argument;
    const TickType_t xDelay = 1350 / portTICK_PERIOD_MS;
    static uint8_t buffer[1];
    static uint8_t UART_Message[] = "Hello UART!\n\r";
        
    for (;;)
    {
        UART_TxMessage(UART_Message, sizeof(UART_Message));
            
        // don't starve RTOS. yield with delay:
        osDelay(xDelay);
    }
}

