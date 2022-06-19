/**
  ******************************************************************************
  * @file           : NMEA.hpp
  * @brief          : Source / Header file for NMEA.c/.h
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
#include <string>
#include <vector>
#include <array>
#include <memory>

using string = std::string;
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


class NMEA_Standard{
protected:
	struct Address;
	struct Checksum;

public:
	enum class TalkerID;
	enum class Message;

	class DTM;
	class GBS;
	class GGA;
	class GLL;
	class GNS;
	class GRS;
	class GSA;
	class GST;
	class GSV;
	class RLM;
	class RMC;
	class TXT;
	class VLW;
	class VTG;
	class ZDA;

	NMEA_Standard() = default;
	NMEA_Standard(const std::vector<string> & fields);
	// NMEA_Standard(const Address & addr) : addr(addr) {}
	
	virtual string toString() = 0;	// NMEA is an Abstract Class
	inline static bool valid(const string & nmea) {return Checksum::valid(nmea);}

	static std::unique_ptr<NMEA_Standard> factory(const string & nmea);

private:
	struct Address{
		string tt{};	// Talker Identifier (string format)
		string sss{};	// Sentence Formatter
		// Note: tt and sss are typically that many characters long but proprietary messages can be different.
		
		Address() = default;
		Address(const string & s);
		Address(const string & tt, const string & sss);
		string toString();
	} addr{};
	
protected:
	struct Checksum{
		static const char ast = '*';	// Checksum Prefix
		uint8_t cs;						// Checksum Value

		Checksum() = default;
		Checksum(const string & s);
		Checksum(uint8_t c);
		
		static uint8_t checksum(const string & nmea);
		static bool valid(const string & nmea);
		string toString();
	};

	struct UTC_Time{
		uint8_t hh{};	// Hours
		uint8_t mm{};	// Minutes
		float ss{};	// Seconds (2 or 3 decimal points of precision)

		UTC_Time() = default;
		UTC_Time(const string & tStr);
		string toString();
	};

	struct Coordinate{
		uint16_t deg{};
		float min{};

		Coordinate() = default;
		Coordinate(const string & s);

		string toString();

		float operator = (const Coordinate c);
	};


	static const char start = '$';	// Start Character
						// Address field above. Made Private for extension override.
						// Payload data added in derived class.
	Checksum cs{};		// Checksum
	string crlf = "\r\n";

	static std::vector<std::string> parseFields(const string & nmea) noexcept;
	void setChecksum();
	static string toString(const Message msg);
	static string toString(const TalkerID tId);
	
private:
	
};

enum class NMEA_Standard::TalkerID {
	GP,	// GPS, SBAS
	GL, // GLONASS
	GA,	// Galileo
	GB,	// BeiDou
	GQ,	// QZSS
	GN,	// Any Combination
};

enum class NMEA_Standard::Message{
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
	ZDA 	// Time and Date
};

class NMEA_Standard::GNS : public NMEA_Standard{
private:
	UTC_Time time{};	// GNSS UTC Time
	Coordinate lat{};	// Latitude
	char NS{};	// North / South
	Coordinate lon{};	// Longitude
	char EW{};	// East / West
	string posMode{};	// Positioning Mode
	uint8_t numSV{};	// Number of Satellites
	float hdop{};	// Horizontal Dilution of Precision
	float alt{};	// Altitude
	float sep{};	// Geoid Separation
	float diffAge{};	// Age of Differential Corrections
	uint16_t diffStation{};	// Differential Correction Station ID
	char navStatus{};	// Navigational Status Indicator
	
public:
	GNS(const std::vector<string> & fields);
	GNS(const string & nmea);
	inline string toString() final{return "";}	// Unimplemented
};

class NMEA_Standard::GLL : public NMEA_Standard{
private:
	Coordinate lat{};
	char NS{};
	Coordinate lon{};
	char EW{};
	UTC_Time time{};
	char status{};
	char posMode{};

public:
	GLL(const std::vector<string> & fields);
	GLL(const string & nmea);
	inline string toString() final{return "";}
};

class NMEA_Standard::GSA : public NMEA_Standard{
private:
	char opMode{};	// Operational Mode ('M' or 'A')
	uint8_t navMode{};	// Navigation Mode
	std::array<uint8_t, 12> svid;	// Satellite Numbers
	float pdop{};	// Position DOP
	float hdop{};	// Horizontal DOP
	float vdop{};	// Vertical DOP
	uint8_t systemId{};	// GNSS System ID

public:
	GSA(const std::vector<string> & fields);
	GSA(const string & nmea);
	inline string toString() final{return "";}	// Unimplemented
};

class NMEA_Standard::ZDA : public NMEA_Standard{
private:
	struct UTC_DateTime : UTC_Time{
		uint8_t day{};
		uint8_t month{};
		uint16_t year{};
		uint8_t ltzh{};
		uint8_t ltzm{};


		UTC_DateTime() = default;
		UTC_DateTime(const string & time, 
			uint8_t day, uint8_t month, uint16_t year, 
			uint8_t ltzh, uint8_t ltzm);

		} time;

public:
	ZDA(const std::vector<string> & fields);
	ZDA(const string & nmea);
	inline string toString() final{return "";}	// Unimplemented
};


/* End Public Class Definitions */

/*** END OF FILE ***/
