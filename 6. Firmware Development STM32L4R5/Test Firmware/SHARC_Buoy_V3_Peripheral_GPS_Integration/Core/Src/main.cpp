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


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
// extern RTC_HandleTypeDef hrtc; //RTC Handler Instance

 uint8_t GPS_On = 0; //flag to show if sensor is online

 uint8_t IR_On = 0; //flag to show if Iridium is online

 uint8_t wavebuffer[WAVEBUFFER_SIZE];



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void);

/**
  * @brief function to handle failures in Peripheral initialization functions
  * @param None
  * @retval None
  */
void Error_Handler(void);

///**
//  * @brief Place code for IMU Event Detection here
//  * @param None
//  * @retval None
//  */
//static void Routine_ASYNC_IMU_EVENT(void);


/*
 * @brief Code for Reset State Routine
 * @param None
 * @retval None
 */
static void Routine_STATE_RESET(void);

/*
 * @brief Code for Sleep State Routine
 * @param None
 * @retval None
 */
static void Routine_STATE_SLEEP(void);

/*
 * @brief Code for Sample State Routine
 * @param None
 * @retval None
 */
static void Routine_STATE_SAMPLE(void);

/*
 * @brief Code for Transmit State Routine
 * @param None
 * @retval None
 */
static void Routine_STATE_TRANSMIT(void);
/*
 * @brief Code for Init State Routine
 * @param None
 * @retval None
 */
static void Routine_Init_STATE(void);

}	/*Extern C*/
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

	printmsg("SHARC BUOY STARTING! \r\n");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

//=================================== 1. END ====================================//

	//======================= 2. POWER AND RESET STATE CHECK ========================//

		/*
		 * When system powers on, check for any asynchronous resets that
		 * may have occured. Use this area to add in any reset handling
		 */
			if(__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) == SET)
			{
			  BOR_Handler();
			}
			uint8_t flag = __HAL_RCC_GET_PORRST_FLAG();
			if(flag  == SET)
			{
			  printmsg("Software Reset Detected. Initializing main program...\r\n");
			  POR_Handler();
			}
	//=================================== 2. END ====================================//


		  /* Infinite loop START */
		  while (1)
		  {

	//=========================== 3. SYSTEM STATE CHECK =============================//
			  	  /*
			  	   * Main Loop state detection: use this area to implement state
			  	   * check.States are positive integers written to Back up Register
			  	   * 0. State functions include Reading/ Writing to Back Up register
			  	   * determing previous state before sleep and writing state to back up register
			  	   * states are defined in the enum Buoy_State_typedef. The state check block performs the following routine
			  	   *
			  	   */

			  	  //enable access to back up registers
			  	  switch(__GET_PREV_STATE())
			  	  {
			  	  	 case STATE_RESET:
			  	  	 //system encountered a power on reset, put peripherals here
			  	  	 Current_State = STATE_SAMPLE;
			  	  	 break;

			  	  	 case STATE_SAMPLE:
			  	  	 //check how many samples have been recorded by the Buoy
			  	  	 sample_count = __GET_SAMPLE_COUNT();
			  	  	 if(sample_count >= 2)
			  	  	 {
			  	  		 //set next Buoy State to Transmit
			  	  		 Current_State = STATE_TRANSMIT;
			  	  		 IMU_On = 1;
			  	  	 }
			  	  	 // Set Buoy Next state to Sleep
			  	  	 else
			  	  	 {
			  	  		 IMU_On = 0;
			  	  		 Current_State = STATE_SLEEP;
			  	  		 __HAL_RCC_PWR_CLK_ENABLE();
			  	  		 __SET_CURRENT_STATE(Current_State);
			  	  		 __HAL_RCC_PWR_CLK_DISABLE();
			  	  	 }
			  	  	 break;

			  	  	 case STATE_SLEEP:
			  	  	hrtc.Instance = RTC;					 			//attach RTC instance to handler
			  	  	HAL_PWREx_DisableInternalWakeUpLine();				//clear wake up pending interrupt from internal wake up
			  	  	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);					//clear pending interrupt from ext wake up pins
			  	  	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
			  		set_WUP_Pin(IMU_EVENT_WAKE_PIN,MODE_EXTI); 	  		//reconfigure wake up pins
			  	  	Current_State = STATE_SAMPLE;
			  	  	 break;

			  	  	 case STATE_TRANSMIT:
			  	  	 Current_State = STATE_SLEEP;
			    		 __SET_CURRENT_STATE(Current_State);
			  	  	 break;

			  	  	 //default case: reset state
			  	  	 default:
			  	  	 Current_State = STATE_INIT;
			  	  }
			  	  __HAL_RCC_PWR_CLK_DISABLE();

	//=================================== 3. END ====================================//

	//============================== 4. STATE FUNCTIONS =============================//

			  	  /*
			  	   * Place Routine code Here
			  	   */
			  	  if(Current_State == STATE_INIT)
			  	  {
			  		  Routine_Init_STATE();
			  		  Current_State = STATE_RESET;
			  	  }

			  	  if(Current_State == STATE_RESET)
			  	  {
			  	  	Routine_STATE_RESET();
			  	  }
			  	  // SLEEP STATE
			  	  else if(Current_State == STATE_SLEEP)
			  	  {
			  		  Routine_STATE_SLEEP();
			  	  }
			  	  //RESET STATE

			  	  //SAMPLE STATE
			  	  else if(Current_State == STATE_SAMPLE)
			  	  {
			  		  Routine_STATE_SAMPLE();
			  	  }
			  	  //TRANSMIT STATE
			  	  else if(Current_State == STATE_TRANSMIT)
			  	  {
			  		  Routine_STATE_TRANSMIT();
			  	  }
			  	  // ADDITONAL STATE FUNCTIONS HERE:

	//=================================== 4. END ====================================//
	//========================= 5. END OF ROUTINE FUNCTION ==========================//
				  /*
				   * After each routine has run, save state to the back up registers
				   */
				  __HAL_RCC_PWR_CLK_ENABLE();
				  if(Current_State == STATE_SAMPLE)			//increment sample counter after each sampe
				  {
					  sample_count = __GET_SAMPLE_COUNT();
					  __SET_SAMPLE_COUNT(++sample_count);
				  }


				  __SET_CURRENT_STATE(Current_State);	    //write value to back up register
				  __HAL_RCC_PWR_CLK_DISABLE();

	//=================================== 5. END ====================================//
		 }
			/* Infinite loop END*/


}

//==================== 6. Configuration & Initialization Functions ====================//

/* Private functions */

static void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
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

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 12;
  sTime.Minutes = 57;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_FRIDAY;
  sDate.Month = RTC_MONTH_MAY;
  sDate.Date = 8;
  sDate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  //clear unwanted interrupts
  if(__HAL_RTC_WAKEUPTIMER_GET_FLAG(&hrtc,RTC_FLAG_WUTF))
  {
	  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc,RTC_FLAG_WUTF);
  }



}

//====================================== 6. END ======================================//

//==================================== 7. Handlers ===================================//

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

//===================================== 7. END ======================================//

//=============================== 8. Routines =======================================//
static void Routine_STATE_RESET(void)
{
	 //initialise RTC
	 MX_RTC_Init();
	 //Enable Interrupt pins as EXTI Outputs
	 //set_WUP_Pin(IMU_EVENT_WAKE_PIN,MODE_EXTI);
	 printmsg("Device Online!\r\n");
	 printmsg("Current State: RESET \t Next State: SAMPLE\r\n");
//	 HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,SET);

}

static void Routine_STATE_SLEEP(void)
{
	  printmsg("Current State: SLEEP \t Next State: SAMPLE\r\n");
	  printmsg("Good Night! \r\n");
	  Go_To_Sleep(STDBY,T_SLEEP);
}

static void Routine_STATE_SAMPLE(void)
{
	//Initialize RTC struct to get current time
	RTC_TimeTypeDef gTime;

	//Log initial time
	Sample_Time_Start = HAL_GetTick();

	//Get Previous Directory and Log Numbers for SD Cards
	  __HAL_RCC_PWR_CLK_ENABLE();
	  waveLogNo = (RTC->BKP0R)&0xFF;
	  waveDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  gpsLogNo = (RTC->BKP0R)&0xFF;
	  gpsDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  envLogNo = (RTC->BKP0R)&0xFF;
	  envDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  pwrLogNo = (RTC->BKP0R)&0xFF;
	  pwrDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  __HAL_RCC_PWR_CLK_DISABLE();


	  //Revert all logs to zero - except wave logs
	  waveLogNo = 0;
	  gpsLogNo = 0;
	  envLogNo = 0;
	  pwrLogNo = 0;



	//SD Init Routine
	if(SD_Init()==SD_OK)
	{
		printmsg("SD Card online \r\n");
	}
	else
	{
		printmsg("SD Card offline \r\n");
	}

	  //GPS  Init Routine
	  GPS_Data_t Gdata;
	  sample_count = __GET_SAMPLE_COUNT();
	  if(sample_count <= 2)
	  {
		  printmsg("Current State: SAMPLE \t Next State: SLEEP\r\n");
	  } else
	  {
		  printmsg("Current State: SAMPLE \t Next State: TRANS\r\n");
		  IMU_On = 1;
	  }

	  //initialise gps peripherals and begin comms on sensor instanc


		  // Sample Routine

		  if(GPS_On)
		  {

			  	  GPS_InterruptsOn();

			  	  HAL_Delay(5000);


			  	  GPS_Update();

				  printmsg("Logging Data...\r\n");
//				  HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,SET);
				  Gdata.coordinates = gpsDataLive.coordinates;
				  Gdata.diag = gpsDataLive.diag;
				  printmsg("local time: %lu, position: %f Lat, %f long\r\n", Gdata.coordinates.time, Gdata.coordinates.lat, Gdata.coordinates.longi);
				  printmsg("HDOP = %d.%d, \t PDOP = %d.%d, VDOP = %d.%d\r\n",  Gdata.diag.HDOP.digit, Gdata.diag.HDOP.precision,  Gdata.diag.PDOP.digit, Gdata.diag.PDOP.precision,  Gdata.diag.VDOP.digit, Gdata.diag.VDOP.precision, Gdata.diag.num_sats);
				  printmsg("Number of Satellites %d, Fix Type = %d\r\n", Gdata.diag.num_sats, Gdata.diag.fix_type);

				  // Record all GPS data onto SD cards
				  uint8_t tempGPSBuf[500];
				  SD_GPS_Open(&File, &Dir, &fno, gpsDirNo, gpsLogNo);
				  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
				  sprintf((char *)tempGPSBuf, "%d:%d:%d, %ld, %ld, %ld, %ld, %ld, %d.%d, %d.%d, %d.%d, %d, %d \r\n", gTime.Hours, gTime.Minutes, gTime.Seconds,  Gdata.coordinates.lat,  Gdata.coordinates.longi, Gdata.coordinates.time, Gdata.diag.HDOP.digit, Gdata.diag.HDOP.precision,  Gdata.diag.PDOP.digit, Gdata.diag.PDOP.precision, Gdata.diag.VDOP.digit, Gdata.diag.VDOP.precision, Gdata.diag.fix_type);
				  SD_File_Write(&File, tempGPSBuf);
				  SD_File_Close(&File);
				  SD_Unmount(SDFatFs);

				  GPS_InterruptsOff();

		  }
		else
		  {
			  printmsg("Error GPS Not Found!\r\n");
		  }




	  // Environmental Sensor Init Routine
	  BMP_Init_Typedef BMP_InitStruct = {0};
	  //configure device for environmental sensing
	  BMP_InitStruct.BMP_Pressure_OverSample = BMP280_CTRLMEAS_OSRSP_OS_1;
	  BMP_InitStruct.BMP_Temperature_OverSample = BMP280_CTRLMEAS_OSRST_OS_1;
	  BMP_InitStruct.BMP_IIR_FILTER_COEFFICIENTS = BMP280_CONFIG_FILTER_COEFF_OFF;
	  BMP_InitStruct.BMP_Power_Mode = BMP280_CTRLMEAS_MODE_FORCED;
	  if(BMP280_Init(&BMP_InitStruct) == BMP_OK)
	  {
		  printmsg("Environmental Sensor Online!\r\n");
		  //create variables
		  uint32_t temp,press;
		  int32_t t_fine;
		  for (int i = 0; i < 10; ++i) //60 second compensation period for averaging
		  {
			BMP280_Force_Measure(&temp,&press);		//trigger conversion
			Gdata.env_Temp = BMP280_Compensate_Temp(temp,&t_fine,bmp.Factory_Trim);			//compensate temperature
			Gdata.atm_Press = BMP280_Compensate_Pressure(press,t_fine,bmp.Factory_Trim)/256;	//compensate pressure
			HAL_Delay(1000);

		  }
		  printmsg("Temp = %ld�C \t Pressure = %lu Pa \r\n",Gdata.env_Temp,Gdata.atm_Press);

		  //Store environmental samples
		  uint8_t tempENVBuf[200];
		  SD_ENV_Open(&File, &Dir, &fno,envDirNo, envLogNo);
		  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
		  sprintf((char *)tempENVBuf, "%d:%d:%d, %ld, %lu \r\n", gTime.Hours, gTime.Minutes, gTime.Seconds, Gdata.env_Temp, Gdata.atm_Press);
		  SD_File_Write(&File, tempENVBuf);
		  SD_File_Close(&File);
		  SD_Unmount(SDFatFs);
		  envDirNo++;
		  envLogNo++;

	  }
	  else
	  {
		  printmsg( "BMP280 offline! \r\n");
	  }

	  //INA219 Sample Routine
	  if(INA219_Init_Sensor() == INA_OK)
	  {
		  int16_t p_temp = 0;
		  printmsg("INA219 Ready! \r\n");
		  //Trigger a conversion
		  INA219_Trigger_Conversion(2);
		  //read registers
		  INA219_Get_Shunt_Voltage((int16_t *)&Gdata.shunt_v);
		  INA219_Get_Bus_Voltage((int16_t *)&Gdata.bus_v);
		  INA219_Get_Current((int16_t *)&Gdata.current);
		  INA219_Get_Power(&p_temp);
		  Gdata.power = (ina.INA219_P_LSB*(float)p_temp)*1000;
		  printmsg("V_Shunt %d mV V_Bus %d mV Current %d mA Power %d mW\r\n",Gdata.shunt_v,Gdata.bus_v, Gdata.current,Gdata.power);

		  uint8_t tempPWRBuf[200];
		  SD_ENV_Open(&File, &Dir, &fno,pwrDirNo, pwrLogNo);
		  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
		  sprintf((char *)tempPWRBuf, "%d:%d:%d, %d, %d, %d, %d \r\n", gTime.Hours, gTime.Minutes, gTime.Seconds, Gdata.shunt_v, Gdata.bus_v, Gdata.current, Gdata.power);
		  SD_File_Write(&File, tempPWRBuf);
		  SD_File_Close(&File);
		  SD_Unmount(SDFatFs);
		  pwrDirNo++;
		  pwrLogNo++;
	  }


	  /* High Frequency IMU sampling */

	  //Temporary variables related to IMU sampling
	  int32_t accelTemp[3];
	  int32_t gyroTemp[3];
	  uint8_t tempFIFOBuf[500];
	  uint8_t imu[12] = {0};
	  uint8_t data_status;

	  IMU_On = 1;

	  SD_Wave_Open(&File, &Dir, &fno, waveDirNo, waveLogNo);

		  if((ICM20649_Init_IMU(GYRO_CONFIG_FSSEL_500DPS, ACC_CONFIG_AFSSEL_4G, ACCEL_DPLFCFG_1, GYRO_DPLFCFG_0) == IMU_OK))
		  	  {

			  while (IMU_On)
			  {

				  if(imu_sample_count== WAVELOGBUFNO)
					 {
						SD_File_Close(&File); //NB Remember to close file
						waveLogNo++;
						imu_sample_count = 0;
						SD_Wave_Open(&File, &Dir, &fno, waveDirNo, waveLogNo);
						printmsg("New Wave log! \r\n");
					 }

				  	ICM20649_Is_Data_Ready(&hi2c1, &data_status);

					if(data_status)
					{

						ICM20649_Get_IMU_RawData(&hi2c1, imu);

						HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);

						accelTemp[0] = ( (int16_t) (imu[0] << 8) | imu[1]);
						accelTemp[1] = ( (int16_t) (imu[2] << 8) | imu[3]);
						accelTemp[2] = ( (int16_t) (imu[4] << 8) | imu[5]);
						gyroTemp[0] = ( (int16_t) (imu[6] << 8) | imu[7]);
						gyroTemp[1] = ( (int16_t) (imu[8] << 8) | imu[9]);
						gyroTemp[2] = ( (int16_t) (imu[10] << 8) | imu[11]);

					   //printmsg("Ax      Ay      Az      Gx      Gy      Gz \r\n");
					   //printmsg("%d  %d  %d  %d  %d  %d \r\n", accelTemp[0], accelTemp[1], accelTemp[2], gyroTemp[0], gyroTemp[1],gyroTemp[2]);

					   sprintf((char *)tempFIFOBuf, "%d:%d:%d, %ld, %ld, %ld, %d.%d, %d.%d, %d.%d \r\n", gTime.Hours, gTime.Minutes, gTime.Seconds,  accelTemp[0], accelTemp[1], accelTemp[2], gyroTemp[0], gyroTemp[1], gyroTemp[2]);
					   SD_File_Write(&File, tempFIFOBuf);

					   imu_sample_count++;

					}


					  if(waveLogNo == WAVELOGNO+1)
					  {
						  SD_File_Close(&File); //NB Remember to close file
						  waveDirNo++;
						  waveLogNo = 0 ;
						  break;
					  }

			  }

		  	  }

		  	  else
		  	  {
		  		  printmsg("IMU Offline!\r\n");
		  	  }

		  ICM20649_Deinit_IMU();
		  SD_Unmount(SDFatFs);

		  IMU_On = 0;

	//Store updated directory and log numbers
	  __HAL_RCC_PWR_CLK_ENABLE();
	  WRITE_REG(RTC->BKP1R,(RTC->BKP1R &0xFF00)|(waveLogNo));
	  WRITE_REG(RTC->BKP1R,(RTC->BKP1R &0xFF)|((waveDirNo)<<8));
	  WRITE_REG(RTC->BKP2R,(RTC->BKP2R &0xFF00)|(gpsLogNo));
	  WRITE_REG(RTC->BKP2R,(RTC->BKP2R &0xFF)|((gpsDirNo)<<8));
      WRITE_REG(RTC->BKP3R,(RTC->BKP3R &0xFF00)|(envLogNo));
	  WRITE_REG(RTC->BKP3R,(RTC->BKP3R &0xFF)|((envDirNo)<<8));
	  WRITE_REG(RTC->BKP4R,(RTC->BKP4R &0xFF00)|(pwrLogNo));
	  WRITE_REG(RTC->BKP4R,(RTC->BKP4R &0xFF)|((pwrDirNo)<<8));
	  __HAL_RCC_PWR_CLK_DISABLE();

	  Sample_Time = HAL_GetTick() - Sample_Time_Start;

}


static void Routine_STATE_TRANSMIT(void)
{

	  printmsg("Current State: TRANS \t Next State: SLEEP\r\n");


	  //Get Previous Directory and Log Numbers for SD Cards
	  __HAL_RCC_PWR_CLK_ENABLE();
	  waveLogNo = (RTC->BKP0R)&0xFF;
	  waveDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  gpsLogNo = (RTC->BKP0R)&0xFF;
	  gpsDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  envLogNo = (RTC->BKP0R)&0xFF;
	  envDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  pwrLogNo = (RTC->BKP0R)&0xFF;
	  pwrDirNo = ((RTC->BKP0R)&0xFF00)>>8;
	  __HAL_RCC_PWR_CLK_DISABLE();

	  //Transfer Buffer
	  uint8_t GPS_trans_Buffer[340];
	  uint8_t WAVE_trans_Buffer[340];

	  //File pointer
	  uint32_t fpointer = 0;

	  //Enable SD card interface
	  SD_Init();

	  //Create Temporary Arrays
	  float32_t gpsData[9] = {0};
	  float32_t envData[3] = {0};
	  float32_t pwrData[5] = {0};


	  //GPS Buffer - Log GPS data here
	  GPS_Data_t GdataT; //GPS struct used for transmission and binary conversion

	  /* First GPS Buffer */

	  //Get GPS data from SD card
	  fpointer = 0;
	  SD_GPS_Read(&File, gpsData, gpsDirNo-1, gpsLogNo, &fpointer);
	  SD_File_Close(&File);

	  //Note: gpsData[0] is a timestamp
	  GdataT.coordinates.lat =  gpsData[1];
	  GdataT.coordinates.longi = gpsData[2];
	  GdataT.diag.HDOP.digit = (uint8_t)gpsData[3];
	  GdataT.diag.HDOP.precision = (uint8_t)gpsData[4];
	  GdataT.diag.VDOP.digit = (uint8_t)gpsData[5];
	  GdataT.diag.VDOP.precision = (uint8_t)gpsData[6];
	  GdataT.diag.PDOP.digit = (uint8_t)gpsData[7];
	  GdataT.diag.PDOP.precision = (uint8_t)gpsData[8];

	  //Get Environmental data from SD card
	  fpointer = 0;
	  SD_ENV_Read(&File, envData, envDirNo-1, envLogNo, &fpointer);
	  SD_File_Close(&File);

	  //ENV Data
	  //Note: envData[0] is a timestamp
	  GdataT.env_Temp = (uint32_t)envData[1];
	  GdataT.atm_Press = (uint32_t)envData[2];

	  //Get power data from SD Card
	  fpointer = 0;
	  SD_PWR_Read(&File, pwrData, pwrDirNo-1, pwrLogNo, &fpointer);
	  SD_File_Close(&File);

	  //PWR Data
	  //Note: pwrData[0] is a timestamp
	  GdataT.shunt_v = pwrData[1];
	  GdataT.bus_v = pwrData[2];
	  GdataT.current = pwrData[3];
	  GdataT.power = pwrData[4];


	  //Convert GData Buffer to binary
	  uint8_t* buffer = to_binary_format_GPS(GdataT, (__GET_SAMPLE_COUNT()-1) );

	  //Populate first packet of GPS data into array
	  memcpy(&GPS_trans_Buffer[0], buffer, DRIFTBUFFER_SIZE);

	  /* Second GPS Buffer */

  	  //Get GPS data from SD card
	  fpointer = 0;
	  SD_GPS_Read(&File, gpsData, gpsDirNo, gpsLogNo, &fpointer);
	  SD_File_Close(&File);

	  //Note: gpsData[0] is a timestamp
	  GdataT.coordinates.lat =  gpsData[1];
	  GdataT.coordinates.longi = gpsData[2];
	  GdataT.diag.HDOP.digit = (uint8_t)gpsData[3];
	  GdataT.diag.HDOP.precision = (uint8_t)gpsData[4];
	  GdataT.diag.VDOP.digit = (uint8_t)gpsData[5];
	  GdataT.diag.VDOP.precision = (uint8_t)gpsData[6];
	  GdataT.diag.PDOP.digit = (uint8_t)gpsData[7];
	  GdataT.diag.PDOP.precision = (uint8_t)gpsData[8];

	  //Get Environmental data from SD card
	  fpointer = 0;
	  SD_ENV_Read(&File, envData, envDirNo-1, envLogNo, &fpointer);
	  SD_File_Close(&File);

	  //ENV Data
	  //Note: envData[0] is a timestamp
	  GdataT.env_Temp = (uint32_t)envData[1];
	  GdataT.atm_Press = (uint32_t)envData[2];

	  //Get power data from SD Card
	  fpointer = 0;
	  SD_PWR_Read(&File, pwrData, pwrDirNo, pwrLogNo, &fpointer);
	  SD_File_Close(&File);

	  //PWR Data
	  //Note: pwrData[0] is a timestamp
	  GdataT.shunt_v = pwrData[1];
	  GdataT.bus_v = pwrData[2];
	  GdataT.current = pwrData[3];
	  GdataT.power = pwrData[4];

	  //Convert GData Buffer to binary
	  buffer = to_binary_format_GPS(GdataT, __GET_SAMPLE_COUNT());

	  //Populate Second packet of GPS data into array
	  memcpy(&GPS_trans_Buffer[DRIFTBUFFER_SIZE], buffer, DRIFTBUFFER_SIZE);

	  //Wave Buffer
	  //Calculate wave parameter extraction for previous two logs
	  Wave_Data_t waveData1;
	  fullPipeline(waveData1, waveDirNo-1); //get wave data from previous record
	  Wave_Data_t waveData2;
	  fullPipeline(waveData2, waveDirNo); //get wave data from previous record

	  buffer = to_binary_format_Wave(waveData1, __GET_SAMPLE_COUNT() -1);

	  memcpy(&WAVE_trans_Buffer[0], buffer, WAVEBUFFER_SIZE);

	  buffer = to_binary_format_Wave(waveData2, __GET_SAMPLE_COUNT());

	  memcpy(&WAVE_trans_Buffer[WAVEBUFFER_SIZE], buffer, WAVEBUFFER_SIZE);

	  //Dismount SD cards! DO NOT WANT MOUNTED SD CARDS DURING IRIDIUM TRANSMISSION
	  SD_Unmount(SDFatFs);

	  uint8_t retry = 0;
	  IR_On = 1;
	  while (IR_Init_Module() != IR_OK)
	  {
		  IR_DeInit_Module();
		  if(retry == 20)
		  {
			  IR_On = 0;
			  break;
		  }
		retry++;

	  }
	  if(IR_On)
	  {

		  printmsg("Preparing To Transmit...");
		  //getlength of data


		  /* 3. Upload Drift Data */
		  IR_Status_t flag;
		 for (int i = 0; i < 2; ++i)
		 {
			 flag = (i<1)? IR_send_Bin_String(GPS_trans_Buffer,sizeof(GPS_trans_Buffer)):IR_send_Bin_String(WAVE_trans_Buffer,sizeof(WAVE_trans_Buffer));

	  	  if(flag == IR_MSG_UPLOAD_OK)
	  	  {
		  	  printmsg("Message Uploaded!\r\nTransmitting...");
		  	  //create SBD Session
		  	  SBDX_Status_t sbd;
		  	  for (int i = 0; i < 5; ++i)
		  	  {
		  		  if(IR_start_SBD_Session(&sbd)== IR_OK)
		  		  {
		  			 		  	  //check return status
		  	  		  if(sbd.MO_Status < 2)
		  	  		  {
		  			  	  //message sent
		  	  			  IR_send_AT_CMD("AT+SBDD0\r");
		  			  	  printmsg("Success!\r\n");
		  			  	  break;
		  		  	  }else
		  		  	  {
		  		  		  printmsg("Failed!\r\n");

		  		  	  }
		 	  	  }
		  		  HAL_Delay(1000);
		  	  }
	  		  IR_send_AT_CMD("AT+SBDD0\r");
	  	  }

		 }
	  }
	  IR_DeInit_Module();
/* Reset Memory pointer*/
  //reset sample count
  __SET_SAMPLE_COUNT(0);
  //erase page and reset counter


}

static void Routine_Init_STATE(void)
{
	//Initialize and configure the SD cards
	printmsg("Setting Up SD Cards...\r\n");

	//Initial log and directory values for SD cards
	waveLogNo = 1;
	waveDirNo = 1;
	gpsLogNo = 1;
	gpsDirNo = 1;
	envLogNo = 1;
	envDirNo = 1;
	pwrLogNo = 1;
	pwrDirNo = 1;

	//Store current SD and log numbers variable in RTC->BCKUP//
	 __HAL_RCC_PWR_CLK_ENABLE();
	 WRITE_REG(RTC->BKP1R,(RTC->BKP1R &0xFF00)|(waveLogNo));
	 WRITE_REG(RTC->BKP1R,(RTC->BKP1R &0xFF)|((waveDirNo)<<8));
	 WRITE_REG(RTC->BKP2R,(RTC->BKP2R &0xFF00)|(gpsLogNo));
	 WRITE_REG(RTC->BKP2R,(RTC->BKP2R &0xFF)|((gpsDirNo)<<8));
     WRITE_REG(RTC->BKP3R,(RTC->BKP3R &0xFF00)|(envLogNo));
	 WRITE_REG(RTC->BKP3R,(RTC->BKP3R &0xFF)|((envDirNo)<<8));
     WRITE_REG(RTC->BKP4R,(RTC->BKP4R &0xFF00)|(pwrLogNo));
	 WRITE_REG(RTC->BKP4R,(RTC->BKP4R &0xFF)|((pwrDirNo)<<8));
	 __HAL_RCC_PWR_CLK_DISABLE();

	 /* Test Iridium Modem */
	 /*uint8_t retries = 0;
	 while(retries++ < 20)
	 {
		 if(IR_Init_Module() == IR_OK)
	 	 {
			 IR_On = 1;
			 break;
	 	 }
	 	 IR_DeInit_Module();
	 }
	 if(IR_On)
	 {
		 printmsg("Iridium Module online!\r\n");
	 }else
	 {
		 printmsg("Error Connecting To Modem\r\n");
	 }
	 IR_DeInit_Module(); */

	 /* Test BMP280 Sensor*/
	 BMP_Init_Typedef BMP_InitStruct = {0};
	 BMP280_Init_Preset_Mode(Weather_Monitoring,&BMP_InitStruct);
	 if(BMP280_Init(&BMP_InitStruct) == BMP_OK)
	 {
		 printmsg("Environmental Sensor Online!\r\n");
	 }else
	 {
		 printmsg("Environmental Sensor Offline!\r\n");
	 }

	 /* Test INA 219 Sensor */
	 if(INA219_Init_Sensor() == INA_OK)
	 {
		 printmsg("Current Monitor Online!\r\n");
	 } else
	 {
		 printmsg("Current Monitor Offline!\r\n");
	 }

	 /* Test INA 219 Sensor */
 if(GPS_Init() == GPS_Init_OK)
 {
	 printmsg("GPS Online!");
	 GPS_InterruptsOff();
	 GPS_On = 1;
 } else
 {
	 printmsg("GPS offline!\r\n");
 }

	 /* Test SD Cards */
	 if(SD_Init() == SD_OK)
	 {
		 printmsg(" SD Cards Online! \r\n");
	 }
	 else
	 {
		 printmsg("SD Cards Offline! \r\n");
	 }

	 /* Test ICM20649 Sensor */

	if(ICM20649_Init_IMU(GYRO_CONFIG_FSSEL_500DPS, ACC_CONFIG_AFSSEL_4G, ACCEL_DPLFCFG_1, GYRO_DPLFCFG_0) == IMU_OK)
	 {
		 printmsg("IMU Online \r\n");
	 }else
	 {
		 printmsg("IMU Offline \r\n");
	 }
	ICM20649_Deinit_IMU();

}


//===================================== 8. END ======================================//

