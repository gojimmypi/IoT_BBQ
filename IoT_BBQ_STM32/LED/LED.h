#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    enum LED_Mode { IsBlinking, AlwaysOn, AlwaysOff };

    int LED_VERSION();

    int LED_init();
    int LED2_init();
    
	void LED_ON();
	void LED_OFF();
    void LED_TOGGLE();
    
	void STATE_LED_OFF();
	void STATE_LED_ON();


    void LED2_ON();
    void LED2_OFF();
    void LED2_TOGGLE();
        
    // The "state of an LED is on or off; the "Mode" is one of the LED_Mode enum values
    enum LED_Mode LED_GetMode();
    int LED_SetMode(enum LED_Mode NewMode);



#ifdef __cplusplus
}
#endif     