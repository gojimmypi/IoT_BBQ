@echo off
REM Run this file to build the project outside of the IDE.
REM WARNING: if using a different machine, copy the .rsp files together with this script.
echo hsensor.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Common/hsensor.gcc.rsp" || exit 1
echo psensor.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/Common/psensor.gcc.rsp" || exit 1
echo stm32l475e_iot01.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Common/stm32l475e_iot01.gcc.rsp" || exit 1
echo stm32l4xx_hal_msp.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Common/stm32l4xx_hal_msp.gcc.rsp" || exit 1
echo tsensor.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/Common/tsensor.gcc.rsp" || exit 1
echo hts221.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Components/hts221.gcc.rsp" || exit 1
echo lps22hb.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Components/lps22hb/lps22hb.gcc.rsp" || exit 1
echo DISPLAY.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/DISPLAY/DISPLAY.gcc.rsp" || exit 1
echo flash_config.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Flash/flash_config.gcc.rsp" || exit 1
echo Flash_Sim_Demo.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/Flash/Flash_Sim_Demo.gcc.rsp" || exit 1
echo spi_flash.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Flash/spi_flash.gcc.rsp" || exit 1
echo HX711.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/HX711/HX711.gcc.rsp" || exit 1
echo LED.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/LED/LED.gcc.rsp" || exit 1
echo stm32l475e_iot01_hsensor.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/HTS221/stm32l475e_iot01_hsensor.gcc.rsp" || exit 1
echo stm32l475e_iot01_tsensor.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/HTS221/stm32l475e_iot01_tsensor.gcc.rsp" || exit 1
echo stm32l475e_iot01_psensor.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/LPS22HB/stm32l475e_iot01_psensor.gcc.rsp" || exit 1
echo ssd1306.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/SSD1306/ssd1306.gcc.rsp" || exit 1
echo ssd1306_fonts.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/SSD1306/ssd1306_fonts.gcc.rsp" || exit 1
echo ssd1306_tests.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/SSD1306/ssd1306_tests.gcc.rsp" || exit 1
echo SSD1306_demo.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/SSD1306/SSD1306_demo.gcc.rsp" || exit 1
echo state_machine.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/Tasks/state_machine.gcc.rsp" || exit 1
echo task_display.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/Tasks/task_display.gcc.rsp" || exit 1
echo int_to_string.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/UART/int_to_string.gcc.rsp" || exit 1
echo UART.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/UART/UART.gcc.rsp" || exit 1
echo startup.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/_Init/startup.gcc.rsp" || exit 1
echo system_stm32l4xx.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/system_stm32l4xx.gcc.rsp" || exit 1
echo task_weight_monitor.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/Tasks/task_weight_monitor.gcc.rsp" || exit 1
echo wiring_shift.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/wiring_shift.gcc.rsp" || exit 1
echo Init_GPIO.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/_Init/Init_GPIO.gcc.rsp" || exit 1
echo Init_GPIO_I2C.cpp
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @"VisualGDB/Debug/_Init/Init_GPIO_I2C.gcc.rsp" || exit 1
echo _main.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/_main.gcc.rsp" || exit 1
echo _main_interrupt.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/_main_interrupt.gcc.rsp" || exit 1
echo _main_LED_Thread1.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/_main_LED_Thread1.gcc.rsp" || exit 1
echo _main_LED_Thread2.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/_main_LED_Thread2.gcc.rsp" || exit 1
echo _main_pwm_thread.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/_main_pwm_thread.gcc.rsp" || exit 1
echo startup_stm32l475xx.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/StartupFiles/startup_stm32l475xx.gcc.rsp" || exit 1
echo croutine.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/croutine.gcc.rsp" || exit 1
echo event_groups.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/event_groups.gcc.rsp" || exit 1
echo list.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/list.gcc.rsp" || exit 1
echo queue.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/queue.gcc.rsp" || exit 1
echo stream_buffer.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/stream_buffer.gcc.rsp" || exit 1
echo tasks.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/tasks.gcc.rsp" || exit 1
echo timers.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/timers.gcc.rsp" || exit 1
echo cmsis_os.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.gcc.rsp" || exit 1
echo port.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/portable/GCC/ARM_CM3/port.gcc.rsp" || exit 1
echo heap_4.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/FreeRTOS/Source/portable/MemMang/heap_4.gcc.rsp" || exit 1
echo stm32l4xx_hal.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.gcc.rsp" || exit 1
echo stm32l4xx_hal_adc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc.gcc.rsp" || exit 1
echo stm32l4xx_hal_adc_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_can.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_can.gcc.rsp" || exit 1
echo stm32l4xx_hal_comp.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_comp.gcc.rsp" || exit 1
echo stm32l4xx_hal_cortex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.gcc.rsp" || exit 1
echo stm32l4xx_hal_crc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc.gcc.rsp" || exit 1
echo stm32l4xx_hal_crc_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_crc_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_cryp.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cryp.gcc.rsp" || exit 1
echo stm32l4xx_hal_cryp_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cryp_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_dac.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dac.gcc.rsp" || exit 1
echo stm32l4xx_hal_dac_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dac_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_dcmi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dcmi.gcc.rsp" || exit 1
echo stm32l4xx_hal_dfsdm.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dfsdm.gcc.rsp" || exit 1
echo stm32l4xx_hal_dfsdm_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dfsdm_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_dma.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.gcc.rsp" || exit 1
echo stm32l4xx_hal_dma2d.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma2d.gcc.rsp" || exit 1
echo stm32l4xx_hal_dma_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_dsi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dsi.gcc.rsp" || exit 1
echo stm32l4xx_hal_exti.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.gcc.rsp" || exit 1
echo stm32l4xx_hal_firewall.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_firewall.gcc.rsp" || exit 1
echo stm32l4xx_hal_flash.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.gcc.rsp" || exit 1
echo stm32l4xx_hal_flash_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_flash_ramfunc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.gcc.rsp" || exit 1
echo stm32l4xx_hal_gfxmmu.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gfxmmu.gcc.rsp" || exit 1
echo stm32l4xx_hal_gpio.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.gcc.rsp" || exit 1
echo stm32l4xx_hal_hash.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_hash.gcc.rsp" || exit 1
echo stm32l4xx_hal_hash_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_hash_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_hcd.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_hcd.gcc.rsp" || exit 1
echo stm32l4xx_hal_i2c.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.gcc.rsp" || exit 1
echo stm32l4xx_hal_i2c_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_irda.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_irda.gcc.rsp" || exit 1
echo stm32l4xx_hal_iwdg.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_iwdg.gcc.rsp" || exit 1
echo stm32l4xx_hal_lcd.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_lcd.gcc.rsp" || exit 1
echo stm32l4xx_hal_lptim.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_lptim.gcc.rsp" || exit 1
echo stm32l4xx_hal_ltdc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_ltdc.gcc.rsp" || exit 1
echo stm32l4xx_hal_ltdc_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_ltdc_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_mmc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc.gcc.rsp" || exit 1
echo stm32l4xx_hal_mmc_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_mmc_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_nand.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_nand.gcc.rsp" || exit 1
echo stm32l4xx_hal_nor.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_nor.gcc.rsp" || exit 1
echo stm32l4xx_hal_opamp.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_opamp.gcc.rsp" || exit 1
echo stm32l4xx_hal_opamp_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_opamp_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_ospi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_ospi.gcc.rsp" || exit 1
echo stm32l4xx_hal_pcd.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pcd.gcc.rsp" || exit 1
echo stm32l4xx_hal_pcd_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pcd_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_pka.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pka.gcc.rsp" || exit 1
echo stm32l4xx_hal_pssi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pssi.gcc.rsp" || exit 1
echo stm32l4xx_hal_pwr.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.gcc.rsp" || exit 1
echo stm32l4xx_hal_pwr_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_qspi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_qspi.gcc.rsp" || exit 1
echo stm32l4xx_hal_rcc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.gcc.rsp" || exit 1
echo stm32l4xx_hal_rcc_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_rng.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.gcc.rsp" || exit 1
echo stm32l4xx_hal_rng_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_rtc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc.gcc.rsp" || exit 1
echo stm32l4xx_hal_rtc_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rtc_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_sai.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sai.gcc.rsp" || exit 1
echo stm32l4xx_hal_sai_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sai_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_sd.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd.gcc.rsp" || exit 1
echo stm32l4xx_hal_sd_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sd_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_smartcard.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_smartcard.gcc.rsp" || exit 1
echo stm32l4xx_hal_smartcard_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_smartcard_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_smbus.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_smbus.gcc.rsp" || exit 1
echo stm32l4xx_hal_spi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.gcc.rsp" || exit 1
echo stm32l4xx_hal_spi_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_sram.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_sram.gcc.rsp" || exit 1
echo stm32l4xx_hal_swpmi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_swpmi.gcc.rsp" || exit 1
echo stm32l4xx_hal_tim.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.gcc.rsp" || exit 1
echo stm32l4xx_hal_tim_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_tsc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tsc.gcc.rsp" || exit 1
echo stm32l4xx_hal_uart.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.gcc.rsp" || exit 1
echo stm32l4xx_hal_uart_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_usart.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_usart.gcc.rsp" || exit 1
echo stm32l4xx_hal_usart_ex.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_usart_ex.gcc.rsp" || exit 1
echo stm32l4xx_hal_wwdg.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_wwdg.gcc.rsp" || exit 1
echo stm32l4xx_ll_usb.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usb.gcc.rsp" || exit 1
echo stm32l4xx_ll_adc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_adc.gcc.rsp" || exit 1
echo stm32l4xx_ll_comp.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_comp.gcc.rsp" || exit 1
echo stm32l4xx_ll_crc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_crc.gcc.rsp" || exit 1
echo stm32l4xx_ll_crs.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_crs.gcc.rsp" || exit 1
echo stm32l4xx_ll_dac.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dac.gcc.rsp" || exit 1
echo stm32l4xx_ll_dma.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma.gcc.rsp" || exit 1
echo stm32l4xx_ll_dma2d.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_dma2d.gcc.rsp" || exit 1
echo stm32l4xx_ll_exti.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_exti.gcc.rsp" || exit 1
echo stm32l4xx_ll_fmc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_fmc.gcc.rsp" || exit 1
echo stm32l4xx_ll_gpio.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.gcc.rsp" || exit 1
echo stm32l4xx_ll_i2c.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_i2c.gcc.rsp" || exit 1
echo stm32l4xx_ll_lptim.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_lptim.gcc.rsp" || exit 1
echo stm32l4xx_ll_lpuart.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_lpuart.gcc.rsp" || exit 1
echo stm32l4xx_ll_opamp.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_opamp.gcc.rsp" || exit 1
echo stm32l4xx_ll_pka.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pka.gcc.rsp" || exit 1
echo stm32l4xx_ll_pwr.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_pwr.gcc.rsp" || exit 1
echo stm32l4xx_ll_rcc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rcc.gcc.rsp" || exit 1
echo stm32l4xx_ll_rng.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rng.gcc.rsp" || exit 1
echo stm32l4xx_ll_rtc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_rtc.gcc.rsp" || exit 1
echo stm32l4xx_ll_sdmmc.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_sdmmc.gcc.rsp" || exit 1
echo stm32l4xx_ll_spi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.gcc.rsp" || exit 1
echo stm32l4xx_ll_swpmi.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_swpmi.gcc.rsp" || exit 1
echo stm32l4xx_ll_tim.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_tim.gcc.rsp" || exit 1
echo stm32l4xx_ll_usart.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_usart.gcc.rsp" || exit 1
echo stm32l4xx_ll_utils.c
c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe @"VisualGDB/Debug/__BSP_ROOT__/STM32L4xxxx/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.gcc.rsp" || exit 1
echo Linking VisualGDB/Debug/IoT_BBQ_STM32...
c:\SysGCC\arm-eabi\bin\arm-none-eabi-g++.exe @VisualGDB/Debug/IoT_BBQ_STM32.link.rsp || exit 1
c:\SysGCC\arm-eabi\bin\arm-none-eabi-objcopy.exe @VisualGDB/Debug/IoT_BBQ_STM32.mkbin.rsp || exit 1
