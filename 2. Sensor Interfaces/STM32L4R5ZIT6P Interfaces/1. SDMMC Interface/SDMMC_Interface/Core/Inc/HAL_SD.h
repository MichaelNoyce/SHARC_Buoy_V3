/*
 * HAL_SD.h
 *
 *  Created on: Apr 20, 2022
 *      Author: Michael Noyce
 *      Student No: NYCMIC002
 *      For: The University of Cape Town
 *
 *  This Library is designed to be used with the STM32 HAL Driver files version 1.15.1
 *  Version 1.14.x is also supported
 *
 *  This library is designed to interface with SD card external memory using the
 *  onboard SDMMC driver on the STM32
 *
 *  This library contains all the functions and definitions to interface with and configure the sensor.
 *  This includes functions that
 *
 *  1. Configure the SD card and FATFS
 *  2. Open files
 *  3. Read files
 *  4. Create Files
 *
 *
 */

#ifndef HAL_SD_H_
#define HAL_SD_H_

//============================= 1. Includes ==============================================

#include "stm32l4xx_hal.h"	//HAL library includes
#include "math.h"			//Math Functions
#include "stdint.h"			//integers
#include "string.h"			//Mem functions
#include "fatfs.h"
#include "stdio.h"
//========================== 2. Structs & Enums ===========================================

/*
 * IMU_Status_t
 *
 * @brief:	Used to represent numeric statuses returned as a result of
 * 		    running Sensor-register level functions e.g. using i2c to write
 * 		    a value for Power mode. Successful return
 */
typedef enum
{
	SD_SDMMC_ERROR,
	SD_INIT_ERROR,
	SD_MOUNT_ERROR,
	SD_CLOSE_ERROR,
	SD_OPEN_ERROR,
	SD_WRITE_ERROR,
	SD_CRC_ERROR,
	SD_DMA_ERROR,
	SD_OK,
}sd_status_t;

//========================== 4. Global Variables ==========================================



//============================= 5. Handlers ===============================================

CRC_HandleTypeDef hcrc;

UART_HandleTypeDef hlpuart1;

SD_HandleTypeDef hsd1;

//======================== 6. SD Configuration Functions =========================================


/*Function Name sd_status_t SD_Init(void);
 *
 * @brief: Initialise SD Interface
 *
 */

sd_status_t SD_Init(void);

/*Function Name sd_status_t SD_Mount(uint8_t mount);
 *
 * @brief: Mount SD Card
 *
 */
sd_status_t SD_Mount(FATFS SDFatFs, char myPath[]);

/*Function Name sd_status_t SD_File_Open(FIL myfile);
 *
 * @brief: Open file on SD Card
 *
 */
sd_status_t SD_File_Open(FIL *myFile, uint32_t fileNo);

/*Function Name sd_status_t SD_File_Write(FIL myfile, uint8_t dataBuffer[]);
 *
 * @brief: Write to SD Card
 *
 */
sd_status_t SD_File_Write(FIL *myFile, uint8_t *dataBuffer);

/*Function Name sd_status_t SD_File_Close(FIL myfile)
 *
 * @brief: Close File on SD Card
 *
 */
sd_status_t SD_File_Close(FIL *myFile);


//======================== 6. SD Read/Write Functions ============================================

#endif /* HAL_SD_H_ */
