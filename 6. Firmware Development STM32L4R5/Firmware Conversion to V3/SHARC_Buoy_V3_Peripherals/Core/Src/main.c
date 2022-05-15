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

	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_Delay(500);



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
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}



/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
