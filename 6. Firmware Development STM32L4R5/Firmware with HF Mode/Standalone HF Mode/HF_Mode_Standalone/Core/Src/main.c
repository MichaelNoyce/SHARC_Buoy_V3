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
#include "HAL_ICM20689.h"
#include "math.h"
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


I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_tx;
DMA_HandleTypeDef hdma_i2c1_rx;

UART_HandleTypeDef hlpuart1;

SD_HandleTypeDef hsd1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_CRC_Init(void);
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
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_LPUART1_UART_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  imu_status_t flag;
  float Ax, Ay, Az, Gx, Gy, Gz, T;

  if((ICM20689_Init_IMU(GYRO_CONFIG_FSSEL_500DPS, ACC_CONFIG_AFSSEL_4G, ACCEL_DPLFCFG_1, GYRO_DPLFCFG_0) != IMU_OK))
  {
	  printmsg("Error in i2c init \r\n");
  }
  else
  {
	  printmsg("Init successful! \r\n");
  }

  flag = ICM20689_reset(&hi2c1);
  if(flag!=IMU_OK)
    {
  	  printmsg("Error in i2c init \r\n");
  	  printmsg("Reset error, %d \r\n", flag);
    }
    else
    {
  	  printmsg("Reset successful! \r\n");
    }


	uint8_t whoami = 0;
	if(ICM20689_Get_ID(&hi2c1,&whoami) != IMU_OK)
	{
		return IMU_I2C_DEVICE_OFFLINE;
		printmsg("offline error \r\n");

	}
	else if(whoami != WHO_AM_I_VALUE)
	{
		return IMU_I2C_ID_ERROR;
		printmsg("i2c id error \r\n");
	}
	else
	{
		printmsg("WHO_AM_I, %d", whoami);
	}

flag =  ICM20689_Set_Wake(&hi2c1);
if(flag!=IMU_OK)
{
	  printmsg("Error in wake \r\n");
	  printmsg("Wake error, %d \r\n", flag);
}
else
{
	  printmsg("Wake successful! \r\n");
}


  //read out all power and control registers
  //user control register

  uint8_t usr_ctrl_reg = 0;
  uint8_t pwr_mgmt1_reg = 0;
  uint8_t pwr_mgmt2_reg = 0;


  if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address,USER_CTRL,1,&usr_ctrl_reg,1,100) != HAL_OK)
  {
  	  return IMU_I2C_ERROR;
  	printmsg("i2c read error");

  }
  else
  {
	  printmsg("USR_CTRL %d \r\n", usr_ctrl_reg);
  }


  if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, PWR_MGMT_1, 1,&pwr_mgmt1_reg,1,100) != HAL_OK)
  {
	  return IMU_I2C_ERROR;
	  printmsg("i2c read error");
  }
  else
  {
	  printmsg("PWR_MGMT_1 %d \r\n", pwr_mgmt1_reg);
  }

  if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, PWR_MGMT_2, 1, &pwr_mgmt1_reg, 1, 100) != HAL_OK)
   {
        return IMU_I2C_ERROR;
        printmsg("i2c read error");
   }
  else
  {
	  printmsg("PWR_MGMT_2 %d \r\n", pwr_mgmt1_reg);
  }


  printmsg("Interface started \r\n");

  if(HAL_I2C_IsDeviceReady(&hi2c1,IMU_Device_Address,10,100)== HAL_OK)
  {
   printmsg("i2c interface working! \r\n");
  }
  else
  {
	  printmsg("i2c not working");
  }

  HAL_Delay(500);

  uint8_t imu[12] = {0};
  ICM20689_Get_IMU_RawData(&hi2c1, imu);

  printmsg("Accel x high %i low %i \r\n", imu[0], imu[1]);

  int16_t rawAccX = (int16_t)imu[0]<<8 | (int16_t)imu[1];
  int16_t rawAccY = (int16_t)imu[2]<<8 | (int16_t)imu[3];
  int16_t rawAccZ = (int16_t)imu[4]<<8 | (int16_t)imu[5];
  int16_t rawRoll = (int16_t)imu[6]<<8 | (int16_t)imu[7];
  int16_t rawPitch = (int16_t)imu[8]<<8 | (int16_t)imu[9];
  int16_t rawYaw = (int16_t)imu[10]<<8 | (int16_t)imu[11];

  printmsg("rawAccX: %f \r\n", (float)rawAccX/8192*9.81);
  printmsg("rawAccY: %f \r\n", (float)rawAccY/8192*9.81);
  printmsg("rawAccZ: %f \r\n", (float)rawAccZ/8192*9.81);
  printmsg("rawRoll: %f \r\n", (float)rawRoll/65.5);
  printmsg("rawPitch: %f \r\n", (float)rawPitch/65.5);
  printmsg("rawYaw: %f \r\n", (float)rawYaw/65.5);

  uint8_t temp[2] = {0};
  if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, TEMP_OUT_H,I2C_MEMADD_SIZE_8BIT, temp,2,100)!= HAL_OK)
 {
 	return IMU_I2C_ERROR;
 }
 else
 {

	int16_t temperature =  (int16_t)temp[0]<<8 | (int16_t)temp[1];
 	printmsg("temp %f \r\n", ((float)temperature/333.81+21));
 }



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  FIL File; /* File object */
  uint8_t dataBuffer[100] = "Starting Logger Test #1 \r\n";
  uint32_t logStartTime;
  uint8_t logNumber = 1;
  SD_File_Open(&File, 1);
  SD_File_Write(&File, dataBuffer);
  logStartTime = HAL_GetTick();
  sprintf(dataBuffer, "Log start time: %.2f \r\n", (float)logStartTime/1000);
  SD_File_Write(&File, dataBuffer);
  sprintf(dataBuffer, "Ax	Ay	Az	Gx	Gy	Gz T\r\n");

  while (1)
  {

	  if(((HAL_GetTick()-logStartTime)>=600000))
	  {
		   logStartTime = HAL_GetTick();
		   SD_File_Close(&File);
		   logNumber++;
		   SD_File_Open(&File, logNumber);
		   sprintf(dataBuffer, "Log start time: %.2f \r\n", (float)logStartTime/1000);
		   SD_File_Write(&File, dataBuffer);
		   sprintf(dataBuffer, "Ax	Ay	Az	Gx	Gy	Gz T\r\n");
		   SD_File_Write(&File, dataBuffer);
	  }

	  ICM20689_Get_IMU_RawData(&hi2c1, imu);
	  HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, TEMP_OUT_H,I2C_MEMADD_SIZE_8BIT, temp,2,100);

	  int16_t rawAccX = (int16_t)imu[0]<<8 | (int16_t)imu[1];
	  int16_t rawAccY = (int16_t)imu[2]<<8 | (int16_t)imu[3];
	  int16_t rawAccZ = (int16_t)imu[4]<<8 | (int16_t)imu[5];
	  int16_t rawRoll = (int16_t)imu[6]<<8 | (int16_t)imu[7];
	  int16_t rawPitch = (int16_t)imu[8]<<8 | (int16_t)imu[9];
	  int16_t rawYaw = (int16_t)imu[10]<<8 | (int16_t)imu[11];
	  int16_t temperature =  (int16_t)temp[0]<<8 | (int16_t)temp[1];

	  Ax = (float)rawAccX/8192*9.81;
	  Ay = (float)rawAccY/8192*9.81;
	  Az = (float)rawAccZ/8192*9.81;
	  Gx = (float)rawRoll/65.5;
	  Gy = (float)rawPitch/65.5;
	  Gz = (float)rawYaw/65.5;
	  T = (float)temperature/333.81+21;

	  sprintf(dataBuffer, "%.3f  %.3f  %.3f  %.3f  %.3f  %.3f  %.3f \r\n", Ax, Ay, Az, Gx, Gy, Gz, T);

	  SD_File_Write(&File, dataBuffer);


	 HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000E14;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  hsd1.Init.ClockDiv = 8;
  hsd1.Init.Transceiver = SDMMC_TRANSCEIVER_DISABLE;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);

}

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : SD_Detect_Pin_Pin */
  GPIO_InitStruct.Pin = SD_Detect_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SD_Detect_Pin_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : INT_IMU_Pin */
  GPIO_InitStruct.Pin = INT_IMU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INT_IMU_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
