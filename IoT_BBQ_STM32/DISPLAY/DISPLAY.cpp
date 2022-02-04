#include <cmsis_os.h>

#include "DISPLAY.h"
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

extern "C" {
#endif

    int DISPLAY_VERSION() {
        return 1;
    }

    void DISPLAY_Thread1(void const* argument) {
        (void)argument;
        static const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
        static long CurrentTankWeight = 0;
        static uint8_t WeightMessage[] = "Weight = ";
        static uint8_t CrLf[] = "\n\r";
       
        static uint8_t PressureMessage[] = "Pressure = ";
        static uint8_t HumidityMessage[] = "Humidity = ";
        static uint8_t TemperatureMessage[] = "Temperature = ";    
        static uint8_t ThisTimerMessage[] = "Timer = 0x";
        float CurrentPressureValue = 0;
        
        for (;;)
        {
            switch (GetAppState())
            {
            case Running:
                ssd1306_Fill(Black);
                
//                portENTER_CRITICAL(); // this wrapper causes a hard fault upon exit
                CurrentTankWeight = GetScaleWeight();
//                portEXIT_CRITICAL();  

                osDelay(xDelay);
                
                portENTER_CRITICAL();
                CurrentPressureValue = BSP_PSENSOR_ReadPressure(); 
                
                portEXIT_CRITICAL();  
                
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

