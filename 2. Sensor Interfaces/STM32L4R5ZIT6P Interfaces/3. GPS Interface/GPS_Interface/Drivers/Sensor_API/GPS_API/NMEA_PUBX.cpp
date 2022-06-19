/**
  ******************************************************************************
  * @file			: NMEA_PUBX.cpp
  * @brief			: Source for NMEA_PUBX.hpp
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

#include "NMEA_PUBX.hpp"

M9N_Base::NMEA_PUBX::PUBX::PUBX(uint8_t msgId) :
	NMEA_PUBX(),
	addr(msgId) {}

M9N_Base::NMEA_PUBX::Config::Config(
	M9N_Base::PortID portId, 
	M9N_Base::InProto inProto, 
	M9N_Base::OutProto outProto, 
	M9N_Base::Baud baudrate, 
	bool autobauding) :
		PUBX(41u),
		portId(portId),
		inProto(inProto),
		outProto(outProto),
		baudrate(baudrate),
		autobauding(autobauding){
			setChecksum();
}

string M9N_Base::NMEA_PUBX::Config::toString(){
	// Buffer initialised to an arbritray size.
	const std::size_t size = 36;
	char buff[size];	// Arbitrarily large size.

	std::snprintf(buff, size, "$PUBX,41,%1hu,%04hX,%04hX,%lu,%1u*%02X\r\n",
					static_cast<uint8_t>(portId), 
					static_cast<uint16_t>(inProto), 
					static_cast<uint16_t>(outProto), 
					static_cast<uint32_t>(baudrate),
					autobauding ? 1u : 0u,
					cs.cs);
	return std::string(buff);
}

string M9N_Base::NMEA_PUBX::toString(const Message msg){
	switch(msg){
		/* PUBX Extension Cases */
		case Message::PUBX_CONFIG: 		return "PUBX,41";
		case Message::PUBX_POSITION: 	return "PUBX,00";
		case Message::PUBX_RATE: 		return "PUBX,03";
		case Message::PUBX_SVSTATUS: 	return "PUBX,03";
		case Message::PUBX_TIME: 		return "PUBX,04";

		/* Standard NMEA Cases */
		// Duplicated from NMEA_Standard::toString() because NMEA_PUBX::Message did
		// not inherit enumerals from NMEA_Standard::Message. 
		// Without explicit enumeral values, casting is prone to error.
		// This approach is therefore safer, and the Standard NMEA messages will rarely change if ever.
		case Message::DTM : return "DTM";
		case Message::GAQ : return "GAQ";
		case Message::GBQ : return "GBQ";
		case Message::GBS : return "GBS";
		case Message::GGA : return "GGA";
		case Message::GLL : return "GLL";
		case Message::GLQ : return "GLQ";
		case Message::GNQ : return "GNQ";
		case Message::GNS : return "GNS";
		case Message::GPQ : return "GPQ";
		case Message::GRS : return "GRS";
		case Message::GSA : return "GSA";
		case Message::GST : return "GST";
		case Message::GSV : return "GSV";
		case Message::RLM : return "RLM";
		case Message::RMC : return "RMC";
		case Message::TXT : return "TXT";
		case Message::VLW : return "VLW";
		case Message::VTG : return "VTG";
		case Message::ZDA : return "ZDA";

		default: return "";
	}
}

M9N_Base::NMEA_PUBX::Rate::Rate(
	Message ID,
	uint8_t rddc,
	uint8_t rus1,
	uint8_t rus2,
	uint8_t rusb,
	uint8_t rspi ) :
		PUBX(40u),
		ID(ID),
		rddc(rddc),
		rus1(rus1),
		rus2(rus2),
		rusb(rusb),
		rspi(rspi) {
			setChecksum();
}

string M9N_Base::NMEA_PUBX::Rate::toString(){
	const std::size_t size = 42;
	char buff[size];

	std::snprintf(buff, size, "$PUBX,40,%3s,%1u,%1u,%1u,%1u,%1u,%1u*%02X\r\n",
					NMEA_PUBX::toString(ID).c_str(),	
					rddc, rus1, rus2, rusb, rspi, reserved, cs.cs );
	
	return std::string(buff);
}

/*** END OF FILE ***/