# Final Project

This document addresses the [Final Project Instructions](./Final_Project_Instructions.md) for the [Making Embedded Systems](https://lms.classpert.com/classpert-x/courses/making-embedded-systems-wUXIUA) class.

The objective is to create Propane Tank Weight Sensor System with something considerably more accurate and precise to replace the stock mechanical spring gauge:

![Existing_tank_scale.png](./images/Existing_tank_scale.png)   
 
## Minimum Project Requirements
 
The project must:

### (a) Use a Cortex-M processor: 

This project is using an STMicro STML4, specifically the [STM32L475VG](https://www.st.com/resource/en/datasheet/stm32l475vg.pdf), 
part of the [STM32 Ultra Low Power](https://www.st.com/en/microcontrollers-microprocessors/stm32-ultra-low-power-mcus.html) Arm® Cortex®-M4 32-bit MCU+FPU series.

### (b) Have a button that causes an interrupt

This project leverages the code from [Exercise 4](./Exercise_4.md) that implements an operational mode-switch via interrupt-driven button press code.

### (c) Use at least three peripherals such as ADC, DAC, PWM LED, Smart LED, LCD, sensor, BLE

The peripherals used in the project:

* Load cell (weight sensor) such as the [SparkFun HX711](https://www.sparkfun.com/products/13879). See [Project HX711 code](../IoT_BBQ_STM32/HX711/).

* Display: SSD1306 OLED Dual Color (Yellow / Blue) such as [this I2C Serial 12864 on Amazon](https://www.amazon.com/dp/B08KY21SR2/) that includes mbedded Driver IC. See [Project SSD1306 code](../IoT_BBQ_STM32/SSD1306/)

* Temperature Sensor (The onboard device TODO specify)

* Onboard LED: See [Project LED code](../IoT_BBQ_STM32/LED/)

### (d) Have serial port output

See  [Project UART code](../IoT_BBQ_STM32/UART/)

### (e) Implement an algorithmic piece that makes the system interesting

TODO: _interesting_

### (f) Implement a state machine

There's currently a prototype [LED STate Machine](https://github.com/gojimmypi/IoT_BBQ/blob/ce44c00152af0a16b26d9a246a799ed7db8553ae/IoT_BBQ_STM32/LED/LED.cpp#L23) 
with [IsBlinking, AlwaysOn, AlwaysOff](https://github.com/gojimmypi/IoT_BBQ/blob/ce44c00152af0a16b26d9a246a799ed7db8553ae/IoT_BBQ_STM32/LED/LED.h#L14) states.

This project uses the STM32L4XX HAL, for example [here](https://github.com/gojimmypi/IoT_BBQ/blob/ce44c00152af0a16b26d9a246a799ed7db8553ae/IoT_BBQ_STM32/_main.c#L2), 
and is a mult-threaded application using embedded RTOS (specfically [CMSIS_RTOS](https://arm-software.github.io/CMSIS_5/RTOS2/html/rtos_api2.html)) for example included [here](https://github.com/gojimmypi/IoT_BBQ/blob/ce44c00152af0a16b26d9a246a799ed7db8553ae/IoT_BBQ_STM32/_main.c#L3)

## List of the tasks to complete for the project

:heavy_check_mark:

- [X] Confirm operational display
- [X] Confirm operational weight sensor
- [ ] Show weight value on display
- [X] Confirm serial port operation
- [ ] Implement serial debug messages
- [ ] Design enclosure
- [ ] Print enclosure
- [ ] Mount hardware in enclosure

## Challenges

There are plenty of potential challenges. This project was originally started (and abandoned) [6 years ago](https://github.com/gojimmypi/IoT_BBQ/tree/c15d7c90c0f49ad006a91550d2dd1ab7d34544e8), in part due to 
mechanical issues. It is hoped that modern 3D Printing flexibility will be able to help with the mechanical mounting aspects.

Technical implementation difficulties of a new hardware platform are always a concern (the original project was based on the ESP8266 and the LUA language).

Details on some of the challenges:

### Mechanical support for weight sensor

I [reached out on Twitter](https://twitter.com/gojimmypi/status/1481711080497823744?s=20) for suggestions on how to mount the load cell. 
One of the responses is regarding [load cell damage if the propane tank is dropped into place](https://twitter.com/RueNahcMohr/status/1481724026221305861?s=20).
Another concern is [load cell creep](https://twitter.com/GMahovlic/status/1481724848040775685?s=20) when the tank is left in place for a long period.

### Enclosure

Enclosures are always challenging. Fortunately there's a 3D Printer available to create a custom enclosure for this project.

The enclosure should probably be weather-proof, and located reasonably far from the grill heat box which can get up to 500 degrees.

The OLED display is likely not tolerant to hard freeze. 

## Component Availability

If any sort of mass-production was desired, there's of course the chip shortage to be concerned about.



## Deliverables

The final project will be delivered as:

(a) Video of the system working as intended (link to mp4 or youtube)  ** TODO **
(b) Write up of the system (PDF or Google docs report). This document.
(c) Link to the code: see [GitHub IoT BBQ STM32 Project](https://github.com/gojimmypi/IoT_BBQ/tree/main/IoT_BBQ_STM32)


## References

### Core Hardware

- [STM32 Discovery Kits](https://www.st.com/en/evaluation-tools/stm32-discovery-kits.html#products)
- [STM32L4 series of ultra-low-power MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32l4-series.html)
- [ARM MBED DISCO-L475VG-IOT01A (B-L475E-IOT01A](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/) (this is where the link on the OTG file points)
- [Mouser B-L475E-IOT01A Data Brief ](https://www.mouser.com/datasheet/2/389/b-l475e-iot01a-1848022.pdf)
- [Mouser Discovery Kit for IoT Node](https://www.mouser.com/pdfdocs/RS7706_IC_STM32L475E-IOT01A1_0517d.pdf) (this is the front and back of the insert card in for the shipped product)
- [Mouser STMicroelectronics B-L475E-IOT01A Discovery Kit for IoT Node](https://www.mouser.com/new/stmicroelectronics/stm-b-l475e-iot01a-kit/)

### Drivers

- [ST-LINK, ST-LINK/V2, ST-LINK/V2-1, STLINK-V3 USB driver signed for Windows7, Windows8, Windows10](https://www.st.com/content/my_st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.license=1637530388106.product=STSW-LINK009.version=2.0.2.html)


### Peripheral Hardware

- [SSD1306 I2C Serial](https://www.amazon.com/dp/B08KY21SR2/)
- [bogde/HX711](https://github.com/bogde/HX711)
- [nimaltd/HX711](https://github.com/nimaltd/HX711/blob/master/hx711.c)

### Development Environment

- [Visual Studio 2019](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes)
- [Sysprogs VisualGDB Extension](https://visualgdb.com/)
- [CMSIS-RTOS2](https://arm-software.github.io/CMSIS_5/RTOS2/html/index.html)
- [STM32L4 Discovery kit IoT node software](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html#tools-software)
- [VS Code Extension: Markdown PDF](https://marketplace.visualstudio.com/items?itemName=yzane.markdown-pdf)

### Tutorials and Sample Code

- [Sysprogs VisualGDB Developing STM32 projects with Visual Studio tutorial](https://visualgdb.com/tutorials/arm/stm32/)
- [Sysprogs VisualGDB Using the STM32 UART interface with HAL](https://visualgdb.com/tutorials/arm/stm32/uart/hal/)
