#include "Common/globals.h"
#include <stm32l4xx_hal.h>
#include <SSD1306/ssd1306.h>
#include <SSD1306/SSD1306_demo.h>

#include "DISPLAY.h"
#include "BUTTON/button.h"
#include "UART/UART.h"
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

    static const int ValuePositionY = 38;
    static const int LabelPositionY = 16;
    
    // Labels are Font_11x18 at display row 36
    void PrintLabelCenteredAt(int x_pos, char * msg)
    {
        ssd1306_SetCursor(x_pos, LabelPositionY);
        ssd1306_WriteString(msg, Font_11x18, White);
    }    
    
    void PrintLabelCentered(char * msg)
    {
        int ct = 0;
        int w = 0;
        while ((msg[ct] != '\0') && (ct < 32) && (w < SSD1306_WIDTH))
        {
            ct++;
            w += Font_11x18.FontWidth;
        } 
                   
        int x_pos = ((SSD1306_WIDTH >> 1) - (w >> 1)) > 0 ? ((SSD1306_WIDTH >> 1) - (w >> 1)) : 0; 

        PrintLabelCenteredAt(x_pos, msg); 
    }
    
    
    // Values are Font_16x26 at display row 38
    void PrintValueCenteredAt(int x_pos, char * msg)
    {
        ssd1306_SetCursor(x_pos, ValuePositionY);
        ssd1306_WriteString(msg, Font_16x26, White);
    }
    
    void PrintValueCentered(int value)
    {
        char numStr[32];
        int_to_dec(numStr, value);
        char * msg =  (char *)&numStr;
                
        int ct = 0;
        int w = 0;
        while ((msg[ct] != '\0') && (ct < 32) && (w < SSD1306_WIDTH))
        {
            ct++;
            w += Font_16x26.FontWidth; 
        } 
                   
        int x_pos = ((SSD1306_WIDTH >> 1) - (w >> 1)) > 0 ? ((SSD1306_WIDTH >> 1) - (w >> 1)) : 0; 
        
        // TODO test
        x_pos = ((SSD1306_WIDTH >> 1) - (w >> 1)) > 0 ? ((SSD1306_WIDTH >> 1) - (w >> 1)) : 0;
                
        PrintValueCenteredAt(x_pos, msg);
//        ssd1306_SetCursor(x_pos, 38);
//                
//        ssd1306_WriteString(msg, Font_16x26, White);
        
    }
    
    void DISPLAY_Thread1(void const* argument) {
        (void)argument;
        static const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
        static long CurrentTankWeight = 0;
        static uint8_t WeightMessage[] = "Weight";
        static uint8_t CrLf[] = "\n\r";
       
        static uint8_t TareMessage[] = "Tare";
        static uint8_t PressureMessage[] = "Pressure";
        static uint8_t HumidityMessage[] = "Humidity";
        static uint8_t TemperatureMessage[] = "Temperature";    
        static uint8_t ThisTimerMessage[] = "Timer";
        float CurrentPressureValue = 0;
        
        char * msg; 

        if (IsInitialized == 0) {
            ssd1306_Init();
            IsInitialized = 1;
            ssd1306_TestFonts();
            ScaleInit();

        }
    
        
        for (;;)
        {
            // a longpress may change current app state
            CheckForLongPress();
            
            switch (GetAppState())
            {
            case Running:
                
                CurrentTankWeight = GetScaleWeight();

                osDelay(xDelay);
                
                CurrentPressureValue = BSP_PSENSOR_ReadPressure(); 
                
                // the blue section of screen starts at y=16
                ssd1306_Fill(Black);
                
                // the 0-15 yellow + 18 blue font + 7 spacing = 40

                PrintLabelCentered((char *)&WeightMessage);
                
                PrintValueCentered(CurrentTankWeight);
                
                ssd1306_UpdateScreen();
                
//                UART_TxMessageIntValue(PressureMessage, sizeof(PressureMessage), (long)CurrentPressureValue);
//                UART_TxMessage(CrLf, sizeof(CrLf));
//
//                UART_TxMessageIntValue(WeightMessage, sizeof(WeightMessage), CurrentTankWeight);
//                UART_TxMessage(CrLf, sizeof(CrLf));
                osDelay(xDelay); 
                
                break;
            
            case Tare :
                DoScaleTare();
                ssd1306_Fill(Black);
                PrintLabelCentered((char *)&TareMessage);
                PrintValueCentered(CurrentTankWeight);
                ssd1306_UpdateScreen();

                osDelay(xDelay);
                SetAppState(Running);
                break;
                
            case Demo:
            default:
                // be sure to exit promptly during longpress
                ssd1306_TestAll();
                break;
            }
        }
    }
    
#ifdef __cplusplus
}
#endif    

