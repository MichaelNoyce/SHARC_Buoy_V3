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
 * NB: get_fattime must be updated in the fatfs.c file to use f_utime and timestamp functions
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
 * sd_status_t
 *
 * @brief:	Used to represent numeric statuses returned as a result of
 * 		    running SDMMC interface
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
	SD_TIME_ERROR,
}sd_status_t;

//========================== 4. Global Variables ==========================================

FATFS SDFatFs; /* File system object for User logical drive */
FIL File; /* File object */
DIR Dir; /*Directory Object*/
FILINFO fno;

//============================= 5. Defines ===============================================

#define SD_Detect_Pin GPIO_PIN_3
#define SD_Detect_GPIO_Port GPIOF

//============================= 6. Handlers ===============================================

CRC_HandleTypeDef hcrc;

UART_HandleTypeDef hlpuart1;

SD_HandleTypeDef hsd1;

RTC_HandleTypeDef hrtc; // this is only included for the standalone module - remove if using code with own RTC


//======================== 7. SD Configuration Functions =========================================


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

//======================== 6. SD Read/Write Functions ============================================

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

/**
 * @brief Closes current file directory
 *
 * @param myFile
 * @return
 */
sd_status_t SD_Dir_Close(DIR *myDir);


/**
 * @brief Time-stamps myFile with current time from RTC
 *
 * @param myFile
 * @return
 */
sd_status_t SD_File_TimeStamp(FIL *myFile);



/**
 * @brief Function to write local IMU data buffers to SD card
 *
 * Description: The function takes a individual IMU sample segment from local memory and appends it to a numbered wave log file.
 * After a determined number of buffers have been added, close file and start new file.
 *
 * @param myFile
 * @param waveLogNo
 * @param waveBufferSegment
 * @param FIFOCount
 * @return
 */
sd_status_t SD_Wave_Store(FIL *myFile, DIR *myDir, FILINFO* fno, uint32_t waveLogNo, uint8_t *waveBufferSegment, uint8_t* FIFOCount);



/**
 * @brief Function to read the most recent waveBuffer file within the last sampling period. Increments to nth most recent
 * file with each invocation.
 *
 * If the file is empty, next most recent full file is used and number of wave buffers for use in wave
 * parameter extraction is decremented.
 *
 * Excludes files outside of previous 30 minute sampling period
 *
 * @param myFile
 * @param waveFileNo
 * @param timePeriod
 * @return
 */
sd_status_t SD_Wave_Read(FIL *myFile, uint32_t waveFileNo, uint32_t timePeriod);




/**
 * @brief Stores local GPS data buffer on SD card
 *
 * @param myFile
 * @param GPSFileNo
 * @param timePeriod
 * @return
 */
sd_status_t SD_GPS_Store(FIL *myFile, uint32_t GPSFileNo, uint32_t timePeriod);


/**
 * @brief Reads last GPS data buffer stored on SD card
 *
 * @param myFile
 * @param GPSFileNo
 * @param timePeriod
 * @return
 */
sd_status_t SD_GPS_Read(FIL *myFile, uint32_t GPSFileNo, uint32_t timePeriod);








#endif /* HAL_SD_H_ */
