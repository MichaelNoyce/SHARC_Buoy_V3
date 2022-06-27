/**
  ******************************************************************************
  * @file			: UART.cpp
  * @brief			: Source for UART.hpp
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

#include "UART.hpp"

#include <cstring>

using vect = std::vector<uint8_t>;

UART::UART(UART_HandleTypeDef * h, IRQn_Type uartIrq, IRQn_Type dmaTxIrq, IRQn_Type dmaRxIrq) :
	hUart(h), uartIrq(uartIrq), dmaTxIrq(dmaTxIrq), dmaRxIrq(dmaRxIrq) {}

inline void UART::interruptsOff() const{
	HAL_NVIC_DisableIRQ(uartIrq);
	HAL_NVIC_DisableIRQ(dmaTxIrq);
	HAL_NVIC_DisableIRQ(dmaRxIrq);
}

inline void UART::interruptsOn() const{
	HAL_NVIC_EnableIRQ(uartIrq);
	HAL_NVIC_EnableIRQ(dmaTxIrq);
	HAL_NVIC_EnableIRQ(dmaRxIrq);
}

void UART::transmit(const std::vector<uint8_t> & msg){
	// Critical Path. Cannot be interrupted else txQueue may be corrupted.
	interruptsOff();
	txQueue.push(msg);
	next();	// Will start transmission if idle. Else message will be sent later.
	interruptsOn();
}

void UART::next(){
	/**
	 * ISR Enable/Disable not necessary due to txBusy check guarding against modifications to txQueue if transmission is active.
	 * 
	 * The .empty() check is vulnerable to the non-volatile types of rxQueue.begin() and .end(). If this method
	 * is called repeatedly without visible modification to txQueue, temporary values for these pointers could become
	 * unsynchronised with events in an ISR routine. However, so long as txQueue is pushed to or poped from, this 
	 * should allow the check to proceed as expected
	 */
	if(!txQueue.empty() && !txBusy()){	
		HAL_UART_Transmit_DMA(hUart, txQueue.front().data(), txQueue.front().size());	// Should be ready based on earlier check.
		// Do not pop. Keep on heap until txCpltCallback to maintain pointer to data().
	}
}

bool UART::txBusy() const {
	const auto halTxState = HAL_UART_GetState(hUart);

	return !( 
		( (halTxState & HAL_UART_STATE_READY) == HAL_UART_STATE_READY ) &&
		( (halTxState & HAL_UART_STATE_BUSY_TX) != HAL_UART_STATE_BUSY_TX) );
}

/**
 * @brief Initialises DMA UART Reception.
 * 
 * @note The UART and DMA Peripherals must already be initialised by the time this function is called.
 * @note The DMA peripheral must be configured in circular mode.
 */
void UART::beginReceive(){
	HAL_UARTEx_ReceiveToIdle_DMA(hUart, rx.dmaBuff.buff, rx.dmaBuff.size);		
}

void UART::endReceive(){
	HAL_UART_DMAStop(hUart);
}

void UART::updateRxQueue(){
	if(rx.offloadBuff.tail > 0){
		interruptsOff();
		rxQueue.push(vect(rx.offloadBuff.buff, rx.offloadBuff.buff + rx.offloadBuff.tail));
		rx.offloadBuff.tail = 0;
		interruptsOn();
	}
}

void UART::setBaudrate(uint32_t baud) const{
	if(HAL_UART_DeInit(hUart) == HAL_OK){
		hUart->Init.BaudRate = baud;
		HAL_UART_Init(hUart);
	}
}


/**
 * @brief Transmission Complete Callback
 * 
 * @note This function must be called by HAL_UART_TxCmpltCallback upon completion of a transmission for the relevant UART interface.
 */
void UART::txCmpltCallback(){
	// Interrupt Enable/Disable not necessary because this ISR is to begin the next transmission.
	// interruptsOff();
	txQueue.pop();	// Delete the message that was just sent from the queue.
	next();
	// interruptsOn();
}


/**
 * @brief 
 * 
 * @param size The new head position reported from the UART peripheral.
 */
void UART::rxEventCallback(uint16_t size){
	if(size == rx.dmaBuff.tail) return;	// Do nothing. Unknown event of zero size.
	
	/**
	 * If an interrupt is missed, a condition may arise where the tail was not reset and is now greater than the head.
	 * If so, the tail must be reset. The data at the end of the buffer should not be retrieved as this may create a race condition with the DMA controller.
	 */
	if(rx.dmaBuff.tail > size) rx.dmaBuff.tail = 0;

	// Offload buffer overflow. Reduce size to fill only available capacity. All further characters will be discarded.
	auto head = (rx.offloadBuff.tail + size - rx.dmaBuff.tail > rx.offloadBuff.size) ?  // Will the offload buffer overflow if [size] characters are added.
		rx.offloadBuff.size - rx.offloadBuff.tail + rx.dmaBuff.tail : 	// Only move head to as many characters forward as will fit in offload buffer.
		size; 	// Move head to new head
	
	std::memcpy(rx.offloadBuff.buff + rx.offloadBuff.tail, rx.dmaBuff.buff + rx.dmaBuff.tail, head - rx.dmaBuff.tail);
	rx.offloadBuff.tail += (head - rx.dmaBuff.tail);
	
	rx.dmaBuff.tail = (head == rx.dmaBuff.size) ? 0 : head;	// Loop if at end else move tail to head.
}

/*** END OF FILE ***/