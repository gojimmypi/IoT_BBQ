# Final Project Report

This Final Project Report is a supplement to the [Final Project Minimum Project Requirement Detail](./Final_Project.md).
An embedded microscontroller was used to create a propane tank weaigh measurement system. 

## Application Description


## Hardware Description


## Software description

The application is written in C/C++ and targets the STM32 ARM Platform. 


### Describe the code in general

The code is a multi-threaded FreeRTOS embedded application.

### Describe the parts you wrote in some detail (maybe 3-5 sentences per module)

### Describe code you re-used from other sources, including the licenses for those

This project was created using the [Sysprogs VisualGDB Extension](https://visualgdb.com/?features=embedded) for [Visual Studio 2019](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes).
A tiny amount of initialization code was generated using the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html). 

The main code repository can be found at [github.com/gojimmypi/IoT_BBQ/tree/main/IoT_BBQ_STM32](https://github.com/gojimmypi/IoT_BBQ/tree/main/IoT_BBQ_STM32). MIT License.

* [HX711 Arduino Library](https://github.com/bogde/HX711) was ported to this STM32 HAL environment with FreeRTOS support. MIT License.

* [STM hsensor HAL](https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_hsensor.c) BSD 3-Clause license. 

* [STM Pressure Sensor HAL](https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_psensor.h) BSD 3-Clause license

* [ssd1306 display driver](https://github.com/afiskon/stm32-ssd1306) was created by Aleksander Alekseev and [modified](https://github.com/gojimmypi/IoT_BBQ/commits/main/IoT_BBQ_STM32/SSD1306) for this project.  MIT License

* [Display Code](https://github.com/gojimmypi/IoT_BBQ/tree/main/IoT_BBQ_STM32/DISPLAY) was written specifically for this project. MIT License.

* [Flash HAL](https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c). Assumed to still be Licensed by ST under BSD 3-Clause license, 
but the [license File is now blank](https://github.com/STMicroelectronics/STM32CubeL4/issues/63).  

* [Flash Config](https://github.com/gojimmypi/IoT_BBQ/blob/main/IoT_BBQ_STM32/Flash/flash_config.h) was created from scratch for this project. MIT license.

* [LED Blinky and State Machine](https://github.com/gojimmypi/IoT_BBQ/tree/main/IoT_BBQ_STM32/LED) created by gojimmypi for this project. MIT license.

* [UART](https://github.com/gojimmypi/IoT_BBQ/tree/main/IoT_BBQ_STM32/UART) created for this project, MIT license. Uses [stm32l4xx_hal.h](https://github.com/STMicroelectronics/STM32CubeL4/blob/master/Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h) 
assumed to still be [BSD 3-Clause license](https://github.com/STMicroelectronics/STM32CubeL4/blob/d023c0d560ace11509f9b761c8913a9e48fcf194/Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c#L27)

## Diagram(s) of the architecture


## Build instructions

To build in Visual Studio,


Open the Visual Studio Solution File called [IoT_BBQ_STM32.sln](https://github.com/gojimmypi/IoT_BBQ/blob/main/IoT_BBQ_STM32/IoT_BBQ_STM32.sln). 
Find the `IoT_BBQ_STM32` Project. Right-click and select "Build...":

![VisualGDB_build.png](./images/VisualGDB_build.png)

To build and upload code, simply click the green `VisualGDB Debugger` button:

![VisualGDB_Debugger_Button.png](./images/VisualGDB_Debugger_Button.png)

If the STM32 toolchain is installed (for Windows) there's also an auto-generated [batch file](https://github.com/gojimmypi/IoT_BBQ/blob/main/IoT_BBQ_STM32/IoT_BBQ_STM32-Debug.bat) to build from command-line.


### How to build the system (including the toolchain(s))

The only toolchain required for this project is the [VisualGDB Extension](https://visualgdb.com/). See the [Developing STM32 projects with Visual Studio](https://visualgdb.com/tutorials/arm/stm32/)

### Hardware

### Software

### How you debugged and tested the system


## Future

Although the discovery board was convenient from a _getting started_ perspective, it is also massive and power hungry.
The next steps are to port this project to a [Blue Pill]().

## What would be needed to get this project ready for production?

Key to a production deployment would be an _enclosure_ and some way to have them mass-produced. For large-scale production, some means of
mass-programming the devices would be needed. It would not be practical to manually plug in a million boards and program them each one at a time.


## How would you extend this project to do something more? Are there other features you’d like? How would you go about adding them?

## Grading

Self assessment of the project: for each criteria, choose a score (1, 2, 3) andexplain your reason for the score in 1-2 sentences.
Have you gone beyond the base requirements? How so?

