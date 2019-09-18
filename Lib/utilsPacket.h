///////////////////////////////////////////////////////////////////////////////////////////////////
// utilsPacket.h
//
// Standard ISO/IEC 114882, C++17
//
// |   version  |    release    | Description
// |------------|---------------|---------------------------------
// |      1     |   2019 06 20  |
// |            |               | 
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "utilsBase.h"

namespace utils
{
	namespace packet
	{
///////////////////////////////////////////////////////////////////////////////////////////////////
template
<
	template <class> class TFormat,
	class TPayload
>
class tPacket : public TFormat<TPayload>, TPayload
{
public:
	tPacket() { }

	static bool Find(tVectorUInt8& receivedData, tPacket& packet)
	{
		tVectorUInt8::const_iterator Begin = receivedData.cbegin();

		for (;;)
		{
			Begin = std::find(Begin, receivedData.cend(), TFormat<TPayload>::STX);

			if (Begin == receivedData.cend())
			{
				break;
			}

			tVectorUInt8 PacketVector = TFormat<TPayload>::TestPacket(Begin, receivedData.cend());

			if (PacketVector.size() > 0)
			{
				if (TryParse(PacketVector, packet))
				{
					size_t EraseSize = std::distance(receivedData.cbegin(), Begin);

					EraseSize += PacketVector.size();

					receivedData.erase(receivedData.begin(), receivedData.begin() + EraseSize);

					return true;
				}
			}

			Begin++;
		}

		return false;
	}

	static bool TryParse(const tVectorUInt8& packetVector, tPacket& packet)
	{
		return TFormat<TPayload>::TryParse(packetVector, packet, packet);
	}

	template <class tMsg>
	tMsg GetMsg() const
	{
		return tMsg(TPayload::Data);
	}

	template <class tMsg>
	void SetMsg(const tMsg& msg)
	{
		TFormat<TPayload>::SetPayloadIDs(msg);

		TPayload::Data = msg.ToVector();
	}

	tVectorUInt8 ToVector()
	{
		size_t PayloadSize = TPayload::GetSize();

		size_t PacketSize = TFormat<TPayload>::GetSize(PayloadSize);

		tVectorUInt8 PacketVector;

		PacketVector.reserve(PacketSize);

		TFormat<TPayload>::Append(PacketVector, *this);

		return PacketVector;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
struct tPayloadCommon
{
	tVectorUInt8 Data;

	tPayloadCommon() { }

	tPayloadCommon(tVectorUInt8::const_iterator cbegin, tVectorUInt8::const_iterator cend)
	{
		Data.insert(Data.end(), cbegin, cend);
	}

	size_t GetSize() const { return Data.size(); }

	void Append(tVectorUInt8& dst) const
	{
		dst.insert(dst.end(), Data.cbegin(), Data.cend());
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
	}
}