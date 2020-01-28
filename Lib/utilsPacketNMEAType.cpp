#include "utilsPacketNMEAType.h"

namespace utils
{
	namespace packet_NMEA
	{
		namespace Type
		{
///////////////////////////////////////////////////////////////////////////////////////////////////
tDate::tDate(tUInt8 year, tUInt8 month, tUInt8 day)
	:Year(year), Month(month), Day(day)
{

}

tDate::tDate(const std::string& val)
{
	if (val.size() == 6)//260216
	{
		char Data[3]{};//C++11

		Data[0] = val[0];
		Data[1] = val[1];

		Day = static_cast<tUInt8>(std::strtoul(Data, 0, 10));

		Data[0] = val[2];
		Data[1] = val[3];

		Month = static_cast<tUInt8>(std::strtoul(Data, 0, 10));

		Data[0] = val[4];
		Data[1] = val[5];

		Year = static_cast<tUInt8>(std::strtoul(Data, 0, 10));
	}
}

std::string tDate::ToString()
{
	char Str[10]{};

	if (Year < 100 && Month < 13 && Day < 32)
	{
		std::sprintf(Str, "%02d%02d%02d", Day, Month, Year);
	}

	return Str;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}
