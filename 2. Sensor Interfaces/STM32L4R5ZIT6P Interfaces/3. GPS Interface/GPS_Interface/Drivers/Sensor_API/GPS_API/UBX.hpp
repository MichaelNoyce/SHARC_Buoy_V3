/**
  ******************************************************************************
  * @file           : UBX.hpp
  * @brief          : uBlox Proprietary UBX Protocol Driver
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

#include "stdio.h"

#include <array>
#include <vector>
#include <string>
#include <memory>
#include <map>

using string = std::string;
using vect = std::vector<uint8_t>;
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
class UBX{
public:
	class ACKNAK;
	class CFG;
	class INF;
	class LOG;
	class MGA;
	class MON;
	class NAV;
	class RXM;
	class SEC;
	class TIM;
	class UPD;

	static uint16_t getLen(const vect & _ubx);

	template<typename T>
	vect toHex(const T n);

	static std::unique_ptr<UBX> factory(const vect & _ubx);
	
protected:
	static const uint8_t sync1 = 0xB5;	// mu
	static const uint8_t sync2 = 0x62;	// b
	uint8_t msgClass;
	uint8_t msgID;
	uint16_t len;

	struct Checksum{
		uint8_t ckA;
		uint8_t ckB;

		Checksum() = default;
		Checksum(const vect & _ubxProto);
		Checksum(uint8_t _ckA, uint8_t _ckB);

		inline vect toHex() {return vect{ckA, ckB};}
	} cs;

	UBX() = default;
	UBX(uint8_t _msgClass, uint8_t _msgID, uint16_t _len);
	UBX(const vect & _ubx);

private:
	static std::map<uint8_t, std::map<uint8_t, UBX *>> factoryMap;
};

class UBX::SEC : public UBX{
public:
	class UNIQID;
};

class UBX::SEC::UNIQID : public UBX::SEC{
public:
	UNIQID(const vect & ubx);
};

class UBX::UPD : public UBX{
public:
	class SOS;
};

class UBX::UPD::SOS : public UBX::UPD{
public:
	SOS(const vect & ubx);
};


/* End Public Class Definitions */

/*** END OF FILE ***/
