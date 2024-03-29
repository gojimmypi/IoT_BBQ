# Power Analysis

The worksheet describing Wordy’s power use is demonstrated in the lecture. Make one for your
system (either design or engineering version).

Estimates are ok in place of real numbers. If you have many components, limit it to the top 5-8
most likely to consume power. Even if you have a USB or wall powered system, identify the
largest consumers of power and how you might reduce power consumption.

Turn in a link to your power worksheet to Discord #assignment-submission by 9am on Feb 13th.

## Overview:

> "_only ST-LINK circuit has the power before USB enumeration, because the host PC only provides 100 mA to the board at that time. During the USB enumeration_"
-- [UM2153](https://www.st.com/resource/en/user_manual/um2153-discovery-kit-for-iot-node-multichannel-communication-with-stm32l4-stmicroelectronics.pdf) section 7.4 Power supply.

I started [Power Analysis Day](https://twitter.com/gojimmypi/status/1492178884883746820?s=20&t=vy_CMO37vpjmfwYx7sZaPw) with my backup board:
 
![PPK3_power_analysis.png](./images/PPK3_power_analysis.png)

Here's a diagram of the full Power Analysis Setup:

![power_mangement_component_map.png](./images/power_mangement_component_map.png)

See my [blog](https://gojimmypi.github.io/ppk2-power-analysis/) for additional Power Analysis setup information.

## What are the different states the device can be in?

That various sleep modes (and all the other HAL details) are discussed in the 2,600+ page [UM1884 PWR Firmware driver API description](https://www.st.com/resource/en/user_manual/dm00173145-description-of-stm32l4l4-hal-and-lowlayer-drivers-stmicroelectronics.pdf) guide. There are 8 main Power Modes and several sub-modes  summarized in [this STM32L4 Power Presentation](https://www.st.com/content/ccc/resource/training/technical/product_training/ce/57/a3/86/7a/3d/4d/87/STM32L4_System_Power.pdf/files/STM32L4_System_Power.pdf/jcr:content/translations/en.STM32L4_System_Power.pdf):

![STM32L4_power_modes.png](./images/STM32L4_power_modes.png)

## How much will your device be in each state?

My goal is to have two main power modes: `On` and `Deep Sleep`. The `On` mode requires a whopping 120mA. I've not yet determined how to successfully put my device into sleep mode.

## How much current is used in each state?

I used a [Nordic Power Profile Kit](https://www.nordicsemi.com/Products/Development-hardware/Power-Profiler-Kit-2) to measure board power.

See [UM1884 Description of STM32L4/L4+ HAL and low-layer drivers](https://www.st.com/resource/en/user_manual/dm00173145-description-of-stm32l4l4-hal-and-lowlayer-drivers-stmicroelectronics.pdf) for information on `HAL_PWR_EnterSLEEPMode()`.


Curiously, even when paused in the debugger, there's a fluctuation in power:

![power_fluctuation_during_debug_pause.png](./images/power_fluctuation_during_debug_pause.png)


These peripherals, many of which are unused for this project, also consume power (most are assumed in "off" low power state unless initialized, but they may need to be manualyl turned off).

* SPBTLE-RF Bluetooth

* SPSGRF-868 or SPSGRF-915 Sub-GHz (868 or 915 MHz) low-power-programmable RF module

* 64-Mbit Quad-SPI NOR Flash memory

* ISM43362-M3G-L44 Wi-Fi module Inventek system  (802.11 b/g/n compliant)

* MP34DT01 ST-MEMS microphones

* HTS221 relative humidity and temperature low-power consumption: 2 μA  (page 25).

* LPS22HB 260-1260 hPa absolute digital output barometer

* LIS3MDL High-performance 3-axis magnetometer

* VL53L0X Time-of-Flight and gesture detection sensor

* LED indicator lights (9x of them)

## How long will the device last given a 40mAh battery?

At 120mA draw, not very long. The dev board likely won't even power on!

This particular board was chosen for the Wi-Fi capabilities and many interesting peripherals built-in. Unless power is pulled to the BBQ Grill, there's an unreasonable amount of power needed
from basic batteries. Consideration will be given to forego the Wi-Fi capabilities, port the code to a [Blue Pill](https://hackaday.com/2021/01/20/blue-pill-vs-black-pill-transitioning-from-stm32f103-to-stm32f411/), 
and use a battery or perhaps solar power. At this point, the only feature implemented that will not be avilable is the baromatric sensor.

If using a Blue Pill, there's considerably lower power requirements:

![blue_pill_power.png](./images/blue_pill_power.png)

Zooming out on the time scale, we see that the LED blinky has a noticable effect on the power profile:

![blue_pill_power_blinky.png](./images/blue_pill_power_blinky.png)

Leaving the Green LED off, and unsoldering the red power LED, we can likely get the device current down to about 25mA during run mode.

This STM32 Blue Pill is using the [STM32F103C8T6](https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html) "Mainstream Performance line, Arm Cortex-M3". 
The observed current is certainly in line with the [datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf) specifications:

![STM32F103C8T6_run_mode_current.png](./images/STM32F103C8T6_run_mode_current.png)

Relatively small sleep current:

![STM32F103C8T6_sleep_mode_current.png](./images/STM32F103C8T6_sleep_mode_current.png)

Stop and standby current in the uA range:

![STM32F103C8T6_stop_standby_mode_current.png](./images/STM32F103C8T6_stop_standby_mode_current.png) 

If the display is only on for a total of a minute or so, with mostly stop current levels when the BBQ is not in use for sometimes weeks at a time, 
battery life will be quite reasonable.

If there's only 5uA of current in stop mode, a 40mA hour battey could keep the device alive for up to 8,000 hours, or nearly a year. Actual battery life and voltage retention
over time will vary depending on battery age, quality, and ambient temperature.


## Additional Information

### Caution

Do not connect the PC to the ST-LINK (CN7) when R30 is soldered. The PC may be damaged
or the board may not be powered correctly. From page 17 of [UM2153](https://www.st.com/resource/en/user_manual/um2153-discovery-kit-for-iot-node-multichannel-communication-with-stm32l4-stmicroelectronics.pdf)

### Power Tree

From page 18 of [UM2153](https://www.st.com/resource/en/user_manual/um2153-discovery-kit-for-iot-node-multichannel-communication-with-stm32l4-stmicroelectronics.pdf):

![power_tree.png](./images/power_tree.png)


<< [Exercise 9](./Exercise_9.md) -- [Assignments](./README.md) --  END