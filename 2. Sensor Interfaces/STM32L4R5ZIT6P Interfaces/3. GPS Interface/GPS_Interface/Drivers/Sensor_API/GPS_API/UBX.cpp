/**
  ******************************************************************************
  * @file           : UBX.cpp
  * @brief          : Source UBX.hpp
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
#include "UBX.hpp"
#include "UBX_ACK.hpp"
#include "UBX_CFG.hpp"
#include "UBX_INF.hpp"
#include "UBX_LOG.hpp"
#include "UBX_MGA.hpp"
#include "UBX_MON.hpp"
#include "UBX_NAV.hpp"
#include "UBX_RXM.hpp"
#include "UBX_TIM.hpp"


#include <vector>


using string = std::string;
using vect = std::vector<uint8_t>;
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

UBX::UBX(uint8_t _msgClass, uint8_t _msgID, uint16_t _len) :
	msgClass(_msgClass), msgID(_msgID), len(_len){}

UBX::UBX(const vect & ubx){
	if(ubx.size() >= 8u){	// Minimum required size for valid UBX frame.
		msgClass = ubx[2];
		msgID = ubx[3];
		len = getLen(ubx);

		if(ubx.size() == (len + 8u) ){		// Check the len. Will also reject inputs with trailing excess elements.
			cs.ckA = ubx[ubx.size() - 2];	// Second to last.
			cs.ckB = ubx[ubx.size() - 1];	// Last
		}
		else{				// Same outcome as below.
			msgClass = msgID = len = 0;
		}
	}
	else{				// Insufficient data to be valid ubx. Default values to 0.
		msgClass = msgID = len = 0;
	}
}

/**
 * @brief CalcuUBX::Checksum::Checksum object from a UBX frame prototype (without any checksum> attached.
 * 
 * @param ubxProto
 */
UBX::Checksum::Checksum(const vect & ubxProto){
	auto v = vect(ubxProto.begin()+2, ubxProto.end());	// Checksum string excludes preamble.
	ckA = ckB = 0;

	for(const auto c : v){
		ckA += c;
		ckB += ckA;
	}
}

UBX::Checksum::Checksum(uint8_t ckA, uint8_t ckB) :
	ckA(ckA), ckB(ckB) {}


template<typename T>
vect UBX::toHex(const T n){
	#ifdef __ARMEL__	// If ARM Little Endian. This should be the default for all STM32 devices.
	return vect(&n, &n + sizeof(T));
	#else
	// Unimplemented
	#endif
}

uint16_t UBX::getLen(const vect & ubx){
	if(
	ubx.size() >= 6){
		#ifdef __ARMEL__	// If ARM Little Endian. This should be the default for all STM32 devices.
		return *(uint16_t *)(
		ubx.data() + 4);
		#elif __ARMEB__		// If ARM Big Endian.
		return (*(uint16_t *)(
		ubx.data() + 4) << 8) | *(
		ubx.data() + 5);
		#else				// Unknown endianess.
		#error "Unknown Endianness"
		#endif
	}
	else return 0;
}




std::unique_ptr<UBX> UBX::factory(const vect & ubx){
	if(ubx.size() == UBX::getLen(ubx) + 8u){
		// UBX * pUbx;
		switch(ubx[2]){
			case 0x05:{
				switch(ubx[3]){
					case 0x01: return std::make_unique<ACKNAK::ACK>(ubx);
					case 0x00: return std::make_unique<ACKNAK::NAK>(ubx);
					default: return nullptr;
				}
			}
			case 0x06:{
				switch(ubx[3]){
					case 0x13: return std::make_unique<CFG::ANT>(ubx);
					case 0x93: return std::make_unique<CFG::BATCH>(ubx);
					case 0x09: return std::make_unique<CFG::CCFG>(ubx);
					case 0x06: return std::make_unique<CFG::DAT>(ubx);
					case 0x69: return std::make_unique<CFG::GEOFENCE>(ubx);
					case 0x3E: return std::make_unique<CFG::GNSS>(ubx);
					case 0x02: return std::make_unique<CFG::INF>(ubx);
					case 0x39: return std::make_unique<CFG::ITFM>(ubx);
					case 0x47: return std::make_unique<CFG::LOGFILTER>(ubx);
					case 0x01: return std::make_unique<CFG::MSG>(ubx);
					case 0x24: return std::make_unique<CFG::NAV5>(ubx);
					case 0x23: return std::make_unique<CFG::NAVX5>(ubx);
					case 0x17: return std::make_unique<CFG::NMEA>(ubx);
					case 0x1E: return std::make_unique<CFG::ODO>(ubx);
					case 0x3B: return std::make_unique<CFG::PM2>(ubx);
					case 0x86: return std::make_unique<CFG::PMS>(ubx);
					case 0x00: return std::make_unique<CFG::PRT>(ubx);
					case 0x57: return std::make_unique<CFG::POWER>(ubx);
					case 0x08: return std::make_unique<CFG::RATE>(ubx);
					case 0x34: return std::make_unique<CFG::RINV>(ubx);
					case 0x04: return std::make_unique<CFG::RST>(ubx);
					case 0x11: return std::make_unique<CFG::RXM>(ubx);
					case 0x16: return std::make_unique<CFG::SBAS>(ubx);
					case 0x31: return std::make_unique<CFG::TP5>(ubx);
					case 0x1B: return std::make_unique<CFG::USB>(ubx);
					case 0x8C: return std::make_unique<CFG::VAL::DEL>(ubx);
					case 0x8B: return std::make_unique<CFG::VAL::GET>(ubx);
					case 0x8A: return std::make_unique<CFG::VAL::SET>(ubx);
					default: return nullptr;
				}
			}
			case 0x04:{
				switch(ubx[3]){
					case 0x04: return std::make_unique<INF::DEBUG>(ubx);
					case 0x00: return std::make_unique<INF::ERROR>(ubx);
					case 0x02: return std::make_unique<INF::NOTICE>(ubx);
					case 0x03: return std::make_unique<INF::TEST>(ubx);
					case 0x01: return std::make_unique<INF::WARNING>(ubx);
					default: return nullptr;
				}
			}
			case 0x21:{
				switch(ubx[3]){
					case 0x11: return std::make_unique<LOG::BATCH>(ubx);
					case 0x07: return std::make_unique<LOG::CREATE>(ubx);
					case 0x03: return std::make_unique<LOG::ERASE>(ubx);
					case 0x0E: return std::make_unique<LOG::FINDTIME>(ubx);
					case 0x08: return std::make_unique<LOG::INFO>(ubx);
					case 0x09: return std::make_unique<LOG::RETRIEVE>(ubx);
					case 0x10: return std::make_unique<LOG::RETRIEVE_BATCH>(ubx);
					case 0x0B: return std::make_unique<LOG::RETRIEVE_POS>(ubx);
					case 0x0F: return std::make_unique<LOG::RETRIEVE_POS_EXTRA>(ubx);
					case 0x0D: return std::make_unique<LOG::RETRIEVE_STRING>(ubx);
					case 0x04: return std::make_unique<LOG::STRING>(ubx);
					default: return nullptr;
				}
			}
			case 0x13:{
				switch(ubx[3]){
					case 0x60: return std::make_unique<MGA::ACK>(ubx);
					case 0x20: return std::make_unique<MGA::ANO>(ubx);
					case 0x03: return std::make_unique<MGA::BDS>(ubx);
					case 0x80: return std::make_unique<MGA::DBD>(ubx);
					case 0x02: return std::make_unique<MGA::GAL>(ubx);
					case 0x06: return std::make_unique<MGA::GLO>(ubx);
					case 0x00: return std::make_unique<MGA::GPS>(ubx);
					case 0x40: return std::make_unique<MGA::INI>(ubx);
					case 0x05: return std::make_unique<MGA::QZSS>(ubx);
					default: return nullptr;
				}
			}
			case 0x0A:{
				switch(ubx[3]){
					case 0x32: return std::make_unique<MON::BATCH>(ubx);
					case 0x36: return std::make_unique<MON::COMMS>(ubx);
					case 0x28: return std::make_unique<MON::GNSS>(ubx);
					case 0x09: return std::make_unique<MON::HW>(ubx);
					case 0x0B: return std::make_unique<MON::HW2>(ubx);
					case 0x37: return std::make_unique<MON::HW3>(ubx);
					case 0x02: return std::make_unique<MON::IO>(ubx);
					case 0x06: return std::make_unique<MON::MSGPP>(ubx);
					case 0x27: return std::make_unique<MON::PATCH>(ubx);
					case 0x38: return std::make_unique<MON::RF>(ubx);
					case 0x07: return std::make_unique<MON::RXBUF>(ubx);
					case 0x21: return std::make_unique<MON::RXR>(ubx);
					case 0x31: return std::make_unique<MON::SPAN>(ubx);
					case 0x08: return std::make_unique<MON::TXBUF>(ubx);
					case 0x04: return std::make_unique<MON::VER>(ubx);
					default: return nullptr;
				}
			}
			case 0x01:{
				switch(ubx[3]){
					case 0x22: return std::make_unique<NAV::CLOCK>(ubx);
					case 0x36: return std::make_unique<NAV::COV>(ubx);
					case 0x04: return std::make_unique<NAV::DOP>(ubx);
					case 0x61: return std::make_unique<NAV::EOE>(ubx);
					case 0x39: return std::make_unique<NAV::GEOFENCE>(ubx);
					case 0x09: return std::make_unique<NAV::ODO>(ubx);
					case 0x34: return std::make_unique<NAV::ORB>(ubx);
					case 0x01: return std::make_unique<NAV::POS::ECEF>(ubx);
					case 0x02: return std::make_unique<NAV::POS::LLH>(ubx);
					case 0x07: return std::make_unique<NAV::PVT>(ubx);
					case 0x10: return std::make_unique<NAV::RESET_ODO>(ubx);
					case 0x35: return std::make_unique<NAV::SAT>(ubx);
					case 0x43: return std::make_unique<NAV::SIG>(ubx);
					case 0x03: return std::make_unique<NAV::STATUS>(ubx);
					case 0x24: return std::make_unique<NAV::TIME::BDS>(ubx);
					case 0x25: return std::make_unique<NAV::TIME::GAL>(ubx);
					case 0x23: return std::make_unique<NAV::TIME::GLO>(ubx);
					case 0x20: return std::make_unique<NAV::TIME::GPS>(ubx);
					case 0x26: return std::make_unique<NAV::TIME::ELS>(ubx);
					case 0x27: return std::make_unique<NAV::TIME::QZSS>(ubx);
					case 0x21: return std::make_unique<NAV::TIME::UTC>(ubx);
					case 0x11: return std::make_unique<NAV::VEL::ECEF>(ubx);
					case 0x12: return std::make_unique<NAV::VEL::NED>(ubx);
					default: return nullptr;
				}
			}
			case 0x02:{
				switch(ubx[3]){
					case 0x14: return std::make_unique<RXM::MEASX>(ubx);
					case 0x41: return std::make_unique<RXM::PMREQ>(ubx);
					case 0x59: return std::make_unique<RXM::RLM>(ubx);
					case 0x32: return std::make_unique<RXM::RTCM>(ubx);
					case 0x13: return std::make_unique<RXM::SFRBX>(ubx);
					default: return nullptr;
				}
			}
			case 0x27:{
				return (ubx[3] == 0x03) ?
					std::make_unique<SEC::UNIQID>(ubx):
					nullptr;
			}
			case 0x0D:{
				switch(ubx[3]){
					case 0x03: return std::make_unique<TIM::TM2>(ubx);
					case 0x01: return std::make_unique<TIM::TP>(ubx);
					case 0x06: return std::make_unique<TIM::VRFY>(ubx);
				}
			}
			case 0x09:{
				return (ubx[3] == 0x14) ?
					std::make_unique<UPD::SOS>(ubx):
					nullptr;
			}
			default: return nullptr;
		}
	}
	else return nullptr;
}




/* End Source Code */


/*** END OF FILE ***/
