/**
******************************************************************************
* @file    FreeRTOS/FreeRTOS_ThreadCreation/Src/main.c
* @author  MCD Application Team
* @version V1.2.2
* @date    25-May-2015
* @brief   Main program body
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        http://www.st.com/software_license_agreement_liberty_v2
*
* Unless required by applicable law or agreed to in writing, software 
* distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include <stm32l4xx_hal.h>
#include <../CMSIS_RTOS/cmsis_os.h>
#include "startup.h"
#include "task_weight_monitor.h"

#include "spi_flash.h"

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
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* STM32F4xx HAL library initialization:
         - Configure the Flash prefetch, instruction and Data caches
         - Configure the Systick to generate an interrupt each 1 msec
         - Set NVIC Group Priority to 4
         - Global MSP (MCU Support Package) initialization
    */
    HAL_Init();  

    // 
    // -------------------------------------------------------------------------
    // flash testing for Exercise 3b
    // -------------------------------------------------------------------------
    //
    
    // initialize SPI Flash
    sFLASH_Init();

#ifdef is_spi_flash_simulation
    uint32_t UsingFlashAddress = 0x1000;
    uint32_t MaxFlashTestSize  = 0x1FFF;
    
    // when writing NULL during simulation, the parameters are actually setup for stating address and max size
    sFLASH_WriteBuffer(NULL, UsingFlashAddress, MaxFlashTestSize);
#endif
    
    // setup some data
    uint8_t someData = 42;
    uint8_t someOtherData = 0x55;
    
    uint8_t* otherData = &someOtherData;
    uint8_t* thisFlashData = &someData;
    uint32_t thisFlashAddress = 0x1234;
    uint32_t thisFlashTestSize = 1;

    // sample write
    sFLASH_WriteBuffer(thisFlashData, thisFlashAddress, thisFlashTestSize);


    // sample read
    sFLASH_ReadBuffer(otherData, thisFlashAddress, thisFlashTestSize);
    
    
    // sample erase
    sFLASH_EraseBulk();

    
    // sample read after erase
    sFLASH_ReadBuffer(thisFlashData, thisFlashAddress, thisFlashTestSize);
    

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
    GPIO_InitTypeDef GPIO_InitStructureC;

    GPIO_InitStructureC.Pin = GPIO_PIN_13;

    GPIO_InitStructureC.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructureC.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructureC.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructureC);
    
    GPIO_PinState SwitchState;
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    
    
    
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

    
    /* Thread 1 definition */
    // the macro gives a compiler warning in C++
    // osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
//    char* LED1_threadname = (char*)"LED1";
//    const osThreadDef_t os_thread_def_LED1 = { LED1_threadname, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE };
 
    
    /*  Thread 2 definition */
    // the macro gives a compiler warning in C++  // osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
//    char* LED2_threadname = (char*)"LED2";
//    const osThreadDef_t os_thread_def_LED2 = { LED2_threadname, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE };

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
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        osDelay(2000);
		
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        osThreadSuspend(LEDThread2Handle);
        osDelay(2000);
		
        osThreadResume(LEDThread2Handle);
        
        theScaleTask();
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
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
        osDelay(200);
    }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/