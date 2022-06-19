/**
  ******************************************************************************
  * @file			: UBX_CFG.hpp
  * @brief			: Configuration classes for UBX Driver.
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

#include "UBX.hpp"

class UBX::CFG : public UBX {
public:
	class ANT;
	class BATCH;
	class CCFG;
	class DAT;
	class GEOFENCE;
	class GNSS;
	class INF;
	class ITFM;
	class LOGFILTER;
	class MSG;
	class NAV5;
	class NAVX5;
	class NMEA;
	class ODO;
	class PM2;
	class PM5;
	class PMS;
	class PRT;
	class POWER;	// PWR. PWR was overloaded by a define.
	class RATE;
	class RINV;
	class RST;
	class RXM;
	class SBAS;
	class TP5;
	class USB;
	class VAL;

private:


};

class UBX::CFG::ANT : public UBX::CFG{
public:
	ANT(const vect & ubx);
};

class UBX::CFG::BATCH : public UBX::CFG{
public:
	BATCH(const vect & ubx);
};

class UBX::CFG::CCFG : public UBX::CFG{
public:
	CCFG(const vect & ubx);
};

class UBX::CFG::DAT : public UBX::CFG{
public:
	DAT(const vect & ubx);
};

class UBX::CFG::GEOFENCE : public UBX::CFG{
public:
	GEOFENCE(const vect & ubx);
};

class UBX::CFG::GNSS : public UBX::CFG{
public:
	GNSS(const vect & ubx);
};

class UBX::CFG::INF : public UBX::CFG{
public:
	INF(const vect & ubx);
};

class UBX::CFG::ITFM : public UBX::CFG{
public:
	ITFM(const vect & ubx);
};

class UBX::CFG::LOGFILTER : public UBX::CFG{
public:
	LOGFILTER(const vect & ubx);
};

class UBX::CFG::MSG : public UBX::CFG{
public:
	MSG(const vect & ubx);
};

class UBX::CFG::NAV5 : public UBX::CFG{
public:
	NAV5(const vect & ubx);
};

class UBX::CFG::NAVX5 : public UBX::CFG{
public:
	NAVX5(const vect & ubx);
};

class UBX::CFG::NMEA : public UBX::CFG{
public:
	NMEA(const vect & ubx);
};

class UBX::CFG::ODO : public UBX::CFG{
public:
	ODO(const vect & ubx);
};

class UBX::CFG::PM2 : public UBX::CFG{
public:
	PM2(const vect & ubx);
};

class UBX::CFG::PM5 : public UBX::CFG{
public:
	PM5(const vect & ubx);
};

class UBX::CFG::PMS : public UBX::CFG{
public:
	PMS(const vect & ubx);
};

class UBX::CFG::PRT : public UBX::CFG{
public:
	PRT(const vect & ubx);
};

class UBX::CFG::POWER : public UBX::CFG{
public:
	POWER(const vect & ubx);
};

class UBX::CFG::RATE : public UBX::CFG{
public:
	RATE(const vect & ubx);
};

class UBX::CFG::RINV : public UBX::CFG{
public:
	RINV(const vect & ubx);
};

class UBX::CFG::RST : public UBX::CFG{
public:
	RST(const vect & ubx);
};

class UBX::CFG::RXM : public UBX::CFG{
public:
	RXM(const vect & ubx);
};

class UBX::CFG::SBAS : public UBX::CFG{
public:
	SBAS(const vect & ubx);
};

class UBX::CFG::TP5 : public UBX::CFG{
public:
	TP5(const vect & ubx);
};

class UBX::CFG::USB : public UBX::CFG{
public:
	USB(const vect & ubx);
};

class UBX::CFG::VAL : public UBX::CFG{
public:
	class DEL;
	class GET;
	class SET;

protected:
	VAL(const vect & ubx);
};

class UBX::CFG::VAL::DEL : public UBX::CFG::VAL{
public:
	DEL(const vect & ubx);
};

class UBX::CFG::VAL::GET : public UBX::CFG::VAL{
public:
	GET(const vect & ubx);
};

class UBX::CFG::VAL::SET : public UBX::CFG::VAL{
public:
	SET(const vect & ubx);
};

/*** END OF FILE ***/