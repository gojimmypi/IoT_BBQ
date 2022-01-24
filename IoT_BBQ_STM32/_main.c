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
#include  "UART/int_to_string.h"
#include <stm32l4xx_hal.h>

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

#define bufferLenth 80
static uint8_t buffer[bufferLenth] = "Global Variable: Hello World";


/* Private function prototypes -----------------------------------------------*/
static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);

static void PWM_Thread1(void const *argument);

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

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
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
    htim2.Init.Period = 4294967295;
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
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
}


int pwm_main(void)
{    int32_t CH1_DC = 0;
 
    HAL_Init();
    pwm_SystemClock_Config();
    pwm_MX_GPIO_Init();
    MX_TIM2_Init();
    
    // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim2);
    
    while (1)
    {
        while (CH1_DC < 65535)
        {
            TIM2->CCR1 = CH1_DC;
            CH1_DC += 70;
            // osDelay(555);
        }
        while (CH1_DC > 0)
        {
            TIM2->CCR1 = CH1_DC;
            CH1_DC -= 70;
            // osDelay(555);
        }
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

    UART_init();



    pwm_SystemClock_Config();
    pwm_MX_GPIO_Init();
    MX_TIM2_Init();
    
    //HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim2);

    
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

    osThreadDef(PWM, PWM_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

    
    
    /* Start thread 1 */
    LEDThread1Handle = osThreadCreate(osThread(LED1), NULL);
  
    /* Start thread 2 */
    LEDThread2Handle = osThreadCreate(osThread(LED2), NULL);
  
    /* UART is on a thread */
    UART_Thread1Handle = osThreadCreate(osThread(UART1), NULL);
    
    /* the display in on a thread */
    DISPLAY_Thread1Handle = osThreadCreate(osThread(DISPLAY), NULL);

    /* our PWM */
    PWM_Thread1Handle = osThreadCreate(osThread(PWM), NULL);

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

#define configADJUSTED_HEAP_SIZE	( configTOTAL_HEAP_SIZE - portBYTE_ALIGNMENT )

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



static void PWM_Thread1(void const *argument)
{
    // long thisStackSize = __process_stack_size__; // this does not work (why??)
        
    // see https://stackoverflow.com/questions/20059673/print-out-value-of-stack-pointer
    // locally allocated variables are on the stack, so get the address:
    void* p = NULL;
    volatile long myStackPointer = (long)((void*)&p);
    
    void* q = NULL;
    volatile long myStackPointer2 = (long)((void*)&q);

    int* r = (int*)0xBEAD;
    volatile long myStackPointer3 = (long)((void*)&r);
        
    static uint8_t CrLf[bufferLenth] = "\n\r";
       
    static uint8_t StackMessage[bufferLenth]        = "Stack     = ";
    static uint8_t StackMessageHex[bufferLenth]     = "Stack     = 0x";
    static uint8_t HeapMessageHex[bufferLenth]      = "Heap      = 0x";

    static uint8_t HeapMessageSizeHex[bufferLenth]  = "Heap Size = 0x";
    static uint8_t HeapMessageFreeHex[bufferLenth]  = "Heap Free = 0x";
 
    long myHeapSize = configADJUSTED_HEAP_SIZE;
        
    size_t myHeapFreeSize = xPortGetFreeHeapSize();
   
    volatile long myHeapPointer = pvPortMalloc(0); // this returns a NULL pointer
    myHeapPointer = (long)pvPortMalloc(1); // a non-zero param returns heap pointer

    UART_init();
    
    // Print global variable buffer
    UART_TxMessage(buffer, bufferLenth);
    UART_TxMessage(CrLf, bufferLenth);

    // show decimal value of Stack pointer
    UART_TxMessageIntValue(StackMessage, bufferLenth, myStackPointer);
    UART_TxMessage(CrLf, bufferLenth);

    // show hex value of current stack pointer
    UART_TxMessageIntValueHex(StackMessageHex, bufferLenth, myStackPointer);
    UART_TxMessage(CrLf, bufferLenth);

    // show hex value of current heap pointer (xstart is static, not available)
    UART_TxMessageIntValueHex(HeapMessageHex, bufferLenth, myHeapPointer);
    UART_TxMessage(CrLf, bufferLenth);

    // show hex value of current heap size
    UART_TxMessageIntValueHex(HeapMessageSizeHex, bufferLenth, myHeapSize);
    UART_TxMessage(CrLf, bufferLenth);

    // show free heap free size
    UART_TxMessageIntValueHex(HeapMessageFreeHex, bufferLenth, myHeapFreeSize);
    UART_TxMessage(CrLf, bufferLenth);

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
 
  
    for (;;)
    {
            
        while (1)
        {
            osDelay(10);
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
            LED2_TOGGLE();
            osDelay(200);
            
            LED2_TOGGLE();
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