/**
  ******************************************************************************
  * @file           : M9N_STM32.hpp
  * @brief          : Source / Header file for M9N_STM32.c/.h
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

#pragma once

#include "M9N_Base.hpp"
#include "UART.hpp"
#include "stm32l4xx_hal.h"

#include <string>
#include <queue>

using string = std::string;

class M9N : public M9N_Base{
public:
	M9N(UART_HandleTypeDef * h, IRQn_Type uartIrq, IRQn_Type dmaTxIrq, IRQn_Type dmaRxIrq);

private:
	UART uart;

	std::queue<string> nmeaMailbox{};	// Separated NMEA Message Sentences.
	std::queue<std::vector<uint8_t>> ubxMailbox{};	// Seperated UBX Frames.
	void updateMailbox();	// Updates nmeaMailbox and ubxMailbox with new data from uart.
	
	std::queue<std::unique_ptr<UBX>> ubxReceived{};	// Queue of pointers to dynamically allocated received UBX Frame Objects.
	std::queue<std::unique_ptr<NMEA_Standard>> nmeaReceived{};	// Queue of pointers to dynamically allocated received NMEA Sentence Objects.
	void processMailbox();	// Processes the mailboxes into received message objects.
	
	friend int main();		// Temporary for testing.

	virtual void transmit(const std::vector<uint8_t> & msg) final;
	virtual void delay(uint32_t delay) final;
	virtual void setBaudrate(Baud baud = Baud::B38400, PortID portId = PortID::UART1) final;

	friend void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
	friend void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
};

/*** END OF FILE ***/
