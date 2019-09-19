///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsPacketNMEABin.h
//
// Created by Sergey Maslennikov
// Tel.:   
// E-mail: maslennikovserge@yandex.ru
//
// Standard ISO/IEC 114882, C++17
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2019 09 19  |
// |            |               | 
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "utilsPacketNMEA.h"

#include <string>
#include <vector>

namespace utils
{
	namespace packet_NMEA
	{
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class TPayload>
struct tFormatNMEABin// : public tFormatNMEA<TPayload>
{
	static const unsigned char STX = '!';

protected:
	template <class tMsg>
	void SetPayloadIDs(const tMsg& msg) { }

	static tVectorUInt8 TestPacket(tVectorUInt8::const_iterator cbegin, tVectorUInt8::const_iterator cend)
	{
		size_t Size = std::distance(cbegin, cend);

		if (Size >= GetSize(0) && *cbegin == STX)
		{
			tVectorUInt8::const_iterator Begin = cbegin + 1;
			tVectorUInt8::const_iterator End = std::find(Begin, cend, '*');

			if (End != cend)
			{
				size_t DataSize = std::distance(Begin, End);

				if (Size >= GetSize(DataSize) && VerifyCRC(Begin, DataSize))
				{
					return tVectorUInt8(cbegin, cbegin + GetSize(DataSize));
				}
			}
		}

		return tVectorUInt8();
	}

	static bool TryParse(const tVectorUInt8& packetVector, tFormatNMEABin& format, TPayload& payload)
	{
		if (packetVector.size() >= GetSize(0) && packetVector[0] == STX)
		{
			tVectorUInt8::const_iterator Begin = packetVector.cbegin() + 1;
			tVectorUInt8::const_iterator End = std::find(Begin, packetVector.cend(), '*');

			if (End != packetVector.cend())
			{
				size_t DataSize = std::distance(Begin, End);

				if (packetVector.size() == GetSize(DataSize) && VerifyCRC(Begin, DataSize))
				{
					payload = TPayload(Begin, End);

					return true;
				}
			}
		}

		return false;
	}

	static size_t GetSize(size_t payloadSize) { return sizeof(STX) + payloadSize + 5; };//$*xx\xd\xa

	void Append(tVectorUInt8& dst, const TPayload& payload) const
	{
		dst.push_back(STX);

		payload.Append(dst);

		unsigned char CRC = utils::crc::CRC08_NMEA<tVectorUInt8::const_iterator>(dst.cbegin() + 1, dst.cend());

		dst.push_back('*');

		char StrCRC[5];
		sprintf_s(StrCRC, "%02X", CRC);

		dst.push_back(StrCRC[0]);
		dst.push_back(StrCRC[1]);

		dst.push_back(0x0D);
		dst.push_back(0x0A);
	}

private:
	static bool VerifyCRC(tVectorUInt8::const_iterator begin, size_t crcDataSize)
	{
		auto CRC = utils::crc::CRC08_NMEA(begin, begin + crcDataSize);

		tVectorUInt8::const_iterator CRCBegin = begin + crcDataSize + 1;//1 for '*'

		auto CRCReceived = utils::Read<unsigned char>(CRCBegin, CRCBegin + 2, utils::tRadix_16);

		return CRC == CRCReceived;
	}
};

	}
}
