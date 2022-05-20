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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdarg.h>
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "HAL_ICM20649.h"
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

UART_HandleTypeDef hlpuart1;

/* USER CODE BEGIN PV */
HAL_StatusTypeDef i2cErrorCode;
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
	  uint8_t buf[12];
	  int16_t val;
	  imu_status_t flag;
	  float acc;
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


//======================== 1. Testing Initialisation ==============================================================



  if((ICM20649_Init_IMU(GYRO_CONFIG_FSSEL_500DPS, ACC_CONFIG_AFSSEL_4G, ACCEL_DPLFCFG_1, GYRO_DPLFCFG_0) != IMU_OK))
  {
	  printmsg("Error in i2c init \r\n");
  }
  else
  {
	  printmsg("Init successful! \r\n");
  }


	uint8_t whoami = 0;
	if(ICM20649_Get_ID(&hi2c1,&whoami) != IMU_OK)
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
		printmsg("WHO_AM_I, %d \r\n", whoami);
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

/*
  if(ICM20649_Deinit_IMU()!= IMU_OK)
  {
	  printmsg("Error in i2c init \r\n");
  }
  else
  {
	  printmsg("Init successful! \r\n");
  }

*/

  HAL_Delay(1000);
  //get raw data

//======================== 2. Testing Non-Blocking Communication and raw data acquisition ==============================================================

  uint8_t imu[12] = {0};
  ICM20649_Get_IMU_RawData(&hi2c1, imu);

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

 HAL_Delay(5000);


 //======================== 3. Testing FIFO Interface ==============================================================

 uint8_t user_ctrl = 0;
 uint8_t fifo_rst = 0;
 uint8_t fifo_en_1 = 0;
 uint8_t fifo_en_2 = 0;


 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, USER_CTRL, 1, &user_ctrl, 1, 100) != HAL_OK)
  {
       return IMU_I2C_ERROR;
       printmsg("i2c read error");
  }
 else
 {
	  printmsg("User control:  %d \r\n", user_ctrl);
 }

 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, FIFO_RST, 1, &fifo_rst, 1, 100) != HAL_OK)
  {
       return IMU_I2C_ERROR;
       printmsg("i2c read error");
  }
 else
 {
	  printmsg("FIFO Reset:  %d \r\n", fifo_rst);
 }

 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, FIFO_EN_1, 1, &fifo_en_1, 1, 100) != HAL_OK)
  {
       return IMU_I2C_ERROR;
       printmsg("i2c read error");
  }
 else
 {
	  printmsg("FIFO_EN_1:  %d \r\n", fifo_en_1);
 }

 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, FIFO_EN_2, 1, &fifo_en_2, 1, 100) != HAL_OK)
  {
       return IMU_I2C_ERROR;
       printmsg("i2c read error");
  }
 else
 {
	  printmsg("FIFO_EN_2: %d \r\n", fifo_en_2);
 }


 uint16_t count = 0;
 ICM20649_Get_FIFO_Count(&hi2c1, &count);

 printmsg("FIFO count size: %f \r\n", (float)count);



 //Read data from fifo buffer

 printmsg("Getting data from FIFO buffer ... \r\n");

 uint8_t imu_fifo[6] = {0};

 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, FIFO_R_W, I2C_MEMADD_SIZE_8BIT, imu_fifo, 14,100)!= HAL_OK)
{
	return IMU_I2C_ERROR;
}
else
{

 //int16_t rawTemp = (int16_t)imu_fifo[0]<<8 | (int16_t)imu_fifo[1];
 int16_t rawAccY = (int16_t)imu_fifo[0]<<8 | (int16_t)imu_fifo[1];
 int16_t rawAccZ = (int16_t)imu_fifo[2]<<8 | (int16_t)imu_fifo[3];
 int16_t rawAccX = (int16_t)imu_fifo[4]<<8 | (int16_t)imu_fifo[5];
 //int16_t rawRoll = (int16_t)imu_fifo[8]<<8 | (int16_t)imu_fifo[9];
 //int16_t rawPitch = (int16_t)imu_fifo[10]<<8 | (int16_t)imu_fifo[11];
 //int16_t rawYaw = (int16_t)imu_fifo[12]<<8 | (int16_t)imu_fifo[13];



 printmsg("rawAccX: %f \r\n", (float)rawAccX/8192*9.81);
 printmsg("rawAccY: %f \r\n", (float)rawAccY/8192*9.81);
 printmsg("rawAccZ: %f \r\n", (float)rawAccZ/8192*9.81);
 //printmsg("rawRoll: %f \r\n", (float)rawRoll/65.5);
 //printmsg("rawPitch: %f \r\n", (float)rawPitch/65.5);
 //printmsg("rawYaw: %f \r\n", (float)rawYaw/65.5);
 //printmsg("temp %f \r\n", ((float)rawTemp/333.81+21));

}


 //======================== 4. Testing DMA Transfer via i2c ==============================================================

 Reset_FIFO(&hi2c1);
 HAL_Delay(10000);
 printmsg("Starting DMA test...");


 uint16_t countTest = 0;
 ICM20649_Get_FIFO_Count(&hi2c1, &countTest);

 printmsg("FIFO count size: %f \r\n", (float)countTest);

 ICM20649_Get_IMU_RawData_DMA(&hi2c1, IMU_Buffer, 6);


// for(int i = 0; i<(countTest-6); i+=6)
 //{
	  	rawAccX= (int16_t)IMU_Buffer[0]<<8 | (int16_t)IMU_Buffer[1];
	    rawAccY = (int16_t)IMU_Buffer[2]<<8 | (int16_t)IMU_Buffer[3];
	    rawAccZ = (int16_t)IMU_Buffer[4]<<8 | (int16_t)IMU_Buffer[5];
	    //rawRoll = (int16_t)IMU_Buffer[6]<<8 | (int16_t)IMU_Buffer[7];
	    //rawPitch = (int16_t)IMU_Buffer[8]<<8 | (int16_t)IMU_Buffer[9];
	    //rawYaw = (int16_t)IMU_Buffer[10]<<8 | (int16_t)IMU_Buffer[11];

	   printmsg("rawAccX: %f \r\n", (float)rawAccX/8192*9.81);
	   printmsg("rawAccY: %f \r\n", (float)rawAccY/8192*9.81);
	   printmsg("rawAccZ: %f \r\n", (float)rawAccZ/8192*9.81);
	   //printmsg("rawRoll: %f \r\n", (float)rawRoll/65.5);
	   //printmsg("rawPitch: %f \r\n", (float)rawPitch/65.5);
	   //printmsg("rawYaw: %f \r\n", (float)rawYaw/65.5);

// }
 //======================== 5. Testing Interrupts ==============================================================

printmsg("Interrupt test started!");

 uint8_t int_pin_config = 0;
 uint8_t int_enable = 0;
 uint8_t int_enable_1 = 0;
 uint8_t int_enable_2 = 0;
 uint8_t int_enable_3 = 0;
 uint8_t int_status = 0;
 uint8_t int_status_1 = 0;
 uint8_t int_status_2 = 0;
 uint8_t int_status_3 = 0;


 //Print out int_config register

 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, INT_PIN_CFG, 1, &int_pin_config, 1, 100) != HAL_OK)
  {
	 printmsg("i2c read error");
       return IMU_I2C_ERROR;
  }
 else
 {
	  printmsg("INT_PIN_CONFIG: %d \r\n", int_pin_config);
 }


 //Print out interrupt enable registers

 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, INT_ENABLE, 1, &int_enable, 1, 100) != HAL_OK)
  {
       return IMU_I2C_ERROR;
       printmsg("i2c read error");
  }
 else
 {
	  printmsg("INT_ENABLE: %d \r\n", int_enable);
 }

 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, INT_ENABLE_1, 1, &int_enable_1, 1, 100) != HAL_OK)
  {
       return IMU_I2C_ERROR;
       printmsg("i2c read error");
  }
 else
 {
	  printmsg("INT_ENABLE_1: %d \r\n", int_enable_1);
 }
 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, INT_ENABLE_2, 1, &int_enable_2, 1, 100) != HAL_OK)
  {
	 printmsg("i2c read error");
	 return IMU_I2C_ERROR;

  }
 else
 {
	  printmsg("INT_ENABLE_2: %d \r\n", int_enable_2);
 }
 if(HAL_I2C_Mem_Read(&hi2c1,IMU_Device_Address, INT_ENABLE_3, 1, &int_enable_3, 1, 100) != HAL_OK)
  {
	 printmsg("i2c read error");
       return IMU_I2C_ERROR;
  }
 else
 {
	  printmsg("INT_ENABLE_3: %d \r\n", int_enable_3);
 }

 if(ICM20649_Get_Interrupt_Status(&hi2c1, INT_STATUS, &int_status) != IMU_OK)
{
	return IMU_I2C_ERROR;
}
else
{
	printmsg("INT_STATUS %d \r\n", int_status);
}

 if(ICM20649_Get_Interrupt_Status(&hi2c1, INT_STATUS_1, &int_status_1) != IMU_OK)
{
	return IMU_I2C_ERROR;
}
else
{
	printmsg("INT_STATUS_1 %d \r\n", int_status_1);
}

 if(ICM20649_Get_Interrupt_Status(&hi2c1, INT_STATUS_2, &int_status_2) != IMU_OK)
{
	return IMU_I2C_ERROR;
}
else
{
	printmsg("INT_STATUS_2 %d \r\n", int_status_2);
}

 if(ICM20649_Get_Interrupt_Status(&hi2c1, INT_STATUS_3, &int_status_3) != IMU_OK)
{
	return IMU_I2C_ERROR;
}
else
{
	printmsg("INT_STATUS_3 %d \r\n", int_status_3);
}






  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   while (1)
  {
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
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
	printmsg("I2C Initialisation error");
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
