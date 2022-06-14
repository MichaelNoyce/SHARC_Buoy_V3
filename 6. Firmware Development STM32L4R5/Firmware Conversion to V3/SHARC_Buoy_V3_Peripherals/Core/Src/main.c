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
#include "HAL_GPS.h"
#include "HAL_INA219.h"
#include "HAL_Iridium.h"
#include "HAL_BMP280.h"
#include "Sharc_Frame.h"
#include "HAL_ICM20649.h"
#include "HAL_SD.h"
#include "stm32l4xx_hal.h"	//HAL library
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
 RTC_HandleTypeDef hrtc; //RTC Handler Instance

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

/**
  * @brief Place code for IMU Event Detection here
  * @param None
  * @retval None
  */
static void Routine_ASYNC_IMU_EVENT(void);


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

	printmsg("SHARC BUOY STARTING!");
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

//========================= 3. ASYNCHRONOUS STATE CHECK ===========================//

		  /*
		   * If an interrupt occurred while the device was sleeping, check the
		   * flags to determine if this occurred
		   */

		  //check for interrupts on wake up pins during deep sleep
		  __HAL_RCC_PWR_CLK_ENABLE();
		  if(__HAL_PWR_GET_FLAG(IMU_EVENT_WAKE_FLAG)|| __HAL_PWR_GET_FLAG(IRIDIUM_RING_WAKE_FLAG))
		  {
			  Current_State = __GET_PREV_STATE();			//get previous state from back up reg
			  if(__HAL_PWR_GET_FLAG(IMU_EVENT_WAKE_FLAG))
			  {
				  __HAL_PWR_CLEAR_FLAG(IMU_EVENT_WAKE_FLAG);	//clear  flag in PWR SR
				  Routine_ASYNC_IMU_EVENT();				//Perform IMU Event Detection Routine
			  }
			  if(__HAL_PWR_GET_FLAG(IRIDIUM_RING_WAKE_FLAG))	//clear  flag in PWR SR
			  {
				__HAL_PWR_CLEAR_FLAG(IRIDIUM_RING_WAKE_FLAG);
				Routine_ASYNC_IRIDIUM_RX();

			  }
			  if(Current_State == STATE_SLEEP)				//return to sleep if Interrupt event handled before wake up
			  {

				  printmsg("System Going Back To Sleep\r\n"); 	//check how long device was asleep for
				  set_WUP_Pin(IMU_EVENT_WAKE_PIN, MODE_WUP);	//reenable wake up pins
				  Go_To_Sleep(STDBY,T_SLEEP);						//return to sleep
			  }
			  	 else
			  {

			  	  printmsg("Going Back to Main Loop:\r\n");		//if come from wake mode
				  __SET_CURRENT_STATE(STATE_ASYNCINT);
			  }
		  }

//=================================== 3. END ====================================//

//=========================== 4. SYSTEM STATE CHECK =============================//
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
		  	  	 case STATE_ASYNCINT:
		  	  	 case STATE_RESET:
		  	  	 //system encountered a power on reset, put peripherals here
		  	  	 Current_State = STATE_SAMPLE;
		  	  	 break;

		  	  	 case STATE_SAMPLE:
		  	  	 //check how many samples have been recorded by the Buoy
		  	  	 sample_count = __GET_SAMPLE_COUNT();
		  	  	 if(sample_count > 3)
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

//=================================== 4. END ====================================//

//============================== 5. STATE FUNCTIONS =============================//

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

//=================================== 5. END ====================================//
//========================= 6. END OF ROUTINE FUNCTION ==========================//
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

//=================================== 6. END ====================================//
	 }
		/* Infinite loop END*/
}

//==================== 7. Configuration & Initialization Functions ====================//

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

//====================================== 7. END ======================================//

//==================================== 8. Handlers ===================================//

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

//===================================== 8. END ======================================//

//=============================== 9. Routines =======================================//
static void Routine_ASYNC_IMU_EVENT(void)
{
	 printmsg("IMU Event Detected: Sampling...");
	 for (int i = 0; i < 50; ++i)
	 {
	 	HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
	 	HAL_Delay(100);
	 }
	 printmsg("Done\r\n");
}



static void Routine_STATE_RESET(void)
{
	 //initialise RTC
	 MX_RTC_Init();
	 //Enable Interrupt pins as EXTI Outputs
	 set_WUP_Pin(IMU_EVENT_WAKE_PIN,MODE_EXTI);
	 printmsg("Device Online!\r\n");
	 printmsg("Current State: RESET \t Next State: SAMPLE\r\n");
	 HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,SET);


}

static void Routine_STATE_SLEEP(void)
{
	  printmsg("Current State: SLEEP \t Next State: SAMPLE\r\n");
	  printmsg("Good Night! \r\n");
	  set_WUP_Pin(IMU_EVENT_WAKE_PIN,MODE_WUP);
	  Go_To_Sleep(STDBY,T_SLEEP);
}

static void Routine_STATE_SAMPLE(void)
{
	  //GPS  Init Routine
	  GPS_Data_t Gdata;
	  sample_count = __GET_SAMPLE_COUNT();
	  if(sample_count < 3)
	  {
		  printmsg("Current State: SAMPLE \t Next State: SLEEP\r\n");
	  } else
	  {
		  printmsg("Current State: SAMPLE \t Next State: TRANS\r\n");
		  IMU_On = 1;
	  }

	  /* Attempt to initialize sensor within a number of retries */
	  uint8_t retries = 0;
	  do
	  {
		  //initialise gps peripherals and begin comms on sensor instance
		  if(init_GPS(&hgps)== GPS_Init_OK)
		  {
			 printmsg("GPS Online! Acquiring Signal...\r\n");
			 GPS_On = 1;
			 break;
		  }
		deinit_GPS(&hgps);
		retries++;
	  }
	  while (retries < GPS_INIT_RETRIES);

	  // Sample Routine

	  if(GPS_On)
	  {
		  	  int x = HAL_GetTick();
			  while(packet_full != 7)
			  {
				  GPS_Log_Begin();
				  int y = HAL_GetTick()- x;
				  if(y >  30000) //30s to acquire signal
				  {
					  printmsg("Failed to Acquire Signal\r\n");
					  break;
				  }

			  }
			  GPS_Log_Stop();
			  printmsg("Logging Data...\r\n");
			  HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,SET);
			  Gdata.coordinates = GPS_coord;
			  Gdata.Etime = eTime;
			  Gdata.diag = diag;
			  printmsg("local time: %lu, position: %f Lat, %f long\r\n", Gdata.Etime, Gdata.coordinates.lat, Gdata.coordinates.longi);
			  printmsg("HDOP = %d.%d, \t PDOP = %d.%d, VDOP = %d.%d\r\n",  Gdata.diag.HDOP.digit, Gdata.diag.HDOP.precision,  Gdata.diag.PDOP.digit, Gdata.diag.PDOP.precision,  Gdata.diag.VDOP.digit, Gdata.diag.VDOP.precision);
			  printmsg("Number of Satellites %d, Fix Type = %d\r\n", Gdata.diag.num_sats, Gdata.diag.fix_type);

		  deinit_GPS(&hgps);
	  }else
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
		  for (int i = 0; i < 5; ++i)
		  {
			BMP280_Force_Measure(&temp,&press);		//trigger conversion
			Gdata.env_Temp = BMP280_Compensate_Temp(temp,&t_fine,bmp.Factory_Trim);			//compensate temperature
			Gdata.atm_Press = BMP280_Compensate_Pressure(press,t_fine,bmp.Factory_Trim)/256;	//compensate pressure

		  }
		  printmsg("Temp = %ld�C \t Pressure = %lu Pa \r\n",Gdata.env_Temp,Gdata.atm_Press);
	  }

	  //INA219 Sample Routine
	  if(INA219_Init_Sensor() == INA_OK)
	  {
		  int16_t p_temp = 0;
		  printmsg("INA219 Ready! \r\n");
		  //Trigger a conversion
		  INA219_Trigger_Conversion(2);
		  //read registers
		  INA219_Get_Shunt_Voltage(&Gdata.shunt_v);
		  INA219_Get_Bus_Voltage(&Gdata.bus_v);
		  INA219_Get_Current(&Gdata.current);
		  INA219_Get_Power(&p_temp);
		  Gdata.power = (ina.INA219_P_LSB*(float)p_temp)*1000;
		  printmsg("V_Shunt %d mV V_Bus %d mV Current %d mA Power %d mW\r\n",Gdata.shunt_v,Gdata.bus_v, Gdata.current,Gdata.power);
	  }

	  /* High Frequency IMU sampling */

	  int32_t accelTemp[3];
	  int32_t gyroTemp[3];
	  uint8_t tempFIFOBuf[500];
	  uint8_t imu[12] = {0};
	  RTC_TimeTypeDef gTime;
	  uint8_t data_status;

	  waveDirNo = 1;
	  waveLogNo = 1;
	  fifo_sample_complete = 0;
	  SD_Wave_Open(&File, &Dir, &fno, waveDirNo, waveLogNo);

	  while (1)
	  {
		  if((ICM20649_Init_IMU(GYRO_CONFIG_FSSEL_500DPS, ACC_CONFIG_AFSSEL_4G, ACCEL_DPLFCFG_1, GYRO_DPLFCFG_0) != IMU_OK))
		  	  {
			  while (1)
			  {

				  if(imu_sample_count== WAVELOGBUFNO)
					 {
						SD_File_Close(&File); //NB Remember to close file
						waveLogNo++;
						imu_sample_count = 0;
						SD_Wave_Open(&File, &Dir, &fno, waveDirNo, waveLogNo);
						printmsg("New log! \r\n");
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

					   printmsg(tempFIFOBuf, "%d:%d:%d, %ld, %ld, %ld, %ld, %ld, %ld \r\n", gTime.Hours, gTime.Minutes, gTime.Seconds,  accelTemp[0], accelTemp[1], accelTemp[2], gyroTemp[0], gyroTemp[1], gyroTemp[2]);
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

	  }


}

static void Routine_STATE_TRANSMIT(void)
{
	  printmsg("Current State: TRANS \t Next State: SLEEP\r\n");

	  //Enable SD card interface

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

		  uint8_t trans_Buffer[256];

		  /* Load data Frome Memory*/
		 /* FLASH_SetAddress(0x00,0x00,0x01);
		 memcpy(trans_Buffer,FLASH_READ_BufferHF(chip,BUFFER1),256);*/

		  /* 3. Upload Drift Data */
		  IR_Status_t flag;
		 for (int i = 0; i < 2; ++i)
		 {
			 flag = (i<1)? IR_send_Bin_String(trans_Buffer,(4*DRIFTBUFFER_SIZE)):IR_send_Bin_String(wavebuffer,WAVEBUFFER_SIZE);

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
	printmsg("Setting Up Flash Chips...\r\n");
	uint8_t status;

	uint32_t backup_val;


	//Store Chip status variable in RTC->BCKUP byte 0 : chip status, byte 1 : active chip, byte 2: back up chip
	 __HAL_RCC_PWR_CLK_ENABLE();
	 RTC->BKP1R = backup_val;
	 __HAL_RCC_PWR_CLK_DISABLE();

	 /* Test Iridium Modem */
	 uint8_t retries = 0;
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
	 IR_DeInit_Module();

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

	 /* Test MPU6050 Sensor */

	/* if(MPU6050_Init_MPU(GYRO_CONFIG_FSSEL_500DPS,ACC_CONFIG_AFSSEL_2G,CONFIG_DLFP_2) == MPU_OK)
	 {
		 printmsg("IMU Online\r\n");
		 //perform self-test
		 float test_results[6];
		 MPU6050_SelfTest(&hi2c1,test_results);
	 }else
	 {
		 printmsg("IMU Offline\r\n");
	 }
	 MPU6050_Deinit_MPU(); */

}
//===================================== 9. END ======================================//

