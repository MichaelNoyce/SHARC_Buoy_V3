/*
 * HAL_SD.c
 *
 *  Created on: Apr 20, 2022
 *      Author: Michael Noyce
 */


//======================== 1. Includes ==============================================================

#include "HAL_SD.h"
#include "string.h"
#include "main.h"

//======================== 2. Private Variables =====================================================

//uint8_t I2C_TX_CPLT;	//Flag signaling completion of I2C DMA transfer

//======================== 3. Static Functions Prototypes ===========================================
static void MX_GPIO_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_CRC_Init(void);
static void MX_RTC_Init(void);
void MX_FATFS_Init();

//======================== 4. Static Functions Definition ===========================================

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();


  /*Configure GPIO pin : SD_Detect_Pin */
  GPIO_InitStruct.Pin = SD_Detect_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SD_Detect_GPIO_Port, &GPIO_InitStruct);


}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 1;
  hsd1.Init.Transceiver = SDMMC_TRANSCEIVER_DISABLE;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}


/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x20;
  sTime.Minutes = 0X20;
  sTime.Seconds = 0x00;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_SUNDAY;
  sDate.Month = RTC_MONTH_MAY;
  sDate.Date = 0x22;
  sDate.Year = 0x22;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}



//======================== 5. MSP Function Definitions ==================================
/* MSP FUNCTIONS:
 *
 *  Functions designed to replace the _weak MSP peripheral initialization
 *  function definitions in the HAL Library files.
 *
 *  NB!!!! before running the code do the following:
 *
 *  1. Uncomment the desired MSP Function
 *
 *  2. Cut the function and paste it in the stm32l4xx_hal_msp.c file
 *
 *  3. In the stm32l4xx_hal_msp.c file, include the header "HAL_BMP280.h"
 */



//======================== 6. SD Configuration Functions =========================================


sd_status_t SD_Init(void)
{
	MX_FATFS_Init();
	MX_GPIO_Init();
	MX_SDMMC1_SD_Init();
	//MX_CRC_Init();
	MX_RTC_Init(); // remove if program has own RTC

	return SD_OK;
}

sd_status_t SD_Mount(FATFS SDFatFs, char diskPath[])
{

	if(f_mount(&SDFatFS, (TCHAR const*)diskPath, 0) != FR_OK)
	{
	  return SD_MOUNT_ERROR;
	}

	return SD_OK;
}

sd_status_t SD_File_Open(FIL *myFile, uint32_t fileNumber)
{
	  printmsg("SDMMC Interface Starting! \r\n");
	  char diskPath[10]; /* User logical drive path */
	  sd_status_t errorCode;
	  FRESULT res;
	  uint32_t byteswritten = 0;

	  errorCode = SD_Init();
	  printmsg("Error Code, %d \r\n", errorCode);

	  if(SD_Mount(SDFatFs, diskPath) == SD_OK)
	  {
		  printmsg("Mounted successfully!");
		  sprintf(diskPath, "Log%ld.txt", fileNumber);
		   if(f_open(myFile, (const TCHAR*)diskPath, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
		    {
			  printmsg("Opened file!");
		    }
		  else
		  {
			return SD_OPEN_ERROR;
			printmsg("Open failed!");
		  }
	  }
	  else
	  {
		  printmsg("Mount failed");
		  return SD_MOUNT_ERROR;
	  }

	  return SD_OK;

}

sd_status_t SD_File_Write(FIL *myFile, uint8_t *dataBuffer)
{

	uint32_t byteswritten = 0 ;  /* File write counts */

	if(f_write(myFile, dataBuffer, strlen((char *)dataBuffer), (void *)&byteswritten)!= FR_OK)
	{
		printmsg("Write failed!");
		return SD_WRITE_ERROR;
	}

	if(byteswritten == 0)
    {
	  printmsg("Write failed!");
  	  return SD_WRITE_ERROR;
    }



	return SD_OK;
}

sd_status_t SD_File_Close(FIL *myFile)
{
	if(f_close(myFile) != FR_OK)
	{
		printmsg("Close Failed!");
		return SD_CLOSE_ERROR;
	}

	return SD_OK;
}

/**
 * @brief Closes Current Directory
 *
 * @param myDir
 * @return
 */
sd_status_t SD_Dir_Close(DIR *myDir)
{
	if(f_closedir(myDir) != FR_OK)
	{
		printmsg("CloseDir Failed!");
		return SD_CLOSE_ERROR;
	}

	return SD_OK;
}

/**
 * @brief Manually timestmap file if get_fattime() in fatfs.c is not used
 *
 * @param myFile
 * @return
 */
sd_status_t SD_File_TimeStamp(FIL *myFile)
{
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);

	FILINFO fno;

	fno.fdate = (WORD)(((gDate.Year - 1980) * 512U) | gDate.Month * 32U | gDate.Date);
	fno.ftime = (WORD)(gTime.Hours * 2048U | gTime.Minutes * 32U | gTime.Seconds / 2U);


	if(f_utime(myFile, &fno) != FR_OK)
		{
			printmsg("Timestamp Failed!");
			return SD_TIME_ERROR;
		}

		return SD_OK;

}





/**
 * @brief Function to open a wave log file for writing local data buffers to.
 *
 * Description: The function opens a wavLog file in a waveDir directory to be written to
 *
 *
 * @param myFile
 * @param waveBufferSegment
 * @return
 */
sd_status_t SD_Wave_Store(FIL *myFile, DIR *myDir, FILINFO* fno, uint32_t waveDirNo, uint32_t waveLogNo)
{

	 printmsg("SDMMC Interface Starting! \r\n");
     char diskPath[100]; /* User logical drive path */
     char dirPath[100];

	  if(SD_Mount(SDFatFs, diskPath) == SD_OK)
	  {
		  printmsg("Mounted successfully!");

		  sprintf(dirPath, "/WaveDir%ld", waveDirNo);

		  if(f_stat((const TCHAR*)dirPath, fno) == FR_NO_FILE)
		  {
			  if(f_mkdir((const TCHAR*)dirPath) != FR_OK)
			  {
			  	printmsg("Directory not created");
			  }
		  }

			  sprintf(diskPath, "WaveDir%ld/WaveLog%ld.txt",waveDirNo, waveLogNo);

			  if(f_open(myFile, (const TCHAR*)diskPath, FA_OPEN_APPEND | FA_WRITE) == FR_OK)
			  {
				  printmsg("Opened file!");
			  }
			  else
			  {
				  printmsg("Open failed!");
				  return SD_OPEN_ERROR;
			  }
	  }
	  else
	  {
		   printmsg("Mount failed");
		   return SD_MOUNT_ERROR;
	  }


	  return SD_OK;


}


