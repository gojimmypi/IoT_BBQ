/* Includes ------------------------------------------------------------------*/
#include <stm32l4xx_hal.h>
#include <../CMSIS_RTOS/cmsis_os.h>

#include "_Init/startup.h"
#include "_Init/Init_GPIO.h"
#include "Tasks/task_weight_monitor.h"
#include "Flash/Flash_Sim_Demo.h"
#include "LED/LED.h"

// #include "Flash/Flash_Sim_Demo.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
osThreadId LEDThread1Handle, LEDThread2Handle;

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
        switch (current_LED_MODE)
        {
        case IsBlinking:
            current_LED_MODE = AlwaysOn;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            break;
            
        case AlwaysOn:
            current_LED_MODE = AlwaysOff;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        case AlwaysOff:
            current_LED_MODE = IsBlinking;
            break;
            
        default:
            current_LED_MODE = IsBlinking;
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


    // -------------------------------------------------------------------------
    // start of regular app
    // -------------------------------------------------------------------------
    __GPIOA_CLK_ENABLE(); //    __HAL_RCC_GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE(); //    __HAL_RCC_GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();


    // Initialize Port A
    GPIO_InitTypeDef GPIO_InitStructureA;

    GPIO_InitStructureA.Pin = GPIO_PIN_5;

    GPIO_InitStructureA.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructureA.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructureA.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructureA);

    
    // Initialize Port B
    GPIO_InitTypeDef GPIO_InitStructureB;

    GPIO_InitStructureB.Pin = GPIO_PIN_14 | GPIO_PIN_8;

    GPIO_InitStructureB.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructureB.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructureB.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructureB);

    GPIO_InitStructureB.Pin = GPIO_PIN_9;
    GPIO_InitStructureB.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructureB.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructureB.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructureB);
    
    // Initialize Port C
    GPIO_InitTypeDef GPIO_InitStructureC = { 0 }; 

    GPIO_InitStructureC.Pin = GPIO_PIN_13;

    GPIO_InitStructureC.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStructureC.Speed = GPIO_SPEED_LOW;
    GPIO_InitStructureC.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructureC);
    

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);    
    
    // I2C
    ConfigureI2CPins();
    


    // create a SwitchState variable to hold the result of out button press 
    GPIO_PinState SwitchState;
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    
    
    
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

    

    /* Thread 1 definition */
    osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
    /*  Thread 2 definition */
    osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);    
    
  
    /* Start thread 1 */
    LEDThread1Handle = osThreadCreate(osThread(LED1), NULL);
  
    /* Start thread 2 */
    LEDThread2Handle = osThreadCreate(osThread(LED2), NULL);
  
    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    for (;;) ;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
    osSystickHandler();
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
        switch (current_LED_MODE)
        {
        case IsBlinking:
            LED_ON();
            STATE_LED_ON(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            osDelay(555);
		
            STATE_LED_OFF(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            //osThreadSuspend(LEDThread2Handle);
            osDelay(555);
		
            //osThreadResume(LEDThread2Handle);
        
            // TODO for now, we call the scale taks during blinks
            theScaleTask();

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
            current_LED_MODE = IsBlinking;
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
        switch (current_LED_MODE)
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