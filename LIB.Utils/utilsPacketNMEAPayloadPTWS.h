///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsPacketNMEAPayloadPTWS.h
//
// Standard ISO/IEC 114882, C++17
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2020 02 11  |
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
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadPTWS_JAM_SIGNAL_VAL
{
	static const char* PayloadID;
	static const char* PayloadMsgID;
	static const char* PayloadMsgID2;
	static const char* PayloadMsgCMD;
	static const char* PayloadMsgVAL1;
	static const char* PayloadMsgVAL2;

	typedef Type::tUInt<tUInt8, 0> index_type;
	typedef Type::tFloat<0, 6> frequency_type;

	index_type Index;
	frequency_type Frequency;

	tPayloadPTWS_JAM_SIGNAL_VAL() = default;
	explicit tPayloadPTWS_JAM_SIGNAL_VAL(tUInt8 index, double frequency)
		:Index(index), Frequency(frequency)
	{}
	explicit tPayloadPTWS_JAM_SIGNAL_VAL(const tPayloadCommon::value_type& val)
	{
		if (Try(val))
		{
			Index = index_type(val[5]);
			Frequency = frequency_type(val[7]);
		}
	}

	static bool Try(const tPayloadCommon::value_type& val)
	{
		return val.size() == 8 &&
			!std::strcmp(val[0].c_str(), PayloadID) &&
			!std::strcmp(val[1].c_str(), PayloadMsgID) &&
			!std::strcmp(val[2].c_str(), PayloadMsgID2) &&
			!std::strcmp(val[3].c_str(), PayloadMsgCMD) &&
			!std::strcmp(val[4].c_str(), PayloadMsgVAL1) &&
			!std::strcmp(val[6].c_str(), PayloadMsgVAL2);
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(PayloadMsgID);
		Data.push_back(PayloadMsgID2);
		Data.push_back(PayloadMsgCMD);
		Data.push_back(PayloadMsgVAL1);
		Data.push_back(Index.ToString());
		Data.push_back(PayloadMsgVAL2);
		Data.push_back(Frequency.ToString());

		return Data;
	}
};

const char* tPayloadPTWS_JAM_SIGNAL_VAL::PayloadID = "PTWS";
const char* tPayloadPTWS_JAM_SIGNAL_VAL::PayloadMsgID = "JAM";
const char* tPayloadPTWS_JAM_SIGNAL_VAL::PayloadMsgID2 = "SIGNAL";
const char* tPayloadPTWS_JAM_SIGNAL_VAL::PayloadMsgCMD = "VAL";
const char* tPayloadPTWS_JAM_SIGNAL_VAL::PayloadMsgVAL1 = "INDEX";
const char* tPayloadPTWS_JAM_SIGNAL_VAL::PayloadMsgVAL2 = "FREQ";
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadPTWS_VERSION_GET
{
	static const char* PayloadID;
	static const char* PayloadMsgID;
	static const char* PayloadMsgCMD;

	tPayloadPTWS_VERSION_GET() = default;
	explicit tPayloadPTWS_VERSION_GET(const tPayloadCommon::value_type& val)
	{
		//if (Try(val))
		//{

		//}
	}

	static bool Try(const tPayloadCommon::value_type& val)
	{
		return val.size() == 3 &&
			!std::strcmp(val[0].c_str(), PayloadID) &&
			!std::strcmp(val[1].c_str(), PayloadMsgID) &&
			!std::strcmp(val[2].c_str(), PayloadMsgCMD);
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(PayloadMsgID);
		Data.push_back(PayloadMsgCMD);

		return Data;
	}
};

const char* tPayloadPTWS_VERSION_GET::PayloadID = "PTWS";
const char* tPayloadPTWS_VERSION_GET::PayloadMsgID = "VERSION";
const char* tPayloadPTWS_VERSION_GET::PayloadMsgCMD = "GET";
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadPTWS_VERSION_VAL
{
	static const char* PayloadID;
	static const char* PayloadMsgID;
	static const char* PayloadMsgCMD;

	typedef std::string version_type;

	version_type Version;

	tPayloadPTWS_VERSION_VAL() = default;
	explicit tPayloadPTWS_VERSION_VAL(version_type version)
		:Version(version)
	{}
	explicit tPayloadPTWS_VERSION_VAL(const tPayloadCommon::value_type& val)
	{
		if (Try(val))
		{
			Version = val[3];
		}
	}

	static bool Try(const tPayloadCommon::value_type& val)
	{
		return val.size() == 4 &&
			!std::strcmp(val[0].c_str(), PayloadID) &&
			!std::strcmp(val[1].c_str(), PayloadMsgID) &&
			!std::strcmp(val[2].c_str(), PayloadMsgCMD);
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(PayloadMsgID);
		Data.push_back(PayloadMsgCMD);
		Data.push_back(Version);

		return Data;
	}
};

const char* tPayloadPTWS_VERSION_VAL::PayloadID = "PTWS";
const char* tPayloadPTWS_VERSION_VAL::PayloadMsgID = "VERSION";
const char* tPayloadPTWS_VERSION_VAL::PayloadMsgCMD = "VAL";
///////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
