/**
  ******************************************************************************
  * @file			: UART.hpp
  * @brief			: Application specific UART Port Controller with Dynamic Data Queues.
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

/**
 * Warning:
 * This controller makes use of standard library containers for dynamic memory allocation.
 * The standard library containers are however not thread safe, which includes issues with interrupt service routines.
 * It is absolutely necessary to test code where dynamically allocated containers are involved in interrupt events.
 */

#pragma once

#include "stm32l4xx_hal.h"

#include <queue>
#include <vector>
#include <string>

class UART{
private:
	UART_HandleTypeDef * hUart;	// STM32 HAL UART Handle
	const IRQn_Type uartIrq;	// IRQ related to hUart
	const IRQn_Type dmaTxIrq;	// IRQ related to Rx DMA Process
	const IRQn_Type dmaRxIrq;	// IRQ related to Tx DMA Process

	std::queue<std::vector<uint8_t>> txQueue{};	// Processed Data to be Sent
	
	struct Rx{	// Data Structure for asynchronously receiving UART data.
		template<size_t S, typename tB = uint8_t, typename tS = uint16_t>
		struct Buffer{
			const tS size{S};		// Size of buffer.
			tB buff[S];				// Static Storage
			volatile tS tail{0};	// Data Written to Buffer. Will be advanced in an ISR.

			Buffer() = default;
			static_assert(S > 0, "Buffer size must be non-zero.");
			static_assert(sizeof(tB) == 1, "Only byte-sized types allowed for buffer elements.");
		};

		static const size_t buffSize = 254u;
		Buffer<buffSize> dmaBuff{};			// Main Circular Buffer given to HAL DMA Process
		Buffer<8*buffSize> offloadBuff{};	// Large static offloading buffer. Rx Event Callbacks will move data from rxBuff to here.
		
	} rx;
	
public:
	std::queue<std::vector<uint8_t>> rxQueue{};	// Unprocessed Received Data. Only push to during synchronous event loop.
	
	UART(UART_HandleTypeDef * h, IRQn_Type uartIrq, IRQn_Type dmaTxIrq, IRQn_Type dmaRxIrq);

	void transmit(const std::vector<uint8_t> & msg);
	void beginReceive();	// Begins data reception. Does not initialise the STM32 UART peripheral device.
	void endReceive();		// Ends data reception. Does not de-initialise the STM32 UART peripheral device.

	void setBaudrate(uint32_t baud) const;

	void updateRxQueue();	// Synchronously move data from rx.offloadBuff rxQueue. Call periodically in main event loop.

private:
	friend int main();	// Temporary for testing.
	
	void next();	// Initiates a new transmission, if one is not already active.

	inline void interruptsOff() const;	// Disables all UART related interrupts.
	inline void interruptsOn() const;	// Enables all UART related interrupts.

	bool txBusy() const;	// Checks for a current UART Transmission Process.

	void txCmpltCallback();	// Must be called upon UART transmission complete.
	void rxEventCallback(uint16_t size);	// Must be called upon UART idle, half and full complete data reception.
	
	friend class M9N;	// Temporary for testing.
	friend void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
	friend void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
};

/*** END OF FILE ***/