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
/* --------------------------------------------------------------------------- */
/* Begin Public Includes */
#include "M9N_Base.hpp"
#include "stm32l4xx_hal.h"

#include <string>
#include <queue>
#include <array>
#include <utility>

using string = std::string;
/* End Public Includes */

/* --------------------------------------------------------------------------- */
/* Begin Public Defines */


/* End Public Defines */

/* --------------------------------------------------------------------------- */
/* Begin Public Typedefs */


/* End Public Typedefs */

/* --------------------------------------------------------------------------- */
/* Begin Global Public Variables */


/* End Global Public Variables */

/* --------------------------------------------------------------------------- */
/* Begin Public Function Prototypes */


/* End Public Function Prototypes */

/* --------------------------------------------------------------------------- */
/* Begin Public Class Definitions */
class M9N : public M9N_Base{
public:
	M9N(UART_HandleTypeDef * h, IRQn_Type irq);

private:
	class UART{
	private:
		UART_HandleTypeDef * hUart;	// STM32 HAL UART Handle
		const IRQn_Type uartIRQ;	// IRQ related to hUart

		std::queue<std::vector<uint8_t>> txQueue{};	// Processed Data to be Sent
		std::queue<std::vector<uint8_t>> rxQueue{};	// Unprocessed Received Data
		
		struct RxRing{
			static const uint16_t cBuffLen = 254u;	// 254 allows for 8-bit index variables.
			static_assert(cBuffLen % 2 == 0, "Error: Rx buffer length must be an even number.");
			static const uint16_t cBuffLenHalf = cBuffLen / 2;
			uint8_t cBuff[cBuffLen];	// C-style Array Circular Receiving Buffer

			uint8_t head{};	// Head. Advanced upon each reception callback.
			uint8_t tail{};	// Tail. Remembers last position of head before it is advanced.

		} rxRing;

		std::queue<string> nmeaMailbox{};	// Seperated NMEA Message Sentences.
		std::queue<std::vector<uint8_t>> ubxMailbox{};	// Seperated UBX Frames.
		void updateMailbox();	// Updates nmeaMailbox and ubxMailbox with new received data.
		
		std::queue<std::unique_ptr<UBX>> ubxReceived{};	// Queue of received UBX Frame Objects.
		std::queue<std::unique_ptr<NMEA_Standard>> nmeaReceived{};	// Queue of received NMEA Sentance Objects.
		void processMailbox();	// Processes the mailboxes into received message objects.

		friend int main();	// Temporary for testing.

	public:
		UART(UART_HandleTypeDef * h, IRQn_Type irq);

		void transmit(const string & msg);
		void transmit(const std::vector<uint8_t> & msg);
		void beginReceive();
		void endReceive();

		void txCmpltCallback();
		void rxHalfCmpltCallback();
		void rxCmpltCallback();
		void rxIdleCallback(uint16_t size);

	private:
		void next();

		bool txBusy();

		friend class M9N;
		friend void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
		friend void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
		friend void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
		friend void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
	} uart;
	friend int main();	// Temporary for testing.

	virtual void write(const string & msg) final;
	virtual void transmit(const string & msg) final;
	virtual void delay(uint32_t delay) final;

	virtual void setBaudrate(Baud baud = Baud::B38400, PortID portId = PortID::UART1) final;
	
	friend void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
	friend void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
	friend void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
	friend void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

};



/* End Public Class Definitions */

/*** END OF FILE ***/
