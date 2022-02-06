// _main_LED_Thread2.h

/* Includes ------------------------------------------------------------------*/
#include "Common/globals.h"
#include <stm32l4xx_hal.h>

#include "_Init/startup.h"
#include "_Init/Init_GPIO.h"
#include "LED/LED.h"

#ifndef __main_LED_Thread2_h
#define __main_LED_Thread2_h

void LED_Thread2(void const *argument);

#endif

