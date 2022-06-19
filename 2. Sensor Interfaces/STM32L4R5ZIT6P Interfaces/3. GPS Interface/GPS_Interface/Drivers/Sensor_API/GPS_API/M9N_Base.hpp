/**
  ******************************************************************************
  * @file           : M9N.hpp
  * @brief          : Source / Header file for M9N.c/.h
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
#include <map>

#include "NMEA_PUBX.hpp"
#include "UBX.hpp"

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
		class Rate;

	private:
		class PUBX;

		static string toString(const Message msg);
	};

	void setConfig(NMEA_PUBX::Config cfg);
	void silenceDefaultRates();

protected:
	Baud baud {Baud::B38400};	// Assumed MCU Baudrate initialised to 38400.
	
	// virtual void write(const string & msg) = 0;
	virtual void transmit(const string & msg) = 0;
	virtual void delay(uint32_t delay) = 0;
	virtual void setBaudrate(Baud baud = Baud::B38400, PortID portId = PortID::UART1) = 0;
	
	void setRate(NMEA_PUBX::Rate rate);
};

enum class M9N_Base::NMEA_PUBX::Message{
	/* Standard NMEA Sentences. Identical to NMEA_Base::Message */
	DTM,	// Datum Reference
	GAQ,	// GA Poll
	GBQ,	// GB Poll
	GBS,	// Satellite Fault Detection
	GGA,	// GPS Fix Data
	GLL,	// Location with Time and Fix Status
	GLQ,	// GL Poll
	GNQ,	// GN Poll
	GNS,	// GNSS Fix Data
	GPQ,	// GP Poll
	GRS,	// GNSS Range Residuals
	GSA,	// GNSS Dilution of Precision
	GST,	// GNSS Pseudorange Error Statistics
	GSV,	// GNSS Satellites in View
	RLM,	// Return Link Message
	RMC,	// Recommended Minimum Data
	TXT,	// Test transmission
	VLW,	// Dual Ground/Water Distance
	VTG,	// Course over Ground and Speed
	ZDA, 	// Time and Date

	/* uBlox PUBX Extensions  */
	PUBX_CONFIG,	// Protocols and Rate Configuration
	PUBX_POSITION,	// Positional Data
	PUBX_RATE,		// Message Output Rate
	PUBX_SVSTATUS,	// Satellite Status
	PUBX_TIME		// Time Information
};

class M9N_Base::NMEA_PUBX::PUBX : public NMEA_PUBX{
protected:
	struct Address{
		const string pubx{"PUBX"};
		uint8_t msgId;

		Address(uint8_t msgId);
	} addr;

	PUBX(uint8_t msgId);
	virtual string toString() = 0;
};

class M9N_Base::NMEA_PUBX::Config : public PUBX{
public:
	M9N_Base::PortID portId;
	M9N_Base::InProto inProto;
	M9N_Base::OutProto outProto;
	M9N_Base::Baud baudrate;
	bool autobauding;

	Config(
		M9N_Base::PortID portId, 
		M9N_Base::InProto inProto, 
		M9N_Base::OutProto outProto, 
		M9N_Base::Baud baudrate, 
		bool autobauding );

	string toString() override final;
};

class M9N_Base::NMEA_PUBX::Rate : public PUBX{
public:
	Message ID;		// NMEA Message Identifier
					// Note: Interface Description overloaded "msgId". 
					// Swapped "msgId" for "ID" to preserve naming with PUBX.
	uint8_t rddc{};	// Rate on DDC Port
	uint8_t rus1{};	// Rate on UART1 Port
	uint8_t rus2{};	// Rate on UART2 Port
	uint8_t rusb{};	// Rate on USB Port
	uint8_t rspi{};	// Rate on SPI Port
	uint8_t reserved{};	// Always 0

	Rate() = default;
	Rate(
		Message ID,
		uint8_t rus1 = 0u,
		uint8_t rddc = 0u,
		uint8_t rus2 = 0u,
		uint8_t rusb = 0u,
		uint8_t rspi = 0u);

	string toString() override final;
};

/*** END OF FILE ***/
