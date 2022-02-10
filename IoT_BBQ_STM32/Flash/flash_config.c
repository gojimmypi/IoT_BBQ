#include "flash_config.h"
#include <stm32l4xx.h>
#include <stm32l4xx_hal_flash.h>

#include <string.h>

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

#ifdef __cplusplus
extern "C" {
#endif
    

    // a couple of references PROVIDE'd by linker file
    extern int __flash_data_start__;
    extern int __flash_data_end__;

#define ADDR_FLASH_DATA_START   ((uint32_t)&(__flash_data_start__)) /* Base @ of Page 255, 4 Kbytes this is the last 4K of 1MB flash: 1048576 - 4096 = 1044480 ; 0x100000 - 0x01000  = FF000 */
#define ADDR_FLASH_DATA_END     ((uint32_t)&(__flash_data_end__))   

#define FLASH_ROW_SIZE          64


    // FLASH_CONFIG is the data actually on the flash. See DeviceFlashConfig()
    __attribute__((__section__(".flash_user_data"))) static const struct FlashConfig FLASH_CONFIG;

    // CACHE_CONFIG is the runtime, updatable copy of the config. See DeviceCacheConfig()
    static struct FlashConfig CACHE_CONFIG;

    /*Variable used for Erase procedure*/


    
    struct FlashConfig* DeviceFlashConfig()
    {
        return (struct FlashConfig *)&FLASH_CONFIG;
    };
    

    static int IsInitialized = 0;

    // instead of a global variable, we have this function for a struct pointer to our device config    

    // by default we just return the current cache of the flash config (we don't read from flash every time for performance)
    // see below for optional update-time save option
//    struct FlashConfig* DeviceCacheConfig()
//    {
//        return DeviceFlashConfig(NoSave);
//    };

    // when passing a WithSave paramter, the cach will also be written to flash before returning
    // be aware of performance penalty when doing this frequently
    struct FlashConfig* DeviceCacheConfig(DeviceConfigSaveOption SaveOption) 
    {
        if (IsInitialized)
        {
            // we've already copied the Read-Only flash to our working RW cache
        }
        else
        {
            // copy the config in flash to our writable cache config
            memcpy((uint32_t *)&CACHE_CONFIG, (uint32_t *)&FLASH_CONFIG, sizeof(FLASH_CONFIG));

            if (CACHE_CONFIG.MajorVersion <= (uint8_t)(0) )
            {
                // if we find all 0xFF in flash, then we assume the flash was erased, but never written
            
                uint8_t* thisValuePtr8; // setup a reusable pointer to what are normally struct const uint8_t values;
                uint32_t* thisValuePtr32; // setup a reusable pointer to what are normally struct const uint32_t values;
            
                thisValuePtr32 = (uint32_t*)&CACHE_CONFIG.FLASH_START;
                *thisValuePtr32 = ADDR_FLASH_DATA_START;
                
                thisValuePtr8 =  (uint8_t*)&CACHE_CONFIG.MajorVersion; // point to the read-only MajorVersion
                *thisValuePtr8 = FlashConfigMajorVersion; // update const value CACHE_CONFIG.MajorVersion
            
                thisValuePtr8 =  (uint8_t*)&CACHE_CONFIG.MinorVersion;
                *thisValuePtr8 = FlashConfigMinorVersion; // update const value CACHE_CONFIG.FlashConfigMinorVersion
            }
            IsInitialized = 1;
        }

        // optional write to flash as requested, but only if needed:
        if ((SaveOption == WithSave) && FlashNeedsUpdate())
        {
            SaveDeviceConfig();
        }
        
        // return the result: a struct pointer to the cache of device config in RAM (which is a copy of read-only flash) 
        return (struct FlashConfig *)&CACHE_CONFIG;
    };

    uint32_t FlashNeedsUpdate()
    {
        uint32_t res = 0;
        // there's no struct compare, so we'll do a byte-by-byte compare
        uint8_t* thisCachePtr8; // setup a reusable pointer to cach data
        uint8_t* thisFlashPtr8; // setup a reusable pointer to cach data
        
        for (size_t i = 0; i < sizeof(CACHE_CONFIG); i++)
        {
            thisCachePtr8 = i + (uint8_t*)&CACHE_CONFIG;
            thisFlashPtr8 = i + (uint8_t*)&FLASH_CONFIG;
            if (*thisCachePtr8 == *thisFlashPtr8)
            {
                // equal
            }
            else
            {
                res++;
            }
        }
        
        return res;
    } 
/**
  * @brief  Gets the bank of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
    static uint32_t GetBank(uint32_t Addr)
    {
        uint32_t bank = 0;
  
        if (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE) == 0)
        {
            /* No Bank swap */
            if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
            {
                bank = FLASH_BANK_1;
            }
            else
            {
                bank = FLASH_BANK_2;
            }
        }
        else
        {
            /* Bank swap */
            if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
            {
                bank = FLASH_BANK_2;
            }
            else
            {
                bank = FLASH_BANK_1;
            }
        }
  
        return bank;
    }

    // Erase the device config in Flash. THis is usually because we want to take the CACHE_CONFIG and save it to Flash
    HAL_StatusTypeDef EraseDeviceConfig()
    {
        HAL_StatusTypeDef res = HAL_OK;
        HAL_StatusTypeDef thisStepResult = HAL_OK;

        static FLASH_EraseInitTypeDef EraseInitStruct;    

        uint32_t PAGEError = 0;
        uint32_t BankNumber = 0;

        HAL_FLASH_Unlock();

        /* Erase the user Flash area
          (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

        /* Clear OPTVERR bit set on virgin samples */
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 

        /* Get the bank */
        BankNumber = GetBank(ADDR_FLASH_DATA_START);

        /* Fill EraseInit structure*/
        EraseInitStruct.TypeErase = FLASH_TYPEERASE_MASSERASE;
        EraseInitStruct.Banks     = BankNumber;

        // TODO wrap in RTOS safe
        thisStepResult = HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
        
        if (thisStepResult == HAL_OK)
        {
            // success
        }
        else
        {
            /*
              Error occurred while mass erase.
              User can add here some code to deal with this error.
              To know the code error, user can call function 'HAL_FLASH_GetError()'
            */
            res = thisStepResult;
        }  
        
        HAL_FLASH_Lock();
        
        return res;
    }
    
    /// Save the device config to flash
    HAL_StatusTypeDef SaveDeviceConfig()
    {
        HAL_StatusTypeDef res = HAL_OK;
        HAL_StatusTypeDef thisStepResult = HAL_OK;
        
        uint32_t Address = 0, PAGEError = 0;
        uint32_t src_addr = (uint32_t)&CACHE_CONFIG;

        /* Erase the user Flash area
          (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

        thisStepResult = EraseDeviceConfig();
        if (thisStepResult == HAL_OK)
        {
            // success
            /* Clear OPTVERR bit set on virgin samples */
            __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 
            Address = ADDR_FLASH_DATA_START;
    
            HAL_FLASH_Unlock();

            while (Address <= (ADDR_FLASH_DATA_END))
            {
                // TODO wrap in RTOS safe
                thisStepResult = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, Address, (uint64_t)src_addr);
                if (thisStepResult == HAL_OK)
                {
                    Address = Address + (FLASH_ROW_SIZE*sizeof(uint64_t));
                }
                else
                {
                    /* Error occurred while writing data in Flash memory.
                       User can add here some code to deal with this error */
                    res = thisStepResult;
                }
            }
            
            HAL_FLASH_Lock();
        }
        else
        {
            /*
              Error occurred while mass erase.
              User can add here some code to deal with this error.
              To know the code error, user can call function 'HAL_FLASH_GetError()'
            */
            res = thisStepResult;
        }
    
        /* Lock the Flash to disable the flash control register access (recommended
           to protect the FLASH memory against possible unwanted operation) *********/
        return res;
    }
    
#ifdef __cplusplus
}
#endif
