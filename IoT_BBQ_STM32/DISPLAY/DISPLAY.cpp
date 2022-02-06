#include "DISPLAY.h"
#include "Common/globals.h"
#include <stm32l4xx_hal.h>
#include <SSD1306/ssd1306.h>
#include <SSD1306/SSD1306_demo.h>
#include <UART/UART.h>
#include "Tasks/state_machine.h"
#include "Tasks/task_weight_monitor.h"
#include "DISPLAY/DISPLAY.h"

#include "LPS22HB/stm32l475e_iot01_psensor.h"
#include "HTS221/stm32l475e_iot01_hsensor.h"
#include "HTS221/stm32l475e_iot01_tsensor.h"

#ifdef __cplusplus
#include <SSD1306/ssd1306_tests.h>
#include <UART/int_to_string.h>

extern "C" {
#endif

    int DISPLAY_VERSION() {
        return 1;
    }
    
    static int IsInitialized = 0x0;

    
    void DISPLAY_Thread1(void const* argument) {
        (void)argument;
        static const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
        static long CurrentTankWeight = 0;
        static uint8_t WeightMessage[] = "Weight ";
        static uint8_t CrLf[] = "\n\r";
       
        static uint8_t PressureMessage[] = "Pressure = ";
        static uint8_t HumidityMessage[] = "Humidity = ";
        static uint8_t TemperatureMessage[] = "Temperature = ";    
        static uint8_t ThisTimerMessage[] = "Timer = 0x";
        float CurrentPressureValue = 0;
        
        char * msg; 

        if (IsInitialized == 0) {
            ssd1306_Init();
            IsInitialized = 1;
            ssd1306_TestFonts();
        }
    
        
        for (;;)
        {
            switch (GetAppState())
            {
            case Running:
                
                CurrentTankWeight = GetScaleWeight();

                osDelay(xDelay);
                
                CurrentPressureValue = BSP_PSENSOR_ReadPressure(); 
                
                // the blue section of screen starts at y=16
                ssd1306_Fill(Black);
                ssd1306_SetCursor(40, 16);
                msg = (char *)&WeightMessage;
                ssd1306_WriteString(msg, Font_11x18, White);
                
                // the 0-15 yellow + 18 blue font + 7 spacing = 40
                ssd1306_SetCursor(60, 38);
                static char numStr[32];
                int_to_dec(numStr, CurrentTankWeight);
                msg =  (char *)&numStr;
                ssd1306_WriteString(msg, Font_16x26, White);
                
                ssd1306_UpdateScreen();
                
                UART_TxMessageIntValue(PressureMessage, sizeof(PressureMessage), (long)CurrentPressureValue);
                UART_TxMessage(CrLf, sizeof(CrLf));

                UART_TxMessageIntValue(WeightMessage, sizeof(WeightMessage), CurrentTankWeight);
                UART_TxMessage(CrLf, sizeof(CrLf));
                osDelay(xDelay); 
                
                break;
                
            case Demo:
            default:
                ssd1306_TestAll();
                break;
            }
        }
    }
    
#ifdef __cplusplus
}
#endif    

