# Assignments for [Making Embedded Systems](https://classpert.com/classpertx/cohorts/making-embedded-systems/dashboard?path_to_locale=en) class.

- [Exercise 1](./Exercise_1.md)
- [Exercise 2.1](./Exercise_2_1.md)
- [Exercise 2.2](./Exercise_2_2.md)
- [Exercise 3a](./Exercise_3a.md)
- [Exercise 3b](./Exercise_3b.md)  See also [Class Materials](https://drive.google.com/drive/folders/1xk9AmmLDqESqimDk_KvxHu6KfzpaYX9M), [spi_flash.h](https://drive.google.com/file/d/12dw-pZiKiK1vi4gv49W1x6np5uzCH_cV/view)
- [Exercise 4](./Exercise_4.md) 
- [Exercise 5](./Exercise_5.md) 
- [Exercise 6](./Exercise_6.md) 
- [Exercise 7](./Exercise_7.md) 
- [Exercise 8](./Exercise_8.md) 
- [Final Project](./Final_Project.md)


## Links

Hardware
- [STM32L4 Series](https://www.st.com/en/microcontrollers-microprocessors/stm32l4-series.html)
- [Mouser B-L475E-IOT01A1](https://www.mouser.com/ProductDetail/stmicroelectronics/b-l475e-iot01a1/?qs=2m8Gdae5Lr3rq3rcxS2xEg%3D%3D&countrycode=US&currencycode=USD)
- [Mouser SPBTLE-RF](https://www.mouser.com/ProductDetail/STMicroelectronics/SPBTLE-RF?qs=k5OWtXsTJaq8f%252B3JiZyqyw%3D%3D), [Datasheet](https://www.mouser.com/datasheet/2/389/SGST_S_A0003533199_1-2576929.pdf)
- [ST B-L475E-IOT01A STM32L4 Discovery kit IoT node](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html#)
- [Migrating from STM32L4 and STM32L4+ to STM32L5 Series microcontrollers (AN5138)](https://www.st.com/resource/en/application_note/dm00476869-migrating-from-stm32l4-and-stm32l4-to-stm32l5-series-microcontrollers-stmicroelectronics.pdf)

Specifications

- [User Manual (57 pages) STM32L4 Discovery kit for the IoT node (B-L475E-IOT01A)](https://www.st.com/resource/en/user_manual/um2153-discovery-kit-for-iot-node-multichannel-communication-with-stm32l4-stmicroelectronics.pdf)
- [Data brief (4 pages) ST B-L475E-IOT01A](https://www.st.com/resource/en/data_brief/b-l475e-iot01a.pdf) Discovery kit for IoT node, multi-channel communication with STM32L4
- [STM32L475VG](https://www.st.com/en/microcontrollers-microprocessors/stm32l475vg.html#), [STM32L475xx datasheet (204 pages)](https://www.st.com/resource/en/datasheet/stm32l475vg.pdf)
- [STM32L475xx Datasheet AN4666](https://www.st.com/resource/en/datasheet/stm32l475vg.pdf)

Application Notes

- [Using the STM32F2, STM32F4 and STM32F7 Series DMA controller AN4031](https://www.st.com/content/ccc/resource/technical/document/application_note/27/46/7c/ea/2d/91/40/a9/DM00046011.pdf/files/DM00046011.pdf/jcr:content/translations/en.DM00046011.pdf)
- [Using the STM32F0/F1/F3/Gx/Lx Series DMA controller AN2548](https://www.st.com/resource/en/application_note/an2548-using-the-stm32f0f1f3gxlx-series-dma-controller-stmicroelectronics.pdf)
- [Parallel synchronous transmission using GPIO and DMA](https://www.st.com/resource/en/application_note/an4666-parallel-synchronous-transmission-using-gpio-and-dma-stmicroelectronics.pdf)

Examples

- [B-L475E-IOT01A/Examples](https://github.com/STMicroelectronics/STM32CubeL4/tree/master/Projects/B-L475E-IOT01A/Examples) (not many examples)
- [STM32CubeL4/Projects/B-L475E-IOT01A/Examples/BSP/Src/](https://github.com/STMicroelectronics/STM32CubeL4/tree/master/Projects/B-L475E-IOT01A/Examples/BSP/Src)

Peripherals

- [Inventek Systems ISM43362-M3G-L44-E/U Serial-to-WiFi Module](https://www.inventeksys.com/ism4336-m3g-l44-e-embedded-serial-to-wifi-module/), [ISM43362-M3G-L44 Datasheet](http://www.inventeksys.com/wp-content/uploads/ISM43362_M3G_L44_Functional_Spec.pdf)

mbed

- [os.mbed.com DISCO-L475VG-IOT01A (B-L475E-IOT01A)](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/)
- [sensors](https://ide.mbed.com/compiler/#nav:/DISCO_L475VG_IOT01-Sensors-BSP/main.cpp;)

Visual GDB

- [Creating Advanced STM32CubeMX-based Projects with VisualGDB](https://visualgdb.com/tutorials/arm/stm32/cube/advanced/)
- [Controlling STM32 Hardware Timers using HAL](https://visualgdb.com/tutorials/arm/stm32/timers/hal/)
- [Using STM32 timers in PWM mode](https://visualgdb.com/tutorials/arm/stm32/pwm/)

RTOS

- [CMSIS-RTOS2 Documentation](https://arm-software.github.io/CMSIS_5/RTOS2/html/index.html)
- GitHub [CMSIS Version 5](https://github.com/ARM-software/CMSIS_5)
- [The FreeRTOS Reference Manual](https://www.freertos.org/fr-content-src/uploads/2018/07/FreeRTOS_Reference_Manual_V10.0.0.pdf)
- [stackoverflow: What are valid values of `HAL_NVIC_SetPriority()` when using STM32 and FreeRTOS?](https://stackoverflow.com/questions/50243996/what-are-valid-values-of-hal-nvic-setpriority-when-using-stm32-and-freertos)

Debuggers

- [ST-LINK/V2 in-circuit debugger/programmer for STM8 and STM32](https://www.st.com/en/development-tools/st-link-v2.html)
- [Segger J-Link / J-Trace User Guide](https://www.segger.com/downloads/jlink/UM08001)
- [Converting ST-LINK On-Board Into a J-Link](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/)

Sample Code

- [ST community: delay in a microsecond(us)](https://community.st.com/s/question/0D50X0000BGkxmCSQR/stm32l462-delay-in-a-microsecondus)
- [a-podshivalov/RIOT](https://github.com/a-podshivalov/RIOT) sample code
- [bogde/HX711](https://github.com/bogde/HX711/blob/master/src/HX711.cpp)
- [ArduinoCore-samd/cores/arduino/wiring_private.h](https://github.com/arduino/ArduinoCore-samd/blob/master/cores/arduino/wiring_private.h)
- [ArduinoCore-avr/cores/arduino/wiring_shift.c](https://github.com/arduino/ArduinoCore-avr/blob/9f8d27f09f3bbd1da1374b5549a82bda55d45d44/cores/arduino/wiring_shift.c) - original code for [shiftIn()](https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftin/)
- [logicalelegance/midifun/Core/Console/console.c](https://github.com/logicalelegance/midifun/blob/master/Core/Console/console.c)
- [stackoverflow: STM32 HAL timer interrupt isn't triggered](https://stackoverflow.com/questions/40323461/stm32-hal-timer-interrupt-isnt-triggered)
- [stackoverflow: STM32F3 Discovery - Implement GPIO-Interrupt](https://stackoverflow.com/questions/40057581/stm32f3-discovery-implement-gpio-interrupt)
- [STM32-libraries/Drivers/LCD/Adafruit_GFX.h](https://github.com/mindThomas/STM32-libraries/blob/master/Drivers/LCD/Adafruit_GFX.h)

IoT Management Tools

- [What Is IoT Device Management and Why Do You Need It?](https://www.digi.com/blog/post/what-is-iot-device-management)
- [Memfault - Cloud Debugging and Observability for Your IoT Devices](https://memfault.com/); [Monitoring Fleet Health with Heartbeat Metrics](https://interrupt.memfault.com/blog/device-heartbeat-metrics); [Defensive Programming](https://interrupt.memfault.com/blog/defensive-and-offensive-programming)
- [Tyler Hoffman on embedded.fm to discuss the issues associated with embedded devices at consumer scale](https://embedded.fm/episodes/390).
- [Monitor your entire Azure IoT environment with Datadog](https://www.datadoghq.com/dg/monitor/azure-iot/)
- [ThingsBoard Open-source IoT Platform](https://thingsboard.io/)
- [Azure IoT](https://azure.microsoft.com/en-us/overview/iot/#overview)
- [AWS IoT Device Management](https://aws.amazon.com/iot-device-management/)

Other Stuff

- wikipedia [.bss block starting symbol](https://en.wikipedia.org/wiki/.bss)
- [pinout](https://pinout.readthedocs.io/en/latest/)
- [cmocka unit testing framework for C with support for mock objects](https://cmocka.org/)
- [asciiflow.com](https://asciiflow.com/#/)
- [app.diagrams.net](https://app.diagrams.net/)
- [lucidChart Block diagram maker](https://www.lucidchart.com/pages/examples/block-diagram-maker)
- [drawio-desktop](https://github.com/jgraph/drawio-desktop/releases/tag/v15.8.7)
- [Everything You Never Wanted To Know About Linker Script](https://mcyoung.xyz/2021/06/01/linker-script/)
- [Basic Concepts in Interrupts](https://web.sonoma.edu/users/f/farahman/sonoma/courses/es310/310_arm/lectures/Chapter_11_Interrupts_ARM.pdf) from [EE 310/310L: Microprocessors and System Design - Introducing ARM](https://web.sonoma.edu/users/f/farahman/sonoma/courses/es310/310_arm/)
- [STM32Cube initialization code generator](https://www.st.com/en/development-tools/stm32cubemx.html?icmp=stm32cubemx_pron_pr-stm32cubef2_apr2014&sc=stm32cube-pr2#documentation),  specifically [STM32 configuration and initialization C code generation](https://www.st.com/resource/en/data_brief/stm32cubemx.pdf)
- [hackaday stm32cubemx makes makefiles](https://hackaday.com/2017/07/15/stm32cubemx-makes-makefiles/)
- [godbolt.org](godbolt.org)
