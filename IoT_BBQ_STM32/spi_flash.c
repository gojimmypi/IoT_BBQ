#include "_stdint.h"

// define is_spi_flash_simulation when we don't actually have an spi_flash to play with
#define is_spi_flash_simulation


#ifdef is_spi_flash_simulation

static uint8_t* savedValue;

// the simulation of sFLASH_ReadBuffer just returns the value of savedValue
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    pBuffer = savedValue;
}

// the simulation of sFLASH_WriteBuffer just  puts the pBuffer in our savedValue
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    savedValue = pBuffer;
}

// the simulation of sFLASH_EraseBulk clears the savedValue
void sFLASH_EraseBulk(void)
{
    savedValue = 0;
}

// the simuilation of sFLASH_Init calls sFLASH_EraseBulk
void sFLASH_Init(void)
{
    sFLASH_EraseBulk();
}



#else
    // actual SPI code goes here
    error no SPI code implemented
#endif // not is_spi_flash_simulation
