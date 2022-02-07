#include "spi_flash.h"

#include "stdint.h"
#include <stdlib.h> // needed for malloc see https://stackoverflow.com/questions/1230386/why-do-i-get-a-warning-every-time-i-use-malloc
#include <string.h>

// see https://github.com/STMicroelectronics/STM32CubeL4/blob/f93a2f74f8e9912405dbf1a297b6df0c423eddf2/Projects/32L4R9IDISCOVERY/Examples/FLASH/FLASH_EraseProgram/Inc/main.h
#define ADDR_FLASH_PAGE_255   ((uint32_t)0x080FF000) /* Base @ of Page 255, 4 Kbytes this is the last 4K of 1MB flash: 1048576 - 4096 = 1044480 ; 0x100000 - 0x01000  = FF000 */

// define is_spi_flash_simulation when we don't actually have an spi_flash to play with
#define FLASH_ROW_SIZE          64

    /* !!! Be careful the user area should be in another bank than the code !!! */
#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_255   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     FLASH_USER_START_ADDR + 0x0FFF       /* End @ of user Flash area */


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
#include  <stm32l4xx_hal_flash.h>

// actual SPI code goes here

void sFLASH_Init()
{
    
}

void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    
}

void sFLASH_EraseBulk(void)
{
    
}

void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite) 
{
    
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

void flash_test()
{
    
    /* Private typedef -----------------------------------------------------------*/
    /* Private define ------------------------------------------------------------*/

    /* Private macro -------------------------------------------------------------*/
    /* Private variables ---------------------------------------------------------*/
    uint32_t BankNumber = 0;
    uint32_t Address = 0, PAGEError = 0;
    __IO uint32_t MemoryProgramStatus = 0;
    __IO uint64_t data64 = 0;

    /*Variable used for Erase procedure*/
    static FLASH_EraseInitTypeDef EraseInitStruct;    

    
    /* Table used for fast programming */
    // see https://stackoverflow.com/questions/44443619/how-to-write-read-to-flash-on-stm32f4-cortex-m4
    // see https://github.com/gojimmypi/IoT_BBQ/commit/95d8862e57ac7b4acde8f23305d0a0f8d061411a#diff-947cad9d8806e1f3e06bc4a751f2f9b4ca05367b64068dfc15ac1904fc2d4890
    // see https://github.com/STMicroelectronics/STM32CubeL4/issues/61
    __attribute__((__section__(".user_data")))  static const uint64_t Data64_In_Flash[FLASH_ROW_SIZE] = {
  0x1212121212121212, 0x1111111111111111, 0x2222222222222222, 0x3333333333333333,
  0x4444444444444444, 0x5555555555555555, 0x6666666666666666, 0x7777777777777777,
  0x8888888888888888, 0x9999999999999999, 0xAAAAAAAAAAAAAAAA, 0xBBBBBBBBBBBBBBBB,
  0xCCCCCCCCCCCCCCCC, 0xDDDDDDDDDDDDDDDD, 0xEEEEEEEEEEEEEEEE, 0xFFFFFFFFFFFFFFFF,
  0x0011001100110011, 0x2233223322332233, 0x4455445544554455, 0x6677667766776677,
  0x8899889988998899, 0xAABBAABBAABBAABB, 0xCCDDCCDDCCDDCCDD, 0xEEFFEEFFEEFFEEFF,
  0x2200220022002200, 0x3311331133113311, 0x6644664466446644, 0x7755775577557755,
  0xAA88AA88AA88AA88, 0xBB99BB99BB99BB99, 0xEECCEECCEECCEECC, 0xFFDDFFDDFFDDFFDD};

    static const uint64_t NewData[FLASH_ROW_SIZE] = {
  0x1313113131313131, 0x1111111111111111, 0x2222222222222222, 0x3333333333333333,
  0x4444444444444444, 0x5555555555555555, 0x6666666666666666, 0x7777777777777777,
  0x8888888888888888, 0x9999999999999999, 0xAAAAAAAAAAAAAAAA, 0xBBBBBBBBBBBBBBBB,
  0xCCCCCCCCCCCCCCCC, 0xDDDDDDDDDDDDDDDD, 0xEEEEEEEEEEEEEEEE, 0xFFFFFFFFFFFFFFFF,
  0x0011001100110011, 0x2233223322332233, 0x4455445544554455, 0x6677667766776677,
  0x8899889988998899, 0xAABBAABBAABBAABB, 0xCCDDCCDDCCDDCCDD, 0xEEFFEEFFEEFFEEFF,
  0x2200220022002200, 0x3311331133113311, 0x6644664466446644, 0x7755775577557755,
  0xAA88AA88AA88AA88, 0xBB99BB99BB99BB99, 0xEECCEECCEECCEECC, 0xFFDDFFDDFFDDFFDD};
    
    uint32_t src_addr = (uint32_t)NewData;
    uint8_t data_index = 0;
    
/* Private function prototypes -----------------------------------------------*/
    
    
        HAL_FLASH_Unlock();

        /* Erase the user Flash area
          (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

        /* Clear OPTVERR bit set on virgin samples */
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR); 

        /* Get the bank */
        BankNumber = GetBank(FLASH_USER_START_ADDR);

        /* Fill EraseInit structure*/
        EraseInitStruct.TypeErase = FLASH_TYPEERASE_MASSERASE;
        EraseInitStruct.Banks     = BankNumber;
        if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
        {
            /*
              Error occurred while mass erase.
              User can add here some code to deal with this error.
              To know the code error, user can call function 'HAL_FLASH_GetError()'
          */
          /* Infinite loop */
            while (1)
            {
                // TODO
                HAL_Delay(1000);
            }
        }  
    
    Address = FLASH_USER_START_ADDR;

    while (Address < (FLASH_USER_END_ADDR - (FLASH_ROW_SIZE*sizeof(uint64_t))))
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, Address, (uint64_t)src_addr) == HAL_OK)
        {
            Address = Address + (FLASH_ROW_SIZE*sizeof(uint64_t));
        }
        else
        {
            /* Error occurred while writing data in Flash memory.
               User can add here some code to deal with this error */
            while (1)
            {
                // TODO
                HAL_Delay(1000);
            }
        }
    }

    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST_AND_LAST, Address, (uint64_t)src_addr) != HAL_OK)
    {
        /* Error occurred while writing data in Flash memory.
           User can add here some code to deal with this error */
        while (1)
        {
            HAL_Delay(1000);
        }
    }

    /* Lock the Flash to disable the flash control register access (recommended
       to protect the FLASH memory against possible unwanted operation) *********/
    HAL_FLASH_Lock();

    /* Check if the programmed data is OK
        MemoryProgramStatus = 0: data programmed correctly
        MemoryProgramStatus != 0: number of words not programmed correctly ******/
    Address = FLASH_USER_START_ADDR;
    MemoryProgramStatus = 0x0;

    while (Address < FLASH_USER_END_ADDR)
    {
        for (data_index = 0; data_index < FLASH_ROW_SIZE; data_index++)
        {
            data64 = *(__IO uint64_t *)Address;
    
            if (data64 != Data64_In_Flash[data_index])
            {
                MemoryProgramStatus++;
            }
            Address = Address + sizeof(uint64_t);
        }
    }

    /*Check if there is an issue to program data*/
    if (MemoryProgramStatus == 0)
    {
        /* No error detected. Switch on LED1*/
       
    }
    else
    {
        /* Error detected. Switch on LED2*/
        // TODO
        while (1) ;
    }
}

#endif // not is_spi_flash_simulation
