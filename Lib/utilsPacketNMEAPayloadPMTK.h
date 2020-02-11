///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsPacketNMEAPayloadPMTK.h
//
// Standard ISO/IEC 114882, C++11
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2020 02 07  |
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
struct tPayloadPMTK001
{
	const char* PayloadID = "PMTK001";

	enum class tStatus : tUInt8
	{
		InvalidCommand = 0,//0 = Invalid command / packet
		UnsupportedCommand,//1 = Unsupported command / packet type
		Failed,//2 = Valid command / packet, but action failed.
		Succeeded,//3 = Valid command / packet, and action succeeded
	};

	typedef Type::tUInt<tUInt16, 3> command_type;
	typedef Type::tUInt<tStatus, 1> status_type;

	command_type CMD;
	status_type Status;

	tPayloadPMTK001() = default;
	explicit tPayloadPMTK001(const tPayloadCommon::value_type& val)
	{
		if (val.size() == 3 && !std::strcmp(val[0].c_str(), PayloadID))
		{
			CMD = command_type(val[1]);
			Status = status_type(val[2]);
		}
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(CMD.ToString());
		Data.push_back(Status.ToString());

		return Data;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadPMTK010
{
	const char* PayloadID = "PMTK010";

	enum class tStatus : tUInt8
	{
		UNKNOWN = 0,
		STARTUP,
		EPO,//Notification for the host aiding Extended Prediction Orbit (EPO)
		NORMAL,//Notification for the transition to Normal mode is successfully done
		UNINITIALIZED = 0xFF,//Notification for the transition to Normal mode is successfully done
	};

	typedef Type::tUInt<tStatus, 3> status_type;

	status_type Status;

	tPayloadPMTK010() = default;
	explicit tPayloadPMTK010(const tPayloadCommon::value_type& val)
	{
		if (val.size() == 2 && !std::strcmp(val[0].c_str(), PayloadID))
		{
			Status = status_type(val[1]);
		}
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(Status.ToString());

		return Data;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadPMTK011
{
	const char* PayloadID = "PMTK011";

	typedef std::string message_type;

	message_type Message;

	tPayloadPMTK011() = default;
	explicit tPayloadPMTK011(const tPayloadCommon::value_type& val)
	{
		if (val.size() == 2 && !std::strcmp(val[0].c_str(), PayloadID))
		{
			Message = val[1];
		}
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(Message);

		return Data;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadPMTK314
{
	const char* PayloadID = "PMTK314";

	typedef Type::tUInt<tUInt8, 1> status_type;

	status_type GLL;
	status_type RMC;

	tPayloadPMTK314() = default;
	tPayloadPMTK314(tUInt8 gll, tUInt8 rmc)
		:GLL(gll), RMC(rmc)
	{ }
	explicit tPayloadPMTK314(const tPayloadCommon::value_type& val)
	{
		if (val.size() == 2 && !std::strcmp(val[0].c_str(), PayloadID))
		{
			GLL = status_type(val[1]);
			RMC = status_type(val[2]);
		}
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(GLL.ToString());
		Data.push_back(RMC.ToString());

		return Data;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadPMTK705
{
	const char* PayloadID = "PMTK705";

	typedef std::string release_type;
	typedef std::string build_type;
	typedef std::string internal_use_1_type;
	typedef std::string internal_use_2_type;

	release_type Release;
	build_type Build;
	internal_use_1_type InternalUse1;
	internal_use_2_type InternalUse2;

	tPayloadPMTK705() = default;
	tPayloadPMTK705(const std::string& release, const std::string& revision, const std::string& internalUse1, const std::string& internalUse2)
		:Release(release), Build(revision), InternalUse1(internalUse1), InternalUse2(internalUse2)
	{ }
	explicit tPayloadPMTK705(const tPayloadCommon::value_type& val)
	{
		if (val.size() == 5 && !std::strcmp(val[0].c_str(), PayloadID))
		{
			Release = val[1];
			Build = val[2];
			InternalUse1 = val[3];
			InternalUse2 = val[4];
		}
	}

	tPayloadCommon::value_type GetPayload() const
	{
		tPayloadCommon::value_type Data;

		Data.push_back(PayloadID);
		Data.push_back(Release);
		Data.push_back(Build);
		Data.push_back(InternalUse1);
		Data.push_back(InternalUse2);

		return Data;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
