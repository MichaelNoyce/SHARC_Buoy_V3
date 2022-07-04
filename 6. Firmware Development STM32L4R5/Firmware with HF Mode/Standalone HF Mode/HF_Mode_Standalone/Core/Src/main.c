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
#include <stdarg.h>
#include "stdio.h"
#include "string.h"
#include "HAL_SD.h"
#include "HAL_ICM20649.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FILE_FIFO_BUF_NO 72 // 72 x 3.4 second buffer = 244.8 seconds = 04:04:08

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef hlpuart1;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void printmsg(char *format,...);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_LPUART1_UART_Init();

  /* USER CODE BEGIN 2 */


  if((ICM20649_Init_IMU(GYRO_CONFIG_FSSEL_500DPS, ACC_CONFIG_AFSSEL_4G, ACCEL_DPLFCFG_1, GYRO_DPLFCFG_0) != IMU_OK))
  {
	  printmsg("Error in IMU Init\r\n");
  }
  else
  {
	  printmsg("Init successful! \r\n");
  }


   if(SD_Init()!= SD_OK)
   {
	   printmsg("SD not initialised correctly!");
   }
   else
   {
	   printmsg("SD Initialised correctly!");
   }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int32_t accelTemp[3];
  int32_t gyroTemp[3];
  uint8_t tempFIFOBuf[500];
  uint8_t imu[12] = {0};
  int32_t Ax, Ay, Az, Gx, Gy, Gz;
  RTC_TimeTypeDef gTime;
  RTC_DateTypeDef gDate;
  uint8_t data_status;

  waveDirNo = 1;
  waveLogNo = 1;
  fifo_sample_complete = 0;
  SD_Wave_Open(&File, &Dir, &fno, waveDirNo, waveLogNo);

  uint8_t acc_smplrt[2];

  ICM20649_Register_Bank_Select(&hi2c1, 2);
  HAL_I2C_Mem_Read(&hi2c1, IMU_Device_Address, ACCEL_SMPLRT_DIV_1, 1, acc_smplrt, 2, 100);
  ICM20649_Register_Bank_Select(&hi2c1, 0);

  printmsg("Acc smplrt %d", ( (int16_t) (acc_smplrt[0] << 8) | acc_smplrt[1]));


  //Enable interrupt

  while (1)
  {

	  if(imu_sample_count== WAVELOGBUFNO)
		 {
			SD_File_Close(&File); //NB Remember to close file
			waveLogNo++;
			imu_sample_count = 0;
			SD_Wave_Open(&File, &Dir, &fno, waveDirNo, waveLogNo);
			//printmsg("New log! \r\n");
		 }

	  	ICM20649_Is_Data_Ready(&hi2c1, &data_status);

		if(data_status)
		{
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

			printmsg("Data ready, imu sample count %d\r\n", imu_sample_count);

			ICM20649_Get_IMU_RawData(&hi2c1, imu);

			HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);

			HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN); //unlocks time stamp

			accelTemp[0] = ( (int16_t) (imu[0] << 8) | imu[1]);
			accelTemp[1] = ( (int16_t) (imu[2] << 8) | imu[3]);
			accelTemp[2] = ( (int16_t) (imu[4] << 8) | imu[5]);
			gyroTemp[0] = ( (int16_t) (imu[6] << 8) | imu[7]);
			gyroTemp[1] = ( (int16_t) (imu[8] << 8) | imu[9]);
			gyroTemp[2] = ( (int16_t) (imu[10] << 8) | imu[11]);

		   //printmsg("Ax      Ay      Az      Gx      Gy      Gz \r\n");
		   //printmsg("%d  %d  %d  %d  %d  %d \r\n", accelTemp[0], accelTemp[1], accelTemp[2], gyroTemp[0], gyroTemp[1],gyroTemp[2]);

			sprintf(tempFIFOBuf, "%d:%d:%d, %ld, %ld, %ld, %ld, %ld, %ld \r\n", gTime.Hours, gTime.Minutes, gTime.Seconds,  accelTemp[0], accelTemp[1], accelTemp[2], gyroTemp[0], gyroTemp[1], gyroTemp[2]);
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

	  //Disable Interrupt
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/* USER CODE BEGIN 4 */
void printmsg(char *format,...) {
    char str[80];

    /*Extract the the argument list using VA apis */
    va_list args;
    va_start(args, format);
    vsprintf(str, format,args);
    HAL_UART_Transmit(&hlpuart1,(uint8_t *)str, strlen(str),HAL_MAX_DELAY);
    va_end(args);
}
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
