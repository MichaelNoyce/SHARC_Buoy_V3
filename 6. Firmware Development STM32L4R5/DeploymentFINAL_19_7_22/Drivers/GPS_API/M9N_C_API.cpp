/**
  ******************************************************************************
  * @file           : M9N_C_API.c
  * @brief          : Source / Header file for M9N_C_API.c/.h
  * @author			: Lawrence Stanton
  ******************************************************************************
  * @attention
  *
  * © LD Stanton 2022
  *
  * This file and its content are the copyright property of the author. All
  * rights are reserved. No warranty is given. No liability is assumed.
  * Confidential unless licensed otherwise. If licensed, refer to the
  * accompanying file "LICENCE" for license details.
  *
  ******************************************************************************
  */

// #include "main.h"
#include "main.h"
#include "M9N_C_API.h"

#include <time.h>

static void MX_UART4_Init(void);
static void MX_DMA4_Init(void);

UART_HandleTypeDef huart4;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart4_tx;

M9N m9n{ &huart4, UART4_IRQn, DMA2_Channel3_IRQn, DMA2_Channel5_IRQn };
uint32_t midnight = 0;

GPS_Init_msg_t GPS_Init(){
	MX_DMA4_Init();
	MX_UART4_Init();
	m9n.init();
	return GPS_Init_OK;
}

void GPS_Update(){
	m9n.scanMessages();
}

uint8_t GPS_Data_Ready(){
	return (m9n.dataReady() ? 1u : 0u);
}

void GPS_InterruptsOff(){
	m9n.interruptsOff();
}

void GPS_InterruptsOn(){
	m9n.interruptsOn();
}

void receiveGLL(const NMEA_Standard::GLL& gll){
	gpsDataLive.coordinates.tic = HAL_GetTick();
	gpsDataLive.coordinates.lat = gll.lat;
	gpsDataLive.coordinates.longi = gll.lon;
	gpsDataLive.coordinates.time = midnight + gll.time;
}

void receiveGSA(const NMEA_Standard::GSA& gsa){
	static const uint32_t ticTimeDelayThreshold = 5000u;

	gpsDataLive.diag.HDOP.digit = static_cast<int>(gsa.hdop);
	gpsDataLive.diag.HDOP.precision = static_cast<int>((gsa.hdop - gpsDataLive.diag.HDOP.digit) * 100);
	gpsDataLive.diag.VDOP.digit = static_cast<int>(gsa.vdop);
	gpsDataLive.diag.VDOP.precision = static_cast<int>((gsa.vdop - gpsDataLive.diag.VDOP.digit) * 100);
	gpsDataLive.diag.PDOP.digit = static_cast<int>(gsa.pdop);
	gpsDataLive.diag.PDOP.precision = static_cast<int>((gsa.pdop - gpsDataLive.diag.PDOP.digit) * 100);

	gpsDataLive.diag.num_sats = std::count_if(gsa.svid.begin(), gsa.svid.end(), [](uint8_t n) -> bool{ return n != 0; });	// TODO: GSA Receives Satellite IDs, not the number of sattelites

	gpsDataLive.diag.fix_type = gsa.navMode;

	auto delaySinceLocation = (int32_t)HAL_GetTick() - gpsDataLive.coordinates.tic;

	if (delaySinceLocation < 0) 							gpsDataLive.diag.time = 0;
	else if (delaySinceLocation < ticTimeDelayThreshold) gpsDataLive.diag.time = gpsDataLive.coordinates.time;
	else 												gpsDataLive.diag.time = gpsDataLive.coordinates.time + delaySinceLocation;
}

void receiveZDA(const NMEA_Standard::ZDA& zda){
	midnight = zda.time.midnight();
}

/**
  * Enable DMA controller clock
  */
static void MX_DMA4_Init(void){

  /* DMA controller clock enable */
	__HAL_RCC_DMAMUX1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Channel1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Channel3_IRQn, 6, 0);
	HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
	/* DMA1_Channel2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Channel5_IRQn, 7, 0);
	HAL_NVIC_EnableIRQ(DMA2_Channel5_IRQn);

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void){

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 38400;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart4) != HAL_OK){
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK){
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_2) != HAL_OK){
		Error_Handler();
	}
	if (HAL_UARTEx_EnableFifoMode(&huart4) != HAL_OK){
		Error_Handler();
	}
	/* USER CODE BEGIN UART4_Init 2 */

	/* USER CODE END UART4_Init 2 */

}


/*** END OF FILE ***/
