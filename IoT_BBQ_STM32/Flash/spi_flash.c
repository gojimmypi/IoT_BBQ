#include "spi_flash.h"

#include "stdint.h"
#include <stdlib.h> // needed for malloc see https://stackoverflow.com/questions/1230386/why-do-i-get-a-warning-every-time-i-use-malloc
#include <string.h>


// define is_spi_flash_simulation when we don't actually have an spi_flash to play with


#ifdef is_spi_flash_simulation

static uint8_t* SimulatedFlash = NULL;
static int IsSimInitialized = 0;
static int SimStartAddress = 0;
static int SimSize = 0;

// the simulation of sFLASH_ReadBuffer just returns the value of savedValue
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t* res = NULL;
    res = memcpy(pBuffer, SimulatedFlash + ReadAddr, NumByteToRead); 
}

// the simulation of sFLASH_WriteBuffer just  puts the pBuffer in our savedValue
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    if (pBuffer == NULL)
    {
        // when pBuffer is NULL, that's our simulation que to use parameters as sizing
        if (IsSimInitialized == 0)
        {
            if (NumByteToWrite < 1)
            {
                NumByteToWrite = 1;
            }
            SimulatedFlash = malloc(NumByteToWrite);      
            IsSimInitialized = 1; // ensure we don't repeat malloc
            SimStartAddress = WriteAddr;
            SimSize = NumByteToWrite;
        }
        else
        {
            // TODO warning when re-init attempt
        }
    }
    else
    {
       // our simulated flash has already been initialized, so write our pBuffer to the simulated flash at an offset of [WriteAddr]
        uint8_t* res = NULL;
        res = memcpy(SimulatedFlash + WriteAddr, pBuffer, NumByteToWrite);
    }
}

// the simulation of sFLASH_EraseBulk clears the savedValue
void sFLASH_EraseBulk(void)
{
    if (IsSimInitialized != 0)
    {
        // free(SimulatedFlash);
        
        uint8_t* res = NULL;
        res = memset(SimulatedFlash, 0, SimSize);
    }
    else
    {
        // TODO warn that flash simulation is not initialized
    }
}

// the simulation of sFLASH_Init sets flash params to uninitialized values. 
// to set, call sFLASH_WriteBuffer with NULL buffer:
//   sFLASH_WriteBuffer(NULL, UsingFlashAddress, MaxFlashTestSize);
void sFLASH_Init(void)
{
    SimSize = 0;
    SimulatedFlash = NULL;
    IsSimInitialized = 0;
}



#else
    // actual SPI code goes here

    error no SPI code implemented
#endif // not is_spi_flash_simulation
