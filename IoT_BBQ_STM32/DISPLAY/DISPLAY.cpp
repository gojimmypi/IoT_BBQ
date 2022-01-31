#include <cmsis_os.h>

#include "DISPLAY.h"
#include <stm32l4xx_hal.h>
#include <SSD1306/ssd1306.h>
#include <SSD1306/SSD1306_demo.h>
#include <UART/UART.h>
#include "Tasks/state_machine.h"
#include "Tasks/task_weight_monitor.h"
#include "DISPLAY/DISPLAY.h"

#ifdef __cplusplus

extern "C" {
#endif

    int DISPLAY_VERSION() {
        return 1;
    }

    void DISPLAY_Thread1(void const* argument) {
        (void)argument;
        static const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
        static long CurrentTankWeight = 0;
        static const int bufferLenth = 20;
        static uint8_t WeightMessage[bufferLenth] = "Weight = ";
        static uint8_t CrLf[bufferLenth] = "\n\r";
       
        for (;;)
        {
            switch (GetAppState())
            {
            case Running:
                ssd1306_Fill(Black);
                CurrentTankWeight = GetScaleWeight();
                UART_TxMessageIntValue(WeightMessage, bufferLenth, CurrentTankWeight);
                UART_TxMessage(CrLf, bufferLenth);
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

