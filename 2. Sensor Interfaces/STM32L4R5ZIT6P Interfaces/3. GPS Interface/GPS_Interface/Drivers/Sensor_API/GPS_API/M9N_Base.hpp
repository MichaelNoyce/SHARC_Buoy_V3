/**
  ******************************************************************************
  * @file           : M9N.hpp
  * @brief          : Header file for uBlox M9N Base Driver.
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

#include <stdio.h>
#include <vector>
#include <string>
#include <map>

#include "UBX.hpp"
#include "NMEA_Standard.hpp"

using vect = std::vector<uint8_t>;

class M9N_Base{
public:

	enum class PortID : uint8_t{
		UART1 = 1u,	// UART Interface
		USB = 3u	// Serial USB Interface
	};
	
	enum class InProto : uint16_t{
		UBX   = 0x0001u,
		NMEA  = 0x0002u,
		RTCM  = 0x0004u,
		RTCM3 = 0x0020u,
		ALL   = 0x0027u
	};

	enum class OutProto : uint16_t{
		UBX   = 0x0001u,
		NMEA  = 0x0002u
	};

	enum class Baud : uint32_t{
		B9600 = 9600u,
		B19200 = 19200u,
		B38400 = 38400u,
		B115200 = 115200u,
		B230400 = 230400u,
		B460800 = 460800u,
		B921600 = 921600u
	};

	enum class MessageType{
		NMEA,
		UBX,
		RTCM
	};

	class NMEA_PUBX : public NMEA_Standard{
	public:
		enum class Message;

		class Config;
		class Position;
		class Rate;
		class SvStatus;
		class Time;

	private:
		class PUBX;

		static string toString(const Message msg);
	};

	/* NMEA Protocol API */
	using NMEA = NMEA_PUBX;
	void setConfig(NMEA::Config cfg);

	void setRate(NMEA::Rate rate);
	void silenceDefaultRates();

	/* UBX Protocol API */
	// TODO

protected:
	Baud baud {Baud::B38400};	// Assumed MCU Baudrate initialised to 38400.
	
	/*****************************************************************************************************************************/
										/* Application Specific Communication and Control Interface */
	/* This class must be extended and must implement the following methods based on the device-specific peripherals.*/
	
	/**
	 * @brief Transmit a vector of byte-sized values on the selected communication interface.
	 * 
	 * @param msg
	 * 
	 * @note The transmission may occur in non-blocking mode but should send messages in the sequence that they were requested.
	 */
	virtual void transmit(const std::vector<uint8_t> & msg) = 0;
	
	/**
	 * @brief Delay the program execution.
	 * 
	 * @param delay	Delay in milliseconds.
	 * 
	 * @note The delay need not be precise but should delay by at least the the passed amount of time.
	 */
	virtual void delay(uint32_t delay) = 0;

	/**
	 * @brief Set the baudrate of the relevant communication peripheral device.
	 * 
	 * @param baud		The baudrate to set in bits per second.
	 * @param portId	The Port the baudrate change should occur upon.
	 * 
	 * @note This method will not be called at startup. The peripheral communication interface should default to 
	 * 		 the M9N's default baudrate to begin communication.
	 */
	virtual void setBaudrate(Baud baud = Baud::B38400, PortID portId = PortID::UART1) = 0;
	/*****************************************************************************************************************************/
	
protected:
	virtual void transmit(const string & msg);

};

#include "NMEA_PUBX.hpp"

/*** END OF FILE ***/
