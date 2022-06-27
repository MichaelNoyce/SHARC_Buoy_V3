/**
  ******************************************************************************
  * @file           : M9N_Base.cpp
  * @brief          : Source M9N_Base.hpp
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


#include "M9N_Base.hpp"

void M9N_Base::transmit(const string & msg){
	transmit( vect(msg.begin(), msg.end()) );
}

void M9N_Base::setRate(NMEA_PUBX::Rate rate){
	transmit(rate.toString());
}

void M9N_Base::setConfig(NMEA_PUBX::Config cfg){
	transmit(cfg.toString());

	if(cfg.baudrate != baud) setBaudrate(cfg.baudrate, cfg.portId);
}

void M9N_Base::silenceDefaultRates(){
	const std::array<NMEA_PUBX::Message, 7u> msgs = {
		NMEA_PUBX::Message::GGA, 
		// NMEA_PUBX::Message::GLL, 
		NMEA_PUBX::Message::GSA, 
		NMEA_PUBX::Message::GSV, 
		NMEA_PUBX::Message::RMC, 
		NMEA_PUBX::Message::VTG,
		NMEA_PUBX::Message::TXT 
		};

	for(auto m : msgs)
		setRate(NMEA_PUBX::Rate(m));
}

/* End Source Code */


/*** END OF FILE ***/
