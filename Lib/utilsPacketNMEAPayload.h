///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsPacketNMEAPayload.h
//
// Standard ISO/IEC 114882, C++11
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2020 01 28  |
// |            |               | 
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "utilsBase.h"
#include "utilsPacketNMEA.h"
#include "utilsPacketNMEAType.h"

namespace utils
{
	namespace packet_NMEA
	{

template
<
	std::size_t FieldQty,
	int TimeSize,
	int LatitudeSize,
	int LongitudeSize
>
struct tPayloadRMC
{
	typedef Type::tGNSS gnss_type;
	typedef Type::tValid valid_type;
	typedef Type::tDate date_type;
	typedef Type::tTime<TimeSize> time_type;
	typedef Type::tLatitude<LatitudeSize> latitude_type;
	typedef Type::tLongitude<LongitudeSize> longitude_type;

	gnss_type GNSS = gnss_type::UNKNOWN;
	valid_type Valid;
	date_type Date;
	time_type Time;
	latitude_type Latitude;
	longitude_type Longitude;

	tPayloadRMC() = default;
	explicit tPayloadRMC(const tPayloadCommon::value_type& val)
	{
		if (val.size() == FieldQty && val[0].size() > 3 && !std::strcmp(&val[0][2],"RMC"))
		{
			switch (val[0][1])
			{
			case 'P': GNSS = gnss_type::GPS; break;
			case 'L': GNSS = gnss_type::GLONASS; break;
			case 'N': GNSS = gnss_type::GPS_GLONASS; break;
			}

			Time = time_type(val[1]);
			Valid = valid_type(val[2]);
			Latitude = latitude_type(val[3], val[4]);
			Longitude = longitude_type(val[5], val[6]);
			//...
			Date = date_type(val[9]);
		}
	}

	tPayloadCommon::value_type GetPayload()
	{
		tPayloadCommon::value_type Data;

		std::string Str("G");
		switch (GNSS)
		{
		case gnss_type::GPS: Str += 'P'; break;
		case gnss_type::GLONASS: Str += 'L'; break;
		case gnss_type::GPS_GLONASS: Str += 'N'; break;
		default: Str += '-'; break;
		}
		Data.push_back(Str + "RMC");
		Data.push_back(Time.ToString());
		Data.push_back(Valid.ToString());
		Data.push_back(Latitude.ToStringValue());
		Data.push_back(Latitude.ToStringHemisphere());
		Data.push_back(Longitude.ToStringValue());
		Data.push_back(Longitude.ToStringHemisphere());
		Data.push_back("");
		Data.push_back("");
		Data.push_back(Date.ToString());
		Data.push_back("");
		Data.push_back("");
		Data.push_back("");

		return Data;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
