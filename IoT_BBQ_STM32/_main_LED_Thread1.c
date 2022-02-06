// 
// 
// 

#include "_main_LED_Thread1.h"

#include "Common/globals.h"
#include <stm32l4xx_hal.h>

#include "_Init/startup.h"
#include "_Init/Init_GPIO.h"
#include "Tasks/task_weight_monitor.h"
#include "Flash/Flash_Sim_Demo.h"
#include "LED/LED.h"
#include "UART/UART.h"
#include "Tasks/state_machine.h"

#include "LPS22HB/stm32l475e_iot01_psensor.h"
#include "HTS221/stm32l475e_iot01_hsensor.h"
#include "HTS221/stm32l475e_iot01_tsensor.h"


/**
  * @brief  Toggle LED1
  * @param  thread not used
  * @retval None
  */
void LED_Thread1(void const *argument)
{
    (void) argument;
  
    static const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
    static long CurrentTankWeight = 0;
    // static const int bufferLenth = 20;
    static uint8_t WeightMessage[] = "1 Weight = ";
    static uint8_t CrLf[] = "\n\r";
       
    static uint8_t PressureMessage[] = "1 Pressure = ";
    static uint8_t HumidityMessage[] = "1 Humidity = ";
    static uint8_t TemperatureMessage[] = "1 Temperature = ";    
    static uint8_t ThisTimerMessage[] = "1 Timer = 0x";
    float CurrentPressureValue = 0;

    for (;;)
    {
        CurrentTankWeight = GetScaleWeight();

        // this is the only place we read pressure
        portENTER_CRITICAL();
        // TODO consider mutex instead
        CurrentPressureValue = BSP_PSENSOR_ReadPressure(); 
        portEXIT_CRITICAL(); 
                
        UART_TxMessageIntValue(PressureMessage, sizeof(PressureMessage), (long)CurrentPressureValue);
        UART_TxMessage(CrLf, sizeof(CrLf));

        UART_TxMessageIntValue(WeightMessage, sizeof(WeightMessage), CurrentTankWeight);
        UART_TxMessage(CrLf, sizeof(CrLf));
        osDelay(xDelay); 
        
        
        switch (LED_GetMode())
        {
        case IsBlinking:
            LED_ON();
            STATE_LED_ON(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            osDelay((TickType_t)(555 / portTICK_PERIOD_MS));
		
            STATE_LED_OFF(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            osDelay((TickType_t)(555 / portTICK_PERIOD_MS));

            break;

        case AlwaysOn:
            STATE_LED_ON(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            osDelay((TickType_t)(1000 / portTICK_PERIOD_MS)); // no sense in runing hard the whole time if we are not blinking
            break;

        case AlwaysOff:
            STATE_LED_OFF(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            osDelay((TickType_t)(1000 / portTICK_PERIOD_MS)); // no sense in runing hard the whole time if we are not blinking
            break;
            
        default:
            LED_SetMode(IsBlinking);
            break;
        }    
    }
}


