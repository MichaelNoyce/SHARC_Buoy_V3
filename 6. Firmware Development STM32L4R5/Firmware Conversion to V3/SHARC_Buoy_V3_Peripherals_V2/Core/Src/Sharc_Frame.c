/*
 * Sharc_Frame.c
 *
 *  Created on: Jun 7, 2020
 *      Author: jamie
 */

#include "Sharc_Frame.h"



static uint8_t driftbuffer[DRIFTBUFFER_SIZE] = {0};
static uint8_t wavebuffer[WAVEBUFFER_SIZE] = {0};


HAL_StatusTypeDef Init_Debug(void)
{
	// set up clock output on GPIO Pin A8 for testing
#ifdef DEBUG_HSE_OUTPUT_ENABLE
	//configure pin
	/*Configure GPIO pin : PA8 */
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	 GPIO_InitStruct.Pin = GPIO_PIN_8;
	 GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
	 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	 //map clock output to PIN PA8
	 HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
#endif
	//initialise USART 2 for USB comms
#ifdef DEBUG_USART_ENABLE
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
	    return HAL_ERROR;
	  }
	  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	  {
		  return HAL_ERROR;
	  }
	  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	  {
		  return HAL_ERROR;
	  }
	  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
	  {
		  return HAL_ERROR;
	  }
#endif

#ifdef DEBUG_LED2_ENABLE

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();
	  HAL_PWREx_EnableVddIO2();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : PB14 */
	  GPIO_InitStruct.Pin = LD2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif

#ifdef DEBUG_LED3_ENABLE
	  /*Configure GPIO pin Output Level */
	    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

	    GPIO_InitStruct.Pin = LD3_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif

#ifdef DEBUG_LP_ENABLE
	  HAL_DBGMCU_EnableDBGStandbyMode();	//enable for shutdown mode
	  HAL_DBGMCU_EnableDBGStopMode();

#endif

	  return HAL_OK;
}

//Debug Print
void printmsg(char *format,...) {
    char str[80];

    /*Extract the the argument list using VA apis */
    va_list args;
    va_start(args, format);
    vsprintf(str, format,args);
    HAL_UART_Transmit(&hlpuart1,(uint8_t *)str, strlen(str),HAL_MAX_DELAY);
    va_end(args);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
HAL_StatusTypeDef SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
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
	  return HAL_ERROR;
  }

  return HAL_OK;
}



HAL_StatusTypeDef Go_To_Sleep(PWR_MODE_t mode, uint32_t seconds)
{
	//reset wake up pin interrupt
	__HAL_RCC_PWR_CLK_ENABLE();
	/* Enable Wake Up timer in interrupt mode */
	HAL_PWREx_EnableGPIOPullDown(PWR_GPIO_C, GPIO_PIN_7);

	HAL_PWREx_EnablePullUpPullDownConfig();
	//set alarm
	if(seconds > 0)
	{
	 if(HAL_RTCEx_SetWakeUpTimer_IT(&hrtc,(seconds-1),RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
	  {
		 return HAL_ERROR;
	  }
	}
	 HAL_PWREx_EnableInternalWakeUpLine();
	 //if shutdown mode enabled
	 if(mode == SHUTDOWN)
	 {
		 HAL_PWREx_EnterSHUTDOWNMode();
	 }
	 else if(mode == STDBY)
	 {
		 HAL_PWR_EnterSTANDBYMode();
	 }
	 return HAL_OK;
}

HAL_StatusTypeDef USART_Enter_Standby_for_data(UART_HandleTypeDef *huart)
{
	//step 1, wait for ongoing uart transmissions to finish
	printf("Heading to Sleep\r\n");

	//disable systick timer

	HAL_RCCEx_WakeUpStopCLKConfig(RCC_STOP_WAKEUPCLOCK_HSI);
	HAL_UARTEx_EnableClockStopMode(huart);
	while(__HAL_UART_GET_FLAG(&hlpuart1,UART_FLAG_BUSY) == SET);
	//clear all interrupts
	while(__HAL_UART_GET_FLAG(huart, USART_ISR_REACK) == RESET);
	UART_WakeUpTypeDef hwake;
	//configure wake up to wake up on start bit
	hwake.WakeUpEvent = UART_WAKEUP_ON_STARTBIT;

	if(HAL_UARTEx_StopModeWakeUpSourceConfig(huart,hwake)!= HAL_OK)
	{
		//error setting sleep state
		return HAL_ERROR;
	}
	//set device to generate interrupt on wake up
	__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(huart,UART_IT_WUF);
	//configure wake up clock source to MSI and enable
	//enable stop mode
	HAL_UARTEx_EnableClockStopMode(huart);
	HAL_UARTEx_EnableStopMode(huart);
	HAL_PWREx_EnterSTOP1Mode(PWR_STOPENTRY_WFI);
	return HAL_OK;
}

void GPIO_Set_Pin_LP(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	  /*Configure GPIO pins : PC13 PC0 PC1 PC2
	                           PC3 PC4 PC5 PC6
	                           PC7 PC8 PC9 PC10
	                           PC11 PC12 */
	  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
	                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
	                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
	                          |GPIO_PIN_11|GPIO_PIN_12;
	  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA0 PA1 PA4 PA6
	                           PA7 PA9 PA10 PA11
	                           PA12 PA15 */
	  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_6
	                          |GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
	                          |GPIO_PIN_12|GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : LD2_Pin */
	  GPIO_InitStruct.Pin = LD2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : PB0 PB1 PB2 PB10
	                           PB11 PB12 PB13 PB14
	                           PB15 PB3 PB4 PB5
	                           PB6 PB7 PB8 PB9 */
	  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
	                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
	                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
	                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

uint8_t* to_binary_format_GPS(GPS_Data_t gps_data ,uint8_t ID)
{
	//define union to convert 32 bit float to unsigned uint8_t array
	union
	{
		float a;					//for 32 bit floats
		unsigned char bytes[4];		//for 4 byte long unsigned integer arrays
		uint32_t num;				//for long numbers
	} byte_converter;
	//define union to convert uint16_t/int16_t into unsigned 8-bit byte arrays
	union
	{
		int16_t  s_halfword;
		unsigned char bytes[2];
	}halfword_converter;

	/*0. Byte 0: Packet ID*/
	*driftbuffer = ID;
	/*1. Bytes 1 - 4:  Epoch Time*/
	byte_converter.num = gps_data.Etime;
	memcpy(&driftbuffer[1],(byte_converter).bytes,4);

	/* Add coordinates bytes 1 - 5 = lat, bytes 6 - 10 = long*/
	byte_converter.a = gps_data.coordinates.lat;
	memcpy(&driftbuffer[5],byte_converter.bytes,4);
	byte_converter.a = gps_data.coordinates.longi;
	memcpy(&driftbuffer[9],byte_converter.bytes,4);


	//convert HDOP,VDOP, PDOP to 2 bytes big endian
	driftbuffer[13] = gps_data.diag.HDOP.digit;
	driftbuffer[14] = gps_data.diag.HDOP.precision;
	driftbuffer[15] = gps_data.diag.VDOP.digit;
	driftbuffer[16] = gps_data.diag.VDOP.precision;
	driftbuffer[17] = gps_data.diag.PDOP.digit;
	driftbuffer[18] = gps_data.diag.PDOP.precision;
	driftbuffer[19] = (gps_data.diag.num_sats);
	driftbuffer[19] = driftbuffer[19]<<2;
	driftbuffer[19] |= gps_data.diag.fix_type;

	//breakdown temperature into 4 unsigned bytes
	byte_converter.num = (uint32_t)gps_data.env_Temp;
	memcpy(&driftbuffer[20],byte_converter.bytes,sizeof(uint32_t));

	//break down pressure into 4 unsigned bytes
	byte_converter.num = gps_data.atm_Press;
	memcpy(&driftbuffer[24],byte_converter.bytes,sizeof(uint32_t));

	//shunt voltage
	halfword_converter.s_halfword = gps_data.shunt_v;
	memcpy(&driftbuffer[29],halfword_converter.bytes,sizeof(int16_t));

	//bus voltage
	halfword_converter.s_halfword = gps_data.bus_v;
	memcpy(&driftbuffer[31],halfword_converter.bytes,sizeof(int16_t));

	//current
	halfword_converter.s_halfword = gps_data.current;
	memcpy(&driftbuffer[33],halfword_converter.bytes,sizeof(int16_t));

	//power
	halfword_converter.s_halfword = gps_data.power;
	memcpy(&driftbuffer[35],halfword_converter.bytes,sizeof(int16_t));

	driftbuffer[get_driftBuffer_Size() -1] = 0xd; //end of packet character

	//return a pointer the the array driftbuffer;
	return driftbuffer;
}

uint8_t* to_binary_format_Wave(Wave_Data_t wave_data, uint8_t ID)
{
	//define union to convert 32 bit float to unsigned uint8_t array
	union
	{
		float a;					//for 32 bit floats
		unsigned char bytes[4];		//for 4 byte long unsigned integer arrays
		uint32_t num;				//for long numbers
	} byte_converter;
	//define union to convert uint16_t/int16_t into unsigned 8-bit byte arrays
	union
	{
		int16_t  s_halfword;
		unsigned char bytes[2];
	}halfword_converter;

	/*0. Byte 0: Packet ID*/
	*wavebuffer = ID;
	/*1. Bytes 1 - 4:  Significant wave height*/
	byte_converter.a = wave_data.Hm0;
	memcpy(&wavebuffer[1],(byte_converter).bytes,4);
	/*2. Bytes 5 - 9:  Root mean square wave height*/
	byte_converter.a = wave_data.Hrms;
	memcpy(&wavebuffer[5],(byte_converter).bytes,4);
	/*3. Bytes 9 - 13:  Mean zero crossing period */
	byte_converter.a = wave_data.T0;
	memcpy(&wavebuffer[1],(byte_converter).bytes,4);
	/*4. Bytes 14 - 17: Peak wave period*/
	byte_converter.a = wave_data.TM01;
	memcpy(&wavebuffer[1],(byte_converter).bytes,4);
	/*5. Bytes 18 - 21:  0th spectral moment*/
	byte_converter.a = wave_data.Tp;
	memcpy(&wavebuffer[1],(byte_converter).bytes,4);
	/*6. Bytes 22 - 25:  1st spectral moment*/
	byte_converter.a = wave_data.M0;
	memcpy(&wavebuffer[1],(byte_converter).bytes,4);
	/*7. Bytes 26 - 29:  2nd spectral moment*/
	byte_converter.a = wave_data.M1;
	memcpy(&wavebuffer[1],(byte_converter).bytes,4);
	/*8. Bytes 30 - 150:  PSD Spectra */
	byte_converter.a = wave_data.M2;
	memcpy(&wavebuffer[1],(byte_converter).bytes,4);


	wavebuffer[WAVEBUFFER_SIZE-1] = 0xd; //end of packet character

	//return a pointer the the array buffer;
	return wavebuffer;
}

uint8_t  get_driftBuffer_Size(void)
{
	return DRIFTBUFFER_SIZE;
}
/******************************* HANDLER FUNCTIONS *******************************/

/*
 * @brief: Routine for Ring Alert Detection on IRidium Ring Pin
 */

void Routine_ASYNC_IRIDIUM_RX(void)
{
	printf("Incoming Message from Satellite: Receiving...");
	//intialise modem
	if(IR_Init_Module() == IR_OK)
	{
		//recieve message
		uint8_t message[100] = {0};
		uint16_t num_messages = 0;
		IR_recieve_String(message,100,&num_messages);
	}
	printf("Message Received!\r\n");
}

/*
 * @brief: Power On Reset Handler for BUOY (CASE: NRST Line Pulled low)
 */
void POR_Handler(void)
{
	  //clear flags
	  __HAL_RCC_CLEAR_RESET_FLAGS();
	  //clear the back up registers
	  HAL_PWR_EnableBkUpAccess();
	  __HAL_RCC_BACKUPRESET_FORCE();
	  __HAL_RCC_BACKUPRESET_RELEASE();
	  HAL_PWR_DisableBkUpAccess();
	  SystemClock_Config();

	  //deactivate and disable wake up timers
	  HAL_PWREx_DisableInternalWakeUpLine();
	  /* Clear PWR wake up Flag */
	 __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	 __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);
	  //reinitialise the clock
}
/*
 * @brief: Brown Out Reset Handler for BUOY (case Vbat < Vbrownoutthreshold)
 */
void BOR_Handler(void)
{
	  //clear flags
	  __HAL_RCC_CLEAR_RESET_FLAGS();
	  // transmit log to PC

	  char* msg= "Warning! Device encountered a Brown Out. Exiting Program...\r\n";
	  HAL_UART_Transmit(&hlpuart1,(uint8_t*)msg,strlen(msg),100);
	  //perform system reset
	  POR_Handler();
	  HAL_NVIC_SystemReset();
	  /*
	   * Failure to perform system reset causes device to enter an infinite loop
	   */
	  while(1)
	  {
		  HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
		  HAL_Delay(500);
	  }
}
