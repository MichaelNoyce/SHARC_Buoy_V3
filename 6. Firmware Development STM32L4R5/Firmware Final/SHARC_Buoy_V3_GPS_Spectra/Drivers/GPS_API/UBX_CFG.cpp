/**
  ******************************************************************************
  * @file			: UBX_CFG.cpp
  * @brief			: Source for UBX_CFG.hpp
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

#include "UBX_CFG.hpp"
#include "M9N_Base.hpp"

#include <type_traits>

/**
 * @brief 
 * 
 * @return uint8_t 
 * 
 * ! There is a duplication of information between KeyValuePair::tag and KeyID::size. This function assumed upon KeyID::size. !
 */
uint8_t UBX::CFG::VAL::KeyValuePair::size() const{
	switch(keyId.size){
		case KeyID::Size::BIT:		return 1u;
		case KeyID::Size::BYTE:		return 1u;
		case KeyID::Size::WORD:		return 2u;
		case KeyID::Size::DOUBLE:	return 4u;
		case KeyID::Size::QUAD:		return 8u;
		default: return 0u;
	}
}

std::pair<std::array<uint8_t, 12>, uint8_t> UBX::CFG::VAL::KeyValuePair::value() const{
	std::pair<std::array<uint8_t, 12>, uint8_t> b;

	for(auto i = 0u; i < 4; i++ ) b.first[i] = (keyId.toKey() & (0xFFul << 8*i)) >> 8*i; 

	b.second = size() + 4u;

	uint32_t val;
	switch(tag){
		case KeyValuePair::L:  val = l;  break;
		case KeyValuePair::U1: val = u1; break;
		case KeyValuePair::I1: val = i1; break;
		case KeyValuePair::E1: val = e1; break;
		case KeyValuePair::X1: val = x1; break;
		case KeyValuePair::U2: val = u2; break;
		case KeyValuePair::I2: val = i2; break;
		case KeyValuePair::E2: val = e2; break;
		case KeyValuePair::X2: val = x2; break;
		case KeyValuePair::U4: val = u4; break;
		case KeyValuePair::I4: val = i4; break;
		case KeyValuePair::E4: val = e4; break;
		case KeyValuePair::X4: val = x4; break;
		case KeyValuePair::R4: val = r4; break;
		default: return b;
	}
	#ifdef __ARMEL__
	for(auto i = 4u; i < b.second; i++) b.first[i] = (val & (0xFFul << 8*(i-4))) >> 8*(i-4);
	#else
	#error "UBX Key Value Pair Bit Packing not implemented for non-little endian system."
	#endif
	return b;
}




UBX::X4 UBX::CFG::VAL::KeyID::toKey() const {
	return ( ( ((X4)size) << 28 ) | ( ((X4)groupID) << 16 ) | ( ((X4)itemID) ) );
}

std::pair<std::array<uint8_t, 8+64*12>, uint8_t> UBX::CFG::VAL::SET::binary() const noexcept {
	std::array<uint8_t, 8+64*12> data;
	auto head = header();

	std::copy(head.begin(), head.end(), data.begin());

	data[4] = version;
	data[5] = static_cast<uint8_t>(layers);
	data[6] = reserved0[0];
	data[7] = reserved0[1];

	size_t k = 8;
	for(auto i = 0u; i < cfgData.second; i++){
		auto b = cfgData.first[i].value();
		std::copy(b.first.begin(), b.first.begin() + b.second, data.begin() + k);
		k += b.second;
	}

	// cs = Checksum(data.begin() + 2, data.begin() + k);
	data[k++] = cs.ckA;
	data[k++] = cs.ckB;

	return {data, k};
}

void UBX::CFG::VAL::SET::push(KeyValuePair cfg){
	cfgData.first[cfgData.second++] = cfg;
	len += (cfg.size() + 4);
}


/*** END OF FILE ***/