// flash_config.h

#include "stdint.h"
#include <stm32l4xx.h> // this explicit inclusion is needs for HAL_StatusTypeDef
#include <stm32l4xx_hal_flash.h>

/*
MIT License

Copyright (c) 2022 gojimmypi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef _flash_config_h
#define _flash_config_h

#ifdef __cplusplus
extern "C" {
#endif
    
    /* Exported types ------------------------------------------------------------*/

#define FlashConfigMajorVersion 1
#define FlashConfigMinorVersion 0
    
    struct FlashConfig
    {
        // WARNING maintain size and order of existing elements to ensure firmware upgrades do not corrupt saved values
        const uint32_t FLASH_START;
        const uint8_t MajorVersion;
        const uint8_t MinorVersion;
        uint32_t SCALE_OFFSET;
        const uint64_t Data64_In_Flash[0x20];       
    };
   
    struct FlashConfig* DeviceFlashConfig(); // read-only values directly from Flash
    struct FlashConfig* DeviceCacheConfig(); // pointer to updatable cache item (needs to be saved to flash!)

    uint32_t FlashNeedsUpdate(); // returns how many bytes in our cache do not match flash (any non-zero result means we need to save)
    HAL_StatusTypeDef SaveDeviceConfig();
    HAL_StatusTypeDef EraseDeviceConfig();

#ifdef __cplusplus
}
#endif
    
#endif

