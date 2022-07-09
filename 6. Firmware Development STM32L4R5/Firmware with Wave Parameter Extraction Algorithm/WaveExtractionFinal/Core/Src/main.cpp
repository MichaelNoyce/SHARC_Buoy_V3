/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wformat"


#include "M9N_STM32.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "M9N_C_API.h"
#include "HAL_INA219.h"
#include "HAL_Iridium.h"
#include "HAL_BMP280.h"
#include "HAL_ICM20649.h"
#include "HAL_SD.h"
#include "stm32l4xx_hal.h"	//HAL library
#include "waveFunctions.h"
#include "Sharc_Frame.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
GPS_Data_t gpsDataLive;
}/*Extern C*/
/* USER CODE END PFP */

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **  IMPORTANT NOTE!
 **  The symbol VECT_TAB_SRAM needs to be defined when building the project
 **  if code has been located to RAM and interrupts are used.
 **  Otherwise the interrupt table located in flash will be used.
 **  See also the <system_*.c> file and how the SystemInit() function updates
 **  SCB->VTOR register.
 **  E.g.  SCB->VTOR = 0x20000000;
 **
 **
 **===========================================================================
 **/

int main(void)
{
//======================== 1. SYSTEM INIT & CLOCK CONFIG ========================//

	HAL_Init();				//Init Flash prefetch, systick timer, NVIC and LL functions
	SystemClock_Config();	//configure clock
	//GPIO_Set_Pin_LP();		//Configure all unused GPIO pins to low Power mode
	Init_Debug();			// initialize debug peripherals

	printmsg("Wave Spectra Test \r\n");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

//=================================== 1. END ====================================//

	  //Wave Buffer
	  //Calculate wave parameter extraction for previous two logs
	  //Wave_Data_t waveData1;
	  //fullPipeline(waveData1, waveDirNo-1); //get wave data from previous record
	  //Wave_Data_t waveData2;
	  //fullPipeline(waveData2, waveDirNo); //get wave data from previous record


}


//===================================== 8. END ======================================//

