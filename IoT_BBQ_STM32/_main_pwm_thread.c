/* Includes ------------------------------------------------------------------*/
#include "Common/globals.h"
#include <stm32l4xx_hal.h>

#include "_Init/startup.h"
#include "_Init/Init_GPIO.h"
#include "Tasks/task_weight_monitor.h"
#include "Flash/Flash_Sim_Demo.h"
#include "Flash/spi_flash.h"

#include "LED/LED.h"
#include "UART/UART.h"
#include "DISPLAY/DISPLAY.h"
#include "UART/int_to_string.h"
#include "Tasks/state_machine.h"
#include "LPS22HB/stm32l475e_iot01_psensor.h"
#include "HTS221/stm32l475e_iot01_hsensor.h"
#include "HTS221/stm32l475e_iot01_tsensor.h"

#define configADJUSTED_HEAP_SIZE	( configTOTAL_HEAP_SIZE - portBYTE_ALIGNMENT )

static uint8_t buffer[] = "Global Variable: Hello World";

static int myNotInitializedVariable;
static int myInitializedVariable = 42;

// How many bits are one in a given 32-bit uint?

static size_t BitCount(uint32_t n)
{
    size_t res = 0;
    uint32_t pos = 1; // ensure this is the same bit size as parameter!
    for (size_t i = 0; i < 32; i++)
    {
        // if the and operation is non-zero, we found a 1 bit
        if (n & pos)
        {
            res++;  
        }
        
        // get ready to look at the next bit position
        pos = (pos << 1);

        // no sensee in continuing if we found the answer
        if (pos > n)
        {
            break;
        }
    }
    return res;
}

static size_t BitCountLeadingZeros(uint32_t n)
{
    const int BitsToCount = 32;
    size_t res = 0;
    uint32_t pos = 1; // ensure this is the same bit size as parameter!
    
    for (size_t i = 0; i < BitsToCount; i++)
    {
        // get ready to look at the next bit position
        pos = (pos << 1);

        // no sensee in continuing if we found the answer (in this case the mask is larger than our inspection number
        if (pos > n)
        {
            res = (i + 1); // zero based, so we need to add one
            break;
        }
    }
    
    // if we actually found leading zeros, the quantity is the total number of bits minus the position where we stopped looking
    if (res)
    {
        res = BitsToCount - res;  
    }
    
    return res;
}

/*
    On [-1000..+1000] range with 0.001 step average error is: +/- 0.000011, max error: +/- 0.000060
    On [-100..+100] range with 0.001 step average error is:   +/- 0.000009, max error: +/- 0.000034
    On [-10..+10] range with 0.001 step average error is:     +/- 0.000009, max error: +/- 0.000030
    Error distribution ensures there's no discontinuity.
*/

const double PI          = 3.141592653589793;
const double HALF_PI     = 1.570796326794897;
const double DOUBLE_PI   = 6.283185307179586;
const double SIN_CURVE_A = 0.0415896;
const double SIN_CURVE_B = 0.00129810625032;

double cos1(double x) {
    if (x < 0) {
        int q = -x / DOUBLE_PI;
        q += 1;
        double y = q * DOUBLE_PI;
        x = -(x - y);
    }
    if (x >= DOUBLE_PI) {
        int q = x / DOUBLE_PI;
        double y = q * DOUBLE_PI;
        x = x - y;
    }
    int s = 1;
    if (x >= PI) {
        s = -1;
        x -= PI;
    }
    if (x > HALF_PI) {
        x = PI - x;
        s = -s;
    }
    double z = x * x;
    double r = z * (z * (SIN_CURVE_A - SIN_CURVE_B * z) - 0.5) + 1.0;
    if (r > 1.0) r = r - 2.0;
    if (s > 0) return r;
    else return -r;
}

double sin1(double x) {
    return cos1(x - HALF_PI);
}



void PWM_Thread1(void const *argument)
{
    
    flash_test();


    int n;
    n = BitCount(0xF); // 4
    n = BitCount(0x0); // 0
    n = BitCount(0x1); // 1
    n = BitCount(21); // 3
    n = BitCount(0xFFFF); // 16
    n = BitCount(0xFF000000); // 8
    n = BitCount(0xFFFFFFFF); // 32

    n = BitCountLeadingZeros(0xF); // 28
    n = BitCountLeadingZeros(0x0); // an interesting case that "0" is not counted in the other 31 digits of leading zeros
    n = BitCountLeadingZeros(0x1); // also 31
    n = BitCountLeadingZeros(21); // 27 leading zeros for 10101
    n = BitCountLeadingZeros(0xFFFF); // 16
    n = BitCountLeadingZeros(0xFF000000); // 0
    n = BitCountLeadingZeros(0xFFFFFFFF); // 0
    
    // long thisStackSize = __process_stack_size__; // this does not work (why??)
        
    // see https://stackoverflow.com/questions/20059673/print-out-value-of-stack-pointer
    // locally allocated variables are on the stack, so get the address:
    void* p = NULL;
    volatile long myStackPointer = (long)((void*)&p);
    
    void* q = NULL;
    volatile long myStackPointer2 = (long)((void*)&q);

    int* r = (int*)0xBEAD;
    volatile long myStackPointer3 = (long)((void*)&r);
        
    static uint8_t CrLf[] = "\n\r";
       
    static uint8_t StackMessage[]        = "Stack     = ";
    static uint8_t StackMessageHex[]     = "Stack     = 0x";
    static uint8_t HeapMessageHex[]      = "Heap      = 0x";

    static uint8_t HeapMessageSizeHex[]  = "Heap Size = 0x";
    static uint8_t HeapMessageFreeHex[]  = "Heap Free = 0x";
 
    static uint8_t InitMessageHex[]      = "Initialized     = 0x";
    static uint8_t NotInitMessageHex[]   = "Not Initialized = 0x";

    long myHeapSize = configADJUSTED_HEAP_SIZE;
        
    size_t myHeapFreeSize = xPortGetFreeHeapSize();
   
    volatile long myHeapPointer = (long)pvPortMalloc(0); // this returns a NULL pointer
    myHeapPointer = (long)pvPortMalloc(1); // a non-zero param returns heap pointer

    // UART_init();
    
    // Print global variable buffer
    UART_TxMessage(buffer, sizeof(buffer));
    UART_TxMessage(CrLf, sizeof(CrLf));

    // show decimal value of Stack pointer
    UART_TxMessageIntValue(StackMessage, sizeof(StackMessage), myStackPointer);
    UART_TxMessage(CrLf, sizeof(CrLf));

    // show hex value of current stack pointer
    UART_TxMessageIntValueHex(StackMessageHex, sizeof(StackMessageHex), myStackPointer);
    UART_TxMessage(CrLf, sizeof(CrLf));

    // show hex value of current heap pointer (xstart is static, not available)
    UART_TxMessageIntValueHex(HeapMessageHex, sizeof(HeapMessageHex), myHeapPointer);
    UART_TxMessage(CrLf, sizeof(CrLf));

    // show hex value of current heap size
    UART_TxMessageIntValueHex(HeapMessageSizeHex, sizeof(HeapMessageSizeHex), myHeapSize);
    UART_TxMessage(CrLf, sizeof(CrLf));

    // show free heap free size
    UART_TxMessageIntValueHex(HeapMessageFreeHex, sizeof(HeapMessageFreeHex), myHeapFreeSize);
    UART_TxMessage(CrLf, sizeof(CrLf));

    
    UART_TxMessage(CrLf, sizeof(CrLf));
    UART_TxMessage(CrLf, sizeof(CrLf));
    UART_TxMessage(CrLf, sizeof(CrLf));
    UART_TxMessage(CrLf, sizeof(CrLf));

    // show Initialized Variable Address
    UART_TxMessageIntValueHex(InitMessageHex, sizeof(InitMessageHex), (long)&myInitializedVariable);
    UART_TxMessage(CrLf, sizeof(CrLf));

    // show Uninitialized Variable Address
    UART_TxMessageIntValueHex(NotInitMessageHex, sizeof(NotInitMessageHex), (long)&myNotInitializedVariable);
    UART_TxMessage(CrLf, sizeof(CrLf));

    volatile int checkValue = myInitializedVariable;
    
    
    //    static char numStr[32];
    //    int_to_string(numStr, 32, 42);
    //    UART_TxMessage(numStr, 32);
    
        // workspace/STM32CubeL4/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_1.c
    pvPortMalloc(0);
    myHeapFreeSize = xPortGetFreeHeapSize();
    pvPortMalloc(0x10);
    myHeapFreeSize = xPortGetFreeHeapSize();
    pvPortMalloc(0x21);
    myHeapFreeSize = xPortGetFreeHeapSize();
    pvPortMalloc(0);

    
    (void) argument;
    int32_t CH1_DC = 0;
 
  
    static uint8_t PressureMessage[] = "Pressure = ";
    static uint8_t HumidityMessage[] = "Humidity = ";
    static uint8_t TemperatureMessage[] = "Temperature = ";    
    static uint8_t ThisTimerMessage[] = "Timer = 0x";
    float thisValue;
    
    for (;;)
    {

        while (1)
        {
            //            int timerValue = __HAL_TIM_GET_COUNTER(&htim2);
            //
            //            // UART_TxMessageIntValueHex(ThisTimerMessage, bufferLenth, (long)htim2.Instance->CNT);
            //            UART_TxMessageIntValueHex(ThisTimerMessage, bufferLenth, (long)timerValue);
            //            UART_TxMessage(CrLf, bufferLenth);
            
            //            osDelay(2000);  // This causes a hard fault!
            static const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;
            osDelay(xDelay); // this does NOT cause a hard fault

            portENTER_CRITICAL();
            // TODO consider mutex instead
            thisValue = BSP_PSENSOR_ReadPressure();
            portEXIT_CRITICAL();
            
            UART_TxMessageIntValue(PressureMessage, sizeof(PressureMessage), (long)thisValue);
            UART_TxMessage(CrLf, sizeof(CrLf));
            osDelay(2000);
            
            //            thisValue = BSP_HSENSOR_ReadHumidity();
            //            UART_TxMessageIntValue(HumidityMessage, bufferLenth, (long)thisValue);
            //            UART_TxMessage(CrLf, bufferLenth);
            //            
            //            portENTER_CRITICAL();
            //            thisValue = BSP_TSENSOR_ReadTemp();
            //            portEXIT_CRITICAL();   
            //            
            //            UART_TxMessageIntValue(TemperatureMessage, bufferLenth, (long)thisValue);
            //            UART_TxMessage(CrLf, bufferLenth);
            //            
            //            osDelay(2000);
            
            //            while (CH1_DC < 65535)
            //            {
            //                TIM2->CCR1 = CH1_DC;
            //                CH1_DC += 70;
            //                osDelay(10);
            //            }
            //            while (CH1_DC > 0)
            //            {
            //                TIM2->CCR1 = CH1_DC;
            //                CH1_DC -= 70;
            //                osDelay(10);
            //            }
        }
        
    }
}

