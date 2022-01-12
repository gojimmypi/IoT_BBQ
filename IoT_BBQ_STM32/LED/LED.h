#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    int LED_VERSION();

	void LED_ON();
	void LED_OFF();
	void STATE_LED_OFF();
	void STATE_LED_ON();

    enum LED_Mode { IsBlinking, AlwaysOn, AlwaysOff };

    volatile static enum LED_Mode current_LED_MODE = IsBlinking; // we'll use a button to trigger an interrupt to set LED mode, starting with blinky


#ifdef __cplusplus
}
#endif     