#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32l4xx_hal.h>
#include <stm32_hal_legacy.h>
	

	int UART_VERSION();
	int UART_init(void);
	void UART_Thread1(void const* argument);

#ifdef __cplusplus
}
#endif     