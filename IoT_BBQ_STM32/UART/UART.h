#pragma once
#include "Common/globals.h"

#include <stm32l4xx_hal.h>
#include <stm32_hal_legacy.h>

#ifdef __cplusplus
extern "C" {
#endif

	

	int UART_VERSION();
	int UART_init(void);
    
    // send a message to the UART
    int UART_TxMessage(uint8_t *pData, uint16_t Size);

    // send a message and a value to the UART
    int UART_TxMessageIntValue(uint8_t *pData, uint16_t Size, long Value);
    int UART_TxMessageIntValueHex(uint8_t *pData, uint16_t Size, long Value);
    
	void UART_Thread1(void const* argument);

#ifdef __cplusplus
}
#endif     