#include "Flash_Sim_Demo.h"
#include "Flash/spi_flash.h"

#ifdef __cplusplus
extern "C" {
#endif


	void Flash_Sim_Demo() {
        // 
        // -------------------------------------------------------------------------
        // flash testing for Exercise 3b
        // -------------------------------------------------------------------------
        //

        // initialize SPI Flash
        sFLASH_Init();

#ifdef is_spi_flash_simulation
        uint32_t UsingFlashAddress = 0x1000;
        uint32_t MaxFlashTestSize = 0x1FFF;

        // when writing NULL during simulation, the parameters are actually setup for stating address and max size
        sFLASH_WriteBuffer(NULL, UsingFlashAddress, MaxFlashTestSize);
#endif

        // setup some data
        uint8_t someData = 42;
        uint8_t someOtherData = 0x55;

        uint8_t* otherData = &someOtherData;
        uint8_t* thisFlashData = &someData;
        uint32_t thisFlashAddress = 0x1234;
        uint32_t thisFlashTestSize = 1;

        // sample write
        sFLASH_WriteBuffer(thisFlashData, thisFlashAddress, thisFlashTestSize);


        // sample read
        sFLASH_ReadBuffer(otherData, thisFlashAddress, thisFlashTestSize);


        // sample erase
        sFLASH_EraseBulk();


        // sample read after erase
        sFLASH_ReadBuffer(thisFlashData, thisFlashAddress, thisFlashTestSize);

	}

#ifdef __cplusplus
}
#endif    


