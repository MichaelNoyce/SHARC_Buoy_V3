/**
  ******************************************************************************
  * @file			: UBX_ACK.hpp
  * @brief			: Acknowledge Classes for UBX Driver
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

class UBX::ACKNAK : public UBX{
public:
	class ACK;
	class NAK;
protected:
	uint8_t ackClsID;	//Class ID of Acknowledged/Not Acknowledged Message.
	uint8_t ackMsgID;	//Message ID of Acknowledged/Not Acknowledged Message.

	ACKNAK(const vect & ubx);
	ACKNAK(uint8_t ackNakID, uint8_t ackClsID, uint8_t ackMsgID);

private:
	ACKNAK() = default;
};

class UBX::ACKNAK::ACK : public ACKNAK{
public:
	ACK(const vect & ubx);
	ACK(uint8_t ackClsID, uint8_t ackMsgID);
};

class UBX::ACKNAK::NAK : public ACKNAK{
public:
	NAK(const vect & ubx);
	NAK(uint8_t ackClsID, uint8_t ackMsgID);
};


/*** END OF FILE ***/