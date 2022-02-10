/* Includes ------------------------------------------------------------------*/
#include "Common/globals.h"
#include <stm32l4xx_hal.h>

#include "_Init/startup.h"
#include "_Init/Init_GPIO.h"
#include "Tasks/task_weight_monitor.h"
#include "Flash/Flash_Sim_Demo.h"
#include "LED/LED.h"
#include "UART/UART.h"
#include "DISPLAY/DISPLAY.h"
#include "UART/int_to_string.h"
#include "Tasks/state_machine.h"
#include "LPS22HB/stm32l475e_iot01_psensor.h"
#include "HTS221/stm32l475e_iot01_hsensor.h"
#include "HTS221/stm32l475e_iot01_tsensor.h"
#include "_main_pwm_thread.h"
#include "_main_LED_Thread1.h"
#include "_main_LED_Thread2.h"

// #include "common/stm32l4xx_hal_msp.h"

// #include "Flash/Flash_Sim_Demo.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
osThreadId LEDThread1Handle, LEDThread2Handle;
osThreadId UART_Thread1Handle;
osThreadId DISPLAY_Thread1Handle;

osThreadId PWM_Thread1Handle;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief Interrupt callback for GPIOs
*/


TIM_HandleTypeDef htim2;

void pwm_SystemClock_Config(void);
static void pwm_MX_GPIO_Init(void);
static void pwm_MX_TIM2_Init(void);


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

void pwm_SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = 0;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);


// see startup_stm32l475xx.c 
void TIM2_IRQHandler()
{
    // this handler is the one that actually calls the callbacks
    HAL_TIM_IRQHandler(&htim2);
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void pwm_MX_TIM2_Init(void)
{

    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
    TIM_MasterConfigTypeDef sMasterConfig = { 0 };
    TIM_OC_InitTypeDef sConfigOC = { 0 };

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    // htim2.Init.Period = 4294967295;
    htim2.Init.Period = 500;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */

    /* USER CODE END TIM2_Init 2 */
    HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void pwm_MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}


// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // Check which version of the timer triggered this callback and toggle LED
    if (htim == &htim2)
    {
        // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    //pwm_main();
    
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
    
    LED2_ON();
    LED2_OFF();

    LED2_ON();
    LED2_OFF();

    LED2_ON();
    LED2_OFF();

    static uint8_t CrLf[] = "\n\r";

    if (BSP_PSENSOR_Init() == PSENSOR_OK)
    {
        //        float thisValue = BSP_PSENSOR_ReadPressure();
        //        static uint8_t Message[bufferLenth] = "Pressure = ";
        //        UART_TxMessageIntValue(Message, bufferLenth, (long)thisValue);
        //        UART_TxMessage(CrLf, bufferLenth);
        //        
    }
    else
    {
        // while (1) ; //TODO fix
    }
    
   if (BSP_HSENSOR_Init() == HSENSOR_OK)
   {
//        float thisValue = BSP_HSENSOR_ReadHumidity();
//        static uint8_t Message[bufferLenth] = "Humidity = ";
//        UART_TxMessageIntValue(Message, bufferLenth, (long)thisValue);
//        UART_TxMessage(CrLf, bufferLenth);
   }
    else
    {
        // while (1) ;  //TODO fix
    }

    
   if (BSP_TSENSOR_Init() == TSENSOR_OK)
   {
//        float thisValue = BSP_TSENSOR_ReadTemp();
//        static uint8_t Message[bufferLenth] = "Temperature = ";
//        UART_TxMessageIntValue(Message, bufferLenth, (long)thisValue);
//        UART_TxMessage(CrLf, bufferLenth);
   }
    else
    {
        // while (1) ;  //TODO fix
    }

//    HAL_NVIC_DisableIRQ(DISCOVERY_I2Cx_ER_IRQn);
//    HAL_NVIC_DisableIRQ(DISCOVERY_I2Cx_EV_IRQn);
    

    if (1 == 1)
    {
        pwm_SystemClock_Config();
        pwm_MX_GPIO_Init();
        pwm_MX_TIM2_Init();
    
        //HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
        HAL_TIM_Base_Start_IT(&htim2);
        
    }

    
    // create a SwitchState variable to hold the result of out button press 
    GPIO_PinState SwitchState;

    // a couple of lines for debugging / testing
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    SwitchState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

    SetAppState(Running);

    // See https://www.freertos.org/RTOS-Cortex-M3-M4.html
    // but where is our NVIC_PriorityGroupConfig?
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    /* Thread 1 definition */
    osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
    /*  Thread 2 definition */
    osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);    
    
    /* UART - Serial Port Debug */
    osThreadDef(UART1, UART_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

    osThreadDef(DISPLAY, DISPLAY_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

    osThreadDef(PWM, PWM_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

    
    
    /* Start thread 1 */
    LEDThread1Handle = osThreadCreate(osThread(LED1), NULL);
  
    /* Start thread 2 */
    LEDThread2Handle = osThreadCreate(osThread(LED2), NULL);
  
    /* UART is on a thread */
    // TODO loopback currently disabled; this thread does nothing!
    UART_Thread1Handle = osThreadCreate(osThread(UART1), NULL);
    
    /* the display in on a thread */
    DISPLAY_Thread1Handle = osThreadCreate(osThread(DISPLAY), NULL);

    /* our PWM */
    PWM_Thread1Handle = osThreadCreate(osThread(PWM), NULL);


    // Callbacks disabled
    // htim2.PWM_PulseFinishedCallback = PWM_PulseFinishedCallback;
    // htim2.PeriodElapsedCallback = HAL_TIM_PeriodElapsedCallback;

    // you can use interrupt priorities of 5 to 15 for your interrupts if they make FreeRTOS API calls
    HAL_NVIC_SetPriority(TIM2_IRQn, 15, 14);
    
    // ssd1306_TestFPS() in ssd1306_tests.c and this interrupt enabled causes a hard fault!
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    UART_init();

    /* Start scheduler */
    osKernelStart();


    /* We should never get here as control is now taken by the scheduler */
    for (;;) ;
}

///* Allocate the memory for the heap. */
//#if( configAPPLICATION_ALLOCATED_HEAP == 1 )
//	/* The application writer has already defined the array used for the RTOS
//	heap - probably so it can be placed in a special segment or address. */
//extern uint8_t ucHeap[configTOTAL_HEAP_SIZE];
//#else
//static uint8_t ucHeap[configTOTAL_HEAP_SIZE];
//#endif /* configAPPLICATION_ALLOCATED_HEAP */
//
///* Index into the ucHeap array. */
//static size_t xNextFreeByte = (size_t) 0;




/**
  * @brief  Toggle LED2 thread
  * @param  argument not used
  * @retval None
  */

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