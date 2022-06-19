/**
  ******************************************************************************
  * @file           : M9N_STM32.cpp
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

/* --------------------------------------------------------------------------- */
/* Begin Private Includes */
#include "M9N_STM32.hpp"
#include <array>
#include <algorithm>
#include <string>
#include <string.h>
/* End Private Includes */

/* --------------------------------------------------------------------------- */
/* Begin Private Defines */


/* End Private Defines */

/* --------------------------------------------------------------------------- */
/* Begin Private Macros */


/* End Private Macros */

/* --------------------------------------------------------------------------- */
/* Begin Private Typedefs */


/* End Private Typedefs */

/* --------------------------------------------------------------------------- */
/* Begin Private Function Prototypes */


/* End Private Function Prototypes */

/* --------------------------------------------------------------------------- */
/* Begin Private Variables */

/* End Private Variables */

/* --------------------------------------------------------------------------- */
/* Begin Source Code */
M9N::M9N(UART_HandleTypeDef * h, IRQn_Type irq) :
	uart(h, irq){}

void M9N::write(const string & msg){
	HAL_StatusTypeDef halStatus;
	unsigned short attempts = 0;
	do{
		halStatus = HAL_UART_Transmit(uart.hUart, (uint8_t *)msg.c_str(), msg.length(), 100);
		
		if(halStatus == HAL_OK) break;
		else{
			attempts++;
			delay(10);
		}
	} while(attempts < 100);
}

void M9N::transmit(const string & msg){
	uart.transmit(msg);
}

void M9N::setBaudrate(Baud baud, PortID portId){
	switch (portId){
	case PortID::UART1:
		if(HAL_UART_DeInit(uart.hUart) == HAL_OK){
			uart.hUart->Init.BaudRate = static_cast<uint32_t>(baud);
			HAL_UART_Init(uart.hUart);
			this->baud = baud;
		}
		break;
	case PortID::USB:
		// Unimplemented
		break;
	default:
		break;
	}
}


inline void M9N::delay(uint32_t delay){ HAL_Delay(delay); }







M9N::UART::UART(UART_HandleTypeDef * h, IRQn_Type irq) :
	hUart(h), uartIRQ(irq){}

void M9N::UART::transmit(const string & msg){
	// Critical Path. Cannot be interrupted else schedule may be corrupted.
	HAL_NVIC_DisableIRQ(uartIRQ);
	txQueue.push(std::vector<uint8_t>(msg.begin(), msg.end()));
	next();	// Necessary to start transmission from idle. Else message will be sent later.
	HAL_NVIC_EnableIRQ(uartIRQ);
}

void M9N::UART::transmit(const std::vector<uint8_t> & msg){
	// Critical Path. Cannot be interrupted else schedule may be corrupted.
	HAL_NVIC_DisableIRQ(uartIRQ);
	txQueue.push(msg);
	next();
	HAL_NVIC_EnableIRQ(uartIRQ);
}

void M9N::UART::beginReceive(){
	HAL_UARTEx_ReceiveToIdle_DMA(hUart, rxRing.cBuff, rxRing.cBuffLen);		// DMA Circular Mode
}

void M9N::UART::endReceive(){
	HAL_UART_DMAStop(hUart);
}

/**
 * @brief 
 * 
 * @note This method implicitly assumes a little-endian processor format, which is the default for all ARM CPUs.
 */
void M9N::UART::updateMailbox(){
	using vect = std::vector<uint8_t>;

	vect remainder;
	string s;
	while(!rxQueue.empty()){
		auto v = rxQueue.front(); rxQueue.pop();

		while(!v.empty()){
			switch(v.at(0)){
				case '$':{		// NMEA Sentence Start Character
					s = string(v.begin(), v.end());
					v.clear();
					do{
						auto endC = s.find_first_of('\n');
						if(endC != string::npos){	// Newline found. Extract
							auto nmea = s.substr(0, endC + 1);
							s.erase(0, endC);	// Delete all that was extracted.
							v = vect(s.begin(), s.end());	// Return remainder of s to v (NMEA could be followed by UBX).
							
							// Check and adjust for possible errors.
							size_t scI;
							do{
								scI = nmea.substr(1).find_last_of('$');
								if(scI != string::npos){	// Error: Second start character. Previous \n may have been missed.
									nmea.erase(0, scI+1);	// Section before second '$' is discarded. Continue with new start.
								}
							} while(scI != string::npos);
							
							// Success. Add NMEA message to mailbox.
							nmeaMailbox.push(nmea);
							break;	// Break do-while forever loop.
						}
						else{	// No newline character is found. May be later in queue.
							size_t nlI = string::npos;
							while(!rxQueue.empty()){	// Check if next section is in queue.
								s.append(string(rxQueue.front().begin(), rxQueue.front().end())); rxQueue.pop();
								
								nlI = s.find_last_of('\n');
								if(nlI != string::npos){	// If \n was appended.									
									break;	// \n was found. Break from while loop and recurse into do-while loop which will find the \n.
								}
							}
							if(nlI == string::npos){	// Ran out of rxQueue without finding \n
								remainder = vect(s.begin(), s.end());	// Return s to remainder to process in next update;
								s.erase();
								break;
							}
						}
					} while(true);	// Will be exited with break conditions.
					break;	// Switch Case
				}
				case 0xB5:{		// UBX Sentence Start Character
					if( !rxQueue.empty() && (v.size() < 2) ) {
						v.insert(v.end(), rxQueue.front().begin(), rxQueue.front().end()); rxQueue.pop();	// Will append at least 1 character (queue item cannot be empty).
					}

					if(v.size() < 2){	// Queue ran out before sufficient length was appended.
						remainder = v;
						v.clear();
						break;			// Break from case and will then end.
					}
					else{				// s is now at least 2 characters long.
						if(v.at(1) == 0x62){	// Check for second sync character. Else 0xB5 discarded as erroneous.
							while( !rxQueue.empty() && (v.size() < 6) ){	// Append until length specifier is in s
								v.insert(v.end(), rxQueue.front().begin(), rxQueue.front().end()); rxQueue.pop();
							}
							if(v.size() >= 6){		
								auto l = UBX::getLen(v);

								while(!rxQueue.empty() && (v.size() < (l + 8u)) ){	// Append until entire frame in s or queue empty;
																					// Note + 8 adds length for frame preamble and checksum.									
									v.insert(v.end(), rxQueue.front().begin(), rxQueue.front().end()); rxQueue.pop();
								}

								if(v.size() < (l + 8u)){	// Frame not yet completely received;
									remainder = v;
									v.clear();
									break;	
								}
								else{	// Success. Frame received and in s.
									auto ubx = vect(v.begin(), v.begin() + l + 1);
									v = vect(v.begin() + l + 1, v.end());
									ubxMailbox.push(ubx);
									break;	// Break from case
								}
							}
							else{		// Frame not yet completely received.
								remainder = v;
								v.clear();
								break;
							}
						}
						else v.erase(v.begin());	// Invalid starting preamble. Erase
					}
					break;
				}
				default:{		// Not start character. Discard as erroneous.
					v.erase(v.begin());
					break;
				}
			}
		}
	}
	if(!remainder.empty()) rxQueue.push(remainder);
}

void M9N::UART::processMailbox(){
	// TODO: NMEA Processing

	while(!ubxMailbox.empty()){	// UBX Frames
		auto ubxObj = UBX::factory(ubxMailbox.front());
		
		if(ubxObj) ubxReceived.push(std::move(ubxObj));	// May contain nullptrs. Filter out.

		ubxMailbox.pop();
	}
}


void M9N::UART::next(){
	if(!txQueue.empty() && !txBusy()){	
		HAL_UART_Transmit_DMA(hUart, txQueue.front().data(), txQueue.front().size());	// Should be ready based on earlier check.
		// Do not pop. Keep on heap until txCpltCallback to maintain pointer to data().
	}
}

bool M9N::UART::txBusy(){
	const auto halTxState = HAL_UART_GetState(hUart);

	return !( 
		( (halTxState & HAL_UART_STATE_READY) == HAL_UART_STATE_READY ) &&
		( (halTxState & HAL_UART_STATE_BUSY_TX) != HAL_UART_STATE_BUSY_TX) );
}

/**
 * @brief Transmission Complete Callback
 * 
 * @note This function must be called by HAL_UART_TxCmpltCallback upon completion of a transmission for the relevant UART interface.
 */
void M9N::UART::txCmpltCallback(){
	// IRQ Enable/Disable not necessary because this ISR is to begin the next transmission.
	
	// HAL_NVIC_DisableIRQ(uartIRQ);
	txQueue.pop();	// Delete the message that was just sent from the queue.
	next();
	// HAL_NVIC_EnableIRQ(uartIRQ);
}

void M9N::UART::rxHalfCmpltCallback(){
	rxRing.head = rxRing.cBuffLenHalf - 1;
	if(rxRing.head > rxRing.tail){
		auto rxVct = std::vector<uint8_t>(rxRing.cBuff + rxRing.tail, rxRing.cBuff + rxRing.head);
		rxQueue.push(rxVct);
	}
	rxRing.tail = rxRing.cBuffLenHalf;
}

void M9N::UART::rxCmpltCallback(){
	rxRing.head = rxRing.cBuffLen - 1;
	if(rxRing.head > rxRing.tail){
		auto rxVct = std::vector<uint8_t>(rxRing.cBuff + rxRing.tail, rxRing.cBuff + rxRing.head);
		rxQueue.push(rxVct);
	}
	rxRing.tail = 0;
}

void M9N::UART::rxIdleCallback(uint16_t size){
	rxRing.head = rxRing.tail + size;
	if(rxRing.head > rxRing.tail){
		auto rxVct = std::vector<uint8_t>(rxRing.cBuff + rxRing.tail, rxRing.cBuff + rxRing.head);
		rxQueue.push(rxVct);
	}
	rxRing.tail += size;
}


extern M9N m9n;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == m9n.uart.hUart->Instance) m9n.uart.txCmpltCallback();
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == m9n.uart.hUart->Instance) m9n.uart.rxHalfCmpltCallback();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == m9n.uart.hUart->Instance) m9n.uart.rxCmpltCallback();
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if(( huart->Instance == m9n.uart.hUart->Instance) && (__HAL_UART_GET_FLAG(m9n.uart.hUart, UART_FLAG_IDLE)) )
		m9n.uart.rxIdleCallback(Size);
}


/* End Source Code */


/*** END OF FILE ***/
