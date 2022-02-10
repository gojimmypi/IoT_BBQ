/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "SSD1306/ssd1306_tests.h"

#include "SSD1306_demo.h"
#include "SSD1306/ssd1306_conf.h"
//#include "SSD1306/ssd1306_tests.h"
#include <stdbool.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef SSD1306_I2C_PORT;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_I2C3_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void SSD1306_test_init() {
    // HAL_GPIO_WritePin(SPI_Led_GPIO_Port, SPI_Led_Pin, GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(I2C_Led_GPIO_Port, I2C_Led_Pin, GPIO_PIN_RESET);
}

//void SSD1306_test_loop() {
//    // Blue button pressed - repeast the test
//    // if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
//        // Indicate that test is running
//        // HAL_GPIO_WritePin(I2C_Led_GPIO_Port, I2C_Led_Pin, GPIO_PIN_SET);
//
//        ssd1306_TestAll();
//
//        // HAL_GPIO_WritePin(SPI_Led_GPIO_Port, SPI_Led_Pin, GPIO_PIN_RESET);
//        // HAL_GPIO_WritePin(I2C_Led_GPIO_Port, I2C_Led_Pin, GPIO_PIN_RESET);
//    // }
//
//    // Blink an LED
//    // HAL_GPIO_TogglePin(I2C_Led_GPIO_Port, I2C_Led_Pin);
//    // HAL_Delay(150);
//}

/* USER CODE END 0 */

static void MX_GPIO_Init(void)
{


    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

 
}




void SSD1306_test()
{

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//  HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
//  SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C3_Init();

    /* USER CODE BEGIN 2 */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    SSD1306_test_init();
    {
        // SSD1306_test_loop();
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

    }
    /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

//    RCC_OscInitTypeDef RCC_OscInitStruct;
//    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = 0;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    //    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
//        _Error_Handler(__FILE__, __LINE__);
    }

    /**Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
//        _Error_Handler(__FILE__, __LINE__);
    }

    /**Configure the Systick interrupt time
    */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    /**Configure the Systick
    */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/* I2C3 init function */
static void MX_I2C3_Init(void)
{

    SSD1306_I2C_PORT.Instance = I2C3;
    SSD1306_I2C_PORT.Init.Timing = 0x00000E14; // 100kHz
    SSD1306_I2C_PORT.Init.OwnAddress1 = 0; // SSD1306_I2C_ADDR;
//    hi2c1.Init.ClockSpeed = 400000;
//    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    // hi2c1.Init.OwnAddress1 = 0;
    SSD1306_I2C_PORT.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    SSD1306_I2C_PORT.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    SSD1306_I2C_PORT.Init.OwnAddress2 = 0;
    SSD1306_I2C_PORT.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    SSD1306_I2C_PORT.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    SSD1306_I2C_PORT.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    __I2C3_CLK_ENABLE();

    if (HAL_I2C_Init(&SSD1306_I2C_PORT) != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
    }



}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char* file, int line)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
      /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

  /**
    * @}
  */

  /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
