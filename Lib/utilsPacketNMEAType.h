///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsPacketNMEAType.h
//
// Standard ISO/IEC 114882, C++11
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2020 01 27  |
// |            |               | 
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "utilsBase.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>

namespace utils
{
	namespace packet_NMEA
	{
		namespace Type
		{
///////////////////////////////////////////////////////////////////////////////////////////////////
enum class tGNSS : tUInt8//It's like bitfield
{
	UNKNOWN = 0,
	GPS = 1,    //0000'0001
	GLONASS,    //0000'0010
	GPS_GLONASS,//0000'0011
};
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tDate
{
	tUInt8 Year = 0;
	tUInt8 Month = 0;
	tUInt8 Day = 0;

	tDate() = default;//C++11
	tDate(tUInt8 year, tUInt8 month, tUInt8 day);
	explicit tDate(const std::string& val);	

	std::string ToString();
};
///////////////////////////////////////////////////////////////////////////////////////////////////
template <std::size_t Size>
struct tTime
{
	tUInt8 Hour = 0;
	tUInt8 Minute = 0;
	double Second = 0;

	tTime() = default;
	tTime(tUInt8 hour, tUInt8 minute, double second) :Hour(hour), Minute(minute), Second(second) {}
	explicit tTime(const std::string& val)
	{
		if (val.size() == Size)
		{
			char Data[3]{};//C++11

			Data[0] = val[0];
			Data[1] = val[1];

			Hour = static_cast<tUInt8>(std::strtoul(Data, 0, 10));

			Data[0] = val[2];
			Data[1] = val[3];

			Minute = static_cast<tUInt8>(std::strtoul(Data, 0, 10));

			Second = std::strtod(val.c_str() + 4, 0);
		}
	}

	std::string ToString()
	{
		char Str[Size + 1]{};

		if (Hour < 24 && Minute < 60 && Second < 60)
		{
			switch (Size)
			{
			case 6: std::sprintf(Str, "%02d%02d%02d", Hour, Minute, static_cast<tUInt8>(Second)); break;
			case 10: std::sprintf(Str, "%02d%02d%06.3f", Hour, Minute, Second); break;
			}
		}

		return Str;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
template <std::size_t Size>
struct tLatitude
{
	double Value = 0;

	tLatitude() = default;
	explicit tLatitude(double val) :Value(val) {}
	tLatitude(const std::string& val, const std::string& valSign)
	{
		static_assert(Size == 9 || Size == 11, "tLatitude: Size");//C++11

		if (val.size() == Size && valSign.size() == 1)
		{
			char Data[3]{};

			std::strncpy(Data, val.c_str(), sizeof(Data) - 1);

			Value = std::strtod(Data, 0);

			double Rest = std::strtod(val.c_str() + 2, 0);

			Value += Rest / 60;

			if (valSign[0] == 'S')
			{
				Value = -Value;
			}
		}
	}

	std::string ToStringValue()
	{
		double ValueAbs = std::abs(Value);

		tUInt8 Deg = static_cast<tUInt8>(ValueAbs);
		double Min = (ValueAbs - Deg) * 60;

		char Str[Size + 1]{};

		if (Deg < 100)
		{
			switch (Size)
			{
			case 9: std::sprintf(Str, "%02d%07.4f", Deg, Min); break;
			case 11: std::sprintf(Str, "%02d%09.6f", Deg, Min); break;
			}
		}

		return Str;
	}

	std::string ToStringHemisphere()
	{
		return Value < 0 ? "S" : "N";
	}

	std::string ToString()
	{
		return ToStringValue() + ',' + ToStringHemisphere();
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
template <std::size_t Size>
struct tLongitude
{
	double Value = 0;

	tLongitude() = default;
	explicit tLongitude(double val) :Value(val) { }
	tLongitude(const std::string& val, const std::string& valSign)
	{
		static_assert(Size == 10 || Size == 12, "tLongitude: Size");//C++11

		if (val.size() == Size && valSign.size() == 1)
		{
			char Data[4]{};

			std::strncpy(Data, val.c_str(), sizeof(Data) - 1);

			Value = std::strtod(Data, 0);

			double Rest = std::strtod(val.c_str() + 3, 0);

			Value += Rest / 60;

			if (valSign[0] == 'W')
			{
				Value = -Value;
			}
		}
	}

	std::string ToStringValue()
	{
		double ValueAbs = std::abs(Value);

		tUInt16 Deg = static_cast<tUInt16>(ValueAbs);
		double Min = (ValueAbs - Deg) * 60;

		char Str[Size + 1]{};

		if (Deg < 1000)
		{
			switch (Size)
			{
			case 10: std::sprintf(Str, "%03d%07.4f", Deg, Min); break;
			case 12: std::sprintf(Str, "%03d%09.6f", Deg, Min); break;
			}
		}

		return Str;
	}

	std::string ToStringHemisphere()
	{
		return Value < 0 ? "W" : "E";
	}

	std::string ToString()
	{
		return ToStringValue() + ',' + ToStringHemisphere();
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}
