/* Includes ------------------------------------------------------------------*/
#include <stm32l4xx_hal.h>
#include <../CMSIS_RTOS/cmsis_os.h>

#include "_Init/startup.h"
#include "_Init/Init_GPIO.h"
#include "Tasks/task_weight_monitor.h"
#include "Flash/Flash_Sim_Demo.h"
#include "LED/LED.h"
#include "UART/UART.h"
#include  "DISPLAY/DISPLAY.h"

// #include "Flash/Flash_Sim_Demo.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
osThreadId LEDThread1Handle, LEDThread2Handle;
osThreadId UART_Thread1Handle;
osThreadId DISPLAY_Thread1Handle;

/* Private function prototypes -----------------------------------------------*/
static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);

/* Private functions ---------------------------------------------------------*/

/**
* @brief Interrupt callback for GPIOs
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13)
    {
        switch (LED_GetMode())
        {
        case IsBlinking:
            LED_SetMode(AlwaysOn);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            break;
            
        case AlwaysOn:
            LED_SetMode(AlwaysOff);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        case AlwaysOff:
            LED_SetMode(IsBlinking);
            break;
            
        default:
            LED_SetMode(IsBlinking);
            break;
        }    
    }
    // when done here, recall we'll return to EXTI15_10_IRQHandler()
}

// EXTI15_10_IRQHandler is a predefined name. See STM32L4xx_HAL_Driver\Src\stm32l4xx_hal_gpio.c
void EXTI15_10_IRQHandler(void)
{
    // when an interrupt occurs, we arrive here, but we need to figure out which pin triggered it.
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);  // check to see if this is our interrupt. if so clear it and call the HAL_GPIO_EXTI_Callback(GPIO_Pin)
}



/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    // run flash simulation demo
    Flash_Sim_Demo();


    /* STM32F4xx HAL library initialization:
         - Configure the Flash prefetch, instruction and Data caches
         - Configure the Systick to generate an interrupt each 1 msec
         - Set NVIC Group Priority to 4
         - Global MSP (MCU Support Package) initialization
    */
    HAL_Init();  

    GPIO_init();    

    UART_init();



    // create a SwitchState variable to hold the result of out button press 
    GPIO_PinState SwitchState;

    // a couple of lines for debugging / testing
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

    

    /* Thread 1 definition */
    osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
    /*  Thread 2 definition */
    osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);    
    
    /* UART - Serial Port Debug */
    osThreadDef(UART1, UART_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

    osThreadDef(DISPLAY, DISPLAY_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

    
    /* Start thread 1 */
    LEDThread1Handle = osThreadCreate(osThread(LED1), NULL);
  
    /* Start thread 2 */
    LEDThread2Handle = osThreadCreate(osThread(LED2), NULL);
  
    /* UART is on a thread */
    UART_Thread1Handle = osThreadCreate(osThread(UART1), NULL);
    
    /* the display in on a thread */
    DISPLAY_Thread1Handle = osThreadCreate(osThread(DISPLAY), NULL);

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    for (;;) ;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
    osSystickHandler();

    HAL_SYSTICK_IRQHandler(); // for UART
}




/**
  * @brief  Toggle LED1
  * @param  thread not used
  * @retval None
  */
static void LED_Thread1(void const *argument)
{
    (void) argument;
  
    for (;;)
    {
        switch (LED_GetMode())
        {
        case IsBlinking:
            LED_ON();
            STATE_LED_ON(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            osDelay(555);
		
            STATE_LED_OFF(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            //osThreadSuspend(LEDThread2Handle);
            osDelay(555);
		
            //osThreadResume(LEDThread2Handle);
        
            // TODO for now, we call the scale tasks during blinks
            theScaleTask(); // TODO move to own thread

            break;

        case AlwaysOn:
            STATE_LED_ON();      // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            osDelay(2000); // no sense in runing hard the whole time if we are not blinking
            break;

        case AlwaysOff:
            STATE_LED_OFF();     // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            //osThreadSuspend(LEDThread2Handle);
            osDelay(2000); // no sense in runing hard the whole time if we are not blinking
            //osThreadResume(LEDThread2Handle);
            break;
            
        default:
            LED_SetMode(IsBlinking);
            break;
        }    
    }
}

/**
  * @brief  Toggle LED2 thread
  * @param  argument not used
  * @retval None
  */
static void LED_Thread2(void const *argument)
{
    uint32_t count;
    (void) argument;
  
    for (;;)
    {
        int blink_Count = 0;
        switch (LED_GetMode())
        {
        case IsBlinking:
            blink_Count = 1;
            break;
            
        case AlwaysOn:
            blink_Count = 2;
            break;

        case AlwaysOff:
            blink_Count = 3;
            break;
            
        default:
            blink_Count = 4;
        }    

        for (size_t i = 0; i < blink_Count; i++)
        {
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
            osDelay(200);
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
            osDelay(200);
        }        
        osDelay(2000);
    }
    osDelay(2000);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

     /* Infinite loop */
    while (1)
    {
    }
}
#endif