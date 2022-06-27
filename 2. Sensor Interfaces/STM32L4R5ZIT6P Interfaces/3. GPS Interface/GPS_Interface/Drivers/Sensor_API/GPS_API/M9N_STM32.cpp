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

#include "main.h"
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
M9N::M9N(UART_HandleTypeDef * h, IRQn_Type uartIrq, IRQn_Type dmaTxIrq, IRQn_Type dmaRxIrq) :
	uart(h, uartIrq, dmaTxIrq, dmaRxIrq) {}

// void M9N::write(const string & msg){
// 	HAL_StatusTypeDef halStatus;
// 	unsigned short attempts = 0;
// 	do{
// 		halStatus = HAL_UART_Transmit(uart.hUart, (uint8_t *)msg.c_str(), msg.length(), 100);
		
// 		if(halStatus == HAL_OK) break;
// 		else{
// 			attempts++;
// 			delay(10);
// 		}
// 	} while(attempts < 100);
// }


void M9N::transmit(const std::vector<uint8_t> & msg){
	uart.transmit(msg);		// Delegated to UART class.
}

inline void M9N::delay(uint32_t delay){ HAL_Delay(delay); }

void M9N::setBaudrate(Baud baud, PortID portId){
	switch (portId){
		case PortID::UART1:
			if(this->baud != baud){
				uart.setBaudrate(static_cast<uint32_t>(baud));
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

void M9N::updateMailbox(){
	uart.updateRxQueue();

	vect remainder;
	string s;
	while(!uart.rxQueue.empty()){
		auto v = uart.rxQueue.front(); uart.rxQueue.pop();

		while(!v.empty()){
			switch(v.at(0)){
				case '$':{		// NMEA Sentence Start Character
					s = string(v.begin(), v.end());
					do{
						auto endC = s.find_first_of('\n');
						if(endC != string::npos){	// Newline found. Extract
							auto nmea = s.substr(0, endC + 1);
							s.erase(0, endC + 1);	// Delete all that was extracted.
							v.erase(v.begin(), v.begin() + endC + 1);	// Also delete all characters used from v.

							// Check and adjust for possible errors.
							size_t scI = nmea.find_last_of('$');
							if(scI != 0){	// Error: Second start character. A \n may have been missed and s contains another message sentence.
								nmea.erase(0, scI+1);	// Section before the late '$' is discarded. s is now guaranteed to have exclusive start and end characters.
							}
							
							// Success. Add NMEA message to mailbox.
							nmeaMailbox.push(nmea);
							break;	// Break do-while forever loop.
						}
						else{	// No newline character is found. May be later in queue.
							size_t nlI = string::npos;
							while(!uart.rxQueue.empty()){	// Check if next section is in queue.
								s.append(string(uart.rxQueue.front().begin(), uart.rxQueue.front().end())); uart.rxQueue.pop();
								
								nlI = s.find_last_of('\n');
								if(nlI != string::npos){	// If \n was appended.									
									break;	// \n was found. Break from while loop and recurse into do-while forever loop which will find the \n.
								}
							}
							if(nlI == string::npos){	// Ran out of rxQueue without finding \n
								remainder = v;
								v.clear();
								break;
							}
						}
					} while(true);	// Will be exited with break conditions.
					break;	// Switch Case
				}
				case 0xB5:{		// UBX Sentence Start Character
					if( !uart.rxQueue.empty() && (v.size() < 2) ) {
						v.insert(v.end(), uart.rxQueue.front().begin(), uart.rxQueue.front().end()); // Will append at least 1 character (rxQueue items cannot be empty).
						uart.rxQueue.pop();	
					}

					if(v.size() < 2){	// Queue ran out before sufficient length was appended.
						remainder = v;
						v.clear();
						break;			// Break from case and will then end.
					}
					else{				// s is now at least 2 characters long.
						if(v.at(1) == 0x62){	// Check for second sync character. Else 0xB5 discarded as erroneous.
							resetL:	// Entry point for resetting sequence if l was reset from a prior erroneous value.
							while( !uart.rxQueue.empty() && (v.size() < 6) ){	// Append until length specifier is in v
								v.insert(v.end(), uart.rxQueue.front().begin(), uart.rxQueue.front().end());
								uart.rxQueue.pop();
							}
							if(v.size() >= 6){		
								auto l = UBX::getLen(v);

								while(!uart.rxQueue.empty() && (v.size() < (l + 8u)) ){	// Append until entire UBX frame in v or queue empty;
																					// Note: + 8 adds length for frame preamble and checksum.
									v.insert(v.end(), uart.rxQueue.front().begin(), uart.rxQueue.front().end());
									uart.rxQueue.pop();

									// Check. If l was corrupted, this may send this function searching for a very frame.
									// If l was arbritrarily large, then check if another starting sequence is appended.
									// If so delete all previous characters and reset l to a new value.
									if(l > 100){
										auto secI = std::find_if(v.begin()+1, v.end()-1, [](uint8_t c) -> bool { return ( (c == 0xB5) && (*(&c+1) == 0x62) ) ? true : false; } );

										if(secI != v.end()-1){	// There exists a second set of sync characters.
											v.erase(v.begin(), secI);	// Erase all characters before the second set of sync characters.
											goto resetL;
										}
									}
								}

								if(v.size() < (l + 8u)){	// Frame not yet completely received;
									remainder = v;
									v.clear();
									break;	
								}
								else{	// Success. Frame received and in v.
									const auto endFrame = v.begin() + l + 1;
									auto ubx = vect(v.begin(), endFrame);
									ubxMailbox.push(ubx);
									v = vect(endFrame, v.end());	// Remove all used values from v
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
				default:{		// Not start character. Discard.
					v.erase(v.begin());
					break;
				}
			}
		}
	}
	if(!remainder.empty()) uart.rxQueue.push(remainder);
}

void M9N::processMailbox(){
	updateMailbox();

	while(!nmeaMailbox.empty()){	// NMEA Sentences
		auto nmeaObjP = NMEA::factory(nmeaMailbox.front());

		if(nmeaObjP) nmeaReceived.push(std::move(nmeaObjP));	// Filters out nullptrs.

		nmeaMailbox.pop();
	}

	while(!ubxMailbox.empty()){		// UBX Frames
		auto ubxObjP = UBX::factory(ubxMailbox.front());
		
		if(ubxObjP) ubxReceived.push(std::move(ubxObjP));	// Filters out nullptrs.

		ubxMailbox.pop();
	}
}


extern M9N m9n;	// To be declared in main.
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == m9n.uart.hUart->Instance) m9n.uart.txCmpltCallback();
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if(( huart->Instance == m9n.uart.hUart->Instance) )
		m9n.uart.rxEventCallback(Size);
}


/*** END OF FILE ***/
