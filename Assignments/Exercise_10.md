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

Here's a diagram of the Power Analysis Setup:

![power_mangement_component_map.png](./images/power_mangement_component_map.png)


## What are the different states the device can be in?

Wordy can be on (display showing) or sleeping (processor asleep, accelerometer set interrupt/wake it).

## How much will your device be in each state?
My goal is for the ring to be on for 5-10s every five minutes. Sometimes it will be on more, as I play with it a lot. More often it will be sleeping, such as left on a table overnight.

## How much current is used in each state?
Using a DVM in current sensing mode to measure the current in each state.

Curiously, even when paused in the debugger, there's a fluctuation in power:

![power_fluctuation_during_debug_pause.png](./image/power_fluctuation_during_debug_pause.png)


These peripherals, many of which are unused for this project, consume power (most are assumed in "off" low power state unless initialized.

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
4.983660131

## Additional Information

### Caution

Do not connect the PC to the ST-LINK (CN7) when R30 is soldered. The PC may be damaged
or the board may not be powered correctly. From page 17 of [UM2153](https://www.st.com/resource/en/user_manual/um2153-discovery-kit-for-iot-node-multichannel-communication-with-stm32l4-stmicroelectronics.pdf)

### Power Tree

From page 18 of [UM2153](https://www.st.com/resource/en/user_manual/um2153-discovery-kit-for-iot-node-multichannel-communication-with-stm32l4-stmicroelectronics.pdf)
![power_tree.png](./images/power_tree.png)


<< [Exercise 9](./Exercise_9.md) -- [Assignments](./README.md) --  END