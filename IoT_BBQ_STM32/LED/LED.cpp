#include "Common/globals.h"
#include "../LED/LED.h"
#include <stm32l4xx_hal.h>
#include <Tasks/state_machine.h>

#ifdef __cplusplus
extern "C" {
#endif

    volatile static enum LED_Mode __current_LED_MODE = IsBlinking; // we'll use a button to trigger an interrupt to set LED mode, starting with blinky

    int LED_VERSION() {
        return 1;
    }
    
    LED_Mode LED_GetMode()
    {
        // TODO RTOS wrap
        LED_Mode thisState = __current_LED_MODE;
        
        return thisState;
    }
    
    int LED_SetMode(LED_Mode NewState)
    {
        // called from interrupt! 
 
        __current_LED_MODE = NewState;
        
        // TODO we probably don't want to set application runnnig state based on LED
        if (__current_LED_MODE == IsBlinking)
        {
            SetAppState(Running);
        }
        else
        {
            SetAppState(Demo);
        }
        
        return 0; // TODO check for errors
    }
    
    int LED_init()
    {
        GPIO_InitTypeDef GPIO_InitStructureA;

        GPIO_InitStructureA.Pin = GPIO_PIN_5;

        GPIO_InitStructureA.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructureA.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructureA.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructureA);
        
        return 0; // TODO check for errors
    }

    int LED2_init()
    {
        GPIO_InitTypeDef GPIO_InitStructureB;

        GPIO_InitStructureB.Pin = GPIO_PIN_14;

        GPIO_InitStructureB.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructureB.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructureB.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStructureB);
        
        return 0; // TODO check for errors
    }
    
    
    void LED_ON() {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }

    void LED_OFF() {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
    
    void LED_TOGGLE() {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }

    void LED2_ON() {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
    }

    void LED2_OFF() {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    }

    void LED2_TOGGLE() {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
    }

    //
    // Turn the LED on (unless button mode set to always off, or always on)
    //
     void STATE_LED_ON()
    {
        switch (__current_LED_MODE)
        {
        case IsBlinking:
            LED_ON();
            break;

        case AlwaysOn:
            LED_ON();
            break;
            
        case AlwaysOff:
            LED_OFF();
            break;

        default:
            LED_ON();
            break;
        }
    }


    //
    // Turn the LED off (unless button mode set to always on, or always off)
    //
     void STATE_LED_OFF()
    {
        switch (__current_LED_MODE)
        {
        case IsBlinking:
            LED_OFF();  // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        case AlwaysOn:
            LED_ON(); // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            break;

        case AlwaysOff:
            LED_OFF();  // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        default:
            LED_OFF(); //  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
            break;

        }
    }


    void temp_MX_TIM1_Init(void)
    {

        TIM_MasterConfigTypeDef sMasterConfig;
        TIM_OC_InitTypeDef sConfigOC;
        TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
        
        TIM_HandleTypeDef htim1;
        
        htim1.Instance = TIM1;
        htim1.Init.Prescaler = 80;
        htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim1.Init.Period = 20000;
        htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim1.Init.RepetitionCounter = 0;
        htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
        if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
        {
            //_Error_Handler(__FILE__, __LINE__);
        }

        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
        {
           // _Error_Handler(__FILE__, __LINE__);
        }

        sConfigOC.OCMode = TIM_OCMODE_PWM1;
        sConfigOC.Pulse = 1000;
        sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
        sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
        sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
        if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
        {
           // _Error_Handler(__FILE__, __LINE__);
        }

        if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
        {
           // _Error_Handler(__FILE__, __LINE__);
        }

        if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
        {
            //_Error_Handler(__FILE__, __LINE__);
        }

        sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
        sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
        sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
        sBreakDeadTimeConfig.DeadTime = 0;
        sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
        sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
        sBreakDeadTimeConfig.BreakFilter = 0;
        sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
        sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
        sBreakDeadTimeConfig.Break2Filter = 0;
        sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
        if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
        {
            //_Error_Handler(__FILE__, __LINE__);
        }

        HAL_TIM_Base_MspInit(&htim1);

    }
    
#ifdef __cplusplus
}
#endif    