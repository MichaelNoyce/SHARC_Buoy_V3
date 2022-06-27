/**
  ******************************************************************************
  * @file           : NMEA.cpp
  * @brief          : Header file for NMEA_Standard.hpp
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
#include "NMEA_Standard.hpp"
#include <stdexcept>
#include <map>

template<typename T>
static T safe_stoi(const std::string &__str, std::size_t *__idx = (std::size_t *)0, int __base = 10) noexcept;
static float safe_stof(const string& __str, size_t* __idx = 0) noexcept;

/**
 * @brief Splits a NMEA sentence into a vector containing each field element.
 * 
 * @param nmea NMEA Sentence string.
 * @return std::vector<std::string>& NMEA Sentence field elements.
 * 
 * @note Does not include fields for sentence constants:
 * 			1. The starting character "$".
 * 			2. CRLF "\r\n"
 * @note The checksum field contains the '*'.
 * @note This fuction will return an empty vector if any of the following occurs:
 * 			1. nmea is empty.
 * 			2. nmea does not pass the checksum validation.
 * 			3. nmea does not start with '$'.
 */
std::vector<string> NMEA_Standard::parseFields(const string & nmea) noexcept{
	std::vector<string> fields;
	std::size_t i = 1;

	if(!nmea.empty() && valid(nmea)){	// Only proceed if the NMEA sentence was valid.
		if(nmea.at(0) == '$'){
			std::size_t j;
			for(j = 1; j < nmea.length(); j++){
				if(nmea.at(j) == ','){	// Push each comma delimited item.
					fields.push_back(nmea.substr(i, j-i)); 
					i = j+1;
				}
				else if(nmea.at(j) == '*'){
					fields.push_back(nmea.substr(i, j-i));	// Last field before checksum
					break;
				}
			}
			if(j < nmea.length() - 3) fields.push_back(nmea.substr(j, 3));	// Checksum characters.
		}
	}
	return fields;
}

std::unique_ptr<NMEA_Standard> NMEA_Standard::factory(const string & nmea){
	auto fields = NMEA_Standard::parseFields(nmea);

	static std::map<string, Message> nmeaMap{
		{"DTM", Message::DTM},
		{"GAQ", Message::GAQ},
		{"GBQ", Message::GBQ},
		{"GBS", Message::GBS},
		{"GGA", Message::GGA},
		{"GLL", Message::GLL},
		{"GLQ", Message::GLQ},
		{"GNQ", Message::GNQ},
		{"GNS", Message::GNS},
		{"GPQ", Message::GPQ},
		{"GRS", Message::GRS},
		{"GSA", Message::GSA},
		{"GST", Message::GST},
		{"GSV", Message::GSV},
		{"RLM", Message::RLM},
		{"RMC", Message::RMC},
		{"TXT", Message::TXT},
		{"VLW", Message::VLW},
		{"VTG", Message::VTG},
		{"ZDA", Message::ZDA}	
	};


	if(!fields.empty()){
		switch(nmeaMap[fields[0]]){
			// case Message::DTM: return std::make_unique<DTM>(fields);
			// case Message::GAQ: return std::make_unique<GAQ>(fields);
			// case Message::GBQ: return std::make_unique<GBQ>(fields);
			// case Message::GBS: return std::make_unique<GBS>(fields);
			// case Message::GGA: return std::make_unique<GGA>(fields);
			case Message::GLL: return std::make_unique<GLL>(fields);
			// case Message::GLQ: return std::make_unique<GLQ>(fields);
			// case Message::GNQ: return std::make_unique<GNQ>(fields);
			case Message::GNS: return std::make_unique<GNS>(fields);
			// case Message::GPQ: return std::make_unique<GPQ>(fields);
			// case Message::GRS: return std::make_unique<GRS>(fields);
			case Message::GSA: return std::make_unique<GSA>(fields);
			// case Message::GST: return std::make_unique<GST>(fields);
			// case Message::GSV: return std::make_unique<GSV>(fields);
			// case Message::RLM: return std::make_unique<RLM>(fields);
			// case Message::RMC: return std::make_unique<RMC>(fields);
			// case Message::TXT: return std::make_unique<TXT>(fields);
			// case Message::VLW: return std::make_unique<VLW>(fields);
			// case Message::VTG: return std::make_unique<VTG>(fields);
			case Message::ZDA: return std::make_unique<ZDA>(fields);
			default: return nullptr;
		}
	}
	else return nullptr;
}


/* NMEA Address Methods */

/**
 * @brief Construct a new NMEA::Address::Address object
 * 
 * @param str
 * 
 * @note sss always filled with 3 characters. tt will assume the remainder.
 */
NMEA_Standard::Address::Address(const string & str){
	if(str.length() >= 3){
		tt = str.substr(0, str.length() - 3);
		sss = str.substr(2);
	}
}

NMEA_Standard::Address::Address(const string & tt, const string & sss) :
	tt(tt), sss(sss){}

string NMEA_Standard::Address::toString(){
	return tt + sss;
}

/* NMEA Checksum Methods */

NMEA_Standard::Checksum::Checksum(const string & s){
	std::sscanf(s.c_str(), "*%2hhX", &cs);
}

NMEA_Standard::Checksum::Checksum(uint8_t c){
	cs = c;
}

bool NMEA_Standard::Checksum::valid(const string & nmea){
	auto astI = nmea.find_last_of('*');

	if(nmea.empty() || astI == std::string::npos) return false;

	uint8_t givenC = 0;
	auto nConv = std::sscanf(nmea.substr(astI).c_str(), "*%2hhX\r\n", &givenC);
	if(nConv != 1) return false;	// Scan failed.
	else return givenC == checksum(nmea);
}

uint8_t NMEA_Standard::Checksum::checksum(const string & nmea){
	uint8_t chk = 0x00u;
	for(auto & c : nmea){
		if(c == '$') continue;
		else if (c == '*') break;
		else chk ^= c;
	}
	return chk;
}

void NMEA_Standard::setChecksum(){
	cs.cs = Checksum::checksum(this->toString());
}

string NMEA_Standard::toString(const Message msg){
	switch (msg){
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

string NMEA_Standard::toString(const TalkerID tId){
	switch(tId){
		case TalkerID::GP : return"GP";
		case TalkerID::GL : return"GL";
		case TalkerID::GA : return"GA";
		case TalkerID::GB : return"GB";
		case TalkerID::GQ : return"GQ";
		case TalkerID::GN : return"GN";
		default: return "";
	}
}


string NMEA_Standard::Checksum::toString(){
	char cStr[4];
	auto nConv = std::snprintf(cStr, 4, "*%2X", cs);
	return (nConv == 1) ? std::string(cStr) : "";
}

/* NMEA UTC Time Methods */

NMEA_Standard::UTC_Time::UTC_Time(const string & tStr){
	std::sscanf(tStr.c_str(), "%2hhu%2hhu%f", &hh, &mm, &ss);
}

/*  NMEA Coordinate Methods */

NMEA_Standard::Coordinate::Coordinate(const string & s){
	auto const decI = s.find('.');
	if(
		(decI != string::npos) &&
		(s.length() >= 6)
	){
		char fmt[7];
		std::snprintf(fmt, 7, "%%%1dhd%%f", decI-2);
		std::sscanf(s.c_str(), fmt, &deg, &min);
	}
}

string NMEA_Standard::Coordinate::toString(){
	char cStr[32];	// Arbitrarily large size
	auto nConv = std::snprintf(cStr, 32, "%3d%f", deg, min);
	return (nConv == 2) ? std::string(cStr) : "";
}

/**
 * @brief Assignes the Coordinate in terms of fractional degrees.
 * 
 * @param c	The Coordinate being assigned.
 * @return float The Coordinate in fractional degrees.
 */
float NMEA_Standard::Coordinate::operator = (const Coordinate c){
	return static_cast<float>(deg)*60 + min;
}

/* NMEA GNS Message */

NMEA_Standard::GNS::GNS(const std::vector<string> & fields){
	if(fields.size() == 15){
		// Class constructors will handle empty cases.
								addr 		= fields[0];
								time		= fields[1];
								lat			= fields[2];
		if(!fields[3].empty())	NS 			= fields[3].at(0);
								lon			= fields[4];
		if(!fields[5].empty())	EW 			= fields[5].at(0);
								posMode		= fields[6];
		if(!fields[7].empty())	numSV		= safe_stoi<uint8_t>(fields[7]);
		if(!fields[8].empty())	hdop		= safe_stof(fields[8]);
		if(!fields[9].empty())	alt			= safe_stof(fields[9]);
		if(!fields[10].empty())	sep			= safe_stof(fields[10]);
		if(!fields[11].empty())	diffAge		= safe_stof(fields[11]);
		if(!fields[12].empty())	diffStation	= safe_stoi<uint16_t>(fields[12]);
		if(!fields[13].empty()) navStatus 	= fields[13].at(0);
								cs			= fields[14];
	}
}

NMEA_Standard::GNS::GNS(const string & msg) :
	GNS(parseFields(msg)){}

/* NMEA GLL Message */

NMEA_Standard::GLL::GLL(const std::vector<string> & fields){
	if(fields.size() == 9) {
								addr 	= fields[0];
								lat 	= fields[1];
		if(!fields[2].empty())	NS 		= fields[2].at(0);
								lon 	= fields[3];
		if(!fields[4].empty())	EW 		= fields[4].at(0);
								time 	= fields[5];
		if(!fields[6].empty()) 	status 	= fields[6].at(0);
		if(!fields[7].empty()) 	posMode = fields[7].at(0);
								cs 		= fields[8];
	}
}

NMEA_Standard::GLL::GLL(const string & nmea):
	GLL(parseFields(nmea)){}

/* NMEA GSA Message */

NMEA_Standard::GSA::GSA(const std::vector<string> & fields){
	if(fields.size() == 20){
								addr 		= fields[0];
		if(!fields[1].empty())	opMode 		= fields[1].at(0);
		if(!fields[2].empty()) 	navMode 	= safe_stoi<uint8_t>(fields[2]);
		
		for(int i = 0; i < 12; i++)
		if(!fields[3+i].empty()) svid[i] 	= safe_stoi<uint8_t>(fields[3+i]);
		
		if(!fields[15].empty()) pdop 		= safe_stof(fields[15]);
		if(!fields[16].empty()) hdop 		= safe_stof(fields[16]);
		if(!fields[17].empty()) vdop 		= safe_stof(fields[17]);
		if(!fields[18].empty()) systemId 	= safe_stoi<uint8_t>(fields[18], nullptr, 16);
								cs 			= fields[19];
	}
}

NMEA_Standard::GSA::GSA(const string & nmea) :
	GSA(parseFields(nmea)){}

/* NMEA ZDA Message */


NMEA_Standard::ZDA::ZDA(const std::vector<string> & fields){
	if(fields.size() == 8){
		addr		= fields[0];
		time		= UTC_DateTime(
						fields[1],
						safe_stoi<uint8_t>(fields[2]), safe_stoi<uint8_t>(fields[3]), safe_stoi<uint8_t>(fields[4]),
						safe_stoi<uint8_t>(fields[5]), safe_stoi<uint8_t>(fields[6]) );
		cs			= fields[7];
	}
}

NMEA_Standard::ZDA::ZDA(const string & nmea) :
	ZDA(parseFields(nmea)){}

NMEA_Standard::ZDA::UTC_DateTime::UTC_DateTime(const string & time, 
				uint8_t day, uint8_t month, uint16_t year, 
				uint8_t ltzh, uint8_t ltzm) :
	UTC_Time(time), 
	day(day), month(month), year(year),
	ltzh(ltzh), ltzm(ltzm) {}



/* Exception Safe Numerical String Parsers */

/*
 * @brief Implements the safe_stoi method with a catch-all exception wrapper.
 * 
 * @param __str
 * @param __idx
 * @param __base
 * @return int Parsed value if success, zero if exception thrown.
 */
template<typename T>
T safe_stoi(const std::string &__str, std::size_t *__idx, int __base) noexcept{
	try{ return static_cast<T>(std::stoi(__str, __idx, __base)); }
	catch(std::invalid_argument const &){ return 0; }
	catch(std::out_of_range const &){ return 0; }
	catch(...) { return 0; }
}

/**
 * @brief Implements the safe_stof method with a catch-all exception wrapper.
 * 
 * @param __str
 * @param __idx
 * @return float 
 */
float safe_stof(const string& __str, size_t* __idx) noexcept{
	try{ return std::stof(__str, __idx); }
	catch(std::invalid_argument const &){ return 0.0f; }
	catch(std::out_of_range const &){ return 0.0f; }
	catch(...) { return 0.0f; }
}



/*** END OF FILE ***/
